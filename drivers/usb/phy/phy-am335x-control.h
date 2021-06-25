<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _AM335x_PHY_CONTROL_H_
#घोषणा _AM335x_PHY_CONTROL_H_

काष्ठा phy_control अणु
	व्योम (*phy_घातer)(काष्ठा phy_control *phy_ctrl, u32 id,
			क्रमागत usb_dr_mode dr_mode, bool on);
	व्योम (*phy_wkup)(काष्ठा phy_control *phy_ctrl, u32 id, bool on);
पूर्ण;

अटल अंतरभूत व्योम phy_ctrl_घातer(काष्ठा phy_control *phy_ctrl, u32 id,
				क्रमागत usb_dr_mode dr_mode, bool on)
अणु
	phy_ctrl->phy_घातer(phy_ctrl, id, dr_mode, on);
पूर्ण

अटल अंतरभूत व्योम phy_ctrl_wkup(काष्ठा phy_control *phy_ctrl, u32 id, bool on)
अणु
	phy_ctrl->phy_wkup(phy_ctrl, id, on);
पूर्ण

काष्ठा phy_control *am335x_get_phy_control(काष्ठा device *dev);

#पूर्ण_अगर
