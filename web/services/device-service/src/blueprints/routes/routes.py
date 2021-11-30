from flask import request

from src.services.device_service import DeviceService
from src.services.perfil_service import PerfilService
from src.services.type_service import TypeService

def init_app(app):

    @app.route('/')
    def alive():
        return "device service"

    @app.route('/device/get-all')
    def getAllDevices():
        return DeviceService.getAllDevices(request)

    @app.route('/device/delete')
    def deleteDevice():
        return DeviceService.delete(request)

    @app.route('/device/add', methods=['POST'])
    def addDevice():
        return DeviceService.add(request)

    @app.route('/device/update', methods=['POST'])
    def updateDevice():
        return DeviceService.update(request)


    @app.route('/perfil/get-all')
    def getAllPerfils():
        return PerfilService.getAllPerfils(request)

    @app.route('/perfil/delete')
    def deletePerfil():
        return PerfilService.delete(request)

    @app.route('/perfil/add', methods=['POST'])
    def addPerfil():
        return PerfilService.add(request)

    @app.route('/perfil/update', methods=['POST'])
    def updatePerfil():
        return PerfilService.update(request)
    


    @app.route('/type/get-all')
    def getAllTypes():
        return TypeService.getAllTypes(request)

    @app.route('/type/delete')
    def deleteType():
        return TypeService.delete(request)

    @app.route('/type/add', methods=['POST'])
    def addType():
        return TypeService.add(request)

    @app.route('/type/update', methods=['POST'])
    def updateType():
        return TypeService.update(request)