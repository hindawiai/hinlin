<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC64_PSRCOMPAT_H
#घोषणा _SPARC64_PSRCOMPAT_H

#समावेश <यंत्र/pstate.h>

/* Old 32-bit PSR fields क्रम the compatibility conversion code. */
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

#घोषणा PSR_V8PLUS  0xff000000         /* fake impl/ver, meaning a 64bit CPU is present */
#घोषणा PSR_XCC	    0x000f0000         /* अगर PSR_V8PLUS, this is %xcc */

अटल अंतरभूत अचिन्हित पूर्णांक tstate_to_psr(अचिन्हित दीर्घ tstate)
अणु
	वापस ((tstate & TSTATE_CWP)			|
		PSR_S					|
		((tstate & TSTATE_ICC) >> 12)		|
		((tstate & TSTATE_XCC) >> 20)		|
		((tstate & TSTATE_SYSCALL) ? PSR_SYSCALL : 0) |
		PSR_V8PLUS);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ psr_to_tstate_icc(अचिन्हित पूर्णांक psr)
अणु
	अचिन्हित दीर्घ tstate = ((अचिन्हित दीर्घ)(psr & PSR_ICC)) << 12;
	अगर ((psr & (PSR_VERS|PSR_IMPL)) == PSR_V8PLUS)
		tstate |= ((अचिन्हित दीर्घ)(psr & PSR_XCC)) << 20;
	वापस tstate;
पूर्ण

#पूर्ण_अगर /* !(_SPARC64_PSRCOMPAT_H) */
