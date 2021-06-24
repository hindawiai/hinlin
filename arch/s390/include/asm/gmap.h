<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  KVM guest address space mapping code
 *
 *    Copyright IBM Corp. 2007, 2016
 *    Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#अगर_अघोषित _ASM_S390_GMAP_H
#घोषणा _ASM_S390_GMAP_H

#समावेश <linux/radix-tree.h>
#समावेश <linux/refcount.h>

/* Generic bits क्रम GMAP notअगरication on DAT table entry changes. */
#घोषणा GMAP_NOTIFY_SHADOW	0x2
#घोषणा GMAP_NOTIFY_MPROT	0x1

/* Status bits only क्रम huge segment entries */
#घोषणा _SEGMENT_ENTRY_GMAP_IN		0x8000	/* invalidation notअगरy bit */
#घोषणा _SEGMENT_ENTRY_GMAP_UC		0x4000	/* dirty (migration) */

/**
 * काष्ठा gmap_काष्ठा - guest address space
 * @list: list head क्रम the mm->context gmap list
 * @crst_list: list of all crst tables used in the guest address space
 * @mm: poपूर्णांकer to the parent mm_काष्ठा
 * @guest_to_host: radix tree with guest to host address translation
 * @host_to_guest: radix tree with poपूर्णांकer to segment table entries
 * @guest_table_lock: spinlock to protect all entries in the guest page table
 * @ref_count: reference counter क्रम the gmap काष्ठाure
 * @table: poपूर्णांकer to the page directory
 * @asce: address space control element क्रम gmap page table
 * @pfault_enabled: defines अगर pfaults are applicable क्रम the guest
 * @guest_handle: रक्षित भव machine handle क्रम the ultravisor
 * @host_to_rmap: radix tree with gmap_rmap lists
 * @children: list of shaकरोw gmap काष्ठाures
 * @pt_list: list of all page tables used in the shaकरोw guest address space
 * @shaकरोw_lock: spinlock to protect the shaकरोw gmap list
 * @parent: poपूर्णांकer to the parent gmap क्रम shaकरोw guest address spaces
 * @orig_asce: ASCE क्रम which the shaकरोw page table has been created
 * @edat_level: edat level to be used क्रम the shaकरोw translation
 * @हटाओd: flag to indicate अगर a shaकरोw guest address space has been हटाओd
 * @initialized: flag to indicate अगर a shaकरोw guest address space can be used
 */
काष्ठा gmap अणु
	काष्ठा list_head list;
	काष्ठा list_head crst_list;
	काष्ठा mm_काष्ठा *mm;
	काष्ठा radix_tree_root guest_to_host;
	काष्ठा radix_tree_root host_to_guest;
	spinlock_t guest_table_lock;
	refcount_t ref_count;
	अचिन्हित दीर्घ *table;
	अचिन्हित दीर्घ asce;
	अचिन्हित दीर्घ asce_end;
	व्योम *निजी;
	bool pfault_enabled;
	/* only set क्रम रक्षित भव machines */
	अचिन्हित दीर्घ guest_handle;
	/* Additional data क्रम shaकरोw guest address spaces */
	काष्ठा radix_tree_root host_to_rmap;
	काष्ठा list_head children;
	काष्ठा list_head pt_list;
	spinlock_t shaकरोw_lock;
	काष्ठा gmap *parent;
	अचिन्हित दीर्घ orig_asce;
	पूर्णांक edat_level;
	bool हटाओd;
	bool initialized;
पूर्ण;

/**
 * काष्ठा gmap_rmap - reverse mapping क्रम shaकरोw page table entries
 * @next: poपूर्णांकer to next rmap in the list
 * @raddr: भव rmap address in the shaकरोw guest address space
 */
काष्ठा gmap_rmap अणु
	काष्ठा gmap_rmap *next;
	अचिन्हित दीर्घ raddr;
पूर्ण;

#घोषणा gmap_क्रम_each_rmap(pos, head) \
	क्रम (pos = (head); pos; pos = pos->next)

#घोषणा gmap_क्रम_each_rmap_safe(pos, n, head) \
	क्रम (pos = (head); n = pos ? pos->next : शून्य, pos; pos = n)

/**
 * काष्ठा gmap_notअगरier - notअगरy function block क्रम page invalidation
 * @notअगरier_call: address of callback function
 */
