<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Aपंचांगel SMC (Static Memory Controller) रेजिस्टर offsets and bit definitions.
 *
 * Copyright (C) 2014 Aपंचांगel
 * Copyright (C) 2014 Free Electrons
 *
 * Author: Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 */

#अगर_अघोषित _LINUX_MFD_SYSCON_ATMEL_SMC_H_
#घोषणा _LINUX_MFD_SYSCON_ATMEL_SMC_H_

#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#घोषणा ATMEL_SMC_SETUP(cs)			(((cs) * 0x10))
#घोषणा ATMEL_HSMC_SETUP(layout, cs)		\
	((layout)->timing_regs_offset + ((cs) * 0x14))
#घोषणा ATMEL_SMC_PULSE(cs)			(((cs) * 0x10) + 0x4)
#घोषणा ATMEL_HSMC_PULSE(layout, cs)		\
	((layout)->timing_regs_offset + ((cs) * 0x14) + 0x4)
#घोषणा ATMEL_SMC_CYCLE(cs)			(((cs) * 0x10) + 0x8)
#घोषणा ATMEL_HSMC_CYCLE(layout, cs)			\
	((layout)->timing_regs_offset + ((cs) * 0x14) + 0x8)
#घोषणा ATMEL_SMC_NWE_SHIFT			0
#घोषणा ATMEL_SMC_NCS_WR_SHIFT			8
#घोषणा ATMEL_SMC_NRD_SHIFT			16
#घोषणा ATMEL_SMC_NCS_RD_SHIFT			24

#घोषणा ATMEL_SMC_MODE(cs)			(((cs) * 0x10) + 0xc)
#घोषणा ATMEL_HSMC_MODE(layout, cs)			\
	((layout)->timing_regs_offset + ((cs) * 0x14) + 0x10)
#घोषणा ATMEL_SMC_MODE_READMODE_MASK		BIT(0)
#घोषणा ATMEL_SMC_MODE_READMODE_NCS		(0 << 0)
#घोषणा ATMEL_SMC_MODE_READMODE_NRD		(1 << 0)
#घोषणा ATMEL_SMC_MODE_WRITEMODE_MASK		BIT(1)
#घोषणा ATMEL_SMC_MODE_WRITEMODE_NCS		(0 << 1)
#घोषणा ATMEL_SMC_MODE_WRITEMODE_NWE		(1 << 1)
#घोषणा ATMEL_SMC_MODE_EXNWMODE_MASK		GENMASK(5, 4)
#घोषणा ATMEL_SMC_MODE_EXNWMODE_DISABLE		(0 << 4)
#घोषणा ATMEL_SMC_MODE_EXNWMODE_FROZEN		(2 << 4)
#घोषणा ATMEL_SMC_MODE_EXNWMODE_READY		(3 << 4)
#घोषणा ATMEL_SMC_MODE_BAT_MASK			BIT(8)
#घोषणा ATMEL_SMC_MODE_BAT_SELECT		(0 << 8)
#घोषणा ATMEL_SMC_MODE_BAT_WRITE		(1 << 8)
#घोषणा ATMEL_SMC_MODE_DBW_MASK			GENMASK(13, 12)
#घोषणा ATMEL_SMC_MODE_DBW_8			(0 << 12)
#घोषणा ATMEL_SMC_MODE_DBW_16			(1 << 12)
#घोषणा ATMEL_SMC_MODE_DBW_32			(2 << 12)
#घोषणा ATMEL_SMC_MODE_TDF_MASK			GENMASK(19, 16)
#घोषणा ATMEL_SMC_MODE_TDF(x)			(((x) - 1) << 16)
#घोषणा ATMEL_SMC_MODE_TDF_MAX			16
#घोषणा ATMEL_SMC_MODE_TDF_MIN			1
#घोषणा ATMEL_SMC_MODE_TDFMODE_OPTIMIZED	BIT(20)
#घोषणा ATMEL_SMC_MODE_PMEN			BIT(24)
#घोषणा ATMEL_SMC_MODE_PS_MASK			GENMASK(29, 28)
#घोषणा ATMEL_SMC_MODE_PS_4			(0 << 28)
#घोषणा ATMEL_SMC_MODE_PS_8			(1 << 28)
#घोषणा ATMEL_SMC_MODE_PS_16			(2 << 28)
#घोषणा ATMEL_SMC_MODE_PS_32			(3 << 28)

