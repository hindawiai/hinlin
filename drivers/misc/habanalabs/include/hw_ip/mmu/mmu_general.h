<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित INCLUDE_MMU_GENERAL_H_
#घोषणा INCLUDE_MMU_GENERAL_H_

#घोषणा PAGE_SHIFT_4KB			12
#घोषणा PAGE_SHIFT_2MB			21
#घोषणा PAGE_SIZE_2MB			(_AC(1, UL) << PAGE_SHIFT_2MB)
#घोषणा PAGE_SIZE_4KB			(_AC(1, UL) << PAGE_SHIFT_4KB)

#घोषणा PAGE_PRESENT_MASK		0x0000000000001ull
#घोषणा SWAP_OUT_MASK			0x0000000000004ull
#घोषणा LAST_MASK			0x0000000000800ull
#घोषणा HOP0_MASK			0x3000000000000ull
#घोषणा HOP1_MASK			0x0FF8000000000ull
#घोषणा HOP2_MASK			0x0007FC0000000ull
#घोषणा HOP3_MASK			0x000003FE00000ull
#घोषणा HOP4_MASK			0x00000001FF000ull
#घोषणा FLAGS_MASK			0x0000000000FFFull

#घोषणा HOP0_SHIFT			48
#घोषणा HOP1_SHIFT			39
#घोषणा HOP2_SHIFT			30
#घोषणा HOP3_SHIFT			21
#घोषणा HOP4_SHIFT			12

#घोषणा MMU_ARCH_5_HOPS			5

#घोषणा HOP_PHYS_ADDR_MASK		(~FLAGS_MASK)

#घोषणा HL_PTE_SIZE			माप(u64)
#घोषणा HOP_TABLE_SIZE			PAGE_SIZE_4KB
#घोषणा PTE_ENTRIES_IN_HOP		(HOP_TABLE_SIZE / HL_PTE_SIZE)
#घोषणा HOP0_TABLES_TOTAL_SIZE		(HOP_TABLE_SIZE * MAX_ASID)

#घोषणा MMU_HOP0_PA43_12_SHIFT		12
#घोषणा MMU_HOP0_PA49_44_SHIFT		(12 + 32)

#घोषणा MMU_CONFIG_TIMEOUT_USEC		2000 /* 2 ms */

#पूर्ण_अगर /* INCLUDE_MMU_GENERAL_H_ */
