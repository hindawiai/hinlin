<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015, Sony Mobile Communications, AB.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/kernel.h>
#समावेश <linux/backlight.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/regmap.h>

/* From DT binding */
#घोषणा WLED_MAX_STRINGS				4
#घोषणा MOD_A						0
#घोषणा MOD_B						1

#घोषणा WLED_DEFAULT_BRIGHTNESS				2048
#घोषणा WLED_SOFT_START_DLY_US				10000
#घोषणा WLED3_SINK_REG_BRIGHT_MAX			0xFFF
#घोषणा WLED5_SINK_REG_BRIGHT_MAX_12B			0xFFF
#घोषणा WLED5_SINK_REG_BRIGHT_MAX_15B			0x7FFF

/* WLED3/WLED4 control रेजिस्टरs */
#घोषणा WLED3_CTRL_REG_FAULT_STATUS			0x08
#घोषणा  WLED3_CTRL_REG_ILIM_FAULT_BIT			BIT(0)
#घोषणा  WLED3_CTRL_REG_OVP_FAULT_BIT			BIT(1)
#घोषणा  WLED4_CTRL_REG_SC_FAULT_BIT			BIT(2)
#घोषणा  WLED5_CTRL_REG_OVP_PRE_ALARM_BIT		BIT(4)

#घोषणा WLED3_CTRL_REG_INT_RT_STS			0x10
#घोषणा  WLED3_CTRL_REG_OVP_FAULT_STATUS		BIT(1)

#घोषणा WLED3_CTRL_REG_MOD_EN				0x46
#घोषणा  WLED3_CTRL_REG_MOD_EN_MASK			BIT(7)
#घोषणा  WLED3_CTRL_REG_MOD_EN_SHIFT			7

#घोषणा WLED3_CTRL_REG_FEEDBACK_CONTROL			0x48

#घोषणा WLED3_CTRL_REG_FREQ				0x4c
#घोषणा  WLED3_CTRL_REG_FREQ_MASK			GENMASK(3, 0)

#घोषणा WLED3_CTRL_REG_OVP				0x4d
#घोषणा  WLED3_CTRL_REG_OVP_MASK			GENMASK(1, 0)
#घोषणा  WLED5_CTRL_REG_OVP_MASK			GENMASK(3, 0)

#घोषणा WLED3_CTRL_REG_ILIMIT				0x4e
#घोषणा  WLED3_CTRL_REG_ILIMIT_MASK			GENMASK(2, 0)

/* WLED3/WLED4 sink रेजिस्टरs */
#घोषणा WLED3_SINK_REG_SYNC				0x47
#घोषणा  WLED3_SINK_REG_SYNC_CLEAR			0x00

#घोषणा WLED3_SINK_REG_CURR_SINK			0x4f
#घोषणा  WLED3_SINK_REG_CURR_SINK_MASK			GENMASK(7, 5)
#घोषणा  WLED3_SINK_REG_CURR_SINK_SHFT			5

/* WLED3 specअगरic per-'string' रेजिस्टरs below */
#घोषणा WLED3_SINK_REG_BRIGHT(n)			(0x40 + n)

#घोषणा WLED3_SINK_REG_STR_MOD_EN(n)			(0x60 + (n * 0x10))
#घोषणा  WLED3_SINK_REG_STR_MOD_MASK			BIT(7)

#घोषणा WLED3_SINK_REG_STR_FULL_SCALE_CURR(n)		(0x62 + (n * 0x10))
#घोषणा  WLED3_SINK_REG_STR_FULL_SCALE_CURR_MASK	GENMASK(4, 0)

#घोषणा WLED3_SINK_REG_STR_MOD_SRC(n)			(0x63 + (n * 0x10))
#घोषणा  WLED3_SINK_REG_STR_MOD_SRC_MASK		BIT(0)
#घोषणा  WLED3_SINK_REG_STR_MOD_SRC_INT			0x00
#घोषणा  WLED3_SINK_REG_STR_MOD_SRC_EXT			0x01

#घोषणा WLED3_SINK_REG_STR_CABC(n)			(0x66 + (n * 0x10))
#घोषणा  WLED3_SINK_REG_STR_CABC_MASK			BIT(7)

/* WLED4 specअगरic control रेजिस्टरs */
#घोषणा WLED4_CTRL_REG_SHORT_PROTECT			0x5e
#घोषणा  WLED4_CTRL_REG_SHORT_EN_MASK			BIT(7)

#घोषणा WLED4_CTRL_REG_SEC_ACCESS			0xd0
#घोषणा  WLED4_CTRL_REG_SEC_UNLOCK			0xa5

#घोषणा WLED4_CTRL_REG_TEST1				0xe2
#घोषणा  WLED4_CTRL_REG_TEST1_EXT_FET_DTEST2		0x09

/* WLED4 specअगरic sink रेजिस्टरs */
#घोषणा WLED4_SINK_REG_CURR_SINK			0x46
#घोषणा  WLED4_SINK_REG_CURR_SINK_MASK			GENMASK(7, 4)
#घोषणा  WLED4_SINK_REG_CURR_SINK_SHFT			4

/* WLED4 specअगरic per-'string' रेजिस्टरs below */
#घोषणा WLED4_SINK_REG_STR_MOD_EN(n)			(0x50 + (n * 0x10))
#घोषणा  WLED4_SINK_REG_STR_MOD_MASK			BIT(7)

#घोषणा WLED4_SINK_REG_STR_FULL_SCALE_CURR(n)		(0x52 + (n * 0x10))
#घोषणा  WLED4_SINK_REG_STR_FULL_SCALE_CURR_MASK	GENMASK(3, 0)

#घोषणा WLED4_SINK_REG_STR_MOD_SRC(n)			(0x53 + (n * 0x10))
#घोषणा  WLED4_SINK_REG_STR_MOD_SRC_MASK		BIT(0)
#घोषणा  WLED4_SINK_REG_STR_MOD_SRC_INT			0x00
#घोषणा  WLED4_SINK_REG_STR_MOD_SRC_EXT			0x01

#घोषणा WLED4_SINK_REG_STR_CABC(n)			(0x56 + (n * 0x10))
#घोषणा  WLED4_SINK_REG_STR_CABC_MASK			BIT(7)

#घोषणा WLED4_SINK_REG_BRIGHT(n)			(0x57 + (n * 0x10))

/* WLED5 specअगरic control रेजिस्टरs */
#घोषणा WLED5_CTRL_REG_OVP_INT_CTL			0x5f
#घोषणा  WLED5_CTRL_REG_OVP_INT_TIMER_MASK		GENMASK(2, 0)

/* WLED5 specअगरic sink रेजिस्टरs */
#घोषणा WLED5_SINK_REG_MOD_A_EN				0x50
#घोषणा WLED5_SINK_REG_MOD_B_EN				0x60
#घोषणा  WLED5_SINK_REG_MOD_EN_MASK			BIT(7)

#घोषणा WLED5_SINK_REG_MOD_A_SRC_SEL			0x51
#घोषणा WLED5_SINK_REG_MOD_B_SRC_SEL			0x61
#घोषणा  WLED5_SINK_REG_MOD_SRC_SEL_HIGH		0
#घोषणा  WLED5_SINK_REG_MOD_SRC_SEL_EXT			0x03
#घोषणा  WLED5_SINK_REG_MOD_SRC_SEL_MASK		GENMASK(1, 0)

#घोषणा WLED5_SINK_REG_MOD_A_BRIGHTNESS_WIDTH_SEL	0x52
#घोषणा WLED5_SINK_REG_MOD_B_BRIGHTNESS_WIDTH_SEL	0x62
#घोषणा  WLED5_SINK_REG_BRIGHTNESS_WIDTH_12B		0
#घोषणा  WLED5_SINK_REG_BRIGHTNESS_WIDTH_15B		1

