<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */

/* BFA common services */

#अगर_अघोषित __BFA_CS_H__
#घोषणा __BFA_CS_H__

#समावेश "cna.h"

/* BFA state machine पूर्णांकerfaces */

प्रकार व्योम (*bfa_sm_t)(व्योम *sm, पूर्णांक event);

/* For converting from state machine function to state encoding. */
काष्ठा bfa_sm_table अणु
	bfa_sm_t	sm;	/*!< state machine function	*/
	पूर्णांक		state;	/*!< state machine encoding	*/
	अक्षर		*name;	/*!< state name क्रम display	*/
पूर्ण;
#घोषणा BFA_SM(_sm)		((bfa_sm_t)(_sm))

/* State machine with entry actions. */
प्रकार व्योम (*bfa_fsm_t)(व्योम *fsm, पूर्णांक event);

/* oc - object class eg. bfa_ioc
 * st - state, eg. reset
 * otype - object type, eg. काष्ठा bfa_ioc
 * etype - object type, eg. क्रमागत ioc_event
 */
#घोषणा bfa_fsm_state_decl(oc, st, otype, etype)			\
	अटल व्योम oc ## _sm_ ## st(otype * fsm, etype event);		\
	अटल व्योम oc ## _sm_ ## st ## _entry(otype * fsm)

#घोषणा bfa_fsm_set_state(_fsm, _state) करो अणु				\
	(_fsm)->fsm = (bfa_fsm_t)(_state);				\
	_state ## _entry(_fsm);						\
पूर्ण जबतक (0)

#घोषणा bfa_fsm_send_event(_fsm, _event)	((_fsm)->fsm((_fsm), (_event)))
#घोषणा bfa_fsm_cmp_state(_fsm, _state)					\
	((_fsm)->fsm == (bfa_fsm_t)(_state))

अटल अंतरभूत पूर्णांक
bfa_sm_to_state(स्थिर काष्ठा bfa_sm_table *smt, bfa_sm_t sm)
अणु
	पूर्णांक	i = 0;

	जबतक (smt[i].sm && smt[i].sm != sm)
		i++;
	वापस smt[i].state;
पूर्ण

/* Generic रुको counter. */

प्रकार व्योम (*bfa_wc_resume_t) (व्योम *cbarg);

काष्ठा bfa_wc अणु
	bfa_wc_resume_t wc_resume;
	व्योम		*wc_cbarg;
	पूर्णांक		wc_count;
पूर्ण;

अटल अंतरभूत व्योम
bfa_wc_up(काष्ठा bfa_wc *wc)
अणु
	wc->wc_count++;
पूर्ण

अटल अंतरभूत व्योम
bfa_wc_करोwn(काष्ठा bfa_wc *wc)
अणु
	wc->wc_count--;
	अगर (wc->wc_count == 0)
		wc->wc_resume(wc->wc_cbarg);
पूर्ण

/* Initialize a रुकोing counter. */
अटल अंतरभूत व्योम
bfa_wc_init(काष्ठा bfa_wc *wc, bfa_wc_resume_t wc_resume, व्योम *wc_cbarg)
अणु
	wc->wc_resume = wc_resume;
	wc->wc_cbarg = wc_cbarg;
	wc->wc_count = 0;
	bfa_wc_up(wc);
पूर्ण

/* Wait क्रम counter to reach zero */
अटल अंतरभूत व्योम
bfa_wc_रुको(काष्ठा bfa_wc *wc)
अणु
	bfa_wc_करोwn(wc);
पूर्ण

#पूर्ण_अगर /* __BFA_CS_H__ */
