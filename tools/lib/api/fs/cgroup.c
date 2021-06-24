<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/stringअगरy.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश "fs.h"

काष्ठा cgroupfs_cache_entry अणु
	अक्षर	subsys[32];
	अक्षर	mountpoपूर्णांक[PATH_MAX];
पूर्ण;

/* just cache last used one */
अटल काष्ठा cgroupfs_cache_entry cached;

पूर्णांक cgroupfs_find_mountpoपूर्णांक(अक्षर *buf, माप_प्रकार maxlen, स्थिर अक्षर *subsys)
अणु
	खाता *fp;
	अक्षर *line = शून्य;
	माप_प्रकार len = 0;
	अक्षर *p, *path;
	अक्षर mountpoपूर्णांक[PATH_MAX];

	अगर (!म_भेद(cached.subsys, subsys)) अणु
		अगर (म_माप(cached.mountpoपूर्णांक) < maxlen) अणु
			म_नकल(buf, cached.mountpoपूर्णांक);
			वापस 0;
		पूर्ण
		वापस -1;
	पूर्ण

	fp = ख_खोलो("/proc/mounts", "r");
	अगर (!fp)
		वापस -1;

	/*
	 * in order to handle split hierarchy, we need to scan /proc/mounts
	 * and inspect every cgroupfs mount poपूर्णांक to find one that has
	 * the given subप्रणाली.  If we found v1, just use it.  If not we can
	 * use v2 path as a fallback.
	 */
	mountpoपूर्णांक[0] = '\0';

	/*
	 * The /proc/mounts has the follow क्रमmat:
	 *
	 *   <devname> <mount poपूर्णांक> <fs type> <options> ...
	 *
	 */
	जबतक (getline(&line, &len, fp) != -1) अणु
		/* skip devname */
		p = म_अक्षर(line, ' ');
		अगर (p == शून्य)
			जारी;

		/* save the mount poपूर्णांक */
		path = ++p;
		p = म_अक्षर(p, ' ');
		अगर (p == शून्य)
			जारी;

		*p++ = '\0';

		/* check fileप्रणाली type */
		अगर (म_भेदन(p, "cgroup", 6))
			जारी;

		अगर (p[6] == '2') अणु
			/* save cgroup v2 path */
			म_नकल(mountpoपूर्णांक, path);
			जारी;
		पूर्ण

		/* now we have cgroup v1, check the options क्रम subप्रणाली */
		p += 7;

		p = म_माला(p, subsys);
		अगर (p == शून्य)
			जारी;

		/* sanity check: it should be separated by a space or a comma */
		अगर (!म_अक्षर(" ,", p[-1]) || !म_अक्षर(" ,", p[म_माप(subsys)]))
			जारी;

		म_नकल(mountpoपूर्णांक, path);
		अवरोध;
	पूर्ण
	मुक्त(line);
	ख_बंद(fp);

	म_नकलन(cached.subsys, subsys, माप(cached.subsys) - 1);
	म_नकल(cached.mountpoपूर्णांक, mountpoपूर्णांक);

	अगर (mountpoपूर्णांक[0] && म_माप(mountpoपूर्णांक) < maxlen) अणु
		म_नकल(buf, mountpoपूर्णांक);
		वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
