<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008,2009, Steven Rostedt <srostedt@redhat.com>
 */
#समावेश <dirent.h>
#समावेश <mntent.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/रुको.h>
#समावेश <fcntl.h>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>
#समावेश <linux/list.h>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <पूर्णांकernal/lib.h> // page_size

#समावेश "trace-event.h"
#समावेश <api/fs/tracing_path.h>
#समावेश "evsel.h"
#समावेश "debug.h"

#घोषणा VERSION "0.6"

अटल पूर्णांक output_fd;


पूर्णांक bigendian(व्योम)
अणु
	अचिन्हित अक्षर str[] = अणु 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x0पूर्ण;
	अचिन्हित पूर्णांक *ptr;

	ptr = (अचिन्हित पूर्णांक *)(व्योम *)str;
	वापस *ptr == 0x01020304;
पूर्ण

/* unक्रमtunately, you can not stat debugfs or proc files क्रम size */
अटल पूर्णांक record_file(स्थिर अक्षर *file, sमाप_प्रकार hdr_sz)
अणु
	अचिन्हित दीर्घ दीर्घ size = 0;
	अक्षर buf[बफ_मान], *sizep;
	off_t hdr_pos = lseek(output_fd, 0, प्रस्तुत_से);
	पूर्णांक r, fd;
	पूर्णांक err = -EIO;

	fd = खोलो(file, O_RDONLY);
	अगर (fd < 0) अणु
		pr_debug("Can't read '%s'", file);
		वापस -त्रुटि_सं;
	पूर्ण

	/* put in zeros क्रम file size, then fill true size later */
	अगर (hdr_sz) अणु
		अगर (ग_लिखो(output_fd, &size, hdr_sz) != hdr_sz)
			जाओ out;
	पूर्ण

	करो अणु
		r = पढ़ो(fd, buf, बफ_मान);
		अगर (r > 0) अणु
			size += r;
			अगर (ग_लिखो(output_fd, buf, r) != r)
				जाओ out;
		पूर्ण
	पूर्ण जबतक (r > 0);

	/* ugh, handle big-endian hdr_size == 4 */
	sizep = (अक्षर*)&size;
	अगर (bigendian())
		sizep += माप(u64) - hdr_sz;

	अगर (hdr_sz && pग_लिखो(output_fd, sizep, hdr_sz, hdr_pos) < 0) अणु
		pr_debug("writing file size failed\n");
		जाओ out;
	पूर्ण

	err = 0;
out:
	बंद(fd);
	वापस err;
पूर्ण

अटल पूर्णांक record_header_files(व्योम)
अणु
	अक्षर *path = get_events_file("header_page");
	काष्ठा stat st;
	पूर्णांक err = -EIO;

	अगर (!path) अणु
		pr_debug("can't get tracing/events/header_page");
		वापस -ENOMEM;
	पूर्ण

	अगर (stat(path, &st) < 0) अणु
		pr_debug("can't read '%s'", path);
		जाओ out;
	पूर्ण

	अगर (ग_लिखो(output_fd, "header_page", 12) != 12) अणु
		pr_debug("can't write header_page\n");
		जाओ out;
	पूर्ण

	अगर (record_file(path, 8) < 0) अणु
		pr_debug("can't record header_page file\n");
		जाओ out;
	पूर्ण

	put_events_file(path);

	path = get_events_file("header_event");
	अगर (!path) अणु
		pr_debug("can't get tracing/events/header_event");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (stat(path, &st) < 0) अणु
		pr_debug("can't read '%s'", path);
		जाओ out;
	पूर्ण

	अगर (ग_लिखो(output_fd, "header_event", 13) != 13) अणु
		pr_debug("can't write header_event\n");
		जाओ out;
	पूर्ण

	अगर (record_file(path, 8) < 0) अणु
		pr_debug("can't record header_event file\n");
		जाओ out;
	पूर्ण

	err = 0;
out:
	put_events_file(path);
	वापस err;
पूर्ण

अटल bool name_in_tp_list(अक्षर *sys, काष्ठा tracepoपूर्णांक_path *tps)
अणु
	जबतक (tps) अणु
		अगर (!म_भेद(sys, tps->name))
			वापस true;
		tps = tps->next;
	पूर्ण

	वापस false;
पूर्ण

