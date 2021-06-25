<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_FB_H_
#घोषणा _SPARC_FB_H_
#समावेश <linux/console.h>
#समावेश <linux/fb.h>
#समावेश <linux/fs.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prom.h>

अटल अंतरभूत व्योम fb_pgprotect(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ off)
अणु
#अगर_घोषित CONFIG_SPARC64
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक fb_is_primary_device(काष्ठा fb_info *info)
अणु
	काष्ठा device *dev = info->device;
	काष्ठा device_node *node;

	अगर (console_set_on_cmdline)
		वापस 0;

	node = dev->of_node;
	अगर (node &&
	    node == of_console_device)
		वापस 1;

	वापस 0;
पूर्ण

#पूर्ण_अगर /* _SPARC_FB_H_ */
