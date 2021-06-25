<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UML_LONGJMP_H
#घोषणा __UML_LONGJMP_H

#समावेश <sysdep/archसमलाँघ.स>
#समावेश <os.h>

बाह्य पूर्णांक बनाओ_लाँघ(लाँघ_बफ);
बाह्य व्योम दीर्घ_लाँघ(लाँघ_बफ, पूर्णांक);

#घोषणा UML_LONGJMP(buf, val) करो अणु \
	दीर्घ_लाँघ(*buf, val);	\
पूर्ण जबतक(0)

#घोषणा UML_SETJMP(buf) (अणु \
	पूर्णांक n;	   \
	अस्थिर पूर्णांक enable;	\
	enable = get_संकेतs(); \
	n = बनाओ_लाँघ(*buf); \
	अगर(n != 0) \
		set_संकेतs_trace(enable); \
	n; पूर्ण)

#पूर्ण_अगर
