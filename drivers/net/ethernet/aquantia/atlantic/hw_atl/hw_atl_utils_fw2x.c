<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File hw_atl_utils_fw2x.c: Definition of firmware 2.x functions क्रम
 * Atlantic hardware असलtraction layer.
 */

#समावेश "../aq_hw.h"
#समावेश "../aq_hw_utils.h"
#समावेश "../aq_pci_func.h"
#समावेश "../aq_ring.h"
#समावेश "../aq_vec.h"
#समावेश "../aq_nic.h"
#समावेश "hw_atl_utils.h"
#समावेश "hw_atl_llh.h"

#घोषणा HW_ATL_FW2X_MPI_LED_ADDR         0x31c
#घोषणा HW_ATL_FW2X_MPI_RPC_ADDR         0x334

#घोषणा HW_ATL_FW2X_MPI_MBOX_ADDR        0x360
#घोषणा HW_ATL_FW2X_MPI_EFUSE_ADDR       0x364
#घोषणा HW_ATL_FW2X_MPI_CONTROL_ADDR     0x368
#घोषणा HW_ATL_FW2X_MPI_CONTROL2_ADDR    0x36C
#घोषणा HW_ATL_FW2X_MPI_STATE_ADDR       0x370
#घोषणा HW_ATL_FW2X_MPI_STATE2_ADDR      0x374

#घोषणा HW_ATL_FW3X_EXT_CONTROL_ADDR     0x378
#घोषणा HW_ATL_FW3X_EXT_STATE_ADDR       0x37c

#घोषणा HW_ATL_FW3X_PTP_ADJ_LSW_ADDR	 0x50a0
#घोषणा HW_ATL_FW3X_PTP_ADJ_MSW_ADDR	 0x50a4

#घोषणा HW_ATL_FW2X_CAP_PAUSE            BIT(CAPS_HI_PAUSE)
#घोषणा HW_ATL_FW2X_CAP_ASYM_PAUSE       BIT(CAPS_HI_ASYMMETRIC_PAUSE)
#घोषणा HW_ATL_FW2X_CAP_SLEEP_PROXY      BIT(CAPS_HI_SLEEP_PROXY)
#घोषणा HW_ATL_FW2X_CAP_WOL              BIT(CAPS_HI_WOL)

#घोषणा HW_ATL_FW2X_CTRL_WAKE_ON_LINK     BIT(CTRL_WAKE_ON_LINK)
#घोषणा HW_ATL_FW2X_CTRL_SLEEP_PROXY      BIT(CTRL_SLEEP_PROXY)
#घोषणा HW_ATL_FW2X_CTRL_WOL              BIT(CTRL_WOL)
#घोषणा HW_ATL_FW2X_CTRL_LINK_DROP        BIT(CTRL_LINK_DROP)
#घोषणा HW_ATL_FW2X_CTRL_PAUSE            BIT(CTRL_PAUSE)
#घोषणा HW_ATL_FW2X_CTRL_TEMPERATURE      BIT(CTRL_TEMPERATURE)
#घोषणा HW_ATL_FW2X_CTRL_ASYMMETRIC_PAUSE BIT(CTRL_ASYMMETRIC_PAUSE)
#घोषणा HW_ATL_FW2X_CTRL_INT_LOOPBACK     BIT(CTRL_INT_LOOPBACK)
#घोषणा HW_ATL_FW2X_CTRL_EXT_LOOPBACK     BIT(CTRL_EXT_LOOPBACK)
#घोषणा HW_ATL_FW2X_CTRL_DOWNSHIFT        BIT(CTRL_DOWNSHIFT)
#घोषणा HW_ATL_FW2X_CTRL_FORCE_RECONNECT  BIT(CTRL_FORCE_RECONNECT)

#घोषणा HW_ATL_FW2X_CAP_EEE_1G_MASK      BIT(CAPS_HI_1000BASET_FD_EEE)
#घोषणा HW_ATL_FW2X_CAP_EEE_2G5_MASK     BIT(CAPS_HI_2P5GBASET_FD_EEE)
#घोषणा HW_ATL_FW2X_CAP_EEE_5G_MASK      BIT(CAPS_HI_5GBASET_FD_EEE)
#घोषणा HW_ATL_FW2X_CAP_EEE_10G_MASK     BIT(CAPS_HI_10GBASET_FD_EEE)

