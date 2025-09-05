@echo off
pushd .
if not exist build/tests/training_main.exe (
	echo "training_main.exe not exists!"
	popd
)
cd build/tests
training_main.exe
popd