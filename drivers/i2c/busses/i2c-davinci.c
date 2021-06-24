<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 *
 * Updated by Vinod & Sudhakar Feb 2005
 *
 * ----------------------------------------------------------------------------
 *
 * ----------------------------------------------------------------------------
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/i2c-davinci.h>
#समावेश <linux/pm_runसमय.स>

/* ----- global defines ----------------------------------------------- */

#घोषणा DAVINCI_I2C_TIMEOUT	(1*HZ)
#घोषणा DAVINCI_I2C_MAX_TRIES	2
#घोषणा DAVINCI_I2C_OWN_ADDRESS	0x08
#घोषणा I2C_DAVINCI_INTR_ALL    (DAVINCI_I2C_IMR_SCD | \
				 DAVINCI_I2C_IMR_ARDY | \
				 DAVINCI_I2C_IMR_NACK | \
				 DAVINCI_I2C_IMR_AL)

#घोषणा DAVINCI_I2C_OAR_REG	0x00
#घोषणा DAVINCI_I2C_IMR_REG	0x04
#घोषणा DAVINCI_I2C_STR_REG	0x08
#घोषणा DAVINCI_I2C_CLKL_REG	0x0c
#घोषणा DAVINCI_I2C_CLKH_REG	0x10
#घोषणा DAVINCI_I2C_CNT_REG	0x14
#घोषणा DAVINCI_I2C_DRR_REG	0x18
#घोषणा DAVINCI_I2C_SAR_REG	0x1c
#घोषणा DAVINCI_I2C_DXR_REG	0x20
#घोषणा DAVINCI_I2C_MDR_REG	0x24
#घोषणा DAVINCI_I2C_IVR_REG	0x28
#घोषणा DAVINCI_I2C_EMDR_REG	0x2c
#घोषणा DAVINCI_I2C_PSC_REG	0x30
#घोषणा DAVINCI_I2C_FUNC_REG	0x48
#घोषणा DAVINCI_I2C_सूची_REG	0x4c
#घोषणा DAVINCI_I2C_DIN_REG	0x50
#घोषणा DAVINCI_I2C_DOUT_REG	0x54
#घोषणा DAVINCI_I2C_DSET_REG	0x58
#घोषणा DAVINCI_I2C_DCLR_REG	0x5c

#घोषणा DAVINCI_I2C_IVR_AAS	0x07
#घोषणा DAVINCI_I2C_IVR_SCD	0x06
#घोषणा DAVINCI_I2C_IVR_XRDY	0x05
#घोषणा DAVINCI_I2C_IVR_RDR	0x04
#घोषणा DAVINCI_I2C_IVR_ARDY	0x03
#घोषणा DAVINCI_I2C_IVR_NACK	0x02
#घोषणा DAVINCI_I2C_IVR_AL	0x01

#घोषणा DAVINCI_I2C_STR_BB	BIT(12)
#घोषणा DAVINCI_I2C_STR_RSFULL	BIT(11)
#घोषणा DAVINCI_I2C_STR_SCD	BIT(5)
#घोषणा DAVINCI_I2C_STR_ARDY	BIT(2)
#घोषणा DAVINCI_I2C_STR_NACK	BIT(1)
#घोषणा DAVINCI_I2C_STR_AL	BIT(0)

#घोषणा DAVINCI_I2C_MDR_NACK	BIT(15)
#घोषणा DAVINCI_I2C_MDR_STT	BIT(13)
#घोषणा DAVINCI_I2C_MDR_STP	BIT(11)
#घोषणा DAVINCI_I2C_MDR_MST	BIT(10)
#घोषणा DAVINCI_I2C_MDR_TRX	BIT(9)
#घोषणा DAVINCI_I2C_MDR_XA	BIT(8)
#घोषणा DAVINCI_I2C_MDR_RM	BIT(7)
#घोषणा DAVINCI_I2C_MDR_IRS	BIT(5)

#घोषणा DAVINCI_I2C_IMR_AAS	BIT(6)
#घोषणा DAVINCI_I2C_IMR_SCD	BIT(5)
#घोषणा DAVINCI_I2C_IMR_XRDY	BIT(4)
#घोषणा DAVINCI_I2C_IMR_RRDY	BIT(3)
#घोषणा DAVINCI_I2C_IMR_ARDY	BIT(2)
#घोषणा DAVINCI_I2C_IMR_NACK	BIT(1)
#घोषणा DAVINCI_I2C_IMR_AL	BIT(0)

