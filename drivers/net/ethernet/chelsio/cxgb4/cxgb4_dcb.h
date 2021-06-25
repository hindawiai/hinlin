<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2013-2014 Chelsio Communications.  All rights reserved.
 *
 *  Written by Anish Bhatt (anish@chelsio.com)
 */

#अगर_अघोषित __CXGB4_DCB_H
#घोषणा __CXGB4_DCB_H

#समावेश <linux/netdevice.h>
#समावेश <linux/dcbnl.h>
#समावेश <net/dcbnl.h>

#अगर_घोषित CONFIG_CHELSIO_T4_DCB

#घोषणा CXGB4_DCBX_FW_SUPPORT \
	(DCB_CAP_DCBX_VER_CEE | \
	 DCB_CAP_DCBX_VER_IEEE | \
	 DCB_CAP_DCBX_LLD_MANAGED)
#घोषणा CXGB4_DCBX_HOST_SUPPORT \
	(DCB_CAP_DCBX_VER_CEE | \
	 DCB_CAP_DCBX_VER_IEEE | \
	 DCB_CAP_DCBX_HOST)

#घोषणा CXGB4_MAX_PRIORITY      CXGB4_MAX_DCBX_APP_SUPPORTED
#घोषणा CXGB4_MAX_TCS           CXGB4_MAX_DCBX_APP_SUPPORTED

#घोषणा INIT_PORT_DCB_CMD(__pcmd, __port, __op, __action) \
	करो अणु \
		स_रखो(&(__pcmd), 0, माप(__pcmd)); \
		(__pcmd).op_to_portid = \
			cpu_to_be32(FW_CMD_OP_V(FW_PORT_CMD) | \
				    FW_CMD_REQUEST_F | \
				    FW_CMD_##__op##_F | \
				    FW_PORT_CMD_PORTID_V(__port)); \
		(__pcmd).action_to_len16 = \
			cpu_to_be32(FW_PORT_CMD_ACTION_V(__action) | \
				    FW_LEN16(pcmd)); \
	पूर्ण जबतक (0)

#घोषणा INIT_PORT_DCB_READ_PEER_CMD(__pcmd, __port) \
	INIT_PORT_DCB_CMD(__pcmd, __port, READ, FW_PORT_ACTION_DCB_READ_RECV)

#घोषणा INIT_PORT_DCB_READ_LOCAL_CMD(__pcmd, __port) \
	INIT_PORT_DCB_CMD(__pcmd, __port, READ, FW_PORT_ACTION_DCB_READ_TRANS)

#घोषणा INIT_PORT_DCB_READ_SYNC_CMD(__pcmd, __port) \
	INIT_PORT_DCB_CMD(__pcmd, __port, READ, FW_PORT_ACTION_DCB_READ_DET)

#घोषणा INIT_PORT_DCB_WRITE_CMD(__pcmd, __port) \
	INIT_PORT_DCB_CMD(__pcmd, __port, EXEC, FW_PORT_ACTION_L2_DCB_CFG)

#घोषणा IEEE_FAUX_SYNC(__dev, __dcb) \
	करो अणु \
		अगर ((__dcb)->dcb_version == FW_PORT_DCB_VER_IEEE) \
			cxgb4_dcb_state_fsm((__dev), \
					    CXGB4_DCB_INPUT_FW_ALLSYNCED); \
	पूर्ण जबतक (0)

/* States we can be in क्रम a port's Data Center Bridging.
 */
क्रमागत cxgb4_dcb_state अणु
	CXGB4_DCB_STATE_START,		/* initial unknown state */
	CXGB4_DCB_STATE_HOST,		/* we're using Host DCB (अगर at all) */
	CXGB4_DCB_STATE_FW_INCOMPLETE,	/* using firmware DCB, incomplete */
	CXGB4_DCB_STATE_FW_ALLSYNCED,	/* using firmware DCB, all sync'ed */
पूर्ण;

/* Data Center Bridging state input क्रम the Finite State Machine.
 */
