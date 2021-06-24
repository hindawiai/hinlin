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

#अगर_अघोषित __CSIO_LNODE_H__
#घोषणा __CSIO_LNODE_H__

#समावेश <linux/kref.h>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/fc/fc_els.h>


#समावेश "csio_defs.h"
#समावेश "csio_hw.h"

#घोषणा CSIO_FCOE_MAX_NPIV	128
#घोषणा CSIO_FCOE_MAX_RNODES	2048

/* FDMI port attribute unknown speed */
#घोषणा CSIO_HBA_PORTSPEED_UNKNOWN	0x8000

बाह्य पूर्णांक csio_fcoe_rnodes;
बाह्य पूर्णांक csio_fdmi_enable;

/* State machine evets */
क्रमागत csio_ln_ev अणु
	CSIO_LNE_NONE = (uपूर्णांक32_t)0,
	CSIO_LNE_LINKUP,
	CSIO_LNE_FAB_INIT_DONE,
	CSIO_LNE_LINK_DOWN,
	CSIO_LNE_DOWN_LINK,
	CSIO_LNE_LOGO,
	CSIO_LNE_CLOSE,
	CSIO_LNE_MAX_EVENT,
पूर्ण;


काष्ठा csio_fcf_info अणु
	काष्ठा list_head	list;
	uपूर्णांक8_t			priority;
	uपूर्णांक8_t			mac[6];
	uपूर्णांक8_t			name_id[8];
	uपूर्णांक8_t			fabric[8];
	uपूर्णांक16_t		vf_id;
	uपूर्णांक8_t			vlan_id;
	uपूर्णांक16_t		max_fcoe_size;
	uपूर्णांक8_t			fc_map[3];
	uपूर्णांक32_t		fka_adv;
	uपूर्णांक32_t		fcfi;
	uपूर्णांक8_t			get_next:1;
	uपूर्णांक8_t			link_aff:1;
	uपूर्णांक8_t			fpma:1;
	uपूर्णांक8_t			spma:1;
	uपूर्णांक8_t			login:1;
	uपूर्णांक8_t			portid;
	uपूर्णांक8_t			spma_mac[6];
	काष्ठा kref		kref;
पूर्ण;

/* Defines क्रम flags */
#घोषणा	CSIO_LNF_FIPSUPP		0x00000001	/* Fip Supported */
#घोषणा	CSIO_LNF_NPIVSUPP		0x00000002	/* NPIV supported */
#घोषणा CSIO_LNF_LINK_ENABLE		0x00000004	/* Link enabled */
#घोषणा	CSIO_LNF_FDMI_ENABLE		0x00000008	/* FDMI support */

/* Transport events */
क्रमागत csio_ln_fc_evt अणु
	CSIO_LN_FC_LINKUP = 1,
	CSIO_LN_FC_LINKDOWN,
	CSIO_LN_FC_RSCN,
	CSIO_LN_FC_ATTRIB_UPDATE,
पूर्ण;

/* Lnode stats */
काष्ठा csio_lnode_stats अणु
	uपूर्णांक32_t	n_link_up;	/* Link करोwn */
	uपूर्णांक32_t	n_link_करोwn;	/* Link up */
	uपूर्णांक32_t	n_err;		/* error */
	uपूर्णांक32_t	n_err_nomem;	/* memory not available */
	uपूर्णांक32_t	n_inval_parm;   /* Invalid parameters */
	uपूर्णांक32_t	n_evt_unexp;	/* unexpected event */
	uपूर्णांक32_t	n_evt_drop;	/* dropped event */
	uपूर्णांक32_t	n_rnode_match;  /* matched rnode */
	uपूर्णांक32_t	n_dev_loss_पंचांगo; /* Device loss समयout */
	uपूर्णांक32_t	n_fdmi_err;	/* fdmi err */
	uपूर्णांक32_t	n_evt_fw[PROTO_ERR_IMPL_LOGO + 1];	/* fw events */
	क्रमागत csio_ln_ev	n_evt_sm[CSIO_LNE_MAX_EVENT];	/* State m/c events */
	uपूर्णांक32_t	n_rnode_alloc;	/* rnode allocated */
	uपूर्णांक32_t	n_rnode_मुक्त;	/* rnode मुक्तd */
	uपूर्णांक32_t	n_rnode_nomem;	/* rnode alloc failure */
	uपूर्णांक32_t        n_input_requests; /* Input Requests */
	uपूर्णांक32_t        n_output_requests; /* Output Requests */
	uपूर्णांक32_t        n_control_requests; /* Control Requests */
	uपूर्णांक32_t        n_input_bytes; /* Input Bytes */
	uपूर्णांक32_t        n_output_bytes; /* Output Bytes */
	uपूर्णांक32_t	rsvd1;
