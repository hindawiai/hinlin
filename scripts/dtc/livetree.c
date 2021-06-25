<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * (C) Copyright David Gibson <dwg@au1.ibm.com>, IBM Corporation.  2005.
 */

#समावेश "dtc.h"
#समावेश "srcpos.h"

/*
 * Tree building functions
 */

व्योम add_label(काष्ठा label **labels, अक्षर *label)
अणु
	काष्ठा label *new;

	/* Make sure the label isn't alपढ़ोy there */
	क्रम_each_label_withdel(*labels, new)
		अगर (streq(new->label, label)) अणु
			new->deleted = 0;
			वापस;
		पूर्ण

	new = xदो_स्मृति(माप(*new));
	स_रखो(new, 0, माप(*new));
	new->label = label;
	new->next = *labels;
	*labels = new;
पूर्ण

व्योम delete_labels(काष्ठा label **labels)
अणु
	काष्ठा label *label;

	क्रम_each_label(*labels, label)
		label->deleted = 1;
पूर्ण

काष्ठा property *build_property(अक्षर *name, काष्ठा data val,
				काष्ठा srcpos *srcpos)
अणु
	काष्ठा property *new = xदो_स्मृति(माप(*new));

	स_रखो(new, 0, माप(*new));

	new->name = name;
	new->val = val;
	new->srcpos = srcpos_copy(srcpos);

	वापस new;
पूर्ण

काष्ठा property *build_property_delete(अक्षर *name)
अणु
	काष्ठा property *new = xदो_स्मृति(माप(*new));

	स_रखो(new, 0, माप(*new));

	new->name = name;
	new->deleted = 1;

	वापस new;
पूर्ण

काष्ठा property *chain_property(काष्ठा property *first, काष्ठा property *list)
अणु
	निश्चित(first->next == शून्य);

	first->next = list;
	वापस first;
पूर्ण

काष्ठा property *reverse_properties(काष्ठा property *first)
अणु
	काष्ठा property *p = first;
	काष्ठा property *head = शून्य;
	काष्ठा property *next;

	जबतक (p) अणु
		next = p->next;
		p->next = head;
		head = p;
		p = next;
	पूर्ण
	वापस head;
पूर्ण

काष्ठा node *build_node(काष्ठा property *proplist, काष्ठा node *children,
			काष्ठा srcpos *srcpos)
अणु
	काष्ठा node *new = xदो_स्मृति(माप(*new));
	काष्ठा node *child;

	स_रखो(new, 0, माप(*new));

	new->proplist = reverse_properties(proplist);
	new->children = children;
	new->srcpos = srcpos_copy(srcpos);

	क्रम_each_child(new, child) अणु
		child->parent = new;
	पूर्ण

	वापस new;
पूर्ण

काष्ठा node *build_node_delete(काष्ठा srcpos *srcpos)
अणु
	काष्ठा node *new = xदो_स्मृति(माप(*new));

	स_रखो(new, 0, माप(*new));

	new->deleted = 1;
	new->srcpos = srcpos_copy(srcpos);

	वापस new;
पूर्ण

काष्ठा node *name_node(काष्ठा node *node, अक्षर *name)
अणु
	निश्चित(node->name == शून्य);

	node->name = name;

	वापस node;
पूर्ण

काष्ठा node *omit_node_अगर_unused(काष्ठा node *node)
अणु
	node->omit_अगर_unused = 1;

	वापस node;
पूर्ण

काष्ठा node *reference_node(काष्ठा node *node)
अणु
	node->is_referenced = 1;

	वापस node;
पूर्ण

