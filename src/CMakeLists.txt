PROJECT(DiePyramide CXX)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(pyramideSrc main IntroGameState MainGameState MainMenuGameState Sprite SpriteManager Entity)
#IF(WIN32)
SET(pyramideSrc ${pyramideSrc} ../include/main.h ../include/IntroGameState.h ../include/MainGameState.h
                           ../include/MainMenuGameState.h ../include/Sprite.h ../include/SpriteManager.h
						   ../include/Entity.h)
#ENDIF(WIN32)

SET(PA ../import/bin ../import/lib)
find_library(SDL_LIB SDL PATHS ${PA})
find_library(DR_ENGINE2_LIB DREngine2 PATHS ${PA} REQUIRED)
find_library(DR_CORE2_LIB DRCore2 PATHS ${PA} REQUIRED)
if(WIN32)
SET(pyramideLibs ${SDL_LIB} ${DR_ENGINE2_LIB} ${DR_CORE2_LIB} glu32 opengl32)
else()
SET(pyramideLibs ${SDL_LIB} Engine2 Core2 GLEW glut)
endif()

ADD_EXECUTABLE(DiePyramide ${pyramideSrc})

TARGET_LINK_LIBRARIES(DiePyramide ${pyramideLibs})

SET_TARGET_PROPERTIES(DiePyramide PROPERTIES EXECUTABLE_OUTPUT_PATH ../)
