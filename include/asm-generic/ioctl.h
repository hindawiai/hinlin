<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_IOCTL_H
#घोषणा _ASM_GENERIC_IOCTL_H

#समावेश <uapi/यंत्र-generic/ioctl.h>

#अगर_घोषित __CHECKER__
#घोषणा _IOC_TYPECHECK(t) (माप(t))
#अन्यथा
/* provoke compile error क्रम invalid uses of size argument */
बाह्य अचिन्हित पूर्णांक __invalid_size_argument_क्रम_IOC;
#घोषणा _IOC_TYPECHECK(t) \
	((माप(t) == माप(t[1]) && \
	  माप(t) < (1 << _IOC_SIZEBITS)) ? \
	  माप(t) : __invalid_size_argument_क्रम_IOC)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_GENERIC_IOCTL_H */
