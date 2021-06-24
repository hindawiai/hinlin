<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2018 Facebook
// Author: Yonghong Song <yhs@fb.com>

#घोषणा _GNU_SOURCE
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>
#समावेश <ftw.h>

#समावेश <bpf/bpf.h>

#समावेश "main.h"

/* 0: undecided, 1: supported, 2: not supported */
अटल पूर्णांक perf_query_supported;
अटल bool has_perf_query_support(व्योम)
अणु
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	अक्षर buf[256];
	पूर्णांक fd;

	अगर (perf_query_supported)
		जाओ out;

	fd = खोलो("/", O_RDONLY);
	अगर (fd < 0) अणु
		p_err("perf_query_support: cannot open directory \"/\" (%s)",
		      म_त्रुटि(त्रुटि_सं));
		जाओ out;
	पूर्ण

	/* the following query will fail as no bpf attachment,
	 * the expected त्रुटि_सं is ENOTSUPP
	 */
	त्रुटि_सं = 0;
	len = माप(buf);
	bpf_task_fd_query(getpid(), fd, 0, buf, &len, &prog_id,
			  &fd_type, &probe_offset, &probe_addr);

	अगर (त्रुटि_सं == 524 /* ENOTSUPP */) अणु
		perf_query_supported = 1;
		जाओ बंद_fd;
	पूर्ण

	perf_query_supported = 2;
	p_err("perf_query_support: %s", म_त्रुटि(त्रुटि_सं));
	ख_लिखो(मानक_त्रुटि,
		"HINT: non root or kernel doesn't support TASK_FD_QUERY\n");

बंद_fd:
	बंद(fd);
out:
	वापस perf_query_supported == 1;
पूर्ण

अटल व्योम prपूर्णांक_perf_json(पूर्णांक pid, पूर्णांक fd, __u32 prog_id, __u32 fd_type,
			    अक्षर *buf, __u64 probe_offset, __u64 probe_addr)
अणु
	jsonw_start_object(json_wtr);
	jsonw_पूर्णांक_field(json_wtr, "pid", pid);
	jsonw_पूर्णांक_field(json_wtr, "fd", fd);
	jsonw_uपूर्णांक_field(json_wtr, "prog_id", prog_id);
	चयन (fd_type) अणु
	हाल BPF_FD_TYPE_RAW_TRACEPOINT:
		jsonw_string_field(json_wtr, "fd_type", "raw_tracepoint");
		jsonw_string_field(json_wtr, "tracepoint", buf);
		अवरोध;
	हाल BPF_FD_TYPE_TRACEPOINT:
		jsonw_string_field(json_wtr, "fd_type", "tracepoint");
		jsonw_string_field(json_wtr, "tracepoint", buf);
		अवरोध;
	हाल BPF_FD_TYPE_KPROBE:
		jsonw_string_field(json_wtr, "fd_type", "kprobe");
		अगर (buf[0] != '\0') अणु
			jsonw_string_field(json_wtr, "func", buf);
			jsonw_lluपूर्णांक_field(json_wtr, "offset", probe_offset);
		पूर्ण अन्यथा अणु
			jsonw_lluपूर्णांक_field(json_wtr, "addr", probe_addr);
		पूर्ण
		अवरोध;
	हाल BPF_FD_TYPE_KRETPROBE:
		jsonw_string_field(json_wtr, "fd_type", "kretprobe");
		अगर (buf[0] != '\0') अणु
			jsonw_string_field(json_wtr, "func", buf);
			jsonw_lluपूर्णांक_field(json_wtr, "offset", probe_offset);
		पूर्ण अन्यथा अणु
			jsonw_lluपूर्णांक_field(json_wtr, "addr", probe_addr);
		पूर्ण
		अवरोध;
	हाल BPF_FD_TYPE_UPROBE:
		jsonw_string_field(json_wtr, "fd_type", "uprobe");
		jsonw_string_field(json_wtr, "filename", buf);
		jsonw_lluपूर्णांक_field(json_wtr, "offset", probe_offset);
		अवरोध;
	हाल BPF_FD_TYPE_URETPROBE:
		jsonw_string_field(json_wtr, "fd_type", "uretprobe");
		jsonw_string_field(json_wtr, "filename", buf);
		jsonw_lluपूर्णांक_field(json_wtr, "offset", probe_offset);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	jsonw_end_object(json_wtr);
पूर्ण

अटल व्योम prपूर्णांक_perf_plain(पूर्णांक pid, पूर्णांक fd, __u32 prog_id, __u32 fd_type,
			     अक्षर *buf, __u64 probe_offset, __u64 probe_addr)
