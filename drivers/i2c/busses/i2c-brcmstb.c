<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#घोषणा N_DATA_REGS					8

/*
 * PER_I2C/BSC count रेजिस्टर mask depends on 1 byte/4 byte data रेजिस्टर
 * size. Cable modem and DSL SoCs with Peripheral i2c cores use 1 byte per
 * data रेजिस्टर whereas STB SoCs use 4 byte per data रेजिस्टर transfer,
 * account क्रम this dअगरference in total count per transaction and mask to
 * use.
 */
#घोषणा BSC_CNT_REG1_MASK(nb)	(nb == 1 ? GENMASK(3, 0) : GENMASK(5, 0))
#घोषणा BSC_CNT_REG1_SHIFT	0

/* BSC CTL रेजिस्टर field definitions */
#घोषणा BSC_CTL_REG_DTF_MASK				0x00000003
#घोषणा BSC_CTL_REG_SCL_SEL_MASK			0x00000030
#घोषणा BSC_CTL_REG_SCL_SEL_SHIFT			4
#घोषणा BSC_CTL_REG_INT_EN_MASK				0x00000040
#घोषणा BSC_CTL_REG_INT_EN_SHIFT			6
#घोषणा BSC_CTL_REG_DIV_CLK_MASK			0x00000080

/* BSC_IIC_ENABLE r/w enable and पूर्णांकerrupt field definitions */
#घोषणा BSC_IIC_EN_RESTART_MASK				0x00000040
#घोषणा BSC_IIC_EN_NOSTART_MASK				0x00000020
#घोषणा BSC_IIC_EN_NOSTOP_MASK				0x00000010
#घोषणा BSC_IIC_EN_NOACK_MASK				0x00000004
#घोषणा BSC_IIC_EN_INTRP_MASK				0x00000002
#घोषणा BSC_IIC_EN_ENABLE_MASK				0x00000001

/* BSC_CTLHI control रेजिस्टर field definitions */
#घोषणा BSC_CTLHI_REG_INPUT_SWITCHING_LEVEL_MASK	0x00000080
#घोषणा BSC_CTLHI_REG_DATAREG_SIZE_MASK			0x00000040
#घोषणा BSC_CTLHI_REG_IGNORE_ACK_MASK			0x00000002
#घोषणा BSC_CTLHI_REG_WAIT_DIS_MASK			0x00000001

#घोषणा I2C_TIMEOUT					100 /* msecs */

/* Condition mask used क्रम non combined transfer */
#घोषणा COND_RESTART		BSC_IIC_EN_RESTART_MASK
#घोषणा COND_NOSTART		BSC_IIC_EN_NOSTART_MASK
#घोषणा COND_NOSTOP		BSC_IIC_EN_NOSTOP_MASK
#घोषणा COND_START_STOP		(COND_RESTART | COND_NOSTART | COND_NOSTOP)

/* BSC data transfer direction */
#घोषणा DTF_WR_MASK		0x00000000
#घोषणा DTF_RD_MASK		0x00000001
/* BSC data transfer direction combined क्रमmat */
#घोषणा DTF_RD_WR_MASK		0x00000002
#घोषणा DTF_WR_RD_MASK		0x00000003

#घोषणा INT_ENABLE		true
#घोषणा INT_DISABLE		false

/* BSC block रेजिस्टर map काष्ठाure to cache fields to be written */
काष्ठा bsc_regs अणु
	u32	chip_address;           /* slave address */
	u32	data_in[N_DATA_REGS];   /* tx data buffer*/
	u32	cnt_reg;		/* rx/tx data length */
	u32	ctl_reg;		/* control रेजिस्टर */
	u32	iic_enable;		/* xfer enable and status */
	u32	data_out[N_DATA_REGS];  /* rx data buffer */
	u32	ctlhi_reg;		/* more control fields */
	u32	scl_param;		/* reserved */
पूर्ण;

काष्ठा bsc_clk_param अणु
	u32 hz;
	u32 scl_mask;
	u32 भाग_mask;
पूर्ण;

क्रमागत bsc_xfer_cmd अणु
	CMD_WR,
	CMD_RD,
	CMD_WR_NOACK,
	CMD_RD_NOACK,
पूर्ण;

अटल अक्षर स्थिर *cmd_string[] = अणु
	[CMD_WR] = "WR",
	[CMD_RD] = "RD",
	[CMD_WR_NOACK] = "WR NOACK",
	[CMD_RD_NOACK] = "RD NOACK",
