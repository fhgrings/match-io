import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    client.subscribe(topic)
    client.publish(topic, "SERVER STARTED", qos=0, retain=False)
    client.publish(topic, "CONNECTED", qos=0, retain=False)


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))

def on_publish(client, userdata, mid):
    print("Message Sent")

def init_app(app):
    host = app.config.MQTT_HOST
    port = app.config.MQTT_PORT
    topic = app.config.MQTT_TOPIC

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.on_publish = on_publish
    client.username_pw_set("username", "password")
    client.connect(host, port)
    app.mqtt = client