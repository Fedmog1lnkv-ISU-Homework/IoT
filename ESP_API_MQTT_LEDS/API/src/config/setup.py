from fastapi import FastAPI

from src.auth_router import auth_router
from src.database import SqliteDB, create_device_table, create_user_table, create_color_leds_table
from src.device_router import device_router
from src.pixels_router import pixel_router


def init_tables():
    engine = SqliteDB()
    create_user_table(engine)
    create_color_leds_table(engine)
    create_device_table(engine)
    engine.close_connection()


def setup():
    init_tables()

    app = FastAPI(title='leds')
    app.include_router(auth_router)
    app.include_router(pixel_router)
    app.include_router(device_router)

    return app
