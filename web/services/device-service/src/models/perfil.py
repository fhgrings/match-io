from ..ext.database import db

class Perfil(db.Model):
    __tablename__ = "Perfil"
    id_perfil = db.Column(db.Integer, primary_key=True)
    refresh_rate = db.Column(db.Integer)
    name = db.Column(db.String(30))
    def __init__(self, name,refresh_rate):
        self.name = name
        self.refresh_rate = refresh_rate
        db.create_all()

    def dump(self, _indent=0):
        return (
            "   " * _indent
            + repr(self)
            + "\n"
        )
