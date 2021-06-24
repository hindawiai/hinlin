<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * pmic-cpcap.c - CPCAP-specअगरic functions क्रम the OPP code
 *
 * Adapted from Motorola Mapphone Android Linux kernel
 * Copyright (C) 2011 Motorola, Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

#समावेश "soc.h"
#समावेश "pm.h"
#समावेश "voltage.h"

#समावेश <linux/init.h>
#समावेश "vc.h"

/**
 * omap_cpcap_vsel_to_vdc - convert CPCAP VSEL value to microvolts DC
 * @vsel: CPCAP VSEL value to convert
 *
 * Returns the microvolts DC that the CPCAP PMIC should generate when
 * programmed with @vsel.
 */
अटल अचिन्हित दीर्घ omap_cpcap_vsel_to_uv(अचिन्हित अक्षर vsel)
अणु
	अगर (vsel > 0x44)
		vsel = 0x44;
	वापस (((vsel * 125) + 6000)) * 100;
पूर्ण

/**
 * omap_cpcap_uv_to_vsel - convert microvolts DC to CPCAP VSEL value
 * @uv: microvolts DC to convert
 *
 * Returns the VSEL value necessary क्रम the CPCAP PMIC to
 * generate an output voltage equal to or greater than @uv microvolts DC.
 */
अटल अचिन्हित अक्षर omap_cpcap_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	अगर (uv < 600000)
		uv = 600000;
	अन्यथा अगर (uv > 1450000)
		uv = 1450000;
	वापस DIV_ROUND_UP(uv - 600000, 12500);
पूर्ण

अटल काष्ठा omap_voltdm_pmic omap_cpcap_core = अणु
	.slew_rate = 4000,
	.step_size = 12500,
	.vp_erroroffset = OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1350000,
	.vp_समयout_us = OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr = 0x02,
	.volt_reg_addr = 0x00,
	.cmd_reg_addr = 0x01,
	.i2c_high_speed = false,
	.vsel_to_uv = omap_cpcap_vsel_to_uv,
	.uv_to_vsel = omap_cpcap_uv_to_vsel,
पूर्ण;

अटल काष्ठा omap_voltdm_pmic omap_cpcap_iva = अणु
	.slew_rate = 4000,
	.step_size = 12500,
	.vp_erroroffset = OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1375000,
	.vp_समयout_us = OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr = 0x44,
	.volt_reg_addr = 0x0,
	.cmd_reg_addr = 0x01,
	.i2c_high_speed = false,
	.vsel_to_uv = omap_cpcap_vsel_to_uv,
	.uv_to_vsel = omap_cpcap_uv_to_vsel,
पूर्ण;

/**
 * omap_max8952_vsel_to_vdc - convert MAX8952 VSEL value to microvolts DC
 * @vsel: MAX8952 VSEL value to convert
 *
 * Returns the microvolts DC that the MAX8952 Regulator should generate when
 * programmed with @vsel.
 */
अटल अचिन्हित दीर्घ omap_max8952_vsel_to_uv(अचिन्हित अक्षर vsel)
अणु
	अगर (vsel > 0x3F)
		vsel = 0x3F;
	वापस (((vsel * 100) + 7700)) * 100;
पूर्ण

/**
 * omap_max8952_uv_to_vsel - convert microvolts DC to MAX8952 VSEL value
 * @uv: microvolts DC to convert
 *
 * Returns the VSEL value necessary क्रम the MAX8952 Regulator to
 * generate an output voltage equal to or greater than @uv microvolts DC.
 */
अटल अचिन्हित अक्षर omap_max8952_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	अगर (uv < 770000)
		uv = 770000;
	अन्यथा अगर (uv > 1400000)
		uv = 1400000;
	वापस DIV_ROUND_UP(uv - 770000, 10000);
पूर्ण

अटल काष्ठा omap_voltdm_pmic omap443x_max8952_mpu = अणु
	.slew_rate = 16000,
	.step_size = 10000,
	.vp_erroroffset = OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 900000,
	.vddmax = 1400000,
	.vp_समयout_us = OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr = 0x60,
	.volt_reg_addr = 0x03,
	.cmd_reg_addr = 0x03,
	.i2c_high_speed = false,
	.vsel_to_uv = omap_max8952_vsel_to_uv,
	.uv_to_vsel = omap_max8952_uv_to_vsel,
पूर्ण;

/**
 * omap_fan5355_vsel_to_vdc - convert FAN535503 VSEL value to microvolts DC
 * @vsel: FAN535503 VSEL value to convert
 *
 * Returns the microvolts DC that the FAN535503 Regulator should generate when
 * programmed with @vsel.
 */
अटल अचिन्हित दीर्घ omap_fan535503_vsel_to_uv(अचिन्हित अक्षर vsel)
अणु
	/* Extract bits[5:0] */
	vsel &= 0x3F;

	वापस (((vsel * 125) + 7500)) * 100;
पूर्ण