#घोषणा WLED5_SINK_REG_MOD_A_BRIGHTNESS_LSB		0x53
#घोषणा WLED5_SINK_REG_MOD_A_BRIGHTNESS_MSB		0x54
#घोषणा WLED5_SINK_REG_MOD_B_BRIGHTNESS_LSB		0x63
#घोषणा WLED5_SINK_REG_MOD_B_BRIGHTNESS_MSB		0x64

#घोषणा WLED5_SINK_REG_MOD_SYNC_BIT			0x65
#घोषणा  WLED5_SINK_REG_SYNC_MOD_A_BIT			BIT(0)
#घोषणा  WLED5_SINK_REG_SYNC_MOD_B_BIT			BIT(1)
#घोषणा  WLED5_SINK_REG_SYNC_MASK			GENMASK(1, 0)

/* WLED5 specअगरic per-'string' रेजिस्टरs below */
#घोषणा WLED5_SINK_REG_STR_FULL_SCALE_CURR(n)		(0x72 + (n * 0x10))

#घोषणा WLED5_SINK_REG_STR_SRC_SEL(n)			(0x73 + (n * 0x10))
#घोषणा  WLED5_SINK_REG_SRC_SEL_MOD_A			0
#घोषणा  WLED5_SINK_REG_SRC_SEL_MOD_B			1
#घोषणा  WLED5_SINK_REG_SRC_SEL_MASK			GENMASK(1, 0)

काष्ठा wled_var_cfg अणु
	स्थिर u32 *values;
	u32 (*fn)(u32);
	पूर्णांक size;
पूर्ण;

काष्ठा wled_u32_opts अणु
	स्थिर अक्षर *name;
	u32 *val_ptr;
	स्थिर काष्ठा wled_var_cfg *cfg;
पूर्ण;

काष्ठा wled_bool_opts अणु
	स्थिर अक्षर *name;
	bool *val_ptr;
पूर्ण;

काष्ठा wled_config अणु
	u32 boost_i_limit;
	u32 ovp;
	u32 चयन_freq;
	u32 num_strings;
	u32 string_i_limit;
	u32 enabled_strings[WLED_MAX_STRINGS];
	u32 mod_sel;
	u32 cabc_sel;
	bool cs_out_en;
	bool ext_gen;
	bool cabc;
	bool बाह्यal_pfet;
	bool स्वतः_detection_enabled;
पूर्ण;

काष्ठा wled अणु
	स्थिर अक्षर *name;
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;	/* Lock to aव्योम race from thपढ़ो irq handler */
	kसमय_प्रकार last_लघु_event;
	kसमय_प्रकार start_ovp_fault_समय;
	u16 ctrl_addr;
	u16 sink_addr;
	u16 max_string_count;
	u16 स्वतः_detection_ovp_count;
	u32 brightness;
	u32 max_brightness;
	u32 लघु_count;
	u32 स्वतः_detect_count;
	u32 version;
	bool disabled_by_लघु;
	bool has_लघु_detect;
	bool cabc_disabled;
	पूर्णांक लघु_irq;
	पूर्णांक ovp_irq;

	काष्ठा wled_config cfg;
	काष्ठा delayed_work ovp_work;

	/* Configures the brightness. Applicable क्रम wled3, wled4 and wled5 */
	पूर्णांक (*wled_set_brightness)(काष्ठा wled *wled, u16 brightness);

	/* Configures the cabc रेजिस्टर. Applicable क्रम wled4 and wled5 */
	पूर्णांक (*wled_cabc_config)(काष्ठा wled *wled, bool enable);

	/*
	 * Toggles the sync bit क्रम the brightness update to take place.
	 * Applicable क्रम WLED3, WLED4 and WLED5.
	 */
	पूर्णांक (*wled_sync_toggle)(काष्ठा wled *wled);

	/*
	 * Time to रुको beक्रमe checking the OVP status after wled module enable.
	 * Applicable क्रम WLED4 and WLED5.
	 */
	पूर्णांक (*wled_ovp_delay)(काष्ठा wled *wled);

	/*
	 * Determines अगर the स्वतः string detection is required.
	 * Applicable क्रम WLED4 and WLED5
	 */
	bool (*wled_स्वतः_detection_required)(काष्ठा wled *wled);
पूर्ण;

अटल पूर्णांक wled3_set_brightness(काष्ठा wled *wled, u16 brightness)
अणु
	पूर्णांक rc, i;
	u8 v[2];

	v[0] = brightness & 0xff;
	v[1] = (brightness >> 8) & 0xf;

	क्रम (i = 0;  i < wled->cfg.num_strings; ++i) अणु
		rc = regmap_bulk_ग_लिखो(wled->regmap, wled->ctrl_addr +
				       WLED3_SINK_REG_BRIGHT(i), v, 2);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wled4_set_brightness(काष्ठा wled *wled, u16 brightness)
अणु
	पूर्णांक rc, i;
	u16 low_limit = wled->max_brightness * 4 / 1000;
	u8 v[2];

	/* WLED4's lower limit of operation is 0.4% */
	अगर (brightness > 0 && brightness < low_limit)
		brightness = low_limit;

	v[0] = brightness & 0xff;
	v[1] = (brightness >> 8) & 0xf;

	क्रम (i = 0;  i < wled->cfg.num_strings; ++i) अणु
		rc = regmap_bulk_ग_लिखो(wled->regmap, wled->sink_addr +
				       WLED4_SINK_REG_BRIGHT(i), v, 2);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wled5_set_brightness(काष्ठा wled *wled, u16 brightness)
अणु
	पूर्णांक rc, offset;
	u16 low_limit = wled->max_brightness * 1 / 1000;
	u8 v[2];

	/* WLED5's lower limit is 0.1% */
	अगर (brightness < low_limit)
		brightness = low_limit;

	v[0] = brightness & 0xff;
	v[1] = (brightness >> 8) & 0x7f;

	offset = (wled->cfg.mod_sel == MOD_A) ?
		  WLED5_SINK_REG_MOD_A_BRIGHTNESS_LSB :
		  WLED5_SINK_REG_MOD_B_BRIGHTNESS_LSB;

	rc = regmap_bulk_ग_लिखो(wled->regmap, wled->sink_addr + offset,
			       v, 2);
	वापस rc;
पूर्ण

अटल व्योम wled_ovp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wled *wled = container_of(work,
					 काष्ठा wled, ovp_work.work);
	enable_irq(wled->ovp_irq);
पूर्ण

अटल पूर्णांक wled_module_enable(काष्ठा wled *wled, पूर्णांक val)
अणु
	पूर्णांक rc;

	अगर (wled->disabled_by_लघु)
		वापस -ENXIO;

	rc = regmap_update_bits(wled->regmap, wled->ctrl_addr +
				WLED3_CTRL_REG_MOD_EN,
				WLED3_CTRL_REG_MOD_EN_MASK,
				val << WLED3_CTRL_REG_MOD_EN_SHIFT);
	अगर (rc < 0)
		वापस rc;

	अगर (wled->ovp_irq > 0) अणु
		अगर (val) अणु
			/*
			 * The hardware generates a storm of spurious OVP
			 * पूर्णांकerrupts during soft start operations. So defer
			 * enabling the IRQ क्रम 10ms to ensure that the
			 * soft start is complete.
			 */
			schedule_delayed_work(&wled->ovp_work, HZ / 100);
		पूर्ण अन्यथा अणु
			अगर (!cancel_delayed_work_sync(&wled->ovp_work))
				disable_irq(wled->ovp_irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wled3_sync_toggle(काष्ठा wled *wled)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक mask = GENMASK(wled->max_string_count - 1, 0);

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED3_SINK_REG_SYNC,
				mask, WLED3_SINK_REG_SYNC_CLEAR);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED3_SINK_REG_SYNC,
				mask, mask);

	वापस rc;
पूर्ण

