import StepResponse as SR
import numpy as np
from threading import Lock

class DMC:
    
    U_MIN = 0.0
    U_MAX = 100.0
    D = int(150)
    Dz = int(40)

    def __init__(self):
        self._mutex = Lock()

        self._deltaUp = 0
        self._deltaZp = 0

        self._Uk_1 = 0.0
        self._Zk_1 = 0.0

        self._ke = 0
        self._Ku = 0
        self._Kz = 0

        self._yzad = 25.0

    def init_regulator(self, N, Nu, lmbd):
        M = np.zeros((N,Nu))
        for i in range(N):
            for j in range(Nu):
                if j > i:
                    M[i][j] = 0.0
                else:
                    M[i][j] = SR.Su[i-j]
        
        K = np.matmul(np.linalg.inv(M.T @ M + lmbd * np.identity(Nu)), (M.T))

        K1 = K[0,:]

        ke = 0
        for i in range(N):
            ke = ke + K1[i]

        Mp = np.zeros((N,DMC.D - 1))
        for i in range(N):
            for j in range(DMC.D-1):
                if i + j < (DMC.D-1):
                    Mp[i,j] = SR.Su[i+j+1] - SR.Su[j]
                else:
                    Mp[i,j] = SR.Su[DMC.D-1] - SR.Su[j]


        Mzp = np.zeros((N,DMC.Dz))
        for i in range(N):
            Mzp[i,0] = SR.Sz[i]
            for j in range(1,DMC.Dz):
                if i + j < (DMC.Dz-1):
                    Mzp[i,j] = SR.Sz[i+j] - SR.Sz[j-1]
                else:
                    Mzp[i,j] = SR.Sz[DMC.Dz-1] - SR.Sz[j-1]


        Ku = K1 @ Mp
        Kz = K1 @ Mzp

        self._mutex.acquire()

        try:
            self._deltaUp = np.zeros((DMC.D-1, 1))
            self._deltaZp = np.zeros((DMC.Dz, 1))
            self._ke = ke
            self._Ku = Ku
            self._Kz = Kz
        finally:
            self._mutex.release()

    def calculate_U(self,y, z):
        self._mutex.acquire()
        try:

            deltaZ = z - self._Zk_1
            self._deltaZp = np.insert(self._deltaZp, 0, deltaZ, axis=0)[0:DMC.Dz,:]

            self._Zk_1 = z

            deltaU = (self._ke * (self._yzad - y) - self._Ku @ self._deltaUp - self._Kz @ self._deltaZp)[0]

            u = self._Uk_1 + deltaU

            if u > DMC.U_MAX:
                u  = DMC.U_MAX
                deltaU = DMC.U_MAX - self._Uk_1
            elif u < DMC.U_MIN:
                u = DMC.U_MIN
                deltaU = DMC.U_MIN - self._Uk_1

            self._deltaUp = np.insert(self._deltaUp, 0, deltaU, axis=0)[0:(DMC.D-1),:]

            self._Uk_1 = u

        finally:
            self._mutex.release()

        return u

    def set_yzad(self, yzad):
        self._mutex.acquire()
        try:
            self._yzad = yzad
        finally:
            self._mutex.release()




        