/* set SDA and SCL as GPIO */
#घोषणा DAVINCI_I2C_FUNC_PFUNC0	BIT(0)

/* set SCL as output when used as GPIO*/
#घोषणा DAVINCI_I2C_सूची_Pसूची0	BIT(0)
/* set SDA as output when used as GPIO*/
#घोषणा DAVINCI_I2C_सूची_Pसूची1	BIT(1)

/* पढ़ो SCL GPIO level */
#घोषणा DAVINCI_I2C_DIN_PDIN0 BIT(0)
/* पढ़ो SDA GPIO level */
#घोषणा DAVINCI_I2C_DIN_PDIN1 BIT(1)

/*set the SCL GPIO high */
#घोषणा DAVINCI_I2C_DSET_PDSET0	BIT(0)
/*set the SDA GPIO high */
#घोषणा DAVINCI_I2C_DSET_PDSET1	BIT(1)

/* set the SCL GPIO low */
#घोषणा DAVINCI_I2C_DCLR_PDCLR0	BIT(0)
/* set the SDA GPIO low */
#घोषणा DAVINCI_I2C_DCLR_PDCLR1	BIT(1)

/* समयout क्रम pm runसमय स्वतःsuspend */
#घोषणा DAVINCI_I2C_PM_TIMEOUT	1000	/* ms */

काष्ठा davinci_i2c_dev अणु
	काष्ठा device           *dev;
	व्योम __iomem		*base;
	काष्ठा completion	cmd_complete;
	काष्ठा clk              *clk;
	पूर्णांक			cmd_err;
	u8			*buf;
	माप_प्रकार			buf_len;
	पूर्णांक			irq;
	पूर्णांक			stop;
	u8			terminate;
	काष्ठा i2c_adapter	adapter;
#अगर_घोषित CONFIG_CPU_FREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
	काष्ठा davinci_i2c_platक्रमm_data *pdata;
पूर्ण;

/* शेष platक्रमm data to use अगर not supplied in the platक्रमm_device */
अटल काष्ठा davinci_i2c_platक्रमm_data davinci_i2c_platक्रमm_data_शेष = अणु
	.bus_freq	= 100,
	.bus_delay	= 0,
पूर्ण;

अटल अंतरभूत व्योम davinci_i2c_ग_लिखो_reg(काष्ठा davinci_i2c_dev *i2c_dev,
					 पूर्णांक reg, u16 val)
अणु
	ग_लिखोw_relaxed(val, i2c_dev->base + reg);
पूर्ण

अटल अंतरभूत u16 davinci_i2c_पढ़ो_reg(काष्ठा davinci_i2c_dev *i2c_dev, पूर्णांक reg)
अणु
	वापस पढ़ोw_relaxed(i2c_dev->base + reg);
पूर्ण

अटल अंतरभूत व्योम davinci_i2c_reset_ctrl(काष्ठा davinci_i2c_dev *i2c_dev,
								पूर्णांक val)
अणु
	u16 w;

	w = davinci_i2c_पढ़ो_reg(i2c_dev, DAVINCI_I2C_MDR_REG);
	अगर (!val)	/* put I2C पूर्णांकo reset */
		w &= ~DAVINCI_I2C_MDR_IRS;
	अन्यथा		/* take I2C out of reset */
		w |= DAVINCI_I2C_MDR_IRS;

	davinci_i2c_ग_लिखो_reg(i2c_dev, DAVINCI_I2C_MDR_REG, w);
पूर्ण

