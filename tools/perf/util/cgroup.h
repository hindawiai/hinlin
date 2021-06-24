<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CGROUP_H__
#घोषणा __CGROUP_H__

#समावेश <linux/refcount.h>
#समावेश <linux/rbtree.h>
#समावेश "util/env.h"

काष्ठा option;

काष्ठा cgroup अणु
	काष्ठा rb_node		node;
	u64			id;
	अक्षर			*name;
	पूर्णांक			fd;
	refcount_t		refcnt;
पूर्ण;

बाह्य पूर्णांक nr_cgroups; /* number of explicit cgroups defined */

काष्ठा cgroup *cgroup__get(काष्ठा cgroup *cgroup);
व्योम cgroup__put(काष्ठा cgroup *cgroup);

काष्ठा evlist;
काष्ठा rblist;

काष्ठा cgroup *evlist__findnew_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *name);
पूर्णांक evlist__expand_cgroup(काष्ठा evlist *evlist, स्थिर अक्षर *cgroups,
			  काष्ठा rblist *metric_events, bool खोलो_cgroup);

व्योम evlist__set_शेष_cgroup(काष्ठा evlist *evlist, काष्ठा cgroup *cgroup);

पूर्णांक parse_cgroups(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);

काष्ठा cgroup *cgroup__findnew(काष्ठा perf_env *env, uपूर्णांक64_t id,
			       स्थिर अक्षर *path);
काष्ठा cgroup *cgroup__find(काष्ठा perf_env *env, uपूर्णांक64_t id);

व्योम perf_env__purge_cgroups(काष्ठा perf_env *env);

#पूर्ण_अगर /* __CGROUP_H__ */
