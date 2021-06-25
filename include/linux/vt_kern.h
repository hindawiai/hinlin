<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VT_KERN_H
#घोषणा _VT_KERN_H

/*
 * this really is an extension of the vc_cons काष्ठाure in console.c, but
 * with inक्रमmation needed by the vt package
 */

#समावेश <linux/vt.h>
#समावेश <linux/kd.h>
#समावेश <linux/tty.h>
#समावेश <linux/mutex.h>
#समावेश <linux/console_काष्ठा.h>
#समावेश <linux/mm.h>
#समावेश <linux/consolemap.h>
#समावेश <linux/notअगरier.h>

व्योम kd_mksound(अचिन्हित पूर्णांक hz, अचिन्हित पूर्णांक ticks);
पूर्णांक kbd_rate(काष्ठा kbd_repeat *rep);

बाह्य पूर्णांक fg_console, last_console, want_console;

/* console.c */

पूर्णांक vc_allocate(अचिन्हित पूर्णांक console);
पूर्णांक vc_cons_allocated(अचिन्हित पूर्णांक console);
पूर्णांक vc_resize(काष्ठा vc_data *vc, अचिन्हित पूर्णांक cols, अचिन्हित पूर्णांक lines);
काष्ठा vc_data *vc_deallocate(अचिन्हित पूर्णांक console);
व्योम reset_palette(काष्ठा vc_data *vc);
व्योम करो_blank_screen(पूर्णांक entering_gfx);
व्योम करो_unblank_screen(पूर्णांक leaving_gfx);
व्योम unblank_screen(व्योम);
व्योम poke_blanked_console(व्योम);
पूर्णांक con_font_op(काष्ठा vc_data *vc, काष्ठा console_font_op *op);
पूर्णांक con_set_cmap(अचिन्हित अक्षर __user *cmap);
पूर्णांक con_get_cmap(अचिन्हित अक्षर __user *cmap);
व्योम scrollback(काष्ठा vc_data *vc);
व्योम scrollfront(काष्ठा vc_data *vc, पूर्णांक lines);
व्योम clear_buffer_attributes(काष्ठा vc_data *vc);
व्योम update_region(काष्ठा vc_data *vc, अचिन्हित दीर्घ start, पूर्णांक count);
व्योम redraw_screen(काष्ठा vc_data *vc, पूर्णांक is_चयन);
#घोषणा update_screen(x) redraw_screen(x, 0)
#घोषणा चयन_screen(x) redraw_screen(x, 1)

काष्ठा tty_काष्ठा;
पूर्णांक tioclinux(काष्ठा tty_काष्ठा *tty, अचिन्हित दीर्घ arg);

#अगर_घोषित CONFIG_CONSOLE_TRANSLATIONS
/* consolemap.c */

काष्ठा unipair;

पूर्णांक con_set_trans_old(अचिन्हित अक्षर __user * table);
पूर्णांक con_get_trans_old(अचिन्हित अक्षर __user * table);
पूर्णांक con_set_trans_new(अचिन्हित लघु __user * table);
पूर्णांक con_get_trans_new(अचिन्हित लघु __user * table);
पूर्णांक con_clear_unimap(काष्ठा vc_data *vc);
पूर्णांक con_set_unimap(काष्ठा vc_data *vc, uलघु ct, काष्ठा unipair __user *list);
पूर्णांक con_get_unimap(काष्ठा vc_data *vc, uलघु ct, uलघु __user *uct, काष्ठा unipair __user *list);
पूर्णांक con_set_शेष_unimap(काष्ठा vc_data *vc);
व्योम con_मुक्त_unimap(काष्ठा vc_data *vc);
पूर्णांक con_copy_unimap(काष्ठा vc_data *dst_vc, काष्ठा vc_data *src_vc);

