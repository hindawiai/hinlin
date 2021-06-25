<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on पूर्णांकlist.c by:
 * (c) 2009 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <linux/compiler.h>

#समावेश "intlist.h"

अटल काष्ठा rb_node *पूर्णांकlist__node_new(काष्ठा rblist *rblist __maybe_unused,
					 स्थिर व्योम *entry)
अणु
	अचिन्हित दीर्घ i = (अचिन्हित दीर्घ)entry;
	काष्ठा rb_node *rc = शून्य;
	काष्ठा पूर्णांक_node *node = दो_स्मृति(माप(*node));

	अगर (node != शून्य) अणु
		node->i = i;
		node->priv = शून्य;
		rc = &node->rb_node;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम पूर्णांक_node__delete(काष्ठा पूर्णांक_node *ilist)
अणु
	मुक्त(ilist);
पूर्ण

अटल व्योम पूर्णांकlist__node_delete(काष्ठा rblist *rblist __maybe_unused,
				 काष्ठा rb_node *rb_node)
अणु
	काष्ठा पूर्णांक_node *node = container_of(rb_node, काष्ठा पूर्णांक_node, rb_node);

	पूर्णांक_node__delete(node);
पूर्ण

अटल पूर्णांक पूर्णांकlist__node_cmp(काष्ठा rb_node *rb_node, स्थिर व्योम *entry)
अणु
	अचिन्हित दीर्घ i = (अचिन्हित दीर्घ)entry;
	काष्ठा पूर्णांक_node *node = container_of(rb_node, काष्ठा पूर्णांक_node, rb_node);

	अगर (node->i > i)
		वापस 1;
	अन्यथा अगर (node->i < i)
		वापस -1;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकlist__add(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i)
अणु
	वापस rblist__add_node(&ilist->rblist, (व्योम *)i);
पूर्ण

व्योम पूर्णांकlist__हटाओ(काष्ठा पूर्णांकlist *ilist, काष्ठा पूर्णांक_node *node)
अणु
	rblist__हटाओ_node(&ilist->rblist, &node->rb_node);
पूर्ण

अटल काष्ठा पूर्णांक_node *__पूर्णांकlist__findnew(काष्ठा पूर्णांकlist *ilist,
					   अचिन्हित दीर्घ i, bool create)
अणु
	काष्ठा पूर्णांक_node *node = शून्य;
	काष्ठा rb_node *rb_node;

	अगर (ilist == शून्य)
		वापस शून्य;

	अगर (create)
		rb_node = rblist__findnew(&ilist->rblist, (व्योम *)i);
	अन्यथा
		rb_node = rblist__find(&ilist->rblist, (व्योम *)i);

	अगर (rb_node)
		node = container_of(rb_node, काष्ठा पूर्णांक_node, rb_node);

	वापस node;
पूर्ण

काष्ठा पूर्णांक_node *पूर्णांकlist__find(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i)
अणु
	वापस __पूर्णांकlist__findnew(ilist, i, false);
पूर्ण

काष्ठा पूर्णांक_node *पूर्णांकlist__findnew(काष्ठा पूर्णांकlist *ilist, अचिन्हित दीर्घ i)
अणु
	वापस __पूर्णांकlist__findnew(ilist, i, true);
पूर्ण

अटल पूर्णांक पूर्णांकlist__parse_list(काष्ठा पूर्णांकlist *ilist, स्थिर अक्षर *s)
अणु
	अक्षर *sep;
	पूर्णांक err;

	करो अणु
		अचिन्हित दीर्घ value = म_से_दीर्घ(s, &sep, 10);
		err = -EINVAL;
		अगर (*sep != ',' && *sep != '\0')
			अवरोध;
		err = पूर्णांकlist__add(ilist, value);
		अगर (err)
			अवरोध;
		s = sep + 1;
	पूर्ण जबतक (*sep != '\0');

	वापस err;
पूर्ण

काष्ठा पूर्णांकlist *पूर्णांकlist__new(स्थिर अक्षर *slist)
अणु
	काष्ठा पूर्णांकlist *ilist = दो_स्मृति(माप(*ilist));

	अगर (ilist != शून्य) अणु
		rblist__init(&ilist->rblist);
		ilist->rblist.node_cmp    = पूर्णांकlist__node_cmp;
		ilist->rblist.node_new    = पूर्णांकlist__node_new;
		ilist->rblist.node_delete = पूर्णांकlist__node_delete;

		अगर (slist && पूर्णांकlist__parse_list(ilist, slist))
			जाओ out_delete;
	पूर्ण

	वापस ilist;
out_delete:
	पूर्णांकlist__delete(ilist);
	वापस शून्य;
पूर्ण

व्योम पूर्णांकlist__delete(काष्ठा पूर्णांकlist *ilist)
अणु
	अगर (ilist != शून्य)
		rblist__delete(&ilist->rblist);
पूर्ण

काष्ठा पूर्णांक_node *पूर्णांकlist__entry(स्थिर काष्ठा पूर्णांकlist *ilist, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा पूर्णांक_node *node = शून्य;
	काष्ठा rb_node *rb_node;

	rb_node = rblist__entry(&ilist->rblist, idx);
	अगर (rb_node)
		node = container_of(rb_node, काष्ठा पूर्णांक_node, rb_node);

	वापस node;
पूर्ण
