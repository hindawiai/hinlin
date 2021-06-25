<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_DEBUG_H
#घोषणा __RTW_DEBUG_H

क्रमागत rtw_debug_mask अणु
	RTW_DBG_PCI		= 0x00000001,
	RTW_DBG_TX		= 0x00000002,
	RTW_DBG_RX		= 0x00000004,
	RTW_DBG_PHY		= 0x00000008,
	RTW_DBG_FW		= 0x00000010,
	RTW_DBG_EFUSE		= 0x00000020,
	RTW_DBG_COEX		= 0x00000040,
	RTW_DBG_RFK		= 0x00000080,
	RTW_DBG_REGD		= 0x00000100,
	RTW_DBG_DEBUGFS		= 0x00000200,
	RTW_DBG_PS		= 0x00000400,
	RTW_DBG_BF		= 0x00000800,
	RTW_DBG_WOW		= 0x00001000,
	RTW_DBG_CFO		= 0x00002000,

	RTW_DBG_ALL		= 0xffffffff
पूर्ण;

#अगर_घोषित CONFIG_RTW88_DEBUGFS

व्योम rtw_debugfs_init(काष्ठा rtw_dev *rtwdev);
व्योम rtw_debugfs_get_simple_phy_info(काष्ठा seq_file *m);

#अन्यथा

अटल अंतरभूत व्योम rtw_debugfs_init(काष्ठा rtw_dev *rtwdev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_RTW88_DEBUGFS */

#अगर_घोषित CONFIG_RTW88_DEBUG

__म_लिखो(3, 4)
व्योम __rtw_dbg(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_debug_mask mask,
	       स्थिर अक्षर *fmt, ...);

#घोषणा rtw_dbg(rtwdev, a...) __rtw_dbg(rtwdev, ##a)

#अन्यथा

अटल अंतरभूत व्योम rtw_dbg(काष्ठा rtw_dev *rtwdev, क्रमागत rtw_debug_mask mask,
			   स्थिर अक्षर *fmt, ...) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_RTW88_DEBUG */

#घोषणा rtw_info(rtwdev, a...) dev_info(rtwdev->dev, ##a)
#घोषणा rtw_warn(rtwdev, a...) dev_warn(rtwdev->dev, ##a)
#घोषणा rtw_err(rtwdev, a...) dev_err(rtwdev->dev, ##a)

#पूर्ण_अगर
