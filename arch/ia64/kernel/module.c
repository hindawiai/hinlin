<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IA-64-specअगरic support क्रम kernel module loader.
 *
 * Copyright (C) 2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * Loosely based on patch by Rusty Russell.
 */

/* relocs tested so far:

   सूची64LSB
   FPTR64LSB
   GPREL22
   LDXMOV
   LDXMOV
   LTOFF22
   LTOFF22X
   LTOFF22X
   LTOFF_FPTR22
   PCREL21B	(क्रम br.call only; br.cond is not supported out of modules!)
   PCREL60B	(क्रम brl.cond only; brl.call is not supported क्रम modules!)
   PCREL64LSB
   SECREL32LSB
   SEGREL64LSB
 */


#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/elf.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/sections.h>

#घोषणा ARCH_MODULE_DEBUG 0

#अगर ARCH_MODULE_DEBUG
# define DEBUGP prपूर्णांकk
# define अंतरभूत
#अन्यथा
# define DEBUGP(fmt , a...)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ITANIUM
# define USE_BRL	0
#अन्यथा
# define USE_BRL	1
#पूर्ण_अगर

#घोषणा MAX_LTOFF	((uपूर्णांक64_t) (1 << 22))	/* max. allowable linkage-table offset */

/* Define some relocation helper macros/types: */

#घोषणा FORMAT_SHIFT	0
#घोषणा FORMAT_BITS	3
#घोषणा FORMAT_MASK	((1 << FORMAT_BITS) - 1)
#घोषणा VALUE_SHIFT	3
#घोषणा VALUE_BITS	5
#घोषणा VALUE_MASK	((1 << VALUE_BITS) - 1)

क्रमागत reloc_target_क्रमmat अणु
	/* direct encoded क्रमmats: */
	RF_NONE = 0,
	RF_INSN14 = 1,
	RF_INSN22 = 2,
	RF_INSN64 = 3,
	RF_32MSB = 4,
	RF_32LSB = 5,
	RF_64MSB = 6,
	RF_64LSB = 7,

	/* क्रमmats that cannot be directly decoded: */
	RF_INSN60,
	RF_INSN21B,	/* imm21 क्रमm 1 */
	RF_INSN21M,	/* imm21 क्रमm 2 */
	RF_INSN21F	/* imm21 क्रमm 3 */
पूर्ण;

क्रमागत reloc_value_क्रमmula अणु
	RV_सूचीECT = 4,		/* S + A */
	RV_GPREL = 5,		/* @gprel(S + A) */
	RV_LTREL = 6,		/* @ltoff(S + A) */
	RV_PLTREL = 7,		/* @pltoff(S + A) */
	RV_FPTR = 8,		/* @fptr(S + A) */
	RV_PCREL = 9,		/* S + A - P */
	RV_LTREL_FPTR = 10,	/* @ltoff(@fptr(S + A)) */
	RV_SEGREL = 11,		/* @segrel(S + A) */
	RV_SECREL = 12,		/* @secrel(S + A) */
	RV_BDREL = 13,		/* BD + A */
	RV_LTV = 14,		/* S + A (like RV_सूचीECT, except frozen at अटल link-समय) */
	RV_PCREL2 = 15,		/* S + A - P */
	RV_SPECIAL = 16,	/* various (see below) */
	RV_RSVD17 = 17,
	RV_TPREL = 18,		/* @tprel(S + A) */
	RV_LTREL_TPREL = 19,	/* @ltoff(@tprel(S + A)) */
	RV_DTPMOD = 20,		/* @dtpmod(S + A) */
	RV_LTREL_DTPMOD = 21,	/* @ltoff(@dtpmod(S + A)) */
	RV_DTPREL = 22,		/* @dtprel(S + A) */
	RV_LTREL_DTPREL = 23,	/* @ltoff(@dtprel(S + A)) */
	RV_RSVD24 = 24,
	RV_RSVD25 = 25,
	RV_RSVD26 = 26,
	RV_RSVD27 = 27
	/* 28-31 reserved क्रम implementation-specअगरic purposes.  */
पूर्ण;

#घोषणा N(reloc)	[R_IA64_##reloc] = #reloc

