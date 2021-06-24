<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// BQ256XX Battery Charger Driver
// Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com/

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>
#समावेश <linux/usb/phy.h>
#समावेश <linux/device.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>

#घोषणा BQ256XX_MANUFACTURER "Texas Instruments"

#घोषणा BQ256XX_INPUT_CURRENT_LIMIT		0x00
#घोषणा BQ256XX_CHARGER_CONTROL_0		0x01
#घोषणा BQ256XX_CHARGE_CURRENT_LIMIT		0x02
#घोषणा BQ256XX_PRECHG_AND_TERM_CURR_LIM	0x03
#घोषणा BQ256XX_BATTERY_VOLTAGE_LIMIT		0x04
#घोषणा BQ256XX_CHARGER_CONTROL_1		0x05
#घोषणा BQ256XX_CHARGER_CONTROL_2		0x06
#घोषणा BQ256XX_CHARGER_CONTROL_3		0x07
#घोषणा BQ256XX_CHARGER_STATUS_0		0x08
#घोषणा BQ256XX_CHARGER_STATUS_1		0x09
#घोषणा BQ256XX_CHARGER_STATUS_2		0x0a
#घोषणा BQ256XX_PART_INFORMATION		0x0b
#घोषणा BQ256XX_CHARGER_CONTROL_4		0x0c

#घोषणा BQ256XX_IINDPM_MASK		GENMASK(4, 0)
#घोषणा BQ256XX_IINDPM_STEP_uA		100000
#घोषणा BQ256XX_IINDPM_OFFSET_uA	100000
#घोषणा BQ256XX_IINDPM_MIN_uA		100000
#घोषणा BQ256XX_IINDPM_MAX_uA		3200000
#घोषणा BQ256XX_IINDPM_DEF_uA		2400000

#घोषणा BQ256XX_VINDPM_MASK		GENMASK(3, 0)
#घोषणा BQ256XX_VINDPM_STEP_uV		100000
#घोषणा BQ256XX_VINDPM_OFFSET_uV	3900000
#घोषणा BQ256XX_VINDPM_MIN_uV		3900000
#घोषणा BQ256XX_VINDPM_MAX_uV		5400000
#घोषणा BQ256XX_VINDPM_DEF_uV		4500000

#घोषणा BQ256XX_VBATREG_MASK		GENMASK(7, 3)
#घोषणा BQ2560X_VBATREG_STEP_uV		32000
#घोषणा BQ2560X_VBATREG_OFFSET_uV	3856000
#घोषणा BQ2560X_VBATREG_MIN_uV		3856000
#घोषणा BQ2560X_VBATREG_MAX_uV		4624000
#घोषणा BQ2560X_VBATREG_DEF_uV		4208000
#घोषणा BQ25601D_VBATREG_OFFSET_uV	3847000
#घोषणा BQ25601D_VBATREG_MIN_uV		3847000
#घोषणा BQ25601D_VBATREG_MAX_uV		4615000
#घोषणा BQ25601D_VBATREG_DEF_uV		4199000
#घोषणा BQ2561X_VBATREG_STEP_uV		10000
#घोषणा BQ25611D_VBATREG_MIN_uV		3494000
#घोषणा BQ25611D_VBATREG_MAX_uV		4510000
#घोषणा BQ25611D_VBATREG_DEF_uV		4190000
#घोषणा BQ25618_VBATREG_MIN_uV		3504000
#घोषणा BQ25618_VBATREG_MAX_uV		4500000
#घोषणा BQ25618_VBATREG_DEF_uV		4200000
#घोषणा BQ256XX_VBATREG_BIT_SHIFT	3
#घोषणा BQ2561X_VBATREG_THRESH		0x8
#घोषणा BQ25611D_VBATREG_THRESH_uV	4290000
#घोषणा BQ25618_VBATREG_THRESH_uV	4300000

#घोषणा BQ256XX_ITERM_MASK		GENMASK(3, 0)
#घोषणा BQ256XX_ITERM_STEP_uA		60000
#घोषणा BQ256XX_ITERM_OFFSET_uA		60000
#घोषणा BQ256XX_ITERM_MIN_uA		60000
#घोषणा BQ256XX_ITERM_MAX_uA		780000
#घोषणा BQ256XX_ITERM_DEF_uA		180000
#घोषणा BQ25618_ITERM_STEP_uA		20000
#घोषणा BQ25618_ITERM_OFFSET_uA		20000
#घोषणा BQ25618_ITERM_MIN_uA		20000
#घोषणा BQ25618_ITERM_MAX_uA		260000
#घोषणा BQ25618_ITERM_DEF_uA		60000

#घोषणा BQ256XX_IPRECHG_MASK		GENMASK(7, 4)
#घोषणा BQ256XX_IPRECHG_STEP_uA		60000
#घोषणा BQ256XX_IPRECHG_OFFSET_uA	60000
#घोषणा BQ256XX_IPRECHG_MIN_uA		60000
#घोषणा BQ256XX_IPRECHG_MAX_uA		780000
#घोषणा BQ256XX_IPRECHG_DEF_uA		180000
#घोषणा BQ25618_IPRECHG_STEP_uA		20000
#घोषणा BQ25618_IPRECHG_OFFSET_uA	20000
#घोषणा BQ25618_IPRECHG_MIN_uA		20000
#घोषणा BQ25618_IPRECHG_MAX_uA		260000
#घोषणा BQ25618_IPRECHG_DEF_uA		40000
#घोषणा BQ256XX_IPRECHG_BIT_SHIFT	4

#घोषणा BQ256XX_ICHG_MASK		GENMASK(5, 0)
#घोषणा BQ256XX_ICHG_STEP_uA		60000
#घोषणा BQ256XX_ICHG_MIN_uA		0
#घोषणा BQ256XX_ICHG_MAX_uA		3000000
#घोषणा BQ2560X_ICHG_DEF_uA		2040000
#घोषणा BQ25611D_ICHG_DEF_uA		1020000
#घोषणा BQ25618_ICHG_STEP_uA		20000
#घोषणा BQ25618_ICHG_MIN_uA		0
#घोषणा BQ25618_ICHG_MAX_uA		1500000
#घोषणा BQ25618_ICHG_DEF_uA		340000
#घोषणा BQ25618_ICHG_THRESH		0x3c
#घोषणा BQ25618_ICHG_THRESH_uA		1180000

#घोषणा BQ256XX_VBUS_STAT_MASK		GENMASK(7, 5)
#घोषणा BQ256XX_VBUS_STAT_NO_INPUT	0
#घोषणा BQ256XX_VBUS_STAT_USB_SDP	BIT(5)
#घोषणा BQ256XX_VBUS_STAT_USB_CDP	BIT(6)
#घोषणा BQ256XX_VBUS_STAT_USB_DCP	(BIT(6) | BIT(5))
#घोषणा BQ256XX_VBUS_STAT_USB_OTG	(BIT(7) | BIT(6) | BIT(5))

#घोषणा BQ256XX_CHRG_STAT_MASK		GENMASK(4, 3)
#घोषणा BQ256XX_CHRG_STAT_NOT_CHRGING	0
#घोषणा BQ256XX_CHRG_STAT_PRECHRGING	BIT(3)
#घोषणा BQ256XX_CHRG_STAT_FAST_CHRGING	BIT(4)
#घोषणा BQ256XX_CHRG_STAT_CHRG_TERM	(BIT(4) | BIT(3))

