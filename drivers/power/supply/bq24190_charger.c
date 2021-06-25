<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the TI bq24190 battery अक्षरger.
 *
 * Author: Mark A. Greer <mgreer@animalcreek.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/घातer/bq24190_अक्षरger.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/i2c.h>
#समावेश <linux/extcon-provider.h>

#घोषणा	BQ24190_MANUFACTURER	"Texas Instruments"

#घोषणा BQ24190_REG_ISC		0x00 /* Input Source Control */
#घोषणा BQ24190_REG_ISC_EN_HIZ_MASK		BIT(7)
#घोषणा BQ24190_REG_ISC_EN_HIZ_SHIFT		7
#घोषणा BQ24190_REG_ISC_VINDPM_MASK		(BIT(6) | BIT(5) | BIT(4) | \
						 BIT(3))
#घोषणा BQ24190_REG_ISC_VINDPM_SHIFT		3
#घोषणा BQ24190_REG_ISC_IINLIM_MASK		(BIT(2) | BIT(1) | BIT(0))
#घोषणा BQ24190_REG_ISC_IINLIM_SHIFT		0

#घोषणा BQ24190_REG_POC		0x01 /* Power-On Configuration */
#घोषणा BQ24190_REG_POC_RESET_MASK		BIT(7)
#घोषणा BQ24190_REG_POC_RESET_SHIFT		7
#घोषणा BQ24190_REG_POC_WDT_RESET_MASK		BIT(6)
#घोषणा BQ24190_REG_POC_WDT_RESET_SHIFT		6
#घोषणा BQ24190_REG_POC_CHG_CONFIG_MASK		(BIT(5) | BIT(4))
#घोषणा BQ24190_REG_POC_CHG_CONFIG_SHIFT	4
#घोषणा BQ24190_REG_POC_CHG_CONFIG_DISABLE		0x0
#घोषणा BQ24190_REG_POC_CHG_CONFIG_CHARGE		0x1
#घोषणा BQ24190_REG_POC_CHG_CONFIG_OTG			0x2
#घोषणा BQ24190_REG_POC_SYS_MIN_MASK		(BIT(3) | BIT(2) | BIT(1))
#घोषणा BQ24190_REG_POC_SYS_MIN_SHIFT		1
#घोषणा BQ24190_REG_POC_SYS_MIN_MIN			3000
#घोषणा BQ24190_REG_POC_SYS_MIN_MAX			3700
#घोषणा BQ24190_REG_POC_BOOST_LIM_MASK		BIT(0)
#घोषणा BQ24190_REG_POC_BOOST_LIM_SHIFT		0

#घोषणा BQ24190_REG_CCC		0x02 /* Charge Current Control */
#घोषणा BQ24190_REG_CCC_ICHG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4) | BIT(3) | BIT(2))
#घोषणा BQ24190_REG_CCC_ICHG_SHIFT		2
#घोषणा BQ24190_REG_CCC_FORCE_20PCT_MASK	BIT(0)
#घोषणा BQ24190_REG_CCC_FORCE_20PCT_SHIFT	0

#घोषणा BQ24190_REG_PCTCC	0x03 /* Pre-अक्षरge/Termination Current Cntl */
#घोषणा BQ24190_REG_PCTCC_IPRECHG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4))
#घोषणा BQ24190_REG_PCTCC_IPRECHG_SHIFT		4
#घोषणा BQ24190_REG_PCTCC_IPRECHG_MIN			128
#घोषणा BQ24190_REG_PCTCC_IPRECHG_MAX			2048
#घोषणा BQ24190_REG_PCTCC_ITERM_MASK		(BIT(3) | BIT(2) | BIT(1) | \
						 BIT(0))
#घोषणा BQ24190_REG_PCTCC_ITERM_SHIFT		0
#घोषणा BQ24190_REG_PCTCC_ITERM_MIN			128
#घोषणा BQ24190_REG_PCTCC_ITERM_MAX			2048

#घोषणा BQ24190_REG_CVC		0x04 /* Charge Voltage Control */
#घोषणा BQ24190_REG_CVC_VREG_MASK		(BIT(7) | BIT(6) | BIT(5) | \
						 BIT(4) | BIT(3) | BIT(2))
#घोषणा BQ24190_REG_CVC_VREG_SHIFT		2
#घोषणा BQ24190_REG_CVC_BATLOWV_MASK		BIT(1)
#घोषणा BQ24190_REG_CVC_BATLOWV_SHIFT		1
#घोषणा BQ24190_REG_CVC_VRECHG_MASK		BIT(0)
#घोषणा BQ24190_REG_CVC_VRECHG_SHIFT		0

#घोषणा BQ24190_REG_CTTC	0x05 /* Charge Term/Timer Control */
#घोषणा BQ24190_REG_CTTC_EN_TERM_MASK		BIT(7)
#घोषणा BQ24190_REG_CTTC_EN_TERM_SHIFT		7
#घोषणा BQ24190_REG_CTTC_TERM_STAT_MASK		BIT(6)
#घोषणा BQ24190_REG_CTTC_TERM_STAT_SHIFT	6
#घोषणा BQ24190_REG_CTTC_WATCHDOG_MASK		(BIT(5) | BIT(4))
#घोषणा BQ24190_REG_CTTC_WATCHDOG_SHIFT		4
#घोषणा BQ24190_REG_CTTC_EN_TIMER_MASK		BIT(3)
#घोषणा BQ24190_REG_CTTC_EN_TIMER_SHIFT		3
#घोषणा BQ24190_REG_CTTC_CHG_TIMER_MASK		(BIT(2) | BIT(1))
#घोषणा BQ24190_REG_CTTC_CHG_TIMER_SHIFT	1
#घोषणा BQ24190_REG_CTTC_JEITA_ISET_MASK	BIT(0)
#घोषणा BQ24190_REG_CTTC_JEITA_ISET_SHIFT	0

#घोषणा BQ24190_REG_ICTRC	0x06 /* IR Comp/Thermal Regulation Control */
#घोषणा BQ24190_REG_ICTRC_BAT_COMP_MASK		(BIT(7) | BIT(6) | BIT(5))
#घोषणा BQ24190_REG_ICTRC_BAT_COMP_SHIFT	5
#घोषणा BQ24190_REG_ICTRC_VCLAMP_MASK		(BIT(4) | BIT(3) | BIT(2))
#घोषणा BQ24190_REG_ICTRC_VCLAMP_SHIFT		2
#घोषणा BQ24190_REG_ICTRC_TREG_MASK		(BIT(1) | BIT(0))
#घोषणा BQ24190_REG_ICTRC_TREG_SHIFT		0

#घोषणा BQ24190_REG_MOC		0x07 /* Misc. Operation Control */
#घोषणा BQ24190_REG_MOC_DPDM_EN_MASK		BIT(7)
#घोषणा BQ24190_REG_MOC_DPDM_EN_SHIFT		7
#घोषणा BQ24190_REG_MOC_TMR2X_EN_MASK		BIT(6)
#घोषणा BQ24190_REG_MOC_TMR2X_EN_SHIFT		6
#घोषणा BQ24190_REG_MOC_BATFET_DISABLE_MASK	BIT(5)
#घोषणा BQ24190_REG_MOC_BATFET_DISABLE_SHIFT	5
#घोषणा BQ24190_REG_MOC_JEITA_VSET_MASK		BIT(4)
#घोषणा BQ24190_REG_MOC_JEITA_VSET_SHIFT	4
#घोषणा BQ24190_REG_MOC_INT_MASK_MASK		(BIT(1) | BIT(0))
#घोषणा BQ24190_REG_MOC_INT_MASK_SHIFT		0

#घोषणा BQ24190_REG_SS		0x08 /* System Status */
#घोषणा BQ24190_REG_SS_VBUS_STAT_MASK		(BIT(7) | BIT(6))
#घोषणा BQ24190_REG_SS_VBUS_STAT_SHIFT		6
#घोषणा BQ24190_REG_SS_CHRG_STAT_MASK		(BIT(5) | BIT(4))
#घोषणा BQ24190_REG_SS_CHRG_STAT_SHIFT		4
#घोषणा BQ24190_REG_SS_DPM_STAT_MASK		BIT(3)
#घोषणा BQ24190_REG_SS_DPM_STAT_SHIFT		3
#घोषणा BQ24190_REG_SS_PG_STAT_MASK		BIT(2)
#घोषणा BQ24190_REG_SS_PG_STAT_SHIFT		2
#घोषणा BQ24190_REG_SS_THERM_STAT_MASK		BIT(1)
#घोषणा BQ24190_REG_SS_THERM_STAT_SHIFT		1
#घोषणा BQ24190_REG_SS_VSYS_STAT_MASK		BIT(0)
#घोषणा BQ24190_REG_SS_VSYS_STAT_SHIFT		0

