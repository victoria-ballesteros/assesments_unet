#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <stdlib.h>
#include <limits>
#include <locale.h>
#include <fstream>
#include <cstring>

#include "..\helpers.h"

using namespace std;

helpers helper;

class registro
{

public:
    int auxPosicionProducto = 0, auxPosicionCliente = 0, auxPosicionCompra = 0, auxPosicionFactura = 0, auxPosicionProveedor = 0;
    struct ProductosAgotados
    {
        int stock = -1;
        int stock_min = -1;
        int id_proveedor = -1;
    };
    
    struct Producto
    {
        int id = -1;
        int id_proveedor = -1;
        int stock = -1;
        float precio = -1;
        char description[45] = "";
        int stock_min = -1;
    };

    struct Cliente
    {
        int id = -1;
        char nombre[45] = "";
        char direccion[70] = "";
        char telefono[18] = "";
    };

    struct Compra
    {
        int id = -1;
        int id_producto = -1;
        int id_factura = -1;
        int cantidad = -1;
    };

    struct Factura
    {
        int id = -1;
        int id_cliente = -1;
        char fecha[12] = "";
    };

    struct Proveedor
    {
        int id = -1;
        char nombre[45] = "";
        char telefono[30] = "";
    };

    struct Almacen
    {
        string nombreArchivo = "";
    };

    Producto getProducto(int _id)
    {
        fstream e("database/Producto.bin", ios::out | ios::in | ios::binary);
        int i = 0;
        Producto auxiliar;
        if (e.is_open())
        {
            int cant = cantidadRegistro("database/Producto.bin", sizeof(Producto));
            for (i = 0; i < cant; i++)
            {
                e.seekg(i * sizeof(Producto));
                e.read((char *)&auxiliar, sizeof(Producto));
                if (auxiliar.id == _id)
                {
                    auxPosicionProducto = i;
                    return auxiliar;
                }
            }
            auxiliar.id = -1;
            return auxiliar;
        }
    }

    Cliente getCliente(int _id)
    {
        fstream e("database/Cliente.bin", ios::out | ios::in | ios::binary);
        int i = 0;
        Cliente auxiliar;
        if (e.is_open())
        {
            int cant = cantidadRegistro("database/Cliente.bin", sizeof(Cliente));
            for (i = 0; i < cant; i++)
            {
                e.seekg(i * sizeof(Cliente));
                e.read((char *)&auxiliar, sizeof(Cliente));
                if (auxiliar.id == _id)
                {
                    auxPosicionCliente = i;
                    return auxiliar;
                }
            }
            auxiliar.id = -1;
            return auxiliar;
        }
    }

    Compra getCompra(int _id)
    {
        fstream e("database/Compra.bin", ios::out | ios::in | ios::binary);
        int i = 0;
        Compra auxiliar;
        if (e.is_open())
        {
            int cant = cantidadRegistro("database/Compra.bin", sizeof(Compra));
            for (i = 0; i < cant; i++)
            {
                e.seekg(i * sizeof(Compra));
                e.read((char *)&auxiliar, sizeof(Compra));
                if (auxiliar.id == _id)
                {
                    auxPosicionCompra = i;
                    return auxiliar;
                }
            }
            auxiliar.id = -1;
            return auxiliar;
        }
    }

    Factura getFactura(int _id)
    {
        fstream e("database/Factura.bin", ios::out | ios::in | ios::binary);
        int i = 0;
        Factura auxiliar;
        if (e.is_open())
        {
            int cant = cantidadRegistro("database/Factura.bin", sizeof(Factura));
            for (i = 0; i < cant; i++)
            {
                e.seekg(i * sizeof(Factura));
                e.read((char *)&auxiliar, sizeof(Factura));
                if (auxiliar.id == _id)
                {
                    auxPosicionFactura = i;
                    return auxiliar;
                }
            }
            auxiliar.id = -1;
            return auxiliar;
        }
    }

    Proveedor getProveedor(int _id)
    {
        fstream e("database/Proveedor.bin", ios::out | ios::in | ios::binary);
        int i = 0;
        Proveedor auxiliar;
        if (e.is_open())
        {
            int cant = cantidadRegistro("database/Proveedor.bin", sizeof(Proveedor));
            for (i = 0; i < cant; i++)
            {
                e.seekg(i * sizeof(Proveedor));
                e.read((char *)&auxiliar, sizeof(Proveedor));
                if (auxiliar.id == _id)
                {
                    auxPosicionProveedor = i;
                    return auxiliar;
                }
            }
            auxiliar.id = -1;
            return auxiliar;
        }
    }

    int cantidadRegistro(string dir, size_t sizeOf)
    {
        ifstream archivo(dir, ios::binary | ios::ate);
        if (archivo.fail())
        {
            cerr << "No se pudo abrir el archivo.\n";
            archivo.close();
            return -1;
        }
        streamsize size = archivo.tellg();
        archivo.close();
        int cantidadDeRegistros = size / sizeOf;
        return cantidadDeRegistros;
    }

    void modificarCantidadProducto(int _id, int disminucion)
    {
        Producto modelo;
        fstream archivo("database/Producto.bin", ios::out | ios::in | ios::binary);
        modelo = getProducto(_id);
        modelo.stock -= disminucion;
        if (archivo.fail())
        {
            cerr << "No se pudo abrir el archivo para escritura.\n";
        }
        else
        {
            archivo.seekg(auxPosicionProducto * sizeof(Producto));
            archivo.write((char *)&modelo, sizeof(Producto));
            archivo.close();
        }
    }
    void listarProductos(string dir)
    {
        std::fstream archivo(dir, std::ios::binary | std::ios::in | std::ios::out);
        if (archivo.fail())
        {
            cerr << "No se pudo abrir el archivo.\n";
            system("pause");
            return;
        }
        Producto producto;
        while (archivo.read((char *)&producto, sizeof(Producto)))
        {
            std::cout << '\n';
            std::cout << "ID--------------------: " << producto.id << "\n";
            std::cout << "DESCRIPCION-----------: " << producto.description << "\n";
            std::cout << "STOCK-----------------: " << producto.stock << "\n";
            std::cout << "____________________________________________________________" << '\n';
            std::cout << '\n';
        }
        archivo.close();
    }
};

#endif