/**
 * omap_fan535508_vsel_to_vdc - convert FAN535508 VSEL value to microvolts DC
 * @vsel: FAN535508 VSEL value to convert
 *
 * Returns the microvolts DC that the FAN535508 Regulator should generate when
 * programmed with @vsel.
 */
अटल अचिन्हित दीर्घ omap_fan535508_vsel_to_uv(अचिन्हित अक्षर vsel)
अणु
	/* Extract bits[5:0] */
	vsel &= 0x3F;

	अगर (vsel > 0x37)
		vsel = 0x37;
	वापस (((vsel * 125) + 7500)) * 100;
पूर्ण


/**
 * omap_fan535503_uv_to_vsel - convert microvolts DC to FAN535503 VSEL value
 * @uv: microvolts DC to convert
 *
 * Returns the VSEL value necessary क्रम the MAX8952 Regulator to
 * generate an output voltage equal to or greater than @uv microvolts DC.
 */
अटल अचिन्हित अक्षर omap_fan535503_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	अचिन्हित अक्षर vsel;
	अगर (uv < 750000)
		uv = 750000;
	अन्यथा अगर (uv > 1537500)
		uv = 1537500;

	vsel = DIV_ROUND_UP(uv - 750000, 12500);
	वापस vsel | 0xC0;
पूर्ण

/**
 * omap_fan535508_uv_to_vsel - convert microvolts DC to FAN535508 VSEL value
 * @uv: microvolts DC to convert
 *
 * Returns the VSEL value necessary क्रम the MAX8952 Regulator to
 * generate an output voltage equal to or greater than @uv microvolts DC.
 */
अटल अचिन्हित अक्षर omap_fan535508_uv_to_vsel(अचिन्हित दीर्घ uv)
अणु
	अचिन्हित अक्षर vsel;
	अगर (uv < 750000)
		uv = 750000;
	अन्यथा अगर (uv > 1437500)
		uv = 1437500;

	vsel = DIV_ROUND_UP(uv - 750000, 12500);
	वापस vsel | 0xC0;
पूर्ण

/* fan5335-core */
अटल काष्ठा omap_voltdm_pmic omap4_fan_core = अणु
	.slew_rate = 4000,
	.step_size = 12500,
	.vp_erroroffset = OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 850000,
	.vddmax = 1375000,
	.vp_समयout_us = OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr = 0x4A,
	.i2c_high_speed = false,
	.volt_reg_addr = 0x01,
	.cmd_reg_addr = 0x01,
	.vsel_to_uv = omap_fan535508_vsel_to_uv,
	.uv_to_vsel = omap_fan535508_uv_to_vsel,
पूर्ण;

/* fan5335 iva */
अटल काष्ठा omap_voltdm_pmic omap4_fan_iva = अणु
	.slew_rate = 4000,
	.step_size = 12500,
	.vp_erroroffset = OMAP4_VP_CONFIG_ERROROFFSET,
	.vp_vstepmin = OMAP4_VP_VSTEPMIN_VSTEPMIN,
	.vp_vstepmax = OMAP4_VP_VSTEPMAX_VSTEPMAX,
	.vddmin = 850000,
	.vddmax = 1375000,
	.vp_समयout_us = OMAP4_VP_VLIMITTO_TIMEOUT_US,
	.i2c_slave_addr = 0x48,
	.volt_reg_addr = 0x01,
	.cmd_reg_addr = 0x01,
	.i2c_high_speed = false,
	.vsel_to_uv = omap_fan535503_vsel_to_uv,
	.uv_to_vsel = omap_fan535503_uv_to_vsel,
पूर्ण;

पूर्णांक __init omap4_cpcap_init(व्योम)
अणु
	काष्ठा voltageकरोमुख्य *voltdm;

	अगर (!of_find_compatible_node(शून्य, शून्य, "motorola,cpcap"))
		वापस -ENODEV;

	voltdm = voltdm_lookup("mpu");
	omap_voltage_रेजिस्टर_pmic(voltdm, &omap443x_max8952_mpu);

	अगर (of_machine_is_compatible("motorola,droid-bionic")) अणु
		voltdm = voltdm_lookup("core");
		omap_voltage_रेजिस्टर_pmic(voltdm, &omap_cpcap_core);

		voltdm = voltdm_lookup("iva");
		omap_voltage_रेजिस्टर_pmic(voltdm, &omap_cpcap_iva);
	पूर्ण अन्यथा अणु
		voltdm = voltdm_lookup("core");
		omap_voltage_रेजिस्टर_pmic(voltdm, &omap4_fan_core);

		voltdm = voltdm_lookup("iva");
		omap_voltage_रेजिस्टर_pmic(voltdm, &omap4_fan_iva);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init cpcap_late_init(व्योम)
अणु
	omap4_vc_set_pmic_संकेतing(PWRDM_POWER_RET);

	वापस 0;
पूर्ण
omap_late_initcall(cpcap_late_init);
