<शैली गुरु>
/*
 * OMAP SoC specअगरic OPP Data helpers
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 *	Kevin Hilman
 * Copyright (C) 2010 Nokia Corporation.
 *      Eduarकरो Valentin
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित __ARCH_ARM_MACH_OMAP2_OMAP_OPP_DATA_H
#घोषणा __ARCH_ARM_MACH_OMAP2_OMAP_OPP_DATA_H

#समावेश "omap_hwmod.h"

#समावेश "voltage.h"

/*
 * *BIG FAT WARNING*:
 * USE the following ONLY in opp data initialization common to an SoC.
 * DO NOT USE these in board files/pm core etc.
 */

/**
 * काष्ठा omap_opp_def - OMAP OPP Definition
 * @hwmod_name:	Name of the hwmod क्रम this करोमुख्य
 * @freq:	Frequency in hertz corresponding to this OPP
 * @u_volt:	Nominal voltage in microvolts corresponding to this OPP
 * @शेष_available:	True/false - is this OPP available by शेष
 *
 * OMAP SOCs have a standard set of tuples consisting of frequency and voltage
 * pairs that the device will support per voltage करोमुख्य. This is called
 * Operating Poपूर्णांकs or OPP. The actual definitions of OMAP Operating Poपूर्णांकs
 * varies over silicon within the same family of devices. For a specअगरic
 * करोमुख्य, you can have a set of अणुfrequency, voltageपूर्ण pairs and this is denoted
 * by an array of omap_opp_def. As the kernel boots and more inक्रमmation is
 * available, a set of these are activated based on the precise nature of
 * device the kernel boots up on. It is पूर्णांकeresting to remember that each IP
 * which beदीर्घs to a voltage करोमुख्य may define their own set of OPPs on top
 * of this - but this is handled by the appropriate driver.
 */
काष्ठा omap_opp_def अणु
	अक्षर *hwmod_name;

	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ u_volt;

	bool शेष_available;
पूर्ण;

/*
 * Initialization wrapper used to define an OPP क्रम OMAP variants.
 */
#घोषणा OPP_INITIALIZER(_hwmod_name, _enabled, _freq, _uv)	\
अणु								\
	.hwmod_name	= _hwmod_name,				\
	.शेष_available	= _enabled,			\
	.freq		= _freq,				\
	.u_volt		= _uv,					\
पूर्ण

/*
 * Initialization wrapper used to define SmartReflex process data
 * XXX Is this needed?  Just use C99 initializers in data files?
 */
#घोषणा VOLT_DATA_DEFINE(_v_nom, _efuse_offs, _errminlimit, _errgain)  \
अणु								       \
	.volt_nominal	= _v_nom,				       \
	.sr_efuse_offs	= _efuse_offs,				       \
	.sr_errminlimit = _errminlimit,				       \
	.vp_errgain	= _errgain				       \
पूर्ण

/* Use this to initialize the शेष table */
बाह्य पूर्णांक __init omap_init_opp_table(काष्ठा omap_opp_def *opp_def,
		u32 opp_def_size);


बाह्य काष्ठा omap_volt_data omap34xx_vddmpu_volt_data[];
बाह्य काष्ठा omap_volt_data omap34xx_vddcore_volt_data[];
बाह्य काष्ठा omap_volt_data omap36xx_vddmpu_volt_data[];
बाह्य काष्ठा omap_volt_data omap36xx_vddcore_volt_data[];

बाह्य काष्ठा omap_volt_data omap443x_vdd_mpu_volt_data[];
बाह्य काष्ठा omap_volt_data omap443x_vdd_iva_volt_data[];
बाह्य काष्ठा omap_volt_data omap443x_vdd_core_volt_data[];
बाह्य काष्ठा omap_volt_data omap446x_vdd_mpu_volt_data[];
बाह्य काष्ठा omap_volt_data omap446x_vdd_iva_volt_data[];
बाह्य काष्ठा omap_volt_data omap446x_vdd_core_volt_data[];

#पूर्ण_अगर		/* __ARCH_ARM_MACH_OMAP2_OMAP_OPP_DATA_H */
