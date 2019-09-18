import readcfg as rd
import  numpy as np
import drawEnv
from drawEnv import  drawHeightPic
from collections import  Counter

if __name__ == '__main__':

    conFileName =  "D:\\VScode\\3D_pathPlanning\\debugMsg\\grid.dat"
    rd_cfg = rd.Read_Cfg(conFileName)

    maxRow = int(rd_cfg.getSingleVal('maxRow'))
    maxCol = int(rd_cfg.getSingleVal('maxCol'))
    mat = np.zeros((maxRow,maxCol),dtype=int)
    h_mat = np.zeros((maxRow,maxCol),dtype=int)

    list_row = []
    list_col = []
    list_row_ob = []
    list_col_ob = []

    list_x = []
    list_y = []
    list_z = []

    rd_cfg.get("row",list_row)
    rd_cfg.get("col",list_col)
    rd_cfg.get("obRow",list_row_ob, dtype = 'int')
    rd_cfg.get("obCol",list_col_ob, dtype = 'int')
    # print(list_row_ob)
    rd_cfg.get("x",list_x, dtype = 'float')
    rd_cfg.get("y",list_y)
    rd_cfg.get("z",list_z, dtype = 'float')

    print(list_z)
    print(list_row_ob)
    print(list_col_ob)
    print(list_z)
    # list_z.
    # c = Counter(list_z)
    # print(len(c.elements()))

    list_row_ob = [int(x) for x in list_row_ob]
    list_col_ob = [int(x) for x in list_col_ob]

    for i in range(len(list_col_ob)):
        mat[list_row_ob[i]][list_col_ob[i]] = 1
    ind = 0
    for rowID in range(maxRow):
        for colID in range(maxCol):
            # print(ind)
            h_mat[rowID][colID] = list_z[ind]
            ind  = ind + 1

    conFileName =  "D:\\VScode\\3D_pathPlanning\\debugMsg\\a_plan.dat"
    rd_cfg = rd.Read_Cfg(conFileName)

    x_list = []
    y_list = []
    pos_list = []
    rd_cfg.get('x',x_list)
    rd_cfg.get('y',y_list)
    for i in range(len(x_list)):
        pos_list.append((x_list[i],y_list[i]))
    print(pos_list)
    # drawHeightPic(mat,h_mat =[] ,pathLst = pos_list)
    drawHeightPic(mat,h_mat = h_mat ,pathLst = pos_list)


    # print(mat)
    # env = drawEnv.Env(mat)
    # env.addgrid()
    # env.addTest()
    # env.drawPic('xx',fileType= False)

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
    # print(list_row_ob)
    # print("ww")
