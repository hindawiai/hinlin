<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Helpers क्रम initial module or kernel cmdline parsing
   Copyright (C) 2001 Rusty Russell.

*/
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/security.h>

#अगर_घोषित CONFIG_SYSFS
/* Protects all built-in parameters, modules use their own param_lock */
अटल DEFINE_MUTEX(param_lock);

/* Use the module's mutex, or अगर built-in use the built-in mutex */
#अगर_घोषित CONFIG_MODULES
#घोषणा KPARAM_MUTEX(mod)	((mod) ? &(mod)->param_lock : &param_lock)
#अन्यथा
#घोषणा KPARAM_MUTEX(mod)	(&param_lock)
#पूर्ण_अगर

अटल अंतरभूत व्योम check_kparam_locked(काष्ठा module *mod)
अणु
	BUG_ON(!mutex_is_locked(KPARAM_MUTEX(mod)));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम check_kparam_locked(काष्ठा module *mod)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_SYSFS */

/* This just allows us to keep track of which parameters are kदो_स्मृतिed. */
काष्ठा kदो_स्मृतिed_param अणु
	काष्ठा list_head list;
	अक्षर val[];
पूर्ण;
अटल LIST_HEAD(kदो_स्मृतिed_params);
अटल DEFINE_SPINLOCK(kदो_स्मृतिed_params_lock);

