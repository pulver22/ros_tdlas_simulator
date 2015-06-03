load '/home/ali/ros_workspace/odor_simulation/simulated_MOX/src/sensor_log.txt'

figure;
plot(sensor_log(:,1),'Linewidth',2,'color','r');
hold on,
plot(sensor_log(:,2),'Linewidth',2,'color','g');
hold on;
plot(sensor_log(:,3),'Linewidth',2,'color','b');

