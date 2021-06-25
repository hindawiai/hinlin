<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011-2015 Daniel Schwierzeck <daniel.schwierzeck@gmail.com>
 * Copyright (C) 2016 Hauke Mehrtens <hauke@hauke-m.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/completion.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>

#अगर_घोषित CONFIG_LANTIQ
#समावेश <lantiq_soc.h>
#पूर्ण_अगर

#घोषणा LTQ_SPI_RX_IRQ_NAME	"spi_rx"
#घोषणा LTQ_SPI_TX_IRQ_NAME	"spi_tx"
#घोषणा LTQ_SPI_ERR_IRQ_NAME	"spi_err"
#घोषणा LTQ_SPI_FRM_IRQ_NAME	"spi_frm"

#घोषणा LTQ_SPI_CLC		0x00
#घोषणा LTQ_SPI_PISEL		0x04
#घोषणा LTQ_SPI_ID		0x08
#घोषणा LTQ_SPI_CON		0x10
#घोषणा LTQ_SPI_STAT		0x14
#घोषणा LTQ_SPI_WHBSTATE	0x18
#घोषणा LTQ_SPI_TB		0x20
#घोषणा LTQ_SPI_RB		0x24
#घोषणा LTQ_SPI_RXFCON		0x30
#घोषणा LTQ_SPI_TXFCON		0x34
#घोषणा LTQ_SPI_FSTAT		0x38
#घोषणा LTQ_SPI_BRT		0x40
#घोषणा LTQ_SPI_BRSTAT		0x44
#घोषणा LTQ_SPI_SFCON		0x60
#घोषणा LTQ_SPI_SFSTAT		0x64
#घोषणा LTQ_SPI_GPOCON		0x70
#घोषणा LTQ_SPI_GPOSTAT		0x74
#घोषणा LTQ_SPI_FPGO		0x78
#घोषणा LTQ_SPI_RXREQ		0x80
#घोषणा LTQ_SPI_RXCNT		0x84
#घोषणा LTQ_SPI_DMACON		0xec
#घोषणा LTQ_SPI_IRNEN		0xf4

#घोषणा LTQ_SPI_CLC_SMC_S	16	/* Clock भागider क्रम sleep mode */
#घोषणा LTQ_SPI_CLC_SMC_M	(0xFF << LTQ_SPI_CLC_SMC_S)
#घोषणा LTQ_SPI_CLC_RMC_S	8	/* Clock भागider क्रम normal run mode */
#घोषणा LTQ_SPI_CLC_RMC_M	(0xFF << LTQ_SPI_CLC_RMC_S)
#घोषणा LTQ_SPI_CLC_DISS	BIT(1)	/* Disable status bit */
#घोषणा LTQ_SPI_CLC_DISR	BIT(0)	/* Disable request bit */

#घोषणा LTQ_SPI_ID_TXFS_S	24	/* Implemented TX FIFO size */
#घोषणा LTQ_SPI_ID_RXFS_S	16	/* Implemented RX FIFO size */
#घोषणा LTQ_SPI_ID_MOD_S	8	/* Module ID */
#घोषणा LTQ_SPI_ID_MOD_M	(0xff << LTQ_SPI_ID_MOD_S)
#घोषणा LTQ_SPI_ID_CFG_S	5	/* DMA पूर्णांकerface support */
#घोषणा LTQ_SPI_ID_CFG_M	(1 << LTQ_SPI_ID_CFG_S)
#घोषणा LTQ_SPI_ID_REV_M	0x1F	/* Hardware revision number */

#घोषणा LTQ_SPI_CON_BM_S	16	/* Data width selection */
#घोषणा LTQ_SPI_CON_BM_M	(0x1F << LTQ_SPI_CON_BM_S)
#घोषणा LTQ_SPI_CON_EM		BIT(24)	/* Echo mode */
#घोषणा LTQ_SPI_CON_IDLE	BIT(23)	/* Idle bit value */
#घोषणा LTQ_SPI_CON_ENBV	BIT(22)	/* Enable byte valid control */
#घोषणा LTQ_SPI_CON_RUEN	BIT(12)	/* Receive underflow error enable */
#घोषणा LTQ_SPI_CON_TUEN	BIT(11)	/* Transmit underflow error enable */
#घोषणा LTQ_SPI_CON_AEN		BIT(10)	/* Abort error enable */
#घोषणा LTQ_SPI_CON_REN		BIT(9)	/* Receive overflow error enable */
#घोषणा LTQ_SPI_CON_TEN		BIT(8)	/* Transmit overflow error enable */
#घोषणा LTQ_SPI_CON_LB		BIT(7)	/* Loopback control */
#घोषणा LTQ_SPI_CON_PO		BIT(6)	/* Clock polarity control */
#घोषणा LTQ_SPI_CON_PH		BIT(5)	/* Clock phase control */
#घोषणा LTQ_SPI_CON_HB		BIT(4)	/* Heading control */
#घोषणा LTQ_SPI_CON_RXOFF	BIT(1)	/* Switch receiver off */
#घोषणा LTQ_SPI_CON_TXOFF	BIT(0)	/* Switch transmitter off */

