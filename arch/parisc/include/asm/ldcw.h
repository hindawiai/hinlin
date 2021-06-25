<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PARISC_LDCW_H
#घोषणा __PARISC_LDCW_H

#अगर_अघोषित CONFIG_PA20
/* Because kदो_स्मृति only guarantees 8-byte alignment क्रम kदो_स्मृति'd data,
   and GCC only guarantees 8-byte alignment क्रम stack locals, we can't
   be assured of 16-byte alignment क्रम atomic lock data even अगर we
   specअगरy "__attribute ((aligned(16)))" in the type declaration.  So,
   we use a काष्ठा containing an array of four पूर्णांकs क्रम the atomic lock
   type and dynamically select the 16-byte aligned पूर्णांक from the array
   क्रम the semaphore.  */

#घोषणा __PA_LDCW_ALIGNMENT	16
#घोषणा __PA_LDCW_ALIGN_ORDER	4
#घोषणा __ldcw_align(a) (अणु					\
	अचिन्हित दीर्घ __ret = (अचिन्हित दीर्घ) &(a)->lock[0];	\
	__ret = (__ret + __PA_LDCW_ALIGNMENT - 1)		\
		& ~(__PA_LDCW_ALIGNMENT - 1);			\
	(अस्थिर अचिन्हित पूर्णांक *) __ret;			\
पूर्ण)
#घोषणा __LDCW	"ldcw"

#अन्यथा /*CONFIG_PA20*/
/* From: "Jim Hull" <jim.hull of hp.com>
   I've attached a summary of the change, but basically, क्रम PA 2.0, as
   दीर्घ as the ",CO" (coherent operation) completer is specअगरied, then the
   16-byte alignment requirement क्रम ldcw and ldcd is relaxed, and instead
   they only require "natural" alignment (4-byte क्रम ldcw, 8-byte क्रम
   ldcd). */

#घोषणा __PA_LDCW_ALIGNMENT	4
#घोषणा __PA_LDCW_ALIGN_ORDER	2
#घोषणा __ldcw_align(a) (&(a)->slock)
#घोषणा __LDCW	"ldcw,co"

#पूर्ण_अगर /*!CONFIG_PA20*/

/* LDCW, the only atomic पढ़ो-ग_लिखो operation PA-RISC has. *sigh*.
   We करोn't explicitly expose that "*a" may be written as reload
   fails to find a रेजिस्टर in class R1_REGS when "a" needs to be
   reloaded when generating 64-bit PIC code.  Instead, we clobber
   memory to indicate to the compiler that the assembly code पढ़ोs
   or ग_लिखोs to items other than those listed in the input and output
   opeअक्रमs.  This may pessimize the code somewhat but __ldcw is
   usually used within code blocks surrounded by memory barriers.  */
#घोषणा __ldcw(a) (अणु						\
	अचिन्हित __ret;						\
	__यंत्र__ __अस्थिर__(__LDCW " 0(%1),%0"			\
		: "=r" (__ret) : "r" (a) : "memory");		\
	__ret;							\
पूर्ण)

#अगर_घोषित CONFIG_SMP
# define __lock_aligned __section(".data..lock_aligned")
#पूर्ण_अगर

#पूर्ण_अगर /* __PARISC_LDCW_H */
