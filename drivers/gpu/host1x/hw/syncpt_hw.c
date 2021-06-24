<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Syncpoपूर्णांकs
 *
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/पन.स>

#समावेश "../dev.h"
#समावेश "../syncpt.h"

/*
 * Write the current syncpoपूर्णांक value back to hw.
 */
अटल व्योम syncpt_restore(काष्ठा host1x_syncpt *sp)
अणु
	u32 min = host1x_syncpt_पढ़ो_min(sp);
	काष्ठा host1x *host = sp->host;

	host1x_sync_ग_लिखोl(host, min, HOST1X_SYNC_SYNCPT(sp->id));
पूर्ण

/*
 * Write the current रुकोbase value back to hw.
 */
अटल व्योम syncpt_restore_रुको_base(काष्ठा host1x_syncpt *sp)
अणु
#अगर HOST1X_HW < 7
	काष्ठा host1x *host = sp->host;

	host1x_sync_ग_लिखोl(host, sp->base_val,
			   HOST1X_SYNC_SYNCPT_BASE(sp->id));
#पूर्ण_अगर
पूर्ण

/*
 * Read रुकोbase value from hw.
 */
अटल व्योम syncpt_पढ़ो_रुको_base(काष्ठा host1x_syncpt *sp)
अणु
#अगर HOST1X_HW < 7
	काष्ठा host1x *host = sp->host;

	sp->base_val =
		host1x_sync_पढ़ोl(host, HOST1X_SYNC_SYNCPT_BASE(sp->id));
#पूर्ण_अगर
पूर्ण

/*
 * Updates the last value पढ़ो from hardware.
 */
अटल u32 syncpt_load(काष्ठा host1x_syncpt *sp)
अणु
	काष्ठा host1x *host = sp->host;
	u32 old, live;

	/* Loop in हाल there's a race writing to min_val */
	करो अणु
		old = host1x_syncpt_पढ़ो_min(sp);
		live = host1x_sync_पढ़ोl(host, HOST1X_SYNC_SYNCPT(sp->id));
	पूर्ण जबतक ((u32)atomic_cmpxchg(&sp->min_val, old, live) != old);

	अगर (!host1x_syncpt_check_max(sp, live))
		dev_err(host->dev, "%s failed: id=%u, min=%d, max=%d\n",
			__func__, sp->id, host1x_syncpt_पढ़ो_min(sp),
			host1x_syncpt_पढ़ो_max(sp));

	वापस live;
पूर्ण

/*
 * Write a cpu syncpoपूर्णांक increment to the hardware, without touching
 * the cache.
 */
अटल पूर्णांक syncpt_cpu_incr(काष्ठा host1x_syncpt *sp)
अणु
	काष्ठा host1x *host = sp->host;
	u32 reg_offset = sp->id / 32;

	अगर (!host1x_syncpt_client_managed(sp) &&
	    host1x_syncpt_idle(sp))
		वापस -EINVAL;

	host1x_sync_ग_लिखोl(host, BIT(sp->id % 32),
			   HOST1X_SYNC_SYNCPT_CPU_INCR(reg_offset));
	wmb();

	वापस 0;
पूर्ण

/**
 * syncpt_assign_to_channel() - Assign syncpoपूर्णांक to channel
 * @sp: syncpoपूर्णांक
 * @ch: channel
 *
 * On chips with the syncpoपूर्णांक protection feature (Tegra186+), assign @sp to
 * @ch, preventing other channels from incrementing the syncpoपूर्णांकs. If @ch is
 * शून्य, unassigns the syncpoपूर्णांक.
 *
 * On older chips, करो nothing.
 */
अटल व्योम syncpt_assign_to_channel(काष्ठा host1x_syncpt *sp,
				  काष्ठा host1x_channel *ch)
अणु
#अगर HOST1X_HW >= 6
	काष्ठा host1x *host = sp->host;

	अगर (!host->hv_regs)
		वापस;

	host1x_sync_ग_लिखोl(host,
			   HOST1X_SYNC_SYNCPT_CH_APP_CH(ch ? ch->id : 0xff),
			   HOST1X_SYNC_SYNCPT_CH_APP(sp->id));
#पूर्ण_अगर
पूर्ण

/**
 * syncpt_enable_protection() - Enable syncpoपूर्णांक protection
 * @host: host1x instance
 *
 * On chips with the syncpoपूर्णांक protection feature (Tegra186+), enable this
 * feature. On older chips, करो nothing.
 */
अटल व्योम syncpt_enable_protection(काष्ठा host1x *host)
अणु
#अगर HOST1X_HW >= 6
	अगर (!host->hv_regs)
		वापस;

	host1x_hypervisor_ग_लिखोl(host, HOST1X_HV_SYNCPT_PROT_EN_CH_EN,
				 HOST1X_HV_SYNCPT_PROT_EN);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा host1x_syncpt_ops host1x_syncpt_ops = अणु
	.restore = syncpt_restore,
	.restore_रुको_base = syncpt_restore_रुको_base,
	.load_रुको_base = syncpt_पढ़ो_रुको_base,
	.load = syncpt_load,
	.cpu_incr = syncpt_cpu_incr,
	.assign_to_channel = syncpt_assign_to_channel,
	.enable_protection = syncpt_enable_protection,
पूर्ण;
