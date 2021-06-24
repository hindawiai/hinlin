<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * SC16IS7xx tty serial driver - Copyright (C) 2014 GridPoपूर्णांक
 * Author: Jon Ringle <jringle@gridpoपूर्णांक.com>
 *
 *  Based on max310x.c, by Alexander Shiyan <shc_work@mail.ru>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/sched/types.h>

#घोषणा SC16IS7XX_NAME			"sc16is7xx"
#घोषणा SC16IS7XX_MAX_DEVS		8

/* SC16IS7XX रेजिस्टर definitions */
#घोषणा SC16IS7XX_RHR_REG		(0x00) /* RX FIFO */
#घोषणा SC16IS7XX_THR_REG		(0x00) /* TX FIFO */
#घोषणा SC16IS7XX_IER_REG		(0x01) /* Interrupt enable */
#घोषणा SC16IS7XX_IIR_REG		(0x02) /* Interrupt Identअगरication */
#घोषणा SC16IS7XX_FCR_REG		(0x02) /* FIFO control */
#घोषणा SC16IS7XX_LCR_REG		(0x03) /* Line Control */
#घोषणा SC16IS7XX_MCR_REG		(0x04) /* Modem Control */
#घोषणा SC16IS7XX_LSR_REG		(0x05) /* Line Status */
#घोषणा SC16IS7XX_MSR_REG		(0x06) /* Modem Status */
#घोषणा SC16IS7XX_SPR_REG		(0x07) /* Scratch Pad */
#घोषणा SC16IS7XX_TXLVL_REG		(0x08) /* TX FIFO level */
#घोषणा SC16IS7XX_RXLVL_REG		(0x09) /* RX FIFO level */
#घोषणा SC16IS7XX_IOसूची_REG		(0x0a) /* I/O Direction
						* - only on 75x/76x
						*/
#घोषणा SC16IS7XX_IOSTATE_REG		(0x0b) /* I/O State
						* - only on 75x/76x
						*/
#घोषणा SC16IS7XX_IOINTENA_REG		(0x0c) /* I/O Interrupt Enable
						* - only on 75x/76x
						*/
#घोषणा SC16IS7XX_IOCONTROL_REG		(0x0e) /* I/O Control
						* - only on 75x/76x
						*/
#घोषणा SC16IS7XX_EFCR_REG		(0x0f) /* Extra Features Control */

/* TCR/TLR Register set: Only अगर ((MCR[2] == 1) && (EFR[4] == 1)) */
#घोषणा SC16IS7XX_TCR_REG		(0x06) /* Transmit control */
#घोषणा SC16IS7XX_TLR_REG		(0x07) /* Trigger level */

/* Special Register set: Only अगर ((LCR[7] == 1) && (LCR != 0xBF)) */
#घोषणा SC16IS7XX_DLL_REG		(0x00) /* Divisor Latch Low */
#घोषणा SC16IS7XX_DLH_REG		(0x01) /* Divisor Latch High */

/* Enhanced Register set: Only अगर (LCR == 0xBF) */
#घोषणा SC16IS7XX_EFR_REG		(0x02) /* Enhanced Features */
#घोषणा SC16IS7XX_XON1_REG		(0x04) /* Xon1 word */
#घोषणा SC16IS7XX_XON2_REG		(0x05) /* Xon2 word */
#घोषणा SC16IS7XX_XOFF1_REG		(0x06) /* Xoff1 word */
#घोषणा SC16IS7XX_XOFF2_REG		(0x07) /* Xoff2 word */

/* IER रेजिस्टर bits */
#घोषणा SC16IS7XX_IER_RDI_BIT		(1 << 0) /* Enable RX data पूर्णांकerrupt */
#घोषणा SC16IS7XX_IER_THRI_BIT		(1 << 1) /* Enable TX holding रेजिस्टर
						  * पूर्णांकerrupt */
#घोषणा SC16IS7XX_IER_RLSI_BIT		(1 << 2) /* Enable RX line status
						  * पूर्णांकerrupt */
#घोषणा SC16IS7XX_IER_MSI_BIT		(1 << 3) /* Enable Modem status
						  * पूर्णांकerrupt */

/* IER रेजिस्टर bits - ग_लिखो only अगर (EFR[4] == 1) */
#घोषणा SC16IS7XX_IER_SLEEP_BIT		(1 << 4) /* Enable Sleep mode */
#घोषणा SC16IS7XX_IER_XOFFI_BIT		(1 << 5) /* Enable Xoff पूर्णांकerrupt */
#घोषणा SC16IS7XX_IER_RTSI_BIT		(1 << 6) /* Enable nRTS पूर्णांकerrupt */
#घोषणा SC16IS7XX_IER_CTSI_BIT		(1 << 7) /* Enable nCTS पूर्णांकerrupt */

/* FCR रेजिस्टर bits */
#घोषणा SC16IS7XX_FCR_FIFO_BIT		(1 << 0) /* Enable FIFO */
#घोषणा SC16IS7XX_FCR_RXRESET_BIT	(1 << 1) /* Reset RX FIFO */
#घोषणा SC16IS7XX_FCR_TXRESET_BIT	(1 << 2) /* Reset TX FIFO */
#घोषणा SC16IS7XX_FCR_RXLVLL_BIT	(1 << 6) /* RX Trigger level LSB */
#घोषणा SC16IS7XX_FCR_RXLVLH_BIT	(1 << 7) /* RX Trigger level MSB */

/* FCR रेजिस्टर bits - ग_लिखो only अगर (EFR[4] == 1) */
#घोषणा SC16IS7XX_FCR_TXLVLL_BIT	(1 << 4) /* TX Trigger level LSB */
#घोषणा SC16IS7XX_FCR_TXLVLH_BIT	(1 << 5) /* TX Trigger level MSB */

/* IIR रेजिस्टर bits */
#घोषणा SC16IS7XX_IIR_NO_INT_BIT	(1 << 0) /* No पूर्णांकerrupts pending */
#घोषणा SC16IS7XX_IIR_ID_MASK		0x3e     /* Mask क्रम the पूर्णांकerrupt ID */
#घोषणा SC16IS7XX_IIR_THRI_SRC		0x02     /* TX holding रेजिस्टर empty */
#घोषणा SC16IS7XX_IIR_RDI_SRC		0x04     /* RX data पूर्णांकerrupt */
#घोषणा SC16IS7XX_IIR_RLSE_SRC		0x06     /* RX line status error */
#घोषणा SC16IS7XX_IIR_RTOI_SRC		0x0c     /* RX समय-out पूर्णांकerrupt */
#घोषणा SC16IS7XX_IIR_MSI_SRC		0x00     /* Modem status पूर्णांकerrupt
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_IIR_INPIN_SRC		0x30     /* Input pin change of state
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_IIR_XOFFI_SRC		0x10     /* Received Xoff */
#घोषणा SC16IS7XX_IIR_CTSRTS_SRC	0x20     /* nCTS,nRTS change of state
						  * from active (LOW)
						  * to inactive (HIGH)
						  */
/* LCR रेजिस्टर bits */
#घोषणा SC16IS7XX_LCR_LENGTH0_BIT	(1 << 0) /* Word length bit 0 */
#घोषणा SC16IS7XX_LCR_LENGTH1_BIT	(1 << 1) /* Word length bit 1
						  *
						  * Word length bits table:
						  * 00 -> 5 bit words
						  * 01 -> 6 bit words
						  * 10 -> 7 bit words
						  * 11 -> 8 bit words
						  */
#घोषणा SC16IS7XX_LCR_STOPLEN_BIT	(1 << 2) /* STOP length bit
						  *
						  * STOP length bit table:
						  * 0 -> 1 stop bit
						  * 1 -> 1-1.5 stop bits अगर
						  *      word length is 5,
						  *      2 stop bits otherwise
						  */