#घोषणा BQ256XX_PG_STAT_MASK		BIT(2)
#घोषणा BQ256XX_WDT_FAULT_MASK		BIT(7)
#घोषणा BQ256XX_CHRG_FAULT_MASK		GENMASK(5, 4)
#घोषणा BQ256XX_CHRG_FAULT_NORMAL	0
#घोषणा BQ256XX_CHRG_FAULT_INPUT	BIT(4)
#घोषणा BQ256XX_CHRG_FAULT_THERM	BIT(5)
#घोषणा BQ256XX_CHRG_FAULT_CST_EXPIRE	(BIT(5) | BIT(4))
#घोषणा BQ256XX_BAT_FAULT_MASK		BIT(3)
#घोषणा BQ256XX_NTC_FAULT_MASK		GENMASK(2, 0)
#घोषणा BQ256XX_NTC_FAULT_WARM		BIT(1)
#घोषणा BQ256XX_NTC_FAULT_COOL		(BIT(1) | BIT(0))
#घोषणा BQ256XX_NTC_FAULT_COLD		(BIT(2) | BIT(0))
#घोषणा BQ256XX_NTC_FAULT_HOT		(BIT(2) | BIT(1))

#घोषणा BQ256XX_NUM_WD_VAL	4
#घोषणा BQ256XX_WATCHDOG_MASK	GENMASK(5, 4)
#घोषणा BQ256XX_WATCHDOG_MAX	1600000
#घोषणा BQ256XX_WATCHDOG_DIS	0
#घोषणा BQ256XX_WDT_BIT_SHIFT	4

#घोषणा BQ256XX_REG_RST		BIT(7)

/**
 * काष्ठा bq256xx_init_data -
 * @ichg: fast अक्षरge current
 * @iindpm: input current limit
 * @vbatreg: अक्षरge voltage
 * @iterm: termination current
 * @iprechg: preअक्षरge current
 * @vindpm: input voltage limit
 * @ichg_max: maximum fast अक्षरge current
 * @vbatreg_max: maximum अक्षरge voltage
 */
काष्ठा bq256xx_init_data अणु
	u32 ichg;
	u32 iindpm;
	u32 vbatreg;
	u32 iterm;
	u32 iprechg;
	u32 vindpm;
	u32 ichg_max;
	u32 vbatreg_max;
पूर्ण;

/**
 * काष्ठा bq256xx_state -
 * @vbus_stat: VBUS status according to BQ256XX_CHARGER_STATUS_0
 * @chrg_stat: अक्षरging status according to BQ256XX_CHARGER_STATUS_0
 * @online: PG status according to BQ256XX_CHARGER_STATUS_0
 *
 * @wdt_fault: watchकरोg fault according to BQ256XX_CHARGER_STATUS_1
 * @bat_fault: battery fault according to BQ256XX_CHARGER_STATUS_1
 * @chrg_fault: अक्षरging fault according to BQ256XX_CHARGER_STATUS_1
 * @ntc_fault: TS fault according to BQ256XX_CHARGER_STATUS_1
 */
काष्ठा bq256xx_state अणु
	u8 vbus_stat;
	u8 chrg_stat;
	bool online;

	u8 wdt_fault;
	u8 bat_fault;
	u8 chrg_fault;
	u8 ntc_fault;
पूर्ण;

क्रमागत bq256xx_id अणु
	BQ25600,
	BQ25600D,
	BQ25601,
	BQ25601D,
	BQ25618,
	BQ25619,
	BQ25611D,
पूर्ण;

/**
 * काष्ठा bq256xx_device -
 * @client: i2c client काष्ठाure
 * @regmap: रेजिस्टर map काष्ठाure
 * @dev: device काष्ठाure
 * @अक्षरger: घातer supply रेजिस्टरed क्रम the अक्षरger
 * @battery: घातer supply रेजिस्टरed क्रम the battery
 * @lock: mutex lock काष्ठाure
 *
 * @usb2_phy: usb_phy identअगरier
 * @usb3_phy: usb_phy identअगरier
 * @usb_nb: notअगरier block
 * @usb_work: usb work queue
 * @usb_event: usb_event code
 *
 * @model_name: i2c name string
 *
 * @init_data: initialization data
 * @chip_info: device variant inक्रमmation
 * @state: device status and faults
 * @watchकरोg_समयr: watchकरोg समयr value in milliseconds
 */
काष्ठा bq256xx_device अणु
	काष्ठा i2c_client *client;
	काष्ठा device *dev;
	काष्ठा घातer_supply *अक्षरger;
	काष्ठा घातer_supply *battery;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;

	काष्ठा usb_phy *usb2_phy;
	काष्ठा usb_phy *usb3_phy;
	काष्ठा notअगरier_block usb_nb;
	काष्ठा work_काष्ठा usb_work;
	अचिन्हित दीर्घ usb_event;

	अक्षर model_name[I2C_NAME_SIZE];

	काष्ठा bq256xx_init_data init_data;
	स्थिर काष्ठा bq256xx_chip_info *chip_info;
	काष्ठा bq256xx_state state;
	पूर्णांक watchकरोg_समयr;
पूर्ण;

/**
 * काष्ठा bq256xx_chip_info -
 * @model_id: device instance
 *
 * @bq256xx_regmap_config: regmap configuration काष्ठा
 * @bq256xx_get_ichg: poपूर्णांकer to instance specअगरic get_ichg function
 * @bq256xx_get_iindpm: poपूर्णांकer to instance specअगरic get_iindpm function
 * @bq256xx_get_vbatreg: poपूर्णांकer to instance specअगरic get_vbatreg function
 * @bq256xx_get_iterm: poपूर्णांकer to instance specअगरic get_iterm function
 * @bq256xx_get_iprechg: poपूर्णांकer to instance specअगरic get_iprechg function
 * @bq256xx_get_vindpm: poपूर्णांकer to instance specअगरic get_vindpm function
 *
 * @bq256xx_set_ichg: poपूर्णांकer to instance specअगरic set_ichg function
 * @bq256xx_set_iindpm: poपूर्णांकer to instance specअगरic set_iindpm function
 * @bq256xx_set_vbatreg: poपूर्णांकer to instance specअगरic set_vbatreg function
 * @bq256xx_set_iterm: poपूर्णांकer to instance specअगरic set_iterm function
 * @bq256xx_set_iprechg: poपूर्णांकer to instance specअगरic set_iprechg function
 * @bq256xx_set_vindpm: poपूर्णांकer to instance specअगरic set_vindpm function
 *
 * @bq256xx_def_ichg: शेष ichg value in microamps
 * @bq256xx_def_iindpm: शेष iindpm value in microamps
 * @bq256xx_def_vbatreg: शेष vbatreg value in microvolts
 * @bq256xx_def_iterm: शेष iterm value in microamps
 * @bq256xx_def_iprechg: शेष iprechg value in microamps
 * @bq256xx_def_vindpm: शेष vindpm value in microvolts
 *
 * @bq256xx_max_ichg: maximum अक्षरge current in microamps
 * @bq256xx_max_vbatreg: maximum battery regulation voltage in microvolts
 *
 * @has_usb_detect: indicates whether device has BC1.2 detection
 */
काष्ठा bq256xx_chip_info अणु
	पूर्णांक model_id;

	स्थिर काष्ठा regmap_config *bq256xx_regmap_config;

	पूर्णांक (*bq256xx_get_ichg)(काष्ठा bq256xx_device *bq);
	पूर्णांक (*bq256xx_get_iindpm)(काष्ठा bq256xx_device *bq);
	पूर्णांक (*bq256xx_get_vbatreg)(काष्ठा bq256xx_device *bq);
	पूर्णांक (*bq256xx_get_iterm)(काष्ठा bq256xx_device *bq);
	पूर्णांक (*bq256xx_get_iprechg)(काष्ठा bq256xx_device *bq);
	पूर्णांक (*bq256xx_get_vindpm)(काष्ठा bq256xx_device *bq);

	पूर्णांक (*bq256xx_set_ichg)(काष्ठा bq256xx_device *bq, पूर्णांक ichg);
	पूर्णांक (*bq256xx_set_iindpm)(काष्ठा bq256xx_device *bq, पूर्णांक iindpm);
	पूर्णांक (*bq256xx_set_vbatreg)(काष्ठा bq256xx_device *bq, पूर्णांक vbatreg);
	पूर्णांक (*bq256xx_set_iterm)(काष्ठा bq256xx_device *bq, पूर्णांक iterm);
	पूर्णांक (*bq256xx_set_iprechg)(काष्ठा bq256xx_device *bq, पूर्णांक iprechg);
	पूर्णांक (*bq256xx_set_vindpm)(काष्ठा bq256xx_device *bq, पूर्णांक vindpm);

	पूर्णांक bq256xx_def_ichg;
	पूर्णांक bq256xx_def_iindpm;
	पूर्णांक bq256xx_def_vbatreg;
	पूर्णांक bq256xx_def_iterm;
	पूर्णांक bq256xx_def_iprechg;
	पूर्णांक bq256xx_def_vindpm;

	पूर्णांक bq256xx_max_ichg;
	पूर्णांक bq256xx_max_vbatreg;

	bool has_usb_detect;
