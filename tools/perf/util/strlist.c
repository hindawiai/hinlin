<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (c) 2009 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */

#समावेश "strlist.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/zभाग.स>

अटल
काष्ठा rb_node *strlist__node_new(काष्ठा rblist *rblist, स्थिर व्योम *entry)
अणु
	स्थिर अक्षर *s = entry;
	काष्ठा rb_node *rc = शून्य;
	काष्ठा strlist *strlist = container_of(rblist, काष्ठा strlist, rblist);
	काष्ठा str_node *snode = दो_स्मृति(माप(*snode));

	अगर (snode != शून्य) अणु
		अगर (strlist->dupstr) अणु
			s = strdup(s);
			अगर (s == शून्य)
				जाओ out_delete;
		पूर्ण
		snode->s = s;
		rc = &snode->rb_node;
	पूर्ण

	वापस rc;

out_delete:
	मुक्त(snode);
	वापस शून्य;
पूर्ण

अटल व्योम str_node__delete(काष्ठा str_node *snode, bool dupstr)
अणु
	अगर (dupstr)
		zमुक्त((अक्षर **)&snode->s);
	मुक्त(snode);
पूर्ण

अटल
व्योम strlist__node_delete(काष्ठा rblist *rblist, काष्ठा rb_node *rb_node)
अणु
	काष्ठा strlist *slist = container_of(rblist, काष्ठा strlist, rblist);
	काष्ठा str_node *snode = container_of(rb_node, काष्ठा str_node, rb_node);

	str_node__delete(snode, slist->dupstr);
पूर्ण

अटल पूर्णांक strlist__node_cmp(काष्ठा rb_node *rb_node, स्थिर व्योम *entry)
अणु
	स्थिर अक्षर *str = entry;
	काष्ठा str_node *snode = container_of(rb_node, काष्ठा str_node, rb_node);

	वापस म_भेद(snode->s, str);
पूर्ण

पूर्णांक strlist__add(काष्ठा strlist *slist, स्थिर अक्षर *new_entry)
अणु
	वापस rblist__add_node(&slist->rblist, new_entry);
पूर्ण

पूर्णांक strlist__load(काष्ठा strlist *slist, स्थिर अक्षर *filename)
अणु
	अक्षर entry[1024];
	पूर्णांक err;
	खाता *fp = ख_खोलो(filename, "r");

	अगर (fp == शून्य)
		वापस -त्रुटि_सं;

	जबतक (ख_माला_लो(entry, माप(entry), fp) != शून्य) अणु
		स्थिर माप_प्रकार len = म_माप(entry);

		अगर (len == 0)
			जारी;
		entry[len - 1] = '\0';

		err = strlist__add(slist, entry);
		अगर (err != 0)
			जाओ out;
	पूर्ण

	err = 0;
out:
	ख_बंद(fp);
	वापस err;
पूर्ण

व्योम strlist__हटाओ(काष्ठा strlist *slist, काष्ठा str_node *snode)
अणु
	rblist__हटाओ_node(&slist->rblist, &snode->rb_node);
पूर्ण

काष्ठा str_node *strlist__find(काष्ठा strlist *slist, स्थिर अक्षर *entry)
अणु
	काष्ठा str_node *snode = शून्य;
	काष्ठा rb_node *rb_node = rblist__find(&slist->rblist, entry);

	अगर (rb_node)
		snode = container_of(rb_node, काष्ठा str_node, rb_node);

	वापस snode;
पूर्ण

अटल पूर्णांक strlist__parse_list_entry(काष्ठा strlist *slist, स्थिर अक्षर *s,
				     स्थिर अक्षर *subst_dir)
अणु
	पूर्णांक err;
	अक्षर *subst = शून्य;

	अगर (म_भेदन(s, "file://", 7) == 0)
		वापस strlist__load(slist, s + 7);

	अगर (subst_dir) अणु
		err = -ENOMEM;
		अगर (aप्र_लिखो(&subst, "%s/%s", subst_dir, s) < 0)
			जाओ out;

		अगर (access(subst, F_OK) == 0) अणु
			err = strlist__load(slist, subst);
			जाओ out;
		पूर्ण

		अगर (slist->file_only) अणु
			err = -ENOENT;
			जाओ out;
		पूर्ण
	पूर्ण

	err = strlist__add(slist, s);
out:
	मुक्त(subst);
	वापस err;
पूर्ण

अटल पूर्णांक strlist__parse_list(काष्ठा strlist *slist, स्थिर अक्षर *s, स्थिर अक्षर *subst_dir)
अणु
	अक्षर *sep;
	पूर्णांक err;

	जबतक ((sep = म_अक्षर(s, ',')) != शून्य) अणु
		*sep = '\0';
		err = strlist__parse_list_entry(slist, s, subst_dir);
		*sep = ',';
		अगर (err != 0)
			वापस err;
		s = sep + 1;
	पूर्ण

	वापस *s ? strlist__parse_list_entry(slist, s, subst_dir) : 0;
पूर्ण

काष्ठा strlist *strlist__new(स्थिर अक्षर *list, स्थिर काष्ठा strlist_config *config)
अणु
	काष्ठा strlist *slist = दो_स्मृति(माप(*slist));

	अगर (slist != शून्य) अणु
		bool dupstr = true;
		bool file_only = false;
		स्थिर अक्षर *स_नाम = शून्य;

		अगर (config) अणु
			dupstr = !config->करोnt_dupstr;
			स_नाम = config->स_नाम;
			file_only = config->file_only;
		पूर्ण

		rblist__init(&slist->rblist);
		slist->rblist.node_cmp    = strlist__node_cmp;
		slist->rblist.node_new    = strlist__node_new;
		slist->rblist.node_delete = strlist__node_delete;

		slist->dupstr	 = dupstr;
		slist->file_only = file_only;

		अगर (list && strlist__parse_list(slist, list, स_नाम) != 0)
			जाओ out_error;
	पूर्ण

	वापस slist;
out_error:
	मुक्त(slist);
	वापस शून्य;
पूर्ण

व्योम strlist__delete(काष्ठा strlist *slist)
अणु
	अगर (slist != शून्य)
		rblist__delete(&slist->rblist);
पूर्ण

काष्ठा str_node *strlist__entry(स्थिर काष्ठा strlist *slist, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा str_node *snode = शून्य;
	काष्ठा rb_node *rb_node;

	rb_node = rblist__entry(&slist->rblist, idx);
	अगर (rb_node)
		snode = container_of(rb_node, काष्ठा str_node, rb_node);

	वापस snode;
पूर्ण
