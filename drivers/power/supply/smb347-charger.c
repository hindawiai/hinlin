<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Summit Microelectronics SMB347 Battery Charger Driver
 *
 * Copyright (C) 2011, Intel Corporation
 *
 * Authors: Bruce E. Robertson <bruce.e.robertson@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>

#समावेश <dt-bindings/घातer/summit,smb347-अक्षरger.h>

/* Use the शेष compensation method */
#घोषणा SMB3XX_SOFT_TEMP_COMPENSATE_DEFAULT -1

/* Use शेष factory programmed value क्रम hard/soft temperature limit */
#घोषणा SMB3XX_TEMP_USE_DEFAULT		-273

/*
 * Configuration रेजिस्टरs. These are mirrored to अस्थिर RAM and can be
 * written once %CMD_A_ALLOW_WRITE is set in %CMD_A रेजिस्टर. They will be
 * reloaded from non-अस्थिर रेजिस्टरs after POR.
 */
#घोषणा CFG_CHARGE_CURRENT			0x00
#घोषणा CFG_CHARGE_CURRENT_FCC_MASK		0xe0
#घोषणा CFG_CHARGE_CURRENT_FCC_SHIFT		5
#घोषणा CFG_CHARGE_CURRENT_PCC_MASK		0x18
#घोषणा CFG_CHARGE_CURRENT_PCC_SHIFT		3
#घोषणा CFG_CHARGE_CURRENT_TC_MASK		0x07
#घोषणा CFG_CURRENT_LIMIT			0x01
#घोषणा CFG_CURRENT_LIMIT_DC_MASK		0xf0
#घोषणा CFG_CURRENT_LIMIT_DC_SHIFT		4
#घोषणा CFG_CURRENT_LIMIT_USB_MASK		0x0f
#घोषणा CFG_FLOAT_VOLTAGE			0x03
#घोषणा CFG_FLOAT_VOLTAGE_FLOAT_MASK		0x3f
#घोषणा CFG_FLOAT_VOLTAGE_THRESHOLD_MASK	0xc0
#घोषणा CFG_FLOAT_VOLTAGE_THRESHOLD_SHIFT	6
#घोषणा CFG_STAT				0x05
#घोषणा CFG_STAT_DISABLED			BIT(5)
#घोषणा CFG_STAT_ACTIVE_HIGH			BIT(7)
#घोषणा CFG_PIN					0x06
#घोषणा CFG_PIN_EN_CTRL_MASK			0x60
#घोषणा CFG_PIN_EN_CTRL_ACTIVE_HIGH		0x40
#घोषणा CFG_PIN_EN_CTRL_ACTIVE_LOW		0x60
#घोषणा CFG_PIN_EN_APSD_IRQ			BIT(1)
#घोषणा CFG_PIN_EN_CHARGER_ERROR		BIT(2)
#घोषणा CFG_THERM				0x07
#घोषणा CFG_THERM_SOFT_HOT_COMPENSATION_MASK	0x03
#घोषणा CFG_THERM_SOFT_HOT_COMPENSATION_SHIFT	0
#घोषणा CFG_THERM_SOFT_COLD_COMPENSATION_MASK	0x0c
#घोषणा CFG_THERM_SOFT_COLD_COMPENSATION_SHIFT	2
#घोषणा CFG_THERM_MONITOR_DISABLED		BIT(4)
#घोषणा CFG_SYSOK				0x08
#घोषणा CFG_SYSOK_SUSPEND_HARD_LIMIT_DISABLED	BIT(2)
#घोषणा CFG_OTHER				0x09
#घोषणा CFG_OTHER_RID_MASK			0xc0
#घोषणा CFG_OTHER_RID_ENABLED_AUTO_OTG		0xc0
#घोषणा CFG_OTG					0x0a
#घोषणा CFG_OTG_TEMP_THRESHOLD_MASK		0x30
#घोषणा CFG_OTG_TEMP_THRESHOLD_SHIFT		4
#घोषणा CFG_OTG_CC_COMPENSATION_MASK		0xc0
#घोषणा CFG_OTG_CC_COMPENSATION_SHIFT		6
#घोषणा CFG_TEMP_LIMIT				0x0b
#घोषणा CFG_TEMP_LIMIT_SOFT_HOT_MASK		0x03
#घोषणा CFG_TEMP_LIMIT_SOFT_HOT_SHIFT		0
#घोषणा CFG_TEMP_LIMIT_SOFT_COLD_MASK		0x0c
#घोषणा CFG_TEMP_LIMIT_SOFT_COLD_SHIFT		2
#घोषणा CFG_TEMP_LIMIT_HARD_HOT_MASK		0x30
#घोषणा CFG_TEMP_LIMIT_HARD_HOT_SHIFT		4
#घोषणा CFG_TEMP_LIMIT_HARD_COLD_MASK		0xc0
#घोषणा CFG_TEMP_LIMIT_HARD_COLD_SHIFT		6
#घोषणा CFG_FAULT_IRQ				0x0c
#घोषणा CFG_FAULT_IRQ_DCIN_UV			BIT(2)
#घोषणा CFG_STATUS_IRQ				0x0d
#घोषणा CFG_STATUS_IRQ_TERMINATION_OR_TAPER	BIT(4)
#घोषणा CFG_STATUS_IRQ_CHARGE_TIMEOUT		BIT(7)
#घोषणा CFG_ADDRESS				0x0e

/* Command रेजिस्टरs */
#घोषणा CMD_A					0x30
#घोषणा CMD_A_CHG_ENABLED			BIT(1)
#घोषणा CMD_A_SUSPEND_ENABLED			BIT(2)
#घोषणा CMD_A_ALLOW_WRITE			BIT(7)
#घोषणा CMD_B					0x31
#घोषणा CMD_C					0x33

/* Interrupt Status रेजिस्टरs */
#घोषणा IRQSTAT_A				0x35
#घोषणा IRQSTAT_C				0x37
#घोषणा IRQSTAT_C_TERMINATION_STAT		BIT(0)
#घोषणा IRQSTAT_C_TERMINATION_IRQ		BIT(1)
#घोषणा IRQSTAT_C_TAPER_IRQ			BIT(3)
#घोषणा IRQSTAT_D				0x38
#घोषणा IRQSTAT_D_CHARGE_TIMEOUT_STAT		BIT(2)
#घोषणा IRQSTAT_D_CHARGE_TIMEOUT_IRQ		BIT(3)
#घोषणा IRQSTAT_E				0x39
#घोषणा IRQSTAT_E_USBIN_UV_STAT			BIT(0)
#घोषणा IRQSTAT_E_USBIN_UV_IRQ			BIT(1)
#घोषणा IRQSTAT_E_DCIN_UV_STAT			BIT(4)
#घोषणा IRQSTAT_E_DCIN_UV_IRQ			BIT(5)
#घोषणा IRQSTAT_F				0x3a

