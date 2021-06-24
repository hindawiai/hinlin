<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <subcmd/parse-options.h>
#समावेश "evsel.h"
#समावेश "cgroup.h"
#समावेश "evlist.h"
#समावेश "rblist.h"
#समावेश "metricgroup.h"
#समावेश "stat.h"
#समावेश <linux/zभाग.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <api/fs/fs.h>
#समावेश <ftw.h>
#समावेश <regex.h>

पूर्णांक nr_cgroups;

/* used to match cgroup name with patterns */
काष्ठा cgroup_name अणु
	काष्ठा list_head list;
	bool used;
	अक्षर name[];
पूर्ण;
अटल LIST_HEAD(cgroup_list);

अटल पूर्णांक खोलो_cgroup(स्थिर अक्षर *name)
अणु
	अक्षर path[PATH_MAX + 1];
	अक्षर mnt[PATH_MAX + 1];
	पूर्णांक fd;


	अगर (cgroupfs_find_mountpoपूर्णांक(mnt, PATH_MAX + 1, "perf_event"))
		वापस -1;

	scnम_लिखो(path, PATH_MAX, "%s/%s", mnt, name);

	fd = खोलो(path, O_RDONLY);
	अगर (fd == -1)
		ख_लिखो(मानक_त्रुटि, "no access to cgroup %s\n", path);

	वापस fd;
पूर्ण

अटल काष्ठा cgroup *evlist__find_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *str)
अणु
	काष्ठा evsel *counter;
	/*
	 * check अगर cgrp is alपढ़ोy defined, अगर so we reuse it
	 */
	evlist__क्रम_each_entry(evlist, counter) अणु
		अगर (!counter->cgrp)
			जारी;
		अगर (!म_भेद(counter->cgrp->name, str))
			वापस cgroup__get(counter->cgrp);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा cgroup *cgroup__new(स्थिर अक्षर *name, bool करो_खोलो)
अणु
	काष्ठा cgroup *cgroup = zalloc(माप(*cgroup));

	अगर (cgroup != शून्य) अणु
		refcount_set(&cgroup->refcnt, 1);

		cgroup->name = strdup(name);
		अगर (!cgroup->name)
			जाओ out_err;

		अगर (करो_खोलो) अणु
			cgroup->fd = खोलो_cgroup(name);
			अगर (cgroup->fd == -1)
				जाओ out_मुक्त_name;
		पूर्ण अन्यथा अणु
			cgroup->fd = -1;
		पूर्ण
	पूर्ण

	वापस cgroup;

out_मुक्त_name:
	zमुक्त(&cgroup->name);
out_err:
	मुक्त(cgroup);
	वापस शून्य;
पूर्ण

काष्ठा cgroup *evlist__findnew_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *name)
अणु
	काष्ठा cgroup *cgroup = evlist__find_cgroup(evlist, name);

	वापस cgroup ?: cgroup__new(name, true);
पूर्ण

अटल पूर्णांक add_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *str)
अणु
	काष्ठा evsel *counter;
	काष्ठा cgroup *cgrp = evlist__findnew_cgroup(evlist, str);
	पूर्णांक n;

	अगर (!cgrp)
		वापस -1;
	/*
	 * find corresponding event
	 * अगर add cgroup N, then need to find event N
	 */
	n = 0;
	evlist__क्रम_each_entry(evlist, counter) अणु
		अगर (n == nr_cgroups)
			जाओ found;
		n++;
	पूर्ण

	cgroup__put(cgrp);
	वापस -1;
found:
	counter->cgrp = cgrp;
	वापस 0;
पूर्ण

अटल व्योम cgroup__delete(काष्ठा cgroup *cgroup)
अणु
	अगर (cgroup->fd >= 0)
		बंद(cgroup->fd);
	zमुक्त(&cgroup->name);
	मुक्त(cgroup);
पूर्ण

व्योम cgroup__put(काष्ठा cgroup *cgrp)
अणु
	अगर (cgrp && refcount_dec_and_test(&cgrp->refcnt)) अणु
		cgroup__delete(cgrp);
	पूर्ण
पूर्ण

काष्ठा cgroup *cgroup__get(काष्ठा cgroup *cgroup)
अणु
       अगर (cgroup)
		refcount_inc(&cgroup->refcnt);
       वापस cgroup;
