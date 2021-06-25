<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTW_EVENT_H_
#घोषणा _RTW_EVENT_H_

#समावेश <osdep_service.h>

#समावेश <wlan_bssdef.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sem.h>

/*
 * Used to report a bss has been scanned
 */
काष्ठा survey_event	अणु
	काष्ठा wlan_bssid_ex bss;
पूर्ण;

/*
 * Used to report that the requested site survey has been करोne.
 *
 * bss_cnt indicates the number of bss that has been reported.
 *
 *
 */
काष्ठा surveyकरोne_event अणु
	अचिन्हित पूर्णांक	bss_cnt;

पूर्ण;

/*
 * Used to report the link result of joinning the given bss
 *
 *
 * join_res:
 * -1: authentication fail
 * -2: association fail
 * > 0: TID
 *
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
	पूर्णांक    cam_id;
पूर्ण;

काष्ठा stadel_event अणु
	अचिन्हित अक्षर macaddr[6];
	अचिन्हित अक्षर rsvd[2]; /* क्रम reason */
	पूर्णांक mac_id;
पूर्ण;

काष्ठा fwevent अणु
	u32	parmsize;
	व्योम (*event_callback)(काष्ठा adapter *dev, u8 *pbuf);
पूर्ण;

#घोषणा C2HEVENT_SZ			32

#घोषणा NETWORK_QUEUE_SZ	4

काष्ठा network_queue अणु
	पूर्णांक	head;
	पूर्णांक	tail;
	काष्ठा wlan_bssid_ex networks[NETWORK_QUEUE_SZ];
पूर्ण;

#पूर्ण_अगर /*  _WLANEVENT_H_ */
