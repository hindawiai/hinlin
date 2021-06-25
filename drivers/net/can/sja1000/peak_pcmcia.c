<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010-2012 Stephane Grosjean <s.grosjean@peak-प्रणाली.com>
 *
 * CAN driver क्रम PEAK-System PCAN-PC Card
 * Derived from the PCAN project file driver/src/pcan_pccard.c
 * Copyright (C) 2006-2010 PEAK System-Technik GmbH
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <pcmcia/cistpl.h>
#समावेश <pcmcia/ds.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश "sja1000.h"

MODULE_AUTHOR("Stephane Grosjean <s.grosjean@peak-system.com>");
MODULE_DESCRIPTION("CAN driver for PEAK-System PCAN-PC Cards");
MODULE_LICENSE("GPL v2");

/* PEAK-System PCMCIA driver name */
#घोषणा PCC_NAME		"peak_pcmcia"

#घोषणा PCC_CHAN_MAX		2

#घोषणा PCC_CAN_CLOCK		(16000000 / 2)

#घोषणा PCC_MANF_ID		0x0377
#घोषणा PCC_CARD_ID		0x0001

#घोषणा PCC_CHAN_SIZE		0x20
#घोषणा PCC_CHAN_OFF(c)		((c) * PCC_CHAN_SIZE)
#घोषणा PCC_COMN_OFF		(PCC_CHAN_OFF(PCC_CHAN_MAX))
#घोषणा PCC_COMN_SIZE		0x40

/* common area रेजिस्टरs */
#घोषणा PCC_CCR			0x00
#घोषणा PCC_CSR			0x02
#घोषणा PCC_CPR			0x04
#घोषणा PCC_SPI_सूची		0x06
#घोषणा PCC_SPI_DOR		0x08
#घोषणा PCC_SPI_ADR		0x0a
#घोषणा PCC_SPI_IR		0x0c
#घोषणा PCC_FW_MAJOR		0x10
#घोषणा PCC_FW_MINOR		0x12

/* CCR bits */
#घोषणा PCC_CCR_CLK_16		0x00
#घोषणा PCC_CCR_CLK_10		0x01
#घोषणा PCC_CCR_CLK_21		0x02
#घोषणा PCC_CCR_CLK_8		0x03
#घोषणा PCC_CCR_CLK_MASK	PCC_CCR_CLK_8

#घोषणा PCC_CCR_RST_CHAN(c)	(0x01 << ((c) + 2))
#घोषणा PCC_CCR_RST_ALL		(PCC_CCR_RST_CHAN(0) | PCC_CCR_RST_CHAN(1))
#घोषणा PCC_CCR_RST_MASK	PCC_CCR_RST_ALL

/* led selection bits */
#घोषणा PCC_LED(c)		(1 << (c))
#घोषणा PCC_LED_ALL		(PCC_LED(0) | PCC_LED(1))

/* led state value */
#घोषणा PCC_LED_ON		0x00
#घोषणा PCC_LED_FAST		0x01
#घोषणा PCC_LED_SLOW		0x02
#घोषणा PCC_LED_OFF		0x03

#घोषणा PCC_CCR_LED_CHAN(s, c)	((s) << (((c) + 2) << 1))

#घोषणा PCC_CCR_LED_ON_CHAN(c)		PCC_CCR_LED_CHAN(PCC_LED_ON, c)
#घोषणा PCC_CCR_LED_FAST_CHAN(c)	PCC_CCR_LED_CHAN(PCC_LED_FAST, c)
#घोषणा PCC_CCR_LED_SLOW_CHAN(c)	PCC_CCR_LED_CHAN(PCC_LED_SLOW, c)
#घोषणा PCC_CCR_LED_OFF_CHAN(c)		PCC_CCR_LED_CHAN(PCC_LED_OFF, c)
#घोषणा PCC_CCR_LED_MASK_CHAN(c)	PCC_CCR_LED_OFF_CHAN(c)
#घोषणा PCC_CCR_LED_OFF_ALL		(PCC_CCR_LED_OFF_CHAN(0) | \
					 PCC_CCR_LED_OFF_CHAN(1))
#घोषणा PCC_CCR_LED_MASK		PCC_CCR_LED_OFF_ALL

#घोषणा PCC_CCR_INIT	(PCC_CCR_CLK_16 | PCC_CCR_RST_ALL | PCC_CCR_LED_OFF_ALL)

/* CSR bits */
#घोषणा PCC_CSR_SPI_BUSY		0x04

/* समय रुकोing क्रम SPI busy (prevent from infinite loop) */
#घोषणा PCC_SPI_MAX_BUSY_WAIT_MS	3

/* max count of पढ़ोing the SPI status रेजिस्टर रुकोing क्रम a change */
/* (prevent from infinite loop) */
#घोषणा PCC_WRITE_MAX_LOOP		1000

/* max nb of पूर्णांक handled by that isr in one shot (prevent from infinite loop) */
#घोषणा PCC_ISR_MAX_LOOP		10

/* EEPROM chip inकाष्ठाion set */
/* note: EEPROM Read/Write inकाष्ठाions include A8 bit */
#घोषणा PCC_EEP_WRITE(a)	(0x02 | (((a) & 0x100) >> 5))
#घोषणा PCC_EEP_READ(a)		(0x03 | (((a) & 0x100) >> 5))
#घोषणा PCC_EEP_WRDI		0x04	/* EEPROM Write Disable */
#घोषणा PCC_EEP_RDSR		0x05	/* EEPROM Read Status Register */
#घोषणा PCC_EEP_WREN		0x06	/* EEPROM Write Enable */

/* EEPROM Status Register bits */
#घोषणा PCC_EEP_SR_WEN		0x02	/* EEPROM SR Write Enable bit */
#घोषणा PCC_EEP_SR_WIP		0x01	/* EEPROM SR Write In Progress bit */

/*
 * The board configuration is probably following:
 * RX1 is connected to ground.
 * TX1 is not connected.
 * CLKO is not connected.
 * Setting the OCR रेजिस्टर to 0xDA is a good idea.
 * This means normal output mode, push-pull and the correct polarity.
 */
#घोषणा PCC_OCR			(OCR_TX0_PUSHPULL | OCR_TX1_PUSHPULL)

/*
 * In the CDR रेजिस्टर, you should set CBP to 1.
 * You will probably also want to set the घड़ी भागider value to 7
 * (meaning direct oscillator output) because the second SJA1000 chip
 * is driven by the first one CLKOUT output.
 */
#घोषणा PCC_CDR			(CDR_CBP | CDR_CLKOUT_MASK)

काष्ठा pcan_channel अणु
	काष्ठा net_device *netdev;
	अचिन्हित दीर्घ prev_rx_bytes;
	अचिन्हित दीर्घ prev_tx_bytes;
पूर्ण;

/* PCAN-PC Card निजी काष्ठाure */
काष्ठा pcan_pccard अणु
	काष्ठा pcmcia_device *pdev;
	पूर्णांक chan_count;
	काष्ठा pcan_channel channel[PCC_CHAN_MAX];
	u8 ccr;
	u8 fw_major;
	u8 fw_minor;
	व्योम __iomem *ioport_addr;
	काष्ठा समयr_list led_समयr;
पूर्ण;

अटल काष्ठा pcmcia_device_id pcan_table[] = अणु
	PCMCIA_DEVICE_MANF_CARD(PCC_MANF_ID, PCC_CARD_ID),
	PCMCIA_DEVICE_शून्य,
पूर्ण;

MODULE_DEVICE_TABLE(pcmcia, pcan_table);

अटल व्योम pcan_set_leds(काष्ठा pcan_pccard *card, u8 mask, u8 state);

/*
 * start समयr which controls leds state
 */
अटल व्योम pcan_start_led_समयr(काष्ठा pcan_pccard *card)
अणु
	अगर (!समयr_pending(&card->led_समयr))
		mod_समयr(&card->led_समयr, jअगरfies + HZ);
पूर्ण

/*
 * stop the समयr which controls leds state
 */