#घोषणा क्रम_each_event_tps(dir, dent, tps)			\
	जबतक ((dent = सूची_पढ़ो(dir)))				\
		अगर (dent->d_type == DT_सूची &&			\
		    (म_भेद(dent->d_name, ".")) &&		\
		    (म_भेद(dent->d_name, "..")))		\

अटल पूर्णांक copy_event_प्रणाली(स्थिर अक्षर *sys, काष्ठा tracepoपूर्णांक_path *tps)
अणु
	काष्ठा dirent *dent;
	काष्ठा stat st;
	अक्षर *क्रमmat;
	सूची *dir;
	पूर्णांक count = 0;
	पूर्णांक ret;
	पूर्णांक err;

	dir = सूची_खोलो(sys);
	अगर (!dir) अणु
		pr_debug("can't read directory '%s'", sys);
		वापस -त्रुटि_सं;
	पूर्ण

	क्रम_each_event_tps(dir, dent, tps) अणु
		अगर (!name_in_tp_list(dent->d_name, tps))
			जारी;

		अगर (aप्र_लिखो(&क्रमmat, "%s/%s/format", sys, dent->d_name) < 0) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = stat(क्रमmat, &st);
		मुक्त(क्रमmat);
		अगर (ret < 0)
			जारी;
		count++;
	पूर्ण

	अगर (ग_लिखो(output_fd, &count, 4) != 4) अणु
		err = -EIO;
		pr_debug("can't write count\n");
		जाओ out;
	पूर्ण

	सूची_शुरु(dir);
	क्रम_each_event_tps(dir, dent, tps) अणु
		अगर (!name_in_tp_list(dent->d_name, tps))
			जारी;

		अगर (aप्र_लिखो(&क्रमmat, "%s/%s/format", sys, dent->d_name) < 0) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = stat(क्रमmat, &st);

		अगर (ret >= 0) अणु
			err = record_file(क्रमmat, 8);
			अगर (err) अणु
				मुक्त(क्रमmat);
				जाओ out;
			पूर्ण
		पूर्ण
		मुक्त(क्रमmat);
	पूर्ण
	err = 0;
out:
	बंद_सूची(dir);
	वापस err;
पूर्ण

अटल पूर्णांक record_ftrace_files(काष्ठा tracepoपूर्णांक_path *tps)
अणु
	अक्षर *path;
	पूर्णांक ret;

	path = get_events_file("ftrace");
	अगर (!path) अणु
		pr_debug("can't get tracing/events/ftrace");
		वापस -ENOMEM;
	पूर्ण

	ret = copy_event_प्रणाली(path, tps);

	put_tracing_file(path);

	वापस ret;
पूर्ण

अटल bool प्रणाली_in_tp_list(अक्षर *sys, काष्ठा tracepoपूर्णांक_path *tps)
अणु
	जबतक (tps) अणु
		अगर (!म_भेद(sys, tps->प्रणाली))
			वापस true;
		tps = tps->next;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक record_event_files(काष्ठा tracepoपूर्णांक_path *tps)
अणु
	काष्ठा dirent *dent;
	काष्ठा stat st;
	अक्षर *path;
	अक्षर *sys;
	सूची *dir;
	पूर्णांक count = 0;
	पूर्णांक ret;
	पूर्णांक err;

	path = get_tracing_file("events");
	अगर (!path) अणु
		pr_debug("can't get tracing/events");
		वापस -ENOMEM;
	पूर्ण

	dir = सूची_खोलो(path);
	अगर (!dir) अणु
		err = -त्रुटि_सं;
		pr_debug("can't read directory '%s'", path);
		जाओ out;
	पूर्ण

	क्रम_each_event_tps(dir, dent, tps) अणु
		अगर (म_भेद(dent->d_name, "ftrace") == 0 ||
		    !प्रणाली_in_tp_list(dent->d_name, tps))
			जारी;

		count++;
	पूर्ण

	अगर (ग_लिखो(output_fd, &count, 4) != 4) अणु
		err = -EIO;
		pr_debug("can't write count\n");
		जाओ out;
	पूर्ण

	सूची_शुरु(dir);
	क्रम_each_event_tps(dir, dent, tps) अणु
		अगर (म_भेद(dent->d_name, "ftrace") == 0 ||
		    !प्रणाली_in_tp_list(dent->d_name, tps))
			जारी;

		अगर (aप्र_लिखो(&sys, "%s/%s", path, dent->d_name) < 0) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = stat(sys, &st);
		अगर (ret >= 0) अणु
			sमाप_प्रकार size = म_माप(dent->d_name) + 1;

			अगर (ग_लिखो(output_fd, dent->d_name, size) != size ||
			    copy_event_प्रणाली(sys, tps) < 0) अणु
				err = -EIO;
				मुक्त(sys);
				जाओ out;
			पूर्ण
		पूर्ण
		मुक्त(sys);
	पूर्ण
	err = 0;
