<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/video/dummycon.c -- A dummy console driver
 *
 *  To be used अगर there's no other console driver (e.g. क्रम plain VGA text)
 *  available, usually until fbcon takes console over.
 */

#समावेश <linux/types.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/console.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>

/*
 *  Dummy console driver
 */

#अगर defined(__arm__)
#घोषणा DUMMY_COLUMNS	screen_info.orig_video_cols
#घोषणा DUMMY_ROWS	screen_info.orig_video_lines
#अन्यथा
/* set by Kconfig. Use 80x25 क्रम 640x480 and 160x64 क्रम 1280x1024 */
#घोषणा DUMMY_COLUMNS	CONFIG_DUMMY_CONSOLE_COLUMNS
#घोषणा DUMMY_ROWS	CONFIG_DUMMY_CONSOLE_ROWS
#पूर्ण_अगर

#अगर_घोषित CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER
/* These are both रक्षित by the console_lock */
अटल RAW_NOTIFIER_HEAD(dummycon_output_nh);
अटल bool dummycon_अ_दो_called;

व्योम dummycon_रेजिस्टर_output_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	WARN_CONSOLE_UNLOCKED();

	raw_notअगरier_chain_रेजिस्टर(&dummycon_output_nh, nb);

	अगर (dummycon_अ_दो_called)
		nb->notअगरier_call(nb, 0, शून्य);
पूर्ण

व्योम dummycon_unरेजिस्टर_output_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	WARN_CONSOLE_UNLOCKED();

	raw_notअगरier_chain_unरेजिस्टर(&dummycon_output_nh, nb);
पूर्ण

अटल व्योम dummycon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos)
अणु
	WARN_CONSOLE_UNLOCKED();

	dummycon_अ_दो_called = true;
	raw_notअगरier_call_chain(&dummycon_output_nh, 0, शून्य);
पूर्ण

अटल व्योम dummycon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			   पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos)
अणु
	पूर्णांक i;

	अगर (!dummycon_अ_दो_called) अणु
		/* Ignore erases */
		क्रम (i = 0 ; i < count; i++) अणु
			अगर (s[i] != vc->vc_video_erase_अक्षर)
				अवरोध;
		पूर्ण
		अगर (i == count)
			वापस;

		dummycon_अ_दो_called = true;
	पूर्ण

	raw_notअगरier_call_chain(&dummycon_output_nh, 0, शून्य);
पूर्ण

अटल पूर्णांक dummycon_blank(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	/* Redraw, so that we get अ_दो(s) क्रम output करोne जबतक blanked */
	वापस 1;
पूर्ण
#अन्यथा
अटल व्योम dummycon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos) अणु पूर्ण
अटल व्योम dummycon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			   पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos) अणु पूर्ण
अटल पूर्णांक dummycon_blank(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर अक्षर *dummycon_startup(व्योम)
अणु
    वापस "dummy device";
पूर्ण

अटल व्योम dummycon_init(काष्ठा vc_data *vc, पूर्णांक init)
अणु
    vc->vc_can_करो_color = 1;
    अगर (init) अणु
	vc->vc_cols = DUMMY_COLUMNS;
	vc->vc_rows = DUMMY_ROWS;
    पूर्ण अन्यथा
	vc_resize(vc, DUMMY_COLUMNS, DUMMY_ROWS);
पूर्ण

अटल व्योम dummycon_deinit(काष्ठा vc_data *vc) अणु पूर्ण
अटल व्योम dummycon_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			   पूर्णांक width) अणु पूर्ण
अटल व्योम dummycon_cursor(काष्ठा vc_data *vc, पूर्णांक mode) अणु पूर्ण

अटल bool dummycon_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक top,
			    अचिन्हित पूर्णांक bottom, क्रमागत con_scroll dir,
			    अचिन्हित पूर्णांक lines)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक dummycon_चयन(काष्ठा vc_data *vc)
अणु
	वापस 0;
पूर्ण

/*
 *  The console `चयन' काष्ठाure क्रम the dummy console
 *
 *  Most of the operations are dummies.
 */

स्थिर काष्ठा consw dummy_con = अणु
	.owner =		THIS_MODULE,
	.con_startup =	dummycon_startup,
	.con_init =		dummycon_init,
	.con_deinit =	dummycon_deinit,
	.con_clear =	dummycon_clear,
	.con_अ_दो =		dummycon_अ_दो,
	.con_अ_दोs =	dummycon_अ_दोs,
	.con_cursor =	dummycon_cursor,
	.con_scroll =	dummycon_scroll,
	.con_चयन =	dummycon_चयन,
	.con_blank =	dummycon_blank,
पूर्ण;
EXPORT_SYMBOL_GPL(dummy_con);
