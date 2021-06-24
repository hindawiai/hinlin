<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश "progress.h"

अटल व्योम null_progress__update(काष्ठा ui_progress *p __maybe_unused)
अणु
पूर्ण

अटल काष्ठा ui_progress_ops null_progress__ops =
अणु
	.update = null_progress__update,
पूर्ण;

काष्ठा ui_progress_ops *ui_progress__ops = &null_progress__ops;

व्योम ui_progress__update(काष्ठा ui_progress *p, u64 adv)
अणु
	u64 last = p->curr;

	p->curr += adv;

	अगर (p->curr >= p->next) अणु
		u64 nr = DIV_ROUND_UP(p->curr - last, p->step);

		p->next += nr * p->step;
		ui_progress__ops->update(p);
	पूर्ण
पूर्ण

व्योम __ui_progress__init(काष्ठा ui_progress *p, u64 total,
			 स्थिर अक्षर *title, bool size)
अणु
	p->curr = 0;
	p->next = p->step = total / 16 ?: 1;
	p->total = total;
	p->title = title;
	p->size  = size;

	अगर (ui_progress__ops->init)
		ui_progress__ops->init(p);
पूर्ण

व्योम ui_progress__finish(व्योम)
अणु
	अगर (ui_progress__ops->finish)
		ui_progress__ops->finish();
पूर्ण
