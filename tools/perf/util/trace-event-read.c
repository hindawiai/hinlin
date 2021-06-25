<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <dirent.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <sys/mman.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>

#समावेश "trace-event.h"
#समावेश "debug.h"

अटल पूर्णांक input_fd;

अटल sमाप_प्रकार trace_data_size;
अटल bool repipe;

अटल पूर्णांक __करो_पढ़ो(पूर्णांक fd, व्योम *buf, पूर्णांक size)
अणु
	पूर्णांक rsize = size;

	जबतक (size) अणु
		पूर्णांक ret = पढ़ो(fd, buf, size);

		अगर (ret <= 0)
			वापस -1;

		अगर (repipe) अणु
			पूर्णांक retw = ग_लिखो(STDOUT_खाताNO, buf, ret);

			अगर (retw <= 0 || retw != ret) अणु
				pr_debug("repiping input file");
				वापस -1;
			पूर्ण
		पूर्ण

		size -= ret;
		buf += ret;
	पूर्ण

	वापस rsize;
पूर्ण

अटल पूर्णांक करो_पढ़ो(व्योम *data, पूर्णांक size)
अणु
	पूर्णांक r;

	r = __करो_पढ़ो(input_fd, data, size);
	अगर (r <= 0) अणु
		pr_debug("reading input file (size expected=%d received=%d)",
			 size, r);
		वापस -1;
	पूर्ण

	trace_data_size += r;

	वापस r;
पूर्ण

