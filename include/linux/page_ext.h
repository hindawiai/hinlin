<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_PAGE_EXT_H
#घोषणा __LINUX_PAGE_EXT_H

#समावेश <linux/types.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/stackdepot.h>

काष्ठा pglist_data;
काष्ठा page_ext_operations अणु
	माप_प्रकार offset;
	माप_प्रकार size;
	bool (*need)(व्योम);
	व्योम (*init)(व्योम);
पूर्ण;

#अगर_घोषित CONFIG_PAGE_EXTENSION

क्रमागत page_ext_flags अणु
	PAGE_EXT_OWNER,
	PAGE_EXT_OWNER_ALLOCATED,
#अगर defined(CONFIG_IDLE_PAGE_TRACKING) && !defined(CONFIG_64BIT)
	PAGE_EXT_YOUNG,
	PAGE_EXT_IDLE,
#पूर्ण_अगर
पूर्ण;

/*
 * Page Extension can be considered as an extended mem_map.
 * A page_ext page is associated with every page descriptor. The
 * page_ext helps us add more inक्रमmation about the page.
 * All page_ext are allocated at boot or memory hotplug event,
 * then the page_ext क्रम pfn always exists.
 */
काष्ठा page_ext अणु
	अचिन्हित दीर्घ flags;
पूर्ण;

बाह्य अचिन्हित दीर्घ page_ext_size;
बाह्य व्योम pgdat_page_ext_init(काष्ठा pglist_data *pgdat);

#अगर_घोषित CONFIG_SPARSEMEM
अटल अंतरभूत व्योम page_ext_init_flaपंचांगem(व्योम)
अणु
पूर्ण
बाह्य व्योम page_ext_init(व्योम);
अटल अंतरभूत व्योम page_ext_init_flaपंचांगem_late(व्योम)
अणु
पूर्ण
#अन्यथा
बाह्य व्योम page_ext_init_flaपंचांगem(व्योम);
बाह्य व्योम page_ext_init_flaपंचांगem_late(व्योम);
अटल अंतरभूत व्योम page_ext_init(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा page_ext *lookup_page_ext(स्थिर काष्ठा page *page);

अटल अंतरभूत काष्ठा page_ext *page_ext_next(काष्ठा page_ext *curr)
अणु
	व्योम *next = curr;
	next += page_ext_size;
	वापस next;
पूर्ण

#अन्यथा /* !CONFIG_PAGE_EXTENSION */
काष्ठा page_ext;

अटल अंतरभूत व्योम pgdat_page_ext_init(काष्ठा pglist_data *pgdat)
अणु
पूर्ण

अटल अंतरभूत काष्ठा page_ext *lookup_page_ext(स्थिर काष्ठा page *page)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम page_ext_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम page_ext_init_flaपंचांगem_late(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम page_ext_init_flaपंचांगem(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PAGE_EXTENSION */
#पूर्ण_अगर /* __LINUX_PAGE_EXT_H */
