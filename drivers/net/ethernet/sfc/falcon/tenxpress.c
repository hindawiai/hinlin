<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2007-2011 Solarflare Communications Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "efx.h"
#समावेश "mdio_10g.h"
#समावेश "nic.h"
#समावेश "phy.h"
#समावेश "workarounds.h"

/* We expect these MMDs to be in the package. */
#घोषणा TENXPRESS_REQUIRED_DEVS (MDIO_DEVS_PMAPMD	| \
				 MDIO_DEVS_PCS		| \
				 MDIO_DEVS_PHYXS	| \
				 MDIO_DEVS_AN)

#घोषणा SFX7101_LOOPBACKS ((1 << LOOPBACK_PHYXS) |	\
			   (1 << LOOPBACK_PCS) |	\
			   (1 << LOOPBACK_PMAPMD) |	\
			   (1 << LOOPBACK_PHYXS_WS))

/* We complain अगर we fail to see the link partner as 10G capable this many
 * बार in a row (must be > 1 as sampling the स्वतःneg. रेजिस्टरs is racy)
 */
#घोषणा MAX_BAD_LP_TRIES	(5)

/* Extended control रेजिस्टर */
#घोषणा PMA_PMD_XCONTROL_REG	49152
#घोषणा PMA_PMD_EXT_GMII_EN_LBN	1
#घोषणा PMA_PMD_EXT_GMII_EN_WIDTH 1
#घोषणा PMA_PMD_EXT_CLK_OUT_LBN	2
#घोषणा PMA_PMD_EXT_CLK_OUT_WIDTH 1
#घोषणा PMA_PMD_LNPGA_POWERDOWN_LBN 8
#घोषणा PMA_PMD_LNPGA_POWERDOWN_WIDTH 1
#घोषणा PMA_PMD_EXT_CLK312_WIDTH 1
#घोषणा PMA_PMD_EXT_LPOWER_LBN  12
#घोषणा PMA_PMD_EXT_LPOWER_WIDTH 1
#घोषणा PMA_PMD_EXT_ROBUST_LBN	14
#घोषणा PMA_PMD_EXT_ROBUST_WIDTH 1
#घोषणा PMA_PMD_EXT_SSR_LBN	15
#घोषणा PMA_PMD_EXT_SSR_WIDTH	1

/* extended status रेजिस्टर */
#घोषणा PMA_PMD_XSTATUS_REG	49153
#घोषणा PMA_PMD_XSTAT_MDIX_LBN	14
#घोषणा PMA_PMD_XSTAT_FLP_LBN   (12)

/* LED control रेजिस्टर */
#घोषणा PMA_PMD_LED_CTRL_REG	49159
#घोषणा PMA_PMA_LED_ACTIVITY_LBN	(3)

/* LED function override रेजिस्टर */
#घोषणा PMA_PMD_LED_OVERR_REG	49161
/* Bit positions क्रम dअगरferent LEDs (there are more but not wired on SFE4001)*/
#घोषणा PMA_PMD_LED_LINK_LBN	(0)
#घोषणा PMA_PMD_LED_SPEED_LBN	(2)
#घोषणा PMA_PMD_LED_TX_LBN	(4)
#घोषणा PMA_PMD_LED_RX_LBN	(6)
/* Override settings */
#घोषणा	PMA_PMD_LED_AUTO	(0)	/* H/W control */
#घोषणा	PMA_PMD_LED_ON		(1)
#घोषणा	PMA_PMD_LED_OFF		(2)
#घोषणा PMA_PMD_LED_FLASH	(3)
#घोषणा PMA_PMD_LED_MASK	3
/* All LEDs under hardware control */
/* Green and Amber under hardware control, Red off */
#घोषणा SFX7101_PMA_PMD_LED_DEFAULT (PMA_PMD_LED_OFF << PMA_PMD_LED_RX_LBN)

#घोषणा PMA_PMD_SPEED_ENABLE_REG 49192
#घोषणा PMA_PMD_100TX_ADV_LBN    1
#घोषणा PMA_PMD_100TX_ADV_WIDTH  1
#घोषणा PMA_PMD_1000T_ADV_LBN    2
#घोषणा PMA_PMD_1000T_ADV_WIDTH  1
#घोषणा PMA_PMD_10000T_ADV_LBN   3
#घोषणा PMA_PMD_10000T_ADV_WIDTH 1
#घोषणा PMA_PMD_SPEED_LBN        4
#घोषणा PMA_PMD_SPEED_WIDTH      4

