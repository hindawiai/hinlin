<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * netup_unidvb_i2c.c
 *
 * Internal I2C bus driver क्रम NetUP Universal Dual DVB-CI
 *
 * Copyright (C) 2014 NetUP Inc.
 * Copyright (C) 2014 Sergey Kozlov <serjk@netup.ru>
 * Copyright (C) 2014 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश "netup_unidvb.h"

#घोषणा NETUP_I2C_BUS0_ADDR		0x4800
#घोषणा NETUP_I2C_BUS1_ADDR		0x4840
#घोषणा NETUP_I2C_TIMEOUT		1000

/* twi_ctrl0_stat reg bits */
#घोषणा TWI_IRQEN_COMPL	0x1
#घोषणा TWI_IRQEN_ANACK 0x2
#घोषणा TWI_IRQEN_DNACK 0x4
#घोषणा TWI_IRQ_COMPL	(TWI_IRQEN_COMPL << 8)
#घोषणा TWI_IRQ_ANACK	(TWI_IRQEN_ANACK << 8)
#घोषणा TWI_IRQ_DNACK	(TWI_IRQEN_DNACK << 8)
#घोषणा TWI_IRQ_TX	0x800
#घोषणा TWI_IRQ_RX	0x1000
#घोषणा TWI_IRQEN	(TWI_IRQEN_COMPL | TWI_IRQEN_ANACK | TWI_IRQEN_DNACK)
/* twi_addr_ctrl1 reg bits*/
#घोषणा TWI_TRANSFER	0x100
#घोषणा TWI_NOSTOP	0x200
#घोषणा TWI_SOFT_RESET	0x2000
/* twi_clkभाग reg value */
#घोषणा TWI_CLKDIV	156
/* fअगरo_stat_ctrl reg bits */
#घोषणा FIFO_IRQEN	0x8000
#घोषणा FIFO_RESET	0x4000
/* FIFO size */
#घोषणा FIFO_SIZE	16

काष्ठा netup_i2c_fअगरo_regs अणु
	जोड़ अणु
		__u8	data8;
		__le16	data16;
		__le32	data32;
	पूर्ण;
	__u8		padding[4];
	__le16		stat_ctrl;
पूर्ण __packed __aligned(1);

काष्ठा netup_i2c_regs अणु
	__le16				clkभाग;
	__le16				twi_ctrl0_stat;
	__le16				twi_addr_ctrl1;
	__le16				length;
	__u8				padding1[8];
	काष्ठा netup_i2c_fअगरo_regs	tx_fअगरo;
	__u8				padding2[6];
	काष्ठा netup_i2c_fअगरo_regs	rx_fअगरo;
पूर्ण __packed __aligned(1);

irqवापस_t netup_i2c_पूर्णांकerrupt(काष्ठा netup_i2c *i2c)
अणु
	u16 reg, पंचांगp;
	अचिन्हित दीर्घ flags;
	irqवापस_t iret = IRQ_HANDLED;

	spin_lock_irqsave(&i2c->lock, flags);
	reg = पढ़ोw(&i2c->regs->twi_ctrl0_stat);
	ग_लिखोw(reg & ~TWI_IRQEN, &i2c->regs->twi_ctrl0_stat);
	dev_dbg(i2c->adap.dev.parent,
		"%s(): twi_ctrl0_state 0x%x\n", __func__, reg);
	अगर ((reg & TWI_IRQEN_COMPL) != 0 && (reg & TWI_IRQ_COMPL)) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): TWI_IRQEN_COMPL\n", __func__);
		i2c->state = STATE_DONE;
		जाओ irq_ok;
	पूर्ण
	अगर ((reg & TWI_IRQEN_ANACK) != 0 && (reg & TWI_IRQ_ANACK)) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): TWI_IRQEN_ANACK\n", __func__);
		i2c->state = STATE_ERROR;
		जाओ irq_ok;
	पूर्ण
	अगर ((reg & TWI_IRQEN_DNACK) != 0 && (reg & TWI_IRQ_DNACK)) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): TWI_IRQEN_DNACK\n", __func__);
		i2c->state = STATE_ERROR;
		जाओ irq_ok;
	पूर्ण
	अगर ((reg & TWI_IRQ_RX) != 0) अणु
		पंचांगp = पढ़ोw(&i2c->regs->rx_fअगरo.stat_ctrl);
		ग_लिखोw(पंचांगp & ~FIFO_IRQEN, &i2c->regs->rx_fअगरo.stat_ctrl);
		i2c->state = STATE_WANT_READ;
		dev_dbg(i2c->adap.dev.parent,
			"%s(): want read\n", __func__);
		जाओ irq_ok;
	पूर्ण
	अगर ((reg & TWI_IRQ_TX) != 0) अणु
		पंचांगp = पढ़ोw(&i2c->regs->tx_fअगरo.stat_ctrl);
		ग_लिखोw(पंचांगp & ~FIFO_IRQEN, &i2c->regs->tx_fअगरo.stat_ctrl);
		i2c->state = STATE_WANT_WRITE;
		dev_dbg(i2c->adap.dev.parent,
			"%s(): want write\n", __func__);
		जाओ irq_ok;
	पूर्ण
	dev_warn(&i2c->adap.dev, "%s(): not mine interrupt\n", __func__);
	iret = IRQ_NONE;
