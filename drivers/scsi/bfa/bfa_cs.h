<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014- QLogic Corporation.
 * All rights reserved
 * www.qlogic.com
 *
 * Linux driver क्रम QLogic BR-series Fibre Channel Host Bus Adapter.
 */

/*
 *  bfa_cs.h BFA common services
 */

#अगर_अघोषित __BFA_CS_H__
#घोषणा __BFA_CS_H__

#समावेश "bfad_drv.h"

/*
 * BFA TRC
 */

#अगर_अघोषित BFA_TRC_MAX
#घोषणा BFA_TRC_MAX	(4 * 1024)
#पूर्ण_अगर

#घोषणा BFA_TRC_TS(_trcm)                               \
	(अणु                                              \
		काष्ठा बारpec64 ts;                   \
							\
		kसमय_get_ts64(&ts);                    \
		(ts.tv_sec*1000000+ts.tv_nsec / 1000);  \
	पूर्ण)

#अगर_अघोषित BFA_TRC_TS
#घोषणा BFA_TRC_TS(_trcm)	((_trcm)->ticks++)
#पूर्ण_अगर

काष्ठा bfa_trc_s अणु
#अगर_घोषित __BIG_ENDIAN
	u16	fileno;
	u16	line;
#अन्यथा
	u16	line;
	u16	fileno;
#पूर्ण_अगर
	u32	बारtamp;
	जोड़ अणु
		काष्ठा अणु
			u32	rsvd;
			u32	u32;
		पूर्ण u32;
		u64	u64;
	पूर्ण data;
पूर्ण;

काष्ठा bfa_trc_mod_s अणु
	u32	head;
	u32	tail;
	u32	ntrc;
	u32	stopped;
	u32	ticks;
	u32	rsvd[3];
	काष्ठा bfa_trc_s trc[BFA_TRC_MAX];
पूर्ण;

क्रमागत अणु
	BFA_TRC_HAL  = 1,	/*  BFA modules */
	BFA_TRC_FCS  = 2,	/*  BFA FCS modules */
	BFA_TRC_LDRV = 3,	/*  Linux driver modules */
	BFA_TRC_CNA  = 4,	/*  Common modules */
पूर्ण;
#घोषणा BFA_TRC_MOD_SH	10
#घोषणा BFA_TRC_MOD(__mod)	((BFA_TRC_ ## __mod) << BFA_TRC_MOD_SH)

/*
 * Define a new tracing file (module). Module should match one defined above.
 */
