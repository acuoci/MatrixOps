# Complete Tutorial: Professional C++ GitHub Workflow

This tutorial walks you through setting up a professional GitHub workflow for C++ scientific computing projects, from scratch to production-ready automation.

## Table of Contents

1. [Initial Setup](#initial-setup)
2. [Understanding the Project Structure](#understanding-the-project-structure)
3. [GitHub Repository Setup](#github-repository-setup)
4. [CI/CD Workflows Explained](#cicd-workflows-explained)
5. [Code Quality Tools](#code-quality-tools)
6. [Testing Strategy](#testing-strategy)
7. [Performance Monitoring](#performance-monitoring)
8. [Documentation](#documentation)
9. [Release Process](#release-process)
10. [Applying to Your Project](#applying-to-your-project)

---

## Initial Setup

### Prerequisites

Install these tools on your local machine:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install git cmake g++ clang-format clang-tidy

# macOS (with Homebrew)
brew install git cmake llvm

# Windows (with Chocolatey)
choco install git cmake llvm
```

### Local Build and Test

```bash
# Clone the repository (after pushing to GitHub)
git clone <your-repo-url>
cd MatrixOps

# Configure and build
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

# Run tests
cd build
ctest --output-on-failure

# Run benchmarks
./benchmarks/matrixops_benchmarks
```

---

## Understanding the Project Structure

### Key Files and Their Purposes

**Source Code:**
- `include/matrixops/matrix.h` - Public API header
- `src/matrix.cpp` - Implementation
- `tests/test_matrix.cpp` - Unit tests using Catch2
- `benchmarks/bench_matrix.cpp` - Performance benchmarks using Google Benchmark

**Build Configuration:**
- `CMakeLists.txt` - Main build script
- `tests/CMakeLists.txt` - Test configuration
- `benchmarks/CMakeLists.txt` - Benchmark configuration
- `cmake/MatrixOpsConfig.cmake.in` - Package configuration template

**Code Quality:**
- `.clang-format` - Automatic code formatting rules
- `.clang-tidy` - Static analysis rules
- `.gitignore` - Files to exclude from version control

**GitHub Workflows:**
- `.github/workflows/ci.yml` - Main CI pipeline
- `.github/workflows/release.yml` - Automated releases
- `.github/workflows/docs.yml` - Documentation generation

---

## GitHub Repository Setup

### Step 1: Create GitHub Repository

1. Go to https://github.com/new
2. Name: `MatrixOps` (or your preferred name)
3. Description: "Professional C++ workflow tutorial"
4. Visibility: Public or Private
5. **DO NOT** initialize with README (we already have one)
6. Click "Create repository"

### Step 2: Push Your Local Code

```bash
# Initialize git repository
cd MatrixOps
git init

# Add all files
git add .

# Commit
git commit -m "Initial commit: Complete project structure"

# Add remote
git remote add origin https://github.com/YOUR_USERNAME/MatrixOps.git

# Push to GitHub
git branch -M main
git push -u origin main
```

### Step 3: Enable GitHub Pages (for documentation)

1. Go to repository Settings → Pages
2. Source: Deploy from a branch
3. Branch: `gh-pages` → `/ (root)`
4. Save

### Step 4: Add Secrets (if using Codecov)

1. Sign up at https://codecov.io with your GitHub account
2. Add your repository
3. Copy the upload token
4. Go to GitHub repository Settings → Secrets and variables → Actions
5. Click "New repository secret"
6. Name: `CODECOV_TOKEN`
7. Value: paste your token
8. Save

---

## CI/CD Workflows Explained

### Main CI Workflow (`.github/workflows/ci.yml`)

This workflow runs on every push and pull request. It includes:

#### 1. **Format Check Job**
```yaml
format-check:
  runs-on: ubuntu-latest
  steps:
  - uses: actions/checkout@v4
  - uses: jidicula/clang-format-action@v4.11.0
```
- Checks if code follows `.clang-format` rules
- Fails if formatting is incorrect
- To fix locally: `clang-format -i src/*.cpp include/matrixops/*.h`

#### 2. **Static Analysis Job**
```yaml
static-analysis:
  runs-on: ubuntu-latest
  steps:
  - run: clang-tidy-17 --config-file=.clang-tidy -p build src/*.cpp
```
- Runs clang-tidy to find potential bugs
- Checks code quality and best practices
- Configure rules in `.clang-tidy`

#### 3. **Multi-Platform Build and Test**
```yaml
strategy:
  matrix:
    config:
    - { os: ubuntu-latest, cc: gcc-12, cxx: g++-12 }
    - { os: ubuntu-latest, cc: clang-15, cxx: clang++-15 }
    - { os: macos-latest, cc: clang, cxx: clang++ }
    - { os: windows-latest, cc: cl, cxx: cl }
```
- Builds on Linux (GCC & Clang), macOS, and Windows
- Ensures cross-platform compatibility
- Runs all tests on each platform

#### 4. **Code Coverage**
```yaml
- name: Generate coverage report
  run: |
    lcov --directory build --capture --output-file coverage.info
    lcov --remove coverage.info '/usr/*' '*/tests/*' --output-file coverage.info
```
- Measures test coverage on Ubuntu GCC build
- Uploads to Codecov
- Coverage badge: Add to README with `[![codecov](https://codecov.io/gh/USERNAME/REPO/branch/main/graph/badge.svg)](https://codecov.io/gh/USERNAME/REPO)`

#### 5. **Sanitizer Builds**
```yaml
sanitizers:
  strategy:
    matrix:
      sanitizer: [address, undefined, thread]
```
- **AddressSanitizer (ASan)**: Detects memory errors (buffer overflows, use-after-free)
- **UndefinedBehaviorSanitizer (UBSan)**: Catches undefined behavior
- **ThreadSanitizer (TSan)**: Finds data races in multithreaded code

#### 6. **Performance Benchmarks**
```yaml
- name: Run benchmarks
  run: ./build/benchmarks/matrixops_benchmarks --benchmark_format=json
- uses: benchmark-action/github-action-benchmark@v1
  with:
    alert-threshold: '120%'
```
- Runs benchmarks on every commit
- Tracks performance over time
- Alerts if performance degrades by >20%
- Results viewable at: `https://YOUR_USERNAME.github.io/MatrixOps/dev/bench/`

---

## Code Quality Tools

### clang-format (Automatic Formatting)

**Purpose:** Ensures consistent code style across the project.

**Usage:**
```bash
# Format all source files
find src include tests -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Check formatting (CI mode)
clang-format --dry-run --Werror src/*.cpp include/matrixops/*.h
```

**Configuration (`.clang-format`):**
- `BasedOnStyle: LLVM` - Base style
- `IndentWidth: 4` - 4 spaces for indentation
- `ColumnLimit: 80` - Maximum line length
- Customize to your preferences!

**IDE Integration:**
- VS Code: Install "C/C++" extension, enable format on save
- CLion: Settings → Editor → Code Style → C/C++ → Set from... → .clang-format

### clang-tidy (Static Analysis)

**Purpose:** Catches bugs, performance issues, and style violations.

**Usage:**
```bash
# Run on all files
clang-tidy --config-file=.clang-tidy -p build src/*.cpp

# Auto-fix issues (be careful!)
clang-tidy --config-file=.clang-tidy -p build --fix src/*.cpp
```

**Key Checks Enabled:**
- `bugprone-*`: Potential bugs
- `cert-*`: CERT C++ Coding Standard
- `cppcoreguidelines-*`: C++ Core Guidelines
- `modernize-*`: Modern C++ features (C++11/14/17)
- `performance-*`: Performance improvements
- `readability-*`: Code readability

**Common Warnings:**
- Uninitialized variables
- Memory leaks
- Inefficient string operations
- Use of deprecated features

---

## Testing Strategy

### Unit Tests (Catch2)

**Structure:**
```cpp
TEST_CASE("Description", "[tag1][tag2]") {
    SECTION("Subsection") {
        REQUIRE(condition);
        REQUIRE_THROWS_AS(expression, exception_type);
    }
}
```

**Running Tests:**
```bash
# All tests
ctest

# Verbose output
ctest --output-on-failure

# Specific test
ctest -R matrix

# With Catch2 filters
./build/tests/matrixops_tests "[multiplication]"
```

**Coverage Analysis:**
```bash
# Build with coverage
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DMATRIXOPS_ENABLE_COVERAGE=ON
cmake --build build

# Run tests
cd build
ctest

# Generate HTML report
genhtml coverage.info --output-directory coverage_html
# Open coverage_html/index.html in browser
```

**Best Practices:**
- Test normal cases, edge cases, and error conditions
- Each function should have multiple test cases
- Aim for >80% coverage for critical code
- Use descriptive test names

### Sanitizers

**AddressSanitizer Example:**
```bash
cmake -B build -DCMAKE_CXX_FLAGS="-fsanitize=address -g"
cmake --build build
./build/tests/matrixops_tests
```

**If a memory error is found, you'll see:**
```
=================================================================
==12345==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x...
    #0 0x... in Matrix::operator()
    #1 0x... in test_case
```

**Common Issues Detected:**
- Buffer overflows
- Use-after-free
- Memory leaks
- Stack overflows

---

## Performance Monitoring

### Google Benchmark

**Writing Benchmarks:**
```cpp
static void BM_MyFunction(benchmark::State& state) {
    // Setup
    Matrix m(100, 100);
    
    // Benchmark loop
    for (auto _ : state) {
        auto result = m.transpose();
        benchmark::DoNotOptimize(result);  // Prevent optimization
    }
    
    // Optional: Set computational complexity
    state.SetComplexityN(state.range(0));
}

BENCHMARK(BM_MyFunction)->Range(8, 8<<10)->Complexity();
```

**Running Benchmarks:**
```bash
# All benchmarks
./build/benchmarks/matrixops_benchmarks

# Specific benchmark
./build/benchmarks/matrixops_benchmarks --benchmark_filter=Multiplication

# JSON output (for CI)
./build/benchmarks/matrixops_benchmarks --benchmark_format=json > results.json
```

**Interpreting Results:**
```
Benchmark                Time             CPU   Iterations
---------------------------------------------------------
BM_MatrixMult/8        245 ns          245 ns      2856789
BM_MatrixMult/16       1845 ns         1844 ns       379234
BM_MatrixMult/32      14234 ns        14230 ns        49182
```

**Performance Regression:**
- GitHub Action automatically tracks performance
- Alerts if >20% slowdown detected
- View graphs at `https://YOUR_USERNAME.github.io/MatrixOps/dev/bench/`

---

## Documentation

### Doxygen Comments

**Header File Example:**
```cpp
/**
 * @brief Calculate the Frobenius norm of the matrix
 * 
 * The Frobenius norm is defined as the square root of the sum
 * of the absolute squares of its elements.
 * 
 * @return The Frobenius norm as a double
 * 
 * @note This operation is O(n*m) where n and m are dimensions
 */
double norm() const;
```

**Documentation Tags:**
- `@brief`: Short description
- `@param name description`: Parameter documentation
- `@return description`: Return value
- `@throw exception description`: Exceptions thrown
- `@note`: Additional notes
- `@warning`: Important warnings
- `@see`: References to related items

**Generating Locally:**
```bash
# Install Doxygen
sudo apt-get install doxygen graphviz

# Generate
doxygen Doxyfile

# Open in browser
firefox docs/html/index.html
```

**GitHub Pages:**
- Documentation automatically deployed to `https://YOUR_USERNAME.github.io/MatrixOps/`
- Updates on every push to `main` branch

---

## Release Process

### Manual Release

**Step 1: Update version numbers**
```cmake
# CMakeLists.txt
project(MatrixOps VERSION 1.1.0)
```

**Step 2: Create and push tag**
```bash
git tag -a v1.1.0 -m "Release version 1.1.0"
git push origin v1.1.0
```

**Step 3: Automatic workflow triggers**
- Builds on Linux, macOS, Windows
- Runs tests on all platforms
- Creates release artifacts
- Publishes GitHub Release

### Semantic Versioning

Follow [SemVer](https://semver.org/):
- `MAJOR.MINOR.PATCH`
- MAJOR: Breaking API changes
- MINOR: New features, backwards compatible
- PATCH: Bug fixes

Examples:
- `v1.0.0` → `v1.0.1`: Bug fix
- `v1.0.0` → `v1.1.0`: New feature
- `v1.0.0` → `v2.0.0`: Breaking change

---

## Applying to Your Project

### Gradual Integration

**Phase 1: Basic Setup** (Week 1)
1. Add `.gitignore`, `LICENSE`, `README.md`
2. Set up CMake with modern targets
3. Create basic CI workflow (Linux only)
4. Add clang-format

**Phase 2: Testing** (Week 2)
5. Convert existing tests to Catch2
6. Add code coverage
7. Enable multi-platform CI

**Phase 3: Quality** (Week 3)
8. Add clang-tidy
9. Enable sanitizers
10. Add benchmarks

**Phase 4: Automation** (Week 4)
11. Set up documentation
12. Add release automation
13. Configure performance tracking

### Adapting for Your Framework

**For your reactive flow simulation:**

1. **Dependencies:** Update `CMakeLists.txt` to find your libraries:
```cmake
find_package(Eigen3 REQUIRED)
find_package(MKL REQUIRED)
find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)
# ... etc

target_link_libraries(your_target
    PRIVATE
        Eigen3::Eigen
        MKL::MKL
        Boost::boost
        spdlog::spdlog
)
```

2. **Testing:** Focus on critical numerical methods:
   - Test conservation properties
   - Verify against analytical solutions
   - Check thermodynamic consistency

3. **Benchmarks:** Performance-critical operations:
   - Jacobian calculations
   - Chemistry integration
   - Linear solver performance

4. **Documentation:** Scientific context:
   - Mathematical formulations
   - Numerical schemes
   - Validation cases

### Common Pitfalls

1. **Large binary files:** Don't commit build artifacts or large data files
   - Use Git LFS for large test data
   - Keep repository < 1 GB

2. **Hardcoded paths:** Use relative paths and CMake variables
   ```cmake
   # Bad: set(EIGEN_DIR /home/user/eigen)
   # Good: find_package(Eigen3 REQUIRED)
   ```

3. **Platform-specific code:** Use `#ifdef` guards
   ```cpp
   #ifdef _WIN32
       // Windows-specific code
   #elif __APPLE__
       // macOS-specific code
   #else
       // Linux/Unix code
   #endif
   ```

4. **Ignoring warnings:** Treat warnings as errors (`-Werror` in CMake)

---

## Next Steps

### Recommended Enhancements

1. **Codecov integration:** Visual coverage reports
2. **GitHub Actions matrix:** Test multiple compilers/versions
3. **Pre-commit hooks:** Auto-format before commit
4. **Branch protection:** Require CI success before merge
5. **Dependabot:** Automatic dependency updates
6. **Custom badges:** Add to README

### Learning Resources

- **CMake:** [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)
- **GitHub Actions:** [Actions Documentation](https://docs.github.com/en/actions)
- **Catch2:** [Catch2 Tutorial](https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md)
- **Google Benchmark:** [Benchmark User Guide](https://github.com/google/benchmark/blob/main/docs/user_guide.md)
- **Doxygen:** [Doxygen Manual](https://www.doxygen.nl/manual/index.html)

### Getting Help

- GitHub Issues: For project-specific questions
- Stack Overflow: Tag `cmake`, `github-actions`, `catch2`
- Reddit: r/cpp, r/github
- C++ Slack/Discord communities

---

## Conclusion

You now have a complete, professional GitHub workflow for C++ scientific computing! This setup provides:

✅ Multi-platform compatibility  
✅ Automated testing and validation  
✅ Code quality enforcement  
✅ Performance monitoring  
✅ Comprehensive documentation  
✅ Streamlined releases  

The key is to implement these features gradually. Start with basic CI, then add features as you become comfortable with each tool.

Remember: **The goal is not perfection, but continuous improvement!**

Good luck with your reactive flow simulation framework! 🚀
