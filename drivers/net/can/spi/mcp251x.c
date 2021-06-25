<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* CAN bus driver क्रम Microchip 251x/25625 CAN Controller with SPI Interface
 *
 * MCP2510 support and bug fixes by Christian Pellegrin
 * <chripell@evolware.org>
 *
 * Copyright 2009 Christian Pellegrin EVOL S.r.l.
 *
 * Copyright 2007 Raymarine UK, Ltd. All Rights Reserved.
 * Written under contract by:
 *   Chris Elston, Katalix Systems, Ltd.
 *
 * Based on Microchip MCP251x CAN controller driver written by
 * David Vrabel, Copyright 2006 Arcom Control Systems Ltd.
 *
 * Based on CAN bus driver क्रम the CCAN controller written by
 * - Sascha Hauer, Marc Kleine-Budde, Pengutronix
 * - Simon Kallweit, पूर्णांकefo AG
 * Copyright 2007
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/can/core.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/led.h>
#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/uaccess.h>

/* SPI पूर्णांकerface inकाष्ठाion set */
#घोषणा INSTRUCTION_WRITE	0x02
#घोषणा INSTRUCTION_READ	0x03
#घोषणा INSTRUCTION_BIT_MODIFY	0x05
#घोषणा INSTRUCTION_LOAD_TXB(n)	(0x40 + 2 * (n))
#घोषणा INSTRUCTION_READ_RXB(n)	(((n) == 0) ? 0x90 : 0x94)
#घोषणा INSTRUCTION_RESET	0xC0
#घोषणा RTS_TXB0		0x01
#घोषणा RTS_TXB1		0x02
#घोषणा RTS_TXB2		0x04
#घोषणा INSTRUCTION_RTS(n)	(0x80 | ((n) & 0x07))

/* MPC251x रेजिस्टरs */
#घोषणा BFPCTRL			0x0c
#  define BFPCTRL_B0BFM		BIT(0)
#  define BFPCTRL_B1BFM		BIT(1)
#  define BFPCTRL_BFM(n)	(BFPCTRL_B0BFM << (n))
#  define BFPCTRL_BFM_MASK	GENMASK(1, 0)
#  define BFPCTRL_B0BFE		BIT(2)
#  define BFPCTRL_B1BFE		BIT(3)
#  define BFPCTRL_BFE(n)	(BFPCTRL_B0BFE << (n))
#  define BFPCTRL_BFE_MASK	GENMASK(3, 2)
#  define BFPCTRL_B0BFS		BIT(4)
#  define BFPCTRL_B1BFS		BIT(5)
#  define BFPCTRL_BFS(n)	(BFPCTRL_B0BFS << (n))
#  define BFPCTRL_BFS_MASK	GENMASK(5, 4)
#घोषणा TXRTSCTRL		0x0d
#  define TXRTSCTRL_B0RTSM	BIT(0)
#  define TXRTSCTRL_B1RTSM	BIT(1)
#  define TXRTSCTRL_B2RTSM	BIT(2)
#  define TXRTSCTRL_RTSM(n)	(TXRTSCTRL_B0RTSM << (n))
#  define TXRTSCTRL_RTSM_MASK	GENMASK(2, 0)
#  define TXRTSCTRL_B0RTS	BIT(3)
#  define TXRTSCTRL_B1RTS	BIT(4)
#  define TXRTSCTRL_B2RTS	BIT(5)
#  define TXRTSCTRL_RTS(n)	(TXRTSCTRL_B0RTS << (n))
#  define TXRTSCTRL_RTS_MASK	GENMASK(5, 3)
#घोषणा CANSTAT	      0x0e
#घोषणा CANCTRL	      0x0f
#  define CANCTRL_REQOP_MASK	    0xe0
#  define CANCTRL_REQOP_CONF	    0x80
#  define CANCTRL_REQOP_LISTEN_ONLY 0x60
#  define CANCTRL_REQOP_LOOPBACK    0x40
#  define CANCTRL_REQOP_SLEEP	    0x20
#  define CANCTRL_REQOP_NORMAL	    0x00
#  define CANCTRL_OSM		    0x08
#  define CANCTRL_ABAT		    0x10
#घोषणा TEC	      0x1c
#घोषणा REC	      0x1d
#घोषणा CNF1	      0x2a
#  define CNF1_SJW_SHIFT   6
#घोषणा CNF2	      0x29
#  define CNF2_BTLMODE	   0x80
#  define CNF2_SAM         0x40
#  define CNF2_PS1_SHIFT   3
#घोषणा CNF3	      0x28
#  define CNF3_SOF	   0x08
#  define CNF3_WAKFIL	   0x04
#  define CNF3_PHSEG2_MASK 0x07
#घोषणा CANINTE	      0x2b
#  define CANINTE_MERRE 0x80
#  define CANINTE_WAKIE 0x40
#  define CANINTE_ERRIE 0x20
#  define CANINTE_TX2IE 0x10
#  define CANINTE_TX1IE 0x08
#  define CANINTE_TX0IE 0x04
#  define CANINTE_RX1IE 0x02
#  define CANINTE_RX0IE 0x01
#घोषणा CANINTF	      0x2c
#  define CANINTF_MERRF 0x80
#  define CANINTF_WAKIF 0x40
#  define CANINTF_ERRIF 0x20
#  define CANINTF_TX2IF 0x10
#  define CANINTF_TX1IF 0x08
#  define CANINTF_TX0IF 0x04
#  define CANINTF_RX1IF 0x02
#  define CANINTF_RX0IF 0x01
#  define CANINTF_RX (CANINTF_RX0IF | CANINTF_RX1IF)
#  define CANINTF_TX (CANINTF_TX2IF | CANINTF_TX1IF | CANINTF_TX0IF)
#  define CANINTF_ERR (CANINTF_ERRIF)
#घोषणा EFLG	      0x2d
#  define EFLG_EWARN	0x01
#  define EFLG_RXWAR	0x02
#  define EFLG_TXWAR	0x04
#  define EFLG_RXEP	0x08
#  define EFLG_TXEP	0x10
#  define EFLG_TXBO	0x20
#  define EFLG_RX0OVR	0x40
#  define EFLG_RX1OVR	0x80
#घोषणा TXBCTRL(n)  (((n) * 0x10) + 0x30 + TXBCTRL_OFF)
#  define TXBCTRL_ABTF	0x40
#  define TXBCTRL_MLOA	0x20
#  define TXBCTRL_TXERR 0x10
#  define TXBCTRL_TXREQ 0x08
#घोषणा TXBSIDH(n)  (((n) * 0x10) + 0x30 + TXBSIDH_OFF)
#  define SIDH_SHIFT    3
#घोषणा TXBSIDL(n)  (((n) * 0x10) + 0x30 + TXBSIDL_OFF)
#  define SIDL_SID_MASK    7
#  define SIDL_SID_SHIFT   5
#  define SIDL_EXIDE_SHIFT 3
#  define SIDL_EID_SHIFT   16
#  define SIDL_EID_MASK    3
#घोषणा TXBEID8(n)  (((n) * 0x10) + 0x30 + TXBEID8_OFF)
#घोषणा TXBEID0(n)  (((n) * 0x10) + 0x30 + TXBEID0_OFF)
#घोषणा TXBDLC(n)   (((n) * 0x10) + 0x30 + TXBDLC_OFF)
#  define DLC_RTR_SHIFT    6
#घोषणा TXBCTRL_OFF 0
#घोषणा TXBSIDH_OFF 1
#घोषणा TXBSIDL_OFF 2
#घोषणा TXBEID8_OFF 3
#घोषणा TXBEID0_OFF 4
#घोषणा TXBDLC_OFF  5
#घोषणा TXBDAT_OFF  6
#घोषणा RXBCTRL(n)  (((n) * 0x10) + 0x60 + RXBCTRL_OFF)
#  define RXBCTRL_BUKT	0x04
#  define RXBCTRL_RXM0	0x20
#  define RXBCTRL_RXM1	0x40
#घोषणा RXBSIDH(n)  (((n) * 0x10) + 0x60 + RXBSIDH_OFF)
#  define RXBSIDH_SHIFT 3
#घोषणा RXBSIDL(n)  (((n) * 0x10) + 0x60 + RXBSIDL_OFF)
#  define RXBSIDL_IDE   0x08
#  define RXBSIDL_SRR   0x10
#  define RXBSIDL_EID   3
#  define RXBSIDL_SHIFT 5
#घोषणा RXBEID8(n)  (((n) * 0x10) + 0x60 + RXBEID8_OFF)
#घोषणा RXBEID0(n)  (((n) * 0x10) + 0x60 + RXBEID0_OFF)
#घोषणा RXBDLC(n)   (((n) * 0x10) + 0x60 + RXBDLC_OFF)
#  define RXBDLC_LEN_MASK  0x0f
#  define RXBDLC_RTR       0x40
#घोषणा RXBCTRL_OFF 0
#घोषणा RXBSIDH_OFF 1
#घोषणा RXBSIDL_OFF 2
#घोषणा RXBEID8_OFF 3
#घोषणा RXBEID0_OFF 4
#घोषणा RXBDLC_OFF  5
#घोषणा RXBDAT_OFF  6
#घोषणा RXFSID(n) ((n < 3) ? 0 : 4)
#घोषणा RXFSIDH(n) ((n) * 4 + RXFSID(n))
#घोषणा RXFSIDL(n) ((n) * 4 + 1 + RXFSID(n))
#घोषणा RXFEID8(n) ((n) * 4 + 2 + RXFSID(n))
#घोषणा RXFEID0(n) ((n) * 4 + 3 + RXFSID(n))
#घोषणा RXMSIDH(n) ((n) * 4 + 0x20)
#घोषणा RXMSIDL(n) ((n) * 4 + 0x21)
#घोषणा RXMEID8(n) ((n) * 4 + 0x22)
#घोषणा RXMEID0(n) ((n) * 4 + 0x23)

