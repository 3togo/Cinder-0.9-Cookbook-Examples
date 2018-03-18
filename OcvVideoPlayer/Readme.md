### OcvVideoPlayer
<br />

**Playing back a movie file with OpenCV instead of Quicktime**
<br /><br />

This requires the following Cinder blocks cloned in the cinder_master/blocks directory: 

https://github.com/wieden-kennedy/Cinder-OcvVideo

https://github.com/christian-schneider/Cinder-OpenCV3

My fork of Cinder-OpenCV3 just adds the dependencies (as static libs) for VideoCapture to actually work which are currently not present in the official Cinder-OpenCV3 rep. 

Quick instruction to *build OpenCV from source* on your Mac, it worked for me on Sierra: 

Use homebrew to install opencv3

```brew install opencv3```

This makes sure you have all the dependencies. Then download or clone the sourcode and use Cmake Gui for configuring. Important: uncheck the BUILD_SHARED_LIBS flag to have the static libs built as well. 

**The Cinder-OcvVideo implementation is currently not working right on MacOSX, the movie plays back at roughly half the original speed. Needs investigation.**


