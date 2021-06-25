<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * selection.h
 *
 * Interface between console.c, tty_io.c, vt.c, vc_screen.c and selection.c
 */

#अगर_अघोषित _LINUX_SELECTION_H_
#घोषणा _LINUX_SELECTION_H_

#समावेश <linux/tiocl.h>
#समावेश <linux/vt_buffer.h>

काष्ठा tty_काष्ठा;
काष्ठा vc_data;

बाह्य व्योम clear_selection(व्योम);
बाह्य पूर्णांक set_selection_user(स्थिर काष्ठा tiocl_selection __user *sel,
			      काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक set_selection_kernel(काष्ठा tiocl_selection *v,
				काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक paste_selection(काष्ठा tty_काष्ठा *tty);
बाह्य पूर्णांक sel_loadlut(अक्षर __user *p);
बाह्य पूर्णांक mouse_reporting(व्योम);
बाह्य व्योम mouse_report(काष्ठा tty_काष्ठा * tty, पूर्णांक butt, पूर्णांक mrx, पूर्णांक mry);

bool vc_is_sel(काष्ठा vc_data *vc);

बाह्य पूर्णांक console_blanked;

बाह्य स्थिर अचिन्हित अक्षर color_table[];
बाह्य अचिन्हित अक्षर शेष_red[];
बाह्य अचिन्हित अक्षर शेष_grn[];
बाह्य अचिन्हित अक्षर शेष_blu[];

बाह्य अचिन्हित लघु *screen_pos(स्थिर काष्ठा vc_data *vc, पूर्णांक w_offset,
		bool viewed);
बाह्य u16 screen_glyph(स्थिर काष्ठा vc_data *vc, पूर्णांक offset);
बाह्य u32 screen_glyph_unicode(स्थिर काष्ठा vc_data *vc, पूर्णांक offset);
बाह्य व्योम complement_pos(काष्ठा vc_data *vc, पूर्णांक offset);
बाह्य व्योम invert_screen(काष्ठा vc_data *vc, पूर्णांक offset, पूर्णांक count, bool viewed);

बाह्य व्योम अ_लोonsxy(स्थिर काष्ठा vc_data *vc, अचिन्हित अक्षर xy[अटल 2]);
बाह्य व्योम अ_दोonsxy(काष्ठा vc_data *vc, अचिन्हित अक्षर xy[अटल स्थिर 2]);

बाह्य u16 vcs_scr_पढ़ोw(स्थिर काष्ठा vc_data *vc, स्थिर u16 *org);
बाह्य व्योम vcs_scr_ग_लिखोw(काष्ठा vc_data *vc, u16 val, u16 *org);
बाह्य व्योम vcs_scr_updated(काष्ठा vc_data *vc);

बाह्य पूर्णांक vc_uniscr_check(काष्ठा vc_data *vc);
बाह्य व्योम vc_uniscr_copy_line(स्थिर काष्ठा vc_data *vc, व्योम *dest,
				bool viewed,
				अचिन्हित पूर्णांक row, अचिन्हित पूर्णांक col,
				अचिन्हित पूर्णांक nr);

#पूर्ण_अगर