अटल व्योम i2c_davinci_calc_clk_भागiders(काष्ठा davinci_i2c_dev *dev)
अणु
	काष्ठा davinci_i2c_platक्रमm_data *pdata = dev->pdata;
	u16 psc;
	u32 clk;
	u32 d;
	u32 clkh;
	u32 clkl;
	u32 input_घड़ी = clk_get_rate(dev->clk);
	काष्ठा device_node *of_node = dev->dev->of_node;

	/* NOTE: I2C Clock भागider programming info
	 * As per I2C specs the following क्रमmulas provide prescaler
	 * and low/high भागider values
	 * input clk --> PSC Div -----------> ICCL/H Div --> output घड़ी
	 *                       module clk
	 *
	 * output clk = module clk / (PSC + 1) [ (ICCL + d) + (ICCH + d) ]
	 *
	 * Thus,
	 * (ICCL + ICCH) = clk = (input clk / ((psc +1) * output clk)) - 2d;
	 *
	 * where अगर PSC == 0, d = 7,
	 *       अगर PSC == 1, d = 6
	 *       अगर PSC > 1 , d = 5
	 *
	 * Note:
	 * d is always 6 on Keystone I2C controller
	 */

	/*
	 * Both Davinci and current Keystone User Guides recommend a value
	 * between 7MHz and 12MHz. In reality 7MHz module घड़ी करोesn't
	 * always produce enough margin between SDA and SCL transitions.
	 * Measurements show that the higher the module घड़ी is, the
	 * bigger is the margin, providing more reliable communication.
	 * So we better target क्रम 12MHz.
	 */
	psc = (input_घड़ी / 12000000) - 1;
	अगर ((input_घड़ी / (psc + 1)) > 12000000)
		psc++;	/* better to run under spec than over */
	d = (psc >= 2) ? 5 : 7 - psc;

	अगर (of_node && of_device_is_compatible(of_node, "ti,keystone-i2c"))
		d = 6;

	clk = ((input_घड़ी / (psc + 1)) / (pdata->bus_freq * 1000));
	/* Aव्योम driving the bus too fast because of rounding errors above */
	अगर (input_घड़ी / (psc + 1) / clk > pdata->bus_freq * 1000)
		clk++;
	/*
	 * According to I2C-BUS Spec 2.1, in FAST-MODE LOW period should be at
	 * least 1.3uS, which is not the हाल with 50% duty cycle. Driving HIGH
	 * to LOW ratio as 1 to 2 is more safe.
	 */
	अगर (pdata->bus_freq > 100)
		clkl = (clk << 1) / 3;
	अन्यथा
		clkl = (clk >> 1);
	/*
	 * It's not always possible to have 1 to 2 ratio when d=7, so fall back
	 * to minimal possible clkh in this हाल.
	 *
	 * Note:
	 * CLKH is not allowed to be 0, in this हाल I2C घड़ी is not generated
	 * at all
	 */
	अगर (clk > clkl + d) अणु
		clkh = clk - clkl - d;
		clkl -= d;
	पूर्ण अन्यथा अणु
		clkh = 1;
		clkl = clk - (d << 1);
	पूर्ण

	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_PSC_REG, psc);
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_CLKH_REG, clkh);
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_CLKL_REG, clkl);

	dev_dbg(dev->dev, "input_clock = %d, CLK = %d\n", input_घड़ी, clk);
पूर्ण

/*
 * This function configures I2C and brings I2C out of reset.
 * This function is called during I2C init function. This function
 * also माला_लो called अगर I2C encounters any errors.
 */
अटल पूर्णांक i2c_davinci_init(काष्ठा davinci_i2c_dev *dev)
अणु
	काष्ठा davinci_i2c_platक्रमm_data *pdata = dev->pdata;

	/* put I2C पूर्णांकo reset */
	davinci_i2c_reset_ctrl(dev, 0);

	/* compute घड़ी भागiders */
	i2c_davinci_calc_clk_भागiders(dev);

	/* Respond at reserved "SMBus Host" slave address" (and zero);
	 * we seem to have no option to not respond...
	 */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_OAR_REG, DAVINCI_I2C_OWN_ADDRESS);

	dev_dbg(dev->dev, "PSC  = %d\n",
		davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_PSC_REG));
	dev_dbg(dev->dev, "CLKL = %d\n",
		davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_CLKL_REG));
	dev_dbg(dev->dev, "CLKH = %d\n",
		davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_CLKH_REG));
	dev_dbg(dev->dev, "bus_freq = %dkHz, bus_delay = %d\n",
		pdata->bus_freq, pdata->bus_delay);


	/* Take the I2C module out of reset: */
	davinci_i2c_reset_ctrl(dev, 1);

	/* Enable पूर्णांकerrupts */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_IMR_REG, I2C_DAVINCI_INTR_ALL);

	वापस 0;
पूर्ण

/*
 * This routine करोes i2c bus recovery by using i2c_generic_scl_recovery
 * which is provided by I2C Bus recovery infraकाष्ठाure.
 */
अटल व्योम davinci_i2c_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	/* Disable पूर्णांकerrupts */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_IMR_REG, 0);

	/* put I2C पूर्णांकo reset */
	davinci_i2c_reset_ctrl(dev, 0);
