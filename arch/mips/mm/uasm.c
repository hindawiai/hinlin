<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * A small micro-assembler. It is पूर्णांकentionally kept simple, करोes only
 * support a subset of inकाष्ठाions, and करोes not try to hide pipeline
 * effects like branch delay slots.
 *
 * Copyright (C) 2004, 2005, 2006, 2008	 Thiemo Seufer
 * Copyright (C) 2005, 2007  Maciej W. Rozycki
 * Copyright (C) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2012, 2013  MIPS Technologies, Inc.  All rights reserved.
 */

क्रमागत fields अणु
	RS = 0x001,
	RT = 0x002,
	RD = 0x004,
	RE = 0x008,
	SIMM = 0x010,
	UIMM = 0x020,
	BIMM = 0x040,
	JIMM = 0x080,
	FUNC = 0x100,
	SET = 0x200,
	SCIMM = 0x400,
	SIMM9 = 0x800,
पूर्ण;

#घोषणा OP_MASK		0x3f
#घोषणा OP_SH		26
#घोषणा RD_MASK		0x1f
#घोषणा RD_SH		11
#घोषणा RE_MASK		0x1f
#घोषणा RE_SH		6
#घोषणा IMM_MASK	0xffff
#घोषणा IMM_SH		0
#घोषणा JIMM_MASK	0x3ffffff
#घोषणा JIMM_SH		0
#घोषणा FUNC_MASK	0x3f
#घोषणा FUNC_SH		0
#घोषणा SET_MASK	0x7
#घोषणा SET_SH		0
#घोषणा SIMM9_SH	7
#घोषणा SIMM9_MASK	0x1ff

क्रमागत opcode अणु
	insn_addiu, insn_addu, insn_and, insn_andi, insn_bbit0, insn_bbit1,
	insn_beq, insn_beql, insn_bgez, insn_bgezl, insn_bgtz, insn_blez,
	insn_bltz, insn_bltzl, insn_bne, insn_अवरोध, insn_cache, insn_cfc1,
	insn_cfcmsa, insn_ctc1, insn_ctcmsa, insn_daddiu, insn_daddu, insn_dभागu,
	insn_dभागu_r6, insn_di, insn_dins, insn_dinsm, insn_dinsu, insn_भागu,
	insn_भागu_r6, insn_dmfc0, insn_dmodu, insn_dmtc0, insn_dmultu,
	insn_dmulu, insn_drotr, insn_drotr32, insn_dsbh, insn_dshd, insn_dsll,
	insn_dsll32, insn_dsllv, insn_dsra, insn_dsra32, insn_dsrav, insn_dsrl,
	insn_dsrl32, insn_dsrlv, insn_dsubu, insn_eret, insn_ext, insn_ins,
	insn_j, insn_jal, insn_jalr, insn_jr, insn_lb, insn_lbu, insn_ld,
	insn_lddir, insn_ldpte, insn_ldx, insn_lh, insn_lhu, insn_ll, insn_lld,
	insn_lui, insn_lw, insn_lwu, insn_lwx, insn_mfc0, insn_mfhc0, insn_mfhi,
	insn_mflo, insn_modu, insn_movn, insn_movz, insn_mtc0, insn_mthc0,
	insn_mthi, insn_mtlo, insn_mul, insn_multu, insn_mulu, insn_nor,
	insn_or, insn_ori, insn_pref, insn_rfe, insn_rotr, insn_sb, insn_sc,
	insn_scd, insn_seleqz, insn_selnez, insn_sd, insn_sh, insn_sll,
	insn_sllv, insn_slt, insn_slti, insn_sltiu, insn_sltu, insn_sra,
	insn_srav, insn_srl, insn_srlv, insn_subu, insn_sw, insn_sync,
	insn_syscall, insn_tlbp, insn_tlbr, insn_tlbwi, insn_tlbwr, insn_रुको,
	insn_wsbh, insn_xor, insn_xori, insn_yield,
	insn_invalid /* insn_invalid must be last */
पूर्ण;

काष्ठा insn अणु
	u32 match;
	क्रमागत fields fields;
पूर्ण;

