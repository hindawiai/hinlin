<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ingenic JZ4780 I2C bus driver
 *
 * Copyright (C) 2006 - 2009 Ingenic Semiconductor Inc.
 * Copyright (C) 2015 Imagination Technologies
 * Copyright (C) 2019 ोउॉओौओ (Zhou Yanjie) <zhouyanjie@wanyeetech.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/समय.स>

#घोषणा JZ4780_I2C_CTRL		0x00
#घोषणा JZ4780_I2C_TAR		0x04
#घोषणा JZ4780_I2C_SAR		0x08
#घोषणा JZ4780_I2C_DC		0x10
#घोषणा JZ4780_I2C_SHCNT	0x14
#घोषणा JZ4780_I2C_SLCNT	0x18
#घोषणा JZ4780_I2C_FHCNT	0x1C
#घोषणा JZ4780_I2C_FLCNT	0x20
#घोषणा JZ4780_I2C_INTST	0x2C
#घोषणा JZ4780_I2C_INTM		0x30
#घोषणा JZ4780_I2C_RXTL		0x38
#घोषणा JZ4780_I2C_TXTL		0x3C
#घोषणा JZ4780_I2C_CINTR	0x40
#घोषणा JZ4780_I2C_CRXUF	0x44
#घोषणा JZ4780_I2C_CRXOF	0x48
#घोषणा JZ4780_I2C_CTXOF	0x4C
#घोषणा JZ4780_I2C_CRXREQ	0x50
#घोषणा JZ4780_I2C_CTXABRT	0x54
#घोषणा JZ4780_I2C_CRXDONE	0x58
#घोषणा JZ4780_I2C_CACT		0x5C
#घोषणा JZ4780_I2C_CSTP		0x60
#घोषणा JZ4780_I2C_CSTT		0x64
#घोषणा JZ4780_I2C_CGC		0x68
#घोषणा JZ4780_I2C_ENB		0x6C
#घोषणा JZ4780_I2C_STA		0x70
#घोषणा JZ4780_I2C_TXABRT	0x80
#घोषणा JZ4780_I2C_DMACR	0x88
#घोषणा JZ4780_I2C_DMATDLR	0x8C
#घोषणा JZ4780_I2C_DMARDLR	0x90
#घोषणा JZ4780_I2C_SDASU	0x94
#घोषणा JZ4780_I2C_ACKGC	0x98
#घोषणा JZ4780_I2C_ENSTA	0x9C
#घोषणा JZ4780_I2C_SDAHD	0xD0
#घोषणा X1000_I2C_SDAHD		0x7C

#घोषणा JZ4780_I2C_CTRL_STPHLD		BIT(7)
#घोषणा JZ4780_I2C_CTRL_SLVDIS		BIT(6)
#घोषणा JZ4780_I2C_CTRL_REST		BIT(5)
#घोषणा JZ4780_I2C_CTRL_MATP		BIT(4)
#घोषणा JZ4780_I2C_CTRL_SATP		BIT(3)
#घोषणा JZ4780_I2C_CTRL_SPDF		BIT(2)
#घोषणा JZ4780_I2C_CTRL_SPDS		BIT(1)
#घोषणा JZ4780_I2C_CTRL_MD		BIT(0)

#घोषणा JZ4780_I2C_STA_SLVACT		BIT(6)
#घोषणा JZ4780_I2C_STA_MSTACT		BIT(5)
#घोषणा JZ4780_I2C_STA_RFF		BIT(4)
#घोषणा JZ4780_I2C_STA_RFNE		BIT(3)
#घोषणा JZ4780_I2C_STA_TFE		BIT(2)
#घोषणा JZ4780_I2C_STA_TFNF		BIT(1)
#घोषणा JZ4780_I2C_STA_ACT		BIT(0)

#घोषणा X1000_I2C_DC_STOP		BIT(9)

#घोषणा JZ4780_I2C_INTST_IGC		BIT(11)
#घोषणा JZ4780_I2C_INTST_ISTT		BIT(10)
#घोषणा JZ4780_I2C_INTST_ISTP		BIT(9)
#घोषणा JZ4780_I2C_INTST_IACT		BIT(8)
#घोषणा JZ4780_I2C_INTST_RXDN		BIT(7)
#घोषणा JZ4780_I2C_INTST_TXABT		BIT(6)
#घोषणा JZ4780_I2C_INTST_RDREQ		BIT(5)
#घोषणा JZ4780_I2C_INTST_TXEMP		BIT(4)
#घोषणा JZ4780_I2C_INTST_TXOF		BIT(3)
#घोषणा JZ4780_I2C_INTST_RXFL		BIT(2)
#घोषणा JZ4780_I2C_INTST_RXOF		BIT(1)
#घोषणा JZ4780_I2C_INTST_RXUF		BIT(0)

#घोषणा JZ4780_I2C_INTM_MIGC		BIT(11)
#घोषणा JZ4780_I2C_INTM_MISTT		BIT(10)
#घोषणा JZ4780_I2C_INTM_MISTP		BIT(9)
#घोषणा JZ4780_I2C_INTM_MIACT		BIT(8)
#घोषणा JZ4780_I2C_INTM_MRXDN		BIT(7)
#घोषणा JZ4780_I2C_INTM_MTXABT		BIT(6)
#घोषणा JZ4780_I2C_INTM_MRDREQ		BIT(5)
#घोषणा JZ4780_I2C_INTM_MTXEMP		BIT(4)
#घोषणा JZ4780_I2C_INTM_MTXOF		BIT(3)
#घोषणा JZ4780_I2C_INTM_MRXFL		BIT(2)
#घोषणा JZ4780_I2C_INTM_MRXOF		BIT(1)
#घोषणा JZ4780_I2C_INTM_MRXUF		BIT(0)

#घोषणा JZ4780_I2C_DC_READ		BIT(8)

#घोषणा JZ4780_I2C_SDAHD_HDENB		BIT(8)

#घोषणा JZ4780_I2C_ENB_I2C		BIT(0)

#घोषणा JZ4780_I2CSHCNT_ADJUST(n)	(((n) - 8) < 6 ? 6 : ((n) - 8))
#घोषणा JZ4780_I2CSLCNT_ADJUST(n)	(((n) - 1) < 8 ? 8 : ((n) - 1))
#घोषणा JZ4780_I2CFHCNT_ADJUST(n)	(((n) - 8) < 6 ? 6 : ((n) - 8))
#घोषणा JZ4780_I2CFLCNT_ADJUST(n)	(((n) - 1) < 8 ? 8 : ((n) - 1))

#घोषणा JZ4780_I2C_FIFO_LEN	16

#घोषणा X1000_I2C_FIFO_LEN	64

#घोषणा JZ4780_I2C_TIMEOUT	300

#घोषणा बफ_मानE 200

क्रमागत ingenic_i2c_version अणु
	ID_JZ4780,
	ID_X1000,
पूर्ण;

/* ingenic_i2c_config: SoC specअगरic config data. */
काष्ठा ingenic_i2c_config अणु
	क्रमागत ingenic_i2c_version version;

	पूर्णांक fअगरosize;
	पूर्णांक tx_level;
	पूर्णांक rx_level;
पूर्ण;

काष्ठा jz4780_i2c अणु
	व्योम __iomem		*iomem;
	पूर्णांक			 irq;
	काष्ठा clk		*clk;
	काष्ठा i2c_adapter	 adap;
	स्थिर काष्ठा ingenic_i2c_config *cdata;

	/* lock to protect rbuf and wbuf between xfer_rd/wr and irq handler */
	spinlock_t		lock;

	/* beginning of lock scope */
	अचिन्हित अक्षर		*rbuf;
	पूर्णांक			rd_total_len;
	पूर्णांक			rd_data_xfered;
	पूर्णांक			rd_cmd_xfered;

	अचिन्हित अक्षर		*wbuf;
	पूर्णांक			wt_len;

	पूर्णांक			is_ग_लिखो;
	पूर्णांक			stop_hold;
	पूर्णांक			speed;

	पूर्णांक			data_buf[बफ_मानE];
	पूर्णांक			cmd_buf[बफ_मानE];
	पूर्णांक			cmd;

	/* end of lock scope */
	काष्ठा completion	trans_रुकोq;
