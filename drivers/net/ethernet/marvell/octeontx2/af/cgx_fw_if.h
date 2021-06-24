<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 CGX driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#अगर_अघोषित __CGX_FW_INTF_H__
#घोषणा __CGX_FW_INTF_H__

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>

#घोषणा CGX_FIRMWARE_MAJOR_VER		1
#घोषणा CGX_FIRMWARE_MINOR_VER		0

#घोषणा CGX_EVENT_ACK                   1UL

/* CGX error types. set क्रम cmd response status as CGX_STAT_FAIL */
क्रमागत cgx_error_type अणु
	CGX_ERR_NONE,
	CGX_ERR_LMAC_NOT_ENABLED,
	CGX_ERR_LMAC_MODE_INVALID,
	CGX_ERR_REQUEST_ID_INVALID,
	CGX_ERR_PREV_ACK_NOT_CLEAR,
	CGX_ERR_PHY_LINK_DOWN,
	CGX_ERR_PCS_RESET_FAIL,
	CGX_ERR_AN_CPT_FAIL,
	CGX_ERR_TX_NOT_IDLE,
	CGX_ERR_RX_NOT_IDLE,
	CGX_ERR_SPUX_BR_BLKLOCK_FAIL,
	CGX_ERR_SPUX_RX_ALIGN_FAIL,
	CGX_ERR_SPUX_TX_FAULT,
	CGX_ERR_SPUX_RX_FAULT,
	CGX_ERR_SPUX_RESET_FAIL,
	CGX_ERR_SPUX_AN_RESET_FAIL,
	CGX_ERR_SPUX_USX_AN_RESET_FAIL,
	CGX_ERR_SMUX_RX_LINK_NOT_OK,
	CGX_ERR_PCS_RECV_LINK_FAIL,
	CGX_ERR_TRAINING_FAIL,
	CGX_ERR_RX_EQU_FAIL,
	CGX_ERR_SPUX_BER_FAIL,
	CGX_ERR_SPUX_RSFEC_ALGN_FAIL,
	CGX_ERR_SPUX_MARKER_LOCK_FAIL,
	CGX_ERR_SET_FEC_INVALID,
	CGX_ERR_SET_FEC_FAIL,
	CGX_ERR_MODULE_INVALID,
	CGX_ERR_MODULE_NOT_PRESENT,
	CGX_ERR_SPEED_CHANGE_INVALID,
पूर्ण;

/* LINK speed types */
क्रमागत cgx_link_speed अणु
	CGX_LINK_NONE,
	CGX_LINK_10M,
	CGX_LINK_100M,
	CGX_LINK_1G,
	CGX_LINK_2HG,
	CGX_LINK_5G,
	CGX_LINK_10G,
	CGX_LINK_20G,
	CGX_LINK_25G,
	CGX_LINK_40G,
	CGX_LINK_50G,
	CGX_LINK_80G,
	CGX_LINK_100G,
	CGX_LINK_SPEED_MAX,
पूर्ण;

क्रमागत CGX_MODE_ अणु
	CGX_MODE_SGMII,
	CGX_MODE_1000_BASEX,
	CGX_MODE_QSGMII,
	CGX_MODE_10G_C2C,
	CGX_MODE_10G_C2M,
	CGX_MODE_10G_KR,
	CGX_MODE_20G_C2C,
	CGX_MODE_25G_C2C,
	CGX_MODE_25G_C2M,
	CGX_MODE_25G_2_C2C,
	CGX_MODE_25G_CR,
	CGX_MODE_25G_KR,
	CGX_MODE_40G_C2C,
	CGX_MODE_40G_C2M,
	CGX_MODE_40G_CR4,
	CGX_MODE_40G_KR4,
	CGX_MODE_40GAUI_C2C,
	CGX_MODE_50G_C2C,
	CGX_MODE_50G_C2M,
	CGX_MODE_50G_4_C2C,
	CGX_MODE_50G_CR,
	CGX_MODE_50G_KR,
	CGX_MODE_80GAUI_C2C,
	CGX_MODE_100G_C2C,
	CGX_MODE_100G_C2M,
	CGX_MODE_100G_CR4,
	CGX_MODE_100G_KR4,
	CGX_MODE_MAX /* = 29 */
