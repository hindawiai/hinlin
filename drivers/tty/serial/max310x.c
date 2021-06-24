<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Maxim (Dallas) MAX3107/8/9, MAX14830 serial driver
 *
 *  Copyright (C) 2012-2016 Alexander Shiyan <shc_work@mail.ru>
 *
 *  Based on max3100.c, by Christian Pellegrin <chripell@evolware.org>
 *  Based on max3110.c, by Feng Tang <feng.tang@पूर्णांकel.com>
 *  Based on max3107.c, by Aavamobile
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/uaccess.h>

#घोषणा MAX310X_NAME			"max310x"
#घोषणा MAX310X_MAJOR			204
#घोषणा MAX310X_MINOR			209
#घोषणा MAX310X_UART_NRMAX		16

/* MAX310X रेजिस्टर definitions */
#घोषणा MAX310X_RHR_REG			(0x00) /* RX FIFO */
#घोषणा MAX310X_THR_REG			(0x00) /* TX FIFO */
#घोषणा MAX310X_IRQEN_REG		(0x01) /* IRQ enable */
#घोषणा MAX310X_IRQSTS_REG		(0x02) /* IRQ status */
#घोषणा MAX310X_LSR_IRQEN_REG		(0x03) /* LSR IRQ enable */
#घोषणा MAX310X_LSR_IRQSTS_REG		(0x04) /* LSR IRQ status */
#घोषणा MAX310X_REG_05			(0x05)
#घोषणा MAX310X_SPCHR_IRQEN_REG		MAX310X_REG_05 /* Special अक्षर IRQ en */
#घोषणा MAX310X_SPCHR_IRQSTS_REG	(0x06) /* Special अक्षर IRQ status */
#घोषणा MAX310X_STS_IRQEN_REG		(0x07) /* Status IRQ enable */
#घोषणा MAX310X_STS_IRQSTS_REG		(0x08) /* Status IRQ status */
#घोषणा MAX310X_MODE1_REG		(0x09) /* MODE1 */
#घोषणा MAX310X_MODE2_REG		(0x0a) /* MODE2 */
#घोषणा MAX310X_LCR_REG			(0x0b) /* LCR */
#घोषणा MAX310X_RXTO_REG		(0x0c) /* RX समयout */
#घोषणा MAX310X_HDPIXDELAY_REG		(0x0d) /* Auto transceiver delays */
#घोषणा MAX310X_IRDA_REG		(0x0e) /* IRDA settings */
#घोषणा MAX310X_FLOWLVL_REG		(0x0f) /* Flow control levels */
#घोषणा MAX310X_FIFOTRIGLVL_REG		(0x10) /* FIFO IRQ trigger levels */
#घोषणा MAX310X_TXFIFOLVL_REG		(0x11) /* TX FIFO level */
#घोषणा MAX310X_RXFIFOLVL_REG		(0x12) /* RX FIFO level */
#घोषणा MAX310X_FLOWCTRL_REG		(0x13) /* Flow control */
#घोषणा MAX310X_XON1_REG		(0x14) /* XON1 अक्षरacter */
#घोषणा MAX310X_XON2_REG		(0x15) /* XON2 अक्षरacter */
#घोषणा MAX310X_XOFF1_REG		(0x16) /* XOFF1 अक्षरacter */
#घोषणा MAX310X_XOFF2_REG		(0x17) /* XOFF2 अक्षरacter */
#घोषणा MAX310X_GPIOCFG_REG		(0x18) /* GPIO config */
#घोषणा MAX310X_GPIODATA_REG		(0x19) /* GPIO data */
#घोषणा MAX310X_PLLCFG_REG		(0x1a) /* PLL config */
#घोषणा MAX310X_BRGCFG_REG		(0x1b) /* Baud rate generator conf */
#घोषणा MAX310X_BRGDIVLSB_REG		(0x1c) /* Baud rate भागisor LSB */
#घोषणा MAX310X_BRGDIVMSB_REG		(0x1d) /* Baud rate भागisor MSB */
#घोषणा MAX310X_CLKSRC_REG		(0x1e) /* Clock source */
#घोषणा MAX310X_REG_1F			(0x1f)

#घोषणा MAX310X_REVID_REG		MAX310X_REG_1F /* Revision ID */

#घोषणा MAX310X_GLOBALIRQ_REG		MAX310X_REG_1F /* Global IRQ (RO) */
#घोषणा MAX310X_GLOBALCMD_REG		MAX310X_REG_1F /* Global Command (WO) */

/* Extended रेजिस्टरs */
#घोषणा MAX310X_REVID_EXTREG		MAX310X_REG_05 /* Revision ID */

/* IRQ रेजिस्टर bits */
#घोषणा MAX310X_IRQ_LSR_BIT		(1 << 0) /* LSR पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_SPCHR_BIT		(1 << 1) /* Special अक्षर पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_STS_BIT		(1 << 2) /* Status पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_RXFIFO_BIT		(1 << 3) /* RX FIFO पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_TXFIFO_BIT		(1 << 4) /* TX FIFO पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_TXEMPTY_BIT		(1 << 5) /* TX FIFO empty पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_RXEMPTY_BIT		(1 << 6) /* RX FIFO empty पूर्णांकerrupt */
#घोषणा MAX310X_IRQ_CTS_BIT		(1 << 7) /* CTS पूर्णांकerrupt */

/* LSR रेजिस्टर bits */
#घोषणा MAX310X_LSR_RXTO_BIT		(1 << 0) /* RX समयout */
#घोषणा MAX310X_LSR_RXOVR_BIT		(1 << 1) /* RX overrun */
#घोषणा MAX310X_LSR_RXPAR_BIT		(1 << 2) /* RX parity error */
#घोषणा MAX310X_LSR_FRERR_BIT		(1 << 3) /* Frame error */
#घोषणा MAX310X_LSR_RXBRK_BIT		(1 << 4) /* RX अवरोध */
#घोषणा MAX310X_LSR_RXNOISE_BIT		(1 << 5) /* RX noise */
#घोषणा MAX310X_LSR_CTS_BIT		(1 << 7) /* CTS pin state */

/* Special अक्षरacter रेजिस्टर bits */
#घोषणा MAX310X_SPCHR_XON1_BIT		(1 << 0) /* XON1 अक्षरacter */
#घोषणा MAX310X_SPCHR_XON2_BIT		(1 << 1) /* XON2 अक्षरacter */
#घोषणा MAX310X_SPCHR_XOFF1_BIT		(1 << 2) /* XOFF1 अक्षरacter */
#घोषणा MAX310X_SPCHR_XOFF2_BIT		(1 << 3) /* XOFF2 अक्षरacter */
#घोषणा MAX310X_SPCHR_BREAK_BIT		(1 << 4) /* RX अवरोध */
#घोषणा MAX310X_SPCHR_MULTIDROP_BIT	(1 << 5) /* 9-bit multidrop addr अक्षर */

/* Status रेजिस्टर bits */
#घोषणा MAX310X_STS_GPIO0_BIT		(1 << 0) /* GPIO 0 पूर्णांकerrupt */
#घोषणा MAX310X_STS_GPIO1_BIT		(1 << 1) /* GPIO 1 पूर्णांकerrupt */
#घोषणा MAX310X_STS_GPIO2_BIT		(1 << 2) /* GPIO 2 पूर्णांकerrupt */
#घोषणा MAX310X_STS_GPIO3_BIT		(1 << 3) /* GPIO 3 पूर्णांकerrupt */
#घोषणा MAX310X_STS_CLKREADY_BIT	(1 << 5) /* Clock पढ़ोy */
#घोषणा MAX310X_STS_SLEEP_BIT		(1 << 6) /* Sleep पूर्णांकerrupt */

