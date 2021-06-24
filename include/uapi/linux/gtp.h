<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_GTP_H_
#घोषणा _UAPI_LINUX_GTP_H_

#घोषणा GTP_GENL_MCGRP_NAME	"gtp"

क्रमागत gtp_genl_cmds अणु
	GTP_CMD_NEWPDP,
	GTP_CMD_DELPDP,
	GTP_CMD_GETPDP,

	GTP_CMD_MAX,
पूर्ण;

क्रमागत gtp_version अणु
	GTP_V0 = 0,
	GTP_V1,
पूर्ण;

क्रमागत gtp_attrs अणु
	GTPA_UNSPEC = 0,
	GTPA_LINK,
	GTPA_VERSION,
	GTPA_TID,	/* क्रम GTPv0 only */
	GTPA_PEER_ADDRESS,	/* Remote GSN peer, either SGSN or GGSN */
#घोषणा GTPA_SGSN_ADDRESS GTPA_PEER_ADDRESS /* मुख्यtain legacy attr name */
	GTPA_MS_ADDRESS,
	GTPA_FLOW,
	GTPA_NET_NS_FD,
	GTPA_I_TEI,	/* क्रम GTPv1 only */
	GTPA_O_TEI,	/* क्रम GTPv1 only */
	GTPA_PAD,
	__GTPA_MAX,
पूर्ण;
#घोषणा GTPA_MAX (__GTPA_MAX + 1)

#पूर्ण_अगर /* _UAPI_LINUX_GTP_H_ */
