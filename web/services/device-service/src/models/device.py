import json
from ..ext.database import db

class Device(db.Model):
    __tablename__ = "Device"
    id_device = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(30))
    description = db.Column(db.String(30))
    id_type = db.Column(db.Integer)
    id_perfil = db.Column(db.Integer)

    def __init__(self, name, description, id_type, id_perfil):
        self.name = name
        self.description = description
        self.id_type = id_type
        self.id_perfil = id_perfil
        db.create_all()

    def dump(self, _indent=0):
        return (
            "   " * _indent
            + repr(self)
            + "\n"
        )

    def without_sa_instance_state(self):
        del self.__dict__['_sa_instance_state']
        return self.__dict__

    def toJson(self):
        del self.__dict__['_sa_instance_state']
        return json.dumps(self.__dict__)

