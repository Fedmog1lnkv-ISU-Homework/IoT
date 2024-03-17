from pydantic import BaseModel

class AddTemperatureRequest(BaseModel):
    location: str
    value: float