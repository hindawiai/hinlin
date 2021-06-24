<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2012-2016, The Linux Foundation. All rights reserved.
// Copyright (c) 2017-20 Linaro Limited.

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा CCI_HW_VERSION				0x0
#घोषणा CCI_RESET_CMD				0x004
#घोषणा CCI_RESET_CMD_MASK			0x0f73f3f7
#घोषणा CCI_RESET_CMD_M0_MASK			0x000003f1
#घोषणा CCI_RESET_CMD_M1_MASK			0x0003f001
#घोषणा CCI_QUEUE_START				0x008
#घोषणा CCI_HALT_REQ				0x034
#घोषणा CCI_HALT_REQ_I2C_M0_Q0Q1		BIT(0)
#घोषणा CCI_HALT_REQ_I2C_M1_Q0Q1		BIT(1)

#घोषणा CCI_I2C_Mm_SCL_CTL(m)			(0x100 + 0x100 * (m))
#घोषणा CCI_I2C_Mm_SDA_CTL_0(m)			(0x104 + 0x100 * (m))
#घोषणा CCI_I2C_Mm_SDA_CTL_1(m)			(0x108 + 0x100 * (m))
#घोषणा CCI_I2C_Mm_SDA_CTL_2(m)			(0x10c + 0x100 * (m))
#घोषणा CCI_I2C_Mm_MISC_CTL(m)			(0x110 + 0x100 * (m))

#घोषणा CCI_I2C_Mm_READ_DATA(m)			(0x118 + 0x100 * (m))
#घोषणा CCI_I2C_Mm_READ_BUF_LEVEL(m)		(0x11c + 0x100 * (m))
#घोषणा CCI_I2C_Mm_Qn_EXEC_WORD_CNT(m, n)	(0x300 + 0x200 * (m) + 0x100 * (n))
#घोषणा CCI_I2C_Mm_Qn_CUR_WORD_CNT(m, n)	(0x304 + 0x200 * (m) + 0x100 * (n))
#घोषणा CCI_I2C_Mm_Qn_CUR_CMD(m, n)		(0x308 + 0x200 * (m) + 0x100 * (n))
#घोषणा CCI_I2C_Mm_Qn_REPORT_STATUS(m, n)	(0x30c + 0x200 * (m) + 0x100 * (n))
#घोषणा CCI_I2C_Mm_Qn_LOAD_DATA(m, n)		(0x310 + 0x200 * (m) + 0x100 * (n))

#घोषणा CCI_IRQ_GLOBAL_CLEAR_CMD		0xc00
#घोषणा CCI_IRQ_MASK_0				0xc04
#घोषणा CCI_IRQ_MASK_0_I2C_M0_RD_DONE		BIT(0)
#घोषणा CCI_IRQ_MASK_0_I2C_M0_Q0_REPORT		BIT(4)
#घोषणा CCI_IRQ_MASK_0_I2C_M0_Q1_REPORT		BIT(8)
#घोषणा CCI_IRQ_MASK_0_I2C_M1_RD_DONE		BIT(12)
#घोषणा CCI_IRQ_MASK_0_I2C_M1_Q0_REPORT		BIT(16)
#घोषणा CCI_IRQ_MASK_0_I2C_M1_Q1_REPORT		BIT(20)
#घोषणा CCI_IRQ_MASK_0_RST_DONE_ACK		BIT(24)
#घोषणा CCI_IRQ_MASK_0_I2C_M0_Q0Q1_HALT_ACK	BIT(25)
#घोषणा CCI_IRQ_MASK_0_I2C_M1_Q0Q1_HALT_ACK	BIT(26)
#घोषणा CCI_IRQ_MASK_0_I2C_M0_ERROR		0x18000ee6
#घोषणा CCI_IRQ_MASK_0_I2C_M1_ERROR		0x60ee6000
#घोषणा CCI_IRQ_CLEAR_0				0xc08
#घोषणा CCI_IRQ_STATUS_0			0xc0c
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_RD_DONE		BIT(0)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_Q0_REPORT	BIT(4)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_Q1_REPORT	BIT(8)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_RD_DONE		BIT(12)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_Q0_REPORT	BIT(16)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_Q1_REPORT	BIT(20)
#घोषणा CCI_IRQ_STATUS_0_RST_DONE_ACK		BIT(24)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_Q0Q1_HALT_ACK	BIT(25)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_Q0Q1_HALT_ACK	BIT(26)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_Q0_NACK_ERR	BIT(27)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_Q1_NACK_ERR	BIT(28)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_Q0_NACK_ERR	BIT(29)
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_Q1_NACK_ERR	BIT(30)
#घोषणा CCI_IRQ_STATUS_0_I2C_M0_ERROR		0x18000ee6
#घोषणा CCI_IRQ_STATUS_0_I2C_M1_ERROR		0x60ee6000