#घोषणा SC16IS7XX_LCR_PARITY_BIT	(1 << 3) /* Parity bit enable */
#घोषणा SC16IS7XX_LCR_EVENPARITY_BIT	(1 << 4) /* Even parity bit enable */
#घोषणा SC16IS7XX_LCR_FORCEPARITY_BIT	(1 << 5) /* 9-bit multidrop parity */
#घोषणा SC16IS7XX_LCR_TXBREAK_BIT	(1 << 6) /* TX अवरोध enable */
#घोषणा SC16IS7XX_LCR_DLAB_BIT		(1 << 7) /* Divisor Latch enable */
#घोषणा SC16IS7XX_LCR_WORD_LEN_5	(0x00)
#घोषणा SC16IS7XX_LCR_WORD_LEN_6	(0x01)
#घोषणा SC16IS7XX_LCR_WORD_LEN_7	(0x02)
#घोषणा SC16IS7XX_LCR_WORD_LEN_8	(0x03)
#घोषणा SC16IS7XX_LCR_CONF_MODE_A	SC16IS7XX_LCR_DLAB_BIT /* Special
								* reg set */
#घोषणा SC16IS7XX_LCR_CONF_MODE_B	0xBF                   /* Enhanced
								* reg set */

/* MCR रेजिस्टर bits */
#घोषणा SC16IS7XX_MCR_DTR_BIT		(1 << 0) /* DTR complement
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MCR_RTS_BIT		(1 << 1) /* RTS complement */
#घोषणा SC16IS7XX_MCR_TCRTLR_BIT	(1 << 2) /* TCR/TLR रेजिस्टर enable */
#घोषणा SC16IS7XX_MCR_LOOP_BIT		(1 << 4) /* Enable loopback test mode */
#घोषणा SC16IS7XX_MCR_XOन_अंकY_BIT	(1 << 5) /* Enable Xon Any
						  * - ग_लिखो enabled
						  * अगर (EFR[4] == 1)
						  */
#घोषणा SC16IS7XX_MCR_IRDA_BIT		(1 << 6) /* Enable IrDA mode
						  * - ग_लिखो enabled
						  * अगर (EFR[4] == 1)
						  */
#घोषणा SC16IS7XX_MCR_CLKSEL_BIT	(1 << 7) /* Divide घड़ी by 4
						  * - ग_लिखो enabled
						  * अगर (EFR[4] == 1)
						  */

/* LSR रेजिस्टर bits */
#घोषणा SC16IS7XX_LSR_DR_BIT		(1 << 0) /* Receiver data पढ़ोy */
#घोषणा SC16IS7XX_LSR_OE_BIT		(1 << 1) /* Overrun Error */
#घोषणा SC16IS7XX_LSR_PE_BIT		(1 << 2) /* Parity Error */
#घोषणा SC16IS7XX_LSR_FE_BIT		(1 << 3) /* Frame Error */
#घोषणा SC16IS7XX_LSR_BI_BIT		(1 << 4) /* Break Interrupt */
#घोषणा SC16IS7XX_LSR_BRK_ERROR_MASK	0x1E     /* BI, FE, PE, OE bits */
#घोषणा SC16IS7XX_LSR_THRE_BIT		(1 << 5) /* TX holding रेजिस्टर empty */
#घोषणा SC16IS7XX_LSR_TEMT_BIT		(1 << 6) /* Transmitter empty */
#घोषणा SC16IS7XX_LSR_FIFOE_BIT		(1 << 7) /* Fअगरo Error */

/* MSR रेजिस्टर bits */
#घोषणा SC16IS7XX_MSR_DCTS_BIT		(1 << 0) /* Delta CTS Clear To Send */
#घोषणा SC16IS7XX_MSR_DDSR_BIT		(1 << 1) /* Delta DSR Data Set Ready
						  * or (IO4)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_DRI_BIT		(1 << 2) /* Delta RI Ring Indicator
						  * or (IO7)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_DCD_BIT		(1 << 3) /* Delta CD Carrier Detect
						  * or (IO6)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_CTS_BIT		(1 << 4) /* CTS */
#घोषणा SC16IS7XX_MSR_DSR_BIT		(1 << 5) /* DSR (IO4)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_RI_BIT		(1 << 6) /* RI (IO7)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_CD_BIT		(1 << 7) /* CD (IO6)
						  * - only on 75x/76x
						  */
#घोषणा SC16IS7XX_MSR_DELTA_MASK	0x0F     /* Any of the delta bits! */

/*
 * TCR रेजिस्टर bits
 * TCR trigger levels are available from 0 to 60 अक्षरacters with a granularity
 * of four.
 * The programmer must program the TCR such that TCR[3:0] > TCR[7:4]. There is
 * no built-in hardware check to make sure this condition is met. Also, the TCR
 * must be programmed with this condition beक्रमe स्वतः RTS or software flow
 * control is enabled to aव्योम spurious operation of the device.
 */
#घोषणा SC16IS7XX_TCR_RX_HALT(words)	((((words) / 4) & 0x0f) << 0)
#घोषणा SC16IS7XX_TCR_RX_RESUME(words)	((((words) / 4) & 0x0f) << 4)

/*
 * TLR रेजिस्टर bits
 * If TLR[3:0] or TLR[7:4] are logical 0, the selectable trigger levels via the
 * FIFO Control Register (FCR) are used क्रम the transmit and receive FIFO
 * trigger levels. Trigger levels from 4 अक्षरacters to 60 अक्षरacters are
 * available with a granularity of four.
 *
 * When the trigger level setting in TLR is zero, the SC16IS740/750/760 uses the
 * trigger level setting defined in FCR. If TLR has non-zero trigger level value
 * the trigger level defined in FCR is discarded. This applies to both transmit
 * FIFO and receive FIFO trigger level setting.
 *
 * When TLR is used क्रम RX trigger level control, FCR[7:6] should be left at the
 * शेष state, that is, '00'.
 */
#घोषणा SC16IS7XX_TLR_TX_TRIGGER(words)	((((words) / 4) & 0x0f) << 0)
#घोषणा SC16IS7XX_TLR_RX_TRIGGER(words)	((((words) / 4) & 0x0f) << 4)

/* IOControl रेजिस्टर bits (Only 750/760) */
#घोषणा SC16IS7XX_IOCONTROL_LATCH_BIT	(1 << 0) /* Enable input latching */
#घोषणा SC16IS7XX_IOCONTROL_MODEM_BIT	(1 << 1) /* Enable GPIO[7:4] as modem pins */
#घोषणा SC16IS7XX_IOCONTROL_SRESET_BIT	(1 << 3) /* Software Reset */

/* EFCR रेजिस्टर bits */
#घोषणा SC16IS7XX_EFCR_9BIT_MODE_BIT	(1 << 0) /* Enable 9-bit or Multidrop
						  * mode (RS485) */
#घोषणा SC16IS7XX_EFCR_RXDISABLE_BIT	(1 << 1) /* Disable receiver */
#घोषणा SC16IS7XX_EFCR_TXDISABLE_BIT	(1 << 2) /* Disable transmitter */
#घोषणा SC16IS7XX_EFCR_AUTO_RS485_BIT	(1 << 4) /* Auto RS485 RTS direction */
#घोषणा SC16IS7XX_EFCR_RTS_INVERT_BIT	(1 << 5) /* RTS output inversion */
#घोषणा SC16IS7XX_EFCR_IRDA_MODE_BIT	(1 << 7) /* IrDA mode
						  * 0 = rate upto 115.2 kbit/s
						  *   - Only 750/760
						  * 1 = rate upto 1.152 Mbit/s
						  *   - Only 760
						  */

/* EFR रेजिस्टर bits */
#घोषणा SC16IS7XX_EFR_AUTORTS_BIT	(1 << 6) /* Auto RTS flow ctrl enable */
#घोषणा SC16IS7XX_EFR_AUTOCTS_BIT	(1 << 7) /* Auto CTS flow ctrl enable */
#घोषणा SC16IS7XX_EFR_XOFF2_DETECT_BIT	(1 << 5) /* Enable Xoff2 detection */
#घोषणा SC16IS7XX_EFR_ENABLE_BIT	(1 << 4) /* Enable enhanced functions
						  * and writing to IER[7:4],
						  * FCR[5:4], MCR[7:5]
						  */
#घोषणा SC16IS7XX_EFR_SWFLOW3_BIT	(1 << 3) /* SWFLOW bit 3 */
#घोषणा SC16IS7XX_EFR_SWFLOW2_BIT	(1 << 2) /* SWFLOW bit 2
						  *
						  * SWFLOW bits 3 & 2 table:
						  * 00 -> no transmitter flow
						  *       control
						  * 01 -> transmitter generates
						  *       XON2 and XOFF2
						  * 10 -> transmitter generates
						  *       XON1 and XOFF1
						  * 11 -> transmitter generates
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2
						  */
