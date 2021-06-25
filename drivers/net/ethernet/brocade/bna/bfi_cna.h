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
#अगर_अघोषित __BFI_CNA_H__
#घोषणा __BFI_CNA_H__

#समावेश "bfi.h"
#समावेश "bfa_defs_cna.h"

क्रमागत bfi_port_h2i अणु
	BFI_PORT_H2I_ENABLE_REQ		= (1),
	BFI_PORT_H2I_DISABLE_REQ	= (2),
	BFI_PORT_H2I_GET_STATS_REQ	= (3),
	BFI_PORT_H2I_CLEAR_STATS_REQ	= (4),
पूर्ण;

क्रमागत bfi_port_i2h अणु
	BFI_PORT_I2H_ENABLE_RSP		= BFA_I2HM(1),
	BFI_PORT_I2H_DISABLE_RSP	= BFA_I2HM(2),
	BFI_PORT_I2H_GET_STATS_RSP	= BFA_I2HM(3),
	BFI_PORT_I2H_CLEAR_STATS_RSP	= BFA_I2HM(4),
पूर्ण;

/* Generic REQ type */
काष्ठा bfi_port_generic_req अणु
	काष्ठा bfi_mhdr mh;		/*!< msg header			    */
	u32	msgtag;		/*!< msgtag क्रम reply		    */
	u32	rsvd;
पूर्ण __packed;

/* Generic RSP type */
काष्ठा bfi_port_generic_rsp अणु
	काष्ठा bfi_mhdr mh;		/*!< common msg header		    */
	u8		status;		/*!< port enable status		    */
	u8		rsvd[3];
	u32	msgtag;		/*!< msgtag क्रम reply		    */
पूर्ण __packed;

/* BFI_PORT_H2I_GET_STATS_REQ */
काष्ठा bfi_port_get_stats_req अणु
	काष्ठा bfi_mhdr mh;		/*!< common msg header		    */
	जोड़ bfi_addr_u   dma_addr;
पूर्ण __packed;

जोड़ bfi_port_h2i_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_port_generic_req enable_req;
	काष्ठा bfi_port_generic_req disable_req;
	काष्ठा bfi_port_get_stats_req माला_लोtats_req;
	काष्ठा bfi_port_generic_req clearstats_req;
पूर्ण __packed;

जोड़ bfi_port_i2h_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_port_generic_rsp enable_rsp;
	काष्ठा bfi_port_generic_rsp disable_rsp;
	काष्ठा bfi_port_generic_rsp माला_लोtats_rsp;
	काष्ठा bfi_port_generic_rsp clearstats_rsp;
पूर्ण __packed;

/* @brief Mailbox commands from host to (DCBX/LLDP) firmware */
क्रमागत bfi_cee_h2i_msgs अणु
	BFI_CEE_H2I_GET_CFG_REQ = 1,
	BFI_CEE_H2I_RESET_STATS = 2,
	BFI_CEE_H2I_GET_STATS_REQ = 3,
पूर्ण;

/* @brief Mailbox reply and AEN messages from DCBX/LLDP firmware to host */
क्रमागत bfi_cee_i2h_msgs अणु
	BFI_CEE_I2H_GET_CFG_RSP = BFA_I2HM(1),
	BFI_CEE_I2H_RESET_STATS_RSP = BFA_I2HM(2),
	BFI_CEE_I2H_GET_STATS_RSP = BFA_I2HM(3),
पूर्ण;

/* Data काष्ठाures */

/*
 * @brief H2I command काष्ठाure क्रम resetting the stats.
 * BFI_CEE_H2I_RESET_STATS
 */
काष्ठा bfi_lldp_reset_stats अणु
	काष्ठा bfi_mhdr mh;
पूर्ण __packed;

/*
 * @brief H2I command काष्ठाure क्रम resetting the stats.
 * BFI_CEE_H2I_RESET_STATS
 */
काष्ठा bfi_cee_reset_stats अणु
	काष्ठा bfi_mhdr mh;
पूर्ण __packed;

/*
 * @brief  get configuration  command from host
 * BFI_CEE_H2I_GET_CFG_REQ
 */
काष्ठा bfi_cee_get_req अणु
	काष्ठा bfi_mhdr mh;
	जोड़ bfi_addr_u   dma_addr;
पूर्ण __packed;

/*
 * @brief reply message from firmware
 * BFI_CEE_I2H_GET_CFG_RSP
 */
काष्ठा bfi_cee_get_rsp अणु
	काष्ठा bfi_mhdr mh;
	u8			cmd_status;
	u8			rsvd[3];
पूर्ण __packed;

/*
 * @brief  get configuration  command from host
 * BFI_CEE_H2I_GET_STATS_REQ
 */
काष्ठा bfi_cee_stats_req अणु
	काष्ठा bfi_mhdr mh;
	जोड़ bfi_addr_u   dma_addr;
पूर्ण __packed;

/*
 * @brief reply message from firmware
 * BFI_CEE_I2H_GET_STATS_RSP
 */
काष्ठा bfi_cee_stats_rsp अणु
	काष्ठा bfi_mhdr mh;
	u8			cmd_status;
	u8			rsvd[3];
पूर्ण __packed;

/* @brief mailbox command काष्ठाures from host to firmware */
जोड़ bfi_cee_h2i_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_cee_get_req get_req;
	काष्ठा bfi_cee_stats_req stats_req;
पूर्ण __packed;

/* @brief mailbox message काष्ठाures from firmware to host	*/
जोड़ bfi_cee_i2h_msg_u अणु
	काष्ठा bfi_mhdr mh;
	काष्ठा bfi_cee_get_rsp get_rsp;
	काष्ठा bfi_cee_stats_rsp stats_rsp;
पूर्ण __packed;

#पूर्ण_अगर /* __BFI_CNA_H__ */