पूर्ण;

अटल अंतरभूत अचिन्हित लघु jz4780_i2c_पढ़ोw(काष्ठा jz4780_i2c *i2c,
					      अचिन्हित दीर्घ offset)
अणु
	वापस पढ़ोw(i2c->iomem + offset);
पूर्ण

अटल अंतरभूत व्योम jz4780_i2c_ग_लिखोw(काष्ठा jz4780_i2c *i2c,
				     अचिन्हित दीर्घ offset, अचिन्हित लघु val)
अणु
	ग_लिखोw(val, i2c->iomem + offset);
पूर्ण

अटल पूर्णांक jz4780_i2c_disable(काष्ठा jz4780_i2c *i2c)
अणु
	अचिन्हित लघु regval;
	अचिन्हित दीर्घ loops = 5;

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_ENB, 0);

	करो अणु
		regval = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_ENSTA);
		अगर (!(regval & JZ4780_I2C_ENB_I2C))
			वापस 0;

		usleep_range(5000, 15000);
	पूर्ण जबतक (--loops);

	dev_err(&i2c->adap.dev, "disable failed: ENSTA=0x%04x\n", regval);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक jz4780_i2c_enable(काष्ठा jz4780_i2c *i2c)
अणु
	अचिन्हित लघु regval;
	अचिन्हित दीर्घ loops = 5;

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_ENB, 1);

	करो अणु
		regval = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_ENSTA);
		अगर (regval & JZ4780_I2C_ENB_I2C)
			वापस 0;

		usleep_range(5000, 15000);
	पूर्ण जबतक (--loops);

	dev_err(&i2c->adap.dev, "enable failed: ENSTA=0x%04x\n", regval);
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक jz4780_i2c_set_target(काष्ठा jz4780_i2c *i2c, अचिन्हित अक्षर address)
अणु
	अचिन्हित लघु regval;
	अचिन्हित दीर्घ loops = 5;

	करो अणु
		regval = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_STA);
		अगर ((regval & JZ4780_I2C_STA_TFE) &&
		    !(regval & JZ4780_I2C_STA_MSTACT))
			अवरोध;

		usleep_range(5000, 15000);
	पूर्ण जबतक (--loops);

	अगर (loops) अणु
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_TAR, address);
		वापस 0;
	पूर्ण

	dev_err(&i2c->adap.dev,
		"set device to address 0x%02x failed, STA=0x%04x\n",
		address, regval);

	वापस -ENXIO;
पूर्ण

