//Qt悬浮框
// @ author CZY
//悬浮类

//1, 覆写eventFilter方法
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

bool TipsDockDlg::eventFilter(QObject* watched, QEvent* event)
{
    Q_UNUSED(watched)
    if (event->type() == QEvent::Enter)
    {
        show();
        move(m_targetPoint);
        raise();
        return true;
    }
    return QDialog::eventFilter(watched, event);
}

//初始化悬浮框

Qt::WindowFlags flags = windowFlags();
setWindowFlags(flags | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);//无边框, 上层显示
setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除
//	setAttribute(Qt::WA_Hover);//鼠标进入或移出窗体时产生paint事件
//	setAttribute(Qt::WA_TranslucentBackground);
setWindowOpacity(0.9);//1不透明.0完全透明
setStyleSheet("QWidget {background: grey;}");//灰色背景
//	setStyleSheet("border-radius: 10px");//TODO 圆角
//TODO 小箭头



//使用者

//1, 重写paintEvent. 在paintEvent中才能正确获取控件位置

void paintEvent(QPaintEvent* event) override;

void EditDiskOsListProperty::paintEvent(QPaintEvent* event)
{
    QPoint btnPoint{ m_ui->pushButton->mapToGlobal(QPoint(pos())) }; //gist
    QPoint temp{ btnPoint.x() + m_ui->pushButton->width(), btnPoint.y() };
    m_tipsDlg->setTarget(temp);
}

//安装事件过滤器
m_ui->pushButton->installEventFilter(m_tipsDlg);



//其他

pos(); //相对于父控件的位置(屏幕左上角维(0, 0))

//获取屏幕坐标,并移动到屏幕的坐标
QPoint oPoint = this.mapTopGlobal(QPoing(0, this.heigth()));
m_pWidget->move(oPoint);

button->mapTopGlobal(pushButton->pos());


//移走隐藏
mousemoveEvent();
//鼠标进入控件的范围内的时候才起作用(并且要提前设置setMouseTracking为true)
//但如果在enterEvent中和leaveEvent中处理显隐则导致鼠标进入不了悬浮窗就会隐藏

//显示悬浮窗的时候,开启timer
this->startTimer(1000);

//在timerEvent中判断鼠标是否游离到了本控件和悬浮窗之外.如果游离出去了,那么隐藏窗口,
//并关闭timer
void myLabel::timerEvent(QTimerEvent *ev)
{
    if (!m_pWidget && m_pWidget.isVisible())
    {
        QPoint oPoint       = QCursor::pos();
        QPoint oSelfPoint   = this->mapFromGlobal(oPoint);
        QPoint oWidgetPoint = m_pProjectWidget->mapFromGlobal(oPoint);
        QRect  oSelfRect    = this->rect();
        QRect  oWidgetRect  = m_pWidget->rect();
        if (!oSelfRect.contains(oSelfPoint) && !oWidgetRect.contains(oWidgetPoint))
        {
            m_pWidget->hide();
            killTimer(ev->timerId());
        }
    }
    else
    {
        killTimer(ev->timerId());
    }
}

//override
bool eventFilter(QObject* target, QEvent* event)
{
    if (ui->btn == tartget || m_label == tartget)
    {
        if (QEvent::Enter == event->type()) //鼠标 in
        {
            if (m_label->inHidden())
            {
                m_label->show();
                QPoint point = ui->btn->pos();
                point.rx() = point.x() - m_label->width() + 120;
                point.ry() = point.y() + ui->btn->heigth() + 40;
                m_label->move(point);

                m_label->raise()//最顶层
                return true;
            }
        }
        else if (QEvent::Leave == event->type())//鼠标 out
        {
            if (!m_label->inHidden())
            {
                if (!ui->btn->geometry().contains(this->mapFromGlobal(QCursor::pos()))
                && !m_label->geometry().contains(this->mapFromGlobal(QCursor::pos())))
                {
                    m_label->hide();
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(target, event);
}



QPoint QMouseEvent::pos();
//返回相对这个widget(重载了QMouseEvent的widget)的位置

QPoint QMouseEvent::globalPos();
//窗口坐标,返回鼠标的全局坐标

QPoint QCursor::pos();
//返回相对显示器的全局坐标

QPoint QWidget::mapToGlobal(const QPoint& pos) const;
//将窗口坐标转换成显示器坐标

QPoint QWidget::mapFromGlobal(const QPoint& pos) const;
//将显示器坐标转换成窗口坐标

QPoint QWidget::mapToParent(const QPoint& pos) const;
//将窗口坐标获得的pos转换成父类widget的坐标

QPoint QWidget::mapFromParent(const QPoint& pos) const;
//将父类窗口坐标转换成当前窗口坐标

QPoint QWidget::mapTo(const QWidget* parent, const QPoint& pos) const;
//将当前窗口坐标转换成指定parent坐标

QWidget::pos() : QPoint
//获得当前控件在父窗口中的位置


//背景设置黑色,前景设置白色
QPalette palette = palette();
palette.setColor(QPalette::Background, QColor(0,0,0,255));
palette.setColor(QPalette::Foreground, QColor(255,255,255,255));
setPalette(palette);
//或使用
setStyleSheet("background-color: rgb(0,0,0); color: rgb(255,255,255);");
//上个方法会影响子控件
setStyleSheet("venus--TitleBar {background-color: rgb(0,0,0); color: rgb(255,255,255);}");

//圆角控件
setStyleSheet("border-radius: 10px");

//圆角窗口
RoundRectWin::RoundRectWin(){
    QPalette p = palette();
    QPixmap img("roundrect.png");
    QBitmap mask("roundrect_mask.png");
    setPalette(p);
    setMask(mask);
    resize(img.size());
}

//窗口透明,控件不透明
QPalette p = palette();
p.setColor(QPalette::Background, QColor(0x00, 0xff, 0x00, 0x00));
setPalette(p);

QPoint GlobalPoint(m_btn->mapToGlobal(QPoint(0, 0)));//获取控件在窗体中的坐标


// oh yeah
void EditDiskOsListProperty::paintEvent(QPaintEvent* event)
{
	QPoint btnPoint{ m_ui->pushButton->mapToGlobal(QPoint(pos())) };
	m_tipsDlg->targetPoint.setX(btnPoint.x() + m_ui->pushButton->width());
	m_tipsDlg->targetPoint.setY(btnPoint.y() + m_ui->pushButton->height());
}