#घोषणा CCI_TIMEOUT	(msecs_to_jअगरfies(100))
#घोषणा NUM_MASTERS	2
#घोषणा NUM_QUEUES	2

/* Max number of resources + 1 क्रम a शून्य terminator */
#घोषणा CCI_RES_MAX	6

#घोषणा CCI_I2C_SET_PARAM	1
#घोषणा CCI_I2C_REPORT		8
#घोषणा CCI_I2C_WRITE		9
#घोषणा CCI_I2C_READ		10

#घोषणा CCI_I2C_REPORT_IRQ_EN	BIT(8)

क्रमागत अणु
	I2C_MODE_STANDARD,
	I2C_MODE_FAST,
	I2C_MODE_FAST_PLUS,
पूर्ण;

क्रमागत cci_i2c_queue_t अणु
	QUEUE_0,
	QUEUE_1
पूर्ण;

काष्ठा hw_params अणु
	u16 thigh; /* HIGH period of the SCL घड़ी in घड़ी ticks */
	u16 tlow; /* LOW period of the SCL घड़ी */
	u16 tsu_sto; /* set-up समय क्रम STOP condition */
	u16 tsu_sta; /* set-up समय क्रम a repeated START condition */
	u16 thd_dat; /* data hold समय */
	u16 thd_sta; /* hold समय (repeated) START condition */
	u16 tbuf; /* bus मुक्त समय between a STOP and START condition */
	u8 scl_stretch_en;
	u16 trdhld;
	u16 tsp; /* pulse width of spikes suppressed by the input filter */
पूर्ण;

काष्ठा cci;

काष्ठा cci_master अणु
	काष्ठा i2c_adapter adap;
	u16 master;
	u8 mode;
	पूर्णांक status;
	काष्ठा completion irq_complete;
	काष्ठा cci *cci;
पूर्ण;

काष्ठा cci_data अणु
	अचिन्हित पूर्णांक num_masters;
	काष्ठा i2c_adapter_quirks quirks;
	u16 queue_size[NUM_QUEUES];
	अचिन्हित दीर्घ cci_clk_rate;
	काष्ठा hw_params params[3];
पूर्ण;

काष्ठा cci अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	अचिन्हित पूर्णांक irq;
	स्थिर काष्ठा cci_data *data;
	काष्ठा clk_bulk_data *घड़ीs;
	पूर्णांक nघड़ीs;
	काष्ठा cci_master master[NUM_MASTERS];
पूर्ण;

