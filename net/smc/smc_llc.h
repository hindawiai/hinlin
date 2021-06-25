<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  Definitions क्रम LLC (link layer control) message handling
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Klaus Wacker <Klaus.Wacker@de.ibm.com>
 *              Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_LLC_H
#घोषणा SMC_LLC_H

#समावेश "smc_wr.h"

#घोषणा SMC_LLC_FLAG_RESP		0x80

#घोषणा SMC_LLC_WAIT_FIRST_TIME		(5 * HZ)
#घोषणा SMC_LLC_WAIT_TIME		(2 * HZ)

क्रमागत smc_llc_reqresp अणु
	SMC_LLC_REQ,
	SMC_LLC_RESP
पूर्ण;

क्रमागत smc_llc_msg_type अणु
	SMC_LLC_CONFIRM_LINK		= 0x01,
	SMC_LLC_ADD_LINK		= 0x02,
	SMC_LLC_ADD_LINK_CONT		= 0x03,
	SMC_LLC_DELETE_LINK		= 0x04,
	SMC_LLC_CONFIRM_RKEY		= 0x06,
	SMC_LLC_TEST_LINK		= 0x07,
	SMC_LLC_CONFIRM_RKEY_CONT	= 0x08,
	SMC_LLC_DELETE_RKEY		= 0x09,
पूर्ण;

#घोषणा smc_link_करोwning(state) \
	(cmpxchg(state, SMC_LNK_ACTIVE, SMC_LNK_INACTIVE) == SMC_LNK_ACTIVE)

/* LLC DELETE LINK Request Reason Codes */
#घोषणा SMC_LLC_DEL_LOST_PATH		0x00010000
#घोषणा SMC_LLC_DEL_OP_INIT_TERM	0x00020000
#घोषणा SMC_LLC_DEL_PROG_INIT_TERM	0x00030000
#घोषणा SMC_LLC_DEL_PROT_VIOL		0x00040000
#घोषणा SMC_LLC_DEL_NO_ASYM_NEEDED	0x00050000
/* LLC DELETE LINK Response Reason Codes */
#घोषणा SMC_LLC_DEL_NOLNK	0x00100000  /* Unknown Link ID (no link) */
#घोषणा SMC_LLC_DEL_NOLGR	0x00200000  /* Unknown Link Group */

/* वापसs a usable link of the link group, or शून्य */
अटल अंतरभूत काष्ठा smc_link *smc_llc_usable_link(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++)
		अगर (smc_link_usable(&lgr->lnk[i]))
			वापस &lgr->lnk[i];
	वापस शून्य;
पूर्ण

/* set the termination reason code क्रम the link group */
अटल अंतरभूत व्योम smc_llc_set_termination_rsn(काष्ठा smc_link_group *lgr,
					       u32 rsn)
अणु
	अगर (!lgr->llc_termination_rsn)
		lgr->llc_termination_rsn = rsn;
पूर्ण

/* transmit */
पूर्णांक smc_llc_send_confirm_link(काष्ठा smc_link *lnk,
			      क्रमागत smc_llc_reqresp reqresp);
पूर्णांक smc_llc_send_add_link(काष्ठा smc_link *link, u8 mac[], u8 gid[],
			  काष्ठा smc_link *link_new,
			  क्रमागत smc_llc_reqresp reqresp);
पूर्णांक smc_llc_send_delete_link(काष्ठा smc_link *link, u8 link_del_id,
			     क्रमागत smc_llc_reqresp reqresp, bool orderly,
			     u32 reason);
व्योम smc_llc_srv_delete_link_local(काष्ठा smc_link *link, u8 del_link_id);
व्योम smc_llc_lgr_init(काष्ठा smc_link_group *lgr, काष्ठा smc_sock *smc);
व्योम smc_llc_lgr_clear(काष्ठा smc_link_group *lgr);
पूर्णांक smc_llc_link_init(काष्ठा smc_link *link);
व्योम smc_llc_link_active(काष्ठा smc_link *link);
व्योम smc_llc_link_clear(काष्ठा smc_link *link, bool log);
पूर्णांक smc_llc_करो_confirm_rkey(काष्ठा smc_link *send_link,
			    काष्ठा smc_buf_desc *rmb_desc);
पूर्णांक smc_llc_करो_delete_rkey(काष्ठा smc_link_group *lgr,
			   काष्ठा smc_buf_desc *rmb_desc);
पूर्णांक smc_llc_flow_initiate(काष्ठा smc_link_group *lgr,
			  क्रमागत smc_llc_flowtype type);
व्योम smc_llc_flow_stop(काष्ठा smc_link_group *lgr, काष्ठा smc_llc_flow *flow);
पूर्णांक smc_llc_eval_conf_link(काष्ठा smc_llc_qentry *qentry,
			   क्रमागत smc_llc_reqresp type);
व्योम smc_llc_link_set_uid(काष्ठा smc_link *link);
व्योम smc_llc_save_peer_uid(काष्ठा smc_llc_qentry *qentry);
काष्ठा smc_llc_qentry *smc_llc_रुको(काष्ठा smc_link_group *lgr,
				    काष्ठा smc_link *lnk,
				    पूर्णांक समय_out, u8 exp_msg);
काष्ठा smc_llc_qentry *smc_llc_flow_qentry_clr(काष्ठा smc_llc_flow *flow);
व्योम smc_llc_flow_qentry_del(काष्ठा smc_llc_flow *flow);
व्योम smc_llc_send_link_delete_all(काष्ठा smc_link_group *lgr, bool ord,
				  u32 rsn);
पूर्णांक smc_llc_cli_add_link(काष्ठा smc_link *link, काष्ठा smc_llc_qentry *qentry);
पूर्णांक smc_llc_srv_add_link(काष्ठा smc_link *link);
व्योम smc_llc_add_link_local(काष्ठा smc_link *link);
पूर्णांक smc_llc_init(व्योम) __init;

#पूर्ण_अगर /* SMC_LLC_H */
