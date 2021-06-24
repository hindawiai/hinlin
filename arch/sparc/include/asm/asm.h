<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_ASM_H
#घोषणा _SPARC_ASM_H

/* Macros to assist the sharing of assembler code between 32-bit and
 * 64-bit sparc.
 */

#अगर_घोषित CONFIG_SPARC64
#घोषणा BRANCH32(TYPE, PREDICT, DEST) \
	TYPE,PREDICT	%icc, DEST
#घोषणा BRANCH32_ANNUL(TYPE, PREDICT, DEST) \
	TYPE,a,PREDICT	%icc, DEST
#घोषणा BRANCH_REG_ZERO(PREDICT, REG, DEST) \
	brz,PREDICT	REG, DEST
#घोषणा BRANCH_REG_ZERO_ANNUL(PREDICT, REG, DEST) \
	brz,a,PREDICT	REG, DEST
#घोषणा BRANCH_REG_NOT_ZERO(PREDICT, REG, DEST) \
	brnz,PREDICT	REG, DEST
#घोषणा BRANCH_REG_NOT_ZERO_ANNUL(PREDICT, REG, DEST) \
	brnz,a,PREDICT	REG, DEST
#अन्यथा
#घोषणा BRANCH32(TYPE, PREDICT, DEST) \
	TYPE		DEST
#घोषणा BRANCH32_ANNUL(TYPE, PREDICT, DEST) \
	TYPE,a		DEST
#घोषणा BRANCH_REG_ZERO(PREDICT, REG, DEST) \
	cmp		REG, 0; \
	be		DEST
#घोषणा BRANCH_REG_ZERO_ANNUL(PREDICT, REG, DEST) \
	cmp		REG, 0; \
	be,a		DEST
#घोषणा BRANCH_REG_NOT_ZERO(PREDICT, REG, DEST) \
	cmp		REG, 0; \
	bne		DEST
#घोषणा BRANCH_REG_NOT_ZERO_ANNUL(PREDICT, REG, DEST) \
	cmp		REG, 0; \
	bne,a		DEST
#पूर्ण_अगर

#पूर्ण_अगर /* _SPARC_ASM_H */
