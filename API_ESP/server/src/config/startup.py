from fastapi import FastAPI

from src.api.routers import temperature, location
from src.data.config import init_db


def create_app():
    init_db()
    app = FastAPI()
    include_routers(app)
    return app

def include_routers(app: FastAPI):
    app.include_router(temperature.router)
    app.include_router(location.router)