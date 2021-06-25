<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* visemul.c: Emulation of VIS inकाष्ठाions.
 *
 * Copyright (C) 2006 David S. Miller (davem@davemloft.net)
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/pstate.h>
#समावेश <यंत्र/fpumacro.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

/* OPF field of various VIS inकाष्ठाions.  */

/* 000111011 - four 16-bit packs  */
#घोषणा FPACK16_OPF	0x03b

/* 000111010 - two 32-bit packs  */
#घोषणा FPACK32_OPF	0x03a

/* 000111101 - four 16-bit packs  */
#घोषणा FPACKFIX_OPF	0x03d

/* 001001101 - four 16-bit expands  */
#घोषणा FEXPAND_OPF	0x04d

/* 001001011 - two 32-bit merges */
#घोषणा FPMERGE_OPF	0x04b

/* 000110001 - 8-by-16-bit partitioned product  */
#घोषणा FMUL8x16_OPF	0x031

/* 000110011 - 8-by-16-bit upper alpha partitioned product  */
#घोषणा FMUL8x16AU_OPF	0x033

/* 000110101 - 8-by-16-bit lower alpha partitioned product  */
#घोषणा FMUL8x16AL_OPF	0x035

/* 000110110 - upper 8-by-16-bit partitioned product  */
#घोषणा FMUL8SUx16_OPF	0x036

/* 000110111 - lower 8-by-16-bit partitioned product  */
#घोषणा FMUL8ULx16_OPF	0x037

/* 000111000 - upper 8-by-16-bit partitioned product  */
#घोषणा FMULD8SUx16_OPF	0x038

/* 000111001 - lower अचिन्हित 8-by-16-bit partitioned product  */
#घोषणा FMULD8ULx16_OPF	0x039

/* 000101000 - four 16-bit compare; set rd अगर src1 > src2  */
#घोषणा FCMPGT16_OPF	0x028

/* 000101100 - two 32-bit compare; set rd अगर src1 > src2  */
#घोषणा FCMPGT32_OPF	0x02c

/* 000100000 - four 16-bit compare; set rd अगर src1 <= src2  */
#घोषणा FCMPLE16_OPF	0x020

/* 000100100 - two 32-bit compare; set rd अगर src1 <= src2  */
#घोषणा FCMPLE32_OPF	0x024

/* 000100010 - four 16-bit compare; set rd अगर src1 != src2  */
#घोषणा FCMPNE16_OPF	0x022

/* 000100110 - two 32-bit compare; set rd अगर src1 != src2  */
#घोषणा FCMPNE32_OPF	0x026

/* 000101010 - four 16-bit compare; set rd अगर src1 == src2  */
#घोषणा FCMPEQ16_OPF	0x02a

/* 000101110 - two 32-bit compare; set rd अगर src1 == src2  */
#घोषणा FCMPEQ32_OPF	0x02e

/* 000000000 - Eight 8-bit edge boundary processing  */
#घोषणा EDGE8_OPF	0x000

/* 000000001 - Eight 8-bit edge boundary processing, no CC */
#घोषणा EDGE8N_OPF	0x001

/* 000000010 - Eight 8-bit edge boundary processing, little-endian  */
#घोषणा EDGE8L_OPF	0x002

/* 000000011 - Eight 8-bit edge boundary processing, little-endian, no CC  */
#घोषणा EDGE8LN_OPF	0x003

/* 000000100 - Four 16-bit edge boundary processing  */
#घोषणा EDGE16_OPF	0x004

/* 000000101 - Four 16-bit edge boundary processing, no CC  */
#घोषणा EDGE16N_OPF	0x005

/* 000000110 - Four 16-bit edge boundary processing, little-endian  */
#घोषणा EDGE16L_OPF	0x006

/* 000000111 - Four 16-bit edge boundary processing, little-endian, no CC  */
#घोषणा EDGE16LN_OPF	0x007

/* 000001000 - Two 32-bit edge boundary processing  */
#घोषणा EDGE32_OPF	0x008

/* 000001001 - Two 32-bit edge boundary processing, no CC  */
#घोषणा EDGE32N_OPF	0x009

/* 000001010 - Two 32-bit edge boundary processing, little-endian  */
#घोषणा EDGE32L_OPF	0x00a

/* 000001011 - Two 32-bit edge boundary processing, little-endian, no CC  */
#घोषणा EDGE32LN_OPF	0x00b

