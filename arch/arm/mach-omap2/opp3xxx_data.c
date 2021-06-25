<शैली गुरु>
/*
 * OMAP3 OPP table definitions.
 *
 * Copyright (C) 2009-2010 Texas Instruments Incorporated - https://www.ti.com/
 *	Nishanth Menon
 *	Kevin Hilman
 * Copyright (C) 2010-2011 Nokia Corporation.
 *      Eduarकरो Valentin
 *      Paul Walmsley
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
#समावेश <linux/module.h>

#समावेश "soc.h"
#समावेश "control.h"
#समावेश "omap_opp_data.h"
#समावेश "pm.h"

/* 34xx */

/* VDD1 */

#घोषणा OMAP3430_VDD_MPU_OPP1_UV		975000
#घोषणा OMAP3430_VDD_MPU_OPP2_UV		1075000
#घोषणा OMAP3430_VDD_MPU_OPP3_UV		1200000
#घोषणा OMAP3430_VDD_MPU_OPP4_UV		1270000
#घोषणा OMAP3430_VDD_MPU_OPP5_UV		1350000

काष्ठा omap_volt_data omap34xx_vddmpu_volt_data[] = अणु
	VOLT_DATA_DEFINE(OMAP3430_VDD_MPU_OPP1_UV, OMAP343X_CONTROL_FUSE_OPP1_VDD1, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3430_VDD_MPU_OPP2_UV, OMAP343X_CONTROL_FUSE_OPP2_VDD1, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3430_VDD_MPU_OPP3_UV, OMAP343X_CONTROL_FUSE_OPP3_VDD1, 0xf9, 0x18),
	VOLT_DATA_DEFINE(OMAP3430_VDD_MPU_OPP4_UV, OMAP343X_CONTROL_FUSE_OPP4_VDD1, 0xf9, 0x18),
	VOLT_DATA_DEFINE(OMAP3430_VDD_MPU_OPP5_UV, OMAP343X_CONTROL_FUSE_OPP5_VDD1, 0xf9, 0x18),
	VOLT_DATA_DEFINE(0, 0, 0, 0),
पूर्ण;

/* VDD2 */

#घोषणा OMAP3430_VDD_CORE_OPP1_UV		975000
#घोषणा OMAP3430_VDD_CORE_OPP2_UV		1050000
#घोषणा OMAP3430_VDD_CORE_OPP3_UV		1150000

काष्ठा omap_volt_data omap34xx_vddcore_volt_data[] = अणु
	VOLT_DATA_DEFINE(OMAP3430_VDD_CORE_OPP1_UV, OMAP343X_CONTROL_FUSE_OPP1_VDD2, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3430_VDD_CORE_OPP2_UV, OMAP343X_CONTROL_FUSE_OPP2_VDD2, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3430_VDD_CORE_OPP3_UV, OMAP343X_CONTROL_FUSE_OPP3_VDD2, 0xf9, 0x18),
	VOLT_DATA_DEFINE(0, 0, 0, 0),
पूर्ण;

/* 36xx */

/* VDD1 */

#घोषणा OMAP3630_VDD_MPU_OPP50_UV		1012500
#घोषणा OMAP3630_VDD_MPU_OPP100_UV		1200000
#घोषणा OMAP3630_VDD_MPU_OPP120_UV		1325000
#घोषणा OMAP3630_VDD_MPU_OPP1G_UV		1375000

काष्ठा omap_volt_data omap36xx_vddmpu_volt_data[] = अणु
	VOLT_DATA_DEFINE(OMAP3630_VDD_MPU_OPP50_UV, OMAP3630_CONTROL_FUSE_OPP50_VDD1, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3630_VDD_MPU_OPP100_UV, OMAP3630_CONTROL_FUSE_OPP100_VDD1, 0xf9, 0x16),
	VOLT_DATA_DEFINE(OMAP3630_VDD_MPU_OPP120_UV, OMAP3630_CONTROL_FUSE_OPP120_VDD1, 0xfa, 0x23),
	VOLT_DATA_DEFINE(OMAP3630_VDD_MPU_OPP1G_UV, OMAP3630_CONTROL_FUSE_OPP1G_VDD1, 0xfa, 0x27),
	VOLT_DATA_DEFINE(0, 0, 0, 0),
पूर्ण;

/* VDD2 */

#घोषणा OMAP3630_VDD_CORE_OPP50_UV		1000000
#घोषणा OMAP3630_VDD_CORE_OPP100_UV		1200000

काष्ठा omap_volt_data omap36xx_vddcore_volt_data[] = अणु
	VOLT_DATA_DEFINE(OMAP3630_VDD_CORE_OPP50_UV, OMAP3630_CONTROL_FUSE_OPP50_VDD2, 0xf4, 0x0c),
	VOLT_DATA_DEFINE(OMAP3630_VDD_CORE_OPP100_UV, OMAP3630_CONTROL_FUSE_OPP100_VDD2, 0xf9, 0x16),
	VOLT_DATA_DEFINE(0, 0, 0, 0),
पूर्ण;
