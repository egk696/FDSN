function  ReadAndAnalyze(size, windowSize, arduino, h1, RawData, SensorData1, SensorData2, States1, States2, CurrentState, TEMP, GYRO, ACCEL)
%ReadAndAnalyze συνάρτηση συλλογής δεδομένων και ανάλυσης
%   Στην συνάρτηση αυτή εκτελείται ένας βρόγχος επανάληψης για όσο είναι το
%   δηλωμένο μέγεθος δειγμάτων προς ανάλυση στην μεταβλητή size. Κατα την
%   διάρκεια του βρόγχου γίνεται ανάγνωση και προσωρινή αποθήκευση των
%   δεδομένων της σειριακής θύρας, στην συνέχεια χωρίζονται σε 2 πίνακες
%   ανάλογα με τον κόμβο ασθενή που προέρχονται, αποστέλονται στην
%   συνάρτηση StateAnalysis για την ανάλυση της κινητικότητας του ασθενή
%   και τέλος γίνεται ανανέωση του γραφήματος.
    time = 0;
    disp('Arduinoread: Gathering and analyzing data...');
    fopen(arduino);
    for j=1:size
        tic;
        while(arduino.BytesAvailable == 0)
        end
        try
            RawData(1,:) = fscanf(arduino, '%d:%d:%d:%d:%d:%d:%d:%d:%d+%d:%d:%d:%d:%d:%d:%d:%d:%d$\n');
            disp(RawData(1,:));
            disp(time);
            SensorData1(j,:) = RawData(1, 2:9);
            SensorData2(j,:) = RawData(1, 11:18);
            assignin('base', 'SensorData1', SensorData1);
            assignin('base', 'SensorData2', SensorData2);
            if(j>windowSize && mod(j, windowSize) == 0)
                States1(1:j-1,:) = StateAnalysis(SensorData1(:,ACCEL),SensorData1(:,GYRO),1,windowSize,j);
                States2(1:j-1,:) = StateAnalysis(SensorData2(:,ACCEL),SensorData2(:,GYRO),1,windowSize,j);
                CurrentState(1) = 2^0*States1(j-1,1)+2^1*States1(j-1,2)+2^2*States1(j-1,3);
                CurrentState(2) = 2^0*States2(j-1,1)+2^1*States2(j-1,2)+2^2*States2(j-1,3);
                assignin('base', 'States1', States1);
                assignin('base', 'States2', States2);
                assignin('base', 'CurrentState', CurrentState);
            end
            refreshdata(h1);
            drawnow expose update
        catch ReadAndAnalyzeErr
            disp(ReadAndAnalyzeErr);
            break
        end
        time = time + toc;
    end
    fclose(arduino);
end