#घोषणा BQ24190_REG_F		0x09 /* Fault */
#घोषणा BQ24190_REG_F_WATCHDOG_FAULT_MASK	BIT(7)
#घोषणा BQ24190_REG_F_WATCHDOG_FAULT_SHIFT	7
#घोषणा BQ24190_REG_F_BOOST_FAULT_MASK		BIT(6)
#घोषणा BQ24190_REG_F_BOOST_FAULT_SHIFT		6
#घोषणा BQ24190_REG_F_CHRG_FAULT_MASK		(BIT(5) | BIT(4))
#घोषणा BQ24190_REG_F_CHRG_FAULT_SHIFT		4
#घोषणा BQ24190_REG_F_BAT_FAULT_MASK		BIT(3)
#घोषणा BQ24190_REG_F_BAT_FAULT_SHIFT		3
#घोषणा BQ24190_REG_F_NTC_FAULT_MASK		(BIT(2) | BIT(1) | BIT(0))
#घोषणा BQ24190_REG_F_NTC_FAULT_SHIFT		0

#घोषणा BQ24190_REG_VPRS	0x0A /* Venकरोr/Part/Revision Status */
#घोषणा BQ24190_REG_VPRS_PN_MASK		(BIT(5) | BIT(4) | BIT(3))
#घोषणा BQ24190_REG_VPRS_PN_SHIFT		3
#घोषणा BQ24190_REG_VPRS_PN_24190			0x4
#घोषणा BQ24190_REG_VPRS_PN_24192			0x5 /* Also 24193, 24196 */
#घोषणा BQ24190_REG_VPRS_PN_24192I			0x3
#घोषणा BQ24190_REG_VPRS_TS_PROखाता_MASK	BIT(2)
#घोषणा BQ24190_REG_VPRS_TS_PROखाता_SHIFT	2
#घोषणा BQ24190_REG_VPRS_DEV_REG_MASK		(BIT(1) | BIT(0))
#घोषणा BQ24190_REG_VPRS_DEV_REG_SHIFT		0

/*
 * The FAULT रेजिस्टर is latched by the bq24190 (except क्रम NTC_FAULT)
 * so the first पढ़ो after a fault वापसs the latched value and subsequent
 * पढ़ोs वापस the current value.  In order to वापस the fault status
 * to the user, have the पूर्णांकerrupt handler save the reg's value and retrieve
 * it in the appropriate health/status routine.
 */
काष्ठा bq24190_dev_info अणु
	काष्ठा i2c_client		*client;
	काष्ठा device			*dev;
	काष्ठा extcon_dev		*edev;
	काष्ठा घातer_supply		*अक्षरger;
	काष्ठा घातer_supply		*battery;
	काष्ठा delayed_work		input_current_limit_work;
	अक्षर				model_name[I2C_NAME_SIZE];
	bool				initialized;
	bool				irq_event;
	u16				sys_min;
	u16				iprechg;
	u16				iterm;
	काष्ठा mutex			f_reg_lock;
	u8				f_reg;
	u8				ss_reg;
	u8				watchकरोg;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक bq24190_usb_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_NONE,
पूर्ण;

/*
 * The tables below provide a 2-way mapping क्रम the value that goes in
 * the रेजिस्टर field and the real-world value that it represents.
 * The index of the array is the value that goes in the रेजिस्टर; the
 * number at that index in the array is the real-world value that it
 * represents.
 */

/* REG00[2:0] (IINLIM) in uAh */
अटल स्थिर पूर्णांक bq24190_isc_iinlim_values[] = अणु
	 100000,  150000,  500000,  900000, 1200000, 1500000, 2000000, 3000000
पूर्ण;

/* REG02[7:2] (ICHG) in uAh */
अटल स्थिर पूर्णांक bq24190_ccc_ichg_values[] = अणु
	 512000,  576000,  640000,  704000,  768000,  832000,  896000,  960000,
	1024000, 1088000, 1152000, 1216000, 1280000, 1344000, 1408000, 1472000,
	1536000, 1600000, 1664000, 1728000, 1792000, 1856000, 1920000, 1984000,
	2048000, 2112000, 2176000, 2240000, 2304000, 2368000, 2432000, 2496000,
	2560000, 2624000, 2688000, 2752000, 2816000, 2880000, 2944000, 3008000,
	3072000, 3136000, 3200000, 3264000, 3328000, 3392000, 3456000, 3520000,
	3584000, 3648000, 3712000, 3776000, 3840000, 3904000, 3968000, 4032000,
	4096000, 4160000, 4224000, 4288000, 4352000, 4416000, 4480000, 4544000
पूर्ण;

/* REG04[7:2] (VREG) in uV */
अटल स्थिर पूर्णांक bq24190_cvc_vreg_values[] = अणु
	3504000, 3520000, 3536000, 3552000, 3568000, 3584000, 3600000, 3616000,
	3632000, 3648000, 3664000, 3680000, 3696000, 3712000, 3728000, 3744000,
	3760000, 3776000, 3792000, 3808000, 3824000, 3840000, 3856000, 3872000,
	3888000, 3904000, 3920000, 3936000, 3952000, 3968000, 3984000, 4000000,
	4016000, 4032000, 4048000, 4064000, 4080000, 4096000, 4112000, 4128000,
	4144000, 4160000, 4176000, 4192000, 4208000, 4224000, 4240000, 4256000,
	4272000, 4288000, 4304000, 4320000, 4336000, 4352000, 4368000, 4384000,
	4400000
पूर्ण;

/* REG06[1:0] (TREG) in tenths of degrees Celsius */
अटल स्थिर पूर्णांक bq24190_ictrc_treg_values[] = अणु
	600, 800, 1000, 1200
पूर्ण;

/*
 * Return the index in 'tbl' of greatest value that is less than or equal to
 * 'val'.  The index range returned is 0 to 'tbl_size' - 1.  Assumes that
 * the values in 'tbl' are sorted from smallest to largest and 'tbl_size'
 * is less than 2^8.
 */
अटल u8 bq24190_find_idx(स्थिर पूर्णांक tbl[], पूर्णांक tbl_size, पूर्णांक v)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < tbl_size; i++)
		अगर (v < tbl[i])
			अवरोध;

	वापस i - 1;
पूर्ण

/* Basic driver I/O routines */

