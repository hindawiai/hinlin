<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * DA7280 Haptic device driver
 *
 * Copyright (c) 2020 Dialog Semiconductor.
 * Author: Roy Im <Roy.Im.Opensource@diasemi.com>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uaccess.h>

/* Registers */
#घोषणा DA7280_IRQ_EVENT1			0x03
#घोषणा DA7280_IRQ_EVENT_WARNING_DIAG		0x04
#घोषणा DA7280_IRQ_EVENT_SEQ_DIAG		0x05
#घोषणा DA7280_IRQ_STATUS1			0x06
#घोषणा DA7280_IRQ_MASK1			0x07
#घोषणा DA7280_FRQ_LRA_PER_H			0x0A
#घोषणा DA7280_FRQ_LRA_PER_L			0x0B
#घोषणा DA7280_ACTUATOR1			0x0C
#घोषणा DA7280_ACTUATOR2			0x0D
#घोषणा DA7280_ACTUATOR3			0x0E
#घोषणा DA7280_CALIB_V2I_H			0x0F
#घोषणा DA7280_CALIB_V2I_L			0x10
#घोषणा DA7280_TOP_CFG1				0x13
#घोषणा DA7280_TOP_CFG2				0x14
#घोषणा DA7280_TOP_CFG4				0x16
#घोषणा DA7280_TOP_INT_CFG1			0x17
#घोषणा DA7280_TOP_CTL1				0x22
#घोषणा DA7280_TOP_CTL2				0x23
#घोषणा DA7280_SEQ_CTL2				0x28
#घोषणा DA7280_GPI_0_CTL			0x29
#घोषणा DA7280_GPI_1_CTL			0x2A
#घोषणा DA7280_GPI_2_CTL			0x2B
#घोषणा DA7280_MEM_CTL1				0x2C
#घोषणा DA7280_MEM_CTL2				0x2D
#घोषणा DA7280_TOP_CFG5				0x6E
#घोषणा DA7280_IRQ_MASK2			0x83
#घोषणा DA7280_SNP_MEM_99			0xE7

/* Register field */

/* DA7280_IRQ_EVENT1 (Address 0x03) */
#घोषणा DA7280_E_SEQ_CONTINUE_MASK		BIT(0)
#घोषणा DA7280_E_UVLO_MASK			BIT(1)
#घोषणा DA7280_E_SEQ_DONE_MASK			BIT(2)
#घोषणा DA7280_E_OVERTEMP_CRIT_MASK		BIT(3)
#घोषणा DA7280_E_SEQ_FAULT_MASK			BIT(4)
#घोषणा DA7280_E_WARNING_MASK			BIT(5)
#घोषणा DA7280_E_ACTUATOR_FAULT_MASK		BIT(6)
#घोषणा DA7280_E_OC_FAULT_MASK			BIT(7)

/* DA7280_IRQ_EVENT_WARNING_DIAG (Address 0x04) */
#घोषणा DA7280_E_OVERTEMP_WARN_MASK             BIT(3)
#घोषणा DA7280_E_MEM_TYPE_MASK                  BIT(4)
#घोषणा DA7280_E_LIM_DRIVE_ACC_MASK             BIT(6)
#घोषणा DA7280_E_LIM_DRIVE_MASK                 BIT(7)

/* DA7280_IRQ_EVENT_PAT_DIAG (Address 0x05) */
#घोषणा DA7280_E_PWM_FAULT_MASK			BIT(5)
#घोषणा DA7280_E_MEM_FAULT_MASK			BIT(6)
#घोषणा DA7280_E_SEQ_ID_FAULT_MASK		BIT(7)

/* DA7280_IRQ_STATUS1 (Address 0x06) */
#घोषणा DA7280_STA_SEQ_CONTINUE_MASK		BIT(0)
#घोषणा DA7280_STA_UVLO_VBAT_OK_MASK		BIT(1)
#घोषणा DA7280_STA_SEQ_DONE_MASK		BIT(2)
#घोषणा DA7280_STA_OVERTEMP_CRIT_MASK		BIT(3)
#घोषणा DA7280_STA_SEQ_FAULT_MASK		BIT(4)
#घोषणा DA7280_STA_WARNING_MASK			BIT(5)
#घोषणा DA7280_STA_ACTUATOR_MASK		BIT(6)
#घोषणा DA7280_STA_OC_MASK			BIT(7)

/* DA7280_IRQ_MASK1 (Address 0x07) */
#घोषणा DA7280_SEQ_CONTINUE_M_MASK		BIT(0)
#घोषणा DA7280_E_UVLO_M_MASK			BIT(1)
#घोषणा DA7280_SEQ_DONE_M_MASK			BIT(2)
#घोषणा DA7280_OVERTEMP_CRIT_M_MASK		BIT(3)
#घोषणा DA7280_SEQ_FAULT_M_MASK			BIT(4)
#घोषणा DA7280_WARNING_M_MASK			BIT(5)
#घोषणा DA7280_ACTUATOR_M_MASK			BIT(6)
#घोषणा DA7280_OC_M_MASK			BIT(7)

/* DA7280_ACTUATOR3 (Address 0x0e) */
#घोषणा DA7280_IMAX_MASK			GENMASK(4, 0)

/* DA7280_TOP_CFG1 (Address 0x13) */
#घोषणा DA7280_AMP_PID_EN_MASK			BIT(0)
#घोषणा DA7280_RAPID_STOP_EN_MASK		BIT(1)
#घोषणा DA7280_ACCELERATION_EN_MASK		BIT(2)
#घोषणा DA7280_FREQ_TRACK_EN_MASK		BIT(3)
#घोषणा DA7280_BEMF_SENSE_EN_MASK		BIT(4)
#घोषणा DA7280_ACTUATOR_TYPE_MASK		BIT(5)

/* DA7280_TOP_CFG2 (Address 0x14) */
#घोषणा DA7280_FULL_BRAKE_THR_MASK		GENMASK(3, 0)
#घोषणा DA7280_MEM_DATA_SIGNED_MASK		BIT(4)

/* DA7280_TOP_CFG4 (Address 0x16) */
#घोषणा DA7280_TST_CALIB_IMPEDANCE_DIS_MASK	BIT(6)
#घोषणा DA7280_V2I_FACTOR_FREEZE_MASK		BIT(7)

/* DA7280_TOP_INT_CFG1 (Address 0x17) */
#घोषणा DA7280_BEMF_FAULT_LIM_MASK		GENMASK(1, 0)

