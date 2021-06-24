<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFCTRL_H_
#घोषणा CFCTRL_H_
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <net/caअगर/cfsrvl.h>

/* CAIF Control packet commands */
क्रमागत cfctrl_cmd अणु
	CFCTRL_CMD_LINK_SETUP = 0,
	CFCTRL_CMD_LINK_DESTROY = 1,
	CFCTRL_CMD_LINK_ERR = 2,
	CFCTRL_CMD_ENUM = 3,
	CFCTRL_CMD_SLEEP = 4,
	CFCTRL_CMD_WAKE = 5,
	CFCTRL_CMD_LINK_RECONF = 6,
	CFCTRL_CMD_START_REASON = 7,
	CFCTRL_CMD_RADIO_SET = 8,
	CFCTRL_CMD_MODEM_SET = 9,
	CFCTRL_CMD_MASK = 0xf
पूर्ण;

/* Channel types */
क्रमागत cfctrl_srv अणु
	CFCTRL_SRV_DECM = 0,
	CFCTRL_SRV_VEI = 1,
	CFCTRL_SRV_VIDEO = 2,
	CFCTRL_SRV_DBG = 3,
	CFCTRL_SRV_DATAGRAM = 4,
	CFCTRL_SRV_RFM = 5,
	CFCTRL_SRV_UTIL = 6,
	CFCTRL_SRV_MASK = 0xf
पूर्ण;

#घोषणा CFCTRL_RSP_BIT 0x20
#घोषणा CFCTRL_ERR_BIT 0x10

काष्ठा cfctrl_rsp अणु
	व्योम (*linksetup_rsp)(काष्ठा cflayer *layer, u8 linkid,
			      क्रमागत cfctrl_srv serv, u8 phyid,
			      काष्ठा cflayer *adapt_layer);
	व्योम (*linkdestroy_rsp)(काष्ठा cflayer *layer, u8 linkid);
	व्योम (*linkerror_ind)(व्योम);
	व्योम (*क्रमागत_rsp)(व्योम);
	व्योम (*sleep_rsp)(व्योम);
	व्योम (*wake_rsp)(व्योम);
	व्योम (*restart_rsp)(व्योम);
	व्योम (*radioset_rsp)(व्योम);
	व्योम (*reject_rsp)(काष्ठा cflayer *layer, u8 linkid,
				काष्ठा cflayer *client_layer);
पूर्ण;

/* Link Setup Parameters क्रम CAIF-Links. */
काष्ठा cfctrl_link_param अणु
	क्रमागत cfctrl_srv linktype;/* (T3,T0) Type of Channel */
	u8 priority;		  /* (P4,P0) Priority of the channel */
	u8 phyid;		  /* (U2-U0) Physical पूर्णांकerface to connect */
	u8 endpoपूर्णांक;		  /* (E1,E0) Endpoपूर्णांक क्रम data channels */
	u8 chtype;		  /* (H1,H0) Channel-Type, applies to
				   *            VEI, DEBUG */
	जोड़ अणु
		काष्ठा अणु
			u8 connid;	/*  (D7,D0) Video LinkId */
		पूर्ण video;

		काष्ठा अणु
			u32 connid;	/* (N31,Ngit0) Connection ID used
					 *  क्रम Datagram */
		पूर्ण datagram;

		काष्ठा अणु
			u32 connid;	/* Connection ID used क्रम RFM */
			अक्षर volume[20];	/* Volume to mount क्रम RFM */
		पूर्ण rfm;		/* Configuration क्रम RFM */

		काष्ठा अणु
			u16 fअगरosize_kb;	/* Psock FIFO size in KB */
			u16 fअगरosize_bufs;	/* Psock # संकेत buffers */
			अक्षर name[16];	/* Name of the PSOCK service */
			u8 params[255];	/* Link setup Parameters> */
			u16 paramlen;	/* Length of Link Setup
						 *   Parameters */
		पूर्ण utility;	/* Configuration क्रम Utility Links (Psock) */
	पूर्ण u;
पूर्ण;

/* This काष्ठाure is used पूर्णांकernally in CFCTRL */
काष्ठा cfctrl_request_info अणु
	पूर्णांक sequence_no;
	क्रमागत cfctrl_cmd cmd;
	u8 channel_id;
	काष्ठा cfctrl_link_param param;
	काष्ठा cflayer *client_layer;
	काष्ठा list_head list;
पूर्ण;

काष्ठा cfctrl अणु
	काष्ठा cfsrvl serv;
	काष्ठा cfctrl_rsp res;
	atomic_t req_seq_no;
	atomic_t rsp_seq_no;
	काष्ठा list_head list;
	/* Protects from simultaneous access to first_req list */
	spinlock_t info_list_lock;
#अगर_अघोषित CAIF_NO_LOOP
	u8 loop_linkid;
	पूर्णांक loop_linkused[256];
	/* Protects simultaneous access to loop_linkid and loop_linkused */
	spinlock_t loop_linkid_lock;
#पूर्ण_अगर

पूर्ण;

व्योम cfctrl_क्रमागत_req(काष्ठा cflayer *cfctrl, u8 physlinkid);
पूर्णांक cfctrl_linkup_request(काष्ठा cflayer *cfctrl,
			   काष्ठा cfctrl_link_param *param,
			   काष्ठा cflayer *user_layer);
पूर्णांक  cfctrl_linkकरोwn_req(काष्ठा cflayer *cfctrl, u8 linkid,
			 काष्ठा cflayer *client);

काष्ठा cflayer *cfctrl_create(व्योम);
काष्ठा cfctrl_rsp *cfctrl_get_respfuncs(काष्ठा cflayer *layer);
पूर्णांक cfctrl_cancel_req(काष्ठा cflayer *layr, काष्ठा cflayer *adap_layer);
व्योम cfctrl_हटाओ(काष्ठा cflayer *layr);

#पूर्ण_अगर				/* CFCTRL_H_ */
