<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Linaro Ltd.
 */

#समावेश <linux/debugfs.h>

#समावेश "core.h"

व्योम venus_dbgfs_init(काष्ठा venus_core *core)
अणु
	core->root = debugfs_create_dir("venus", शून्य);
	debugfs_create_x32("fw_level", 0644, core->root, &venus_fw_debug);
पूर्ण

व्योम venus_dbgfs_deinit(काष्ठा venus_core *core)
अणु
	debugfs_हटाओ_recursive(core->root);
पूर्ण
