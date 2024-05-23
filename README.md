## Features

- **Memory Usage Endpoint**: Provides detailed information about the system's memory usage.
- **CPU Usage Endpoint**: Reports the current CPU usage percentage.
- **Swap Memory Endpoint**: Provides details about the system's swap memory.
- **System Information Endpoint**: Aggregates memory, CPU, and swap memory information into a single response.

## Endpoints

### 1. Get Memory Usage

**URL**: `/api/memory`  
**Method**: `GET`  
**Description**: Returns detailed information about the system's memory usage.

**Response**:
```json
{
    "total": "Total memory in bytes",
    "available": "Available memory in bytes",
    "percent": "Memory usage percentage",
    "used": "Used memory in bytes",
    "free": "Free memory in bytes"
}
```

### 2. Get CPU Usage

**URL**: `/api/cpu`  
**Method**: `GET`  
**Description**: Returns the current CPU usage percentage.

**Response**:
```json
{
    "cpu_percent": "CPU usage percentage"
}
```

### 3. Get Swap Memory

**URL**: `/api/swap`  
**Method**: `GET`  
**Description**: Returns detailed information about the system's swap memory.

**Response**:
```json
{
    "total": "Total swap memory in bytes",
    "used": "Used swap memory in bytes",
    "free": "Free swap memory in bytes",
    "percent": "Swap memory usage percentage",
    "sin": "Amount of swap memory swapped in from disk in bytes",
    "sout": "Amount of swap memory swapped out to disk in bytes"
}
```

### 4. Get System Information

**URL**: `/api/system`  
**Method**: `GET`  
**Description**: Returns a combined report of memory usage, CPU usage, and swap memory information.

**Response**:
```json
{
    "memory": {
        "total": "Total memory in bytes",
        "available": "Available memory in bytes",
        "percent": "Memory usage percentage",
        "used": "Used memory in bytes",
        "free": "Free memory in bytes"
    },
    "cpu": {
        "cpu_percent": "CPU usage percentage"
    },
    "swap": {
        "total": "Total swap memory in bytes",
        "used": "Used swap memory in bytes",
        "free": "Free swap memory in bytes",
        "percent": "Swap memory usage percentage",
        "sin": "Amount of swap memory swapped in from disk in bytes",
        "sout": "Amount of swap memory swapped out to disk in bytes"
    }
}
```

## Setup

### Requirements

- Python 3.x
- Flask
- psutil
- flask-cors

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/adgsenpai/systemstatsapi.git
    cd systemstatsapi
    ```

2. Create a virtual environment:
    ```bash
    python3 -m venv venv
    source venv/bin/activate
    ```

3. Install the required packages:
    ```bash
    pip install -r requirements.txt
    ```

### Running the Application

1. Start the Flask application:
    ```bash
    python app.py
    ```

2. The application will be running at `http://0.0.0.0:5000`.

## License

This project is licensed under the MIT License.

---

Feel free to contribute to this project by submitting issues or pull requests. For any questions or suggestions, please contact the project maintainer.
 