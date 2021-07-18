# mshare
a simple node web app used for sharing and hosting files across local network

## REQUIREMENTS

1. You should have ***nodejs installed*** in your system

2. You should have set your nodejs bin path to ***environment variables***(the installer for windows automatically does this as I remember)

3. You should have ***internet connection*** to install dependencies

----------------------------------------------------------

## SETUP FOR BEGINERS

1. ***Select or create*** a folder/directory where you want to put this project.

2. ***Download this repository***, and extract it.

3. ***Move or Copy*** the project's folder called **mshare** into your ***created or selected folder***

4. Go inside the **mshare** folder after you copy/move it... then copy its directory/path

5. open the command line(cmd) then type **cd "** then press **ctrl+v** (paste the path) then put a double-quote **"** at the end then hit enter.

    ex: **cd "the/copied/path/mshare"**
    
6. then we need to ***install dependencies***(internet connection required), to do that input the command below in the command line and hit enter 

    **npm install**
  
----------------------------------------------------------
  
## SETUP WITH GIT, AND RUNNING/HOSTING THE APPLICATION

**in your command line termina, cd to the directory where you want to put the node app, ex: ```cd "C:/Documents/myapplication"```, then run the following command below**

### for windows

```
git clone https://github.com/mrdcvlsc/mshare.git
cd mshare
npm install
node fileserver_win.js
```

### for linux

```
git clone https://github.com/mrdcvlsc/mshare.git
cd mshare
npm install
make linux
node fileserver_linux.js
```
----------------------------------------------------------

## UPLOAD AND VIEW FILES IN ANY DEVICE THAT IS CONNECTED TO THE NETWORK WHERE THE HOST IS ALSO CONNECTED USING YOUR BROWSER

To view files from other devices you should have done the "TO START HOSTING/SERVING FILES" step above.

1.) to access the web app in other devices, use the appropriate IP address being displayed by the "node fileserver_win.js or fileserver_linux.js" use that as a url for other devices and add a "/files" in it 

  Windows host url format: ***http://HOST_IP/files***
  
  Linux host url format: ***http://HOST_IP:3000/files*** (you can also setup linux to do the same http request like in windows but there is more work that using port 3000)
  
ex in browser : ***https:192.168.5.123/files*** or add a :3000 for linux ***https:192.168.5.123:3000/files***  

if node is saying that your port is not avilable, you can change it, it is inside the fileserver_win.js or fileserver_linux.js at the end of the files, use a text editor

## sample image

![Main Device Running NODE](/public/images/commandline.png) ![Other Device in the same network](/public/images/otherdevice.jpg)
