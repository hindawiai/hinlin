<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (c) Copyright 2007 Hewlett-Packard Development Company, L.P.
 *        Contributed by Peter Keilty <peter.keilty@hp.com>
 *
 * fsyscall समय_लोofday data
 */

/* like बारpec, but includes "shifted nanoseconds" */
काष्ठा समय_sn_spec अणु
	u64	sec;
	u64	snsec;
पूर्ण;

काष्ठा fsyscall_gtod_data_t अणु
	seqcount_t	seq;
	काष्ठा समय_sn_spec wall_समय;
	काष्ठा समय_sn_spec monotonic_समय;
	u64		clk_mask;
	u32		clk_mult;
	u32		clk_shअगरt;
	व्योम		*clk_fsys_mmio;
	u64		clk_cycle_last;
पूर्ण ____cacheline_aligned;

काष्ठा itc_jitter_data_t अणु
	पूर्णांक		itc_jitter;
	u64		itc_lastcycle;
पूर्ण ____cacheline_aligned;