#घोषणा GET_BYTE(val, byte)			\
	(((val) >> ((byte) * 8)) & 0xff)
#घोषणा SET_BYTE(val, byte)			\
	(((val) & 0xff) << ((byte) * 8))

/* Buffer size required क्रम the largest SPI transfer (i.e., पढ़ोing a
 * frame)
 */
#घोषणा CAN_FRAME_MAX_DATA_LEN	8
#घोषणा SPI_TRANSFER_BUF_LEN	(6 + CAN_FRAME_MAX_DATA_LEN)
#घोषणा CAN_FRAME_MAX_BITS	128

#घोषणा TX_ECHO_SKB_MAX	1

#घोषणा MCP251X_OST_DELAY_MS	(5)

#घोषणा DEVICE_NAME "mcp251x"

अटल स्थिर काष्ठा can_bittiming_स्थिर mcp251x_bittiming_स्थिर = अणु
	.name = DEVICE_NAME,
	.tseg1_min = 3,
	.tseg1_max = 16,
	.tseg2_min = 2,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 64,
	.brp_inc = 1,
पूर्ण;

क्रमागत mcp251x_model अणु
	CAN_MCP251X_MCP2510	= 0x2510,
	CAN_MCP251X_MCP2515	= 0x2515,
	CAN_MCP251X_MCP25625	= 0x25625,
पूर्ण;

काष्ठा mcp251x_priv अणु
	काष्ठा can_priv	   can;
	काष्ठा net_device *net;
	काष्ठा spi_device *spi;
	क्रमागत mcp251x_model model;

	काष्ठा mutex mcp_lock; /* SPI device lock */

	u8 *spi_tx_buf;
	u8 *spi_rx_buf;

	काष्ठा sk_buff *tx_skb;
	पूर्णांक tx_len;

	काष्ठा workqueue_काष्ठा *wq;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा work_काष्ठा restart_work;

	पूर्णांक क्रमce_quit;
	पूर्णांक after_suspend;
#घोषणा AFTER_SUSPEND_UP 1
#घोषणा AFTER_SUSPEND_DOWN 2
#घोषणा AFTER_SUSPEND_POWER 4
#घोषणा AFTER_SUSPEND_RESTART 8
	पूर्णांक restart_tx;
	काष्ठा regulator *घातer;
	काष्ठा regulator *transceiver;
	काष्ठा clk *clk;
#अगर_घोषित CONFIG_GPIOLIB
	काष्ठा gpio_chip gpio;
	u8 reg_bfpctrl;
#पूर्ण_अगर
पूर्ण;

#घोषणा MCP251X_IS(_model) \
अटल अंतरभूत पूर्णांक mcp251x_is_##_model(काष्ठा spi_device *spi) \
अणु \
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi); \
	वापस priv->model == CAN_MCP251X_MCP##_model; \
पूर्ण

MCP251X_IS(2510);

अटल व्योम mcp251x_clean(काष्ठा net_device *net)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);

	अगर (priv->tx_skb || priv->tx_len)
		net->stats.tx_errors++;
	dev_kमुक्त_skb(priv->tx_skb);
	अगर (priv->tx_len)
		can_मुक्त_echo_skb(priv->net, 0, शून्य);
	priv->tx_skb = शून्य;
	priv->tx_len = 0;
पूर्ण

/* Note about handling of error वापस of mcp251x_spi_trans: accessing
 * रेजिस्टरs via SPI is not really dअगरferent conceptually than using
 * normal I/O assembler inकाष्ठाions, although it's much more
 * complicated from a practical POV. So it's not advisable to always
 * check the वापस value of this function. Imagine that every
 * पढ़ोअणुb,lपूर्ण, ग_लिखोअणुb,lपूर्ण and मित्रs would be bracketed in "अगर ( < 0)
 * error();", it would be a great mess (well there are some situation
 * when exception handling C++ like could be useful after all). So we
 * just check that transfers are OK at the beginning of our
 * conversation with the chip and to aव्योम करोing really nasty things
 * (like injecting bogus packets in the network stack).
 */
