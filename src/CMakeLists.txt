##
# Software License Agreement (BSD License)
#
#  Copyright (c) 2014, 2020 CNRS-LAAS
#  Author: Florent Lamiraux
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#   * Neither the name of CNRS-LAAS. nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
#  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
#  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
#  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
#  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
#  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
#  POSSIBILITY OF SUCH DAMAGE.

# --------------------------------------------------------------------
# Sources
# --------------------------------------------------------------------
set(LIBRARY_NAME ${PROJECT_NAME})

set(${LIBRARY_NAME}_SOURCES
  collision.cpp
  distance_func_matrix.cpp
  collision_data.cpp
  collision_node.cpp
  collision_object.cpp
  BV/RSS.cpp
  BV/AABB.cpp
  BV/kIOS.cpp
  BV/kDOP.cpp
  BV/OBBRSS.cpp
  BV/OBB.cpp
  narrowphase/narrowphase.cpp
  narrowphase/gjk.cpp
  narrowphase/details.h
  shape/convex.cpp
  shape/geometric_shapes.cpp
  shape/geometric_shapes_utility.cpp
  distance/box_halfspace.cpp
  distance/box_plane.cpp
  distance/box_sphere.cpp
  distance/capsule_capsule.cpp
  distance/capsule_halfspace.cpp
  distance/capsule_plane.cpp
  distance/cone_halfspace.cpp
  distance/cone_plane.cpp
  distance/cylinder_halfspace.cpp
  distance/cylinder_plane.cpp
  distance/sphere_sphere.cpp
  distance/sphere_cylinder.cpp
  distance/sphere_halfspace.cpp
  distance/sphere_plane.cpp
  distance/convex_halfspace.cpp
  distance/triangle_halfspace.cpp
  intersect.cpp
  math/transform.cpp
  traversal/traversal_recurse.cpp
  distance.cpp
  BVH/BVH_utility.cpp
  BVH/BV_fitter.cpp
  BVH/BVH_model.cpp
  BVH/BV_splitter.cpp
  collision_func_matrix.cpp
  collision_utility.cpp
  mesh_loader/assimp.cpp
  mesh_loader/loader.cpp
)

# --------------------------------------------------------------------
# Optional QHull support
# --------------------------------------------------------------------
if(HPP_FCL_HAS_QHULL)
  set(
    libqhullcpp_HEADERS
    ${Qhullcpp_PREFIX}/libqhullcpp/Coordinates.h
    ${Qhullcpp_PREFIX}/libqhullcpp/functionObjects.h
    ${Qhullcpp_PREFIX}/libqhullcpp/PointCoordinates.h
    ${Qhullcpp_PREFIX}/libqhullcpp/Qhull.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullError.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacet.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacetList.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacetSet.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullHyperplane.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullIterator.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullLinkedList.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPoint.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPoints.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPointSet.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullQh.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullRidge.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullSet.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullSets.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullStat.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullVertex.h
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullVertexSet.h
    ${Qhullcpp_PREFIX}/libqhullcpp/RboxPoints.h
    ${Qhullcpp_PREFIX}/libqhullcpp/RoadError.h
    ${Qhullcpp_PREFIX}/libqhullcpp/RoadLogEvent.h
  )

  set(
    libqhullcpp_SOURCES
    ${Qhullcpp_PREFIX}/libqhullcpp/Coordinates.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/PointCoordinates.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/Qhull.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacet.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacetList.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullFacetSet.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullHyperplane.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPoint.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPointSet.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullPoints.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullQh.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullRidge.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullSet.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullStat.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullVertex.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/QhullVertexSet.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/RboxPoints.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/RoadError.cpp
    ${Qhullcpp_PREFIX}/libqhullcpp/RoadLogEvent.cpp
    ${libqhullcpp_HEADERS}
  )

  # Append QHull sources into main library sources
  list(APPEND ${LIBRARY_NAME}_SOURCES ${libqhullcpp_SOURCES})
endif()

# --------------------------------------------------------------------
# Public headers (top-level CMakeLists.txt defines ${PROJECT_NAME}_HEADERS)
# --------------------------------------------------------------------
set(PROJECT_HEADERS_FULL_PATH)
foreach(header ${${PROJECT_NAME}_HEADERS})
  list(APPEND PROJECT_HEADERS_FULL_PATH ${PROJECT_SOURCE_DIR}/${header})
endforeach()
list(APPEND PROJECT_HEADERS_FULL_PATH
  ${PROJECT_BINARY_DIR}/include/hpp/fcl/config.hh
)

# --------------------------------------------------------------------
# Library type: static on MSVC, shared otherwise
# --------------------------------------------------------------------
set(HPP_FCL_LIB_TYPE SHARED)
#if(MSVC)
#  # On Windows we prefer a static lib for easier CRT handling
#  set(HPP_FCL_LIB_TYPE SHARED)
#endif()

add_library(${LIBRARY_NAME}
  ${HPP_FCL_LIB_TYPE}
  ${PROJECT_HEADERS_FULL_PATH}
  ${${LIBRARY_NAME}_SOURCES}
)

# IDE sources and headers sorting (macros from hpp.cmake)
ADD_SOURCE_GROUP(${LIBRARY_NAME}_SOURCES)
ADD_HEADER_GROUP(PROJECT_HEADERS_FULL_PATH)

# --------------------------------------------------------------------
# Include directories / compile definitions
# --------------------------------------------------------------------

# Eigen: vendored, provided by top-level CMakeLists.txt
target_include_directories(${LIBRARY_NAME}
  SYSTEM PUBLIC
    ${EIGEN3_INCLUDE_DIR}
)

# Build- / install-interface include dirs for public headers
target_include_directories(${LIBRARY_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Optional QHull
if(HPP_FCL_HAS_QHULL)
  target_compile_definitions(${LIBRARY_NAME} PRIVATE -DHPP_FCL_HAS_QHULL)
  target_include_directories(${LIBRARY_NAME} SYSTEM PRIVATE
    ${Qhull_r_INCLUDE_DIR}
    ${Qhullcpp_PREFIX}
  )
  target_link_libraries(${LIBRARY_NAME} PRIVATE "${Qhull_r_LIBRARY}")
endif()

# Optional Octomap (currently disabled in top-level, but keep for future)
if(octomap_FOUND)
  target_include_directories(${LIBRARY_NAME} SYSTEM PUBLIC ${OCTOMAP_INCLUDE_DIRS})
  target_link_libraries(${LIBRARY_NAME} PUBLIC ${OCTOMAP_LIBRARIES})
  target_compile_definitions(${LIBRARY_NAME} PUBLIC
    -DHPP_FCL_HAVE_OCTOMAP
    -DOCTOMAP_MAJOR_VERSION=${OCTOMAP_MAJOR_VERSION}
    -DOCTOMAP_MINOR_VERSION=${OCTOMAP_MINOR_VERSION}
    -DOCTOMAP_PATCH_VERSION=${OCTOMAP_PATCH_VERSION}
  )
endif()

# --------------------------------------------------------------------
# Install
# --------------------------------------------------------------------
install(TARGETS ${LIBRARY_NAME}
  EXPORT ${TARGETS_EXPORT_NAME}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  INCLUDES      DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}
  LIBRARY       DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  ARCHIVE       DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
  RUNTIME       DESTINATION ${CMAKE_INSTALL_FULL_BINDIR}
)
