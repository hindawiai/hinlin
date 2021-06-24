<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub driver debugging
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>

#समावेश "intel_th.h"
#समावेश "debug.h"

काष्ठा dentry *पूर्णांकel_th_dbg;

व्योम पूर्णांकel_th_debug_init(व्योम)
अणु
	पूर्णांकel_th_dbg = debugfs_create_dir("intel_th", शून्य);
	अगर (IS_ERR(पूर्णांकel_th_dbg))
		पूर्णांकel_th_dbg = शून्य;
पूर्ण

व्योम पूर्णांकel_th_debug_करोne(व्योम)
अणु
	debugfs_हटाओ(पूर्णांकel_th_dbg);
	पूर्णांकel_th_dbg = शून्य;
पूर्ण
