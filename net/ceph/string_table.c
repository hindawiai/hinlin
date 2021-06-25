<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/gfp.h>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/ceph/string_table.h>

अटल DEFINE_SPINLOCK(string_tree_lock);
अटल काष्ठा rb_root string_tree = RB_ROOT;

काष्ठा ceph_string *ceph_find_or_create_string(स्थिर अक्षर* str, माप_प्रकार len)
अणु
	काष्ठा ceph_string *cs, *exist;
	काष्ठा rb_node **p, *parent;
	पूर्णांक ret;

	exist = शून्य;
	spin_lock(&string_tree_lock);
	p = &string_tree.rb_node;
	जबतक (*p) अणु
		exist = rb_entry(*p, काष्ठा ceph_string, node);
		ret = ceph_compare_string(exist, str, len);
		अगर (ret > 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (ret < 0)
			p = &(*p)->rb_right;
		अन्यथा
			अवरोध;
		exist = शून्य;
	पूर्ण
	अगर (exist && !kref_get_unless_zero(&exist->kref)) अणु
		rb_erase(&exist->node, &string_tree);
		RB_CLEAR_NODE(&exist->node);
		exist = शून्य;
	पूर्ण
	spin_unlock(&string_tree_lock);
	अगर (exist)
		वापस exist;

	cs = kदो_स्मृति(माप(*cs) + len + 1, GFP_NOFS);
	अगर (!cs)
		वापस शून्य;

	kref_init(&cs->kref);
	cs->len = len;
	स_नकल(cs->str, str, len);
	cs->str[len] = 0;

retry:
	exist = शून्य;
	parent = शून्य;
	p = &string_tree.rb_node;
	spin_lock(&string_tree_lock);
	जबतक (*p) अणु
		parent = *p;
		exist = rb_entry(*p, काष्ठा ceph_string, node);
		ret = ceph_compare_string(exist, str, len);
		अगर (ret > 0)
			p = &(*p)->rb_left;
		अन्यथा अगर (ret < 0)
			p = &(*p)->rb_right;
		अन्यथा
			अवरोध;
		exist = शून्य;
	पूर्ण
	ret = 0;
	अगर (!exist) अणु
		rb_link_node(&cs->node, parent, p);
		rb_insert_color(&cs->node, &string_tree);
	पूर्ण अन्यथा अगर (!kref_get_unless_zero(&exist->kref)) अणु
		rb_erase(&exist->node, &string_tree);
		RB_CLEAR_NODE(&exist->node);
		ret = -EAGAIN;
	पूर्ण
	spin_unlock(&string_tree_lock);
	अगर (ret == -EAGAIN)
		जाओ retry;

	अगर (exist) अणु
		kमुक्त(cs);
		cs = exist;
	पूर्ण

	वापस cs;
पूर्ण
EXPORT_SYMBOL(ceph_find_or_create_string);

व्योम ceph_release_string(काष्ठा kref *ref)
अणु
	काष्ठा ceph_string *cs = container_of(ref, काष्ठा ceph_string, kref);

	spin_lock(&string_tree_lock);
	अगर (!RB_EMPTY_NODE(&cs->node)) अणु
		rb_erase(&cs->node, &string_tree);
		RB_CLEAR_NODE(&cs->node);
	पूर्ण
	spin_unlock(&string_tree_lock);

	kमुक्त_rcu(cs, rcu);
पूर्ण
EXPORT_SYMBOL(ceph_release_string);

bool ceph_strings_empty(व्योम)
अणु
	वापस RB_EMPTY_ROOT(&string_tree);
पूर्ण
