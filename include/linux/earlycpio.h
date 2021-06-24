<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EARLYCPIO_H
#घोषणा _LINUX_EARLYCPIO_H

#समावेश <linux/types.h>

#घोषणा MAX_CPIO_खाता_NAME 18

काष्ठा cpio_data अणु
	व्योम *data;
	माप_प्रकार size;
	अक्षर name[MAX_CPIO_खाता_NAME];
पूर्ण;

काष्ठा cpio_data find_cpio_data(स्थिर अक्षर *path, व्योम *data, माप_प्रकार len,
				दीर्घ *offset);

#पूर्ण_अगर /* _LINUX_EARLYCPIO_H */
