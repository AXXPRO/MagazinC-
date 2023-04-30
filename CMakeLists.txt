cmake_minimum_required(VERSION 3.22.1)
project(MagazinC__)

set(CMAKE_CXX_STANDARD 17)

add_executable(MagazinC__ main.cpp Domain/domain.h Domain/domain.cpp Teste/teste.h Teste/teste.cpp UI/ui.h UI/ui.cpp Service/service.h Service/service.cpp Repository/repo.h Repository/repo.cpp Lista/lista.h Erori/errors.h Validator/validator.h Validator/validator.cpp Undo/undo.h Undo/undo.cpp Undo/undo.cpp)