/* Misc रेजिस्टर defines */
#घोषणा PCS_CLOCK_CTRL_REG	55297
#घोषणा PLL312_RST_N_LBN 2

#घोषणा PCS_SOFT_RST2_REG	55302
#घोषणा SERDES_RST_N_LBN 13
#घोषणा XGXS_RST_N_LBN 12

#घोषणा	PCS_TEST_SELECT_REG	55303	/* PRM 10.5.8 */
#घोषणा	CLK312_EN_LBN 3

/* PHYXS रेजिस्टरs */
#घोषणा PHYXS_XCONTROL_REG	49152
#घोषणा PHYXS_RESET_LBN		15
#घोषणा PHYXS_RESET_WIDTH	1

#घोषणा PHYXS_TEST1         (49162)
#घोषणा LOOPBACK_NEAR_LBN   (8)
#घोषणा LOOPBACK_NEAR_WIDTH (1)

/* Boot status रेजिस्टर */
#घोषणा PCS_BOOT_STATUS_REG		53248
#घोषणा PCS_BOOT_FATAL_ERROR_LBN	0
#घोषणा PCS_BOOT_PROGRESS_LBN		1
#घोषणा PCS_BOOT_PROGRESS_WIDTH		2
#घोषणा PCS_BOOT_PROGRESS_INIT		0
#घोषणा PCS_BOOT_PROGRESS_WAIT_MDIO	1
#घोषणा PCS_BOOT_PROGRESS_CHECKSUM	2
#घोषणा PCS_BOOT_PROGRESS_JUMP		3
#घोषणा PCS_BOOT_DOWNLOAD_WAIT_LBN	3
#घोषणा PCS_BOOT_CODE_STARTED_LBN	4

/* 100M/1G PHY रेजिस्टरs */
#घोषणा GPHY_XCONTROL_REG	49152
#घोषणा GPHY_ISOLATE_LBN	10
#घोषणा GPHY_ISOLATE_WIDTH	1
#घोषणा GPHY_DUPLEX_LBN		8
#घोषणा GPHY_DUPLEX_WIDTH	1
#घोषणा GPHY_LOOPBACK_NEAR_LBN	14
#घोषणा GPHY_LOOPBACK_NEAR_WIDTH 1

#घोषणा C22EXT_STATUS_REG       49153
#घोषणा C22EXT_STATUS_LINK_LBN  2
#घोषणा C22EXT_STATUS_LINK_WIDTH 1

#घोषणा C22EXT_MSTSLV_CTRL			49161
#घोषणा C22EXT_MSTSLV_CTRL_ADV_1000_HD_LBN	8
#घोषणा C22EXT_MSTSLV_CTRL_ADV_1000_FD_LBN	9

#घोषणा C22EXT_MSTSLV_STATUS			49162
#घोषणा C22EXT_MSTSLV_STATUS_LP_1000_HD_LBN	10
#घोषणा C22EXT_MSTSLV_STATUS_LP_1000_FD_LBN	11

/* Time to रुको between घातering करोwn the LNPGA and turning off the घातer
 * rails */
#घोषणा LNPGA_PDOWN_WAIT	(HZ / 5)

काष्ठा tenxpress_phy_data अणु
	क्रमागत ef4_loopback_mode loopback_mode;
	क्रमागत ef4_phy_mode phy_mode;
	पूर्णांक bad_lp_tries;
पूर्ण;

अटल पूर्णांक tenxpress_init(काष्ठा ef4_nic *efx)
अणु
	/* Enable 312.5 MHz घड़ी */
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PCS, PCS_TEST_SELECT_REG,
		       1 << CLK312_EN_LBN);

	/* Set the LEDs up as: Green = Link, Amber = Link/Act, Red = Off */
	ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_CTRL_REG,
			  1 << PMA_PMA_LED_ACTIVITY_LBN, true);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_OVERR_REG,
		       SFX7101_PMA_PMD_LED_DEFAULT);

	वापस 0;
पूर्ण

