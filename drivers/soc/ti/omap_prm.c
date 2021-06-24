<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OMAP2+ PRM driver
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com/
 *	Tero Kristo <t-kristo@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_घड़ी.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/delay.h>

#समावेश <linux/platक्रमm_data/ti-prm.h>

क्रमागत omap_prm_करोमुख्य_mode अणु
	OMAP_PRMD_OFF,
	OMAP_PRMD_RETENTION,
	OMAP_PRMD_ON_INACTIVE,
	OMAP_PRMD_ON_ACTIVE,
पूर्ण;

काष्ठा omap_prm_करोमुख्य_map अणु
	अचिन्हित पूर्णांक usable_modes;	/* Mask of hardware supported modes */
	अचिन्हित दीर्घ statechange:1;	/* Optional low-घातer state change */
	अचिन्हित दीर्घ logicretstate:1;	/* Optional logic off mode */
पूर्ण;

काष्ठा omap_prm_करोमुख्य अणु
	काष्ठा device *dev;
	काष्ठा omap_prm *prm;
	काष्ठा generic_pm_करोमुख्य pd;
	u16 pwrstctrl;
	u16 pwrstst;
	स्थिर काष्ठा omap_prm_करोमुख्य_map *cap;
	u32 pwrstctrl_saved;
	अचिन्हित पूर्णांक uses_pm_clk:1;
पूर्ण;

काष्ठा omap_rst_map अणु
	s8 rst;
	s8 st;
पूर्ण;

काष्ठा omap_prm_data अणु
	u32 base;
	स्थिर अक्षर *name;
	स्थिर अक्षर *clkdm_name;
	u16 pwrstctrl;
	u16 pwrstst;
	स्थिर काष्ठा omap_prm_करोमुख्य_map *dmap;
	u16 rstctrl;
	u16 rstst;
	स्थिर काष्ठा omap_rst_map *rsपंचांगap;
	u8 flags;
पूर्ण;

काष्ठा omap_prm अणु
	स्थिर काष्ठा omap_prm_data *data;
	व्योम __iomem *base;
	काष्ठा omap_prm_करोमुख्य *prmd;
पूर्ण;

काष्ठा omap_reset_data अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा omap_prm *prm;
	u32 mask;
	spinlock_t lock;
	काष्ठा घड़ीकरोमुख्य *clkdm;
	काष्ठा device *dev;
पूर्ण;

#घोषणा genpd_to_prm_करोमुख्य(gpd) container_of(gpd, काष्ठा omap_prm_करोमुख्य, pd)
#घोषणा to_omap_reset_data(p) container_of((p), काष्ठा omap_reset_data, rcdev)

#घोषणा OMAP_MAX_RESETS		8
#घोषणा OMAP_RESET_MAX_WAIT	10000

#घोषणा OMAP_PRM_HAS_RSTCTRL	BIT(0)
#घोषणा OMAP_PRM_HAS_RSTST	BIT(1)
#घोषणा OMAP_PRM_HAS_NO_CLKDM	BIT(2)
#घोषणा OMAP_PRM_RET_WHEN_IDLE	BIT(3)

#घोषणा OMAP_PRM_HAS_RESETS	(OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_RSTST)

#घोषणा PRM_STATE_MAX_WAIT	10000
#घोषणा PRM_LOGICRETSTATE	BIT(2)
#घोषणा PRM_LOWPOWERSTATECHANGE	BIT(4)
#घोषणा PRM_POWERSTATE_MASK	OMAP_PRMD_ON_ACTIVE

#घोषणा PRM_ST_INTRANSITION	BIT(20)

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_all = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE) | BIT(OMAP_PRMD_ON_INACTIVE) |
			BIT(OMAP_PRMD_RETENTION) | BIT(OMAP_PRMD_OFF),
	.statechange = 1,
	.logicretstate = 1,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_noinact = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE) | BIT(OMAP_PRMD_RETENTION) |
			BIT(OMAP_PRMD_OFF),
	.statechange = 1,
	.logicretstate = 1,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_nooff = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE) | BIT(OMAP_PRMD_ON_INACTIVE) |
			BIT(OMAP_PRMD_RETENTION),
	.statechange = 1,
	.logicretstate = 1,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_onoff_noस्वतः = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE) | BIT(OMAP_PRMD_OFF),
	.statechange = 1,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_alwon = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE),
पूर्ण;

