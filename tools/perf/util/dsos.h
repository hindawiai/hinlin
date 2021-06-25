<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_DSOS
#घोषणा __PERF_DSOS

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश "rwsem.h"

काष्ठा dso;
काष्ठा dso_id;

/*
 * DSOs are put पूर्णांकo both a list क्रम fast iteration and rbtree क्रम fast
 * दीर्घ name lookup.
 */
काष्ठा dsos अणु
	काष्ठा list_head    head;
	काष्ठा rb_root	    root;	/* rbtree root sorted by दीर्घ name */
	काष्ठा rw_semaphore lock;
पूर्ण;

व्योम __dsos__add(काष्ठा dsos *dsos, काष्ठा dso *dso);
व्योम dsos__add(काष्ठा dsos *dsos, काष्ठा dso *dso);
काष्ठा dso *__dsos__addnew(काष्ठा dsos *dsos, स्थिर अक्षर *name);
काष्ठा dso *__dsos__find(काष्ठा dsos *dsos, स्थिर अक्षर *name, bool cmp_लघु);

काष्ठा dso *dsos__findnew_id(काष्ठा dsos *dsos, स्थिर अक्षर *name, काष्ठा dso_id *id);
 
काष्ठा dso *__dsos__findnew_link_by_दीर्घname_id(काष्ठा rb_root *root, काष्ठा dso *dso,
						स्थिर अक्षर *name, काष्ठा dso_id *id);

bool __dsos__पढ़ो_build_ids(काष्ठा list_head *head, bool with_hits);

माप_प्रकार __dsos__ख_लिखो_buildid(काष्ठा list_head *head, खाता *fp,
			       bool (skip)(काष्ठा dso *dso, पूर्णांक parm), पूर्णांक parm);
माप_प्रकार __dsos__ख_लिखो(काष्ठा list_head *head, खाता *fp);

#पूर्ण_अगर /* __PERF_DSOS */
