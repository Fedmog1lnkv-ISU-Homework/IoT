from pydantic import BaseModel


class GetLocationsResponse(BaseModel):
    is_successful: bool
    locations: list
