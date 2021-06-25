<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _DYNAMIC_DEBUG_H
#घोषणा _DYNAMIC_DEBUG_H

#अगर defined(CONFIG_JUMP_LABEL)
#समावेश <linux/jump_label.h>
#पूर्ण_अगर

/*
 * An instance of this काष्ठाure is created in a special
 * ELF section at every dynamic debug callsite.  At runसमय,
 * the special section is treated as an array of these.
 */
काष्ठा _ddebug अणु
	/*
	 * These fields are used to drive the user पूर्णांकerface
	 * क्रम selecting and displaying debug callsites.
	 */
	स्थिर अक्षर *modname;
	स्थिर अक्षर *function;
	स्थिर अक्षर *filename;
	स्थिर अक्षर *क्रमmat;
	अचिन्हित पूर्णांक lineno:18;
	/*
	 * The flags field controls the behaviour at the callsite.
	 * The bits here are changed dynamically when the user
	 * ग_लिखोs commands to <debugfs>/dynamic_debug/control
	 */
#घोषणा _DPRINTK_FLAGS_NONE	0
#घोषणा _DPRINTK_FLAGS_PRINT	(1<<0) /* prपूर्णांकk() a message using the क्रमmat */
#घोषणा _DPRINTK_FLAGS_INCL_MODNAME	(1<<1)
#घोषणा _DPRINTK_FLAGS_INCL_FUNCNAME	(1<<2)
#घोषणा _DPRINTK_FLAGS_INCL_LINENO	(1<<3)
#घोषणा _DPRINTK_FLAGS_INCL_TID		(1<<4)

#घोषणा _DPRINTK_FLAGS_INCL_ANY		\
	(_DPRINTK_FLAGS_INCL_MODNAME | _DPRINTK_FLAGS_INCL_FUNCNAME |\
	 _DPRINTK_FLAGS_INCL_LINENO  | _DPRINTK_FLAGS_INCL_TID)

#अगर defined DEBUG
#घोषणा _DPRINTK_FLAGS_DEFAULT _DPRINTK_FLAGS_PRINT
#अन्यथा
#घोषणा _DPRINTK_FLAGS_DEFAULT 0
#पूर्ण_अगर
	अचिन्हित पूर्णांक flags:8;
#अगर_घोषित CONFIG_JUMP_LABEL
	जोड़ अणु
		काष्ठा अटल_key_true dd_key_true;
		काष्ठा अटल_key_false dd_key_false;
	पूर्ण key;
#पूर्ण_अगर
पूर्ण __attribute__((aligned(8)));



#अगर defined(CONFIG_DYNAMIC_DEBUG_CORE)

/* exported क्रम module authors to exercise >control */
पूर्णांक dynamic_debug_exec_queries(स्थिर अक्षर *query, स्थिर अक्षर *modname);

पूर्णांक ddebug_add_module(काष्ठा _ddebug *tab, अचिन्हित पूर्णांक n,
				स्थिर अक्षर *modname);
बाह्य पूर्णांक ddebug_हटाओ_module(स्थिर अक्षर *mod_name);
बाह्य __म_लिखो(2, 3)
व्योम __dynamic_pr_debug(काष्ठा _ddebug *descriptor, स्थिर अक्षर *fmt, ...);

बाह्य पूर्णांक ddebug_dyndbg_module_param_cb(अक्षर *param, अक्षर *val,
					स्थिर अक्षर *modname);

काष्ठा device;

बाह्य __म_लिखो(3, 4)
व्योम __dynamic_dev_dbg(काष्ठा _ddebug *descriptor, स्थिर काष्ठा device *dev,
		       स्थिर अक्षर *fmt, ...);

काष्ठा net_device;

बाह्य __म_लिखो(3, 4)
व्योम __dynamic_netdev_dbg(काष्ठा _ddebug *descriptor,
			  स्थिर काष्ठा net_device *dev,
			  स्थिर अक्षर *fmt, ...);

काष्ठा ib_device;

बाह्य __म_लिखो(3, 4)
व्योम __dynamic_ibdev_dbg(काष्ठा _ddebug *descriptor,
			 स्थिर काष्ठा ib_device *ibdev,
			 स्थिर अक्षर *fmt, ...);

#घोषणा DEFINE_DYNAMIC_DEBUG_METADATA(name, fmt)		\
	अटल काष्ठा _ddebug  __aligned(8)			\
	__section("__dyndbg") name = अणु				\
		.modname = KBUILD_MODNAME,			\
		.function = __func__,				\
		.filename = __खाता__,				\
		.क्रमmat = (fmt),				\
		.lineno = __LINE__,				\
		.flags = _DPRINTK_FLAGS_DEFAULT,		\
		_DPRINTK_KEY_INIT				\
	पूर्ण

#अगर_घोषित CONFIG_JUMP_LABEL

#अगर_घोषित DEBUG

#घोषणा _DPRINTK_KEY_INIT .key.dd_key_true = (STATIC_KEY_TRUE_INIT)

#घोषणा DYNAMIC_DEBUG_BRANCH(descriptor) \
	अटल_branch_likely(&descriptor.key.dd_key_true)
#अन्यथा
#घोषणा _DPRINTK_KEY_INIT .key.dd_key_false = (STATIC_KEY_FALSE_INIT)

#घोषणा DYNAMIC_DEBUG_BRANCH(descriptor) \
	अटल_branch_unlikely(&descriptor.key.dd_key_false)