अटल पूर्णांक wled5_mod_sync_toggle(काष्ठा wled *wled)
अणु
	पूर्णांक rc;
	u8 val;

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED5_SINK_REG_MOD_SYNC_BIT,
				WLED5_SINK_REG_SYNC_MASK, 0);
	अगर (rc < 0)
		वापस rc;

	val = (wled->cfg.mod_sel == MOD_A) ? WLED5_SINK_REG_SYNC_MOD_A_BIT :
					     WLED5_SINK_REG_SYNC_MOD_B_BIT;
	वापस regmap_update_bits(wled->regmap,
				  wled->sink_addr + WLED5_SINK_REG_MOD_SYNC_BIT,
				  WLED5_SINK_REG_SYNC_MASK, val);
पूर्ण

अटल पूर्णांक wled_ovp_fault_status(काष्ठा wled *wled, bool *fault_set)
अणु
	पूर्णांक rc;
	u32 पूर्णांक_rt_sts, fault_sts;

	*fault_set = false;
	rc = regmap_पढ़ो(wled->regmap,
			wled->ctrl_addr + WLED3_CTRL_REG_INT_RT_STS,
			&पूर्णांक_rt_sts);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to read INT_RT_STS rc=%d\n", rc);
		वापस rc;
	पूर्ण

	rc = regmap_पढ़ो(wled->regmap,
			wled->ctrl_addr + WLED3_CTRL_REG_FAULT_STATUS,
			&fault_sts);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to read FAULT_STATUS rc=%d\n", rc);
		वापस rc;
	पूर्ण

	अगर (पूर्णांक_rt_sts & WLED3_CTRL_REG_OVP_FAULT_STATUS)
		*fault_set = true;

	अगर (wled->version == 4 && (fault_sts & WLED3_CTRL_REG_OVP_FAULT_BIT))
		*fault_set = true;

	अगर (wled->version == 5 && (fault_sts & (WLED3_CTRL_REG_OVP_FAULT_BIT |
				   WLED5_CTRL_REG_OVP_PRE_ALARM_BIT)))
		*fault_set = true;

	अगर (*fault_set)
		dev_dbg(wled->dev, "WLED OVP fault detected, int_rt_sts=0x%x fault_sts=0x%x\n",
			पूर्णांक_rt_sts, fault_sts);

	वापस rc;
पूर्ण

अटल पूर्णांक wled4_ovp_delay(काष्ठा wled *wled)
अणु
	वापस WLED_SOFT_START_DLY_US;
पूर्ण

अटल पूर्णांक wled5_ovp_delay(काष्ठा wled *wled)
अणु
	पूर्णांक rc, delay_us;
	u32 val;
	u8 ovp_समयr_ms[8] = अणु1, 2, 4, 8, 12, 16, 20, 24पूर्ण;

	/* For WLED5, get the delay based on OVP समयr */
	rc = regmap_पढ़ो(wled->regmap, wled->ctrl_addr +
			 WLED5_CTRL_REG_OVP_INT_CTL, &val);
	अगर (rc < 0)
		delay_us =
		ovp_समयr_ms[val & WLED5_CTRL_REG_OVP_INT_TIMER_MASK] * 1000;
	अन्यथा
		delay_us = 2 * WLED_SOFT_START_DLY_US;

	dev_dbg(wled->dev, "delay_time_us: %d\n", delay_us);

	वापस delay_us;
पूर्ण

अटल पूर्णांक wled_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा wled *wled = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	पूर्णांक rc = 0;

	mutex_lock(&wled->lock);
	अगर (brightness) अणु
		rc = wled->wled_set_brightness(wled, brightness);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "wled failed to set brightness rc:%d\n",
				rc);
			जाओ unlock_mutex;
		पूर्ण

		अगर (wled->version < 5) अणु
			rc = wled->wled_sync_toggle(wled);
			अगर (rc < 0) अणु
				dev_err(wled->dev, "wled sync failed rc:%d\n", rc);
				जाओ unlock_mutex;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * For WLED5 toggling the MOD_SYNC_BIT updates the
			 * brightness
			 */
			rc = wled5_mod_sync_toggle(wled);
			अगर (rc < 0) अणु
				dev_err(wled->dev, "wled mod sync failed rc:%d\n",
					rc);
				जाओ unlock_mutex;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!!brightness != !!wled->brightness) अणु
		rc = wled_module_enable(wled, !!brightness);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "wled enable failed rc:%d\n", rc);
			जाओ unlock_mutex;
		पूर्ण
	पूर्ण

	wled->brightness = brightness;

unlock_mutex:
	mutex_unlock(&wled->lock);

	वापस rc;
पूर्ण

अटल पूर्णांक wled4_cabc_config(काष्ठा wled *wled, bool enable)
अणु
	पूर्णांक i, j, rc;
	u8 val;

	क्रम (i = 0; i < wled->cfg.num_strings; i++) अणु
		j = wled->cfg.enabled_strings[i];

		val = enable ? WLED4_SINK_REG_STR_CABC_MASK : 0;
		rc = regmap_update_bits(wled->regmap, wled->sink_addr +
					WLED4_SINK_REG_STR_CABC(j),
					WLED4_SINK_REG_STR_CABC_MASK, val);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wled5_cabc_config(काष्ठा wled *wled, bool enable)
अणु
	पूर्णांक rc, offset;
	u8 reg;

	अगर (wled->cabc_disabled)
		वापस 0;

	reg = enable ? wled->cfg.cabc_sel : 0;
	offset = (wled->cfg.mod_sel == MOD_A) ? WLED5_SINK_REG_MOD_A_SRC_SEL :
						WLED5_SINK_REG_MOD_B_SRC_SEL;

	rc = regmap_update_bits(wled->regmap, wled->sink_addr + offset,
				WLED5_SINK_REG_MOD_SRC_SEL_MASK, reg);
	अगर (rc < 0) अणु
		pr_err("Error in configuring CABC rc=%d\n", rc);
		वापस rc;
	पूर्ण

	अगर (!wled->cfg.cabc_sel)
		wled->cabc_disabled = true;

	वापस 0;
पूर्ण

#घोषणा WLED_SHORT_DLY_MS			20
#घोषणा WLED_SHORT_CNT_MAX			5
#घोषणा WLED_SHORT_RESET_CNT_DLY_US		USEC_PER_SEC

अटल irqवापस_t wled_लघु_irq_handler(पूर्णांक irq, व्योम *_wled)
अणु
	काष्ठा wled *wled = _wled;
	पूर्णांक rc;
	s64 elapsed_समय;

	wled->लघु_count++;
	mutex_lock(&wled->lock);
	rc = wled_module_enable(wled, false);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "wled disable failed rc:%d\n", rc);
		जाओ unlock_mutex;
	पूर्ण

	elapsed_समय = kसमय_us_delta(kसमय_get(),
				      wled->last_लघु_event);
	अगर (elapsed_समय > WLED_SHORT_RESET_CNT_DLY_US)
		wled->लघु_count = 1;

	अगर (wled->लघु_count > WLED_SHORT_CNT_MAX) अणु
		dev_err(wled->dev, "Short triggered %d times, disabling WLED forever!\n",
			wled->लघु_count);
		wled->disabled_by_लघु = true;
		जाओ unlock_mutex;
	पूर्ण

	wled->last_लघु_event = kसमय_get();

	msleep(WLED_SHORT_DLY_MS);
	rc = wled_module_enable(wled, true);
	अगर (rc < 0)
		dev_err(wled->dev, "wled enable failed rc:%d\n", rc);

unlock_mutex:
	mutex_unlock(&wled->lock);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा AUTO_DETECT_BRIGHTNESS		200

