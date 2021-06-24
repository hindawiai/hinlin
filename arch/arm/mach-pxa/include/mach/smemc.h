<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Static memory controller रेजिस्टर definitions क्रम PXA CPUs
 *
 * Copyright (C) 2010 Marek Vasut <marek.vasut@gmail.com>
 */

#अगर_अघोषित __SMEMC_REGS_H
#घोषणा __SMEMC_REGS_H

#घोषणा PXA2XX_SMEMC_BASE	0x48000000
#घोषणा PXA3XX_SMEMC_BASE	0x4a000000
#घोषणा SMEMC_VIRT		IOMEM(0xf6000000)

#घोषणा MDCNFG		(SMEMC_VIRT + 0x00)  /* SDRAM Configuration Register 0 */
#घोषणा MDREFR		(SMEMC_VIRT + 0x04)  /* SDRAM Refresh Control Register */
#घोषणा MSC0		(SMEMC_VIRT + 0x08)  /* Static Memory Control Register 0 */
#घोषणा MSC1		(SMEMC_VIRT + 0x0C)  /* Static Memory Control Register 1 */
#घोषणा MSC2		(SMEMC_VIRT + 0x10)  /* Static Memory Control Register 2 */
#घोषणा MECR		(SMEMC_VIRT + 0x14)  /* Expansion Memory (PCMCIA/Compact Flash) Bus Configuration */
#घोषणा SXLCR		(SMEMC_VIRT + 0x18)  /* LCR value to be written to SDRAM-Timing Synchronous Flash */
#घोषणा SXCNFG		(SMEMC_VIRT + 0x1C)  /* Synchronous Static Memory Control Register */
#घोषणा SXMRS		(SMEMC_VIRT + 0x24)  /* MRS value to be written to Synchronous Flash or SMROM */
#घोषणा MCMEM0		(SMEMC_VIRT + 0x28)  /* Card पूर्णांकerface Common Memory Space Socket 0 Timing */
#घोषणा MCMEM1		(SMEMC_VIRT + 0x2C)  /* Card पूर्णांकerface Common Memory Space Socket 1 Timing */
#घोषणा MCATT0		(SMEMC_VIRT + 0x30)  /* Card पूर्णांकerface Attribute Space Socket 0 Timing Configuration */
#घोषणा MCATT1		(SMEMC_VIRT + 0x34)  /* Card पूर्णांकerface Attribute Space Socket 1 Timing Configuration */
#घोषणा MCIO0		(SMEMC_VIRT + 0x38)  /* Card पूर्णांकerface I/O Space Socket 0 Timing Configuration */
#घोषणा MCIO1		(SMEMC_VIRT + 0x3C)  /* Card पूर्णांकerface I/O Space Socket 1 Timing Configuration */
#घोषणा MDMRS		(SMEMC_VIRT + 0x40)  /* MRS value to be written to SDRAM */
#घोषणा BOOT_DEF	(SMEMC_VIRT + 0x44)  /* Read-Only Boot-Time Register. Contains BOOT_SEL and PKG_SEL */
#घोषणा MEMCLKCFG	(SMEMC_VIRT + 0x68)  /* Clock Configuration */
#घोषणा CSADRCFG0	(SMEMC_VIRT + 0x80)  /* Address Configuration Register क्रम CS0 */
#घोषणा CSADRCFG1	(SMEMC_VIRT + 0x84)  /* Address Configuration Register क्रम CS1 */
#घोषणा CSADRCFG2	(SMEMC_VIRT + 0x88)  /* Address Configuration Register क्रम CS2 */
#घोषणा CSADRCFG3	(SMEMC_VIRT + 0x8C)  /* Address Configuration Register क्रम CS3 */
#घोषणा CSMSADRCFG	(SMEMC_VIRT + 0xA0)  /* Chip Select Configuration Register */

/*
 * More handy macros क्रम PCMCIA
 *
 * Arg is socket number
 */
#घोषणा MCMEM(s)	(SMEMC_VIRT + 0x28 + ((s)<<2))  /* Card पूर्णांकerface Common Memory Space Socket s Timing */
#घोषणा MCATT(s)	(SMEMC_VIRT + 0x30 + ((s)<<2))  /* Card पूर्णांकerface Attribute Space Socket s Timing Configuration */
#घोषणा MCIO(s)		(SMEMC_VIRT + 0x38 + ((s)<<2))  /* Card पूर्णांकerface I/O Space Socket s Timing Configuration */

/* MECR रेजिस्टर defines */
#घोषणा MECR_NOS	(1 << 0)	/* Number Of Sockets: 0 -> 1 sock, 1 -> 2 sock */
#घोषणा MECR_CIT	(1 << 1)	/* Card Is There: 0 -> no card, 1 -> card inserted */

#घोषणा MDCNFG_DE0	(1 << 0)	/* SDRAM Bank 0 Enable */
#घोषणा MDCNFG_DE1	(1 << 1)	/* SDRAM Bank 1 Enable */
#घोषणा MDCNFG_DE2	(1 << 16)	/* SDRAM Bank 2 Enable */
#घोषणा MDCNFG_DE3	(1 << 17)	/* SDRAM Bank 3 Enable */

#घोषणा MDREFR_K0DB4	(1 << 29)	/* SDCLK0 Divide by 4 Control/Status */
#घोषणा MDREFR_K2FREE	(1 << 25)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_K1FREE	(1 << 24)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_K0FREE	(1 << 23)	/* SDRAM Free-Running Control */
#घोषणा MDREFR_SLFRSH	(1 << 22)	/* SDRAM Self-Refresh Control/Status */
#घोषणा MDREFR_APD	(1 << 20)	/* SDRAM/SSRAM Auto-Power-Down Enable */
#घोषणा MDREFR_K2DB2	(1 << 19)	/* SDCLK2 Divide by 2 Control/Status */
#घोषणा MDREFR_K2RUN	(1 << 18)	/* SDCLK2 Run Control/Status */
#घोषणा MDREFR_K1DB2	(1 << 17)	/* SDCLK1 Divide by 2 Control/Status */
#घोषणा MDREFR_K1RUN	(1 << 16)	/* SDCLK1 Run Control/Status */
#घोषणा MDREFR_E1PIN	(1 << 15)	/* SDCKE1 Level Control/Status */
#घोषणा MDREFR_K0DB2	(1 << 14)	/* SDCLK0 Divide by 2 Control/Status */
#घोषणा MDREFR_K0RUN	(1 << 13)	/* SDCLK0 Run Control/Status */
#घोषणा MDREFR_E0PIN	(1 << 12)	/* SDCKE0 Level Control/Status */

#पूर्ण_अगर
