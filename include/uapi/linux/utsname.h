<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_UTSNAME_H
#घोषणा _UAPI_LINUX_UTSNAME_H

#घोषणा __OLD_UTS_LEN 8

काष्ठा olकरोld_utsname अणु
	अक्षर sysname[9];
	अक्षर nodename[9];
	अक्षर release[9];
	अक्षर version[9];
	अक्षर machine[9];
पूर्ण;

#घोषणा __NEW_UTS_LEN 64

काष्ठा old_utsname अणु
	अक्षर sysname[65];
	अक्षर nodename[65];
	अक्षर release[65];
	अक्षर version[65];
	अक्षर machine[65];
पूर्ण;

काष्ठा new_utsname अणु
	अक्षर sysname[__NEW_UTS_LEN + 1];
	अक्षर nodename[__NEW_UTS_LEN + 1];
	अक्षर release[__NEW_UTS_LEN + 1];
	अक्षर version[__NEW_UTS_LEN + 1];
	अक्षर machine[__NEW_UTS_LEN + 1];
	अक्षर करोमुख्यname[__NEW_UTS_LEN + 1];
पूर्ण;


#पूर्ण_अगर /* _UAPI_LINUX_UTSNAME_H */