/* Status रेजिस्टरs */
#घोषणा STAT_A					0x3b
#घोषणा STAT_A_FLOAT_VOLTAGE_MASK		0x3f
#घोषणा STAT_B					0x3c
#घोषणा STAT_C					0x3d
#घोषणा STAT_C_CHG_ENABLED			BIT(0)
#घोषणा STAT_C_HOLDOFF_STAT			BIT(3)
#घोषणा STAT_C_CHG_MASK				0x06
#घोषणा STAT_C_CHG_SHIFT			1
#घोषणा STAT_C_CHG_TERM				BIT(5)
#घोषणा STAT_C_CHARGER_ERROR			BIT(6)
#घोषणा STAT_E					0x3f

#घोषणा SMB347_MAX_REGISTER			0x3f

/**
 * काष्ठा smb347_अक्षरger - smb347 अक्षरger instance
 * @dev: poपूर्णांकer to device
 * @regmap: poपूर्णांकer to driver regmap
 * @मुख्यs: घातer_supply instance क्रम AC/DC घातer
 * @usb: घातer_supply instance क्रम USB घातer
 * @id: SMB अक्षरger ID
 * @मुख्यs_online: is AC/DC input connected
 * @usb_online: is USB input connected
 * @अक्षरging_enabled: is अक्षरging enabled
 * @irq_unsupported: is पूर्णांकerrupt unsupported by SMB hardware
 * @max_अक्षरge_current: maximum current (in uA) the battery can be अक्षरged
 * @max_अक्षरge_voltage: maximum voltage (in uV) the battery can be अक्षरged
 * @pre_अक्षरge_current: current (in uA) to use in pre-अक्षरging phase
 * @termination_current: current (in uA) used to determine when the
 *			 अक्षरging cycle terminates
 * @pre_to_fast_voltage: voltage (in uV) treshold used क्रम transitioning to
 *			 pre-अक्षरge to fast अक्षरge mode
 * @मुख्यs_current_limit: maximum input current drawn from AC/DC input (in uA)
 * @usb_hc_current_limit: maximum input high current (in uA) drawn from USB
 *			  input
 * @chip_temp_threshold: die temperature where device starts limiting अक्षरge
 *			 current [%100 - %130] (in degree C)
 * @soft_cold_temp_limit: soft cold temperature limit [%0 - %15] (in degree C),
 *			  granularity is 5 deg C.
 * @soft_hot_temp_limit: soft hot temperature limit [%40 - %55] (in degree  C),
 *			 granularity is 5 deg C.
 * @hard_cold_temp_limit: hard cold temperature limit [%-5 - %10] (in degree C),
 *			  granularity is 5 deg C.
 * @hard_hot_temp_limit: hard hot temperature limit [%50 - %65] (in degree C),
 *			 granularity is 5 deg C.
 * @suspend_on_hard_temp_limit: suspend अक्षरging when hard limit is hit
 * @soft_temp_limit_compensation: compensation method when soft temperature
 *				  limit is hit
 * @अक्षरge_current_compensation: current (in uA) क्रम अक्षरging compensation
 *				 current when temperature hits soft limits
 * @use_मुख्यs: AC/DC input can be used
 * @use_usb: USB input can be used
 * @use_usb_otg: USB OTG output can be used (not implemented yet)
 * @enable_control: how अक्षरging enable/disable is controlled
 *		    (driver/pin controls)
 *
 * @use_मुख्य, @use_usb, and @use_usb_otg are means to enable/disable
 * hardware support क्रम these. This is useful when we want to have क्रम
 * example OTG अक्षरging controlled via OTG transceiver driver and not by
 * the SMB347 hardware.
 *
 * Hard and soft temperature limit values are given as described in the
 * device data sheet and assuming NTC beta value is %3750. Even अगर this is
 * not the हाल, these values should be used. They can be mapped to the
 * corresponding NTC beta values with the help of table %2 in the data
 * sheet. So क्रम example अगर NTC beta is %3375 and we want to program hard
 * hot limit to be %53 deg C, @hard_hot_temp_limit should be set to %50.
 *
 * If zero value is given in any of the current and voltage values, the
 * factory programmed शेष will be used. For soft/hard temperature
 * values, pass in %SMB3XX_TEMP_USE_DEFAULT instead.
 */
काष्ठा smb347_अक्षरger अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*regmap;
	काष्ठा घातer_supply	*मुख्यs;
	काष्ठा घातer_supply	*usb;
	अचिन्हित पूर्णांक		id;
	bool			मुख्यs_online;
	bool			usb_online;
	bool			अक्षरging_enabled;
	bool			irq_unsupported;

	अचिन्हित पूर्णांक		max_अक्षरge_current;
	अचिन्हित पूर्णांक		max_अक्षरge_voltage;
	अचिन्हित पूर्णांक		pre_अक्षरge_current;
	अचिन्हित पूर्णांक		termination_current;
	अचिन्हित पूर्णांक		pre_to_fast_voltage;
	अचिन्हित पूर्णांक		मुख्यs_current_limit;
	अचिन्हित पूर्णांक		usb_hc_current_limit;
	अचिन्हित पूर्णांक		chip_temp_threshold;
	पूर्णांक			soft_cold_temp_limit;
	पूर्णांक			soft_hot_temp_limit;
	पूर्णांक			hard_cold_temp_limit;
	पूर्णांक			hard_hot_temp_limit;
	bool			suspend_on_hard_temp_limit;
	अचिन्हित पूर्णांक		soft_temp_limit_compensation;
	अचिन्हित पूर्णांक		अक्षरge_current_compensation;
	bool			use_मुख्यs;
	bool			use_usb;
	bool			use_usb_otg;
	अचिन्हित पूर्णांक		enable_control;
पूर्ण;

क्रमागत smb_अक्षरger_chipid अणु
	SMB345,
	SMB347,
	SMB358,
	NUM_CHIP_TYPES,
पूर्ण;