अटल पूर्णांक mcp251x_spi_trans(काष्ठा spi_device *spi, पूर्णांक len)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	काष्ठा spi_transfer t = अणु
		.tx_buf = priv->spi_tx_buf,
		.rx_buf = priv->spi_rx_buf,
		.len = len,
		.cs_change = 0,
	पूर्ण;
	काष्ठा spi_message m;
	पूर्णांक ret;

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);

	ret = spi_sync(spi, &m);
	अगर (ret)
		dev_err(&spi->dev, "spi transfer failed: ret = %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mcp251x_spi_ग_लिखो(काष्ठा spi_device *spi, पूर्णांक len)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	पूर्णांक ret;

	ret = spi_ग_लिखो(spi, priv->spi_tx_buf, len);
	अगर (ret)
		dev_err(&spi->dev, "spi write failed: ret = %d\n", ret);

	वापस ret;
पूर्ण

अटल u8 mcp251x_पढ़ो_reg(काष्ठा spi_device *spi, u8 reg)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	u8 val = 0;

	priv->spi_tx_buf[0] = INSTRUCTION_READ;
	priv->spi_tx_buf[1] = reg;

	अगर (spi->controller->flags & SPI_CONTROLLER_HALF_DUPLEX) अणु
		spi_ग_लिखो_then_पढ़ो(spi, priv->spi_tx_buf, 2, &val, 1);
	पूर्ण अन्यथा अणु
		mcp251x_spi_trans(spi, 3);
		val = priv->spi_rx_buf[2];
	पूर्ण

	वापस val;
पूर्ण

अटल व्योम mcp251x_पढ़ो_2regs(काष्ठा spi_device *spi, u8 reg, u8 *v1, u8 *v2)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = INSTRUCTION_READ;
	priv->spi_tx_buf[1] = reg;

	अगर (spi->controller->flags & SPI_CONTROLLER_HALF_DUPLEX) अणु
		u8 val[2] = अणु 0 पूर्ण;

		spi_ग_लिखो_then_पढ़ो(spi, priv->spi_tx_buf, 2, val, 2);
		*v1 = val[0];
		*v2 = val[1];
	पूर्ण अन्यथा अणु
		mcp251x_spi_trans(spi, 4);

		*v1 = priv->spi_rx_buf[2];
		*v2 = priv->spi_rx_buf[3];
	पूर्ण
पूर्ण

अटल व्योम mcp251x_ग_लिखो_reg(काष्ठा spi_device *spi, u8 reg, u8 val)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = INSTRUCTION_WRITE;
	priv->spi_tx_buf[1] = reg;
	priv->spi_tx_buf[2] = val;

	mcp251x_spi_ग_लिखो(spi, 3);
पूर्ण

अटल व्योम mcp251x_ग_लिखो_2regs(काष्ठा spi_device *spi, u8 reg, u8 v1, u8 v2)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = INSTRUCTION_WRITE;
	priv->spi_tx_buf[1] = reg;
	priv->spi_tx_buf[2] = v1;
	priv->spi_tx_buf[3] = v2;

	mcp251x_spi_ग_लिखो(spi, 4);
पूर्ण

अटल व्योम mcp251x_ग_लिखो_bits(काष्ठा spi_device *spi, u8 reg,
			       u8 mask, u8 val)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = INSTRUCTION_BIT_MODIFY;
	priv->spi_tx_buf[1] = reg;
	priv->spi_tx_buf[2] = mask;
	priv->spi_tx_buf[3] = val;

	mcp251x_spi_ग_लिखो(spi, 4);
पूर्ण

अटल u8 mcp251x_पढ़ो_stat(काष्ठा spi_device *spi)
अणु
	वापस mcp251x_पढ़ो_reg(spi, CANSTAT) & CANCTRL_REQOP_MASK;
पूर्ण

#घोषणा mcp251x_पढ़ो_stat_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(mcp251x_पढ़ो_stat, addr, val, cond, \
			   delay_us, समयout_us)

#अगर_घोषित CONFIG_GPIOLIB
क्रमागत अणु
	MCP251X_GPIO_TX0RTS = 0,		/* inमाला_दो */
	MCP251X_GPIO_TX1RTS,
	MCP251X_GPIO_TX2RTS,
	MCP251X_GPIO_RX0BF,			/* outमाला_दो */
	MCP251X_GPIO_RX1BF,
पूर्ण;

#घोषणा MCP251X_GPIO_INPUT_MASK \
	GENMASK(MCP251X_GPIO_TX2RTS, MCP251X_GPIO_TX0RTS)
#घोषणा MCP251X_GPIO_OUTPUT_MASK \
	GENMASK(MCP251X_GPIO_RX1BF, MCP251X_GPIO_RX0BF)

अटल स्थिर अक्षर * स्थिर mcp251x_gpio_names[] = अणु
	[MCP251X_GPIO_TX0RTS] = "TX0RTS",	/* inमाला_दो */
	[MCP251X_GPIO_TX1RTS] = "TX1RTS",
	[MCP251X_GPIO_TX2RTS] = "TX2RTS",
	[MCP251X_GPIO_RX0BF] = "RX0BF",		/* outमाला_दो */
	[MCP251X_GPIO_RX1BF] = "RX1BF",
पूर्ण;

अटल अंतरभूत bool mcp251x_gpio_is_input(अचिन्हित पूर्णांक offset)
अणु
	वापस offset <= MCP251X_GPIO_TX2RTS;
पूर्ण

अटल पूर्णांक mcp251x_gpio_request(काष्ठा gpio_chip *chip,
				अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	u8 val;

	/* nothing to be करोne क्रम inमाला_दो */
	अगर (mcp251x_gpio_is_input(offset))
		वापस 0;

	val = BFPCTRL_BFE(offset - MCP251X_GPIO_RX0BF);

	mutex_lock(&priv->mcp_lock);
	mcp251x_ग_लिखो_bits(priv->spi, BFPCTRL, val, val);
	mutex_unlock(&priv->mcp_lock);

	priv->reg_bfpctrl |= val;

	वापस 0;
पूर्ण

अटल व्योम mcp251x_gpio_मुक्त(काष्ठा gpio_chip *chip,
			      अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	u8 val;

	/* nothing to be करोne क्रम inमाला_दो */
	अगर (mcp251x_gpio_is_input(offset))
		वापस;

	val = BFPCTRL_BFE(offset - MCP251X_GPIO_RX0BF);

	mutex_lock(&priv->mcp_lock);
	mcp251x_ग_लिखो_bits(priv->spi, BFPCTRL, val, 0);
	mutex_unlock(&priv->mcp_lock);

	priv->reg_bfpctrl &= ~val;
पूर्ण

अटल पूर्णांक mcp251x_gpio_get_direction(काष्ठा gpio_chip *chip,
				      अचिन्हित पूर्णांक offset)
अणु
	अगर (mcp251x_gpio_is_input(offset))
		वापस GPIOF_सूची_IN;

	वापस GPIOF_सूची_OUT;
पूर्ण

अटल पूर्णांक mcp251x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	u8 reg, mask, val;

	अगर (mcp251x_gpio_is_input(offset)) अणु
		reg = TXRTSCTRL;
		mask = TXRTSCTRL_RTS(offset);
	पूर्ण अन्यथा अणु
		reg = BFPCTRL;
		mask = BFPCTRL_BFS(offset - MCP251X_GPIO_RX0BF);
	पूर्ण

	mutex_lock(&priv->mcp_lock);
	val = mcp251x_पढ़ो_reg(priv->spi, reg);
	mutex_unlock(&priv->mcp_lock);

	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक mcp251x_gpio_get_multiple(काष्ठा gpio_chip *chip,
				     अचिन्हित दीर्घ *maskp, अचिन्हित दीर्घ *bitsp)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	अचिन्हित दीर्घ bits = 0;
	u8 val;

	mutex_lock(&priv->mcp_lock);
	अगर (maskp[0] & MCP251X_GPIO_INPUT_MASK) अणु
		val = mcp251x_पढ़ो_reg(priv->spi, TXRTSCTRL);
		val = FIELD_GET(TXRTSCTRL_RTS_MASK, val);
		bits |= FIELD_PREP(MCP251X_GPIO_INPUT_MASK, val);
	पूर्ण
	अगर (maskp[0] & MCP251X_GPIO_OUTPUT_MASK) अणु
		val = mcp251x_पढ़ो_reg(priv->spi, BFPCTRL);
		val = FIELD_GET(BFPCTRL_BFS_MASK, val);
		bits |= FIELD_PREP(MCP251X_GPIO_OUTPUT_MASK, val);
	पूर्ण
	mutex_unlock(&priv->mcp_lock);

	bitsp[0] = bits;
	वापस 0;
पूर्ण

अटल व्योम mcp251x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     पूर्णांक value)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	u8 mask, val;

	mask = BFPCTRL_BFS(offset - MCP251X_GPIO_RX0BF);
	val = value ? mask : 0;

	mutex_lock(&priv->mcp_lock);
	mcp251x_ग_लिखो_bits(priv->spi, BFPCTRL, mask, val);
	mutex_unlock(&priv->mcp_lock);

	priv->reg_bfpctrl &= ~mask;
	priv->reg_bfpctrl |= val;
पूर्ण

अटल व्योम
mcp251x_gpio_set_multiple(काष्ठा gpio_chip *chip,
			  अचिन्हित दीर्घ *maskp, अचिन्हित दीर्घ *bitsp)
अणु
	काष्ठा mcp251x_priv *priv = gpiochip_get_data(chip);
	u8 mask, val;

	mask = FIELD_GET(MCP251X_GPIO_OUTPUT_MASK, maskp[0]);
	mask = FIELD_PREP(BFPCTRL_BFS_MASK, mask);

	val = FIELD_GET(MCP251X_GPIO_OUTPUT_MASK, bitsp[0]);
	val = FIELD_PREP(BFPCTRL_BFS_MASK, val);

	अगर (!mask)
		वापस;

	mutex_lock(&priv->mcp_lock);
	mcp251x_ग_लिखो_bits(priv->spi, BFPCTRL, mask, val);
	mutex_unlock(&priv->mcp_lock);

	priv->reg_bfpctrl &= ~mask;
	priv->reg_bfpctrl |= val;
पूर्ण

अटल व्योम mcp251x_gpio_restore(काष्ठा spi_device *spi)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	mcp251x_ग_लिखो_reg(spi, BFPCTRL, priv->reg_bfpctrl);
पूर्ण

अटल पूर्णांक mcp251x_gpio_setup(काष्ठा mcp251x_priv *priv)
अणु
	काष्ठा gpio_chip *gpio = &priv->gpio;

	अगर (!device_property_present(&priv->spi->dev, "gpio-controller"))
		वापस 0;

	/* gpiochip handles TX[0..2]RTS and RX[0..1]BF */
	gpio->label = priv->spi->modalias;
	gpio->parent = &priv->spi->dev;
	gpio->owner = THIS_MODULE;
	gpio->request = mcp251x_gpio_request;
	gpio->मुक्त = mcp251x_gpio_मुक्त;
	gpio->get_direction = mcp251x_gpio_get_direction;
	gpio->get = mcp251x_gpio_get;
	gpio->get_multiple = mcp251x_gpio_get_multiple;
	gpio->set = mcp251x_gpio_set;
	gpio->set_multiple = mcp251x_gpio_set_multiple;
	gpio->base = -1;
	gpio->ngpio = ARRAY_SIZE(mcp251x_gpio_names);
	gpio->names = mcp251x_gpio_names;
	gpio->can_sleep = true;
#अगर_घोषित CONFIG_OF_GPIO
	gpio->of_node = priv->spi->dev.of_node;
#पूर्ण_अगर

	वापस devm_gpiochip_add_data(&priv->spi->dev, gpio, priv);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम mcp251x_gpio_restore(काष्ठा spi_device *spi)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक mcp251x_gpio_setup(काष्ठा mcp251x_priv *priv)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम mcp251x_hw_tx_frame(काष्ठा spi_device *spi, u8 *buf,
				पूर्णांक len, पूर्णांक tx_buf_idx)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	अगर (mcp251x_is_2510(spi)) अणु
		पूर्णांक i;

		क्रम (i = 1; i < TXBDAT_OFF + len; i++)
			mcp251x_ग_लिखो_reg(spi, TXBCTRL(tx_buf_idx) + i,
					  buf[i]);
	पूर्ण अन्यथा अणु
		स_नकल(priv->spi_tx_buf, buf, TXBDAT_OFF + len);
		mcp251x_spi_ग_लिखो(spi, TXBDAT_OFF + len);
	पूर्ण
पूर्ण

अटल व्योम mcp251x_hw_tx(काष्ठा spi_device *spi, काष्ठा can_frame *frame,
			  पूर्णांक tx_buf_idx)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	u32 sid, eid, exide, rtr;
	u8 buf[SPI_TRANSFER_BUF_LEN];

	exide = (frame->can_id & CAN_EFF_FLAG) ? 1 : 0; /* Extended ID Enable */
	अगर (exide)
		sid = (frame->can_id & CAN_EFF_MASK) >> 18;
	अन्यथा
		sid = frame->can_id & CAN_SFF_MASK; /* Standard ID */
	eid = frame->can_id & CAN_EFF_MASK; /* Extended ID */
	rtr = (frame->can_id & CAN_RTR_FLAG) ? 1 : 0; /* Remote transmission */

	buf[TXBCTRL_OFF] = INSTRUCTION_LOAD_TXB(tx_buf_idx);
	buf[TXBSIDH_OFF] = sid >> SIDH_SHIFT;
	buf[TXBSIDL_OFF] = ((sid & SIDL_SID_MASK) << SIDL_SID_SHIFT) |
		(exide << SIDL_EXIDE_SHIFT) |
		((eid >> SIDL_EID_SHIFT) & SIDL_EID_MASK);
	buf[TXBEID8_OFF] = GET_BYTE(eid, 1);
	buf[TXBEID0_OFF] = GET_BYTE(eid, 0);
	buf[TXBDLC_OFF] = (rtr << DLC_RTR_SHIFT) | frame->len;
	स_नकल(buf + TXBDAT_OFF, frame->data, frame->len);
	mcp251x_hw_tx_frame(spi, buf, frame->len, tx_buf_idx);

	/* use INSTRUCTION_RTS, to aव्योम "repeated frame problem" */
	priv->spi_tx_buf[0] = INSTRUCTION_RTS(1 << tx_buf_idx);
	mcp251x_spi_ग_लिखो(priv->spi, 1);
पूर्ण

अटल व्योम mcp251x_hw_rx_frame(काष्ठा spi_device *spi, u8 *buf,
				पूर्णांक buf_idx)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	अगर (mcp251x_is_2510(spi)) अणु
		पूर्णांक i, len;

		क्रम (i = 1; i < RXBDAT_OFF; i++)
			buf[i] = mcp251x_पढ़ो_reg(spi, RXBCTRL(buf_idx) + i);

		len = can_cc_dlc2len(buf[RXBDLC_OFF] & RXBDLC_LEN_MASK);
		क्रम (; i < (RXBDAT_OFF + len); i++)
			buf[i] = mcp251x_पढ़ो_reg(spi, RXBCTRL(buf_idx) + i);
	पूर्ण अन्यथा अणु
		priv->spi_tx_buf[RXBCTRL_OFF] = INSTRUCTION_READ_RXB(buf_idx);
		अगर (spi->controller->flags & SPI_CONTROLLER_HALF_DUPLEX) अणु
			spi_ग_लिखो_then_पढ़ो(spi, priv->spi_tx_buf, 1,
					    priv->spi_rx_buf,
					    SPI_TRANSFER_BUF_LEN);
			स_नकल(buf + 1, priv->spi_rx_buf,
			       SPI_TRANSFER_BUF_LEN - 1);
		पूर्ण अन्यथा अणु
			mcp251x_spi_trans(spi, SPI_TRANSFER_BUF_LEN);
			स_नकल(buf, priv->spi_rx_buf, SPI_TRANSFER_BUF_LEN);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mcp251x_hw_rx(काष्ठा spi_device *spi, पूर्णांक buf_idx)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;
	u8 buf[SPI_TRANSFER_BUF_LEN];

	skb = alloc_can_skb(priv->net, &frame);
	अगर (!skb) अणु
		dev_err(&spi->dev, "cannot allocate RX skb\n");
		priv->net->stats.rx_dropped++;
		वापस;
	पूर्ण

	mcp251x_hw_rx_frame(spi, buf, buf_idx);
	अगर (buf[RXBSIDL_OFF] & RXBSIDL_IDE) अणु
		/* Extended ID क्रमmat */
		frame->can_id = CAN_EFF_FLAG;
		frame->can_id |=
			/* Extended ID part */
			SET_BYTE(buf[RXBSIDL_OFF] & RXBSIDL_EID, 2) |
			SET_BYTE(buf[RXBEID8_OFF], 1) |
			SET_BYTE(buf[RXBEID0_OFF], 0) |
			/* Standard ID part */
			(((buf[RXBSIDH_OFF] << RXBSIDH_SHIFT) |
			  (buf[RXBSIDL_OFF] >> RXBSIDL_SHIFT)) << 18);
		/* Remote transmission request */
		अगर (buf[RXBDLC_OFF] & RXBDLC_RTR)
			frame->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		/* Standard ID क्रमmat */
		frame->can_id =
			(buf[RXBSIDH_OFF] << RXBSIDH_SHIFT) |
			(buf[RXBSIDL_OFF] >> RXBSIDL_SHIFT);
		अगर (buf[RXBSIDL_OFF] & RXBSIDL_SRR)
			frame->can_id |= CAN_RTR_FLAG;
	पूर्ण
	/* Data length */
	frame->len = can_cc_dlc2len(buf[RXBDLC_OFF] & RXBDLC_LEN_MASK);
	स_नकल(frame->data, buf + RXBDAT_OFF, frame->len);

	priv->net->stats.rx_packets++;
	priv->net->stats.rx_bytes += frame->len;

	can_led_event(priv->net, CAN_LED_EVENT_RX);

	netअगर_rx_ni(skb);
पूर्ण

अटल व्योम mcp251x_hw_sleep(काष्ठा spi_device *spi)
अणु
	mcp251x_ग_लिखो_reg(spi, CANCTRL, CANCTRL_REQOP_SLEEP);
पूर्ण

/* May only be called when device is sleeping! */
अटल पूर्णांक mcp251x_hw_wake(काष्ठा spi_device *spi)
अणु
	u8 value;
	पूर्णांक ret;

	/* Force wakeup पूर्णांकerrupt to wake device, but करोn't execute IST */
	disable_irq(spi->irq);
	mcp251x_ग_लिखो_2regs(spi, CANINTE, CANINTE_WAKIE, CANINTF_WAKIF);

	/* Wait क्रम oscillator startup समयr after wake up */
	mdelay(MCP251X_OST_DELAY_MS);

	/* Put device पूर्णांकo config mode */
	mcp251x_ग_लिखो_reg(spi, CANCTRL, CANCTRL_REQOP_CONF);

	/* Wait क्रम the device to enter config mode */
	ret = mcp251x_पढ़ो_stat_poll_समयout(spi, value, value == CANCTRL_REQOP_CONF,
					     MCP251X_OST_DELAY_MS * 1000,
					     USEC_PER_SEC);
	अगर (ret) अणु
		dev_err(&spi->dev, "MCP251x didn't enter in config mode\n");
		वापस ret;
	पूर्ण

	/* Disable and clear pending पूर्णांकerrupts */
	mcp251x_ग_लिखो_2regs(spi, CANINTE, 0x00, 0x00);
	enable_irq(spi->irq);

	वापस 0;
पूर्ण

अटल netdev_tx_t mcp251x_hard_start_xmit(काष्ठा sk_buff *skb,
					   काष्ठा net_device *net)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;

	अगर (priv->tx_skb || priv->tx_len) अणु
		dev_warn(&spi->dev, "hard_xmit called while tx busy\n");
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (can_dropped_invalid_skb(net, skb))
		वापस NETDEV_TX_OK;

	netअगर_stop_queue(net);
	priv->tx_skb = skb;
	queue_work(priv->wq, &priv->tx_work);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक mcp251x_करो_set_mode(काष्ठा net_device *net, क्रमागत can_mode mode)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);

	चयन (mode) अणु
	हाल CAN_MODE_START:
		mcp251x_clean(net);
		/* We have to delay work since SPI I/O may sleep */
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		priv->restart_tx = 1;
		अगर (priv->can.restart_ms == 0)
			priv->after_suspend = AFTER_SUSPEND_RESTART;
		queue_work(priv->wq, &priv->restart_work);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251x_set_normal_mode(काष्ठा spi_device *spi)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	u8 value;
	पूर्णांक ret;

	/* Enable पूर्णांकerrupts */
	mcp251x_ग_लिखो_reg(spi, CANINTE,
			  CANINTE_ERRIE | CANINTE_TX2IE | CANINTE_TX1IE |
			  CANINTE_TX0IE | CANINTE_RX1IE | CANINTE_RX0IE);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) अणु
		/* Put device पूर्णांकo loopback mode */
		mcp251x_ग_लिखो_reg(spi, CANCTRL, CANCTRL_REQOP_LOOPBACK);
	पूर्ण अन्यथा अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) अणु
		/* Put device पूर्णांकo listen-only mode */
		mcp251x_ग_लिखो_reg(spi, CANCTRL, CANCTRL_REQOP_LISTEN_ONLY);
	पूर्ण अन्यथा अणु
		/* Put device पूर्णांकo normal mode */
		mcp251x_ग_लिखो_reg(spi, CANCTRL, CANCTRL_REQOP_NORMAL);

		/* Wait क्रम the device to enter normal mode */
		ret = mcp251x_पढ़ो_stat_poll_समयout(spi, value, value == 0,
						     MCP251X_OST_DELAY_MS * 1000,
						     USEC_PER_SEC);
		अगर (ret) अणु
			dev_err(&spi->dev, "MCP251x didn't enter in normal mode\n");
			वापस ret;
		पूर्ण
	पूर्ण
	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	वापस 0;
