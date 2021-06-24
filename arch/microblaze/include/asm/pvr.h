<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम the MicroBlaze PVR (Processor Version Register)
 *
 * Copyright (C) 2009 - 2011 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007 John Williams <john.williams@petalogix.com>
 * Copyright (C) 2007 - 2011 PetaLogix
 */

#अगर_अघोषित _ASM_MICROBLAZE_PVR_H
#घोषणा _ASM_MICROBLAZE_PVR_H

#घोषणा PVR_MSR_BIT 0x400

काष्ठा pvr_s अणु
	अचिन्हित pvr[12];
पूर्ण;

/* The following taken from Xilinx's standalone BSP pvr.h */

/* Basic PVR mask */
#घोषणा PVR0_PVR_FULL_MASK		0x80000000
#घोषणा PVR0_USE_BARREL_MASK		0x40000000
#घोषणा PVR0_USE_DIV_MASK		0x20000000
#घोषणा PVR0_USE_HW_MUL_MASK		0x10000000
#घोषणा PVR0_USE_FPU_MASK		0x08000000
#घोषणा PVR0_USE_EXC_MASK		0x04000000
#घोषणा PVR0_USE_ICACHE_MASK		0x02000000
#घोषणा PVR0_USE_DCACHE_MASK		0x01000000
#घोषणा PVR0_USE_MMU			0x00800000
#घोषणा PVR0_USE_BTC			0x00400000
#घोषणा PVR0_ENDI			0x00200000
#घोषणा PVR0_VERSION_MASK		0x0000FF00
#घोषणा PVR0_USER1_MASK			0x000000FF

/* User 2 PVR mask */
#घोषणा PVR1_USER2_MASK			0xFFFFFFFF

/* Configuration PVR masks */
#घोषणा PVR2_D_OPB_MASK			0x80000000 /* or AXI */
#घोषणा PVR2_D_LMB_MASK			0x40000000
#घोषणा PVR2_I_OPB_MASK			0x20000000 /* or AXI */
#घोषणा PVR2_I_LMB_MASK			0x10000000
#घोषणा PVR2_INTERRUPT_IS_EDGE_MASK	0x08000000
#घोषणा PVR2_EDGE_IS_POSITIVE_MASK	0x04000000
#घोषणा PVR2_D_PLB_MASK			0x02000000 /* new */
#घोषणा PVR2_I_PLB_MASK			0x01000000 /* new */
#घोषणा PVR2_INTERCONNECT		0x00800000 /* new */
#घोषणा PVR2_USE_EXTEND_FSL		0x00080000 /* new */
#घोषणा PVR2_USE_FSL_EXC		0x00040000 /* new */
#घोषणा PVR2_USE_MSR_INSTR		0x00020000
#घोषणा PVR2_USE_PCMP_INSTR		0x00010000
#घोषणा PVR2_AREA_OPTIMISED		0x00008000
#घोषणा PVR2_USE_BARREL_MASK		0x00004000
#घोषणा PVR2_USE_DIV_MASK		0x00002000
#घोषणा PVR2_USE_HW_MUL_MASK		0x00001000
#घोषणा PVR2_USE_FPU_MASK		0x00000800
#घोषणा PVR2_USE_MUL64_MASK		0x00000400
#घोषणा PVR2_USE_FPU2_MASK		0x00000200 /* new */
#घोषणा PVR2_USE_IPLBEXC 		0x00000100
#घोषणा PVR2_USE_DPLBEXC		0x00000080
#घोषणा PVR2_OPCODE_0x0_ILL_MASK	0x00000040
#घोषणा PVR2_UNALIGNED_EXC_MASK		0x00000020
#घोषणा PVR2_ILL_OPCODE_EXC_MASK	0x00000010
#घोषणा PVR2_IOPB_BUS_EXC_MASK		0x00000008 /* or AXI */
#घोषणा PVR2_DOPB_BUS_EXC_MASK		0x00000004 /* or AXI */
#घोषणा PVR2_DIV_ZERO_EXC_MASK		0x00000002
#घोषणा PVR2_FPU_EXC_MASK		0x00000001

