from flask import Flask, jsonify, request, make_response
import jwt
from functools import wraps

from src.services.login_service import LoginService


def init_app(app):

    def token_required(f):
        @wraps(f)
        def decorated(*args, **kwargs):
            token = request.headers.get('Authorization')
            if not token:
                return jsonify({'message': 'Token is missing'}), 403
            try:
                data = jwt.decode(token, app.config['SECRET_KEY'])
            except:
                return jsonify({'message': "Token is invalid"})
            return f(*args, **kwargs)
        return decorated


    @app.route('/')
    def openRoute():
        return jsonify({'message' : 'Anyone can view this'})
    
    @app.route('/closed')
    @token_required
    def closed():
        return jsonify({'message' : 'Message from closed endpoint server'})

    @app.route('/login', methods = ['POST'])
    def login():
        return LoginService.login(request, app)


    @app.route('/token')
    @token_required
    def getNewToken():
        return LoginService.getNewToken(request, app)