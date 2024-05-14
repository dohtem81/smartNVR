<H1>smartNVR</H1>
This code provides fucntionality to connect to specified cameras and provide non-stop recording to pre-configured lengts of avi files.

<H2>Future functionality</H2>
Will provide interface to yolo model (probably Darknet) to start and stop triggers for recording when detected person, animal etc (to be configured). Will also provide data to front end (web all, most probably blazor) providing real time view of selected camera from the list. smartNVR module will also log events into DB (most probably Postgres)

<H2>What is not here</H2>
Plan to use submodules to provide core source code. In order to be able to deploy provate project containing configuration. Will make public project as an example of the config.
Plan is to use Docker. As another submodule all docker files and docker compose.
Idea is to run this as microservices type of architecture. Was planning to use Redis as comm bus (license changes will require investigation if I still can use it). smartNVR front end backends would run on regular server/raspberryPi, while Darknet would use NVidia Jetson NANO. Using Redis would provide easy comm bus where adding additional functionality would be easy, not requiring to worry about IP addresses and adding code. Redis would be password protected and encrypted.

<H2>Why?</H2>
Of course there are many similair projects. Why do I even do that? Just for fun, and to implement something to learn new thing or document what I already know. Maybe somebody else will have some good idea out of this one.

<H1>Stay tuned for updates :)</H1>
