include( FetchContent )
include( gauxc-dep-versions )

# Check if offline build is requested or a local directory is specified
if(GAUXC_OFFLINE_BUILD OR GAUXC_LINALG_MODULES_DIR)
  message(STATUS "Offline mode for linalg-cmake-modules")

  # Check if a local directory is specified
  if(GAUXC_LINALG_MODULES_DIR)
    message(STATUS "Using local linalg-cmake-modules from: ${GAUXC_LINALG_MODULES_DIR}")

    # Verify the directory exists
    if(NOT EXISTS "${GAUXC_LINALG_MODULES_DIR}")
      message(FATAL_ERROR "GAUXC_LINALG_MODULES_DIR points to non-existent directory: ${GAUXC_LINALG_MODULES_DIR}")
    endif()

    # Add the directory to CMAKE_MODULE_PATH
    list( PREPEND CMAKE_MODULE_PATH ${GAUXC_LINALG_MODULES_DIR} )
    message(STATUS "Successfully added linalg-cmake-modules to CMAKE_MODULE_PATH")
    set(linalg-cmake-modules_SOURCE_DIR ${GAUXC_LINALG_MODULES_DIR})

  else()
    # No directory specified, provide helpful error
    message(STATUS "GAUXC_OFFLINE_BUILD enabled but GAUXC_LINALG_MODULES_DIR not specified")
    message(FATAL_ERROR "linalg-cmake-modules is required but GAUXC_OFFLINE_BUILD is enabled. "
                        "Please either:
                        1. Set GAUXC_LINALG_MODULES_DIR to point to a local installation, or
                        2. Disable GAUXC_OFFLINE_BUILD to allow remote downloads.")
  endif()
else()
  # Normal online build
  FetchContent_Declare( linalg-cmake-modules
    GIT_REPOSITORY ${GAUXC_LINALG_MODULES_REPOSITORY}
    GIT_TAG        ${GAUXC_LINALG_MODULES_REVISION}
  )
  FetchContent_GetProperties( linalg-cmake-modules )
  if( NOT linalg-cmake-modules_POPULATED )
    FetchContent_Populate( linalg-cmake-modules )
    list( PREPEND CMAKE_MODULE_PATH ${linalg-cmake-modules_SOURCE_DIR} )
  endif()
endif()
