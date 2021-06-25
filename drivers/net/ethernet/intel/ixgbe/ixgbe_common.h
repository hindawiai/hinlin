<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#अगर_अघोषित _IXGBE_COMMON_H_
#घोषणा _IXGBE_COMMON_H_

#समावेश "ixgbe_type.h"
#समावेश "ixgbe.h"

u16 ixgbe_get_pcie_msix_count_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_init_ops_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_init_hw_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_start_hw_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_start_hw_gen2(काष्ठा ixgbe_hw *hw);
s32 ixgbe_clear_hw_cntrs_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_पढ़ो_pba_string_generic(काष्ठा ixgbe_hw *hw, u8 *pba_num,
				  u32 pba_num_size);
s32 ixgbe_get_mac_addr_generic(काष्ठा ixgbe_hw *hw, u8 *mac_addr);
क्रमागत ixgbe_bus_width ixgbe_convert_bus_width(u16 link_status);
क्रमागत ixgbe_bus_speed ixgbe_convert_bus_speed(u16 link_status);
s32 ixgbe_get_bus_info_generic(काष्ठा ixgbe_hw *hw);
व्योम ixgbe_set_lan_id_multi_port_pcie(काष्ठा ixgbe_hw *hw);
s32 ixgbe_stop_adapter_generic(काष्ठा ixgbe_hw *hw);

s32 ixgbe_led_on_generic(काष्ठा ixgbe_hw *hw, u32 index);
s32 ixgbe_led_off_generic(काष्ठा ixgbe_hw *hw, u32 index);
s32 ixgbe_init_led_link_act_generic(काष्ठा ixgbe_hw *hw);

s32 ixgbe_init_eeprom_params_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_ग_लिखो_eeprom_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 data);
s32 ixgbe_ग_लिखो_eeprom_buffer_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
					       u16 words, u16 *data);
s32 ixgbe_पढ़ो_eerd_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 *data);
s32 ixgbe_पढ़ो_eerd_buffer_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				   u16 words, u16 *data);
s32 ixgbe_ग_लिखो_eewr_generic(काष्ठा ixgbe_hw *hw, u16 offset, u16 data);
s32 ixgbe_ग_लिखो_eewr_buffer_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				    u16 words, u16 *data);
s32 ixgbe_पढ़ो_eeprom_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
				       u16 *data);
s32 ixgbe_पढ़ो_eeprom_buffer_bit_bang_generic(काष्ठा ixgbe_hw *hw, u16 offset,
					      u16 words, u16 *data);
s32 ixgbe_calc_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_validate_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw,
					   u16 *checksum_val);
s32 ixgbe_update_eeprom_checksum_generic(काष्ठा ixgbe_hw *hw);

s32 ixgbe_set_rar_generic(काष्ठा ixgbe_hw *hw, u32 index, u8 *addr, u32 vmdq,
			  u32 enable_addr);
s32 ixgbe_clear_rar_generic(काष्ठा ixgbe_hw *hw, u32 index);
s32 ixgbe_init_rx_addrs_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_update_mc_addr_list_generic(काष्ठा ixgbe_hw *hw,
				      काष्ठा net_device *netdev);
s32 ixgbe_enable_mc_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_disable_mc_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_disable_rx_buff_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_enable_rx_buff_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_enable_rx_dma_generic(काष्ठा ixgbe_hw *hw, u32 regval);
s32 ixgbe_fc_enable_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_setup_fc_generic(काष्ठा ixgbe_hw *);
bool ixgbe_device_supports_स्वतःneg_fc(काष्ठा ixgbe_hw *hw);
व्योम ixgbe_fc_स्वतःneg(काष्ठा ixgbe_hw *hw);

s32 ixgbe_acquire_swfw_sync(काष्ठा ixgbe_hw *hw, u32 mask);
व्योम ixgbe_release_swfw_sync(काष्ठा ixgbe_hw *hw, u32 mask);
s32 ixgbe_get_san_mac_addr_generic(काष्ठा ixgbe_hw *hw, u8 *san_mac_addr);
s32 ixgbe_set_vmdq_generic(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq);
s32 ixgbe_set_vmdq_san_mac_generic(काष्ठा ixgbe_hw *hw, u32 vmdq);
s32 ixgbe_clear_vmdq_generic(काष्ठा ixgbe_hw *hw, u32 rar, u32 vmdq);
s32 ixgbe_init_uta_tables_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_set_vfta_generic(काष्ठा ixgbe_hw *hw, u32 vlan,
			   u32 vind, bool vlan_on, bool vlvf_bypass);
