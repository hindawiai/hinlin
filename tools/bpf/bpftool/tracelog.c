<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (c) 2015-2017 Daniel Borkmann */
/* Copyright (c) 2018 Netronome Systems, Inc. */

#समावेश <त्रुटिसं.स>
#समावेश <सीमा.स>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/magic.h>
#समावेश <sys/fcntl.h>
#समावेश <sys/vfs.h>

#समावेश "main.h"

#अगर_अघोषित TRACEFS_MAGIC
# define TRACEFS_MAGIC	0x74726163
#पूर्ण_अगर

#घोषणा _textअगरy(x)	#x
#घोषणा textअगरy(x)	_textअगरy(x)

खाता *trace_pipe_fd;
अक्षर *buff;

अटल पूर्णांक validate_tracefs_mnt(स्थिर अक्षर *mnt, अचिन्हित दीर्घ magic)
अणु
	काष्ठा statfs st_fs;

	अगर (statfs(mnt, &st_fs) < 0)
		वापस -ENOENT;
	अगर ((अचिन्हित दीर्घ)st_fs.f_type != magic)
		वापस -ENOENT;

	वापस 0;
पूर्ण

अटल bool
find_tracefs_mnt_single(अचिन्हित दीर्घ magic, अक्षर *mnt, स्थिर अक्षर *mntpt)
अणु
	माप_प्रकार src_len;

	अगर (validate_tracefs_mnt(mntpt, magic))
		वापस false;

	src_len = म_माप(mntpt);
	अगर (src_len + 1 >= PATH_MAX) अणु
		p_err("tracefs mount point name too long");
		वापस false;
	पूर्ण

	म_नकल(mnt, mntpt);
	वापस true;
पूर्ण

अटल bool get_tracefs_pipe(अक्षर *mnt)
अणु
	अटल स्थिर अक्षर * स्थिर known_mnts[] = अणु
		"/sys/kernel/debug/tracing",
		"/sys/kernel/tracing",
		"/tracing",
		"/trace",
	पूर्ण;
	स्थिर अक्षर *pipe_name = "/trace_pipe";
	स्थिर अक्षर *fstype = "tracefs";
	अक्षर type[100], क्रमmat[32];
	स्थिर अक्षर * स्थिर *ptr;
	bool found = false;
	खाता *fp;

	क्रम (ptr = known_mnts; ptr < known_mnts + ARRAY_SIZE(known_mnts); ptr++)
		अगर (find_tracefs_mnt_single(TRACEFS_MAGIC, mnt, *ptr))
			जाओ निकास_found;

	fp = ख_खोलो("/proc/mounts", "r");
	अगर (!fp)
		वापस false;

	/* Allow room क्रम शून्य terminating byte and pipe file name */
	snम_लिखो(क्रमmat, माप(क्रमmat), "%%*s %%%zds %%99s %%*s %%*d %%*d\\n",
		 PATH_MAX - म_माप(pipe_name) - 1);
	जबतक (ख_पूछो(fp, क्रमmat, mnt, type) == 2)
		अगर (म_भेद(type, fstype) == 0) अणु
			found = true;
			अवरोध;
		पूर्ण
	ख_बंद(fp);

	/* The string from ख_पूछो() might be truncated, check mnt is valid */
	अगर (found && validate_tracefs_mnt(mnt, TRACEFS_MAGIC))
		जाओ निकास_found;

	अगर (block_mount)
		वापस false;

	p_info("could not find tracefs, attempting to mount it now");
	/* Most of the समय, tracefs is स्वतःmatically mounted by debugfs at
	 * /sys/kernel/debug/tracing when we try to access it. If we could not
	 * find it, it is likely that debugfs is not mounted. Let's give one
	 * attempt at mounting just tracefs at /sys/kernel/tracing.
	 */
	म_नकल(mnt, known_mnts[1]);
	अगर (mount_tracefs(mnt))
		वापस false;

निकास_found:
	म_जोड़ो(mnt, pipe_name);
	वापस true;
पूर्ण

अटल व्योम निकास_tracelog(पूर्णांक signum)
अणु
	ख_बंद(trace_pipe_fd);
	मुक्त(buff);

	अगर (json_output) अणु
		jsonw_end_array(json_wtr);
		jsonw_destroy(&json_wtr);
	पूर्ण

	निकास(0);
पूर्ण

पूर्णांक करो_tracelog(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर काष्ठा sigaction act = अणु
		.sa_handler = निकास_tracelog
	पूर्ण;
	अक्षर trace_pipe[PATH_MAX];
	माप_प्रकार buff_len = 0;

	अगर (json_output)
		jsonw_start_array(json_wtr);

	अगर (!get_tracefs_pipe(trace_pipe))
		वापस -1;

	trace_pipe_fd = ख_खोलो(trace_pipe, "r");
	अगर (!trace_pipe_fd) अणु
		p_err("could not open trace pipe: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	sigaction(SIGHUP, &act, शून्य);
	sigaction(संक_विघ्न, &act, शून्य);
	sigaction(संक_इति, &act, शून्य);
	जबतक (1) अणु
		sमाप_प्रकार ret;

		ret = getline(&buff, &buff_len, trace_pipe_fd);
		अगर (ret <= 0) अणु
			p_err("failed to read content from trace pipe: %s",
			      म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण
		अगर (json_output)
			jsonw_string(json_wtr, buff);
		अन्यथा
			म_लिखो("%s", buff);
	पूर्ण

	ख_बंद(trace_pipe_fd);
	मुक्त(buff);
	वापस -1;
पूर्ण
