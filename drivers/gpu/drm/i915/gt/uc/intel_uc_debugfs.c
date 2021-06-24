<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/debugfs.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "gt/debugfs_gt.h"
#समावेश "intel_guc_debugfs.h"
#समावेश "intel_huc_debugfs.h"
#समावेश "intel_uc.h"
#समावेश "intel_uc_debugfs.h"

अटल पूर्णांक uc_usage_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_uc *uc = m->निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	drm_म_लिखो(&p, "[guc] supported:%s wanted:%s used:%s\n",
		   yesno(पूर्णांकel_uc_supports_guc(uc)),
		   yesno(पूर्णांकel_uc_wants_guc(uc)),
		   yesno(पूर्णांकel_uc_uses_guc(uc)));
	drm_म_लिखो(&p, "[huc] supported:%s wanted:%s used:%s\n",
		   yesno(पूर्णांकel_uc_supports_huc(uc)),
		   yesno(पूर्णांकel_uc_wants_huc(uc)),
		   yesno(पूर्णांकel_uc_uses_huc(uc)));
	drm_म_लिखो(&p, "[submission] supported:%s wanted:%s used:%s\n",
		   yesno(पूर्णांकel_uc_supports_guc_submission(uc)),
		   yesno(पूर्णांकel_uc_wants_guc_submission(uc)),
		   yesno(पूर्णांकel_uc_uses_guc_submission(uc)));

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(uc_usage);

व्योम पूर्णांकel_uc_debugfs_रेजिस्टर(काष्ठा पूर्णांकel_uc *uc, काष्ठा dentry *gt_root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "usage", &uc_usage_fops, शून्य पूर्ण,
	पूर्ण;
	काष्ठा dentry *root;

	अगर (!gt_root)
		वापस;

	/* GuC and HuC go always in pair, no need to check both */
	अगर (!पूर्णांकel_uc_supports_guc(uc))
		वापस;

	root = debugfs_create_dir("uc", gt_root);
	अगर (IS_ERR(root))
		वापस;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), uc);

	पूर्णांकel_guc_debugfs_रेजिस्टर(&uc->guc, root);
	पूर्णांकel_huc_debugfs_रेजिस्टर(&uc->huc, root);
पूर्ण
