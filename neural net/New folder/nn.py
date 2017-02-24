import csv
import cPickle

class NeuronNetwork:
    def __init__(self,layer):
        self.layer = layer
        self.L = len(layer)
        self.w = [np.random.randn(layer[i+1],layer[i])  for i in range(0,self.L-1)]
        self.b = [np.random.randn(layer[i+1],1)  for i in range(0, self.L - 1)]

    def predict(self,xin):
        x = np.copy(xin).reshape([self.layer[0],1])
        self.listZ = [None]*self.L
        self.listX = [None]*self.L
        self.listX[0] = x
        for i in range(1,self.L):
            self.listZ[i] = np.dot(self.w[i-1],x) + self.b[i-1]
            x =  self.sigmod(self.listZ[i])
            self.listX[i] = x

        return np.copy(self.listX[-1])

    def calCost(self,input,label):
        out = self.predict(input)
        return (out - label)**2/2

    def callDxLastLayer(self,out,label):
        return out - label

    def callDzLastLayer(self, delta):
        return delta * self.sigmod_derivate(self.listX[-1])

    def calGradient(self,x,y):
        out = self.predict(x)
        delta = self.callDxLastLayer(out,y)

        ldz = [None] * self.L
        ldz[-1] = self.callDzLastLayer(delta)

        for l in range(self.L-2,0,-1):
            ldz[l] = np.dot(self.w[l].transpose(),ldz[l+1])*self.sigmod_derivate(self.listX[l])
        ldw = [None]*(self.L-1)
        ldb = [None]*(self.L-1)
        for l in range(0,self.L-1):
            ldw[l] = ldz[l+1]*self.listX[l].transpose()
            ldb[l] = ldz[l+1]
        return [ldw,ldb]

    def train(self,x,y,epochs,learn_rate, loseRate = 1):
        for turn in range(0, epochs):
            #print 'train : epoch ', turn

            sdw = [np.zeros([self.layer[i + 1], self.layer[i]]) for i in range(0, self.L - 1)]
            sdb = [np.zeros([self.layer[i + 1], 1]) for i in range(0, self.L - 1)]
            sz = len(y)
            for i in range(0, sz):
                [ldw, ldb] = self.calGradient(x[i], y[i])
                for i in range(0, self.L - 1):
                    sdw[i] += ldw[i] / sz
                    sdb[i] += ldb[i] / sz

            for i in range(0, self.L - 1):
                self.w[i] -= learn_rate * sdw[i]
                self.b[i] -= learn_rate * sdb[i]

            cost = 0
            for i in range(sz):
                cost += self.calCost(x[i],y[i])
            if turn % 100 == 0:
                print 'avg train cost: ',np.float32(cost/sz)
                learn_rate *= loseRate


    def evaluate(self,input, label):
        cnt = 0
        siz = input.shape[1]
        for i in range(0,siz):
            output = self.predict(input[i,:])
            cnt += np.argmax(output) == label[i]
        return cnt


    def sigmod(self,z):
        return 1/(1+np.exp(-z))

    def sigmod_derivate(self,x):
        return x*(1-x)

    def softmax(self,x):
        y = np.exp(x)
        y /= np.sum(y)
        return y


def loadParams(file):
    f = open(file, 'rb')
    net = cPickle.load(f)
    f.close()
    return net
def save(file, net):
    f = open(file, 'wb')
    cPickle.dump(net, f, protocol=cPickle.HIGHEST_PROTOCOL)
    f.close()


op = raw_input("train (t) or predict (p): ")
if op == 't':
    fileInput = raw_input("input file name: ")
    nn1 = NeuronNetwork([1,3, 2, 1])
    nn2 = NeuronNetwork([2,6, 6, 1])
    in1 = []
    out1 = []
    in2 = []
    out2 = []
    with open(fileInput, 'rb') as csvfile:
        data = csv.reader(csvfile, delimiter=',', quotechar='|')
        for row in data:
            try:
                dis = float(row[0])
                in1.append([dis])
                if row[1] == 'forward':
                    out1.append(0)
                else:
                    out1.append(1)
                    disRigh = float(row[2])
                    disLeft = float(row[3])
                    in2.append([disRigh,disLeft])
                    if row[4] =='right':
                        out2.append(0)
                    else:
                        out2.append(1)
            except:
                pass

    nn1.train(in1, out1, 10000, 0.3)
    nn2.train(in2, out2, 5000, 0.3)
    save("nn.pk",[nn1,nn2])
    print 'success train, stored NN in nn.kk file'
else:
    netFile = raw_input('NN store file: ')
    [nn1, nn2] = loadParams(netFile)
    print 'start predict: '
    while True:
        dis = input("Enter distance: ")

        p = nn1.predict([dis])
        print 'Probability stop is ',p
        if p < 0.5:
            print 'Neuron network predict forward'
        else:
            print "Neuron network predict stop"
            rightDis = input("Enter right dis: ")
            leftDis = input("Enter left dis: ")
            p = nn2.predict([rightDis, leftDis])
            if p < 0.5:
                print 'turn right'
            else:
                print 'turn left'