import plotly.graph_objects as go
import plotly
import numpy as np
# import MCMPinstance
import  colorlover as cl

class Pnt:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y
    def pnt2dict(self):
        dic = dict(x=x, y=y)
        return dic
    def display(self):
        print('x = ', self.x, 'y = ', self.y)

class Rect:
    def __init__(self, pnt=Pnt(), width=0, height=0):
        self.x0 = pnt.x
        self.y0 = pnt.y
        self.x1 = self.x0 + width
        self.y1 = self.y0 + height

    def goShape(self):
        dic = go.layout.Shape()
        dic['type'] = 'rect'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
        dic['line'] = dict(color='rgb(128, 0, 128)')
        return dic

    def rect2dict(self):
        dic = dict()
        dic['type'] = 'rect'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
        dic['line'] = dict(color='rgb(128, 0, 128)')
        return dic


class Line:
    def __init__(self, pnt0=Pnt(), pnt1=Pnt()):
        self.x0 = pnt0.x
        self.y0 = pnt0.y
        self.x1 = pnt1.x
        self.y1 = pnt1.y

    def line2dict(self):
        dic = dict()
        dic['type'] = 'line'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
        dic['line'] = dict(color='rgb(128, 0, 128)')
        return dic

class Env:
    def __init__(self, mat):
        self._mat = mat
        self._shapeLst= []
        self._scatterLst = []
        self.annotations = []

    def addgrid(self):
        g_color = 'blue'
        row = len(self._mat)
        for i in range(row):
            for j in range(len(self._mat[i])):
                pnt = Pnt(i, j)
                rect = Rect(pnt, 1, 1)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 0.5
                #                rectDic['opacity'] =  1/(int(self.mat[i][j])+1)
                #                rectDic['fillcolor'] = colorLst[int(self.mat[i][j])]
                if (int(self._mat[i][j]) == 1):
                    rectDic['fillcolor'] = 'black'
                #                if(int(self.mat[i][j])==0):
                #                    rectDic['fillcolor'] = colorLst[int(self.mat[i][j])]
                #                getLevelColor(mat[i][j])

                self._shapeLst.append(rectDic)
    def addHGrid(self,h_mat):
        row = len(self._mat)
        h_set = set()
        for i in range(row):
            for j in range(len(self._mat[i])):
                h_set.add(h_mat[i][j])

        bupu =  cl.scales[str(len(h_set))]['div']['PRGn']

        h_list  = list(h_set)
        print(h_list)
        sorted(h_list)

        g_color = 'blue'
        row = len(self._mat)
        for i in range(row):
            for j in range(len(self._mat[i])):
                pnt = Pnt(i, j)
                rect = Rect(pnt, 1, 1)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 0.5
                #                rectDic['opacity'] =  1/(int(self.mat[i][j])+1)
                #                rectDic['fillcolor'] = colorLst[int(self.mat[i][j])]
                lvl = h_list.index(h_mat[i][j])
                rectDic['fillcolor'] = bupu[lvl]
                rectDic['opacity'] = 0.6

                if (int(self._mat[i][j]) == 1):
                    rectDic['fillcolor'] = 'black'
                    rectDic['opacity'] = 0.9

                self._shapeLst.append(rectDic)


    def addRobotStartPnt(self, lst=[]):
        for robID in range(len(lst)):
            startTrace = go.Scatter(x=[lst[robID][0]+0.5], y=[lst[robID][1]+0.5], mode='markers',
                                    marker=dict(symbol='cross-dot', size=20),
                                    name='Robot_' + str(robID))
            self._scatterLst.append(startTrace)
    def addEdges(self, lst=[]):
        mark_x = []
        mark_y = []
        for p in range(len(lst)):
            pnt0 = Pnt(lst[p][0] + 0.5, lst[p][1] + 0.5)
            pnt1 = Pnt(lst[p][2] + 0.5, lst[p][3] + 0.5)
            mark_x.append(pnt0.x)
            mark_x.append(pnt1.x)
            mark_y.append(pnt0.y)
            mark_y.append(pnt1.y)
            line = Line(pnt0, pnt1)
            lineDic = line.line2dict()
            #                print(randColor())
            lineDic['line']['color'] = 'darkred'
            lineDic['line']['width'] = 3
            self._shapeLst.append(lineDic)

        markTrace = go.Scatter(mode='markers',
                               x=mark_x,
                               y=mark_y,
                               marker=dict(size=3),
                               name='Spanning-Tree')
        self._scatterLst.append(markTrace)

    def addEdgesInPnt(self,lst = []):
        mark_x = []
        mark_y = []
        for p in range(len(lst)):
            pnt0 = Pnt(lst[p][0], lst[p][1])
            pnt1 = Pnt(lst[p][2], lst[p][3])
            mark_x.append(pnt0.x)
            mark_x.append(pnt1.x)
            mark_y.append(pnt0.y)
            mark_y.append(pnt1.y)
            line = Line(pnt0, pnt1)
            lineDic = line.line2dict()
            #                print(randColor())
            lineDic['line']['color'] = 'darkred'
            # lineDic['line']['color'] = 'rgba(15,15,15,0.5)'
            lineDic['line']['width'] = 3
            self._shapeLst.append(lineDic)

        markTrace = go.Scatter(mode='markers',
                               x=mark_x,
                               y=mark_y,
                               marker=dict(size=3),
                               name='Spanning-Tree')
        self._scatterLst.append(markTrace)

    def addSinglePathInd(self,pathInd = []):

        x = [path_unit[0]+0.5 for path_unit in pathInd]
        y = [path_unit[1]+0.5 for path_unit in pathInd]

        markTrace = go.Scatter(mode='markers+lines',
                               x=x,
                               y=y,
                               # marker=dict(size=10),
                               name='Path_single' )
        self._scatterLst.append(markTrace)
    def addSinglePathInPnt(self,pathInd = []):

        x = [path_unit[0] for path_unit in pathInd]
        y = [path_unit[1] for path_unit in pathInd]
        print(x)
        print(y)
        markTrace = go.Scatter(mode='markers+lines',
                               x=x,
                               y=y,
                               # color="species",
                               # color = 'darkred',
                               # marker=dict(size=10),
                               line=dict(width=3,color ='darkred'),
                               name='Path_single' )
        self._scatterLst.append(markTrace)

    def drawPic(self, name='env', showBoolean = True,saveBoolean = False,):
        layout = dict()
        layout['shapes'] = self._shapeLst
        # layout['xaxis'] = dict(showgrid=False)

        layout['xaxis'] = dict(
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            # autotick=True,
            ticks='',
            showticklabels=False)

        layout['yaxis'] = dict(
            scaleanchor="x",
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            # autotick=True,
            ticks='',
            showticklabels=False)
        layout['xaxis']['range'] = [0, len(self._mat[0])]
        layout['yaxis']['range'] = [0, len(self._mat)]

        layout['font'] = dict(
            family='sans-serif',
            size=25,
            color='#000'
        )
        layout['autosize'] = False
        layout['height'] = 1000
        layout['width'] = 1000
        layout['template'] = "plotly_white"
        # layout['annotations'] = self.annotations
        #        print(layout)
        fig = go.Figure(data = self._scatterLst, layout = layout)

        if showBoolean:
            fig.show()
        if saveBoolean:
            fig.write_image('fig.pdf')


