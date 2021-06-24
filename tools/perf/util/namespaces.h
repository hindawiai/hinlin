<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2017 Hari Bathini, IBM Corporation
 */

#अगर_अघोषित __PERF_NAMESPACES_H
#घोषणा __PERF_NAMESPACES_H

#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/perf_event.h>
#समावेश <linux/refcount.h>
#समावेश <linux/types.h>

#अगर_अघोषित HAVE_SETNS_SUPPORT
पूर्णांक setns(पूर्णांक fd, पूर्णांक nstype);
#पूर्ण_अगर

काष्ठा perf_record_namespaces;

काष्ठा namespaces अणु
	काष्ठा list_head list;
	u64 end_समय;
	काष्ठा perf_ns_link_info link_info[];
पूर्ण;

काष्ठा namespaces *namespaces__new(काष्ठा perf_record_namespaces *event);
व्योम namespaces__मुक्त(काष्ठा namespaces *namespaces);

काष्ठा nsinfo अणु
	pid_t			pid;
	pid_t			tgid;
	pid_t			nstgid;
	bool			need_setns;
	bool			in_pidns;
	अक्षर			*mntns_path;
	refcount_t		refcnt;
पूर्ण;

काष्ठा nscookie अणु
	पूर्णांक			oldns;
	पूर्णांक			newns;
	अक्षर			*oldcwd;
पूर्ण;

पूर्णांक nsinfo__init(काष्ठा nsinfo *nsi);
काष्ठा nsinfo *nsinfo__new(pid_t pid);
काष्ठा nsinfo *nsinfo__copy(काष्ठा nsinfo *nsi);
व्योम nsinfo__delete(काष्ठा nsinfo *nsi);

काष्ठा nsinfo *nsinfo__get(काष्ठा nsinfo *nsi);
व्योम nsinfo__put(काष्ठा nsinfo *nsi);

व्योम nsinfo__mountns_enter(काष्ठा nsinfo *nsi, काष्ठा nscookie *nc);
व्योम nsinfo__mountns_निकास(काष्ठा nscookie *nc);

अक्षर *nsinfo__realpath(स्थिर अक्षर *path, काष्ठा nsinfo *nsi);
पूर्णांक nsinfo__stat(स्थिर अक्षर *filename, काष्ठा stat *st, काष्ठा nsinfo *nsi);

अटल अंतरभूत व्योम __nsinfo__zput(काष्ठा nsinfo **nsip)
अणु
	अगर (nsip) अणु
		nsinfo__put(*nsip);
		*nsip = शून्य;
	पूर्ण
पूर्ण

#घोषणा nsinfo__zput(nsi) __nsinfo__zput(&nsi)

स्थिर अक्षर *perf_ns__name(अचिन्हित पूर्णांक id);

#पूर्ण_अगर  /* __PERF_NAMESPACES_H */