अटल irqवापस_t cci_isr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा cci *cci = dev;
	u32 val, reset = 0;
	पूर्णांक ret = IRQ_NONE;

	val = पढ़ोl(cci->base + CCI_IRQ_STATUS_0);
	ग_लिखोl(val, cci->base + CCI_IRQ_CLEAR_0);
	ग_लिखोl(0x1, cci->base + CCI_IRQ_GLOBAL_CLEAR_CMD);

	अगर (val & CCI_IRQ_STATUS_0_RST_DONE_ACK) अणु
		complete(&cci->master[0].irq_complete);
		अगर (cci->master[1].master)
			complete(&cci->master[1].irq_complete);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (val & CCI_IRQ_STATUS_0_I2C_M0_RD_DONE ||
			val & CCI_IRQ_STATUS_0_I2C_M0_Q0_REPORT ||
			val & CCI_IRQ_STATUS_0_I2C_M0_Q1_REPORT) अणु
		cci->master[0].status = 0;
		complete(&cci->master[0].irq_complete);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (val & CCI_IRQ_STATUS_0_I2C_M1_RD_DONE ||
			val & CCI_IRQ_STATUS_0_I2C_M1_Q0_REPORT ||
			val & CCI_IRQ_STATUS_0_I2C_M1_Q1_REPORT) अणु
		cci->master[1].status = 0;
		complete(&cci->master[1].irq_complete);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(val & CCI_IRQ_STATUS_0_I2C_M0_Q0Q1_HALT_ACK)) अणु
		reset = CCI_RESET_CMD_M0_MASK;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(val & CCI_IRQ_STATUS_0_I2C_M1_Q0Q1_HALT_ACK)) अणु
		reset = CCI_RESET_CMD_M1_MASK;
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(reset))
		ग_लिखोl(reset, cci->base + CCI_RESET_CMD);

	अगर (unlikely(val & CCI_IRQ_STATUS_0_I2C_M0_ERROR)) अणु
		अगर (val & CCI_IRQ_STATUS_0_I2C_M0_Q0_NACK_ERR ||
			val & CCI_IRQ_STATUS_0_I2C_M0_Q1_NACK_ERR)
			cci->master[0].status = -ENXIO;
		अन्यथा
			cci->master[0].status = -EIO;

		ग_लिखोl(CCI_HALT_REQ_I2C_M0_Q0Q1, cci->base + CCI_HALT_REQ);
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(val & CCI_IRQ_STATUS_0_I2C_M1_ERROR)) अणु
		अगर (val & CCI_IRQ_STATUS_0_I2C_M1_Q0_NACK_ERR ||
			val & CCI_IRQ_STATUS_0_I2C_M1_Q1_NACK_ERR)
			cci->master[1].status = -ENXIO;
		अन्यथा
			cci->master[1].status = -EIO;

		ग_लिखोl(CCI_HALT_REQ_I2C_M1_Q0Q1, cci->base + CCI_HALT_REQ);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cci_halt(काष्ठा cci *cci, u8 master_num)
अणु
	काष्ठा cci_master *master;
	u32 val;

	अगर (master_num >= cci->data->num_masters) अणु
		dev_err(cci->dev, "Unsupported master idx (%u)\n", master_num);
		वापस -EINVAL;
	पूर्ण

	val = BIT(master_num);
	master = &cci->master[master_num];

	reinit_completion(&master->irq_complete);
	ग_लिखोl(val, cci->base + CCI_HALT_REQ);

	अगर (!रुको_क्रम_completion_समयout(&master->irq_complete, CCI_TIMEOUT)) अणु
		dev_err(cci->dev, "CCI halt timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cci_reset(काष्ठा cci *cci)
अणु
	/*
	 * we reset the whole controller, here and क्रम implicity use
	 * master[0].xxx क्रम रुकोing on it.
	 */
	reinit_completion(&cci->master[0].irq_complete);
	ग_लिखोl(CCI_RESET_CMD_MASK, cci->base + CCI_RESET_CMD);

	अगर (!रुको_क्रम_completion_समयout(&cci->master[0].irq_complete,
					 CCI_TIMEOUT)) अणु
		dev_err(cci->dev, "CCI reset timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cci_init(काष्ठा cci *cci)
अणु
	u32 val = CCI_IRQ_MASK_0_I2C_M0_RD_DONE |
			CCI_IRQ_MASK_0_I2C_M0_Q0_REPORT |
			CCI_IRQ_MASK_0_I2C_M0_Q1_REPORT |
			CCI_IRQ_MASK_0_I2C_M1_RD_DONE |
			CCI_IRQ_MASK_0_I2C_M1_Q0_REPORT |
			CCI_IRQ_MASK_0_I2C_M1_Q1_REPORT |
			CCI_IRQ_MASK_0_RST_DONE_ACK |
			CCI_IRQ_MASK_0_I2C_M0_Q0Q1_HALT_ACK |
			CCI_IRQ_MASK_0_I2C_M1_Q0Q1_HALT_ACK |
			CCI_IRQ_MASK_0_I2C_M0_ERROR |
			CCI_IRQ_MASK_0_I2C_M1_ERROR;
	पूर्णांक i;

	ग_लिखोl(val, cci->base + CCI_IRQ_MASK_0);

	क्रम (i = 0; i < cci->data->num_masters; i++) अणु
		पूर्णांक mode = cci->master[i].mode;
		स्थिर काष्ठा hw_params *hw;

		अगर (!cci->master[i].cci)
			जारी;

		hw = &cci->data->params[mode];

		val = hw->thigh << 16 | hw->tlow;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_SCL_CTL(i));

		val = hw->tsu_sto << 16 | hw->tsu_sta;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_SDA_CTL_0(i));

		val = hw->thd_dat << 16 | hw->thd_sta;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_SDA_CTL_1(i));

		val = hw->tbuf;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_SDA_CTL_2(i));

		val = hw->scl_stretch_en << 8 | hw->trdhld << 4 | hw->tsp;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_MISC_CTL(i));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cci_run_queue(काष्ठा cci *cci, u8 master, u8 queue)
