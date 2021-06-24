<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 - 1997, 1999 Silicon Graphics, Inc.
 * Copyright (C) 1999 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_SN0_HUB_H
#घोषणा _ASM_SN_SN0_HUB_H

/* The secret password; used to release protection */
#घोषणा HUB_PASSWORD		0x53474972756c6573ull

#घोषणा CHIPID_HUB		0
#घोषणा CHIPID_ROUTER		1

#घोषणा HUB_REV_1_0		1
#घोषणा HUB_REV_2_0		2
#घोषणा HUB_REV_2_1		3
#घोषणा HUB_REV_2_2		4
#घोषणा HUB_REV_2_3		5
#घोषणा HUB_REV_2_4		6

#घोषणा MAX_HUB_PATH		80

#समावेश <यंत्र/sn/sn0/addrs.h>
#समावेश <यंत्र/sn/sn0/hubpi.h>
#समावेश <यंत्र/sn/sn0/hubmd.h>
#समावेश <यंत्र/sn/sn0/hubपन.स>
#समावेश <यंत्र/sn/sn0/hubni.h>
//#समावेश <यंत्र/sn/sn0/hubcore.h>

/* Translation of uncached attributes */
#घोषणा UATTR_HSPEC	0
#घोषणा UATTR_IO	1
#घोषणा UATTR_MSPEC	2
#घोषणा UATTR_UNCAC	3

#अगर_घोषित __ASSEMBLY__
/*
 * Returns the local nasid पूर्णांकo res.
 */
	.macro GET_NASID_ASM res
	dli	\लes, LOCAL_HUB_ADDR(NI_STATUS_REV_ID)
	ld	\लes, (\लes)
	and	\लes, NSRI_NODEID_MASK
	dsrl	\लes, NSRI_NODEID_SHFT
	.endm
#अन्यथा

/*
 * get_nasid() वापसs the physical node id number of the caller.
 */
अटल अंतरभूत nasid_t get_nasid(व्योम)
अणु
	वापस (nasid_t)((LOCAL_HUB_L(NI_STATUS_REV_ID) & NSRI_NODEID_MASK)
			 >> NSRI_NODEID_SHFT);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SN_SN0_HUB_H */