अटल व्योम pcan_stop_led_समयr(काष्ठा pcan_pccard *card)
अणु
	del_समयr_sync(&card->led_समयr);
पूर्ण

/*
 * पढ़ो a sja1000 रेजिस्टर
 */
अटल u8 pcan_पढ़ो_canreg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port)
अणु
	वापस ioपढ़ो8(priv->reg_base + port);
पूर्ण

/*
 * ग_लिखो a sja1000 रेजिस्टर
 */
अटल व्योम pcan_ग_लिखो_canreg(स्थिर काष्ठा sja1000_priv *priv, पूर्णांक port, u8 v)
अणु
	काष्ठा pcan_pccard *card = priv->priv;
	पूर्णांक c = (priv->reg_base - card->ioport_addr) / PCC_CHAN_SIZE;

	/* sja1000 रेजिस्टर changes control the leds state */
	अगर (port == SJA1000_MOD)
		चयन (v) अणु
		हाल MOD_RM:
			/* Reset Mode: set led on */
			pcan_set_leds(card, PCC_LED(c), PCC_LED_ON);
			अवरोध;
		हाल 0x00:
			/* Normal Mode: led slow blinking and start led समयr */
			pcan_set_leds(card, PCC_LED(c), PCC_LED_SLOW);
			pcan_start_led_समयr(card);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

	ioग_लिखो8(v, priv->reg_base + port);
पूर्ण

/*
 * पढ़ो a रेजिस्टर from the common area
 */
अटल u8 pcan_पढ़ो_reg(काष्ठा pcan_pccard *card, पूर्णांक port)
अणु
	वापस ioपढ़ो8(card->ioport_addr + PCC_COMN_OFF + port);
पूर्ण

/*
 * ग_लिखो a रेजिस्टर पूर्णांकo the common area
 */
अटल व्योम pcan_ग_लिखो_reg(काष्ठा pcan_pccard *card, पूर्णांक port, u8 v)
अणु
	/* cache ccr value */
	अगर (port == PCC_CCR) अणु
		अगर (card->ccr == v)
			वापस;
		card->ccr = v;
	पूर्ण

	ioग_लिखो8(v, card->ioport_addr + PCC_COMN_OFF + port);
पूर्ण

/*
 * check whether the card is present by checking its fw version numbers
 * against values पढ़ो at probing समय.
 */
अटल अंतरभूत पूर्णांक pcan_pccard_present(काष्ठा pcan_pccard *card)
अणु
	वापस ((pcan_पढ़ो_reg(card, PCC_FW_MAJOR) == card->fw_major) &&
		(pcan_पढ़ो_reg(card, PCC_FW_MINOR) == card->fw_minor));
पूर्ण

/*
 * रुको क्रम SPI engine जबतक it is busy
 */
अटल पूर्णांक pcan_रुको_spi_busy(काष्ठा pcan_pccard *card)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies +
				msecs_to_jअगरfies(PCC_SPI_MAX_BUSY_WAIT_MS) + 1;

	/* be sure to पढ़ो status at least once after sleeping */
	जबतक (pcan_पढ़ो_reg(card, PCC_CSR) & PCC_CSR_SPI_BUSY) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -EBUSY;
		schedule();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ग_लिखो data in device eeprom
 */
