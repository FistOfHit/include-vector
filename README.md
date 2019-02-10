<a href="https://imgur.com/SADgi5k"><img src="https://i.imgur.com/SADgi5k.jpg" title="source: imgur.com" width="30%" /></a>
<a href="https://imgur.com/YwXwEwg"><img src="https://i.imgur.com/YwXwEwg.jpg" title="source: imgur.com" width="30%" /></a>
<a href="https://imgur.com/q2WSgfi"><img src="https://i.imgur.com/q2WSgfi.jpg" title="source: imgur.com" width="30%" /></a>


# Edge enhancement for medical image interpretation #

Capability developed to support the interpretation of medical images by enchancing visual edges on the images, intended originally for enchancing x-ray scans but can be applied to any image theorietically. Developed as part of ACSE-5 (2019) at Imperial College London.

## Summary ##
- Read DICOM images, convert to BMP and back to DICOM - supports both 24-bit and 8-bit depth images (almost all BMP and DICOM images)
- Invert colors, apply greyscaling, thresholding, and use convolutional filters for edge enchancement
- One-click setup, and simple user interface with minimal input required. 

## Requirements and Installation ##

- MS Visual studio IDE
- C++ SDK (part of MSVS)
- DMCTK [1] binaries and DLL's (included, and automatically setup. Must be in a dmctk directory in the working directory)

To setup, simply clone this repository. The file setup.bat will install the DMCTK package if needed however these files are already in the repository so you can open the project in MSVS and build as normal. (NOTE: as of 07/02/19, compiler warnings may be raised regarding the inputs to ``_RAISE``. You can safely ignore these for now. 

## Usage ##

Upon running, the user interface should make things quite clear and self explanatory:

<a href="https://imgur.com/OkvS8sK"><img src="https://i.imgur.com/OkvS8sK.jpg" title="source: imgur.com" width="100%"/></a>

From here you can load images, apply filters and save them (converting automatically as appropriate). Of course, this requires some background knowledge from the user in that images should be loaded first, and the order in which filters should be applied etc. However anyone who has to examine DICOM files as a profession should be more than capable of understanding this. 

Having all these filters, and being able to use them in various orders does mean that you can apply very complicated operations to the images quite easily. Experiment around if you like, but the reccomended order for colourful images is greyscale -> threshold -> omni/bi directional and for relativley monochromatic images (like X-ray scans), simply avoid the thresholding step.

With the current latest release, the possibility of memory leaks does exist if the user attempts to load/save files in incorrect ordering, so care should be taken with this. 

Of course, you're not restriced at all to using DICOM files. You could very well just load up BMP files independently and play around, getting results like these:

<a href="https://imgur.com/TUrFtyz"><img src="https://i.imgur.com/TUrFtyz.png" title="source: imgur.com" width="40%" /></a>
<a href="https://imgur.com/6SoOfR1"><img src="https://i.imgur.com/6SoOfR1.png" title="source: imgur.com" width="40%"/></a>
<a href="https://imgur.com/I1nOufd"><img src="https://i.imgur.com/I1nOufd.png" title="source: imgur.com" width="40%" /></a>
<a href="https://imgur.com/Tbws3MZ"><img src="https://i.imgur.com/Tbws3MZ.png" title="source: imgur.com" width="40%"/></a>


## License ##
MIT license.

## References ##
[1]: DMCTK - 07/02/2019 -dicom.offis.de - https://dcmtk.org/
