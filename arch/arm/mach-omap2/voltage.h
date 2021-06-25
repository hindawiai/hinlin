<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * OMAP Voltage Management Routines
 *
 * Author: Thara Gopinath	<thara@ti.com>
 *
 * Copyright (C) 2009 Texas Instruments, Inc.
 * Thara Gopinath <thara@ti.com>
 */

#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_VOLTAGE_H
#घोषणा __ARCH_ARM_MACH_OMAP2_VOLTAGE_H

#समावेश <linux/err.h>

#समावेश <linux/platक्रमm_data/voltage-omap.h>

#समावेश "vc.h"
#समावेश "vp.h"

काष्ठा घातerकरोमुख्य;

/*
 * OMAP3 GENERIC setup बार. Revisit to see अगर these needs to be
 * passed from board or PMIC file
 */
#घोषणा OMAP3_CLKSETUP		0xff
#घोषणा OMAP3_VOLTOFFSET	0xff
#घोषणा OMAP3_VOLTSETUP2	0xff

/**
 * काष्ठा omap_vfsm_instance - per-voltage manager FSM रेजिस्टर/bitfield
 * data
 * @voltsetup_mask: SETUP_TIME* biपंचांगask in the PRM_VOLTSETUP* रेजिस्टर
 * @voltsetup_reg: रेजिस्टर offset of PRM_VOLTSETUP from PRM base
 * @voltsetup_off_reg: रेजिस्टर offset of PRM_VOLTSETUP_OFF from PRM base
 *
 * XXX What about VOLTOFFSET/VOLTCTRL?
 */
काष्ठा omap_vfsm_instance अणु
	u32 voltsetup_mask;
	u8 voltsetup_reg;
	u8 voltsetup_off_reg;
पूर्ण;

/**
 * काष्ठा voltageकरोमुख्य - omap voltage करोमुख्य global काष्ठाure.
 * @name: Name of the voltage करोमुख्य which can be used as a unique identअगरier.
 * @scalable: Whether or not this voltage करोमुख्य is scalable
 * @node: list_head linking all voltage करोमुख्यs
 * @vc: poपूर्णांकer to VC channel associated with this voltageकरोमुख्य
 * @vp: poपूर्णांकer to VP associated with this voltageकरोमुख्य
 * @पढ़ो: पढ़ो a VC/VP रेजिस्टर
 * @ग_लिखो: ग_लिखो a VC/VP रेजिस्टर
 * @पढ़ो: पढ़ो-modअगरy-ग_लिखो a VC/VP रेजिस्टर
 * @sys_clk: प्रणाली घड़ी name/frequency, used क्रम various timing calculations
 * @scale: function used to scale the voltage of the voltageकरोमुख्य
 * @nominal_volt: current nominal voltage क्रम this voltage करोमुख्य
 * @volt_data: voltage table having the distinct voltages supported
 *             by the करोमुख्य and other associated per voltage data.
 */
काष्ठा voltageकरोमुख्य अणु
	अक्षर *name;
	bool scalable;
	काष्ठा list_head node;
	काष्ठा omap_vc_channel *vc;
	स्थिर काष्ठा omap_vfsm_instance *vfsm;
	काष्ठा omap_vp_instance *vp;
	काष्ठा omap_voltdm_pmic *pmic;
	काष्ठा omap_vp_param *vp_param;
	काष्ठा omap_vc_param *vc_param;

	/* VC/VP रेजिस्टर access functions: SoC specअगरic */
	u32 (*पढ़ो) (u8 offset);
	व्योम (*ग_लिखो) (u32 val, u8 offset);
	u32 (*rmw)(u32 mask, u32 bits, u8 offset);

	जोड़ अणु
		स्थिर अक्षर *name;
		u32 rate;
	पूर्ण sys_clk;

	पूर्णांक (*scale) (काष्ठा voltageकरोमुख्य *voltdm,
		      अचिन्हित दीर्घ target_volt);

	u32 nominal_volt;
	काष्ठा omap_volt_data *volt_data;
पूर्ण;

/* Min and max voltages from OMAP perspective */
#घोषणा OMAP3430_VP1_VLIMITTO_VDDMIN	850000
#घोषणा OMAP3430_VP1_VLIMITTO_VDDMAX	1425000
#घोषणा OMAP3430_VP2_VLIMITTO_VDDMIN	900000
#घोषणा OMAP3430_VP2_VLIMITTO_VDDMAX	1150000