अटल पूर्णांक jz4780_i2c_set_speed(काष्ठा jz4780_i2c *i2c)
अणु
	पूर्णांक dev_clk_khz = clk_get_rate(i2c->clk) / 1000;
	पूर्णांक cnt_high = 0;	/* HIGH period count of the SCL घड़ी */
	पूर्णांक cnt_low = 0;	/* LOW period count of the SCL घड़ी */
	पूर्णांक cnt_period = 0;	/* period count of the SCL घड़ी */
	पूर्णांक setup_समय = 0;
	पूर्णांक hold_समय = 0;
	अचिन्हित लघु पंचांगp = 0;
	पूर्णांक i2c_clk = i2c->speed;

	अगर (jz4780_i2c_disable(i2c))
		dev_dbg(&i2c->adap.dev, "i2c not disabled\n");

	/*
	 * 1 JZ4780_I2C cycle equals to cnt_period PCLK(i2c_clk)
	 * standard mode, min LOW and HIGH period are 4700 ns and 4000 ns
	 * fast mode, min LOW and HIGH period are 1300 ns and 600 ns
	 */
	cnt_period = dev_clk_khz / i2c_clk;

	अगर (i2c_clk <= 100)
		cnt_high = (cnt_period * 4000) / (4700 + 4000);
	अन्यथा
		cnt_high = (cnt_period * 600) / (1300 + 600);

	cnt_low = cnt_period - cnt_high;

	/*
	 * NOTE: JZ4780_I2C_CTRL_REST can't set when i2c enabled, because
	 * normal पढ़ो are 2 messages, we cannot disable i2c controller
	 * between these two messages, this means that we must always set
	 * JZ4780_I2C_CTRL_REST when init JZ4780_I2C_CTRL
	 *
	 */
	अगर (i2c_clk <= 100) अणु
		पंचांगp = JZ4780_I2C_CTRL_SPDS | JZ4780_I2C_CTRL_REST
		      | JZ4780_I2C_CTRL_SLVDIS | JZ4780_I2C_CTRL_MD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);

		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_SHCNT,
				  JZ4780_I2CSHCNT_ADJUST(cnt_high));
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_SLCNT,
				  JZ4780_I2CSLCNT_ADJUST(cnt_low));
	पूर्ण अन्यथा अणु
		पंचांगp = JZ4780_I2C_CTRL_SPDF | JZ4780_I2C_CTRL_REST
		      | JZ4780_I2C_CTRL_SLVDIS | JZ4780_I2C_CTRL_MD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);

		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_FHCNT,
				  JZ4780_I2CFHCNT_ADJUST(cnt_high));
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_FLCNT,
				  JZ4780_I2CFLCNT_ADJUST(cnt_low));
	पूर्ण

	/*
	 * a i2c device must पूर्णांकernally provide a hold समय at least 300ns
	 * tHD:DAT
	 *	Standard Mode: min=300ns, max=3450ns
	 *	Fast Mode: min=0ns, max=900ns
	 * tSU:DAT
	 *	Standard Mode: min=250ns, max=infinite
	 *	Fast Mode: min=100(250ns is recommended), max=infinite
	 *
	 * 1i2c_clk = 10^6 / dev_clk_khz
	 * on FPGA, dev_clk_khz = 12000, so 1i2c_clk = 1000/12 = 83ns
	 * on Pisces(1008M), dev_clk_khz=126000, so 1i2c_clk = 1000 / 126 = 8ns
	 *
	 * The actual hold समय is (SDAHD + 1) * (i2c_clk period).
	 *
	 * Length of setup समय calculated using (SDASU - 1) * (ic_clk_period)
	 *
	 */
	अगर (i2c_clk <= 100) अणु /* standard mode */
		setup_समय = 300;
		hold_समय = 400;
	पूर्ण अन्यथा अणु
		setup_समय = 450;
		hold_समय = 450;
	पूर्ण

	hold_समय = ((hold_समय * dev_clk_khz) / 1000000) - 1;
	setup_समय = ((setup_समय * dev_clk_khz) / 1000000)  + 1;

	अगर (setup_समय > 255)
		setup_समय = 255;

	अगर (setup_समय <= 0)
		setup_समय = 1;

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_SDASU, setup_समय);

	अगर (hold_समय > 255)
		hold_समय = 255;

	अगर (hold_समय >= 0) अणु
		/*i2c hold समय enable */
		अगर (i2c->cdata->version >= ID_X1000) अणु
			jz4780_i2c_ग_लिखोw(i2c, X1000_I2C_SDAHD, hold_समय);
		पूर्ण अन्यथा अणु
			hold_समय |= JZ4780_I2C_SDAHD_HDENB;
			jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_SDAHD, hold_समय);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* disable hold समय */
		अगर (i2c->cdata->version >= ID_X1000)
			jz4780_i2c_ग_लिखोw(i2c, X1000_I2C_SDAHD, 0);
		अन्यथा
			jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_SDAHD, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4780_i2c_cleanup(काष्ठा jz4780_i2c *i2c)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	अचिन्हित लघु पंचांगp;

	spin_lock_irqsave(&i2c->lock, flags);

	/* can send stop now अगर need */
	अगर (i2c->cdata->version < ID_X1000) अणु
		पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTRL);
		पंचांगp &= ~JZ4780_I2C_CTRL_STPHLD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);
	पूर्ण

	/* disable all पूर्णांकerrupts first */
	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM, 0);

	/* then clear all पूर्णांकerrupts */
	jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTXABRT);
	jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CINTR);

	/* then disable the controller */
	पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTRL);
	पंचांगp &= ~JZ4780_I2C_ENB_I2C;
	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);
	udelay(10);
	पंचांगp |= JZ4780_I2C_ENB_I2C;
	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);

	spin_unlock_irqrestore(&i2c->lock, flags);

	ret = jz4780_i2c_disable(i2c);
	अगर (ret)
		dev_err(&i2c->adap.dev,
			"unable to disable device during cleanup!\n");

	अगर (unlikely(jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_INTM)
		     & jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_INTST)))
		dev_err(&i2c->adap.dev,
			"device has interrupts after a complete cleanup!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_i2c_prepare(काष्ठा jz4780_i2c *i2c)
अणु
	jz4780_i2c_set_speed(i2c);
	वापस jz4780_i2c_enable(i2c);
पूर्ण

अटल व्योम jz4780_i2c_send_rcmd(काष्ठा jz4780_i2c *i2c,
								 पूर्णांक cmd_count,
								 पूर्णांक cmd_left)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < cmd_count - 1; i++)
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_DC, JZ4780_I2C_DC_READ);

	अगर ((cmd_left == 0) && (i2c->cdata->version >= ID_X1000))
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_DC,
				JZ4780_I2C_DC_READ | X1000_I2C_DC_STOP);
	अन्यथा
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_DC, JZ4780_I2C_DC_READ);
पूर्ण

