<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright(c) 2007 Intel Corporation. All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#अगर_अघोषित _FC_GS_H_
#घोषणा	_FC_GS_H_

#समावेश <linux/types.h>

/*
 * Fibre Channel Services - Common Transport.
 * From T11.org FC-GS-2 Rev 5.3 November 1998.
 */

काष्ठा fc_ct_hdr अणु
	__u8		ct_rev;		/* revision */
	__u8		ct_in_id[3];	/* N_Port ID of original requestor */
	__u8		ct_fs_type;	/* type of fibre channel service */
	__u8		ct_fs_subtype;	/* subtype */
	__u8		ct_options;
	__u8		_ct_resvd1;
	__be16		ct_cmd;		/* command / response code */
	__be16		ct_mr_size;	/* maximum / residual size */
	__u8		_ct_resvd2;
	__u8		ct_reason;	/* reject reason */
	__u8		ct_explan;	/* reason code explanation */
	__u8		ct_venकरोr;	/* venकरोr unique data */
पूर्ण;

#घोषणा	FC_CT_HDR_LEN	16	/* expected माप (काष्ठा fc_ct_hdr) */

क्रमागत fc_ct_rev अणु
	FC_CT_REV = 1		/* common transport revision */
पूर्ण;

/*
 * ct_fs_type values.
 */
क्रमागत fc_ct_fs_type अणु
	FC_FST_ALIAS =	0xf8,	/* alias service */
	FC_FST_MGMT =	0xfa,	/* management service */
	FC_FST_TIME =	0xfb,	/* समय service */
	FC_FST_सूची =	0xfc,	/* directory service */
पूर्ण;

/*
 * ct_cmd: Command / response codes
 */
क्रमागत fc_ct_cmd अणु
	FC_FS_RJT =	0x8001,	/* reject */
	FC_FS_ACC =	0x8002,	/* accept */
पूर्ण;

/*
 * FS_RJT reason codes.
 */
क्रमागत fc_ct_reason अणु
	FC_FS_RJT_CMD =		0x01,	/* invalid command code */
	FC_FS_RJT_VER =		0x02,	/* invalid version level */
	FC_FS_RJT_LOG =		0x03,	/* logical error */
	FC_FS_RJT_IUSIZ =	0x04,	/* invalid IU size */
	FC_FS_RJT_BSY =		0x05,	/* logical busy */
	FC_FS_RJT_PROTO =	0x07,	/* protocol error */
	FC_FS_RJT_UNABL =	0x09,	/* unable to perक्रमm command request */
	FC_FS_RJT_UNSUP =	0x0b,	/* command not supported */
पूर्ण;

/*
 * FS_RJT reason code explanations.
 */
क्रमागत fc_ct_explan अणु
	FC_FS_EXP_NONE =	0x00,	/* no additional explanation */
	FC_FS_EXP_PID =		0x01,	/* port ID not रेजिस्टरed */
	FC_FS_EXP_PNAM =	0x02,	/* port name not रेजिस्टरed */
	FC_FS_EXP_NNAM =	0x03,	/* node name not रेजिस्टरed */
	FC_FS_EXP_COS =		0x04,	/* class of service not रेजिस्टरed */
	FC_FS_EXP_FTNR =	0x07,	/* FC-4 types not रेजिस्टरed */
	/* definitions not complete */
पूर्ण;

#पूर्ण_अगर /* _FC_GS_H_ */
