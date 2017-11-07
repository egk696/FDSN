% ARDUINOREAD Code for managing data and plots with Arduino.

% Make sure workspace is clear.
%msg = 'clearing workspace';
clear all;
clear history;
try
    % Initialize workspace.
    %msg = 'initializing workspace';
    % Configuration dialog
    prompt = {'Enter number of samples to record:','Enter window size:'};
    dlg_title = 'Data Configuration';
    num_lines = 1;
    def = {'500','20'};
    config = inputdlg(prompt,dlg_title,num_lines,def);
    size = str2double(config{1});
    windowSize = str2double(config{2});
    X = 1:size;
    TEMP = 1:2;
    GYRO = 3:5;
    ACCEL = 6:8;
    RawData = zeros(1,18);
    SensorData1 = zeros(size, 8);
    SensorData2 = zeros(size, 8);
    States1 = false(size, 3);
    States2 = false(size, 3);
    CurrentState = zeros(1,2);
    %Initialize plot
    % Create figure
    h1 = hgload('allinone.fig');
    linkdata on;
    refreshdata(h1);
catch err
    err
end
