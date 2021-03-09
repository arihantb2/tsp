BUILD_DIRECTORY="build"
BUILD_STATUS_FILE=".build_incomplete"
RUN_FILE="build/tsp"

if ! test -d "$BUILD_DIRECTORY"; then
    echo "Build not executed or incomplete. Building application now.."
    ./build.sh
fi

if test -f "$BUILD_STATUS_FILE"; then
    echo "Build not executed or incomplete. Building application now.."
    ./build.sh
fi

if ! test -f "$RUN_FILE"; then
    echo "Build not executed or incomplete. Building application now.."
    ./build.sh
fi

chmod +x build/tsp
cd build
./tsp
cd ..
