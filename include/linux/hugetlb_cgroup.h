<शैली गुरु>
/*
 * Copyright IBM Corporation, 2012
 * Author Aneesh Kumar K.V <aneesh.kumar@linux.vnet.ibm.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2.1 of the GNU Lesser General Public License
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#अगर_अघोषित _LINUX_HUGETLB_CGROUP_H
#घोषणा _LINUX_HUGETLB_CGROUP_H

#समावेश <linux/mmdebug.h>

काष्ठा hugetlb_cgroup;
काष्ठा resv_map;
काष्ठा file_region;

/*
 * Minimum page order trackable by hugetlb cgroup.
 * At least 4 pages are necessary क्रम all the tracking inक्रमmation.
 * The second tail page (hpage[2]) is the fault usage cgroup.
 * The third tail page (hpage[3]) is the reservation usage cgroup.
 */
#घोषणा HUGETLB_CGROUP_MIN_ORDER	2

#अगर_घोषित CONFIG_CGROUP_HUGETLB
क्रमागत hugetlb_memory_event अणु
	HUGETLB_MAX,
	HUGETLB_NR_MEMORY_EVENTS,
पूर्ण;

काष्ठा hugetlb_cgroup अणु
	काष्ठा cgroup_subsys_state css;

	/*
	 * the counter to account क्रम hugepages from hugetlb.
	 */
	काष्ठा page_counter hugepage[HUGE_MAX_HSTATE];

	/*
	 * the counter to account क्रम hugepage reservations from hugetlb.
	 */
	काष्ठा page_counter rsvd_hugepage[HUGE_MAX_HSTATE];

	atomic_दीर्घ_t events[HUGE_MAX_HSTATE][HUGETLB_NR_MEMORY_EVENTS];
	atomic_दीर्घ_t events_local[HUGE_MAX_HSTATE][HUGETLB_NR_MEMORY_EVENTS];

	/* Handle क्रम "hugetlb.events" */
	काष्ठा cgroup_file events_file[HUGE_MAX_HSTATE];

	/* Handle क्रम "hugetlb.events.local" */
	काष्ठा cgroup_file events_local_file[HUGE_MAX_HSTATE];
पूर्ण;

अटल अंतरभूत काष्ठा hugetlb_cgroup *
__hugetlb_cgroup_from_page(काष्ठा page *page, bool rsvd)
अणु
	VM_BUG_ON_PAGE(!PageHuge(page), page);

	अगर (compound_order(page) < HUGETLB_CGROUP_MIN_ORDER)
		वापस शून्य;
	अगर (rsvd)
		वापस (काष्ठा hugetlb_cgroup *)page[3].निजी;
	अन्यथा
		वापस (काष्ठा hugetlb_cgroup *)page[2].निजी;
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *hugetlb_cgroup_from_page(काष्ठा page *page)
अणु
	वापस __hugetlb_cgroup_from_page(page, false);
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *
hugetlb_cgroup_from_page_rsvd(काष्ठा page *page)
अणु
	वापस __hugetlb_cgroup_from_page(page, true);
पूर्ण

अटल अंतरभूत पूर्णांक __set_hugetlb_cgroup(काष्ठा page *page,
				       काष्ठा hugetlb_cgroup *h_cg, bool rsvd)
अणु
	VM_BUG_ON_PAGE(!PageHuge(page), page);

	अगर (compound_order(page) < HUGETLB_CGROUP_MIN_ORDER)
		वापस -1;
	अगर (rsvd)
		page[3].निजी = (अचिन्हित दीर्घ)h_cg;
	अन्यथा
		page[2].निजी = (अचिन्हित दीर्घ)h_cg;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_hugetlb_cgroup(काष्ठा page *page,
				     काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस __set_hugetlb_cgroup(page, h_cg, false);
पूर्ण

अटल अंतरभूत पूर्णांक set_hugetlb_cgroup_rsvd(काष्ठा page *page,
					  काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस __set_hugetlb_cgroup(page, h_cg, true);
पूर्ण

अटल अंतरभूत bool hugetlb_cgroup_disabled(व्योम)
अणु
	वापस !cgroup_subsys_enabled(hugetlb_cgrp_subsys);
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_put_rsvd_cgroup(काष्ठा hugetlb_cgroup *h_cg)
अणु
	css_put(&h_cg->css);
पूर्ण

बाह्य पूर्णांक hugetlb_cgroup_अक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					काष्ठा hugetlb_cgroup **ptr);
बाह्य पूर्णांक hugetlb_cgroup_अक्षरge_cgroup_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					     काष्ठा hugetlb_cgroup **ptr);
बाह्य व्योम hugetlb_cgroup_commit_अक्षरge(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					 काष्ठा hugetlb_cgroup *h_cg,
					 काष्ठा page *page);
