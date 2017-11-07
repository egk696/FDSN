function frequency = DiffGyroFrequency(dGyro)
    countX = 0;
    countY = 0;
    countZ = 0;
    for i=1:length(dGyro(:,1))
        if(abs(dGyro(i,1)) > 0)
            countX = countX + 1;
        end
    end
    for i=1:length(dGyro(:,2))
        if(abs(dGyro(i,2)) > 0)
            countY = countY + 1;
        end
    end
    for i=1:length(dGyro(:,3))
        if(abs(dGyro(i,3)) > 0)
            countZ = countZ + 1;
        end
    end
    frequency = [countX/length(dGyro(:,1));countY/length(dGyro(:,2));countZ/length(dGyro(:,3))];
end