अटल व्योम wled_स्वतः_string_detection(काष्ठा wled *wled)
अणु
	पूर्णांक rc = 0, i, delay_समय_us;
	u32 sink_config = 0;
	u8 sink_test = 0, sink_valid = 0, val;
	bool fault_set;

	/* Read configured sink configuration */
	rc = regmap_पढ़ो(wled->regmap, wled->sink_addr +
			 WLED4_SINK_REG_CURR_SINK, &sink_config);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to read SINK configuration rc=%d\n",
			rc);
		जाओ failed_detect;
	पूर्ण

	/* Disable the module beक्रमe starting detection */
	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_MOD_EN,
				WLED3_CTRL_REG_MOD_EN_MASK, 0);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to disable WLED module rc=%d\n", rc);
		जाओ failed_detect;
	पूर्ण

	/* Set low brightness across all sinks */
	rc = wled4_set_brightness(wled, AUTO_DETECT_BRIGHTNESS);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to set brightness for auto detection rc=%d\n",
			rc);
		जाओ failed_detect;
	पूर्ण

	अगर (wled->cfg.cabc) अणु
		rc = wled->wled_cabc_config(wled, false);
		अगर (rc < 0)
			जाओ failed_detect;
	पूर्ण

	/* Disable all sinks */
	rc = regmap_ग_लिखो(wled->regmap,
			  wled->sink_addr + WLED4_SINK_REG_CURR_SINK, 0);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to disable all sinks rc=%d\n", rc);
		जाओ failed_detect;
	पूर्ण

	/* Iterate through the strings one by one */
	क्रम (i = 0; i < wled->cfg.num_strings; i++) अणु
		sink_test = BIT((WLED4_SINK_REG_CURR_SINK_SHFT + i));

		/* Enable feedback control */
		rc = regmap_ग_लिखो(wled->regmap, wled->ctrl_addr +
				  WLED3_CTRL_REG_FEEDBACK_CONTROL, i + 1);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "Failed to enable feedback for SINK %d rc = %d\n",
				i + 1, rc);
			जाओ failed_detect;
		पूर्ण

		/* Enable the sink */
		rc = regmap_ग_लिखो(wled->regmap, wled->sink_addr +
				  WLED4_SINK_REG_CURR_SINK, sink_test);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "Failed to configure SINK %d rc=%d\n",
				i + 1, rc);
			जाओ failed_detect;
		पूर्ण

		/* Enable the module */
		rc = regmap_update_bits(wled->regmap, wled->ctrl_addr +
					WLED3_CTRL_REG_MOD_EN,
					WLED3_CTRL_REG_MOD_EN_MASK,
					WLED3_CTRL_REG_MOD_EN_MASK);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "Failed to enable WLED module rc=%d\n",
				rc);
			जाओ failed_detect;
		पूर्ण

		delay_समय_us = wled->wled_ovp_delay(wled);
		usleep_range(delay_समय_us, delay_समय_us + 1000);

		rc = wled_ovp_fault_status(wled, &fault_set);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "Error in getting OVP fault_sts, rc=%d\n",
				rc);
			जाओ failed_detect;
		पूर्ण

		अगर (fault_set)
			dev_dbg(wled->dev, "WLED OVP fault detected with SINK %d\n",
				i + 1);
		अन्यथा
			sink_valid |= sink_test;

		/* Disable the module */
		rc = regmap_update_bits(wled->regmap,
					wled->ctrl_addr + WLED3_CTRL_REG_MOD_EN,
					WLED3_CTRL_REG_MOD_EN_MASK, 0);
		अगर (rc < 0) अणु
			dev_err(wled->dev, "Failed to disable WLED module rc=%d\n",
				rc);
			जाओ failed_detect;
		पूर्ण
	पूर्ण

	अगर (!sink_valid) अणु
		dev_err(wled->dev, "No valid WLED sinks found\n");
		wled->disabled_by_लघु = true;
		जाओ failed_detect;
	पूर्ण

	अगर (sink_valid != sink_config) अणु
		dev_warn(wled->dev, "%x is not a valid sink configuration - using %x instead\n",
			 sink_config, sink_valid);
		sink_config = sink_valid;
	पूर्ण

	/* Write the new sink configuration */
	rc = regmap_ग_लिखो(wled->regmap,
			  wled->sink_addr + WLED4_SINK_REG_CURR_SINK,
			  sink_config);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to reconfigure the default sink rc=%d\n",
			rc);
		जाओ failed_detect;
	पूर्ण

	/* Enable valid sinks */
	अगर (wled->version == 4) अणु
		क्रम (i = 0; i < wled->cfg.num_strings; i++) अणु
			अगर (sink_config &
			    BIT(WLED4_SINK_REG_CURR_SINK_SHFT + i))
				val = WLED4_SINK_REG_STR_MOD_MASK;
			अन्यथा
				/* Disable modulator_en क्रम unused sink */
				val = 0;

			rc = regmap_ग_लिखो(wled->regmap, wled->sink_addr +
					  WLED4_SINK_REG_STR_MOD_EN(i), val);
			अगर (rc < 0) अणु
				dev_err(wled->dev, "Failed to configure MODULATOR_EN rc=%d\n",
					rc);
				जाओ failed_detect;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Enable CABC */
	rc = wled->wled_cabc_config(wled, true);
	अगर (rc < 0)
		जाओ failed_detect;

	/* Restore the feedback setting */
	rc = regmap_ग_लिखो(wled->regmap,
			  wled->ctrl_addr + WLED3_CTRL_REG_FEEDBACK_CONTROL, 0);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to restore feedback setting rc=%d\n",
			rc);
		जाओ failed_detect;
	पूर्ण

	/* Restore brightness */
	rc = wled4_set_brightness(wled, wled->brightness);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to set brightness after auto detection rc=%d\n",
			rc);
		जाओ failed_detect;
	पूर्ण

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_MOD_EN,
				WLED3_CTRL_REG_MOD_EN_MASK,
				WLED3_CTRL_REG_MOD_EN_MASK);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to enable WLED module rc=%d\n", rc);
		जाओ failed_detect;
	पूर्ण

failed_detect:
	वापस;
पूर्ण

#घोषणा WLED_AUTO_DETECT_OVP_COUNT		5
#घोषणा WLED_AUTO_DETECT_CNT_DLY_US		USEC_PER_SEC

अटल bool wled4_स्वतः_detection_required(काष्ठा wled *wled)
अणु
	s64 elapsed_समय_us;

	अगर (!wled->cfg.स्वतः_detection_enabled)
		वापस false;

	/*
	 * Check अगर the OVP fault was an occasional one
	 * or अगर it's firing continuously, the latter qualअगरies
	 * क्रम an स्वतः-detection check.
	 */
	अगर (!wled->स्वतः_detection_ovp_count) अणु
		wled->start_ovp_fault_समय = kसमय_get();
		wled->स्वतः_detection_ovp_count++;
	पूर्ण अन्यथा अणु
		elapsed_समय_us = kसमय_us_delta(kसमय_get(),
						 wled->start_ovp_fault_समय);
		अगर (elapsed_समय_us > WLED_AUTO_DETECT_CNT_DLY_US)
			wled->स्वतः_detection_ovp_count = 0;
		अन्यथा
			wled->स्वतः_detection_ovp_count++;

		अगर (wled->स्वतः_detection_ovp_count >=
				WLED_AUTO_DETECT_OVP_COUNT) अणु
			wled->स्वतः_detection_ovp_count = 0;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool wled5_स्वतः_detection_required(काष्ठा wled *wled)
अणु
	अगर (!wled->cfg.स्वतः_detection_enabled)
		वापस false;

	/*
	 * Unlike WLED4, WLED5 has OVP fault density पूर्णांकerrupt configuration
	 * i.e. to count the number of OVP alarms क्रम a certain duration beक्रमe
	 * triggering OVP fault पूर्णांकerrupt. By शेष, number of OVP fault
	 * events counted beक्रमe an पूर्णांकerrupt is fired is 32 and the समय
	 * पूर्णांकerval is 12 ms. If we see one OVP fault पूर्णांकerrupt, then that
	 * should qualअगरy क्रम a real OVP fault condition to run स्वतः detection
	 * algorithm.
	 */
	वापस true;
