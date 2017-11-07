% ARDUINOREAD Code for communicating with Arduino.

% Make sure objects are cleaned
instrreset;

% Configuration dialog
prompt = {'Enter a Serial Port name to connecto to (ex. COM1, COM2...):','Enter Baud Rate of connection:'};
dlg_title = 'Arduino Communication Configuration';
num_lines = 1;
def = {'COM5','115200'};
config = inputdlg(prompt,dlg_title,num_lines,def);

% Find a serial port object.
obj1 = instrfind('Type', 'serial', 'Port', config{1}, 'Tag', '');

% Create the serial port object if it does not exist
% otherwise use the object that was found.
if isempty(obj1)
    obj1 = serial(config{1});
else
    fclose(obj1);
    obj1 = obj1(1);
end

% Configure instrument object, obj1.
set(obj1, 'BaudRate', str2num(config{2}));
set(obj1, 'ReadAsyncMode', 'continuous');
set(obj1, 'RecordMode', 'append');
set(obj1, 'Name', 'Arduino-Serial');
set(obj1, 'RequestToSend', 'off');
set(obj1, 'Timeout', 30.0);

% Connect to instrument object, obj1.
fopen(obj1);
clear config prompt dlg_title def num_lines;

% For testing read out.
%testConnectionDataStr = fscanf(obj1, '%s\n')

% Gather data.
time=0;
for j=1:size
    %j
    tic;
    %Checking to refresh data.
    while(obj1.BytesAvailable == 0)
         %pause(0.05);
    end
    % Communicating with instrument object, obj1.
    try
        RawData(1,:) = fscanf(obj1, '%d:%d:%d:%d:%d:%d:%d:%d:%d+%d:%d:%d:%d:%d:%d:%d:%d:%d$\n');
        %SensorData1(j,:) = RawData(1, 2:9);
        evalin('base', 'SensorData1(j,:) = RawData(1, 2:9);');
        %SensorData2(j,:) = RawData(1, 11:18);
        evalin('base', 'SensorData2(j,:) = RawData(1, 11:18);');
        %clear RawData;
        if(j>windowSize && mod(j, windowSize) == 0)
            evalin('base','States1(1:j-1,:) = StateAnalysis(SensorData1(:,ACCEL),SensorData1(:,GYRO),1,windowSize,j);');
            evalin('base','States2(1:j-1,:) = StateAnalysis(SensorData2(:,ACCEL),SensorData2(:,GYRO),1,windowSize,j);');
            evalin('base','CurrentState(1) = 2^0*States1(j-1,1)+2^1*States1(j-1,2)+2^2*States1(j-1,3);');
            evalin('base','CurrentState(2) = 2^0*States2(j-1,1)+2^1*States2(j-1,2)+2^2*States2(j-1,3);');
            dlmwrite('CurrentState.txt', CurrentState, 'delimiter', '+', 'precision', '%d');
            %pause(0.1);
        end
        refreshdata(h1);
        drawnow expose update
    catch err
        %DO NOTHING
        err
        break
    end
    time = time + toc;
end

% Disconnect from instrument object, obj1.
fclose(obj1);

% Clean up all objects.
delete(obj1);