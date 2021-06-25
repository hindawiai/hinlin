<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2007-2012 Solarflare Communications Inc.
 */

#समावेश <linux/rtnetlink.h>

#समावेश "net_driver.h"
#समावेश "phy.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "workarounds.h"

/* Macros क्रम unpacking the board revision */
/* The revision info is in host byte order. */
#घोषणा FALCON_BOARD_TYPE(_rev) (_rev >> 8)
#घोषणा FALCON_BOARD_MAJOR(_rev) ((_rev >> 4) & 0xf)
#घोषणा FALCON_BOARD_MINOR(_rev) (_rev & 0xf)

/* Board types */
#घोषणा FALCON_BOARD_SFE4001 0x01
#घोषणा FALCON_BOARD_SFE4002 0x02
#घोषणा FALCON_BOARD_SFE4003 0x03
#घोषणा FALCON_BOARD_SFN4112F 0x52

/* Board temperature is about 15तओC above ambient when air flow is
 * limited.  The maximum acceptable ambient temperature varies
 * depending on the PHY specअगरications but the critical temperature
 * above which we should shut करोwn to aव्योम damage is 80तओC. */
#घोषणा FALCON_BOARD_TEMP_BIAS	15
#घोषणा FALCON_BOARD_TEMP_CRIT	(80 + FALCON_BOARD_TEMP_BIAS)

/* SFC4000 datasheet says: 'The maximum permitted junction temperature
 * is 125तओC; the thermal design of the environment क्रम the SFC4000
 * should aim to keep this well below 100तओC.' */
#घोषणा FALCON_JUNC_TEMP_MIN	0
#घोषणा FALCON_JUNC_TEMP_MAX	90
#घोषणा FALCON_JUNC_TEMP_CRIT	125

/*****************************************************************************
 * Support क्रम LM87 sensor chip used on several boards
 */
#घोषणा LM87_REG_TEMP_HW_INT_LOCK	0x13
#घोषणा LM87_REG_TEMP_HW_EXT_LOCK	0x14
#घोषणा LM87_REG_TEMP_HW_INT		0x17
#घोषणा LM87_REG_TEMP_HW_EXT		0x18
#घोषणा LM87_REG_TEMP_EXT1		0x26
#घोषणा LM87_REG_TEMP_INT		0x27
#घोषणा LM87_REG_ALARMS1		0x41
#घोषणा LM87_REG_ALARMS2		0x42
#घोषणा LM87_IN_LIMITS(nr, _min, _max)			\
	0x2B + (nr) * 2, _max, 0x2C + (nr) * 2, _min
#घोषणा LM87_AIN_LIMITS(nr, _min, _max)			\
	0x3B + (nr), _max, 0x1A + (nr), _min
#घोषणा LM87_TEMP_INT_LIMITS(_min, _max)		\
	0x39, _max, 0x3A, _min
#घोषणा LM87_TEMP_EXT1_LIMITS(_min, _max)		\
	0x37, _max, 0x38, _min

#घोषणा LM87_ALARM_TEMP_INT		0x10
#घोषणा LM87_ALARM_TEMP_EXT1		0x20

#अगर IS_ENABLED(CONFIG_SENSORS_LM87)

अटल पूर्णांक ef4_poke_lm87(काष्ठा i2c_client *client, स्थिर u8 *reg_values)
अणु
	जबतक (*reg_values) अणु
		u8 reg = *reg_values++;
		u8 value = *reg_values++;
		पूर्णांक rc = i2c_smbus_ग_लिखो_byte_data(client, reg, value);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर u8 falcon_lm87_common_regs[] = अणु
	LM87_REG_TEMP_HW_INT_LOCK, FALCON_BOARD_TEMP_CRIT,
	LM87_REG_TEMP_HW_INT, FALCON_BOARD_TEMP_CRIT,
	LM87_TEMP_EXT1_LIMITS(FALCON_JUNC_TEMP_MIN, FALCON_JUNC_TEMP_MAX),
	LM87_REG_TEMP_HW_EXT_LOCK, FALCON_JUNC_TEMP_CRIT,
	LM87_REG_TEMP_HW_EXT, FALCON_JUNC_TEMP_CRIT,
	0