अटल व्योम jz4780_i2c_trans_करोne(काष्ठा jz4780_i2c *i2c)
अणु
	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM, 0);
	complete(&i2c->trans_रुकोq);
पूर्ण

अटल irqवापस_t jz4780_i2c_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	अचिन्हित लघु पंचांगp;
	अचिन्हित लघु पूर्णांकst;
	अचिन्हित लघु पूर्णांकmsk;
	काष्ठा jz4780_i2c *i2c = dev_id;

	spin_lock(&i2c->lock);
	पूर्णांकmsk = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_INTM);
	पूर्णांकst = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_INTST);

	पूर्णांकst &= पूर्णांकmsk;

	अगर (पूर्णांकst & JZ4780_I2C_INTST_TXABT) अणु
		jz4780_i2c_trans_करोne(i2c);
		जाओ करोne;
	पूर्ण

	अगर (पूर्णांकst & JZ4780_I2C_INTST_RXOF) अणु
		dev_dbg(&i2c->adap.dev, "received fifo overflow!\n");
		jz4780_i2c_trans_करोne(i2c);
		जाओ करोne;
	पूर्ण

	/*
	 * When पढ़ोing, always drain RX FIFO beक्रमe we send more Read
	 * Commands to aव्योम fअगरo overrun
	 */
	अगर (i2c->is_ग_लिखो == 0) अणु
		पूर्णांक rd_left;

		जबतक ((jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_STA)
				  & JZ4780_I2C_STA_RFNE)) अणु
			*(i2c->rbuf++) = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_DC)
					 & 0xff;
			i2c->rd_data_xfered++;
			अगर (i2c->rd_data_xfered == i2c->rd_total_len) अणु
				jz4780_i2c_trans_करोne(i2c);
				जाओ करोne;
			पूर्ण
		पूर्ण

		rd_left = i2c->rd_total_len - i2c->rd_data_xfered;

		अगर (rd_left <= i2c->cdata->fअगरosize)
			jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_RXTL, rd_left - 1);
	पूर्ण

	अगर (पूर्णांकst & JZ4780_I2C_INTST_TXEMP) अणु
		अगर (i2c->is_ग_लिखो == 0) अणु
			पूर्णांक cmd_left = i2c->rd_total_len - i2c->rd_cmd_xfered;
			पूर्णांक max_send = (i2c->cdata->fअगरosize - 1)
					 - (i2c->rd_cmd_xfered
					 - i2c->rd_data_xfered);
			पूर्णांक cmd_to_send = min(cmd_left, max_send);

			अगर (i2c->rd_cmd_xfered != 0)
				cmd_to_send = min(cmd_to_send,
						  i2c->cdata->fअगरosize
						  - i2c->cdata->tx_level - 1);

			अगर (cmd_to_send) अणु
				i2c->rd_cmd_xfered += cmd_to_send;
				cmd_left = i2c->rd_total_len -
						i2c->rd_cmd_xfered;
				jz4780_i2c_send_rcmd(i2c,
						cmd_to_send, cmd_left);

			पूर्ण

			अगर (cmd_left == 0) अणु
				पूर्णांकmsk = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_INTM);
				पूर्णांकmsk &= ~JZ4780_I2C_INTM_MTXEMP;
				jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM, पूर्णांकmsk);

				अगर (i2c->cdata->version < ID_X1000) अणु
					पंचांगp = jz4780_i2c_पढ़ोw(i2c,
							JZ4780_I2C_CTRL);
					पंचांगp &= ~JZ4780_I2C_CTRL_STPHLD;
					jz4780_i2c_ग_लिखोw(i2c,
							JZ4780_I2C_CTRL, पंचांगp);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			अचिन्हित लघु data;
			अचिन्हित लघु i2c_sta;

			i2c_sta = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_STA);

			जबतक ((i2c_sta & JZ4780_I2C_STA_TFNF) &&
					(i2c->wt_len > 0)) अणु
				i2c_sta = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_STA);
				data = *i2c->wbuf;
				data &= ~JZ4780_I2C_DC_READ;
				अगर ((i2c->wt_len == 1) && (!i2c->stop_hold) &&
						(i2c->cdata->version >= ID_X1000))
					data |= X1000_I2C_DC_STOP;
				jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_DC, data);
				i2c->wbuf++;
				i2c->wt_len--;
			पूर्ण

			अगर (i2c->wt_len == 0) अणु
				अगर ((!i2c->stop_hold) && (i2c->cdata->version <
						ID_X1000)) अणु
					पंचांगp = jz4780_i2c_पढ़ोw(i2c,
							JZ4780_I2C_CTRL);
					पंचांगp &= ~JZ4780_I2C_CTRL_STPHLD;
					jz4780_i2c_ग_लिखोw(i2c,
							JZ4780_I2C_CTRL, पंचांगp);
				पूर्ण

				jz4780_i2c_trans_करोne(i2c);
				जाओ करोne;
			पूर्ण
		पूर्ण
	पूर्ण

