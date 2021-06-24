<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_HEATHROW_H
#घोषणा _ASM_POWERPC_HEATHROW_H
#अगर_घोषित __KERNEL__
/*
 * heathrow.h: definitions क्रम using the "Heathrow" I/O controller chip.
 *
 * Grabbed from Open Firmware definitions on a PowerBook G3 Series
 *
 * Copyright (C) 1997 Paul Mackerras.
 */

/* Front light color on Yikes/B&W G3. 32 bits */
#घोषणा HEATHROW_FRONT_LIGHT		0x32 /* (set to 0 or 0xffffffff) */

/* Brightness/contrast (gossamer iMac ?). 8 bits */
#घोषणा HEATHROW_BRIGHTNESS_CNTL	0x32
#घोषणा HEATHROW_CONTRAST_CNTL		0x33

/* offset from ohare base क्रम feature control रेजिस्टर */
#घोषणा HEATHROW_MBCR			0x34	/* Media bay control */
#घोषणा HEATHROW_FCR			0x38	/* Feature control */
#घोषणा HEATHROW_AUX_CNTL_REG		0x3c	/* Aux control */

/*
 * Bits in feature control रेजिस्टर.
 * Bits postfixed with a _N are in inverse logic
 */
#घोषणा HRW_SCC_TRANS_EN_N	0x00000001	/* Also controls modem घातer */
#घोषणा HRW_BAY_POWER_N		0x00000002
#घोषणा HRW_BAY_PCI_ENABLE	0x00000004
#घोषणा HRW_BAY_IDE_ENABLE	0x00000008
#घोषणा HRW_BAY_FLOPPY_ENABLE	0x00000010
#घोषणा HRW_IDE0_ENABLE		0x00000020
#घोषणा HRW_IDE0_RESET_N	0x00000040
#घोषणा HRW_BAY_DEV_MASK	0x0000001c
#घोषणा HRW_BAY_RESET_N		0x00000080
#घोषणा HRW_IOBUS_ENABLE	0x00000100	/* Internal IDE ? */
#घोषणा HRW_SCC_ENABLE		0x00000200
#घोषणा HRW_MESH_ENABLE		0x00000400
#घोषणा HRW_SWIM_ENABLE		0x00000800
#घोषणा HRW_SOUND_POWER_N	0x00001000
#घोषणा HRW_SOUND_CLK_ENABLE	0x00002000
#घोषणा HRW_SCCA_IO		0x00004000
#घोषणा HRW_SCCB_IO		0x00008000
#घोषणा HRW_PORT_OR_DESK_VIA_N	0x00010000	/* This one is 0 on PowerBook */
#घोषणा HRW_PWM_MON_ID_N	0x00020000	/* ??? (0) */
#घोषणा HRW_HOOK_MB_CNT_N	0x00040000	/* ??? (0) */
#घोषणा HRW_SWIM_CLONE_FLOPPY	0x00080000	/* ??? (0) */
#घोषणा HRW_AUD_RUN22		0x00100000	/* ??? (1) */
#घोषणा HRW_SCSI_LINK_MODE	0x00200000	/* Read ??? (1) */
#घोषणा HRW_ARB_BYPASS		0x00400000	/* Disable पूर्णांकernal PCI arbitrer */
#घोषणा HRW_IDE1_RESET_N	0x00800000	/* Media bay */
#घोषणा HRW_SLOW_SCC_PCLK	0x01000000	/* ??? (0) */
#घोषणा HRW_RESET_SCC		0x02000000
#घोषणा HRW_MFDC_CELL_ENABLE	0x04000000	/* ??? (0) */
#घोषणा HRW_USE_MFDC		0x08000000	/* ??? (0) */
#घोषणा HRW_BMAC_IO_ENABLE	0x60000000	/* two bits, not करोcumented in OF */
#घोषणा HRW_BMAC_RESET		0x80000000	/* not करोcumented in OF */

/* We OR those features at boot on desktop G3s */
#घोषणा HRW_DEFAULTS		(HRW_SCCA_IO | HRW_SCCB_IO | HRW_SCC_ENABLE)

/* Looks like Heathrow has some sort of GPIOs as well... */
#घोषणा HRW_GPIO_MODEM_RESET	0x6d

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_HEATHROW_H */
