<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2011 Solarflare Communications Inc.
 */

/*
 * Driver क्रम Tranचयन/Mysticom CX4 reसमयr
 * see www.tranचयन.com, part is TXC-43128
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश "efx.h"
#समावेश "mdio_10g.h"
#समावेश "phy.h"
#समावेश "nic.h"

/* We expect these MMDs to be in the package */
#घोषणा TXC_REQUIRED_DEVS (MDIO_DEVS_PCS |	\
			   MDIO_DEVS_PMAPMD |	\
			   MDIO_DEVS_PHYXS)

#घोषणा TXC_LOOPBACKS ((1 << LOOPBACK_PCS) |	\
		       (1 << LOOPBACK_PMAPMD) |	\
		       (1 << LOOPBACK_PHYXS_WS))

/**************************************************************************
 *
 * Compile-समय config
 *
 **************************************************************************
 */
#घोषणा TXCNAME "TXC43128"
/* Total length of समय we'll रुको क्रम the PHY to come out of reset (ms) */
#घोषणा TXC_MAX_RESET_TIME	500
/* Interval between checks (ms) */
#घोषणा TXC_RESET_WAIT		10
/* How दीर्घ to run BIST (us) */
#घोषणा TXC_BIST_DURATION	50

/**************************************************************************
 *
 * Register definitions
 *
 **************************************************************************
 */

/* Command रेजिस्टर */
#घोषणा TXC_GLRGS_GLCMD		0xc004
/* Useful bits in command रेजिस्टर */
/* Lane घातer-करोwn */
#घोषणा TXC_GLCMD_L01PD_LBN	5
#घोषणा TXC_GLCMD_L23PD_LBN	6
/* Limited SW reset: preserves configuration but
 * initiates a logic reset. Self-clearing */
#घोषणा TXC_GLCMD_LMTSWRST_LBN	14

/* Signal Quality Control */
#घोषणा TXC_GLRGS_GSGQLCTL	0xc01a
/* Enable bit */
#घोषणा TXC_GSGQLCT_SGQLEN_LBN	15
/* Lane selection */
#घोषणा TXC_GSGQLCT_LNSL_LBN	13
#घोषणा TXC_GSGQLCT_LNSL_WIDTH	2

/* Analog TX control */
#घोषणा TXC_ALRGS_ATXCTL	0xc040
/* Lane घातer-करोwn */
#घोषणा TXC_ATXCTL_TXPD3_LBN	15
#घोषणा TXC_ATXCTL_TXPD2_LBN	14
#घोषणा TXC_ATXCTL_TXPD1_LBN	13
#घोषणा TXC_ATXCTL_TXPD0_LBN	12

/* Amplitude on lanes 0, 1 */
#घोषणा TXC_ALRGS_ATXAMP0	0xc041
/* Amplitude on lanes 2, 3 */
#घोषणा TXC_ALRGS_ATXAMP1	0xc042
/* Bit position of value क्रम lane 0 (or 2) */
#घोषणा TXC_ATXAMP_LANE02_LBN	3
/* Bit position of value क्रम lane 1 (or 3) */
#घोषणा TXC_ATXAMP_LANE13_LBN	11

#घोषणा TXC_ATXAMP_1280_mV	0
#घोषणा TXC_ATXAMP_1200_mV	8
#घोषणा TXC_ATXAMP_1120_mV	12
#घोषणा TXC_ATXAMP_1060_mV	14
#घोषणा TXC_ATXAMP_0820_mV	25
#घोषणा TXC_ATXAMP_0720_mV	26
#घोषणा TXC_ATXAMP_0580_mV	27
#घोषणा TXC_ATXAMP_0440_mV	28

#घोषणा TXC_ATXAMP_0820_BOTH					\
	((TXC_ATXAMP_0820_mV << TXC_ATXAMP_LANE02_LBN)		\
	 | (TXC_ATXAMP_0820_mV << TXC_ATXAMP_LANE13_LBN))

#घोषणा TXC_ATXAMP_DEFAULT	0x6060 /* From databook */

/* Preemphasis on lanes 0, 1 */
#घोषणा TXC_ALRGS_ATXPRE0	0xc043
/* Preemphasis on lanes 2, 3 */
#घोषणा TXC_ALRGS_ATXPRE1	0xc044

