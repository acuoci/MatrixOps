# MatrixOps - A Tutorial Project for Professional C++ GitHub Workflow

This is a learning project demonstrating professional GitHub workflows for C++ scientific computing.

## Features Demonstrated

- ✅ Multi-platform CI/CD (Linux, macOS, Windows)
- ✅ Automated testing
- ✅ Code coverage
- ✅ Sanitizers (ASan, UBSan)
- ✅ Static analysis
- ✅ Automated formatting
- ✅ Performance regression testing
- ✅ Automated releases
- ✅ Documentation generation

## Project Structure

```
MatrixOps/
├── include/           # Public headers
│   └── matrixops/
├── src/              # Implementation files
├── tests/            # Unit tests
├── benchmarks/       # Performance tests
├── docs/             # Documentation
├── .github/          # GitHub Actions workflows
└── CMakeLists.txt    # Build configuration
```

## Building

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Testing

```bash
cd build
ctest --output-on-failure
```

## License

MIT License
