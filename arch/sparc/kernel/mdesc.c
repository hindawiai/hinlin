<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* mdesc.c: Sun4V machine description handling.
 *
 * Copyright (C) 2007, 2008 David S. Miller <davem@davemloft.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/log2.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/memblock.h>
#समावेश <linux/export.h>
#समावेश <linux/refcount.h>

#समावेश <यंत्र/cpudata.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/mdesc.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/adi.h>

/* Unlike the OBP device tree, the machine description is a full-on
 * DAG.  An arbitrary number of ARCs are possible from one
 * node to other nodes and thus we can't use the OBP device_node
 * data काष्ठाure to represent these nodes inside of the kernel.
 *
 * Actually, it isn't even a DAG, because there are back poपूर्णांकers
 * which create cycles in the graph.
 *
 * mdesc_hdr and mdesc_elem describe the layout of the data काष्ठाure
 * we get from the Hypervisor.
 */
काष्ठा mdesc_hdr अणु
	u32	version; /* Transport version */
	u32	node_sz; /* node block size */
	u32	name_sz; /* name block size */
	u32	data_sz; /* data block size */
पूर्ण __attribute__((aligned(16)));

काष्ठा mdesc_elem अणु
	u8	tag;
#घोषणा MD_LIST_END	0x00
#घोषणा MD_NODE		0x4e
#घोषणा MD_NODE_END	0x45
#घोषणा MD_NOOP		0x20
#घोषणा MD_PROP_ARC	0x61
#घोषणा MD_PROP_VAL	0x76
#घोषणा MD_PROP_STR	0x73
#घोषणा MD_PROP_DATA	0x64
	u8	name_len;
	u16	resv;
	u32	name_offset;
	जोड़ अणु
		काष्ठा अणु
			u32	data_len;
			u32	data_offset;
		पूर्ण data;
		u64	val;
	पूर्ण d;
पूर्ण;

काष्ठा mdesc_mem_ops अणु
	काष्ठा mdesc_handle *(*alloc)(अचिन्हित पूर्णांक mdesc_size);
	व्योम (*मुक्त)(काष्ठा mdesc_handle *handle);
पूर्ण;

काष्ठा mdesc_handle अणु
	काष्ठा list_head	list;
	काष्ठा mdesc_mem_ops	*mops;
	व्योम			*self_base;
	refcount_t		refcnt;
	अचिन्हित पूर्णांक		handle_size;
	काष्ठा mdesc_hdr	mdesc;
पूर्ण;

प्रकार पूर्णांक (*mdesc_node_info_get_f)(काष्ठा mdesc_handle *, u64,
				     जोड़ md_node_info *);
प्रकार व्योम (*mdesc_node_info_rel_f)(जोड़ md_node_info *);
प्रकार bool (*mdesc_node_match_f)(जोड़ md_node_info *, जोड़ md_node_info *);

काष्ठा md_node_ops अणु
	अक्षर			*name;
	mdesc_node_info_get_f	get_info;
	mdesc_node_info_rel_f	rel_info;
	mdesc_node_match_f	node_match;
पूर्ण;

अटल पूर्णांक get_vdev_port_node_info(काष्ठा mdesc_handle *md, u64 node,
				   जोड़ md_node_info *node_info);
अटल व्योम rel_vdev_port_node_info(जोड़ md_node_info *node_info);
अटल bool vdev_port_node_match(जोड़ md_node_info *a_node_info,
				 जोड़ md_node_info *b_node_info);

अटल पूर्णांक get_ds_port_node_info(काष्ठा mdesc_handle *md, u64 node,
				 जोड़ md_node_info *node_info);
अटल व्योम rel_ds_port_node_info(जोड़ md_node_info *node_info);
अटल bool ds_port_node_match(जोड़ md_node_info *a_node_info,
			       जोड़ md_node_info *b_node_info);

/* supported node types which can be रेजिस्टरed */
अटल काष्ठा md_node_ops md_node_ops_table[] = अणु
	अणु"virtual-device-port", get_vdev_port_node_info,
	 rel_vdev_port_node_info, vdev_port_node_matchपूर्ण,
	अणु"domain-services-port", get_ds_port_node_info,
	 rel_ds_port_node_info, ds_port_node_matchपूर्ण,
	अणुशून्य, शून्य, शून्य, शून्यपूर्ण
पूर्ण;

अटल व्योम mdesc_get_node_ops(स्थिर अक्षर *node_name,
			       mdesc_node_info_get_f *get_info_f,
			       mdesc_node_info_rel_f *rel_info_f,
			       mdesc_node_match_f *match_f)
अणु
	पूर्णांक i;

	अगर (get_info_f)
		*get_info_f = शून्य;

	अगर (rel_info_f)
		*rel_info_f = शून्य;

	अगर (match_f)
		*match_f = शून्य;

	अगर (!node_name)
		वापस;

	क्रम (i = 0; md_node_ops_table[i].name != शून्य; i++) अणु
		अगर (म_भेद(md_node_ops_table[i].name, node_name) == 0) अणु
			अगर (get_info_f)
				*get_info_f = md_node_ops_table[i].get_info;

			अगर (rel_info_f)
				*rel_info_f = md_node_ops_table[i].rel_info;

			अगर (match_f)
				*match_f = md_node_ops_table[i].node_match;

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mdesc_handle_init(काष्ठा mdesc_handle *hp,
			      अचिन्हित पूर्णांक handle_size,
			      व्योम *base)
अणु
	BUG_ON(((अचिन्हित दीर्घ)&hp->mdesc) & (16UL - 1));

	स_रखो(hp, 0, handle_size);
	INIT_LIST_HEAD(&hp->list);
	hp->self_base = base;
	refcount_set(&hp->refcnt, 1);
	hp->handle_size = handle_size;
पूर्ण

