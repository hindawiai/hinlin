<शैली गुरु>
#अगर_अघोषित LLC_S_ST_H
#घोषणा LLC_S_ST_H
/*
 * Copyright (c) 1997 by Procom Technology,Inc.
 * 		 2001 by Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 *
 * This program can be redistributed or modअगरied under the terms of the
 * GNU General Public License as published by the Free Software Foundation.
 * This program is distributed without any warranty or implied warranty
 * of merchantability or fitness क्रम a particular purpose.
 *
 * See the GNU General Public License क्रम more details.
 */

#घोषणा LLC_NR_SAP_STATES	2       /* size of state table */

/* काष्ठाures and types */
/* SAP state table काष्ठाure */
काष्ठा llc_sap_state_trans अणु
	llc_sap_ev_t	  ev;
	u8		  next_state;
	स्थिर llc_sap_action_t *ev_actions;
पूर्ण;

काष्ठा llc_sap_state अणु
	u8			   curr_state;
	काष्ठा llc_sap_state_trans **transitions;
पूर्ण;

/* only access to SAP state table */
बाह्य काष्ठा llc_sap_state llc_sap_state_table[LLC_NR_SAP_STATES];
#पूर्ण_अगर /* LLC_S_ST_H */
