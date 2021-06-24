<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007, 2011 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Copyright (C) 2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * Derived from the PCAN project file driver/src/pcan_pci.c:
 *
 * Copyright (C) 2001-2006  PEAK System-Technik GmbH
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>

#समावेश "sja1000.h"

MODULE_AUTHOR("Stephane Grosjean <s.grosjean@peak-system.com>");
MODULE_DESCRIPTION("Socket-CAN driver for PEAK PCAN PCI family cards");
MODULE_LICENSE("GPL v2");

#घोषणा DRV_NAME  "peak_pci"

काष्ठा peak_pciec_card;
काष्ठा peak_pci_chan अणु
	व्योम __iomem *cfg_base;		/* Common क्रम all channels */
	काष्ठा net_device *prev_dev;	/* Chain of network devices */
	u16 icr_mask;			/* Interrupt mask क्रम fast ack */
	काष्ठा peak_pciec_card *pciec_card;	/* only क्रम PCIeC LEDs */
पूर्ण;

#घोषणा PEAK_PCI_CAN_CLOCK	(16000000 / 2)

#घोषणा PEAK_PCI_CDR		(CDR_CBP | CDR_CLKOUT_MASK)
#घोषणा PEAK_PCI_OCR		OCR_TX0_PUSHPULL

/*
 * Important PITA रेजिस्टरs
 */
#घोषणा PITA_ICR		0x00	/* Interrupt control रेजिस्टर */
#घोषणा PITA_GPIOICR		0x18	/* GPIO पूर्णांकerface control रेजिस्टर */
#घोषणा PITA_MISC		0x1C	/* Miscellaneous रेजिस्टर */

#घोषणा PEAK_PCI_CFG_SIZE	0x1000	/* Size of the config PCI bar */
#घोषणा PEAK_PCI_CHAN_SIZE	0x0400	/* Size used by the channel */

#घोषणा PEAK_PCI_VENDOR_ID	0x001C	/* The PCI device and venकरोr IDs */
#घोषणा PEAK_PCI_DEVICE_ID	0x0001	/* क्रम PCI/PCIe slot cards */
#घोषणा PEAK_PCIEC_DEVICE_ID	0x0002	/* क्रम ExpressCard slot cards */
#घोषणा PEAK_PCIE_DEVICE_ID	0x0003	/* क्रम nextgen PCIe slot cards */
#घोषणा PEAK_CPCI_DEVICE_ID	0x0004	/* क्रम nextgen cPCI slot cards */
#घोषणा PEAK_MPCI_DEVICE_ID	0x0005	/* क्रम nextgen miniPCI slot cards */
#घोषणा PEAK_PC_104P_DEVICE_ID	0x0006	/* PCAN-PC/104+ cards */
#घोषणा PEAK_PCI_104E_DEVICE_ID	0x0007	/* PCAN-PCI/104 Express cards */
#घोषणा PEAK_MPCIE_DEVICE_ID	0x0008	/* The miniPCIe slot cards */
#घोषणा PEAK_PCIE_OEM_ID	0x0009	/* PCAN-PCI Express OEM */
#घोषणा PEAK_PCIEC34_DEVICE_ID	0x000A	/* PCAN-PCI Express 34 (one channel) */

#घोषणा PEAK_PCI_CHAN_MAX	4

अटल स्थिर u16 peak_pci_icr_masks[PEAK_PCI_CHAN_MAX] = अणु
	0x02, 0x01, 0x40, 0x80
पूर्ण;

अटल स्थिर काष्ठा pci_device_id peak_pci_tbl[] = अणु
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCI_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCIE_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_MPCI_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_MPCIE_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_PC_104P_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCI_104E_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_CPCI_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCIE_OEM_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
#अगर_घोषित CONFIG_CAN_PEAK_PCIEC
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCIEC_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणुPEAK_PCI_VENDOR_ID, PEAK_PCIEC34_DEVICE_ID, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
#पूर्ण_अगर
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, peak_pci_tbl);

#अगर_घोषित CONFIG_CAN_PEAK_PCIEC
/*
 * PCAN-ExpressCard needs I2C bit-banging configuration option.
 */

