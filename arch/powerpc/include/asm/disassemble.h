<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright IBM Corp. 2008
 *
 * Authors: Hollis Blanअक्षरd <hollisb@us.ibm.com>
 */

#अगर_अघोषित __ASM_PPC_DISASSEMBLE_H__
#घोषणा __ASM_PPC_DISASSEMBLE_H__

#समावेश <linux/types.h>

अटल अंतरभूत अचिन्हित पूर्णांक get_op(u32 inst)
अणु
	वापस inst >> 26;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_xop(u32 inst)
अणु
	वापस (inst >> 1) & 0x3ff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_sprn(u32 inst)
अणु
	वापस ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_dcrn(u32 inst)
अणु
	वापस ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_पंचांगrn(u32 inst)
अणु
	वापस ((inst >> 16) & 0x1f) | ((inst >> 6) & 0x3e0);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_rt(u32 inst)
अणु
	वापस (inst >> 21) & 0x1f;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_rs(u32 inst)
अणु
	वापस (inst >> 21) & 0x1f;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_ra(u32 inst)
अणु
	वापस (inst >> 16) & 0x1f;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_rb(u32 inst)
अणु
	वापस (inst >> 11) & 0x1f;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_rc(u32 inst)
अणु
	वापस inst & 0x1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_ws(u32 inst)
अणु
	वापस (inst >> 11) & 0x1f;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_d(u32 inst)
अणु
	वापस inst & 0xffff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_oc(u32 inst)
अणु
	वापस (inst >> 11) & 0x7fff;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक get_tx_or_sx(u32 inst)
अणु
	वापस (inst) & 0x1;
पूर्ण

#घोषणा IS_XFORM(inst)	(get_op(inst)  == 31)
#घोषणा IS_DSFORM(inst)	(get_op(inst) >= 56)

/*
 * Create a DSISR value from the inकाष्ठाion
 */
अटल अंतरभूत अचिन्हित make_dsisr(अचिन्हित instr)
अणु
	अचिन्हित dsisr;


	/* bits  6:15 --> 22:31 */
	dsisr = (instr & 0x03ff0000) >> 16;

	अगर (IS_XFORM(instr)) अणु
		/* bits 29:30 --> 15:16 */
		dsisr |= (instr & 0x00000006) << 14;
		/* bit     25 -->    17 */
		dsisr |= (instr & 0x00000040) << 8;
		/* bits 21:24 --> 18:21 */
		dsisr |= (instr & 0x00000780) << 3;
	पूर्ण अन्यथा अणु
		/* bit      5 -->    17 */
		dsisr |= (instr & 0x04000000) >> 12;
		/* bits  1: 4 --> 18:21 */
		dsisr |= (instr & 0x78000000) >> 17;
		/* bits 30:31 --> 12:13 */
		अगर (IS_DSFORM(instr))
			dsisr |= (instr & 0x00000003) << 18;
	पूर्ण

	वापस dsisr;
पूर्ण
#पूर्ण_अगर /* __ASM_PPC_DISASSEMBLE_H__ */