पूर्ण

अटल व्योम davinci_i2c_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	i2c_davinci_init(dev);
पूर्ण

अटल काष्ठा i2c_bus_recovery_info davinci_i2c_gpio_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.prepare_recovery = davinci_i2c_prepare_recovery,
	.unprepare_recovery = davinci_i2c_unprepare_recovery,
पूर्ण;

अटल व्योम davinci_i2c_set_scl(काष्ठा i2c_adapter *adap, पूर्णांक val)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	अगर (val)
		davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_DSET_REG,
				      DAVINCI_I2C_DSET_PDSET0);
	अन्यथा
		davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_DCLR_REG,
				      DAVINCI_I2C_DCLR_PDCLR0);
पूर्ण

अटल पूर्णांक davinci_i2c_get_scl(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक val;

	/* पढ़ो the state of SCL */
	val = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_DIN_REG);
	वापस val & DAVINCI_I2C_DIN_PDIN0;
पूर्ण

अटल पूर्णांक davinci_i2c_get_sda(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक val;

	/* पढ़ो the state of SDA */
	val = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_DIN_REG);
	वापस val & DAVINCI_I2C_DIN_PDIN1;
पूर्ण

अटल व्योम davinci_i2c_scl_prepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	davinci_i2c_prepare_recovery(adap);

	/* SCL output, SDA input */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_सूची_REG, DAVINCI_I2C_सूची_Pसूची0);

	/* change to GPIO mode */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_FUNC_REG,
			      DAVINCI_I2C_FUNC_PFUNC0);
पूर्ण

अटल व्योम davinci_i2c_scl_unprepare_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);

	/* change back to I2C mode */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_FUNC_REG, 0);

	davinci_i2c_unprepare_recovery(adap);
पूर्ण

अटल काष्ठा i2c_bus_recovery_info davinci_i2c_scl_recovery_info = अणु
	.recover_bus = i2c_generic_scl_recovery,
	.set_scl = davinci_i2c_set_scl,
	.get_scl = davinci_i2c_get_scl,
	.get_sda = davinci_i2c_get_sda,
	.prepare_recovery = davinci_i2c_scl_prepare_recovery,
	.unprepare_recovery = davinci_i2c_scl_unprepare_recovery,
पूर्ण;

/*
 * Waiting क्रम bus not busy
 */
अटल पूर्णांक i2c_davinci_रुको_bus_not_busy(काष्ठा davinci_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + dev->adapter.समयout;

	करो अणु
		अगर (!(davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_STR_REG) & DAVINCI_I2C_STR_BB))
			वापस 0;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_beक्रमe_eq(jअगरfies, समयout));

	dev_warn(dev->dev, "timeout waiting for bus ready\n");
	i2c_recover_bus(&dev->adapter);

	/*
	 * अगर bus is still "busy" here, it's most probably a HW problem like
	 * लघु-circuit
	 */
	अगर (davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_STR_REG) & DAVINCI_I2C_STR_BB)
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * Low level master पढ़ो/ग_लिखो transaction. This function is called
 * from i2c_davinci_xfer.
 */
