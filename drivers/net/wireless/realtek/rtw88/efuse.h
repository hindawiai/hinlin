<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#अगर_अघोषित __RTW_EFUSE_H__
#घोषणा __RTW_EFUSE_H__

#घोषणा EFUSE_HW_CAP_IGNORE		0
#घोषणा EFUSE_HW_CAP_PTCL_VHT		3
#घोषणा EFUSE_HW_CAP_SUPP_BW80		7
#घोषणा EFUSE_HW_CAP_SUPP_BW40		6

#घोषणा EFUSE_READ_FAIL			0xff

#घोषणा GET_EFUSE_HW_CAP_HCI(hw_cap)					       \
	le32_get_bits(*((__le32 *)(hw_cap) + 0x01), GENMASK(3, 0))
#घोषणा GET_EFUSE_HW_CAP_BW(hw_cap)					       \
	le32_get_bits(*((__le32 *)(hw_cap) + 0x01), GENMASK(18, 16))
#घोषणा GET_EFUSE_HW_CAP_NSS(hw_cap)					       \
	le32_get_bits(*((__le32 *)(hw_cap) + 0x01), GENMASK(20, 19))
#घोषणा GET_EFUSE_HW_CAP_ANT_NUM(hw_cap)				       \
	le32_get_bits(*((__le32 *)(hw_cap) + 0x01), GENMASK(23, 21))
#घोषणा GET_EFUSE_HW_CAP_PTCL(hw_cap)					       \
	le32_get_bits(*((__le32 *)(hw_cap) + 0x01), GENMASK(27, 26))

पूर्णांक rtw_parse_efuse_map(काष्ठा rtw_dev *rtwdev);
पूर्णांक rtw_पढ़ो8_physical_efuse(काष्ठा rtw_dev *rtwdev, u16 addr, u8 *data);

#पूर्ण_अगर
