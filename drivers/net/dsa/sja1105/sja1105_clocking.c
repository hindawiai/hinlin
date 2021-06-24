<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause
/* Copyright (c) 2016-2018, NXP Semiconductors
 * Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश <linux/packing.h>
#समावेश "sja1105.h"

#घोषणा SJA1105_SIZE_CGU_CMD	4

/* Common काष्ठाure क्रम CFG_PAD_MIIx_RX and CFG_PAD_MIIx_TX */
काष्ठा sja1105_cfg_pad_mii अणु
	u64 d32_os;
	u64 d32_ih;
	u64 d32_ipud;
	u64 d10_ih;
	u64 d10_os;
	u64 d10_ipud;
	u64 ctrl_os;
	u64 ctrl_ih;
	u64 ctrl_ipud;
	u64 clk_os;
	u64 clk_ih;
	u64 clk_ipud;
पूर्ण;

काष्ठा sja1105_cfg_pad_mii_id अणु
	u64 rxc_stable_ovr;
	u64 rxc_delay;
	u64 rxc_bypass;
	u64 rxc_pd;
	u64 txc_stable_ovr;
	u64 txc_delay;
	u64 txc_bypass;
	u64 txc_pd;
पूर्ण;

/* UM10944 Table 82.
 * IDIV_0_C to IDIV_4_C control रेजिस्टरs
 * (addr. 10000Bh to 10000Fh)
 */
काष्ठा sja1105_cgu_iभाग अणु
	u64 clksrc;
	u64 स्वतःblock;
	u64 iभाग;
	u64 pd;
पूर्ण;

/* PLL_1_C control रेजिस्टर
 *
 * SJA1105 E/T: UM10944 Table 81 (address 10000Ah)
 * SJA1105 P/Q/R/S: UM11040 Table 116 (address 10000Ah)
 */
काष्ठा sja1105_cgu_pll_ctrl अणु
	u64 pllclksrc;
	u64 msel;
	u64 स्वतःblock;
	u64 psel;
	u64 direct;
	u64 fbsel;
	u64 bypass;
	u64 pd;
पूर्ण;

क्रमागत अणु
	CLKSRC_MII0_TX_CLK	= 0x00,
	CLKSRC_MII0_RX_CLK	= 0x01,
	CLKSRC_MII1_TX_CLK	= 0x02,
	CLKSRC_MII1_RX_CLK	= 0x03,
	CLKSRC_MII2_TX_CLK	= 0x04,
	CLKSRC_MII2_RX_CLK	= 0x05,
	CLKSRC_MII3_TX_CLK	= 0x06,
	CLKSRC_MII3_RX_CLK	= 0x07,
	CLKSRC_MII4_TX_CLK	= 0x08,
	CLKSRC_MII4_RX_CLK	= 0x09,
	CLKSRC_PLL0		= 0x0B,
	CLKSRC_PLL1		= 0x0E,
	CLKSRC_IDIV0		= 0x11,
	CLKSRC_IDIV1		= 0x12,
	CLKSRC_IDIV2		= 0x13,
	CLKSRC_IDIV3		= 0x14,
	CLKSRC_IDIV4		= 0x15,
पूर्ण;

/* UM10944 Table 83.
 * MIIx घड़ी control रेजिस्टरs 1 to 30
 * (addresses 100013h to 100035h)
 */
काष्ठा sja1105_cgu_mii_ctrl अणु
	u64 clksrc;
	u64 स्वतःblock;
	u64 pd;
पूर्ण;