#पूर्ण_अगर

#अन्यथा /* !CONFIG_JUMP_LABEL */

#घोषणा _DPRINTK_KEY_INIT

#अगर_घोषित DEBUG
#घोषणा DYNAMIC_DEBUG_BRANCH(descriptor) \
	likely(descriptor.flags & _DPRINTK_FLAGS_PRINT)
#अन्यथा
#घोषणा DYNAMIC_DEBUG_BRANCH(descriptor) \
	unlikely(descriptor.flags & _DPRINTK_FLAGS_PRINT)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_JUMP_LABEL */

#घोषणा __dynamic_func_call(id, fmt, func, ...) करो अणु	\
	DEFINE_DYNAMIC_DEBUG_METADATA(id, fmt);		\
	अगर (DYNAMIC_DEBUG_BRANCH(id))			\
		func(&id, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

#घोषणा __dynamic_func_call_no_desc(id, fmt, func, ...) करो अणु	\
	DEFINE_DYNAMIC_DEBUG_METADATA(id, fmt);			\
	अगर (DYNAMIC_DEBUG_BRANCH(id))				\
		func(__VA_ARGS__);				\
पूर्ण जबतक (0)

/*
 * "Factory macro" क्रम generating a call to func, guarded by a
 * DYNAMIC_DEBUG_BRANCH. The dynamic debug descriptor will be
 * initialized using the fmt argument. The function will be called with
 * the address of the descriptor as first argument, followed by all
 * the varargs. Note that fmt is repeated in invocations of this
 * macro.
 */
#घोषणा _dynamic_func_call(fmt, func, ...)				\
	__dynamic_func_call(__UNIQUE_ID(ddebug), fmt, func, ##__VA_ARGS__)
/*
 * A variant that करोes the same, except that the descriptor is not
 * passed as the first argument to the function; it is only called
 * with precisely the macro's varargs.
 */
#घोषणा _dynamic_func_call_no_desc(fmt, func, ...)	\
	__dynamic_func_call_no_desc(__UNIQUE_ID(ddebug), fmt, func, ##__VA_ARGS__)

#घोषणा dynamic_pr_debug(fmt, ...)				\
	_dynamic_func_call(fmt,	__dynamic_pr_debug,		\
			   pr_fmt(fmt), ##__VA_ARGS__)

#घोषणा dynamic_dev_dbg(dev, fmt, ...)				\
	_dynamic_func_call(fmt,__dynamic_dev_dbg, 		\
			   dev, fmt, ##__VA_ARGS__)

#घोषणा dynamic_netdev_dbg(dev, fmt, ...)			\
	_dynamic_func_call(fmt, __dynamic_netdev_dbg,		\
			   dev, fmt, ##__VA_ARGS__)

#घोषणा dynamic_ibdev_dbg(dev, fmt, ...)			\
	_dynamic_func_call(fmt, __dynamic_ibdev_dbg,		\
			   dev, fmt, ##__VA_ARGS__)

#घोषणा dynamic_hex_dump(prefix_str, prefix_type, rowsize,		\
			 groupsize, buf, len, ascii)			\
	_dynamic_func_call_no_desc(__builtin_स्थिरant_p(prefix_str) ? prefix_str : "hexdump", \
				   prपूर्णांक_hex_dump,			\
				   KERN_DEBUG, prefix_str, prefix_type,	\
				   rowsize, groupsize, buf, len, ascii)

#अन्यथा /* !CONFIG_DYNAMIC_DEBUG_CORE */

#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/prपूर्णांकk.h>

अटल अंतरभूत पूर्णांक ddebug_add_module(काष्ठा _ddebug *tab, अचिन्हित पूर्णांक n,
				    स्थिर अक्षर *modname)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ddebug_हटाओ_module(स्थिर अक्षर *mod)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ddebug_dyndbg_module_param_cb(अक्षर *param, अक्षर *val,
						स्थिर अक्षर *modname)
अणु
	अगर (म_माला(param, "dyndbg")) अणु
		/* aव्योम pr_warn(), which wants pr_fmt() fully defined */
		prपूर्णांकk(KERN_WARNING "dyndbg param is supported only in "
			"CONFIG_DYNAMIC_DEBUG builds\n");
		वापस 0; /* allow and ignore */
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा dynamic_pr_debug(fmt, ...)					\
	करो अणु अगर (0) prपूर्णांकk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__); पूर्ण जबतक (0)
#घोषणा dynamic_dev_dbg(dev, fmt, ...)					\
	करो अणु अगर (0) dev_prपूर्णांकk(KERN_DEBUG, dev, fmt, ##__VA_ARGS__); पूर्ण जबतक (0)
#घोषणा dynamic_hex_dump(prefix_str, prefix_type, rowsize,		\
			 groupsize, buf, len, ascii)			\
	करो अणु अगर (0)							\
		prपूर्णांक_hex_dump(KERN_DEBUG, prefix_str, prefix_type,	\
				rowsize, groupsize, buf, len, ascii);	\
	पूर्ण जबतक (0)

अटल अंतरभूत पूर्णांक dynamic_debug_exec_queries(स्थिर अक्षर *query, स्थिर अक्षर *modname)
अणु
	pr_warn("kernel not built with CONFIG_DYNAMIC_DEBUG_CORE\n");
	वापस 0;
पूर्ण

#पूर्ण_अगर /* !CONFIG_DYNAMIC_DEBUG_CORE */

#पूर्ण_अगर
