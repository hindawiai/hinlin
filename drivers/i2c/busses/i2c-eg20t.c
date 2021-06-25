<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/fs.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/slab.h>

#घोषणा PCH_EVENT_SET	0	/* I2C Interrupt Event Set Status */
#घोषणा PCH_EVENT_NONE	1	/* I2C Interrupt Event Clear Status */
#घोषणा PCH_MAX_CLK		100000	/* Maximum Clock speed in MHz */
#घोषणा PCH_BUFFER_MODE_ENABLE	0x0002	/* flag क्रम Buffer mode enable */
#घोषणा PCH_EEPROM_SW_RST_MODE_ENABLE	0x0008	/* EEPROM SW RST enable flag */

#घोषणा PCH_I2CSADR	0x00	/* I2C slave address रेजिस्टर */
#घोषणा PCH_I2CCTL	0x04	/* I2C control रेजिस्टर */
#घोषणा PCH_I2CSR	0x08	/* I2C status रेजिस्टर */
#घोषणा PCH_I2CDR	0x0C	/* I2C data रेजिस्टर */
#घोषणा PCH_I2CMON	0x10	/* I2C bus monitor रेजिस्टर */
#घोषणा PCH_I2CBC	0x14	/* I2C bus transfer rate setup counter */
#घोषणा PCH_I2CMOD	0x18	/* I2C mode रेजिस्टर */
#घोषणा PCH_I2CBUFSLV	0x1C	/* I2C buffer mode slave address रेजिस्टर */
#घोषणा PCH_I2CBUFSUB	0x20	/* I2C buffer mode subaddress रेजिस्टर */
#घोषणा PCH_I2CBUFFOR	0x24	/* I2C buffer mode क्रमmat रेजिस्टर */
#घोषणा PCH_I2CBUFCTL	0x28	/* I2C buffer mode control रेजिस्टर */
#घोषणा PCH_I2CBUFMSK	0x2C	/* I2C buffer mode पूर्णांकerrupt mask रेजिस्टर */
#घोषणा PCH_I2CBUFSTA	0x30	/* I2C buffer mode status रेजिस्टर */
#घोषणा PCH_I2CBUFLEV	0x34	/* I2C buffer mode level रेजिस्टर */
#घोषणा PCH_I2CESRFOR	0x38	/* EEPROM software reset mode क्रमmat रेजिस्टर */
#घोषणा PCH_I2CESRCTL	0x3C	/* EEPROM software reset mode ctrl रेजिस्टर */
#घोषणा PCH_I2CESRMSK	0x40	/* EEPROM software reset mode */
#घोषणा PCH_I2CESRSTA	0x44	/* EEPROM software reset mode status रेजिस्टर */
#घोषणा PCH_I2CTMR	0x48	/* I2C समयr रेजिस्टर */
#घोषणा PCH_I2CSRST	0xFC	/* I2C reset रेजिस्टर */
#घोषणा PCH_I2CNF	0xF8	/* I2C noise filter रेजिस्टर */

#घोषणा BUS_IDLE_TIMEOUT	20
#घोषणा PCH_I2CCTL_I2CMEN	0x0080
#घोषणा TEN_BIT_ADDR_DEFAULT	0xF000
#घोषणा TEN_BIT_ADDR_MASK	0xF0
#घोषणा PCH_START		0x0020
#घोषणा PCH_RESTART		0x0004
#घोषणा PCH_ESR_START		0x0001
#घोषणा PCH_BUFF_START		0x1
#घोषणा PCH_REPSTART		0x0004
#घोषणा PCH_ACK			0x0008
#घोषणा PCH_GETACK		0x0001
#घोषणा CLR_REG			0x0
#घोषणा I2C_RD			0x1
#घोषणा I2CMCF_BIT		0x0080
#घोषणा I2CMIF_BIT		0x0002
#घोषणा I2CMAL_BIT		0x0010
#घोषणा I2CBMFI_BIT		0x0001
#घोषणा I2CBMAL_BIT		0x0002
#घोषणा I2CBMNA_BIT		0x0004
#घोषणा I2CBMTO_BIT		0x0008
#घोषणा I2CBMIS_BIT		0x0010
#घोषणा I2CESRFI_BIT		0X0001
#घोषणा I2CESRTO_BIT		0x0002
#घोषणा I2CESRFIIE_BIT		0x1
#घोषणा I2CESRTOIE_BIT		0x2
#घोषणा I2CBMDZ_BIT		0x0040
#घोषणा I2CBMAG_BIT		0x0020
#घोषणा I2CMBB_BIT		0x0020
#घोषणा BUFFER_MODE_MASK	(I2CBMFI_BIT | I2CBMAL_BIT | I2CBMNA_BIT | \
				I2CBMTO_BIT | I2CBMIS_BIT)
#घोषणा I2C_ADDR_MSK		0xFF
#घोषणा I2C_MSB_2B_MSK		0x300
#घोषणा FAST_MODE_CLK		400
#घोषणा FAST_MODE_EN		0x0001
#घोषणा SUB_ADDR_LEN_MAX	4
#घोषणा BUF_LEN_MAX		32
#घोषणा PCH_BUFFER_MODE		0x1
#घोषणा EEPROM_SW_RST_MODE	0x0002
#घोषणा NORMAL_INTR_ENBL	0x0300
#घोषणा EEPROM_RST_INTR_ENBL	(I2CESRFIIE_BIT | I2CESRTOIE_BIT)
#घोषणा EEPROM_RST_INTR_DISBL	0x0
#घोषणा BUFFER_MODE_INTR_ENBL	0x001F
#घोषणा BUFFER_MODE_INTR_DISBL	0x0
#घोषणा NORMAL_MODE		0x0
#घोषणा BUFFER_MODE		0x1
#घोषणा EEPROM_SR_MODE		0x2
#घोषणा I2C_TX_MODE		0x0010
#घोषणा PCH_BUF_TX		0xFFF7
#घोषणा PCH_BUF_RD		0x0008
#घोषणा I2C_ERROR_MASK	(I2CESRTO_EVENT | I2CBMIS_EVENT | I2CBMTO_EVENT | \
			I2CBMNA_EVENT | I2CBMAL_EVENT | I2CMAL_EVENT)
#घोषणा I2CMAL_EVENT		0x0001
#घोषणा I2CMCF_EVENT		0x0002
#घोषणा I2CBMFI_EVENT		0x0004
#घोषणा I2CBMAL_EVENT		0x0008
#घोषणा I2CBMNA_EVENT		0x0010
#घोषणा I2CBMTO_EVENT		0x0020
#घोषणा I2CBMIS_EVENT		0x0040
#घोषणा I2CESRFI_EVENT		0x0080
#घोषणा I2CESRTO_EVENT		0x0100
#घोषणा PCI_DEVICE_ID_PCH_I2C	0x8817

