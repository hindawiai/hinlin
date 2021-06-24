<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2018-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

#समावेश "aq_phy.h"

#घोषणा HW_ATL_PTP_DISABLE_MSK	BIT(10)

bool aq_mdio_busy_रुको(काष्ठा aq_hw_s *aq_hw)
अणु
	पूर्णांक err = 0;
	u32 val;

	err = पढ़ोx_poll_समयout_atomic(hw_atl_mdio_busy_get, aq_hw,
					val, val == 0U, 10U, 100000U);

	अगर (err < 0)
		वापस false;

	वापस true;
पूर्ण

u16 aq_mdio_पढ़ो_word(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 addr)
अणु
	u16 phy_addr = aq_hw->phy_id << 5 | mmd;

	/* Set Address रेजिस्टर. */
	hw_atl_glb_mdio_अगरace4_set(aq_hw, (addr & HW_ATL_MDIO_ADDRESS_MSK) <<
				   HW_ATL_MDIO_ADDRESS_SHIFT);
	/* Send Address command. */
	hw_atl_glb_mdio_अगरace2_set(aq_hw, HW_ATL_MDIO_EXECUTE_OPERATION_MSK |
				   (3 << HW_ATL_MDIO_OP_MODE_SHIFT) |
				   ((phy_addr & HW_ATL_MDIO_PHY_ADDRESS_MSK) <<
				    HW_ATL_MDIO_PHY_ADDRESS_SHIFT));

	aq_mdio_busy_रुको(aq_hw);

	/* Send Read command. */
	hw_atl_glb_mdio_अगरace2_set(aq_hw, HW_ATL_MDIO_EXECUTE_OPERATION_MSK |
				   (1 << HW_ATL_MDIO_OP_MODE_SHIFT) |
				   ((phy_addr & HW_ATL_MDIO_PHY_ADDRESS_MSK) <<
				    HW_ATL_MDIO_PHY_ADDRESS_SHIFT));
	/* Read result. */
	aq_mdio_busy_रुको(aq_hw);

	वापस (u16)hw_atl_glb_mdio_अगरace5_get(aq_hw);
पूर्ण

व्योम aq_mdio_ग_लिखो_word(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 addr, u16 data)
अणु
	u16 phy_addr = aq_hw->phy_id << 5 | mmd;

	/* Set Address रेजिस्टर. */
	hw_atl_glb_mdio_अगरace4_set(aq_hw, (addr & HW_ATL_MDIO_ADDRESS_MSK) <<
				   HW_ATL_MDIO_ADDRESS_SHIFT);
	/* Send Address command. */
	hw_atl_glb_mdio_अगरace2_set(aq_hw, HW_ATL_MDIO_EXECUTE_OPERATION_MSK |
				   (3 << HW_ATL_MDIO_OP_MODE_SHIFT) |
				   ((phy_addr & HW_ATL_MDIO_PHY_ADDRESS_MSK) <<
				    HW_ATL_MDIO_PHY_ADDRESS_SHIFT));

	aq_mdio_busy_रुको(aq_hw);

	hw_atl_glb_mdio_अगरace3_set(aq_hw, (data & HW_ATL_MDIO_WRITE_DATA_MSK) <<
				   HW_ATL_MDIO_WRITE_DATA_SHIFT);
	/* Send Write command. */
	hw_atl_glb_mdio_अगरace2_set(aq_hw, HW_ATL_MDIO_EXECUTE_OPERATION_MSK |
				   (2 << HW_ATL_MDIO_OP_MODE_SHIFT) |
				   ((phy_addr & HW_ATL_MDIO_PHY_ADDRESS_MSK) <<
				    HW_ATL_MDIO_PHY_ADDRESS_SHIFT));

	aq_mdio_busy_रुको(aq_hw);
पूर्ण

u16 aq_phy_पढ़ो_reg(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 address)
अणु
	पूर्णांक err = 0;
	u32 val;

	err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_mdio_get, aq_hw,
					val, val == 1U, 10U, 100000U);

	अगर (err < 0) अणु
		err = 0xffff;
		जाओ err_निकास;
	पूर्ण

	err = aq_mdio_पढ़ो_word(aq_hw, mmd, address);

	hw_atl_reg_glb_cpu_sem_set(aq_hw, 1U, HW_ATL_FW_SM_MDIO);

err_निकास:
	वापस err;
पूर्ण

व्योम aq_phy_ग_लिखो_reg(काष्ठा aq_hw_s *aq_hw, u16 mmd, u16 address, u16 data)
अणु
	पूर्णांक err = 0;
	u32 val;

	err = पढ़ोx_poll_समयout_atomic(hw_atl_sem_mdio_get, aq_hw,
					val, val == 1U, 10U, 100000U);
	अगर (err < 0)
		वापस;

	aq_mdio_ग_लिखो_word(aq_hw, mmd, address, data);
	hw_atl_reg_glb_cpu_sem_set(aq_hw, 1U, HW_ATL_FW_SM_MDIO);
पूर्ण

bool aq_phy_init_phy_id(काष्ठा aq_hw_s *aq_hw)
अणु
	u16 val;

	क्रम (aq_hw->phy_id = 0; aq_hw->phy_id < HW_ATL_PHY_ID_MAX;
	     ++aq_hw->phy_id) अणु
		/* PMA Standard Device Identअगरier 2: Address 1.3 */
		val = aq_phy_पढ़ो_reg(aq_hw, MDIO_MMD_PMAPMD, 3);

		अगर (val != 0xffff)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool aq_phy_init(काष्ठा aq_hw_s *aq_hw)
अणु
	u32 dev_id;

	अगर (aq_hw->phy_id == HW_ATL_PHY_ID_MAX)
		अगर (!aq_phy_init_phy_id(aq_hw))
			वापस false;

	/* PMA Standard Device Identअगरier:
	 * Address 1.2 = MSW,
	 * Address 1.3 = LSW
	 */
	dev_id = aq_phy_पढ़ो_reg(aq_hw, MDIO_MMD_PMAPMD, 2);
	dev_id <<= 16;
	dev_id |= aq_phy_पढ़ो_reg(aq_hw, MDIO_MMD_PMAPMD, 3);

	अगर (dev_id == 0xffffffff) अणु
		aq_hw->phy_id = HW_ATL_PHY_ID_MAX;
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम aq_phy_disable_ptp(काष्ठा aq_hw_s *aq_hw)
अणु
	अटल स्थिर u16 ptp_रेजिस्टरs[] = अणु
		0x031e,
		0x031d,
		0x031c,
		0x031b,
	पूर्ण;
	u16 val;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ptp_रेजिस्टरs); i++) अणु
		val = aq_phy_पढ़ो_reg(aq_hw, MDIO_MMD_VEND1,
				      ptp_रेजिस्टरs[i]);

		aq_phy_ग_लिखो_reg(aq_hw, MDIO_MMD_VEND1,
				 ptp_रेजिस्टरs[i],
				 val & ~HW_ATL_PTP_DISABLE_MSK);
	पूर्ण
पूर्ण
