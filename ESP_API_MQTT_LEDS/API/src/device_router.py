from fastapi import APIRouter, Depends
from pydantic import BaseModel

from src.auth_router import check_auth, FullUserInfo
from src.database import SqliteDB

device_router = APIRouter(prefix="/device", tags=['Devices'])


class DeviceRegister(BaseModel):
    name: str
    mac_addr: str


@device_router.post("/register")
def register_device(device: DeviceRegister, auth: FullUserInfo = Depends(check_auth)):
    engine = SqliteDB()
    stmt = f"""
        INSERT INTO Devices (device_name, mac_address, user_id) VALUES
         ('{device.name}', '{device.mac_addr}', '{auth.id}')
        """
    engine.execute_query(stmt)
    engine.close_connection()
    return {"ok": True, "message": "Device register successful"}


@device_router.get("/my-devices")
def get_user_devices(auth: FullUserInfo = Depends(check_auth)):
    engine = SqliteDB()
    stmt = f"""
        SELECT * FROM Devises WHERE user_id='{auth.id}'
        """
    result = engine.execute_query(stmt)
    print(result)
    engine.close_connection()
