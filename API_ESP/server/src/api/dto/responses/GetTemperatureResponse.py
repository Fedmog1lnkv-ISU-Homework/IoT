from pydantic import BaseModel


class GetTemperatureResponse(BaseModel):
    is_successful: bool
    values: list