अटल काष्ठा mdesc_handle * __init mdesc_memblock_alloc(अचिन्हित पूर्णांक mdesc_size)
अणु
	अचिन्हित पूर्णांक handle_size, alloc_size;
	काष्ठा mdesc_handle *hp;
	अचिन्हित दीर्घ paddr;

	handle_size = (माप(काष्ठा mdesc_handle) -
		       माप(काष्ठा mdesc_hdr) +
		       mdesc_size);
	alloc_size = PAGE_ALIGN(handle_size);

	paddr = memblock_phys_alloc(alloc_size, PAGE_SIZE);

	hp = शून्य;
	अगर (paddr) अणु
		hp = __va(paddr);
		mdesc_handle_init(hp, handle_size, hp);
	पूर्ण
	वापस hp;
पूर्ण

अटल व्योम __init mdesc_memblock_मुक्त(काष्ठा mdesc_handle *hp)
अणु
	अचिन्हित पूर्णांक alloc_size;
	अचिन्हित दीर्घ start;

	BUG_ON(refcount_पढ़ो(&hp->refcnt) != 0);
	BUG_ON(!list_empty(&hp->list));

	alloc_size = PAGE_ALIGN(hp->handle_size);
	start = __pa(hp);
	memblock_मुक्त_late(start, alloc_size);
पूर्ण

अटल काष्ठा mdesc_mem_ops memblock_mdesc_ops = अणु
	.alloc = mdesc_memblock_alloc,
	.मुक्त  = mdesc_memblock_मुक्त,
पूर्ण;

अटल काष्ठा mdesc_handle *mdesc_kदो_स्मृति(अचिन्हित पूर्णांक mdesc_size)
अणु
	अचिन्हित पूर्णांक handle_size;
	काष्ठा mdesc_handle *hp;
	अचिन्हित दीर्घ addr;
	व्योम *base;

	handle_size = (माप(काष्ठा mdesc_handle) -
		       माप(काष्ठा mdesc_hdr) +
		       mdesc_size);
	base = kदो_स्मृति(handle_size + 15, GFP_KERNEL | __GFP_RETRY_MAYFAIL);
	अगर (!base)
		वापस शून्य;

	addr = (अचिन्हित दीर्घ)base;
	addr = (addr + 15UL) & ~15UL;
	hp = (काष्ठा mdesc_handle *) addr;

	mdesc_handle_init(hp, handle_size, base);

	वापस hp;
पूर्ण

अटल व्योम mdesc_kमुक्त(काष्ठा mdesc_handle *hp)
अणु
	BUG_ON(refcount_पढ़ो(&hp->refcnt) != 0);
	BUG_ON(!list_empty(&hp->list));

	kमुक्त(hp->self_base);
पूर्ण

अटल काष्ठा mdesc_mem_ops kदो_स्मृति_mdesc_memops = अणु
	.alloc = mdesc_kदो_स्मृति,
	.मुक्त  = mdesc_kमुक्त,
पूर्ण;

अटल काष्ठा mdesc_handle *mdesc_alloc(अचिन्हित पूर्णांक mdesc_size,
					काष्ठा mdesc_mem_ops *mops)
अणु
	काष्ठा mdesc_handle *hp = mops->alloc(mdesc_size);

	अगर (hp)
		hp->mops = mops;

	वापस hp;
पूर्ण

अटल व्योम mdesc_मुक्त(काष्ठा mdesc_handle *hp)
अणु
	hp->mops->मुक्त(hp);
पूर्ण

अटल काष्ठा mdesc_handle *cur_mdesc;
अटल LIST_HEAD(mdesc_zombie_list);
अटल DEFINE_SPINLOCK(mdesc_lock);

काष्ठा mdesc_handle *mdesc_grab(व्योम)
अणु
	काष्ठा mdesc_handle *hp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdesc_lock, flags);
	hp = cur_mdesc;
	अगर (hp)
		refcount_inc(&hp->refcnt);
	spin_unlock_irqrestore(&mdesc_lock, flags);

	वापस hp;
पूर्ण
EXPORT_SYMBOL(mdesc_grab);

व्योम mdesc_release(काष्ठा mdesc_handle *hp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdesc_lock, flags);
	अगर (refcount_dec_and_test(&hp->refcnt)) अणु
		list_del_init(&hp->list);
		hp->mops->मुक्त(hp);
	पूर्ण
	spin_unlock_irqrestore(&mdesc_lock, flags);
पूर्ण
EXPORT_SYMBOL(mdesc_release);

अटल DEFINE_MUTEX(mdesc_mutex);
अटल काष्ठा mdesc_notअगरier_client *client_list;

व्योम mdesc_रेजिस्टर_notअगरier(काष्ठा mdesc_notअगरier_client *client)
अणु
	bool supported = false;
	u64 node;
	पूर्णांक i;

	mutex_lock(&mdesc_mutex);

	/* check to see अगर the node is supported क्रम registration */
	क्रम (i = 0; md_node_ops_table[i].name != शून्य; i++) अणु
		अगर (म_भेद(md_node_ops_table[i].name, client->node_name) == 0) अणु
			supported = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!supported) अणु
		pr_err("MD: %s node not supported\n", client->node_name);
		mutex_unlock(&mdesc_mutex);
		वापस;
	पूर्ण

	client->next = client_list;
	client_list = client;

	mdesc_क्रम_each_node_by_name(cur_mdesc, node, client->node_name)
		client->add(cur_mdesc, node, client->node_name);

	mutex_unlock(&mdesc_mutex);
पूर्ण

अटल स्थिर u64 *parent_cfg_handle(काष्ठा mdesc_handle *hp, u64 node)
अणु
	स्थिर u64 *id;
	u64 a;

	id = शून्य;
	mdesc_क्रम_each_arc(a, hp, node, MDESC_ARC_TYPE_BACK) अणु
		u64 target;

		target = mdesc_arc_target(hp, a);
		id = mdesc_get_property(hp, target,
					"cfg-handle", शून्य);
		अगर (id)
			अवरोध;
	पूर्ण

	वापस id;
पूर्ण

