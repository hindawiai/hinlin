<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UML_INIT_H
#घोषणा _LINUX_UML_INIT_H

/* These macros are used to mark some functions or
 * initialized data (करोesn't apply to uninitialized data)
 * as `initialization' functions. The kernel can take this
 * as hपूर्णांक that the function is used only during the initialization
 * phase and मुक्त up used memory resources after
 *
 * Usage:
 * For functions:
 *
 * You should add __init immediately beक्रमe the function name, like:
 *
 * अटल व्योम __init iniपंचांगe(पूर्णांक x, पूर्णांक y)
 * अणु
 *    बाह्य पूर्णांक z; z = x * y;
 * पूर्ण
 *
 * If the function has a prototype somewhere, you can also add
 * __init between closing brace of the prototype and semicolon:
 *
 * बाह्य पूर्णांक initialize_foobar_device(पूर्णांक, पूर्णांक, पूर्णांक) __init;
 *
 * For initialized data:
 * You should insert __initdata between the variable name and equal
 * sign followed by value, e.g.:
 *
 * अटल पूर्णांक init_variable __initdata = 0;
 * अटल स्थिर अक्षर linux_logo[] __initस्थिर = अणु 0x32, 0x36, ... पूर्ण;
 *
 * Don't क्रमget to initialize data not at file scope, i.e. within a function,
 * as gcc otherwise माला_दो the data पूर्णांकo the bss section and not पूर्णांकo the init
 * section.
 *
 * Also note, that this data cannot be "const".
 */

#अगर_अघोषित _LINUX_INIT_H
प्रकार पूर्णांक (*initcall_t)(व्योम);
प्रकार व्योम (*निकासcall_t)(व्योम);

#समावेश <linux/compiler_types.h>

/* These are क्रम everybody (although not all archs will actually
   discard it in modules) */
#घोषणा __init		__section(".init.text")
#घोषणा __initdata	__section(".init.data")
#घोषणा __निकासdata	__section(".exit.data")
#घोषणा __निकास_call	__used __section(".exitcall.exit")

#अगर_घोषित MODULE
#घोषणा __निकास		__section(".exit.text")
#अन्यथा
#घोषणा __निकास		__used __section(".exit.text")
#पूर्ण_अगर

#पूर्ण_अगर

#अगर_अघोषित MODULE
काष्ठा uml_param अणु
        स्थिर अक्षर *str;
        पूर्णांक (*setup_func)(अक्षर *, पूर्णांक *);
पूर्ण;

बाह्य initcall_t __uml_postsetup_start, __uml_postsetup_end;
बाह्य स्थिर अक्षर *__uml_help_start, *__uml_help_end;
#पूर्ण_अगर

#घोषणा __uml_निकासcall(fn)						\
	अटल निकासcall_t __uml_निकासcall_##fn __uml_निकास_call = fn

बाह्य काष्ठा uml_param __uml_setup_start, __uml_setup_end;

#घोषणा __uml_postsetup(fn)						\
	अटल initcall_t __uml_postsetup_##fn __uml_postsetup_call = fn

#घोषणा __non_empty_string(dummyname,string)				\
	काष्ठा __uml_non_empty_string_काष्ठा_##dummyname		\
	अणु								\
		अक्षर _string[माप(string)-2];				\
	पूर्ण

#अगर_अघोषित MODULE
#घोषणा __uml_setup(str, fn, help...)					\
	__non_empty_string(fn ##_setup, str);				\
	__uml_help(fn, help);						\
	अटल अक्षर __uml_setup_str_##fn[] __initdata = str;		\
	अटल काष्ठा uml_param __uml_setup_##fn __uml_init_setup = अणु __uml_setup_str_##fn, fn पूर्ण
#अन्यथा
#घोषणा __uml_setup(str, fn, help...)					\

#पूर्ण_अगर

#घोषणा __uml_help(fn, help...)						\
	__non_empty_string(fn ##__help, help);				\
	अटल अक्षर __uml_help_str_##fn[] __initdata = help;		\
	अटल स्थिर अक्षर *__uml_help_##fn __uml_setup_help = __uml_help_str_##fn

/*
 * Mark functions and data as being only used at initialization
 * or निकास समय.
 */
#घोषणा __uml_init_setup	__used __section(".uml.setup.init")
#घोषणा __uml_setup_help	__used __section(".uml.help.init")
#घोषणा __uml_postsetup_call	__used __section(".uml.postsetup.init")
#घोषणा __uml_निकास_call		__used __section(".uml.exitcall.exit")

#अगर_घोषित __UM_HOST__

#घोषणा __define_initcall(level,fn) \
	अटल initcall_t __initcall_##fn __used \
	__attribute__((__section__(".initcall" level ".init"))) = fn

/* Userspace initcalls shouldn't depend on anything in the kernel, so we'll
 * make them run first.
 */
#घोषणा __initcall(fn) __define_initcall("1", fn)

#घोषणा __निकासcall(fn) अटल निकासcall_t __निकासcall_##fn __निकास_call = fn

#घोषणा __init_call	__used __section(".initcall.init")

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_UML_INIT_H */
