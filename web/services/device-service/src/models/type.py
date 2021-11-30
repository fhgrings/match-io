from ..ext.database import db

class Type(db.Model):
    __tablename__ = "Type"
    id_type = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(30))
    def __init__(self, name):
        self.name = name
        db.create_all()

    def dump(self, _indent=0):
        return (
            "   " * _indent
            + repr(self)
            + "\n"
        )
