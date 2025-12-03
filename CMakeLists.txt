#
# Software License Agreement (BSD License)
#
#  Copyright (c) 2014-2020 CNRS-LAAS, INRIA
#  Author: Florent Lamiraux, Joseph Mirabel
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

cmake_minimum_required(VERSION 3.16...3.31)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CXX_DISABLE_WERROR TRUE)

set(PROJECT_NAME hpp-fcl)
set(PROJECT_DESCRIPTION
  "HPP fork of FCL -- The Flexible Collision Library"
  )
set(PROJECT_USE_CMAKE_EXPORT FALSE)

# Do not support CMake older than 2.8.12
cmake_policy(SET CMP0022 NEW)
set(PROJECT_USE_KEYWORD_LINK_LIBRARIES TRUE)
set(DOXYGEN_USE_TEMPLATE_CSS TRUE)

# Check if the submodule cmake have been initialized
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/cmake/base.cmake")
  message(FATAL_ERROR "\nPlease run the following command first:\ngit submodule update --init\n")
endif()

# --------------------------------------------------------------------
# Eigen: Windows-only, vendored, no find_package(Eigen3) anymore
# --------------------------------------------------------------------
set(EIGEN3_VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor/eigen")

if (EXISTS "${EIGEN3_VENDOR_DIR}/Eigen/Dense")
    message(STATUS "Using vendored Eigen headers in ${EIGEN3_VENDOR_DIR}")

    add_library(eigen3_vendor INTERFACE)
    target_include_directories(eigen3_vendor
        INTERFACE
            "${EIGEN3_VENDOR_DIR}"
    )

    # Modern imported target name expected by most code
    add_library(Eigen3::Eigen ALIAS eigen3_vendor)

    # Old-style variables some macros might check
    set(EIGEN3_INCLUDE_DIR "${EIGEN3_VENDOR_DIR}")
    set(Eigen3_FOUND TRUE)
    set(EIGEN3_FOUND TRUE)
else()
    message(FATAL_ERROR
        "Eigen3 not found: vendored headers at "
        "${EIGEN3_VENDOR_DIR}/Eigen/Dense"
    )
endif()

# --------------------------------------------------------------------
# Project infrastructure
# --------------------------------------------------------------------
#include(cmake/boost.cmake)
include(cmake/python.cmake)
include(cmake/hpp.cmake)
# include(cmake/apple.cmake)  # <-- removed for Windows-only fork
include(cmake/ide.cmake)

set(CMAKE_MODULE_PATH
  ${CMAKE_SOURCE_DIR}/cmake-modules/
  ${CMAKE_MODULE_PATH})

# Apple-specific policy – not needed on Windows
# APPLY_DEFAULT_APPLE_CONFIGURATION()  # <-- removed

option(BUILD_PYTHON_INTERFACE "Build the python bindings" OFF)

COMPUTE_PROJECT_ARGS(PROJECT_ARGS LANGUAGES CXX)
project(${PROJECT_NAME} ${PROJECT_ARGS})

# --------------------------------------------------------------------
# Dependencies
# --------------------------------------------------------------------

# We already wired Eigen above; do NOT call the hpp "ADD_PROJECT_DEPENDENCY(Eigen3 ...)"
# which would try to run find_package(Eigen3) and blow up on Windows.
# ADD_PROJECT_DEPENDENCY(Eigen3 REQUIRED PKG_CONFIG_REQUIRES "eigen3 >= 3.0.0")

# Required dependencies
# For this Windows-only fork, skip the whole Boost dependency mechanism.
# If something later really needs Boost, we can wire it manually or via vcpkg.

# SET_BOOST_DEFAULT_OPTIONS()
# EXPORT_BOOST_DEFAULT_OPTIONS()
# ADD_PROJECT_DEPENDENCY(Boost REQUIRED)



# Optional dependencies
# Disable octomap/pkg-config on Windows for now
# ADD_PROJECT_DEPENDENCY(octomap PKG_CONFIG_REQUIRES "octomap >= 1.6")
# if(octomap_FOUND)
#   set(HPP_FCL_HAVE_OCTOMAP TRUE)
#   string(REPLACE "." ";" VERSION_LIST ${octomap_VERSION})
#   list(GET VERSION_LIST 0 OCTOMAP_MAJOR_VERSION)
#   list(GET VERSION_LIST 1 OCTOMAP_MINOR_VERSION)
#   list(GET VERSION_LIST 2 OCTOMAP_PATCH_VERSION)
#   message(STATUS "FCL uses Octomap")
# else()
#   set(HPP_FCL_HAVE_OCTOMAP FALSE)
#   message(STATUS "FCL does not use Octomap")
# endif()
set(HPP_FCL_HAVE_OCTOMAP FALSE)
message(STATUS "FCL does not use Octomap (Windows-only fork)")

option(HPP_FCL_HAS_QHULL "use qhull library to compute convex hulls." FALSE)
if(HPP_FCL_HAS_QHULL)
  if(DEFINED CMAKE_CXX_STANDARD AND CMAKE_CXX_STANDARD EQUAL 98)
    message(FATAL_ERROR "Cannot use qhull library with C++ < 11.\nYou may add -DCMAKE_CXX_STANDARD=11")
  endif()
  file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/third-parties)
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/third-parties/qhull/src/libqhullcpp
    ${CMAKE_CURRENT_BINARY_DIR}/third-parties/libqhullcpp
    )
  set(Qhullcpp_PREFIX ${CMAKE_BINARY_DIR}/third-parties)
  find_path(Qhull_r_INCLUDE_DIR
    NAMES libqhull_r/libqhull_r.h
    PATHS ${Qhull_PREFIX}
    )
  find_library(Qhull_r_LIBRARY
    NAMES libqhull_r.so
    PATHS ${Qhull_PREFIX}
    )