पूर्ण

अटल पूर्णांक wled_स्वतः_detection_at_init(काष्ठा wled *wled)
अणु
	पूर्णांक rc;
	bool fault_set;

	अगर (!wled->cfg.स्वतः_detection_enabled)
		वापस 0;

	rc = wled_ovp_fault_status(wled, &fault_set);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Error in getting OVP fault_sts, rc=%d\n",
			rc);
		वापस rc;
	पूर्ण

	अगर (fault_set) अणु
		mutex_lock(&wled->lock);
		wled_स्वतः_string_detection(wled);
		mutex_unlock(&wled->lock);
	पूर्ण

	वापस rc;
पूर्ण

अटल irqवापस_t wled_ovp_irq_handler(पूर्णांक irq, व्योम *_wled)
अणु
	काष्ठा wled *wled = _wled;
	पूर्णांक rc;
	u32 पूर्णांक_sts, fault_sts;

	rc = regmap_पढ़ो(wled->regmap,
			 wled->ctrl_addr + WLED3_CTRL_REG_INT_RT_STS, &पूर्णांक_sts);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Error in reading WLED3_INT_RT_STS rc=%d\n",
			rc);
		वापस IRQ_HANDLED;
	पूर्ण

	rc = regmap_पढ़ो(wled->regmap, wled->ctrl_addr +
			 WLED3_CTRL_REG_FAULT_STATUS, &fault_sts);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Error in reading WLED_FAULT_STATUS rc=%d\n",
			rc);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (fault_sts & (WLED3_CTRL_REG_OVP_FAULT_BIT |
		WLED3_CTRL_REG_ILIM_FAULT_BIT))
		dev_dbg(wled->dev, "WLED OVP fault detected, int_sts=%x fault_sts= %x\n",
			पूर्णांक_sts, fault_sts);

	अगर (fault_sts & WLED3_CTRL_REG_OVP_FAULT_BIT) अणु
		अगर (wled->wled_स्वतः_detection_required(wled)) अणु
			mutex_lock(&wled->lock);
			wled_स्वतः_string_detection(wled);
			mutex_unlock(&wled->lock);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wled3_setup(काष्ठा wled *wled)
अणु
	u16 addr;
	u8 sink_en = 0;
	पूर्णांक rc, i, j;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_OVP,
				WLED3_CTRL_REG_OVP_MASK, wled->cfg.ovp);
	अगर (rc)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_ILIMIT,
				WLED3_CTRL_REG_ILIMIT_MASK,
				wled->cfg.boost_i_limit);
	अगर (rc)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_FREQ,
				WLED3_CTRL_REG_FREQ_MASK,
				wled->cfg.चयन_freq);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < wled->cfg.num_strings; ++i) अणु
		j = wled->cfg.enabled_strings[i];
		addr = wled->ctrl_addr + WLED3_SINK_REG_STR_MOD_EN(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED3_SINK_REG_STR_MOD_MASK,
					WLED3_SINK_REG_STR_MOD_MASK);
		अगर (rc)
			वापस rc;

		अगर (wled->cfg.ext_gen) अणु
			addr = wled->ctrl_addr + WLED3_SINK_REG_STR_MOD_SRC(j);
			rc = regmap_update_bits(wled->regmap, addr,
						WLED3_SINK_REG_STR_MOD_SRC_MASK,
						WLED3_SINK_REG_STR_MOD_SRC_EXT);
			अगर (rc)
				वापस rc;
		पूर्ण

		addr = wled->ctrl_addr + WLED3_SINK_REG_STR_FULL_SCALE_CURR(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED3_SINK_REG_STR_FULL_SCALE_CURR_MASK,
					wled->cfg.string_i_limit);
		अगर (rc)
			वापस rc;

		addr = wled->ctrl_addr + WLED3_SINK_REG_STR_CABC(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED3_SINK_REG_STR_CABC_MASK,
					wled->cfg.cabc ?
					WLED3_SINK_REG_STR_CABC_MASK : 0);
		अगर (rc)
			वापस rc;

		sink_en |= BIT(j + WLED3_SINK_REG_CURR_SINK_SHFT);
	पूर्ण

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_SINK_REG_CURR_SINK,
				WLED3_SINK_REG_CURR_SINK_MASK, sink_en);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wled_config wled3_config_शेषs = अणु
	.boost_i_limit = 3,
	.string_i_limit = 20,
	.ovp = 2,
	.num_strings = 3,
	.चयन_freq = 5,
	.cs_out_en = false,
	.ext_gen = false,
	.cabc = false,
	.enabled_strings = अणु0, 1, 2, 3पूर्ण,
पूर्ण;

अटल पूर्णांक wled4_setup(काष्ठा wled *wled)
अणु
	पूर्णांक rc, temp, i, j;
	u16 addr;
	u8 sink_en = 0;
	u32 sink_cfg;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_OVP,
				WLED3_CTRL_REG_OVP_MASK, wled->cfg.ovp);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_ILIMIT,
				WLED3_CTRL_REG_ILIMIT_MASK,
				wled->cfg.boost_i_limit);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_FREQ,
				WLED3_CTRL_REG_FREQ_MASK,
				wled->cfg.चयन_freq);
	अगर (rc < 0)
		वापस rc;

	अगर (wled->cfg.बाह्यal_pfet) अणु
		/* Unlock the secure रेजिस्टर access */
		rc = regmap_ग_लिखो(wled->regmap, wled->ctrl_addr +
				  WLED4_CTRL_REG_SEC_ACCESS,
				  WLED4_CTRL_REG_SEC_UNLOCK);
		अगर (rc < 0)
			वापस rc;

		rc = regmap_ग_लिखो(wled->regmap,
				  wled->ctrl_addr + WLED4_CTRL_REG_TEST1,
				  WLED4_CTRL_REG_TEST1_EXT_FET_DTEST2);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = regmap_पढ़ो(wled->regmap, wled->sink_addr +
			 WLED4_SINK_REG_CURR_SINK, &sink_cfg);
	अगर (rc < 0)
		वापस rc;

	क्रम (i = 0; i < wled->cfg.num_strings; i++) अणु
		j = wled->cfg.enabled_strings[i];
		temp = j + WLED4_SINK_REG_CURR_SINK_SHFT;
		sink_en |= 1 << temp;
	पूर्ण

	अगर (sink_cfg == sink_en) अणु
		rc = wled_स्वतः_detection_at_init(wled);
		वापस rc;
	पूर्ण

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED4_SINK_REG_CURR_SINK,
				WLED4_SINK_REG_CURR_SINK_MASK, 0);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap, wled->ctrl_addr +
				WLED3_CTRL_REG_MOD_EN,
				WLED3_CTRL_REG_MOD_EN_MASK, 0);
	अगर (rc < 0)
		वापस rc;

	/* Per sink/string configuration */
	क्रम (i = 0; i < wled->cfg.num_strings; i++) अणु
		j = wled->cfg.enabled_strings[i];

		addr = wled->sink_addr +
				WLED4_SINK_REG_STR_MOD_EN(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED4_SINK_REG_STR_MOD_MASK,
					WLED4_SINK_REG_STR_MOD_MASK);
		अगर (rc < 0)
			वापस rc;

		addr = wled->sink_addr +
				WLED4_SINK_REG_STR_FULL_SCALE_CURR(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED4_SINK_REG_STR_FULL_SCALE_CURR_MASK,
					wled->cfg.string_i_limit);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = wled4_cabc_config(wled, wled->cfg.cabc);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap, wled->ctrl_addr +
				WLED3_CTRL_REG_MOD_EN,
				WLED3_CTRL_REG_MOD_EN_MASK,
				WLED3_CTRL_REG_MOD_EN_MASK);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED4_SINK_REG_CURR_SINK,
				WLED4_SINK_REG_CURR_SINK_MASK, sink_en);
	अगर (rc < 0)
		वापस rc;

	rc = wled->wled_sync_toggle(wled);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Failed to toggle sync reg rc:%d\n", rc);
		वापस rc;
	पूर्ण

	rc = wled_स्वतः_detection_at_init(wled);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा wled_config wled4_config_शेषs = अणु
	.boost_i_limit = 4,
	.string_i_limit = 10,
	.ovp = 1,
	.num_strings = 4,
	.चयन_freq = 11,
	.cabc = false,
	.बाह्यal_pfet = false,
	.स्वतः_detection_enabled = false,
