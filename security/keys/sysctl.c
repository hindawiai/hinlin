<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Key management controls
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/key.h>
#समावेश <linux/sysctl.h>
#समावेश "internal.h"

काष्ठा ctl_table key_sysctls[] = अणु
	अणु
		.procname = "maxkeys",
		.data = &key_quota_maxkeys,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ONE,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname = "maxbytes",
		.data = &key_quota_maxbytes,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ONE,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname = "root_maxkeys",
		.data = &key_quota_root_maxkeys,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ONE,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname = "root_maxbytes",
		.data = &key_quota_root_maxbytes,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ONE,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
	अणु
		.procname = "gc_delay",
		.data = &key_gc_delay,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ZERO,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
#अगर_घोषित CONFIG_PERSISTENT_KEYRINGS
	अणु
		.procname = "persistent_keyring_expiry",
		.data = &persistent_keyring_expiry,
		.maxlen = माप(अचिन्हित),
		.mode = 0644,
		.proc_handler = proc_करोपूर्णांकvec_minmax,
		.extra1 = (व्योम *) SYSCTL_ZERO,
		.extra2 = (व्योम *) SYSCTL_पूर्णांक_उच्च,
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;