पूर्ण

अटल व्योम evsel__set_शेष_cgroup(काष्ठा evsel *evsel, काष्ठा cgroup *cgroup)
अणु
	अगर (evsel->cgrp == शून्य)
		evsel->cgrp = cgroup__get(cgroup);
पूर्ण

व्योम evlist__set_शेष_cgroup(काष्ठा evlist *evlist, काष्ठा cgroup *cgroup)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel)
		evsel__set_शेष_cgroup(evsel, cgroup);
पूर्ण

/* helper function क्रम ftw() in match_cgroups and list_cgroups */
अटल पूर्णांक add_cgroup_name(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb __maybe_unused,
			   पूर्णांक typeflag, काष्ठा FTW *ftwbuf __maybe_unused)
अणु
	काष्ठा cgroup_name *cn;

	अगर (typeflag != FTW_D)
		वापस 0;

	cn = दो_स्मृति(माप(*cn) + म_माप(fpath) + 1);
	अगर (cn == शून्य)
		वापस -1;

	cn->used = false;
	म_नकल(cn->name, fpath);

	list_add_tail(&cn->list, &cgroup_list);
	वापस 0;
पूर्ण

अटल व्योम release_cgroup_list(व्योम)
अणु
	काष्ठा cgroup_name *cn;

	जबतक (!list_empty(&cgroup_list)) अणु
		cn = list_first_entry(&cgroup_list, काष्ठा cgroup_name, list);
		list_del(&cn->list);
		मुक्त(cn);
	पूर्ण
पूर्ण

/* collect given cgroups only */
अटल पूर्णांक list_cgroups(स्थिर अक्षर *str)
अणु
	स्थिर अक्षर *p, *e, *eos = str + म_माप(str);
	काष्ठा cgroup_name *cn;
	अक्षर *s;

	/* use given name as is - क्रम testing purpose */
	क्रम (;;) अणु
		p = म_अक्षर(str, ',');
		e = p ? p : eos;

		अगर (e - str) अणु
			पूर्णांक ret;

			s = strndup(str, e - str);
			अगर (!s)
				वापस -1;
			/* pretend अगर it's added by ftw() */
			ret = add_cgroup_name(s, शून्य, FTW_D, शून्य);
			मुक्त(s);
			अगर (ret)
				वापस -1;
		पूर्ण अन्यथा अणु
			अगर (add_cgroup_name("", शून्य, FTW_D, शून्य) < 0)
				वापस -1;
		पूर्ण

		अगर (!p)
			अवरोध;
		str = p+1;
	पूर्ण

	/* these groups will be used */
	list_क्रम_each_entry(cn, &cgroup_list, list)
		cn->used = true;

	वापस 0;
पूर्ण

/* collect all cgroups first and then match with the pattern */
अटल पूर्णांक match_cgroups(स्थिर अक्षर *str)
अणु
	अक्षर mnt[PATH_MAX];
	स्थिर अक्षर *p, *e, *eos = str + म_माप(str);
	काष्ठा cgroup_name *cn;
	regex_t reg;
	पूर्णांक prefix_len;
	अक्षर *s;

	अगर (cgroupfs_find_mountpoपूर्णांक(mnt, माप(mnt), "perf_event"))
		वापस -1;

	/* cgroup_name will have a full path, skip the root directory */
	prefix_len = म_माप(mnt);

	/* collect all cgroups in the cgroup_list */
	अगर (nftw(mnt, add_cgroup_name, 20, 0) < 0)
		वापस -1;

	क्रम (;;) अणु
		p = म_अक्षर(str, ',');
		e = p ? p : eos;

		/* allow empty cgroups, i.e., skip */
		अगर (e - str) अणु
			/* termination added */
			s = strndup(str, e - str);
			अगर (!s)
				वापस -1;
			अगर (regcomp(&reg, s, REG_NOSUB)) अणु
				मुक्त(s);
				वापस -1;
			पूर्ण

			/* check cgroup name with the pattern */
			list_क्रम_each_entry(cn, &cgroup_list, list) अणु
				अक्षर *name = cn->name + prefix_len;

				अगर (name[0] == '/' && name[1])
					name++;
				अगर (!regexec(&reg, name, 0, शून्य, 0))
					cn->used = true;
			पूर्ण
			regमुक्त(&reg);
			मुक्त(s);
		पूर्ण अन्यथा अणु
			/* first entry to root cgroup */
			cn = list_first_entry(&cgroup_list, काष्ठा cgroup_name,
					      list);
			cn->used = true;
		पूर्ण

		अगर (!p)
			अवरोध;
		str = p+1;
	पूर्ण
	वापस prefix_len;
