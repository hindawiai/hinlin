<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SYSCALLTBL_H
#घोषणा __PERF_SYSCALLTBL_H

काष्ठा syscalltbl अणु
	पूर्णांक audit_machine;
	काष्ठा अणु
		पूर्णांक max_id;
		पूर्णांक nr_entries;
		व्योम *entries;
	पूर्ण syscalls;
पूर्ण;

काष्ठा syscalltbl *syscalltbl__new(व्योम);
व्योम syscalltbl__delete(काष्ठा syscalltbl *tbl);

स्थिर अक्षर *syscalltbl__name(स्थिर काष्ठा syscalltbl *tbl, पूर्णांक id);
पूर्णांक syscalltbl__id(काष्ठा syscalltbl *tbl, स्थिर अक्षर *name);

पूर्णांक syscalltbl__strglobmatch_first(काष्ठा syscalltbl *tbl, स्थिर अक्षर *syscall_glob, पूर्णांक *idx);
पूर्णांक syscalltbl__strglobmatch_next(काष्ठा syscalltbl *tbl, स्थिर अक्षर *syscall_glob, पूर्णांक *idx);

#पूर्ण_अगर /* __PERF_SYSCALLTBL_H */
