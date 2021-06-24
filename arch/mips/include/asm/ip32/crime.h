<शैली गुरु>
/*
 * Definitions क्रम the SGI CRIME (CPU, Rendering, Interconnect and Memory
 * Engine)
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000 Harald Koerfgen
 */

#अगर_अघोषित __ASM_CRIME_H__
#घोषणा __ASM_CRIME_H__

/*
 * Address map
 */
#घोषणा CRIME_BASE	0x14000000	/* physical */

काष्ठा sgi_crime अणु
	अस्थिर अचिन्हित दीर्घ id;
#घोषणा CRIME_ID_MASK			0xff
#घोषणा CRIME_ID_IDBITS			0xf0
#घोषणा CRIME_ID_IDVALUE		0xa0
#घोषणा CRIME_ID_REV			0x0f
#घोषणा CRIME_REV_PETTY			0x00
#घोषणा CRIME_REV_11			0x11
#घोषणा CRIME_REV_13			0x13
#घोषणा CRIME_REV_14			0x14

	अस्थिर अचिन्हित दीर्घ control;
#घोषणा CRIME_CONTROL_MASK		0x3fff
#घोषणा CRIME_CONTROL_TRITON_SYSADC	0x2000
#घोषणा CRIME_CONTROL_CRIME_SYSADC	0x1000
#घोषणा CRIME_CONTROL_HARD_RESET	0x0800
#घोषणा CRIME_CONTROL_SOFT_RESET	0x0400
#घोषणा CRIME_CONTROL_DOG_ENA		0x0200
#घोषणा CRIME_CONTROL_ENDIANESS		0x0100
#घोषणा CRIME_CONTROL_ENDIAN_BIG	0x0100
#घोषणा CRIME_CONTROL_ENDIAN_LITTLE	0x0000
#घोषणा CRIME_CONTROL_CQUEUE_HWM	0x000f
#घोषणा CRIME_CONTROL_CQUEUE_SHFT	0
#घोषणा CRIME_CONTROL_WBUF_HWM		0x00f0
#घोषणा CRIME_CONTROL_WBUF_SHFT		8

	अस्थिर अचिन्हित दीर्घ istat;
	अस्थिर अचिन्हित दीर्घ imask;
	अस्थिर अचिन्हित दीर्घ soft_पूर्णांक;
	अस्थिर अचिन्हित दीर्घ hard_पूर्णांक;
#घोषणा MACE_VID_IN1_INT		BIT(0)
#घोषणा MACE_VID_IN2_INT		BIT(1)
#घोषणा MACE_VID_OUT_INT		BIT(2)
#घोषणा MACE_ETHERNET_INT		BIT(3)
#घोषणा MACE_SUPERIO_INT		BIT(4)
#घोषणा MACE_MISC_INT			BIT(5)
#घोषणा MACE_AUDIO_INT			BIT(6)
#घोषणा MACE_PCI_BRIDGE_INT		BIT(7)
#घोषणा MACEPCI_SCSI0_INT		BIT(8)
#घोषणा MACEPCI_SCSI1_INT		BIT(9)
#घोषणा MACEPCI_SLOT0_INT		BIT(10)
#घोषणा MACEPCI_SLOT1_INT		BIT(11)
#घोषणा MACEPCI_SLOT2_INT		BIT(12)
#घोषणा MACEPCI_SHARED0_INT		BIT(13)
#घोषणा MACEPCI_SHARED1_INT		BIT(14)
#घोषणा MACEPCI_SHARED2_INT		BIT(15)
#घोषणा CRIME_GBE0_INT			BIT(16)
#घोषणा CRIME_GBE1_INT			BIT(17)
#घोषणा CRIME_GBE2_INT			BIT(18)
#घोषणा CRIME_GBE3_INT			BIT(19)
#घोषणा CRIME_CPUERR_INT		BIT(20)
#घोषणा CRIME_MEMERR_INT		BIT(21)
#घोषणा CRIME_RE_EMPTY_E_INT		BIT(22)
#घोषणा CRIME_RE_FULL_E_INT		BIT(23)
#घोषणा CRIME_RE_IDLE_E_INT		BIT(24)
#घोषणा CRIME_RE_EMPTY_L_INT		BIT(25)
#घोषणा CRIME_RE_FULL_L_INT		BIT(26)
#घोषणा CRIME_RE_IDLE_L_INT		BIT(27)
#घोषणा CRIME_SOFT0_INT			BIT(28)
#घोषणा CRIME_SOFT1_INT			BIT(29)
#घोषणा CRIME_SOFT2_INT			BIT(30)
#घोषणा CRIME_SYSCORERR_INT		CRIME_SOFT2_INT
#घोषणा CRIME_VICE_INT			BIT(31)
/* Masks क्रम deciding who handles the पूर्णांकerrupt */
#घोषणा CRIME_MACE_INT_MASK		0x8f
#घोषणा CRIME_MACEISA_INT_MASK		0x70
#घोषणा CRIME_MACEPCI_INT_MASK		0xff00
#घोषणा CRIME_CRIME_INT_MASK		0xffff0000

	अस्थिर अचिन्हित दीर्घ watchकरोg;