पूर्ण;

अटल पूर्णांक ef4_init_lm87(काष्ठा ef4_nic *efx, स्थिर काष्ठा i2c_board_info *info,
			 स्थिर u8 *reg_values)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);
	काष्ठा i2c_client *client = i2c_new_client_device(&board->i2c_adap, info);
	पूर्णांक rc;

	अगर (IS_ERR(client))
		वापस PTR_ERR(client);

	/* Read-to-clear alarm/पूर्णांकerrupt status */
	i2c_smbus_पढ़ो_byte_data(client, LM87_REG_ALARMS1);
	i2c_smbus_पढ़ो_byte_data(client, LM87_REG_ALARMS2);

	rc = ef4_poke_lm87(client, reg_values);
	अगर (rc)
		जाओ err;
	rc = ef4_poke_lm87(client, falcon_lm87_common_regs);
	अगर (rc)
		जाओ err;

	board->hwmon_client = client;
	वापस 0;

err:
	i2c_unरेजिस्टर_device(client);
	वापस rc;
पूर्ण

अटल व्योम ef4_fini_lm87(काष्ठा ef4_nic *efx)
अणु
	i2c_unरेजिस्टर_device(falcon_board(efx)->hwmon_client);
पूर्ण

अटल पूर्णांक ef4_check_lm87(काष्ठा ef4_nic *efx, अचिन्हित mask)
अणु
	काष्ठा i2c_client *client = falcon_board(efx)->hwmon_client;
	bool temp_crit, elec_fault, is_failure;
	u16 alarms;
	s32 reg;

	/* If link is up then करो not monitor temperature */
	अगर (EF4_WORKAROUND_7884(efx) && efx->link_state.up)
		वापस 0;

	reg = i2c_smbus_पढ़ो_byte_data(client, LM87_REG_ALARMS1);
	अगर (reg < 0)
		वापस reg;
	alarms = reg;
	reg = i2c_smbus_पढ़ो_byte_data(client, LM87_REG_ALARMS2);
	अगर (reg < 0)
		वापस reg;
	alarms |= reg << 8;
	alarms &= mask;

	temp_crit = false;
	अगर (alarms & LM87_ALARM_TEMP_INT) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client, LM87_REG_TEMP_INT);
		अगर (reg < 0)
			वापस reg;
		अगर (reg > FALCON_BOARD_TEMP_CRIT)
			temp_crit = true;
	पूर्ण
	अगर (alarms & LM87_ALARM_TEMP_EXT1) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client, LM87_REG_TEMP_EXT1);
		अगर (reg < 0)
			वापस reg;
		अगर (reg > FALCON_JUNC_TEMP_CRIT)
			temp_crit = true;
	पूर्ण
	elec_fault = alarms & ~(LM87_ALARM_TEMP_INT | LM87_ALARM_TEMP_EXT1);
	is_failure = temp_crit || elec_fault;

	अगर (alarms)
		netअगर_err(efx, hw, efx->net_dev,
			  "LM87 detected a hardware %s (status %02x:%02x)"
			  "%s%s%s%s\n",
			  is_failure ? "failure" : "problem",
			  alarms & 0xff, alarms >> 8,
			  (alarms & LM87_ALARM_TEMP_INT) ?
			  "; board is overheating" : "",
			  (alarms & LM87_ALARM_TEMP_EXT1) ?
			  "; controller is overheating" : "",
			  temp_crit ? "; reached critical temperature" : "",
			  elec_fault ? "; electrical fault" : "");

	वापस is_failure ? -दुस्फल : 0;
पूर्ण

#अन्यथा /* !CONFIG_SENSORS_LM87 */

अटल अंतरभूत पूर्णांक
ef4_init_lm87(काष्ठा ef4_nic *efx, स्थिर काष्ठा i2c_board_info *info,
	      स्थिर u8 *reg_values)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम ef4_fini_lm87(काष्ठा ef4_nic *efx)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक ef4_check_lm87(काष्ठा ef4_nic *efx, अचिन्हित mask)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SENSORS_LM87 */

