<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../../builtin.h"
#समावेश "../../perf.h"
#समावेश "../../util/util.h" // perf_exe()
#समावेश "../util.h"
#समावेश "../../util/hist.h"
#समावेश "../../util/debug.h"
#समावेश "../../util/symbol.h"
#समावेश "../browser.h"
#समावेश "../libslang.h"
#समावेश "config.h"
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <मानककोष.स>

#घोषणा SCRIPT_NAMELEN	128
#घोषणा SCRIPT_MAX_NO	64
/*
 * Usually the full path क्रम a script is:
 *	/home/username/libexec/perf-core/scripts/python/xxx.py
 *	/home/username/libexec/perf-core/scripts/perl/xxx.pl
 * So 256 should be दीर्घ enough to contain the full path.
 */
#घोषणा SCRIPT_FULLPATH_LEN	256

काष्ठा script_config अणु
	स्थिर अक्षर **names;
	अक्षर **paths;
	पूर्णांक index;
	स्थिर अक्षर *perf;
	अक्षर extra_क्रमmat[256];
पूर्ण;

व्योम attr_to_script(अक्षर *extra_क्रमmat, काष्ठा perf_event_attr *attr)
अणु
	extra_क्रमmat[0] = 0;
	अगर (attr->पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		म_जोड़ो(extra_क्रमmat, " -F +metric");
	अगर (attr->sample_type & PERF_SAMPLE_BRANCH_STACK)
		म_जोड़ो(extra_क्रमmat, " -F +brstackinsn --xed");
	अगर (attr->sample_type & PERF_SAMPLE_REGS_INTR)
		म_जोड़ो(extra_क्रमmat, " -F +iregs");
	अगर (attr->sample_type & PERF_SAMPLE_REGS_USER)
		म_जोड़ो(extra_क्रमmat, " -F +uregs");
	अगर (attr->sample_type & PERF_SAMPLE_PHYS_ADDR)
		म_जोड़ो(extra_क्रमmat, " -F +phys_addr");
पूर्ण

अटल पूर्णांक add_script_option(स्थिर अक्षर *name, स्थिर अक्षर *opt,
			     काष्ठा script_config *c)
अणु
	c->names[c->index] = name;
	अगर (aप्र_लिखो(&c->paths[c->index],
		     "%s script %s -F +metric %s %s",
		     c->perf, opt, symbol_conf.अंतरभूत_name ? " --inline" : "",
		     c->extra_क्रमmat) < 0)
		वापस -1;
	c->index++;
	वापस 0;
पूर्ण

अटल पूर्णांक scripts_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data)
अणु
	काष्ठा script_config *c = data;

	अगर (!strstarts(var, "scripts."))
		वापस -1;
	अगर (c->index >= SCRIPT_MAX_NO)
		वापस -1;
	c->names[c->index] = strdup(var + 7);
	अगर (!c->names[c->index])
		वापस -1;
	अगर (aप्र_लिखो(&c->paths[c->index], "%s %s", value,
		     c->extra_क्रमmat) < 0)
		वापस -1;
	c->index++;
	वापस 0;
पूर्ण

/*
 * When success, will copy the full path of the selected script
 * पूर्णांकo  the buffer poपूर्णांकed by script_name, and वापस 0.
 * Return -1 on failure.
 */
अटल पूर्णांक list_scripts(अक्षर *script_name, bool *custom,
			काष्ठा evsel *evsel)
अणु
	अक्षर *buf, *paths[SCRIPT_MAX_NO], *names[SCRIPT_MAX_NO];
	पूर्णांक i, num, choice;
	पूर्णांक ret = 0;
	पूर्णांक max_std, custom_perf;
	अक्षर pbuf[256];
	स्थिर अक्षर *perf = perf_exe(pbuf, माप pbuf);
	काष्ठा script_config scriptc = अणु
		.names = (स्थिर अक्षर **)names,
		.paths = paths,
		.perf = perf
	पूर्ण;

	script_name[0] = 0;

	/* Preset the script name to SCRIPT_NAMELEN */
	buf = दो_स्मृति(SCRIPT_MAX_NO * (SCRIPT_NAMELEN + SCRIPT_FULLPATH_LEN));
	अगर (!buf)
		वापस -1;

	अगर (evsel)
		attr_to_script(scriptc.extra_क्रमmat, &evsel->core.attr);
	add_script_option("Show individual samples", "", &scriptc);
	add_script_option("Show individual samples with assembler", "-F +insn --xed",
			  &scriptc);
	add_script_option("Show individual samples with source", "-F +srcline,+srccode",
			  &scriptc);
	perf_config(scripts_config, &scriptc);
	custom_perf = scriptc.index;
	add_script_option("Show samples with custom perf script arguments", "", &scriptc);
	i = scriptc.index;
	max_std = i;

	क्रम (; i < SCRIPT_MAX_NO; i++) अणु
		names[i] = buf + (i - max_std) * (SCRIPT_NAMELEN + SCRIPT_FULLPATH_LEN);
		paths[i] = names[i] + SCRIPT_NAMELEN;
	पूर्ण

	num = find_scripts(names + max_std, paths + max_std, SCRIPT_MAX_NO - max_std,
			SCRIPT_FULLPATH_LEN);
	अगर (num < 0)
		num = 0;
	choice = ui__popup_menu(num + max_std, (अक्षर * स्थिर *)names, शून्य);
	अगर (choice < 0) अणु
		ret = -1;
		जाओ out;
	पूर्ण
	अगर (choice == custom_perf) अणु
		अक्षर script_args[50];
		पूर्णांक key = ui_browser__input_winकरोw("perf script command",
				"Enter perf script command line (without perf script prefix)",
				script_args, "", 0);
		अगर (key != K_ENTER) अणु
			ret = -1;
			जाओ out;
		पूर्ण
		प्र_लिखो(script_name, "%s script %s", perf, script_args);
	पूर्ण अन्यथा अगर (choice < num + max_std) अणु
		म_नकल(script_name, paths[choice]);
	पूर्ण
	*custom = choice >= max_std;

out:
	मुक्त(buf);
	क्रम (i = 0; i < max_std; i++)
		zमुक्त(&paths[i]);
	वापस ret;
पूर्ण

व्योम run_script(अक्षर *cmd)
अणु
	pr_debug("Running %s\n", cmd);
	SLang_reset_tty();
	अगर (प्रणाली(cmd) < 0)
		pr_warning("Cannot run %s\n", cmd);
	/*
	 * SLang करोesn't seem to reset the whole terminal, so be more
	 * क्रमceful to get back to the original state.
	 */
	म_लिखो("\033[c\033[H\033[J");
	ख_साफ(मानक_निकास);
	SLang_init_tty(0, 0, 0);
	SLsmg_refresh();
पूर्ण

पूर्णांक script_browse(स्थिर अक्षर *script_opt, काष्ठा evsel *evsel)
अणु
	अक्षर *cmd, script_name[SCRIPT_FULLPATH_LEN];
	bool custom = false;

	स_रखो(script_name, 0, SCRIPT_FULLPATH_LEN);
	अगर (list_scripts(script_name, &custom, evsel))
		वापस -1;

	अगर (aप्र_लिखो(&cmd, "%s%s %s %s%s 2>&1 | less",
			custom ? "perf script -s " : "",
			script_name,
			script_opt ? script_opt : "",
			input_name ? "-i " : "",
			input_name ? input_name : "") < 0)
		वापस -1;

	run_script(cmd);
	मुक्त(cmd);

	वापस 0;
पूर्ण