अटल पूर्णांक bq24190_पढ़ो(काष्ठा bq24190_dev_info *bdi, u8 reg, u8 *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(bdi->client, reg);
	अगर (ret < 0)
		वापस ret;

	*data = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_ग_लिखो(काष्ठा bq24190_dev_info *bdi, u8 reg, u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(bdi->client, reg, data);
पूर्ण

अटल पूर्णांक bq24190_पढ़ो_mask(काष्ठा bq24190_dev_info *bdi, u8 reg,
		u8 mask, u8 shअगरt, u8 *data)
अणु
	u8 v;
	पूर्णांक ret;

	ret = bq24190_पढ़ो(bdi, reg, &v);
	अगर (ret < 0)
		वापस ret;

	v &= mask;
	v >>= shअगरt;
	*data = v;

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_ग_लिखो_mask(काष्ठा bq24190_dev_info *bdi, u8 reg,
		u8 mask, u8 shअगरt, u8 data)
अणु
	u8 v;
	पूर्णांक ret;

	ret = bq24190_पढ़ो(bdi, reg, &v);
	अगर (ret < 0)
		वापस ret;

	v &= ~mask;
	v |= ((data << shअगरt) & mask);

	वापस bq24190_ग_लिखो(bdi, reg, v);
पूर्ण

अटल पूर्णांक bq24190_get_field_val(काष्ठा bq24190_dev_info *bdi,
		u8 reg, u8 mask, u8 shअगरt,
		स्थिर पूर्णांक tbl[], पूर्णांक tbl_size,
		पूर्णांक *val)
अणु
	u8 v;
	पूर्णांक ret;

	ret = bq24190_पढ़ो_mask(bdi, reg, mask, shअगरt, &v);
	अगर (ret < 0)
		वापस ret;

	v = (v >= tbl_size) ? (tbl_size - 1) : v;
	*val = tbl[v];

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_set_field_val(काष्ठा bq24190_dev_info *bdi,
		u8 reg, u8 mask, u8 shअगरt,
		स्थिर पूर्णांक tbl[], पूर्णांक tbl_size,
		पूर्णांक val)
अणु
	u8 idx;

	idx = bq24190_find_idx(tbl, tbl_size, val);

	वापस bq24190_ग_लिखो_mask(bdi, reg, mask, shअगरt, idx);
पूर्ण

#अगर_घोषित CONFIG_SYSFS
/*
 * There are a numerous options that are configurable on the bq24190
 * that go well beyond what the घातer_supply properties provide access to.
 * Provide sysfs access to them so they can be examined and possibly modअगरied
 * on the fly.  They will be provided क्रम the अक्षरger घातer_supply object only
 * and will be prefixed by 'f_' to make them easier to recognize.
 */

#घोषणा BQ24190_SYSFS_FIELD(_name, r, f, m, store)			\
अणु									\
	.attr	= __ATTR(f_##_name, m, bq24190_sysfs_show, store),	\
	.reg	= BQ24190_REG_##r,					\
	.mask	= BQ24190_REG_##r##_##f##_MASK,				\
	.shअगरt	= BQ24190_REG_##r##_##f##_SHIFT,			\
पूर्ण

#घोषणा BQ24190_SYSFS_FIELD_RW(_name, r, f)				\
		BQ24190_SYSFS_FIELD(_name, r, f, S_IWUSR | S_IRUGO,	\
				bq24190_sysfs_store)

#घोषणा BQ24190_SYSFS_FIELD_RO(_name, r, f)				\
		BQ24190_SYSFS_FIELD(_name, r, f, S_IRUGO, शून्य)

अटल sमाप_प्रकार bq24190_sysfs_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf);
अटल sमाप_प्रकार bq24190_sysfs_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count);

काष्ठा bq24190_sysfs_field_info अणु
	काष्ठा device_attribute	attr;
	u8	reg;
	u8	mask;
	u8	shअगरt;
पूर्ण;

/* On i386 ptrace-abi.h defines SS that अवरोधs the macro calls below. */
#अघोषित SS

अटल काष्ठा bq24190_sysfs_field_info bq24190_sysfs_field_tbl[] = अणु
			/*	sysfs name	reg	field in reg */
	BQ24190_SYSFS_FIELD_RW(en_hiz,		ISC,	EN_HIZ),
	BQ24190_SYSFS_FIELD_RW(vindpm,		ISC,	VINDPM),
	BQ24190_SYSFS_FIELD_RW(iinlim,		ISC,	IINLIM),
	BQ24190_SYSFS_FIELD_RW(chg_config,	POC,	CHG_CONFIG),
	BQ24190_SYSFS_FIELD_RW(sys_min,		POC,	SYS_MIN),
	BQ24190_SYSFS_FIELD_RW(boost_lim,	POC,	BOOST_LIM),
	BQ24190_SYSFS_FIELD_RW(ichg,		CCC,	ICHG),
	BQ24190_SYSFS_FIELD_RW(क्रमce_20_pct,	CCC,	FORCE_20PCT),
	BQ24190_SYSFS_FIELD_RW(iprechg,		PCTCC,	IPRECHG),
	BQ24190_SYSFS_FIELD_RW(iterm,		PCTCC,	ITERM),
	BQ24190_SYSFS_FIELD_RW(vreg,		CVC,	VREG),
	BQ24190_SYSFS_FIELD_RW(batlowv,		CVC,	BATLOWV),
	BQ24190_SYSFS_FIELD_RW(vrechg,		CVC,	VRECHG),
	BQ24190_SYSFS_FIELD_RW(en_term,		CTTC,	EN_TERM),
	BQ24190_SYSFS_FIELD_RW(term_stat,	CTTC,	TERM_STAT),
	BQ24190_SYSFS_FIELD_RO(watchकरोg,	CTTC,	WATCHDOG),
	BQ24190_SYSFS_FIELD_RW(en_समयr,	CTTC,	EN_TIMER),
	BQ24190_SYSFS_FIELD_RW(chg_समयr,	CTTC,	CHG_TIMER),
	BQ24190_SYSFS_FIELD_RW(jeta_iset,	CTTC,	JEITA_ISET),
	BQ24190_SYSFS_FIELD_RW(bat_comp,	ICTRC,	BAT_COMP),
	BQ24190_SYSFS_FIELD_RW(vclamp,		ICTRC,	VCLAMP),
	BQ24190_SYSFS_FIELD_RW(treg,		ICTRC,	TREG),
	BQ24190_SYSFS_FIELD_RW(dpdm_en,		MOC,	DPDM_EN),
	BQ24190_SYSFS_FIELD_RW(पंचांगr2x_en,	MOC,	TMR2X_EN),
	BQ24190_SYSFS_FIELD_RW(batfet_disable,	MOC,	BATFET_DISABLE),
	BQ24190_SYSFS_FIELD_RW(jeita_vset,	MOC,	JEITA_VSET),
	BQ24190_SYSFS_FIELD_RO(पूर्णांक_mask,	MOC,	INT_MASK),
	BQ24190_SYSFS_FIELD_RO(vbus_stat,	SS,	VBUS_STAT),
	BQ24190_SYSFS_FIELD_RO(chrg_stat,	SS,	CHRG_STAT),
	BQ24190_SYSFS_FIELD_RO(dpm_stat,	SS,	DPM_STAT),
	BQ24190_SYSFS_FIELD_RO(pg_stat,		SS,	PG_STAT),
	BQ24190_SYSFS_FIELD_RO(therm_stat,	SS,	THERM_STAT),
	BQ24190_SYSFS_FIELD_RO(vsys_stat,	SS,	VSYS_STAT),
	BQ24190_SYSFS_FIELD_RO(watchकरोg_fault,	F,	WATCHDOG_FAULT),
	BQ24190_SYSFS_FIELD_RO(boost_fault,	F,	BOOST_FAULT),
	BQ24190_SYSFS_FIELD_RO(chrg_fault,	F,	CHRG_FAULT),
	BQ24190_SYSFS_FIELD_RO(bat_fault,	F,	BAT_FAULT),
	BQ24190_SYSFS_FIELD_RO(ntc_fault,	F,	NTC_FAULT),
	BQ24190_SYSFS_FIELD_RO(pn,		VPRS,	PN),
	BQ24190_SYSFS_FIELD_RO(ts_profile,	VPRS,	TS_PROखाता),
	BQ24190_SYSFS_FIELD_RO(dev_reg,		VPRS,	DEV_REG),
पूर्ण;

अटल काष्ठा attribute *
	bq24190_sysfs_attrs[ARRAY_SIZE(bq24190_sysfs_field_tbl) + 1];

ATTRIBUTE_GROUPS(bq24190_sysfs);

अटल व्योम bq24190_sysfs_init_attrs(व्योम)
अणु
	पूर्णांक i, limit = ARRAY_SIZE(bq24190_sysfs_field_tbl);

	क्रम (i = 0; i < limit; i++)
		bq24190_sysfs_attrs[i] = &bq24190_sysfs_field_tbl[i].attr.attr;

	bq24190_sysfs_attrs[limit] = शून्य; /* Has additional entry क्रम this */
पूर्ण

अटल काष्ठा bq24190_sysfs_field_info *bq24190_sysfs_field_lookup(
		स्थिर अक्षर *name)
अणु
	पूर्णांक i, limit = ARRAY_SIZE(bq24190_sysfs_field_tbl);

	क्रम (i = 0; i < limit; i++)
		अगर (!म_भेद(name, bq24190_sysfs_field_tbl[i].attr.attr.name))
			अवरोध;

	अगर (i >= limit)
		वापस शून्य;

	वापस &bq24190_sysfs_field_tbl[i];
पूर्ण

अटल sमाप_प्रकार bq24190_sysfs_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	काष्ठा bq24190_sysfs_field_info *info;
	sमाप_प्रकार count;
	पूर्णांक ret;
	u8 v;

	info = bq24190_sysfs_field_lookup(attr->attr.name);
	अगर (!info)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	ret = bq24190_पढ़ो_mask(bdi, info->reg, info->mask, info->shअगरt, &v);
	अगर (ret)
		count = ret;
	अन्यथा
		count = scnम_लिखो(buf, PAGE_SIZE, "%hhx\n", v);

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार bq24190_sysfs_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा घातer_supply *psy = dev_get_drvdata(dev);
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	काष्ठा bq24190_sysfs_field_info *info;
	पूर्णांक ret;
	u8 v;

	info = bq24190_sysfs_field_lookup(attr->attr.name);
	अगर (!info)
		वापस -EINVAL;

	ret = kstrtou8(buf, 0, &v);
	अगर (ret < 0)
		वापस ret;

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	ret = bq24190_ग_लिखो_mask(bdi, info->reg, info->mask, info->shअगरt, v);
	अगर (ret)
		count = ret;

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस count;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_REGULATOR
अटल पूर्णांक bq24190_set_अक्षरge_mode(काष्ठा regulator_dev *dev, u8 val)
अणु
	काष्ठा bq24190_dev_info *bdi = rdev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", ret);
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_POC,
				 BQ24190_REG_POC_CHG_CONFIG_MASK,
				 BQ24190_REG_POC_CHG_CONFIG_SHIFT, val);

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_vbus_enable(काष्ठा regulator_dev *dev)
अणु
	वापस bq24190_set_अक्षरge_mode(dev, BQ24190_REG_POC_CHG_CONFIG_OTG);