#घोषणा SC16IS7XX_EFR_SWFLOW1_BIT	(1 << 1) /* SWFLOW bit 2 */
#घोषणा SC16IS7XX_EFR_SWFLOW0_BIT	(1 << 0) /* SWFLOW bit 3
						  *
						  * SWFLOW bits 3 & 2 table:
						  * 00 -> no received flow
						  *       control
						  * 01 -> receiver compares
						  *       XON2 and XOFF2
						  * 10 -> receiver compares
						  *       XON1 and XOFF1
						  * 11 -> receiver compares
						  *       XON1, XON2, XOFF1 and
						  *       XOFF2
						  */

/* Misc definitions */
#घोषणा SC16IS7XX_FIFO_SIZE		(64)
#घोषणा SC16IS7XX_REG_SHIFT		2

काष्ठा sc16is7xx_devtype अणु
	अक्षर	name[10];
	पूर्णांक	nr_gpio;
	पूर्णांक	nr_uart;
पूर्ण;

#घोषणा SC16IS7XX_RECONF_MD		(1 << 0)
#घोषणा SC16IS7XX_RECONF_IER		(1 << 1)
#घोषणा SC16IS7XX_RECONF_RS485		(1 << 2)

काष्ठा sc16is7xx_one_config अणु
	अचिन्हित पूर्णांक			flags;
	u8				ier_clear;
पूर्ण;

काष्ठा sc16is7xx_one अणु
	काष्ठा uart_port		port;
	u8				line;
	काष्ठा kthपढ़ो_work		tx_work;
	काष्ठा kthपढ़ो_work		reg_work;
	काष्ठा sc16is7xx_one_config	config;
	bool				irda_mode;
पूर्ण;

काष्ठा sc16is7xx_port अणु
	स्थिर काष्ठा sc16is7xx_devtype	*devtype;
	काष्ठा regmap			*regmap;
	काष्ठा clk			*clk;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip		gpio;
#पूर्ण_अगर
	अचिन्हित अक्षर			buf[SC16IS7XX_FIFO_SIZE];
	काष्ठा kthपढ़ो_worker		kworker;
	काष्ठा task_काष्ठा		*kworker_task;
	काष्ठा mutex			efr_lock;
	काष्ठा sc16is7xx_one		p[];
पूर्ण;

अटल अचिन्हित दीर्घ sc16is7xx_lines;

अटल काष्ठा uart_driver sc16is7xx_uart = अणु
	.owner		= THIS_MODULE,
	.dev_name	= "ttySC",
	.nr		= SC16IS7XX_MAX_DEVS,
पूर्ण;

#घोषणा to_sc16is7xx_port(p,e)	((container_of((p), काष्ठा sc16is7xx_port, e)))
#घोषणा to_sc16is7xx_one(p,e)	((container_of((p), काष्ठा sc16is7xx_one, e)))

अटल पूर्णांक sc16is7xx_line(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	वापस one->line;
पूर्ण

अटल u8 sc16is7xx_port_पढ़ो(काष्ठा uart_port *port, u8 reg)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक val = 0;
	स्थिर u8 line = sc16is7xx_line(port);

	regmap_पढ़ो(s->regmap, (reg << SC16IS7XX_REG_SHIFT) | line, &val);

	वापस val;
पूर्ण

अटल व्योम sc16is7xx_port_ग_लिखो(काष्ठा uart_port *port, u8 reg, u8 val)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	स्थिर u8 line = sc16is7xx_line(port);

	regmap_ग_लिखो(s->regmap, (reg << SC16IS7XX_REG_SHIFT) | line, val);
पूर्ण

अटल व्योम sc16is7xx_fअगरo_पढ़ो(काष्ठा uart_port *port, अचिन्हित पूर्णांक rxlen)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	स्थिर u8 line = sc16is7xx_line(port);
	u8 addr = (SC16IS7XX_RHR_REG << SC16IS7XX_REG_SHIFT) | line;

	regcache_cache_bypass(s->regmap, true);
	regmap_raw_पढ़ो(s->regmap, addr, s->buf, rxlen);
	regcache_cache_bypass(s->regmap, false);
पूर्ण

अटल व्योम sc16is7xx_fअगरo_ग_लिखो(काष्ठा uart_port *port, u8 to_send)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	स्थिर u8 line = sc16is7xx_line(port);
	u8 addr = (SC16IS7XX_THR_REG << SC16IS7XX_REG_SHIFT) | line;

	/*
	 * Don't send zero-length data, at least on SPI it confuses the chip
	 * delivering wrong TXLVL data.
	 */
	अगर (unlikely(!to_send))
		वापस;

	regcache_cache_bypass(s->regmap, true);
	regmap_raw_ग_लिखो(s->regmap, addr, s->buf, to_send);
	regcache_cache_bypass(s->regmap, false);
पूर्ण

अटल व्योम sc16is7xx_port_update(काष्ठा uart_port *port, u8 reg,
				  u8 mask, u8 val)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	स्थिर u8 line = sc16is7xx_line(port);

	regmap_update_bits(s->regmap, (reg << SC16IS7XX_REG_SHIFT) | line,
			   mask, val);
पूर्ण

अटल पूर्णांक sc16is7xx_alloc_line(व्योम)
अणु
	पूर्णांक i;

	BUILD_BUG_ON(SC16IS7XX_MAX_DEVS > BITS_PER_LONG);

	क्रम (i = 0; i < SC16IS7XX_MAX_DEVS; i++)
		अगर (!test_and_set_bit(i, &sc16is7xx_lines))
			अवरोध;

	वापस i;
पूर्ण

अटल व्योम sc16is7xx_घातer(काष्ठा uart_port *port, पूर्णांक on)
अणु
	sc16is7xx_port_update(port, SC16IS7XX_IER_REG,
			      SC16IS7XX_IER_SLEEP_BIT,
			      on ? 0 : SC16IS7XX_IER_SLEEP_BIT);
पूर्ण

अटल स्थिर काष्ठा sc16is7xx_devtype sc16is74x_devtype = अणु
	.name		= "SC16IS74X",
	.nr_gpio	= 0,
	.nr_uart	= 1,
पूर्ण;

अटल स्थिर काष्ठा sc16is7xx_devtype sc16is750_devtype = अणु
	.name		= "SC16IS750",
	.nr_gpio	= 8,
	.nr_uart	= 1,
पूर्ण;

अटल स्थिर काष्ठा sc16is7xx_devtype sc16is752_devtype = अणु
	.name		= "SC16IS752",
	.nr_gpio	= 8,
	.nr_uart	= 2,
पूर्ण;

अटल स्थिर काष्ठा sc16is7xx_devtype sc16is760_devtype = अणु
	.name		= "SC16IS760",
	.nr_gpio	= 8,
	.nr_uart	= 1,
पूर्ण;

अटल स्थिर काष्ठा sc16is7xx_devtype sc16is762_devtype = अणु
	.name		= "SC16IS762",
	.nr_gpio	= 8,
	.nr_uart	= 2,
पूर्ण;

अटल bool sc16is7xx_regmap_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg >> SC16IS7XX_REG_SHIFT) अणु
	हाल SC16IS7XX_RHR_REG:
	हाल SC16IS7XX_IIR_REG:
	हाल SC16IS7XX_LSR_REG:
	हाल SC16IS7XX_MSR_REG:
	हाल SC16IS7XX_TXLVL_REG:
	हाल SC16IS7XX_RXLVL_REG:
	हाल SC16IS7XX_IOSTATE_REG:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool sc16is7xx_regmap_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg >> SC16IS7XX_REG_SHIFT) अणु
	हाल SC16IS7XX_RHR_REG:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक sc16is7xx_set_baud(काष्ठा uart_port *port, पूर्णांक baud)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	u8 lcr;
	u8 prescaler = 0;
	अचिन्हित दीर्घ clk = port->uartclk, भाग = clk / 16 / baud;

	अगर (भाग > 0xffff) अणु
		prescaler = SC16IS7XX_MCR_CLKSEL_BIT;
		भाग /= 4;
	पूर्ण

	/* In an amazing feat of design, the Enhanced Features Register shares
	 * the address of the Interrupt Identअगरication Register, and is
	 * चयनed in by writing a magic value (0xbf) to the Line Control
	 * Register. Any पूर्णांकerrupt firing during this समय will see the EFR
	 * where it expects the IIR to be, leading to "Unexpected interrupt"
	 * messages.
	 *
	 * Prevent this possibility by claiming a mutex जबतक accessing the
	 * EFR, and claiming the same mutex from within the पूर्णांकerrupt handler.
	 * This is similar to disabling the पूर्णांकerrupt, but that करोesn't work
	 * because the bulk of the पूर्णांकerrupt processing is run as a workqueue
	 * job in thपढ़ो context.
	 */
	mutex_lock(&s->efr_lock);

	lcr = sc16is7xx_port_पढ़ो(port, SC16IS7XX_LCR_REG);

	/* Open the LCR भागisors क्रम configuration */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_B);

	/* Enable enhanced features */
	regcache_cache_bypass(s->regmap, true);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_EFR_REG,
			     SC16IS7XX_EFR_ENABLE_BIT);
	regcache_cache_bypass(s->regmap, false);

	/* Put LCR back to the normal mode */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG, lcr);

	mutex_unlock(&s->efr_lock);

	sc16is7xx_port_update(port, SC16IS7XX_MCR_REG,
			      SC16IS7XX_MCR_CLKSEL_BIT,
			      prescaler);

	/* Open the LCR भागisors क्रम configuration */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_A);

	/* Write the new भागisor */
	regcache_cache_bypass(s->regmap, true);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_DLH_REG, भाग / 256);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_DLL_REG, भाग % 256);
	regcache_cache_bypass(s->regmap, false);

	/* Put LCR back to the normal mode */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG, lcr);

	वापस DIV_ROUND_CLOSEST(clk / 16, भाग);
