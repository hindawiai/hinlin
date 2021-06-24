<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2012 Solarflare Communications Inc.
 */
/*
 * Driver क्रम AMCC QT202x SFP+ and XFP adapters; see www.amcc.com क्रम details
 */

#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश "efx.h"
#समावेश "mdio_10g.h"
#समावेश "phy.h"
#समावेश "nic.h"

#घोषणा QT202X_REQUIRED_DEVS (MDIO_DEVS_PCS |		\
			      MDIO_DEVS_PMAPMD |	\
			      MDIO_DEVS_PHYXS)

#घोषणा QT202X_LOOPBACKS ((1 << LOOPBACK_PCS) |		\
			  (1 << LOOPBACK_PMAPMD) |	\
			  (1 << LOOPBACK_PHYXS_WS))

/****************************************************************************/
/* Quake-specअगरic MDIO रेजिस्टरs */
#घोषणा MDIO_QUAKE_LED0_REG	(0xD006)

/* QT2025C only */
#घोषणा PCS_FW_HEARTBEAT_REG	0xd7ee
#घोषणा PCS_FW_HEARTB_LBN	0
#घोषणा PCS_FW_HEARTB_WIDTH	8
#घोषणा PCS_FW_PRODUCT_CODE_1	0xd7f0
#घोषणा PCS_FW_VERSION_1	0xd7f3
#घोषणा PCS_FW_BUILD_1		0xd7f6
#घोषणा PCS_UC8051_STATUS_REG	0xd7fd
#घोषणा PCS_UC_STATUS_LBN	0
#घोषणा PCS_UC_STATUS_WIDTH	8
#घोषणा PCS_UC_STATUS_FW_SAVE	0x20
#घोषणा PMA_PMD_MODE_REG	0xc301
#घोषणा PMA_PMD_RXIN_SEL_LBN	6
#घोषणा PMA_PMD_FTX_CTRL2_REG	0xc309
#घोषणा PMA_PMD_FTX_STATIC_LBN	13
#घोषणा PMA_PMD_VEND1_REG	0xc001
#घोषणा PMA_PMD_VEND1_LBTXD_LBN	15
#घोषणा PCS_VEND1_REG		0xc000
#घोषणा PCS_VEND1_LBTXD_LBN	5

व्योम falcon_qt202x_set_led(काष्ठा ef4_nic *p, पूर्णांक led, पूर्णांक mode)
अणु
	पूर्णांक addr = MDIO_QUAKE_LED0_REG + led;
	ef4_mdio_ग_लिखो(p, MDIO_MMD_PMAPMD, addr, mode);
पूर्ण

काष्ठा qt202x_phy_data अणु
	क्रमागत ef4_phy_mode phy_mode;
	bool bug17190_in_bad_state;
	अचिन्हित दीर्घ bug17190_समयr;
	u32 firmware_ver;
पूर्ण;

#घोषणा QT2022C2_MAX_RESET_TIME 500
#घोषणा QT2022C2_RESET_WAIT 10

#घोषणा QT2025C_MAX_HEARTB_TIME (5 * HZ)
#घोषणा QT2025C_HEARTB_WAIT 100
#घोषणा QT2025C_MAX_FWSTART_TIME (25 * HZ / 10)
#घोषणा QT2025C_FWSTART_WAIT 100

#घोषणा BUG17190_INTERVAL (2 * HZ)

अटल पूर्णांक qt2025c_रुको_heartbeat(काष्ठा ef4_nic *efx)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + QT2025C_MAX_HEARTB_TIME;
	पूर्णांक reg, old_counter = 0;

	/* Wait क्रम firmware heartbeat to start */
	क्रम (;;) अणु
		पूर्णांक counter;
		reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_PCS, PCS_FW_HEARTBEAT_REG);
		अगर (reg < 0)
			वापस reg;
		counter = ((reg >> PCS_FW_HEARTB_LBN) &
			    ((1 << PCS_FW_HEARTB_WIDTH) - 1));
		अगर (old_counter == 0)
			old_counter = counter;
		अन्यथा अगर (counter != old_counter)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout)) अणु
			/* Some cables have EEPROMs that conflict with the
			 * PHY's on-board EEPROM so it cannot load firmware */
			netअगर_err(efx, hw, efx->net_dev,
				  "If an SFP+ direct attach cable is"
				  " connected, please check that it complies"
				  " with the SFP+ specification\n");
			वापस -ETIMEDOUT;
		पूर्ण
		msleep(QT2025C_HEARTB_WAIT);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qt2025c_रुको_fw_status_good(काष्ठा ef4_nic *efx)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + QT2025C_MAX_FWSTART_TIME;
	पूर्णांक reg;

	/* Wait क्रम firmware status to look good */
	क्रम (;;) अणु
		reg = ef4_mdio_पढ़ो(efx, MDIO_MMD_PCS, PCS_UC8051_STATUS_REG);
		अगर (reg < 0)
			वापस reg;
		अगर ((reg &
		     ((1 << PCS_UC_STATUS_WIDTH) - 1) << PCS_UC_STATUS_LBN) >=
		    PCS_UC_STATUS_FW_SAVE)
			अवरोध;
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		msleep(QT2025C_FWSTART_WAIT);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qt2025c_restart_firmware(काष्ठा ef4_nic *efx)
अणु
	/* Restart microcontroller execution of firmware from RAM */
	ef4_mdio_ग_लिखो(efx, 3, 0xe854, 0x00c0);
	ef4_mdio_ग_लिखो(efx, 3, 0xe854, 0x0040);
	msleep(50);
पूर्ण

अटल पूर्णांक qt2025c_रुको_reset(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	rc = qt2025c_रुको_heartbeat(efx);
	अगर (rc != 0)
		वापस rc;

	rc = qt2025c_रुको_fw_status_good(efx);
	अगर (rc == -ETIMEDOUT) अणु
		/* Bug 17689: occasionally heartbeat starts but firmware status
		 * code never progresses beyond 0x00.  Try again, once, after
		 * restarting execution of the firmware image. */
		netअगर_dbg(efx, hw, efx->net_dev,
			  "bashing QT2025C microcontroller\n");
		qt2025c_restart_firmware(efx);
		rc = qt2025c_रुको_heartbeat(efx);
		अगर (rc != 0)
			वापस rc;
		rc = qt2025c_रुको_fw_status_good(efx);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम qt2025c_firmware_id(काष्ठा ef4_nic *efx)
अणु
	काष्ठा qt202x_phy_data *phy_data = efx->phy_data;
	u8 firmware_id[9];
	माप_प्रकार i;

	क्रम (i = 0; i < माप(firmware_id); i++)
		firmware_id[i] = ef4_mdio_पढ़ो(efx, MDIO_MMD_PCS,
					       PCS_FW_PRODUCT_CODE_1 + i);
	netअगर_info(efx, probe, efx->net_dev,
		   "QT2025C firmware %xr%d v%d.%d.%d.%d [20%02d-%02d-%02d]\n",
		   (firmware_id[0] << 8) | firmware_id[1], firmware_id[2],
		   firmware_id[3] >> 4, firmware_id[3] & 0xf,
		   firmware_id[4], firmware_id[5],
		   firmware_id[6], firmware_id[7], firmware_id[8]);
	phy_data->firmware_ver = ((firmware_id[3] & 0xf0) << 20) |
				 ((firmware_id[3] & 0x0f) << 16) |
				 (firmware_id[4] << 8) | firmware_id[5];
पूर्ण

अटल व्योम qt2025c_bug17190_workaround(काष्ठा ef4_nic *efx)
अणु
	काष्ठा qt202x_phy_data *phy_data = efx->phy_data;

	/* The PHY can get stuck in a state where it reports PHY_XS and PMA/PMD
	 * layers up, but PCS करोwn (no block_lock).  If we notice this state
	 * persisting क्रम a couple of seconds, we चयन PMA/PMD loopback
	 * briefly on and then off again, which is normally sufficient to
	 * recover it.
	 */
	अगर (efx->link_state.up ||
	    !ef4_mdio_links_ok(efx, MDIO_DEVS_PMAPMD | MDIO_DEVS_PHYXS)) अणु
		phy_data->bug17190_in_bad_state = false;
		वापस;
	पूर्ण

	अगर (!phy_data->bug17190_in_bad_state) अणु
		phy_data->bug17190_in_bad_state = true;
		phy_data->bug17190_समयr = jअगरfies + BUG17190_INTERVAL;
		वापस;
	पूर्ण

	अगर (समय_after_eq(jअगरfies, phy_data->bug17190_समयr)) अणु
		netअगर_dbg(efx, hw, efx->net_dev, "bashing QT2025C PMA/PMD\n");
		ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD, MDIO_CTRL1,
				  MDIO_PMA_CTRL1_LOOPBACK, true);
		msleep(100);
		ef4_mdio_set_flag(efx, MDIO_MMD_PMAPMD, MDIO_CTRL1,
				  MDIO_PMA_CTRL1_LOOPBACK, false);
		phy_data->bug17190_समयr = jअगरfies + BUG17190_INTERVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qt2025c_select_phy_mode(काष्ठा ef4_nic *efx)
