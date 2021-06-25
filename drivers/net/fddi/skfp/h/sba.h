<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/******************************************************************************
 *
 *	(C)Copyright 1998,1999 SysKonnect,
 *	a business unit of Schneider & Koch & Co. Datenप्रणालीe GmbH.
 *
 *	The inक्रमmation in this file is provided "AS IS" without warranty.
 *
 ******************************************************************************/

/*
 * Synchronous Bandwidth Allocation (SBA) काष्ठाs
 */
 
#अगर_अघोषित _SBA_
#घोषणा _SBA_

#समावेश "mbuf.h"
#समावेश "sba_def.h"

#अगर_घोषित	SBA

/* Timer Cell Template */
काष्ठा समयr_cell अणु
	काष्ठा समयr_cell	*next_ptr ;
	काष्ठा समयr_cell	*prev_ptr ;
	u_दीर्घ			start_समय ;
	काष्ठा s_sba_node_vars	*node_var ;
पूर्ण ;

/*
 * Node variables
 */
काष्ठा s_sba_node_vars अणु
	u_अक्षर			change_resp_flag ;
	u_अक्षर			report_resp_flag ;
	u_अक्षर			change_req_flag ;
	u_अक्षर			report_req_flag ;
	दीर्घ			change_amount ;
	दीर्घ			node_overhead ;
	दीर्घ			node_payload ;
	u_दीर्घ			node_status ;
	u_अक्षर			deallocate_status ;
	u_अक्षर			समयr_state ;
	u_लघु			report_cnt ;
	दीर्घ			lastrep_req_tranid ;
	काष्ठा fddi_addr	mac_address ;
	काष्ठा s_sba_sessions 	*node_sessions ;
	काष्ठा समयr_cell	समयr ;
पूर्ण ;

/*
 * Session variables
 */
काष्ठा s_sba_sessions अणु
	u_दीर्घ			deallocate_status ;
	दीर्घ			session_overhead ;
	u_दीर्घ			min_segment_size ;
	दीर्घ			session_payload ;
	u_दीर्घ			session_status ;
	u_दीर्घ			sba_category ;
	दीर्घ			lastchg_req_tranid ;
	u_लघु			session_id ;
	u_अक्षर			class ;
	u_अक्षर			fddi2 ;
	u_दीर्घ			max_t_neg ;
	काष्ठा s_sba_sessions	*next_session ;
पूर्ण ;

काष्ठा s_sba अणु

	काष्ठा s_sba_node_vars	node[MAX_NODES] ;
	काष्ठा s_sba_sessions	session[MAX_SESSIONS] ;

	काष्ठा s_sba_sessions	*मुक्त_session ;	/* poपूर्णांकs to the first */
						/* मुक्त session */

	काष्ठा समयr_cell	*tail_समयr ;	/* poपूर्णांकs to the last समयr cell */

	/*
	 * variables क्रम allocation actions
	 */
	दीर्घ	total_payload ;		/* Total Payload */
	दीर्घ	total_overhead ;	/* Total Overhead */
	दीर्घ	sba_allocatable ;	/* allocatable sync bandwidth */

	/*
	 * RAF message receive parameters
	 */
	दीर्घ		msg_path_index ;	/* Path Type */
	दीर्घ		msg_sba_pl_req ;	/* Payload Request */
	दीर्घ		msg_sba_ov_req ;	/* Overhead Request */
	दीर्घ		msg_mib_pl ;		/* Current Payload क्रम this Path */
	दीर्घ		msg_mib_ov ;		/* Current Overhead क्रम this Path*/
	दीर्घ		msg_category ;		/* Category of the Allocation */
	u_दीर्घ		msg_max_t_neg ;		/* दीर्घest T_Neg acceptable */
	u_दीर्घ		msg_min_seg_siz ;	/* minimum segement size */
	काष्ठा smt_header	*sm ;		/* poपूर्णांकs to the rec message */
	काष्ठा fddi_addr	*msg_alloc_addr ;	/* Allocation Address */

	/*
	 * SBA variables
	 */
	u_दीर्घ	sba_t_neg ;		/* holds the last T_NEG */
	दीर्घ	sba_max_alloc ;		/* the parsed value of SBAAvailable */	

	/*
	 * SBA state machine variables
	 */
	लघु	sba_next_state ;	/* the next state of the SBA */
	अक्षर	sba_command ;		/* holds the execuded SBA cmd */
	u_अक्षर	sba_available ;		/* parsed value after possible check */
पूर्ण ;

#पूर्ण_अगर	/* SBA */

	/*
	 * variables क्रम the End Station Support
	 */
काष्ठा s_ess अणु

	/*
	 * flags and counters
	 */
	u_अक्षर	sync_bw_available ;	/* is set अगर sync bw is allocated */
	u_अक्षर	local_sba_active ;	/* set when a local sba is available */
	अक्षर	raf_act_समयr_poll ;	/* activate the समयr to send allc req */
	अक्षर	समयr_count ;		/* counts every समयr function call */

	SMbuf	*sba_reply_pend ;	/* local reply क्रम the sba is pending */
	
	/*
	 * variables क्रम the ess bandwidth control
	 */
	दीर्घ	sync_bw ;		/* holds the allocaed sync bw */
	u_दीर्घ	alloc_trans_id ;	/* trans id of the last alloc req */
पूर्ण ;
#पूर्ण_अगर
