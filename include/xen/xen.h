<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _XEN_XEN_H
#घोषणा _XEN_XEN_H

क्रमागत xen_करोमुख्य_type अणु
	XEN_NATIVE,		/* running on bare hardware    */
	XEN_PV_DOMAIN,		/* running in a PV करोमुख्य      */
	XEN_HVM_DOMAIN,		/* running in a Xen hvm करोमुख्य */
पूर्ण;

#अगर_घोषित CONFIG_XEN
बाह्य क्रमागत xen_करोमुख्य_type xen_करोमुख्य_type;
#अन्यथा
#घोषणा xen_करोमुख्य_type		XEN_NATIVE
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_PVH
बाह्य bool xen_pvh;
#अन्यथा
#घोषणा xen_pvh			0
#पूर्ण_अगर

#घोषणा xen_करोमुख्य()		(xen_करोमुख्य_type != XEN_NATIVE)
#घोषणा xen_pv_करोमुख्य()		(xen_करोमुख्य_type == XEN_PV_DOMAIN)
#घोषणा xen_hvm_करोमुख्य()	(xen_करोमुख्य_type == XEN_HVM_DOMAIN)
#घोषणा xen_pvh_करोमुख्य()	(xen_pvh)

#समावेश <linux/types.h>

बाह्य uपूर्णांक32_t xen_start_flags;

#समावेश <xen/पूर्णांकerface/hvm/start_info.h>
बाह्य काष्ठा hvm_start_info pvh_start_info;

#अगर_घोषित CONFIG_XEN_DOM0
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <यंत्र/xen/hypervisor.h>

#घोषणा xen_initial_करोमुख्य()	(xen_करोमुख्य() && \
				 (xen_start_flags & SIF_INITDOMAIN))
#अन्यथा  /* !CONFIG_XEN_DOM0 */
#घोषणा xen_initial_करोमुख्य()	(0)
#पूर्ण_अगर	/* CONFIG_XEN_DOM0 */

काष्ठा bio_vec;
काष्ठा page;

bool xen_biovec_phys_mergeable(स्थिर काष्ठा bio_vec *vec1,
		स्थिर काष्ठा page *page);

#अगर defined(CONFIG_MEMORY_HOTPLUG) && defined(CONFIG_XEN_BALLOON)
बाह्य u64 xen_saved_max_mem_size;
#पूर्ण_अगर

#अगर_घोषित CONFIG_XEN_UNPOPULATED_ALLOC
पूर्णांक xen_alloc_unpopulated_pages(अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages);
व्योम xen_मुक्त_unpopulated_pages(अचिन्हित पूर्णांक nr_pages, काष्ठा page **pages);
#अन्यथा
#घोषणा xen_alloc_unpopulated_pages alloc_xenballooned_pages
#घोषणा xen_मुक्त_unpopulated_pages मुक्त_xenballooned_pages
#समावेश <xen/balloon.h>
#पूर्ण_अगर

#पूर्ण_अगर	/* _XEN_XEN_H */
