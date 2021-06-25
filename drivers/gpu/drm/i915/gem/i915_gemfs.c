<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2017 Intel Corporation
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/pagemap.h>

#समावेश "i915_drv.h"
#समावेश "i915_gemfs.h"

पूर्णांक i915_gemfs_init(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा file_प्रणाली_type *type;
	काष्ठा vfsmount *gemfs;

	type = get_fs_type("tmpfs");
	अगर (!type)
		वापस -ENODEV;

	/*
	 * By creating our own shmemfs mountpoपूर्णांक, we can pass in
	 * mount flags that better match our useहाल.
	 *
	 * One example, although it is probably better with a per-file
	 * control, is selecting huge page allocations ("huge=within_size").
	 * Currently unused due to bandwidth issues (slow पढ़ोs) on Broadwell+.
	 */

	gemfs = kern_mount(type);
	अगर (IS_ERR(gemfs))
		वापस PTR_ERR(gemfs);

	i915->mm.gemfs = gemfs;

	वापस 0;
पूर्ण

व्योम i915_gemfs_fini(काष्ठा drm_i915_निजी *i915)
अणु
	kern_unmount(i915->mm.gemfs);
पूर्ण
