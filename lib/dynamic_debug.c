<शैली गुरु>
/*
 * lib/dynamic_debug.c
 *
 * make pr_debug()/dev_dbg() calls runसमय configurable based upon their
 * source module.
 *
 * Copyright (C) 2008 Jason Baron <jbaron@redhat.com>
 * By Greg Banks <gnb@melbourne.sgi.com>
 * Copyright (c) 2008 Silicon Graphics Inc.  All Rights Reserved.
 * Copyright (C) 2011 Bart Van Assche.  All Rights Reserved.
 * Copyright (C) 2013 Du, Changbin <changbin.du@gmail.com>
 */

#घोषणा pr_fmt(fmt) "dyndbg: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/list.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/parser.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/jump_label.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h>
#समावेश <linux/netdevice.h>

#समावेश <rdma/ib_verbs.h>

बाह्य काष्ठा _ddebug __start___dyndbg[];
बाह्य काष्ठा _ddebug __stop___dyndbg[];

काष्ठा ddebug_table अणु
	काष्ठा list_head link;
	स्थिर अक्षर *mod_name;
	अचिन्हित पूर्णांक num_ddebugs;
	काष्ठा _ddebug *ddebugs;
पूर्ण;

काष्ठा ddebug_query अणु
	स्थिर अक्षर *filename;
	स्थिर अक्षर *module;
	स्थिर अक्षर *function;
	स्थिर अक्षर *क्रमmat;
	अचिन्हित पूर्णांक first_lineno, last_lineno;
पूर्ण;

काष्ठा ddebug_iter अणु
	काष्ठा ddebug_table *table;
	अचिन्हित पूर्णांक idx;
पूर्ण;

काष्ठा flag_settings अणु
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक mask;
पूर्ण;

अटल DEFINE_MUTEX(ddebug_lock);
अटल LIST_HEAD(ddebug_tables);
अटल पूर्णांक verbose;
module_param(verbose, पूर्णांक, 0644);

/* Return the path relative to source root */
अटल अंतरभूत स्थिर अक्षर *trim_prefix(स्थिर अक्षर *path)
अणु
	पूर्णांक skip = म_माप(__खाता__) - म_माप("lib/dynamic_debug.c");

	अगर (म_भेदन(path, __खाता__, skip))
		skip = 0; /* prefix mismatch, करोn't skip */

	वापस path + skip;
पूर्ण

अटल काष्ठा अणु अचिन्हित flag:8; अक्षर opt_अक्षर; पूर्ण opt_array[] = अणु
	अणु _DPRINTK_FLAGS_PRINT, 'p' पूर्ण,
	अणु _DPRINTK_FLAGS_INCL_MODNAME, 'm' पूर्ण,
	अणु _DPRINTK_FLAGS_INCL_FUNCNAME, 'f' पूर्ण,
	अणु _DPRINTK_FLAGS_INCL_LINENO, 'l' पूर्ण,
	अणु _DPRINTK_FLAGS_INCL_TID, 't' पूर्ण,
	अणु _DPRINTK_FLAGS_NONE, '_' पूर्ण,
पूर्ण;

काष्ठा flagsbuf अणु अक्षर buf[ARRAY_SIZE(opt_array)+1]; पूर्ण;

/* क्रमmat a string पूर्णांकo buf[] which describes the _ddebug's flags */
अटल अक्षर *ddebug_describe_flags(अचिन्हित पूर्णांक flags, काष्ठा flagsbuf *fb)
अणु
	अक्षर *p = fb->buf;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(opt_array); ++i)
		अगर (flags & opt_array[i].flag)
			*p++ = opt_array[i].opt_अक्षर;
	अगर (p == fb->buf)
		*p++ = '_';
	*p = '\0';

	वापस fb->buf;
पूर्ण

