<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <pthपढ़ो.h>
#समावेश <dlfcn.h>
#समावेश <unistd.h>

#समावेश <subcmd/pager.h>
#समावेश "../util/debug.h"
#समावेश "../util/hist.h"
#समावेश "ui.h"

pthपढ़ो_mutex_t ui__lock = PTHREAD_MUTEX_INITIALIZER;
व्योम *perf_gtk_handle;
पूर्णांक use_browser = -1;

#घोषणा PERF_GTK_DSO "libperf-gtk.so"

#अगर_घोषित HAVE_GTK2_SUPPORT

अटल पूर्णांक setup_gtk_browser(व्योम)
अणु
	पूर्णांक (*perf_ui_init)(व्योम);

	अगर (perf_gtk_handle)
		वापस 0;

	perf_gtk_handle = dlखोलो(PERF_GTK_DSO, RTLD_LAZY);
	अगर (perf_gtk_handle == शून्य) अणु
		अक्षर buf[PATH_MAX];
		scnम_लिखो(buf, माप(buf), "%s/%s", LIBसूची, PERF_GTK_DSO);
		perf_gtk_handle = dlखोलो(buf, RTLD_LAZY);
	पूर्ण
	अगर (perf_gtk_handle == शून्य)
		वापस -1;

	perf_ui_init = dlsym(perf_gtk_handle, "perf_gtk__init");
	अगर (perf_ui_init == शून्य)
		जाओ out_बंद;

	अगर (perf_ui_init() == 0)
		वापस 0;

out_बंद:
	dlबंद(perf_gtk_handle);
	वापस -1;
पूर्ण

अटल व्योम निकास_gtk_browser(bool रुको_क्रम_ok)
अणु
	व्योम (*perf_ui_निकास)(bool);

	अगर (perf_gtk_handle == शून्य)
		वापस;

	perf_ui_निकास = dlsym(perf_gtk_handle, "perf_gtk__exit");
	अगर (perf_ui_निकास == शून्य)
		जाओ out_बंद;

	perf_ui_निकास(रुको_क्रम_ok);

out_बंद:
	dlबंद(perf_gtk_handle);

	perf_gtk_handle = शून्य;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक setup_gtk_browser(व्योम) अणु वापस -1; पूर्ण
अटल अंतरभूत व्योम निकास_gtk_browser(bool रुको_क्रम_ok __maybe_unused) अणुपूर्ण
#पूर्ण_अगर

पूर्णांक stdio__config_color(स्थिर काष्ठा option *opt __maybe_unused,
			स्थिर अक्षर *mode, पूर्णांक unset __maybe_unused)
अणु
	perf_use_color_शेष = perf_config_colorbool("color.ui", mode, -1);
	वापस 0;
पूर्ण

व्योम setup_browser(bool fallback_to_pager)
अणु
	अगर (use_browser < 2 && (!isatty(1) || dump_trace))
		use_browser = 0;

	/* शेष to TUI */
	अगर (use_browser < 0)
		use_browser = 1;

	चयन (use_browser) अणु
	हाल 2:
		अगर (setup_gtk_browser() == 0)
			अवरोध;
		म_लिखो("GTK browser requested but could not find %s\n",
		       PERF_GTK_DSO);
		sleep(1);
		use_browser = 1;
		/* fall through */
	हाल 1:
		अगर (ui__init() == 0)
			अवरोध;
		/* fall through */
	शेष:
		use_browser = 0;
		अगर (fallback_to_pager)
			setup_pager();
		अवरोध;
	पूर्ण
पूर्ण

व्योम निकास_browser(bool रुको_क्रम_ok)
अणु
	चयन (use_browser) अणु
	हाल 2:
		निकास_gtk_browser(रुको_क्रम_ok);
		अवरोध;

	हाल 1:
		ui__निकास(रुको_क्रम_ok);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण
