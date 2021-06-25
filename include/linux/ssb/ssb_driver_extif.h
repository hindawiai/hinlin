<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hardware-specअगरic External Interface I/O core definitions
 * क्रम the BCM47xx family of SiliconBackplane-based chips.
 *
 * The External Interface core supports a total of three बाह्यal chip selects
 * supporting बाह्यal पूर्णांकerfaces. One of the बाह्यal chip selects is
 * used क्रम Flash, one is used क्रम PCMCIA, and the other may be
 * programmed to support either a synchronous पूर्णांकerface or an
 * asynchronous पूर्णांकerface. The asynchronous पूर्णांकerface can be used to
 * support बाह्यal devices such as UARTs and the BCM2019 Bluetooth
 * baseband processor.
 * The बाह्यal पूर्णांकerface core also contains 2 on-chip 16550 UARTs, घड़ी
 * frequency control, a watchकरोg पूर्णांकerrupt समयr, and a GPIO पूर्णांकerface.
 *
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, Michael Buesch
 */
#अगर_अघोषित LINUX_SSB_EXTIFCORE_H_
#घोषणा LINUX_SSB_EXTIFCORE_H_

/* बाह्यal पूर्णांकerface address space */
#घोषणा	SSB_EXTIF_PCMCIA_MEMBASE(x)	(x)
#घोषणा	SSB_EXTIF_PCMCIA_IOBASE(x)	((x) + 0x100000)
#घोषणा	SSB_EXTIF_PCMCIA_CFGBASE(x)	((x) + 0x200000)
#घोषणा	SSB_EXTIF_CFGIF_BASE(x)		((x) + 0x800000)
#घोषणा	SSB_EXTIF_FLASH_BASE(x)		((x) + 0xc00000)

#घोषणा SSB_EXTIF_NR_GPIOOUT		5
/* GPIO NOTE:
 * The multiple instances of output and output enable रेजिस्टरs
 * are present to allow driver software क्रम multiple cores to control
 * gpio outमाला_दो without needing to share a single रेजिस्टर pair.
 * Use the following helper macro to get a रेजिस्टर offset value.
 */
#घोषणा SSB_EXTIF_GPIO_OUT(index)	(अणु		\
	BUILD_BUG_ON(index >= SSB_EXTIF_NR_GPIOOUT);	\
	SSB_EXTIF_GPIO_OUT_BASE + ((index) * 8);	\
					पूर्ण)
#घोषणा SSB_EXTIF_GPIO_OUTEN(index)	(अणु		\
	BUILD_BUG_ON(index >= SSB_EXTIF_NR_GPIOOUT);	\
	SSB_EXTIF_GPIO_OUTEN_BASE + ((index) * 8);	\
					पूर्ण)

/** EXTIF core रेजिस्टरs **/

#घोषणा SSB_EXTIF_CTL			0x0000
#घोषणा  SSB_EXTIF_CTL_UARTEN		(1 << 0) /* UART enable */
#घोषणा SSB_EXTIF_EXTSTAT		0x0004
#घोषणा  SSB_EXTIF_EXTSTAT_EMODE	(1 << 0) /* Endian mode (ro) */
#घोषणा  SSB_EXTIF_EXTSTAT_EIRQPIN	(1 << 1) /* External पूर्णांकerrupt pin (ro) */
#घोषणा  SSB_EXTIF_EXTSTAT_GPIOIRQPIN	(1 << 2) /* GPIO पूर्णांकerrupt pin (ro) */
#घोषणा SSB_EXTIF_PCMCIA_CFG		0x0010
#घोषणा SSB_EXTIF_PCMCIA_MEMWAIT	0x0014
#घोषणा SSB_EXTIF_PCMCIA_ATTRWAIT	0x0018
#घोषणा SSB_EXTIF_PCMCIA_IOWAIT		0x001C
#घोषणा SSB_EXTIF_PROG_CFG		0x0020
#घोषणा SSB_EXTIF_PROG_WAITCNT		0x0024
#घोषणा SSB_EXTIF_FLASH_CFG		0x0028
#घोषणा SSB_EXTIF_FLASH_WAITCNT		0x002C
#घोषणा SSB_EXTIF_WATCHDOG		0x0040
#घोषणा SSB_EXTIF_CLOCK_N		0x0044
#घोषणा SSB_EXTIF_CLOCK_SB		0x0048
#घोषणा SSB_EXTIF_CLOCK_PCI		0x004C
#घोषणा SSB_EXTIF_CLOCK_MII		0x0050
#घोषणा SSB_EXTIF_GPIO_IN		0x0060
#घोषणा SSB_EXTIF_GPIO_OUT_BASE		0x0064
#घोषणा SSB_EXTIF_GPIO_OUTEN_BASE	0x0068
#घोषणा SSB_EXTIF_EJTAG_OUTEN		0x0090
#घोषणा SSB_EXTIF_GPIO_INTPOL		0x0094
#घोषणा SSB_EXTIF_GPIO_INTMASK		0x0098
#घोषणा SSB_EXTIF_UART_DATA		0x0300
#घोषणा SSB_EXTIF_UART_TIMER		0x0310
#घोषणा SSB_EXTIF_UART_FCR		0x0320
#घोषणा SSB_EXTIF_UART_LCR		0x0330
#घोषणा SSB_EXTIF_UART_MCR		0x0340
#घोषणा SSB_EXTIF_UART_LSR		0x0350
#घोषणा SSB_EXTIF_UART_MSR		0x0360
#घोषणा SSB_EXTIF_UART_SCRATCH		0x0370




