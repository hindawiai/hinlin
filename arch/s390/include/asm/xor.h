<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Optimited xor routines
 *
 * Copyright IBM Corp. 2016
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */
#अगर_अघोषित _ASM_S390_XOR_H
#घोषणा _ASM_S390_XOR_H

बाह्य काष्ठा xor_block_ढाँचा xor_block_xc;

#अघोषित XOR_TRY_TEMPLATES
#घोषणा XOR_TRY_TEMPLATES				\
करो अणु							\
	xor_speed(&xor_block_xc);			\
पूर्ण जबतक (0)

#घोषणा XOR_SELECT_TEMPLATE(FASTEST)	(&xor_block_xc)

#पूर्ण_अगर /* _ASM_S390_XOR_H */