पूर्ण

अटल पूर्णांक mcp251x_करो_set_bittiming(काष्ठा net_device *net)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा spi_device *spi = priv->spi;

	mcp251x_ग_लिखो_reg(spi, CNF1, ((bt->sjw - 1) << CNF1_SJW_SHIFT) |
			  (bt->brp - 1));
	mcp251x_ग_लिखो_reg(spi, CNF2, CNF2_BTLMODE |
			  (priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES ?
			   CNF2_SAM : 0) |
			  ((bt->phase_seg1 - 1) << CNF2_PS1_SHIFT) |
			  (bt->prop_seg - 1));
	mcp251x_ग_लिखो_bits(spi, CNF3, CNF3_PHSEG2_MASK,
			   (bt->phase_seg2 - 1));
	dev_dbg(&spi->dev, "CNF: 0x%02x 0x%02x 0x%02x\n",
		mcp251x_पढ़ो_reg(spi, CNF1),
		mcp251x_पढ़ो_reg(spi, CNF2),
		mcp251x_पढ़ो_reg(spi, CNF3));

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251x_setup(काष्ठा net_device *net, काष्ठा spi_device *spi)
अणु
	mcp251x_करो_set_bittiming(net);

	mcp251x_ग_लिखो_reg(spi, RXBCTRL(0),
			  RXBCTRL_BUKT | RXBCTRL_RXM0 | RXBCTRL_RXM1);
	mcp251x_ग_लिखो_reg(spi, RXBCTRL(1),
			  RXBCTRL_RXM0 | RXBCTRL_RXM1);
	वापस 0;