काष्ठा node *merge_nodes(काष्ठा node *old_node, काष्ठा node *new_node)
अणु
	काष्ठा property *new_prop, *old_prop;
	काष्ठा node *new_child, *old_child;
	काष्ठा label *l;

	old_node->deleted = 0;

	/* Add new node labels to old node */
	क्रम_each_label_withdel(new_node->labels, l)
		add_label(&old_node->labels, l->label);

	/* Move properties from the new node to the old node.  If there
	 * is a collision, replace the old value with the new */
	जबतक (new_node->proplist) अणु
		/* Pop the property off the list */
		new_prop = new_node->proplist;
		new_node->proplist = new_prop->next;
		new_prop->next = शून्य;

		अगर (new_prop->deleted) अणु
			delete_property_by_name(old_node, new_prop->name);
			मुक्त(new_prop);
			जारी;
		पूर्ण

		/* Look क्रम a collision, set new value अगर there is */
		क्रम_each_property_withdel(old_node, old_prop) अणु
			अगर (streq(old_prop->name, new_prop->name)) अणु
				/* Add new labels to old property */
				क्रम_each_label_withdel(new_prop->labels, l)
					add_label(&old_prop->labels, l->label);

				old_prop->val = new_prop->val;
				old_prop->deleted = 0;
				मुक्त(old_prop->srcpos);
				old_prop->srcpos = new_prop->srcpos;
				मुक्त(new_prop);
				new_prop = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		/* अगर no collision occurred, add property to the old node. */
		अगर (new_prop)
			add_property(old_node, new_prop);
	पूर्ण

	/* Move the override child nodes पूर्णांकo the primary node.  If
	 * there is a collision, then merge the nodes. */
	जबतक (new_node->children) अणु
		/* Pop the child node off the list */
		new_child = new_node->children;
		new_node->children = new_child->next_sibling;
		new_child->parent = शून्य;
		new_child->next_sibling = शून्य;

		अगर (new_child->deleted) अणु
			delete_node_by_name(old_node, new_child->name);
			मुक्त(new_child);
			जारी;
		पूर्ण

		/* Search क्रम a collision.  Merge अगर there is */
		क्रम_each_child_withdel(old_node, old_child) अणु
			अगर (streq(old_child->name, new_child->name)) अणु
				merge_nodes(old_child, new_child);
				new_child = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण

		/* अगर no collision occurred, add child to the old node. */
		अगर (new_child)
			add_child(old_node, new_child);
	पूर्ण

	old_node->srcpos = srcpos_extend(old_node->srcpos, new_node->srcpos);

	/* The new node contents are now merged पूर्णांकo the old node.  Free
	 * the new node. */
	मुक्त(new_node);

	वापस old_node;
पूर्ण

काष्ठा node * add_orphan_node(काष्ठा node *dt, काष्ठा node *new_node, अक्षर *ref)
अणु
	अटल अचिन्हित पूर्णांक next_orphan_fragment = 0;
	काष्ठा node *node;
	काष्ठा property *p;
	काष्ठा data d = empty_data;
	अक्षर *name;

	अगर (ref[0] == '/') अणु
		d = data_add_marker(d, TYPE_STRING, ref);
		d = data_append_data(d, ref, म_माप(ref) + 1);

		p = build_property("target-path", d, शून्य);
	पूर्ण अन्यथा अणु
		d = data_add_marker(d, REF_PHANDLE, ref);
		d = data_append_पूर्णांकeger(d, 0xffffffff, 32);

		p = build_property("target", d, शून्य);
	पूर्ण

	xaप्र_लिखो(&name, "fragment@%u",
			next_orphan_fragment++);
	name_node(new_node, "__overlay__");
	node = build_node(p, new_node, शून्य);
	name_node(node, name);

	add_child(dt, node);
	वापस dt;
पूर्ण

काष्ठा node *chain_node(काष्ठा node *first, काष्ठा node *list)
अणु
	निश्चित(first->next_sibling == शून्य);

	first->next_sibling = list;
	वापस first;
पूर्ण

व्योम add_property(काष्ठा node *node, काष्ठा property *prop)
अणु
	काष्ठा property **p;

	prop->next = शून्य;

	p = &node->proplist;
	जबतक (*p)
		p = &((*p)->next);

	*p = prop;
पूर्ण

व्योम delete_property_by_name(काष्ठा node *node, अक्षर *name)
अणु
	काष्ठा property *prop = node->proplist;

	जबतक (prop) अणु
		अगर (streq(prop->name, name)) अणु
			delete_property(prop);
			वापस;
		पूर्ण
		prop = prop->next;
	पूर्ण
पूर्ण

व्योम delete_property(काष्ठा property *prop)
अणु
	prop->deleted = 1;
	delete_labels(&prop->labels);
पूर्ण

