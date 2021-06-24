<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * config.c
 *
 * Helper functions क्रम parsing config items.
 * Originally copied from GIT source.
 *
 * Copyright (C) Linus Torvalds, 2005
 * Copyright (C) Johannes Schindelin, 2005
 *
 */
#समावेश <त्रुटिसं.स>
#समावेश <sys/param.h>
#समावेश "cache.h"
#समावेश "callchain.h"
#समावेश <subcmd/exec-cmd.h>
#समावेश "util/event.h"  /* proc_map_समयout */
#समावेश "util/hist.h"  /* perf_hist_config */
#समावेश "util/llvm-utils.h"   /* perf_llvm_config */
#समावेश "util/stat.h"  /* perf_stat__set_big_num */
#समावेश "util/evsel.h"  /* evsel__hw_names, evsel__use_bpf_counters */
#समावेश "build-id.h"
#समावेश "debug.h"
#समावेश "config.h"
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <linux/प्रकार.स>

#घोषणा MAXNAME (256)

#घोषणा DEBUG_CACHE_सूची ".debug"


अक्षर buildid_dir[MAXPATHLEN]; /* root dir क्रम buildid, binary cache */

अटल खाता *config_file;
अटल स्थिर अक्षर *config_file_name;
अटल पूर्णांक config_linenr;
अटल पूर्णांक config_file_eof;
अटल काष्ठा perf_config_set *config_set;

स्थिर अक्षर *config_exclusive_filename;

अटल पूर्णांक get_next_अक्षर(व्योम)
अणु
	पूर्णांक c;
	खाता *f;

	c = '\n';
	अगर ((f = config_file) != शून्य) अणु
		c = ख_अक्षर_लो(f);
		अगर (c == '\r') अणु
			/* DOS like प्रणालीs */
			c = ख_अक्षर_लो(f);
			अगर (c != '\n') अणु
				अक्षर_वापस(c, f);
				c = '\r';
			पूर्ण
		पूर्ण
		अगर (c == '\n')
			config_linenr++;
		अगर (c == खातापूर्ण) अणु
			config_file_eof = 1;
			c = '\n';
		पूर्ण
	पूर्ण
	वापस c;
पूर्ण

अटल अक्षर *parse_value(व्योम)
अणु
	अटल अक्षर value[1024];
	पूर्णांक quote = 0, comment = 0, space = 0;
	माप_प्रकार len = 0;

	क्रम (;;) अणु
		पूर्णांक c = get_next_अक्षर();

		अगर (len >= माप(value) - 1)
			वापस शून्य;
		अगर (c == '\n') अणु
			अगर (quote)
				वापस शून्य;
			value[len] = 0;
			वापस value;
		पूर्ण
		अगर (comment)
			जारी;
		अगर (है_खाली(c) && !quote) अणु
			space = 1;
			जारी;
		पूर्ण
		अगर (!quote) अणु
			अगर (c == ';' || c == '#') अणु
				comment = 1;
				जारी;
			पूर्ण
		पूर्ण
		अगर (space) अणु
			अगर (len)
				value[len++] = ' ';
			space = 0;
		पूर्ण
		अगर (c == '\\') अणु
			c = get_next_अक्षर();
			चयन (c) अणु
			हाल '\n':
				जारी;
			हाल 't':
				c = '\t';
				अवरोध;
			हाल 'b':
				c = '\b';
				अवरोध;
			हाल 'n':
				c = '\n';
				अवरोध;
			/* Some अक्षरacters escape as themselves */
			हाल '\\': case '"':
				अवरोध;
			/* Reject unknown escape sequences */
			शेष:
				वापस शून्य;
			पूर्ण
			value[len++] = c;
			जारी;
		पूर्ण
		अगर (c == '"') अणु
			quote = 1-quote;
			जारी;
		पूर्ण
		value[len++] = c;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक iskeyअक्षर(पूर्णांक c)
अणु
	वापस है_अक्षर_अंक(c) || c == '-' || c == '_';