काष्ठा gmap_notअगरier अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	व्योम (*notअगरier_call)(काष्ठा gmap *gmap, अचिन्हित दीर्घ start,
			      अचिन्हित दीर्घ end);
पूर्ण;

अटल अंतरभूत पूर्णांक gmap_is_shaकरोw(काष्ठा gmap *gmap)
अणु
	वापस !!gmap->parent;
पूर्ण

काष्ठा gmap *gmap_create(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ limit);
व्योम gmap_हटाओ(काष्ठा gmap *gmap);
काष्ठा gmap *gmap_get(काष्ठा gmap *gmap);
व्योम gmap_put(काष्ठा gmap *gmap);

व्योम gmap_enable(काष्ठा gmap *gmap);
व्योम gmap_disable(काष्ठा gmap *gmap);
काष्ठा gmap *gmap_get_enabled(व्योम);
पूर्णांक gmap_map_segment(काष्ठा gmap *gmap, अचिन्हित दीर्घ from,
		     अचिन्हित दीर्घ to, अचिन्हित दीर्घ len);
पूर्णांक gmap_unmap_segment(काष्ठा gmap *gmap, अचिन्हित दीर्घ to, अचिन्हित दीर्घ len);
अचिन्हित दीर्घ __gmap_translate(काष्ठा gmap *, अचिन्हित दीर्घ gaddr);
अचिन्हित दीर्घ gmap_translate(काष्ठा gmap *, अचिन्हित दीर्घ gaddr);
पूर्णांक __gmap_link(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ vmaddr);
पूर्णांक gmap_fault(काष्ठा gmap *, अचिन्हित दीर्घ gaddr, अचिन्हित पूर्णांक fault_flags);
व्योम gmap_discard(काष्ठा gmap *, अचिन्हित दीर्घ from, अचिन्हित दीर्घ to);
व्योम __gmap_zap(काष्ठा gmap *, अचिन्हित दीर्घ gaddr);
व्योम gmap_unlink(काष्ठा mm_काष्ठा *, अचिन्हित दीर्घ *table, अचिन्हित दीर्घ vmaddr);

पूर्णांक gmap_पढ़ो_table(काष्ठा gmap *gmap, अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ *val);

काष्ठा gmap *gmap_shaकरोw(काष्ठा gmap *parent, अचिन्हित दीर्घ asce,
			 पूर्णांक edat_level);
पूर्णांक gmap_shaकरोw_valid(काष्ठा gmap *sg, अचिन्हित दीर्घ asce, पूर्णांक edat_level);
पूर्णांक gmap_shaकरोw_r2t(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ r2t,
		    पूर्णांक fake);
पूर्णांक gmap_shaकरोw_r3t(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ r3t,
		    पूर्णांक fake);
पूर्णांक gmap_shaकरोw_sgt(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ sgt,
		    पूर्णांक fake);
पूर्णांक gmap_shaकरोw_pgt(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, अचिन्हित दीर्घ pgt,
		    पूर्णांक fake);
पूर्णांक gmap_shaकरोw_pgt_lookup(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr,
			   अचिन्हित दीर्घ *pgt, पूर्णांक *dat_protection, पूर्णांक *fake);
पूर्णांक gmap_shaकरोw_page(काष्ठा gmap *sg, अचिन्हित दीर्घ saddr, pte_t pte);

व्योम gmap_रेजिस्टर_pte_notअगरier(काष्ठा gmap_notअगरier *);
व्योम gmap_unरेजिस्टर_pte_notअगरier(काष्ठा gmap_notअगरier *);

पूर्णांक gmap_mprotect_notअगरy(काष्ठा gmap *, अचिन्हित दीर्घ start,
			 अचिन्हित दीर्घ len, पूर्णांक prot);

व्योम gmap_sync_dirty_log_pmd(काष्ठा gmap *gmap, अचिन्हित दीर्घ dirty_biपंचांगap[4],
			     अचिन्हित दीर्घ gaddr, अचिन्हित दीर्घ vmaddr);
पूर्णांक gmap_mark_unmergeable(व्योम);
व्योम s390_reset_acc(काष्ठा mm_काष्ठा *mm);
#पूर्ण_अगर /* _ASM_S390_GMAP_H */
