<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _RUNTIME_INSTR_H
#घोषणा _RUNTIME_INSTR_H

#समावेश <uapi/यंत्र/runसमय_instr.h>

बाह्य काष्ठा runसमय_instr_cb runसमय_instr_empty_cb;

अटल अंतरभूत व्योम save_ri_cb(काष्ठा runसमय_instr_cb *cb_prev)
अणु
	अगर (cb_prev)
		store_runसमय_instr_cb(cb_prev);
पूर्ण

अटल अंतरभूत व्योम restore_ri_cb(काष्ठा runसमय_instr_cb *cb_next,
				 काष्ठा runसमय_instr_cb *cb_prev)
अणु
	अगर (cb_next)
		load_runसमय_instr_cb(cb_next);
	अन्यथा अगर (cb_prev)
		load_runसमय_instr_cb(&runसमय_instr_empty_cb);
पूर्ण

काष्ठा task_काष्ठा;

व्योम runसमय_instr_release(काष्ठा task_काष्ठा *tsk);

#पूर्ण_अगर /* _RUNTIME_INSTR_H */