पूर्ण;

/* Common Lnode params */
काष्ठा csio_lnode_params अणु
	uपूर्णांक32_t	ra_tov;
	uपूर्णांक32_t	fcfi;
	uपूर्णांक32_t	log_level;	/* Module level क्रम debugging */
पूर्ण;

काष्ठा csio_service_parms अणु
	काष्ठा fc_els_csp	csp;		/* Common service parms */
	uपूर्णांक8_t			wwpn[8];	/* WWPN */
	uपूर्णांक8_t			wwnn[8];	/* WWNN */
	काष्ठा fc_els_cssp	clsp[4];	/* Class service params */
	uपूर्णांक8_t			vvl[16];	/* Venकरोr version level */
पूर्ण;

/* Lnode */
काष्ठा csio_lnode अणु
	काष्ठा csio_sm		sm;		/* State machine + sibling
						 * lnode list.
						 */
	काष्ठा csio_hw		*hwp;		/* Poपूर्णांकer to the HW module */
	uपूर्णांक8_t			portid;		/* Port ID */
	uपूर्णांक8_t			rsvd1;
	uपूर्णांक16_t		rsvd2;
	uपूर्णांक32_t		dev_num;	/* Device number */
	uपूर्णांक32_t		flags;		/* Flags */
	काष्ठा list_head	fcf_lsthead;	/* FCF entries */
	काष्ठा csio_fcf_info	*fcfinfo;	/* FCF in use */
	काष्ठा csio_ioreq	*mgmt_req;	/* MGMT request */

	/* FCoE identअगरiers */
	uपूर्णांक8_t			mac[6];
	uपूर्णांक32_t		nport_id;
	काष्ठा csio_service_parms ln_sparm;	/* Service parms */

	/* Firmware identअगरiers */
	uपूर्णांक32_t		fcf_flowid;	/*fcf flowid */
	uपूर्णांक32_t		vnp_flowid;
	uपूर्णांक16_t		ssn_cnt;	/* Registered Session */
	uपूर्णांक8_t			cur_evt;	/* Current event */
	uपूर्णांक8_t			prev_evt;	/* Previous event */

	/* Children */
	काष्ठा list_head	cln_head;	/* Head of the children lnode
						 * list.
						 */
	uपूर्णांक32_t		num_vports;	/* Total NPIV/children LNodes*/
	काष्ठा csio_lnode	*pln;		/* Parent lnode of child
						 * lnodes.
						 */
	काष्ठा list_head	cmpl_q;		/* Pending I/Os on this lnode */

	/* Remote node inक्रमmation */
	काष्ठा list_head	rnhead;		/* Head of rnode list */
	uपूर्णांक32_t		num_reg_rnodes;	/* Number of rnodes रेजिस्टरed
						 * with the host.
						 */
	uपूर्णांक32_t		n_scsi_tgts;	/* Number of scsi tarमाला_लो
						 * found
						 */
	uपूर्णांक32_t		last_scan_ntgts;/* Number of scsi tarमाला_लो
						 * found per last scan.
						 */
	uपूर्णांक32_t		tgt_scan_tick;	/* समयr started after
						 * new tgt found
						 */
	/* FC transport data */
	काष्ठा fc_vport		*fc_vport;
	काष्ठा fc_host_statistics fch_stats;

	काष्ठा csio_lnode_stats stats;		/* Common lnode stats */
	काष्ठा csio_lnode_params params;	/* Common lnode params */