पूर्ण;

अटल पूर्णांक bq256xx_watchकरोg_समय[BQ256XX_NUM_WD_VAL] = अणु
	0, 40000, 80000, 1600000
पूर्ण;

अटल स्थिर पूर्णांक bq25611d_vbatreg_values[] = अणु
	3494000, 3590000, 3686000, 3790000, 3894000, 3990000, 4090000, 4140000,
	4190000
पूर्ण;

अटल स्थिर पूर्णांक bq25618_619_vbatreg_values[] = अणु
	3504000, 3600000, 3696000, 3800000, 3904000, 4000000, 4100000, 4150000,
	4200000
पूर्ण;

अटल स्थिर पूर्णांक bq25618_619_ichg_values[] = अणु
	1290000, 1360000, 1430000, 1500000
पूर्ण;

अटल क्रमागत घातer_supply_usb_type bq256xx_usb_type[] = अणु
	POWER_SUPPLY_USB_TYPE_SDP,
	POWER_SUPPLY_USB_TYPE_CDP,
	POWER_SUPPLY_USB_TYPE_DCP,
	POWER_SUPPLY_USB_TYPE_UNKNOWN,
	POWER_SUPPLY_USB_TYPE_ACA,
पूर्ण;

अटल पूर्णांक bq256xx_array_parse(पूर्णांक array_size, पूर्णांक val, स्थिर पूर्णांक array[])
अणु
	पूर्णांक i = 0;

	अगर (val < array[i])
		वापस i - 1;

	अगर (val >= array[array_size - 1])
		वापस array_size - 1;

	क्रम (i = 1; i < array_size; i++) अणु
		अगर (val == array[i])
			वापस i;

		अगर (val > array[i - 1] && val < array[i]) अणु
			अगर (val < array[i])
				वापस i - 1;
			अन्यथा
				वापस i;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bq256xx_usb_notअगरier(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ val,
				व्योम *priv)
अणु
	काष्ठा bq256xx_device *bq =
			container_of(nb, काष्ठा bq256xx_device, usb_nb);

	bq->usb_event = val;
	queue_work(प्रणाली_घातer_efficient_wq, &bq->usb_work);

	वापस NOTIFY_OK;
पूर्ण

अटल व्योम bq256xx_usb_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा bq256xx_device *bq =
			container_of(data, काष्ठा bq256xx_device, usb_work);

	चयन (bq->usb_event) अणु
	हाल USB_EVENT_ID:
		अवरोध;
	हाल USB_EVENT_NONE:
		घातer_supply_changed(bq->अक्षरger);
		अवरोध;
	शेष:
		dev_err(bq->dev, "Error switching to charger mode.\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा reg_शेष bq2560x_reg_defs[] = अणु
	अणुBQ256XX_INPUT_CURRENT_LIMIT, 0x17पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_0, 0x1aपूर्ण,
	अणुBQ256XX_CHARGE_CURRENT_LIMIT, 0xa2पूर्ण,
	अणुBQ256XX_PRECHG_AND_TERM_CURR_LIM, 0x22पूर्ण,
	अणुBQ256XX_BATTERY_VOLTAGE_LIMIT, 0x58पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_1, 0x9fपूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_2, 0x66पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_3, 0x4cपूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष bq25611d_reg_defs[] = अणु
	अणुBQ256XX_INPUT_CURRENT_LIMIT, 0x17पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_0, 0x1aपूर्ण,
	अणुBQ256XX_CHARGE_CURRENT_LIMIT, 0x91पूर्ण,
	अणुBQ256XX_PRECHG_AND_TERM_CURR_LIM, 0x12पूर्ण,
	अणुBQ256XX_BATTERY_VOLTAGE_LIMIT, 0x40पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_1, 0x9eपूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_2, 0xe6पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_3, 0x4cपूर्ण,
	अणुBQ256XX_PART_INFORMATION, 0x54पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_4, 0x75पूर्ण,
पूर्ण;

अटल काष्ठा reg_शेष bq25618_619_reg_defs[] = अणु
	अणुBQ256XX_INPUT_CURRENT_LIMIT, 0x17पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_0, 0x1aपूर्ण,
	अणुBQ256XX_CHARGE_CURRENT_LIMIT, 0x91पूर्ण,
	अणुBQ256XX_PRECHG_AND_TERM_CURR_LIM, 0x12पूर्ण,
	अणुBQ256XX_BATTERY_VOLTAGE_LIMIT, 0x40पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_1, 0x9eपूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_2, 0xe6पूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_3, 0x4cपूर्ण,
	अणुBQ256XX_PART_INFORMATION, 0x2cपूर्ण,
	अणुBQ256XX_CHARGER_CONTROL_4, 0x75पूर्ण,
पूर्ण;

अटल पूर्णांक bq256xx_get_state(काष्ठा bq256xx_device *bq,
				काष्ठा bq256xx_state *state)
अणु
	अचिन्हित पूर्णांक अक्षरger_status_0;
	अचिन्हित पूर्णांक अक्षरger_status_1;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_CHARGER_STATUS_0,
						&अक्षरger_status_0);
	अगर (ret)
		वापस ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_CHARGER_STATUS_1,
						&अक्षरger_status_1);
	अगर (ret)
		वापस ret;

	state->vbus_stat = अक्षरger_status_0 & BQ256XX_VBUS_STAT_MASK;
	state->chrg_stat = अक्षरger_status_0 & BQ256XX_CHRG_STAT_MASK;
	state->online = अक्षरger_status_0 & BQ256XX_PG_STAT_MASK;

	state->wdt_fault = अक्षरger_status_1 & BQ256XX_WDT_FAULT_MASK;
	state->bat_fault = अक्षरger_status_1 & BQ256XX_BAT_FAULT_MASK;
	state->chrg_fault = अक्षरger_status_1 & BQ256XX_CHRG_FAULT_MASK;
	state->ntc_fault = अक्षरger_status_1 & BQ256XX_NTC_FAULT_MASK;

	वापस 0;
पूर्ण

अटल पूर्णांक bq256xx_get_ichg_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक अक्षरge_current_limit;
	अचिन्हित पूर्णांक ichg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_CHARGE_CURRENT_LIMIT,
						&अक्षरge_current_limit);
	अगर (ret)
		वापस ret;

	ichg_reg_code = अक्षरge_current_limit & BQ256XX_ICHG_MASK;

	वापस ichg_reg_code * BQ256XX_ICHG_STEP_uA;
पूर्ण

अटल पूर्णांक bq25618_619_get_ichg_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक अक्षरge_current_limit;
	अचिन्हित पूर्णांक ichg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_CHARGE_CURRENT_LIMIT,
						&अक्षरge_current_limit);
	अगर (ret)
		वापस ret;

	ichg_reg_code = अक्षरge_current_limit & BQ256XX_ICHG_MASK;

	अगर (ichg_reg_code < BQ25618_ICHG_THRESH)
		वापस ichg_reg_code * BQ25618_ICHG_STEP_uA;

	वापस bq25618_619_ichg_values[ichg_reg_code - BQ25618_ICHG_THRESH];
पूर्ण

