<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_CRASH_DUMP_H
#घोषणा LINUX_CRASH_DUMP_H

#समावेश <linux/kexec.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/elf.h>
#समावेश <linux/pgtable.h>
#समावेश <uapi/linux/vmcore.h>

#समावेश <linux/pgtable.h> /* क्रम pgprot_t */

#अगर_घोषित CONFIG_CRASH_DUMP
#घोषणा ELFCORE_ADDR_MAX	(-1ULL)
#घोषणा ELFCORE_ADDR_ERR	(-2ULL)

बाह्य अचिन्हित दीर्घ दीर्घ elfcorehdr_addr;
बाह्य अचिन्हित दीर्घ दीर्घ elfcorehdr_size;

बाह्य पूर्णांक elfcorehdr_alloc(अचिन्हित दीर्घ दीर्घ *addr, अचिन्हित दीर्घ दीर्घ *size);
बाह्य व्योम elfcorehdr_मुक्त(अचिन्हित दीर्घ दीर्घ addr);
बाह्य sमाप_प्रकार elfcorehdr_पढ़ो(अक्षर *buf, माप_प्रकार count, u64 *ppos);
बाह्य sमाप_प्रकार elfcorehdr_पढ़ो_notes(अक्षर *buf, माप_प्रकार count, u64 *ppos);
बाह्य पूर्णांक remap_oldmem_pfn_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ from, अचिन्हित दीर्घ pfn,
				  अचिन्हित दीर्घ size, pgprot_t prot);

बाह्य sमाप_प्रकार copy_oldmem_page(अचिन्हित दीर्घ, अक्षर *, माप_प्रकार,
						अचिन्हित दीर्घ, पूर्णांक);
बाह्य sमाप_प्रकार copy_oldmem_page_encrypted(अचिन्हित दीर्घ pfn, अक्षर *buf,
					  माप_प्रकार csize, अचिन्हित दीर्घ offset,
					  पूर्णांक userbuf);

व्योम vmcore_cleanup(व्योम);

/* Architecture code defines this अगर there are other possible ELF
 * machine types, e.g. on bi-arch capable hardware. */
#अगर_अघोषित vmcore_elf_check_arch_cross
#घोषणा vmcore_elf_check_arch_cross(x) 0
#पूर्ण_अगर

/*
 * Architecture code can redefine this अगर there are any special checks
 * needed क्रम 32-bit ELF or 64-bit ELF vmcores.  In हाल of 32-bit
 * only architecture, vmcore_elf64_check_arch can be set to zero.
 */
#अगर_अघोषित vmcore_elf32_check_arch
#घोषणा vmcore_elf32_check_arch(x) elf_check_arch(x)
#पूर्ण_अगर

#अगर_अघोषित vmcore_elf64_check_arch
#घोषणा vmcore_elf64_check_arch(x) (elf_check_arch(x) || vmcore_elf_check_arch_cross(x))
#पूर्ण_अगर

/*
 * is_kdump_kernel() checks whether this kernel is booting after a panic of
 * previous kernel or not. This is determined by checking अगर previous kernel
 * has passed the elf core header address on command line.
 *
 * This is not just a test अगर CONFIG_CRASH_DUMP is enabled or not. It will
 * वापस true अगर CONFIG_CRASH_DUMP=y and अगर kernel is booting after a panic
 * of previous kernel.
 */

अटल अंतरभूत bool is_kdump_kernel(व्योम)
अणु
	वापस elfcorehdr_addr != ELFCORE_ADDR_MAX;
पूर्ण

/* is_vmcore_usable() checks अगर the kernel is booting after a panic and
 * the vmcore region is usable.
 *
 * This makes use of the fact that due to alignment -2ULL is not
 * a valid poपूर्णांकer, much in the vain of IS_ERR(), except
 * dealing directly with an अचिन्हित दीर्घ दीर्घ rather than a poपूर्णांकer.
 */

अटल अंतरभूत पूर्णांक is_vmcore_usable(व्योम)
अणु
	वापस is_kdump_kernel() && elfcorehdr_addr != ELFCORE_ADDR_ERR ? 1 : 0;
पूर्ण

/* vmcore_unusable() marks the vmcore as unusable,
 * without disturbing the logic of is_kdump_kernel()
 */

अटल अंतरभूत व्योम vmcore_unusable(व्योम)
अणु
	अगर (is_kdump_kernel())
		elfcorehdr_addr = ELFCORE_ADDR_ERR;
पूर्ण

#घोषणा HAVE_OLDMEM_PFN_IS_RAM 1
बाह्य पूर्णांक रेजिस्टर_oldmem_pfn_is_ram(पूर्णांक (*fn)(अचिन्हित दीर्घ pfn));
बाह्य व्योम unरेजिस्टर_oldmem_pfn_is_ram(व्योम);

#अन्यथा /* !CONFIG_CRASH_DUMP */
अटल अंतरभूत bool is_kdump_kernel(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_CRASH_DUMP */

/* Device Dump inक्रमmation to be filled by drivers */
काष्ठा vmcoredd_data अणु
	अक्षर dump_name[VMCOREDD_MAX_NAME_BYTES]; /* Unique name of the dump */
	अचिन्हित पूर्णांक size;                       /* Size of the dump */
	/* Driver's रेजिस्टरed callback to be invoked to collect dump */
	पूर्णांक (*vmcoredd_callback)(काष्ठा vmcoredd_data *data, व्योम *buf);
पूर्ण;

#अगर_घोषित CONFIG_PROC_VMCORE_DEVICE_DUMP
पूर्णांक vmcore_add_device_dump(काष्ठा vmcoredd_data *data);
#अन्यथा
अटल अंतरभूत पूर्णांक vmcore_add_device_dump(काष्ठा vmcoredd_data *data)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_VMCORE_DEVICE_DUMP */

#अगर_घोषित CONFIG_PROC_VMCORE
sमाप_प्रकार पढ़ो_from_oldmem(अक्षर *buf, माप_प्रकार count,
			 u64 *ppos, पूर्णांक userbuf,
			 bool encrypted);
#अन्यथा
अटल अंतरभूत sमाप_प्रकार पढ़ो_from_oldmem(अक्षर *buf, माप_प्रकार count,
				       u64 *ppos, पूर्णांक userbuf,
				       bool encrypted)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर /* CONFIG_PROC_VMCORE */

#पूर्ण_अगर /* LINUX_CRASHDUMP_H */
