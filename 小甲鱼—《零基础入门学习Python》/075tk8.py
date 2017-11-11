# encoding: utf-8
"""
@author: 酸饺子
@contact: changzheng300@foxmail.com
@license: Apache Licence
@file: 075tk8.py
@time: 2017/8/8 18:33

设置窗口透明度属性
"""


from tkinter import *


def main():
    root = Tk()

    def create():
        top = Toplevel()
        top.attributes('-alpha', 0.5)
        top.title('fishC Demo')

        msg = Message(top, text='I love FishC.com')
        msg.pack()

    Button(root, text='创建顶级窗口', command=create).pack()

    mainloop()

if __name__ == '__main__':
    main()