अटल पूर्णांक pcan_ग_लिखो_eeprom(काष्ठा pcan_pccard *card, u16 addr, u8 v)
अणु
	u8 status;
	पूर्णांक err, i;

	/* ग_लिखो inकाष्ठाion enabling ग_लिखो */
	pcan_ग_लिखो_reg(card, PCC_SPI_IR, PCC_EEP_WREN);
	err = pcan_रुको_spi_busy(card);
	अगर (err)
		जाओ we_spi_err;

	/* रुको until ग_लिखो enabled */
	क्रम (i = 0; i < PCC_WRITE_MAX_LOOP; i++) अणु
		/* ग_लिखो inकाष्ठाion पढ़ोing the status रेजिस्टर */
		pcan_ग_लिखो_reg(card, PCC_SPI_IR, PCC_EEP_RDSR);
		err = pcan_रुको_spi_busy(card);
		अगर (err)
			जाओ we_spi_err;

		/* get status रेजिस्टर value and check ग_लिखो enable bit */
		status = pcan_पढ़ो_reg(card, PCC_SPI_सूची);
		अगर (status & PCC_EEP_SR_WEN)
			अवरोध;
	पूर्ण

	अगर (i >= PCC_WRITE_MAX_LOOP) अणु
		dev_err(&card->pdev->dev,
			"stop waiting to be allowed to write in eeprom\n");
		वापस -EIO;
	पूर्ण

	/* set address and data */
	pcan_ग_लिखो_reg(card, PCC_SPI_ADR, addr & 0xff);
	pcan_ग_लिखो_reg(card, PCC_SPI_DOR, v);

	/*
	 * ग_लिखो inकाष्ठाion with bit[3] set according to address value:
	 * अगर addr refers to upper half of the memory array: bit[3] = 1
	 */
	pcan_ग_लिखो_reg(card, PCC_SPI_IR, PCC_EEP_WRITE(addr));
	err = pcan_रुको_spi_busy(card);
	अगर (err)
		जाओ we_spi_err;

	/* रुको जबतक ग_लिखो in progress */
	क्रम (i = 0; i < PCC_WRITE_MAX_LOOP; i++) अणु
		/* ग_लिखो inकाष्ठाion पढ़ोing the status रेजिस्टर */
		pcan_ग_लिखो_reg(card, PCC_SPI_IR, PCC_EEP_RDSR);
		err = pcan_रुको_spi_busy(card);
		अगर (err)
			जाओ we_spi_err;

		/* get status रेजिस्टर value and check ग_लिखो in progress bit */
		status = pcan_पढ़ो_reg(card, PCC_SPI_सूची);
		अगर (!(status & PCC_EEP_SR_WIP))
			अवरोध;
	पूर्ण

	अगर (i >= PCC_WRITE_MAX_LOOP) अणु
		dev_err(&card->pdev->dev,
			"stop waiting for write in eeprom to complete\n");
		वापस -EIO;
	पूर्ण

	/* ग_लिखो inकाष्ठाion disabling ग_लिखो */
	pcan_ग_लिखो_reg(card, PCC_SPI_IR, PCC_EEP_WRDI);
	err = pcan_रुको_spi_busy(card);
	अगर (err)
		जाओ we_spi_err;

	वापस 0;

we_spi_err:
	dev_err(&card->pdev->dev,
		"stop waiting (spi engine always busy) err %d\n", err);

	वापस err;
पूर्ण

अटल व्योम pcan_set_leds(काष्ठा pcan_pccard *card, u8 led_mask, u8 state)
अणु
	u8 ccr = card->ccr;
	पूर्णांक i;

	क्रम (i = 0; i < card->chan_count; i++)
		अगर (led_mask & PCC_LED(i)) अणु
			/* clear corresponding led bits in ccr */
			ccr &= ~PCC_CCR_LED_MASK_CHAN(i);
			/* then set new bits */
			ccr |= PCC_CCR_LED_CHAN(state, i);
		पूर्ण

	/* real ग_लिखो only अगर something has changed in ccr */
	pcan_ग_लिखो_reg(card, PCC_CCR, ccr);
पूर्ण

/*
 * enable/disable CAN connectors घातer
 */
अटल अंतरभूत व्योम pcan_set_can_घातer(काष्ठा pcan_pccard *card, पूर्णांक onoff)
अणु
	पूर्णांक err;

	err = pcan_ग_लिखो_eeprom(card, 0, !!onoff);
	अगर (err)
		dev_err(&card->pdev->dev,
			"failed setting power %s to can connectors (err %d)\n",
			(onoff) ? "on" : "off", err);
पूर्ण

/*
 * set leds state according to channel activity
 */