#घोषणा vnpr_info(lvl, fmt, ...)				\
करो अणु								\
	अगर (verbose >= lvl)					\
		pr_info(fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

#घोषणा vpr_info(fmt, ...)	vnpr_info(1, fmt, ##__VA_ARGS__)
#घोषणा v2pr_info(fmt, ...)	vnpr_info(2, fmt, ##__VA_ARGS__)

अटल व्योम vpr_info_dq(स्थिर काष्ठा ddebug_query *query, स्थिर अक्षर *msg)
अणु
	/* trim any trailing newlines */
	पूर्णांक fmtlen = 0;

	अगर (query->क्रमmat) अणु
		fmtlen = म_माप(query->क्रमmat);
		जबतक (fmtlen && query->क्रमmat[fmtlen - 1] == '\n')
			fmtlen--;
	पूर्ण

	vpr_info("%s: func=\"%s\" file=\"%s\" module=\"%s\" format=\"%.*s\" lineno=%u-%u\n",
		 msg,
		 query->function ?: "",
		 query->filename ?: "",
		 query->module ?: "",
		 fmtlen, query->क्रमmat ?: "",
		 query->first_lineno, query->last_lineno);
पूर्ण

/*
 * Search the tables क्रम _ddebug's which match the given `query' and
 * apply the `flags' and `mask' to them.  Returns number of matching
 * callsites, normally the same as number of changes.  If verbose,
 * logs the changes.  Takes ddebug_lock.
 */
अटल पूर्णांक ddebug_change(स्थिर काष्ठा ddebug_query *query,
			 काष्ठा flag_settings *modअगरiers)
अणु
	पूर्णांक i;
	काष्ठा ddebug_table *dt;
	अचिन्हित पूर्णांक newflags;
	अचिन्हित पूर्णांक nfound = 0;
	काष्ठा flagsbuf fbuf;

	/* search क्रम matching ddebugs */
	mutex_lock(&ddebug_lock);
	list_क्रम_each_entry(dt, &ddebug_tables, link) अणु

		/* match against the module name */
		अगर (query->module &&
		    !match_wildcard(query->module, dt->mod_name))
			जारी;

		क्रम (i = 0; i < dt->num_ddebugs; i++) अणु
			काष्ठा _ddebug *dp = &dt->ddebugs[i];

			/* match against the source filename */
			अगर (query->filename &&
			    !match_wildcard(query->filename, dp->filename) &&
			    !match_wildcard(query->filename,
					   kbasename(dp->filename)) &&
			    !match_wildcard(query->filename,
					   trim_prefix(dp->filename)))
				जारी;

			/* match against the function */
			अगर (query->function &&
			    !match_wildcard(query->function, dp->function))
				जारी;

			/* match against the क्रमmat */
			अगर (query->क्रमmat) अणु
				अगर (*query->क्रमmat == '^') अणु
					अक्षर *p;
					/* anchored search. match must be at beginning */
					p = म_माला(dp->क्रमmat, query->क्रमmat+1);
					अगर (p != dp->क्रमmat)
						जारी;
				पूर्ण अन्यथा अगर (!म_माला(dp->क्रमmat, query->क्रमmat))
					जारी;
			पूर्ण

			/* match against the line number range */
			अगर (query->first_lineno &&
			    dp->lineno < query->first_lineno)
				जारी;
			अगर (query->last_lineno &&
			    dp->lineno > query->last_lineno)
				जारी;

			nfound++;

			newflags = (dp->flags & modअगरiers->mask) | modअगरiers->flags;
			अगर (newflags == dp->flags)
				जारी;
#अगर_घोषित CONFIG_JUMP_LABEL
			अगर (dp->flags & _DPRINTK_FLAGS_PRINT) अणु
				अगर (!(modअगरiers->flags & _DPRINTK_FLAGS_PRINT))
					अटल_branch_disable(&dp->key.dd_key_true);
			पूर्ण अन्यथा अगर (modअगरiers->flags & _DPRINTK_FLAGS_PRINT)
				अटल_branch_enable(&dp->key.dd_key_true);
#पूर्ण_अगर
			dp->flags = newflags;
			v2pr_info("changed %s:%d [%s]%s =%s\n",
				 trim_prefix(dp->filename), dp->lineno,
				 dt->mod_name, dp->function,
				 ddebug_describe_flags(dp->flags, &fbuf));
		पूर्ण
	पूर्ण
	mutex_unlock(&ddebug_lock);

	अगर (!nfound && verbose)
		pr_info("no matches for query\n");

	वापस nfound;
पूर्ण

/*
 * Split the buffer `buf' पूर्णांकo space-separated words.
 * Handles simple " and ' quoting, i.e. without nested,
 * embedded or escaped \".  Return the number of words
 * or <0 on error.
 */
अटल पूर्णांक ddebug_tokenize(अक्षर *buf, अक्षर *words[], पूर्णांक maxwords)
अणु
	पूर्णांक nwords = 0;

	जबतक (*buf) अणु
		अक्षर *end;

		/* Skip leading whitespace */
		buf = skip_spaces(buf);
		अगर (!*buf)
			अवरोध;	/* oh, it was trailing whitespace */
		अगर (*buf == '#')
			अवरोध;	/* token starts comment, skip rest of line */

		/* find `end' of word, whitespace separated or quoted */
		अगर (*buf == '"' || *buf == '\'') अणु
			पूर्णांक quote = *buf++;
			क्रम (end = buf; *end && *end != quote; end++)
				;
			अगर (!*end) अणु
				pr_err("unclosed quote: %s\n", buf);
				वापस -EINVAL;	/* unबंदd quote */
			पूर्ण
		पूर्ण अन्यथा अणु
			क्रम (end = buf; *end && !है_खाली(*end); end++)
				;
			BUG_ON(end == buf);
		पूर्ण

		/* `buf' is start of word, `end' is one past its end */
		अगर (nwords == maxwords) अणु
			pr_err("too many words, legal max <=%d\n", maxwords);
			वापस -EINVAL;	/* ran out of words[] beक्रमe bytes */
		पूर्ण
		अगर (*end)
			*end++ = '\0';	/* terminate the word */
		words[nwords++] = buf;
		buf = end;
	पूर्ण

	अगर (verbose) अणु
		पूर्णांक i;
		pr_info("split into words:");
		क्रम (i = 0; i < nwords; i++)
			pr_cont(" \"%s\"", words[i]);
		pr_cont("\n");
	पूर्ण

	वापस nwords;
पूर्ण

/*
 * Parse a single line number.  Note that the empty string ""
 * is treated as a special हाल and converted to zero, which
 * is later treated as a "don't care" value.
 */
अटल अंतरभूत पूर्णांक parse_lineno(स्थिर अक्षर *str, अचिन्हित पूर्णांक *val)
अणु
	BUG_ON(str == शून्य);
	अगर (*str == '\0') अणु
		*val = 0;
		वापस 0;
	पूर्ण
	अगर (kstrtouपूर्णांक(str, 10, val) < 0) अणु
		pr_err("bad line-number: %s\n", str);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक parse_linerange(काष्ठा ddebug_query *query, स्थिर अक्षर *first)
अणु
	अक्षर *last = म_अक्षर(first, '-');

	अगर (query->first_lineno || query->last_lineno) अणु
		pr_err("match-spec: line used 2x\n");
		वापस -EINVAL;
	पूर्ण
	अगर (last)
		*last++ = '\0';
	अगर (parse_lineno(first, &query->first_lineno) < 0)
		वापस -EINVAL;
	अगर (last) अणु
		/* range <first>-<last> */
		अगर (parse_lineno(last, &query->last_lineno) < 0)
			वापस -EINVAL;

		/* special हाल क्रम last lineno not specअगरied */
		अगर (query->last_lineno == 0)
			query->last_lineno = अच_पूर्णांक_उच्च;

		अगर (query->last_lineno < query->first_lineno) अणु
			pr_err("last-line:%d < 1st-line:%d\n",
			       query->last_lineno,
			       query->first_lineno);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		query->last_lineno = query->first_lineno;
	पूर्ण
	vpr_info("parsed line %d-%d\n", query->first_lineno,
		 query->last_lineno);
	वापस 0;
पूर्ण

अटल पूर्णांक check_set(स्थिर अक्षर **dest, अक्षर *src, अक्षर *name)
अणु
	पूर्णांक rc = 0;

	अगर (*dest) अणु
		rc = -EINVAL;
		pr_err("match-spec:%s val:%s overridden by %s\n",
		       name, *dest, src);
	पूर्ण
	*dest = src;
	वापस rc;
पूर्ण

/*
 * Parse words[] as a ddebug query specअगरication, which is a series
 * of (keyword, value) pairs chosen from these possibilities:
 *
 * func <function-name>
 * file <full-pathname>
 * file <base-filename>
 * module <module-name>
 * क्रमmat <escaped-string-to-find-in-क्रमmat>
 * line <lineno>
 * line <first-lineno>-<last-lineno> // where either may be empty
 *
 * Only 1 of each type is allowed.
 * Returns 0 on success, <0 on error.
 */
अटल पूर्णांक ddebug_parse_query(अक्षर *words[], पूर्णांक nwords,
			काष्ठा ddebug_query *query, स्थिर अक्षर *modname)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;
	अक्षर *fline;

	/* check we have an even number of words */
	अगर (nwords % 2 != 0) अणु
		pr_err("expecting pairs of match-spec <value>\n");
		वापस -EINVAL;
	पूर्ण

	अगर (modname)
		/* support $modname.dyndbg=<multiple queries> */
		query->module = modname;

	क्रम (i = 0; i < nwords; i += 2) अणु
		अक्षर *keyword = words[i];
		अक्षर *arg = words[i+1];

		अगर (!म_भेद(keyword, "func")) अणु
			rc = check_set(&query->function, arg, "func");
		पूर्ण अन्यथा अगर (!म_भेद(keyword, "file")) अणु
			अगर (check_set(&query->filename, arg, "file"))
				वापस -EINVAL;

			/* tail :$info is function or line-range */
			fline = म_अक्षर(query->filename, ':');
			अगर (!fline)
				जारी;
			*fline++ = '\0';
			अगर (है_अक्षर(*fline) || *fline == '*' || *fline == '?') अणु
				/* take as function name */
				अगर (check_set(&query->function, fline, "func"))
					वापस -EINVAL;
			पूर्ण अन्यथा अणु
				अगर (parse_linerange(query, fline))
					वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(keyword, "module")) अणु
			rc = check_set(&query->module, arg, "module");
		पूर्ण अन्यथा अगर (!म_भेद(keyword, "format")) अणु
			string_unescape_inplace(arg, UNESCAPE_SPACE |
							    UNESCAPE_OCTAL |
							    UNESCAPE_SPECIAL);
			rc = check_set(&query->क्रमmat, arg, "format");
		पूर्ण अन्यथा अगर (!म_भेद(keyword, "line")) अणु
			अगर (parse_linerange(query, arg))
				वापस -EINVAL;
		पूर्ण अन्यथा अणु
			pr_err("unknown keyword \"%s\"\n", keyword);
			वापस -EINVAL;
		पूर्ण
		अगर (rc)
			वापस rc;
	पूर्ण
	vpr_info_dq(query, "parsed");
	वापस 0;
पूर्ण

/*
 * Parse `str' as a flags specअगरication, क्रमmat [-+=][p]+.
 * Sets up *maskp and *flagsp to be used when changing the
 * flags fields of matched _ddebug's.  Returns 0 on success
 * or <0 on error.
 */
अटल पूर्णांक ddebug_parse_flags(स्थिर अक्षर *str, काष्ठा flag_settings *modअगरiers)
अणु
	पूर्णांक op, i;

	चयन (*str) अणु
	हाल '+':
	हाल '-':
	हाल '=':
		op = *str++;
		अवरोध;
	शेष:
		pr_err("bad flag-op %c, at start of %s\n", *str, str);
		वापस -EINVAL;
	पूर्ण
	vpr_info("op='%c'\n", op);

	क्रम (; *str ; ++str) अणु
		क्रम (i = ARRAY_SIZE(opt_array) - 1; i >= 0; i--) अणु
			अगर (*str == opt_array[i].opt_अक्षर) अणु
				modअगरiers->flags |= opt_array[i].flag;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i < 0) अणु
			pr_err("unknown flag '%c'\n", *str);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	vpr_info("flags=0x%x\n", modअगरiers->flags);

	/* calculate final flags, mask based upon op */
	चयन (op) अणु
	हाल '=':
		/* modअगरiers->flags alपढ़ोy set */
		modअगरiers->mask = 0;
		अवरोध;
	हाल '+':
		modअगरiers->mask = ~0U;
		अवरोध;
	हाल '-':
		modअगरiers->mask = ~modअगरiers->flags;
		modअगरiers->flags = 0;
		अवरोध;
	पूर्ण
	vpr_info("*flagsp=0x%x *maskp=0x%x\n", modअगरiers->flags, modअगरiers->mask);

	वापस 0;