#घोषणा HW_ATL_FW2X_CAP_MACSEC           BIT(CAPS_LO_MACSEC)

#घोषणा HAL_ATLANTIC_WOL_FILTERS_COUNT   8
#घोषणा HAL_ATLANTIC_UTILS_FW2X_MSG_WOL  0x0E

#घोषणा HW_ATL_FW_VER_LED                0x03010026U
#घोषणा HW_ATL_FW_VER_MEDIA_CONTROL      0x0301005aU

काष्ठा __packed fw2x_msg_wol_pattern अणु
	u8 mask[16];
	u32 crc;
पूर्ण;

काष्ठा __packed fw2x_msg_wol अणु
	u32 msg_id;
	u8 hw_addr[ETH_ALEN];
	u8 magic_packet_enabled;
	u8 filter_count;
	काष्ठा fw2x_msg_wol_pattern filter[HAL_ATLANTIC_WOL_FILTERS_COUNT];
	u8 link_up_enabled;
	u8 link_करोwn_enabled;
	u16 reserved;
	u32 link_up_समयout;
	u32 link_करोwn_समयout;
पूर्ण;

अटल पूर्णांक aq_fw2x_set_link_speed(काष्ठा aq_hw_s *self, u32 speed);
अटल पूर्णांक aq_fw2x_set_state(काष्ठा aq_hw_s *self,
			     क्रमागत hal_atl_utils_fw_state_e state);

अटल u32 aq_fw2x_mbox_get(काष्ठा aq_hw_s *self);
अटल u32 aq_fw2x_rpc_get(काष्ठा aq_hw_s *self);
अटल पूर्णांक aq_fw2x_settings_get(काष्ठा aq_hw_s *self, u32 *addr);
अटल u32 aq_fw2x_state_get(काष्ठा aq_hw_s *self);
अटल u32 aq_fw2x_state2_get(काष्ठा aq_hw_s *self);

अटल पूर्णांक aq_fw2x_init(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err = 0;

	/* check 10 बार by 1ms */
	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_mbox_get,
					self, self->mbox_addr,
					self->mbox_addr != 0U,
					1000U, 10000U);

	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_rpc_get,
					self, self->rpc_addr,
					self->rpc_addr != 0U,
					1000U, 100000U);

	err = aq_fw2x_settings_get(self, &self->settings_addr);

	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_deinit(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err = aq_fw2x_set_link_speed(self, 0);

	अगर (!err)
		err = aq_fw2x_set_state(self, MPI_DEINIT);

	वापस err;
पूर्ण

अटल क्रमागत hw_atl_fw2x_rate link_speed_mask_2fw2x_ratemask(u32 speed)
अणु
	क्रमागत hw_atl_fw2x_rate rate = 0;

	अगर (speed & AQ_NIC_RATE_10G)
		rate |= FW2X_RATE_10G;

	अगर (speed & AQ_NIC_RATE_5G)
		rate |= FW2X_RATE_5G;

	अगर (speed & AQ_NIC_RATE_5GSR)
		rate |= FW2X_RATE_5G;

	अगर (speed & AQ_NIC_RATE_2G5)
		rate |= FW2X_RATE_2G5;

	अगर (speed & AQ_NIC_RATE_1G)
		rate |= FW2X_RATE_1G;

	अगर (speed & AQ_NIC_RATE_100M)
		rate |= FW2X_RATE_100M;

	वापस rate;
पूर्ण

अटल u32 fw2x_to_eee_mask(u32 speed)
अणु
	u32 rate = 0;

	अगर (speed & HW_ATL_FW2X_CAP_EEE_10G_MASK)
		rate |= AQ_NIC_RATE_EEE_10G;
	अगर (speed & HW_ATL_FW2X_CAP_EEE_5G_MASK)
		rate |= AQ_NIC_RATE_EEE_5G;
	अगर (speed & HW_ATL_FW2X_CAP_EEE_2G5_MASK)
		rate |= AQ_NIC_RATE_EEE_2G5;
	अगर (speed & HW_ATL_FW2X_CAP_EEE_1G_MASK)
		rate |= AQ_NIC_RATE_EEE_1G;

	वापस rate;
पूर्ण

अटल u32 eee_mask_to_fw2x(u32 speed)
अणु
	u32 rate = 0;

	अगर (speed & AQ_NIC_RATE_EEE_10G)
		rate |= HW_ATL_FW2X_CAP_EEE_10G_MASK;
	अगर (speed & AQ_NIC_RATE_EEE_5G)
		rate |= HW_ATL_FW2X_CAP_EEE_5G_MASK;
	अगर (speed & AQ_NIC_RATE_EEE_2G5)
		rate |= HW_ATL_FW2X_CAP_EEE_2G5_MASK;
	अगर (speed & AQ_NIC_RATE_EEE_1G)
		rate |= HW_ATL_FW2X_CAP_EEE_1G_MASK;

	वापस rate;
पूर्ण

अटल पूर्णांक aq_fw2x_set_link_speed(काष्ठा aq_hw_s *self, u32 speed)
अणु
	u32 val = link_speed_mask_2fw2x_ratemask(speed);

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL_ADDR, val);

	वापस 0;
