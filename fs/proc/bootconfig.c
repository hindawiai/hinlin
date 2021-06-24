<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * /proc/bootconfig - Extra boot configuration
 */
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/bootconfig.h>
#समावेश <linux/slab.h>

अटल अक्षर *saved_boot_config;

अटल पूर्णांक boot_config_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	अगर (saved_boot_config)
		seq_माला_दो(m, saved_boot_config);
	वापस 0;
पूर्ण

/* Rest size of buffer */
#घोषणा rest(dst, end) ((end) > (dst) ? (end) - (dst) : 0)

/* Return the needed total length अगर @size is 0 */
अटल पूर्णांक __init copy_xbc_key_value_list(अक्षर *dst, माप_प्रकार size)
अणु
	काष्ठा xbc_node *leaf, *vnode;
	अक्षर *key, *end = dst + size;
	स्थिर अक्षर *val;
	अक्षर q;
	पूर्णांक ret = 0;

	key = kzalloc(XBC_KEYLEN_MAX, GFP_KERNEL);

	xbc_क्रम_each_key_value(leaf, val) अणु
		ret = xbc_node_compose_key(leaf, key, XBC_KEYLEN_MAX);
		अगर (ret < 0)
			अवरोध;
		ret = snम_लिखो(dst, rest(dst, end), "%s = ", key);
		अगर (ret < 0)
			अवरोध;
		dst += ret;
		vnode = xbc_node_get_child(leaf);
		अगर (vnode) अणु
			xbc_array_क्रम_each_value(vnode, val) अणु
				अगर (म_अक्षर(val, '"'))
					q = '\'';
				अन्यथा
					q = '"';
				ret = snम_लिखो(dst, rest(dst, end), "%c%s%c%s",
					q, val, q, vnode->next ? ", " : "\n");
				अगर (ret < 0)
					जाओ out;
				dst += ret;
			पूर्ण
		पूर्ण अन्यथा अणु
			ret = snम_लिखो(dst, rest(dst, end), "\"\"\n");
			अगर (ret < 0)
				अवरोध;
			dst += ret;
		पूर्ण
	पूर्ण
out:
	kमुक्त(key);

	वापस ret < 0 ? ret : dst - (end - size);
पूर्ण

अटल पूर्णांक __init proc_boot_config_init(व्योम)
अणु
	पूर्णांक len;

	len = copy_xbc_key_value_list(शून्य, 0);
	अगर (len < 0)
		वापस len;

	अगर (len > 0) अणु
		saved_boot_config = kzalloc(len + 1, GFP_KERNEL);
		अगर (!saved_boot_config)
			वापस -ENOMEM;

		len = copy_xbc_key_value_list(saved_boot_config, len + 1);
		अगर (len < 0) अणु
			kमुक्त(saved_boot_config);
			वापस len;
		पूर्ण
	पूर्ण

	proc_create_single("bootconfig", 0, शून्य, boot_config_proc_show);

	वापस 0;
पूर्ण
fs_initcall(proc_boot_config_init);