अटल पूर्णांक
i2c_davinci_xfer_msg(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msg, पूर्णांक stop)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	काष्ठा davinci_i2c_platक्रमm_data *pdata = dev->pdata;
	u32 flag;
	u16 w;
	अचिन्हित दीर्घ समय_left;

	अगर (msg->addr == DAVINCI_I2C_OWN_ADDRESS) अणु
		dev_warn(dev->dev, "transfer to own address aborted\n");
		वापस -EADDRNOTAVAIL;
	पूर्ण

	/* Introduce a delay, required क्रम some boards (e.g Davinci EVM) */
	अगर (pdata->bus_delay)
		udelay(pdata->bus_delay);

	/* set the slave address */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_SAR_REG, msg->addr);

	dev->buf = msg->buf;
	dev->buf_len = msg->len;
	dev->stop = stop;

	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_CNT_REG, dev->buf_len);

	reinit_completion(&dev->cmd_complete);
	dev->cmd_err = 0;

	/* Take I2C out of reset and configure it as master */
	flag = DAVINCI_I2C_MDR_IRS | DAVINCI_I2C_MDR_MST;

	/* अगर the slave address is ten bit address, enable XA bit */
	अगर (msg->flags & I2C_M_TEN)
		flag |= DAVINCI_I2C_MDR_XA;
	अगर (!(msg->flags & I2C_M_RD))
		flag |= DAVINCI_I2C_MDR_TRX;
	अगर (msg->len == 0)
		flag |= DAVINCI_I2C_MDR_RM;

	/* Enable receive or transmit पूर्णांकerrupts */
	w = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_IMR_REG);
	अगर (msg->flags & I2C_M_RD)
		w |= DAVINCI_I2C_IMR_RRDY;
	अन्यथा
		w |= DAVINCI_I2C_IMR_XRDY;
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_IMR_REG, w);

	dev->terminate = 0;

	/*
	 * Write mode रेजिस्टर first as needed क्रम correct behaviour
	 * on OMAP-L138, but करोn't set STT yet to aव्योम a race with XRDY
	 * occurring beक्रमe we have loaded DXR
	 */
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, flag);

	/*
	 * First byte should be set here, not after पूर्णांकerrupt,
	 * because transmit-data-पढ़ोy पूर्णांकerrupt can come beक्रमe
	 * NACK-पूर्णांकerrupt during sending of previous message and
	 * ICDXR may have wrong data
	 * It also saves us one पूर्णांकerrupt, slightly faster
	 */
	अगर ((!(msg->flags & I2C_M_RD)) && dev->buf_len) अणु
		davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_DXR_REG, *dev->buf++);
		dev->buf_len--;
	पूर्ण

	/* Set STT to begin transmit now DXR is loaded */
	flag |= DAVINCI_I2C_MDR_STT;
	अगर (stop && msg->len != 0)
		flag |= DAVINCI_I2C_MDR_STP;
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, flag);

	समय_left = रुको_क्रम_completion_समयout(&dev->cmd_complete,
						dev->adapter.समयout);
	अगर (!समय_left) अणु
		dev_err(dev->dev, "controller timed out\n");
		i2c_recover_bus(adap);
		dev->buf_len = 0;
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (dev->buf_len) अणु
		/* This should be 0 अगर all bytes were transferred
		 * or dev->cmd_err denotes an error.
		 */
		dev_err(dev->dev, "abnormal termination buf_len=%zu\n",
			dev->buf_len);
		dev->terminate = 1;
		wmb();
		dev->buf_len = 0;
		वापस -EREMOTEIO;
	पूर्ण

	/* no error */
	अगर (likely(!dev->cmd_err))
		वापस msg->len;

	/* We have an error */
	अगर (dev->cmd_err & DAVINCI_I2C_STR_AL) अणु
		i2c_davinci_init(dev);
		वापस -EIO;
	पूर्ण

	अगर (dev->cmd_err & DAVINCI_I2C_STR_NACK) अणु
		अगर (msg->flags & I2C_M_IGNORE_NAK)
			वापस msg->len;
		w = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_MDR_REG);
		w |= DAVINCI_I2C_MDR_STP;
		davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, w);
		वापस -EREMOTEIO;
	पूर्ण
	वापस -EIO;
पूर्ण

/*
 * Prepare controller क्रम a transaction and call i2c_davinci_xfer_msg
 */
अटल पूर्णांक
i2c_davinci_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा davinci_i2c_dev *dev = i2c_get_adapdata(adap);
	पूर्णांक i;
	पूर्णांक ret;

	dev_dbg(dev->dev, "%s: msgs: %d\n", __func__, num);

	ret = pm_runसमय_get_sync(dev->dev);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "Failed to runtime_get device: %d\n", ret);
		pm_runसमय_put_noidle(dev->dev);
		वापस ret;
	पूर्ण

	ret = i2c_davinci_रुको_bus_not_busy(dev);
	अगर (ret < 0) अणु
		dev_warn(dev->dev, "timeout waiting for bus ready\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		ret = i2c_davinci_xfer_msg(adap, &msgs[i], (i == (num - 1)));
		dev_dbg(dev->dev, "%s [%d/%d] ret: %d\n", __func__, i + 1, num,
			ret);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = num;

out:
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस ret;
पूर्ण

अटल u32 i2c_davinci_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल व्योम terminate_पढ़ो(काष्ठा davinci_i2c_dev *dev)
अणु
	u16 w = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_MDR_REG);
	w |= DAVINCI_I2C_MDR_NACK;
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, w);

	/* Throw away data */
	davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_DRR_REG);
	अगर (!dev->terminate)
		dev_err(dev->dev, "RDR IRQ while no data requested\n");