/* 000111110 - distance between 8 8-bit components  */
#घोषणा PDIST_OPF	0x03e

/* 000010000 - convert 8-bit 3-D address to blocked byte address  */
#घोषणा ARRAY8_OPF	0x010

/* 000010010 - convert 16-bit 3-D address to blocked byte address  */
#घोषणा ARRAY16_OPF	0x012

/* 000010100 - convert 32-bit 3-D address to blocked byte address  */
#घोषणा ARRAY32_OPF	0x014

/* 000011001 - Set the GSR.MASK field in preparation क्रम a BSHUFFLE  */
#घोषणा BMASK_OPF	0x019

/* 001001100 - Permute bytes as specअगरied by GSR.MASK  */
#घोषणा BSHUFFLE_OPF	0x04c

#घोषणा VIS_OPF_SHIFT	5
#घोषणा VIS_OPF_MASK	(0x1ff << VIS_OPF_SHIFT)

#घोषणा RS1(INSN)	(((INSN) >> 14) & 0x1f)
#घोषणा RS2(INSN)	(((INSN) >>  0) & 0x1f)
#घोषणा RD(INSN)	(((INSN) >> 25) & 0x1f)

अटल अंतरभूत व्योम maybe_flush_winकरोws(अचिन्हित पूर्णांक rs1, अचिन्हित पूर्णांक rs2,
				       अचिन्हित पूर्णांक rd, पूर्णांक from_kernel)
