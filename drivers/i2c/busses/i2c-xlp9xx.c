<शैली गुरु>
/*
 * Copyright (c) 2003-2015 Broadcom Corporation
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>

#घोषणा XLP9XX_I2C_DIV			0x0
#घोषणा XLP9XX_I2C_CTRL			0x1
#घोषणा XLP9XX_I2C_CMD			0x2
#घोषणा XLP9XX_I2C_STATUS		0x3
#घोषणा XLP9XX_I2C_MTXFIFO		0x4
#घोषणा XLP9XX_I2C_MRXFIFO		0x5
#घोषणा XLP9XX_I2C_MFIFOCTRL		0x6
#घोषणा XLP9XX_I2C_STXFIFO		0x7
#घोषणा XLP9XX_I2C_SRXFIFO		0x8
#घोषणा XLP9XX_I2C_SFIFOCTRL		0x9
#घोषणा XLP9XX_I2C_SLAVEADDR		0xA
#घोषणा XLP9XX_I2C_OWNADDR		0xB
#घोषणा XLP9XX_I2C_FIFOWCNT		0xC
#घोषणा XLP9XX_I2C_INTEN		0xD
#घोषणा XLP9XX_I2C_INTST		0xE
#घोषणा XLP9XX_I2C_WAITCNT		0xF
#घोषणा XLP9XX_I2C_TIMEOUT		0X10
#घोषणा XLP9XX_I2C_GENCALLADDR		0x11

#घोषणा XLP9XX_I2C_STATUS_BUSY		BIT(0)

#घोषणा XLP9XX_I2C_CMD_START		BIT(7)
#घोषणा XLP9XX_I2C_CMD_STOP		BIT(6)
#घोषणा XLP9XX_I2C_CMD_READ		BIT(5)
#घोषणा XLP9XX_I2C_CMD_WRITE		BIT(4)
#घोषणा XLP9XX_I2C_CMD_ACK		BIT(3)

#घोषणा XLP9XX_I2C_CTRL_MCTLEN_SHIFT	16
#घोषणा XLP9XX_I2C_CTRL_MCTLEN_MASK	0xffff0000
#घोषणा XLP9XX_I2C_CTRL_RST		BIT(8)
#घोषणा XLP9XX_I2C_CTRL_EN		BIT(6)
#घोषणा XLP9XX_I2C_CTRL_MASTER		BIT(4)
#घोषणा XLP9XX_I2C_CTRL_FIFORD		BIT(1)
#घोषणा XLP9XX_I2C_CTRL_ADDMODE		BIT(0)

#घोषणा XLP9XX_I2C_INTEN_NACKADDR	BIT(25)
#घोषणा XLP9XX_I2C_INTEN_SADDR		BIT(13)
#घोषणा XLP9XX_I2C_INTEN_DATADONE	BIT(12)
#घोषणा XLP9XX_I2C_INTEN_ARLOST		BIT(11)
#घोषणा XLP9XX_I2C_INTEN_MFIFOFULL	BIT(4)
#घोषणा XLP9XX_I2C_INTEN_MFIFOEMTY	BIT(3)
#घोषणा XLP9XX_I2C_INTEN_MFIFOHI	BIT(2)
#घोषणा XLP9XX_I2C_INTEN_BUSERR		BIT(0)

#घोषणा XLP9XX_I2C_MFIFOCTRL_HITH_SHIFT		8
#घोषणा XLP9XX_I2C_MFIFOCTRL_LOTH_SHIFT		0
#घोषणा XLP9XX_I2C_MFIFOCTRL_RST		BIT(16)

#घोषणा XLP9XX_I2C_SLAVEADDR_RW			BIT(0)
#घोषणा XLP9XX_I2C_SLAVEADDR_ADDR_SHIFT		1

#घोषणा XLP9XX_I2C_IP_CLK_FREQ		133000000UL
#घोषणा XLP9XX_I2C_FIFO_SIZE		0x80U
#घोषणा XLP9XX_I2C_TIMEOUT_MS		1000
#घोषणा XLP9XX_I2C_BUSY_TIMEOUT		50

#घोषणा XLP9XX_I2C_FIFO_WCNT_MASK	0xff
#घोषणा XLP9XX_I2C_STATUS_ERRMASK	(XLP9XX_I2C_INTEN_ARLOST | \
			XLP9XX_I2C_INTEN_NACKADDR | XLP9XX_I2C_INTEN_BUSERR)

काष्ठा xlp9xx_i2c_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_adapter adapter;
	काष्ठा completion msg_complete;
	काष्ठा i2c_smbus_alert_setup alert_data;
	काष्ठा i2c_client *ara;
	पूर्णांक irq;
	bool msg_पढ़ो;
	bool len_recv;
	bool client_pec;
	u32 __iomem *base;
	u32 msg_buf_reमुख्यing;
	u32 msg_len;
	u32 ip_clk_hz;
	u32 clk_hz;
	u32 msg_err;
	u8 *msg_buf;
पूर्ण;

अटल अंतरभूत व्योम xlp9xx_ग_लिखो_i2c_reg(काष्ठा xlp9xx_i2c_dev *priv,
					अचिन्हित दीर्घ reg, u32 val)
अणु
	ग_लिखोl(val, priv->base + reg);
पूर्ण

अटल अंतरभूत u32 xlp9xx_पढ़ो_i2c_reg(काष्ठा xlp9xx_i2c_dev *priv,
				      अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(priv->base + reg);
पूर्ण

अटल व्योम xlp9xx_i2c_mask_irq(काष्ठा xlp9xx_i2c_dev *priv, u32 mask)
अणु
	u32 पूर्णांकen;

	पूर्णांकen = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_INTEN) & ~mask;
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTEN, पूर्णांकen);
पूर्ण

अटल व्योम xlp9xx_i2c_unmask_irq(काष्ठा xlp9xx_i2c_dev *priv, u32 mask)
अणु
	u32 पूर्णांकen;

	पूर्णांकen = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_INTEN) | mask;
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTEN, पूर्णांकen);
पूर्ण

अटल व्योम xlp9xx_i2c_update_rx_fअगरo_thres(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 thres;

	अगर (priv->len_recv)
		/* पूर्णांकerrupt after the first पढ़ो to examine
		 * the length byte beक्रमe proceeding further
		 */
		thres = 1;
	अन्यथा अगर (priv->msg_buf_reमुख्यing > XLP9XX_I2C_FIFO_SIZE)
		thres = XLP9XX_I2C_FIFO_SIZE;
	अन्यथा
		thres = priv->msg_buf_reमुख्यing;

	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_MFIFOCTRL,
			     thres << XLP9XX_I2C_MFIFOCTRL_HITH_SHIFT);
पूर्ण

अटल व्योम xlp9xx_i2c_fill_tx_fअगरo(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 len, i;
	u8 *buf = priv->msg_buf;

	len = min(priv->msg_buf_reमुख्यing, XLP9XX_I2C_FIFO_SIZE);
	क्रम (i = 0; i < len; i++)
		xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_MTXFIFO, buf[i]);
	priv->msg_buf_reमुख्यing -= len;
	priv->msg_buf += len;
पूर्ण

अटल व्योम xlp9xx_i2c_update_rlen(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 val, len;

	/*
	 * Update receive length. Re-पढ़ो len to get the latest value,
	 * and then add 4 to have a minimum value that can be safely
	 * written. This is to account क्रम the byte पढ़ो above, the
	 * transfer in progress and any delays in the रेजिस्टर I/O
	 */
	val = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_CTRL);
	len = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_FIFOWCNT) &
				  XLP9XX_I2C_FIFO_WCNT_MASK;
	len = max_t(u32, priv->msg_len, len + 4);
	अगर (len >= I2C_SMBUS_BLOCK_MAX + 2)
		वापस;
	val = (val & ~XLP9XX_I2C_CTRL_MCTLEN_MASK) |
			(len << XLP9XX_I2C_CTRL_MCTLEN_SHIFT);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CTRL, val);