अटल स्थिर काष्ठा omap_prm_करोमुख्य_map omap_prm_reton = अणु
	.usable_modes = BIT(OMAP_PRMD_ON_ACTIVE) | BIT(OMAP_PRMD_RETENTION),
	.statechange = 1,
	.logicretstate = 1,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map rst_map_0[] = अणु
	अणु .rst = 0, .st = 0 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map rst_map_01[] = अणु
	अणु .rst = 0, .st = 0 पूर्ण,
	अणु .rst = 1, .st = 1 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map rst_map_012[] = अणु
	अणु .rst = 0, .st = 0 पूर्ण,
	अणु .rst = 1, .st = 1 पूर्ण,
	अणु .rst = 2, .st = 2 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_data omap4_prm_data[] = अणु
	अणु
		.name = "mpu", .base = 0x4a306300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
	पूर्ण,
	अणु
		.name = "tesla", .base = 0x4a306400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "abe", .base = 0x4a306500,
		.pwrstctrl = 0, .pwrstst = 0x4, .dmap = &omap_prm_all,
	पूर्ण,
	अणु
		.name = "always_on_core", .base = 0x4a306600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "core", .base = 0x4a306700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
		.rstctrl = 0x210, .rstst = 0x214, .clkdm_name = "ducati",
		.rsपंचांगap = rst_map_012,
		.flags = OMAP_PRM_RET_WHEN_IDLE,
	पूर्ण,
	अणु
		.name = "ivahd", .base = 0x4a306f00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_012
	पूर्ण,
	अणु
		.name = "cam", .base = 0x4a307000,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "dss", .base = 0x4a307100,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact
	पूर्ण,
	अणु
		.name = "gfx", .base = 0x4a307200,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "l3init", .base = 0x4a307300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton
	पूर्ण,
	अणु
		.name = "l4per", .base = 0x4a307400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
		.flags = OMAP_PRM_RET_WHEN_IDLE,
	पूर्ण,
	अणु
		.name = "cefuse", .base = 0x4a307600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "wkup", .base = 0x4a307700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon
	पूर्ण,
	अणु
		.name = "emu", .base = 0x4a307900,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "device", .base = 0x4a307b00,
		.rstctrl = 0x0, .rstst = 0x4, .rsपंचांगap = rst_map_01,
		.flags = OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_data omap5_prm_data[] = अणु
	अणु
		.name = "mpu", .base = 0x4ae06300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
	पूर्ण,
	अणु
		.name = "dsp", .base = 0x4ae06400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "abe", .base = 0x4ae06500,
		.pwrstctrl = 0, .pwrstst = 0x4, .dmap = &omap_prm_nooff,
	पूर्ण,
	अणु
		.name = "coreaon", .base = 0x4ae06600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon
	पूर्ण,
	अणु
		.name = "core", .base = 0x4ae06700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
		.rstctrl = 0x210, .rstst = 0x214, .clkdm_name = "ipu",
		.rsपंचांगap = rst_map_012
	पूर्ण,
	अणु
		.name = "iva", .base = 0x4ae07200,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_012
	पूर्ण,
	अणु
		.name = "cam", .base = 0x4ae07300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "dss", .base = 0x4ae07400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact
	पूर्ण,
	अणु
		.name = "gpu", .base = 0x4ae07500,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "l3init", .base = 0x4ae07600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton
	पूर्ण,
	अणु
		.name = "custefuse", .base = 0x4ae07700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "wkupaon", .base = 0x4ae07800,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon
	पूर्ण,
	अणु
		.name = "emu", .base = 0x4ae07a00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः
	पूर्ण,
	अणु
		.name = "device", .base = 0x4ae07c00,
		.rstctrl = 0x0, .rstst = 0x4, .rsपंचांगap = rst_map_01,
		.flags = OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_data dra7_prm_data[] = अणु
	अणु
		.name = "mpu", .base = 0x4ae06300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_reton,
	पूर्ण,
	अणु
		.name = "dsp1", .base = 0x4ae06400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01,
	पूर्ण,
	अणु
		.name = "ipu", .base = 0x4ae06500,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_012,
		.clkdm_name = "ipu1"
	पूर्ण,
	अणु
		.name = "coreaon", .base = 0x4ae06628,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "core", .base = 0x4ae06700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
		.rstctrl = 0x210, .rstst = 0x214, .rsपंचांगap = rst_map_012,
		.clkdm_name = "ipu2"
	पूर्ण,
	अणु
		.name = "iva", .base = 0x4ae06f00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_012,
	पूर्ण,
	अणु
		.name = "cam", .base = 0x4ae07000,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "dss", .base = 0x4ae07100,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "gpu", .base = 0x4ae07200,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "l3init", .base = 0x4ae07300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01,
		.clkdm_name = "pcie"
	पूर्ण,
	अणु
		.name = "l4per", .base = 0x4ae07400,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "custefuse", .base = 0x4ae07600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "wkupaon", .base = 0x4ae07724,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "emu", .base = 0x4ae07900,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "dsp2", .base = 0x4ae07b00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "eve1", .base = 0x4ae07b40,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "eve2", .base = 0x4ae07b80,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "eve3", .base = 0x4ae07bc0,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "eve4", .base = 0x4ae07c00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_01
	पूर्ण,
	अणु
		.name = "rtc", .base = 0x4ae07c60,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "vpe", .base = 0x4ae07c80,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map am3_per_rst_map[] = अणु
	अणु .rst = 1 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map am3_wkup_rst_map[] = अणु
	अणु .rst = 3, .st = 5 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_data am3_prm_data[] = अणु
	अणु
		.name = "per", .base = 0x44e00c00,
		.pwrstctrl = 0xc, .pwrstst = 0x8, .dmap = &omap_prm_noinact,
		.rstctrl = 0x0, .rsपंचांगap = am3_per_rst_map,
		.flags = OMAP_PRM_HAS_RSTCTRL, .clkdm_name = "pruss_ocp"
	पूर्ण,
	अणु
		.name = "wkup", .base = 0x44e00d00,
		.pwrstctrl = 0x4, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
		.rstctrl = 0x0, .rstst = 0xc, .rsपंचांगap = am3_wkup_rst_map,
		.flags = OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु
		.name = "mpu", .base = 0x44e00e00,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
	पूर्ण,
	अणु
		.name = "device", .base = 0x44e00f00,
		.rstctrl = 0x0, .rstst = 0x8, .rsपंचांगap = rst_map_01,
		.flags = OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु
		.name = "rtc", .base = 0x44e01000,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "gfx", .base = 0x44e01100,
		.pwrstctrl = 0, .pwrstst = 0x10, .dmap = &omap_prm_noinact,
		.rstctrl = 0x4, .rstst = 0x14, .rsपंचांगap = rst_map_0, .clkdm_name = "gfx_l3",
	पूर्ण,
	अणु
		.name = "cefuse", .base = 0x44e01200,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map am4_per_rst_map[] = अणु
	अणु .rst = 1, .st = 0 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_rst_map am4_device_rst_map[] = अणु
	अणु .rst = 0, .st = 1 पूर्ण,
	अणु .rst = 1, .st = 0 पूर्ण,
	अणु .rst = -1 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा omap_prm_data am4_prm_data[] = अणु
	अणु
		.name = "mpu", .base = 0x44df0300,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
	पूर्ण,
	अणु
		.name = "gfx", .base = 0x44df0400,
		.pwrstctrl = 0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = rst_map_0, .clkdm_name = "gfx_l3",
	पूर्ण,
	अणु
		.name = "rtc", .base = 0x44df0500,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "tamper", .base = 0x44df0600,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
	पूर्ण,
	अणु
		.name = "cefuse", .base = 0x44df0700,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_onoff_noस्वतः,
	पूर्ण,
	अणु
		.name = "per", .base = 0x44df0800,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_noinact,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = am4_per_rst_map,
		.clkdm_name = "pruss_ocp"
	पूर्ण,
	अणु
		.name = "wkup", .base = 0x44df2000,
		.pwrstctrl = 0x0, .pwrstst = 0x4, .dmap = &omap_prm_alwon,
		.rstctrl = 0x10, .rstst = 0x14, .rsपंचांगap = am3_wkup_rst_map,
		.flags = OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु
		.name = "device", .base = 0x44df4000,
		.rstctrl = 0x0, .rstst = 0x4, .rsपंचांगap = am4_device_rst_map,
		.flags = OMAP_PRM_HAS_RSTCTRL | OMAP_PRM_HAS_NO_CLKDM
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_prm_id_table[] = अणु
	अणु .compatible = "ti,omap4-prm-inst", .data = omap4_prm_data पूर्ण,
	अणु .compatible = "ti,omap5-prm-inst", .data = omap5_prm_data पूर्ण,
	अणु .compatible = "ti,dra7-prm-inst", .data = dra7_prm_data पूर्ण,
	अणु .compatible = "ti,am3-prm-inst", .data = am3_prm_data पूर्ण,
	अणु .compatible = "ti,am4-prm-inst", .data = am4_prm_data पूर्ण,
	अणु पूर्ण,
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम omap_prm_करोमुख्य_show_state(काष्ठा omap_prm_करोमुख्य *prmd,
				       स्थिर अक्षर *desc)
