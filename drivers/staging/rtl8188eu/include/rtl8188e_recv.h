<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8188E_RECV_H__
#घोषणा __RTL8188E_RECV_H__

#घोषणा TX_RPT1_PKT_LEN 8

#घोषणा RECV_BLK_SZ 512
#घोषणा RECV_BLK_CNT 16
#घोषणा RECV_BLK_TH RECV_BLK_CNT
#घोषणा RECV_BULK_IN_ADDR		0x80
#घोषणा RECV_INT_IN_ADDR		0x81

#घोषणा NR_PREALLOC_RECV_SKB (8)

#घोषणा NR_RECVBUFF (4)

#घोषणा MAX_RECVBUF_SZ (15360) /*  15k < 16k */

काष्ठा phy_stat अणु
	अचिन्हित पूर्णांक phydw0;
	अचिन्हित पूर्णांक phydw1;
	अचिन्हित पूर्णांक phydw2;
	अचिन्हित पूर्णांक phydw3;
	अचिन्हित पूर्णांक phydw4;
	अचिन्हित पूर्णांक phydw5;
	अचिन्हित पूर्णांक phydw6;
	अचिन्हित पूर्णांक phydw7;
पूर्ण;

/*  Rx smooth factor */
#घोषणा	Rx_Smooth_Factor (20)

क्रमागत rx_packet_type अणु
	NORMAL_RX,/* Normal rx packet */
	TX_REPORT1,/* CCX */
	TX_REPORT2,/* TX RPT */
	HIS_REPORT,/*  USB HISR RPT */
पूर्ण;

#घोषणा INTERRUPT_MSG_FORMAT_LEN 60
व्योम rtl8188eu_recv_tasklet(काष्ठा tasklet_काष्ठा *t);
व्योम rtl8188e_process_phy_info(काष्ठा adapter *padapter,
			       काष्ठा recv_frame *prframe);
व्योम update_recvframe_phyinfo_88e(काष्ठा recv_frame *fra, काष्ठा phy_stat *phy);
व्योम update_recvframe_attrib_88e(काष्ठा recv_frame *fra,
				 काष्ठा recv_stat *stat);

#पूर्ण_अगर
