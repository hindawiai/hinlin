<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004, 2005, 2006, 2008	 Thiemo Seufer
 * Copyright (C) 2005  Maciej W. Rozycki
 * Copyright (C) 2006  Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2012, 2013  MIPS Technologies, Inc.  All rights reserved.
 */

#अगर_अघोषित __ASM_UASM_H
#घोषणा __ASM_UASM_H

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_EXPORT_UASM
#समावेश <linux/export.h>
#घोषणा UASM_EXPORT_SYMBOL(sym) EXPORT_SYMBOL(sym)
#अन्यथा
#घोषणा UASM_EXPORT_SYMBOL(sym)
#पूर्ण_अगर

#घोषणा Ip_u1u2u3(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c)

#घोषणा Ip_u2u1u3(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c)

#घोषणा Ip_u3u2u1(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c)

#घोषणा Ip_u3u1u2(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c)

#घोषणा Ip_u1u2s3(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, चिन्हित पूर्णांक c)

#घोषणा Ip_u2s3u1(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, चिन्हित पूर्णांक b, अचिन्हित पूर्णांक c)

#घोषणा Ip_s3s1s2(op)							\
व्योम uयंत्र_i##op(u32 **buf, पूर्णांक a, पूर्णांक b, पूर्णांक c)

#घोषणा Ip_u2u1s3(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, चिन्हित पूर्णांक c)

#घोषणा Ip_u2u1msbu3(op)						\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b, अचिन्हित पूर्णांक c, \
	   अचिन्हित पूर्णांक d)

#घोषणा Ip_u1u2(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)

#घोषणा Ip_u2u1(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, अचिन्हित पूर्णांक b)

#घोषणा Ip_u1s2(op)							\
व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a, चिन्हित पूर्णांक b)

#घोषणा Ip_u1(op) व्योम uयंत्र_i##op(u32 **buf, अचिन्हित पूर्णांक a)

#घोषणा Ip_0(op) व्योम uयंत्र_i##op(u32 **buf)