/* pcmcia/prog/flash_config */
#घोषणा	SSB_EXTCFG_EN			(1 << 0)	/* enable */
#घोषणा	SSB_EXTCFG_MODE			0xE		/* mode */
#घोषणा	SSB_EXTCFG_MODE_SHIFT		1
#घोषणा	 SSB_EXTCFG_MODE_FLASH		0x0		/* flash/asynchronous mode */
#घोषणा	 SSB_EXTCFG_MODE_SYNC		0x2		/* synchronous mode */
#घोषणा	 SSB_EXTCFG_MODE_PCMCIA		0x4		/* pcmcia mode */
#घोषणा	SSB_EXTCFG_DS16			(1 << 4)	/* destsize:  0=8bit, 1=16bit */
#घोषणा	SSB_EXTCFG_BSWAP		(1 << 5)	/* byteswap */
#घोषणा	SSB_EXTCFG_CLKDIV		0xC0		/* घड़ी भागider */
#घोषणा	SSB_EXTCFG_CLKDIV_SHIFT		6
#घोषणा	 SSB_EXTCFG_CLKDIV_2		0x0		/* backplane/2 */
#घोषणा	 SSB_EXTCFG_CLKDIV_3		0x40		/* backplane/3 */
#घोषणा	 SSB_EXTCFG_CLKDIV_4		0x80		/* backplane/4 */
#घोषणा	SSB_EXTCFG_CLKEN		(1 << 8)	/* घड़ी enable */
#घोषणा	SSB_EXTCFG_STROBE		(1 << 9)	/* size/bytestrobe (synch only) */

/* pcmcia_memरुको */
#घोषणा	SSB_PCMCIA_MEMW_0		0x0000003F	/* रुकोcount0 */
#घोषणा	SSB_PCMCIA_MEMW_1		0x00001F00	/* रुकोcount1 */
#घोषणा	SSB_PCMCIA_MEMW_1_SHIFT		8
#घोषणा	SSB_PCMCIA_MEMW_2		0x001F0000	/* रुकोcount2 */
#घोषणा	SSB_PCMCIA_MEMW_2_SHIFT		16
#घोषणा	SSB_PCMCIA_MEMW_3		0x1F000000	/* रुकोcount3 */
#घोषणा	SSB_PCMCIA_MEMW_3_SHIFT		24

/* pcmcia_attrरुको */
#घोषणा	SSB_PCMCIA_ATTW_0		0x0000003F	/* रुकोcount0 */
#घोषणा	SSB_PCMCIA_ATTW_1		0x00001F00	/* रुकोcount1 */
#घोषणा	SSB_PCMCIA_ATTW_1_SHIFT		8
#घोषणा	SSB_PCMCIA_ATTW_2		0x001F0000	/* रुकोcount2 */
#घोषणा	SSB_PCMCIA_ATTW_2_SHIFT		16
#घोषणा	SSB_PCMCIA_ATTW_3		0x1F000000	/* रुकोcount3 */
#घोषणा	SSB_PCMCIA_ATTW_3_SHIFT		24

/* pcmcia_ioरुको */
#घोषणा	SSB_PCMCIA_IOW_0		0x0000003F	/* रुकोcount0 */
#घोषणा	SSB_PCMCIA_IOW_1		0x00001F00	/* रुकोcount1 */
#घोषणा	SSB_PCMCIA_IOW_1_SHIFT		8
#घोषणा	SSB_PCMCIA_IOW_2		0x001F0000	/* रुकोcount2 */
#घोषणा	SSB_PCMCIA_IOW_2_SHIFT		16
#घोषणा	SSB_PCMCIA_IOW_3		0x1F000000	/* रुकोcount3 */
#घोषणा	SSB_PCMCIA_IOW_3_SHIFT		24

/* prog_रुकोcount */
#घोषणा	SSB_PROG_WCNT_0			0x0000001F	/* रुकोcount0 */
#घोषणा	SSB_PROG_WCNT_1			0x00001F00	/* रुकोcount1 */
#घोषणा	SSB_PROG_WCNT_1_SHIFT		8
#घोषणा	SSB_PROG_WCNT_2			0x001F0000	/* रुकोcount2 */
#घोषणा	SSB_PROG_WCNT_2_SHIFT		16
#घोषणा	SSB_PROG_WCNT_3			0x1F000000	/* रुकोcount3 */
#घोषणा	SSB_PROG_WCNT_3_SHIFT		24

