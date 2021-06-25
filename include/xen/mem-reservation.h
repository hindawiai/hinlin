<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/*
 * Xen memory reservation utilities.
 *
 * Copyright (c) 2003, B Dragovic
 * Copyright (c) 2003-2004, M Williamson, K Fraser
 * Copyright (c) 2005 Dan M. Smith, IBM Corporation
 * Copyright (c) 2010 Daniel Kiper
 * Copyright (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 */

#अगर_अघोषित _XENMEM_RESERVATION_H
#घोषणा _XENMEM_RESERVATION_H

#समावेश <linux/highस्मृति.स>

#समावेश <xen/page.h>

बाह्य bool xen_scrub_pages;

अटल अंतरभूत व्योम xenmem_reservation_scrub_page(काष्ठा page *page)
अणु
	अगर (xen_scrub_pages)
		clear_highpage(page);
पूर्ण

#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
व्योम __xenmem_reservation_va_mapping_update(अचिन्हित दीर्घ count,
					    काष्ठा page **pages,
					    xen_pfn_t *frames);

व्योम __xenmem_reservation_va_mapping_reset(अचिन्हित दीर्घ count,
					   काष्ठा page **pages);
#पूर्ण_अगर

अटल अंतरभूत व्योम xenmem_reservation_va_mapping_update(अचिन्हित दीर्घ count,
							काष्ठा page **pages,
							xen_pfn_t *frames)
अणु
#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap))
		__xenmem_reservation_va_mapping_update(count, pages, frames);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम xenmem_reservation_va_mapping_reset(अचिन्हित दीर्घ count,
						       काष्ठा page **pages)
अणु
#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
	अगर (!xen_feature(XENFEAT_स्वतः_translated_physmap))
		__xenmem_reservation_va_mapping_reset(count, pages);
#पूर्ण_अगर
पूर्ण

पूर्णांक xenmem_reservation_increase(पूर्णांक count, xen_pfn_t *frames);

पूर्णांक xenmem_reservation_decrease(पूर्णांक count, xen_pfn_t *frames);

#पूर्ण_अगर
