<शैली गुरु>
/*
 *  linux/include/linux/console.h
 *
 *  Copyright (C) 1993        Hamish Macकरोnald
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Changed:
 * 10-Mar-94: Arno Grअगरfioen: Conversion क्रम vt100 emulator port from PC LINUX
 */

#अगर_अघोषित _LINUX_CONSOLE_H_
#घोषणा _LINUX_CONSOLE_H_ 1

#समावेश <linux/atomic.h>
#समावेश <linux/types.h>

काष्ठा vc_data;
काष्ठा console_font_op;
काष्ठा console_font;
काष्ठा module;
काष्ठा tty_काष्ठा;
काष्ठा notअगरier_block;

क्रमागत con_scroll अणु
	SM_UP,
	SM_DOWN,
पूर्ण;

क्रमागत vc_पूर्णांकensity;

/**
 * काष्ठा consw - callbacks क्रम consoles
 *
 * @con_scroll: move lines from @top to @bottom in direction @dir by @lines.
 *		Return true अगर no generic handling should be करोne.
 *		Invoked by csi_M and prपूर्णांकing to the console.
 * @con_set_palette: sets the palette of the console to @table (optional)
 * @con_scrolldelta: the contents of the console should be scrolled by @lines.
 *		     Invoked by user. (optional)
 */
काष्ठा consw अणु
	काष्ठा module *owner;
	स्थिर अक्षर *(*con_startup)(व्योम);
	व्योम	(*con_init)(काष्ठा vc_data *vc, पूर्णांक init);
	व्योम	(*con_deinit)(काष्ठा vc_data *vc);
	व्योम	(*con_clear)(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx, पूर्णांक height,
			पूर्णांक width);
	व्योम	(*con_अ_दो)(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos, पूर्णांक xpos);
	व्योम	(*con_अ_दोs)(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
			पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos);
	व्योम	(*con_cursor)(काष्ठा vc_data *vc, पूर्णांक mode);
	bool	(*con_scroll)(काष्ठा vc_data *vc, अचिन्हित पूर्णांक top,
			अचिन्हित पूर्णांक bottom, क्रमागत con_scroll dir,
			अचिन्हित पूर्णांक lines);
	पूर्णांक	(*con_चयन)(काष्ठा vc_data *vc);
	पूर्णांक	(*con_blank)(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन);
	पूर्णांक	(*con_font_set)(काष्ठा vc_data *vc, काष्ठा console_font *font,
			अचिन्हित पूर्णांक flags);
	पूर्णांक	(*con_font_get)(काष्ठा vc_data *vc, काष्ठा console_font *font);
	पूर्णांक	(*con_font_शेष)(काष्ठा vc_data *vc,
			काष्ठा console_font *font, अक्षर *name);
	पूर्णांक     (*con_resize)(काष्ठा vc_data *vc, अचिन्हित पूर्णांक width,
			अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक user);
	व्योम	(*con_set_palette)(काष्ठा vc_data *vc,
			स्थिर अचिन्हित अक्षर *table);
	व्योम	(*con_scrolldelta)(काष्ठा vc_data *vc, पूर्णांक lines);
	पूर्णांक	(*con_set_origin)(काष्ठा vc_data *vc);
	व्योम	(*con_save_screen)(काष्ठा vc_data *vc);
	u8	(*con_build_attr)(काष्ठा vc_data *vc, u8 color,
			क्रमागत vc_पूर्णांकensity पूर्णांकensity,
			bool blink, bool underline, bool reverse, bool italic);
	व्योम	(*con_invert_region)(काष्ठा vc_data *vc, u16 *p, पूर्णांक count);
	u16    *(*con_screen_pos)(स्थिर काष्ठा vc_data *vc, पूर्णांक offset);
	अचिन्हित दीर्घ (*con_getxy)(काष्ठा vc_data *vc, अचिन्हित दीर्घ position,
			पूर्णांक *px, पूर्णांक *py);
	/*
	 * Flush the video console driver's scrollback buffer
	 */
	व्योम	(*con_flush_scrollback)(काष्ठा vc_data *vc);
	/*
	 * Prepare the console क्रम the debugger.  This includes, but is not
	 * limited to, unblanking the console, loading an appropriate
	 * palette, and allowing debugger generated output.
	 */
	पूर्णांक	(*con_debug_enter)(काष्ठा vc_data *vc);
	/*
	 * Restore the console to its pre-debug state as बंदly as possible.
	 */
	पूर्णांक	(*con_debug_leave)(काष्ठा vc_data *vc);
पूर्ण;

बाह्य स्थिर काष्ठा consw *conचयनp;

बाह्य स्थिर काष्ठा consw dummy_con;	/* dummy console buffer */
बाह्य स्थिर काष्ठा consw vga_con;	/* VGA text console */
बाह्य स्थिर काष्ठा consw newport_con;	/* SGI Newport console  */