/*****************************************************************************
 * Support क्रम the SFE4001 NIC.
 *
 * The SFE4001 करोes not घातer-up fully at reset due to its high घातer
 * consumption.  We control its घातer via a PCA9539 I/O expander.
 * It also has a MAX6647 temperature monitor which we expose to
 * the lm90 driver.
 *
 * This also provides minimal support क्रम reflashing the PHY, which is
 * initiated by resetting it with the FLASH_CFG_1 pin pulled करोwn.
 * On SFE4001 rev A2 and later this is connected to the 3V3X output of
 * the IO-expander.
 * We represent reflash mode as PHY_MODE_SPECIAL and make it mutually
 * exclusive with the network device being खोलो.
 */

/**************************************************************************
 * Support क्रम I2C IO Expander device on SFE4001
 */
#घोषणा	PCA9539 0x74

#घोषणा	P0_IN 0x00
#घोषणा	P0_OUT 0x02
#घोषणा	P0_INVERT 0x04
#घोषणा	P0_CONFIG 0x06

#घोषणा	P0_EN_1V0X_LBN 0
#घोषणा	P0_EN_1V0X_WIDTH 1
#घोषणा	P0_EN_1V2_LBN 1
#घोषणा	P0_EN_1V2_WIDTH 1
#घोषणा	P0_EN_2V5_LBN 2
#घोषणा	P0_EN_2V5_WIDTH 1
#घोषणा	P0_EN_3V3X_LBN 3
#घोषणा	P0_EN_3V3X_WIDTH 1
#घोषणा	P0_EN_5V_LBN 4
#घोषणा	P0_EN_5V_WIDTH 1
#घोषणा	P0_SHORTEN_JTAG_LBN 5
#घोषणा	P0_SHORTEN_JTAG_WIDTH 1
#घोषणा	P0_X_TRST_LBN 6
#घोषणा	P0_X_TRST_WIDTH 1
#घोषणा	P0_DSP_RESET_LBN 7
#घोषणा	P0_DSP_RESET_WIDTH 1

#घोषणा	P1_IN 0x01
#घोषणा	P1_OUT 0x03
#घोषणा	P1_INVERT 0x05
#घोषणा	P1_CONFIG 0x07

#घोषणा	P1_AFE_PWD_LBN 0
#घोषणा	P1_AFE_PWD_WIDTH 1
#घोषणा	P1_DSP_PWD25_LBN 1
#घोषणा	P1_DSP_PWD25_WIDTH 1
#घोषणा	P1_RESERVED_LBN 2
#घोषणा	P1_RESERVED_WIDTH 2
#घोषणा	P1_SPARE_LBN 4
#घोषणा	P1_SPARE_WIDTH 4

/* Temperature Sensor */
#घोषणा MAX664X_REG_RSL		0x02
#घोषणा MAX664X_REG_WLHO	0x0B

अटल व्योम sfe4001_घातeroff(काष्ठा ef4_nic *efx)
अणु
	काष्ठा i2c_client *ioexp_client = falcon_board(efx)->ioexp_client;
	काष्ठा i2c_client *hwmon_client = falcon_board(efx)->hwmon_client;

	/* Turn off all घातer rails and disable outमाला_दो */
	i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_OUT, 0xff);
	i2c_smbus_ग_लिखो_byte_data(ioexp_client, P1_CONFIG, 0xff);
	i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_CONFIG, 0xff);

	/* Clear any over-temperature alert */
	i2c_smbus_पढ़ो_byte_data(hwmon_client, MAX664X_REG_RSL);
पूर्ण

