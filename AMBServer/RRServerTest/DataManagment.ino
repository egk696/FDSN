void receiveDataWord(int id){
  if(id==1){
    if(part2==""){
      do{
        sendRequest("clie1", "REQ1");
        part1 = getResponse();
      }
      while(part1=="" || !part1.startsWith("1:"));
    }
#ifdef DEBUG
    Serial.println("--------------");
#endif
    if(part1!=""){
      do{
        sendRequest("clie1", "SEC1");
        part2 = getResponse();
      }
      while(part2=="" || part2.indexOf(":")==-1 || part2.endsWith(":"));
    }
    if(part1!="" && part2!=""){
      data = part1+part2;
      part1 = "";
      part2 = "";
#ifdef DEBUG
      Serial.println("--------------");
      Serial.println("--------------");
      Serial.println("Word = " + data);
#endif
    }
  }
  else{
    if(part2==""){
      do{
        sendRequest("clie2", "REQ2");
        part1 = getResponse();
      }
      while(part1=="" || !part1.startsWith("2:"));
    }
#ifdef DEBUG
    Serial.println("--------------");
#endif
    if(part1!=""){
      do{
        sendRequest("clie2", "SEC2");
        part2 = getResponse();
      }
      while(part2=="" || part2.indexOf(":")==-1 || part2.endsWith(":"));
    }
    if(part1!="" && part2!=""){
      data = part1+part2;
      part1 = "";
      part2 = "";
#ifdef DEBUG
      Serial.println("--------------");
      Serial.println("--------------");
      Serial.println("DataWord = " + data);
#endif
    }
  }
}





