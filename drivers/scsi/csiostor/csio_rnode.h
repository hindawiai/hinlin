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

#अगर_अघोषित __CSIO_RNODE_H__
#घोषणा __CSIO_RNODE_H__

#समावेश "csio_defs.h"

/* State machine evets */
क्रमागत csio_rn_ev अणु
	CSIO_RNFE_NONE = (uपूर्णांक32_t)0,			/* None */
	CSIO_RNFE_LOGGED_IN,				/* [N/F]Port login
							 * complete.
							 */
	CSIO_RNFE_PRLI_DONE,				/* PRLI completed */
	CSIO_RNFE_PLOGI_RECV,				/* Received PLOGI */
	CSIO_RNFE_PRLI_RECV,				/* Received PLOGI */
	CSIO_RNFE_LOGO_RECV,				/* Received LOGO */
	CSIO_RNFE_PRLO_RECV,				/* Received PRLO */
	CSIO_RNFE_DOWN,					/* Rnode is करोwn */
	CSIO_RNFE_CLOSE,				/* Close rnode */
	CSIO_RNFE_NAME_MISSING,				/* Rnode name missing
							 * in name server.
							 */
	CSIO_RNFE_MAX_EVENT,
पूर्ण;

/* rnode stats */
काष्ठा csio_rnode_stats अणु
	uपूर्णांक32_t	n_err;		/* error */
	uपूर्णांक32_t	n_err_inval;	/* invalid parameter */
	uपूर्णांक32_t	n_err_nomem;	/* error nomem */
	uपूर्णांक32_t	n_evt_unexp;	/* unexpected event */
	uपूर्णांक32_t	n_evt_drop;	/* unexpected event */
	uपूर्णांक32_t	n_evt_fw[PROTO_ERR_IMPL_LOGO + 1];	/* fw events */
	क्रमागत csio_rn_ev	n_evt_sm[CSIO_RNFE_MAX_EVENT];	/* State m/c events */
	uपूर्णांक32_t	n_lun_rst;	/* Number of resets of
					 * of LUNs under this
					 * target
					 */
	uपूर्णांक32_t	n_lun_rst_fail;	/* Number of LUN reset
					 * failures.
					 */
	uपूर्णांक32_t	n_tgt_rst;	/* Number of target resets */
	uपूर्णांक32_t	n_tgt_rst_fail;	/* Number of target reset
					 * failures.
					 */
पूर्ण;

/* Defines क्रम rnode role */
#घोषणा	CSIO_RNFR_INITIATOR	0x1
#घोषणा	CSIO_RNFR_TARGET	0x2
#घोषणा CSIO_RNFR_FABRIC	0x4
#घोषणा	CSIO_RNFR_NS		0x8
#घोषणा CSIO_RNFR_NPORT		0x10

काष्ठा csio_rnode अणु
	काष्ठा csio_sm		sm;			/* State machine -
							 * should be the
							 * 1st member
							 */
	काष्ठा csio_lnode	*lnp;			/* Poपूर्णांकer to owning
							 * Lnode */
	uपूर्णांक32_t		flowid;			/* Firmware ID */
	काष्ठा list_head	host_cmpl_q;		/* SCSI IOs
							 * pending to completed
							 * to Mid-layer.
							 */
	/* FC identअगरiers क्रम remote node */
	uपूर्णांक32_t		nport_id;
	uपूर्णांक16_t		fcp_flags;		/* FCP Flags */
	uपूर्णांक8_t			cur_evt;		/* Current event */
	uपूर्णांक8_t			prev_evt;		/* Previous event */
	uपूर्णांक32_t		role;			/* Fabric/Target/
							 * Initiator/NS
							 */
	काष्ठा fcoe_rdev_entry		*rdev_entry;	/* Rdev entry */
	काष्ठा csio_service_parms	rn_sparm;

	/* FC transport attributes */
	काष्ठा fc_rport		*rport;		/* FC transport rport */
	uपूर्णांक32_t		supp_classes;	/* Supported FC classes */
	uपूर्णांक32_t		maxframe_size;	/* Max Frame size */
	uपूर्णांक32_t		scsi_id;	/* Transport given SCSI id */

	काष्ठा csio_rnode_stats	stats;		/* Common rnode stats */
पूर्ण;

#घोषणा csio_rn_flowid(rn)			((rn)->flowid)
#घोषणा csio_rn_wwpn(rn)			((rn)->rn_sparm.wwpn)
#घोषणा csio_rn_wwnn(rn)			((rn)->rn_sparm.wwnn)
#घोषणा csio_rnode_to_lnode(rn)			((rn)->lnp)

पूर्णांक csio_is_rnode_पढ़ोy(काष्ठा csio_rnode *rn);
व्योम csio_rnode_state_to_str(काष्ठा csio_rnode *rn, पूर्णांक8_t *str);

काष्ठा csio_rnode *csio_rnode_lookup_portid(काष्ठा csio_lnode *, uपूर्णांक32_t);
काष्ठा csio_rnode *csio_confirm_rnode(काष्ठा csio_lnode *,
					  uपूर्णांक32_t, काष्ठा fcoe_rdev_entry *);

व्योम csio_rnode_fwevt_handler(काष्ठा csio_rnode *rn, uपूर्णांक8_t fwevt);

व्योम csio_put_rnode(काष्ठा csio_lnode *ln, काष्ठा csio_rnode *rn);

व्योम csio_reg_rnode(काष्ठा csio_rnode *);
व्योम csio_unreg_rnode(काष्ठा csio_rnode *);

व्योम csio_rnode_devloss_handler(काष्ठा csio_rnode *);

#पूर्ण_अगर /* अगरndef __CSIO_RNODE_H__ */