/* GPIOICR byte access offsets */
#घोषणा PITA_GPOUT		0x18	/* GPx output value */
#घोषणा PITA_GPIN		0x19	/* GPx input value */
#घोषणा PITA_GPOEN		0x1A	/* configure GPx as output pin */

/* I2C GP bits */
#घोषणा PITA_GPIN_SCL		0x01	/* Serial Clock Line */
#घोषणा PITA_GPIN_SDA		0x04	/* Serial DAta line */

#घोषणा PCA9553_1_SLAVEADDR	(0xC4 >> 1)

/* PCA9553 LS0 fields values */
क्रमागत अणु
	PCA9553_LOW,
	PCA9553_HIGHZ,
	PCA9553_PWM0,
	PCA9553_PWM1
पूर्ण;

/* LEDs control */
#घोषणा PCA9553_ON		PCA9553_LOW
#घोषणा PCA9553_OFF		PCA9553_HIGHZ
#घोषणा PCA9553_SLOW		PCA9553_PWM0
#घोषणा PCA9553_FAST		PCA9553_PWM1

#घोषणा PCA9553_LED(c)		(1 << (c))
#घोषणा PCA9553_LED_STATE(s, c)	((s) << ((c) << 1))

#घोषणा PCA9553_LED_ON(c)	PCA9553_LED_STATE(PCA9553_ON, c)
#घोषणा PCA9553_LED_OFF(c)	PCA9553_LED_STATE(PCA9553_OFF, c)
#घोषणा PCA9553_LED_SLOW(c)	PCA9553_LED_STATE(PCA9553_SLOW, c)
#घोषणा PCA9553_LED_FAST(c)	PCA9553_LED_STATE(PCA9553_FAST, c)
#घोषणा PCA9553_LED_MASK(c)	PCA9553_LED_STATE(0x03, c)

#घोषणा PCA9553_LED_OFF_ALL	(PCA9553_LED_OFF(0) | PCA9553_LED_OFF(1))

#घोषणा PCA9553_LS0_INIT	0x40 /* initial value (!= from 0x00) */

काष्ठा peak_pciec_chan अणु
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ prev_rx_bytes;
	अचिन्हित दीर्घ prev_tx_bytes;
पूर्ण;

काष्ठा peak_pciec_card अणु
	व्योम __iomem *cfg_base;		/* Common क्रम all channels */
	व्योम __iomem *reg_base;		/* first channel base address */
	u8 led_cache;			/* leds state cache */

	/* PCIExpressCard i2c data */
	काष्ठा i2c_algo_bit_data i2c_bit;
	काष्ठा i2c_adapter led_chip;
	काष्ठा delayed_work led_work;	/* led delayed work */
	पूर्णांक chan_count;
	काष्ठा peak_pciec_chan channel[PEAK_PCI_CHAN_MAX];
पूर्ण;

/* "normal" pci रेजिस्टर ग_लिखो callback is overloaded क्रम leds control */
अटल व्योम peak_pci_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
			       पूर्णांक port, u8 val);

अटल अंतरभूत व्योम pita_set_scl_highz(काष्ठा peak_pciec_card *card)
अणु
	u8 gp_outen = पढ़ोb(card->cfg_base + PITA_GPOEN) & ~PITA_GPIN_SCL;
	ग_लिखोb(gp_outen, card->cfg_base + PITA_GPOEN);
पूर्ण

अटल अंतरभूत व्योम pita_set_sda_highz(काष्ठा peak_pciec_card *card)
अणु
	u8 gp_outen = पढ़ोb(card->cfg_base + PITA_GPOEN) & ~PITA_GPIN_SDA;
	ग_लिखोb(gp_outen, card->cfg_base + PITA_GPOEN);
पूर्ण

अटल व्योम peak_pciec_init_pita_gpio(काष्ठा peak_pciec_card *card)
अणु
	/* उठाओ SCL & SDA GPIOs to high-Z */
	pita_set_scl_highz(card);
	pita_set_sda_highz(card);
पूर्ण

