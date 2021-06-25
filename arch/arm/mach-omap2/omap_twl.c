<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMAP and TWL PMIC specअगरic initializations.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated.
 * Thara Gopinath
 * Copyright (C) 2009 Texas Instruments Incorporated.
 * Nishanth Menon
 * Copyright (C) 2009 Nokia Corporation
 * Paul Walmsley
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/twl.h>

#समावेश "soc.h"
#समावेश "voltage.h"

#समावेश "pm.h"

#घोषणा OMAP3_SRI2C_SLAVE_ADDR		0x12
#घोषणा OMAP3_VDD_MPU_SR_CONTROL_REG	0x00
#घोषणा OMAP3_VDD_CORE_SR_CONTROL_REG	0x01
#घोषणा OMAP3_VP_CONFIG_ERROROFFSET	0x00
#घोषणा OMAP3_VP_VSTEPMIN_VSTEPMIN	0x1
#घोषणा OMAP3_VP_VSTEPMAX_VSTEPMAX	0x04
#घोषणा OMAP3_VP_VLIMITTO_TIMEOUT_US	200

#घोषणा OMAP4_SRI2C_SLAVE_ADDR		0x12
#घोषणा OMAP4_VDD_MPU_SR_VOLT_REG	0x55
#घोषणा OMAP4_VDD_MPU_SR_CMD_REG	0x56
#घोषणा OMAP4_VDD_IVA_SR_VOLT_REG	0x5B
#घोषणा OMAP4_VDD_IVA_SR_CMD_REG	0x5C
#घोषणा OMAP4_VDD_CORE_SR_VOLT_REG	0x61
#घोषणा OMAP4_VDD_CORE_SR_CMD_REG	0x62

अटल bool is_offset_valid;
अटल u8 smps_offset;

#घोषणा REG_SMPS_OFFSET         0xE0

अटल अचिन्हित दीर्घ twl4030_vsel_to_uv(स्थिर u8 vsel)
अणु
	वापस (((vsel * 125) + 6000)) * 100;
पूर्ण

अटल u8 twl4030_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	वापस DIV_ROUND_UP(uv - 600000, 12500);
पूर्ण

अटल अचिन्हित दीर्घ twl6030_vsel_to_uv(स्थिर u8 vsel)
अणु
	/*
	 * In TWL6030 depending on the value of SMPS_OFFSET
	 * efuse रेजिस्टर the voltage range supported in
	 * standard mode can be either between 0.6V - 1.3V or
	 * 0.7V - 1.4V. In TWL6030 ES1.0 SMPS_OFFSET efuse
	 * is programmed to all 0's where as starting from
	 * TWL6030 ES1.1 the efuse is programmed to 1
	 */
	अगर (!is_offset_valid) अणु
		twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID0, &smps_offset,
				REG_SMPS_OFFSET);
		is_offset_valid = true;
	पूर्ण

	अगर (!vsel)
		वापस 0;
	/*
	 * There is no specअगरic क्रमmula क्रम voltage to vsel
	 * conversion above 1.3V. There are special hardcoded
	 * values क्रम voltages above 1.3V. Currently we are
	 * hardcoding only क्रम 1.35 V which is used क्रम 1GH OPP क्रम
	 * OMAP4430.
	 */
	अगर (vsel == 0x3A)
		वापस 1350000;

	अगर (smps_offset & 0x8)
		वापस ((((vsel - 1) * 1266) + 70900)) * 10;
	अन्यथा
		वापस ((((vsel - 1) * 1266) + 60770)) * 10;
पूर्ण

अटल u8 twl6030_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	/*
	 * In TWL6030 depending on the value of SMPS_OFFSET
	 * efuse रेजिस्टर the voltage range supported in
	 * standard mode can be either between 0.6V - 1.3V or
	 * 0.7V - 1.4V. In TWL6030 ES1.0 SMPS_OFFSET efuse
	 * is programmed to all 0's where as starting from
	 * TWL6030 ES1.1 the efuse is programmed to 1
	 */
	अगर (!is_offset_valid) अणु
		twl_i2c_पढ़ो_u8(TWL6030_MODULE_ID0, &smps_offset,
				REG_SMPS_OFFSET);
		is_offset_valid = true;
	पूर्ण

	अगर (!uv)
		वापस 0x00;
	/*
	 * There is no specअगरic क्रमmula क्रम voltage to vsel
	 * conversion above 1.3V. There are special hardcoded
	 * values क्रम voltages above 1.3V. Currently we are
	 * hardcoding only क्रम 1.35 V which is used क्रम 1GH OPP क्रम
	 * OMAP4430.
	 */
	अगर (uv > twl6030_vsel_to_uv(0x39)) अणु
		अगर (uv == 1350000)
			वापस 0x3A;
		pr_err("%s:OUT OF RANGE! non mapped vsel for %ld Vs max %ld\n",
			__func__, uv, twl6030_vsel_to_uv(0x39));
		वापस 0x3A;
	पूर्ण

	अगर (smps_offset & 0x8)
		वापस DIV_ROUND_UP(uv - 709000, 12660) + 1;
	अन्यथा
		वापस DIV_ROUND_UP(uv - 607700, 12660) + 1;
