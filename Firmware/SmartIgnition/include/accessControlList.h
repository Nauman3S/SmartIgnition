String allowedNUIDs[50];
int currentPointer=0;
void addAllowedNUID(String NUID){
    allowedNUIDs[currentPointer]=NUID;
    currentPointer++;
}
void setupAccessControlList(){
    for (int i=0;i<50;i++){
        allowedNUIDs[i]=String("0");
    }


    
}