Ip_u2u1s3(_addiu);
Ip_u3u1u2(_addu);
Ip_u3u1u2(_and);
Ip_u2u1u3(_andi);
Ip_u1u2s3(_bbit0);
Ip_u1u2s3(_bbit1);
Ip_u1u2s3(_beq);
Ip_u1u2s3(_beql);
Ip_u1s2(_bgez);
Ip_u1s2(_bgezl);
Ip_u1s2(_bgtz);
Ip_u1s2(_blez);
Ip_u1s2(_bltz);
Ip_u1s2(_bltzl);
Ip_u1u2s3(_bne);
Ip_u1(_अवरोध);
Ip_u2s3u1(_cache);
Ip_u1u2(_cfc1);
Ip_u2u1(_cfcmsa);
Ip_u1u2(_ctc1);
Ip_u2u1(_ctcmsa);
Ip_u2u1s3(_daddiu);
Ip_u3u1u2(_daddu);
Ip_u1u2(_dभागu);
Ip_u3u1u2(_dभागu_r6);
Ip_u1(_di);
Ip_u2u1msbu3(_dins);
Ip_u2u1msbu3(_dinsm);
Ip_u2u1msbu3(_dinsu);
Ip_u1u2(_भागu);
Ip_u3u1u2(_भागu_r6);
Ip_u1u2u3(_dmfc0);
Ip_u3u1u2(_dmodu);
Ip_u1u2u3(_dmtc0);
Ip_u1u2(_dmultu);
Ip_u3u1u2(_dmulu);
Ip_u2u1u3(_drotr);
Ip_u2u1u3(_drotr32);
Ip_u2u1(_dsbh);
Ip_u2u1(_dshd);
Ip_u2u1u3(_dsll);
Ip_u2u1u3(_dsll32);
Ip_u3u2u1(_dsllv);
Ip_u2u1u3(_dsra);
Ip_u2u1u3(_dsra32);
Ip_u3u2u1(_dsrav);
Ip_u2u1u3(_dsrl);
Ip_u2u1u3(_dsrl32);
Ip_u3u2u1(_dsrlv);
Ip_u3u1u2(_dsubu);
Ip_0(_eret);
Ip_u2u1msbu3(_ext);
Ip_u2u1msbu3(_ins);
Ip_u1(_j);
Ip_u1(_jal);
Ip_u2u1(_jalr);
Ip_u1(_jr);
Ip_u2s3u1(_lb);
Ip_u2s3u1(_lbu);
Ip_u2s3u1(_ld);
Ip_u3u1u2(_ldx);
Ip_u2s3u1(_lh);
Ip_u2s3u1(_lhu);
Ip_u2s3u1(_ll);
Ip_u2s3u1(_lld);
Ip_u1s2(_lui);
Ip_u2s3u1(_lw);
Ip_u2s3u1(_lwu);
Ip_u3u1u2(_lwx);
Ip_u1u2u3(_mfc0);
Ip_u1u2u3(_mfhc0);
Ip_u1(_mfhi);
Ip_u1(_mflo);
Ip_u3u1u2(_modu);
Ip_u3u1u2(_movn);
Ip_u3u1u2(_movz);
Ip_u1u2u3(_mtc0);
Ip_u1u2u3(_mthc0);
Ip_u1(_mthi);
Ip_u1(_mtlo);
Ip_u3u1u2(_mul);
Ip_u1u2(_multu);
Ip_u3u1u2(_mulu);
Ip_u3u1u2(_nor);
Ip_u3u1u2(_or);
Ip_u2u1u3(_ori);
Ip_u2s3u1(_pref);
Ip_0(_rfe);
Ip_u2u1u3(_rotr);
Ip_u2s3u1(_sb);
Ip_u2s3u1(_sc);
Ip_u2s3u1(_scd);
Ip_u2s3u1(_sd);
Ip_u3u1u2(_seleqz);
Ip_u3u1u2(_selnez);
Ip_u2s3u1(_sh);
Ip_u2u1u3(_sll);
Ip_u3u2u1(_sllv);
Ip_s3s1s2(_slt);
Ip_u2u1s3(_slti);
Ip_u2u1s3(_sltiu);
Ip_u3u1u2(_sltu);
Ip_u2u1u3(_sra);
Ip_u3u2u1(_srav);
Ip_u2u1u3(_srl);
Ip_u3u2u1(_srlv);
Ip_u3u1u2(_subu);
Ip_u2s3u1(_sw);
Ip_u1(_sync);
Ip_u1(_syscall);
Ip_0(_tlbp);
Ip_0(_tlbr);
Ip_0(_tlbwi);
Ip_0(_tlbwr);
Ip_u1(_रुको);
Ip_u2u1(_wsbh);
Ip_u3u1u2(_xor);
Ip_u2u1u3(_xori);
Ip_u2u1(_yield);
Ip_u1u2(_ldpte);
Ip_u2u1u3(_lddir);

/* Handle labels. */
काष्ठा uयंत्र_label अणु
	u32 *addr;
	पूर्णांक lab;
पूर्ण;

व्योम uयंत्र_build_label(काष्ठा uयंत्र_label **lab, u32 *addr,
			पूर्णांक lid);
#अगर_घोषित CONFIG_64BIT
पूर्णांक uयंत्र_in_compat_space_p(दीर्घ addr);
#पूर्ण_अगर
पूर्णांक uयंत्र_rel_hi(दीर्घ val);
पूर्णांक uयंत्र_rel_lo(दीर्घ val);
व्योम UASM_i_LA_mostly(u32 **buf, अचिन्हित पूर्णांक rs, दीर्घ addr);
व्योम UASM_i_LA(u32 **buf, अचिन्हित पूर्णांक rs, दीर्घ addr);