अणु
	u32 val;

	val = पढ़ोl(cci->base + CCI_I2C_Mm_Qn_CUR_WORD_CNT(master, queue));
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_EXEC_WORD_CNT(master, queue));

	reinit_completion(&cci->master[master].irq_complete);
	val = BIT(master * 2 + queue);
	ग_लिखोl(val, cci->base + CCI_QUEUE_START);

	अगर (!रुको_क्रम_completion_समयout(&cci->master[master].irq_complete,
					 CCI_TIMEOUT)) अणु
		dev_err(cci->dev, "master %d queue %d timeout\n",
			master, queue);
		cci_reset(cci);
		cci_init(cci);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस cci->master[master].status;
पूर्ण

अटल पूर्णांक cci_validate_queue(काष्ठा cci *cci, u8 master, u8 queue)
अणु
	u32 val;

	val = पढ़ोl(cci->base + CCI_I2C_Mm_Qn_CUR_WORD_CNT(master, queue));
	अगर (val == cci->data->queue_size[queue])
		वापस -EINVAL;

	अगर (!val)
		वापस 0;

	val = CCI_I2C_REPORT | CCI_I2C_REPORT_IRQ_EN;
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));

	वापस cci_run_queue(cci, master, queue);
पूर्ण

अटल पूर्णांक cci_i2c_पढ़ो(काष्ठा cci *cci, u16 master,
			u16 addr, u8 *buf, u16 len)
अणु
	u32 val, words_पढ़ो, words_exp;
	u8 queue = QUEUE_1;
	पूर्णांक i, index = 0, ret;
	bool first = true;

	/*
	 * Call validate queue to make sure queue is empty beक्रमe starting.
	 * This is to aव्योम overflow / underflow of queue.
	 */
	ret = cci_validate_queue(cci, master, queue);
	अगर (ret < 0)
		वापस ret;

	val = CCI_I2C_SET_PARAM | (addr & 0x7f) << 4;
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));

	val = CCI_I2C_READ | len << 4;
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));

	ret = cci_run_queue(cci, master, queue);
	अगर (ret < 0)
		वापस ret;

	words_पढ़ो = पढ़ोl(cci->base + CCI_I2C_Mm_READ_BUF_LEVEL(master));
	words_exp = len / 4 + 1;
	अगर (words_पढ़ो != words_exp) अणु
		dev_err(cci->dev, "words read = %d, words expected = %d\n",
			words_पढ़ो, words_exp);
		वापस -EIO;
	पूर्ण

	करो अणु
		val = पढ़ोl(cci->base + CCI_I2C_Mm_READ_DATA(master));

		क्रम (i = 0; i < 4 && index < len; i++) अणु
			अगर (first) अणु
				/* The LS byte of this रेजिस्टर represents the
				 * first byte पढ़ो from the slave during a पढ़ो
				 * access.
				 */
				first = false;
				जारी;
			पूर्ण
			buf[index++] = (val >> (i * 8)) & 0xff;
		पूर्ण
	पूर्ण जबतक (--words_पढ़ो);

	वापस 0;
