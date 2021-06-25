<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe_x540.h"
#समावेश "ixgbe_type.h"
#समावेश "ixgbe_common.h"
#समावेश "ixgbe_phy.h"

अटल s32 ixgbe_setup_kr_speed_x550em(काष्ठा ixgbe_hw *, ixgbe_link_speed);
अटल s32 ixgbe_setup_fc_x550em(काष्ठा ixgbe_hw *);
अटल व्योम ixgbe_fc_स्वतःneg_fiber_x550em_a(काष्ठा ixgbe_hw *);
अटल व्योम ixgbe_fc_स्वतःneg_backplane_x550em_a(काष्ठा ixgbe_hw *);
अटल s32 ixgbe_setup_fc_backplane_x550em_a(काष्ठा ixgbe_hw *);

अटल s32 ixgbe_get_invariants_X550_x(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	काष्ठा ixgbe_phy_info *phy = &hw->phy;
	काष्ठा ixgbe_link_info *link = &hw->link;

	/* Start with X540 invariants, since so simular */
	ixgbe_get_invariants_X540(hw);

	अगर (mac->ops.get_media_type(hw) != ixgbe_media_type_copper)
		phy->ops.set_phy_घातer = शून्य;

	link->addr = IXGBE_CS4227;

	वापस 0;
पूर्ण

अटल s32 ixgbe_get_invariants_X550_x_fw(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_phy_info *phy = &hw->phy;

	/* Start with X540 invariants, since so similar */
	ixgbe_get_invariants_X540(hw);

	phy->ops.set_phy_घातer = शून्य;

	वापस 0;
पूर्ण

अटल s32 ixgbe_get_invariants_X550_a(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	काष्ठा ixgbe_phy_info *phy = &hw->phy;

	/* Start with X540 invariants, since so simular */
	ixgbe_get_invariants_X540(hw);

	अगर (mac->ops.get_media_type(hw) != ixgbe_media_type_copper)
		phy->ops.set_phy_घातer = शून्य;

	वापस 0;
पूर्ण

अटल s32 ixgbe_get_invariants_X550_a_fw(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_phy_info *phy = &hw->phy;

	/* Start with X540 invariants, since so similar */
	ixgbe_get_invariants_X540(hw);

	phy->ops.set_phy_घातer = शून्य;

	वापस 0;
पूर्ण

/** ixgbe_setup_mux_ctl - Setup ESDP रेजिस्टर क्रम I2C mux control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_setup_mux_ctl(काष्ठा ixgbe_hw *hw)
अणु
	u32 esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);

	अगर (hw->bus.lan_id) अणु
		esdp &= ~(IXGBE_ESDP_SDP1_NATIVE | IXGBE_ESDP_SDP1);
		esdp |= IXGBE_ESDP_SDP1_सूची;
	पूर्ण
	esdp &= ~(IXGBE_ESDP_SDP0_NATIVE | IXGBE_ESDP_SDP0_सूची);
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_पढ़ो_cs4227 - Read CS4227 रेजिस्टर
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg: रेजिस्टर number to ग_लिखो
 * @value: poपूर्णांकer to receive value पढ़ो
 *
 * Returns status code
 */
अटल s32 ixgbe_पढ़ो_cs4227(काष्ठा ixgbe_hw *hw, u16 reg, u16 *value)
अणु
	वापस hw->link.ops.पढ़ो_link_unlocked(hw, hw->link.addr, reg, value);
पूर्ण

/**
 * ixgbe_ग_लिखो_cs4227 - Write CS4227 रेजिस्टर
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg: रेजिस्टर number to ग_लिखो
 * @value: value to ग_लिखो to रेजिस्टर
 *
 * Returns status code
 */
अटल s32 ixgbe_ग_लिखो_cs4227(काष्ठा ixgbe_hw *hw, u16 reg, u16 value)
अणु
	वापस hw->link.ops.ग_लिखो_link_unlocked(hw, hw->link.addr, reg, value);
पूर्ण

/**
 * ixgbe_पढ़ो_pe - Read रेजिस्टर from port expander
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg: रेजिस्टर number to पढ़ो
 * @value: poपूर्णांकer to receive पढ़ो value
 *
 * Returns status code
 */
अटल s32 ixgbe_पढ़ो_pe(काष्ठा ixgbe_hw *hw, u8 reg, u8 *value)
अणु
	s32 status;

	status = ixgbe_पढ़ो_i2c_byte_generic_unlocked(hw, reg, IXGBE_PE, value);
	अगर (status)
		hw_err(hw, "port expander access failed with %d\n", status);
	वापस status;
पूर्ण

/**
 * ixgbe_ग_लिखो_pe - Write रेजिस्टर to port expander
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg: रेजिस्टर number to ग_लिखो
 * @value: value to ग_लिखो
 *
 * Returns status code
 */
अटल s32 ixgbe_ग_लिखो_pe(काष्ठा ixgbe_hw *hw, u8 reg, u8 value)
अणु
	s32 status;

	status = ixgbe_ग_लिखो_i2c_byte_generic_unlocked(hw, reg, IXGBE_PE,
						       value);
	अगर (status)
		hw_err(hw, "port expander access failed with %d\n", status);
	वापस status;
पूर्ण

/**
 * ixgbe_reset_cs4227 - Reset CS4227 using port expander
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * This function assumes that the caller has acquired the proper semaphore.
 * Returns error code
 */
अटल s32 ixgbe_reset_cs4227(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u32 retry;
	u16 value;
	u8 reg;

	/* Trigger hard reset. */
	status = ixgbe_पढ़ो_pe(hw, IXGBE_PE_OUTPUT, &reg);
	अगर (status)
		वापस status;
	reg |= IXGBE_PE_BIT1;
	status = ixgbe_ग_लिखो_pe(hw, IXGBE_PE_OUTPUT, reg);
	अगर (status)
		वापस status;

	status = ixgbe_पढ़ो_pe(hw, IXGBE_PE_CONFIG, &reg);
	अगर (status)
		वापस status;
	reg &= ~IXGBE_PE_BIT1;
	status = ixgbe_ग_लिखो_pe(hw, IXGBE_PE_CONFIG, reg);
	अगर (status)
		वापस status;

	status = ixgbe_पढ़ो_pe(hw, IXGBE_PE_OUTPUT, &reg);
	अगर (status)
		वापस status;
	reg &= ~IXGBE_PE_BIT1;
	status = ixgbe_ग_लिखो_pe(hw, IXGBE_PE_OUTPUT, reg);
	अगर (status)
		वापस status;

	usleep_range(IXGBE_CS4227_RESET_HOLD, IXGBE_CS4227_RESET_HOLD + 100);

	status = ixgbe_पढ़ो_pe(hw, IXGBE_PE_OUTPUT, &reg);
	अगर (status)
		वापस status;
	reg |= IXGBE_PE_BIT1;
	status = ixgbe_ग_लिखो_pe(hw, IXGBE_PE_OUTPUT, reg);
	अगर (status)
		वापस status;

	/* Wait क्रम the reset to complete. */
	msleep(IXGBE_CS4227_RESET_DELAY);
	क्रम (retry = 0; retry < IXGBE_CS4227_RETRIES; retry++) अणु
		status = ixgbe_पढ़ो_cs4227(hw, IXGBE_CS4227_EFUSE_STATUS,
					   &value);
		अगर (!status && value == IXGBE_CS4227_EEPROM_LOAD_OK)
			अवरोध;
		msleep(IXGBE_CS4227_CHECK_DELAY);
	पूर्ण
	अगर (retry == IXGBE_CS4227_RETRIES) अणु
		hw_err(hw, "CS4227 reset did not complete\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	status = ixgbe_पढ़ो_cs4227(hw, IXGBE_CS4227_EEPROM_STATUS, &value);
	अगर (status || !(value & IXGBE_CS4227_EEPROM_LOAD_OK)) अणु
		hw_err(hw, "CS4227 EEPROM did not load successfully\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_check_cs4227 - Check CS4227 and reset as needed
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल व्योम ixgbe_check_cs4227(काष्ठा ixgbe_hw *hw)
अणु
	u32 swfw_mask = hw->phy.phy_semaphore_mask;
	s32 status;
	u16 value;
	u8 retry;

	क्रम (retry = 0; retry < IXGBE_CS4227_RETRIES; retry++) अणु
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		अगर (status) अणु
			hw_err(hw, "semaphore failed with %d\n", status);
			msleep(IXGBE_CS4227_CHECK_DELAY);
			जारी;
		पूर्ण

		/* Get status of reset flow. */
		status = ixgbe_पढ़ो_cs4227(hw, IXGBE_CS4227_SCRATCH, &value);
		अगर (!status && value == IXGBE_CS4227_RESET_COMPLETE)
			जाओ out;

		अगर (status || value != IXGBE_CS4227_RESET_PENDING)
			अवरोध;

		/* Reset is pending. Wait and check again. */
		hw->mac.ops.release_swfw_sync(hw, swfw_mask);
		msleep(IXGBE_CS4227_CHECK_DELAY);
	पूर्ण
	/* If still pending, assume other instance failed. */
	अगर (retry == IXGBE_CS4227_RETRIES) अणु
		status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
		अगर (status) अणु
			hw_err(hw, "semaphore failed with %d\n", status);
			वापस;
		पूर्ण
	पूर्ण

	/* Reset the CS4227. */
	status = ixgbe_reset_cs4227(hw);
	अगर (status) अणु
		hw_err(hw, "CS4227 reset failed: %d", status);
		जाओ out;
	पूर्ण

	/* Reset takes so दीर्घ, temporarily release semaphore in हाल the
	 * other driver instance is रुकोing क्रम the reset indication.
	 */
	ixgbe_ग_लिखो_cs4227(hw, IXGBE_CS4227_SCRATCH,
			   IXGBE_CS4227_RESET_PENDING);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	usleep_range(10000, 12000);
	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	अगर (status) अणु
		hw_err(hw, "semaphore failed with %d", status);
		वापस;
	पूर्ण

	/* Record completion क्रम next समय. */
	status = ixgbe_ग_लिखो_cs4227(hw, IXGBE_CS4227_SCRATCH,
				    IXGBE_CS4227_RESET_COMPLETE);

out:
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	msleep(hw->eeprom.semaphore_delay);
पूर्ण

/** ixgbe_identअगरy_phy_x550em - Get PHY type based on device id
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns error code
 */
अटल s32 ixgbe_identअगरy_phy_x550em(काष्ठा ixgbe_hw *hw)
अणु
	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_X550EM_A_SFP:
		अगर (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
		अन्यथा
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;
		वापस ixgbe_identअगरy_module_generic(hw);
	हाल IXGBE_DEV_ID_X550EM_X_SFP:
		/* set up क्रम CS4227 usage */
		hw->phy.phy_semaphore_mask = IXGBE_GSSR_SHARED_I2C_SM;
		ixgbe_setup_mux_ctl(hw);
		ixgbe_check_cs4227(hw);
		fallthrough;
	हाल IXGBE_DEV_ID_X550EM_A_SFP_N:
		वापस ixgbe_identअगरy_module_generic(hw);
	हाल IXGBE_DEV_ID_X550EM_X_KX4:
		hw->phy.type = ixgbe_phy_x550em_kx4;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_X_XFI:
		hw->phy.type = ixgbe_phy_x550em_xfi;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_X_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR_L:
		hw->phy.type = ixgbe_phy_x550em_kr;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_A_10G_T:
		अगर (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
		अन्यथा
			hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;
		fallthrough;
	हाल IXGBE_DEV_ID_X550EM_X_10G_T:
		वापस ixgbe_identअगरy_phy_generic(hw);
	हाल IXGBE_DEV_ID_X550EM_X_1G_T:
		hw->phy.type = ixgbe_phy_ext_1g_t;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		hw->phy.type = ixgbe_phy_fw;
		hw->phy.ops.पढ़ो_reg = शून्य;
		hw->phy.ops.ग_लिखो_reg = शून्य;
		अगर (hw->bus.lan_id)
			hw->phy.phy_semaphore_mask |= IXGBE_GSSR_PHY1_SM;
		अन्यथा
			hw->phy.phy_semaphore_mask |= IXGBE_GSSR_PHY0_SM;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल s32 ixgbe_पढ़ो_phy_reg_x550em(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				     u32 device_type, u16 *phy_data)
अणु
	वापस IXGBE_NOT_IMPLEMENTED;
पूर्ण

अटल s32 ixgbe_ग_लिखो_phy_reg_x550em(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				      u32 device_type, u16 phy_data)
अणु
	वापस IXGBE_NOT_IMPLEMENTED;
पूर्ण

/**
 * ixgbe_पढ़ो_i2c_combined_generic - Perक्रमm I2C पढ़ो combined operation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @addr: I2C bus address to पढ़ो from
 * @reg: I2C device रेजिस्टर to पढ़ो from
 * @val: poपूर्णांकer to location to receive पढ़ो value
 *
 * Returns an error code on error.
 **/
अटल s32 ixgbe_पढ़ो_i2c_combined_generic(काष्ठा ixgbe_hw *hw, u8 addr,
					   u16 reg, u16 *val)
अणु
	वापस ixgbe_पढ़ो_i2c_combined_generic_पूर्णांक(hw, addr, reg, val, true);
पूर्ण

/**
 * ixgbe_पढ़ो_i2c_combined_generic_unlocked - Do I2C पढ़ो combined operation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @addr: I2C bus address to पढ़ो from
 * @reg: I2C device रेजिस्टर to पढ़ो from
 * @val: poपूर्णांकer to location to receive पढ़ो value
 *
 * Returns an error code on error.
 **/
अटल s32
ixgbe_पढ़ो_i2c_combined_generic_unlocked(काष्ठा ixgbe_hw *hw, u8 addr,
					 u16 reg, u16 *val)
अणु
	वापस ixgbe_पढ़ो_i2c_combined_generic_पूर्णांक(hw, addr, reg, val, false);
पूर्ण

/**
 * ixgbe_ग_लिखो_i2c_combined_generic - Perक्रमm I2C ग_लिखो combined operation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @addr: I2C bus address to ग_लिखो to
 * @reg: I2C device रेजिस्टर to ग_लिखो to
 * @val: value to ग_लिखो
 *
 * Returns an error code on error.
 **/
अटल s32 ixgbe_ग_लिखो_i2c_combined_generic(काष्ठा ixgbe_hw *hw,
					    u8 addr, u16 reg, u16 val)
अणु
	वापस ixgbe_ग_लिखो_i2c_combined_generic_पूर्णांक(hw, addr, reg, val, true);
पूर्ण

/**
 * ixgbe_ग_लिखो_i2c_combined_generic_unlocked - Do I2C ग_लिखो combined operation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @addr: I2C bus address to ग_लिखो to
 * @reg: I2C device रेजिस्टर to ग_लिखो to
 * @val: value to ग_लिखो
 *
 * Returns an error code on error.
 **/
अटल s32
ixgbe_ग_लिखो_i2c_combined_generic_unlocked(काष्ठा ixgbe_hw *hw,
					  u8 addr, u16 reg, u16 val)
अणु
	वापस ixgbe_ग_लिखो_i2c_combined_generic_पूर्णांक(hw, addr, reg, val, false);
पूर्ण

/**
 * ixgbe_fw_phy_activity - Perक्रमm an activity on a PHY
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @activity: activity to perक्रमm
 * @data: Poपूर्णांकer to 4 32-bit words of data
 */
s32 ixgbe_fw_phy_activity(काष्ठा ixgbe_hw *hw, u16 activity,
			  u32 (*data)[FW_PHY_ACT_DATA_COUNT])
अणु
	जोड़ अणु
		काष्ठा ixgbe_hic_phy_activity_req cmd;
		काष्ठा ixgbe_hic_phy_activity_resp rsp;
	पूर्ण hic;
	u16 retries = FW_PHY_ACT_RETRIES;
	s32 rc;
	u32 i;

	करो अणु
		स_रखो(&hic, 0, माप(hic));
		hic.cmd.hdr.cmd = FW_PHY_ACT_REQ_CMD;
		hic.cmd.hdr.buf_len = FW_PHY_ACT_REQ_LEN;
		hic.cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
		hic.cmd.port_number = hw->bus.lan_id;
		hic.cmd.activity_id = cpu_to_le16(activity);
		क्रम (i = 0; i < ARRAY_SIZE(hic.cmd.data); ++i)
			hic.cmd.data[i] = cpu_to_be32((*data)[i]);

		rc = ixgbe_host_पूर्णांकerface_command(hw, &hic.cmd, माप(hic.cmd),
						  IXGBE_HI_COMMAND_TIMEOUT,
						  true);
		अगर (rc)
			वापस rc;
		अगर (hic.rsp.hdr.cmd_or_resp.ret_status ==
		    FW_CEM_RESP_STATUS_SUCCESS) अणु
			क्रम (i = 0; i < FW_PHY_ACT_DATA_COUNT; ++i)
				(*data)[i] = be32_to_cpu(hic.rsp.data[i]);
			वापस 0;
		पूर्ण
		usleep_range(20, 30);
		--retries;
	पूर्ण जबतक (retries > 0);

	वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;
पूर्ण

अटल स्थिर काष्ठा अणु
	u16 fw_speed;
	ixgbe_link_speed phy_speed;
पूर्ण ixgbe_fw_map[] = अणु
	अणु FW_PHY_ACT_LINK_SPEED_10, IXGBE_LINK_SPEED_10_FULL पूर्ण,
	अणु FW_PHY_ACT_LINK_SPEED_100, IXGBE_LINK_SPEED_100_FULL पूर्ण,
	अणु FW_PHY_ACT_LINK_SPEED_1G, IXGBE_LINK_SPEED_1GB_FULL पूर्ण,
	अणु FW_PHY_ACT_LINK_SPEED_2_5G, IXGBE_LINK_SPEED_2_5GB_FULL पूर्ण,
	अणु FW_PHY_ACT_LINK_SPEED_5G, IXGBE_LINK_SPEED_5GB_FULL पूर्ण,
	अणु FW_PHY_ACT_LINK_SPEED_10G, IXGBE_LINK_SPEED_10GB_FULL पूर्ण,
पूर्ण;

/**
 * ixgbe_get_phy_id_fw - Get the phy ID via firmware command
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Returns error code
 */
अटल s32 ixgbe_get_phy_id_fw(काष्ठा ixgbe_hw *hw)
अणु
	u32 info[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	u16 phy_speeds;
	u16 phy_id_lo;
	s32 rc;
	u16 i;

	अगर (hw->phy.id)
		वापस 0;

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_GET_PHY_INFO, &info);
	अगर (rc)
		वापस rc;

	hw->phy.speeds_supported = 0;
	phy_speeds = info[0] & FW_PHY_INFO_SPEED_MASK;
	क्रम (i = 0; i < ARRAY_SIZE(ixgbe_fw_map); ++i) अणु
		अगर (phy_speeds & ixgbe_fw_map[i].fw_speed)
			hw->phy.speeds_supported |= ixgbe_fw_map[i].phy_speed;
	पूर्ण

	hw->phy.id = info[0] & FW_PHY_INFO_ID_HI_MASK;
	phy_id_lo = info[1] & FW_PHY_INFO_ID_LO_MASK;
	hw->phy.id |= phy_id_lo & IXGBE_PHY_REVISION_MASK;
	hw->phy.revision = phy_id_lo & ~IXGBE_PHY_REVISION_MASK;
	अगर (!hw->phy.id || hw->phy.id == IXGBE_PHY_REVISION_MASK)
		वापस IXGBE_ERR_PHY_ADDR_INVALID;

	hw->phy.स्वतःneg_advertised = hw->phy.speeds_supported;
	hw->phy.eee_speeds_supported = IXGBE_LINK_SPEED_100_FULL |
				       IXGBE_LINK_SPEED_1GB_FULL;
	hw->phy.eee_speeds_advertised = hw->phy.eee_speeds_supported;
	वापस 0;
पूर्ण

/**
 * ixgbe_identअगरy_phy_fw - Get PHY type based on firmware command
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Returns error code
 */
अटल s32 ixgbe_identअगरy_phy_fw(काष्ठा ixgbe_hw *hw)
अणु
	अगर (hw->bus.lan_id)
		hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY1_SM;
	अन्यथा
		hw->phy.phy_semaphore_mask = IXGBE_GSSR_PHY0_SM;

	hw->phy.type = ixgbe_phy_fw;
	hw->phy.ops.पढ़ो_reg = शून्य;
	hw->phy.ops.ग_लिखो_reg = शून्य;
	वापस ixgbe_get_phy_id_fw(hw);
पूर्ण

/**
 * ixgbe_shutकरोwn_fw_phy - Shutकरोwn a firmware-controlled PHY
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Returns error code
 */
अटल s32 ixgbe_shutकरोwn_fw_phy(काष्ठा ixgbe_hw *hw)
अणु
	u32 setup[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;

	setup[0] = FW_PHY_ACT_FORCE_LINK_DOWN_OFF;
	वापस ixgbe_fw_phy_activity(hw, FW_PHY_ACT_FORCE_LINK_DOWN, &setup);
पूर्ण

/**
 * ixgbe_setup_fw_link - Setup firmware-controlled PHYs
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_setup_fw_link(काष्ठा ixgbe_hw *hw)
अणु
	u32 setup[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	s32 rc;
	u16 i;

	अगर (hw->phy.reset_disable || ixgbe_check_reset_blocked(hw))
		वापस 0;

	अगर (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_छोड़ो) अणु
		hw_err(hw, "rx_pause not valid in strict IEEE mode\n");
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
	पूर्ण

	चयन (hw->fc.requested_mode) अणु
	हाल ixgbe_fc_full:
		setup[0] |= FW_PHY_ACT_SETUP_LINK_PAUSE_RXTX <<
			    FW_PHY_ACT_SETUP_LINK_PAUSE_SHIFT;
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		setup[0] |= FW_PHY_ACT_SETUP_LINK_PAUSE_RX <<
			    FW_PHY_ACT_SETUP_LINK_PAUSE_SHIFT;
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		setup[0] |= FW_PHY_ACT_SETUP_LINK_PAUSE_TX <<
			    FW_PHY_ACT_SETUP_LINK_PAUSE_SHIFT;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(ixgbe_fw_map); ++i) अणु
		अगर (hw->phy.स्वतःneg_advertised & ixgbe_fw_map[i].phy_speed)
			setup[0] |= ixgbe_fw_map[i].fw_speed;
	पूर्ण
	setup[0] |= FW_PHY_ACT_SETUP_LINK_HP | FW_PHY_ACT_SETUP_LINK_AN;

	अगर (hw->phy.eee_speeds_advertised)
		setup[0] |= FW_PHY_ACT_SETUP_LINK_EEE;

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_SETUP_LINK, &setup);
	अगर (rc)
		वापस rc;
	अगर (setup[0] == FW_PHY_ACT_SETUP_LINK_RSP_DOWN)
		वापस IXGBE_ERR_OVERTEMP;
	वापस 0;
पूर्ण

/**
 * ixgbe_fc_स्वतःneg_fw - Set up flow control क्रम FW-controlled PHYs
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Called at init समय to set up flow control.
 */
अटल s32 ixgbe_fc_स्वतःneg_fw(काष्ठा ixgbe_hw *hw)
अणु
	अगर (hw->fc.requested_mode == ixgbe_fc_शेष)
		hw->fc.requested_mode = ixgbe_fc_full;

	वापस ixgbe_setup_fw_link(hw);
पूर्ण

/** ixgbe_init_eeprom_params_X550 - Initialize EEPROM params
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initializes the EEPROM parameters ixgbe_eeprom_info within the
 *  ixgbe_hw काष्ठा in order to set up EEPROM access.
 **/
अटल s32 ixgbe_init_eeprom_params_X550(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_eeprom_info *eeprom = &hw->eeprom;
	u32 eec;
	u16 eeprom_size;

	अगर (eeprom->type == ixgbe_eeprom_uninitialized) अणु
		eeprom->semaphore_delay = 10;
		eeprom->type = ixgbe_flash;

		eec = IXGBE_READ_REG(hw, IXGBE_EEC(hw));
		eeprom_size = (u16)((eec & IXGBE_EEC_SIZE) >>
				    IXGBE_EEC_SIZE_SHIFT);
		eeprom->word_size = BIT(eeprom_size +
					IXGBE_EEPROM_WORD_SIZE_SHIFT);

		hw_dbg(hw, "Eeprom params: type = %d, size = %d\n",
		       eeprom->type, eeprom->word_size);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_iosf_रुको - Wait क्रम IOSF command completion
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @ctrl: poपूर्णांकer to location to receive final IOSF control value
 *
 * Return: failing status on समयout
 *
 * Note: ctrl can be शून्य अगर the IOSF control रेजिस्टर value is not needed
 */
अटल s32 ixgbe_iosf_रुको(काष्ठा ixgbe_hw *hw, u32 *ctrl)
अणु
	u32 i, command;

	/* Check every 10 usec to see अगर the address cycle completed.
	 * The SB IOSF BUSY bit will clear when the operation is
	 * complete.
	 */
	क्रम (i = 0; i < IXGBE_MDIO_COMMAND_TIMEOUT; i++) अणु
		command = IXGBE_READ_REG(hw, IXGBE_SB_IOSF_INसूचीECT_CTRL);
		अगर (!(command & IXGBE_SB_IOSF_CTRL_BUSY))
			अवरोध;
		udelay(10);
	पूर्ण
	अगर (ctrl)
		*ctrl = command;
	अगर (i == IXGBE_MDIO_COMMAND_TIMEOUT) अणु
		hw_dbg(hw, "IOSF wait timed out\n");
		वापस IXGBE_ERR_PHY;
	पूर्ण

	वापस 0;
पूर्ण

/** ixgbe_पढ़ो_iosf_sb_reg_x550 - Writes a value to specअगरied रेजिस्टर of the
 *  IOSF device
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 3 bit device type
 *  @phy_data: Poपूर्णांकer to पढ़ो data from the रेजिस्टर
 **/
अटल s32 ixgbe_पढ़ो_iosf_sb_reg_x550(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				       u32 device_type, u32 *data)
अणु
	u32 gssr = IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_PHY0_SM;
	u32 command, error;
	s32 ret;

	ret = hw->mac.ops.acquire_swfw_sync(hw, gssr);
	अगर (ret)
		वापस ret;

	ret = ixgbe_iosf_रुको(hw, शून्य);
	अगर (ret)
		जाओ out;

	command = ((reg_addr << IXGBE_SB_IOSF_CTRL_ADDR_SHIFT) |
		   (device_type << IXGBE_SB_IOSF_CTRL_TARGET_SELECT_SHIFT));

	/* Write IOSF control रेजिस्टर */
	IXGBE_WRITE_REG(hw, IXGBE_SB_IOSF_INसूचीECT_CTRL, command);

	ret = ixgbe_iosf_रुको(hw, &command);

	अगर ((command & IXGBE_SB_IOSF_CTRL_RESP_STAT_MASK) != 0) अणु
		error = (command & IXGBE_SB_IOSF_CTRL_CMPL_ERR_MASK) >>
			 IXGBE_SB_IOSF_CTRL_CMPL_ERR_SHIFT;
		hw_dbg(hw, "Failed to read, error %x\n", error);
		वापस IXGBE_ERR_PHY;
	पूर्ण

	अगर (!ret)
		*data = IXGBE_READ_REG(hw, IXGBE_SB_IOSF_INसूचीECT_DATA);

out:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	वापस ret;
पूर्ण

/**
 * ixgbe_get_phy_token - Get the token क्रम shared PHY access
 * @hw: Poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_get_phy_token(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_hic_phy_token_req token_cmd;
	s32 status;

	token_cmd.hdr.cmd = FW_PHY_TOKEN_REQ_CMD;
	token_cmd.hdr.buf_len = FW_PHY_TOKEN_REQ_LEN;
	token_cmd.hdr.cmd_or_resp.cmd_resv = 0;
	token_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
	token_cmd.port_number = hw->bus.lan_id;
	token_cmd.command_type = FW_PHY_TOKEN_REQ;
	token_cmd.pad = 0;
	status = ixgbe_host_पूर्णांकerface_command(hw, &token_cmd, माप(token_cmd),
					      IXGBE_HI_COMMAND_TIMEOUT,
					      true);
	अगर (status)
		वापस status;
	अगर (token_cmd.hdr.cmd_or_resp.ret_status == FW_PHY_TOKEN_OK)
		वापस 0;
	अगर (token_cmd.hdr.cmd_or_resp.ret_status != FW_PHY_TOKEN_RETRY)
		वापस IXGBE_ERR_FW_RESP_INVALID;

	वापस IXGBE_ERR_TOKEN_RETRY;
पूर्ण

/**
 * ixgbe_put_phy_token - Put the token क्रम shared PHY access
 * @hw: Poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_put_phy_token(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_hic_phy_token_req token_cmd;
	s32 status;

	token_cmd.hdr.cmd = FW_PHY_TOKEN_REQ_CMD;
	token_cmd.hdr.buf_len = FW_PHY_TOKEN_REQ_LEN;
	token_cmd.hdr.cmd_or_resp.cmd_resv = 0;
	token_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
	token_cmd.port_number = hw->bus.lan_id;
	token_cmd.command_type = FW_PHY_TOKEN_REL;
	token_cmd.pad = 0;
	status = ixgbe_host_पूर्णांकerface_command(hw, &token_cmd, माप(token_cmd),
					      IXGBE_HI_COMMAND_TIMEOUT,
					      true);
	अगर (status)
		वापस status;
	अगर (token_cmd.hdr.cmd_or_resp.ret_status == FW_PHY_TOKEN_OK)
		वापस 0;
	वापस IXGBE_ERR_FW_RESP_INVALID;
पूर्ण

/**
 *  ixgbe_ग_लिखो_iosf_sb_reg_x550a - Write to IOSF PHY रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 3 bit device type
 *  @data: Data to ग_लिखो to the रेजिस्टर
 **/
अटल s32 ixgbe_ग_लिखो_iosf_sb_reg_x550a(काष्ठा ixgbe_hw *hw, u32 reg_addr,
					 __always_unused u32 device_type,
					 u32 data)
अणु
	काष्ठा ixgbe_hic_पूर्णांकernal_phy_req ग_लिखो_cmd;

	स_रखो(&ग_लिखो_cmd, 0, माप(ग_लिखो_cmd));
	ग_लिखो_cmd.hdr.cmd = FW_INT_PHY_REQ_CMD;
	ग_लिखो_cmd.hdr.buf_len = FW_INT_PHY_REQ_LEN;
	ग_लिखो_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
	ग_लिखो_cmd.port_number = hw->bus.lan_id;
	ग_लिखो_cmd.command_type = FW_INT_PHY_REQ_WRITE;
	ग_लिखो_cmd.address = cpu_to_be16(reg_addr);
	ग_लिखो_cmd.ग_लिखो_data = cpu_to_be32(data);

	वापस ixgbe_host_पूर्णांकerface_command(hw, &ग_लिखो_cmd, माप(ग_लिखो_cmd),
					    IXGBE_HI_COMMAND_TIMEOUT, false);
पूर्ण

/**
 *  ixgbe_पढ़ो_iosf_sb_reg_x550a - Read from IOSF PHY रेजिस्टर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 3 bit device type
 *  @data: Poपूर्णांकer to पढ़ो data from the रेजिस्टर
 **/
अटल s32 ixgbe_पढ़ो_iosf_sb_reg_x550a(काष्ठा ixgbe_hw *hw, u32 reg_addr,
					__always_unused u32 device_type,
					u32 *data)
अणु
	जोड़ अणु
		काष्ठा ixgbe_hic_पूर्णांकernal_phy_req cmd;
		काष्ठा ixgbe_hic_पूर्णांकernal_phy_resp rsp;
	पूर्ण hic;
	s32 status;

	स_रखो(&hic, 0, माप(hic));
	hic.cmd.hdr.cmd = FW_INT_PHY_REQ_CMD;
	hic.cmd.hdr.buf_len = FW_INT_PHY_REQ_LEN;
	hic.cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
	hic.cmd.port_number = hw->bus.lan_id;
	hic.cmd.command_type = FW_INT_PHY_REQ_READ;
	hic.cmd.address = cpu_to_be16(reg_addr);

	status = ixgbe_host_पूर्णांकerface_command(hw, &hic.cmd, माप(hic.cmd),
					      IXGBE_HI_COMMAND_TIMEOUT, true);

	/* Extract the रेजिस्टर value from the response. */
	*data = be32_to_cpu(hic.rsp.पढ़ो_data);

	वापस status;
पूर्ण

/** ixgbe_पढ़ो_ee_hostअगर_buffer_X550- Read EEPROM word(s) using hostअगर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @words: number of words
 *  @data: word(s) पढ़ो from the EEPROM
 *
 *  Reads a 16 bit word(s) from the EEPROM using the hostअगर.
 **/
अटल s32 ixgbe_पढ़ो_ee_hostअगर_buffer_X550(काष्ठा ixgbe_hw *hw,
					    u16 offset, u16 words, u16 *data)
अणु
	स्थिर u32 mask = IXGBE_GSSR_SW_MNG_SM | IXGBE_GSSR_EEP_SM;
	काष्ठा ixgbe_hic_पढ़ो_shaकरोw_ram buffer;
	u32 current_word = 0;
	u16 words_to_पढ़ो;
	s32 status;
	u32 i;

	/* Take semaphore क्रम the entire operation. */
	status = hw->mac.ops.acquire_swfw_sync(hw, mask);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read buffer - semaphore failed\n");
		वापस status;
	पूर्ण

	जबतक (words) अणु
		अगर (words > FW_MAX_READ_BUFFER_SIZE / 2)
			words_to_पढ़ो = FW_MAX_READ_BUFFER_SIZE / 2;
		अन्यथा
			words_to_पढ़ो = words;

		buffer.hdr.req.cmd = FW_READ_SHADOW_RAM_CMD;
		buffer.hdr.req.buf_lenh = 0;
		buffer.hdr.req.buf_lenl = FW_READ_SHADOW_RAM_LEN;
		buffer.hdr.req.checksum = FW_DEFAULT_CHECKSUM;

		/* convert offset from words to bytes */
		buffer.address = (__क्रमce u32)cpu_to_be32((offset +
							   current_word) * 2);
		buffer.length = (__क्रमce u16)cpu_to_be16(words_to_पढ़ो * 2);
		buffer.pad2 = 0;
		buffer.pad3 = 0;

		status = ixgbe_hic_unlocked(hw, (u32 *)&buffer, माप(buffer),
					    IXGBE_HI_COMMAND_TIMEOUT);
		अगर (status) अणु
			hw_dbg(hw, "Host interface command failed\n");
			जाओ out;
		पूर्ण

		क्रम (i = 0; i < words_to_पढ़ो; i++) अणु
			u32 reg = IXGBE_FLEX_MNG + (FW_NVM_DATA_OFFSET << 2) +
				  2 * i;
			u32 value = IXGBE_READ_REG(hw, reg);

			data[current_word] = (u16)(value & 0xffff);
			current_word++;
			i++;
			अगर (i < words_to_पढ़ो) अणु
				value >>= 16;
				data[current_word] = (u16)(value & 0xffff);
				current_word++;
			पूर्ण
		पूर्ण
		words -= words_to_पढ़ो;
	पूर्ण

out:
	hw->mac.ops.release_swfw_sync(hw, mask);
	वापस status;
पूर्ण

/** ixgbe_checksum_ptr_x550 - Checksum one poपूर्णांकer region
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @ptr: poपूर्णांकer offset in eeprom
 *  @size: size of section poपूर्णांकed by ptr, अगर 0 first word will be used as size
 *  @csum: address of checksum to update
 *
 *  Returns error status क्रम any failure
 **/
अटल s32 ixgbe_checksum_ptr_x550(काष्ठा ixgbe_hw *hw, u16 ptr,
				   u16 size, u16 *csum, u16 *buffer,
				   u32 buffer_size)
अणु
	u16 buf[256];
	s32 status;
	u16 length, bufsz, i, start;
	u16 *local_buffer;

	bufsz = ARRAY_SIZE(buf);

	/* Read a chunk at the poपूर्णांकer location */
	अगर (!buffer) अणु
		status = ixgbe_पढ़ो_ee_hostअगर_buffer_X550(hw, ptr, bufsz, buf);
		अगर (status) अणु
			hw_dbg(hw, "Failed to read EEPROM image\n");
			वापस status;
		पूर्ण
		local_buffer = buf;
	पूर्ण अन्यथा अणु
		अगर (buffer_size < ptr)
			वापस  IXGBE_ERR_PARAM;
		local_buffer = &buffer[ptr];
	पूर्ण

	अगर (size) अणु
		start = 0;
		length = size;
	पूर्ण अन्यथा अणु
		start = 1;
		length = local_buffer[0];

		/* Skip poपूर्णांकer section अगर length is invalid. */
		अगर (length == 0xFFFF || length == 0 ||
		    (ptr + length) >= hw->eeprom.word_size)
			वापस 0;
	पूर्ण

	अगर (buffer && ((u32)start + (u32)length > buffer_size))
		वापस IXGBE_ERR_PARAM;

	क्रम (i = start; length; i++, length--) अणु
		अगर (i == bufsz && !buffer) अणु
			ptr += bufsz;
			i = 0;
			अगर (length < bufsz)
				bufsz = length;

			/* Read a chunk at the poपूर्णांकer location */
			status = ixgbe_पढ़ो_ee_hostअगर_buffer_X550(hw, ptr,
								  bufsz, buf);
			अगर (status) अणु
				hw_dbg(hw, "Failed to read EEPROM image\n");
				वापस status;
			पूर्ण
		पूर्ण
		*csum += local_buffer[i];
	पूर्ण
	वापस 0;
पूर्ण

/** ixgbe_calc_checksum_X550 - Calculates and वापसs the checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @buffer: poपूर्णांकer to buffer containing calculated checksum
 *  @buffer_size: size of buffer
 *
 *  Returns a negative error code on error, or the 16-bit checksum
 **/
अटल s32 ixgbe_calc_checksum_X550(काष्ठा ixgbe_hw *hw, u16 *buffer,
				    u32 buffer_size)
अणु
	u16 eeprom_ptrs[IXGBE_EEPROM_LAST_WORD + 1];
	u16 *local_buffer;
	s32 status;
	u16 checksum = 0;
	u16 poपूर्णांकer, i, size;

	hw->eeprom.ops.init_params(hw);

	अगर (!buffer) अणु
		/* Read poपूर्णांकer area */
		status = ixgbe_पढ़ो_ee_hostअगर_buffer_X550(hw, 0,
						IXGBE_EEPROM_LAST_WORD + 1,
						eeprom_ptrs);
		अगर (status) अणु
			hw_dbg(hw, "Failed to read EEPROM image\n");
			वापस status;
		पूर्ण
		local_buffer = eeprom_ptrs;
	पूर्ण अन्यथा अणु
		अगर (buffer_size < IXGBE_EEPROM_LAST_WORD)
			वापस IXGBE_ERR_PARAM;
		local_buffer = buffer;
	पूर्ण

	/* For X550 hardware include 0x0-0x41 in the checksum, skip the
	 * checksum word itself
	 */
	क्रम (i = 0; i <= IXGBE_EEPROM_LAST_WORD; i++)
		अगर (i != IXGBE_EEPROM_CHECKSUM)
			checksum += local_buffer[i];

	/* Include all data from poपूर्णांकers 0x3, 0x6-0xE.  This excludes the
	 * FW, PHY module, and PCIe Expansion/Option ROM poपूर्णांकers.
	 */
	क्रम (i = IXGBE_PCIE_ANALOG_PTR_X550; i < IXGBE_FW_PTR; i++) अणु
		अगर (i == IXGBE_PHY_PTR || i == IXGBE_OPTION_ROM_PTR)
			जारी;

		poपूर्णांकer = local_buffer[i];

		/* Skip poपूर्णांकer section अगर the poपूर्णांकer is invalid. */
		अगर (poपूर्णांकer == 0xFFFF || poपूर्णांकer == 0 ||
		    poपूर्णांकer >= hw->eeprom.word_size)
			जारी;

		चयन (i) अणु
		हाल IXGBE_PCIE_GENERAL_PTR:
			size = IXGBE_IXGBE_PCIE_GENERAL_SIZE;
			अवरोध;
		हाल IXGBE_PCIE_CONFIG0_PTR:
		हाल IXGBE_PCIE_CONFIG1_PTR:
			size = IXGBE_PCIE_CONFIG_SIZE;
			अवरोध;
		शेष:
			size = 0;
			अवरोध;
		पूर्ण

		status = ixgbe_checksum_ptr_x550(hw, poपूर्णांकer, size, &checksum,
						 buffer, buffer_size);
		अगर (status)
			वापस status;
	पूर्ण

	checksum = (u16)IXGBE_EEPROM_SUM - checksum;

	वापस (s32)checksum;
पूर्ण

/** ixgbe_calc_eeprom_checksum_X550 - Calculates and वापसs the checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns a negative error code on error, or the 16-bit checksum
 **/
अटल s32 ixgbe_calc_eeprom_checksum_X550(काष्ठा ixgbe_hw *hw)
अणु
	वापस ixgbe_calc_checksum_X550(hw, शून्य, 0);
पूर्ण

/** ixgbe_पढ़ो_ee_hostअगर_X550 - Read EEPROM word using a host पूर्णांकerface command
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to पढ़ो
 *  @data: word पढ़ो from the EEPROM
 *
 *   Reads a 16 bit word from the EEPROM using the hostअगर.
 **/
अटल s32 ixgbe_पढ़ो_ee_hostअगर_X550(काष्ठा ixgbe_hw *hw, u16 offset, u16 *data)
अणु
	स्थिर u32 mask = IXGBE_GSSR_SW_MNG_SM | IXGBE_GSSR_EEP_SM;
	काष्ठा ixgbe_hic_पढ़ो_shaकरोw_ram buffer;
	s32 status;

	buffer.hdr.req.cmd = FW_READ_SHADOW_RAM_CMD;
	buffer.hdr.req.buf_lenh = 0;
	buffer.hdr.req.buf_lenl = FW_READ_SHADOW_RAM_LEN;
	buffer.hdr.req.checksum = FW_DEFAULT_CHECKSUM;

	/* convert offset from words to bytes */
	buffer.address = (__क्रमce u32)cpu_to_be32(offset * 2);
	/* one word */
	buffer.length = (__क्रमce u16)cpu_to_be16(माप(u16));

	status = hw->mac.ops.acquire_swfw_sync(hw, mask);
	अगर (status)
		वापस status;

	status = ixgbe_hic_unlocked(hw, (u32 *)&buffer, माप(buffer),
				    IXGBE_HI_COMMAND_TIMEOUT);
	अगर (!status) अणु
		*data = (u16)IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG,
						  FW_NVM_DATA_OFFSET);
	पूर्ण

	hw->mac.ops.release_swfw_sync(hw, mask);
	वापस status;
पूर्ण

/** ixgbe_validate_eeprom_checksum_X550 - Validate EEPROM checksum
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @checksum_val: calculated checksum
 *
 *  Perक्रमms checksum calculation and validates the EEPROM checksum.  If the
 *  caller करोes not need checksum_val, the value can be शून्य.
 **/
अटल s32 ixgbe_validate_eeprom_checksum_X550(काष्ठा ixgbe_hw *hw,
					       u16 *checksum_val)
अणु
	s32 status;
	u16 checksum;
	u16 पढ़ो_checksum = 0;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = hw->eeprom.ops.पढ़ो(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	status = hw->eeprom.ops.calc_checksum(hw);
	अगर (status < 0)
		वापस status;

	checksum = (u16)(status & 0xffff);

	status = ixgbe_पढ़ो_ee_hostअगर_X550(hw, IXGBE_EEPROM_CHECKSUM,
					   &पढ़ो_checksum);
	अगर (status)
		वापस status;

	/* Verअगरy पढ़ो checksum from EEPROM is the same as
	 * calculated checksum
	 */
	अगर (पढ़ो_checksum != checksum) अणु
		status = IXGBE_ERR_EEPROM_CHECKSUM;
		hw_dbg(hw, "Invalid EEPROM checksum");
	पूर्ण

	/* If the user cares, वापस the calculated checksum */
	अगर (checksum_val)
		*checksum_val = checksum;

	वापस status;
पूर्ण

/** ixgbe_ग_लिखो_ee_hostअगर_X550 - Write EEPROM word using hostअगर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @data: word ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word to the EEPROM using the hostअगर.
 **/
अटल s32 ixgbe_ग_लिखो_ee_hostअगर_data_X550(काष्ठा ixgbe_hw *hw, u16 offset,
					   u16 data)
अणु
	s32 status;
	काष्ठा ixgbe_hic_ग_लिखो_shaकरोw_ram buffer;

	buffer.hdr.req.cmd = FW_WRITE_SHADOW_RAM_CMD;
	buffer.hdr.req.buf_lenh = 0;
	buffer.hdr.req.buf_lenl = FW_WRITE_SHADOW_RAM_LEN;
	buffer.hdr.req.checksum = FW_DEFAULT_CHECKSUM;

	/* one word */
	buffer.length = cpu_to_be16(माप(u16));
	buffer.data = data;
	buffer.address = cpu_to_be32(offset * 2);

	status = ixgbe_host_पूर्णांकerface_command(hw, &buffer, माप(buffer),
					      IXGBE_HI_COMMAND_TIMEOUT, false);
	वापस status;
पूर्ण

/** ixgbe_ग_लिखो_ee_hostअगर_X550 - Write EEPROM word using hostअगर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @data: word ग_लिखो to the EEPROM
 *
 *  Write a 16 bit word to the EEPROM using the hostअगर.
 **/
अटल s32 ixgbe_ग_लिखो_ee_hostअगर_X550(काष्ठा ixgbe_hw *hw, u16 offset, u16 data)
अणु
	s32 status = 0;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM) == 0) अणु
		status = ixgbe_ग_लिखो_ee_hostअगर_data_X550(hw, offset, data);
		hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	पूर्ण अन्यथा अणु
		hw_dbg(hw, "write ee hostif failed to get semaphore");
		status = IXGBE_ERR_SWFW_SYNC;
	पूर्ण

	वापस status;
पूर्ण

/** ixgbe_update_flash_X550 - Inकाष्ठा HW to copy EEPROM to Flash device
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Issue a shaकरोw RAM dump to FW to copy EEPROM from shaकरोw RAM to the flash.
 **/
अटल s32 ixgbe_update_flash_X550(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = 0;
	जोड़ ixgbe_hic_hdr2 buffer;

	buffer.req.cmd = FW_SHADOW_RAM_DUMP_CMD;
	buffer.req.buf_lenh = 0;
	buffer.req.buf_lenl = FW_SHADOW_RAM_DUMP_LEN;
	buffer.req.checksum = FW_DEFAULT_CHECKSUM;

	status = ixgbe_host_पूर्णांकerface_command(hw, &buffer, माप(buffer),
					      IXGBE_HI_COMMAND_TIMEOUT, false);
	वापस status;
पूर्ण

/**
 * ixgbe_get_bus_info_X550em - Set PCI bus info
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Sets bus link width and speed to unknown because X550em is
 * not a PCI device.
 **/
अटल s32 ixgbe_get_bus_info_X550em(काष्ठा ixgbe_hw *hw)
अणु
	hw->bus.type  = ixgbe_bus_type_पूर्णांकernal;
	hw->bus.width = ixgbe_bus_width_unknown;
	hw->bus.speed = ixgbe_bus_speed_unknown;

	hw->mac.ops.set_lan_id(hw);

	वापस 0;
पूर्ण

/**
 * ixgbe_fw_recovery_mode_X550 - Check FW NVM recovery mode
 * @hw: poपूर्णांकer t hardware काष्ठाure
 *
 * Returns true अगर in FW NVM recovery mode.
 */
अटल bool ixgbe_fw_recovery_mode_X550(काष्ठा ixgbe_hw *hw)
अणु
	u32 fwsm;

	fwsm = IXGBE_READ_REG(hw, IXGBE_FWSM(hw));
	वापस !!(fwsm & IXGBE_FWSM_FW_NVM_RECOVERY_MODE);
पूर्ण

/** ixgbe_disable_rx_x550 - Disable RX unit
 *
 *  Enables the Rx DMA unit क्रम x550
 **/
अटल व्योम ixgbe_disable_rx_x550(काष्ठा ixgbe_hw *hw)
अणु
	u32 rxctrl, pfdtxgswc;
	s32 status;
	काष्ठा ixgbe_hic_disable_rxen fw_cmd;

	rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
	अगर (rxctrl & IXGBE_RXCTRL_RXEN) अणु
		pfdtxgswc = IXGBE_READ_REG(hw, IXGBE_PFDTXGSWC);
		अगर (pfdtxgswc & IXGBE_PFDTXGSWC_VT_LBEN) अणु
			pfdtxgswc &= ~IXGBE_PFDTXGSWC_VT_LBEN;
			IXGBE_WRITE_REG(hw, IXGBE_PFDTXGSWC, pfdtxgswc);
			hw->mac.set_lben = true;
		पूर्ण अन्यथा अणु
			hw->mac.set_lben = false;
		पूर्ण

		fw_cmd.hdr.cmd = FW_DISABLE_RXEN_CMD;
		fw_cmd.hdr.buf_len = FW_DISABLE_RXEN_LEN;
		fw_cmd.hdr.checksum = FW_DEFAULT_CHECKSUM;
		fw_cmd.port_number = hw->bus.lan_id;

		status = ixgbe_host_पूर्णांकerface_command(hw, &fw_cmd,
					माप(काष्ठा ixgbe_hic_disable_rxen),
					IXGBE_HI_COMMAND_TIMEOUT, true);

		/* If we fail - disable RX using रेजिस्टर ग_लिखो */
		अगर (status) अणु
			rxctrl = IXGBE_READ_REG(hw, IXGBE_RXCTRL);
			अगर (rxctrl & IXGBE_RXCTRL_RXEN) अणु
				rxctrl &= ~IXGBE_RXCTRL_RXEN;
				IXGBE_WRITE_REG(hw, IXGBE_RXCTRL, rxctrl);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/** ixgbe_update_eeprom_checksum_X550 - Updates the EEPROM checksum and flash
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  After writing EEPROM to shaकरोw RAM using EEWR रेजिस्टर, software calculates
 *  checksum and updates the EEPROM and inकाष्ठाs the hardware to update
 *  the flash.
 **/
अटल s32 ixgbe_update_eeprom_checksum_X550(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 checksum = 0;

	/* Read the first word from the EEPROM. If this बार out or fails, करो
	 * not जारी or we could be in क्रम a very दीर्घ रुको जबतक every
	 * EEPROM पढ़ो fails
	 */
	status = ixgbe_पढ़ो_ee_hostअगर_X550(hw, 0, &checksum);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM read failed\n");
		वापस status;
	पूर्ण

	status = ixgbe_calc_eeprom_checksum_X550(hw);
	अगर (status < 0)
		वापस status;

	checksum = (u16)(status & 0xffff);

	status = ixgbe_ग_लिखो_ee_hostअगर_X550(hw, IXGBE_EEPROM_CHECKSUM,
					    checksum);
	अगर (status)
		वापस status;

	status = ixgbe_update_flash_X550(hw);

	वापस status;
पूर्ण

/** ixgbe_ग_लिखो_ee_hostअगर_buffer_X550 - Write EEPROM word(s) using hostअगर
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @offset: offset of  word in the EEPROM to ग_लिखो
 *  @words: number of words
 *  @data: word(s) ग_लिखो to the EEPROM
 *
 *
 *  Write a 16 bit word(s) to the EEPROM using the hostअगर.
 **/
अटल s32 ixgbe_ग_लिखो_ee_hostअगर_buffer_X550(काष्ठा ixgbe_hw *hw,
					     u16 offset, u16 words,
					     u16 *data)
अणु
	s32 status = 0;
	u32 i = 0;

	/* Take semaphore क्रम the entire operation. */
	status = hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_EEP_SM);
	अगर (status) अणु
		hw_dbg(hw, "EEPROM write buffer - semaphore failed\n");
		वापस status;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		status = ixgbe_ग_लिखो_ee_hostअगर_data_X550(hw, offset + i,
							 data[i]);
		अगर (status) अणु
			hw_dbg(hw, "Eeprom buffered write failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_EEP_SM);

	वापस status;
पूर्ण

/** ixgbe_ग_लिखो_iosf_sb_reg_x550 - Writes a value to specअगरied रेजिस्टर of the
 *  IOSF device
 *
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 *  @device_type: 3 bit device type
 *  @data: Data to ग_लिखो to the रेजिस्टर
 **/
अटल s32 ixgbe_ग_लिखो_iosf_sb_reg_x550(काष्ठा ixgbe_hw *hw, u32 reg_addr,
					u32 device_type, u32 data)
अणु
	u32 gssr = IXGBE_GSSR_PHY1_SM | IXGBE_GSSR_PHY0_SM;
	u32 command, error;
	s32 ret;

	ret = hw->mac.ops.acquire_swfw_sync(hw, gssr);
	अगर (ret)
		वापस ret;

	ret = ixgbe_iosf_रुको(hw, शून्य);
	अगर (ret)
		जाओ out;

	command = ((reg_addr << IXGBE_SB_IOSF_CTRL_ADDR_SHIFT) |
		   (device_type << IXGBE_SB_IOSF_CTRL_TARGET_SELECT_SHIFT));

	/* Write IOSF control रेजिस्टर */
	IXGBE_WRITE_REG(hw, IXGBE_SB_IOSF_INसूचीECT_CTRL, command);

	/* Write IOSF data रेजिस्टर */
	IXGBE_WRITE_REG(hw, IXGBE_SB_IOSF_INसूचीECT_DATA, data);

	ret = ixgbe_iosf_रुको(hw, &command);

	अगर ((command & IXGBE_SB_IOSF_CTRL_RESP_STAT_MASK) != 0) अणु
		error = (command & IXGBE_SB_IOSF_CTRL_CMPL_ERR_MASK) >>
			 IXGBE_SB_IOSF_CTRL_CMPL_ERR_SHIFT;
		hw_dbg(hw, "Failed to write, error %x\n", error);
		वापस IXGBE_ERR_PHY;
	पूर्ण

out:
	hw->mac.ops.release_swfw_sync(hw, gssr);
	वापस ret;
पूर्ण

/**
 *  ixgbe_setup_ixfi_x550em_x - MAC specअगरic iXFI configuration
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  iXfI configuration needed क्रम ixgbe_mac_X550EM_x devices.
 **/
अटल s32 ixgbe_setup_ixfi_x550em_x(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u32 reg_val;

	/* Disable training protocol FSM. */
	status = ixgbe_पढ़ो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_RX_TRN_LINKUP_CTRL(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val |= IXGBE_KRM_RX_TRN_LINKUP_CTRL_CONV_WO_PROTOCOL;
	status = ixgbe_ग_लिखो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_RX_TRN_LINKUP_CTRL(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	अगर (status)
		वापस status;

	/* Disable Flex from training TXFFE. */
	status = ixgbe_पढ़ो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_4(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_C0_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CP1_CN1_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CO_ADAPT_EN;
	status = ixgbe_ग_लिखो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_4(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	अगर (status)
		वापस status;

	status = ixgbe_पढ़ो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_5(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_C0_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CP1_CN1_EN;
	reg_val &= ~IXGBE_KRM_DSP_TXFFE_STATE_CO_ADAPT_EN;
	status = ixgbe_ग_लिखो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_DSP_TXFFE_STATE_5(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	अगर (status)
		वापस status;

	/* Enable override क्रम coefficients. */
	status = ixgbe_पढ़ो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_TX_COEFF_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_OVRRD_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CZERO_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CPLUS1_OVRRD_EN;
	reg_val |= IXGBE_KRM_TX_COEFF_CTRL_1_CMINUS1_OVRRD_EN;
	status = ixgbe_ग_लिखो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_TX_COEFF_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	वापस status;
पूर्ण

/**
 *  ixgbe_restart_an_पूर्णांकernal_phy_x550em - restart स्वतःnegotiation क्रम the
 *  पूर्णांकernal PHY
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_restart_an_पूर्णांकernal_phy_x550em(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u32 link_ctrl;

	/* Restart स्वतः-negotiation. */
	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &link_ctrl);

	अगर (status) अणु
		hw_dbg(hw, "Auto-negotiation did not complete\n");
		वापस status;
	पूर्ण

	link_ctrl |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_RESTART;
	status = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, link_ctrl);

	अगर (hw->mac.type == ixgbe_mac_x550em_a) अणु
		u32 flx_mask_st20;

		/* Indicate to FW that AN restart has been निश्चितed */
		status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &flx_mask_st20);

		अगर (status) अणु
			hw_dbg(hw, "Auto-negotiation did not complete\n");
			वापस status;
		पूर्ण

		flx_mask_st20 |= IXGBE_KRM_PMD_FLX_MASK_ST20_FW_AN_RESTART;
		status = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, flx_mask_st20);
	पूर्ण

	वापस status;
पूर्ण

/** ixgbe_setup_ixfi_x550em - Configure the KR PHY क्रम iXFI mode.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @speed: the link speed to क्रमce
 *
 *  Configures the पूर्णांकegrated KR PHY to use iXFI mode. Used to connect an
 *  पूर्णांकernal and बाह्यal PHY at a specअगरic speed, without स्वतःnegotiation.
 **/
अटल s32 ixgbe_setup_ixfi_x550em(काष्ठा ixgbe_hw *hw, ixgbe_link_speed *speed)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	s32 status;
	u32 reg_val;

	/* iXFI is only supported with X552 */
	अगर (mac->type != ixgbe_mac_X550EM_x)
		वापस IXGBE_ERR_LINK_SETUP;

	/* Disable AN and क्रमce speed to 10G Serial. */
	status = ixgbe_पढ़ो_iosf_sb_reg_x550(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val &= ~IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE;
	reg_val &= ~IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_MASK;

	/* Select क्रमced link speed क्रम पूर्णांकernal PHY. */
	चयन (*speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_10G;
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_1G;
		अवरोध;
	शेष:
		/* Other link speeds are not supported by पूर्णांकernal KR PHY. */
		वापस IXGBE_ERR_LINK_SETUP;
	पूर्ण

	status = ixgbe_ग_लिखो_iosf_sb_reg_x550(hw,
				IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	अगर (status)
		वापस status;

	/* Additional configuration needed क्रम x550em_x */
	अगर (hw->mac.type == ixgbe_mac_X550EM_x) अणु
		status = ixgbe_setup_ixfi_x550em_x(hw);
		अगर (status)
			वापस status;
	पूर्ण

	/* Toggle port SW reset by AN reset. */
	status = ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);

	वापस status;
पूर्ण

/**
 *  ixgbe_supported_sfp_modules_X550em - Check अगर SFP module type is supported
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @linear: true अगर SFP module is linear
 */
अटल s32 ixgbe_supported_sfp_modules_X550em(काष्ठा ixgbe_hw *hw, bool *linear)
अणु
	चयन (hw->phy.sfp_type) अणु
	हाल ixgbe_sfp_type_not_present:
		वापस IXGBE_ERR_SFP_NOT_PRESENT;
	हाल ixgbe_sfp_type_da_cu_core0:
	हाल ixgbe_sfp_type_da_cu_core1:
		*linear = true;
		अवरोध;
	हाल ixgbe_sfp_type_srlr_core0:
	हाल ixgbe_sfp_type_srlr_core1:
	हाल ixgbe_sfp_type_da_act_lmt_core0:
	हाल ixgbe_sfp_type_da_act_lmt_core1:
	हाल ixgbe_sfp_type_1g_sx_core0:
	हाल ixgbe_sfp_type_1g_sx_core1:
	हाल ixgbe_sfp_type_1g_lx_core0:
	हाल ixgbe_sfp_type_1g_lx_core1:
		*linear = false;
		अवरोध;
	हाल ixgbe_sfp_type_unknown:
	हाल ixgbe_sfp_type_1g_cu_core0:
	हाल ixgbe_sfp_type_1g_cu_core1:
	शेष:
		वापस IXGBE_ERR_SFP_NOT_SUPPORTED;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ixgbe_setup_mac_link_sfp_x550em - Configure the KR PHY क्रम SFP.
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: the link speed to क्रमce
 * @स्वतःneg_रुको_to_complete: unused
 *
 * Configures the बाह्य PHY and the पूर्णांकegrated KR PHY क्रम SFP support.
 */
अटल s32
ixgbe_setup_mac_link_sfp_x550em(काष्ठा ixgbe_hw *hw,
				ixgbe_link_speed speed,
				__always_unused bool स्वतःneg_रुको_to_complete)
अणु
	s32 status;
	u16 reg_slice, reg_val;
	bool setup_linear = false;

	/* Check अगर SFP module is supported and linear */
	status = ixgbe_supported_sfp_modules_X550em(hw, &setup_linear);

	/* If no SFP module present, then वापस success. Return success since
	 * there is no reason to configure CS4227 and SFP not present error is
	 * not accepted in the setup MAC link flow.
	 */
	अगर (status == IXGBE_ERR_SFP_NOT_PRESENT)
		वापस 0;

	अगर (status)
		वापस status;

	/* Configure पूर्णांकernal PHY क्रम KR/KX. */
	ixgbe_setup_kr_speed_x550em(hw, speed);

	/* Configure CS4227 LINE side to proper mode. */
	reg_slice = IXGBE_CS4227_LINE_SPARE24_LSB + (hw->bus.lan_id << 12);
	अगर (setup_linear)
		reg_val = (IXGBE_CS4227_EDC_MODE_CX1 << 1) | 0x1;
	अन्यथा
		reg_val = (IXGBE_CS4227_EDC_MODE_SR << 1) | 0x1;

	status = hw->link.ops.ग_लिखो_link(hw, hw->link.addr, reg_slice,
					 reg_val);

	वापस status;
पूर्ण

/**
 * ixgbe_setup_sfi_x550a - Configure the पूर्णांकernal PHY क्रम native SFI mode
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: the link speed to क्रमce
 *
 * Configures the पूर्णांकegrated PHY क्रम native SFI mode. Used to connect the
 * पूर्णांकernal PHY directly to an SFP cage, without स्वतःnegotiation.
 **/
अटल s32 ixgbe_setup_sfi_x550a(काष्ठा ixgbe_hw *hw, ixgbe_link_speed *speed)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	s32 status;
	u32 reg_val;

	/* Disable all AN and क्रमce speed to 10G Serial. */
	status = mac->ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;
	reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;

	/* Select क्रमced link speed क्रम पूर्णांकernal PHY. */
	चयन (*speed) अणु
	हाल IXGBE_LINK_SPEED_10GB_FULL:
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_10G;
		अवरोध;
	हाल IXGBE_LINK_SPEED_1GB_FULL:
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_1G;
		अवरोध;
	शेष:
		/* Other link speeds are not supported by पूर्णांकernal PHY. */
		वापस IXGBE_ERR_LINK_SETUP;
	पूर्ण

	status = mac->ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);

	/* Toggle port SW reset by AN reset. */
	status = ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);

	वापस status;
पूर्ण

/**
 * ixgbe_setup_mac_link_sfp_n - Setup पूर्णांकernal PHY क्रम native SFP
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: link speed
 * @स्वतःneg_रुको_to_complete: unused
 *
 * Configure the the पूर्णांकegrated PHY क्रम native SFP support.
 */
अटल s32
ixgbe_setup_mac_link_sfp_n(काष्ठा ixgbe_hw *hw, ixgbe_link_speed speed,
			   __always_unused bool स्वतःneg_रुको_to_complete)
अणु
	bool setup_linear = false;
	u32 reg_phy_पूर्णांक;
	s32 ret_val;

	/* Check अगर SFP module is supported and linear */
	ret_val = ixgbe_supported_sfp_modules_X550em(hw, &setup_linear);

	/* If no SFP module present, then वापस success. Return success since
	 * SFP not present error is not excepted in the setup MAC link flow.
	 */
	अगर (ret_val == IXGBE_ERR_SFP_NOT_PRESENT)
		वापस 0;

	अगर (ret_val)
		वापस ret_val;

	/* Configure पूर्णांकernal PHY क्रम native SFI based on module type */
	ret_val = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_phy_पूर्णांक);
	अगर (ret_val)
		वापस ret_val;

	reg_phy_पूर्णांक &= IXGBE_KRM_PMD_FLX_MASK_ST20_SFI_10G_DA;
	अगर (!setup_linear)
		reg_phy_पूर्णांक |= IXGBE_KRM_PMD_FLX_MASK_ST20_SFI_10G_SR;

	ret_val = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_phy_पूर्णांक);
	अगर (ret_val)
		वापस ret_val;

	/* Setup SFI पूर्णांकernal link. */
	वापस ixgbe_setup_sfi_x550a(hw, &speed);
पूर्ण

/**
 * ixgbe_setup_mac_link_sfp_x550a - Setup पूर्णांकernal PHY क्रम SFP
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: link speed
 * @स्वतःneg_रुको_to_complete: unused
 *
 * Configure the the पूर्णांकegrated PHY क्रम SFP support.
 */
अटल s32
ixgbe_setup_mac_link_sfp_x550a(काष्ठा ixgbe_hw *hw, ixgbe_link_speed speed,
			       __always_unused bool स्वतःneg_रुको_to_complete)
अणु
	u32 reg_slice, slice_offset;
	bool setup_linear = false;
	u16 reg_phy_ext;
	s32 ret_val;

	/* Check अगर SFP module is supported and linear */
	ret_val = ixgbe_supported_sfp_modules_X550em(hw, &setup_linear);

	/* If no SFP module present, then वापस success. Return success since
	 * SFP not present error is not excepted in the setup MAC link flow.
	 */
	अगर (ret_val == IXGBE_ERR_SFP_NOT_PRESENT)
		वापस 0;

	अगर (ret_val)
		वापस ret_val;

	/* Configure पूर्णांकernal PHY क्रम KR/KX. */
	ixgbe_setup_kr_speed_x550em(hw, speed);

	अगर (hw->phy.mdio.prtad == MDIO_PRTAD_NONE)
		वापस IXGBE_ERR_PHY_ADDR_INVALID;

	/* Get बाह्यal PHY SKU id */
	ret_val = hw->phy.ops.पढ़ो_reg(hw, IXGBE_CS4227_EFUSE_PDF_SKU,
				       IXGBE_MDIO_ZERO_DEV_TYPE, &reg_phy_ext);
	अगर (ret_val)
		वापस ret_val;

	/* When configuring quad port CS4223, the MAC instance is part
	 * of the slice offset.
	 */
	अगर (reg_phy_ext == IXGBE_CS4223_SKU_ID)
		slice_offset = (hw->bus.lan_id +
				(hw->bus.instance_id << 1)) << 12;
	अन्यथा
		slice_offset = hw->bus.lan_id << 12;

	/* Configure CS4227/CS4223 LINE side to proper mode. */
	reg_slice = IXGBE_CS4227_LINE_SPARE24_LSB + slice_offset;

	ret_val = hw->phy.ops.पढ़ो_reg(hw, reg_slice,
				       IXGBE_MDIO_ZERO_DEV_TYPE, &reg_phy_ext);
	अगर (ret_val)
		वापस ret_val;

	reg_phy_ext &= ~((IXGBE_CS4227_EDC_MODE_CX1 << 1) |
			 (IXGBE_CS4227_EDC_MODE_SR << 1));

	अगर (setup_linear)
		reg_phy_ext |= (IXGBE_CS4227_EDC_MODE_CX1 << 1) | 1;
	अन्यथा
		reg_phy_ext |= (IXGBE_CS4227_EDC_MODE_SR << 1) | 1;

	ret_val = hw->phy.ops.ग_लिखो_reg(hw, reg_slice,
					IXGBE_MDIO_ZERO_DEV_TYPE, reg_phy_ext);
	अगर (ret_val)
		वापस ret_val;

	/* Flush previous ग_लिखो with a पढ़ो */
	वापस hw->phy.ops.पढ़ो_reg(hw, reg_slice,
				    IXGBE_MDIO_ZERO_DEV_TYPE, &reg_phy_ext);
पूर्ण

/**
 * ixgbe_setup_mac_link_t_X550em - Sets the स्वतः advertised link speed
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: new link speed
 * @स्वतःneg_रुको: true when रुकोing क्रम completion is needed
 *
 * Setup पूर्णांकernal/बाह्यal PHY link speed based on link speed, then set
 * बाह्यal PHY स्वतः advertised link speed.
 *
 * Returns error status क्रम any failure
 **/
अटल s32 ixgbe_setup_mac_link_t_X550em(काष्ठा ixgbe_hw *hw,
					 ixgbe_link_speed speed,
					 bool स्वतःneg_रुको)
अणु
	s32 status;
	ixgbe_link_speed क्रमce_speed;

	/* Setup पूर्णांकernal/बाह्यal PHY link speed to iXFI (10G), unless
	 * only 1G is स्वतः advertised then setup KX link.
	 */
	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
		क्रमce_speed = IXGBE_LINK_SPEED_10GB_FULL;
	अन्यथा
		क्रमce_speed = IXGBE_LINK_SPEED_1GB_FULL;

	/* If X552 and पूर्णांकernal link mode is XFI, then setup XFI पूर्णांकernal link.
	 */
	अगर (hw->mac.type == ixgbe_mac_X550EM_x &&
	    !(hw->phy.nw_mng_अगर_sel & IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE)) अणु
		status = ixgbe_setup_ixfi_x550em(hw, &क्रमce_speed);

		अगर (status)
			वापस status;
	पूर्ण

	वापस hw->phy.ops.setup_link_speed(hw, speed, स्वतःneg_रुको);
पूर्ण

/** ixgbe_check_link_t_X550em - Determine link and speed status
  * @hw: poपूर्णांकer to hardware काष्ठाure
  * @speed: poपूर्णांकer to link speed
  * @link_up: true when link is up
  * @link_up_रुको_to_complete: bool used to रुको क्रम link up or not
  *
  * Check that both the MAC and X557 बाह्यal PHY have link.
  **/
अटल s32 ixgbe_check_link_t_X550em(काष्ठा ixgbe_hw *hw,
				     ixgbe_link_speed *speed,
				     bool *link_up,
				     bool link_up_रुको_to_complete)
अणु
	u32 status;
	u16 i, स्वतःneg_status;

	अगर (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		वापस IXGBE_ERR_CONFIG;

	status = ixgbe_check_mac_link_generic(hw, speed, link_up,
					      link_up_रुको_to_complete);

	/* If check link fails or MAC link is not up, then वापस */
	अगर (status || !(*link_up))
		वापस status;

	/* MAC link is up, so check बाह्यal PHY link.
	 * Link status is latching low, and can only be used to detect link
	 * drop, and not the current status of the link without perक्रमming
	 * back-to-back पढ़ोs.
	 */
	क्रम (i = 0; i < 2; i++) अणु
		status = hw->phy.ops.पढ़ो_reg(hw, MDIO_STAT1, MDIO_MMD_AN,
					      &स्वतःneg_status);

		अगर (status)
			वापस status;
	पूर्ण

	/* If बाह्यal PHY link is not up, then indicate link not up */
	अगर (!(स्वतःneg_status & IXGBE_MDIO_AUTO_NEG_LINK_STATUS))
		*link_up = false;

	वापस 0;
पूर्ण

/**
 * ixgbe_setup_sgmii - Set up link क्रम sgmii
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: unused
 * @स्वतःneg_रुको_to_complete: unused
 */
अटल s32
ixgbe_setup_sgmii(काष्ठा ixgbe_hw *hw, __always_unused ixgbe_link_speed speed,
		  __always_unused bool स्वतःneg_रुको_to_complete)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	u32 lval, sval, flx_val;
	s32 rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				       IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				       IXGBE_SB_IOSF_TARGET_KR_PHY, &lval);
	अगर (rc)
		वापस rc;

	lval &= ~IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE;
	lval &= ~IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_MASK;
	lval |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_SGMII_EN;
	lval |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CLAUSE_37_EN;
	lval |= IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_1G;
	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, lval);
	अगर (rc)
		वापस rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				       IXGBE_KRM_SGMII_CTRL(hw->bus.lan_id),
				       IXGBE_SB_IOSF_TARGET_KR_PHY, &sval);
	अगर (rc)
		वापस rc;

	sval |= IXGBE_KRM_SGMII_CTRL_MAC_TAR_FORCE_10_D;
	sval |= IXGBE_KRM_SGMII_CTRL_MAC_TAR_FORCE_100_D;
	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_SGMII_CTRL(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, sval);
	अगर (rc)
		वापस rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &flx_val);
	अगर (rc)
		वापस rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &flx_val);
	अगर (rc)
		वापस rc;

	flx_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_1G;
	flx_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;

	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, flx_val);
	अगर (rc)
		वापस rc;

	rc = ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);
	वापस rc;
पूर्ण

/**
 * ixgbe_setup_sgmii_fw - Set up link क्रम sgmii with firmware-controlled PHYs
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: the link speed to क्रमce
 * @स्वतःneg_रुको: true when रुकोing क्रम completion is needed
 */
अटल s32 ixgbe_setup_sgmii_fw(काष्ठा ixgbe_hw *hw, ixgbe_link_speed speed,
				bool स्वतःneg_रुको)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;
	u32 lval, sval, flx_val;
	s32 rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				       IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
				       IXGBE_SB_IOSF_TARGET_KR_PHY, &lval);
	अगर (rc)
		वापस rc;

	lval &= ~IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE;
	lval &= ~IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_MASK;
	lval |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_SGMII_EN;
	lval |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CLAUSE_37_EN;
	lval &= ~IXGBE_KRM_LINK_CTRL_1_TETH_FORCE_SPEED_1G;
	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, lval);
	अगर (rc)
		वापस rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				       IXGBE_KRM_SGMII_CTRL(hw->bus.lan_id),
				       IXGBE_SB_IOSF_TARGET_KR_PHY, &sval);
	अगर (rc)
		वापस rc;

	sval &= ~IXGBE_KRM_SGMII_CTRL_MAC_TAR_FORCE_10_D;
	sval &= ~IXGBE_KRM_SGMII_CTRL_MAC_TAR_FORCE_100_D;
	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_SGMII_CTRL(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, sval);
	अगर (rc)
		वापस rc;

	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, lval);
	अगर (rc)
		वापस rc;

	rc = mac->ops.पढ़ो_iosf_sb_reg(hw,
				    IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				    IXGBE_SB_IOSF_TARGET_KR_PHY, &flx_val);
	अगर (rc)
		वापस rc;

	flx_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_AN;
	flx_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;
	flx_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;

	rc = mac->ops.ग_लिखो_iosf_sb_reg(hw,
				    IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				    IXGBE_SB_IOSF_TARGET_KR_PHY, flx_val);
	अगर (rc)
		वापस rc;

	ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);

	वापस hw->phy.ops.setup_link_speed(hw, speed, स्वतःneg_रुको);
पूर्ण

/**
 * ixgbe_fc_स्वतःneg_sgmii_x550em_a - Enable flow control IEEE clause 37
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Enable flow control according to IEEE clause 37.
 */
अटल व्योम ixgbe_fc_स्वतःneg_sgmii_x550em_a(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = IXGBE_ERR_FC_NOT_NEGOTIATED;
	u32 info[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	ixgbe_link_speed speed;
	bool link_up;

	/* AN should have completed when the cable was plugged in.
	 * Look क्रम reasons to bail out.  Bail out अगर:
	 * - FC स्वतःneg is disabled, or अगर
	 * - link is not up.
	 */
	अगर (hw->fc.disable_fc_स्वतःneg)
		जाओ out;

	hw->mac.ops.check_link(hw, &speed, &link_up, false);
	अगर (!link_up)
		जाओ out;

	/* Check अगर स्वतः-negotiation has completed */
	status = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_GET_LINK_INFO, &info);
	अगर (status || !(info[0] & FW_PHY_ACT_GET_LINK_INFO_AN_COMPLETE)) अणु
		status = IXGBE_ERR_FC_NOT_NEGOTIATED;
		जाओ out;
	पूर्ण

	/* Negotiate the flow control */
	status = ixgbe_negotiate_fc(hw, info[0], info[0],
				    FW_PHY_ACT_GET_LINK_INFO_FC_RX,
				    FW_PHY_ACT_GET_LINK_INFO_FC_TX,
				    FW_PHY_ACT_GET_LINK_INFO_LP_FC_RX,
				    FW_PHY_ACT_GET_LINK_INFO_LP_FC_TX);

out:
	अगर (!status) अणु
		hw->fc.fc_was_स्वतःnegged = true;
	पूर्ण अन्यथा अणु
		hw->fc.fc_was_स्वतःnegged = false;
		hw->fc.current_mode = hw->fc.requested_mode;
	पूर्ण
पूर्ण

/** ixgbe_init_mac_link_ops_X550em_a - Init mac link function poपूर्णांकers
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_init_mac_link_ops_X550em_a(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;

	चयन (mac->ops.get_media_type(hw)) अणु
	हाल ixgbe_media_type_fiber:
		mac->ops.setup_fc = शून्य;
		mac->ops.fc_स्वतःneg = ixgbe_fc_स्वतःneg_fiber_x550em_a;
		अवरोध;
	हाल ixgbe_media_type_copper:
		अगर (hw->device_id != IXGBE_DEV_ID_X550EM_A_1G_T &&
		    hw->device_id != IXGBE_DEV_ID_X550EM_A_1G_T_L) अणु
			mac->ops.setup_link = ixgbe_setup_mac_link_t_X550em;
			अवरोध;
		पूर्ण
		mac->ops.fc_स्वतःneg = ixgbe_fc_स्वतःneg_sgmii_x550em_a;
		mac->ops.setup_fc = ixgbe_fc_स्वतःneg_fw;
		mac->ops.setup_link = ixgbe_setup_sgmii_fw;
		mac->ops.check_link = ixgbe_check_mac_link_generic;
		अवरोध;
	हाल ixgbe_media_type_backplane:
		mac->ops.fc_स्वतःneg = ixgbe_fc_स्वतःneg_backplane_x550em_a;
		mac->ops.setup_fc = ixgbe_setup_fc_backplane_x550em_a;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/** ixgbe_init_mac_link_ops_X550em - init mac link function poपूर्णांकers
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_init_mac_link_ops_X550em(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_mac_info *mac = &hw->mac;

	mac->ops.setup_fc = ixgbe_setup_fc_x550em;

	चयन (mac->ops.get_media_type(hw)) अणु
	हाल ixgbe_media_type_fiber:
		/* CS4227 करोes not support स्वतःneg, so disable the laser control
		 * functions क्रम SFP+ fiber
		 */
		mac->ops.disable_tx_laser = शून्य;
		mac->ops.enable_tx_laser = शून्य;
		mac->ops.flap_tx_laser = शून्य;
		mac->ops.setup_link = ixgbe_setup_mac_link_multispeed_fiber;
		चयन (hw->device_id) अणु
		हाल IXGBE_DEV_ID_X550EM_A_SFP_N:
			mac->ops.setup_mac_link = ixgbe_setup_mac_link_sfp_n;
			अवरोध;
		हाल IXGBE_DEV_ID_X550EM_A_SFP:
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550a;
			अवरोध;
		शेष:
			mac->ops.setup_mac_link =
						ixgbe_setup_mac_link_sfp_x550em;
			अवरोध;
		पूर्ण
		mac->ops.set_rate_select_speed =
					ixgbe_set_soft_rate_select_speed;
		अवरोध;
	हाल ixgbe_media_type_copper:
		अगर (hw->device_id == IXGBE_DEV_ID_X550EM_X_1G_T)
			अवरोध;
		mac->ops.setup_link = ixgbe_setup_mac_link_t_X550em;
		mac->ops.setup_fc = ixgbe_setup_fc_generic;
		mac->ops.check_link = ixgbe_check_link_t_X550em;
		अवरोध;
	हाल ixgbe_media_type_backplane:
		अगर (hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII ||
		    hw->device_id == IXGBE_DEV_ID_X550EM_A_SGMII_L)
			mac->ops.setup_link = ixgbe_setup_sgmii;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Additional modअगरication क्रम X550em_a devices */
	अगर (hw->mac.type == ixgbe_mac_x550em_a)
		ixgbe_init_mac_link_ops_X550em_a(hw);
पूर्ण

/** ixgbe_setup_sfp_modules_X550em - Setup SFP module
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_setup_sfp_modules_X550em(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	bool linear;

	/* Check अगर SFP module is supported */
	status = ixgbe_supported_sfp_modules_X550em(hw, &linear);
	अगर (status)
		वापस status;

	ixgbe_init_mac_link_ops_X550em(hw);
	hw->phy.ops.reset = शून्य;

	वापस 0;
पूर्ण

/** ixgbe_get_link_capabilities_x550em - Determines link capabilities
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: poपूर्णांकer to link speed
 * @स्वतःneg: true when स्वतःneg or स्वतःtry is enabled
 **/
अटल s32 ixgbe_get_link_capabilities_X550em(काष्ठा ixgbe_hw *hw,
					      ixgbe_link_speed *speed,
					      bool *स्वतःneg)
अणु
	अगर (hw->phy.type == ixgbe_phy_fw) अणु
		*स्वतःneg = true;
		*speed = hw->phy.speeds_supported;
		वापस 0;
	पूर्ण

	/* SFP */
	अगर (hw->phy.media_type == ixgbe_media_type_fiber) अणु
		/* CS4227 SFP must not enable स्वतः-negotiation */
		*स्वतःneg = false;

		अगर (hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core0 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_sx_core1 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core0 ||
		    hw->phy.sfp_type == ixgbe_sfp_type_1g_lx_core1) अणु
			*speed = IXGBE_LINK_SPEED_1GB_FULL;
			वापस 0;
		पूर्ण

		/* Link capabilities are based on SFP */
		अगर (hw->phy.multispeed_fiber)
			*speed = IXGBE_LINK_SPEED_10GB_FULL |
				 IXGBE_LINK_SPEED_1GB_FULL;
		अन्यथा
			*speed = IXGBE_LINK_SPEED_10GB_FULL;
	पूर्ण अन्यथा अणु
		चयन (hw->phy.type) अणु
		हाल ixgbe_phy_x550em_kx4:
			*speed = IXGBE_LINK_SPEED_1GB_FULL |
				 IXGBE_LINK_SPEED_2_5GB_FULL |
				 IXGBE_LINK_SPEED_10GB_FULL;
			अवरोध;
		हाल ixgbe_phy_x550em_xfi:
			*speed = IXGBE_LINK_SPEED_1GB_FULL |
				 IXGBE_LINK_SPEED_10GB_FULL;
			अवरोध;
		हाल ixgbe_phy_ext_1g_t:
		हाल ixgbe_phy_sgmii:
			*speed = IXGBE_LINK_SPEED_1GB_FULL;
			अवरोध;
		हाल ixgbe_phy_x550em_kr:
			अगर (hw->mac.type == ixgbe_mac_x550em_a) अणु
				/* check dअगरferent backplane modes */
				अगर (hw->phy.nw_mng_अगर_sel &
				    IXGBE_NW_MNG_IF_SEL_PHY_SPEED_2_5G) अणु
					*speed = IXGBE_LINK_SPEED_2_5GB_FULL;
					अवरोध;
				पूर्ण अन्यथा अगर (hw->device_id ==
					   IXGBE_DEV_ID_X550EM_A_KR_L) अणु
					*speed = IXGBE_LINK_SPEED_1GB_FULL;
					अवरोध;
				पूर्ण
			पूर्ण
			fallthrough;
		शेष:
			*speed = IXGBE_LINK_SPEED_10GB_FULL |
				 IXGBE_LINK_SPEED_1GB_FULL;
			अवरोध;
		पूर्ण
		*स्वतःneg = true;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ixgbe_get_lasi_ext_t_x550em - Determime बाह्यal Base T PHY पूर्णांकerrupt cause
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @lsc: poपूर्णांकer to boolean flag which indicates whether बाह्यal Base T
 *	 PHY पूर्णांकerrupt is lsc
 *
 * Determime अगर बाह्यal Base T PHY पूर्णांकerrupt cause is high temperature
 * failure alarm or link status change.
 *
 * Return IXGBE_ERR_OVERTEMP अगर पूर्णांकerrupt is high temperature
 * failure alarm, अन्यथा वापस PHY access status.
 **/
अटल s32 ixgbe_get_lasi_ext_t_x550em(काष्ठा ixgbe_hw *hw, bool *lsc)
अणु
	u32 status;
	u16 reg;

	*lsc = false;

	/* Venकरोr alarm triggered */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_CHIP_STD_INT_FLAG,
				      MDIO_MMD_VEND1,
				      &reg);

	अगर (status || !(reg & IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN))
		वापस status;

	/* Venकरोr Auto-Neg alarm triggered or Global alarm 1 triggered */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_FLAG,
				      MDIO_MMD_VEND1,
				      &reg);

	अगर (status || !(reg & (IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN |
				IXGBE_MDIO_GLOBAL_ALARM_1_INT)))
		वापस status;

	/* Global alarm triggered */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_ALARM_1,
				      MDIO_MMD_VEND1,
				      &reg);

	अगर (status)
		वापस status;

	/* If high temperature failure, then वापस over temp error and निकास */
	अगर (reg & IXGBE_MDIO_GLOBAL_ALM_1_HI_TMP_FAIL) अणु
		/* घातer करोwn the PHY in हाल the PHY FW didn't alपढ़ोy */
		ixgbe_set_copper_phy_घातer(hw, false);
		वापस IXGBE_ERR_OVERTEMP;
	पूर्ण
	अगर (reg & IXGBE_MDIO_GLOBAL_ALM_1_DEV_FAULT) अणु
		/*  device fault alarm triggered */
		status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_FAULT_MSG,
					  MDIO_MMD_VEND1,
					  &reg);
		अगर (status)
			वापस status;

		/* अगर device fault was due to high temp alarm handle and निकास */
		अगर (reg == IXGBE_MDIO_GLOBAL_FAULT_MSG_HI_TMP) अणु
			/* घातer करोwn the PHY in हाल the PHY FW didn't */
			ixgbe_set_copper_phy_घातer(hw, false);
			वापस IXGBE_ERR_OVERTEMP;
		पूर्ण
	पूर्ण

	/* Venकरोr alarm 2 triggered */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_CHIP_STD_INT_FLAG,
				      MDIO_MMD_AN, &reg);

	अगर (status || !(reg & IXGBE_MDIO_GLOBAL_STD_ALM2_INT))
		वापस status;

	/* link connect/disconnect event occurred */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_TX_ALARM2,
				      MDIO_MMD_AN, &reg);

	अगर (status)
		वापस status;

	/* Indicate LSC */
	अगर (reg & IXGBE_MDIO_AUTO_NEG_VEN_LSC)
		*lsc = true;

	वापस 0;
