<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * trace-event-scripting.  Scripting engine common and initialization code.
 *
 * Copyright (C) 2009-2010 Tom Zanussi <tzanussi@gmail.com>
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <त्रुटिसं.स>

#समावेश "debug.h"
#समावेश "trace-event.h"
#समावेश <linux/zभाग.स>

काष्ठा scripting_context *scripting_context;

अटल पूर्णांक flush_script_unsupported(व्योम)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक stop_script_unsupported(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम process_event_unsupported(जोड़ perf_event *event __maybe_unused,
				      काष्ठा perf_sample *sample __maybe_unused,
				      काष्ठा evsel *evsel __maybe_unused,
				      काष्ठा addr_location *al __maybe_unused)
अणु
पूर्ण

अटल व्योम prपूर्णांक_python_unsupported_msg(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Python scripting not supported."
		"  Install libpython and rebuild perf to enable it.\n"
		"For example:\n  # apt-get install python-dev (ubuntu)"
		"\n  # yum install python-devel (Fedora)"
		"\n  etc.\n");
पूर्ण

अटल पूर्णांक python_start_script_unsupported(स्थिर अक्षर *script __maybe_unused,
					   पूर्णांक argc __maybe_unused,
					   स्थिर अक्षर **argv __maybe_unused)
अणु
	prपूर्णांक_python_unsupported_msg();

	वापस -1;
पूर्ण

अटल पूर्णांक python_generate_script_unsupported(काष्ठा tep_handle *pevent
					      __maybe_unused,
					      स्थिर अक्षर *outfile
					      __maybe_unused)
अणु
	prपूर्णांक_python_unsupported_msg();

	वापस -1;
पूर्ण

काष्ठा scripting_ops python_scripting_unsupported_ops = अणु
	.name = "Python",
	.start_script = python_start_script_unsupported,
	.flush_script = flush_script_unsupported,
	.stop_script = stop_script_unsupported,
	.process_event = process_event_unsupported,
	.generate_script = python_generate_script_unsupported,
पूर्ण;

अटल व्योम रेजिस्टर_python_scripting(काष्ठा scripting_ops *scripting_ops)
अणु
	अगर (scripting_context == शून्य)
		scripting_context = दो_स्मृति(माप(*scripting_context));

       अगर (scripting_context == शून्य ||
	   script_spec_रेजिस्टर("Python", scripting_ops) ||
	   script_spec_रेजिस्टर("py", scripting_ops)) अणु
		pr_err("Error registering Python script extension: disabling it\n");
		zमुक्त(&scripting_context);
	पूर्ण
पूर्ण

#अगर_अघोषित HAVE_LIBPYTHON_SUPPORT
व्योम setup_python_scripting(व्योम)
अणु
	रेजिस्टर_python_scripting(&python_scripting_unsupported_ops);
पूर्ण
#अन्यथा
बाह्य काष्ठा scripting_ops python_scripting_ops;

व्योम setup_python_scripting(व्योम)
अणु
	रेजिस्टर_python_scripting(&python_scripting_ops);
पूर्ण
#पूर्ण_अगर

अटल व्योम prपूर्णांक_perl_unsupported_msg(व्योम)
अणु
	ख_लिखो(मानक_त्रुटि, "Perl scripting not supported."
		"  Install libperl and rebuild perf to enable it.\n"
		"For example:\n  # apt-get install libperl-dev (ubuntu)"
		"\n  # yum install 'perl(ExtUtils::Embed)' (Fedora)"
		"\n  etc.\n");
पूर्ण

अटल पूर्णांक perl_start_script_unsupported(स्थिर अक्षर *script __maybe_unused,
					 पूर्णांक argc __maybe_unused,
					 स्थिर अक्षर **argv __maybe_unused)
अणु
	prपूर्णांक_perl_unsupported_msg();

	वापस -1;
पूर्ण

अटल पूर्णांक perl_generate_script_unsupported(काष्ठा tep_handle *pevent
					    __maybe_unused,
					    स्थिर अक्षर *outfile __maybe_unused)
अणु
	prपूर्णांक_perl_unsupported_msg();

	वापस -1;
पूर्ण

काष्ठा scripting_ops perl_scripting_unsupported_ops = अणु
	.name = "Perl",
	.start_script = perl_start_script_unsupported,
	.flush_script = flush_script_unsupported,
	.stop_script = stop_script_unsupported,
	.process_event = process_event_unsupported,
	.generate_script = perl_generate_script_unsupported,
पूर्ण;

अटल व्योम रेजिस्टर_perl_scripting(काष्ठा scripting_ops *scripting_ops)
अणु
	अगर (scripting_context == शून्य)
		scripting_context = दो_स्मृति(माप(*scripting_context));

       अगर (scripting_context == शून्य ||
	   script_spec_रेजिस्टर("Perl", scripting_ops) ||
	   script_spec_रेजिस्टर("pl", scripting_ops)) अणु
		pr_err("Error registering Perl script extension: disabling it\n");
		zमुक्त(&scripting_context);
	पूर्ण
पूर्ण

#अगर_अघोषित HAVE_LIBPERL_SUPPORT
व्योम setup_perl_scripting(व्योम)
अणु
	रेजिस्टर_perl_scripting(&perl_scripting_unsupported_ops);
पूर्ण
#अन्यथा
बाह्य काष्ठा scripting_ops perl_scripting_ops;

व्योम setup_perl_scripting(व्योम)
अणु
	रेजिस्टर_perl_scripting(&perl_scripting_ops);
पूर्ण
#पूर्ण_अगर
