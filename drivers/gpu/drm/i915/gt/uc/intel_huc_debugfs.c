<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "gt/debugfs_gt.h"
#समावेश "intel_huc.h"
#समावेश "intel_huc_debugfs.h"

अटल पूर्णांक huc_info_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_huc *huc = m->निजी;
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	अगर (!पूर्णांकel_huc_is_supported(huc))
		वापस -ENODEV;

	पूर्णांकel_huc_load_status(huc, &p);

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(huc_info);

व्योम पूर्णांकel_huc_debugfs_रेजिस्टर(काष्ठा पूर्णांकel_huc *huc, काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "huc_info", &huc_info_fops, शून्य पूर्ण,
	पूर्ण;

	अगर (!पूर्णांकel_huc_is_supported(huc))
		वापस;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), huc);
पूर्ण
