-- DROP TABLE IF EXISTS Acl;
-- DROP TABLE IF EXISTS Resources;
-- DROP TABLE IF EXISTS Entity;

CREATE TABLE IF NOT EXISTS Entity
(
    id INT PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Resources
(
    resour VARCHAR(255) PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Acl
(
    id_en INT,
    res VARCHAR(255) NOT NULL,
    access VARCHAR(16) NOT NULL,
    CONSTRAINT fk_resource
      FOREIGN KEY(res) 
	    REFERENCES Resources(resour)
        ON DELETE CASCADE,
    CONSTRAINT fk_entity
      FOREIGN KEY(id_en) 
	    REFERENCES Entity(id)
        ON DELETE CASCADE
);