पूर्ण

अटल पूर्णांक mcp251x_hw_reset(काष्ठा spi_device *spi)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	u8 value;
	पूर्णांक ret;

	/* Wait क्रम oscillator startup समयr after घातer up */
	mdelay(MCP251X_OST_DELAY_MS);

	priv->spi_tx_buf[0] = INSTRUCTION_RESET;
	ret = mcp251x_spi_ग_लिखो(spi, 1);
	अगर (ret)
		वापस ret;

	/* Wait क्रम oscillator startup समयr after reset */
	mdelay(MCP251X_OST_DELAY_MS);

	/* Wait क्रम reset to finish */
	ret = mcp251x_पढ़ो_stat_poll_समयout(spi, value, value == CANCTRL_REQOP_CONF,
					     MCP251X_OST_DELAY_MS * 1000,
					     USEC_PER_SEC);
	अगर (ret)
		dev_err(&spi->dev, "MCP251x didn't enter in conf mode after reset\n");
	वापस ret;
पूर्ण

अटल पूर्णांक mcp251x_hw_probe(काष्ठा spi_device *spi)
अणु
	u8 ctrl;
	पूर्णांक ret;

	ret = mcp251x_hw_reset(spi);
	अगर (ret)
		वापस ret;

	ctrl = mcp251x_पढ़ो_reg(spi, CANCTRL);

	dev_dbg(&spi->dev, "CANCTRL 0x%02x\n", ctrl);

	/* Check क्रम घातer up शेष value */
	अगर ((ctrl & 0x17) != 0x07)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक mcp251x_घातer_enable(काष्ठा regulator *reg, पूर्णांक enable)
अणु
	अगर (IS_ERR_OR_शून्य(reg))
		वापस 0;

	अगर (enable)
		वापस regulator_enable(reg);
	अन्यथा
		वापस regulator_disable(reg);
पूर्ण