/* Fast अक्षरge current in uA */
अटल स्थिर अचिन्हित पूर्णांक fcc_tbl[NUM_CHIP_TYPES][8] = अणु
	[SMB345] = अणु  200000,  450000,  600000,  900000,
		     1300000, 1500000, 1800000, 2000000 पूर्ण,
	[SMB347] = अणु  700000,  900000, 1200000, 1500000,
		     1800000, 2000000, 2200000, 2500000 पूर्ण,
	[SMB358] = अणु  200000,  450000,  600000,  900000,
		     1300000, 1500000, 1800000, 2000000 पूर्ण,
पूर्ण;
/* Pre-अक्षरge current in uA */
अटल स्थिर अचिन्हित पूर्णांक pcc_tbl[NUM_CHIP_TYPES][4] = अणु
	[SMB345] = अणु 150000, 250000, 350000, 450000 पूर्ण,
	[SMB347] = अणु 100000, 150000, 200000, 250000 पूर्ण,
	[SMB358] = अणु 150000, 250000, 350000, 450000 पूर्ण,
पूर्ण;

/* Termination current in uA */
अटल स्थिर अचिन्हित पूर्णांक tc_tbl[NUM_CHIP_TYPES][8] = अणु
	[SMB345] = अणु  30000,  40000,  60000,  80000,
		     100000, 125000, 150000, 200000 पूर्ण,
	[SMB347] = अणु  37500,  50000, 100000, 150000,
		     200000, 250000, 500000, 600000 पूर्ण,
	[SMB358] = अणु  30000,  40000,  60000,  80000,
		     100000, 125000, 150000, 200000 पूर्ण,
पूर्ण;

/* Input current limit in uA */
अटल स्थिर अचिन्हित पूर्णांक icl_tbl[NUM_CHIP_TYPES][10] = अणु
	[SMB345] = अणु  300000,  500000,  700000, 1000000, 1500000,
		     1800000, 2000000, 2000000, 2000000, 2000000 पूर्ण,
	[SMB347] = अणु  300000,  500000,  700000,  900000, 1200000,
		     1500000, 1800000, 2000000, 2200000, 2500000 पूर्ण,
	[SMB358] = अणु  300000,  500000,  700000, 1000000, 1500000,
		     1800000, 2000000, 2000000, 2000000, 2000000 पूर्ण,
पूर्ण;

/* Charge current compensation in uA */
अटल स्थिर अचिन्हित पूर्णांक ccc_tbl[NUM_CHIP_TYPES][4] = अणु
	[SMB345] = अणु  200000,  450000,  600000,  900000 पूर्ण,
	[SMB347] = अणु  250000,  700000,  900000, 1200000 पूर्ण,
	[SMB358] = अणु  200000,  450000,  600000,  900000 पूर्ण,
पूर्ण;

/* Convert रेजिस्टर value to current using lookup table */
अटल पूर्णांक hw_to_current(स्थिर अचिन्हित पूर्णांक *tbl, माप_प्रकार size, अचिन्हित पूर्णांक val)
अणु
	अगर (val >= size)
		वापस -EINVAL;
	वापस tbl[val];
पूर्ण

/* Convert current to रेजिस्टर value using lookup table */
अटल पूर्णांक current_to_hw(स्थिर अचिन्हित पूर्णांक *tbl, माप_प्रकार size, अचिन्हित पूर्णांक val)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size; i++)
		अगर (val < tbl[i])
			अवरोध;
	वापस i > 0 ? i - 1 : -EINVAL;
पूर्ण

/**
 * smb347_update_ps_status - refreshes the घातer source status
 * @smb: poपूर्णांकer to smb347 अक्षरger instance
 *
 * Function checks whether any घातer source is connected to the अक्षरger and
 * updates पूर्णांकernal state accordingly. If there is a change to previous state
 * function वापसs %1, otherwise %0 and negative त्रुटि_सं in हाल of errror.
 */
अटल पूर्णांक smb347_update_ps_status(काष्ठा smb347_अक्षरger *smb)
अणु
	bool usb = false;
	bool dc = false;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(smb->regmap, IRQSTAT_E, &val);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Dc and usb are set depending on whether they are enabled in
	 * platक्रमm data _and_ whether corresponding undervoltage is set.
	 */
	अगर (smb->use_मुख्यs)
		dc = !(val & IRQSTAT_E_DCIN_UV_STAT);
	अगर (smb->use_usb)
		usb = !(val & IRQSTAT_E_USBIN_UV_STAT);

	ret = smb->मुख्यs_online != dc || smb->usb_online != usb;
	smb->मुख्यs_online = dc;
	smb->usb_online = usb;

	वापस ret;
पूर्ण

/*
 * smb347_is_ps_online - वापसs whether input घातer source is connected
 * @smb: poपूर्णांकer to smb347 अक्षरger instance
 *
 * Returns %true अगर input घातer source is connected. Note that this is
 * dependent on what platक्रमm has configured क्रम usable घातer sources. For
 * example अगर USB is disabled, this will वापस %false even अगर the USB cable
 * is connected.
 */
अटल bool smb347_is_ps_online(काष्ठा smb347_अक्षरger *smb)
अणु
	वापस smb->usb_online || smb->मुख्यs_online;
पूर्ण

/**
 * smb347_अक्षरging_status - वापसs status of अक्षरging
 * @smb: poपूर्णांकer to smb347 अक्षरger instance
 *
 * Function वापसs अक्षरging status. %0 means no अक्षरging is in progress,
 * %1 means pre-अक्षरging, %2 fast-अक्षरging and %3 taper-अक्षरging.
 */
