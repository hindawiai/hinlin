<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/fault-inject.h>
#समावेश <linux/fault-inject-usercopy.h>

अटल काष्ठा अणु
	काष्ठा fault_attr attr;
पूर्ण fail_usercopy = अणु
	.attr = FAULT_ATTR_INITIALIZER,
पूर्ण;

अटल पूर्णांक __init setup_fail_usercopy(अक्षर *str)
अणु
	वापस setup_fault_attr(&fail_usercopy.attr, str);
पूर्ण
__setup("fail_usercopy=", setup_fail_usercopy);

#अगर_घोषित CONFIG_FAULT_INJECTION_DEBUG_FS

अटल पूर्णांक __init fail_usercopy_debugfs(व्योम)
अणु
	काष्ठा dentry *dir;

	dir = fault_create_debugfs_attr("fail_usercopy", शून्य,
					&fail_usercopy.attr);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);

	वापस 0;
पूर्ण

late_initcall(fail_usercopy_debugfs);

#पूर्ण_अगर /* CONFIG_FAULT_INJECTION_DEBUG_FS */

bool should_fail_usercopy(व्योम)
अणु
	वापस should_fail(&fail_usercopy.attr, 1);
पूर्ण
EXPORT_SYMBOL_GPL(should_fail_usercopy);
