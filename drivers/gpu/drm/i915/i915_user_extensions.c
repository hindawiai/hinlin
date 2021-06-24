<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2018 Intel Corporation
 */

#समावेश <linux/nospec.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/uaccess.h>

#समावेश <uapi/drm/i915_drm.h>

#समावेश "i915_user_extensions.h"
#समावेश "i915_utils.h"

पूर्णांक i915_user_extensions(काष्ठा i915_user_extension __user *ext,
			 स्थिर i915_user_extension_fn *tbl,
			 अचिन्हित पूर्णांक count,
			 व्योम *data)
अणु
	अचिन्हित पूर्णांक stackdepth = 512;

	जबतक (ext) अणु
		पूर्णांक i, err;
		u32 name;
		u64 next;

		अगर (!stackdepth--) /* recursion vs useful flexibility */
			वापस -E2BIG;

		err = check_user_mbz(&ext->flags);
		अगर (err)
			वापस err;

		क्रम (i = 0; i < ARRAY_SIZE(ext->rsvd); i++) अणु
			err = check_user_mbz(&ext->rsvd[i]);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (get_user(name, &ext->name))
			वापस -EFAULT;

		err = -EINVAL;
		अगर (name < count) अणु
			name = array_index_nospec(name, count);
			अगर (tbl[name])
				err = tbl[name](ext, data);
		पूर्ण
		अगर (err)
			वापस err;

		अगर (get_user(next, &ext->next_extension) ||
		    overflows_type(next, ext))
			वापस -EFAULT;

		ext = u64_to_user_ptr(next);
	पूर्ण

	वापस 0;
पूर्ण
