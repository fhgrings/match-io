from flask import Flask, jsonify, request, make_response
import json
import jwt
import datetime
from sqlalchemy import or_

from src.models.user import User
from src.models.role import Role
from src.models.permission import Permission
from src.ext.database import db

class UserService():
    def login(request, app):
        if app.config['public_key'] != request.json['public_key']:
            return make_response("Could not verify!", 401, {"Erro": "Erro"})
        try:
            username = request.json['username']
            password = request.json['password']
        except Exception as e:
            return "Wrong paragemeters", 400

        try:
            user = User.query.filter_by(username=username, password = password).join(Role, Role.id_role == User.id_role).join(Permission, Permission.id_permission == User.id_permission).add_columns(User.email, User.phone, User.id_user, User.first_name, User.last_name, Role.name.label("role"), Permission.name.label("permission")).first()

            if not user:
                return make_response("User or password does not match!", 403, {"Erro": "user or password incorrect"})

            token = jwt.encode({'user': username, 'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=30)},
                               app.config['SECRET_KEY'])
            print(token.decode('UTF-8'))
            returnable = {
                "user": {
                    "first_name" : user.first_name,
                    "last_name" : user.last_name,
                    "id_user" : user.id_user,
                    "role" : user.role,
                    "permission" : user.permission,
                    "email" : user.email,
                    "phone" : user.phone
                },
                "token": token.decode('UTF-8')
            }
            return json.dumps(returnable)
        except Exception as e:
            return str(e), 400
    def getNewToken(request, app):
        token = request.headers.get('Authorization')
        user = jwt.decode(token, app.config['SECRET_KEY'])
        newToken = jwt.encode({'user': user, 'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=30)}, app.config['SECRET_KEY'])

        return jsonify({'token': newToken.decode('UTF-8')})

    def add(request):
        try:
            userJson = request.json
            permission = Permission.query.filter_by(name=userJson['id_permission']).first()
            role = Role.query.filter_by(name=userJson['id_role']).first()

            username = userJson['username']
            password = userJson['password']
            first_name = userJson['first_name']
            last_name = userJson['last_name']
            email = userJson['email']
            phone = userJson['phone']
            id_role = role.id_role
            id_permission = permission.id_permission

            user = User(username, password, first_name, last_name, email, phone, id_role, id_permission)
            db.session.add(user)
            db.session.commit()
            return "ok"
        except Exception as e:
            return str(e), 400

    def editUser(request):
        try:
            userJson = request.json
            permission = Permission.query.filter_by(name = userJson['id_permission']).first()
            role = Role.query.filter_by(name = userJson['id_role']).first()
            user = User.query.filter_by(id_user = userJson['id_user']).first()

            user.username = userJson['username']
            user.first_name = userJson['first_name']
            user.last_name = userJson['last_name']
            user.email = userJson['email']
            user.phone = userJson['phone']
            user.id_role = role.id_role
            user.id_permission = permission.id_permission

            db.session.commit()
            return "ok", 200
        except Exception as e:
            return str(e), 400

    def getAllUsers(request):
        name = ""
        try:
            name = request.args['name']
        except:
            pass
        try:
            search = "%{}%".format(name)
            userResult = list(User.query.filter(or_(User.first_name.like(search),User.last_name.like(search))).join(Role, Role.id_role == User.id_role).join( Permission, Permission.id_permission == User.id_permission).add_columns(User.email, User.phone, User.id_user, User.first_name, User.last_name, Role.name.label("role"), Permission.name.label("permission")).all())
            userList = list(map(lambda user: {"first_name" : user.first_name,
                                                "last_name" : user.last_name,
                                                "id_user" : user.id_user,
                                                "role" : user.role,
                                                "permission" : user.permission,
                                                "email" : user.email,
                                                "phone" : user.phone
                                              },userResult))

            return json.dumps(userList)
        except Exception as e:
            return str(e), 400

    def getUserById(request):
        try:
            id_user = request.args['id_user']
            user = User.query.filter_by(id_user = id_user).join(Role, Role.id_role == User.id_role).join(Permission, Permission.id_permission == User.id_permission).add_columns(User.username, User.email, User.phone, User.id_user, User.first_name, User.last_name, Role.name.label("role"), Permission.name.label("permission")).first()
            user = {
                "id_user": user.id_user,
                "username" : user.username,
                "first_name": user.first_name,
                "last_name": user.last_name,
                "role": user.role,
                "permission": user.permission,
                "email": user.email,
                "phone": user.phone
            }
            return json.dumps(user)
        except Exception as e:
            return str(e), 400


    def getRoles(request):
        try:
            roleResult = Role.query.all()
            roleList = list(map(lambda x: x.name, roleResult))
            return json.dumps(roleList)
        except Exception as e:
            return str(e), 400

    def getPermission(request):
        try:
            permissionResult = Permission.query.all()
            permissionList = list(map(lambda x: x.name, permissionResult))
            return json.dumps(permissionList)
        except Exception as e:
            return str(e), 400