irq_ok:
	spin_unlock_irqrestore(&i2c->lock, flags);
	अगर (iret == IRQ_HANDLED)
		wake_up(&i2c->wq);
	वापस iret;
पूर्ण

अटल व्योम netup_i2c_reset(काष्ठा netup_i2c *i2c)
अणु
	dev_dbg(i2c->adap.dev.parent, "%s()\n", __func__);
	i2c->state = STATE_DONE;
	ग_लिखोw(TWI_SOFT_RESET, &i2c->regs->twi_addr_ctrl1);
	ग_लिखोw(TWI_CLKDIV, &i2c->regs->clkभाग);
	ग_लिखोw(FIFO_RESET, &i2c->regs->tx_fअगरo.stat_ctrl);
	ग_लिखोw(FIFO_RESET, &i2c->regs->rx_fअगरo.stat_ctrl);
	ग_लिखोw(0x800, &i2c->regs->tx_fअगरo.stat_ctrl);
	ग_लिखोw(0x800, &i2c->regs->rx_fअगरo.stat_ctrl);
पूर्ण

अटल व्योम netup_i2c_fअगरo_tx(काष्ठा netup_i2c *i2c)
अणु
	u8 data;
	u32 fअगरo_space = FIFO_SIZE -
		(पढ़ोw(&i2c->regs->tx_fअगरo.stat_ctrl) & 0x3f);
	u32 msg_length = i2c->msg->len - i2c->xmit_size;

	msg_length = (msg_length < fअगरo_space ? msg_length : fअगरo_space);
	जबतक (msg_length--) अणु
		data = i2c->msg->buf[i2c->xmit_size++];
		ग_लिखोb(data, &i2c->regs->tx_fअगरo.data8);
		dev_dbg(i2c->adap.dev.parent,
			"%s(): write 0x%02x\n", __func__, data);
	पूर्ण
	अगर (i2c->xmit_size < i2c->msg->len) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): TX IRQ enabled\n", __func__);
		ग_लिखोw(पढ़ोw(&i2c->regs->tx_fअगरo.stat_ctrl) | FIFO_IRQEN,
			&i2c->regs->tx_fअगरo.stat_ctrl);
	पूर्ण
पूर्ण

अटल व्योम netup_i2c_fअगरo_rx(काष्ठा netup_i2c *i2c)
अणु
	u8 data;
	u32 fअगरo_size = पढ़ोw(&i2c->regs->rx_fअगरo.stat_ctrl) & 0x3f;

	dev_dbg(i2c->adap.dev.parent,
		"%s(): RX fifo size %d\n", __func__, fअगरo_size);
	जबतक (fअगरo_size--) अणु
		data = पढ़ोb(&i2c->regs->rx_fअगरo.data8);
		अगर ((i2c->msg->flags & I2C_M_RD) != 0 &&
					i2c->xmit_size < i2c->msg->len) अणु
			i2c->msg->buf[i2c->xmit_size++] = data;
			dev_dbg(i2c->adap.dev.parent,
				"%s(): read 0x%02x\n", __func__, data);
		पूर्ण
	पूर्ण
	अगर (i2c->xmit_size < i2c->msg->len) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): RX IRQ enabled\n", __func__);
		ग_लिखोw(पढ़ोw(&i2c->regs->rx_fअगरo.stat_ctrl) | FIFO_IRQEN,
			&i2c->regs->rx_fअगरo.stat_ctrl);
	पूर्ण