अणु
	dev_dbg(prmd->dev, "%s %s: %08x/%08x\n",
		prmd->pd.name, desc,
		पढ़ोl_relaxed(prmd->prm->base + prmd->pwrstctrl),
		पढ़ोl_relaxed(prmd->prm->base + prmd->pwrstst));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम omap_prm_करोमुख्य_show_state(काष्ठा omap_prm_करोमुख्य *prmd,
					      स्थिर अक्षर *desc)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक omap_prm_करोमुख्य_घातer_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा omap_prm_करोमुख्य *prmd;
	पूर्णांक ret;
	u32 v, mode;

	prmd = genpd_to_prm_करोमुख्य(करोमुख्य);
	अगर (!prmd->cap)
		वापस 0;

	omap_prm_करोमुख्य_show_state(prmd, "on: previous state");

	अगर (prmd->pwrstctrl_saved)
		v = prmd->pwrstctrl_saved;
	अन्यथा
		v = पढ़ोl_relaxed(prmd->prm->base + prmd->pwrstctrl);

	अगर (prmd->prm->data->flags & OMAP_PRM_RET_WHEN_IDLE)
		mode = OMAP_PRMD_RETENTION;
	अन्यथा
		mode = OMAP_PRMD_ON_ACTIVE;

	ग_लिखोl_relaxed((v & ~PRM_POWERSTATE_MASK) | mode,
		       prmd->prm->base + prmd->pwrstctrl);

	/* रुको क्रम the transition bit to get cleared */
	ret = पढ़ोl_relaxed_poll_समयout(prmd->prm->base + prmd->pwrstst,
					 v, !(v & PRM_ST_INTRANSITION), 1,
					 PRM_STATE_MAX_WAIT);
	अगर (ret)
		dev_err(prmd->dev, "%s: %s timed out\n",
			prmd->pd.name, __func__);

	omap_prm_करोमुख्य_show_state(prmd, "on: new state");

	वापस ret;
