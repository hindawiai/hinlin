<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/mmc/host.h>
#समावेश <linux/platक्रमm_data/mmc-omap.h>

#घोषणा OMAP15XX_NR_MMC		1
#घोषणा OMAP16XX_NR_MMC		2
#घोषणा OMAP1_MMC_SIZE		0x080
#घोषणा OMAP1_MMC1_BASE		0xfffb7800
#घोषणा OMAP1_MMC2_BASE		0xfffb7c00	/* omap16xx only */

#अगर IS_ENABLED(CONFIG_MMC_OMAP)
व्योम omap1_init_mmc(काष्ठा omap_mmc_platक्रमm_data **mmc_data,
				पूर्णांक nr_controllers);
#अन्यथा
अटल अंतरभूत व्योम omap1_init_mmc(काष्ठा omap_mmc_platक्रमm_data **mmc_data,
				पूर्णांक nr_controllers)
अणु
पूर्ण
#पूर्ण_अगर