पूर्ण

अटल व्योम netup_i2c_start_xfer(काष्ठा netup_i2c *i2c)
अणु
	u16 rdflag = ((i2c->msg->flags & I2C_M_RD) ? 1 : 0);
	u16 reg = पढ़ोw(&i2c->regs->twi_ctrl0_stat);

	ग_लिखोw(TWI_IRQEN | reg, &i2c->regs->twi_ctrl0_stat);
	ग_लिखोw(i2c->msg->len, &i2c->regs->length);
	ग_लिखोw(TWI_TRANSFER | (i2c->msg->addr << 1) | rdflag,
		&i2c->regs->twi_addr_ctrl1);
	dev_dbg(i2c->adap.dev.parent,
		"%s(): length %d twi_addr_ctrl1 0x%x twi_ctrl0_stat 0x%x\n",
		__func__, पढ़ोw(&i2c->regs->length),
		पढ़ोw(&i2c->regs->twi_addr_ctrl1),
		पढ़ोw(&i2c->regs->twi_ctrl0_stat));
	i2c->state = STATE_WAIT;
	i2c->xmit_size = 0;
	अगर (!rdflag)
		netup_i2c_fअगरo_tx(i2c);
	अन्यथा
		ग_लिखोw(FIFO_IRQEN | पढ़ोw(&i2c->regs->rx_fअगरo.stat_ctrl),
			&i2c->regs->rx_fअगरo.stat_ctrl);
पूर्ण

