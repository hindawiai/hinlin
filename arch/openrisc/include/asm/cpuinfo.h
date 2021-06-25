<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_CPUINFO_H
#घोषणा __ASM_OPENRISC_CPUINFO_H

काष्ठा cpuinfo_or1k अणु
	u32 घड़ी_frequency;

	u32 icache_size;
	u32 icache_block_size;
	u32 icache_ways;

	u32 dcache_size;
	u32 dcache_block_size;
	u32 dcache_ways;

	u16 coreid;
पूर्ण;

बाह्य काष्ठा cpuinfo_or1k cpuinfo_or1k[NR_CPUS];
बाह्य व्योम setup_cpuinfo(व्योम);

#पूर्ण_अगर /* __ASM_OPENRISC_CPUINFO_H */
