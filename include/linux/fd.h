<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FD_H
#घोषणा _LINUX_FD_H

#समावेश <uapi/linux/fd.h>

#अगर_घोषित CONFIG_COMPAT
#समावेश <linux/compat.h>

काष्ठा compat_floppy_काष्ठा अणु
	compat_uपूर्णांक_t	size;
	compat_uपूर्णांक_t	sect;
	compat_uपूर्णांक_t	head;
	compat_uपूर्णांक_t	track;
	compat_uपूर्णांक_t	stretch;
	अचिन्हित अक्षर	gap;
	अचिन्हित अक्षर	rate;
	अचिन्हित अक्षर	spec1;
	अचिन्हित अक्षर	fmt_gap;
	स्थिर compat_caddr_t name;
पूर्ण;

#घोषणा FDGETPRM32 _IOR(2, 0x04, काष्ठा compat_floppy_काष्ठा)
#पूर्ण_अगर
#पूर्ण_अगर
