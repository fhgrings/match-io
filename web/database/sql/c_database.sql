-- ##### TABELA USUARIOS

DROP TABLE IF EXISTS Role;

CREATE TABLE Role (
    id_role int PRIMARY KEY auto_increment,
    name VARCHAR(20)
);

INSERT INTO Role VALUE(1,"Engenheiro");
INSERT INTO Role VALUE(2,"Tecnico");
INSERT INTO Role VALUE(3,"Gerente");
INSERT INTO Role VALUE(4,"Analista");


DROP TABLE IF EXISTS Permission;

CREATE TABLE Permission (
    id_permission int PRIMARY KEY auto_increment,
    name VARCHAR(20)
);

INSERT INTO Permission VALUE(1,"Total");
INSERT INTO Permission VALUE(2,"Controle");
INSERT INTO Permission VALUE(3,"Acesso");

DROP TABLE IF EXISTS User;

CREATE TABLE User (
    id_user int PRIMARY KEY auto_increment,
    username VARCHAR(30) NOT NULL,
    password VARCHAR(30) NOT NULL,
    first_name VARCHAR(30) NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    email VARCHAR(20) NOT NULL,
    phone VARCHAR(20) NOT NULL,
    id_role int,
    id_permission int,
    

    FOREIGN KEY (id_role) REFERENCES Role (id_role),
    FOREIGN KEY (id_permission) REFERENCES Permission (id_permission)
);


INSERT INTO User VALUE(1,"admin","admin","Admin","Grings","nb_iot@gmail.com","2321231233",1,1);
INSERT INTO User VALUE(2,"user","user","user","Cunha","nb_iot@gmail.com","1231231233",3,1);



-- ##### TABELA DISPOSITVOS

DROP TABLE IF EXISTS Type;

CREATE TABLE Type (
    id_type int PRIMARY KEY auto_increment,
    name VARCHAR(30)
);

INSERT INTO Type value (1, "Temperatura");
INSERT INTO Type value (2, "Umidade");

DROP TABLE IF EXISTS Perfil;

CREATE TABLE Perfil (
    id_perfil int PRIMARY KEY auto_increment,
    name VARCHAR(30),
    refresh_rate int NOT NULL
);
INSERT INTO Perfil value (1, "Aviario", 5);


DROP TABLE IF EXISTS Device;

CREATE TABLE Device (
    id_device int PRIMARY KEY auto_increment,
    name VARCHAR(30) NOT null,
    description VARCHAR(30),
    id_type int,
    id_perfil int,
    
    FOREIGN KEY (id_type) REFERENCES Type (id_type),
    FOREIGN KEY (id_perfil) REFERENCES Perfil (id_perfil)
);

INSERT INTO Device value (1, "Cald-1", "Sensor Caldeira Lateral", 1, 1);
