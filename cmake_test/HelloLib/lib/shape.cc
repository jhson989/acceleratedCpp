#include "shape.hpp"
#include <iostream>
#include <thread>

Rectangle::Rectangle(int width, int height) : width_(width), height_(height) {}

int Rectangle::GetSize() const {

  std::thread t ([this]() {std::cout << "Calculate .." << std::endl; });
  t.join ();

  // 직사각형의 넓이를 리턴한다.
  return width_ * height_;
}