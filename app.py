from flask import Flask, jsonify
from flask_cors import CORS
import psutil

app = Flask(__name__)
CORS(app)

@app.route('/api/memory', methods=['GET'])
def get_memory_usage():
    memory_info = psutil.virtual_memory()
    memory_usage = {
        'total': memory_info.total,
        'available': memory_info.available,
        'percent': memory_info.percent,
        'used': memory_info.used,
        'free': memory_info.free
    }
    return jsonify(memory_usage)

@app.route('/api/cpu', methods=['GET'])
def get_cpu_usage():
    cpu_percent = psutil.cpu_percent(interval=1)
    cpu_usage = {
        'cpu_percent': cpu_percent
    }
    return jsonify(cpu_usage)

@app.route('/api/swap', methods=['GET'])
def get_swap_memory():
    swap_info = psutil.swap_memory()
    swap_memory = {
        'total': swap_info.total,
        'used': swap_info.used,
        'free': swap_info.free,
        'percent': swap_info.percent,
        'sin': swap_info.sin,
        'sout': swap_info.sout
    }
    return jsonify(swap_memory)

@app.route('/api/system', methods=['GET'])
def get_system_info():
    memory_info = psutil.virtual_memory()
    memory_usage = {
        'total': memory_info.total,
        'available': memory_info.available,
        'percent': memory_info.percent,
        'used': memory_info.used,
        'free': memory_info.free
    }
    
    cpu_percent = psutil.cpu_percent(interval=1)
    cpu_usage = {
        'cpu_percent': cpu_percent
    }
    
    swap_info = psutil.swap_memory()
    swap_memory = {
        'total': swap_info.total,
        'used': swap_info.used,
        'free': swap_info.free,
        'percent': swap_info.percent,
        'sin': swap_info.sin,
        'sout': swap_info.sout
    }
    
    system_info = {
        'memory': memory_usage,
        'cpu': cpu_usage,
        'swap': swap_memory
    }
    
    return jsonify(system_info)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
