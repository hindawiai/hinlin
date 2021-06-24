<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This module emits "Hello, world" on prपूर्णांकk when loaded.
 *
 * It is deचिन्हित to be used क्रम basic evaluation of the module loading
 * subप्रणाली (क्रम example when validating module signing/verअगरication). It
 * lacks any extra dependencies, and will not normally be loaded by the
 * प्रणाली unless explicitly requested by name.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>

अटल पूर्णांक __init test_module_init(व्योम)
अणु
	pr_warn("Hello, world\n");

	वापस 0;
पूर्ण

module_init(test_module_init);

अटल व्योम __निकास test_module_निकास(व्योम)
अणु
	pr_warn("Goodbye\n");
पूर्ण

module_निकास(test_module_निकास);

MODULE_AUTHOR("Kees Cook <keescook@chromium.org>");
MODULE_LICENSE("GPL");