#घोषणा TXC_ATXPRE_NONE 0
#घोषणा TXC_ATXPRE_DEFAULT	0x1010 /* From databook */

#घोषणा TXC_ALRGS_ARXCTL	0xc045
/* Lane घातer-करोwn */
#घोषणा TXC_ARXCTL_RXPD3_LBN	15
#घोषणा TXC_ARXCTL_RXPD2_LBN	14
#घोषणा TXC_ARXCTL_RXPD1_LBN	13
#घोषणा TXC_ARXCTL_RXPD0_LBN	12

/* Main control */
#घोषणा TXC_MRGS_CTL		0xc340
/* Bits in मुख्य control */
#घोषणा TXC_MCTL_RESET_LBN	15	/* Self clear */
#घोषणा TXC_MCTL_TXLED_LBN	14	/* 1 to show align status */
#घोषणा TXC_MCTL_RXLED_LBN	13	/* 1 to show align status */

/* GPIO output */
#घोषणा TXC_GPIO_OUTPUT		0xc346
#घोषणा TXC_GPIO_सूची		0xc348

/* Venकरोr-specअगरic BIST रेजिस्टरs */
#घोषणा TXC_BIST_CTL		0xc280
#घोषणा TXC_BIST_TXFRMCNT	0xc281
#घोषणा TXC_BIST_RX0FRMCNT	0xc282
#घोषणा TXC_BIST_RX1FRMCNT	0xc283
#घोषणा TXC_BIST_RX2FRMCNT	0xc284
#घोषणा TXC_BIST_RX3FRMCNT	0xc285
#घोषणा TXC_BIST_RX0ERRCNT	0xc286
#घोषणा TXC_BIST_RX1ERRCNT	0xc287
#घोषणा TXC_BIST_RX2ERRCNT	0xc288
#घोषणा TXC_BIST_RX3ERRCNT	0xc289

/* BIST type (controls bit patter in test) */
#घोषणा TXC_BIST_CTRL_TYPE_LBN	10
#घोषणा TXC_BIST_CTRL_TYPE_TSD	0	/* TranSwitch Deterministic */
#घोषणा TXC_BIST_CTRL_TYPE_CRP	1	/* CRPAT standard */
#घोषणा TXC_BIST_CTRL_TYPE_CJP	2	/* CJPAT standard */
#घोषणा TXC_BIST_CTRL_TYPE_TSR	3	/* TranSwitch pseuकरो-अक्रमom */
/* Set this to 1 क्रम 10 bit and 0 क्रम 8 bit */
#घोषणा TXC_BIST_CTRL_B10EN_LBN	12
/* Enable BIST (ग_लिखो 0 to disable) */
#घोषणा TXC_BIST_CTRL_ENAB_LBN	13
/* Stop BIST (self-clears when stop complete) */
#घोषणा TXC_BIST_CTRL_STOP_LBN	14
/* Start BIST (cleared by writing 1 to STOP) */
#घोषणा TXC_BIST_CTRL_STRT_LBN	15

/* Mt. Diablo test configuration */
#घोषणा TXC_MTDIABLO_CTRL	0xc34f
#घोषणा TXC_MTDIABLO_CTRL_PMA_LOOP_LBN	10

काष्ठा txc43128_data अणु
	अचिन्हित दीर्घ bug10934_समयr;
	क्रमागत ef4_phy_mode phy_mode;
	क्रमागत ef4_loopback_mode loopback_mode;
पूर्ण;

/* The PHY someबार needs a reset to bring the link back up.  So दीर्घ as
 * it reports link करोwn, we reset it every 5 seconds.
 */
#घोषणा BUG10934_RESET_INTERVAL (5 * HZ)

/* Perक्रमm a reset that करोesn't clear configuration changes */
अटल व्योम txc_reset_logic(काष्ठा ef4_nic *efx);

/* Set the output value of a gpio */
व्योम falcon_txc_set_gpio_val(काष्ठा ef4_nic *efx, पूर्णांक pin, पूर्णांक on)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS, TXC_GPIO_OUTPUT, 1 << pin, on);
पूर्ण