अटल पूर्णांक sfe4001_घातeron(काष्ठा ef4_nic *efx)
अणु
	काष्ठा i2c_client *ioexp_client = falcon_board(efx)->ioexp_client;
	काष्ठा i2c_client *hwmon_client = falcon_board(efx)->hwmon_client;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक rc;
	u8 out;

	/* Clear any previous over-temperature alert */
	rc = i2c_smbus_पढ़ो_byte_data(hwmon_client, MAX664X_REG_RSL);
	अगर (rc < 0)
		वापस rc;

	/* Enable port 0 and port 1 outमाला_दो on IO expander */
	rc = i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_CONFIG, 0x00);
	अगर (rc)
		वापस rc;
	rc = i2c_smbus_ग_लिखो_byte_data(ioexp_client, P1_CONFIG,
				       0xff & ~(1 << P1_SPARE_LBN));
	अगर (rc)
		जाओ fail_on;

	/* If PHY घातer is on, turn it all off and रुको 1 second to
	 * ensure a full reset.
	 */
	rc = i2c_smbus_पढ़ो_byte_data(ioexp_client, P0_OUT);
	अगर (rc < 0)
		जाओ fail_on;
	out = 0xff & ~((0 << P0_EN_1V2_LBN) | (0 << P0_EN_2V5_LBN) |
		       (0 << P0_EN_3V3X_LBN) | (0 << P0_EN_5V_LBN) |
		       (0 << P0_EN_1V0X_LBN));
	अगर (rc != out) अणु
		netअगर_info(efx, hw, efx->net_dev, "power-cycling PHY\n");
		rc = i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_OUT, out);
		अगर (rc)
			जाओ fail_on;
		schedule_समयout_unपूर्णांकerruptible(HZ);
	पूर्ण

	क्रम (i = 0; i < 20; ++i) अणु
		/* Turn on 1.2V, 2.5V, 3.3V and 5V घातer rails */
		out = 0xff & ~((1 << P0_EN_1V2_LBN) | (1 << P0_EN_2V5_LBN) |
			       (1 << P0_EN_3V3X_LBN) | (1 << P0_EN_5V_LBN) |
			       (1 << P0_X_TRST_LBN));
		अगर (efx->phy_mode & PHY_MODE_SPECIAL)
			out |= 1 << P0_EN_3V3X_LBN;

		rc = i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_OUT, out);
		अगर (rc)
			जाओ fail_on;
		msleep(10);

		/* Turn on 1V घातer rail */
		out &= ~(1 << P0_EN_1V0X_LBN);
		rc = i2c_smbus_ग_लिखो_byte_data(ioexp_client, P0_OUT, out);
		अगर (rc)
			जाओ fail_on;

		netअगर_info(efx, hw, efx->net_dev,
			   "waiting for DSP boot (attempt %d)...\n", i);

		/* In flash config mode, DSP करोes not turn on AFE, so
		 * just रुको 1 second.
		 */
		अगर (efx->phy_mode & PHY_MODE_SPECIAL) अणु
			schedule_समयout_unपूर्णांकerruptible(HZ);
			वापस 0;
		पूर्ण

		क्रम (j = 0; j < 10; ++j) अणु
			msleep(100);

			/* Check DSP has निश्चितed AFE घातer line */
			rc = i2c_smbus_पढ़ो_byte_data(ioexp_client, P1_IN);
			अगर (rc < 0)
				जाओ fail_on;
			अगर (rc & (1 << P1_AFE_PWD_LBN))
				वापस 0;
		पूर्ण
	पूर्ण

	netअगर_info(efx, hw, efx->net_dev, "timed out waiting for DSP boot\n");
	rc = -ETIMEDOUT;