/* DA7280_TOP_CTL1 (Address 0x22) */
#घोषणा DA7280_OPERATION_MODE_MASK		GENMASK(2, 0)
#घोषणा DA7280_STANDBY_EN_MASK			BIT(3)
#घोषणा DA7280_SEQ_START_MASK			BIT(4)

/* DA7280_SEQ_CTL2 (Address 0x28) */
#घोषणा DA7280_PS_SEQ_ID_MASK			GENMASK(3, 0)
#घोषणा DA7280_PS_SEQ_LOOP_MASK			GENMASK(7, 4)

/* DA7280_GPIO_0_CTL (Address 0x29) */
#घोषणा DA7280_GPI0_POLARITY_MASK		GENMASK(1, 0)
#घोषणा DA7280_GPI0_MODE_MASK			BIT(2)
#घोषणा DA7280_GPI0_SEQUENCE_ID_MASK		GENMASK(6, 3)

/* DA7280_GPIO_1_CTL (Address 0x2a) */
#घोषणा DA7280_GPI1_POLARITY_MASK		GENMASK(1, 0)
#घोषणा DA7280_GPI1_MODE_MASK			BIT(2)
#घोषणा DA7280_GPI1_SEQUENCE_ID_MASK		GENMASK(6, 3)

/* DA7280_GPIO_2_CTL (Address 0x2b) */
#घोषणा DA7280_GPI2_POLARITY_MASK		GENMASK(1, 0)
#घोषणा DA7280_GPI2_MODE_MASK			BIT(2)
#घोषणा DA7280_GPI2_SEQUENCE_ID_MASK		GENMASK(6, 3)

/* DA7280_MEM_CTL2 (Address 0x2d) */
#घोषणा DA7280_WAV_MEM_LOCK_MASK		BIT(7)

/* DA7280_TOP_CFG5 (Address 0x6e) */
#घोषणा DA7280_V2I_FACTOR_OFFSET_EN_MASK	BIT(0)

/* DA7280_IRQ_MASK2 (Address 0x83) */
#घोषणा DA7280_ADC_SAT_M_MASK			BIT(7)

/* Controls */

#घोषणा DA7280_VOLTAGE_RATE_MAX			6000000
#घोषणा DA7280_VOLTAGE_RATE_STEP		23400
#घोषणा DA7280_NOMMAX_DFT			0x6B
#घोषणा DA7280_ABSMAX_DFT			0x78

#घोषणा DA7280_IMPD_MAX				1500000000
#घोषणा DA7280_IMPD_DEFAULT			22000000

#घोषणा DA7280_IMAX_DEFAULT			0x0E
#घोषणा DA7280_IMAX_STEP			7200
#घोषणा DA7280_IMAX_LIMIT			252000

#घोषणा DA7280_RESONT_FREQH_DFT			0x39
#घोषणा DA7280_RESONT_FREQL_DFT			0x32
#घोषणा DA7280_MIN_RESONAT_FREQ_HZ		50
#घोषणा DA7280_MAX_RESONAT_FREQ_HZ		300

#घोषणा DA7280_SEQ_ID_MAX			15
#घोषणा DA7280_SEQ_LOOP_MAX			15
#घोषणा DA7280_GPI_SEQ_ID_DFT			0
#घोषणा DA7280_GPI_SEQ_ID_MAX			2

#घोषणा DA7280_SNP_MEM_SIZE			100
#घोषणा DA7280_SNP_MEM_MAX			DA7280_SNP_MEM_99

#घोषणा DA7280_IRQ_NUM				3

#घोषणा DA7280_SKIP_INIT			0x100

#घोषणा DA7280_FF_EFFECT_COUNT_MAX		15

/* Maximum gain is 0x7fff क्रम PWM mode */
#घोषणा DA7280_MAX_MAGNITUDE_SHIFT		15

क्रमागत da7280_haptic_dev_t अणु
	DA7280_LRA	= 0,
	DA7280_ERM_BAR	= 1,
	DA7280_ERM_COIN	= 2,
	DA7280_DEV_MAX,
पूर्ण;

क्रमागत da7280_op_mode अणु
	DA7280_INACTIVE		= 0,
	DA7280_DRO_MODE		= 1,
	DA7280_PWM_MODE		= 2,
	DA7280_RTWM_MODE	= 3,
	DA7280_ETWM_MODE	= 4,
	DA7280_OPMODE_MAX,
पूर्ण;

#घोषणा DA7280_FF_CONSTANT_DRO			1
#घोषणा DA7280_FF_PERIODIC_PWM			2
#घोषणा DA7280_FF_PERIODIC_RTWM			1
#घोषणा DA7280_FF_PERIODIC_ETWM			2

#घोषणा DA7280_FF_PERIODIC_MODE			DA7280_RTWM_MODE
#घोषणा DA7280_FF_CONSTANT_MODE			DA7280_DRO_MODE

क्रमागत da7280_custom_effect_param अणु
	DA7280_CUSTOM_SEQ_ID_IDX	= 0,
	DA7280_CUSTOM_SEQ_LOOP_IDX	= 1,
	DA7280_CUSTOM_DATA_LEN		= 2,
पूर्ण;

क्रमागत da7280_custom_gpi_effect_param अणु
	DA7280_CUSTOM_GPI_SEQ_ID_IDX	= 0,
	DA7280_CUSTOM_GPI_NUM_IDX	= 2,
	DA7280_CUSTOM_GP_DATA_LEN	= 3,
पूर्ण;

काष्ठा da7280_gpi_ctl अणु
	u8 seq_id;
	u8 mode;
	u8 polarity;
पूर्ण;

काष्ठा da7280_haptic अणु
	काष्ठा regmap *regmap;
	काष्ठा input_dev *input_dev;
	काष्ठा device *dev;
	काष्ठा i2c_client *client;
	काष्ठा pwm_device *pwm_dev;

	bool legacy;
	काष्ठा work_काष्ठा work;
	पूर्णांक val;
	u16 gain;
	s16 level;

	u8 dev_type;
	u8 op_mode;
	u8 स्थिर_op_mode;
	u8 periodic_op_mode;
	u16 nommax;
	u16 असलmax;
	u32 imax;
	u32 impd;
	u32 resonant_freq_h;
	u32 resonant_freq_l;
	bool bemf_sense_en;
	bool freq_track_en;
	bool acc_en;
	bool rapid_stop_en;
	bool amp_pid_en;
	u8 ps_seq_id;
	u8 ps_seq_loop;
	काष्ठा da7280_gpi_ctl gpi_ctl[3];
	bool mem_update;
	u8 snp_mem[DA7280_SNP_MEM_SIZE];
	bool active;
	bool suspended;
पूर्ण;

