<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_TIOCL_H
#घोषणा _LINUX_TIOCL_H

#घोषणा TIOCL_SETSEL	2	/* set a selection */
#घोषणा 	TIOCL_SELCHAR	0	/* select अक्षरacters */
#घोषणा 	TIOCL_SELWORD	1	/* select whole words */
#घोषणा 	TIOCL_SELLINE	2	/* select whole lines */
#घोषणा 	TIOCL_SELPOINTER	3	/* show the poपूर्णांकer */
#घोषणा 	TIOCL_SELCLEAR	4	/* clear visibility of selection */
#घोषणा 	TIOCL_SELMOUSEREPORT	16	/* report beginning of selection */
#घोषणा 	TIOCL_SELBUTTONMASK	15	/* button mask क्रम report */
/* selection extent */
काष्ठा tiocl_selection अणु
	अचिन्हित लघु xs;	/* X start */
	अचिन्हित लघु ys;	/* Y start */
	अचिन्हित लघु xe;	/* X end */
	अचिन्हित लघु ye;	/* Y end */
	अचिन्हित लघु sel_mode;	/* selection mode */
पूर्ण;

#घोषणा TIOCL_PASTESEL	3	/* paste previous selection */
#घोषणा TIOCL_UNBLANKSCREEN	4	/* unblank screen */

#घोषणा TIOCL_SELLOADLUT	5
	/* set अक्षरacters to be considered alphabetic when selecting */
	/* u32[8] bit array, 4 bytes-aligned with type */

/* these two करोn't वापस a value: they ग_लिखो it back in the type */
#घोषणा TIOCL_GETSHIFTSTATE	6	/* ग_लिखो shअगरt state */
#घोषणा TIOCL_GETMOUSEREPORTING	7	/* ग_लिखो whether mouse event are reported */
#घोषणा TIOCL_SETVESABLANK	10	/* set vesa blanking mode */
#घोषणा TIOCL_SETKMSGREसूचीECT	11	/* restrict kernel messages to a vt */
#घोषणा TIOCL_GETFGCONSOLE	12	/* get क्रमeground vt */
#घोषणा TIOCL_SCROLLCONSOLE	13	/* scroll console */
#घोषणा TIOCL_BLANKSCREEN	14	/* keep screen blank even अगर a key is pressed */
#घोषणा TIOCL_BLANKEDSCREEN	15	/* वापस which vt was blanked */
#घोषणा TIOCL_GETKMSGREसूचीECT	17	/* get the vt the kernel messages are restricted to */

#पूर्ण_अगर /* _LINUX_TIOCL_H */
