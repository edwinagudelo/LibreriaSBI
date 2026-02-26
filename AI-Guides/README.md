# GitHub Actions Workflows

This directory contains CI/CD pipeline configurations for the SBI Library project.

## sbilib_pipeline.yml

Automated build and test pipeline that runs on multiple platforms.

### Triggers

- Push to `main` or `develop` branches
- Pull requests targeting `main` or `develop` branches
- Manual workflow dispatch

### Jobs

#### 1. build-and-test-windows
Builds and tests the library on Windows using MSVC compiler.

**Steps:**
1. Checkout code
2. Set up Python 3.11
3. Install Conan package manager
4. Configure Conan profile
5. Install project dependencies
6. Configure CMake with Conan toolchain
7. Build sbi_clib shared library
8. Build unit tests (configura_test, entorno_test)
9. Run tests with CTest
10. Upload test results as artifacts

#### 2. build-and-test-linux
Builds and tests the library on Ubuntu Linux using GCC compiler.

**Steps:**
1. Checkout code
2. Install system dependencies (build-essential, cmake)
3. Set up Python 3.11
4. Install Conan package manager
5. Configure Conan profile
6. Install project dependencies
7. Configure CMake with Conan toolchain
8. Build sbi_clib shared library
9. Build unit tests (configura_test, entorno_test)
10. Run tests with CTest
11. Upload test results as artifacts

#### 3. build-and-test-macos
Builds and tests the library on macOS using Clang compiler.

**Steps:**
1. Checkout code
2. Set up Python 3.11
3. Install Conan package manager
4. Configure Conan profile
5. Install project dependencies
6. Configure CMake with Conan toolchain
7. Build sbi_clib shared library
8. Build unit tests (configura_test, entorno_test)
9. Run tests with CTest
10. Upload test results as artifacts

### Artifacts

Test results are uploaded as artifacts for each platform:
- `test-results-windows` - Windows test results
- `test-results-linux` - Linux test results
- `test-results-macos` - macOS test results

These artifacts are available for download from the Actions tab in GitHub for 90 days.

### Status Badge

Add this badge to your README.md to show the build status:

```markdown
![SBI Library CI](https://github.com/YOUR_USERNAME/YOUR_REPO/actions/workflows/sbilib_pipeline.yml/badge.svg)
```

Replace `YOUR_USERNAME` and `YOUR_REPO` with your actual GitHub username and repository name.

### Running Manually

You can manually trigger the workflow from the GitHub Actions tab:
1. Go to the "Actions" tab in your repository
2. Select "SBI Library CI Pipeline" from the workflows list
3. Click "Run workflow"
4. Select the branch and click "Run workflow"

### Notes

- Tests are set to `continue-on-error: true` to allow the pipeline to complete even if some tests fail
- This helps identify platform-specific issues
- Check the test results artifacts for detailed failure information
- The pipeline uses Conan 2.x for dependency management
- CMake 3.20+ is required for building the project
