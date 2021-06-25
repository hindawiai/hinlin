<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*  Kernel module help क्रम x86.
    Copyright (C) 2001 Rusty Russell.

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kasan.h>
#समावेश <linux/bug.h>
#समावेश <linux/mm.h>
#समावेश <linux/gfp.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/memory.h>

#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/unwind.h>

#अगर 0
#घोषणा DEBUGP(fmt, ...)				\
	prपूर्णांकk(KERN_DEBUG fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा DEBUGP(fmt, ...)				\
करो अणु							\
	अगर (0)						\
		prपूर्णांकk(KERN_DEBUG fmt, ##__VA_ARGS__);	\
पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_RANDOMIZE_BASE
अटल अचिन्हित दीर्घ module_load_offset;

/* Mutex protects the module_load_offset. */
अटल DEFINE_MUTEX(module_kaslr_mutex);

अटल अचिन्हित दीर्घ पूर्णांक get_module_load_offset(व्योम)
अणु
	अगर (kaslr_enabled()) अणु
		mutex_lock(&module_kaslr_mutex);
		/*
		 * Calculate the module_load_offset the first समय this
		 * code is called. Once calculated it stays the same until
		 * reboot.
		 */
		अगर (module_load_offset == 0)
			module_load_offset =
				(get_अक्रमom_पूर्णांक() % 1024 + 1) * PAGE_SIZE;
		mutex_unlock(&module_kaslr_mutex);
	पूर्ण
	वापस module_load_offset;
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ पूर्णांक get_module_load_offset(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	व्योम *p;

	अगर (PAGE_ALIGN(size) > MODULES_LEN)
		वापस शून्य;

	p = __vदो_स्मृति_node_range(size, MODULE_ALIGN,
				    MODULES_VADDR + get_module_load_offset(),
				    MODULES_END, GFP_KERNEL,
				    PAGE_KERNEL, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
	अगर (p && (kasan_module_alloc(p, size) < 0)) अणु
		vमुक्त(p);
		वापस शून्य;
	पूर्ण

	वापस p;
पूर्ण

#अगर_घोषित CONFIG_X86_32
पूर्णांक apply_relocate(Elf32_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i;
	Elf32_Rel *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf32_Sym *sym;
	uपूर्णांक32_t *location;

	DEBUGP("Applying relocate section %u to %u\n",
	       rअन्यथाc, sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;
		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf32_Sym *)sechdrs[symindex].sh_addr
			+ ELF32_R_SYM(rel[i].r_info);

		चयन (ELF32_R_TYPE(rel[i].r_info)) अणु
		हाल R_386_32:
			/* We add the value पूर्णांकo the location given */
			*location += sym->st_value;
			अवरोध;
		हाल R_386_PC32:
		हाल R_386_PLT32:
			/* Add the value, subtract its position */
			*location += sym->st_value - (uपूर्णांक32_t)location;
			अवरोध;
		शेष:
			pr_err("%s: Unknown relocation: %u\n",
			       me->name, ELF32_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
#अन्यथा /*X86_64*/
अटल पूर्णांक __apply_relocate_add(Elf64_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me,
		   व्योम *(*ग_लिखो)(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len))
अणु
	अचिन्हित पूर्णांक i;
	Elf64_Rela *rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	Elf64_Sym *sym;
	व्योम *loc;
	u64 val;

	DEBUGP("Applying relocate section %u to %u\n",
	       rअन्यथाc, sechdrs[rअन्यथाc].sh_info);
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / माप(*rel); i++) अणु
		/* This is where to make the change */
		loc = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ rel[i].r_offset;

		/* This is the symbol it is referring to.  Note that all
		   undefined symbols have been resolved.  */
		sym = (Elf64_Sym *)sechdrs[symindex].sh_addr
			+ ELF64_R_SYM(rel[i].r_info);

		DEBUGP("type %d st_value %Lx r_addend %Lx loc %Lx\n",
		       (पूर्णांक)ELF64_R_TYPE(rel[i].r_info),
		       sym->st_value, rel[i].r_addend, (u64)loc);

		val = sym->st_value + rel[i].r_addend;

		चयन (ELF64_R_TYPE(rel[i].r_info)) अणु
		हाल R_X86_64_NONE:
			अवरोध;
		हाल R_X86_64_64:
			अगर (*(u64 *)loc != 0)
				जाओ invalid_relocation;
			ग_लिखो(loc, &val, 8);
			अवरोध;
		हाल R_X86_64_32:
			अगर (*(u32 *)loc != 0)
				जाओ invalid_relocation;
			ग_लिखो(loc, &val, 4);
			अगर (val != *(u32 *)loc)
				जाओ overflow;
			अवरोध;
		हाल R_X86_64_32S:
			अगर (*(s32 *)loc != 0)
				जाओ invalid_relocation;
			ग_लिखो(loc, &val, 4);
			अगर ((s64)val != *(s32 *)loc)
				जाओ overflow;
			अवरोध;
		हाल R_X86_64_PC32:
		हाल R_X86_64_PLT32:
			अगर (*(u32 *)loc != 0)
				जाओ invalid_relocation;
			val -= (u64)loc;
			ग_लिखो(loc, &val, 4);
#अगर 0
			अगर ((s64)val != *(s32 *)loc)
				जाओ overflow;
#पूर्ण_अगर
			अवरोध;
		हाल R_X86_64_PC64:
			अगर (*(u64 *)loc != 0)
				जाओ invalid_relocation;
			val -= (u64)loc;
			ग_लिखो(loc, &val, 8);
			अवरोध;
		शेष:
			pr_err("%s: Unknown rela relocation: %llu\n",
			       me->name, ELF64_R_TYPE(rel[i].r_info));
			वापस -ENOEXEC;
		पूर्ण
	पूर्ण
	वापस 0;

invalid_relocation:
	pr_err("x86/modules: Skipping invalid relocation target, existing value is nonzero for type %d, loc %p, val %Lx\n",
	       (पूर्णांक)ELF64_R_TYPE(rel[i].r_info), loc, val);
	वापस -ENOEXEC;

overflow:
	pr_err("overflow in relocation type %d val %Lx\n",
	       (पूर्णांक)ELF64_R_TYPE(rel[i].r_info), val);
	pr_err("`%s' likely not compiled with -mcmodel=kernel\n",
	       me->name);
	वापस -ENOEXEC;
पूर्ण

पूर्णांक apply_relocate_add(Elf64_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	पूर्णांक ret;
	bool early = me->state == MODULE_STATE_UNFORMED;
	व्योम *(*ग_लिखो)(व्योम *, स्थिर व्योम *, माप_प्रकार) = स_नकल;

	अगर (!early) अणु
		ग_लिखो = text_poke;
		mutex_lock(&text_mutex);
	पूर्ण

	ret = __apply_relocate_add(sechdrs, strtab, symindex, rअन्यथाc, me,
				   ग_लिखो);

	अगर (!early) अणु
		text_poke_sync();
		mutex_unlock(&text_mutex);
	पूर्ण

	वापस ret;
पूर्ण

#पूर्ण_अगर

पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	स्थिर Elf_Shdr *s, *text = शून्य, *alt = शून्य, *locks = शून्य,
		*para = शून्य, *orc = शून्य, *orc_ip = शून्य;
	अक्षर *secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	क्रम (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) अणु
		अगर (!म_भेद(".text", secstrings + s->sh_name))
			text = s;
		अगर (!म_भेद(".altinstructions", secstrings + s->sh_name))
			alt = s;
		अगर (!म_भेद(".smp_locks", secstrings + s->sh_name))
			locks = s;
		अगर (!म_भेद(".parainstructions", secstrings + s->sh_name))
			para = s;
		अगर (!म_भेद(".orc_unwind", secstrings + s->sh_name))
			orc = s;
		अगर (!म_भेद(".orc_unwind_ip", secstrings + s->sh_name))
			orc_ip = s;
	पूर्ण

	अगर (alt) अणु
		/* patch .altinकाष्ठाions */
		व्योम *aseg = (व्योम *)alt->sh_addr;
		apply_alternatives(aseg, aseg + alt->sh_size);
	पूर्ण
	अगर (locks && text) अणु
		व्योम *lseg = (व्योम *)locks->sh_addr;
		व्योम *tseg = (व्योम *)text->sh_addr;
		alternatives_smp_module_add(me, me->name,
					    lseg, lseg + locks->sh_size,
					    tseg, tseg + text->sh_size);
	पूर्ण

	अगर (para) अणु
		व्योम *pseg = (व्योम *)para->sh_addr;
		apply_paravirt(pseg, pseg + para->sh_size);
	पूर्ण

	/* make jump label nops */
	jump_label_apply_nops(me);

	अगर (orc && orc_ip)
		unwind_module_init(me, (व्योम *)orc_ip->sh_addr, orc_ip->sh_size,
				   (व्योम *)orc->sh_addr, orc->sh_size);

	वापस 0;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
	alternatives_smp_module_del(mod);
पूर्ण
