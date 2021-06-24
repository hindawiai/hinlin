<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 *	Low-Level PCI Support क्रम SH7751 tarमाला_लो
 *
 *  Dustin McIntire (dustin@sensoria.com) (c) 2001
 *  Paul Mundt (lethal@linux-sh.org) (c) 2003
 */

#अगर_अघोषित _PCI_SH7751_H_
#घोषणा _PCI_SH7751_H_

/* Platक्रमm Specअगरic Values */
#घोषणा SH7751_VENDOR_ID             0x1054
#घोषणा SH7751_DEVICE_ID             0x3505
#घोषणा SH7751R_DEVICE_ID            0x350e

/* SH7751 Specअगरic Values */
#घोषणा SH7751_PCI_CONFIG_BASE	     0xFD000000  /* Config space base addr */
#घोषणा SH7751_PCI_CONFIG_SIZE       0x1000000   /* Config space size */
#घोषणा SH7751_PCI_MEMORY_BASE	     0xFD000000  /* Memory space base addr */
#घोषणा SH7751_PCI_MEM_SIZE          0x01000000  /* Size of Memory winकरोw */
#घोषणा SH7751_PCI_IO_BASE           0xFE240000  /* IO space base address */
#घोषणा SH7751_PCI_IO_SIZE           0x40000     /* Size of IO winकरोw */

#घोषणा SH7751_PCIREG_BASE           0xFE200000  /* PCI regs base address */

#घोषणा SH7751_PCICONF0            0x0           /* PCI Config Reg 0 */
  #घोषणा SH7751_PCICONF0_DEVID      0xFFFF0000  /* Device ID */
  #घोषणा SH7751_PCICONF0_VNDID      0x0000FFFF  /* Venकरोr ID */
#घोषणा SH7751_PCICONF1            0x4           /* PCI Config Reg 1 */
  #घोषणा SH7751_PCICONF1_DPE        0x80000000  /* Data Parity Error */
  #घोषणा SH7751_PCICONF1_SSE        0x40000000  /* System Error Status */
  #घोषणा SH7751_PCICONF1_RMA        0x20000000  /* Master Abort */
  #घोषणा SH7751_PCICONF1_RTA        0x10000000  /* Target Abort Rx Status */
  #घोषणा SH7751_PCICONF1_STA        0x08000000  /* Target Abort Exec Status */
  #घोषणा SH7751_PCICONF1_DEV        0x06000000  /* Timing Status */
  #घोषणा SH7751_PCICONF1_DPD        0x01000000  /* Data Parity Status */
  #घोषणा SH7751_PCICONF1_FBBC       0x00800000  /* Back 2 Back Status */
  #घोषणा SH7751_PCICONF1_UDF        0x00400000  /* User Defined Status */
  #घोषणा SH7751_PCICONF1_66M        0x00200000  /* 66Mhz Operation Status */
  #घोषणा SH7751_PCICONF1_PM         0x00100000  /* Power Management Status */
  #घोषणा SH7751_PCICONF1_PBBE       0x00000200  /* Back 2 Back Control */
  #घोषणा SH7751_PCICONF1_SER        0x00000100  /* SERR Output Control */
  #घोषणा SH7751_PCICONF1_WCC        0x00000080  /* Wait Cycle Control */
  #घोषणा SH7751_PCICONF1_PER        0x00000040  /* Parity Error Response */
  #घोषणा SH7751_PCICONF1_VPS        0x00000020  /* VGA Pallet Snoop */
  #घोषणा SH7751_PCICONF1_MWIE       0x00000010  /* Memory Write+Invalidate */
  #घोषणा SH7751_PCICONF1_SPC        0x00000008  /* Special Cycle Control */
  #घोषणा SH7751_PCICONF1_BUM        0x00000004  /* Bus Master Control */
  #घोषणा SH7751_PCICONF1_MES        0x00000002  /* Memory Space Control */
  #घोषणा SH7751_PCICONF1_IOS        0x00000001  /* I/O Space Control */
#घोषणा SH7751_PCICONF2            0x8           /* PCI Config Reg 2 */
  #घोषणा SH7751_PCICONF2_BCC        0xFF000000  /* Base Class Code */
  #घोषणा SH7751_PCICONF2_SCC        0x00FF0000  /* Sub-Class Code */
  #घोषणा SH7751_PCICONF2_RLPI       0x0000FF00  /* Programming Interface */
  #घोषणा SH7751_PCICONF2_REV        0x000000FF  /* Revision ID */
#घोषणा SH7751_PCICONF3            0xC           /* PCI Config Reg 3 */
  #घोषणा SH7751_PCICONF3_BIST7      0x80000000  /* Bist Supported */
  #घोषणा SH7751_PCICONF3_BIST6      0x40000000  /* Bist Executing */
  #घोषणा SH7751_PCICONF3_BIST3_0    0x0F000000  /* Bist Passed */
  #घोषणा SH7751_PCICONF3_HD7        0x00800000  /* Single Function device */
  #घोषणा SH7751_PCICONF3_HD6_0      0x007F0000  /* Configuration Layout */
  #घोषणा SH7751_PCICONF3_LAT        0x0000FF00  /* Latency Timer */
  #घोषणा SH7751_PCICONF3_CLS        0x000000FF  /* Cache Line Size */
#घोषणा SH7751_PCICONF4            0x10          /* PCI Config Reg 4 */
  #घोषणा SH7751_PCICONF4_BASE       0xFFFFFFFC  /* I/O Space Base Addr */
  #घोषणा SH7751_PCICONF4_ASI        0x00000001  /* Address Space Type */
