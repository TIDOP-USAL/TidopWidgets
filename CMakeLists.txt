##########################################################################
#                                                                        #
# Copyright 2024 by Tidop Research Group <daguilera@usal.es>             #
#                                                                        #
# This file is part of TidopWidgets                                      #
#                                                                        #
# TidopWidgets is free software: you can redistribute it and/or modify   #
# it under the terms of the GNU General Public License as published by   #
# the Free Software Foundation, either version 3 of the License, or (at  #
# your option) any later version.                                        #
#                                                                        #
# TidopWidgets is distributed in the hope that it will be useful, but    #
# WITHOUT ANY WARRANTY; without even the implied warranty of             #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                   #
# See the GNU General Public License for more details.                   #
#                                                                        #
# You should have received a copy of the GNU General Public License      #
# along with TidopWidgets.  If not, see <http://www.gnu.org/licenses/>.  #
#                                                                        #
# https://spdx.org/licenses/GPL-3.0-or-later.html                        #
#                                                                        #
##########################################################################

cmake_minimum_required(VERSION 3.14)

project(TidopWidgets 
        VERSION 0.0.1
        DESCRIPTION "Tidop Widgets"
        HOMEPAGE_URL "http://tidop.usal.es"
        LANGUAGES CXX)
		
message(STATUS "\n${PROJECT_NAME} ${TidopWidgets_VERSION}")
message(STATUS ${TidopWidgets_DESCRIPTION})
message(STATUS ${TidopWidgets_HOMEPAGE_URL})		


# Configuration 

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CONFIGURATION_TYPES Release;Debug)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Buscar Qt (asegúrate de tener Qt instalado)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Añadir los archivos del widget
set(WIDGET_SOURCES
    src/TWidgets/TestWidget/TestWidget.cpp
)

set(WIDGET_HEADERS
    src/TWidgets/TidopWidget.h
    src/TWidgets/JPEGWidget/JPEGWidget
)

# Ejecutable principal
add_executable(TestWidget main.cpp ${WIDGET_SOURCES} ${WIDGET_HEADERS})

# Vincular bibliotecas de Qt
target_link_libraries(TestWidget PRIVATE Qt5::Widgets)

# Incluir directorios
target_include_directories(TestWidget PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
