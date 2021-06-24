<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "gtk.h"
#समावेश <linux/compiler.h>
#समावेश "../util.h"

बाह्य काष्ठा perf_error_ops perf_gtk_eops;

पूर्णांक perf_gtk__init(व्योम)
अणु
	perf_error__रेजिस्टर(&perf_gtk_eops);
	perf_gtk__init_helpline();
	gtk_ui_progress__init();
	perf_gtk__init_hpp();

	वापस gtk_init_check(शून्य, शून्य) ? 0 : -1;
पूर्ण

व्योम perf_gtk__निकास(bool रुको_क्रम_ok __maybe_unused)
अणु
	अगर (!perf_gtk__is_active_context(pgctx))
		वापस;
	perf_error__unरेजिस्टर(&perf_gtk_eops);
	gtk_मुख्य_quit();
पूर्ण
