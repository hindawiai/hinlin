<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MODULELOADER_H
#घोषणा _LINUX_MODULELOADER_H
/* The stuff needed क्रम archs to support modules. */

#समावेश <linux/module.h>
#समावेश <linux/elf.h>

/* These may be implemented by architectures that need to hook पूर्णांकo the
 * module loader code.  Architectures that करोn't need to करो anything special
 * can just rely on the 'weak' शेष hooks defined in kernel/module.c.
 * Note, however, that at least one of apply_relocate or apply_relocate_add
 * must be implemented by each architecture.
 */

/* Adjust arch-specअगरic sections.  Return 0 on success.  */
पूर्णांक module_frob_arch_sections(Elf_Ehdr *hdr,
			      Elf_Shdr *sechdrs,
			      अक्षर *secstrings,
			      काष्ठा module *mod);

/* Additional bytes needed by arch in front of inभागidual sections */
अचिन्हित पूर्णांक arch_mod_section_prepend(काष्ठा module *mod, अचिन्हित पूर्णांक section);

/* Allocator used क्रम allocating काष्ठा module, core sections and init
   sections.  Returns शून्य on failure. */
व्योम *module_alloc(अचिन्हित दीर्घ size);

/* Free memory वापसed from module_alloc. */
व्योम module_memमुक्त(व्योम *module_region);

/* Determines अगर the section name is an init section (that is only used during
 * module loading).
 */
bool module_init_section(स्थिर अक्षर *name);

/* Determines अगर the section name is an निकास section (that is only used during
 * module unloading)
 */
bool module_निकास_section(स्थिर अक्षर *name);

/*
 * Apply the given relocation to the (simplअगरied) ELF.  Return -error
 * or 0.
 */
#अगर_घोषित CONFIG_MODULES_USE_ELF_REL
पूर्णांक apply_relocate(Elf_Shdr *sechdrs,
		   स्थिर अक्षर *strtab,
		   अचिन्हित पूर्णांक symindex,
		   अचिन्हित पूर्णांक rअन्यथाc,
		   काष्ठा module *mod);
#अन्यथा
अटल अंतरभूत पूर्णांक apply_relocate(Elf_Shdr *sechdrs,
				 स्थिर अक्षर *strtab,
				 अचिन्हित पूर्णांक symindex,
				 अचिन्हित पूर्णांक rअन्यथाc,
				 काष्ठा module *me)
अणु
	prपूर्णांकk(KERN_ERR "module %s: REL relocation unsupported\n",
	       module_name(me));
	वापस -ENOEXEC;
पूर्ण
#पूर्ण_अगर

/*
 * Apply the given add relocation to the (simplअगरied) ELF.  Return
 * -error or 0
 */
#अगर_घोषित CONFIG_MODULES_USE_ELF_RELA
पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs,
		       स्थिर अक्षर *strtab,
		       अचिन्हित पूर्णांक symindex,
		       अचिन्हित पूर्णांक rअन्यथाc,
		       काष्ठा module *mod);
#अन्यथा
अटल अंतरभूत पूर्णांक apply_relocate_add(Elf_Shdr *sechdrs,
				     स्थिर अक्षर *strtab,
				     अचिन्हित पूर्णांक symindex,
				     अचिन्हित पूर्णांक rअन्यथाc,
				     काष्ठा module *me)
अणु
	prपूर्णांकk(KERN_ERR "module %s: REL relocation unsupported\n",
	       module_name(me));
	वापस -ENOEXEC;
पूर्ण
#पूर्ण_अगर

/* Any final processing of module beक्रमe access.  Return -error or 0. */
पूर्णांक module_finalize(स्थिर Elf_Ehdr *hdr,
		    स्थिर Elf_Shdr *sechdrs,
		    काष्ठा module *mod);

/* Any cleanup needed when module leaves. */
व्योम module_arch_cleanup(काष्ठा module *mod);

/* Any cleanup beक्रमe मुक्तing mod->module_init */
व्योम module_arch_मुक्तing_init(काष्ठा module *mod);

#अगर (defined(CONFIG_KASAN_GENERIC) || defined(CONFIG_KASAN_SW_TAGS)) && \
		!defined(CONFIG_KASAN_VMALLOC)
#समावेश <linux/kasan.h>
#घोषणा MODULE_ALIGN (PAGE_SIZE << KASAN_SHADOW_SCALE_SHIFT)
#अन्यथा
#घोषणा MODULE_ALIGN PAGE_SIZE
#पूर्ण_अगर

#पूर्ण_अगर