पूर्ण;
/* REQUEST ID types. Input to firmware */
क्रमागत cgx_cmd_id अणु
	CGX_CMD_NONE,
	CGX_CMD_GET_FW_VER,
	CGX_CMD_GET_MAC_ADDR,
	CGX_CMD_SET_MTU,
	CGX_CMD_GET_LINK_STS,		/* optional to user */
	CGX_CMD_LINK_BRING_UP,
	CGX_CMD_LINK_BRING_DOWN,
	CGX_CMD_INTERNAL_LBK,
	CGX_CMD_EXTERNAL_LBK,
	CGX_CMD_HIGIG,
	CGX_CMD_LINK_STAT_CHANGE,
	CGX_CMD_MODE_CHANGE,		/* hot plug support */
	CGX_CMD_INTF_SHUTDOWN,
	CGX_CMD_GET_MKEX_PRFL_SIZE,
	CGX_CMD_GET_MKEX_PRFL_ADDR,
	CGX_CMD_GET_FWD_BASE,		/* get base address of shared FW data */
	CGX_CMD_GET_LINK_MODES,		/* Supported Link Modes */
	CGX_CMD_SET_LINK_MODE,
	CGX_CMD_GET_SUPPORTED_FEC,
	CGX_CMD_SET_FEC,
	CGX_CMD_GET_AN,
	CGX_CMD_SET_AN,
	CGX_CMD_GET_ADV_LINK_MODES,
	CGX_CMD_GET_ADV_FEC,
	CGX_CMD_GET_PHY_MOD_TYPE, /* line-side modulation type: NRZ or PAM4 */
	CGX_CMD_SET_PHY_MOD_TYPE,
	CGX_CMD_PRBS,
	CGX_CMD_DISPLAY_EYE,
	CGX_CMD_GET_PHY_FEC_STATS,
पूर्ण;

/* async event ids */
क्रमागत cgx_evt_id अणु
	CGX_EVT_NONE,
	CGX_EVT_LINK_CHANGE,
पूर्ण;

/* event types - cause of पूर्णांकerrupt */
क्रमागत cgx_evt_type अणु
	CGX_EVT_ASYNC,
	CGX_EVT_CMD_RESP
पूर्ण;

क्रमागत cgx_stat अणु
	CGX_STAT_SUCCESS,
	CGX_STAT_FAIL
पूर्ण;

क्रमागत cgx_cmd_own अणु
	CGX_CMD_OWN_NS,
	CGX_CMD_OWN_FIRMWARE,
पूर्ण;

/* m - bit mask
 * y - value to be written in the bitrange
 * x - input value whose bitrange to be modअगरied
 */
#घोषणा FIELD_SET(m, y, x)		\
	(((x) & ~(m)) |			\
	FIELD_PREP((m), (y)))

/* scratchx(0) CSR used क्रम ATF->non-secure SW communication.
 * This acts as the status रेजिस्टर
 * Provides details on command ack/status, command response, error details
 */
#घोषणा EVTREG_ACK		BIT_ULL(0)
#घोषणा EVTREG_EVT_TYPE		BIT_ULL(1)
#घोषणा EVTREG_STAT		BIT_ULL(2)
#घोषणा EVTREG_ID		GENMASK_ULL(8, 3)

/* Response to command IDs with command status as CGX_STAT_FAIL
 *
 * Not applicable क्रम commands :
 * CGX_CMD_LINK_BRING_UP/DOWN/CGX_EVT_LINK_CHANGE
 */
#घोषणा EVTREG_ERRTYPE		GENMASK_ULL(18, 9)

/* Response to cmd ID as CGX_CMD_GET_FW_VER with cmd status as
 * CGX_STAT_SUCCESS
 */
#घोषणा RESP_MAJOR_VER		GENMASK_ULL(12, 9)
#घोषणा RESP_MINOR_VER		GENMASK_ULL(16, 13)

/* Response to cmd ID as CGX_CMD_GET_MAC_ADDR with cmd status as
 * CGX_STAT_SUCCESS
 */
#घोषणा RESP_MAC_ADDR		GENMASK_ULL(56, 9)

/* Response to cmd ID as CGX_CMD_GET_MKEX_PRFL_SIZE with cmd status as
 * CGX_STAT_SUCCESS
 */