अटल पूर्णांक smb347_अक्षरging_status(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	अगर (!smb347_is_ps_online(smb))
		वापस 0;

	ret = regmap_पढ़ो(smb->regmap, STAT_C, &val);
	अगर (ret < 0)
		वापस 0;

	वापस (val & STAT_C_CHG_MASK) >> STAT_C_CHG_SHIFT;
पूर्ण

अटल पूर्णांक smb347_अक्षरging_set(काष्ठा smb347_अक्षरger *smb, bool enable)
अणु
	पूर्णांक ret = 0;

	अगर (smb->enable_control != SMB3XX_CHG_ENABLE_SW) अणु
		dev_dbg(smb->dev, "charging enable/disable in SW disabled\n");
		वापस 0;
	पूर्ण

	अगर (smb->अक्षरging_enabled != enable) अणु
		ret = regmap_update_bits(smb->regmap, CMD_A, CMD_A_CHG_ENABLED,
					 enable ? CMD_A_CHG_ENABLED : 0);
		अगर (!ret)
			smb->अक्षरging_enabled = enable;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक smb347_अक्षरging_enable(काष्ठा smb347_अक्षरger *smb)
अणु
	वापस smb347_अक्षरging_set(smb, true);
पूर्ण

अटल अंतरभूत पूर्णांक smb347_अक्षरging_disable(काष्ठा smb347_अक्षरger *smb)
अणु
	वापस smb347_अक्षरging_set(smb, false);
पूर्ण

अटल पूर्णांक smb347_start_stop_अक्षरging(काष्ठा smb347_अक्षरger *smb)
अणु
	पूर्णांक ret;

	/*
	 * Depending on whether valid घातer source is connected or not, we
	 * disable or enable the अक्षरging. We करो it manually because it
	 * depends on how the platक्रमm has configured the valid inमाला_दो.
	 */
	अगर (smb347_is_ps_online(smb)) अणु
		ret = smb347_अक्षरging_enable(smb);
		अगर (ret < 0)
			dev_err(smb->dev, "failed to enable charging\n");
	पूर्ण अन्यथा अणु
		ret = smb347_अक्षरging_disable(smb);
		अगर (ret < 0)
			dev_err(smb->dev, "failed to disable charging\n");
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smb347_set_अक्षरge_current(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक id = smb->id;
	पूर्णांक ret;

	अगर (smb->max_अक्षरge_current) अणु
		ret = current_to_hw(fcc_tbl[id], ARRAY_SIZE(fcc_tbl[id]),
				    smb->max_अक्षरge_current);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_FCC_MASK,
					 ret << CFG_CHARGE_CURRENT_FCC_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->pre_अक्षरge_current) अणु
		ret = current_to_hw(pcc_tbl[id], ARRAY_SIZE(pcc_tbl[id]),
				    smb->pre_अक्षरge_current);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_PCC_MASK,
					 ret << CFG_CHARGE_CURRENT_PCC_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->termination_current) अणु
		ret = current_to_hw(tc_tbl[id], ARRAY_SIZE(tc_tbl[id]),
				    smb->termination_current);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_TC_MASK, ret);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb347_set_current_limits(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक id = smb->id;
	पूर्णांक ret;

	अगर (smb->मुख्यs_current_limit) अणु
		ret = current_to_hw(icl_tbl[id], ARRAY_SIZE(icl_tbl[id]),
				    smb->मुख्यs_current_limit);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_CURRENT_LIMIT,
					 CFG_CURRENT_LIMIT_DC_MASK,
					 ret << CFG_CURRENT_LIMIT_DC_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->usb_hc_current_limit) अणु
		ret = current_to_hw(icl_tbl[id], ARRAY_SIZE(icl_tbl[id]),
				    smb->usb_hc_current_limit);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_CURRENT_LIMIT,
					 CFG_CURRENT_LIMIT_USB_MASK, ret);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb347_set_voltage_limits(काष्ठा smb347_अक्षरger *smb)
