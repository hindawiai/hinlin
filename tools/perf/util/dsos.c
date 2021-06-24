<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "debug.h"
#समावेश "dsos.h"
#समावेश "dso.h"
#समावेश "vdso.h"
#समावेश "namespaces.h"
#समावेश <libgen.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <symbol.h> // filename__पढ़ो_build_id

अटल पूर्णांक __dso_id__cmp(काष्ठा dso_id *a, काष्ठा dso_id *b)
अणु
	अगर (a->maj > b->maj) वापस -1;
	अगर (a->maj < b->maj) वापस 1;

	अगर (a->min > b->min) वापस -1;
	अगर (a->min < b->min) वापस 1;

	अगर (a->ino > b->ino) वापस -1;
	अगर (a->ino < b->ino) वापस 1;

	अगर (a->ino_generation > b->ino_generation) वापस -1;
	अगर (a->ino_generation < b->ino_generation) वापस 1;

	वापस 0;
पूर्ण

अटल bool dso_id__empty(काष्ठा dso_id *id)
अणु
	अगर (!id)
		वापस true;

	वापस !id->maj && !id->min && !id->ino && !id->ino_generation;
पूर्ण

अटल व्योम dso__inject_id(काष्ठा dso *dso, काष्ठा dso_id *id)
अणु
	dso->id.maj = id->maj;
	dso->id.min = id->min;
	dso->id.ino = id->ino;
	dso->id.ino_generation = id->ino_generation;
पूर्ण

अटल पूर्णांक dso_id__cmp(काष्ठा dso_id *a, काष्ठा dso_id *b)
अणु
	/*
	 * The second is always dso->id, so zeroes अगर not set, assume passing
	 * शून्य क्रम a means a zeroed id
	 */
	अगर (dso_id__empty(a) || dso_id__empty(b))
		वापस 0;

	वापस __dso_id__cmp(a, b);
पूर्ण

पूर्णांक dso__cmp_id(काष्ठा dso *a, काष्ठा dso *b)
अणु
	वापस __dso_id__cmp(&a->id, &b->id);
पूर्ण

bool __dsos__पढ़ो_build_ids(काष्ठा list_head *head, bool with_hits)
अणु
	bool have_build_id = false;
	काष्ठा dso *pos;
	काष्ठा nscookie nsc;

	list_क्रम_each_entry(pos, head, node) अणु
		अगर (with_hits && !pos->hit && !dso__is_vdso(pos))
			जारी;
		अगर (pos->has_build_id) अणु
			have_build_id = true;
			जारी;
		पूर्ण
		nsinfo__mountns_enter(pos->nsinfo, &nsc);
		अगर (filename__पढ़ो_build_id(pos->दीर्घ_name, &pos->bid) > 0) अणु
			have_build_id	  = true;
			pos->has_build_id = true;
		पूर्ण
		nsinfo__mountns_निकास(&nsc);
	पूर्ण

	वापस have_build_id;
पूर्ण

अटल पूर्णांक __dso__cmp_दीर्घ_name(स्थिर अक्षर *दीर्घ_name, काष्ठा dso_id *id, काष्ठा dso *b)
अणु
	पूर्णांक rc = म_भेद(दीर्घ_name, b->दीर्घ_name);
	वापस rc ?: dso_id__cmp(id, &b->id);
पूर्ण

अटल पूर्णांक __dso__cmp_लघु_name(स्थिर अक्षर *लघु_name, काष्ठा dso_id *id, काष्ठा dso *b)
अणु
	पूर्णांक rc = म_भेद(लघु_name, b->लघु_name);
	वापस rc ?: dso_id__cmp(id, &b->id);
पूर्ण

अटल पूर्णांक dso__cmp_लघु_name(काष्ठा dso *a, काष्ठा dso *b)
अणु
	वापस __dso__cmp_लघु_name(a->लघु_name, &a->id, b);
पूर्ण

