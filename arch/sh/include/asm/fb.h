<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FB_H_
#घोषणा _ASM_FB_H_

#समावेश <linux/fb.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/page.h>

अटल अंतरभूत व्योम fb_pgprotect(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ off)
अणु
	vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
पूर्ण

अटल अंतरभूत पूर्णांक fb_is_primary_device(काष्ठा fb_info *info)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _ASM_FB_H_ */
