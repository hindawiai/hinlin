<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LIVEPATCH_TRANSITION_H
#घोषणा _LIVEPATCH_TRANSITION_H

#समावेश <linux/livepatch.h>

बाह्य काष्ठा klp_patch *klp_transition_patch;

व्योम klp_init_transition(काष्ठा klp_patch *patch, पूर्णांक state);
व्योम klp_cancel_transition(व्योम);
व्योम klp_start_transition(व्योम);
व्योम klp_try_complete_transition(व्योम);
व्योम klp_reverse_transition(व्योम);
व्योम klp_क्रमce_transition(व्योम);

#पूर्ण_अगर /* _LIVEPATCH_TRANSITION_H */
