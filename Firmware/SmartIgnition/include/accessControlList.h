String allowedNUIDs[50];
int currentPointer=0;
bool lastCardAllowed=false;
void addAllowedNUID(String NUID){
    allowedNUIDs[currentPointer]=NUID;
    currentPointer++;
}
void setupAccessControlList(){
    for (int i=0;i<50;i++){
        allowedNUIDs[i]=String("0");
    }
}

bool checkAccess(String nuid){
    for (int i=0;i<currentPointer;i++){
        if(allowedNUIDs[i].indexOf(nuid)>=0 || nuid.indexOf(allowedNUIDs[i])>=0){
            lastCardAllowed=true;
            return true;
        }
    }
    return false;
}