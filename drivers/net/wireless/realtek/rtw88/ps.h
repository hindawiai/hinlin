<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_PS_H_
#घोषणा __RTW_PS_H_

#घोषणा RTW_LPS_THRESHOLD	50

#घोषणा POWER_MODE_ACK		BIT(6)
#घोषणा POWER_MODE_PG		BIT(4)
#घोषणा POWER_MODE_LCLK		BIT(0)

#घोषणा LEAVE_LPS_TRY_CNT	5
#घोषणा LEAVE_LPS_TIMEOUT	msecs_to_jअगरfies(100)

पूर्णांक rtw_enter_ips(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_leave_ips(काष्ठा rtw_dev *rtwdev);

व्योम rtw_घातer_mode_change(काष्ठा rtw_dev *rtwdev, bool enter);
व्योम rtw_enter_lps(काष्ठा rtw_dev *rtwdev, u8 port_id);
व्योम rtw_leave_lps(काष्ठा rtw_dev *rtwdev);
व्योम rtw_leave_lps_deep(काष्ठा rtw_dev *rtwdev);
क्रमागत rtw_lps_deep_mode rtw_get_lps_deep_mode(काष्ठा rtw_dev *rtwdev);
#पूर्ण_अगर