व्योम add_child(काष्ठा node *parent, काष्ठा node *child)
अणु
	काष्ठा node **p;

	child->next_sibling = शून्य;
	child->parent = parent;

	p = &parent->children;
	जबतक (*p)
		p = &((*p)->next_sibling);

	*p = child;
पूर्ण

व्योम delete_node_by_name(काष्ठा node *parent, अक्षर *name)
अणु
	काष्ठा node *node = parent->children;

	जबतक (node) अणु
		अगर (streq(node->name, name)) अणु
			delete_node(node);
			वापस;
		पूर्ण
		node = node->next_sibling;
	पूर्ण
पूर्ण

व्योम delete_node(काष्ठा node *node)
अणु
	काष्ठा property *prop;
	काष्ठा node *child;

	node->deleted = 1;
	क्रम_each_child(node, child)
		delete_node(child);
	क्रम_each_property(node, prop)
		delete_property(prop);
	delete_labels(&node->labels);
पूर्ण

व्योम append_to_property(काष्ठा node *node,
			अक्षर *name, स्थिर व्योम *data, पूर्णांक len,
			क्रमागत markertype type)
अणु
	काष्ठा data d;
	काष्ठा property *p;

	p = get_property(node, name);
	अगर (p) अणु
		d = data_add_marker(p->val, type, name);
		d = data_append_data(d, data, len);
		p->val = d;
	पूर्ण अन्यथा अणु
		d = data_add_marker(empty_data, type, name);
		d = data_append_data(d, data, len);
		p = build_property(name, d, शून्य);
		add_property(node, p);
	पूर्ण
पूर्ण

काष्ठा reserve_info *build_reserve_entry(uपूर्णांक64_t address, uपूर्णांक64_t size)
अणु
	काष्ठा reserve_info *new = xदो_स्मृति(माप(*new));

	स_रखो(new, 0, माप(*new));

	new->address = address;
	new->size = size;

	वापस new;
पूर्ण

काष्ठा reserve_info *chain_reserve_entry(काष्ठा reserve_info *first,
					काष्ठा reserve_info *list)
अणु
	निश्चित(first->next == शून्य);

	first->next = list;
	वापस first;
पूर्ण

काष्ठा reserve_info *add_reserve_entry(काष्ठा reserve_info *list,
				      काष्ठा reserve_info *new)
अणु
	काष्ठा reserve_info *last;

	new->next = शून्य;

	अगर (! list)
		वापस new;

	क्रम (last = list; last->next; last = last->next)
		;

	last->next = new;

	वापस list;
पूर्ण

काष्ठा dt_info *build_dt_info(अचिन्हित पूर्णांक dtsflags,
			      काष्ठा reserve_info *reservelist,
			      काष्ठा node *tree, uपूर्णांक32_t boot_cpuid_phys)
अणु
	काष्ठा dt_info *dti;

	dti = xदो_स्मृति(माप(*dti));
	dti->dtsflags = dtsflags;
	dti->reservelist = reservelist;
	dti->dt = tree;
	dti->boot_cpuid_phys = boot_cpuid_phys;

	वापस dti;
पूर्ण

/*
 * Tree accessor functions
 */

स्थिर अक्षर *get_unitname(काष्ठा node *node)
अणु
	अगर (node->name[node->basenamelen] == '\0')
		वापस "";
	अन्यथा
		वापस node->name + node->basenamelen + 1;
पूर्ण

काष्ठा property *get_property(काष्ठा node *node, स्थिर अक्षर *propname)
अणु
	काष्ठा property *prop;

	क्रम_each_property(node, prop)
		अगर (streq(prop->name, propname))
			वापस prop;

	वापस शून्य;
पूर्ण

cell_t propval_cell(काष्ठा property *prop)
अणु
	निश्चित(prop->val.len == माप(cell_t));
	वापस fdt32_to_cpu(*((fdt32_t *)prop->val.val));
पूर्ण

cell_t propval_cell_n(काष्ठा property *prop, अचिन्हित पूर्णांक n)
अणु
	निश्चित(prop->val.len / माप(cell_t) >= n);
	वापस fdt32_to_cpu(*((fdt32_t *)prop->val.val + n));
पूर्ण

काष्ठा property *get_property_by_label(काष्ठा node *tree, स्थिर अक्षर *label,
				       काष्ठा node **node)
