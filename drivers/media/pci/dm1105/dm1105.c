<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dm1105.c - driver क्रम DVB cards based on SDMC DM1105 PCI chip
 *
 * Copyright (C) 2008 Igor M. Liplianin <liplianin@me.by>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>

#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>
#समावेश "dvb-pll.h"

#समावेश "stv0299.h"
#समावेश "stv0288.h"
#समावेश "stb6000.h"
#समावेश "si21xx.h"
#समावेश "cx24116.h"
#समावेश "z0194a.h"
#समावेश "ts2020.h"
#समावेश "ds3000.h"

#घोषणा MODULE_NAME "dm1105"

#घोषणा UNSET (-1U)

#घोषणा DM1105_BOARD_NOAUTO			UNSET
#घोषणा DM1105_BOARD_UNKNOWN			0
#घोषणा DM1105_BOARD_DVBWORLD_2002		1
#घोषणा DM1105_BOARD_DVBWORLD_2004		2
#घोषणा DM1105_BOARD_AXESS_DM05			3
#घोषणा DM1105_BOARD_UNBRANDED_I2C_ON_GPIO	4

/* ----------------------------------------------- */
/*
 * PCI ID's
 */
#अगर_अघोषित PCI_VENDOR_ID_TRIGEM
#घोषणा PCI_VENDOR_ID_TRIGEM	0x109f
#पूर्ण_अगर
#अगर_अघोषित PCI_VENDOR_ID_AXESS
#घोषणा PCI_VENDOR_ID_AXESS	0x195d
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_DM1105
#घोषणा PCI_DEVICE_ID_DM1105	0x036f
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_DW2002
#घोषणा PCI_DEVICE_ID_DW2002	0x2002
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_DW2004
#घोषणा PCI_DEVICE_ID_DW2004	0x2004
#पूर्ण_अगर
#अगर_अघोषित PCI_DEVICE_ID_DM05
#घोषणा PCI_DEVICE_ID_DM05	0x1105
#पूर्ण_अगर
/* ----------------------------------------------- */
/* sdmc dm1105 रेजिस्टरs */

/* TS Control */
#घोषणा DM1105_TSCTR				0x00
#घोषणा DM1105_DTALENTH				0x04

/* GPIO Interface */
#घोषणा DM1105_GPIOVAL				0x08
#घोषणा DM1105_GPIOCTR				0x0c

/* PID serial number */
#घोषणा DM1105_PIDN				0x10

/* Odd-even secret key select */
#घोषणा DM1105_CWSEL				0x14

/* Host Command Interface */
#घोषणा DM1105_HOST_CTR				0x18
#घोषणा DM1105_HOST_AD				0x1c

/* PCI Interface */
#घोषणा DM1105_CR				0x30
#घोषणा DM1105_RST				0x34
#घोषणा DM1105_STADR				0x38
#घोषणा DM1105_RLEN				0x3c
#घोषणा DM1105_WRP				0x40
#घोषणा DM1105_INTCNT				0x44
#घोषणा DM1105_INTMAK				0x48
#घोषणा DM1105_INTSTS				0x4c

/* CW Value */
#घोषणा DM1105_ODD				0x50
#घोषणा DM1105_EVEN				0x58

/* PID Value */
#घोषणा DM1105_PID				0x60

/* IR Control */
#घोषणा DM1105_IRCTR				0x64
#घोषणा DM1105_IRMODE				0x68
#घोषणा DM1105_SYSTEMCODE			0x6c
#घोषणा DM1105_IRCODE				0x70

/* Unknown Values */
#घोषणा DM1105_ENCRYPT				0x74
#घोषणा DM1105_VER				0x7c

/* I2C Interface */
#घोषणा DM1105_I2CCTR				0x80
#घोषणा DM1105_I2CSTS				0x81
#घोषणा DM1105_I2CDAT				0x82
#घोषणा DM1105_I2C_RA				0x83
/* ----------------------------------------------- */
/* Interrupt Mask Bits */

#घोषणा INTMAK_TSIRQM				0x01
#घोषणा INTMAK_HIRQM				0x04
#घोषणा INTMAK_IRM				0x08
#घोषणा INTMAK_ALLMASK				(INTMAK_TSIRQM | \
						INTMAK_HIRQM | \
						INTMAK_IRM)
#घोषणा INTMAK_NONEMASK				0x00

/* Interrupt Status Bits */
#घोषणा INTSTS_TSIRQ				0x01
#घोषणा INTSTS_HIRQ				0x04
#घोषणा INTSTS_IR				0x08

/* IR Control Bits */
#घोषणा DM1105_IR_EN				0x01
#घोषणा DM1105_SYS_CHK				0x02
#घोषणा DM1105_REP_FLG				0x08

/* EEPROM addr */
#घोषणा IIC_24C01_addr				0xa0
/* Max board count */
#घोषणा DM1105_MAX				0x04

#घोषणा DRIVER_NAME				"dm1105"
#घोषणा DM1105_I2C_GPIO_NAME			"dm1105-gpio"

#घोषणा DM1105_DMA_PACKETS			47
#घोषणा DM1105_DMA_PACKET_LENGTH		(128*4)
#घोषणा DM1105_DMA_BYTES			(128 * 4 * DM1105_DMA_PACKETS)

/*  */
#घोषणा GPIO08					(1 << 8)
#घोषणा GPIO13					(1 << 13)
#घोषणा GPIO14					(1 << 14)
#घोषणा GPIO15					(1 << 15)
#घोषणा GPIO16					(1 << 16)
#घोषणा GPIO17					(1 << 17)
#घोषणा GPIO_ALL				0x03ffff

/* GPIO's क्रम LNB घातer control */
#घोषणा DM1105_LNB_MASK				(GPIO_ALL & ~(GPIO14 | GPIO13))
#घोषणा DM1105_LNB_OFF				GPIO17
#घोषणा DM1105_LNB_13V				(GPIO16 | GPIO08)
#घोषणा DM1105_LNB_18V				GPIO08

/* GPIO's क्रम LNB घातer control क्रम Axess DM05 */
#घोषणा DM05_LNB_MASK				(GPIO_ALL & ~(GPIO14 | GPIO13))
#घोषणा DM05_LNB_OFF				GPIO17/* actually 13v */
#घोषणा DM05_LNB_13V				GPIO17
#घोषणा DM05_LNB_18V				(GPIO17 | GPIO16)

/* GPIO's क्रम LNB घातer control क्रम unbअक्रमed with I2C on GPIO */
#घोषणा UNBR_LNB_MASK				(GPIO17 | GPIO16)
#घोषणा UNBR_LNB_OFF				0
#घोषणा UNBR_LNB_13V				GPIO17
#घोषणा UNBR_LNB_18V				(GPIO17 | GPIO16)

अटल अचिन्हित पूर्णांक card[]  = अणु[0 ... 3] = UNSET पूर्ण;
module_param_array(card,  पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(card, "card type");

अटल पूर्णांक ir_debug;
module_param(ir_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(ir_debug, "enable debugging information for IR decoding");

अटल अचिन्हित पूर्णांक dm1105_devcount;

DVB_DEFINE_MOD_OPT_ADAPTER_NR(adapter_nr);

काष्ठा dm1105_board अणु
	अक्षर	*name;
	काष्ठा	अणु
		u32	mask, off, v13, v18;
	पूर्ण lnb;
	u32	gpio_scl, gpio_sda;
पूर्ण;

काष्ठा dm1105_subid अणु
	u16     subvenकरोr;
	u16     subdevice;
	u32     card;
पूर्ण;

अटल स्थिर काष्ठा dm1105_board dm1105_boards[] = अणु
	[DM1105_BOARD_UNKNOWN] = अणु
		.name		= "UNKNOWN/GENERIC",
		.lnb = अणु
			.mask = DM1105_LNB_MASK,
			.off = DM1105_LNB_OFF,
			.v13 = DM1105_LNB_13V,
			.v18 = DM1105_LNB_18V,
		पूर्ण,
	पूर्ण,
	[DM1105_BOARD_DVBWORLD_2002] = अणु
		.name		= "DVBWorld PCI 2002",
		.lnb = अणु
			.mask = DM1105_LNB_MASK,
			.off = DM1105_LNB_OFF,
			.v13 = DM1105_LNB_13V,
			.v18 = DM1105_LNB_18V,
		पूर्ण,
	पूर्ण,
	[DM1105_BOARD_DVBWORLD_2004] = अणु
		.name		= "DVBWorld PCI 2004",
		.lnb = अणु
			.mask = DM1105_LNB_MASK,
			.off = DM1105_LNB_OFF,
			.v13 = DM1105_LNB_13V,
			.v18 = DM1105_LNB_18V,
		पूर्ण,
	पूर्ण,
	[DM1105_BOARD_AXESS_DM05] = अणु
		.name		= "Axess/EasyTv DM05",
		.lnb = अणु
			.mask = DM05_LNB_MASK,
			.off = DM05_LNB_OFF,
			.v13 = DM05_LNB_13V,
			.v18 = DM05_LNB_18V,
		पूर्ण,
	पूर्ण,
	[DM1105_BOARD_UNBRANDED_I2C_ON_GPIO] = अणु
		.name		= "Unbranded DM1105 with i2c on GPIOs",
		.lnb = अणु
			.mask = UNBR_LNB_MASK,
			.off = UNBR_LNB_OFF,
			.v13 = UNBR_LNB_13V,
			.v18 = UNBR_LNB_18V,
		पूर्ण,
		.gpio_scl	= GPIO14,
		.gpio_sda	= GPIO13,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dm1105_subid dm1105_subids[] = अणु
	अणु
		.subvenकरोr = 0x0000,
		.subdevice = 0x2002,
		.card      = DM1105_BOARD_DVBWORLD_2002,
	पूर्ण, अणु
		.subvenकरोr = 0x0001,
		.subdevice = 0x2002,
		.card      = DM1105_BOARD_DVBWORLD_2002,
	पूर्ण, अणु
		.subvenकरोr = 0x0000,
		.subdevice = 0x2004,
		.card      = DM1105_BOARD_DVBWORLD_2004,
	पूर्ण, अणु
		.subvenकरोr = 0x0001,
		.subdevice = 0x2004,
		.card      = DM1105_BOARD_DVBWORLD_2004,
	पूर्ण, अणु
		.subvenकरोr = 0x195d,
		.subdevice = 0x1105,
		.card      = DM1105_BOARD_AXESS_DM05,
	पूर्ण,
पूर्ण;

अटल व्योम dm1105_card_list(काष्ठा pci_dev *pci)
अणु
	पूर्णांक i;

	अगर (0 == pci->subप्रणाली_venकरोr &&
			0 == pci->subप्रणाली_device) अणु
		prपूर्णांकk(KERN_ERR
			"dm1105: Your board has no valid PCI Subsystem ID\n"
			"dm1105: and thus can't be autodetected\n"
			"dm1105: Please pass card=<n> insmod option to\n"
			"dm1105: workaround that.  Redirect complaints to\n"
			"dm1105: the vendor of the TV card.  Best regards,\n"
			"dm1105: -- tux\n");
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR
			"dm1105: Your board isn't known (yet) to the driver.\n"
			"dm1105: You can try to pick one of the existing\n"
			"dm1105: card configs via card=<n> insmod option.\n"
			"dm1105: Updating to the latest version might help\n"
			"dm1105: as well.\n");
	पूर्ण
	prपूर्णांकk(KERN_ERR "Here is a list of valid choices for the card=<n> insmod option:\n");
	क्रम (i = 0; i < ARRAY_SIZE(dm1105_boards); i++)
		prपूर्णांकk(KERN_ERR "dm1105:    card=%d -> %s\n",
				i, dm1105_boards[i].name);
पूर्ण

/* infrared remote control */
काष्ठा infrared अणु
	काष्ठा rc_dev		*dev;
	अक्षर			input_phys[32];
	काष्ठा work_काष्ठा	work;
	u32			ir_command;
पूर्ण;

काष्ठा dm1105_dev अणु
	/* pci */
	काष्ठा pci_dev *pdev;
	u8 __iomem *io_mem;

	/* ir */
	काष्ठा infrared ir;

	/* dvb */
	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dvb_frontend *fe;
	काष्ठा dvb_net dvbnet;
	अचिन्हित पूर्णांक full_ts_users;
	अचिन्हित पूर्णांक boardnr;
	पूर्णांक nr;

	/* i2c */
	काष्ठा i2c_adapter i2c_adap;
	काष्ठा i2c_adapter i2c_bb_adap;
	काष्ठा i2c_algo_bit_data i2c_bit;

	/* irq */
	काष्ठा work_काष्ठा work;
	काष्ठा workqueue_काष्ठा *wq;
	अक्षर wqn[16];

	/* dma */
	dma_addr_t dma_addr;
	अचिन्हित अक्षर *ts_buf;
	u32 wrp;
	u32 nextwrp;
	u32 buffer_size;
	अचिन्हित पूर्णांक	PacketErrorCount;
	अचिन्हित पूर्णांक dmarst;
	spinlock_t lock;
पूर्ण;

#घोषणा dm_io_mem(reg)	((अचिन्हित दीर्घ)(&dev->io_mem[reg]))

#घोषणा dm_पढ़ोb(reg)		inb(dm_io_mem(reg))
#घोषणा dm_ग_लिखोb(reg, value)	outb((value), (dm_io_mem(reg)))

#घोषणा dm_पढ़ोw(reg)		inw(dm_io_mem(reg))
#घोषणा dm_ग_लिखोw(reg, value)	outw((value), (dm_io_mem(reg)))

#घोषणा dm_पढ़ोl(reg)		inl(dm_io_mem(reg))
#घोषणा dm_ग_लिखोl(reg, value)	outl((value), (dm_io_mem(reg)))

#घोषणा dm_anकरोrl(reg, mask, value) \
	outl((inl(dm_io_mem(reg)) & ~(mask)) |\
		((value) & (mask)), (dm_io_mem(reg)))

#घोषणा dm_setl(reg, bit)	dm_anकरोrl((reg), (bit), (bit))
#घोषणा dm_clearl(reg, bit)	dm_anकरोrl((reg), (bit), 0)

/* The chip has 18 GPIOs. In HOST mode GPIO's used as 15 bit address lines,
 so we can use only 3 GPIO's from GPIO15 to GPIO17.
 Here I करोn't check whether HOST is enebled as it is not implemented yet.
 */
अटल व्योम dm1105_gpio_set(काष्ठा dm1105_dev *dev, u32 mask)
अणु
	अगर (mask & 0xfffc0000)
		prपूर्णांकk(KERN_ERR "%s: Only 18 GPIO's are allowed\n", __func__);

	अगर (mask & 0x0003ffff)
		dm_setl(DM1105_GPIOVAL, mask & 0x0003ffff);

पूर्ण

अटल व्योम dm1105_gpio_clear(काष्ठा dm1105_dev *dev, u32 mask)
अणु
	अगर (mask & 0xfffc0000)
		prपूर्णांकk(KERN_ERR "%s: Only 18 GPIO's are allowed\n", __func__);

	अगर (mask & 0x0003ffff)
		dm_clearl(DM1105_GPIOVAL, mask & 0x0003ffff);

पूर्ण

अटल व्योम dm1105_gpio_anकरोr(काष्ठा dm1105_dev *dev, u32 mask, u32 val)
अणु
	अगर (mask & 0xfffc0000)
		prपूर्णांकk(KERN_ERR "%s: Only 18 GPIO's are allowed\n", __func__);

	अगर (mask & 0x0003ffff)
		dm_anकरोrl(DM1105_GPIOVAL, mask & 0x0003ffff, val);

पूर्ण

अटल u32 dm1105_gpio_get(काष्ठा dm1105_dev *dev, u32 mask)
अणु
	अगर (mask & 0xfffc0000)
		prपूर्णांकk(KERN_ERR "%s: Only 18 GPIO's are allowed\n", __func__);

	अगर (mask & 0x0003ffff)
		वापस dm_पढ़ोl(DM1105_GPIOVAL) & mask & 0x0003ffff;

	वापस 0;
पूर्ण

अटल व्योम dm1105_gpio_enable(काष्ठा dm1105_dev *dev, u32 mask, पूर्णांक asoutput)
अणु
	अगर (mask & 0xfffc0000)
		prपूर्णांकk(KERN_ERR "%s: Only 18 GPIO's are allowed\n", __func__);

	अगर ((mask & 0x0003ffff) && asoutput)
		dm_clearl(DM1105_GPIOCTR, mask & 0x0003ffff);
	अन्यथा अगर ((mask & 0x0003ffff) && !asoutput)
		dm_setl(DM1105_GPIOCTR, mask & 0x0003ffff);

पूर्ण

अटल व्योम dm1105_setline(काष्ठा dm1105_dev *dev, u32 line, पूर्णांक state)
अणु
	अगर (state)
		dm1105_gpio_enable(dev, line, 0);
	अन्यथा अणु
		dm1105_gpio_enable(dev, line, 1);
		dm1105_gpio_clear(dev, line);
	पूर्ण
पूर्ण

अटल व्योम dm1105_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा dm1105_dev *dev = data;

	dm1105_setline(dev, dm1105_boards[dev->boardnr].gpio_sda, state);
पूर्ण

अटल व्योम dm1105_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा dm1105_dev *dev = data;

	dm1105_setline(dev, dm1105_boards[dev->boardnr].gpio_scl, state);
पूर्ण

अटल पूर्णांक dm1105_माला_लोda(व्योम *data)
अणु
	काष्ठा dm1105_dev *dev = data;

	वापस dm1105_gpio_get(dev, dm1105_boards[dev->boardnr].gpio_sda)
									? 1 : 0;
पूर्ण

अटल पूर्णांक dm1105_माला_लोcl(व्योम *data)
अणु
	काष्ठा dm1105_dev *dev = data;

	वापस dm1105_gpio_get(dev, dm1105_boards[dev->boardnr].gpio_scl)
									? 1 : 0;
पूर्ण

अटल पूर्णांक dm1105_i2c_xfer(काष्ठा i2c_adapter *i2c_adap,
			    काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा dm1105_dev *dev ;

	पूर्णांक addr, rc, i, j, k, len, byte, data;
	u8 status;

	dev = i2c_adap->algo_data;
	क्रम (i = 0; i < num; i++) अणु
		dm_ग_लिखोb(DM1105_I2CCTR, 0x00);
		अगर (msgs[i].flags & I2C_M_RD) अणु
			/* पढ़ो bytes */
			addr  = msgs[i].addr << 1;
			addr |= 1;
			dm_ग_लिखोb(DM1105_I2CDAT, addr);
			क्रम (byte = 0; byte < msgs[i].len; byte++)
				dm_ग_लिखोb(DM1105_I2CDAT + byte + 1, 0);

			dm_ग_लिखोb(DM1105_I2CCTR, 0x81 + msgs[i].len);
			क्रम (j = 0; j < 55; j++) अणु
				mdelay(10);
				status = dm_पढ़ोb(DM1105_I2CSTS);
				अगर ((status & 0xc0) == 0x40)
					अवरोध;
			पूर्ण
			अगर (j >= 55)
				वापस -1;

			क्रम (byte = 0; byte < msgs[i].len; byte++) अणु
				rc = dm_पढ़ोb(DM1105_I2CDAT + byte + 1);
				अगर (rc < 0)
					जाओ err;
				msgs[i].buf[byte] = rc;
			पूर्ण
		पूर्ण अन्यथा अगर ((msgs[i].buf[0] == 0xf7) && (msgs[i].addr == 0x55)) अणु
			/* prepared क्रम cx24116 firmware */
			/* Write in small blocks */
			len = msgs[i].len - 1;
			k = 1;
			करो अणु
				dm_ग_लिखोb(DM1105_I2CDAT, msgs[i].addr << 1);
				dm_ग_लिखोb(DM1105_I2CDAT + 1, 0xf7);
				क्रम (byte = 0; byte < (len > 48 ? 48 : len); byte++) अणु
					data = msgs[i].buf[k + byte];
					dm_ग_लिखोb(DM1105_I2CDAT + byte + 2, data);
				पूर्ण
				dm_ग_लिखोb(DM1105_I2CCTR, 0x82 + (len > 48 ? 48 : len));
				क्रम (j = 0; j < 25; j++) अणु
					mdelay(10);
					status = dm_पढ़ोb(DM1105_I2CSTS);
					अगर ((status & 0xc0) == 0x40)
						अवरोध;
				पूर्ण

				अगर (j >= 25)
					वापस -1;

				k += 48;
				len -= 48;
			पूर्ण जबतक (len > 0);
		पूर्ण अन्यथा अणु
			/* ग_लिखो bytes */
			dm_ग_लिखोb(DM1105_I2CDAT, msgs[i].addr << 1);
			क्रम (byte = 0; byte < msgs[i].len; byte++) अणु
				data = msgs[i].buf[byte];
				dm_ग_लिखोb(DM1105_I2CDAT + byte + 1, data);
			पूर्ण
			dm_ग_लिखोb(DM1105_I2CCTR, 0x81 + msgs[i].len);
			क्रम (j = 0; j < 25; j++) अणु
				mdelay(10);
				status = dm_पढ़ोb(DM1105_I2CSTS);
				अगर ((status & 0xc0) == 0x40)
					अवरोध;
			पूर्ण

			अगर (j >= 25)
				वापस -1;
		पूर्ण
	पूर्ण
	वापस num;
 err:
	वापस rc;
पूर्ण

अटल u32 functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm dm1105_algo = अणु
	.master_xfer   = dm1105_i2c_xfer,
	.functionality = functionality,
पूर्ण;

अटल अंतरभूत काष्ठा dm1105_dev *feed_to_dm1105_dev(काष्ठा dvb_demux_feed *feed)
अणु
	वापस container_of(feed->demux, काष्ठा dm1105_dev, demux);
पूर्ण

अटल अंतरभूत काष्ठा dm1105_dev *frontend_to_dm1105_dev(काष्ठा dvb_frontend *fe)
अणु
	वापस container_of(fe->dvb, काष्ठा dm1105_dev, dvb_adapter);
पूर्ण

अटल पूर्णांक dm1105_set_voltage(काष्ठा dvb_frontend *fe,
			      क्रमागत fe_sec_voltage voltage)
अणु
	काष्ठा dm1105_dev *dev = frontend_to_dm1105_dev(fe);

	dm1105_gpio_enable(dev, dm1105_boards[dev->boardnr].lnb.mask, 1);
	अगर (voltage == SEC_VOLTAGE_18)
		dm1105_gpio_anकरोr(dev,
				dm1105_boards[dev->boardnr].lnb.mask,
				dm1105_boards[dev->boardnr].lnb.v18);
	अन्यथा अगर (voltage == SEC_VOLTAGE_13)
		dm1105_gpio_anकरोr(dev,
				dm1105_boards[dev->boardnr].lnb.mask,
				dm1105_boards[dev->boardnr].lnb.v13);
	अन्यथा
		dm1105_gpio_anकरोr(dev,
				dm1105_boards[dev->boardnr].lnb.mask,
				dm1105_boards[dev->boardnr].lnb.off);

	वापस 0;
पूर्ण

अटल व्योम dm1105_set_dma_addr(काष्ठा dm1105_dev *dev)
अणु
	dm_ग_लिखोl(DM1105_STADR, (__क्रमce u32)cpu_to_le32(dev->dma_addr));
पूर्ण

अटल पूर्णांक dm1105_dma_map(काष्ठा dm1105_dev *dev)
अणु
	dev->ts_buf = dma_alloc_coherent(&dev->pdev->dev,
					 6 * DM1105_DMA_BYTES, &dev->dma_addr,
					 GFP_KERNEL);

	वापस !dev->ts_buf;
पूर्ण

अटल व्योम dm1105_dma_unmap(काष्ठा dm1105_dev *dev)
अणु
	dma_मुक्त_coherent(&dev->pdev->dev, 6 * DM1105_DMA_BYTES, dev->ts_buf,
			  dev->dma_addr);
पूर्ण

अटल व्योम dm1105_enable_irqs(काष्ठा dm1105_dev *dev)
अणु
	dm_ग_लिखोb(DM1105_INTMAK, INTMAK_ALLMASK);
	dm_ग_लिखोb(DM1105_CR, 1);
पूर्ण

अटल व्योम dm1105_disable_irqs(काष्ठा dm1105_dev *dev)
अणु
	dm_ग_लिखोb(DM1105_INTMAK, INTMAK_IRM);
	dm_ग_लिखोb(DM1105_CR, 0);
पूर्ण

अटल पूर्णांक dm1105_start_feed(काष्ठा dvb_demux_feed *f)
अणु
	काष्ठा dm1105_dev *dev = feed_to_dm1105_dev(f);

	अगर (dev->full_ts_users++ == 0)
		dm1105_enable_irqs(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dm1105_stop_feed(काष्ठा dvb_demux_feed *f)
अणु
	काष्ठा dm1105_dev *dev = feed_to_dm1105_dev(f);

	अगर (--dev->full_ts_users == 0)
		dm1105_disable_irqs(dev);

	वापस 0;
पूर्ण

/* ir work handler */
अटल व्योम dm1105_emit_key(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा infrared *ir = container_of(work, काष्ठा infrared, work);
	u32 ircom = ir->ir_command;
	u8 data;

	अगर (ir_debug)
		prपूर्णांकk(KERN_INFO "%s: received byte 0x%04x\n", __func__, ircom);

	data = (ircom >> 8) & 0x7f;

	/* FIXME: UNKNOWN because we करोn't generate a full NEC scancode (yet?) */
	rc_keyकरोwn(ir->dev, RC_PROTO_UNKNOWN, data, 0);
पूर्ण

/* work handler */
अटल व्योम dm1105_dmx_buffer(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dm1105_dev *dev = container_of(work, काष्ठा dm1105_dev, work);
	अचिन्हित पूर्णांक nbpackets;
	u32 oldwrp = dev->wrp;
	u32 nextwrp = dev->nextwrp;

	अगर (!((dev->ts_buf[oldwrp] == 0x47) &&
			(dev->ts_buf[oldwrp + 188] == 0x47) &&
			(dev->ts_buf[oldwrp + 188 * 2] == 0x47))) अणु
		dev->PacketErrorCount++;
		/* bad packet found */
		अगर ((dev->PacketErrorCount >= 2) &&
				(dev->dmarst == 0)) अणु
			dm_ग_लिखोb(DM1105_RST, 1);
			dev->wrp = 0;
			dev->PacketErrorCount = 0;
			dev->dmarst = 0;
			वापस;
		पूर्ण
	पूर्ण

	अगर (nextwrp < oldwrp) अणु
		स_नकल(dev->ts_buf + dev->buffer_size, dev->ts_buf, nextwrp);
		nbpackets = ((dev->buffer_size - oldwrp) + nextwrp) / 188;
	पूर्ण अन्यथा
		nbpackets = (nextwrp - oldwrp) / 188;

	dev->wrp = nextwrp;
	dvb_dmx_swfilter_packets(&dev->demux, &dev->ts_buf[oldwrp], nbpackets);
पूर्ण

अटल irqवापस_t dm1105_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dm1105_dev *dev = dev_id;

	/* Read-Write INSTS Ack's Interrupt क्रम DM1105 chip 16.03.2008 */
	अचिन्हित पूर्णांक पूर्णांकsts = dm_पढ़ोb(DM1105_INTSTS);
	dm_ग_लिखोb(DM1105_INTSTS, पूर्णांकsts);

	चयन (पूर्णांकsts) अणु
	हाल INTSTS_TSIRQ:
	हाल (INTSTS_TSIRQ | INTSTS_IR):
		dev->nextwrp = dm_पढ़ोl(DM1105_WRP) - dm_पढ़ोl(DM1105_STADR);
		queue_work(dev->wq, &dev->work);
		अवरोध;
	हाल INTSTS_IR:
		dev->ir.ir_command = dm_पढ़ोl(DM1105_IRCODE);
		schedule_work(&dev->ir.work);
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dm1105_ir_init(काष्ठा dm1105_dev *dm1105)
अणु
	काष्ठा rc_dev *dev;
	पूर्णांक err = -ENOMEM;

	dev = rc_allocate_device(RC_DRIVER_SCANCODE);
	अगर (!dev)
		वापस -ENOMEM;

	snम_लिखो(dm1105->ir.input_phys, माप(dm1105->ir.input_phys),
		"pci-%s/ir0", pci_name(dm1105->pdev));

	dev->driver_name = MODULE_NAME;
	dev->map_name = RC_MAP_DM1105_NEC;
	dev->device_name = "DVB on-card IR receiver";
	dev->input_phys = dm1105->ir.input_phys;
	dev->input_id.bustype = BUS_PCI;
	dev->input_id.version = 1;
	अगर (dm1105->pdev->subप्रणाली_venकरोr) अणु
		dev->input_id.venकरोr = dm1105->pdev->subप्रणाली_venकरोr;
		dev->input_id.product = dm1105->pdev->subप्रणाली_device;
	पूर्ण अन्यथा अणु
		dev->input_id.venकरोr = dm1105->pdev->venकरोr;
		dev->input_id.product = dm1105->pdev->device;
	पूर्ण
	dev->dev.parent = &dm1105->pdev->dev;

	INIT_WORK(&dm1105->ir.work, dm1105_emit_key);

	err = rc_रेजिस्टर_device(dev);
	अगर (err < 0) अणु
		rc_मुक्त_device(dev);
		वापस err;
	पूर्ण

	dm1105->ir.dev = dev;
	वापस 0;
पूर्ण

अटल व्योम dm1105_ir_निकास(काष्ठा dm1105_dev *dm1105)
अणु
	rc_unरेजिस्टर_device(dm1105->ir.dev);
पूर्ण

अटल पूर्णांक dm1105_hw_init(काष्ठा dm1105_dev *dev)
अणु
	dm1105_disable_irqs(dev);

	dm_ग_लिखोb(DM1105_HOST_CTR, 0);

	/*DATALEN 188,*/
	dm_ग_लिखोb(DM1105_DTALENTH, 188);
	/*TS_STRT TS_VALP MSBFIRST TS_MODE ALPAS TSPES*/
	dm_ग_लिखोw(DM1105_TSCTR, 0xc10a);

	/* map DMA and set address */
	dm1105_dma_map(dev);
	dm1105_set_dma_addr(dev);
	/* big buffer */
	dm_ग_लिखोl(DM1105_RLEN, 5 * DM1105_DMA_BYTES);
	dm_ग_लिखोb(DM1105_INTCNT, 47);

	/* IR NEC mode enable */
	dm_ग_लिखोb(DM1105_IRCTR, (DM1105_IR_EN | DM1105_SYS_CHK));
	dm_ग_लिखोb(DM1105_IRMODE, 0);
	dm_ग_लिखोw(DM1105_SYSTEMCODE, 0);

	वापस 0;
पूर्ण

अटल व्योम dm1105_hw_निकास(काष्ठा dm1105_dev *dev)
अणु
	dm1105_disable_irqs(dev);

	/* IR disable */
	dm_ग_लिखोb(DM1105_IRCTR, 0);
	dm_ग_लिखोb(DM1105_INTMAK, INTMAK_NONEMASK);

	dm1105_dma_unmap(dev);
पूर्ण

अटल स्थिर काष्ठा stv0299_config sharp_z0194a_config = अणु
	.demod_address = 0x68,
	.inittab = sharp_z0194a_inittab,
	.mclk = 88000000UL,
	.invert = 1,
	.skip_reinit = 0,
	.lock_output = STV0299_LOCKOUTPUT_1,
	.volt13_op0_op1 = STV0299_VOLT13_OP1,
	.min_delay_ms = 100,
	.set_symbol_rate = sharp_z0194a_set_symbol_rate,
पूर्ण;

अटल काष्ठा stv0288_config earda_config = अणु
	.demod_address = 0x68,
	.min_delay_ms = 100,
पूर्ण;

अटल काष्ठा si21xx_config serit_config = अणु
	.demod_address = 0x68,
	.min_delay_ms = 100,

पूर्ण;

अटल काष्ठा cx24116_config serit_sp2633_config = अणु
	.demod_address = 0x55,
पूर्ण;

अटल काष्ठा ds3000_config dvbworld_ds3000_config = अणु
	.demod_address = 0x68,
पूर्ण;

अटल काष्ठा ts2020_config dvbworld_ts2020_config  = अणु
	.tuner_address = 0x60,
	.clk_out_भाग = 1,
पूर्ण;

अटल पूर्णांक frontend_init(काष्ठा dm1105_dev *dev)
अणु
	पूर्णांक ret;

	चयन (dev->boardnr) अणु
	हाल DM1105_BOARD_UNBRANDED_I2C_ON_GPIO:
		dm1105_gpio_enable(dev, GPIO15, 1);
		dm1105_gpio_clear(dev, GPIO15);
		msleep(100);
		dm1105_gpio_set(dev, GPIO15);
		msleep(200);
		dev->fe = dvb_attach(
			stv0299_attach, &sharp_z0194a_config,
			&dev->i2c_bb_adap);
		अगर (dev->fe) अणु
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(dvb_pll_attach, dev->fe, 0x60,
					&dev->i2c_bb_adap, DVB_PLL_OPERA1);
			अवरोध;
		पूर्ण

		dev->fe = dvb_attach(
			stv0288_attach, &earda_config,
			&dev->i2c_bb_adap);
		अगर (dev->fe) अणु
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(stb6000_attach, dev->fe, 0x61,
					&dev->i2c_bb_adap);
			अवरोध;
		पूर्ण

		dev->fe = dvb_attach(
			si21xx_attach, &serit_config,
			&dev->i2c_bb_adap);
		अगर (dev->fe)
			dev->fe->ops.set_voltage = dm1105_set_voltage;
		अवरोध;
	हाल DM1105_BOARD_DVBWORLD_2004:
		dev->fe = dvb_attach(
			cx24116_attach, &serit_sp2633_config,
			&dev->i2c_adap);
		अगर (dev->fe) अणु
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			अवरोध;
		पूर्ण

		dev->fe = dvb_attach(
			ds3000_attach, &dvbworld_ds3000_config,
			&dev->i2c_adap);
		अगर (dev->fe) अणु
			dvb_attach(ts2020_attach, dev->fe,
				&dvbworld_ts2020_config, &dev->i2c_adap);
			dev->fe->ops.set_voltage = dm1105_set_voltage;
		पूर्ण

		अवरोध;
	हाल DM1105_BOARD_DVBWORLD_2002:
	हाल DM1105_BOARD_AXESS_DM05:
	शेष:
		dev->fe = dvb_attach(
			stv0299_attach, &sharp_z0194a_config,
			&dev->i2c_adap);
		अगर (dev->fe) अणु
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(dvb_pll_attach, dev->fe, 0x60,
					&dev->i2c_adap, DVB_PLL_OPERA1);
			अवरोध;
		पूर्ण

		dev->fe = dvb_attach(
			stv0288_attach, &earda_config,
			&dev->i2c_adap);
		अगर (dev->fe) अणु
			dev->fe->ops.set_voltage = dm1105_set_voltage;
			dvb_attach(stb6000_attach, dev->fe, 0x61,
					&dev->i2c_adap);
			अवरोध;
		पूर्ण

		dev->fe = dvb_attach(
			si21xx_attach, &serit_config,
			&dev->i2c_adap);
		अगर (dev->fe)
			dev->fe->ops.set_voltage = dm1105_set_voltage;

	पूर्ण

	अगर (!dev->fe) अणु
		dev_err(&dev->pdev->dev, "could not attach frontend\n");
		वापस -ENODEV;
	पूर्ण

	ret = dvb_रेजिस्टर_frontend(&dev->dvb_adapter, dev->fe);
	अगर (ret < 0) अणु
		अगर (dev->fe->ops.release)
			dev->fe->ops.release(dev->fe);
		dev->fe = शून्य;
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dm1105_पढ़ो_mac(काष्ठा dm1105_dev *dev, u8 *mac)
अणु
	अटल u8 command[1] = अणु 0x28 पूर्ण;

	काष्ठा i2c_msg msg[] = अणु
		अणु
			.addr = IIC_24C01_addr >> 1,
			.flags = 0,
			.buf = command,
			.len = 1
		पूर्ण, अणु
			.addr = IIC_24C01_addr >> 1,
			.flags = I2C_M_RD,
			.buf = mac,
			.len = 6
		पूर्ण,
	पूर्ण;

	dm1105_i2c_xfer(&dev->i2c_adap, msg , 2);
	dev_info(&dev->pdev->dev, "MAC %pM\n", mac);
पूर्ण

अटल पूर्णांक dm1105_probe(काष्ठा pci_dev *pdev,
				  स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा dm1105_dev *dev;
	काष्ठा dvb_adapter *dvb_adapter;
	काष्ठा dvb_demux *dvbdemux;
	काष्ठा dmx_demux *dmx;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	अगर (dm1105_devcount >= ARRAY_SIZE(card))
		वापस -ENODEV;

	dev = kzalloc(माप(काष्ठा dm1105_dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	/* board config */
	dev->nr = dm1105_devcount;
	dev->boardnr = UNSET;
	अगर (card[dev->nr] < ARRAY_SIZE(dm1105_boards))
		dev->boardnr = card[dev->nr];
	क्रम (i = 0; UNSET == dev->boardnr &&
				i < ARRAY_SIZE(dm1105_subids); i++)
		अगर (pdev->subप्रणाली_venकरोr ==
			dm1105_subids[i].subvenकरोr &&
				pdev->subप्रणाली_device ==
					dm1105_subids[i].subdevice)
			dev->boardnr = dm1105_subids[i].card;

	अगर (UNSET == dev->boardnr) अणु
		dev->boardnr = DM1105_BOARD_UNKNOWN;
		dm1105_card_list(pdev);
	पूर्ण

	dm1105_devcount++;
	dev->pdev = pdev;
	dev->buffer_size = 5 * DM1105_DMA_BYTES;
	dev->PacketErrorCount = 0;
	dev->dmarst = 0;

	ret = pci_enable_device(pdev);
	अगर (ret < 0)
		जाओ err_kमुक्त;

	ret = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	pci_set_master(pdev);

	ret = pci_request_regions(pdev, DRIVER_NAME);
	अगर (ret < 0)
		जाओ err_pci_disable_device;

	dev->io_mem = pci_iomap(pdev, 0, pci_resource_len(pdev, 0));
	अगर (!dev->io_mem) अणु
		ret = -EIO;
		जाओ err_pci_release_regions;
	पूर्ण

	spin_lock_init(&dev->lock);
	pci_set_drvdata(pdev, dev);

	ret = dm1105_hw_init(dev);
	अगर (ret < 0)
		जाओ err_pci_iounmap;

	/* i2c */
	i2c_set_adapdata(&dev->i2c_adap, dev);
	strscpy(dev->i2c_adap.name, DRIVER_NAME, माप(dev->i2c_adap.name));
	dev->i2c_adap.owner = THIS_MODULE;
	dev->i2c_adap.dev.parent = &pdev->dev;
	dev->i2c_adap.algo = &dm1105_algo;
	dev->i2c_adap.algo_data = dev;
	ret = i2c_add_adapter(&dev->i2c_adap);

	अगर (ret < 0)
		जाओ err_dm1105_hw_निकास;

	i2c_set_adapdata(&dev->i2c_bb_adap, dev);
	strscpy(dev->i2c_bb_adap.name, DM1105_I2C_GPIO_NAME,
		माप(dev->i2c_bb_adap.name));
	dev->i2c_bb_adap.owner = THIS_MODULE;
	dev->i2c_bb_adap.dev.parent = &pdev->dev;
	dev->i2c_bb_adap.algo_data = &dev->i2c_bit;
	dev->i2c_bit.data = dev;
	dev->i2c_bit.setsda = dm1105_setsda;
	dev->i2c_bit.setscl = dm1105_setscl;
	dev->i2c_bit.माला_लोda = dm1105_माला_लोda;
	dev->i2c_bit.माला_लोcl = dm1105_माला_लोcl;
	dev->i2c_bit.udelay = 10;
	dev->i2c_bit.समयout = 10;

	/* Raise SCL and SDA */
	dm1105_setsda(dev, 1);
	dm1105_setscl(dev, 1);

	ret = i2c_bit_add_bus(&dev->i2c_bb_adap);
	अगर (ret < 0)
		जाओ err_i2c_del_adapter;

	/* dvb */
	ret = dvb_रेजिस्टर_adapter(&dev->dvb_adapter, DRIVER_NAME,
					THIS_MODULE, &pdev->dev, adapter_nr);
	अगर (ret < 0)
		जाओ err_i2c_del_adapters;

	dvb_adapter = &dev->dvb_adapter;

	dm1105_पढ़ो_mac(dev, dvb_adapter->proposed_mac);

	dvbdemux = &dev->demux;
	dvbdemux->filternum = 256;
	dvbdemux->feednum = 256;
	dvbdemux->start_feed = dm1105_start_feed;
	dvbdemux->stop_feed = dm1105_stop_feed;
	dvbdemux->dmx.capabilities = (DMX_TS_FILTERING |
			DMX_SECTION_FILTERING | DMX_MEMORY_BASED_FILTERING);
	ret = dvb_dmx_init(dvbdemux);
	अगर (ret < 0)
		जाओ err_dvb_unरेजिस्टर_adapter;

	dmx = &dvbdemux->dmx;
	dev->dmxdev.filternum = 256;
	dev->dmxdev.demux = dmx;
	dev->dmxdev.capabilities = 0;

	ret = dvb_dmxdev_init(&dev->dmxdev, dvb_adapter);
	अगर (ret < 0)
		जाओ err_dvb_dmx_release;

	dev->hw_frontend.source = DMX_FRONTEND_0;

	ret = dmx->add_frontend(dmx, &dev->hw_frontend);
	अगर (ret < 0)
		जाओ err_dvb_dmxdev_release;

	dev->mem_frontend.source = DMX_MEMORY_FE;

	ret = dmx->add_frontend(dmx, &dev->mem_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_hw_frontend;

	ret = dmx->connect_frontend(dmx, &dev->hw_frontend);
	अगर (ret < 0)
		जाओ err_हटाओ_mem_frontend;

	ret = dvb_net_init(dvb_adapter, &dev->dvbnet, dmx);
	अगर (ret < 0)
		जाओ err_disconnect_frontend;

	ret = frontend_init(dev);
	अगर (ret < 0)
		जाओ err_dvb_net;

	dm1105_ir_init(dev);

	INIT_WORK(&dev->work, dm1105_dmx_buffer);
	प्र_लिखो(dev->wqn, "%s/%d", dvb_adapter->name, dvb_adapter->num);
	dev->wq = create_singlethपढ़ो_workqueue(dev->wqn);
	अगर (!dev->wq) अणु
		ret = -ENOMEM;
		जाओ err_dvb_net;
	पूर्ण

	ret = request_irq(pdev->irq, dm1105_irq, IRQF_SHARED,
						DRIVER_NAME, dev);
	अगर (ret < 0)
		जाओ err_workqueue;

	वापस 0;

err_workqueue:
	destroy_workqueue(dev->wq);
err_dvb_net:
	dvb_net_release(&dev->dvbnet);
err_disconnect_frontend:
	dmx->disconnect_frontend(dmx);
err_हटाओ_mem_frontend:
	dmx->हटाओ_frontend(dmx, &dev->mem_frontend);
err_हटाओ_hw_frontend:
	dmx->हटाओ_frontend(dmx, &dev->hw_frontend);
err_dvb_dmxdev_release:
	dvb_dmxdev_release(&dev->dmxdev);
err_dvb_dmx_release:
	dvb_dmx_release(dvbdemux);
err_dvb_unरेजिस्टर_adapter:
	dvb_unरेजिस्टर_adapter(dvb_adapter);
err_i2c_del_adapters:
	i2c_del_adapter(&dev->i2c_bb_adap);
err_i2c_del_adapter:
	i2c_del_adapter(&dev->i2c_adap);
err_dm1105_hw_निकास:
	dm1105_hw_निकास(dev);
err_pci_iounmap:
	pci_iounmap(pdev, dev->io_mem);
err_pci_release_regions:
	pci_release_regions(pdev);
err_pci_disable_device:
	pci_disable_device(pdev);
err_kमुक्त:
	kमुक्त(dev);
	वापस ret;
पूर्ण

अटल व्योम dm1105_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा dm1105_dev *dev = pci_get_drvdata(pdev);
	काष्ठा dvb_adapter *dvb_adapter = &dev->dvb_adapter;
	काष्ठा dvb_demux *dvbdemux = &dev->demux;
	काष्ठा dmx_demux *dmx = &dvbdemux->dmx;

	dm1105_ir_निकास(dev);
	dmx->बंद(dmx);
	dvb_net_release(&dev->dvbnet);
	अगर (dev->fe)
		dvb_unरेजिस्टर_frontend(dev->fe);

	dmx->disconnect_frontend(dmx);
	dmx->हटाओ_frontend(dmx, &dev->mem_frontend);
	dmx->हटाओ_frontend(dmx, &dev->hw_frontend);
	dvb_dmxdev_release(&dev->dmxdev);
	dvb_dmx_release(dvbdemux);
	dvb_unरेजिस्टर_adapter(dvb_adapter);
	i2c_del_adapter(&dev->i2c_adap);

	dm1105_hw_निकास(dev);
	मुक्त_irq(pdev->irq, dev);
	pci_iounmap(pdev, dev->io_mem);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	dm1105_devcount--;
	kमुक्त(dev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id dm1105_id_table[] = अणु
	अणु
		.venकरोr = PCI_VENDOR_ID_TRIGEM,
		.device = PCI_DEVICE_ID_DM1105,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण, अणु
		.venकरोr = PCI_VENDOR_ID_AXESS,
		.device = PCI_DEVICE_ID_DM05,
		.subvenकरोr = PCI_ANY_ID,
		.subdevice = PCI_ANY_ID,
	पूर्ण, अणु
		/* empty */
	पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, dm1105_id_table);

अटल काष्ठा pci_driver dm1105_driver = अणु
	.name = DRIVER_NAME,
	.id_table = dm1105_id_table,
	.probe = dm1105_probe,
	.हटाओ = dm1105_हटाओ,
पूर्ण;

module_pci_driver(dm1105_driver);

MODULE_AUTHOR("Igor M. Liplianin <liplianin@me.by>");
MODULE_DESCRIPTION("SDMC DM1105 DVB driver");
MODULE_LICENSE("GPL");
