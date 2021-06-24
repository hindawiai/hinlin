<शैली गुरु>
/*
 * parse_vdso.c: Linux reference vDSO parser
 * Written by Andrew Lutomirski, 2011-2014.
 *
 * This code is meant to be linked in to various programs that run on Linux.
 * As such, it is available with as few restrictions as possible.  This file
 * is licensed under the Creative Commons Zero License, version 1.0,
 * available at http://creativecommons.org/खुलाकरोमुख्य/zero/1.0/legalcode
 *
 * The vDSO is a regular ELF DSO that the kernel maps पूर्णांकo user space when
 * it starts a program.  It works equally well in अटलally and dynamically
 * linked binaries.
 *
 * This code is tested on x86.  In principle it should work on any
 * architecture that has a vDSO.
 */

#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <माला.स>
#समावेश <सीमा.स>
#समावेश <elf.h>

#समावेश "parse_vdso.h"

/* And here's the code. */
#अगर_अघोषित ELF_BITS
# अगर अच_दीर्घ_उच्च > 0xffffffffUL
#  define ELF_BITS 64
# अन्यथा
#  define ELF_BITS 32
# endअगर
#पूर्ण_अगर

#घोषणा ELF_BITS_XFORM2(bits, x) Elf##bits##_##x
#घोषणा ELF_BITS_XFORM(bits, x) ELF_BITS_XFORM2(bits, x)
#घोषणा ELF(x) ELF_BITS_XFORM(ELF_BITS, x)

अटल काष्ठा vdso_info
अणु
	bool valid;

	/* Load inक्रमmation */
	uपूर्णांकptr_t load_addr;
	uपूर्णांकptr_t load_offset;  /* load_addr - recorded vaddr */

	/* Symbol table */
	ELF(Sym) *symtab;
	स्थिर अक्षर *symstrings;
	ELF(Word) *bucket, *chain;
	ELF(Word) nbucket, nchain;

	/* Version table */
	ELF(Versym) *versym;
	ELF(Verdef) *verdef;
पूर्ण vdso_info;

/* Straight from the ELF specअगरication. */
अटल अचिन्हित दीर्घ elf_hash(स्थिर अचिन्हित अक्षर *name)
अणु
	अचिन्हित दीर्घ h = 0, g;
	जबतक (*name)
	अणु
		h = (h << 4) + *name++;
		अगर (g = h & 0xf0000000)
			h ^= g >> 24;
		h &= ~g;
	पूर्ण
	वापस h;
पूर्ण

व्योम vdso_init_from_sysinfo_ehdr(uपूर्णांकptr_t base)
अणु
	माप_प्रकार i;
	bool found_vaddr = false;

	vdso_info.valid = false;

	vdso_info.load_addr = base;

	ELF(Ehdr) *hdr = (ELF(Ehdr)*)base;
	अगर (hdr->e_ident[EI_CLASS] !=
	    (ELF_BITS == 32 ? ELFCLASS32 : ELFCLASS64)) अणु
		वापस;  /* Wrong ELF class -- check ELF_BITS */
	पूर्ण

	ELF(Phdr) *pt = (ELF(Phdr)*)(vdso_info.load_addr + hdr->e_phoff);
	ELF(Dyn) *dyn = 0;

	/*
	 * We need two things from the segment table: the load offset
	 * and the dynamic table.
	 */
	क्रम (i = 0; i < hdr->e_phnum; i++)
	अणु
		अगर (pt[i].p_type == PT_LOAD && !found_vaddr) अणु
			found_vaddr = true;
			vdso_info.load_offset =	base
				+ (uपूर्णांकptr_t)pt[i].p_offset
				- (uपूर्णांकptr_t)pt[i].p_vaddr;
		पूर्ण अन्यथा अगर (pt[i].p_type == PT_DYNAMIC) अणु
			dyn = (ELF(Dyn)*)(base + pt[i].p_offset);
		पूर्ण
	पूर्ण

	अगर (!found_vaddr || !dyn)
		वापस;  /* Failed */

	/*
	 * Fish out the useful bits of the dynamic table.
	 */
	ELF(Word) *hash = 0;
	vdso_info.symstrings = 0;
	vdso_info.symtab = 0;
	vdso_info.versym = 0;
	vdso_info.verdef = 0;
	क्रम (i = 0; dyn[i].d_tag != DT_शून्य; i++) अणु
		चयन (dyn[i].d_tag) अणु
		हाल DT_STRTAB:
			vdso_info.symstrings = (स्थिर अक्षर *)
				((uपूर्णांकptr_t)dyn[i].d_un.d_ptr
				 + vdso_info.load_offset);
			अवरोध;
		हाल DT_SYMTAB:
			vdso_info.symtab = (ELF(Sym) *)
				((uपूर्णांकptr_t)dyn[i].d_un.d_ptr
				 + vdso_info.load_offset);
			अवरोध;
		हाल DT_HASH:
			hash = (ELF(Word) *)
				((uपूर्णांकptr_t)dyn[i].d_un.d_ptr
				 + vdso_info.load_offset);
			अवरोध;
		हाल DT_VERSYM:
			vdso_info.versym = (ELF(Versym) *)
				((uपूर्णांकptr_t)dyn[i].d_un.d_ptr
				 + vdso_info.load_offset);
			अवरोध;
		हाल DT_VERDEF:
			vdso_info.verdef = (ELF(Verdef) *)
				((uपूर्णांकptr_t)dyn[i].d_un.d_ptr
				 + vdso_info.load_offset);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!vdso_info.symstrings || !vdso_info.symtab || !hash)
		वापस;  /* Failed */

	अगर (!vdso_info.verdef)
		vdso_info.versym = 0;

	/* Parse the hash table header. */
	vdso_info.nbucket = hash[0];
	vdso_info.nchain = hash[1];
	vdso_info.bucket = &hash[2];
	vdso_info.chain = &hash[vdso_info.nbucket + 2];

	/* That's all we need. */
	vdso_info.valid = true;