क्रमागत cxgb4_dcb_state_input अणु
	/* Input from the firmware.
	 */
	CXGB4_DCB_INPUT_FW_DISABLED,	/* firmware DCB disabled */
	CXGB4_DCB_INPUT_FW_ENABLED,	/* firmware DCB enabled */
	CXGB4_DCB_INPUT_FW_INCOMPLETE,	/* firmware reports incomplete DCB */
	CXGB4_DCB_INPUT_FW_ALLSYNCED,	/* firmware reports all sync'ed */

पूर्ण;

/* Firmware DCB messages that we've received so far ...
 */
क्रमागत cxgb4_dcb_fw_msgs अणु
	CXGB4_DCB_FW_PGID	= 0x01,
	CXGB4_DCB_FW_PGRATE	= 0x02,
	CXGB4_DCB_FW_PRIORATE	= 0x04,
	CXGB4_DCB_FW_PFC	= 0x08,
	CXGB4_DCB_FW_APP_ID	= 0x10,
पूर्ण;

#घोषणा CXGB4_MAX_DCBX_APP_SUPPORTED 8

/* Data Center Bridging support;
 */
काष्ठा port_dcb_info अणु
	क्रमागत cxgb4_dcb_state state;	/* DCB State Machine */
	क्रमागत cxgb4_dcb_fw_msgs msgs;	/* DCB Firmware messages received */
	अचिन्हित पूर्णांक supported;		/* OS DCB capabilities supported */
	bool enabled;			/* OS Enabled state */

	/* Cached copies of DCB inक्रमmation sent by the firmware (in Host
	 * Native Endian क्रमmat).
	 */
	u32	pgid;			/* Priority Group[0..7] */
	u8	dcb_version;		/* Running DCBx version */
	u8	pfcen;			/* Priority Flow Control[0..7] */
	u8	pg_num_tcs_supported;	/* max PG Traffic Classes */
	u8	pfc_num_tcs_supported;	/* max PFC Traffic Classes */
	u8	pgrate[8];		/* Priority Group Rate[0..7] */
	u8	priorate[8];		/* Priority Rate[0..7] */
	u8	tsa[8];			/* TSA Algorithm[0..7] */
	काष्ठा app_priority अणु /* Application Inक्रमmation */
		u8	user_prio_map;	/* Priority Map bitfield */
		u8	sel_field;	/* Protocol ID पूर्णांकerpretation */
		u16	protocolid;	/* Protocol ID */
	पूर्ण app_priority[CXGB4_MAX_DCBX_APP_SUPPORTED];
पूर्ण;

व्योम cxgb4_dcb_state_init(काष्ठा net_device *);
व्योम cxgb4_dcb_version_init(काष्ठा net_device *);
व्योम cxgb4_dcb_reset(काष्ठा net_device *dev);
व्योम cxgb4_dcb_state_fsm(काष्ठा net_device *, क्रमागत cxgb4_dcb_state_input);
व्योम cxgb4_dcb_handle_fw_update(काष्ठा adapter *, स्थिर काष्ठा fw_port_cmd *);
व्योम cxgb4_dcb_set_caps(काष्ठा adapter *, स्थिर काष्ठा fw_port_cmd *);
बाह्य स्थिर काष्ठा dcbnl_rtnl_ops cxgb4_dcb_ops;

अटल अंतरभूत __u8 bitswap_1(अचिन्हित अक्षर val)
अणु
	वापस ((val & 0x80) >> 7) |
	       ((val & 0x40) >> 5) |
	       ((val & 0x20) >> 3) |
	       ((val & 0x10) >> 1) |
	       ((val & 0x08) << 1) |
	       ((val & 0x04) << 3) |
	       ((val & 0x02) << 5) |
	       ((val & 0x01) << 7);
पूर्ण

बाह्य स्थिर अक्षर * स्थिर dcb_ver_array[];

#घोषणा CXGB4_DCB_ENABLED true

#अन्यथा /* !CONFIG_CHELSIO_T4_DCB */

अटल अंतरभूत व्योम cxgb4_dcb_state_init(काष्ठा net_device *dev)
अणु
पूर्ण

#घोषणा CXGB4_DCB_ENABLED false

#पूर्ण_अगर /* !CONFIG_CHELSIO_T4_DCB */

#पूर्ण_अगर /* __CXGB4_DCB_H */
