<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 *  Copyright (C) 2001 Rusty Russell.
 *  Copyright (C) 2003, 2004 Ralf Baechle (ralf@linux-mips.org)
 *  Copyright (C) 2005 Thiemo Seufer
 */

#अघोषित DEBUG

#समावेश <linux/extable.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/elf.h>
#समावेश <linux/mm.h>
#समावेश <linux/numa.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jump_label.h>


काष्ठा mips_hi16 अणु
	काष्ठा mips_hi16 *next;
	Elf_Addr *addr;
	Elf_Addr value;
पूर्ण;

अटल LIST_HEAD(dbe_list);
अटल DEFINE_SPINLOCK(dbe_lock);

#अगर_घोषित MODULE_START
व्योम *module_alloc(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, 1, MODULE_START, MODULE_END,
				GFP_KERNEL, PAGE_KERNEL, 0, NUMA_NO_NODE,
				__builtin_वापस_address(0));
पूर्ण
#पूर्ण_अगर

अटल व्योम apply_r_mips_32(u32 *location, u32 base, Elf_Addr v)
अणु
	*location = base + v;
पूर्ण

अटल पूर्णांक apply_r_mips_26(काष्ठा module *me, u32 *location, u32 base,
			   Elf_Addr v)
अणु
	अगर (v % 4) अणु
		pr_err("module %s: dangerous R_MIPS_26 relocation\n",
		       me->name);
		वापस -ENOEXEC;
	पूर्ण

	अगर ((v & 0xf0000000) != (((अचिन्हित दीर्घ)location + 4) & 0xf0000000)) अणु
		pr_err("module %s: relocation overflow\n",
		       me->name);
		वापस -ENOEXEC;
	पूर्ण

	*location = (*location & ~0x03ffffff) |
		    ((base + (v >> 2)) & 0x03ffffff);

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_hi16(काष्ठा module *me, u32 *location, Elf_Addr v,
			     bool rela)
अणु
	काष्ठा mips_hi16 *n;

	अगर (rela) अणु
		*location = (*location & 0xffff0000) |
			    ((((दीर्घ दीर्घ) v + 0x8000LL) >> 16) & 0xffff);
		वापस 0;
	पूर्ण

	/*
	 * We cannot relocate this one now because we करोn't know the value of
	 * the carry we need to add.  Save the inक्रमmation, and let LO16 करो the
	 * actual relocation.
	 */
	n = kदो_स्मृति(माप *n, GFP_KERNEL);
	अगर (!n)
		वापस -ENOMEM;

	n->addr = (Elf_Addr *)location;
	n->value = v;
	n->next = me->arch.r_mips_hi16_list;
	me->arch.r_mips_hi16_list = n;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_relocation_chain(काष्ठा mips_hi16 *l)
अणु
	काष्ठा mips_hi16 *next;

	जबतक (l) अणु
		next = l->next;
		kमुक्त(l);
		l = next;
	पूर्ण
पूर्ण

अटल पूर्णांक apply_r_mips_lo16(काष्ठा module *me, u32 *location,
			     u32 base, Elf_Addr v, bool rela)
अणु
	अचिन्हित दीर्घ insnlo = base;
	काष्ठा mips_hi16 *l;
	Elf_Addr val, vallo;

	अगर (rela) अणु
		*location = (*location & 0xffff0000) | (v & 0xffff);
		वापस 0;
	पूर्ण

	/* Sign extend the addend we extract from the lo insn.	*/
	vallo = ((insnlo & 0xffff) ^ 0x8000) - 0x8000;

	अगर (me->arch.r_mips_hi16_list != शून्य) अणु
		l = me->arch.r_mips_hi16_list;
		जबतक (l != शून्य) अणु
			काष्ठा mips_hi16 *next;
			अचिन्हित दीर्घ insn;

			/*
			 * The value क्रम the HI16 had best be the same.
			 */
			अगर (v != l->value)
				जाओ out_danger;

			/*
			 * Do the HI16 relocation.  Note that we actually करोn't
			 * need to know anything about the LO16 itself, except
			 * where to find the low 16 bits of the addend needed
			 * by the LO16.
			 */
			insn = *l->addr;
			val = ((insn & 0xffff) << 16) + vallo;
			val += v;

			/*
			 * Account क्रम the sign extension that will happen in
			 * the low bits.
			 */
			val = ((val >> 16) + ((val & 0x8000) != 0)) & 0xffff;

			insn = (insn & ~0xffff) | val;
			*l->addr = insn;

			next = l->next;
			kमुक्त(l);
			l = next;
		पूर्ण

		me->arch.r_mips_hi16_list = शून्य;
	पूर्ण

	/*
	 * Ok, we're करोne with the HI16 relocs.	 Now deal with the LO16.
	 */
	val = v + vallo;
	insnlo = (insnlo & ~0xffff) | (val & 0xffff);
	*location = insnlo;

	वापस 0;

