<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_INSTRUMENTATION_H
#घोषणा __LINUX_INSTRUMENTATION_H

#अगर defined(CONFIG_DEBUG_ENTRY) && defined(CONFIG_STACK_VALIDATION)

/* Begin/end of an instrumentation safe region */
#घोषणा instrumentation_begin() (अणु					\
	यंत्र अस्थिर("%c0: nop\n\t"						\
		     ".pushsection .discard.instr_begin\n\t"		\
		     ".long %c0b - .\n\t"				\
		     ".popsection\n\t" : : "i" (__COUNTER__));		\
पूर्ण)

/*
 * Because instrumentation_अणुbegin,endपूर्ण() can nest, objtool validation considers
 * _begin() a +1 and _end() a -1 and computes a sum over the inकाष्ठाions.
 * When the value is greater than 0, we consider instrumentation allowed.
 *
 * There is a problem with code like:
 *
 * noinstr व्योम foo()
 * अणु
 *	instrumentation_begin();
 *	...
 *	अगर (cond) अणु
 *		instrumentation_begin();
 *		...
 *		instrumentation_end();
 *	पूर्ण
 *	bar();
 *	instrumentation_end();
 * पूर्ण
 *
 * If instrumentation_end() would be an empty label, like all the other
 * annotations, the inner _end(), which is at the end of a conditional block,
 * would land on the inकाष्ठाion after the block.
 *
 * If we then consider the sum of the !cond path, we'll see that the call to
 * bar() is with a 0-value, even though, we meant it to happen with a positive
 * value.
 *
 * To aव्योम this, have _end() be a NOP inकाष्ठाion, this ensures it will be
 * part of the condition block and करोes not escape.
 */
#घोषणा instrumentation_end() (अणु					\
	यंत्र अस्थिर("%c0: nop\n\t"					\
		     ".pushsection .discard.instr_end\n\t"		\
		     ".long %c0b - .\n\t"				\
		     ".popsection\n\t" : : "i" (__COUNTER__));		\
पूर्ण)
#अन्यथा
# define instrumentation_begin()	करो अणु पूर्ण जबतक(0)
# define instrumentation_end()		करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_INSTRUMENTATION_H */