पूर्ण

अटल पूर्णांक ddebug_exec_query(अक्षर *query_string, स्थिर अक्षर *modname)
अणु
	काष्ठा flag_settings modअगरiers = अणुपूर्ण;
	काष्ठा ddebug_query query = अणुपूर्ण;
#घोषणा MAXWORDS 9
	पूर्णांक nwords, nfound;
	अक्षर *words[MAXWORDS];

	nwords = ddebug_tokenize(query_string, words, MAXWORDS);
	अगर (nwords <= 0) अणु
		pr_err("tokenize failed\n");
		वापस -EINVAL;
	पूर्ण
	/* check flags 1st (last arg) so query is pairs of spec,val */
	अगर (ddebug_parse_flags(words[nwords-1], &modअगरiers)) अणु
		pr_err("flags parse failed\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ddebug_parse_query(words, nwords-1, &query, modname)) अणु
		pr_err("query parse failed\n");
		वापस -EINVAL;
	पूर्ण
	/* actually go and implement the change */
	nfound = ddebug_change(&query, &modअगरiers);
	vpr_info_dq(&query, nfound ? "applied" : "no-match");

	वापस nfound;
पूर्ण

/* handle multiple queries in query string, जारी on error, वापस
   last error or number of matching callsites.  Module name is either
   in param (क्रम boot arg) or perhaps in query string.
*/
अटल पूर्णांक ddebug_exec_queries(अक्षर *query, स्थिर अक्षर *modname)
अणु
	अक्षर *split;
	पूर्णांक i, errs = 0, निकासcode = 0, rc, nfound = 0;

	क्रम (i = 0; query; query = split) अणु
		split = strpbrk(query, ";\n");
		अगर (split)
			*split++ = '\0';

		query = skip_spaces(query);
		अगर (!query || !*query || *query == '#')
			जारी;

		vpr_info("query %d: \"%s\"\n", i, query);

		rc = ddebug_exec_query(query, modname);
		अगर (rc < 0) अणु
			errs++;
			निकासcode = rc;
		पूर्ण अन्यथा अणु
			nfound += rc;
		पूर्ण
		i++;
	पूर्ण
	vpr_info("processed %d queries, with %d matches, %d errs\n",
		 i, nfound, errs);

	अगर (निकासcode)
		वापस निकासcode;
	वापस nfound;
पूर्ण

/**
 * dynamic_debug_exec_queries - select and change dynamic-debug prपूर्णांकs
 * @query: query-string described in admin-guide/dynamic-debug-howto
 * @modname: string containing module name, usually &module.mod_name
 *
 * This uses the >/proc/dynamic_debug/control पढ़ोer, allowing module
 * authors to modअगरy their dynamic-debug callsites. The modname is
 * canonically काष्ठा module.mod_name, but can also be null or a
 * module-wildcard, क्रम example: "drm*".
 */
पूर्णांक dynamic_debug_exec_queries(स्थिर अक्षर *query, स्थिर अक्षर *modname)
अणु
	पूर्णांक rc;
	अक्षर *qry; /* writable copy of query */

	अगर (!query) अणु
		pr_err("non-null query/command string expected\n");
		वापस -EINVAL;
	पूर्ण
	qry = kstrndup(query, PAGE_SIZE, GFP_KERNEL);
	अगर (!qry)
		वापस -ENOMEM;

	rc = ddebug_exec_queries(qry, modname);
	kमुक्त(qry);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(dynamic_debug_exec_queries);

#घोषणा PREFIX_SIZE 64

अटल पूर्णांक reमुख्यing(पूर्णांक wrote)
अणु
	अगर (PREFIX_SIZE - wrote > 0)
		वापस PREFIX_SIZE - wrote;
	वापस 0;
पूर्ण

अटल अक्षर *__dynamic_emit_prefix(स्थिर काष्ठा _ddebug *desc, अक्षर *buf)
अणु
	पूर्णांक pos_after_tid;
	पूर्णांक pos = 0;

	अगर (desc->flags & _DPRINTK_FLAGS_INCL_TID) अणु
		अगर (in_पूर्णांकerrupt())
			pos += snम_लिखो(buf + pos, reमुख्यing(pos), "<intr> ");
		अन्यथा
			pos += snम_लिखो(buf + pos, reमुख्यing(pos), "[%d] ",
					task_pid_vnr(current));
	पूर्ण
	pos_after_tid = pos;
	अगर (desc->flags & _DPRINTK_FLAGS_INCL_MODNAME)
		pos += snम_लिखो(buf + pos, reमुख्यing(pos), "%s:",
				desc->modname);
	अगर (desc->flags & _DPRINTK_FLAGS_INCL_FUNCNAME)
		pos += snम_लिखो(buf + pos, reमुख्यing(pos), "%s:",
				desc->function);
	अगर (desc->flags & _DPRINTK_FLAGS_INCL_LINENO)
		pos += snम_लिखो(buf + pos, reमुख्यing(pos), "%d:",
				desc->lineno);
	अगर (pos - pos_after_tid)
		pos += snम_लिखो(buf + pos, reमुख्यing(pos), " ");
	अगर (pos >= PREFIX_SIZE)
		buf[PREFIX_SIZE - 1] = '\0';

	वापस buf;
पूर्ण

अटल अंतरभूत अक्षर *dynamic_emit_prefix(काष्ठा _ddebug *desc, अक्षर *buf)
अणु
	अगर (unlikely(desc->flags & _DPRINTK_FLAGS_INCL_ANY))
		वापस __dynamic_emit_prefix(desc, buf);
	वापस buf;
पूर्ण

व्योम __dynamic_pr_debug(काष्ठा _ddebug *descriptor, स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	काष्ठा va_क्रमmat vaf;
	अक्षर buf[PREFIX_SIZE] = "";

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk(KERN_DEBUG "%s%pV", dynamic_emit_prefix(descriptor, buf), &vaf);

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__dynamic_pr_debug);

व्योम __dynamic_dev_dbg(काष्ठा _ddebug *descriptor,
		      स्थिर काष्ठा device *dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (!dev) अणु
		prपूर्णांकk(KERN_DEBUG "(NULL device *): %pV", &vaf);
	पूर्ण अन्यथा अणु
		अक्षर buf[PREFIX_SIZE] = "";

		dev_prपूर्णांकk_emit(LOGLEVEL_DEBUG, dev, "%s%s %s: %pV",
				dynamic_emit_prefix(descriptor, buf),
				dev_driver_string(dev), dev_name(dev),
				&vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__dynamic_dev_dbg);

#अगर_घोषित CONFIG_NET

व्योम __dynamic_netdev_dbg(काष्ठा _ddebug *descriptor,
			  स्थिर काष्ठा net_device *dev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	BUG_ON(!descriptor);
	BUG_ON(!fmt);

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (dev && dev->dev.parent) अणु
		अक्षर buf[PREFIX_SIZE] = "";

		dev_prपूर्णांकk_emit(LOGLEVEL_DEBUG, dev->dev.parent,
				"%s%s %s %s%s: %pV",
				dynamic_emit_prefix(descriptor, buf),
				dev_driver_string(dev->dev.parent),
				dev_name(dev->dev.parent),
				netdev_name(dev), netdev_reg_state(dev),
				&vaf);
	पूर्ण अन्यथा अगर (dev) अणु
		prपूर्णांकk(KERN_DEBUG "%s%s: %pV", netdev_name(dev),
		       netdev_reg_state(dev), &vaf);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "(NULL net_device): %pV", &vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__dynamic_netdev_dbg);

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_INFINIBAND)

व्योम __dynamic_ibdev_dbg(काष्ठा _ddebug *descriptor,
			 स्थिर काष्ठा ib_device *ibdev, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	अगर (ibdev && ibdev->dev.parent) अणु
		अक्षर buf[PREFIX_SIZE] = "";

		dev_prपूर्णांकk_emit(LOGLEVEL_DEBUG, ibdev->dev.parent,
				"%s%s %s %s: %pV",
				dynamic_emit_prefix(descriptor, buf),
				dev_driver_string(ibdev->dev.parent),
				dev_name(ibdev->dev.parent),
				dev_name(&ibdev->dev),
				&vaf);
	पूर्ण अन्यथा अगर (ibdev) अणु
		prपूर्णांकk(KERN_DEBUG "%s: %pV", dev_name(&ibdev->dev), &vaf);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "(NULL ib_device): %pV", &vaf);
	पूर्ण

	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL(__dynamic_ibdev_dbg);

#पूर्ण_अगर

#घोषणा DDEBUG_STRING_SIZE 1024
अटल __initdata अक्षर ddebug_setup_string[DDEBUG_STRING_SIZE];

अटल __init पूर्णांक ddebug_setup_query(अक्षर *str)
अणु
	अगर (म_माप(str) >= DDEBUG_STRING_SIZE) अणु
		pr_warn("ddebug boot param string too large\n");
		वापस 0;
	पूर्ण
	strlcpy(ddebug_setup_string, str, DDEBUG_STRING_SIZE);
	वापस 1;
पूर्ण

__setup("ddebug_query=", ddebug_setup_query);

/*
 * File_ops->ग_लिखो method क्रम <debugfs>/dynamic_debug/control.  Gathers the
 * command text from userspace, parses and executes it.
 */
#घोषणा USER_BUF_PAGE 4096
अटल sमाप_प्रकार ddebug_proc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
				  माप_प्रकार len, loff_t *offp)