अटल पूर्णांक netup_i2c_xfer(काष्ठा i2c_adapter *adap,
			  काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i, trans_करोne, res = num;
	काष्ठा netup_i2c *i2c = i2c_get_adapdata(adap);
	u16 reg;

	spin_lock_irqsave(&i2c->lock, flags);
	अगर (i2c->state != STATE_DONE) अणु
		dev_dbg(i2c->adap.dev.parent,
			"%s(): i2c->state == %d, resetting I2C\n",
			__func__, i2c->state);
		netup_i2c_reset(i2c);
	पूर्ण
	dev_dbg(i2c->adap.dev.parent, "%s() num %d\n", __func__, num);
	क्रम (i = 0; i < num; i++) अणु
		i2c->msg = &msgs[i];
		netup_i2c_start_xfer(i2c);
		trans_करोne = 0;
		जबतक (!trans_करोne) अणु
			spin_unlock_irqrestore(&i2c->lock, flags);
			अगर (रुको_event_समयout(i2c->wq,
					i2c->state != STATE_WAIT,
					msecs_to_jअगरfies(NETUP_I2C_TIMEOUT))) अणु
				spin_lock_irqsave(&i2c->lock, flags);
				चयन (i2c->state) अणु
				हाल STATE_WANT_READ:
					netup_i2c_fअगरo_rx(i2c);
					अवरोध;
				हाल STATE_WANT_WRITE:
					netup_i2c_fअगरo_tx(i2c);
					अवरोध;
				हाल STATE_DONE:
					अगर ((i2c->msg->flags & I2C_M_RD) != 0 &&
						i2c->xmit_size != i2c->msg->len)
						netup_i2c_fअगरo_rx(i2c);
					dev_dbg(i2c->adap.dev.parent,
						"%s(): msg %d OK\n",
						__func__, i);
					trans_करोne = 1;
					अवरोध;
				हाल STATE_ERROR:
					res = -EIO;
					dev_dbg(i2c->adap.dev.parent,
						"%s(): error state\n",
						__func__);
					जाओ करोne;
				शेष:
					dev_dbg(i2c->adap.dev.parent,
						"%s(): invalid state %d\n",
						__func__, i2c->state);
					res = -EINVAL;
					जाओ करोne;
				पूर्ण
				अगर (!trans_करोne) अणु
					i2c->state = STATE_WAIT;
					reg = पढ़ोw(
						&i2c->regs->twi_ctrl0_stat);
					ग_लिखोw(TWI_IRQEN | reg,
						&i2c->regs->twi_ctrl0_stat);
				पूर्ण
				spin_unlock_irqrestore(&i2c->lock, flags);
			पूर्ण अन्यथा अणु
				spin_lock_irqsave(&i2c->lock, flags);
				dev_dbg(i2c->adap.dev.parent,
					"%s(): wait timeout\n", __func__);
				res = -ETIMEDOUT;
				जाओ करोne;
			पूर्ण
			spin_lock_irqsave(&i2c->lock, flags);
		पूर्ण
	पूर्ण
करोne:
	spin_unlock_irqrestore(&i2c->lock, flags);
	dev_dbg(i2c->adap.dev.parent, "%s(): result %d\n", __func__, res);
	वापस res;
पूर्ण

अटल u32 netup_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm netup_i2c_algorithm = अणु
	.master_xfer	= netup_i2c_xfer,
	.functionality	= netup_i2c_func,
पूर्ण;

अटल स्थिर काष्ठा i2c_adapter netup_i2c_adapter = अणु
	.owner		= THIS_MODULE,
	.name		= NETUP_UNIDVB_NAME,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &netup_i2c_algorithm,
पूर्ण;

अटल पूर्णांक netup_i2c_init(काष्ठा netup_unidvb_dev *ndev, पूर्णांक bus_num)
अणु
	पूर्णांक ret;
	काष्ठा netup_i2c *i2c;

	अगर (bus_num < 0 || bus_num > 1) अणु
		dev_err(&ndev->pci_dev->dev,
			"%s(): invalid bus_num %d\n", __func__, bus_num);
		वापस -EINVAL;
	पूर्ण
	i2c = &ndev->i2c[bus_num];
	spin_lock_init(&i2c->lock);
	init_रुकोqueue_head(&i2c->wq);
	i2c->regs = (काष्ठा netup_i2c_regs __iomem *)(ndev->bmmio0 +
		(bus_num == 0 ? NETUP_I2C_BUS0_ADDR : NETUP_I2C_BUS1_ADDR));
	netup_i2c_reset(i2c);
	i2c->adap = netup_i2c_adapter;
	i2c->adap.dev.parent = &ndev->pci_dev->dev;
	i2c_set_adapdata(&i2c->adap, i2c);
	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret)
		वापस ret;
	dev_info(&ndev->pci_dev->dev,
		"%s(): registered I2C bus %d at 0x%x\n",
		__func__,
		bus_num, (bus_num == 0 ?
			NETUP_I2C_BUS0_ADDR :
			NETUP_I2C_BUS1_ADDR));
	वापस 0;
पूर्ण

अटल व्योम netup_i2c_हटाओ(काष्ठा netup_unidvb_dev *ndev, पूर्णांक bus_num)
अणु
	काष्ठा netup_i2c *i2c;

	अगर (bus_num < 0 || bus_num > 1) अणु
		dev_err(&ndev->pci_dev->dev,
			"%s(): invalid bus number %d\n", __func__, bus_num);
		वापस;
	पूर्ण
	i2c = &ndev->i2c[bus_num];
	netup_i2c_reset(i2c);
	/* हटाओ adapter */
	i2c_del_adapter(&i2c->adap);
	dev_info(&ndev->pci_dev->dev,
		"netup_i2c_remove: unregistered I2C bus %d\n", bus_num);
पूर्ण

पूर्णांक netup_i2c_रेजिस्टर(काष्ठा netup_unidvb_dev *ndev)
अणु
	पूर्णांक ret;

	ret = netup_i2c_init(ndev, 0);
	अगर (ret)
		वापस ret;
	ret = netup_i2c_init(ndev, 1);
	अगर (ret) अणु
		netup_i2c_हटाओ(ndev, 0);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

व्योम netup_i2c_unरेजिस्टर(काष्ठा netup_unidvb_dev *ndev)
अणु
	netup_i2c_हटाओ(ndev, 0);
	netup_i2c_हटाओ(ndev, 1);
पूर्ण