पूर्ण
अटल व्योम terminate_ग_लिखो(काष्ठा davinci_i2c_dev *dev)
अणु
	u16 w = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_MDR_REG);
	w |= DAVINCI_I2C_MDR_RM | DAVINCI_I2C_MDR_STP;
	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, w);

	अगर (!dev->terminate)
		dev_dbg(dev->dev, "TDR IRQ while no data to send\n");
पूर्ण

/*
 * Interrupt service routine. This माला_लो called whenever an I2C पूर्णांकerrupt
 * occurs.
 */
अटल irqवापस_t i2c_davinci_isr(पूर्णांक this_irq, व्योम *dev_id)
अणु
	काष्ठा davinci_i2c_dev *dev = dev_id;
	u32 stat;
	पूर्णांक count = 0;
	u16 w;

	अगर (pm_runसमय_suspended(dev->dev))
		वापस IRQ_NONE;

	जबतक ((stat = davinci_i2c_पढ़ो_reg(dev, DAVINCI_I2C_IVR_REG))) अणु
		dev_dbg(dev->dev, "%s: stat=0x%x\n", __func__, stat);
		अगर (count++ == 100) अणु
			dev_warn(dev->dev, "Too much work in one IRQ\n");
			अवरोध;
		पूर्ण

		चयन (stat) अणु
		हाल DAVINCI_I2C_IVR_AL:
			/* Arbitration lost, must retry */
			dev->cmd_err |= DAVINCI_I2C_STR_AL;
			dev->buf_len = 0;
			complete(&dev->cmd_complete);
			अवरोध;

		हाल DAVINCI_I2C_IVR_NACK:
			dev->cmd_err |= DAVINCI_I2C_STR_NACK;
			dev->buf_len = 0;
			complete(&dev->cmd_complete);
			अवरोध;

		हाल DAVINCI_I2C_IVR_ARDY:
			davinci_i2c_ग_लिखो_reg(dev,
				DAVINCI_I2C_STR_REG, DAVINCI_I2C_STR_ARDY);
			अगर (((dev->buf_len == 0) && (dev->stop != 0)) ||
			    (dev->cmd_err & DAVINCI_I2C_STR_NACK)) अणु
				w = davinci_i2c_पढ़ो_reg(dev,
							 DAVINCI_I2C_MDR_REG);
				w |= DAVINCI_I2C_MDR_STP;
				davinci_i2c_ग_लिखो_reg(dev,
						      DAVINCI_I2C_MDR_REG, w);
			पूर्ण
			complete(&dev->cmd_complete);
			अवरोध;

		हाल DAVINCI_I2C_IVR_RDR:
			अगर (dev->buf_len) अणु
				*dev->buf++ =
				    davinci_i2c_पढ़ो_reg(dev,
							 DAVINCI_I2C_DRR_REG);
				dev->buf_len--;
				अगर (dev->buf_len)
					जारी;

				davinci_i2c_ग_लिखो_reg(dev,
					DAVINCI_I2C_STR_REG,
					DAVINCI_I2C_IMR_RRDY);
			पूर्ण अन्यथा अणु
				/* संकेत can terminate transfer */
				terminate_पढ़ो(dev);
			पूर्ण
			अवरोध;

		हाल DAVINCI_I2C_IVR_XRDY:
			अगर (dev->buf_len) अणु
				davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_DXR_REG,
						      *dev->buf++);
				dev->buf_len--;
				अगर (dev->buf_len)
					जारी;

				w = davinci_i2c_पढ़ो_reg(dev,
							 DAVINCI_I2C_IMR_REG);
				w &= ~DAVINCI_I2C_IMR_XRDY;
				davinci_i2c_ग_लिखो_reg(dev,
						      DAVINCI_I2C_IMR_REG,
						      w);
			पूर्ण अन्यथा अणु
				/* संकेत can terminate transfer */
				terminate_ग_लिखो(dev);
			पूर्ण
			अवरोध;

		हाल DAVINCI_I2C_IVR_SCD:
			davinci_i2c_ग_लिखो_reg(dev,
				DAVINCI_I2C_STR_REG, DAVINCI_I2C_STR_SCD);
			complete(&dev->cmd_complete);
			अवरोध;

		हाल DAVINCI_I2C_IVR_AAS:
			dev_dbg(dev->dev, "Address as slave interrupt\n");
			अवरोध;

		शेष:
			dev_warn(dev->dev, "Unrecognized irq stat %d\n", stat);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस count ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_CPU_FREQ
