<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित _GNU_SOURCE
# define _GNU_SOURCE
#पूर्ण_अगर

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/माला.स>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश "fs.h"

#समावेश "tracing_path.h"

अटल अक्षर tracing_mnt[PATH_MAX]  = "/sys/kernel/debug";
अटल अक्षर tracing_path[PATH_MAX]        = "/sys/kernel/debug/tracing";
अटल अक्षर tracing_events_path[PATH_MAX] = "/sys/kernel/debug/tracing/events";

अटल व्योम __tracing_path_set(स्थिर अक्षर *tracing, स्थिर अक्षर *mountpoपूर्णांक)
अणु
	snम_लिखो(tracing_mnt, माप(tracing_mnt), "%s", mountpoपूर्णांक);
	snम_लिखो(tracing_path, माप(tracing_path), "%s/%s",
		 mountpoपूर्णांक, tracing);
	snम_लिखो(tracing_events_path, माप(tracing_events_path), "%s/%s%s",
		 mountpoपूर्णांक, tracing, "events");
पूर्ण

अटल स्थिर अक्षर *tracing_path_tracefs_mount(व्योम)
अणु
	स्थिर अक्षर *mnt;

	mnt = tracefs__mount();
	अगर (!mnt)
		वापस शून्य;

	__tracing_path_set("", mnt);

	वापस tracing_path;
पूर्ण

अटल स्थिर अक्षर *tracing_path_debugfs_mount(व्योम)
अणु
	स्थिर अक्षर *mnt;

	mnt = debugfs__mount();
	अगर (!mnt)
		वापस शून्य;

	__tracing_path_set("tracing/", mnt);

	वापस tracing_path;
पूर्ण

स्थिर अक्षर *tracing_path_mount(व्योम)
अणु
	स्थिर अक्षर *mnt;

	mnt = tracing_path_tracefs_mount();
	अगर (mnt)
		वापस mnt;

	mnt = tracing_path_debugfs_mount();

	वापस mnt;
पूर्ण

व्योम tracing_path_set(स्थिर अक्षर *mntpt)
अणु
	__tracing_path_set("tracing/", mntpt);
पूर्ण

अक्षर *get_tracing_file(स्थिर अक्षर *name)
अणु
	अक्षर *file;

	अगर (aप्र_लिखो(&file, "%s/%s", tracing_path_mount(), name) < 0)
		वापस शून्य;

	वापस file;
पूर्ण

व्योम put_tracing_file(अक्षर *file)
अणु
	मुक्त(file);
पूर्ण

अक्षर *get_events_file(स्थिर अक्षर *name)
अणु
	अक्षर *file;

	अगर (aप्र_लिखो(&file, "%s/events/%s", tracing_path_mount(), name) < 0)
		वापस शून्य;

	वापस file;
पूर्ण

व्योम put_events_file(अक्षर *file)
अणु
	मुक्त(file);
पूर्ण

सूची *tracing_events__सूची_खोलो(व्योम)
अणु
	सूची *dir = शून्य;
	अक्षर *path = get_tracing_file("events");

	अगर (path) अणु
		dir = सूची_खोलो(path);
		put_events_file(path);
	पूर्ण

	वापस dir;
पूर्ण

पूर्णांक tracing_path__म_त्रुटि_खोलो_tp(पूर्णांक err, अक्षर *buf, माप_प्रकार size,
				   स्थिर अक्षर *sys, स्थिर अक्षर *name)
अणु
	अक्षर sbuf[128];
	अक्षर filename[PATH_MAX];

	snम_लिखो(filename, PATH_MAX, "%s/%s", sys, name ?: "*");

	चयन (err) अणु
	हाल ENOENT:
		/*
		 * We will get here अगर we can't find the tracepoपूर्णांक, but one of
		 * debugfs or tracefs is configured, which means you probably
		 * want some tracepoपूर्णांक which wasn't compiled in your kernel.
		 * - jirka
		 */
		अगर (debugfs__configured() || tracefs__configured()) अणु
			/* sdt markers */
			अगर (!म_भेदन(filename, "sdt_", 4)) अणु
				snम_लिखो(buf, size,
					"Error:\tFile %s/%s not found.\n"
					"Hint:\tSDT event cannot be directly recorded on.\n"
					"\tPlease first use 'perf probe %s:%s' before recording it.\n",
					tracing_events_path, filename, sys, name);
			पूर्ण अन्यथा अणु
				snम_लिखो(buf, size,
					 "Error:\tFile %s/%s not found.\n"
					 "Hint:\tPerhaps this kernel misses some CONFIG_ setting to enable this feature?.\n",
					 tracing_events_path, filename);
			पूर्ण
			अवरोध;
		पूर्ण
		snम_लिखो(buf, size, "%s",
			 "Error:\tUnable to find debugfs/tracefs\n"
			 "Hint:\tWas your kernel compiled with debugfs/tracefs support?\n"
			 "Hint:\tIs the debugfs/tracefs filesystem mounted?\n"
			 "Hint:\tTry 'sudo mount -t debugfs nodev /sys/kernel/debug'");
		अवरोध;
	हाल EACCES: अणु
		snम_लिखो(buf, size,
			 "Error:\tNo permissions to read %s/%s\n"
			 "Hint:\tTry 'sudo mount -o remount,mode=755 %s'\n",
			 tracing_events_path, filename, tracing_path_mount());
	पूर्ण
		अवरोध;
	शेष:
		snम_लिखो(buf, size, "%s", str_error_r(err, sbuf, माप(sbuf)));
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
