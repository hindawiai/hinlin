<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Author: Aleksa Sarai <cyphar@cyphar.com>
 * Copyright (C) 2018-2019 SUSE LLC.
 */

#अगर_अघोषित __RESOLVEAT_H__
#घोषणा __RESOLVEAT_H__

#घोषणा _GNU_SOURCE
#समावेश <मानक_निवेशt.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश "../kselftest.h"

#घोषणा ARRAY_LEN(X) (माप (X) / माप (*(X)))
#घोषणा BUILD_BUG_ON(e) ((व्योम)(माप(काष्ठा अणु पूर्णांक:(-!!(e)); पूर्ण)))

#अगर_अघोषित SYS_खोलोat2
#अगर_अघोषित __NR_खोलोat2
#घोषणा __NR_खोलोat2 437
#पूर्ण_अगर /* __NR_खोलोat2 */
#घोषणा SYS_खोलोat2 __NR_खोलोat2
#पूर्ण_अगर /* SYS_खोलोat2 */

/*
 * Arguments क्रम how खोलोat2(2) should खोलो the target path. If @resolve is
 * zero, then खोलोat2(2) operates very similarly to खोलोat(2).
 *
 * However, unlike खोलोat(2), unknown bits in @flags result in -EINVAL rather
 * than being silently ignored. @mode must be zero unless one of अणुO_CREAT,
 * O_TMPखातापूर्ण are set.
 *
 * @flags: O_* flags.
 * @mode: O_CREAT/O_TMPखाता file mode.
 * @resolve: RESOLVE_* flags.
 */
काष्ठा खोलो_how अणु
	__u64 flags;
	__u64 mode;
	__u64 resolve;
पूर्ण;

#घोषणा OPEN_HOW_SIZE_VER0	24 /* माप first published काष्ठा */
#घोषणा OPEN_HOW_SIZE_LATEST	OPEN_HOW_SIZE_VER0

bool needs_खोलोat2(स्थिर काष्ठा खोलो_how *how);

#अगर_अघोषित RESOLVE_IN_ROOT
/* how->resolve flags क्रम खोलोat2(2). */
#घोषणा RESOLVE_NO_XDEV		0x01 /* Block mount-poपूर्णांक crossings
					(includes bind-mounts). */
#घोषणा RESOLVE_NO_MAGICLINKS	0x02 /* Block traversal through procfs-style
					"magic-links". */
#घोषणा RESOLVE_NO_SYMLINKS	0x04 /* Block traversal through all symlinks
					(implies OEXT_NO_MAGICLINKS) */
#घोषणा RESOLVE_BENEATH		0x08 /* Block "lexical" trickery like
					"..", symlinks, and असलolute
					paths which escape the dirfd. */
#घोषणा RESOLVE_IN_ROOT		0x10 /* Make all jumps to "/" and ".."
					be scoped inside the dirfd
					(similar to chroot(2)). */
#पूर्ण_अगर /* RESOLVE_IN_ROOT */

#घोषणा E_func(func, ...)						\
	करो अणु								\
		अगर (func(__VA_ARGS__) < 0)				\
			ksft_निकास_fail_msg("%s:%d %s failed\n", \
					   __खाता__, __LINE__, #func);\
	पूर्ण जबतक (0)

#घोषणा E_aप्र_लिखो(...)		E_func(aप्र_लिखो,	__VA_ARGS__)
#घोषणा E_chmod(...)		E_func(chmod,		__VA_ARGS__)
#घोषणा E_dup2(...)		E_func(dup2,		__VA_ARGS__)
#घोषणा E_fस_बदलो(...)		E_func(fस_बदलो,		__VA_ARGS__)
#घोषणा E_ख_स्थितिat(...)		E_func(ख_स्थितिat,		__VA_ARGS__)
#घोषणा E_समाप्त(...)		E_func(समाप्त,		__VA_ARGS__)
#घोषणा E_सूची_गढ़ोat(...)		E_func(सूची_गढ़ोat,		__VA_ARGS__)
#घोषणा E_mount(...)		E_func(mount,		__VA_ARGS__)
#घोषणा E_prctl(...)		E_func(prctl,		__VA_ARGS__)
#घोषणा E_पढ़ोlink(...)		E_func(पढ़ोlink,	__VA_ARGS__)
#घोषणा E_setresuid(...)	E_func(setresuid,	__VA_ARGS__)
#घोषणा E_symlinkat(...)	E_func(symlinkat,	__VA_ARGS__)
#घोषणा E_touchat(...)		E_func(touchat,		__VA_ARGS__)
#घोषणा E_unshare(...)		E_func(unshare,		__VA_ARGS__)

#घोषणा E_निश्चित(expr, msg, ...)					\
	करो अणु								\
		अगर (!(expr))						\
			ksft_निकास_fail_msg("ASSERT(%s:%d) failed (%s): " msg "\n", \
					   __खाता__, __LINE__, #expr, ##__VA_ARGS__); \
	पूर्ण जबतक (0)

पूर्णांक raw_खोलोat2(पूर्णांक dfd, स्थिर अक्षर *path, व्योम *how, माप_प्रकार size);
पूर्णांक sys_खोलोat2(पूर्णांक dfd, स्थिर अक्षर *path, काष्ठा खोलो_how *how);
पूर्णांक sys_खोलोat(पूर्णांक dfd, स्थिर अक्षर *path, काष्ठा खोलो_how *how);
पूर्णांक sys_नामat2(पूर्णांक olddirfd, स्थिर अक्षर *oldpath,
		  पूर्णांक newdirfd, स्थिर अक्षर *newpath, अचिन्हित पूर्णांक flags);

पूर्णांक touchat(पूर्णांक dfd, स्थिर अक्षर *path);
अक्षर *fdपढ़ोlink(पूर्णांक fd);
bool fdequal(पूर्णांक fd, पूर्णांक dfd, स्थिर अक्षर *path);

बाह्य bool खोलोat2_supported;

#पूर्ण_अगर /* __RESOLVEAT_H__ */