अटल व्योम pcan_led_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा pcan_pccard *card = from_समयr(card, t, led_समयr);
	काष्ठा net_device *netdev;
	पूर्णांक i, up_count = 0;
	u8 ccr;

	ccr = card->ccr;
	क्रम (i = 0; i < card->chan_count; i++) अणु
		/* शेष is: not configured */
		ccr &= ~PCC_CCR_LED_MASK_CHAN(i);
		ccr |= PCC_CCR_LED_ON_CHAN(i);

		netdev = card->channel[i].netdev;
		अगर (!netdev || !(netdev->flags & IFF_UP))
			जारी;

		up_count++;

		/* no activity (but configured) */
		ccr &= ~PCC_CCR_LED_MASK_CHAN(i);
		ccr |= PCC_CCR_LED_SLOW_CHAN(i);

		/* अगर bytes counters changed, set fast blinking led */
		अगर (netdev->stats.rx_bytes != card->channel[i].prev_rx_bytes) अणु
			card->channel[i].prev_rx_bytes = netdev->stats.rx_bytes;
			ccr &= ~PCC_CCR_LED_MASK_CHAN(i);
			ccr |= PCC_CCR_LED_FAST_CHAN(i);
		पूर्ण
		अगर (netdev->stats.tx_bytes != card->channel[i].prev_tx_bytes) अणु
			card->channel[i].prev_tx_bytes = netdev->stats.tx_bytes;
			ccr &= ~PCC_CCR_LED_MASK_CHAN(i);
			ccr |= PCC_CCR_LED_FAST_CHAN(i);
		पूर्ण
	पूर्ण

	/* ग_लिखो the new leds state */
	pcan_ग_लिखो_reg(card, PCC_CCR, ccr);

	/* restart समयr (except अगर no more configured channels) */
	अगर (up_count)
		mod_समयr(&card->led_समयr, jअगरfies + HZ);
पूर्ण

/*
 * पूर्णांकerrupt service routine
 */
अटल irqवापस_t pcan_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcan_pccard *card = dev_id;
	पूर्णांक irq_handled;

	/* prevent from infinite loop */
	क्रम (irq_handled = 0; irq_handled < PCC_ISR_MAX_LOOP; irq_handled++) अणु
		/* handle shared पूर्णांकerrupt and next loop */
		पूर्णांक nothing_to_handle = 1;
		पूर्णांक i;

		/* check पूर्णांकerrupt क्रम each channel */
		क्रम (i = 0; i < card->chan_count; i++) अणु
			काष्ठा net_device *netdev;

			/*
			 * check whether the card is present beक्रमe calling
			 * sja1000_पूर्णांकerrupt() to speed up hotplug detection
			 */
			अगर (!pcan_pccard_present(card)) अणु
				/* card unplugged during isr */
				वापस IRQ_NONE;
			पूर्ण

			/*
			 * should check whether all or SJA1000_MAX_IRQ
			 * पूर्णांकerrupts have been handled: loop again to be sure.
			 */
			netdev = card->channel[i].netdev;
			अगर (netdev &&
			    sja1000_पूर्णांकerrupt(irq, netdev) == IRQ_HANDLED)
				nothing_to_handle = 0;
		पूर्ण

		अगर (nothing_to_handle)
			अवरोध;
	पूर्ण

	वापस (irq_handled) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

/*
 * मुक्त all resources used by the channels and चयन off leds and can घातer
 */
अटल व्योम pcan_मुक्त_channels(काष्ठा pcan_pccard *card)
अणु
	पूर्णांक i;
	u8 led_mask = 0;

	क्रम (i = 0; i < card->chan_count; i++) अणु
		काष्ठा net_device *netdev;
		अक्षर name[IFNAMSIZ];

		led_mask |= PCC_LED(i);

		netdev = card->channel[i].netdev;
		अगर (!netdev)
			जारी;

		strlcpy(name, netdev->name, IFNAMSIZ);

		unरेजिस्टर_sja1000dev(netdev);

		मुक्त_sja1000dev(netdev);

		dev_info(&card->pdev->dev, "%s removed\n", name);
	पूर्ण

	/* करो it only अगर device not हटाओd */
	अगर (pcan_pccard_present(card)) अणु
		pcan_set_leds(card, led_mask, PCC_LED_OFF);
		pcan_set_can_घातer(card, 0);
	पूर्ण