करोne:
	spin_unlock(&i2c->lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम jz4780_i2c_txabrt(काष्ठा jz4780_i2c *i2c, पूर्णांक src)
अणु
	dev_dbg(&i2c->adap.dev, "txabrt: 0x%08x, cmd: %d, send: %d, recv: %d\n",
		src, i2c->cmd, i2c->cmd_buf[i2c->cmd], i2c->data_buf[i2c->cmd]);
पूर्ण

अटल अंतरभूत पूर्णांक jz4780_i2c_xfer_पढ़ो(काष्ठा jz4780_i2c *i2c,
				       अचिन्हित अक्षर *buf, पूर्णांक len, पूर्णांक cnt,
				       पूर्णांक idx)
अणु
	पूर्णांक ret = 0;
	दीर्घ समयout;
	पूर्णांक रुको_समय = JZ4780_I2C_TIMEOUT * (len + 5);
	अचिन्हित लघु पंचांगp;
	अचिन्हित दीर्घ flags;

	स_रखो(buf, 0, len);

	spin_lock_irqsave(&i2c->lock, flags);

	i2c->stop_hold = 0;
	i2c->is_ग_लिखो = 0;
	i2c->rbuf = buf;
	i2c->rd_total_len = len;
	i2c->rd_data_xfered = 0;
	i2c->rd_cmd_xfered = 0;

	अगर (len <= i2c->cdata->fअगरosize)
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_RXTL, len - 1);
	अन्यथा
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_RXTL, i2c->cdata->rx_level);

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_TXTL, i2c->cdata->tx_level);

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM,
			  JZ4780_I2C_INTM_MRXFL | JZ4780_I2C_INTM_MTXEMP
			  | JZ4780_I2C_INTM_MTXABT | JZ4780_I2C_INTM_MRXOF);

	अगर (i2c->cdata->version < ID_X1000) अणु
		पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTRL);
		पंचांगp |= JZ4780_I2C_CTRL_STPHLD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);
	पूर्ण

	spin_unlock_irqrestore(&i2c->lock, flags);

	समयout = रुको_क्रम_completion_समयout(&i2c->trans_रुकोq,
					      msecs_to_jअगरfies(रुको_समय));

	अगर (!समयout) अणु
		dev_err(&i2c->adap.dev, "irq read timeout\n");
		dev_dbg(&i2c->adap.dev, "send cmd count:%d  %d\n",
			i2c->cmd, i2c->cmd_buf[i2c->cmd]);
		dev_dbg(&i2c->adap.dev, "receive data count:%d  %d\n",
			i2c->cmd, i2c->data_buf[i2c->cmd]);
		ret = -EIO;
	पूर्ण

	पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_TXABRT);
	अगर (पंचांगp) अणु
		jz4780_i2c_txabrt(i2c, पंचांगp);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक jz4780_i2c_xfer_ग_लिखो(काष्ठा jz4780_i2c *i2c,
					अचिन्हित अक्षर *buf, पूर्णांक len,
					पूर्णांक cnt, पूर्णांक idx)