अटल व्योम pita_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा peak_pciec_card *card = (काष्ठा peak_pciec_card *)data;
	u8 gp_out, gp_outen;

	/* set output sda always to 0 */
	gp_out = पढ़ोb(card->cfg_base + PITA_GPOUT) & ~PITA_GPIN_SDA;
	ग_लिखोb(gp_out, card->cfg_base + PITA_GPOUT);

	/* control output sda with GPOEN */
	gp_outen = पढ़ोb(card->cfg_base + PITA_GPOEN);
	अगर (state)
		gp_outen &= ~PITA_GPIN_SDA;
	अन्यथा
		gp_outen |= PITA_GPIN_SDA;

	ग_लिखोb(gp_outen, card->cfg_base + PITA_GPOEN);
पूर्ण

अटल व्योम pita_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा peak_pciec_card *card = (काष्ठा peak_pciec_card *)data;
	u8 gp_out, gp_outen;

	/* set output scl always to 0 */
	gp_out = पढ़ोb(card->cfg_base + PITA_GPOUT) & ~PITA_GPIN_SCL;
	ग_लिखोb(gp_out, card->cfg_base + PITA_GPOUT);

	/* control output scl with GPOEN */
	gp_outen = पढ़ोb(card->cfg_base + PITA_GPOEN);
	अगर (state)
		gp_outen &= ~PITA_GPIN_SCL;
	अन्यथा
		gp_outen |= PITA_GPIN_SCL;

	ग_लिखोb(gp_outen, card->cfg_base + PITA_GPOEN);
पूर्ण

अटल पूर्णांक pita_माला_लोda(व्योम *data)
अणु
	काष्ठा peak_pciec_card *card = (काष्ठा peak_pciec_card *)data;

	/* set tristate */
	pita_set_sda_highz(card);

	वापस (पढ़ोb(card->cfg_base + PITA_GPIN) & PITA_GPIN_SDA) ? 1 : 0;
पूर्ण

अटल पूर्णांक pita_माला_लोcl(व्योम *data)
अणु
	काष्ठा peak_pciec_card *card = (काष्ठा peak_pciec_card *)data;

	/* set tristate */
	pita_set_scl_highz(card);

	वापस (पढ़ोb(card->cfg_base + PITA_GPIN) & PITA_GPIN_SCL) ? 1 : 0;
पूर्ण

/*
 * ग_लिखो commands to the LED chip though the I2C-bus of the PCAN-PCIeC
 */
अटल पूर्णांक peak_pciec_ग_लिखो_pca9553(काष्ठा peak_pciec_card *card,
				    u8 offset, u8 data)
अणु
	u8 buffer[2] = अणु
		offset,
		data
	पूर्ण;
	काष्ठा i2c_msg msg = अणु
		.addr = PCA9553_1_SLAVEADDR,
		.len = 2,
		.buf = buffer,
	पूर्ण;
	पूर्णांक ret;

	/* cache led mask */
	अगर ((offset == 5) && (data == card->led_cache))
		वापस 0;

	ret = i2c_transfer(&card->led_chip, &msg, 1);
	अगर (ret < 0)
		वापस ret;

	अगर (offset == 5)
		card->led_cache = data;

	वापस 0;
पूर्ण

/*
 * delayed work callback used to control the LEDs
 */
अटल व्योम peak_pciec_led_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा peak_pciec_card *card =
		container_of(work, काष्ठा peak_pciec_card, led_work.work);
	काष्ठा net_device *netdev;
	u8 new_led = card->led_cache;
	पूर्णांक i, up_count = 0;

	/* first check what is to करो */
	क्रम (i = 0; i < card->chan_count; i++) अणु
		/* शेष is: not configured */
		new_led &= ~PCA9553_LED_MASK(i);
		new_led |= PCA9553_LED_ON(i);

		netdev = card->channel[i].netdev;
		अगर (!netdev || !(netdev->flags & IFF_UP))
			जारी;

		up_count++;

		/* no activity (but configured) */
		new_led &= ~PCA9553_LED_MASK(i);
		new_led |= PCA9553_LED_SLOW(i);

		/* अगर bytes counters changed, set fast blinking led */
		अगर (netdev->stats.rx_bytes != card->channel[i].prev_rx_bytes) अणु
			card->channel[i].prev_rx_bytes = netdev->stats.rx_bytes;
			new_led &= ~PCA9553_LED_MASK(i);
			new_led |= PCA9553_LED_FAST(i);
		पूर्ण
		अगर (netdev->stats.tx_bytes != card->channel[i].prev_tx_bytes) अणु
			card->channel[i].prev_tx_bytes = netdev->stats.tx_bytes;
			new_led &= ~PCA9553_LED_MASK(i);
			new_led |= PCA9553_LED_FAST(i);
		पूर्ण
	पूर्ण

	/* check अगर LS0 settings changed, only update i2c अगर so */
	peak_pciec_ग_लिखो_pca9553(card, 5, new_led);

	/* restart समयr (except अगर no more configured channels) */
	अगर (up_count)
		schedule_delayed_work(&card->led_work, HZ);
