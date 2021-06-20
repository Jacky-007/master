from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import inspect
import ctypes
import pymysql
from tkinter.scrolledtext import ScrolledText


class App:
    def __init__(self):
        self.username = "root"
        self.password = "123456"
        self.sqlname = "school"
        self.win = Tk()
        self.win.title("学生信息管理系统")
        self.win.geometry("500x300+50+150")
        self.win.resizable(0, 0)
        self.views()
        self.run()

    def views(self):
        Label(self.win, text='学生信息管理系统', font=("宋体", 24, "bold")).place(x=100, y=20, width=300, height=30)

        ttk.Button(self.win, text="插入学生信息", command=self.insert_student).place(x=50, y=80, height=30, width=150)
        ttk.Button(self.win, text="查看学生信息", command=self.select_student).place(x=50, y=130, height=30, width=150)
        ttk.Button(self.win, text="删除学生信息", command=self.delete_student).place(x=50, y=180, height=30, width=150)
        ttk.Button(self.win, text="学生借阅图书", command=self.insert_book).place(x=50, y=230, height=30, width=150)
        ttk.Button(self.win, text="插入老师信息", command=self.insert_teacher).place(x=300, y=100, height=30, width=150)
        ttk.Button(self.win, text="查看选课信息", command=self.select_class).place(x=300, y=150, height=30, width=150)
        ttk.Button(self.win, text="添加选课信息", command=self.insert_class).place(x=300, y=200, height=30, width=150)
        ttk.Button(self.win, text="退出系统", command=self.close_win).place(x=350, y=265, height=25, width=100)

    def close_win(self):
        self.win.destroy()

    # 插入学生信息
    def insert_student(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=70, width=480, height=230)
        Label(f, text="添加学生信息：", font=("宋体", 16, "bold")).place(x=10, y=0)

        ttk.Label(f, text="学号：",background="#708090").place(x=10, y=40, height=25)
        s_num = ttk.Entry(f)
        s_num.place(x=50, y=40, width=100, height=25)

        ttk.Label(f, text="姓名：").place(x=10, y=75, height=25)
        s_name = ttk.Entry(f)
        s_name.place(x=50, y=75, width=100, height=25)

        ttk.Label(f, text="密码：").place(x=10, y=110, height=25)
        s_pwd = ttk.Entry(f)
        s_pwd.place(x=50, y=110, width=100, height=25)

        ttk.Label(f, text="性别：").place(x=10, y=145, height=25)
        s_sex = ttk.Entry(f)
        s_sex.place(x=50, y=145, width=100, height=25)

        ttk.Label(f, text="班级编号：").place(x=180, y=40, height=25)
        cls_num = ttk.Entry(f)
        cls_num.place(x=240, y=40, width=100, height=25)

        ttk.Label(f, text="生日：").place(x=180, y=75, height=25)
        s_date = ttk.Entry(f)
        s_date.place(x=220, y=75, width=120, height=25)

        ttk.Label(f, text="电话：").place(x=180, y=110, height=25)
        s_tel = ttk.Entry(f)
        s_tel.place(x=220, y=110, width=120, height=25)

        controls = [s_num, s_pwd, s_sex, s_name, s_date, s_tel, cls_num]

        ttk.Button(f, text="插入", command=lambda conts=controls: self.insert_func(conts, "学生")).place(x=390, y=150, width=80)
        ttk.Button(f, text="返回", command=f.destroy).place(x=390, y=190, width=80)

    def insert_teacher(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=70, width=480, height=230)
        Label(f, text="添加教师信息：", font=("宋体", 16, "bold")).place(x=10, y=0)

        ttk.Label(f, text="编号：").place(x=10, y=40, height=25)
        t_num = ttk.Entry(f)
        t_num.place(x=50, y=40, width=100, height=25)

        ttk.Label(f, text="姓名：").place(x=10, y=75, height=25)
        t_name = ttk.Entry(f)
        t_name.place(x=50, y=75, width=100, height=25)

        ttk.Label(f, text="性别：").place(x=10, y=105, height=25)
        t_sex = ttk.Entry(f)
        t_sex.place(x=50, y=105, width=100, height=25)

        ttk.Label(f, text="邮箱：").place(x=10, y=140, height=25)
        t_email = ttk.Entry(f)
        t_email.place(x=50, y=140, width=100, height=25)

        ttk.Label(f, text="电话：").place(x=10, y=175, height=25)
        t_tel = ttk.Entry(f)
        t_tel.place(x=50, y=175, width=100, height=25)

        ttk.Label(f, text="学院编号：").place(x=180, y=40, height=25)
        xy_num = ttk.Entry(f)
        xy_num.place(x=240, y=40, width=100, height=25)

        ttk.Label(f, text="薪资：").place(x=180, y=75, height=25)
        t_xz = ttk.Entry(f)
        t_xz.place(x=220, y=75, width=120, height=25)

        ttk.Label(f, text="生日：").place(x=180, y=110, height=25)
        t_date = ttk.Entry(f)
        t_date.place(x=220, y=110, width=120, height=25)

        ttk.Label(f, text="密码：").place(x=180, y=145, height=25)
        t_pwd = ttk.Entry(f)
        t_pwd.place(x=220, y=145, width=120, height=25)
        controls = [t_num, t_name, t_email, t_sex, t_tel, t_xz, t_date, t_pwd, xy_num]

        ttk.Button(f, text="插 入", command=lambda conts=controls: self.insert_func(conts, "教师")).place(x=390, y=150, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=390, y=190, width=80)

    # 插入数据
    def insert_data(self, tableName, data):
        res = 1
        # 连接数据库
        db = pymysql.connect(host="localhost", user=self.username, password=self.password, db=self.sqlname)
        cursor = db.cursor()  # 创建一个cursor对象（游标）
        data_str = "'" + "','".join(data).replace("\n", "") + "'"
        print(data_str)
        sql = "insert into {} values({});".format(tableName, data_str)
        # 执行 sql 语句
        try:
            cursor.execute(sql)
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
        return res

    # 查询数据
    def select_student(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=60, width=480, height=230)
        Label(f, text="查询学生信息：", font=("宋体", 16, "bold")).place(x=10, y=0)

        Label(f, text="学号：", font=("宋体", 11, "bold")).place(x=10, y=35, height=25)
        s_num = ttk.Entry(f)
        s_num.place(x=60, y=35, width=200, height=25)
        #print(type(s_num))

        ttk.Button(f, text="查 询", command=lambda w=s_num: self.select_sdata(w)).place(x=280, y=35, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=380, y=35, width=80)

        self.student_info = ScrolledText(f)
        self.student_info.place(x=10, y=70, width=460, height=150)

    # 查询数据
    def select_class(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=60, width=480, height=230)
        Label(f, text="查询课程信息：", font=("宋体", 16, "bold")).place(x=10, y=0)

        Label(f, text="编号：", font=("宋体", 11, "bold")).place(x=10, y=35, height=25)
        cls_num = ttk.Entry(f)
        cls_num.place(x=60, y=35, width=200, height=25)
        ttk.Button(f, text="查 询", command=lambda w=cls_num: self.select_cdata(w)).place(x=280, y=35, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=380, y=35, width=80)

        self.cls_info = ScrolledText(f)
        self.cls_info.place(x=10, y=70, width=460, height=150)

    def select_cdata(self, w):
        self.cls_info.delete(0.0, END)
        cls_num = w.get()
        db = pymysql.connect(host="localhost", user=self.username, password=self.password, db=self.sqlname)  # 连接数据库
        cursor = db.cursor()  # 创建一个cursor对象（游标）
        sql = "select * from 开设课程 where 课程编号='{}';".format(cls_num)
        try:
            cursor.execute(sql)
            results = cursor.fetchall()
            if results:
                self.cls_info.insert(END, "课程编号：{}\n".format(results[0][0]))
                self.cls_info.insert(END, "开课学期：{}\n".format(results[0][1]))
                self.cls_info.insert(END, "课程名称：{}\n".format(results[0][2]))
                self.cls_info.insert(END, "课程类别：{}\n".format(results[0][3]))
                self.cls_info.insert(END, "考试时间：{}\n".format(results[0][4]))
                self.cls_info.insert(END, "考试地点：{}\n".format(results[0][5]))
                self.cls_info.insert(END, "选课开始时间：{}\n".format(results[0][6]))
                self.cls_info.insert(END, "选课截止时间：{}\n".format(results[0][7]))
                self.cls_info.insert(END, "人数上限：{}\n".format(results[0][8]))
            else:
                self.cls_info.insert(END, "编号错误，查无记录\n")
        except Exception as e:
            db.rollback()
            print("error:", e)
        cursor.close()  # 关闭连接
        db.close()

    def select_sdata(self, w):
        self.student_info.delete(0.0, END)
        s_num = w.get()
        s_num = "\'" + s_num + "\'"
        db = pymysql.connect(host="localhost", user=self.username, password=self.password, db=self.sqlname)  # 连接数据库
        cursor = db.cursor()  # 创建一个cursor对象（游标）
        sql = "select * from 学生 where 学号={};".format(s_num)
        try:
            cursor.execute(sql)
            results = cursor.fetchall()
            if results:
                self.student_info.insert(END, "查询结果：\n学号：{}\n".format(results[0][0]))
                self.student_info.insert(END, "姓名：{}\n".format(results[0][3]))
                self.student_info.insert(END, "性别：{}\n".format(results[0][2]))
                self.student_info.insert(END, "密码：{}\n".format(results[0][1]))
                self.student_info.insert(END, "生日：{}\n".format(results[0][4]))
                self.student_info.insert(END, "电话：{}\n".format(results[0][5]))
                self.student_info.insert(END, "班级编号：{}\n".format(results[0][6]))
                self.student_info.insert(END, "剩余意愿值：{}\n".format(results[0][7]))
            else:
                self.student_info.insert(END, "学号错误，查无此人\n")
        except Exception as e:
            db.rollback()
            print("error:", e)
        sql = "select * from 选课 where 学号={};".format(s_num)
        try:
            cursor.execute(sql)
            results = cursor.fetchall()
            if results:
                self.student_info.insert(END, "\n选课信息：\n开课编号：{}\n".format(results[0][1]))
                self.student_info.insert(END, "所投意愿值：{}\n".format(results[0][2]))
            else:
                self.student_info.insert(END, "没有选课信息\n")
        except Exception as e:
            db.rollback()
            print("error:", e)
        cursor.close()  # 关闭连接
        db.close()

    def insert_func(self, controls, t):
        result = []
        for control in controls:
            res = control.get()
            # if not res:
            #     res = "NULL"
            result.append(res)
        print(t, result)
        if(len(result) == 7):
            result.append("100")
        res = self.insert_data(t, result)
        if res:
            messagebox.showinfo("提示", "信息插入成功")
        else:
            messagebox.showerror("提示", "信息插入失败")

    #删除学生信息
    def delete_student(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=60, width=480, height=230)
        Label(f, text="删除学生信息：", font=("宋体", 16, "bold")).place(x=10, y=0)
        Label(f, text="请教务老师仔细审核所删除学号！慎重使用！", font=("宋体", 16, "bold")).place(x=10, y=100)

        Label(f, text="学号：", font=("宋体", 11, "bold")).place(x=10, y=35, height=25)
        s_num = ttk.Entry(f)
        s_num.place(x=60, y=35, width=200, height=25)
        #ttk.Button(f, text="删 除", command=lambda conts=str(s_num): self.delete_func(conts)).place(x=280, y=35, width=80)
        ttk.Button(f, text="删 除", command=lambda w=s_num: self.delete_func(w)).place(x=280, y=35, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=380, y=35, width=80)

    def delete_sdata(self,w):
        #self.student_info.delete(0.0, END)
        res = 1
        s_num = w.get()
        s_num = '\"' + s_num + '\"'
        print(s_num)
        db = pymysql.connect(host="localhost", user=self.username, password=self.password, db=self.sqlname)  # 连接数据库
        cursor = db.cursor()  # 创建一个cursor对象（游标）
        sql = "delete from 学生 where 学号={};".format(s_num)
        try:
            cursor.execute(sql)
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
        return res

    def delete_func(self, w):
        #self.cls_info.delete(0.0, END)
        temp = w
        print(w, temp)
        print(type(temp))
        res = self.delete_sdata(temp)
        if res:
            messagebox.showinfo("提示", "信息删除成功")
        else:
            messagebox.showerror("提示", "信息删除失败")

        #插入选课信息
    def insert_class(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=70, width=480, height=230)
        Label(f, text="添加学生选课信息：", font=("宋体", 16, "bold")).place(x=10, y=0)

        ttk.Label(f, text="学号：").place(x=10, y=40, height=25)
        stu_num = ttk.Entry(f)
        stu_num.place(x=80, y=40, width=300, height=25)

        ttk.Label(f, text="课程编号：").place(x=10, y=75, height=25)
        class_num = ttk.Entry(f)
        class_num.place(x=80, y=75, width=300, height=25)

        ttk.Label(f, text="意愿值：").place(x=10, y=105, height=25)
        val = ttk.Entry(f)
        val.place(x=80, y=105, width=300, height=25)

        controls = [stu_num, class_num, val]

        ttk.Button(f, text="插 入", command=lambda conts=controls: self.insert_func(conts, "选课")).place(x=390, y=150, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=390, y=190, width=80)

    def insert_book(self):
        f = ttk.Frame(self.win)
        f.place(x=20, y=70, width=480, height=230)
        Label(f, text="添加学生借阅图书：", font=("宋体", 16, "bold")).place(x=10, y=0)

        ttk.Label(f, text="可借图书编号：").place(x=10, y=40, height=25)
        book_num = ttk.Entry(f)
        book_num.place(x=90, y=40, width=150, height=25)

        ttk.Label(f, text="可借副本编号：").place(x=10, y=80, height=25)
        borrow_num = ttk.Entry(f)
        borrow_num.place(x=90, y=80, width=150, height=25)

        ttk.Label(f, text="学号：").place(x=10, y=120, height=25)
        stu_num = ttk.Entry(f)
        stu_num.place(x=90, y=120, width=150, height=25)

        ttk.Label(f, text="借书日期：").place(x=250, y=40, height=25)
        s_date = ttk.Entry(f)
        s_date.place(x=315, y=40, width=150, height=25)

        ttk.Label(f, text="应还日期：").place(x=250, y=80, height=25)
        end_date = ttk.Entry(f)
        end_date.place(x=315, y=80, width=150, height=25)

        ttk.Label(f, text="逾期罚款：").place(x=250, y=120, height=25)
        fine = ttk.Entry(f)
        fine.place(x=315, y=120, width=150, height=25)

        controls = [book_num, borrow_num, stu_num, s_date, end_date, fine]

        ttk.Button(f, text="插 入", command=lambda conts=controls: self.insert_func(conts, "可借图书")).place(x=390, y=150, width=80)
        ttk.Button(f, text="返 回", command=f.destroy).place(x=390, y=190, width=80)


    # 消息主循环
    def run(self):
        self.win.mainloop()


if __name__ == "__main__":
    app = App()