अटल पूर्णांक bq256xx_set_ichg_curr(काष्ठा bq256xx_device *bq, पूर्णांक ichg)
अणु
	अचिन्हित पूर्णांक ichg_reg_code;
	पूर्णांक ichg_max = bq->init_data.ichg_max;

	ichg = clamp(ichg, BQ256XX_ICHG_MIN_uA, ichg_max);
	ichg_reg_code = ichg / BQ256XX_ICHG_STEP_uA;

	वापस regmap_update_bits(bq->regmap, BQ256XX_CHARGE_CURRENT_LIMIT,
					BQ256XX_ICHG_MASK, ichg_reg_code);
पूर्ण

अटल पूर्णांक bq25618_619_set_ichg_curr(काष्ठा bq256xx_device *bq, पूर्णांक ichg)
अणु
	पूर्णांक array_size = ARRAY_SIZE(bq25618_619_ichg_values);
	अचिन्हित पूर्णांक ichg_reg_code;
	पूर्णांक ichg_max = bq->init_data.ichg_max;

	ichg = clamp(ichg, BQ25618_ICHG_MIN_uA, ichg_max);

	अगर (ichg <= BQ25618_ICHG_THRESH_uA) अणु
		ichg_reg_code = ichg / BQ25618_ICHG_STEP_uA;
	पूर्ण अन्यथा अणु
		ichg_reg_code = bq256xx_array_parse(array_size, ichg,
			bq25618_619_ichg_values) + BQ25618_ICHG_THRESH;
	पूर्ण

	वापस regmap_update_bits(bq->regmap, BQ256XX_CHARGE_CURRENT_LIMIT,
					BQ256XX_ICHG_MASK, ichg_reg_code);
पूर्ण

अटल पूर्णांक bq25618_619_get_chrg_volt(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक battery_volt_lim;
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
							&battery_volt_lim);

	अगर (ret)
		वापस ret;

	vbatreg_reg_code = (battery_volt_lim & BQ256XX_VBATREG_MASK) >>
						BQ256XX_VBATREG_BIT_SHIFT;

	अगर (vbatreg_reg_code > BQ2561X_VBATREG_THRESH)
		वापस ((vbatreg_reg_code - BQ2561X_VBATREG_THRESH) *
					BQ2561X_VBATREG_STEP_uV) +
					BQ25618_VBATREG_THRESH_uV;

	वापस bq25618_619_vbatreg_values[vbatreg_reg_code];
पूर्ण

अटल पूर्णांक bq25611d_get_chrg_volt(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक battery_volt_lim;
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
							&battery_volt_lim);
	अगर (ret)
		वापस ret;

	vbatreg_reg_code = (battery_volt_lim & BQ256XX_VBATREG_MASK) >>
						BQ256XX_VBATREG_BIT_SHIFT;

	अगर (vbatreg_reg_code > BQ2561X_VBATREG_THRESH)
		वापस ((vbatreg_reg_code - BQ2561X_VBATREG_THRESH) *
					BQ2561X_VBATREG_STEP_uV) +
					BQ25611D_VBATREG_THRESH_uV;

	वापस bq25611d_vbatreg_values[vbatreg_reg_code];
पूर्ण

अटल पूर्णांक bq2560x_get_chrg_volt(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक battery_volt_lim;
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
							&battery_volt_lim);
	अगर (ret)
		वापस ret;

	vbatreg_reg_code = (battery_volt_lim & BQ256XX_VBATREG_MASK) >>
						BQ256XX_VBATREG_BIT_SHIFT;

	वापस (vbatreg_reg_code * BQ2560X_VBATREG_STEP_uV)
					+ BQ2560X_VBATREG_OFFSET_uV;
पूर्ण

अटल पूर्णांक bq25601d_get_chrg_volt(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक battery_volt_lim;
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
							&battery_volt_lim);
	अगर (ret)
		वापस ret;

	vbatreg_reg_code = (battery_volt_lim & BQ256XX_VBATREG_MASK) >>
						BQ256XX_VBATREG_BIT_SHIFT;

	वापस (vbatreg_reg_code * BQ2560X_VBATREG_STEP_uV)
					+ BQ25601D_VBATREG_OFFSET_uV;
पूर्ण

अटल पूर्णांक bq25618_619_set_chrg_volt(काष्ठा bq256xx_device *bq, पूर्णांक vbatreg)
अणु
	पूर्णांक array_size = ARRAY_SIZE(bq25618_619_vbatreg_values);
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक vbatreg_max = bq->init_data.vbatreg_max;

	vbatreg = clamp(vbatreg, BQ25618_VBATREG_MIN_uV, vbatreg_max);

	अगर (vbatreg > BQ25618_VBATREG_THRESH_uV)
		vbatreg_reg_code = ((vbatreg -
		BQ25618_VBATREG_THRESH_uV) /
		(BQ2561X_VBATREG_STEP_uV)) + BQ2561X_VBATREG_THRESH;
	अन्यथा अणु
		vbatreg_reg_code = bq256xx_array_parse(array_size, vbatreg,
						bq25618_619_vbatreg_values);
	पूर्ण

	वापस regmap_update_bits(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
				BQ256XX_VBATREG_MASK, vbatreg_reg_code <<
						BQ256XX_VBATREG_BIT_SHIFT);
पूर्ण

अटल पूर्णांक bq25611d_set_chrg_volt(काष्ठा bq256xx_device *bq, पूर्णांक vbatreg)
अणु
	पूर्णांक array_size = ARRAY_SIZE(bq25611d_vbatreg_values);
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक vbatreg_max = bq->init_data.vbatreg_max;

	vbatreg = clamp(vbatreg, BQ25611D_VBATREG_MIN_uV, vbatreg_max);

	अगर (vbatreg > BQ25611D_VBATREG_THRESH_uV)
		vbatreg_reg_code = ((vbatreg -
		BQ25611D_VBATREG_THRESH_uV) /
		(BQ2561X_VBATREG_STEP_uV)) + BQ2561X_VBATREG_THRESH;
	अन्यथा अणु
		vbatreg_reg_code = bq256xx_array_parse(array_size, vbatreg,
						bq25611d_vbatreg_values);
	पूर्ण

	वापस regmap_update_bits(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
				BQ256XX_VBATREG_MASK, vbatreg_reg_code <<
						BQ256XX_VBATREG_BIT_SHIFT);
पूर्ण

अटल पूर्णांक bq2560x_set_chrg_volt(काष्ठा bq256xx_device *bq, पूर्णांक vbatreg)
अणु
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक vbatreg_max = bq->init_data.vbatreg_max;

	vbatreg = clamp(vbatreg, BQ2560X_VBATREG_MIN_uV, vbatreg_max);

	vbatreg_reg_code = (vbatreg - BQ2560X_VBATREG_OFFSET_uV) /
						BQ2560X_VBATREG_STEP_uV;

	वापस regmap_update_bits(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
				BQ256XX_VBATREG_MASK, vbatreg_reg_code <<
						BQ256XX_VBATREG_BIT_SHIFT);
पूर्ण

अटल पूर्णांक bq25601d_set_chrg_volt(काष्ठा bq256xx_device *bq, पूर्णांक vbatreg)
अणु
	अचिन्हित पूर्णांक vbatreg_reg_code;
	पूर्णांक vbatreg_max = bq->init_data.vbatreg_max;

	vbatreg = clamp(vbatreg, BQ25601D_VBATREG_MIN_uV, vbatreg_max);

	vbatreg_reg_code = (vbatreg - BQ25601D_VBATREG_OFFSET_uV) /
						BQ2560X_VBATREG_STEP_uV;

	वापस regmap_update_bits(bq->regmap, BQ256XX_BATTERY_VOLTAGE_LIMIT,
				BQ256XX_VBATREG_MASK, vbatreg_reg_code <<
						BQ256XX_VBATREG_BIT_SHIFT);
पूर्ण