अटल पूर्णांक tenxpress_phy_probe(काष्ठा ef4_nic *efx)
अणु
	काष्ठा tenxpress_phy_data *phy_data;

	/* Allocate phy निजी storage */
	phy_data = kzalloc(माप(*phy_data), GFP_KERNEL);
	अगर (!phy_data)
		वापस -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;

	efx->mdio.mmds = TENXPRESS_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45;

	efx->loopback_modes = SFX7101_LOOPBACKS | FALCON_XMAC_LOOPBACKS;

	efx->link_advertising = (ADVERTISED_TP | ADVERTISED_Autoneg |
				 ADVERTISED_10000baseT_Full);

	वापस 0;
पूर्ण

अटल पूर्णांक tenxpress_phy_init(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	falcon_board(efx)->type->init_phy(efx);

	अगर (!(efx->phy_mode & PHY_MODE_SPECIAL)) अणु
		rc = ef4_mdio_रुको_reset_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		अगर (rc < 0)
			वापस rc;

		rc = ef4_mdio_check_mmds(efx, TENXPRESS_REQUIRED_DEVS);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = tenxpress_init(efx);
	अगर (rc < 0)
		वापस rc;

	/* Reinitialise flow control settings */
	ef4_link_set_wanted_fc(efx, efx->wanted_fc);
	ef4_mdio_an_reconfigure(efx);

	schedule_समयout_unपूर्णांकerruptible(HZ / 5); /* 200ms */

	/* Let XGXS and SerDes out of reset */
	falcon_reset_xaui(efx);

	वापस 0;
पूर्ण

/* Perक्रमm a "special software reset" on the PHY. The caller is
 * responsible क्रम saving and restoring the PHY hardware रेजिस्टरs
 * properly, and masking/unmasking LASI */
अटल पूर्णांक tenxpress_special_reset(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc, reg;

	/* The XGMAC घड़ी is driven from the SFX7101 312MHz घड़ी, so
	 * a special software reset can glitch the XGMAC sufficiently क्रम stats
	 * requests to fail. */
	falcon_stop_nic_stats(efx);

	/* Initiate reset */
	reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTROL_REG);
	reg |= (1 << PMA_PMD_EXT_SSR_LBN);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTROL_REG, reg);

	mdelay(200);

	/* Wait क्रम the blocks to come out of reset */
	rc = ef4_mdio_रुको_reset_mmds(efx, TENXPRESS_REQUIRED_DEVS);
	अगर (rc < 0)
		जाओ out;

	/* Try and reconfigure the device */
	rc = tenxpress_init(efx);
	अगर (rc < 0)
		जाओ out;

	/* Wait क्रम the XGXS state machine to churn */
	mdelay(10);
out:
	falcon_start_nic_stats(efx);
	वापस rc;
पूर्ण

अटल व्योम sfx7101_check_bad_lp(काष्ठा ef4_nic *efx, bool link_ok)
अणु
	काष्ठा tenxpress_phy_data *pd = efx->phy_data;
	bool bad_lp;
	पूर्णांक reg;

	अगर (link_ok) अणु
		bad_lp = false;
	पूर्ण अन्यथा अणु
		/* Check that AN has started but not completed. */
		reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_AN, MDIO_STAT1);
		अगर (!(reg & MDIO_AN_STAT1_LPABLE))
			वापस; /* LP status is unknown */
		bad_lp = !(reg & MDIO_AN_STAT1_COMPLETE);
		अगर (bad_lp)
			pd->bad_lp_tries++;
	पूर्ण

	/* Nothing to करो अगर all is well and was previously so. */
	अगर (!pd->bad_lp_tries)
		वापस;

	/* Use the RX (red) LED as an error indicator once we've seen AN
	 * failure several बार in a row, and also log a message. */
	अगर (!bad_lp || pd->bad_lp_tries == MAX_BAD_LP_TRIES) अणु
		reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_PMAPMD,
				    PMA_PMD_LED_OVERR_REG);
		reg &= ~(PMA_PMD_LED_MASK << PMA_PMD_LED_RX_LBN);
		अगर (!bad_lp) अणु
			reg |= PMA_PMD_LED_OFF << PMA_PMD_LED_RX_LBN;
		पूर्ण अन्यथा अणु
			reg |= PMA_PMD_LED_FLASH << PMA_PMD_LED_RX_LBN;
			netअगर_err(efx, link, efx->net_dev,
				  "appears to be plugged into a port"
				  " that is not 10GBASE-T capable. The PHY"
				  " supports 10GBASE-T ONLY, so no link can"
				  " be established\n");
		पूर्ण
		ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD,
			       PMA_PMD_LED_OVERR_REG, reg);
		pd->bad_lp_tries = bad_lp;
	पूर्ण