अटल पूर्णांक get_vdev_port_node_info(काष्ठा mdesc_handle *md, u64 node,
				   जोड़ md_node_info *node_info)
अणु
	स्थिर u64 *parent_cfg_hdlp;
	स्थिर अक्षर *name;
	स्थिर u64 *idp;

	/*
	 * Virtual device nodes are distinguished by:
	 * 1. "id" property
	 * 2. "name" property
	 * 3. parent node "cfg-handle" property
	 */
	idp = mdesc_get_property(md, node, "id", शून्य);
	name = mdesc_get_property(md, node, "name", शून्य);
	parent_cfg_hdlp = parent_cfg_handle(md, node);

	अगर (!idp || !name || !parent_cfg_hdlp)
		वापस -1;

	node_info->vdev_port.id = *idp;
	node_info->vdev_port.name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!node_info->vdev_port.name)
		वापस -1;
	node_info->vdev_port.parent_cfg_hdl = *parent_cfg_hdlp;

	वापस 0;
पूर्ण

अटल व्योम rel_vdev_port_node_info(जोड़ md_node_info *node_info)
अणु
	अगर (node_info && node_info->vdev_port.name) अणु
		kमुक्त_स्थिर(node_info->vdev_port.name);
		node_info->vdev_port.name = शून्य;
	पूर्ण
पूर्ण

अटल bool vdev_port_node_match(जोड़ md_node_info *a_node_info,
				 जोड़ md_node_info *b_node_info)
अणु
	अगर (a_node_info->vdev_port.id != b_node_info->vdev_port.id)
		वापस false;

	अगर (a_node_info->vdev_port.parent_cfg_hdl !=
	    b_node_info->vdev_port.parent_cfg_hdl)
		वापस false;

	अगर (म_भेदन(a_node_info->vdev_port.name,
		    b_node_info->vdev_port.name, MDESC_MAX_STR_LEN) != 0)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक get_ds_port_node_info(काष्ठा mdesc_handle *md, u64 node,
				 जोड़ md_node_info *node_info)
अणु
	स्थिर u64 *idp;

	/* DS port nodes use the "id" property to distinguish them */
	idp = mdesc_get_property(md, node, "id", शून्य);
	अगर (!idp)
		वापस -1;

	node_info->ds_port.id = *idp;

	वापस 0;
पूर्ण

अटल व्योम rel_ds_port_node_info(जोड़ md_node_info *node_info)
अणु
पूर्ण

अटल bool ds_port_node_match(जोड़ md_node_info *a_node_info,
			       जोड़ md_node_info *b_node_info)
अणु
	अगर (a_node_info->ds_port.id != b_node_info->ds_port.id)
		वापस false;

	वापस true;
पूर्ण

/* Run 'func' on nodes which are in A but not in B.  */
अटल व्योम invoke_on_missing(स्थिर अक्षर *name,
			      काष्ठा mdesc_handle *a,
			      काष्ठा mdesc_handle *b,
			      व्योम (*func)(काष्ठा mdesc_handle *, u64,
					   स्थिर अक्षर *node_name))
अणु
	mdesc_node_info_get_f get_info_func;
	mdesc_node_info_rel_f rel_info_func;
	mdesc_node_match_f node_match_func;
	जोड़ md_node_info a_node_info;
	जोड़ md_node_info b_node_info;
	bool found;
	u64 a_node;
	u64 b_node;
	पूर्णांक rv;

	/*
	 * Find the get_info, rel_info and node_match ops क्रम the given
	 * node name
	 */
	mdesc_get_node_ops(name, &get_info_func, &rel_info_func,
			   &node_match_func);

	/* If we didn't find a match, the node type is not supported */
	अगर (!get_info_func || !rel_info_func || !node_match_func) अणु
		pr_err("MD: %s node type is not supported\n", name);
		वापस;
	पूर्ण

	mdesc_क्रम_each_node_by_name(a, a_node, name) अणु
		found = false;

		rv = get_info_func(a, a_node, &a_node_info);
		अगर (rv != 0) अणु
			pr_err("MD: Cannot find 1 or more required match properties for %s node.\n",
			       name);
			जारी;
		पूर्ण

		/* Check each node in B क्रम node matching a_node */
		mdesc_क्रम_each_node_by_name(b, b_node, name) अणु
			rv = get_info_func(b, b_node, &b_node_info);
			अगर (rv != 0)
				जारी;

			अगर (node_match_func(&a_node_info, &b_node_info)) अणु
				found = true;
				rel_info_func(&b_node_info);
				अवरोध;
			पूर्ण

			rel_info_func(&b_node_info);
		पूर्ण

		rel_info_func(&a_node_info);

		अगर (!found)
			func(a, a_node, name);
	पूर्ण
पूर्ण

अटल व्योम notअगरy_one(काष्ठा mdesc_notअगरier_client *p,
		       काष्ठा mdesc_handle *old_hp,
		       काष्ठा mdesc_handle *new_hp)
अणु
	invoke_on_missing(p->node_name, old_hp, new_hp, p->हटाओ);
	invoke_on_missing(p->node_name, new_hp, old_hp, p->add);
पूर्ण

अटल व्योम mdesc_notअगरy_clients(काष्ठा mdesc_handle *old_hp,
				 काष्ठा mdesc_handle *new_hp)
अणु
	काष्ठा mdesc_notअगरier_client *p = client_list;

	जबतक (p) अणु
		notअगरy_one(p, old_hp, new_hp);
		p = p->next;
	पूर्ण
पूर्ण

