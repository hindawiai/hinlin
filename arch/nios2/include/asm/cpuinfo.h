<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2011 Tobias Klauser <tklauser@distanz.ch>
 */

#अगर_अघोषित _ASM_NIOS2_CPUINFO_H
#घोषणा _ASM_NIOS2_CPUINFO_H

#समावेश <linux/types.h>

काष्ठा cpuinfo अणु
	/* Core CPU configuration */
	अक्षर cpu_impl[12];
	u32 cpu_घड़ी_freq;
	bool mmu;
	bool has_भाग;
	bool has_mul;
	bool has_mulx;
	bool has_bmx;
	bool has_cdx;

	/* CPU caches */
	u32 icache_line_size;
	u32 icache_size;
	u32 dcache_line_size;
	u32 dcache_size;

	/* TLB */
	u32 tlb_pid_num_bits;	/* number of bits used क्रम the PID in TLBMISC */
	u32 tlb_num_ways;
	u32 tlb_num_ways_log2;
	u32 tlb_num_entries;
	u32 tlb_num_lines;
	u32 tlb_ptr_sz;

	/* Addresses */
	u32 reset_addr;
	u32 exception_addr;
	u32 fast_tlb_miss_exc_addr;
पूर्ण;

बाह्य काष्ठा cpuinfo cpuinfo;

बाह्य व्योम setup_cpuinfo(व्योम);

#पूर्ण_अगर /* _ASM_NIOS2_CPUINFO_H */