/* MODE1 रेजिस्टर bits */
#घोषणा MAX310X_MODE1_RXDIS_BIT		(1 << 0) /* RX disable */
#घोषणा MAX310X_MODE1_TXDIS_BIT		(1 << 1) /* TX disable */
#घोषणा MAX310X_MODE1_TXHIZ_BIT		(1 << 2) /* TX pin three-state */
#घोषणा MAX310X_MODE1_RTSHIZ_BIT	(1 << 3) /* RTS pin three-state */
#घोषणा MAX310X_MODE1_TRNSCVCTRL_BIT	(1 << 4) /* Transceiver ctrl enable */
#घोषणा MAX310X_MODE1_FORCESLEEP_BIT	(1 << 5) /* Force sleep mode */
#घोषणा MAX310X_MODE1_AUTOSLEEP_BIT	(1 << 6) /* Auto sleep enable */
#घोषणा MAX310X_MODE1_IRQSEL_BIT	(1 << 7) /* IRQ pin enable */

/* MODE2 रेजिस्टर bits */
#घोषणा MAX310X_MODE2_RST_BIT		(1 << 0) /* Chip reset */
#घोषणा MAX310X_MODE2_FIFORST_BIT	(1 << 1) /* FIFO reset */
#घोषणा MAX310X_MODE2_RXTRIGINV_BIT	(1 << 2) /* RX FIFO INT invert */
#घोषणा MAX310X_MODE2_RXEMPTINV_BIT	(1 << 3) /* RX FIFO empty INT invert */
#घोषणा MAX310X_MODE2_SPCHR_BIT		(1 << 4) /* Special chr detect enable */
#घोषणा MAX310X_MODE2_LOOPBACK_BIT	(1 << 5) /* Internal loopback enable */
#घोषणा MAX310X_MODE2_MULTIDROP_BIT	(1 << 6) /* 9-bit multidrop enable */
#घोषणा MAX310X_MODE2_ECHOSUPR_BIT	(1 << 7) /* ECHO suppression enable */

/* LCR रेजिस्टर bits */
#घोषणा MAX310X_LCR_LENGTH0_BIT		(1 << 0) /* Word length bit 0 */
#घोषणा MAX310X_LCR_LENGTH1_BIT		(1 << 1) /* Word length bit 1
						  *
						  * Word length bits table:
						  * 00 -> 5 bit words
						  * 01 -> 6 bit words
						  * 10 -> 7 bit words
						  * 11 -> 8 bit words
						  */
#घोषणा MAX310X_LCR_STOPLEN_BIT		(1 << 2) /* STOP length bit
						  *
						  * STOP length bit table:
						  * 0 -> 1 stop bit
						  * 1 -> 1-1.5 stop bits अगर
						  *      word length is 5,
						  *      2 stop bits otherwise
						  */
#घोषणा MAX310X_LCR_PARITY_BIT		(1 << 3) /* Parity bit enable */
#घोषणा MAX310X_LCR_EVENPARITY_BIT	(1 << 4) /* Even parity bit enable */
#घोषणा MAX310X_LCR_FORCEPARITY_BIT	(1 << 5) /* 9-bit multidrop parity */
#घोषणा MAX310X_LCR_TXBREAK_BIT		(1 << 6) /* TX अवरोध enable */
#घोषणा MAX310X_LCR_RTS_BIT		(1 << 7) /* RTS pin control */

/* IRDA रेजिस्टर bits */
#घोषणा MAX310X_IRDA_IRDAEN_BIT		(1 << 0) /* IRDA mode enable */
#घोषणा MAX310X_IRDA_SIR_BIT		(1 << 1) /* SIR mode enable */

/* Flow control trigger level रेजिस्टर masks */
#घोषणा MAX310X_FLOWLVL_HALT_MASK	(0x000f) /* Flow control halt level */
#घोषणा MAX310X_FLOWLVL_RES_MASK	(0x00f0) /* Flow control resume level */
#घोषणा MAX310X_FLOWLVL_HALT(words)	((words / 8) & 0x0f)
#घोषणा MAX310X_FLOWLVL_RES(words)	(((words / 8) & 0x0f) << 4)

/* FIFO पूर्णांकerrupt trigger level रेजिस्टर masks */
#घोषणा MAX310X_FIFOTRIGLVL_TX_MASK	(0x0f) /* TX FIFO trigger level */
#घोषणा MAX310X_FIFOTRIGLVL_RX_MASK	(0xf0) /* RX FIFO trigger level */
#घोषणा MAX310X_FIFOTRIGLVL_TX(words)	((words / 8) & 0x0f)
#घोषणा MAX310X_FIFOTRIGLVL_RX(words)	(((words / 8) & 0x0f) << 4)

/* Flow control रेजिस्टर bits */
#घोषणा MAX310X_FLOWCTRL_AUTORTS_BIT	(1 << 0) /* Auto RTS flow ctrl enable */
#घोषणा MAX310X_FLOWCTRL_AUTOCTS_BIT	(1 << 1) /* Auto CTS flow ctrl enable */
#घोषणा MAX310X_FLOWCTRL_GPIADDR_BIT	(1 << 2) /* Enables that GPIO inमाला_दो
						  * are used in conjunction with
						  * XOFF2 क्रम definition of
						  * special अक्षरacter */
#घोषणा MAX310X_FLOWCTRL_SWFLOWEN_BIT	(1 << 3) /* Auto SW flow ctrl enable */
#घोषणा MAX310X_FLOWCTRL_SWFLOW0_BIT	(1 << 4) /* SWFLOW bit 0 */
#घोषणा MAX310X_FLOWCTRL_SWFLOW1_BIT	(1 << 5) /* SWFLOW bit 1
						  *
						  * SWFLOW bits 1 & 0 table:
						  * 00 -> no transmitter flow
						  *       control
						  * 01 -> receiver compares
						  *       XON2 and XOFF2
						  *       and controls
						  *       transmitter
						  * 10 -> receiver compares
						  *       XON1 and XOFF1
						  *       and controls
						  *       transmitter
						  * 11 -> receiver compares
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2 and controls
						  *       transmitter
						  */
#घोषणा MAX310X_FLOWCTRL_SWFLOW2_BIT	(1 << 6) /* SWFLOW bit 2 */
#घोषणा MAX310X_FLOWCTRL_SWFLOW3_BIT	(1 << 7) /* SWFLOW bit 3
						  *
						  * SWFLOW bits 3 & 2 table:
						  * 00 -> no received flow
						  *       control
						  * 01 -> transmitter generates
						  *       XON2 and XOFF2
						  * 10 -> transmitter generates
						  *       XON1 and XOFF1
						  * 11 -> transmitter generates
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2
						  */

/* PLL configuration रेजिस्टर masks */
#घोषणा MAX310X_PLLCFG_PREDIV_MASK	(0x3f) /* PLL preभागision value */
#घोषणा MAX310X_PLLCFG_PLLFACTOR_MASK	(0xc0) /* PLL multiplication factor */

/* Baud rate generator configuration रेजिस्टर bits */
#घोषणा MAX310X_BRGCFG_2XMODE_BIT	(1 << 4) /* Double baud rate */
#घोषणा MAX310X_BRGCFG_4XMODE_BIT	(1 << 5) /* Quadruple baud rate */

/* Clock source रेजिस्टर bits */
#घोषणा MAX310X_CLKSRC_CRYST_BIT	(1 << 1) /* Crystal osc enable */
#घोषणा MAX310X_CLKSRC_PLL_BIT		(1 << 2) /* PLL enable */
#घोषणा MAX310X_CLKSRC_PLLBYP_BIT	(1 << 3) /* PLL bypass */
#घोषणा MAX310X_CLKSRC_EXTCLK_BIT	(1 << 4) /* External घड़ी enable */
#घोषणा MAX310X_CLKSRC_CLK2RTS_BIT	(1 << 7) /* Baud clk to RTS pin */