अणु
	पूर्णांक ret;

	अगर (smb->pre_to_fast_voltage) अणु
		ret = smb->pre_to_fast_voltage;

		/* uV */
		ret = clamp_val(ret, 2400000, 3000000) - 2400000;
		ret /= 200000;

		ret = regmap_update_bits(smb->regmap, CFG_FLOAT_VOLTAGE,
				CFG_FLOAT_VOLTAGE_THRESHOLD_MASK,
				ret << CFG_FLOAT_VOLTAGE_THRESHOLD_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->max_अक्षरge_voltage) अणु
		ret = smb->max_अक्षरge_voltage;

		/* uV */
		ret = clamp_val(ret, 3500000, 4500000) - 3500000;
		ret /= 20000;

		ret = regmap_update_bits(smb->regmap, CFG_FLOAT_VOLTAGE,
					 CFG_FLOAT_VOLTAGE_FLOAT_MASK, ret);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb347_set_temp_limits(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक id = smb->id;
	bool enable_therm_monitor = false;
	पूर्णांक ret = 0;
	पूर्णांक val;

	अगर (smb->chip_temp_threshold) अणु
		val = smb->chip_temp_threshold;

		/* degree C */
		val = clamp_val(val, 100, 130) - 100;
		val /= 10;

		ret = regmap_update_bits(smb->regmap, CFG_OTG,
					 CFG_OTG_TEMP_THRESHOLD_MASK,
					 val << CFG_OTG_TEMP_THRESHOLD_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->soft_cold_temp_limit != SMB3XX_TEMP_USE_DEFAULT) अणु
		val = smb->soft_cold_temp_limit;

		val = clamp_val(val, 0, 15);
		val /= 5;
		/* this goes from higher to lower so invert the value */
		val = ~val & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_SOFT_COLD_MASK,
					 val << CFG_TEMP_LIMIT_SOFT_COLD_SHIFT);
		अगर (ret < 0)
			वापस ret;

		enable_therm_monitor = true;
	पूर्ण

	अगर (smb->soft_hot_temp_limit != SMB3XX_TEMP_USE_DEFAULT) अणु
		val = smb->soft_hot_temp_limit;

		val = clamp_val(val, 40, 55) - 40;
		val /= 5;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_SOFT_HOT_MASK,
					 val << CFG_TEMP_LIMIT_SOFT_HOT_SHIFT);
		अगर (ret < 0)
			वापस ret;

		enable_therm_monitor = true;
	पूर्ण

	अगर (smb->hard_cold_temp_limit != SMB3XX_TEMP_USE_DEFAULT) अणु
		val = smb->hard_cold_temp_limit;

		val = clamp_val(val, -5, 10) + 5;
		val /= 5;
		/* this goes from higher to lower so invert the value */
		val = ~val & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_HARD_COLD_MASK,
					 val << CFG_TEMP_LIMIT_HARD_COLD_SHIFT);
		अगर (ret < 0)
			वापस ret;

		enable_therm_monitor = true;
	पूर्ण

	अगर (smb->hard_hot_temp_limit != SMB3XX_TEMP_USE_DEFAULT) अणु
		val = smb->hard_hot_temp_limit;

		val = clamp_val(val, 50, 65) - 50;
		val /= 5;

		ret = regmap_update_bits(smb->regmap, CFG_TEMP_LIMIT,
					 CFG_TEMP_LIMIT_HARD_HOT_MASK,
					 val << CFG_TEMP_LIMIT_HARD_HOT_SHIFT);
		अगर (ret < 0)
			वापस ret;

		enable_therm_monitor = true;
	पूर्ण

	/*
	 * If any of the temperature limits are set, we also enable the
	 * thermistor monitoring.
	 *
	 * When soft limits are hit, the device will start to compensate
	 * current and/or voltage depending on the configuration.
	 *
	 * When hard limit is hit, the device will suspend अक्षरging
	 * depending on the configuration.
	 */
	अगर (enable_therm_monitor) अणु
		ret = regmap_update_bits(smb->regmap, CFG_THERM,
					 CFG_THERM_MONITOR_DISABLED, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->suspend_on_hard_temp_limit) अणु
		ret = regmap_update_bits(smb->regmap, CFG_SYSOK,
				 CFG_SYSOK_SUSPEND_HARD_LIMIT_DISABLED, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->soft_temp_limit_compensation !=
	    SMB3XX_SOFT_TEMP_COMPENSATE_DEFAULT) अणु
		val = smb->soft_temp_limit_compensation & 0x3;

		ret = regmap_update_bits(smb->regmap, CFG_THERM,
				 CFG_THERM_SOFT_HOT_COMPENSATION_MASK,
				 val << CFG_THERM_SOFT_HOT_COMPENSATION_SHIFT);
		अगर (ret < 0)
			वापस ret;

		ret = regmap_update_bits(smb->regmap, CFG_THERM,
				 CFG_THERM_SOFT_COLD_COMPENSATION_MASK,
				 val << CFG_THERM_SOFT_COLD_COMPENSATION_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (smb->अक्षरge_current_compensation) अणु
		val = current_to_hw(ccc_tbl[id], ARRAY_SIZE(ccc_tbl[id]),
				    smb->अक्षरge_current_compensation);
		अगर (val < 0)
			वापस val;

		ret = regmap_update_bits(smb->regmap, CFG_OTG,
				CFG_OTG_CC_COMPENSATION_MASK,
				(val & 0x3) << CFG_OTG_CC_COMPENSATION_SHIFT);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * smb347_set_writable - enables/disables writing to non-अस्थिर रेजिस्टरs
 * @smb: poपूर्णांकer to smb347 अक्षरger instance
 *
 * You can enable/disable writing to the non-अस्थिर configuration
 * रेजिस्टरs by calling this function.
 *
 * Returns %0 on success and negative त्रुटि_सं in हाल of failure.
 */
अटल पूर्णांक smb347_set_writable(काष्ठा smb347_अक्षरger *smb, bool writable)
अणु
	वापस regmap_update_bits(smb->regmap, CMD_A, CMD_A_ALLOW_WRITE,
				  writable ? CMD_A_ALLOW_WRITE : 0);
पूर्ण

अटल पूर्णांक smb347_hw_init(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = smb347_set_writable(smb, true);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Program the platक्रमm specअगरic configuration values to the device
	 * first.
	 */
	ret = smb347_set_अक्षरge_current(smb);
	अगर (ret < 0)
		जाओ fail;

	ret = smb347_set_current_limits(smb);
	अगर (ret < 0)
		जाओ fail;

	ret = smb347_set_voltage_limits(smb);
	अगर (ret < 0)
		जाओ fail;

	ret = smb347_set_temp_limits(smb);
	अगर (ret < 0)
		जाओ fail;

	/* If USB अक्षरging is disabled we put the USB in suspend mode */
	अगर (!smb->use_usb) अणु
		ret = regmap_update_bits(smb->regmap, CMD_A,
					 CMD_A_SUSPEND_ENABLED,
					 CMD_A_SUSPEND_ENABLED);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण

	/*
	 * If configured by platक्रमm data, we enable hardware Auto-OTG
	 * support क्रम driving VBUS. Otherwise we disable it.
	 */
	ret = regmap_update_bits(smb->regmap, CFG_OTHER, CFG_OTHER_RID_MASK,
		smb->use_usb_otg ? CFG_OTHER_RID_ENABLED_AUTO_OTG : 0);
	अगर (ret < 0)
		जाओ fail;

	/*
	 * Make the अक्षरging functionality controllable by a ग_लिखो to the
	 * command रेजिस्टर unless pin control is specअगरied in the platक्रमm
	 * data.
	 */
	चयन (smb->enable_control) अणु
	हाल SMB3XX_CHG_ENABLE_PIN_ACTIVE_LOW:
		val = CFG_PIN_EN_CTRL_ACTIVE_LOW;
		अवरोध;
	हाल SMB3XX_CHG_ENABLE_PIN_ACTIVE_HIGH:
		val = CFG_PIN_EN_CTRL_ACTIVE_HIGH;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_CTRL_MASK,
				 val);
	अगर (ret < 0)
		जाओ fail;

	/* Disable Automatic Power Source Detection (APSD) पूर्णांकerrupt. */
	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_APSD_IRQ, 0);
	अगर (ret < 0)
		जाओ fail;

	ret = smb347_update_ps_status(smb);
	अगर (ret < 0)
		जाओ fail;

	ret = smb347_start_stop_अक्षरging(smb);

fail:
	smb347_set_writable(smb, false);
	वापस ret;
पूर्ण

