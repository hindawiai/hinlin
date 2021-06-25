<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/spinlock.h>
#समावेश "clk.h"

DEFINE_SPINLOCK(mxs_lock);

पूर्णांक mxs_clk_रुको(व्योम __iomem *reg, u8 shअगरt)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(10);

	जबतक (पढ़ोl_relaxed(reg) & (1 << shअगरt))
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;

	वापस 0;
पूर्ण
