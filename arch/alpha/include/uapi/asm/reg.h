<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __reg_h__
#घोषणा __reg_h__

/*
 * Exception frame offsets.
 */
#घोषणा EF_V0		0
#घोषणा EF_T0		1
#घोषणा EF_T1		2
#घोषणा EF_T2		3
#घोषणा EF_T3		4
#घोषणा EF_T4		5
#घोषणा EF_T5		6
#घोषणा EF_T6		7
#घोषणा EF_T7		8
#घोषणा EF_S0		9
#घोषणा EF_S1		10
#घोषणा EF_S2		11
#घोषणा EF_S3		12
#घोषणा EF_S4		13
#घोषणा EF_S5		14
#घोषणा EF_S6		15
#घोषणा EF_A3		16
#घोषणा EF_A4		17
#घोषणा EF_A5		18
#घोषणा EF_T8		19
#घोषणा EF_T9		20
#घोषणा EF_T10		21
#घोषणा EF_T11		22
#घोषणा EF_RA		23
#घोषणा EF_T12		24
#घोषणा EF_AT		25
#घोषणा EF_SP		26
#घोषणा EF_PS		27
#घोषणा EF_PC		28
#घोषणा EF_GP		29
#घोषणा EF_A0		30
#घोषणा EF_A1		31
#घोषणा EF_A2		32

#घोषणा EF_SIZE		(33*8)
#घोषणा HWEF_SIZE	(6*8)		/* size of PAL frame (PS-A2) */

#घोषणा EF_SSIZE	(EF_SIZE - HWEF_SIZE)

/*
 * Map रेजिस्टर number पूर्णांकo core file offset.
 */
#घोषणा CORE_REG(reg, ubase) \
	(((अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)(ubase)))[reg])

#पूर्ण_अगर /* __reg_h__ */