पूर्ण

अटल व्योम xlp9xx_i2c_drain_rx_fअगरo(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 len, i;
	u8 rlen, *buf = priv->msg_buf;

	len = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_FIFOWCNT) &
				  XLP9XX_I2C_FIFO_WCNT_MASK;
	अगर (!len)
		वापस;
	अगर (priv->len_recv) अणु
		/* पढ़ो length byte */
		rlen = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_MRXFIFO);

		/*
		 * We expect at least 2 पूर्णांकerrupts क्रम I2C_M_RECV_LEN
		 * transactions. The length is updated during the first
		 * पूर्णांकerrupt, and the buffer contents are only copied
		 * during subsequent पूर्णांकerrupts. If in हाल the पूर्णांकerrupts
		 * get merged we would complete the transaction without
		 * copying out the bytes from RX fअगरo. To aव्योम this now we
		 * drain the fअगरo as and when data is available.
		 * We drained the rlen byte alपढ़ोy, decrement total length
		 * by one.
		 */

		len--;
		अगर (rlen > I2C_SMBUS_BLOCK_MAX || rlen == 0) अणु
			rlen = 0;	/*पात transfer */
			priv->msg_buf_reमुख्यing = 0;
			priv->msg_len = 0;
			xlp9xx_i2c_update_rlen(priv);
			वापस;
		पूर्ण

		*buf++ = rlen;
		अगर (priv->client_pec)
			++rlen; /* account क्रम error check byte */
		/* update reमुख्यing bytes and message length */
		priv->msg_buf_reमुख्यing = rlen;
		priv->msg_len = rlen + 1;
		xlp9xx_i2c_update_rlen(priv);
		priv->len_recv = false;
	पूर्ण

	len = min(priv->msg_buf_reमुख्यing, len);
	क्रम (i = 0; i < len; i++, buf++)
		*buf = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_MRXFIFO);

	priv->msg_buf_reमुख्यing -= len;
	priv->msg_buf = buf;

	अगर (priv->msg_buf_reमुख्यing)
		xlp9xx_i2c_update_rx_fअगरo_thres(priv);
पूर्ण

अटल irqवापस_t xlp9xx_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xlp9xx_i2c_dev *priv = dev_id;
	u32 status;

	status = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_INTST);
	अगर (status == 0)
		वापस IRQ_NONE;

	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTST, status);
	अगर (status & XLP9XX_I2C_STATUS_ERRMASK) अणु
		priv->msg_err = status;
		जाओ xfer_करोne;
	पूर्ण

	/* SADDR ACK क्रम SMBUS_QUICK */
	अगर ((status & XLP9XX_I2C_INTEN_SADDR) && (priv->msg_len == 0))
		जाओ xfer_करोne;

	अगर (!priv->msg_पढ़ो) अणु
		अगर (status & XLP9XX_I2C_INTEN_MFIFOEMTY) अणु
			/* TX FIFO got empty, fill it up again */
			अगर (priv->msg_buf_reमुख्यing)
				xlp9xx_i2c_fill_tx_fअगरo(priv);
			अन्यथा
				xlp9xx_i2c_mask_irq(priv,
						    XLP9XX_I2C_INTEN_MFIFOEMTY);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (status & (XLP9XX_I2C_INTEN_DATADONE |
			      XLP9XX_I2C_INTEN_MFIFOHI)) अणु
			/* data is in FIFO, पढ़ो it */
			अगर (priv->msg_buf_reमुख्यing)
				xlp9xx_i2c_drain_rx_fअगरo(priv);
		पूर्ण
	पूर्ण

	/* Transfer complete */
	अगर (status & XLP9XX_I2C_INTEN_DATADONE)
		जाओ xfer_करोne;

	वापस IRQ_HANDLED;

