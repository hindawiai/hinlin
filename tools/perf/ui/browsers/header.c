<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "ui/browser.h"
#समावेश "ui/keysyms.h"
#समावेश "ui/ui.h"
#समावेश "ui/util.h"
#समावेश "ui/libslang.h"
#समावेश "util/header.h"
#समावेश "util/session.h"

#समावेश <sys/ttyशेषs.h>

अटल व्योम ui_browser__argv_ग_लिखो(काष्ठा ui_browser *browser,
				   व्योम *entry, पूर्णांक row)
अणु
	अक्षर **arg = entry;
	अक्षर *str = *arg;
	अक्षर empty[] = " ";
	bool current_entry = ui_browser__is_current_entry(browser, row);
	अचिन्हित दीर्घ offset = (अचिन्हित दीर्घ)browser->priv;

	अगर (offset >= म_माप(str))
		str = empty;
	अन्यथा
		str = str + offset;

	ui_browser__set_color(browser, current_entry ? HE_COLORSET_SELECTED :
						       HE_COLORSET_NORMAL);

	ui_browser__ग_लिखो_nstring(browser, str, browser->width);
पूर्ण

अटल पूर्णांक list_menu__run(काष्ठा ui_browser *menu)
अणु
	पूर्णांक key;
	अचिन्हित दीर्घ offset;
	अटल स्थिर अक्षर help[] =
	"h/?/F1        Show this window\n"
	"UP/DOWN/PGUP\n"
	"PGDN/SPACE\n"
	"LEFT/RIGHT    Navigate\n"
	"q/ESC/CTRL+C  Exit browser";

	अगर (ui_browser__show(menu, "Header information", "Press 'q' to exit") < 0)
		वापस -1;

	जबतक (1) अणु
		key = ui_browser__run(menu, 0);

		चयन (key) अणु
		हाल K_RIGHT:
			offset = (अचिन्हित दीर्घ)menu->priv;
			offset += 10;
			menu->priv = (व्योम *)offset;
			जारी;
		हाल K_LEFT:
			offset = (अचिन्हित दीर्घ)menu->priv;
			अगर (offset >= 10)
				offset -= 10;
			menu->priv = (व्योम *)offset;
			जारी;
		हाल K_F1:
		हाल 'h':
		हाल '?':
			ui_browser__help_winकरोw(menu, help);
			जारी;
		हाल K_ESC:
		हाल 'q':
		हाल CTRL('c'):
			key = -1;
			अवरोध;
		शेष:
			जारी;
		पूर्ण

		अवरोध;
	पूर्ण

	ui_browser__hide(menu);
	वापस key;
पूर्ण

अटल पूर्णांक ui__list_menu(पूर्णांक argc, अक्षर * स्थिर argv[])
अणु
	काष्ठा ui_browser menu = अणु
		.entries    = (व्योम *)argv,
		.refresh    = ui_browser__argv_refresh,
		.seek	    = ui_browser__argv_seek,
		.ग_लिखो	    = ui_browser__argv_ग_लिखो,
		.nr_entries = argc,
	पूर्ण;

	वापस list_menu__run(&menu);
पूर्ण

पूर्णांक tui__header_winकरोw(काष्ठा perf_env *env)
अणु
	पूर्णांक i, argc = 0;
	अक्षर **argv;
	काष्ठा perf_session *session;
	अक्षर *ptr, *pos;
	माप_प्रकार size;
	खाता *fp = खोलो_memstream(&ptr, &size);

	session = container_of(env, काष्ठा perf_session, header.env);
	perf_header__ख_लिखो_info(session, fp, true);
	ख_बंद(fp);

	क्रम (pos = ptr, argc = 0; (pos = म_अक्षर(pos, '\n')) != शून्य; pos++)
		argc++;

	argv = सुस्मृति(argc + 1, माप(*argv));
	अगर (argv == शून्य)
		जाओ out;

	argv[0] = pos = ptr;
	क्रम (i = 1; (pos = म_अक्षर(pos, '\n')) != शून्य; i++) अणु
		*pos++ = '\0';
		argv[i] = pos;
	पूर्ण

	BUG_ON(i != argc + 1);

	ui__list_menu(argc, argv);

out:
	मुक्त(argv);
	मुक्त(ptr);
	वापस 0;
पूर्ण
