<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * call-path.h: Manipulate a tree data काष्ठाure containing function call paths
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/rbtree.h>
#समावेश <linux/list.h>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>

#समावेश "call-path.h"

अटल व्योम call_path__init(काष्ठा call_path *cp, काष्ठा call_path *parent,
			    काष्ठा symbol *sym, u64 ip, bool in_kernel)
अणु
	cp->parent = parent;
	cp->sym = sym;
	cp->ip = sym ? 0 : ip;
	cp->db_id = 0;
	cp->in_kernel = in_kernel;
	RB_CLEAR_NODE(&cp->rb_node);
	cp->children = RB_ROOT;
पूर्ण

काष्ठा call_path_root *call_path_root__new(व्योम)
अणु
	काष्ठा call_path_root *cpr;

	cpr = zalloc(माप(काष्ठा call_path_root));
	अगर (!cpr)
		वापस शून्य;
	call_path__init(&cpr->call_path, शून्य, शून्य, 0, false);
	INIT_LIST_HEAD(&cpr->blocks);
	वापस cpr;
पूर्ण

व्योम call_path_root__मुक्त(काष्ठा call_path_root *cpr)
अणु
	काष्ठा call_path_block *pos, *n;

	list_क्रम_each_entry_safe(pos, n, &cpr->blocks, node) अणु
		list_del_init(&pos->node);
		मुक्त(pos);
	पूर्ण
	मुक्त(cpr);
पूर्ण

अटल काष्ठा call_path *call_path__new(काष्ठा call_path_root *cpr,
					काष्ठा call_path *parent,
					काष्ठा symbol *sym, u64 ip,
					bool in_kernel)
अणु
	काष्ठा call_path_block *cpb;
	काष्ठा call_path *cp;
	माप_प्रकार n;

	अगर (cpr->next < cpr->sz) अणु
		cpb = list_last_entry(&cpr->blocks, काष्ठा call_path_block,
				      node);
	पूर्ण अन्यथा अणु
		cpb = zalloc(माप(काष्ठा call_path_block));
		अगर (!cpb)
			वापस शून्य;
		list_add_tail(&cpb->node, &cpr->blocks);
		cpr->sz += CALL_PATH_BLOCK_SIZE;
	पूर्ण

	n = cpr->next++ & CALL_PATH_BLOCK_MASK;
	cp = &cpb->cp[n];

	call_path__init(cp, parent, sym, ip, in_kernel);

	वापस cp;
पूर्ण

काष्ठा call_path *call_path__findnew(काष्ठा call_path_root *cpr,
				     काष्ठा call_path *parent,
				     काष्ठा symbol *sym, u64 ip, u64 ks)
अणु
	काष्ठा rb_node **p;
	काष्ठा rb_node *node_parent = शून्य;
	काष्ठा call_path *cp;
	bool in_kernel = ip >= ks;

	अगर (sym)
		ip = 0;

	अगर (!parent)
		वापस call_path__new(cpr, parent, sym, ip, in_kernel);

	p = &parent->children.rb_node;
	जबतक (*p != शून्य) अणु
		node_parent = *p;
		cp = rb_entry(node_parent, काष्ठा call_path, rb_node);

		अगर (cp->sym == sym && cp->ip == ip)
			वापस cp;

		अगर (sym < cp->sym || (sym == cp->sym && ip < cp->ip))
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	cp = call_path__new(cpr, parent, sym, ip, in_kernel);
	अगर (!cp)
		वापस शून्य;

	rb_link_node(&cp->rb_node, node_parent, p);
	rb_insert_color(&cp->rb_node, &parent->children);

	वापस cp;
पूर्ण
