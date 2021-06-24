<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_STDDEF_H
#घोषणा _LINUX_STDDEF_H

#समावेश <uapi/linux/मानकघोष.स>

#अघोषित शून्य
#घोषणा शून्य ((व्योम *)0)

क्रमागत अणु
	false	= 0,
	true	= 1
पूर्ण;

#अघोषित दुरत्व
#अगर_घोषित __compiler_दुरत्व
#घोषणा दुरत्व(TYPE, MEMBER)	__compiler_दुरत्व(TYPE, MEMBER)
#अन्यथा
#घोषणा दुरत्व(TYPE, MEMBER)	((माप_प्रकार)&((TYPE *)0)->MEMBER)
#पूर्ण_अगर

/**
 * माप_field(TYPE, MEMBER)
 *
 * @TYPE: The काष्ठाure containing the field of पूर्णांकerest
 * @MEMBER: The field to वापस the size of
 */
#घोषणा माप_field(TYPE, MEMBER) माप((((TYPE *)0)->MEMBER))

/**
 * दुरत्वend(TYPE, MEMBER)
 *
 * @TYPE: The type of the काष्ठाure
 * @MEMBER: The member within the काष्ठाure to get the end offset of
 */
#घोषणा दुरत्वend(TYPE, MEMBER) \
	(दुरत्व(TYPE, MEMBER)	+ माप_field(TYPE, MEMBER))

#पूर्ण_अगर