#घोषणा pch_dbg(adap, fmt, arg...)  \
	dev_dbg(adap->pch_adapter.dev.parent, "%s :" fmt, __func__, ##arg)

#घोषणा pch_err(adap, fmt, arg...)  \
	dev_err(adap->pch_adapter.dev.parent, "%s :" fmt, __func__, ##arg)

#घोषणा pch_pci_err(pdev, fmt, arg...)  \
	dev_err(&pdev->dev, "%s :" fmt, __func__, ##arg)

#घोषणा pch_pci_dbg(pdev, fmt, arg...)  \
	dev_dbg(&pdev->dev, "%s :" fmt, __func__, ##arg)

/*
Set the number of I2C instance max
Intel EG20T PCH :		1ch
LAPIS Semiconductor ML7213 IOH :	2ch
LAPIS Semiconductor ML7831 IOH :	1ch
*/
#घोषणा PCH_I2C_MAX_DEV			2

/**
 * काष्ठा i2c_algo_pch_data - क्रम I2C driver functionalities
 * @pch_adapter:		stores the reference to i2c_adapter काष्ठाure
 * @p_adapter_info:		stores the reference to adapter_info काष्ठाure
 * @pch_base_address:		specअगरies the remapped base address
 * @pch_buff_mode_en:		specअगरies अगर buffer mode is enabled
 * @pch_event_flag:		specअगरies occurrence of पूर्णांकerrupt events
 * @pch_i2c_xfer_in_progress:	specअगरies whether the transfer is completed
 */
काष्ठा i2c_algo_pch_data अणु
	काष्ठा i2c_adapter pch_adapter;
	काष्ठा adapter_info *p_adapter_info;
	व्योम __iomem *pch_base_address;
	पूर्णांक pch_buff_mode_en;
	u32 pch_event_flag;
	bool pch_i2c_xfer_in_progress;
पूर्ण;

/**
 * काष्ठा adapter_info - This काष्ठाure holds the adapter inक्रमmation क्रम the
 *			 PCH i2c controller
 * @pch_data:		stores a list of i2c_algo_pch_data
 * @pch_i2c_suspended:	specअगरies whether the प्रणाली is suspended or not
 *			perhaps with more lines and words.
 * @ch_num:		specअगरies the number of i2c instance
 *
 * pch_data has as many elements as maximum I2C channels
 */
काष्ठा adapter_info अणु
	काष्ठा i2c_algo_pch_data pch_data[PCH_I2C_MAX_DEV];
	bool pch_i2c_suspended;
	पूर्णांक ch_num;
पूर्ण;


अटल पूर्णांक pch_i2c_speed = 100; /* I2C bus speed in Kbps */
अटल पूर्णांक pch_clk = 50000;	/* specअगरies I2C घड़ी speed in KHz */
अटल रुको_queue_head_t pch_event;
अटल DEFINE_MUTEX(pch_mutex);

/* Definition क्रम ML7213 by LAPIS Semiconductor */
#घोषणा PCI_DEVICE_ID_ML7213_I2C	0x802D
#घोषणा PCI_DEVICE_ID_ML7223_I2C	0x8010
#घोषणा PCI_DEVICE_ID_ML7831_I2C	0x8817

अटल स्थिर काष्ठा pci_device_id pch_pcidev_id[] = अणु
	अणु PCI_VDEVICE(INTEL, PCI_DEVICE_ID_PCH_I2C),   1, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7213_I2C), 2, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7223_I2C), 1, पूर्ण,
	अणु PCI_VDEVICE(ROHM, PCI_DEVICE_ID_ML7831_I2C), 1, पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pch_pcidev_id);

अटल irqवापस_t pch_i2c_handler(पूर्णांक irq, व्योम *pData);

अटल अंतरभूत व्योम pch_setbit(व्योम __iomem *addr, u32 offset, u32 biपंचांगask)
अणु
	u32 val;
	val = ioपढ़ो32(addr + offset);
	val |= biपंचांगask;
	ioग_लिखो32(val, addr + offset);
पूर्ण

अटल अंतरभूत व्योम pch_clrbit(व्योम __iomem *addr, u32 offset, u32 biपंचांगask)
अणु
	u32 val;
	val = ioपढ़ो32(addr + offset);
	val &= (~biपंचांगask);
	ioग_लिखो32(val, addr + offset);
पूर्ण

/**
 * pch_i2c_init() - hardware initialization of I2C module
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_init(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	u32 pch_i2cbc;
	u32 pch_i2cपंचांगr;
	u32 reg_value;

	/* reset I2C controller */
	ioग_लिखो32(0x01, p + PCH_I2CSRST);
	msleep(20);
	ioग_लिखो32(0x0, p + PCH_I2CSRST);

	/* Initialize I2C रेजिस्टरs */
	ioग_लिखो32(0x21, p + PCH_I2CNF);

	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_I2CCTL_I2CMEN);

	अगर (pch_i2c_speed != 400)
		pch_i2c_speed = 100;

	reg_value = PCH_I2CCTL_I2CMEN;
	अगर (pch_i2c_speed == FAST_MODE_CLK) अणु
		reg_value |= FAST_MODE_EN;
		pch_dbg(adap, "Fast mode enabled\n");
	पूर्ण

	अगर (pch_clk > PCH_MAX_CLK)
		pch_clk = 62500;

	pch_i2cbc = (pch_clk + (pch_i2c_speed * 4)) / (pch_i2c_speed * 8);
	/* Set transfer speed in I2CBC */
	ioग_लिखो32(pch_i2cbc, p + PCH_I2CBC);

	pch_i2cपंचांगr = (pch_clk) / 8;
	ioग_लिखो32(pch_i2cपंचांगr, p + PCH_I2CTMR);

	reg_value |= NORMAL_INTR_ENBL;	/* Enable पूर्णांकerrupts in normal mode */
	ioग_लिखो32(reg_value, p + PCH_I2CCTL);

	pch_dbg(adap,
		"I2CCTL=%x pch_i2cbc=%x pch_i2ctmr=%x Enable interrupts\n",
		ioपढ़ो32(p + PCH_I2CCTL), pch_i2cbc, pch_i2cपंचांगr);

	init_रुकोqueue_head(&pch_event);
पूर्ण

/**
 * pch_i2c_रुको_क्रम_bus_idle() - check the status of bus.
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 * @समयout:	रुकोing समय counter (ms).
 */
अटल s32 pch_i2c_रुको_क्रम_bus_idle(काष्ठा i2c_algo_pch_data *adap,
				     s32 समयout)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	पूर्णांक schedule = 0;
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(समयout);

	जबतक (ioपढ़ो32(p + PCH_I2CSR) & I2CMBB_BIT) अणु
		अगर (समय_after(jअगरfies, end)) अणु
			pch_dbg(adap, "I2CSR = %x\n", ioपढ़ो32(p + PCH_I2CSR));
			pch_err(adap, "%s: Timeout Error.return%d\n",
					__func__, -ETIME);
			pch_i2c_init(adap);

			वापस -ETIME;
		पूर्ण

		अगर (!schedule)
			/* Retry after some usecs */
			udelay(5);
		अन्यथा
			/* Wait a bit more without consuming CPU */
			usleep_range(20, 1000);

		schedule = 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pch_i2c_start() - Generate I2C start condition in normal mode.
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 *
 * Generate I2C start condition in normal mode by setting I2CCTL.I2CMSTA to 1.
 */
अटल व्योम pch_i2c_start(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_START);
पूर्ण

/**
 * pch_i2c_stop() - generate stop condition in normal mode.
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_stop(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	/* clear the start bit */
	pch_clrbit(adap->pch_base_address, PCH_I2CCTL, PCH_START);
पूर्ण

अटल पूर्णांक pch_i2c_रुको_क्रम_check_xfer(काष्ठा i2c_algo_pch_data *adap)
अणु
	दीर्घ ret;
	व्योम __iomem *p = adap->pch_base_address;

	ret = रुको_event_समयout(pch_event,
			(adap->pch_event_flag != 0), msecs_to_jअगरfies(1000));
	अगर (!ret) अणु
		pch_err(adap, "%s:wait-event timeout\n", __func__);
		adap->pch_event_flag = 0;
		pch_i2c_stop(adap);
		pch_i2c_init(adap);
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (adap->pch_event_flag & I2C_ERROR_MASK) अणु
		pch_err(adap, "Lost Arbitration\n");
		adap->pch_event_flag = 0;
		pch_clrbit(adap->pch_base_address, PCH_I2CSR, I2CMAL_BIT);
		pch_clrbit(adap->pch_base_address, PCH_I2CSR, I2CMIF_BIT);
		pch_i2c_init(adap);
		वापस -EAGAIN;
	पूर्ण

	adap->pch_event_flag = 0;

	अगर (ioपढ़ो32(p + PCH_I2CSR) & PCH_GETACK) अणु
		pch_dbg(adap, "Receive NACK for slave address setting\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * pch_i2c_repstart() - generate repeated start condition in normal mode
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_repstart(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_REPSTART);
पूर्ण

/**
 * pch_i2c_ग_लिखोbytes() - ग_लिखो data to I2C bus in normal mode
 * @i2c_adap:	Poपूर्णांकer to the काष्ठा i2c_adapter.
 * @msgs:	Poपूर्णांकer to the i2c message काष्ठाure.
 * @last:	specअगरies whether last message or not.
 *		In the हाल of compound mode it will be 1 क्रम last message,
 *		otherwise 0.
 * @first:	specअगरies whether first message or not.
 *		1 क्रम first message otherwise 0.
 */
अटल s32 pch_i2c_ग_लिखोbytes(काष्ठा i2c_adapter *i2c_adap,
			      काष्ठा i2c_msg *msgs, u32 last, u32 first)
अणु
	काष्ठा i2c_algo_pch_data *adap = i2c_adap->algo_data;
	u8 *buf;
	u32 length;
	u32 addr;
	u32 addr_2_msb;
	u32 addr_8_lsb;
	s32 wrcount;
	s32 rtn;
	व्योम __iomem *p = adap->pch_base_address;

	length = msgs->len;
	buf = msgs->buf;
	addr = msgs->addr;

	/* enable master tx */
	pch_setbit(adap->pch_base_address, PCH_I2CCTL, I2C_TX_MODE);

	pch_dbg(adap, "I2CCTL = %x msgs->len = %d\n", ioपढ़ो32(p + PCH_I2CCTL),
		length);

	अगर (first) अणु
		अगर (pch_i2c_रुको_क्रम_bus_idle(adap, BUS_IDLE_TIMEOUT) == -ETIME)
			वापस -ETIME;
	पूर्ण

	अगर (msgs->flags & I2C_M_TEN) अणु
		addr_2_msb = ((addr & I2C_MSB_2B_MSK) >> 7) & 0x06;
		ioग_लिखो32(addr_2_msb | TEN_BIT_ADDR_MASK, p + PCH_I2CDR);
		अगर (first)
			pch_i2c_start(adap);

		rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
		अगर (rtn)
			वापस rtn;

		addr_8_lsb = (addr & I2C_ADDR_MSK);
		ioग_लिखो32(addr_8_lsb, p + PCH_I2CDR);
	पूर्ण अन्यथा अणु
		/* set 7 bit slave address and R/W bit as 0 */
		ioग_लिखो32(i2c_8bit_addr_from_msg(msgs), p + PCH_I2CDR);
		अगर (first)
			pch_i2c_start(adap);
	पूर्ण

	rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
	अगर (rtn)
		वापस rtn;

	क्रम (wrcount = 0; wrcount < length; ++wrcount) अणु
		/* ग_लिखो buffer value to I2C data रेजिस्टर */
		ioग_लिखो32(buf[wrcount], p + PCH_I2CDR);
		pch_dbg(adap, "writing %x to Data register\n", buf[wrcount]);

		rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
		अगर (rtn)
			वापस rtn;

		pch_clrbit(adap->pch_base_address, PCH_I2CSR, I2CMCF_BIT);
		pch_clrbit(adap->pch_base_address, PCH_I2CSR, I2CMIF_BIT);
	पूर्ण

	/* check अगर this is the last message */
	अगर (last)
		pch_i2c_stop(adap);
	अन्यथा
		pch_i2c_repstart(adap);

	pch_dbg(adap, "return=%d\n", wrcount);

	वापस wrcount;
पूर्ण

/**
 * pch_i2c_sendack() - send ACK
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_sendack(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	pch_clrbit(adap->pch_base_address, PCH_I2CCTL, PCH_ACK);
पूर्ण

/**
 * pch_i2c_sendnack() - send NACK
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_sendnack(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_ACK);
पूर्ण

/**
 * pch_i2c_restart() - Generate I2C restart condition in normal mode.
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 *
 * Generate I2C restart condition in normal mode by setting I2CCTL.I2CRSTA.
 */
अटल व्योम pch_i2c_restart(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;
	pch_dbg(adap, "I2CCTL = %x\n", ioपढ़ो32(p + PCH_I2CCTL));
	pch_setbit(adap->pch_base_address, PCH_I2CCTL, PCH_RESTART);
पूर्ण

/**
 * pch_i2c_पढ़ोbytes() - पढ़ो data  from I2C bus in normal mode.
 * @i2c_adap:	Poपूर्णांकer to the काष्ठा i2c_adapter.
 * @msgs:	Poपूर्णांकer to i2c_msg काष्ठाure.
 * @last:	specअगरies whether last message or not.
 * @first:	specअगरies whether first message or not.
 */
अटल s32 pch_i2c_पढ़ोbytes(काष्ठा i2c_adapter *i2c_adap, काष्ठा i2c_msg *msgs,
			     u32 last, u32 first)
अणु
	काष्ठा i2c_algo_pch_data *adap = i2c_adap->algo_data;

	u8 *buf;
	u32 count;
	u32 length;
	u32 addr;
	u32 addr_2_msb;
	u32 addr_8_lsb;
	व्योम __iomem *p = adap->pch_base_address;
	s32 rtn;

	length = msgs->len;
	buf = msgs->buf;
	addr = msgs->addr;

	/* enable master reception */
	pch_clrbit(adap->pch_base_address, PCH_I2CCTL, I2C_TX_MODE);

	अगर (first) अणु
		अगर (pch_i2c_रुको_क्रम_bus_idle(adap, BUS_IDLE_TIMEOUT) == -ETIME)
			वापस -ETIME;
	पूर्ण

	अगर (msgs->flags & I2C_M_TEN) अणु
		addr_2_msb = ((addr & I2C_MSB_2B_MSK) >> 7);
		ioग_लिखो32(addr_2_msb | TEN_BIT_ADDR_MASK, p + PCH_I2CDR);
		अगर (first)
			pch_i2c_start(adap);

		rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
		अगर (rtn)
			वापस rtn;

		addr_8_lsb = (addr & I2C_ADDR_MSK);
		ioग_लिखो32(addr_8_lsb, p + PCH_I2CDR);

		pch_i2c_restart(adap);

		rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
		अगर (rtn)
			वापस rtn;

		addr_2_msb |= I2C_RD;
		ioग_लिखो32(addr_2_msb | TEN_BIT_ADDR_MASK, p + PCH_I2CDR);
	पूर्ण अन्यथा अणु
		/* 7 address bits + R/W bit */
		ioग_लिखो32(i2c_8bit_addr_from_msg(msgs), p + PCH_I2CDR);
	पूर्ण

	/* check अगर it is the first message */
	अगर (first)
		pch_i2c_start(adap);

	rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
	अगर (rtn)
		वापस rtn;

	अगर (length == 0) अणु
		pch_i2c_stop(adap);
		ioपढ़ो32(p + PCH_I2CDR); /* Dummy पढ़ो needs */

		count = length;
	पूर्ण अन्यथा अणु
		पूर्णांक पढ़ो_index;
		पूर्णांक loop;
		pch_i2c_sendack(adap);

		/* Dummy पढ़ो */
		क्रम (loop = 1, पढ़ो_index = 0; loop < length; loop++) अणु
			buf[पढ़ो_index] = ioपढ़ो32(p + PCH_I2CDR);

			अगर (loop != 1)
				पढ़ो_index++;

			rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
			अगर (rtn)
				वापस rtn;
		पूर्ण	/* end क्रम */

		pch_i2c_sendnack(adap);

		buf[पढ़ो_index] = ioपढ़ो32(p + PCH_I2CDR); /* Read final - 1 */

		अगर (length != 1)
			पढ़ो_index++;

		rtn = pch_i2c_रुको_क्रम_check_xfer(adap);
		अगर (rtn)
			वापस rtn;

		अगर (last)
			pch_i2c_stop(adap);
		अन्यथा
			pch_i2c_repstart(adap);

		buf[पढ़ो_index++] = ioपढ़ो32(p + PCH_I2CDR); /* Read Final */
		count = पढ़ो_index;
	पूर्ण

	वापस count;
पूर्ण

/**
 * pch_i2c_cb() - Interrupt handler Call back function
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_cb(काष्ठा i2c_algo_pch_data *adap)
अणु
	u32 sts;
	व्योम __iomem *p = adap->pch_base_address;

	sts = ioपढ़ो32(p + PCH_I2CSR);
	sts &= (I2CMAL_BIT | I2CMCF_BIT | I2CMIF_BIT);
	अगर (sts & I2CMAL_BIT)
		adap->pch_event_flag |= I2CMAL_EVENT;

	अगर (sts & I2CMCF_BIT)
		adap->pch_event_flag |= I2CMCF_EVENT;

	/* clear the applicable bits */
	pch_clrbit(adap->pch_base_address, PCH_I2CSR, sts);

	pch_dbg(adap, "PCH_I2CSR = %x\n", ioपढ़ो32(p + PCH_I2CSR));

	wake_up(&pch_event);
पूर्ण

/**
 * pch_i2c_handler() - पूर्णांकerrupt handler क्रम the PCH I2C controller
 * @irq:	irq number.
 * @pData:	cookie passed back to the handler function.
 */
अटल irqवापस_t pch_i2c_handler(पूर्णांक irq, व्योम *pData)
अणु
	u32 reg_val;
	पूर्णांक flag;
	पूर्णांक i;
	काष्ठा adapter_info *adap_info = pData;
	व्योम __iomem *p;
	u32 mode;

	क्रम (i = 0, flag = 0; i < adap_info->ch_num; i++) अणु
		p = adap_info->pch_data[i].pch_base_address;
		mode = ioपढ़ो32(p + PCH_I2CMOD);
		mode &= BUFFER_MODE | EEPROM_SR_MODE;
		अगर (mode != NORMAL_MODE) अणु
			pch_err(adap_info->pch_data,
				"I2C-%d mode(%d) is not supported\n", mode, i);
			जारी;
		पूर्ण
		reg_val = ioपढ़ो32(p + PCH_I2CSR);
		अगर (reg_val & (I2CMAL_BIT | I2CMCF_BIT | I2CMIF_BIT)) अणु
			pch_i2c_cb(&adap_info->pch_data[i]);
			flag = 1;
		पूर्ण
	पूर्ण

	वापस flag ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/**
 * pch_i2c_xfer() - Reading adnd writing data through I2C bus
 * @i2c_adap:	Poपूर्णांकer to the काष्ठा i2c_adapter.
 * @msgs:	Poपूर्णांकer to i2c_msg काष्ठाure.
 * @num:	number of messages.
 */
अटल s32 pch_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			काष्ठा i2c_msg *msgs, s32 num)
अणु
	काष्ठा i2c_msg *pmsg;
	u32 i = 0;
	u32 status;
	s32 ret;

	काष्ठा i2c_algo_pch_data *adap = i2c_adap->algo_data;

	ret = mutex_lock_पूर्णांकerruptible(&pch_mutex);
	अगर (ret)
		वापस ret;

	अगर (adap->p_adapter_info->pch_i2c_suspended) अणु
		mutex_unlock(&pch_mutex);
		वापस -EBUSY;
	पूर्ण

	pch_dbg(adap, "adap->p_adapter_info->pch_i2c_suspended is %d\n",
		adap->p_adapter_info->pch_i2c_suspended);
	/* transfer not completed */
	adap->pch_i2c_xfer_in_progress = true;

	क्रम (i = 0; i < num && ret >= 0; i++) अणु
		pmsg = &msgs[i];
		pmsg->flags |= adap->pch_buff_mode_en;
		status = pmsg->flags;
		pch_dbg(adap,
			"After invoking I2C_MODE_SEL :flag= 0x%x\n", status);

		अगर ((status & (I2C_M_RD)) != false) अणु
			ret = pch_i2c_पढ़ोbytes(i2c_adap, pmsg, (i + 1 == num),
						(i == 0));
		पूर्ण अन्यथा अणु
			ret = pch_i2c_ग_लिखोbytes(i2c_adap, pmsg, (i + 1 == num),
						 (i == 0));
		पूर्ण
	पूर्ण

	adap->pch_i2c_xfer_in_progress = false;	/* transfer completed */

	mutex_unlock(&pch_mutex);

	वापस (ret < 0) ? ret : num;
पूर्ण

/**
 * pch_i2c_func() - वापस the functionality of the I2C driver
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल u32 pch_i2c_func(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL | I2C_FUNC_10BIT_ADDR;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm pch_algorithm = अणु
	.master_xfer = pch_i2c_xfer,
	.functionality = pch_i2c_func
पूर्ण;

/**
 * pch_i2c_disbl_पूर्णांक() - Disable PCH I2C पूर्णांकerrupts
 * @adap:	Poपूर्णांकer to काष्ठा i2c_algo_pch_data.
 */
अटल व्योम pch_i2c_disbl_पूर्णांक(काष्ठा i2c_algo_pch_data *adap)
अणु
	व्योम __iomem *p = adap->pch_base_address;

	pch_clrbit(adap->pch_base_address, PCH_I2CCTL, NORMAL_INTR_ENBL);

	ioग_लिखो32(EEPROM_RST_INTR_DISBL, p + PCH_I2CESRMSK);

	ioग_लिखो32(BUFFER_MODE_INTR_DISBL, p + PCH_I2CBUFMSK);
पूर्ण

अटल पूर्णांक pch_i2c_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	व्योम __iomem *base_addr;
	पूर्णांक ret;
	पूर्णांक i, j;
	काष्ठा adapter_info *adap_info;
	काष्ठा i2c_adapter *pch_adap;

	pch_pci_dbg(pdev, "Entered.\n");

	adap_info = kzalloc((माप(काष्ठा adapter_info)), GFP_KERNEL);
	अगर (adap_info == शून्य)
		वापस -ENOMEM;

	ret = pci_enable_device(pdev);
	अगर (ret) अणु
		pch_pci_err(pdev, "pci_enable_device FAILED\n");
		जाओ err_pci_enable;
	पूर्ण

	ret = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (ret) अणु
		pch_pci_err(pdev, "pci_request_regions FAILED\n");
		जाओ err_pci_req;
	पूर्ण

	base_addr = pci_iomap(pdev, 1, 0);

	अगर (base_addr == शून्य) अणु
		pch_pci_err(pdev, "pci_iomap FAILED\n");
		ret = -ENOMEM;
		जाओ err_pci_iomap;
	पूर्ण

	/* Set the number of I2C channel instance */
	adap_info->ch_num = id->driver_data;

	क्रम (i = 0; i < adap_info->ch_num; i++) अणु
		pch_adap = &adap_info->pch_data[i].pch_adapter;
		adap_info->pch_i2c_suspended = false;

		adap_info->pch_data[i].p_adapter_info = adap_info;

		pch_adap->owner = THIS_MODULE;
		pch_adap->class = I2C_CLASS_HWMON;
		strlcpy(pch_adap->name, KBUILD_MODNAME, माप(pch_adap->name));
		pch_adap->algo = &pch_algorithm;
		pch_adap->algo_data = &adap_info->pch_data[i];

		/* base_addr + offset; */
		adap_info->pch_data[i].pch_base_address = base_addr + 0x100 * i;

		pch_adap->dev.of_node = pdev->dev.of_node;
		pch_adap->dev.parent = &pdev->dev;
	पूर्ण

	ret = request_irq(pdev->irq, pch_i2c_handler, IRQF_SHARED,
		  KBUILD_MODNAME, adap_info);
	अगर (ret) अणु
		pch_pci_err(pdev, "request_irq FAILED\n");
		जाओ err_request_irq;
	पूर्ण

	क्रम (i = 0; i < adap_info->ch_num; i++) अणु
		pch_adap = &adap_info->pch_data[i].pch_adapter;

		pch_i2c_init(&adap_info->pch_data[i]);

		pch_adap->nr = i;
		ret = i2c_add_numbered_adapter(pch_adap);
		अगर (ret) अणु
			pch_pci_err(pdev, "i2c_add_adapter[ch:%d] FAILED\n", i);
			जाओ err_add_adapter;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, adap_info);
	pch_pci_dbg(pdev, "returns %d.\n", ret);
	वापस 0;

err_add_adapter:
	क्रम (j = 0; j < i; j++)
		i2c_del_adapter(&adap_info->pch_data[j].pch_adapter);
	मुक्त_irq(pdev->irq, adap_info);
err_request_irq:
	pci_iounmap(pdev, base_addr);
err_pci_iomap:
	pci_release_regions(pdev);
err_pci_req:
	pci_disable_device(pdev);
err_pci_enable:
	kमुक्त(adap_info);
	वापस ret;
पूर्ण

अटल व्योम pch_i2c_हटाओ(काष्ठा pci_dev *pdev)
अणु
	पूर्णांक i;
	काष्ठा adapter_info *adap_info = pci_get_drvdata(pdev);

	मुक्त_irq(pdev->irq, adap_info);

	क्रम (i = 0; i < adap_info->ch_num; i++) अणु
		pch_i2c_disbl_पूर्णांक(&adap_info->pch_data[i]);
		i2c_del_adapter(&adap_info->pch_data[i].pch_adapter);
	पूर्ण

	अगर (adap_info->pch_data[0].pch_base_address)
		pci_iounmap(pdev, adap_info->pch_data[0].pch_base_address);

	क्रम (i = 0; i < adap_info->ch_num; i++)
		adap_info->pch_data[i].pch_base_address = शून्य;

	pci_release_regions(pdev);

	pci_disable_device(pdev);
	kमुक्त(adap_info);
