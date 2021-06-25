<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_OPENAT2_H
#घोषणा _UAPI_LINUX_OPENAT2_H

#समावेश <linux/types.h>

/*
 * Arguments क्रम how खोलोat2(2) should खोलो the target path. If only @flags and
 * @mode are non-zero, then खोलोat2(2) operates very similarly to खोलोat(2).
 *
 * However, unlike खोलोat(2), unknown or invalid bits in @flags result in
 * -EINVAL rather than being silently ignored. @mode must be zero unless one of
 * अणुO_CREAT, O_TMPखातापूर्ण are set.
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
#घोषणा RESOLVE_CACHED		0x20 /* Only complete अगर resolution can be
					completed through cached lookup. May
					वापस -EAGAIN अगर that's not
					possible. */

#पूर्ण_अगर /* _UAPI_LINUX_OPENAT2_H */
