#include <matplot/matplot.h>
#include <library/stb_image.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>

namespace mp = matplot;

#ifndef VIEW_H
#define VIEW_H

// ----------------------------------------------------------------------
// Вспомогательные функции для чтения way-файлов (разделитель ';')
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
// Чтение координат из path-файла (Формат: row;col)
// ----------------------------------------------------------------------
std::vector<std::pair<int, int>> read_way_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("⛔ Cannot open way file: " + filename);
    }

    std::vector<std::pair<int, int>> points;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string token;
        std::vector<int> coords;

        // Парсим строку с разделителем ';'
        while (std::getline(iss, token, ';')) {
            token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
            if (!token.empty()) {
                coords.push_back(std::stoi(token));
            }
        }

        if (coords.size() >= 2) {
            points.emplace_back(coords[0] - 1, coords[1] - 1); // Переход в 0-базис
        }
    }
    return points;
}

// ----------------------------------------------------------------------
// Загрузка картинки в оттенках серого (Matplot++ работает с double)
// ----------------------------------------------------------------------
std::vector<std::vector<double>> load_map(const std::string& file_path, double scale = 1.0) {
    int width, height, channels;
    unsigned char* img = stbi_load(file_path.c_str(), &width, &height, &channels, 0);
    if (!img) {
        throw std::runtime_error("⛔ Failed to load image: " + file_path);
    }

    // Используем стандартный C++ контейнер для данных
    std::vector<std::vector<double>> result(height, std::vector<double>(width));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            unsigned char* pixel = img + (y * width + x) * channels;
            double gray;
            if (channels >= 3) {
                // Формула перевода в оттенки серого (Rec. 601)
                gray = 0.299 * pixel[0] + 0.587 * pixel[1] + 0.114 * pixel[2];
            } else {
                gray = pixel[0];
            }
            result[y][x] = gray * scale;
        }
    }
    stbi_image_free(img);
    return result;
}

// ----------------------------------------------------------------------
// Отрисовка основной карты (Цвет изменен на "blue", т.к. "deep" — устарел)
// ----------------------------------------------------------------------
void draw_map(const std::string& map_file_path, double scale = 1.0) {
    auto Z = load_map(map_file_path, scale);   // матрица высот
    size_t rows = Z.size();
    size_t cols = rows ? Z[0].size() : 0;

    // Координатные векторы
    std::vector<double> x_coords(cols);
    std::vector<double> y_coords(rows);
    for (size_t i = 0; i < cols; ++i) x_coords[i] = static_cast<double>(i);
    for (size_t i = 0; i < rows; ++i) y_coords[i] = static_cast<double>(i);

    // Создаём двумерные сетки X и Y
    auto [X, Y] = mp::meshgrid(x_coords, y_coords);

    // Теперь все аргументы – двумерные матрицы
    mp::surf(X, Y, Z);
    mp::colormap(mp::palette::parula());  // или "viridis()", "blue()"
    mp::xlabel("X (пиксели)");
    mp::ylabel("Y (пиксели)");
    mp::zlabel("Высота");
}
// ----------------------------------------------------------------------
// Добавление путей поверх карты
// ----------------------------------------------------------------------
void draw_add_way(const std::string& way_file_path, const std::string& map_file_path,
                  double offset = 1.0, double scale = 1.0,
                  const std::string& color = "red", double linewidth = 1.0) {
    auto map_data = load_map(map_file_path, scale);
    auto way_points = read_way_file(way_file_path);

    std::vector<double> xs, ys, zs;
    for (const auto& pt : way_points) {
        int row = pt.first;
        int col = pt.second;
        if (row >= 0 && row < static_cast<int>(map_data.size()) &&
            col >= 0 && col < static_cast<int>(map_data[0].size())) {
            // Высота в этой точке + оффсет
            double z = map_data[row][col] + offset;
            xs.push_back(static_cast<double>(col));
            ys.push_back(static_cast<double>(row));
            zs.push_back(z);
        }
    }

    mp::hold(mp::on);
    //mp::plot3(xs, ys, zs)->line_width(linewidth).color(color);
    mp::plot3(ys, xs, zs)->line_width(linewidth).color(color);
    mp::hold(mp::off);
}
// ----------------------------------------------------------------------
// Главная функция (пример использования)
// ----------------------------------------------------------------------

void view(std::string map, std::string way){
    try {
        std::string map_file_path = map;
        double scale = 10.0;

        std::string way_file_path   = way;

       // std::string step_map_path = "Kyrsova/map_step1.obj";

        draw_map(map_file_path, scale);

        draw_add_way(way_file_path,   map_file_path, 2.0, scale, "yellow", 4.0);

        //draw_step_map(step_map_path);

        mp::show();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

#endif