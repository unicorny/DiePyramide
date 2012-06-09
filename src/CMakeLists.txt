PROJECT(DiePyramide CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(pyramideSrc main IntroGameState MainGameState MainMenuGameState)
#IF(WIN32)
SET(pyramideSrc ${pongSrc} ../include/main.h ../include/IntroGameState.h ../include/MainGameState.h
                           ../include/MainMenuGameState.h)
#ENDIF(WIN32)

SET(PA ../import/bin ../import/lib)
find_library(SDL_LIB SDL PATHS ${PA})
find_library(DR_ENGINE2_LIB Engine2 PATHS ${PA} REQUIRED)
find_library(DR_CORE2_LIB Core2 PATHS ${PA} REQUIRED)
if(WIN32)
SET(PyramideLibs ${SDL_LIB} ${DR_ENGINE2_LIB} ${DR_CORE2_LIB} glu32 opengl32)
else()
SET(PyramideLibs ${SDL_LIB} Engine2 Core2 GLEW glut)
endif()

ADD_EXECUTABLE(DiePyramide ${pyramideSrc})

TARGET_LINK_LIBRARIES(DiePyramide ${PyramideLibs})

SET_TARGET_PROPERTIES(DiePyramide PROPERTIES EXECUTABLE_OUTPUT_PATH ../)