अटल व्योम sja1105_cgu_iभाग_packing(व्योम *buf, काष्ठा sja1105_cgu_iभाग *iभाग,
				     क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = 4;

	sja1105_packing(buf, &iभाग->clksrc,    28, 24, size, op);
	sja1105_packing(buf, &iभाग->स्वतःblock, 11, 11, size, op);
	sja1105_packing(buf, &iभाग->iभाग,       5,  2, size, op);
	sja1105_packing(buf, &iभाग->pd,         0,  0, size, op);
पूर्ण

अटल पूर्णांक sja1105_cgu_iभाग_config(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				   bool enabled, पूर्णांक factor)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा device *dev = priv->ds->dev;
	काष्ठा sja1105_cgu_iभाग iभाग;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;

	अगर (enabled && factor != 1 && factor != 10) अणु
		dev_err(dev, "idiv factor must be 1 or 10\n");
		वापस -दुस्फल;
	पूर्ण

	/* Payload क्रम packed_buf */
	iभाग.clksrc    = 0x0A;            /* 25MHz */
	iभाग.स्वतःblock = 1;               /* Block clk स्वतःmatically */
	iभाग.iभाग      = factor - 1;      /* Divide by 1 or 10 */
	iभाग.pd        = enabled ? 0 : 1; /* Power करोwn? */
	sja1105_cgu_iभाग_packing(packed_buf, &iभाग, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->cgu_iभाग[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल व्योम
sja1105_cgu_mii_control_packing(व्योम *buf, काष्ठा sja1105_cgu_mii_ctrl *cmd,
				क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = 4;

	sja1105_packing(buf, &cmd->clksrc,    28, 24, size, op);
	sja1105_packing(buf, &cmd->स्वतःblock, 11, 11, size, op);
	sja1105_packing(buf, &cmd->pd,         0,  0, size, op);
पूर्ण

अटल पूर्णांक sja1105_cgu_mii_tx_clk_config(काष्ठा sja1105_निजी *priv,
					 पूर्णांक port, sja1105_mii_role_t role)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl mii_tx_clk;
	स्थिर पूर्णांक mac_clk_sources[] = अणु
		CLKSRC_MII0_TX_CLK,
		CLKSRC_MII1_TX_CLK,
		CLKSRC_MII2_TX_CLK,
		CLKSRC_MII3_TX_CLK,
		CLKSRC_MII4_TX_CLK,
	पूर्ण;
	स्थिर पूर्णांक phy_clk_sources[] = अणु
		CLKSRC_IDIV0,
		CLKSRC_IDIV1,
		CLKSRC_IDIV2,
		CLKSRC_IDIV3,
		CLKSRC_IDIV4,
	पूर्ण;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	पूर्णांक clksrc;

	अगर (role == XMII_MAC)
		clksrc = mac_clk_sources[port];
	अन्यथा
		clksrc = phy_clk_sources[port];

	/* Payload क्रम packed_buf */
	mii_tx_clk.clksrc    = clksrc;
	mii_tx_clk.स्वतःblock = 1;  /* Autoblock clk जबतक changing clksrc */
	mii_tx_clk.pd        = 0;  /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &mii_tx_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->mii_tx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक
sja1105_cgu_mii_rx_clk_config(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl mii_rx_clk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक clk_sources[] = अणु
		CLKSRC_MII0_RX_CLK,
		CLKSRC_MII1_RX_CLK,
		CLKSRC_MII2_RX_CLK,
		CLKSRC_MII3_RX_CLK,
		CLKSRC_MII4_RX_CLK,
	पूर्ण;

	/* Payload क्रम packed_buf */
	mii_rx_clk.clksrc    = clk_sources[port];
	mii_rx_clk.स्वतःblock = 1;  /* Autoblock clk जबतक changing clksrc */
	mii_rx_clk.pd        = 0;  /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &mii_rx_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->mii_rx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक
sja1105_cgu_mii_ext_tx_clk_config(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl mii_ext_tx_clk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक clk_sources[] = अणु
		CLKSRC_IDIV0,
		CLKSRC_IDIV1,
		CLKSRC_IDIV2,
		CLKSRC_IDIV3,
		CLKSRC_IDIV4,
	पूर्ण;

	/* Payload क्रम packed_buf */
	mii_ext_tx_clk.clksrc    = clk_sources[port];
	mii_ext_tx_clk.स्वतःblock = 1; /* Autoblock clk जबतक changing clksrc */
	mii_ext_tx_clk.pd        = 0; /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &mii_ext_tx_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->mii_ext_tx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक
sja1105_cgu_mii_ext_rx_clk_config(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl mii_ext_rx_clk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक clk_sources[] = अणु
		CLKSRC_IDIV0,
		CLKSRC_IDIV1,
		CLKSRC_IDIV2,
		CLKSRC_IDIV3,
		CLKSRC_IDIV4,
	पूर्ण;

	/* Payload क्रम packed_buf */
	mii_ext_rx_clk.clksrc    = clk_sources[port];
	mii_ext_rx_clk.स्वतःblock = 1; /* Autoblock clk जबतक changing clksrc */
	mii_ext_rx_clk.pd        = 0; /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &mii_ext_rx_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->mii_ext_rx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक sja1105_mii_घड़ीing_setup(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				      sja1105_mii_role_t role)
अणु
	काष्ठा device *dev = priv->ds->dev;
	पूर्णांक rc;

	dev_dbg(dev, "Configuring MII-%s clocking\n",
		(role == XMII_MAC) ? "MAC" : "PHY");
	/* If role is MAC, disable IDIV
	 * If role is PHY, enable IDIV and configure क्रम 1/1 भागider
	 */
	rc = sja1105_cgu_iभाग_config(priv, port, (role == XMII_PHY), 1);
	अगर (rc < 0)
		वापस rc;

	/* Configure CLKSRC of MII_TX_CLK_n
	 *   * If role is MAC, select TX_CLK_n
	 *   * If role is PHY, select IDIV_n
	 */
	rc = sja1105_cgu_mii_tx_clk_config(priv, port, role);
	अगर (rc < 0)
		वापस rc;

	/* Configure CLKSRC of MII_RX_CLK_n
	 * Select RX_CLK_n
	 */
	rc = sja1105_cgu_mii_rx_clk_config(priv, port);
	अगर (rc < 0)
		वापस rc;

	अगर (role == XMII_PHY) अणु
		/* Per MII spec, the PHY (which is us) drives the TX_CLK pin */

		/* Configure CLKSRC of EXT_TX_CLK_n
		 * Select IDIV_n
		 */
		rc = sja1105_cgu_mii_ext_tx_clk_config(priv, port);
		अगर (rc < 0)
			वापस rc;

		/* Configure CLKSRC of EXT_RX_CLK_n
		 * Select IDIV_n
		 */
		rc = sja1105_cgu_mii_ext_rx_clk_config(priv, port);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
sja1105_cgu_pll_control_packing(व्योम *buf, काष्ठा sja1105_cgu_pll_ctrl *cmd,
				क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = 4;

	sja1105_packing(buf, &cmd->pllclksrc, 28, 24, size, op);
	sja1105_packing(buf, &cmd->msel,      23, 16, size, op);
	sja1105_packing(buf, &cmd->स्वतःblock, 11, 11, size, op);
	sja1105_packing(buf, &cmd->psel,       9,  8, size, op);
	sja1105_packing(buf, &cmd->direct,     7,  7, size, op);
	sja1105_packing(buf, &cmd->fbsel,      6,  6, size, op);
	sja1105_packing(buf, &cmd->bypass,     1,  1, size, op);
	sja1105_packing(buf, &cmd->pd,         0,  0, size, op);
पूर्ण

अटल पूर्णांक sja1105_cgu_rgmii_tx_clk_config(काष्ठा sja1105_निजी *priv,
					   पूर्णांक port, sja1105_speed_t speed)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl txc;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	पूर्णांक clksrc;

	अगर (speed == SJA1105_SPEED_1000MBPS) अणु
		clksrc = CLKSRC_PLL0;
	पूर्ण अन्यथा अणु
		पूर्णांक clk_sources[] = अणुCLKSRC_IDIV0, CLKSRC_IDIV1, CLKSRC_IDIV2,
				     CLKSRC_IDIV3, CLKSRC_IDIV4पूर्ण;
		clksrc = clk_sources[port];
	पूर्ण

	/* RGMII: 125MHz क्रम 1000, 25MHz क्रम 100, 2.5MHz क्रम 10 */
	txc.clksrc = clksrc;
	/* Autoblock clk जबतक changing clksrc */
	txc.स्वतःblock = 1;
	/* Power Down off => enabled */
	txc.pd = 0;
	sja1105_cgu_mii_control_packing(packed_buf, &txc, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->rgmii_tx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

/* AGU */
अटल व्योम
sja1105_cfg_pad_mii_packing(व्योम *buf, काष्ठा sja1105_cfg_pad_mii *cmd,
			    क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = 4;

	sja1105_packing(buf, &cmd->d32_os,   28, 27, size, op);
	sja1105_packing(buf, &cmd->d32_ih,   26, 26, size, op);
	sja1105_packing(buf, &cmd->d32_ipud, 25, 24, size, op);
	sja1105_packing(buf, &cmd->d10_os,   20, 19, size, op);
	sja1105_packing(buf, &cmd->d10_ih,   18, 18, size, op);
	sja1105_packing(buf, &cmd->d10_ipud, 17, 16, size, op);
	sja1105_packing(buf, &cmd->ctrl_os,  12, 11, size, op);
	sja1105_packing(buf, &cmd->ctrl_ih,  10, 10, size, op);
	sja1105_packing(buf, &cmd->ctrl_ipud, 9,  8, size, op);
	sja1105_packing(buf, &cmd->clk_os,    4,  3, size, op);
	sja1105_packing(buf, &cmd->clk_ih,    2,  2, size, op);
	sja1105_packing(buf, &cmd->clk_ipud,  1,  0, size, op);
पूर्ण

अटल पूर्णांक sja1105_rgmii_cfg_pad_tx_config(काष्ठा sja1105_निजी *priv,
					   पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cfg_pad_mii pad_mii_tx = अणु0पूर्ण;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;

	/* Payload */
	pad_mii_tx.d32_os    = 3; /* TXD[3:2] output stage: */
				  /*          high noise/high speed */
	pad_mii_tx.d10_os    = 3; /* TXD[1:0] output stage: */
				  /*          high noise/high speed */
	pad_mii_tx.d32_ipud  = 2; /* TXD[3:2] input stage: */
				  /*          plain input (शेष) */
	pad_mii_tx.d10_ipud  = 2; /* TXD[1:0] input stage: */
				  /*          plain input (शेष) */
	pad_mii_tx.ctrl_os   = 3; /* TX_CTL / TX_ER output stage */
	pad_mii_tx.ctrl_ipud = 2; /* TX_CTL / TX_ER input stage (शेष) */
	pad_mii_tx.clk_os    = 3; /* TX_CLK output stage */
	pad_mii_tx.clk_ih    = 0; /* TX_CLK input hysteresis (शेष) */
	pad_mii_tx.clk_ipud  = 2; /* TX_CLK input stage (शेष) */
	sja1105_cfg_pad_mii_packing(packed_buf, &pad_mii_tx, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->pad_mii_tx[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक sja1105_cfg_pad_rx_config(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cfg_pad_mii pad_mii_rx = अणु0पूर्ण;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;

	/* Payload */
	pad_mii_rx.d32_ih    = 0; /* RXD[3:2] input stage hysteresis: */
				  /*          non-Schmitt (शेष) */
	pad_mii_rx.d32_ipud  = 2; /* RXD[3:2] input weak pull-up/करोwn */
				  /*          plain input (शेष) */
	pad_mii_rx.d10_ih    = 0; /* RXD[1:0] input stage hysteresis: */
				  /*          non-Schmitt (शेष) */
	pad_mii_rx.d10_ipud  = 2; /* RXD[1:0] input weak pull-up/करोwn */
				  /*          plain input (शेष) */
	pad_mii_rx.ctrl_ih   = 0; /* RX_DV/CRS_DV/RX_CTL and RX_ER */
				  /* input stage hysteresis: */
				  /* non-Schmitt (शेष) */
	pad_mii_rx.ctrl_ipud = 3; /* RX_DV/CRS_DV/RX_CTL and RX_ER */
				  /* input stage weak pull-up/करोwn: */
				  /* pull-करोwn */
	pad_mii_rx.clk_os    = 2; /* RX_CLK/RXC output stage: */
				  /* medium noise/fast speed (शेष) */
	pad_mii_rx.clk_ih    = 0; /* RX_CLK/RXC input hysteresis: */
				  /* non-Schmitt (शेष) */
	pad_mii_rx.clk_ipud  = 2; /* RX_CLK/RXC input pull-up/करोwn: */
				  /* plain input (शेष) */
	sja1105_cfg_pad_mii_packing(packed_buf, &pad_mii_rx, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->pad_mii_rx[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल व्योम
sja1105_cfg_pad_mii_id_packing(व्योम *buf, काष्ठा sja1105_cfg_pad_mii_id *cmd,
			       क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_CGU_CMD;

	sja1105_packing(buf, &cmd->rxc_stable_ovr, 15, 15, size, op);
	sja1105_packing(buf, &cmd->rxc_delay,      14, 10, size, op);
	sja1105_packing(buf, &cmd->rxc_bypass,      9,  9, size, op);
	sja1105_packing(buf, &cmd->rxc_pd,          8,  8, size, op);
	sja1105_packing(buf, &cmd->txc_stable_ovr,  7,  7, size, op);
	sja1105_packing(buf, &cmd->txc_delay,       6,  2, size, op);
	sja1105_packing(buf, &cmd->txc_bypass,      1,  1, size, op);
	sja1105_packing(buf, &cmd->txc_pd,          0,  0, size, op);
पूर्ण

/* Valid range in degrees is an पूर्णांकeger between 73.8 and 101.7 */
अटल u64 sja1105_rgmii_delay(u64 phase)
अणु
	/* UM11040.pdf: The delay in degree phase is 73.8 + delay_tune * 0.9.
	 * To aव्योम भग्नing poपूर्णांक operations we'll multiply by 10
	 * and get 1 decimal poपूर्णांक precision.
	 */
	phase *= 10;
	वापस (phase - 738) / 9;
पूर्ण

/* The RGMII delay setup procedure is 2-step and माला_लो called upon each
 * .phylink_mac_config. Both are strategic.
 * The reason is that the RX Tunable Delay Line of the SJA1105 MAC has issues
 * with recovering from a frequency change of the link partner's RGMII घड़ी.
 * The easiest way to recover from this is to temporarily घातer करोwn the TDL,
 * as it will re-lock at the new frequency afterwards.
 */
पूर्णांक sja1105pqrs_setup_rgmii_delay(स्थिर व्योम *ctx, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_निजी *priv = ctx;
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cfg_pad_mii_id pad_mii_id = अणु0पूर्ण;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (priv->rgmii_rx_delay[port])
		pad_mii_id.rxc_delay = sja1105_rgmii_delay(90);
	अगर (priv->rgmii_tx_delay[port])
		pad_mii_id.txc_delay = sja1105_rgmii_delay(90);

	/* Stage 1: Turn the RGMII delay lines off. */
	pad_mii_id.rxc_bypass = 1;
	pad_mii_id.rxc_pd = 1;
	pad_mii_id.txc_bypass = 1;
	pad_mii_id.txc_pd = 1;
	sja1105_cfg_pad_mii_id_packing(packed_buf, &pad_mii_id, PACK);

	rc = sja1105_xfer_buf(priv, SPI_WRITE, regs->pad_mii_id[port],
			      packed_buf, SJA1105_SIZE_CGU_CMD);
	अगर (rc < 0)
		वापस rc;

	/* Stage 2: Turn the RGMII delay lines on. */
	अगर (priv->rgmii_rx_delay[port]) अणु
		pad_mii_id.rxc_bypass = 0;
		pad_mii_id.rxc_pd = 0;
	पूर्ण
	अगर (priv->rgmii_tx_delay[port]) अणु
		pad_mii_id.txc_bypass = 0;
		pad_mii_id.txc_pd = 0;
	पूर्ण
	sja1105_cfg_pad_mii_id_packing(packed_buf, &pad_mii_id, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->pad_mii_id[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक sja1105_rgmii_घड़ीing_setup(काष्ठा sja1105_निजी *priv, पूर्णांक port,
					sja1105_mii_role_t role)
अणु
	काष्ठा device *dev = priv->ds->dev;
	काष्ठा sja1105_mac_config_entry *mac;
	sja1105_speed_t speed;
	पूर्णांक rc;

	mac = priv->अटल_config.tables[BLK_IDX_MAC_CONFIG].entries;
	speed = mac[port].speed;

	dev_dbg(dev, "Configuring port %d RGMII at speed %dMbps\n",
		port, speed);

	चयन (speed) अणु
	हाल SJA1105_SPEED_1000MBPS:
		/* 1000Mbps, IDIV disabled (125 MHz) */
		rc = sja1105_cgu_iभाग_config(priv, port, false, 1);
		अवरोध;
	हाल SJA1105_SPEED_100MBPS:
		/* 100Mbps, IDIV enabled, भागide by 1 (25 MHz) */
		rc = sja1105_cgu_iभाग_config(priv, port, true, 1);
		अवरोध;
	हाल SJA1105_SPEED_10MBPS:
		/* 10Mbps, IDIV enabled, भागide by 10 (2.5 MHz) */
		rc = sja1105_cgu_iभाग_config(priv, port, true, 10);
		अवरोध;
	हाल SJA1105_SPEED_AUTO:
		/* Skip CGU configuration अगर there is no speed available
		 * (e.g. link is not established yet)
		 */
		dev_dbg(dev, "Speed not available, skipping CGU config\n");
		वापस 0;
	शेष:
		rc = -EINVAL;
	पूर्ण

	अगर (rc < 0) अणु
		dev_err(dev, "Failed to configure idiv\n");
		वापस rc;
	पूर्ण
	rc = sja1105_cgu_rgmii_tx_clk_config(priv, port, speed);
	अगर (rc < 0) अणु
		dev_err(dev, "Failed to configure RGMII Tx clock\n");
		वापस rc;
	पूर्ण
	rc = sja1105_rgmii_cfg_pad_tx_config(priv, port);
	अगर (rc < 0) अणु
		dev_err(dev, "Failed to configure Tx pad registers\n");
		वापस rc;
	पूर्ण
	अगर (!priv->info->setup_rgmii_delay)
		वापस 0;
	/* The role has no hardware effect क्रम RGMII. However we use it as
	 * a proxy क्रम this पूर्णांकerface being a MAC-to-MAC connection, with
	 * the RGMII पूर्णांकernal delays needing to be applied by us.
	 */
	अगर (role == XMII_MAC)
		वापस 0;

	वापस priv->info->setup_rgmii_delay(priv, port);
पूर्ण

अटल पूर्णांक sja1105_cgu_rmii_ref_clk_config(काष्ठा sja1105_निजी *priv,
					   पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl ref_clk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	स्थिर पूर्णांक clk_sources[] = अणु
		CLKSRC_MII0_TX_CLK,
		CLKSRC_MII1_TX_CLK,
		CLKSRC_MII2_TX_CLK,
		CLKSRC_MII3_TX_CLK,
		CLKSRC_MII4_TX_CLK,
	पूर्ण;

	/* Payload क्रम packed_buf */
	ref_clk.clksrc    = clk_sources[port];
	ref_clk.स्वतःblock = 1;      /* Autoblock clk जबतक changing clksrc */
	ref_clk.pd        = 0;      /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &ref_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->rmii_ref_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक
sja1105_cgu_rmii_ext_tx_clk_config(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	काष्ठा sja1105_cgu_mii_ctrl ext_tx_clk;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;

	/* Payload क्रम packed_buf */
	ext_tx_clk.clksrc    = CLKSRC_PLL1;
	ext_tx_clk.स्वतःblock = 1;   /* Autoblock clk जबतक changing clksrc */
	ext_tx_clk.pd        = 0;   /* Power Down off => enabled */
	sja1105_cgu_mii_control_packing(packed_buf, &ext_tx_clk, PACK);

	वापस sja1105_xfer_buf(priv, SPI_WRITE, regs->rmii_ext_tx_clk[port],
				packed_buf, SJA1105_SIZE_CGU_CMD);
पूर्ण

अटल पूर्णांक sja1105_cgu_rmii_pll_config(काष्ठा sja1105_निजी *priv)
अणु
	स्थिर काष्ठा sja1105_regs *regs = priv->info->regs;
	u8 packed_buf[SJA1105_SIZE_CGU_CMD] = अणु0पूर्ण;
	काष्ठा sja1105_cgu_pll_ctrl pll = अणु0पूर्ण;
	काष्ठा device *dev = priv->ds->dev;
	पूर्णांक rc;

	/* PLL1 must be enabled and output 50 Mhz.
	 * This is करोne by writing first 0x0A010941 to
	 * the PLL_1_C रेजिस्टर and then deनिश्चितing
	 * घातer करोwn (PD) 0x0A010940.
	 */

	/* Step 1: PLL1 setup क्रम 50Mhz */
	pll.pllclksrc = 0xA;
	pll.msel      = 0x1;
	pll.स्वतःblock = 0x1;
	pll.psel      = 0x1;
	pll.direct    = 0x0;
	pll.fbsel     = 0x1;
	pll.bypass    = 0x0;
	pll.pd        = 0x1;

	sja1105_cgu_pll_control_packing(packed_buf, &pll, PACK);
	rc = sja1105_xfer_buf(priv, SPI_WRITE, regs->rmii_pll1, packed_buf,
			      SJA1105_SIZE_CGU_CMD);
	अगर (rc < 0) अणु
		dev_err(dev, "failed to configure PLL1 for 50MHz\n");
		वापस rc;
	पूर्ण

	/* Step 2: Enable PLL1 */
	pll.pd = 0x0;

	sja1105_cgu_pll_control_packing(packed_buf, &pll, PACK);
	rc = sja1105_xfer_buf(priv, SPI_WRITE, regs->rmii_pll1, packed_buf,
			      SJA1105_SIZE_CGU_CMD);
	अगर (rc < 0) अणु
		dev_err(dev, "failed to enable PLL1\n");
		वापस rc;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक sja1105_rmii_घड़ीing_setup(काष्ठा sja1105_निजी *priv, पूर्णांक port,
				       sja1105_mii_role_t role)
अणु
	काष्ठा device *dev = priv->ds->dev;
	पूर्णांक rc;

	dev_dbg(dev, "Configuring RMII-%s clocking\n",
		(role == XMII_MAC) ? "MAC" : "PHY");
	/* AH1601.pdf chapter 2.5.1. Sources */
	अगर (role == XMII_MAC) अणु
		/* Configure and enable PLL1 क्रम 50Mhz output */
		rc = sja1105_cgu_rmii_pll_config(priv);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	/* Disable IDIV क्रम this port */
	rc = sja1105_cgu_iभाग_config(priv, port, false, 1);
	अगर (rc < 0)
		वापस rc;
	/* Source to sink mappings */
	rc = sja1105_cgu_rmii_ref_clk_config(priv, port);
	अगर (rc < 0)
		वापस rc;
	अगर (role == XMII_MAC) अणु
		rc = sja1105_cgu_rmii_ext_tx_clk_config(priv, port);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक sja1105_घड़ीing_setup_port(काष्ठा sja1105_निजी *priv, पूर्णांक port)
अणु
	काष्ठा sja1105_xmii_params_entry *mii;
	काष्ठा device *dev = priv->ds->dev;
	sja1105_phy_पूर्णांकerface_t phy_mode;
	sja1105_mii_role_t role;
	पूर्णांक rc;

	mii = priv->अटल_config.tables[BLK_IDX_XMII_PARAMS].entries;

	/* RGMII etc */
	phy_mode = mii->xmii_mode[port];
	/* MAC or PHY, क्रम applicable types (not RGMII) */
	role = mii->phy_mac[port];

	चयन (phy_mode) अणु
	हाल XMII_MODE_MII:
		rc = sja1105_mii_घड़ीing_setup(priv, port, role);
		अवरोध;
	हाल XMII_MODE_RMII:
		rc = sja1105_rmii_घड़ीing_setup(priv, port, role);
		अवरोध;
	हाल XMII_MODE_RGMII:
		rc = sja1105_rgmii_घड़ीing_setup(priv, port, role);
		अवरोध;
	हाल XMII_MODE_SGMII:
		/* Nothing to करो in the CGU क्रम SGMII */
		rc = 0;
		अवरोध;
	शेष:
		dev_err(dev, "Invalid interface mode specified: %d\n",
			phy_mode);
		वापस -EINVAL;
	पूर्ण
	अगर (rc) अणु
		dev_err(dev, "Clocking setup for port %d failed: %d\n",
			port, rc);
		वापस rc;
	पूर्ण

	/* Internally pull करोwn the RX_DV/CRS_DV/RX_CTL and RX_ER inमाला_दो */
	वापस sja1105_cfg_pad_rx_config(priv, port);
पूर्ण

पूर्णांक sja1105_घड़ीing_setup(काष्ठा sja1105_निजी *priv)
अणु
	पूर्णांक port, rc;

	क्रम (port = 0; port < SJA1105_NUM_PORTS; port++) अणु
		rc = sja1105_घड़ीing_setup_port(priv, port);
		अगर (rc < 0)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण
