<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PowerPC 64-bit swsusp implementation
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <यंत्र/iommu.h>
#समावेश <linux/irq.h>
#समावेश <linux/sched.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/nmi.h>

व्योम करो_after_copyback(व्योम)
अणु
	iommu_restore();
	touch_softlockup_watchकरोg();
	mb();
पूर्ण

व्योम _iommu_save(व्योम)
अणु
	iommu_save();
पूर्ण