पूर्ण

अटल पूर्णांक cci_i2c_ग_लिखो(काष्ठा cci *cci, u16 master,
			 u16 addr, u8 *buf, u16 len)
अणु
	u8 queue = QUEUE_0;
	u8 load[12] = अणु 0 पूर्ण;
	पूर्णांक i = 0, j, ret;
	u32 val;

	/*
	 * Call validate queue to make sure queue is empty beक्रमe starting.
	 * This is to aव्योम overflow / underflow of queue.
	 */
	ret = cci_validate_queue(cci, master, queue);
	अगर (ret < 0)
		वापस ret;

	val = CCI_I2C_SET_PARAM | (addr & 0x7f) << 4;
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));

	load[i++] = CCI_I2C_WRITE | len << 4;

	क्रम (j = 0; j < len; j++)
		load[i++] = buf[j];

	क्रम (j = 0; j < i; j += 4) अणु
		val = load[j];
		val |= load[j + 1] << 8;
		val |= load[j + 2] << 16;
		val |= load[j + 3] << 24;
		ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));
	पूर्ण

	val = CCI_I2C_REPORT | CCI_I2C_REPORT_IRQ_EN;
	ग_लिखोl(val, cci->base + CCI_I2C_Mm_Qn_LOAD_DATA(master, queue));

	वापस cci_run_queue(cci, master, queue);
पूर्ण

अटल पूर्णांक cci_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा cci_master *cci_master = i2c_get_adapdata(adap);
	काष्ठा cci *cci = cci_master->cci;
	पूर्णांक i, ret;

	ret = pm_runसमय_get_sync(cci->dev);
	अगर (ret < 0)
		जाओ err;

	क्रम (i = 0; i < num; i++) अणु
		अगर (msgs[i].flags & I2C_M_RD)
			ret = cci_i2c_पढ़ो(cci, cci_master->master,
					   msgs[i].addr, msgs[i].buf,
					   msgs[i].len);
		अन्यथा
			ret = cci_i2c_ग_लिखो(cci, cci_master->master,
					    msgs[i].addr, msgs[i].buf,
					    msgs[i].len);

		अगर (ret < 0)
			अवरोध;
	पूर्ण

	अगर (!ret)
		ret = num;

err:
	pm_runसमय_mark_last_busy(cci->dev);
	pm_runसमय_put_स्वतःsuspend(cci->dev);

	वापस ret;
पूर्ण

अटल u32 cci_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm cci_algo = अणु
	.master_xfer	= cci_xfer,
	.functionality	= cci_func,
पूर्ण;

अटल पूर्णांक cci_enable_घड़ीs(काष्ठा cci *cci)
अणु
	वापस clk_bulk_prepare_enable(cci->nघड़ीs, cci->घड़ीs);
पूर्ण

अटल व्योम cci_disable_घड़ीs(काष्ठा cci *cci)
अणु
	clk_bulk_disable_unprepare(cci->nघड़ीs, cci->घड़ीs);
पूर्ण

अटल पूर्णांक __maybe_unused cci_suspend_runसमय(काष्ठा device *dev)
अणु
	काष्ठा cci *cci = dev_get_drvdata(dev);

	cci_disable_घड़ीs(cci);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cci_resume_runसमय(काष्ठा device *dev)
अणु
	काष्ठा cci *cci = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = cci_enable_घड़ीs(cci);
	अगर (ret)
		वापस ret;

	cci_init(cci);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cci_suspend(काष्ठा device *dev)