पूर्ण

अटल व्योम sc16is7xx_handle_rx(काष्ठा uart_port *port, अचिन्हित पूर्णांक rxlen,
				अचिन्हित पूर्णांक iir)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक lsr = 0, ch, flag, bytes_पढ़ो, i;
	bool पढ़ो_lsr = (iir == SC16IS7XX_IIR_RLSE_SRC) ? true : false;

	अगर (unlikely(rxlen >= माप(s->buf))) अणु
		dev_warn_ratelimited(port->dev,
				     "ttySC%i: Possible RX FIFO overrun: %d\n",
				     port->line, rxlen);
		port->icount.buf_overrun++;
		/* Ensure sanity of RX level */
		rxlen = माप(s->buf);
	पूर्ण

	जबतक (rxlen) अणु
		/* Only पढ़ो lsr अगर there are possible errors in FIFO */
		अगर (पढ़ो_lsr) अणु
			lsr = sc16is7xx_port_पढ़ो(port, SC16IS7XX_LSR_REG);
			अगर (!(lsr & SC16IS7XX_LSR_FIFOE_BIT))
				पढ़ो_lsr = false; /* No errors left in FIFO */
		पूर्ण अन्यथा
			lsr = 0;

		अगर (पढ़ो_lsr) अणु
			s->buf[0] = sc16is7xx_port_पढ़ो(port, SC16IS7XX_RHR_REG);
			bytes_पढ़ो = 1;
		पूर्ण अन्यथा अणु
			sc16is7xx_fअगरo_पढ़ो(port, rxlen);
			bytes_पढ़ो = rxlen;
		पूर्ण

		lsr &= SC16IS7XX_LSR_BRK_ERROR_MASK;

		port->icount.rx++;
		flag = TTY_NORMAL;

		अगर (unlikely(lsr)) अणु
			अगर (lsr & SC16IS7XX_LSR_BI_BIT) अणु
				port->icount.brk++;
				अगर (uart_handle_अवरोध(port))
					जारी;
			पूर्ण अन्यथा अगर (lsr & SC16IS7XX_LSR_PE_BIT)
				port->icount.parity++;
			अन्यथा अगर (lsr & SC16IS7XX_LSR_FE_BIT)
				port->icount.frame++;
			अन्यथा अगर (lsr & SC16IS7XX_LSR_OE_BIT)
				port->icount.overrun++;

			lsr &= port->पढ़ो_status_mask;
			अगर (lsr & SC16IS7XX_LSR_BI_BIT)
				flag = TTY_BREAK;
			अन्यथा अगर (lsr & SC16IS7XX_LSR_PE_BIT)
				flag = TTY_PARITY;
			अन्यथा अगर (lsr & SC16IS7XX_LSR_FE_BIT)
				flag = TTY_FRAME;
			अन्यथा अगर (lsr & SC16IS7XX_LSR_OE_BIT)
				flag = TTY_OVERRUN;
		पूर्ण

		क्रम (i = 0; i < bytes_पढ़ो; ++i) अणु
			ch = s->buf[i];
			अगर (uart_handle_sysrq_अक्षर(port, ch))
				जारी;

			अगर (lsr & port->ignore_status_mask)
				जारी;

			uart_insert_अक्षर(port, lsr, SC16IS7XX_LSR_OE_BIT, ch,
					 flag);
		पूर्ण
		rxlen -= bytes_पढ़ो;
	पूर्ण

	tty_flip_buffer_push(&port->state->port);
पूर्ण

अटल व्योम sc16is7xx_handle_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	काष्ठा circ_buf *xmit = &port->state->xmit;
	अचिन्हित पूर्णांक txlen, to_send, i;

	अगर (unlikely(port->x_अक्षर)) अणु
		sc16is7xx_port_ग_लिखो(port, SC16IS7XX_THR_REG, port->x_अक्षर);
		port->icount.tx++;
		port->x_अक्षर = 0;
		वापस;
	पूर्ण

	अगर (uart_circ_empty(xmit) || uart_tx_stopped(port))
		वापस;

	/* Get length of data pending in circular buffer */
	to_send = uart_circ_अक्षरs_pending(xmit);
	अगर (likely(to_send)) अणु
		/* Limit to size of TX FIFO */
		txlen = sc16is7xx_port_पढ़ो(port, SC16IS7XX_TXLVL_REG);
		अगर (txlen > SC16IS7XX_FIFO_SIZE) अणु
			dev_err_ratelimited(port->dev,
				"chip reports %d free bytes in TX fifo, but it only has %d",
				txlen, SC16IS7XX_FIFO_SIZE);
			txlen = 0;
		पूर्ण
		to_send = (to_send > txlen) ? txlen : to_send;

		/* Add data to send */
		port->icount.tx += to_send;

		/* Convert to linear buffer */
		क्रम (i = 0; i < to_send; ++i) अणु
			s->buf[i] = xmit->buf[xmit->tail];
			xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		पूर्ण

		sc16is7xx_fअगरo_ग_लिखो(port, to_send);
	पूर्ण

	अगर (uart_circ_अक्षरs_pending(xmit) < WAKEUP_CHARS)
		uart_ग_लिखो_wakeup(port);
पूर्ण

अटल bool sc16is7xx_port_irq(काष्ठा sc16is7xx_port *s, पूर्णांक portno)
अणु
	काष्ठा uart_port *port = &s->p[portno].port;

	करो अणु
		अचिन्हित पूर्णांक iir, rxlen;

		iir = sc16is7xx_port_पढ़ो(port, SC16IS7XX_IIR_REG);
		अगर (iir & SC16IS7XX_IIR_NO_INT_BIT)
			वापस false;

		iir &= SC16IS7XX_IIR_ID_MASK;

		चयन (iir) अणु
		हाल SC16IS7XX_IIR_RDI_SRC:
		हाल SC16IS7XX_IIR_RLSE_SRC:
		हाल SC16IS7XX_IIR_RTOI_SRC:
		हाल SC16IS7XX_IIR_XOFFI_SRC:
			rxlen = sc16is7xx_port_पढ़ो(port, SC16IS7XX_RXLVL_REG);
			अगर (rxlen)
				sc16is7xx_handle_rx(port, rxlen, iir);
			अवरोध;
		हाल SC16IS7XX_IIR_THRI_SRC:
			sc16is7xx_handle_tx(port);
			अवरोध;
		शेष:
			dev_err_ratelimited(port->dev,
					    "ttySC%i: Unexpected interrupt: %x",
					    port->line, iir);
			अवरोध;
		पूर्ण
	पूर्ण जबतक (0);
	वापस true;
