<शैली गुरु>
/*
 * This file is part of the Chelsio FCoE driver क्रम Linux.
 *
 * Copyright (c) 2008-2012 Chelsio Communications, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित __CSIO_MB_H__
#घोषणा __CSIO_MB_H__

#समावेश <linux/समयr.h>
#समावेश <linux/completion.h>

#समावेश "t4fw_api.h"
#समावेश "t4fw_api_stor.h"
#समावेश "csio_defs.h"

#घोषणा CSIO_STATS_OFFSET (2)
#घोषणा CSIO_NUM_STATS_PER_MB (6)

काष्ठा fw_fcoe_port_cmd_params अणु
	uपूर्णांक8_t		portid;
	uपूर्णांक8_t		idx;
	uपूर्णांक8_t		nstats;
पूर्ण;

#घोषणा CSIO_DUMP_MB(__hw, __num, __mb)					\
	csio_dbg(__hw, "\t%llx %llx %llx %llx %llx %llx %llx %llx\n",	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb),		\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 8),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 16),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 24),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 32),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 40),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 48),	\
		(अचिन्हित दीर्घ दीर्घ)csio_rd_reg64(__hw, __mb + 56))

#घोषणा CSIO_MB_MAX_REGS	8
#घोषणा CSIO_MAX_MB_SIZE	64
#घोषणा CSIO_MB_POLL_FREQ	5		/*  5 ms */
#घोषणा CSIO_MB_DEFAULT_TMO	FW_CMD_MAX_TIMEOUT

/* Device master in HELLO command */
क्रमागत csio_dev_master अणु CSIO_MASTER_CANT, CSIO_MASTER_MAY, CSIO_MASTER_MUST पूर्ण;

क्रमागत csio_mb_owner अणु CSIO_MBOWNER_NONE, CSIO_MBOWNER_FW, CSIO_MBOWNER_PL पूर्ण;

क्रमागत csio_dev_state अणु
	CSIO_DEV_STATE_UNINIT,
	CSIO_DEV_STATE_INIT,
	CSIO_DEV_STATE_ERR
पूर्ण;

#घोषणा FW_PARAM_DEV(param) \
	(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) | \
	 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_##param))

#घोषणा FW_PARAM_PFVF(param) \
	(FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_PFVF) | \
	 FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_PFVF_##param)|  \
	 FW_PARAMS_PARAM_Y_V(0) | \
	 FW_PARAMS_PARAM_Z_V(0))

#घोषणा CSIO_INIT_MBP(__mbp, __cp,  __पंचांगo, __priv, __fn, __clear)	\
करो अणु									\
	अगर (__clear)							\
		स_रखो((__cp), 0,					\
			    CSIO_MB_MAX_REGS * माप(__be64));		\
	INIT_LIST_HEAD(&(__mbp)->list);					\
	(__mbp)->पंचांगo		= (__पंचांगo);				\
	(__mbp)->priv		= (व्योम *)(__priv);			\
	(__mbp)->mb_cbfn	= (__fn);				\
	(__mbp)->mb_size	= माप(*(__cp));			\
पूर्ण जबतक (0)

काष्ठा csio_mbm_stats अणु
	uपूर्णांक32_t	n_req;		/* number of mbox req */
	uपूर्णांक32_t	n_rsp;		/* number of mbox rsp */
	uपूर्णांक32_t	n_activeq;	/* number of mbox req active Q */
	uपूर्णांक32_t	n_cbfnq;	/* number of mbox req cbfn Q */
	uपूर्णांक32_t	n_पंचांगo;		/* number of mbox समयout */
	uपूर्णांक32_t	n_cancel;	/* number of mbox cancel */
	uपूर्णांक32_t	n_err;		/* number of mbox error */
पूर्ण;