पूर्ण

अटल पूर्णांक __maybe_unused pch_i2c_suspend(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा adapter_info *adap_info = pci_get_drvdata(pdev);
	व्योम __iomem *p = adap_info->pch_data[0].pch_base_address;

	adap_info->pch_i2c_suspended = true;

	क्रम (i = 0; i < adap_info->ch_num; i++) अणु
		जबतक ((adap_info->pch_data[i].pch_i2c_xfer_in_progress)) अणु
			/* Wait until all channel transfers are completed */
			msleep(20);
		पूर्ण
	पूर्ण

	/* Disable the i2c पूर्णांकerrupts */
	क्रम (i = 0; i < adap_info->ch_num; i++)
		pch_i2c_disbl_पूर्णांक(&adap_info->pch_data[i]);

	pch_pci_dbg(pdev, "I2CSR = %x I2CBUFSTA = %x I2CESRSTA = %x "
		"invoked function pch_i2c_disbl_int successfully\n",
		ioपढ़ो32(p + PCH_I2CSR), ioपढ़ो32(p + PCH_I2CBUFSTA),
		ioपढ़ो32(p + PCH_I2CESRSTA));

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_i2c_resume(काष्ठा device *dev)
अणु
	पूर्णांक i;
	काष्ठा adapter_info *adap_info = dev_get_drvdata(dev);

	क्रम (i = 0; i < adap_info->ch_num; i++)
		pch_i2c_init(&adap_info->pch_data[i]);

	adap_info->pch_i2c_suspended = false;

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_i2c_pm_ops, pch_i2c_suspend, pch_i2c_resume);

अटल काष्ठा pci_driver pch_pcidriver = अणु
	.name = KBUILD_MODNAME,
	.id_table = pch_pcidev_id,
	.probe = pch_i2c_probe,
	.हटाओ = pch_i2c_हटाओ,
	.driver.pm = &pch_i2c_pm_ops,
पूर्ण;

module_pci_driver(pch_pcidriver);

MODULE_DESCRIPTION("Intel EG20T PCH/LAPIS Semico ML7213/ML7223/ML7831 IOH I2C");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tomoya MORINAGA. <tomoya.rohm@gmail.com>");
module_param(pch_i2c_speed, पूर्णांक, (S_IRUSR | S_IWUSR));
module_param(pch_clk, पूर्णांक, (S_IRUSR | S_IWUSR));
