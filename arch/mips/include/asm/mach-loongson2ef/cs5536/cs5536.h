<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The header file of cs5536 south bridge.
 *
 * Copyright (C) 2007 Lemote, Inc.
 * Author : jlliu <liujl@lemote.com>
 */

#अगर_अघोषित _CS5536_H
#घोषणा _CS5536_H

#समावेश <linux/types.h>

बाह्य व्योम _rdmsr(u32 msr, u32 *hi, u32 *lo);
बाह्य व्योम _wrmsr(u32 msr, u32 hi, u32 lo);

/*
 * MSR module base
 */
#घोषणा CS5536_SB_MSR_BASE	(0x00000000)
#घोषणा CS5536_GLIU_MSR_BASE	(0x10000000)
#घोषणा CS5536_ILLEGAL_MSR_BASE (0x20000000)
#घोषणा CS5536_USB_MSR_BASE	(0x40000000)
#घोषणा CS5536_IDE_MSR_BASE	(0x60000000)
#घोषणा CS5536_DIVIL_MSR_BASE	(0x80000000)
#घोषणा CS5536_ACC_MSR_BASE	(0xa0000000)
#घोषणा CS5536_UNUSED_MSR_BASE	(0xc0000000)
#घोषणा CS5536_GLCP_MSR_BASE	(0xe0000000)

#घोषणा SB_MSR_REG(offset)	(CS5536_SB_MSR_BASE	| (offset))
#घोषणा GLIU_MSR_REG(offset)	(CS5536_GLIU_MSR_BASE	| (offset))
#घोषणा ILLEGAL_MSR_REG(offset) (CS5536_ILLEGAL_MSR_BASE | (offset))
#घोषणा USB_MSR_REG(offset)	(CS5536_USB_MSR_BASE	| (offset))
#घोषणा IDE_MSR_REG(offset)	(CS5536_IDE_MSR_BASE	| (offset))
#घोषणा DIVIL_MSR_REG(offset)	(CS5536_DIVIL_MSR_BASE	| (offset))
#घोषणा ACC_MSR_REG(offset)	(CS5536_ACC_MSR_BASE	| (offset))
#घोषणा UNUSED_MSR_REG(offset)	(CS5536_UNUSED_MSR_BASE | (offset))
#घोषणा GLCP_MSR_REG(offset)	(CS5536_GLCP_MSR_BASE	| (offset))

/*
 * BAR SPACE OF VIRTUAL PCI :
 * range क्रम pci probe use, length is the actual size.
 */
/* IO space क्रम all DIVIL modules */
#घोषणा CS5536_IRQ_RANGE	0xffffffe0 /* USERD FOR PCI PROBE */
#घोषणा CS5536_IRQ_LENGTH	0x20	/* THE REGS ACTUAL LENGTH */
#घोषणा CS5536_SMB_RANGE	0xfffffff8
#घोषणा CS5536_SMB_LENGTH	0x08
#घोषणा CS5536_GPIO_RANGE	0xffffff00
#घोषणा CS5536_GPIO_LENGTH	0x100
#घोषणा CS5536_MFGPT_RANGE	0xffffffc0
#घोषणा CS5536_MFGPT_LENGTH	0x40
#घोषणा CS5536_ACPI_RANGE	0xffffffe0
#घोषणा CS5536_ACPI_LENGTH	0x20
#घोषणा CS5536_PMS_RANGE	0xffffff80
#घोषणा CS5536_PMS_LENGTH	0x80
/* IO space क्रम IDE */
#घोषणा CS5536_IDE_RANGE	0xfffffff0
#घोषणा CS5536_IDE_LENGTH	0x10
/* IO space क्रम ACC */
#घोषणा CS5536_ACC_RANGE	0xffffff80
#घोषणा CS5536_ACC_LENGTH	0x80
/* MEM space क्रम ALL USB modules */
#घोषणा CS5536_OHCI_RANGE	0xfffff000
#घोषणा CS5536_OHCI_LENGTH	0x1000
#घोषणा CS5536_EHCI_RANGE	0xfffff000
#घोषणा CS5536_EHCI_LENGTH	0x1000

/*
 * PCI MSR ACCESS
 */
#घोषणा PCI_MSR_CTRL		0xF0
#घोषणा PCI_MSR_ADDR		0xF4
#घोषणा PCI_MSR_DATA_LO		0xF8
#घोषणा PCI_MSR_DATA_HI		0xFC

/**************** MSR *****************************/

/*
 * GLIU STANDARD MSR
 */
#घोषणा GLIU_CAP		0x00
#घोषणा GLIU_CONFIG		0x01
#घोषणा GLIU_SMI		0x02
#घोषणा GLIU_ERROR		0x03
#घोषणा GLIU_PM			0x04
#घोषणा GLIU_DIAG		0x05

/*
 * GLIU SPEC. MSR
 */
