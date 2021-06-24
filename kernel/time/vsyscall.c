<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 ARM Ltd.
 *
 * Generic implementation of update_vsyscall and update_vsyscall_tz.
 *
 * Based on the x86 specअगरic implementation.
 */

#समावेश <linux/hrसमयr.h>
#समावेश <linux/समयkeeper_पूर्णांकernal.h>
#समावेश <vdso/datapage.h>
#समावेश <vdso/helpers.h>
#समावेश <vdso/vsyscall.h>

#समावेश "timekeeping_internal.h"

अटल अंतरभूत व्योम update_vdso_data(काष्ठा vdso_data *vdata,
				    काष्ठा समयkeeper *tk)
अणु
	काष्ठा vdso_बारtamp *vdso_ts;
	u64 nsec, sec;

	vdata[CS_HRES_COARSE].cycle_last	= tk->tkr_mono.cycle_last;
	vdata[CS_HRES_COARSE].mask		= tk->tkr_mono.mask;
	vdata[CS_HRES_COARSE].mult		= tk->tkr_mono.mult;
	vdata[CS_HRES_COARSE].shअगरt		= tk->tkr_mono.shअगरt;
	vdata[CS_RAW].cycle_last		= tk->tkr_raw.cycle_last;
	vdata[CS_RAW].mask			= tk->tkr_raw.mask;
	vdata[CS_RAW].mult			= tk->tkr_raw.mult;
	vdata[CS_RAW].shअगरt			= tk->tkr_raw.shअगरt;

	/* CLOCK_MONOTONIC */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_MONOTONIC];
	vdso_ts->sec	= tk->xसमय_sec + tk->wall_to_monotonic.tv_sec;

	nsec = tk->tkr_mono.xसमय_nsec;
	nsec += ((u64)tk->wall_to_monotonic.tv_nsec << tk->tkr_mono.shअगरt);
	जबतक (nsec >= (((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt)) अणु
		nsec -= (((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt);
		vdso_ts->sec++;
	पूर्ण
	vdso_ts->nsec	= nsec;

	/* Copy MONOTONIC समय क्रम BOOTTIME */
	sec	= vdso_ts->sec;
	/* Add the boot offset */
	sec	+= tk->monotonic_to_boot.tv_sec;
	nsec	+= (u64)tk->monotonic_to_boot.tv_nsec << tk->tkr_mono.shअगरt;

	/* CLOCK_BOOTTIME */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_BOOTTIME];
	vdso_ts->sec	= sec;

	जबतक (nsec >= (((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt)) अणु
		nsec -= (((u64)NSEC_PER_SEC) << tk->tkr_mono.shअगरt);
		vdso_ts->sec++;
	पूर्ण
	vdso_ts->nsec	= nsec;

	/* CLOCK_MONOTONIC_RAW */
	vdso_ts		= &vdata[CS_RAW].baseसमय[CLOCK_MONOTONIC_RAW];
	vdso_ts->sec	= tk->raw_sec;
	vdso_ts->nsec	= tk->tkr_raw.xसमय_nsec;

	/* CLOCK_TAI */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_TAI];
	vdso_ts->sec	= tk->xसमय_sec + (s64)tk->tai_offset;
	vdso_ts->nsec	= tk->tkr_mono.xसमय_nsec;
पूर्ण

व्योम update_vsyscall(काष्ठा समयkeeper *tk)
अणु
	काष्ठा vdso_data *vdata = __arch_get_k_vdso_data();
	काष्ठा vdso_बारtamp *vdso_ts;
	s32 घड़ी_mode;
	u64 nsec;

	/* copy vsyscall data */
	vdso_ग_लिखो_begin(vdata);

	घड़ी_mode = tk->tkr_mono.घड़ी->vdso_घड़ी_mode;
	vdata[CS_HRES_COARSE].घड़ी_mode	= घड़ी_mode;
	vdata[CS_RAW].घड़ी_mode		= घड़ी_mode;

	/* CLOCK_REALTIME also required क्रम समय() */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_REALTIME];
	vdso_ts->sec	= tk->xसमय_sec;
	vdso_ts->nsec	= tk->tkr_mono.xसमय_nsec;

	/* CLOCK_REALTIME_COARSE */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_REALTIME_COARSE];
	vdso_ts->sec	= tk->xसमय_sec;
	vdso_ts->nsec	= tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt;

	/* CLOCK_MONOTONIC_COARSE */
	vdso_ts		= &vdata[CS_HRES_COARSE].baseसमय[CLOCK_MONOTONIC_COARSE];
	vdso_ts->sec	= tk->xसमय_sec + tk->wall_to_monotonic.tv_sec;
	nsec		= tk->tkr_mono.xसमय_nsec >> tk->tkr_mono.shअगरt;
	nsec		= nsec + tk->wall_to_monotonic.tv_nsec;
	vdso_ts->sec	+= __iter_भाग_u64_rem(nsec, NSEC_PER_SEC, &vdso_ts->nsec);

	/*
	 * Read without the seqlock held by घड़ी_getres().
	 * Note: No need to have a second copy.
	 */
	WRITE_ONCE(vdata[CS_HRES_COARSE].hrसमयr_res, hrसमयr_resolution);

	/*
	 * If the current घड़ीsource is not VDSO capable, then spare the
	 * update of the high resolution parts.
	 */
	अगर (घड़ी_mode != VDSO_CLOCKMODE_NONE)
		update_vdso_data(vdata, tk);

	__arch_update_vsyscall(vdata, tk);

	vdso_ग_लिखो_end(vdata);

	__arch_sync_vdso_data(vdata);
पूर्ण

व्योम update_vsyscall_tz(व्योम)
अणु
	काष्ठा vdso_data *vdata = __arch_get_k_vdso_data();

	vdata[CS_HRES_COARSE].tz_minuteswest = sys_tz.tz_minuteswest;
	vdata[CS_HRES_COARSE].tz_dstसमय = sys_tz.tz_dstसमय;

	__arch_sync_vdso_data(vdata);
पूर्ण

/**
 * vdso_update_begin - Start of a VDSO update section
 *
 * Allows architecture code to safely update the architecture specअगरic VDSO
 * data. Disables पूर्णांकerrupts, acquires समयkeeper lock to serialize against
 * concurrent updates from समयkeeping and invalidates the VDSO data
 * sequence counter to prevent concurrent पढ़ोers from accessing
 * inconsistent data.
 *
 * Returns: Saved पूर्णांकerrupt flags which need to be handed in to
 * vdso_update_end().
 */
अचिन्हित दीर्घ vdso_update_begin(व्योम)
अणु
	काष्ठा vdso_data *vdata = __arch_get_k_vdso_data();
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&समयkeeper_lock, flags);
	vdso_ग_लिखो_begin(vdata);
	वापस flags;
पूर्ण

/**
 * vdso_update_end - End of a VDSO update section
 * @flags:	Interrupt flags as वापसed from vdso_update_begin()
 *
 * Pairs with vdso_update_begin(). Marks vdso data consistent, invokes data
 * synchronization अगर the architecture requires it, drops समयkeeper lock
 * and restores पूर्णांकerrupt flags.
 */
व्योम vdso_update_end(अचिन्हित दीर्घ flags)
अणु
	काष्ठा vdso_data *vdata = __arch_get_k_vdso_data();

	vdso_ग_लिखो_end(vdata);
	__arch_sync_vdso_data(vdata);
	raw_spin_unlock_irqrestore(&समयkeeper_lock, flags);
पूर्ण
