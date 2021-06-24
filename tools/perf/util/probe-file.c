<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * probe-file.c : operate ftrace k/uprobe events files
 *
 * Written by Masami Hiramatsu <masami.hiramatsu.pt@hitachi.com>
 */
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <sys/uपन.स>
#समावेश <unistd.h>
#समावेश <linux/zभाग.स>
#समावेश "namespaces.h"
#समावेश "event.h"
#समावेश "strlist.h"
#समावेश "strfilter.h"
#समावेश "debug.h"
#समावेश "build-id.h"
#समावेश "dso.h"
#समावेश "color.h"
#समावेश "symbol.h"
#समावेश "strbuf.h"
#समावेश <api/fs/tracing_path.h>
#समावेश "probe-event.h"
#समावेश "probe-file.h"
#समावेश "session.h"
#समावेश "perf_regs.h"
#समावेश "string2.h"

/* 4096 - 2 ('\n' + '\0') */
#घोषणा MAX_CMDLEN 4094

अटल व्योम prपूर्णांक_खोलो_warning(पूर्णांक err, bool uprobe)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (err == -ENOENT) अणु
		स्थिर अक्षर *config;

		अगर (uprobe)
			config = "CONFIG_UPROBE_EVENTS";
		अन्यथा
			config = "CONFIG_KPROBE_EVENTS";

		pr_warning("%cprobe_events file does not exist"
			   " - please rebuild kernel with %s.\n",
			   uprobe ? 'u' : 'k', config);
	पूर्ण अन्यथा अगर (err == -ENOTSUP)
		pr_warning("Tracefs or debugfs is not mounted.\n");
	अन्यथा
		pr_warning("Failed to open %cprobe_events: %s\n",
			   uprobe ? 'u' : 'k',
			   str_error_r(-err, sbuf, माप(sbuf)));
पूर्ण

अटल व्योम prपूर्णांक_both_खोलो_warning(पूर्णांक kerr, पूर्णांक uerr)
अणु
	/* Both kprobes and uprobes are disabled, warn it. */
	अगर (kerr == -ENOTSUP && uerr == -ENOTSUP)
		pr_warning("Tracefs or debugfs is not mounted.\n");
	अन्यथा अगर (kerr == -ENOENT && uerr == -ENOENT)
		pr_warning("Please rebuild kernel with CONFIG_KPROBE_EVENTS "
			   "or/and CONFIG_UPROBE_EVENTS.\n");
	अन्यथा अणु
		अक्षर sbuf[STRERR_बफ_मानE];
		pr_warning("Failed to open kprobe events: %s.\n",
			   str_error_r(-kerr, sbuf, माप(sbuf)));
		pr_warning("Failed to open uprobe events: %s.\n",
			   str_error_r(-uerr, sbuf, माप(sbuf)));
	पूर्ण
पूर्ण

पूर्णांक खोलो_trace_file(स्थिर अक्षर *trace_file, bool पढ़ोग_लिखो)
अणु
	अक्षर buf[PATH_MAX];
	पूर्णांक ret;

	ret = e_snम_लिखो(buf, PATH_MAX, "%s/%s", tracing_path_mount(), trace_file);
	अगर (ret >= 0) अणु
		pr_debug("Opening %s write=%d\n", buf, पढ़ोग_लिखो);
		अगर (पढ़ोग_लिखो && !probe_event_dry_run)
			ret = खोलो(buf, O_RDWR | O_APPEND, 0);
		अन्यथा
			ret = खोलो(buf, O_RDONLY, 0);

		अगर (ret < 0)
			ret = -त्रुटि_सं;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक खोलो_kprobe_events(bool पढ़ोग_लिखो)
अणु
	वापस खोलो_trace_file("kprobe_events", पढ़ोग_लिखो);
पूर्ण

अटल पूर्णांक खोलो_uprobe_events(bool पढ़ोग_लिखो)
अणु
	वापस खोलो_trace_file("uprobe_events", पढ़ोग_लिखो);
पूर्ण

पूर्णांक probe_file__खोलो(पूर्णांक flag)
अणु
	पूर्णांक fd;

	अगर (flag & PF_FL_UPROBE)
		fd = खोलो_uprobe_events(flag & PF_FL_RW);
	अन्यथा
		fd = खोलो_kprobe_events(flag & PF_FL_RW);
	अगर (fd < 0)
		prपूर्णांक_खोलो_warning(fd, flag & PF_FL_UPROBE);

	वापस fd;
पूर्ण

पूर्णांक probe_file__खोलो_both(पूर्णांक *kfd, पूर्णांक *ufd, पूर्णांक flag)
अणु
	अगर (!kfd || !ufd)
		वापस -EINVAL;

	*kfd = खोलो_kprobe_events(flag & PF_FL_RW);
	*ufd = खोलो_uprobe_events(flag & PF_FL_RW);
	अगर (*kfd < 0 && *ufd < 0) अणु
		prपूर्णांक_both_खोलो_warning(*kfd, *ufd);
		वापस *kfd;
	पूर्ण

	वापस 0;