पूर्ण

/**
 * ixgbe_enable_lasi_ext_t_x550em - Enable बाह्यal Base T PHY पूर्णांकerrupts
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Enable link status change and temperature failure alarm क्रम the बाह्यal
 * Base T PHY
 *
 * Returns PHY access status
 **/
अटल s32 ixgbe_enable_lasi_ext_t_x550em(काष्ठा ixgbe_hw *hw)
अणु
	u32 status;
	u16 reg;
	bool lsc;

	/* Clear पूर्णांकerrupt flags */
	status = ixgbe_get_lasi_ext_t_x550em(hw, &lsc);

	/* Enable link status change alarm */

	/* Enable the LASI पूर्णांकerrupts on X552 devices to receive notअगरications
	 * of the link configurations of the बाह्यal PHY and correspondingly
	 * support the configuration of the पूर्णांकernal iXFI link, since iXFI करोes
	 * not support स्वतः-negotiation. This is not required क्रम X553 devices
	 * having KR support, which perक्रमms स्वतः-negotiations and which is used
	 * as the पूर्णांकernal link to the बाह्यal PHY. Hence adding a check here
	 * to aव्योम enabling LASI पूर्णांकerrupts क्रम X553 devices.
	 */
	अगर (hw->mac.type != ixgbe_mac_x550em_a) अणु
		status = hw->phy.ops.पढ़ो_reg(hw,
					    IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
					    MDIO_MMD_AN, &reg);
		अगर (status)
			वापस status;

		reg |= IXGBE_MDIO_PMA_TX_VEN_LASI_INT_EN;

		status = hw->phy.ops.ग_लिखो_reg(hw,
					    IXGBE_MDIO_PMA_TX_VEN_LASI_INT_MASK,
					    MDIO_MMD_AN, reg);
		अगर (status)
			वापस status;
	पूर्ण

	/* Enable high temperature failure and global fault alarms */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	अगर (status)
		वापस status;

	reg |= (IXGBE_MDIO_GLOBAL_INT_HI_TEMP_EN |
		IXGBE_MDIO_GLOBAL_INT_DEV_FAULT_EN);

	status = hw->phy.ops.ग_लिखो_reg(hw, IXGBE_MDIO_GLOBAL_INT_MASK,
				       MDIO_MMD_VEND1,
				       reg);
	अगर (status)
		वापस status;

	/* Enable venकरोr Auto-Neg alarm and Global Interrupt Mask 1 alarm */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	अगर (status)
		वापस status;

	reg |= (IXGBE_MDIO_GLOBAL_AN_VEN_ALM_INT_EN |
		IXGBE_MDIO_GLOBAL_ALARM_1_INT);

	status = hw->phy.ops.ग_लिखो_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_VEN_MASK,
				       MDIO_MMD_VEND1,
				       reg);
	अगर (status)
		वापस status;

	/* Enable chip-wide venकरोr alarm */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				      MDIO_MMD_VEND1,
				      &reg);
	अगर (status)
		वापस status;

	reg |= IXGBE_MDIO_GLOBAL_VEN_ALM_INT_EN;

	status = hw->phy.ops.ग_लिखो_reg(hw, IXGBE_MDIO_GLOBAL_INT_CHIP_STD_MASK,
				       MDIO_MMD_VEND1,
				       reg);

	वापस status;
पूर्ण

/**
 * ixgbe_handle_lasi_ext_t_x550em - Handle बाह्यal Base T PHY पूर्णांकerrupt
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Handle बाह्यal Base T PHY पूर्णांकerrupt. If high temperature
 * failure alarm then वापस error, अन्यथा अगर link status change
 * then setup पूर्णांकernal/बाह्यal PHY link
 *
 * Return IXGBE_ERR_OVERTEMP अगर पूर्णांकerrupt is high temperature
 * failure alarm, अन्यथा वापस PHY access status.
 **/
अटल s32 ixgbe_handle_lasi_ext_t_x550em(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_phy_info *phy = &hw->phy;
	bool lsc;
	u32 status;

	status = ixgbe_get_lasi_ext_t_x550em(hw, &lsc);
	अगर (status)
		वापस status;

	अगर (lsc && phy->ops.setup_पूर्णांकernal_link)
		वापस phy->ops.setup_पूर्णांकernal_link(hw);

	वापस 0;
पूर्ण

/**
 * ixgbe_setup_kr_speed_x550em - Configure the KR PHY क्रम link speed.
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @speed: link speed
 *
 * Configures the पूर्णांकegrated KR PHY.
 **/
अटल s32 ixgbe_setup_kr_speed_x550em(काष्ठा ixgbe_hw *hw,
				       ixgbe_link_speed speed)
अणु
	s32 status;
	u32 reg_val;

	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);
	अगर (status)
		वापस status;

	reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_ENABLE;
	reg_val &= ~(IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KR |
		     IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KX);

	/* Advertise 10G support. */
	अगर (speed & IXGBE_LINK_SPEED_10GB_FULL)
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KR;

	/* Advertise 1G support. */
	अगर (speed & IXGBE_LINK_SPEED_1GB_FULL)
		reg_val |= IXGBE_KRM_LINK_CTRL_1_TETH_AN_CAP_KX;

	status = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_CTRL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);

	अगर (hw->mac.type == ixgbe_mac_x550em_a) अणु
		/* Set lane mode  to KR स्वतः negotiation */
		status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &reg_val);

		अगर (status)
			वापस status;

		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_MASK;
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_SPEED_AN;
		reg_val |= IXGBE_KRM_PMD_FLX_MASK_ST20_AN_EN;
		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_AN37_EN;
		reg_val &= ~IXGBE_KRM_PMD_FLX_MASK_ST20_SGMII_EN;

		status = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
				IXGBE_KRM_PMD_FLX_MASK_ST20(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, reg_val);
	पूर्ण

	वापस ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);