बाह्य व्योम hugetlb_cgroup_commit_अक्षरge_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					      काष्ठा hugetlb_cgroup *h_cg,
					      काष्ठा page *page);
बाह्य व्योम hugetlb_cgroup_unअक्षरge_page(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					 काष्ठा page *page);
बाह्य व्योम hugetlb_cgroup_unअक्षरge_page_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					      काष्ठा page *page);

बाह्य व्योम hugetlb_cgroup_unअक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					   काष्ठा hugetlb_cgroup *h_cg);
बाह्य व्योम hugetlb_cgroup_unअक्षरge_cgroup_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
						काष्ठा hugetlb_cgroup *h_cg);
बाह्य व्योम hugetlb_cgroup_unअक्षरge_counter(काष्ठा resv_map *resv,
					    अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end);

बाह्य व्योम hugetlb_cgroup_unअक्षरge_file_region(काष्ठा resv_map *resv,
						काष्ठा file_region *rg,
						अचिन्हित दीर्घ nr_pages,
						bool region_del);

बाह्य व्योम hugetlb_cgroup_file_init(व्योम) __init;
बाह्य व्योम hugetlb_cgroup_migrate(काष्ठा page *oldhpage,
				   काष्ठा page *newhpage);

#अन्यथा
अटल अंतरभूत व्योम hugetlb_cgroup_unअक्षरge_file_region(काष्ठा resv_map *resv,
						       काष्ठा file_region *rg,
						       अचिन्हित दीर्घ nr_pages,
						       bool region_del)
अणु
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *hugetlb_cgroup_from_page(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *
hugetlb_cgroup_from_page_resv(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा hugetlb_cgroup *
hugetlb_cgroup_from_page_rsvd(काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक set_hugetlb_cgroup(काष्ठा page *page,
				     काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक set_hugetlb_cgroup_rsvd(काष्ठा page *page,
					  काष्ठा hugetlb_cgroup *h_cg)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool hugetlb_cgroup_disabled(व्योम)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_put_rsvd_cgroup(काष्ठा hugetlb_cgroup *h_cg)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक hugetlb_cgroup_अक्षरge_cgroup(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
					       काष्ठा hugetlb_cgroup **ptr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक hugetlb_cgroup_अक्षरge_cgroup_rsvd(पूर्णांक idx,
						    अचिन्हित दीर्घ nr_pages,
						    काष्ठा hugetlb_cgroup **ptr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_commit_अक्षरge(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
						काष्ठा hugetlb_cgroup *h_cg,
						काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम
hugetlb_cgroup_commit_अक्षरge_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				  काष्ठा hugetlb_cgroup *h_cg,
				  काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_unअक्षरge_page(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
						काष्ठा page *page)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_unअक्षरge_page_rsvd(पूर्णांक idx,
						     अचिन्हित दीर्घ nr_pages,
						     काष्ठा page *page)
अणु
पूर्ण
अटल अंतरभूत व्योम hugetlb_cgroup_unअक्षरge_cgroup(पूर्णांक idx,
						  अचिन्हित दीर्घ nr_pages,
						  काष्ठा hugetlb_cgroup *h_cg)
अणु
पूर्ण

अटल अंतरभूत व्योम
hugetlb_cgroup_unअक्षरge_cgroup_rsvd(पूर्णांक idx, अचिन्हित दीर्घ nr_pages,
				    काष्ठा hugetlb_cgroup *h_cg)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_unअक्षरge_counter(काष्ठा resv_map *resv,
						   अचिन्हित दीर्घ start,
						   अचिन्हित दीर्घ end)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_file_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम hugetlb_cgroup_migrate(काष्ठा page *oldhpage,
					  काष्ठा page *newhpage)
अणु
पूर्ण

#पूर्ण_अगर  /* CONFIG_MEM_RES_CTLR_HUGETLB */
#पूर्ण_अगर
