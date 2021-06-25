<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_COMM_H
#घोषणा __PERF_COMM_H

#समावेश <linux/list.h>
#समावेश <linux/types.h>
#समावेश <stdbool.h>

काष्ठा comm_str;

काष्ठा comm अणु
	काष्ठा comm_str *comm_str;
	u64 start;
	काष्ठा list_head list;
	bool exec;
	जोड़ अणु /* Tool specअगरic area */
		व्योम	*priv;
		u64	db_id;
	पूर्ण;
पूर्ण;

व्योम comm__मुक्त(काष्ठा comm *comm);
काष्ठा comm *comm__new(स्थिर अक्षर *str, u64 बारtamp, bool exec);
स्थिर अक्षर *comm__str(स्थिर काष्ठा comm *comm);
पूर्णांक comm__override(काष्ठा comm *comm, स्थिर अक्षर *str, u64 बारtamp,
		   bool exec);

#पूर्ण_अगर  /* __PERF_COMM_H */
