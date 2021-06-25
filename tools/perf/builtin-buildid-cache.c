<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * builtin-buildid-cache.c
 *
 * Builtin buildid-cache command: Manages build-id cache
 *
 * Copyright (C) 2010, Red Hat Inc.
 * Copyright (C) 2010, Arnalकरो Carvalho de Melo <acme@redhat.com>
 */
#समावेश <sys/types.h>
#समावेश <sys/समय.स>
#समावेश <समय.स>
#समावेश <dirent.h>
#समावेश <त्रुटिसं.स>
#समावेश <unistd.h>
#समावेश "builtin.h"
#समावेश "namespaces.h"
#समावेश "util/debug.h"
#समावेश "util/header.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/strlist.h"
#समावेश "util/build-id.h"
#समावेश "util/session.h"
#समावेश "util/dso.h"
#समावेश "util/symbol.h"
#समावेश "util/time-utils.h"
#समावेश "util/util.h"
#समावेश "util/probe-file.h"
#समावेश "util/config.h"
#समावेश <linux/माला.स>
#समावेश <linux/err.h>

अटल पूर्णांक build_id_cache__kcore_buildid(स्थिर अक्षर *proc_dir, अक्षर *sbuildid)
अणु
	अक्षर root_dir[PATH_MAX];
	अक्षर *p;

	strlcpy(root_dir, proc_dir, माप(root_dir));

	p = म_खोजप(root_dir, '/');
	अगर (!p)
		वापस -1;
	*p = '\0';
	वापस sysfs__प्र_लिखो_build_id(root_dir, sbuildid);
पूर्ण

अटल पूर्णांक build_id_cache__kcore_dir(अक्षर *dir, माप_प्रकार sz)
अणु
	वापस fetch_current_बारtamp(dir, sz);
पूर्ण

अटल bool same_kallsyms_reloc(स्थिर अक्षर *from_dir, अक्षर *to_dir)
अणु
	अक्षर from[PATH_MAX];
	अक्षर to[PATH_MAX];
	स्थिर अक्षर *name;
	u64 addr1 = 0, addr2 = 0;
	पूर्णांक i, err = -1;

	scnम_लिखो(from, माप(from), "%s/kallsyms", from_dir);
	scnम_लिखो(to, माप(to), "%s/kallsyms", to_dir);

	क्रम (i = 0; (name = ref_reloc_sym_names[i]) != शून्य; i++) अणु
		err = kallsyms__get_function_start(from, name, &addr1);
		अगर (!err)
			अवरोध;
	पूर्ण

	अगर (err)
		वापस false;

	अगर (kallsyms__get_function_start(to, name, &addr2))
		वापस false;

	वापस addr1 == addr2;
पूर्ण

अटल पूर्णांक build_id_cache__kcore_existing(स्थिर अक्षर *from_dir, अक्षर *to_dir,
					  माप_प्रकार to_dir_sz)
अणु
	अक्षर from[PATH_MAX];
	अक्षर to[PATH_MAX];
	अक्षर to_subdir[PATH_MAX];
	काष्ठा dirent *dent;
	पूर्णांक ret = -1;
	सूची *d;

	d = सूची_खोलो(to_dir);
	अगर (!d)
		वापस -1;

	scnम_लिखो(from, माप(from), "%s/modules", from_dir);

	जबतक (1) अणु
		dent = सूची_पढ़ो(d);
		अगर (!dent)
			अवरोध;
		अगर (dent->d_type != DT_सूची)
			जारी;
		scnम_लिखो(to, माप(to), "%s/%s/modules", to_dir,
			  dent->d_name);
		scnम_लिखो(to_subdir, माप(to_subdir), "%s/%s",
			  to_dir, dent->d_name);
		अगर (!compare_proc_modules(from, to) &&
		    same_kallsyms_reloc(from_dir, to_subdir)) अणु
			strlcpy(to_dir, to_subdir, to_dir_sz);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	बंद_सूची(d);

	वापस ret;
पूर्ण

