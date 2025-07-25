# MATCH IO: UM SISTEMA IOT LPWAN DE UTILIZAÇÃO SIMPLIFICADA PARA O MONITORAMENTO DE GRANDEZAS FÍSICAS

A Computing Engineer's Dissertation Repository developed by Felipe Grings.

Read the entire paper, and take a look at: [Full Paper](./match-io_paper_Felipe-Grings.pdf)

Video Presentation: [Youtube Link](https://www.youtube.com/watch?v=z5Odm_62vqk)


## Abstract
The main goal of this paper is to carry out a comprehensive study about the concept of Internet of Things and technologies that surround it. The paper explores several architectures aimed at optimizing the concept of IoT used for long range communication, aiming at a system that is simple to install for the end user. A bibliographical review on protocols, architectures, distributions is presented with components and the importance for the small farmer and industry of monitor their environment variables to optimize their processes. From the perception of a lack availability of products that consider the usability and installation, using these technologies of accessible to businesses and farmers who do not have high financial resources for such implementation. Faced with this problem, the proposal of the paper is to develop a prototype that delivers a product to the final consumer. End-to-End, no third-party setup required and easy to install, independent of Internet connection, and ready to use On-Premise or Cloud environment. A development methodology is used in stages, where the hardware and firmware product, the high level software product such as database, communication services HTTP and user interfaces, as well as scripting for the infrastructure run as code. Thus, technologies, such as: LoRa, used to long-distance communication; MQTT for messaging services; C/C++/Lua for SoC firmware; Python, Flask and Vue for high-level services; among other technologies to simplify the development, as Bash, Docker and Docker Swarm for infrastructure provisioning. This makes it possible to implement the prototype for monitoring of physical quantities, as well as transmission to a database for future analysis and understanding of the environment. To prove the efficiency and the reliability of the system, continuous tests were carried out over 6 months in real use situation in a aviary environment. The results obtained showed the rate of messages sent with real success over 84.56% ideal and an average approval of 4 out of 5 among users in usability and implementation of the system. These tests prove the correct working of the proposed system.


### Software Requirements

Python3

AVR-GCC Compiler

Docker

Docker Swarm

PlatformIO

### Hardware Requirements

HELTEC LoRa ESP32 V2

Transdutor BME380

## Install

#### Software

```bash
git clone ...
cd match-io/web
./run.sh
```

#### Hardware

Import projects on Platform IO and deploy to microcontrolers 

## Results

### Architecture
![high-architecture](./imgs/high-architecture.png)

![detailed-architecture](./imgs/detailed-architecture.png)

![services-architecture](./imgs/services-architecture.png)

### Hardware
![Arduino PCB](./imgs/arduino-pcb.png)

![pcb-building](./imgs/pcb-building.jpg)

![pcb-back](./imgs/pcb-back.jpg)

![pcb-front](./imgs/pcb-front.jpg)

![node-case](./imgs/node-case.png)

### Final Results
![control-panel](./imgs/control-panel.png)

![dashboard](./imgs/dashboard.png)

### Authors and acknowledgment

https://github.com/fhgrings

### License

MIT