अणु
	अगर (rs2 >= 16 || rs1 >= 16 || rd >= 16) अणु
		अगर (from_kernel != 0)
			__यंत्र__ __अस्थिर__("flushw");
		अन्यथा
			flushw_user();
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ fetch_reg(अचिन्हित पूर्णांक reg, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ value, fp;
	
	अगर (reg < 16)
		वापस (!reg ? 0 : regs->u_regs[reg]);

	fp = regs->u_regs[UREG_FP];

	अगर (regs->tstate & TSTATE_PRIV) अणु
		काष्ठा reg_winकरोw *win;
		win = (काष्ठा reg_winकरोw *)(fp + STACK_BIAS);
		value = win->locals[reg - 16];
	पूर्ण अन्यथा अगर (!test_thपढ़ो_64bit_stack(fp)) अणु
		काष्ठा reg_winकरोw32 __user *win32;
		win32 = (काष्ठा reg_winकरोw32 __user *)((अचिन्हित दीर्घ)((u32)fp));
		get_user(value, &win32->locals[reg - 16]);
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw __user *win;
		win = (काष्ठा reg_winकरोw __user *)(fp + STACK_BIAS);
		get_user(value, &win->locals[reg - 16]);
	पूर्ण
	वापस value;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __user *__fetch_reg_addr_user(अचिन्हित पूर्णांक reg,
							  काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fp = regs->u_regs[UREG_FP];

	BUG_ON(reg < 16);
	BUG_ON(regs->tstate & TSTATE_PRIV);

	अगर (!test_thपढ़ो_64bit_stack(fp)) अणु
		काष्ठा reg_winकरोw32 __user *win32;
		win32 = (काष्ठा reg_winकरोw32 __user *)((अचिन्हित दीर्घ)((u32)fp));
		वापस (अचिन्हित दीर्घ __user *)&win32->locals[reg - 16];
	पूर्ण अन्यथा अणु
		काष्ठा reg_winकरोw __user *win;
		win = (काष्ठा reg_winकरोw __user *)(fp + STACK_BIAS);
		वापस &win->locals[reg - 16];
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *__fetch_reg_addr_kern(अचिन्हित पूर्णांक reg,
						   काष्ठा pt_regs *regs)
अणु
	BUG_ON(reg >= 16);
	BUG_ON(regs->tstate & TSTATE_PRIV);

	वापस &regs->u_regs[reg];
पूर्ण

अटल व्योम store_reg(काष्ठा pt_regs *regs, अचिन्हित दीर्घ val, अचिन्हित दीर्घ rd)
अणु
	अगर (rd < 16) अणु
		अचिन्हित दीर्घ *rd_kern = __fetch_reg_addr_kern(rd, regs);

		*rd_kern = val;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ __user *rd_user = __fetch_reg_addr_user(rd, regs);

		अगर (!test_thपढ़ो_64bit_stack(regs->u_regs[UREG_FP]))
			__put_user((u32)val, (u32 __user *)rd_user);
		अन्यथा
			__put_user(val, rd_user);
	पूर्ण
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ fpd_regval(काष्ठा fpustate *f,
				       अचिन्हित पूर्णांक insn_regnum)
अणु
	insn_regnum = (((insn_regnum & 1) << 5) |
		       (insn_regnum & 0x1e));

	वापस *(अचिन्हित दीर्घ *) &f->regs[insn_regnum];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ *fpd_regaddr(काष्ठा fpustate *f,
					 अचिन्हित पूर्णांक insn_regnum)
अणु
	insn_regnum = (((insn_regnum & 1) << 5) |
		       (insn_regnum & 0x1e));

	वापस (अचिन्हित दीर्घ *) &f->regs[insn_regnum];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fps_regval(काष्ठा fpustate *f,
				      अचिन्हित पूर्णांक insn_regnum)
अणु
	वापस f->regs[insn_regnum];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक *fps_regaddr(काष्ठा fpustate *f,
					अचिन्हित पूर्णांक insn_regnum)
अणु
	वापस &f->regs[insn_regnum];
पूर्ण

काष्ठा edge_tab अणु
	u16 left, right;
पूर्ण;
अटल काष्ठा edge_tab edge8_tab[8] = अणु
	अणु 0xff, 0x80 पूर्ण,
	अणु 0x7f, 0xc0 पूर्ण,
	अणु 0x3f, 0xe0 पूर्ण,
	अणु 0x1f, 0xf0 पूर्ण,
	अणु 0x0f, 0xf8 पूर्ण,
	अणु 0x07, 0xfc पूर्ण,
	अणु 0x03, 0xfe पूर्ण,
	अणु 0x01, 0xff पूर्ण,
पूर्ण;
अटल काष्ठा edge_tab edge8_tab_l[8] = अणु
	अणु 0xff, 0x01 पूर्ण,
	अणु 0xfe, 0x03 पूर्ण,
	अणु 0xfc, 0x07 पूर्ण,
	अणु 0xf8, 0x0f पूर्ण,
	अणु 0xf0, 0x1f पूर्ण,
	अणु 0xe0, 0x3f पूर्ण,
	अणु 0xc0, 0x7f पूर्ण,
	अणु 0x80, 0xff पूर्ण,
पूर्ण;
अटल काष्ठा edge_tab edge16_tab[4] = अणु
	अणु 0xf, 0x8 पूर्ण,
	अणु 0x7, 0xc पूर्ण,
	अणु 0x3, 0xe पूर्ण,
	अणु 0x1, 0xf पूर्ण,
पूर्ण;
अटल काष्ठा edge_tab edge16_tab_l[4] = अणु
	अणु 0xf, 0x1 पूर्ण,
	अणु 0xe, 0x3 पूर्ण,
	अणु 0xc, 0x7 पूर्ण,
	अणु 0x8, 0xf पूर्ण,
पूर्ण;
अटल काष्ठा edge_tab edge32_tab[2] = अणु
	अणु 0x3, 0x2 पूर्ण,
	अणु 0x1, 0x3 पूर्ण,
पूर्ण;
अटल काष्ठा edge_tab edge32_tab_l[2] = अणु
	अणु 0x3, 0x1 पूर्ण,
	अणु 0x2, 0x3 पूर्ण,
पूर्ण;

अटल व्योम edge(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक opf)
अणु
	अचिन्हित दीर्घ orig_rs1, rs1, orig_rs2, rs2, rd_val;
	u16 left, right;

	maybe_flush_winकरोws(RS1(insn), RS2(insn), RD(insn), 0);
	orig_rs1 = rs1 = fetch_reg(RS1(insn), regs);
	orig_rs2 = rs2 = fetch_reg(RS2(insn), regs);

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		rs1 = rs1 & 0xffffffff;
		rs2 = rs2 & 0xffffffff;
	पूर्ण
	चयन (opf) अणु
	शेष:
	हाल EDGE8_OPF:
	हाल EDGE8N_OPF:
		left = edge8_tab[rs1 & 0x7].left;
		right = edge8_tab[rs2 & 0x7].right;
		अवरोध;
	हाल EDGE8L_OPF:
	हाल EDGE8LN_OPF:
		left = edge8_tab_l[rs1 & 0x7].left;
		right = edge8_tab_l[rs2 & 0x7].right;
		अवरोध;

	हाल EDGE16_OPF:
	हाल EDGE16N_OPF:
		left = edge16_tab[(rs1 >> 1) & 0x3].left;
		right = edge16_tab[(rs2 >> 1) & 0x3].right;
		अवरोध;

	हाल EDGE16L_OPF:
	हाल EDGE16LN_OPF:
		left = edge16_tab_l[(rs1 >> 1) & 0x3].left;
		right = edge16_tab_l[(rs2 >> 1) & 0x3].right;
		अवरोध;

	हाल EDGE32_OPF:
	हाल EDGE32N_OPF:
		left = edge32_tab[(rs1 >> 2) & 0x1].left;
		right = edge32_tab[(rs2 >> 2) & 0x1].right;
		अवरोध;

	हाल EDGE32L_OPF:
	हाल EDGE32LN_OPF:
		left = edge32_tab_l[(rs1 >> 2) & 0x1].left;
		right = edge32_tab_l[(rs2 >> 2) & 0x1].right;
		अवरोध;
	पूर्ण

	अगर ((rs1 & ~0x7UL) == (rs2 & ~0x7UL))
		rd_val = right & left;
	अन्यथा
		rd_val = left;

	store_reg(regs, rd_val, RD(insn));

	चयन (opf) अणु
	हाल EDGE8_OPF:
	हाल EDGE8L_OPF:
	हाल EDGE16_OPF:
	हाल EDGE16L_OPF:
	हाल EDGE32_OPF:
	हाल EDGE32L_OPF: अणु
		अचिन्हित दीर्घ ccr, tstate;

		__यंत्र__ __अस्थिर__("subcc	%1, %2, %%g0\n\t"
				     "rd	%%ccr, %0"
				     : "=r" (ccr)
				     : "r" (orig_rs1), "r" (orig_rs2)
				     : "cc");
		tstate = regs->tstate & ~(TSTATE_XCC | TSTATE_ICC);
		regs->tstate = tstate | (ccr << 32UL);
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम array(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक opf)
अणु
	अचिन्हित दीर्घ rs1, rs2, rd_val;
	अचिन्हित पूर्णांक bits, bits_mask;

	maybe_flush_winकरोws(RS1(insn), RS2(insn), RD(insn), 0);
	rs1 = fetch_reg(RS1(insn), regs);
	rs2 = fetch_reg(RS2(insn), regs);

	bits = (rs2 > 5 ? 5 : rs2);
	bits_mask = (1UL << bits) - 1UL;

	rd_val = ((((rs1 >> 11) & 0x3) <<  0) |
		  (((rs1 >> 33) & 0x3) <<  2) |
		  (((rs1 >> 55) & 0x1) <<  4) |
		  (((rs1 >> 13) & 0xf) <<  5) |
		  (((rs1 >> 35) & 0xf) <<  9) |
		  (((rs1 >> 56) & 0xf) << 13) |
		  (((rs1 >> 17) & bits_mask) << 17) |
		  (((rs1 >> 39) & bits_mask) << (17 + bits)) |
		  (((rs1 >> 60) & 0xf)       << (17 + (2*bits))));

	चयन (opf) अणु
	हाल ARRAY16_OPF:
		rd_val <<= 1;
		अवरोध;

	हाल ARRAY32_OPF:
		rd_val <<= 2;
	पूर्ण

	store_reg(regs, rd_val, RD(insn));
पूर्ण

अटल व्योम bmask(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित दीर्घ rs1, rs2, rd_val, gsr;

	maybe_flush_winकरोws(RS1(insn), RS2(insn), RD(insn), 0);
	rs1 = fetch_reg(RS1(insn), regs);
	rs2 = fetch_reg(RS2(insn), regs);
	rd_val = rs1 + rs2;

	store_reg(regs, rd_val, RD(insn));

	gsr = current_thपढ़ो_info()->gsr[0] & 0xffffffff;
	gsr |= rd_val << 32UL;
	current_thपढ़ो_info()->gsr[0] = gsr;
पूर्ण

अटल व्योम bshuffle(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	काष्ठा fpustate *f = FPUSTATE;
	अचिन्हित दीर्घ rs1, rs2, rd_val;
	अचिन्हित दीर्घ bmask, i;

	bmask = current_thपढ़ो_info()->gsr[0] >> 32UL;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));

	rd_val = 0UL;
	क्रम (i = 0; i < 8; i++) अणु
		अचिन्हित दीर्घ which = (bmask >> (i * 4)) & 0xf;
		अचिन्हित दीर्घ byte;

		अगर (which < 8)
			byte = (rs1 >> (which * 8)) & 0xff;
		अन्यथा
			byte = (rs2 >> ((which-8)*8)) & 0xff;
		rd_val |= (byte << (i * 8));
	पूर्ण

	*fpd_regaddr(f, RD(insn)) = rd_val;
पूर्ण

अटल व्योम pdist(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	काष्ठा fpustate *f = FPUSTATE;
	अचिन्हित दीर्घ rs1, rs2, *rd, rd_val;
	अचिन्हित दीर्घ i;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));
	rd = fpd_regaddr(f, RD(insn));

	rd_val = *rd;

	क्रम (i = 0; i < 8; i++) अणु
		s16 s1, s2;

		s1 = (rs1 >> (56 - (i * 8))) & 0xff;
		s2 = (rs2 >> (56 - (i * 8))) & 0xff;

		/* Absolute value of dअगरference. */
		s1 -= s2;
		अगर (s1 < 0)
			s1 = ~s1 + 1;

		rd_val += s1;
	पूर्ण

	*rd = rd_val;
पूर्ण

अटल व्योम pक्रमmat(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक opf)
अणु
	काष्ठा fpustate *f = FPUSTATE;
	अचिन्हित दीर्घ rs1, rs2, gsr, scale, rd_val;

	gsr = current_thपढ़ो_info()->gsr[0];
	scale = (gsr >> 3) & (opf == FPACK16_OPF ? 0xf : 0x1f);
	चयन (opf) अणु
	हाल FPACK16_OPF: अणु
		अचिन्हित दीर्घ byte;

		rs2 = fpd_regval(f, RS2(insn));
		rd_val = 0;
		क्रम (byte = 0; byte < 4; byte++) अणु
			अचिन्हित पूर्णांक val;
			s16 src = (rs2 >> (byte * 16UL)) & 0xffffUL;
			पूर्णांक scaled = src << scale;
			पूर्णांक from_fixed = scaled >> 7;

			val = ((from_fixed < 0) ?
			       0 :
			       (from_fixed > 255) ?
			       255 : from_fixed);

			rd_val |= (val << (8 * byte));
		पूर्ण
		*fps_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FPACK32_OPF: अणु
		अचिन्हित दीर्घ word;

		rs1 = fpd_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));
		rd_val = (rs1 << 8) & ~(0x000000ff000000ffUL);
		क्रम (word = 0; word < 2; word++) अणु
			अचिन्हित दीर्घ val;
			s32 src = (rs2 >> (word * 32UL));
			s64 scaled = src << scale;
			s64 from_fixed = scaled >> 23;

			val = ((from_fixed < 0) ?
			       0 :
			       (from_fixed > 255) ?
			       255 : from_fixed);

			rd_val |= (val << (32 * word));
		पूर्ण
		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FPACKFIX_OPF: अणु
		अचिन्हित दीर्घ word;

		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		क्रम (word = 0; word < 2; word++) अणु
			दीर्घ val;
			s32 src = (rs2 >> (word * 32UL));
			s64 scaled = src << scale;
			s64 from_fixed = scaled >> 16;

			val = ((from_fixed < -32768) ?
			       -32768 :
			       (from_fixed > 32767) ?
			       32767 : from_fixed);

			rd_val |= ((val & 0xffff) << (word * 16));
		पूर्ण
		*fps_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FEXPAND_OPF: अणु
		अचिन्हित दीर्घ byte;

		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		क्रम (byte = 0; byte < 4; byte++) अणु
			अचिन्हित दीर्घ val;
			u8 src = (rs2 >> (byte * 8)) & 0xff;

			val = src << 4;

			rd_val |= (val << (byte * 16));
		पूर्ण
		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FPMERGE_OPF: अणु
		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = (((rs2 & 0x000000ff) <<  0) |
			  ((rs1 & 0x000000ff) <<  8) |
			  ((rs2 & 0x0000ff00) <<  8) |
			  ((rs1 & 0x0000ff00) << 16) |
			  ((rs2 & 0x00ff0000) << 16) |
			  ((rs1 & 0x00ff0000) << 24) |
			  ((rs2 & 0xff000000) << 24) |
			  ((rs1 & 0xff000000) << 32));
		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pmul(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक opf)