पूर्ण

/* Get raw string list of current kprobe_events  or uprobe_events */
काष्ठा strlist *probe_file__get_rawlist(पूर्णांक fd)
अणु
	पूर्णांक ret, idx, fddup;
	खाता *fp;
	अक्षर buf[MAX_CMDLEN];
	अक्षर *p;
	काष्ठा strlist *sl;

	अगर (fd < 0)
		वापस शून्य;

	sl = strlist__new(शून्य, शून्य);
	अगर (sl == शून्य)
		वापस शून्य;

	fddup = dup(fd);
	अगर (fddup < 0)
		जाओ out_मुक्त_sl;

	fp = fकरोpen(fddup, "r");
	अगर (!fp)
		जाओ out_बंद_fddup;

	जबतक (!ख_पूर्ण(fp)) अणु
		p = ख_माला_लो(buf, MAX_CMDLEN, fp);
		अगर (!p)
			अवरोध;

		idx = म_माप(p) - 1;
		अगर (p[idx] == '\n')
			p[idx] = '\0';
		ret = strlist__add(sl, buf);
		अगर (ret < 0) अणु
			pr_debug("strlist__add failed (%d)\n", ret);
			जाओ out_बंद_fp;
		पूर्ण
	पूर्ण
	ख_बंद(fp);

	वापस sl;

out_बंद_fp:
	ख_बंद(fp);
	जाओ out_मुक्त_sl;
out_बंद_fddup:
	बंद(fddup);
out_मुक्त_sl:
	strlist__delete(sl);
	वापस शून्य;
पूर्ण

अटल काष्ठा strlist *__probe_file__get_namelist(पूर्णांक fd, bool include_group)
अणु
	अक्षर buf[128];
	काष्ठा strlist *sl, *rawlist;
	काष्ठा str_node *ent;
	काष्ठा probe_trace_event tev;
	पूर्णांक ret = 0;

	स_रखो(&tev, 0, माप(tev));
	rawlist = probe_file__get_rawlist(fd);
	अगर (!rawlist)
		वापस शून्य;
	sl = strlist__new(शून्य, शून्य);
	strlist__क्रम_each_entry(ent, rawlist) अणु
		ret = parse_probe_trace_command(ent->s, &tev);
		अगर (ret < 0)
			अवरोध;
		अगर (include_group) अणु
			ret = e_snम_लिखो(buf, 128, "%s:%s", tev.group,
					tev.event);
			अगर (ret >= 0)
				ret = strlist__add(sl, buf);
		पूर्ण अन्यथा
			ret = strlist__add(sl, tev.event);
		clear_probe_trace_event(&tev);
		/* Skip अगर there is same name multi-probe event in the list */
		अगर (ret == -EEXIST)
			ret = 0;
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	strlist__delete(rawlist);

	अगर (ret < 0) अणु
		strlist__delete(sl);
		वापस शून्य;
	पूर्ण
	वापस sl;
पूर्ण

/* Get current perf-probe event names */
काष्ठा strlist *probe_file__get_namelist(पूर्णांक fd)
अणु
	वापस __probe_file__get_namelist(fd, false);
पूर्ण