पूर्ण

अटल व्योम aq_fw2x_upd_flow_control_bits(काष्ठा aq_hw_s *self,
					  u32 *mpi_state, u32 fc)
अणु
	*mpi_state &= ~(HW_ATL_FW2X_CTRL_PAUSE |
			HW_ATL_FW2X_CTRL_ASYMMETRIC_PAUSE);

	चयन (fc) अणु
	/* There is not explicit mode of RX only छोड़ो frames,
	 * thus, we join this mode with FC full.
	 * FC full is either Rx, either Tx, or both.
	 */
	हाल AQ_NIC_FC_FULL:
	हाल AQ_NIC_FC_RX:
		*mpi_state |= HW_ATL_FW2X_CTRL_PAUSE |
			      HW_ATL_FW2X_CTRL_ASYMMETRIC_PAUSE;
		अवरोध;
	हाल AQ_NIC_FC_TX:
		*mpi_state |= HW_ATL_FW2X_CTRL_ASYMMETRIC_PAUSE;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम aq_fw2x_upd_eee_rate_bits(काष्ठा aq_hw_s *self, u32 *mpi_opts,
				      u32 eee_speeds)
अणु
	*mpi_opts &= ~(HW_ATL_FW2X_CAP_EEE_1G_MASK |
		       HW_ATL_FW2X_CAP_EEE_2G5_MASK |
		       HW_ATL_FW2X_CAP_EEE_5G_MASK |
		       HW_ATL_FW2X_CAP_EEE_10G_MASK);

	*mpi_opts |= eee_mask_to_fw2x(eee_speeds);
पूर्ण

अटल पूर्णांक aq_fw2x_set_state(काष्ठा aq_hw_s *self,
			     क्रमागत hal_atl_utils_fw_state_e state)
अणु
	u32 mpi_state = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	काष्ठा aq_nic_cfg_s *cfg = self->aq_nic_cfg;

	चयन (state) अणु
	हाल MPI_INIT:
		mpi_state &= ~BIT(CAPS_HI_LINK_DROP);
		aq_fw2x_upd_eee_rate_bits(self, &mpi_state, cfg->eee_speeds);
		aq_fw2x_upd_flow_control_bits(self, &mpi_state,
					      self->aq_nic_cfg->fc.req);
		अवरोध;
	हाल MPI_DEINIT:
		mpi_state |= BIT(CAPS_HI_LINK_DROP);
		अवरोध;
	हाल MPI_RESET:
	हाल MPI_POWER:
		/* No actions */
		अवरोध;
	पूर्ण
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_state);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_update_link_status(काष्ठा aq_hw_s *self)
अणु
	काष्ठा aq_hw_link_status_s *link_status = &self->aq_link_status;
	u32 mpi_state;
	u32 speed;

	mpi_state = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_STATE_ADDR);
	speed = mpi_state & (FW2X_RATE_100M | FW2X_RATE_1G |
			     FW2X_RATE_2G5 | FW2X_RATE_5G |
			     FW2X_RATE_10G);

	अगर (speed) अणु
		अगर (speed & FW2X_RATE_10G)
			link_status->mbps = 10000;
		अन्यथा अगर (speed & FW2X_RATE_5G)
			link_status->mbps = 5000;
		अन्यथा अगर (speed & FW2X_RATE_2G5)
			link_status->mbps = 2500;
		अन्यथा अगर (speed & FW2X_RATE_1G)
			link_status->mbps = 1000;
		अन्यथा अगर (speed & FW2X_RATE_100M)
			link_status->mbps = 100;
		अन्यथा
			link_status->mbps = 10000;
	पूर्ण अन्यथा अणु
		link_status->mbps = 0;
	पूर्ण
	link_status->full_duplex = true;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_get_mac_permanent(काष्ठा aq_hw_s *self, u8 *mac)