पूर्णांक con_is_bound(स्थिर काष्ठा consw *csw);
पूर्णांक करो_unरेजिस्टर_con_driver(स्थिर काष्ठा consw *csw);
पूर्णांक करो_take_over_console(स्थिर काष्ठा consw *sw, पूर्णांक first, पूर्णांक last, पूर्णांक deflt);
व्योम give_up_console(स्थिर काष्ठा consw *sw);
#अगर_घोषित CONFIG_HW_CONSOLE
पूर्णांक con_debug_enter(काष्ठा vc_data *vc);
पूर्णांक con_debug_leave(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक con_debug_enter(काष्ठा vc_data *vc)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक con_debug_leave(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* cursor */
#घोषणा CM_DRAW     (1)
#घोषणा CM_ERASE    (2)
#घोषणा CM_MOVE     (3)

/*
 * The पूर्णांकerface क्रम a console, or any other device that wants to capture
 * console messages (prपूर्णांकer driver?)
 *
 * If a console driver is marked CON_BOOT then it will be स्वतः-unरेजिस्टरed
 * when the first real console is रेजिस्टरed.  This is क्रम early-prपूर्णांकk drivers.
 */

#घोषणा CON_PRINTBUFFER	(1)
#घोषणा CON_CONSDEV	(2) /* Preferred console, /dev/console */
#घोषणा CON_ENABLED	(4)
#घोषणा CON_BOOT	(8)
#घोषणा CON_ANYTIME	(16) /* Safe to call when cpu is offline */
#घोषणा CON_BRL		(32) /* Used क्रम a braille device */
#घोषणा CON_EXTENDED	(64) /* Use the extended output क्रमmat a la /dev/kmsg */

काष्ठा console अणु
	अक्षर	name[16];
	व्योम	(*ग_लिखो)(काष्ठा console *, स्थिर अक्षर *, अचिन्हित);
	पूर्णांक	(*पढ़ो)(काष्ठा console *, अक्षर *, अचिन्हित);
	काष्ठा tty_driver *(*device)(काष्ठा console *, पूर्णांक *);
	व्योम	(*unblank)(व्योम);
	पूर्णांक	(*setup)(काष्ठा console *, अक्षर *);
	पूर्णांक	(*निकास)(काष्ठा console *);
	पूर्णांक	(*match)(काष्ठा console *, अक्षर *name, पूर्णांक idx, अक्षर *options);
	लघु	flags;
	लघु	index;
	पूर्णांक	cflag;
	व्योम	*data;
	काष्ठा	 console *next;
पूर्ण;

/*
 * क्रम_each_console() allows you to iterate on each console
 */
#घोषणा क्रम_each_console(con) \
	क्रम (con = console_drivers; con != शून्य; con = con->next)

बाह्य पूर्णांक console_set_on_cmdline;
बाह्य काष्ठा console *early_console;

क्रमागत con_flush_mode अणु
	CONSOLE_FLUSH_PENDING,
	CONSOLE_REPLAY_ALL,
पूर्ण;

बाह्य पूर्णांक add_preferred_console(अक्षर *name, पूर्णांक idx, अक्षर *options);
बाह्य व्योम रेजिस्टर_console(काष्ठा console *);
बाह्य पूर्णांक unरेजिस्टर_console(काष्ठा console *);
बाह्य काष्ठा console *console_drivers;
बाह्य व्योम console_lock(व्योम);
बाह्य पूर्णांक console_trylock(व्योम);
बाह्य व्योम console_unlock(व्योम);
बाह्य व्योम console_conditional_schedule(व्योम);
बाह्य व्योम console_unblank(व्योम);
बाह्य व्योम console_flush_on_panic(क्रमागत con_flush_mode mode);
बाह्य काष्ठा tty_driver *console_device(पूर्णांक *);
बाह्य व्योम console_stop(काष्ठा console *);
बाह्य व्योम console_start(काष्ठा console *);
बाह्य पूर्णांक is_console_locked(व्योम);
बाह्य पूर्णांक braille_रेजिस्टर_console(काष्ठा console *, पूर्णांक index,
		अक्षर *console_options, अक्षर *braille_options);
बाह्य पूर्णांक braille_unरेजिस्टर_console(काष्ठा console *);
#अगर_घोषित CONFIG_TTY
बाह्य व्योम console_sysfs_notअगरy(व्योम);
#अन्यथा
अटल अंतरभूत व्योम console_sysfs_notअगरy(व्योम)
अणु पूर्ण
#पूर्ण_अगर
बाह्य bool console_suspend_enabled;

/* Suspend and resume console messages over PM events */
बाह्य व्योम suspend_console(व्योम);
बाह्य व्योम resume_console(व्योम);

पूर्णांक mda_console_init(व्योम);

व्योम vcs_make_sysfs(पूर्णांक index);
व्योम vcs_हटाओ_sysfs(पूर्णांक index);

/* Some debug stub to catch some of the obvious races in the VT code */
#घोषणा WARN_CONSOLE_UNLOCKED()						\
	WARN_ON(!atomic_पढ़ो(&ignore_console_lock_warning) &&		\
		!is_console_locked() && !oops_in_progress)
/*
 * Increment ignore_console_lock_warning अगर you need to quiet
 * WARN_CONSOLE_UNLOCKED() क्रम debugging purposes.
 */
बाह्य atomic_t ignore_console_lock_warning;

/* VESA Blanking Levels */
#घोषणा VESA_NO_BLANKING        0
#घोषणा VESA_VSYNC_SUSPEND      1
#घोषणा VESA_HSYNC_SUSPEND      2
#घोषणा VESA_POWERDOWN          3

#अगर_घोषित CONFIG_VGA_CONSOLE
बाह्य bool vgacon_text_क्रमce(व्योम);
#अन्यथा
अटल अंतरभूत bool vgacon_text_क्रमce(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

बाह्य व्योम console_init(व्योम);

/* For deferred console takeover */
व्योम dummycon_रेजिस्टर_output_notअगरier(काष्ठा notअगरier_block *nb);
व्योम dummycon_unरेजिस्टर_output_notअगरier(काष्ठा notअगरier_block *nb);

#पूर्ण_अगर /* _LINUX_CONSOLE_H */
