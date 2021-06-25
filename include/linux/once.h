<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_ONCE_H
#घोषणा _LINUX_ONCE_H

#समावेश <linux/types.h>
#समावेश <linux/jump_label.h>

bool __करो_once_start(bool *करोne, अचिन्हित दीर्घ *flags);
व्योम __करो_once_करोne(bool *करोne, काष्ठा अटल_key_true *once_key,
		    अचिन्हित दीर्घ *flags);

/* Call a function exactly once. The idea of DO_ONCE() is to perक्रमm
 * a function call such as initialization of अक्रमom seeds, etc, only
 * once, where DO_ONCE() can live in the fast-path. After @func has
 * been called with the passed arguments, the अटल key will patch
 * out the condition पूर्णांकo a nop. DO_ONCE() guarantees type safety of
 * arguments!
 *
 * Not that the following is not equivalent ...
 *
 *   DO_ONCE(func, arg);
 *   DO_ONCE(func, arg);
 *
 * ... to this version:
 *
 *   व्योम foo(व्योम)
 *   अणु
 *     DO_ONCE(func, arg);
 *   पूर्ण
 *
 *   foo();
 *   foo();
 *
 * In हाल the one-समय invocation could be triggered from multiple
 * places, then a common helper function must be defined, so that only
 * a single अटल key will be placed there!
 */
#घोषणा DO_ONCE(func, ...)						     \
	(अणु								     \
		bool ___ret = false;					     \
		अटल bool ___करोne = false;				     \
		अटल DEFINE_STATIC_KEY_TRUE(___once_key);		     \
		अगर (अटल_branch_unlikely(&___once_key)) अणु		     \
			अचिन्हित दीर्घ ___flags;				     \
			___ret = __करो_once_start(&___करोne, &___flags);	     \
			अगर (unlikely(___ret)) अणु				     \
				func(__VA_ARGS__);			     \
				__करो_once_करोne(&___करोne, &___once_key,	     \
					       &___flags);		     \
			पूर्ण						     \
		पूर्ण							     \
		___ret;							     \
	पूर्ण)

#घोषणा get_अक्रमom_once(buf, nbytes)					     \
	DO_ONCE(get_अक्रमom_bytes, (buf), (nbytes))
#घोषणा get_अक्रमom_once_रुको(buf, nbytes)                                    \
	DO_ONCE(get_अक्रमom_bytes_रुको, (buf), (nbytes))                      \

#पूर्ण_अगर /* _LINUX_ONCE_H */