/*
 * Find a matching entry and/or link current entry to RB tree.
 * Either one of the dso or name parameter must be non-शून्य or the
 * function will not work.
 */
काष्ठा dso *__dsos__findnew_link_by_दीर्घname_id(काष्ठा rb_root *root, काष्ठा dso *dso,
						स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node  *parent = शून्य;

	अगर (!name)
		name = dso->दीर्घ_name;
	/*
	 * Find node with the matching name
	 */
	जबतक (*p) अणु
		काष्ठा dso *this = rb_entry(*p, काष्ठा dso, rb_node);
		पूर्णांक rc = __dso__cmp_दीर्घ_name(name, id, this);

		parent = *p;
		अगर (rc == 0) अणु
			/*
			 * In हाल the new DSO is a duplicate of an existing
			 * one, prपूर्णांक a one-समय warning & put the new entry
			 * at the end of the list of duplicates.
			 */
			अगर (!dso || (dso == this))
				वापस this;	/* Find matching dso */
			/*
			 * The core kernel DSOs may have duplicated दीर्घ name.
			 * In this हाल, the लघु name should be dअगरferent.
			 * Comparing the लघु names to dअगरferentiate the DSOs.
			 */
			rc = dso__cmp_लघु_name(dso, this);
			अगर (rc == 0) अणु
				pr_err("Duplicated dso name: %s\n", name);
				वापस शून्य;
			पूर्ण
		पूर्ण
		अगर (rc < 0)
			p = &parent->rb_left;
		अन्यथा
			p = &parent->rb_right;
	पूर्ण
	अगर (dso) अणु
		/* Add new node and rebalance tree */
		rb_link_node(&dso->rb_node, parent, p);
		rb_insert_color(&dso->rb_node, root);
		dso->root = root;
	पूर्ण
	वापस शून्य;
पूर्ण

व्योम __dsos__add(काष्ठा dsos *dsos, काष्ठा dso *dso)
अणु
	list_add_tail(&dso->node, &dsos->head);
	__dsos__findnew_link_by_दीर्घname_id(&dsos->root, dso, शून्य, &dso->id);
	/*
	 * It is now in the linked list, grab a reference, then garbage collect
	 * this when needing memory, by looking at LRU dso instances in the
	 * list with atomic_पढ़ो(&dso->refcnt) == 1, i.e. no references
	 * anywhere besides the one क्रम the list, करो, under a lock क्रम the
	 * list: हटाओ it from the list, then a dso__put(), that probably will
	 * be the last and will then call dso__delete(), end of lअगरe.
	 *
	 * That, or at the end of the 'struct machine' lअगरeसमय, when all
	 * 'struct dso' instances will be हटाओd from the list, in
	 * dsos__निकास(), अगर they have no other reference from some other data
	 * काष्ठाure.
	 *
	 * E.g.: after processing a 'perf.data' file and storing references
	 * to objects instantiated जबतक processing events, we will have
	 * references to the 'thread', 'map', 'dso' structs all from 'काष्ठा
	 * hist_entry' instances, but we may not need anything not referenced,
	 * so we might as well call machines__निकास()/machines__delete() and
	 * garbage collect it.
	 */
	dso__get(dso);
पूर्ण

व्योम dsos__add(काष्ठा dsos *dsos, काष्ठा dso *dso)
अणु
	करोwn_ग_लिखो(&dsos->lock);
	__dsos__add(dsos, dso);
	up_ग_लिखो(&dsos->lock);
पूर्ण

अटल काष्ठा dso *__dsos__findnew_by_दीर्घname_id(काष्ठा rb_root *root, स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	वापस __dsos__findnew_link_by_दीर्घname_id(root, शून्य, name, id);
पूर्ण

अटल काष्ठा dso *__dsos__find_id(काष्ठा dsos *dsos, स्थिर अक्षर *name, काष्ठा dso_id *id, bool cmp_लघु)
अणु
	काष्ठा dso *pos;

	अगर (cmp_लघु) अणु
		list_क्रम_each_entry(pos, &dsos->head, node)
			अगर (__dso__cmp_लघु_name(name, id, pos) == 0)
				वापस pos;
		वापस शून्य;
	पूर्ण
	वापस __dsos__findnew_by_दीर्घname_id(&dsos->root, name, id);
पूर्ण

काष्ठा dso *__dsos__find(काष्ठा dsos *dsos, स्थिर अक्षर *name, bool cmp_लघु)
अणु
	वापस __dsos__find_id(dsos, name, शून्य, cmp_लघु);
पूर्ण

अटल व्योम dso__set_basename(काष्ठा dso *dso)
अणु
	अक्षर *base, *lname;
	पूर्णांक tid;

	अगर (माला_पूछो(dso->दीर्घ_name, "/tmp/perf-%d.map", &tid) == 1) अणु
		अगर (aप्र_लिखो(&base, "[JIT] tid %d", tid) < 0)
			वापस;
	पूर्ण अन्यथा अणु
	      /*
	       * basename() may modअगरy path buffer, so we must pass
               * a copy.
               */
		lname = strdup(dso->दीर्घ_name);
		अगर (!lname)
			वापस;

		/*
		 * basename() may वापस a poपूर्णांकer to पूर्णांकernal
		 * storage which is reused in subsequent calls
		 * so copy the result.
		 */
		base = strdup(basename(lname));

		मुक्त(lname);

		अगर (!base)
			वापस;
	पूर्ण
	dso__set_लघु_name(dso, base, true);
पूर्ण

अटल काष्ठा dso *__dsos__addnew_id(काष्ठा dsos *dsos, स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	काष्ठा dso *dso = dso__new_id(name, id);

	अगर (dso != शून्य) अणु
		__dsos__add(dsos, dso);
		dso__set_basename(dso);
		/* Put dso here because __dsos_add alपढ़ोy got it */
		dso__put(dso);
	पूर्ण
	वापस dso;
पूर्ण

काष्ठा dso *__dsos__addnew(काष्ठा dsos *dsos, स्थिर अक्षर *name)
अणु
	वापस __dsos__addnew_id(dsos, name, शून्य);
पूर्ण

अटल काष्ठा dso *__dsos__findnew_id(काष्ठा dsos *dsos, स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	काष्ठा dso *dso = __dsos__find_id(dsos, name, id, false);

	अगर (dso && dso_id__empty(&dso->id) && !dso_id__empty(id))
		dso__inject_id(dso, id);

	वापस dso ? dso : __dsos__addnew_id(dsos, name, id);
पूर्ण

काष्ठा dso *dsos__findnew_id(काष्ठा dsos *dsos, स्थिर अक्षर *name, काष्ठा dso_id *id)
अणु
	काष्ठा dso *dso;
	करोwn_ग_लिखो(&dsos->lock);
	dso = dso__get(__dsos__findnew_id(dsos, name, id));
	up_ग_लिखो(&dsos->lock);
	वापस dso;
पूर्ण

माप_प्रकार __dsos__ख_लिखो_buildid(काष्ठा list_head *head, खाता *fp,
			       bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm)
अणु
	काष्ठा dso *pos;
	माप_प्रकार ret = 0;

	list_क्रम_each_entry(pos, head, node) अणु
		अक्षर sbuild_id[SBUILD_ID_SIZE];

		अगर (skip && skip(pos, parm))
			जारी;
		build_id__प्र_लिखो(&pos->bid, sbuild_id);
		ret += ख_लिखो(fp, "%-40s %s\n", sbuild_id, pos->दीर्घ_name);
	पूर्ण
	वापस ret;
पूर्ण

माप_प्रकार __dsos__ख_लिखो(काष्ठा list_head *head, खाता *fp)
अणु
	काष्ठा dso *pos;
	माप_प्रकार ret = 0;

	list_क्रम_each_entry(pos, head, node) अणु
		ret += dso__ख_लिखो(pos, fp);
	पूर्ण

	वापस ret;
पूर्ण