अणु
	अगर (!pm_runसमय_suspended(dev))
		वापस cci_suspend_runसमय(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cci_resume(काष्ठा device *dev)
अणु
	cci_resume_runसमय(dev);
	pm_runसमय_mark_last_busy(dev);
	pm_request_स्वतःsuspend(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qcom_cci_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cci_suspend, cci_resume)
	SET_RUNTIME_PM_OPS(cci_suspend_runसमय, cci_resume_runसमय, शून्य)
पूर्ण;

अटल पूर्णांक cci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	अचिन्हित दीर्घ cci_clk_rate = 0;
	काष्ठा device_node *child;
	काष्ठा resource *r;
	काष्ठा cci *cci;
	पूर्णांक ret, i;
	u32 val;

	cci = devm_kzalloc(dev, माप(*cci), GFP_KERNEL);
	अगर (!cci)
		वापस -ENOMEM;

	cci->dev = dev;
	platक्रमm_set_drvdata(pdev, cci);
	cci->data = device_get_match_data(dev);
	अगर (!cci->data)
		वापस -ENOENT;

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		u32 idx;

		ret = of_property_पढ़ो_u32(child, "reg", &idx);
		अगर (ret) अणु
			dev_err(dev, "%pOF invalid 'reg' property", child);
			जारी;
		पूर्ण

		अगर (idx >= cci->data->num_masters) अणु
			dev_err(dev, "%pOF invalid 'reg' value: %u (max is %u)",
				child, idx, cci->data->num_masters - 1);
			जारी;
		पूर्ण

		cci->master[idx].adap.quirks = &cci->data->quirks;
		cci->master[idx].adap.algo = &cci_algo;
		cci->master[idx].adap.dev.parent = dev;
		cci->master[idx].adap.dev.of_node = child;
		cci->master[idx].master = idx;
		cci->master[idx].cci = cci;

		i2c_set_adapdata(&cci->master[idx].adap, &cci->master[idx]);
		snम_लिखो(cci->master[idx].adap.name,
			 माप(cci->master[idx].adap.name), "Qualcomm-CCI");

		cci->master[idx].mode = I2C_MODE_STANDARD;
		ret = of_property_पढ़ो_u32(child, "clock-frequency", &val);
		अगर (!ret) अणु
			अगर (val == I2C_MAX_FAST_MODE_FREQ)
				cci->master[idx].mode = I2C_MODE_FAST;
			अन्यथा अगर (val == I2C_MAX_FAST_MODE_PLUS_FREQ)
				cci->master[idx].mode = I2C_MODE_FAST_PLUS;
		पूर्ण

		init_completion(&cci->master[idx].irq_complete);
	पूर्ण

	/* Memory */

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	cci->base = devm_ioremap_resource(dev, r);
	अगर (IS_ERR(cci->base))
		वापस PTR_ERR(cci->base);

	/* Clocks */

	ret = devm_clk_bulk_get_all(dev, &cci->घड़ीs);
	अगर (ret < 1) अणु
		dev_err(dev, "failed to get clocks %d\n", ret);
		वापस ret;
	पूर्ण
	cci->nघड़ीs = ret;

	/* Retrieve CCI घड़ी rate */
	क्रम (i = 0; i < cci->nघड़ीs; i++) अणु
		अगर (!म_भेद(cci->घड़ीs[i].id, "cci")) अणु
			cci_clk_rate = clk_get_rate(cci->घड़ीs[i].clk);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (cci_clk_rate != cci->data->cci_clk_rate) अणु
		/* cci घड़ी set by the bootloader or via asचिन्हित घड़ी rate
		 * in DT.
		 */
		dev_warn(dev, "Found %lu cci clk rate while %lu was expected\n",
			 cci_clk_rate, cci->data->cci_clk_rate);
	पूर्ण

	ret = cci_enable_घड़ीs(cci);
	अगर (ret < 0)
		वापस ret;

	/* Interrupt */

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		जाओ disable_घड़ीs;
	cci->irq = ret;

	ret = devm_request_irq(dev, cci->irq, cci_isr, 0, dev_name(dev), cci);
	अगर (ret < 0) अणु
		dev_err(dev, "request_irq failed, ret: %d\n", ret);
		जाओ disable_घड़ीs;
	पूर्ण

	val = पढ़ोl(cci->base + CCI_HW_VERSION);
	dev_dbg(dev, "CCI HW version = 0x%08x", val);

	ret = cci_reset(cci);
	अगर (ret < 0)
		जाओ error;

	ret = cci_init(cci);
	अगर (ret < 0)
		जाओ error;

	क्रम (i = 0; i < cci->data->num_masters; i++) अणु
		अगर (!cci->master[i].cci)
			जारी;

		ret = i2c_add_adapter(&cci->master[i].adap);
		अगर (ret < 0)
			जाओ error_i2c;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev, MSEC_PER_SEC);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	वापस 0;