#घोषणा SH7751_PCICONF5            0x14          /* PCI Config Reg 5 */
  #घोषणा SH7751_PCICONF5_BASE       0xFFFFFFF0  /* Mem Space Base Addr */
  #घोषणा SH7751_PCICONF5_LAP        0x00000008  /* Prefetch Enabled */
  #घोषणा SH7751_PCICONF5_LAT        0x00000006  /* Local Memory type */
  #घोषणा SH7751_PCICONF5_ASI        0x00000001  /* Address Space Type */
#घोषणा SH7751_PCICONF6            0x18          /* PCI Config Reg 6 */
  #घोषणा SH7751_PCICONF6_BASE       0xFFFFFFF0  /* Mem Space Base Addr */
  #घोषणा SH7751_PCICONF6_LAP        0x00000008  /* Prefetch Enabled */
  #घोषणा SH7751_PCICONF6_LAT        0x00000006  /* Local Memory type */
  #घोषणा SH7751_PCICONF6_ASI        0x00000001  /* Address Space Type */
/* PCICONF7 - PCICONF10 are undefined */
#घोषणा SH7751_PCICONF11           0x2C          /* PCI Config Reg 11 */
  #घोषणा SH7751_PCICONF11_SSID      0xFFFF0000  /* Subप्रणाली ID */
  #घोषणा SH7751_PCICONF11_SVID      0x0000FFFF  /* Subप्रणाली Venकरोr ID */
/* PCICONF12 is undefined */
#घोषणा SH7751_PCICONF13           0x34          /* PCI Config Reg 13 */
  #घोषणा SH7751_PCICONF13_CPTR      0x000000FF  /* PM function poपूर्णांकer */
/* PCICONF14 is undefined */
#घोषणा SH7751_PCICONF15           0x3C          /* PCI Config Reg 15 */
  #घोषणा SH7751_PCICONF15_IPIN      0x000000FF  /* Interrupt Pin */
#घोषणा SH7751_PCICONF16           0x40          /* PCI Config Reg 16 */
  #घोषणा SH7751_PCICONF16_PMES      0xF8000000  /* PME Support */
  #घोषणा SH7751_PCICONF16_D2S       0x04000000  /* D2 Support */
  #घोषणा SH7751_PCICONF16_D1S       0x02000000  /* D1 Support */
  #घोषणा SH7751_PCICONF16_DSI       0x00200000  /* Bit Device Init. */
  #घोषणा SH7751_PCICONF16_PMCK      0x00080000  /* Clock क्रम PME req. */
  #घोषणा SH7751_PCICONF16_VER       0x00070000  /* PM Version */
  #घोषणा SH7751_PCICONF16_NIP       0x0000FF00  /* Next Item Poपूर्णांकer */
  #घोषणा SH7751_PCICONF16_CID       0x000000FF  /* Capability Identअगरier */
#घोषणा SH7751_PCICONF17           0x44          /* PCI Config Reg 17 */
  #घोषणा SH7751_PCICONF17_DATA      0xFF000000  /* Data field क्रम PM */
  #घोषणा SH7751_PCICONF17_PMES      0x00800000  /* PME Status */
  #घोषणा SH7751_PCICONF17_DSCL      0x00600000  /* Data Scaling Value */
  #घोषणा SH7751_PCICONF17_DSEL      0x001E0000  /* Data Select */
  #घोषणा SH7751_PCICONF17_PMEN      0x00010000  /* PME Enable */
  #घोषणा SH7751_PCICONF17_PWST      0x00000003  /* Power State */
/* SH7715 Internal PCI Registers */

/* Memory Control Registers */
#घोषणा SH7751_BCR1                0xFF800000    /* Memory BCR1 Register */
#घोषणा SH7751_BCR2                0xFF800004    /* Memory BCR2 Register */
#घोषणा SH7751_BCR3                0xFF800050    /* Memory BCR3 Register */
#घोषणा SH7751_BCR4                0xFE0A00F0    /* Memory BCR4 Register */
#घोषणा SH7751_WCR1                0xFF800008    /* Wait Control 1 Register */
#घोषणा SH7751_WCR2                0xFF80000C    /* Wait Control 2 Register */
#घोषणा SH7751_WCR3                0xFF800010    /* Wait Control 3 Register */
#घोषणा SH7751_MCR                 0xFF800014    /* Memory Control Register */

/* General Memory Config Addresses */
#घोषणा SH7751_CS0_BASE_ADDR       0x0
#घोषणा SH7751_MEM_REGION_SIZE     0x04000000
#घोषणा SH7751_CS1_BASE_ADDR       (SH7751_CS0_BASE_ADDR + SH7751_MEM_REGION_SIZE)
#घोषणा SH7751_CS2_BASE_ADDR       (SH7751_CS1_BASE_ADDR + SH7751_MEM_REGION_SIZE)
#घोषणा SH7751_CS3_BASE_ADDR       (SH7751_CS2_BASE_ADDR + SH7751_MEM_REGION_SIZE)
#घोषणा SH7751_CS4_BASE_ADDR       (SH7751_CS3_BASE_ADDR + SH7751_MEM_REGION_SIZE)
#घोषणा SH7751_CS5_BASE_ADDR       (SH7751_CS4_BASE_ADDR + SH7751_MEM_REGION_SIZE)
#घोषणा SH7751_CS6_BASE_ADDR       (SH7751_CS5_BASE_ADDR + SH7751_MEM_REGION_SIZE)

#पूर्ण_अगर /* _PCI_SH7751_H_ */