fail_on:
	sfe4001_घातeroff(efx);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार show_phy_flash_cfg(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ef4_nic *efx = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", !!(efx->phy_mode & PHY_MODE_SPECIAL));
पूर्ण

अटल sमाप_प्रकार set_phy_flash_cfg(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ef4_nic *efx = dev_get_drvdata(dev);
	क्रमागत ef4_phy_mode old_mode, new_mode;
	पूर्णांक err;

	rtnl_lock();
	old_mode = efx->phy_mode;
	अगर (count == 0 || *buf == '0')
		new_mode = old_mode & ~PHY_MODE_SPECIAL;
	अन्यथा
		new_mode = PHY_MODE_SPECIAL;
	अगर (!((old_mode ^ new_mode) & PHY_MODE_SPECIAL)) अणु
		err = 0;
	पूर्ण अन्यथा अगर (efx->state != STATE_READY || netअगर_running(efx->net_dev)) अणु
		err = -EBUSY;
	पूर्ण अन्यथा अणु
		/* Reset the PHY, reconfigure the MAC and enable/disable
		 * MAC stats accordingly. */
		efx->phy_mode = new_mode;
		अगर (new_mode & PHY_MODE_SPECIAL)
			falcon_stop_nic_stats(efx);
		err = sfe4001_घातeron(efx);
		अगर (!err)
			err = ef4_reconfigure_port(efx);
		अगर (!(new_mode & PHY_MODE_SPECIAL))
			falcon_start_nic_stats(efx);
	पूर्ण
	rtnl_unlock();

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(phy_flash_cfg, 0644, show_phy_flash_cfg, set_phy_flash_cfg);

अटल व्योम sfe4001_fini(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);

	netअगर_info(efx, drv, efx->net_dev, "%s\n", __func__);

	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_phy_flash_cfg);
	sfe4001_घातeroff(efx);
	i2c_unरेजिस्टर_device(board->ioexp_client);
	i2c_unरेजिस्टर_device(board->hwmon_client);
पूर्ण

अटल पूर्णांक sfe4001_check_hw(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_nic_data *nic_data = efx->nic_data;
	s32 status;

	/* If XAUI link is up then करो not monitor */
	अगर (EF4_WORKAROUND_7884(efx) && !nic_data->xmac_poll_required)
		वापस 0;

	/* Check the घातered status of the PHY. Lack of घातer implies that
	 * the MAX6647 has shut करोwn घातer to it, probably due to a temp.
	 * alarm. Reading the घातer status rather than the MAX6647 status
	 * directly because the later is पढ़ो-to-clear and would thus
	 * start to घातer up the PHY again when polled, causing us to blip
	 * the घातer undesirably.
	 * We know we can पढ़ो from the IO expander because we did
	 * it during घातer-on. Assume failure now is bad news. */
	status = i2c_smbus_पढ़ो_byte_data(falcon_board(efx)->ioexp_client, P1_IN);
	अगर (status >= 0 &&
	    (status & ((1 << P1_AFE_PWD_LBN) | (1 << P1_DSP_PWD25_LBN))) != 0)
		वापस 0;

	/* Use board घातer control, not PHY घातer control */
	sfe4001_घातeroff(efx);
	efx->phy_mode = PHY_MODE_OFF;

	वापस (status < 0) ? -EIO : -दुस्फल;
पूर्ण

अटल स्थिर काष्ठा i2c_board_info sfe4001_hwmon_info = अणु
	I2C_BOARD_INFO("max6647", 0x4e),
पूर्ण;

/* This board uses an I2C expander to provider घातer to the PHY, which needs to
 * be turned on beक्रमe the PHY can be used.
 * Context: Process context, rtnl lock held
 */
अटल पूर्णांक sfe4001_init(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);
	पूर्णांक rc;

#अगर IS_ENABLED(CONFIG_SENSORS_LM90)
	board->hwmon_client =
		i2c_new_client_device(&board->i2c_adap, &sfe4001_hwmon_info);
#अन्यथा
	board->hwmon_client =
		i2c_new_dummy_device(&board->i2c_adap, sfe4001_hwmon_info.addr);
#पूर्ण_अगर
	अगर (IS_ERR(board->hwmon_client))
		वापस PTR_ERR(board->hwmon_client);

	/* Raise board/PHY high limit from 85 to 90 degrees Celsius */
	rc = i2c_smbus_ग_लिखो_byte_data(board->hwmon_client,
				       MAX664X_REG_WLHO, 90);
	अगर (rc)
		जाओ fail_hwmon;

	board->ioexp_client = i2c_new_dummy_device(&board->i2c_adap, PCA9539);
	अगर (IS_ERR(board->ioexp_client)) अणु
		rc = PTR_ERR(board->ioexp_client);
		जाओ fail_hwmon;
	पूर्ण

	अगर (efx->phy_mode & PHY_MODE_SPECIAL) अणु
		/* PHY won't generate a 156.25 MHz घड़ी and MAC stats fetch
		 * will fail. */
		falcon_stop_nic_stats(efx);
	पूर्ण
	rc = sfe4001_घातeron(efx);
	अगर (rc)
		जाओ fail_ioexp;

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_phy_flash_cfg);
	अगर (rc)
		जाओ fail_on;

	netअगर_info(efx, hw, efx->net_dev, "PHY is powered on\n");
	वापस 0;

fail_on:
	sfe4001_घातeroff(efx);
fail_ioexp:
	i2c_unरेजिस्टर_device(board->ioexp_client);
fail_hwmon:
	i2c_unरेजिस्टर_device(board->hwmon_client);
	वापस rc;
पूर्ण

/*****************************************************************************
 * Support क्रम the SFE4002
 *
 */
अटल u8 sfe4002_lm87_channel = 0x03; /* use AIN not FAN inमाला_दो */

अटल स्थिर u8 sfe4002_lm87_regs[] = अणु
	LM87_IN_LIMITS(0, 0x7c, 0x99),		/* 2.5V:  1.8V +/- 10% */
	LM87_IN_LIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	LM87_IN_LIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	LM87_IN_LIMITS(3, 0xac, 0xd4),		/* 5V:    5.0V +/- 10% */
	LM87_IN_LIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	LM87_IN_LIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	LM87_AIN_LIMITS(0, 0x98, 0xbb),		/* AIN1:  1.66V +/- 10% */
	LM87_AIN_LIMITS(1, 0x8a, 0xa9),		/* AIN2:  1.5V +/- 10% */
	LM87_TEMP_INT_LIMITS(0, 80 + FALCON_BOARD_TEMP_BIAS),
	LM87_TEMP_EXT1_LIMITS(0, FALCON_JUNC_TEMP_MAX),
	0
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info sfe4002_hwmon_info = अणु
	I2C_BOARD_INFO("lm87", 0x2e),
	.platक्रमm_data	= &sfe4002_lm87_channel,
पूर्ण;

/****************************************************************************/
/* LED allocations. Note that on rev A0 boards the schematic and the reality
 * dअगरfer: red and green are swapped. Below is the fixed (A1) layout (there
 * are only 3 A0 boards in existence, so no real reason to make this
 * conditional).
 */
#घोषणा SFE4002_FAULT_LED (2)	/* Red */
#घोषणा SFE4002_RX_LED    (0)	/* Green */
#घोषणा SFE4002_TX_LED    (1)	/* Amber */

अटल व्योम sfe4002_init_phy(काष्ठा ef4_nic *efx)
अणु
	/* Set the TX and RX LEDs to reflect status and activity, and the
	 * fault LED off */
	falcon_qt202x_set_led(efx, SFE4002_TX_LED,
			      QUAKE_LED_TXLINK | QUAKE_LED_LINK_ACTSTAT);
	falcon_qt202x_set_led(efx, SFE4002_RX_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_ACTSTAT);
	falcon_qt202x_set_led(efx, SFE4002_FAULT_LED, QUAKE_LED_OFF);
पूर्ण

अटल व्योम sfe4002_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode)
अणु
	falcon_qt202x_set_led(
		efx, SFE4002_FAULT_LED,
		(mode == EF4_LED_ON) ? QUAKE_LED_ON : QUAKE_LED_OFF);
