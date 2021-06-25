<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PROJID_H
#घोषणा _LINUX_PROJID_H

/*
 * A set of types क्रम the पूर्णांकernal kernel types representing project ids.
 *
 * The types defined in this header allow distinguishing which project ids in
 * the kernel are values used by userspace and which project id values are
 * the पूर्णांकernal kernel values.  With the addition of user namespaces the values
 * can be dअगरferent.  Using the type प्रणाली makes it possible क्रम the compiler
 * to detect when we overlook these dअगरferences.
 *
 */
#समावेश <linux/types.h>

काष्ठा user_namespace;
बाह्य काष्ठा user_namespace init_user_ns;

प्रकार __kernel_uid32_t projid_t;

प्रकार काष्ठा अणु
	projid_t val;
पूर्ण kprojid_t;

अटल अंतरभूत projid_t __kprojid_val(kprojid_t projid)
अणु
	वापस projid.val;
पूर्ण

#घोषणा KPROJIDT_INIT(value) (kprojid_t)अणु value पूर्ण

#घोषणा INVALID_PROJID KPROJIDT_INIT(-1)
#घोषणा OVERFLOW_PROJID 65534

अटल अंतरभूत bool projid_eq(kprojid_t left, kprojid_t right)
अणु
	वापस __kprojid_val(left) == __kprojid_val(right);
पूर्ण

अटल अंतरभूत bool projid_lt(kprojid_t left, kprojid_t right)
अणु
	वापस __kprojid_val(left) < __kprojid_val(right);
पूर्ण

अटल अंतरभूत bool projid_valid(kprojid_t projid)
अणु
	वापस !projid_eq(projid, INVALID_PROJID);
पूर्ण

#अगर_घोषित CONFIG_USER_NS

बाह्य kprojid_t make_kprojid(काष्ठा user_namespace *from, projid_t projid);

बाह्य projid_t from_kprojid(काष्ठा user_namespace *to, kprojid_t projid);
बाह्य projid_t from_kprojid_munged(काष्ठा user_namespace *to, kprojid_t projid);

अटल अंतरभूत bool kprojid_has_mapping(काष्ठा user_namespace *ns, kprojid_t projid)
अणु
	वापस from_kprojid(ns, projid) != (projid_t)-1;
पूर्ण

#अन्यथा

अटल अंतरभूत kprojid_t make_kprojid(काष्ठा user_namespace *from, projid_t projid)
अणु
	वापस KPROJIDT_INIT(projid);
पूर्ण

अटल अंतरभूत projid_t from_kprojid(काष्ठा user_namespace *to, kprojid_t kprojid)
अणु
	वापस __kprojid_val(kprojid);
पूर्ण

अटल अंतरभूत projid_t from_kprojid_munged(काष्ठा user_namespace *to, kprojid_t kprojid)
अणु
	projid_t projid = from_kprojid(to, kprojid);
	अगर (projid == (projid_t)-1)
		projid = OVERFLOW_PROJID;
	वापस projid;
पूर्ण

अटल अंतरभूत bool kprojid_has_mapping(काष्ठा user_namespace *ns, kprojid_t projid)
अणु
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_USER_NS */

#पूर्ण_अगर /* _LINUX_PROJID_H */