/* Set up the GPIO direction रेजिस्टर */
व्योम falcon_txc_set_gpio_dir(काष्ठा ef4_nic *efx, पूर्णांक pin, पूर्णांक dir)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS, TXC_GPIO_सूची, 1 << pin, dir);
पूर्ण

/* Reset the PMA/PMD MMD. The करोcumentation is explicit that this करोes a
 * global reset (it's less clear what reset of other MMDs करोes).*/
अटल पूर्णांक txc_reset_phy(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc = ef4_mdio_reset_mmd(efx, MDIO_MMD_PMAPMD,
				    TXC_MAX_RESET_TIME / TXC_RESET_WAIT,
				    TXC_RESET_WAIT);
	अगर (rc < 0)
		जाओ fail;

	/* Check that all the MMDs we expect are present and responding. */
	rc = ef4_mdio_check_mmds(efx, TXC_REQUIRED_DEVS);
	अगर (rc < 0)
		जाओ fail;

	वापस 0;

fail:
	netअगर_err(efx, hw, efx->net_dev, TXCNAME ": reset timed out!\n");
	वापस rc;
पूर्ण

/* Run a single BIST on one MMD */
अटल पूर्णांक txc_bist_one(काष्ठा ef4_nic *efx, पूर्णांक mmd, पूर्णांक test)
अणु
	पूर्णांक ctrl, bctl;
	पूर्णांक lane;
	पूर्णांक rc = 0;

	/* Set PMA to test पूर्णांकo loopback using Mt Diablo reg as per app note */
	ctrl = ef4_mdio_पढ़ो(efx, MDIO_MMD_PCS, TXC_MTDIABLO_CTRL);
	ctrl |= (1 << TXC_MTDIABLO_CTRL_PMA_LOOP_LBN);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PCS, TXC_MTDIABLO_CTRL, ctrl);

	/* The BIST app. note lists these  as 3 distinct steps. */
	/* Set the BIST type */
	bctl = (test << TXC_BIST_CTRL_TYPE_LBN);
	ef4_mdio_ग_लिखो(efx, mmd, TXC_BIST_CTL, bctl);

	/* Set the BSTEN bit in the BIST Control रेजिस्टर to enable */
	bctl |= (1 << TXC_BIST_CTRL_ENAB_LBN);
	ef4_mdio_ग_लिखो(efx, mmd, TXC_BIST_CTL, bctl);

	/* Set the BSTRT bit in the BIST Control रेजिस्टर */
	ef4_mdio_ग_लिखो(efx, mmd, TXC_BIST_CTL,
		       bctl | (1 << TXC_BIST_CTRL_STRT_LBN));

	/* Wait. */
	udelay(TXC_BIST_DURATION);

	/* Set the BSTOP bit in the BIST Control रेजिस्टर */
	bctl |= (1 << TXC_BIST_CTRL_STOP_LBN);
	ef4_mdio_ग_लिखो(efx, mmd, TXC_BIST_CTL, bctl);

	/* The STOP bit should go off when things have stopped */
	जबतक (bctl & (1 << TXC_BIST_CTRL_STOP_LBN))
		bctl = ef4_mdio_पढ़ो(efx, mmd, TXC_BIST_CTL);

	/* Check all the error counts are 0 and all the frame counts are
	   non-zero */
	क्रम (lane = 0; lane < 4; lane++) अणु
		पूर्णांक count = ef4_mdio_पढ़ो(efx, mmd, TXC_BIST_RX0ERRCNT + lane);
		अगर (count != 0) अणु
			netअगर_err(efx, hw, efx->net_dev, TXCNAME": BIST error. "
				  "Lane %d had %d errs\n", lane, count);
			rc = -EIO;
		पूर्ण
		count = ef4_mdio_पढ़ो(efx, mmd, TXC_BIST_RX0FRMCNT + lane);
		अगर (count == 0) अणु
			netअगर_err(efx, hw, efx->net_dev, TXCNAME": BIST error. "
				  "Lane %d got 0 frames\n", lane);
			rc = -EIO;
		पूर्ण
	पूर्ण

	अगर (rc == 0)
		netअगर_info(efx, hw, efx->net_dev, TXCNAME": BIST pass\n");

	/* Disable BIST */
	ef4_mdio_ग_लिखो(efx, mmd, TXC_BIST_CTL, 0);

	/* Turn off loopback */
	ctrl &= ~(1 << TXC_MTDIABLO_CTRL_PMA_LOOP_LBN);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PCS, TXC_MTDIABLO_CTRL, ctrl);

	वापस rc;
