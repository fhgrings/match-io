from flask_influxdb import InfluxDB

db = InfluxDB()

def init_app(app):
    db.init_app(app)
