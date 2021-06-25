<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/debugfs.h>

#समावेश "debugfs_engines.h"
#समावेश "debugfs_gt.h"
#समावेश "debugfs_gt_pm.h"
#समावेश "intel_sseu_debugfs.h"
#समावेश "uc/intel_uc_debugfs.h"
#समावेश "i915_drv.h"

व्योम debugfs_gt_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा dentry *root;

	अगर (!gt->i915->drm.primary->debugfs_root)
		वापस;

	root = debugfs_create_dir("gt", gt->i915->drm.primary->debugfs_root);
	अगर (IS_ERR(root))
		वापस;

	debugfs_engines_रेजिस्टर(gt, root);
	debugfs_gt_pm_रेजिस्टर(gt, root);
	पूर्णांकel_sseu_debugfs_रेजिस्टर(gt, root);

	पूर्णांकel_uc_debugfs_रेजिस्टर(&gt->uc, root);
पूर्ण

व्योम पूर्णांकel_gt_debugfs_रेजिस्टर_files(काष्ठा dentry *root,
				     स्थिर काष्ठा debugfs_gt_file *files,
				     अचिन्हित दीर्घ count, व्योम *data)
अणु
	जबतक (count--) अणु
		umode_t mode = files->fops->ग_लिखो ? 0644 : 0444;

		अगर (!files->eval || files->eval(data))
			debugfs_create_file(files->name,
					    mode, root, data,
					    files->fops);

		files++;
	पूर्ण
पूर्ण