व्योम mdesc_update(व्योम)
अणु
	अचिन्हित दीर्घ len, real_len, status;
	काष्ठा mdesc_handle *hp, *orig_hp;
	अचिन्हित दीर्घ flags;

	mutex_lock(&mdesc_mutex);

	(व्योम) sun4v_mach_desc(0UL, 0UL, &len);

	hp = mdesc_alloc(len, &kदो_स्मृति_mdesc_memops);
	अगर (!hp) अणु
		prपूर्णांकk(KERN_ERR "MD: mdesc alloc fails\n");
		जाओ out;
	पूर्ण

	status = sun4v_mach_desc(__pa(&hp->mdesc), len, &real_len);
	अगर (status != HV_EOK || real_len > len) अणु
		prपूर्णांकk(KERN_ERR "MD: mdesc reread fails with %lu\n",
		       status);
		refcount_dec(&hp->refcnt);
		mdesc_मुक्त(hp);
		जाओ out;
	पूर्ण

	spin_lock_irqsave(&mdesc_lock, flags);
	orig_hp = cur_mdesc;
	cur_mdesc = hp;
	spin_unlock_irqrestore(&mdesc_lock, flags);

	mdesc_notअगरy_clients(orig_hp, hp);

	spin_lock_irqsave(&mdesc_lock, flags);
	अगर (refcount_dec_and_test(&orig_hp->refcnt))
		mdesc_मुक्त(orig_hp);
	अन्यथा
		list_add(&orig_hp->list, &mdesc_zombie_list);
	spin_unlock_irqrestore(&mdesc_lock, flags);

out:
	mutex_unlock(&mdesc_mutex);
पूर्ण

u64 mdesc_get_node(काष्ठा mdesc_handle *hp, स्थिर अक्षर *node_name,
		   जोड़ md_node_info *node_info)
अणु
	mdesc_node_info_get_f get_info_func;
	mdesc_node_info_rel_f rel_info_func;
	mdesc_node_match_f node_match_func;
	जोड़ md_node_info hp_node_info;
	u64 hp_node;
	पूर्णांक rv;

	अगर (hp == शून्य || node_name == शून्य || node_info == शून्य)
		वापस MDESC_NODE_शून्य;

	/* Find the ops क्रम the given node name */
	mdesc_get_node_ops(node_name, &get_info_func, &rel_info_func,
			   &node_match_func);

	/* If we didn't find ops क्रम the given node name, it is not supported */
	अगर (!get_info_func || !rel_info_func || !node_match_func) अणु
		pr_err("MD: %s node is not supported\n", node_name);
		वापस -EINVAL;
	पूर्ण

	mdesc_क्रम_each_node_by_name(hp, hp_node, node_name) अणु
		rv = get_info_func(hp, hp_node, &hp_node_info);
		अगर (rv != 0)
			जारी;

		अगर (node_match_func(node_info, &hp_node_info))
			अवरोध;

		rel_info_func(&hp_node_info);
	पूर्ण

	rel_info_func(&hp_node_info);

	वापस hp_node;
पूर्ण
EXPORT_SYMBOL(mdesc_get_node);

पूर्णांक mdesc_get_node_info(काष्ठा mdesc_handle *hp, u64 node,
			स्थिर अक्षर *node_name, जोड़ md_node_info *node_info)
अणु
	mdesc_node_info_get_f get_info_func;
	पूर्णांक rv;

	अगर (hp == शून्य || node == MDESC_NODE_शून्य ||
	    node_name == शून्य || node_info == शून्य)
		वापस -EINVAL;

	/* Find the get_info op क्रम the given node name */
	mdesc_get_node_ops(node_name, &get_info_func, शून्य, शून्य);

	/* If we didn't find a get_info_func, the node name is not supported */
	अगर (get_info_func == शून्य) अणु
		pr_err("MD: %s node is not supported\n", node_name);
		वापस -EINVAL;
	पूर्ण

	rv = get_info_func(hp, node, node_info);
	अगर (rv != 0) अणु
		pr_err("MD: Cannot find 1 or more required match properties for %s node.\n",
		       node_name);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdesc_get_node_info);

अटल काष्ठा mdesc_elem *node_block(काष्ठा mdesc_hdr *mdesc)
अणु
	वापस (काष्ठा mdesc_elem *) (mdesc + 1);
पूर्ण

अटल व्योम *name_block(काष्ठा mdesc_hdr *mdesc)
अणु
	वापस ((व्योम *) node_block(mdesc)) + mdesc->node_sz;
पूर्ण

अटल व्योम *data_block(काष्ठा mdesc_hdr *mdesc)
अणु
	वापस ((व्योम *) name_block(mdesc)) + mdesc->name_sz;
पूर्ण

u64 mdesc_node_by_name(काष्ठा mdesc_handle *hp,
		       u64 from_node, स्थिर अक्षर *name)
अणु
	काष्ठा mdesc_elem *ep = node_block(&hp->mdesc);
	स्थिर अक्षर *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;
	u64 ret;

	अगर (from_node == MDESC_NODE_शून्य) अणु
		ret = from_node = 0;
	पूर्ण अन्यथा अगर (from_node >= last_node) अणु
		वापस MDESC_NODE_शून्य;
	पूर्ण अन्यथा अणु
		ret = ep[from_node].d.val;
	पूर्ण

	जबतक (ret < last_node) अणु
		अगर (ep[ret].tag != MD_NODE)
			वापस MDESC_NODE_शून्य;
		अगर (!म_भेद(names + ep[ret].name_offset, name))
			अवरोध;
		ret = ep[ret].d.val;
	पूर्ण
	अगर (ret >= last_node)
		ret = MDESC_NODE_शून्य;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mdesc_node_by_name);

स्थिर व्योम *mdesc_get_property(काष्ठा mdesc_handle *hp, u64 node,
			       स्थिर अक्षर *name, पूर्णांक *lenp)
अणु
	स्थिर अक्षर *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;
	व्योम *data = data_block(&hp->mdesc);
	काष्ठा mdesc_elem *ep;

	अगर (node == MDESC_NODE_शून्य || node >= last_node)
		वापस शून्य;

	ep = node_block(&hp->mdesc) + node;
	ep++;
	क्रम (; ep->tag != MD_NODE_END; ep++) अणु
		व्योम *val = शून्य;
		पूर्णांक len = 0;

		चयन (ep->tag) अणु
		हाल MD_PROP_VAL:
			val = &ep->d.val;
			len = 8;
			अवरोध;

		हाल MD_PROP_STR:
		हाल MD_PROP_DATA:
			val = data + ep->d.data.data_offset;
			len = ep->d.data.data_len;
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अगर (!val)
			जारी;

		अगर (!म_भेद(names + ep->name_offset, name)) अणु
			अगर (lenp)
				*lenp = len;
			वापस val;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(mdesc_get_property);