पूर्ण

पूर्णांक parse_cgroups(स्थिर काष्ठा option *opt, स्थिर अक्षर *str,
		  पूर्णांक unset __maybe_unused)
अणु
	काष्ठा evlist *evlist = *(काष्ठा evlist **)opt->value;
	काष्ठा evsel *counter;
	काष्ठा cgroup *cgrp = शून्य;
	स्थिर अक्षर *p, *e, *eos = str + म_माप(str);
	अक्षर *s;
	पूर्णांक ret, i;

	अगर (list_empty(&evlist->core.entries)) अणु
		ख_लिखो(मानक_त्रुटि, "must define events before cgroups\n");
		वापस -1;
	पूर्ण

	क्रम (;;) अणु
		p = म_अक्षर(str, ',');
		e = p ? p : eos;

		/* allow empty cgroups, i.e., skip */
		अगर (e - str) अणु
			/* termination added */
			s = strndup(str, e - str);
			अगर (!s)
				वापस -1;
			ret = add_cgroup(evlist, s);
			मुक्त(s);
			अगर (ret)
				वापस -1;
		पूर्ण
		/* nr_cgroups is increased een क्रम empty cgroups */
		nr_cgroups++;
		अगर (!p)
			अवरोध;
		str = p+1;
	पूर्ण
	/* क्रम the हाल one cgroup combine to multiple events */
	i = 0;
	अगर (nr_cgroups == 1) अणु
		evlist__क्रम_each_entry(evlist, counter) अणु
			अगर (i == 0)
				cgrp = counter->cgrp;
			अन्यथा अणु
				counter->cgrp = cgrp;
				refcount_inc(&cgrp->refcnt);
			पूर्ण
			i++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल bool has_pattern_string(स्थिर अक्षर *str)
अणु
	वापस !!strpbrk(str, "अणुपूर्ण[]()|*+?^$");
पूर्ण

पूर्णांक evlist__expand_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *str,
			  काष्ठा rblist *metric_events, bool खोलो_cgroup)