पूर्ण

अटल पूर्णांक txc_bist(काष्ठा ef4_nic *efx)
अणु
	वापस txc_bist_one(efx, MDIO_MMD_PCS, TXC_BIST_CTRL_TYPE_TSD);
पूर्ण

/* Push the non-configurable शेषs पूर्णांकo the PHY. This must be
 * करोne after every full reset */
अटल व्योम txc_apply_शेषs(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक mctrl;

	/* Turn amplitude करोwn and preemphasis off on the host side
	 * (PHY<->MAC) as this is believed less likely to upset Falcon
	 * and no adverse effects have been noted. It probably also
	 * saves a picowatt or two */

	/* Turn off preemphasis */
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PHYXS, TXC_ALRGS_ATXPRE0, TXC_ATXPRE_NONE);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PHYXS, TXC_ALRGS_ATXPRE1, TXC_ATXPRE_NONE);

	/* Turn करोwn the amplitude */
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PHYXS,
		       TXC_ALRGS_ATXAMP0, TXC_ATXAMP_0820_BOTH);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PHYXS,
		       TXC_ALRGS_ATXAMP1, TXC_ATXAMP_0820_BOTH);

	/* Set the line side amplitude and preemphasis to the databook
	 * शेषs as an erratum causes them to be 0 on at least some
	 * PHY rev.s */
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXPRE0, TXC_ATXPRE_DEFAULT);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXPRE1, TXC_ATXPRE_DEFAULT);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXAMP0, TXC_ATXAMP_DEFAULT);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD,
		       TXC_ALRGS_ATXAMP1, TXC_ATXAMP_DEFAULT);

	/* Set up the LEDs  */
	mctrl = ef4_mdio_पढ़ो(efx, MDIO_MMD_PHYXS, TXC_MRGS_CTL);

	/* Set the Green and Red LEDs to their शेष modes */
	mctrl &= ~((1 << TXC_MCTL_TXLED_LBN) | (1 << TXC_MCTL_RXLED_LBN));
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PHYXS, TXC_MRGS_CTL, mctrl);

	/* Databook recommends करोing this after configuration changes */
	txc_reset_logic(efx);

	falcon_board(efx)->type->init_phy(efx);
पूर्ण

अटल पूर्णांक txc43128_phy_probe(काष्ठा ef4_nic *efx)
अणु
	काष्ठा txc43128_data *phy_data;

	/* Allocate phy निजी storage */
	phy_data = kzalloc(माप(*phy_data), GFP_KERNEL);
	अगर (!phy_data)
		वापस -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TXC_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;

	efx->loopback_modes = TXC_LOOPBACKS | FALCON_XMAC_LOOPBACKS;

	वापस 0;
पूर्ण