#घोषणा LTQ_SPI_STAT_RXBV_S	28
#घोषणा LTQ_SPI_STAT_RXBV_M	(0x7 << LTQ_SPI_STAT_RXBV_S)
#घोषणा LTQ_SPI_STAT_BSY	BIT(13)	/* Busy flag */
#घोषणा LTQ_SPI_STAT_RUE	BIT(12)	/* Receive underflow error flag */
#घोषणा LTQ_SPI_STAT_TUE	BIT(11)	/* Transmit underflow error flag */
#घोषणा LTQ_SPI_STAT_AE		BIT(10)	/* Abort error flag */
#घोषणा LTQ_SPI_STAT_RE		BIT(9)	/* Receive error flag */
#घोषणा LTQ_SPI_STAT_TE		BIT(8)	/* Transmit error flag */
#घोषणा LTQ_SPI_STAT_ME		BIT(7)	/* Mode error flag */
#घोषणा LTQ_SPI_STAT_MS		BIT(1)	/* Master/slave select bit */
#घोषणा LTQ_SPI_STAT_EN		BIT(0)	/* Enable bit */
#घोषणा LTQ_SPI_STAT_ERRORS	(LTQ_SPI_STAT_ME | LTQ_SPI_STAT_TE | \
				 LTQ_SPI_STAT_RE | LTQ_SPI_STAT_AE | \
				 LTQ_SPI_STAT_TUE | LTQ_SPI_STAT_RUE)

#घोषणा LTQ_SPI_WHBSTATE_SETTUE	BIT(15)	/* Set transmit underflow error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETAE	BIT(14)	/* Set पात error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETRE	BIT(13)	/* Set receive error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETTE	BIT(12)	/* Set transmit error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRTUE	BIT(11)	/* Clear transmit underflow error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRAE	BIT(10)	/* Clear पात error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRRE	BIT(9)	/* Clear receive error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRTE	BIT(8)	/* Clear transmit error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETME	BIT(7)	/* Set mode error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRME	BIT(6)	/* Clear mode error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETRUE	BIT(5)	/* Set receive underflow error flag */
#घोषणा LTQ_SPI_WHBSTATE_CLRRUE	BIT(4)	/* Clear receive underflow error flag */
#घोषणा LTQ_SPI_WHBSTATE_SETMS	BIT(3)	/* Set master select bit */
#घोषणा LTQ_SPI_WHBSTATE_CLRMS	BIT(2)	/* Clear master select bit */
#घोषणा LTQ_SPI_WHBSTATE_SETEN	BIT(1)	/* Set enable bit (operational mode) */
#घोषणा LTQ_SPI_WHBSTATE_CLREN	BIT(0)	/* Clear enable bit (config mode */
#घोषणा LTQ_SPI_WHBSTATE_CLR_ERRORS	(LTQ_SPI_WHBSTATE_CLRRUE | \
					 LTQ_SPI_WHBSTATE_CLRME | \
					 LTQ_SPI_WHBSTATE_CLRTE | \
					 LTQ_SPI_WHBSTATE_CLRRE | \
					 LTQ_SPI_WHBSTATE_CLRAE | \
					 LTQ_SPI_WHBSTATE_CLRTUE)

#घोषणा LTQ_SPI_RXFCON_RXFITL_S	8	/* FIFO पूर्णांकerrupt trigger level */
#घोषणा LTQ_SPI_RXFCON_RXFLU	BIT(1)	/* FIFO flush */
#घोषणा LTQ_SPI_RXFCON_RXFEN	BIT(0)	/* FIFO enable */

#घोषणा LTQ_SPI_TXFCON_TXFITL_S	8	/* FIFO पूर्णांकerrupt trigger level */
#घोषणा LTQ_SPI_TXFCON_TXFLU	BIT(1)	/* FIFO flush */
#घोषणा LTQ_SPI_TXFCON_TXFEN	BIT(0)	/* FIFO enable */

#घोषणा LTQ_SPI_FSTAT_RXFFL_S	0
#घोषणा LTQ_SPI_FSTAT_TXFFL_S	8

#घोषणा LTQ_SPI_GPOCON_ISCSBN_S	8
#घोषणा LTQ_SPI_GPOCON_INVOUTN_S	0

#घोषणा LTQ_SPI_FGPO_SETOUTN_S	8
#घोषणा LTQ_SPI_FGPO_CLROUTN_S	0

#घोषणा LTQ_SPI_RXREQ_RXCNT_M	0xFFFF	/* Receive count value */
#घोषणा LTQ_SPI_RXCNT_TODO_M	0xFFFF	/* Recevie to-करो value */

#घोषणा LTQ_SPI_IRNEN_TFI	BIT(4)	/* TX finished पूर्णांकerrupt */
#घोषणा LTQ_SPI_IRNEN_F		BIT(3)	/* Frame end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_E		BIT(2)	/* Error end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_T_XWAY	BIT(1)	/* Transmit end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_R_XWAY	BIT(0)	/* Receive end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_R_XRX	BIT(1)	/* Transmit end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_T_XRX	BIT(0)	/* Receive end पूर्णांकerrupt request */
#घोषणा LTQ_SPI_IRNEN_ALL	0x1F

काष्ठा lantiq_ssc_spi;

काष्ठा lantiq_ssc_hwcfg अणु
	पूर्णांक (*cfg_irq)(काष्ठा platक्रमm_device *pdev, काष्ठा lantiq_ssc_spi *spi);
	अचिन्हित पूर्णांक	irnen_r;
	अचिन्हित पूर्णांक	irnen_t;
	अचिन्हित पूर्णांक	irncr;
	अचिन्हित पूर्णांक	irnicr;
	bool		irq_ack;
	u32		fअगरo_size_mask;
पूर्ण;

