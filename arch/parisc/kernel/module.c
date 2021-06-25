<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*    Kernel dynamically loadable module help क्रम PARISC.
 *
 *    The best reference क्रम this stuff is probably the Processor-
 *    Specअगरic ELF Supplement क्रम PA-RISC:
 *        https://parisc.wiki.kernel.org/index.php/File:Elf-pa-hp.pdf
 *
 *    Linux/PA-RISC Project
 *    Copyright (C) 2003 Ranकरोlph Chung <tausq at debian . org>
 *    Copyright (C) 2008 Helge Deller <deller@gmx.de>
 *
 *    Notes:
 *    - PLT stub handling
 *      On 32bit (and someबार 64bit) and with big kernel modules like xfs or
 *      ipv6 the relocation types R_PARISC_PCREL17F and R_PARISC_PCREL22F may
 *      fail to reach their PLT stub अगर we only create one big stub array क्रम
 *      all sections at the beginning of the core or init section.
 *      Instead we now insert inभागidual PLT stub entries directly in front of
 *      of the code sections where the stubs are actually called.
 *      This reduces the distance between the PCREL location and the stub entry
 *      so that the relocations can be fulfilled.
 *      While calculating the final layout of the kernel module in memory, the
 *      kernel module loader calls arch_mod_section_prepend() to request the
 *      to be reserved amount of memory in front of each inभागidual section.
 *
 *    - SEGREL32 handling
 *      We are not करोing SEGREL32 handling correctly. According to the ABI, we
 *      should करो a value offset, like this:
 *			अगर (in_init(me, (व्योम *)val))
 *				val -= (uपूर्णांक32_t)me->init_layout.base;
 *			अन्यथा
 *				val -= (uपूर्णांक32_t)me->core_layout.base;
 *	However, SEGREL32 is used only क्रम PARISC unwind entries, and we want
 *	those entries to have an असलolute address, and not just an offset.
 *
 *	The unwind table mechanism has the ability to specअगरy an offset क्रम
 *	the unwind table; however, because we split off the init functions पूर्णांकo
 *	a dअगरferent piece of memory, it is not possible to करो this using a
 *	single offset. Instead, we use the above hack क्रम now.
 */

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/sections.h>

#घोषणा RELOC_REACHABLE(val, bits) \
	(( ( !((val) & (1<<((bits)-1))) && ((val)>>(bits)) != 0 )  ||	\
	     ( ((val) & (1<<((bits)-1))) && ((val)>>(bits)) != (((__typeof__(val))(~0))>>((bits)+2)))) ? \
	0 : 1)

#घोषणा CHECK_RELOC(val, bits) \
	अगर (!RELOC_REACHABLE(val, bits)) अणु \
		prपूर्णांकk(KERN_ERR "module %s relocation of symbol %s is out of range (0x%lx in %d bits)\n", \
		me->name, strtab + sym->st_name, (अचिन्हित दीर्घ)val, bits); \
		वापस -ENOEXEC;			\
	पूर्ण

/* Maximum number of GOT entries. We use a दीर्घ displacement ldd from
 * the bottom of the table, which has a maximum चिन्हित displacement of
 * 0x3fff; however, since we're only going क्रमward, this becomes
 * 0x1fff, and thus, since each GOT entry is 8 bytes दीर्घ we can have
 * at most 1023 entries.
 * To overcome this 14bit displacement with some kernel modules, we'll
 * use instead the unusal 16bit displacement method (see reassemble_16a)
 * which gives us a maximum positive displacement of 0x7fff, and as such
 * allows us to allocate up to 4095 GOT entries. */
#घोषणा MAX_GOTS	4095

/* three functions to determine where in the module core
 * or init pieces the location is */
अटल अंतरभूत पूर्णांक in_init(काष्ठा module *me, व्योम *loc)
अणु
	वापस (loc >= me->init_layout.base &&
		loc <= (me->init_layout.base + me->init_layout.size));
पूर्ण

अटल अंतरभूत पूर्णांक in_core(काष्ठा module *me, व्योम *loc)
अणु
	वापस (loc >= me->core_layout.base &&
		loc <= (me->core_layout.base + me->core_layout.size));
पूर्ण

अटल अंतरभूत पूर्णांक in_local(काष्ठा module *me, व्योम *loc)
अणु
	वापस in_init(me, loc) || in_core(me, loc);
पूर्ण

#अगर_अघोषित CONFIG_64BIT
काष्ठा got_entry अणु
	Elf32_Addr addr;
पूर्ण;

काष्ठा stub_entry अणु
	Elf32_Word insns[2]; /* each stub entry has two insns */