#घोषणा GLIU_P2D_BM0		0x20
#घोषणा GLIU_P2D_BM1		0x21
#घोषणा GLIU_P2D_BM2		0x22
#घोषणा GLIU_P2D_BMK0		0x23
#घोषणा GLIU_P2D_BMK1		0x24
#घोषणा GLIU_P2D_BM3		0x25
#घोषणा GLIU_P2D_BM4		0x26
#घोषणा GLIU_COH		0x80
#घोषणा GLIU_PAE		0x81
#घोषणा GLIU_ARB		0x82
#घोषणा GLIU_ASMI		0x83
#घोषणा GLIU_AERR		0x84
#घोषणा GLIU_DEBUG		0x85
#घोषणा GLIU_PHY_CAP		0x86
#घोषणा GLIU_NOUT_RESP		0x87
#घोषणा GLIU_NOUT_WDATA		0x88
#घोषणा GLIU_WHOAMI		0x8B
#घोषणा GLIU_SLV_DIS		0x8C
#घोषणा GLIU_IOD_BM0		0xE0
#घोषणा GLIU_IOD_BM1		0xE1
#घोषणा GLIU_IOD_BM2		0xE2
#घोषणा GLIU_IOD_BM3		0xE3
#घोषणा GLIU_IOD_BM4		0xE4
#घोषणा GLIU_IOD_BM5		0xE5
#घोषणा GLIU_IOD_BM6		0xE6
#घोषणा GLIU_IOD_BM7		0xE7
#घोषणा GLIU_IOD_BM8		0xE8
#घोषणा GLIU_IOD_BM9		0xE9
#घोषणा GLIU_IOD_SC0		0xEA
#घोषणा GLIU_IOD_SC1		0xEB
#घोषणा GLIU_IOD_SC2		0xEC
#घोषणा GLIU_IOD_SC3		0xED
#घोषणा GLIU_IOD_SC4		0xEE
#घोषणा GLIU_IOD_SC5		0xEF
#घोषणा GLIU_IOD_SC6		0xF0
#घोषणा GLIU_IOD_SC7		0xF1

/*
 * SB STANDARD
 */
#घोषणा SB_CAP		0x00
#घोषणा SB_CONFIG	0x01
#घोषणा SB_SMI		0x02
#घोषणा SB_ERROR	0x03
#घोषणा SB_MAR_ERR_EN		0x00000001
#घोषणा SB_TAR_ERR_EN		0x00000002
#घोषणा SB_RSVD_BIT1		0x00000004
#घोषणा SB_EXCEP_ERR_EN		0x00000008
#घोषणा SB_SYSE_ERR_EN		0x00000010
#घोषणा SB_PARE_ERR_EN		0x00000020
#घोषणा SB_TAS_ERR_EN		0x00000040
#घोषणा SB_MAR_ERR_FLAG		0x00010000
#घोषणा SB_TAR_ERR_FLAG		0x00020000
#घोषणा SB_RSVD_BIT2		0x00040000
#घोषणा SB_EXCEP_ERR_FLAG	0x00080000
#घोषणा SB_SYSE_ERR_FLAG	0x00100000
#घोषणा SB_PARE_ERR_FLAG	0x00200000
#घोषणा SB_TAS_ERR_FLAG		0x00400000
#घोषणा SB_PM		0x04
#घोषणा SB_DIAG		0x05

/*
 * SB SPEC.
 */
#घोषणा SB_CTRL		0x10
#घोषणा SB_R0		0x20
#घोषणा SB_R1		0x21
#घोषणा SB_R2		0x22
#घोषणा SB_R3		0x23
#घोषणा SB_R4		0x24
#घोषणा SB_R5		0x25
#घोषणा SB_R6		0x26
#घोषणा SB_R7		0x27
#घोषणा SB_R8		0x28
#घोषणा SB_R9		0x29
#घोषणा SB_R10		0x2A
#घोषणा SB_R11		0x2B
#घोषणा SB_R12		0x2C
#घोषणा SB_R13		0x2D
#घोषणा SB_R14		0x2E
#घोषणा SB_R15		0x2F

/*
 * GLCP STANDARD
 */
#घोषणा GLCP_CAP		0x00
#घोषणा GLCP_CONFIG		0x01
#घोषणा GLCP_SMI		0x02
#घोषणा GLCP_ERROR		0x03
#घोषणा GLCP_PM			0x04
#घोषणा GLCP_DIAG		0x05

/*
 * GLCP SPEC.
 */