अटल पूर्णांक bq256xx_get_prechrg_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक prechg_and_term_curr_lim;
	अचिन्हित पूर्णांक iprechg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
						&prechg_and_term_curr_lim);
	अगर (ret)
		वापस ret;

	iprechg_reg_code = (prechg_and_term_curr_lim & BQ256XX_IPRECHG_MASK)
						>> BQ256XX_IPRECHG_BIT_SHIFT;

	वापस (iprechg_reg_code * BQ256XX_IPRECHG_STEP_uA) +
						BQ256XX_IPRECHG_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq256xx_set_prechrg_curr(काष्ठा bq256xx_device *bq, पूर्णांक iprechg)
अणु
	अचिन्हित पूर्णांक iprechg_reg_code;

	iprechg = clamp(iprechg, BQ256XX_IPRECHG_MIN_uA,
						BQ256XX_IPRECHG_MAX_uA);

	iprechg_reg_code = ((iprechg - BQ256XX_IPRECHG_OFFSET_uA) /
			BQ256XX_IPRECHG_STEP_uA) << BQ256XX_IPRECHG_BIT_SHIFT;

	वापस regmap_update_bits(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
				BQ256XX_IPRECHG_MASK, iprechg_reg_code);
पूर्ण

अटल पूर्णांक bq25618_619_get_prechrg_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक prechg_and_term_curr_lim;
	अचिन्हित पूर्णांक iprechg_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
						&prechg_and_term_curr_lim);
	अगर (ret)
		वापस ret;

	iprechg_reg_code = (prechg_and_term_curr_lim & BQ256XX_IPRECHG_MASK)
						>> BQ256XX_IPRECHG_BIT_SHIFT;

	वापस (iprechg_reg_code * BQ25618_IPRECHG_STEP_uA) +
						BQ25618_IPRECHG_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq25618_619_set_prechrg_curr(काष्ठा bq256xx_device *bq, पूर्णांक iprechg)
अणु
	अचिन्हित पूर्णांक iprechg_reg_code;

	iprechg = clamp(iprechg, BQ25618_IPRECHG_MIN_uA,
						BQ25618_IPRECHG_MAX_uA);

	iprechg_reg_code = ((iprechg - BQ25618_IPRECHG_OFFSET_uA) /
			BQ25618_IPRECHG_STEP_uA) << BQ256XX_IPRECHG_BIT_SHIFT;

	वापस regmap_update_bits(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
				BQ256XX_IPRECHG_MASK, iprechg_reg_code);
पूर्ण

अटल पूर्णांक bq256xx_get_term_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक prechg_and_term_curr_lim;
	अचिन्हित पूर्णांक iterm_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
						&prechg_and_term_curr_lim);
	अगर (ret)
		वापस ret;

	iterm_reg_code = prechg_and_term_curr_lim & BQ256XX_ITERM_MASK;

	वापस (iterm_reg_code * BQ256XX_ITERM_STEP_uA) +
						BQ256XX_ITERM_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq256xx_set_term_curr(काष्ठा bq256xx_device *bq, पूर्णांक iterm)
अणु
	अचिन्हित पूर्णांक iterm_reg_code;

	iterm = clamp(iterm, BQ256XX_ITERM_MIN_uA, BQ256XX_ITERM_MAX_uA);

	iterm_reg_code = (iterm - BQ256XX_ITERM_OFFSET_uA) /
							BQ256XX_ITERM_STEP_uA;

	वापस regmap_update_bits(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
				BQ256XX_ITERM_MASK, iterm_reg_code);
पूर्ण

अटल पूर्णांक bq25618_619_get_term_curr(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक prechg_and_term_curr_lim;
	अचिन्हित पूर्णांक iterm_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
						&prechg_and_term_curr_lim);
	अगर (ret)
		वापस ret;

	iterm_reg_code = prechg_and_term_curr_lim & BQ256XX_ITERM_MASK;

	वापस (iterm_reg_code * BQ25618_ITERM_STEP_uA) +
						BQ25618_ITERM_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq25618_619_set_term_curr(काष्ठा bq256xx_device *bq, पूर्णांक iterm)
अणु
	अचिन्हित पूर्णांक iterm_reg_code;

	iterm = clamp(iterm, BQ25618_ITERM_MIN_uA, BQ25618_ITERM_MAX_uA);

	iterm_reg_code = (iterm - BQ25618_ITERM_OFFSET_uA) /
							BQ25618_ITERM_STEP_uA;

	वापस regmap_update_bits(bq->regmap, BQ256XX_PRECHG_AND_TERM_CURR_LIM,
				BQ256XX_ITERM_MASK, iterm_reg_code);
पूर्ण

अटल पूर्णांक bq256xx_get_input_volt_lim(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक अक्षरger_control_2;
	अचिन्हित पूर्णांक vindpm_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_CHARGER_CONTROL_2,
						&अक्षरger_control_2);
	अगर (ret)
		वापस ret;

	vindpm_reg_code = अक्षरger_control_2 & BQ256XX_VINDPM_MASK;

	वापस (vindpm_reg_code * BQ256XX_VINDPM_STEP_uV) +
						BQ256XX_VINDPM_OFFSET_uV;
पूर्ण

अटल पूर्णांक bq256xx_set_input_volt_lim(काष्ठा bq256xx_device *bq, पूर्णांक vindpm)
अणु
	अचिन्हित पूर्णांक vindpm_reg_code;

	vindpm = clamp(vindpm, BQ256XX_VINDPM_MIN_uV, BQ256XX_VINDPM_MAX_uV);

	vindpm_reg_code = (vindpm - BQ256XX_VINDPM_OFFSET_uV) /
						BQ256XX_VINDPM_STEP_uV;

	वापस regmap_update_bits(bq->regmap, BQ256XX_CHARGER_CONTROL_2,
					BQ256XX_VINDPM_MASK, vindpm_reg_code);
पूर्ण

अटल पूर्णांक bq256xx_get_input_curr_lim(काष्ठा bq256xx_device *bq)
अणु
	अचिन्हित पूर्णांक input_current_limit;
	अचिन्हित पूर्णांक iindpm_reg_code;
	पूर्णांक ret;

	ret = regmap_पढ़ो(bq->regmap, BQ256XX_INPUT_CURRENT_LIMIT,
						&input_current_limit);
	अगर (ret)
		वापस ret;

	iindpm_reg_code = input_current_limit & BQ256XX_IINDPM_MASK;

	वापस (iindpm_reg_code * BQ256XX_IINDPM_STEP_uA) +
						BQ256XX_IINDPM_OFFSET_uA;
पूर्ण

अटल पूर्णांक bq256xx_set_input_curr_lim(काष्ठा bq256xx_device *bq, पूर्णांक iindpm)
अणु
	अचिन्हित पूर्णांक iindpm_reg_code;

	iindpm = clamp(iindpm, BQ256XX_IINDPM_MIN_uA, BQ256XX_IINDPM_MAX_uA);

	iindpm_reg_code = (iindpm - BQ256XX_IINDPM_OFFSET_uA) /
							BQ256XX_IINDPM_STEP_uA;

	वापस regmap_update_bits(bq->regmap, BQ256XX_INPUT_CURRENT_LIMIT,
					BQ256XX_IINDPM_MASK, iindpm_reg_code);
पूर्ण

अटल व्योम bq256xx_अक्षरger_reset(व्योम *data)
अणु
	काष्ठा bq256xx_device *bq = data;

	regmap_update_bits(bq->regmap, BQ256XX_PART_INFORMATION,
					BQ256XX_REG_RST, BQ256XX_REG_RST);

	अगर (!IS_ERR_OR_शून्य(bq->usb2_phy))
		usb_unरेजिस्टर_notअगरier(bq->usb2_phy, &bq->usb_nb);

	अगर (!IS_ERR_OR_शून्य(bq->usb3_phy))
		usb_unरेजिस्टर_notअगरier(bq->usb3_phy, &bq->usb_nb);
पूर्ण