पूर्ण

अटल bool sfx7101_link_ok(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_mdio_links_ok(efx,
				 MDIO_DEVS_PMAPMD |
				 MDIO_DEVS_PCS |
				 MDIO_DEVS_PHYXS);
पूर्ण

अटल व्योम tenxpress_ext_loopback(काष्ठा ef4_nic *efx)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_PHYXS, PHYXS_TEST1,
			  1 << LOOPBACK_NEAR_LBN,
			  efx->loopback_mode == LOOPBACK_PHYXS);
पूर्ण

अटल व्योम tenxpress_low_घातer(काष्ठा ef4_nic *efx)
अणु
	ef4_mdio_set_mmds_lघातer(
		efx, !!(efx->phy_mode & PHY_MODE_LOW_POWER),
		TENXPRESS_REQUIRED_DEVS);
पूर्ण

अटल पूर्णांक tenxpress_phy_reconfigure(काष्ठा ef4_nic *efx)
अणु
	काष्ठा tenxpress_phy_data *phy_data = efx->phy_data;
	bool phy_mode_change, loop_reset;

	अगर (efx->phy_mode & (PHY_MODE_OFF | PHY_MODE_SPECIAL)) अणु
		phy_data->phy_mode = efx->phy_mode;
		वापस 0;
	पूर्ण

	phy_mode_change = (efx->phy_mode == PHY_MODE_NORMAL &&
			   phy_data->phy_mode != PHY_MODE_NORMAL);
	loop_reset = (LOOPBACK_OUT_OF(phy_data, efx, LOOPBACKS_EXTERNAL(efx)) ||
		      LOOPBACK_CHANGED(phy_data, efx, 1 << LOOPBACK_GPHY));

	अगर (loop_reset || phy_mode_change) अणु
		tenxpress_special_reset(efx);
		falcon_reset_xaui(efx);
	पूर्ण

	tenxpress_low_घातer(efx);
	ef4_mdio_transmit_disable(efx);
	ef4_mdio_phy_reconfigure(efx);
	tenxpress_ext_loopback(efx);
	ef4_mdio_an_reconfigure(efx);

	phy_data->loopback_mode = efx->loopback_mode;
	phy_data->phy_mode = efx->phy_mode;

	वापस 0;
पूर्ण

/* Poll क्रम link state changes */
अटल bool tenxpress_phy_poll(काष्ठा ef4_nic *efx)
अणु
	काष्ठा ef4_link_state old_state = efx->link_state;

	efx->link_state.up = sfx7101_link_ok(efx);
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;
	efx->link_state.fc = ef4_mdio_get_छोड़ो(efx);

	sfx7101_check_bad_lp(efx, efx->link_state.up);

	वापस !ef4_link_state_equal(&efx->link_state, &old_state);
पूर्ण

अटल व्योम sfx7101_phy_fini(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक reg;

	/* Power करोwn the LNPGA */
	reg = (1 << PMA_PMD_LNPGA_POWERDOWN_LBN);
	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD, PMA_PMD_XCONTROL_REG, reg);

	/* Waiting here ensures that the board fini, which can turn
	 * off the घातer to the PHY, won't get run until the LNPGA
	 * घातerकरोwn has been given दीर्घ enough to complete. */
	schedule_समयout_unपूर्णांकerruptible(LNPGA_PDOWN_WAIT); /* 200 ms */
पूर्ण

अटल व्योम tenxpress_phy_हटाओ(काष्ठा ef4_nic *efx)
अणु
	kमुक्त(efx->phy_data);
	efx->phy_data = शून्य;
पूर्ण