पूर्ण;

क्रमागत bus_speeds अणु
	SPD_375K,
	SPD_390K,
	SPD_187K,
	SPD_200K,
	SPD_93K,
	SPD_97K,
	SPD_46K,
	SPD_50K
पूर्ण;

अटल स्थिर काष्ठा bsc_clk_param bsc_clk[] = अणु
	[SPD_375K] = अणु
		.hz = 375000,
		.scl_mask = SPD_375K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = 0
	पूर्ण,
	[SPD_390K] = अणु
		.hz = 390000,
		.scl_mask = SPD_390K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = 0
	पूर्ण,
	[SPD_187K] = अणु
		.hz = 187500,
		.scl_mask = SPD_187K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = 0
	पूर्ण,
	[SPD_200K] = अणु
		.hz = 200000,
		.scl_mask = SPD_200K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = 0
	पूर्ण,
	[SPD_93K]  = अणु
		.hz = 93750,
		.scl_mask = SPD_375K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = BSC_CTL_REG_DIV_CLK_MASK
	पूर्ण,
	[SPD_97K]  = अणु
		.hz = 97500,
		.scl_mask = SPD_390K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = BSC_CTL_REG_DIV_CLK_MASK
	पूर्ण,
	[SPD_46K]  = अणु
		.hz = 46875,
		.scl_mask = SPD_187K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = BSC_CTL_REG_DIV_CLK_MASK
	पूर्ण,
	[SPD_50K]  = अणु
		.hz = 50000,
		.scl_mask = SPD_200K << BSC_CTL_REG_SCL_SEL_SHIFT,
		.भाग_mask = BSC_CTL_REG_DIV_CLK_MASK
	पूर्ण
पूर्ण;

काष्ठा brcmstb_i2c_dev अणु
	काष्ठा device *device;
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा bsc_regs *bsc_regmap;
	काष्ठा i2c_adapter adapter;
	काष्ठा completion करोne;
	u32 clk_freq_hz;
	पूर्णांक data_regsz;
पूर्ण;

/* रेजिस्टर accessors क्रम both be and le cpu arch */
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
#घोषणा __bsc_पढ़ोl(_reg) ioपढ़ो32be(_reg)
#घोषणा __bsc_ग_लिखोl(_val, _reg) ioग_लिखो32be(_val, _reg)
#अन्यथा
#घोषणा __bsc_पढ़ोl(_reg) ioपढ़ो32(_reg)
#घोषणा __bsc_ग_लिखोl(_val, _reg) ioग_लिखो32(_val, _reg)
#पूर्ण_अगर

#घोषणा bsc_पढ़ोl(_dev, _reg)						\
	__bsc_पढ़ोl(_dev->base + दुरत्व(काष्ठा bsc_regs, _reg))

#घोषणा bsc_ग_लिखोl(_dev, _val, _reg)					\
	__bsc_ग_लिखोl(_val, _dev->base + दुरत्व(काष्ठा bsc_regs, _reg))

अटल अंतरभूत पूर्णांक brcmstb_i2c_get_xfersz(काष्ठा brcmstb_i2c_dev *dev)
अणु
	वापस (N_DATA_REGS * dev->data_regsz);
पूर्ण

अटल अंतरभूत पूर्णांक brcmstb_i2c_get_data_regsz(काष्ठा brcmstb_i2c_dev *dev)
अणु
	वापस dev->data_regsz;
पूर्ण

अटल व्योम brcmstb_i2c_enable_disable_irq(काष्ठा brcmstb_i2c_dev *dev,
					   bool पूर्णांक_en)
अणु

	अगर (पूर्णांक_en)
		/* Enable BSC  CTL पूर्णांकerrupt line */
		dev->bsc_regmap->ctl_reg |= BSC_CTL_REG_INT_EN_MASK;
	अन्यथा
		/* Disable BSC CTL पूर्णांकerrupt line */
		dev->bsc_regmap->ctl_reg &= ~BSC_CTL_REG_INT_EN_MASK;

	barrier();
	bsc_ग_लिखोl(dev, dev->bsc_regmap->ctl_reg, ctl_reg);
पूर्ण

