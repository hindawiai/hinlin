<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/lib/libgcc.h
 */

#अगर_अघोषित __LIB_LIBGCC_H
#घोषणा __LIB_LIBGCC_H

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

#पूर्ण_अगर /* __ASM_LIBGCC_H */