#घोषणा CRIME_DOG_POWER_ON_RESET	0x00010000
#घोषणा CRIME_DOG_WARM_RESET		0x00080000
#घोषणा CRIME_DOG_TIMEOUT		(CRIME_DOG_POWER_ON_RESET|CRIME_DOG_WARM_RESET)
#घोषणा CRIME_DOG_VALUE			0x00007fff

	अस्थिर अचिन्हित दीर्घ समयr;
#घोषणा CRIME_MASTER_FREQ		66666500	/* Crime upcounter frequency */
#घोषणा CRIME_NS_PER_TICK		15		/* क्रम delay_calibrate */

	अस्थिर अचिन्हित दीर्घ cpu_error_addr;
#घोषणा CRIME_CPU_ERROR_ADDR_MASK	0x3ffffffff

	अस्थिर अचिन्हित दीर्घ cpu_error_stat;
#घोषणा CRIME_CPU_ERROR_MASK		0x7		/* cpu error stat is 3 bits */
#घोषणा CRIME_CPU_ERROR_CPU_ILL_ADDR	0x4
#घोषणा CRIME_CPU_ERROR_VICE_WRT_PRTY	0x2
#घोषणा CRIME_CPU_ERROR_CPU_WRT_PRTY	0x1

	अचिन्हित दीर्घ _pad0[54];

	अस्थिर अचिन्हित दीर्घ mc_ctrl;
	अस्थिर अचिन्हित दीर्घ bank_ctrl[8];
#घोषणा CRIME_MEM_BANK_CONTROL_MASK		0x11f	/* 9 bits 7:5 reserved */
#घोषणा CRIME_MEM_BANK_CONTROL_ADDR		0x01f
#घोषणा CRIME_MEM_BANK_CONTROL_SDRAM_SIZE	0x100
#घोषणा CRIME_MAXBANKS				8

	अस्थिर अचिन्हित दीर्घ mem_ref_counter;
#घोषणा CRIME_MEM_REF_COUNTER_MASK	0x3ff		/* 10bit */

	अस्थिर अचिन्हित दीर्घ mem_error_stat;
#घोषणा CRIME_MEM_ERROR_STAT_MASK	0x0ff7ffff	/* 28-bit रेजिस्टर */
#घोषणा CRIME_MEM_ERROR_MACE_ID		0x0000007f
#घोषणा CRIME_MEM_ERROR_MACE_ACCESS	0x00000080
#घोषणा CRIME_MEM_ERROR_RE_ID		0x00007f00
#घोषणा CRIME_MEM_ERROR_RE_ACCESS	0x00008000
#घोषणा CRIME_MEM_ERROR_GBE_ACCESS	0x00010000
#घोषणा CRIME_MEM_ERROR_VICE_ACCESS	0x00020000
#घोषणा CRIME_MEM_ERROR_CPU_ACCESS	0x00040000
#घोषणा CRIME_MEM_ERROR_RESERVED	0x00080000
#घोषणा CRIME_MEM_ERROR_SOFT_ERR	0x00100000
#घोषणा CRIME_MEM_ERROR_HARD_ERR	0x00200000
#घोषणा CRIME_MEM_ERROR_MULTIPLE	0x00400000
#घोषणा CRIME_MEM_ERROR_ECC		0x01800000
#घोषणा CRIME_MEM_ERROR_MEM_ECC_RD	0x00800000
#घोषणा CRIME_MEM_ERROR_MEM_ECC_RMW	0x01000000
#घोषणा CRIME_MEM_ERROR_INV		0x0e000000
#घोषणा CRIME_MEM_ERROR_INV_MEM_ADDR_RD 0x02000000
#घोषणा CRIME_MEM_ERROR_INV_MEM_ADDR_WR 0x04000000
#घोषणा CRIME_MEM_ERROR_INV_MEM_ADDR_RMW 0x08000000

	अस्थिर अचिन्हित दीर्घ mem_error_addr;
#घोषणा CRIME_MEM_ERROR_ADDR_MASK	0x3fffffff

	अस्थिर अचिन्हित दीर्घ mem_ecc_syn;
#घोषणा CRIME_MEM_ERROR_ECC_SYN_MASK	0xffffffff

	अस्थिर अचिन्हित दीर्घ mem_ecc_chk;
#घोषणा CRIME_MEM_ERROR_ECC_CHK_MASK	0xffffffff

	अस्थिर अचिन्हित दीर्घ mem_ecc_repl;
#घोषणा CRIME_MEM_ERROR_ECC_REPL_MASK	0xffffffff
पूर्ण;

बाह्य काष्ठा sgi_crime __iomem *crime;

#घोषणा CRIME_HI_MEM_BASE	0x40000000	/* this is where whole 1G of RAM is mapped */

#पूर्ण_अगर /* __ASM_CRIME_H__ */
