<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************
 * features.c
 *
 * Xen feature flags.
 *
 * Copyright (c) 2006, Ian Campbell, XenSource Inc.
 */
#समावेश <linux/types.h>
#समावेश <linux/cache.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/version.h>
#समावेश <xen/features.h>

u8 xen_features[XENFEAT_NR_SUBMAPS * 32] __पढ़ो_mostly;
EXPORT_SYMBOL_GPL(xen_features);

व्योम xen_setup_features(व्योम)
अणु
	काष्ठा xen_feature_info fi;
	पूर्णांक i, j;

	क्रम (i = 0; i < XENFEAT_NR_SUBMAPS; i++) अणु
		fi.submap_idx = i;
		अगर (HYPERVISOR_xen_version(XENVER_get_features, &fi) < 0)
			अवरोध;
		क्रम (j = 0; j < 32; j++)
			xen_features[i * 32 + j] = !!(fi.submap & 1<<j);
	पूर्ण
पूर्ण