/* Debug and exception PVR masks */
#घोषणा PVR3_DEBUG_ENABLED_MASK		0x80000000
#घोषणा PVR3_NUMBER_OF_PC_BRK_MASK	0x1E000000
#घोषणा PVR3_NUMBER_OF_RD_ADDR_BRK_MASK	0x00380000
#घोषणा PVR3_NUMBER_OF_WR_ADDR_BRK_MASK	0x0000E000
#घोषणा PVR3_FSL_LINKS_MASK		0x00000380

/* ICache config PVR masks */
#घोषणा PVR4_USE_ICACHE_MASK		0x80000000 /* ICU */
#घोषणा PVR4_ICACHE_ADDR_TAG_BITS_MASK	0x7C000000 /* ICTS */
#घोषणा PVR4_ICACHE_ALLOW_WR_MASK	0x01000000 /* ICW */
#घोषणा PVR4_ICACHE_LINE_LEN_MASK	0x00E00000 /* ICLL */
#घोषणा PVR4_ICACHE_BYTE_SIZE_MASK	0x001F0000 /* ICBS */
#घोषणा PVR4_ICACHE_ALWAYS_USED		0x00008000 /* IAU */
#घोषणा PVR4_ICACHE_INTERFACE		0x00002000 /* ICI */

/* DCache config PVR masks */
#घोषणा PVR5_USE_DCACHE_MASK		0x80000000 /* DCU */
#घोषणा PVR5_DCACHE_ADDR_TAG_BITS_MASK	0x7C000000 /* DCTS */
#घोषणा PVR5_DCACHE_ALLOW_WR_MASK	0x01000000 /* DCW */
#घोषणा PVR5_DCACHE_LINE_LEN_MASK	0x00E00000 /* DCLL */
#घोषणा PVR5_DCACHE_BYTE_SIZE_MASK	0x001F0000 /* DCBS */
#घोषणा PVR5_DCACHE_ALWAYS_USED		0x00008000 /* DAU */
#घोषणा PVR5_DCACHE_USE_WRITEBACK	0x00004000 /* DWB */
#घोषणा PVR5_DCACHE_INTERFACE		0x00002000 /* DCI */

/* ICache base address PVR mask */
#घोषणा PVR6_ICACHE_BASEADDR_MASK	0xFFFFFFFF

/* ICache high address PVR mask */
#घोषणा PVR7_ICACHE_HIGHADDR_MASK	0xFFFFFFFF

/* DCache base address PVR mask */
#घोषणा PVR8_DCACHE_BASEADDR_MASK	0xFFFFFFFF

/* DCache high address PVR mask */
#घोषणा PVR9_DCACHE_HIGHADDR_MASK	0xFFFFFFFF

/* Target family PVR mask */
#घोषणा PVR10_TARGET_FAMILY_MASK	0xFF000000

/* MMU description */
#घोषणा PVR11_USE_MMU			0xC0000000
#घोषणा PVR11_MMU_ITLB_SIZE		0x38000000
#घोषणा PVR11_MMU_DTLB_SIZE		0x07000000
#घोषणा PVR11_MMU_TLB_ACCESS		0x00C00000
#घोषणा PVR11_MMU_ZONES			0x003C0000
#घोषणा PVR11_MMU_PRIVINS		0x00010000
/* MSR Reset value PVR mask */
#घोषणा PVR11_MSR_RESET_VALUE_MASK	0x000007FF

/* PVR access macros */
#घोषणा PVR_IS_FULL(_pvr)	(_pvr.pvr[0] & PVR0_PVR_FULL_MASK)
#घोषणा PVR_USE_BARREL(_pvr)	(_pvr.pvr[0] & PVR0_USE_BARREL_MASK)
#घोषणा PVR_USE_DIV(_pvr)	(_pvr.pvr[0] & PVR0_USE_DIV_MASK)
#घोषणा PVR_USE_HW_MUL(_pvr)	(_pvr.pvr[0] & PVR0_USE_HW_MUL_MASK)
#घोषणा PVR_USE_FPU(_pvr)	(_pvr.pvr[0] & PVR0_USE_FPU_MASK)
#घोषणा PVR_USE_FPU2(_pvr)	(_pvr.pvr[2] & PVR2_USE_FPU2_MASK)
#घोषणा PVR_USE_ICACHE(_pvr)	(_pvr.pvr[0] & PVR0_USE_ICACHE_MASK)
#घोषणा PVR_USE_DCACHE(_pvr)	(_pvr.pvr[0] & PVR0_USE_DCACHE_MASK)
#घोषणा PVR_VERSION(_pvr)	((_pvr.pvr[0] & PVR0_VERSION_MASK) >> 8)
#घोषणा PVR_USER1(_pvr)		(_pvr.pvr[0] & PVR0_USER1_MASK)
#घोषणा PVR_USER2(_pvr)		(_pvr.pvr[1] & PVR1_USER2_MASK)