# def drawPic(ins: MCMPinstance.MCMPInstance, singlePathInd = None, edgeLst = None):
#     env = Env(ins._mat)
#     env.addgrid()
#     env.addRobotStartPnt(ins._robPosLst)
#     if singlePathInd != None:
#         env.addSinglePathInd(singlePathInd)
#         # pass
#     if edgeLst != None:
#         # raise Exception('xxx')
#         env.addEdges(edgeLst)
#     else:
#         pass
#         # raise  Exception('ssss')
#     env.drawPic(name = 'pic')

# def drawSTCPic(ins:MCMPinstance.MCMPInstance, edgePntLst = None):
#     env = Env(ins._mat)
#     env.addgrid()
#     env.addEdgesInPnt(edgePntLst)
#     env.drawPic(name = 'pic')
#     raise Exception('xx')

def drawHeightPic(mat,h_mat = [],pathLst = []):
    env = Env(mat)
    if h_mat == []:
        env.addgrid()
    else:
        env.addHGrid(h_mat)
    env.addSinglePathInPnt(pathLst)
    env.drawPic()




if __name__ == '__main__':

    row = 40
    col = 40
    robNum = 2
    p = np.array([0.9,0.1])
    np.random.seed(1000)
    rob_x = np.random.randint(20,size = robNum)
    rob_y = np.random.randint(20,size = robNum)
    robPosLst = []
    for i in range(robNum):
        robPosLst.append((rob_x[i],rob_y[i]))
    # 1 means obstacles
    # 0 means way
    print(robPosLst)
    obstacleLst = []
    for rowInd in range(row):
        for colInd in range(col):
            if (rowInd,colInd) in robPosLst:
                obstacleLst.append(0)
            else:
                obstacleLst.append(np.random.choice([0,1],p =p.ravel()))
    _row = row
    _col = col
    _obstacleLst = obstacleLst
    _robNum = len(robPosLst)
    _mat = np.zeros([_row, _col])
    # print(self._mat)
    ind = 0
    for rowInd in range(row):
        for colInd in range(col):
            _mat[rowInd][colInd] = _obstacleLst[ind]
            ind = ind + 1

    env = Env(_mat)
    env.addgrid()
    env.addRobotStartPnt(robPosLst)
    env.drawPic(showBoolean= True, saveBoolean= False)
    print('ss')


