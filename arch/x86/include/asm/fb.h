<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_FB_H
#घोषणा _ASM_X86_FB_H

#समावेश <linux/fb.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/page.h>

अटल अंतरभूत व्योम fb_pgprotect(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ off)
अणु
	अचिन्हित दीर्घ prot;

	prot = pgprot_val(vma->vm_page_prot) & ~_PAGE_CACHE_MASK;
	अगर (boot_cpu_data.x86 > 3)
		pgprot_val(vma->vm_page_prot) =
			prot | cachemode2protval(_PAGE_CACHE_MODE_UC_MINUS);
पूर्ण

बाह्य पूर्णांक fb_is_primary_device(काष्ठा fb_info *info);

#पूर्ण_अगर /* _ASM_X86_FB_H */
