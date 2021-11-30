import json, datetime

def JsonToPoint(jsonRequest):

##################################################################################
#   Example message: 101/3/A79C/89,38.05,.../-103
#                     |  |  |    |  |    |     '--> LoRa RSSI
#                     |  |  |    |  |    |    
#                     |  |  |    |  |    '--> Value n
#                     |  |  |    |  '-------> Value 1
#                     |  |  |    '----------> Node Battery
#                     |  |  |    
#                     |  |  '-----------> Node ID
#                     |  '--------------> Request ID
#                     '-----------------> Status
#
#   Example topic: /matchio/2/data
#                       |   |   '--> Flag para WebHook
#                       |   '------> GateWay ID
#                       '----------> Logo
##################################################################################

    package = jsonRequest['payload'].split('/')
    nodeId = package[2]
    loraRSSI = package[4]


    gatewayId = jsonRequest['topic'].split('/')[2]

    data = package[3].split(',')
    nodeBatery = data[0]
    json_body = [
                    {
                        "measurement": "matchio.data",
                        "tags": {
                            "nodeId" : nodeId,
                            "gatewayId" : gatewayId
                            # "controllerId" : controllerId
                        },
                        "time": str(datetime.datetime.now()),
                        "fields": {
                            "nodeBatery" : int(nodeBatery),
                            "loraRSSI" : int(loraRSSI),
                        }
                    }
                ]
    index=1
    for value in data[1:]:
        field = "value" + str(index)
        json_body[0]['fields'][field] = float(value)
        index += 1
    
    print(json_body)
    return json_body




        