पूर्ण

अटल irqवापस_t sc16is7xx_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sc16is7xx_port *s = (काष्ठा sc16is7xx_port *)dev_id;

	mutex_lock(&s->efr_lock);

	जबतक (1) अणु
		bool keep_polling = false;
		पूर्णांक i;

		क्रम (i = 0; i < s->devtype->nr_uart; ++i)
			keep_polling |= sc16is7xx_port_irq(s, i);
		अगर (!keep_polling)
			अवरोध;
	पूर्ण

	mutex_unlock(&s->efr_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sc16is7xx_tx_proc(काष्ठा kthपढ़ो_work *ws)
अणु
	काष्ठा uart_port *port = &(to_sc16is7xx_one(ws, tx_work)->port);

	अगर ((port->rs485.flags & SER_RS485_ENABLED) &&
	    (port->rs485.delay_rts_beक्रमe_send > 0))
		msleep(port->rs485.delay_rts_beक्रमe_send);

	sc16is7xx_handle_tx(port);
पूर्ण

अटल व्योम sc16is7xx_reconf_rs485(काष्ठा uart_port *port)
अणु
	स्थिर u32 mask = SC16IS7XX_EFCR_AUTO_RS485_BIT |
			 SC16IS7XX_EFCR_RTS_INVERT_BIT;
	u32 efcr = 0;
	काष्ठा serial_rs485 *rs485 = &port->rs485;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&port->lock, irqflags);
	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		efcr |=	SC16IS7XX_EFCR_AUTO_RS485_BIT;

		अगर (rs485->flags & SER_RS485_RTS_AFTER_SEND)
			efcr |= SC16IS7XX_EFCR_RTS_INVERT_BIT;
	पूर्ण
	spin_unlock_irqrestore(&port->lock, irqflags);

	sc16is7xx_port_update(port, SC16IS7XX_EFCR_REG, mask, efcr);
पूर्ण

अटल व्योम sc16is7xx_reg_proc(काष्ठा kthपढ़ो_work *ws)
अणु
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(ws, reg_work);
	काष्ठा sc16is7xx_one_config config;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&one->port.lock, irqflags);
	config = one->config;
	स_रखो(&one->config, 0, माप(one->config));
	spin_unlock_irqrestore(&one->port.lock, irqflags);

	अगर (config.flags & SC16IS7XX_RECONF_MD) अणु
		sc16is7xx_port_update(&one->port, SC16IS7XX_MCR_REG,
				      SC16IS7XX_MCR_LOOP_BIT,
				      (one->port.mctrl & TIOCM_LOOP) ?
				      SC16IS7XX_MCR_LOOP_BIT : 0);
		sc16is7xx_port_update(&one->port, SC16IS7XX_MCR_REG,
				      SC16IS7XX_MCR_RTS_BIT,
				      (one->port.mctrl & TIOCM_RTS) ?
				      SC16IS7XX_MCR_RTS_BIT : 0);
		sc16is7xx_port_update(&one->port, SC16IS7XX_MCR_REG,
				      SC16IS7XX_MCR_DTR_BIT,
				      (one->port.mctrl & TIOCM_DTR) ?
				      SC16IS7XX_MCR_DTR_BIT : 0);
	पूर्ण
	अगर (config.flags & SC16IS7XX_RECONF_IER)
		sc16is7xx_port_update(&one->port, SC16IS7XX_IER_REG,
				      config.ier_clear, 0);

	अगर (config.flags & SC16IS7XX_RECONF_RS485)
		sc16is7xx_reconf_rs485(&one->port);
पूर्ण

अटल व्योम sc16is7xx_ier_clear(काष्ठा uart_port *port, u8 bit)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	one->config.flags |= SC16IS7XX_RECONF_IER;
	one->config.ier_clear |= bit;
	kthपढ़ो_queue_work(&s->kworker, &one->reg_work);
पूर्ण

अटल व्योम sc16is7xx_stop_tx(काष्ठा uart_port *port)
अणु
	sc16is7xx_ier_clear(port, SC16IS7XX_IER_THRI_BIT);
पूर्ण

अटल व्योम sc16is7xx_stop_rx(काष्ठा uart_port *port)
अणु
	sc16is7xx_ier_clear(port, SC16IS7XX_IER_RDI_BIT);
पूर्ण

अटल व्योम sc16is7xx_start_tx(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	kthपढ़ो_queue_work(&s->kworker, &one->tx_work);
पूर्ण

अटल अचिन्हित पूर्णांक sc16is7xx_tx_empty(काष्ठा uart_port *port)
अणु
	अचिन्हित पूर्णांक lsr;

	lsr = sc16is7xx_port_पढ़ो(port, SC16IS7XX_LSR_REG);

	वापस (lsr & SC16IS7XX_LSR_TEMT_BIT) ? TIOCSER_TEMT : 0;
पूर्ण

अटल अचिन्हित पूर्णांक sc16is7xx_get_mctrl(काष्ठा uart_port *port)
अणु
	/* DCD and DSR are not wired and CTS/RTS is handled स्वतःmatically
	 * so just indicate DSR and CAR निश्चितed
	 */
	वापस TIOCM_DSR | TIOCM_CAR;
पूर्ण

अटल व्योम sc16is7xx_set_mctrl(काष्ठा uart_port *port, अचिन्हित पूर्णांक mctrl)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	one->config.flags |= SC16IS7XX_RECONF_MD;
	kthपढ़ो_queue_work(&s->kworker, &one->reg_work);
पूर्ण

अटल व्योम sc16is7xx_अवरोध_ctl(काष्ठा uart_port *port, पूर्णांक अवरोध_state)
अणु
	sc16is7xx_port_update(port, SC16IS7XX_LCR_REG,
			      SC16IS7XX_LCR_TXBREAK_BIT,
			      अवरोध_state ? SC16IS7XX_LCR_TXBREAK_BIT : 0);
पूर्ण

अटल व्योम sc16is7xx_set_termios(काष्ठा uart_port *port,
				  काष्ठा ktermios *termios,
				  काष्ठा ktermios *old)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक lcr, flow = 0;
	पूर्णांक baud;

	/* Mask termios capabilities we करोn't support */
	termios->c_cflag &= ~CMSPAR;

	/* Word size */
	चयन (termios->c_cflag & CSIZE) अणु
	हाल CS5:
		lcr = SC16IS7XX_LCR_WORD_LEN_5;
		अवरोध;
	हाल CS6:
		lcr = SC16IS7XX_LCR_WORD_LEN_6;
		अवरोध;
	हाल CS7:
		lcr = SC16IS7XX_LCR_WORD_LEN_7;
		अवरोध;
	हाल CS8:
		lcr = SC16IS7XX_LCR_WORD_LEN_8;
		अवरोध;
	शेष:
		lcr = SC16IS7XX_LCR_WORD_LEN_8;
		termios->c_cflag &= ~CSIZE;
		termios->c_cflag |= CS8;
		अवरोध;
	पूर्ण

	/* Parity */
	अगर (termios->c_cflag & PARENB) अणु
		lcr |= SC16IS7XX_LCR_PARITY_BIT;
		अगर (!(termios->c_cflag & PARODD))
			lcr |= SC16IS7XX_LCR_EVENPARITY_BIT;
	पूर्ण

	/* Stop bits */
	अगर (termios->c_cflag & CSTOPB)
		lcr |= SC16IS7XX_LCR_STOPLEN_BIT; /* 2 stops */

	/* Set पढ़ो status mask */
	port->पढ़ो_status_mask = SC16IS7XX_LSR_OE_BIT;
	अगर (termios->c_अगरlag & INPCK)
		port->पढ़ो_status_mask |= SC16IS7XX_LSR_PE_BIT |
					  SC16IS7XX_LSR_FE_BIT;
	अगर (termios->c_अगरlag & (BRKINT | PARMRK))
		port->पढ़ो_status_mask |= SC16IS7XX_LSR_BI_BIT;

	/* Set status ignore mask */
	port->ignore_status_mask = 0;
	अगर (termios->c_अगरlag & IGNBRK)
		port->ignore_status_mask |= SC16IS7XX_LSR_BI_BIT;
	अगर (!(termios->c_cflag & CREAD))
		port->ignore_status_mask |= SC16IS7XX_LSR_BRK_ERROR_MASK;

	/* As above, claim the mutex जबतक accessing the EFR. */
	mutex_lock(&s->efr_lock);

	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_B);

	/* Configure flow control */
	regcache_cache_bypass(s->regmap, true);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_XON1_REG, termios->c_cc[VSTART]);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_XOFF1_REG, termios->c_cc[VSTOP]);
	अगर (termios->c_cflag & CRTSCTS)
		flow |= SC16IS7XX_EFR_AUTOCTS_BIT |
			SC16IS7XX_EFR_AUTORTS_BIT;
	अगर (termios->c_अगरlag & IXON)
		flow |= SC16IS7XX_EFR_SWFLOW3_BIT;
	अगर (termios->c_अगरlag & IXOFF)
		flow |= SC16IS7XX_EFR_SWFLOW1_BIT;

	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_EFR_REG, flow);
	regcache_cache_bypass(s->regmap, false);

	/* Update LCR रेजिस्टर */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG, lcr);

	mutex_unlock(&s->efr_lock);

	/* Get baud rate generator configuration */
	baud = uart_get_baud_rate(port, termios, old,
				  port->uartclk / 16 / 4 / 0xffff,
				  port->uartclk / 16);

	/* Setup baudrate generator */
	baud = sc16is7xx_set_baud(port, baud);

	/* Update समयout according to new baud rate */
	uart_update_समयout(port, termios->c_cflag, baud);