अणु
	पूर्णांक ret = 0;
	पूर्णांक रुको_समय = JZ4780_I2C_TIMEOUT * (len + 5);
	दीर्घ समयout;
	अचिन्हित लघु पंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&i2c->lock, flags);

	अगर (idx < (cnt - 1))
		i2c->stop_hold = 1;
	अन्यथा
		i2c->stop_hold = 0;

	i2c->is_ग_लिखो = 1;
	i2c->wbuf = buf;
	i2c->wt_len = len;

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_TXTL, i2c->cdata->tx_level);

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM, JZ4780_I2C_INTM_MTXEMP
					| JZ4780_I2C_INTM_MTXABT);

	अगर (i2c->cdata->version < ID_X1000) अणु
		पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTRL);
		पंचांगp |= JZ4780_I2C_CTRL_STPHLD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);
	पूर्ण

	spin_unlock_irqrestore(&i2c->lock, flags);

	समयout = रुको_क्रम_completion_समयout(&i2c->trans_रुकोq,
					      msecs_to_jअगरfies(रुको_समय));
	अगर (समयout && !i2c->stop_hold) अणु
		अचिन्हित लघु i2c_sta;
		पूर्णांक ग_लिखो_in_process;

		समयout = JZ4780_I2C_TIMEOUT * 100;
		क्रम (; समयout > 0; समयout--) अणु
			i2c_sta = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_STA);

			ग_लिखो_in_process = (i2c_sta & JZ4780_I2C_STA_MSTACT) ||
				!(i2c_sta & JZ4780_I2C_STA_TFE);
			अगर (!ग_लिखो_in_process)
				अवरोध;
			udelay(10);
		पूर्ण
	पूर्ण

	अगर (!समयout) अणु
		dev_err(&i2c->adap.dev, "write wait timeout\n");
		ret = -EIO;
	पूर्ण

	पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_TXABRT);
	अगर (पंचांगp) अणु
		jz4780_i2c_txabrt(i2c, पंचांगp);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg,
			   पूर्णांक count)
अणु
	पूर्णांक i = -EIO;
	पूर्णांक ret = 0;
	काष्ठा jz4780_i2c *i2c = adap->algo_data;

	ret = jz4780_i2c_prepare(i2c);
	अगर (ret) अणु
		dev_err(&i2c->adap.dev, "I2C prepare failed\n");
		जाओ out;
	पूर्ण

	अगर (msg->addr != jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_TAR)) अणु
		ret = jz4780_i2c_set_target(i2c, msg->addr);
		अगर (ret)
			जाओ out;
	पूर्ण
	क्रम (i = 0; i < count; i++, msg++) अणु
		अगर (msg->flags & I2C_M_RD)
			ret = jz4780_i2c_xfer_पढ़ो(i2c, msg->buf, msg->len,
						   count, i);
		अन्यथा
			ret = jz4780_i2c_xfer_ग_लिखो(i2c, msg->buf, msg->len,
						    count, i);

		अगर (ret)
			जाओ out;
	पूर्ण

	ret = i;

out:
	jz4780_i2c_cleanup(i2c);
	वापस ret;
पूर्ण

अटल u32 jz4780_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm jz4780_i2c_algorithm = अणु
	.master_xfer	= jz4780_i2c_xfer,
	.functionality	= jz4780_i2c_functionality,
पूर्ण;

