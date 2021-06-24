<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * console_काष्ठा.h
 *
 * Data काष्ठाure describing single भव console except क्रम data
 * used by vt.c.
 *
 * Fields marked with [#] must be set by the low-level driver.
 * Fields marked with [!] can be changed by the low-level driver
 * to achieve effects such as fast scrolling by changing the origin.
 */

#अगर_अघोषित _LINUX_CONSOLE_STRUCT_H
#घोषणा _LINUX_CONSOLE_STRUCT_H

#समावेश <linux/रुको.h>
#समावेश <linux/vt.h>
#समावेश <linux/workqueue.h>

काष्ठा uni_pagedir;
काष्ठा uni_screen;

#घोषणा NPAR 16
#घोषणा VC_TABSTOPS_COUNT	256U

क्रमागत vc_पूर्णांकensity अणु
	VCI_HALF_BRIGHT,
	VCI_NORMAL,
	VCI_BOLD,
	VCI_MASK = 0x3,
पूर्ण;

/**
 * काष्ठा vc_state -- state of a VC
 * @x: cursor's x-position
 * @y: cursor's y-position
 * @color: क्रमeground & background colors
 * @Gx_अक्षरset: what's G0/G1 slot set to (like GRAF_MAP, LAT1_MAP)
 * @अक्षरset: what अक्षरacter set to use (0=G0 or 1=G1)
 * @पूर्णांकensity: see क्रमागत vc_पूर्णांकensity क्रम values
 * @reverse: reversed क्रमeground/background colors
 *
 * These members are defined separately from काष्ठा vc_data as we save &
 * restore them at बार.
 */
काष्ठा vc_state अणु
	अचिन्हित पूर्णांक	x, y;

	अचिन्हित अक्षर	color;

	अचिन्हित अक्षर	Gx_अक्षरset[2];
	अचिन्हित पूर्णांक	अक्षरset		: 1;

	/* attribute flags */
	क्रमागत vc_पूर्णांकensity पूर्णांकensity;
	bool		italic;
	bool		underline;
	bool		blink;
	bool		reverse;
पूर्ण;

/*
 * Example: vc_data of a console that was scrolled 3 lines करोwn.
 *
 *                              Console buffer
 * vc_screenbuf ---------> +----------------------+-.
 *                         | initializing W       |  \
 *                         | initializing X       |   |
 *                         | initializing Y       |    > scroll-back area
 *                         | initializing Z       |   |
 *                         |                      |  /
 * vc_visible_origin ---> ^+----------------------+-:
 * (changes by scroll)    || Welcome to linux     |  \
 *                        ||                      |   |
 *           vc_rows --->< | login: root          |   |  visible on console
 *                        || password:            |    > (vc_screenbuf_size is
 * vc_origin -----------> ||                      |   |   vc_size_row * vc_rows)
 * (start when no scroll) || Last login: 12:28    |  /
 *                        v+----------------------+-:
 *                         | Have a lot of fun... |  \
 * vc_pos -----------------|--------v             |   > scroll-front area
 *                         | ~ # cat_             |  /
 * vc_scr_end -----------> +----------------------+-:
 * (vc_origin +            |                      |  \ EMPTY, to be filled by
 *  vc_screenbuf_size)     |                      |  / vc_video_erase_अक्षर
 *                         +----------------------+-'
 *                         <---- 2 * vc_cols ----->
 *                         <---- vc_size_row ----->
 *
 * Note that every अक्षरacter in the console buffer is accompanied with an
 * attribute in the buffer right after the अक्षरacter. This is not depicted
 * in the figure.
 */
काष्ठा vc_data अणु
	काष्ठा tty_port port;			/* Upper level data */

	काष्ठा vc_state state, saved_state;

	अचिन्हित लघु	vc_num;			/* Console number */
	अचिन्हित पूर्णांक	vc_cols;		/* [#] Console size */
	अचिन्हित पूर्णांक	vc_rows;
	अचिन्हित पूर्णांक	vc_size_row;		/* Bytes per row */
	अचिन्हित पूर्णांक	vc_scan_lines;		/* # of scan lines */
	अचिन्हित पूर्णांक	vc_cell_height;		/* CRTC अक्षरacter cell height */
	अचिन्हित दीर्घ	vc_origin;		/* [!] Start of real screen */
	अचिन्हित दीर्घ	vc_scr_end;		/* [!] End of real screen */
	अचिन्हित दीर्घ	vc_visible_origin;	/* [!] Top of visible winकरोw */
	अचिन्हित पूर्णांक	vc_top, vc_bottom;	/* Scrolling region */
	स्थिर काष्ठा consw *vc_sw;
	अचिन्हित लघु	*vc_screenbuf;		/* In-memory अक्षरacter/attribute buffer */
	अचिन्हित पूर्णांक	vc_screenbuf_size;
	अचिन्हित अक्षर	vc_mode;		/* KD_TEXT, ... */
	/* attributes क्रम all अक्षरacters on screen */
	अचिन्हित अक्षर	vc_attr;		/* Current attributes */
	अचिन्हित अक्षर	vc_def_color;		/* Default colors */
	अचिन्हित अक्षर	vc_ulcolor;		/* Color क्रम underline mode */
	अचिन्हित अक्षर   vc_itcolor;
	अचिन्हित अक्षर	vc_halfcolor;		/* Color क्रम half पूर्णांकensity mode */
	/* cursor */
	अचिन्हित पूर्णांक	vc_cursor_type;
	अचिन्हित लघु	vc_complement_mask;	/* [#] Xor mask क्रम mouse poपूर्णांकer */
	अचिन्हित लघु	vc_s_complement_mask;	/* Saved mouse poपूर्णांकer mask */
	अचिन्हित दीर्घ	vc_pos;			/* Cursor address */
	/* fonts */	
	अचिन्हित लघु	vc_hi_font_mask;	/* [#] Attribute set क्रम upper 256 अक्षरs of font or 0 अगर not supported */
	काष्ठा console_font vc_font;		/* Current VC font set */
	अचिन्हित लघु	vc_video_erase_अक्षर;	/* Background erase अक्षरacter */
	/* VT terminal data */
	अचिन्हित पूर्णांक	vc_state;		/* Escape sequence parser state */
	अचिन्हित पूर्णांक	vc_npar,vc_par[NPAR];	/* Parameters of current escape sequence */
	/* data क्रम manual vt चयनing */
	काष्ठा vt_mode	vt_mode;
	काष्ठा pid 	*vt_pid;
	पूर्णांक		vt_newvt;
	रुको_queue_head_t paste_रुको;
	/* mode flags */
	अचिन्हित पूर्णांक	vc_disp_ctrl	: 1;	/* Display अक्षरs < 32? */
	अचिन्हित पूर्णांक	vc_toggle_meta	: 1;	/* Toggle high bit? */
	अचिन्हित पूर्णांक	vc_decscnm	: 1;	/* Screen Mode */
	अचिन्हित पूर्णांक	vc_decom	: 1;	/* Origin Mode */
	अचिन्हित पूर्णांक	vc_decawm	: 1;	/* Autowrap Mode */
	अचिन्हित पूर्णांक	vc_deccm	: 1;	/* Cursor Visible */
	अचिन्हित पूर्णांक	vc_decim	: 1;	/* Insert Mode */
	/* misc */
	अचिन्हित पूर्णांक	vc_priv		: 3;
	अचिन्हित पूर्णांक	vc_need_wrap	: 1;
	अचिन्हित पूर्णांक	vc_can_करो_color	: 1;
	अचिन्हित पूर्णांक	vc_report_mouse : 2;
	अचिन्हित अक्षर	vc_utf		: 1;	/* Unicode UTF-8 encoding */
	अचिन्हित अक्षर	vc_utf_count;
		 पूर्णांक	vc_utf_अक्षर;
	DECLARE_BITMAP(vc_tab_stop, VC_TABSTOPS_COUNT);	/* Tab stops. 256 columns. */
	अचिन्हित अक्षर   vc_palette[16*3];       /* Colour palette क्रम VGA+ */
	अचिन्हित लघु * vc_translate;
	अचिन्हित पूर्णांक    vc_resize_user;         /* resize request from user */
	अचिन्हित पूर्णांक	vc_bell_pitch;		/* Console bell pitch */
	अचिन्हित पूर्णांक	vc_bell_duration;	/* Console bell duration */
	अचिन्हित लघु	vc_cur_blink_ms;	/* Cursor blink duration */
	काष्ठा vc_data **vc_display_fg;		/* [!] Ptr to var holding fg console क्रम this display */
	काष्ठा uni_pagedir *vc_uni_pagedir;
	काष्ठा uni_pagedir **vc_uni_pagedir_loc; /* [!] Location of uni_pagedir variable क्रम this console */
	काष्ठा uni_screen *vc_uni_screen;	/* unicode screen content */
	/* additional inक्रमmation is in vt_kern.h */
पूर्ण;

काष्ठा vc अणु
	काष्ठा vc_data *d;
	काष्ठा work_काष्ठा SAK_work;

	/* might add  scrmem, kbd  at some समय,
	   to have everything in one place */
पूर्ण;

बाह्य काष्ठा vc vc_cons [MAX_NR_CONSOLES];
बाह्य व्योम vc_SAK(काष्ठा work_काष्ठा *work);

#घोषणा CUR_MAKE(size, change, set)	((size) | ((change) << 8) |	\
		((set) << 16))
#घोषणा CUR_SIZE(c)		 ((c) & 0x00000f)
# define CUR_DEF			       0
# define CUR_NONE			       1
# define CUR_UNDERLINE			       2
# define CUR_LOWER_THIRD		       3
# define CUR_LOWER_HALF			       4
# define CUR_TWO_THIRDS			       5
# define CUR_BLOCK			       6
#घोषणा CUR_SW				0x000010
#घोषणा CUR_ALWAYS_BG			0x000020
#घोषणा CUR_INVERT_FG_BG		0x000040
#घोषणा CUR_FG				0x000700
#घोषणा CUR_BG				0x007000
#घोषणा CUR_CHANGE(c)		 ((c) & 0x00ff00)
#घोषणा CUR_SET(c)		(((c) & 0xff0000) >> 8)

bool con_is_visible(स्थिर काष्ठा vc_data *vc);

#पूर्ण_अगर /* _LINUX_CONSOLE_STRUCT_H */
