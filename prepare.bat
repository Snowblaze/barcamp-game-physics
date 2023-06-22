@echo off

# Setup git lfs for binary files
git lfs install || (exit /b)
git lfs pull --exclude="" || (exit /b)

# Setup submodules
git submodule init || (exit /b)
git submodule update --remote || (exit /b)

pause