पूर्ण;
#अन्यथा
काष्ठा got_entry अणु
	Elf64_Addr addr;
पूर्ण;

काष्ठा stub_entry अणु
	Elf64_Word insns[4]; /* each stub entry has four insns */
पूर्ण;
#पूर्ण_अगर

/* Field selection types defined by hppa */
#घोषणा rnd(x)			(((x)+0x1000)&~0x1fff)
/* fsel: full 32 bits */
#घोषणा fsel(v,a)		((v)+(a))
/* lsel: select left 21 bits */
#घोषणा lsel(v,a)		(((v)+(a))>>11)
/* rsel: select right 11 bits */
#घोषणा rsel(v,a)		(((v)+(a))&0x7ff)
/* lrsel with rounding of addend to nearest 8k */
#घोषणा lrsel(v,a)		(((v)+rnd(a))>>11)
/* rrsel with rounding of addend to nearest 8k */
#घोषणा rrsel(v,a)		((((v)+rnd(a))&0x7ff)+((a)-rnd(a)))

#घोषणा mask(x,sz)		((x) & ~((1<<(sz))-1))


/* The reassemble_* functions prepare an immediate value क्रम
   insertion पूर्णांकo an opcode. pa-risc uses all sorts of weird bitfields
   in the inकाष्ठाion to hold the value.  */
अटल अंतरभूत पूर्णांक sign_unext(पूर्णांक x, पूर्णांक len)
अणु
	पूर्णांक len_ones;

	len_ones = (1 << len) - 1;
	वापस x & len_ones;
पूर्ण

अटल अंतरभूत पूर्णांक low_sign_unext(पूर्णांक x, पूर्णांक len)
अणु
	पूर्णांक sign, temp;

	sign = (x >> (len-1)) & 1;
	temp = sign_unext(x, len-1);
	वापस (temp << 1) | sign;
पूर्ण

अटल अंतरभूत पूर्णांक reassemble_14(पूर्णांक as14)
अणु
	वापस (((as14 & 0x1fff) << 1) |
		((as14 & 0x2000) >> 13));
पूर्ण

अटल अंतरभूत पूर्णांक reassemble_16a(पूर्णांक as16)
अणु
	पूर्णांक s, t;

	/* Unusual 16-bit encoding, क्रम wide mode only.  */
	t = (as16 << 1) & 0xffff;
	s = (as16 & 0x8000);
	वापस (t ^ s ^ (s >> 1)) | (s >> 15);
पूर्ण


अटल अंतरभूत पूर्णांक reassemble_17(पूर्णांक as17)
अणु
	वापस (((as17 & 0x10000) >> 16) |
		((as17 & 0x0f800) << 5) |
		((as17 & 0x00400) >> 8) |
		((as17 & 0x003ff) << 3));
पूर्ण

अटल अंतरभूत पूर्णांक reassemble_21(पूर्णांक as21)
अणु
	वापस (((as21 & 0x100000) >> 20) |
		((as21 & 0x0ffe00) >> 8) |
		((as21 & 0x000180) << 7) |
		((as21 & 0x00007c) << 14) |
		((as21 & 0x000003) << 12));
पूर्ण

अटल अंतरभूत पूर्णांक reassemble_22(पूर्णांक as22)
अणु
	वापस (((as22 & 0x200000) >> 21) |
		((as22 & 0x1f0000) << 5) |
		((as22 & 0x00f800) << 5) |
		((as22 & 0x000400) >> 8) |
		((as22 & 0x0003ff) << 3));