अणु
	अक्षर *पंचांगpbuf;
	पूर्णांक ret;

	अगर (len == 0)
		वापस 0;
	अगर (len > USER_BUF_PAGE - 1) अणु
		pr_warn("expected <%d bytes into control\n", USER_BUF_PAGE);
		वापस -E2BIG;
	पूर्ण
	पंचांगpbuf = memdup_user_nul(ubuf, len);
	अगर (IS_ERR(पंचांगpbuf))
		वापस PTR_ERR(पंचांगpbuf);
	vpr_info("read %d bytes from userspace\n", (पूर्णांक)len);

	ret = ddebug_exec_queries(पंचांगpbuf, शून्य);
	kमुक्त(पंचांगpbuf);
	अगर (ret < 0)
		वापस ret;

	*offp += len;
	वापस len;
पूर्ण

/*
 * Set the iterator to poपूर्णांक to the first _ddebug object
 * and वापस a poपूर्णांकer to that first object.  Returns
 * शून्य अगर there are no _ddebugs at all.
 */
अटल काष्ठा _ddebug *ddebug_iter_first(काष्ठा ddebug_iter *iter)
अणु
	अगर (list_empty(&ddebug_tables)) अणु
		iter->table = शून्य;
		iter->idx = 0;
		वापस शून्य;
	पूर्ण
	iter->table = list_entry(ddebug_tables.next,
				 काष्ठा ddebug_table, link);
	iter->idx = 0;
	वापस &iter->table->ddebugs[iter->idx];