/* Driver version of Mailbox */
काष्ठा csio_mb अणु
	काष्ठा list_head	list;			/* क्रम req/resp */
							/* queue in driver */
	__be64			mb[CSIO_MB_MAX_REGS];	/* MB in HW क्रमmat */
	पूर्णांक			mb_size;		/* Size of this
							 * mailbox.
							 */
	uपूर्णांक32_t		पंचांगo;			/* Timeout */
	काष्ठा completion	cmplobj;		/* MB Completion
							 * object
							 */
	व्योम			(*mb_cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *);
							/* Callback fn */
	व्योम			*priv;			/* Owner निजी ptr */
पूर्ण;

काष्ठा csio_mbm अणु
	uपूर्णांक32_t		a_mbox;			/* Async mbox num */
	uपूर्णांक32_t		पूर्णांकr_idx;		/* Interrupt index */
	काष्ठा समयr_list	समयr;			/* Mbox समयr */
	काष्ठा csio_hw		*hw;			/* Hardware poपूर्णांकer */
	काष्ठा list_head	req_q;			/* Mbox request queue */
	काष्ठा list_head	cbfn_q;			/* Mbox completion q */
	काष्ठा csio_mb		*mcurrent;		/* Current mailbox */
	uपूर्णांक32_t		req_q_cnt;		/* Outstanding mbox
							 * cmds
							 */
	काष्ठा csio_mbm_stats	stats;			/* Statistics */
पूर्ण;

#घोषणा csio_set_mb_पूर्णांकr_idx(_m, _i)	((_m)->पूर्णांकr_idx = (_i))
#घोषणा csio_get_mb_पूर्णांकr_idx(_m)	((_m)->पूर्णांकr_idx)

काष्ठा csio_iq_params;
काष्ठा csio_eq_params;

क्रमागत fw_retval csio_mb_fw_retval(काष्ठा csio_mb *);