पूर्ण

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	/* using RWX means less protection क्रम modules, but it's
	 * easier than trying to map the text, data, init_text and
	 * init_data correctly */
	वापस __vदो_स्मृति_node_range(size, 1, VMALLOC_START, VMALLOC_END,
				    GFP_KERNEL,
				    PAGE_KERNEL_RWX, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण

#अगर_अघोषित CONFIG_64BIT
अटल अंतरभूत अचिन्हित दीर्घ count_gots(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ count_fdescs(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ count_stubs(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ cnt = 0;

	क्रम (; n > 0; n--, rela++)
	अणु
		चयन (ELF32_R_TYPE(rela->r_info)) अणु
			हाल R_PARISC_PCREL17F:
			हाल R_PARISC_PCREL22F:
				cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ count_gots(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ cnt = 0;

	क्रम (; n > 0; n--, rela++)
	अणु
		चयन (ELF64_R_TYPE(rela->r_info)) अणु
			हाल R_PARISC_LTOFF21L:
			हाल R_PARISC_LTOFF14R:
			हाल R_PARISC_PCREL22F:
				cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ count_fdescs(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ cnt = 0;

	क्रम (; n > 0; n--, rela++)
	अणु
		चयन (ELF64_R_TYPE(rela->r_info)) अणु
			हाल R_PARISC_FPTR64:
				cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ count_stubs(स्थिर Elf_Rela *rela, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ cnt = 0;

	क्रम (; n > 0; n--, rela++)
	अणु
		चयन (ELF64_R_TYPE(rela->r_info)) अणु
			हाल R_PARISC_PCREL22F:
				cnt++;
		पूर्ण
	पूर्ण

	वापस cnt;
पूर्ण
#पूर्ण_अगर

व्योम module_arch_मुक्तing_init(काष्ठा module *mod)
अणु
	kमुक्त(mod->arch.section);
	mod->arch.section = शून्य;
पूर्ण

/* Additional bytes needed in front of inभागidual sections */
अचिन्हित पूर्णांक arch_mod_section_prepend(काष्ठा module *mod,
				      अचिन्हित पूर्णांक section)
अणु
	/* size needed क्रम all stubs of this section (including
	 * one additional क्रम correct alignment of the stubs) */
	वापस (mod->arch.section[section].stub_entries + 1)
		* माप(काष्ठा stub_entry);
पूर्ण

#घोषणा CONST
पूर्णांक module_frob_arch_sections(CONST Elf_Ehdr *hdr,
			      CONST Elf_Shdr *sechdrs,
			      CONST अक्षर *secstrings,
			      काष्ठा module *me)
अणु
	अचिन्हित दीर्घ gots = 0, fdescs = 0, len;
	अचिन्हित पूर्णांक i;

	len = hdr->e_shnum * माप(me->arch.section[0]);
	me->arch.section = kzalloc(len, GFP_KERNEL);
	अगर (!me->arch.section)
		वापस -ENOMEM;

	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		स्थिर Elf_Rela *rels = (व्योम *)sechdrs[i].sh_addr;
		अचिन्हित दीर्घ nrels = sechdrs[i].sh_size / माप(*rels);
		अचिन्हित पूर्णांक count, s;

		अगर (म_भेदन(secstrings + sechdrs[i].sh_name,
			    ".PARISC.unwind", 14) == 0)
			me->arch.unwind_section = i;

		अगर (sechdrs[i].sh_type != SHT_RELA)
			जारी;

		/* some of these are not relevant क्रम 32-bit/64-bit
		 * we leave them here to make the code common. the
		 * compiler will करो its thing and optimize out the
		 * stuff we करोn't need
		 */
		gots += count_gots(rels, nrels);
		fdescs += count_fdescs(rels, nrels);

		/* XXX: By sorting the relocs and finding duplicate entries
		 *  we could reduce the number of necessary stubs and save
		 *  some memory. */
		count = count_stubs(rels, nrels);
		अगर (!count)
			जारी;

		/* so we need relocation stubs. reserve necessary memory. */
		/* sh_info gives the section क्रम which we need to add stubs. */
		s = sechdrs[i].sh_info;

		/* each code section should only have one relocation section */
		WARN_ON(me->arch.section[s].stub_entries);

		/* store number of stubs we need क्रम this section */
		me->arch.section[s].stub_entries += count;
	पूर्ण

	/* align things a bit */
	me->core_layout.size = ALIGN(me->core_layout.size, 16);
	me->arch.got_offset = me->core_layout.size;
	me->core_layout.size += gots * माप(काष्ठा got_entry);

	me->core_layout.size = ALIGN(me->core_layout.size, 16);
	me->arch.fdesc_offset = me->core_layout.size;
	me->core_layout.size += fdescs * माप(Elf_Fdesc);

	me->arch.got_max = gots;
	me->arch.fdesc_max = fdescs;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल Elf64_Word get_got(काष्ठा module *me, अचिन्हित दीर्घ value, दीर्घ addend)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा got_entry *got;

	value += addend;

	BUG_ON(value == 0);

	got = me->core_layout.base + me->arch.got_offset;
	क्रम (i = 0; got[i].addr; i++)
		अगर (got[i].addr == value)
			जाओ out;

	BUG_ON(++me->arch.got_count > me->arch.got_max);

	got[i].addr = value;
 out:
	pr_debug("GOT ENTRY %d[%lx] val %lx\n", i, i*माप(काष्ठा got_entry),
	       value);
	वापस i * माप(काष्ठा got_entry);
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

#अगर_घोषित CONFIG_64BIT
अटल Elf_Addr get_fdesc(काष्ठा module *me, अचिन्हित दीर्घ value)
अणु
	Elf_Fdesc *fdesc = me->core_layout.base + me->arch.fdesc_offset;

	अगर (!value) अणु
		prपूर्णांकk(KERN_ERR "%s: zero OPD requested!\n", me->name);
		वापस 0;
	पूर्ण

	/* Look क्रम existing fdesc entry. */
	जबतक (fdesc->addr) अणु
		अगर (fdesc->addr == value)
			वापस (Elf_Addr)fdesc;
		fdesc++;
	पूर्ण

	BUG_ON(++me->arch.fdesc_count > me->arch.fdesc_max);

	/* Create new one */
	fdesc->addr = value;
	fdesc->gp = (Elf_Addr)me->core_layout.base + me->arch.got_offset;
	वापस (Elf_Addr)fdesc;
पूर्ण
#पूर्ण_अगर /* CONFIG_64BIT */

क्रमागत elf_stub_type अणु
	ELF_STUB_GOT,
	ELF_STUB_MILLI,
	ELF_STUB_सूचीECT,
पूर्ण;

अटल Elf_Addr get_stub(काष्ठा module *me, अचिन्हित दीर्घ value, दीर्घ addend,
	क्रमागत elf_stub_type stub_type, Elf_Addr loc0, अचिन्हित पूर्णांक tarमाला_लोec)
अणु
	काष्ठा stub_entry *stub;
	पूर्णांक __maybe_unused d;

	/* initialize stub_offset to poपूर्णांक in front of the section */
	अगर (!me->arch.section[tarमाला_लोec].stub_offset) अणु
		loc0 -= (me->arch.section[tarमाला_लोec].stub_entries + 1) *
				माप(काष्ठा stub_entry);
		/* get correct alignment क्रम the stubs */
		loc0 = ALIGN(loc0, माप(काष्ठा stub_entry));
		me->arch.section[tarमाला_लोec].stub_offset = loc0;
	पूर्ण

	/* get address of stub entry */
	stub = (व्योम *) me->arch.section[tarमाला_लोec].stub_offset;
	me->arch.section[tarमाला_लोec].stub_offset += माप(काष्ठा stub_entry);

	/* करो not ग_लिखो outside available stub area */
	BUG_ON(0 == me->arch.section[tarमाला_लोec].stub_entries--);


#अगर_अघोषित CONFIG_64BIT
/* क्रम 32-bit the stub looks like this:
 * 	ldil L'XXX,%r1
 * 	be,n R'XXX(%sr4,%r1)
 */
	//value = *(अचिन्हित दीर्घ *)((value + addend) & ~3); /* why? */

	stub->insns[0] = 0x20200000;	/* ldil L'XXX,%r1	*/
	stub->insns[1] = 0xe0202002;	/* be,n R'XXX(%sr4,%r1)	*/

	stub->insns[0] |= reassemble_21(lrsel(value, addend));
	stub->insns[1] |= reassemble_17(rrsel(value, addend) / 4);

#अन्यथा
/* क्रम 64-bit we have three kinds of stubs:
 * क्रम normal function calls:
 * 	ldd 0(%dp),%dp
 * 	ldd 10(%dp), %r1
 * 	bve (%r1)
 * 	ldd 18(%dp), %dp
 *
 * क्रम millicode:
 * 	ldil 0, %r1
 * 	lकरो 0(%r1), %r1
 * 	ldd 10(%r1), %r1
 * 	bve,n (%r1)
 *
 * क्रम direct branches (jumps between dअगरferent section of the
 * same module):
 *	ldil 0, %r1
 *	lकरो 0(%r1), %r1
 *	bve,n (%r1)
 */
	चयन (stub_type) अणु
	हाल ELF_STUB_GOT:
		d = get_got(me, value, addend);
		अगर (d <= 15) अणु
			/* Format 5 */
			stub->insns[0] = 0x0f6010db; /* ldd 0(%dp),%dp	*/
			stub->insns[0] |= low_sign_unext(d, 5) << 16;
		पूर्ण अन्यथा अणु
			/* Format 3 */
			stub->insns[0] = 0x537b0000; /* ldd 0(%dp),%dp	*/
			stub->insns[0] |= reassemble_16a(d);
		पूर्ण
		stub->insns[1] = 0x53610020;	/* ldd 10(%dp),%r1	*/
		stub->insns[2] = 0xe820d000;	/* bve (%r1)		*/
		stub->insns[3] = 0x537b0030;	/* ldd 18(%dp),%dp	*/
		अवरोध;
	हाल ELF_STUB_MILLI:
		stub->insns[0] = 0x20200000;	/* ldil 0,%r1		*/
		stub->insns[1] = 0x34210000;	/* lकरो 0(%r1), %r1	*/
		stub->insns[2] = 0x50210020;	/* ldd 10(%r1),%r1	*/
		stub->insns[3] = 0xe820d002;	/* bve,n (%r1)		*/

		stub->insns[0] |= reassemble_21(lrsel(value, addend));
		stub->insns[1] |= reassemble_14(rrsel(value, addend));
		अवरोध;
	हाल ELF_STUB_सूचीECT:
		stub->insns[0] = 0x20200000;    /* ldil 0,%r1           */
		stub->insns[1] = 0x34210000;    /* lकरो 0(%r1), %r1      */
		stub->insns[2] = 0xe820d002;    /* bve,n (%r1)          */

		stub->insns[0] |= reassemble_21(lrsel(value, addend));
		stub->insns[1] |= reassemble_14(rrsel(value, addend));
		अवरोध;
	पूर्ण

#पूर्ण_अगर

	वापस (Elf_Addr)stub;
पूर्ण

#अगर_अघोषित CONFIG_64BIT
पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	पूर्णांक i;
	Elf32_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	Elf32_Word *loc;
	Elf32_Addr val;
	Elf32_Sword addend;
	Elf32_Addr करोt;
	Elf_Addr loc0;
	अचिन्हित पूर्णांक tarमाला_लोec = sechdrs[rअन्यथाc].sh_info;
	//अचिन्हित दीर्घ dp = (अचिन्हित दीर्घ)$global$;
	रेजिस्टर अचिन्हित दीर्घ dp यंत्र ("r27");

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
	       tarमाला_लोec);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		loc = (व्योम *)sechdrs[tarमाला_लोec].sh_addr
		      + rel[i].r_offset;
		/* This is the start of the target section */
		loc0 = sechdrs[tarमाला_लोec].sh_addr;
		/* This is the symbol it is referring to */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);
		अगर (!sym->st_value) अणु
			prपूर्णांकk(KERN_WARNING "%s: Unknown symbol %s\n",
			       me->name, strtab + sym->st_name);
			वापस -ENOENT;
		पूर्ण
		//करोt = (sechdrs[rअन्यथाc].sh_addr + rel->r_offset) & ~0x03;
		करोt =  (Elf32_Addr)loc & ~0x03;

		val = sym->st_value;
		addend = rel[i].r_addend;

#अगर 0
#घोषणा r(t) ELF32_R_TYPE(rel[i].r_info)==t ? #t :
		pr_debug("Symbol %s loc 0x%x val 0x%x addend 0x%x: %s\n",
			strtab + sym->st_name,
			(uपूर्णांक32_t)loc, val, addend,
			r(R_PARISC_PLABEL32)
			r(R_PARISC_सूची32)
			r(R_PARISC_सूची21L)
			r(R_PARISC_सूची14R)
			r(R_PARISC_SEGREL32)
			r(R_PARISC_DPREL21L)
			r(R_PARISC_DPREL14R)
			r(R_PARISC_PCREL17F)
			r(R_PARISC_PCREL22F)
			"UNKNOWN");
#अघोषित r
#पूर्ण_अगर

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_PARISC_PLABEL32:
			/* 32-bit function address */
			/* no function descriptors... */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_सूची32:
			/* direct 32-bit ref */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_सूची21L:
			/* left 21 bits of effective address */
			val = lrsel(val, addend);
			*loc = mask(*loc, 21) | reassemble_21(val);
			अवरोध;
		हाल R_PARISC_सूची14R:
			/* right 14 bits of effective address */
			val = rrsel(val, addend);
			*loc = mask(*loc, 14) | reassemble_14(val);
			अवरोध;
		हाल R_PARISC_SEGREL32:
			/* 32-bit segment relative address */
			/* See note about special handling of SEGREL32 at
			 * the beginning of this file.
			 */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_SECREL32:
			/* 32-bit section relative address. */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_DPREL21L:
			/* left 21 bit of relative address */
			val = lrsel(val - dp, addend);
			*loc = mask(*loc, 21) | reassemble_21(val);
			अवरोध;
		हाल R_PARISC_DPREL14R:
			/* right 14 bit of relative address */
			val = rrsel(val - dp, addend);
			*loc = mask(*loc, 14) | reassemble_14(val);
			अवरोध;
		हाल R_PARISC_PCREL17F:
			/* 17-bit PC relative address */
			/* calculate direct call offset */
			val += addend;
			val = (val - करोt - 8)/4;
			अगर (!RELOC_REACHABLE(val, 17)) अणु
				/* direct distance too far, create
				 * stub entry instead */
				val = get_stub(me, sym->st_value, addend,
					ELF_STUB_सूचीECT, loc0, tarमाला_लोec);
				val = (val - करोt - 8)/4;
				CHECK_RELOC(val, 17);
			पूर्ण
			*loc = (*loc & ~0x1f1ffd) | reassemble_17(val);
			अवरोध;
		हाल R_PARISC_PCREL22F:
			/* 22-bit PC relative address; only defined क्रम pa20 */
			/* calculate direct call offset */
			val += addend;
			val = (val - करोt - 8)/4;
			अगर (!RELOC_REACHABLE(val, 22)) अणु
				/* direct distance too far, create
				 * stub entry instead */
				val = get_stub(me, sym->st_value, addend,
					ELF_STUB_सूचीECT, loc0, tarमाला_लोec);
				val = (val - करोt - 8)/4;
				CHECK_RELOC(val, 22);
			पूर्ण
			*loc = (*loc & ~0x3ff1ffd) | reassemble_22(val);
			अवरोध;
		हाल R_PARISC_PCREL32:
			/* 32-bit PC relative address */
			*loc = val - करोt - 8 + addend;
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_ERR "module %s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	पूर्णांक i;
	Elf64_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf64_Sym *sym;
	Elf64_Word *loc;
	Elf64_Xword *loc64;
	Elf64_Addr val;
	Elf64_Sxword addend;
	Elf64_Addr करोt;
	Elf_Addr loc0;
	अचिन्हित पूर्णांक tarमाला_लोec = sechdrs[rअन्यथाc].sh_info;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
	       tarमाला_लोec);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		loc = (व्योम *)sechdrs[tarमाला_लोec].sh_addr
		      + rel[i].r_offset;
		/* This is the start of the target section */
		loc0 = sechdrs[tarमाला_लोec].sh_addr;
		/* This is the symbol it is referring to */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rel[i].r_info);
		अगर (!sym->st_value) अणु
			prपूर्णांकk(KERN_WARNING "%s: Unknown symbol %s\n",
			       me->name, strtab + sym->st_name);
			वापस -ENOENT;
		पूर्ण
		//करोt = (sechdrs[rअन्यथाc].sh_addr + rel->r_offset) & ~0x03;
		करोt = (Elf64_Addr)loc & ~0x03;
		loc64 = (Elf64_Xword *)loc;

		val = sym->st_value;
		addend = rel[i].r_addend;

#अगर 0
#घोषणा r(t) ELF64_R_TYPE(rel[i].r_info)==t ? #t :
		prपूर्णांकk("Symbol %s loc %p val 0x%Lx addend 0x%Lx: %s\n",
			strtab + sym->st_name,
			loc, val, addend,
			r(R_PARISC_LTOFF14R)
			r(R_PARISC_LTOFF21L)
			r(R_PARISC_PCREL22F)
			r(R_PARISC_सूची64)
			r(R_PARISC_SEGREL32)
			r(R_PARISC_FPTR64)
			"UNKNOWN");
#अघोषित r
#पूर्ण_अगर

		चयन (ELF64_R_TYPE(rel[i].r_info)) अणु
		हाल R_PARISC_LTOFF21L:
			/* LT-relative; left 21 bits */
			val = get_got(me, val, addend);
			pr_debug("LTOFF21L Symbol %s loc %p val %llx\n",
			       strtab + sym->st_name,
			       loc, val);
			val = lrsel(val, 0);
			*loc = mask(*loc, 21) | reassemble_21(val);
			अवरोध;
		हाल R_PARISC_LTOFF14R:
			/* L(ltoff(val+addend)) */
			/* LT-relative; right 14 bits */
			val = get_got(me, val, addend);
			val = rrsel(val, 0);
			pr_debug("LTOFF14R Symbol %s loc %p val %llx\n",
			       strtab + sym->st_name,
			       loc, val);
			*loc = mask(*loc, 14) | reassemble_14(val);
			अवरोध;
		हाल R_PARISC_PCREL22F:
			/* PC-relative; 22 bits */
			pr_debug("PCREL22F Symbol %s loc %p val %llx\n",
			       strtab + sym->st_name,
			       loc, val);
			val += addend;
			/* can we reach it locally? */
			अगर (in_local(me, (व्योम *)val)) अणु
				/* this is the हाल where the symbol is local
				 * to the module, but in a dअगरferent section,
				 * so stub the jump in हाल it's more than 22
				 * bits away */
				val = (val - करोt - 8)/4;
				अगर (!RELOC_REACHABLE(val, 22)) अणु
					/* direct distance too far, create
					 * stub entry instead */
					val = get_stub(me, sym->st_value,
						addend, ELF_STUB_सूचीECT,
						loc0, tarमाला_लोec);
				पूर्ण अन्यथा अणु
					/* Ok, we can reach it directly. */
					val = sym->st_value;
					val += addend;
				पूर्ण
			पूर्ण अन्यथा अणु
				val = sym->st_value;
				अगर (म_भेदन(strtab + sym->st_name, "$$", 2)
				    == 0)
					val = get_stub(me, val, addend, ELF_STUB_MILLI,
						       loc0, tarमाला_लोec);
				अन्यथा
					val = get_stub(me, val, addend, ELF_STUB_GOT,
						       loc0, tarमाला_लोec);
			पूर्ण
			pr_debug("STUB FOR %s loc %px, val %llx+%llx at %llx\n",
			       strtab + sym->st_name, loc, sym->st_value,
			       addend, val);
			val = (val - करोt - 8)/4;
			CHECK_RELOC(val, 22);
			*loc = (*loc & ~0x3ff1ffd) | reassemble_22(val);
			अवरोध;
		हाल R_PARISC_PCREL32:
			/* 32-bit PC relative address */
			*loc = val - करोt - 8 + addend;
			अवरोध;
		हाल R_PARISC_PCREL64:
			/* 64-bit PC relative address */
			*loc64 = val - करोt - 8 + addend;
			अवरोध;
		हाल R_PARISC_सूची64:
			/* 64-bit effective address */
			*loc64 = val + addend;
			अवरोध;
		हाल R_PARISC_SEGREL32:
			/* 32-bit segment relative address */
			/* See note about special handling of SEGREL32 at
			 * the beginning of this file.
			 */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_SECREL32:
			/* 32-bit section relative address. */
			*loc = fsel(val, addend);
			अवरोध;
		हाल R_PARISC_FPTR64:
			/* 64-bit function address */
			अगर(in_local(me, (व्योम *)(val + addend))) अणु
				*loc64 = get_fdesc(me, val+addend);
				pr_debug("FDESC for %s at %llx points to %llx\n",
				       strtab + sym->st_name, *loc64,
				       ((Elf_Fdesc *)*loc64)->addr);
			पूर्ण अन्यथा अणु
				/* अगर the symbol is not local to this
				 * module then val+addend is a poपूर्णांकer
				 * to the function descriptor */
				pr_debug("Non local FPTR64 Symbol %s loc %p val %llx\n",
				       strtab + sym->st_name,
				       loc, val);
				*loc64 = val + addend;
			पूर्ण
			अवरोध;

		शेष:
			prपूर्णांकk(KERN_ERR "module %s: Unknown relocation: %Lu\n",
			       me->name, ELF64_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम
रेजिस्टर_unwind_table(काष्ठा module *me,
		      स्थिर Elf_Shdr *sechdrs)
अणु
	अचिन्हित अक्षर *table, *end;
	अचिन्हित दीर्घ gp;

	अगर (!me->arch.unwind_section)
		वापस;

	table = (अचिन्हित अक्षर *)sechdrs[me->arch.unwind_section].sh_addr;
	end = table + sechdrs[me->arch.unwind_section].sh_size;
	gp = (Elf_Addr)me->core_layout.base + me->arch.got_offset;

	pr_debug("register_unwind_table(), sect = %d at 0x%p - 0x%p (gp=0x%lx)\n",
	       me->arch.unwind_section, table, end, gp);
	me->arch.unwind = unwind_table_add(me->name, 0, gp, table, end);
पूर्ण

अटल व्योम
deरेजिस्टर_unwind_table(काष्ठा module *me)
अणु
	अगर (me->arch.unwind)
		unwind_table_हटाओ(me->arch.unwind);
पूर्ण

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ nsyms;
	स्थिर अक्षर *strtab = शून्य;
	स्थिर Elf_Shdr *s;
	अक्षर *secstrings;
	पूर्णांक symindex = -1;
	Elf_Sym *newptr, *oldptr;
	Elf_Shdr *symhdr = शून्य;
#अगर_घोषित DEBUG
	Elf_Fdesc *entry;
	u32 *addr;

	entry = (Elf_Fdesc *)me->init;
	prपूर्णांकk("FINALIZE, ->init FPTR is %p, GP %lx ADDR %lx\n", entry,
	       entry->gp, entry->addr);
	addr = (u32 *)entry->addr;
	prपूर्णांकk("INSNS: %x %x %x %x\n",
	       addr[0], addr[1], addr[2], addr[3]);
	prपूर्णांकk("got entries used %ld, gots max %ld\n"
	       "fdescs used %ld, fdescs max %ld\n",
	       me->arch.got_count, me->arch.got_max,
	       me->arch.fdesc_count, me->arch.fdesc_max);
#पूर्ण_अगर

	रेजिस्टर_unwind_table(me, sechdrs);

	/* haven't filled in me->symtab yet, so have to find it
	 * ourselves */
	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		अगर(sechdrs[i].sh_type == SHT_SYMTAB
		   && (sechdrs[i].sh_flags & SHF_ALLOC)) अणु
			पूर्णांक strindex = sechdrs[i].sh_link;
			symindex = i;
			/* FIXME: AWFUL HACK
			 * The cast is to drop the स्थिर from
			 * the sechdrs poपूर्णांकer */
			symhdr = (Elf_Shdr *)&sechdrs[i];
			strtab = (अक्षर *)sechdrs[strindex].sh_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	pr_debug("module %s: strtab %p, symhdr %p\n",
	       me->name, strtab, symhdr);

	अगर(me->arch.got_count > MAX_GOTS) अणु
		prपूर्णांकk(KERN_ERR "%s: Global Offset Table overflow (used %ld, allowed %d)\n",
				me->name, me->arch.got_count, MAX_GOTS);
		वापस -EINVAL;
	पूर्ण

	kमुक्त(me->arch.section);
	me->arch.section = शून्य;

	/* no symbol table */
	अगर(symhdr == शून्य)
		वापस 0;

	oldptr = (व्योम *)symhdr->sh_addr;
	newptr = oldptr + 1;	/* we start counting at 1 */
	nsyms = symhdr->sh_size / माप(Elf_Sym);
	pr_debug("OLD num_symtab %lu\n", nsyms);

	क्रम (i = 1; i < nsyms; i++) अणु
		oldptr++;	/* note, count starts at 1 so preincrement */
		अगर(म_भेदन(strtab + oldptr->st_name,
			      ".L", 2) == 0)
			जारी;

		अगर(newptr != oldptr)
			*newptr++ = *oldptr;
		अन्यथा
			newptr++;

	पूर्ण
	nsyms = newptr - (Elf_Sym *)symhdr->sh_addr;
	pr_debug("NEW num_symtab %lu\n", nsyms);
	symhdr->sh_size = nsyms * माप(Elf_Sym);

	/* find .altinकाष्ठाions section */
	secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;
	क्रम (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) अणु
		व्योम *aseg = (व्योम *) s->sh_addr;
		अक्षर *secname = secstrings + s->sh_name;

		अगर (!म_भेद(".altinstructions", secname))
			/* patch .altinकाष्ठाions */
			apply_alternatives(aseg, aseg + s->sh_size, me->name);

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
		/* For 32 bit kernels we're compiling modules with
		 * -ffunction-sections so we must relocate the addresses in the
		 *  ftrace callsite section.
		 */
		अगर (symindex != -1 && !म_भेद(secname, FTRACE_CALLSITE_SECTION)) अणु
			पूर्णांक err;
			अगर (s->sh_type == SHT_REL)
				err = apply_relocate((Elf_Shdr *)sechdrs,
							strtab, symindex,
							s - sechdrs, me);
			अन्यथा अगर (s->sh_type == SHT_RELA)
				err = apply_relocate_add((Elf_Shdr *)sechdrs,
							strtab, symindex,
							s - sechdrs, me);
			अगर (err)
				वापस err;
		पूर्ण
#पूर्ण_अगर
	पूर्ण
	वापस 0;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
	deरेजिस्टर_unwind_table(mod);
पूर्ण

#अगर_घोषित CONFIG_64BIT
व्योम *dereference_module_function_descriptor(काष्ठा module *mod, व्योम *ptr)
अणु
	अचिन्हित दीर्घ start_opd = (Elf64_Addr)mod->core_layout.base +
				   mod->arch.fdesc_offset;
	अचिन्हित दीर्घ end_opd = start_opd +
				mod->arch.fdesc_count * माप(Elf64_Fdesc);

	अगर (ptr < (व्योम *)start_opd || ptr >= (व्योम *)end_opd)
		वापस ptr;

	वापस dereference_function_descriptor(ptr);
पूर्ण
#पूर्ण_अगर