अटल bool da7280_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7280_IRQ_EVENT1:
	हाल DA7280_IRQ_EVENT_WARNING_DIAG:
	हाल DA7280_IRQ_EVENT_SEQ_DIAG:
	हाल DA7280_IRQ_STATUS1:
	हाल DA7280_TOP_CTL1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config da7280_haptic_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = DA7280_SNP_MEM_MAX,
	.अस्थिर_reg = da7280_अस्थिर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक da7280_haptic_mem_update(काष्ठा da7280_haptic *haptics)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक error;

	/* The patterns should be updated when haptic is not working */
	error = regmap_पढ़ो(haptics->regmap, DA7280_IRQ_STATUS1, &val);
	अगर (error)
		वापस error;
	अगर (val & DA7280_STA_WARNING_MASK) अणु
		dev_warn(haptics->dev,
			 "Warning! Please check HAPTIC status.\n");
		वापस -EBUSY;
	पूर्ण

	/* Patterns are not updated अगर the lock bit is enabled */
	val = 0;
	error = regmap_पढ़ो(haptics->regmap, DA7280_MEM_CTL2, &val);
	अगर (error)
		वापस error;
	अगर (~val & DA7280_WAV_MEM_LOCK_MASK) अणु
		dev_warn(haptics->dev, "Please unlock the bit first\n");
		वापस -EACCES;
	पूर्ण

	/* Set to Inactive mode to make sure safety */
	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CTL1,
				   DA7280_OPERATION_MODE_MASK,
				   0);
	अगर (error)
		वापस error;

	error = regmap_पढ़ो(haptics->regmap, DA7280_MEM_CTL1, &val);
	अगर (error)
		वापस error;

	वापस regmap_bulk_ग_लिखो(haptics->regmap, val, haptics->snp_mem,
				 DA7280_SNP_MEM_MAX - val + 1);
पूर्ण

अटल पूर्णांक da7280_haptic_set_pwm(काष्ठा da7280_haptic *haptics, bool enabled)
अणु
	काष्ठा pwm_state state;
	u64 period_mag_multi;
	पूर्णांक error;

	अगर (!haptics->gain && enabled) अणु
		dev_err(haptics->dev, "Unable to enable pwm with 0 gain\n");
		वापस -EINVAL;
	पूर्ण

	pwm_get_state(haptics->pwm_dev, &state);
	state.enabled = enabled;
	अगर (enabled) अणु
		period_mag_multi = (u64)state.period * haptics->gain;
		period_mag_multi >>= DA7280_MAX_MAGNITUDE_SHIFT;

		/*
		 * The पूर्णांकerpretation of duty cycle depends on the acc_en,
		 * it should be between 50% and 100% क्रम acc_en = 0.
		 * See datasheet 'PWM mode' section.
		 */
		अगर (!haptics->acc_en) अणु
			period_mag_multi += state.period;
			period_mag_multi /= 2;
		पूर्ण

		state.duty_cycle = period_mag_multi;
	पूर्ण

	error = pwm_apply_state(haptics->pwm_dev, &state);
	अगर (error)
		dev_err(haptics->dev, "Failed to apply pwm state: %d\n", error);

	वापस error;
पूर्ण

अटल व्योम da7280_haptic_activate(काष्ठा da7280_haptic *haptics)
अणु
	पूर्णांक error;

	अगर (haptics->active)
		वापस;

	चयन (haptics->op_mode) अणु
	हाल DA7280_DRO_MODE:
		/* the valid range check when acc_en is enabled */
		अगर (haptics->acc_en && haptics->level > 0x7F)
			haptics->level = 0x7F;
		अन्यथा अगर (haptics->level > 0xFF)
			haptics->level = 0xFF;

		/* Set level as a % of ACTUATOR_NOMMAX (nommax) */
		error = regmap_ग_लिखो(haptics->regmap, DA7280_TOP_CTL2,
				     haptics->level);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to set level to %d: %d\n",
				haptics->level, error);
			वापस;
		पूर्ण
		अवरोध;

	हाल DA7280_PWM_MODE:
		अगर (da7280_haptic_set_pwm(haptics, true))
			वापस;
		अवरोध;

	हाल DA7280_RTWM_MODE:
		/*
		 * The pattern will be played by the PS_SEQ_ID and the
		 * PS_SEQ_LOOP
		 */
		अवरोध;

	हाल DA7280_ETWM_MODE:
		/*
		 * The pattern will be played by the GPI[N] state,
		 * GPI(N)_SEQUENCE_ID and the PS_SEQ_LOOP. See the
		 * datasheet क्रम the details.
		 */
		अवरोध;

	शेष:
		dev_err(haptics->dev, "Invalid op mode %d\n", haptics->op_mode);
		वापस;
	पूर्ण

	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CTL1,
				   DA7280_OPERATION_MODE_MASK,
				   haptics->op_mode);
	अगर (error) अणु
		dev_err(haptics->dev,
			"Failed to set operation mode: %d", error);
		वापस;
	पूर्ण

	अगर (haptics->op_mode == DA7280_PWM_MODE ||
	    haptics->op_mode == DA7280_RTWM_MODE) अणु
		error = regmap_update_bits(haptics->regmap,
					   DA7280_TOP_CTL1,
					   DA7280_SEQ_START_MASK,
					   DA7280_SEQ_START_MASK);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to start sequence: %d\n", error);
			वापस;
		पूर्ण
	पूर्ण

	haptics->active = true;
पूर्ण

अटल व्योम da7280_haptic_deactivate(काष्ठा da7280_haptic *haptics)
अणु
	पूर्णांक error;

	अगर (!haptics->active)
		वापस;

	/* Set to Inactive mode */
	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CTL1,
				   DA7280_OPERATION_MODE_MASK, 0);
	अगर (error) अणु
		dev_err(haptics->dev,
			"Failed to clear operation mode: %d", error);
		वापस;
	पूर्ण

	चयन (haptics->op_mode) अणु
	हाल DA7280_DRO_MODE:
		error = regmap_ग_लिखो(haptics->regmap,
				     DA7280_TOP_CTL2, 0);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to disable DRO mode: %d\n", error);
			वापस;
		पूर्ण
		अवरोध;

	हाल DA7280_PWM_MODE:
		अगर (da7280_haptic_set_pwm(haptics, false))
			वापस;
		अवरोध;

	हाल DA7280_RTWM_MODE:
	हाल DA7280_ETWM_MODE:
		error = regmap_update_bits(haptics->regmap,
					   DA7280_TOP_CTL1,
					   DA7280_SEQ_START_MASK, 0);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to disable RTWM/ETWM mode: %d\n",
				error);
			वापस;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(haptics->dev, "Invalid op mode %d\n", haptics->op_mode);
		वापस;
	पूर्ण

	haptics->active = false;