अटल पूर्णांक build_id_cache__add_kcore(स्थिर अक्षर *filename, bool क्रमce)
अणु
	अक्षर dir[32], sbuildid[SBUILD_ID_SIZE];
	अक्षर from_dir[PATH_MAX], to_dir[PATH_MAX];
	अक्षर *p;

	strlcpy(from_dir, filename, माप(from_dir));

	p = म_खोजप(from_dir, '/');
	अगर (!p || म_भेद(p + 1, "kcore"))
		वापस -1;
	*p = '\0';

	अगर (build_id_cache__kcore_buildid(from_dir, sbuildid) < 0)
		वापस -1;

	scnम_लिखो(to_dir, माप(to_dir), "%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuildid);

	अगर (!क्रमce &&
	    !build_id_cache__kcore_existing(from_dir, to_dir, माप(to_dir))) अणु
		pr_debug("same kcore found in %s\n", to_dir);
		वापस 0;
	पूर्ण

	अगर (build_id_cache__kcore_dir(dir, माप(dir)))
		वापस -1;

	scnम_लिखो(to_dir, माप(to_dir), "%s/%s/%s/%s",
		  buildid_dir, DSO__NAME_KCORE, sbuildid, dir);

	अगर (सूची_गढ़ो_p(to_dir, 0755))
		वापस -1;

	अगर (kcore_copy(from_dir, to_dir)) अणु
		/* Remove YYYYmmddHHMMSShh directory */
		अगर (!सूची_हटाओ(to_dir)) अणु
			p = म_खोजप(to_dir, '/');
			अगर (p)
				*p = '\0';
			/* Try to हटाओ buildid directory */
			अगर (!सूची_हटाओ(to_dir)) अणु
				p = म_खोजप(to_dir, '/');
				अगर (p)
					*p = '\0';
				/* Try to हटाओ [kernel.kcore] directory */
				सूची_हटाओ(to_dir);
			पूर्ण
		पूर्ण
		वापस -1;
	पूर्ण

	pr_debug("kcore added to build-id cache directory %s\n", to_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक build_id_cache__add_file(स्थिर अक्षर *filename, काष्ठा nsinfo *nsi)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	काष्ठा build_id bid;
	पूर्णांक err;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	err = filename__पढ़ो_build_id(filename, &bid);
	nsinfo__mountns_निकास(&nsc);
	अगर (err < 0) अणु
		pr_debug("Couldn't read a build-id in %s\n", filename);
		वापस -1;
	पूर्ण

	build_id__प्र_लिखो(&bid, sbuild_id);
	err = build_id_cache__add_s(sbuild_id, filename, nsi,
				    false, false);
	pr_debug("Adding %s %s: %s\n", sbuild_id, filename,
		 err ? "FAIL" : "Ok");
	वापस err;
पूर्ण

अटल पूर्णांक build_id_cache__हटाओ_file(स्थिर अक्षर *filename, काष्ठा nsinfo *nsi)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	काष्ठा build_id bid;
	काष्ठा nscookie nsc;

	पूर्णांक err;

	nsinfo__mountns_enter(nsi, &nsc);
	err = filename__पढ़ो_build_id(filename, &bid);
	nsinfo__mountns_निकास(&nsc);
	अगर (err < 0) अणु
		pr_debug("Couldn't read a build-id in %s\n", filename);
		वापस -1;
	पूर्ण

	build_id__प्र_लिखो(&bid, sbuild_id);
	err = build_id_cache__हटाओ_s(sbuild_id);
	pr_debug("Removing %s %s: %s\n", sbuild_id, filename,
		 err ? "FAIL" : "Ok");

	वापस err;
पूर्ण

अटल पूर्णांक build_id_cache__purge_path(स्थिर अक्षर *pathname, काष्ठा nsinfo *nsi)
अणु
	काष्ठा strlist *list;
	काष्ठा str_node *pos;
	पूर्णांक err;

	err = build_id_cache__list_build_ids(pathname, nsi, &list);
	अगर (err)
		जाओ out;

	strlist__क्रम_each_entry(pos, list) अणु
		err = build_id_cache__हटाओ_s(pos->s);
		pr_debug("Removing %s %s: %s\n", pos->s, pathname,
			 err ? "FAIL" : "Ok");
		अगर (err)
			अवरोध;
	पूर्ण
	strlist__delete(list);

out:
	pr_debug("Purging %s: %s\n", pathname, err ? "FAIL" : "Ok");

	वापस err;
पूर्ण

अटल पूर्णांक build_id_cache__purge_all(व्योम)
अणु
	काष्ठा strlist *list;
	काष्ठा str_node *pos;
	पूर्णांक err = 0;
	अक्षर *buf;

	list = build_id_cache__list_all(false);
	अगर (!list) अणु
		pr_debug("Failed to get buildids: -%d\n", त्रुटि_सं);
		वापस -EINVAL;
	पूर्ण

	strlist__क्रम_each_entry(pos, list) अणु
		buf = build_id_cache__origname(pos->s);
		err = build_id_cache__हटाओ_s(pos->s);
		pr_debug("Removing %s (%s): %s\n", buf, pos->s,
			 err ? "FAIL" : "Ok");
		मुक्त(buf);
		अगर (err)
			अवरोध;
	पूर्ण
	strlist__delete(list);

	pr_debug("Purged all: %s\n", err ? "FAIL" : "Ok");
	वापस err;
पूर्ण

अटल bool dso__missing_buildid_cache(काष्ठा dso *dso, पूर्णांक parm __maybe_unused)
अणु
	अक्षर filename[PATH_MAX];
	काष्ठा build_id bid;

	अगर (dso__build_id_filename(dso, filename, माप(filename), false) &&
	    filename__पढ़ो_build_id(filename, &bid) == -1) अणु
		अगर (त्रुटि_सं == ENOENT)
			वापस false;

		pr_warning("Problems with %s file, consider removing it from the cache\n",
			   filename);
	पूर्ण अन्यथा अगर (स_भेद(dso->bid.data, bid.data, bid.size)) अणु
		pr_warning("Problems with %s file, consider removing it from the cache\n",
			   filename);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक build_id_cache__ख_लिखो_missing(काष्ठा perf_session *session, खाता *fp)
अणु
	perf_session__ख_लिखो_dsos_buildid(session, fp, dso__missing_buildid_cache, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक build_id_cache__update_file(स्थिर अक्षर *filename, काष्ठा nsinfo *nsi)
अणु
	अक्षर sbuild_id[SBUILD_ID_SIZE];
	काष्ठा build_id bid;
	काष्ठा nscookie nsc;

	पूर्णांक err;

	nsinfo__mountns_enter(nsi, &nsc);
	err = filename__पढ़ो_build_id(filename, &bid);
	nsinfo__mountns_निकास(&nsc);
	अगर (err < 0) अणु
		pr_debug("Couldn't read a build-id in %s\n", filename);
		वापस -1;
	पूर्ण
	err = 0;

	build_id__प्र_लिखो(&bid, sbuild_id);
	अगर (build_id_cache__cached(sbuild_id))
		err = build_id_cache__हटाओ_s(sbuild_id);

	अगर (!err)
		err = build_id_cache__add_s(sbuild_id, filename, nsi, false,
					    false);

	pr_debug("Updating %s %s: %s\n", sbuild_id, filename,
		 err ? "FAIL" : "Ok");

	वापस err;
पूर्ण

अटल पूर्णांक build_id_cache__show_all(व्योम)
अणु
	काष्ठा strlist *bidlist;
	काष्ठा str_node *nd;
	अक्षर *buf;

	bidlist = build_id_cache__list_all(true);
	अगर (!bidlist) अणु
		pr_debug("Failed to get buildids: -%d\n", त्रुटि_सं);
		वापस -1;
	पूर्ण
	strlist__क्रम_each_entry(nd, bidlist) अणु
		buf = build_id_cache__origname(nd->s);
		ख_लिखो(मानक_निकास, "%s %s\n", nd->s, buf);
		मुक्त(buf);
	पूर्ण
	strlist__delete(bidlist);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_buildid_cache_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *cb)
अणु
	स्थिर अक्षर **debuginfod = cb;

	अगर (!म_भेद(var, "buildid-cache.debuginfod"))
		*debuginfod = strdup(value);

	वापस 0;
पूर्ण

पूर्णांक cmd_buildid_cache(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा strlist *list;
	काष्ठा str_node *pos;
	पूर्णांक ret, ns_id = -1;
	bool क्रमce = false;
	bool list_files = false;
	bool opts_flag = false;
	bool purge_all = false;
	अक्षर स्थिर *add_name_list_str = शून्य,
		   *हटाओ_name_list_str = शून्य,
		   *purge_name_list_str = शून्य,
		   *missing_filename = शून्य,
		   *update_name_list_str = शून्य,
		   *kcore_filename = शून्य,
		   *debuginfod = शून्य;
	अक्षर sbuf[STRERR_बफ_मानE];

	काष्ठा perf_data data = अणु
		.mode  = PERF_DATA_MODE_READ,
	पूर्ण;
	काष्ठा perf_session *session = शून्य;
	काष्ठा nsinfo *nsi = शून्य;

	स्थिर काष्ठा option buildid_cache_options[] = अणु
	OPT_STRING('a', "add", &add_name_list_str,
		   "file list", "file(s) to add"),
	OPT_STRING('k', "kcore", &kcore_filename,
		   "file", "kcore file to add"),
	OPT_STRING('r', "remove", &हटाओ_name_list_str, "file list",
		    "file(s) to remove"),
	OPT_STRING('p', "purge", &purge_name_list_str, "file list",
		    "file(s) to remove (remove old caches too)"),
	OPT_BOOLEAN('P', "purge-all", &purge_all, "purge all cached files"),
	OPT_BOOLEAN('l', "list", &list_files, "list all cached files"),
	OPT_STRING('M', "missing", &missing_filename, "file",
		   "to find missing build ids in the cache"),
	OPT_BOOLEAN('f', "force", &force, "don't complain, करो it"),
	OPT_STRING('u', "update", &update_name_list_str, "file list",
		    "file(s) to update"),
	OPT_STRING(0, "debuginfod", &debuginfod, "debuginfod url",
		    "set debuginfod url"),
	OPT_INCR('v', "verbose", &verbose, "be more verbose"),
	OPT_INTEGER(0, "target-ns", &ns_id, "target pid for namespace context"),
	OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर buildid_cache_usage[] = अणु
		"perf buildid-cache [<options>]",
		शून्य
	पूर्ण;

	ret = perf_config(perf_buildid_cache_config, &debuginfod);
	अगर (ret)
		वापस ret;

	argc = parse_options(argc, argv, buildid_cache_options,
			     buildid_cache_usage, 0);

	opts_flag = add_name_list_str || kcore_filename ||
		हटाओ_name_list_str || purge_name_list_str ||
		missing_filename || update_name_list_str ||
		purge_all;

	अगर (argc || !(list_files || opts_flag))
		usage_with_options(buildid_cache_usage, buildid_cache_options);

	अगर (debuginfod) अणु
		pr_debug("DEBUGINFOD_URLS=%s\n", debuginfod);
		setenv("DEBUGINFOD_URLS", debuginfod, 1);
	पूर्ण

	/* -l is exclusive. It can not be used with other options. */
	अगर (list_files && opts_flag) अणु
		usage_with_options_msg(buildid_cache_usage,
			buildid_cache_options, "-l is exclusive.\n");
	पूर्ण

	अगर (ns_id > 0)
		nsi = nsinfo__new(ns_id);

	अगर (missing_filename) अणु
		data.path  = missing_filename;
		data.क्रमce = क्रमce;

		session = perf_session__new(&data, false, शून्य);
		अगर (IS_ERR(session))
			वापस PTR_ERR(session);
	पूर्ण

	अगर (symbol__init(session ? &session->header.env : शून्य) < 0)
		जाओ out;

	setup_pager();

	अगर (list_files) अणु
		ret = build_id_cache__show_all();
		जाओ out;
	पूर्ण

	अगर (add_name_list_str) अणु
		list = strlist__new(add_name_list_str, शून्य);
		अगर (list) अणु
			strlist__क्रम_each_entry(pos, list)
				अगर (build_id_cache__add_file(pos->s, nsi)) अणु
					अगर (त्रुटि_सं == EEXIST) अणु
						pr_debug("%s already in the cache\n",
							 pos->s);
						जारी;
					पूर्ण
					pr_warning("Couldn't add %s: %s\n",
						   pos->s, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
				पूर्ण

			strlist__delete(list);
		पूर्ण
	पूर्ण

	अगर (हटाओ_name_list_str) अणु
		list = strlist__new(हटाओ_name_list_str, शून्य);
		अगर (list) अणु
			strlist__क्रम_each_entry(pos, list)
				अगर (build_id_cache__हटाओ_file(pos->s, nsi)) अणु
					अगर (त्रुटि_सं == ENOENT) अणु
						pr_debug("%s wasn't in the cache\n",
							 pos->s);
						जारी;
					पूर्ण
					pr_warning("Couldn't remove %s: %s\n",
						   pos->s, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
				पूर्ण

			strlist__delete(list);
		पूर्ण
	पूर्ण

	अगर (purge_name_list_str) अणु
		list = strlist__new(purge_name_list_str, शून्य);
		अगर (list) अणु
			strlist__क्रम_each_entry(pos, list)
				अगर (build_id_cache__purge_path(pos->s, nsi)) अणु
					अगर (त्रुटि_सं == ENOENT) अणु
						pr_debug("%s wasn't in the cache\n",
							 pos->s);
						जारी;
					पूर्ण
					pr_warning("Couldn't remove %s: %s\n",
						   pos->s, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
				पूर्ण

			strlist__delete(list);
		पूर्ण
	पूर्ण

	अगर (purge_all) अणु
		अगर (build_id_cache__purge_all()) अणु
			pr_warning("Couldn't remove some caches. Error: %s.\n",
				str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		पूर्ण
	पूर्ण

	अगर (missing_filename)
		ret = build_id_cache__ख_लिखो_missing(session, मानक_निकास);

	अगर (update_name_list_str) अणु
		list = strlist__new(update_name_list_str, शून्य);
		अगर (list) अणु
			strlist__क्रम_each_entry(pos, list)
				अगर (build_id_cache__update_file(pos->s, nsi)) अणु
					अगर (त्रुटि_सं == ENOENT) अणु
						pr_debug("%s wasn't in the cache\n",
							 pos->s);
						जारी;
					पूर्ण
					pr_warning("Couldn't update %s: %s\n",
						   pos->s, str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
				पूर्ण

			strlist__delete(list);
		पूर्ण
	पूर्ण

	अगर (kcore_filename && build_id_cache__add_kcore(kcore_filename, क्रमce))
		pr_warning("Couldn't add %s\n", kcore_filename);

out:
	perf_session__delete(session);
	nsinfo__zput(nsi);

	वापस ret;
पूर्ण