पूर्ण;

अटल पूर्णांक wled5_setup(काष्ठा wled *wled)
अणु
	पूर्णांक rc, temp, i, j, offset;
	u8 sink_en = 0;
	u16 addr;
	u32 val;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_OVP,
				WLED5_CTRL_REG_OVP_MASK, wled->cfg.ovp);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_ILIMIT,
				WLED3_CTRL_REG_ILIMIT_MASK,
				wled->cfg.boost_i_limit);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->ctrl_addr + WLED3_CTRL_REG_FREQ,
				WLED3_CTRL_REG_FREQ_MASK,
				wled->cfg.चयन_freq);
	अगर (rc < 0)
		वापस rc;

	/* Per sink/string configuration */
	क्रम (i = 0; i < wled->cfg.num_strings; ++i) अणु
		j = wled->cfg.enabled_strings[i];
		addr = wled->sink_addr +
				WLED4_SINK_REG_STR_FULL_SCALE_CURR(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED4_SINK_REG_STR_FULL_SCALE_CURR_MASK,
					wled->cfg.string_i_limit);
		अगर (rc < 0)
			वापस rc;

		addr = wled->sink_addr + WLED5_SINK_REG_STR_SRC_SEL(j);
		rc = regmap_update_bits(wled->regmap, addr,
					WLED5_SINK_REG_SRC_SEL_MASK,
					wled->cfg.mod_sel == MOD_A ?
					WLED5_SINK_REG_SRC_SEL_MOD_A :
					WLED5_SINK_REG_SRC_SEL_MOD_B);

		temp = j + WLED4_SINK_REG_CURR_SINK_SHFT;
		sink_en |= 1 << temp;
	पूर्ण

	rc = wled5_cabc_config(wled, wled->cfg.cabc_sel ? true : false);
	अगर (rc < 0)
		वापस rc;

	/* Enable one of the modulators A or B based on mod_sel */
	addr = wled->sink_addr + WLED5_SINK_REG_MOD_A_EN;
	val = (wled->cfg.mod_sel == MOD_A) ? WLED5_SINK_REG_MOD_EN_MASK : 0;
	rc = regmap_update_bits(wled->regmap, addr,
				WLED5_SINK_REG_MOD_EN_MASK, val);
	अगर (rc < 0)
		वापस rc;

	addr = wled->sink_addr + WLED5_SINK_REG_MOD_B_EN;
	val = (wled->cfg.mod_sel == MOD_B) ? WLED5_SINK_REG_MOD_EN_MASK : 0;
	rc = regmap_update_bits(wled->regmap, addr,
				WLED5_SINK_REG_MOD_EN_MASK, val);
	अगर (rc < 0)
		वापस rc;

	offset = (wled->cfg.mod_sel == MOD_A) ?
		  WLED5_SINK_REG_MOD_A_BRIGHTNESS_WIDTH_SEL :
		  WLED5_SINK_REG_MOD_B_BRIGHTNESS_WIDTH_SEL;

	addr = wled->sink_addr + offset;
	val = (wled->max_brightness == WLED5_SINK_REG_BRIGHT_MAX_15B) ?
		 WLED5_SINK_REG_BRIGHTNESS_WIDTH_15B :
		 WLED5_SINK_REG_BRIGHTNESS_WIDTH_12B;
	rc = regmap_ग_लिखो(wled->regmap, addr, val);
	अगर (rc < 0)
		वापस rc;

	rc = regmap_update_bits(wled->regmap,
				wled->sink_addr + WLED4_SINK_REG_CURR_SINK,
				WLED4_SINK_REG_CURR_SINK_MASK, sink_en);
	अगर (rc < 0)
		वापस rc;

	/* This updates only FSC configuration in WLED5 */
	rc = wled->wled_sync_toggle(wled);
	अगर (rc < 0) अणु
		pr_err("Failed to toggle sync reg rc:%d\n", rc);
		वापस rc;
	पूर्ण

	rc = wled_स्वतः_detection_at_init(wled);
	अगर (rc < 0)
		वापस rc;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा wled_config wled5_config_शेषs = अणु
	.boost_i_limit = 5,
	.string_i_limit = 10,
	.ovp = 4,
	.num_strings = 4,
	.चयन_freq = 11,
	.mod_sel = 0,
	.cabc_sel = 0,
	.cabc = false,
	.बाह्यal_pfet = false,
	.स्वतः_detection_enabled = false,
पूर्ण;

अटल स्थिर u32 wled3_boost_i_limit_values[] = अणु
	105, 385, 525, 805, 980, 1260, 1400, 1680,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled3_boost_i_limit_cfg = अणु
	.values = wled3_boost_i_limit_values,
	.size = ARRAY_SIZE(wled3_boost_i_limit_values),
पूर्ण;

अटल स्थिर u32 wled4_boost_i_limit_values[] = अणु
	105, 280, 450, 620, 970, 1150, 1300, 1500,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled4_boost_i_limit_cfg = अणु
	.values = wled4_boost_i_limit_values,
	.size = ARRAY_SIZE(wled4_boost_i_limit_values),
पूर्ण;

अटल अंतरभूत u32 wled5_boost_i_limit_values_fn(u32 idx)
अणु
	वापस 525 + (idx * 175);
पूर्ण

अटल स्थिर काष्ठा wled_var_cfg wled5_boost_i_limit_cfg = अणु
	.fn = wled5_boost_i_limit_values_fn,
	.size = 8,
पूर्ण;

अटल स्थिर u32 wled3_ovp_values[] = अणु
	35, 32, 29, 27,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled3_ovp_cfg = अणु
	.values = wled3_ovp_values,
	.size = ARRAY_SIZE(wled3_ovp_values),
पूर्ण;

अटल स्थिर u32 wled4_ovp_values[] = अणु
	31100, 29600, 19600, 18100,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled4_ovp_cfg = अणु
	.values = wled4_ovp_values,
	.size = ARRAY_SIZE(wled4_ovp_values),
पूर्ण;

अटल अंतरभूत u32 wled5_ovp_values_fn(u32 idx)
अणु
	/*
	 * 0000 - 38.5 V
	 * 0001 - 37 V ..
	 * 1111 - 16 V
	 */
	वापस 38500 - (idx * 1500);
पूर्ण

अटल स्थिर काष्ठा wled_var_cfg wled5_ovp_cfg = अणु
	.fn = wled5_ovp_values_fn,
	.size = 16,
पूर्ण;

अटल u32 wled3_num_strings_values_fn(u32 idx)
अणु
	वापस idx + 1;
पूर्ण

अटल स्थिर काष्ठा wled_var_cfg wled3_num_strings_cfg = अणु
	.fn = wled3_num_strings_values_fn,
	.size = 3,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled4_num_strings_cfg = अणु
	.fn = wled3_num_strings_values_fn,
	.size = 4,
पूर्ण;

अटल u32 wled3_चयन_freq_values_fn(u32 idx)
अणु
	वापस 19200 / (2 * (1 + idx));
पूर्ण

अटल स्थिर काष्ठा wled_var_cfg wled3_चयन_freq_cfg = अणु
	.fn = wled3_चयन_freq_values_fn,
	.size = 16,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled3_string_i_limit_cfg = अणु
	.size = 26,
