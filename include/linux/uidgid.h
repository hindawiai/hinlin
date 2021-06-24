<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UIDGID_H
#घोषणा _LINUX_UIDGID_H

/*
 * A set of types क्रम the पूर्णांकernal kernel types representing uids and gids.
 *
 * The types defined in this header allow distinguishing which uids and gids in
 * the kernel are values used by userspace and which uid and gid values are
 * the पूर्णांकernal kernel values.  With the addition of user namespaces the values
 * can be dअगरferent.  Using the type प्रणाली makes it possible क्रम the compiler
 * to detect when we overlook these dअगरferences.
 *
 */
#समावेश <linux/types.h>
#समावेश <linux/highuid.h>

काष्ठा user_namespace;
बाह्य काष्ठा user_namespace init_user_ns;

प्रकार काष्ठा अणु
	uid_t val;
पूर्ण kuid_t;


प्रकार काष्ठा अणु
	gid_t val;
पूर्ण kgid_t;

#घोषणा KUIDT_INIT(value) (kuid_t)अणु value पूर्ण
#घोषणा KGIDT_INIT(value) (kgid_t)अणु value पूर्ण

#अगर_घोषित CONFIG_MULTIUSER
अटल अंतरभूत uid_t __kuid_val(kuid_t uid)
अणु
	वापस uid.val;
पूर्ण

अटल अंतरभूत gid_t __kgid_val(kgid_t gid)
अणु
	वापस gid.val;
पूर्ण
#अन्यथा
अटल अंतरभूत uid_t __kuid_val(kuid_t uid)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत gid_t __kgid_val(kgid_t gid)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#घोषणा GLOBAL_ROOT_UID KUIDT_INIT(0)
#घोषणा GLOBAL_ROOT_GID KGIDT_INIT(0)

#घोषणा INVALID_UID KUIDT_INIT(-1)
#घोषणा INVALID_GID KGIDT_INIT(-1)

अटल अंतरभूत bool uid_eq(kuid_t left, kuid_t right)
अणु
	वापस __kuid_val(left) == __kuid_val(right);
पूर्ण

अटल अंतरभूत bool gid_eq(kgid_t left, kgid_t right)
अणु
	वापस __kgid_val(left) == __kgid_val(right);
पूर्ण

अटल अंतरभूत bool uid_gt(kuid_t left, kuid_t right)
अणु
	वापस __kuid_val(left) > __kuid_val(right);
पूर्ण

अटल अंतरभूत bool gid_gt(kgid_t left, kgid_t right)
अणु
	वापस __kgid_val(left) > __kgid_val(right);
पूर्ण

अटल अंतरभूत bool uid_gte(kuid_t left, kuid_t right)
अणु
	वापस __kuid_val(left) >= __kuid_val(right);
पूर्ण

अटल अंतरभूत bool gid_gte(kgid_t left, kgid_t right)
अणु
	वापस __kgid_val(left) >= __kgid_val(right);
पूर्ण

अटल अंतरभूत bool uid_lt(kuid_t left, kuid_t right)
अणु
	वापस __kuid_val(left) < __kuid_val(right);
पूर्ण

अटल अंतरभूत bool gid_lt(kgid_t left, kgid_t right)
अणु
	वापस __kgid_val(left) < __kgid_val(right);
पूर्ण

अटल अंतरभूत bool uid_lte(kuid_t left, kuid_t right)
अणु
	वापस __kuid_val(left) <= __kuid_val(right);
पूर्ण

अटल अंतरभूत bool gid_lte(kgid_t left, kgid_t right)
अणु
	वापस __kgid_val(left) <= __kgid_val(right);
पूर्ण

अटल अंतरभूत bool uid_valid(kuid_t uid)
अणु
	वापस __kuid_val(uid) != (uid_t) -1;
पूर्ण

अटल अंतरभूत bool gid_valid(kgid_t gid)
अणु
	वापस __kgid_val(gid) != (gid_t) -1;
पूर्ण

#अगर_घोषित CONFIG_USER_NS

बाह्य kuid_t make_kuid(काष्ठा user_namespace *from, uid_t uid);
बाह्य kgid_t make_kgid(काष्ठा user_namespace *from, gid_t gid);

बाह्य uid_t from_kuid(काष्ठा user_namespace *to, kuid_t uid);
बाह्य gid_t from_kgid(काष्ठा user_namespace *to, kgid_t gid);
बाह्य uid_t from_kuid_munged(काष्ठा user_namespace *to, kuid_t uid);
बाह्य gid_t from_kgid_munged(काष्ठा user_namespace *to, kgid_t gid);

अटल अंतरभूत bool kuid_has_mapping(काष्ठा user_namespace *ns, kuid_t uid)
अणु
	वापस from_kuid(ns, uid) != (uid_t) -1;
पूर्ण

अटल अंतरभूत bool kgid_has_mapping(काष्ठा user_namespace *ns, kgid_t gid)
अणु
	वापस from_kgid(ns, gid) != (gid_t) -1;
पूर्ण

#अन्यथा

अटल अंतरभूत kuid_t make_kuid(काष्ठा user_namespace *from, uid_t uid)
अणु
	वापस KUIDT_INIT(uid);
पूर्ण

अटल अंतरभूत kgid_t make_kgid(काष्ठा user_namespace *from, gid_t gid)
अणु
	वापस KGIDT_INIT(gid);
पूर्ण

अटल अंतरभूत uid_t from_kuid(काष्ठा user_namespace *to, kuid_t kuid)
अणु
	वापस __kuid_val(kuid);
पूर्ण

अटल अंतरभूत gid_t from_kgid(काष्ठा user_namespace *to, kgid_t kgid)
अणु
	वापस __kgid_val(kgid);
पूर्ण

अटल अंतरभूत uid_t from_kuid_munged(काष्ठा user_namespace *to, kuid_t kuid)
अणु
	uid_t uid = from_kuid(to, kuid);
	अगर (uid == (uid_t)-1)
		uid = overflowuid;
	वापस uid;
पूर्ण

अटल अंतरभूत gid_t from_kgid_munged(काष्ठा user_namespace *to, kgid_t kgid)
अणु
	gid_t gid = from_kgid(to, kgid);
	अगर (gid == (gid_t)-1)
		gid = overflowgid;
	वापस gid;
पूर्ण

अटल अंतरभूत bool kuid_has_mapping(काष्ठा user_namespace *ns, kuid_t uid)
अणु
	वापस uid_valid(uid);
पूर्ण

अटल अंतरभूत bool kgid_has_mapping(काष्ठा user_namespace *ns, kgid_t gid)
अणु
	वापस gid_valid(gid);
पूर्ण

#पूर्ण_अगर /* CONFIG_USER_NS */

#पूर्ण_अगर /* _LINUX_UIDGID_H */
