function States = StateAnalysis(Accel, Gyro, frameStart, frameStep, frameCount)
%StateAnalysis συνάρτηση ανάλυσης ληφθέντος δείγματος με την χρήση
%   κινούμενου παραθύρου.
%   Στην συνάρτηση αυτή εκτελείται ένας βρόγχος επανάληψης για όσα δείγματα
%   μετρήσεων έχουν ληφθεί μέχρι την παρούσα στιγμή (frameCount) στον οποίο
%   καλείται η συνάρτηση WindowState. Τέλος η συνάρτηση αυτή επιστρέφει τις
%   λογικές καταστάσεις για την κινητικότητα του ασθενή για το δείγμα που
%   έχει ληφθεί.
    for i=frameStart:frameStep:frameCount
        if(i>1)
            WStart = i-1;
        else
            WStart = i;
        end
        IndexStart = WStart;
        IndexFinish = IndexStart+frameStep-1;
        States(IndexStart:IndexFinish,:) = WindowState(Accel(WStart:(WStart+frameStep),:), Gyro(WStart:(WStart+frameStep),:), frameStep);
    end
end