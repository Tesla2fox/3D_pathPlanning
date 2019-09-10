# import  instance
import  numpy as np

import plotly.plotly as py
import plotly.graph_objs as go
import plotly
import random
from numpy import *
from copy import *
import copy
import colorlover as cl
import plotly.io as pio
# import read_cfg


class Pnt:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def pnt2dict(self):
        dic = dict(x=x, y=y)
        return dic

    def display(self):
        print('x = ', self.x, 'y = ', self.y)


class Circle:
    def __init__(self, pnt=Pnt(), rad=0):
        self.x = pnt.x
        self.y = pnt.y
        self.rad = rad
        self.x0 = self.x - self.rad
        self.y0 = self.y - self.rad
        self.x1 = self.x + self.rad
        self.y1 = self.y + self.rad

    def circle2dict(self):
        dic = dict()
        dic['type'] = 'circle'
        dic['xref'] = 'x'
        dic['yref'] = 'y'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
        dic['line'] = dict(color='rgba(50, 171, 96, 1)')
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


class Rect:
    def __init__(self, pnt=Pnt(), width=0, height=0):
        self.x0 = pnt.x
        self.y0 = pnt.y
        self.x1 = self.x0 + width
        self.y1 = self.y0 + height

    def rect2dict(self):
        dic = dict()
        dic['type'] = 'rect'
        dic['x0'] = self.x0
        dic['y0'] = self.y0
        dic['x1'] = self.x1
        dic['y1'] = self.y1
        dic['line'] = dict(color='rgb(128, 0, 128)')
        return dic


def getLevelColor(level):
    strcolor = 'rgba('
    for i in range(3):
        strcolor = strcolor + str(level * 50) + ','
    strcolor = strcolor + str(1 / level) + ')'
    return strcolor


colorLst = ['white', 'black']