#घोषणा UASM_L_LA(lb)							\
अटल अंतरभूत व्योम uयंत्र_l##lb(काष्ठा uयंत्र_label **lab, u32 *addr)	\
अणु									\
	uयंत्र_build_label(lab, addr, label##lb);				\
पूर्ण

/* convenience macros क्रम inकाष्ठाions */
#अगर_घोषित CONFIG_64BIT
# define UASM_i_ADDIU(buf, rs, rt, val) uयंत्र_i_daddiu(buf, rs, rt, val)
# define UASM_i_ADDU(buf, rs, rt, rd) uयंत्र_i_daddu(buf, rs, rt, rd)
# define UASM_i_LL(buf, rs, rt, off) uयंत्र_i_lld(buf, rs, rt, off)
# define UASM_i_LW(buf, rs, rt, off) uयंत्र_i_ld(buf, rs, rt, off)
# define UASM_i_LWX(buf, rs, rt, rd) uयंत्र_i_ldx(buf, rs, rt, rd)
# define UASM_i_MFC0(buf, rt, rd...) uयंत्र_i_dmfc0(buf, rt, rd)
# define UASM_i_MTC0(buf, rt, rd...) uयंत्र_i_dmtc0(buf, rt, rd)
# define UASM_i_ROTR(buf, rs, rt, sh) uयंत्र_i_drotr(buf, rs, rt, sh)
# define UASM_i_SC(buf, rs, rt, off) uयंत्र_i_scd(buf, rs, rt, off)
# define UASM_i_SLL(buf, rs, rt, sh) uयंत्र_i_dsll(buf, rs, rt, sh)
# define UASM_i_SRA(buf, rs, rt, sh) uयंत्र_i_dsra(buf, rs, rt, sh)
# define UASM_i_SRL(buf, rs, rt, sh) uयंत्र_i_dsrl(buf, rs, rt, sh)
# define UASM_i_SRL_SAFE(buf, rs, rt, sh) uयंत्र_i_dsrl_safe(buf, rs, rt, sh)
# define UASM_i_SUBU(buf, rs, rt, rd) uयंत्र_i_dsubu(buf, rs, rt, rd)
# define UASM_i_SW(buf, rs, rt, off) uयंत्र_i_sd(buf, rs, rt, off)
#अन्यथा
# define UASM_i_ADDIU(buf, rs, rt, val) uयंत्र_i_addiu(buf, rs, rt, val)
# define UASM_i_ADDU(buf, rs, rt, rd) uयंत्र_i_addu(buf, rs, rt, rd)
# define UASM_i_LL(buf, rs, rt, off) uयंत्र_i_ll(buf, rs, rt, off)
# define UASM_i_LW(buf, rs, rt, off) uयंत्र_i_lw(buf, rs, rt, off)
# define UASM_i_LWX(buf, rs, rt, rd) uयंत्र_i_lwx(buf, rs, rt, rd)
# define UASM_i_MFC0(buf, rt, rd...) uयंत्र_i_mfc0(buf, rt, rd)
# define UASM_i_MTC0(buf, rt, rd...) uयंत्र_i_mtc0(buf, rt, rd)
# define UASM_i_ROTR(buf, rs, rt, sh) uयंत्र_i_rotr(buf, rs, rt, sh)
# define UASM_i_SC(buf, rs, rt, off) uयंत्र_i_sc(buf, rs, rt, off)
# define UASM_i_SLL(buf, rs, rt, sh) uयंत्र_i_sll(buf, rs, rt, sh)
# define UASM_i_SRA(buf, rs, rt, sh) uयंत्र_i_sra(buf, rs, rt, sh)
# define UASM_i_SRL(buf, rs, rt, sh) uयंत्र_i_srl(buf, rs, rt, sh)
# define UASM_i_SRL_SAFE(buf, rs, rt, sh) uयंत्र_i_srl(buf, rs, rt, sh)
# define UASM_i_SUBU(buf, rs, rt, rd) uयंत्र_i_subu(buf, rs, rt, rd)
# define UASM_i_SW(buf, rs, rt, off) uयंत्र_i_sw(buf, rs, rt, off)
#पूर्ण_अगर

#घोषणा uयंत्र_i_b(buf, off) uयंत्र_i_beq(buf, 0, 0, off)
#घोषणा uयंत्र_i_beqz(buf, rs, off) uयंत्र_i_beq(buf, rs, 0, off)
#घोषणा uयंत्र_i_beqzl(buf, rs, off) uयंत्र_i_beql(buf, rs, 0, off)
#घोषणा uयंत्र_i_bnez(buf, rs, off) uयंत्र_i_bne(buf, rs, 0, off)
#घोषणा uयंत्र_i_bnezl(buf, rs, off) uयंत्र_i_bnel(buf, rs, 0, off)
#घोषणा uयंत्र_i_ehb(buf) uयंत्र_i_sll(buf, 0, 0, 3)
#घोषणा uयंत्र_i_move(buf, a, b) UASM_i_ADDU(buf, a, 0, b)
#घोषणा uयंत्र_i_nop(buf) uयंत्र_i_sll(buf, 0, 0, 0)
#घोषणा uयंत्र_i_ssnop(buf) uयंत्र_i_sll(buf, 0, 0, 1)

अटल अंतरभूत व्योम uयंत्र_i_drotr_safe(u32 **p, अचिन्हित पूर्णांक a1,
				     अचिन्हित पूर्णांक a2, अचिन्हित पूर्णांक a3)
अणु
	अगर (a3 < 32)
		uयंत्र_i_drotr(p, a1, a2, a3);
	अन्यथा
		uयंत्र_i_drotr32(p, a1, a2, a3 - 32);
पूर्ण

अटल अंतरभूत व्योम uयंत्र_i_dsll_safe(u32 **p, अचिन्हित पूर्णांक a1,
				    अचिन्हित पूर्णांक a2, अचिन्हित पूर्णांक a3)
अणु
	अगर (a3 < 32)
		uयंत्र_i_dsll(p, a1, a2, a3);
	अन्यथा
		uयंत्र_i_dsll32(p, a1, a2, a3 - 32);
पूर्ण

अटल अंतरभूत व्योम uयंत्र_i_dsrl_safe(u32 **p, अचिन्हित पूर्णांक a1,
				    अचिन्हित पूर्णांक a2, अचिन्हित पूर्णांक a3)
अणु
	अगर (a3 < 32)
		uयंत्र_i_dsrl(p, a1, a2, a3);
	अन्यथा
		uयंत्र_i_dsrl32(p, a1, a2, a3 - 32);
पूर्ण

अटल अंतरभूत व्योम uयंत्र_i_dsra_safe(u32 **p, अचिन्हित पूर्णांक a1,
				    अचिन्हित पूर्णांक a2, अचिन्हित पूर्णांक a3)
अणु
	अगर (a3 < 32)
		uयंत्र_i_dsra(p, a1, a2, a3);
	अन्यथा
		uयंत्र_i_dsra32(p, a1, a2, a3 - 32);
पूर्ण

/* Handle relocations. */
काष्ठा uयंत्र_reloc अणु
	u32 *addr;
	अचिन्हित पूर्णांक type;
	पूर्णांक lab;
पूर्ण;

/* This is zero so we can use zeroed label arrays. */
#घोषणा UASM_LABEL_INVALID 0

व्योम uयंत्र_r_mips_pc16(काष्ठा uयंत्र_reloc **rel, u32 *addr, पूर्णांक lid);
व्योम uयंत्र_resolve_relocs(काष्ठा uयंत्र_reloc *rel, काष्ठा uयंत्र_label *lab);
व्योम uयंत्र_move_relocs(काष्ठा uयंत्र_reloc *rel, u32 *first, u32 *end, दीर्घ off);
व्योम uयंत्र_move_labels(काष्ठा uयंत्र_label *lab, u32 *first, u32 *end, दीर्घ off);
व्योम uयंत्र_copy_handler(काष्ठा uयंत्र_reloc *rel, काष्ठा uयंत्र_label *lab,
	u32 *first, u32 *end, u32 *target);
पूर्णांक uयंत्र_insn_has_bdelay(काष्ठा uयंत्र_reloc *rel, u32 *addr);

/* Convenience functions क्रम labeled branches. */
व्योम uयंत्र_il_b(u32 **p, काष्ठा uयंत्र_reloc **r, पूर्णांक lid);
व्योम uयंत्र_il_bbit0(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
		   अचिन्हित पूर्णांक bit, पूर्णांक lid);
व्योम uयंत्र_il_bbit1(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg,
		   अचिन्हित पूर्णांक bit, पूर्णांक lid);
व्योम uयंत्र_il_beq(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक r1,
		 अचिन्हित पूर्णांक r2, पूर्णांक lid);
व्योम uयंत्र_il_beqz(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);
व्योम uयंत्र_il_beqzl(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);
व्योम uयंत्र_il_bgezl(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);
व्योम uयंत्र_il_bgez(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);
व्योम uयंत्र_il_bltz(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);
व्योम uयंत्र_il_bne(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg1,
		 अचिन्हित पूर्णांक reg2, पूर्णांक lid);
व्योम uयंत्र_il_bnez(u32 **p, काष्ठा uयंत्र_reloc **r, अचिन्हित पूर्णांक reg, पूर्णांक lid);

#पूर्ण_अगर /* __ASM_UASM_H */