पूर्ण;

अटल स्थिर u32 wled4_string_i_limit_values[] = अणु
	0, 2500, 5000, 7500, 10000, 12500, 15000, 17500, 20000,
	22500, 25000, 27500, 30000,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled4_string_i_limit_cfg = अणु
	.values = wled4_string_i_limit_values,
	.size = ARRAY_SIZE(wled4_string_i_limit_values),
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled5_mod_sel_cfg = अणु
	.size = 2,
पूर्ण;

अटल स्थिर काष्ठा wled_var_cfg wled5_cabc_sel_cfg = अणु
	.size = 4,
पूर्ण;

अटल u32 wled_values(स्थिर काष्ठा wled_var_cfg *cfg, u32 idx)
अणु
	अगर (idx >= cfg->size)
		वापस अच_पूर्णांक_उच्च;
	अगर (cfg->fn)
		वापस cfg->fn(idx);
	अगर (cfg->values)
		वापस cfg->values[idx];
	वापस idx;
पूर्ण

अटल पूर्णांक wled_configure(काष्ठा wled *wled)
अणु
	काष्ठा wled_config *cfg = &wled->cfg;
	काष्ठा device *dev = wled->dev;
	स्थिर __be32 *prop_addr;
	u32 size, val, c;
	पूर्णांक rc, i, j, string_len;

	स्थिर काष्ठा wled_u32_opts *u32_opts = शून्य;
	स्थिर काष्ठा wled_u32_opts wled3_opts[] = अणु
		अणु
			.name = "qcom,current-boost-limit",
			.val_ptr = &cfg->boost_i_limit,
			.cfg = &wled3_boost_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,current-limit",
			.val_ptr = &cfg->string_i_limit,
			.cfg = &wled3_string_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,ovp",
			.val_ptr = &cfg->ovp,
			.cfg = &wled3_ovp_cfg,
		पूर्ण,
		अणु
			.name = "qcom,switching-freq",
			.val_ptr = &cfg->चयन_freq,
			.cfg = &wled3_चयन_freq_cfg,
		पूर्ण,
		अणु
			.name = "qcom,num-strings",
			.val_ptr = &cfg->num_strings,
			.cfg = &wled3_num_strings_cfg,
		पूर्ण,
	पूर्ण;

	स्थिर काष्ठा wled_u32_opts wled4_opts[] = अणु
		अणु
			.name = "qcom,current-boost-limit",
			.val_ptr = &cfg->boost_i_limit,
			.cfg = &wled4_boost_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,current-limit-microamp",
			.val_ptr = &cfg->string_i_limit,
			.cfg = &wled4_string_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,ovp-millivolt",
			.val_ptr = &cfg->ovp,
			.cfg = &wled4_ovp_cfg,
		पूर्ण,
		अणु
			.name = "qcom,switching-freq",
			.val_ptr = &cfg->चयन_freq,
			.cfg = &wled3_चयन_freq_cfg,
		पूर्ण,
		अणु
			.name = "qcom,num-strings",
			.val_ptr = &cfg->num_strings,
			.cfg = &wled4_num_strings_cfg,
		पूर्ण,
	पूर्ण;

	स्थिर काष्ठा wled_u32_opts wled5_opts[] = अणु
		अणु
			.name = "qcom,current-boost-limit",
			.val_ptr = &cfg->boost_i_limit,
			.cfg = &wled5_boost_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,current-limit-microamp",
			.val_ptr = &cfg->string_i_limit,
			.cfg = &wled4_string_i_limit_cfg,
		पूर्ण,
		अणु
			.name = "qcom,ovp-millivolt",
			.val_ptr = &cfg->ovp,
			.cfg = &wled5_ovp_cfg,
		पूर्ण,
		अणु
			.name = "qcom,switching-freq",
			.val_ptr = &cfg->चयन_freq,
			.cfg = &wled3_चयन_freq_cfg,
		पूर्ण,
		अणु
			.name = "qcom,num-strings",
			.val_ptr = &cfg->num_strings,
			.cfg = &wled4_num_strings_cfg,
		पूर्ण,
		अणु
			.name = "qcom,modulator-sel",
			.val_ptr = &cfg->mod_sel,
			.cfg = &wled5_mod_sel_cfg,
		पूर्ण,
		अणु
			.name = "qcom,cabc-sel",
			.val_ptr = &cfg->cabc_sel,
			.cfg = &wled5_cabc_sel_cfg,
		पूर्ण,
	पूर्ण;

	स्थिर काष्ठा wled_bool_opts bool_opts[] = अणु
		अणु "qcom,cs-out", &cfg->cs_out_en, पूर्ण,
		अणु "qcom,ext-gen", &cfg->ext_gen, पूर्ण,
		अणु "qcom,cabc", &cfg->cabc, पूर्ण,
		अणु "qcom,external-pfet", &cfg->बाह्यal_pfet, पूर्ण,
		अणु "qcom,auto-string-detection", &cfg->स्वतः_detection_enabled, पूर्ण,
	पूर्ण;

	prop_addr = of_get_address(dev->of_node, 0, शून्य, शून्य);
	अगर (!prop_addr) अणु
		dev_err(wled->dev, "invalid IO resources\n");
		वापस -EINVAL;
	पूर्ण
	wled->ctrl_addr = be32_to_cpu(*prop_addr);

	rc = of_property_पढ़ो_string(dev->of_node, "label", &wled->name);
	अगर (rc)
		wled->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%pOFn", dev->of_node);

	चयन (wled->version) अणु
	हाल 3:
		u32_opts = wled3_opts;
		size = ARRAY_SIZE(wled3_opts);
		*cfg = wled3_config_शेषs;
		wled->wled_set_brightness = wled3_set_brightness;
		wled->wled_sync_toggle = wled3_sync_toggle;
		wled->max_string_count = 3;
		wled->sink_addr = wled->ctrl_addr;
		अवरोध;

	हाल 4:
		u32_opts = wled4_opts;
		size = ARRAY_SIZE(wled4_opts);
		*cfg = wled4_config_शेषs;
		wled->wled_set_brightness = wled4_set_brightness;
		wled->wled_sync_toggle = wled3_sync_toggle;
		wled->wled_cabc_config = wled4_cabc_config;
		wled->wled_ovp_delay = wled4_ovp_delay;
		wled->wled_स्वतः_detection_required =
					wled4_स्वतः_detection_required;
		wled->max_string_count = 4;

		prop_addr = of_get_address(dev->of_node, 1, शून्य, शून्य);
		अगर (!prop_addr) अणु
			dev_err(wled->dev, "invalid IO resources\n");
			वापस -EINVAL;
		पूर्ण
		wled->sink_addr = be32_to_cpu(*prop_addr);
		अवरोध;

	हाल 5:
		u32_opts = wled5_opts;
		size = ARRAY_SIZE(wled5_opts);
		*cfg = wled5_config_शेषs;
		wled->wled_set_brightness = wled5_set_brightness;
		wled->wled_sync_toggle = wled3_sync_toggle;
		wled->wled_cabc_config = wled5_cabc_config;
		wled->wled_ovp_delay = wled5_ovp_delay;
		wled->wled_स्वतः_detection_required =
					wled5_स्वतः_detection_required;
		wled->max_string_count = 4;

		prop_addr = of_get_address(dev->of_node, 1, शून्य, शून्य);
		अगर (!prop_addr) अणु
			dev_err(wled->dev, "invalid IO resources\n");
			वापस -EINVAL;
		पूर्ण
		wled->sink_addr = be32_to_cpu(*prop_addr);
		अवरोध;

	शेष:
		dev_err(wled->dev, "Invalid WLED version\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; ++i) अणु
		rc = of_property_पढ़ो_u32(dev->of_node, u32_opts[i].name, &val);
		अगर (rc == -EINVAL) अणु
			जारी;
		पूर्ण अन्यथा अगर (rc) अणु
			dev_err(dev, "error reading '%s'\n", u32_opts[i].name);
			वापस rc;
		पूर्ण

		c = अच_पूर्णांक_उच्च;
		क्रम (j = 0; c != val; j++) अणु
			c = wled_values(u32_opts[i].cfg, j);
			अगर (c == अच_पूर्णांक_उच्च) अणु
				dev_err(dev, "invalid value for '%s'\n",
					u32_opts[i].name);
				वापस -EINVAL;
			पूर्ण

			अगर (c == val)
				अवरोध;
		पूर्ण

		dev_dbg(dev, "'%s' = %u\n", u32_opts[i].name, c);
		*u32_opts[i].val_ptr = j;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(bool_opts); ++i) अणु
		अगर (of_property_पढ़ो_bool(dev->of_node, bool_opts[i].name))
			*bool_opts[i].val_ptr = true;
	पूर्ण

	cfg->num_strings = cfg->num_strings + 1;

	string_len = of_property_count_elems_of_size(dev->of_node,
						     "qcom,enabled-strings",
						     माप(u32));
	अगर (string_len > 0)
		of_property_पढ़ो_u32_array(dev->of_node,
						"qcom,enabled-strings",
						wled->cfg.enabled_strings,
						माप(u32));

	वापस 0;
