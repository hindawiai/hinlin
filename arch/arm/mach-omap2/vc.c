<शैली गुरु>
/*
 * OMAP Voltage Controller (VC) पूर्णांकerface
 *
 * Copyright (C) 2011 Texas Instruments, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/भाग64.h>

#समावेश "iomap.h"
#समावेश "soc.h"
#समावेश "voltage.h"
#समावेश "vc.h"
#समावेश "prm-regbits-34xx.h"
#समावेश "prm-regbits-44xx.h"
#समावेश "prm44xx.h"
#समावेश "pm.h"
#समावेश "scrm44xx.h"
#समावेश "control.h"

#घोषणा OMAP4430_VDD_IVA_I2C_DISABLE		BIT(14)
#घोषणा OMAP4430_VDD_MPU_I2C_DISABLE		BIT(13)
#घोषणा OMAP4430_VDD_CORE_I2C_DISABLE		BIT(12)
#घोषणा OMAP4430_VDD_IVA_PRESENCE		BIT(9)
#घोषणा OMAP4430_VDD_MPU_PRESENCE		BIT(8)
#घोषणा OMAP4430_AUTO_CTRL_VDD_IVA(x)		((x) << 4)
#घोषणा OMAP4430_AUTO_CTRL_VDD_MPU(x)		((x) << 2)
#घोषणा OMAP4430_AUTO_CTRL_VDD_CORE(x)		((x) << 0)
#घोषणा OMAP4430_AUTO_CTRL_VDD_RET		2

#घोषणा OMAP4430_VDD_I2C_DISABLE_MASK	\
	(OMAP4430_VDD_IVA_I2C_DISABLE | \
	 OMAP4430_VDD_MPU_I2C_DISABLE | \
	 OMAP4430_VDD_CORE_I2C_DISABLE)

#घोषणा OMAP4_VDD_DEFAULT_VAL	\
	(OMAP4430_VDD_I2C_DISABLE_MASK | \
	 OMAP4430_VDD_IVA_PRESENCE | OMAP4430_VDD_MPU_PRESENCE | \
	 OMAP4430_AUTO_CTRL_VDD_IVA(OMAP4430_AUTO_CTRL_VDD_RET) | \
	 OMAP4430_AUTO_CTRL_VDD_MPU(OMAP4430_AUTO_CTRL_VDD_RET) | \
	 OMAP4430_AUTO_CTRL_VDD_CORE(OMAP4430_AUTO_CTRL_VDD_RET))

#घोषणा OMAP4_VDD_RET_VAL	\
	(OMAP4_VDD_DEFAULT_VAL & ~OMAP4430_VDD_I2C_DISABLE_MASK)

/**
 * काष्ठा omap_vc_channel_cfg - describe the cfg_channel bitfield
 * @sa: bit क्रम slave address
 * @rav: bit क्रम voltage configuration रेजिस्टर
 * @rac: bit क्रम command configuration रेजिस्टर
 * @racen: enable bit क्रम RAC
 * @cmd: bit क्रम command value set selection
 *
 * Channel configuration bits, common क्रम OMAP3+
 * OMAP3 रेजिस्टर: PRM_VC_CH_CONF
 * OMAP4 रेजिस्टर: PRM_VC_CFG_CHANNEL
 * OMAP5 रेजिस्टर: PRM_VC_SMPS_<voltdm>_CONFIG
 */
काष्ठा omap_vc_channel_cfg अणु
	u8 sa;
	u8 rav;
	u8 rac;
	u8 racen;
	u8 cmd;
पूर्ण;

अटल काष्ठा omap_vc_channel_cfg vc_शेष_channel_cfg = अणु
	.sa    = BIT(0),
	.rav   = BIT(1),
	.rac   = BIT(2),
	.racen = BIT(3),
	.cmd   = BIT(4),
पूर्ण;

/*
 * On OMAP3+, all VC channels have the above शेष bitfield
 * configuration, except the OMAP4 MPU channel.  This appears
 * to be a freak accident as every other VC channel has the
 * शेष configuration, thus creating a mutant channel config.
 */
अटल काष्ठा omap_vc_channel_cfg vc_mutant_channel_cfg = अणु
	.sa    = BIT(0),
	.rav   = BIT(2),
	.rac   = BIT(3),
	.racen = BIT(4),
	.cmd   = BIT(1),
पूर्ण;

अटल काष्ठा omap_vc_channel_cfg *vc_cfg_bits;

/* Default I2C trace length on pcb, 6.3cm. Used क्रम capacitance calculations. */
अटल u32 sr_i2c_pcb_length = 63;
#घोषणा CFG_CHANNEL_MASK 0x1f