अटल स्थिर काष्ठा ingenic_i2c_config jz4780_i2c_config = अणु
	.version = ID_JZ4780,

	.fअगरosize = JZ4780_I2C_FIFO_LEN,
	.tx_level = JZ4780_I2C_FIFO_LEN / 2,
	.rx_level = JZ4780_I2C_FIFO_LEN / 2 - 1,
पूर्ण;

अटल स्थिर काष्ठा ingenic_i2c_config x1000_i2c_config = अणु
	.version = ID_X1000,

	.fअगरosize = X1000_I2C_FIFO_LEN,
	.tx_level = X1000_I2C_FIFO_LEN / 2,
	.rx_level = X1000_I2C_FIFO_LEN / 2 - 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4780_i2c_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4770-i2c", .data = &jz4780_i2c_config पूर्ण,
	अणु .compatible = "ingenic,jz4780-i2c", .data = &jz4780_i2c_config पूर्ण,
	अणु .compatible = "ingenic,x1000-i2c", .data = &x1000_i2c_config पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4780_i2c_of_matches);

अटल पूर्णांक jz4780_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक clk_freq = 0;
	अचिन्हित लघु पंचांगp;
	काष्ठा jz4780_i2c *i2c;

	i2c = devm_kzalloc(&pdev->dev, माप(काष्ठा jz4780_i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->cdata = device_get_match_data(&pdev->dev);
	अगर (!i2c->cdata) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	i2c->adap.owner		= THIS_MODULE;
	i2c->adap.algo		= &jz4780_i2c_algorithm;
	i2c->adap.algo_data	= i2c;
	i2c->adap.retries	= 5;
	i2c->adap.dev.parent	= &pdev->dev;
	i2c->adap.dev.of_node	= pdev->dev.of_node;
	प्र_लिखो(i2c->adap.name, "%s", pdev->name);

	init_completion(&i2c->trans_रुकोq);
	spin_lock_init(&i2c->lock);

	i2c->iomem = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(i2c->iomem))
		वापस PTR_ERR(i2c->iomem);

	platक्रमm_set_drvdata(pdev, i2c);

	i2c->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c->clk))
		वापस PTR_ERR(i2c->clk);

	ret = clk_prepare_enable(i2c->clk);
	अगर (ret)
		वापस ret;

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
				   &clk_freq);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clock-frequency not specified in DT\n");
		जाओ err;
	पूर्ण

	i2c->speed = clk_freq / 1000;
	अगर (i2c->speed == 0) अणु
		ret = -EINVAL;
		dev_err(&pdev->dev, "clock-frequency minimum is 1000\n");
		जाओ err;
	पूर्ण
	jz4780_i2c_set_speed(i2c);

	dev_info(&pdev->dev, "Bus frequency is %d KHz\n", i2c->speed);

	अगर (i2c->cdata->version < ID_X1000) अणु
		पंचांगp = jz4780_i2c_पढ़ोw(i2c, JZ4780_I2C_CTRL);
		पंचांगp &= ~JZ4780_I2C_CTRL_STPHLD;
		jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_CTRL, पंचांगp);
	पूर्ण

	jz4780_i2c_ग_लिखोw(i2c, JZ4780_I2C_INTM, 0x0);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ err;
	i2c->irq = ret;
	ret = devm_request_irq(&pdev->dev, i2c->irq, jz4780_i2c_irq, 0,
			       dev_name(&pdev->dev), i2c);
	अगर (ret)
		जाओ err;

	ret = i2c_add_adapter(&i2c->adap);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	clk_disable_unprepare(i2c->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक jz4780_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा jz4780_i2c *i2c = platक्रमm_get_drvdata(pdev);

	clk_disable_unprepare(i2c->clk);
	i2c_del_adapter(&i2c->adap);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver jz4780_i2c_driver = अणु
	.probe		= jz4780_i2c_probe,
	.हटाओ		= jz4780_i2c_हटाओ,
	.driver		= अणु
		.name	= "jz4780-i2c",
		.of_match_table = jz4780_i2c_of_matches,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4780_i2c_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ztyan<ztyan@ingenic.cn>");
MODULE_DESCRIPTION("i2c driver for JZ4780 SoCs");
