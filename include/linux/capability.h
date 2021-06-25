<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This is <linux/capability.h>
 *
 * Andrew G. Morgan <morgan@kernel.org>
 * Alexander Kjeldaas <astor@guardian.no>
 * with help from Aleph1, Roland Buresund and Andrew Main.
 *
 * See here क्रम the libcap library ("POSIX draft" compliance):
 *
 * ftp://www.kernel.org/pub/linux/libs/security/linux-privs/kernel-2.6/
 */
#अगर_अघोषित _LINUX_CAPABILITY_H
#घोषणा _LINUX_CAPABILITY_H

#समावेश <uapi/linux/capability.h>
#समावेश <linux/uidgid.h>

#घोषणा _KERNEL_CAPABILITY_VERSION _LINUX_CAPABILITY_VERSION_3
#घोषणा _KERNEL_CAPABILITY_U32S    _LINUX_CAPABILITY_U32S_3

बाह्य पूर्णांक file_caps_enabled;

प्रकार काष्ठा kernel_cap_काष्ठा अणु
	__u32 cap[_KERNEL_CAPABILITY_U32S];
पूर्ण kernel_cap_t;

/* same as vfs_ns_cap_data but in cpu endian and always filled completely */
काष्ठा cpu_vfs_cap_data अणु
	__u32 magic_etc;
	kernel_cap_t permitted;
	kernel_cap_t inheritable;
	kuid_t rootid;
पूर्ण;

#घोषणा _USER_CAP_HEADER_SIZE  (माप(काष्ठा __user_cap_header_काष्ठा))
#घोषणा _KERNEL_CAP_T_SIZE     (माप(kernel_cap_t))


काष्ठा file;
काष्ठा inode;
काष्ठा dentry;
काष्ठा task_काष्ठा;
काष्ठा user_namespace;

बाह्य स्थिर kernel_cap_t __cap_empty_set;
बाह्य स्थिर kernel_cap_t __cap_init_eff_set;

/*
 * Internal kernel functions only
 */

#घोषणा CAP_FOR_EACH_U32(__capi)  \
	क्रम (__capi = 0; __capi < _KERNEL_CAPABILITY_U32S; ++__capi)

/*
 * CAP_FS_MASK and CAP_NFSD_MASKS:
 *
 * The fs mask is all the privileges that fsuid==0 historically meant.
 * At one समय in the past, that included CAP_MKNOD and CAP_LINUX_IMMUTABLE.
 *
 * It has never meant setting security.* and trusted.* xattrs.
 *
 * We could also define fsmask as follows:
 *   1. CAP_FS_MASK is the privilege to bypass all fs-related DAC permissions
 *   2. The security.* and trusted.* xattrs are fs-related MAC permissions
 */

# define CAP_FS_MASK_B0     (CAP_TO_MASK(CAP_CHOWN)		\
			    | CAP_TO_MASK(CAP_MKNOD)		\
			    | CAP_TO_MASK(CAP_DAC_OVERRIDE)	\
			    | CAP_TO_MASK(CAP_DAC_READ_SEARCH)	\
			    | CAP_TO_MASK(CAP_FOWNER)		\
			    | CAP_TO_MASK(CAP_FSETID))

# define CAP_FS_MASK_B1     (CAP_TO_MASK(CAP_MAC_OVERRIDE))

#अगर _KERNEL_CAPABILITY_U32S != 2
# error Fix up hand-coded capability macro initializers
#अन्यथा /* HAND-CODED capability initializers */

#घोषणा CAP_LAST_U32			((_KERNEL_CAPABILITY_U32S) - 1)
#घोषणा CAP_LAST_U32_VALID_MASK		(CAP_TO_MASK(CAP_LAST_CAP + 1) -1)

# define CAP_EMPTY_SET    ((kernel_cap_t)अणुअणु 0, 0 पूर्णपूर्ण)
# define CAP_FULL_SET     ((kernel_cap_t)अणुअणु ~0, CAP_LAST_U32_VALID_MASK पूर्णपूर्ण)
# define CAP_FS_SET       ((kernel_cap_t)अणुअणु CAP_FS_MASK_B0 \
				    | CAP_TO_MASK(CAP_LINUX_IMMUTABLE), \
				    CAP_FS_MASK_B1 पूर्ण पूर्ण)