out:
	बंद_सूची(dir);
	put_tracing_file(path);

	वापस err;
पूर्ण

अटल पूर्णांक record_proc_kallsyms(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ size = 0;
	/*
	 * Just to keep older perf.data file parsers happy, record a zero
	 * sized kallsyms file, i.e. करो the same thing that was करोne when
	 * /proc/kallsyms (or something specअगरied via --kallsyms, in a
	 * dअगरferent path) couldn't be पढ़ो.
	 */
	वापस ग_लिखो(output_fd, &size, 4) != 4 ? -EIO : 0;
पूर्ण

अटल पूर्णांक record_ftrace_prपूर्णांकk(व्योम)
अणु
	अचिन्हित पूर्णांक size;
	अक्षर *path;
	काष्ठा stat st;
	पूर्णांक ret, err = 0;

	path = get_tracing_file("printk_formats");
	अगर (!path) अणु
		pr_debug("can't get tracing/printk_formats");
		वापस -ENOMEM;
	पूर्ण

	ret = stat(path, &st);
	अगर (ret < 0) अणु
		/* not found */
		size = 0;
		अगर (ग_लिखो(output_fd, &size, 4) != 4)
			err = -EIO;
		जाओ out;
	पूर्ण
	err = record_file(path, 4);

out:
	put_tracing_file(path);
	वापस err;
पूर्ण

अटल पूर्णांक record_saved_cmdline(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ size;
	अक्षर *path;
	काष्ठा stat st;
	पूर्णांक ret, err = 0;

	path = get_tracing_file("saved_cmdlines");
	अगर (!path) अणु
		pr_debug("can't get tracing/saved_cmdline");
		वापस -ENOMEM;
	पूर्ण

	ret = stat(path, &st);
	अगर (ret < 0) अणु
		/* not found */
		size = 0;
		अगर (ग_लिखो(output_fd, &size, 8) != 8)
			err = -EIO;
		जाओ out;
	पूर्ण
	err = record_file(path, 8);

out:
	put_tracing_file(path);
	वापस err;
पूर्ण

अटल व्योम
put_tracepoपूर्णांकs_path(काष्ठा tracepoपूर्णांक_path *tps)
अणु
	जबतक (tps) अणु
		काष्ठा tracepoपूर्णांक_path *t = tps;

		tps = tps->next;
		zमुक्त(&t->name);
		zमुक्त(&t->प्रणाली);
		मुक्त(t);
	पूर्ण
पूर्ण

अटल काष्ठा tracepoपूर्णांक_path *
get_tracepoपूर्णांकs_path(काष्ठा list_head *pattrs)
अणु
	काष्ठा tracepoपूर्णांक_path path, *ppath = &path;
	काष्ठा evsel *pos;
	पूर्णांक nr_tracepoपूर्णांकs = 0;

	list_क्रम_each_entry(pos, pattrs, core.node) अणु
		अगर (pos->core.attr.type != PERF_TYPE_TRACEPOINT)
			जारी;
		++nr_tracepoपूर्णांकs;

		अगर (pos->name) अणु
			ppath->next = tracepoपूर्णांक_name_to_path(pos->name);
			अगर (ppath->next)
				जाओ next;

			अगर (म_अक्षर(pos->name, ':') == शून्य)
				जाओ try_id;

			जाओ error;
		पूर्ण

try_id:
		ppath->next = tracepoपूर्णांक_id_to_path(pos->core.attr.config);
		अगर (!ppath->next) अणु
error:
			pr_debug("No memory to alloc tracepoints list\n");
			put_tracepoपूर्णांकs_path(path.next);
			वापस शून्य;
		पूर्ण
next:
		ppath = ppath->next;
	पूर्ण

	वापस nr_tracepoपूर्णांकs > 0 ? path.next : शून्य;
पूर्ण

bool have_tracepoपूर्णांकs(काष्ठा list_head *pattrs)
अणु
	काष्ठा evsel *pos;

	list_क्रम_each_entry(pos, pattrs, core.node)
		अगर (pos->core.attr.type == PERF_TYPE_TRACEPOINT)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक tracing_data_header(व्योम)
अणु
	अक्षर buf[20];
	sमाप_प्रकार size;

	/* just guessing this is someone's birthday.. ;) */
	buf[0] = 23;
	buf[1] = 8;
	buf[2] = 68;
	स_नकल(buf + 3, "tracing", 7);

	अगर (ग_लिखो(output_fd, buf, 10) != 10)
		वापस -1;

	size = म_माप(VERSION) + 1;
	अगर (ग_लिखो(output_fd, VERSION, size) != size)
		वापस -1;

	/* save endian */
	अगर (bigendian())
		buf[0] = 1;
	अन्यथा
		buf[0] = 0;

	अगर (ग_लिखो(output_fd, buf, 1) != 1)
		वापस -1;

	/* save size of दीर्घ */
	buf[0] = माप(दीर्घ);
	अगर (ग_लिखो(output_fd, buf, 1) != 1)
		वापस -1;

	/* save page_size */
	अगर (ग_लिखो(output_fd, &page_size, 4) != 4)
		वापस -1;

	वापस 0;
पूर्ण

काष्ठा tracing_data *tracing_data_get(काष्ठा list_head *pattrs,
				      पूर्णांक fd, bool temp)
अणु
	काष्ठा tracepoपूर्णांक_path *tps;
	काष्ठा tracing_data *tdata;
	पूर्णांक err;

	output_fd = fd;

	tps = get_tracepoपूर्णांकs_path(pattrs);
	अगर (!tps)
		वापस शून्य;

	tdata = दो_स्मृति(माप(*tdata));
	अगर (!tdata)
		वापस शून्य;

	tdata->temp = temp;
	tdata->size = 0;

	अगर (temp) अणु
		पूर्णांक temp_fd;

		snम_लिखो(tdata->temp_file, माप(tdata->temp_file),
			 "/tmp/perf-XXXXXX");
		अगर (!mkstemp(tdata->temp_file)) अणु
			pr_debug("Can't make temp file");
			मुक्त(tdata);
			वापस शून्य;
		पूर्ण

		temp_fd = खोलो(tdata->temp_file, O_RDWR);
		अगर (temp_fd < 0) अणु
			pr_debug("Can't read '%s'", tdata->temp_file);
			मुक्त(tdata);
			वापस शून्य;
		पूर्ण

		/*
		 * Set the temp file the शेष output, so all the
		 * tracing data are stored पूर्णांकo it.
		 */
		output_fd = temp_fd;
	पूर्ण

	err = tracing_data_header();
	अगर (err)
		जाओ out;
	err = record_header_files();
	अगर (err)
		जाओ out;
	err = record_ftrace_files(tps);
	अगर (err)
		जाओ out;
	err = record_event_files(tps);
	अगर (err)
		जाओ out;
	err = record_proc_kallsyms();
	अगर (err)
		जाओ out;
	err = record_ftrace_prपूर्णांकk();
	अगर (err)
		जाओ out;
	err = record_saved_cmdline();

out:
	/*
	 * All tracing data are stored by now, we can restore
	 * the शेष output file in हाल we used temp file.
	 */
	अगर (temp) अणु
		tdata->size = lseek(output_fd, 0, प्रस्तुत_से);
		बंद(output_fd);
		output_fd = fd;
	पूर्ण

	अगर (err)
		zमुक्त(&tdata);

	put_tracepoपूर्णांकs_path(tps);
	वापस tdata;
पूर्ण

पूर्णांक tracing_data_put(काष्ठा tracing_data *tdata)
अणु
	पूर्णांक err = 0;

	अगर (tdata->temp) अणु
		err = record_file(tdata->temp_file, 0);
		unlink(tdata->temp_file);
	पूर्ण

	मुक्त(tdata);
	वापस err;
पूर्ण

पूर्णांक पढ़ो_tracing_data(पूर्णांक fd, काष्ठा list_head *pattrs)
अणु
	पूर्णांक err;
	काष्ठा tracing_data *tdata;

	/*
	 * We work over the real file, so we can ग_लिखो data
	 * directly, no temp file is needed.
	 */
	tdata = tracing_data_get(pattrs, fd, false);
	अगर (!tdata)
		वापस -ENOMEM;

	err = tracing_data_put(tdata);
	वापस err;
पूर्ण