अटल irqवापस_t brcmstb_i2c_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा brcmstb_i2c_dev *dev = devid;
	u32 status_bsc_ctl = bsc_पढ़ोl(dev, ctl_reg);
	u32 status_iic_पूर्णांकrp = bsc_पढ़ोl(dev, iic_enable);

	dev_dbg(dev->device, "isr CTL_REG %x IIC_EN %x\n",
		status_bsc_ctl, status_iic_पूर्णांकrp);

	अगर (!(status_bsc_ctl & BSC_CTL_REG_INT_EN_MASK))
		वापस IRQ_NONE;

	brcmstb_i2c_enable_disable_irq(dev, INT_DISABLE);
	complete(&dev->करोne);

	dev_dbg(dev->device, "isr handled");
	वापस IRQ_HANDLED;
पूर्ण

/* Wait क्रम device to be पढ़ोy */
अटल पूर्णांक brcmstb_i2c_रुको_अगर_busy(काष्ठा brcmstb_i2c_dev *dev)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(I2C_TIMEOUT);

	जबतक ((bsc_पढ़ोl(dev, iic_enable) & BSC_IIC_EN_INTRP_MASK)) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

/* i2c xfer completion function, handles both irq and polling mode */
अटल पूर्णांक brcmstb_i2c_रुको_क्रम_completion(काष्ठा brcmstb_i2c_dev *dev)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(I2C_TIMEOUT);

	अगर (dev->irq >= 0) अणु
		अगर (!रुको_क्रम_completion_समयout(&dev->करोne, समयout))
			ret = -ETIMEDOUT;
	पूर्ण अन्यथा अणु
		/* we are in polling mode */
		u32 bsc_पूर्णांकrp;
		अचिन्हित दीर्घ समय_left = jअगरfies + समयout;

		करो अणु
			bsc_पूर्णांकrp = bsc_पढ़ोl(dev, iic_enable) &
				BSC_IIC_EN_INTRP_MASK;
			अगर (समय_after(jअगरfies, समय_left)) अणु
				ret = -ETIMEDOUT;
				अवरोध;
			पूर्ण
			cpu_relax();
		पूर्ण जबतक (!bsc_पूर्णांकrp);
	पूर्ण

	अगर (dev->irq < 0 || ret == -ETIMEDOUT)
		brcmstb_i2c_enable_disable_irq(dev, INT_DISABLE);

	वापस ret;
पूर्ण

/* Set xfer START/STOP conditions क्रम subsequent transfer */
अटल व्योम brcmstb_set_i2c_start_stop(काष्ठा brcmstb_i2c_dev *dev,
				       u32 cond_flag)
अणु
	u32 regval = dev->bsc_regmap->iic_enable;

	dev->bsc_regmap->iic_enable = (regval & ~COND_START_STOP) | cond_flag;
पूर्ण

/* Send I2C request check completion */
अटल पूर्णांक brcmstb_send_i2c_cmd(काष्ठा brcmstb_i2c_dev *dev,
				क्रमागत bsc_xfer_cmd cmd)
अणु
	पूर्णांक rc = 0;
	काष्ठा bsc_regs *pi2creg = dev->bsc_regmap;

	/* Make sure the hardware is पढ़ोy */
	rc = brcmstb_i2c_रुको_अगर_busy(dev);
	अगर (rc < 0)
		वापस rc;

	/* only अगर we are in पूर्णांकerrupt mode */
	अगर (dev->irq >= 0)
		reinit_completion(&dev->करोne);

	/* enable BSC CTL पूर्णांकerrupt line */
	brcmstb_i2c_enable_disable_irq(dev, INT_ENABLE);

	/* initiate transfer by setting iic_enable */
	pi2creg->iic_enable |= BSC_IIC_EN_ENABLE_MASK;
	bsc_ग_लिखोl(dev, pi2creg->iic_enable, iic_enable);

	/* Wait क्रम transaction to finish or समयout */
	rc = brcmstb_i2c_रुको_क्रम_completion(dev);
	अगर (rc) अणु
		dev_dbg(dev->device, "intr timeout for cmd %s\n",
			cmd_string[cmd]);
		जाओ cmd_out;
	पूर्ण

	अगर ((cmd == CMD_RD || cmd == CMD_WR) &&
	    bsc_पढ़ोl(dev, iic_enable) & BSC_IIC_EN_NOACK_MASK) अणु
		rc = -EREMOTEIO;
		dev_dbg(dev->device, "controller received NOACK intr for %s\n",
			cmd_string[cmd]);
	पूर्ण

cmd_out:
	bsc_ग_लिखोl(dev, 0, cnt_reg);
	bsc_ग_लिखोl(dev, 0, iic_enable);

	वापस rc;
पूर्ण

/* Actual data transfer through the BSC master */
अटल पूर्णांक brcmstb_i2c_xfer_bsc_data(काष्ठा brcmstb_i2c_dev *dev,
				     u8 *buf, अचिन्हित पूर्णांक len,
				     काष्ठा i2c_msg *pmsg)
अणु
	पूर्णांक cnt, byte, i, rc;
	क्रमागत bsc_xfer_cmd cmd;
	u32 ctl_reg;
	काष्ठा bsc_regs *pi2creg = dev->bsc_regmap;
	पूर्णांक no_ack = pmsg->flags & I2C_M_IGNORE_NAK;
	पूर्णांक data_regsz = brcmstb_i2c_get_data_regsz(dev);

	/* see अगर the transaction needs to check NACK conditions */
	अगर (no_ack) अणु
		cmd = (pmsg->flags & I2C_M_RD) ? CMD_RD_NOACK
			: CMD_WR_NOACK;
		pi2creg->ctlhi_reg |= BSC_CTLHI_REG_IGNORE_ACK_MASK;
	पूर्ण अन्यथा अणु
		cmd = (pmsg->flags & I2C_M_RD) ? CMD_RD : CMD_WR;
		pi2creg->ctlhi_reg &= ~BSC_CTLHI_REG_IGNORE_ACK_MASK;
	पूर्ण
	bsc_ग_लिखोl(dev, pi2creg->ctlhi_reg, ctlhi_reg);

	/* set data transfer direction */
	ctl_reg = pi2creg->ctl_reg & ~BSC_CTL_REG_DTF_MASK;
	अगर (cmd == CMD_WR || cmd == CMD_WR_NOACK)
		pi2creg->ctl_reg = ctl_reg | DTF_WR_MASK;
	अन्यथा
		pi2creg->ctl_reg = ctl_reg | DTF_RD_MASK;

	/* set the पढ़ो/ग_लिखो length */
	bsc_ग_लिखोl(dev, BSC_CNT_REG1_MASK(data_regsz) &
		   (len << BSC_CNT_REG1_SHIFT), cnt_reg);

	/* Write data पूर्णांकo data_in रेजिस्टर */

	अगर (cmd == CMD_WR || cmd == CMD_WR_NOACK) अणु
		क्रम (cnt = 0, i = 0; cnt < len; cnt += data_regsz, i++) अणु
			u32 word = 0;

			क्रम (byte = 0; byte < data_regsz; byte++) अणु
				word >>= BITS_PER_BYTE;
				अगर ((cnt + byte) < len)
					word |= buf[cnt + byte] <<
					(BITS_PER_BYTE * (data_regsz - 1));
			पूर्ण
			bsc_ग_लिखोl(dev, word, data_in[i]);
		पूर्ण
	पूर्ण

	/* Initiate xfer, the function will वापस on completion */
	rc = brcmstb_send_i2c_cmd(dev, cmd);

	अगर (rc != 0) अणु
		dev_dbg(dev->device, "%s failure", cmd_string[cmd]);
		वापस rc;
	पूर्ण

	/* Read data from data_out रेजिस्टर */
	अगर (cmd == CMD_RD || cmd == CMD_RD_NOACK) अणु
		क्रम (cnt = 0, i = 0; cnt < len; cnt += data_regsz, i++) अणु
			u32 data = bsc_पढ़ोl(dev, data_out[i]);

			क्रम (byte = 0; byte < data_regsz &&
				     (byte + cnt) < len; byte++) अणु
				buf[cnt + byte] = data & 0xff;
				data >>= BITS_PER_BYTE;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Write a single byte of data to the i2c bus */
अटल पूर्णांक brcmstb_i2c_ग_लिखो_data_byte(काष्ठा brcmstb_i2c_dev *dev,
				       u8 *buf, अचिन्हित पूर्णांक nak_expected)
अणु
	क्रमागत bsc_xfer_cmd cmd = nak_expected ? CMD_WR : CMD_WR_NOACK;

	bsc_ग_लिखोl(dev, 1, cnt_reg);
	bsc_ग_लिखोl(dev, *buf, data_in);

	वापस brcmstb_send_i2c_cmd(dev, cmd);
पूर्ण

