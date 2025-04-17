class hashtable:
    def__init__(self):
        self.hashtable=[None]*self.m
        self.elecount=0
        self.comparison=0
        print(self.hashtable)
    def hashFunction(self,key):
    return key % self.m
        
    def isfull(self):
        if self.elecount==self.m:
            return True
        else:
            return False        
    def linearprobe(self,key,data):
    index=self.hashFunction(key)
    compare=0
    while(self.hashtable[index]!=None):
    
    index=index+1
    compare=compare+1
    if(index==self.m):
    index=0
    self.hashtable[index]=[key,data]
    self.elecount+=1
    print("data inserted at",index)
    print(self.hashtable)
    print("no of comparison=",compare)
    

    def getline (self,key,data):
        index=self.hashFunction(key)
        
        while self.hashtable[index]==[key,data]:
            if self.hashtable[index]==[key,data]
                return index
index=(index+1)% self.m
return None

    def quadraticprobe(self,key,data):
    index=self.hashfunction(key)
    compare=0
    i=0
    while(self.hashtable[index]!=None):
    
    index=(index+i*i)%self.m
    compare=compare+1
    i=i+1
    
    self.hashtable[index]=[key,data]
