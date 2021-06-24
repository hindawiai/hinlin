<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Display a menu with inभागidual samples to browse with perf script */
#समावेश "hist.h"
#समावेश "evsel.h"
#समावेश "hists.h"
#समावेश "sort.h"
#समावेश "config.h"
#समावेश "time-utils.h"
#समावेश "../util.h"
#समावेश "../../util/util.h" // perf_exe()
#समावेश "../../perf.h"
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>

अटल u64 context_len = 10 * NSEC_PER_MSEC;

अटल पूर्णांक res_sample_config(स्थिर अक्षर *var, स्थिर अक्षर *value, व्योम *data __maybe_unused)
अणु
	अगर (!म_भेद(var, "samples.context"))
		वापस perf_config_u64(&context_len, var, value);
	वापस 0;
पूर्ण

व्योम res_sample_init(व्योम)
अणु
	perf_config(res_sample_config, शून्य);
पूर्ण

पूर्णांक res_sample_browse(काष्ठा res_sample *res_samples, पूर्णांक num_res,
		      काष्ठा evsel *evsel, क्रमागत rstype rstype)
अणु
	अक्षर **names;
	पूर्णांक i, n;
	पूर्णांक choice;
	अक्षर *cmd;
	अक्षर pbuf[256], tidbuf[32], cpubuf[32];
	स्थिर अक्षर *perf = perf_exe(pbuf, माप pbuf);
	अक्षर trange[128], tsample[64];
	काष्ठा res_sample *r;
	अक्षर extra_क्रमmat[256];

	names = सुस्मृति(num_res, माप(अक्षर *));
	अगर (!names)
		वापस -1;
	क्रम (i = 0; i < num_res; i++) अणु
		अक्षर tbuf[64];

		बारtamp__scnम_लिखो_nsec(res_samples[i].समय, tbuf, माप tbuf);
		अगर (aप्र_लिखो(&names[i], "%s: CPU %d tid %d", tbuf,
			     res_samples[i].cpu, res_samples[i].tid) < 0) अणु
			जबतक (--i >= 0)
				zमुक्त(&names[i]);
			मुक्त(names);
			वापस -1;
		पूर्ण
	पूर्ण
	choice = ui__popup_menu(num_res, names, शून्य);
	क्रम (i = 0; i < num_res; i++)
		zमुक्त(&names[i]);
	मुक्त(names);

	अगर (choice < 0 || choice >= num_res)
		वापस -1;
	r = &res_samples[choice];

	n = बारtamp__scnम_लिखो_nsec(r->समय - context_len, trange, माप trange);
	trange[n++] = ',';
	बारtamp__scnम_लिखो_nsec(r->समय + context_len, trange + n, माप trange - n);

	बारtamp__scnम_लिखो_nsec(r->समय, tsample, माप tsample);

	attr_to_script(extra_क्रमmat, &evsel->core.attr);

	अगर (aप्र_लिखो(&cmd, "%s script %s%s --time %s %s%s %s%s --ns %s %s %s %s %s | less +/%s",
		     perf,
		     input_name ? "-i " : "",
		     input_name ? input_name : "",
		     trange,
		     r->cpu >= 0 ? "--cpu " : "",
		     r->cpu >= 0 ? (प्र_लिखो(cpubuf, "%d", r->cpu), cpubuf) : "",
		     r->tid ? "--tid " : "",
		     r->tid ? (प्र_लिखो(tidbuf, "%d", r->tid), tidbuf) : "",
		     extra_क्रमmat,
		     rstype == A_ASM ? "-F +insn --xed" :
		     rstype == A_SOURCE ? "-F +srcline,+srccode" : "",
		     symbol_conf.अंतरभूत_name ? "--inline" : "",
		     "--show-lost-events ",
		     r->tid ? "--show-switch-events --show-task-events " : "",
		     tsample) < 0)
		वापस -1;
	run_script(cmd);
	मुक्त(cmd);
	वापस 0;
पूर्ण
