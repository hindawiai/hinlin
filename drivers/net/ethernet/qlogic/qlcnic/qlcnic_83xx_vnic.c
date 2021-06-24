<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश "qlcnic.h"
#समावेश "qlcnic_hw.h"

अटल पूर्णांक qlcnic_83xx_enable_vnic_mode(काष्ठा qlcnic_adapter *adapter, पूर्णांक lock)
अणु
	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण
	QLCWRX(adapter->ahw, QLC_83XX_VNIC_STATE, QLCNIC_DEV_NPAR_OPER);
	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_disable_vnic_mode(काष्ठा qlcnic_adapter *adapter, पूर्णांक lock)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (lock) अणु
		अगर (qlcnic_83xx_lock_driver(adapter))
			वापस -EBUSY;
	पूर्ण

	QLCWRX(adapter->ahw, QLC_83XX_VNIC_STATE, QLCNIC_DEV_NPAR_NON_OPER);
	ahw->idc.vnic_state = QLCNIC_DEV_NPAR_NON_OPER;

	अगर (lock)
		qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_set_vnic_opmode(काष्ठा qlcnic_adapter *adapter)
अणु
	u8 id;
	पूर्णांक ret = -EBUSY;
	u32 data = QLCNIC_MGMT_FUNC;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (qlcnic_83xx_lock_driver(adapter))
		वापस ret;

	id = ahw->pci_func;
	data = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);
	data = (data & ~QLC_83XX_SET_FUNC_OPMODE(0x3, id)) |
	       QLC_83XX_SET_FUNC_OPMODE(QLCNIC_MGMT_FUNC, id);

	QLCWRX(adapter->ahw, QLC_83XX_DRV_OP_MODE, data);

	qlcnic_83xx_unlock_driver(adapter);

	वापस 0;
पूर्ण

