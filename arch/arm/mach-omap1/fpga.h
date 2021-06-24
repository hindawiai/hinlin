<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Interrupt handler क्रम OMAP-1510 FPGA
 *
 * Copyright (C) 2001 RidgeRun, Inc.
 * Author: Greg Lonnon <glonnon@ridgerun.com>
 *
 * Copyright (C) 2002 MontaVista Software, Inc.
 *
 * Separated FPGA पूर्णांकerrupts from innovator1510.c and cleaned up क्रम 2.6
 * Copyright (C) 2004 Nokia Corporation by Tony Lindrgen <tony@atomide.com>
 */

#अगर_अघोषित __ASM_ARCH_OMAP_FPGA_H
#घोषणा __ASM_ARCH_OMAP_FPGA_H

/*
 * ---------------------------------------------------------------------------
 *  H2/P2 Debug board FPGA
 * ---------------------------------------------------------------------------
 */
/* maps in the FPGA रेजिस्टरs and the ETHR रेजिस्टरs */
#घोषणा H2P2_DBG_FPGA_BASE		0xE8000000		/* VA */
#घोषणा H2P2_DBG_FPGA_SIZE		SZ_4K			/* SIZE */
#घोषणा H2P2_DBG_FPGA_START		0x04000000		/* PA */

#घोषणा H2P2_DBG_FPGA_ETHR_START	(H2P2_DBG_FPGA_START + 0x300)
#घोषणा H2P2_DBG_FPGA_FPGA_REV		IOMEM(H2P2_DBG_FPGA_BASE + 0x10)	/* FPGA Revision */
#घोषणा H2P2_DBG_FPGA_BOARD_REV		IOMEM(H2P2_DBG_FPGA_BASE + 0x12)	/* Board Revision */
#घोषणा H2P2_DBG_FPGA_GPIO		IOMEM(H2P2_DBG_FPGA_BASE + 0x14)	/* GPIO outमाला_दो */
#घोषणा H2P2_DBG_FPGA_LEDS		IOMEM(H2P2_DBG_FPGA_BASE + 0x16)	/* LEDs outमाला_दो */
#घोषणा H2P2_DBG_FPGA_MISC_INPUTS	IOMEM(H2P2_DBG_FPGA_BASE + 0x18)	/* Misc inमाला_दो */
#घोषणा H2P2_DBG_FPGA_LAN_STATUS	IOMEM(H2P2_DBG_FPGA_BASE + 0x1A)	/* LAN Status line */
#घोषणा H2P2_DBG_FPGA_LAN_RESET		IOMEM(H2P2_DBG_FPGA_BASE + 0x1C)	/* LAN Reset line */

/* LEDs definition on debug board (16 LEDs, all physically green) */
#घोषणा H2P2_DBG_FPGA_LED_GREEN		(1 << 15)
#घोषणा H2P2_DBG_FPGA_LED_AMBER		(1 << 14)
#घोषणा H2P2_DBG_FPGA_LED_RED		(1 << 13)
#घोषणा H2P2_DBG_FPGA_LED_BLUE		(1 << 12)
/*  cpu0 load-meter LEDs */
#घोषणा H2P2_DBG_FPGA_LOAD_METER	(1 << 0)	// A bit of fun on our board ...
#घोषणा H2P2_DBG_FPGA_LOAD_METER_SIZE	11
#घोषणा H2P2_DBG_FPGA_LOAD_METER_MASK	((1 << H2P2_DBG_FPGA_LOAD_METER_SIZE) - 1)

#घोषणा H2P2_DBG_FPGA_P2_LED_TIMER		(1 << 0)
#घोषणा H2P2_DBG_FPGA_P2_LED_IDLE		(1 << 1)

#पूर्ण_अगर