endif()

find_package(assimp REQUIRED)

set(${PROJECT_NAME}_HEADERS
  include/hpp/fcl/collision_data.h
  include/hpp/fcl/BV/kIOS.h
  include/hpp/fcl/BV/BV.h
  include/hpp/fcl/BV/RSS.h
  include/hpp/fcl/BV/OBBRSS.h
  include/hpp/fcl/BV/BV_node.h
  include/hpp/fcl/BV/AABB.h
  include/hpp/fcl/BV/OBB.h
  include/hpp/fcl/BV/kDOP.h
  include/hpp/fcl/narrowphase/narrowphase.h
  include/hpp/fcl/narrowphase/gjk.h
  include/hpp/fcl/shape/convex.h
  include/hpp/fcl/shape/details/convex.hxx
  include/hpp/fcl/shape/geometric_shape_to_BVH_model.h
  include/hpp/fcl/shape/geometric_shapes.h
  include/hpp/fcl/shape/geometric_shapes_utility.h
  include/hpp/fcl/distance_func_matrix.h
  include/hpp/fcl/collision.h
  include/hpp/fcl/collision_func_matrix.h
  include/hpp/fcl/distance.h
  include/hpp/fcl/math/matrix_3f.h
  include/hpp/fcl/math/vec_3f.h
  include/hpp/fcl/math/types.h
  include/hpp/fcl/math/transform.h
  include/hpp/fcl/data_types.h
  include/hpp/fcl/BVH/BVH_internal.h
  include/hpp/fcl/BVH/BVH_model.h
  include/hpp/fcl/BVH/BVH_front.h
  include/hpp/fcl/BVH/BVH_utility.h
  include/hpp/fcl/collision_object.h
  include/hpp/fcl/collision_utility.h
  include/hpp/fcl/octree.h
  include/hpp/fcl/fwd.hh
  include/hpp/fcl/mesh_loader/assimp.h
  include/hpp/fcl/mesh_loader/loader.h
  include/hpp/fcl/internal/BV_fitter.h
  include/hpp/fcl/internal/BV_splitter.h
  include/hpp/fcl/internal/intersect.h
  include/hpp/fcl/internal/tools.h
  include/hpp/fcl/internal/traversal_node_base.h
  include/hpp/fcl/internal/traversal_node_bvh_shape.h
  include/hpp/fcl/internal/traversal_node_bvhs.h
  include/hpp/fcl/internal/traversal_node_octree.h
  include/hpp/fcl/internal/traversal_node_setup.h
  include/hpp/fcl/internal/traversal_node_shapes.h
  include/hpp/fcl/internal/traversal_recurse.h
  include/hpp/fcl/internal/traversal.h
  )

# add_subdirectory(doc)
add_subdirectory(src)
if (BUILD_PYTHON_INTERFACE)
  add_subdirectory(python)
endif ()
# add_subdirectory(test)

pkg_config_append_libs("hpp-fcl")
if(HPP_FCL_HAVE_OCTOMAP)
  # FCL_HAVE_OCTOMAP kept for backward compatibility reasons.
  pkg_config_append_cflags(
    "-DHPP_FCL_HAVE_OCTOMAP -DFCL_HAVE_OCTOMAP -DOCTOMAP_MAJOR_VERSION=${OCTOMAP_MAJOR_VERSION} -DOCTOMAP_MINOR_VERSION=${OCTOMAP_MINOR_VERSION} -DOCTOMAP_PATCH_VERSION=${OCTOMAP_PATCH_VERSION}")
endif()

# Install catkin package.xml
#install(FILES package.xml DESTINATION share/${PROJECT_NAME})