पूर्ण

/**
 * ixgbe_setup_kr_x550em - Configure the KR PHY
 * @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_setup_kr_x550em(काष्ठा ixgbe_hw *hw)
अणु
	/* leave link alone क्रम 2.5G */
	अगर (hw->phy.स्वतःneg_advertised & IXGBE_LINK_SPEED_2_5GB_FULL)
		वापस 0;

	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	वापस ixgbe_setup_kr_speed_x550em(hw, hw->phy.स्वतःneg_advertised);
पूर्ण

/** ixgbe_ext_phy_t_x550em_get_link - Get ext phy link status
 *  @hw: address of hardware काष्ठाure
 *  @link_up: address of boolean to indicate link status
 *
 *  Returns error code अगर unable to get link status.
 **/
अटल s32 ixgbe_ext_phy_t_x550em_get_link(काष्ठा ixgbe_hw *hw, bool *link_up)
अणु
	u32 ret;
	u16 स्वतःneg_status;

	*link_up = false;

	/* पढ़ो this twice back to back to indicate current status */
	ret = hw->phy.ops.पढ़ो_reg(hw, MDIO_STAT1, MDIO_MMD_AN,
				   &स्वतःneg_status);
	अगर (ret)
		वापस ret;

	ret = hw->phy.ops.पढ़ो_reg(hw, MDIO_STAT1, MDIO_MMD_AN,
				   &स्वतःneg_status);
	अगर (ret)
		वापस ret;

	*link_up = !!(स्वतःneg_status & IXGBE_MDIO_AUTO_NEG_LINK_STATUS);

	वापस 0;
