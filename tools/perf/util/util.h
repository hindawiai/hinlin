<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित GIT_COMPAT_UTIL_H
#घोषणा GIT_COMPAT_UTIL_H

#घोषणा _BSD_SOURCE 1
/* glibc 2.20 deprecates _BSD_SOURCE in favour of _DEFAULT_SOURCE */
#घोषणा _DEFAULT_SOURCE 1

#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <linux/compiler.h>
#समावेश <sys/types.h>

/* General helper functions */
व्योम usage(स्थिर अक्षर *err) __noवापस;
व्योम die(स्थिर अक्षर *err, ...) __noवापस __म_लिखो(1, 2);

काष्ठा dirent;
काष्ठा strlist;

पूर्णांक सूची_गढ़ो_p(अक्षर *path, mode_t mode);
पूर्णांक rm_rf(स्थिर अक्षर *path);
पूर्णांक rm_rf_perf_data(स्थिर अक्षर *path);
काष्ठा strlist *lsdir(स्थिर अक्षर *name, bool (*filter)(स्थिर अक्षर *, काष्ठा dirent *));
bool lsdir_no_करोt_filter(स्थिर अक्षर *name, काष्ठा dirent *d);

माप_प्रकार hex_width(u64 v);

पूर्णांक sysctl__max_stack(व्योम);

bool sysctl__nmi_watchकरोg_enabled(व्योम);

पूर्णांक fetch_kernel_version(अचिन्हित पूर्णांक *puपूर्णांक,
			 अक्षर *str, माप_प्रकार str_sz);
#घोषणा KVER_VERSION(x)		(((x) >> 16) & 0xff)
#घोषणा KVER_PATCHLEVEL(x)	(((x) >> 8) & 0xff)
#घोषणा KVER_SUBLEVEL(x)	((x) & 0xff)
#घोषणा KVER_FMT	"%d.%d.%d"
#घोषणा KVER_PARAM(x)	KVER_VERSION(x), KVER_PATCHLEVEL(x), KVER_SUBLEVEL(x)

स्थिर अक्षर *perf_tip(स्थिर अक्षर *dirpath);

#अगर_अघोषित HAVE_SCHED_GETCPU_SUPPORT
पूर्णांक sched_अ_लोpu(व्योम);
#पूर्ण_अगर

बाह्य bool perf_singlethपढ़ोed;

व्योम perf_set_singlethपढ़ोed(व्योम);
व्योम perf_set_multithपढ़ोed(व्योम);

अक्षर *perf_exe(अक्षर *buf, पूर्णांक len);

#अगर_अघोषित O_CLOEXEC
#अगर_घोषित __sparc__
#घोषणा O_CLOEXEC      0x400000
#या_अगर defined(__alpha__) || defined(__hppa__)
#घोषणा O_CLOEXEC      010000000
#अन्यथा
#घोषणा O_CLOEXEC      02000000
#पूर्ण_अगर
#पूर्ण_अगर

बाह्य bool test_attr__enabled;
व्योम test_attr__पढ़ोy(व्योम);
व्योम test_attr__init(व्योम);
काष्ठा perf_event_attr;
व्योम test_attr__खोलो(काष्ठा perf_event_attr *attr, pid_t pid, पूर्णांक cpu,
		     पूर्णांक fd, पूर्णांक group_fd, अचिन्हित दीर्घ flags);
#पूर्ण_अगर /* GIT_COMPAT_UTIL_H */