काष्ठा lantiq_ssc_spi अणु
	काष्ठा spi_master		*master;
	काष्ठा device			*dev;
	व्योम __iomem			*regbase;
	काष्ठा clk			*spi_clk;
	काष्ठा clk			*fpi_clk;
	स्थिर काष्ठा lantiq_ssc_hwcfg	*hwcfg;

	spinlock_t			lock;
	काष्ठा workqueue_काष्ठा		*wq;
	काष्ठा work_काष्ठा		work;

	स्थिर u8			*tx;
	u8				*rx;
	अचिन्हित पूर्णांक			tx_toकरो;
	अचिन्हित पूर्णांक			rx_toकरो;
	अचिन्हित पूर्णांक			bits_per_word;
	अचिन्हित पूर्णांक			speed_hz;
	अचिन्हित पूर्णांक			tx_fअगरo_size;
	अचिन्हित पूर्णांक			rx_fअगरo_size;
	अचिन्हित पूर्णांक			base_cs;
	अचिन्हित पूर्णांक			fdx_tx_level;
पूर्ण;

अटल u32 lantiq_ssc_पढ़ोl(स्थिर काष्ठा lantiq_ssc_spi *spi, u32 reg)
अणु
	वापस __raw_पढ़ोl(spi->regbase + reg);
पूर्ण

अटल व्योम lantiq_ssc_ग_लिखोl(स्थिर काष्ठा lantiq_ssc_spi *spi, u32 val,
			      u32 reg)
अणु
	__raw_ग_लिखोl(val, spi->regbase + reg);
पूर्ण

अटल व्योम lantiq_ssc_maskl(स्थिर काष्ठा lantiq_ssc_spi *spi, u32 clr,
			     u32 set, u32 reg)
अणु
	u32 val = __raw_पढ़ोl(spi->regbase + reg);

	val &= ~clr;
	val |= set;
	__raw_ग_लिखोl(val, spi->regbase + reg);
पूर्ण

अटल अचिन्हित पूर्णांक tx_fअगरo_level(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;
	u32 ख_स्थिति = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_FSTAT);

	वापस (ख_स्थिति >> LTQ_SPI_FSTAT_TXFFL_S) & hwcfg->fअगरo_size_mask;
पूर्ण

अटल अचिन्हित पूर्णांक rx_fअगरo_level(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;
	u32 ख_स्थिति = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_FSTAT);

	वापस (ख_स्थिति >> LTQ_SPI_FSTAT_RXFFL_S) & hwcfg->fअगरo_size_mask;
पूर्ण