/* Send i2c address */
अटल पूर्णांक brcmstb_i2c_करो_addr(काष्ठा brcmstb_i2c_dev *dev,
			       काष्ठा i2c_msg *msg)
अणु
	अचिन्हित अक्षर addr;

	अगर (msg->flags & I2C_M_TEN) अणु
		/* First byte is 11110XX0 where XX is upper 2 bits */
		addr = 0xF0 | ((msg->addr & 0x300) >> 7);
		bsc_ग_लिखोl(dev, addr, chip_address);

		/* Second byte is the reमुख्यing 8 bits */
		addr = msg->addr & 0xFF;
		अगर (brcmstb_i2c_ग_लिखो_data_byte(dev, &addr, 0) < 0)
			वापस -EREMOTEIO;

		अगर (msg->flags & I2C_M_RD) अणु
			/* For पढ़ो, send restart without stop condition */
			brcmstb_set_i2c_start_stop(dev, COND_RESTART
						   | COND_NOSTOP);
			/* Then re-send the first byte with the पढ़ो bit set */
			addr = 0xF0 | ((msg->addr & 0x300) >> 7) | 0x01;
			अगर (brcmstb_i2c_ग_लिखो_data_byte(dev, &addr, 0) < 0)
				वापस -EREMOTEIO;

		पूर्ण
	पूर्ण अन्यथा अणु
		addr = i2c_8bit_addr_from_msg(msg);

		bsc_ग_लिखोl(dev, addr, chip_address);
	पूर्ण

	वापस 0;
पूर्ण

