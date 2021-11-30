from flask import Flask, jsonify, request, make_response, abort
from requests.auth import HTTPBasicAuth
import requests
import json

from ...utils.jsonToPoints import JsonToPoint
from ...ext.database import db



def init_app(app):

    @app.route('/')
    def openRoute():
        return jsonify({'message' : 'Anyone can view this'})

    @app.route('/mqtt/add-data', methods=['POST'])
    def addData():
        json_body = request.get_json()
        try:
            json = JsonToPoint(json_body)
            print(db.write_points(json))
        except Exception as e:
            return str(e), 400
        return jsonify({'message': 'data added'})

    @app.route('/mqtt/publish')
    def mqttPublish():
        data = {
            "topic":"/matchio",
            "payload":"1",
            "qos":1,
            "retain":"false",
            "clientid":"example"
        }
        headers = {'content-type': 'application/json'}
        try:
            url = 'http://35.232.145.183:8081/api/v4/mqtt/publish'
            auth = HTTPBasicAuth('admin', 'public')
            r = requests.post(url=url, data=json.dumps(data), auth=auth, headers=headers)
            return "ok"
        except Exception as e:
            return str(e), 400