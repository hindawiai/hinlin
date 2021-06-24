<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_PHY_LCN_H_
#घोषणा B43_PHY_LCN_H_

#समावेश "phy_common.h"


#घोषणा B43_PHY_LCN_AFE_CTL1			B43_PHY_OFDM(0x03B)
#घोषणा B43_PHY_LCN_AFE_CTL2			B43_PHY_OFDM(0x03C)
#घोषणा B43_PHY_LCN_RF_CTL1			B43_PHY_OFDM(0x04C)
#घोषणा B43_PHY_LCN_RF_CTL2			B43_PHY_OFDM(0x04D)
#घोषणा B43_PHY_LCN_TABLE_ADDR			B43_PHY_OFDM(0x055) /* Table address */
#घोषणा B43_PHY_LCN_TABLE_DATALO		B43_PHY_OFDM(0x056) /* Table data low */
#घोषणा B43_PHY_LCN_TABLE_DATAHI		B43_PHY_OFDM(0x057) /* Table data high */
#घोषणा B43_PHY_LCN_RF_CTL3			B43_PHY_OFDM(0x0B0)
#घोषणा B43_PHY_LCN_RF_CTL4			B43_PHY_OFDM(0x0B1)
#घोषणा B43_PHY_LCN_RF_CTL5			B43_PHY_OFDM(0x0B7)
#घोषणा B43_PHY_LCN_RF_CTL6			B43_PHY_OFDM(0x0F9)
#घोषणा B43_PHY_LCN_RF_CTL7			B43_PHY_OFDM(0x0FA)


काष्ठा b43_phy_lcn अणु
	bool hw_pwr_ctl;
	bool hw_pwr_ctl_capable;
	u8 tx_pwr_curr_idx;
पूर्ण;


काष्ठा b43_phy_operations;
बाह्य स्थिर काष्ठा b43_phy_operations b43_phyops_lcn;

#पूर्ण_अगर /* B43_PHY_LCN_H_ */