# define CAP_NFSD_SET     ((kernel_cap_t)अणुअणु CAP_FS_MASK_B0 \
				    | CAP_TO_MASK(CAP_SYS_RESOURCE), \
				    CAP_FS_MASK_B1 पूर्ण पूर्ण)

#पूर्ण_अगर /* _KERNEL_CAPABILITY_U32S != 2 */

# define cap_clear(c)         करो अणु (c) = __cap_empty_set; पूर्ण जबतक (0)

#घोषणा cap_उठाओ(c, flag)  ((c).cap[CAP_TO_INDEX(flag)] |= CAP_TO_MASK(flag))
#घोषणा cap_lower(c, flag)  ((c).cap[CAP_TO_INDEX(flag)] &= ~CAP_TO_MASK(flag))
#घोषणा cap_उठाओd(c, flag) ((c).cap[CAP_TO_INDEX(flag)] & CAP_TO_MASK(flag))

#घोषणा CAP_BOP_ALL(c, a, b, OP)                                    \
करो अणु                                                                \
	अचिन्हित __capi;                                            \
	CAP_FOR_EACH_U32(__capi) अणु                                  \
		c.cap[__capi] = a.cap[__capi] OP b.cap[__capi];     \
	पूर्ण                                                           \
पूर्ण जबतक (0)

#घोषणा CAP_UOP_ALL(c, a, OP)                                       \
करो अणु                                                                \
	अचिन्हित __capi;                                            \
	CAP_FOR_EACH_U32(__capi) अणु                                  \
		c.cap[__capi] = OP a.cap[__capi];                   \
	पूर्ण                                                           \
पूर्ण जबतक (0)

अटल अंतरभूत kernel_cap_t cap_combine(स्थिर kernel_cap_t a,
				       स्थिर kernel_cap_t b)
अणु
	kernel_cap_t dest;
	CAP_BOP_ALL(dest, a, b, |);
	वापस dest;
पूर्ण

अटल अंतरभूत kernel_cap_t cap_पूर्णांकersect(स्थिर kernel_cap_t a,
					 स्थिर kernel_cap_t b)
अणु
	kernel_cap_t dest;
	CAP_BOP_ALL(dest, a, b, &);
	वापस dest;
पूर्ण

अटल अंतरभूत kernel_cap_t cap_drop(स्थिर kernel_cap_t a,
				    स्थिर kernel_cap_t drop)
अणु
	kernel_cap_t dest;
	CAP_BOP_ALL(dest, a, drop, &~);
	वापस dest;
पूर्ण

अटल अंतरभूत kernel_cap_t cap_invert(स्थिर kernel_cap_t c)
अणु
	kernel_cap_t dest;
	CAP_UOP_ALL(dest, c, ~);
	वापस dest;
पूर्ण

अटल अंतरभूत bool cap_isclear(स्थिर kernel_cap_t a)
अणु
	अचिन्हित __capi;
	CAP_FOR_EACH_U32(__capi) अणु
		अगर (a.cap[__capi] != 0)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Check अगर "a" is a subset of "set".
 * वापस true अगर ALL of the capabilities in "a" are also in "set"
 *	cap_issubset(0101, 1111) will वापस true
 * वापस false अगर ANY of the capabilities in "a" are not in "set"
 *	cap_issubset(1111, 0101) will वापस false
 */
अटल अंतरभूत bool cap_issubset(स्थिर kernel_cap_t a, स्थिर kernel_cap_t set)
अणु
	kernel_cap_t dest;
	dest = cap_drop(a, set);
	वापस cap_isclear(dest);
पूर्ण

/* Used to decide between falling back on the old suser() or fsuser(). */

अटल अंतरभूत kernel_cap_t cap_drop_fs_set(स्थिर kernel_cap_t a)
अणु
	स्थिर kernel_cap_t __cap_fs_set = CAP_FS_SET;
	वापस cap_drop(a, __cap_fs_set);
पूर्ण

अटल अंतरभूत kernel_cap_t cap_उठाओ_fs_set(स्थिर kernel_cap_t a,
					    स्थिर kernel_cap_t permitted)
