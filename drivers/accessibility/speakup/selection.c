<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h> /* क्रम kदो_स्मृति */
#समावेश <linux/consolemap.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/device.h> /* क्रम dev_warn */
#समावेश <linux/selection.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/tty.h>
#समावेश <linux/tty_flip.h>
#समावेश <linux/atomic.h>
#समावेश <linux/console.h>

#समावेश "speakup.h"

अचिन्हित लघु spk_xs, spk_ys, spk_xe, spk_ye; /* our region poपूर्णांकs */
काष्ठा vc_data *spk_sel_cons;

काष्ठा speakup_selection_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा tiocl_selection sel;
	काष्ठा tty_काष्ठा *tty;
पूर्ण;

अटल व्योम __speakup_set_selection(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा speakup_selection_work *ssw =
		container_of(work, काष्ठा speakup_selection_work, work);

	काष्ठा tty_काष्ठा *tty;
	काष्ठा tiocl_selection sel;

	sel = ssw->sel;

	/* this ensures we copy sel beक्रमe releasing the lock below */
	rmb();

	/* release the lock by setting tty of the काष्ठा to शून्य */
	tty = xchg(&ssw->tty, शून्य);

	अगर (spk_sel_cons != vc_cons[fg_console].d) अणु
		spk_sel_cons = vc_cons[fg_console].d;
		pr_warn("Selection: mark console not the same as cut\n");
		जाओ unref;
	पूर्ण

	console_lock();
	clear_selection();
	console_unlock();

	set_selection_kernel(&sel, tty);

unref:
	tty_kref_put(tty);
पूर्ण

अटल काष्ठा speakup_selection_work speakup_sel_work = अणु
	.work = __WORK_INITIALIZER(speakup_sel_work.work,
				   __speakup_set_selection)
पूर्ण;

पूर्णांक speakup_set_selection(काष्ठा tty_काष्ठा *tty)
अणु
	/* we get kref here first in order to aव्योम a subtle race when
	 * cancelling selection work. getting kref first establishes the
	 * invariant that अगर speakup_sel_work.tty is not शून्य when
	 * speakup_cancel_selection() is called, it must be the हाल that a put
	 * kref is pending.
	 */
	tty_kref_get(tty);
	अगर (cmpxchg(&speakup_sel_work.tty, शून्य, tty)) अणु
		tty_kref_put(tty);
		वापस -EBUSY;
	पूर्ण
	/* now we have the 'lock' by setting tty member of
	 * speakup_selection_work. wmb() ensures that ग_लिखोs to
	 * speakup_sel_work करोn't happen beक्रमe cmpxchg() above.
	 */
	wmb();

	speakup_sel_work.sel.xs = spk_xs + 1;
	speakup_sel_work.sel.ys = spk_ys + 1;
	speakup_sel_work.sel.xe = spk_xe + 1;
	speakup_sel_work.sel.ye = spk_ye + 1;
	speakup_sel_work.sel.sel_mode = TIOCL_SELCHAR;

	schedule_work_on(WORK_CPU_UNBOUND, &speakup_sel_work.work);

	वापस 0;
पूर्ण

व्योम speakup_cancel_selection(व्योम)
अणु
	काष्ठा tty_काष्ठा *tty;

	cancel_work_sync(&speakup_sel_work.work);
	/* setting to null so that अगर work fails to run and we cancel it,
	 * we can run it again without getting EBUSY क्रमever from there on.
	 * we need to use xchg here to aव्योम race with speakup_set_selection()
	 */
	tty = xchg(&speakup_sel_work.tty, शून्य);
	अगर (tty)
		tty_kref_put(tty);
पूर्ण

अटल व्योम __speakup_paste_selection(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा speakup_selection_work *ssw =
		container_of(work, काष्ठा speakup_selection_work, work);
	काष्ठा tty_काष्ठा *tty = xchg(&ssw->tty, शून्य);

	paste_selection(tty);
	tty_kref_put(tty);
पूर्ण

अटल काष्ठा speakup_selection_work speakup_paste_work = अणु
	.work = __WORK_INITIALIZER(speakup_paste_work.work,
				   __speakup_paste_selection)
पूर्ण;

पूर्णांक speakup_paste_selection(काष्ठा tty_काष्ठा *tty)
अणु
	tty_kref_get(tty);
	अगर (cmpxchg(&speakup_paste_work.tty, शून्य, tty)) अणु
		tty_kref_put(tty);
		वापस -EBUSY;
	पूर्ण

	schedule_work_on(WORK_CPU_UNBOUND, &speakup_paste_work.work);
	वापस 0;
पूर्ण

व्योम speakup_cancel_paste(व्योम)
अणु
	काष्ठा tty_काष्ठा *tty;

	cancel_work_sync(&speakup_paste_work.work);
	tty = xchg(&speakup_paste_work.tty, शून्य);
	अगर (tty)
		tty_kref_put(tty);
पूर्ण
