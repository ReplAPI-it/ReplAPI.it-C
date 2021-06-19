if ! which conan > /dev/null; then pip install conan; fi
cd ReplAPI.it

conan create . demo/testing