#घोषणा BFA_TRC_खाता(__mod, __submod)					\
	अटल पूर्णांक __trc_fileno = ((BFA_TRC_ ## __mod ## _ ## __submod) | \
						 BFA_TRC_MOD(__mod))


#घोषणा bfa_trc32(_trcp, _data)	\
	__bfa_trc((_trcp)->trcmod, __trc_fileno, __LINE__, (u32)_data)
#घोषणा bfa_trc(_trcp, _data)	\
	__bfa_trc((_trcp)->trcmod, __trc_fileno, __LINE__, (u64)_data)

अटल अंतरभूत व्योम
bfa_trc_init(काष्ठा bfa_trc_mod_s *trcm)
अणु
	trcm->head = trcm->tail = trcm->stopped = 0;
	trcm->ntrc = BFA_TRC_MAX;
पूर्ण

अटल अंतरभूत व्योम
bfa_trc_stop(काष्ठा bfa_trc_mod_s *trcm)
अणु
	trcm->stopped = 1;
पूर्ण

व्योम
__bfa_trc(काष्ठा bfa_trc_mod_s *trcm, पूर्णांक fileno, पूर्णांक line, u64 data);

व्योम
__bfa_trc32(काष्ठा bfa_trc_mod_s *trcm, पूर्णांक fileno, पूर्णांक line, u32 data);

#घोषणा bfa_sm_fault(__mod, __event)	करो अणु				\
	bfa_trc(__mod, (((u32)0xDEAD << 16) | __event));		\
	prपूर्णांकk(KERN_ERR	"Assertion failure: %s:%d: %d",			\
		__खाता__, __LINE__, (__event));				\
पूर्ण जबतक (0)

/* BFA queue definitions */
#घोषणा bfa_q_first(_q) ((व्योम *)(((काष्ठा list_head *) (_q))->next))
#घोषणा bfa_q_next(_qe) (((काष्ठा list_head *) (_qe))->next)
#घोषणा bfa_q_prev(_qe) (((काष्ठा list_head *) (_qe))->prev)

/*
 * bfa_q_qe_init - to initialize a queue element
 */
#घोषणा bfa_q_qe_init(_qe) अणु				\
	bfa_q_next(_qe) = (काष्ठा list_head *) शून्य;	\
	bfa_q_prev(_qe) = (काष्ठा list_head *) शून्य;	\
पूर्ण

/*
 * bfa_q_deq - dequeue an element from head of the queue
 */
#घोषणा bfa_q_deq(_q, _qe) करो अणु						\
	अगर (!list_empty(_q)) अणु						\
		(*((काष्ठा list_head **) (_qe))) = bfa_q_next(_q);	\
		bfa_q_prev(bfa_q_next(*((काष्ठा list_head **) _qe))) =	\
				(काष्ठा list_head *) (_q);		\
		bfa_q_next(_q) = bfa_q_next(*((काष्ठा list_head **) _qe));\
	पूर्ण अन्यथा अणु							\
		*((काष्ठा list_head **) (_qe)) = (काष्ठा list_head *) शून्य;\
	पूर्ण								\
पूर्ण जबतक (0)

/*
 * bfa_q_deq_tail - dequeue an element from tail of the queue
 */
#घोषणा bfa_q_deq_tail(_q, _qe) अणु					\
	अगर (!list_empty(_q)) अणु						\
		*((काष्ठा list_head **) (_qe)) = bfa_q_prev(_q);	\
		bfa_q_next(bfa_q_prev(*((काष्ठा list_head **) _qe))) =	\
			(काष्ठा list_head *) (_q);			\
		bfa_q_prev(_q) = bfa_q_prev(*(काष्ठा list_head **) _qe);\
	पूर्ण अन्यथा अणु							\
		*((काष्ठा list_head **) (_qe)) = (काष्ठा list_head *) शून्य;\
	पूर्ण								\
पूर्ण

अटल अंतरभूत पूर्णांक
bfa_q_is_on_q_func(काष्ठा list_head *q, काष्ठा list_head *qe)
अणु
	काष्ठा list_head        *tqe;

	tqe = bfa_q_next(q);
	जबतक (tqe != q) अणु
		अगर (tqe == qe)
			वापस 1;
		tqe = bfa_q_next(tqe);
		अगर (tqe == शून्य)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा bfa_q_is_on_q(_q, _qe)      \
	bfa_q_is_on_q_func(_q, (काष्ठा list_head *)(_qe))

/*
 * @ BFA state machine पूर्णांकerfaces
 */

प्रकार व्योम (*bfa_sm_t)(व्योम *sm, पूर्णांक event);

/*
 * oc - object class eg. bfa_ioc
 * st - state, eg. reset
 * otype - object type, eg. काष्ठा bfa_ioc_s
 * etype - object type, eg. क्रमागत ioc_event
 */
#घोषणा bfa_sm_state_decl(oc, st, otype, etype)		\
	अटल व्योम oc ## _sm_ ## st(otype * fsm, etype event)

#घोषणा bfa_sm_set_state(_sm, _state)	((_sm)->sm = (bfa_sm_t)(_state))
#घोषणा bfa_sm_send_event(_sm, _event)	((_sm)->sm((_sm), (_event)))
#घोषणा bfa_sm_get_state(_sm)		((_sm)->sm)
#घोषणा bfa_sm_cmp_state(_sm, _state)	((_sm)->sm == (bfa_sm_t)(_state))

/*
 * For converting from state machine function to state encoding.
 */
काष्ठा bfa_sm_table_s अणु
	bfa_sm_t	sm;	/*  state machine function	*/
	पूर्णांक		state;	/*  state machine encoding	*/
	अक्षर		*name;	/*  state name क्रम display	*/
पूर्ण;
#घोषणा BFA_SM(_sm)	((bfa_sm_t)(_sm))

/*
 * State machine with entry actions.
 */
प्रकार व्योम (*bfa_fsm_t)(व्योम *fsm, पूर्णांक event);

/*
 * oc - object class eg. bfa_ioc
 * st - state, eg. reset
 * otype - object type, eg. काष्ठा bfa_ioc_s
 * etype - object type, eg. क्रमागत ioc_event
 */
#घोषणा bfa_fsm_state_decl(oc, st, otype, etype)		\
	अटल व्योम oc ## _sm_ ## st(otype * fsm, etype event);      \
	अटल व्योम oc ## _sm_ ## st ## _entry(otype * fsm)

#घोषणा bfa_fsm_set_state(_fsm, _state) करो अणु	\
	(_fsm)->fsm = (bfa_fsm_t)(_state);      \
	_state ## _entry(_fsm);      \
पूर्ण जबतक (0)

#घोषणा bfa_fsm_send_event(_fsm, _event)	((_fsm)->fsm((_fsm), (_event)))
#घोषणा bfa_fsm_get_state(_fsm)			((_fsm)->fsm)
#घोषणा bfa_fsm_cmp_state(_fsm, _state)		\
	((_fsm)->fsm == (bfa_fsm_t)(_state))

अटल अंतरभूत पूर्णांक
bfa_sm_to_state(काष्ठा bfa_sm_table_s *smt, bfa_sm_t sm)
अणु
	पूर्णांक	i = 0;

	जबतक (smt[i].sm && smt[i].sm != sm)
		i++;
	वापस smt[i].state;
पूर्ण

/*
 * @ Generic रुको counter.
 */

प्रकार व्योम (*bfa_wc_resume_t) (व्योम *cbarg);

काष्ठा bfa_wc_s अणु
	bfa_wc_resume_t wc_resume;
	व्योम		*wc_cbarg;
	पूर्णांक		wc_count;
पूर्ण;

अटल अंतरभूत व्योम
bfa_wc_up(काष्ठा bfa_wc_s *wc)
अणु
	wc->wc_count++;
पूर्ण

अटल अंतरभूत व्योम
bfa_wc_करोwn(काष्ठा bfa_wc_s *wc)
अणु
	wc->wc_count--;
	अगर (wc->wc_count == 0)
		wc->wc_resume(wc->wc_cbarg);
पूर्ण

/*
 * Initialize a रुकोing counter.
 */
अटल अंतरभूत व्योम
bfa_wc_init(काष्ठा bfa_wc_s *wc, bfa_wc_resume_t wc_resume, व्योम *wc_cbarg)
अणु
	wc->wc_resume = wc_resume;
	wc->wc_cbarg = wc_cbarg;
	wc->wc_count = 0;
	bfa_wc_up(wc);
पूर्ण

/*
 * Wait क्रम counter to reach zero
 */
अटल अंतरभूत व्योम
bfa_wc_रुको(काष्ठा bfa_wc_s *wc)
अणु
	bfa_wc_करोwn(wc);
पूर्ण

अटल अंतरभूत व्योम
wwn2str(अक्षर *wwn_str, u64 wwn)
अणु
	जोड़ अणु
		u64 wwn;
		u8 byte[8];
	पूर्ण w;

	w.wwn = wwn;
	प्र_लिखो(wwn_str, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", w.byte[0],
		w.byte[1], w.byte[2], w.byte[3], w.byte[4], w.byte[5],
		w.byte[6], w.byte[7]);
पूर्ण

अटल अंतरभूत व्योम
fcid2str(अक्षर *fcid_str, u32 fcid)
अणु
	जोड़ अणु
		u32 fcid;
		u8 byte[4];
	पूर्ण f;

	f.fcid = fcid;
	प्र_लिखो(fcid_str, "%02x:%02x:%02x", f.byte[1], f.byte[2], f.byte[3]);
पूर्ण

#घोषणा bfa_swap_3b(_x)				\
	((((_x) & 0xff) << 16) |		\
	((_x) & 0x00ff00) |			\
	(((_x) & 0xff0000) >> 16))

#अगर_अघोषित __BIG_ENDIAN
#घोषणा bfa_hton3b(_x)  bfa_swap_3b(_x)
#अन्यथा
#घोषणा bfa_hton3b(_x)  (_x)
#पूर्ण_अगर

#घोषणा bfa_ntoh3b(_x)  bfa_hton3b(_x)

#पूर्ण_अगर /* __BFA_CS_H__ */
