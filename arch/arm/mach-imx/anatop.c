<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013-2015 Freescale Semiconductor, Inc.
 * Copyright 2017-2018 NXP.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश "common.h"
#समावेश "hardware.h"

#घोषणा REG_SET		0x4
#घोषणा REG_CLR		0x8

#घोषणा ANADIG_REG_2P5		0x130
#घोषणा ANADIG_REG_CORE		0x140
#घोषणा ANADIG_ANA_MISC0	0x150
#घोषणा ANADIG_DIGPROG		0x260
#घोषणा ANADIG_DIGPROG_IMX6SL	0x280
#घोषणा ANADIG_DIGPROG_IMX7D	0x800

#घोषणा SRC_SBMR2		0x1c

#घोषणा BM_ANADIG_REG_2P5_ENABLE_WEAK_LINREG	0x40000
#घोषणा BM_ANADIG_REG_2P5_ENABLE_PULLDOWN	0x8
#घोषणा BM_ANADIG_REG_CORE_FET_ODRIVE		0x20000000
#घोषणा BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG	0x1000
/* Below MISC0_DISCON_HIGH_SNVS is only क्रम i.MX6SL */
#घोषणा BM_ANADIG_ANA_MISC0_DISCON_HIGH_SNVS	0x2000

अटल काष्ठा regmap *anatop;

अटल व्योम imx_anatop_enable_weak2p5(bool enable)
अणु
	u32 reg, val;

	regmap_पढ़ो(anatop, ANADIG_ANA_MISC0, &val);

	/* can only be enabled when stop_mode_config is clear. */
	reg = ANADIG_REG_2P5;
	reg += (enable && (val & BM_ANADIG_ANA_MISC0_STOP_MODE_CONFIG) == 0) ?
		REG_SET : REG_CLR;
	regmap_ग_लिखो(anatop, reg, BM_ANADIG_REG_2P5_ENABLE_WEAK_LINREG);
पूर्ण

अटल व्योम imx_anatop_enable_fet_odrive(bool enable)
अणु
	regmap_ग_लिखो(anatop, ANADIG_REG_CORE + (enable ? REG_SET : REG_CLR),
		BM_ANADIG_REG_CORE_FET_ODRIVE);
पूर्ण

अटल अंतरभूत व्योम imx_anatop_enable_2p5_pullकरोwn(bool enable)
अणु
	regmap_ग_लिखो(anatop, ANADIG_REG_2P5 + (enable ? REG_SET : REG_CLR),
		BM_ANADIG_REG_2P5_ENABLE_PULLDOWN);
पूर्ण

अटल अंतरभूत व्योम imx_anatop_disconnect_high_snvs(bool enable)
अणु
	regmap_ग_लिखो(anatop, ANADIG_ANA_MISC0 + (enable ? REG_SET : REG_CLR),
		BM_ANADIG_ANA_MISC0_DISCON_HIGH_SNVS);
पूर्ण

व्योम imx_anatop_pre_suspend(व्योम)
अणु
	अगर (imx_mmdc_get_ddr_type() == IMX_DDR_TYPE_LPDDR2)
		imx_anatop_enable_2p5_pullकरोwn(true);
	अन्यथा
		imx_anatop_enable_weak2p5(true);

	imx_anatop_enable_fet_odrive(true);

	अगर (cpu_is_imx6sl())
		imx_anatop_disconnect_high_snvs(true);
पूर्ण

व्योम imx_anatop_post_resume(व्योम)
अणु
	अगर (imx_mmdc_get_ddr_type() == IMX_DDR_TYPE_LPDDR2)
		imx_anatop_enable_2p5_pullकरोwn(false);
	अन्यथा
		imx_anatop_enable_weak2p5(false);

	imx_anatop_enable_fet_odrive(false);

	अगर (cpu_is_imx6sl())
		imx_anatop_disconnect_high_snvs(false);
पूर्ण

व्योम __init imx_init_revision_from_anatop(व्योम)
अणु
	काष्ठा device_node *np, *src_np;
	व्योम __iomem *anatop_base;
	अचिन्हित पूर्णांक revision;
	u32 digprog;
	u16 offset = ANADIG_DIGPROG;
	u8 major_part, minor_part;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx6q-anatop");
	anatop_base = of_iomap(np, 0);
	WARN_ON(!anatop_base);
	अगर (of_device_is_compatible(np, "fsl,imx6sl-anatop"))
		offset = ANADIG_DIGPROG_IMX6SL;
	अगर (of_device_is_compatible(np, "fsl,imx7d-anatop"))
		offset = ANADIG_DIGPROG_IMX7D;
	digprog = पढ़ोl_relaxed(anatop_base + offset);
	iounmap(anatop_base);

	/*
	 * On i.MX7D digprog value match linux version क्रमmat, so
	 * it needn't map again and we can use रेजिस्टर value directly.
	 */
	अगर (of_device_is_compatible(np, "fsl,imx7d-anatop")) अणु
		revision = digprog & 0xff;
	पूर्ण अन्यथा अणु
		/*
		 * MAJOR: [15:8], the major silicon revison;
		 * MINOR: [7: 0], the minor silicon revison;
		 *
		 * please refer to the i.MX RM क्रम the detailed
		 * silicon revison bit define.
		 * क्रमmat the major part and minor part to match the
		 * linux kernel soc version क्रमmat.
		 */
		major_part = (digprog >> 8) & 0xf;
		minor_part = digprog & 0xf;
		revision = ((major_part + 1) << 4) | minor_part;

		अगर ((digprog >> 16) == MXC_CPU_IMX6ULL) अणु
			व्योम __iomem *src_base;
			u32 sbmr2;

			src_np = of_find_compatible_node(शून्य, शून्य,
						     "fsl,imx6ul-src");
			src_base = of_iomap(src_np, 0);
			of_node_put(src_np);
			WARN_ON(!src_base);
			sbmr2 = पढ़ोl_relaxed(src_base + SRC_SBMR2);
			iounmap(src_base);

			/* src_sbmr2 bit 6 is to identअगरy अगर it is i.MX6ULZ */
			अगर (sbmr2 & (1 << 6)) अणु
				digprog &= ~(0xff << 16);
				digprog |= (MXC_CPU_IMX6ULZ << 16);
			पूर्ण
		पूर्ण
	पूर्ण
	of_node_put(np);

	mxc_set_cpu_type(digprog >> 16 & 0xff);
	imx_set_soc_revision(revision);
पूर्ण

व्योम __init imx_anatop_init(व्योम)
अणु
	anatop = syscon_regmap_lookup_by_compatible("fsl,imx6q-anatop");
	अगर (IS_ERR(anatop))
		pr_err("%s: failed to find imx6q-anatop regmap!\n", __func__);
पूर्ण
