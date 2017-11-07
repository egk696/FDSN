function [ size, windowSize, X, TEMP, GYRO, ACCEL, RawData, SensorData1, SensorData2, States1, States2, CurrentState, h1, arduino ] = Configuration(size, windowSize, X, TEMP, GYRO, ACCEL, RawData, SensorData1, SensorData2, States1, States2, CurrentState, h1, arduino)
%Configuration συνάρτηση αρχικοποίησης μεταβλητών
%   Στην συνάρτηση αυτή δημιουργείτε παράθυρο διαλόγου όπου ο χρήστης
%   ορίζει το μέγεθος δειγμάτων που θα ληφθούν & αναλυθούν και την σειριακή
%   θύρα απο την οποία θα γίνει η επικοινωνία με τον κεντρικό κόμβο. Τέλος
%   καλέιτε το σχέδιο του γραφήματος και συνδέεται δυναμικά με της 
%   μεταβλητές που θα χρησιμοποιεί.
    instrreset;
    disp('Configuration: Initilizing workspace and arduino communication...');
    try
        prompt = {'Enter number of samples to record:','Enter window size:','Enter a Serial Port name to connecto to (ex. COM1, COM2...):','Enter Baud Rate of connection:'};
        dlg_title = 'Data Configuration and Arduino Communication';
        num_lines = 1;
        def = {'500','20','COM5','115200'};
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
        pause(0.05);
        arduino = instrfind('Type', 'serial', 'Port', config{3}, 'Tag', '');
        if isempty(arduino)
            arduino = serial(config{3});
        else
            fclose(arduino);
            arduino = arduino(1);
        end
        set(arduino, 'BaudRate', str2num(config{4}));
        set(arduino, 'ReadAsyncMode', 'continuous');
        set(arduino, 'RecordMode', 'append');
        set(arduino, 'Name', 'Arduino-Serial');
        set(arduino, 'RequestToSend', 'off');
        set(arduino, 'Timeout', 30.0);
        clear config prompt dlg_title def num_lines; 
        pause(0.05);
        h1 = hgload('allinone.fig');
        linkdata on;
    catch ConfigErr
        disp(ConfigErr);
    end
end