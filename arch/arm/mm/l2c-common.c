<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 ARM Ltd.
 * Written by Catalin Marinas <catalin.marinas@arm.com>
 */
#समावेश <linux/bug.h>
#समावेश <linux/smp.h>
#समावेश <यंत्र/outercache.h>

व्योम outer_disable(व्योम)
अणु
	WARN_ON(!irqs_disabled());
	WARN_ON(num_online_cpus() > 1);

	अगर (outer_cache.disable)
		outer_cache.disable();
पूर्ण