/* Global commands */
#घोषणा MAX310X_EXTREG_ENBL		(0xce)
#घोषणा MAX310X_EXTREG_DSBL		(0xcd)

/* Misc definitions */
#घोषणा MAX310X_FIFO_SIZE		(128)
#घोषणा MAX310x_REV_MASK		(0xf8)
#घोषणा MAX310X_WRITE_BIT		0x80

/* MAX3107 specअगरic */
#घोषणा MAX3107_REV_ID			(0xa0)

/* MAX3109 specअगरic */
#घोषणा MAX3109_REV_ID			(0xc0)

/* MAX14830 specअगरic */
#घोषणा MAX14830_BRGCFG_CLKDIS_BIT	(1 << 6) /* Clock Disable */
#घोषणा MAX14830_REV_ID			(0xb0)

काष्ठा max310x_devtype अणु
	अक्षर	name[9];
	पूर्णांक	nr;
	u8	mode1;
	पूर्णांक	(*detect)(काष्ठा device *);
	व्योम	(*घातer)(काष्ठा uart_port *, पूर्णांक);
पूर्ण;

काष्ठा max310x_one अणु
	काष्ठा uart_port	port;
	काष्ठा work_काष्ठा	tx_work;
	काष्ठा work_काष्ठा	md_work;
	काष्ठा work_काष्ठा	rs_work;

	u8 wr_header;
	u8 rd_header;
	u8 rx_buf[MAX310X_FIFO_SIZE];
पूर्ण;
#घोषणा to_max310x_port(_port) \
	container_of(_port, काष्ठा max310x_one, port)

काष्ठा max310x_port अणु
	स्थिर काष्ठा max310x_devtype *devtype;
	काष्ठा regmap		*regmap;
	काष्ठा clk		*clk;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip	gpio;
#पूर्ण_अगर
	काष्ठा max310x_one	p[];
पूर्ण;

अटल काष्ठा uart_driver max310x_uart = अणु
	.owner		= THIS_MODULE,
	.driver_name	= MAX310X_NAME,
	.dev_name	= "ttyMAX",
	.major		= MAX310X_MAJOR,
	.minor		= MAX310X_MINOR,
	.nr		= MAX310X_UART_NRMAX,
पूर्ण;

अटल DECLARE_BITMAP(max310x_lines, MAX310X_UART_NRMAX);

अटल u8 max310x_port_पढ़ो(काष्ठा uart_port *port, u8 reg)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक val = 0;

	regmap_पढ़ो(s->regmap, port->iobase + reg, &val);

	वापस val;
पूर्ण

अटल व्योम max310x_port_ग_लिखो(काष्ठा uart_port *port, u8 reg, u8 val)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);

	regmap_ग_लिखो(s->regmap, port->iobase + reg, val);
पूर्ण

अटल व्योम max310x_port_update(काष्ठा uart_port *port, u8 reg, u8 mask, u8 val)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);

	regmap_update_bits(s->regmap, port->iobase + reg, mask, val);
पूर्ण