पूर्ण

अटल व्योम da7280_haptic_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da7280_haptic *haptics =
		container_of(work, काष्ठा da7280_haptic, work);
	पूर्णांक val = haptics->val;

	अगर (val)
		da7280_haptic_activate(haptics);
	अन्यथा
		da7280_haptic_deactivate(haptics);
पूर्ण

अटल पूर्णांक da7280_haptics_upload_effect(काष्ठा input_dev *dev,
					काष्ठा ff_effect *effect,
					काष्ठा ff_effect *old)
अणु
	काष्ठा da7280_haptic *haptics = input_get_drvdata(dev);
	s16 data[DA7280_SNP_MEM_SIZE] = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक val;
	पूर्णांक पंचांगp, i, num;
	पूर्णांक error;

	/* The effect should be uploaded when haptic is not working */
	अगर (haptics->active)
		वापस -EBUSY;

	चयन (effect->type) अणु
	/* DRO/PWM modes support this type */
	हाल FF_CONSTANT:
		haptics->op_mode = haptics->स्थिर_op_mode;
		अगर (haptics->op_mode == DA7280_DRO_MODE) अणु
			पंचांगp = effect->u.स्थिरant.level * 254;
			haptics->level = पंचांगp / 0x7FFF;
			अवरोध;
		पूर्ण

		haptics->gain =	effect->u.स्थिरant.level <= 0 ?
					0 : effect->u.स्थिरant.level;
		अवरोध;

	/* RTWM/ETWM modes support this type */
	हाल FF_PERIODIC:
		अगर (effect->u.periodic.waveक्रमm != FF_CUSTOM) अणु
			dev_err(haptics->dev,
				"Device can only accept FF_CUSTOM waveform\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * Load the data and check the length.
		 * the data will be patterns in this हाल: 4 < X <= 100,
		 * and will be saved पूर्णांकo the waveक्रमm memory inside DA728x.
		 * If X = 2, the data will be PS_SEQ_ID and PS_SEQ_LOOP.
		 * If X = 3, the 1st data will be GPIX_SEQUENCE_ID .
		 */
		अगर (effect->u.periodic.custom_len == DA7280_CUSTOM_DATA_LEN)
			जाओ set_seq_id_loop;

		अगर (effect->u.periodic.custom_len == DA7280_CUSTOM_GP_DATA_LEN)
			जाओ set_gpix_seq_id;

		अगर (effect->u.periodic.custom_len < DA7280_CUSTOM_DATA_LEN ||
		    effect->u.periodic.custom_len > DA7280_SNP_MEM_SIZE) अणु
			dev_err(haptics->dev, "Invalid waveform data size\n");
			वापस -EINVAL;
		पूर्ण

		अगर (copy_from_user(data, effect->u.periodic.custom_data,
				   माप(s16) *
				   effect->u.periodic.custom_len))
			वापस -EFAULT;

		स_रखो(haptics->snp_mem, 0, DA7280_SNP_MEM_SIZE);

		क्रम (i = 0; i < effect->u.periodic.custom_len; i++) अणु
			अगर (data[i] < 0 || data[i] > 0xff) अणु
				dev_err(haptics->dev,
					"Invalid waveform data %d at offset %d\n",
					data[i], i);
				वापस -EINVAL;
			पूर्ण
			haptics->snp_mem[i] = (u8)data[i];
		पूर्ण

		error = da7280_haptic_mem_update(haptics);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to upload waveform: %d\n", error);
			वापस error;
		पूर्ण
		अवरोध;

set_seq_id_loop:
		अगर (copy_from_user(data, effect->u.periodic.custom_data,
				   माप(s16) * DA7280_CUSTOM_DATA_LEN))
			वापस -EFAULT;

		अगर (data[DA7280_CUSTOM_SEQ_ID_IDX] < 0 ||
		    data[DA7280_CUSTOM_SEQ_ID_IDX] > DA7280_SEQ_ID_MAX ||
		    data[DA7280_CUSTOM_SEQ_LOOP_IDX] < 0 ||
		    data[DA7280_CUSTOM_SEQ_LOOP_IDX] > DA7280_SEQ_LOOP_MAX) अणु
			dev_err(haptics->dev,
				"Invalid custom id (%d) or loop (%d)\n",
				data[DA7280_CUSTOM_SEQ_ID_IDX],
				data[DA7280_CUSTOM_SEQ_LOOP_IDX]);
			वापस -EINVAL;
		पूर्ण

		haptics->ps_seq_id = data[DA7280_CUSTOM_SEQ_ID_IDX] & 0x0f;
		haptics->ps_seq_loop = data[DA7280_CUSTOM_SEQ_LOOP_IDX] & 0x0f;
		haptics->op_mode = haptics->periodic_op_mode;

		val = FIELD_PREP(DA7280_PS_SEQ_ID_MASK, haptics->ps_seq_id) |
			FIELD_PREP(DA7280_PS_SEQ_LOOP_MASK,
				   haptics->ps_seq_loop);
		error = regmap_ग_लिखो(haptics->regmap, DA7280_SEQ_CTL2, val);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to update PS sequence: %d\n", error);
			वापस error;
		पूर्ण
		अवरोध;

set_gpix_seq_id:
		अगर (copy_from_user(data, effect->u.periodic.custom_data,
				   माप(s16) * DA7280_CUSTOM_GP_DATA_LEN))
			वापस -EFAULT;

		अगर (data[DA7280_CUSTOM_GPI_SEQ_ID_IDX] < 0 ||
		    data[DA7280_CUSTOM_GPI_SEQ_ID_IDX] > DA7280_SEQ_ID_MAX ||
		    data[DA7280_CUSTOM_GPI_NUM_IDX] < 0 ||
		    data[DA7280_CUSTOM_GPI_NUM_IDX] > DA7280_GPI_SEQ_ID_MAX) अणु
			dev_err(haptics->dev,
				"Invalid custom GPI id (%d) or num (%d)\n",
				data[DA7280_CUSTOM_GPI_SEQ_ID_IDX],
				data[DA7280_CUSTOM_GPI_NUM_IDX]);
			वापस -EINVAL;
		पूर्ण

		num = data[DA7280_CUSTOM_GPI_NUM_IDX] & 0x0f;
		haptics->gpi_ctl[num].seq_id =
			data[DA7280_CUSTOM_GPI_SEQ_ID_IDX] & 0x0f;
		haptics->op_mode = haptics->periodic_op_mode;

		val = FIELD_PREP(DA7280_GPI0_SEQUENCE_ID_MASK,
				 haptics->gpi_ctl[num].seq_id);
		error = regmap_update_bits(haptics->regmap,
					   DA7280_GPI_0_CTL + num,
					   DA7280_GPI0_SEQUENCE_ID_MASK,
					   val);
		अगर (error) अणु
			dev_err(haptics->dev,
				"Failed to update GPI sequence: %d\n", error);
			वापस error;
		पूर्ण
		अवरोध;

	शेष:
		dev_err(haptics->dev, "Unsupported effect type: %d\n",
			effect->type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7280_haptics_playback(काष्ठा input_dev *dev,
				   पूर्णांक effect_id, पूर्णांक val)
अणु
	काष्ठा da7280_haptic *haptics = input_get_drvdata(dev);

	अगर (!haptics->op_mode) अणु
		dev_warn(haptics->dev, "No effects have been uploaded\n");
		वापस -EINVAL;
	पूर्ण

	अगर (likely(!haptics->suspended)) अणु
		haptics->val = val;
		schedule_work(&haptics->work);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da7280_haptic_start(काष्ठा da7280_haptic *haptics)
अणु
	पूर्णांक error;

	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CTL1,
				   DA7280_STANDBY_EN_MASK,
				   DA7280_STANDBY_EN_MASK);
	अगर (error) अणु
		dev_err(haptics->dev, "Unable to enable device: %d\n", error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम da7280_haptic_stop(काष्ठा da7280_haptic *haptics)
अणु
	पूर्णांक error;

	cancel_work_sync(&haptics->work);


	da7280_haptic_deactivate(haptics);

	error = regmap_update_bits(haptics->regmap, DA7280_TOP_CTL1,
				   DA7280_STANDBY_EN_MASK, 0);
	अगर (error)
		dev_err(haptics->dev, "Failed to disable device: %d\n", error);
पूर्ण

अटल पूर्णांक da7280_haptic_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा da7280_haptic *haptics = input_get_drvdata(dev);

	वापस da7280_haptic_start(haptics);
पूर्ण

अटल व्योम da7280_haptic_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा da7280_haptic *haptics = input_get_drvdata(dev);

	da7280_haptic_stop(haptics);
पूर्ण

अटल u8 da7280_haptic_of_mode_str(काष्ठा device *dev,
				    स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "LRA")) अणु
		वापस DA7280_LRA;
	पूर्ण अन्यथा अगर (!म_भेद(str, "ERM-bar")) अणु
		वापस DA7280_ERM_BAR;
	पूर्ण अन्यथा अगर (!म_भेद(str, "ERM-coin")) अणु
		वापस DA7280_ERM_COIN;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Invalid string - set to LRA\n");
		वापस DA7280_LRA;
	पूर्ण
पूर्ण

अटल u8 da7280_haptic_of_gpi_mode_str(काष्ठा device *dev,
					स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "Single-pattern")) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (!म_भेद(str, "Multi-pattern")) अणु
		वापस 1;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Invalid string - set to Single-pattern\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 da7280_haptic_of_gpi_pol_str(काष्ठा device *dev,
				       स्थिर अक्षर *str)
