<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * MMC definitions क्रम OMAP2
 *
 * Copyright (C) 2006 Nokia Corporation
 */

/*
 * काष्ठा omap_hsmmc_dev_attr.flags possibilities
 *
 * OMAP_HSMMC_SUPPORTS_DUAL_VOLT: Some HSMMC controller instances can
 *    operate with either 1.8Vdc or 3.0Vdc card voltages; this flag
 *    should be set अगर this is the हाल.  See क्रम example Section 22.5.3
 *    "MMC/SD/SDIO1 Bus Voltage Selection" of the OMAP34xx Mulसमयdia
 *    Device Silicon Revision 3.1.x Revision ZR (July 2011) (SWPU223R).
 *
 * OMAP_HSMMC_BROKEN_MULTIBLOCK_READ: Multiple-block पढ़ो transfers
 *    करोn't work correctly on some MMC controller instances on some
 *    OMAP3 SoCs; this flag should be set अगर this is the हाल.  See
 *    क्रम example Advisory 2.1.1.128 "MMC: Multiple Block Read
 *    Operation Issue" in _OMAP3530/3525/3515/3503 Silicon Errata_
 *    Revision F (October 2010) (SPRZ278F).
 */
#घोषणा OMAP_HSMMC_SUPPORTS_DUAL_VOLT		BIT(0)
#घोषणा OMAP_HSMMC_BROKEN_MULTIBLOCK_READ	BIT(1)
#घोषणा OMAP_HSMMC_SWAKEUP_MISSING		BIT(2)

काष्ठा omap_hsmmc_dev_attr अणु
	u8 flags;
पूर्ण;

काष्ठा mmc_card;

काष्ठा omap_hsmmc_platक्रमm_data अणु
	/* back-link to device */
	काष्ठा device *dev;

	/* set अगर your board has components or wiring that limits the
	 * maximum frequency on the MMC bus */
	अचिन्हित पूर्णांक max_freq;

	/* Integrating attributes from the omap_hwmod layer */
	u8 controller_flags;

	/* Register offset deviation */
	u16 reg_offset;

	/*
	 * 4/8 wires and any additional host capabilities
	 * need to OR'd all capabilities (ref. linux/mmc/host.h)
	 */
	u32 caps;	/* Used क्रम the MMC driver on 2430 and later */
	u32 pm_caps;	/* PM capabilities of the mmc */

	/* nonremovable e.g. eMMC */
	अचिन्हित nonremovable:1;

	/* eMMC करोes not handle घातer off when not in sleep state */
	अचिन्हित no_regulator_off_init:1;

	/* we can put the features above पूर्णांकo this variable */
#घोषणा HSMMC_HAS_PBIAS		(1 << 0)
#घोषणा HSMMC_HAS_UPDATED_RESET	(1 << 1)
#घोषणा HSMMC_HAS_HSPE_SUPPORT	(1 << 2)
	अचिन्हित features;

	/* string specअगरying a particular variant of hardware */
	अक्षर *version;

	स्थिर अक्षर *name;
	u32 ocr_mask;
पूर्ण;
