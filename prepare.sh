set -e

# Setup git lfs for binary files
git lfs install
git lfs pull --exclude=""

# Setup submodules
git submodule init
git submodule update --remote