अणु
	u32 efuse_addr = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_EFUSE_ADDR);
	u32 mac_addr[2] = अणु 0 पूर्ण;
	पूर्णांक err = 0;

	अगर (efuse_addr != 0) अणु
		err = hw_atl_utils_fw_करोwnld_dwords(self,
						    efuse_addr + (40U * 4U),
						    mac_addr,
						    ARRAY_SIZE(mac_addr));
		अगर (err)
			वापस err;
		mac_addr[0] = __swab32(mac_addr[0]);
		mac_addr[1] = __swab32(mac_addr[1]);
	पूर्ण

	ether_addr_copy(mac, (u8 *)mac_addr);

	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_update_stats(काष्ठा aq_hw_s *self)
अणु
	u32 mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	u32 orig_stats_val = mpi_opts & BIT(CAPS_HI_STATISTICS);
	u32 stats_val;
	पूर्णांक err = 0;

	/* Toggle statistics bit क्रम FW to update */
	mpi_opts = mpi_opts ^ BIT(CAPS_HI_STATISTICS);
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	/* Wait FW to report back */
	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_state2_get,
					self, stats_val,
					orig_stats_val != (stats_val &
					BIT(CAPS_HI_STATISTICS)),
					1U, 10000U);
	अगर (err)
		वापस err;

	वापस hw_atl_utils_update_stats(self);
पूर्ण

अटल पूर्णांक aq_fw2x_get_phy_temp(काष्ठा aq_hw_s *self, पूर्णांक *temp)
अणु
	u32 mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	u32 temp_val = mpi_opts & HW_ATL_FW2X_CTRL_TEMPERATURE;
	u32 phy_temp_offset;
	u32 temp_res;
	पूर्णांक err = 0;
	u32 val;

	phy_temp_offset = self->mbox_addr + दुरत्व(काष्ठा hw_atl_utils_mbox,
						     info.phy_temperature);

	/* Toggle statistics bit क्रम FW to 0x36C.18 (CTRL_TEMPERATURE) */
	mpi_opts = mpi_opts ^ HW_ATL_FW2X_CTRL_TEMPERATURE;
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);
	/* Wait FW to report back */
	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_state2_get, self, val,
					temp_val !=
					(val & HW_ATL_FW2X_CTRL_TEMPERATURE),
					1U, 10000U);
	err = hw_atl_utils_fw_करोwnld_dwords(self, phy_temp_offset,
					    &temp_res, 1);

	अगर (err)
		वापस err;

	/* Convert PHY temperature from 1/256 degree Celsius
	 * to 1/1000 degree Celsius.
	 */
	*temp = (पूर्णांक16_t)(temp_res & 0xFFFF) * 1000 / 256;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_set_wol(काष्ठा aq_hw_s *self, u8 *mac)
अणु
	काष्ठा hw_atl_utils_fw_rpc *rpc = शून्य;
	काष्ठा offload_info *info = शून्य;
	u32 wol_bits = 0;
	u32 rpc_size;
	पूर्णांक err = 0;
	u32 val;

	अगर (self->aq_nic_cfg->wol & WAKE_PHY) अणु
		aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR,
				HW_ATL_FW2X_CTRL_LINK_DROP);
		पढ़ोx_poll_समयout_atomic(aq_fw2x_state2_get, self, val,
					  (val &
					   HW_ATL_FW2X_CTRL_LINK_DROP) != 0,
					  1000, 100000);
		wol_bits |= HW_ATL_FW2X_CTRL_WAKE_ON_LINK;
	पूर्ण

	अगर (self->aq_nic_cfg->wol & WAKE_MAGIC) अणु
		wol_bits |= HW_ATL_FW2X_CTRL_SLEEP_PROXY |
			    HW_ATL_FW2X_CTRL_WOL;

		err = hw_atl_utils_fw_rpc_रुको(self, &rpc);
		अगर (err < 0)
			जाओ err_निकास;

		rpc_size = माप(*info) +
			   दुरत्व(काष्ठा hw_atl_utils_fw_rpc, fw2x_offloads);
		स_रखो(rpc, 0, rpc_size);
		info = &rpc->fw2x_offloads;
		स_नकल(info->mac_addr, mac, ETH_ALEN);
		info->len = माप(*info);

		err = hw_atl_utils_fw_rpc_call(self, rpc_size);
		अगर (err < 0)
			जाओ err_निकास;
	पूर्ण

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, wol_bits);