अटल स्थिर अक्षर *reloc_name[256] = अणु
	N(NONE),		N(IMM14),		N(IMM22),		N(IMM64),
	N(सूची32MSB),		N(सूची32LSB),		N(सूची64MSB),		N(सूची64LSB),
	N(GPREL22),		N(GPREL64I),		N(GPREL32MSB),		N(GPREL32LSB),
	N(GPREL64MSB),		N(GPREL64LSB),		N(LTOFF22),		N(LTOFF64I),
	N(PLTOFF22),		N(PLTOFF64I),		N(PLTOFF64MSB),		N(PLTOFF64LSB),
	N(FPTR64I),		N(FPTR32MSB),		N(FPTR32LSB),		N(FPTR64MSB),
	N(FPTR64LSB),		N(PCREL60B),		N(PCREL21B),		N(PCREL21M),
	N(PCREL21F),		N(PCREL32MSB),		N(PCREL32LSB),		N(PCREL64MSB),
	N(PCREL64LSB),		N(LTOFF_FPTR22),	N(LTOFF_FPTR64I),	N(LTOFF_FPTR32MSB),
	N(LTOFF_FPTR32LSB),	N(LTOFF_FPTR64MSB),	N(LTOFF_FPTR64LSB),	N(SEGREL32MSB),
	N(SEGREL32LSB),		N(SEGREL64MSB),		N(SEGREL64LSB),		N(SECREL32MSB),
	N(SECREL32LSB),		N(SECREL64MSB),		N(SECREL64LSB),		N(REL32MSB),
	N(REL32LSB),		N(REL64MSB),		N(REL64LSB),		N(LTV32MSB),
	N(LTV32LSB),		N(LTV64MSB),		N(LTV64LSB),		N(PCREL21BI),
	N(PCREL22),		N(PCREL64I),		N(IPLTMSB),		N(IPLTLSB),
	N(COPY),		N(LTOFF22X),		N(LDXMOV),		N(TPREL14),
	N(TPREL22),		N(TPREL64I),		N(TPREL64MSB),		N(TPREL64LSB),
	N(LTOFF_TPREL22),	N(DTPMOD64MSB),		N(DTPMOD64LSB),		N(LTOFF_DTPMOD22),
	N(DTPREL14),		N(DTPREL22),		N(DTPREL64I),		N(DTPREL32MSB),
	N(DTPREL32LSB),		N(DTPREL64MSB),		N(DTPREL64LSB),		N(LTOFF_DTPREL22)
पूर्ण;

#अघोषित N

/* Opaque काष्ठा क्रम insns, to protect against derefs. */
काष्ठा insn;

अटल अंतरभूत uपूर्णांक64_t
bundle (स्थिर काष्ठा insn *insn)
अणु
	वापस (uपूर्णांक64_t) insn & ~0xfUL;
पूर्ण

अटल अंतरभूत पूर्णांक
slot (स्थिर काष्ठा insn *insn)
अणु
	वापस (uपूर्णांक64_t) insn & 0x3;
पूर्ण

अटल पूर्णांक
apply_imm64 (काष्ठा module *mod, काष्ठा insn *insn, uपूर्णांक64_t val)
अणु
	अगर (slot(insn) != 1 && slot(insn) != 2) अणु
		prपूर्णांकk(KERN_ERR "%s: invalid slot number %d for IMM64\n",
		       mod->name, slot(insn));
		वापस 0;
	पूर्ण
	ia64_patch_imm64((u64) insn, val);
	वापस 1;
पूर्ण

अटल पूर्णांक
apply_imm60 (काष्ठा module *mod, काष्ठा insn *insn, uपूर्णांक64_t val)
अणु
	अगर (slot(insn) != 1 && slot(insn) != 2) अणु
		prपूर्णांकk(KERN_ERR "%s: invalid slot number %d for IMM60\n",
		       mod->name, slot(insn));
		वापस 0;
	पूर्ण
	अगर (val + ((uपूर्णांक64_t) 1 << 59) >= (1UL << 60)) अणु
		prपूर्णांकk(KERN_ERR "%s: value %ld out of IMM60 range\n",
			mod->name, (दीर्घ) val);
		वापस 0;
	पूर्ण
	ia64_patch_imm60((u64) insn, val);
	वापस 1;
पूर्ण

अटल पूर्णांक
apply_imm22 (काष्ठा module *mod, काष्ठा insn *insn, uपूर्णांक64_t val)
अणु
	अगर (val + (1 << 21) >= (1 << 22)) अणु
		prपूर्णांकk(KERN_ERR "%s: value %li out of IMM22 range\n",
			mod->name, (दीर्घ)val);
		वापस 0;
	पूर्ण
	ia64_patch((u64) insn, 0x01fffcfe000UL, (  ((val & 0x200000UL) << 15) /* bit 21 -> 36 */
					         | ((val & 0x1f0000UL) <<  6) /* bit 16 -> 22 */
					         | ((val & 0x00ff80UL) << 20) /* bit  7 -> 27 */
					         | ((val & 0x00007fUL) << 13) /* bit  0 -> 13 */));
	वापस 1;
पूर्ण

अटल पूर्णांक
apply_imm21b (काष्ठा module *mod, काष्ठा insn *insn, uपूर्णांक64_t val)
अणु
	अगर (val + (1 << 20) >= (1 << 21)) अणु
		prपूर्णांकk(KERN_ERR "%s: value %li out of IMM21b range\n",
			mod->name, (दीर्घ)val);
		वापस 0;
	पूर्ण
	ia64_patch((u64) insn, 0x11ffffe000UL, (  ((val & 0x100000UL) << 16) /* bit 20 -> 36 */
					        | ((val & 0x0fffffUL) << 13) /* bit  0 -> 13 */));
	वापस 1;
पूर्ण

#अगर USE_BRL

काष्ठा plt_entry अणु
	/* Three inकाष्ठाion bundles in PLT. */
 	अचिन्हित अक्षर bundle[2][16];
पूर्ण;

