function DPSSApplication()
%DPSSApplication συνάρτηση αρχικοποίησης προγράμματος και έναρξης ανάλυσης
%   Στην συνάρτηση αυτή γίνεται καθαρισμός του workspace του MATLAB,
%   δηλώνονται οι μεταβλητές που θα χρησιμοποιηθούν 
%   και αρχικοποιούνται καλώντας την συνάρτηση Configuration
%   και τέλος καλείται η συνάρτηση ReadAndAnalyze η οποία διαβάζει και
%   αναλυεί τις μετρήσεις για όσα δείγματα έχουν δηλωθεί προς ανάλυση.
    clc;
    clear all;
    global size;
    global windowSize;
    global X;
    global TEMP;
    global GYRO;
    global ACCEL;
    global RawData;
    global SensorData1;
    global SensorData2;
    global States1;
    global States2;
    global CurrentState;
    global arduino;
    global h1;
    [size, windowSize, X, TEMP, GYRO, ACCEL, RawData, SensorData1, SensorData2, States1, States2, CurrentState, h1, arduino] = Configuration(size, windowSize, X, TEMP, GYRO, ACCEL, RawData, SensorData1, SensorData2, States1, States2, CurrentState, h1, arduino);
    assignin('base', 'size', size);
    assignin('base', 'windowSize', windowSize);
    assignin('base', 'X', X);
    assignin('base', 'TEMP', TEMP);
    assignin('base', 'GYRO', GYRO);
    assignin('base', 'ACCEL', ACCEL);
    assignin('base', 'RawData', RawData);
    assignin('base', 'SensorData1', SensorData1);
    assignin('base', 'SensorData2', SensorData2);
    assignin('base', 'States1', States1);
    assignin('base', 'States2', States2);
    assignin('base', 'CurrentState', CurrentState);
    assignin('base', 'arduino', arduino);
    assignin('base', 'h1', h1);
    assignin('base', 'j', j);
    refreshdata(h1);
    drawnow expose update
    ReadAndAnalyze(size, windowSize, arduino, h1, RawData, SensorData1, SensorData2, States1, States2, CurrentState, TEMP, GYRO, ACCEL);
    delete(arduino);
end