s32 ixgbe_clear_vfta_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_check_mac_link_generic(काष्ठा ixgbe_hw *hw,
				 ixgbe_link_speed *speed,
				 bool *link_up, bool link_up_रुको_to_complete);
s32 ixgbe_get_wwn_prefix_generic(काष्ठा ixgbe_hw *hw, u16 *wwnn_prefix,
				 u16 *wwpn_prefix);

s32 prot_स्वतःc_पढ़ो_generic(काष्ठा ixgbe_hw *hw, bool *, u32 *reg_val);
s32 prot_स्वतःc_ग_लिखो_generic(काष्ठा ixgbe_hw *hw, u32 reg_val, bool locked);

s32 ixgbe_blink_led_start_generic(काष्ठा ixgbe_hw *hw, u32 index);
s32 ixgbe_blink_led_stop_generic(काष्ठा ixgbe_hw *hw, u32 index);
व्योम ixgbe_set_mac_anti_spoofing(काष्ठा ixgbe_hw *hw, bool enable, पूर्णांक vf);
व्योम ixgbe_set_vlan_anti_spoofing(काष्ठा ixgbe_hw *hw, bool enable, पूर्णांक vf);
s32 ixgbe_get_device_caps_generic(काष्ठा ixgbe_hw *hw, u16 *device_caps);
s32 ixgbe_set_fw_drv_ver_generic(काष्ठा ixgbe_hw *hw, u8 maj, u8 min,
				 u8 build, u8 ver, u16 len, स्थिर अक्षर *str);
u8 ixgbe_calculate_checksum(u8 *buffer, u32 length);
s32 ixgbe_host_पूर्णांकerface_command(काष्ठा ixgbe_hw *hw, व्योम *, u32 length,
				 u32 समयout, bool वापस_data);
s32 ixgbe_hic_unlocked(काष्ठा ixgbe_hw *hw, u32 *buffer, u32 len, u32 समयout);
s32 ixgbe_fw_phy_activity(काष्ठा ixgbe_hw *hw, u16 activity,
			  u32 (*data)[FW_PHY_ACT_DATA_COUNT]);
व्योम ixgbe_clear_tx_pending(काष्ठा ixgbe_hw *hw);
bool ixgbe_mng_present(काष्ठा ixgbe_hw *hw);
bool ixgbe_mng_enabled(काष्ठा ixgbe_hw *hw);

व्योम ixgbe_set_rxpba_generic(काष्ठा ixgbe_hw *hw, पूर्णांक num_pb,
			     u32 headroom, पूर्णांक strategy);

बाह्य स्थिर u32 ixgbe_mvals_8259X[IXGBE_MVALS_IDX_LIMIT];

#घोषणा IXGBE_I2C_THERMAL_SENSOR_ADDR	0xF8
#घोषणा IXGBE_EMC_INTERNAL_DATA		0x00
#घोषणा IXGBE_EMC_INTERNAL_THERM_LIMIT	0x20
#घोषणा IXGBE_EMC_DIODE1_DATA		0x01
#घोषणा IXGBE_EMC_DIODE1_THERM_LIMIT	0x19
#घोषणा IXGBE_EMC_DIODE2_DATA		0x23
#घोषणा IXGBE_EMC_DIODE2_THERM_LIMIT	0x1A
#घोषणा IXGBE_EMC_DIODE3_DATA		0x2A
#घोषणा IXGBE_EMC_DIODE3_THERM_LIMIT	0x30

s32 ixgbe_get_thermal_sensor_data_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_init_thermal_sensor_thresh_generic(काष्ठा ixgbe_hw *hw);
व्योम ixgbe_get_etk_id(काष्ठा ixgbe_hw *hw,
		      काष्ठा ixgbe_nvm_version *nvm_ver);
व्योम ixgbe_get_oem_prod_version(काष्ठा ixgbe_hw *hw,
				काष्ठा ixgbe_nvm_version *nvm_ver);
व्योम ixgbe_get_orom_version(काष्ठा ixgbe_hw *hw,
			    काष्ठा ixgbe_nvm_version *nvm_ver);
व्योम ixgbe_disable_rx_generic(काष्ठा ixgbe_hw *hw);
व्योम ixgbe_enable_rx_generic(काष्ठा ixgbe_hw *hw);
s32 ixgbe_setup_mac_link_multispeed_fiber(काष्ठा ixgbe_hw *hw,
					  ixgbe_link_speed speed,
					  bool स्वतःneg_रुको_to_complete);