पूर्णांक probe_file__add_event(पूर्णांक fd, काष्ठा probe_trace_event *tev)
अणु
	पूर्णांक ret = 0;
	अक्षर *buf = synthesize_probe_trace_command(tev);
	अक्षर sbuf[STRERR_बफ_मानE];

	अगर (!buf) अणु
		pr_debug("Failed to synthesize probe trace event.\n");
		वापस -EINVAL;
	पूर्ण

	pr_debug("Writing event: %s\n", buf);
	अगर (!probe_event_dry_run) अणु
		अगर (ग_लिखो(fd, buf, म_माप(buf)) < (पूर्णांक)म_माप(buf)) अणु
			ret = -त्रुटि_सं;
			pr_warning("Failed to write event: %s\n",
				   str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		पूर्ण
	पूर्ण
	मुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक __del_trace_probe_event(पूर्णांक fd, काष्ठा str_node *ent)
अणु
	अक्षर *p;
	अक्षर buf[128];
	पूर्णांक ret;

	/* Convert from perf-probe event to trace-probe event */
	ret = e_snम_लिखो(buf, 128, "-:%s", ent->s);
	अगर (ret < 0)
		जाओ error;

	p = म_अक्षर(buf + 2, ':');
	अगर (!p) अणु
		pr_debug("Internal error: %s should have ':' but not.\n",
			 ent->s);
		ret = -ENOTSUP;
		जाओ error;
	पूर्ण
	*p = '/';

	pr_debug("Writing event: %s\n", buf);
	ret = ग_लिखो(fd, buf, म_माप(buf));
	अगर (ret < 0) अणु
		ret = -त्रुटि_सं;
		जाओ error;
	पूर्ण

	वापस 0;
error:
	pr_warning("Failed to delete event: %s\n",
		   str_error_r(-ret, buf, माप(buf)));
	वापस ret;
पूर्ण

पूर्णांक probe_file__get_events(पूर्णांक fd, काष्ठा strfilter *filter,
			   काष्ठा strlist *plist)
अणु
	काष्ठा strlist *namelist;
	काष्ठा str_node *ent;
	स्थिर अक्षर *p;
	पूर्णांक ret = -ENOENT;

	अगर (!plist)
		वापस -EINVAL;

	namelist = __probe_file__get_namelist(fd, true);
	अगर (!namelist)
		वापस -ENOENT;

	strlist__क्रम_each_entry(ent, namelist) अणु
		p = म_अक्षर(ent->s, ':');
		अगर ((p && strfilter__compare(filter, p + 1)) ||
		    strfilter__compare(filter, ent->s)) अणु
			ret = strlist__add(plist, ent->s);
			अगर (ret == -ENOMEM) अणु
				pr_err("strlist__add failed with -ENOMEM\n");
				जाओ out;
			पूर्ण
			ret = 0;
		पूर्ण
	पूर्ण
out:
	strlist__delete(namelist);

	वापस ret;
पूर्ण

पूर्णांक probe_file__del_strlist(पूर्णांक fd, काष्ठा strlist *namelist)
अणु
	पूर्णांक ret = 0;
	काष्ठा str_node *ent;

	strlist__क्रम_each_entry(ent, namelist) अणु
		ret = __del_trace_probe_event(fd, ent);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक probe_file__del_events(पूर्णांक fd, काष्ठा strfilter *filter)
अणु
	काष्ठा strlist *namelist;
	पूर्णांक ret;

	namelist = strlist__new(शून्य, शून्य);
	अगर (!namelist)
		वापस -ENOMEM;

	ret = probe_file__get_events(fd, filter, namelist);
	अगर (ret < 0)
		वापस ret;

	ret = probe_file__del_strlist(fd, namelist);
	strlist__delete(namelist);

	वापस ret;
पूर्ण

/* Caller must ensure to हटाओ this entry from list */
अटल व्योम probe_cache_entry__delete(काष्ठा probe_cache_entry *entry)
अणु
	अगर (entry) अणु
		BUG_ON(!list_empty(&entry->node));

		strlist__delete(entry->tevlist);
		clear_perf_probe_event(&entry->pev);
		zमुक्त(&entry->spev);
		मुक्त(entry);
	पूर्ण
पूर्ण

अटल काष्ठा probe_cache_entry *
probe_cache_entry__new(काष्ठा perf_probe_event *pev)
अणु
	काष्ठा probe_cache_entry *entry = zalloc(माप(*entry));

	अगर (entry) अणु
		INIT_LIST_HEAD(&entry->node);
		entry->tevlist = strlist__new(शून्य, शून्य);
		अगर (!entry->tevlist)
			zमुक्त(&entry);
		अन्यथा अगर (pev) अणु
			entry->spev = synthesize_perf_probe_command(pev);
			अगर (!entry->spev ||
			    perf_probe_event__copy(&entry->pev, pev) < 0) अणु
				probe_cache_entry__delete(entry);
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस entry;
पूर्ण

पूर्णांक probe_cache_entry__get_event(काष्ठा probe_cache_entry *entry,
				 काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा probe_trace_event *tev;
	काष्ठा str_node *node;
	पूर्णांक ret, i;

	ret = strlist__nr_entries(entry->tevlist);
	अगर (ret > probe_conf.max_probes)
		वापस -E2BIG;

	*tevs = zalloc(ret * माप(*tev));
	अगर (!*tevs)
		वापस -ENOMEM;

	i = 0;
	strlist__क्रम_each_entry(node, entry->tevlist) अणु
		tev = &(*tevs)[i++];
		ret = parse_probe_trace_command(node->s, tev);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस i;
पूर्ण

/* For the kernel probe caches, pass target = शून्य or DSO__NAME_KALLSYMS */
अटल पूर्णांक probe_cache__खोलो(काष्ठा probe_cache *pcache, स्थिर अक्षर *target,
			     काष्ठा nsinfo *nsi)
अणु
	अक्षर cpath[PATH_MAX];
	अक्षर sbuildid[SBUILD_ID_SIZE];
	अक्षर *dir_name = शून्य;
	bool is_kallsyms = false;
	पूर्णांक ret, fd;
	काष्ठा nscookie nsc;

	अगर (target && build_id_cache__cached(target)) अणु
		/* This is a cached buildid */
		strlcpy(sbuildid, target, SBUILD_ID_SIZE);
		dir_name = build_id_cache__linkname(sbuildid, शून्य, 0);
		जाओ found;
	पूर्ण

	अगर (!target || !म_भेद(target, DSO__NAME_KALLSYMS)) अणु
		target = DSO__NAME_KALLSYMS;
		is_kallsyms = true;
		ret = sysfs__प्र_लिखो_build_id("/", sbuildid);
	पूर्ण अन्यथा अणु
		nsinfo__mountns_enter(nsi, &nsc);
		ret = filename__प्र_लिखो_build_id(target, sbuildid);
		nsinfo__mountns_निकास(&nsc);
	पूर्ण

	अगर (ret < 0) अणु
		pr_debug("Failed to get build-id from %s.\n", target);
		वापस ret;
	पूर्ण

	/* If we have no buildid cache, make it */
	अगर (!build_id_cache__cached(sbuildid)) अणु
		ret = build_id_cache__add_s(sbuildid, target, nsi,
					    is_kallsyms, शून्य);
		अगर (ret < 0) अणु
			pr_debug("Failed to add build-id cache: %s\n", target);
			वापस ret;
		पूर्ण
	पूर्ण

	dir_name = build_id_cache__cachedir(sbuildid, target, nsi, is_kallsyms,
					    false);
found:
	अगर (!dir_name) अणु
		pr_debug("Failed to get cache from %s\n", target);
		वापस -ENOMEM;
	पूर्ण

	snम_लिखो(cpath, PATH_MAX, "%s/probes", dir_name);
	fd = खोलो(cpath, O_CREAT | O_RDWR, 0644);
	अगर (fd < 0)
		pr_debug("Failed to open cache(%d): %s\n", fd, cpath);
	मुक्त(dir_name);
	pcache->fd = fd;

	वापस fd;
पूर्ण

अटल पूर्णांक probe_cache__load(काष्ठा probe_cache *pcache)
अणु
	काष्ठा probe_cache_entry *entry = शून्य;
	अक्षर buf[MAX_CMDLEN], *p;
	पूर्णांक ret = 0, fddup;
	खाता *fp;

	fddup = dup(pcache->fd);
	अगर (fddup < 0)
		वापस -त्रुटि_सं;
	fp = fकरोpen(fddup, "r");
	अगर (!fp) अणु
		बंद(fddup);
		वापस -EINVAL;
	पूर्ण

	जबतक (!ख_पूर्ण(fp)) अणु
		अगर (!ख_माला_लो(buf, MAX_CMDLEN, fp))
			अवरोध;
		p = म_अक्षर(buf, '\n');
		अगर (p)
			*p = '\0';
		/* #perf_probe_event or %sdt_event */
		अगर (buf[0] == '#' || buf[0] == '%') अणु
			entry = probe_cache_entry__new(शून्य);
			अगर (!entry) अणु
				ret = -ENOMEM;
				जाओ out;
			पूर्ण
			अगर (buf[0] == '%')
				entry->sdt = true;
			entry->spev = strdup(buf + 1);
			अगर (entry->spev)
				ret = parse_perf_probe_command(buf + 1,
								&entry->pev);
			अन्यथा
				ret = -ENOMEM;
			अगर (ret < 0) अणु
				probe_cache_entry__delete(entry);
				जाओ out;
			पूर्ण
			list_add_tail(&entry->node, &pcache->entries);
		पूर्ण अन्यथा अणु	/* trace_probe_event */
			अगर (!entry) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			ret = strlist__add(entry->tevlist, buf);
			अगर (ret == -ENOMEM) अणु
				pr_err("strlist__add failed with -ENOMEM\n");
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	ख_बंद(fp);
	वापस ret;
पूर्ण

अटल काष्ठा probe_cache *probe_cache__alloc(व्योम)
अणु
	काष्ठा probe_cache *pcache = zalloc(माप(*pcache));

	अगर (pcache) अणु
		INIT_LIST_HEAD(&pcache->entries);
		pcache->fd = -EINVAL;
	पूर्ण
	वापस pcache;
पूर्ण

व्योम probe_cache__purge(काष्ठा probe_cache *pcache)
अणु
	काष्ठा probe_cache_entry *entry, *n;

	list_क्रम_each_entry_safe(entry, n, &pcache->entries, node) अणु
		list_del_init(&entry->node);
		probe_cache_entry__delete(entry);
	पूर्ण
पूर्ण

व्योम probe_cache__delete(काष्ठा probe_cache *pcache)
अणु
	अगर (!pcache)
		वापस;

	probe_cache__purge(pcache);
	अगर (pcache->fd > 0)
		बंद(pcache->fd);
	मुक्त(pcache);
पूर्ण

काष्ठा probe_cache *probe_cache__new(स्थिर अक्षर *target, काष्ठा nsinfo *nsi)
अणु
	काष्ठा probe_cache *pcache = probe_cache__alloc();
	पूर्णांक ret;

	अगर (!pcache)
		वापस शून्य;

	ret = probe_cache__खोलो(pcache, target, nsi);
	अगर (ret < 0) अणु
		pr_debug("Cache open error: %d\n", ret);
		जाओ out_err;
	पूर्ण

	ret = probe_cache__load(pcache);
	अगर (ret < 0) अणु
		pr_debug("Cache read error: %d\n", ret);
		जाओ out_err;
	पूर्ण

	वापस pcache;

out_err:
	probe_cache__delete(pcache);
	वापस शून्य;
पूर्ण

अटल bool streql(स्थिर अक्षर *a, स्थिर अक्षर *b)
अणु
	अगर (a == b)
		वापस true;

	अगर (!a || !b)
		वापस false;

	वापस !म_भेद(a, b);
पूर्ण

काष्ठा probe_cache_entry *
probe_cache__find(काष्ठा probe_cache *pcache, काष्ठा perf_probe_event *pev)
अणु
	काष्ठा probe_cache_entry *entry = शून्य;
	अक्षर *cmd = synthesize_perf_probe_command(pev);

	अगर (!cmd)
		वापस शून्य;

	क्रम_each_probe_cache_entry(entry, pcache) अणु
		अगर (pev->sdt) अणु
			अगर (entry->pev.event &&
			    streql(entry->pev.event, pev->event) &&
			    (!pev->group ||
			     streql(entry->pev.group, pev->group)))
				जाओ found;

			जारी;
		पूर्ण
		/* Hit अगर same event name or same command-string */
		अगर ((pev->event &&
		     (streql(entry->pev.group, pev->group) &&
		      streql(entry->pev.event, pev->event))) ||
		    (!म_भेद(entry->spev, cmd)))
			जाओ found;
	पूर्ण
	entry = शून्य;

found:
	मुक्त(cmd);
	वापस entry;
पूर्ण

काष्ठा probe_cache_entry *
probe_cache__find_by_name(काष्ठा probe_cache *pcache,
			  स्थिर अक्षर *group, स्थिर अक्षर *event)
अणु
	काष्ठा probe_cache_entry *entry = शून्य;

	क्रम_each_probe_cache_entry(entry, pcache) अणु
		/* Hit अगर same event name or same command-string */
		अगर (streql(entry->pev.group, group) &&
		    streql(entry->pev.event, event))
			जाओ found;
	पूर्ण
	entry = शून्य;

found:
	वापस entry;
पूर्ण

पूर्णांक probe_cache__add_entry(काष्ठा probe_cache *pcache,
			   काष्ठा perf_probe_event *pev,
			   काष्ठा probe_trace_event *tevs, पूर्णांक ntevs)
अणु
	काष्ठा probe_cache_entry *entry = शून्य;
	अक्षर *command;
	पूर्णांक i, ret = 0;

	अगर (!pcache || !pev || !tevs || ntevs <= 0) अणु
		ret = -EINVAL;
		जाओ out_err;
	पूर्ण

	/* Remove old cache entry */
	entry = probe_cache__find(pcache, pev);
	अगर (entry) अणु
		list_del_init(&entry->node);
		probe_cache_entry__delete(entry);
	पूर्ण

	ret = -ENOMEM;
	entry = probe_cache_entry__new(pev);
	अगर (!entry)
		जाओ out_err;

	क्रम (i = 0; i < ntevs; i++) अणु
		अगर (!tevs[i].poपूर्णांक.symbol)
			जारी;

		command = synthesize_probe_trace_command(&tevs[i]);
		अगर (!command)
			जाओ out_err;
		ret = strlist__add(entry->tevlist, command);
		अगर (ret == -ENOMEM) अणु
			pr_err("strlist__add failed with -ENOMEM\n");
			जाओ out_err;
		पूर्ण

		मुक्त(command);
	पूर्ण
	list_add_tail(&entry->node, &pcache->entries);
	pr_debug("Added probe cache: %d\n", ntevs);
	वापस 0;

out_err:
	pr_debug("Failed to add probe caches\n");
	probe_cache_entry__delete(entry);
	वापस ret;
पूर्ण

#अगर_घोषित HAVE_GELF_GETNOTE_SUPPORT
अटल अचिन्हित दीर्घ दीर्घ sdt_note__get_addr(काष्ठा sdt_note *note)
अणु
	वापस note->bit32 ?
		(अचिन्हित दीर्घ दीर्घ)note->addr.a32[SDT_NOTE_IDX_LOC] :
		(अचिन्हित दीर्घ दीर्घ)note->addr.a64[SDT_NOTE_IDX_LOC];
पूर्ण

अटल अचिन्हित दीर्घ दीर्घ sdt_note__get_ref_ctr_offset(काष्ठा sdt_note *note)
अणु
	वापस note->bit32 ?
		(अचिन्हित दीर्घ दीर्घ)note->addr.a32[SDT_NOTE_IDX_REFCTR] :
		(अचिन्हित दीर्घ दीर्घ)note->addr.a64[SDT_NOTE_IDX_REFCTR];
पूर्ण

अटल स्थिर अक्षर * स्थिर type_to_suffix[] = अणु
	":s64", "", "", "", ":s32", "", ":s16", ":s8",
	"", ":u8", ":u16", "", ":u32", "", "", "", ":u64"
पूर्ण;

/*
 * Isolate the string number and convert it पूर्णांकo a decimal value;
 * this will be an index to get suffix of the uprobe name (defining
 * the type)
 */
अटल पूर्णांक sdt_arg_parse_size(अक्षर *n_ptr, स्थिर अक्षर **suffix)
अणु
	दीर्घ type_idx;

	type_idx = म_से_दीर्घ(n_ptr, शून्य, 10);
	अगर (type_idx < -8 || type_idx > 8) अणु
		pr_debug4("Failed to get a valid sdt type\n");
		वापस -1;
	पूर्ण

	*suffix = type_to_suffix[type_idx + 8];
	वापस 0;
पूर्ण

अटल पूर्णांक synthesize_sdt_probe_arg(काष्ठा strbuf *buf, पूर्णांक i, स्थिर अक्षर *arg)
अणु
	अक्षर *op, *desc = strdup(arg), *new_op = शून्य;
	स्थिर अक्षर *suffix = "";
	पूर्णांक ret = -1;

	अगर (desc == शून्य) अणु
		pr_debug4("Allocation error\n");
		वापस ret;
	पूर्ण

	/*
	 * Argument is in N@OP क्रमmat. N is size of the argument and OP is
	 * the actual assembly opeअक्रम. N can be omitted; in that हाल
	 * argument is just OP(without @).
	 */
	op = म_अक्षर(desc, '@');
	अगर (op) अणु
		op[0] = '\0';
		op++;

		अगर (sdt_arg_parse_size(desc, &suffix))
			जाओ error;
	पूर्ण अन्यथा अणु
		op = desc;
	पूर्ण

	ret = arch_sdt_arg_parse_op(op, &new_op);

	अगर (ret < 0)
		जाओ error;

	अगर (ret == SDT_ARG_VALID) अणु
		ret = strbuf_addf(buf, " arg%d=%s%s", i + 1, new_op, suffix);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	ret = 0;
error:
	मुक्त(desc);
	मुक्त(new_op);
	वापस ret;
पूर्ण

अटल अक्षर *synthesize_sdt_probe_command(काष्ठा sdt_note *note,
					स्थिर अक्षर *pathname,
					स्थिर अक्षर *sdtgrp)
अणु
	काष्ठा strbuf buf;
	अक्षर *ret = शून्य;
	पूर्णांक i, args_count, err;
	अचिन्हित दीर्घ दीर्घ ref_ctr_offset;
	अक्षर *arg;
	पूर्णांक arg_idx = 0;

	अगर (strbuf_init(&buf, 32) < 0)
		वापस शून्य;

	err = strbuf_addf(&buf, "p:%s/%s %s:0x%llx",
			sdtgrp, note->name, pathname,
			sdt_note__get_addr(note));

	ref_ctr_offset = sdt_note__get_ref_ctr_offset(note);
	अगर (ref_ctr_offset && err >= 0)
		err = strbuf_addf(&buf, "(0x%llx)", ref_ctr_offset);

	अगर (err < 0)
		जाओ error;

	अगर (!note->args)
		जाओ out;

	अगर (note->args) अणु
		अक्षर **args = argv_split(note->args, &args_count);

		अगर (args == शून्य)
			जाओ error;

		क्रम (i = 0; i < args_count; ) अणु
			/*
			 * FIXUP: Arm64 ELF section '.note.stapsdt' uses string
			 * क्रमmat "-4@[sp, NUM]" अगर a probe is to access data in
			 * the stack, e.g. below is an example क्रम the SDT
			 * Arguments:
			 *
			 *   Arguments: -4@[sp, 12] -4@[sp, 8] -4@[sp, 4]
			 *
			 * Since the string पूर्णांकroduces an extra space अक्षरacter
			 * in the middle of square brackets, the argument is
			 * भागided पूर्णांकo two items.  Fixup क्रम this हाल, अगर an
			 * item contains sub string "[sp,", need to concatenate
			 * the two items.
			 */
			अगर (म_माला(args[i], "[sp,") && (i+1) < args_count) अणु
				err = aप्र_लिखो(&arg, "%s %s", args[i], args[i+1]);
				i += 2;
			पूर्ण अन्यथा अणु
				err = aप्र_लिखो(&arg, "%s", args[i]);
				i += 1;
			पूर्ण

			/* Failed to allocate memory */
			अगर (err < 0) अणु
				argv_मुक्त(args);
				जाओ error;
			पूर्ण

			अगर (synthesize_sdt_probe_arg(&buf, arg_idx, arg) < 0) अणु
				मुक्त(arg);
				argv_मुक्त(args);
				जाओ error;
			पूर्ण

			मुक्त(arg);
			arg_idx++;
		पूर्ण

		argv_मुक्त(args);
	पूर्ण

out:
	ret = strbuf_detach(&buf, शून्य);
error:
	strbuf_release(&buf);
	वापस ret;
पूर्ण

पूर्णांक probe_cache__scan_sdt(काष्ठा probe_cache *pcache, स्थिर अक्षर *pathname)
अणु
	काष्ठा probe_cache_entry *entry = शून्य;
	काष्ठा list_head sdtlist;
	काष्ठा sdt_note *note;
	अक्षर *buf;
	अक्षर sdtgrp[64];
	पूर्णांक ret;

	INIT_LIST_HEAD(&sdtlist);
	ret = get_sdt_note_list(&sdtlist, pathname);
	अगर (ret < 0) अणु
		pr_debug4("Failed to get sdt note: %d\n", ret);
		वापस ret;
	पूर्ण
	list_क्रम_each_entry(note, &sdtlist, note_list) अणु
		ret = snम_लिखो(sdtgrp, 64, "sdt_%s", note->provider);
		अगर (ret < 0)
			अवरोध;
		/* Try to find same-name entry */
		entry = probe_cache__find_by_name(pcache, sdtgrp, note->name);
		अगर (!entry) अणु
			entry = probe_cache_entry__new(शून्य);
			अगर (!entry) अणु
				ret = -ENOMEM;
				अवरोध;
			पूर्ण
			entry->sdt = true;
			ret = aप्र_लिखो(&entry->spev, "%s:%s=%s", sdtgrp,
					note->name, note->name);
			अगर (ret < 0)
				अवरोध;
			entry->pev.event = strdup(note->name);
			entry->pev.group = strdup(sdtgrp);
			list_add_tail(&entry->node, &pcache->entries);
		पूर्ण
		buf = synthesize_sdt_probe_command(note, pathname, sdtgrp);
		अगर (!buf) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		ret = strlist__add(entry->tevlist, buf);

		मुक्त(buf);
		entry = शून्य;

		अगर (ret == -ENOMEM) अणु
			pr_err("strlist__add failed with -ENOMEM\n");
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (entry) अणु
		list_del_init(&entry->node);
		probe_cache_entry__delete(entry);
	पूर्ण
	cleanup_sdt_note_list(&sdtlist);
	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक probe_cache_entry__ग_लिखो(काष्ठा probe_cache_entry *entry, पूर्णांक fd)
अणु
	काष्ठा str_node *snode;
	काष्ठा stat st;
	काष्ठा iovec iov[3];
	स्थिर अक्षर *prefix = entry->sdt ? "%" : "#";
	पूर्णांक ret;
	/* Save stat क्रम rollback */
	ret = ख_स्थिति(fd, &st);
	अगर (ret < 0)
		वापस ret;

	pr_debug("Writing cache: %s%s\n", prefix, entry->spev);
	iov[0].iov_base = (व्योम *)prefix; iov[0].iov_len = 1;
	iov[1].iov_base = entry->spev; iov[1].iov_len = म_माप(entry->spev);
	iov[2].iov_base = (व्योम *)"\n"; iov[2].iov_len = 1;
	ret = ग_लिखोv(fd, iov, 3);
	अगर (ret < (पूर्णांक)iov[1].iov_len + 2)
		जाओ rollback;

	strlist__क्रम_each_entry(snode, entry->tevlist) अणु
		iov[0].iov_base = (व्योम *)snode->s;
		iov[0].iov_len = म_माप(snode->s);
		iov[1].iov_base = (व्योम *)"\n"; iov[1].iov_len = 1;
		ret = ग_लिखोv(fd, iov, 2);
		अगर (ret < (पूर्णांक)iov[0].iov_len + 1)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	/* Rollback to aव्योम cache file corruption */
	अगर (ret > 0)
		ret = -1;
	अगर (ftruncate(fd, st.st_size) < 0)
		ret = -2;

	वापस ret;
पूर्ण

पूर्णांक probe_cache__commit(काष्ठा probe_cache *pcache)
अणु
	काष्ठा probe_cache_entry *entry;
	पूर्णांक ret = 0;

	/* TBD: अगर we करो not update existing entries, skip it */
	ret = lseek(pcache->fd, 0, शुरू_से);
	अगर (ret < 0)
		जाओ out;

	ret = ftruncate(pcache->fd, 0);
	अगर (ret < 0)
		जाओ out;

	क्रम_each_probe_cache_entry(entry, pcache) अणु
		ret = probe_cache_entry__ग_लिखो(entry, pcache->fd);
		pr_debug("Cache committed: %d\n", ret);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल bool probe_cache_entry__compare(काष्ठा probe_cache_entry *entry,
				       काष्ठा strfilter *filter)
अणु
	अक्षर buf[128], *ptr = entry->spev;

	अगर (entry->pev.event) अणु
		snम_लिखो(buf, 128, "%s:%s", entry->pev.group, entry->pev.event);
		ptr = buf;
	पूर्ण
	वापस strfilter__compare(filter, ptr);
पूर्ण

पूर्णांक probe_cache__filter_purge(काष्ठा probe_cache *pcache,
			      काष्ठा strfilter *filter)
अणु
	काष्ठा probe_cache_entry *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, &pcache->entries, node) अणु
		अगर (probe_cache_entry__compare(entry, filter)) अणु
			pr_info("Removed cached event: %s\n", entry->spev);
			list_del_init(&entry->node);
			probe_cache_entry__delete(entry);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक probe_cache__show_entries(काष्ठा probe_cache *pcache,
				     काष्ठा strfilter *filter)
अणु
	काष्ठा probe_cache_entry *entry;

	क्रम_each_probe_cache_entry(entry, pcache) अणु
		अगर (probe_cache_entry__compare(entry, filter))
			म_लिखो("%s\n", entry->spev);
	पूर्ण
	वापस 0;
पूर्ण

/* Show all cached probes */
पूर्णांक probe_cache__show_all_caches(काष्ठा strfilter *filter)
अणु
	काष्ठा probe_cache *pcache;
	काष्ठा strlist *bidlist;
	काष्ठा str_node *nd;
	अक्षर *buf = strfilter__string(filter);

	pr_debug("list cache with filter: %s\n", buf);
	मुक्त(buf);

	bidlist = build_id_cache__list_all(true);
	अगर (!bidlist) अणु
		pr_debug("Failed to get buildids: %d\n", त्रुटि_सं);
		वापस -EINVAL;
	पूर्ण
	strlist__क्रम_each_entry(nd, bidlist) अणु
		pcache = probe_cache__new(nd->s, शून्य);
		अगर (!pcache)
			जारी;
		अगर (!list_empty(&pcache->entries)) अणु
			buf = build_id_cache__origname(nd->s);
			म_लिखो("%s (%s):\n", buf, nd->s);
			मुक्त(buf);
			probe_cache__show_entries(pcache, filter);
		पूर्ण
		probe_cache__delete(pcache);
	पूर्ण
	strlist__delete(bidlist);

	वापस 0;
पूर्ण

क्रमागत ftrace_पढ़ोme अणु
	FTRACE_README_PROBE_TYPE_X = 0,
	FTRACE_README_KRETPROBE_OFFSET,
	FTRACE_README_UPROBE_REF_CTR,
	FTRACE_README_USER_ACCESS,
	FTRACE_README_MULTIPROBE_EVENT,
	FTRACE_README_IMMEDIATE_VALUE,
	FTRACE_README_END,
पूर्ण;

अटल काष्ठा अणु
	स्थिर अक्षर *pattern;
	bool avail;
पूर्ण ftrace_पढ़ोme_table[] = अणु
#घोषणा DEFINE_TYPE(idx, pat)			\
	[idx] = अणु.pattern = pat, .avail = falseपूर्ण
	DEFINE_TYPE(FTRACE_README_PROBE_TYPE_X, "*type: * x8/16/32/64,*"),
	DEFINE_TYPE(FTRACE_README_KRETPROBE_OFFSET, "*place (kretprobe): *"),
	DEFINE_TYPE(FTRACE_README_UPROBE_REF_CTR, "*ref_ctr_offset*"),
	DEFINE_TYPE(FTRACE_README_USER_ACCESS, "*u]<offset>*"),
	DEFINE_TYPE(FTRACE_README_MULTIPROBE_EVENT, "*Create/append/*"),
	DEFINE_TYPE(FTRACE_README_IMMEDIATE_VALUE, "*\\imm-value,*"),
पूर्ण;

अटल bool scan_ftrace_पढ़ोme(क्रमागत ftrace_पढ़ोme type)
अणु
	पूर्णांक fd;
	खाता *fp;
	अक्षर *buf = शून्य;
	माप_प्रकार len = 0;
	bool ret = false;
	अटल bool scanned = false;

	अगर (scanned)
		जाओ result;

	fd = खोलो_trace_file("README", false);
	अगर (fd < 0)
		वापस ret;

	fp = fकरोpen(fd, "r");
	अगर (!fp) अणु
		बंद(fd);
		वापस ret;
	पूर्ण

	जबतक (getline(&buf, &len, fp) > 0)
		क्रम (क्रमागत ftrace_पढ़ोme i = 0; i < FTRACE_README_END; i++)
			अगर (!ftrace_पढ़ोme_table[i].avail)
				ftrace_पढ़ोme_table[i].avail =
					strglobmatch(buf, ftrace_पढ़ोme_table[i].pattern);
	scanned = true;

	ख_बंद(fp);
	मुक्त(buf);

result:
	अगर (type >= FTRACE_README_END)
		वापस false;

	वापस ftrace_पढ़ोme_table[type].avail;
पूर्ण

bool probe_type_is_available(क्रमागत probe_type type)
अणु
	अगर (type >= PROBE_TYPE_END)
		वापस false;
	अन्यथा अगर (type == PROBE_TYPE_X)
		वापस scan_ftrace_पढ़ोme(FTRACE_README_PROBE_TYPE_X);

	वापस true;
पूर्ण

bool kretprobe_offset_is_supported(व्योम)
अणु
	वापस scan_ftrace_पढ़ोme(FTRACE_README_KRETPROBE_OFFSET);
पूर्ण

bool uprobe_ref_ctr_is_supported(व्योम)
अणु
	वापस scan_ftrace_पढ़ोme(FTRACE_README_UPROBE_REF_CTR);
पूर्ण

bool user_access_is_supported(व्योम)
अणु
	वापस scan_ftrace_पढ़ोme(FTRACE_README_USER_ACCESS);
पूर्ण

bool multiprobe_event_is_supported(व्योम)
अणु
	वापस scan_ftrace_पढ़ोme(FTRACE_README_MULTIPROBE_EVENT);
पूर्ण

bool immediate_value_is_supported(व्योम)
अणु
	वापस scan_ftrace_पढ़ोme(FTRACE_README_IMMEDIATE_VALUE);
पूर्ण
