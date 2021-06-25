<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * psr.h: This file holds the macros क्रम masking off various parts of
 *        the processor status रेजिस्टर on the Sparc. This is valid
 *        क्रम Version 8. On the V9 this is नामd to the PSTATE
 *        रेजिस्टर and its members are accessed as fields like
 *        PSTATE.PRIV क्रम the current CPU privilege level.
 *
 * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)
 */

#अगर_अघोषित _UAPI__LINUX_SPARC_PSR_H
#घोषणा _UAPI__LINUX_SPARC_PSR_H

/* The Sparc PSR fields are laid out as the following:
 *
 *  ------------------------------------------------------------------------
 *  | impl  | vers  | icc   | resv  | EC | EF | PIL  | S | PS | ET |  CWP  |
 *  | 31-28 | 27-24 | 23-20 | 19-14 | 13 | 12 | 11-8 | 7 | 6  | 5  |  4-0  |
 *  ------------------------------------------------------------------------
 */
#घोषणा PSR_CWP     0x0000001f         /* current winकरोw poपूर्णांकer     */
#घोषणा PSR_ET      0x00000020         /* enable traps field         */
#घोषणा PSR_PS      0x00000040         /* previous privilege level   */
#घोषणा PSR_S       0x00000080         /* current privilege level    */
#घोषणा PSR_PIL     0x00000f00         /* processor पूर्णांकerrupt level  */
#घोषणा PSR_EF      0x00001000         /* enable भग्नing poपूर्णांक      */
#घोषणा PSR_EC      0x00002000         /* enable co-processor        */
#घोषणा PSR_SYSCALL 0x00004000         /* inside of a syscall        */
#घोषणा PSR_LE      0x00008000         /* SuperSparcII little-endian */
#घोषणा PSR_ICC     0x00f00000         /* पूर्णांकeger condition codes    */
#घोषणा PSR_C       0x00100000         /* carry bit                  */
#घोषणा PSR_V       0x00200000         /* overflow bit               */
#घोषणा PSR_Z       0x00400000         /* zero bit                   */
#घोषणा PSR_N       0x00800000         /* negative bit               */
#घोषणा PSR_VERS    0x0f000000         /* cpu-version field          */
#घोषणा PSR_IMPL    0xf0000000         /* cpu-implementation field   */

#घोषणा PSR_VERS_SHIFT		24
#घोषणा PSR_IMPL_SHIFT		28
#घोषणा PSR_VERS_SHIFTED_MASK	0xf
#घोषणा PSR_IMPL_SHIFTED_MASK	0xf

#घोषणा PSR_IMPL_TI		0x4
#घोषणा PSR_IMPL_LEON		0xf


#पूर्ण_अगर /* _UAPI__LINUX_SPARC_PSR_H */
