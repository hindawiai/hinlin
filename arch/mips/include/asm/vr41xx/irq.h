<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/यंत्र-mips/vr41xx/irq.h
 *
 * Interrupt numbers क्रम NEC VR4100 series.
 *
 * Copyright (C) 1999 Michael Klar
 * Copyright (C) 2001, 2002 Paul Mundt
 * Copyright (C) 2002 MontaVista Software, Inc.
 * Copyright (C) 2002 TimeSys Corp.
 * Copyright (C) 2003-2006 Yoichi Yuasa <yuasa@linux-mips.org>
 */
#अगर_अघोषित __NEC_VR41XX_IRQ_H
#घोषणा __NEC_VR41XX_IRQ_H

/*
 * CPU core Interrupt Numbers
 */
#घोषणा MIPS_CPU_IRQ_BASE	0
#घोषणा MIPS_CPU_IRQ(x)		(MIPS_CPU_IRQ_BASE + (x))
#घोषणा MIPS_SOFTINT0_IRQ	MIPS_CPU_IRQ(0)
#घोषणा MIPS_SOFTINT1_IRQ	MIPS_CPU_IRQ(1)
#घोषणा INT0_IRQ		MIPS_CPU_IRQ(2)
#घोषणा INT1_IRQ		MIPS_CPU_IRQ(3)
#घोषणा INT2_IRQ		MIPS_CPU_IRQ(4)
#घोषणा INT3_IRQ		MIPS_CPU_IRQ(5)
#घोषणा INT4_IRQ		MIPS_CPU_IRQ(6)
#घोषणा TIMER_IRQ		MIPS_CPU_IRQ(7)

/*
 * SYINT1 Interrupt Numbers
 */
#घोषणा SYSINT1_IRQ_BASE	8
#घोषणा SYSINT1_IRQ(x)		(SYSINT1_IRQ_BASE + (x))
#घोषणा BATTRY_IRQ		SYSINT1_IRQ(0)
#घोषणा POWER_IRQ		SYSINT1_IRQ(1)
#घोषणा RTCLONG1_IRQ		SYSINT1_IRQ(2)
#घोषणा ELAPSEDTIME_IRQ		SYSINT1_IRQ(3)
/* RFU */
#घोषणा PIU_IRQ			SYSINT1_IRQ(5)
#घोषणा AIU_IRQ			SYSINT1_IRQ(6)
#घोषणा KIU_IRQ			SYSINT1_IRQ(7)
#घोषणा GIUINT_IRQ		SYSINT1_IRQ(8)
#घोषणा SIU_IRQ			SYSINT1_IRQ(9)
#घोषणा BUSERR_IRQ		SYSINT1_IRQ(10)
#घोषणा SOFTINT_IRQ		SYSINT1_IRQ(11)
#घोषणा CLKRUN_IRQ		SYSINT1_IRQ(12)
#घोषणा DOZEPIU_IRQ		SYSINT1_IRQ(13)
#घोषणा SYSINT1_IRQ_LAST	DOZEPIU_IRQ

/*
 * SYSINT2 Interrupt Numbers
 */
#घोषणा SYSINT2_IRQ_BASE	24
#घोषणा SYSINT2_IRQ(x)		(SYSINT2_IRQ_BASE + (x))
#घोषणा RTCLONG2_IRQ		SYSINT2_IRQ(0)
#घोषणा LED_IRQ			SYSINT2_IRQ(1)
#घोषणा HSP_IRQ			SYSINT2_IRQ(2)
#घोषणा TCLOCK_IRQ		SYSINT2_IRQ(3)
#घोषणा FIR_IRQ			SYSINT2_IRQ(4)
#घोषणा CEU_IRQ			SYSINT2_IRQ(4)	/* same number as FIR_IRQ */
#घोषणा DSIU_IRQ		SYSINT2_IRQ(5)
#घोषणा PCI_IRQ			SYSINT2_IRQ(6)
#घोषणा SCU_IRQ			SYSINT2_IRQ(7)
#घोषणा CSI_IRQ			SYSINT2_IRQ(8)
#घोषणा BCU_IRQ			SYSINT2_IRQ(9)
#घोषणा ETHERNET_IRQ		SYSINT2_IRQ(10)
#घोषणा SYSINT2_IRQ_LAST	ETHERNET_IRQ

/*
 * GIU Interrupt Numbers
 */
#घोषणा GIU_IRQ_BASE		40
#घोषणा GIU_IRQ(x)		(GIU_IRQ_BASE + (x))	/* IRQ 40-71 */
#घोषणा GIU_IRQ_LAST		GIU_IRQ(31)

/*
 * VRC4173 Interrupt Numbers
 */
#घोषणा VRC4173_IRQ_BASE	72
#घोषणा VRC4173_IRQ(x)		(VRC4173_IRQ_BASE + (x))
#घोषणा VRC4173_USB_IRQ		VRC4173_IRQ(0)
#घोषणा VRC4173_PCMCIA2_IRQ	VRC4173_IRQ(1)
#घोषणा VRC4173_PCMCIA1_IRQ	VRC4173_IRQ(2)
#घोषणा VRC4173_PS2CH2_IRQ	VRC4173_IRQ(3)
#घोषणा VRC4173_PS2CH1_IRQ	VRC4173_IRQ(4)
#घोषणा VRC4173_PIU_IRQ		VRC4173_IRQ(5)
#घोषणा VRC4173_AIU_IRQ		VRC4173_IRQ(6)
#घोषणा VRC4173_KIU_IRQ		VRC4173_IRQ(7)
#घोषणा VRC4173_GIU_IRQ		VRC4173_IRQ(8)
#घोषणा VRC4173_AC97_IRQ	VRC4173_IRQ(9)
#घोषणा VRC4173_AC97INT1_IRQ	VRC4173_IRQ(10)
/* RFU */
#घोषणा VRC4173_DOZEPIU_IRQ	VRC4173_IRQ(13)
#घोषणा VRC4173_IRQ_LAST	VRC4173_DOZEPIU_IRQ

#पूर्ण_अगर /* __NEC_VR41XX_IRQ_H */