पूर्ण

/** ixgbe_setup_पूर्णांकernal_phy_t_x550em - Configure KR PHY to X557 link
 *  @hw: poपूर्णांक to hardware काष्ठाure
 *
 *  Configures the link between the पूर्णांकegrated KR PHY and the बाह्यal X557 PHY
 *  The driver will call this function when it माला_लो a link status change
 *  पूर्णांकerrupt from the X557 PHY. This function configures the link speed
 *  between the PHYs to match the link speed of the BASE-T link.
 *
 * A वापस of a non-zero value indicates an error, and the base driver should
 * not report link up.
 **/
अटल s32 ixgbe_setup_पूर्णांकernal_phy_t_x550em(काष्ठा ixgbe_hw *hw)
अणु
	ixgbe_link_speed क्रमce_speed;
	bool link_up;
	u32 status;
	u16 speed;

	अगर (hw->mac.ops.get_media_type(hw) != ixgbe_media_type_copper)
		वापस IXGBE_ERR_CONFIG;

	अगर (!(hw->mac.type == ixgbe_mac_X550EM_x &&
	      !(hw->phy.nw_mng_अगर_sel & IXGBE_NW_MNG_IF_SEL_INT_PHY_MODE))) अणु
		speed = IXGBE_LINK_SPEED_10GB_FULL |
			IXGBE_LINK_SPEED_1GB_FULL;
		वापस ixgbe_setup_kr_speed_x550em(hw, speed);
	पूर्ण

	/* If link is not up, then there is no setup necessary so वापस  */
	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	अगर (status)
		वापस status;

	अगर (!link_up)
		वापस 0;

	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_STAT,
				      MDIO_MMD_AN,
				      &speed);
	अगर (status)
		वापस status;

	/* If link is not still up, then no setup is necessary so वापस */
	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	अगर (status)
		वापस status;

	अगर (!link_up)
		वापस 0;

	/* clear everything but the speed and duplex bits */
	speed &= IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_MASK;

	चयन (speed) अणु
	हाल IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_10GB_FULL:
		क्रमce_speed = IXGBE_LINK_SPEED_10GB_FULL;
		अवरोध;
	हाल IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_1GB_FULL:
		क्रमce_speed = IXGBE_LINK_SPEED_1GB_FULL;
		अवरोध;
	शेष:
		/* Internal PHY करोes not support anything अन्यथा */
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
	पूर्ण

	वापस ixgbe_setup_ixfi_x550em(hw, &क्रमce_speed);
