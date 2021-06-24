<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/kernel/opcodes.c
 *
 *  A32 condition code lookup feature moved from nwfpe/fpopcode.c
 */

#समावेश <linux/module.h>
#समावेश <यंत्र/opcodes.h>

#घोषणा ARM_OPCODE_CONDITION_UNCOND 0xf

/*
 * condition code lookup table
 * index पूर्णांकo the table is test code: EQ, NE, ... LT, GT, AL, NV
 *
 * bit position in लघु is condition code: NZCV
 */
अटल स्थिर अचिन्हित लघु cc_map[16] = अणु
	0xF0F0,			/* EQ == Z set            */
	0x0F0F,			/* NE                     */
	0xCCCC,			/* CS == C set            */
	0x3333,			/* CC                     */
	0xFF00,			/* MI == N set            */
	0x00FF,			/* PL                     */
	0xAAAA,			/* VS == V set            */
	0x5555,			/* VC                     */
	0x0C0C,			/* HI == C set && Z clear */
	0xF3F3,			/* LS == C clear || Z set */
	0xAA55,			/* GE == (N==V)           */
	0x55AA,			/* LT == (N!=V)           */
	0x0A05,			/* GT == (!Z && (N==V))   */
	0xF5FA,			/* LE == (Z || (N!=V))    */
	0xFFFF,			/* AL always              */
	0			/* NV                     */
पूर्ण;

/*
 * Returns:
 * ARM_OPCODE_CONDTEST_FAIL   - अगर condition fails
 * ARM_OPCODE_CONDTEST_PASS   - अगर condition passes (including AL)
 * ARM_OPCODE_CONDTEST_UNCOND - अगर NV condition, or separate unconditional
 *                              opcode space from v5 onwards
 *
 * Code that tests whether a conditional inकाष्ठाion would pass its condition
 * check should check that वापस value == ARM_OPCODE_CONDTEST_PASS.
 *
 * Code that tests अगर a condition means that the inकाष्ठाion would be executed
 * (regardless of conditional or unconditional) should instead check that the
 * वापस value != ARM_OPCODE_CONDTEST_FAIL.
 */
यंत्रlinkage अचिन्हित पूर्णांक arm_check_condition(u32 opcode, u32 psr)
अणु
	u32 cc_bits  = opcode >> 28;
	u32 psr_cond = psr >> 28;
	अचिन्हित पूर्णांक ret;

	अगर (cc_bits != ARM_OPCODE_CONDITION_UNCOND) अणु
		अगर ((cc_map[cc_bits] >> (psr_cond)) & 1)
			ret = ARM_OPCODE_CONDTEST_PASS;
		अन्यथा
			ret = ARM_OPCODE_CONDTEST_FAIL;
	पूर्ण अन्यथा अणु
		ret = ARM_OPCODE_CONDTEST_UNCOND;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(arm_check_condition);