पूर्ण

/*
 * check अगर a CAN controller is present at the specअगरied location
 */
अटल अंतरभूत पूर्णांक pcan_channel_present(काष्ठा sja1000_priv *priv)
अणु
	/* make sure SJA1000 is in reset mode */
	pcan_ग_लिखो_canreg(priv, SJA1000_MOD, 1);
	pcan_ग_लिखो_canreg(priv, SJA1000_CDR, CDR_PELICAN);

	/* पढ़ो reset-values */
	अगर (pcan_पढ़ो_canreg(priv, SJA1000_CDR) == CDR_PELICAN)
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pcan_add_channels(काष्ठा pcan_pccard *card)
अणु
	काष्ठा pcmcia_device *pdev = card->pdev;
	पूर्णांक i, err = 0;
	u8 ccr = PCC_CCR_INIT;

	/* init common रेजिस्टरs (reset channels and leds off) */
	card->ccr = ~ccr;
	pcan_ग_लिखो_reg(card, PCC_CCR, ccr);

	/* रुको 2ms beक्रमe unresetting channels */
	usleep_range(2000, 3000);

	ccr &= ~PCC_CCR_RST_ALL;
	pcan_ग_लिखो_reg(card, PCC_CCR, ccr);

	/* create one network device per channel detected */
	क्रम (i = 0; i < ARRAY_SIZE(card->channel); i++) अणु
		काष्ठा net_device *netdev;
		काष्ठा sja1000_priv *priv;

		netdev = alloc_sja1000dev(0);
		अगर (!netdev) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		/* update linkages */
		priv = netdev_priv(netdev);
		priv->priv = card;
		SET_NETDEV_DEV(netdev, &pdev->dev);
		netdev->dev_id = i;

		priv->irq_flags = IRQF_SHARED;
		netdev->irq = pdev->irq;
		priv->reg_base = card->ioport_addr + PCC_CHAN_OFF(i);

		/* check अगर channel is present */
		अगर (!pcan_channel_present(priv)) अणु
			dev_err(&pdev->dev, "channel %d not present\n", i);
			मुक्त_sja1000dev(netdev);
			जारी;
		पूर्ण

		priv->पढ़ो_reg  = pcan_पढ़ो_canreg;
		priv->ग_लिखो_reg = pcan_ग_लिखो_canreg;
		priv->can.घड़ी.freq = PCC_CAN_CLOCK;
		priv->ocr = PCC_OCR;
		priv->cdr = PCC_CDR;

		/* Neither a slave device distributes the घड़ी */
		अगर (i > 0)
			priv->cdr |= CDR_CLK_OFF;

		priv->flags |= SJA1000_CUSTOM_IRQ_HANDLER;

		/* रेजिस्टर SJA1000 device */
		err = रेजिस्टर_sja1000dev(netdev);
		अगर (err) अणु
			मुक्त_sja1000dev(netdev);
			जारी;
		पूर्ण

		card->channel[i].netdev = netdev;
		card->chan_count++;

		/* set corresponding led on in the new ccr */
		ccr &= ~PCC_CCR_LED_OFF_CHAN(i);

		dev_info(&pdev->dev,
			"%s on channel %d at 0x%p irq %d\n",
			netdev->name, i, priv->reg_base, pdev->irq);
	पूर्ण

	/* ग_लिखो new ccr (change leds state) */
	pcan_ग_लिखो_reg(card, PCC_CCR, ccr);

	वापस err;
पूर्ण

अटल पूर्णांक pcan_conf_check(काष्ठा pcmcia_device *pdev, व्योम *priv_data)
अणु
	pdev->resource[0]->flags &= ~IO_DATA_PATH_WIDTH;
	pdev->resource[0]->flags |= IO_DATA_PATH_WIDTH_8; /* only */
	pdev->io_lines = 10;

	/* This reserves IO space but करोesn't actually enable it */
	वापस pcmcia_request_io(pdev);
पूर्ण

/*
 * मुक्त all resources used by the device
 */
