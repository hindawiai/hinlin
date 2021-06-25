<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/memblock.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/swiotlb.h>

#समावेश <xen/xen.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/page.h>
#समावेश <xen/swiotlb-xen.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/पूर्णांकerface.h>

काष्ठा xen_p2m_entry अणु
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ mfn;
	अचिन्हित दीर्घ nr_pages;
	काष्ठा rb_node rbnode_phys;
पूर्ण;

अटल rwlock_t p2m_lock;
काष्ठा rb_root phys_to_mach = RB_ROOT;
EXPORT_SYMBOL_GPL(phys_to_mach);

अटल पूर्णांक xen_add_phys_to_mach_entry(काष्ठा xen_p2m_entry *new)
अणु
	काष्ठा rb_node **link = &phys_to_mach.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा xen_p2m_entry *entry;
	पूर्णांक rc = 0;

	जबतक (*link) अणु
		parent = *link;
		entry = rb_entry(parent, काष्ठा xen_p2m_entry, rbnode_phys);

		अगर (new->pfn == entry->pfn)
			जाओ err_out;

		अगर (new->pfn < entry->pfn)
			link = &(*link)->rb_left;
		अन्यथा
			link = &(*link)->rb_right;
	पूर्ण
	rb_link_node(&new->rbnode_phys, parent, link);
	rb_insert_color(&new->rbnode_phys, &phys_to_mach);
	जाओ out;

err_out:
	rc = -EINVAL;
	pr_warn("%s: cannot add pfn=%pa -> mfn=%pa: pfn=%pa -> mfn=%pa already exists\n",
			__func__, &new->pfn, &new->mfn, &entry->pfn, &entry->mfn);
out:
	वापस rc;
पूर्ण

अचिन्हित दीर्घ __pfn_to_mfn(अचिन्हित दीर्घ pfn)
अणु
	काष्ठा rb_node *n = phys_to_mach.rb_node;
	काष्ठा xen_p2m_entry *entry;
	अचिन्हित दीर्घ irqflags;

	पढ़ो_lock_irqsave(&p2m_lock, irqflags);
	जबतक (n) अणु
		entry = rb_entry(n, काष्ठा xen_p2m_entry, rbnode_phys);
		अगर (entry->pfn <= pfn &&
				entry->pfn + entry->nr_pages > pfn) अणु
			अचिन्हित दीर्घ mfn = entry->mfn + (pfn - entry->pfn);
			पढ़ो_unlock_irqrestore(&p2m_lock, irqflags);
			वापस mfn;
		पूर्ण
		अगर (pfn < entry->pfn)
			n = n->rb_left;
		अन्यथा
			n = n->rb_right;
	पूर्ण
	पढ़ो_unlock_irqrestore(&p2m_lock, irqflags);

	वापस INVALID_P2M_ENTRY;
पूर्ण
EXPORT_SYMBOL_GPL(__pfn_to_mfn);

पूर्णांक set_क्रमeign_p2m_mapping(काष्ठा gnttab_map_grant_ref *map_ops,
			    काष्ठा gnttab_map_grant_ref *kmap_ops,
			    काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा gnttab_unmap_grant_ref unmap;
		पूर्णांक rc;

		अगर (map_ops[i].status)
			जारी;
		अगर (likely(set_phys_to_machine(map_ops[i].host_addr >> XEN_PAGE_SHIFT,
				    map_ops[i].dev_bus_addr >> XEN_PAGE_SHIFT)))
			जारी;

		/*
		 * Signal an error क्रम this slot. This in turn requires
		 * immediate unmapping.
		 */
		map_ops[i].status = GNTST_general_error;
		unmap.host_addr = map_ops[i].host_addr,
		unmap.handle = map_ops[i].handle;
		map_ops[i].handle = INVALID_GRANT_HANDLE;
		अगर (map_ops[i].flags & GNTMAP_device_map)
			unmap.dev_bus_addr = map_ops[i].dev_bus_addr;
		अन्यथा
			unmap.dev_bus_addr = 0;

		/*
		 * Pre-populate the status field, to be recognizable in
		 * the log message below.
		 */
		unmap.status = 1;

		rc = HYPERVISOR_grant_table_op(GNTTABOP_unmap_grant_ref,
					       &unmap, 1);
		अगर (rc || unmap.status != GNTST_okay)
			pr_err_once("gnttab unmap failed: rc=%d st=%d\n",
				    rc, unmap.status);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक clear_क्रमeign_p2m_mapping(काष्ठा gnttab_unmap_grant_ref *unmap_ops,
			      काष्ठा gnttab_unmap_grant_ref *kunmap_ops,
			      काष्ठा page **pages, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		set_phys_to_machine(unmap_ops[i].host_addr >> XEN_PAGE_SHIFT,
				    INVALID_P2M_ENTRY);
	पूर्ण

	वापस 0;
पूर्ण

bool __set_phys_to_machine_multi(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ mfn, अचिन्हित दीर्घ nr_pages)
अणु
	पूर्णांक rc;
	अचिन्हित दीर्घ irqflags;
	काष्ठा xen_p2m_entry *p2m_entry;
	काष्ठा rb_node *n = phys_to_mach.rb_node;

	अगर (mfn == INVALID_P2M_ENTRY) अणु
		ग_लिखो_lock_irqsave(&p2m_lock, irqflags);
		जबतक (n) अणु
			p2m_entry = rb_entry(n, काष्ठा xen_p2m_entry, rbnode_phys);
			अगर (p2m_entry->pfn <= pfn &&
					p2m_entry->pfn + p2m_entry->nr_pages > pfn) अणु
				rb_erase(&p2m_entry->rbnode_phys, &phys_to_mach);
				ग_लिखो_unlock_irqrestore(&p2m_lock, irqflags);
				kमुक्त(p2m_entry);
				वापस true;
			पूर्ण
			अगर (pfn < p2m_entry->pfn)
				n = n->rb_left;
			अन्यथा
				n = n->rb_right;
		पूर्ण
		ग_लिखो_unlock_irqrestore(&p2m_lock, irqflags);
		वापस true;
	पूर्ण

	p2m_entry = kzalloc(माप(*p2m_entry), GFP_NOWAIT);
	अगर (!p2m_entry)
		वापस false;

	p2m_entry->pfn = pfn;
	p2m_entry->nr_pages = nr_pages;
	p2m_entry->mfn = mfn;

	ग_लिखो_lock_irqsave(&p2m_lock, irqflags);
	rc = xen_add_phys_to_mach_entry(p2m_entry);
	अगर (rc < 0) अणु
		ग_लिखो_unlock_irqrestore(&p2m_lock, irqflags);
		kमुक्त(p2m_entry);
		वापस false;
	पूर्ण
	ग_लिखो_unlock_irqrestore(&p2m_lock, irqflags);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(__set_phys_to_machine_multi);

bool __set_phys_to_machine(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn)
अणु
	वापस __set_phys_to_machine_multi(pfn, mfn, 1);
पूर्ण
EXPORT_SYMBOL_GPL(__set_phys_to_machine);

अटल पूर्णांक p2m_init(व्योम)
अणु
	rwlock_init(&p2m_lock);
	वापस 0;
पूर्ण
arch_initcall(p2m_init);