पूर्ण

अटल पूर्णांक bq24190_vbus_disable(काष्ठा regulator_dev *dev)
अणु
	वापस bq24190_set_अक्षरge_mode(dev, BQ24190_REG_POC_CHG_CONFIG_CHARGE);
पूर्ण

अटल पूर्णांक bq24190_vbus_is_enabled(काष्ठा regulator_dev *dev)
अणु
	काष्ठा bq24190_dev_info *bdi = rdev_get_drvdata(dev);
	पूर्णांक ret;
	u8 val;

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", ret);
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_POC,
				BQ24190_REG_POC_CHG_CONFIG_MASK,
				BQ24190_REG_POC_CHG_CONFIG_SHIFT, &val);

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret ? ret : val == BQ24190_REG_POC_CHG_CONFIG_OTG;
पूर्ण

अटल स्थिर काष्ठा regulator_ops bq24190_vbus_ops = अणु
	.enable = bq24190_vbus_enable,
	.disable = bq24190_vbus_disable,
	.is_enabled = bq24190_vbus_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा regulator_desc bq24190_vbus_desc = अणु
	.name = "usb_otg_vbus",
	.of_match = "usb-otg-vbus",
	.type = REGULATOR_VOLTAGE,
	.owner = THIS_MODULE,
	.ops = &bq24190_vbus_ops,
	.fixed_uV = 5000000,
	.n_voltages = 1,
पूर्ण;

अटल स्थिर काष्ठा regulator_init_data bq24190_vbus_init_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.valid_ops_mask = REGULATOR_CHANGE_STATUS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bq24190_रेजिस्टर_vbus_regulator(काष्ठा bq24190_dev_info *bdi)
अणु
	काष्ठा bq24190_platक्रमm_data *pdata = bdi->dev->platक्रमm_data;
	काष्ठा regulator_config cfg = अणु पूर्ण;
	काष्ठा regulator_dev *reg;
	पूर्णांक ret = 0;

	cfg.dev = bdi->dev;
	अगर (pdata && pdata->regulator_init_data)
		cfg.init_data = pdata->regulator_init_data;
	अन्यथा
		cfg.init_data = &bq24190_vbus_init_data;
	cfg.driver_data = bdi;
	reg = devm_regulator_रेजिस्टर(bdi->dev, &bq24190_vbus_desc, &cfg);
	अगर (IS_ERR(reg)) अणु
		ret = PTR_ERR(reg);
		dev_err(bdi->dev, "Can't register regulator: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक bq24190_रेजिस्टर_vbus_regulator(काष्ठा bq24190_dev_info *bdi)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bq24190_set_config(काष्ठा bq24190_dev_info *bdi)
अणु
	पूर्णांक ret;
	u8 v;

	ret = bq24190_पढ़ो(bdi, BQ24190_REG_CTTC, &v);
	अगर (ret < 0)
		वापस ret;

	bdi->watchकरोg = ((v & BQ24190_REG_CTTC_WATCHDOG_MASK) >>
					BQ24190_REG_CTTC_WATCHDOG_SHIFT);

	/*
	 * According to the "Host Mode and default Mode" section of the
	 * manual, a ग_लिखो to any रेजिस्टर causes the bq24190 to चयन
	 * from शेष mode to host mode.  It will चयन back to शेष
	 * mode after a WDT समयout unless the WDT is turned off as well.
	 * So, by simply turning off the WDT, we accomplish both with the
	 * same ग_लिखो.
	 */
	v &= ~BQ24190_REG_CTTC_WATCHDOG_MASK;

	ret = bq24190_ग_लिखो(bdi, BQ24190_REG_CTTC, v);
	अगर (ret < 0)
		वापस ret;

	अगर (bdi->sys_min) अणु
		v = bdi->sys_min / 100 - 30; // manual section 9.5.1.2, table 9
		ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_POC,
					 BQ24190_REG_POC_SYS_MIN_MASK,
					 BQ24190_REG_POC_SYS_MIN_SHIFT,
					 v);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (bdi->iprechg) अणु
		v = bdi->iprechg / 128 - 1; // manual section 9.5.1.4, table 11
		ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_PCTCC,
					 BQ24190_REG_PCTCC_IPRECHG_MASK,
					 BQ24190_REG_PCTCC_IPRECHG_SHIFT,
					 v);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (bdi->iterm) अणु
		v = bdi->iterm / 128 - 1; // manual section 9.5.1.4, table 11
		ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_PCTCC,
					 BQ24190_REG_PCTCC_ITERM_MASK,
					 BQ24190_REG_PCTCC_ITERM_SHIFT,
					 v);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_रेजिस्टर_reset(काष्ठा bq24190_dev_info *bdi)
अणु
	पूर्णांक ret, limit = 100;
	u8 v;

	/*
	 * This prop. can be passed on device instantiation from platक्रमm code:
	 * काष्ठा property_entry pe[] =
	 *   अणु PROPERTY_ENTRY_BOOL("disable-reset"), ... पूर्ण;
	 * काष्ठा i2c_board_info bi =
	 *   अणु .type = "bq24190", .addr = 0x6b, .properties = pe, .irq = irq पूर्ण;
	 * काष्ठा i2c_adapter ad = अणु ... पूर्ण;
	 * i2c_add_adapter(&ad);
	 * i2c_new_client_device(&ad, &bi);
	 */
	अगर (device_property_पढ़ो_bool(bdi->dev, "disable-reset"))
		वापस 0;

	/* Reset the रेजिस्टरs */
	ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_RESET_MASK,
			BQ24190_REG_POC_RESET_SHIFT,
			0x1);
	अगर (ret < 0)
		वापस ret;

	/* Reset bit will be cleared by hardware so poll until it is */
	करो अणु
		ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_POC,
				BQ24190_REG_POC_RESET_MASK,
				BQ24190_REG_POC_RESET_SHIFT,
				&v);
		अगर (ret < 0)
			वापस ret;

		अगर (v == 0)
			वापस 0;

		usleep_range(100, 200);
	पूर्ण जबतक (--limit);

	वापस -EIO;
पूर्ण

/* Charger घातer supply property routines */

