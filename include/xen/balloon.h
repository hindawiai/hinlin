<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * Xen balloon functionality
 */
#अगर_अघोषित _XEN_BALLOON_H
#घोषणा _XEN_BALLOON_H

#घोषणा RETRY_UNLIMITED	0

काष्ठा balloon_stats अणु
	/* We aim क्रम 'current allocation' == 'target allocation'. */
	अचिन्हित दीर्घ current_pages;
	अचिन्हित दीर्घ target_pages;
	अचिन्हित दीर्घ target_unpopulated;
	/* Number of pages in high- and low-memory balloons. */
	अचिन्हित दीर्घ balloon_low;
	अचिन्हित दीर्घ balloon_high;
	अचिन्हित दीर्घ total_pages;
	अचिन्हित दीर्घ schedule_delay;
	अचिन्हित दीर्घ max_schedule_delay;
	अचिन्हित दीर्घ retry_count;
	अचिन्हित दीर्घ max_retry_count;
पूर्ण;

बाह्य काष्ठा balloon_stats balloon_stats;

व्योम balloon_set_new_target(अचिन्हित दीर्घ target);

पूर्णांक alloc_xenballooned_pages(पूर्णांक nr_pages, काष्ठा page **pages);
व्योम मुक्त_xenballooned_pages(पूर्णांक nr_pages, काष्ठा page **pages);

#अगर_घोषित CONFIG_XEN_BALLOON
व्योम xen_balloon_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम xen_balloon_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/* _XEN_BALLOON_H */
