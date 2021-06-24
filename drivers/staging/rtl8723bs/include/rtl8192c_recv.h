<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित _RTL8192C_RECV_H_
#घोषणा _RTL8192C_RECV_H_

#घोषणा RECV_BLK_SZ 512
#घोषणा RECV_BLK_CNT 16
#घोषणा RECV_BLK_TH RECV_BLK_CNT

#घोषणा MAX_RECVBUF_SZ (10240)

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


व्योम rtl8192c_translate_rx_संकेत_stuff(जोड़ recv_frame *precvframe, काष्ठा phy_stat *pphy_status);
व्योम rtl8192c_query_rx_desc_status(जोड़ recv_frame *precvframe, काष्ठा recv_stat *pdesc);

#पूर्ण_अगर