/* MB helpers */
व्योम csio_mb_hello(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t,
		   uपूर्णांक32_t, uपूर्णांक32_t, क्रमागत csio_dev_master,
		   व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_process_hello_rsp(काष्ठा csio_hw *, काष्ठा csio_mb *,
			       क्रमागत fw_retval *, क्रमागत csio_dev_state *,
			       uपूर्णांक8_t *);

व्योम csio_mb_bye(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t,
		 व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_reset(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t, पूर्णांक, पूर्णांक,
		   व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_params(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t, अचिन्हित पूर्णांक,
		    अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, स्थिर u32 *, u32 *, bool,
		    व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_process_पढ़ो_params_rsp(काष्ठा csio_hw *, काष्ठा csio_mb *,
				क्रमागत fw_retval *, अचिन्हित पूर्णांक , u32 *);

व्योम csio_mb_ldst(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp, uपूर्णांक32_t पंचांगo,
		  पूर्णांक reg);

व्योम csio_mb_caps_config(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t,
			    bool, bool, bool, bool,
			    व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_port(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t,
		  uपूर्णांक8_t, bool, uपूर्णांक32_t, uपूर्णांक16_t,
		  व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_process_पढ़ो_port_rsp(काष्ठा csio_hw *, काष्ठा csio_mb *,
				   क्रमागत fw_retval *, uपूर्णांक16_t,
				   uपूर्णांक32_t *, uपूर्णांक32_t *);

व्योम csio_mb_initialize(काष्ठा csio_hw *, काष्ठा csio_mb *, uपूर्णांक32_t,
			व्योम (*)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_iq_alloc_ग_लिखो(काष्ठा csio_hw *, काष्ठा csio_mb *, व्योम *,
			uपूर्णांक32_t, काष्ठा csio_iq_params *,
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_iq_alloc_ग_लिखो_rsp(काष्ठा csio_hw *, काष्ठा csio_mb *,
				क्रमागत fw_retval *, काष्ठा csio_iq_params *);

व्योम csio_mb_iq_मुक्त(काष्ठा csio_hw *, काष्ठा csio_mb *, व्योम *,
		     uपूर्णांक32_t, काष्ठा csio_iq_params *,
		     व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_eq_ofld_alloc_ग_लिखो(काष्ठा csio_hw *, काष्ठा csio_mb *, व्योम *,
				 uपूर्णांक32_t, काष्ठा csio_eq_params *,
				 व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_eq_ofld_alloc_ग_लिखो_rsp(काष्ठा csio_hw *, काष्ठा csio_mb *,
				     क्रमागत fw_retval *, काष्ठा csio_eq_params *);

व्योम csio_mb_eq_ofld_मुक्त(काष्ठा csio_hw *, काष्ठा csio_mb *, व्योम *,
			  uपूर्णांक32_t , काष्ठा csio_eq_params *,
			  व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_पढ़ो_res_info_init_mb(काष्ठा csio_hw *, काष्ठा csio_mb *,
			uपूर्णांक32_t,
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_ग_लिखो_fcoe_link_cond_init_mb(काष्ठा csio_lnode *, काष्ठा csio_mb *,
			uपूर्णांक32_t, uपूर्णांक8_t, uपूर्णांक32_t, uपूर्णांक8_t, bool, uपूर्णांक32_t,
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_vnp_alloc_init_mb(काष्ठा csio_lnode *, काष्ठा csio_mb *,
			uपूर्णांक32_t, uपूर्णांक32_t , uपूर्णांक32_t , uपूर्णांक16_t,
			uपूर्णांक8_t [8], uपूर्णांक8_t [8],
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_vnp_पढ़ो_init_mb(काष्ठा csio_lnode *, काष्ठा csio_mb *,
			uपूर्णांक32_t, uपूर्णांक32_t , uपूर्णांक32_t ,
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_vnp_मुक्त_init_mb(काष्ठा csio_lnode *, काष्ठा csio_mb *,
			uपूर्णांक32_t , uपूर्णांक32_t, uपूर्णांक32_t ,
			व्योम (*) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_पढ़ो_fcf_init_mb(काष्ठा csio_lnode *, काष्ठा csio_mb *,
			uपूर्णांक32_t, uपूर्णांक32_t, uपूर्णांक32_t,
			व्योम (*cbfn) (काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_fcoe_पढ़ो_portparams_init_mb(काष्ठा csio_hw *hw,
			काष्ठा csio_mb *mbp, uपूर्णांक32_t mb_पंचांगo,
			काष्ठा fw_fcoe_port_cmd_params *portparams,
			व्योम (*cbfn)(काष्ठा csio_hw *, काष्ठा csio_mb *));

व्योम csio_mb_process_portparams_rsp(काष्ठा csio_hw *hw, काष्ठा csio_mb *mbp,
				क्रमागत fw_retval *retval,
				काष्ठा fw_fcoe_port_cmd_params *portparams,
				काष्ठा fw_fcoe_port_stats *portstats);

/* MB module functions */
पूर्णांक csio_mbm_init(काष्ठा csio_mbm *, काष्ठा csio_hw *,
			    व्योम (*)(काष्ठा समयr_list *));
व्योम csio_mbm_निकास(काष्ठा csio_mbm *);
व्योम csio_mb_पूर्णांकr_enable(काष्ठा csio_hw *);
व्योम csio_mb_पूर्णांकr_disable(काष्ठा csio_hw *);

पूर्णांक csio_mb_issue(काष्ठा csio_hw *, काष्ठा csio_mb *);
व्योम csio_mb_completions(काष्ठा csio_hw *, काष्ठा list_head *);
पूर्णांक csio_mb_fwevt_handler(काष्ठा csio_hw *, __be64 *);
पूर्णांक csio_mb_isr_handler(काष्ठा csio_hw *);
काष्ठा csio_mb *csio_mb_पंचांगo_handler(काष्ठा csio_hw *);
व्योम csio_mb_cancel_all(काष्ठा csio_hw *, काष्ठा list_head *);

#पूर्ण_अगर /* अगरndef __CSIO_MB_H__ */
