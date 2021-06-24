<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/fs.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "gt/debugfs_gt.h"
#समावेश "intel_guc.h"
#समावेश "intel_guc_log.h"
#समावेश "intel_guc_log_debugfs.h"

अटल पूर्णांक guc_log_dump_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	वापस पूर्णांकel_guc_log_dump(m->निजी, &p, false);
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_log_dump);

अटल पूर्णांक guc_load_err_log_dump_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	वापस पूर्णांकel_guc_log_dump(m->निजी, &p, true);
पूर्ण
DEFINE_GT_DEBUGFS_ATTRIBUTE(guc_load_err_log_dump);

अटल पूर्णांक guc_log_level_get(व्योम *data, u64 *val)
अणु
	काष्ठा पूर्णांकel_guc_log *log = data;

	अगर (!पूर्णांकel_guc_is_used(log_to_guc(log)))
		वापस -ENODEV;

	*val = पूर्णांकel_guc_log_get_level(log);

	वापस 0;
पूर्ण

अटल पूर्णांक guc_log_level_set(व्योम *data, u64 val)
अणु
	काष्ठा पूर्णांकel_guc_log *log = data;

	अगर (!पूर्णांकel_guc_is_used(log_to_guc(log)))
		वापस -ENODEV;

	वापस पूर्णांकel_guc_log_set_level(log, val);
पूर्ण

DEFINE_SIMPLE_ATTRIBUTE(guc_log_level_fops,
			guc_log_level_get, guc_log_level_set,
			"%lld\n");

अटल पूर्णांक guc_log_relay_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा पूर्णांकel_guc_log *log = inode->i_निजी;

	अगर (!पूर्णांकel_guc_is_पढ़ोy(log_to_guc(log)))
		वापस -ENODEV;

	file->निजी_data = log;

	वापस पूर्णांकel_guc_log_relay_खोलो(log);
पूर्ण

अटल sमाप_प्रकार
guc_log_relay_ग_लिखो(काष्ठा file *filp,
		    स्थिर अक्षर __user *ubuf,
		    माप_प्रकार cnt,
		    loff_t *ppos)
अणु
	काष्ठा पूर्णांकel_guc_log *log = filp->निजी_data;
	पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक_from_user(ubuf, cnt, 0, &val);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Enable and start the guc log relay on value of 1.
	 * Flush log relay क्रम any other value.
	 */
	अगर (val == 1)
		ret = पूर्णांकel_guc_log_relay_start(log);
	अन्यथा
		पूर्णांकel_guc_log_relay_flush(log);

	वापस ret ?: cnt;
पूर्ण

अटल पूर्णांक guc_log_relay_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा पूर्णांकel_guc_log *log = inode->i_निजी;

	पूर्णांकel_guc_log_relay_बंद(log);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations guc_log_relay_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = guc_log_relay_खोलो,
	.ग_लिखो = guc_log_relay_ग_लिखो,
	.release = guc_log_relay_release,
पूर्ण;

व्योम पूर्णांकel_guc_log_debugfs_रेजिस्टर(काष्ठा पूर्णांकel_guc_log *log,
				    काष्ठा dentry *root)
अणु
	अटल स्थिर काष्ठा debugfs_gt_file files[] = अणु
		अणु "guc_log_dump", &guc_log_dump_fops, शून्य पूर्ण,
		अणु "guc_load_err_log_dump", &guc_load_err_log_dump_fops, शून्य पूर्ण,
		अणु "guc_log_level", &guc_log_level_fops, शून्य पूर्ण,
		अणु "guc_log_relay", &guc_log_relay_fops, शून्य पूर्ण,
	पूर्ण;

	अगर (!पूर्णांकel_guc_is_supported(log_to_guc(log)))
		वापस;

	पूर्णांकel_gt_debugfs_रेजिस्टर_files(root, files, ARRAY_SIZE(files), log);
पूर्ण