पूर्ण;

#घोषणा	csio_lnode_to_hw(ln)	((ln)->hwp)
#घोषणा csio_root_lnode(ln)	(csio_lnode_to_hw((ln))->rln)
#घोषणा csio_parent_lnode(ln)	((ln)->pln)
#घोषणा	csio_ln_flowid(ln)	((ln)->vnp_flowid)
#घोषणा csio_ln_wwpn(ln)	((ln)->ln_sparm.wwpn)
#घोषणा csio_ln_wwnn(ln)	((ln)->ln_sparm.wwnn)

#घोषणा csio_is_root_ln(ln)	(((ln) == csio_root_lnode((ln))) ? 1 : 0)
#घोषणा csio_is_phys_ln(ln)	(((ln)->pln == शून्य) ? 1 : 0)
#घोषणा csio_is_npiv_ln(ln)	(((ln)->pln != शून्य) ? 1 : 0)


#घोषणा csio_ln_dbg(_ln, _fmt, ...)	\
	csio_dbg(_ln->hwp, "%x:%x "_fmt, CSIO_DEVID_HI(_ln), \
		 CSIO_DEVID_LO(_ln), ##__VA_ARGS__);

#घोषणा csio_ln_err(_ln, _fmt, ...)	\
	csio_err(_ln->hwp, "%x:%x "_fmt, CSIO_DEVID_HI(_ln), \
		 CSIO_DEVID_LO(_ln), ##__VA_ARGS__);

#घोषणा csio_ln_warn(_ln, _fmt, ...)	\
	csio_warn(_ln->hwp, "%x:%x "_fmt, CSIO_DEVID_HI(_ln), \
		 CSIO_DEVID_LO(_ln), ##__VA_ARGS__);

/* HW->Lnode notअगरications */
क्रमागत csio_ln_notअगरy अणु
	CSIO_LN_NOTIFY_HWREADY = 1,
	CSIO_LN_NOTIFY_HWSTOP,
	CSIO_LN_NOTIFY_HWREMOVE,
	CSIO_LN_NOTIFY_HWRESET,
पूर्ण;

व्योम csio_fcoe_fwevt_handler(काष्ठा csio_hw *,  __u8 cpl_op, __be64 *);
पूर्णांक csio_is_lnode_पढ़ोy(काष्ठा csio_lnode *);
व्योम csio_lnode_state_to_str(काष्ठा csio_lnode *ln, पूर्णांक8_t *str);
काष्ठा csio_lnode *csio_lnode_lookup_by_wwpn(काष्ठा csio_hw *, uपूर्णांक8_t *);
पूर्णांक csio_get_phy_port_stats(काष्ठा csio_hw *, uपूर्णांक8_t ,
				      काष्ठा fw_fcoe_port_stats *);
पूर्णांक csio_scan_करोne(काष्ठा csio_lnode *, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		   अचिन्हित दीर्घ, अचिन्हित दीर्घ);
व्योम csio_notअगरy_lnodes(काष्ठा csio_hw *, क्रमागत csio_ln_notअगरy);
व्योम csio_disable_lnodes(काष्ठा csio_hw *, uपूर्णांक8_t, bool);
व्योम csio_lnode_async_event(काष्ठा csio_lnode *, क्रमागत csio_ln_fc_evt);
पूर्णांक csio_ln_fdmi_start(काष्ठा csio_lnode *, व्योम *);
पूर्णांक csio_lnode_start(काष्ठा csio_lnode *);
व्योम csio_lnode_stop(काष्ठा csio_lnode *);
व्योम csio_lnode_बंद(काष्ठा csio_lnode *);
पूर्णांक csio_lnode_init(काष्ठा csio_lnode *, काष्ठा csio_hw *,
			      काष्ठा csio_lnode *);
व्योम csio_lnode_निकास(काष्ठा csio_lnode *);

#पूर्ण_अगर /* अगरndef __CSIO_LNODE_H__ */