#घोषणा PVR_D_OPB(_pvr)		(_pvr.pvr[2] & PVR2_D_OPB_MASK)
#घोषणा PVR_D_LMB(_pvr)		(_pvr.pvr[2] & PVR2_D_LMB_MASK)
#घोषणा PVR_I_OPB(_pvr)		(_pvr.pvr[2] & PVR2_I_OPB_MASK)
#घोषणा PVR_I_LMB(_pvr)		(_pvr.pvr[2] & PVR2_I_LMB_MASK)
#घोषणा PVR_INTERRUPT_IS_EDGE(_pvr) \
			(_pvr.pvr[2] & PVR2_INTERRUPT_IS_EDGE_MASK)
#घोषणा PVR_EDGE_IS_POSITIVE(_pvr) \
			(_pvr.pvr[2] & PVR2_EDGE_IS_POSITIVE_MASK)
#घोषणा PVR_USE_MSR_INSTR(_pvr)		(_pvr.pvr[2] & PVR2_USE_MSR_INSTR)
#घोषणा PVR_USE_PCMP_INSTR(_pvr)	(_pvr.pvr[2] & PVR2_USE_PCMP_INSTR)
#घोषणा PVR_AREA_OPTIMISED(_pvr)	(_pvr.pvr[2] & PVR2_AREA_OPTIMISED)
#घोषणा PVR_USE_MUL64(_pvr)		(_pvr.pvr[2] & PVR2_USE_MUL64_MASK)
#घोषणा PVR_OPCODE_0x0_ILLEGAL(_pvr) \
			(_pvr.pvr[2] & PVR2_OPCODE_0x0_ILL_MASK)
#घोषणा PVR_UNALIGNED_EXCEPTION(_pvr) \
			(_pvr.pvr[2] & PVR2_UNALIGNED_EXC_MASK)
#घोषणा PVR_ILL_OPCODE_EXCEPTION(_pvr) \
			(_pvr.pvr[2] & PVR2_ILL_OPCODE_EXC_MASK)
#घोषणा PVR_IOPB_BUS_EXCEPTION(_pvr) \
			(_pvr.pvr[2] & PVR2_IOPB_BUS_EXC_MASK)
#घोषणा PVR_DOPB_BUS_EXCEPTION(_pvr) \
			(_pvr.pvr[2] & PVR2_DOPB_BUS_EXC_MASK)
#घोषणा PVR_DIV_ZERO_EXCEPTION(_pvr) \
			(_pvr.pvr[2] & PVR2_DIV_ZERO_EXC_MASK)
#घोषणा PVR_FPU_EXCEPTION(_pvr)		(_pvr.pvr[2] & PVR2_FPU_EXC_MASK)
#घोषणा PVR_FSL_EXCEPTION(_pvr)		(_pvr.pvr[2] & PVR2_USE_EXTEND_FSL)

#घोषणा PVR_DEBUG_ENABLED(_pvr)		(_pvr.pvr[3] & PVR3_DEBUG_ENABLED_MASK)
#घोषणा PVR_NUMBER_OF_PC_BRK(_pvr) \
			((_pvr.pvr[3] & PVR3_NUMBER_OF_PC_BRK_MASK) >> 25)
#घोषणा PVR_NUMBER_OF_RD_ADDR_BRK(_pvr) \
			((_pvr.pvr[3] & PVR3_NUMBER_OF_RD_ADDR_BRK_MASK) >> 19)
#घोषणा PVR_NUMBER_OF_WR_ADDR_BRK(_pvr) \
			((_pvr.pvr[3] & PVR3_NUMBER_OF_WR_ADDR_BRK_MASK) >> 13)
#घोषणा PVR_FSL_LINKS(_pvr)	((_pvr.pvr[3] & PVR3_FSL_LINKS_MASK) >> 7)

#घोषणा PVR_ICACHE_ADDR_TAG_BITS(_pvr) \
		((_pvr.pvr[4] & PVR4_ICACHE_ADDR_TAG_BITS_MASK) >> 26)
