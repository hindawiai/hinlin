<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <linux/kernel.h>

#समावेश "gtk.h"
#समावेश "../ui.h"
#समावेश "../helpline.h"

अटल व्योम gtk_helpline_pop(व्योम)
अणु
	अगर (!perf_gtk__is_active_context(pgctx))
		वापस;

	gtk_statusbar_pop(GTK_STATUSBAR(pgctx->statbar),
			  pgctx->statbar_ctx_id);
पूर्ण

अटल व्योम gtk_helpline_push(स्थिर अक्षर *msg)
अणु
	अगर (!perf_gtk__is_active_context(pgctx))
		वापस;

	gtk_statusbar_push(GTK_STATUSBAR(pgctx->statbar),
			   pgctx->statbar_ctx_id, msg);
पूर्ण

अटल पूर्णांक gtk_helpline_show(स्थिर अक्षर *fmt, बहु_सूची ap)
अणु
	पूर्णांक ret;
	अक्षर *ptr;
	अटल पूर्णांक backlog;

	ret = vscnम_लिखो(ui_helpline__current + backlog,
			 माप(ui_helpline__current) - backlog, fmt, ap);
	backlog += ret;

	/* only first line can be displayed */
	ptr = म_अक्षर(ui_helpline__current, '\n');
	अगर (ptr && (ptr - ui_helpline__current) <= backlog) अणु
		*ptr = '\0';
		ui_helpline__माला_दो(ui_helpline__current);
		backlog = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा ui_helpline gtk_helpline_fns = अणु
	.pop	= gtk_helpline_pop,
	.push	= gtk_helpline_push,
	.show	= gtk_helpline_show,
पूर्ण;

व्योम perf_gtk__init_helpline(व्योम)
अणु
	helpline_fns = &gtk_helpline_fns;
पूर्ण