/* Initialisation entry poपूर्णांक क्रम this PHY driver */
अटल पूर्णांक txc43128_phy_init(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	rc = txc_reset_phy(efx);
	अगर (rc < 0)
		वापस rc;

	rc = txc_bist(efx);
	अगर (rc < 0)
		वापस rc;

	txc_apply_शेषs(efx);

	वापस 0;
पूर्ण

/* Set the lane घातer करोwn state in the global रेजिस्टरs */
अटल व्योम txc_glrgs_lane_घातer(काष्ठा ef4_nic *efx, पूर्णांक mmd)
अणु
	पूर्णांक pd = (1 << TXC_GLCMD_L01PD_LBN) | (1 << TXC_GLCMD_L23PD_LBN);
	पूर्णांक ctl = ef4_mdio_पढ़ो(efx, mmd, TXC_GLRGS_GLCMD);

	अगर (!(efx->phy_mode & PHY_MODE_LOW_POWER))
		ctl &= ~pd;
	अन्यथा
		ctl |= pd;

	ef4_mdio_ग_लिखो(efx, mmd, TXC_GLRGS_GLCMD, ctl);
पूर्ण

/* Set the lane घातer करोwn state in the analog control रेजिस्टरs */
अटल व्योम txc_analog_lane_घातer(काष्ठा ef4_nic *efx, पूर्णांक mmd)
अणु
	पूर्णांक txpd = (1 << TXC_ATXCTL_TXPD3_LBN) | (1 << TXC_ATXCTL_TXPD2_LBN)
		| (1 << TXC_ATXCTL_TXPD1_LBN) | (1 << TXC_ATXCTL_TXPD0_LBN);
	पूर्णांक rxpd = (1 << TXC_ARXCTL_RXPD3_LBN) | (1 << TXC_ARXCTL_RXPD2_LBN)
		| (1 << TXC_ARXCTL_RXPD1_LBN) | (1 << TXC_ARXCTL_RXPD0_LBN);
	पूर्णांक txctl = ef4_mdio_पढ़ो(efx, mmd, TXC_ALRGS_ATXCTL);
	पूर्णांक rxctl = ef4_mdio_पढ़ो(efx, mmd, TXC_ALRGS_ARXCTL);

	अगर (!(efx->phy_mode & PHY_MODE_LOW_POWER)) अणु
		txctl &= ~txpd;
		rxctl &= ~rxpd;
	पूर्ण अन्यथा अणु
		txctl |= txpd;
		rxctl |= rxpd;
	पूर्ण

	ef4_mdio_ग_लिखो(efx, mmd, TXC_ALRGS_ATXCTL, txctl);
	ef4_mdio_ग_लिखो(efx, mmd, TXC_ALRGS_ARXCTL, rxctl);
पूर्ण

अटल व्योम txc_set_घातer(काष्ठा ef4_nic *efx)
अणु
	/* According to the data book, all the MMDs can करो low घातer */
	ef4_mdio_set_mmds_lघातer(efx,
				 !!(efx->phy_mode & PHY_MODE_LOW_POWER),
				 TXC_REQUIRED_DEVS);

	/* Global रेजिस्टर bank is in PCS, PHY XS. These control the host
	 * side and line side settings respectively. */
	txc_glrgs_lane_घातer(efx, MDIO_MMD_PCS);
	txc_glrgs_lane_घातer(efx, MDIO_MMD_PHYXS);

	/* Analog रेजिस्टर bank in PMA/PMD, PHY XS */
	txc_analog_lane_घातer(efx, MDIO_MMD_PMAPMD);
	txc_analog_lane_घातer(efx, MDIO_MMD_PHYXS);
पूर्ण

अटल व्योम txc_reset_logic_mmd(काष्ठा ef4_nic *efx, पूर्णांक mmd)
अणु
	पूर्णांक val = ef4_mdio_पढ़ो(efx, mmd, TXC_GLRGS_GLCMD);
	पूर्णांक tries = 50;

	val |= (1 << TXC_GLCMD_LMTSWRST_LBN);
	ef4_mdio_ग_लिखो(efx, mmd, TXC_GLRGS_GLCMD, val);
	जबतक (--tries) अणु
		val = ef4_mdio_पढ़ो(efx, mmd, TXC_GLRGS_GLCMD);
		अगर (!(val & (1 << TXC_GLCMD_LMTSWRST_LBN)))
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (!tries)
		netअगर_info(efx, hw, efx->net_dev,
			   TXCNAME " Logic reset timed out!\n");
पूर्ण

/* Perक्रमm a logic reset. This preserves the configuration रेजिस्टरs
 * and is needed क्रम some configuration changes to take effect */
अटल व्योम txc_reset_logic(काष्ठा ef4_nic *efx)
अणु
	/* The data sheet claims we can करो the logic reset on either the
	 * PCS or the PHYXS and the result is a reset of both host- and
	 * line-side logic. */
	txc_reset_logic_mmd(efx, MDIO_MMD_PCS);
पूर्ण

अटल bool txc43128_phy_पढ़ो_link(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_mdio_links_ok(efx, TXC_REQUIRED_DEVS);
पूर्ण

अटल पूर्णांक txc43128_phy_reconfigure(काष्ठा ef4_nic *efx)
अणु
	काष्ठा txc43128_data *phy_data = efx->phy_data;
	क्रमागत ef4_phy_mode mode_change = efx->phy_mode ^ phy_data->phy_mode;
	bool loop_change = LOOPBACK_CHANGED(phy_data, efx, TXC_LOOPBACKS);

	अगर (efx->phy_mode & mode_change & PHY_MODE_TX_DISABLED) अणु
		txc_reset_phy(efx);
		txc_apply_शेषs(efx);
		falcon_reset_xaui(efx);
		mode_change &= ~PHY_MODE_TX_DISABLED;
	पूर्ण

	ef4_mdio_transmit_disable(efx);
	ef4_mdio_phy_reconfigure(efx);
	अगर (mode_change & PHY_MODE_LOW_POWER)
		txc_set_घातer(efx);

	/* The data sheet claims this is required after every reconfiguration
	 * (note at end of 7.1), but we mustn't करो it when nothing changes as
	 * it glitches the link, and reconfigure माला_लो called on link change,
	 * so we get an IRQ storm on link up. */
	अगर (loop_change || mode_change)
		txc_reset_logic(efx);

	phy_data->phy_mode = efx->phy_mode;
	phy_data->loopback_mode = efx->loopback_mode;

	वापस 0;
पूर्ण

अटल व्योम txc43128_phy_fini(काष्ठा ef4_nic *efx)
अणु
	/* Disable link events */
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL, 0);
पूर्ण

अटल व्योम txc43128_phy_हटाओ(काष्ठा ef4_nic *efx)
अणु
	kमुक्त(efx->phy_data);
	efx->phy_data = शून्य;
पूर्ण

/* Periodic callback: this exists मुख्यly to poll link status as we
 * करोn't use LASI पूर्णांकerrupts */
अटल bool txc43128_phy_poll(काष्ठा ef4_nic *efx)
अणु
	काष्ठा txc43128_data *data = efx->phy_data;
	bool was_up = efx->link_state.up;

	efx->link_state.up = txc43128_phy_पढ़ो_link(efx);
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;
	efx->link_state.fc = efx->wanted_fc;

	अगर (efx->link_state.up || (efx->loopback_mode != LOOPBACK_NONE)) अणु
		data->bug10934_समयr = jअगरfies;
	पूर्ण अन्यथा अणु
		अगर (समय_after_eq(jअगरfies, (data->bug10934_समयr +
					    BUG10934_RESET_INTERVAL))) अणु
			data->bug10934_समयr = jअगरfies;
			txc_reset_logic(efx);
		पूर्ण
	पूर्ण

	वापस efx->link_state.up != was_up;
पूर्ण

अटल स्थिर अक्षर *स्थिर txc43128_test_names[] = अणु
	"bist"
पूर्ण;

अटल स्थिर अक्षर *txc43128_test_name(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक index)
अणु
	अगर (index < ARRAY_SIZE(txc43128_test_names))
		वापस txc43128_test_names[index];
	वापस शून्य;
पूर्ण

अटल पूर्णांक txc43128_run_tests(काष्ठा ef4_nic *efx, पूर्णांक *results, अचिन्हित flags)
अणु
	पूर्णांक rc;

	अगर (!(flags & ETH_TEST_FL_OFFLINE))
		वापस 0;

	rc = txc_reset_phy(efx);
	अगर (rc < 0)
		वापस rc;

	rc = txc_bist(efx);
	txc_apply_शेषs(efx);
	results[0] = rc ? -1 : 1;
	वापस rc;
पूर्ण

अटल व्योम txc43128_get_link_ksettings(काष्ठा ef4_nic *efx,
					काष्ठा ethtool_link_ksettings *cmd)
अणु
	mdio45_ethtool_ksettings_get(&efx->mdio, cmd);
पूर्ण

स्थिर काष्ठा ef4_phy_operations falcon_txc_phy_ops = अणु
	.probe		= txc43128_phy_probe,
	.init		= txc43128_phy_init,
	.reconfigure	= txc43128_phy_reconfigure,
	.poll		= txc43128_phy_poll,
	.fini		= txc43128_phy_fini,
	.हटाओ		= txc43128_phy_हटाओ,
	.get_link_ksettings = txc43128_get_link_ksettings,
	.set_link_ksettings = ef4_mdio_set_link_ksettings,
	.test_alive	= ef4_mdio_test_alive,
	.run_tests	= txc43128_run_tests,
	.test_name	= txc43128_test_name,
पूर्ण;
