<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __SYSDEP_H
#घोषणा __SYSDEP_H

#अगर_घोषित __ASSEMBLER__

#अगर defined(__CK860__)
#घोषणा LABLE_ALIGN	\
	.balignw 16, 0x6c03

#घोषणा PRE_BNEZAD(R)

#घोषणा BNEZAD(R, L)	\
	bnezad	R, L
#अन्यथा
#घोषणा LABLE_ALIGN	\
	.balignw 8, 0x6c03

#घोषणा PRE_BNEZAD(R)	\
	subi	R, 1

#घोषणा BNEZAD(R, L)	\
	bnez	R, L
#पूर्ण_अगर

#पूर्ण_अगर

#पूर्ण_अगर
