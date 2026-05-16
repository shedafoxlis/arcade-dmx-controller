# REST API Documentation

## Base URL

```
http://192.168.x.x/api/
```

## Endpoints

### Status

#### GET /api/status

Get controller status

**Response:**
```json
{
  "status": "ok",
  "heap": 2048000,
  "uptime": 12345
}
```

### Scenes

#### POST /api/scene

Activate a scene

**Parameters:**
- `id` (uint8_t): Scene ID (0-9)

**Example:**
```
POST /api/scene?id=0
```

**Response:**
```json
{
  "ok": true
}
```

### Programs

#### POST /api/program

Activate a program for a group

**Parameters:**
- `group` (uint8_t): Group ID (0-4)
- `id` (uint8_t): Program ID (0-5)

**Example:**
```
POST /api/program?group=0&id=2
```

### DMX Control

#### POST /api/dmx

Set DMX channel value

**Parameters:**
- `ch` (uint16_t): Channel (0-511)
- `val` (uint8_t): Value (0-255)

**Example:**
```
POST /api/dmx?ch=0&val=255
```

### Recording

#### POST /api/record/start

Start recording show

#### POST /api/record/stop

Stop recording

#### POST /api/record/play

**Parameters:**
- `id` (uint8_t): Show ID

## HTTP Response Codes

| Code | Meaning |
|------|----------|
| 200  | Success |
| 400  | Bad Request |
| 404  | Not Found |
| 500  | Server Error |