अणु
	काष्ठा property *prop;
	काष्ठा node *c;

	*node = tree;

	क्रम_each_property(tree, prop) अणु
		काष्ठा label *l;

		क्रम_each_label(prop->labels, l)
			अगर (streq(l->label, label))
				वापस prop;
	पूर्ण

	क्रम_each_child(tree, c) अणु
		prop = get_property_by_label(c, label, node);
		अगर (prop)
			वापस prop;
	पूर्ण

	*node = शून्य;
	वापस शून्य;
पूर्ण

काष्ठा marker *get_marker_label(काष्ठा node *tree, स्थिर अक्षर *label,
				काष्ठा node **node, काष्ठा property **prop)
अणु
	काष्ठा marker *m;
	काष्ठा property *p;
	काष्ठा node *c;

	*node = tree;

	क्रम_each_property(tree, p) अणु
		*prop = p;
		m = p->val.markers;
		क्रम_each_marker_of_type(m, LABEL)
			अगर (streq(m->ref, label))
				वापस m;
	पूर्ण

	क्रम_each_child(tree, c) अणु
		m = get_marker_label(c, label, node, prop);
		अगर (m)
			वापस m;
	पूर्ण

	*prop = शून्य;
	*node = शून्य;
	वापस शून्य;
पूर्ण

काष्ठा node *get_subnode(काष्ठा node *node, स्थिर अक्षर *nodename)
अणु
	काष्ठा node *child;

	क्रम_each_child(node, child)
		अगर (streq(child->name, nodename))
			वापस child;

	वापस शून्य;
पूर्ण

