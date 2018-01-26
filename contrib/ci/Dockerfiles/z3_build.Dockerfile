ARG DOCKER_IMAGE_BASE
FROM ${DOCKER_IMAGE_BASE}

# Build arguments. This can be changed when invoking
# `docker build`.
ARG ASAN_BUILD
ARG ASAN_DSO
ARG BUILD_DOCS
ARG CC
ARG COMMIT_HASH
ARG CXX
ARG DOTNET_BINDINGS
ARG JAVA_BINDINGS
ARG NO_SUPPRESS_OUTPUT
ARG PYTHON_BINDINGS
ARG PYTHON_EXECUTABLE=/usr/bin/python2.7
ARG RUN_API_EXAMPLES
ARG RUN_SYSTEM_TESTS
ARG RUN_UNIT_TESTS
ARG SANITIZER_PRINT_SUPPRESSIONS
ARG TARGET_ARCH
ARG TEST_INSTALL
ARG UBSAN_BUILD
ARG USE_LIBGMP
ARG USE_LTO
ARG USE_OPENMP
ARG Z3_SRC_DIR=/home/user/z3_src
ARG Z3_BUILD_TYPE
ARG Z3_CMAKE_GENERATOR
ARG Z3_INSTALL_PREFIX
ARG Z3_STATIC_BUILD
ARG Z3_SYSTEM_TEST_GIT_REVISION
ARG Z3_WARNINGS_AS_ERRORS
ARG Z3_VERBOSE_BUILD_OUTPUT

ENV \
  CC=${CC} \
  COMMIT_HASH=${COMMIT_HASH} \
  CXX=${CXX} \
  Z3_SRC_DIR=${Z3_SRC_DIR} \
  Z3_BUILD_DIR=/home/user/z3_build \
  Z3_BUILD_TYPE=${Z3_BUILD_TYPE}

# Build Z3
RUN mkdir -p "${Z3_SRC_DIR}"
ADD --chown=user /cmake ${Z3_SRC_DIR}/cmake/
ADD --chown=user /doc ${Z3_SRC_DIR}/doc/
ADD --chown=user /examples ${Z3_SRC_DIR}/examples/
ADD --chown=user /scripts ${Z3_SRC_DIR}/scripts/
ADD --chown=user /src ${Z3_SRC_DIR}/src/
ADD --chown=user *.txt *.md RELEASE_NOTES ${Z3_SRC_DIR}/
ADD --chown=user /package_z3_linux.sh ${Z3_SRC_DIR}/
RUN ${Z3_SRC_DIR}/package_z3_linux.sh

