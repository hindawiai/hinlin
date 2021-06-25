<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_STDIO_H_
#घोषणा _PPC_BOOT_STDIO_H_

#समावेश <मानकतर्क.स>

#घोषणा	ENOMEM		12	/* Out of Memory */
#घोषणा	EINVAL		22	/* Invalid argument */
#घोषणा ENOSPC		28	/* No space left on device */

बाह्य पूर्णांक म_लिखो(स्थिर अक्षर *fmt, ...) __attribute__((क्रमmat(म_लिखो, 1, 2)));

#घोषणा ख_लिखो(fmt, args...)	म_लिखो(args)

बाह्य पूर्णांक प्र_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, ...)
	__attribute__((क्रमmat(म_लिखो, 2, 3)));

बाह्य पूर्णांक भम_लिखो(अक्षर *buf, स्थिर अक्षर *fmt, बहु_सूची args);

#पूर्ण_अगर				/* _PPC_BOOT_STDIO_H_ */