xfer_करोne:
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);
	complete(&priv->msg_complete);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_check_bus_status(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 status;
	u32 busy_समयout = XLP9XX_I2C_BUSY_TIMEOUT;

	जबतक (busy_समयout) अणु
		status = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_STATUS);
		अगर ((status & XLP9XX_I2C_STATUS_BUSY) == 0)
			अवरोध;

		busy_समयout--;
		usleep_range(1000, 1100);
	पूर्ण

	अगर (!busy_समयout)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_init(काष्ठा xlp9xx_i2c_dev *priv)
अणु
	u32 prescale;

	/*
	 * The controller uses 5 * SCL घड़ी पूर्णांकernally.
	 * So prescale value should be भागided by 5.
	 */
	prescale = DIV_ROUND_UP(priv->ip_clk_hz, priv->clk_hz);
	prescale = ((prescale - 8) / 5) - 1;
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CTRL, XLP9XX_I2C_CTRL_RST);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CTRL, XLP9XX_I2C_CTRL_EN |
			     XLP9XX_I2C_CTRL_MASTER);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_DIV, prescale);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_xfer_msg(काष्ठा xlp9xx_i2c_dev *priv, काष्ठा i2c_msg *msg,
			       पूर्णांक last_msg)
अणु
	अचिन्हित दीर्घ समयleft;
	u32 पूर्णांकr_mask, cmd, val, len;

	priv->msg_buf = msg->buf;
	priv->msg_buf_reमुख्यing = priv->msg_len = msg->len;
	priv->msg_err = 0;
	priv->msg_पढ़ो = (msg->flags & I2C_M_RD);
	reinit_completion(&priv->msg_complete);

	/* Reset FIFO */
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_MFIFOCTRL,
			     XLP9XX_I2C_MFIFOCTRL_RST);

	/* set slave addr */
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_SLAVEADDR,
			     (msg->addr << XLP9XX_I2C_SLAVEADDR_ADDR_SHIFT) |
			     (priv->msg_पढ़ो ? XLP9XX_I2C_SLAVEADDR_RW : 0));

	/* Build control word क्रम transfer */
	val = xlp9xx_पढ़ो_i2c_reg(priv, XLP9XX_I2C_CTRL);
	अगर (!priv->msg_पढ़ो)
		val &= ~XLP9XX_I2C_CTRL_FIFORD;
	अन्यथा
		val |= XLP9XX_I2C_CTRL_FIFORD;	/* पढ़ो */

	अगर (msg->flags & I2C_M_TEN)
		val |= XLP9XX_I2C_CTRL_ADDMODE;	/* 10-bit address mode*/
	अन्यथा
		val &= ~XLP9XX_I2C_CTRL_ADDMODE;

	priv->len_recv = msg->flags & I2C_M_RECV_LEN;
	len = priv->len_recv ? I2C_SMBUS_BLOCK_MAX + 2 : msg->len;
	priv->client_pec = msg->flags & I2C_CLIENT_PEC;

	/* set FIFO threshold अगर पढ़ोing */
	अगर (priv->msg_पढ़ो)
		xlp9xx_i2c_update_rx_fअगरo_thres(priv);

	/* set data length to be transferred */
	val = (val & ~XLP9XX_I2C_CTRL_MCTLEN_MASK) |
	      (len << XLP9XX_I2C_CTRL_MCTLEN_SHIFT);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CTRL, val);

	/* fill fअगरo during tx */
	अगर (!priv->msg_पढ़ो)
		xlp9xx_i2c_fill_tx_fअगरo(priv);

	/* set पूर्णांकerrupt mask */
	पूर्णांकr_mask = (XLP9XX_I2C_INTEN_ARLOST | XLP9XX_I2C_INTEN_BUSERR |
		     XLP9XX_I2C_INTEN_NACKADDR | XLP9XX_I2C_INTEN_DATADONE);

	अगर (priv->msg_पढ़ो) अणु
		पूर्णांकr_mask |= XLP9XX_I2C_INTEN_MFIFOHI;
		अगर (msg->len == 0)
			पूर्णांकr_mask |= XLP9XX_I2C_INTEN_SADDR;
	पूर्ण अन्यथा अणु
		अगर (msg->len == 0)
			पूर्णांकr_mask |= XLP9XX_I2C_INTEN_SADDR;
		अन्यथा
			पूर्णांकr_mask |= XLP9XX_I2C_INTEN_MFIFOEMTY;
	पूर्ण
	xlp9xx_i2c_unmask_irq(priv, पूर्णांकr_mask);

	/* set cmd reg */
	cmd = XLP9XX_I2C_CMD_START;
	अगर (msg->len)
		cmd |= (priv->msg_पढ़ो ?
			XLP9XX_I2C_CMD_READ : XLP9XX_I2C_CMD_WRITE);
	अगर (last_msg)
		cmd |= XLP9XX_I2C_CMD_STOP;

	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CMD, cmd);

	समयleft = msecs_to_jअगरfies(XLP9XX_I2C_TIMEOUT_MS);
	समयleft = रुको_क्रम_completion_समयout(&priv->msg_complete, समयleft);

	अगर (priv->msg_err & XLP9XX_I2C_INTEN_BUSERR) अणु
		dev_dbg(priv->dev, "transfer error %x!\n", priv->msg_err);
		xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CMD, XLP9XX_I2C_CMD_STOP);
		वापस -EIO;
	पूर्ण अन्यथा अगर (priv->msg_err & XLP9XX_I2C_INTEN_NACKADDR) अणु
		वापस -ENXIO;
	पूर्ण

	अगर (समयleft == 0) अणु
		dev_dbg(priv->dev, "i2c transfer timed out!\n");
		xlp9xx_i2c_init(priv);
		वापस -ETIMEDOUT;
	पूर्ण

	/* update msg->len with actual received length */
	अगर (msg->flags & I2C_M_RECV_LEN) अणु
		अगर (!priv->msg_len)
			वापस -EPROTO;
		msg->len = priv->msg_len;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
			   पूर्णांक num)
