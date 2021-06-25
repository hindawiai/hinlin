<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC64_PSTATE_H
#घोषणा _SPARC64_PSTATE_H

#समावेश <linux/स्थिर.h>

/* The V9 PSTATE Register (with SpitFire extensions).
 *
 * -----------------------------------------------------------------------
 * | Resv | IG | MG | CLE | TLE |  MM  | RED | PEF | AM | PRIV | IE | AG |
 * -----------------------------------------------------------------------
 *  63  12  11   10    9     8    7   6   5     4     3     2     1    0
 */
/* IG on V9 conflicts with MCDE on M7. PSTATE_MCDE will only be used on
 * processors that support ADI which करो not use IG, hence there is no
 * functional conflict
 */
#घोषणा PSTATE_IG   _AC(0x0000000000000800,UL) /* Interrupt Globals.	*/
#घोषणा PSTATE_MCDE _AC(0x0000000000000800,UL) /* MCD Enable		*/
#घोषणा PSTATE_MG   _AC(0x0000000000000400,UL) /* MMU Globals.		*/
#घोषणा PSTATE_CLE  _AC(0x0000000000000200,UL) /* Current Little Endian.*/
#घोषणा PSTATE_TLE  _AC(0x0000000000000100,UL) /* Trap Little Endian.	*/
#घोषणा PSTATE_MM   _AC(0x00000000000000c0,UL) /* Memory Model.		*/
#घोषणा PSTATE_TSO  _AC(0x0000000000000000,UL) /* MM: TotalStoreOrder	*/
#घोषणा PSTATE_PSO  _AC(0x0000000000000040,UL) /* MM: PartialStoreOrder	*/
#घोषणा PSTATE_RMO  _AC(0x0000000000000080,UL) /* MM: RelaxedMemoryOrder*/
#घोषणा PSTATE_RED  _AC(0x0000000000000020,UL) /* Reset Error Debug.	*/
#घोषणा PSTATE_PEF  _AC(0x0000000000000010,UL) /* Floating Poपूर्णांक Enable.*/
#घोषणा PSTATE_AM   _AC(0x0000000000000008,UL) /* Address Mask.		*/
#घोषणा PSTATE_PRIV _AC(0x0000000000000004,UL) /* Privilege.		*/
#घोषणा PSTATE_IE   _AC(0x0000000000000002,UL) /* Interrupt Enable.	*/
#घोषणा PSTATE_AG   _AC(0x0000000000000001,UL) /* Alternate Globals.	*/

/* The V9 TSTATE Register (with SpitFire and Linux extensions).
 *
 * ---------------------------------------------------------------------
 * |  Resv |  GL  |  CCR  |  ASI  |  %pil  |  PSTATE  |  Resv  |  CWP  |
 * ---------------------------------------------------------------------
 *  63   43 42  40 39   32 31   24 23    20 19       8 7      5 4     0
 */
#घोषणा TSTATE_GL	_AC(0x0000070000000000,UL) /* Global reg level  */
#घोषणा TSTATE_CCR	_AC(0x000000ff00000000,UL) /* Condition Codes.	*/
#घोषणा TSTATE_XCC	_AC(0x000000f000000000,UL) /* Condition Codes.	*/
#घोषणा TSTATE_XNEG	_AC(0x0000008000000000,UL) /* %xcc Negative.	*/
#घोषणा TSTATE_XZERO	_AC(0x0000004000000000,UL) /* %xcc Zero.	*/
#घोषणा TSTATE_XOVFL	_AC(0x0000002000000000,UL) /* %xcc Overflow.	*/
#घोषणा TSTATE_XCARRY	_AC(0x0000001000000000,UL) /* %xcc Carry.	*/
#घोषणा TSTATE_ICC	_AC(0x0000000f00000000,UL) /* Condition Codes.	*/
#घोषणा TSTATE_INEG	_AC(0x0000000800000000,UL) /* %icc Negative.	*/
#घोषणा TSTATE_IZERO	_AC(0x0000000400000000,UL) /* %icc Zero.	*/
#घोषणा TSTATE_IOVFL	_AC(0x0000000200000000,UL) /* %icc Overflow.	*/
#घोषणा TSTATE_ICARRY	_AC(0x0000000100000000,UL) /* %icc Carry.	*/
#घोषणा TSTATE_ASI	_AC(0x00000000ff000000,UL) /* AddrSpace ID.	*/
#घोषणा TSTATE_PIL	_AC(0x0000000000f00000,UL) /* %pil (Linux traps)*/
#घोषणा TSTATE_PSTATE	_AC(0x00000000000fff00,UL) /* PSTATE.		*/
/* IG on V9 conflicts with MCDE on M7. TSTATE_MCDE will only be used on
 * processors that support ADI which करो not support IG, hence there is
 * no functional conflict
 */
