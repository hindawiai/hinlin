<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश <linux/kernel.h>

#समावेश "i915_debugfs_params.h"
#समावेश "i915_drv.h"
#समावेश "i915_params.h"

/* पूर्णांक param */
अटल पूर्णांक i915_param_पूर्णांक_show(काष्ठा seq_file *m, व्योम *data)
अणु
	पूर्णांक *value = m->निजी;

	seq_म_लिखो(m, "%d\n", *value);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_param_पूर्णांक_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_param_पूर्णांक_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार i915_param_पूर्णांक_ग_लिखो(काष्ठा file *file,
				    स्थिर अक्षर __user *ubuf, माप_प्रकार len,
				    loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	पूर्णांक *value = m->निजी;
	पूर्णांक ret;

	ret = kstrtoपूर्णांक_from_user(ubuf, len, 0, value);
	अगर (ret) अणु
		/* support boolean values too */
		bool b;

		ret = kstrtobool_from_user(ubuf, len, &b);
		अगर (!ret)
			*value = b;
	पूर्ण

	वापस ret ?: len;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_param_पूर्णांक_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_पूर्णांक_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = i915_param_पूर्णांक_ग_लिखो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_param_पूर्णांक_fops_ro = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_पूर्णांक_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

/* अचिन्हित पूर्णांक param */
अटल पूर्णांक i915_param_uपूर्णांक_show(काष्ठा seq_file *m, व्योम *data)
अणु
	अचिन्हित पूर्णांक *value = m->निजी;

	seq_म_लिखो(m, "%u\n", *value);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_param_uपूर्णांक_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_param_uपूर्णांक_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार i915_param_uपूर्णांक_ग_लिखो(काष्ठा file *file,
				     स्थिर अक्षर __user *ubuf, माप_प्रकार len,
				     loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	अचिन्हित पूर्णांक *value = m->निजी;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक_from_user(ubuf, len, 0, value);
	अगर (ret) अणु
		/* support boolean values too */
		bool b;

		ret = kstrtobool_from_user(ubuf, len, &b);
		अगर (!ret)
			*value = b;
	पूर्ण

	वापस ret ?: len;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_param_uपूर्णांक_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_uपूर्णांक_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = i915_param_uपूर्णांक_ग_लिखो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_param_uपूर्णांक_fops_ro = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_uपूर्णांक_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

/* अक्षर * param */
अटल पूर्णांक i915_param_अक्षरp_show(काष्ठा seq_file *m, व्योम *data)
अणु
	स्थिर अक्षर **s = m->निजी;

	seq_म_लिखो(m, "%s\n", *s);

	वापस 0;
पूर्ण

अटल पूर्णांक i915_param_अक्षरp_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, i915_param_अक्षरp_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार i915_param_अक्षरp_ग_लिखो(काष्ठा file *file,
				      स्थिर अक्षर __user *ubuf, माप_प्रकार len,
				      loff_t *offp)
अणु
	काष्ठा seq_file *m = file->निजी_data;
	अक्षर **s = m->निजी;
	अक्षर *new, *old;

	old = *s;
	new = strndup_user(ubuf, PAGE_SIZE);
	अगर (IS_ERR(new)) अणु
		len = PTR_ERR(new);
		जाओ out;
	पूर्ण

	*s = new;

	kमुक्त(old);
out:
	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations i915_param_अक्षरp_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_अक्षरp_खोलो,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = i915_param_अक्षरp_ग_लिखो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

अटल स्थिर काष्ठा file_operations i915_param_अक्षरp_fops_ro = अणु
	.owner = THIS_MODULE,
	.खोलो = i915_param_अक्षरp_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = शेष_llseek,
	.release = single_release,
पूर्ण;

#घोषणा RO(mode) (((mode) & 0222) == 0)

अटल काष्ठा dentry *
i915_debugfs_create_पूर्णांक(स्थिर अक्षर *name, umode_t mode,
			काष्ठा dentry *parent, पूर्णांक *value)
अणु
	वापस debugfs_create_file_unsafe(name, mode, parent, value,
					  RO(mode) ? &i915_param_पूर्णांक_fops_ro :
					  &i915_param_पूर्णांक_fops);
पूर्ण

अटल काष्ठा dentry *
i915_debugfs_create_uपूर्णांक(स्थिर अक्षर *name, umode_t mode,
			 काष्ठा dentry *parent, अचिन्हित पूर्णांक *value)
अणु
	वापस debugfs_create_file_unsafe(name, mode, parent, value,
					  RO(mode) ? &i915_param_uपूर्णांक_fops_ro :
					  &i915_param_uपूर्णांक_fops);
पूर्ण

अटल काष्ठा dentry *
i915_debugfs_create_अक्षरp(स्थिर अक्षर *name, umode_t mode,
			  काष्ठा dentry *parent, अक्षर **value)
अणु
	वापस debugfs_create_file(name, mode, parent, value,
				   RO(mode) ? &i915_param_अक्षरp_fops_ro :
				   &i915_param_अक्षरp_fops);
पूर्ण

अटल __always_अंतरभूत व्योम
_i915_param_create_file(काष्ठा dentry *parent, स्थिर अक्षर *name,
			स्थिर अक्षर *type, पूर्णांक mode, व्योम *value)
अणु
	अगर (!mode)
		वापस;

	अगर (!__builtin_म_भेद(type, "bool"))
		debugfs_create_bool(name, mode, parent, value);
	अन्यथा अगर (!__builtin_म_भेद(type, "int"))
		i915_debugfs_create_पूर्णांक(name, mode, parent, value);
	अन्यथा अगर (!__builtin_म_भेद(type, "unsigned int"))
		i915_debugfs_create_uपूर्णांक(name, mode, parent, value);
	अन्यथा अगर (!__builtin_म_भेद(type, "unsigned long"))
		debugfs_create_uदीर्घ(name, mode, parent, value);
	अन्यथा अगर (!__builtin_म_भेद(type, "char *"))
		i915_debugfs_create_अक्षरp(name, mode, parent, value);
	अन्यथा
		WARN(1, "no debugfs fops defined for param type %s (i915.%s)\n",
		     type, name);
पूर्ण

/* add a subdirectory with files क्रम each i915 param */
काष्ठा dentry *i915_debugfs_params(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_minor *minor = i915->drm.primary;
	काष्ठा i915_params *params = &i915->params;
	काष्ठा dentry *dir;

	dir = debugfs_create_dir("i915_params", minor->debugfs_root);
	अगर (IS_ERR(dir))
		वापस dir;

	/*
	 * Note: We could create files क्रम params needing special handling
	 * here. Set mode in params to 0 to skip the generic create file, or
	 * just let the generic create file fail silently with -EEXIST.
	 */

#घोषणा REGISTER(T, x, unused, mode, ...) _i915_param_create_file(dir, #x, #T, mode, &params->x);
	I915_PARAMS_FOR_EACH(REGISTER);
#अघोषित REGISTER

	वापस dir;
पूर्ण