पूर्ण

अटल पूर्णांक wled_configure_लघु_irq(काष्ठा wled *wled,
				    काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;

	अगर (!wled->has_लघु_detect)
		वापस 0;

	rc = regmap_update_bits(wled->regmap, wled->ctrl_addr +
				WLED4_CTRL_REG_SHORT_PROTECT,
				WLED4_CTRL_REG_SHORT_EN_MASK,
				WLED4_CTRL_REG_SHORT_EN_MASK);
	अगर (rc < 0)
		वापस rc;

	wled->लघु_irq = platक्रमm_get_irq_byname(pdev, "short");
	अगर (wled->लघु_irq < 0) अणु
		dev_dbg(&pdev->dev, "short irq is not used\n");
		वापस 0;
	पूर्ण

	rc = devm_request_thपढ़ोed_irq(wled->dev, wled->लघु_irq,
				       शून्य, wled_लघु_irq_handler,
				       IRQF_ONESHOT,
				       "wled_short_irq", wled);
	अगर (rc < 0)
		dev_err(wled->dev, "Unable to request short_irq (err:%d)\n",
			rc);

	वापस rc;
पूर्ण

अटल पूर्णांक wled_configure_ovp_irq(काष्ठा wled *wled,
				  काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक rc;
	u32 val;

	wled->ovp_irq = platक्रमm_get_irq_byname(pdev, "ovp");
	अगर (wled->ovp_irq < 0) अणु
		dev_dbg(&pdev->dev, "OVP IRQ not found - disabling automatic string detection\n");
		वापस 0;
	पूर्ण

	rc = devm_request_thपढ़ोed_irq(wled->dev, wled->ovp_irq, शून्य,
				       wled_ovp_irq_handler, IRQF_ONESHOT,
				       "wled_ovp_irq", wled);
	अगर (rc < 0) अणु
		dev_err(wled->dev, "Unable to request ovp_irq (err:%d)\n",
			rc);
		wled->ovp_irq = 0;
		वापस 0;
	पूर्ण

	rc = regmap_पढ़ो(wled->regmap, wled->ctrl_addr +
			 WLED3_CTRL_REG_MOD_EN, &val);
	अगर (rc < 0)
		वापस rc;

	/* Keep OVP irq disabled until module is enabled */
	अगर (!(val & WLED3_CTRL_REG_MOD_EN_MASK))
		disable_irq(wled->ovp_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops wled_ops = अणु
	.update_status = wled_update_status,
पूर्ण;

अटल पूर्णांक wled_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bl;
	काष्ठा wled *wled;
	काष्ठा regmap *regmap;
	u32 val;
	पूर्णांक rc;

	regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!regmap) अणु
		dev_err(&pdev->dev, "Unable to get regmap\n");
		वापस -EINVAL;
	पूर्ण

	wled = devm_kzalloc(&pdev->dev, माप(*wled), GFP_KERNEL);
	अगर (!wled)
		वापस -ENOMEM;

	wled->regmap = regmap;
	wled->dev = &pdev->dev;

	wled->version = (uपूर्णांकptr_t)of_device_get_match_data(&pdev->dev);
	अगर (!wled->version) अणु
		dev_err(&pdev->dev, "Unknown device version\n");
		वापस -ENODEV;
	पूर्ण

	mutex_init(&wled->lock);
	rc = wled_configure(wled);
	अगर (rc)
		वापस rc;

	val = WLED3_SINK_REG_BRIGHT_MAX;
	of_property_पढ़ो_u32(pdev->dev.of_node, "max-brightness", &val);
	wled->max_brightness = val;

	चयन (wled->version) अणु
	हाल 3:
		wled->cfg.स्वतः_detection_enabled = false;
		rc = wled3_setup(wled);
		अगर (rc) अणु
			dev_err(&pdev->dev, "wled3_setup failed\n");
			वापस rc;
		पूर्ण
		अवरोध;

	हाल 4:
		wled->has_लघु_detect = true;
		rc = wled4_setup(wled);
		अगर (rc) अणु
			dev_err(&pdev->dev, "wled4_setup failed\n");
			वापस rc;
		पूर्ण
		अवरोध;

	हाल 5:
		wled->has_लघु_detect = true;
		अगर (wled->cfg.cabc_sel)
			wled->max_brightness = WLED5_SINK_REG_BRIGHT_MAX_12B;

		rc = wled5_setup(wled);
		अगर (rc) अणु
			dev_err(&pdev->dev, "wled5_setup failed\n");
			वापस rc;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(wled->dev, "Invalid WLED version\n");
		अवरोध;
	पूर्ण

	INIT_DELAYED_WORK(&wled->ovp_work, wled_ovp_work);

	rc = wled_configure_लघु_irq(wled, pdev);
	अगर (rc < 0)
		वापस rc;

	rc = wled_configure_ovp_irq(wled, pdev);
	अगर (rc < 0)
		वापस rc;

	val = WLED_DEFAULT_BRIGHTNESS;
	of_property_पढ़ो_u32(pdev->dev.of_node, "default-brightness", &val);

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.brightness = val;
	props.max_brightness = wled->max_brightness;
	bl = devm_backlight_device_रेजिस्टर(&pdev->dev, wled->name,
					    &pdev->dev, wled,
					    &wled_ops, &props);
	वापस PTR_ERR_OR_ZERO(bl);
पूर्ण;

अटल पूर्णांक wled_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wled *wled = platक्रमm_get_drvdata(pdev);

	mutex_destroy(&wled->lock);
	cancel_delayed_work_sync(&wled->ovp_work);
	disable_irq(wled->लघु_irq);
	disable_irq(wled->ovp_irq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wled_match_table[] = अणु
	अणु .compatible = "qcom,pm8941-wled", .data = (व्योम *)3 पूर्ण,
	अणु .compatible = "qcom,pmi8998-wled", .data = (व्योम *)4 पूर्ण,
	अणु .compatible = "qcom,pm660l-wled", .data = (व्योम *)4 पूर्ण,
	अणु .compatible = "qcom,pm8150l-wled", .data = (व्योम *)5 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wled_match_table);

अटल काष्ठा platक्रमm_driver wled_driver = अणु
	.probe = wled_probe,
	.हटाओ = wled_हटाओ,
	.driver	= अणु
		.name = "qcom,wled",
		.of_match_table	= wled_match_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wled_driver);

MODULE_DESCRIPTION("Qualcomm WLED driver");
MODULE_LICENSE("GPL v2");
