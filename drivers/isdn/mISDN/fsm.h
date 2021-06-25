<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Author       Karsten Keil <kkeil@novell.com>
 *
 * Thanks to    Jan den Ouden
 *              Fritz Elfert
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#अगर_अघोषित _MISDN_FSM_H
#घोषणा _MISDN_FSM_H

#समावेश <linux/समयr.h>

/* Statemachine */

काष्ठा FsmInst;

प्रकार व्योम (*FSMFNPTR)(काष्ठा FsmInst *, पूर्णांक, व्योम *);

काष्ठा Fsm अणु
	FSMFNPTR *jumpmatrix;
	पूर्णांक state_count, event_count;
	अक्षर **strEvent, **strState;
पूर्ण;

काष्ठा FsmInst अणु
	काष्ठा Fsm *fsm;
	पूर्णांक state;
	पूर्णांक debug;
	व्योम *userdata;
	पूर्णांक userपूर्णांक;
	व्योम (*prपूर्णांकdebug) (काष्ठा FsmInst *, अक्षर *, ...);
पूर्ण;

काष्ठा FsmNode अणु
	पूर्णांक state, event;
	व्योम (*routine) (काष्ठा FsmInst *, पूर्णांक, व्योम *);
पूर्ण;

काष्ठा FsmTimer अणु
	काष्ठा FsmInst *fi;
	काष्ठा समयr_list tl;
	पूर्णांक event;
	व्योम *arg;
पूर्ण;

बाह्य पूर्णांक mISDN_FsmNew(काष्ठा Fsm *, काष्ठा FsmNode *, पूर्णांक);
बाह्य व्योम mISDN_FsmFree(काष्ठा Fsm *);
बाह्य पूर्णांक mISDN_FsmEvent(काष्ठा FsmInst *, पूर्णांक , व्योम *);
बाह्य व्योम mISDN_FsmChangeState(काष्ठा FsmInst *, पूर्णांक);
बाह्य व्योम mISDN_FsmInitTimer(काष्ठा FsmInst *, काष्ठा FsmTimer *);
बाह्य पूर्णांक mISDN_FsmAddTimer(काष्ठा FsmTimer *, पूर्णांक, पूर्णांक, व्योम *, पूर्णांक);
बाह्य व्योम mISDN_FsmRestartTimer(काष्ठा FsmTimer *, पूर्णांक, पूर्णांक, व्योम *, पूर्णांक);
बाह्य व्योम mISDN_FsmDelTimer(काष्ठा FsmTimer *, पूर्णांक);

#पूर्ण_अगर
