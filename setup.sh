#!/bin/bash
set -e  

echo "=== Установка системных зависимостей (требуется sudo) ==="
#sudo apt update
sudo apt install -y build-essential cmake git gnuplot libglfw3-dev libjpeg-dev libpng-dev
sudo apt install libtiff-dev

echo "=== Подготовка папки для Matplot++ ==="
mkdir -p libs
cd libs

if [ ! -d "matplotplusplus" ]; then
    echo "=== Клонирование Matplot++ ==="
    git clone https://github.com/alandefreitas/matplotplusplus.git
    cd matplotplusplus
else
    echo "Matplot++ уже есть, обновляем (при необходимости)"
    cd matplotplusplus
    git pull
fi

echo "=== Сборка Matplot++ (статическая библиотека) ==="
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release \
         -DMATPLOTPP_BUILD_EXAMPLES=OFF \
         -DMATPLOTPP_BUILD_TESTS=OFF \
         -DCMAKE_INSTALL_PREFIX=../install
make -j$(nproc)
make install

cd ../..   
echo "=== Matplot++ установлен в libs/matplotplusplus/install ==="

cd ..      
echo "=== Всё готово. Теперь выполните 'make' для сборки программы ==="