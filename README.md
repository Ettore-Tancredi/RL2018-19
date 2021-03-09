#Rescue Line Galilei 2018/19
This is the repository where we are developing the _code_ that will guide our robot at the 2019 edition of the Robocup JR in the Rescue Line competition.

![Alt text](https://upload.wikimedia.org/wikipedia/commons/f/fa/Martian_rover_Curiosity_using_ChemCam_Msl20111115_PIA14760_MSL_PIcture-3-br2.jpg "Our robot")

##Commits
###Prefixes:
 Since you are lazy and use GitKraken, there's no point in telling you what prefix to use.
###Content:
  Keep it short and simple. But not stupid. Please.
###Maintenance
  File names are sacred: DO NOT change them.
* * *
##Code standards
 If in doubt, follow the Python Zen (`import this`).       
 If still in doubt, follow the Tao of programming: http://www.mit.edu/~xela/tao.html
###Indentation
 Indentations are made by a tab. Or Two spaces. It doesn't really matter.
###Comments
Comments should respect these parameters:    

+ the language used is English
+ the infinitive is preferred in order to keep things as simple as possible

The structure used to describe a function is as follows:

	/*******************************************
	* function name (possible parameters)
	* the aim of the function
	* possible values returned
	*******************************************/
if you need to comment a single line of code, you have done something horribly wrong... Unless it's THAT line... (or debugging comments. Those are always welcome).
* * *
##Tools
###Camera
pycapture.py can be used to take pictures. 
You can pass the delay as a parameter (default is 10 seconds)
```
	python3 pycapture.py <time>
```    
###Data analysis
stats.py can generate graphs from the images it is pointed to.   
```
	python3 stats.py -flag1 -flag2 -flag3 ... <image_file>.png <graph_name>.png
```       
You will have to select which kind of graph to make and which image to use (you can point it at a directory as well).   
(3D graphs cannot be saved automatically. You can save a 2D snapshot from the GUI. A placeholder name must be put nontheless    
for `<image_file>`)      

- `-prc`: graph displaying the percentages of the total image comprised by each color (black, white, green, "else")
- `-card`: graph displaying for each unique pixel value (the average of the RGB values rounded to the nearest multiple  
               of ten) how many times it appears in the image.
- `-distr`: the selected image will be opened. You must then click on pixels of your choosing and label them as black or white.        
              After you are done choosing data points, the average of the RGB values of each pixel will be displayed on a line             
              (colored according to labelling).   
- `-map`: 3D surface graph displaying on the x,y plane the coordinates, and on the z axis the average of each rgb pixel.      
          (3D graphs cannot be saved automatically. You can save a 2D snapshot from the GUI. A placeholder name must be put nontheless    
          for `<image_file>`)
- `-wir`: 3D wireframe graph displaying on the x,y plane the coordinates, and on the z axis the average of each rgb pixel.      
          (3D graphs cannot be saved automatically. You can save a 2D snapshot from the GUI. A placeholder name must be put nontheless    
          for `<image_file>`)
- `-mapG`: 3D surface graph displaying on the x,y plane the coordinates, and on the z axis the G value of each rgb pixel.      
          (3D graphs cannot be saved automatically. You can save a 2D snapshot from the GUI. A placeholder name must be put nontheless    
          for `<image_file>`)
- `-wirG`: 3D wireframe graph displaying on the x,y plane the coordinates, and on the z axis the G value of each rgb pixel.      
          (3D graphs cannot be saved automatically. You can save a 2D snapshot from the GUI. A placeholder name must be put nontheless    
          for `<image_file>`)
- `-diff`: 3D surface graph displaying on the x,y plane the coordinates, and on the z axis the difference between the maximum and minimum RGB value of each rgb pixel.      

- `-dir`: if this option is used, `<image_file>` should be subsituted with the directory name. If you want to    
             ignore specific files in the directory, add their names immediatly after the flag option as `<!file_to_ignore>`.
***
##Environment setup
###Raspberry PI
####-Enabling the camera    
Install latest kernel, GPU firmware and applications:     

```
	sudo apt-get update
	sudo apt-get upgrade
```   

Open the settings:     

```
	sudo raspy-config
```      

(move with the cursor keys) Select "Interfaces" --> "Camera" and then enable the camera. Reboot.
Test with:   

```
	raspistill -v -o test.jpg
```  

###Git
####-Setting up Git
Download Git (it usally ships with all linux distros): 
```
	  sudo apt-get install git
```
Download the repository (the url can be found on the website):
```
	  git clone <repo url>
```
Configure your account:
```
	  git config --global user.name <name>
```
```
	  git config --global user.email <email>
```
####-Committing changes
  Pull updates from the server.   
  (Always update the local repository when starting the Pi):    

```
	  git pull
```
  Update the server before shutting down (if you have modified anything)
```
      git add -A
      git commit -m "your commit message"
      git push origin master
```
 All the Git commands need to be launched from the repo directory.
###Python
   Remember to use python 3.
```
	  python3 <args>
```
  pycamera.py and pytour.py MUST be launched from a shell.

  The "tkinter", "picamera", "os", "time" modules are all required. As well as all the scipy libraries.  

```
  	  pip3 install <package>
```

###Shared library
  Compile with
```
  	  g++ -std=c++11 -shared -o <libname>.so -fPIC <filename>.cpp
```
Libraries compiled in x86_64 architecture need to be recompiled on ARM.

* * *

##Contributors

+ Luigi
+ Nicola
+ Pietro
+ Martino
+ Rolleri

;)