पूर्ण

अटल काष्ठा omap_voltdm_pmic omap3_mpu_pmic = अणु
	.slew_rate		= 4000,
	.step_size		= 12500,
	.vp_erroroffset		= OMAP3_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin		= OMAP3_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax		= OMAP3_VP_VSTEPMAX_VSTEPMAX,
	.vddmin			= 600000,
	.vddmax			= 1450000,
	.vp_समयout_us		= OMAP3_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr		= OMAP3_SRI2C_SLAVE_ADDR,
	.volt_reg_addr		= OMAP3_VDD_MPU_SR_CONTROL_REG,
	.i2c_high_speed		= true,
	.vsel_to_uv		= twl4030_vsel_to_uv,
	.uv_to_vsel		= twl4030_uv_to_vsel,
पूर्ण;

अटल काष्ठा omap_voltdm_pmic omap3_core_pmic = अणु
	.slew_rate		= 4000,
	.step_size		= 12500,
	.vp_erroroffset		= OMAP3_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin		= OMAP3_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax		= OMAP3_VP_VSTEPMAX_VSTEPMAX,
	.vddmin			= 600000,
	.vddmax			= 1450000,
	.vp_समयout_us		= OMAP3_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr		= OMAP3_SRI2C_SLAVE_ADDR,
	.volt_reg_addr		= OMAP3_VDD_CORE_SR_CONTROL_REG,
	.i2c_high_speed		= true,
	.vsel_to_uv		= twl4030_vsel_to_uv,
	.uv_to_vsel		= twl4030_uv_to_vsel,
पूर्ण;

अटल काष्ठा omap_voltdm_pmic omap4_mpu_pmic = अणु
	.slew_rate		= 4000,
	.step_size		= 12660,
	.vp_erroroffset		= OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin		= OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax		= OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin			= 0,
	.vddmax			= 2100000,
	.vp_समयout_us		= OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr		= OMAP4_SRI2C_SLAVE_ADDR,
	.volt_reg_addr		= OMAP4_VDD_MPU_SR_VOLT_REG,
	.cmd_reg_addr		= OMAP4_VDD_MPU_SR_CMD_REG,
	.i2c_high_speed		= true,
	.i2c_pad_load		= 3,
	.vsel_to_uv		= twl6030_vsel_to_uv,
	.uv_to_vsel		= twl6030_uv_to_vsel,
पूर्ण;

अटल काष्ठा omap_voltdm_pmic omap4_iva_pmic = अणु
	.slew_rate		= 4000,
	.step_size		= 12660,
	.vp_erroroffset		= OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin		= OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax		= OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin			= 0,
	.vddmax			= 2100000,
	.vp_समयout_us		= OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr		= OMAP4_SRI2C_SLAVE_ADDR,
	.volt_reg_addr		= OMAP4_VDD_IVA_SR_VOLT_REG,
	.cmd_reg_addr		= OMAP4_VDD_IVA_SR_CMD_REG,
	.i2c_high_speed		= true,
	.i2c_pad_load		= 3,
	.vsel_to_uv		= twl6030_vsel_to_uv,
	.uv_to_vsel		= twl6030_uv_to_vsel,
पूर्ण;

अटल काष्ठा omap_voltdm_pmic omap4_core_pmic = अणु
	.slew_rate		= 4000,
	.step_size		= 12660,
	.vp_erroroffset		= OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin		= OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax		= OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin			= 0,
	.vddmax			= 2100000,
	.vp_समयout_us		= OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr		= OMAP4_SRI2C_SLAVE_ADDR,
	.volt_reg_addr		= OMAP4_VDD_CORE_SR_VOLT_REG,
	.cmd_reg_addr		= OMAP4_VDD_CORE_SR_CMD_REG,
	.i2c_high_speed		= true,
	.i2c_pad_load		= 3,
	.vsel_to_uv		= twl6030_vsel_to_uv,
	.uv_to_vsel		= twl6030_uv_to_vsel,
पूर्ण;

पूर्णांक __init omap4_twl_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;

	अगर (!cpu_is_omap44xx() ||
	    of_find_compatible_node(शून्य, शून्य, "motorola,cpcap"))
		वापस -ENODEV;

	voltdm = voltdm_lookup("mpu");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap4_mpu_pmic);

	voltdm = voltdm_lookup("iva");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap4_iva_pmic);

	voltdm = voltdm_lookup("core");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap4_core_pmic);

	वापस 0;
पूर्ण

पूर्णांक __init omap3_twl_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;

	अगर (!cpu_is_omap34xx())
		वापस -ENODEV;

	voltdm = voltdm_lookup("mpu_iva");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap3_mpu_pmic);

	voltdm = voltdm_lookup("core");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap3_core_pmic);

	वापस 0;
पूर्ण
