import json

from src.models.type import Type
from src.ext.database import db

class TypeService():
    def delete(request):
        try:
            typeJson = request.args.get('id')
            type = Type.query.filter_by(id_type = typeJson).first()

            db.session.delete(type)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def add(request):
        try:
            typeJson = request.json

            name = typeJson['name']

            type = Type(name)
            db.session.add(type)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def update(request):
        try:
            typeJson = request.json
            type = Type.query.filter_by(id_type = typeJson['id']).first()

            type.name = typeJson['name']

            db.session.commit()
            return "ok", 200
        except Exception as e:
            return str(e), 400

    def getAllTypes(request):
        try:
            typeResult = Type.query.all()
            typeList = list(map(lambda type: {"id":type.id_type, "name":type.name}, typeResult))
            return json.dumps(typeList)
        except Exception as e:
            return str(e), 400