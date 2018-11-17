# Dependency management

### Clone and install dependencies
```bash
./tools/setup/init.sh CXX=g++-7
```
### Update and reinstall dependencies
```bash
./tools/setup/update.sh CXX=g++-7
```
### Install dependencies
```bash
./tools/setup/install.sh CXX=g++-7
```
Note: This script is used internally by `init.sh` and `update.sh`, so you don't usually need to use it, but it can be useful in some situations. For example, if compilation fails because of wrong make parameters, you can skip the cloning/updating phase, and jump to installation with this script.


# Troubleshooting
1. All scripts accept `make` parameters, as shown in the examples. Make sure to they are all correct.
2. Run the scripts from the project root.
3. Dependencies get stored in `.dependencies` directory of the project root. Check if they exist and are correct.