पूर्ण

अटल bool vdso_match_version(ELF(Versym) ver,
			       स्थिर अक्षर *name, ELF(Word) hash)
अणु
	/*
	 * This is a helper function to check अगर the version indexed by
	 * ver matches name (which hashes to hash).
	 *
	 * The version definition table is a mess, and I करोn't know how
	 * to करो this in better than linear समय without allocating memory
	 * to build an index.  I also करोn't know why the table has
	 * variable size entries in the first place.
	 *
	 * For added fun, I can't find a comprehensible specअगरication of how
	 * to parse all the weird flags in the table.
	 *
	 * So I just parse the whole table every समय.
	 */

	/* First step: find the version definition */
	ver &= 0x7fff;  /* Apparently bit 15 means "hidden" */
	ELF(Verdef) *def = vdso_info.verdef;
	जबतक(true) अणु
		अगर ((def->vd_flags & VER_FLG_BASE) == 0
		    && (def->vd_ndx & 0x7fff) == ver)
			अवरोध;

		अगर (def->vd_next == 0)
			वापस false;  /* No definition. */

		def = (ELF(Verdef) *)((अक्षर *)def + def->vd_next);
	पूर्ण

	/* Now figure out whether it matches. */
	ELF(Verdaux) *aux = (ELF(Verdaux)*)((अक्षर *)def + def->vd_aux);
	वापस def->vd_hash == hash
		&& !म_भेद(name, vdso_info.symstrings + aux->vda_name);
पूर्ण

व्योम *vdso_sym(स्थिर अक्षर *version, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ ver_hash;
	अगर (!vdso_info.valid)
		वापस 0;

	ver_hash = elf_hash(version);
	ELF(Word) chain = vdso_info.bucket[elf_hash(name) % vdso_info.nbucket];

	क्रम (; chain != STN_UNDEF; chain = vdso_info.chain[chain]) अणु
		ELF(Sym) *sym = &vdso_info.symtab[chain];

		/* Check क्रम a defined global or weak function w/ right name. */
		अगर (ELF64_ST_TYPE(sym->st_info) != STT_FUNC)
			जारी;
		अगर (ELF64_ST_BIND(sym->st_info) != STB_GLOBAL &&
		    ELF64_ST_BIND(sym->st_info) != STB_WEAK)
			जारी;
		अगर (sym->st_shndx == SHN_UNDEF)
			जारी;
		अगर (म_भेद(name, vdso_info.symstrings + sym->st_name))
			जारी;

		/* Check symbol version. */
		अगर (vdso_info.versym
		    && !vdso_match_version(vdso_info.versym[chain],
					   version, ver_hash))
			जारी;

		वापस (व्योम *)(vdso_info.load_offset + sym->st_value);
	पूर्ण

	वापस 0;
पूर्ण

व्योम vdso_init_from_auxv(व्योम *auxv)
अणु
	ELF(auxv_t) *elf_auxv = auxv;
	क्रम (पूर्णांक i = 0; elf_auxv[i].a_type != AT_शून्य; i++)
	अणु
		अगर (elf_auxv[i].a_type == AT_SYSINFO_EHDR) अणु
			vdso_init_from_sysinfo_ehdr(elf_auxv[i].a_un.a_val);
			वापस;
		पूर्ण
	पूर्ण

	vdso_info.valid = false;
पूर्ण
