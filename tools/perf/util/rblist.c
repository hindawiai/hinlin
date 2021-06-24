<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on strlist.c by:
 * (c) 2009 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "rblist.h"

पूर्णांक rblist__add_node(काष्ठा rblist *rblist, स्थिर व्योम *new_entry)
अणु
	काष्ठा rb_node **p = &rblist->entries.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य, *new_node;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		पूर्णांक rc;

		parent = *p;

		rc = rblist->node_cmp(parent, new_entry);
		अगर (rc > 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (rc < 0) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	new_node = rblist->node_new(rblist, new_entry);
	अगर (new_node == शून्य)
		वापस -ENOMEM;

	rb_link_node(new_node, parent, p);
	rb_insert_color_cached(new_node, &rblist->entries, lefपंचांगost);
	++rblist->nr_entries;

	वापस 0;
पूर्ण

व्योम rblist__हटाओ_node(काष्ठा rblist *rblist, काष्ठा rb_node *rb_node)
अणु
	rb_erase_cached(rb_node, &rblist->entries);
	--rblist->nr_entries;
	rblist->node_delete(rblist, rb_node);
पूर्ण

अटल काष्ठा rb_node *__rblist__findnew(काष्ठा rblist *rblist,
					 स्थिर व्योम *entry,
					 bool create)
अणु
	काष्ठा rb_node **p = &rblist->entries.rb_root.rb_node;
	काष्ठा rb_node *parent = शून्य, *new_node = शून्य;
	bool lefपंचांगost = true;

	जबतक (*p != शून्य) अणु
		पूर्णांक rc;

		parent = *p;

		rc = rblist->node_cmp(parent, entry);
		अगर (rc > 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (rc < 0) अणु
			p = &(*p)->rb_right;
			lefपंचांगost = false;
		पूर्ण
		अन्यथा
			वापस parent;
	पूर्ण

	अगर (create) अणु
		new_node = rblist->node_new(rblist, entry);
		अगर (new_node) अणु
			rb_link_node(new_node, parent, p);
			rb_insert_color_cached(new_node,
					       &rblist->entries, lefपंचांगost);
			++rblist->nr_entries;
		पूर्ण
	पूर्ण

	वापस new_node;
पूर्ण

काष्ठा rb_node *rblist__find(काष्ठा rblist *rblist, स्थिर व्योम *entry)
अणु
	वापस __rblist__findnew(rblist, entry, false);
पूर्ण

काष्ठा rb_node *rblist__findnew(काष्ठा rblist *rblist, स्थिर व्योम *entry)
अणु
	वापस __rblist__findnew(rblist, entry, true);
पूर्ण

व्योम rblist__init(काष्ठा rblist *rblist)
अणु
	अगर (rblist != शून्य) अणु
		rblist->entries	 = RB_ROOT_CACHED;
		rblist->nr_entries = 0;
	पूर्ण

	वापस;
पूर्ण

व्योम rblist__निकास(काष्ठा rblist *rblist)
अणु
	काष्ठा rb_node *pos, *next = rb_first_cached(&rblist->entries);

	जबतक (next) अणु
		pos = next;
		next = rb_next(pos);
		rblist__हटाओ_node(rblist, pos);
	पूर्ण
पूर्ण

व्योम rblist__delete(काष्ठा rblist *rblist)
अणु
	अगर (rblist != शून्य) अणु
		rblist__निकास(rblist);
		मुक्त(rblist);
	पूर्ण
पूर्ण

काष्ठा rb_node *rblist__entry(स्थिर काष्ठा rblist *rblist, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा rb_node *node;

	क्रम (node = rb_first_cached(&rblist->entries); node;
	     node = rb_next(node)) अणु
		अगर (!idx--)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण
