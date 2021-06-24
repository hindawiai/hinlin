<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_KD_H
#घोषणा _UAPI_LINUX_KD_H
#समावेश <linux/types.h>
#समावेश <linux/compiler.h>

/* 0x4B is 'K', to aव्योम collision with termios and vt */

#घोषणा GIO_FONT	0x4B60	/* माला_लो font in expanded क्रमm */
#घोषणा PIO_FONT	0x4B61	/* use font in expanded क्रमm */

#घोषणा GIO_FONTX	0x4B6B	/* get font using काष्ठा consolefontdesc */
#घोषणा PIO_FONTX	0x4B6C	/* set font using काष्ठा consolefontdesc */
काष्ठा consolefontdesc अणु
	अचिन्हित लघु अक्षरcount;	/* अक्षरacters in font (256 or 512) */
	अचिन्हित लघु अक्षरheight;	/* scan lines per अक्षरacter (1-32) */
	अक्षर __user *अक्षरdata;		/* font data in expanded क्रमm */
पूर्ण;

#घोषणा PIO_FONTRESET   0x4B6D	/* reset to शेष font */

#घोषणा GIO_CMAP	0x4B70	/* माला_लो colour palette on VGA+ */
#घोषणा PIO_CMAP	0x4B71	/* sets colour palette on VGA+ */

#घोषणा KIOCSOUND	0x4B2F	/* start sound generation (0 क्रम off) */
#घोषणा KDMKTONE	0x4B30	/* generate tone */

#घोषणा KDGETLED	0x4B31	/* वापस current led state */
#घोषणा KDSETLED	0x4B32	/* set led state [lights, not flags] */
#घोषणा 	LED_SCR		0x01	/* scroll lock led */
#घोषणा 	LED_NUM		0x02	/* num lock led */
#घोषणा 	LED_CAP		0x04	/* caps lock led */

#घोषणा KDGKBTYPE	0x4B33	/* get keyboard type */
#घोषणा 	KB_84		0x01
#घोषणा 	KB_101		0x02 	/* this is what we always answer */
#घोषणा 	KB_OTHER	0x03

#घोषणा KDADDIO		0x4B34	/* add i/o port as valid */
#घोषणा KDDELIO		0x4B35	/* del i/o port as valid */
#घोषणा KDENABIO	0x4B36	/* enable i/o to video board */
#घोषणा KDDISABIO	0x4B37	/* disable i/o to video board */

#घोषणा KDSETMODE	0x4B3A	/* set text/graphics mode */
#घोषणा		KD_TEXT		0x00
#घोषणा		KD_GRAPHICS	0x01
#घोषणा		KD_TEXT0	0x02	/* obsolete */
#घोषणा		KD_TEXT1	0x03	/* obsolete */
#घोषणा KDGETMODE	0x4B3B	/* get current mode */

#घोषणा KDMAPDISP	0x4B3C	/* map display पूर्णांकo address space */
#घोषणा KDUNMAPDISP	0x4B3D	/* unmap display from address space */

प्रकार अक्षर scrnmap_t;
#घोषणा		E_TABSZ		256
#घोषणा GIO_SCRNMAP	0x4B40	/* get screen mapping from kernel */
#घोषणा PIO_SCRNMAP	0x4B41	/* put screen mapping table in kernel */
#घोषणा GIO_UNISCRNMAP  0x4B69	/* get full Unicode screen mapping */
#घोषणा PIO_UNISCRNMAP  0x4B6A  /* set full Unicode screen mapping */

#घोषणा GIO_UNIMAP	0x4B66	/* get unicode-to-font mapping from kernel */
काष्ठा unipair अणु
	अचिन्हित लघु unicode;
	अचिन्हित लघु fontpos;
पूर्ण;
काष्ठा unimapdesc अणु
	अचिन्हित लघु entry_ct;
	काष्ठा unipair __user *entries;
पूर्ण;
#घोषणा PIO_UNIMAP	0x4B67	/* put unicode-to-font mapping in kernel */
#घोषणा PIO_UNIMAPCLR	0x4B68	/* clear table, possibly advise hash algorithm */
काष्ठा unimapinit अणु
	अचिन्हित लघु advised_hashsize;  /* 0 अगर no opinion */
	अचिन्हित लघु advised_hashstep;  /* 0 अगर no opinion */
	अचिन्हित लघु advised_hashlevel; /* 0 अगर no opinion */
पूर्ण;

#घोषणा UNI_सूचीECT_BASE 0xF000	/* start of Direct Font Region */
#घोषणा UNI_सूचीECT_MASK 0x01FF	/* Direct Font Region biपंचांगask */

#घोषणा		K_RAW		0x00
#घोषणा		K_XLATE		0x01
#घोषणा		K_MEDIUMRAW	0x02
#घोषणा		K_UNICODE	0x03
#घोषणा		K_OFF		0x04
#घोषणा KDGKBMODE	0x4B44	/* माला_लो current keyboard mode */
#घोषणा KDSKBMODE	0x4B45	/* sets current keyboard mode */