पूर्ण

/* No need to check क्रम holes in the mask क्रम the lowest mode */
अटल पूर्णांक omap_prm_करोमुख्य_find_lowest(काष्ठा omap_prm_करोमुख्य *prmd)
अणु
	वापस __ffs(prmd->cap->usable_modes);
पूर्ण

अटल पूर्णांक omap_prm_करोमुख्य_घातer_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा omap_prm_करोमुख्य *prmd;
	पूर्णांक ret;
	u32 v;

	prmd = genpd_to_prm_करोमुख्य(करोमुख्य);
	अगर (!prmd->cap)
		वापस 0;

	omap_prm_करोमुख्य_show_state(prmd, "off: previous state");

	v = पढ़ोl_relaxed(prmd->prm->base + prmd->pwrstctrl);
	prmd->pwrstctrl_saved = v;

	v &= ~PRM_POWERSTATE_MASK;
	v |= omap_prm_करोमुख्य_find_lowest(prmd);

	अगर (prmd->cap->statechange)
		v |= PRM_LOWPOWERSTATECHANGE;
	अगर (prmd->cap->logicretstate)
		v &= ~PRM_LOGICRETSTATE;
	अन्यथा
		v |= PRM_LOGICRETSTATE;

	ग_लिखोl_relaxed(v, prmd->prm->base + prmd->pwrstctrl);

	/* रुको क्रम the transition bit to get cleared */
	ret = पढ़ोl_relaxed_poll_समयout(prmd->prm->base + prmd->pwrstst,
					 v, !(v & PRM_ST_INTRANSITION), 1,
					 PRM_STATE_MAX_WAIT);
	अगर (ret)
		dev_warn(prmd->dev, "%s: %s timed out\n",
			 __func__, prmd->pd.name);

	omap_prm_करोमुख्य_show_state(prmd, "off: new state");

	वापस 0;
पूर्ण

