<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2013 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTW_BTCOEX_H__
#घोषणा __RTW_BTCOEX_H__

#समावेश <drv_types.h>


#घोषणा	PACKET_NORMAL			0
#घोषणा	PACKET_DHCP				1
#घोषणा	PACKET_ARP				2
#घोषणा	PACKET_EAPOL			3

व्योम rtw_btcoex_MediaStatusNotअगरy(काष्ठा adapter *, u8 mediaStatus);
व्योम rtw_btcoex_HaltNotअगरy(काष्ठा adapter *);

/*  ================================================== */
/*  Below Functions are called by BT-Coex */
/*  ================================================== */
व्योम rtw_btcoex_RejectApAggregatedPacket(काष्ठा adapter *, u8 enable);
व्योम rtw_btcoex_LPS_Enter(काष्ठा adapter *);
व्योम rtw_btcoex_LPS_Leave(काष्ठा adapter *);

#पूर्ण_अगर /*  __RTW_BTCOEX_H__ */