व्योम ixgbe_set_soft_rate_select_speed(काष्ठा ixgbe_hw *hw,
				      ixgbe_link_speed speed);

#घोषणा IXGBE_FAILED_READ_RETRIES 5
#घोषणा IXGBE_FAILED_READ_REG 0xffffffffU
#घोषणा IXGBE_FAILED_READ_CFG_DWORD 0xffffffffU
#घोषणा IXGBE_FAILED_READ_CFG_WORD 0xffffU

u16 ixgbe_पढ़ो_pci_cfg_word(काष्ठा ixgbe_hw *hw, u32 reg);
व्योम ixgbe_ग_लिखो_pci_cfg_word(काष्ठा ixgbe_hw *hw, u32 reg, u16 value);

अटल अंतरभूत bool ixgbe_हटाओd(व्योम __iomem *addr)
अणु
	वापस unlikely(!addr);
पूर्ण

अटल अंतरभूत व्योम ixgbe_ग_लिखो_reg(काष्ठा ixgbe_hw *hw, u32 reg, u32 value)
अणु
	u8 __iomem *reg_addr = READ_ONCE(hw->hw_addr);

	अगर (ixgbe_हटाओd(reg_addr))
		वापस;
	ग_लिखोl(value, reg_addr + reg);
पूर्ण
#घोषणा IXGBE_WRITE_REG(a, reg, value) ixgbe_ग_लिखो_reg((a), (reg), (value))

#अगर_अघोषित ग_लिखोq
#घोषणा ग_लिखोq ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(u64 val, व्योम __iomem *addr)
अणु
	ग_लिखोl((u32)val, addr);
	ग_लिखोl((u32)(val >> 32), addr + 4);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम ixgbe_ग_लिखो_reg64(काष्ठा ixgbe_hw *hw, u32 reg, u64 value)
अणु
	u8 __iomem *reg_addr = READ_ONCE(hw->hw_addr);

	अगर (ixgbe_हटाओd(reg_addr))
		वापस;
	ग_लिखोq(value, reg_addr + reg);
पूर्ण
#घोषणा IXGBE_WRITE_REG64(a, reg, value) ixgbe_ग_लिखो_reg64((a), (reg), (value))

u32 ixgbe_पढ़ो_reg(काष्ठा ixgbe_hw *hw, u32 reg);
#घोषणा IXGBE_READ_REG(a, reg) ixgbe_पढ़ो_reg((a), (reg))

#घोषणा IXGBE_WRITE_REG_ARRAY(a, reg, offset, value) \
		ixgbe_ग_लिखो_reg((a), (reg) + ((offset) << 2), (value))

#घोषणा IXGBE_READ_REG_ARRAY(a, reg, offset) \
		ixgbe_पढ़ो_reg((a), (reg) + ((offset) << 2))

#घोषणा IXGBE_WRITE_FLUSH(a) ixgbe_पढ़ो_reg((a), IXGBE_STATUS)

#घोषणा ixgbe_hw_to_netdev(hw) (((काष्ठा ixgbe_adapter *)(hw)->back)->netdev)

#घोषणा hw_dbg(hw, क्रमmat, arg...) \
	netdev_dbg(ixgbe_hw_to_netdev(hw), क्रमmat, ## arg)
#घोषणा hw_err(hw, क्रमmat, arg...) \
	netdev_err(ixgbe_hw_to_netdev(hw), क्रमmat, ## arg)
#घोषणा e_dev_info(क्रमmat, arg...) \
	dev_info(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_dev_warn(क्रमmat, arg...) \
	dev_warn(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_dev_err(क्रमmat, arg...) \
	dev_err(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_dev_notice(क्रमmat, arg...) \
	dev_notice(&adapter->pdev->dev, क्रमmat, ## arg)
#घोषणा e_info(msglvl, क्रमmat, arg...) \
	netअगर_info(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_err(msglvl, क्रमmat, arg...) \
	netअगर_err(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_warn(msglvl, क्रमmat, arg...) \
	netअगर_warn(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#घोषणा e_crit(msglvl, क्रमmat, arg...) \
	netअगर_crit(adapter, msglvl, adapter->netdev, क्रमmat, ## arg)
#पूर्ण_अगर /* IXGBE_COMMON */
