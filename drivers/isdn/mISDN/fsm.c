<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * finite state machine implementation
 *
 * Author       Karsten Keil <kkeil@novell.com>
 *
 * Thanks to    Jan den Ouden
 *              Fritz Elfert
 * Copyright 2008  by Karsten Keil <kkeil@novell.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश "fsm.h"

#घोषणा FSM_TIMER_DEBUG 0

पूर्णांक
mISDN_FsmNew(काष्ठा Fsm *fsm,
	     काष्ठा FsmNode *fnlist, पूर्णांक fncount)
अणु
	पूर्णांक i;

	fsm->jumpmatrix =
		kzalloc(array3_size(माप(FSMFNPTR), fsm->state_count,
				    fsm->event_count),
			GFP_KERNEL);
	अगर (fsm->jumpmatrix == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < fncount; i++)
		अगर ((fnlist[i].state >= fsm->state_count) ||
		    (fnlist[i].event >= fsm->event_count)) अणु
			prपूर्णांकk(KERN_ERR
			       "mISDN_FsmNew Error: %d st(%ld/%ld) ev(%ld/%ld)\n",
			       i, (दीर्घ)fnlist[i].state, (दीर्घ)fsm->state_count,
			       (दीर्घ)fnlist[i].event, (दीर्घ)fsm->event_count);
		पूर्ण अन्यथा
			fsm->jumpmatrix[fsm->state_count * fnlist[i].event +
					fnlist[i].state] = (FSMFNPTR) fnlist[i].routine;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_FsmNew);

व्योम
mISDN_FsmFree(काष्ठा Fsm *fsm)
अणु
	kमुक्त((व्योम *) fsm->jumpmatrix);
पूर्ण
EXPORT_SYMBOL(mISDN_FsmFree);

पूर्णांक
mISDN_FsmEvent(काष्ठा FsmInst *fi, पूर्णांक event, व्योम *arg)
अणु
	FSMFNPTR r;

	अगर ((fi->state >= fi->fsm->state_count) ||
	    (event >= fi->fsm->event_count)) अणु
		prपूर्णांकk(KERN_ERR
		       "mISDN_FsmEvent Error st(%ld/%ld) ev(%d/%ld)\n",
		       (दीर्घ)fi->state, (दीर्घ)fi->fsm->state_count, event,
		       (दीर्घ)fi->fsm->event_count);
		वापस 1;
	पूर्ण
	r = fi->fsm->jumpmatrix[fi->fsm->state_count * event + fi->state];
	अगर (r) अणु
		अगर (fi->debug)
			fi->prपूर्णांकdebug(fi, "State %s Event %s",
				       fi->fsm->strState[fi->state],
				       fi->fsm->strEvent[event]);
		r(fi, event, arg);
		वापस 0;
	पूर्ण अन्यथा अणु
		अगर (fi->debug)
			fi->prपूर्णांकdebug(fi, "State %s Event %s no action",
				       fi->fsm->strState[fi->state],
				       fi->fsm->strEvent[event]);
		वापस 1;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mISDN_FsmEvent);

व्योम
mISDN_FsmChangeState(काष्ठा FsmInst *fi, पूर्णांक newstate)
अणु
	fi->state = newstate;
	अगर (fi->debug)
		fi->prपूर्णांकdebug(fi, "ChangeState %s",
			       fi->fsm->strState[newstate]);
पूर्ण
EXPORT_SYMBOL(mISDN_FsmChangeState);

अटल व्योम
FsmExpireTimer(काष्ठा समयr_list *t)
अणु
	काष्ठा FsmTimer *ft = from_समयr(ft, t, tl);
#अगर FSM_TIMER_DEBUG
	अगर (ft->fi->debug)
		ft->fi->prपूर्णांकdebug(ft->fi, "FsmExpireTimer %lx", (दीर्घ) ft);
#पूर्ण_अगर
	mISDN_FsmEvent(ft->fi, ft->event, ft->arg);
पूर्ण

व्योम
mISDN_FsmInitTimer(काष्ठा FsmInst *fi, काष्ठा FsmTimer *ft)
अणु
	ft->fi = fi;
#अगर FSM_TIMER_DEBUG
	अगर (ft->fi->debug)
		ft->fi->prपूर्णांकdebug(ft->fi, "mISDN_FsmInitTimer %lx", (दीर्घ) ft);
#पूर्ण_अगर
	समयr_setup(&ft->tl, FsmExpireTimer, 0);
पूर्ण
EXPORT_SYMBOL(mISDN_FsmInitTimer);

व्योम
mISDN_FsmDelTimer(काष्ठा FsmTimer *ft, पूर्णांक where)
अणु
#अगर FSM_TIMER_DEBUG
	अगर (ft->fi->debug)
		ft->fi->prपूर्णांकdebug(ft->fi, "mISDN_FsmDelTimer %lx %d",
				   (दीर्घ) ft, where);
#पूर्ण_अगर
	del_समयr(&ft->tl);
पूर्ण
EXPORT_SYMBOL(mISDN_FsmDelTimer);

पूर्णांक
mISDN_FsmAddTimer(काष्ठा FsmTimer *ft,
		  पूर्णांक millisec, पूर्णांक event, व्योम *arg, पूर्णांक where)
अणु

#अगर FSM_TIMER_DEBUG
	अगर (ft->fi->debug)
		ft->fi->prपूर्णांकdebug(ft->fi, "mISDN_FsmAddTimer %lx %d %d",
				   (दीर्घ) ft, millisec, where);
#पूर्ण_अगर

	अगर (समयr_pending(&ft->tl)) अणु
		अगर (ft->fi->debug) अणु
			prपूर्णांकk(KERN_WARNING
			       "mISDN_FsmAddTimer: timer already active!\n");
			ft->fi->prपूर्णांकdebug(ft->fi,
					   "mISDN_FsmAddTimer already active!");
		पूर्ण
		वापस -1;
	पूर्ण
	ft->event = event;
	ft->arg = arg;
	ft->tl.expires = jअगरfies + (millisec * HZ) / 1000;
	add_समयr(&ft->tl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mISDN_FsmAddTimer);

व्योम
mISDN_FsmRestartTimer(काष्ठा FsmTimer *ft,
		      पूर्णांक millisec, पूर्णांक event, व्योम *arg, पूर्णांक where)
अणु

#अगर FSM_TIMER_DEBUG
	अगर (ft->fi->debug)
		ft->fi->prपूर्णांकdebug(ft->fi, "mISDN_FsmRestartTimer %lx %d %d",
				   (दीर्घ) ft, millisec, where);
#पूर्ण_अगर

	अगर (समयr_pending(&ft->tl))
		del_समयr(&ft->tl);
	ft->event = event;
	ft->arg = arg;
	ft->tl.expires = jअगरfies + (millisec * HZ) / 1000;
	add_समयr(&ft->tl);
पूर्ण
EXPORT_SYMBOL(mISDN_FsmRestartTimer);