/* Master transfer function */
अटल पूर्णांक brcmstb_i2c_xfer(काष्ठा i2c_adapter *adapter,
			    काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा brcmstb_i2c_dev *dev = i2c_get_adapdata(adapter);
	काष्ठा i2c_msg *pmsg;
	पूर्णांक rc = 0;
	पूर्णांक i;
	पूर्णांक bytes_to_xfer;
	u8 *पंचांगp_buf;
	पूर्णांक len = 0;
	पूर्णांक xfersz = brcmstb_i2c_get_xfersz(dev);
	u32 cond, cond_per_msg;

	/* Loop through all messages */
	क्रम (i = 0; i < num; i++) अणु
		pmsg = &msgs[i];
		len = pmsg->len;
		पंचांगp_buf = pmsg->buf;

		dev_dbg(dev->device,
			"msg# %d/%d flg %x buf %x len %d\n", i,
			num - 1, pmsg->flags,
			pmsg->buf ? pmsg->buf[0] : '0', pmsg->len);

		अगर (i < (num - 1) && (msgs[i + 1].flags & I2C_M_NOSTART))
			cond = ~COND_START_STOP;
		अन्यथा
			cond = COND_RESTART | COND_NOSTOP;

		brcmstb_set_i2c_start_stop(dev, cond);

		/* Send slave address */
		अगर (!(pmsg->flags & I2C_M_NOSTART)) अणु
			rc = brcmstb_i2c_करो_addr(dev, pmsg);
			अगर (rc < 0) अणु
				dev_dbg(dev->device,
					"NACK for addr %2.2x msg#%d rc = %d\n",
					pmsg->addr, i, rc);
				जाओ out;
			पूर्ण
		पूर्ण

		cond_per_msg = cond;

		/* Perक्रमm data transfer */
		जबतक (len) अणु
			bytes_to_xfer = min(len, xfersz);

			अगर (len <= xfersz) अणु
				अगर (i == (num - 1))
					cond_per_msg = cond_per_msg &
						~(COND_RESTART | COND_NOSTOP);
				अन्यथा
					cond_per_msg = cond;
			पूर्ण अन्यथा अणु
				cond_per_msg = (cond_per_msg & ~COND_RESTART) |
					COND_NOSTOP;
			पूर्ण

			brcmstb_set_i2c_start_stop(dev, cond_per_msg);

			rc = brcmstb_i2c_xfer_bsc_data(dev, पंचांगp_buf,
						       bytes_to_xfer, pmsg);
			अगर (rc < 0)
				जाओ out;

			len -=  bytes_to_xfer;
			पंचांगp_buf += bytes_to_xfer;

			cond_per_msg = COND_NOSTART | COND_NOSTOP;
		पूर्ण
	पूर्ण

	rc = num;
out:
	वापस rc;

पूर्ण

अटल u32 brcmstb_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR
		| I2C_FUNC_NOSTART | I2C_FUNC_PROTOCOL_MANGLING;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm brcmstb_i2c_algo = अणु
	.master_xfer = brcmstb_i2c_xfer,
	.functionality = brcmstb_i2c_functionality,
पूर्ण;

अटल व्योम brcmstb_i2c_set_bus_speed(काष्ठा brcmstb_i2c_dev *dev)
अणु
	पूर्णांक i = 0, num_speeds = ARRAY_SIZE(bsc_clk);
	u32 clk_freq_hz = dev->clk_freq_hz;

	क्रम (i = 0; i < num_speeds; i++) अणु
		अगर (bsc_clk[i].hz == clk_freq_hz) अणु
			dev->bsc_regmap->ctl_reg &= ~(BSC_CTL_REG_SCL_SEL_MASK
						| BSC_CTL_REG_DIV_CLK_MASK);
			dev->bsc_regmap->ctl_reg |= (bsc_clk[i].scl_mask |
						     bsc_clk[i].भाग_mask);
			bsc_ग_लिखोl(dev, dev->bsc_regmap->ctl_reg, ctl_reg);
			अवरोध;
		पूर्ण
	पूर्ण

	/* in हाल we did not get find a valid speed */
	अगर (i == num_speeds) अणु
		i = (bsc_पढ़ोl(dev, ctl_reg) & BSC_CTL_REG_SCL_SEL_MASK) >>
			BSC_CTL_REG_SCL_SEL_SHIFT;
		dev_warn(dev->device, "leaving current clock-frequency @ %dHz\n",
			bsc_clk[i].hz);
	पूर्ण
पूर्ण

अटल व्योम brcmstb_i2c_set_bsc_reg_शेषs(काष्ठा brcmstb_i2c_dev *dev)
अणु
	अगर (brcmstb_i2c_get_data_regsz(dev) == माप(u32))
		/* set 4 byte data in/out xfers  */
		dev->bsc_regmap->ctlhi_reg = BSC_CTLHI_REG_DATAREG_SIZE_MASK;
	अन्यथा
		dev->bsc_regmap->ctlhi_reg &= ~BSC_CTLHI_REG_DATAREG_SIZE_MASK;

	bsc_ग_लिखोl(dev, dev->bsc_regmap->ctlhi_reg, ctlhi_reg);
	/* set bus speed */
	brcmstb_i2c_set_bus_speed(dev);
पूर्ण

#घोषणा AUTOI2C_CTRL0		0x26c
#घोषणा AUTOI2C_CTRL0_RELEASE_BSC	BIT(1)

अटल पूर्णांक bcm2711_release_bsc(काष्ठा brcmstb_i2c_dev *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->device);
	काष्ठा resource *iomem;
	व्योम __iomem *स्वतःi2c;

	/* Map hardware रेजिस्टरs */
	iomem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "auto-i2c");
	स्वतःi2c = devm_ioremap_resource(&pdev->dev, iomem);
	अगर (IS_ERR(स्वतःi2c))
		वापस PTR_ERR(स्वतःi2c);

	ग_लिखोl(AUTOI2C_CTRL0_RELEASE_BSC, स्वतःi2c + AUTOI2C_CTRL0);
	devm_iounmap(&pdev->dev, स्वतःi2c);

	/* We need to reset the controller after the release */
	dev->bsc_regmap->iic_enable = 0;
	bsc_ग_लिखोl(dev, dev->bsc_regmap->iic_enable, iic_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc = 0;
	काष्ठा brcmstb_i2c_dev *dev;
	काष्ठा i2c_adapter *adap;
	काष्ठा resource *iomem;
	स्थिर अक्षर *पूर्णांक_name;

	/* Allocate memory क्रम निजी data काष्ठाure */
	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->bsc_regmap = devm_kzalloc(&pdev->dev, माप(*dev->bsc_regmap), GFP_KERNEL);
	अगर (!dev->bsc_regmap)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, dev);
	dev->device = &pdev->dev;
	init_completion(&dev->करोne);

	/* Map hardware रेजिस्टरs */
	iomem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dev->base = devm_ioremap_resource(dev->device, iomem);
	अगर (IS_ERR(dev->base)) अणु
		rc = -ENOMEM;
		जाओ probe_errorout;
	पूर्ण

	अगर (of_device_is_compatible(dev->device->of_node,
				    "brcm,bcm2711-hdmi-i2c")) अणु
		rc = bcm2711_release_bsc(dev);
		अगर (rc)
			जाओ probe_errorout;
	पूर्ण

	rc = of_property_पढ़ो_string(dev->device->of_node, "interrupt-names",
				     &पूर्णांक_name);
	अगर (rc < 0)
		पूर्णांक_name = शून्य;

	/* Get the पूर्णांकerrupt number */
	dev->irq = platक्रमm_get_irq_optional(pdev, 0);

	/* disable the bsc पूर्णांकerrupt line */
	brcmstb_i2c_enable_disable_irq(dev, INT_DISABLE);

	/* रेजिस्टर the ISR handler */
	अगर (dev->irq >= 0) अणु
		rc = devm_request_irq(&pdev->dev, dev->irq, brcmstb_i2c_isr,
				      IRQF_SHARED,
				      पूर्णांक_name ? पूर्णांक_name : pdev->name,
				      dev);

		अगर (rc) अणु
			dev_dbg(dev->device, "falling back to polling mode");
			dev->irq = -1;
		पूर्ण
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->device->of_node,
				 "clock-frequency", &dev->clk_freq_hz)) अणु
		dev_warn(dev->device, "setting clock-frequency@%dHz\n",
			 bsc_clk[0].hz);
		dev->clk_freq_hz = bsc_clk[0].hz;
	पूर्ण

	/* set the data in/out रेजिस्टर size क्रम compatible SoCs */
	अगर (of_device_is_compatible(dev->device->of_node,
				    "brcmstb,brcmper-i2c"))
		dev->data_regsz = माप(u8);
	अन्यथा
		dev->data_regsz = माप(u32);

	brcmstb_i2c_set_bsc_reg_शेषs(dev);

	/* Add the i2c adapter */
	adap = &dev->adapter;
	i2c_set_adapdata(adap, dev);
	adap->owner = THIS_MODULE;
	strlcpy(adap->name, "Broadcom STB : ", माप(adap->name));
	अगर (पूर्णांक_name)
		strlcat(adap->name, पूर्णांक_name, माप(adap->name));
	adap->algo = &brcmstb_i2c_algo;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	rc = i2c_add_adapter(adap);
	अगर (rc)
		जाओ probe_errorout;

	dev_info(dev->device, "%s@%dhz registered in %s mode\n",
		 पूर्णांक_name ? पूर्णांक_name : " ", dev->clk_freq_hz,
		 (dev->irq >= 0) ? "interrupt" : "polling");

	वापस 0;

