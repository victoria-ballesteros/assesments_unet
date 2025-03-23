-- Tabla SUCURSALES
CREATE TABLE Sucursales (
    idSuc INT PRIMARY KEY,
    nombreSuc VARCHAR(100) NOT NULL,
    ciudad VARCHAR(100) NOT NULL,
    estado VARCHAR(100) NOT NULL
);

-- Tabla CLIENTES
CREATE TABLE Clientes (
    cedula VARCHAR(20) PRIMARY KEY,
    nombre VARCHAR(100) NOT NULL,
    direccion VARCHAR(255),
    telefono VARCHAR(20),
    correo VARCHAR(100) UNIQUE
);

-- Tabla COBRANZAS
CREATE TABLE Cobranzas (
    idCob INT PRIMARY KEY,
    fechaCobro DATE NOT NULL,
    montoCobro DECIMAL(10,2) NOT NULL CHECK (montoCobro >= 0)
);

-- Tabla SERVICIOS
CREATE TABLE Servicios (
    idServicio INT PRIMARY KEY,
    descServicio VARCHAR(255) NOT NULL,
    fechaInicio DATE NOT NULL,
    fechaFin DATE NOT NULL,
    costoServ DECIMAL(10,2) NOT NULL CHECK (costoServ >= 0),
    responsableServ VARCHAR(100),
    categoriaServicio VARCHAR(50),
    idSuc INT NOT NULL,
    FOREIGN KEY (idSuc) REFERENCES Sucursales(idSuc) ON DELETE CASCADE
);

-- Tabla FACTURAS
CREATE TABLE Facturas (
    idfactura INT PRIMARY KEY,
    fechafactura DATE NOT NULL,
    montoFac DECIMAL(10,2) NOT NULL CHECK (montoFac >= 0),
    idCob INT NOT NULL,
    FOREIGN KEY (idCob) REFERENCES Cobranzas(idCob) ON DELETE CASCADE
);

-- Tabla DETALLE_FACTURA (Intermedia entre Facturas y Servicios)
CREATE TABLE Detalle_Factura (
    idfactura INT NOT NULL,
    idServicio INT NOT NULL,
    cedula VARCHAR(20) NOT NULL,
    PRIMARY KEY (idfactura, idServicio, cedula),
    FOREIGN KEY (idfactura) REFERENCES Facturas(idfactura) ON DELETE CASCADE,
    FOREIGN KEY (idServicio) REFERENCES Servicios(idServicio) ON DELETE CASCADE,
    FOREIGN KEY (cedula) REFERENCES Clientes(cedula) ON DELETE CASCADE
);