err_निकास:
	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_set_घातer(काष्ठा aq_hw_s *self, अचिन्हित पूर्णांक घातer_state,
			     u8 *mac)
अणु
	पूर्णांक err = 0;

	अगर (self->aq_nic_cfg->wol)
		err = aq_fw2x_set_wol(self, mac);

	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_send_fw_request(काष्ठा aq_hw_s *self,
				   स्थिर काष्ठा hw_fw_request_अगरace *fw_req,
				   माप_प्रकार size)
अणु
	u32 ctrl2, orig_ctrl2;
	u32 dword_cnt;
	पूर्णांक err = 0;
	u32 val;

	/* Write data to drvIface Mailbox */
	dword_cnt = size / माप(u32);
	अगर (size % माप(u32))
		dword_cnt++;
	err = hw_atl_ग_लिखो_fwcfg_dwords(self, (व्योम *)fw_req, dword_cnt);
	अगर (err < 0)
		जाओ err_निकास;

	/* Toggle statistics bit क्रम FW to update */
	ctrl2 = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	orig_ctrl2 = ctrl2 & BIT(CAPS_HI_FW_REQUEST);
	ctrl2 = ctrl2 ^ BIT(CAPS_HI_FW_REQUEST);
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, ctrl2);

	/* Wait FW to report back */
	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_state2_get, self, val,
					orig_ctrl2 != (val &
						       BIT(CAPS_HI_FW_REQUEST)),
					1U, 10000U);

err_निकास:
	वापस err;
पूर्ण

अटल व्योम aq_fw3x_enable_ptp(काष्ठा aq_hw_s *self, पूर्णांक enable)
अणु
	u32 ptp_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW3X_EXT_STATE_ADDR);
	u32 all_ptp_features = BIT(CAPS_EX_PHY_PTP_EN) |
						   BIT(CAPS_EX_PTP_GPIO_EN);

	अगर (enable)
		ptp_opts |= all_ptp_features;
	अन्यथा
		ptp_opts &= ~all_ptp_features;

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW3X_EXT_CONTROL_ADDR, ptp_opts);
पूर्ण

अटल व्योम aq_fw3x_adjust_ptp(काष्ठा aq_hw_s *self, uपूर्णांक64_t adj)
अणु
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW3X_PTP_ADJ_LSW_ADDR,
			(adj >>  0) & 0xffffffff);
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW3X_PTP_ADJ_MSW_ADDR,
			(adj >> 32) & 0xffffffff);
पूर्ण

अटल पूर्णांक aq_fw2x_led_control(काष्ठा aq_hw_s *self, u32 mode)
अणु
	अगर (self->fw_ver_actual < HW_ATL_FW_VER_LED)
		वापस -EOPNOTSUPP;

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_LED_ADDR, mode);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_set_eee_rate(काष्ठा aq_hw_s *self, u32 speed)
अणु
	u32 mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);

	aq_fw2x_upd_eee_rate_bits(self, &mpi_opts, speed);

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_get_eee_rate(काष्ठा aq_hw_s *self, u32 *rate,
				u32 *supported_rates)
अणु
	u32 mpi_state;
	u32 caps_hi;
	पूर्णांक err = 0;
	u32 offset;

	offset = self->mbox_addr + दुरत्व(काष्ठा hw_atl_utils_mbox,
					    info.caps_hi);

	err = hw_atl_utils_fw_करोwnld_dwords(self, offset, &caps_hi, 1);

	अगर (err)
		वापस err;

	*supported_rates = fw2x_to_eee_mask(caps_hi);

	mpi_state = aq_fw2x_state2_get(self);
	*rate = fw2x_to_eee_mask(mpi_state);

	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_renegotiate(काष्ठा aq_hw_s *self)