अटल पूर्णांक bq24190_अक्षरger_get_अक्षरge_type(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक type, ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_CHG_CONFIG_MASK,
			BQ24190_REG_POC_CHG_CONFIG_SHIFT,
			&v);
	अगर (ret < 0)
		वापस ret;

	/* If POC[CHG_CONFIG] (REG01[5:4]) == 0, अक्षरge is disabled */
	अगर (!v) अणु
		type = POWER_SUPPLY_CHARGE_TYPE_NONE;
	पूर्ण अन्यथा अणु
		ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_CCC,
				BQ24190_REG_CCC_FORCE_20PCT_MASK,
				BQ24190_REG_CCC_FORCE_20PCT_SHIFT,
				&v);
		अगर (ret < 0)
			वापस ret;

		type = (v) ? POWER_SUPPLY_CHARGE_TYPE_TRICKLE :
			     POWER_SUPPLY_CHARGE_TYPE_FAST;
	पूर्ण

	val->पूर्णांकval = type;

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_अक्षरge_type(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	u8 chg_config, क्रमce_20pct, en_term;
	पूर्णांक ret;

	/*
	 * According to the "Termination when REG02[0] = 1" section of
	 * the bq24190 manual, the trickle अक्षरge could be less than the
	 * termination current so it recommends turning off the termination
	 * function.
	 *
	 * Note: AFAICT from the datasheet, the user will have to manually
	 * turn off the अक्षरging when in 20% mode.  If its not turned off,
	 * there could be battery damage.  So, use this mode at your own risk.
	 */
	चयन (val->पूर्णांकval) अणु
	हाल POWER_SUPPLY_CHARGE_TYPE_NONE:
		chg_config = 0x0;
		अवरोध;
	हाल POWER_SUPPLY_CHARGE_TYPE_TRICKLE:
		chg_config = 0x1;
		क्रमce_20pct = 0x1;
		en_term = 0x0;
		अवरोध;
	हाल POWER_SUPPLY_CHARGE_TYPE_FAST:
		chg_config = 0x1;
		क्रमce_20pct = 0x0;
		en_term = 0x1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (chg_config) अणु /* Enabling the अक्षरger */
		ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_CCC,
				BQ24190_REG_CCC_FORCE_20PCT_MASK,
				BQ24190_REG_CCC_FORCE_20PCT_SHIFT,
				क्रमce_20pct);
		अगर (ret < 0)
			वापस ret;

		ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_CTTC,
				BQ24190_REG_CTTC_EN_TERM_MASK,
				BQ24190_REG_CTTC_EN_TERM_SHIFT,
				en_term);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस bq24190_ग_लिखो_mask(bdi, BQ24190_REG_POC,
			BQ24190_REG_POC_CHG_CONFIG_MASK,
			BQ24190_REG_POC_CHG_CONFIG_SHIFT, chg_config);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_health(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक health;

	mutex_lock(&bdi->f_reg_lock);
	v = bdi->f_reg;
	mutex_unlock(&bdi->f_reg_lock);

	अगर (v & BQ24190_REG_F_NTC_FAULT_MASK) अणु
		चयन (v >> BQ24190_REG_F_NTC_FAULT_SHIFT & 0x7) अणु
		हाल 0x1: /* TS1  Cold */
		हाल 0x3: /* TS2  Cold */
		हाल 0x5: /* Both Cold */
			health = POWER_SUPPLY_HEALTH_COLD;
			अवरोध;
		हाल 0x2: /* TS1  Hot */
		हाल 0x4: /* TS2  Hot */
		हाल 0x6: /* Both Hot */
			health = POWER_SUPPLY_HEALTH_OVERHEAT;
			अवरोध;
		शेष:
			health = POWER_SUPPLY_HEALTH_UNKNOWN;
		पूर्ण
	पूर्ण अन्यथा अगर (v & BQ24190_REG_F_BAT_FAULT_MASK) अणु
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	पूर्ण अन्यथा अगर (v & BQ24190_REG_F_CHRG_FAULT_MASK) अणु
		चयन (v >> BQ24190_REG_F_CHRG_FAULT_SHIFT & 0x3) अणु
		हाल 0x1: /* Input Fault (VBUS OVP or VBAT<VBUS<3.8V) */
			/*
			 * This could be over-voltage or under-voltage
			 * and there's no way to tell which.  Instead
			 * of looking foolish and वापसing 'OVERVOLTAGE'
			 * when its really under-voltage, just वापस
			 * 'UNSPEC_FAILURE'.
			 */
			health = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
			अवरोध;
		हाल 0x2: /* Thermal Shutकरोwn */
			health = POWER_SUPPLY_HEALTH_OVERHEAT;
			अवरोध;
		हाल 0x3: /* Charge Safety Timer Expiration */
			health = POWER_SUPPLY_HEALTH_SAFETY_TIMER_EXPIRE;
			अवरोध;
		शेष:  /* prevent compiler warning */
			health = -1;
		पूर्ण
	पूर्ण अन्यथा अगर (v & BQ24190_REG_F_BOOST_FAULT_MASK) अणु
		/*
		 * This could be over-current or over-voltage but there's
		 * no way to tell which.  Return 'OVERVOLTAGE' since there
		 * isn't an 'OVERCURRENT' value defined that we can वापस
		 * even अगर it was over-current.
		 */
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	पूर्ण अन्यथा अणु
		health = POWER_SUPPLY_HEALTH_GOOD;
	पूर्ण

	val->पूर्णांकval = health;

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_online(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 pg_stat, batfet_disable;
	पूर्णांक ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_SS,
			BQ24190_REG_SS_PG_STAT_MASK,
			BQ24190_REG_SS_PG_STAT_SHIFT, &pg_stat);
	अगर (ret < 0)
		वापस ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_MOC,
			BQ24190_REG_MOC_BATFET_DISABLE_MASK,
			BQ24190_REG_MOC_BATFET_DISABLE_SHIFT, &batfet_disable);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = pg_stat && !batfet_disable;

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_battery_set_online(काष्ठा bq24190_dev_info *bdi,
				      स्थिर जोड़ घातer_supply_propval *val);
अटल पूर्णांक bq24190_battery_get_status(काष्ठा bq24190_dev_info *bdi,
				      जोड़ घातer_supply_propval *val);
अटल पूर्णांक bq24190_battery_get_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
					      जोड़ घातer_supply_propval *val);
अटल पूर्णांक bq24190_battery_set_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
					      स्थिर जोड़ घातer_supply_propval *val);