अणु
	काष्ठा qt202x_phy_data *phy_data = efx->phy_data;
	काष्ठा falcon_board *board = falcon_board(efx);
	पूर्णांक reg, rc, i;
	uपूर्णांक16_t phy_op_mode;

	/* Only 2.0.1.0+ PHY firmware supports the more optimal SFP+
	 * Self-Configure mode.  Don't attempt any चयनing अगर we encounter
	 * older firmware. */
	अगर (phy_data->firmware_ver < 0x02000100)
		वापस 0;

	/* In general we will get optimal behaviour in "SFP+ Self-Configure"
	 * mode; however, that घातers करोwn most of the PHY when no module is
	 * present, so we must use a dअगरferent mode (any fixed mode will करो)
	 * to be sure that loopbacks will work. */
	phy_op_mode = (efx->loopback_mode == LOOPBACK_NONE) ? 0x0038 : 0x0020;

	/* Only change mode अगर really necessary */
	reg = ef4_mdio_पढ़ो(efx, 1, 0xc319);
	अगर ((reg & 0x0038) == phy_op_mode)
		वापस 0;
	netअगर_dbg(efx, hw, efx->net_dev, "Switching PHY to mode 0x%04x\n",
		  phy_op_mode);

	/* This sequence replicates the रेजिस्टर ग_लिखोs configured in the boot
	 * EEPROM (including the dअगरferences between board revisions), except
	 * that the operating mode is changed, and the PHY is prevented from
	 * unnecessarily reloading the मुख्य firmware image again. */
	ef4_mdio_ग_लिखो(efx, 1, 0xc300, 0x0000);
	/* (Note: this portion of the boot EEPROM sequence, which bit-bashes 9
	 * STOPs onto the firmware/module I2C bus to reset it, varies across
	 * board revisions, as the bus is connected to dअगरferent GPIO/LED
	 * outमाला_दो on the PHY.) */
	अगर (board->major == 0 && board->minor < 2) अणु
		ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4498);
		क्रम (i = 0; i < 9; i++) अणु
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4488);
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4480);
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4490);
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4498);
		पूर्ण
	पूर्ण अन्यथा अणु
		ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x0920);
		ef4_mdio_ग_लिखो(efx, 1, 0xd008, 0x0004);
		क्रम (i = 0; i < 9; i++) अणु
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x0900);
			ef4_mdio_ग_लिखो(efx, 1, 0xd008, 0x0005);
			ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x0920);
			ef4_mdio_ग_लिखो(efx, 1, 0xd008, 0x0004);
		पूर्ण
		ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4900);
	पूर्ण
	ef4_mdio_ग_लिखो(efx, 1, 0xc303, 0x4900);
	ef4_mdio_ग_लिखो(efx, 1, 0xc302, 0x0004);
	ef4_mdio_ग_लिखो(efx, 1, 0xc316, 0x0013);
	ef4_mdio_ग_लिखो(efx, 1, 0xc318, 0x0054);
	ef4_mdio_ग_लिखो(efx, 1, 0xc319, phy_op_mode);
	ef4_mdio_ग_लिखो(efx, 1, 0xc31a, 0x0098);
	ef4_mdio_ग_लिखो(efx, 3, 0x0026, 0x0e00);
	ef4_mdio_ग_लिखो(efx, 3, 0x0027, 0x0013);
	ef4_mdio_ग_लिखो(efx, 3, 0x0028, 0xa528);
	ef4_mdio_ग_लिखो(efx, 1, 0xd006, 0x000a);
	ef4_mdio_ग_लिखो(efx, 1, 0xd007, 0x0009);
	ef4_mdio_ग_लिखो(efx, 1, 0xd008, 0x0004);
	/* This additional ग_लिखो is not present in the boot EEPROM.  It
	 * prevents the PHY's पूर्णांकernal boot ROM करोing another poपूर्णांकless (and
	 * slow) reload of the firmware image (the microcontroller's code
	 * memory is not affected by the microcontroller reset). */
	ef4_mdio_ग_लिखो(efx, 1, 0xc317, 0x00ff);
	/* PMA/PMD loopback sets RXIN to inverse polarity and the firmware
	 * restart करोesn't reset it. We need to करो that ourselves. */
	ef4_mdio_set_flag(efx, 1, PMA_PMD_MODE_REG,
			  1 << PMA_PMD_RXIN_SEL_LBN, false);
	ef4_mdio_ग_लिखो(efx, 1, 0xc300, 0x0002);
	msleep(20);

	/* Restart microcontroller execution of firmware from RAM */
	qt2025c_restart_firmware(efx);

	/* Wait क्रम the microcontroller to be पढ़ोy again */
	rc = qt2025c_रुको_reset(efx);
	अगर (rc < 0) अणु
		netअगर_err(efx, hw, efx->net_dev,
			  "PHY microcontroller reset during mode switch "
			  "timed out\n");
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qt202x_reset_phy(काष्ठा ef4_nic *efx)
अणु
	पूर्णांक rc;

	अगर (efx->phy_type == PHY_TYPE_QT2025C) अणु
		/* Wait क्रम the reset triggered by falcon_reset_hw()
		 * to complete */
		rc = qt2025c_रुको_reset(efx);
		अगर (rc < 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		/* Reset the PHYXS MMD. This is करोcumented as करोing
		 * a complete soft reset. */
		rc = ef4_mdio_reset_mmd(efx, MDIO_MMD_PHYXS,
					QT2022C2_MAX_RESET_TIME /
					QT2022C2_RESET_WAIT,
					QT2022C2_RESET_WAIT);
		अगर (rc < 0)
			जाओ fail;
	पूर्ण

	/* Wait 250ms क्रम the PHY to complete bootup */
	msleep(250);

	falcon_board(efx)->type->init_phy(efx);

	वापस 0;

 fail:
	netअगर_err(efx, hw, efx->net_dev, "PHY reset timed out\n");
	वापस rc;
पूर्ण

अटल पूर्णांक qt202x_phy_probe(काष्ठा ef4_nic *efx)
अणु
	काष्ठा qt202x_phy_data *phy_data;

	phy_data = kzalloc(माप(काष्ठा qt202x_phy_data), GFP_KERNEL);
	अगर (!phy_data)
		वापस -ENOMEM;
	efx->phy_data = phy_data;
	phy_data->phy_mode = efx->phy_mode;
	phy_data->bug17190_in_bad_state = false;
	phy_data->bug17190_समयr = 0;

	efx->mdio.mmds = QT202X_REQUIRED_DEVS;
	efx->mdio.mode_support = MDIO_SUPPORTS_C45 | MDIO_EMULATE_C22;
	efx->loopback_modes = QT202X_LOOPBACKS | FALCON_XMAC_LOOPBACKS;
	वापस 0;
पूर्ण

अटल पूर्णांक qt202x_phy_init(काष्ठा ef4_nic *efx)
अणु
	u32 devid;
	पूर्णांक rc;

	rc = qt202x_reset_phy(efx);
	अगर (rc) अणु
		netअगर_err(efx, probe, efx->net_dev, "PHY init failed\n");
		वापस rc;
	पूर्ण

	devid = ef4_mdio_पढ़ो_id(efx, MDIO_MMD_PHYXS);
	netअगर_info(efx, probe, efx->net_dev,
		   "PHY ID reg %x (OUI %06x model %02x revision %x)\n",
		   devid, ef4_mdio_id_oui(devid), ef4_mdio_id_model(devid),
		   ef4_mdio_id_rev(devid));

	अगर (efx->phy_type == PHY_TYPE_QT2025C)
		qt2025c_firmware_id(efx);

	वापस 0;
पूर्ण

अटल पूर्णांक qt202x_link_ok(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_mdio_links_ok(efx, QT202X_REQUIRED_DEVS);
पूर्ण

अटल bool qt202x_phy_poll(काष्ठा ef4_nic *efx)
अणु
	bool was_up = efx->link_state.up;

	efx->link_state.up = qt202x_link_ok(efx);
	efx->link_state.speed = 10000;
	efx->link_state.fd = true;
	efx->link_state.fc = efx->wanted_fc;

	अगर (efx->phy_type == PHY_TYPE_QT2025C)
		qt2025c_bug17190_workaround(efx);

	वापस efx->link_state.up != was_up;
पूर्ण

अटल पूर्णांक qt202x_phy_reconfigure(काष्ठा ef4_nic *efx)
अणु
	काष्ठा qt202x_phy_data *phy_data = efx->phy_data;

	अगर (efx->phy_type == PHY_TYPE_QT2025C) अणु
		पूर्णांक rc = qt2025c_select_phy_mode(efx);
		अगर (rc)
			वापस rc;

		/* There are several dअगरferent रेजिस्टर bits which can
		 * disable TX (and save घातer) on direct-attach cables
		 * or optical transceivers, varying somewhat between
		 * firmware versions.  Only 'static mode' appears to
		 * cover everything. */
		mdio_set_flag(
			&efx->mdio, efx->mdio.prtad, MDIO_MMD_PMAPMD,
			PMA_PMD_FTX_CTRL2_REG, 1 << PMA_PMD_FTX_STATIC_LBN,
			efx->phy_mode & PHY_MODE_TX_DISABLED ||
			efx->phy_mode & PHY_MODE_LOW_POWER ||
			efx->loopback_mode == LOOPBACK_PCS ||
			efx->loopback_mode == LOOPBACK_PMAPMD);
	पूर्ण अन्यथा अणु
		/* Reset the PHY when moving from tx off to tx on */
		अगर (!(efx->phy_mode & PHY_MODE_TX_DISABLED) &&
		    (phy_data->phy_mode & PHY_MODE_TX_DISABLED))
			qt202x_reset_phy(efx);

		ef4_mdio_transmit_disable(efx);
	पूर्ण

	ef4_mdio_phy_reconfigure(efx);

	phy_data->phy_mode = efx->phy_mode;

	वापस 0;
पूर्ण

अटल व्योम qt202x_phy_get_link_ksettings(काष्ठा ef4_nic *efx,
					  काष्ठा ethtool_link_ksettings *cmd)
अणु
	mdio45_ethtool_ksettings_get(&efx->mdio, cmd);
पूर्ण

अटल व्योम qt202x_phy_हटाओ(काष्ठा ef4_nic *efx)
अणु
	/* Free the context block */
	kमुक्त(efx->phy_data);
	efx->phy_data = शून्य;
पूर्ण

अटल पूर्णांक qt202x_phy_get_module_info(काष्ठा ef4_nic *efx,
				      काष्ठा ethtool_modinfo *modinfo)
अणु
	modinfo->type = ETH_MODULE_SFF_8079;
	modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	वापस 0;
पूर्ण

अटल पूर्णांक qt202x_phy_get_module_eeprom(काष्ठा ef4_nic *efx,
					काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	पूर्णांक mmd, reg_base, rc, i;

	अगर (efx->phy_type == PHY_TYPE_QT2025C) अणु
		mmd = MDIO_MMD_PCS;
		reg_base = 0xd000;
	पूर्ण अन्यथा अणु
		mmd = MDIO_MMD_PMAPMD;
		reg_base = 0x8007;
	पूर्ण

	क्रम (i = 0; i < ee->len; i++) अणु
		rc = ef4_mdio_पढ़ो(efx, mmd, reg_base + ee->offset + i);
		अगर (rc < 0)
			वापस rc;
		data[i] = rc;
	पूर्ण

	वापस 0;
पूर्ण

स्थिर काष्ठा ef4_phy_operations falcon_qt202x_phy_ops = अणु
	.probe		 = qt202x_phy_probe,
	.init		 = qt202x_phy_init,
	.reconfigure	 = qt202x_phy_reconfigure,
	.poll		 = qt202x_phy_poll,
	.fini		 = ef4_port_dummy_op_व्योम,
	.हटाओ		 = qt202x_phy_हटाओ,
	.get_link_ksettings = qt202x_phy_get_link_ksettings,
	.set_link_ksettings = ef4_mdio_set_link_ksettings,
	.test_alive	 = ef4_mdio_test_alive,
	.get_module_eeprom = qt202x_phy_get_module_eeprom,
	.get_module_info = qt202x_phy_get_module_info,
पूर्ण;
