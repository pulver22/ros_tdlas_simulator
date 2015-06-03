clc;
files = dir('/home/victor/OpenFOAM/quadcopter-2obs-3d/CSV/*.csv');

for i=1:length(files)
    A = importdata(files(i).name, ',', 1);
    %eval(['load ' files(i).name ' -ascii']);
    U = zeros(160, 40);
    W = zeros(160, 40);
    V = zeros(160, 40);
    for j=1:6240
        x = int32((A.data(j,5)-0.05)/0.1);
        y = int32((A.data(j,6)-0.05)/0.1);
        x = x+1;
        y = y+1;
        U(x, y) = A.data(j,2);
        W(x, y) = A.data(j,3);
        V(x, y) = A.data(j,4);
    end
    
    str_U = strcat(files(i).name, '_U');
    str_W = strcat(files(i).name, '_W');
    str_V = strcat(files(i).name, '_V');
    save(str_U,'U', '-ASCII');
    save(str_W,'W', '-ASCII');
    save(str_V,'V', '-ASCII');
    %eval(['save ' str_U U ' -ascii']);
    %eval(['save ' str_W W ' -ascii']);
    %eval(['save ' str_V V ' -ascii']);
end