अटल पूर्णांक mcp251x_stop(काष्ठा net_device *net)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;

	बंद_candev(net);

	priv->क्रमce_quit = 1;
	मुक्त_irq(spi->irq, priv);

	mutex_lock(&priv->mcp_lock);

	/* Disable and clear pending पूर्णांकerrupts */
	mcp251x_ग_लिखो_2regs(spi, CANINTE, 0x00, 0x00);

	mcp251x_ग_लिखो_reg(spi, TXBCTRL(0), 0);
	mcp251x_clean(net);

	mcp251x_hw_sleep(spi);

	mcp251x_घातer_enable(priv->transceiver, 0);

	priv->can.state = CAN_STATE_STOPPED;

	mutex_unlock(&priv->mcp_lock);

	can_led_event(net, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल व्योम mcp251x_error_skb(काष्ठा net_device *net, पूर्णांक can_id, पूर्णांक data1)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;

	skb = alloc_can_err_skb(net, &frame);
	अगर (skb) अणु
		frame->can_id |= can_id;
		frame->data[1] = data1;
		netअगर_rx_ni(skb);
	पूर्ण अन्यथा अणु
		netdev_err(net, "cannot allocate error skb\n");
	पूर्ण
पूर्ण

अटल व्योम mcp251x_tx_work_handler(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mcp251x_priv *priv = container_of(ws, काष्ठा mcp251x_priv,
						 tx_work);
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;
	काष्ठा can_frame *frame;

	mutex_lock(&priv->mcp_lock);
	अगर (priv->tx_skb) अणु
		अगर (priv->can.state == CAN_STATE_BUS_OFF) अणु
			mcp251x_clean(net);
		पूर्ण अन्यथा अणु
			frame = (काष्ठा can_frame *)priv->tx_skb->data;

			अगर (frame->len > CAN_FRAME_MAX_DATA_LEN)
				frame->len = CAN_FRAME_MAX_DATA_LEN;
			mcp251x_hw_tx(spi, frame, 0);
			priv->tx_len = 1 + frame->len;
			can_put_echo_skb(priv->tx_skb, net, 0, 0);
			priv->tx_skb = शून्य;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->mcp_lock);
पूर्ण

अटल व्योम mcp251x_restart_work_handler(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा mcp251x_priv *priv = container_of(ws, काष्ठा mcp251x_priv,
						 restart_work);
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;

	mutex_lock(&priv->mcp_lock);
	अगर (priv->after_suspend) अणु
		अगर (priv->after_suspend & AFTER_SUSPEND_POWER) अणु
			mcp251x_hw_reset(spi);
			mcp251x_setup(net, spi);
			mcp251x_gpio_restore(spi);
		पूर्ण अन्यथा अणु
			mcp251x_hw_wake(spi);
		पूर्ण
		priv->क्रमce_quit = 0;
		अगर (priv->after_suspend & AFTER_SUSPEND_RESTART) अणु
			mcp251x_set_normal_mode(spi);
		पूर्ण अन्यथा अगर (priv->after_suspend & AFTER_SUSPEND_UP) अणु
			netअगर_device_attach(net);
			mcp251x_clean(net);
			mcp251x_set_normal_mode(spi);
			netअगर_wake_queue(net);
		पूर्ण अन्यथा अणु
			mcp251x_hw_sleep(spi);
		पूर्ण
		priv->after_suspend = 0;
	पूर्ण

	अगर (priv->restart_tx) अणु
		priv->restart_tx = 0;
		mcp251x_ग_लिखो_reg(spi, TXBCTRL(0), 0);
		mcp251x_clean(net);
		netअगर_wake_queue(net);
		mcp251x_error_skb(net, CAN_ERR_RESTARTED, 0);
	पूर्ण
	mutex_unlock(&priv->mcp_lock);
पूर्ण

अटल irqवापस_t mcp251x_can_ist(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mcp251x_priv *priv = dev_id;
	काष्ठा spi_device *spi = priv->spi;
	काष्ठा net_device *net = priv->net;

	mutex_lock(&priv->mcp_lock);
	जबतक (!priv->क्रमce_quit) अणु
		क्रमागत can_state new_state;
		u8 पूर्णांकf, eflag;
		u8 clear_पूर्णांकf = 0;
		पूर्णांक can_id = 0, data1 = 0;

		mcp251x_पढ़ो_2regs(spi, CANINTF, &पूर्णांकf, &eflag);

		/* mask out flags we करोn't care about */
		पूर्णांकf &= CANINTF_RX | CANINTF_TX | CANINTF_ERR;

		/* receive buffer 0 */
		अगर (पूर्णांकf & CANINTF_RX0IF) अणु
			mcp251x_hw_rx(spi, 0);
			/* Free one buffer ASAP
			 * (The MCP2515/25625 करोes this स्वतःmatically.)
			 */
			अगर (mcp251x_is_2510(spi))
				mcp251x_ग_लिखो_bits(spi, CANINTF,
						   CANINTF_RX0IF, 0x00);
		पूर्ण

		/* receive buffer 1 */
		अगर (पूर्णांकf & CANINTF_RX1IF) अणु
			mcp251x_hw_rx(spi, 1);
			/* The MCP2515/25625 करोes this स्वतःmatically. */
			अगर (mcp251x_is_2510(spi))
				clear_पूर्णांकf |= CANINTF_RX1IF;
		पूर्ण

		/* any error or tx पूर्णांकerrupt we need to clear? */
		अगर (पूर्णांकf & (CANINTF_ERR | CANINTF_TX))
			clear_पूर्णांकf |= पूर्णांकf & (CANINTF_ERR | CANINTF_TX);
		अगर (clear_पूर्णांकf)
			mcp251x_ग_लिखो_bits(spi, CANINTF, clear_पूर्णांकf, 0x00);

		अगर (eflag & (EFLG_RX0OVR | EFLG_RX1OVR))
			mcp251x_ग_लिखो_bits(spi, EFLG, eflag, 0x00);

		/* Update can state */
		अगर (eflag & EFLG_TXBO) अणु
			new_state = CAN_STATE_BUS_OFF;
			can_id |= CAN_ERR_BUSOFF;
		पूर्ण अन्यथा अगर (eflag & EFLG_TXEP) अणु
			new_state = CAN_STATE_ERROR_PASSIVE;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_TX_PASSIVE;
		पूर्ण अन्यथा अगर (eflag & EFLG_RXEP) अणु
			new_state = CAN_STATE_ERROR_PASSIVE;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_RX_PASSIVE;
		पूर्ण अन्यथा अगर (eflag & EFLG_TXWAR) अणु
			new_state = CAN_STATE_ERROR_WARNING;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_TX_WARNING;
		पूर्ण अन्यथा अगर (eflag & EFLG_RXWAR) अणु
			new_state = CAN_STATE_ERROR_WARNING;
			can_id |= CAN_ERR_CRTL;
			data1 |= CAN_ERR_CRTL_RX_WARNING;
		पूर्ण अन्यथा अणु
			new_state = CAN_STATE_ERROR_ACTIVE;
		पूर्ण

		/* Update can state statistics */
		चयन (priv->can.state) अणु
		हाल CAN_STATE_ERROR_ACTIVE:
			अगर (new_state >= CAN_STATE_ERROR_WARNING &&
			    new_state <= CAN_STATE_BUS_OFF)
				priv->can.can_stats.error_warning++;
			fallthrough;
		हाल CAN_STATE_ERROR_WARNING:
			अगर (new_state >= CAN_STATE_ERROR_PASSIVE &&
			    new_state <= CAN_STATE_BUS_OFF)
				priv->can.can_stats.error_passive++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		priv->can.state = new_state;

		अगर (पूर्णांकf & CANINTF_ERRIF) अणु
			/* Handle overflow counters */
			अगर (eflag & (EFLG_RX0OVR | EFLG_RX1OVR)) अणु
				अगर (eflag & EFLG_RX0OVR) अणु
					net->stats.rx_over_errors++;
					net->stats.rx_errors++;
				पूर्ण
				अगर (eflag & EFLG_RX1OVR) अणु
					net->stats.rx_over_errors++;
					net->stats.rx_errors++;
				पूर्ण
				can_id |= CAN_ERR_CRTL;
				data1 |= CAN_ERR_CRTL_RX_OVERFLOW;
			पूर्ण
			mcp251x_error_skb(net, can_id, data1);
		पूर्ण

		अगर (priv->can.state == CAN_STATE_BUS_OFF) अणु
			अगर (priv->can.restart_ms == 0) अणु
				priv->क्रमce_quit = 1;
				priv->can.can_stats.bus_off++;
				can_bus_off(net);
				mcp251x_hw_sleep(spi);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (पूर्णांकf == 0)
			अवरोध;

		अगर (पूर्णांकf & CANINTF_TX) अणु
			net->stats.tx_packets++;
			net->stats.tx_bytes += priv->tx_len - 1;
			can_led_event(net, CAN_LED_EVENT_TX);
			अगर (priv->tx_len) अणु
				can_get_echo_skb(net, 0, शून्य);
				priv->tx_len = 0;
			पूर्ण
			netअगर_wake_queue(net);
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->mcp_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mcp251x_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा mcp251x_priv *priv = netdev_priv(net);
	काष्ठा spi_device *spi = priv->spi;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक ret;

	ret = खोलो_candev(net);
	अगर (ret) अणु
		dev_err(&spi->dev, "unable to set initial baudrate!\n");
		वापस ret;
	पूर्ण

	mutex_lock(&priv->mcp_lock);
	mcp251x_घातer_enable(priv->transceiver, 1);

	priv->क्रमce_quit = 0;
	priv->tx_skb = शून्य;
	priv->tx_len = 0;

	अगर (!dev_fwnode(&spi->dev))
		flags = IRQF_TRIGGER_FALLING;

	ret = request_thपढ़ोed_irq(spi->irq, शून्य, mcp251x_can_ist,
				   flags | IRQF_ONESHOT, dev_name(&spi->dev),
				   priv);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to acquire irq %d\n", spi->irq);
		जाओ out_बंद;
	पूर्ण

	ret = mcp251x_hw_wake(spi);
	अगर (ret)
		जाओ out_मुक्त_irq;
	ret = mcp251x_setup(net, spi);
	अगर (ret)
		जाओ out_मुक्त_irq;
	ret = mcp251x_set_normal_mode(spi);
	अगर (ret)
		जाओ out_मुक्त_irq;

	can_led_event(net, CAN_LED_EVENT_OPEN);

	netअगर_wake_queue(net);
	mutex_unlock(&priv->mcp_lock);

	वापस 0;

out_मुक्त_irq:
	मुक्त_irq(spi->irq, priv);
	mcp251x_hw_sleep(spi);
out_बंद:
	mcp251x_घातer_enable(priv->transceiver, 0);
	बंद_candev(net);
	mutex_unlock(&priv->mcp_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mcp251x_netdev_ops = अणु
	.nकरो_खोलो = mcp251x_खोलो,
	.nकरो_stop = mcp251x_stop,
	.nकरो_start_xmit = mcp251x_hard_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mcp251x_of_match[] = अणु
	अणु
		.compatible	= "microchip,mcp2510",
		.data		= (व्योम *)CAN_MCP251X_MCP2510,
	पूर्ण,
	अणु
		.compatible	= "microchip,mcp2515",
		.data		= (व्योम *)CAN_MCP251X_MCP2515,
	पूर्ण,
	अणु
		.compatible	= "microchip,mcp25625",
		.data		= (व्योम *)CAN_MCP251X_MCP25625,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mcp251x_of_match);

अटल स्थिर काष्ठा spi_device_id mcp251x_id_table[] = अणु
	अणु
		.name		= "mcp2510",
		.driver_data	= (kernel_uदीर्घ_t)CAN_MCP251X_MCP2510,
	पूर्ण,
	अणु
		.name		= "mcp2515",
		.driver_data	= (kernel_uदीर्घ_t)CAN_MCP251X_MCP2515,
	पूर्ण,
	अणु
		.name		= "mcp25625",
		.driver_data	= (kernel_uदीर्घ_t)CAN_MCP251X_MCP25625,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp251x_id_table);

अटल पूर्णांक mcp251x_can_probe(काष्ठा spi_device *spi)
अणु
	स्थिर व्योम *match = device_get_match_data(&spi->dev);
	काष्ठा net_device *net;
	काष्ठा mcp251x_priv *priv;
	काष्ठा clk *clk;
	u32 freq;
	पूर्णांक ret;

	clk = devm_clk_get_optional(&spi->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	freq = clk_get_rate(clk);
	अगर (freq == 0)
		device_property_पढ़ो_u32(&spi->dev, "clock-frequency", &freq);

	/* Sanity check */
	अगर (freq < 1000000 || freq > 25000000)
		वापस -दुस्फल;

	/* Allocate can/net device */
	net = alloc_candev(माप(काष्ठा mcp251x_priv), TX_ECHO_SKB_MAX);
	अगर (!net)
		वापस -ENOMEM;

	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ out_मुक्त;

	net->netdev_ops = &mcp251x_netdev_ops;
	net->flags |= IFF_ECHO;

	priv = netdev_priv(net);
	priv->can.bittiming_स्थिर = &mcp251x_bittiming_स्थिर;
	priv->can.करो_set_mode = mcp251x_करो_set_mode;
	priv->can.घड़ी.freq = freq / 2;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_3_SAMPLES |
		CAN_CTRLMODE_LOOPBACK | CAN_CTRLMODE_LISTENONLY;
	अगर (match)
		priv->model = (क्रमागत mcp251x_model)match;
	अन्यथा
		priv->model = spi_get_device_id(spi)->driver_data;
	priv->net = net;
	priv->clk = clk;

	spi_set_drvdata(spi, priv);

	/* Configure the SPI bus */
	spi->bits_per_word = 8;
	अगर (mcp251x_is_2510(spi))
		spi->max_speed_hz = spi->max_speed_hz ? : 5 * 1000 * 1000;
	अन्यथा
		spi->max_speed_hz = spi->max_speed_hz ? : 10 * 1000 * 1000;
	ret = spi_setup(spi);
	अगर (ret)
		जाओ out_clk;

	priv->घातer = devm_regulator_get_optional(&spi->dev, "vdd");
	priv->transceiver = devm_regulator_get_optional(&spi->dev, "xceiver");
	अगर ((PTR_ERR(priv->घातer) == -EPROBE_DEFER) ||
	    (PTR_ERR(priv->transceiver) == -EPROBE_DEFER)) अणु
		ret = -EPROBE_DEFER;
		जाओ out_clk;
	पूर्ण

	ret = mcp251x_घातer_enable(priv->घातer, 1);
	अगर (ret)
		जाओ out_clk;

	priv->wq = alloc_workqueue("mcp251x_wq", WQ_FREEZABLE | WQ_MEM_RECLAIM,
				   0);
	अगर (!priv->wq) अणु
		ret = -ENOMEM;
		जाओ out_clk;
	पूर्ण
	INIT_WORK(&priv->tx_work, mcp251x_tx_work_handler);
	INIT_WORK(&priv->restart_work, mcp251x_restart_work_handler);

	priv->spi = spi;
	mutex_init(&priv->mcp_lock);

	priv->spi_tx_buf = devm_kzalloc(&spi->dev, SPI_TRANSFER_BUF_LEN,
					GFP_KERNEL);
	अगर (!priv->spi_tx_buf) अणु
		ret = -ENOMEM;
		जाओ error_probe;
	पूर्ण

	priv->spi_rx_buf = devm_kzalloc(&spi->dev, SPI_TRANSFER_BUF_LEN,
					GFP_KERNEL);
	अगर (!priv->spi_rx_buf) अणु
		ret = -ENOMEM;
		जाओ error_probe;
	पूर्ण

	SET_NETDEV_DEV(net, &spi->dev);

	/* Here is OK to not lock the MCP, no one knows about it yet */
	ret = mcp251x_hw_probe(spi);
	अगर (ret) अणु
		अगर (ret == -ENODEV)
			dev_err(&spi->dev, "Cannot initialize MCP%x. Wrong wiring?\n",
				priv->model);
		जाओ error_probe;
	पूर्ण

	mcp251x_hw_sleep(spi);

	ret = रेजिस्टर_candev(net);
	अगर (ret)
		जाओ error_probe;

	devm_can_led_init(net);

	ret = mcp251x_gpio_setup(priv);
	अगर (ret)
		जाओ error_probe;

	netdev_info(net, "MCP%x successfully initialized.\n", priv->model);
	वापस 0;

error_probe:
	destroy_workqueue(priv->wq);
	priv->wq = शून्य;
	mcp251x_घातer_enable(priv->घातer, 0);

out_clk:
	clk_disable_unprepare(clk);

out_मुक्त:
	मुक्त_candev(net);

	dev_err(&spi->dev, "Probe failed, err=%d\n", -ret);
	वापस ret;
पूर्ण

अटल पूर्णांक mcp251x_can_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	काष्ठा net_device *net = priv->net;

	unरेजिस्टर_candev(net);

	mcp251x_घातer_enable(priv->घातer, 0);

	destroy_workqueue(priv->wq);
	priv->wq = शून्य;

	clk_disable_unprepare(priv->clk);

	मुक्त_candev(net);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mcp251x_can_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);
	काष्ठा net_device *net = priv->net;

	priv->क्रमce_quit = 1;
	disable_irq(spi->irq);
	/* Note: at this poपूर्णांक neither IST nor workqueues are running.
	 * खोलो/stop cannot be called anyway so locking is not needed
	 */
	अगर (netअगर_running(net)) अणु
		netअगर_device_detach(net);

		mcp251x_hw_sleep(spi);
		mcp251x_घातer_enable(priv->transceiver, 0);
		priv->after_suspend = AFTER_SUSPEND_UP;
	पूर्ण अन्यथा अणु
		priv->after_suspend = AFTER_SUSPEND_DOWN;
	पूर्ण

	mcp251x_घातer_enable(priv->घातer, 0);
	priv->after_suspend |= AFTER_SUSPEND_POWER;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mcp251x_can_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	काष्ठा mcp251x_priv *priv = spi_get_drvdata(spi);

	अगर (priv->after_suspend & AFTER_SUSPEND_POWER)
		mcp251x_घातer_enable(priv->घातer, 1);
	अगर (priv->after_suspend & AFTER_SUSPEND_UP)
		mcp251x_घातer_enable(priv->transceiver, 1);

	अगर (priv->after_suspend & (AFTER_SUSPEND_POWER | AFTER_SUSPEND_UP))
		queue_work(priv->wq, &priv->restart_work);
	अन्यथा
		priv->after_suspend = 0;

	priv->क्रमce_quit = 0;
	enable_irq(spi->irq);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(mcp251x_can_pm_ops, mcp251x_can_suspend,
	mcp251x_can_resume);

अटल काष्ठा spi_driver mcp251x_can_driver = अणु
	.driver = अणु
		.name = DEVICE_NAME,
		.of_match_table = mcp251x_of_match,
		.pm = &mcp251x_can_pm_ops,
	पूर्ण,
	.id_table = mcp251x_id_table,
	.probe = mcp251x_can_probe,
	.हटाओ = mcp251x_can_हटाओ,
पूर्ण;
module_spi_driver(mcp251x_can_driver);

MODULE_AUTHOR("Chris Elston <celston@katalix.com>, "
	      "Christian Pellegrin <chripell@evolware.org>");
MODULE_DESCRIPTION("Microchip 251x/25625 CAN driver");
MODULE_LICENSE("GPL v2");