पूर्ण

/*
 * Advance the iterator to poपूर्णांक to the next _ddebug
 * object from the one the iterator currently poपूर्णांकs at,
 * and वापसs a poपूर्णांकer to the new _ddebug.  Returns
 * शून्य अगर the iterator has seen all the _ddebugs.
 */
अटल काष्ठा _ddebug *ddebug_iter_next(काष्ठा ddebug_iter *iter)
अणु
	अगर (iter->table == शून्य)
		वापस शून्य;
	अगर (++iter->idx == iter->table->num_ddebugs) अणु
		/* iterate to next table */
		iter->idx = 0;
		अगर (list_is_last(&iter->table->link, &ddebug_tables)) अणु
			iter->table = शून्य;
			वापस शून्य;
		पूर्ण
		iter->table = list_entry(iter->table->link.next,
					 काष्ठा ddebug_table, link);
	पूर्ण
	वापस &iter->table->ddebugs[iter->idx];
पूर्ण

/*
 * Seq_ops start method.  Called at the start of every
 * पढ़ो() call from userspace.  Takes the ddebug_lock and
 * seeks the seq_file's iterator to the given position.
 */
अटल व्योम *ddebug_proc_start(काष्ठा seq_file *m, loff_t *pos)
अणु
	काष्ठा ddebug_iter *iter = m->निजी;
	काष्ठा _ddebug *dp;
	पूर्णांक n = *pos;

	mutex_lock(&ddebug_lock);

	अगर (!n)
		वापस SEQ_START_TOKEN;
	अगर (n < 0)
		वापस शून्य;
	dp = ddebug_iter_first(iter);
	जबतक (dp != शून्य && --n > 0)
		dp = ddebug_iter_next(iter);
	वापस dp;
पूर्ण

/*
 * Seq_ops next method.  Called several बार within a पढ़ो()
 * call from userspace, with ddebug_lock held.  Walks to the
 * next _ddebug object with a special हाल क्रम the header line.
 */
अटल व्योम *ddebug_proc_next(काष्ठा seq_file *m, व्योम *p, loff_t *pos)
अणु
	काष्ठा ddebug_iter *iter = m->निजी;
	काष्ठा _ddebug *dp;

	अगर (p == SEQ_START_TOKEN)
		dp = ddebug_iter_first(iter);
	अन्यथा
		dp = ddebug_iter_next(iter);
	++*pos;
	वापस dp;
पूर्ण

/*
 * Seq_ops show method.  Called several बार within a पढ़ो()
 * call from userspace, with ddebug_lock held.  Formats the
 * current _ddebug as a single human-पढ़ोable line, with a
 * special हाल क्रम the header line.
 */