अणु
	अगर (!म_भेद(str, "Rising-edge")) अणु
		वापस 0;
	पूर्ण अन्यथा अगर (!म_भेद(str, "Falling-edge")) अणु
		वापस 1;
	पूर्ण अन्यथा अगर (!म_भेद(str, "Both-edge")) अणु
		वापस 2;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Invalid string - set to Rising-edge\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल u8 da7280_haptic_of_volt_rating_set(u32 val)
अणु
	u32 voltage = val / DA7280_VOLTAGE_RATE_STEP + 1;

	वापस min_t(u32, voltage, 0xff);
पूर्ण

अटल व्योम da7280_parse_properties(काष्ठा device *dev,
				    काष्ठा da7280_haptic *haptics)
अणु
	अचिन्हित पूर्णांक i, mem[DA7280_SNP_MEM_SIZE];
	अक्षर gpi_str1[] = "dlg,gpi0-seq-id";
	अक्षर gpi_str2[] = "dlg,gpi0-mode";
	अक्षर gpi_str3[] = "dlg,gpi0-polarity";
	स्थिर अक्षर *str;
	u32 val;
	पूर्णांक error;

	/*
	 * If there is no property, then use the mode programmed पूर्णांकo the chip.
	 */
	haptics->dev_type = DA7280_DEV_MAX;
	error = device_property_पढ़ो_string(dev, "dlg,actuator-type", &str);
	अगर (!error)
		haptics->dev_type = da7280_haptic_of_mode_str(dev, str);

	haptics->स्थिर_op_mode = DA7280_DRO_MODE;
	error = device_property_पढ़ो_u32(dev, "dlg,const-op-mode", &val);
	अगर (!error && val == DA7280_FF_PERIODIC_PWM)
		haptics->स्थिर_op_mode = DA7280_PWM_MODE;

	haptics->periodic_op_mode = DA7280_RTWM_MODE;
	error = device_property_पढ़ो_u32(dev, "dlg,periodic-op-mode", &val);
	अगर (!error && val == DA7280_FF_PERIODIC_ETWM)
		haptics->periodic_op_mode = DA7280_ETWM_MODE;

	haptics->nommax = DA7280_SKIP_INIT;
	error = device_property_पढ़ो_u32(dev, "dlg,nom-microvolt", &val);
	अगर (!error && val < DA7280_VOLTAGE_RATE_MAX)
		haptics->nommax = da7280_haptic_of_volt_rating_set(val);

	haptics->असलmax = DA7280_SKIP_INIT;
	error = device_property_पढ़ो_u32(dev, "dlg,abs-max-microvolt", &val);
	अगर (!error && val < DA7280_VOLTAGE_RATE_MAX)
		haptics->असलmax = da7280_haptic_of_volt_rating_set(val);

	haptics->imax = DA7280_IMAX_DEFAULT;
	error = device_property_पढ़ो_u32(dev, "dlg,imax-microamp", &val);
	अगर (!error && val < DA7280_IMAX_LIMIT)
		haptics->imax = (val - 28600) / DA7280_IMAX_STEP + 1;

	haptics->impd = DA7280_IMPD_DEFAULT;
	error = device_property_पढ़ो_u32(dev, "dlg,impd-micro-ohms", &val);
	अगर (!error && val <= DA7280_IMPD_MAX)
		haptics->impd = val;

	haptics->resonant_freq_h = DA7280_SKIP_INIT;
	haptics->resonant_freq_l = DA7280_SKIP_INIT;
	error = device_property_पढ़ो_u32(dev, "dlg,resonant-freq-hz", &val);
	अगर (!error) अणु
		अगर (val < DA7280_MAX_RESONAT_FREQ_HZ &&
		    val > DA7280_MIN_RESONAT_FREQ_HZ) अणु
			haptics->resonant_freq_h =
				((1000000000 / (val * 1333)) >> 7) & 0xFF;
			haptics->resonant_freq_l =
				(1000000000 / (val * 1333)) & 0x7F;
		पूर्ण अन्यथा अणु
			haptics->resonant_freq_h = DA7280_RESONT_FREQH_DFT;
			haptics->resonant_freq_l = DA7280_RESONT_FREQL_DFT;
		पूर्ण
	पूर्ण

	/* If no property, set to zero as शेष is to करो nothing. */
	haptics->ps_seq_id = 0;
	error = device_property_पढ़ो_u32(dev, "dlg,ps-seq-id", &val);
	अगर (!error && val <= DA7280_SEQ_ID_MAX)
		haptics->ps_seq_id = val;

	haptics->ps_seq_loop = 0;
	error = device_property_पढ़ो_u32(dev, "dlg,ps-seq-loop", &val);
	अगर (!error && val <= DA7280_SEQ_LOOP_MAX)
		haptics->ps_seq_loop = val;

	/* GPI0~2 Control */
	क्रम (i = 0; i <= DA7280_GPI_SEQ_ID_MAX; i++) अणु
		gpi_str1[7] = '0' + i;
		haptics->gpi_ctl[i].seq_id = DA7280_GPI_SEQ_ID_DFT + i;
		error = device_property_पढ़ो_u32 (dev, gpi_str1, &val);
		अगर (!error && val <= DA7280_SEQ_ID_MAX)
			haptics->gpi_ctl[i].seq_id = val;

		gpi_str2[7] = '0' + i;
		haptics->gpi_ctl[i].mode = 0;
		error = device_property_पढ़ो_string(dev, gpi_str2, &str);
		अगर (!error)
			haptics->gpi_ctl[i].mode =
				da7280_haptic_of_gpi_mode_str(dev, str);

		gpi_str3[7] = '0' + i;
		haptics->gpi_ctl[i].polarity = 0;
		error = device_property_पढ़ो_string(dev, gpi_str3, &str);
		अगर (!error)
			haptics->gpi_ctl[i].polarity =
				da7280_haptic_of_gpi_pol_str(dev, str);
	पूर्ण

	haptics->bemf_sense_en =
		device_property_पढ़ो_bool(dev, "dlg,bemf-sens-enable");
	haptics->freq_track_en =
		device_property_पढ़ो_bool(dev, "dlg,freq-track-enable");
	haptics->acc_en =
		device_property_पढ़ो_bool(dev, "dlg,acc-enable");
	haptics->rapid_stop_en =
		device_property_पढ़ो_bool(dev, "dlg,rapid-stop-enable");
	haptics->amp_pid_en =
		device_property_पढ़ो_bool(dev, "dlg,amp-pid-enable");

	haptics->mem_update = false;
	error = device_property_पढ़ो_u32_array(dev, "dlg,mem-array",
					       &mem[0], DA7280_SNP_MEM_SIZE);
	अगर (!error) अणु
		haptics->mem_update = true;
		स_रखो(haptics->snp_mem, 0, DA7280_SNP_MEM_SIZE);
		क्रम (i = 0; i < DA7280_SNP_MEM_SIZE; i++) अणु
			अगर (mem[i] <= 0xff) अणु
				haptics->snp_mem[i] = (u8)mem[i];
			पूर्ण अन्यथा अणु
				dev_err(haptics->dev,
					"Invalid data in mem-array at %d: %x\n",
					i, mem[i]);
				haptics->mem_update = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t da7280_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da7280_haptic *haptics = data;
	काष्ठा device *dev = haptics->dev;
	u8 events[DA7280_IRQ_NUM];
	पूर्णांक error;

	/* Check what events have happened */
	error = regmap_bulk_पढ़ो(haptics->regmap, DA7280_IRQ_EVENT1,
				 events, माप(events));
	अगर (error) अणु
		dev_err(dev, "failed to read interrupt data: %d\n", error);
		जाओ out;
	पूर्ण

	/* Clear events */
	error = regmap_ग_लिखो(haptics->regmap, DA7280_IRQ_EVENT1, events[0]);
	अगर (error) अणु
		dev_err(dev, "failed to clear interrupts: %d\n", error);
		जाओ out;
	पूर्ण

	अगर (events[0] & DA7280_E_SEQ_FAULT_MASK) अणु
		/*
		 * Stop first अगर haptic is active, otherwise, the fault may
		 * happen continually even though the bit is cleared.
		 */
		error = regmap_update_bits(haptics->regmap, DA7280_TOP_CTL1,
					   DA7280_OPERATION_MODE_MASK, 0);
		अगर (error)
			dev_err(dev, "failed to clear op mode on fault: %d\n",
				error);
	पूर्ण

	अगर (events[0] & DA7280_E_SEQ_DONE_MASK)
		haptics->active = false;

	अगर (events[0] & DA7280_E_WARNING_MASK) अणु
		अगर (events[1] & DA7280_E_LIM_DRIVE_MASK ||
		    events[1] & DA7280_E_LIM_DRIVE_ACC_MASK)
			dev_warn(dev, "Please reduce the driver level\n");
		अगर (events[1] & DA7280_E_MEM_TYPE_MASK)
			dev_warn(dev, "Please check the mem data format\n");
		अगर (events[1] & DA7280_E_OVERTEMP_WARN_MASK)
			dev_warn(dev, "Over-temperature warning\n");
	पूर्ण

	अगर (events[0] & DA7280_E_SEQ_FAULT_MASK) अणु
		अगर (events[2] & DA7280_E_SEQ_ID_FAULT_MASK)
			dev_info(dev, "Please reload PS_SEQ_ID & mem data\n");
		अगर (events[2] & DA7280_E_MEM_FAULT_MASK)
			dev_info(dev, "Please reload the mem data\n");
		अगर (events[2] & DA7280_E_PWM_FAULT_MASK)
			dev_info(dev, "Please restart PWM interface\n");
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da7280_init(काष्ठा da7280_haptic *haptics)
अणु
	अचिन्हित पूर्णांक val = 0;
	u32 v2i_factor;
	पूर्णांक error, i;
	u8 mask = 0;

	/*
	 * If device type is DA7280_DEV_MAX then simply use currently
	 * programmed mode.
	 */
	अगर (haptics->dev_type == DA7280_DEV_MAX) अणु
		error = regmap_पढ़ो(haptics->regmap, DA7280_TOP_CFG1, &val);
		अगर (error)
			जाओ out_err;

		haptics->dev_type = val & DA7280_ACTUATOR_TYPE_MASK ?
					DA7280_ERM_COIN : DA7280_LRA;
	पूर्ण

	/* Apply user settings */
	अगर (haptics->dev_type == DA7280_LRA &&
	    haptics->resonant_freq_l != DA7280_SKIP_INIT) अणु
		error = regmap_ग_लिखो(haptics->regmap, DA7280_FRQ_LRA_PER_H,
				     haptics->resonant_freq_h);
		अगर (error)
			जाओ out_err;
		error = regmap_ग_लिखो(haptics->regmap, DA7280_FRQ_LRA_PER_L,
				     haptics->resonant_freq_l);
		अगर (error)
			जाओ out_err;
	पूर्ण अन्यथा अगर (haptics->dev_type == DA7280_ERM_COIN) अणु
		error = regmap_update_bits(haptics->regmap, DA7280_TOP_INT_CFG1,
					   DA7280_BEMF_FAULT_LIM_MASK, 0);
		अगर (error)
			जाओ out_err;

		mask = DA7280_TST_CALIB_IMPEDANCE_DIS_MASK |
			DA7280_V2I_FACTOR_FREEZE_MASK;
		val = DA7280_TST_CALIB_IMPEDANCE_DIS_MASK |
			DA7280_V2I_FACTOR_FREEZE_MASK;
		error = regmap_update_bits(haptics->regmap, DA7280_TOP_CFG4,
					   mask, val);
		अगर (error)
			जाओ out_err;

		haptics->acc_en = false;
		haptics->rapid_stop_en = false;
		haptics->amp_pid_en = false;
	पूर्ण

	mask = DA7280_ACTUATOR_TYPE_MASK |
			DA7280_BEMF_SENSE_EN_MASK |
			DA7280_FREQ_TRACK_EN_MASK |
			DA7280_ACCELERATION_EN_MASK |
			DA7280_RAPID_STOP_EN_MASK |
			DA7280_AMP_PID_EN_MASK;
	val = FIELD_PREP(DA7280_ACTUATOR_TYPE_MASK,
			 (haptics->dev_type ? 1 : 0)) |
		FIELD_PREP(DA7280_BEMF_SENSE_EN_MASK,
			   (haptics->bemf_sense_en ? 1 : 0)) |
		FIELD_PREP(DA7280_FREQ_TRACK_EN_MASK,
			   (haptics->freq_track_en ? 1 : 0)) |
		FIELD_PREP(DA7280_ACCELERATION_EN_MASK,
			   (haptics->acc_en ? 1 : 0)) |
		FIELD_PREP(DA7280_RAPID_STOP_EN_MASK,
			   (haptics->rapid_stop_en ? 1 : 0)) |
		FIELD_PREP(DA7280_AMP_PID_EN_MASK,
			   (haptics->amp_pid_en ? 1 : 0));

	error = regmap_update_bits(haptics->regmap, DA7280_TOP_CFG1, mask, val);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(haptics->regmap, DA7280_TOP_CFG5,
				   DA7280_V2I_FACTOR_OFFSET_EN_MASK,
				   haptics->acc_en ?
					DA7280_V2I_FACTOR_OFFSET_EN_MASK : 0);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CFG2,
				   DA7280_MEM_DATA_SIGNED_MASK,
				   haptics->acc_en ?
					0 : DA7280_MEM_DATA_SIGNED_MASK);
	अगर (error)
		जाओ out_err;

	अगर (haptics->nommax != DA7280_SKIP_INIT) अणु
		error = regmap_ग_लिखो(haptics->regmap, DA7280_ACTUATOR1,
				     haptics->nommax);
		अगर (error)
			जाओ out_err;
	पूर्ण

	अगर (haptics->असलmax != DA7280_SKIP_INIT) अणु
		error = regmap_ग_लिखो(haptics->regmap, DA7280_ACTUATOR2,
				     haptics->असलmax);
		अगर (error)
			जाओ out_err;
	पूर्ण

	error = regmap_update_bits(haptics->regmap, DA7280_ACTUATOR3,
				   DA7280_IMAX_MASK, haptics->imax);
	अगर (error)
		जाओ out_err;

	v2i_factor = haptics->impd * (haptics->imax + 4) / 1610400;
	error = regmap_ग_लिखो(haptics->regmap, DA7280_CALIB_V2I_L,
			     v2i_factor & 0xff);
	अगर (error)
		जाओ out_err;
	error = regmap_ग_लिखो(haptics->regmap, DA7280_CALIB_V2I_H,
			     v2i_factor >> 8);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(haptics->regmap,
				   DA7280_TOP_CTL1,
				   DA7280_STANDBY_EN_MASK,
				   DA7280_STANDBY_EN_MASK);
	अगर (error)
		जाओ out_err;

	अगर (haptics->mem_update) अणु
		error = da7280_haptic_mem_update(haptics);
		अगर (error)
			जाओ out_err;
	पूर्ण

	/* Set  PS_SEQ_ID and PS_SEQ_LOOP */
	val = FIELD_PREP(DA7280_PS_SEQ_ID_MASK, haptics->ps_seq_id) |
		FIELD_PREP(DA7280_PS_SEQ_LOOP_MASK, haptics->ps_seq_loop);
	error = regmap_ग_लिखो(haptics->regmap, DA7280_SEQ_CTL2, val);
	अगर (error)
		जाओ out_err;

	/* GPI(N) CTL */
	क्रम (i = 0; i < 3; i++) अणु
		val = FIELD_PREP(DA7280_GPI0_SEQUENCE_ID_MASK,
				 haptics->gpi_ctl[i].seq_id) |
			FIELD_PREP(DA7280_GPI0_MODE_MASK,
				   haptics->gpi_ctl[i].mode) |
			FIELD_PREP(DA7280_GPI0_POLARITY_MASK,
				   haptics->gpi_ctl[i].polarity);
		error = regmap_ग_लिखो(haptics->regmap,
				     DA7280_GPI_0_CTL + i, val);
		अगर (error)
			जाओ out_err;
	पूर्ण

	/* Mask ADC_SAT_M bit as शेष */
	error = regmap_update_bits(haptics->regmap,
				   DA7280_IRQ_MASK2,
				   DA7280_ADC_SAT_M_MASK,
				   DA7280_ADC_SAT_M_MASK);
	अगर (error)
		जाओ out_err;

	/* Clear Interrupts */
	error = regmap_ग_लिखो(haptics->regmap, DA7280_IRQ_EVENT1, 0xff);
	अगर (error)
		जाओ out_err;

	error = regmap_update_bits(haptics->regmap,
				   DA7280_IRQ_MASK1,
				   DA7280_SEQ_FAULT_M_MASK |
					DA7280_SEQ_DONE_M_MASK,
				   0);
	अगर (error)
		जाओ out_err;

	haptics->active = false;
	वापस 0;

