from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import inspect
import ctypes
import pymysql
from tkinter.scrolledtext import ScrolledText

import func
from func import *


class App:
    def __init__(self):
        self.username = "root"
        self.password = "123456"
        self.sqlname = "school"
        self.win = Tk()
        self.win.title("学生信息管理系统")
        self.win.geometry("500x300+50+150")
        self.win.resizable(0, 0)
        self.login()
        self.run()

    def login(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=60, width=480, height=230)
        Label(f, text="登陆本科生信息管理系统：", font=("宋体", 16, "bold")).place(x=10, y=0)

        Label(f, text="用户名：", font=("宋体", 11, "bold")).place(x=10, y=35, height=25)
        num = ttk.Entry(f)
        num.place(x=60, y=35, width=200, height=25)

        password = StringVar()
        Label(f, text="密码：", font=("宋体", 11, "bold")).place(x=10, y=75, height=25)
        passd = ttk.Entry(f,textvariable=password, show='*')
        passd.place(x=60, y=75, width=200, height=25)

        controls = [num, passd]

        ttk.Button(f, text="登 陆", command=lambda conts=controls: self.login_func(conts)).place(x=280, y=35, width=80)
        ttk.Button(self.win, text="退出系统", command=self.close_win).place(x=350, y=260, height=25, width=100)

    def login_data(self, w):
        # self.student_info.delete(0.0, END)
        res = 1
        result = ""
        num = '\"' + w + '\"'
        db = pymysql.connect(host="localhost", user=self.username, password=self.password, db=self.sqlname)  # 连接数据库
        cursor = db.cursor()  # 创建一个cursor对象（游标）
        sql = "select 密码 from 管理员 where 管理员编号={};".format(num)
        try:
            cursor.execute(sql)
            result = cursor.fetchone()
            # 提交事务
            db.commit()
        except Exception as e:
            # 如果提交失败，回滚到上一次的数据
            db.rollback()
            # 打印异常
            print("error:", e)
            res = 0
        cursor.close()  # 关闭连接
        db.close()
        return result

    def login_func(self, controls):
        result = []
        for control in controls:
            res = control.get()
            # if not res:
            #     res = "NULL"
            result.append(res)
        temp1 = str(result[0])
        temp2 = str(result[1])
        print(temp1)
        print(temp2)
        res = self.login_data(temp1)[0]
        print(res)
        if res == temp2:
            messagebox.showinfo("提示", "登陆成功")
            self.win.destroy()
            func.App()
        else:
            messagebox.showerror("提示", "登陆失败")

    def close_win(self):
        self.win.destroy()

    # 消息主循环
    def run(self):
        self.win.mainloop()


if __name__ == "__main__":
    app = App()