error_i2c:
	क्रम (; i >= 0; i--) अणु
		अगर (cci->master[i].cci)
			i2c_del_adapter(&cci->master[i].adap);
	पूर्ण
error:
	disable_irq(cci->irq);
disable_घड़ीs:
	cci_disable_घड़ीs(cci);

	वापस ret;
पूर्ण

अटल पूर्णांक cci_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cci *cci = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < cci->data->num_masters; i++) अणु
		अगर (cci->master[i].cci)
			i2c_del_adapter(&cci->master[i].adap);
		cci_halt(cci, i);
	पूर्ण

	disable_irq(cci->irq);
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cci_data cci_v1_data = अणु
	.num_masters = 1,
	.queue_size = अणु 64, 16 पूर्ण,
	.quirks = अणु
		.max_ग_लिखो_len = 10,
		.max_पढ़ो_len = 12,
	पूर्ण,
	.cci_clk_rate =  19200000,
	.params[I2C_MODE_STANDARD] = अणु
		.thigh = 78,
		.tlow = 114,
		.tsu_sto = 28,
		.tsu_sta = 28,
		.thd_dat = 10,
		.thd_sta = 77,
		.tbuf = 118,
		.scl_stretch_en = 0,
		.trdhld = 6,
		.tsp = 1
	पूर्ण,
	.params[I2C_MODE_FAST] = अणु
		.thigh = 20,
		.tlow = 28,
		.tsu_sto = 21,
		.tsu_sta = 21,
		.thd_dat = 13,
		.thd_sta = 18,
		.tbuf = 32,
		.scl_stretch_en = 0,
		.trdhld = 6,
		.tsp = 3
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा cci_data cci_v2_data = अणु
	.num_masters = 2,
	.queue_size = अणु 64, 16 पूर्ण,
	.quirks = अणु
		.max_ग_लिखो_len = 11,
		.max_पढ़ो_len = 12,
	पूर्ण,
	.cci_clk_rate =  37500000,
	.params[I2C_MODE_STANDARD] = अणु
		.thigh = 201,
		.tlow = 174,
		.tsu_sto = 204,
		.tsu_sta = 231,
		.thd_dat = 22,
		.thd_sta = 162,
		.tbuf = 227,
		.scl_stretch_en = 0,
		.trdhld = 6,
		.tsp = 3
	पूर्ण,
	.params[I2C_MODE_FAST] = अणु
		.thigh = 38,
		.tlow = 56,
		.tsu_sto = 40,
		.tsu_sta = 40,
		.thd_dat = 22,
		.thd_sta = 35,
		.tbuf = 62,
		.scl_stretch_en = 0,
		.trdhld = 6,
		.tsp = 3
	पूर्ण,
	.params[I2C_MODE_FAST_PLUS] = अणु
		.thigh = 16,
		.tlow = 22,
		.tsu_sto = 17,
		.tsu_sta = 18,
		.thd_dat = 16,
		.thd_sta = 15,
		.tbuf = 24,
		.scl_stretch_en = 0,
		.trdhld = 3,
		.tsp = 3
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id cci_dt_match[] = अणु
	अणु .compatible = "qcom,msm8916-cci", .data = &cci_v1_dataपूर्ण,
	अणु .compatible = "qcom,msm8996-cci", .data = &cci_v2_dataपूर्ण,
	अणु .compatible = "qcom,sdm845-cci", .data = &cci_v2_dataपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cci_dt_match);

अटल काष्ठा platक्रमm_driver qcom_cci_driver = अणु
	.probe  = cci_probe,
	.हटाओ = cci_हटाओ,
	.driver = अणु
		.name = "i2c-qcom-cci",
		.of_match_table = cci_dt_match,
		.pm = &qcom_cci_pm,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(qcom_cci_driver);

MODULE_DESCRIPTION("Qualcomm Camera Control Interface driver");
MODULE_AUTHOR("Todor Tomov <todor.tomov@linaro.org>");
MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
MODULE_LICENSE("GPL v2");
