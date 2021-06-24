<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "../util.h"
#समावेश "gtk.h"

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <linux/zभाग.स>

काष्ठा perf_gtk_context *pgctx;

काष्ठा perf_gtk_context *perf_gtk__activate_context(GtkWidget *winकरोw)
अणु
	काष्ठा perf_gtk_context *ctx;

	ctx = दो_स्मृति(माप(*pgctx));
	अगर (ctx)
		ctx->मुख्य_winकरोw = winकरोw;

	वापस ctx;
पूर्ण

पूर्णांक perf_gtk__deactivate_context(काष्ठा perf_gtk_context **ctx)
अणु
	अगर (!perf_gtk__is_active_context(*ctx))
		वापस -1;

	zमुक्त(ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक perf_gtk__error(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *msg;
	GtkWidget *dialog;

	अगर (!perf_gtk__is_active_context(pgctx) ||
	    vaप्र_लिखो(&msg, क्रमmat, args) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Error:\n");
		भख_लिखो(मानक_त्रुटि, क्रमmat, args);
		ख_लिखो(मानक_त्रुटि, "\n");
		वापस -1;
	पूर्ण

	dialog = gtk_message_dialog_new_with_markup(GTK_WINDOW(pgctx->मुख्य_winकरोw),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_ERROR,
					GTK_BUTTONS_CLOSE,
					"<b>Error</b>\n\n%s", msg);
	gtk_dialog_run(GTK_DIALOG(dialog));

	gtk_widget_destroy(dialog);
	मुक्त(msg);
	वापस 0;
पूर्ण

#अगर_घोषित HAVE_GTK_INFO_BAR_SUPPORT
अटल पूर्णांक perf_gtk__warning_info_bar(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *msg;

	अगर (!perf_gtk__is_active_context(pgctx) ||
	    vaप्र_लिखो(&msg, क्रमmat, args) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Warning:\n");
		भख_लिखो(मानक_त्रुटि, क्रमmat, args);
		ख_लिखो(मानक_त्रुटि, "\n");
		वापस -1;
	पूर्ण

	gtk_label_set_text(GTK_LABEL(pgctx->message_label), msg);
	gtk_info_bar_set_message_type(GTK_INFO_BAR(pgctx->info_bar),
				      GTK_MESSAGE_WARNING);
	gtk_widget_show(pgctx->info_bar);

	मुक्त(msg);
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक perf_gtk__warning_statusbar(स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	अक्षर *msg, *p;

	अगर (!perf_gtk__is_active_context(pgctx) ||
	    vaप्र_लिखो(&msg, क्रमmat, args) < 0) अणु
		ख_लिखो(मानक_त्रुटि, "Warning:\n");
		भख_लिखो(मानक_त्रुटि, क्रमmat, args);
		ख_लिखो(मानक_त्रुटि, "\n");
		वापस -1;
	पूर्ण

	gtk_statusbar_pop(GTK_STATUSBAR(pgctx->statbar),
			  pgctx->statbar_ctx_id);

	/* Only first line can be displayed */
	p = म_अक्षर(msg, '\n');
	अगर (p)
		*p = '\0';

	gtk_statusbar_push(GTK_STATUSBAR(pgctx->statbar),
			   pgctx->statbar_ctx_id, msg);

	मुक्त(msg);
	वापस 0;
पूर्ण
#पूर्ण_अगर

काष्ठा perf_error_ops perf_gtk_eops = अणु
	.error		= perf_gtk__error,
#अगर_घोषित HAVE_GTK_INFO_BAR_SUPPORT
	.warning	= perf_gtk__warning_info_bar,
#अन्यथा
	.warning	= perf_gtk__warning_statusbar,
#पूर्ण_अगर
पूर्ण;
