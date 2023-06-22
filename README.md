# barcamp-game-physics

## prerequisites

- CMake 3.21.0 and above
- C23 and C++23 capable compiler
- Git LFS extension installed

## usage

Prepare Git LFS and dependencies before starting development

```
# Setup git lfs for binary files
git lfs install
git lfs pull --exclude=""

# Setup submodules
git submodule init
git submodule update --remote
```

## build

To build the executable run the following commands:

```
cmake -S ./ -B ./build
cd ./build
make
```

### XCode

To build XCode project run

`cmake -S ./ -B ./build -GXcode`

## license
[MIT](https://github.com/Snowblaze/sdl2-cmake-starter/blob/main/LICENSE)
