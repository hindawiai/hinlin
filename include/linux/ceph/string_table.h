<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FS_CEPH_STRING_TABLE_H
#घोषणा _FS_CEPH_STRING_TABLE_H

#समावेश <linux/types.h>
#समावेश <linux/kref.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/rcupdate.h>

काष्ठा ceph_string अणु
	काष्ठा kref kref;
	जोड़ अणु
		काष्ठा rb_node node;
		काष्ठा rcu_head rcu;
	पूर्ण;
	माप_प्रकार len;
	अक्षर str[];
पूर्ण;

बाह्य व्योम ceph_release_string(काष्ठा kref *ref);
बाह्य काष्ठा ceph_string *ceph_find_or_create_string(स्थिर अक्षर *str,
						      माप_प्रकार len);
बाह्य bool ceph_strings_empty(व्योम);

अटल अंतरभूत काष्ठा ceph_string *ceph_get_string(काष्ठा ceph_string *str)
अणु
	kref_get(&str->kref);
	वापस str;
पूर्ण

अटल अंतरभूत व्योम ceph_put_string(काष्ठा ceph_string *str)
अणु
	अगर (!str)
		वापस;
	kref_put(&str->kref, ceph_release_string);
पूर्ण

अटल अंतरभूत पूर्णांक ceph_compare_string(काष्ठा ceph_string *cs,
				      स्थिर अक्षर* str, माप_प्रकार len)
अणु
	माप_प्रकार cs_len = cs ? cs->len : 0;
	अगर (cs_len != len)
		वापस cs_len - len;
	अगर (len == 0)
		वापस 0;
	वापस म_भेदन(cs->str, str, len);
पूर्ण

#घोषणा ceph_try_get_string(x)					\
(अणु								\
	काष्ठा ceph_string *___str;				\
	rcu_पढ़ो_lock();					\
	क्रम (;;) अणु						\
		___str = rcu_dereference(x);			\
		अगर (!___str ||					\
		    kref_get_unless_zero(&___str->kref))	\
			अवरोध;					\
	पूर्ण							\
	rcu_पढ़ो_unlock();					\
	(___str);						\
पूर्ण)

#पूर्ण_अगर
