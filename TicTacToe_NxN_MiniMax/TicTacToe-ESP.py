from tkinter import messagebox
from tkinter import *
import math

#TicTacToe Modules

choice=0
size=0
root=Tk()
root.title("TicTacToe")
list1=[]
xTurn=0
count=0
winP1=0
winP2=0

def mainMenu1():
    root.destroy()
    global e2
    global root2
    global e1
    root2=Tk()
    root2.title("TicTacToe")
    label=Label(root2,text="Enter the size for tic tac toe greater than 1").grid(row=0,column=0)
    e1=Entry(root2)
    e1.grid(row=0,column=1)
    label=Label(root2,text="Enter 0 for PvP and 1 for PvAI").grid(row=1,column=0)
    e2=Entry(root2)
    e2.grid(row=1,column=1)
    button=Button(root2,text="Enter",command=printBoard).grid(row=2,column=0,columnspan=3,sticky=W+E)
    mainloop()
def minimax(alpha,beta,n,depth,maximizingPlayer):
    global winP1
    global winP2
    global count
    if winChecker()==1:
        return -1
    elif winChecker()==0:
        return 1
    elif winChecker()==2:
        if n==size**2 or depth==0:
            return 0
        else:
            pass
    if maximizingPlayer:
        bestScore=-math.inf
        for i in range(size):
            for j in range(size):
                if list1[i][j]["text"]==" ":
                    list1[i][j]["text"]="X"
                    score=minimax(alpha,beta,n+1,depth-1,False)
                    list1[i][j]["text"]=" "
                    bestScore=max(score,bestScore)
                    alpha=max(score,alpha)
                    if bestScore>beta:
                        break
        winP1=0
        winP2=0
        winChecker()
        return bestScore
    else:
        bestScore=math.inf
        for i in range(size):
            for j in range(size):
                if list1[i][j]["text"]==" ":
                    list1[i][j]["text"]="O"
                    score=minimax(alpha,beta,n+1,depth-1,True)
                    list1[i][j]["text"]=" "
                    bestScore=min(score,bestScore)
                    beta=min(score,beta)
                    if bestScore<alpha:
                        break
        winP1=0
        winP2=0
        winChecker()
        return bestScore
def compMove():
    global winP1
    global winP2
    bestScore=-math.inf
    bestMove=""
    for i in range(size):
        for j in range(size):
            if list1[i][j]["text"]==" ":
                list1[i][j]["text"]="X"
                score=minimax(-math.inf,math.inf,count+2,7,False)
                winP2=0
                winP1=0
                list1[i][j]["text"]=" "
                if score>bestScore:
                    bestScore=score
                    bestMove=str(i)+str(j)
    return bestMove
def gridClear():
    list1.clear()
def winChecker():
    global winP1
    global winP2
    if winP1==size:
        return 1
    elif winP2==size:
        return 0
    for i in range(size):
        for j in range(size):
            if list1[i][j]["text"]=="O":
                winP1+=1
            elif list1[i][j]["text"]=="X":
                winP2+=1
            if winP1==size:
                return 1
            elif winP2==size:
                return 0
        winP1=0
        winP2=0
    for i in range(size):
        for j in range(size):
            if list1[j][i]["text"]=="O":
                winP1+=1
            elif list1[j][i]["text"]=="X":
                winP2+=1
            if winP1==size:
                return 1
            elif winP2==size:
                return 0
        winP1=0
        winP2=0
    for i in range(size):
        if list1[i][i]["text"]=="O":
            winP1+=1
        elif list1[i][i]["text"]=="X":
            winP2+=1
        if winP1==size:
            return 1
        elif winP2==size:
            return 0
    winP1=0
    winP2=0
    for i in range(size):
        if list1[i][size-1-i]["text"]=="O":
            winP1+=1
        elif list1[i][size-1-i]["text"]=="X":
            winP2+=1
        if winP1==size:
            return 1
        elif winP2==size:
            return 0
    winP1=0
    winP2=0
    return 2
