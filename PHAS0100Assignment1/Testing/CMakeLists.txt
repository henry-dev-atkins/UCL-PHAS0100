#/*============================================================================
#
#  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.
#
#  Copyright (c) University College London (UCL). All rights reserved.
#
#  This software is distributed WITHOUT ANY WARRANTY; without even
#  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
#  PURPOSE.
#
#  See LICENSE.txt in the top level directory for details.
#
#============================================================================*/

set(DATA_DIR ${CMAKE_SOURCE_DIR}/Testing/Data)
set(TMP_DIR ${CMAKE_BINARY_DIR}/Testing/Temporary)

set(TEST_CASES
golGrid_Initialisation
golEmpty_Grid_Editing
golRandom_Initial_Testing
golIs_Random_Grid_Creating_Correct_Alive_Number
golIs_Random_Grid_Initialisation_Correct_Size
golIs_Oscillator_Oscillating
golIs_Count_Correct_Boundary_Condition_Corners
golIs_Count_Correct_Boundary_Condition_Sides

)

foreach(_test_case ${TEST_CASES})
  add_executable(${_test_case} ${_test_case}.cpp golCatchMain.cpp)
  target_link_libraries(${_test_case} ${PHAS0100ASSIGNMENT1_LIBRARIES} ${ALL_THIRD_PARTY_LIBRARIES})
endforeach()

# Adding tests is done outside the above loop,
# as each test will need different arguments.

##################################################################################################
# Dont forget its:  add_test(<test name (globally unique) > <exe name> <argument1> <argument2>
##################################################################################################

add_test(Grid_Initialisation ${EXECUTABLE_OUTPUT_PATH}/golGrid_Initialisation)
add_test(Empty_Grid_Editing ${EXECUTABLE_OUTPUT_PATH}/golEmpty_Grid_Editing)
add_test(Is_Random_Grid_Initialisation_Unique ${EXECUTABLE_OUTPUT_PATH}/golRandom_Initial_Testing)
add_test(Is_Random_Grid_Creating_Correct_Alive_Number ${EXECUTABLE_OUTPUT_PATH}/golIs_Random_Grid_Creating_Correct_Alive_Number)

add_test(Is_Random_Grid_Initialisation_Correct_Size ${EXECUTABLE_OUTPUT_PATH}/golIs_Random_Grid_Initialisation_Correct_Size)
add_test(Is_Oscillator_Oscillating ${EXECUTABLE_OUTPUT_PATH}/golIs_Oscillator_Oscillating)
add_test(Is_Count_Correct_Boundary_Condition_Corners ${EXECUTABLE_OUTPUT_PATH}/golIs_Count_Correct_Boundary_Condition_Corners)
add_test(Is_Count_Correct_Boundary_Condition_Sides ${EXECUTABLE_OUTPUT_PATH}/golIs_Count_Correct_Boundary_Condition_Sides)