#अन्यथा
अटल अंतरभूत पूर्णांक con_set_trans_old(अचिन्हित अक्षर __user *table)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक con_get_trans_old(अचिन्हित अक्षर __user *table)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक con_set_trans_new(अचिन्हित लघु __user *table)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक con_get_trans_new(अचिन्हित लघु __user *table)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक con_clear_unimap(काष्ठा vc_data *vc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
पूर्णांक con_set_unimap(काष्ठा vc_data *vc, uलघु ct, काष्ठा unipair __user *list)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
पूर्णांक con_get_unimap(काष्ठा vc_data *vc, uलघु ct, uलघु __user *uct,
		   काष्ठा unipair __user *list)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक con_set_शेष_unimap(काष्ठा vc_data *vc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम con_मुक्त_unimap(काष्ठा vc_data *vc)
अणु
पूर्ण
अटल अंतरभूत व्योम con_protect_unimap(काष्ठा vc_data *vc, पूर्णांक rकरोnly)
अणु
पूर्ण
अटल अंतरभूत
पूर्णांक con_copy_unimap(काष्ठा vc_data *dst_vc, काष्ठा vc_data *src_vc)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

/* vt.c */
व्योम vt_event_post(अचिन्हित पूर्णांक event, अचिन्हित पूर्णांक old, अचिन्हित पूर्णांक new);
पूर्णांक vt_रुकोactive(पूर्णांक n);
व्योम change_console(काष्ठा vc_data *new_vc);
व्योम reset_vc(काष्ठा vc_data *vc);
पूर्णांक करो_unbind_con_driver(स्थिर काष्ठा consw *csw, पूर्णांक first, पूर्णांक last,
			 पूर्णांक deflt);
पूर्णांक vty_init(स्थिर काष्ठा file_operations *console_fops);

बाह्य bool vt_करोnt_चयन;
बाह्य पूर्णांक शेष_utf8;
बाह्य पूर्णांक global_cursor_शेष;

काष्ठा vt_spawn_console अणु
	spinlock_t lock;
	काष्ठा pid *pid;
	पूर्णांक sig;
पूर्ण;
बाह्य काष्ठा vt_spawn_console vt_spawn_con;

पूर्णांक vt_move_to_console(अचिन्हित पूर्णांक vt, पूर्णांक alloc);

/* Interfaces क्रम VC notअगरication of अक्षरacter events (क्रम accessibility etc) */

काष्ठा vt_notअगरier_param अणु
	काष्ठा vc_data *vc;	/* VC on which the update happened */
	अचिन्हित पूर्णांक c;		/* Prपूर्णांकed अक्षर */
पूर्ण;

पूर्णांक रेजिस्टर_vt_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक unरेजिस्टर_vt_notअगरier(काष्ठा notअगरier_block *nb);

व्योम hide_boot_cursor(bool hide);

/* keyboard  provided पूर्णांकerfaces */
पूर्णांक vt_करो_diacrit(अचिन्हित पूर्णांक cmd, व्योम __user *up, पूर्णांक eperm);
पूर्णांक vt_करो_kdskbmode(पूर्णांक console, अचिन्हित पूर्णांक arg);
पूर्णांक vt_करो_kdskbmeta(पूर्णांक console, अचिन्हित पूर्णांक arg);
पूर्णांक vt_करो_kbkeycode_ioctl(पूर्णांक cmd, काष्ठा kbkeycode __user *user_kbkc,
			  पूर्णांक perm);
पूर्णांक vt_करो_kdsk_ioctl(पूर्णांक cmd, काष्ठा kbentry __user *user_kbe, पूर्णांक perm,
		     पूर्णांक console);
पूर्णांक vt_करो_kdgkb_ioctl(पूर्णांक cmd, काष्ठा kbsentry __user *user_kdgkb, पूर्णांक perm);
पूर्णांक vt_करो_kdskled(पूर्णांक console, पूर्णांक cmd, अचिन्हित दीर्घ arg, पूर्णांक perm);
पूर्णांक vt_करो_kdgkbmode(पूर्णांक console);
पूर्णांक vt_करो_kdgkbmeta(पूर्णांक console);
व्योम vt_reset_unicode(पूर्णांक console);
पूर्णांक vt_get_shअगरt_state(व्योम);
व्योम vt_reset_keyboard(पूर्णांक console);
पूर्णांक vt_get_leds(पूर्णांक console, पूर्णांक flag);
पूर्णांक vt_get_kbd_mode_bit(पूर्णांक console, पूर्णांक bit);
व्योम vt_set_kbd_mode_bit(पूर्णांक console, पूर्णांक bit);
व्योम vt_clr_kbd_mode_bit(पूर्णांक console, पूर्णांक bit);
व्योम vt_set_led_state(पूर्णांक console, पूर्णांक leds);
व्योम vt_set_led_state(पूर्णांक console, पूर्णांक leds);
व्योम vt_kbd_con_start(पूर्णांक console);
व्योम vt_kbd_con_stop(पूर्णांक console);

व्योम vc_scrolldelta_helper(काष्ठा vc_data *c, पूर्णांक lines,
		अचिन्हित पूर्णांक rolled_over, व्योम *_base, अचिन्हित पूर्णांक size);

#पूर्ण_अगर /* _VT_KERN_H */