पूर्ण

/** ixgbe_reset_phy_t_X550em - Perक्रमms X557 PHY reset and enables LASI
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_reset_phy_t_X550em(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;

	status = ixgbe_reset_phy_generic(hw);

	अगर (status)
		वापस status;

	/* Configure Link Status Alarm and Temperature Threshold पूर्णांकerrupts */
	वापस ixgbe_enable_lasi_ext_t_x550em(hw);
पूर्ण

/**
 *  ixgbe_led_on_t_x550em - Turns on the software controllable LEDs.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @led_idx: led number to turn on
 **/
अटल s32 ixgbe_led_on_t_x550em(काष्ठा ixgbe_hw *hw, u32 led_idx)
अणु
	u16 phy_data;

	अगर (led_idx >= IXGBE_X557_MAX_LED_INDEX)
		वापस IXGBE_ERR_PARAM;

	/* To turn on the LED, set mode to ON. */
	hw->phy.ops.पढ़ो_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			     MDIO_MMD_VEND1, &phy_data);
	phy_data |= IXGBE_X557_LED_MANUAL_SET_MASK;
	hw->phy.ops.ग_लिखो_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			      MDIO_MMD_VEND1, phy_data);

	वापस 0;
पूर्ण

/**
 *  ixgbe_led_off_t_x550em - Turns off the software controllable LEDs.
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @led_idx: led number to turn off
 **/
अटल s32 ixgbe_led_off_t_x550em(काष्ठा ixgbe_hw *hw, u32 led_idx)
अणु
	u16 phy_data;

	अगर (led_idx >= IXGBE_X557_MAX_LED_INDEX)
		वापस IXGBE_ERR_PARAM;

	/* To turn on the LED, set mode to ON. */
	hw->phy.ops.पढ़ो_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			     MDIO_MMD_VEND1, &phy_data);
	phy_data &= ~IXGBE_X557_LED_MANUAL_SET_MASK;
	hw->phy.ops.ग_लिखो_reg(hw, IXGBE_X557_LED_PROVISIONING + led_idx,
			      MDIO_MMD_VEND1, phy_data);

	वापस 0;
पूर्ण

/**
 *  ixgbe_set_fw_drv_ver_x550 - Sends driver version to firmware
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @maj: driver version major number
 *  @min: driver version minor number
 *  @build: driver version build number
 *  @sub: driver version sub build number
 *  @len: length of driver_ver string
 *  @driver_ver: driver string
 *
 *  Sends driver version number to firmware through the manageability
 *  block.  On success वापस 0
 *  अन्यथा वापसs IXGBE_ERR_SWFW_SYNC when encountering an error acquiring
 *  semaphore or IXGBE_ERR_HOST_INTERFACE_COMMAND when command fails.
 **/
अटल s32 ixgbe_set_fw_drv_ver_x550(काष्ठा ixgbe_hw *hw, u8 maj, u8 min,
				     u8 build, u8 sub, u16 len,
				     स्थिर अक्षर *driver_ver)
अणु
	काष्ठा ixgbe_hic_drv_info2 fw_cmd;
	s32 ret_val;
	पूर्णांक i;

	अगर (!len || !driver_ver || (len > माप(fw_cmd.driver_string)))
		वापस IXGBE_ERR_INVALID_ARGUMENT;

	fw_cmd.hdr.cmd = FW_CEM_CMD_DRIVER_INFO;
	fw_cmd.hdr.buf_len = FW_CEM_CMD_DRIVER_INFO_LEN + len;
	fw_cmd.hdr.cmd_or_resp.cmd_resv = FW_CEM_CMD_RESERVED;
	fw_cmd.port_num = (u8)hw->bus.func;
	fw_cmd.ver_maj = maj;
	fw_cmd.ver_min = min;
	fw_cmd.ver_build = build;
	fw_cmd.ver_sub = sub;
	fw_cmd.hdr.checksum = 0;
	स_नकल(fw_cmd.driver_string, driver_ver, len);
	fw_cmd.hdr.checksum = ixgbe_calculate_checksum((u8 *)&fw_cmd,
			      (FW_CEM_HDR_LEN + fw_cmd.hdr.buf_len));

	क्रम (i = 0; i <= FW_CEM_MAX_RETRIES; i++) अणु
		ret_val = ixgbe_host_पूर्णांकerface_command(hw, (u32 *)&fw_cmd,
						       माप(fw_cmd),
						       IXGBE_HI_COMMAND_TIMEOUT,
						       true);
		अगर (ret_val)
			जारी;

		अगर (fw_cmd.hdr.cmd_or_resp.ret_status !=
		    FW_CEM_RESP_STATUS_SUCCESS)
			वापस IXGBE_ERR_HOST_INTERFACE_COMMAND;
		वापस 0;
	पूर्ण

	वापस ret_val;
पूर्ण

/** ixgbe_get_lcd_x550em - Determine lowest common denominator
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @lcd_speed: poपूर्णांकer to lowest common link speed
 *
 *  Determine lowest common link speed with link partner.
 **/
अटल s32 ixgbe_get_lcd_t_x550em(काष्ठा ixgbe_hw *hw,
				  ixgbe_link_speed *lcd_speed)
अणु
	u16 an_lp_status;
	s32 status;
	u16 word = hw->eeprom.ctrl_word_3;

	*lcd_speed = IXGBE_LINK_SPEED_UNKNOWN;

	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_AUTO_NEG_LP_STATUS,
				      MDIO_MMD_AN,
				      &an_lp_status);
	अगर (status)
		वापस status;

	/* If link partner advertised 1G, वापस 1G */
	अगर (an_lp_status & IXGBE_AUTO_NEG_LP_1000BASE_CAP) अणु
		*lcd_speed = IXGBE_LINK_SPEED_1GB_FULL;
		वापस status;
	पूर्ण

	/* If 10G disabled क्रम LPLU via NVM D10GMP, then वापस no valid LCD */
	अगर ((hw->bus.lan_id && (word & NVM_INIT_CTRL_3_D10GMP_PORT1)) ||
	    (word & NVM_INIT_CTRL_3_D10GMP_PORT0))
		वापस status;

	/* Link partner not capable of lower speeds, वापस 10G */
	*lcd_speed = IXGBE_LINK_SPEED_10GB_FULL;
	वापस status;
पूर्ण

/**
 * ixgbe_setup_fc_x550em - Set up flow control
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_setup_fc_x550em(काष्ठा ixgbe_hw *hw)
अणु
	bool छोड़ो, यंत्र_dir;
	u32 reg_val;
	s32 rc = 0;

	/* Validate the requested mode */
	अगर (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_छोड़ो) अणु
		hw_err(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
	पूर्ण

	/* 10gig parts करो not have a word in the EEPROM to determine the
	 * शेष flow control setting, so we explicitly set it to full.
	 */
	अगर (hw->fc.requested_mode == ixgbe_fc_शेष)
		hw->fc.requested_mode = ixgbe_fc_full;

	/* Determine PAUSE and ASM_सूची bits. */
	चयन (hw->fc.requested_mode) अणु
	हाल ixgbe_fc_none:
		छोड़ो = false;
		यंत्र_dir = false;
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		छोड़ो = false;
		यंत्र_dir = true;
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		/* Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE, as such we fall
		 * through to the fc_full statement.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
		fallthrough;
	हाल ixgbe_fc_full:
		छोड़ो = true;
		यंत्र_dir = true;
		अवरोध;
	शेष:
		hw_err(hw, "Flow control param set incorrectly\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_X550EM_X_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR_L:
		rc = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
					    IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					    IXGBE_SB_IOSF_TARGET_KR_PHY,
					    &reg_val);
		अगर (rc)
			वापस rc;

		reg_val &= ~(IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			     IXGBE_KRM_AN_CNTL_1_ASM_PAUSE);
		अगर (छोड़ो)
			reg_val |= IXGBE_KRM_AN_CNTL_1_SYM_PAUSE;
		अगर (यंत्र_dir)
			reg_val |= IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		rc = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
					    IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					    IXGBE_SB_IOSF_TARGET_KR_PHY,
					    reg_val);

		/* This device करोes not fully support AN. */
		hw->fc.disable_fc_स्वतःneg = true;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_X_XFI:
		hw->fc.disable_fc_स्वतःneg = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg_backplane_x550em_a - Enable flow control IEEE clause 37
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_fc_स्वतःneg_backplane_x550em_a(काष्ठा ixgbe_hw *hw)
अणु
	u32 link_s1, lp_an_page_low, an_cntl_1;
	s32 status = IXGBE_ERR_FC_NOT_NEGOTIATED;
	ixgbe_link_speed speed;
	bool link_up;

	/* AN should have completed when the cable was plugged in.
	 * Look क्रम reasons to bail out.  Bail out अगर:
	 * - FC स्वतःneg is disabled, or अगर
	 * - link is not up.
	 */
	अगर (hw->fc.disable_fc_स्वतःneg) अणु
		hw_err(hw, "Flow control autoneg is disabled");
		जाओ out;
	पूर्ण

	hw->mac.ops.check_link(hw, &speed, &link_up, false);
	अगर (!link_up) अणु
		hw_err(hw, "The link is down");
		जाओ out;
	पूर्ण

	/* Check at स्वतः-negotiation has completed */
	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
					IXGBE_KRM_LINK_S1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &link_s1);

	अगर (status || (link_s1 & IXGBE_KRM_LINK_S1_MAC_AN_COMPLETE) == 0) अणु
		hw_dbg(hw, "Auto-Negotiation did not complete\n");
		status = IXGBE_ERR_FC_NOT_NEGOTIATED;
		जाओ out;
	पूर्ण

	/* Read the 10g AN स्वतःc and LP ability रेजिस्टरs and resolve
	 * local flow control settings accordingly
	 */
	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &an_cntl_1);

	अगर (status) अणु
		hw_dbg(hw, "Auto-Negotiation did not complete\n");
		जाओ out;
	पूर्ण

	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
				IXGBE_KRM_LP_BASE_PAGE_HIGH(hw->bus.lan_id),
				IXGBE_SB_IOSF_TARGET_KR_PHY, &lp_an_page_low);

	अगर (status) अणु
		hw_dbg(hw, "Auto-Negotiation did not complete\n");
		जाओ out;
	पूर्ण

	status = ixgbe_negotiate_fc(hw, an_cntl_1, lp_an_page_low,
				    IXGBE_KRM_AN_CNTL_1_SYM_PAUSE,
				    IXGBE_KRM_AN_CNTL_1_ASM_PAUSE,
				    IXGBE_KRM_LP_BASE_PAGE_HIGH_SYM_PAUSE,
				    IXGBE_KRM_LP_BASE_PAGE_HIGH_ASM_PAUSE);

out:
	अगर (!status) अणु
		hw->fc.fc_was_स्वतःnegged = true;
	पूर्ण अन्यथा अणु
		hw->fc.fc_was_स्वतःnegged = false;
		hw->fc.current_mode = hw->fc.requested_mode;
	पूर्ण
पूर्ण

/**
 *  ixgbe_fc_स्वतःneg_fiber_x550em_a - passthrough FC settings
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल व्योम ixgbe_fc_स्वतःneg_fiber_x550em_a(काष्ठा ixgbe_hw *hw)
अणु
	hw->fc.fc_was_स्वतःnegged = false;
	hw->fc.current_mode = hw->fc.requested_mode;
पूर्ण

/** ixgbe_enter_lplu_x550em - Transition to low घातer states
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Configures Low Power Link Up on transition to low घातer states
 *  (from D0 to non-D0). Link is required to enter LPLU so aव्योम resetting
 *  the X557 PHY immediately prior to entering LPLU.
 **/
अटल s32 ixgbe_enter_lplu_t_x550em(काष्ठा ixgbe_hw *hw)
अणु
	u16 an_10g_cntl_reg, स्वतःneg_reg, speed;
	s32 status;
	ixgbe_link_speed lcd_speed;
	u32 save_स्वतःneg;
	bool link_up;

	/* If blocked by MNG FW, then करोn't restart AN */
	अगर (ixgbe_check_reset_blocked(hw))
		वापस 0;

	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	अगर (status)
		वापस status;

	status = hw->eeprom.ops.पढ़ो(hw, NVM_INIT_CTRL_3,
				     &hw->eeprom.ctrl_word_3);
	अगर (status)
		वापस status;

	/* If link is करोwn, LPLU disabled in NVM, WoL disabled, or
	 * manageability disabled, then क्रमce link करोwn by entering
	 * low घातer mode.
	 */
	अगर (!link_up || !(hw->eeprom.ctrl_word_3 & NVM_INIT_CTRL_3_LPLU) ||
	    !(hw->wol_enabled || ixgbe_mng_present(hw)))
		वापस ixgbe_set_copper_phy_घातer(hw, false);

	/* Determine LCD */
	status = ixgbe_get_lcd_t_x550em(hw, &lcd_speed);
	अगर (status)
		वापस status;

	/* If no valid LCD link speed, then क्रमce link करोwn and निकास. */
	अगर (lcd_speed == IXGBE_LINK_SPEED_UNKNOWN)
		वापस ixgbe_set_copper_phy_घातer(hw, false);

	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_STAT,
				      MDIO_MMD_AN,
				      &speed);
	अगर (status)
		वापस status;

	/* If no link now, speed is invalid so take link करोwn */
	status = ixgbe_ext_phy_t_x550em_get_link(hw, &link_up);
	अगर (status)
		वापस ixgbe_set_copper_phy_घातer(hw, false);

	/* clear everything but the speed bits */
	speed &= IXGBE_MDIO_AUTO_NEG_VEN_STAT_SPEED_MASK;

	/* If current speed is alपढ़ोy LCD, then निकास. */
	अगर (((speed == IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_1GB) &&
	     (lcd_speed == IXGBE_LINK_SPEED_1GB_FULL)) ||
	    ((speed == IXGBE_MDIO_AUTO_NEG_VENDOR_STATUS_10GB) &&
	     (lcd_speed == IXGBE_LINK_SPEED_10GB_FULL)))
		वापस status;

	/* Clear AN completed indication */
	status = hw->phy.ops.पढ़ो_reg(hw, IXGBE_MDIO_AUTO_NEG_VENDOR_TX_ALARM,
				      MDIO_MMD_AN,
				      &स्वतःneg_reg);
	अगर (status)
		वापस status;

	status = hw->phy.ops.पढ़ो_reg(hw, MDIO_AN_10GBT_CTRL,
				      MDIO_MMD_AN,
				      &an_10g_cntl_reg);
	अगर (status)
		वापस status;

	status = hw->phy.ops.पढ़ो_reg(hw,
				      IXGBE_MII_AUTONEG_VENDOR_PROVISION_1_REG,
				      MDIO_MMD_AN,
				      &स्वतःneg_reg);
	अगर (status)
		वापस status;

	save_स्वतःneg = hw->phy.स्वतःneg_advertised;

	/* Setup link at least common link speed */
	status = hw->mac.ops.setup_link(hw, lcd_speed, false);

	/* restore स्वतःneg from beक्रमe setting lplu speed */
	hw->phy.स्वतःneg_advertised = save_स्वतःneg;

	वापस status;
पूर्ण

/**
 * ixgbe_reset_phy_fw - Reset firmware-controlled PHYs
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_reset_phy_fw(काष्ठा ixgbe_hw *hw)
अणु
	u32 store[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	s32 rc;

	अगर (hw->phy.reset_disable || ixgbe_check_reset_blocked(hw))
		वापस 0;

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_PHY_SW_RESET, &store);
	अगर (rc)
		वापस rc;
	स_रखो(store, 0, माप(store));

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_INIT_PHY, &store);
	अगर (rc)
		वापस rc;

	वापस ixgbe_setup_fw_link(hw);
पूर्ण

/**
 * ixgbe_check_overtemp_fw - Check firmware-controlled PHYs क्रम overtemp
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल s32 ixgbe_check_overtemp_fw(काष्ठा ixgbe_hw *hw)
अणु
	u32 store[FW_PHY_ACT_DATA_COUNT] = अणु 0 पूर्ण;
	s32 rc;

	rc = ixgbe_fw_phy_activity(hw, FW_PHY_ACT_GET_LINK_INFO, &store);
	अगर (rc)
		वापस rc;

	अगर (store[0] & FW_PHY_ACT_GET_LINK_INFO_TEMP) अणु
		ixgbe_shutकरोwn_fw_phy(hw);
		वापस IXGBE_ERR_OVERTEMP;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ixgbe_पढ़ो_mng_अगर_sel_x550em - Read NW_MNG_IF_SEL रेजिस्टर
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * Read NW_MNG_IF_SEL रेजिस्टर and save field values.
 */
अटल व्योम ixgbe_पढ़ो_mng_अगर_sel_x550em(काष्ठा ixgbe_hw *hw)
अणु
	/* Save NW management पूर्णांकerface connected on board. This is used
	 * to determine पूर्णांकernal PHY mode.
	 */
	hw->phy.nw_mng_अगर_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);

	/* If X552 (X550EM_a) and MDIO is connected to बाह्यal PHY, then set
	 * PHY address. This रेजिस्टर field was has only been used क्रम X552.
	 */
	अगर (hw->mac.type == ixgbe_mac_x550em_a &&
	    hw->phy.nw_mng_अगर_sel & IXGBE_NW_MNG_IF_SEL_MDIO_ACT) अणु
		hw->phy.mdio.prtad = (hw->phy.nw_mng_अगर_sel &
				      IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD) >>
				     IXGBE_NW_MNG_IF_SEL_MDIO_PHY_ADD_SHIFT;
	पूर्ण
पूर्ण

/** ixgbe_init_phy_ops_X550em - PHY/SFP specअगरic init
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Initialize any function poपूर्णांकers that were not able to be
 *  set during init_shared_code because the PHY/SFP type was
 *  not known.  Perक्रमm the SFP init अगर necessary.
 **/
