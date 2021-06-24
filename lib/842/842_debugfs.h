<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __842_DEBUGFS_H__
#घोषणा __842_DEBUGFS_H__

#समावेश <linux/debugfs.h>

अटल bool sw842_ढाँचा_counts;
module_param_named(ढाँचा_counts, sw842_ढाँचा_counts, bool, 0444);

अटल atomic_t ढाँचा_count[OPS_MAX], ढाँचा_repeat_count,
	ढाँचा_zeros_count, ढाँचा_लघु_data_count, ढाँचा_end_count;

अटल काष्ठा dentry *sw842_debugfs_root;

अटल पूर्णांक __init sw842_debugfs_create(व्योम)
अणु
	umode_t m = S_IRUGO | S_IWUSR;
	पूर्णांक i;

	अगर (!debugfs_initialized())
		वापस -ENODEV;

	sw842_debugfs_root = debugfs_create_dir(MODULE_NAME, शून्य);

	क्रम (i = 0; i < ARRAY_SIZE(ढाँचा_count); i++) अणु
		अक्षर name[32];

		snम_लिखो(name, 32, "template_%02x", i);
		debugfs_create_atomic_t(name, m, sw842_debugfs_root,
					&ढाँचा_count[i]);
	पूर्ण
	debugfs_create_atomic_t("template_repeat", m, sw842_debugfs_root,
				&ढाँचा_repeat_count);
	debugfs_create_atomic_t("template_zeros", m, sw842_debugfs_root,
				&ढाँचा_zeros_count);
	debugfs_create_atomic_t("template_short_data", m, sw842_debugfs_root,
				&ढाँचा_लघु_data_count);
	debugfs_create_atomic_t("template_end", m, sw842_debugfs_root,
				&ढाँचा_end_count);

	वापस 0;
पूर्ण

अटल व्योम __निकास sw842_debugfs_हटाओ(व्योम)
अणु
	debugfs_हटाओ_recursive(sw842_debugfs_root);
पूर्ण

#पूर्ण_अगर
