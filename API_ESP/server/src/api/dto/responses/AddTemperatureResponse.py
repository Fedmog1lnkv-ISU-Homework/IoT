from pydantic import BaseModel


class AddTemperatureResponse(BaseModel):
    is_successful: bool
    message: str