अटल s32 ixgbe_init_phy_ops_X550em(काष्ठा ixgbe_hw *hw)
अणु
	काष्ठा ixgbe_phy_info *phy = &hw->phy;
	s32 ret_val;

	hw->mac.ops.set_lan_id(hw);

	ixgbe_पढ़ो_mng_अगर_sel_x550em(hw);

	अगर (hw->mac.ops.get_media_type(hw) == ixgbe_media_type_fiber) अणु
		phy->phy_semaphore_mask = IXGBE_GSSR_SHARED_I2C_SM;
		ixgbe_setup_mux_ctl(hw);
	पूर्ण

	/* Identअगरy the PHY or SFP module */
	ret_val = phy->ops.identअगरy(hw);
	अगर (ret_val == IXGBE_ERR_SFP_NOT_SUPPORTED ||
	    ret_val == IXGBE_ERR_PHY_ADDR_INVALID)
		वापस ret_val;

	/* Setup function poपूर्णांकers based on detected hardware */
	ixgbe_init_mac_link_ops_X550em(hw);
	अगर (phy->sfp_type != ixgbe_sfp_type_unknown)
		phy->ops.reset = शून्य;

	/* Set functions poपूर्णांकers based on phy type */
	चयन (hw->phy.type) अणु
	हाल ixgbe_phy_x550em_kx4:
		phy->ops.setup_link = शून्य;
		phy->ops.पढ़ो_reg = ixgbe_पढ़ो_phy_reg_x550em;
		phy->ops.ग_लिखो_reg = ixgbe_ग_लिखो_phy_reg_x550em;
		अवरोध;
	हाल ixgbe_phy_x550em_kr:
		phy->ops.setup_link = ixgbe_setup_kr_x550em;
		phy->ops.पढ़ो_reg = ixgbe_पढ़ो_phy_reg_x550em;
		phy->ops.ग_लिखो_reg = ixgbe_ग_लिखो_phy_reg_x550em;
		अवरोध;
	हाल ixgbe_phy_x550em_xfi:
		/* link is managed by HW */
		phy->ops.setup_link = शून्य;
		phy->ops.पढ़ो_reg = ixgbe_पढ़ो_phy_reg_x550em;
		phy->ops.ग_लिखो_reg = ixgbe_ग_लिखो_phy_reg_x550em;
		अवरोध;
	हाल ixgbe_phy_x550em_ext_t:
		/* Save NW management पूर्णांकerface connected on board. This is used
		 * to determine पूर्णांकernal PHY mode
		 */
		phy->nw_mng_अगर_sel = IXGBE_READ_REG(hw, IXGBE_NW_MNG_IF_SEL);

		/* If पूर्णांकernal link mode is XFI, then setup iXFI पूर्णांकernal link,
		 * अन्यथा setup KR now.
		 */
		phy->ops.setup_पूर्णांकernal_link =
					      ixgbe_setup_पूर्णांकernal_phy_t_x550em;

		/* setup SW LPLU only क्रम first revision */
		अगर (hw->mac.type == ixgbe_mac_X550EM_x &&
		    !(IXGBE_READ_REG(hw, IXGBE_FUSES0_GROUP(0)) &
		      IXGBE_FUSES0_REV_MASK))
			phy->ops.enter_lplu = ixgbe_enter_lplu_t_x550em;

		phy->ops.handle_lasi = ixgbe_handle_lasi_ext_t_x550em;
		phy->ops.reset = ixgbe_reset_phy_t_X550em;
		अवरोध;
	हाल ixgbe_phy_sgmii:
		phy->ops.setup_link = शून्य;
		अवरोध;
	हाल ixgbe_phy_fw:
		phy->ops.setup_link = ixgbe_setup_fw_link;
		phy->ops.reset = ixgbe_reset_phy_fw;
		अवरोध;
	हाल ixgbe_phy_ext_1g_t:
		phy->ops.setup_link = शून्य;
		phy->ops.पढ़ो_reg = शून्य;
		phy->ops.ग_लिखो_reg = शून्य;
		phy->ops.reset = शून्य;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret_val;
पूर्ण

/** ixgbe_get_media_type_X550em - Get media type
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Returns the media type (fiber, copper, backplane)
 *
 */
अटल क्रमागत ixgbe_media_type ixgbe_get_media_type_X550em(काष्ठा ixgbe_hw *hw)
अणु
	क्रमागत ixgbe_media_type media_type;

	/* Detect अगर there is a copper PHY attached. */
	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_X550EM_A_SGMII:
	हाल IXGBE_DEV_ID_X550EM_A_SGMII_L:
		hw->phy.type = ixgbe_phy_sgmii;
		fallthrough;
	हाल IXGBE_DEV_ID_X550EM_X_KR:
	हाल IXGBE_DEV_ID_X550EM_X_KX4:
	हाल IXGBE_DEV_ID_X550EM_X_XFI:
	हाल IXGBE_DEV_ID_X550EM_A_KR:
	हाल IXGBE_DEV_ID_X550EM_A_KR_L:
		media_type = ixgbe_media_type_backplane;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_X_SFP:
	हाल IXGBE_DEV_ID_X550EM_A_SFP:
	हाल IXGBE_DEV_ID_X550EM_A_SFP_N:
		media_type = ixgbe_media_type_fiber;
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_X_1G_T:
	हाल IXGBE_DEV_ID_X550EM_X_10G_T:
	हाल IXGBE_DEV_ID_X550EM_A_10G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		media_type = ixgbe_media_type_copper;
		अवरोध;
	शेष:
		media_type = ixgbe_media_type_unknown;
		अवरोध;
	पूर्ण
	वापस media_type;
पूर्ण

/** ixgbe_init_ext_t_x550em - Start (unstall) the बाह्यal Base T PHY.
 ** @hw: poपूर्णांकer to hardware काष्ठाure
 **/
अटल s32 ixgbe_init_ext_t_x550em(काष्ठा ixgbe_hw *hw)
अणु
	s32 status;
	u16 reg;

	status = hw->phy.ops.पढ़ो_reg(hw,
				      IXGBE_MDIO_TX_VENDOR_ALARMS_3,
				      MDIO_MMD_PMAPMD,
				      &reg);
	अगर (status)
		वापस status;

	/* If PHY FW reset completed bit is set then this is the first
	 * SW instance after a घातer on so the PHY FW must be un-stalled.
	 */
	अगर (reg & IXGBE_MDIO_TX_VENDOR_ALARMS_3_RST_MASK) अणु
		status = hw->phy.ops.पढ़ो_reg(hw,
					IXGBE_MDIO_GLOBAL_RES_PR_10,
					MDIO_MMD_VEND1,
					&reg);
		अगर (status)
			वापस status;

		reg &= ~IXGBE_MDIO_POWER_UP_STALL;

		status = hw->phy.ops.ग_लिखो_reg(hw,
					IXGBE_MDIO_GLOBAL_RES_PR_10,
					MDIO_MMD_VEND1,
					reg);
		अगर (status)
			वापस status;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ixgbe_set_mdio_speed - Set MDIO घड़ी speed
 * @hw: poपूर्णांकer to hardware काष्ठाure
 */
अटल व्योम ixgbe_set_mdio_speed(काष्ठा ixgbe_hw *hw)
अणु
	u32 hlreg0;

	चयन (hw->device_id) अणु
	हाल IXGBE_DEV_ID_X550EM_X_10G_T:
	हाल IXGBE_DEV_ID_X550EM_A_SGMII:
	हाल IXGBE_DEV_ID_X550EM_A_SGMII_L:
	हाल IXGBE_DEV_ID_X550EM_A_10G_T:
	हाल IXGBE_DEV_ID_X550EM_A_SFP:
		/* Config MDIO घड़ी speed beक्रमe the first MDIO PHY access */
		hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		hlreg0 &= ~IXGBE_HLREG0_MDCSPD;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
		अवरोध;
	हाल IXGBE_DEV_ID_X550EM_A_1G_T:
	हाल IXGBE_DEV_ID_X550EM_A_1G_T_L:
		/* Select fast MDIO घड़ी speed क्रम these devices */
		hlreg0 = IXGBE_READ_REG(hw, IXGBE_HLREG0);
		hlreg0 |= IXGBE_HLREG0_MDCSPD;
		IXGBE_WRITE_REG(hw, IXGBE_HLREG0, hlreg0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**  ixgbe_reset_hw_X550em - Perक्रमm hardware reset
 **  @hw: poपूर्णांकer to hardware काष्ठाure
 **
 **  Resets the hardware by resetting the transmit and receive units, masks
 **  and clears all पूर्णांकerrupts, perक्रमm a PHY reset, and perक्रमm a link (MAC)
 **  reset.
 **/
अटल s32 ixgbe_reset_hw_X550em(काष्ठा ixgbe_hw *hw)
अणु
	ixgbe_link_speed link_speed;
	s32 status;
	u32 ctrl = 0;
	u32 i;
	bool link_up = false;
	u32 swfw_mask = hw->phy.phy_semaphore_mask;

	/* Call adapter stop to disable Tx/Rx and clear पूर्णांकerrupts */
	status = hw->mac.ops.stop_adapter(hw);
	अगर (status)
		वापस status;

	/* flush pending Tx transactions */
	ixgbe_clear_tx_pending(hw);

	/* PHY ops must be identअगरied and initialized prior to reset */
	status = hw->phy.ops.init(hw);
	अगर (status == IXGBE_ERR_SFP_NOT_SUPPORTED ||
	    status == IXGBE_ERR_PHY_ADDR_INVALID)
		वापस status;

	/* start the बाह्यal PHY */
	अगर (hw->phy.type == ixgbe_phy_x550em_ext_t) अणु
		status = ixgbe_init_ext_t_x550em(hw);
		अगर (status)
			वापस status;
	पूर्ण

	/* Setup SFP module अगर there is one present. */
	अगर (hw->phy.sfp_setup_needed) अणु
		status = hw->mac.ops.setup_sfp(hw);
		hw->phy.sfp_setup_needed = false;
	पूर्ण

	अगर (status == IXGBE_ERR_SFP_NOT_SUPPORTED)
		वापस status;

	/* Reset PHY */
	अगर (!hw->phy.reset_disable && hw->phy.ops.reset)
		hw->phy.ops.reset(hw);

mac_reset_top:
	/* Issue global reset to the MAC.  Needs to be SW reset अगर link is up.
	 * If link reset is used when link is up, it might reset the PHY when
	 * mng is using it.  If link is करोwn or the flag to क्रमce full link
	 * reset is set, then perक्रमm link reset.
	 */
	ctrl = IXGBE_CTRL_LNK_RST;

	अगर (!hw->क्रमce_full_reset) अणु
		hw->mac.ops.check_link(hw, &link_speed, &link_up, false);
		अगर (link_up)
			ctrl = IXGBE_CTRL_RST;
	पूर्ण

	status = hw->mac.ops.acquire_swfw_sync(hw, swfw_mask);
	अगर (status) अणु
		hw_dbg(hw, "semaphore failed with %d", status);
		वापस IXGBE_ERR_SWFW_SYNC;
	पूर्ण

	ctrl |= IXGBE_READ_REG(hw, IXGBE_CTRL);
	IXGBE_WRITE_REG(hw, IXGBE_CTRL, ctrl);
	IXGBE_WRITE_FLUSH(hw);
	hw->mac.ops.release_swfw_sync(hw, swfw_mask);
	usleep_range(1000, 1200);

	/* Poll क्रम reset bit to self-clear meaning reset is complete */
	क्रम (i = 0; i < 10; i++) अणु
		ctrl = IXGBE_READ_REG(hw, IXGBE_CTRL);
		अगर (!(ctrl & IXGBE_CTRL_RST_MASK))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (ctrl & IXGBE_CTRL_RST_MASK) अणु
		status = IXGBE_ERR_RESET_FAILED;
		hw_dbg(hw, "Reset polling failed to complete.\n");
	पूर्ण

	msleep(50);

	/* Double resets are required क्रम recovery from certain error
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modअगरy this value when programming the SAN MAC address.
	 */
	अगर (hw->mac.flags & IXGBE_FLAGS_DOUBLE_RESET_REQUIRED) अणु
		hw->mac.flags &= ~IXGBE_FLAGS_DOUBLE_RESET_REQUIRED;
		जाओ mac_reset_top;
	पूर्ण

	/* Store the permanent mac address */
	hw->mac.ops.get_mac_addr(hw, hw->mac.perm_addr);

	/* Store MAC address from RAR0, clear receive address रेजिस्टरs, and
	 * clear the multicast table.  Also reset num_rar_entries to 128,
	 * since we modअगरy this value when programming the SAN MAC address.
	 */
	hw->mac.num_rar_entries = 128;
	hw->mac.ops.init_rx_addrs(hw);

	ixgbe_set_mdio_speed(hw);

	अगर (hw->device_id == IXGBE_DEV_ID_X550EM_X_SFP)
		ixgbe_setup_mux_ctl(hw);

	वापस status;
पूर्ण

/** ixgbe_set_ethertype_anti_spoofing_X550 - Enable/Disable Ethertype
 *	anti-spoofing
 *  @hw:  poपूर्णांकer to hardware काष्ठाure
 *  @enable: enable or disable चयन क्रम Ethertype anti-spoofing
 *  @vf: Virtual Function pool - VF Pool to set क्रम Ethertype anti-spoofing
 **/
अटल व्योम ixgbe_set_ethertype_anti_spoofing_X550(काष्ठा ixgbe_hw *hw,
						   bool enable, पूर्णांक vf)
अणु
	पूर्णांक vf_target_reg = vf >> 3;
	पूर्णांक vf_target_shअगरt = vf % 8 + IXGBE_SPOOF_ETHERTYPEAS_SHIFT;
	u32 pfvfspoof;

	pfvfspoof = IXGBE_READ_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg));
	अगर (enable)
		pfvfspoof |= BIT(vf_target_shअगरt);
	अन्यथा
		pfvfspoof &= ~BIT(vf_target_shअगरt);

	IXGBE_WRITE_REG(hw, IXGBE_PFVFSPOOF(vf_target_reg), pfvfspoof);
पूर्ण

/** ixgbe_set_source_address_pruning_X550 - Enable/Disbale src address pruning
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *  @enable: enable or disable source address pruning
 *  @pool: Rx pool to set source address pruning क्रम
 **/
अटल व्योम ixgbe_set_source_address_pruning_X550(काष्ठा ixgbe_hw *hw,
						  bool enable,
						  अचिन्हित पूर्णांक pool)
अणु
	u64 pfflp;

	/* max rx pool is 63 */
	अगर (pool > 63)
		वापस;

	pfflp = (u64)IXGBE_READ_REG(hw, IXGBE_PFFLPL);
	pfflp |= (u64)IXGBE_READ_REG(hw, IXGBE_PFFLPH) << 32;

	अगर (enable)
		pfflp |= (1ULL << pool);
	अन्यथा
		pfflp &= ~(1ULL << pool);

	IXGBE_WRITE_REG(hw, IXGBE_PFFLPL, (u32)pfflp);
	IXGBE_WRITE_REG(hw, IXGBE_PFFLPH, (u32)(pfflp >> 32));
पूर्ण

/**
 *  ixgbe_setup_fc_backplane_x550em_a - Set up flow control
 *  @hw: poपूर्णांकer to hardware काष्ठाure
 *
 *  Called at init समय to set up flow control.
 **/