#घोषणा ATMEL_HSMC_TIMINGS(layout, cs)			\
	((layout)->timing_regs_offset + ((cs) * 0x14) + 0xc)
#घोषणा ATMEL_HSMC_TIMINGS_OCMS			BIT(12)
#घोषणा ATMEL_HSMC_TIMINGS_RBNSEL(x)		((x) << 28)
#घोषणा ATMEL_HSMC_TIMINGS_NFSEL		BIT(31)
#घोषणा ATMEL_HSMC_TIMINGS_TCLR_SHIFT		0
#घोषणा ATMEL_HSMC_TIMINGS_TADL_SHIFT		4
#घोषणा ATMEL_HSMC_TIMINGS_TAR_SHIFT		8
#घोषणा ATMEL_HSMC_TIMINGS_TRR_SHIFT		16
#घोषणा ATMEL_HSMC_TIMINGS_TWB_SHIFT		24

काष्ठा aपंचांगel_hsmc_reg_layout अणु
	अचिन्हित पूर्णांक timing_regs_offset;
पूर्ण;

/**
 * काष्ठा aपंचांगel_smc_cs_conf - SMC CS config as described in the datasheet.
 * @setup: NCS/NWE/NRD setup timings (not applicable to at91rm9200)
 * @pulse: NCS/NWE/NRD pulse timings (not applicable to at91rm9200)
 * @cycle: NWE/NRD cycle timings (not applicable to at91rm9200)
 * @timings: advanced न_अंकD related timings (only applicable to HSMC)
 * @mode: all kind of config parameters (see the fields definition above).
 *	  The mode fields are dअगरferent on at91rm9200
 */
काष्ठा aपंचांगel_smc_cs_conf अणु
	u32 setup;
	u32 pulse;
	u32 cycle;
	u32 timings;
	u32 mode;
पूर्ण;

व्योम aपंचांगel_smc_cs_conf_init(काष्ठा aपंचांगel_smc_cs_conf *conf);
पूर्णांक aपंचांगel_smc_cs_conf_set_timing(काष्ठा aपंचांगel_smc_cs_conf *conf,
				 अचिन्हित पूर्णांक shअगरt,
				 अचिन्हित पूर्णांक ncycles);
पूर्णांक aपंचांगel_smc_cs_conf_set_setup(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles);
पूर्णांक aपंचांगel_smc_cs_conf_set_pulse(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles);
पूर्णांक aपंचांगel_smc_cs_conf_set_cycle(काष्ठा aपंचांगel_smc_cs_conf *conf,
				अचिन्हित पूर्णांक shअगरt, अचिन्हित पूर्णांक ncycles);
व्योम aपंचांगel_smc_cs_conf_apply(काष्ठा regmap *regmap, पूर्णांक cs,
			     स्थिर काष्ठा aपंचांगel_smc_cs_conf *conf);
व्योम aपंचांगel_hsmc_cs_conf_apply(काष्ठा regmap *regmap,
			      स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *reglayout,
			      पूर्णांक cs, स्थिर काष्ठा aपंचांगel_smc_cs_conf *conf);
व्योम aपंचांगel_smc_cs_conf_get(काष्ठा regmap *regmap, पूर्णांक cs,
			   काष्ठा aपंचांगel_smc_cs_conf *conf);
व्योम aपंचांगel_hsmc_cs_conf_get(काष्ठा regmap *regmap,
			    स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *reglayout,
			    पूर्णांक cs, काष्ठा aपंचांगel_smc_cs_conf *conf);
स्थिर काष्ठा aपंचांगel_hsmc_reg_layout *
aपंचांगel_hsmc_get_reg_layout(काष्ठा device_node *np);

#पूर्ण_अगर /* _LINUX_MFD_SYSCON_ATMEL_SMC_H_ */