/**
 * omap_vc_config_channel - configure VC channel to PMIC mappings
 * @voltdm: poपूर्णांकer to voltagकरोमुख्य defining the desired VC channel
 *
 * Configures the VC channel to PMIC mappings क्रम the following
 * PMIC settings
 * - i2c slave address (SA)
 * - voltage configuration address (RAV)
 * - command configuration address (RAC) and enable bit (RACEN)
 * - command values क्रम ON, ONLP, RET and OFF (CMD)
 *
 * This function currently only allows flexible configuration of the
 * non-शेष channel.  Starting with OMAP4, there are more than 2
 * channels, with one defined as the शेष (on OMAP4, it's MPU.)
 * Only the non-शेष channel can be configured.
 */
अटल पूर्णांक omap_vc_config_channel(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vc_channel *vc = voltdm->vc;

	/*
	 * For शेष channel, the only configurable bit is RACEN.
	 * All others must stay at zero (see function comment above.)
	 */
	अगर (vc->flags & OMAP_VC_CHANNEL_DEFAULT)
		vc->cfg_channel &= vc_cfg_bits->racen;

	voltdm->rmw(CFG_CHANNEL_MASK << vc->cfg_channel_sa_shअगरt,
		    vc->cfg_channel << vc->cfg_channel_sa_shअगरt,
		    vc->cfg_channel_reg);

	वापस 0;
पूर्ण

/* Voltage scale and accessory APIs */
पूर्णांक omap_vc_pre_scale(काष्ठा voltageकरोमुख्य *voltdm,
		      अचिन्हित दीर्घ target_volt,
		      u8 *target_vsel, u8 *current_vsel)
अणु
	काष्ठा omap_vc_channel *vc = voltdm->vc;
	u32 vc_cmdval;

	/* Check अगर sufficient pmic info is available क्रम this vdd */
	अगर (!voltdm->pmic) अणु
		pr_err("%s: Insufficient pmic info to scale the vdd_%s\n",
			__func__, voltdm->name);
		वापस -EINVAL;
	पूर्ण

	अगर (!voltdm->pmic->uv_to_vsel) अणु
		pr_err("%s: PMIC function to convert voltage in uV to vsel not registered. Hence unable to scale voltage for vdd_%s\n",
		       __func__, voltdm->name);
		वापस -ENODATA;
	पूर्ण

	अगर (!voltdm->पढ़ो || !voltdm->ग_लिखो) अणु
		pr_err("%s: No read/write API for accessing vdd_%s regs\n",
			__func__, voltdm->name);
		वापस -EINVAL;
	पूर्ण

	*target_vsel = voltdm->pmic->uv_to_vsel(target_volt);
	*current_vsel = voltdm->pmic->uv_to_vsel(voltdm->nominal_volt);

	/* Setting the ON voltage to the new target voltage */
	vc_cmdval = voltdm->पढ़ो(vc->cmdval_reg);
	vc_cmdval &= ~vc->common->cmd_on_mask;
	vc_cmdval |= (*target_vsel << vc->common->cmd_on_shअगरt);
	voltdm->ग_लिखो(vc_cmdval, vc->cmdval_reg);

	voltdm->vc_param->on = target_volt;

	omap_vp_update_errorgain(voltdm, target_volt);

	वापस 0;
पूर्ण

व्योम omap_vc_post_scale(काष्ठा voltageकरोमुख्य *voltdm,
			अचिन्हित दीर्घ target_volt,
			u8 target_vsel, u8 current_vsel)
अणु
	u32 smps_steps = 0, smps_delay = 0;

	smps_steps = असल(target_vsel - current_vsel);
	/* SMPS slew rate / step size. 2us added as buffer. */
	smps_delay = ((smps_steps * voltdm->pmic->step_size) /
			voltdm->pmic->slew_rate) + 2;
	udelay(smps_delay);
पूर्ण

/* vc_bypass_scale - VC bypass method of voltage scaling */
पूर्णांक omap_vc_bypass_scale(काष्ठा voltageकरोमुख्य *voltdm,
			 अचिन्हित दीर्घ target_volt)
अणु
	काष्ठा omap_vc_channel *vc = voltdm->vc;
	u32 loop_cnt = 0, retries_cnt = 0;
	u32 vc_valid, vc_bypass_val_reg, vc_bypass_value;
	u8 target_vsel, current_vsel;
	पूर्णांक ret;

	ret = omap_vc_pre_scale(voltdm, target_volt, &target_vsel, &current_vsel);
	अगर (ret)
		वापस ret;

	vc_valid = vc->common->valid;
	vc_bypass_val_reg = vc->common->bypass_val_reg;
	vc_bypass_value = (target_vsel << vc->common->data_shअगरt) |
		(vc->volt_reg_addr << vc->common->regaddr_shअगरt) |
		(vc->i2c_slave_addr << vc->common->slaveaddr_shअगरt);

	voltdm->ग_लिखो(vc_bypass_value, vc_bypass_val_reg);
	voltdm->ग_लिखो(vc_bypass_value | vc_valid, vc_bypass_val_reg);

	vc_bypass_value = voltdm->पढ़ो(vc_bypass_val_reg);
	/*
	 * Loop till the bypass command is acknowledged from the SMPS.
	 * NOTE: This is legacy code. The loop count and retry count needs
	 * to be revisited.
	 */
	जबतक (!(vc_bypass_value & vc_valid)) अणु
		loop_cnt++;

		अगर (retries_cnt > 10) अणु
			pr_warn("%s: Retry count exceeded\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		अगर (loop_cnt > 50) अणु
			retries_cnt++;
			loop_cnt = 0;
			udelay(10);
		पूर्ण
		vc_bypass_value = voltdm->पढ़ो(vc_bypass_val_reg);
	पूर्ण

	omap_vc_post_scale(voltdm, target_volt, target_vsel, current_vsel);
	वापस 0;
पूर्ण

/* Convert microsecond value to number of 32kHz घड़ी cycles */
अटल अंतरभूत u32 omap_usec_to_32k(u32 usec)
अणु
	वापस DIV_ROUND_UP_ULL(32768ULL * (u64)usec, 1000000ULL);
पूर्ण

काष्ठा omap3_vc_timings अणु
	u32 voltsetup1;
	u32 voltsetup2;
पूर्ण;

काष्ठा omap3_vc अणु
	काष्ठा voltageकरोमुख्य *vd;
	u32 voltctrl;
	u32 voltsetup1;
	u32 voltsetup2;
	काष्ठा omap3_vc_timings timings[2];
पूर्ण;
अटल काष्ठा omap3_vc vc;

व्योम omap3_vc_set_pmic_संकेतing(पूर्णांक core_next_state)
अणु
	काष्ठा voltageकरोमुख्य *vd = vc.vd;
	काष्ठा omap3_vc_timings *c = vc.timings;
	u32 voltctrl, voltsetup1, voltsetup2;

	voltctrl = vc.voltctrl;
	voltsetup1 = vc.voltsetup1;
	voltsetup2 = vc.voltsetup2;

	चयन (core_next_state) अणु
	हाल PWRDM_POWER_OFF:
		voltctrl &= ~(OMAP3430_PRM_VOLTCTRL_AUTO_RET |
			      OMAP3430_PRM_VOLTCTRL_AUTO_SLEEP);
		voltctrl |= OMAP3430_PRM_VOLTCTRL_AUTO_OFF;
		अगर (voltctrl & OMAP3430_PRM_VOLTCTRL_SEL_OFF)
			voltsetup2 = c->voltsetup2;
		अन्यथा
			voltsetup1 = c->voltsetup1;
		अवरोध;
	हाल PWRDM_POWER_RET:
	शेष:
		c++;
		voltctrl &= ~(OMAP3430_PRM_VOLTCTRL_AUTO_OFF |
			      OMAP3430_PRM_VOLTCTRL_AUTO_SLEEP);
		voltctrl |= OMAP3430_PRM_VOLTCTRL_AUTO_RET;
		voltsetup1 = c->voltsetup1;
		अवरोध;
	पूर्ण

	अगर (voltctrl != vc.voltctrl) अणु
		vd->ग_लिखो(voltctrl, OMAP3_PRM_VOLTCTRL_OFFSET);
		vc.voltctrl = voltctrl;
	पूर्ण
	अगर (voltsetup1 != vc.voltsetup1) अणु
		vd->ग_लिखो(c->voltsetup1,
			  OMAP3_PRM_VOLTSETUP1_OFFSET);
		vc.voltsetup1 = voltsetup1;
	पूर्ण
	अगर (voltsetup2 != vc.voltsetup2) अणु
		vd->ग_लिखो(c->voltsetup2,
			  OMAP3_PRM_VOLTSETUP2_OFFSET);
		vc.voltsetup2 = voltsetup2;
	पूर्ण
पूर्ण

व्योम omap4_vc_set_pmic_संकेतing(पूर्णांक core_next_state)
अणु
	काष्ठा voltageकरोमुख्य *vd = vc.vd;
	u32 val;

	अगर (!vd)
		वापस;

	चयन (core_next_state) अणु
	हाल PWRDM_POWER_RET:
		val = OMAP4_VDD_RET_VAL;
		अवरोध;
	शेष:
		val = OMAP4_VDD_DEFAULT_VAL;
		अवरोध;
	पूर्ण

	vd->ग_लिखो(val, OMAP4_PRM_VOLTCTRL_OFFSET);
पूर्ण

/*
 * Configure संकेत polarity क्रम sys_clkreq and sys_off_mode pins
 * as the शेष values are wrong and can cause the प्रणाली to hang
 * अगर any twl4030 scripts are loaded.
 */
अटल व्योम __init omap3_vc_init_pmic_संकेतing(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	u32 val;

	अगर (vc.vd)
		वापस;

	vc.vd = voltdm;

	val = voltdm->पढ़ो(OMAP3_PRM_POLCTRL_OFFSET);
	अगर (!(val & OMAP3430_PRM_POLCTRL_CLKREQ_POL) ||
	    (val & OMAP3430_PRM_POLCTRL_OFFMODE_POL)) अणु
		val |= OMAP3430_PRM_POLCTRL_CLKREQ_POL;
		val &= ~OMAP3430_PRM_POLCTRL_OFFMODE_POL;
		pr_debug("PM: fixing sys_clkreq and sys_off_mode polarity to 0x%x\n",
			 val);
		voltdm->ग_लिखो(val, OMAP3_PRM_POLCTRL_OFFSET);
	पूर्ण

	/*
	 * By शेष let's use I2C4 संकेतing क्रम retention idle
	 * and sys_off_mode pin संकेतing क्रम off idle. This way we
	 * have sys_clk_req pin go करोwn क्रम retention and both
	 * sys_clk_req and sys_off_mode pins will go करोwn क्रम off
	 * idle. And we can also scale voltages to zero क्रम off-idle.
	 * Note that no actual voltage scaling during off-idle will
	 * happen unless the board specअगरic twl4030 PMIC scripts are
	 * loaded. See also omap_vc_i2c_init क्रम comments regarding
	 * erratum i531.
	 */
	val = voltdm->पढ़ो(OMAP3_PRM_VOLTCTRL_OFFSET);
	अगर (!(val & OMAP3430_PRM_VOLTCTRL_SEL_OFF)) अणु
		val |= OMAP3430_PRM_VOLTCTRL_SEL_OFF;
		pr_debug("PM: setting voltctrl sys_off_mode signaling to 0x%x\n",
			 val);
		voltdm->ग_लिखो(val, OMAP3_PRM_VOLTCTRL_OFFSET);
	पूर्ण
	vc.voltctrl = val;

	omap3_vc_set_pmic_संकेतing(PWRDM_POWER_ON);
पूर्ण

अटल व्योम omap3_init_voltsetup1(काष्ठा voltageकरोमुख्य *voltdm,
				  काष्ठा omap3_vc_timings *c, u32 idle)
अणु
	अचिन्हित दीर्घ val;

	val = (voltdm->vc_param->on - idle) / voltdm->pmic->slew_rate;
	val *= voltdm->sys_clk.rate / 8 / 1000000 + 1;
	val <<= __ffs(voltdm->vfsm->voltsetup_mask);
	c->voltsetup1 &= ~voltdm->vfsm->voltsetup_mask;
	c->voltsetup1 |= val;
पूर्ण

/**
 * omap3_set_i2c_timings - sets i2c sleep timings क्रम a channel
 * @voltdm: channel to configure
 * @off_mode: select whether retention or off mode values used
 *
 * Calculates and sets up voltage controller to use I2C based
 * voltage scaling क्रम sleep modes. This can be used क्रम either off mode
 * or retention. Off mode has additionally an option to use sys_off_mode
 * pad, which uses a global संकेत to program the whole घातer IC to
 * off-mode.
 *
 * Note that pmic is not controlling the voltage scaling during
 * retention संकेतed over I2C4, so we can keep voltsetup2 as 0.
 * And the oscillator is not shut off over I2C4, so no need to
 * set clksetup.
 */
अटल व्योम omap3_set_i2c_timings(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap3_vc_timings *c = vc.timings;

	/* Configure PRWDM_POWER_OFF over I2C4 */
	omap3_init_voltsetup1(voltdm, c, voltdm->vc_param->off);
	c++;
	/* Configure PRWDM_POWER_RET over I2C4 */
	omap3_init_voltsetup1(voltdm, c, voltdm->vc_param->ret);
पूर्ण

/**
 * omap3_set_off_timings - sets off-mode timings क्रम a channel
 * @voltdm: channel to configure
 *
 * Calculates and sets up off-mode timings क्रम a channel. Off-mode
 * can use either I2C based voltage scaling, or alternatively
 * sys_off_mode pad can be used to send a global command to घातer IC.n,
 * sys_off_mode has the additional benefit that voltages can be
 * scaled to zero volt level with TWL4030 / TWL5030, I2C can only
 * scale to 600mV.
 *
 * Note that omap is not controlling the voltage scaling during
 * off idle संकेतed by sys_off_mode, so we can keep voltsetup1
 * as 0.
 */
अटल व्योम omap3_set_off_timings(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap3_vc_timings *c = vc.timings;
	u32 tstart, tshut, clksetup, voltoffset;

	अगर (c->voltsetup2)
		वापस;

	omap_pm_get_oscillator(&tstart, &tshut);
	अगर (tstart == अच_दीर्घ_उच्च) अणु
		pr_debug("PM: oscillator start-up time not initialized, using 10ms\n");
		clksetup = omap_usec_to_32k(10000);
	पूर्ण अन्यथा अणु
		clksetup = omap_usec_to_32k(tstart);
	पूर्ण

	/*
	 * For twl4030 errata 27, we need to allow minimum ~488.32 us रुको to
	 * चयन from HFCLKIN to पूर्णांकernal oscillator. That means timings
	 * have voltoffset fixed to 0xa in rounded up 32 KiHz cycles. And
	 * that means we can calculate the value based on the oscillator
	 * start-up समय since voltoffset2 = clksetup - voltoffset.
	 */
	voltoffset = omap_usec_to_32k(488);
	c->voltsetup2 = clksetup - voltoffset;
	voltdm->ग_लिखो(clksetup, OMAP3_PRM_CLKSETUP_OFFSET);
	voltdm->ग_लिखो(voltoffset, OMAP3_PRM_VOLTOFFSET_OFFSET);
पूर्ण

अटल व्योम __init omap3_vc_init_channel(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	omap3_vc_init_pmic_संकेतing(voltdm);
	omap3_set_off_timings(voltdm);
	omap3_set_i2c_timings(voltdm);
पूर्ण

/**
 * omap4_calc_volt_ramp - calculates voltage ramping delays on omap4
 * @voltdm: channel to calculate values क्रम
 * @voltage_dअगरf: voltage dअगरference in microvolts
 *
 * Calculates voltage ramp prescaler + counter values क्रम a voltage
 * dअगरference on omap4. Returns a field value suitable क्रम writing to
 * VOLTSETUP रेजिस्टर क्रम a channel in following क्रमmat:
 * bits[8:9] prescaler ... bits[0:5] counter. See OMAP4 TRM क्रम reference.
 */
अटल u32 omap4_calc_volt_ramp(काष्ठा voltageकरोमुख्य *voltdm, u32 voltage_dअगरf)
अणु
	u32 prescaler;
	u32 cycles;
	u32 समय;

	समय = voltage_dअगरf / voltdm->pmic->slew_rate;

	cycles = voltdm->sys_clk.rate / 1000 * समय / 1000;

	cycles /= 64;
	prescaler = 0;

	/* shअगरt to next prescaler until no overflow */

	/* scale क्रम भाग 256 = 64 * 4 */
	अगर (cycles > 63) अणु
		cycles /= 4;
		prescaler++;
	पूर्ण

	/* scale क्रम भाग 512 = 256 * 2 */
	अगर (cycles > 63) अणु
		cycles /= 2;
		prescaler++;
	पूर्ण

	/* scale क्रम भाग 2048 = 512 * 4 */
	अगर (cycles > 63) अणु
		cycles /= 4;
		prescaler++;
	पूर्ण

	/* check क्रम overflow => invalid ramp समय */
	अगर (cycles > 63) अणु
		pr_warn("%s: invalid setuptime for vdd_%s\n", __func__,
			voltdm->name);
		वापस 0;
	पूर्ण

	cycles++;

	वापस (prescaler << OMAP4430_RAMP_UP_PRESCAL_SHIFT) |
		(cycles << OMAP4430_RAMP_UP_COUNT_SHIFT);
पूर्ण

/**
 * omap4_usec_to_val_scrm - convert microsecond value to SCRM module bitfield
 * @usec: microseconds
 * @shअगरt: number of bits to shअगरt left
 * @mask: bitfield mask
 *
 * Converts microsecond value to OMAP4 SCRM bitfield. Bitfield is
 * shअगरted to requested position, and checked agains the mask value.
 * If larger, क्रमced to the max value of the field (i.e. the mask itself.)
 * Returns the SCRM bitfield value.
 */
अटल u32 omap4_usec_to_val_scrm(u32 usec, पूर्णांक shअगरt, u32 mask)
अणु
	u32 val;

	val = omap_usec_to_32k(usec) << shअगरt;

	/* Check क्रम overflow, अगर yes, क्रमce to max value */
	अगर (val > mask)
		val = mask;

	वापस val;
पूर्ण

/**
 * omap4_set_timings - set voltage ramp timings क्रम a channel
 * @voltdm: channel to configure
 * @off_mode: whether off-mode values are used
 *
 * Calculates and sets the voltage ramp up / करोwn values क्रम a channel.
 */
अटल व्योम omap4_set_timings(काष्ठा voltageकरोमुख्य *voltdm, bool off_mode)
अणु
	u32 val;
	u32 ramp;
	पूर्णांक offset;
	u32 tstart, tshut;

	अगर (off_mode) अणु
		ramp = omap4_calc_volt_ramp(voltdm,
			voltdm->vc_param->on - voltdm->vc_param->off);
		offset = voltdm->vfsm->voltsetup_off_reg;
	पूर्ण अन्यथा अणु
		ramp = omap4_calc_volt_ramp(voltdm,
			voltdm->vc_param->on - voltdm->vc_param->ret);
		offset = voltdm->vfsm->voltsetup_reg;
	पूर्ण

	अगर (!ramp)
		वापस;

	val = voltdm->पढ़ो(offset);

	val |= ramp << OMAP4430_RAMP_DOWN_COUNT_SHIFT;

	val |= ramp << OMAP4430_RAMP_UP_COUNT_SHIFT;

	voltdm->ग_लिखो(val, offset);

	omap_pm_get_oscillator(&tstart, &tshut);

	val = omap4_usec_to_val_scrm(tstart, OMAP4_SETUPTIME_SHIFT,
		OMAP4_SETUPTIME_MASK);
	val |= omap4_usec_to_val_scrm(tshut, OMAP4_DOWNTIME_SHIFT,
		OMAP4_DOWNTIME_MASK);

	ग_लिखोl_relaxed(val, OMAP4_SCRM_CLKSETUPTIME);
पूर्ण

अटल व्योम __init omap4_vc_init_pmic_संकेतing(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	अगर (vc.vd)
		वापस;

	vc.vd = voltdm;
	voltdm->ग_लिखो(OMAP4_VDD_DEFAULT_VAL, OMAP4_PRM_VOLTCTRL_OFFSET);
पूर्ण

/* OMAP4 specअगरic voltage init functions */
अटल व्योम __init omap4_vc_init_channel(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	omap4_vc_init_pmic_संकेतing(voltdm);
	omap4_set_timings(voltdm, true);
	omap4_set_timings(voltdm, false);
पूर्ण

काष्ठा i2c_init_data अणु
	u8 loadbits;
	u8 load;
	u8 hsscll_38_4;
	u8 hsscll_26;
	u8 hsscll_19_2;
	u8 hsscll_16_8;
	u8 hsscll_12;
पूर्ण;

अटल स्थिर काष्ठा i2c_init_data omap4_i2c_timing_data[] __initस्थिर = अणु
	अणु
		.load = 50,
		.loadbits = 0x3,
		.hsscll_38_4 = 13,
		.hsscll_26 = 11,
		.hsscll_19_2 = 9,
		.hsscll_16_8 = 9,
		.hsscll_12 = 8,
	पूर्ण,
	अणु
		.load = 25,
		.loadbits = 0x2,
		.hsscll_38_4 = 13,
		.hsscll_26 = 11,
		.hsscll_19_2 = 9,
		.hsscll_16_8 = 9,
		.hsscll_12 = 8,
	पूर्ण,
	अणु
		.load = 12,
		.loadbits = 0x1,
		.hsscll_38_4 = 11,
		.hsscll_26 = 10,
		.hsscll_19_2 = 9,
		.hsscll_16_8 = 9,
		.hsscll_12 = 8,
	पूर्ण,
	अणु
		.load = 0,
		.loadbits = 0x0,
		.hsscll_38_4 = 12,
		.hsscll_26 = 10,
		.hsscll_19_2 = 9,
		.hsscll_16_8 = 8,
		.hsscll_12 = 8,
	पूर्ण,
पूर्ण;

/**
 * omap4_vc_i2c_timing_init - sets up board I2C timing parameters
 * @voltdm: voltageकरोमुख्य poपूर्णांकer to get data from
 *
 * Use PMIC + board supplied settings क्रम calculating the total I2C
 * channel capacitance and set the timing parameters based on this.
 * Pre-calculated values are provided in data tables, as it is not
 * too straightक्रमward to calculate these runसमय.
 */
अटल व्योम __init omap4_vc_i2c_timing_init(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	u32 capacitance;
	u32 val;
	u16 hsscll;
	स्थिर काष्ठा i2c_init_data *i2c_data;

	अगर (!voltdm->pmic->i2c_high_speed) अणु
		pr_info("%s: using bootloader low-speed timings\n", __func__);
		वापस;
	पूर्ण

	/* PCB trace capacitance, 0.125pF / mm => mm / 8 */
	capacitance = DIV_ROUND_UP(sr_i2c_pcb_length, 8);

	/* OMAP pad capacitance */
	capacitance += 4;

	/* PMIC pad capacitance */
	capacitance += voltdm->pmic->i2c_pad_load;

	/* Search क्रम capacitance match in the table */
	i2c_data = omap4_i2c_timing_data;

	जबतक (i2c_data->load > capacitance)
		i2c_data++;

	/* Select proper values based on sysclk frequency */
	चयन (voltdm->sys_clk.rate) अणु
	हाल 38400000:
		hsscll = i2c_data->hsscll_38_4;
		अवरोध;
	हाल 26000000:
		hsscll = i2c_data->hsscll_26;
		अवरोध;
	हाल 19200000:
		hsscll = i2c_data->hsscll_19_2;
		अवरोध;
	हाल 16800000:
		hsscll = i2c_data->hsscll_16_8;
		अवरोध;
	हाल 12000000:
		hsscll = i2c_data->hsscll_12;
		अवरोध;
	शेष:
		pr_warn("%s: unsupported sysclk rate: %d!\n", __func__,
			voltdm->sys_clk.rate);
		वापस;
	पूर्ण

	/* Loadbits define pull setup क्रम the I2C channels */
	val = i2c_data->loadbits << 25 | i2c_data->loadbits << 29;

	/* Write to SYSCTRL_PADCONF_WKUP_CTRL_I2C_2 to setup I2C pull */
	ग_लिखोl_relaxed(val, OMAP2_L4_IO_ADDRESS(OMAP4_CTRL_MODULE_PAD_WKUP +
				OMAP4_CTRL_MODULE_PAD_WKUP_CONTROL_I2C_2));

	/* HSSCLH can always be zero */
	val = hsscll << OMAP4430_HSSCLL_SHIFT;
	val |= (0x28 << OMAP4430_SCLL_SHIFT | 0x2c << OMAP4430_SCLH_SHIFT);

	/* Write setup बार to I2C config रेजिस्टर */
	voltdm->ग_लिखो(val, OMAP4_PRM_VC_CFG_I2C_CLK_OFFSET);
पूर्ण



/**
 * omap_vc_i2c_init - initialize I2C पूर्णांकerface to PMIC
 * @voltdm: voltage करोमुख्य containing VC data
 *
 * Use PMIC supplied settings क्रम I2C high-speed mode and
 * master code (अगर set) and program the VC I2C configuration
 * रेजिस्टर.
 *
 * The VC I2C configuration is common to all VC channels,
 * so this function only configures I2C क्रम the first VC
 * channel रेजिस्टरs.  All other VC channels will use the
 * same configuration.
 */
अटल व्योम __init omap_vc_i2c_init(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vc_channel *vc = voltdm->vc;
	अटल bool initialized;
	अटल bool i2c_high_speed;
	u8 mcode;

	अगर (initialized) अणु
		अगर (voltdm->pmic->i2c_high_speed != i2c_high_speed)
			pr_warn("%s: I2C config for vdd_%s does not match other channels (%u).\n",
				__func__, voltdm->name, i2c_high_speed);
		वापस;
	पूर्ण

	/*
	 * Note that क्रम omap3 OMAP3430_SREN_MASK clears SREN to work around
	 * erratum i531 "Extra Power Consumed When Repeated Start Operation
	 * Mode Is Enabled on I2C Interface Dedicated क्रम Smart Reflex (I2C4)".
	 * Otherwise I2C4 eventually leads पूर्णांकo about 23mW extra घातer being
	 * consumed even during off idle using VMODE.
	 */
	i2c_high_speed = voltdm->pmic->i2c_high_speed;
	अगर (i2c_high_speed)
		voltdm->rmw(vc->common->i2c_cfg_clear_mask,
			    vc->common->i2c_cfg_hsen_mask,
			    vc->common->i2c_cfg_reg);

	mcode = voltdm->pmic->i2c_mcode;
	अगर (mcode)
		voltdm->rmw(vc->common->i2c_mcode_mask,
			    mcode << __ffs(vc->common->i2c_mcode_mask),
			    vc->common->i2c_cfg_reg);

	अगर (cpu_is_omap44xx())
		omap4_vc_i2c_timing_init(voltdm);

	initialized = true;
पूर्ण

/**
 * omap_vc_calc_vsel - calculate vsel value क्रम a channel
 * @voltdm: channel to calculate value क्रम
 * @uvolt: microvolt value to convert to vsel
 *
 * Converts a microvolt value to vsel value क्रम the used PMIC.
 * This checks whether the microvolt value is out of bounds, and
 * adjusts the value accordingly. If unsupported value detected,
 * warning is thrown.
 */
अटल u8 omap_vc_calc_vsel(काष्ठा voltageकरोमुख्य *voltdm, u32 uvolt)
अणु
	अगर (voltdm->pmic->vddmin > uvolt)
		uvolt = voltdm->pmic->vddmin;
	अगर (voltdm->pmic->vddmax < uvolt) अणु
		WARN(1, "%s: voltage not supported by pmic: %u vs max %u\n",
			__func__, uvolt, voltdm->pmic->vddmax);
		/* Lets try maximum value anyway */
		uvolt = voltdm->pmic->vddmax;
	पूर्ण

	वापस voltdm->pmic->uv_to_vsel(uvolt);
पूर्ण

#अगर_घोषित CONFIG_PM
/**
 * omap_pm_setup_sr_i2c_pcb_length - set length of SR I2C traces on PCB
 * @mm: length of the PCB trace in millimetres
 *
 * Sets the PCB trace length क्रम the I2C channel. By शेष uses 63mm.
 * This is needed क्रम properly calculating the capacitance value क्रम
 * the PCB trace, and क्रम setting the SR I2C channel timing parameters.
 */
व्योम __init omap_pm_setup_sr_i2c_pcb_length(u32 mm)
अणु
	sr_i2c_pcb_length = mm;
पूर्ण
#पूर्ण_अगर

व्योम __init omap_vc_init_channel(काष्ठा voltageकरोमुख्य *voltdm)
अणु
	काष्ठा omap_vc_channel *vc = voltdm->vc;
	u8 on_vsel, onlp_vsel, ret_vsel, off_vsel;
	u32 val;

	अगर (!voltdm->pmic || !voltdm->pmic->uv_to_vsel) अणु
		pr_err("%s: No PMIC info for vdd_%s\n", __func__, voltdm->name);
		वापस;
	पूर्ण

	अगर (!voltdm->पढ़ो || !voltdm->ग_लिखो) अणु
		pr_err("%s: No read/write API for accessing vdd_%s regs\n",
			__func__, voltdm->name);
		वापस;
	पूर्ण

	vc->cfg_channel = 0;
	अगर (vc->flags & OMAP_VC_CHANNEL_CFG_MUTANT)
		vc_cfg_bits = &vc_mutant_channel_cfg;
	अन्यथा
		vc_cfg_bits = &vc_शेष_channel_cfg;

	/* get PMIC/board specअगरic settings */
	vc->i2c_slave_addr = voltdm->pmic->i2c_slave_addr;
	vc->volt_reg_addr = voltdm->pmic->volt_reg_addr;
	vc->cmd_reg_addr = voltdm->pmic->cmd_reg_addr;

	/* Configure the i2c slave address क्रम this VC */
	voltdm->rmw(vc->smps_sa_mask,
		    vc->i2c_slave_addr << __ffs(vc->smps_sa_mask),
		    vc->smps_sa_reg);
	vc->cfg_channel |= vc_cfg_bits->sa;

	/*
	 * Configure the PMIC रेजिस्टर addresses.
	 */
	voltdm->rmw(vc->smps_volra_mask,
		    vc->volt_reg_addr << __ffs(vc->smps_volra_mask),
		    vc->smps_volra_reg);
	vc->cfg_channel |= vc_cfg_bits->rav;

	अगर (vc->cmd_reg_addr) अणु
		voltdm->rmw(vc->smps_cmdra_mask,
			    vc->cmd_reg_addr << __ffs(vc->smps_cmdra_mask),
			    vc->smps_cmdra_reg);
		vc->cfg_channel |= vc_cfg_bits->rac;
	पूर्ण

	अगर (vc->cmd_reg_addr == vc->volt_reg_addr)
		vc->cfg_channel |= vc_cfg_bits->racen;

	/* Set up the on, inactive, retention and off voltage */
	on_vsel = omap_vc_calc_vsel(voltdm, voltdm->vc_param->on);
	onlp_vsel = omap_vc_calc_vsel(voltdm, voltdm->vc_param->onlp);
	ret_vsel = omap_vc_calc_vsel(voltdm, voltdm->vc_param->ret);
	off_vsel = omap_vc_calc_vsel(voltdm, voltdm->vc_param->off);

	val = ((on_vsel << vc->common->cmd_on_shअगरt) |
	       (onlp_vsel << vc->common->cmd_onlp_shअगरt) |
	       (ret_vsel << vc->common->cmd_ret_shअगरt) |
	       (off_vsel << vc->common->cmd_off_shअगरt));
	voltdm->ग_लिखो(val, vc->cmdval_reg);
	vc->cfg_channel |= vc_cfg_bits->cmd;

	/* Channel configuration */
	omap_vc_config_channel(voltdm);

	omap_vc_i2c_init(voltdm);

	अगर (cpu_is_omap34xx())
		omap3_vc_init_channel(voltdm);
	अन्यथा अगर (cpu_is_omap44xx())
		omap4_vc_init_channel(voltdm);
पूर्ण