अणु
	पूर्णांक i, ret;
	काष्ठा xlp9xx_i2c_dev *priv = i2c_get_adapdata(adap);

	ret = xlp9xx_i2c_check_bus_status(priv);
	अगर (ret) अणु
		xlp9xx_i2c_init(priv);
		ret = xlp9xx_i2c_check_bus_status(priv);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		ret = xlp9xx_i2c_xfer_msg(priv, &msgs[i], i == num - 1);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस num;
पूर्ण

अटल u32 xlp9xx_i2c_functionality(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_EMUL | I2C_FUNC_SMBUS_READ_BLOCK_DATA |
			I2C_FUNC_I2C | I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm xlp9xx_i2c_algo = अणु
	.master_xfer = xlp9xx_i2c_xfer,
	.functionality = xlp9xx_i2c_functionality,
पूर्ण;

अटल पूर्णांक xlp9xx_i2c_get_frequency(काष्ठा platक्रमm_device *pdev,
				    काष्ठा xlp9xx_i2c_dev *priv)
अणु
	काष्ठा clk *clk;
	u32 freq;
	पूर्णांक err;

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		priv->ip_clk_hz = XLP9XX_I2C_IP_CLK_FREQ;
		dev_dbg(&pdev->dev, "using default input frequency %u\n",
			priv->ip_clk_hz);
	पूर्ण अन्यथा अणु
		priv->ip_clk_hz = clk_get_rate(clk);
	पूर्ण

	err = device_property_पढ़ो_u32(&pdev->dev, "clock-frequency", &freq);
	अगर (err) अणु
		freq = I2C_MAX_STANDARD_MODE_FREQ;
		dev_dbg(&pdev->dev, "using default frequency %u\n", freq);
	पूर्ण अन्यथा अगर (freq == 0 || freq > I2C_MAX_FAST_MODE_FREQ) अणु
		dev_warn(&pdev->dev, "invalid frequency %u, using default\n",
			 freq);
		freq = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण
	priv->clk_hz = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_smbus_setup(काष्ठा xlp9xx_i2c_dev *priv,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_client *ara;

	अगर (!priv->alert_data.irq)
		वापस -EINVAL;

	ara = i2c_new_smbus_alert_device(&priv->adapter, &priv->alert_data);
	अगर (IS_ERR(ara))
		वापस PTR_ERR(ara);

	priv->ara = ara;

	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlp9xx_i2c_dev *priv;
	पूर्णांक err = 0;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->irq = platक्रमm_get_irq(pdev, 0);
	अगर (priv->irq <= 0)
		वापस priv->irq;
	/* SMBAlert irq */
	priv->alert_data.irq = platक्रमm_get_irq(pdev, 1);
	अगर (priv->alert_data.irq <= 0)
		priv->alert_data.irq = 0;

	xlp9xx_i2c_get_frequency(pdev, priv);
	xlp9xx_i2c_init(priv);

	err = devm_request_irq(&pdev->dev, priv->irq, xlp9xx_i2c_isr, 0,
			       pdev->name, priv);
	अगर (err) अणु
		dev_err(&pdev->dev, "IRQ request failed!\n");
		वापस err;
	पूर्ण

	init_completion(&priv->msg_complete);
	priv->adapter.dev.parent = &pdev->dev;
	priv->adapter.algo = &xlp9xx_i2c_algo;
	priv->adapter.class = I2C_CLASS_HWMON;
	ACPI_COMPANION_SET(&priv->adapter.dev, ACPI_COMPANION(&pdev->dev));
	priv->adapter.dev.of_node = pdev->dev.of_node;
	priv->dev = &pdev->dev;

	snम_लिखो(priv->adapter.name, माप(priv->adapter.name), "xlp9xx-i2c");
	i2c_set_adapdata(&priv->adapter, priv);

	err = i2c_add_adapter(&priv->adapter);
	अगर (err)
		वापस err;

	err = xlp9xx_i2c_smbus_setup(priv, pdev);
	अगर (err)
		dev_dbg(&pdev->dev, "No active SMBus alert %d\n", err);

	platक्रमm_set_drvdata(pdev, priv);
	dev_dbg(&pdev->dev, "I2C bus:%d added\n", priv->adapter.nr);

	वापस 0;
पूर्ण

अटल पूर्णांक xlp9xx_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xlp9xx_i2c_dev *priv;

	priv = platक्रमm_get_drvdata(pdev);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_INTEN, 0);
	synchronize_irq(priv->irq);
	i2c_del_adapter(&priv->adapter);
	xlp9xx_ग_लिखो_i2c_reg(priv, XLP9XX_I2C_CTRL, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id xlp9xx_i2c_of_match[] = अणु
	अणु .compatible = "netlogic,xlp980-i2c", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xlp9xx_i2c_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xlp9xx_i2c_acpi_ids[] = अणु
	अणु"BRCM9007", 0पूर्ण,
	अणु"CAV9007",  0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xlp9xx_i2c_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver xlp9xx_i2c_driver = अणु
	.probe = xlp9xx_i2c_probe,
	.हटाओ = xlp9xx_i2c_हटाओ,
	.driver = अणु
		.name = "xlp9xx-i2c",
		.of_match_table = xlp9xx_i2c_of_match,
		.acpi_match_table = ACPI_PTR(xlp9xx_i2c_acpi_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xlp9xx_i2c_driver);

MODULE_AUTHOR("Subhendu Sekhar Behera <sbehera@broadcom.com>");
MODULE_DESCRIPTION("XLP9XX/5XX I2C Bus Controller Driver");
MODULE_LICENSE("GPL v2");