अटल पूर्णांक bq24190_अक्षरger_set_online(काष्ठा bq24190_dev_info *bdi,
				      स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_battery_set_online(bdi, val);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_status(काष्ठा bq24190_dev_info *bdi,
				      जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_battery_get_status(bdi, val);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
					      जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_battery_get_temp_alert_max(bdi, val);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
					      स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_battery_set_temp_alert_max(bdi, val);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_preअक्षरge(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_PCTCC,
			BQ24190_REG_PCTCC_IPRECHG_MASK,
			BQ24190_REG_PCTCC_IPRECHG_SHIFT, &v);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = ++v * 128 * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_अक्षरge_term(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_PCTCC,
			BQ24190_REG_PCTCC_ITERM_MASK,
			BQ24190_REG_PCTCC_ITERM_SHIFT, &v);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = ++v * 128 * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_current(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक curr, ret;

	ret = bq24190_get_field_val(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_ICHG_MASK, BQ24190_REG_CCC_ICHG_SHIFT,
			bq24190_ccc_ichg_values,
			ARRAY_SIZE(bq24190_ccc_ichg_values), &curr);
	अगर (ret < 0)
		वापस ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_FORCE_20PCT_MASK,
			BQ24190_REG_CCC_FORCE_20PCT_SHIFT, &v);
	अगर (ret < 0)
		वापस ret;

	/* If FORCE_20PCT is enabled, then current is 20% of ICHG value */
	अगर (v)
		curr /= 5;

	val->पूर्णांकval = curr;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_current_max(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक idx = ARRAY_SIZE(bq24190_ccc_ichg_values) - 1;

	val->पूर्णांकval = bq24190_ccc_ichg_values[idx];
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_current(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक ret, curr = val->पूर्णांकval;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_FORCE_20PCT_MASK,
			BQ24190_REG_CCC_FORCE_20PCT_SHIFT, &v);
	अगर (ret < 0)
		वापस ret;

	/* If FORCE_20PCT is enabled, have to multiply value passed in by 5 */
	अगर (v)
		curr *= 5;

	वापस bq24190_set_field_val(bdi, BQ24190_REG_CCC,
			BQ24190_REG_CCC_ICHG_MASK, BQ24190_REG_CCC_ICHG_SHIFT,
			bq24190_ccc_ichg_values,
			ARRAY_SIZE(bq24190_ccc_ichg_values), curr);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_voltage(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक voltage, ret;

	ret = bq24190_get_field_val(bdi, BQ24190_REG_CVC,
			BQ24190_REG_CVC_VREG_MASK, BQ24190_REG_CVC_VREG_SHIFT,
			bq24190_cvc_vreg_values,
			ARRAY_SIZE(bq24190_cvc_vreg_values), &voltage);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = voltage;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_voltage_max(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक idx = ARRAY_SIZE(bq24190_cvc_vreg_values) - 1;

	val->पूर्णांकval = bq24190_cvc_vreg_values[idx];
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_voltage(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_set_field_val(bdi, BQ24190_REG_CVC,
			BQ24190_REG_CVC_VREG_MASK, BQ24190_REG_CVC_VREG_SHIFT,
			bq24190_cvc_vreg_values,
			ARRAY_SIZE(bq24190_cvc_vreg_values), val->पूर्णांकval);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_iinlimit(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक iinlimit, ret;

	ret = bq24190_get_field_val(bdi, BQ24190_REG_ISC,
			BQ24190_REG_ISC_IINLIM_MASK,
			BQ24190_REG_ISC_IINLIM_SHIFT,
			bq24190_isc_iinlim_values,
			ARRAY_SIZE(bq24190_isc_iinlim_values), &iinlimit);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = iinlimit;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_iinlimit(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_set_field_val(bdi, BQ24190_REG_ISC,
			BQ24190_REG_ISC_IINLIM_MASK,
			BQ24190_REG_ISC_IINLIM_SHIFT,
			bq24190_isc_iinlim_values,
			ARRAY_SIZE(bq24190_isc_iinlim_values), val->पूर्णांकval);
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = bq24190_अक्षरger_get_अक्षरge_type(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = bq24190_अक्षरger_get_health(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_अक्षरger_get_online(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq24190_अक्षरger_get_status(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret =  bq24190_अक्षरger_get_temp_alert_max(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_PRECHARGE_CURRENT:
		ret = bq24190_अक्षरger_get_preअक्षरge(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT:
		ret = bq24190_अक्षरger_get_अक्षरge_term(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq24190_अक्षरger_get_current(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
		ret = bq24190_अक्षरger_get_current_max(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq24190_अक्षरger_get_voltage(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
		ret = bq24190_अक्षरger_get_voltage_max(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq24190_अक्षरger_get_iinlimit(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		ret = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = bdi->model_name;
		ret = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ24190_MANUFACTURER;
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODATA;
	पूर्ण

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_अक्षरger_set_online(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = bq24190_अक्षरger_set_temp_alert_max(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = bq24190_अक्षरger_set_अक्षरge_type(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
		ret = bq24190_अक्षरger_set_current(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
		ret = bq24190_अक्षरger_set_voltage(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		ret = bq24190_अक्षरger_set_iinlimit(bdi, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE:
	हाल POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम bq24190_input_current_limit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bq24190_dev_info *bdi =
		container_of(work, काष्ठा bq24190_dev_info,
			     input_current_limit_work.work);

	घातer_supply_set_input_current_limit_from_supplier(bdi->अक्षरger);
पूर्ण

/* Sync the input-current-limit with our parent supply (अगर we have one) */
अटल व्योम bq24190_अक्षरger_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);

	/*
	 * The Power-Good detection may take up to 220ms, someबार
	 * the बाह्यal अक्षरger detection is quicker, and the bq24190 will
	 * reset to iinlim based on its own अक्षरger detection (which is not
	 * hooked up when using बाह्यal अक्षरger detection) resulting in a
	 * too low शेष 500mA iinlim. Delay setting the input-current-limit
	 * क्रम 300ms to aव्योम this.
	 */
	queue_delayed_work(प्रणाली_wq, &bdi->input_current_limit_work,
			   msecs_to_jअगरfies(300));
पूर्ण

अटल क्रमागत घातer_supply_property bq24190_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_CHARGE_TYPE,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
	POWER_SUPPLY_PROP_PRECHARGE_CURRENT,
	POWER_SUPPLY_PROP_CHARGE_TERM_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_INPUT_CURRENT_LIMIT,
	POWER_SUPPLY_PROP_SCOPE,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल अक्षर *bq24190_अक्षरger_supplied_to[] = अणु
	"main-battery",
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq24190_अक्षरger_desc = अणु
	.name			= "bq24190-charger",
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= bq24190_अक्षरger_properties,
	.num_properties		= ARRAY_SIZE(bq24190_अक्षरger_properties),
	.get_property		= bq24190_अक्षरger_get_property,
	.set_property		= bq24190_अक्षरger_set_property,
	.property_is_ग_लिखोable	= bq24190_अक्षरger_property_is_ग_लिखोable,
	.बाह्यal_घातer_changed	= bq24190_अक्षरger_बाह्यal_घातer_changed,
पूर्ण;

/* Battery घातer supply property routines */

अटल पूर्णांक bq24190_battery_get_status(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 ss_reg, chrg_fault;
	पूर्णांक status, ret;

	mutex_lock(&bdi->f_reg_lock);
	chrg_fault = bdi->f_reg;
	mutex_unlock(&bdi->f_reg_lock);

	chrg_fault &= BQ24190_REG_F_CHRG_FAULT_MASK;
	chrg_fault >>= BQ24190_REG_F_CHRG_FAULT_SHIFT;

	ret = bq24190_पढ़ो(bdi, BQ24190_REG_SS, &ss_reg);
	अगर (ret < 0)
		वापस ret;

	/*
	 * The battery must be disअक्षरging when any of these are true:
	 * - there is no good घातer source;
	 * - there is a अक्षरge fault.
	 * Could also be disअक्षरging when in "supplement mode" but
	 * there is no way to tell when its in that mode.
	 */
	अगर (!(ss_reg & BQ24190_REG_SS_PG_STAT_MASK) || chrg_fault) अणु
		status = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण अन्यथा अणु
		ss_reg &= BQ24190_REG_SS_CHRG_STAT_MASK;
		ss_reg >>= BQ24190_REG_SS_CHRG_STAT_SHIFT;

		चयन (ss_reg) अणु
		हाल 0x0: /* Not Charging */
			status = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		हाल 0x1: /* Pre-अक्षरge */
		हाल 0x2: /* Fast Charging */
			status = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 0x3: /* Charge Termination Done */
			status = POWER_SUPPLY_STATUS_FULL;
			अवरोध;
		शेष:
			ret = -EIO;
		पूर्ण
	पूर्ण

	अगर (!ret)
		val->पूर्णांकval = status;

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_battery_get_health(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 v;
	पूर्णांक health;

	mutex_lock(&bdi->f_reg_lock);
	v = bdi->f_reg;
	mutex_unlock(&bdi->f_reg_lock);

	अगर (v & BQ24190_REG_F_BAT_FAULT_MASK) अणु
		health = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
	पूर्ण अन्यथा अणु
		v &= BQ24190_REG_F_NTC_FAULT_MASK;
		v >>= BQ24190_REG_F_NTC_FAULT_SHIFT;

		चयन (v) अणु
		हाल 0x0: /* Normal */
			health = POWER_SUPPLY_HEALTH_GOOD;
			अवरोध;
		हाल 0x1: /* TS1 Cold */
		हाल 0x3: /* TS2 Cold */
		हाल 0x5: /* Both Cold */
			health = POWER_SUPPLY_HEALTH_COLD;
			अवरोध;
		हाल 0x2: /* TS1 Hot */
		हाल 0x4: /* TS2 Hot */
		हाल 0x6: /* Both Hot */
			health = POWER_SUPPLY_HEALTH_OVERHEAT;
			अवरोध;
		शेष:
			health = POWER_SUPPLY_HEALTH_UNKNOWN;
		पूर्ण
	पूर्ण

	val->पूर्णांकval = health;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_battery_get_online(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	u8 batfet_disable;
	पूर्णांक ret;

	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_MOC,
			BQ24190_REG_MOC_BATFET_DISABLE_MASK,
			BQ24190_REG_MOC_BATFET_DISABLE_SHIFT, &batfet_disable);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = !batfet_disable;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_battery_set_online(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_ग_लिखो_mask(bdi, BQ24190_REG_MOC,
			BQ24190_REG_MOC_BATFET_DISABLE_MASK,
			BQ24190_REG_MOC_BATFET_DISABLE_SHIFT, !val->पूर्णांकval);
पूर्ण

अटल पूर्णांक bq24190_battery_get_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
		जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक temp, ret;

	ret = bq24190_get_field_val(bdi, BQ24190_REG_ICTRC,
			BQ24190_REG_ICTRC_TREG_MASK,
			BQ24190_REG_ICTRC_TREG_SHIFT,
			bq24190_ictrc_treg_values,
			ARRAY_SIZE(bq24190_ictrc_treg_values), &temp);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_battery_set_temp_alert_max(काष्ठा bq24190_dev_info *bdi,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	वापस bq24190_set_field_val(bdi, BQ24190_REG_ICTRC,
			BQ24190_REG_ICTRC_TREG_MASK,
			BQ24190_REG_ICTRC_TREG_SHIFT,
			bq24190_ictrc_treg_values,
			ARRAY_SIZE(bq24190_ictrc_treg_values), val->पूर्णांकval);
पूर्ण

अटल पूर्णांक bq24190_battery_get_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	dev_warn(bdi->dev, "warning: /sys/class/power_supply/bq24190-battery is deprecated\n");
	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		ret = bq24190_battery_get_status(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = bq24190_battery_get_health(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_battery_get_online(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		/* Could be Li-on or Li-polymer but no way to tell which */
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		ret = 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = bq24190_battery_get_temp_alert_max(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_SCOPE:
		val->पूर्णांकval = POWER_SUPPLY_SCOPE_SYSTEM;
		ret = 0;
		अवरोध;
	शेष:
		ret = -ENODATA;
	पूर्ण

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_battery_set_property(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp,
		स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24190_dev_info *bdi = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	dev_warn(bdi->dev, "warning: /sys/class/power_supply/bq24190-battery is deprecated\n");
	dev_dbg(bdi->dev, "prop: %d\n", psp);

	ret = pm_runसमय_get_sync(bdi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(bdi->dev);
		वापस ret;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		ret = bq24190_battery_set_online(bdi, val);
		अवरोध;
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = bq24190_battery_set_temp_alert_max(bdi, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_battery_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
		क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
	हाल POWER_SUPPLY_PROP_TEMP_ALERT_MAX:
		ret = 1;
		अवरोध;
	शेष:
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल क्रमागत घातer_supply_property bq24190_battery_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_TEMP_ALERT_MAX,
	POWER_SUPPLY_PROP_SCOPE,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc bq24190_battery_desc = अणु
	.name			= "bq24190-battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= bq24190_battery_properties,
	.num_properties		= ARRAY_SIZE(bq24190_battery_properties),
	.get_property		= bq24190_battery_get_property,
	.set_property		= bq24190_battery_set_property,
	.property_is_ग_लिखोable	= bq24190_battery_property_is_ग_लिखोable,
पूर्ण;

अटल पूर्णांक bq24190_configure_usb_otg(काष्ठा bq24190_dev_info *bdi, u8 ss_reg)
अणु
	bool otg_enabled;
	पूर्णांक ret;

	otg_enabled = !!(ss_reg & BQ24190_REG_SS_VBUS_STAT_MASK);
	ret = extcon_set_state_sync(bdi->edev, EXTCON_USB, otg_enabled);
	अगर (ret < 0)
		dev_err(bdi->dev, "Can't set extcon state to %d: %d\n",
			otg_enabled, ret);

	वापस ret;
पूर्ण

अटल व्योम bq24190_check_status(काष्ठा bq24190_dev_info *bdi)
अणु
	स्थिर u8 battery_mask_ss = BQ24190_REG_SS_CHRG_STAT_MASK;
	स्थिर u8 battery_mask_f = BQ24190_REG_F_BAT_FAULT_MASK
				| BQ24190_REG_F_NTC_FAULT_MASK;
	bool alert_अक्षरger = false, alert_battery = false;
	u8 ss_reg = 0, f_reg = 0;
	पूर्णांक i, ret;

	ret = bq24190_पढ़ो(bdi, BQ24190_REG_SS, &ss_reg);
	अगर (ret < 0) अणु
		dev_err(bdi->dev, "Can't read SS reg: %d\n", ret);
		वापस;
	पूर्ण

	i = 0;
	करो अणु
		ret = bq24190_पढ़ो(bdi, BQ24190_REG_F, &f_reg);
		अगर (ret < 0) अणु
			dev_err(bdi->dev, "Can't read F reg: %d\n", ret);
			वापस;
		पूर्ण
	पूर्ण जबतक (f_reg && ++i < 2);

	/* ignore over/under voltage fault after disconnect */
	अगर (f_reg == (1 << BQ24190_REG_F_CHRG_FAULT_SHIFT) &&
	    !(ss_reg & BQ24190_REG_SS_PG_STAT_MASK))
		f_reg = 0;

	अगर (f_reg != bdi->f_reg) अणु
		dev_warn(bdi->dev,
			"Fault: boost %d, charge %d, battery %d, ntc %d\n",
			!!(f_reg & BQ24190_REG_F_BOOST_FAULT_MASK),
			!!(f_reg & BQ24190_REG_F_CHRG_FAULT_MASK),
			!!(f_reg & BQ24190_REG_F_BAT_FAULT_MASK),
			!!(f_reg & BQ24190_REG_F_NTC_FAULT_MASK));

		mutex_lock(&bdi->f_reg_lock);
		अगर ((bdi->f_reg & battery_mask_f) != (f_reg & battery_mask_f))
			alert_battery = true;
		अगर ((bdi->f_reg & ~battery_mask_f) != (f_reg & ~battery_mask_f))
			alert_अक्षरger = true;
		bdi->f_reg = f_reg;
		mutex_unlock(&bdi->f_reg_lock);
	पूर्ण

	अगर (ss_reg != bdi->ss_reg) अणु
		/*
		 * The device is in host mode so when PG_STAT goes from 1->0
		 * (i.e., घातer हटाओd) HIZ needs to be disabled.
		 */
		अगर ((bdi->ss_reg & BQ24190_REG_SS_PG_STAT_MASK) &&
				!(ss_reg & BQ24190_REG_SS_PG_STAT_MASK)) अणु
			ret = bq24190_ग_लिखो_mask(bdi, BQ24190_REG_ISC,
					BQ24190_REG_ISC_EN_HIZ_MASK,
					BQ24190_REG_ISC_EN_HIZ_SHIFT,
					0);
			अगर (ret < 0)
				dev_err(bdi->dev, "Can't access ISC reg: %d\n",
					ret);
		पूर्ण

		अगर ((bdi->ss_reg & battery_mask_ss) != (ss_reg & battery_mask_ss))
			alert_battery = true;
		अगर ((bdi->ss_reg & ~battery_mask_ss) != (ss_reg & ~battery_mask_ss))
			alert_अक्षरger = true;
		bdi->ss_reg = ss_reg;
	पूर्ण

	अगर (alert_अक्षरger || alert_battery) अणु
		घातer_supply_changed(bdi->अक्षरger);
		bq24190_configure_usb_otg(bdi, ss_reg);
	पूर्ण
	अगर (alert_battery && bdi->battery)
		घातer_supply_changed(bdi->battery);

	dev_dbg(bdi->dev, "ss_reg: 0x%02x, f_reg: 0x%02x\n", ss_reg, f_reg);
पूर्ण

अटल irqवापस_t bq24190_irq_handler_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bq24190_dev_info *bdi = data;
	पूर्णांक error;

	bdi->irq_event = true;
	error = pm_runसमय_get_sync(bdi->dev);
	अगर (error < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runसमय_put_noidle(bdi->dev);
		वापस IRQ_NONE;
	पूर्ण
	bq24190_check_status(bdi);
	pm_runसमय_mark_last_busy(bdi->dev);
	pm_runसमय_put_स्वतःsuspend(bdi->dev);
	bdi->irq_event = false;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bq24190_hw_init(काष्ठा bq24190_dev_info *bdi)
अणु
	u8 v;
	पूर्णांक ret;

	/* First check that the device really is what its supposed to be */
	ret = bq24190_पढ़ो_mask(bdi, BQ24190_REG_VPRS,
			BQ24190_REG_VPRS_PN_MASK,
			BQ24190_REG_VPRS_PN_SHIFT,
			&v);
	अगर (ret < 0)
		वापस ret;

	चयन (v) अणु
	हाल BQ24190_REG_VPRS_PN_24190:
	हाल BQ24190_REG_VPRS_PN_24192:
	हाल BQ24190_REG_VPRS_PN_24192I:
		अवरोध;
	शेष:
		dev_err(bdi->dev, "Error unknown model: 0x%02x\n", v);
		वापस -ENODEV;
	पूर्ण

	ret = bq24190_रेजिस्टर_reset(bdi);
	अगर (ret < 0)
		वापस ret;

	ret = bq24190_set_config(bdi);
	अगर (ret < 0)
		वापस ret;

	वापस bq24190_पढ़ो(bdi, BQ24190_REG_SS, &bdi->ss_reg);
पूर्ण

अटल पूर्णांक bq24190_get_config(काष्ठा bq24190_dev_info *bdi)
अणु
	स्थिर अक्षर * स्थिर s = "ti,system-minimum-microvolt";
	काष्ठा घातer_supply_battery_info info = अणुपूर्ण;
	पूर्णांक v;

	अगर (device_property_पढ़ो_u32(bdi->dev, s, &v) == 0) अणु
		v /= 1000;
		अगर (v >= BQ24190_REG_POC_SYS_MIN_MIN
		 && v <= BQ24190_REG_POC_SYS_MIN_MAX)
			bdi->sys_min = v;
		अन्यथा
			dev_warn(bdi->dev, "invalid value for %s: %u\n", s, v);
	पूर्ण

	अगर (bdi->dev->of_node &&
	    !घातer_supply_get_battery_info(bdi->अक्षरger, &info)) अणु
		v = info.preअक्षरge_current_ua / 1000;
		अगर (v >= BQ24190_REG_PCTCC_IPRECHG_MIN
		 && v <= BQ24190_REG_PCTCC_IPRECHG_MAX)
			bdi->iprechg = v;
		अन्यथा
			dev_warn(bdi->dev, "invalid value for battery:precharge-current-microamp: %d\n",
				 v);

		v = info.अक्षरge_term_current_ua / 1000;
		अगर (v >= BQ24190_REG_PCTCC_ITERM_MIN
		 && v <= BQ24190_REG_PCTCC_ITERM_MAX)
			bdi->iterm = v;
		अन्यथा
			dev_warn(bdi->dev, "invalid value for battery:charge-term-current-microamp: %d\n",
				 v);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq24190_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा घातer_supply_config अक्षरger_cfg = अणुपूर्ण, battery_cfg = अणुपूर्ण;
	काष्ठा bq24190_dev_info *bdi;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		वापस -ENODEV;
	पूर्ण

	bdi = devm_kzalloc(dev, माप(*bdi), GFP_KERNEL);
	अगर (!bdi) अणु
		dev_err(dev, "Can't alloc bdi struct\n");
		वापस -ENOMEM;
	पूर्ण

	bdi->client = client;
	bdi->dev = dev;
	म_नकलन(bdi->model_name, id->name, I2C_NAME_SIZE);
	mutex_init(&bdi->f_reg_lock);
	bdi->f_reg = 0;
	bdi->ss_reg = BQ24190_REG_SS_VBUS_STAT_MASK; /* impossible state */
	INIT_DELAYED_WORK(&bdi->input_current_limit_work,
			  bq24190_input_current_limit_work);

	i2c_set_clientdata(client, bdi);

	अगर (client->irq <= 0) अणु
		dev_err(dev, "Can't get irq info\n");
		वापस -EINVAL;
	पूर्ण

	bdi->edev = devm_extcon_dev_allocate(dev, bq24190_usb_extcon_cable);
	अगर (IS_ERR(bdi->edev))
		वापस PTR_ERR(bdi->edev);

	ret = devm_extcon_dev_रेजिस्टर(dev, bdi->edev);
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_enable(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 600);
	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "pm_runtime_get failed: %i\n", ret);
		जाओ out_pmrt;
	पूर्ण

#अगर_घोषित CONFIG_SYSFS
	bq24190_sysfs_init_attrs();
	अक्षरger_cfg.attr_grp = bq24190_sysfs_groups;
#पूर्ण_अगर

	अक्षरger_cfg.drv_data = bdi;
	अक्षरger_cfg.of_node = dev->of_node;
	अक्षरger_cfg.supplied_to = bq24190_अक्षरger_supplied_to;
	अक्षरger_cfg.num_supplicants = ARRAY_SIZE(bq24190_अक्षरger_supplied_to);
	bdi->अक्षरger = घातer_supply_रेजिस्टर(dev, &bq24190_अक्षरger_desc,
						&अक्षरger_cfg);
	अगर (IS_ERR(bdi->अक्षरger)) अणु
		dev_err(dev, "Can't register charger\n");
		ret = PTR_ERR(bdi->अक्षरger);
		जाओ out_pmrt;
	पूर्ण

	/* the battery class is deprecated and will be हटाओd. */
	/* in the पूर्णांकerim, this property hides it.              */
	अगर (!device_property_पढ़ो_bool(dev, "omit-battery-class")) अणु
		battery_cfg.drv_data = bdi;
		bdi->battery = घातer_supply_रेजिस्टर(dev, &bq24190_battery_desc,
						     &battery_cfg);
		अगर (IS_ERR(bdi->battery)) अणु
			dev_err(dev, "Can't register battery\n");
			ret = PTR_ERR(bdi->battery);
			जाओ out_अक्षरger;
		पूर्ण
	पूर्ण

	ret = bq24190_get_config(bdi);
	अगर (ret < 0) अणु
		dev_err(dev, "Can't get devicetree config\n");
		जाओ out_अक्षरger;
	पूर्ण

	ret = bq24190_hw_init(bdi);
	अगर (ret < 0) अणु
		dev_err(dev, "Hardware init failed\n");
		जाओ out_अक्षरger;
	पूर्ण

	ret = bq24190_configure_usb_otg(bdi, bdi->ss_reg);
	अगर (ret < 0)
		जाओ out_अक्षरger;

	bdi->initialized = true;

	ret = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
			bq24190_irq_handler_thपढ़ो,
			IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			"bq24190-charger", bdi);
	अगर (ret < 0) अणु
		dev_err(dev, "Can't set up irq handler\n");
		जाओ out_अक्षरger;
	पूर्ण

	ret = bq24190_रेजिस्टर_vbus_regulator(bdi);
	अगर (ret < 0)
		जाओ out_अक्षरger;

	enable_irq_wake(client->irq);

	pm_runसमय_mark_last_busy(dev);
	pm_runसमय_put_स्वतःsuspend(dev);

	वापस 0;

out_अक्षरger:
	अगर (!IS_ERR_OR_शून्य(bdi->battery))
		घातer_supply_unरेजिस्टर(bdi->battery);
	घातer_supply_unरेजिस्टर(bdi->अक्षरger);

out_pmrt:
	pm_runसमय_put_sync(dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(dev);
	pm_runसमय_disable(dev);
	वापस ret;
पूर्ण

अटल पूर्णांक bq24190_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा bq24190_dev_info *bdi = i2c_get_clientdata(client);
	पूर्णांक error;

	error = pm_runसमय_get_sync(bdi->dev);
	अगर (error < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runसमय_put_noidle(bdi->dev);
	पूर्ण

	bq24190_रेजिस्टर_reset(bdi);
	अगर (bdi->battery)
		घातer_supply_unरेजिस्टर(bdi->battery);
	घातer_supply_unरेजिस्टर(bdi->अक्षरger);
	अगर (error >= 0)
		pm_runसमय_put_sync(bdi->dev);
	pm_runसमय_करोnt_use_स्वतःsuspend(bdi->dev);
	pm_runसमय_disable(bdi->dev);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक bq24190_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bq24190_dev_info *bdi = i2c_get_clientdata(client);

	अगर (!bdi->initialized)
		वापस 0;

	dev_dbg(bdi->dev, "%s\n", __func__);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक bq24190_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bq24190_dev_info *bdi = i2c_get_clientdata(client);

	अगर (!bdi->initialized)
		वापस 0;

	अगर (!bdi->irq_event) अणु
		dev_dbg(bdi->dev, "checking events on possible wakeirq\n");
		bq24190_check_status(bdi);
	पूर्ण

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक bq24190_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bq24190_dev_info *bdi = i2c_get_clientdata(client);
	पूर्णांक error;

	error = pm_runसमय_get_sync(bdi->dev);
	अगर (error < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runसमय_put_noidle(bdi->dev);
	पूर्ण

	bq24190_रेजिस्टर_reset(bdi);

	अगर (error >= 0) अणु
		pm_runसमय_mark_last_busy(bdi->dev);
		pm_runसमय_put_स्वतःsuspend(bdi->dev);
	पूर्ण

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक bq24190_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा bq24190_dev_info *bdi = i2c_get_clientdata(client);
	पूर्णांक error;

	bdi->f_reg = 0;
	bdi->ss_reg = BQ24190_REG_SS_VBUS_STAT_MASK; /* impossible state */

	error = pm_runसमय_get_sync(bdi->dev);
	अगर (error < 0) अणु
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runसमय_put_noidle(bdi->dev);
	पूर्ण

	bq24190_रेजिस्टर_reset(bdi);
	bq24190_set_config(bdi);
	bq24190_पढ़ो(bdi, BQ24190_REG_SS, &bdi->ss_reg);

	अगर (error >= 0) अणु
		pm_runसमय_mark_last_busy(bdi->dev);
		pm_runसमय_put_स्वतःsuspend(bdi->dev);
	पूर्ण

	/* Things may have changed जबतक suspended so alert upper layer */
	घातer_supply_changed(bdi->अक्षरger);
	अगर (bdi->battery)
		घातer_supply_changed(bdi->battery);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops bq24190_pm_ops = अणु
	SET_RUNTIME_PM_OPS(bq24190_runसमय_suspend, bq24190_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(bq24190_pm_suspend, bq24190_pm_resume)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id bq24190_i2c_ids[] = अणु
	अणु "bq24190" पूर्ण,
	अणु "bq24192" पूर्ण,
	अणु "bq24192i" पूर्ण,
	अणु "bq24196" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq24190_i2c_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id bq24190_of_match[] = अणु
	अणु .compatible = "ti,bq24190", पूर्ण,
	अणु .compatible = "ti,bq24192", पूर्ण,
	अणु .compatible = "ti,bq24192i", पूर्ण,
	अणु .compatible = "ti,bq24196", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bq24190_of_match);
#अन्यथा
अटल स्थिर काष्ठा of_device_id bq24190_of_match[] = अणु
	अणु पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा i2c_driver bq24190_driver = अणु
	.probe		= bq24190_probe,
	.हटाओ		= bq24190_हटाओ,
	.id_table	= bq24190_i2c_ids,
	.driver = अणु
		.name		= "bq24190-charger",
		.pm		= &bq24190_pm_ops,
		.of_match_table	= of_match_ptr(bq24190_of_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(bq24190_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark A. Greer <mgreer@animalcreek.com>");
MODULE_DESCRIPTION("TI BQ24190 Charger Driver");
