<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Texas Instruments Ethernet Switch Driver
 *
 * Copyright (C) 2013 Texas Instruments
 *
 */
#अगर_अघोषित __CPSW_H__
#घोषणा __CPSW_H__

#समावेश <linux/अगर_ether.h>
#समावेश <linux/phy.h>

#घोषणा mac_hi(mac)	(((mac)[0] << 0) | ((mac)[1] << 8) |	\
			 ((mac)[2] << 16) | ((mac)[3] << 24))
#घोषणा mac_lo(mac)	(((mac)[4] << 0) | ((mac)[5] << 8))

#अगर IS_ENABLED(CONFIG_TI_CPSW_PHY_SEL)
व्योम cpsw_phy_sel(काष्ठा device *dev, phy_पूर्णांकerface_t phy_mode, पूर्णांक slave);
#अन्यथा
अटल अंतरभूत
व्योम cpsw_phy_sel(काष्ठा device *dev, phy_पूर्णांकerface_t phy_mode, पूर्णांक slave)
अणुपूर्ण
#पूर्ण_अगर
पूर्णांक ti_cm_get_macid(काष्ठा device *dev, पूर्णांक slave, u8 *mac_addr);

#पूर्ण_अगर /* __CPSW_H__ */
