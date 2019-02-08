<a href="https://imgur.com/SADgi5k"><img src="https://i.imgur.com/SADgi5k.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/YwXwEwg"><img src="https://i.imgur.com/YwXwEwg.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/q2WSgfi"><img src="https://i.imgur.com/q2WSgfi.jpg" title="source: imgur.com" /></a>


# Edge enhancement for medical image interpretation #

Capability developed to support the interpretation of medical images by enchancing visual edges on the images, intended originally for enchancing x-ray scans but can be applied to any image theorietically. Developed as part of ACSE-5 (2019) at Imperial College London.

## Summary ##
- Read DICOM images, convert to BMP and back to DICOM
- Invert colors, apply greyscaling, and use convolutional filters for edge enchancement
- One-click setup, and simple user interface with minimal input required. 

## Requirements and Installation ##

- MS Visual studio IDE
- C++ SDK (part of MSVS)
- DMCTK [1] binaries and DLL's (included, and automatically setup)

To setup, simply clone this repository and run the setup file, "setup.bat". That is all. Then you can open the project in MSVS and build as normal. (NOTE: as of 07/02/19, compiler warnings may be raised regarding the inputs to ``_RAISE``. You can safely ignore these for now. 

## Usage ##

The most important thing is to be sure that you've run setup.bat before attempting to run the code itself. After that you are free to compile the code and run as you like. Once running, you are prompted to feed in a file name (absolute path needed, make sure to provide the full path starting with "C:/..." etc.) for the DICOM iamge that you want to detect edges in. Everything else is decided before compile time, and so to edit it (you shouldn't need to), you'll have to edit the code itself.

In fact, if you tweak the main file, you can quite easily load and apply the filter to BMP images independently, without any conversion to/from DICOM. Here's what you can create:

<a href="https://imgur.com/TUrFtyz"><img src="https://i.imgur.com/TUrFtyz.png" title="source: imgur.com" /></a>
<a href="https://imgur.com/6SoOfR1"><img src="https://i.imgur.com/6SoOfR1.png" title="source: imgur.com" /></a>


## License ##
MIT license.

## References ##
[1]: DMCTK - 07/02/2019 -dicom.offis.de - https://dcmtk.org/
