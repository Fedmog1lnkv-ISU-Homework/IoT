from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from src.api.dto.requests.AddTemperatureRequest import AddTemperatureRequest
from src.api.dto.responses.AddTemperatureResponse import AddTemperatureResponse
from src.api.dto.responses.GetTemperatureResponse import GetTemperatureResponse
from src.data.config import get_db
from src.data.dbo.TemperatureDbo import TemperatureDbo

router = APIRouter()


@router.post("/add_value", response_model=AddTemperatureResponse)
async def add_value(temp: AddTemperatureRequest, db: Session = Depends(get_db)):
    temperature = TemperatureDbo(location=temp.location, value=temp.value)
    db.add(temperature)
    db.commit()
    return AddTemperatureResponse(is_successful=True, message="Temperature added")


@router.get("/get_values", response_model=GetTemperatureResponse)
async def get_values(location: str, db: Session = Depends(get_db)):
    temperatures = db.query(TemperatureDbo).filter(TemperatureDbo.location == location).all()
    temperatures = [float(tdb.value) for tdb in temperatures]

    return GetTemperatureResponse(is_successful=True, values=temperatures)