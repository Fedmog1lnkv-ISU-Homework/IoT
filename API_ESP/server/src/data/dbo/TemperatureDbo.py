from sqlalchemy import Column, Integer, String, Double
from src.data.config import Base


class TemperatureDbo(Base):
    __tablename__ = 'temperature'

    id = Column(Integer, primary_key=True, index=True)
    location = Column(String(80), nullable=False)
    value = Column(Double, nullable=False)
