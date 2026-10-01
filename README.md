\# 🗝️ Sistema de Gestión para Cerrajería (C++)



!\[Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)

!\[Paradigm](https://img.shields.io/badge/Paradigm-POO-green.svg)

!\[Persistence](https://img.shields.io/badge/Persistence-Archivos%20Binarios-orange.svg)

!\[Status](https://img.shields.io/badge/Status-Completado-brightgreen.svg)



\*\*SistemaCerrajeria\*\* es una aplicación de escritorio interactiva en consola desarrollada en C++ bajo el paradigma de \*\*Programación Orientada a Objetos (POO)\*\*. Está diseñada para la automatización de procesos clave en un negocio de cerrajería, gestionando productos, servicios técnicos, ventas, compras a proveedores e informes ejecutivos.



\---



\## 📐 Arquitectura del Proyecto



El sistema aplica una \*\*arquitectura por capas\*\* desacoplada para garantizar la escalabilidad, mantenibilidad y separación de responsabilidades:



```text

SistemaCerrajeriaV3/

├── include/           # Declaraciones de clases (.h)

│   ├── Archivos/      # Persistencia de datos en disco (.dat)

│   ├── Managers/      # Reglas de negocio y orquestación

│   ├── Menus/         # Interfaz de usuario interactiva

│   ├── Modelo/        # Entidades del dominio (POO)

│   └── rlutil.h       # Librería de apoyo para UI en consola

├── src/               # Implementación de métodos (.cpp)

└── main.cpp           # Punto de entrada de la aplicación