काष्ठा node *get_node_by_path(काष्ठा node *tree, स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *p;
	काष्ठा node *child;

	अगर (!path || ! (*path)) अणु
		अगर (tree->deleted)
			वापस शून्य;
		वापस tree;
	पूर्ण

	जबतक (path[0] == '/')
		path++;

	p = म_अक्षर(path, '/');

	क्रम_each_child(tree, child) अणु
		अगर (p && strprefixeq(path, p - path, child->name))
			वापस get_node_by_path(child, p+1);
		अन्यथा अगर (!p && streq(path, child->name))
			वापस child;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा node *get_node_by_label(काष्ठा node *tree, स्थिर अक्षर *label)
अणु
	काष्ठा node *child, *node;
	काष्ठा label *l;

	निश्चित(label && (म_माप(label) > 0));

	क्रम_each_label(tree->labels, l)
		अगर (streq(l->label, label))
			वापस tree;

	क्रम_each_child(tree, child) अणु
		node = get_node_by_label(child, label);
		अगर (node)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा node *get_node_by_phandle(काष्ठा node *tree, cell_t phandle)
अणु
	काष्ठा node *child, *node;

	अगर ((phandle == 0) || (phandle == -1)) अणु
		निश्चित(generate_fixups);
		वापस शून्य;
	पूर्ण

	अगर (tree->phandle == phandle) अणु
		अगर (tree->deleted)
			वापस शून्य;
		वापस tree;
	पूर्ण

	क्रम_each_child(tree, child) अणु
		node = get_node_by_phandle(child, phandle);
		अगर (node)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा node *get_node_by_ref(काष्ठा node *tree, स्थिर अक्षर *ref)
अणु
	अगर (streq(ref, "/"))
		वापस tree;
	अन्यथा अगर (ref[0] == '/')
		वापस get_node_by_path(tree, ref);
	अन्यथा
		वापस get_node_by_label(tree, ref);
पूर्ण

cell_t get_node_phandle(काष्ठा node *root, काष्ठा node *node)
अणु
	अटल cell_t phandle = 1; /* FIXME: ick, अटल local */
	काष्ठा data d = empty_data;

	अगर ((node->phandle != 0) && (node->phandle != -1))
		वापस node->phandle;

	जबतक (get_node_by_phandle(root, phandle))
		phandle++;

	node->phandle = phandle;

	d = data_add_marker(d, TYPE_UINT32, शून्य);
	d = data_append_cell(d, phandle);

	अगर (!get_property(node, "linux,phandle")
	    && (phandle_क्रमmat & PHANDLE_LEGACY))
		add_property(node, build_property("linux,phandle", d, शून्य));

	अगर (!get_property(node, "phandle")
	    && (phandle_क्रमmat & PHANDLE_EPAPR))
		add_property(node, build_property("phandle", d, शून्य));

	/* If the node *करोes* have a phandle property, we must
	 * be dealing with a self-referencing phandle, which will be
	 * fixed up momentarily in the caller */

	वापस node->phandle;
पूर्ण

uपूर्णांक32_t guess_boot_cpuid(काष्ठा node *tree)
अणु
	काष्ठा node *cpus, *bootcpu;
	काष्ठा property *reg;

	cpus = get_node_by_path(tree, "/cpus");
	अगर (!cpus)
		वापस 0;


	bootcpu = cpus->children;
	अगर (!bootcpu)
		वापस 0;

	reg = get_property(bootcpu, "reg");
	अगर (!reg || (reg->val.len != माप(uपूर्णांक32_t)))
		वापस 0;

	/* FIXME: Sanity check node? */

	वापस propval_cell(reg);
पूर्ण

अटल पूर्णांक cmp_reserve_info(स्थिर व्योम *ax, स्थिर व्योम *bx)
अणु
	स्थिर काष्ठा reserve_info *a, *b;

	a = *((स्थिर काष्ठा reserve_info * स्थिर *)ax);
	b = *((स्थिर काष्ठा reserve_info * स्थिर *)bx);

	अगर (a->address < b->address)
		वापस -1;
	अन्यथा अगर (a->address > b->address)
		वापस 1;
	अन्यथा अगर (a->size < b->size)
		वापस -1;
	अन्यथा अगर (a->size > b->size)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम sort_reserve_entries(काष्ठा dt_info *dti)
अणु
	काष्ठा reserve_info *ri, **tbl;
	पूर्णांक n = 0, i = 0;

	क्रम (ri = dti->reservelist;
	     ri;
	     ri = ri->next)
		n++;

	अगर (n == 0)
		वापस;

	tbl = xदो_स्मृति(n * माप(*tbl));

	क्रम (ri = dti->reservelist;
	     ri;
	     ri = ri->next)
		tbl[i++] = ri;

	क्विक(tbl, n, माप(*tbl), cmp_reserve_info);

	dti->reservelist = tbl[0];
	क्रम (i = 0; i < (n-1); i++)
		tbl[i]->next = tbl[i+1];
	tbl[n-1]->next = शून्य;

	मुक्त(tbl);
पूर्ण

अटल पूर्णांक cmp_prop(स्थिर व्योम *ax, स्थिर व्योम *bx)
अणु
	स्थिर काष्ठा property *a, *b;

	a = *((स्थिर काष्ठा property * स्थिर *)ax);
	b = *((स्थिर काष्ठा property * स्थिर *)bx);

	वापस म_भेद(a->name, b->name);
पूर्ण

अटल व्योम sort_properties(काष्ठा node *node)
अणु
	पूर्णांक n = 0, i = 0;
	काष्ठा property *prop, **tbl;

	क्रम_each_property_withdel(node, prop)
		n++;

	अगर (n == 0)
		वापस;

	tbl = xदो_स्मृति(n * माप(*tbl));

	क्रम_each_property_withdel(node, prop)
		tbl[i++] = prop;

	क्विक(tbl, n, माप(*tbl), cmp_prop);

	node->proplist = tbl[0];
	क्रम (i = 0; i < (n-1); i++)
		tbl[i]->next = tbl[i+1];
	tbl[n-1]->next = शून्य;

	मुक्त(tbl);
पूर्ण

अटल पूर्णांक cmp_subnode(स्थिर व्योम *ax, स्थिर व्योम *bx)
अणु
	स्थिर काष्ठा node *a, *b;

	a = *((स्थिर काष्ठा node * स्थिर *)ax);
	b = *((स्थिर काष्ठा node * स्थिर *)bx);

	वापस म_भेद(a->name, b->name);
पूर्ण

अटल व्योम sort_subnodes(काष्ठा node *node)
अणु
	पूर्णांक n = 0, i = 0;
	काष्ठा node *subnode, **tbl;

	क्रम_each_child_withdel(node, subnode)
		n++;

	अगर (n == 0)
		वापस;

	tbl = xदो_स्मृति(n * माप(*tbl));

	क्रम_each_child_withdel(node, subnode)
		tbl[i++] = subnode;

	क्विक(tbl, n, माप(*tbl), cmp_subnode);

	node->children = tbl[0];
	क्रम (i = 0; i < (n-1); i++)
		tbl[i]->next_sibling = tbl[i+1];
	tbl[n-1]->next_sibling = शून्य;

	मुक्त(tbl);
पूर्ण

अटल व्योम sort_node(काष्ठा node *node)
अणु
	काष्ठा node *c;

	sort_properties(node);
	sort_subnodes(node);
	क्रम_each_child_withdel(node, c)
		sort_node(c);
पूर्ण

व्योम sort_tree(काष्ठा dt_info *dti)
अणु
	sort_reserve_entries(dti);
	sort_node(dti->dt);
पूर्ण

/* utility helper to aव्योम code duplication */
अटल काष्ठा node *build_and_name_child_node(काष्ठा node *parent, अक्षर *name)
अणु
	काष्ठा node *node;

	node = build_node(शून्य, शून्य, शून्य);
	name_node(node, xstrdup(name));
	add_child(parent, node);

	वापस node;
पूर्ण

अटल काष्ठा node *build_root_node(काष्ठा node *dt, अक्षर *name)
अणु
	काष्ठा node *an;

	an = get_subnode(dt, name);
	अगर (!an)
		an = build_and_name_child_node(dt, name);

	अगर (!an)
		die("Could not build root node /%s\n", name);

	वापस an;
पूर्ण

अटल bool any_label_tree(काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा node *c;

	अगर (node->labels)
		वापस true;

	क्रम_each_child(node, c)
		अगर (any_label_tree(dti, c))
			वापस true;

	वापस false;
पूर्ण

अटल व्योम generate_label_tree_पूर्णांकernal(काष्ठा dt_info *dti,
					 काष्ठा node *an, काष्ठा node *node,
					 bool allocph)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा node *c;
	काष्ठा property *p;
	काष्ठा label *l;

	/* अगर there are labels */
	अगर (node->labels) अणु

		/* now add the label in the node */
		क्रम_each_label(node->labels, l) अणु

			/* check whether the label alपढ़ोy exists */
			p = get_property(an, l->label);
			अगर (p) अणु
				ख_लिखो(मानक_त्रुटि, "WARNING: label %s already"
					" exists in /%s", l->label,
					an->name);
				जारी;
			पूर्ण

			/* insert it */
			p = build_property(l->label,
				data_copy_escape_string(node->fullpath,
						म_माप(node->fullpath)),
				शून्य);
			add_property(an, p);
		पूर्ण

		/* क्रमce allocation of a phandle क्रम this node */
		अगर (allocph)
			(व्योम)get_node_phandle(dt, node);
	पूर्ण

	क्रम_each_child(node, c)
		generate_label_tree_पूर्णांकernal(dti, an, c, allocph);
पूर्ण

अटल bool any_fixup_tree(काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा node *c;
	काष्ठा property *prop;
	काष्ठा marker *m;

	क्रम_each_property(node, prop) अणु
		m = prop->val.markers;
		क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
			अगर (!get_node_by_ref(dti->dt, m->ref))
				वापस true;
		पूर्ण
	पूर्ण

	क्रम_each_child(node, c) अणु
		अगर (any_fixup_tree(dti, c))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम add_fixup_entry(काष्ठा dt_info *dti, काष्ठा node *fn,
			    काष्ठा node *node, काष्ठा property *prop,
			    काष्ठा marker *m)
अणु
	अक्षर *entry;

	/* m->ref can only be a REF_PHANDLE, but check anyway */
	निश्चित(m->type == REF_PHANDLE);

	/* there shouldn't be any ':' in the arguments */
	अगर (म_अक्षर(node->fullpath, ':') || strchr(prop->name, ':'))
		die("arguments should not contain ':'\n");

	xaप्र_लिखो(&entry, "%s:%s:%u",
			node->fullpath, prop->name, m->offset);
	append_to_property(fn, m->ref, entry, म_माप(entry) + 1, TYPE_STRING);

	मुक्त(entry);
पूर्ण

अटल व्योम generate_fixups_tree_पूर्णांकernal(काष्ठा dt_info *dti,
					  काष्ठा node *fn,
					  काष्ठा node *node)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा node *c;
	काष्ठा property *prop;
	काष्ठा marker *m;
	काष्ठा node *refnode;

	क्रम_each_property(node, prop) अणु
		m = prop->val.markers;
		क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
			refnode = get_node_by_ref(dt, m->ref);
			अगर (!refnode)
				add_fixup_entry(dti, fn, node, prop, m);
		पूर्ण
	पूर्ण

	क्रम_each_child(node, c)
		generate_fixups_tree_पूर्णांकernal(dti, fn, c);
पूर्ण

अटल bool any_local_fixup_tree(काष्ठा dt_info *dti, काष्ठा node *node)
अणु
	काष्ठा node *c;
	काष्ठा property *prop;
	काष्ठा marker *m;

	क्रम_each_property(node, prop) अणु
		m = prop->val.markers;
		क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
			अगर (get_node_by_ref(dti->dt, m->ref))
				वापस true;
		पूर्ण
	पूर्ण

	क्रम_each_child(node, c) अणु
		अगर (any_local_fixup_tree(dti, c))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम add_local_fixup_entry(काष्ठा dt_info *dti,
		काष्ठा node *lfn, काष्ठा node *node,
		काष्ठा property *prop, काष्ठा marker *m,
		काष्ठा node *refnode)
अणु
	काष्ठा node *wn, *nwn;	/* local fixup node, walk node, new */
	fdt32_t value_32;
	अक्षर **compp;
	पूर्णांक i, depth;

	/* walk back retrieving depth */
	depth = 0;
	क्रम (wn = node; wn; wn = wn->parent)
		depth++;

	/* allocate name array */
	compp = xदो_स्मृति(माप(*compp) * depth);

	/* store names in the array */
	क्रम (wn = node, i = depth - 1; wn; wn = wn->parent, i--)
		compp[i] = wn->name;

	/* walk the path components creating nodes अगर they करोn't exist */
	क्रम (wn = lfn, i = 1; i < depth; i++, wn = nwn) अणु
		/* अगर no node exists, create it */
		nwn = get_subnode(wn, compp[i]);
		अगर (!nwn)
			nwn = build_and_name_child_node(wn, compp[i]);
	पूर्ण

	मुक्त(compp);

	value_32 = cpu_to_fdt32(m->offset);
	append_to_property(wn, prop->name, &value_32, माप(value_32), TYPE_UINT32);
पूर्ण

अटल व्योम generate_local_fixups_tree_पूर्णांकernal(काष्ठा dt_info *dti,
						काष्ठा node *lfn,
						काष्ठा node *node)
अणु
	काष्ठा node *dt = dti->dt;
	काष्ठा node *c;
	काष्ठा property *prop;
	काष्ठा marker *m;
	काष्ठा node *refnode;

	क्रम_each_property(node, prop) अणु
		m = prop->val.markers;
		क्रम_each_marker_of_type(m, REF_PHANDLE) अणु
			refnode = get_node_by_ref(dt, m->ref);
			अगर (refnode)
				add_local_fixup_entry(dti, lfn, node, prop, m, refnode);
		पूर्ण
	पूर्ण

	क्रम_each_child(node, c)
		generate_local_fixups_tree_पूर्णांकernal(dti, lfn, c);
पूर्ण

व्योम generate_label_tree(काष्ठा dt_info *dti, अक्षर *name, bool allocph)
अणु
	अगर (!any_label_tree(dti, dti->dt))
		वापस;
	generate_label_tree_पूर्णांकernal(dti, build_root_node(dti->dt, name),
				     dti->dt, allocph);
पूर्ण

व्योम generate_fixups_tree(काष्ठा dt_info *dti, अक्षर *name)
अणु
	अगर (!any_fixup_tree(dti, dti->dt))
		वापस;
	generate_fixups_tree_पूर्णांकernal(dti, build_root_node(dti->dt, name),
				      dti->dt);
पूर्ण

व्योम generate_local_fixups_tree(काष्ठा dt_info *dti, अक्षर *name)
अणु
	अगर (!any_local_fixup_tree(dti, dti->dt))
		वापस;
	generate_local_fixups_tree_पूर्णांकernal(dti, build_root_node(dti->dt, name),
					    dti->dt);
पूर्ण