u64 mdesc_next_arc(काष्ठा mdesc_handle *hp, u64 from, स्थिर अक्षर *arc_type)
अणु
	काष्ठा mdesc_elem *ep, *base = node_block(&hp->mdesc);
	स्थिर अक्षर *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;

	अगर (from == MDESC_NODE_शून्य || from >= last_node)
		वापस MDESC_NODE_शून्य;

	ep = base + from;

	ep++;
	क्रम (; ep->tag != MD_NODE_END; ep++) अणु
		अगर (ep->tag != MD_PROP_ARC)
			जारी;

		अगर (म_भेद(names + ep->name_offset, arc_type))
			जारी;

		वापस ep - base;
	पूर्ण

	वापस MDESC_NODE_शून्य;
पूर्ण
EXPORT_SYMBOL(mdesc_next_arc);

u64 mdesc_arc_target(काष्ठा mdesc_handle *hp, u64 arc)
अणु
	काष्ठा mdesc_elem *ep, *base = node_block(&hp->mdesc);

	ep = base + arc;

	वापस ep->d.val;
पूर्ण
EXPORT_SYMBOL(mdesc_arc_target);

स्थिर अक्षर *mdesc_node_name(काष्ठा mdesc_handle *hp, u64 node)
अणु
	काष्ठा mdesc_elem *ep, *base = node_block(&hp->mdesc);
	स्थिर अक्षर *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;

	अगर (node == MDESC_NODE_शून्य || node >= last_node)
		वापस शून्य;

	ep = base + node;
	अगर (ep->tag != MD_NODE)
		वापस शून्य;

	वापस names + ep->name_offset;
पूर्ण
EXPORT_SYMBOL(mdesc_node_name);

अटल u64 max_cpus = 64;

अटल व्योम __init report_platक्रमm_properties(व्योम)
अणु
	काष्ठा mdesc_handle *hp = mdesc_grab();
	u64 pn = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "platform");
	स्थिर अक्षर *s;
	स्थिर u64 *v;

	अगर (pn == MDESC_NODE_शून्य) अणु
		prom_म_लिखो("No platform node in machine-description.\n");
		prom_halt();
	पूर्ण

	s = mdesc_get_property(hp, pn, "banner-name", शून्य);
	prपूर्णांकk("PLATFORM: banner-name [%s]\n", s);
	s = mdesc_get_property(hp, pn, "name", शून्य);
	prपूर्णांकk("PLATFORM: name [%s]\n", s);

	v = mdesc_get_property(hp, pn, "hostid", शून्य);
	अगर (v)
		prपूर्णांकk("PLATFORM: hostid [%08llx]\n", *v);
	v = mdesc_get_property(hp, pn, "serial#", शून्य);
	अगर (v)
		prपूर्णांकk("PLATFORM: serial# [%08llx]\n", *v);
	v = mdesc_get_property(hp, pn, "stick-frequency", शून्य);
	prपूर्णांकk("PLATFORM: stick-frequency [%08llx]\n", *v);
	v = mdesc_get_property(hp, pn, "mac-address", शून्य);
	अगर (v)
		prपूर्णांकk("PLATFORM: mac-address [%llx]\n", *v);
	v = mdesc_get_property(hp, pn, "watchdog-resolution", शून्य);
	अगर (v)
		prपूर्णांकk("PLATFORM: watchdog-resolution [%llu ms]\n", *v);
	v = mdesc_get_property(hp, pn, "watchdog-max-timeout", शून्य);
	अगर (v)
		prपूर्णांकk("PLATFORM: watchdog-max-timeout [%llu ms]\n", *v);
	v = mdesc_get_property(hp, pn, "max-cpus", शून्य);
	अगर (v) अणु
		max_cpus = *v;
		prपूर्णांकk("PLATFORM: max-cpus [%llu]\n", max_cpus);
	पूर्ण

#अगर_घोषित CONFIG_SMP
	अणु
		पूर्णांक max_cpu, i;

		अगर (v) अणु
			max_cpu = *v;
			अगर (max_cpu > NR_CPUS)
				max_cpu = NR_CPUS;
		पूर्ण अन्यथा अणु
			max_cpu = NR_CPUS;
		पूर्ण
		क्रम (i = 0; i < max_cpu; i++)
			set_cpu_possible(i, true);
	पूर्ण
#पूर्ण_अगर

	mdesc_release(hp);
पूर्ण

अटल व्योम fill_in_one_cache(cpuinfo_sparc *c, काष्ठा mdesc_handle *hp, u64 mp)
अणु
	स्थिर u64 *level = mdesc_get_property(hp, mp, "level", शून्य);
	स्थिर u64 *size = mdesc_get_property(hp, mp, "size", शून्य);
	स्थिर u64 *line_size = mdesc_get_property(hp, mp, "line-size", शून्य);
	स्थिर अक्षर *type;
	पूर्णांक type_len;

	type = mdesc_get_property(hp, mp, "type", &type_len);

	चयन (*level) अणु
	हाल 1:
		अगर (of_find_in_proplist(type, "instn", type_len)) अणु
			c->icache_size = *size;
			c->icache_line_size = *line_size;
		पूर्ण अन्यथा अगर (of_find_in_proplist(type, "data", type_len)) अणु
			c->dcache_size = *size;
			c->dcache_line_size = *line_size;
		पूर्ण
		अवरोध;

	हाल 2:
		c->ecache_size = *size;
		c->ecache_line_size = *line_size;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (*level == 1) अणु
		u64 a;

		mdesc_क्रम_each_arc(a, hp, mp, MDESC_ARC_TYPE_FWD) अणु
			u64 target = mdesc_arc_target(hp, a);
			स्थिर अक्षर *name = mdesc_node_name(hp, target);

			अगर (!म_भेद(name, "cache"))
				fill_in_one_cache(c, hp, target);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम find_back_node_value(काष्ठा mdesc_handle *hp, u64 node,
				 अक्षर *srch_val,
				 व्योम (*func)(काष्ठा mdesc_handle *, u64, पूर्णांक),
				 u64 val, पूर्णांक depth)