/* Override the RX, TX and link LEDs */
व्योम tenxpress_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode)
अणु
	पूर्णांक reg;

	चयन (mode) अणु
	हाल EF4_LED_OFF:
		reg = (PMA_PMD_LED_OFF << PMA_PMD_LED_TX_LBN) |
			(PMA_PMD_LED_OFF << PMA_PMD_LED_RX_LBN) |
			(PMA_PMD_LED_OFF << PMA_PMD_LED_LINK_LBN);
		अवरोध;
	हाल EF4_LED_ON:
		reg = (PMA_PMD_LED_ON << PMA_PMD_LED_TX_LBN) |
			(PMA_PMD_LED_ON << PMA_PMD_LED_RX_LBN) |
			(PMA_PMD_LED_ON << PMA_PMD_LED_LINK_LBN);
		अवरोध;
	शेष:
		reg = SFX7101_PMA_PMD_LED_DEFAULT;
		अवरोध;
	पूर्ण

	ef4_mdio_ग_लिखो(efx, MDIO_MMD_PMAPMD, PMA_PMD_LED_OVERR_REG, reg);
पूर्ण

अटल स्थिर अक्षर *स्थिर sfx7101_test_names[] = अणु
	"bist"
पूर्ण;

अटल स्थिर अक्षर *sfx7101_test_name(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक index)
अणु
	अगर (index < ARRAY_SIZE(sfx7101_test_names))
		वापस sfx7101_test_names[index];
	वापस शून्य;
पूर्ण

अटल पूर्णांक
sfx7101_run_tests(काष्ठा ef4_nic *efx, पूर्णांक *results, अचिन्हित flags)
अणु
	पूर्णांक rc;

	अगर (!(flags & ETH_TEST_FL_OFFLINE))
		वापस 0;

	/* BIST is स्वतःmatically run after a special software reset */
	rc = tenxpress_special_reset(efx);
	results[0] = rc ? -1 : 1;

	ef4_mdio_an_reconfigure(efx);

	वापस rc;
पूर्ण

अटल व्योम
tenxpress_get_link_ksettings(काष्ठा ef4_nic *efx,
			     काष्ठा ethtool_link_ksettings *cmd)
अणु
	u32 adv = 0, lpa = 0;
	पूर्णांक reg;

	reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL);
	अगर (reg & MDIO_AN_10GBT_CTRL_ADV10G)
		adv |= ADVERTISED_10000baseT_Full;
	reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_AN, MDIO_AN_10GBT_STAT);
	अगर (reg & MDIO_AN_10GBT_STAT_LP10G)
		lpa |= ADVERTISED_10000baseT_Full;

	mdio45_ethtool_ksettings_get_npage(&efx->mdio, cmd, adv, lpa);

	/* In loopback, the PHY स्वतःmatically brings up the correct पूर्णांकerface,
	 * but करोesn't advertise the correct speed. So override it */
	अगर (LOOPBACK_EXTERNAL(efx))
		cmd->base.speed = SPEED_10000;
पूर्ण

अटल पूर्णांक
tenxpress_set_link_ksettings(काष्ठा ef4_nic *efx,
			     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!cmd->base.स्वतःneg)
		वापस -EINVAL;

	वापस ef4_mdio_set_link_ksettings(efx, cmd);
पूर्ण

अटल व्योम sfx7101_set_npage_adv(काष्ठा ef4_nic *efx, u32 advertising)
अणु
	ef4_mdio_set_flag(efx, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
			  MDIO_AN_10GBT_CTRL_ADV10G,
			  advertising & ADVERTISED_10000baseT_Full);
पूर्ण

स्थिर काष्ठा ef4_phy_operations falcon_sfx7101_phy_ops = अणु
	.probe		  = tenxpress_phy_probe,
	.init             = tenxpress_phy_init,
	.reconfigure      = tenxpress_phy_reconfigure,
	.poll             = tenxpress_phy_poll,
	.fini             = sfx7101_phy_fini,
	.हटाओ		  = tenxpress_phy_हटाओ,
	.get_link_ksettings = tenxpress_get_link_ksettings,
	.set_link_ksettings = tenxpress_set_link_ksettings,
	.set_npage_adv    = sfx7101_set_npage_adv,
	.test_alive	  = ef4_mdio_test_alive,
	.test_name	  = sfx7101_test_name,
	.run_tests	  = sfx7101_run_tests,
पूर्ण;