अटल अचिन्हित पूर्णांक tx_fअगरo_मुक्त(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	वापस spi->tx_fअगरo_size - tx_fअगरo_level(spi);
पूर्ण

अटल व्योम rx_fअगरo_reset(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	u32 val = spi->rx_fअगरo_size << LTQ_SPI_RXFCON_RXFITL_S;

	val |= LTQ_SPI_RXFCON_RXFEN | LTQ_SPI_RXFCON_RXFLU;
	lantiq_ssc_ग_लिखोl(spi, val, LTQ_SPI_RXFCON);
पूर्ण

अटल व्योम tx_fअगरo_reset(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	u32 val = 1 << LTQ_SPI_TXFCON_TXFITL_S;

	val |= LTQ_SPI_TXFCON_TXFEN | LTQ_SPI_TXFCON_TXFLU;
	lantiq_ssc_ग_लिखोl(spi, val, LTQ_SPI_TXFCON);
पूर्ण

अटल व्योम rx_fअगरo_flush(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_RXFCON_RXFLU, LTQ_SPI_RXFCON);
पूर्ण

अटल व्योम tx_fअगरo_flush(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_TXFCON_TXFLU, LTQ_SPI_TXFCON);
पूर्ण

अटल व्योम hw_enter_config_mode(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	lantiq_ssc_ग_लिखोl(spi, LTQ_SPI_WHBSTATE_CLREN, LTQ_SPI_WHBSTATE);
पूर्ण

अटल व्योम hw_enter_active_mode(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	lantiq_ssc_ग_लिखोl(spi, LTQ_SPI_WHBSTATE_SETEN, LTQ_SPI_WHBSTATE);
पूर्ण

अटल व्योम hw_setup_speed_hz(स्थिर काष्ठा lantiq_ssc_spi *spi,
			      अचिन्हित पूर्णांक max_speed_hz)
अणु
	u32 spi_clk, brt;

	/*
	 * SPI module घड़ी is derived from FPI bus घड़ी dependent on
	 * भागider value in CLC.RMS which is always set to 1.
	 *
	 *                 f_SPI
	 * baudrate = --------------
	 *             2 * (BR + 1)
	 */
	spi_clk = clk_get_rate(spi->fpi_clk) / 2;

	अगर (max_speed_hz > spi_clk)
		brt = 0;
	अन्यथा
		brt = spi_clk / max_speed_hz - 1;

	अगर (brt > 0xFFFF)
		brt = 0xFFFF;

	dev_dbg(spi->dev, "spi_clk %u, max_speed_hz %u, brt %u\n",
		spi_clk, max_speed_hz, brt);

	lantiq_ssc_ग_लिखोl(spi, brt, LTQ_SPI_BRT);
पूर्ण

अटल व्योम hw_setup_bits_per_word(स्थिर काष्ठा lantiq_ssc_spi *spi,
				   अचिन्हित पूर्णांक bits_per_word)
अणु
	u32 bm;

	/* CON.BM value = bits_per_word - 1 */
	bm = (bits_per_word - 1) << LTQ_SPI_CON_BM_S;

	lantiq_ssc_maskl(spi, LTQ_SPI_CON_BM_M, bm, LTQ_SPI_CON);
पूर्ण

अटल व्योम hw_setup_घड़ी_mode(स्थिर काष्ठा lantiq_ssc_spi *spi,
				अचिन्हित पूर्णांक mode)
अणु
	u32 con_set = 0, con_clr = 0;

	/*
	 * SPI mode mapping in CON रेजिस्टर:
	 * Mode CPOL CPHA CON.PO CON.PH
	 *  0    0    0      0      1
	 *  1    0    1      0      0
	 *  2    1    0      1      1
	 *  3    1    1      1      0
	 */
	अगर (mode & SPI_CPHA)
		con_clr |= LTQ_SPI_CON_PH;
	अन्यथा
		con_set |= LTQ_SPI_CON_PH;

	अगर (mode & SPI_CPOL)
		con_set |= LTQ_SPI_CON_PO | LTQ_SPI_CON_IDLE;
	अन्यथा
		con_clr |= LTQ_SPI_CON_PO | LTQ_SPI_CON_IDLE;

	/* Set heading control */
	अगर (mode & SPI_LSB_FIRST)
		con_clr |= LTQ_SPI_CON_HB;
	अन्यथा
		con_set |= LTQ_SPI_CON_HB;

	/* Set loopback mode */
	अगर (mode & SPI_LOOP)
		con_set |= LTQ_SPI_CON_LB;
	अन्यथा
		con_clr |= LTQ_SPI_CON_LB;

	lantiq_ssc_maskl(spi, con_clr, con_set, LTQ_SPI_CON);
पूर्ण

अटल व्योम lantiq_ssc_hw_init(स्थिर काष्ठा lantiq_ssc_spi *spi)
अणु
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;

	/*
	 * Set घड़ी भागider क्रम run mode to 1 to
	 * run at same frequency as FPI bus
	 */
	lantiq_ssc_ग_लिखोl(spi, 1 << LTQ_SPI_CLC_RMC_S, LTQ_SPI_CLC);

	/* Put controller पूर्णांकo config mode */
	hw_enter_config_mode(spi);

	/* Clear error flags */
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_WHBSTATE_CLR_ERRORS, LTQ_SPI_WHBSTATE);

	/* Enable error checking, disable TX/RX */
	lantiq_ssc_ग_लिखोl(spi, LTQ_SPI_CON_RUEN | LTQ_SPI_CON_AEN |
		LTQ_SPI_CON_TEN | LTQ_SPI_CON_REN | LTQ_SPI_CON_TXOFF |
		LTQ_SPI_CON_RXOFF, LTQ_SPI_CON);

	/* Setup शेष SPI mode */
	hw_setup_bits_per_word(spi, spi->bits_per_word);
	hw_setup_घड़ी_mode(spi, SPI_MODE_0);

	/* Enable master mode and clear error flags */
	lantiq_ssc_ग_लिखोl(spi, LTQ_SPI_WHBSTATE_SETMS |
			       LTQ_SPI_WHBSTATE_CLR_ERRORS,
			       LTQ_SPI_WHBSTATE);

	/* Reset GPIO/CS रेजिस्टरs */
	lantiq_ssc_ग_लिखोl(spi, 0, LTQ_SPI_GPOCON);
	lantiq_ssc_ग_लिखोl(spi, 0xFF00, LTQ_SPI_FPGO);

	/* Enable and flush FIFOs */
	rx_fअगरo_reset(spi);
	tx_fअगरo_reset(spi);

	/* Enable पूर्णांकerrupts */
	lantiq_ssc_ग_लिखोl(spi, hwcfg->irnen_t | hwcfg->irnen_r |
			  LTQ_SPI_IRNEN_E, LTQ_SPI_IRNEN);
पूर्ण

अटल पूर्णांक lantiq_ssc_setup(काष्ठा spi_device *spidev)
अणु
	काष्ठा spi_master *master = spidev->master;
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक cs = spidev->chip_select;
	u32 gpocon;

	/* GPIOs are used क्रम CS */
	अगर (spidev->cs_gpiod)
		वापस 0;

	dev_dbg(spi->dev, "using internal chipselect %u\n", cs);

	अगर (cs < spi->base_cs) अणु
		dev_err(spi->dev,
			"chipselect %i too small (min %i)\n", cs, spi->base_cs);
		वापस -EINVAL;
	पूर्ण

	/* set GPO pin to CS mode */
	gpocon = 1 << ((cs - spi->base_cs) + LTQ_SPI_GPOCON_ISCSBN_S);

	/* invert GPO pin */
	अगर (spidev->mode & SPI_CS_HIGH)
		gpocon |= 1 << (cs - spi->base_cs);

	lantiq_ssc_maskl(spi, 0, gpocon, LTQ_SPI_GPOCON);

	वापस 0;
पूर्ण

अटल पूर्णांक lantiq_ssc_prepare_message(काष्ठा spi_master *master,
				      काष्ठा spi_message *message)
अणु
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(master);

	hw_enter_config_mode(spi);
	hw_setup_घड़ी_mode(spi, message->spi->mode);
	hw_enter_active_mode(spi);

	वापस 0;
पूर्ण

अटल व्योम hw_setup_transfer(काष्ठा lantiq_ssc_spi *spi,
			      काष्ठा spi_device *spidev, काष्ठा spi_transfer *t)
अणु
	अचिन्हित पूर्णांक speed_hz = t->speed_hz;
	अचिन्हित पूर्णांक bits_per_word = t->bits_per_word;
	u32 con;

	अगर (bits_per_word != spi->bits_per_word ||
		speed_hz != spi->speed_hz) अणु
		hw_enter_config_mode(spi);
		hw_setup_speed_hz(spi, speed_hz);
		hw_setup_bits_per_word(spi, bits_per_word);
		hw_enter_active_mode(spi);

		spi->speed_hz = speed_hz;
		spi->bits_per_word = bits_per_word;
	पूर्ण

	/* Configure transmitter and receiver */
	con = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_CON);
	अगर (t->tx_buf)
		con &= ~LTQ_SPI_CON_TXOFF;
	अन्यथा
		con |= LTQ_SPI_CON_TXOFF;

	अगर (t->rx_buf)
		con &= ~LTQ_SPI_CON_RXOFF;
	अन्यथा
		con |= LTQ_SPI_CON_RXOFF;

	lantiq_ssc_ग_लिखोl(spi, con, LTQ_SPI_CON);
पूर्ण

अटल पूर्णांक lantiq_ssc_unprepare_message(काष्ठा spi_master *master,
					काष्ठा spi_message *message)
अणु
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(master);

	flush_workqueue(spi->wq);

	/* Disable transmitter and receiver जबतक idle */
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_CON_TXOFF | LTQ_SPI_CON_RXOFF,
			 LTQ_SPI_CON);

	वापस 0;
पूर्ण

अटल व्योम tx_fअगरo_ग_लिखो(काष्ठा lantiq_ssc_spi *spi)
अणु
	स्थिर u8 *tx8;
	स्थिर u16 *tx16;
	स्थिर u32 *tx32;
	u32 data;
	अचिन्हित पूर्णांक tx_मुक्त = tx_fअगरo_मुक्त(spi);

	spi->fdx_tx_level = 0;
	जबतक (spi->tx_toकरो && tx_मुक्त) अणु
		चयन (spi->bits_per_word) अणु
		हाल 2 ... 8:
			tx8 = spi->tx;
			data = *tx8;
			spi->tx_toकरो--;
			spi->tx++;
			अवरोध;
		हाल 16:
			tx16 = (u16 *) spi->tx;
			data = *tx16;
			spi->tx_toकरो -= 2;
			spi->tx += 2;
			अवरोध;
		हाल 32:
			tx32 = (u32 *) spi->tx;
			data = *tx32;
			spi->tx_toकरो -= 4;
			spi->tx += 4;
			अवरोध;
		शेष:
			WARN_ON(1);
			data = 0;
			अवरोध;
		पूर्ण

		lantiq_ssc_ग_लिखोl(spi, data, LTQ_SPI_TB);
		tx_मुक्त--;
		spi->fdx_tx_level++;
	पूर्ण
पूर्ण

अटल व्योम rx_fअगरo_पढ़ो_full_duplex(काष्ठा lantiq_ssc_spi *spi)
अणु
	u8 *rx8;
	u16 *rx16;
	u32 *rx32;
	u32 data;
	अचिन्हित पूर्णांक rx_fill = rx_fअगरo_level(spi);

	/*
	 * Wait until all expected data to be shअगरted in.
	 * Otherwise, rx overrun may occur.
	 */
	जबतक (rx_fill != spi->fdx_tx_level)
		rx_fill = rx_fअगरo_level(spi);

	जबतक (rx_fill) अणु
		data = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_RB);

		चयन (spi->bits_per_word) अणु
		हाल 2 ... 8:
			rx8 = spi->rx;
			*rx8 = data;
			spi->rx_toकरो--;
			spi->rx++;
			अवरोध;
		हाल 16:
			rx16 = (u16 *) spi->rx;
			*rx16 = data;
			spi->rx_toकरो -= 2;
			spi->rx += 2;
			अवरोध;
		हाल 32:
			rx32 = (u32 *) spi->rx;
			*rx32 = data;
			spi->rx_toकरो -= 4;
			spi->rx += 4;
			अवरोध;
		शेष:
			WARN_ON(1);
			अवरोध;
		पूर्ण

		rx_fill--;
	पूर्ण
पूर्ण

अटल व्योम rx_fअगरo_पढ़ो_half_duplex(काष्ठा lantiq_ssc_spi *spi)
अणु
	u32 data, *rx32;
	u8 *rx8;
	अचिन्हित पूर्णांक rxbv, shअगरt;
	अचिन्हित पूर्णांक rx_fill = rx_fअगरo_level(spi);

	/*
	 * In RX-only mode the bits per word value is ignored by HW. A value
	 * of 32 is used instead. Thus all 4 bytes per FIFO must be पढ़ो.
	 * If reमुख्यing RX bytes are less than 4, the FIFO must be पढ़ो
	 * dअगरferently. The amount of received and valid bytes is indicated
	 * by STAT.RXBV रेजिस्टर value.
	 */
	जबतक (rx_fill) अणु
		अगर (spi->rx_toकरो < 4)  अणु
			rxbv = (lantiq_ssc_पढ़ोl(spi, LTQ_SPI_STAT) &
				LTQ_SPI_STAT_RXBV_M) >> LTQ_SPI_STAT_RXBV_S;
			data = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_RB);

			shअगरt = (rxbv - 1) * 8;
			rx8 = spi->rx;

			जबतक (rxbv) अणु
				*rx8++ = (data >> shअगरt) & 0xFF;
				rxbv--;
				shअगरt -= 8;
				spi->rx_toकरो--;
				spi->rx++;
			पूर्ण
		पूर्ण अन्यथा अणु
			data = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_RB);
			rx32 = (u32 *) spi->rx;

			*rx32++ = data;
			spi->rx_toकरो -= 4;
			spi->rx += 4;
		पूर्ण
		rx_fill--;
	पूर्ण
