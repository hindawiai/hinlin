<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FB_H_
#घोषणा _ASM_FB_H_

#समावेश <linux/fb.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_MMU
#अगर_घोषित CONFIG_SUN3
अटल अंतरभूत व्योम fb_pgprotect(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ off)
अणु
	pgprot_val(vma->vm_page_prot) |= SUN3_PAGE_NOCACHE;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम fb_pgprotect(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ off)
अणु
	अगर (CPU_IS_020_OR_030)
		pgprot_val(vma->vm_page_prot) |= _PAGE_NOCACHE030;
	अगर (CPU_IS_040_OR_060) अणु
		pgprot_val(vma->vm_page_prot) &= _CACHEMASK040;
		/* Use no-cache mode, serialized */
		pgprot_val(vma->vm_page_prot) |= _PAGE_NOCACHE_S;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SUN3 */
#अन्यथा
#घोषणा fb_pgprotect(...) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_MMU */

अटल अंतरभूत पूर्णांक fb_is_primary_device(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _ASM_FB_H_ */
