<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common file क्रम modeset selftests.
 */

#समावेश <linux/module.h>

#समावेश "test-drm_modeset_common.h"

#घोषणा TESTS "drm_modeset_selftests.h"
#समावेश "drm_selftest.h"

#समावेश "drm_selftest.c"

अटल पूर्णांक __init test_drm_modeset_init(व्योम)
अणु
	पूर्णांक err;

	err = run_selftests(selftests, ARRAY_SIZE(selftests), शून्य);

	वापस err > 0 ? 0 : err;
पूर्ण

अटल व्योम __निकास test_drm_modeset_निकास(व्योम)
अणु
पूर्ण

module_init(test_drm_modeset_init);
module_निकास(test_drm_modeset_निकास);

MODULE_AUTHOR("Intel Corporation");
MODULE_LICENSE("GPL");