#घोषणा		K_METABIT	0x03
#घोषणा		K_ESCPREFIX	0x04
#घोषणा KDGKBMETA	0x4B62	/* माला_लो meta key handling mode */
#घोषणा KDSKBMETA	0x4B63	/* sets meta key handling mode */

#घोषणा		K_SCROLLLOCK	0x01
#घोषणा		K_NUMLOCK	0x02
#घोषणा		K_CAPSLOCK	0x04
#घोषणा	KDGKBLED	0x4B64	/* get led flags (not lights) */
#घोषणा	KDSKBLED	0x4B65	/* set led flags (not lights) */

काष्ठा kbentry अणु
	अचिन्हित अक्षर kb_table;
	अचिन्हित अक्षर kb_index;
	अचिन्हित लघु kb_value;
पूर्ण;
#घोषणा		K_NORMTAB	0x00
#घोषणा		K_SHIFTTAB	0x01
#घोषणा		K_ALTTAB	0x02
#घोषणा		K_ALTSHIFTTAB	0x03

#घोषणा KDGKBENT	0x4B46	/* माला_लो one entry in translation table */
#घोषणा KDSKBENT	0x4B47	/* sets one entry in translation table */

काष्ठा kbsentry अणु
	अचिन्हित अक्षर kb_func;
	अचिन्हित अक्षर kb_string[512];
पूर्ण;
#घोषणा KDGKBSENT	0x4B48	/* माला_लो one function key string entry */
#घोषणा KDSKBSENT	0x4B49	/* sets one function key string entry */

काष्ठा kbdiacr अणु
        अचिन्हित अक्षर diacr, base, result;
पूर्ण;
काष्ठा kbdiacrs अणु
        अचिन्हित पूर्णांक kb_cnt;    /* number of entries in following array */
	काष्ठा kbdiacr kbdiacr[256];    /* MAX_DIACR from keyboard.h */
पूर्ण;
#घोषणा KDGKBDIACR      0x4B4A  /* पढ़ो kernel accent table */
#घोषणा KDSKBDIACR      0x4B4B  /* ग_लिखो kernel accent table */

काष्ठा kbdiacruc अणु
	अचिन्हित पूर्णांक diacr, base, result;
पूर्ण;
काष्ठा kbdiacrsuc अणु
        अचिन्हित पूर्णांक kb_cnt;    /* number of entries in following array */
	काष्ठा kbdiacruc kbdiacruc[256];    /* MAX_DIACR from keyboard.h */
पूर्ण;
#घोषणा KDGKBDIACRUC    0x4BFA  /* पढ़ो kernel accent table - UCS */
#घोषणा KDSKBDIACRUC    0x4BFB  /* ग_लिखो kernel accent table - UCS */

काष्ठा kbkeycode अणु
	अचिन्हित पूर्णांक scancode, keycode;
पूर्ण;
#घोषणा KDGETKEYCODE	0x4B4C	/* पढ़ो kernel keycode table entry */
#घोषणा KDSETKEYCODE	0x4B4D	/* ग_लिखो kernel keycode table entry */

#घोषणा KDSIGACCEPT	0x4B4E	/* accept kbd generated संकेतs */

काष्ठा kbd_repeat अणु
	पूर्णांक delay;	/* in msec; <= 0: करोn't change */
	पूर्णांक period;	/* in msec; <= 0: करोn't change */
			/* earlier this field was misnamed "rate" */
पूर्ण;

#घोषणा KDKBDREP        0x4B52  /* set keyboard delay/repeat rate;
				 * actually used values are वापसed */

#घोषणा KDFONTOP	0x4B72	/* font operations */

काष्ठा console_font_op अणु
	अचिन्हित पूर्णांक op;	/* operation code KD_FONT_OP_* */
	अचिन्हित पूर्णांक flags;	/* KD_FONT_FLAG_* */
	अचिन्हित पूर्णांक width, height;	/* font size */
	अचिन्हित पूर्णांक अक्षरcount;
	अचिन्हित अक्षर __user *data;	/* font data with height fixed to 32 */
पूर्ण;

काष्ठा console_font अणु
	अचिन्हित पूर्णांक width, height;	/* font size */
	अचिन्हित पूर्णांक अक्षरcount;
	अचिन्हित अक्षर *data;	/* font data with height fixed to 32 */
पूर्ण;

#घोषणा KD_FONT_OP_SET		0	/* Set font */
#घोषणा KD_FONT_OP_GET		1	/* Get font */
#घोषणा KD_FONT_OP_SET_DEFAULT	2	/* Set font to शेष, data poपूर्णांकs to name / शून्य */
#घोषणा KD_FONT_OP_COPY		3	/* Obsolete, करो not use */

#घोषणा KD_FONT_FLAG_DONT_RECALC 	1	/* Don't recalculate hw अक्षरcell size [compat] */

/* note: 0x4B00-0x4B4E all have had a value at some समय;
   करोn't reuse क्रम the समय being */
/* note: 0x4B60-0x4B6D, 0x4B70-0x4B72 used above */

#पूर्ण_अगर /* _UAPI_LINUX_KD_H */