अणु
	स्थिर kernel_cap_t __cap_fs_set = CAP_FS_SET;
	वापस cap_combine(a,
			   cap_पूर्णांकersect(permitted, __cap_fs_set));
पूर्ण

अटल अंतरभूत kernel_cap_t cap_drop_nfsd_set(स्थिर kernel_cap_t a)
अणु
	स्थिर kernel_cap_t __cap_fs_set = CAP_NFSD_SET;
	वापस cap_drop(a, __cap_fs_set);
पूर्ण

अटल अंतरभूत kernel_cap_t cap_उठाओ_nfsd_set(स्थिर kernel_cap_t a,
					      स्थिर kernel_cap_t permitted)
अणु
	स्थिर kernel_cap_t __cap_nfsd_set = CAP_NFSD_SET;
	वापस cap_combine(a,
			   cap_पूर्णांकersect(permitted, __cap_nfsd_set));
पूर्ण

#अगर_घोषित CONFIG_MULTIUSER
बाह्य bool has_capability(काष्ठा task_काष्ठा *t, पूर्णांक cap);
बाह्य bool has_ns_capability(काष्ठा task_काष्ठा *t,
			      काष्ठा user_namespace *ns, पूर्णांक cap);
बाह्य bool has_capability_noaudit(काष्ठा task_काष्ठा *t, पूर्णांक cap);
बाह्य bool has_ns_capability_noaudit(काष्ठा task_काष्ठा *t,
				      काष्ठा user_namespace *ns, पूर्णांक cap);
बाह्य bool capable(पूर्णांक cap);
बाह्य bool ns_capable(काष्ठा user_namespace *ns, पूर्णांक cap);
बाह्य bool ns_capable_noaudit(काष्ठा user_namespace *ns, पूर्णांक cap);
बाह्य bool ns_capable_setid(काष्ठा user_namespace *ns, पूर्णांक cap);
#अन्यथा
अटल अंतरभूत bool has_capability(काष्ठा task_काष्ठा *t, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool has_ns_capability(काष्ठा task_काष्ठा *t,
			      काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool has_capability_noaudit(काष्ठा task_काष्ठा *t, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool has_ns_capability_noaudit(काष्ठा task_काष्ठा *t,
				      काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool capable(पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool ns_capable(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool ns_capable_noaudit(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत bool ns_capable_setid(काष्ठा user_namespace *ns, पूर्णांक cap)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_MULTIUSER */
bool privileged_wrt_inode_uidgid(काष्ठा user_namespace *ns,
				 काष्ठा user_namespace *mnt_userns,
				 स्थिर काष्ठा inode *inode);
bool capable_wrt_inode_uidgid(काष्ठा user_namespace *mnt_userns,
			      स्थिर काष्ठा inode *inode, पूर्णांक cap);
बाह्य bool file_ns_capable(स्थिर काष्ठा file *file, काष्ठा user_namespace *ns, पूर्णांक cap);
बाह्य bool ptracer_capable(काष्ठा task_काष्ठा *tsk, काष्ठा user_namespace *ns);
अटल अंतरभूत bool perfmon_capable(व्योम)
अणु
	वापस capable(CAP_PERFMON) || capable(CAP_SYS_ADMIN);
पूर्ण

अटल अंतरभूत bool bpf_capable(व्योम)
अणु
	वापस capable(CAP_BPF) || capable(CAP_SYS_ADMIN);
पूर्ण

अटल अंतरभूत bool checkpoपूर्णांक_restore_ns_capable(काष्ठा user_namespace *ns)
अणु
	वापस ns_capable(ns, CAP_CHECKPOINT_RESTORE) ||
		ns_capable(ns, CAP_SYS_ADMIN);
पूर्ण

/* audit प्रणाली wants to get cap info from files as well */
पूर्णांक get_vfs_caps_from_disk(काष्ठा user_namespace *mnt_userns,
			   स्थिर काष्ठा dentry *dentry,
			   काष्ठा cpu_vfs_cap_data *cpu_caps);

पूर्णांक cap_convert_nscap(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		      स्थिर व्योम **ivalue, माप_प्रकार size);

#पूर्ण_अगर /* !_LINUX_CAPABILITY_H */
