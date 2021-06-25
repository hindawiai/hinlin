<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MODULE_PARAMS_H
#घोषणा _LINUX_MODULE_PARAMS_H
/* (C) Copyright 2001, 2002 Rusty Russell IBM Corporation */
#समावेश <linux/init.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>

/* You can override this manually, but generally this should match the
   module name. */
#अगर_घोषित MODULE
#घोषणा MODULE_PARAM_PREFIX /* empty */
#घोषणा __MODULE_INFO_PREFIX /* empty */
#अन्यथा
#घोषणा MODULE_PARAM_PREFIX KBUILD_MODNAME "."
/* We cannot use MODULE_PARAM_PREFIX because some modules override it. */
#घोषणा __MODULE_INFO_PREFIX KBUILD_MODNAME "."
#पूर्ण_अगर

/* Chosen so that काष्ठाs with an अचिन्हित दीर्घ line up. */
#घोषणा MAX_PARAM_PREFIX_LEN (64 - माप(अचिन्हित दीर्घ))

#घोषणा __MODULE_INFO(tag, name, info)					  \
	अटल स्थिर अक्षर __UNIQUE_ID(name)[]				  \
		__used __section(".modinfo") __aligned(1)		  \
		= __MODULE_INFO_PREFIX __stringअगरy(tag) "=" info