class Env:
    def __init__(self, mat=zeros((2, 2))):
        self.mat = mat
        self.shapeLst = []
        self.drawData = []
        self.annotations = []

    def addTest(self):

        pathTrace = go.Scatter(x=[5],
                               y=[5],
                               mode='lines',
                               line=dict(shape='spline',
                                         width=4),
                               name='Path_' + str(1))
        self.drawData.append(pathTrace)

    def addgrid(self):
        g_color = 'blue'
        row = len(self.mat)
        for i in range(row):
            for j in range(len(self.mat[i])):
                pnt = Pnt(i, j)
                rect = Rect(pnt, 1, 1)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 0.5
                #                rectDic['opacity'] =  1/(int(self.mat[i][j])+1)
                #                rectDic['fillcolor'] = colorLst[int(self.mat[i][j])]
                if (int(self.mat[i][j]) == 1):
                    rectDic['fillcolor'] = 'black'
                #                if(int(self.mat[i][j])==0):
                #                    rectDic['fillcolor'] = colorLst[int(self.mat[i][j])]
                #                getLevelColor(mat[i][j])
                self.shapeLst.append(copy.deepcopy(rectDic))
        print(len(self.shapeLst))

    def addRobotStartPnt(self, lst=[]):
        for i in range(len(lst[0])):
            lst[0][i] = lst[0][i] + 0.5
            lst[1][i] = lst[1][i] + 0.5
            startTrace = go.Scatter(x=[lst[0][i]], y=[lst[1][i]], mode='markers',
                                    marker=dict(symbol='cross-dot', size=20),
                                    name='Robot_' + str(i))
            self.drawData.append(startTrace)

    def addEdges(self, lst=[]):
        mark_x = []
        mark_y = []
        for p in range(len(lst[0])):
            pnt0 = Pnt(lst[0][p] + 0.5, lst[1][p] + 0.5)
            pnt1 = Pnt(lst[2][p] + 0.5, lst[3][p] + 0.5)
            mark_x.append(pnt0.x)
            mark_x.append(pnt1.x)
            mark_y.append(pnt0.y)
            mark_y.append(pnt1.y)
            line = Line(pnt0, pnt1)
            lineDic = line.line2dict()
            #                print(randColor())
            lineDic['line']['color'] = 'rgba(15,15,15,0.5)'
            lineDic['line']['width'] = 3
            self.shapeLst.append(copy.deepcopy(lineDic))
        markTrace = go.Scatter(mode='markers',
                               x=mark_x,
                               y=mark_y,
                               marker=dict(size=3),
                               name='Spanning-Tree')
        self.drawData.append(markTrace)

    def addEdgeInPnt(self, lst=[]):
        mark_x = []
        mark_y = []
        for p in range(len(lst[0])):
            pnt0 = Pnt(lst[0][p], lst[1][p])
            pnt1 = Pnt(lst[2][p], lst[3][p])
            mark_x.append(pnt0.x)
            mark_x.append(pnt1.x)
            mark_y.append(pnt0.y)
            mark_y.append(pnt1.y)
            line = Line(pnt0, pnt1)
            lineDic = line.line2dict()
            lineDic['line']['color'] = 'red'
            lineDic['line']['width'] = 5
            self.shapeLst.append(copy.deepcopy(lineDic))
        markTrace = go.Scatter(mode='markers',
                               x=mark_x,
                               y=mark_y,
                               marker=dict(size=10),
                               name='Spanning-Tree')
        self.drawData.append(markTrace)

    def addGraph(self, robNum=0, lst=[], txtType=False):
        g_color = 'blue'
        bupu = cl.scales[str(robNum)]['seq']['BuPu']
        print(bupu)
        for i in range(robNum):
            for j in range(len(lst[2 * i])):
                pnt = Pnt(int(lst[2 * i][j]), int(lst[2 * i + 1][j]))
                rect = Rect(pnt, 1, 1)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 0.5
                rectDic['fillcolor'] = bupu[i]
                rectDic['opacity'] = 0.6
                if (txtType):
                    self.annotations.append(dict(showarrow=False,
                                                 x=pnt.x + 0.5, y=pnt.y + 0.5,
                                                 text=str(i)))
                else:
                    self.annotations.append(dict(showarrow=False,
                                                 x=pnt.x + 0.5, y=pnt.y + 0.5,
                                                 text=str(pnt.x) + '-' + str(pnt.y)))
                self.shapeLst.append(copy.deepcopy(rectDic))

    def addPath(self, robNum=0, lst=[], txtType=True):
        for i in range(robNum):
            x = lst[2 * i]
            y = lst[2 * i + 1]
            markTrace = go.Scatter(mode='markers+lines',
                                   x=x,
                                   y=y,
                                   marker=dict(size=10),
                                   name='Path_' + str(i + 1))
            #            if(txtType):
            if (False):
                for i in range(len(x)):
                    self.annotations.append(dict(showarrow=False,
                                                 x=x[i], y=y[i],
                                                 text=str(i)))
            self.drawData.append(markTrace)

    def addSTCGraph(self, robNum=0, lst=[], txtType=False):
        g_color = 'blue'
        bupu = cl.scales[str(robNum)]['seq']['BuPu']
        print(bupu)
        for i in range(robNum):
            for j in range(len(lst[2 * i])):
                pnt = Pnt(int(lst[2 * i][j]) * 2, int(lst[2 * i + 1][j]) * 2)
                rect = Rect(pnt, 2, 2)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 1
                rectDic['fillcolor'] = bupu[i]
                rectDic['opacity'] = 0.6
                if (txtType):
                    self.annotations.append(dict(showarrow=False,
                                                 x=pnt.x + 1, y=pnt.y + 1,
                                                 text=str(i)))
                else:
                    self.annotations.append(dict(showarrow=False,
                                                 x=pnt.x + 1, y=pnt.y + 1,
                                                 text=str(int(lst[2 * i][j])) + '-' +
                                                      str(int(lst[2 * i + 1][j]))))

                self.shapeLst.append(copy.deepcopy(rectDic))

    def addNeiGraph(self, robNum=0, lst=[]):
        g_color = 'blue'
        bupu = cl.scales[str(robNum)]['seq']['BuPu']
        print(bupu)
        for i in range(robNum):
            for j in range(len(lst[2 * i])):
                pnt = Pnt(int(lst[2 * i][j]), int(lst[2 * i + 1][j]))
                rect = Rect(pnt, 1, 1)
                rectDic = rect.rect2dict()
                rectDic['line']['color'] = g_color
                rectDic['line']['width'] = 0.5
                rectDic['fillcolor'] = bupu[i]
                rectDic['opacity'] = 1
                self.shapeLst.append(copy.deepcopy(rectDic))

    def drawPic(self, name='env', fileType=True):
        layout = dict()
        layout['shapes'] = self.shapeLst
        layout['xaxis'] = {'range': [0, len(self.mat[0])]}
        layout['yaxis'] = {'range': [0, len(self.mat)]}
        layout['xaxis'] = dict(
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            autotick=True,
            ticks='',
            showticklabels=False)
        layout['yaxis'] = dict(
            scaleanchor="x",
            autorange=True,
            showgrid=False,
            zeroline=False,
            showline=False,
            autotick=True,
            ticks='',
            showticklabels=False)
        # layout['font'] = dict(
        #     # family='sans-serif',
        #     sie=25
        #     # color='#000'
        # )
        layout['autosize'] = False
        layout['height'] = 1000
        layout['width'] = 1000
        layout['annotations'] = self.annotations
        #        print(layout)
        fig = dict(data=self.drawData, layout=layout)
        if (fileType):
            plotly.offline.plot(fig, filename=name + '.html', validate=False)
        else:
            # pio.write_image(fig,name+'.pdf')
            py.image.save_as(fig, filename=name + '.jpeg')

# def drawPath(ins : instance.MCMPInstance, path = []):
#     print('sss')
#     env = Env(ins._mat)
#     env.addgrid()
#     robLst = []
#     robRowLst = [x[0] for x in ins._robPosLst]
#     robColLst = [x[1] for x in ins._robPosLst]
#     robLst.append(robRowLst)
#     robLst.append(robColLst)
#     env.addRobotStartPnt(robLst)
#     robNum = ins._robNum
#
#     # path = []
#     if path == []:
#         pass
#     else:
#         env.addPath(robNum,path)
#     env.drawPic('test')
#     pass

if __name__ == '__main__':
    row = 20
    col = 20
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
    # for rowInd in range(row):
    #     for colInd in range(col):
    #         if (rowInd,colInd) in robPosLst:
    #             obstacleLst.append(0)
    #         else:
    #             obstacleLst.append(np.random.choice([0,1],p =p.ravel()))
    # ins =    instance.MCMPInstance(row,col,obstacleLst,robPosLst)
    #
    # drawPath(ins)
