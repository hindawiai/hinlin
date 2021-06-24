<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <pthपढ़ो.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>

#समावेश "../helpline.h"
#समावेश "../ui.h"
#समावेश "../libslang.h"

अक्षर ui_helpline__last_msg[1024];
bool tui_helpline__set;

अटल व्योम tui_helpline__pop(व्योम)
अणु
पूर्ण

अटल व्योम tui_helpline__push(स्थिर अक्षर *msg)
अणु
	स्थिर माप_प्रकार sz = माप(ui_helpline__current);

	SLsmg_जाओrc(SLtt_Screen_Rows - 1, 0);
	SLsmg_set_color(0);
	SLsmg_ग_लिखो_nstring((अक्षर *)msg, SLtt_Screen_Cols);
	SLsmg_refresh();
	strlcpy(ui_helpline__current, msg, sz);
पूर्ण

अटल पूर्णांक tui_helpline__show(स्थिर अक्षर *क्रमmat, बहु_सूची ap)
अणु
	पूर्णांक ret;
	अटल पूर्णांक backlog;

	pthपढ़ो_mutex_lock(&ui__lock);
	ret = vscnम_लिखो(ui_helpline__last_msg + backlog,
			माप(ui_helpline__last_msg) - backlog, क्रमmat, ap);
	backlog += ret;

	tui_helpline__set = true;

	अगर (ui_helpline__last_msg[backlog - 1] == '\n') अणु
		ui_helpline__माला_दो(ui_helpline__last_msg);
		SLsmg_refresh();
		backlog = 0;
	पूर्ण
	pthपढ़ो_mutex_unlock(&ui__lock);

	वापस ret;
पूर्ण

काष्ठा ui_helpline tui_helpline_fns = अणु
	.pop	= tui_helpline__pop,
	.push	= tui_helpline__push,
	.show	= tui_helpline__show,
पूर्ण;

व्योम ui_helpline__init(व्योम)
अणु
	helpline_fns = &tui_helpline_fns;
	ui_helpline__माला_दो(" ");
पूर्ण
