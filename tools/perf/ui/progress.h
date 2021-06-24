<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PERF_UI_PROGRESS_H_
#घोषणा _PERF_UI_PROGRESS_H_ 1

#समावेश <linux/types.h>

व्योम ui_progress__finish(व्योम);

काष्ठा ui_progress अणु
	स्थिर अक्षर *title;
	u64 curr, next, step, total;
	bool size;
पूर्ण;

व्योम __ui_progress__init(काष्ठा ui_progress *p, u64 total,
			 स्थिर अक्षर *title, bool size);

#घोषणा ui_progress__init(p, total, title) \
	__ui_progress__init(p, total, title, false)

#घोषणा ui_progress__init_size(p, total, title) \
	__ui_progress__init(p, total, title, true)

व्योम ui_progress__update(काष्ठा ui_progress *p, u64 adv);

काष्ठा ui_progress_ops अणु
	व्योम (*init)(काष्ठा ui_progress *p);
	व्योम (*update)(काष्ठा ui_progress *p);
	व्योम (*finish)(व्योम);
पूर्ण;

बाह्य काष्ठा ui_progress_ops *ui_progress__ops;

#पूर्ण_अगर
