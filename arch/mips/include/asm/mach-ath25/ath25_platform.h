<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_ATH25_PLATFORM_H
#घोषणा __ASM_MACH_ATH25_PLATFORM_H

#समावेश <linux/etherdevice.h>

/*
 * This is board-specअगरic data that is stored in a "fixed" location in flash.
 * It is shared across operating प्रणालीs, so it should not be changed lightly.
 * The मुख्य reason we need it is in order to extract the ethernet MAC
 * address(es).
 */
काष्ठा ath25_boarddata अणु
	u32 magic;                   /* board data is valid */
#घोषणा ATH25_BD_MAGIC 0x35333131    /* "5311", क्रम all 531x/231x platक्रमms */
	u16 cksum;                   /* checksum (starting with BD_REV 2) */
	u16 rev;                     /* revision of this काष्ठा */
#घोषणा BD_REV 4
	अक्षर board_name[64];         /* Name of board */
	u16 major;                   /* Board major number */
	u16 minor;                   /* Board minor number */
	u32 flags;                   /* Board configuration */
#घोषणा BD_ENET0        0x00000001   /* ENET0 is stuffed */
#घोषणा BD_ENET1        0x00000002   /* ENET1 is stuffed */
#घोषणा BD_UART1        0x00000004   /* UART1 is stuffed */
#घोषणा BD_UART0        0x00000008   /* UART0 is stuffed (dma) */
#घोषणा BD_RSTFACTORY   0x00000010   /* Reset factory शेषs stuffed */
#घोषणा BD_SYSLED       0x00000020   /* System LED stuffed */
#घोषणा BD_EXTUARTCLK   0x00000040   /* External UART घड़ी */
#घोषणा BD_CPUFREQ      0x00000080   /* cpu freq is valid in nvram */
#घोषणा BD_SYSFREQ      0x00000100   /* sys freq is set in nvram */
#घोषणा BD_WLAN0        0x00000200   /* Enable WLAN0 */
#घोषणा BD_MEMCAP       0x00000400   /* CAP SDRAM @ mem_cap क्रम testing */
#घोषणा BD_DISWATCHDOG  0x00000800   /* disable प्रणाली watchकरोg */
#घोषणा BD_WLAN1        0x00001000   /* Enable WLAN1 (ar5212) */
#घोषणा BD_ISCASPER     0x00002000   /* FLAG क्रम AR2312 */
#घोषणा BD_WLAN0_2G_EN  0x00004000   /* FLAG क्रम radio0_2G */
#घोषणा BD_WLAN0_5G_EN  0x00008000   /* FLAG क्रम radio0_2G */
#घोषणा BD_WLAN1_2G_EN  0x00020000   /* FLAG क्रम radio0_2G */
#घोषणा BD_WLAN1_5G_EN  0x00040000   /* FLAG क्रम radio0_2G */
	u16 reset_config_gpio;       /* Reset factory GPIO pin */
	u16 sys_led_gpio;            /* System LED GPIO pin */

	u32 cpu_freq;                /* CPU core frequency in Hz */
	u32 sys_freq;                /* System frequency in Hz */
	u32 cnt_freq;                /* Calculated C0_COUNT frequency */

	u8  wlan0_mac[ETH_ALEN];
	u8  enet0_mac[ETH_ALEN];
	u8  enet1_mac[ETH_ALEN];

	u16 pci_id;                  /* Pseuकरो PCIID क्रम common code */
	u16 mem_cap;                 /* cap bank1 in MB */

	/* version 3 */
	u8  wlan1_mac[ETH_ALEN];     /* (ar5212) */
पूर्ण;

#घोषणा BOARD_CONFIG_BUFSZ		0x1000

/*
 * Platक्रमm device inक्रमmation क्रम the Wireless MAC
 */
काष्ठा ar231x_board_config अणु
	u16 devid;

	/* board config data */
	काष्ठा ath25_boarddata *config;

	/* radio calibration data */
	स्थिर अक्षर *radio;
पूर्ण;

#पूर्ण_अगर /* __ASM_MACH_ATH25_PLATFORM_H */