अणु
	म_लिखो("pid %d  fd %d: prog_id %u  ", pid, fd, prog_id);
	चयन (fd_type) अणु
	हाल BPF_FD_TYPE_RAW_TRACEPOINT:
		म_लिखो("raw_tracepoint  %s\n", buf);
		अवरोध;
	हाल BPF_FD_TYPE_TRACEPOINT:
		म_लिखो("tracepoint  %s\n", buf);
		अवरोध;
	हाल BPF_FD_TYPE_KPROBE:
		अगर (buf[0] != '\0')
			म_लिखो("kprobe  func %s  offset %llu\n", buf,
			       probe_offset);
		अन्यथा
			म_लिखो("kprobe  addr %llu\n", probe_addr);
		अवरोध;
	हाल BPF_FD_TYPE_KRETPROBE:
		अगर (buf[0] != '\0')
			म_लिखो("kretprobe  func %s  offset %llu\n", buf,
			       probe_offset);
		अन्यथा
			म_लिखो("kretprobe  addr %llu\n", probe_addr);
		अवरोध;
	हाल BPF_FD_TYPE_UPROBE:
		म_लिखो("uprobe  filename %s  offset %llu\n", buf, probe_offset);
		अवरोध;
	हाल BPF_FD_TYPE_URETPROBE:
		म_लिखो("uretprobe  filename %s  offset %llu\n", buf,
		       probe_offset);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक show_proc(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb,
		     पूर्णांक tflag, काष्ठा FTW *ftwbuf)
अणु
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	पूर्णांक err, pid = 0, fd = 0;
	स्थिर अक्षर *pch;
	अक्षर buf[4096];

	/* prefix always /proc */
	pch = fpath + 5;
	अगर (*pch == '\0')
		वापस 0;

	/* pid should be all numbers */
	pch++;
	जबतक (है_अंक(*pch)) अणु
		pid = pid * 10 + *pch - '0';
		pch++;
	पूर्ण
	अगर (*pch == '\0')
		वापस 0;
	अगर (*pch != '/')
		वापस FTW_SKIP_SUBTREE;

	/* check /proc/<pid>/fd directory */
	pch++;
	अगर (म_भेदन(pch, "fd", 2))
		वापस FTW_SKIP_SUBTREE;
	pch += 2;
	अगर (*pch == '\0')
		वापस 0;
	अगर (*pch != '/')
		वापस FTW_SKIP_SUBTREE;

	/* check /proc/<pid>/fd/<fd_num> */
	pch++;
	जबतक (है_अंक(*pch)) अणु
		fd = fd * 10 + *pch - '0';
		pch++;
	पूर्ण
	अगर (*pch != '\0')
		वापस FTW_SKIP_SUBTREE;

	/* query (pid, fd) क्रम potential perf events */
	len = माप(buf);
	err = bpf_task_fd_query(pid, fd, 0, buf, &len, &prog_id, &fd_type,
				&probe_offset, &probe_addr);
	अगर (err < 0)
		वापस 0;

	अगर (json_output)
		prपूर्णांक_perf_json(pid, fd, prog_id, fd_type, buf, probe_offset,
				probe_addr);
	अन्यथा
		prपूर्णांक_perf_plain(pid, fd, prog_id, fd_type, buf, probe_offset,
				 probe_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_show(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक flags = FTW_ACTIONRETVAL | FTW_PHYS;
	पूर्णांक err = 0, nखोलोfd = 16;

	अगर (!has_perf_query_support())
		वापस -1;

	अगर (json_output)
		jsonw_start_array(json_wtr);
	अगर (nftw("/proc", show_proc, nखोलोfd, flags) == -1) अणु
		p_err("%s", म_त्रुटि(त्रुटि_सं));
		err = -1;
	पूर्ण
	अगर (json_output)
		jsonw_end_array(json_wtr);

	वापस err;
पूर्ण

अटल पूर्णांक करो_help(पूर्णांक argc, अक्षर **argv)
अणु
	ख_लिखो(मानक_त्रुटि,
		"Usage: %1$s %2$s { show | list | help }\n"
		"",
		bin_name, argv[-2]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cmd cmds[] = अणु
	अणु "show",	करो_show पूर्ण,
	अणु "list",	करो_show पूर्ण,
	अणु "help",	करो_help पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

पूर्णांक करो_perf(पूर्णांक argc, अक्षर **argv)
अणु
	वापस cmd_select(cmds, argc, argv, करो_help);
पूर्ण
