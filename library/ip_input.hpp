// @ JNQ写的IP控件

class IPEdit : public QFrame
{
    Q_OBJECT

public:
    IPEdit(QWidget *parent = 0);
    ~IPEdit();

    virtual bool eventFilter(QObject *obj, QEvent *event);
    bool         getIP(QHostAddress *haddr);
    void         SetIp(QHostAddress*haddr);
public slots:
    void slotTextChanged(QLineEdit* pEdit);
    void lineEditChanged();
signals:
    void signalTextChanged(QLineEdit* pEdit);

private:
    enum
    {
        QTUTL_IP_SIZE = 4,//
        MAX_DIGITS = 3 //
    };

    QLineEdit* (m_pLineEdit[QTUTL_IP_SIZE]);
    QLabel* (pDot[QTUTL_IP_SIZE - 1]);
    void MoveNextLineEdit(int i);
    void MovePrevLineEdit(int i);

};


IPEdit::IPEdit(QWidget *parent) : QFrame(parent)
{
    /*setFrameShape(QFrame::StyledPanel);*/
    /*setFrameShadow(QFrame::Sunken);*/

    QHBoxLayout* pLayout = new QHBoxLayout(this);
    setLayout(pLayout);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(0);

    for (int i = 0; i != QTUTL_IP_SIZE; ++i)
    {
        if (i != 0)
        {
            pDot[i - 1] = new QLabel(".", this);
            /*pDot[i - 1]->setStyleSheet("background: white");*/
            pLayout->addWidget(pDot[i - 1]);
            pLayout->setStretch(pLayout->count(), 0);
        }

        m_pLineEdit[i] = new QLineEdit(this);
        QLineEdit *pEdit = m_pLineEdit[i];
        pEdit->installEventFilter(this);

        pLayout->addWidget(pEdit);
        pLayout->setStretch(pLayout->count(), 1);

        pEdit->setFrame(false);
        pEdit->setAlignment(Qt::AlignCenter);

        QFont font = pEdit->font();
        font.setStyleHint(QFont::Monospace);
        font.setFixedPitch(true);
        pEdit->setFont(font);

        QRegExp rx("^(0|[1-9]|[1-9][0-9]|1[0-9][0-9]|2([0-4][0-9]|5[0-5]))$");
        QValidator *validator = new QRegExpValidator(rx, pEdit);
        pEdit->setValidator(validator);
    }
    setMaximumWidth(50 * QTUTL_IP_SIZE);
    setMaximumHeight(30);
    connect(this, SIGNAL(signalTextChanged(QLineEdit *)),
            this, SLOT(slotTextChanged(QLineEdit *)),
            Qt::QueuedConnection);
    for (int i = 0; i < QTUTL_IP_SIZE; i++)
    {
        connect(m_pLineEdit[i], SIGNAL(textChanged(QString)),
                this, SLOT(lineEditChanged()));
    }
}

IPEdit::~IPEdit()
{
  delete[] * pDot;
  delete[] * m_pLineEdit;
}

void IPEdit::lineEditChanged()
{
    QLineEdit *pEdit = qobject_cast<QLineEdit *>(sender());
    for (unsigned int i = 0; i != QTUTL_IP_SIZE; ++i)
    {
        if (pEdit == m_pLineEdit[i])
        {
            if (pEdit->text().size() == MAX_DIGITS 
                && pEdit->text().size() == pEdit->cursorPosition())
            {
                if (i + 1 != QTUTL_IP_SIZE)
                {
                    m_pLineEdit[i + 1]->setFocus();
                    m_pLineEdit[i + 1]->selectAll();
                }
            }
        }
    }
}

void IPEdit::slotTextChanged(QLineEdit *pEdit)
{
    for (unsigned int i = 0; i != QTUTL_IP_SIZE; ++i)
    {
        if (pEdit == m_pLineEdit[i])
        {
            if ((pEdit->text().size() == MAX_DIGITS
                && pEdit->text().size() == pEdit->cursorPosition())
                || (pEdit->text() == "0"))
            {
                if (i + 1 != QTUTL_IP_SIZE)
                {
                    m_pLineEdit[i + 1]->setFocus();
                    m_pLineEdit[i + 1]->selectAll();
                }
            }
        }
    }
}

bool IPEdit::eventFilter(QObject *obj, QEvent *event)
{
    bool bRes = QFrame::eventFilter(obj, event);
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *pEvent = dynamic_cast<QKeyEvent *>(event);
        if (pEvent)
        {
            for (unsigned int i = 0; i != QTUTL_IP_SIZE; ++i)
            {
                QLineEdit *pEdit = m_pLineEdit[i];
                if (pEdit == obj)
                {
                    switch (pEvent->key())
                    {
                    case Qt::Key_Left:
                        if (pEdit->cursorPosition() == 0)
                        {
                            // user wants to move to previous item
                            MovePrevLineEdit(i);
                        }
                        break;
                    case Qt::Key_Right:
                        if (pEdit->text().isEmpty() 
                            || (pEdit->text().size() == pEdit->cursorPosition()))
                        {
                            // user wants to move to next item
                            MoveNextLineEdit(i);
                        }
                        break;
                    case Qt::Key_0:
                        if (pEdit->text().isEmpty() || pEdit->text() == "0")
                        {
                            pEdit->setText("0");
                            // user wants to move to next item
                            MoveNextLineEdit(i);
                        }
                        emit signalTextChanged(pEdit);
                        break;
                    case Qt::Key_Backspace:
                        if (pEdit->text().isEmpty() 
                            || pEdit->cursorPosition() == 0)
                        {
                            // user wants to move to previous item
                            MovePrevLineEdit(i);
                        }
                        break;
                    case Qt::Key_Comma:
                    case Qt::Key_Period:
                        MoveNextLineEdit(i);
                        break;
                    default:
                        emit signalTextChanged(pEdit);
                        break;
                    }
                }
            }
        }
    }
    return bRes;
}

void IPEdit::MoveNextLineEdit(int i)
{
    if (i + 1 != QTUTL_IP_SIZE)
    {
        m_pLineEdit[i + 1]->setFocus();
        m_pLineEdit[i + 1]->setCursorPosition(0);
        m_pLineEdit[i + 1]->selectAll();
    }
}

void IPEdit::MovePrevLineEdit(int i)
{
    if (i != 0)
    {
        m_pLineEdit[i - 1]->setFocus();
        m_pLineEdit[i - 1]->setCursorPosition(m_pLineEdit[i - 1]->text().size());
    }
}

bool IPEdit::getIP(QHostAddress *haddr)
{
    QString ip_str;
    ip_str.clear();
    for (int i = 0; i < QTUTL_IP_SIZE; i++)
    {
        if (i != 0)
            ip_str.append(".");
        if (m_pLineEdit[i]->text().isEmpty())
        {
            continue;
        }

        ip_str.append(m_pLineEdit[i]->text());
    }
    qDebug() << ip_str;
    *haddr = QHostAddress(ip_str);
    return true;
}

void IPEdit::SetIp(QHostAddress *haddr)
{
    QString IpStr = haddr->toString();
    int Begin = 0;
    int End = 0;
    for (int i = 0; i < QTUTL_IP_SIZE; i++)
    {
        End = IpStr.indexOf(".", Begin);
        if (End != -1)
        {
            QString IpMid = IpStr.mid(Begin, End - Begin);
            m_pLineEdit[i]->setText(IpMid);
            Begin = End + 1;
        }
        else
        {
            QString IpMid = IpStr.mid(Begin, IpStr.length() - Begin);
            m_pLineEdit[i]->setText(IpMid);
            return;
        }
    }
}