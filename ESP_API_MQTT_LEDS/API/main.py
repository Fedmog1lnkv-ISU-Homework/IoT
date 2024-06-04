import uvicorn

from src.config.setup import setup

if __name__ == "__main__":
    app = setup()
    uvicorn.run(app, host='127.0.0.1', port=5000)
