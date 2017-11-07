sp = serial('COM5', 'BaudRate', 57600);
fileID = fopen(sp);
for i=1:10
    %[GX1 GY1 GZ1 AX1 AY1 AZ1 GX2 GY2 GZ2 AX2 AY2 AZ2] = strread(fscanf(sp), '');
    DATA = textscan(fileID, '%s:%d:%d:%f:%f:%f:%f:%f:%f+%s:%d:%d:%f:%f:%f:%f:%f:%f$\n');
end
fclose(sp);