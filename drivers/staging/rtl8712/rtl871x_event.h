<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित _RTL871x_EVENT_H_
#घोषणा _RTL871x_EVENT_H_

#समावेश "osdep_service.h"

#समावेश "wlan_bssdef.h"
#समावेश <linux/semaphore.h>
#समावेश <linux/sem.h>

/*
 * Used to report a bss has been scanned
 */
काष्ठा survey_event	अणु
	काष्ठा wlan_bssid_ex bss;
पूर्ण;

/*
 * Used to report that the requested site survey has been करोne.
 * bss_cnt indicates the number of bss that has been reported.
 */
काष्ठा surveyकरोne_event अणु
	अचिन्हित पूर्णांक	bss_cnt;

पूर्ण;

/*
 * Used to report the link result of joinning the given bss
 * join_res:
 *  -1: authentication fail
 *  -2: association fail
 *  > 0: TID
 */
काष्ठा joinbss_event अणु
	काष्ठा	wlan_network	network;
पूर्ण;

/*
 * Used to report a given STA has joinned the created BSS.
 * It is used in AP/Ad-HoC(M) mode.
 */
काष्ठा stassoc_event अणु
	अचिन्हित अक्षर macaddr[6];
	अचिन्हित अक्षर rsvd[2];
	__le32    cam_id;
पूर्ण;

काष्ठा stadel_event अणु
	अचिन्हित अक्षर macaddr[6];
	अचिन्हित अक्षर rsvd[2];
पूर्ण;

काष्ठा addba_event अणु
	अचिन्हित पूर्णांक tid;
पूर्ण;

#घोषणा GEN_EVT_CODE(event)	event ## _EVT_

काष्ठा fwevent अणु
	u32	parmsize;
	व्योम (*event_callback)(काष्ठा _adapter *dev, u8 *pbuf);
पूर्ण;

#घोषणा C2HEVENT_SZ			32
काष्ठा event_node अणु
	अचिन्हित अक्षर *node;
	अचिन्हित अक्षर evt_code;
	अचिन्हित लघु evt_sz;
	/*अस्थिर*/ पूर्णांक *caller_ff_tail;
	पूर्णांक	caller_ff_sz;
पूर्ण;

काष्ठा c2hevent_queue अणु
	/*अस्थिर*/ पूर्णांक	head;
	/*अस्थिर*/ पूर्णांक	tail;
	काष्ठा	event_node	nodes[C2HEVENT_SZ];
	अचिन्हित अक्षर	seq;
पूर्ण;

#घोषणा NETWORK_QUEUE_SZ	4

काष्ठा network_queue अणु
	/*अस्थिर*/ पूर्णांक	head;
	/*अस्थिर*/ पूर्णांक	tail;
	काष्ठा wlan_bssid_ex networks[NETWORK_QUEUE_SZ];
पूर्ण;

काष्ठा ADDBA_Req_Report_parm अणु
	अचिन्हित अक्षर MacAddress[ETH_ALEN];
	अचिन्हित लघु StartSeqNum;
	अचिन्हित अक्षर tid;
पूर्ण;

#समावेश "rtl8712_event.h"

#पूर्ण_अगर /* _WLANEVENT_H_ */

