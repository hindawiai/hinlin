<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/types.h>
#समावेश <linux/kconfig.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/umh.h>
#समावेश <linux/sysctl.h>

#समावेश "fallback.h"
#समावेश "firmware.h"

/*
 * firmware fallback configuration table
 */

काष्ठा firmware_fallback_config fw_fallback_config = अणु
	.क्रमce_sysfs_fallback = IS_ENABLED(CONFIG_FW_LOADER_USER_HELPER_FALLBACK),
	.loading_समयout = 60,
	.old_समयout = 60,
पूर्ण;
EXPORT_SYMBOL_NS_GPL(fw_fallback_config, FIRMWARE_LOADER_PRIVATE);

#अगर_घोषित CONFIG_SYSCTL
काष्ठा ctl_table firmware_config_table[] = अणु
	अणु
		.procname	= "force_sysfs_fallback",
		.data		= &fw_fallback_config.क्रमce_sysfs_fallback,
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोuपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "ignore_sysfs_fallback",
		.data		= &fw_fallback_config.ignore_sysfs_fallback,
		.maxlen         = माप(अचिन्हित पूर्णांक),
		.mode           = 0644,
		.proc_handler   = proc_करोuपूर्णांकvec_minmax,
		.extra1		= SYSCTL_ZERO,
		.extra2		= SYSCTL_ONE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
#पूर्ण_अगर