अटल व्योम pcan_मुक्त(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा pcan_pccard *card = pdev->priv;

	अगर (!card)
		वापस;

	मुक्त_irq(pdev->irq, card);
	pcan_stop_led_समयr(card);

	pcan_मुक्त_channels(card);

	ioport_unmap(card->ioport_addr);

	kमुक्त(card);
	pdev->priv = शून्य;
पूर्ण

/*
 * setup PCMCIA socket and probe क्रम PEAK-System PC-CARD
 */
अटल पूर्णांक pcan_probe(काष्ठा pcmcia_device *pdev)
अणु
	काष्ठा pcan_pccard *card;
	पूर्णांक err;

	pdev->config_flags |= CONF_ENABLE_IRQ | CONF_AUTO_SET_IO;

	err = pcmcia_loop_config(pdev, pcan_conf_check, शून्य);
	अगर (err) अणु
		dev_err(&pdev->dev, "pcmcia_loop_config() error %d\n", err);
		जाओ probe_err_1;
	पूर्ण

	अगर (!pdev->irq) अणु
		dev_err(&pdev->dev, "no irq assigned\n");
		err = -ENODEV;
		जाओ probe_err_1;
	पूर्ण

	err = pcmcia_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "pcmcia_enable_device failed err=%d\n",
			err);
		जाओ probe_err_1;
	पूर्ण

	card = kzalloc(माप(काष्ठा pcan_pccard), GFP_KERNEL);
	अगर (!card) अणु
		err = -ENOMEM;
		जाओ probe_err_2;
	पूर्ण

	card->pdev = pdev;
	pdev->priv = card;

	/* sja1000 api uses iomem */
	card->ioport_addr = ioport_map(pdev->resource[0]->start,
					resource_size(pdev->resource[0]));
	अगर (!card->ioport_addr) अणु
		dev_err(&pdev->dev, "couldn't map io port into io memory\n");
		err = -ENOMEM;
		जाओ probe_err_3;
	पूर्ण
	card->fw_major = pcan_पढ़ो_reg(card, PCC_FW_MAJOR);
	card->fw_minor = pcan_पढ़ो_reg(card, PCC_FW_MINOR);

	/* display board name and firmware version */
	dev_info(&pdev->dev, "PEAK-System pcmcia card %s fw %d.%d\n",
		pdev->prod_id[1] ? pdev->prod_id[1] : "PCAN-PC Card",
		card->fw_major, card->fw_minor);

	/* detect available channels */
	pcan_add_channels(card);
	अगर (!card->chan_count) अणु
		err = -ENOMEM;
		जाओ probe_err_4;
	पूर्ण

	/* init the समयr which controls the leds */
	समयr_setup(&card->led_समयr, pcan_led_समयr, 0);

	/* request the given irq */
	err = request_irq(pdev->irq, &pcan_isr, IRQF_SHARED, PCC_NAME, card);
	अगर (err) अणु
		dev_err(&pdev->dev, "couldn't request irq%d\n", pdev->irq);
		जाओ probe_err_5;
	पूर्ण

	/* घातer on the connectors */
	pcan_set_can_घातer(card, 1);

	वापस 0;

probe_err_5:
	/* unरेजिस्टर can devices from network */
	pcan_मुक्त_channels(card);

probe_err_4:
	ioport_unmap(card->ioport_addr);

probe_err_3:
	kमुक्त(card);
	pdev->priv = शून्य;

probe_err_2:
	pcmcia_disable_device(pdev);

probe_err_1:
	वापस err;
पूर्ण

/*
 * release claimed resources
 */
अटल व्योम pcan_हटाओ(काष्ठा pcmcia_device *pdev)
अणु
	pcan_मुक्त(pdev);
	pcmcia_disable_device(pdev);
पूर्ण

अटल काष्ठा pcmcia_driver pcan_driver = अणु
	.name = PCC_NAME,
	.probe = pcan_probe,
	.हटाओ = pcan_हटाओ,
	.id_table = pcan_table,
पूर्ण;
module_pcmcia_driver(pcan_driver);
