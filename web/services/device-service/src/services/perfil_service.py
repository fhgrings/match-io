import json

from src.models.perfil import Perfil
from src.ext.database import db

class PerfilService():
    def delete(request):
        try:
            perfilJson = request.args.get('id')
            perfil = Perfil.query.filter_by(id_perfil = perfilJson).first()

            db.session.delete(perfil)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def add(request):
        try:
            perfilJson = request.json

            name = perfilJson['name']
            refresh_rate = perfilJson['refresh_rate']
            print(refresh_rate)

            perfil = Perfil(name, refresh_rate)
            db.session.add(perfil)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def update(request):
        try:
            perfilJson = request.json
            perfil = Perfil.query.filter_by(id_perfil = perfilJson['id']).first()

            perfil.name = perfilJson['name']
            perfil.refresh_rate = perfilJson['refresh_rate']

            db.session.commit()
            return "ok", 200
        except Exception as e:
            return str(e), 400

    def getAllPerfils(request):
        try:
            perfilResult = Perfil.query.all()
            perfilList = list(map(lambda perfil: {"id":perfil.id_perfil, "name":perfil.name, "refresh_rate":perfil.refresh_rate}, perfilResult))
            return json.dumps(perfilList)
        except Exception as e:
            return str(e), 400