पूर्ण

अटल व्योम rx_request(काष्ठा lantiq_ssc_spi *spi)
अणु
	अचिन्हित पूर्णांक rxreq, rxreq_max;

	/*
	 * To aव्योम receive overflows at high घड़ीs it is better to request
	 * only the amount of bytes that fits पूर्णांकo all FIFOs. This value
	 * depends on the FIFO size implemented in hardware.
	 */
	rxreq = spi->rx_toकरो;
	rxreq_max = spi->rx_fअगरo_size * 4;
	अगर (rxreq > rxreq_max)
		rxreq = rxreq_max;

	lantiq_ssc_ग_लिखोl(spi, rxreq, LTQ_SPI_RXREQ);
पूर्ण

अटल irqवापस_t lantiq_ssc_xmit_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lantiq_ssc_spi *spi = data;
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;
	u32 val = lantiq_ssc_पढ़ोl(spi, hwcfg->irncr);

	spin_lock(&spi->lock);
	अगर (hwcfg->irq_ack)
		lantiq_ssc_ग_लिखोl(spi, val, hwcfg->irncr);

	अगर (spi->tx) अणु
		अगर (spi->rx && spi->rx_toकरो)
			rx_fअगरo_पढ़ो_full_duplex(spi);

		अगर (spi->tx_toकरो)
			tx_fअगरo_ग_लिखो(spi);
		अन्यथा अगर (!tx_fअगरo_level(spi))
			जाओ completed;
	पूर्ण अन्यथा अगर (spi->rx) अणु
		अगर (spi->rx_toकरो) अणु
			rx_fअगरo_पढ़ो_half_duplex(spi);

			अगर (spi->rx_toकरो)
				rx_request(spi);
			अन्यथा
				जाओ completed;
		पूर्ण अन्यथा अणु
			जाओ completed;
		पूर्ण
	पूर्ण

	spin_unlock(&spi->lock);
	वापस IRQ_HANDLED;

completed:
	queue_work(spi->wq, &spi->work);
	spin_unlock(&spi->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t lantiq_ssc_err_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lantiq_ssc_spi *spi = data;
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;
	u32 stat = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_STAT);
	u32 val = lantiq_ssc_पढ़ोl(spi, hwcfg->irncr);

	अगर (!(stat & LTQ_SPI_STAT_ERRORS))
		वापस IRQ_NONE;

	spin_lock(&spi->lock);
	अगर (hwcfg->irq_ack)
		lantiq_ssc_ग_लिखोl(spi, val, hwcfg->irncr);

	अगर (stat & LTQ_SPI_STAT_RUE)
		dev_err(spi->dev, "receive underflow error\n");
	अगर (stat & LTQ_SPI_STAT_TUE)
		dev_err(spi->dev, "transmit underflow error\n");
	अगर (stat & LTQ_SPI_STAT_AE)
		dev_err(spi->dev, "abort error\n");
	अगर (stat & LTQ_SPI_STAT_RE)
		dev_err(spi->dev, "receive overflow error\n");
	अगर (stat & LTQ_SPI_STAT_TE)
		dev_err(spi->dev, "transmit overflow error\n");
	अगर (stat & LTQ_SPI_STAT_ME)
		dev_err(spi->dev, "mode error\n");

	/* Clear error flags */
	lantiq_ssc_maskl(spi, 0, LTQ_SPI_WHBSTATE_CLR_ERRORS, LTQ_SPI_WHBSTATE);

	/* set bad status so it can be retried */
	अगर (spi->master->cur_msg)
		spi->master->cur_msg->status = -EIO;
	queue_work(spi->wq, &spi->work);
	spin_unlock(&spi->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t पूर्णांकel_lgm_ssc_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा lantiq_ssc_spi *spi = data;
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg = spi->hwcfg;
	u32 val = lantiq_ssc_पढ़ोl(spi, hwcfg->irncr);

	अगर (!(val & LTQ_SPI_IRNEN_ALL))
		वापस IRQ_NONE;

	अगर (val & LTQ_SPI_IRNEN_E)
		वापस lantiq_ssc_err_पूर्णांकerrupt(irq, data);

	अगर ((val & hwcfg->irnen_t) || (val & hwcfg->irnen_r))
		वापस lantiq_ssc_xmit_पूर्णांकerrupt(irq, data);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक transfer_start(काष्ठा lantiq_ssc_spi *spi, काष्ठा spi_device *spidev,
			  काष्ठा spi_transfer *t)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&spi->lock, flags);

	spi->tx = t->tx_buf;
	spi->rx = t->rx_buf;

	अगर (t->tx_buf) अणु
		spi->tx_toकरो = t->len;

		/* initially fill TX FIFO */
		tx_fअगरo_ग_लिखो(spi);
	पूर्ण

	अगर (spi->rx) अणु
		spi->rx_toकरो = t->len;

		/* start shअगरt घड़ी in RX-only mode */
		अगर (!spi->tx)
			rx_request(spi);
	पूर्ण

	spin_unlock_irqrestore(&spi->lock, flags);

	वापस t->len;
पूर्ण

/*
 * The driver only माला_लो an पूर्णांकerrupt when the FIFO is empty, but there
 * is an additional shअगरt रेजिस्टर from which the data is written to
 * the wire. We get the last पूर्णांकerrupt when the controller starts to
 * ग_लिखो the last word to the wire, not when it is finished. Do busy
 * रुकोing till it finishes.
 */
