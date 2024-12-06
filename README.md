# tt | tasktracker utility for linux
this is a simple task tracker written in c++<br/> 
it uses json to store tasks in a file (.tasks) in users home directory ("$HOME")<br/>
<br/>
##Installation
1. clone this repo and cd to the project's folder.
2. compile `/src/main.cpp`:
`g++ src/main.cpp -o tt`
3. copy the output to ur binary folder:
`sudo cp tt /usr/bin`
<br/>
##Usage
###add a new task
`tt add "task's description here"`
this generates a random id for the task and adds it to the tasks data.

###remove a task
`tt remove <task_id>`
this removes the task related to the id you provide<br/>
you can find the id using list commands.

###update a task
`tt update <task_id> "new description"`
this updates the existing task.

###list tasks
####list
`tt list`
this will list all the tasks.

####listw
`tt listw`
this will list tasks which are marked as wip.

####listd
`tt listd`
this will list tasks which are marked as done.

###specify task's state
####markw
`tt markw <task_id>`
mark a task as wip.

####markd
`tt markd <task_id>`
mark a task as done.

###reset tasks data
`tt reset`
this will overwrite the tasks data with an empty task array.

<br/>
##Possible issues/notices
1. make sure the tasks file exists if something went wrong: <br/>
it should be at `/home/$USER/.tasks`
2. you can always regenerate tasks data using:
`tt reset`
3. this project uses nlohmann json library to parse and modify tasks data

<br/>
##:)
i made this project as a practice.<br/>
feel free to use the codes elsewhere.<br/>
i might later make a gui or some improvement.<br/>
<3
