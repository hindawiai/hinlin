<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "gt/debugfs_gt.h"
#समावेश "intel_guc.h"
#समावेश "intel_guc_debugfs.h"
#समावेश "intel_guc_log_debugfs.h"

अटल पूर्णांक guc_info_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_guc *guc = m->निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	अगर (!पूर्णांकel_guc_is_supported(guc))
		वापस -ENODEV;

	पूर्णांकel_guc_load_status(guc, &p);
	drm_माला_दो(&p, "\n");
	पूर्णांकel_guc_log_info(&guc->log, &p);

	/* Add more as required ... */

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_info);

व्योम पूर्णांकel_guc_debugfs_रेजिस्टर(काष्ठा पूर्णांकel_guc *guc, काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "guc_info", &guc_info_fops, शून्य पूर्ण,
	पूर्ण;

	अगर (!पूर्णांकel_guc_is_supported(guc))
		वापस;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), guc);
	पूर्णांकel_guc_log_debugfs_रेजिस्टर(&guc->log, root);
पूर्ण