out_danger:
	मुक्त_relocation_chain(l);
	me->arch.r_mips_hi16_list = शून्य;

	pr_err("module %s: dangerous R_MIPS_LO16 relocation\n", me->name);

	वापस -ENOEXEC;
पूर्ण

अटल पूर्णांक apply_r_mips_pc(काष्ठा module *me, u32 *location, u32 base,
			   Elf_Addr v, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित दीर्घ mask = GENMASK(bits - 1, 0);
	अचिन्हित दीर्घ se_bits;
	दीर्घ offset;

	अगर (v % 4) अणु
		pr_err("module %s: dangerous R_MIPS_PC%u relocation\n",
		       me->name, bits);
		वापस -ENOEXEC;
	पूर्ण

	/* retrieve & sign extend implicit addend अगर any */
	offset = base & mask;
	offset |= (offset & BIT(bits - 1)) ? ~mask : 0;

	offset += ((दीर्घ)v - (दीर्घ)location) >> 2;

	/* check the sign bit onwards are identical - ie. we didn't overflow */
	se_bits = (offset & BIT(bits - 1)) ? ~0ul : 0;
	अगर ((offset & ~mask) != (se_bits & ~mask)) अणु
		pr_err("module %s: relocation overflow\n", me->name);
		वापस -ENOEXEC;
	पूर्ण

	*location = (*location & ~mask) | (offset & mask);

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_pc16(काष्ठा module *me, u32 *location, u32 base,
			     Elf_Addr v)
अणु
	वापस apply_r_mips_pc(me, location, base, v, 16);
पूर्ण

अटल पूर्णांक apply_r_mips_pc21(काष्ठा module *me, u32 *location, u32 base,
			     Elf_Addr v)
अणु
	वापस apply_r_mips_pc(me, location, base, v, 21);
पूर्ण

अटल पूर्णांक apply_r_mips_pc26(काष्ठा module *me, u32 *location, u32 base,
			     Elf_Addr v)
अणु
	वापस apply_r_mips_pc(me, location, base, v, 26);
पूर्ण

अटल पूर्णांक apply_r_mips_64(u32 *location, Elf_Addr v, bool rela)
अणु
	अगर (WARN_ON(!rela))
		वापस -EINVAL;

	*(Elf_Addr *)location = v;

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_higher(u32 *location, Elf_Addr v, bool rela)
अणु
	अगर (WARN_ON(!rela))
		वापस -EINVAL;

	*location = (*location & 0xffff0000) |
		    ((((दीर्घ दीर्घ)v + 0x80008000LL) >> 32) & 0xffff);

	वापस 0;
पूर्ण

अटल पूर्णांक apply_r_mips_highest(u32 *location, Elf_Addr v, bool rela)
अणु
	अगर (WARN_ON(!rela))
		वापस -EINVAL;

	*location = (*location & 0xffff0000) |
		    ((((दीर्घ दीर्घ)v + 0x800080008000LL) >> 48) & 0xffff);

	वापस 0;
पूर्ण

/**
 * reloc_handler() - Apply a particular relocation to a module
 * @type: type of the relocation to apply
 * @me: the module to apply the reloc to
 * @location: the address at which the reloc is to be applied
 * @base: the existing value at location क्रम REL-style; 0 क्रम RELA-style
 * @v: the value of the reloc, with addend क्रम RELA-style
 * @rela: indication of is this a RELA (true) or REL (false) relocation
 *
 * Each implemented relocation function applies a particular type of
 * relocation to the module @me. Relocs that may be found in either REL or RELA
 * variants can be handled by making use of the @base & @v parameters which are
 * set to values which असलtract the dअगरference away from the particular reloc
 * implementations.
 *
 * Return: 0 upon success, अन्यथा -ERRNO
 */
अटल पूर्णांक reloc_handler(u32 type, काष्ठा module *me, u32 *location, u32 base,
			 Elf_Addr v, bool rela)
अणु
	चयन (type) अणु
	हाल R_MIPS_NONE:
		अवरोध;
	हाल R_MIPS_32:
		apply_r_mips_32(location, base, v);
		अवरोध;
	हाल R_MIPS_26:
		वापस apply_r_mips_26(me, location, base, v);
	हाल R_MIPS_HI16:
		वापस apply_r_mips_hi16(me, location, v, rela);
	हाल R_MIPS_LO16:
		वापस apply_r_mips_lo16(me, location, base, v, rela);
	हाल R_MIPS_PC16:
		वापस apply_r_mips_pc16(me, location, base, v);
	हाल R_MIPS_PC21_S2:
		वापस apply_r_mips_pc21(me, location, base, v);
	हाल R_MIPS_PC26_S2:
		वापस apply_r_mips_pc26(me, location, base, v);
	हाल R_MIPS_64:
		वापस apply_r_mips_64(location, v, rela);
	हाल R_MIPS_HIGHER:
		वापस apply_r_mips_higher(location, v, rela);
	हाल R_MIPS_HIGHEST:
		वापस apply_r_mips_highest(location, v, rela);
	शेष:
		pr_err("%s: Unknown relocation type %u\n", me->name, type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __apply_relocate(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
			    अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
			    काष्ठा module *me, bool rela)
अणु
	जोड़ अणु
		Elf_Mips_Rel *rel;
		Elf_Mips_Rela *rela;
	पूर्ण r;
	Elf_Sym *sym;
	u32 *location, base;
	अचिन्हित पूर्णांक i, type;
	Elf_Addr v;
	पूर्णांक err = 0;
	माप_प्रकार reloc_sz;

	pr_debug("Applying relocate section %u to %u\n", rअन्यथाc,
	       sechdrs[rअन्यथाc].sh_info);

	r.rel = (व्योम *)sechdrs[rअन्यथाc].sh_addr;
	reloc_sz = rela ? माप(*r.rela) : माप(*r.rel);
	me->arch.r_mips_hi16_list = शून्य;
	क्रम (i = 0; i < sechdrs[rअन्यथाc].sh_size / reloc_sz; i++) अणु
		/* This is where to make the change */
		location = (व्योम *)sechdrs[sechdrs[rअन्यथाc].sh_info].sh_addr
			+ r.rel->r_offset;
		/* This is the symbol it is referring to */
		sym = (Elf_Sym *)sechdrs[symindex].sh_addr
			+ ELF_MIPS_R_SYM(*r.rel);
		अगर (sym->st_value >= -MAX_ERRNO) अणु
			/* Ignore unresolved weak symbol */
			अगर (ELF_ST_BIND(sym->st_info) == STB_WEAK)
				जारी;
			pr_warn("%s: Unknown symbol %s\n",
				me->name, strtab + sym->st_name);
			err = -ENOENT;
			जाओ out;
		पूर्ण

		type = ELF_MIPS_R_TYPE(*r.rel);

		अगर (rela) अणु
			v = sym->st_value + r.rela->r_addend;
			base = 0;
			r.rela = &r.rela[1];
		पूर्ण अन्यथा अणु
			v = sym->st_value;
			base = *location;
			r.rel = &r.rel[1];
		पूर्ण

		err = reloc_handler(type, me, location, base, v, rela);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	/*
	 * Normally the hi16 list should be deallocated at this poपूर्णांक. A
	 * malक्रमmed binary however could contain a series of R_MIPS_HI16
	 * relocations not followed by a R_MIPS_LO16 relocation, or अगर we hit
	 * an error processing a reloc we might have gotten here beक्रमe
	 * reaching the R_MIPS_LO16. In either हाल, मुक्त up the list and
	 * वापस an error.
	 */
	अगर (me->arch.r_mips_hi16_list) अणु
		मुक्त_relocation_chain(me->arch.r_mips_hi16_list);
		me->arch.r_mips_hi16_list = शून्य;
		err = err ?: -ENOEXEC;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक apply_relocate(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *me)
अणु
	वापस __apply_relocate(sechdrs, strtab, symindex, rअन्यथाc, me, false);
पूर्ण

#अगर_घोषित CONFIG_MODULES_USE_ELF_RELA
पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs, स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex, अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *me)
अणु
	वापस __apply_relocate(sechdrs, strtab, symindex, rअन्यथाc, me, true);
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES_USE_ELF_RELA */

/* Given an address, look क्रम it in the module exception tables. */
स्थिर काष्ठा exception_table_entry *search_module_dbetables(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ flags;
	स्थिर काष्ठा exception_table_entry *e = शून्य;
	काष्ठा mod_arch_specअगरic *dbe;

	spin_lock_irqsave(&dbe_lock, flags);
	list_क्रम_each_entry(dbe, &dbe_list, dbe_list) अणु
		e = search_extable(dbe->dbe_start,
				   dbe->dbe_end - dbe->dbe_start, addr);
		अगर (e)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&dbe_lock, flags);

	/* Now, अगर we found one, we are running inside it now, hence
	   we cannot unload the module, hence no refcnt needed. */
	वापस e;
पूर्ण

/* Put in dbe list अगर necessary. */
पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *me)
अणु
	स्थिर Elf_Shdr *s;
	अक्षर *secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	/* Make jump label nops. */
	jump_label_apply_nops(me);

	INIT_LIST_HEAD(&me->arch.dbe_list);
	क्रम (s = sechdrs; s < sechdrs + hdr->e_shnum; s++) अणु
		अगर (म_भेद("__dbe_table", secstrings + s->sh_name) != 0)
			जारी;
		me->arch.dbe_start = (व्योम *)s->sh_addr;
		me->arch.dbe_end = (व्योम *)s->sh_addr + s->sh_size;
		spin_lock_irq(&dbe_lock);
		list_add(&me->arch.dbe_list, &dbe_list);
		spin_unlock_irq(&dbe_lock);
	पूर्ण
	वापस 0;
पूर्ण

व्योम module_arch_cleanup(काष्ठा module *mod)
अणु
	spin_lock_irq(&dbe_lock);
	list_del(&mod->arch.dbe_list);
	spin_unlock_irq(&dbe_lock);
पूर्ण