अटल पूर्णांक bq256xx_set_अक्षरger_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property prop,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq256xx_device *bq = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = -EINVAL;

	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq->chip_info->bq256xx_set_iindpm(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq->chip_info->bq256xx_set_vbatreg(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq->chip_info->bq256xx_set_ichg(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq->chip_info->bq256xx_set_iprechg(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = bq->chip_info->bq256xx_set_iterm(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = bq->chip_info->bq256xx_set_vindpm(bq, val->पूर्णांकval);
		अगर (ret)
			वापस ret;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण


अटल पूर्णांक bq256xx_get_battery_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq256xx_device *bq = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		val->पूर्णांकval = bq->init_data.ichg_max;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		val->पूर्णांकval = bq->init_data.vbatreg_max;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq256xx_get_अक्षरger_property(काष्ठा घातer_supply *psy,
				क्रमागत घातer_supply_property psp,
				जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq256xx_device *bq = घातer_supply_get_drvdata(psy);
	काष्ठा bq256xx_state state;
	पूर्णांक ret = 0;

	mutex_lock(&bq->lock);
	ret = bq256xx_get_state(bq, &state);
	mutex_unlock(&bq->lock);
	अगर (ret)
		वापस ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		अगर (state.vbus_stat == BQ256XX_VBUS_STAT_NO_INPUT ||
		    state.vbus_stat == BQ256XX_VBUS_STAT_USB_OTG)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा अगर (state.chrg_stat == BQ256XX_CHRG_STAT_NOT_CHRGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा अगर (state.chrg_stat == BQ256XX_CHRG_STAT_CHRG_TERM)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
		अगर (state.wdt_fault) अणु
			val->पूर्णांकval =
				POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE;
		पूर्ण अन्यथा अगर (state.bat_fault) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		पूर्ण अन्यथा अणु
			चयन (state.chrg_stat) अणु
			हाल BQ256XX_CHRG_FAULT_INPUT:
				val->पूर्णांकval =
					POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
				अवरोध;
			हाल BQ256XX_CHRG_FAULT_THERM:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
				अवरोध;
			हाल BQ256XX_CHRG_FAULT_CST_EXPIRE:
				val->पूर्णांकval =
				POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			चयन (state.ntc_fault) अणु
			हाल BQ256XX_NTC_FAULT_WARM:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_WARM;
				अवरोध;
			हाल BQ256XX_NTC_FAULT_COOL:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_COOL;
				अवरोध;
			हाल BQ256XX_NTC_FAULT_COLD:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
				अवरोध;
			हाल BQ256XX_NTC_FAULT_HOT:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_HOT;
				अवरोध;
			शेष:
				val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_USB_TYPE:
		अगर (bq->chip_info->has_usb_detect) अणु
			चयन (state.vbus_stat) अणु
			हाल BQ256XX_VBUS_STAT_USB_SDP:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_SDP;
				अवरोध;
			हाल BQ256XX_VBUS_STAT_USB_CDP:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_CDP;
				अवरोध;
			हाल BQ256XX_VBUS_STAT_USB_DCP:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_DCP;
				अवरोध;
			हाल BQ256XX_VBUS_STAT_USB_OTG:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_ACA;
				अवरोध;
			शेष:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_UNKNOWN;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (state.vbus_stat) अणु
			हाल BQ256XX_VBUS_STAT_USB_SDP:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_SDP;
				अवरोध;
			हाल BQ256XX_VBUS_STAT_USB_OTG:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_ACA;
				अवरोध;
			शेष:
				val->पूर्णांकval = POWER_SUPPLY_USB_TYPE_UNKNOWN;
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		चयन (state.chrg_stat) अणु
		हाल BQ256XX_CHRG_STAT_NOT_CHRGING:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			अवरोध;
		हाल BQ256XX_CHRG_STAT_PRECHRGING:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		हाल BQ256XX_CHRG_STAT_FAST_CHRGING:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
			अवरोध;
		हाल BQ256XX_CHRG_STAT_CHRG_TERM:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_UNKNOWN;
		पूर्ण
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ256XX_MANUFACTURER;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bq->model_name;
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = state.online;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		ret = bq->chip_info->bq256xx_get_vindpm(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq->chip_info->bq256xx_get_iindpm(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq->chip_info->bq256xx_get_vbatreg(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq->chip_info->bq256xx_get_ichg(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq->chip_info->bq256xx_get_iprechg(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = bq->chip_info->bq256xx_get_iterm(bq);
		अगर (ret < 0)
			वापस ret;
		val->पूर्णांकval = ret;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool bq256xx_state_changed(काष्ठा bq256xx_device *bq,
				  काष्ठा bq256xx_state *new_state)
अणु
	काष्ठा bq256xx_state old_state;

	mutex_lock(&bq->lock);
	old_state = bq->state;
	mutex_unlock(&bq->lock);

	वापस स_भेद(&old_state, new_state, माप(काष्ठा bq256xx_state)) != 0;
पूर्ण

अटल irqवापस_t bq256xx_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा bq256xx_device *bq = निजी;
	काष्ठा bq256xx_state state;
	पूर्णांक ret;

	ret = bq256xx_get_state(bq, &state);
	अगर (ret < 0)
		जाओ irq_out;

	अगर (!bq256xx_state_changed(bq, &state))
		जाओ irq_out;

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	घातer_supply_changed(bq->अक्षरger);

irq_out:
	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत घातer_supply_property bq256xx_घातer_supply_props[] = अणु
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_USB_TYPE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
पूर्ण;

अटल क्रमागत घातer_supply_property bq256xx_battery_props[] = अणु
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
पूर्ण;

अटल पूर्णांक bq256xx_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
					 क्रमागत घातer_supply_property prop)
अणु
	चयन (prop) अणु
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
	हाल POWER_SUPPLY_PROP_STATUS:
	हाल POWER_SUPPLY_PROP_INPUT_VOLTAGE_LIMIT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc bq256xx_घातer_supply_desc = अणु
	.name = "bq256xx-charger",
	.type = POWER_SUPPLY_TYPE_USB,
	.usb_types = bq256xx_usb_type,
	.num_usb_types = ARRAY_SIZE(bq256xx_usb_type),
	.properties = bq256xx_घातer_supply_props,
	.num_properties = ARRAY_SIZE(bq256xx_घातer_supply_props),
	.get_property = bq256xx_get_अक्षरger_property,
	.set_property = bq256xx_set_अक्षरger_property,
	.property_is_ग_लिखोable = bq256xx_property_is_ग_लिखोable,
पूर्ण;

अटल काष्ठा घातer_supply_desc bq256xx_battery_desc = अणु
	.name			= "bq256xx-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.get_property		= bq256xx_get_battery_property,
	.properties		= bq256xx_battery_props,
	.num_properties		= ARRAY_SIZE(bq256xx_battery_props),
	.property_is_ग_लिखोable	= bq256xx_property_is_ग_लिखोable,
पूर्ण;


अटल bool bq256xx_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल BQ256XX_INPUT_CURRENT_LIMIT:
	हाल BQ256XX_CHARGER_STATUS_0...BQ256XX_CHARGER_STATUS_2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config bq25600_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ256XX_PART_INFORMATION,
	.reg_शेषs	= bq2560x_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq2560x_reg_defs),
	.cache_type = REGCACHE_FLAT,
	.अस्थिर_reg = bq256xx_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25611d_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ256XX_CHARGER_CONTROL_4,
	.reg_शेषs	= bq25611d_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq25611d_reg_defs),
	.cache_type = REGCACHE_FLAT,
	.अस्थिर_reg = bq256xx_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा regmap_config bq25618_619_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = BQ256XX_CHARGER_CONTROL_4,
	.reg_शेषs	= bq25618_619_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(bq25618_619_reg_defs),
	.cache_type = REGCACHE_FLAT,
	.अस्थिर_reg = bq256xx_is_अस्थिर_reg,
पूर्ण;

अटल स्थिर काष्ठा bq256xx_chip_info bq256xx_chip_info_tbl[] = अणु
	[BQ25600] = अणु
		.model_id = BQ25600,
		.bq256xx_regmap_config = &bq25600_regmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq2560x_get_chrg_volt,
		.bq256xx_get_iterm = bq256xx_get_term_curr,
		.bq256xx_get_iprechg = bq256xx_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq256xx_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq2560x_set_chrg_volt,
		.bq256xx_set_iterm = bq256xx_set_term_curr,
		.bq256xx_set_iprechg = bq256xx_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ2560X_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ256XX_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ256XX_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ2560X_VBATREG_MAX_uV,

		.has_usb_detect = false,
	पूर्ण,

	[BQ25600D] = अणु
		.model_id = BQ25600D,
		.bq256xx_regmap_config = &bq25600_regmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq2560x_get_chrg_volt,
		.bq256xx_get_iterm = bq256xx_get_term_curr,
		.bq256xx_get_iprechg = bq256xx_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq256xx_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq2560x_set_chrg_volt,
		.bq256xx_set_iterm = bq256xx_set_term_curr,
		.bq256xx_set_iprechg = bq256xx_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ2560X_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ256XX_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ256XX_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ2560X_VBATREG_MAX_uV,

		.has_usb_detect = true,
	पूर्ण,

	[BQ25601] = अणु
		.model_id = BQ25601,
		.bq256xx_regmap_config = &bq25600_regmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq2560x_get_chrg_volt,
		.bq256xx_get_iterm = bq256xx_get_term_curr,
		.bq256xx_get_iprechg = bq256xx_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq256xx_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq2560x_set_chrg_volt,
		.bq256xx_set_iterm = bq256xx_set_term_curr,
		.bq256xx_set_iprechg = bq256xx_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ2560X_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ256XX_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ256XX_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ2560X_VBATREG_MAX_uV,

		.has_usb_detect = false,
	पूर्ण,

	[BQ25601D] = अणु
		.model_id = BQ25601D,
		.bq256xx_regmap_config = &bq25600_regmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq25601d_get_chrg_volt,
		.bq256xx_get_iterm = bq256xx_get_term_curr,
		.bq256xx_get_iprechg = bq256xx_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq256xx_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq25601d_set_chrg_volt,
		.bq256xx_set_iterm = bq256xx_set_term_curr,
		.bq256xx_set_iprechg = bq256xx_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ2560X_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ2560X_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ256XX_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ256XX_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ2560X_VBATREG_MAX_uV,

		.has_usb_detect = true,
	पूर्ण,

	[BQ25611D] = अणु
		.model_id = BQ25611D,
		.bq256xx_regmap_config = &bq25611d_regmap_config,
		.bq256xx_get_ichg = bq256xx_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq25611d_get_chrg_volt,
		.bq256xx_get_iterm = bq256xx_get_term_curr,
		.bq256xx_get_iprechg = bq256xx_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq256xx_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq25611d_set_chrg_volt,
		.bq256xx_set_iterm = bq256xx_set_term_curr,
		.bq256xx_set_iprechg = bq256xx_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ25611D_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ25611D_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ256XX_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ256XX_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ256XX_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ25611D_VBATREG_MAX_uV,

		.has_usb_detect = true,
	पूर्ण,

	[BQ25618] = अणु
		.model_id = BQ25618,
		.bq256xx_regmap_config = &bq25618_619_regmap_config,
		.bq256xx_get_ichg = bq25618_619_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq25618_619_get_chrg_volt,
		.bq256xx_get_iterm = bq25618_619_get_term_curr,
		.bq256xx_get_iprechg = bq25618_619_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq25618_619_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq25618_619_set_chrg_volt,
		.bq256xx_set_iterm = bq25618_619_set_term_curr,
		.bq256xx_set_iprechg = bq25618_619_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ25618_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ25618_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ25618_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ25618_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ25618_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ25618_VBATREG_MAX_uV,

		.has_usb_detect = false,
	पूर्ण,

	[BQ25619] = अणु
		.model_id = BQ25619,
		.bq256xx_regmap_config = &bq25618_619_regmap_config,
		.bq256xx_get_ichg = bq25618_619_get_ichg_curr,
		.bq256xx_get_iindpm = bq256xx_get_input_curr_lim,
		.bq256xx_get_vbatreg = bq25618_619_get_chrg_volt,
		.bq256xx_get_iterm = bq25618_619_get_term_curr,
		.bq256xx_get_iprechg = bq25618_619_get_prechrg_curr,
		.bq256xx_get_vindpm = bq256xx_get_input_volt_lim,

		.bq256xx_set_ichg = bq25618_619_set_ichg_curr,
		.bq256xx_set_iindpm = bq256xx_set_input_curr_lim,
		.bq256xx_set_vbatreg = bq25618_619_set_chrg_volt,
		.bq256xx_set_iterm = bq25618_619_set_term_curr,
		.bq256xx_set_iprechg = bq25618_619_set_prechrg_curr,
		.bq256xx_set_vindpm = bq256xx_set_input_volt_lim,

		.bq256xx_def_ichg = BQ25618_ICHG_DEF_uA,
		.bq256xx_def_iindpm = BQ256XX_IINDPM_DEF_uA,
		.bq256xx_def_vbatreg = BQ25618_VBATREG_DEF_uV,
		.bq256xx_def_iterm = BQ25618_ITERM_DEF_uA,
		.bq256xx_def_iprechg = BQ25618_IPRECHG_DEF_uA,
		.bq256xx_def_vindpm = BQ256XX_VINDPM_DEF_uV,

		.bq256xx_max_ichg = BQ25618_ICHG_MAX_uA,
		.bq256xx_max_vbatreg = BQ25618_VBATREG_MAX_uV,

		.has_usb_detect = false,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bq256xx_घातer_supply_init(काष्ठा bq256xx_device *bq,
		काष्ठा घातer_supply_config *psy_cfg, काष्ठा device *dev)
अणु
	bq->अक्षरger = devm_घातer_supply_रेजिस्टर(bq->dev,
						 &bq256xx_घातer_supply_desc,
						 psy_cfg);
	अगर (IS_ERR(bq->अक्षरger)) अणु
		dev_err(dev, "power supply register charger failed\n");
		वापस PTR_ERR(bq->अक्षरger);
	पूर्ण

	bq->battery = devm_घातer_supply_रेजिस्टर(bq->dev,
						      &bq256xx_battery_desc,
						      psy_cfg);
	अगर (IS_ERR(bq->battery)) अणु
		dev_err(dev, "power supply register battery failed\n");
		वापस PTR_ERR(bq->battery);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक bq256xx_hw_init(काष्ठा bq256xx_device *bq)
अणु
	काष्ठा घातer_supply_battery_info bat_info = अणु पूर्ण;
	पूर्णांक wd_reg_val = BQ256XX_WATCHDOG_DIS;
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < BQ256XX_NUM_WD_VAL; i++) अणु
		अगर (bq->watchकरोg_समयr == bq256xx_watchकरोg_समय[i]) अणु
			wd_reg_val = i;
			अवरोध;
		पूर्ण
		अगर (bq->watchकरोg_समयr > bq256xx_watchकरोg_समय[i] &&
		    bq->watchकरोg_समयr < bq256xx_watchकरोg_समय[i + 1])
			wd_reg_val = i;
	पूर्ण
	ret = regmap_update_bits(bq->regmap, BQ256XX_CHARGER_CONTROL_1,
				 BQ256XX_WATCHDOG_MASK, wd_reg_val <<
						BQ256XX_WDT_BIT_SHIFT);

	ret = घातer_supply_get_battery_info(bq->अक्षरger, &bat_info);
	अगर (ret) अणु
		dev_warn(bq->dev, "battery info missing, default values will be applied\n");

		bat_info.स्थिरant_अक्षरge_current_max_ua =
				bq->chip_info->bq256xx_def_ichg;

		bat_info.स्थिरant_अक्षरge_voltage_max_uv =
				bq->chip_info->bq256xx_def_vbatreg;

		bat_info.preअक्षरge_current_ua =
				bq->chip_info->bq256xx_def_iprechg;

		bat_info.अक्षरge_term_current_ua =
				bq->chip_info->bq256xx_def_iterm;

		bq->init_data.ichg_max =
				bq->chip_info->bq256xx_max_ichg;

		bq->init_data.vbatreg_max =
				bq->chip_info->bq256xx_max_vbatreg;
	पूर्ण अन्यथा अणु
		bq->init_data.ichg_max =
			bat_info.स्थिरant_अक्षरge_current_max_ua;

		bq->init_data.vbatreg_max =
			bat_info.स्थिरant_अक्षरge_voltage_max_uv;
	पूर्ण

	ret = bq->chip_info->bq256xx_set_vindpm(bq, bq->init_data.vindpm);
	अगर (ret)
		वापस ret;

	ret = bq->chip_info->bq256xx_set_iindpm(bq, bq->init_data.iindpm);
	अगर (ret)
		वापस ret;

	ret = bq->chip_info->bq256xx_set_ichg(bq,
				bat_info.स्थिरant_अक्षरge_current_max_ua);
	अगर (ret)
		वापस ret;

	ret = bq->chip_info->bq256xx_set_iprechg(bq,
				bat_info.preअक्षरge_current_ua);
	अगर (ret)
		वापस ret;

	ret = bq->chip_info->bq256xx_set_vbatreg(bq,
				bat_info.स्थिरant_अक्षरge_voltage_max_uv);
	अगर (ret)
		वापस ret;

	ret = bq->chip_info->bq256xx_set_iterm(bq,
				bat_info.अक्षरge_term_current_ua);
	अगर (ret)
		वापस ret;

	घातer_supply_put_battery_info(bq->अक्षरger, &bat_info);

	वापस 0;
पूर्ण

अटल पूर्णांक bq256xx_parse_dt(काष्ठा bq256xx_device *bq,
		काष्ठा घातer_supply_config *psy_cfg, काष्ठा device *dev)
अणु
	पूर्णांक ret = 0;

	psy_cfg->drv_data = bq;
	psy_cfg->of_node = dev->of_node;

	ret = device_property_पढ़ो_u32(bq->dev, "ti,watchdog-timeout-ms",
				       &bq->watchकरोg_समयr);
	अगर (ret)
		bq->watchकरोg_समयr = BQ256XX_WATCHDOG_DIS;

	अगर (bq->watchकरोg_समयr > BQ256XX_WATCHDOG_MAX ||
	    bq->watchकरोg_समयr < BQ256XX_WATCHDOG_DIS)
		वापस -EINVAL;

	ret = device_property_पढ़ो_u32(bq->dev,
				       "input-voltage-limit-microvolt",
				       &bq->init_data.vindpm);
	अगर (ret)
		bq->init_data.vindpm = bq->chip_info->bq256xx_def_vindpm;

	ret = device_property_पढ़ो_u32(bq->dev,
				       "input-current-limit-microamp",
				       &bq->init_data.iindpm);
	अगर (ret)
		bq->init_data.iindpm = bq->chip_info->bq256xx_def_iindpm;

	वापस 0;
पूर्ण

अटल पूर्णांक bq256xx_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bq256xx_device *bq;
	काष्ठा घातer_supply_config psy_cfg = अणु पूर्ण;

	पूर्णांक ret;

	bq = devm_kzalloc(dev, माप(*bq), GFP_KERNEL);
	अगर (!bq)
		वापस -ENOMEM;

	bq->client = client;
	bq->dev = dev;
	bq->chip_info = &bq256xx_chip_info_tbl[id->driver_data];

	mutex_init(&bq->lock);

	म_नकलन(bq->model_name, id->name, I2C_NAME_SIZE);

	bq->regmap = devm_regmap_init_i2c(client,
					bq->chip_info->bq256xx_regmap_config);

	अगर (IS_ERR(bq->regmap)) अणु
		dev_err(dev, "Failed to allocate register map\n");
		वापस PTR_ERR(bq->regmap);
	पूर्ण

	i2c_set_clientdata(client, bq);

	ret = bq256xx_parse_dt(bq, &psy_cfg, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to read device tree properties%d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_add_action_or_reset(dev, bq256xx_अक्षरger_reset, bq);
	अगर (ret)
		वापस ret;

	/* OTG reporting */
	bq->usb2_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB2);
	अगर (!IS_ERR_OR_शून्य(bq->usb2_phy)) अणु
		INIT_WORK(&bq->usb_work, bq256xx_usb_work);
		bq->usb_nb.notअगरier_call = bq256xx_usb_notअगरier;
		usb_रेजिस्टर_notअगरier(bq->usb2_phy, &bq->usb_nb);
	पूर्ण

	bq->usb3_phy = devm_usb_get_phy(dev, USB_PHY_TYPE_USB3);
	अगर (!IS_ERR_OR_शून्य(bq->usb3_phy)) अणु
		INIT_WORK(&bq->usb_work, bq256xx_usb_work);
		bq->usb_nb.notअगरier_call = bq256xx_usb_notअगरier;
		usb_रेजिस्टर_notअगरier(bq->usb3_phy, &bq->usb_nb);
	पूर्ण

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						bq256xx_irq_handler_thपढ़ो,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						dev_name(&client->dev), bq);
		अगर (ret < 0) अणु
			dev_err(dev, "get irq fail: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = bq256xx_घातer_supply_init(bq, &psy_cfg, dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register power supply\n");
		वापस ret;
	पूर्ण

	ret = bq256xx_hw_init(bq);
	अगर (ret) अणु
		dev_err(dev, "Cannot initialize the chip.\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq256xx_i2c_ids[] = अणु
	अणु "bq25600", BQ25600 पूर्ण,
	अणु "bq25600d", BQ25600D पूर्ण,
	अणु "bq25601", BQ25601 पूर्ण,
	अणु "bq25601d", BQ25601D पूर्ण,
	अणु "bq25611d", BQ25611D पूर्ण,
	अणु "bq25618", BQ25618 पूर्ण,
	अणु "bq25619", BQ25619 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq256xx_i2c_ids);

अटल स्थिर काष्ठा of_device_id bq256xx_of_match[] = अणु
	अणु .compatible = "ti,bq25600", .data = (व्योम *)BQ25600 पूर्ण,
	अणु .compatible = "ti,bq25600d", .data = (व्योम *)BQ25600D पूर्ण,
	अणु .compatible = "ti,bq25601", .data = (व्योम *)BQ25601 पूर्ण,
	अणु .compatible = "ti,bq25601d", .data = (व्योम *)BQ25601D पूर्ण,
	अणु .compatible = "ti,bq25611d", .data = (व्योम *)BQ25611D पूर्ण,
	अणु .compatible = "ti,bq25618", .data = (व्योम *)BQ25618 पूर्ण,
	अणु .compatible = "ti,bq25619", .data = (व्योम *)BQ25619 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq256xx_of_match);

अटल स्थिर काष्ठा acpi_device_id bq256xx_acpi_match[] = अणु
	अणु "bq25600", BQ25600 पूर्ण,
	अणु "bq25600d", BQ25600D पूर्ण,
	अणु "bq25601", BQ25601 पूर्ण,
	अणु "bq25601d", BQ25601D पूर्ण,
	अणु "bq25611d", BQ25611D पूर्ण,
	अणु "bq25618", BQ25618 पूर्ण,
	अणु "bq25619", BQ25619 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bq256xx_acpi_match);

अटल काष्ठा i2c_driver bq256xx_driver = अणु
	.driver = अणु
		.name = "bq256xx-charger",
		.of_match_table = bq256xx_of_match,
		.acpi_match_table = bq256xx_acpi_match,
	पूर्ण,
	.probe = bq256xx_probe,
	.id_table = bq256xx_i2c_ids,
पूर्ण;
module_i2c_driver(bq256xx_driver);

MODULE_AUTHOR("Ricardo Rivera-Matos <r-rivera-matos@ti.com>");
MODULE_DESCRIPTION("bq256xx charger driver");
MODULE_LICENSE("GPL v2");
