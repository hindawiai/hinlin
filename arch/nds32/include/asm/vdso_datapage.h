<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2012 ARM Limited
// Copyright (C) 2005-2017 Andes Technology Corporation
#अगर_अघोषित __ASM_VDSO_DATAPAGE_H
#घोषणा __ASM_VDSO_DATAPAGE_H

#अगर_घोषित __KERNEL__

#अगर_अघोषित __ASSEMBLY__

काष्ठा vdso_data अणु
	bool cycle_count_करोwn;	/* समयr cyclye counter is decrease with समय */
	u32 cycle_count_offset;	/* offset of समयr cycle counter रेजिस्टर */
	u32 seq_count;		/* sequence count - odd during updates */
	u32 xसमय_coarse_sec;	/* coarse समय */
	u32 xसमय_coarse_nsec;

	u32 wपंचांग_घड़ी_sec;	/* wall to monotonic offset */
	u32 wपंचांग_घड़ी_nsec;
	u32 xसमय_घड़ी_sec;	/* CLOCK_REALTIME - seconds */
	u32 cs_mult;		/* घड़ीsource multiplier */
	u32 cs_shअगरt;		/* Cycle to nanosecond भागisor (घातer of two) */
	u32 hrसमयr_res;	/* hrसमयr resolution */

	u64 cs_cycle_last;	/* last cycle value */
	u64 cs_mask;		/* घड़ीsource mask */

	u64 xसमय_घड़ी_nsec;	/* CLOCK_REALTIME sub-ns base */
	u32 tz_minuteswest;	/* समयzone info क्रम समय_लोofday(2) */
	u32 tz_dstसमय;
पूर्ण;

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __ASM_VDSO_DATAPAGE_H */
