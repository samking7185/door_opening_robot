# door_opening_robot
This is a repo for the door opening robot ROS packages.

**Prerequisite**
- Ubuntu
- ROS Noetic
- Linux compatible joystick 

**Joystick Specifications**
- Linux compatible
- Publishes to js0
- Left Joystick Up and Down
  - Axis [1]
  - Linear motion of base
- Left Joystick Up and Down
  - Axis [0]
  - Angular motion of base
- Right Joystick Up and Down
  - Axis [4]
  - Vertical motion of mechanism
- Right Joystick Up and Down
  - Axis [3]
  - Horizontal motion of mechanism

**Robot Operation**
```
source devel/setup.bash
roslaunch do_operation door_opening_control.launch
```
