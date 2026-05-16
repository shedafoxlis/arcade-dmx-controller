#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "../config.h"

class WebServer {
public:
    void init() {
        // Setup WiFi
        WiFi.softAP(WIFI_SSID, WIFI_PASSWORD);
        Serial.printf("[WiFi] AP started: %s\n", WIFI_SSID);
        Serial.printf("[WiFi] IP: %s\n", WiFi.softAPIP().toString().c_str());
        
        // Setup routes
        setupRoutes();
        
        // Start server
        server.begin();
        Serial.println("[WEB] Server started on port 80");
    }
    
    void setupRoutes() {
        // Status endpoint
        server.on("/api/status", HTTP_GET, [this](AsyncWebServerRequest *request) {
            DynamicJsonDocument doc(256);
            doc["status"] = "ok";
            doc["heap"] = ESP.getFreeHeap();
            doc["uptime"] = millis() / 1000;
            
            String response;
            serializeJson(doc, response);
            request->send(200, "application/json", response);
        });
        
        // Scene control
        server.on("/api/scene", HTTP_POST, [this](AsyncWebServerRequest *request) {
            if (request->hasParam("id")) {
                uint8_t sceneId = request->getParam("id")->value().toInt();
                Serial.printf("[WEB] Activate scene %d\n", sceneId);
                request->send(200, "application/json", "{\"ok\":true}");
            } else {
                request->send(400, "application/json", "{\"error\":\"Missing id\"}");
            }
        });
        
        // DMX channel control
        server.on("/api/dmx", HTTP_POST, [this](AsyncWebServerRequest *request) {
            if (request->hasParam("ch") && request->hasParam("val")) {
                uint16_t ch = request->getParam("ch")->value().toInt();
                uint8_t val = request->getParam("val")->value().toInt();
                Serial.printf("[WEB] DMX ch%d = %d\n", ch, val);
                request->send(200, "application/json", "{\"ok\":true}");
            } else {
                request->send(400, "application/json", "{\"error\":\"Missing parameters\"}");
            }
        });
        
        // Web UI (embedded)
        server.on("/", HTTP_GET, [this](AsyncWebServerRequest *request) {
            request->send(200, "text/html", getWebUI());
        });
    }
    
private:
    AsyncWebServer server{WEB_PORT};
    
    String getWebUI() {
        return R"(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ARCADE DMX Controller</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: Arial, sans-serif; background: #1a1a1a; color: #fff; }
        .container { max-width: 800px; margin: 20px auto; padding: 20px; }
        h1 { margin-bottom: 20px; color: #00ff00; }
        .scene-grid { display: grid; grid-template-columns: repeat(2, 1fr); gap: 10px; margin-bottom: 20px; }
        .scene-btn {
            padding: 15px; background: #222; border: 2px solid #00ff00; color: #00ff00;
            font-size: 14px; cursor: pointer; border-radius: 4px; transition: all 0.2s;
        }
        .scene-btn:hover { background: #00ff00; color: #000; }
        .scene-btn.active { background: #00ff00; color: #000; }
        .status { background: #222; padding: 15px; border: 1px solid #444; border-radius: 4px; margin-top: 20px; }
        .status-item { display: flex; justify-content: space-between; margin: 5px 0; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🎆 ARCADE DMX Controller</h1>
        <div class="scene-grid" id="scenes"></div>
        <div class="status">
            <div class="status-item">
                <span>Статус:</span>
                <span id="status">Инициализация...</span>
            </div>
            <div class="status-item">
                <span>Свободная память:</span>
                <span id="heap">---</span>
            </div>
            <div class="status-item">
                <span>Время работы:</span>
                <span id="uptime">---</span>
            </div>
        </div>
    </div>
    <script>
        const scenes = ['Red', 'Green', 'Blue', 'White', 'Cyan', 'Magenta', 'Yellow', 'Orange', 'Purple', 'Blackout'];
        const sceneGrid = document.getElementById('scenes');
        
        scenes.forEach((name, id) => {
            const btn = document.createElement('button');
            btn.className = 'scene-btn';
            btn.textContent = name;
            btn.onclick = () => activateScene(id);
            sceneGrid.appendChild(btn);
        });
        
        function activateScene(id) {
            fetch(`/api/scene?id=${id}`, { method: 'POST' })
                .then(r => r.json())
                .then(d => console.log('Scene activated:', d));
        }
        
        function updateStatus() {
            fetch('/api/status')
                .then(r => r.json())
                .then(d => {
                    document.getElementById('status').textContent = d.status;
                    document.getElementById('heap').textContent = (d.heap / 1024).toFixed(1) + ' KB';
                    document.getElementById('uptime').textContent = (d.uptime) + ' sec';
                });
        }
        
        setInterval(updateStatus, 1000);
        updateStatus();
    </script>
</body>
</html>
        )";
    }
};

#endif // WEB_SERVER_H