अटल पूर्णांक ddebug_proc_show(काष्ठा seq_file *m, व्योम *p)
अणु
	काष्ठा ddebug_iter *iter = m->निजी;
	काष्ठा _ddebug *dp = p;
	काष्ठा flagsbuf flags;

	अगर (p == SEQ_START_TOKEN) अणु
		seq_माला_दो(m,
			 "# filename:lineno [module]function flags format\n");
		वापस 0;
	पूर्ण

	seq_म_लिखो(m, "%s:%u [%s]%s =%s \"",
		   trim_prefix(dp->filename), dp->lineno,
		   iter->table->mod_name, dp->function,
		   ddebug_describe_flags(dp->flags, &flags));
	seq_escape(m, dp->क्रमmat, "\t\r\n\"");
	seq_माला_दो(m, "\"\n");

	वापस 0;
पूर्ण

/*
 * Seq_ops stop method.  Called at the end of each पढ़ो()
 * call from userspace.  Drops ddebug_lock.
 */
अटल व्योम ddebug_proc_stop(काष्ठा seq_file *m, व्योम *p)
अणु
	mutex_unlock(&ddebug_lock);
पूर्ण

अटल स्थिर काष्ठा seq_operations ddebug_proc_seqops = अणु
	.start = ddebug_proc_start,
	.next = ddebug_proc_next,
	.show = ddebug_proc_show,
	.stop = ddebug_proc_stop
पूर्ण;

अटल पूर्णांक ddebug_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_खोलो_निजी(file, &ddebug_proc_seqops,
				माप(काष्ठा ddebug_iter));
पूर्ण

अटल स्थिर काष्ठा file_operations ddebug_proc_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = ddebug_proc_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = seq_release_निजी,
	.ग_लिखो = ddebug_proc_ग_लिखो
पूर्ण;

अटल स्थिर काष्ठा proc_ops proc_fops = अणु
	.proc_खोलो = ddebug_proc_खोलो,
	.proc_पढ़ो = seq_पढ़ो,
	.proc_lseek = seq_lseek,
	.proc_release = seq_release_निजी,
	.proc_ग_लिखो = ddebug_proc_ग_लिखो
पूर्ण;

/*
 * Allocate a new ddebug_table क्रम the given module
 * and add it to the global list.
 */
पूर्णांक ddebug_add_module(काष्ठा _ddebug *tab, अचिन्हित पूर्णांक n,
			     स्थिर अक्षर *name)
अणु
	काष्ठा ddebug_table *dt;

	dt = kzalloc(माप(*dt), GFP_KERNEL);
	अगर (dt == शून्य) अणु
		pr_err("error adding module: %s\n", name);
		वापस -ENOMEM;
	पूर्ण
	/*
	 * For built-in modules, name lives in .rodata and is
	 * immortal. For loaded modules, name poपूर्णांकs at the name[]
	 * member of काष्ठा module, which lives at least as दीर्घ as
	 * this काष्ठा ddebug_table.
	 */
	dt->mod_name = name;
	dt->num_ddebugs = n;
	dt->ddebugs = tab;

	mutex_lock(&ddebug_lock);
	list_add(&dt->link, &ddebug_tables);
	mutex_unlock(&ddebug_lock);

	v2pr_info("%3u debug prints in module %s\n", n, dt->mod_name);
	वापस 0;
पूर्ण

/* helper क्रम ddebug_dyndbg_(boot|module)_param_cb */
अटल पूर्णांक ddebug_dyndbg_param_cb(अक्षर *param, अक्षर *val,
				स्थिर अक्षर *modname, पूर्णांक on_err)
अणु
	अक्षर *sep;

	sep = म_अक्षर(param, '.');
	अगर (sep) अणु
		/* needed only क्रम ddebug_dyndbg_boot_param_cb */
		*sep = '\0';
		modname = param;
		param = sep + 1;
	पूर्ण
	अगर (म_भेद(param, "dyndbg"))
		वापस on_err; /* determined by caller */

	ddebug_exec_queries((val ? val : "+p"), modname);

	वापस 0; /* query failure shouldnt stop module load */
पूर्ण

/* handle both dyndbg and $module.dyndbg params at boot */
अटल पूर्णांक ddebug_dyndbg_boot_param_cb(अक्षर *param, अक्षर *val,
				स्थिर अक्षर *unused, व्योम *arg)
अणु
	vpr_info("%s=\"%s\"\n", param, val);
	वापस ddebug_dyndbg_param_cb(param, val, शून्य, 0);
पूर्ण

/*
 * modprobe foo finds foo.params in boot-args, strips "foo.", and
 * passes them to load_module().  This callback माला_लो unknown params,
 * processes dyndbg params, rejects others.
 */
पूर्णांक ddebug_dyndbg_module_param_cb(अक्षर *param, अक्षर *val, स्थिर अक्षर *module)
अणु
	vpr_info("module: %s %s=\"%s\"\n", module, param, val);
	वापस ddebug_dyndbg_param_cb(param, val, module, -ENOENT);
पूर्ण

अटल व्योम ddebug_table_मुक्त(काष्ठा ddebug_table *dt)
अणु
	list_del_init(&dt->link);
	kमुक्त(dt);
पूर्ण

/*
 * Called in response to a module being unloaded.  Removes
 * any ddebug_table's which poपूर्णांक at the module.
 */