def drawChecker():
    global bestMove
    if size%2==0:
        if choice==0 and count==size**2:
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","The game is a draw between two players!")
            label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            return True
        elif choice==1 and count==size**2:
            globals()["winP1"] = 0
            globals()["winP2"] = 0
            list1[int(bestMove[0])][int(bestMove[1])]["text"]="X"
            list1[int(bestMove[0])][int(bestMove[1])]["state"]="disabled"
            if winChecker()==1:
                label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
                msg=messagebox.showinfo("Result","Player 1 has won the game!")
                main()
            elif winChecker()==0:
                label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
                msg=messagebox.showinfo("Result","Player 2 has won the game!")
                main()
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","The game is a draw between a player and the computer!")
            label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            return True
        return False
    elif size%2==1:
        if choice==1 and count==(size**2)+1:
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","The game is a draw between a player and the computer!")
            label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            return True
        elif choice==0 and count==size**2:
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","The game is a draw between two players!")
            label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            return True
        return False
def moveMaker(row,col):
    if choice==0:
        if xTurn==0:
            list1[row][col]["text"]="O"
            list1[row][col]["state"]="disabled"
            label=Label(root,text="Waiting for Player 2!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            globals()["xTurn"] = 1
        elif xTurn==1:
            list1[row][col]["text"]="X"
            list1[row][col]["state"]="disabled"
            label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            globals()["xTurn"] = 0
        if winChecker()==2:
            globals()["count"]+=1
            if drawChecker():
                main()
        else:
            if winChecker()==1:
                label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
                msg=messagebox.showinfo("Result","Player 1 has won the game!")
            elif winChecker()==0:
                label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
                msg=messagebox.showinfo("Result","Player 2 has won the game!")
            main()
    elif choice==1:
        if xTurn==0:
            list1[row][col]["text"]="O"
            list1[row][col]["state"]="disabled"
            label=Label(root,text="Waiting for Player 2!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            globals()["xTurn"] = 1
            global bestMove
            bestMove=compMove()
        if winChecker()==2:
            globals()["count"]+=2
            if drawChecker():
                    main()
            else:
                globals()["winP1"] = 0
                globals()["winP2"] = 0
                list1[int(bestMove[0])][int(bestMove[1])]["text"]="X"
                list1[int(bestMove[0])][int(bestMove[1])]["state"]="disabled"
                label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
                globals()["xTurn"] = 0
        if winChecker()==1:
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","Player 1 has won the game!")
            main()
        elif winChecker()==0:
            label=Label(root,text="",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
            msg=messagebox.showinfo("Result","Player 2 has won the game!")
            main()
def printBoard():
    global e1
    global e2
    global size
    size=eval(e1.get())
    global choice
    choice=eval(e2.get())
    global root2
    root2.destroy()
    global root
    if  size<2 or type(size)==float:
        root=Tk()
        root.title("TicTacToe")
        msg=messagebox.showwarning("Error","Enter a valid choice and size")
        main()
        return 0
    if choice!=0 and choice!=1:
        root=Tk()
        root.title("TicTacToe")
        msg=messagebox.showwarning("Error","Enter a valid choice and size")
        main()
        return 0
    root=Tk()
    label=Label(root,text="Waiting for Player 1!",relief=SUNKEN).grid(row=0,column=0,columnspan=size,sticky=W+E)
    gridClear()
    globals()["xTurn"] = 0
    globals()["count"] = 0
    globals()["winP1"] = 0
    globals()["winP2"] = 0
    for i in range(size):
        list2=[]
        for j in range(size):
            global b
            b=Button(root,text=" ",width=10,height=4,command=lambda row=i, column=j: moveMaker(row, column))
            list2.append(b)
            b.grid(row=i+1,column=j)
        list1.append(list2)
def main():
    mainMenu1()

main()

root.mainloop()