/*
 * Note that ti-sysc alपढ़ोy manages the module घड़ीs separately so
 * no need to manage those. Interconnect instances need घड़ीs managed
 * क्रम simple-pm-bus.
 */
अटल पूर्णांक omap_prm_करोमुख्य_attach_घड़ी(काष्ठा device *dev,
					काष्ठा omap_prm_करोमुख्य *prmd)
अणु
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक error;

	अगर (!of_device_is_compatible(np, "simple-pm-bus"))
		वापस 0;

	अगर (!of_property_पढ़ो_bool(np, "clocks"))
		वापस 0;

	error = pm_clk_create(dev);
	अगर (error)
		वापस error;

	error = of_pm_clk_add_clks(dev);
	अगर (error < 0) अणु
		pm_clk_destroy(dev);
		वापस error;
	पूर्ण

	prmd->uses_pm_clk = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_prm_करोमुख्य_attach_dev(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				      काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *genpd_data;
	काष्ठा of_phandle_args pd_args;
	काष्ठा omap_prm_करोमुख्य *prmd;
	काष्ठा device_node *np;
	पूर्णांक ret;

	prmd = genpd_to_prm_करोमुख्य(करोमुख्य);
	np = dev->of_node;

	ret = of_parse_phandle_with_args(np, "power-domains",
					 "#power-domain-cells", 0, &pd_args);
	अगर (ret < 0)
		वापस ret;

	अगर (pd_args.args_count != 0)
		dev_warn(dev, "%s: unusupported #power-domain-cells: %i\n",
			 prmd->pd.name, pd_args.args_count);

	genpd_data = dev_gpd_data(dev);
	genpd_data->data = शून्य;

	ret = omap_prm_करोमुख्य_attach_घड़ी(dev, prmd);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम omap_prm_करोमुख्य_detach_dev(काष्ठा generic_pm_करोमुख्य *करोमुख्य,
				       काष्ठा device *dev)
अणु
	काष्ठा generic_pm_करोमुख्य_data *genpd_data;
	काष्ठा omap_prm_करोमुख्य *prmd;

	prmd = genpd_to_prm_करोमुख्य(करोमुख्य);
	अगर (prmd->uses_pm_clk)
		pm_clk_destroy(dev);
	genpd_data = dev_gpd_data(dev);
	genpd_data->data = शून्य;
पूर्ण

अटल पूर्णांक omap_prm_करोमुख्य_init(काष्ठा device *dev, काष्ठा omap_prm *prm)
अणु
	काष्ठा omap_prm_करोमुख्य *prmd;
	काष्ठा device_node *np = dev->of_node;
	स्थिर काष्ठा omap_prm_data *data;
	स्थिर अक्षर *name;
	पूर्णांक error;

	अगर (!of_find_property(dev->of_node, "#power-domain-cells", शून्य))
		वापस 0;

	of_node_put(dev->of_node);

	prmd = devm_kzalloc(dev, माप(*prmd), GFP_KERNEL);
	अगर (!prmd)
		वापस -ENOMEM;

	data = prm->data;
	name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "prm_%s",
			      data->name);

	prmd->dev = dev;
	prmd->prm = prm;
	prmd->cap = prmd->prm->data->dmap;
	prmd->pwrstctrl = prmd->prm->data->pwrstctrl;
	prmd->pwrstst = prmd->prm->data->pwrstst;

	prmd->pd.name = name;
	prmd->pd.घातer_on = omap_prm_करोमुख्य_घातer_on;
	prmd->pd.घातer_off = omap_prm_करोमुख्य_घातer_off;
	prmd->pd.attach_dev = omap_prm_करोमुख्य_attach_dev;
	prmd->pd.detach_dev = omap_prm_करोमुख्य_detach_dev;
	prmd->pd.flags = GENPD_FLAG_PM_CLK;

	pm_genpd_init(&prmd->pd, शून्य, true);
	error = of_genpd_add_provider_simple(np, &prmd->pd);
	अगर (error)
		pm_genpd_हटाओ(&prmd->pd);
	अन्यथा
		prm->prmd = prmd;

	वापस error;
पूर्ण

अटल bool _is_valid_reset(काष्ठा omap_reset_data *reset, अचिन्हित दीर्घ id)
अणु
	अगर (reset->mask & BIT(id))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक omap_reset_get_st_bit(काष्ठा omap_reset_data *reset,
				 अचिन्हित दीर्घ id)
