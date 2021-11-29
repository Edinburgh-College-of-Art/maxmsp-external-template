# maxmsp-external-template

Template Projects for [building external objects in MaxMSP](https://cycling74.com/sdk/max-sdk-8.2.0/)

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:1 orderedList:0 -->

- [maxmsp-external-template](#maxmsp-external-template)
	- [Setup](#setup)
	- [Cloning this Repository](#cloning-this-repository)
	- [Configuration](#configuration)
		- [maxmspsdk.xcconfig](#maxmspsdkxcconfig)
		- [.prop sheets](#prop-sheets)
	- [Projects](#projects)
		- [max-external](#max-external)
		- [max-external~](#max-external)
		- [mspcpp](#mspcpp)

<!-- /TOC -->

## Setup

To get started, click _use this template_ at the top of the repository

![](https://help.github.com/assets/images/help/repository/use-this-template-button.png)

then [follow the instructions for creating a repository](https://help.github.com/en/github/creating-cloning-and-archiving-repositories/creating-a-repository-from-a-template)

## Cloning this Repository

To make this repository a little more portable, the `max-sdk-base` has been included as a submodule. If you are using the [GitHub desktop app](https://desktop.github.com), the submodule will be cloned automatically. If you are using git from the command line, this means you will need to state `--recurse-submodules` when cloning.

```sh
git clone --recurse-submodules https://github.com/Edinburgh-College-of-Art/maxmsp-external-template
```

You should be able to build straight away from the Xcode project or the Visual Studio solution. Other methods of cloning or downloading this repository may result in the `max-sdk-base` folder being empty. In that situation either use the above git command or download the [`max-sdk-base`](https://github.com/Cycling74/max-sdk-base) directly and copy over the contents.

## Configuration

Build configuration is slightly different depending on which IDE you are using. For Visual Studio you should be looking at the [property sheets](https://docs.microsoft.com/en-us/cpp/build/working-with-project-properties?view=vs-2019) and for Xcode the [`.xcconfig`](https://nshipster.com/xcconfig/).

The build destination for each project is set to the default user Max Packages directory.

**macOS**:

```
~/Max 8/Packages/$(Project_Name)/externals
```

**Windows**:

```
$(USERPROFILE)\Documents\Max 8\Packages\$(ProjectName)\externals
```

This means you should be able to use your object in Max immediately after building, though Max will require a restart.

### maxmspsdk.xcconfig

The `maxmspsdk.xcconfig` in the `xcode` directory sets a couple of global paths in the Xcode project. `DSTROOT` sets the build destination.

### .prop sheets

To change the destination folder:

1. make sure you have highlighted the project in the _Solution Explorer_

![highlight solution explorer project](images/highlight_project.png)

2. Press <kbd>F4</kbd> or Properties by navigating the menus `View` -> `Properties...`

3. In Configuration Properties -> General you can change the Output Directory

![vs output directory](images/output-directory.png)

For Visual Studio users, there should be nothing that you need to change in the property sheets. If you would like to change them or just take a look, you can edit them directly in any text editor as VS files are essentially XML files.

To edit the property sheets in visual studio:

1. make sure you have highlighted the project in the _Solution Explorer_

![highlight solution explorer project](images/highlight_project.png)

2. Select the property manager by navigating the menus `View` -> `Other Windows` -> `property manager`

![View -> Other Windows -> property manager](images/property-manager-nav.png)

3. Select a property sheet press <kbd>Alt</kbd> + <kbd>Enter</kbd> or right click and select properties

![properties](images/prop-sheet-props.png)

4. navigate to user macros

![User Macros](images/user-macros.png)

***

## Projects

The Xcode and VS project have multiple targets / projects to demonstrate how to approach building a Max external `.mxo`, `.mxe64` file.

### max-external

The vanilla C approach. There are plenty of examples in the sdk, but this target / project aims to take a more modern approach. Documentation has been added inline as well as some slightly less obtuse variable name choices which will hopefully reduce the barrier of entry.

### max-external~

The vanilla C approach to MSP objects.

### mspcpp

If you have already coded a ton of DSP C++ classes for something like JUCE, you may want to start here.

Demonstrates using `extern "C"` to write wrappers for pre-existing c++ classes. you need only write wrapper functions for public class methods or anything that needs to be called directly in `C`