अटल पूर्णांक max3107_detect(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = regmap_पढ़ो(s->regmap, MAX310X_REVID_REG, &val);
	अगर (ret)
		वापस ret;

	अगर (((val & MAX310x_REV_MASK) != MAX3107_REV_ID)) अणु
		dev_err(dev,
			"%s ID 0x%02x does not match\n", s->devtype->name, val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max3108_detect(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	/* MAX3108 have not REV ID रेजिस्टर, we just check शेष value
	 * from घड़ीsource रेजिस्टर to make sure everything works.
	 */
	ret = regmap_पढ़ो(s->regmap, MAX310X_CLKSRC_REG, &val);
	अगर (ret)
		वापस ret;

	अगर (val != (MAX310X_CLKSRC_EXTCLK_BIT | MAX310X_CLKSRC_PLLBYP_BIT)) अणु
		dev_err(dev, "%s not present\n", s->devtype->name);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max3109_detect(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(s->regmap, MAX310X_GLOBALCMD_REG,
			   MAX310X_EXTREG_ENBL);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(s->regmap, MAX310X_REVID_EXTREG, &val);
	regmap_ग_लिखो(s->regmap, MAX310X_GLOBALCMD_REG, MAX310X_EXTREG_DSBL);
	अगर (((val & MAX310x_REV_MASK) != MAX3109_REV_ID)) अणु
		dev_err(dev,
			"%s ID 0x%02x does not match\n", s->devtype->name, val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max310x_घातer(काष्ठा uart_port *port, पूर्णांक on)
अणु
	max310x_port_update(port, MAX310X_MODE1_REG,
			    MAX310X_MODE1_FORCESLEEP_BIT,
			    on ? 0 : MAX310X_MODE1_FORCESLEEP_BIT);
	अगर (on)
		msleep(50);
पूर्ण

अटल पूर्णांक max14830_detect(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(s->regmap, MAX310X_GLOBALCMD_REG,
			   MAX310X_EXTREG_ENBL);
	अगर (ret)
		वापस ret;
	
	regmap_पढ़ो(s->regmap, MAX310X_REVID_EXTREG, &val);
	regmap_ग_लिखो(s->regmap, MAX310X_GLOBALCMD_REG, MAX310X_EXTREG_DSBL);
	अगर (((val & MAX310x_REV_MASK) != MAX14830_REV_ID)) अणु
		dev_err(dev,
			"%s ID 0x%02x does not match\n", s->devtype->name, val);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max14830_घातer(काष्ठा uart_port *port, पूर्णांक on)
अणु
	max310x_port_update(port, MAX310X_BRGCFG_REG,
			    MAX14830_BRGCFG_CLKDIS_BIT,
			    on ? 0 : MAX14830_BRGCFG_CLKDIS_BIT);
	अगर (on)
		msleep(50);
पूर्ण

अटल स्थिर काष्ठा max310x_devtype max3107_devtype = अणु
	.name	= "MAX3107",
	.nr	= 1,
	.mode1	= MAX310X_MODE1_AUTOSLEEP_BIT | MAX310X_MODE1_IRQSEL_BIT,
	.detect	= max3107_detect,
	.घातer	= max310x_घातer,
पूर्ण;

अटल स्थिर काष्ठा max310x_devtype max3108_devtype = अणु
	.name	= "MAX3108",
	.nr	= 1,
	.mode1	= MAX310X_MODE1_AUTOSLEEP_BIT,
	.detect	= max3108_detect,
	.घातer	= max310x_घातer,
पूर्ण;

अटल स्थिर काष्ठा max310x_devtype max3109_devtype = अणु
	.name	= "MAX3109",
	.nr	= 2,
	.mode1	= MAX310X_MODE1_AUTOSLEEP_BIT,
	.detect	= max3109_detect,
	.घातer	= max310x_घातer,
पूर्ण;

अटल स्थिर काष्ठा max310x_devtype max14830_devtype = अणु
	.name	= "MAX14830",
	.nr	= 4,
	.mode1	= MAX310X_MODE1_IRQSEL_BIT,
	.detect	= max14830_detect,
	.घातer	= max14830_घातer,
पूर्ण;

अटल bool max310x_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg & 0x1f) अणु
	हाल MAX310X_IRQSTS_REG:
	हाल MAX310X_LSR_IRQSTS_REG:
	हाल MAX310X_SPCHR_IRQSTS_REG:
	हाल MAX310X_STS_IRQSTS_REG:
	हाल MAX310X_TXFIFOLVL_REG:
	हाल MAX310X_RXFIFOLVL_REG:
		वापस false;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल bool max310x_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg & 0x1f) अणु
	हाल MAX310X_RHR_REG:
	हाल MAX310X_IRQSTS_REG:
	हाल MAX310X_LSR_IRQSTS_REG:
	हाल MAX310X_SPCHR_IRQSTS_REG:
	हाल MAX310X_STS_IRQSTS_REG:
	हाल MAX310X_TXFIFOLVL_REG:
	हाल MAX310X_RXFIFOLVL_REG:
	हाल MAX310X_GPIODATA_REG:
	हाल MAX310X_BRGDIVLSB_REG:
	हाल MAX310X_REG_05:
	हाल MAX310X_REG_1F:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool max310x_reg_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg & 0x1f) अणु
	हाल MAX310X_RHR_REG:
	हाल MAX310X_IRQSTS_REG:
	हाल MAX310X_SPCHR_IRQSTS_REG:
	हाल MAX310X_STS_IRQSTS_REG:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक max310x_set_baud(काष्ठा uart_port *port, पूर्णांक baud)
अणु
	अचिन्हित पूर्णांक mode = 0, भाग = 0, frac = 0, c = 0, F = 0;

	/*
	 * Calculate the पूर्णांकeger भागisor first. Select a proper mode
	 * in हाल अगर the requested baud is too high क्रम the pre-defined
	 * घड़ीs frequency.
	 */
	भाग = port->uartclk / baud;
	अगर (भाग < 8) अणु
		/* Mode x4 */
		c = 4;
		mode = MAX310X_BRGCFG_4XMODE_BIT;
	पूर्ण अन्यथा अगर (भाग < 16) अणु
		/* Mode x2 */
		c = 8;
		mode = MAX310X_BRGCFG_2XMODE_BIT;
	पूर्ण अन्यथा अणु
		c = 16;
	पूर्ण

	/* Calculate the भागisor in accordance with the fraction coefficient */
	भाग /= c;
	F = c*baud;

	/* Calculate the baud rate fraction */
	अगर (भाग > 0)
		frac = (16*(port->uartclk % F)) / F;
	अन्यथा
		भाग = 1;

	max310x_port_ग_लिखो(port, MAX310X_BRGDIVMSB_REG, भाग >> 8);
	max310x_port_ग_लिखो(port, MAX310X_BRGDIVLSB_REG, भाग);
	max310x_port_ग_लिखो(port, MAX310X_BRGCFG_REG, frac | mode);

	/* Return the actual baud rate we just programmed */
	वापस (16*port->uartclk) / (c*(16*भाग + frac));
पूर्ण

अटल पूर्णांक max310x_update_best_err(अचिन्हित दीर्घ f, दीर्घ *besterr)
अणु
	/* Use baudrate 115200 क्रम calculate error */
	दीर्घ err = f % (460800 * 16);

	अगर ((*besterr < 0) || (*besterr > err)) अणु
		*besterr = err;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक max310x_set_ref_clk(काष्ठा device *dev, काष्ठा max310x_port *s,
			       अचिन्हित दीर्घ freq, bool xtal)
अणु
	अचिन्हित पूर्णांक भाग, clksrc, pllcfg = 0;
	दीर्घ besterr = -1;
	अचिन्हित दीर्घ fभाग, fmul, bestfreq = freq;

	/* First, update error without PLL */
	max310x_update_best_err(freq, &besterr);

	/* Try all possible PLL भागiders */
	क्रम (भाग = 1; (भाग <= 63) && besterr; भाग++) अणु
		fभाग = DIV_ROUND_CLOSEST(freq, भाग);

		/* Try multiplier 6 */
		fmul = fभाग * 6;
		अगर ((fभाग >= 500000) && (fभाग <= 800000))
			अगर (!max310x_update_best_err(fmul, &besterr)) अणु
				pllcfg = (0 << 6) | भाग;
				bestfreq = fmul;
			पूर्ण
		/* Try multiplier 48 */
		fmul = fभाग * 48;
		अगर ((fभाग >= 850000) && (fभाग <= 1200000))
			अगर (!max310x_update_best_err(fmul, &besterr)) अणु
				pllcfg = (1 << 6) | भाग;
				bestfreq = fmul;
			पूर्ण
		/* Try multiplier 96 */
		fmul = fभाग * 96;
		अगर ((fभाग >= 425000) && (fभाग <= 1000000))
			अगर (!max310x_update_best_err(fmul, &besterr)) अणु
				pllcfg = (2 << 6) | भाग;
				bestfreq = fmul;
			पूर्ण
		/* Try multiplier 144 */
		fmul = fभाग * 144;
		अगर ((fभाग >= 390000) && (fभाग <= 667000))
			अगर (!max310x_update_best_err(fmul, &besterr)) अणु
				pllcfg = (3 << 6) | भाग;
				bestfreq = fmul;
			पूर्ण
	पूर्ण

	/* Configure घड़ी source */
	clksrc = MAX310X_CLKSRC_EXTCLK_BIT | (xtal ? MAX310X_CLKSRC_CRYST_BIT : 0);

	/* Configure PLL */
	अगर (pllcfg) अणु
		clksrc |= MAX310X_CLKSRC_PLL_BIT;
		regmap_ग_लिखो(s->regmap, MAX310X_PLLCFG_REG, pllcfg);
	पूर्ण अन्यथा
		clksrc |= MAX310X_CLKSRC_PLLBYP_BIT;

	regmap_ग_लिखो(s->regmap, MAX310X_CLKSRC_REG, clksrc);

	/* Wait क्रम crystal */
	अगर (xtal) अणु
		अचिन्हित पूर्णांक val;
		msleep(10);
		regmap_पढ़ो(s->regmap, MAX310X_STS_IRQSTS_REG, &val);
		अगर (!(val & MAX310X_STS_CLKREADY_BIT)) अणु
			dev_warn(dev, "clock is not stable yet\n");
		पूर्ण
	पूर्ण

	वापस (पूर्णांक)bestfreq;
पूर्ण

अटल व्योम max310x_batch_ग_लिखो(काष्ठा uart_port *port, u8 *txbuf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = &one->wr_header,
			.len = माप(one->wr_header),
		पूर्ण, अणु
			.tx_buf = txbuf,
			.len = len,
		पूर्ण
	पूर्ण;
	spi_sync_transfer(to_spi_device(port->dev), xfer, ARRAY_SIZE(xfer));
पूर्ण

अटल व्योम max310x_batch_पढ़ो(काष्ठा uart_port *port, u8 *rxbuf, अचिन्हित पूर्णांक len)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = &one->rd_header,
			.len = माप(one->rd_header),
		पूर्ण, अणु
			.rx_buf = rxbuf,
			.len = len,
		पूर्ण
	पूर्ण;
	spi_sync_transfer(to_spi_device(port->dev), xfer, ARRAY_SIZE(xfer));
पूर्ण

अटल व्योम max310x_handle_rx(काष्ठा uart_port *port, अचिन्हित पूर्णांक rxlen)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);
	अचिन्हित पूर्णांक sts, ch, flag, i;

	अगर (port->पढ़ो_status_mask == MAX310X_LSR_RXOVR_BIT) अणु
		/* We are just पढ़ोing, happily ignoring any error conditions.
		 * Break condition, parity checking, framing errors -- they
		 * are all ignored. That means that we can करो a batch-पढ़ो.
		 *
		 * There is a small opportunity क्रम race अगर the RX FIFO
		 * overruns जबतक we're पढ़ोing the buffer; the datasheets says
		 * that the LSR रेजिस्टर applies to the "current" अक्षरacter.
		 * That's also the reason why we cannot करो batched पढ़ोs when
		 * asked to check the inभागidual statuses.
		 * */

		sts = max310x_port_पढ़ो(port, MAX310X_LSR_IRQSTS_REG);
		max310x_batch_पढ़ो(port, one->rx_buf, rxlen);

		port->icount.rx += rxlen;
		flag = TTY_NORMAL;
		sts &= port->पढ़ो_status_mask;

		अगर (sts & MAX310X_LSR_RXOVR_BIT) अणु
			dev_warn_ratelimited(port->dev, "Hardware RX FIFO overrun\n");
			port->icount.overrun++;
		पूर्ण

		क्रम (i = 0; i < (rxlen - 1); ++i)
			uart_insert_अक्षर(port, sts, 0, one->rx_buf[i], flag);

		/*
		 * Handle the overrun हाल क्रम the last अक्षरacter only, since
		 * the RxFIFO overflow happens after it is pushed to the FIFO
		 * tail.
		 */
		uart_insert_अक्षर(port, sts, MAX310X_LSR_RXOVR_BIT,
				 one->rx_buf[rxlen-1], flag);

	पूर्ण अन्यथा अणु
		अगर (unlikely(rxlen >= port->fअगरosize)) अणु
			dev_warn_ratelimited(port->dev, "Possible RX FIFO overrun\n");
			port->icount.buf_overrun++;
			/* Ensure sanity of RX level */
			rxlen = port->fअगरosize;
		पूर्ण

		जबतक (rxlen--) अणु
			ch = max310x_port_पढ़ो(port, MAX310X_RHR_REG);
			sts = max310x_port_पढ़ो(port, MAX310X_LSR_IRQSTS_REG);

			sts &= MAX310X_LSR_RXPAR_BIT | MAX310X_LSR_FRERR_BIT |
			       MAX310X_LSR_RXOVR_BIT | MAX310X_LSR_RXBRK_BIT;

			port->icount.rx++;
			flag = TTY_NORMAL;

			अगर (unlikely(sts)) अणु
				अगर (sts & MAX310X_LSR_RXBRK_BIT) अणु
					port->icount.brk++;
					अगर (uart_handle_अवरोध(port))
						जारी;
				पूर्ण अन्यथा अगर (sts & MAX310X_LSR_RXPAR_BIT)
					port->icount.parity++;
				अन्यथा अगर (sts & MAX310X_LSR_FRERR_BIT)
					port->icount.frame++;
				अन्यथा अगर (sts & MAX310X_LSR_RXOVR_BIT)
					port->icount.overrun++;

				sts &= port->पढ़ो_status_mask;
				अगर (sts & MAX310X_LSR_RXBRK_BIT)
					flag = TTY_BREAK;
				अन्यथा अगर (sts & MAX310X_LSR_RXPAR_BIT)
					flag = TTY_PARITY;
				अन्यथा अगर (sts & MAX310X_LSR_FRERR_BIT)
					flag = TTY_FRAME;
				अन्यथा अगर (sts & MAX310X_LSR_RXOVR_BIT)
					flag = TTY_OVERRUN;
			पूर्ण

			अगर (uart_handle_sysrq_अक्षर(port, ch))
				जारी;

			अगर (sts & port->ignore_status_mask)
				जारी;

			uart_insert_अक्षर(port, sts, MAX310X_LSR_RXOVR_BIT, ch, flag);
		पूर्ण
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम max310x_handle_tx(काष्ठा uart_port *port)
अणु
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक txlen, to_send, until_end;

	अगर (unlikely(port->x_अक्षर)) अणु
		max310x_port_ग_लिखो(port, MAX310X_THR_REG, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	/* Get length of data pending in circular buffer */
	to_send = uart_circ_अक्षरs_pending(xmit);
	until_end = CIRC_CNT_TO_END(xmit->head, xmit->tail, UART_XMIT_SIZE);
	अगर (likely(to_send)) अणु
		/* Limit to size of TX FIFO */
		txlen = max310x_port_पढ़ो(port, MAX310X_TXFIFOLVL_REG);
		txlen = port->fअगरosize - txlen;
		to_send = (to_send > txlen) ? txlen : to_send;

		अगर (until_end < to_send) अणु
			/* It's a circ buffer -- wrap around.
			 * We could करो that in one SPI transaction, but meh. */
			max310x_batch_ग_लिखो(port, xmit->buf + xmit->tail, until_end);
			max310x_batch_ग_लिखो(port, xmit->buf, to_send - until_end);
		पूर्ण अन्यथा अणु
			max310x_batch_ग_लिखो(port, xmit->buf + xmit->tail, to_send);
		पूर्ण

		/* Add data to send */
		port->icount.tx += to_send;
		xmit->tail = (xmit->tail + to_send) & (UART_XMIT_SIZE - 1);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल व्योम max310x_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);

	schedule_work(&one->tx_work);
पूर्ण

अटल irqवापस_t max310x_port_irq(काष्ठा max310x_port *s, पूर्णांक portno)
अणु
	काष्ठा uart_port *port = &s->p[portno].port;
	irqवापस_t res = IRQ_NONE;

	करो अणु
		अचिन्हित पूर्णांक ists, lsr, rxlen;

		/* Read IRQ status & RX FIFO level */
		ists = max310x_port_पढ़ो(port, MAX310X_IRQSTS_REG);
		rxlen = max310x_port_पढ़ो(port, MAX310X_RXFIFOLVL_REG);
		अगर (!ists && !rxlen)
			अवरोध;

		res = IRQ_HANDLED;

		अगर (ists & MAX310X_IRQ_CTS_BIT) अणु
			lsr = max310x_port_पढ़ो(port, MAX310X_LSR_IRQSTS_REG);
			uart_handle_cts_change(port,
					       !!(lsr & MAX310X_LSR_CTS_BIT));
		पूर्ण
		अगर (rxlen)
			max310x_handle_rx(port, rxlen);
		अगर (ists & MAX310X_IRQ_TXEMPTY_BIT)
			max310x_start_tx(port);
	पूर्ण जबतक (1);
	वापस res;
पूर्ण

अटल irqवापस_t max310x_ist(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max310x_port *s = (काष्ठा max310x_port *)dev_id;
	bool handled = false;

	अगर (s->devtype->nr > 1) अणु
		करो अणु
			अचिन्हित पूर्णांक val = ~0;

			WARN_ON_ONCE(regmap_पढ़ो(s->regmap,
						 MAX310X_GLOBALIRQ_REG, &val));
			val = ((1 << s->devtype->nr) - 1) & ~val;
			अगर (!val)
				अवरोध;
			अगर (max310x_port_irq(s, fls(val) - 1) == IRQ_HANDLED)
				handled = true;
		पूर्ण जबतक (1);
	पूर्ण अन्यथा अणु
		अगर (max310x_port_irq(s, 0) == IRQ_HANDLED)
			handled = true;
	पूर्ण

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम max310x_tx_proc(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा max310x_one *one = container_of(ws, काष्ठा max310x_one, tx_work);

	max310x_handle_tx(&one->port);
पूर्ण

अटल अचिन्हित पूर्णांक max310x_tx_empty(काष्ठा uart_port *port)
अणु
	u8 lvl = max310x_port_पढ़ो(port, MAX310X_TXFIFOLVL_REG);

	वापस lvl ? 0 : TIOCSER_TEMT;
पूर्ण

अटल अचिन्हित पूर्णांक max310x_get_mctrl(काष्ठा uart_port *port)
अणु
	/* DCD and DSR are not wired and CTS/RTS is handled स्वतःmatically
	 * so just indicate DSR and CAR निश्चितed
	 */
	वापस TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम max310x_md_proc(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा max310x_one *one = container_of(ws, काष्ठा max310x_one, md_work);

	max310x_port_update(&one->port, MAX310X_MODE2_REG,
			    MAX310X_MODE2_LOOPBACK_BIT,
			    (one->port.mctrl & TIOCM_LOOP) ?
			    MAX310X_MODE2_LOOPBACK_BIT : 0);
पूर्ण

अटल व्योम max310x_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);

	schedule_work(&one->md_work);
पूर्ण

अटल व्योम max310x_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	max310x_port_update(port, MAX310X_LCR_REG,
			    MAX310X_LCR_TXBREAK_BIT,
			    अवरोध_state ? MAX310X_LCR_TXBREAK_BIT : 0);
पूर्ण

अटल व्योम max310x_set_termios(काष्ठा uart_port *port,
				काष्ठा ktermios *termios,
				काष्ठा ktermios *old)
अणु
	अचिन्हित पूर्णांक lcr = 0, flow = 0;
	पूर्णांक baud;

	/* Mask termios capabilities we करोn't support */
	termios->c_cflag &= ~CMSPAR;

	/* Word size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		अवरोध;
	हाल CS6:
		lcr = MAX310X_LCR_LENGTH0_BIT;
		अवरोध;
	हाल CS7:
		lcr = MAX310X_LCR_LENGTH1_BIT;
		अवरोध;
	हाल CS8:
	शेष:
		lcr = MAX310X_LCR_LENGTH1_BIT | MAX310X_LCR_LENGTH0_BIT;
		अवरोध;
	पूर्ण

	/* Parity */
	अगर (termios->c_cflag & PARENB) अणु
		lcr |= MAX310X_LCR_PARITY_BIT;
		अगर (!(termios->c_cflag & PARODD))
			lcr |= MAX310X_LCR_EVENPARITY_BIT;
	पूर्ण

	/* Stop bits */
	अगर (termios->c_cflag & CSTOPB)
		lcr |= MAX310X_LCR_STOPLEN_BIT; /* 2 stops */

	/* Update LCR रेजिस्टर */
	max310x_port_ग_लिखो(port, MAX310X_LCR_REG, lcr);

	/* Set पढ़ो status mask */
	port->पढ़ो_status_mask = MAX310X_LSR_RXOVR_BIT;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= MAX310X_LSR_RXPAR_BIT |
					  MAX310X_LSR_FRERR_BIT;
	अगर (termios->c_अगरlag & (IGNBRK | BRKINT | PARMRK))
		port->पढ़ो_status_mask |= MAX310X_LSR_RXBRK_BIT;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNBRK)
		port->ignore_status_mask |= MAX310X_LSR_RXBRK_BIT;
	अगर (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= MAX310X_LSR_RXPAR_BIT |
					    MAX310X_LSR_RXOVR_BIT |
					    MAX310X_LSR_FRERR_BIT |
					    MAX310X_LSR_RXBRK_BIT;

	/* Configure flow control */
	max310x_port_ग_लिखो(port, MAX310X_XON1_REG, termios->c_cc[VSTART]);
	max310x_port_ग_लिखो(port, MAX310X_XOFF1_REG, termios->c_cc[VSTOP]);

	/* Disable transmitter beक्रमe enabling AutoCTS or स्वतः transmitter
	 * flow control
	 */
	अगर (termios->c_cflag & CRTSCTS || termios->c_अगरlag & IXOFF) अणु
		max310x_port_update(port, MAX310X_MODE1_REG,
				    MAX310X_MODE1_TXDIS_BIT,
				    MAX310X_MODE1_TXDIS_BIT);
	पूर्ण

	port->status &= ~(UPSTAT_AUTOCTS | UPSTAT_AUTORTS | UPSTAT_AUTOXOFF);

	अगर (termios->c_cflag & CRTSCTS) अणु
		/* Enable AUTORTS and AUTOCTS */
		port->status |= UPSTAT_AUTOCTS | UPSTAT_AUTORTS;
		flow |= MAX310X_FLOWCTRL_AUTOCTS_BIT |
			MAX310X_FLOWCTRL_AUTORTS_BIT;
	पूर्ण
	अगर (termios->c_अगरlag & IXON)
		flow |= MAX310X_FLOWCTRL_SWFLOW3_BIT |
			MAX310X_FLOWCTRL_SWFLOWEN_BIT;
	अगर (termios->c_अगरlag & IXOFF) अणु
		port->status |= UPSTAT_AUTOXOFF;
		flow |= MAX310X_FLOWCTRL_SWFLOW1_BIT |
			MAX310X_FLOWCTRL_SWFLOWEN_BIT;
	पूर्ण
	max310x_port_ग_लिखो(port, MAX310X_FLOWCTRL_REG, flow);

	/* Enable transmitter after disabling AutoCTS and स्वतः transmitter
	 * flow control
	 */
	अगर (!(termios->c_cflag & CRTSCTS) && !(termios->c_अगरlag & IXOFF)) अणु
		max310x_port_update(port, MAX310X_MODE1_REG,
				    MAX310X_MODE1_TXDIS_BIT,
				    0);
	पूर्ण

	/* Get baud rate generator configuration */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / 0xffff,
				  port->uartclk / 4);

	/* Setup baudrate generator */
	baud = max310x_set_baud(port, baud);

	/* Update समयout according to new baud rate */
	uart_update_समयout(port, termios->c_cflag, baud);
पूर्ण

अटल व्योम max310x_rs_proc(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा max310x_one *one = container_of(ws, काष्ठा max310x_one, rs_work);
	अचिन्हित पूर्णांक delay, mode1 = 0, mode2 = 0;

	delay = (one->port.rs485.delay_rts_beक्रमe_send << 4) |
		one->port.rs485.delay_rts_after_send;
	max310x_port_ग_लिखो(&one->port, MAX310X_HDPIXDELAY_REG, delay);

	अगर (one->port.rs485.flags & SER_RS485_ENABLED) अणु
		mode1 = MAX310X_MODE1_TRNSCVCTRL_BIT;

		अगर (!(one->port.rs485.flags & SER_RS485_RX_DURING_TX))
			mode2 = MAX310X_MODE2_ECHOSUPR_BIT;
	पूर्ण

	max310x_port_update(&one->port, MAX310X_MODE1_REG,
			MAX310X_MODE1_TRNSCVCTRL_BIT, mode1);
	max310x_port_update(&one->port, MAX310X_MODE2_REG,
			MAX310X_MODE2_ECHOSUPR_BIT, mode2);
पूर्ण

अटल पूर्णांक max310x_rs485_config(काष्ठा uart_port *port,
				काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा max310x_one *one = to_max310x_port(port);

	अगर ((rs485->delay_rts_beक्रमe_send > 0x0f) ||
	    (rs485->delay_rts_after_send > 0x0f))
		वापस -दुस्फल;

	rs485->flags &= SER_RS485_RTS_ON_SEND | SER_RS485_RX_DURING_TX |
			SER_RS485_ENABLED;
	स_रखो(rs485->padding, 0, माप(rs485->padding));
	port->rs485 = *rs485;

	schedule_work(&one->rs_work);

	वापस 0;
पूर्ण

अटल पूर्णांक max310x_startup(काष्ठा uart_port *port)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक val;

	s->devtype->घातer(port, 1);

	/* Configure MODE1 रेजिस्टर */
	max310x_port_update(port, MAX310X_MODE1_REG,
			    MAX310X_MODE1_TRNSCVCTRL_BIT, 0);

	/* Configure MODE2 रेजिस्टर & Reset FIFOs*/
	val = MAX310X_MODE2_RXEMPTINV_BIT | MAX310X_MODE2_FIFORST_BIT;
	max310x_port_ग_लिखो(port, MAX310X_MODE2_REG, val);
	max310x_port_update(port, MAX310X_MODE2_REG,
			    MAX310X_MODE2_FIFORST_BIT, 0);

	/* Configure mode1/mode2 to have rs485/rs232 enabled at startup */
	val = (clamp(port->rs485.delay_rts_beक्रमe_send, 0U, 15U) << 4) |
		clamp(port->rs485.delay_rts_after_send, 0U, 15U);
	max310x_port_ग_लिखो(port, MAX310X_HDPIXDELAY_REG, val);

	अगर (port->rs485.flags & SER_RS485_ENABLED) अणु
		max310x_port_update(port, MAX310X_MODE1_REG,
				    MAX310X_MODE1_TRNSCVCTRL_BIT,
				    MAX310X_MODE1_TRNSCVCTRL_BIT);

		अगर (!(port->rs485.flags & SER_RS485_RX_DURING_TX))
			max310x_port_update(port, MAX310X_MODE2_REG,
					    MAX310X_MODE2_ECHOSUPR_BIT,
					    MAX310X_MODE2_ECHOSUPR_BIT);
	पूर्ण

	/* Configure flow control levels */
	/* Flow control halt level 96, resume level 48 */
	max310x_port_ग_लिखो(port, MAX310X_FLOWLVL_REG,
			   MAX310X_FLOWLVL_RES(48) | MAX310X_FLOWLVL_HALT(96));

	/* Clear IRQ status रेजिस्टर */
	max310x_port_पढ़ो(port, MAX310X_IRQSTS_REG);

	/* Enable RX, TX, CTS change पूर्णांकerrupts */
	val = MAX310X_IRQ_RXEMPTY_BIT | MAX310X_IRQ_TXEMPTY_BIT;
	max310x_port_ग_लिखो(port, MAX310X_IRQEN_REG, val | MAX310X_IRQ_CTS_BIT);

	वापस 0;
पूर्ण

अटल व्योम max310x_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);

	/* Disable all पूर्णांकerrupts */
	max310x_port_ग_लिखो(port, MAX310X_IRQEN_REG, 0);

	s->devtype->घातer(port, 0);
पूर्ण

अटल स्थिर अक्षर *max310x_type(काष्ठा uart_port *port)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(port->dev);

	वापस (port->type == PORT_MAX310X) ? s->devtype->name : शून्य;
पूर्ण

अटल पूर्णांक max310x_request_port(काष्ठा uart_port *port)
अणु
	/* Do nothing */
	वापस 0;
पूर्ण

अटल व्योम max310x_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_MAX310X;
पूर्ण

अटल पूर्णांक max310x_verअगरy_port(काष्ठा uart_port *port, काष्ठा serial_काष्ठा *s)
अणु
	अगर ((s->type != PORT_UNKNOWN) && (s->type != PORT_MAX310X))
		वापस -EINVAL;
	अगर (s->irq != port->irq)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम max310x_null_व्योम(काष्ठा uart_port *port)
अणु
	/* Do nothing */
पूर्ण

अटल स्थिर काष्ठा uart_ops max310x_ops = अणु
	.tx_empty	= max310x_tx_empty,
	.set_mctrl	= max310x_set_mctrl,
	.get_mctrl	= max310x_get_mctrl,
	.stop_tx	= max310x_null_व्योम,
	.start_tx	= max310x_start_tx,
	.stop_rx	= max310x_null_व्योम,
	.अवरोध_ctl	= max310x_अवरोध_ctl,
	.startup	= max310x_startup,
	.shutकरोwn	= max310x_shutकरोwn,
	.set_termios	= max310x_set_termios,
	.type		= max310x_type,
	.request_port	= max310x_request_port,
	.release_port	= max310x_null_व्योम,
	.config_port	= max310x_config_port,
	.verअगरy_port	= max310x_verअगरy_port,
पूर्ण;

अटल पूर्णांक __maybe_unused max310x_suspend(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < s->devtype->nr; i++) अणु
		uart_suspend_port(&max310x_uart, &s->p[i].port);
		s->devtype->घातer(&s->p[i].port, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max310x_resume(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < s->devtype->nr; i++) अणु
		s->devtype->घातer(&s->p[i].port, 1);
		uart_resume_port(&max310x_uart, &s->p[i].port);
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max310x_pm_ops, max310x_suspend, max310x_resume);

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक max310x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा max310x_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[offset / 4].port;

	val = max310x_port_पढ़ो(port, MAX310X_GPIODATA_REG);

	वापस !!((val >> 4) & (1 << (offset % 4)));
पूर्ण

अटल व्योम max310x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा max310x_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[offset / 4].port;

	max310x_port_update(port, MAX310X_GPIODATA_REG, 1 << (offset % 4),
			    value ? 1 << (offset % 4) : 0);
पूर्ण

अटल पूर्णांक max310x_gpio_direction_input(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा max310x_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[offset / 4].port;

	max310x_port_update(port, MAX310X_GPIOCFG_REG, 1 << (offset % 4), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक max310x_gpio_direction_output(काष्ठा gpio_chip *chip,
					 अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा max310x_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[offset / 4].port;

	max310x_port_update(port, MAX310X_GPIODATA_REG, 1 << (offset % 4),
			    value ? 1 << (offset % 4) : 0);
	max310x_port_update(port, MAX310X_GPIOCFG_REG, 1 << (offset % 4),
			    1 << (offset % 4));

	वापस 0;
पूर्ण

अटल पूर्णांक max310x_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				   अचिन्हित दीर्घ config)
अणु
	काष्ठा max310x_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[offset / 4].port;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		max310x_port_update(port, MAX310X_GPIOCFG_REG,
				1 << ((offset % 4) + 4),
				1 << ((offset % 4) + 4));
		वापस 0;
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		max310x_port_update(port, MAX310X_GPIOCFG_REG,
				1 << ((offset % 4) + 4), 0);
		वापस 0;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक max310x_probe(काष्ठा device *dev, स्थिर काष्ठा max310x_devtype *devtype,
			 काष्ठा regmap *regmap, पूर्णांक irq)
अणु
	पूर्णांक i, ret, fmin, fmax, freq, uartclk;
	काष्ठा max310x_port *s;
	bool xtal = false;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* Alloc port काष्ठाure */
	s = devm_kzalloc(dev, काष्ठा_size(s, p, devtype->nr), GFP_KERNEL);
	अगर (!s) अणु
		dev_err(dev, "Error allocating port structure\n");
		वापस -ENOMEM;
	पूर्ण

	s->clk = devm_clk_get_optional(dev, "osc");
	अगर (IS_ERR(s->clk))
		वापस PTR_ERR(s->clk);
	अगर (s->clk) अणु
		fmin = 500000;
		fmax = 35000000;
	पूर्ण अन्यथा अणु
		s->clk = devm_clk_get_optional(dev, "xtal");
		अगर (IS_ERR(s->clk))
			वापस PTR_ERR(s->clk);
		अगर (s->clk) अणु
			fmin = 1000000;
			fmax = 4000000;
			xtal = true;
		पूर्ण अन्यथा अणु
			dev_err(dev, "Cannot get clock\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ret = clk_prepare_enable(s->clk);
	अगर (ret)
		वापस ret;

	freq = clk_get_rate(s->clk);
	/* Check frequency limits */
	अगर (freq < fmin || freq > fmax) अणु
		ret = -दुस्फल;
		जाओ out_clk;
	पूर्ण

	s->regmap = regmap;
	s->devtype = devtype;
	dev_set_drvdata(dev, s);

	/* Check device to ensure we are talking to what we expect */
	ret = devtype->detect(dev);
	अगर (ret)
		जाओ out_clk;

	क्रम (i = 0; i < devtype->nr; i++) अणु
		अचिन्हित पूर्णांक offs = i << 5;

		/* Reset port */
		regmap_ग_लिखो(s->regmap, MAX310X_MODE2_REG + offs,
			     MAX310X_MODE2_RST_BIT);
		/* Clear port reset */
		regmap_ग_लिखो(s->regmap, MAX310X_MODE2_REG + offs, 0);

		/* Wait क्रम port startup */
		करो अणु
			regmap_पढ़ो(s->regmap,
				    MAX310X_BRGDIVLSB_REG + offs, &ret);
		पूर्ण जबतक (ret != 0x01);

		regmap_ग_लिखो(s->regmap, MAX310X_MODE1_REG + offs,
			     devtype->mode1);
	पूर्ण

	uartclk = max310x_set_ref_clk(dev, s, freq, xtal);
	dev_dbg(dev, "Reference clock set to %i Hz\n", uartclk);

	क्रम (i = 0; i < devtype->nr; i++) अणु
		अचिन्हित पूर्णांक line;

		line = find_first_zero_bit(max310x_lines, MAX310X_UART_NRMAX);
		अगर (line == MAX310X_UART_NRMAX) अणु
			ret = -दुस्फल;
			जाओ out_uart;
		पूर्ण

		/* Initialize port data */
		s->p[i].port.line	= line;
		s->p[i].port.dev	= dev;
		s->p[i].port.irq	= irq;
		s->p[i].port.type	= PORT_MAX310X;
		s->p[i].port.fअगरosize	= MAX310X_FIFO_SIZE;
		s->p[i].port.flags	= UPF_FIXED_TYPE | UPF_LOW_LATENCY;
		s->p[i].port.iotype	= UPIO_PORT;
		s->p[i].port.iobase	= i * 0x20;
		s->p[i].port.membase	= (व्योम __iomem *)~0;
		s->p[i].port.uartclk	= uartclk;
		s->p[i].port.rs485_config = max310x_rs485_config;
		s->p[i].port.ops	= &max310x_ops;
		/* Disable all पूर्णांकerrupts */
		max310x_port_ग_लिखो(&s->p[i].port, MAX310X_IRQEN_REG, 0);
		/* Clear IRQ status रेजिस्टर */
		max310x_port_पढ़ो(&s->p[i].port, MAX310X_IRQSTS_REG);
		/* Initialize queue क्रम start TX */
		INIT_WORK(&s->p[i].tx_work, max310x_tx_proc);
		/* Initialize queue क्रम changing LOOPBACK mode */
		INIT_WORK(&s->p[i].md_work, max310x_md_proc);
		/* Initialize queue क्रम changing RS485 mode */
		INIT_WORK(&s->p[i].rs_work, max310x_rs_proc);
		/* Initialize SPI-transfer buffers */
		s->p[i].wr_header = (s->p[i].port.iobase + MAX310X_THR_REG) |
				    MAX310X_WRITE_BIT;
		s->p[i].rd_header = (s->p[i].port.iobase + MAX310X_RHR_REG);

		/* Register port */
		ret = uart_add_one_port(&max310x_uart, &s->p[i].port);
		अगर (ret) अणु
			s->p[i].port.dev = शून्य;
			जाओ out_uart;
		पूर्ण
		set_bit(line, max310x_lines);

		/* Go to suspend mode */
		devtype->घातer(&s->p[i].port, 0);
	पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
	/* Setup GPIO cotroller */
	s->gpio.owner		= THIS_MODULE;
	s->gpio.parent		= dev;
	s->gpio.label		= devtype->name;
	s->gpio.direction_input	= max310x_gpio_direction_input;
	s->gpio.get		= max310x_gpio_get;
	s->gpio.direction_output= max310x_gpio_direction_output;
	s->gpio.set		= max310x_gpio_set;
	s->gpio.set_config	= max310x_gpio_set_config;
	s->gpio.base		= -1;
	s->gpio.ngpio		= devtype->nr * 4;
	s->gpio.can_sleep	= 1;
	ret = devm_gpiochip_add_data(dev, &s->gpio, s);
	अगर (ret)
		जाओ out_uart;
#पूर्ण_अगर

	/* Setup पूर्णांकerrupt */
	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, max310x_ist,
					IRQF_ONESHOT | IRQF_SHARED, dev_name(dev), s);
	अगर (!ret)
		वापस 0;

	dev_err(dev, "Unable to reguest IRQ %i\n", irq);

out_uart:
	क्रम (i = 0; i < devtype->nr; i++) अणु
		अगर (s->p[i].port.dev) अणु
			uart_हटाओ_one_port(&max310x_uart, &s->p[i].port);
			clear_bit(s->p[i].port.line, max310x_lines);
		पूर्ण
	पूर्ण

out_clk:
	clk_disable_unprepare(s->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक max310x_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा max310x_port *s = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < s->devtype->nr; i++) अणु
		cancel_work_sync(&s->p[i].tx_work);
		cancel_work_sync(&s->p[i].md_work);
		cancel_work_sync(&s->p[i].rs_work);
		uart_हटाओ_one_port(&max310x_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, max310x_lines);
		s->devtype->घातer(&s->p[i].port, 0);
	पूर्ण

	clk_disable_unprepare(s->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused max310x_dt_ids[] = अणु
	अणु .compatible = "maxim,max3107",	.data = &max3107_devtype, पूर्ण,
	अणु .compatible = "maxim,max3108",	.data = &max3108_devtype, पूर्ण,
	अणु .compatible = "maxim,max3109",	.data = &max3109_devtype, पूर्ण,
	अणु .compatible = "maxim,max14830",	.data = &max14830_devtype पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max310x_dt_ids);

अटल काष्ठा regmap_config regcfg = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.ग_लिखो_flag_mask = MAX310X_WRITE_BIT,
	.cache_type = REGCACHE_RBTREE,
	.ग_लिखोable_reg = max310x_reg_ग_लिखोable,
	.अस्थिर_reg = max310x_reg_अस्थिर,
	.precious_reg = max310x_reg_precious,
पूर्ण;

#अगर_घोषित CONFIG_SPI_MASTER
अटल पूर्णांक max310x_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा max310x_devtype *devtype;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	/* Setup SPI bus */
	spi->bits_per_word	= 8;
	spi->mode		= spi->mode ? : SPI_MODE_0;
	spi->max_speed_hz	= spi->max_speed_hz ? : 26000000;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	devtype = device_get_match_data(&spi->dev);
	अगर (!devtype)
		devtype = (काष्ठा max310x_devtype *)spi_get_device_id(spi)->driver_data;

	regcfg.max_रेजिस्टर = devtype->nr * 0x20 - 1;
	regmap = devm_regmap_init_spi(spi, &regcfg);

	वापस max310x_probe(&spi->dev, devtype, regmap, spi->irq);
पूर्ण

अटल पूर्णांक max310x_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस max310x_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max310x_id_table[] = अणु
	अणु "max3107",	(kernel_uदीर्घ_t)&max3107_devtype, पूर्ण,
	अणु "max3108",	(kernel_uदीर्घ_t)&max3108_devtype, पूर्ण,
	अणु "max3109",	(kernel_uदीर्घ_t)&max3109_devtype, पूर्ण,
	अणु "max14830",	(kernel_uदीर्घ_t)&max14830_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max310x_id_table);

अटल काष्ठा spi_driver max310x_spi_driver = अणु
	.driver = अणु
		.name		= MAX310X_NAME,
		.of_match_table	= max310x_dt_ids,
		.pm		= &max310x_pm_ops,
	पूर्ण,
	.probe		= max310x_spi_probe,
	.हटाओ		= max310x_spi_हटाओ,
	.id_table	= max310x_id_table,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init max310x_uart_init(व्योम)
अणु
	पूर्णांक ret;

	biपंचांगap_zero(max310x_lines, MAX310X_UART_NRMAX);

	ret = uart_रेजिस्टर_driver(&max310x_uart);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_SPI_MASTER
	ret = spi_रेजिस्टर_driver(&max310x_spi_driver);
	अगर (ret)
		uart_unरेजिस्टर_driver(&max310x_uart);
#पूर्ण_अगर

	वापस ret;
पूर्ण
module_init(max310x_uart_init);

अटल व्योम __निकास max310x_uart_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SPI_MASTER
	spi_unरेजिस्टर_driver(&max310x_spi_driver);
#पूर्ण_अगर

	uart_unरेजिस्टर_driver(&max310x_uart);
पूर्ण
module_निकास(max310x_uart_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("MAX310X serial driver");