out_err:
	dev_err(haptics->dev, "chip initialization error: %d\n", error);
	वापस error;
पूर्ण

अटल पूर्णांक da7280_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा da7280_haptic *haptics;
	काष्ठा input_dev *input_dev;
	काष्ठा pwm_state state;
	काष्ठा ff_device *ff;
	पूर्णांक error;

	अगर (!client->irq) अणु
		dev_err(dev, "No IRQ configured\n");
		वापस -EINVAL;
	पूर्ण

	haptics = devm_kzalloc(dev, माप(*haptics), GFP_KERNEL);
	अगर (!haptics)
		वापस -ENOMEM;

	haptics->dev = dev;

	da7280_parse_properties(dev, haptics);

	अगर (haptics->स्थिर_op_mode == DA7280_PWM_MODE) अणु
		haptics->pwm_dev = devm_pwm_get(dev, शून्य);
		error = PTR_ERR_OR_ZERO(haptics->pwm_dev);
		अगर (error) अणु
			अगर (error != -EPROBE_DEFER)
				dev_err(dev, "Unable to request PWM: %d\n",
					error);
			वापस error;
		पूर्ण

		/* Sync up PWM state and ensure it is off. */
		pwm_init_state(haptics->pwm_dev, &state);
		state.enabled = false;
		error = pwm_apply_state(haptics->pwm_dev, &state);
		अगर (error) अणु
			dev_err(dev, "Failed to apply PWM state: %d\n", error);
			वापस error;
		पूर्ण

		/*
		 * Check PWM period, PWM freq = 1000000 / state.period.
		 * The valid PWM freq range: 10k ~ 250kHz.
		 */
		अगर (state.period > 100000 || state.period < 4000) अणु
			dev_err(dev, "Unsupported PWM period: %lld\n",
				state.period);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	INIT_WORK(&haptics->work, da7280_haptic_work);

	haptics->client = client;
	i2c_set_clientdata(client, haptics);

	haptics->regmap = devm_regmap_init_i2c(client,
					       &da7280_haptic_regmap_config);
	error = PTR_ERR_OR_ZERO(haptics->regmap);
	अगर (error) अणु
		dev_err(dev, "Failed to allocate register map: %d\n", error);
		वापस error;
	पूर्ण

	error = da7280_init(haptics);
	अगर (error) अणु
		dev_err(dev, "Failed to initialize device: %d\n", error);
		वापस error;
	पूर्ण

	/* Initialize input device क्रम haptic device */
	input_dev = devm_input_allocate_device(dev);
	अगर (!input_dev) अणु
		dev_err(dev, "Failed to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = "da7280-haptic";
	input_dev->dev.parent = client->dev.parent;
	input_dev->खोलो = da7280_haptic_खोलो;
	input_dev->बंद = da7280_haptic_बंद;
	input_set_drvdata(input_dev, haptics);
	haptics->input_dev = input_dev;

	input_set_capability(haptics->input_dev, EV_FF, FF_PERIODIC);
	input_set_capability(haptics->input_dev, EV_FF, FF_CUSTOM);
	input_set_capability(haptics->input_dev, EV_FF, FF_CONSTANT);
	input_set_capability(haptics->input_dev, EV_FF, FF_GAIN);

	error = input_ff_create(haptics->input_dev,
				DA7280_FF_EFFECT_COUNT_MAX);
	अगर (error) अणु
		dev_err(dev, "Failed to create FF input device: %d\n", error);
		वापस error;
	पूर्ण

	ff = input_dev->ff;
	ff->upload = da7280_haptics_upload_effect;
	ff->playback = da7280_haptics_playback;

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(dev, "Failed to register input device: %d\n", error);
		वापस error;
	पूर्ण

	error = devm_request_thपढ़ोed_irq(dev, client->irq,
					  शून्य, da7280_irq_handler,
					  IRQF_ONESHOT,
					  "da7280-haptics", haptics);
	अगर (error) अणु
		dev_err(dev, "Failed to request IRQ %d: %d\n",
			client->irq, error);
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused da7280_suspend(काष्ठा device *dev)
अणु
	काष्ठा da7280_haptic *haptics = dev_get_drvdata(dev);

	mutex_lock(&haptics->input_dev->mutex);

	/*
	 * Make sure no new requests will be submitted जबतक device is
	 * suspended.
	 */
	spin_lock_irq(&haptics->input_dev->event_lock);
	haptics->suspended = true;
	spin_unlock_irq(&haptics->input_dev->event_lock);

	da7280_haptic_stop(haptics);

	mutex_unlock(&haptics->input_dev->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused da7280_resume(काष्ठा device *dev)
अणु
	काष्ठा da7280_haptic *haptics = dev_get_drvdata(dev);
	पूर्णांक retval;

	mutex_lock(&haptics->input_dev->mutex);

	retval = da7280_haptic_start(haptics);
	अगर (!retval) अणु
		spin_lock_irq(&haptics->input_dev->event_lock);
		haptics->suspended = false;
		spin_unlock_irq(&haptics->input_dev->event_lock);
	पूर्ण

	mutex_unlock(&haptics->input_dev->mutex);
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da7280_of_match[] = अणु
	अणु .compatible = "dlg,da7280", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da7280_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id da7280_i2c_id[] = अणु
	अणु "da7280", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da7280_i2c_id);

अटल SIMPLE_DEV_PM_OPS(da7280_pm_ops, da7280_suspend, da7280_resume);

अटल काष्ठा i2c_driver da7280_driver = अणु
	.driver = अणु
		.name = "da7280",
		.of_match_table = of_match_ptr(da7280_of_match),
		.pm = &da7280_pm_ops,
	पूर्ण,
	.probe = da7280_probe,
	.id_table = da7280_i2c_id,
पूर्ण;
module_i2c_driver(da7280_driver);

MODULE_DESCRIPTION("DA7280 haptics driver");
MODULE_AUTHOR("Roy Im <Roy.Im.Opensource@diasemi.com>");
MODULE_LICENSE("GPL");
