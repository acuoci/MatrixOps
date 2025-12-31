# Quick Start Guide

Get up and running with the MatrixOps tutorial project in 5 minutes!

## Prerequisites

You need:
- Git
- CMake (≥ 3.15)
- C++17 compiler (GCC 12+, Clang 15+, or MSVC 2019+)
- Internet connection (for downloading dependencies)

## Build and Test Locally

### Linux/macOS

```bash
# Clone the repository
git clone <your-repo-url>
cd MatrixOps

# Build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j$(nproc)

# Run tests
cd build
ctest --output-on-failure

# Run benchmarks
./benchmarks/matrixops_benchmarks
```

### Windows (PowerShell)

```powershell
# Clone the repository
git clone <your-repo-url>
cd MatrixOps

# Build
cmake -B build
cmake --build build --config Release

# Run tests
cd build
ctest -C Release --output-on-failure

# Run benchmarks
.\benchmarks\Release\matrixops_benchmarks.exe
```

## GitHub Setup (First Time)

### 1. Create Repository on GitHub

```bash
# In your MatrixOps directory
git init
git add .
git commit -m "Initial commit"
git remote add origin https://github.com/YOUR_USERNAME/MatrixOps.git
git branch -M main
git push -u origin main
```

### 2. Watch CI Run

1. Go to `https://github.com/YOUR_USERNAME/MatrixOps/actions`
2. You'll see workflows running automatically
3. Green checkmark = success! ✅
4. Red X = something failed (check logs)

### 3. Enable GitHub Pages (for documentation)

1. Repository Settings → Pages
2. Source: Deploy from a branch
3. Branch: `gh-pages` → `/ (root)`
4. Save
5. Documentation will be at: `https://YOUR_USERNAME.github.io/MatrixOps/`

## Common Tasks

### Run Code Formatting

```bash
# Check formatting
clang-format --dry-run --Werror src/*.cpp include/matrixops/*.h

# Auto-fix formatting
clang-format -i src/*.cpp include/matrixops/*.h
```

### Run Static Analysis

```bash
cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
clang-tidy --config-file=.clang-tidy -p build src/*.cpp
```

### Measure Code Coverage

```bash
# Build with coverage
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DMATRIXOPS_ENABLE_COVERAGE=ON
cmake --build build

# Run tests
cd build
ctest

# Generate report (Linux)
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' '*/tests/*' '*/benchmarks/*' '*/_deps/*' -o coverage_filtered.info
genhtml coverage_filtered.info --output-directory coverage_html

# Open coverage_html/index.html in your browser
```

### Run with Sanitizers

```bash
# Address Sanitizer
cmake -B build-asan -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g"
cmake --build build-asan
cd build-asan && ctest

# Undefined Behavior Sanitizer
cmake -B build-ubsan -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-fsanitize=undefined -fno-omit-frame-pointer -g"
cmake --build build-ubsan
cd build-ubsan && ctest
```

### Create a Release

```bash
# Update version in CMakeLists.txt first!
# Then create and push a tag
git tag -a v1.0.0 -m "First release"
git push origin v1.0.0

# GitHub Actions will automatically:
# - Build on Linux, macOS, Windows
# - Run all tests
# - Create release artifacts
# - Publish GitHub Release
```

## Understanding the Output

### Successful CI Run

```
✓ Format Check - passed
✓ Static Analysis - passed  
✓ Ubuntu GCC - passed
✓ Ubuntu Clang - passed
✓ macOS - passed
✓ Windows MSVC - passed
✓ Address Sanitizer - passed
✓ Undefined Behavior Sanitizer - passed
✓ Thread Sanitizer - passed
✓ Performance Benchmarks - passed
```

### Test Output

```
===============================================================================
All tests passed (42 assertions in 12 test cases)
```

### Benchmark Output

```
Run on (8 X 3000 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 8192 KiB (x1)
-----------------------------------------------------------------------
Benchmark                            Time             CPU   Iterations
-----------------------------------------------------------------------
BM_MatrixMultiplication/8          245 ns          245 ns      2856789
BM_MatrixMultiplication/16        1845 ns         1844 ns       379234
BM_MatrixMultiplication/32       14234 ns        14230 ns        49182
```

## Troubleshooting

### Build Fails

**Problem:** "Could not find Catch2"  
**Solution:** CMake automatically downloads it. Ensure you have internet connection.

**Problem:** "C++17 required but not supported"  
**Solution:** Update your compiler. Minimum: GCC 7, Clang 5, MSVC 2017.

### Tests Fail

**Problem:** Test failures on macOS  
**Solution:** Ensure you have Xcode Command Line Tools: `xcode-select --install`

**Problem:** Sanitizer failures  
**Solution:** This is good! The sanitizers found a bug. Check the error message for details.

### CI Fails on GitHub

**Problem:** Format check fails  
**Solution:** Run `clang-format -i` locally and commit the changes.

**Problem:** Static analysis fails  
**Solution:** Run `clang-tidy` locally to see warnings, fix them.

**Problem:** Windows build fails but Linux works  
**Solution:** Likely a platform-specific issue. Check the CI logs for details.

## Next Steps

1. Read `TUTORIAL.md` for comprehensive explanations
2. Modify the code and watch CI validate your changes
3. Add new features and tests
4. Experiment with different build configurations
5. Apply what you learned to your own projects!

## Need Help?

- Check the detailed `TUTORIAL.md`
- Review GitHub Actions logs at `.github/workflows/`
- Open an issue on GitHub
- Consult the official documentation linked in TUTORIAL.md

Happy coding! 🎉