पूर्ण

अटल पूर्णांक sc16is7xx_config_rs485(काष्ठा uart_port *port,
				  काष्ठा serial_rs485 *rs485)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);

	अगर (rs485->flags & SER_RS485_ENABLED) अणु
		bool rts_during_rx, rts_during_tx;

		rts_during_rx = rs485->flags & SER_RS485_RTS_AFTER_SEND;
		rts_during_tx = rs485->flags & SER_RS485_RTS_ON_SEND;

		अगर (rts_during_rx == rts_during_tx)
			dev_err(port->dev,
				"unsupported RTS signalling on_send:%d after_send:%d - exactly one of RS485 RTS flags should be set\n",
				rts_during_tx, rts_during_rx);

		/*
		 * RTS संकेत is handled by HW, it's timing can't be influenced.
		 * However, it's someबार useful to delay TX even without RTS
		 * control thereक्रमe we try to handle .delay_rts_beक्रमe_send.
		 */
		अगर (rs485->delay_rts_after_send)
			वापस -EINVAL;
	पूर्ण

	port->rs485 = *rs485;
	one->config.flags |= SC16IS7XX_RECONF_RS485;
	kthपढ़ो_queue_work(&s->kworker, &one->reg_work);

	वापस 0;
पूर्ण

अटल पूर्णांक sc16is7xx_startup(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_one *one = to_sc16is7xx_one(port, port);
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);
	अचिन्हित पूर्णांक val;

	sc16is7xx_घातer(port, 1);

	/* Reset FIFOs*/
	val = SC16IS7XX_FCR_RXRESET_BIT | SC16IS7XX_FCR_TXRESET_BIT;
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_FCR_REG, val);
	udelay(5);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_FCR_REG,
			     SC16IS7XX_FCR_FIFO_BIT);

	/* Enable EFR */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG,
			     SC16IS7XX_LCR_CONF_MODE_B);

	regcache_cache_bypass(s->regmap, true);

	/* Enable ग_लिखो access to enhanced features and पूर्णांकernal घड़ी भाग */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_EFR_REG,
			     SC16IS7XX_EFR_ENABLE_BIT);

	/* Enable TCR/TLR */
	sc16is7xx_port_update(port, SC16IS7XX_MCR_REG,
			      SC16IS7XX_MCR_TCRTLR_BIT,
			      SC16IS7XX_MCR_TCRTLR_BIT);

	/* Configure flow control levels */
	/* Flow control halt level 48, resume level 24 */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_TCR_REG,
			     SC16IS7XX_TCR_RX_RESUME(24) |
			     SC16IS7XX_TCR_RX_HALT(48));

	regcache_cache_bypass(s->regmap, false);

	/* Now, initialize the UART */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_LCR_REG, SC16IS7XX_LCR_WORD_LEN_8);

	/* Enable IrDA mode अगर requested in DT */
	/* This bit must be written with LCR[7] = 0 */
	sc16is7xx_port_update(port, SC16IS7XX_MCR_REG,
			      SC16IS7XX_MCR_IRDA_BIT,
			      one->irda_mode ?
				SC16IS7XX_MCR_IRDA_BIT : 0);

	/* Enable the Rx and Tx FIFO */
	sc16is7xx_port_update(port, SC16IS7XX_EFCR_REG,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT,
			      0);

	/* Enable RX, TX पूर्णांकerrupts */
	val = SC16IS7XX_IER_RDI_BIT | SC16IS7XX_IER_THRI_BIT;
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_IER_REG, val);

	वापस 0;
पूर्ण

अटल व्योम sc16is7xx_shutकरोwn(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);

	/* Disable all पूर्णांकerrupts */
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_IER_REG, 0);
	/* Disable TX/RX */
	sc16is7xx_port_update(port, SC16IS7XX_EFCR_REG,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT);

	sc16is7xx_घातer(port, 0);

	kthपढ़ो_flush_worker(&s->kworker);
पूर्ण

अटल स्थिर अक्षर *sc16is7xx_type(काष्ठा uart_port *port)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(port->dev);

	वापस (port->type == PORT_SC16IS7XX) ? s->devtype->name : शून्य;
पूर्ण

अटल पूर्णांक sc16is7xx_request_port(काष्ठा uart_port *port)
अणु
	/* Do nothing */
	वापस 0;
पूर्ण

अटल व्योम sc16is7xx_config_port(काष्ठा uart_port *port, पूर्णांक flags)
अणु
	अगर (flags & UART_CONFIG_TYPE)
		port->type = PORT_SC16IS7XX;
पूर्ण

अटल पूर्णांक sc16is7xx_verअगरy_port(काष्ठा uart_port *port,
				 काष्ठा serial_काष्ठा *s)
अणु
	अगर ((s->type != PORT_UNKNOWN) && (s->type != PORT_SC16IS7XX))
		वापस -EINVAL;
	अगर (s->irq != port->irq)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम sc16is7xx_pm(काष्ठा uart_port *port, अचिन्हित पूर्णांक state,
			 अचिन्हित पूर्णांक oldstate)
अणु
	sc16is7xx_घातer(port, (state == UART_PM_STATE_ON) ? 1 : 0);
पूर्ण

अटल व्योम sc16is7xx_null_व्योम(काष्ठा uart_port *port)
अणु
	/* Do nothing */
पूर्ण

अटल स्थिर काष्ठा uart_ops sc16is7xx_ops = अणु
	.tx_empty	= sc16is7xx_tx_empty,
	.set_mctrl	= sc16is7xx_set_mctrl,
	.get_mctrl	= sc16is7xx_get_mctrl,
	.stop_tx	= sc16is7xx_stop_tx,
	.start_tx	= sc16is7xx_start_tx,
	.stop_rx	= sc16is7xx_stop_rx,
	.अवरोध_ctl	= sc16is7xx_अवरोध_ctl,
	.startup	= sc16is7xx_startup,
	.shutकरोwn	= sc16is7xx_shutकरोwn,
	.set_termios	= sc16is7xx_set_termios,
	.type		= sc16is7xx_type,
	.request_port	= sc16is7xx_request_port,
	.release_port	= sc16is7xx_null_व्योम,
	.config_port	= sc16is7xx_config_port,
	.verअगरy_port	= sc16is7xx_verअगरy_port,
	.pm		= sc16is7xx_pm,
पूर्ण;

#अगर_घोषित CONFIG_GPIOLIB
अटल पूर्णांक sc16is7xx_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	अचिन्हित पूर्णांक val;
	काष्ठा sc16is7xx_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[0].port;

	val = sc16is7xx_port_पढ़ो(port, SC16IS7XX_IOSTATE_REG);

	वापस !!(val & BIT(offset));
पूर्ण

अटल व्योम sc16is7xx_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा sc16is7xx_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[0].port;

	sc16is7xx_port_update(port, SC16IS7XX_IOSTATE_REG, BIT(offset),
			      val ? BIT(offset) : 0);
पूर्ण

अटल पूर्णांक sc16is7xx_gpio_direction_input(काष्ठा gpio_chip *chip,
					  अचिन्हित offset)
अणु
	काष्ठा sc16is7xx_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[0].port;

	sc16is7xx_port_update(port, SC16IS7XX_IOसूची_REG, BIT(offset), 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sc16is7xx_gpio_direction_output(काष्ठा gpio_chip *chip,
					   अचिन्हित offset, पूर्णांक val)
अणु
	काष्ठा sc16is7xx_port *s = gpiochip_get_data(chip);
	काष्ठा uart_port *port = &s->p[0].port;
	u8 state = sc16is7xx_port_पढ़ो(port, SC16IS7XX_IOSTATE_REG);

	अगर (val)
		state |= BIT(offset);
	अन्यथा
		state &= ~BIT(offset);
	sc16is7xx_port_ग_लिखो(port, SC16IS7XX_IOSTATE_REG, state);
	sc16is7xx_port_update(port, SC16IS7XX_IOसूची_REG, BIT(offset),
			      BIT(offset));

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sc16is7xx_probe(काष्ठा device *dev,
			   स्थिर काष्ठा sc16is7xx_devtype *devtype,
			   काष्ठा regmap *regmap, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ freq = 0, *pfreq = dev_get_platdata(dev);
	अचिन्हित पूर्णांक val;
	u32 uartclk = 0;
	पूर्णांक i, ret;
	काष्ठा sc16is7xx_port *s;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/*
	 * This device करोes not have an identअगरication रेजिस्टर that would
	 * tell us अगर we are really connected to the correct device.
	 * The best we can करो is to check अगर communication is at all possible.
	 */
	ret = regmap_पढ़ो(regmap,
			  SC16IS7XX_LSR_REG << SC16IS7XX_REG_SHIFT, &val);
	अगर (ret < 0)
		वापस -EPROBE_DEFER;

	/* Alloc port काष्ठाure */
	s = devm_kzalloc(dev, काष्ठा_size(s, p, devtype->nr_uart), GFP_KERNEL);
	अगर (!s) अणु
		dev_err(dev, "Error allocating port structure\n");
		वापस -ENOMEM;
	पूर्ण

	/* Always ask क्रम fixed घड़ी rate from a property. */
	device_property_पढ़ो_u32(dev, "clock-frequency", &uartclk);

	s->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(s->clk)) अणु
		अगर (uartclk)
			freq = uartclk;
		अगर (pfreq)
			freq = *pfreq;
		अगर (freq)
			dev_dbg(dev, "Clock frequency: %luHz\n", freq);
		अन्यथा
			वापस PTR_ERR(s->clk);
	पूर्ण अन्यथा अणु
		ret = clk_prepare_enable(s->clk);
		अगर (ret)
			वापस ret;

		freq = clk_get_rate(s->clk);
	पूर्ण

	s->regmap = regmap;
	s->devtype = devtype;
	dev_set_drvdata(dev, s);
	mutex_init(&s->efr_lock);

	kthपढ़ो_init_worker(&s->kworker);
	s->kworker_task = kthपढ़ो_run(kthपढ़ो_worker_fn, &s->kworker,
				      "sc16is7xx");
	अगर (IS_ERR(s->kworker_task)) अणु
		ret = PTR_ERR(s->kworker_task);
		जाओ out_clk;
	पूर्ण
	sched_set_fअगरo(s->kworker_task);

#अगर_घोषित CONFIG_GPIOLIB
	अगर (devtype->nr_gpio) अणु
		/* Setup GPIO cotroller */
		s->gpio.owner		 = THIS_MODULE;
		s->gpio.parent		 = dev;
		s->gpio.label		 = dev_name(dev);
		s->gpio.direction_input	 = sc16is7xx_gpio_direction_input;
		s->gpio.get		 = sc16is7xx_gpio_get;
		s->gpio.direction_output = sc16is7xx_gpio_direction_output;
		s->gpio.set		 = sc16is7xx_gpio_set;
		s->gpio.base		 = -1;
		s->gpio.ngpio		 = devtype->nr_gpio;
		s->gpio.can_sleep	 = 1;
		ret = gpiochip_add_data(&s->gpio, s);
		अगर (ret)
			जाओ out_thपढ़ो;
	पूर्ण
#पूर्ण_अगर

	/* reset device, purging any pending irq / data */
	regmap_ग_लिखो(s->regmap, SC16IS7XX_IOCONTROL_REG << SC16IS7XX_REG_SHIFT,
			SC16IS7XX_IOCONTROL_SRESET_BIT);

	क्रम (i = 0; i < devtype->nr_uart; ++i) अणु
		s->p[i].line		= i;
		/* Initialize port data */
		s->p[i].port.dev	= dev;
		s->p[i].port.irq	= irq;
		s->p[i].port.type	= PORT_SC16IS7XX;
		s->p[i].port.fअगरosize	= SC16IS7XX_FIFO_SIZE;
		s->p[i].port.flags	= UPF_FIXED_TYPE | UPF_LOW_LATENCY;
		s->p[i].port.iobase	= i;
		s->p[i].port.iotype	= UPIO_PORT;
		s->p[i].port.uartclk	= freq;
		s->p[i].port.rs485_config = sc16is7xx_config_rs485;
		s->p[i].port.ops	= &sc16is7xx_ops;
		s->p[i].port.line	= sc16is7xx_alloc_line();
		अगर (s->p[i].port.line >= SC16IS7XX_MAX_DEVS) अणु
			ret = -ENOMEM;
			जाओ out_ports;
		पूर्ण

		/* Disable all पूर्णांकerrupts */
		sc16is7xx_port_ग_लिखो(&s->p[i].port, SC16IS7XX_IER_REG, 0);
		/* Disable TX/RX */
		sc16is7xx_port_ग_लिखो(&s->p[i].port, SC16IS7XX_EFCR_REG,
				     SC16IS7XX_EFCR_RXDISABLE_BIT |
				     SC16IS7XX_EFCR_TXDISABLE_BIT);
		/* Initialize kthपढ़ो work काष्ठाs */
		kthपढ़ो_init_work(&s->p[i].tx_work, sc16is7xx_tx_proc);
		kthपढ़ो_init_work(&s->p[i].reg_work, sc16is7xx_reg_proc);
		/* Register port */
		uart_add_one_port(&sc16is7xx_uart, &s->p[i].port);

		/* Enable EFR */
		sc16is7xx_port_ग_लिखो(&s->p[i].port, SC16IS7XX_LCR_REG,
				     SC16IS7XX_LCR_CONF_MODE_B);

		regcache_cache_bypass(s->regmap, true);

		/* Enable ग_लिखो access to enhanced features */
		sc16is7xx_port_ग_लिखो(&s->p[i].port, SC16IS7XX_EFR_REG,
				     SC16IS7XX_EFR_ENABLE_BIT);

		regcache_cache_bypass(s->regmap, false);

		/* Restore access to general रेजिस्टरs */
		sc16is7xx_port_ग_लिखो(&s->p[i].port, SC16IS7XX_LCR_REG, 0x00);

		/* Go to suspend mode */
		sc16is7xx_घातer(&s->p[i].port, 0);
	पूर्ण

	अगर (dev->of_node) अणु
		काष्ठा property *prop;
		स्थिर __be32 *p;
		u32 u;

		of_property_क्रम_each_u32(dev->of_node, "irda-mode-ports",
					 prop, p, u)
			अगर (u < devtype->nr_uart)
				s->p[u].irda_mode = true;
	पूर्ण

	/*
	 * Setup पूर्णांकerrupt. We first try to acquire the IRQ line as level IRQ.
	 * If that succeeds, we can allow sharing the पूर्णांकerrupt as well.
	 * In हाल the पूर्णांकerrupt controller करोesn't support that, we fall
	 * back to a non-shared falling-edge trigger.
	 */
	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, sc16is7xx_irq,
					IRQF_TRIGGER_LOW | IRQF_SHARED |
					IRQF_ONESHOT,
					dev_name(dev), s);
	अगर (!ret)
		वापस 0;

	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, sc16is7xx_irq,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					dev_name(dev), s);
	अगर (!ret)
		वापस 0;