अटल पूर्णांक i2c_davinci_cpufreq_transition(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा davinci_i2c_dev *dev;

	dev = container_of(nb, काष्ठा davinci_i2c_dev, freq_transition);

	i2c_lock_bus(&dev->adapter, I2C_LOCK_ROOT_ADAPTER);
	अगर (val == CPUFREQ_PRECHANGE) अणु
		davinci_i2c_reset_ctrl(dev, 0);
	पूर्ण अन्यथा अगर (val == CPUFREQ_POSTCHANGE) अणु
		i2c_davinci_calc_clk_भागiders(dev);
		davinci_i2c_reset_ctrl(dev, 1);
	पूर्ण
	i2c_unlock_bus(&dev->adapter, I2C_LOCK_ROOT_ADAPTER);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक i2c_davinci_cpufreq_रेजिस्टर(काष्ठा davinci_i2c_dev *dev)
अणु
	dev->freq_transition.notअगरier_call = i2c_davinci_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&dev->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम i2c_davinci_cpufreq_deरेजिस्टर(काष्ठा davinci_i2c_dev *dev)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&dev->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक i2c_davinci_cpufreq_रेजिस्टर(काष्ठा davinci_i2c_dev *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम i2c_davinci_cpufreq_deरेजिस्टर(काष्ठा davinci_i2c_dev *dev)
अणु
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_algorithm i2c_davinci_algo = अणु
	.master_xfer	= i2c_davinci_xfer,
	.functionality	= i2c_davinci_func,
पूर्ण;

अटल स्थिर काष्ठा of_device_id davinci_i2c_of_match[] = अणु
	अणु.compatible = "ti,davinci-i2c", पूर्ण,
	अणु.compatible = "ti,keystone-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, davinci_i2c_of_match);

अटल पूर्णांक davinci_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_i2c_dev *dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा i2c_bus_recovery_info *rinfo;
	पूर्णांक r, irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		अगर (!irq)
			irq = -ENXIO;
		अगर (irq != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"can't get irq resource ret=%d\n", irq);
		वापस irq;
	पूर्ण

	dev = devm_kzalloc(&pdev->dev, माप(काष्ठा davinci_i2c_dev),
			GFP_KERNEL);
	अगर (!dev) अणु
		dev_err(&pdev->dev, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	init_completion(&dev->cmd_complete);

	dev->dev = &pdev->dev;
	dev->irq = irq;
	dev->pdata = dev_get_platdata(&pdev->dev);
	platक्रमm_set_drvdata(pdev, dev);

	अगर (!dev->pdata && pdev->dev.of_node) अणु
		u32 prop;

		dev->pdata = devm_kzalloc(&pdev->dev,
			माप(काष्ठा davinci_i2c_platक्रमm_data), GFP_KERNEL);
		अगर (!dev->pdata)
			वापस -ENOMEM;

		स_नकल(dev->pdata, &davinci_i2c_platक्रमm_data_शेष,
			माप(काष्ठा davinci_i2c_platक्रमm_data));
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "clock-frequency",
			&prop))
			dev->pdata->bus_freq = prop / 1000;

		dev->pdata->has_pfunc =
			of_property_पढ़ो_bool(pdev->dev.of_node,
					      "ti,has-pfunc");
	पूर्ण अन्यथा अगर (!dev->pdata) अणु
		dev->pdata = &davinci_i2c_platक्रमm_data_शेष;
	पूर्ण

	dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dev->clk))
		वापस PTR_ERR(dev->clk);

	dev->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->base)) अणु
		वापस PTR_ERR(dev->base);
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev->dev,
					 DAVINCI_I2C_PM_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(dev->dev);

	pm_runसमय_enable(dev->dev);

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		dev_err(dev->dev, "failed to runtime_get device: %d\n", r);
		pm_runसमय_put_noidle(dev->dev);
		वापस r;
	पूर्ण

	i2c_davinci_init(dev);

	r = devm_request_irq(&pdev->dev, dev->irq, i2c_davinci_isr, 0,
			pdev->name, dev);
	अगर (r) अणु
		dev_err(&pdev->dev, "failure requesting irq %i\n", dev->irq);
		जाओ err_unuse_घड़ीs;
	पूर्ण

	r = i2c_davinci_cpufreq_रेजिस्टर(dev);
	अगर (r) अणु
		dev_err(&pdev->dev, "failed to register cpufreq\n");
		जाओ err_unuse_घड़ीs;
	पूर्ण

	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_DEPRECATED;
	strlcpy(adap->name, "DaVinci I2C adapter", माप(adap->name));
	adap->algo = &i2c_davinci_algo;
	adap->dev.parent = &pdev->dev;
	adap->समयout = DAVINCI_I2C_TIMEOUT;
	adap->dev.of_node = pdev->dev.of_node;

	अगर (dev->pdata->has_pfunc)
		adap->bus_recovery_info = &davinci_i2c_scl_recovery_info;
	अन्यथा अगर (dev->pdata->gpio_recovery) अणु
		rinfo =  &davinci_i2c_gpio_recovery_info;
		adap->bus_recovery_info = rinfo;
		rinfo->scl_gpiod = devm_gpiod_get(&pdev->dev, "scl",
						  GPIOD_OUT_HIGH_OPEN_DRAIN);
		अगर (IS_ERR(rinfo->scl_gpiod)) अणु
			r = PTR_ERR(rinfo->scl_gpiod);
			जाओ err_unuse_घड़ीs;
		पूर्ण
		rinfo->sda_gpiod = devm_gpiod_get(&pdev->dev, "sda", GPIOD_IN);
		अगर (IS_ERR(rinfo->sda_gpiod)) अणु
			r = PTR_ERR(rinfo->sda_gpiod);
			जाओ err_unuse_घड़ीs;
		पूर्ण
	पूर्ण

	adap->nr = pdev->id;
	r = i2c_add_numbered_adapter(adap);
	अगर (r)
		जाओ err_unuse_घड़ीs;

	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस 0;

