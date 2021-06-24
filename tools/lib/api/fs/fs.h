<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __API_FS__
#घोषणा __API_FS__

#समावेश <stdbool.h>
#समावेश <unistd.h>

/*
 * On most प्रणालीs <सीमा.स> would have given us this, but  not on some प्रणालीs
 * (e.g. GNU/Hurd).
 */
#अगर_अघोषित PATH_MAX
#घोषणा PATH_MAX 4096
#पूर्ण_अगर

#घोषणा FS(name)				\
	स्थिर अक्षर *name##__mountpoपूर्णांक(व्योम);	\
	स्थिर अक्षर *name##__mount(व्योम);	\
	bool name##__configured(व्योम);		\

/*
 * The xxxx__mountpoपूर्णांक() entry poपूर्णांकs find the first match mount poपूर्णांक क्रम each
 * fileप्रणालीs listed below, where xxxx is the fileप्रणाली type.
 *
 * The पूर्णांकerface is as follows:
 *
 * - If a mount poपूर्णांक is found on first call, it is cached and used क्रम all
 *   subsequent calls.
 *
 * - If a mount poपूर्णांक is not found, शून्य is वापसed on first call and all
 *   subsequent calls.
 */
FS(sysfs)
FS(procfs)
FS(debugfs)
FS(tracefs)
FS(hugetlbfs)
FS(bpf_fs)

#अघोषित FS


पूर्णांक cgroupfs_find_mountpoपूर्णांक(अक्षर *buf, माप_प्रकार maxlen, स्थिर अक्षर *subsys);

पूर्णांक filename__पढ़ो_पूर्णांक(स्थिर अक्षर *filename, पूर्णांक *value);
पूर्णांक filename__पढ़ो_ull(स्थिर अक्षर *filename, अचिन्हित दीर्घ दीर्घ *value);
पूर्णांक filename__पढ़ो_xll(स्थिर अक्षर *filename, अचिन्हित दीर्घ दीर्घ *value);
पूर्णांक filename__पढ़ो_str(स्थिर अक्षर *filename, अक्षर **buf, माप_प्रकार *sizep);

पूर्णांक filename__ग_लिखो_पूर्णांक(स्थिर अक्षर *filename, पूर्णांक value);

पूर्णांक procfs__पढ़ो_str(स्थिर अक्षर *entry, अक्षर **buf, माप_प्रकार *sizep);

पूर्णांक sysctl__पढ़ो_पूर्णांक(स्थिर अक्षर *sysctl, पूर्णांक *value);
पूर्णांक sysfs__पढ़ो_पूर्णांक(स्थिर अक्षर *entry, पूर्णांक *value);
पूर्णांक sysfs__पढ़ो_ull(स्थिर अक्षर *entry, अचिन्हित दीर्घ दीर्घ *value);
पूर्णांक sysfs__पढ़ो_xll(स्थिर अक्षर *entry, अचिन्हित दीर्घ दीर्घ *value);
पूर्णांक sysfs__पढ़ो_str(स्थिर अक्षर *entry, अक्षर **buf, माप_प्रकार *sizep);
पूर्णांक sysfs__पढ़ो_bool(स्थिर अक्षर *entry, bool *value);

पूर्णांक sysfs__ग_लिखो_पूर्णांक(स्थिर अक्षर *entry, पूर्णांक value);
#पूर्ण_अगर /* __API_FS__ */
