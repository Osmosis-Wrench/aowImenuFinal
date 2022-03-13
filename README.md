# Oxygen Meter

SKSE plugin that repurposes the enchantment charge meter for an oxygen meter when underwater

## Requirements

* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2019](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CommonLibSSE](https://github.com/powerof3/CommonLibSSE/tree/dev)
	* You need to build from the powerof3/dev branch
	* Add this as as an environment variable `CommonLibSSEPath`

## Register Visual Studio as a Generator

* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building

git clone this url
cd into folder

```powershell

cmake -B build -S .

```

## License

[MIT](LICENSE)