अणु
	u64 arc;

	/* Since we have an estimate of recursion depth, करो a sanity check. */
	अगर (depth == 0)
		वापस;

	mdesc_क्रम_each_arc(arc, hp, node, MDESC_ARC_TYPE_BACK) अणु
		u64 n = mdesc_arc_target(hp, arc);
		स्थिर अक्षर *name = mdesc_node_name(hp, n);

		अगर (!म_भेद(srch_val, name))
			(*func)(hp, n, val);

		find_back_node_value(hp, n, srch_val, func, val, depth-1);
	पूर्ण
पूर्ण

अटल व्योम __mark_core_id(काष्ठा mdesc_handle *hp, u64 node,
			   पूर्णांक core_id)
अणु
	स्थिर u64 *id = mdesc_get_property(hp, node, "id", शून्य);

	अगर (*id < num_possible_cpus())
		cpu_data(*id).core_id = core_id;
पूर्ण

अटल व्योम __mark_max_cache_id(काष्ठा mdesc_handle *hp, u64 node,
				पूर्णांक max_cache_id)
अणु
	स्थिर u64 *id = mdesc_get_property(hp, node, "id", शून्य);

	अगर (*id < num_possible_cpus()) अणु
		cpu_data(*id).max_cache_id = max_cache_id;

		/**
		 * On प्रणालीs without explicit socket descriptions socket
		 * is max_cache_id
		 */
		cpu_data(*id).sock_id = max_cache_id;
	पूर्ण
पूर्ण

अटल व्योम mark_core_ids(काष्ठा mdesc_handle *hp, u64 mp,
			  पूर्णांक core_id)
अणु
	find_back_node_value(hp, mp, "cpu", __mark_core_id, core_id, 10);
पूर्ण

अटल व्योम mark_max_cache_ids(काष्ठा mdesc_handle *hp, u64 mp,
			       पूर्णांक max_cache_id)
अणु
	find_back_node_value(hp, mp, "cpu", __mark_max_cache_id,
			     max_cache_id, 10);
पूर्ण

अटल व्योम set_core_ids(काष्ठा mdesc_handle *hp)
अणु
	पूर्णांक idx;
	u64 mp;

	idx = 1;

	/* Identअगरy unique cores by looking क्रम cpus backpoपूर्णांकed to by
	 * level 1 inकाष्ठाion caches.
	 */
	mdesc_क्रम_each_node_by_name(hp, mp, "cache") अणु
		स्थिर u64 *level;
		स्थिर अक्षर *type;
		पूर्णांक len;

		level = mdesc_get_property(hp, mp, "level", शून्य);
		अगर (*level != 1)
			जारी;

		type = mdesc_get_property(hp, mp, "type", &len);
		अगर (!of_find_in_proplist(type, "instn", len))
			जारी;

		mark_core_ids(hp, mp, idx);
		idx++;
	पूर्ण
पूर्ण

अटल पूर्णांक set_max_cache_ids_by_cache(काष्ठा mdesc_handle *hp, पूर्णांक level)
अणु
	u64 mp;
	पूर्णांक idx = 1;
	पूर्णांक fnd = 0;

	/**
	 * Identअगरy unique highest level of shared cache by looking क्रम cpus
	 * backpoपूर्णांकed to by shared level N caches.
	 */
	mdesc_क्रम_each_node_by_name(hp, mp, "cache") अणु
		स्थिर u64 *cur_lvl;

		cur_lvl = mdesc_get_property(hp, mp, "level", शून्य);
		अगर (*cur_lvl != level)
			जारी;
		mark_max_cache_ids(hp, mp, idx);
		idx++;
		fnd = 1;
	पूर्ण
	वापस fnd;
पूर्ण

अटल व्योम set_sock_ids_by_socket(काष्ठा mdesc_handle *hp, u64 mp)
अणु
	पूर्णांक idx = 1;

	mdesc_क्रम_each_node_by_name(hp, mp, "socket") अणु
		u64 a;

		mdesc_क्रम_each_arc(a, hp, mp, MDESC_ARC_TYPE_FWD) अणु
			u64 t = mdesc_arc_target(hp, a);
			स्थिर अक्षर *name;
			स्थिर u64 *id;

			name = mdesc_node_name(hp, t);
			अगर (म_भेद(name, "cpu"))
				जारी;

			id = mdesc_get_property(hp, t, "id", शून्य);
			अगर (*id < num_possible_cpus())
				cpu_data(*id).sock_id = idx;
		पूर्ण
		idx++;
	पूर्ण
पूर्ण

अटल व्योम set_sock_ids(काष्ठा mdesc_handle *hp)
अणु
	u64 mp;

	/**
	 * Find the highest level of shared cache which pre-T7 is also
	 * the socket.
	 */
	अगर (!set_max_cache_ids_by_cache(hp, 3))
		set_max_cache_ids_by_cache(hp, 2);

	/* If machine description exposes sockets data use it.*/
	mp = mdesc_node_by_name(hp, MDESC_NODE_शून्य, "sockets");
	अगर (mp != MDESC_NODE_शून्य)
		set_sock_ids_by_socket(hp, mp);
पूर्ण