अणु
	u32 mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);

	mpi_opts |= BIT(CTRL_FORCE_RECONNECT);

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_set_flow_control(काष्ठा aq_hw_s *self)
अणु
	u32 mpi_state = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);

	aq_fw2x_upd_flow_control_bits(self, &mpi_state,
				      self->aq_nic_cfg->fc.req);

	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_state);

	वापस 0;
पूर्ण

अटल u32 aq_fw2x_get_flow_control(काष्ठा aq_hw_s *self, u32 *fcmode)
अणु
	u32 mpi_state = aq_fw2x_state2_get(self);
	*fcmode = 0;

	अगर (mpi_state & HW_ATL_FW2X_CAP_PAUSE)
		*fcmode |= AQ_NIC_FC_RX;

	अगर (mpi_state & HW_ATL_FW2X_CAP_ASYM_PAUSE)
		*fcmode |= AQ_NIC_FC_TX;

	वापस 0;
पूर्ण

अटल पूर्णांक aq_fw2x_set_phyloopback(काष्ठा aq_hw_s *self, u32 mode, bool enable)
अणु
	u32 mpi_opts;

	चयन (mode) अणु
	हाल AQ_HW_LOOPBACK_PHYINT_SYS:
		mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
		अगर (enable)
			mpi_opts |= HW_ATL_FW2X_CTRL_INT_LOOPBACK;
		अन्यथा
			mpi_opts &= ~HW_ATL_FW2X_CTRL_INT_LOOPBACK;
		aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);
		अवरोध;
	हाल AQ_HW_LOOPBACK_PHYEXT_SYS:
		mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
		अगर (enable)
			mpi_opts |= HW_ATL_FW2X_CTRL_EXT_LOOPBACK;
		अन्यथा
			mpi_opts &= ~HW_ATL_FW2X_CTRL_EXT_LOOPBACK;
		aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल u32 aq_fw2x_mbox_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_MBOX_ADDR);
पूर्ण

अटल u32 aq_fw2x_rpc_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_RPC_ADDR);
पूर्ण

अटल पूर्णांक aq_fw2x_settings_get(काष्ठा aq_hw_s *self, u32 *addr)
अणु
	पूर्णांक err = 0;
	u32 offset;

	offset = self->mbox_addr + दुरत्व(काष्ठा hw_atl_utils_mbox,
					    info.setting_address);

	err = hw_atl_utils_fw_करोwnld_dwords(self, offset, addr, 1);

	वापस err;
पूर्ण

अटल u32 aq_fw2x_state_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_STATE_ADDR);
पूर्ण

अटल u32 aq_fw2x_state2_get(काष्ठा aq_hw_s *self)
अणु
	वापस aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_STATE2_ADDR);
पूर्ण

अटल पूर्णांक aq_fw2x_set_करोwnshअगरt(काष्ठा aq_hw_s *self, u32 counter)
अणु
	पूर्णांक err = 0;
	u32 mpi_opts;
	u32 offset;

	offset = दुरत्व(काष्ठा hw_atl_utils_settings, करोwnshअगरt_retry_count);
	err = hw_atl_ग_लिखो_fwsettings_dwords(self, offset, &counter, 1);
	अगर (err)
		वापस err;

	mpi_opts = aq_hw_पढ़ो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR);
	अगर (counter)
		mpi_opts |= HW_ATL_FW2X_CTRL_DOWNSHIFT;
	अन्यथा
		mpi_opts &= ~HW_ATL_FW2X_CTRL_DOWNSHIFT;
	aq_hw_ग_लिखो_reg(self, HW_ATL_FW2X_MPI_CONTROL2_ADDR, mpi_opts);

	वापस err;
पूर्ण

अटल पूर्णांक aq_fw2x_set_media_detect(काष्ठा aq_hw_s *self, bool on)
अणु
	u32 enable;
	u32 offset;

	अगर (self->fw_ver_actual < HW_ATL_FW_VER_MEDIA_CONTROL)
		वापस -EOPNOTSUPP;

	offset = दुरत्व(काष्ठा hw_atl_utils_settings, media_detect);
	enable = on;

	वापस hw_atl_ग_लिखो_fwsettings_dwords(self, offset, &enable, 1);
