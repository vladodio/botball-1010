# basically just don't use this
class config():

    def __init__(self, pathOfConfig="/home/alex/config.ini"):
        try:
            self.config = open(pathOfConfig, "r")
        except:
            print("VALID FILE????")

    def __del__(self):
        self.config.close()

    def get(self, header, variable, returnType="f"):
        #ranges on searches are prob off
        headerFound=False
        valueLength=0
        isolatedValue=""
        found=False
        try:
            for line in self.config:
                if(not headerFound and ("[" == line[0]) and (line[1:len(header)+2] == (header + "]"))):
                    headerFound=True
                    continue
                if(headerFound and line[0] == "["):
                    break
                if(headerFound and (line[:len(variable)+1] == (variable + "="))):
                    valueLength=len(line)-len(variable)-1
                    print(line[-valueLength:])
                    print(valueLength)
                    isolatedValue=line[-valueLength:]
                    found=True
                    break
        except:
            pass

        if(not headerFound):
            raise Exception("Header not found.")
        if(not found):
            raise Exception("Variable was not found.")

        if(returnType=="f"):
            return(float(isolatedValue))
        elif(returnType=="i"):
            return(int(isolatedValue))
        elif(returnType=="s"):
            return(str(isolatedValue))
        else:
            return(isolatedValue)
