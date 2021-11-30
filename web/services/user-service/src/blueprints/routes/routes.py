from flask import Flask, jsonify, request, make_response
import jwt
from functools import wraps

from src.services.user_service import UserService


def init_app(app):

    @app.route('/user/add-user', methods=['POST'])
    def add_user():
        return UserService.add(request)


    @app.route('/user/edit-user', methods=['POST'])
    def edit_user():
        return UserService.editUser(request)

    @app.route('/user/get-roles')
    def getRoles():
        return UserService.getRoles(request)

    @app.route('/user/get-permission-list')
    def getPermissions():
        return UserService.getPermission(request)

    @app.route('/user/get-all')
    def getAllUsers():
        return UserService.getAllUsers(request)

    @app.route('/user/get-user-by-id')
    def getUserById():
        return UserService.getUserById(request)