पूर्ण

अटल u32 aq_fw2x_get_link_capabilities(काष्ठा aq_hw_s *self)
अणु
	पूर्णांक err = 0;
	u32 offset;
	u32 val;

	offset = self->mbox_addr +
		 दुरत्व(काष्ठा hw_atl_utils_mbox, info.caps_lo);

	err = hw_atl_utils_fw_करोwnld_dwords(self, offset, &val, 1);

	अगर (err)
		वापस 0;

	वापस val;
पूर्ण

अटल पूर्णांक aq_fw2x_send_macsec_req(काष्ठा aq_hw_s *hw,
				   काष्ठा macsec_msg_fw_request *req,
				   काष्ठा macsec_msg_fw_response *response)
अणु
	u32 low_status, low_req = 0;
	u32 dword_cnt;
	u32 caps_lo;
	u32 offset;
	पूर्णांक err;

	अगर (!req || !response)
		वापस -EINVAL;

	caps_lo = aq_fw2x_get_link_capabilities(hw);
	अगर (!(caps_lo & BIT(CAPS_LO_MACSEC)))
		वापस -EOPNOTSUPP;

	/* Write macsec request to cfg memory */
	dword_cnt = (माप(*req) + माप(u32) - 1) / माप(u32);
	err = hw_atl_ग_लिखो_fwcfg_dwords(hw, (व्योम *)req, dword_cnt);
	अगर (err < 0)
		वापस err;

	/* Toggle 0x368.CAPS_LO_MACSEC bit */
	low_req = aq_hw_पढ़ो_reg(hw, HW_ATL_FW2X_MPI_CONTROL_ADDR);
	low_req ^= HW_ATL_FW2X_CAP_MACSEC;
	aq_hw_ग_लिखो_reg(hw, HW_ATL_FW2X_MPI_CONTROL_ADDR, low_req);

	/* Wait FW to report back */
	err = पढ़ोx_poll_समयout_atomic(aq_fw2x_state_get, hw, low_status,
		low_req != (low_status & BIT(CAPS_LO_MACSEC)), 1U, 10000U);
	अगर (err)
		वापस -EIO;

	/* Read status of ग_लिखो operation */
	offset = hw->rpc_addr + माप(u32);
	err = hw_atl_utils_fw_करोwnld_dwords(hw, offset, (u32 *)(व्योम *)response,
					    माप(*response) / माप(u32));

	वापस err;
पूर्ण

स्थिर काष्ठा aq_fw_ops aq_fw_2x_ops = अणु
	.init               = aq_fw2x_init,
	.deinit             = aq_fw2x_deinit,
	.reset              = शून्य,
	.renegotiate        = aq_fw2x_renegotiate,
	.get_mac_permanent  = aq_fw2x_get_mac_permanent,
	.set_link_speed     = aq_fw2x_set_link_speed,
	.set_state          = aq_fw2x_set_state,
	.update_link_status = aq_fw2x_update_link_status,
	.update_stats       = aq_fw2x_update_stats,
	.get_mac_temp       = शून्य,
	.get_phy_temp       = aq_fw2x_get_phy_temp,
	.set_घातer          = aq_fw2x_set_घातer,
	.set_eee_rate       = aq_fw2x_set_eee_rate,
	.get_eee_rate       = aq_fw2x_get_eee_rate,
	.set_flow_control   = aq_fw2x_set_flow_control,
	.get_flow_control   = aq_fw2x_get_flow_control,
	.send_fw_request    = aq_fw2x_send_fw_request,
	.enable_ptp         = aq_fw3x_enable_ptp,
	.led_control        = aq_fw2x_led_control,
	.set_phyloopback    = aq_fw2x_set_phyloopback,
	.set_करोwnshअगरt      = aq_fw2x_set_करोwnshअगरt,
	.set_media_detect   = aq_fw2x_set_media_detect,
	.adjust_ptp         = aq_fw3x_adjust_ptp,
	.get_link_capabilities = aq_fw2x_get_link_capabilities,
	.send_macsec_req    = aq_fw2x_send_macsec_req,
पूर्ण;
