<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <stdbool.h>
#समावेश <मानककोष.स>

#घोषणा PAGE_SIZE 4096

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

#घोषणा MB(x) (x << 20)

/*
 * Checks अगर two given values dअगरfer by less than err% of their sum.
 */
अटल अंतरभूत पूर्णांक values_बंद(दीर्घ a, दीर्घ b, पूर्णांक err)
अणु
	वापस असल(a - b) <= (a + b) / 100 * err;
पूर्ण

बाह्य पूर्णांक cg_find_unअगरied_root(अक्षर *root, माप_प्रकार len);
बाह्य अक्षर *cg_name(स्थिर अक्षर *root, स्थिर अक्षर *name);
बाह्य अक्षर *cg_name_indexed(स्थिर अक्षर *root, स्थिर अक्षर *name, पूर्णांक index);
बाह्य अक्षर *cg_control(स्थिर अक्षर *cgroup, स्थिर अक्षर *control);
बाह्य पूर्णांक cg_create(स्थिर अक्षर *cgroup);
बाह्य पूर्णांक cg_destroy(स्थिर अक्षर *cgroup);
बाह्य पूर्णांक cg_पढ़ो(स्थिर अक्षर *cgroup, स्थिर अक्षर *control,
		   अक्षर *buf, माप_प्रकार len);
बाह्य पूर्णांक cg_पढ़ो_म_भेद(स्थिर अक्षर *cgroup, स्थिर अक्षर *control,
			  स्थिर अक्षर *expected);
बाह्य पूर्णांक cg_पढ़ो_म_माला(स्थिर अक्षर *cgroup, स्थिर अक्षर *control,
			  स्थिर अक्षर *needle);
बाह्य दीर्घ cg_पढ़ो_दीर्घ(स्थिर अक्षर *cgroup, स्थिर अक्षर *control);
दीर्घ cg_पढ़ो_key_दीर्घ(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, स्थिर अक्षर *key);
बाह्य दीर्घ cg_पढ़ो_lc(स्थिर अक्षर *cgroup, स्थिर अक्षर *control);
बाह्य पूर्णांक cg_ग_लिखो(स्थिर अक्षर *cgroup, स्थिर अक्षर *control, अक्षर *buf);
बाह्य पूर्णांक cg_run(स्थिर अक्षर *cgroup,
		  पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
		  व्योम *arg);
बाह्य पूर्णांक cg_enter(स्थिर अक्षर *cgroup, पूर्णांक pid);
बाह्य पूर्णांक cg_enter_current(स्थिर अक्षर *cgroup);
बाह्य पूर्णांक cg_enter_current_thपढ़ो(स्थिर अक्षर *cgroup);
बाह्य पूर्णांक cg_run_noरुको(स्थिर अक्षर *cgroup,
			 पूर्णांक (*fn)(स्थिर अक्षर *cgroup, व्योम *arg),
			 व्योम *arg);
बाह्य पूर्णांक get_temp_fd(व्योम);
बाह्य पूर्णांक alloc_pagecache(पूर्णांक fd, माप_प्रकार size);
बाह्य पूर्णांक alloc_anon(स्थिर अक्षर *cgroup, व्योम *arg);
बाह्य पूर्णांक is_swap_enabled(व्योम);
बाह्य पूर्णांक set_oom_adj_score(पूर्णांक pid, पूर्णांक score);
बाह्य पूर्णांक cg_रुको_क्रम_proc_count(स्थिर अक्षर *cgroup, पूर्णांक count);
बाह्य पूर्णांक cg_समाप्तall(स्थिर अक्षर *cgroup);
बाह्य sमाप_प्रकार proc_पढ़ो_text(पूर्णांक pid, bool thपढ़ो, स्थिर अक्षर *item, अक्षर *buf, माप_प्रकार size);
बाह्य पूर्णांक proc_पढ़ो_म_माला(पूर्णांक pid, bool thपढ़ो, स्थिर अक्षर *item, स्थिर अक्षर *needle);
बाह्य pid_t clone_पूर्णांकo_cgroup(पूर्णांक cgroup_fd);
बाह्य पूर्णांक clone_reap(pid_t pid, पूर्णांक options);
बाह्य पूर्णांक clone_पूर्णांकo_cgroup_run_रुको(स्थिर अक्षर *cgroup);
बाह्य पूर्णांक dirfd_खोलो_opath(स्थिर अक्षर *dir);
