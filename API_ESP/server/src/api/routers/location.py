from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session

from src.api.dto.responses.GetLocationsResponse import GetLocationsResponse
from src.data.config import get_db
from src.data.dbo.TemperatureDbo import TemperatureDbo

router = APIRouter()


@router.get("/get_locations", response_model=GetLocationsResponse)
async def get_locations(db: Session = Depends(get_db)):
    locations = db.query(TemperatureDbo.location).distinct().all()
    locations = [location[0] for location in locations]

    return GetLocationsResponse(is_successful=True, locations=locations)