अटल व्योम lantiq_ssc_bussy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lantiq_ssc_spi *spi;
	अचिन्हित दीर्घ दीर्घ समयout = 8LL * 1000LL;
	अचिन्हित दीर्घ end;

	spi = container_of(work, typeof(*spi), work);

	करो_भाग(समयout, spi->speed_hz);
	समयout += समयout + 100; /* some tolerance */

	end = jअगरfies + msecs_to_jअगरfies(समयout);
	करो अणु
		u32 stat = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_STAT);

		अगर (!(stat & LTQ_SPI_STAT_BSY)) अणु
			spi_finalize_current_transfer(spi->master);
			वापस;
		पूर्ण

		cond_resched();
	पूर्ण जबतक (!समय_after_eq(jअगरfies, end));

	अगर (spi->master->cur_msg)
		spi->master->cur_msg->status = -EIO;
	spi_finalize_current_transfer(spi->master);
पूर्ण

अटल व्योम lantiq_ssc_handle_err(काष्ठा spi_master *master,
				  काष्ठा spi_message *message)
अणु
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(master);

	/* flush FIFOs on समयout */
	rx_fअगरo_flush(spi);
	tx_fअगरo_flush(spi);
पूर्ण

अटल व्योम lantiq_ssc_set_cs(काष्ठा spi_device *spidev, bool enable)
अणु
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(spidev->master);
	अचिन्हित पूर्णांक cs = spidev->chip_select;
	u32 fgpo;

	अगर (!!(spidev->mode & SPI_CS_HIGH) == enable)
		fgpo = (1 << (cs - spi->base_cs));
	अन्यथा
		fgpo = (1 << (cs - spi->base_cs + LTQ_SPI_FGPO_SETOUTN_S));

	lantiq_ssc_ग_लिखोl(spi, fgpo, LTQ_SPI_FPGO);
पूर्ण

अटल पूर्णांक lantiq_ssc_transfer_one(काष्ठा spi_master *master,
				   काष्ठा spi_device *spidev,
				   काष्ठा spi_transfer *t)
अणु
	काष्ठा lantiq_ssc_spi *spi = spi_master_get_devdata(master);

	hw_setup_transfer(spi, spidev, t);

	वापस transfer_start(spi, spidev, t);
पूर्ण

अटल पूर्णांक पूर्णांकel_lgm_cfg_irq(काष्ठा platक्रमm_device *pdev, काष्ठा lantiq_ssc_spi *spi)
अणु
	पूर्णांक irq;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	वापस devm_request_irq(&pdev->dev, irq, पूर्णांकel_lgm_ssc_isr, 0, "spi", spi);
पूर्ण

अटल पूर्णांक lantiq_cfg_irq(काष्ठा platक्रमm_device *pdev, काष्ठा lantiq_ssc_spi *spi)
अणु
	पूर्णांक irq, err;

	irq = platक्रमm_get_irq_byname(pdev, LTQ_SPI_RX_IRQ_NAME);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, lantiq_ssc_xmit_पूर्णांकerrupt,
			       0, LTQ_SPI_RX_IRQ_NAME, spi);
	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq_byname(pdev, LTQ_SPI_TX_IRQ_NAME);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, lantiq_ssc_xmit_पूर्णांकerrupt,
			       0, LTQ_SPI_TX_IRQ_NAME, spi);

	अगर (err)
		वापस err;

	irq = platक्रमm_get_irq_byname(pdev, LTQ_SPI_ERR_IRQ_NAME);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, lantiq_ssc_err_पूर्णांकerrupt,
			       0, LTQ_SPI_ERR_IRQ_NAME, spi);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा lantiq_ssc_hwcfg lantiq_ssc_xway = अणु
	.cfg_irq	= lantiq_cfg_irq,
	.irnen_r	= LTQ_SPI_IRNEN_R_XWAY,
	.irnen_t	= LTQ_SPI_IRNEN_T_XWAY,
	.irnicr		= 0xF8,
	.irncr		= 0xFC,
	.fअगरo_size_mask	= GENMASK(5, 0),
	.irq_ack	= false,
पूर्ण;

अटल स्थिर काष्ठा lantiq_ssc_hwcfg lantiq_ssc_xrx = अणु
	.cfg_irq	= lantiq_cfg_irq,
	.irnen_r	= LTQ_SPI_IRNEN_R_XRX,
	.irnen_t	= LTQ_SPI_IRNEN_T_XRX,
	.irnicr		= 0xF8,
	.irncr		= 0xFC,
	.fअगरo_size_mask	= GENMASK(5, 0),
	.irq_ack	= false,
पूर्ण;

अटल स्थिर काष्ठा lantiq_ssc_hwcfg पूर्णांकel_ssc_lgm = अणु
	.cfg_irq	= पूर्णांकel_lgm_cfg_irq,
	.irnen_r	= LTQ_SPI_IRNEN_R_XRX,
	.irnen_t	= LTQ_SPI_IRNEN_T_XRX,
	.irnicr		= 0xFC,
	.irncr		= 0xF8,
	.fअगरo_size_mask	= GENMASK(7, 0),
	.irq_ack	= true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lantiq_ssc_match[] = अणु
	अणु .compatible = "lantiq,ase-spi", .data = &lantiq_ssc_xway, पूर्ण,
	अणु .compatible = "lantiq,falcon-spi", .data = &lantiq_ssc_xrx, पूर्ण,
	अणु .compatible = "lantiq,xrx100-spi", .data = &lantiq_ssc_xrx, पूर्ण,
	अणु .compatible = "intel,lgm-spi", .data = &पूर्णांकel_ssc_lgm, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, lantiq_ssc_match);