#घोषणा RESP_MKEX_PRFL_SIZE		GENMASK_ULL(63, 9)

/* Response to cmd ID as CGX_CMD_GET_MKEX_PRFL_ADDR with cmd status as
 * CGX_STAT_SUCCESS
 */
#घोषणा RESP_MKEX_PRFL_ADDR		GENMASK_ULL(63, 9)

/* Response to cmd ID as CGX_CMD_GET_FWD_BASE with cmd status as
 * CGX_STAT_SUCCESS
 */
#घोषणा RESP_FWD_BASE		GENMASK_ULL(56, 9)
#घोषणा RESP_LINKSTAT_LMAC_TYPE                GENMASK_ULL(35, 28)

/* Response to cmd ID - CGX_CMD_LINK_BRING_UP/DOWN, event ID CGX_EVT_LINK_CHANGE
 * status can be either CGX_STAT_FAIL or CGX_STAT_SUCCESS
 *
 * In हाल of CGX_STAT_FAIL, it indicates CGX configuration failed
 * when processing link up/करोwn/change command.
 * Both err_type and current link status will be updated
 *
 * In हाल of CGX_STAT_SUCCESS, err_type will be CGX_ERR_NONE and current
 * link status will be updated
 */
काष्ठा cgx_lnk_sts अणु
	uपूर्णांक64_t reserved1:9;
	uपूर्णांक64_t link_up:1;
	uपूर्णांक64_t full_duplex:1;
	uपूर्णांक64_t speed:4;		/* cgx_link_speed */
	uपूर्णांक64_t err_type:10;
	uपूर्णांक64_t an:1;			/* AN supported or not */
	uपूर्णांक64_t fec:2;			/* FEC type अगर enabled, अगर not 0 */
	uपूर्णांक64_t port:8;
	uपूर्णांक64_t reserved2:28;
पूर्ण;

#घोषणा RESP_LINKSTAT_UP		GENMASK_ULL(9, 9)
#घोषणा RESP_LINKSTAT_FDUPLEX		GENMASK_ULL(10, 10)
#घोषणा RESP_LINKSTAT_SPEED		GENMASK_ULL(14, 11)
#घोषणा RESP_LINKSTAT_ERRTYPE		GENMASK_ULL(24, 15)
#घोषणा RESP_LINKSTAT_AN		GENMASK_ULL(25, 25)
#घोषणा RESP_LINKSTAT_FEC		GENMASK_ULL(27, 26)
#घोषणा RESP_LINKSTAT_PORT		GENMASK_ULL(35, 28)

/* scratchx(1) CSR used क्रम non-secure SW->ATF communication
 * This CSR acts as a command रेजिस्टर
 */
#घोषणा CMDREG_OWN	BIT_ULL(0)
#घोषणा CMDREG_ID	GENMASK_ULL(7, 2)

/* Any command using enable/disable as an argument need
 * to set this bitfield.
 * Ex: Loopback, HiGig...
 */
#घोषणा CMDREG_ENABLE	BIT_ULL(8)

/* command argument to be passed क्रम cmd ID - CGX_CMD_SET_MTU */
#घोषणा CMDMTU_SIZE	GENMASK_ULL(23, 8)

/* command argument to be passed क्रम cmd ID - CGX_CMD_LINK_CHANGE */
#घोषणा CMDLINKCHANGE_LINKUP	BIT_ULL(8)
#घोषणा CMDLINKCHANGE_FULLDPLX	BIT_ULL(9)
#घोषणा CMDLINKCHANGE_SPEED	GENMASK_ULL(13, 10)

#घोषणा CMDSETFEC			GENMASK_ULL(9, 8)
/* command argument to be passed क्रम cmd ID - CGX_CMD_MODE_CHANGE */
#घोषणा CMDMODECHANGE_SPEED		GENMASK_ULL(11, 8)
#घोषणा CMDMODECHANGE_DUPLEX		GENMASK_ULL(12, 12)
#घोषणा CMDMODECHANGE_AN		GENMASK_ULL(13, 13)
#घोषणा CMDMODECHANGE_PORT		GENMASK_ULL(21, 14)
#घोषणा CMDMODECHANGE_FLAGS		GENMASK_ULL(63, 22)

#पूर्ण_अगर /* __CGX_FW_INTF_H__ */