अणु
	स्थिर काष्ठा omap_rst_map *map = reset->prm->data->rsपंचांगap;

	जबतक (map->rst >= 0) अणु
		अगर (map->rst == id)
			वापस map->st;

		map++;
	पूर्ण

	वापस id;
पूर्ण

अटल पूर्णांक omap_reset_status(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा omap_reset_data *reset = to_omap_reset_data(rcdev);
	u32 v;
	पूर्णांक st_bit = omap_reset_get_st_bit(reset, id);
	bool has_rstst = reset->prm->data->rstst ||
		(reset->prm->data->flags & OMAP_PRM_HAS_RSTST);

	/* Check अगर we have rstst */
	अगर (!has_rstst)
		वापस -ENOTSUPP;

	/* Check अगर hw reset line is निश्चितed */
	v = पढ़ोl_relaxed(reset->prm->base + reset->prm->data->rstctrl);
	अगर (v & BIT(id))
		वापस 1;

	/*
	 * Check reset status, high value means reset sequence has been
	 * completed successfully so we can वापस 0 here (reset deनिश्चितed)
	 */
	v = पढ़ोl_relaxed(reset->prm->base + reset->prm->data->rstst);
	v >>= st_bit;
	v &= 1;

	वापस !v;
पूर्ण

अटल पूर्णांक omap_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			     अचिन्हित दीर्घ id)
अणु
	काष्ठा omap_reset_data *reset = to_omap_reset_data(rcdev);
	u32 v;
	अचिन्हित दीर्घ flags;

	/* निश्चित the reset control line */
	spin_lock_irqsave(&reset->lock, flags);
	v = पढ़ोl_relaxed(reset->prm->base + reset->prm->data->rstctrl);
	v |= 1 << id;
	ग_लिखोl_relaxed(v, reset->prm->base + reset->prm->data->rstctrl);
	spin_unlock_irqrestore(&reset->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	काष्ठा omap_reset_data *reset = to_omap_reset_data(rcdev);
	u32 v;
	पूर्णांक st_bit;
	bool has_rstst;
	अचिन्हित दीर्घ flags;
	काष्ठा ti_prm_platक्रमm_data *pdata = dev_get_platdata(reset->dev);
	पूर्णांक ret = 0;

	/* Nothing to करो अगर the reset is alपढ़ोy deनिश्चितed */
	अगर (!omap_reset_status(rcdev, id))
		वापस 0;

	has_rstst = reset->prm->data->rstst ||
		(reset->prm->data->flags & OMAP_PRM_HAS_RSTST);

	अगर (has_rstst) अणु
		st_bit = omap_reset_get_st_bit(reset, id);

		/* Clear the reset status by writing 1 to the status bit */
		v = 1 << st_bit;
		ग_लिखोl_relaxed(v, reset->prm->base + reset->prm->data->rstst);
	पूर्ण

	अगर (reset->clkdm)
		pdata->clkdm_deny_idle(reset->clkdm);

	/* de-निश्चित the reset control line */
	spin_lock_irqsave(&reset->lock, flags);
	v = पढ़ोl_relaxed(reset->prm->base + reset->prm->data->rstctrl);
	v &= ~(1 << id);
	ग_लिखोl_relaxed(v, reset->prm->base + reset->prm->data->rstctrl);
	spin_unlock_irqrestore(&reset->lock, flags);

	अगर (!has_rstst)
		जाओ निकास;

	/* रुको क्रम the status to be set */
	ret = पढ़ोl_relaxed_poll_समयout_atomic(reset->prm->base +
						 reset->prm->data->rstst,
						 v, v & BIT(st_bit), 1,
						 OMAP_RESET_MAX_WAIT);
	अगर (ret)
		pr_err("%s: timedout waiting for %s:%lu\n", __func__,
		       reset->prm->data->name, id);

निकास:
	अगर (reset->clkdm) अणु
		/* At least dra7 iva needs a delay beक्रमe clkdm idle */
		अगर (has_rstst)
			udelay(1);
		pdata->clkdm_allow_idle(reset->clkdm);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops omap_reset_ops = अणु
	.निश्चित		= omap_reset_निश्चित,
	.deनिश्चित	= omap_reset_deनिश्चित,
	.status		= omap_reset_status,
पूर्ण;

अटल पूर्णांक omap_prm_reset_xlate(काष्ठा reset_controller_dev *rcdev,
				स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	काष्ठा omap_reset_data *reset = to_omap_reset_data(rcdev);

	अगर (!_is_valid_reset(reset, reset_spec->args[0]))
		वापस -EINVAL;

	वापस reset_spec->args[0];
पूर्ण

अटल पूर्णांक omap_prm_reset_init(काष्ठा platक्रमm_device *pdev,
			       काष्ठा omap_prm *prm)
अणु
	काष्ठा omap_reset_data *reset;
	स्थिर काष्ठा omap_rst_map *map;
	काष्ठा ti_prm_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	अक्षर buf[32];
	u32 v;

	/*
	 * Check अगर we have controllable resets. If either rstctrl is non-zero
	 * or OMAP_PRM_HAS_RSTCTRL flag is set, we have reset control रेजिस्टर
	 * क्रम the करोमुख्य.
	 */
	अगर (!prm->data->rstctrl && !(prm->data->flags & OMAP_PRM_HAS_RSTCTRL))
		वापस 0;

	/* Check अगर we have the pdata callbacks in place */
	अगर (!pdata || !pdata->clkdm_lookup || !pdata->clkdm_deny_idle ||
	    !pdata->clkdm_allow_idle)
		वापस -EINVAL;

	map = prm->data->rsपंचांगap;
	अगर (!map)
		वापस -EINVAL;

	reset = devm_kzalloc(&pdev->dev, माप(*reset), GFP_KERNEL);
	अगर (!reset)
		वापस -ENOMEM;

	reset->rcdev.owner = THIS_MODULE;
	reset->rcdev.ops = &omap_reset_ops;
	reset->rcdev.of_node = pdev->dev.of_node;
	reset->rcdev.nr_resets = OMAP_MAX_RESETS;
	reset->rcdev.of_xlate = omap_prm_reset_xlate;
	reset->rcdev.of_reset_n_cells = 1;
	reset->dev = &pdev->dev;
	spin_lock_init(&reset->lock);

	reset->prm = prm;

	प्र_लिखो(buf, "%s_clkdm", prm->data->clkdm_name ? prm->data->clkdm_name :
		prm->data->name);

	अगर (!(prm->data->flags & OMAP_PRM_HAS_NO_CLKDM)) अणु
		reset->clkdm = pdata->clkdm_lookup(buf);
		अगर (!reset->clkdm)
			वापस -EINVAL;
	पूर्ण

	जबतक (map->rst >= 0) अणु
		reset->mask |= BIT(map->rst);
		map++;
	पूर्ण

	/* Quirk handling to निश्चित rst_map_012 bits on reset and aव्योम errors */
	अगर (prm->data->rsपंचांगap == rst_map_012) अणु
		v = पढ़ोl_relaxed(reset->prm->base + reset->prm->data->rstctrl);
		अगर ((v & reset->mask) != reset->mask) अणु
			dev_dbg(&pdev->dev, "Asserting all resets: %08x\n", v);
			ग_लिखोl_relaxed(reset->mask, reset->prm->base +
				       reset->prm->data->rstctrl);
		पूर्ण
	पूर्ण

	वापस devm_reset_controller_रेजिस्टर(&pdev->dev, &reset->rcdev);
पूर्ण

अटल पूर्णांक omap_prm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	स्थिर काष्ठा omap_prm_data *data;
	काष्ठा omap_prm *prm;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	match = of_match_device(omap_prm_id_table, &pdev->dev);
	अगर (!match)
		वापस -ENOTSUPP;

	prm = devm_kzalloc(&pdev->dev, माप(*prm), GFP_KERNEL);
	अगर (!prm)
		वापस -ENOMEM;

	data = match->data;

	जबतक (data->base != res->start) अणु
		अगर (!data->base)
			वापस -EINVAL;
		data++;
	पूर्ण

	prm->data = data;

	prm->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(prm->base))
		वापस PTR_ERR(prm->base);

	ret = omap_prm_करोमुख्य_init(&pdev->dev, prm);
	अगर (ret)
		वापस ret;

	ret = omap_prm_reset_init(pdev, prm);
	अगर (ret)
		जाओ err_करोमुख्य;

	वापस 0;

err_करोमुख्य:
	of_genpd_del_provider(pdev->dev.of_node);
	pm_genpd_हटाओ(&prm->prmd->pd);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_prm_driver = अणु
	.probe = omap_prm_probe,
	.driver = अणु
		.name		= KBUILD_MODNAME,
		.of_match_table	= omap_prm_id_table,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(omap_prm_driver);
