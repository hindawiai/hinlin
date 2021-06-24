<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_MXM_8X10_H
#घोषणा __MACH_MXM_8X10_H

#घोषणा MXM_8X10_ETH_PHYS	0x13000000

#अगर defined(CONFIG_MMC)

#घोषणा MXM_8X10_SD_nCD (72)
#घोषणा MXM_8X10_SD_WP (84)

बाह्य व्योम mxm_8x10_mmc_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम mxm_8x10_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

बाह्य व्योम mxm_8x10_usb_host_init(व्योम);
बाह्य व्योम mxm_8x10_ac97_init(व्योम);

बाह्य व्योम mxm_8x10_barebones_init(व्योम);

#पूर्ण_अगर /* __MACH_MXM_8X10_H */