#घोषणा __MODULE_PARM_TYPE(name, _type)					  \
	__MODULE_INFO(parmtype, name##type, #name ":" _type)

/* One क्रम each parameter, describing how to use it.  Some files करो
   multiple of these per line, so can't just use MODULE_INFO. */
#घोषणा MODULE_PARM_DESC(_parm, desc) \
	__MODULE_INFO(parm, _parm, #_parm ":" desc)

काष्ठा kernel_param;

/*
 * Flags available क्रम kernel_param_ops
 *
 * NOARG - the parameter allows क्रम no argument (foo instead of foo=1)
 */
क्रमागत अणु
	KERNEL_PARAM_OPS_FL_NOARG = (1 << 0)
पूर्ण;

काष्ठा kernel_param_ops अणु
	/* How the ops should behave */
	अचिन्हित पूर्णांक flags;
	/* Returns 0, or -त्रुटि_सं.  arg is in kp->arg. */
	पूर्णांक (*set)(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
	/* Returns length written or -त्रुटि_सं.  Buffer is 4k (ie. be लघु!) */
	पूर्णांक (*get)(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
	/* Optional function to मुक्त kp->arg when module unloaded. */
	व्योम (*मुक्त)(व्योम *arg);
पूर्ण;

/*
 * Flags available क्रम kernel_param
 *
 * UNSAFE - the parameter is dangerous and setting it will taपूर्णांक the kernel
 * HWPARAM - Hardware param not permitted in lockकरोwn mode
 */
क्रमागत अणु
	KERNEL_PARAM_FL_UNSAFE	= (1 << 0),
	KERNEL_PARAM_FL_HWPARAM	= (1 << 1),
पूर्ण;

काष्ठा kernel_param अणु
	स्थिर अक्षर *name;
	काष्ठा module *mod;
	स्थिर काष्ठा kernel_param_ops *ops;
	स्थिर u16 perm;
	s8 level;
	u8 flags;
	जोड़ अणु
		व्योम *arg;
		स्थिर काष्ठा kparam_string *str;
		स्थिर काष्ठा kparam_array *arr;
	पूर्ण;
पूर्ण;

बाह्य स्थिर काष्ठा kernel_param __start___param[], __stop___param[];

/* Special one क्रम strings we want to copy पूर्णांकo */
काष्ठा kparam_string अणु
	अचिन्हित पूर्णांक maxlen;
	अक्षर *string;
पूर्ण;

/* Special one क्रम arrays */
काष्ठा kparam_array
अणु
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक elemsize;
	अचिन्हित पूर्णांक *num;
	स्थिर काष्ठा kernel_param_ops *ops;
	व्योम *elem;
पूर्ण;

/**
 * module_param - typesafe helper क्रम a module/cmdline parameter
 * @name: the variable to alter, and exposed parameter name.
 * @type: the type of the parameter
 * @perm: visibility in sysfs.
 *
 * @name becomes the module parameter, or (prefixed by KBUILD_MODNAME and a
 * ".") the kernel commandline parameter.  Note that - is changed to _, so
 * the user can use "foo-bar=1" even क्रम variable "foo_bar".
 *
 * @perm is 0 अगर the variable is not to appear in sysfs, or 0444
 * क्रम world-पढ़ोable, 0644 क्रम root-writable, etc.  Note that अगर it
 * is writable, you may need to use kernel_param_lock() around
 * accesses (esp. अक्षरp, which can be kमुक्तd when it changes).
 *
 * The @type is simply pasted to refer to a param_ops_##type and a
 * param_check_##type: क्रम convenience many standard types are provided but
 * you can create your own by defining those variables.
 *
 * Standard types are:
 *	byte, hexपूर्णांक, लघु, uलघु, पूर्णांक, uपूर्णांक, दीर्घ, uदीर्घ
 *	अक्षरp: a अक्षरacter poपूर्णांकer
 *	bool: a bool, values 0/1, y/n, Y/N.
 *	invbool: the above, only sense-reversed (N = true).
 */
#घोषणा module_param(name, type, perm)				\
	module_param_named(name, name, type, perm)

/**
 * module_param_unsafe - same as module_param but taपूर्णांकs kernel
 * @name: the variable to alter, and exposed parameter name.
 * @type: the type of the parameter
 * @perm: visibility in sysfs.
 */
#घोषणा module_param_unsafe(name, type, perm)			\
	module_param_named_unsafe(name, name, type, perm)

/**
 * module_param_named - typesafe helper क्रम a नामd module/cmdline parameter
 * @name: a valid C identअगरier which is the parameter name.
 * @value: the actual lvalue to alter.
 * @type: the type of the parameter
 * @perm: visibility in sysfs.
 *
 * Usually it's a good idea to have variable names and user-exposed names the
 * same, but that's harder अगर the variable must be non-अटल or is inside a
 * काष्ठाure.  This allows exposure under a dअगरferent name.
 */
#घोषणा module_param_named(name, value, type, perm)			   \
	param_check_##type(name, &(value));				   \
	module_param_cb(name, &param_ops_##type, &value, perm);		   \
	__MODULE_PARM_TYPE(name, #type)

/**
 * module_param_named_unsafe - same as module_param_named but taपूर्णांकs kernel
 * @name: a valid C identअगरier which is the parameter name.
 * @value: the actual lvalue to alter.
 * @type: the type of the parameter
 * @perm: visibility in sysfs.
 */
#घोषणा module_param_named_unsafe(name, value, type, perm)		\
	param_check_##type(name, &(value));				\
	module_param_cb_unsafe(name, &param_ops_##type, &value, perm);	\
	__MODULE_PARM_TYPE(name, #type)

/**
 * module_param_cb - general callback क्रम a module/cmdline parameter
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा module_param_cb(name, ops, arg, perm)				      \
	__module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, -1, 0)

#घोषणा module_param_cb_unsafe(name, ops, arg, perm)			      \
	__module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, -1,    \
			    KERNEL_PARAM_FL_UNSAFE)

#घोषणा __level_param_cb(name, ops, arg, perm, level)			\
	__module_param_call(MODULE_PARAM_PREFIX, name, ops, arg, perm, level, 0)
/**
 * core_param_cb - general callback क्रम a module/cmdline parameter
 *                 to be evaluated beक्रमe core initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा core_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 1)

/**
 * postcore_param_cb - general callback क्रम a module/cmdline parameter
 *                     to be evaluated beक्रमe postcore initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा postcore_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 2)

/**
 * arch_param_cb - general callback क्रम a module/cmdline parameter
 *                 to be evaluated beक्रमe arch initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा arch_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 3)

/**
 * subsys_param_cb - general callback क्रम a module/cmdline parameter
 *                   to be evaluated beक्रमe subsys initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा subsys_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 4)

/**
 * fs_param_cb - general callback क्रम a module/cmdline parameter
 *               to be evaluated beक्रमe fs initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा fs_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 5)

/**
 * device_param_cb - general callback क्रम a module/cmdline parameter
 *                   to be evaluated beक्रमe device initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा device_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 6)

/**
 * late_param_cb - general callback क्रम a module/cmdline parameter
 *                 to be evaluated beक्रमe late initcall level
 * @name: a valid C identअगरier which is the parameter name.
 * @ops: the set & get operations क्रम this parameter.
 * @arg: args क्रम @ops
 * @perm: visibility in sysfs.
 *
 * The ops can have शून्य set or get functions.
 */
#घोषणा late_param_cb(name, ops, arg, perm)		\
	__level_param_cb(name, ops, arg, perm, 7)

/* On alpha, ia64 and ppc64 relocations to global data cannot go पूर्णांकo
   पढ़ो-only sections (which is part of respective UNIX ABI on these
   platक्रमms). So 'const' makes no sense and even causes compile failures
   with some compilers. */
#अगर defined(CONFIG_ALPHA) || defined(CONFIG_IA64) || defined(CONFIG_PPC64)
#घोषणा __moduleparam_स्थिर
#अन्यथा
#घोषणा __moduleparam_स्थिर स्थिर
#पूर्ण_अगर

/* This is the fundamental function क्रम रेजिस्टरing boot/module
   parameters. */
#घोषणा __module_param_call(prefix, name, ops, arg, perm, level, flags)	\
	/* Default value instead of permissions? */			\
	अटल स्थिर अक्षर __param_str_##name[] = prefix #name;		\
	अटल काष्ठा kernel_param __moduleparam_स्थिर __param_##name	\
	__used __section("__param")					\
	__aligned(__alignof__(काष्ठा kernel_param))			\
	= अणु __param_str_##name, THIS_MODULE, ops,			\
	    VERIFY_OCTAL_PERMISSIONS(perm), level, flags, अणु arg पूर्ण पूर्ण

/* Obsolete - use module_param_cb() */
#घोषणा module_param_call(name, _set, _get, arg, perm)			\
	अटल स्थिर काष्ठा kernel_param_ops __param_ops_##name =	\
		अणु .flags = 0, .set = _set, .get = _get पूर्ण;		\
	__module_param_call(MODULE_PARAM_PREFIX,			\
			    name, &__param_ops_##name, arg, perm, -1, 0)

#अगर_घोषित CONFIG_SYSFS
बाह्य व्योम kernel_param_lock(काष्ठा module *mod);
बाह्य व्योम kernel_param_unlock(काष्ठा module *mod);
#अन्यथा
अटल अंतरभूत व्योम kernel_param_lock(काष्ठा module *mod)
अणु
पूर्ण
अटल अंतरभूत व्योम kernel_param_unlock(काष्ठा module *mod)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित MODULE
/**
 * core_param - define a historical core kernel parameter.
 * @name: the name of the cmdline and sysfs parameter (often the same as var)
 * @var: the variable
 * @type: the type of the parameter
 * @perm: visibility in sysfs
 *
 * core_param is just like module_param(), but cannot be modular and
 * करोesn't add a prefix (such as "printk.").  This is क्रम compatibility
 * with __setup(), and it makes sense as truly core parameters aren't
 * tied to the particular file they're in.
 */
#घोषणा core_param(name, var, type, perm)				\
	param_check_##type(name, &(var));				\
	__module_param_call("", name, &param_ops_##type, &var, perm, -1, 0)

/**
 * core_param_unsafe - same as core_param but taपूर्णांकs kernel
 * @name: the name of the cmdline and sysfs parameter (often the same as var)
 * @var: the variable
 * @type: the type of the parameter
 * @perm: visibility in sysfs
 */
#घोषणा core_param_unsafe(name, var, type, perm)		\
	param_check_##type(name, &(var));				\
	__module_param_call("", name, &param_ops_##type, &var, perm,	\
			    -1, KERNEL_PARAM_FL_UNSAFE)

#पूर्ण_अगर /* !MODULE */

/**
 * module_param_string - a अक्षर array parameter
 * @name: the name of the parameter
 * @string: the string variable
 * @len: the maximum length of the string, incl. terminator
 * @perm: visibility in sysfs.
 *
 * This actually copies the string when it's set (unlike type अक्षरp).
 * @len is usually just माप(string).
 */
#घोषणा module_param_string(name, string, len, perm)			\
	अटल स्थिर काष्ठा kparam_string __param_string_##name		\
		= अणु len, string पूर्ण;					\
	__module_param_call(MODULE_PARAM_PREFIX, name,			\
			    &param_ops_string,				\
			    .str = &__param_string_##name, perm, -1, 0);\
	__MODULE_PARM_TYPE(name, "string")

/**
 * parameq - checks अगर two parameter names match
 * @name1: parameter name 1
 * @name2: parameter name 2
 *
 * Returns true अगर the two parameter names are equal.
 * Dashes (-) are considered equal to underscores (_).
 */
बाह्य bool parameq(स्थिर अक्षर *name1, स्थिर अक्षर *name2);

/**
 * parameqn - checks अगर two parameter names match
 * @name1: parameter name 1
 * @name2: parameter name 2
 * @n: the length to compare
 *
 * Similar to parameq(), except it compares @n अक्षरacters.
 */
बाह्य bool parameqn(स्थिर अक्षर *name1, स्थिर अक्षर *name2, माप_प्रकार n);

/* Called on module insert or kernel boot */
बाह्य अक्षर *parse_args(स्थिर अक्षर *name,
		      अक्षर *args,
		      स्थिर काष्ठा kernel_param *params,
		      अचिन्हित num,
		      s16 level_min,
		      s16 level_max,
		      व्योम *arg,
		      पूर्णांक (*unknown)(अक्षर *param, अक्षर *val,
				     स्थिर अक्षर *करोing, व्योम *arg));

/* Called by module हटाओ. */
#अगर_घोषित CONFIG_SYSFS
बाह्य व्योम destroy_params(स्थिर काष्ठा kernel_param *params, अचिन्हित num);
#अन्यथा
अटल अंतरभूत व्योम destroy_params(स्थिर काष्ठा kernel_param *params,
				  अचिन्हित num)
अणु
पूर्ण
#पूर्ण_अगर /* !CONFIG_SYSFS */

/* All the helper functions */
/* The macros to करो compile-समय type checking stolen from Jakub
   Jelinek, who IIRC came up with this idea क्रम the 2.4 module init code. */
#घोषणा __param_check(name, p, type) \
	अटल अंतरभूत type __always_unused *__check_##name(व्योम) अणु वापस(p); पूर्ण

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_byte;
बाह्य पूर्णांक param_set_byte(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_byte(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_byte(name, p) __param_check(name, p, अचिन्हित अक्षर)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_लघु;
बाह्य पूर्णांक param_set_लघु(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_लघु(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_लघु(name, p) __param_check(name, p, लघु)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_uलघु;
बाह्य पूर्णांक param_set_uलघु(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_uलघु(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_uलघु(name, p) __param_check(name, p, अचिन्हित लघु)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_पूर्णांक;
बाह्य पूर्णांक param_set_पूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_पूर्णांक(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_पूर्णांक(name, p) __param_check(name, p, पूर्णांक)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_uपूर्णांक;
बाह्य पूर्णांक param_set_uपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_uपूर्णांक(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_uपूर्णांक(name, p) __param_check(name, p, अचिन्हित पूर्णांक)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_दीर्घ;
बाह्य पूर्णांक param_set_दीर्घ(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_दीर्घ(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_दीर्घ(name, p) __param_check(name, p, दीर्घ)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_uदीर्घ;
बाह्य पूर्णांक param_set_uदीर्घ(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_uदीर्घ(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_uदीर्घ(name, p) __param_check(name, p, अचिन्हित दीर्घ)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_ulदीर्घ;
बाह्य पूर्णांक param_set_ulदीर्घ(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_ulदीर्घ(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_ulदीर्घ(name, p) __param_check(name, p, अचिन्हित दीर्घ दीर्घ)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_hexपूर्णांक;
बाह्य पूर्णांक param_set_hexपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_hexपूर्णांक(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_hexपूर्णांक(name, p) param_check_uपूर्णांक(name, p)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_अक्षरp;
बाह्य पूर्णांक param_set_अक्षरp(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_अक्षरp(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
बाह्य व्योम param_मुक्त_अक्षरp(व्योम *arg);
#घोषणा param_check_अक्षरp(name, p) __param_check(name, p, अक्षर *)

/* We used to allow पूर्णांक as well as bool.  We're taking that away! */
बाह्य स्थिर काष्ठा kernel_param_ops param_ops_bool;
बाह्य पूर्णांक param_set_bool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_bool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_bool(name, p) __param_check(name, p, bool)

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_bool_enable_only;
बाह्य पूर्णांक param_set_bool_enable_only(स्थिर अक्षर *val,
				      स्थिर काष्ठा kernel_param *kp);
/* getter is the same as क्रम the regular bool */
#घोषणा param_check_bool_enable_only param_check_bool

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_invbool;
बाह्य पूर्णांक param_set_invbool(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
बाह्य पूर्णांक param_get_invbool(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_check_invbool(name, p) __param_check(name, p, bool)

/* An पूर्णांक, which can only be set like a bool (though it shows as an पूर्णांक). */
बाह्य स्थिर काष्ठा kernel_param_ops param_ops_bपूर्णांक;
बाह्य पूर्णांक param_set_bपूर्णांक(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp);
#घोषणा param_get_bपूर्णांक param_get_पूर्णांक
#घोषणा param_check_bपूर्णांक param_check_पूर्णांक

/**
 * module_param_array - a parameter which is an array of some type
 * @name: the name of the array variable
 * @type: the type, as per module_param()
 * @nump: optional poपूर्णांकer filled in with the number written
 * @perm: visibility in sysfs
 *
 * Input and output are as comma-separated values.  Commas inside values
 * करोn't work properly (eg. an array of अक्षरp).
 *
 * ARRAY_SIZE(@name) is used to determine the number of elements in the
 * array, so the definition must be visible.
 */
#घोषणा module_param_array(name, type, nump, perm)		\
	module_param_array_named(name, name, type, nump, perm)

/**
 * module_param_array_named - नामd parameter which is an array of some type
 * @name: a valid C identअगरier which is the parameter name
 * @array: the name of the array variable
 * @type: the type, as per module_param()
 * @nump: optional poपूर्णांकer filled in with the number written
 * @perm: visibility in sysfs
 *
 * This exposes a dअगरferent name than the actual variable name.  See
 * module_param_named() क्रम why this might be necessary.
 */
#घोषणा module_param_array_named(name, array, type, nump, perm)		\
	param_check_##type(name, &(array)[0]);				\
	अटल स्थिर काष्ठा kparam_array __param_arr_##name		\
	= अणु .max = ARRAY_SIZE(array), .num = nump,                      \
	    .ops = &param_ops_##type,					\
	    .elemsize = माप(array[0]), .elem = array पूर्ण;		\
	__module_param_call(MODULE_PARAM_PREFIX, name,			\
			    &param_array_ops,				\
			    .arr = &__param_arr_##name,			\
			    perm, -1, 0);				\
	__MODULE_PARM_TYPE(name, "array of " #type)

क्रमागत hwparam_type अणु
	hwparam_ioport,		/* Module parameter configures an I/O port */
	hwparam_iomem,		/* Module parameter configures an I/O mem address */
	hwparam_ioport_or_iomem, /* Module parameter could be either, depending on other option */
	hwparam_irq,		/* Module parameter configures an IRQ */
	hwparam_dma,		/* Module parameter configures a DMA channel */
	hwparam_dma_addr,	/* Module parameter configures a DMA buffer address */
	hwparam_other,		/* Module parameter configures some other value */
पूर्ण;

/**
 * module_param_hw_named - A parameter representing a hw parameters
 * @name: a valid C identअगरier which is the parameter name.
 * @value: the actual lvalue to alter.
 * @type: the type of the parameter
 * @hwtype: what the value represents (क्रमागत hwparam_type)
 * @perm: visibility in sysfs.
 *
 * Usually it's a good idea to have variable names and user-exposed names the
 * same, but that's harder अगर the variable must be non-अटल or is inside a
 * काष्ठाure.  This allows exposure under a dअगरferent name.
 */
#घोषणा module_param_hw_named(name, value, type, hwtype, perm)		\
	param_check_##type(name, &(value));				\
	__module_param_call(MODULE_PARAM_PREFIX, name,			\
			    &param_ops_##type, &value,			\
			    perm, -1,					\
			    KERNEL_PARAM_FL_HWPARAM | (hwparam_##hwtype & 0));	\
	__MODULE_PARM_TYPE(name, #type)

#घोषणा module_param_hw(name, type, hwtype, perm)		\
	module_param_hw_named(name, name, type, hwtype, perm)

/**
 * module_param_hw_array - A parameter representing an array of hw parameters
 * @name: the name of the array variable
 * @type: the type, as per module_param()
 * @hwtype: what the value represents (क्रमागत hwparam_type)
 * @nump: optional poपूर्णांकer filled in with the number written
 * @perm: visibility in sysfs
 *
 * Input and output are as comma-separated values.  Commas inside values
 * करोn't work properly (eg. an array of अक्षरp).
 *
 * ARRAY_SIZE(@name) is used to determine the number of elements in the
 * array, so the definition must be visible.
 */
#घोषणा module_param_hw_array(name, type, hwtype, nump, perm)		\
	param_check_##type(name, &(name)[0]);				\
	अटल स्थिर काष्ठा kparam_array __param_arr_##name		\
	= अणु .max = ARRAY_SIZE(name), .num = nump,			\
	    .ops = &param_ops_##type,					\
	    .elemsize = माप(name[0]), .elem = name पूर्ण;		\
	__module_param_call(MODULE_PARAM_PREFIX, name,			\
			    &param_array_ops,				\
			    .arr = &__param_arr_##name,			\
			    perm, -1,					\
			    KERNEL_PARAM_FL_HWPARAM | (hwparam_##hwtype & 0));	\
	__MODULE_PARM_TYPE(name, "array of " #type)


बाह्य स्थिर काष्ठा kernel_param_ops param_array_ops;

बाह्य स्थिर काष्ठा kernel_param_ops param_ops_string;
बाह्य पूर्णांक param_set_copystring(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *);
बाह्य पूर्णांक param_get_string(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp);

/* क्रम exporting parameters in /sys/module/.../parameters */

काष्ठा module;

#अगर defined(CONFIG_SYSFS) && defined(CONFIG_MODULES)
बाह्य पूर्णांक module_param_sysfs_setup(काष्ठा module *mod,
				    स्थिर काष्ठा kernel_param *kparam,
				    अचिन्हित पूर्णांक num_params);

बाह्य व्योम module_param_sysfs_हटाओ(काष्ठा module *mod);
#अन्यथा
अटल अंतरभूत पूर्णांक module_param_sysfs_setup(काष्ठा module *mod,
			     स्थिर काष्ठा kernel_param *kparam,
			     अचिन्हित पूर्णांक num_params)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम module_param_sysfs_हटाओ(काष्ठा module *mod)
अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_MODULE_PARAMS_H */