अटल व्योम
qlcnic_83xx_config_vnic_buff_descriptors(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;

	अगर (ahw->port_type == QLCNIC_XGBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_VF;
		adapter->max_rxd = MAX_RCV_DESCRIPTORS_VF;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_10G;

	पूर्ण अन्यथा अगर (ahw->port_type == QLCNIC_GBE) अणु
		adapter->num_rxd = DEFAULT_RCV_DESCRIPTORS_1G;
		adapter->num_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_jumbo_rxd = MAX_JUMBO_RCV_DESCRIPTORS_1G;
		adapter->max_rxd = MAX_RCV_DESCRIPTORS_1G;
	पूर्ण
	adapter->num_txd = MAX_CMD_DESCRIPTORS;
	adapter->max_rds_rings = MAX_RDS_RINGS;
पूर्ण


/**
 * qlcnic_83xx_init_mgmt_vnic
 *
 * @adapter: adapter काष्ठाure
 * Management भव NIC sets the operational mode of other vNIC's and
 * configures embedded चयन (ESWITCH).
 * Returns: Success(0) or error code.
 *
 **/
अटल पूर्णांक qlcnic_83xx_init_mgmt_vnic(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा qlcnic_npar_info *npar;
	पूर्णांक i, err = -EIO;

	qlcnic_83xx_get_minidump_ढाँचा(adapter);

	अगर (!(adapter->flags & QLCNIC_ADAPTER_INITIALIZED)) अणु
		अगर (qlcnic_init_pci_info(adapter))
			वापस err;

		npar = adapter->npars;

		क्रम (i = 0; i < ahw->total_nic_func; i++, npar++) अणु
			dev_info(dev, "id:%d active:%d type:%d port:%d min_bw:%d max_bw:%d mac_addr:%pM\n",
				 npar->pci_func, npar->active, npar->type,
				 npar->phy_port, npar->min_bw, npar->max_bw,
				 npar->mac);
		पूर्ण

		dev_info(dev, "Max functions = %d, active functions = %d\n",
			 ahw->max_pci_func, ahw->total_nic_func);

		अगर (qlcnic_83xx_set_vnic_opmode(adapter))
			वापस err;

		अगर (qlcnic_set_शेष_offload_settings(adapter))
			वापस err;
	पूर्ण अन्यथा अणु
		अगर (qlcnic_reset_npar_config(adapter))
			वापस err;
	पूर्ण

	अगर (qlcnic_83xx_get_port_info(adapter))
		वापस err;

	qlcnic_83xx_config_vnic_buff_descriptors(adapter);
	ahw->msix_supported = qlcnic_use_msi_x ? 1 : 0;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;
	qlcnic_83xx_enable_vnic_mode(adapter, 1);

	dev_info(dev, "HAL Version: %d, Management function\n",
		 ahw->fw_hal_version);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_init_privileged_vnic(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = -EIO;

	qlcnic_83xx_get_minidump_ढाँचा(adapter);
	अगर (qlcnic_83xx_get_port_info(adapter))
		वापस err;

	qlcnic_83xx_config_vnic_buff_descriptors(adapter);
	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	dev_info(&adapter->pdev->dev,
		 "HAL Version: %d, Privileged function\n",
		 adapter->ahw->fw_hal_version);
	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_init_non_privileged_vnic(काष्ठा qlcnic_adapter *adapter)
अणु
	पूर्णांक err = -EIO;

	qlcnic_83xx_get_fw_version(adapter);
	अगर (qlcnic_set_eचयन_port_config(adapter))
		वापस err;

	अगर (qlcnic_83xx_get_port_info(adapter))
		वापस err;

	qlcnic_83xx_config_vnic_buff_descriptors(adapter);
	adapter->ahw->msix_supported = !!qlcnic_use_msi_x;
	adapter->flags |= QLCNIC_ADAPTER_INITIALIZED;

	dev_info(&adapter->pdev->dev, "HAL Version: %d, Virtual function\n",
		 adapter->ahw->fw_hal_version);

	वापस 0;
पूर्ण

/**
 * qlcnic_83xx_vnic_opmode
 *
 * @adapter: adapter काष्ठाure
 * Identअगरy भव NIC operational modes.
 *
 * Returns: Success(0) or error code.
 *
 **/
पूर्णांक qlcnic_83xx_config_vnic_opmode(काष्ठा qlcnic_adapter *adapter)
अणु
	u32 op_mode, priv_level;
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlcnic_nic_ढाँचा *nic_ops = adapter->nic_ops;

	qlcnic_get_func_no(adapter);
	op_mode = QLCRDX(adapter->ahw, QLC_83XX_DRV_OP_MODE);

	अगर (op_mode == QLC_83XX_DEFAULT_OPMODE)
		priv_level = QLCNIC_MGMT_FUNC;
	अन्यथा
		priv_level = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
							 ahw->pci_func);
	चयन (priv_level) अणु
	हाल QLCNIC_NON_PRIV_FUNC:
		ahw->op_mode = QLCNIC_NON_PRIV_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_पढ़ोy_state_entry;
		nic_ops->init_driver = qlcnic_83xx_init_non_privileged_vnic;
		अवरोध;
	हाल QLCNIC_PRIV_FUNC:
		ahw->op_mode = QLCNIC_PRIV_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_vnic_pf_entry;
		nic_ops->init_driver = qlcnic_83xx_init_privileged_vnic;
		अवरोध;
	हाल QLCNIC_MGMT_FUNC:
		ahw->op_mode = QLCNIC_MGMT_FUNC;
		ahw->idc.state_entry = qlcnic_83xx_idc_पढ़ोy_state_entry;
		nic_ops->init_driver = qlcnic_83xx_init_mgmt_vnic;
		अवरोध;
	शेष:
		dev_err(&adapter->pdev->dev, "Invalid Virtual NIC opmode\n");
		वापस -EIO;
	पूर्ण

	अगर (ahw->capabilities & QLC_83XX_ESWITCH_CAPABILITY) अणु
		adapter->flags |= QLCNIC_ESWITCH_ENABLED;
		अगर (adapter->drv_mac_learn)
			adapter->rx_mac_learn = true;
	पूर्ण अन्यथा अणु
		adapter->flags &= ~QLCNIC_ESWITCH_ENABLED;
		adapter->rx_mac_learn = false;
	पूर्ण

	ahw->idc.vnic_state = QLCNIC_DEV_NPAR_NON_OPER;
	ahw->idc.vnic_रुको_limit = QLCNIC_DEV_NPAR_OPER_TIMEO;

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_check_vnic_state(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	काष्ठा qlc_83xx_idc *idc = &ahw->idc;
	u32 state;

	state = QLCRDX(ahw, QLC_83XX_VNIC_STATE);
	जबतक (state != QLCNIC_DEV_NPAR_OPER && idc->vnic_रुको_limit) अणु
		idc->vnic_रुको_limit--;
		msleep(1000);
		state = QLCRDX(ahw, QLC_83XX_VNIC_STATE);
	पूर्ण

	अगर (state != QLCNIC_DEV_NPAR_OPER) अणु
		dev_err(&adapter->pdev->dev,
			"vNIC mode not operational, state check timed out.\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qlcnic_83xx_set_port_eचयन_status(काष्ठा qlcnic_adapter *adapter,
					पूर्णांक func, पूर्णांक *port_id)
अणु
	काष्ठा qlcnic_info nic_info;
	पूर्णांक err = 0;

	स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));

	err = qlcnic_get_nic_info(adapter, &nic_info, func);
	अगर (err)
		वापस err;

	अगर (nic_info.capabilities & QLC_83XX_ESWITCH_CAPABILITY)
		*port_id = nic_info.phys_port;
	अन्यथा
		err = -EIO;

	अगर (!err)
		adapter->eचयन[*port_id].flags |= QLCNIC_SWITCH_ENABLE;

	वापस err;
पूर्ण