#घोषणा TSTATE_IG	_AC(0x0000000000080000,UL) /* Interrupt Globals.*/
#घोषणा TSTATE_MCDE	_AC(0x0000000000080000,UL) /* MCD enable.       */
#घोषणा TSTATE_MG	_AC(0x0000000000040000,UL) /* MMU Globals.	*/
#घोषणा TSTATE_CLE	_AC(0x0000000000020000,UL) /* CurrLittleEndian.	*/
#घोषणा TSTATE_TLE	_AC(0x0000000000010000,UL) /* TrapLittleEndian.	*/
#घोषणा TSTATE_MM	_AC(0x000000000000c000,UL) /* Memory Model.	*/
#घोषणा TSTATE_TSO	_AC(0x0000000000000000,UL) /* MM: TSO		*/
#घोषणा TSTATE_PSO	_AC(0x0000000000004000,UL) /* MM: PSO		*/
#घोषणा TSTATE_RMO	_AC(0x0000000000008000,UL) /* MM: RMO		*/
#घोषणा TSTATE_RED	_AC(0x0000000000002000,UL) /* Reset Error Debug.*/
#घोषणा TSTATE_PEF	_AC(0x0000000000001000,UL) /* FPU Enable.	*/
#घोषणा TSTATE_AM	_AC(0x0000000000000800,UL) /* Address Mask.	*/
#घोषणा TSTATE_PRIV	_AC(0x0000000000000400,UL) /* Privilege.	*/
#घोषणा TSTATE_IE	_AC(0x0000000000000200,UL) /* Interrupt Enable.	*/
#घोषणा TSTATE_AG	_AC(0x0000000000000100,UL) /* Alternate Globals.*/
#घोषणा TSTATE_SYSCALL	_AC(0x0000000000000020,UL) /* in syscall trap   */
#घोषणा TSTATE_CWP	_AC(0x000000000000001f,UL) /* Curr Win-Poपूर्णांकer.	*/

/* Floating-Poपूर्णांक Registers State Register.
 *
 * --------------------------------
 * |  Resv  |  FEF  |  DU  |  DL  |
 * --------------------------------
 *  63     3    2       1      0
 */
#घोषणा FPRS_FEF	_AC(0x0000000000000004,UL) /* FPU Enable.	*/
#घोषणा FPRS_DU		_AC(0x0000000000000002,UL) /* Dirty Upper.	*/
#घोषणा FPRS_DL		_AC(0x0000000000000001,UL) /* Dirty Lower.	*/

/* Version Register.
 *
 * ------------------------------------------------------
 * | MANUF | IMPL | MASK | Resv | MAXTL | Resv | MAXWIN |
 * ------------------------------------------------------
 *  63   48 47  32 31  24 23  16 15    8 7    5 4      0
 */
#घोषणा VERS_MANUF	_AC(0xffff000000000000,UL) /* Manufacturer.	*/
#घोषणा VERS_IMPL	_AC(0x0000ffff00000000,UL) /* Implementation.	*/
#घोषणा VERS_MASK	_AC(0x00000000ff000000,UL) /* Mask Set Revision.*/
#घोषणा VERS_MAXTL	_AC(0x000000000000ff00,UL) /* Max Trap Level.	*/
#घोषणा VERS_MAXWIN	_AC(0x000000000000001f,UL) /* Max RegWinकरोw Idx.*/

/* Compatibility Feature Register (%asr26), SPARC-T4 and later  */
#घोषणा CFR_AES		_AC(0x0000000000000001,UL) /* Supports AES opcodes     */
#घोषणा CFR_DES		_AC(0x0000000000000002,UL) /* Supports DES opcodes     */
#घोषणा CFR_KASUMI	_AC(0x0000000000000004,UL) /* Supports KASUMI opcodes  */
#घोषणा CFR_CAMELLIA	_AC(0x0000000000000008,UL) /* Supports CAMELLIA opcodes*/
#घोषणा CFR_MD5		_AC(0x0000000000000010,UL) /* Supports MD5 opcodes     */
#घोषणा CFR_SHA1	_AC(0x0000000000000020,UL) /* Supports SHA1 opcodes    */
#घोषणा CFR_SHA256	_AC(0x0000000000000040,UL) /* Supports SHA256 opcodes  */
#घोषणा CFR_SHA512	_AC(0x0000000000000080,UL) /* Supports SHA512 opcodes  */
#घोषणा CFR_MPMUL	_AC(0x0000000000000100,UL) /* Supports MPMUL opcodes   */
#घोषणा CFR_MONTMUL	_AC(0x0000000000000200,UL) /* Supports MONTMUL opcodes */
#घोषणा CFR_MONTSQR	_AC(0x0000000000000400,UL) /* Supports MONTSQR opcodes */
#घोषणा CFR_CRC32C	_AC(0x0000000000000800,UL) /* Supports CRC32C opcodes  */

#पूर्ण_अगर /* !(_SPARC64_PSTATE_H) */
