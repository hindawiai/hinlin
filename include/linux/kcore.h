<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * /proc/kcore definitions
 */
#अगर_अघोषित _LINUX_KCORE_H
#घोषणा _LINUX_KCORE_H

क्रमागत kcore_type अणु
	KCORE_TEXT,
	KCORE_VMALLOC,
	KCORE_RAM,
	KCORE_VMEMMAP,
	KCORE_USER,
	KCORE_OTHER,
	KCORE_REMAP,
पूर्ण;

काष्ठा kcore_list अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ vaddr;
	माप_प्रकार size;
	पूर्णांक type;
पूर्ण;

काष्ठा vmcore अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ दीर्घ paddr;
	अचिन्हित दीर्घ दीर्घ size;
	loff_t offset;
पूर्ण;

काष्ठा vmcoredd_node अणु
	काष्ठा list_head list;	/* List of dumps */
	व्योम *buf;		/* Buffer containing device's dump */
	अचिन्हित पूर्णांक size;	/* Size of the buffer */
पूर्ण;

#अगर_घोषित CONFIG_PROC_KCORE
व्योम __init kclist_add(काष्ठा kcore_list *, व्योम *, माप_प्रकार, पूर्णांक type);

बाह्य पूर्णांक __init रेजिस्टर_mem_pfn_is_ram(पूर्णांक (*fn)(अचिन्हित दीर्घ pfn));
#अन्यथा
अटल अंतरभूत
व्योम kclist_add(काष्ठा kcore_list *new, व्योम *addr, माप_प्रकार size, पूर्णांक type)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_KCORE_H */
