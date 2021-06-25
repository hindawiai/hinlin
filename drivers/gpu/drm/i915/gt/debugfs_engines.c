<शैली गुरु>
// SPDX-License-Identअगरier: MIT

/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "debugfs_engines.h"
#समावेश "debugfs_gt.h"
#समावेश "i915_drv.h" /* क्रम_each_engine! */
#समावेश "intel_engine.h"

अटल पूर्णांक engines_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा पूर्णांकel_gt *gt = m->निजी;
	काष्ठा पूर्णांकel_engine_cs *engine;
	क्रमागत पूर्णांकel_engine_id id;
	काष्ठा drm_prपूर्णांकer p;

	p = drm_seq_file_prपूर्णांकer(m);
	क्रम_each_engine(engine, gt, id)
		पूर्णांकel_engine_dump(engine, &p, "%s\n", engine->name);

	वापस 0;
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(engines);

व्योम debugfs_engines_रेजिस्टर(काष्ठा पूर्णांकel_gt *gt, काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "engines", &engines_fops पूर्ण,
	पूर्ण;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), gt);
पूर्ण