#घोषणा GLCP_CLK_DIS_DELAY	0x08
#घोषणा GLCP_PM_CLK_DISABLE	0x09
#घोषणा GLCP_GLB_PM		0x0B
#घोषणा GLCP_DBG_OUT		0x0C
#घोषणा GLCP_RSVD1		0x0D
#घोषणा GLCP_SOFT_COM		0x0E
#घोषणा SOFT_BAR_SMB_FLAG	0x00000001
#घोषणा SOFT_BAR_GPIO_FLAG	0x00000002
#घोषणा SOFT_BAR_MFGPT_FLAG	0x00000004
#घोषणा SOFT_BAR_IRQ_FLAG	0x00000008
#घोषणा SOFT_BAR_PMS_FLAG	0x00000010
#घोषणा SOFT_BAR_ACPI_FLAG	0x00000020
#घोषणा SOFT_BAR_IDE_FLAG	0x00000400
#घोषणा SOFT_BAR_ACC_FLAG	0x00000800
#घोषणा SOFT_BAR_OHCI_FLAG	0x00001000
#घोषणा SOFT_BAR_EHCI_FLAG	0x00002000
#घोषणा GLCP_RSVD2		0x0F
#घोषणा GLCP_CLK_OFF		0x10
#घोषणा GLCP_CLK_ACTIVE		0x11
#घोषणा GLCP_CLK_DISABLE	0x12
#घोषणा GLCP_CLK4ACK		0x13
#घोषणा GLCP_SYS_RST		0x14
#घोषणा GLCP_RSVD3		0x15
#घोषणा GLCP_DBG_CLK_CTRL	0x16
#घोषणा GLCP_CHIP_REV_ID	0x17

/* PIC */
#घोषणा PIC_YSEL_LOW		0x20
#घोषणा PIC_YSEL_LOW_USB_SHIFT		8
#घोषणा PIC_YSEL_LOW_ACC_SHIFT		16
#घोषणा PIC_YSEL_LOW_FLASH_SHIFT	24
#घोषणा PIC_YSEL_HIGH		0x21
#घोषणा PIC_ZSEL_LOW		0x22
#घोषणा PIC_ZSEL_HIGH		0x23
#घोषणा PIC_IRQM_PRIM		0x24
#घोषणा PIC_IRQM_LPC		0x25
#घोषणा PIC_XIRR_STS_LOW	0x26
#घोषणा PIC_XIRR_STS_HIGH	0x27
#घोषणा PCI_SHDW		0x34

/*
 * DIVIL STANDARD
 */
#घोषणा DIVIL_CAP		0x00
#घोषणा DIVIL_CONFIG		0x01
#घोषणा DIVIL_SMI		0x02
#घोषणा DIVIL_ERROR		0x03
#घोषणा DIVIL_PM		0x04
#घोषणा DIVIL_DIAG		0x05

/*
 * DIVIL SPEC.
 */
#घोषणा DIVIL_LBAR_IRQ		0x08
#घोषणा DIVIL_LBAR_KEL		0x09
#घोषणा DIVIL_LBAR_SMB		0x0B
#घोषणा DIVIL_LBAR_GPIO		0x0C
#घोषणा DIVIL_LBAR_MFGPT	0x0D
#घोषणा DIVIL_LBAR_ACPI		0x0E
#घोषणा DIVIL_LBAR_PMS		0x0F
#घोषणा DIVIL_LEG_IO		0x14
#घोषणा DIVIL_BALL_OPTS		0x15
#घोषणा DIVIL_SOFT_IRQ		0x16
#घोषणा DIVIL_SOFT_RESET	0x17

/* MFGPT */
#घोषणा MFGPT_IRQ	0x28

/*
 * IDE STANDARD
 */
#घोषणा IDE_CAP		0x00
#घोषणा IDE_CONFIG	0x01
#घोषणा IDE_SMI		0x02
#घोषणा IDE_ERROR	0x03
#घोषणा IDE_PM		0x04
#घोषणा IDE_DIAG	0x05

/*
 * IDE SPEC.
 */
#घोषणा IDE_IO_BAR	0x08
#घोषणा IDE_CFG		0x10
#घोषणा IDE_DTC		0x12
#घोषणा IDE_CAST	0x13
#घोषणा IDE_ETC		0x14
#घोषणा IDE_INTERNAL_PM 0x15

/*
 * ACC STANDARD
 */
#घोषणा ACC_CAP		0x00
#घोषणा ACC_CONFIG	0x01
#घोषणा ACC_SMI		0x02
#घोषणा ACC_ERROR	0x03
#घोषणा ACC_PM		0x04
#घोषणा ACC_DIAG	0x05

/*
 * USB STANDARD
 */
#घोषणा USB_CAP		0x00
#घोषणा USB_CONFIG	0x01
#घोषणा USB_SMI		0x02
#घोषणा USB_ERROR	0x03
#घोषणा USB_PM		0x04
#घोषणा USB_DIAG	0x05

/*
 * USB SPEC.
 */
#घोषणा USB_OHCI	0x08
#घोषणा USB_EHCI	0x09

/****************** NATIVE ***************************/
/* GPIO : I/O SPACE; REG : 32BITS */
#घोषणा GPIOL_OUT_VAL		0x00
#घोषणा GPIOL_OUT_EN		0x04

#पूर्ण_अगर				/* _CS5536_H */
