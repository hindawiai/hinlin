<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _COLIBRI_H_
#घोषणा _COLIBRI_H_

#समावेश <net/ax88796.h>
#समावेश <mach/mfp.h>

/*
 * base board glue क्रम PXA270 module
 */

क्रमागत अणु
	COLIBRI_EVALBOARD = 0,
	COLIBRI_PXA270_INCOME,
पूर्ण;

#अगर defined(CONFIG_MACH_COLIBRI_EVALBOARD)
बाह्य व्योम colibri_evalboard_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम colibri_evalboard_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MACH_COLIBRI_PXA270_INCOME)
बाह्य व्योम colibri_pxa270_income_boardinit(व्योम);
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa270_income_boardinit(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*
 * common settings क्रम all modules
 */

#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
बाह्य व्योम colibri_pxa3xx_init_mmc(mfp_cfg_t *pins, पूर्णांक len, पूर्णांक detect_pin);
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa3xx_init_mmc(mfp_cfg_t *pins, पूर्णांक len, पूर्णांक detect_pin) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
बाह्य व्योम colibri_pxa3xx_init_lcd(पूर्णांक bl_pin);
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa3xx_init_lcd(पूर्णांक bl_pin) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_AX88796)
बाह्य व्योम colibri_pxa3xx_init_eth(काष्ठा ax_plat_data *plat_data);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
बाह्य व्योम colibri_pxa3xx_init_nand(व्योम);
#अन्यथा
अटल अंतरभूत व्योम colibri_pxa3xx_init_nand(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* physical memory regions */
#घोषणा COLIBRI_SDRAM_BASE	0xa0000000      /* SDRAM region */

/* GPIO definitions क्रम Colibri PXA270 */
#घोषणा GPIO114_COLIBRI_PXA270_ETH_IRQ	114
#घोषणा GPIO0_COLIBRI_PXA270_SD_DETECT	0
#घोषणा GPIO113_COLIBRI_PXA270_TS_IRQ	113

/* GPIO definitions क्रम Colibri PXA300/310 */
#घोषणा GPIO13_COLIBRI_PXA300_SD_DETECT	13

/* GPIO definitions क्रम Colibri PXA320 */
#घोषणा GPIO28_COLIBRI_PXA320_SD_DETECT	28

#पूर्ण_अगर /* _COLIBRI_H_ */