अटल irqवापस_t smb347_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा smb347_अक्षरger *smb = data;
	अचिन्हित पूर्णांक stat_c, irqstat_c, irqstat_d, irqstat_e;
	bool handled = false;
	पूर्णांक ret;

	/* SMB347 it needs at least 20ms क्रम setting IRQSTAT_E_*IN_UV_IRQ */
	usleep_range(25000, 35000);

	ret = regmap_पढ़ो(smb->regmap, STAT_C, &stat_c);
	अगर (ret < 0) अणु
		dev_warn(smb->dev, "reading STAT_C failed\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(smb->regmap, IRQSTAT_C, &irqstat_c);
	अगर (ret < 0) अणु
		dev_warn(smb->dev, "reading IRQSTAT_C failed\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(smb->regmap, IRQSTAT_D, &irqstat_d);
	अगर (ret < 0) अणु
		dev_warn(smb->dev, "reading IRQSTAT_D failed\n");
		वापस IRQ_NONE;
	पूर्ण

	ret = regmap_पढ़ो(smb->regmap, IRQSTAT_E, &irqstat_e);
	अगर (ret < 0) अणु
		dev_warn(smb->dev, "reading IRQSTAT_E failed\n");
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * If we get अक्षरger error we report the error back to user.
	 * If the error is recovered अक्षरging will resume again.
	 */
	अगर (stat_c & STAT_C_CHARGER_ERROR) अणु
		dev_err(smb->dev, "charging stopped due to charger error\n");
		अगर (smb->use_मुख्यs)
			घातer_supply_changed(smb->मुख्यs);
		अगर (smb->use_usb)
			घातer_supply_changed(smb->usb);
		handled = true;
	पूर्ण

	/*
	 * If we reached the termination current the battery is अक्षरged and
	 * we can update the status now. Charging is स्वतःmatically
	 * disabled by the hardware.
	 */
	अगर (irqstat_c & (IRQSTAT_C_TERMINATION_IRQ | IRQSTAT_C_TAPER_IRQ)) अणु
		अगर (irqstat_c & IRQSTAT_C_TERMINATION_STAT) अणु
			अगर (smb->use_मुख्यs)
				घातer_supply_changed(smb->मुख्यs);
			अगर (smb->use_usb)
				घातer_supply_changed(smb->usb);
		पूर्ण
		dev_dbg(smb->dev, "going to HW maintenance mode\n");
		handled = true;
	पूर्ण

	/*
	 * If we got a अक्षरger समयout INT that means the अक्षरge
	 * full is not detected with in अक्षरge समयout value.
	 */
	अगर (irqstat_d & IRQSTAT_D_CHARGE_TIMEOUT_IRQ) अणु
		dev_dbg(smb->dev, "total Charge Timeout INT received\n");

		अगर (irqstat_d & IRQSTAT_D_CHARGE_TIMEOUT_STAT)
			dev_warn(smb->dev, "charging stopped due to timeout\n");
		अगर (smb->use_मुख्यs)
			घातer_supply_changed(smb->मुख्यs);
		अगर (smb->use_usb)
			घातer_supply_changed(smb->usb);
		handled = true;
	पूर्ण

	/*
	 * If we got an under voltage पूर्णांकerrupt it means that AC/USB input
	 * was connected or disconnected.
	 */
	अगर (irqstat_e & (IRQSTAT_E_USBIN_UV_IRQ | IRQSTAT_E_DCIN_UV_IRQ)) अणु
		अगर (smb347_update_ps_status(smb) > 0) अणु
			smb347_start_stop_अक्षरging(smb);
			अगर (smb->use_मुख्यs)
				घातer_supply_changed(smb->मुख्यs);
			अगर (smb->use_usb)
				घातer_supply_changed(smb->usb);
		पूर्ण
		handled = true;
	पूर्ण

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल पूर्णांक smb347_irq_set(काष्ठा smb347_अक्षरger *smb, bool enable)
अणु
	पूर्णांक ret;

	अगर (smb->irq_unsupported)
		वापस 0;

	ret = smb347_set_writable(smb, true);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Enable/disable पूर्णांकerrupts क्रम:
	 *	- under voltage
	 *	- termination current reached
	 *	- अक्षरger समयout
	 *	- अक्षरger error
	 */
	ret = regmap_update_bits(smb->regmap, CFG_FAULT_IRQ, 0xff,
				 enable ? CFG_FAULT_IRQ_DCIN_UV : 0);
	अगर (ret < 0)
		जाओ fail;

	ret = regmap_update_bits(smb->regmap, CFG_STATUS_IRQ, 0xff,
			enable ? (CFG_STATUS_IRQ_TERMINATION_OR_TAPER |
					CFG_STATUS_IRQ_CHARGE_TIMEOUT) : 0);
	अगर (ret < 0)
		जाओ fail;

	ret = regmap_update_bits(smb->regmap, CFG_PIN, CFG_PIN_EN_CHARGER_ERROR,
				 enable ? CFG_PIN_EN_CHARGER_ERROR : 0);
fail:
	smb347_set_writable(smb, false);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक smb347_irq_enable(काष्ठा smb347_अक्षरger *smb)
अणु
	वापस smb347_irq_set(smb, true);
पूर्ण

अटल अंतरभूत पूर्णांक smb347_irq_disable(काष्ठा smb347_अक्षरger *smb)
अणु
	वापस smb347_irq_set(smb, false);
पूर्ण

अटल पूर्णांक smb347_irq_init(काष्ठा smb347_अक्षरger *smb,
			   काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	smb->irq_unsupported = true;

	/*
	 * Interrupt pin is optional. If it is connected, we setup the
	 * पूर्णांकerrupt support here.
	 */
	अगर (!client->irq)
		वापस 0;

	ret = smb347_set_writable(smb, true);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Configure the STAT output to be suitable क्रम पूर्णांकerrupts: disable
	 * all other output (except पूर्णांकerrupts) and make it active low.
	 */
	ret = regmap_update_bits(smb->regmap, CFG_STAT,
				 CFG_STAT_ACTIVE_HIGH | CFG_STAT_DISABLED,
				 CFG_STAT_DISABLED);

	smb347_set_writable(smb, false);

	अगर (ret < 0) अणु
		dev_warn(smb->dev, "failed to initialize IRQ: %d\n", ret);
		dev_warn(smb->dev, "disabling IRQ support\n");
		वापस 0;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(smb->dev, client->irq, शून्य,
					smb347_पूर्णांकerrupt, IRQF_ONESHOT,
					client->name, smb);
	अगर (ret)
		वापस ret;

	smb->irq_unsupported = false;

	ret = smb347_irq_enable(smb);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Returns the स्थिरant अक्षरge current programmed
 * पूर्णांकo the अक्षरger in uA.
 */
अटल पूर्णांक get_स्थिर_अक्षरge_current(काष्ठा smb347_अक्षरger *smb)
अणु
	अचिन्हित पूर्णांक id = smb->id;
	पूर्णांक ret, पूर्णांकval;
	अचिन्हित पूर्णांक v;

	अगर (!smb347_is_ps_online(smb))
		वापस -ENODATA;

	ret = regmap_पढ़ो(smb->regmap, STAT_B, &v);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The current value is composition of FCC and PCC values
	 * and we can detect which table to use from bit 5.
	 */
	अगर (v & 0x20) अणु
		पूर्णांकval = hw_to_current(fcc_tbl[id],
				       ARRAY_SIZE(fcc_tbl[id]), v & 7);
	पूर्ण अन्यथा अणु
		v >>= 3;
		पूर्णांकval = hw_to_current(pcc_tbl[id],
				       ARRAY_SIZE(pcc_tbl[id]), v & 7);
	पूर्ण

	वापस पूर्णांकval;
पूर्ण

/*
 * Returns the स्थिरant अक्षरge voltage programmed
 * पूर्णांकo the अक्षरger in uV.
 */
अटल पूर्णांक get_स्थिर_अक्षरge_voltage(काष्ठा smb347_अक्षरger *smb)
अणु
	पूर्णांक ret, पूर्णांकval;
	अचिन्हित पूर्णांक v;

	अगर (!smb347_is_ps_online(smb))
		वापस -ENODATA;

	ret = regmap_पढ़ो(smb->regmap, STAT_A, &v);
	अगर (ret < 0)
		वापस ret;

	v &= STAT_A_FLOAT_VOLTAGE_MASK;
	अगर (v > 0x3d)
		v = 0x3d;

	पूर्णांकval = 3500000 + v * 20000;

	वापस पूर्णांकval;
पूर्ण

अटल पूर्णांक smb347_get_अक्षरging_status(काष्ठा smb347_अक्षरger *smb,
				      काष्ठा घातer_supply *psy)
अणु
	पूर्णांक ret, status;
	अचिन्हित पूर्णांक val;

	अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB) अणु
		अगर (!smb->usb_online)
			वापस POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण अन्यथा अणु
		अगर (!smb->मुख्यs_online)
			वापस POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	ret = regmap_पढ़ो(smb->regmap, STAT_C, &val);
	अगर (ret < 0)
		वापस ret;

	अगर ((val & STAT_C_CHARGER_ERROR) ||
			(val & STAT_C_HOLDOFF_STAT)) अणु
		/*
		 * set to NOT CHARGING upon अक्षरger error
		 * or अक्षरging has stopped.
		 */
		status = POWER_SUPPLY_STATUS_NOT_CHARGING;
	पूर्ण अन्यथा अणु
		अगर ((val & STAT_C_CHG_MASK) >> STAT_C_CHG_SHIFT) अणु
			/*
			 * set to अक्षरging अगर battery is in pre-अक्षरge,
			 * fast अक्षरge or taper अक्षरging mode.
			 */
			status = POWER_SUPPLY_STATUS_CHARGING;
		पूर्ण अन्यथा अगर (val & STAT_C_CHG_TERM) अणु
			/*
			 * set the status to FULL अगर battery is not in pre
			 * अक्षरge, fast अक्षरge or taper अक्षरging mode AND
			 * अक्षरging is terminated at least once.
			 */
			status = POWER_SUPPLY_STATUS_FULL;
		पूर्ण अन्यथा अणु
			/*
			 * in this हाल no अक्षरger error or termination
			 * occured but अक्षरging is not in progress!!!
			 */
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक smb347_get_property_locked(काष्ठा घातer_supply *psy,
				      क्रमागत घातer_supply_property prop,
				      जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smb347_अक्षरger *smb = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = smb347_get_अक्षरging_status(smb, psy);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB) अणु
			अगर (!smb->usb_online)
				वापस -ENODATA;
		पूर्ण अन्यथा अणु
			अगर (!smb->मुख्यs_online)
				वापस -ENODATA;
		पूर्ण

		/*
		 * We handle trickle and pre-अक्षरging the same, and taper
		 * and none the same.
		 */
		चयन (smb347_अक्षरging_status(smb)) अणु
		हाल 1:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		हाल 2:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		अगर (psy->desc->type == POWER_SUPPLY_TYPE_USB)
			val->पूर्णांकval = smb->usb_online;
		अन्यथा
			val->पूर्णांकval = smb->मुख्यs_online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = get_स्थिर_अक्षरge_voltage(smb);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = get_स्थिर_अक्षरge_current(smb);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smb347_get_property(काष्ठा घातer_supply *psy,
			       क्रमागत घातer_supply_property prop,
			       जोड़ घातer_supply_propval *val)
अणु
	काष्ठा smb347_अक्षरger *smb = घातer_supply_get_drvdata(psy);
	काष्ठा i2c_client *client = to_i2c_client(smb->dev);
	पूर्णांक ret;

	अगर (!smb->irq_unsupported)
		disable_irq(client->irq);

	ret = smb347_get_property_locked(psy, prop, val);

	अगर (!smb->irq_unsupported)
		enable_irq(client->irq);

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property smb347_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
पूर्ण;

अटल bool smb347_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल IRQSTAT_A:
	हाल IRQSTAT_C:
	हाल IRQSTAT_D:
	हाल IRQSTAT_E:
	हाल IRQSTAT_F:
	हाल STAT_A:
	हाल STAT_B:
	हाल STAT_C:
	हाल STAT_E:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool smb347_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CFG_CHARGE_CURRENT:
	हाल CFG_CURRENT_LIMIT:
	हाल CFG_FLOAT_VOLTAGE:
	हाल CFG_STAT:
	हाल CFG_PIN:
	हाल CFG_THERM:
	हाल CFG_SYSOK:
	हाल CFG_OTHER:
	हाल CFG_OTG:
	हाल CFG_TEMP_LIMIT:
	हाल CFG_FAULT_IRQ:
	हाल CFG_STATUS_IRQ:
	हाल CFG_ADDRESS:
	हाल CMD_A:
	हाल CMD_B:
	हाल CMD_C:
		वापस true;
	पूर्ण

	वापस smb347_अस्थिर_reg(dev, reg);
पूर्ण

अटल व्योम smb347_dt_parse_dev_info(काष्ठा smb347_अक्षरger *smb)
अणु
	काष्ठा device *dev = smb->dev;

	smb->soft_temp_limit_compensation =
					SMB3XX_SOFT_TEMP_COMPENSATE_DEFAULT;
	/*
	 * These properties come from the battery info, still we need to
	 * pre-initialize the values. See smb347_get_battery_info() below.
	 */
	smb->soft_cold_temp_limit = SMB3XX_TEMP_USE_DEFAULT;
	smb->hard_cold_temp_limit = SMB3XX_TEMP_USE_DEFAULT;
	smb->soft_hot_temp_limit  = SMB3XX_TEMP_USE_DEFAULT;
	smb->hard_hot_temp_limit  = SMB3XX_TEMP_USE_DEFAULT;

	/* Charging स्थिरraपूर्णांकs */
	device_property_पढ़ो_u32(dev, "summit,fast-voltage-threshold-microvolt",
				 &smb->pre_to_fast_voltage);
	device_property_पढ़ो_u32(dev, "summit,mains-current-limit-microamp",
				 &smb->मुख्यs_current_limit);
	device_property_पढ़ो_u32(dev, "summit,usb-current-limit-microamp",
				 &smb->usb_hc_current_limit);

	/* For thermometer monitoring */
	device_property_पढ़ो_u32(dev, "summit,chip-temperature-threshold-celsius",
				 &smb->chip_temp_threshold);
	device_property_पढ़ो_u32(dev, "summit,soft-compensation-method",
				 &smb->soft_temp_limit_compensation);
	device_property_पढ़ो_u32(dev, "summit,charge-current-compensation-microamp",
				 &smb->अक्षरge_current_compensation);

	/* Supported अक्षरging mode */
	smb->use_मुख्यs = device_property_पढ़ो_bool(dev, "summit,enable-mains-charging");
	smb->use_usb = device_property_पढ़ो_bool(dev, "summit,enable-usb-charging");
	smb->use_usb_otg = device_property_पढ़ो_bool(dev, "summit,enable-otg-charging");

	/* Select अक्षरging control */
	device_property_पढ़ो_u32(dev, "summit,enable-charge-control",
				 &smb->enable_control);
पूर्ण

अटल पूर्णांक smb347_get_battery_info(काष्ठा smb347_अक्षरger *smb)
अणु
	काष्ठा घातer_supply_battery_info info = अणुपूर्ण;
	काष्ठा घातer_supply *supply;
	पूर्णांक err;

	अगर (smb->मुख्यs)
		supply = smb->मुख्यs;
	अन्यथा
		supply = smb->usb;

	err = घातer_supply_get_battery_info(supply, &info);
	अगर (err == -ENXIO || err == -ENODEV)
		वापस 0;
	अगर (err)
		वापस err;

	अगर (info.स्थिरant_अक्षरge_current_max_ua != -EINVAL)
		smb->max_अक्षरge_current = info.स्थिरant_अक्षरge_current_max_ua;

	अगर (info.स्थिरant_अक्षरge_voltage_max_uv != -EINVAL)
		smb->max_अक्षरge_voltage = info.स्थिरant_अक्षरge_voltage_max_uv;

	अगर (info.preअक्षरge_current_ua != -EINVAL)
		smb->pre_अक्षरge_current = info.preअक्षरge_current_ua;

	अगर (info.अक्षरge_term_current_ua != -EINVAL)
		smb->termination_current = info.अक्षरge_term_current_ua;

	अगर (info.temp_alert_min != पूर्णांक_न्यून)
		smb->soft_cold_temp_limit = info.temp_alert_min;

	अगर (info.temp_alert_max != पूर्णांक_उच्च)
		smb->soft_hot_temp_limit = info.temp_alert_max;

	अगर (info.temp_min != पूर्णांक_न्यून)
		smb->hard_cold_temp_limit = info.temp_min;

	अगर (info.temp_max != पूर्णांक_उच्च)
		smb->hard_hot_temp_limit = info.temp_max;

	/* Suspend when battery temperature is outside hard limits */
	अगर (smb->hard_cold_temp_limit != SMB3XX_TEMP_USE_DEFAULT ||
	    smb->hard_hot_temp_limit != SMB3XX_TEMP_USE_DEFAULT)
		smb->suspend_on_hard_temp_limit = true;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config smb347_regmap = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= SMB347_MAX_REGISTER,
	.अस्थिर_reg	= smb347_अस्थिर_reg,
	.पढ़ोable_reg	= smb347_पढ़ोable_reg,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc smb347_मुख्यs_desc = अणु
	.name		= "smb347-mains",
	.type		= POWER_SUPPLY_TYPE_MAINS,
	.get_property	= smb347_get_property,
	.properties	= smb347_properties,
	.num_properties	= ARRAY_SIZE(smb347_properties),
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc smb347_usb_desc = अणु
	.name		= "smb347-usb",
	.type		= POWER_SUPPLY_TYPE_USB,
	.get_property	= smb347_get_property,
	.properties	= smb347_properties,
	.num_properties	= ARRAY_SIZE(smb347_properties),
पूर्ण;

अटल पूर्णांक smb347_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा घातer_supply_config मुख्यs_usb_cfg = अणुपूर्ण;
	काष्ठा device *dev = &client->dev;
	काष्ठा smb347_अक्षरger *smb;
	पूर्णांक ret;

	smb = devm_kzalloc(dev, माप(*smb), GFP_KERNEL);
	अगर (!smb)
		वापस -ENOMEM;
	smb->dev = &client->dev;
	smb->id = id->driver_data;
	i2c_set_clientdata(client, smb);

	smb347_dt_parse_dev_info(smb);
	अगर (!smb->use_मुख्यs && !smb->use_usb)
		वापस -EINVAL;

	smb->regmap = devm_regmap_init_i2c(client, &smb347_regmap);
	अगर (IS_ERR(smb->regmap))
		वापस PTR_ERR(smb->regmap);

	मुख्यs_usb_cfg.drv_data = smb;
	मुख्यs_usb_cfg.of_node = dev->of_node;
	अगर (smb->use_मुख्यs) अणु
		smb->मुख्यs = devm_घातer_supply_रेजिस्टर(dev, &smb347_मुख्यs_desc,
							&मुख्यs_usb_cfg);
		अगर (IS_ERR(smb->मुख्यs))
			वापस PTR_ERR(smb->मुख्यs);
	पूर्ण

	अगर (smb->use_usb) अणु
		smb->usb = devm_घातer_supply_रेजिस्टर(dev, &smb347_usb_desc,
						      &मुख्यs_usb_cfg);
		अगर (IS_ERR(smb->usb))
			वापस PTR_ERR(smb->usb);
	पूर्ण

	ret = smb347_get_battery_info(smb);
	अगर (ret)
		वापस ret;

	ret = smb347_hw_init(smb);
	अगर (ret < 0)
		वापस ret;

	ret = smb347_irq_init(smb, client);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक smb347_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा smb347_अक्षरger *smb = i2c_get_clientdata(client);

	smb347_irq_disable(smb);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id smb347_id[] = अणु
	अणु "smb345", SMB345 पूर्ण,
	अणु "smb347", SMB347 पूर्ण,
	अणु "smb358", SMB358 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, smb347_id);

अटल स्थिर काष्ठा of_device_id smb3xx_of_match[] = अणु
	अणु .compatible = "summit,smb345" पूर्ण,
	अणु .compatible = "summit,smb347" पूर्ण,
	अणु .compatible = "summit,smb358" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, smb3xx_of_match);

अटल काष्ठा i2c_driver smb347_driver = अणु
	.driver = अणु
		.name = "smb347",
		.of_match_table = smb3xx_of_match,
	पूर्ण,
	.probe = smb347_probe,
	.हटाओ = smb347_हटाओ,
	.id_table = smb347_id,
पूर्ण;
module_i2c_driver(smb347_driver);

MODULE_AUTHOR("Bruce E. Robertson <bruce.e.robertson@intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com>");
MODULE_DESCRIPTION("SMB347 battery charger driver");
MODULE_LICENSE("GPL");
