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

काष्ठा TWकाष्ठा अणु
	दीर्घ दीर्घ high, low;
पूर्ण;
#या_अगर defined(__LITTLE_ENDIAN)
काष्ठा DWकाष्ठा अणु
	पूर्णांक low, high;
पूर्ण;

काष्ठा TWकाष्ठा अणु
	दीर्घ दीर्घ low, high;
पूर्ण;
#अन्यथा
#त्रुटि I feel sick.
#पूर्ण_अगर

प्रकार जोड़ अणु
	काष्ठा DWकाष्ठा s;
	दीर्घ दीर्घ ll;
पूर्ण DWजोड़;

#अगर defined(CONFIG_64BIT) && defined(CONFIG_CPU_MIPSR6)
प्रकार पूर्णांक ti_type __attribute__((mode(TI)));

प्रकार जोड़ अणु
	काष्ठा TWकाष्ठा s;
	ti_type ti;
पूर्ण TWजोड़;
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_LIBGCC_H */