/* If it fails, the next पढ़ो will report it */
अटल व्योम skip(पूर्णांक size)
अणु
	अक्षर buf[बफ_मान];
	पूर्णांक r;

	जबतक (size) अणु
		r = size > बफ_मान ? बफ_मान : size;
		करो_पढ़ो(buf, r);
		size -= r;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक पढ़ो4(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित पूर्णांक data;

	अगर (करो_पढ़ो(&data, 4) < 0)
		वापस 0;
	वापस tep_पढ़ो_number(pevent, &data, 4);
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ पढ़ो8(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित दीर्घ दीर्घ data;

	अगर (करो_पढ़ो(&data, 8) < 0)
		वापस 0;
	वापस tep_पढ़ो_number(pevent, &data, 8);
पूर्ण

अटल अक्षर *पढ़ो_string(व्योम)
अणु
	अक्षर buf[बफ_मान];
	अक्षर *str = शून्य;
	पूर्णांक size = 0;
	off_t r;
	अक्षर c;

	क्रम (;;) अणु
		r = पढ़ो(input_fd, &c, 1);
		अगर (r < 0) अणु
			pr_debug("reading input file");
			जाओ out;
		पूर्ण

		अगर (!r) अणु
			pr_debug("no data");
			जाओ out;
		पूर्ण

		अगर (repipe) अणु
			पूर्णांक retw = ग_लिखो(STDOUT_खाताNO, &c, 1);

			अगर (retw <= 0 || retw != r) अणु
				pr_debug("repiping input file string");
				जाओ out;
			पूर्ण
		पूर्ण

		buf[size++] = c;

		अगर (!c)
			अवरोध;
	पूर्ण

	trace_data_size += size;

	str = दो_स्मृति(size);
	अगर (str)
		स_नकल(str, buf, size);
out:
	वापस str;
पूर्ण

अटल पूर्णांक पढ़ो_proc_kallsyms(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित पूर्णांक size;

	size = पढ़ो4(pevent);
	अगर (!size)
		वापस 0;
	/*
	 * Just skip it, now that we configure libtraceevent to use the
	 * tools/perf/ symbol resolver.
	 *
	 * We need to skip it so that we can जारी parsing old perf.data
	 * files, that contains this /proc/kallsyms payload.
	 *
	 * Newer perf.data files will have just the 4-bytes zeros "kallsyms
	 * payload", so that older tools can जारी पढ़ोing it and पूर्णांकerpret
	 * it as "no kallsyms payload is present".
	 */
	lseek(input_fd, size, प्रस्तुत_से);
	trace_data_size += size;
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_ftrace_prपूर्णांकk(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित पूर्णांक size;
	अक्षर *buf;

	/* it can have 0 size */
	size = पढ़ो4(pevent);
	अगर (!size)
		वापस 0;

	buf = दो_स्मृति(size + 1);
	अगर (buf == शून्य)
		वापस -1;

	अगर (करो_पढ़ो(buf, size) < 0) अणु
		मुक्त(buf);
		वापस -1;
	पूर्ण

	buf[size] = '\0';

	parse_ftrace_prपूर्णांकk(pevent, buf, size);

	मुक्त(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_header_files(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *header_page;
	अक्षर buf[बफ_मान];
	पूर्णांक ret = 0;

	अगर (करो_पढ़ो(buf, 12) < 0)
		वापस -1;

	अगर (स_भेद(buf, "header_page", 12) != 0) अणु
		pr_debug("did not read header page");
		वापस -1;
	पूर्ण

	size = पढ़ो8(pevent);

	header_page = दो_स्मृति(size);
	अगर (header_page == शून्य)
		वापस -1;

	अगर (करो_पढ़ो(header_page, size) < 0) अणु
		pr_debug("did not read header page");
		मुक्त(header_page);
		वापस -1;
	पूर्ण

	अगर (!tep_parse_header_page(pevent, header_page, size,
				   tep_get_दीर्घ_size(pevent))) अणु
		/*
		 * The commit field in the page is of type दीर्घ,
		 * use that instead, since it represents the kernel.
		 */
		tep_set_दीर्घ_size(pevent, tep_get_header_page_size(pevent));
	पूर्ण
	मुक्त(header_page);

	अगर (करो_पढ़ो(buf, 13) < 0)
		वापस -1;

	अगर (स_भेद(buf, "header_event", 13) != 0) अणु
		pr_debug("did not read header event");
		वापस -1;
	पूर्ण

	size = पढ़ो8(pevent);
	skip(size);

	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_ftrace_file(काष्ठा tep_handle *pevent, अचिन्हित दीर्घ दीर्घ size)
अणु
	पूर्णांक ret;
	अक्षर *buf;

	buf = दो_स्मृति(size);
	अगर (buf == शून्य) अणु
		pr_debug("memory allocation failure\n");
		वापस -1;
	पूर्ण

	ret = करो_पढ़ो(buf, size);
	अगर (ret < 0) अणु
		pr_debug("error reading ftrace file.\n");
		जाओ out;
	पूर्ण

	ret = parse_ftrace_file(pevent, buf, size);
	अगर (ret < 0)
		pr_debug("error parsing ftrace file.\n");
out:
	मुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_event_file(काष्ठा tep_handle *pevent, अक्षर *sys,
			   अचिन्हित दीर्घ दीर्घ size)
अणु
	पूर्णांक ret;
	अक्षर *buf;

	buf = दो_स्मृति(size);
	अगर (buf == शून्य) अणु
		pr_debug("memory allocation failure\n");
		वापस -1;
	पूर्ण

	ret = करो_पढ़ो(buf, size);
	अगर (ret < 0)
		जाओ out;

	ret = parse_event_file(pevent, buf, size, sys);
	अगर (ret < 0)
		pr_debug("error parsing event file.\n");
out:
	मुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो_ftrace_files(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	पूर्णांक count;
	पूर्णांक i;
	पूर्णांक ret;

	count = पढ़ो4(pevent);

	क्रम (i = 0; i < count; i++) अणु
		size = पढ़ो8(pevent);
		ret = पढ़ो_ftrace_file(pevent, size);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_event_files(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *sys;
	पूर्णांक प्रणालीs;
	पूर्णांक count;
	पूर्णांक i,x;
	पूर्णांक ret;

	प्रणालीs = पढ़ो4(pevent);

	क्रम (i = 0; i < प्रणालीs; i++) अणु
		sys = पढ़ो_string();
		अगर (sys == शून्य)
			वापस -1;

		count = पढ़ो4(pevent);

		क्रम (x=0; x < count; x++) अणु
			size = पढ़ो8(pevent);
			ret = पढ़ो_event_file(pevent, sys, size);
			अगर (ret) अणु
				मुक्त(sys);
				वापस ret;
			पूर्ण
		पूर्ण
		मुक्त(sys);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_saved_cmdline(काष्ठा tep_handle *pevent)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *buf;
	पूर्णांक ret;

	/* it can have 0 size */
	size = पढ़ो8(pevent);
	अगर (!size)
		वापस 0;

	buf = दो_स्मृति(size + 1);
	अगर (buf == शून्य) अणु
		pr_debug("memory allocation failure\n");
		वापस -1;
	पूर्ण

	ret = करो_पढ़ो(buf, size);
	अगर (ret < 0) अणु
		pr_debug("error reading saved cmdlines\n");
		जाओ out;
	पूर्ण
	buf[ret] = '\0';

	parse_saved_cmdline(pevent, buf, size);
	ret = 0;
out:
	मुक्त(buf);
	वापस ret;
पूर्ण

sमाप_प्रकार trace_report(पूर्णांक fd, काष्ठा trace_event *tevent, bool __repipe)
अणु
	अक्षर buf[बफ_मान];
	अक्षर test[] = अणु 23, 8, 68 पूर्ण;
	अक्षर *version;
	पूर्णांक show_version = 0;
	पूर्णांक show_funcs = 0;
	पूर्णांक show_prपूर्णांकk = 0;
	sमाप_प्रकार size = -1;
	पूर्णांक file_bigendian;
	पूर्णांक host_bigendian;
	पूर्णांक file_दीर्घ_size;
	पूर्णांक file_page_size;
	काष्ठा tep_handle *pevent = शून्य;
	पूर्णांक err;

	repipe = __repipe;
	input_fd = fd;

	अगर (करो_पढ़ो(buf, 3) < 0)
		वापस -1;
	अगर (स_भेद(buf, test, 3) != 0) अणु
		pr_debug("no trace data in the file");
		वापस -1;
	पूर्ण

	अगर (करो_पढ़ो(buf, 7) < 0)
		वापस -1;
	अगर (स_भेद(buf, "tracing", 7) != 0) अणु
		pr_debug("not a trace file (missing 'tracing' tag)");
		वापस -1;
	पूर्ण

	version = पढ़ो_string();
	अगर (version == शून्य)
		वापस -1;
	अगर (show_version)
		म_लिखो("version = %s\n", version);

	अगर (करो_पढ़ो(buf, 1) < 0) अणु
		मुक्त(version);
		वापस -1;
	पूर्ण
	file_bigendian = buf[0];
	host_bigendian = bigendian();

	अगर (trace_event__init(tevent)) अणु
		pr_debug("trace_event__init failed");
		जाओ out;
	पूर्ण

	pevent = tevent->pevent;

	tep_set_flag(pevent, TEP_NSEC_OUTPUT);
	tep_set_file_bigendian(pevent, file_bigendian);
	tep_set_local_bigendian(pevent, host_bigendian);

	अगर (करो_पढ़ो(buf, 1) < 0)
		जाओ out;
	file_दीर्घ_size = buf[0];

	file_page_size = पढ़ो4(pevent);
	अगर (!file_page_size)
		जाओ out;

	tep_set_दीर्घ_size(pevent, file_दीर्घ_size);
	tep_set_page_size(pevent, file_page_size);

	err = पढ़ो_header_files(pevent);
	अगर (err)
		जाओ out;
	err = पढ़ो_ftrace_files(pevent);
	अगर (err)
		जाओ out;
	err = पढ़ो_event_files(pevent);
	अगर (err)
		जाओ out;
	err = पढ़ो_proc_kallsyms(pevent);
	अगर (err)
		जाओ out;
	err = पढ़ो_ftrace_prपूर्णांकk(pevent);
	अगर (err)
		जाओ out;
	अगर (म_से_भ(version) >= 0.6) अणु
		err = पढ़ो_saved_cmdline(pevent);
		अगर (err)
			जाओ out;
	पूर्ण

	size = trace_data_size;
	repipe = false;

	अगर (show_funcs) अणु
		tep_prपूर्णांक_funcs(pevent);
	पूर्ण अन्यथा अगर (show_prपूर्णांकk) अणु
		tep_prपूर्णांक_prपूर्णांकk(pevent);
	पूर्ण

	pevent = शून्य;

out:
	अगर (pevent)
		trace_event__cleanup(tevent);
	मुक्त(version);
	वापस size;
पूर्ण