पूर्ण

/*
 * set LEDs blinking state
 */
अटल व्योम peak_pciec_set_leds(काष्ठा peak_pciec_card *card, u8 led_mask, u8 s)
अणु
	u8 new_led = card->led_cache;
	पूर्णांक i;

	/* first check what is to करो */
	क्रम (i = 0; i < card->chan_count; i++)
		अगर (led_mask & PCA9553_LED(i)) अणु
			new_led &= ~PCA9553_LED_MASK(i);
			new_led |= PCA9553_LED_STATE(s, i);
		पूर्ण

	/* check अगर LS0 settings changed, only update i2c अगर so */
	peak_pciec_ग_लिखो_pca9553(card, 5, new_led);
पूर्ण

/*
 * start one second delayed work to control LEDs
 */
अटल व्योम peak_pciec_start_led_work(काष्ठा peak_pciec_card *card)
अणु
	schedule_delayed_work(&card->led_work, HZ);
पूर्ण

/*
 * stop LEDs delayed work
 */
अटल व्योम peak_pciec_stop_led_work(काष्ठा peak_pciec_card *card)
अणु
	cancel_delayed_work_sync(&card->led_work);
पूर्ण

/*
 * initialize the PCA9553 4-bit I2C-bus LED chip
 */
अटल पूर्णांक peak_pciec_init_leds(काष्ठा peak_pciec_card *card)
अणु
	पूर्णांक err;

	/* prescaler क्रम frequency 0: "SLOW" = 1 Hz = "44" */
	err = peak_pciec_ग_लिखो_pca9553(card, 1, 44 / 1);
	अगर (err)
		वापस err;

	/* duty cycle 0: 50% */
	err = peak_pciec_ग_लिखो_pca9553(card, 2, 0x80);
	अगर (err)
		वापस err;

	/* prescaler क्रम frequency 1: "FAST" = 5 Hz */
	err = peak_pciec_ग_लिखो_pca9553(card, 3, 44 / 5);
	अगर (err)
		वापस err;

	/* duty cycle 1: 50% */
	err = peak_pciec_ग_लिखो_pca9553(card, 4, 0x80);
	अगर (err)
		वापस err;

	/* चयन LEDs to initial state */
	वापस peak_pciec_ग_लिखो_pca9553(card, 5, PCA9553_LS0_INIT);
पूर्ण

/*
 * restore LEDs state to off peak_pciec_leds_निकास
 */
अटल व्योम peak_pciec_leds_निकास(काष्ठा peak_pciec_card *card)
अणु
	/* चयन LEDs to off */
	peak_pciec_ग_लिखो_pca9553(card, 5, PCA9553_LED_OFF_ALL);
पूर्ण

/*
 * normal ग_लिखो sja1000 रेजिस्टर method overloaded to catch when controller
 * is started or stopped, to control leds
 */
अटल व्योम peak_pciec_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
				 पूर्णांक port, u8 val)
अणु
	काष्ठा peak_pci_chan *chan = priv->priv;
	काष्ठा peak_pciec_card *card = chan->pciec_card;
	पूर्णांक c = (priv->reg_base - card->reg_base) / PEAK_PCI_CHAN_SIZE;

	/* sja1000 रेजिस्टर changes control the leds state */
	अगर (port == SJA1000_MOD)
		चयन (val) अणु
		हाल MOD_RM:
			/* Reset Mode: set led on */
			peak_pciec_set_leds(card, PCA9553_LED(c), PCA9553_ON);
			अवरोध;
		हाल 0x00:
			/* Normal Mode: led slow blinking and start led समयr */
			peak_pciec_set_leds(card, PCA9553_LED(c), PCA9553_SLOW);
			peak_pciec_start_led_work(card);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	/* call base function */
	peak_pci_ग_लिखो_reg(priv, port, val);