#घोषणा OMAP3630_VP1_VLIMITTO_VDDMIN	900000
#घोषणा OMAP3630_VP1_VLIMITTO_VDDMAX	1350000
#घोषणा OMAP3630_VP2_VLIMITTO_VDDMIN	900000
#घोषणा OMAP3630_VP2_VLIMITTO_VDDMAX	1200000

#घोषणा OMAP4_VP_MPU_VLIMITTO_VDDMIN	830000
#घोषणा OMAP4_VP_MPU_VLIMITTO_VDDMAX	1410000
#घोषणा OMAP4_VP_IVA_VLIMITTO_VDDMIN	830000
#घोषणा OMAP4_VP_IVA_VLIMITTO_VDDMAX	1260000
#घोषणा OMAP4_VP_CORE_VLIMITTO_VDDMIN	830000
#घोषणा OMAP4_VP_CORE_VLIMITTO_VDDMAX	1200000

/**
 * काष्ठा omap_voltdm_pmic - PMIC specअगरic data required by voltage driver.
 * @slew_rate:	PMIC slew rate (in uv/us)
 * @step_size:	PMIC voltage step size (in uv)
 * @i2c_slave_addr: I2C slave address of PMIC
 * @volt_reg_addr: voltage configuration रेजिस्टर address
 * @cmd_reg_addr: command (on, on-LP, ret, off) configuration रेजिस्टर address
 * @i2c_high_speed: whether VC uses I2C high-speed mode to PMIC
 * @i2c_mcode: master code value क्रम I2C high-speed preamble transmission
 * @vsel_to_uv:	PMIC API to convert vsel value to actual voltage in uV.
 * @uv_to_vsel:	PMIC API to convert voltage in uV to vsel value.
 */
काष्ठा omap_voltdm_pmic अणु
	पूर्णांक slew_rate;
	पूर्णांक step_size;
	u16 i2c_slave_addr;
	u16 volt_reg_addr;
	u16 cmd_reg_addr;
	u8 vp_erroroffset;
	u8 vp_vstepmin;
	u8 vp_vstepmax;
	u32 vddmin;
	u32 vddmax;
	u8 vp_समयout_us;
	bool i2c_high_speed;
	u32 i2c_pad_load;
	u8 i2c_mcode;
	अचिन्हित दीर्घ (*vsel_to_uv) (स्थिर u8 vsel);
	u8 (*uv_to_vsel) (अचिन्हित दीर्घ uV);
पूर्ण;

काष्ठा omap_vp_param अणु
	u32 vddmax;
	u32 vddmin;
पूर्ण;

काष्ठा omap_vc_param अणु
	u32 on;
	u32 onlp;
	u32 ret;
	u32 off;
पूर्ण;

व्योम omap_voltage_get_volttable(काष्ठा voltageकरोमुख्य *voltdm,
		काष्ठा omap_volt_data **volt_data);
काष्ठा omap_volt_data *omap_voltage_get_voltdata(काष्ठा voltageकरोमुख्य *voltdm,
		अचिन्हित दीर्घ volt);
पूर्णांक omap_voltage_रेजिस्टर_pmic(काष्ठा voltageकरोमुख्य *voltdm,
			       काष्ठा omap_voltdm_pmic *pmic);
पूर्णांक omap_voltage_late_init(व्योम);

बाह्य व्योम omap2xxx_voltageकरोमुख्यs_init(व्योम);
बाह्य व्योम omap3xxx_voltageकरोमुख्यs_init(व्योम);
बाह्य व्योम omap44xx_voltageकरोमुख्यs_init(व्योम);
बाह्य व्योम omap54xx_voltageकरोमुख्यs_init(व्योम);

काष्ठा voltageकरोमुख्य *voltdm_lookup(स्थिर अक्षर *name);
व्योम voltdm_init(काष्ठा voltageकरोमुख्य **voltdm_list);
पूर्णांक voltdm_add_pwrdm(काष्ठा voltageकरोमुख्य *voltdm, काष्ठा घातerकरोमुख्य *pwrdm);
पूर्णांक voltdm_scale(काष्ठा voltageकरोमुख्य *voltdm, अचिन्हित दीर्घ target_volt);
व्योम voltdm_reset(काष्ठा voltageकरोमुख्य *voltdm);
अचिन्हित दीर्घ voltdm_get_voltage(काष्ठा voltageकरोमुख्य *voltdm);
#पूर्ण_अगर