पूर्णांक ddebug_हटाओ_module(स्थिर अक्षर *mod_name)
अणु
	काष्ठा ddebug_table *dt, *nextdt;
	पूर्णांक ret = -ENOENT;

	v2pr_info("removing module \"%s\"\n", mod_name);

	mutex_lock(&ddebug_lock);
	list_क्रम_each_entry_safe(dt, nextdt, &ddebug_tables, link) अणु
		अगर (dt->mod_name == mod_name) अणु
			ddebug_table_मुक्त(dt);
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&ddebug_lock);
	वापस ret;
पूर्ण

अटल व्योम ddebug_हटाओ_all_tables(व्योम)
अणु
	mutex_lock(&ddebug_lock);
	जबतक (!list_empty(&ddebug_tables)) अणु
		काष्ठा ddebug_table *dt = list_entry(ddebug_tables.next,
						      काष्ठा ddebug_table,
						      link);
		ddebug_table_मुक्त(dt);
	पूर्ण
	mutex_unlock(&ddebug_lock);
पूर्ण

अटल __initdata पूर्णांक ddebug_init_success;

अटल पूर्णांक __init dynamic_debug_init_control(व्योम)
अणु
	काष्ठा proc_dir_entry *procfs_dir;
	काष्ठा dentry *debugfs_dir;

	अगर (!ddebug_init_success)
		वापस -ENODEV;

	/* Create the control file in debugfs अगर it is enabled */
	अगर (debugfs_initialized()) अणु
		debugfs_dir = debugfs_create_dir("dynamic_debug", शून्य);
		debugfs_create_file("control", 0644, debugfs_dir, शून्य,
				    &ddebug_proc_fops);
	पूर्ण

	/* Also create the control file in procfs */
	procfs_dir = proc_सूची_गढ़ो("dynamic_debug", शून्य);
	अगर (procfs_dir)
		proc_create("control", 0644, procfs_dir, &proc_fops);

	वापस 0;
पूर्ण

अटल पूर्णांक __init dynamic_debug_init(व्योम)
अणु
	काष्ठा _ddebug *iter, *iter_start;
	स्थिर अक्षर *modname = शून्य;
	अक्षर *cmdline;
	पूर्णांक ret = 0;
	पूर्णांक n = 0, entries = 0, modct = 0;

	अगर (&__start___dyndbg == &__stop___dyndbg) अणु
		अगर (IS_ENABLED(CONFIG_DYNAMIC_DEBUG)) अणु
			pr_warn("_ddebug table is empty in a CONFIG_DYNAMIC_DEBUG build\n");
			वापस 1;
		पूर्ण
		pr_info("Ignore empty _ddebug table in a CONFIG_DYNAMIC_DEBUG_CORE build\n");
		ddebug_init_success = 1;
		वापस 0;
	पूर्ण
	iter = __start___dyndbg;
	modname = iter->modname;
	iter_start = iter;
	क्रम (; iter < __stop___dyndbg; iter++) अणु
		entries++;
		अगर (म_भेद(modname, iter->modname)) अणु
			modct++;
			ret = ddebug_add_module(iter_start, n, modname);
			अगर (ret)
				जाओ out_err;
			n = 0;
			modname = iter->modname;
			iter_start = iter;
		पूर्ण
		n++;
	पूर्ण
	ret = ddebug_add_module(iter_start, n, modname);
	अगर (ret)
		जाओ out_err;

	ddebug_init_success = 1;
	vpr_info("%d modules, %d entries and %d bytes in ddebug tables, %d bytes in __dyndbg section\n",
		 modct, entries, (पूर्णांक)(modct * माप(काष्ठा ddebug_table)),
		 (पूर्णांक)(entries * माप(काष्ठा _ddebug)));

	/* apply ddebug_query boot param, करोnt unload tables on err */
	अगर (ddebug_setup_string[0] != '\0') अणु
		pr_warn("ddebug_query param name is deprecated, change it to dyndbg\n");
		ret = ddebug_exec_queries(ddebug_setup_string, शून्य);
		अगर (ret < 0)
			pr_warn("Invalid ddebug boot param %s\n",
				ddebug_setup_string);
		अन्यथा
			pr_info("%d changes by ddebug_query\n", ret);
	पूर्ण
	/* now that ddebug tables are loaded, process all boot args
	 * again to find and activate queries given in dyndbg params.
	 * While this has alपढ़ोy been करोne क्रम known boot params, it
	 * ignored the unknown ones (dyndbg in particular).  Reusing
	 * parse_args aव्योमs ad-hoc parsing.  This will also attempt
	 * to activate queries क्रम not-yet-loaded modules, which is
	 * slightly noisy अगर verbose, but harmless.
	 */
	cmdline = kstrdup(saved_command_line, GFP_KERNEL);
	parse_args("dyndbg params", cmdline, शून्य,
		   0, 0, 0, शून्य, &ddebug_dyndbg_boot_param_cb);
	kमुक्त(cmdline);
	वापस 0;

out_err:
	ddebug_हटाओ_all_tables();
	वापस 0;
पूर्ण
/* Allow early initialization क्रम boot messages via boot param */
early_initcall(dynamic_debug_init);

/* Debugfs setup must be करोne later */
fs_initcall(dynamic_debug_init_control);
