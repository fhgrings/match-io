import json
from ..ext.database import db

class User(db.Model):
    __tablename__ = "User"
    id_user = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20))
    password = db.Column(db.String(20))
    first_name = db.Column(db.String(20))
    last_name = db.Column(db.String(20))
    email = db.Column(db.String(20))
    phone = db.Column(db.String(20))
    id_role = db.Column(db.Integer)
    id_permission = db.Column(db.Integer)

    def __init__(self, username, password, first_name, last_name, email, phone = None, id_role = 0, id_permission = 0):
        self.username = username
        self.password = password
        self.first_name = first_name
        self.last_name = last_name
        self.email = email
        self.phone = phone
        self.id_role = id_role
        self.id_permission = id_permission
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