अटल व्योम mark_proc_ids(काष्ठा mdesc_handle *hp, u64 mp, पूर्णांक proc_id)
अणु
	u64 a;

	mdesc_क्रम_each_arc(a, hp, mp, MDESC_ARC_TYPE_BACK) अणु
		u64 t = mdesc_arc_target(hp, a);
		स्थिर अक्षर *name;
		स्थिर u64 *id;

		name = mdesc_node_name(hp, t);
		अगर (म_भेद(name, "cpu"))
			जारी;

		id = mdesc_get_property(hp, t, "id", शून्य);
		अगर (*id < NR_CPUS)
			cpu_data(*id).proc_id = proc_id;
	पूर्ण
पूर्ण

अटल व्योम __set_proc_ids(काष्ठा mdesc_handle *hp, स्थिर अक्षर *exec_unit_name)
अणु
	पूर्णांक idx;
	u64 mp;

	idx = 0;
	mdesc_क्रम_each_node_by_name(hp, mp, exec_unit_name) अणु
		स्थिर अक्षर *type;
		पूर्णांक len;

		type = mdesc_get_property(hp, mp, "type", &len);
		अगर (!of_find_in_proplist(type, "int", len) &&
		    !of_find_in_proplist(type, "integer", len))
			जारी;

		mark_proc_ids(hp, mp, idx);
		idx++;
	पूर्ण
पूर्ण

अटल व्योम set_proc_ids(काष्ठा mdesc_handle *hp)
अणु
	__set_proc_ids(hp, "exec_unit");
	__set_proc_ids(hp, "exec-unit");
पूर्ण

अटल व्योम get_one_monकरो_bits(स्थिर u64 *p, अचिन्हित पूर्णांक *mask,
			       अचिन्हित दीर्घ def, अचिन्हित दीर्घ max)
अणु
	u64 val;

	अगर (!p)
		जाओ use_शेष;
	val = *p;

	अगर (!val || val >= 64)
		जाओ use_शेष;

	अगर (val > max)
		val = max;

	*mask = ((1U << val) * 64U) - 1U;
	वापस;

use_शेष:
	*mask = ((1U << def) * 64U) - 1U;
पूर्ण

अटल व्योम get_monकरो_data(काष्ठा mdesc_handle *hp, u64 mp,
			   काष्ठा trap_per_cpu *tb)
अणु
	अटल पूर्णांक prपूर्णांकed;
	स्थिर u64 *val;

	val = mdesc_get_property(hp, mp, "q-cpu-mondo-#bits", शून्य);
	get_one_monकरो_bits(val, &tb->cpu_monकरो_qmask, 7, ilog2(max_cpus * 2));

	val = mdesc_get_property(hp, mp, "q-dev-mondo-#bits", शून्य);
	get_one_monकरो_bits(val, &tb->dev_monकरो_qmask, 7, 8);

	val = mdesc_get_property(hp, mp, "q-resumable-#bits", शून्य);
	get_one_monकरो_bits(val, &tb->resum_qmask, 6, 7);

	val = mdesc_get_property(hp, mp, "q-nonresumable-#bits", शून्य);
	get_one_monकरो_bits(val, &tb->nonresum_qmask, 2, 2);
	अगर (!prपूर्णांकed++) अणु
		pr_info("SUN4V: Mondo queue sizes "
			"[cpu(%u) dev(%u) r(%u) nr(%u)]\n",
			tb->cpu_monकरो_qmask + 1,
			tb->dev_monकरो_qmask + 1,
			tb->resum_qmask + 1,
			tb->nonresum_qmask + 1);
	पूर्ण
पूर्ण

अटल व्योम *mdesc_iterate_over_cpus(व्योम *(*func)(काष्ठा mdesc_handle *, u64, पूर्णांक, व्योम *), व्योम *arg, cpumask_t *mask)
अणु
	काष्ठा mdesc_handle *hp = mdesc_grab();
	व्योम *ret = शून्य;
	u64 mp;

	mdesc_क्रम_each_node_by_name(hp, mp, "cpu") अणु
		स्थिर u64 *id = mdesc_get_property(hp, mp, "id", शून्य);
		पूर्णांक cpuid = *id;

#अगर_घोषित CONFIG_SMP
		अगर (cpuid >= NR_CPUS) अणु
			prपूर्णांकk(KERN_WARNING "Ignoring CPU %d which is "
			       ">= NR_CPUS (%d)\n",
			       cpuid, NR_CPUS);
			जारी;
		पूर्ण
		अगर (!cpumask_test_cpu(cpuid, mask))
			जारी;
#पूर्ण_अगर

		ret = func(hp, mp, cpuid, arg);
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	mdesc_release(hp);
	वापस ret;
पूर्ण

अटल व्योम *record_one_cpu(काष्ठा mdesc_handle *hp, u64 mp, पूर्णांक cpuid,
			    व्योम *arg)
अणु
	ncpus_probed++;
#अगर_घोषित CONFIG_SMP
	set_cpu_present(cpuid, true);
#पूर्ण_अगर
	वापस शून्य;
पूर्ण

व्योम mdesc_populate_present_mask(cpumask_t *mask)
अणु
	अगर (tlb_type != hypervisor)
		वापस;

	ncpus_probed = 0;
	mdesc_iterate_over_cpus(record_one_cpu, शून्य, mask);
पूर्ण

अटल व्योम * __init check_one_pgsz(काष्ठा mdesc_handle *hp, u64 mp, पूर्णांक cpuid, व्योम *arg)
अणु
	स्थिर u64 *pgsz_prop = mdesc_get_property(hp, mp, "mmu-page-size-list", शून्य);
	अचिन्हित दीर्घ *pgsz_mask = arg;
	u64 val;

	val = (HV_PGSZ_MASK_8K | HV_PGSZ_MASK_64K |
	       HV_PGSZ_MASK_512K | HV_PGSZ_MASK_4MB);
	अगर (pgsz_prop)
		val = *pgsz_prop;

	अगर (!*pgsz_mask)
		*pgsz_mask = val;
	अन्यथा
		*pgsz_mask &= val;
	वापस शून्य;
पूर्ण