पूर्ण

अटल पूर्णांक sfe4002_check_hw(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);

	/* A0 board rev. 4002s report a temperature fault the whole समय
	 * (bad sensor) so we mask it out. */
	अचिन्हित alarm_mask =
		(board->major == 0 && board->minor == 0) ?
		~LM87_ALARM_TEMP_EXT1 : ~0;

	वापस ef4_check_lm87(efx, alarm_mask);
पूर्ण

अटल पूर्णांक sfe4002_init(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_init_lm87(efx, &sfe4002_hwmon_info, sfe4002_lm87_regs);
पूर्ण

/*****************************************************************************
 * Support क्रम the SFN4112F
 *
 */
अटल u8 sfn4112f_lm87_channel = 0x03; /* use AIN not FAN inमाला_दो */

अटल स्थिर u8 sfn4112f_lm87_regs[] = अणु
	LM87_IN_LIMITS(0, 0x7c, 0x99),		/* 2.5V:  1.8V +/- 10% */
	LM87_IN_LIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	LM87_IN_LIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	LM87_IN_LIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	LM87_IN_LIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	LM87_AIN_LIMITS(1, 0x8a, 0xa9),		/* AIN2:  1.5V +/- 10% */
	LM87_TEMP_INT_LIMITS(0, 60 + FALCON_BOARD_TEMP_BIAS),
	LM87_TEMP_EXT1_LIMITS(0, FALCON_JUNC_TEMP_MAX),
	0
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info sfn4112f_hwmon_info = अणु
	I2C_BOARD_INFO("lm87", 0x2e),
	.platक्रमm_data	= &sfn4112f_lm87_channel,
पूर्ण;

#घोषणा SFN4112F_ACT_LED	0
#घोषणा SFN4112F_LINK_LED	1

अटल व्योम sfn4112f_init_phy(काष्ठा ef4_nic *efx)
अणु
	falcon_qt202x_set_led(efx, SFN4112F_ACT_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_ACT);
	falcon_qt202x_set_led(efx, SFN4112F_LINK_LED,
			      QUAKE_LED_RXLINK | QUAKE_LED_LINK_STAT);
पूर्ण

अटल व्योम sfn4112f_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode)
अणु
	पूर्णांक reg;

	चयन (mode) अणु
	हाल EF4_LED_OFF:
		reg = QUAKE_LED_OFF;
		अवरोध;
	हाल EF4_LED_ON:
		reg = QUAKE_LED_ON;
		अवरोध;
	शेष:
		reg = QUAKE_LED_RXLINK | QUAKE_LED_LINK_STAT;
		अवरोध;
	पूर्ण

	falcon_qt202x_set_led(efx, SFN4112F_LINK_LED, reg);
