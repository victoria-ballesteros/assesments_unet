-- Tabla PRESUPUESTOS
CREATE TABLE Presupuestos (
    N_pre INT PRIMARY KEY,
    Fecha_pre DATE NOT NULL
);

-- Tabla PRODUCTOS
CREATE TABLE Productos (
    Codigo_prod INT PRIMARY KEY,
    Descrip VARCHAR(255) NOT NULL,
    Precio DECIMAL(10,2) NOT NULL CHECK (Precio > 0)
);

-- Tabla PEDIDOS
CREATE TABLE Pedidos (
    N_ped INT PRIMARY KEY,
    Fecha_ped DATE NOT NULL,
    Vendedor VARCHAR(100) NOT NULL,
    N_pre INT NULL,
    FOREIGN KEY (N_pre) REFERENCES Presupuestos(N_pre) ON DELETE SET NULL
);

-- Tabla PEDIDO_ITEMS (relación entre Pedidos y Productos)
CREATE TABLE Pedido_items (
    N_ped INT NOT NULL,
    Codigo_prod INT NOT NULL,
    Cantidad_pedida INT NOT NULL CHECK (Cantidad_pedida > 0),
    PRIMARY KEY (N_ped, Codigo_prod),
    FOREIGN KEY (N_ped) REFERENCES Pedidos(N_ped) ON DELETE CASCADE,
    FOREIGN KEY (Codigo_prod) REFERENCES Productos(Codigo_prod) ON DELETE CASCADE
);