अटल स्थिर काष्ठा plt_entry ia64_plt_ढाँचा = अणु
	अणु
		अणु
			0x04, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0 */
			0x00, 0x00, 0x00, 0x00, 0x00, 0x20, /*	     movl gp=TARGET_GP */
			0x00, 0x00, 0x00, 0x60
		पूर्ण,
		अणु
			0x05, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0 */
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*	     brl.many gp=TARGET_GP */
			0x08, 0x00, 0x00, 0xc0
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक
patch_plt (काष्ठा module *mod, काष्ठा plt_entry *plt, दीर्घ target_ip, अचिन्हित दीर्घ target_gp)
अणु
	अगर (apply_imm64(mod, (काष्ठा insn *) (plt->bundle[0] + 2), target_gp)
	    && apply_imm60(mod, (काष्ठा insn *) (plt->bundle[1] + 2),
			   (target_ip - (पूर्णांक64_t) plt->bundle[1]) / 16))
		वापस 1;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ
plt_target (काष्ठा plt_entry *plt)
अणु
	uपूर्णांक64_t b0, b1, *b = (uपूर्णांक64_t *) plt->bundle[1];
	दीर्घ off;

	b0 = b[0]; b1 = b[1];
	off = (  ((b1 & 0x00fffff000000000UL) >> 36)		/* imm20b -> bit 0 */
	       | ((b0 >> 48) << 20) | ((b1 & 0x7fffffUL) << 36)	/* imm39 -> bit 20 */
	       | ((b1 & 0x0800000000000000UL) << 0));		/* i -> bit 59 */
	वापस (दीर्घ) plt->bundle[1] + 16*off;
पूर्ण

#अन्यथा /* !USE_BRL */

काष्ठा plt_entry अणु
	/* Three inकाष्ठाion bundles in PLT. */
 	अचिन्हित अक्षर bundle[3][16];
पूर्ण;

अटल स्थिर काष्ठा plt_entry ia64_plt_ढाँचा = अणु
	अणु
		अणु
			0x05, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0 */
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /*	     movl r16=TARGET_IP */
			0x02, 0x00, 0x00, 0x60
		पूर्ण,
		अणु
			0x04, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MLX] nop.m 0 */
			0x00, 0x00, 0x00, 0x00, 0x00, 0x20, /*	     movl gp=TARGET_GP */
			0x00, 0x00, 0x00, 0x60
		पूर्ण,
		अणु
			0x11, 0x00, 0x00, 0x00, 0x01, 0x00, /* [MIB] nop.m 0 */
			0x60, 0x80, 0x04, 0x80, 0x03, 0x00, /*	     mov b6=r16 */
			0x60, 0x00, 0x80, 0x00		    /*	     br.few b6 */
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक
patch_plt (काष्ठा module *mod, काष्ठा plt_entry *plt, दीर्घ target_ip, अचिन्हित दीर्घ target_gp)
अणु
	अगर (apply_imm64(mod, (काष्ठा insn *) (plt->bundle[0] + 2), target_ip)
	    && apply_imm64(mod, (काष्ठा insn *) (plt->bundle[1] + 2), target_gp))
		वापस 1;
	वापस 0;
पूर्ण

अचिन्हित दीर्घ
plt_target (काष्ठा plt_entry *plt)
अणु
	uपूर्णांक64_t b0, b1, *b = (uपूर्णांक64_t *) plt->bundle[0];

	b0 = b[0]; b1 = b[1];
	वापस (  ((b1 & 0x000007f000000000) >> 36)		/* imm7b -> bit 0 */
		| ((b1 & 0x07fc000000000000) >> 43)		/* imm9d -> bit 7 */
		| ((b1 & 0x0003e00000000000) >> 29)		/* imm5c -> bit 16 */
		| ((b1 & 0x0000100000000000) >> 23)		/* ic -> bit 21 */
		| ((b0 >> 46) << 22) | ((b1 & 0x7fffff) << 40)	/* imm41 -> bit 22 */
		| ((b1 & 0x0800000000000000) <<  4));		/* i -> bit 63 */
पूर्ण

#पूर्ण_अगर /* !USE_BRL */

व्योम
module_arch_मुक्तing_init (काष्ठा module *mod)
अणु
	अगर (mod->arch.init_unw_table) अणु
		unw_हटाओ_unwind_table(mod->arch.init_unw_table);
		mod->arch.init_unw_table = शून्य;
	पूर्ण
पूर्ण

/* Have we alपढ़ोy seen one of these relocations? */
/* FIXME: we could look in other sections, too --RR */
अटल पूर्णांक
duplicate_reloc (स्थिर Elf64_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num; i++) अणु
		अगर (rela[i].r_info == rela[num].r_info && rela[i].r_addend == rela[num].r_addend)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Count how many GOT entries we may need */
