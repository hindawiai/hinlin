<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2012 Red Hat.  All rights reserved.
 */

#अगर_अघोषित BTRFS_RCU_STRING_H
#घोषणा BTRFS_RCU_STRING_H

काष्ठा rcu_string अणु
	काष्ठा rcu_head rcu;
	अक्षर str[];
पूर्ण;

अटल अंतरभूत काष्ठा rcu_string *rcu_string_strdup(स्थिर अक्षर *src, gfp_t mask)
अणु
	माप_प्रकार len = म_माप(src) + 1;
	काष्ठा rcu_string *ret = kzalloc(माप(काष्ठा rcu_string) +
					 (len * माप(अक्षर)), mask);
	अगर (!ret)
		वापस ret;
	म_नकलन(ret->str, src, len);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम rcu_string_मुक्त(काष्ठा rcu_string *str)
अणु
	अगर (str)
		kमुक्त_rcu(str, rcu);
पूर्ण

#घोषणा prपूर्णांकk_in_rcu(fmt, ...) करो अणु	\
	rcu_पढ़ो_lock();		\
	prपूर्णांकk(fmt, __VA_ARGS__);	\
	rcu_पढ़ो_unlock();		\
पूर्ण जबतक (0)

#घोषणा prपूर्णांकk_ratelimited_in_rcu(fmt, ...) करो अणु	\
	rcu_पढ़ो_lock();				\
	prपूर्णांकk_ratelimited(fmt, __VA_ARGS__);		\
	rcu_पढ़ो_unlock();				\
पूर्ण जबतक (0)

#घोषणा rcu_str_deref(rcu_str) (अणु				\
	काष्ठा rcu_string *__str = rcu_dereference(rcu_str);	\
	__str->str;						\
पूर्ण)

#पूर्ण_अगर
