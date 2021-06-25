<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-sa1100/include/mach/badge4.h
 *
 *   Tim Connors <connors@hpl.hp.com>
 *   Christopher Hoover <ch@hpl.hp.com>
 *
 * Copyright (C) 2002 Hewlett-Packard Company
 */

#अगर_अघोषित __ASM_ARCH_HARDWARE_H
#त्रुटि "include <mach/hardware.h> instead"
#पूर्ण_अगर

#घोषणा BADGE4_SA1111_BASE		(0x48000000)

/* GPIOs on the BadgePAD 4 */
#घोषणा BADGE4_GPIO_INT_1111		GPIO_GPIO0   /* SA-1111 IRQ */

#घोषणा BADGE4_GPIO_INT_VID		GPIO_GPIO1   /* Video expansion */
#घोषणा BADGE4_GPIO_LGP2		GPIO_GPIO2   /* GPIO_LDD8 */
#घोषणा BADGE4_GPIO_LGP3		GPIO_GPIO3   /* GPIO_LDD9 */
#घोषणा BADGE4_GPIO_LGP4		GPIO_GPIO4   /* GPIO_LDD10 */
#घोषणा BADGE4_GPIO_LGP5		GPIO_GPIO5   /* GPIO_LDD11 */
#घोषणा BADGE4_GPIO_LGP6		GPIO_GPIO6   /* GPIO_LDD12 */
#घोषणा BADGE4_GPIO_LGP7		GPIO_GPIO7   /* GPIO_LDD13 */
#घोषणा BADGE4_GPIO_LGP8		GPIO_GPIO8   /* GPIO_LDD14 */
#घोषणा BADGE4_GPIO_LGP9		GPIO_GPIO9   /* GPIO_LDD15 */
#घोषणा BADGE4_GPIO_GPA_VID		GPIO_GPIO10  /* Video expansion */
#घोषणा BADGE4_GPIO_GPB_VID		GPIO_GPIO11  /* Video expansion */
#घोषणा BADGE4_GPIO_GPC_VID		GPIO_GPIO12  /* Video expansion */

#घोषणा BADGE4_GPIO_UART_HS1		GPIO_GPIO13
#घोषणा BADGE4_GPIO_UART_HS2		GPIO_GPIO14

#घोषणा BADGE4_GPIO_MUXSEL0		GPIO_GPIO15
#घोषणा BADGE4_GPIO_TESTPT_J7		GPIO_GPIO16

#घोषणा BADGE4_GPIO_SDSDA		GPIO_GPIO17  /* SDRAM SPD Data */
#घोषणा BADGE4_GPIO_SDSCL		GPIO_GPIO18  /* SDRAM SPD Clock */
#घोषणा BADGE4_GPIO_SDTYP0		GPIO_GPIO19  /* SDRAM Type Control */
#घोषणा BADGE4_GPIO_SDTYP1		GPIO_GPIO20  /* SDRAM Type Control */

#घोषणा BADGE4_GPIO_BGNT_1111		GPIO_GPIO21  /* GPIO_MBGNT */
#घोषणा BADGE4_GPIO_BREQ_1111		GPIO_GPIO22  /* GPIO_TREQA */

#घोषणा BADGE4_GPIO_TESTPT_J6		GPIO_GPIO23

#घोषणा BADGE4_GPIO_PCMEN5V		GPIO_GPIO24  /* 5V घातer */

#घोषणा BADGE4_GPIO_SA1111_NRST		GPIO_GPIO25  /* SA-1111 nRESET */

#घोषणा BADGE4_GPIO_TESTPT_J5		GPIO_GPIO26

#घोषणा BADGE4_GPIO_CLK_1111		GPIO_GPIO27  /* GPIO_32_768kHz */

/* Interrupts on the BadgePAD 4 */
#घोषणा BADGE4_IRQ_GPIO_SA1111		IRQ_GPIO0    /* SA-1111 पूर्णांकerrupt */


/* PCM5ENV Usage tracking */

#घोषणा BADGE4_5V_PCMCIA_SOCK0		(1<<0)
#घोषणा BADGE4_5V_PCMCIA_SOCK1		(1<<1)
#घोषणा BADGE4_5V_PCMCIA_SOCK(n)	(1<<(n))
#घोषणा BADGE4_5V_USB			(1<<2)
#घोषणा BADGE4_5V_INITIALLY		(1<<3)

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम badge4_set_5V(अचिन्हित subप्रणाली, पूर्णांक on);
#पूर्ण_अगर
