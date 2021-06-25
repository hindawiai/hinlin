<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2018-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित AQ_PHY_H
#घोषणा AQ_PHY_H

#समावेश <linux/mdपन.स>

#समावेश "hw_atl/hw_atl_llh.h"
#समावेश "hw_atl/hw_atl_llh_internal.h"
#समावेश "aq_hw_utils.h"
#समावेश "aq_hw.h"

#घोषणा HW_ATL_PHY_ID_MAX 32U

bool aq_mdio_busy_रुको(काष्ठा aq_hw_s *aq_hw);

u16 aq_mdio_पढ़ो_word(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 addr);

व्योम aq_mdio_ग_लिखो_word(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 addr, u16 data);

u16 aq_phy_पढ़ो_reg(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 address);

व्योम aq_phy_ग_लिखो_reg(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 address, u16 data);

bool aq_phy_init_phy_id(काष्ठा aq_hw_s *aq_hw);

bool aq_phy_init(काष्ठा aq_hw_s *aq_hw);

व्योम aq_phy_disable_ptp(काष्ठा aq_hw_s *aq_hw);

#पूर्ण_अगर /* AQ_PHY_H */