out_ports:
	क्रम (i--; i >= 0; i--) अणु
		uart_हटाओ_one_port(&sc16is7xx_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, &sc16is7xx_lines);
	पूर्ण

#अगर_घोषित CONFIG_GPIOLIB
	अगर (devtype->nr_gpio)
		gpiochip_हटाओ(&s->gpio);

out_thपढ़ो:
#पूर्ण_अगर
	kthपढ़ो_stop(s->kworker_task);

out_clk:
	अगर (!IS_ERR(s->clk))
		clk_disable_unprepare(s->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sc16is7xx_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sc16is7xx_port *s = dev_get_drvdata(dev);
	पूर्णांक i;

#अगर_घोषित CONFIG_GPIOLIB
	अगर (s->devtype->nr_gpio)
		gpiochip_हटाओ(&s->gpio);
#पूर्ण_अगर

	क्रम (i = 0; i < s->devtype->nr_uart; i++) अणु
		uart_हटाओ_one_port(&sc16is7xx_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, &sc16is7xx_lines);
		sc16is7xx_घातer(&s->p[i].port, 0);
	पूर्ण

	kthपढ़ो_flush_worker(&s->kworker);
	kthपढ़ो_stop(s->kworker_task);

	अगर (!IS_ERR(s->clk))
		clk_disable_unprepare(s->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused sc16is7xx_dt_ids[] = अणु
	अणु .compatible = "nxp,sc16is740",	.data = &sc16is74x_devtype, पूर्ण,
	अणु .compatible = "nxp,sc16is741",	.data = &sc16is74x_devtype, पूर्ण,
	अणु .compatible = "nxp,sc16is750",	.data = &sc16is750_devtype, पूर्ण,
	अणु .compatible = "nxp,sc16is752",	.data = &sc16is752_devtype, पूर्ण,
	अणु .compatible = "nxp,sc16is760",	.data = &sc16is760_devtype, पूर्ण,
	अणु .compatible = "nxp,sc16is762",	.data = &sc16is762_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sc16is7xx_dt_ids);

अटल काष्ठा regmap_config regcfg = अणु
	.reg_bits = 7,
	.pad_bits = 1,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = sc16is7xx_regmap_अस्थिर,
	.precious_reg = sc16is7xx_regmap_precious,
पूर्ण;

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_SPI
अटल पूर्णांक sc16is7xx_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा sc16is7xx_devtype *devtype;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	/* Setup SPI bus */
	spi->bits_per_word	= 8;
	/* only supports mode 0 on SC16IS762 */
	spi->mode		= spi->mode ? : SPI_MODE_0;
	spi->max_speed_hz	= spi->max_speed_hz ? : 15000000;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	अगर (spi->dev.of_node) अणु
		devtype = device_get_match_data(&spi->dev);
		अगर (!devtype)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा spi_device_id *id_entry = spi_get_device_id(spi);

		devtype = (काष्ठा sc16is7xx_devtype *)id_entry->driver_data;
	पूर्ण

	regcfg.max_रेजिस्टर = (0xf << SC16IS7XX_REG_SHIFT) |
			      (devtype->nr_uart - 1);
	regmap = devm_regmap_init_spi(spi, &regcfg);

	वापस sc16is7xx_probe(&spi->dev, devtype, regmap, spi->irq);
पूर्ण

अटल पूर्णांक sc16is7xx_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस sc16is7xx_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id sc16is7xx_spi_id_table[] = अणु
	अणु "sc16is74x",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is740",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is741",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is750",	(kernel_uदीर्घ_t)&sc16is750_devtype, पूर्ण,
	अणु "sc16is752",	(kernel_uदीर्घ_t)&sc16is752_devtype, पूर्ण,
	अणु "sc16is760",	(kernel_uदीर्घ_t)&sc16is760_devtype, पूर्ण,
	अणु "sc16is762",	(kernel_uदीर्घ_t)&sc16is762_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, sc16is7xx_spi_id_table);

अटल काष्ठा spi_driver sc16is7xx_spi_uart_driver = अणु
	.driver = अणु
		.name		= SC16IS7XX_NAME,
		.of_match_table	= sc16is7xx_dt_ids,
	पूर्ण,
	.probe		= sc16is7xx_spi_probe,
	.हटाओ		= sc16is7xx_spi_हटाओ,
	.id_table	= sc16is7xx_spi_id_table,
पूर्ण;

MODULE_ALIAS("spi:sc16is7xx");
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_I2C
अटल पूर्णांक sc16is7xx_i2c_probe(काष्ठा i2c_client *i2c,
			       स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर काष्ठा sc16is7xx_devtype *devtype;
	काष्ठा regmap *regmap;

	अगर (i2c->dev.of_node) अणु
		devtype = device_get_match_data(&i2c->dev);
		अगर (!devtype)
			वापस -ENODEV;
	पूर्ण अन्यथा अणु
		devtype = (काष्ठा sc16is7xx_devtype *)id->driver_data;
	पूर्ण

	regcfg.max_रेजिस्टर = (0xf << SC16IS7XX_REG_SHIFT) |
			      (devtype->nr_uart - 1);
	regmap = devm_regmap_init_i2c(i2c, &regcfg);

	वापस sc16is7xx_probe(&i2c->dev, devtype, regmap, i2c->irq);
पूर्ण

अटल पूर्णांक sc16is7xx_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस sc16is7xx_हटाओ(&client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sc16is7xx_i2c_id_table[] = अणु
	अणु "sc16is74x",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is740",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is741",	(kernel_uदीर्घ_t)&sc16is74x_devtype, पूर्ण,
	अणु "sc16is750",	(kernel_uदीर्घ_t)&sc16is750_devtype, पूर्ण,
	अणु "sc16is752",	(kernel_uदीर्घ_t)&sc16is752_devtype, पूर्ण,
	अणु "sc16is760",	(kernel_uदीर्घ_t)&sc16is760_devtype, पूर्ण,
	अणु "sc16is762",	(kernel_uदीर्घ_t)&sc16is762_devtype, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sc16is7xx_i2c_id_table);

अटल काष्ठा i2c_driver sc16is7xx_i2c_uart_driver = अणु
	.driver = अणु
		.name		= SC16IS7XX_NAME,
		.of_match_table	= sc16is7xx_dt_ids,
	पूर्ण,
	.probe		= sc16is7xx_i2c_probe,
	.हटाओ		= sc16is7xx_i2c_हटाओ,
	.id_table	= sc16is7xx_i2c_id_table,
पूर्ण;

#पूर्ण_अगर

अटल पूर्णांक __init sc16is7xx_init(व्योम)
अणु
	पूर्णांक ret;

	ret = uart_रेजिस्टर_driver(&sc16is7xx_uart);
	अगर (ret) अणु
		pr_err("Registering UART driver failed\n");
		वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_I2C
	ret = i2c_add_driver(&sc16is7xx_i2c_uart_driver);
	अगर (ret < 0) अणु
		pr_err("failed to init sc16is7xx i2c --> %d\n", ret);
		जाओ err_i2c;
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_SPI
	ret = spi_रेजिस्टर_driver(&sc16is7xx_spi_uart_driver);
	अगर (ret < 0) अणु
		pr_err("failed to init sc16is7xx spi --> %d\n", ret);
		जाओ err_spi;
	पूर्ण
#पूर्ण_अगर
	वापस ret;

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_SPI
err_spi:
#पूर्ण_अगर
#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_I2C
	i2c_del_driver(&sc16is7xx_i2c_uart_driver);
err_i2c:
#पूर्ण_अगर
	uart_unरेजिस्टर_driver(&sc16is7xx_uart);
	वापस ret;
पूर्ण
module_init(sc16is7xx_init);

अटल व्योम __निकास sc16is7xx_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_I2C
	i2c_del_driver(&sc16is7xx_i2c_uart_driver);
#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_SC16IS7XX_SPI
	spi_unरेजिस्टर_driver(&sc16is7xx_spi_uart_driver);
#पूर्ण_अगर
	uart_unरेजिस्टर_driver(&sc16is7xx_uart);
पूर्ण
module_निकास(sc16is7xx_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jon Ringle <jringle@gridpoint.com>");
MODULE_DESCRIPTION("SC16IS7XX serial driver");