पूर्ण

अटल पूर्णांक sfn4112f_check_hw(काष्ठा ef4_nic *efx)
अणु
	/* Mask out unused sensors */
	वापस ef4_check_lm87(efx, ~0x48);
पूर्ण

अटल पूर्णांक sfn4112f_init(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_init_lm87(efx, &sfn4112f_hwmon_info, sfn4112f_lm87_regs);
पूर्ण

/*****************************************************************************
 * Support क्रम the SFE4003
 *
 */
अटल u8 sfe4003_lm87_channel = 0x03; /* use AIN not FAN inमाला_दो */

अटल स्थिर u8 sfe4003_lm87_regs[] = अणु
	LM87_IN_LIMITS(0, 0x67, 0x7f),		/* 2.5V:  1.5V +/- 10% */
	LM87_IN_LIMITS(1, 0x4c, 0x5e),		/* Vccp1: 1.2V +/- 10% */
	LM87_IN_LIMITS(2, 0xac, 0xd4),		/* 3.3V:  3.3V +/- 10% */
	LM87_IN_LIMITS(4, 0xac, 0xe0),		/* 12V:   10.8-14V */
	LM87_IN_LIMITS(5, 0x3f, 0x4f),		/* Vccp2: 1.0V +/- 10% */
	LM87_TEMP_INT_LIMITS(0, 70 + FALCON_BOARD_TEMP_BIAS),
	0
पूर्ण;

अटल स्थिर काष्ठा i2c_board_info sfe4003_hwmon_info = अणु
	I2C_BOARD_INFO("lm87", 0x2e),
	.platक्रमm_data	= &sfe4003_lm87_channel,
पूर्ण;

/* Board-specअगरic LED info. */
#घोषणा SFE4003_RED_LED_GPIO	11
#घोषणा SFE4003_LED_ON		1
#घोषणा SFE4003_LED_OFF		0

अटल व्योम sfe4003_set_id_led(काष्ठा ef4_nic *efx, क्रमागत ef4_led_mode mode)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);

	/* The LEDs were not wired to GPIOs beक्रमe A3 */
	अगर (board->minor < 3 && board->major == 0)
		वापस;

	falcon_txc_set_gpio_val(
		efx, SFE4003_RED_LED_GPIO,
		(mode == EF4_LED_ON) ? SFE4003_LED_ON : SFE4003_LED_OFF);
