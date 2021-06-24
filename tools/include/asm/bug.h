<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_ASM_BUG_H
#घोषणा _TOOLS_ASM_BUG_H

#समावेश <linux/compiler.h>
#समावेश <मानकपन.स>

#घोषणा __WARN_म_लिखो(arg...)	करो अणु ख_लिखो(मानक_त्रुटि, arg); पूर्ण जबतक (0)

#घोषणा WARN(condition, क्रमmat...) (अणु		\
	पूर्णांक __ret_warn_on = !!(condition);	\
	अगर (unlikely(__ret_warn_on))		\
		__WARN_म_लिखो(क्रमmat);		\
	unlikely(__ret_warn_on);		\
पूर्ण)

#घोषणा WARN_ON(condition) (अणु					\
	पूर्णांक __ret_warn_on = !!(condition);			\
	अगर (unlikely(__ret_warn_on))				\
		__WARN_म_लिखो("assertion failed at %s:%d\n",	\
				__खाता__, __LINE__);		\
	unlikely(__ret_warn_on);				\
पूर्ण)

#घोषणा WARN_ON_ONCE(condition) (अणु			\
	अटल पूर्णांक __warned;				\
	पूर्णांक __ret_warn_once = !!(condition);		\
							\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु	\
		__warned = true;			\
		WARN_ON(1);				\
	पूर्ण						\
	unlikely(__ret_warn_once);			\
पूर्ण)

#घोषणा WARN_ONCE(condition, क्रमmat...)	(अणु	\
	अटल पूर्णांक __warned;			\
	पूर्णांक __ret_warn_once = !!(condition);	\
						\
	अगर (unlikely(__ret_warn_once))		\
		अगर (WARN(!__warned, क्रमmat)) 	\
			__warned = 1;		\
	unlikely(__ret_warn_once);		\
पूर्ण)

#पूर्ण_अगर /* _TOOLS_ASM_BUG_H */
