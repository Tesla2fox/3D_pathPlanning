import drawEnv
import read_cfg as rd
import  numpy as np


if __name__ == '__main__':

    conFileName =  "D:\\VScode\\3D_pathPlanning\\debugMsg\\grid.dat"
    rd_cfg = rd.Read_Cfg(conFileName)

    maxRow = int(rd_cfg.getSingleVal('maxRow'))
    maxCol = int(rd_cfg.getSingleVal('maxCol'))
    mat = np.zeros((maxRow,maxCol),dtype=int)


    list_row = []
    list_col = []
    list_row_ob = []
    list_col_ob = []

    list_x = []
    list_y = []
    list_z = []

    rd_cfg.get("row",list_row)
    rd_cfg.get("col",list_col)
    rd_cfg.get("obRow",list_row_ob)
    rd_cfg.get("obCol",list_row_ob)
    rd_cfg.get("x",list_x)
    rd_cfg.get("y",list_y)
    rd_cfg.get("z",list_z)
    list_row_ob = [int(x) for x in list_row_ob]
    list_col_ob = [int(x) for x in list_col_ob]

    for i in range(len(list_col_ob)):
        mat[list_row_ob[i]][list_col_ob[i]] = 1

    print(mat)
    env = drawEnv.Env(mat)
    env.addgrid()
    env.addTest()
    env.drawPic('xx',fileType= False)

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
