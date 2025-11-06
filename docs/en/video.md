# Getting Onboard Camera Video Stream

## 1. Video Stream Address
```shell
rtsp://192.168.133.1:8554/test
```
The IP address needs to be modified according to the actual connection situation.

## 2. Getting Video Stream via ffmpeg
Execute the following command on a device with ffmpeg installed to directly get the onboard camera video stream
```shell
ffplay -rtsp_transport tcp -fflags nobuffer -flags low_delay -framedrop -strict \
experimental -probesize 32 -analyzeduration 0 -sync ext rtsp://192.168.234.1:8554/test
```

## 3. Getting Video Stream via GStreamer
After installing GStreamer, install the following plugins
```shell
sudo apt install -y gstreamer1.0-tools \
                    gstreamer1.0-plugins-base \
                    gstreamer1.0-plugins-good \
                    gstreamer1.0-plugins-bad \
                    gstreamer1.0-plugins-ugly \
                    gstreamer1.0-libav
```

- gstreamer1.0-tools: Includes core tools such as gst-launch-1.0
- gstreamer1.0-plugins-base: Basic plugins (such as autovideosink)
- gstreamer1.0-plugins-good: Common plugins (such as rtph264depay)
- gstreamer1.0-plugins-bad: Experimental plugins (such as rtspsrc)
- gstreamer1.0-plugins-ugly: Special encoders (such as mpeg)
- gstreamer1.0-libav: FFmpeg related plugins.

After installing the plugins, execute the following command to get the onboard camera video stream
```shell
gst-launch-1.0 rtspsrc location=rtsp://192.168.234.1:8554/test latency=0 ! rtph264depay \
! h264parse ! avdec_h264 ! videoconvert ! videoscale ! video/x-raw,width=1280,height=720 ! autovideosink
```

## 4. Getting Video Stream via VLC
In the latest version 3.0.21 of VLC, right-click on the playlist, select "Add Network Stream", enter the video stream address, and click "Play".
However, some devices cannot open normally after installing version 3.0.21, it is recommended to use GStreamer to get the video stream.

## 5. Getting Video Stream via OpenCV
After installing OpenCV, execute the following code to get the onboard camera video stream
```python
import cv2
import time

def read_rtsp_Stream(rtsp_url):
    # 1. Initialize video capture, force TCP
    cap = cv2.VideoCapture(rtsp_url + "?tcp")  # Try TCP transport
    
    # 2. Reduce buffer size
    if hasattr(cv2, 'CAP_PROP_BUFFERSIZE'):
        cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Buffer only retains 1 frame
    
    # 3. Disable hardware acceleration
    if hasattr(cv2, 'CAP_PROP_HW_ACCELERATION'):
        cap.set(cv2.CAP_PROP_HW_ACCELERATION, cv2.VIDEO_ACCELERATION_NONE)
    
    if not cap.isOpened():
        print(f"Cannot open stream: {rtsp_url}")
        # If TCP fails, try default protocol
        cap = cv2.VideoCapture(rtsp_url)
        if not cap.isOpened():
            print("All protocols cannot open stream, exiting")
            return
    
    # 4. Loop reading, only take the latest frame (skip old frames)
    while True:
        # Read multiple times consecutively, discard intermediate frames, only keep the last frame (latest frame)
        # This step solves the problem of old frames accumulated in the buffer
        for _ in range(3):  # Try reading 3 times to ensure getting the latest frame
            ret, frame = cap.read()
            if not ret:
                break
        
        if not ret:
            print("Stream interrupted, trying to reconnect...")
            time.sleep(1)
            cap = cv2.VideoCapture(rtsp_url + "?tcp")
            if hasattr(cv2, 'CAP_PROP_BUFFERSIZE'):
                cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)
            continue
        
        # 5. Reduce resolution (optional, reduce display and transmission pressure)
        frame = cv2.resize(frame, (1280, 720))  # Adjust according to needs
        
        # Display frame
        cv2.imshow("RTSP Stream (Press q to exit)", frame)
        
        # Detect exit
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    rtsp_url = "rtsp://192.168.234.1:8554/test" 
    read_rtsp_Stream(rtsp_url)
    
```

## 6. Getting Video Stream via OpenCV Using GStreamer
After installing OpenCV and GStreamer, execute the following code to get the onboard camera video stream

```python

import cv2
import time

def read_rtsp_gstreamer(rtsp_url):  
    # Build GStreamer pipeline
    pipeline = (
        f'rtspsrc location={rtsp_url} latency=0 ! '
        'rtph264depay ! avdec_h264 ! '
        'videoconvert ! video/x-raw,format=BGR ! '
        'appsink sync=false drop=true max-buffers=1'
    )

    # Create GStreamer capture object
    cap = cv2.VideoCapture(pipeline, cv2.CAP_GSTREAMER)
    
    if not cap.isOpened():
        print("Cannot open GStreamer pipeline")
        return
    
    try:
        while True:
            ret, frame = cap.read()
            if not ret:
                print("Failed to read frame")
                break
                
            # Display frame
            cv2.imshow("GStreamer Low Latency", frame)
            
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
                
    finally:
        cap.release()
        cv2.destroyAllWindows()
if __name__ == "__main__":
    rtsp_url = "rtsp://192.168.234.1:8554/test"
    read_rtsp_gstreamer(rtsp_url)
```
## 7. Optimizing Video Stream Latency

Directly acquiring and displaying video streams may have picture delay issues. In this case, video stream acquisition parameters need to be optimized, such as adjusting buffer size and disabling hardware acceleration.  
Getting the same video stream on the device screen remote control has achieved lower latency.  
Using the GStreamer method above to get the video stream also has low latency, which is not due to delay in the machine's video stream push.  
You can also choose programs like Daniu Live SDK that have been specifically optimized for playback.