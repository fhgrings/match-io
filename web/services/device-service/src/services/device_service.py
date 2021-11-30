import json

from sqlalchemy.sql.elements import Null

from src.models.device import Device
from src.ext.database import db

class DeviceService():
    def delete(request):
        try:
            deviceJson = request.args.get('id')
            device = Device.query.filter_by(id_device = deviceJson).first()

            db.session.delete(device)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def add(request):
        try:
            deviceJson = request.json

            name = deviceJson['name']
            description = deviceJson['description']
            id_type = deviceJson['id_type']
            id_perfil = deviceJson['id_perfil']

            device = Device(name, description, id_type, id_perfil)
            db.session.add(device)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def update(request):
        try:
            deviceJson = request.json
            device = Device.query.filter_by(id_device = deviceJson['id']).first()

            device.id_device = deviceJson['new_id']
            device.name = deviceJson['name']
            device.description = deviceJson['description']
            device.id_type = deviceJson['id_type']
            device.id_perfil = deviceJson['id_perfil']

            db.session.commit()
            return "ok", 200
        except Exception as e:
            return str(e), 400

    def getAllDevices(request):
        try:
            deviceResult = Device.query.all()
            deviceList = list(map(lambda device: {"id":device.id_device, "name":device.name, "description": device.description, "id_type":device.id_type,"id_perfil":device.id_perfil}, deviceResult))
            return json.dumps(deviceList)
        except Exception as e:
            return str(e), 400