#घोषणा SSB_PROG_W0			0x0000000C
#घोषणा SSB_PROG_W1			0x00000A00
#घोषणा SSB_PROG_W2			0x00020000
#घोषणा SSB_PROG_W3			0x01000000

/* flash_रुकोcount */
#घोषणा	SSB_FLASH_WCNT_0		0x0000001F	/* रुकोcount0 */
#घोषणा	SSB_FLASH_WCNT_1		0x00001F00	/* रुकोcount1 */
#घोषणा	SSB_FLASH_WCNT_1_SHIFT		8
#घोषणा	SSB_FLASH_WCNT_2		0x001F0000	/* रुकोcount2 */
#घोषणा	SSB_FLASH_WCNT_2_SHIFT		16
#घोषणा	SSB_FLASH_WCNT_3		0x1F000000	/* रुकोcount3 */
#घोषणा	SSB_FLASH_WCNT_3_SHIFT		24

/* watchकरोg */
#घोषणा SSB_EXTIF_WATCHDOG_CLK		48000000	/* Hz */

#घोषणा SSB_EXTIF_WATCHDOG_MAX_TIMER	((1 << 28) - 1)
#घोषणा SSB_EXTIF_WATCHDOG_MAX_TIMER_MS	(SSB_EXTIF_WATCHDOG_MAX_TIMER \
					 / (SSB_EXTIF_WATCHDOG_CLK / 1000))


#अगर_घोषित CONFIG_SSB_DRIVER_EXTIF

काष्ठा ssb_extअगर अणु
	काष्ठा ssb_device *dev;
	spinlock_t gpio_lock;
पूर्ण;

अटल अंतरभूत bool ssb_extअगर_available(काष्ठा ssb_extअगर *extअगर)
अणु
	वापस (extअगर->dev != शून्य);
पूर्ण

बाह्य व्योम ssb_extअगर_get_घड़ीcontrol(काष्ठा ssb_extअगर *extअगर,
			               u32 *plltype, u32 *n, u32 *m);

बाह्य व्योम ssb_extअगर_timing_init(काष्ठा ssb_extअगर *extअगर,
				  अचिन्हित दीर्घ ns);

बाह्य u32 ssb_extअगर_watchकरोg_समयr_set(काष्ठा ssb_extअगर *extअगर, u32 ticks);

/* Extअगर GPIO pin access */
u32 ssb_extअगर_gpio_in(काष्ठा ssb_extअगर *extअगर, u32 mask);
u32 ssb_extअगर_gpio_out(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value);
u32 ssb_extअगर_gpio_outen(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value);
u32 ssb_extअगर_gpio_polarity(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value);
u32 ssb_extअगर_gpio_पूर्णांकmask(काष्ठा ssb_extअगर *extअगर, u32 mask, u32 value);

#अगर_घोषित CONFIG_SSB_SERIAL
बाह्य पूर्णांक ssb_extअगर_serial_init(काष्ठा ssb_extअगर *extअगर,
				 काष्ठा ssb_serial_port *ports);
#पूर्ण_अगर /* CONFIG_SSB_SERIAL */


#अन्यथा /* CONFIG_SSB_DRIVER_EXTIF */
/* extअगर disabled */

काष्ठा ssb_extअगर अणु
पूर्ण;

अटल अंतरभूत bool ssb_extअगर_available(काष्ठा ssb_extअगर *extअगर)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम ssb_extअगर_get_घड़ीcontrol(काष्ठा ssb_extअगर *extअगर,
			        u32 *plltype, u32 *n, u32 *m)
अणु
पूर्ण

अटल अंतरभूत
व्योम ssb_extअगर_timing_init(काष्ठा ssb_extअगर *extअगर, अचिन्हित दीर्घ ns)
अणु
पूर्ण

अटल अंतरभूत
u32 ssb_extअगर_watchकरोg_समयr_set(काष्ठा ssb_extअगर *extअगर, u32 ticks)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ssb_extअगर_gpio_in(काष्ठा ssb_extअगर *extअगर, u32 mask)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ssb_extअगर_gpio_out(काष्ठा ssb_extअगर *extअगर, u32 mask,
				     u32 value)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ssb_extअगर_gpio_outen(काष्ठा ssb_extअगर *extअगर, u32 mask,
				       u32 value)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ssb_extअगर_gpio_polarity(काष्ठा ssb_extअगर *extअगर, u32 mask,
					  u32 value)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत u32 ssb_extअगर_gpio_पूर्णांकmask(काष्ठा ssb_extअगर *extअगर, u32 mask,
					 u32 value)
अणु
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SSB_SERIAL
अटल अंतरभूत पूर्णांक ssb_extअगर_serial_init(काष्ठा ssb_extअगर *extअगर,
					काष्ठा ssb_serial_port *ports)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SSB_SERIAL */

#पूर्ण_अगर /* CONFIG_SSB_DRIVER_EXTIF */
#पूर्ण_अगर /* LINUX_SSB_EXTIFCORE_H_ */
