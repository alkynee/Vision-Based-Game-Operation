# Vision-Based-Game-Operation

A revolutionary approach to operate the CS:GO game by using computer vision to translate arm movements in real life into actions in the game. Runs on the OpenCV platform.

## Synopsis

This repository provides a glimpse at it in action: [_**View demonstration**_](https://youtu.be/YiGEf9hP55E).

The user's arm angle and trigger input are handled through the [**_vaaac library_**](https://github.com/alkynee/vaaac) created for this purpose.

## Requirements

You will need to have [OpenCV](https://opencv.org/) installed to compile this program.

## Platform Considerations

Currently, this system uses the win32 api, thus it is only capable of running on Windows. Adapting it to run on other platforms or with other video games shouldn't be too complicated, given that the primary [__*vaaac*__](https://github.com/alkynee/vaaac) library is platform-agnostic.

## Legal Notice

Please note: This software modifies th