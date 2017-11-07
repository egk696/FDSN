function windowState = WindowState(WAccel, WGyro, WLength)
%WindowState συνάρτηση ανάλυσης κινητικότητας ασθενή σε ένα παραθύρο δείγματος
%   Στην συνάρτηση αυτή εκτελείται ο αλγόριθμος ανάλυσης που περιγράφεται
%   στο κεφάλαιο 4.3.1. Πρώτα βρίσκονται οι μεταβολές στο σήμα WGyro, στην
%   συνέχεια βρίσκεται η συχνότητα που εμφανίζονται οι μεταβολές σε αυτό το
%   παράθυρο ανάλυσης και τέλος βάση λογικών συνθηκών και με την χρήση
%   καταφλιών επιστρέφεται η λογική κατάσταση της κινητικότητας του ασθενή
%   για το παράθυρο του δείγματος αυτού.
    dGyro = diff(WGyro);
    dGyroF = DiffGyroFrequency(dGyro);
    idling = WAccel(1:WLength,3)==1 & dGyroF(2) < 0.25 & dGyroF(3) < 0.25;
    moving = ~idling & WAccel(1:WLength,3)>=1;
    falling = (~moving & ~idling) & (WAccel(1:WLength,1) >=1 | WAccel(1:WLength,2) >=1);
    windowState = [idling'; moving'; falling']';
end