<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UCS2_STRING_H_
#घोषणा _LINUX_UCS2_STRING_H_

#समावेश <linux/types.h>	/* क्रम माप_प्रकार */
#समावेश <linux/मानकघोष.स>	/* क्रम शून्य */

प्रकार u16 ucs2_अक्षर_t;

अचिन्हित दीर्घ ucs2_strnlen(स्थिर ucs2_अक्षर_t *s, माप_प्रकार maxlength);
अचिन्हित दीर्घ ucs2_म_माप(स्थिर ucs2_अक्षर_t *s);
अचिन्हित दीर्घ ucs2_strsize(स्थिर ucs2_अक्षर_t *data, अचिन्हित दीर्घ maxlength);
पूर्णांक ucs2_म_भेदन(स्थिर ucs2_अक्षर_t *a, स्थिर ucs2_अक्षर_t *b, माप_प्रकार len);

अचिन्हित दीर्घ ucs2_utf8size(स्थिर ucs2_अक्षर_t *src);
अचिन्हित दीर्घ ucs2_as_utf8(u8 *dest, स्थिर ucs2_अक्षर_t *src,
			   अचिन्हित दीर्घ maxlength);

#पूर्ण_अगर /* _LINUX_UCS2_STRING_H_ */