पूर्ण

अटल स्थिर काष्ठा i2c_algo_bit_data peak_pciec_i2c_bit_ops = अणु
	.setsda	= pita_setsda,
	.setscl	= pita_setscl,
	.माला_लोda	= pita_माला_लोda,
	.माला_लोcl	= pita_माला_लोcl,
	.udelay	= 10,
	.समयout = HZ,
पूर्ण;

अटल पूर्णांक peak_pciec_probe(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा peak_pci_chan *chan = priv->priv;
	काष्ठा peak_pciec_card *card;
	पूर्णांक err;

	/* copy i2c object address from 1st channel */
	अगर (chan->prev_dev) अणु
		काष्ठा sja1000_priv *prev_priv = netdev_priv(chan->prev_dev);
		काष्ठा peak_pci_chan *prev_chan = prev_priv->priv;

		card = prev_chan->pciec_card;
		अगर (!card)
			वापस -ENODEV;

	/* channel is the first one: करो the init part */
	पूर्ण अन्यथा अणु
		/* create the bit banging I2C adapter काष्ठाure */
		card = kzalloc(माप(काष्ठा peak_pciec_card), GFP_KERNEL);
		अगर (!card)
			वापस -ENOMEM;

		card->cfg_base = chan->cfg_base;
		card->reg_base = priv->reg_base;

		card->led_chip.owner = THIS_MODULE;
		card->led_chip.dev.parent = &pdev->dev;
		card->led_chip.algo_data = &card->i2c_bit;
		म_नकलन(card->led_chip.name, "peak_i2c",
			माप(card->led_chip.name));

		card->i2c_bit = peak_pciec_i2c_bit_ops;
		card->i2c_bit.udelay = 10;
		card->i2c_bit.समयout = HZ;
		card->i2c_bit.data = card;

		peak_pciec_init_pita_gpio(card);

		err = i2c_bit_add_bus(&card->led_chip);
		अगर (err) अणु
			dev_err(&pdev->dev, "i2c init failed\n");
			जाओ pciec_init_err_1;
		पूर्ण

		err = peak_pciec_init_leds(card);
		अगर (err) अणु
			dev_err(&pdev->dev, "leds hardware init failed\n");
			जाओ pciec_init_err_2;
		पूर्ण

		INIT_DELAYED_WORK(&card->led_work, peak_pciec_led_work);
		/* PCAN-ExpressCard needs its own callback क्रम leds */
		priv->ग_लिखो_reg = peak_pciec_ग_लिखो_reg;
	पूर्ण

	chan->pciec_card = card;
	card->channel[card->chan_count++].netdev = dev;

	वापस 0;

pciec_init_err_2:
	i2c_del_adapter(&card->led_chip);

pciec_init_err_1:
	peak_pciec_init_pita_gpio(card);
	kमुक्त(card);

	वापस err;
पूर्ण

अटल व्योम peak_pciec_हटाओ(काष्ठा peak_pciec_card *card)
अणु
	peak_pciec_stop_led_work(card);
	peak_pciec_leds_निकास(card);
	i2c_del_adapter(&card->led_chip);
	peak_pciec_init_pita_gpio(card);
	kमुक्त(card);
पूर्ण

#अन्यथा /* CONFIG_CAN_PEAK_PCIEC */

/*
 * Placebo functions when PCAN-ExpressCard support is not selected
 */
अटल अंतरभूत पूर्णांक peak_pciec_probe(काष्ठा pci_dev *pdev, काष्ठा net_device *dev)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम peak_pciec_हटाओ(काष्ठा peak_pciec_card *card)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_CAN_PEAK_PCIEC */

अटल u8 peak_pci_पढ़ो_reg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस पढ़ोb(priv->reg_base + (port << 2));
पूर्ण

अटल व्योम peak_pci_ग_लिखो_reg(स्थिर काष्ठा sja1000_priv *priv,
			       पूर्णांक port, u8 val)
अणु
	ग_लिखोb(val, priv->reg_base + (port << 2));
पूर्ण

अटल व्योम peak_pci_post_irq(स्थिर काष्ठा sja1000_priv *priv)
अणु
	काष्ठा peak_pci_chan *chan = priv->priv;
	u16 icr;

	/* Select and clear in PITA stored पूर्णांकerrupt */
	icr = पढ़ोw(chan->cfg_base + PITA_ICR);
	अगर (icr & chan->icr_mask)
		ग_लिखोw(chan->icr_mask, chan->cfg_base + PITA_ICR);
पूर्ण

अटल पूर्णांक peak_pci_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा sja1000_priv *priv;
	काष्ठा peak_pci_chan *chan;
	काष्ठा net_device *dev, *prev_dev;
	व्योम __iomem *cfg_base, *reg_base;
	u16 sub_sys_id, icr;
	पूर्णांक i, err, channels;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;

	err = pci_request_regions(pdev, DRV_NAME);
	अगर (err)
		जाओ failure_disable_pci;

	err = pci_पढ़ो_config_word(pdev, 0x2e, &sub_sys_id);
	अगर (err)
		जाओ failure_release_regions;

	dev_dbg(&pdev->dev, "probing device %04x:%04x:%04x\n",
		pdev->venकरोr, pdev->device, sub_sys_id);

	err = pci_ग_लिखो_config_word(pdev, 0x44, 0);
	अगर (err)
		जाओ failure_release_regions;

	अगर (sub_sys_id >= 12)
		channels = 4;
	अन्यथा अगर (sub_sys_id >= 10)
		channels = 3;
	अन्यथा अगर (sub_sys_id >= 4)
		channels = 2;
	अन्यथा
		channels = 1;

	cfg_base = pci_iomap(pdev, 0, PEAK_PCI_CFG_SIZE);
	अगर (!cfg_base) अणु
		dev_err(&pdev->dev, "failed to map PCI resource #0\n");
		err = -ENOMEM;
		जाओ failure_release_regions;
	पूर्ण

	reg_base = pci_iomap(pdev, 1, PEAK_PCI_CHAN_SIZE * channels);
	अगर (!reg_base) अणु
		dev_err(&pdev->dev, "failed to map PCI resource #1\n");
		err = -ENOMEM;
		जाओ failure_unmap_cfg_base;
	पूर्ण

	/* Set GPIO control रेजिस्टर */
	ग_लिखोw(0x0005, cfg_base + PITA_GPIOICR + 2);
	/* Enable all channels of this card */
	ग_लिखोb(0x00, cfg_base + PITA_GPIOICR);
	/* Toggle reset */
	ग_लिखोb(0x05, cfg_base + PITA_MISC + 3);
	usleep_range(5000, 6000);
	/* Leave parport mux mode */
	ग_लिखोb(0x04, cfg_base + PITA_MISC + 3);

	icr = पढ़ोw(cfg_base + PITA_ICR + 2);

	क्रम (i = 0; i < channels; i++) अणु
		dev = alloc_sja1000dev(माप(काष्ठा peak_pci_chan));
		अगर (!dev) अणु
			err = -ENOMEM;
			जाओ failure_हटाओ_channels;
		पूर्ण

		priv = netdev_priv(dev);
		chan = priv->priv;

		chan->cfg_base = cfg_base;
		priv->reg_base = reg_base + i * PEAK_PCI_CHAN_SIZE;

		priv->पढ़ो_reg = peak_pci_पढ़ो_reg;
		priv->ग_लिखो_reg = peak_pci_ग_लिखो_reg;
		priv->post_irq = peak_pci_post_irq;

		priv->can.घड़ी.freq = PEAK_PCI_CAN_CLOCK;
		priv->ocr = PEAK_PCI_OCR;
		priv->cdr = PEAK_PCI_CDR;
		/* Neither a slave nor a single device distributes the घड़ी */
		अगर (channels == 1 || i > 0)
			priv->cdr |= CDR_CLK_OFF;

		/* Setup पूर्णांकerrupt handling */
		priv->irq_flags = IRQF_SHARED;
		dev->irq = pdev->irq;

		chan->icr_mask = peak_pci_icr_masks[i];
		icr |= chan->icr_mask;

		SET_NETDEV_DEV(dev, &pdev->dev);
		dev->dev_id = i;

		/* Create chain of SJA1000 devices */
		chan->prev_dev = pci_get_drvdata(pdev);
		pci_set_drvdata(pdev, dev);

		/*
		 * PCAN-ExpressCard needs some additional i2c init.
		 * This must be करोne *beक्रमe* रेजिस्टर_sja1000dev() but
		 * *after* devices linkage
		 */
		अगर (pdev->device == PEAK_PCIEC_DEVICE_ID ||
		    pdev->device == PEAK_PCIEC34_DEVICE_ID) अणु
			err = peak_pciec_probe(pdev, dev);
			अगर (err) अणु
				dev_err(&pdev->dev,
					"failed to probe device (err %d)\n",
					err);
				जाओ failure_मुक्त_dev;
			पूर्ण
		पूर्ण

		err = रेजिस्टर_sja1000dev(dev);
		अगर (err) अणु
			dev_err(&pdev->dev, "failed to register device\n");
			जाओ failure_मुक्त_dev;
		पूर्ण

		dev_info(&pdev->dev,
			 "%s at reg_base=0x%p cfg_base=0x%p irq=%d\n",
			 dev->name, priv->reg_base, chan->cfg_base, dev->irq);
	पूर्ण

	/* Enable पूर्णांकerrupts */
	ग_लिखोw(icr, cfg_base + PITA_ICR + 2);

	वापस 0;

failure_मुक्त_dev:
	pci_set_drvdata(pdev, chan->prev_dev);
	मुक्त_sja1000dev(dev);

failure_हटाओ_channels:
	/* Disable पूर्णांकerrupts */
	ग_लिखोw(0x0, cfg_base + PITA_ICR + 2);

	chan = शून्य;
	क्रम (dev = pci_get_drvdata(pdev); dev; dev = prev_dev) अणु
		priv = netdev_priv(dev);
		chan = priv->priv;
		prev_dev = chan->prev_dev;

		unरेजिस्टर_sja1000dev(dev);
		मुक्त_sja1000dev(dev);
	पूर्ण

	/* मुक्त any PCIeC resources too */
	अगर (chan && chan->pciec_card)
		peak_pciec_हटाओ(chan->pciec_card);

	pci_iounmap(pdev, reg_base);

failure_unmap_cfg_base:
	pci_iounmap(pdev, cfg_base);

failure_release_regions:
	pci_release_regions(pdev);

failure_disable_pci:
	pci_disable_device(pdev);

	/* pci_xxx_config_word() वापस positive PCIBIOS_xxx error codes जबतक
	 * the probe() function must वापस a negative त्रुटि_सं in हाल of failure
	 * (err is unchanged अगर negative) */
	वापस pcibios_err_to_त्रुटि_सं(err);
पूर्ण

अटल व्योम peak_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *dev = pci_get_drvdata(pdev); /* Last device */
	काष्ठा sja1000_priv *priv = netdev_priv(dev);
	काष्ठा peak_pci_chan *chan = priv->priv;
	व्योम __iomem *cfg_base = chan->cfg_base;
	व्योम __iomem *reg_base = priv->reg_base;

	/* Disable पूर्णांकerrupts */
	ग_लिखोw(0x0, cfg_base + PITA_ICR + 2);

	/* Loop over all रेजिस्टरed devices */
	जबतक (1) अणु
		काष्ठा net_device *prev_dev = chan->prev_dev;

		dev_info(&pdev->dev, "removing device %s\n", dev->name);
		unरेजिस्टर_sja1000dev(dev);
		मुक्त_sja1000dev(dev);
		dev = prev_dev;

		अगर (!dev) अणु
			/* करो that only क्रम first channel */
			अगर (chan->pciec_card)
				peak_pciec_हटाओ(chan->pciec_card);
			अवरोध;
		पूर्ण
		priv = netdev_priv(dev);
		chan = priv->priv;
	पूर्ण

	pci_iounmap(pdev, reg_base);
	pci_iounmap(pdev, cfg_base);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल काष्ठा pci_driver peak_pci_driver = अणु
	.name = DRV_NAME,
	.id_table = peak_pci_tbl,
	.probe = peak_pci_probe,
	.हटाओ = peak_pci_हटाओ,
पूर्ण;

module_pci_driver(peak_pci_driver);