पूर्ण

अटल व्योम sfe4003_init_phy(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);

	/* The LEDs were not wired to GPIOs beक्रमe A3 */
	अगर (board->minor < 3 && board->major == 0)
		वापस;

	falcon_txc_set_gpio_dir(efx, SFE4003_RED_LED_GPIO, TXC_GPIO_सूची_OUTPUT);
	falcon_txc_set_gpio_val(efx, SFE4003_RED_LED_GPIO, SFE4003_LED_OFF);
पूर्ण

अटल पूर्णांक sfe4003_check_hw(काष्ठा ef4_nic *efx)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);

	/* A0/A1/A2 board rev. 4003s  report a temperature fault the whole समय
	 * (bad sensor) so we mask it out. */
	अचिन्हित alarm_mask =
		(board->major == 0 && board->minor <= 2) ?
		~LM87_ALARM_TEMP_EXT1 : ~0;

	वापस ef4_check_lm87(efx, alarm_mask);
पूर्ण

अटल पूर्णांक sfe4003_init(काष्ठा ef4_nic *efx)
अणु
	वापस ef4_init_lm87(efx, &sfe4003_hwmon_info, sfe4003_lm87_regs);
पूर्ण

अटल स्थिर काष्ठा falcon_board_type board_types[] = अणु
	अणु
		.id		= FALCON_BOARD_SFE4001,
		.init		= sfe4001_init,
		.init_phy	= ef4_port_dummy_op_व्योम,
		.fini		= sfe4001_fini,
		.set_id_led	= tenxpress_set_id_led,
		.monitor	= sfe4001_check_hw,
	पूर्ण,
	अणु
		.id		= FALCON_BOARD_SFE4002,
		.init		= sfe4002_init,
		.init_phy	= sfe4002_init_phy,
		.fini		= ef4_fini_lm87,
		.set_id_led	= sfe4002_set_id_led,
		.monitor	= sfe4002_check_hw,
	पूर्ण,
	अणु
		.id		= FALCON_BOARD_SFE4003,
		.init		= sfe4003_init,
		.init_phy	= sfe4003_init_phy,
		.fini		= ef4_fini_lm87,
		.set_id_led	= sfe4003_set_id_led,
		.monitor	= sfe4003_check_hw,
	पूर्ण,
	अणु
		.id		= FALCON_BOARD_SFN4112F,
		.init		= sfn4112f_init,
		.init_phy	= sfn4112f_init_phy,
		.fini		= ef4_fini_lm87,
		.set_id_led	= sfn4112f_set_id_led,
		.monitor	= sfn4112f_check_hw,
	पूर्ण,
पूर्ण;

पूर्णांक falcon_probe_board(काष्ठा ef4_nic *efx, u16 revision_info)
अणु
	काष्ठा falcon_board *board = falcon_board(efx);
	u8 type_id = FALCON_BOARD_TYPE(revision_info);
	पूर्णांक i;

	board->major = FALCON_BOARD_MAJOR(revision_info);
	board->minor = FALCON_BOARD_MINOR(revision_info);

	क्रम (i = 0; i < ARRAY_SIZE(board_types); i++)
		अगर (board_types[i].id == type_id)
			board->type = &board_types[i];

	अगर (board->type) अणु
		वापस 0;
	पूर्ण अन्यथा अणु
		netअगर_err(efx, probe, efx->net_dev, "unknown board type %d\n",
			  type_id);
		वापस -ENODEV;
	पूर्ण
पूर्ण