अटल अचिन्हित पूर्णांक
count_gots (स्थिर Elf64_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i, ret = 0;

	/* Sure, this is order(n^2), but it's usually लघु, and not
           समय critical */
	क्रम (i = 0; i < num; i++) अणु
		चयन (ELF64_R_TYPE(rela[i].r_info)) अणु
		      हाल R_IA64_LTOFF22:
		      हाल R_IA64_LTOFF22X:
		      हाल R_IA64_LTOFF64I:
		      हाल R_IA64_LTOFF_FPTR22:
		      हाल R_IA64_LTOFF_FPTR64I:
		      हाल R_IA64_LTOFF_FPTR32MSB:
		      हाल R_IA64_LTOFF_FPTR32LSB:
		      हाल R_IA64_LTOFF_FPTR64MSB:
		      हाल R_IA64_LTOFF_FPTR64LSB:
			अगर (!duplicate_reloc(rela, i))
				ret++;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* Count how many PLT entries we may need */
अटल अचिन्हित पूर्णांक
count_plts (स्थिर Elf64_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i, ret = 0;

	/* Sure, this is order(n^2), but it's usually लघु, and not
           समय critical */
	क्रम (i = 0; i < num; i++) अणु
		चयन (ELF64_R_TYPE(rela[i].r_info)) अणु
		      हाल R_IA64_PCREL21B:
		      हाल R_IA64_PLTOFF22:
		      हाल R_IA64_PLTOFF64I:
		      हाल R_IA64_PLTOFF64MSB:
		      हाल R_IA64_PLTOFF64LSB:
		      हाल R_IA64_IPLTMSB:
		      हाल R_IA64_IPLTLSB:
			अगर (!duplicate_reloc(rela, i))
				ret++;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/* We need to create an function-descriptors क्रम any पूर्णांकernal function
   which is referenced. */
अटल अचिन्हित पूर्णांक
count_fdescs (स्थिर Elf64_Rela *rela, अचिन्हित पूर्णांक num)
अणु
	अचिन्हित पूर्णांक i, ret = 0;

	/* Sure, this is order(n^2), but it's usually लघु, and not समय critical.  */
	क्रम (i = 0; i < num; i++) अणु
		चयन (ELF64_R_TYPE(rela[i].r_info)) अणु
		      हाल R_IA64_FPTR64I:
		      हाल R_IA64_FPTR32LSB:
		      हाल R_IA64_FPTR32MSB:
		      हाल R_IA64_FPTR64LSB:
		      हाल R_IA64_FPTR64MSB:
		      हाल R_IA64_LTOFF_FPTR22:
		      हाल R_IA64_LTOFF_FPTR32LSB:
		      हाल R_IA64_LTOFF_FPTR32MSB:
		      हाल R_IA64_LTOFF_FPTR64I:
		      हाल R_IA64_LTOFF_FPTR64LSB:
		      हाल R_IA64_LTOFF_FPTR64MSB:
		      हाल R_IA64_IPLTMSB:
		      हाल R_IA64_IPLTLSB:
			/*
			 * Jumps to अटल functions someबार go straight to their
			 * offset.  Of course, that may not be possible अगर the jump is
			 * from init -> core or vice. versa, so we need to generate an
			 * FDESC (and PLT etc) क्रम that.
			 */
		      हाल R_IA64_PCREL21B:
			अगर (!duplicate_reloc(rela, i))
				ret++;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक
module_frob_arch_sections (Elf_Ehdr *ehdr, Elf_Shdr *sechdrs, अक्षर *secstrings,
			   काष्ठा module *mod)
अणु
	अचिन्हित दीर्घ core_plts = 0, init_plts = 0, gots = 0, fdescs = 0;
	Elf64_Shdr *s, *sechdrs_end = sechdrs + ehdr->e_shnum;

	/*
	 * To store the PLTs and function-descriptors, we expand the .text section क्रम
	 * core module-code and the .init.text section क्रम initialization code.
	 */
	क्रम (s = sechdrs; s < sechdrs_end; ++s)
		अगर (म_भेद(".core.plt", secstrings + s->sh_name) == 0)
			mod->arch.core_plt = s;
		अन्यथा अगर (म_भेद(".init.plt", secstrings + s->sh_name) == 0)
			mod->arch.init_plt = s;
		अन्यथा अगर (म_भेद(".got", secstrings + s->sh_name) == 0)
			mod->arch.got = s;
		अन्यथा अगर (म_भेद(".opd", secstrings + s->sh_name) == 0)
			mod->arch.opd = s;
		अन्यथा अगर (म_भेद(".IA_64.unwind", secstrings + s->sh_name) == 0)
			mod->arch.unwind = s;

	अगर (!mod->arch.core_plt || !mod->arch.init_plt || !mod->arch.got || !mod->arch.opd) अणु
		prपूर्णांकk(KERN_ERR "%s: sections missing\n", mod->name);
		वापस -ENOEXEC;
	पूर्ण

	/* GOT and PLTs can occur in any relocated section... */
	क्रम (s = sechdrs + 1; s < sechdrs_end; ++s) अणु
		स्थिर Elf64_Rela *rels = (व्योम *)ehdr + s->sh_offset;
		अचिन्हित दीर्घ numrels = s->sh_size/माप(Elf64_Rela);

		अगर (s->sh_type != SHT_RELA)
			जारी;

		gots += count_gots(rels, numrels);
		fdescs += count_fdescs(rels, numrels);
		अगर (म_माला(secstrings + s->sh_name, ".init"))
			init_plts += count_plts(rels, numrels);
		अन्यथा
			core_plts += count_plts(rels, numrels);
	पूर्ण

	mod->arch.core_plt->sh_type = SHT_NOBITS;
	mod->arch.core_plt->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	mod->arch.core_plt->sh_addralign = 16;
	mod->arch.core_plt->sh_size = core_plts * माप(काष्ठा plt_entry);
	mod->arch.init_plt->sh_type = SHT_NOBITS;
	mod->arch.init_plt->sh_flags = SHF_EXECINSTR | SHF_ALLOC;
	mod->arch.init_plt->sh_addralign = 16;
	mod->arch.init_plt->sh_size = init_plts * माप(काष्ठा plt_entry);
	mod->arch.got->sh_type = SHT_NOBITS;
	mod->arch.got->sh_flags = ARCH_SHF_SMALL | SHF_ALLOC;
	mod->arch.got->sh_addralign = 8;
	mod->arch.got->sh_size = gots * माप(काष्ठा got_entry);
	mod->arch.opd->sh_type = SHT_NOBITS;
	mod->arch.opd->sh_flags = SHF_ALLOC;
	mod->arch.opd->sh_addralign = 8;
	mod->arch.opd->sh_size = fdescs * माप(काष्ठा fdesc);
	DEBUGP("%s: core.plt=%lx, init.plt=%lx, got=%lx, fdesc=%lx\n",
	       __func__, mod->arch.core_plt->sh_size, mod->arch.init_plt->sh_size,
	       mod->arch.got->sh_size, mod->arch.opd->sh_size);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
in_init (स्थिर काष्ठा module *mod, uपूर्णांक64_t addr)
अणु
	वापस addr - (uपूर्णांक64_t) mod->init_layout.base < mod->init_layout.size;
पूर्ण

अटल अंतरभूत पूर्णांक
in_core (स्थिर काष्ठा module *mod, uपूर्णांक64_t addr)
अणु
	वापस addr - (uपूर्णांक64_t) mod->core_layout.base < mod->core_layout.size;
पूर्ण

अटल अंतरभूत पूर्णांक
is_पूर्णांकernal (स्थिर काष्ठा module *mod, uपूर्णांक64_t value)
अणु
	वापस in_init(mod, value) || in_core(mod, value);
पूर्ण

/*
 * Get gp-relative offset क्रम the linkage-table entry of VALUE.
 */
अटल uपूर्णांक64_t
get_ltoff (काष्ठा module *mod, uपूर्णांक64_t value, पूर्णांक *okp)
अणु
	काष्ठा got_entry *got, *e;

	अगर (!*okp)
		वापस 0;

	got = (व्योम *) mod->arch.got->sh_addr;
	क्रम (e = got; e < got + mod->arch.next_got_entry; ++e)
		अगर (e->val == value)
			जाओ found;

	/* Not enough GOT entries? */
	BUG_ON(e >= (काष्ठा got_entry *) (mod->arch.got->sh_addr + mod->arch.got->sh_size));

	e->val = value;
	++mod->arch.next_got_entry;
  found:
	वापस (uपूर्णांक64_t) e - mod->arch.gp;
पूर्ण

अटल अंतरभूत पूर्णांक
gp_addressable (काष्ठा module *mod, uपूर्णांक64_t value)
अणु
	वापस value - mod->arch.gp + MAX_LTOFF/2 < MAX_LTOFF;
पूर्ण

/* Get PC-relative PLT entry क्रम this value.  Returns 0 on failure. */
अटल uपूर्णांक64_t
get_plt (काष्ठा module *mod, स्थिर काष्ठा insn *insn, uपूर्णांक64_t value, पूर्णांक *okp)
अणु
	काष्ठा plt_entry *plt, *plt_end;
	uपूर्णांक64_t target_ip, target_gp;

	अगर (!*okp)
		वापस 0;

	अगर (in_init(mod, (uपूर्णांक64_t) insn)) अणु
		plt = (व्योम *) mod->arch.init_plt->sh_addr;
		plt_end = (व्योम *) plt + mod->arch.init_plt->sh_size;
	पूर्ण अन्यथा अणु
		plt = (व्योम *) mod->arch.core_plt->sh_addr;
		plt_end = (व्योम *) plt + mod->arch.core_plt->sh_size;
	पूर्ण

	/* "value" is a poपूर्णांकer to a function-descriptor; fetch the target ip/gp from it: */
	target_ip = ((uपूर्णांक64_t *) value)[0];
	target_gp = ((uपूर्णांक64_t *) value)[1];

	/* Look क्रम existing PLT entry. */
	जबतक (plt->bundle[0][0]) अणु
		अगर (plt_target(plt) == target_ip)
			जाओ found;
		अगर (++plt >= plt_end)
			BUG();
	पूर्ण
	*plt = ia64_plt_ढाँचा;
	अगर (!patch_plt(mod, plt, target_ip, target_gp)) अणु
		*okp = 0;
		वापस 0;
	पूर्ण
#अगर ARCH_MODULE_DEBUG
	अगर (plt_target(plt) != target_ip) अणु
		prपूर्णांकk("%s: mistargeted PLT: wanted %lx, got %lx\n",
		       __func__, target_ip, plt_target(plt));
		*okp = 0;
		वापस 0;
	पूर्ण
#पूर्ण_अगर
  found:
	वापस (uपूर्णांक64_t) plt;
पूर्ण

/* Get function descriptor क्रम VALUE. */
अटल uपूर्णांक64_t
get_fdesc (काष्ठा module *mod, uपूर्णांक64_t value, पूर्णांक *okp)
अणु
	काष्ठा fdesc *fdesc = (व्योम *) mod->arch.opd->sh_addr;

	अगर (!*okp)
		वापस 0;

	अगर (!value) अणु
		prपूर्णांकk(KERN_ERR "%s: fdesc for zero requested!\n", mod->name);
		वापस 0;
	पूर्ण

	अगर (!is_पूर्णांकernal(mod, value))
		/*
		 * If it's not a module-local entry-poपूर्णांक, "value" alपढ़ोy poपूर्णांकs to a
		 * function-descriptor.
		 */
		वापस value;

	/* Look क्रम existing function descriptor. */
	जबतक (fdesc->ip) अणु
		अगर (fdesc->ip == value)
			वापस (uपूर्णांक64_t)fdesc;
		अगर ((uपूर्णांक64_t) ++fdesc >= mod->arch.opd->sh_addr + mod->arch.opd->sh_size)
			BUG();
	पूर्ण

	/* Create new one */
	fdesc->ip = value;
	fdesc->gp = mod->arch.gp;
	वापस (uपूर्णांक64_t) fdesc;
पूर्ण

अटल अंतरभूत पूर्णांक
करो_reloc (काष्ठा module *mod, uपूर्णांक8_t r_type, Elf64_Sym *sym, uपूर्णांक64_t addend,
	  Elf64_Shdr *sec, व्योम *location)
अणु
	क्रमागत reloc_target_क्रमmat क्रमmat = (r_type >> FORMAT_SHIFT) & FORMAT_MASK;
	क्रमागत reloc_value_क्रमmula क्रमmula = (r_type >> VALUE_SHIFT) & VALUE_MASK;
	uपूर्णांक64_t val;
	पूर्णांक ok = 1;

	val = sym->st_value + addend;

	चयन (क्रमmula) अणु
	      हाल RV_SEGREL:	/* segment base is arbitrarily chosen to be 0 क्रम kernel modules */
	      हाल RV_सूचीECT:
		अवरोध;

	      हाल RV_GPREL:	  val -= mod->arch.gp; अवरोध;
	      हाल RV_LTREL:	  val = get_ltoff(mod, val, &ok); अवरोध;
	      हाल RV_PLTREL:	  val = get_plt(mod, location, val, &ok); अवरोध;
	      हाल RV_FPTR:	  val = get_fdesc(mod, val, &ok); अवरोध;
	      हाल RV_SECREL:	  val -= sec->sh_addr; अवरोध;
	      हाल RV_LTREL_FPTR: val = get_ltoff(mod, get_fdesc(mod, val, &ok), &ok); अवरोध;

	      हाल RV_PCREL:
		चयन (r_type) अणु
		      हाल R_IA64_PCREL21B:
			अगर ((in_init(mod, val) && in_core(mod, (uपूर्णांक64_t)location)) ||
			    (in_core(mod, val) && in_init(mod, (uपूर्णांक64_t)location))) अणु
				/*
				 * Init section may have been allocated far away from core,
				 * अगर the branch won't reach, then allocate a plt क्रम it.
				 */
				uपूर्णांक64_t delta = ((पूर्णांक64_t)val - (पूर्णांक64_t)location) / 16;
				अगर (delta + (1 << 20) >= (1 << 21)) अणु
					val = get_fdesc(mod, val, &ok);
					val = get_plt(mod, location, val, &ok);
				पूर्ण
			पूर्ण अन्यथा अगर (!is_पूर्णांकernal(mod, val))
				val = get_plt(mod, location, val, &ok);
			fallthrough;
		      शेष:
			val -= bundle(location);
			अवरोध;

		      हाल R_IA64_PCREL32MSB:
		      हाल R_IA64_PCREL32LSB:
		      हाल R_IA64_PCREL64MSB:
		      हाल R_IA64_PCREL64LSB:
			val -= (uपूर्णांक64_t) location;
			अवरोध;

		पूर्ण
		चयन (r_type) अणु
		      हाल R_IA64_PCREL60B: क्रमmat = RF_INSN60; अवरोध;
		      हाल R_IA64_PCREL21B: क्रमmat = RF_INSN21B; अवरोध;
		      हाल R_IA64_PCREL21M: क्रमmat = RF_INSN21M; अवरोध;
		      हाल R_IA64_PCREL21F: क्रमmat = RF_INSN21F; अवरोध;
		      शेष: अवरोध;
		पूर्ण
		अवरोध;

	      हाल RV_BDREL:
		val -= (uपूर्णांक64_t) (in_init(mod, val) ? mod->init_layout.base : mod->core_layout.base);
		अवरोध;

	      हाल RV_LTV:
		/* can link-समय value relocs happen here?  */
		BUG();
		अवरोध;

	      हाल RV_PCREL2:
		अगर (r_type == R_IA64_PCREL21BI) अणु
			अगर (!is_पूर्णांकernal(mod, val)) अणु
				prपूर्णांकk(KERN_ERR "%s: %s reloc against "
					"non-local symbol (%lx)\n", __func__,
					reloc_name[r_type], (अचिन्हित दीर्घ)val);
				वापस -ENOEXEC;
			पूर्ण
			क्रमmat = RF_INSN21B;
		पूर्ण
		val -= bundle(location);
		अवरोध;

	      हाल RV_SPECIAL:
		चयन (r_type) अणु
		      हाल R_IA64_IPLTMSB:
		      हाल R_IA64_IPLTLSB:
			val = get_fdesc(mod, get_plt(mod, location, val, &ok), &ok);
			क्रमmat = RF_64LSB;
			अगर (r_type == R_IA64_IPLTMSB)
				क्रमmat = RF_64MSB;
			अवरोध;

		      हाल R_IA64_SUB:
			val = addend - sym->st_value;
			क्रमmat = RF_INSN64;
			अवरोध;

		      हाल R_IA64_LTOFF22X:
			अगर (gp_addressable(mod, val))
				val -= mod->arch.gp;
			अन्यथा
				val = get_ltoff(mod, val, &ok);
			क्रमmat = RF_INSN22;
			अवरोध;

		      हाल R_IA64_LDXMOV:
			अगर (gp_addressable(mod, val)) अणु
				/* turn "ld8" पूर्णांकo "mov": */
				DEBUGP("%s: patching ld8 at %p to mov\n", __func__, location);
				ia64_patch((u64) location, 0x1fff80fe000UL, 0x10000000000UL);
			पूर्ण
			वापस 0;

		      शेष:
			अगर (reloc_name[r_type])
				prपूर्णांकk(KERN_ERR "%s: special reloc %s not supported",
				       mod->name, reloc_name[r_type]);
			अन्यथा
				prपूर्णांकk(KERN_ERR "%s: unknown special reloc %x\n",
				       mod->name, r_type);
			वापस -ENOEXEC;
		पूर्ण
		अवरोध;

	      हाल RV_TPREL:
	      हाल RV_LTREL_TPREL:
	      हाल RV_DTPMOD:
	      हाल RV_LTREL_DTPMOD:
	      हाल RV_DTPREL:
	      हाल RV_LTREL_DTPREL:
		prपूर्णांकk(KERN_ERR "%s: %s reloc not supported\n",
		       mod->name, reloc_name[r_type] ? reloc_name[r_type] : "?");
		वापस -ENOEXEC;

	      शेष:
		prपूर्णांकk(KERN_ERR "%s: unknown reloc %x\n", mod->name, r_type);
		वापस -ENOEXEC;
	पूर्ण

	अगर (!ok)
		वापस -ENOEXEC;

	DEBUGP("%s: [%p]<-%016lx = %s(%lx)\n", __func__, location, val,
	       reloc_name[r_type] ? reloc_name[r_type] : "?", sym->st_value + addend);

	चयन (क्रमmat) अणु
	      हाल RF_INSN21B:	ok = apply_imm21b(mod, location, (पूर्णांक64_t) val / 16); अवरोध;
	      हाल RF_INSN22:	ok = apply_imm22(mod, location, val); अवरोध;
	      हाल RF_INSN64:	ok = apply_imm64(mod, location, val); अवरोध;
	      हाल RF_INSN60:	ok = apply_imm60(mod, location, (पूर्णांक64_t) val / 16); अवरोध;
	      हाल RF_32LSB:	put_unaligned(val, (uपूर्णांक32_t *) location); अवरोध;
	      हाल RF_64LSB:	put_unaligned(val, (uपूर्णांक64_t *) location); अवरोध;
	      हाल RF_32MSB:	/* ia64 Linux is little-endian... */
	      हाल RF_64MSB:	/* ia64 Linux is little-endian... */
	      हाल RF_INSN14:	/* must be within-module, i.e., resolved by "ld -r" */
	      हाल RF_INSN21M:	/* must be within-module, i.e., resolved by "ld -r" */
	      हाल RF_INSN21F:	/* must be within-module, i.e., resolved by "ld -r" */
		prपूर्णांकk(KERN_ERR "%s: format %u needed by %s reloc is not supported\n",
		       mod->name, क्रमmat, reloc_name[r_type] ? reloc_name[r_type] : "?");
		वापस -ENOEXEC;

	      शेष:
		prपूर्णांकk(KERN_ERR "%s: relocation %s resulted in unknown format %u\n",
		       mod->name, reloc_name[r_type] ? reloc_name[r_type] : "?", क्रमmat);
		वापस -ENOEXEC;
	पूर्ण
	वापस ok ? 0 : -ENOEXEC;
पूर्ण

पूर्णांक
apply_relocate_add (Elf64_Shdr *sechdrs, स्थिर अक्षर *strtab, अचिन्हित पूर्णांक symindex,
		    अचिन्हित पूर्णांक rअन्यथाc, काष्ठा module *mod)
अणु
	अचिन्हित पूर्णांक i, n = sechdrs[rअन्यथाc].sh_size / माप(Elf64_Rela);
	Elf64_Rela *rela = (व्योम *) sechdrs[rअन्यथाc].sh_addr;
	Elf64_Shdr *target_sec;
	पूर्णांक ret;

	DEBUGP("%s: applying section %u (%u relocs) to %u\n", __func__,
	       rअन्यथाc, n, sechdrs[rअन्यथाc].sh_info);

	target_sec = sechdrs + sechdrs[rअन्यथाc].sh_info;

	अगर (target_sec->sh_entsize == ~0UL)
		/*
		 * If target section wasn't allocated, we don't need to relocate it.
		 * Happens, e.g., क्रम debug sections.
		 */
		वापस 0;

	अगर (!mod->arch.gp) अणु
		/*
		 * XXX Should have an arch-hook क्रम running this after final section
		 *     addresses have been selected...
		 */
		uपूर्णांक64_t gp;
		अगर (mod->core_layout.size > MAX_LTOFF)
			/*
			 * This takes advantage of fact that SHF_ARCH_SMALL माला_लो allocated
			 * at the end of the module.
			 */
			gp = mod->core_layout.size - MAX_LTOFF / 2;
		अन्यथा
			gp = mod->core_layout.size / 2;
		gp = (uपूर्णांक64_t) mod->core_layout.base + ((gp + 7) & -8);
		mod->arch.gp = gp;
		DEBUGP("%s: placing gp at 0x%lx\n", __func__, gp);
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		ret = करो_reloc(mod, ELF64_R_TYPE(rela[i].r_info),
			       ((Elf64_Sym *) sechdrs[symindex].sh_addr
				+ ELF64_R_SYM(rela[i].r_info)),
			       rela[i].r_addend, target_sec,
			       (व्योम *) target_sec->sh_addr + rela[i].r_offset);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Modules contain a single unwind table which covers both the core and the init text
 * sections but since the two are not contiguous, we need to split this table up such that
 * we can रेजिस्टर (and unरेजिस्टर) each "segment" separately.  Fortunately, this sounds
 * more complicated than it really is.
 */
अटल व्योम
रेजिस्टर_unwind_table (काष्ठा module *mod)
अणु
	काष्ठा unw_table_entry *start = (व्योम *) mod->arch.unwind->sh_addr;
	काष्ठा unw_table_entry *end = start + mod->arch.unwind->sh_size / माप (*start);
	काष्ठा unw_table_entry पंचांगp, *e1, *e2, *core, *init;
	अचिन्हित दीर्घ num_init = 0, num_core = 0;

	/* First, count how many init and core unwind-table entries there are.  */
	क्रम (e1 = start; e1 < end; ++e1)
		अगर (in_init(mod, e1->start_offset))
			++num_init;
		अन्यथा
			++num_core;
	/*
	 * Second, sort the table such that all unwind-table entries क्रम the init and core
	 * text sections are nicely separated.  We करो this with a stupid bubble sort
	 * (unwind tables करोn't get ridiculously huge).
	 */
	क्रम (e1 = start; e1 < end; ++e1) अणु
		क्रम (e2 = e1 + 1; e2 < end; ++e2) अणु
			अगर (e2->start_offset < e1->start_offset) अणु
				पंचांगp = *e1;
				*e1 = *e2;
				*e2 = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Third, locate the init and core segments in the unwind table:
	 */
	अगर (in_init(mod, start->start_offset)) अणु
		init = start;
		core = start + num_init;
	पूर्ण अन्यथा अणु
		core = start;
		init = start + num_core;
	पूर्ण

	DEBUGP("%s: name=%s, gp=%lx, num_init=%lu, num_core=%lu\n", __func__,
	       mod->name, mod->arch.gp, num_init, num_core);

	/*
	 * Fourth, रेजिस्टर both tables (अगर not empty).
	 */
	अगर (num_core > 0) अणु
		mod->arch.core_unw_table = unw_add_unwind_table(mod->name, 0, mod->arch.gp,
								core, core + num_core);
		DEBUGP("%s:  core: handle=%p [%p-%p)\n", __func__,
		       mod->arch.core_unw_table, core, core + num_core);
	पूर्ण
	अगर (num_init > 0) अणु
		mod->arch.init_unw_table = unw_add_unwind_table(mod->name, 0, mod->arch.gp,
								init, init + num_init);
		DEBUGP("%s:  init: handle=%p [%p-%p)\n", __func__,
		       mod->arch.init_unw_table, init, init + num_init);
	पूर्ण
पूर्ण

पूर्णांक
module_finalize (स्थिर Elf_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs, काष्ठा module *mod)
अणु
	काष्ठा mod_arch_specअगरic *mas = &mod->arch;

	DEBUGP("%s: init: entry=%p\n", __func__, mod->init);
	अगर (mas->unwind)
		रेजिस्टर_unwind_table(mod);

	/*
	 * ".opd" was alपढ़ोy relocated to the final destination. Store
	 * it's address क्रम use in symbolizer.
	 */
	mas->opd_addr = (व्योम *)mas->opd->sh_addr;
	mas->opd_size = mas->opd->sh_size;

	/*
	 * Module relocation was alपढ़ोy करोne at this poपूर्णांक. Section
	 * headers are about to be deleted. Wipe out load-समय context.
	 */
	mas->core_plt = शून्य;
	mas->init_plt = शून्य;
	mas->got = शून्य;
	mas->opd = शून्य;
	mas->unwind = शून्य;
	mas->gp = 0;
	mas->next_got_entry = 0;

	वापस 0;
पूर्ण

व्योम
module_arch_cleanup (काष्ठा module *mod)
अणु
	अगर (mod->arch.init_unw_table) अणु
		unw_हटाओ_unwind_table(mod->arch.init_unw_table);
		mod->arch.init_unw_table = शून्य;
	पूर्ण
	अगर (mod->arch.core_unw_table) अणु
		unw_हटाओ_unwind_table(mod->arch.core_unw_table);
		mod->arch.core_unw_table = शून्य;
	पूर्ण
पूर्ण

व्योम *dereference_module_function_descriptor(काष्ठा module *mod, व्योम *ptr)
अणु
	काष्ठा mod_arch_specअगरic *mas = &mod->arch;

	अगर (ptr < mas->opd_addr || ptr >= mas->opd_addr + mas->opd_size)
		वापस ptr;

	वापस dereference_function_descriptor(ptr);
पूर्ण