अटल s32 ixgbe_setup_fc_backplane_x550em_a(काष्ठा ixgbe_hw *hw)
अणु
	s32 status = 0;
	u32 an_cntl = 0;

	/* Validate the requested mode */
	अगर (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_छोड़ो) अणु
		hw_err(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		वापस IXGBE_ERR_INVALID_LINK_SETTINGS;
	पूर्ण

	अगर (hw->fc.requested_mode == ixgbe_fc_शेष)
		hw->fc.requested_mode = ixgbe_fc_full;

	/* Set up the 1G and 10G flow control advertisement रेजिस्टरs so the
	 * HW will be able to करो FC स्वतःneg once the cable is plugged in.  If
	 * we link at 10G, the 1G advertisement is harmless and vice versa.
	 */
	status = hw->mac.ops.पढ़ो_iosf_sb_reg(hw,
					IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &an_cntl);

	अगर (status) अणु
		hw_dbg(hw, "Auto-Negotiation did not complete\n");
		वापस status;
	पूर्ण

	/* The possible values of fc.requested_mode are:
	 * 0: Flow control is completely disabled
	 * 1: Rx flow control is enabled (we can receive छोड़ो frames,
	 *    but not send छोड़ो frames).
	 * 2: Tx flow control is enabled (we can send छोड़ो frames but
	 *    we करो not support receiving छोड़ो frames).
	 * 3: Both Rx and Tx flow control (symmetric) are enabled.
	 * other: Invalid.
	 */
	चयन (hw->fc.requested_mode) अणु
	हाल ixgbe_fc_none:
		/* Flow control completely disabled by software override. */
		an_cntl &= ~(IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			     IXGBE_KRM_AN_CNTL_1_ASM_PAUSE);
		अवरोध;
	हाल ixgbe_fc_tx_छोड़ो:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		an_cntl |= IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		an_cntl &= ~IXGBE_KRM_AN_CNTL_1_SYM_PAUSE;
		अवरोध;
	हाल ixgbe_fc_rx_छोड़ो:
		/* Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE, as such we fall
		 * through to the fc_full statement.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
	हाल ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		an_cntl |= IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			   IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		अवरोध;
	शेष:
		hw_err(hw, "Flow control param set incorrectly\n");
		वापस IXGBE_ERR_CONFIG;
	पूर्ण

	status = hw->mac.ops.ग_लिखो_iosf_sb_reg(hw,
					IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, an_cntl);

	/* Restart स्वतः-negotiation. */
	status = ixgbe_restart_an_पूर्णांकernal_phy_x550em(hw);

	वापस status;
पूर्ण

/**
 * ixgbe_set_mux - Set mux क्रम port 1 access with CS4227
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @state: set mux अगर 1, clear अगर 0
 */
अटल व्योम ixgbe_set_mux(काष्ठा ixgbe_hw *hw, u8 state)
अणु
	u32 esdp;

	अगर (!hw->bus.lan_id)
		वापस;
	esdp = IXGBE_READ_REG(hw, IXGBE_ESDP);
	अगर (state)
		esdp |= IXGBE_ESDP_SDP1;
	अन्यथा
		esdp &= ~IXGBE_ESDP_SDP1;
	IXGBE_WRITE_REG(hw, IXGBE_ESDP, esdp);
	IXGBE_WRITE_FLUSH(hw);
पूर्ण

/**
 * ixgbe_acquire_swfw_sync_X550em - Acquire SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to acquire
 *
 * Acquires the SWFW semaphore and sets the I2C MUX
 */
अटल s32 ixgbe_acquire_swfw_sync_X550em(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	s32 status;

	status = ixgbe_acquire_swfw_sync_X540(hw, mask);
	अगर (status)
		वापस status;

	अगर (mask & IXGBE_GSSR_I2C_MASK)
		ixgbe_set_mux(hw, 1);

	वापस 0;
पूर्ण

/**
 * ixgbe_release_swfw_sync_X550em - Release SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to release
 *
 * Releases the SWFW semaphore and sets the I2C MUX
 */
अटल व्योम ixgbe_release_swfw_sync_X550em(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	अगर (mask & IXGBE_GSSR_I2C_MASK)
		ixgbe_set_mux(hw, 0);

	ixgbe_release_swfw_sync_X540(hw, mask);
पूर्ण

/**
 * ixgbe_acquire_swfw_sync_x550em_a - Acquire SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to acquire
 *
 * Acquires the SWFW semaphore and get the shared PHY token as needed
 */
अटल s32 ixgbe_acquire_swfw_sync_x550em_a(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 hmask = mask & ~IXGBE_GSSR_TOKEN_SM;
	पूर्णांक retries = FW_PHY_TOKEN_RETRIES;
	s32 status;

	जबतक (--retries) अणु
		status = 0;
		अगर (hmask)
			status = ixgbe_acquire_swfw_sync_X540(hw, hmask);
		अगर (status)
			वापस status;
		अगर (!(mask & IXGBE_GSSR_TOKEN_SM))
			वापस 0;

		status = ixgbe_get_phy_token(hw);
		अगर (!status)
			वापस 0;
		अगर (hmask)
			ixgbe_release_swfw_sync_X540(hw, hmask);
		अगर (status != IXGBE_ERR_TOKEN_RETRY)
			वापस status;
		msleep(FW_PHY_TOKEN_DELAY);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ixgbe_release_swfw_sync_x550em_a - Release SWFW semaphore
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @mask: Mask to specअगरy which semaphore to release
 *
 * Release the SWFW semaphore and माला_दो the shared PHY token as needed
 */
अटल व्योम ixgbe_release_swfw_sync_x550em_a(काष्ठा ixgbe_hw *hw, u32 mask)
अणु
	u32 hmask = mask & ~IXGBE_GSSR_TOKEN_SM;

	अगर (mask & IXGBE_GSSR_TOKEN_SM)
		ixgbe_put_phy_token(hw);

	अगर (hmask)
		ixgbe_release_swfw_sync_X540(hw, hmask);
पूर्ण

/**
 * ixgbe_पढ़ो_phy_reg_x550a - Reads specअगरied PHY रेजिस्टर
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg_addr: 32 bit address of PHY रेजिस्टर to पढ़ो
 * @device_type: 5 bit device type
 * @phy_data: Poपूर्णांकer to पढ़ो data from PHY रेजिस्टर
 *
 * Reads a value from a specअगरied PHY रेजिस्टर using the SWFW lock and PHY
 * Token. The PHY Token is needed since the MDIO is shared between to MAC
 * instances.
 */
अटल s32 ixgbe_पढ़ो_phy_reg_x550a(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				    u32 device_type, u16 *phy_data)
अणु
	u32 mask = hw->phy.phy_semaphore_mask | IXGBE_GSSR_TOKEN_SM;
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, mask))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = hw->phy.ops.पढ़ो_reg_mdi(hw, reg_addr, device_type, phy_data);

	hw->mac.ops.release_swfw_sync(hw, mask);

	वापस status;
पूर्ण

/**
 * ixgbe_ग_लिखो_phy_reg_x550a - Writes specअगरied PHY रेजिस्टर
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @reg_addr: 32 bit PHY रेजिस्टर to ग_लिखो
 * @device_type: 5 bit device type
 * @phy_data: Data to ग_लिखो to the PHY रेजिस्टर
 *
 * Writes a value to specअगरied PHY रेजिस्टर using the SWFW lock and PHY Token.
 * The PHY Token is needed since the MDIO is shared between to MAC instances.
 */
अटल s32 ixgbe_ग_लिखो_phy_reg_x550a(काष्ठा ixgbe_hw *hw, u32 reg_addr,
				     u32 device_type, u16 phy_data)
अणु
	u32 mask = hw->phy.phy_semaphore_mask | IXGBE_GSSR_TOKEN_SM;
	s32 status;

	अगर (hw->mac.ops.acquire_swfw_sync(hw, mask))
		वापस IXGBE_ERR_SWFW_SYNC;

	status = ixgbe_ग_लिखो_phy_reg_mdi(hw, reg_addr, device_type, phy_data);
	hw->mac.ops.release_swfw_sync(hw, mask);

	वापस status;
पूर्ण

#घोषणा X550_COMMON_MAC \
	.init_hw			= &ixgbe_init_hw_generic, \
	.start_hw			= &ixgbe_start_hw_X540, \
	.clear_hw_cntrs			= &ixgbe_clear_hw_cntrs_generic, \
	.enable_rx_dma			= &ixgbe_enable_rx_dma_generic, \
	.get_mac_addr			= &ixgbe_get_mac_addr_generic, \
	.get_device_caps		= &ixgbe_get_device_caps_generic, \
	.stop_adapter			= &ixgbe_stop_adapter_generic, \
	.set_lan_id			= &ixgbe_set_lan_id_multi_port_pcie, \
	.पढ़ो_analog_reg8		= शून्य, \
	.ग_लिखो_analog_reg8		= शून्य, \
	.set_rxpba			= &ixgbe_set_rxpba_generic, \
	.check_link			= &ixgbe_check_mac_link_generic, \
	.blink_led_start		= &ixgbe_blink_led_start_X540, \
	.blink_led_stop			= &ixgbe_blink_led_stop_X540, \
	.set_rar			= &ixgbe_set_rar_generic, \
	.clear_rar			= &ixgbe_clear_rar_generic, \
	.set_vmdq			= &ixgbe_set_vmdq_generic, \
	.set_vmdq_san_mac		= &ixgbe_set_vmdq_san_mac_generic, \
	.clear_vmdq			= &ixgbe_clear_vmdq_generic, \
	.init_rx_addrs			= &ixgbe_init_rx_addrs_generic, \
	.update_mc_addr_list		= &ixgbe_update_mc_addr_list_generic, \
	.enable_mc			= &ixgbe_enable_mc_generic, \
	.disable_mc			= &ixgbe_disable_mc_generic, \
	.clear_vfta			= &ixgbe_clear_vfta_generic, \
	.set_vfta			= &ixgbe_set_vfta_generic, \
	.fc_enable			= &ixgbe_fc_enable_generic, \
	.set_fw_drv_ver			= &ixgbe_set_fw_drv_ver_x550, \
	.init_uta_tables		= &ixgbe_init_uta_tables_generic, \
	.set_mac_anti_spoofing		= &ixgbe_set_mac_anti_spoofing, \
	.set_vlan_anti_spoofing		= &ixgbe_set_vlan_anti_spoofing, \
	.set_source_address_pruning	= \
				&ixgbe_set_source_address_pruning_X550, \
	.set_ethertype_anti_spoofing	= \
				&ixgbe_set_ethertype_anti_spoofing_X550, \
	.disable_rx_buff		= &ixgbe_disable_rx_buff_generic, \
	.enable_rx_buff			= &ixgbe_enable_rx_buff_generic, \
	.get_thermal_sensor_data	= शून्य, \
	.init_thermal_sensor_thresh	= शून्य, \
	.fw_recovery_mode		= &ixgbe_fw_recovery_mode_X550, \
	.enable_rx			= &ixgbe_enable_rx_generic, \
	.disable_rx			= &ixgbe_disable_rx_x550, \

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_X550 = अणु
	X550_COMMON_MAC
	.led_on			= ixgbe_led_on_generic,
	.led_off		= ixgbe_led_off_generic,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.reset_hw		= &ixgbe_reset_hw_X540,
	.get_media_type		= &ixgbe_get_media_type_X540,
	.get_san_mac_addr	= &ixgbe_get_san_mac_addr_generic,
	.get_wwn_prefix		= &ixgbe_get_wwn_prefix_generic,
	.setup_link		= &ixgbe_setup_mac_link_X540,
	.get_link_capabilities	= &ixgbe_get_copper_link_capabilities_generic,
	.get_bus_info		= &ixgbe_get_bus_info_generic,
	.setup_sfp		= शून्य,
	.acquire_swfw_sync	= &ixgbe_acquire_swfw_sync_X540,
	.release_swfw_sync	= &ixgbe_release_swfw_sync_X540,
	.init_swfw_sync		= &ixgbe_init_swfw_sync_X540,
	.prot_स्वतःc_पढ़ो	= prot_स्वतःc_पढ़ो_generic,
	.prot_स्वतःc_ग_लिखो	= prot_स्वतःc_ग_लिखो_generic,
	.setup_fc		= ixgbe_setup_fc_generic,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_X550EM_x = अणु
	X550_COMMON_MAC
	.led_on			= ixgbe_led_on_t_x550em,
	.led_off		= ixgbe_led_off_t_x550em,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.reset_hw		= &ixgbe_reset_hw_X550em,
	.get_media_type		= &ixgbe_get_media_type_X550em,
	.get_san_mac_addr	= शून्य,
	.get_wwn_prefix		= शून्य,
	.setup_link		= &ixgbe_setup_mac_link_X540,
	.get_link_capabilities	= &ixgbe_get_link_capabilities_X550em,
	.get_bus_info		= &ixgbe_get_bus_info_X550em,
	.setup_sfp		= ixgbe_setup_sfp_modules_X550em,
	.acquire_swfw_sync	= &ixgbe_acquire_swfw_sync_X550em,
	.release_swfw_sync	= &ixgbe_release_swfw_sync_X550em,
	.init_swfw_sync		= &ixgbe_init_swfw_sync_X540,
	.setup_fc		= शून्य, /* defined later */
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.पढ़ो_iosf_sb_reg	= ixgbe_पढ़ो_iosf_sb_reg_x550,
	.ग_लिखो_iosf_sb_reg	= ixgbe_ग_लिखो_iosf_sb_reg_x550,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_X550EM_x_fw = अणु
	X550_COMMON_MAC
	.led_on			= शून्य,
	.led_off		= शून्य,
	.init_led_link_act	= शून्य,
	.reset_hw		= &ixgbe_reset_hw_X550em,
	.get_media_type		= &ixgbe_get_media_type_X550em,
	.get_san_mac_addr	= शून्य,
	.get_wwn_prefix		= शून्य,
	.setup_link		= &ixgbe_setup_mac_link_X540,
	.get_link_capabilities	= &ixgbe_get_link_capabilities_X550em,
	.get_bus_info		= &ixgbe_get_bus_info_X550em,
	.setup_sfp		= ixgbe_setup_sfp_modules_X550em,
	.acquire_swfw_sync	= &ixgbe_acquire_swfw_sync_X550em,
	.release_swfw_sync	= &ixgbe_release_swfw_sync_X550em,
	.init_swfw_sync		= &ixgbe_init_swfw_sync_X540,
	.setup_fc		= शून्य,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.पढ़ो_iosf_sb_reg	= ixgbe_पढ़ो_iosf_sb_reg_x550,
	.ग_लिखो_iosf_sb_reg	= ixgbe_ग_लिखो_iosf_sb_reg_x550,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_x550em_a = अणु
	X550_COMMON_MAC
	.led_on			= ixgbe_led_on_t_x550em,
	.led_off		= ixgbe_led_off_t_x550em,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.reset_hw		= ixgbe_reset_hw_X550em,
	.get_media_type		= ixgbe_get_media_type_X550em,
	.get_san_mac_addr	= शून्य,
	.get_wwn_prefix		= शून्य,
	.setup_link		= &ixgbe_setup_mac_link_X540,
	.get_link_capabilities	= ixgbe_get_link_capabilities_X550em,
	.get_bus_info		= ixgbe_get_bus_info_X550em,
	.setup_sfp		= ixgbe_setup_sfp_modules_X550em,
	.acquire_swfw_sync	= ixgbe_acquire_swfw_sync_x550em_a,
	.release_swfw_sync	= ixgbe_release_swfw_sync_x550em_a,
	.setup_fc		= ixgbe_setup_fc_x550em,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.पढ़ो_iosf_sb_reg	= ixgbe_पढ़ो_iosf_sb_reg_x550a,
	.ग_लिखो_iosf_sb_reg	= ixgbe_ग_लिखो_iosf_sb_reg_x550a,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_mac_operations mac_ops_x550em_a_fw = अणु
	X550_COMMON_MAC
	.led_on			= ixgbe_led_on_generic,
	.led_off		= ixgbe_led_off_generic,
	.init_led_link_act	= ixgbe_init_led_link_act_generic,
	.reset_hw		= ixgbe_reset_hw_X550em,
	.get_media_type		= ixgbe_get_media_type_X550em,
	.get_san_mac_addr	= शून्य,
	.get_wwn_prefix		= शून्य,
	.setup_link		= शून्य, /* defined later */
	.get_link_capabilities	= ixgbe_get_link_capabilities_X550em,
	.get_bus_info		= ixgbe_get_bus_info_X550em,
	.setup_sfp		= ixgbe_setup_sfp_modules_X550em,
	.acquire_swfw_sync	= ixgbe_acquire_swfw_sync_x550em_a,
	.release_swfw_sync	= ixgbe_release_swfw_sync_x550em_a,
	.setup_fc		= ixgbe_setup_fc_x550em,
	.fc_स्वतःneg		= ixgbe_fc_स्वतःneg,
	.पढ़ो_iosf_sb_reg	= ixgbe_पढ़ो_iosf_sb_reg_x550a,
	.ग_लिखो_iosf_sb_reg	= ixgbe_ग_लिखो_iosf_sb_reg_x550a,
पूर्ण;

#घोषणा X550_COMMON_EEP \
	.पढ़ो			= &ixgbe_पढ़ो_ee_hostअगर_X550, \
	.पढ़ो_buffer		= &ixgbe_पढ़ो_ee_hostअगर_buffer_X550, \
	.ग_लिखो			= &ixgbe_ग_लिखो_ee_hostअगर_X550, \
	.ग_लिखो_buffer		= &ixgbe_ग_लिखो_ee_hostअगर_buffer_X550, \
	.validate_checksum	= &ixgbe_validate_eeprom_checksum_X550, \
	.update_checksum	= &ixgbe_update_eeprom_checksum_X550, \
	.calc_checksum		= &ixgbe_calc_eeprom_checksum_X550, \

अटल स्थिर काष्ठा ixgbe_eeprom_operations eeprom_ops_X550 = अणु
	X550_COMMON_EEP
	.init_params		= &ixgbe_init_eeprom_params_X550,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_eeprom_operations eeprom_ops_X550EM_x = अणु
	X550_COMMON_EEP
	.init_params		= &ixgbe_init_eeprom_params_X540,
पूर्ण;

#घोषणा X550_COMMON_PHY	\
	.identअगरy_sfp		= &ixgbe_identअगरy_module_generic, \
	.reset			= शून्य, \
	.setup_link_speed	= &ixgbe_setup_phy_link_speed_generic, \
	.पढ़ो_i2c_byte		= &ixgbe_पढ़ो_i2c_byte_generic, \
	.ग_लिखो_i2c_byte		= &ixgbe_ग_लिखो_i2c_byte_generic, \
	.पढ़ो_i2c_sff8472	= &ixgbe_पढ़ो_i2c_sff8472_generic, \
	.पढ़ो_i2c_eeprom	= &ixgbe_पढ़ो_i2c_eeprom_generic, \
	.ग_लिखो_i2c_eeprom	= &ixgbe_ग_लिखो_i2c_eeprom_generic, \
	.setup_link		= &ixgbe_setup_phy_link_generic, \
	.set_phy_घातer		= शून्य,

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_X550 = अणु
	X550_COMMON_PHY
	.check_overtemp		= &ixgbe_tn_check_overtemp,
	.init			= शून्य,
	.identअगरy		= &ixgbe_identअगरy_phy_generic,
	.पढ़ो_reg		= &ixgbe_पढ़ो_phy_reg_generic,
	.ग_लिखो_reg		= &ixgbe_ग_लिखो_phy_reg_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_X550EM_x = अणु
	X550_COMMON_PHY
	.check_overtemp		= &ixgbe_tn_check_overtemp,
	.init			= &ixgbe_init_phy_ops_X550em,
	.identअगरy		= &ixgbe_identअगरy_phy_x550em,
	.पढ़ो_reg		= &ixgbe_पढ़ो_phy_reg_generic,
	.ग_लिखो_reg		= &ixgbe_ग_लिखो_phy_reg_generic,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_x550em_x_fw = अणु
	X550_COMMON_PHY
	.check_overtemp		= शून्य,
	.init			= ixgbe_init_phy_ops_X550em,
	.identअगरy		= ixgbe_identअगरy_phy_x550em,
	.पढ़ो_reg		= शून्य,
	.ग_लिखो_reg		= शून्य,
	.पढ़ो_reg_mdi		= शून्य,
	.ग_लिखो_reg_mdi		= शून्य,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_x550em_a = अणु
	X550_COMMON_PHY
	.check_overtemp		= &ixgbe_tn_check_overtemp,
	.init			= &ixgbe_init_phy_ops_X550em,
	.identअगरy		= &ixgbe_identअगरy_phy_x550em,
	.पढ़ो_reg		= &ixgbe_पढ़ो_phy_reg_x550a,
	.ग_लिखो_reg		= &ixgbe_ग_लिखो_phy_reg_x550a,
	.पढ़ो_reg_mdi		= &ixgbe_पढ़ो_phy_reg_mdi,
	.ग_लिखो_reg_mdi		= &ixgbe_ग_लिखो_phy_reg_mdi,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_phy_operations phy_ops_x550em_a_fw = अणु
	X550_COMMON_PHY
	.check_overtemp		= ixgbe_check_overtemp_fw,
	.init			= ixgbe_init_phy_ops_X550em,
	.identअगरy		= ixgbe_identअगरy_phy_fw,
	.पढ़ो_reg		= शून्य,
	.ग_लिखो_reg		= शून्य,
	.पढ़ो_reg_mdi		= शून्य,
	.ग_लिखो_reg_mdi		= शून्य,
पूर्ण;

अटल स्थिर काष्ठा ixgbe_link_operations link_ops_x550em_x = अणु
	.पढ़ो_link		= &ixgbe_पढ़ो_i2c_combined_generic,
	.पढ़ो_link_unlocked	= &ixgbe_पढ़ो_i2c_combined_generic_unlocked,
	.ग_लिखो_link		= &ixgbe_ग_लिखो_i2c_combined_generic,
	.ग_लिखो_link_unlocked	= &ixgbe_ग_लिखो_i2c_combined_generic_unlocked,
पूर्ण;

अटल स्थिर u32 ixgbe_mvals_X550[IXGBE_MVALS_IDX_LIMIT] = अणु
	IXGBE_MVALS_INIT(X550)
पूर्ण;

अटल स्थिर u32 ixgbe_mvals_X550EM_x[IXGBE_MVALS_IDX_LIMIT] = अणु
	IXGBE_MVALS_INIT(X550EM_x)
पूर्ण;

अटल स्थिर u32 ixgbe_mvals_x550em_a[IXGBE_MVALS_IDX_LIMIT] = अणु
	IXGBE_MVALS_INIT(X550EM_a)
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_X550_info = अणु
	.mac			= ixgbe_mac_X550,
	.get_invariants		= &ixgbe_get_invariants_X540,
	.mac_ops		= &mac_ops_X550,
	.eeprom_ops		= &eeprom_ops_X550,
	.phy_ops		= &phy_ops_X550,
	.mbx_ops		= &mbx_ops_generic,
	.mvals			= ixgbe_mvals_X550,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_X550EM_x_info = अणु
	.mac			= ixgbe_mac_X550EM_x,
	.get_invariants		= &ixgbe_get_invariants_X550_x,
	.mac_ops		= &mac_ops_X550EM_x,
	.eeprom_ops		= &eeprom_ops_X550EM_x,
	.phy_ops		= &phy_ops_X550EM_x,
	.mbx_ops		= &mbx_ops_generic,
	.mvals			= ixgbe_mvals_X550EM_x,
	.link_ops		= &link_ops_x550em_x,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_x550em_x_fw_info = अणु
	.mac			= ixgbe_mac_X550EM_x,
	.get_invariants		= ixgbe_get_invariants_X550_x_fw,
	.mac_ops		= &mac_ops_X550EM_x_fw,
	.eeprom_ops		= &eeprom_ops_X550EM_x,
	.phy_ops		= &phy_ops_x550em_x_fw,
	.mbx_ops		= &mbx_ops_generic,
	.mvals			= ixgbe_mvals_X550EM_x,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_x550em_a_info = अणु
	.mac			= ixgbe_mac_x550em_a,
	.get_invariants		= &ixgbe_get_invariants_X550_a,
	.mac_ops		= &mac_ops_x550em_a,
	.eeprom_ops		= &eeprom_ops_X550EM_x,
	.phy_ops		= &phy_ops_x550em_a,
	.mbx_ops		= &mbx_ops_generic,
	.mvals			= ixgbe_mvals_x550em_a,
पूर्ण;

स्थिर काष्ठा ixgbe_info ixgbe_x550em_a_fw_info = अणु
	.mac			= ixgbe_mac_x550em_a,
	.get_invariants		= ixgbe_get_invariants_X550_a_fw,
	.mac_ops		= &mac_ops_x550em_a_fw,
	.eeprom_ops		= &eeprom_ops_X550EM_x,
	.phy_ops		= &phy_ops_x550em_a_fw,
	.mbx_ops		= &mbx_ops_generic,
	.mvals			= ixgbe_mvals_x550em_a,
पूर्ण;