अणु
	काष्ठा evlist *orig_list, *पंचांगp_list;
	काष्ठा evsel *pos, *evsel, *leader;
	काष्ठा rblist orig_metric_events;
	काष्ठा cgroup *cgrp = शून्य;
	काष्ठा cgroup_name *cn;
	पूर्णांक ret = -1;
	पूर्णांक prefix_len;

	अगर (evlist->core.nr_entries == 0) अणु
		ख_लिखो(मानक_त्रुटि, "must define events before cgroups\n");
		वापस -EINVAL;
	पूर्ण

	orig_list = evlist__new();
	पंचांगp_list = evlist__new();
	अगर (orig_list == शून्य || पंचांगp_list == शून्य) अणु
		ख_लिखो(मानक_त्रुटि, "memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण

	/* save original events and init evlist */
	evlist__splice_list_tail(orig_list, &evlist->core.entries);
	evlist->core.nr_entries = 0;

	अगर (metric_events) अणु
		orig_metric_events = *metric_events;
		rblist__init(metric_events);
	पूर्ण अन्यथा अणु
		rblist__init(&orig_metric_events);
	पूर्ण

	अगर (has_pattern_string(str))
		prefix_len = match_cgroups(str);
	अन्यथा
		prefix_len = list_cgroups(str);

	अगर (prefix_len < 0)
		जाओ out_err;

	list_क्रम_each_entry(cn, &cgroup_list, list) अणु
		अक्षर *name;

		अगर (!cn->used)
			जारी;

		/* cgroup_name might have a full path, skip the prefix */
		name = cn->name + prefix_len;
		अगर (name[0] == '/' && name[1])
			name++;
		cgrp = cgroup__new(name, खोलो_cgroup);
		अगर (cgrp == शून्य)
			जाओ out_err;

		leader = शून्य;
		evlist__क्रम_each_entry(orig_list, pos) अणु
			evsel = evsel__clone(pos);
			अगर (evsel == शून्य)
				जाओ out_err;

			cgroup__put(evsel->cgrp);
			evsel->cgrp = cgroup__get(cgrp);

			अगर (evsel__is_group_leader(pos))
				leader = evsel;
			evsel->leader = leader;

			evlist__add(पंचांगp_list, evsel);
		पूर्ण
		/* cgroup__new() has a refcount, release it here */
		cgroup__put(cgrp);
		nr_cgroups++;

		अगर (metric_events) अणु
			perf_stat__collect_metric_expr(पंचांगp_list);
			अगर (metricgroup__copy_metric_events(पंचांगp_list, cgrp,
							    metric_events,
							    &orig_metric_events) < 0)
				जाओ out_err;
		पूर्ण

		evlist__splice_list_tail(evlist, &पंचांगp_list->core.entries);
		पंचांगp_list->core.nr_entries = 0;
	पूर्ण

	अगर (list_empty(&evlist->core.entries)) अणु
		ख_लिखो(मानक_त्रुटि, "no cgroup matched: %s\n", str);
		जाओ out_err;
	पूर्ण

	ret = 0;

out_err:
	evlist__delete(orig_list);
	evlist__delete(पंचांगp_list);
	rblist__निकास(&orig_metric_events);
	release_cgroup_list();

	वापस ret;
पूर्ण

अटल काष्ठा cgroup *__cgroup__findnew(काष्ठा rb_root *root, uपूर्णांक64_t id,
					bool create, स्थिर अक्षर *path)
अणु
	काष्ठा rb_node **p = &root->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा cgroup *cgrp;

	जबतक (*p != शून्य) अणु
		parent = *p;
		cgrp = rb_entry(parent, काष्ठा cgroup, node);

		अगर (cgrp->id == id)
			वापस cgrp;

		अगर (cgrp->id < id)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	अगर (!create)
		वापस शून्य;

	cgrp = दो_स्मृति(माप(*cgrp));
	अगर (cgrp == शून्य)
		वापस शून्य;

	cgrp->name = strdup(path);
	अगर (cgrp->name == शून्य) अणु
		मुक्त(cgrp);
		वापस शून्य;
	पूर्ण

	cgrp->fd = -1;
	cgrp->id = id;
	refcount_set(&cgrp->refcnt, 1);

	rb_link_node(&cgrp->node, parent, p);
	rb_insert_color(&cgrp->node, root);

	वापस cgrp;
पूर्ण

काष्ठा cgroup *cgroup__findnew(काष्ठा perf_env *env, uपूर्णांक64_t id,
			       स्थिर अक्षर *path)
अणु
	काष्ठा cgroup *cgrp;

	करोwn_ग_लिखो(&env->cgroups.lock);
	cgrp = __cgroup__findnew(&env->cgroups.tree, id, true, path);
	up_ग_लिखो(&env->cgroups.lock);
	वापस cgrp;
पूर्ण

काष्ठा cgroup *cgroup__find(काष्ठा perf_env *env, uपूर्णांक64_t id)
अणु
	काष्ठा cgroup *cgrp;

	करोwn_पढ़ो(&env->cgroups.lock);
	cgrp = __cgroup__findnew(&env->cgroups.tree, id, false, शून्य);
	up_पढ़ो(&env->cgroups.lock);
	वापस cgrp;
पूर्ण

व्योम perf_env__purge_cgroups(काष्ठा perf_env *env)
अणु
	काष्ठा rb_node *node;
	काष्ठा cgroup *cgrp;

	करोwn_ग_लिखो(&env->cgroups.lock);
	जबतक (!RB_EMPTY_ROOT(&env->cgroups.tree)) अणु
		node = rb_first(&env->cgroups.tree);
		cgrp = rb_entry(node, काष्ठा cgroup, node);

		rb_erase(node, &env->cgroups.tree);
		cgroup__put(cgrp);
	पूर्ण
	up_ग_लिखो(&env->cgroups.lock);
पूर्ण
