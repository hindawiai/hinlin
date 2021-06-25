<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2004 Olof Johansson <olof@lixom.net>, IBM Corporation
 */

#अगर_अघोषित _POWERPC_SYSDEV_DART_H
#घोषणा _POWERPC_SYSDEV_DART_H


/* Offset from base to control रेजिस्टर */
#घोषणा DART_CNTL	0

/* Offset from base to exception रेजिस्टर */
#घोषणा DART_EXCP_U3	0x10
/* Offset from base to TLB tag रेजिस्टरs */
#घोषणा DART_TAGS_U3	0x1000

/* U4 रेजिस्टरs */
#घोषणा DART_BASE_U4	0x10
#घोषणा DART_SIZE_U4	0x20
#घोषणा DART_EXCP_U4	0x30
#घोषणा DART_TAGS_U4	0x1000

/* Control Register fields */

/* U3 रेजिस्टरs */
#घोषणा DART_CNTL_U3_BASE_MASK	0xfffff
#घोषणा DART_CNTL_U3_BASE_SHIFT	12
#घोषणा DART_CNTL_U3_FLUSHTLB	0x400
#घोषणा DART_CNTL_U3_ENABLE	0x200
#घोषणा DART_CNTL_U3_SIZE_MASK	0x1ff
#घोषणा DART_CNTL_U3_SIZE_SHIFT	0

/* U4 रेजिस्टरs */
#घोषणा DART_BASE_U4_BASE_MASK	0xffffff
#घोषणा DART_BASE_U4_BASE_SHIFT	0
#घोषणा DART_CNTL_U4_ENABLE	0x80000000
#घोषणा DART_CNTL_U4_IONE	0x40000000
#घोषणा DART_CNTL_U4_FLUSHTLB	0x20000000
#घोषणा DART_CNTL_U4_IDLE	0x10000000
#घोषणा DART_CNTL_U4_PAR_EN	0x08000000
#घोषणा DART_CNTL_U4_IONE_MASK	0x07ffffff
#घोषणा DART_SIZE_U4_SIZE_MASK	0x1fff
#घोषणा DART_SIZE_U4_SIZE_SHIFT	0

#घोषणा DART_REG(r)	(dart + ((r) >> 2))
#घोषणा DART_IN(r)	(in_be32(DART_REG(r)))
#घोषणा DART_OUT(r,v)	(out_be32(DART_REG(r), (v)))


/* size of table in pages */


/* DART table fields */

#घोषणा DARTMAP_VALID   0x80000000
#घोषणा DARTMAP_RPNMASK 0x00ffffff


#घोषणा DART_PAGE_SHIFT		12
#घोषणा DART_PAGE_SIZE		(1 << DART_PAGE_SHIFT)


#पूर्ण_अगर /* _POWERPC_SYSDEV_DART_H */