अटल अंतरभूत u32 build_rs(u32 arg)
अणु
	WARN(arg & ~RS_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & RS_MASK) << RS_SH;
पूर्ण

अटल अंतरभूत u32 build_rt(u32 arg)
अणु
	WARN(arg & ~RT_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & RT_MASK) << RT_SH;
पूर्ण

अटल अंतरभूत u32 build_rd(u32 arg)
अणु
	WARN(arg & ~RD_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & RD_MASK) << RD_SH;
पूर्ण

अटल अंतरभूत u32 build_re(u32 arg)
अणु
	WARN(arg & ~RE_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & RE_MASK) << RE_SH;
पूर्ण

अटल अंतरभूत u32 build_simm(s32 arg)
अणु
	WARN(arg > 0x7fff || arg < -0x8000,
	     KERN_WARNING "Micro-assembler field overflow\n");

	वापस arg & 0xffff;
पूर्ण

अटल अंतरभूत u32 build_uimm(u32 arg)
अणु
	WARN(arg & ~IMM_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस arg & IMM_MASK;
पूर्ण

अटल अंतरभूत u32 build_scimm(u32 arg)
अणु
	WARN(arg & ~SCIMM_MASK,
	     KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & SCIMM_MASK) << SCIMM_SH;
पूर्ण

अटल अंतरभूत u32 build_scimm9(s32 arg)
अणु
	WARN((arg > 0xff || arg < -0x100),
	       KERN_WARNING "Micro-assembler field overflow\n");

	वापस (arg & SIMM9_MASK) << SIMM9_SH;
पूर्ण

अटल अंतरभूत u32 build_func(u32 arg)
अणु
	WARN(arg & ~FUNC_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस arg & FUNC_MASK;
पूर्ण

अटल अंतरभूत u32 build_set(u32 arg)
अणु
	WARN(arg & ~SET_MASK, KERN_WARNING "Micro-assembler field overflow\n");

	वापस arg & SET_MASK;
पूर्ण

अटल व्योम build_insn(u32 **buf, क्रमागत opcode opc, ...);

#घोषणा I_u1u2u3(op)					\
Ip_u1u2u3(op)						\
अणु							\
	build_insn(buf, insn##op, a, b, c);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_s3s1s2(op)					\
Ip_s3s1s2(op)						\
अणु							\
	build_insn(buf, insn##op, b, c, a);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1u3(op)					\
Ip_u2u1u3(op)						\
अणु							\
	build_insn(buf, insn##op, b, a, c);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u3u2u1(op)					\
Ip_u3u2u1(op)						\
अणु							\
	build_insn(buf, insn##op, c, b, a);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u3u1u2(op)					\
Ip_u3u1u2(op)						\
अणु							\
	build_insn(buf, insn##op, b, c, a);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u1u2s3(op)					\
Ip_u1u2s3(op)						\
अणु							\
	build_insn(buf, insn##op, a, b, c);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2s3u1(op)					\
Ip_u2s3u1(op)						\
अणु							\
	build_insn(buf, insn##op, c, a, b);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1s3(op)					\
Ip_u2u1s3(op)						\
अणु							\
	build_insn(buf, insn##op, b, a, c);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1msbu3(op)					\
Ip_u2u1msbu3(op)					\
अणु							\
	build_insn(buf, insn##op, b, a, c+d-1, c);	\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1msb32u3(op)				\
Ip_u2u1msbu3(op)					\
अणु							\
	build_insn(buf, insn##op, b, a, c+d-33, c);	\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1msb32msb3(op)				\
Ip_u2u1msbu3(op)					\
अणु							\
	build_insn(buf, insn##op, b, a, c+d-33, c-32);	\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1msbdu3(op)				\
Ip_u2u1msbu3(op)					\
अणु							\
	build_insn(buf, insn##op, b, a, d-1, c);	\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u1u2(op)					\
Ip_u1u2(op)						\
अणु							\
	build_insn(buf, insn##op, a, b);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u2u1(op)					\
Ip_u1u2(op)						\
अणु							\
	build_insn(buf, insn##op, b, a);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u1s2(op)					\
Ip_u1s2(op)						\
अणु							\
	build_insn(buf, insn##op, a, b);		\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_u1(op)					\
Ip_u1(op)						\
अणु							\
	build_insn(buf, insn##op, a);			\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

#घोषणा I_0(op)						\
Ip_0(op)						\
अणु							\
	build_insn(buf, insn##op);			\
पूर्ण							\
UASM_EXPORT_SYMBOL(uयंत्र_i##op);

I_u2u1s3(_addiu)
I_u3u1u2(_addu)
I_u2u1u3(_andi)
I_u3u1u2(_and)
I_u1u2s3(_beq)
I_u1u2s3(_beql)
I_u1s2(_bgez)
I_u1s2(_bgezl)
I_u1s2(_bgtz)
I_u1s2(_blez)
I_u1s2(_bltz)
I_u1s2(_bltzl)
I_u1u2s3(_bne)
I_u1(_अवरोध)
I_u2s3u1(_cache)
I_u1u2(_cfc1)
I_u2u1(_cfcmsa)
I_u1u2(_ctc1)
I_u2u1(_ctcmsa)
I_u1u2(_dभागu)
I_u3u1u2(_dभागu_r6)
I_u1u2u3(_dmfc0)
I_u3u1u2(_dmodu)
I_u1u2u3(_dmtc0)
I_u1u2(_dmultu)
I_u3u1u2(_dmulu)
I_u2u1s3(_daddiu)
I_u3u1u2(_daddu)
I_u1(_di);
I_u1u2(_भागu)
I_u3u1u2(_भागu_r6)
I_u2u1(_dsbh);
I_u2u1(_dshd);
I_u2u1u3(_dsll)
I_u2u1u3(_dsll32)
I_u3u2u1(_dsllv)
I_u2u1u3(_dsra)
I_u2u1u3(_dsra32)
I_u3u2u1(_dsrav)
I_u2u1u3(_dsrl)
I_u2u1u3(_dsrl32)
I_u3u2u1(_dsrlv)
I_u2u1u3(_drotr)
I_u2u1u3(_drotr32)
I_u3u1u2(_dsubu)
I_0(_eret)
I_u2u1msbdu3(_ext)
I_u2u1msbu3(_ins)
I_u1(_j)
I_u1(_jal)
I_u2u1(_jalr)
I_u1(_jr)
I_u2s3u1(_lb)
I_u2s3u1(_lbu)
I_u2s3u1(_ld)
I_u2s3u1(_lh)
I_u2s3u1(_lhu)
I_u2s3u1(_ll)
I_u2s3u1(_lld)
I_u1s2(_lui)
I_u2s3u1(_lw)
I_u2s3u1(_lwu)
I_u1u2u3(_mfc0)
I_u1u2u3(_mfhc0)
I_u3u1u2(_modu)
I_u3u1u2(_movn)
I_u3u1u2(_movz)
I_u1(_mfhi)
I_u1(_mflo)
I_u1u2u3(_mtc0)
I_u1u2u3(_mthc0)
I_u1(_mthi)
I_u1(_mtlo)
I_u3u1u2(_mul)
I_u1u2(_multu)
I_u3u1u2(_mulu)
I_u3u1u2(_nor)
I_u3u1u2(_or)
I_u2u1u3(_ori)
I_0(_rfe)
I_u2s3u1(_sb)
I_u2s3u1(_sc)
I_u2s3u1(_scd)
I_u2s3u1(_sd)
I_u3u1u2(_seleqz)
I_u3u1u2(_selnez)
I_u2s3u1(_sh)
I_u2u1u3(_sll)
I_u3u2u1(_sllv)
I_s3s1s2(_slt)
I_u2u1s3(_slti)
I_u2u1s3(_sltiu)
I_u3u1u2(_sltu)
I_u2u1u3(_sra)
I_u3u2u1(_srav)
I_u2u1u3(_srl)
I_u3u2u1(_srlv)
I_u2u1u3(_rotr)
I_u3u1u2(_subu)
I_u2s3u1(_sw)
I_u1(_sync)
I_0(_tlbp)
I_0(_tlbr)
I_0(_tlbwi)
I_0(_tlbwr)
I_u1(_रुको);
I_u2u1(_wsbh)
I_u3u1u2(_xor)
I_u2u1u3(_xori)
I_u2u1(_yield)
I_u2u1msbu3(_dins);
I_u2u1msb32u3(_dinsm);
I_u2u1msb32msb3(_dinsu);
I_u1(_syscall);
I_u1u2s3(_bbit0);
I_u1u2s3(_bbit1);
I_u3u1u2(_lwx)
I_u3u1u2(_ldx)
I_u1u2(_ldpte)
I_u2u1u3(_lddir)

#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
#समावेश <यंत्र/octeon/octeon.h>
व्योम uयंत्र_i_pref(u32 **buf, अचिन्हित पूर्णांक a, चिन्हित पूर्णांक b,
			    अचिन्हित पूर्णांक c)
अणु
	अगर (OCTEON_IS_MODEL(OCTEON_CN6XXX) && a <= 24 && a != 5)
		/*
		 * As per erratum Core-14449, replace prefetches 0-4,
		 * 6-24 with 'pref 28'.
		 */
		build_insn(buf, insn_pref, c, 28, b);
	अन्यथा
		build_insn(buf, insn_pref, c, a, b);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_i_pref);
#अन्यथा
I_u2s3u1(_pref)
#पूर्ण_अगर

/* Handle labels. */
व्योम uयंत्र_build_label(काष्ठा uयंत्र_label **lab, u32 *addr, पूर्णांक lid)
अणु
	(*lab)->addr = addr;
	(*lab)->lab = lid;
	(*lab)++;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_build_label);

पूर्णांक uयंत्र_in_compat_space_p(दीर्घ addr)
अणु
	/* Is this address in 32bit compat space? */
	वापस addr == (पूर्णांक)addr;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_in_compat_space_p);

अटल पूर्णांक uयंत्र_rel_highest(दीर्घ val)
अणु
#अगर_घोषित CONFIG_64BIT
	वापस ((((val + 0x800080008000L) >> 48) & 0xffff) ^ 0x8000) - 0x8000;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक uयंत्र_rel_higher(दीर्घ val)
अणु
#अगर_घोषित CONFIG_64BIT
	वापस ((((val + 0x80008000L) >> 32) & 0xffff) ^ 0x8000) - 0x8000;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

पूर्णांक uयंत्र_rel_hi(दीर्घ val)
अणु
	वापस ((((val + 0x8000L) >> 16) & 0xffff) ^ 0x8000) - 0x8000;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_rel_hi);

पूर्णांक uयंत्र_rel_lo(दीर्घ val)
अणु
	वापस ((val & 0xffff) ^ 0x8000) - 0x8000;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_rel_lo);

व्योम UASM_i_LA_mostly(u32 **buf, अचिन्हित पूर्णांक rs, दीर्घ addr)
अणु
	अगर (!uयंत्र_in_compat_space_p(addr)) अणु
		uयंत्र_i_lui(buf, rs, uयंत्र_rel_highest(addr));
		अगर (uयंत्र_rel_higher(addr))
			uयंत्र_i_daddiu(buf, rs, rs, uयंत्र_rel_higher(addr));
		अगर (uयंत्र_rel_hi(addr)) अणु
			uयंत्र_i_dsll(buf, rs, rs, 16);
			uयंत्र_i_daddiu(buf, rs, rs,
					uयंत्र_rel_hi(addr));
			uयंत्र_i_dsll(buf, rs, rs, 16);
		पूर्ण अन्यथा
			uयंत्र_i_dsll32(buf, rs, rs, 0);
	पूर्ण अन्यथा
		uयंत्र_i_lui(buf, rs, uयंत्र_rel_hi(addr));
पूर्ण
UASM_EXPORT_SYMBOL(UASM_i_LA_mostly);

व्योम UASM_i_LA(u32 **buf, अचिन्हित पूर्णांक rs, दीर्घ addr)
अणु
	UASM_i_LA_mostly(buf, rs, addr);
	अगर (uयंत्र_rel_lo(addr)) अणु
		अगर (!uयंत्र_in_compat_space_p(addr))
			uयंत्र_i_daddiu(buf, rs, rs,
					uयंत्र_rel_lo(addr));
		अन्यथा
			uयंत्र_i_addiu(buf, rs, rs,
					uयंत्र_rel_lo(addr));
	पूर्ण
पूर्ण
UASM_EXPORT_SYMBOL(UASM_i_LA);

/* Handle relocations. */
व्योम uयंत्र_r_mips_pc16(काष्ठा uयंत्र_reloc **rel, u32 *addr, पूर्णांक lid)
अणु
	(*rel)->addr = addr;
	(*rel)->type = R_MIPS_PC16;
	(*rel)->lab = lid;
	(*rel)++;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_r_mips_pc16);

अटल अंतरभूत व्योम __resolve_relocs(काष्ठा uयंत्र_reloc *rel,
				    काष्ठा uयंत्र_label *lab);

व्योम uयंत्र_resolve_relocs(काष्ठा uयंत्र_reloc *rel,
				  काष्ठा uयंत्र_label *lab)
अणु
	काष्ठा uयंत्र_label *l;

	क्रम (; rel->lab != UASM_LABEL_INVALID; rel++)
		क्रम (l = lab; l->lab != UASM_LABEL_INVALID; l++)
			अगर (rel->lab == l->lab)
				__resolve_relocs(rel, l);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_resolve_relocs);

व्योम uयंत्र_move_relocs(काष्ठा uयंत्र_reloc *rel, u32 *first, u32 *end,
			       दीर्घ off)
अणु
	क्रम (; rel->lab != UASM_LABEL_INVALID; rel++)
		अगर (rel->addr >= first && rel->addr < end)
			rel->addr += off;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_move_relocs);

व्योम uयंत्र_move_labels(काष्ठा uयंत्र_label *lab, u32 *first, u32 *end,
			       दीर्घ off)
अणु
	क्रम (; lab->lab != UASM_LABEL_INVALID; lab++)
		अगर (lab->addr >= first && lab->addr < end)
			lab->addr += off;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_move_labels);

व्योम uयंत्र_copy_handler(काष्ठा uयंत्र_reloc *rel, काष्ठा uयंत्र_label *lab,
				u32 *first, u32 *end, u32 *target)
अणु
	दीर्घ off = (दीर्घ)(target - first);

	स_नकल(target, first, (end - first) * माप(u32));

	uयंत्र_move_relocs(rel, first, end, off);
	uयंत्र_move_labels(lab, first, end, off);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_copy_handler);

पूर्णांक uयंत्र_insn_has_bdelay(काष्ठा uयंत्र_reloc *rel, u32 *addr)
अणु
	क्रम (; rel->lab != UASM_LABEL_INVALID; rel++) अणु
		अगर (rel->addr == addr
		    && (rel->type == R_MIPS_PC16
			|| rel->type == R_MIPS_26))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_insn_has_bdelay);

/* Convenience functions क्रम labeled branches. */
व्योम uयंत्र_il_bltz(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			   पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bltz(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bltz);

व्योम uयंत्र_il_b(u32 **p, काष्ठा uयंत्र_reloc **r, पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_b(p, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_b);

व्योम uयंत्र_il_beq(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक r1,
			  अचिन्हित पूर्णांक r2, पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_beq(p, r1, r2, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_beq);

व्योम uयंत्र_il_beqz(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			   पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_beqz(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_beqz);

व्योम uयंत्र_il_beqzl(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			    पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_beqzl(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_beqzl);

व्योम uयंत्र_il_bne(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg1,
			  अचिन्हित पूर्णांक reg2, पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bne(p, reg1, reg2, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bne);

व्योम uयंत्र_il_bnez(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			   पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bnez(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bnez);

व्योम uयंत्र_il_bgezl(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			    पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bgezl(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bgezl);

व्योम uयंत्र_il_bgez(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			   पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bgez(p, reg, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bgez);

व्योम uयंत्र_il_bbit0(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक bit, पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bbit0(p, reg, bit, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bbit0);

व्योम uयंत्र_il_bbit1(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
			    अचिन्हित पूर्णांक bit, पूर्णांक lid)
अणु
	uयंत्र_r_mips_pc16(r, *p, lid);
	uयंत्र_i_bbit1(p, reg, bit, 0);
पूर्ण
UASM_EXPORT_SYMBOL(uयंत्र_il_bbit1);
