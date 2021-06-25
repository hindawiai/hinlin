<शैली गुरु>
/*
 * This header file describes this specअगरic Xtensa processor's TIE extensions
 * that extend basic Xtensa core functionality.  It is customized to this
 * Xtensa processor configuration.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1999-2007 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_CORE_TIE_H
#घोषणा _XTENSA_CORE_TIE_H

#घोषणा XCHAL_CP_NUM			0	/* number of coprocessors */
#घोषणा XCHAL_CP_MAX			0	/* max CP ID + 1 (0 अगर none) */
#घोषणा XCHAL_CP_MASK			0x00	/* biपंचांगask of all CPs by ID */
#घोषणा XCHAL_CP_PORT_MASK		0x00	/* biपंचांगask of only port CPs */

/*  Filler info क्रम unasचिन्हित coprocessors, to simplअगरy arrays etc:  */
#घोषणा XCHAL_NCP_SA_SIZE		0
#घोषणा XCHAL_NCP_SA_ALIGN		1
#घोषणा XCHAL_CP0_SA_SIZE		0
#घोषणा XCHAL_CP0_SA_ALIGN		1
#घोषणा XCHAL_CP1_SA_SIZE		0
#घोषणा XCHAL_CP1_SA_ALIGN		1
#घोषणा XCHAL_CP2_SA_SIZE		0
#घोषणा XCHAL_CP2_SA_ALIGN		1
#घोषणा XCHAL_CP3_SA_SIZE		0
#घोषणा XCHAL_CP3_SA_ALIGN		1
#घोषणा XCHAL_CP4_SA_SIZE		0
#घोषणा XCHAL_CP4_SA_ALIGN		1
#घोषणा XCHAL_CP5_SA_SIZE		0
#घोषणा XCHAL_CP5_SA_ALIGN		1
#घोषणा XCHAL_CP6_SA_SIZE		0
#घोषणा XCHAL_CP6_SA_ALIGN		1
#घोषणा XCHAL_CP7_SA_SIZE		0
#घोषणा XCHAL_CP7_SA_ALIGN		1

/*  Save area क्रम non-coprocessor optional and custom (TIE) state:  */
#घोषणा XCHAL_NCP_SA_SIZE		0
#घोषणा XCHAL_NCP_SA_ALIGN		1

/*  Total save area क्रम optional and custom state (NCP + CPn):  */
#घोषणा XCHAL_TOTAL_SA_SIZE		0	/* with 16-byte align padding */
#घोषणा XCHAL_TOTAL_SA_ALIGN		1	/* actual minimum alignment */

#घोषणा XCHAL_NCP_SA_NUM	0
#घोषणा XCHAL_NCP_SA_LIST(s)
#घोषणा XCHAL_CP0_SA_NUM	0
#घोषणा XCHAL_CP0_SA_LIST(s)
#घोषणा XCHAL_CP1_SA_NUM	0
#घोषणा XCHAL_CP1_SA_LIST(s)
#घोषणा XCHAL_CP2_SA_NUM	0
#घोषणा XCHAL_CP2_SA_LIST(s)
#घोषणा XCHAL_CP3_SA_NUM	0
#घोषणा XCHAL_CP3_SA_LIST(s)
#घोषणा XCHAL_CP4_SA_NUM	0
#घोषणा XCHAL_CP4_SA_LIST(s)
#घोषणा XCHAL_CP5_SA_NUM	0
#घोषणा XCHAL_CP5_SA_LIST(s)
#घोषणा XCHAL_CP6_SA_NUM	0
#घोषणा XCHAL_CP6_SA_LIST(s)
#घोषणा XCHAL_CP7_SA_NUM	0
#घोषणा XCHAL_CP7_SA_LIST(s)

/* Byte length of inकाष्ठाion from its first nibble (op0 field), per FLIX.  */
#घोषणा XCHAL_OP0_FORMAT_LENGTHS	3,3,3,3,3,3,3,3,2,2,2,2,2,2,3,3

#पूर्ण_अगर /*_XTENSA_CORE_TIE_H*/