व्योम __init mdesc_get_page_sizes(cpumask_t *mask, अचिन्हित दीर्घ *pgsz_mask)
अणु
	*pgsz_mask = 0;
	mdesc_iterate_over_cpus(check_one_pgsz, pgsz_mask, mask);
पूर्ण

अटल व्योम *fill_in_one_cpu(काष्ठा mdesc_handle *hp, u64 mp, पूर्णांक cpuid,
			     व्योम *arg)
अणु
	स्थिर u64 *cfreq = mdesc_get_property(hp, mp, "clock-frequency", शून्य);
	काष्ठा trap_per_cpu *tb;
	cpuinfo_sparc *c;
	u64 a;

#अगर_अघोषित CONFIG_SMP
	/* On uniprocessor we only want the values क्रम the
	 * real physical cpu the kernel booted onto, however
	 * cpu_data() only has one entry at index 0.
	 */
	अगर (cpuid != real_hard_smp_processor_id())
		वापस शून्य;
	cpuid = 0;
#पूर्ण_अगर

	c = &cpu_data(cpuid);
	c->घड़ी_प्रकारick = *cfreq;

	tb = &trap_block[cpuid];
	get_monकरो_data(hp, mp, tb);

	mdesc_क्रम_each_arc(a, hp, mp, MDESC_ARC_TYPE_FWD) अणु
		u64 j, t = mdesc_arc_target(hp, a);
		स्थिर अक्षर *t_name;

		t_name = mdesc_node_name(hp, t);
		अगर (!म_भेद(t_name, "cache")) अणु
			fill_in_one_cache(c, hp, t);
			जारी;
		पूर्ण

		mdesc_क्रम_each_arc(j, hp, t, MDESC_ARC_TYPE_FWD) अणु
			u64 n = mdesc_arc_target(hp, j);
			स्थिर अक्षर *n_name;

			n_name = mdesc_node_name(hp, n);
			अगर (!म_भेद(n_name, "cache"))
				fill_in_one_cache(c, hp, n);
		पूर्ण
	पूर्ण

	c->core_id = 0;
	c->proc_id = -1;

	वापस शून्य;
पूर्ण

व्योम mdesc_fill_in_cpu_data(cpumask_t *mask)
अणु
	काष्ठा mdesc_handle *hp;

	mdesc_iterate_over_cpus(fill_in_one_cpu, शून्य, mask);

	hp = mdesc_grab();

	set_core_ids(hp);
	set_proc_ids(hp);
	set_sock_ids(hp);

	mdesc_release(hp);

	smp_fill_in_sib_core_maps();
पूर्ण

/* mdesc_खोलो() - Grab a reference to mdesc_handle when /dev/mdesc is
 * खोलोed. Hold this reference until /dev/mdesc is बंदd to ensure
 * mdesc data काष्ठाure is not released underneath us. Store the
 * poपूर्णांकer to mdesc काष्ठाure in निजी_data क्रम पढ़ो and seek to use
 */
अटल पूर्णांक mdesc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mdesc_handle *hp = mdesc_grab();

	अगर (!hp)
		वापस -ENODEV;

	file->निजी_data = hp;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mdesc_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			  माप_प्रकार len, loff_t *offp)
अणु
	काष्ठा mdesc_handle *hp = file->निजी_data;
	अचिन्हित अक्षर *mdesc;
	पूर्णांक bytes_left, count = len;

	अगर (*offp >= hp->handle_size)
		वापस 0;

	bytes_left = hp->handle_size - *offp;
	अगर (count > bytes_left)
		count = bytes_left;

	mdesc = (अचिन्हित अक्षर *)&hp->mdesc;
	mdesc += *offp;
	अगर (!copy_to_user(buf, mdesc, count)) अणु
		*offp += count;
		वापस count;
	पूर्ण अन्यथा अणु
		वापस -EFAULT;
	पूर्ण
पूर्ण

अटल loff_t mdesc_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा mdesc_handle *hp = file->निजी_data;

	वापस no_seek_end_llseek_size(file, offset, whence, hp->handle_size);
पूर्ण

/* mdesc_बंद() - /dev/mdesc is being बंदd, release the reference to
 * mdesc काष्ठाure.
 */
अटल पूर्णांक mdesc_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	mdesc_release(file->निजी_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations mdesc_fops = अणु
	.खोलो    = mdesc_खोलो,
	.पढ़ो	 = mdesc_पढ़ो,
	.llseek  = mdesc_llseek,
	.release = mdesc_बंद,
	.owner	 = THIS_MODULE,
पूर्ण;

अटल काष्ठा miscdevice mdesc_misc = अणु
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "mdesc",
	.fops	= &mdesc_fops,
पूर्ण;

अटल पूर्णांक __init mdesc_misc_init(व्योम)
अणु
	वापस misc_रेजिस्टर(&mdesc_misc);
पूर्ण

__initcall(mdesc_misc_init);

व्योम __init sun4v_mdesc_init(व्योम)
अणु
	काष्ठा mdesc_handle *hp;
	अचिन्हित दीर्घ len, real_len, status;

	(व्योम) sun4v_mach_desc(0UL, 0UL, &len);

	prपूर्णांकk("MDESC: Size is %lu bytes.\n", len);

	hp = mdesc_alloc(len, &memblock_mdesc_ops);
	अगर (hp == शून्य) अणु
		prom_म_लिखो("MDESC: alloc of %lu bytes failed.\n", len);
		prom_halt();
	पूर्ण

	status = sun4v_mach_desc(__pa(&hp->mdesc), len, &real_len);
	अगर (status != HV_EOK || real_len > len) अणु
		prom_म_लिखो("sun4v_mach_desc fails, err(%lu), "
			    "len(%lu), real_len(%lu)\n",
			    status, len, real_len);
		mdesc_मुक्त(hp);
		prom_halt();
	पूर्ण

	cur_mdesc = hp;

	mdesc_adi_init();
	report_platक्रमm_properties();
पूर्ण
