# mshare
a simple node web app used for sharing and hosting files across local network

## SETUP INSTRUCTIONS

1. You should have node installed in your device, and was added to Environment Variables

2. Download or clone this repository

3. open command line and change directory inside this repository **"cd 'path/to/folder/mshare'**

4. in the command line run **"npm install"** to install dependencies(internet connection needed)

5. if you are using *linux* use the **"make"** command to see how to compile the html_generate.cpp

## TO START HOSTING/SERVING FILES

WINDOWS - to start run in command line **"node fileserver_win.js"** in the same mshare folder directory to start serving/hosting files

LINUX   - **"node fileserver_linux"**

## TO VIEW SHARED FILES FROM OTHER DEVICES

1.) after step starting node, you should be able to see that the program is running and you should see an IP address

2.) now every devices that is connected to the same network where your main device that is running the "node filewebserver.js" is also connected should be able to upload and download files that is being hosted by main device.

3.) to access the web app in other devices, use the appropriate IP address being displayed by the "node filewebserver.js" use that as a url for other devices and add a "/files" in it 

  Windows host EX: http://HOST_IP/files
  
  Linux host EX: http://HOST_IP:3000/files    (can also setup linux to do the same http request like in windows but theres it more work that using port 3000)
  
4.) enter this url in other device, now you can access the hosted files and upload or download files to/from the host

## sample image

![Main Device Running NODE](/public/images/commandline.png) ![Other Device in the same network](/public/images/otherdevice.jpg)
