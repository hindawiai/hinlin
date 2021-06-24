<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LIBGCC_H
#घोषणा __ASM_LIBGCC_H

#समावेश <यंत्र/byteorder.h>

प्रकार पूर्णांक word_type __attribute__ ((mode (__word__)));

#अगर_घोषित __BIG_ENDIAN
काष्ठा DWकाष्ठा अणु
	पूर्णांक high, low;
पूर्ण;
#या_अगर defined(__LITTLE_ENDIAN)
काष्ठा DWकाष्ठा अणु
	पूर्णांक low, high;
पूर्ण;
#अन्यथा
#त्रुटि I feel sick.
#पूर्ण_अगर

प्रकार जोड़ अणु
	काष्ठा DWकाष्ठा s;
	दीर्घ दीर्घ ll;
पूर्ण DWजोड़;

बाह्य दीर्घ दीर्घ __ashldi3(दीर्घ दीर्घ u, word_type b);
बाह्य दीर्घ दीर्घ __ashrdi3(दीर्घ दीर्घ u, word_type b);
बाह्य word_type __cmpdi2(दीर्घ दीर्घ a, दीर्घ दीर्घ b);
बाह्य दीर्घ दीर्घ __lshrdi3(दीर्घ दीर्घ u, word_type b);
बाह्य दीर्घ दीर्घ __muldi3(दीर्घ दीर्घ u, दीर्घ दीर्घ v);
बाह्य word_type __ucmpdi2(अचिन्हित दीर्घ दीर्घ a, अचिन्हित दीर्घ दीर्घ b);

#पूर्ण_अगर /* __ASM_LIBGCC_H */
