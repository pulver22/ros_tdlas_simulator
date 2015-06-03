# Gas Dispersion Simulator Framework for ROS #

![PicsArt_1430298523245.jpg](https://bitbucket.org/repo/Ay6onA/images/2976207008-PicsArt_1430298523245.jpg)

Despite recent achievements, the potential of gas-sensitive mobile robots cannot be realized due to the lack of research on fundamental questions. A key limitation is the difficulty to carry out evaluations against ground truth. To test and compare approaches for gas-sensitive robots a truthful gas dispersion simulator is needed. This repository contains a set of ROS software modules for a unified framework to simulate gas dispersion and to evaluate mobile robotics and gas sensing algorithms. Gas dispersion is modeled as a set of particles affected by diffusion, turbulence, advection and gravity. Wind information is integrated as time snapshots computed with any fluid dynamics computation tool. Users can create their own sensing models and integrate them in the simulation framework. As an example of a sensor model, A set of metal oxide (MOX) sensors modules are included in this package. 

Update: now include by default a remote gas sensor modules (TDLAS) 

## INSTRUCTIONS ##

For installation instructions, technical information regarding the gas dispersion simulation process and requirements please consult the documents included in the **DOC** folder

## Revisions ##

Version 1.0 - Initial release

Version 1.1 - Added the TDLAS sensor


## Contact Information ##

Ali Abdul Khaliq

http://aass.oru.se/~aakq/

ali-abdul [dot] khaliq [at] oru [dot] se

Sepideh Pashami

http://aass.oru.se/Research/Learning/shpi

sepideh [dot] pashami [at] oru [dot] se

Dr. Victor Hernandez Bennetts

victor [dot] hernandez [oru] oru [dot] se

http://aass.oru.se/Research/Learning/vrbs.html

Riccardo Polvara

riccardo [dot] polvara [at] mail [dot] polimi [dot] it

http://pulver22.github.io/

Marco Trabattoni

marco [dot] trabattoni [at] mail [dot] polimi [dot] it
