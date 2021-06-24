<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Trivial I/O routine definitions, पूर्णांकentionally meant to be included
 * multiple बार. Ugly I/O routine concatenation helpers taken from
 * alpha. Must be included _beक्रमe_ पन.स to aव्योम preprocessor-induced
 * routine mismatch.
 */
#घोषणा IO_CONCAT(a,b)	_IO_CONCAT(a,b)
#घोषणा _IO_CONCAT(a,b)	a ## _ ## b

#अगर_अघोषित __IO_PREFIX
#त्रुटि "Don't include this header without a valid system prefix"
#पूर्ण_अगर

व्योम __iomem *IO_CONCAT(__IO_PREFIX,ioport_map)(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक size);
व्योम IO_CONCAT(__IO_PREFIX,ioport_unmap)(व्योम __iomem *addr);
व्योम IO_CONCAT(__IO_PREFIX,mem_init)(व्योम);

#अघोषित __IO_PREFIX
