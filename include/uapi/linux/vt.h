<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_VT_H
#घोषणा _UAPI_LINUX_VT_H


/*
 * These स्थिरants are also useful क्रम user-level apps (e.g., VC
 * resizing).
 */
#घोषणा MIN_NR_CONSOLES 1       /* must be at least 1 */
#घोषणा MAX_NR_CONSOLES	63	/* serial lines start at 64 */
		/* Note: the ioctl VT_GETSTATE करोes not work क्रम
		   consoles 16 and higher (since it वापसs a लघु) */

/* 0x56 is 'V', to aव्योम collision with termios and kd */

#घोषणा VT_OPENQRY	0x5600	/* find available vt */

काष्ठा vt_mode अणु
	अक्षर mode;		/* vt mode */
	अक्षर रुकोv;		/* अगर set, hang on ग_लिखोs अगर not active */
	लघु relsig;		/* संकेत to उठाओ on release req */
	लघु acqsig;		/* संकेत to उठाओ on acquisition */
	लघु frsig;		/* unused (set to 0) */
पूर्ण;
#घोषणा VT_GETMODE	0x5601	/* get mode of active vt */
#घोषणा VT_SETMODE	0x5602	/* set mode of active vt */
#घोषणा		VT_AUTO		0x00	/* स्वतः vt चयनing */
#घोषणा		VT_PROCESS	0x01	/* process controls चयनing */
#घोषणा		VT_ACKACQ	0x02	/* acknowledge चयन */

काष्ठा vt_stat अणु
	अचिन्हित लघु v_active;	/* active vt */
	अचिन्हित लघु v_संकेत;	/* संकेत to send */
	अचिन्हित लघु v_state;		/* vt biपंचांगask */
पूर्ण;
#घोषणा VT_GETSTATE	0x5603	/* get global vt state info */
#घोषणा VT_SENDSIG	0x5604	/* संकेत to send to biपंचांगask of vts */

#घोषणा VT_RELDISP	0x5605	/* release display */

#घोषणा VT_ACTIVATE	0x5606	/* make vt active */
#घोषणा VT_WAITACTIVE	0x5607	/* रुको क्रम vt active */
#घोषणा VT_DISALLOCATE	0x5608  /* मुक्त memory associated to vt */

काष्ठा vt_sizes अणु
	अचिन्हित लघु v_rows;		/* number of rows */
	अचिन्हित लघु v_cols;		/* number of columns */
	अचिन्हित लघु v_scrollsize;	/* number of lines of scrollback */
पूर्ण;
#घोषणा VT_RESIZE	0x5609	/* set kernel's idea of screensize */

काष्ठा vt_consize अणु
	अचिन्हित लघु v_rows;	/* number of rows */
	अचिन्हित लघु v_cols;	/* number of columns */
	अचिन्हित लघु v_vlin;	/* number of pixel rows on screen */
	अचिन्हित लघु v_clin;	/* number of pixel rows per अक्षरacter */
	अचिन्हित लघु v_vcol;	/* number of pixel columns on screen */
	अचिन्हित लघु v_ccol;	/* number of pixel columns per अक्षरacter */
पूर्ण;
#घोषणा VT_RESIZEX      0x560A  /* set kernel's idea of screensize + more */
#घोषणा VT_LOCKSWITCH   0x560B  /* disallow vt चयनing */
#घोषणा VT_UNLOCKSWITCH 0x560C  /* allow vt चयनing */
#घोषणा VT_GETHIFONTMASK 0x560D  /* वापस hi font mask */

काष्ठा vt_event अणु
	अचिन्हित पूर्णांक event;
#घोषणा VT_EVENT_SWITCH		0x0001	/* Console चयन */
#घोषणा VT_EVENT_BLANK		0x0002	/* Screen blank */
#घोषणा VT_EVENT_UNBLANK	0x0004	/* Screen unblank */
#घोषणा VT_EVENT_RESIZE		0x0008	/* Resize display */
#घोषणा VT_MAX_EVENT		0x000F
	अचिन्हित पूर्णांक oldev;		/* Old console */
	अचिन्हित पूर्णांक newev;		/* New console (अगर changing) */
	अचिन्हित पूर्णांक pad[4];		/* Padding क्रम expansion */
पूर्ण;

#घोषणा VT_WAITEVENT	0x560E	/* Wait क्रम an event */

काष्ठा vt_setactivate अणु
	अचिन्हित पूर्णांक console;
	काष्ठा vt_mode mode;
पूर्ण;

#घोषणा VT_SETACTIVATE	0x560F	/* Activate and set the mode of a console */

#पूर्ण_अगर /* _UAPI_LINUX_VT_H */
