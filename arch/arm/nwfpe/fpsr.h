<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    NetWinder Floating Poपूर्णांक Emulator
    (c) Rebel.com, 1998-1999

    Direct questions, comments to Scott Bambrough <scottb@netwinder.org>

*/

#अगर_अघोषित __FPSR_H__
#घोषणा __FPSR_H__

/*
The FPSR is a 32 bit रेजिस्टर consisting of 4 parts, each exactly
one byte.

	SYSTEM ID
	EXCEPTION TRAP ENABLE BYTE
	SYSTEM CONTROL BYTE
	CUMULATIVE EXCEPTION FLAGS BYTE

The FPCR is a 32 bit रेजिस्टर consisting of bit flags.
*/

/* SYSTEM ID
------------
Note: the प्रणाली id byte is पढ़ो only  */

प्रकार अचिन्हित पूर्णांक FPSR;	/* type क्रम भग्नing poपूर्णांक status रेजिस्टर */
प्रकार अचिन्हित पूर्णांक FPCR;	/* type क्रम भग्नing poपूर्णांक control रेजिस्टर */

#घोषणा MASK_SYSID		0xff000000
#घोषणा BIT_HARDWARE		0x80000000
#घोषणा FP_EMULATOR		0x01000000	/* System ID क्रम emulator */
#घोषणा FP_ACCELERATOR		0x81000000	/* System ID क्रम FPA11 */

/* EXCEPTION TRAP ENABLE BYTE
----------------------------- */

#घोषणा MASK_TRAP_ENABLE	0x00ff0000
#घोषणा MASK_TRAP_ENABLE_STRICT	0x001f0000
#घोषणा BIT_IXE		0x00100000	/* inexact exception enable */
#घोषणा BIT_UFE		0x00080000	/* underflow exception enable */
#घोषणा BIT_OFE		0x00040000	/* overflow exception enable */
#घोषणा BIT_DZE		0x00020000	/* भागide by zero exception enable */
#घोषणा BIT_IOE		0x00010000	/* invalid operation exception enable */

/* SYSTEM CONTROL BYTE
---------------------- */

#घोषणा MASK_SYSTEM_CONTROL	0x0000ff00
#घोषणा MASK_TRAP_STRICT	0x00001f00

#घोषणा BIT_AC	0x00001000	/* use alternative C-flag definition
				   क्रम compares */
#घोषणा BIT_EP	0x00000800	/* use expanded packed decimal क्रमmat */
#घोषणा BIT_SO	0x00000400	/* select synchronous operation of FPA */
#घोषणा BIT_NE	0x00000200	/* NaN exception bit */
#घोषणा BIT_ND	0x00000100	/* no denormalized numbers bit */

/* CUMULATIVE EXCEPTION FLAGS BYTE
---------------------------------- */

#घोषणा MASK_EXCEPTION_FLAGS		0x000000ff
#घोषणा MASK_EXCEPTION_FLAGS_STRICT	0x0000001f

#घोषणा BIT_IXC		0x00000010	/* inexact exception flag */
#घोषणा BIT_UFC		0x00000008	/* underflow exception flag */
#घोषणा BIT_OFC		0x00000004	/* overभग्न exception flag */
#घोषणा BIT_DZC		0x00000002	/* भागide by zero exception flag */
#घोषणा BIT_IOC		0x00000001	/* invalid operation exception flag */

/* Floating Poपूर्णांक Control Register
----------------------------------*/

#घोषणा BIT_RU		0x80000000	/* rounded up bit */
#घोषणा BIT_IE		0x10000000	/* inexact bit */
#घोषणा BIT_MO		0x08000000	/* mantissa overflow bit */
#घोषणा BIT_EO		0x04000000	/* exponent overflow bit */
#घोषणा BIT_SB		0x00000800	/* store bounce */
#घोषणा BIT_AB		0x00000400	/* arithmetic bounce */
#घोषणा BIT_RE		0x00000200	/* rounding exception */
#घोषणा BIT_DA		0x00000100	/* disable FPA */

#घोषणा MASK_OP		0x00f08010	/* AU operation code */
#घोषणा MASK_PR		0x00080080	/* AU precision */
#घोषणा MASK_S1		0x00070000	/* AU source रेजिस्टर 1 */
#घोषणा MASK_S2		0x00000007	/* AU source रेजिस्टर 2 */
#घोषणा MASK_DS		0x00007000	/* AU destination रेजिस्टर */
#घोषणा MASK_RM		0x00000060	/* AU rounding mode */
#घोषणा MASK_ALU	0x9cfff2ff	/* only ALU can ग_लिखो these bits */
#घोषणा MASK_RESET	0x00000d00	/* bits set on reset, all others cleared */
#घोषणा MASK_WFC	MASK_RESET
#घोषणा MASK_RFC	~MASK_RESET

#पूर्ण_अगर
