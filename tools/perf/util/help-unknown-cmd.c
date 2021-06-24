<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "cache.h"
#समावेश "config.h"
#समावेश <poll.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <subcmd/help.h>
#समावेश "../builtin.h"
#समावेश "levenshtein.h"
#समावेश <linux/zभाग.स>

अटल पूर्णांक स्वतःcorrect;

अटल पूर्णांक perf_unknown_cmd_config(स्थिर अक्षर *var, स्थिर अक्षर *value,
				   व्योम *cb __maybe_unused)
अणु
	अगर (!म_भेद(var, "help.autocorrect"))
		वापस perf_config_पूर्णांक(&स्वतःcorrect, var,value);

	वापस 0;
पूर्ण

अटल पूर्णांक levenshtein_compare(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा cmdname *स्थिर *c1 = p1, *स्थिर *c2 = p2;
	स्थिर अक्षर *s1 = (*c1)->name, *s2 = (*c2)->name;
	पूर्णांक l1 = (*c1)->len;
	पूर्णांक l2 = (*c2)->len;
	वापस l1 != l2 ? l1 - l2 : म_भेद(s1, s2);
पूर्ण

अटल पूर्णांक add_cmd_list(काष्ठा cmdnames *cmds, काष्ठा cmdnames *old)
अणु
	अचिन्हित पूर्णांक i, nr = cmds->cnt + old->cnt;
	व्योम *पंचांगp;

	अगर (nr > cmds->alloc) अणु
		/* Choose bigger one to alloc */
		अगर (alloc_nr(cmds->alloc) < nr)
			cmds->alloc = nr;
		अन्यथा
			cmds->alloc = alloc_nr(cmds->alloc);
		पंचांगp = पुनः_स्मृति(cmds->names, cmds->alloc * माप(*cmds->names));
		अगर (!पंचांगp)
			वापस -1;
		cmds->names = पंचांगp;
	पूर्ण
	क्रम (i = 0; i < old->cnt; i++)
		cmds->names[cmds->cnt++] = old->names[i];
	zमुक्त(&old->names);
	old->cnt = 0;
	वापस 0;
पूर्ण

स्थिर अक्षर *help_unknown_cmd(स्थिर अक्षर *cmd)
अणु
	अचिन्हित पूर्णांक i, n = 0, best_similarity = 0;
	काष्ठा cmdnames मुख्य_cmds, other_cmds;

	स_रखो(&मुख्य_cmds, 0, माप(मुख्य_cmds));
	स_रखो(&other_cmds, 0, माप(मुख्य_cmds));

	perf_config(perf_unknown_cmd_config, शून्य);

	load_command_list("perf-", &मुख्य_cmds, &other_cmds);

	अगर (add_cmd_list(&मुख्य_cmds, &other_cmds) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "ERROR: Failed to allocate command list for unknown command.\n");
		जाओ end;
	पूर्ण
	क्विक(मुख्य_cmds.names, मुख्य_cmds.cnt,
	      माप(मुख्य_cmds.names), cmdname_compare);
	uniq(&मुख्य_cmds);

	अगर (मुख्य_cmds.cnt) अणु
		/* This reuses cmdname->len क्रम similarity index */
		क्रम (i = 0; i < मुख्य_cmds.cnt; ++i)
			मुख्य_cmds.names[i]->len =
				levenshtein(cmd, मुख्य_cmds.names[i]->name, 0, 2, 1, 4);

		क्विक(मुख्य_cmds.names, मुख्य_cmds.cnt,
		      माप(*मुख्य_cmds.names), levenshtein_compare);

		best_similarity = मुख्य_cmds.names[0]->len;
		n = 1;
		जबतक (n < मुख्य_cmds.cnt && best_similarity == मुख्य_cmds.names[n]->len)
			++n;
	पूर्ण

	अगर (स्वतःcorrect && n == 1) अणु
		स्थिर अक्षर *assumed = मुख्य_cmds.names[0]->name;

		मुख्य_cmds.names[0] = शून्य;
		clean_cmdnames(&मुख्य_cmds);
		ख_लिखो(मानक_त्रुटि, "WARNING: You called a perf program named '%s', "
			"which does not exist.\n"
			"Continuing under the assumption that you meant '%s'\n",
			cmd, assumed);
		अगर (स्वतःcorrect > 0) अणु
			ख_लिखो(मानक_त्रुटि, "in %0.1f seconds automatically...\n",
				(भग्न)स्वतःcorrect/10.0);
			poll(शून्य, 0, स्वतःcorrect * 100);
		पूर्ण
		वापस assumed;
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "perf: '%s' is not a perf-command. See 'perf --help'.\n", cmd);

	अगर (मुख्य_cmds.cnt && best_similarity < 6) अणु
		ख_लिखो(मानक_त्रुटि, "\nDid you mean %s?\n",
			n < 2 ? "this": "one of these");

		क्रम (i = 0; i < n; i++)
			ख_लिखो(मानक_त्रुटि, "\t%s\n", मुख्य_cmds.names[i]->name);
	पूर्ण
end:
	निकास(1);
पूर्ण