#घोषणा PVR_ICACHE_USE_FSL(_pvr) \
		(_pvr.pvr[4] & PVR4_ICACHE_USE_FSL_MASK)
#घोषणा PVR_ICACHE_ALLOW_WR(_pvr) \
		(_pvr.pvr[4] & PVR4_ICACHE_ALLOW_WR_MASK)
#घोषणा PVR_ICACHE_LINE_LEN(_pvr) \
		(1 << ((_pvr.pvr[4] & PVR4_ICACHE_LINE_LEN_MASK) >> 21))
#घोषणा PVR_ICACHE_BYTE_SIZE(_pvr) \
		(1 << ((_pvr.pvr[4] & PVR4_ICACHE_BYTE_SIZE_MASK) >> 16))

#घोषणा PVR_DCACHE_ADDR_TAG_BITS(_pvr) \
			((_pvr.pvr[5] & PVR5_DCACHE_ADDR_TAG_BITS_MASK) >> 26)
#घोषणा PVR_DCACHE_USE_FSL(_pvr)	(_pvr.pvr[5] & PVR5_DCACHE_USE_FSL_MASK)
#घोषणा PVR_DCACHE_ALLOW_WR(_pvr) \
			(_pvr.pvr[5] & PVR5_DCACHE_ALLOW_WR_MASK)
/* FIXME two shअगरts on one line needs any comment */
#घोषणा PVR_DCACHE_LINE_LEN(_pvr) \
		(1 << ((_pvr.pvr[5] & PVR5_DCACHE_LINE_LEN_MASK) >> 21))
#घोषणा PVR_DCACHE_BYTE_SIZE(_pvr) \
		(1 << ((_pvr.pvr[5] & PVR5_DCACHE_BYTE_SIZE_MASK) >> 16))

#घोषणा PVR_DCACHE_USE_WRITEBACK(_pvr) \
			((_pvr.pvr[5] & PVR5_DCACHE_USE_WRITEBACK) >> 14)

#घोषणा PVR_ICACHE_BASEADDR(_pvr) \
			(_pvr.pvr[6] & PVR6_ICACHE_BASEADDR_MASK)
#घोषणा PVR_ICACHE_HIGHADDR(_pvr) \
			(_pvr.pvr[7] & PVR7_ICACHE_HIGHADDR_MASK)
#घोषणा PVR_DCACHE_BASEADDR(_pvr) \
			(_pvr.pvr[8] & PVR8_DCACHE_BASEADDR_MASK)
#घोषणा PVR_DCACHE_HIGHADDR(_pvr) \
			(_pvr.pvr[9] & PVR9_DCACHE_HIGHADDR_MASK)

#घोषणा PVR_TARGET_FAMILY(_pvr) \
			((_pvr.pvr[10] & PVR10_TARGET_FAMILY_MASK) >> 24)

#घोषणा PVR_MSR_RESET_VALUE(_pvr) \
			(_pvr.pvr[11] & PVR11_MSR_RESET_VALUE_MASK)

/* mmu */
#घोषणा PVR_USE_MMU(_pvr)		((_pvr.pvr[11] & PVR11_USE_MMU) >> 30)
#घोषणा PVR_MMU_ITLB_SIZE(_pvr)		(_pvr.pvr[11] & PVR11_MMU_ITLB_SIZE)
#घोषणा PVR_MMU_DTLB_SIZE(_pvr)		(_pvr.pvr[11] & PVR11_MMU_DTLB_SIZE)
#घोषणा PVR_MMU_TLB_ACCESS(_pvr)	(_pvr.pvr[11] & PVR11_MMU_TLB_ACCESS)
#घोषणा PVR_MMU_ZONES(_pvr)		(_pvr.pvr[11] & PVR11_MMU_ZONES)
#घोषणा PVR_MMU_PRIVINS(pvr)		(pvr.pvr[11] & PVR11_MMU_PRIVINS)

/* endian */
#घोषणा PVR_ENDIAN(_pvr)	(_pvr.pvr[0] & PVR0_ENDI)

पूर्णांक cpu_has_pvr(व्योम);
व्योम get_pvr(काष्ठा pvr_s *pvr);

#पूर्ण_अगर /* _ASM_MICROBLAZE_PVR_H */
