<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VT_H
#घोषणा _LINUX_VT_H

#समावेश <uapi/linux/vt.h>


/* Virtual Terminal events. */
#घोषणा VT_ALLOCATE		0x0001 /* Console got allocated */
#घोषणा VT_DEALLOCATE		0x0002 /* Console will be deallocated */
#घोषणा VT_WRITE		0x0003 /* A अक्षर got output */
#घोषणा VT_UPDATE		0x0004 /* A bigger update occurred */
#घोषणा VT_PREWRITE		0x0005 /* A अक्षर is about to be written to the console */

#अगर_घोषित CONFIG_VT_CONSOLE

बाह्य पूर्णांक vt_kmsg_redirect(पूर्णांक new);

#अन्यथा

अटल अंतरभूत पूर्णांक vt_kmsg_redirect(पूर्णांक new)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_VT_H */