err_unuse_घड़ीs:
	pm_runसमय_करोnt_use_स्वतःsuspend(dev->dev);
	pm_runसमय_put_sync(dev->dev);
	pm_runसमय_disable(dev->dev);

	वापस r;
पूर्ण

अटल पूर्णांक davinci_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा davinci_i2c_dev *dev = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	i2c_davinci_cpufreq_deरेजिस्टर(dev);

	i2c_del_adapter(&dev->adapter);

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		वापस ret;
	पूर्ण

	davinci_i2c_ग_लिखो_reg(dev, DAVINCI_I2C_MDR_REG, 0);

	pm_runसमय_करोnt_use_स्वतःsuspend(dev->dev);
	pm_runसमय_put_sync(dev->dev);
	pm_runसमय_disable(dev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक davinci_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा davinci_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	/* put I2C पूर्णांकo reset */
	davinci_i2c_reset_ctrl(i2c_dev, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक davinci_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा davinci_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	/* take I2C out of reset */
	davinci_i2c_reset_ctrl(i2c_dev, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops davinci_i2c_pm = अणु
	.suspend        = davinci_i2c_suspend,
	.resume         = davinci_i2c_resume,
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				      pm_runसमय_क्रमce_resume)
पूर्ण;

#घोषणा davinci_i2c_pm_ops (&davinci_i2c_pm)
#अन्यथा
#घोषणा davinci_i2c_pm_ops शून्य
#पूर्ण_अगर

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:i2c_davinci");

अटल काष्ठा platक्रमm_driver davinci_i2c_driver = अणु
	.probe		= davinci_i2c_probe,
	.हटाओ		= davinci_i2c_हटाओ,
	.driver		= अणु
		.name	= "i2c_davinci",
		.pm	= davinci_i2c_pm_ops,
		.of_match_table = davinci_i2c_of_match,
	पूर्ण,
पूर्ण;

/* I2C may be needed to bring up other drivers */
अटल पूर्णांक __init davinci_i2c_init_driver(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&davinci_i2c_driver);
पूर्ण
subsys_initcall(davinci_i2c_init_driver);

अटल व्योम __निकास davinci_i2c_निकास_driver(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&davinci_i2c_driver);
पूर्ण
module_निकास(davinci_i2c_निकास_driver);

MODULE_AUTHOR("Texas Instruments India");
MODULE_DESCRIPTION("TI DaVinci I2C bus adapter");
MODULE_LICENSE("GPL");
