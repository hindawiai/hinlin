<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FAULT_INJECT_H
#घोषणा _LINUX_FAULT_INJECT_H

#अगर_घोषित CONFIG_FAULT_INJECTION

#समावेश <linux/types.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/atomic.h>

/*
 * For explanation of the elements of this काष्ठा, see
 * Documentation/fault-injection/fault-injection.rst
 */
काष्ठा fault_attr अणु
	अचिन्हित दीर्घ probability;
	अचिन्हित दीर्घ पूर्णांकerval;
	atomic_t बार;
	atomic_t space;
	अचिन्हित दीर्घ verbose;
	bool task_filter;
	अचिन्हित दीर्घ stacktrace_depth;
	अचिन्हित दीर्घ require_start;
	अचिन्हित दीर्घ require_end;
	अचिन्हित दीर्घ reject_start;
	अचिन्हित दीर्घ reject_end;

	अचिन्हित दीर्घ count;
	काष्ठा ratelimit_state ratelimit_state;
	काष्ठा dentry *dname;
पूर्ण;

#घोषणा FAULT_ATTR_INITIALIZER अणु					\
		.पूर्णांकerval = 1,						\
		.बार = ATOMIC_INIT(1),				\
		.require_end = अच_दीर्घ_उच्च,				\
		.stacktrace_depth = 32,					\
		.ratelimit_state = RATELIMIT_STATE_INIT_DISABLED,	\
		.verbose = 2,						\
		.dname = शून्य,						\
	पूर्ण

#घोषणा DECLARE_FAULT_ATTR(name) काष्ठा fault_attr name = FAULT_ATTR_INITIALIZER
पूर्णांक setup_fault_attr(काष्ठा fault_attr *attr, अक्षर *str);
bool should_fail(काष्ठा fault_attr *attr, sमाप_प्रकार size);

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS

काष्ठा dentry *fault_create_debugfs_attr(स्थिर अक्षर *name,
			काष्ठा dentry *parent, काष्ठा fault_attr *attr);

#अन्यथा /* CONFIG_FAULT_INJECTION_DEBUG_FS */

अटल अंतरभूत काष्ठा dentry *fault_create_debugfs_attr(स्थिर अक्षर *name,
			काष्ठा dentry *parent, काष्ठा fault_attr *attr)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION */

काष्ठा kmem_cache;

पूर्णांक should_failslab(काष्ठा kmem_cache *s, gfp_t gfpflags);
#अगर_घोषित CONFIG_FAILSLAB
बाह्य bool __should_failslab(काष्ठा kmem_cache *s, gfp_t gfpflags);
#अन्यथा
अटल अंतरभूत bool __should_failslab(काष्ठा kmem_cache *s, gfp_t gfpflags)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_FAILSLAB */

#पूर्ण_अगर /* _LINUX_FAULT_INJECT_H */