अटल पूर्णांक lantiq_ssc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा spi_master *master;
	काष्ठा lantiq_ssc_spi *spi;
	स्थिर काष्ठा lantiq_ssc_hwcfg *hwcfg;
	स्थिर काष्ठा of_device_id *match;
	u32 id, supports_dma, revision;
	अचिन्हित पूर्णांक num_cs;
	पूर्णांक err;

	match = of_match_device(lantiq_ssc_match, dev);
	अगर (!match) अणु
		dev_err(dev, "no device match\n");
		वापस -EINVAL;
	पूर्ण
	hwcfg = match->data;

	master = spi_alloc_master(dev, माप(काष्ठा lantiq_ssc_spi));
	अगर (!master)
		वापस -ENOMEM;

	spi = spi_master_get_devdata(master);
	spi->master = master;
	spi->dev = dev;
	spi->hwcfg = hwcfg;
	platक्रमm_set_drvdata(pdev, spi);
	spi->regbase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi->regbase)) अणु
		err = PTR_ERR(spi->regbase);
		जाओ err_master_put;
	पूर्ण

	err = hwcfg->cfg_irq(pdev, spi);
	अगर (err)
		जाओ err_master_put;

	spi->spi_clk = devm_clk_get(dev, "gate");
	अगर (IS_ERR(spi->spi_clk)) अणु
		err = PTR_ERR(spi->spi_clk);
		जाओ err_master_put;
	पूर्ण
	err = clk_prepare_enable(spi->spi_clk);
	अगर (err)
		जाओ err_master_put;

	/*
	 * Use the old clk_get_fpi() function on Lantiq platक्रमm, till it
	 * supports common clk.
	 */
#अगर defined(CONFIG_LANTIQ) && !defined(CONFIG_COMMON_CLK)
	spi->fpi_clk = clk_get_fpi();
#अन्यथा
	spi->fpi_clk = clk_get(dev, "freq");
#पूर्ण_अगर
	अगर (IS_ERR(spi->fpi_clk)) अणु
		err = PTR_ERR(spi->fpi_clk);
		जाओ err_clk_disable;
	पूर्ण

	num_cs = 8;
	of_property_पढ़ो_u32(pdev->dev.of_node, "num-cs", &num_cs);

	spi->base_cs = 1;
	of_property_पढ़ो_u32(pdev->dev.of_node, "base-cs", &spi->base_cs);

	spin_lock_init(&spi->lock);
	spi->bits_per_word = 8;
	spi->speed_hz = 0;

	master->dev.of_node = pdev->dev.of_node;
	master->num_chipselect = num_cs;
	master->use_gpio_descriptors = true;
	master->setup = lantiq_ssc_setup;
	master->set_cs = lantiq_ssc_set_cs;
	master->handle_err = lantiq_ssc_handle_err;
	master->prepare_message = lantiq_ssc_prepare_message;
	master->unprepare_message = lantiq_ssc_unprepare_message;
	master->transfer_one = lantiq_ssc_transfer_one;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST | SPI_CS_HIGH |
				SPI_LOOP;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(2, 8) |
				     SPI_BPW_MASK(16) | SPI_BPW_MASK(32);

	spi->wq = alloc_ordered_workqueue(dev_name(dev), WQ_MEM_RECLAIM);
	अगर (!spi->wq) अणु
		err = -ENOMEM;
		जाओ err_clk_put;
	पूर्ण
	INIT_WORK(&spi->work, lantiq_ssc_bussy_work);

	id = lantiq_ssc_पढ़ोl(spi, LTQ_SPI_ID);
	spi->tx_fअगरo_size = (id >> LTQ_SPI_ID_TXFS_S) & hwcfg->fअगरo_size_mask;
	spi->rx_fअगरo_size = (id >> LTQ_SPI_ID_RXFS_S) & hwcfg->fअगरo_size_mask;
	supports_dma = (id & LTQ_SPI_ID_CFG_M) >> LTQ_SPI_ID_CFG_S;
	revision = id & LTQ_SPI_ID_REV_M;

	lantiq_ssc_hw_init(spi);

	dev_info(dev,
		"Lantiq SSC SPI controller (Rev %i, TXFS %u, RXFS %u, DMA %u)\n",
		revision, spi->tx_fअगरo_size, spi->rx_fअगरo_size, supports_dma);

	err = devm_spi_रेजिस्टर_master(dev, master);
	अगर (err) अणु
		dev_err(dev, "failed to register spi_master\n");
		जाओ err_wq_destroy;
	पूर्ण

	वापस 0;

err_wq_destroy:
	destroy_workqueue(spi->wq);
err_clk_put:
	clk_put(spi->fpi_clk);
err_clk_disable:
	clk_disable_unprepare(spi->spi_clk);
err_master_put:
	spi_master_put(master);

	वापस err;
पूर्ण

अटल पूर्णांक lantiq_ssc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lantiq_ssc_spi *spi = platक्रमm_get_drvdata(pdev);

	lantiq_ssc_ग_लिखोl(spi, 0, LTQ_SPI_IRNEN);
	lantiq_ssc_ग_लिखोl(spi, 0, LTQ_SPI_CLC);
	rx_fअगरo_flush(spi);
	tx_fअगरo_flush(spi);
	hw_enter_config_mode(spi);

	destroy_workqueue(spi->wq);
	clk_disable_unprepare(spi->spi_clk);
	clk_put(spi->fpi_clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver lantiq_ssc_driver = अणु
	.probe = lantiq_ssc_probe,
	.हटाओ = lantiq_ssc_हटाओ,
	.driver = अणु
		.name = "spi-lantiq-ssc",
		.of_match_table = lantiq_ssc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lantiq_ssc_driver);

MODULE_DESCRIPTION("Lantiq SSC SPI controller driver");
MODULE_AUTHOR("Daniel Schwierzeck <daniel.schwierzeck@gmail.com>");
MODULE_AUTHOR("Hauke Mehrtens <hauke@hauke-m.de>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:spi-lantiq-ssc");
