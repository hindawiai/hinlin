<शैली गुरु>
#अगर_अघोषित LLC_C_ST_H
#घोषणा LLC_C_ST_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 *		2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */
/* Connection component state management */
/* connection states */
#घोषणा LLC_CONN_OUT_OF_SVC		 0	/* prior to allocation */
 
#घोषणा LLC_CONN_STATE_ADM		 1	/* disc, initial state */
#घोषणा LLC_CONN_STATE_SETUP		 2	/* disconnected state */
#घोषणा LLC_CONN_STATE_NORMAL		 3	/* connected state */
#घोषणा LLC_CONN_STATE_BUSY		 4	/* connected state */
#घोषणा LLC_CONN_STATE_REJ		 5	/* connected state */
#घोषणा LLC_CONN_STATE_AWAIT		 6	/* connected state */
#घोषणा LLC_CONN_STATE_AWAIT_BUSY	 7	/* connected state */
#घोषणा LLC_CONN_STATE_AWAIT_REJ	 8	/* connected state */
#घोषणा LLC_CONN_STATE_D_CONN		 9	/* disconnected state */
#घोषणा LLC_CONN_STATE_RESET		10	/* disconnected state */
#घोषणा LLC_CONN_STATE_ERROR		11	/* disconnected state */
#घोषणा LLC_CONN_STATE_TEMP		12	/* disconnected state */

#घोषणा NBR_CONN_STATES			12	/* size of state table */
#घोषणा NO_STATE_CHANGE			100

/* Connection state table काष्ठाure */
काष्ठा llc_conn_state_trans अणु
	llc_conn_ev_t	   ev;
	u8		   next_state;
	स्थिर llc_conn_ev_qfyr_t *ev_qualअगरiers;
	स्थिर llc_conn_action_t  *ev_actions;
पूर्ण;

काष्ठा llc_conn_state अणु
	u8			    current_state;
	काष्ठा llc_conn_state_trans **transitions;
पूर्ण;

बाह्य काष्ठा llc_conn_state llc_conn_state_table[];
#पूर्ण_अगर /* LLC_C_ST_H */
