<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * build-id.c
 *
 * build-id support
 *
 * Copyright (C) 2009, 2010 Red Hat Inc.
 * Copyright (C) 2009, 2010 Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश "util.h" // lsdir(), सूची_गढ़ो_p(), rm_rf()
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश "util/copyfile.h"
#समावेश "dso.h"
#समावेश "build-id.h"
#समावेश "event.h"
#समावेश "namespaces.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश "thread.h"
#समावेश <linux/kernel.h>
#समावेश "debug.h"
#समावेश "session.h"
#समावेश "tool.h"
#समावेश "header.h"
#समावेश "vdso.h"
#समावेश "path.h"
#समावेश "probe-file.h"
#समावेश "strlist.h"

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
#समावेश <elfutils/debuginfod.h>
#पूर्ण_अगर

#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>
#समावेश <linux/माला.स>
#समावेश <यंत्र/bug.h>

अटल bool no_buildid_cache;

पूर्णांक build_id__mark_dso_hit(काष्ठा perf_tool *tool __maybe_unused,
			   जोड़ perf_event *event,
			   काष्ठा perf_sample *sample,
			   काष्ठा evsel *evsel __maybe_unused,
			   काष्ठा machine *machine)
अणु
	काष्ठा addr_location al;
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid,
							sample->tid);

	अगर (thपढ़ो == शून्य) अणु
		pr_err("problem processing %d event, skipping it.\n",
			event->header.type);
		वापस -1;
	पूर्ण

	अगर (thपढ़ो__find_map(thपढ़ो, sample->cpumode, sample->ip, &al))
		al.map->dso->hit = 1;

	thपढ़ो__put(thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_event__निकास_del_thपढ़ो(काष्ठा perf_tool *tool __maybe_unused,
				       जोड़ perf_event *event,
				       काष्ठा perf_sample *sample
				       __maybe_unused,
				       काष्ठा machine *machine)
अणु
	काष्ठा thपढ़ो *thपढ़ो = machine__findnew_thपढ़ो(machine,
							event->विभाजन.pid,
							event->विभाजन.tid);

	dump_म_लिखो("(%d:%d):(%d:%d)\n", event->विभाजन.pid, event->विभाजन.tid,
		    event->विभाजन.ppid, event->विभाजन.ptid);

	अगर (thपढ़ो) अणु
		machine__हटाओ_thपढ़ो(machine, thपढ़ो);
		thपढ़ो__put(thपढ़ो);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा perf_tool build_id__mark_dso_hit_ops = अणु
	.sample	= build_id__mark_dso_hit,
	.mmap	= perf_event__process_mmap,
	.mmap2	= perf_event__process_mmap2,
	.विभाजन	= perf_event__process_विभाजन,
	.निकास	= perf_event__निकास_del_thपढ़ो,
	.attr		 = perf_event__process_attr,
	.build_id	 = perf_event__process_build_id,
	.ordered_events	 = true,
पूर्ण;

पूर्णांक build_id__प्र_लिखो(स्थिर काष्ठा build_id *build_id, अक्षर *bf)
अणु
	अक्षर *bid = bf;
	स्थिर u8 *raw = build_id->data;
	माप_प्रकार i;

	bf[0] = 0x0;

	क्रम (i = 0; i < build_id->size; ++i) अणु
		प्र_लिखो(bid, "%02x", *raw);
		++raw;
		bid += 2;
	पूर्ण

	वापस (bid - bf) + 1;
पूर्ण

पूर्णांक sysfs__प्र_लिखो_build_id(स्थिर अक्षर *root_dir, अक्षर *sbuild_id)
अणु
	अक्षर notes[PATH_MAX];
	काष्ठा build_id bid;
	पूर्णांक ret;

	अगर (!root_dir)
		root_dir = "";

	scnम_लिखो(notes, माप(notes), "%s/sys/kernel/notes", root_dir);

	ret = sysfs__पढ़ो_build_id(notes, &bid);
	अगर (ret < 0)
		वापस ret;

	वापस build_id__प्र_लिखो(&bid, sbuild_id);
पूर्ण

पूर्णांक filename__प्र_लिखो_build_id(स्थिर अक्षर *pathname, अक्षर *sbuild_id)
अणु
	काष्ठा build_id bid;
	पूर्णांक ret;

	ret = filename__पढ़ो_build_id(pathname, &bid);
	अगर (ret < 0)
		वापस ret;

	वापस build_id__प्र_लिखो(&bid, sbuild_id);
पूर्ण

/* asnम_लिखो consolidates aप्र_लिखो and snम_लिखो */
अटल पूर्णांक asnम_लिखो(अक्षर **strp, माप_प्रकार size, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;
	पूर्णांक ret;

	अगर (!strp)
		वापस -EINVAL;

	बहु_शुरू(ap, fmt);
	अगर (*strp)
		ret = vsnम_लिखो(*strp, size, fmt, ap);
	अन्यथा
		ret = vaप्र_लिखो(strp, fmt, ap);
	बहु_पूर्ण(ap);

	वापस ret;
पूर्ण

अक्षर *build_id_cache__kallsyms_path(स्थिर अक्षर *sbuild_id, अक्षर *bf,
				    माप_प्रकार size)
अणु
	bool retry_old = true;

	snम_लिखो(bf, size, "%s/%s/%s/kallsyms",
		 buildid_dir, DSO__NAME_KALLSYMS, sbuild_id);
retry:
	अगर (!access(bf, F_OK))
		वापस bf;
	अगर (retry_old) अणु
		/* Try old style kallsyms cache */
		snम_लिखो(bf, size, "%s/%s/%s",
			 buildid_dir, DSO__NAME_KALLSYMS, sbuild_id);
		retry_old = false;
		जाओ retry;
	पूर्ण

	वापस शून्य;
पूर्ण

अक्षर *build_id_cache__linkname(स्थिर अक्षर *sbuild_id, अक्षर *bf, माप_प्रकार size)
अणु
	अक्षर *पंचांगp = bf;
	पूर्णांक ret = asnम_लिखो(&bf, size, "%s/.build-id/%.2s/%s", buildid_dir,
			    sbuild_id, sbuild_id + 2);
	अगर (ret < 0 || (पंचांगp && size < (अचिन्हित पूर्णांक)ret))
		वापस शून्य;
	वापस bf;
पूर्ण

/* The caller is responsible to मुक्त the वापसed buffer. */
अक्षर *build_id_cache__origname(स्थिर अक्षर *sbuild_id)
अणु
	अक्षर *linkname;
	अक्षर buf[PATH_MAX];
	अक्षर *ret = शून्य, *p;
	माप_प्रकार offs = 5;	/* == म_माप("../..") */
	sमाप_प्रकार len;

	linkname = build_id_cache__linkname(sbuild_id, शून्य, 0);
	अगर (!linkname)
		वापस शून्य;

	len = पढ़ोlink(linkname, buf, माप(buf) - 1);
	अगर (len <= 0)
		जाओ out;
	buf[len] = '\0';

	/* The link should be "../..<origpath>/<sbuild_id>" */
	p = म_खोजप(buf, '/');	/* Cut off the "/<sbuild_id>" */
	अगर (p && (p > buf + offs)) अणु
		*p = '\0';
		अगर (buf[offs + 1] == '[')
			offs++;	/*
				 * This is a DSO name, like [kernel.kallsyms].
				 * Skip the first '/', since this is not the
				 * cache of a regular file.
				 */
		ret = strdup(buf + offs);	/* Skip "../..[/]" */
	पूर्ण
out:
	मुक्त(linkname);
	वापस ret;
पूर्ण

/* Check अगर the given build_id cache is valid on current running प्रणाली */
अटल bool build_id_cache__valid_id(अक्षर *sbuild_id)
अणु
	अक्षर real_sbuild_id[SBUILD_ID_SIZE] = "";
	अक्षर *pathname;
	पूर्णांक ret = 0;
	bool result = false;

	pathname = build_id_cache__origname(sbuild_id);
	अगर (!pathname)
		वापस false;

	अगर (!म_भेद(pathname, DSO__NAME_KALLSYMS))
		ret = sysfs__प्र_लिखो_build_id("/", real_sbuild_id);
	अन्यथा अगर (pathname[0] == '/')
		ret = filename__प्र_लिखो_build_id(pathname, real_sbuild_id);
	अन्यथा
		ret = -EINVAL;	/* Should we support other special DSO cache? */
	अगर (ret >= 0)
		result = (म_भेद(sbuild_id, real_sbuild_id) == 0);
	मुक्त(pathname);

	वापस result;
पूर्ण

अटल स्थिर अक्षर *build_id_cache__basename(bool is_kallsyms, bool is_vdso,
					    bool is_debug)
अणु
	वापस is_kallsyms ? "kallsyms" : (is_vdso ? "vdso" : (is_debug ?
	    "debug" : "elf"));
पूर्ण

अक्षर *__dso__build_id_filename(स्थिर काष्ठा dso *dso, अक्षर *bf, माप_प्रकार size,
			       bool is_debug, bool is_kallsyms)
अणु
	bool is_vdso = dso__is_vdso((काष्ठा dso *)dso);
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	अक्षर *linkname;
	bool alloc = (bf == शून्य);
	पूर्णांक ret;

	अगर (!dso->has_build_id)
		वापस शून्य;

	build_id__प्र_लिखो(&dso->bid, sbuild_id);
	linkname = build_id_cache__linkname(sbuild_id, शून्य, 0);
	अगर (!linkname)
		वापस शून्य;

	/* Check अगर old style build_id cache */
	अगर (is_regular_file(linkname))
		ret = asnम_लिखो(&bf, size, "%s", linkname);
	अन्यथा
		ret = asnम_लिखो(&bf, size, "%s/%s", linkname,
			 build_id_cache__basename(is_kallsyms, is_vdso,
						  is_debug));
	अगर (ret < 0 || (!alloc && size < (अचिन्हित पूर्णांक)ret))
		bf = शून्य;
	मुक्त(linkname);

	वापस bf;
पूर्ण

अक्षर *dso__build_id_filename(स्थिर काष्ठा dso *dso, अक्षर *bf, माप_प्रकार size,
			     bool is_debug)
अणु
	bool is_kallsyms = dso__is_kallsyms((काष्ठा dso *)dso);

	वापस __dso__build_id_filename(dso, bf, size, is_debug, is_kallsyms);
पूर्ण

#घोषणा dsos__क्रम_each_with_build_id(pos, head)	\
	list_क्रम_each_entry(pos, head, node)	\
		अगर (!pos->has_build_id)		\
			जारी;		\
		अन्यथा

अटल पूर्णांक ग_लिखो_buildid(स्थिर अक्षर *name, माप_प्रकार name_len, काष्ठा build_id *bid,
			 pid_t pid, u16 misc, काष्ठा feat_fd *fd)
अणु
	पूर्णांक err;
	काष्ठा perf_record_header_build_id b;
	माप_प्रकार len;

	len = name_len + 1;
	len = PERF_ALIGN(len, NAME_ALIGN);

	स_रखो(&b, 0, माप(b));
	स_नकल(&b.data, bid->data, bid->size);
	b.size = (u8) bid->size;
	misc |= PERF_RECORD_MISC_BUILD_ID_SIZE;
	b.pid = pid;
	b.header.misc = misc;
	b.header.size = माप(b) + len;

	err = करो_ग_लिखो(fd, &b, माप(b));
	अगर (err < 0)
		वापस err;

	वापस ग_लिखो_padded(fd, name, name_len + 1, len);
पूर्ण

अटल पूर्णांक machine__ग_लिखो_buildid_table(काष्ठा machine *machine,
					काष्ठा feat_fd *fd)
अणु
	पूर्णांक err = 0;
	काष्ठा dso *pos;
	u16 kmisc = PERF_RECORD_MISC_KERNEL,
	    umisc = PERF_RECORD_MISC_USER;

	अगर (!machine__is_host(machine)) अणु
		kmisc = PERF_RECORD_MISC_GUEST_KERNEL;
		umisc = PERF_RECORD_MISC_GUEST_USER;
	पूर्ण

	dsos__क्रम_each_with_build_id(pos, &machine->dsos.head) अणु
		स्थिर अक्षर *name;
		माप_प्रकार name_len;
		bool in_kernel = false;

		अगर (!pos->hit && !dso__is_vdso(pos))
			जारी;

		अगर (dso__is_vdso(pos)) अणु
			name = pos->लघु_name;
			name_len = pos->लघु_name_len;
		पूर्ण अन्यथा अगर (dso__is_kcore(pos)) अणु
			name = machine->mmap_name;
			name_len = म_माप(name);
		पूर्ण अन्यथा अणु
			name = pos->दीर्घ_name;
			name_len = pos->दीर्घ_name_len;
		पूर्ण

		in_kernel = pos->kernel ||
				is_kernel_module(name,
					PERF_RECORD_MISC_CPUMODE_UNKNOWN);
		err = ग_लिखो_buildid(name, name_len, &pos->bid, machine->pid,
				    in_kernel ? kmisc : umisc, fd);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक perf_session__ग_लिखो_buildid_table(काष्ठा perf_session *session,
				      काष्ठा feat_fd *fd)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक err = machine__ग_लिखो_buildid_table(&session->machines.host, fd);

	अगर (err)
		वापस err;

	क्रम (nd = rb_first_cached(&session->machines.guests); nd;
	     nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);
		err = machine__ग_लिखो_buildid_table(pos, fd);
		अगर (err)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __dsos__hit_all(काष्ठा list_head *head)
अणु
	काष्ठा dso *pos;

	list_क्रम_each_entry(pos, head, node)
		pos->hit = true;

	वापस 0;
पूर्ण

अटल पूर्णांक machine__hit_all_dsos(काष्ठा machine *machine)
अणु
	वापस __dsos__hit_all(&machine->dsos.head);
पूर्ण

पूर्णांक dsos__hit_all(काष्ठा perf_session *session)
अणु
	काष्ठा rb_node *nd;
	पूर्णांक err;

	err = machine__hit_all_dsos(&session->machines.host);
	अगर (err)
		वापस err;

	क्रम (nd = rb_first_cached(&session->machines.guests); nd;
	     nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);

		err = machine__hit_all_dsos(pos);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम disable_buildid_cache(व्योम)
अणु
	no_buildid_cache = true;
पूर्ण

अटल bool lsdir_bid_head_filter(स्थिर अक्षर *name __maybe_unused,
				  काष्ठा dirent *d)
अणु
	वापस (म_माप(d->d_name) == 2) &&
		है_षष्ठादशक(d->d_name[0]) && है_षष्ठादशक(d->d_name[1]);
पूर्ण

अटल bool lsdir_bid_tail_filter(स्थिर अक्षर *name __maybe_unused,
				  काष्ठा dirent *d)
अणु
	पूर्णांक i = 0;
	जबतक (है_षष्ठादशक(d->d_name[i]) && i < SBUILD_ID_SIZE - 3)
		i++;
	वापस (i >= SBUILD_ID_MIN_SIZE - 3) && (i <= SBUILD_ID_SIZE - 3) &&
		(d->d_name[i] == '\0');
पूर्ण

काष्ठा strlist *build_id_cache__list_all(bool valiकरोnly)
अणु
	काष्ठा strlist *toplist, *linklist = शून्य, *bidlist;
	काष्ठा str_node *nd, *nd2;
	अक्षर *topdir, *linkdir = शून्य;
	अक्षर sbuild_id[SBUILD_ID_SIZE];

	/* क्रम filename__ functions */
	अगर (valiकरोnly)
		symbol__init(शून्य);

	/* Open the top-level directory */
	अगर (aप्र_लिखो(&topdir, "%s/.build-id/", buildid_dir) < 0)
		वापस शून्य;

	bidlist = strlist__new(शून्य, शून्य);
	अगर (!bidlist)
		जाओ out;

	toplist = lsdir(topdir, lsdir_bid_head_filter);
	अगर (!toplist) अणु
		pr_debug("Error in lsdir(%s): %d\n", topdir, त्रुटि_सं);
		/* If there is no buildid cache, वापस an empty list */
		अगर (त्रुटि_सं == ENOENT)
			जाओ out;
		जाओ err_out;
	पूर्ण

	strlist__क्रम_each_entry(nd, toplist) अणु
		अगर (aप्र_लिखो(&linkdir, "%s/%s", topdir, nd->s) < 0)
			जाओ err_out;
		/* Open the lower-level directory */
		linklist = lsdir(linkdir, lsdir_bid_tail_filter);
		अगर (!linklist) अणु
			pr_debug("Error in lsdir(%s): %d\n", linkdir, त्रुटि_सं);
			जाओ err_out;
		पूर्ण
		strlist__क्रम_each_entry(nd2, linklist) अणु
			अगर (snम_लिखो(sbuild_id, SBUILD_ID_SIZE, "%s%s",
				     nd->s, nd2->s) > SBUILD_ID_SIZE - 1)
				जाओ err_out;
			अगर (valiकरोnly && !build_id_cache__valid_id(sbuild_id))
				जारी;
			अगर (strlist__add(bidlist, sbuild_id) < 0)
				जाओ err_out;
		पूर्ण
		strlist__delete(linklist);
		zमुक्त(&linkdir);
	पूर्ण

out_मुक्त:
	strlist__delete(toplist);
out:
	मुक्त(topdir);

	वापस bidlist;

err_out:
	strlist__delete(linklist);
	zमुक्त(&linkdir);
	strlist__delete(bidlist);
	bidlist = शून्य;
	जाओ out_मुक्त;
पूर्ण

अटल bool str_is_build_id(स्थिर अक्षर *maybe_sbuild_id, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (!है_षष्ठादशक(maybe_sbuild_id[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Return the valid complete build-id */
अक्षर *build_id_cache__complement(स्थिर अक्षर *incomplete_sbuild_id)
अणु
	काष्ठा strlist *bidlist;
	काष्ठा str_node *nd, *cand = शून्य;
	अक्षर *sbuild_id = शून्य;
	माप_प्रकार len = म_माप(incomplete_sbuild_id);

	अगर (len >= SBUILD_ID_SIZE ||
	    !str_is_build_id(incomplete_sbuild_id, len))
		वापस शून्य;

	bidlist = build_id_cache__list_all(true);
	अगर (!bidlist)
		वापस शून्य;

	strlist__क्रम_each_entry(nd, bidlist) अणु
		अगर (म_भेदन(nd->s, incomplete_sbuild_id, len) != 0)
			जारी;
		अगर (cand) अणु	/* Error: There are more than 2 candidates. */
			cand = शून्य;
			अवरोध;
		पूर्ण
		cand = nd;
	पूर्ण
	अगर (cand)
		sbuild_id = strdup(cand->s);
	strlist__delete(bidlist);

	वापस sbuild_id;
पूर्ण

अक्षर *build_id_cache__cachedir(स्थिर अक्षर *sbuild_id, स्थिर अक्षर *name,
			       काष्ठा nsinfo *nsi, bool is_kallsyms,
			       bool is_vdso)
अणु
	अक्षर *realname = (अक्षर *)name, *filename;
	bool slash = is_kallsyms || is_vdso;

	अगर (!slash) अणु
		realname = nsinfo__realpath(name, nsi);
		अगर (!realname)
			वापस शून्य;
	पूर्ण

	अगर (aप्र_लिखो(&filename, "%s%s%s%s%s", buildid_dir, slash ? "/" : "",
		     is_vdso ? DSO__NAME_VDSO : realname,
		     sbuild_id ? "/" : "", sbuild_id ?: "") < 0)
		filename = शून्य;

	अगर (!slash)
		मुक्त(realname);

	वापस filename;
पूर्ण

पूर्णांक build_id_cache__list_build_ids(स्थिर अक्षर *pathname, काष्ठा nsinfo *nsi,
				   काष्ठा strlist **result)
अणु
	अक्षर *dir_name;
	पूर्णांक ret = 0;

	dir_name = build_id_cache__cachedir(शून्य, pathname, nsi, false, false);
	अगर (!dir_name)
		वापस -ENOMEM;

	*result = lsdir(dir_name, lsdir_no_करोt_filter);
	अगर (!*result)
		ret = -त्रुटि_सं;
	मुक्त(dir_name);

	वापस ret;
पूर्ण

#अगर defined(HAVE_LIBELF_SUPPORT) && defined(HAVE_GELF_GETNOTE_SUPPORT)
अटल पूर्णांक build_id_cache__add_sdt_cache(स्थिर अक्षर *sbuild_id,
					  स्थिर अक्षर *realname,
					  काष्ठा nsinfo *nsi)
अणु
	काष्ठा probe_cache *cache;
	पूर्णांक ret;
	काष्ठा nscookie nsc;

	cache = probe_cache__new(sbuild_id, nsi);
	अगर (!cache)
		वापस -1;

	nsinfo__mountns_enter(nsi, &nsc);
	ret = probe_cache__scan_sdt(cache, realname);
	nsinfo__mountns_निकास(&nsc);
	अगर (ret >= 0) अणु
		pr_debug4("Found %d SDTs in %s\n", ret, realname);
		अगर (probe_cache__commit(cache) < 0)
			ret = -1;
	पूर्ण
	probe_cache__delete(cache);
	वापस ret;
पूर्ण
#अन्यथा
#घोषणा build_id_cache__add_sdt_cache(sbuild_id, realname, nsi) (0)
#पूर्ण_अगर

अटल अक्षर *build_id_cache__find_debug(स्थिर अक्षर *sbuild_id,
					काष्ठा nsinfo *nsi)
अणु
	अक्षर *realname = शून्य;
	अक्षर *debugfile;
	काष्ठा nscookie nsc;
	माप_प्रकार len = 0;

	debugfile = सुस्मृति(1, PATH_MAX);
	अगर (!debugfile)
		जाओ out;

	len = __symbol__join_symfs(debugfile, PATH_MAX,
				   "/usr/lib/debug/.build-id/");
	snम_लिखो(debugfile + len, PATH_MAX - len, "%.2s/%s.debug", sbuild_id,
		 sbuild_id + 2);

	nsinfo__mountns_enter(nsi, &nsc);
	realname = realpath(debugfile, शून्य);
	अगर (realname && access(realname, R_OK))
		zमुक्त(&realname);
	nsinfo__mountns_निकास(&nsc);

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
        अगर (realname == शून्य) अणु
                debuginfod_client* c = debuginfod_begin();
                अगर (c != शून्य) अणु
                        पूर्णांक fd = debuginfod_find_debuginfo(c,
                                                           (स्थिर अचिन्हित अक्षर*)sbuild_id, 0,
                                                           &realname);
                        अगर (fd >= 0)
                                बंद(fd); /* retaining reference by realname */
                        debuginfod_end(c);
                पूर्ण
        पूर्ण
#पूर्ण_अगर

out:
	मुक्त(debugfile);
	वापस realname;
पूर्ण

पूर्णांक
build_id_cache__add(स्थिर अक्षर *sbuild_id, स्थिर अक्षर *name, स्थिर अक्षर *realname,
		    काष्ठा nsinfo *nsi, bool is_kallsyms, bool is_vdso)
अणु
	स्थिर माप_प्रकार size = PATH_MAX;
	अक्षर *filename = शून्य, *dir_name = शून्य, *linkname = zalloc(size), *पंचांगp;
	अक्षर *debugfile = शून्य;
	पूर्णांक err = -1;

	dir_name = build_id_cache__cachedir(sbuild_id, name, nsi, is_kallsyms,
					    is_vdso);
	अगर (!dir_name)
		जाओ out_मुक्त;

	/* Remove old style build-id cache */
	अगर (is_regular_file(dir_name))
		अगर (unlink(dir_name))
			जाओ out_मुक्त;

	अगर (सूची_गढ़ो_p(dir_name, 0755))
		जाओ out_मुक्त;

	/* Save the allocated buildid स_नाम */
	अगर (aप्र_लिखो(&filename, "%s/%s", dir_name,
		     build_id_cache__basename(is_kallsyms, is_vdso,
		     false)) < 0) अणु
		filename = शून्य;
		जाओ out_मुक्त;
	पूर्ण

	अगर (access(filename, F_OK)) अणु
		अगर (is_kallsyms) अणु
			अगर (copyfile("/proc/kallsyms", filename))
				जाओ out_मुक्त;
		पूर्ण अन्यथा अगर (nsi && nsi->need_setns) अणु
			अगर (copyfile_ns(name, filename, nsi))
				जाओ out_मुक्त;
		पूर्ण अन्यथा अगर (link(realname, filename) && त्रुटि_सं != EEXIST &&
				copyfile(name, filename))
			जाओ out_मुक्त;
	पूर्ण

	/* Some binaries are stripped, but have .debug files with their symbol
	 * table.  Check to see अगर we can locate one of those, since the elf
	 * file itself may not be very useful to users of our tools without a
	 * symtab.
	 */
	अगर (!is_kallsyms && !is_vdso &&
	    म_भेदन(".ko", name + म_माप(name) - 3, 3)) अणु
		debugfile = build_id_cache__find_debug(sbuild_id, nsi);
		अगर (debugfile) अणु
			zमुक्त(&filename);
			अगर (aप्र_लिखो(&filename, "%s/%s", dir_name,
			    build_id_cache__basename(false, false, true)) < 0) अणु
				filename = शून्य;
				जाओ out_मुक्त;
			पूर्ण
			अगर (access(filename, F_OK)) अणु
				अगर (nsi && nsi->need_setns) अणु
					अगर (copyfile_ns(debugfile, filename,
							nsi))
						जाओ out_मुक्त;
				पूर्ण अन्यथा अगर (link(debugfile, filename) &&
						त्रुटि_सं != EEXIST &&
						copyfile(debugfile, filename))
					जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!build_id_cache__linkname(sbuild_id, linkname, size))
		जाओ out_मुक्त;
	पंचांगp = म_खोजप(linkname, '/');
	*पंचांगp = '\0';

	अगर (access(linkname, X_OK) && सूची_गढ़ो_p(linkname, 0755))
		जाओ out_मुक्त;

	*पंचांगp = '/';
	पंचांगp = dir_name + म_माप(buildid_dir) - 5;
	स_नकल(पंचांगp, "../..", 5);

	अगर (symlink(पंचांगp, linkname) == 0) अणु
		err = 0;
	पूर्ण अन्यथा अगर (त्रुटि_सं == EEXIST) अणु
		अक्षर path[PATH_MAX];
		sमाप_प्रकार len;

		len = पढ़ोlink(linkname, path, माप(path) - 1);
		अगर (len <= 0) अणु
			pr_err("Cant read link: %s\n", linkname);
			जाओ out_मुक्त;
		पूर्ण
		path[len] = '\0';

		अगर (म_भेद(पंचांगp, path)) अणु
			pr_debug("build <%s> already linked to %s\n",
				 sbuild_id, linkname);
		पूर्ण
		err = 0;
	पूर्ण

	/* Update SDT cache : error is just warned */
	अगर (realname &&
	    build_id_cache__add_sdt_cache(sbuild_id, realname, nsi) < 0)
		pr_debug4("Failed to update/scan SDT cache for %s\n", realname);

out_मुक्त:
	मुक्त(filename);
	मुक्त(debugfile);
	मुक्त(dir_name);
	मुक्त(linkname);
	वापस err;
पूर्ण

पूर्णांक build_id_cache__add_s(स्थिर अक्षर *sbuild_id, स्थिर अक्षर *name,
			  काष्ठा nsinfo *nsi, bool is_kallsyms, bool is_vdso)
अणु
	अक्षर *realname = शून्य;
	पूर्णांक err = -1;

	अगर (!is_kallsyms) अणु
		अगर (!is_vdso)
			realname = nsinfo__realpath(name, nsi);
		अन्यथा
			realname = realpath(name, शून्य);
		अगर (!realname)
			जाओ out_मुक्त;
	पूर्ण

	err = build_id_cache__add(sbuild_id, name, realname, nsi, is_kallsyms, is_vdso);

out_मुक्त:
	अगर (!is_kallsyms)
		मुक्त(realname);
	वापस err;
पूर्ण

अटल पूर्णांक build_id_cache__add_b(स्थिर काष्ठा build_id *bid,
				 स्थिर अक्षर *name, काष्ठा nsinfo *nsi,
				 bool is_kallsyms, bool is_vdso)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];

	build_id__प्र_लिखो(bid, sbuild_id);

	वापस build_id_cache__add_s(sbuild_id, name, nsi, is_kallsyms,
				     is_vdso);
पूर्ण

bool build_id_cache__cached(स्थिर अक्षर *sbuild_id)
अणु
	bool ret = false;
	अक्षर *filename = build_id_cache__linkname(sbuild_id, शून्य, 0);

	अगर (filename && !access(filename, F_OK))
		ret = true;
	मुक्त(filename);

	वापस ret;
पूर्ण

पूर्णांक build_id_cache__हटाओ_s(स्थिर अक्षर *sbuild_id)
अणु
	स्थिर माप_प्रकार size = PATH_MAX;
	अक्षर *filename = zalloc(size),
	     *linkname = zalloc(size), *पंचांगp;
	पूर्णांक err = -1;

	अगर (filename == शून्य || linkname == शून्य)
		जाओ out_मुक्त;

	अगर (!build_id_cache__linkname(sbuild_id, linkname, size))
		जाओ out_मुक्त;

	अगर (access(linkname, F_OK))
		जाओ out_मुक्त;

	अगर (पढ़ोlink(linkname, filename, size - 1) < 0)
		जाओ out_मुक्त;

	अगर (unlink(linkname))
		जाओ out_मुक्त;

	/*
	 * Since the link is relative, we must make it असलolute:
	 */
	पंचांगp = म_खोजप(linkname, '/') + 1;
	snम_लिखो(पंचांगp, size - (पंचांगp - linkname), "%s", filename);

	अगर (rm_rf(linkname))
		जाओ out_मुक्त;

	err = 0;
out_मुक्त:
	मुक्त(filename);
	मुक्त(linkname);
	वापस err;
पूर्ण

अटल पूर्णांक dso__cache_build_id(काष्ठा dso *dso, काष्ठा machine *machine,
			       व्योम *priv __maybe_unused)
अणु
	bool is_kallsyms = dso__is_kallsyms(dso);
	bool is_vdso = dso__is_vdso(dso);
	स्थिर अक्षर *name = dso->दीर्घ_name;

	अगर (!dso->has_build_id)
		वापस 0;

	अगर (dso__is_kcore(dso)) अणु
		is_kallsyms = true;
		name = machine->mmap_name;
	पूर्ण
	वापस build_id_cache__add_b(&dso->bid, name, dso->nsinfo,
				     is_kallsyms, is_vdso);
पूर्ण

अटल पूर्णांक
machines__क्रम_each_dso(काष्ठा machines *machines, machine__dso_t fn, व्योम *priv)
अणु
	पूर्णांक ret = machine__क्रम_each_dso(&machines->host, fn, priv);
	काष्ठा rb_node *nd;

	क्रम (nd = rb_first_cached(&machines->guests); nd;
	     nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);

		ret |= machine__क्रम_each_dso(pos, fn, priv);
	पूर्ण
	वापस ret ? -1 : 0;
पूर्ण

पूर्णांक __perf_session__cache_build_ids(काष्ठा perf_session *session,
				    machine__dso_t fn, व्योम *priv)
अणु
	अगर (no_buildid_cache)
		वापस 0;

	अगर (सूची_गढ़ो(buildid_dir, 0755) != 0 && त्रुटि_सं != EEXIST)
		वापस -1;

	वापस machines__क्रम_each_dso(&session->machines, fn, priv) ?  -1 : 0;
पूर्ण

पूर्णांक perf_session__cache_build_ids(काष्ठा perf_session *session)
अणु
	वापस __perf_session__cache_build_ids(session, dso__cache_build_id, शून्य);
पूर्ण

अटल bool machine__पढ़ो_build_ids(काष्ठा machine *machine, bool with_hits)
अणु
	वापस __dsos__पढ़ो_build_ids(&machine->dsos.head, with_hits);
पूर्ण

bool perf_session__पढ़ो_build_ids(काष्ठा perf_session *session, bool with_hits)
अणु
	काष्ठा rb_node *nd;
	bool ret = machine__पढ़ो_build_ids(&session->machines.host, with_hits);

	क्रम (nd = rb_first_cached(&session->machines.guests); nd;
	     nd = rb_next(nd)) अणु
		काष्ठा machine *pos = rb_entry(nd, काष्ठा machine, rb_node);
		ret |= machine__पढ़ो_build_ids(pos, with_hits);
	पूर्ण

	वापस ret;
पूर्ण

व्योम build_id__init(काष्ठा build_id *bid, स्थिर u8 *data, माप_प्रकार size)
अणु
	WARN_ON(size > BUILD_ID_SIZE);
	स_नकल(bid->data, data, size);
	bid->size = size;
पूर्ण

bool build_id__is_defined(स्थिर काष्ठा build_id *bid)
अणु
	वापस bid && bid->size ? !!स_प्रथम_inv(bid->data, 0, bid->size) : false;
पूर्ण