अटल व्योम *kदो_स्मृति_parameter(अचिन्हित पूर्णांक size)
अणु
	काष्ठा kदो_स्मृतिed_param *p;

	p = kदो_स्मृति(माप(*p) + size, GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	spin_lock(&kदो_स्मृतिed_params_lock);
	list_add(&p->list, &kदो_स्मृतिed_params);
	spin_unlock(&kदो_स्मृतिed_params_lock);

	वापस p->val;
पूर्ण

/* Does nothing अगर parameter wasn't kदो_स्मृतिed above. */
अटल व्योम maybe_kमुक्त_parameter(व्योम *param)
अणु
	काष्ठा kदो_स्मृतिed_param *p;

	spin_lock(&kदो_स्मृतिed_params_lock);
	list_क्रम_each_entry(p, &kदो_स्मृतिed_params, list) अणु
		अगर (p->val == param) अणु
			list_del(&p->list);
			kमुक्त(p);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock(&kदो_स्मृतिed_params_lock);
पूर्ण

अटल अक्षर dash2underscore(अक्षर c)
अणु
	अगर (c == '-')
		वापस '_';
	वापस c;
पूर्ण

bool parameqn(स्थिर अक्षर *a, स्थिर अक्षर *b, माप_प्रकार n)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (dash2underscore(a[i]) != dash2underscore(b[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

bool parameq(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	वापस parameqn(a, b, म_माप(a)+1);
पूर्ण

अटल bool param_check_unsafe(स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (kp->flags & KERNEL_PARAM_FL_HWPARAM &&
	    security_locked_करोwn(LOCKDOWN_MODULE_PARAMETERS))
		वापस false;

	अगर (kp->flags & KERNEL_PARAM_FL_UNSAFE) अणु
		pr_notice("Setting dangerous option %s - tainting kernel\n",
			  kp->name);
		add_taपूर्णांक(TAINT_USER, LOCKDEP_STILL_OK);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक parse_one(अक्षर *param,
		     अक्षर *val,
		     स्थिर अक्षर *करोing,
		     स्थिर काष्ठा kernel_param *params,
		     अचिन्हित num_params,
		     s16 min_level,
		     s16 max_level,
		     व्योम *arg,
		     पूर्णांक (*handle_unknown)(अक्षर *param, अक्षर *val,
				     स्थिर अक्षर *करोing, व्योम *arg))
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	/* Find parameter */
	क्रम (i = 0; i < num_params; i++) अणु
		अगर (parameq(param, params[i].name)) अणु
			अगर (params[i].level < min_level
			    || params[i].level > max_level)
				वापस 0;
			/* No one handled शून्य, so करो it here. */
			अगर (!val &&
			    !(params[i].ops->flags & KERNEL_PARAM_OPS_FL_NOARG))
				वापस -EINVAL;
			pr_debug("handling %s with %p\n", param,
				params[i].ops->set);
			kernel_param_lock(params[i].mod);
			अगर (param_check_unsafe(&params[i]))
				err = params[i].ops->set(val, &params[i]);
			अन्यथा
				err = -EPERM;
			kernel_param_unlock(params[i].mod);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (handle_unknown) अणु
		pr_debug("doing %s: %s='%s'\n", करोing, param, val);
		वापस handle_unknown(param, val, करोing, arg);
	पूर्ण

	pr_debug("Unknown argument '%s'\n", param);
	वापस -ENOENT;
पूर्ण

/* Args looks like "foo=bar,bar2 baz=fuz wiz". */
अक्षर *parse_args(स्थिर अक्षर *करोing,
		 अक्षर *args,
		 स्थिर काष्ठा kernel_param *params,
		 अचिन्हित num,
		 s16 min_level,
		 s16 max_level,
		 व्योम *arg,
		 पूर्णांक (*unknown)(अक्षर *param, अक्षर *val,
				स्थिर अक्षर *करोing, व्योम *arg))
अणु
	अक्षर *param, *val, *err = शून्य;

	/* Chew leading spaces */
	args = skip_spaces(args);

	अगर (*args)
		pr_debug("doing %s, parsing ARGS: '%s'\n", करोing, args);

	जबतक (*args) अणु
		पूर्णांक ret;
		पूर्णांक irq_was_disabled;

		args = next_arg(args, &param, &val);
		/* Stop at -- */
		अगर (!val && म_भेद(param, "--") == 0)
			वापस err ?: args;
		irq_was_disabled = irqs_disabled();
		ret = parse_one(param, val, करोing, params, num,
				min_level, max_level, arg, unknown);
		अगर (irq_was_disabled && !irqs_disabled())
			pr_warn("%s: option '%s' enabled irq's!\n",
				करोing, param);

		चयन (ret) अणु
		हाल 0:
			जारी;
		हाल -ENOENT:
			pr_err("%s: Unknown parameter `%s'\n", करोing, param);
			अवरोध;
		हाल -ENOSPC:
			pr_err("%s: `%s' too large for parameter `%s'\n",
			       करोing, val ?: "", param);
			अवरोध;
		शेष:
			pr_err("%s: `%s' invalid for parameter `%s'\n",
			       करोing, val ?: "", param);
			अवरोध;
		पूर्ण

		err = ERR_PTR(ret);
	पूर्ण

	वापस err;
पूर्ण

/* Lazy bastard, eh? */
#घोषणा STANDARD_PARAM_DEF(name, type, क्रमmat, म_से_दीर्घfn)      		\
	पूर्णांक param_set_##name(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp) \
	अणु								\
		वापस म_से_दीर्घfn(val, 0, (type *)kp->arg);		\
	पूर्ण								\
	पूर्णांक param_get_##name(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp) \
	अणु								\
		वापस scnम_लिखो(buffer, PAGE_SIZE, क्रमmat "\n",	\
				*((type *)kp->arg));			\
	पूर्ण								\
	स्थिर काष्ठा kernel_param_ops param_ops_##name = अणु			\
		.set = param_set_##name,				\
		.get = param_get_##name,				\
	पूर्ण;								\
	EXPORT_SYMBOL(param_set_##name);				\
	EXPORT_SYMBOL(param_get_##name);				\
	EXPORT_SYMBOL(param_ops_##name)


STANDARD_PARAM_DEF(byte,	अचिन्हित अक्षर,		"%hhu",		kstrtou8);
STANDARD_PARAM_DEF(लघु,	लघु,			"%hi",		kstrtos16);
STANDARD_PARAM_DEF(uलघु,	अचिन्हित लघु,		"%hu",		kstrtou16);
STANDARD_PARAM_DEF(पूर्णांक,		पूर्णांक,			"%i",		kstrtoपूर्णांक);
STANDARD_PARAM_DEF(uपूर्णांक,	अचिन्हित पूर्णांक,		"%u",		kstrtouपूर्णांक);
STANDARD_PARAM_DEF(दीर्घ,	दीर्घ,			"%li",		kम_से_दीर्घ);
STANDARD_PARAM_DEF(uदीर्घ,	अचिन्हित दीर्घ,		"%lu",		kम_से_अदीर्घ);
STANDARD_PARAM_DEF(ulदीर्घ,	अचिन्हित दीर्घ दीर्घ,	"%llu",		kम_से_अदीर्घl);
STANDARD_PARAM_DEF(hexपूर्णांक,	अचिन्हित पूर्णांक,		"%#08x", 	kstrtouपूर्णांक);

पूर्णांक param_set_अक्षरp(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	अगर (म_माप(val) > 1024) अणु
		pr_err("%s: string parameter too long\n", kp->name);
		वापस -ENOSPC;
	पूर्ण

	maybe_kमुक्त_parameter(*(अक्षर **)kp->arg);

	/* This is a hack.  We can't kदो_स्मृति in early boot, and we
	 * करोn't need to; this mangled commandline is preserved. */
	अगर (slab_is_available()) अणु
		*(अक्षर **)kp->arg = kदो_स्मृति_parameter(म_माप(val)+1);
		अगर (!*(अक्षर **)kp->arg)
			वापस -ENOMEM;
		म_नकल(*(अक्षर **)kp->arg, val);
	पूर्ण अन्यथा
		*(स्थिर अक्षर **)kp->arg = val;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(param_set_अक्षरp);

पूर्णांक param_get_अक्षरp(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", *((अक्षर **)kp->arg));
पूर्ण
EXPORT_SYMBOL(param_get_अक्षरp);

व्योम param_मुक्त_अक्षरp(व्योम *arg)
अणु
	maybe_kमुक्त_parameter(*((अक्षर **)arg));
पूर्ण
EXPORT_SYMBOL(param_मुक्त_अक्षरp);

स्थिर काष्ठा kernel_param_ops param_ops_अक्षरp = अणु
	.set = param_set_अक्षरp,
	.get = param_get_अक्षरp,
	.मुक्त = param_मुक्त_अक्षरp,
पूर्ण;
EXPORT_SYMBOL(param_ops_अक्षरp);

/* Actually could be a bool or an पूर्णांक, क्रम historical reasons. */
पूर्णांक param_set_bool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	/* No equals means "set"... */
	अगर (!val) val = "1";

	/* One of =[yYnN01] */
	वापस strtobool(val, kp->arg);
पूर्ण
EXPORT_SYMBOL(param_set_bool);

पूर्णांक param_get_bool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	/* Y and N chosen as being relatively non-coder मित्रly */
	वापस प्र_लिखो(buffer, "%c\n", *(bool *)kp->arg ? 'Y' : 'N');
पूर्ण
EXPORT_SYMBOL(param_get_bool);

स्थिर काष्ठा kernel_param_ops param_ops_bool = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = param_set_bool,
	.get = param_get_bool,
पूर्ण;
EXPORT_SYMBOL(param_ops_bool);

पूर्णांक param_set_bool_enable_only(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक err = 0;
	bool new_value;
	bool orig_value = *(bool *)kp->arg;
	काष्ठा kernel_param dummy_kp = *kp;

	dummy_kp.arg = &new_value;

	err = param_set_bool(val, &dummy_kp);
	अगर (err)
		वापस err;

	/* Don't let them unset it once it's set! */
	अगर (!new_value && orig_value)
		वापस -EROFS;

	अगर (new_value)
		err = param_set_bool(val, kp);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(param_set_bool_enable_only);

स्थिर काष्ठा kernel_param_ops param_ops_bool_enable_only = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = param_set_bool_enable_only,
	.get = param_get_bool,
पूर्ण;
EXPORT_SYMBOL_GPL(param_ops_bool_enable_only);

/* This one must be bool. */
पूर्णांक param_set_invbool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक ret;
	bool boolval;
	काष्ठा kernel_param dummy;

	dummy.arg = &boolval;
	ret = param_set_bool(val, &dummy);
	अगर (ret == 0)
		*(bool *)kp->arg = !boolval;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(param_set_invbool);

पूर्णांक param_get_invbool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	वापस प्र_लिखो(buffer, "%c\n", (*(bool *)kp->arg) ? 'N' : 'Y');
पूर्ण
EXPORT_SYMBOL(param_get_invbool);

स्थिर काष्ठा kernel_param_ops param_ops_invbool = अणु
	.set = param_set_invbool,
	.get = param_get_invbool,
पूर्ण;
EXPORT_SYMBOL(param_ops_invbool);

पूर्णांक param_set_bपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	/* Match bool exactly, by re-using it. */
	काष्ठा kernel_param boolkp = *kp;
	bool v;
	पूर्णांक ret;

	boolkp.arg = &v;

	ret = param_set_bool(val, &boolkp);
	अगर (ret == 0)
		*(पूर्णांक *)kp->arg = v;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(param_set_bपूर्णांक);

स्थिर काष्ठा kernel_param_ops param_ops_bपूर्णांक = अणु
	.flags = KERNEL_PARAM_OPS_FL_NOARG,
	.set = param_set_bपूर्णांक,
	.get = param_get_पूर्णांक,
पूर्ण;
EXPORT_SYMBOL(param_ops_bपूर्णांक);

/* We अवरोध the rule and mangle the string. */
अटल पूर्णांक param_array(काष्ठा module *mod,
		       स्थिर अक्षर *name,
		       स्थिर अक्षर *val,
		       अचिन्हित पूर्णांक min, अचिन्हित पूर्णांक max,
		       व्योम *elem, पूर्णांक elemsize,
		       पूर्णांक (*set)(स्थिर अक्षर *, स्थिर काष्ठा kernel_param *kp),
		       s16 level,
		       अचिन्हित पूर्णांक *num)
अणु
	पूर्णांक ret;
	काष्ठा kernel_param kp;
	अक्षर save;

	/* Get the name right क्रम errors. */
	kp.name = name;
	kp.arg = elem;
	kp.level = level;

	*num = 0;
	/* We expect a comma-separated list of values. */
	करो अणु
		पूर्णांक len;

		अगर (*num == max) अणु
			pr_err("%s: can only take %i arguments\n", name, max);
			वापस -EINVAL;
		पूर्ण
		len = म_खोज(val, ",");

		/* nul-terminate and parse */
		save = val[len];
		((अक्षर *)val)[len] = '\0';
		check_kparam_locked(mod);
		ret = set(val, &kp);

		अगर (ret != 0)
			वापस ret;
		kp.arg += elemsize;
		val += len+1;
		(*num)++;
	पूर्ण जबतक (save == ',');

	अगर (*num < min) अणु
		pr_err("%s: needs at least %i arguments\n", name, min);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक param_array_set(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर काष्ठा kparam_array *arr = kp->arr;
	अचिन्हित पूर्णांक temp_num;

	वापस param_array(kp->mod, kp->name, val, 1, arr->max, arr->elem,
			   arr->elemsize, arr->ops->set, kp->level,
			   arr->num ?: &temp_num);
पूर्ण

अटल पूर्णांक param_array_get(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक i, off, ret;
	स्थिर काष्ठा kparam_array *arr = kp->arr;
	काष्ठा kernel_param p = *kp;

	क्रम (i = off = 0; i < (arr->num ? *arr->num : arr->max); i++) अणु
		/* Replace \न with comma */
		अगर (i)
			buffer[off - 1] = ',';
		p.arg = arr->elem + arr->elemsize * i;
		check_kparam_locked(p.mod);
		ret = arr->ops->get(buffer + off, &p);
		अगर (ret < 0)
			वापस ret;
		off += ret;
	पूर्ण
	buffer[off] = '\0';
	वापस off;
पूर्ण

अटल व्योम param_array_मुक्त(व्योम *arg)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा kparam_array *arr = arg;

	अगर (arr->ops->मुक्त)
		क्रम (i = 0; i < (arr->num ? *arr->num : arr->max); i++)
			arr->ops->मुक्त(arr->elem + arr->elemsize * i);
पूर्ण

स्थिर काष्ठा kernel_param_ops param_array_ops = अणु
	.set = param_array_set,
	.get = param_array_get,
	.मुक्त = param_array_मुक्त,
पूर्ण;
EXPORT_SYMBOL(param_array_ops);

पूर्णांक param_set_copystring(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर काष्ठा kparam_string *kps = kp->str;

	अगर (म_माप(val)+1 > kps->maxlen) अणु
		pr_err("%s: string doesn't fit in %u chars.\n",
		       kp->name, kps->maxlen-1);
		वापस -ENOSPC;
	पूर्ण
	म_नकल(kps->string, val);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(param_set_copystring);

पूर्णांक param_get_string(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	स्थिर काष्ठा kparam_string *kps = kp->str;
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%s\n", kps->string);
पूर्ण
EXPORT_SYMBOL(param_get_string);

स्थिर काष्ठा kernel_param_ops param_ops_string = अणु
	.set = param_set_copystring,
	.get = param_get_string,
पूर्ण;
EXPORT_SYMBOL(param_ops_string);

/* sysfs output in /sys/modules/XYZ/parameters/ */
#घोषणा to_module_attr(n) container_of(n, काष्ठा module_attribute, attr)
#घोषणा to_module_kobject(n) container_of(n, काष्ठा module_kobject, kobj)

काष्ठा param_attribute
अणु
	काष्ठा module_attribute mattr;
	स्थिर काष्ठा kernel_param *param;
पूर्ण;

काष्ठा module_param_attrs
अणु
	अचिन्हित पूर्णांक num;
	काष्ठा attribute_group grp;
	काष्ठा param_attribute attrs[];
पूर्ण;

#अगर_घोषित CONFIG_SYSFS
#घोषणा to_param_attr(n) container_of(n, काष्ठा param_attribute, mattr)

अटल sमाप_प्रकार param_attr_show(काष्ठा module_attribute *mattr,
			       काष्ठा module_kobject *mk, अक्षर *buf)
अणु
	पूर्णांक count;
	काष्ठा param_attribute *attribute = to_param_attr(mattr);

	अगर (!attribute->param->ops->get)
		वापस -EPERM;

	kernel_param_lock(mk->mod);
	count = attribute->param->ops->get(buf, attribute->param);
	kernel_param_unlock(mk->mod);
	वापस count;
पूर्ण

/* sysfs always hands a nul-terminated string in buf.  We rely on that. */
अटल sमाप_प्रकार param_attr_store(काष्ठा module_attribute *mattr,
				काष्ठा module_kobject *mk,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
 	पूर्णांक err;
	काष्ठा param_attribute *attribute = to_param_attr(mattr);

	अगर (!attribute->param->ops->set)
		वापस -EPERM;

	kernel_param_lock(mk->mod);
	अगर (param_check_unsafe(attribute->param))
		err = attribute->param->ops->set(buf, attribute->param);
	अन्यथा
		err = -EPERM;
	kernel_param_unlock(mk->mod);
	अगर (!err)
		वापस len;
	वापस err;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MODULES
#घोषणा __modinit
#अन्यथा
#घोषणा __modinit __init
#पूर्ण_अगर

#अगर_घोषित CONFIG_SYSFS
व्योम kernel_param_lock(काष्ठा module *mod)
अणु
	mutex_lock(KPARAM_MUTEX(mod));
पूर्ण

व्योम kernel_param_unlock(काष्ठा module *mod)
अणु
	mutex_unlock(KPARAM_MUTEX(mod));
पूर्ण

EXPORT_SYMBOL(kernel_param_lock);
EXPORT_SYMBOL(kernel_param_unlock);

/*
 * add_sysfs_param - add a parameter to sysfs
 * @mk: काष्ठा module_kobject
 * @kp: the actual parameter definition to add to sysfs
 * @name: name of parameter
 *
 * Create a kobject अगर क्रम a (per-module) parameter अगर mp शून्य, and
 * create file in sysfs.  Returns an error on out of memory.  Always cleans up
 * अगर there's an error.
 */
अटल __modinit पूर्णांक add_sysfs_param(काष्ठा module_kobject *mk,
				     स्थिर काष्ठा kernel_param *kp,
				     स्थिर अक्षर *name)
अणु
	काष्ठा module_param_attrs *new_mp;
	काष्ठा attribute **new_attrs;
	अचिन्हित पूर्णांक i;

	/* We करोn't bother calling this with invisible parameters. */
	BUG_ON(!kp->perm);

	अगर (!mk->mp) अणु
		/* First allocation. */
		mk->mp = kzalloc(माप(*mk->mp), GFP_KERNEL);
		अगर (!mk->mp)
			वापस -ENOMEM;
		mk->mp->grp.name = "parameters";
		/* शून्य-terminated attribute array. */
		mk->mp->grp.attrs = kzalloc(माप(mk->mp->grp.attrs[0]),
					    GFP_KERNEL);
		/* Caller will cleanup via मुक्त_module_param_attrs */
		अगर (!mk->mp->grp.attrs)
			वापस -ENOMEM;
	पूर्ण

	/* Enlarge allocations. */
	new_mp = kपुनः_स्मृति(mk->mp,
			  माप(*mk->mp) +
			  माप(mk->mp->attrs[0]) * (mk->mp->num + 1),
			  GFP_KERNEL);
	अगर (!new_mp)
		वापस -ENOMEM;
	mk->mp = new_mp;

	/* Extra poपूर्णांकer क्रम शून्य terminator */
	new_attrs = kपुनः_स्मृति(mk->mp->grp.attrs,
			     माप(mk->mp->grp.attrs[0]) * (mk->mp->num + 2),
			     GFP_KERNEL);
	अगर (!new_attrs)
		वापस -ENOMEM;
	mk->mp->grp.attrs = new_attrs;

	/* Tack new one on the end. */
	स_रखो(&mk->mp->attrs[mk->mp->num], 0, माप(mk->mp->attrs[0]));
	sysfs_attr_init(&mk->mp->attrs[mk->mp->num].mattr.attr);
	mk->mp->attrs[mk->mp->num].param = kp;
	mk->mp->attrs[mk->mp->num].mattr.show = param_attr_show;
	/* Do not allow runसमय DAC changes to make param writable. */
	अगर ((kp->perm & (S_IWUSR | S_IWGRP | S_IWOTH)) != 0)
		mk->mp->attrs[mk->mp->num].mattr.store = param_attr_store;
	अन्यथा
		mk->mp->attrs[mk->mp->num].mattr.store = शून्य;
	mk->mp->attrs[mk->mp->num].mattr.attr.name = (अक्षर *)name;
	mk->mp->attrs[mk->mp->num].mattr.attr.mode = kp->perm;
	mk->mp->num++;

	/* Fix up all the poपूर्णांकers, since kपुनः_स्मृति can move us */
	क्रम (i = 0; i < mk->mp->num; i++)
		mk->mp->grp.attrs[i] = &mk->mp->attrs[i].mattr.attr;
	mk->mp->grp.attrs[mk->mp->num] = शून्य;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MODULES
अटल व्योम मुक्त_module_param_attrs(काष्ठा module_kobject *mk)
अणु
	अगर (mk->mp)
		kमुक्त(mk->mp->grp.attrs);
	kमुक्त(mk->mp);
	mk->mp = शून्य;
पूर्ण

/*
 * module_param_sysfs_setup - setup sysfs support क्रम one module
 * @mod: module
 * @kparam: module parameters (array)
 * @num_params: number of module parameters
 *
 * Adds sysfs entries क्रम module parameters under
 * /sys/module/[mod->name]/parameters/
 */
पूर्णांक module_param_sysfs_setup(काष्ठा module *mod,
			     स्थिर काष्ठा kernel_param *kparam,
			     अचिन्हित पूर्णांक num_params)
अणु
	पूर्णांक i, err;
	bool params = false;

	क्रम (i = 0; i < num_params; i++) अणु
		अगर (kparam[i].perm == 0)
			जारी;
		err = add_sysfs_param(&mod->mkobj, &kparam[i], kparam[i].name);
		अगर (err) अणु
			मुक्त_module_param_attrs(&mod->mkobj);
			वापस err;
		पूर्ण
		params = true;
	पूर्ण

	अगर (!params)
		वापस 0;

	/* Create the param group. */
	err = sysfs_create_group(&mod->mkobj.kobj, &mod->mkobj.mp->grp);
	अगर (err)
		मुक्त_module_param_attrs(&mod->mkobj);
	वापस err;
पूर्ण

/*
 * module_param_sysfs_हटाओ - हटाओ sysfs support क्रम one module
 * @mod: module
 *
 * Remove sysfs entries क्रम module parameters and the corresponding
 * kobject.
 */
व्योम module_param_sysfs_हटाओ(काष्ठा module *mod)
अणु
	अगर (mod->mkobj.mp) अणु
		sysfs_हटाओ_group(&mod->mkobj.kobj, &mod->mkobj.mp->grp);
		/* We are positive that no one is using any param
		 * attrs at this poपूर्णांक.  Deallocate immediately. */
		मुक्त_module_param_attrs(&mod->mkobj);
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम destroy_params(स्थिर काष्ठा kernel_param *params, अचिन्हित num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++)
		अगर (params[i].ops->मुक्त)
			params[i].ops->मुक्त(params[i].arg);
पूर्ण

अटल काष्ठा module_kobject * __init locate_module_kobject(स्थिर अक्षर *name)
अणु
	काष्ठा module_kobject *mk;
	काष्ठा kobject *kobj;
	पूर्णांक err;

	kobj = kset_find_obj(module_kset, name);
	अगर (kobj) अणु
		mk = to_module_kobject(kobj);
	पूर्ण अन्यथा अणु
		mk = kzalloc(माप(काष्ठा module_kobject), GFP_KERNEL);
		BUG_ON(!mk);

		mk->mod = THIS_MODULE;
		mk->kobj.kset = module_kset;
		err = kobject_init_and_add(&mk->kobj, &module_ktype, शून्य,
					   "%s", name);
#अगर_घोषित CONFIG_MODULES
		अगर (!err)
			err = sysfs_create_file(&mk->kobj, &module_uevent.attr);
#पूर्ण_अगर
		अगर (err) अणु
			kobject_put(&mk->kobj);
			pr_crit("Adding module '%s' to sysfs failed (%d), the system may be unstable.\n",
				name, err);
			वापस शून्य;
		पूर्ण

		/* So that we hold reference in both हालs. */
		kobject_get(&mk->kobj);
	पूर्ण

	वापस mk;
पूर्ण

अटल व्योम __init kernel_add_sysfs_param(स्थिर अक्षर *name,
					  स्थिर काष्ठा kernel_param *kparam,
					  अचिन्हित पूर्णांक name_skip)
अणु
	काष्ठा module_kobject *mk;
	पूर्णांक err;

	mk = locate_module_kobject(name);
	अगर (!mk)
		वापस;

	/* We need to हटाओ old parameters beक्रमe adding more. */
	अगर (mk->mp)
		sysfs_हटाओ_group(&mk->kobj, &mk->mp->grp);

	/* These should not fail at boot. */
	err = add_sysfs_param(mk, kparam, kparam->name + name_skip);
	BUG_ON(err);
	err = sysfs_create_group(&mk->kobj, &mk->mp->grp);
	BUG_ON(err);
	kobject_uevent(&mk->kobj, KOBJ_ADD);
	kobject_put(&mk->kobj);
पूर्ण

/*
 * param_sysfs_builtin - add sysfs parameters क्रम built-in modules
 *
 * Add module_parameters to sysfs क्रम "modules" built पूर्णांकo the kernel.
 *
 * The "module" name (KBUILD_MODNAME) is stored beक्रमe a करोt, the
 * "parameter" name is stored behind a करोt in kernel_param->name. So,
 * extract the "module" name क्रम all built-in kernel_param-eters,
 * and क्रम all who have the same, call kernel_add_sysfs_param.
 */
अटल व्योम __init param_sysfs_builtin(व्योम)
अणु
	स्थिर काष्ठा kernel_param *kp;
	अचिन्हित पूर्णांक name_len;
	अक्षर modname[MODULE_NAME_LEN];

	क्रम (kp = __start___param; kp < __stop___param; kp++) अणु
		अक्षर *करोt;

		अगर (kp->perm == 0)
			जारी;

		करोt = म_अक्षर(kp->name, '.');
		अगर (!करोt) अणु
			/* This happens क्रम core_param() */
			म_नकल(modname, "kernel");
			name_len = 0;
		पूर्ण अन्यथा अणु
			name_len = करोt - kp->name + 1;
			strlcpy(modname, kp->name, name_len);
		पूर्ण
		kernel_add_sysfs_param(modname, kp, name_len);
	पूर्ण
पूर्ण

sमाप_प्रकार __modver_version_show(काष्ठा module_attribute *mattr,
			      काष्ठा module_kobject *mk, अक्षर *buf)
अणु
	काष्ठा module_version_attribute *vattr =
		container_of(mattr, काष्ठा module_version_attribute, mattr);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", vattr->version);
पूर्ण

बाह्य स्थिर काष्ठा module_version_attribute __start___modver[];
बाह्य स्थिर काष्ठा module_version_attribute __stop___modver[];

अटल व्योम __init version_sysfs_builtin(व्योम)
अणु
	स्थिर काष्ठा module_version_attribute *vattr;
	काष्ठा module_kobject *mk;
	पूर्णांक err;

	क्रम (vattr = __start___modver; vattr < __stop___modver; vattr++) अणु
		mk = locate_module_kobject(vattr->module_name);
		अगर (mk) अणु
			err = sysfs_create_file(&mk->kobj, &vattr->mattr.attr);
			WARN_ON_ONCE(err);
			kobject_uevent(&mk->kobj, KOBJ_ADD);
			kobject_put(&mk->kobj);
		पूर्ण
	पूर्ण
पूर्ण

/* module-related sysfs stuff */

अटल sमाप_प्रकार module_attr_show(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा module_attribute *attribute;
	काष्ठा module_kobject *mk;
	पूर्णांक ret;

	attribute = to_module_attr(attr);
	mk = to_module_kobject(kobj);

	अगर (!attribute->show)
		वापस -EIO;

	ret = attribute->show(attribute, mk, buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार module_attr_store(काष्ठा kobject *kobj,
				काष्ठा attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा module_attribute *attribute;
	काष्ठा module_kobject *mk;
	पूर्णांक ret;

	attribute = to_module_attr(attr);
	mk = to_module_kobject(kobj);

	अगर (!attribute->store)
		वापस -EIO;

	ret = attribute->store(attribute, mk, buf, len);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops module_sysfs_ops = अणु
	.show = module_attr_show,
	.store = module_attr_store,
पूर्ण;

अटल पूर्णांक uevent_filter(काष्ठा kset *kset, काष्ठा kobject *kobj)
अणु
	काष्ठा kobj_type *ktype = get_ktype(kobj);

	अगर (ktype == &module_ktype)
		वापस 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा kset_uevent_ops module_uevent_ops = अणु
	.filter = uevent_filter,
पूर्ण;

काष्ठा kset *module_kset;
पूर्णांक module_sysfs_initialized;

अटल व्योम module_kobj_release(काष्ठा kobject *kobj)
अणु
	काष्ठा module_kobject *mk = to_module_kobject(kobj);
	complete(mk->kobj_completion);
पूर्ण

काष्ठा kobj_type module_ktype = अणु
	.release   =	module_kobj_release,
	.sysfs_ops =	&module_sysfs_ops,
पूर्ण;

/*
 * param_sysfs_init - wrapper क्रम built-in params support
 */
अटल पूर्णांक __init param_sysfs_init(व्योम)
अणु
	module_kset = kset_create_and_add("module", &module_uevent_ops, शून्य);
	अगर (!module_kset) अणु
		prपूर्णांकk(KERN_WARNING "%s (%d): error creating kset\n",
			__खाता__, __LINE__);
		वापस -ENOMEM;
	पूर्ण
	module_sysfs_initialized = 1;

	version_sysfs_builtin();
	param_sysfs_builtin();

	वापस 0;
पूर्ण
subsys_initcall(param_sysfs_init);

#पूर्ण_अगर /* CONFIG_SYSFS */