अणु
	काष्ठा fpustate *f = FPUSTATE;
	अचिन्हित दीर्घ rs1, rs2, rd_val;

	चयन (opf) अणु
	हाल FMUL8x16_OPF: अणु
		अचिन्हित दीर्घ byte;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		क्रम (byte = 0; byte < 4; byte++) अणु
			u16 src1 = (rs1 >> (byte *  8)) & 0x00ff;
			s16 src2 = (rs2 >> (byte * 16)) & 0xffff;
			u32 prod = src1 * src2;
			u16 scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			अगर (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		पूर्ण

		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FMUL8x16AU_OPF:
	हाल FMUL8x16AL_OPF: अणु
		अचिन्हित दीर्घ byte;
		s16 src2;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		src2 = rs2 >> (opf == FMUL8x16AU_OPF ? 16 : 0);
		क्रम (byte = 0; byte < 4; byte++) अणु
			u16 src1 = (rs1 >> (byte * 8)) & 0x00ff;
			u32 prod = src1 * src2;
			u16 scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			अगर (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		पूर्ण

		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FMUL8SUx16_OPF:
	हाल FMUL8ULx16_OPF: अणु
		अचिन्हित दीर्घ byte, ushअगरt;

		rs1 = fpd_regval(f, RS1(insn));
		rs2 = fpd_regval(f, RS2(insn));

		rd_val = 0;
		ushअगरt = (opf == FMUL8SUx16_OPF) ? 8 : 0;
		क्रम (byte = 0; byte < 4; byte++) अणु
			u16 src1;
			s16 src2;
			u32 prod;
			u16 scaled;

			src1 = ((rs1 >> ((16 * byte) + ushअगरt)) & 0x00ff);
			src2 = ((rs2 >> (16 * byte)) & 0xffff);
			prod = src1 * src2;
			scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			अगर (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) << (byte * 16UL));
		पूर्ण

		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण

	हाल FMULD8SUx16_OPF:
	हाल FMULD8ULx16_OPF: अणु
		अचिन्हित दीर्घ byte, ushअगरt;

		rs1 = fps_regval(f, RS1(insn));
		rs2 = fps_regval(f, RS2(insn));

		rd_val = 0;
		ushअगरt = (opf == FMULD8SUx16_OPF) ? 8 : 0;
		क्रम (byte = 0; byte < 2; byte++) अणु
			u16 src1;
			s16 src2;
			u32 prod;
			u16 scaled;

			src1 = ((rs1 >> ((16 * byte) + ushअगरt)) & 0x00ff);
			src2 = ((rs2 >> (16 * byte)) & 0xffff);
			prod = src1 * src2;
			scaled = ((prod & 0x00ffff00) >> 8);

			/* Round up.  */
			अगर (prod & 0x80)
				scaled++;
			rd_val |= ((scaled & 0xffffUL) <<
				   ((byte * 32UL) + 7UL));
		पूर्ण
		*fpd_regaddr(f, RD(insn)) = rd_val;
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pcmp(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn, अचिन्हित पूर्णांक opf)
अणु
	काष्ठा fpustate *f = FPUSTATE;
	अचिन्हित दीर्घ rs1, rs2, rd_val, i;

	rs1 = fpd_regval(f, RS1(insn));
	rs2 = fpd_regval(f, RS2(insn));

	rd_val = 0;

	चयन (opf) अणु
	हाल FCMPGT16_OPF:
		क्रम (i = 0; i < 4; i++) अणु
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			अगर (a > b)
				rd_val |= 8 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPGT32_OPF:
		क्रम (i = 0; i < 2; i++) अणु
			s32 a = (rs1 >> (i * 32)) & 0xffffffff;
			s32 b = (rs2 >> (i * 32)) & 0xffffffff;

			अगर (a > b)
				rd_val |= 2 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPLE16_OPF:
		क्रम (i = 0; i < 4; i++) अणु
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			अगर (a <= b)
				rd_val |= 8 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPLE32_OPF:
		क्रम (i = 0; i < 2; i++) अणु
			s32 a = (rs1 >> (i * 32)) & 0xffffffff;
			s32 b = (rs2 >> (i * 32)) & 0xffffffff;

			अगर (a <= b)
				rd_val |= 2 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPNE16_OPF:
		क्रम (i = 0; i < 4; i++) अणु
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			अगर (a != b)
				rd_val |= 8 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPNE32_OPF:
		क्रम (i = 0; i < 2; i++) अणु
			s32 a = (rs1 >> (i * 32)) & 0xffffffff;
			s32 b = (rs2 >> (i * 32)) & 0xffffffff;

			अगर (a != b)
				rd_val |= 2 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPEQ16_OPF:
		क्रम (i = 0; i < 4; i++) अणु
			s16 a = (rs1 >> (i * 16)) & 0xffff;
			s16 b = (rs2 >> (i * 16)) & 0xffff;

			अगर (a == b)
				rd_val |= 8 >> i;
		पूर्ण
		अवरोध;

	हाल FCMPEQ32_OPF:
		क्रम (i = 0; i < 2; i++) अणु
			s32 a = (rs1 >> (i * 32)) & 0xffffffff;
			s32 b = (rs2 >> (i * 32)) & 0xffffffff;

			अगर (a == b)
				rd_val |= 2 >> i;
		पूर्ण
		अवरोध;
	पूर्ण

	maybe_flush_winकरोws(0, 0, RD(insn), 0);
	store_reg(regs, rd_val, RD(insn));
पूर्ण

/* Emulate the VIS inकाष्ठाions which are not implemented in
 * hardware on Niagara.
 */
पूर्णांक vis_emul(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक insn)
अणु
	अचिन्हित दीर्घ pc = regs->tpc;
	अचिन्हित पूर्णांक opf;

	BUG_ON(regs->tstate & TSTATE_PRIV);

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		pc = (u32)pc;

	अगर (get_user(insn, (u32 __user *) pc))
		वापस -EFAULT;

	save_and_clear_fpu();

	opf = (insn & VIS_OPF_MASK) >> VIS_OPF_SHIFT;
	चयन (opf) अणु
	शेष:
		वापस -EINVAL;

	/* Pixel Formatting Inकाष्ठाions.  */
	हाल FPACK16_OPF:
	हाल FPACK32_OPF:
	हाल FPACKFIX_OPF:
	हाल FEXPAND_OPF:
	हाल FPMERGE_OPF:
		pक्रमmat(regs, insn, opf);
		अवरोध;

	/* Partitioned Multiply Inकाष्ठाions  */
	हाल FMUL8x16_OPF:
	हाल FMUL8x16AU_OPF:
	हाल FMUL8x16AL_OPF:
	हाल FMUL8SUx16_OPF:
	हाल FMUL8ULx16_OPF:
	हाल FMULD8SUx16_OPF:
	हाल FMULD8ULx16_OPF:
		pmul(regs, insn, opf);
		अवरोध;

	/* Pixel Compare Inकाष्ठाions  */
	हाल FCMPGT16_OPF:
	हाल FCMPGT32_OPF:
	हाल FCMPLE16_OPF:
	हाल FCMPLE32_OPF:
	हाल FCMPNE16_OPF:
	हाल FCMPNE32_OPF:
	हाल FCMPEQ16_OPF:
	हाल FCMPEQ32_OPF:
		pcmp(regs, insn, opf);
		अवरोध;

	/* Edge Handling Inकाष्ठाions  */
	हाल EDGE8_OPF:
	हाल EDGE8N_OPF:
	हाल EDGE8L_OPF:
	हाल EDGE8LN_OPF:
	हाल EDGE16_OPF:
	हाल EDGE16N_OPF:
	हाल EDGE16L_OPF:
	हाल EDGE16LN_OPF:
	हाल EDGE32_OPF:
	हाल EDGE32N_OPF:
	हाल EDGE32L_OPF:
	हाल EDGE32LN_OPF:
		edge(regs, insn, opf);
		अवरोध;

	/* Pixel Component Distance  */
	हाल PDIST_OPF:
		pdist(regs, insn);
		अवरोध;

	/* Three-Dimensional Array Addressing Inकाष्ठाions  */
	हाल ARRAY8_OPF:
	हाल ARRAY16_OPF:
	हाल ARRAY32_OPF:
		array(regs, insn, opf);
		अवरोध;

	/* Byte Mask and Shuffle Inकाष्ठाions  */
	हाल BMASK_OPF:
		bmask(regs, insn);
		अवरोध;

	हाल BSHUFFLE_OPF:
		bshuffle(regs, insn);
		अवरोध;
	पूर्ण

	regs->tpc = regs->tnpc;
	regs->tnpc += 4;
	वापस 0;
पूर्ण
