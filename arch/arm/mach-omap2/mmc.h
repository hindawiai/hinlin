<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#घोषणा OMAP24XX_NR_MMC		2
#घोषणा OMAP2420_MMC_SIZE	OMAP1_MMC_SIZE
#घोषणा OMAP2_MMC1_BASE		0x4809c000

#घोषणा OMAP4_MMC_REG_OFFSET	0x100

काष्ठा omap_hwmod;

#अगर_घोषित CONFIG_SOC_OMAP2420
पूर्णांक omap_msdi_reset(काष्ठा omap_hwmod *oh);
#अन्यथा
अटल अंतरभूत पूर्णांक omap_msdi_reset(काष्ठा omap_hwmod *oh)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