probe_errorout:
	वापस rc;
पूर्ण

अटल पूर्णांक brcmstb_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा brcmstb_i2c_dev *dev = platक्रमm_get_drvdata(pdev);

	i2c_del_adapter(&dev->adapter);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक brcmstb_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	i2c_mark_adapter_suspended(&i2c_dev->adapter);
	वापस 0;
पूर्ण

अटल पूर्णांक brcmstb_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा brcmstb_i2c_dev *i2c_dev = dev_get_drvdata(dev);

	brcmstb_i2c_set_bsc_reg_शेषs(i2c_dev);
	i2c_mark_adapter_resumed(&i2c_dev->adapter);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(brcmstb_i2c_pm, brcmstb_i2c_suspend,
			 brcmstb_i2c_resume);

अटल स्थिर काष्ठा of_device_id brcmstb_i2c_of_match[] = अणु
	अणु.compatible = "brcm,brcmstb-i2c"पूर्ण,
	अणु.compatible = "brcm,brcmper-i2c"पूर्ण,
	अणु.compatible = "brcm,bcm2711-hdmi-i2c"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, brcmstb_i2c_of_match);

अटल काष्ठा platक्रमm_driver brcmstb_i2c_driver = अणु
	.driver = अणु
		   .name = "brcmstb-i2c",
		   .of_match_table = brcmstb_i2c_of_match,
		   .pm = &brcmstb_i2c_pm,
		   पूर्ण,
	.probe = brcmstb_i2c_probe,
	.हटाओ = brcmstb_i2c_हटाओ,
पूर्ण;
module_platक्रमm_driver(brcmstb_i2c_driver);

MODULE_AUTHOR("Kamal Dasu <kdasu@broadcom.com>");
MODULE_DESCRIPTION("Broadcom Settop I2C Driver");
MODULE_LICENSE("GPL v2");
