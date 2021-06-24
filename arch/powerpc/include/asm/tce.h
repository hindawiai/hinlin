<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2001 Mike Corrigan & Dave Engebretsen, IBM Corporation
 * Reग_लिखो, cleanup:
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 */

#अगर_अघोषित _ASM_POWERPC_TCE_H
#घोषणा _ASM_POWERPC_TCE_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/iommu.h>

/*
 * Tces come in two क्रमmats, one क्रम the भव bus and a dअगरferent
 * क्रमmat क्रम PCI.  PCI TCEs can have hardware or software मुख्यtianed
 * coherency.
 */
#घोषणा TCE_VB			0
#घोषणा TCE_PCI			1

/* TCE page size is 4096 bytes (1 << 12) */

#घोषणा TCE_SHIFT	12
#घोषणा TCE_PAGE_SIZE	(1 << TCE_SHIFT)

#घोषणा TCE_ENTRY_SIZE		8		/* each TCE is 64 bits */

#घोषणा TCE_RPN_MASK		0xfffffffffful  /* 40-bit RPN (4K pages) */
#घोषणा TCE_RPN_SHIFT		12
#घोषणा TCE_VALID		0x800		/* TCE valid */
#घोषणा TCE_ALLIO		0x400		/* TCE valid क्रम all lpars */
#घोषणा TCE_PCI_WRITE		0x2		/* ग_लिखो from PCI allowed */
#घोषणा TCE_PCI_READ		0x1		/* पढ़ो from PCI allowed */
#घोषणा TCE_VB_WRITE		0x1		/* ग_लिखो from VB allowed */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_TCE_H */