पूर्ण

अटल पूर्णांक get_value(config_fn_t fn, व्योम *data, अक्षर *name, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक c;
	अक्षर *value;

	/* Get the full name */
	क्रम (;;) अणु
		c = get_next_अक्षर();
		अगर (config_file_eof)
			अवरोध;
		अगर (!iskeyअक्षर(c))
			अवरोध;
		name[len++] = c;
		अगर (len >= MAXNAME)
			वापस -1;
	पूर्ण
	name[len] = 0;
	जबतक (c == ' ' || c == '\t')
		c = get_next_अक्षर();

	value = शून्य;
	अगर (c != '\n') अणु
		अगर (c != '=')
			वापस -1;
		value = parse_value();
		अगर (!value)
			वापस -1;
	पूर्ण
	वापस fn(name, value, data);
पूर्ण

अटल पूर्णांक get_extended_base_var(अक्षर *name, पूर्णांक baselen, पूर्णांक c)
अणु
	करो अणु
		अगर (c == '\n')
			वापस -1;
		c = get_next_अक्षर();
	पूर्ण जबतक (है_खाली(c));

	/* We require the क्रमmat to be '[base "extension"]' */
	अगर (c != '"')
		वापस -1;
	name[baselen++] = '.';

	क्रम (;;) अणु
		पूर्णांक ch = get_next_अक्षर();

		अगर (ch == '\n')
			वापस -1;
		अगर (ch == '"')
			अवरोध;
		अगर (ch == '\\') अणु
			ch = get_next_अक्षर();
			अगर (ch == '\n')
				वापस -1;
		पूर्ण
		name[baselen++] = ch;
		अगर (baselen > MAXNAME / 2)
			वापस -1;
	पूर्ण

	/* Final ']' */
	अगर (get_next_अक्षर() != ']')
		वापस -1;
	वापस baselen;
पूर्ण

अटल पूर्णांक get_base_var(अक्षर *name)
अणु
	पूर्णांक baselen = 0;

	क्रम (;;) अणु
		पूर्णांक c = get_next_अक्षर();
		अगर (config_file_eof)
			वापस -1;
		अगर (c == ']')
			वापस baselen;
		अगर (है_खाली(c))
			वापस get_extended_base_var(name, baselen, c);
		अगर (!iskeyअक्षर(c) && c != '.')
			वापस -1;
		अगर (baselen > MAXNAME / 2)
			वापस -1;
		name[baselen++] = छोटे(c);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_parse_file(config_fn_t fn, व्योम *data)
अणु
	पूर्णांक comment = 0;
	पूर्णांक baselen = 0;
	अटल अक्षर var[MAXNAME];

	/* U+FEFF Byte Order Mark in UTF8 */
	अटल स्थिर अचिन्हित अक्षर *utf8_bom = (अचिन्हित अक्षर *) "\xef\xbb\xbf";
	स्थिर अचिन्हित अक्षर *bomptr = utf8_bom;

	क्रम (;;) अणु
		पूर्णांक line, c = get_next_अक्षर();

		अगर (bomptr && *bomptr) अणु
			/* We are at the file beginning; skip UTF8-encoded BOM
			 * अगर present. Sane editors won't put this in on their
			 * own, but e.g. Winकरोws Notepad will करो it happily. */
			अगर ((अचिन्हित अक्षर) c == *bomptr) अणु
				bomptr++;
				जारी;
			पूर्ण अन्यथा अणु
				/* Do not tolerate partial BOM. */
				अगर (bomptr != utf8_bom)
					अवरोध;
				/* No BOM at file beginning. Cool. */
				bomptr = शून्य;
			पूर्ण
		पूर्ण
		अगर (c == '\n') अणु
			अगर (config_file_eof)
				वापस 0;
			comment = 0;
			जारी;
		पूर्ण
		अगर (comment || है_खाली(c))
			जारी;
		अगर (c == '#' || c == ';') अणु
			comment = 1;
			जारी;
		पूर्ण
		अगर (c == '[') अणु
			baselen = get_base_var(var);
			अगर (baselen <= 0)
				अवरोध;
			var[baselen++] = '.';
			var[baselen] = 0;
			जारी;
		पूर्ण
		अगर (!है_अक्षर(c))
			अवरोध;
		var[baselen] = छोटे(c);

		/*
		 * The get_value function might or might not reach the '\n',
		 * so saving the current line number क्रम error reporting.
		 */
		line = config_linenr;
		अगर (get_value(fn, data, var, baselen+1) < 0) अणु
			config_linenr = line;
			अवरोध;
		पूर्ण
	पूर्ण
	pr_err("bad config file line %d in %s\n", config_linenr, config_file_name);
	वापस -1;
पूर्ण

अटल पूर्णांक parse_unit_factor(स्थिर अक्षर *end, अचिन्हित दीर्घ *val)
अणु
	अगर (!*end)
		वापस 1;
	अन्यथा अगर (!strहालcmp(end, "k")) अणु
		*val *= 1024;
		वापस 1;
	पूर्ण
	अन्यथा अगर (!strहालcmp(end, "m")) अणु
		*val *= 1024 * 1024;
		वापस 1;
	पूर्ण
	अन्यथा अगर (!strहालcmp(end, "g")) अणु
		*val *= 1024 * 1024 * 1024;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक perf_parse_lदीर्घ(स्थिर अक्षर *value, दीर्घ दीर्घ *ret)
अणु
	अगर (value && *value) अणु
		अक्षर *end;
		दीर्घ दीर्घ val = म_से_दीर्घl(value, &end, 0);
		अचिन्हित दीर्घ factor = 1;

		अगर (!parse_unit_factor(end, &factor))
			वापस 0;
		*ret = val * factor;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक perf_parse_दीर्घ(स्थिर अक्षर *value, दीर्घ *ret)
अणु
	अगर (value && *value) अणु
		अक्षर *end;
		दीर्घ val = म_से_दीर्घ(value, &end, 0);
		अचिन्हित दीर्घ factor = 1;
		अगर (!parse_unit_factor(end, &factor))
			वापस 0;
		*ret = val * factor;
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bad_config(स्थिर अक्षर *name)
अणु
	अगर (config_file_name)
		pr_warning("bad config value for '%s' in %s, ignoring...\n", name, config_file_name);
	अन्यथा
		pr_warning("bad config value for '%s', ignoring...\n", name);
पूर्ण

पूर्णांक perf_config_u64(u64 *dest, स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	दीर्घ दीर्घ ret = 0;

	अगर (!perf_parse_lदीर्घ(value, &ret)) अणु
		bad_config(name);
		वापस -1;
	पूर्ण

	*dest = ret;
	वापस 0;
पूर्ण

पूर्णांक perf_config_पूर्णांक(पूर्णांक *dest, स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	दीर्घ ret = 0;
	अगर (!perf_parse_दीर्घ(value, &ret)) अणु
		bad_config(name);
		वापस -1;
	पूर्ण
	*dest = ret;
	वापस 0;
पूर्ण

पूर्णांक perf_config_u8(u8 *dest, स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	दीर्घ ret = 0;

	अगर (!perf_parse_दीर्घ(value, &ret)) अणु
		bad_config(name);
		वापस -1;
	पूर्ण
	*dest = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक perf_config_bool_or_पूर्णांक(स्थिर अक्षर *name, स्थिर अक्षर *value, पूर्णांक *is_bool)
अणु
	पूर्णांक ret;

	*is_bool = 1;
	अगर (!value)
		वापस 1;
	अगर (!*value)
		वापस 0;
	अगर (!strहालcmp(value, "true") || !strहालcmp(value, "yes") || !strहालcmp(value, "on"))
		वापस 1;
	अगर (!strहालcmp(value, "false") || !strहालcmp(value, "no") || !strहालcmp(value, "off"))
		वापस 0;
	*is_bool = 0;
	वापस perf_config_पूर्णांक(&ret, name, value) < 0 ? -1 : ret;
पूर्ण

पूर्णांक perf_config_bool(स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	पूर्णांक discard;
	वापस !!perf_config_bool_or_पूर्णांक(name, value, &discard);
पूर्ण

अटल स्थिर अक्षर *perf_config_स_नाम(स्थिर अक्षर *name, स्थिर अक्षर *value)
अणु
	अगर (!name)
		वापस शून्य;
	वापस value;
पूर्ण

अटल पूर्णांक perf_buildid_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	/* same dir क्रम all commands */
	अगर (!म_भेद(var, "buildid.dir")) अणु
		स्थिर अक्षर *dir = perf_config_स_नाम(var, value);

		अगर (!dir) अणु
			pr_err("Invalid buildid directory!\n");
			वापस -1;
		पूर्ण
		म_नकलन(buildid_dir, dir, MAXPATHLEN-1);
		buildid_dir[MAXPATHLEN-1] = '\0';
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_शेष_core_config(स्थिर अक्षर *var __maybe_unused,
				    स्थिर अक्षर *value __maybe_unused)
अणु
	अगर (!म_भेद(var, "core.proc-map-timeout"))
		proc_map_समयout = म_से_अदीर्घ(value, शून्य, 10);

	/* Add other config variables here. */
	वापस 0;
पूर्ण

अटल पूर्णांक perf_ui_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	/* Add other config variables here. */
	अगर (!म_भेद(var, "ui.show-headers"))
		symbol_conf.show_hist_headers = perf_config_bool(var, value);

	वापस 0;
पूर्ण

अटल पूर्णांक perf_stat_config(स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	अगर (!म_भेद(var, "stat.big-num"))
		perf_stat__set_big_num(perf_config_bool(var, value));

	अगर (!म_भेद(var, "stat.no-csv-summary"))
		perf_stat__set_no_csv_summary(perf_config_bool(var, value));

	अगर (!म_भेद(var, "stat.bpf-counter-events"))
		evsel__bpf_counter_events = strdup(value);

	/* Add other config variables here. */
	वापस 0;
पूर्ण

पूर्णांक perf_शेष_config(स्थिर अक्षर *var, स्थिर अक्षर *value,
			व्योम *dummy __maybe_unused)
अणु
	अगर (strstarts(var, "core."))
		वापस perf_शेष_core_config(var, value);

	अगर (strstarts(var, "hist."))
		वापस perf_hist_config(var, value);

	अगर (strstarts(var, "ui."))
		वापस perf_ui_config(var, value);

	अगर (strstarts(var, "call-graph."))
		वापस perf_callchain_config(var, value);

	अगर (strstarts(var, "llvm."))
		वापस perf_llvm_config(var, value);

	अगर (strstarts(var, "buildid."))
		वापस perf_buildid_config(var, value);

	अगर (strstarts(var, "stat."))
		वापस perf_stat_config(var, value);

	/* Add other config variables here. */
	वापस 0;
पूर्ण

अटल पूर्णांक perf_config_from_file(config_fn_t fn, स्थिर अक्षर *filename, व्योम *data)
अणु
	पूर्णांक ret;
	खाता *f = ख_खोलो(filename, "r");

	ret = -1;
	अगर (f) अणु
		config_file = f;
		config_file_name = filename;
		config_linenr = 1;
		config_file_eof = 0;
		ret = perf_parse_file(fn, data);
		ख_बंद(f);
		config_file_name = शून्य;
	पूर्ण
	वापस ret;
पूर्ण

स्थिर अक्षर *perf_etc_perfconfig(व्योम)
अणु
	अटल स्थिर अक्षर *प्रणाली_wide;
	अगर (!प्रणाली_wide)
		प्रणाली_wide = प्रणाली_path(ETC_PERFCONFIG);
	वापस प्रणाली_wide;
पूर्ण

अटल पूर्णांक perf_env_bool(स्थिर अक्षर *k, पूर्णांक def)
अणु
	स्थिर अक्षर *v = दो_पर्या(k);
	वापस v ? perf_config_bool(k, v) : def;
पूर्ण

पूर्णांक perf_config_प्रणाली(व्योम)
अणु
	वापस !perf_env_bool("PERF_CONFIG_NOSYSTEM", 0);
पूर्ण

पूर्णांक perf_config_global(व्योम)
अणु
	वापस !perf_env_bool("PERF_CONFIG_NOGLOBAL", 0);
पूर्ण

अटल अक्षर *home_perfconfig(व्योम)
अणु
	स्थिर अक्षर *home = शून्य;
	अक्षर *config;
	काष्ठा stat st;

	home = दो_पर्या("HOME");

	/*
	 * Skip पढ़ोing user config अगर:
	 *   - there is no place to पढ़ो it from (HOME)
	 *   - we are asked not to (PERF_CONFIG_NOGLOBAL=1)
	 */
	अगर (!home || !*home || !perf_config_global())
		वापस शून्य;

	config = strdup(mkpath("%s/.perfconfig", home));
	अगर (config == शून्य) अणु
		pr_warning("Not enough memory to process %s/.perfconfig, ignoring it.", home);
		वापस शून्य;
	पूर्ण

	अगर (stat(config, &st) < 0)
		जाओ out_मुक्त;

	अगर (st.st_uid && (st.st_uid != geteuid())) अणु
		pr_warning("File %s not owned by current user or root, ignoring it.", config);
		जाओ out_मुक्त;
	पूर्ण

	अगर (st.st_size)
		वापस config;

out_मुक्त:
	मुक्त(config);
	वापस शून्य;
पूर्ण

स्थिर अक्षर *perf_home_perfconfig(व्योम)
अणु
	अटल स्थिर अक्षर *config;
	अटल bool failed;

	config = failed ? शून्य : home_perfconfig();
	अगर (!config)
		failed = true;

	वापस config;
पूर्ण

अटल काष्ठा perf_config_section *find_section(काष्ठा list_head *sections,
						स्थिर अक्षर *section_name)
अणु
	काष्ठा perf_config_section *section;

	list_क्रम_each_entry(section, sections, node)
		अगर (!म_भेद(section->name, section_name))
			वापस section;

	वापस शून्य;
पूर्ण

अटल काष्ठा perf_config_item *find_config_item(स्थिर अक्षर *name,
						 काष्ठा perf_config_section *section)
अणु
	काष्ठा perf_config_item *item;

	list_क्रम_each_entry(item, &section->items, node)
		अगर (!म_भेद(item->name, name))
			वापस item;

	वापस शून्य;
पूर्ण

अटल काष्ठा perf_config_section *add_section(काष्ठा list_head *sections,
					       स्थिर अक्षर *section_name)
अणु
	काष्ठा perf_config_section *section = zalloc(माप(*section));

	अगर (!section)
		वापस शून्य;

	INIT_LIST_HEAD(&section->items);
	section->name = strdup(section_name);
	अगर (!section->name) अणु
		pr_debug("%s: strdup failed\n", __func__);
		मुक्त(section);
		वापस शून्य;
	पूर्ण

	list_add_tail(&section->node, sections);
	वापस section;
पूर्ण

अटल काष्ठा perf_config_item *add_config_item(काष्ठा perf_config_section *section,
						स्थिर अक्षर *name)
अणु
	काष्ठा perf_config_item *item = zalloc(माप(*item));

	अगर (!item)
		वापस शून्य;

	item->name = strdup(name);
	अगर (!item->name) अणु
		pr_debug("%s: strdup failed\n", __func__);
		मुक्त(item);
		वापस शून्य;
	पूर्ण

	list_add_tail(&item->node, &section->items);
	वापस item;
पूर्ण

अटल पूर्णांक set_value(काष्ठा perf_config_item *item, स्थिर अक्षर *value)
अणु
	अक्षर *val = strdup(value);

	अगर (!val)
		वापस -1;

	zमुक्त(&item->value);
	item->value = val;
	वापस 0;
पूर्ण

अटल पूर्णांक collect_config(स्थिर अक्षर *var, स्थिर अक्षर *value,
			  व्योम *perf_config_set)
अणु
	पूर्णांक ret = -1;
	अक्षर *ptr, *key;
	अक्षर *section_name, *name;
	काष्ठा perf_config_section *section = शून्य;
	काष्ठा perf_config_item *item = शून्य;
	काष्ठा perf_config_set *set = perf_config_set;
	काष्ठा list_head *sections;

	अगर (set == शून्य)
		वापस -1;

	sections = &set->sections;
	key = ptr = strdup(var);
	अगर (!key) अणु
		pr_debug("%s: strdup failed\n", __func__);
		वापस -1;
	पूर्ण

	section_name = strsep(&ptr, ".");
	name = ptr;
	अगर (name == शून्य || value == शून्य)
		जाओ out_मुक्त;

	section = find_section(sections, section_name);
	अगर (!section) अणु
		section = add_section(sections, section_name);
		अगर (!section)
			जाओ out_मुक्त;
	पूर्ण

	item = find_config_item(name, section);
	अगर (!item) अणु
		item = add_config_item(section, name);
		अगर (!item)
			जाओ out_मुक्त;
	पूर्ण

	/* perf_config_set can contain both user and प्रणाली config items.
	 * So we should know where each value is from.
	 * The classअगरication would be needed when a particular config file
	 * is overwritten by setting feature i.e. set_config().
	 */
	अगर (म_भेद(config_file_name, perf_etc_perfconfig()) == 0) अणु
		section->from_प्रणाली_config = true;
		item->from_प्रणाली_config = true;
	पूर्ण अन्यथा अणु
		section->from_प्रणाली_config = false;
		item->from_प्रणाली_config = false;
	पूर्ण

	ret = set_value(item, value);

out_मुक्त:
	मुक्त(key);
	वापस ret;
पूर्ण

पूर्णांक perf_config_set__collect(काष्ठा perf_config_set *set, स्थिर अक्षर *file_name,
			     स्थिर अक्षर *var, स्थिर अक्षर *value)
अणु
	config_file_name = file_name;
	वापस collect_config(var, value, set);
पूर्ण

अटल पूर्णांक perf_config_set__init(काष्ठा perf_config_set *set)
अणु
	पूर्णांक ret = -1;

	/* Setting $PERF_CONFIG makes perf पढ़ो _only_ the given config file. */
	अगर (config_exclusive_filename)
		वापस perf_config_from_file(collect_config, config_exclusive_filename, set);
	अगर (perf_config_प्रणाली() && !access(perf_etc_perfconfig(), R_OK)) अणु
		अगर (perf_config_from_file(collect_config, perf_etc_perfconfig(), set) < 0)
			जाओ out;
	पूर्ण
	अगर (perf_config_global() && perf_home_perfconfig()) अणु
		अगर (perf_config_from_file(collect_config, perf_home_perfconfig(), set) < 0)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

काष्ठा perf_config_set *perf_config_set__new(व्योम)
अणु
	काष्ठा perf_config_set *set = zalloc(माप(*set));

	अगर (set) अणु
		INIT_LIST_HEAD(&set->sections);
		perf_config_set__init(set);
	पूर्ण

	वापस set;
पूर्ण

काष्ठा perf_config_set *perf_config_set__load_file(स्थिर अक्षर *file)
अणु
	काष्ठा perf_config_set *set = zalloc(माप(*set));

	अगर (set) अणु
		INIT_LIST_HEAD(&set->sections);
		perf_config_from_file(collect_config, file, set);
	पूर्ण

	वापस set;
पूर्ण

अटल पूर्णांक perf_config__init(व्योम)
अणु
	अगर (config_set == शून्य)
		config_set = perf_config_set__new();

	वापस config_set == शून्य;
पूर्ण

पूर्णांक perf_config_set(काष्ठा perf_config_set *set,
		    config_fn_t fn, व्योम *data)
अणु
	पूर्णांक ret = 0;
	अक्षर key[बफ_मान];
	काष्ठा perf_config_section *section;
	काष्ठा perf_config_item *item;

	perf_config_set__क्रम_each_entry(set, section, item) अणु
		अक्षर *value = item->value;

		अगर (value) अणु
			scnम_लिखो(key, माप(key), "%s.%s",
				  section->name, item->name);
			ret = fn(key, value, data);
			अगर (ret < 0) अणु
				pr_err("Error: wrong config key-value pair %s=%s\n",
				       key, value);
				/*
				 * Can't be just a 'break', as perf_config_set__क्रम_each_entry()
				 * expands to two nested क्रम() loops.
				 */
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक perf_config(config_fn_t fn, व्योम *data)
अणु
	अगर (config_set == शून्य && perf_config__init())
		वापस -1;

	वापस perf_config_set(config_set, fn, data);
पूर्ण

व्योम perf_config__निकास(व्योम)
अणु
	perf_config_set__delete(config_set);
	config_set = शून्य;
पूर्ण

व्योम perf_config__refresh(व्योम)
अणु
	perf_config__निकास();
	perf_config__init();
पूर्ण

अटल व्योम perf_config_item__delete(काष्ठा perf_config_item *item)
अणु
	zमुक्त(&item->name);
	zमुक्त(&item->value);
	मुक्त(item);
पूर्ण

अटल व्योम perf_config_section__purge(काष्ठा perf_config_section *section)
अणु
	काष्ठा perf_config_item *item, *पंचांगp;

	list_क्रम_each_entry_safe(item, पंचांगp, &section->items, node) अणु
		list_del_init(&item->node);
		perf_config_item__delete(item);
	पूर्ण
पूर्ण

अटल व्योम perf_config_section__delete(काष्ठा perf_config_section *section)
अणु
	perf_config_section__purge(section);
	zमुक्त(&section->name);
	मुक्त(section);
पूर्ण

अटल व्योम perf_config_set__purge(काष्ठा perf_config_set *set)
अणु
	काष्ठा perf_config_section *section, *पंचांगp;

	list_क्रम_each_entry_safe(section, पंचांगp, &set->sections, node) अणु
		list_del_init(&section->node);
		perf_config_section__delete(section);
	पूर्ण
पूर्ण

व्योम perf_config_set__delete(काष्ठा perf_config_set *set)
अणु
	अगर (set == शून्य)
		वापस;

	perf_config_set__purge(set);
	मुक्त(set);
पूर्ण

/*
 * Call this to report error क्रम your variable that should not
 * get a boolean value (i.e. "[my] var" means "true").
 */
पूर्णांक config_error_nonbool(स्थिर अक्षर *var)
अणु
	pr_err("Missing value for '%s'", var);
	वापस -1;
पूर्ण

व्योम set_buildid_dir(स्थिर अक्षर *dir)
अणु
	अगर (dir)
		scnम_लिखो(buildid_dir, MAXPATHLEN, "%s", dir);

	/* शेष to $HOME/.debug */
	अगर (buildid_dir[0] == '\0') अणु
		अक्षर *home = दो_पर्या("HOME");

		अगर (home) अणु
			snम_लिखो(buildid_dir, MAXPATHLEN, "%s/%s",
				 home, DEBUG_CACHE_सूची);
		पूर्ण अन्यथा अणु
			म_नकलन(buildid_dir, DEBUG_CACHE_सूची, MAXPATHLEN-1);
		पूर्ण
		buildid_dir[MAXPATHLEN-1] = '\0';
	पूर्ण
	/* क्रम communicating with बाह्यal commands */
	setenv("PERF_BUILDID_DIR", buildid_dir, 1);
पूर्ण
