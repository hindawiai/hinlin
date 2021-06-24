<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic qlcnic NIC Driver
 * Copyright (c) 2009-2013 QLogic Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/swab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <net/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/aer.h>
#समावेश <linux/log2.h>
#अगर_घोषित CONFIG_QLCNIC_HWMON
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#पूर्ण_अगर

#समावेश "qlcnic.h"
#समावेश "qlcnic_hw.h"

पूर्णांक qlcnicvf_config_bridged_mode(काष्ठा qlcnic_adapter *adapter, u32 enable)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक qlcnicvf_config_led(काष्ठा qlcnic_adapter *adapter, u32 state, u32 rate)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल sमाप_प्रकार qlcnic_store_bridged_mode(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	अचिन्हित दीर्घ new;
	पूर्णांक ret = -EINVAL;

	अगर (!(adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG))
		जाओ err_out;

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state))
		जाओ err_out;

	अगर (kम_से_अदीर्घ(buf, 2, &new))
		जाओ err_out;

	अगर (!qlcnic_config_bridged_mode(adapter, !!new))
		ret = len;

err_out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार qlcnic_show_bridged_mode(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक bridged_mode = 0;

	अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG)
		bridged_mode = !!(adapter->flags & QLCNIC_BRIDGE_ENABLED);

	वापस प्र_लिखो(buf, "%d\n", bridged_mode);
पूर्ण

अटल sमाप_प्रकार qlcnic_store_diag_mode(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	अचिन्हित दीर्घ new;

	अगर (kम_से_अदीर्घ(buf, 2, &new))
		वापस -EINVAL;

	अगर (!!new != !!(adapter->flags & QLCNIC_DIAG_ENABLED))
		adapter->flags ^= QLCNIC_DIAG_ENABLED;

	वापस len;
पूर्ण

अटल sमाप_प्रकार qlcnic_show_diag_mode(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	वापस प्र_लिखो(buf, "%d\n", !!(adapter->flags & QLCNIC_DIAG_ENABLED));
पूर्ण

अटल पूर्णांक qlcnic_validate_beacon(काष्ठा qlcnic_adapter *adapter, u16 beacon,
				  u8 *state, u8 *rate)
अणु
	*rate = LSB(beacon);
	*state = MSB(beacon);

	QLCDB(adapter, DRV, "rate %x state %x\n", *rate, *state);

	अगर (!*state) अणु
		*rate = __QLCNIC_MAX_LED_RATE;
		वापस 0;
	पूर्ण अन्यथा अगर (*state > __QLCNIC_MAX_LED_STATE) अणु
		वापस -EINVAL;
	पूर्ण

	अगर ((!*rate) || (*rate > __QLCNIC_MAX_LED_RATE))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_store_beacon(काष्ठा qlcnic_adapter *adapter,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	अचिन्हित दीर्घ h_beacon;
	पूर्णांक err;

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state))
		वापस -EIO;

	अगर (kम_से_अदीर्घ(buf, 2, &h_beacon))
		वापस -EINVAL;

	qlcnic_get_beacon_state(adapter);

	अगर (ahw->beacon_state == h_beacon)
		वापस len;

	rtnl_lock();
	अगर (!ahw->beacon_state) अणु
		अगर (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) अणु
			rtnl_unlock();
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (h_beacon)
		err = qlcnic_83xx_config_led(adapter, 1, h_beacon);
	अन्यथा
		err = qlcnic_83xx_config_led(adapter, 0, !h_beacon);
	अगर (!err)
		ahw->beacon_state = h_beacon;

	अगर (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);

	rtnl_unlock();
	वापस len;
पूर्ण

अटल पूर्णांक qlcnic_82xx_store_beacon(काष्ठा qlcnic_adapter *adapter,
				    स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक err, drv_sds_rings = adapter->drv_sds_rings;
	u16 beacon;
	u8 b_state, b_rate;

	अगर (len != माप(u16))
		वापस -EINVAL;

	स_नकल(&beacon, buf, माप(u16));
	err = qlcnic_validate_beacon(adapter, beacon, &b_state, &b_rate);
	अगर (err)
		वापस err;

	qlcnic_get_beacon_state(adapter);

	अगर (ahw->beacon_state == b_state)
		वापस len;

	rtnl_lock();
	अगर (!ahw->beacon_state) अणु
		अगर (test_and_set_bit(__QLCNIC_LED_ENABLE, &adapter->state)) अणु
			rtnl_unlock();
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	अगर (test_bit(__QLCNIC_RESETTING, &adapter->state)) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	अगर (!test_bit(__QLCNIC_DEV_UP, &adapter->state)) अणु
		err = qlcnic_diag_alloc_res(adapter->netdev, QLCNIC_LED_TEST);
		अगर (err)
			जाओ out;
		set_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state);
	पूर्ण

	err = qlcnic_config_led(adapter, b_state, b_rate);
	अगर (!err) अणु
		err = len;
		ahw->beacon_state = b_state;
	पूर्ण

	अगर (test_and_clear_bit(__QLCNIC_DIAG_RES_ALLOC, &adapter->state))
		qlcnic_diag_मुक्त_res(adapter->netdev, drv_sds_rings);

out:
	अगर (!ahw->beacon_state)
		clear_bit(__QLCNIC_LED_ENABLE, &adapter->state);
	rtnl_unlock();

	वापस err;
पूर्ण

अटल sमाप_प्रकार qlcnic_store_beacon(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक err = 0;

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC) अणु
		dev_warn(dev,
			 "LED test not supported in non privileged mode\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (qlcnic_82xx_check(adapter))
		err = qlcnic_82xx_store_beacon(adapter, buf, len);
	अन्यथा अगर (qlcnic_83xx_check(adapter))
		err = qlcnic_83xx_store_beacon(adapter, buf, len);
	अन्यथा
		वापस -EIO;

	वापस err;
पूर्ण

अटल sमाप_प्रकार qlcnic_show_beacon(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", adapter->ahw->beacon_state);
पूर्ण

अटल पूर्णांक qlcnic_sysfs_validate_crb(काष्ठा qlcnic_adapter *adapter,
				     loff_t offset, माप_प्रकार size)
अणु
	माप_प्रकार crb_size = 4;

	अगर (!(adapter->flags & QLCNIC_DIAG_ENABLED))
		वापस -EIO;

	अगर (offset < QLCNIC_PCI_CRBSPACE) अणु
		अगर (ADDR_IN_RANGE(offset, QLCNIC_PCI_CAMQM,
				  QLCNIC_PCI_CAMQM_END))
			crb_size = 8;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर ((size != crb_size) || (offset & (crb_size-1)))
		वापस  -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_crb(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr, अक्षर *buf,
				     loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = qlcnic_sysfs_validate_crb(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;
	qlcnic_पढ़ो_crb(adapter, buf, offset, size);
	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_ग_लिखो_crb(काष्ठा file *filp, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr, अक्षर *buf,
				      loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = qlcnic_sysfs_validate_crb(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	qlcnic_ग_लिखो_crb(adapter, buf, offset, size);
	वापस size;
पूर्ण

अटल पूर्णांक qlcnic_sysfs_validate_mem(काष्ठा qlcnic_adapter *adapter,
				     loff_t offset, माप_प्रकार size)
अणु
	अगर (!(adapter->flags & QLCNIC_DIAG_ENABLED))
		वापस -EIO;

	अगर ((size != 8) || (offset & 0x7))
		वापस  -EIO;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_mem(काष्ठा file *filp, काष्ठा kobject *kobj,
				     काष्ठा bin_attribute *attr, अक्षर *buf,
				     loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	u64 data;
	पूर्णांक ret;

	ret = qlcnic_sysfs_validate_mem(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	अगर (qlcnic_pci_mem_पढ़ो_2M(adapter, offset, &data))
		वापस -EIO;

	स_नकल(buf, &data, size);
	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_ग_लिखो_mem(काष्ठा file *filp, काष्ठा kobject *kobj,
				      काष्ठा bin_attribute *attr, अक्षर *buf,
				      loff_t offset, माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	u64 data;
	पूर्णांक ret;

	ret = qlcnic_sysfs_validate_mem(adapter, offset, size);
	अगर (ret != 0)
		वापस ret;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	स_नकल(&data, buf, size);

	अगर (qlcnic_pci_mem_ग_लिखो_2M(adapter, offset, data))
		वापस -EIO;

	वापस size;
पूर्ण

पूर्णांक qlcnic_is_valid_nic_func(काष्ठा qlcnic_adapter *adapter, u8 pci_func)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		अगर (adapter->npars[i].pci_func == pci_func)
			वापस i;
	पूर्ण

	dev_err(&adapter->pdev->dev, "%s: Invalid nic function\n", __func__);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक validate_pm_config(काष्ठा qlcnic_adapter *adapter,
			      काष्ठा qlcnic_pm_func_cfg *pm_cfg, पूर्णांक count)
अणु
	u8 src_pci_func, s_esw_id, d_esw_id;
	u8 dest_pci_func;
	पूर्णांक i, src_index, dest_index;

	क्रम (i = 0; i < count; i++) अणु
		src_pci_func = pm_cfg[i].pci_func;
		dest_pci_func = pm_cfg[i].dest_npar;
		src_index = qlcnic_is_valid_nic_func(adapter, src_pci_func);
		अगर (src_index < 0)
			वापस -EINVAL;

		dest_index = qlcnic_is_valid_nic_func(adapter, dest_pci_func);
		अगर (dest_index < 0)
			वापस -EINVAL;

		s_esw_id = adapter->npars[src_index].phy_port;
		d_esw_id = adapter->npars[dest_index].phy_port;

		अगर (s_esw_id != d_esw_id)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_ग_लिखो_pm_config(काष्ठा file *filp,
					    काष्ठा kobject *kobj,
					    काष्ठा bin_attribute *attr,
					    अक्षर *buf, loff_t offset,
					    माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_pm_func_cfg *pm_cfg;
	u32 id, action, pci_func;
	पूर्णांक count, rem, i, ret, index;

	count	= size / माप(काष्ठा qlcnic_pm_func_cfg);
	rem	= size % माप(काष्ठा qlcnic_pm_func_cfg);
	अगर (rem)
		वापस -EINVAL;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	pm_cfg = (काष्ठा qlcnic_pm_func_cfg *)buf;
	ret = validate_pm_config(adapter, pm_cfg, count);

	अगर (ret)
		वापस ret;
	क्रम (i = 0; i < count; i++) अणु
		pci_func = pm_cfg[i].pci_func;
		action = !!pm_cfg[i].action;
		index = qlcnic_is_valid_nic_func(adapter, pci_func);
		अगर (index < 0)
			वापस -EINVAL;

		id = adapter->npars[index].phy_port;
		ret = qlcnic_config_port_mirroring(adapter, id,
						   action, pci_func);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		pci_func = pm_cfg[i].pci_func;
		index = qlcnic_is_valid_nic_func(adapter, pci_func);
		अगर (index < 0)
			वापस -EINVAL;
		id = adapter->npars[index].phy_port;
		adapter->npars[index].enable_pm = !!pm_cfg[i].action;
		adapter->npars[index].dest_npar = id;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_pm_config(काष्ठा file *filp,
					   काष्ठा kobject *kobj,
					   काष्ठा bin_attribute *attr,
					   अक्षर *buf, loff_t offset,
					   माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_pm_func_cfg *pm_cfg;
	u8 pci_func;
	u32 count;
	पूर्णांक i;

	स_रखो(buf, 0, size);
	pm_cfg = (काष्ठा qlcnic_pm_func_cfg *)buf;
	count = size / माप(काष्ठा qlcnic_pm_func_cfg);
	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		pci_func = adapter->npars[i].pci_func;
		अगर (pci_func >= count) अणु
			dev_dbg(dev, "%s: Total nic functions[%d], App sent function count[%d]\n",
				__func__, adapter->ahw->total_nic_func, count);
			जारी;
		पूर्ण
		अगर (!adapter->npars[i].eचयन_status)
			जारी;

		pm_cfg[pci_func].action = adapter->npars[i].enable_pm;
		pm_cfg[pci_func].dest_npar = 0;
		pm_cfg[pci_func].pci_func = i;
	पूर्ण
	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	वापस size;
पूर्ण

अटल पूर्णांक validate_esw_config(काष्ठा qlcnic_adapter *adapter,
			       काष्ठा qlcnic_esw_func_cfg *esw_cfg, पूर्णांक count)
अणु
	काष्ठा qlcnic_hardware_context *ahw = adapter->ahw;
	पूर्णांक i, ret;
	u32 op_mode;
	u8 pci_func;

	अगर (qlcnic_82xx_check(adapter))
		op_mode = पढ़ोl(ahw->pci_base0 + QLCNIC_DRV_OP_MODE);
	अन्यथा
		op_mode = QLCRDX(ahw, QLC_83XX_DRV_OP_MODE);

	क्रम (i = 0; i < count; i++) अणु
		pci_func = esw_cfg[i].pci_func;
		अगर (pci_func >= ahw->max_vnic_func)
			वापस -EINVAL;

		अगर (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC)
			अगर (qlcnic_is_valid_nic_func(adapter, pci_func) < 0)
				वापस -EINVAL;

		चयन (esw_cfg[i].op_mode) अणु
		हाल QLCNIC_PORT_DEFAULTS:
			अगर (qlcnic_82xx_check(adapter)) अणु
				ret = QLC_DEV_GET_DRV(op_mode, pci_func);
			पूर्ण अन्यथा अणु
				ret = QLC_83XX_GET_FUNC_PRIVILEGE(op_mode,
								  pci_func);
				esw_cfg[i].offload_flags = 0;
			पूर्ण

			अगर (ret != QLCNIC_NON_PRIV_FUNC) अणु
				अगर (esw_cfg[i].mac_anti_spoof != 0)
					वापस -EINVAL;
				अगर (esw_cfg[i].mac_override != 1)
					वापस -EINVAL;
				अगर (esw_cfg[i].promisc_mode != 1)
					वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल QLCNIC_ADD_VLAN:
			अगर (!IS_VALID_VLAN(esw_cfg[i].vlan_id))
				वापस -EINVAL;
			अगर (!esw_cfg[i].op_type)
				वापस -EINVAL;
			अवरोध;
		हाल QLCNIC_DEL_VLAN:
			अगर (!esw_cfg[i].op_type)
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_ग_लिखो_esw_config(काष्ठा file *file,
					     काष्ठा kobject *kobj,
					     काष्ठा bin_attribute *attr,
					     अक्षर *buf, loff_t offset,
					     माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_esw_func_cfg *esw_cfg;
	काष्ठा qlcnic_npar_info *npar;
	पूर्णांक count, rem, i, ret;
	पूर्णांक index;
	u8 op_mode = 0, pci_func;

	count	= size / माप(काष्ठा qlcnic_esw_func_cfg);
	rem	= size % माप(काष्ठा qlcnic_esw_func_cfg);
	अगर (rem)
		वापस -EINVAL;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	esw_cfg = (काष्ठा qlcnic_esw_func_cfg *)buf;
	ret = validate_esw_config(adapter, esw_cfg, count);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < count; i++) अणु
		अगर (adapter->ahw->op_mode == QLCNIC_MGMT_FUNC)
			अगर (qlcnic_config_चयन_port(adapter, &esw_cfg[i]))
				वापस -EINVAL;

		अगर (adapter->ahw->pci_func != esw_cfg[i].pci_func)
			जारी;

		op_mode = esw_cfg[i].op_mode;
		qlcnic_get_eचयन_port_config(adapter, &esw_cfg[i]);
		esw_cfg[i].op_mode = op_mode;
		esw_cfg[i].pci_func = adapter->ahw->pci_func;

		चयन (esw_cfg[i].op_mode) अणु
		हाल QLCNIC_PORT_DEFAULTS:
			qlcnic_set_eचयन_port_features(adapter, &esw_cfg[i]);
			rtnl_lock();
			qlcnic_set_netdev_features(adapter, &esw_cfg[i]);
			rtnl_unlock();
			अवरोध;
		हाल QLCNIC_ADD_VLAN:
			qlcnic_set_vlan_config(adapter, &esw_cfg[i]);
			अवरोध;
		हाल QLCNIC_DEL_VLAN:
			esw_cfg[i].vlan_id = 0;
			qlcnic_set_vlan_config(adapter, &esw_cfg[i]);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		जाओ out;

	क्रम (i = 0; i < count; i++) अणु
		pci_func = esw_cfg[i].pci_func;
		index = qlcnic_is_valid_nic_func(adapter, pci_func);
		अगर (index < 0)
			वापस -EINVAL;
		npar = &adapter->npars[index];
		चयन (esw_cfg[i].op_mode) अणु
		हाल QLCNIC_PORT_DEFAULTS:
			npar->promisc_mode = esw_cfg[i].promisc_mode;
			npar->mac_override = esw_cfg[i].mac_override;
			npar->offload_flags = esw_cfg[i].offload_flags;
			npar->mac_anti_spoof = esw_cfg[i].mac_anti_spoof;
			npar->discard_tagged = esw_cfg[i].discard_tagged;
			अवरोध;
		हाल QLCNIC_ADD_VLAN:
			npar->pvid = esw_cfg[i].vlan_id;
			अवरोध;
		हाल QLCNIC_DEL_VLAN:
			npar->pvid = 0;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_esw_config(काष्ठा file *file,
					    काष्ठा kobject *kobj,
					    काष्ठा bin_attribute *attr,
					    अक्षर *buf, loff_t offset,
					    माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_esw_func_cfg *esw_cfg;
	u8 pci_func;
	u32 count;
	पूर्णांक i;

	स_रखो(buf, 0, size);
	esw_cfg = (काष्ठा qlcnic_esw_func_cfg *)buf;
	count = size / माप(काष्ठा qlcnic_esw_func_cfg);
	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		pci_func = adapter->npars[i].pci_func;
		अगर (pci_func >= count) अणु
			dev_dbg(dev, "%s: Total nic functions[%d], App sent function count[%d]\n",
				__func__, adapter->ahw->total_nic_func, count);
			जारी;
		पूर्ण
		अगर (!adapter->npars[i].eचयन_status)
			जारी;

		esw_cfg[pci_func].pci_func = pci_func;
		अगर (qlcnic_get_eचयन_port_config(adapter, &esw_cfg[pci_func]))
			वापस -EINVAL;
	पूर्ण
	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	वापस size;
पूर्ण

अटल पूर्णांक validate_npar_config(काष्ठा qlcnic_adapter *adapter,
				काष्ठा qlcnic_npar_func_cfg *np_cfg,
				पूर्णांक count)
अणु
	u8 pci_func, i;

	क्रम (i = 0; i < count; i++) अणु
		pci_func = np_cfg[i].pci_func;
		अगर (qlcnic_is_valid_nic_func(adapter, pci_func) < 0)
			वापस -EINVAL;

		अगर (!IS_VALID_BW(np_cfg[i].min_bw) ||
		    !IS_VALID_BW(np_cfg[i].max_bw))
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_ग_लिखो_npar_config(काष्ठा file *file,
					      काष्ठा kobject *kobj,
					      काष्ठा bin_attribute *attr,
					      अक्षर *buf, loff_t offset,
					      माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_info nic_info;
	काष्ठा qlcnic_npar_func_cfg *np_cfg;
	पूर्णांक i, count, rem, ret, index;
	u8 pci_func;

	count	= size / माप(काष्ठा qlcnic_npar_func_cfg);
	rem	= size % माप(काष्ठा qlcnic_npar_func_cfg);
	अगर (rem)
		वापस -EINVAL;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	np_cfg = (काष्ठा qlcnic_npar_func_cfg *)buf;
	ret = validate_npar_config(adapter, np_cfg, count);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < count; i++) अणु
		pci_func = np_cfg[i].pci_func;

		स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));
		ret = qlcnic_get_nic_info(adapter, &nic_info, pci_func);
		अगर (ret)
			वापस ret;
		nic_info.pci_func = pci_func;
		nic_info.min_tx_bw = np_cfg[i].min_bw;
		nic_info.max_tx_bw = np_cfg[i].max_bw;
		ret = qlcnic_set_nic_info(adapter, &nic_info);
		अगर (ret)
			वापस ret;
		index = qlcnic_is_valid_nic_func(adapter, pci_func);
		अगर (index < 0)
			वापस -EINVAL;
		adapter->npars[index].min_bw = nic_info.min_tx_bw;
		adapter->npars[index].max_bw = nic_info.max_tx_bw;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_npar_config(काष्ठा file *file,
					     काष्ठा kobject *kobj,
					     काष्ठा bin_attribute *attr,
					     अक्षर *buf, loff_t offset,
					     माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_npar_func_cfg *np_cfg;
	काष्ठा qlcnic_info nic_info;
	u8 pci_func;
	पूर्णांक i, ret;
	u32 count;

	स_रखो(&nic_info, 0, माप(काष्ठा qlcnic_info));
	स_रखो(buf, 0, size);
	np_cfg = (काष्ठा qlcnic_npar_func_cfg *)buf;

	count = size / माप(काष्ठा qlcnic_npar_func_cfg);
	क्रम (i = 0; i < adapter->ahw->total_nic_func; i++) अणु
		अगर (adapter->npars[i].pci_func >= count) अणु
			dev_dbg(dev, "%s: Total nic functions[%d], App sent function count[%d]\n",
				__func__, adapter->ahw->total_nic_func, count);
			जारी;
		पूर्ण
		अगर (!adapter->npars[i].eचयन_status)
			जारी;
		pci_func = adapter->npars[i].pci_func;
		अगर (qlcnic_is_valid_nic_func(adapter, pci_func) < 0)
			जारी;
		ret = qlcnic_get_nic_info(adapter, &nic_info, pci_func);
		अगर (ret)
			वापस ret;

		np_cfg[pci_func].pci_func = pci_func;
		np_cfg[pci_func].op_mode = (u8)nic_info.op_mode;
		np_cfg[pci_func].port_num = nic_info.phys_port;
		np_cfg[pci_func].fw_capab = nic_info.capabilities;
		np_cfg[pci_func].min_bw = nic_info.min_tx_bw;
		np_cfg[pci_func].max_bw = nic_info.max_tx_bw;
		np_cfg[pci_func].max_tx_queues = nic_info.max_tx_ques;
		np_cfg[pci_func].max_rx_queues = nic_info.max_rx_ques;
	पूर्ण
	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_get_port_stats(काष्ठा file *file,
					   काष्ठा kobject *kobj,
					   काष्ठा bin_attribute *attr,
					   अक्षर *buf, loff_t offset,
					   माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_esw_statistics port_stats;
	पूर्णांक ret;

	अगर (qlcnic_83xx_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (size != माप(काष्ठा qlcnic_esw_statistics))
		वापस -EINVAL;

	अगर (offset >= adapter->ahw->max_vnic_func)
		वापस -EINVAL;

	स_रखो(&port_stats, 0, size);
	ret = qlcnic_get_port_stats(adapter, offset, QLCNIC_QUERY_RX_COUNTER,
				    &port_stats.rx);
	अगर (ret)
		वापस ret;

	ret = qlcnic_get_port_stats(adapter, offset, QLCNIC_QUERY_TX_COUNTER,
				    &port_stats.tx);
	अगर (ret)
		वापस ret;

	स_नकल(buf, &port_stats, size);
	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_get_esw_stats(काष्ठा file *file,
					  काष्ठा kobject *kobj,
					  काष्ठा bin_attribute *attr,
					  अक्षर *buf, loff_t offset,
					  माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_esw_statistics esw_stats;
	पूर्णांक ret;

	अगर (qlcnic_83xx_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (size != माप(काष्ठा qlcnic_esw_statistics))
		वापस -EINVAL;

	अगर (offset >= QLCNIC_NIU_MAX_XG_PORTS)
		वापस -EINVAL;

	स_रखो(&esw_stats, 0, size);
	ret = qlcnic_get_eचयन_stats(adapter, offset, QLCNIC_QUERY_RX_COUNTER,
				       &esw_stats.rx);
	अगर (ret)
		वापस ret;

	ret = qlcnic_get_eचयन_stats(adapter, offset, QLCNIC_QUERY_TX_COUNTER,
				       &esw_stats.tx);
	अगर (ret)
		वापस ret;

	स_नकल(buf, &esw_stats, size);
	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_clear_esw_stats(काष्ठा file *file,
					    काष्ठा kobject *kobj,
					    काष्ठा bin_attribute *attr,
					    अक्षर *buf, loff_t offset,
					    माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (qlcnic_83xx_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (offset >= QLCNIC_NIU_MAX_XG_PORTS)
		वापस -EINVAL;

	ret = qlcnic_clear_esw_stats(adapter, QLCNIC_STATS_ESWITCH, offset,
				     QLCNIC_QUERY_RX_COUNTER);
	अगर (ret)
		वापस ret;

	ret = qlcnic_clear_esw_stats(adapter, QLCNIC_STATS_ESWITCH, offset,
				     QLCNIC_QUERY_TX_COUNTER);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_clear_port_stats(काष्ठा file *file,
					     काष्ठा kobject *kobj,
					     काष्ठा bin_attribute *attr,
					     अक्षर *buf, loff_t offset,
					     माप_प्रकार size)
अणु

	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	पूर्णांक ret;

	अगर (qlcnic_83xx_check(adapter))
		वापस -EOPNOTSUPP;

	अगर (offset >= adapter->ahw->max_vnic_func)
		वापस -EINVAL;

	ret = qlcnic_clear_esw_stats(adapter, QLCNIC_STATS_PORT, offset,
				     QLCNIC_QUERY_RX_COUNTER);
	अगर (ret)
		वापस ret;

	ret = qlcnic_clear_esw_stats(adapter, QLCNIC_STATS_PORT, offset,
				     QLCNIC_QUERY_TX_COUNTER);
	अगर (ret)
		वापस ret;

	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_sysfs_पढ़ो_pci_config(काष्ठा file *file,
					    काष्ठा kobject *kobj,
					    काष्ठा bin_attribute *attr,
					    अक्षर *buf, loff_t offset,
					    माप_प्रकार size)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	काष्ठा qlcnic_pci_func_cfg *pci_cfg;
	काष्ठा qlcnic_pci_info *pci_info;
	पूर्णांक i, ret;
	u32 count;

	pci_info = kसुस्मृति(size, माप(*pci_info), GFP_KERNEL);
	अगर (!pci_info)
		वापस -ENOMEM;

	ret = qlcnic_get_pci_info(adapter, pci_info);
	अगर (ret) अणु
		kमुक्त(pci_info);
		वापस ret;
	पूर्ण

	pci_cfg = (काष्ठा qlcnic_pci_func_cfg *)buf;
	count = size / माप(काष्ठा qlcnic_pci_func_cfg);
	qlcnic_swap32_buffer((u32 *)pci_info, size / माप(u32));
	क्रम (i = 0; i < count; i++) अणु
		pci_cfg[i].pci_func = pci_info[i].id;
		pci_cfg[i].func_type = pci_info[i].type;
		pci_cfg[i].func_state = 0;
		pci_cfg[i].port_num = pci_info[i].शेष_port;
		pci_cfg[i].min_bw = pci_info[i].tx_min_bw;
		pci_cfg[i].max_bw = pci_info[i].tx_max_bw;
		स_नकल(&pci_cfg[i].def_mac_addr, &pci_info[i].mac, ETH_ALEN);
	पूर्ण

	kमुक्त(pci_info);
	वापस size;
पूर्ण

अटल sमाप_प्रकार qlcnic_83xx_sysfs_flash_पढ़ो_handler(काष्ठा file *filp,
						    काष्ठा kobject *kobj,
						    काष्ठा bin_attribute *attr,
						    अक्षर *buf, loff_t offset,
						    माप_प्रकार size)
अणु
	अचिन्हित अक्षर *p_पढ़ो_buf;
	पूर्णांक  ret, count;
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);

	अगर (!size)
		वापस -EINVAL;

	count = size / माप(u32);

	अगर (size % माप(u32))
		count++;

	p_पढ़ो_buf = kसुस्मृति(size, माप(अचिन्हित अक्षर), GFP_KERNEL);
	अगर (!p_पढ़ो_buf)
		वापस -ENOMEM;
	अगर (qlcnic_83xx_lock_flash(adapter) != 0) अणु
		kमुक्त(p_पढ़ो_buf);
		वापस -EIO;
	पूर्ण

	ret = qlcnic_83xx_lockless_flash_पढ़ो32(adapter, offset, p_पढ़ो_buf,
						count);

	अगर (ret) अणु
		qlcnic_83xx_unlock_flash(adapter);
		kमुक्त(p_पढ़ो_buf);
		वापस ret;
	पूर्ण

	qlcnic_83xx_unlock_flash(adapter);
	qlcnic_swap32_buffer((u32 *)p_पढ़ो_buf, count);
	स_नकल(buf, p_पढ़ो_buf, size);
	kमुक्त(p_पढ़ो_buf);

	वापस size;
पूर्ण

अटल पूर्णांक qlcnic_83xx_sysfs_flash_bulk_ग_लिखो(काष्ठा qlcnic_adapter *adapter,
					      अक्षर *buf, loff_t offset,
					      माप_प्रकार size)
अणु
	पूर्णांक  i, ret, count;
	अचिन्हित अक्षर *p_cache, *p_src;

	p_cache = kसुस्मृति(size, माप(अचिन्हित अक्षर), GFP_KERNEL);
	अगर (!p_cache)
		वापस -ENOMEM;

	count = size / माप(u32);
	qlcnic_swap32_buffer((u32 *)buf, count);
	स_नकल(p_cache, buf, size);
	p_src = p_cache;

	अगर (qlcnic_83xx_lock_flash(adapter) != 0) अणु
		kमुक्त(p_cache);
		वापस -EIO;
	पूर्ण

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_enable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count / QLC_83XX_FLASH_WRITE_MAX; i++) अणु
		ret = qlcnic_83xx_flash_bulk_ग_लिखो(adapter, offset,
						   (u32 *)p_src,
						   QLC_83XX_FLASH_WRITE_MAX);

		अगर (ret) अणु
			अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
				ret = qlcnic_83xx_disable_flash_ग_लिखो(adapter);
				अगर (ret) अणु
					kमुक्त(p_cache);
					qlcnic_83xx_unlock_flash(adapter);
					वापस -EIO;
				पूर्ण
			पूर्ण

			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण

		p_src = p_src + माप(u32)*QLC_83XX_FLASH_WRITE_MAX;
		offset = offset + माप(u32)*QLC_83XX_FLASH_WRITE_MAX;
	पूर्ण

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_disable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण
	पूर्ण

	kमुक्त(p_cache);
	qlcnic_83xx_unlock_flash(adapter);

	वापस 0;
पूर्ण

अटल पूर्णांक qlcnic_83xx_sysfs_flash_ग_लिखो(काष्ठा qlcnic_adapter *adapter,
					 अक्षर *buf, loff_t offset, माप_प्रकार size)
अणु
	पूर्णांक  i, ret, count;
	अचिन्हित अक्षर *p_cache, *p_src;

	p_cache = kसुस्मृति(size, माप(अचिन्हित अक्षर), GFP_KERNEL);
	अगर (!p_cache)
		वापस -ENOMEM;

	qlcnic_swap32_buffer((u32 *)buf, size / माप(u32));
	स_नकल(p_cache, buf, size);
	p_src = p_cache;
	count = size / माप(u32);

	अगर (qlcnic_83xx_lock_flash(adapter) != 0) अणु
		kमुक्त(p_cache);
		वापस -EIO;
	पूर्ण

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_enable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		ret = qlcnic_83xx_flash_ग_लिखो32(adapter, offset, (u32 *)p_src);
		अगर (ret) अणु
			अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
				ret = qlcnic_83xx_disable_flash_ग_लिखो(adapter);
				अगर (ret) अणु
					kमुक्त(p_cache);
					qlcnic_83xx_unlock_flash(adapter);
					वापस -EIO;
				पूर्ण
			पूर्ण
			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण

		p_src = p_src + माप(u32);
		offset = offset + माप(u32);
	पूर्ण

	अगर (adapter->ahw->fdt.mfg_id == adapter->flash_mfg_id) अणु
		ret = qlcnic_83xx_disable_flash_ग_लिखो(adapter);
		अगर (ret) अणु
			kमुक्त(p_cache);
			qlcnic_83xx_unlock_flash(adapter);
			वापस -EIO;
		पूर्ण
	पूर्ण

	kमुक्त(p_cache);
	qlcnic_83xx_unlock_flash(adapter);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार qlcnic_83xx_sysfs_flash_ग_लिखो_handler(काष्ठा file *filp,
						     काष्ठा kobject *kobj,
						     काष्ठा bin_attribute *attr,
						     अक्षर *buf, loff_t offset,
						     माप_प्रकार size)
अणु
	पूर्णांक  ret;
	अटल पूर्णांक flash_mode;
	अचिन्हित दीर्घ data;
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);

	ret = kम_से_अदीर्घ(buf, 16, &data);
	अगर (ret)
		वापस ret;

	चयन (data) अणु
	हाल QLC_83XX_FLASH_SECTOR_ERASE_CMD:
		flash_mode = QLC_83XX_ERASE_MODE;
		ret = qlcnic_83xx_erase_flash_sector(adapter, offset);
		अगर (ret) अणु
			dev_err(&adapter->pdev->dev,
				"%s failed at %d\n", __func__, __LINE__);
			वापस -EIO;
		पूर्ण
		अवरोध;

	हाल QLC_83XX_FLASH_BULK_WRITE_CMD:
		flash_mode = QLC_83XX_BULK_WRITE_MODE;
		अवरोध;

	हाल QLC_83XX_FLASH_WRITE_CMD:
		flash_mode = QLC_83XX_WRITE_MODE;
		अवरोध;
	शेष:
		अगर (flash_mode == QLC_83XX_BULK_WRITE_MODE) अणु
			ret = qlcnic_83xx_sysfs_flash_bulk_ग_लिखो(adapter, buf,
								 offset, size);
			अगर (ret) अणु
				dev_err(&adapter->pdev->dev,
					"%s failed at %d\n",
					__func__, __LINE__);
				वापस -EIO;
			पूर्ण
		पूर्ण

		अगर (flash_mode == QLC_83XX_WRITE_MODE) अणु
			ret = qlcnic_83xx_sysfs_flash_ग_लिखो(adapter, buf,
							    offset, size);
			अगर (ret) अणु
				dev_err(&adapter->pdev->dev,
					"%s failed at %d\n", __func__,
					__LINE__);
				वापस -EIO;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस size;
पूर्ण

अटल स्थिर काष्ठा device_attribute dev_attr_bridged_mode = अणु
	.attr = अणु .name = "bridged_mode", .mode = 0644 पूर्ण,
	.show = qlcnic_show_bridged_mode,
	.store = qlcnic_store_bridged_mode,
पूर्ण;

अटल स्थिर काष्ठा device_attribute dev_attr_diag_mode = अणु
	.attr = अणु .name = "diag_mode", .mode = 0644 पूर्ण,
	.show = qlcnic_show_diag_mode,
	.store = qlcnic_store_diag_mode,
पूर्ण;

अटल स्थिर काष्ठा device_attribute dev_attr_beacon = अणु
	.attr = अणु .name = "beacon", .mode = 0644 पूर्ण,
	.show = qlcnic_show_beacon,
	.store = qlcnic_store_beacon,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_crb = अणु
	.attr = अणु .name = "crb", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_crb,
	.ग_लिखो = qlcnic_sysfs_ग_लिखो_crb,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_mem = अणु
	.attr = अणु .name = "mem", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_mem,
	.ग_लिखो = qlcnic_sysfs_ग_लिखो_mem,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_npar_config = अणु
	.attr = अणु .name = "npar_config", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_npar_config,
	.ग_लिखो = qlcnic_sysfs_ग_लिखो_npar_config,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_pci_config = अणु
	.attr = अणु .name = "pci_config", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_pci_config,
	.ग_लिखो = शून्य,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_port_stats = अणु
	.attr = अणु .name = "port_stats", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_get_port_stats,
	.ग_लिखो = qlcnic_sysfs_clear_port_stats,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_esw_stats = अणु
	.attr = अणु .name = "esw_stats", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_get_esw_stats,
	.ग_लिखो = qlcnic_sysfs_clear_esw_stats,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_esw_config = अणु
	.attr = अणु .name = "esw_config", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_esw_config,
	.ग_लिखो = qlcnic_sysfs_ग_लिखो_esw_config,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_pm_config = अणु
	.attr = अणु .name = "pm_config", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_sysfs_पढ़ो_pm_config,
	.ग_लिखो = qlcnic_sysfs_ग_लिखो_pm_config,
पूर्ण;

अटल स्थिर काष्ठा bin_attribute bin_attr_flash = अणु
	.attr = अणु .name = "flash", .mode = 0644 पूर्ण,
	.size = 0,
	.पढ़ो = qlcnic_83xx_sysfs_flash_पढ़ो_handler,
	.ग_लिखो = qlcnic_83xx_sysfs_flash_ग_लिखो_handler,
पूर्ण;

#अगर_घोषित CONFIG_QLCNIC_HWMON

अटल sमाप_प्रकार qlcnic_hwmon_show_temp(काष्ठा device *dev,
				      काष्ठा device_attribute *dev_attr,
				      अक्षर *buf)
अणु
	काष्ठा qlcnic_adapter *adapter = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक temperature = 0, value = 0;

	अगर (qlcnic_83xx_check(adapter))
		value = QLCRDX(adapter->ahw, QLC_83XX_ASIC_TEMP);
	अन्यथा अगर (qlcnic_82xx_check(adapter))
		value = QLC_SHARED_REG_RD32(adapter, QLCNIC_ASIC_TEMP);

	temperature = qlcnic_get_temp_val(value);
	/* display millidegree celcius */
	temperature *= 1000;
	वापस प्र_लिखो(buf, "%u\n", temperature);
पूर्ण

/* hwmon-sysfs attributes */
अटल SENSOR_DEVICE_ATTR(temp1_input, 0444,
			  qlcnic_hwmon_show_temp, शून्य, 1);

अटल काष्ठा attribute *qlcnic_hwmon_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(qlcnic_hwmon);

व्योम qlcnic_रेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;
	काष्ठा device *hwmon_dev;

	/* Skip hwmon registration क्रम a VF device */
	अगर (qlcnic_sriov_vf_check(adapter)) अणु
		adapter->ahw->hwmon_dev = शून्य;
		वापस;
	पूर्ण
	hwmon_dev = hwmon_device_रेजिस्टर_with_groups(dev, qlcnic_driver_name,
						      adapter,
						      qlcnic_hwmon_groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_err(dev, "Cannot register with hwmon, err=%ld\n",
			PTR_ERR(hwmon_dev));
		hwmon_dev = शून्य;
	पूर्ण
	adapter->ahw->hwmon_dev = hwmon_dev;
पूर्ण

व्योम qlcnic_unरेजिस्टर_hwmon_dev(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *hwmon_dev = adapter->ahw->hwmon_dev;
	अगर (hwmon_dev) अणु
		hwmon_device_unरेजिस्टर(hwmon_dev);
		adapter->ahw->hwmon_dev = शून्य;
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम qlcnic_create_sysfs_entries(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG)
		अगर (device_create_file(dev, &dev_attr_bridged_mode))
			dev_warn(dev,
				 "failed to create bridged_mode sysfs entry\n");
पूर्ण

व्योम qlcnic_हटाओ_sysfs_entries(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (adapter->ahw->capabilities & QLCNIC_FW_CAPABILITY_BDG)
		device_हटाओ_file(dev, &dev_attr_bridged_mode);
पूर्ण

अटल व्योम qlcnic_create_diag_entries(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	अगर (device_create_bin_file(dev, &bin_attr_port_stats))
		dev_info(dev, "failed to create port stats sysfs entry");

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC)
		वापस;
	अगर (device_create_file(dev, &dev_attr_diag_mode))
		dev_info(dev, "failed to create diag_mode sysfs entry\n");
	अगर (device_create_bin_file(dev, &bin_attr_crb))
		dev_info(dev, "failed to create crb sysfs entry\n");
	अगर (device_create_bin_file(dev, &bin_attr_mem))
		dev_info(dev, "failed to create mem sysfs entry\n");

	अगर (test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state))
		वापस;

	अगर (device_create_bin_file(dev, &bin_attr_pci_config))
		dev_info(dev, "failed to create pci config sysfs entry");

	अगर (device_create_file(dev, &dev_attr_beacon))
		dev_info(dev, "failed to create beacon sysfs entry");

	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		वापस;
	अगर (device_create_bin_file(dev, &bin_attr_esw_config))
		dev_info(dev, "failed to create esw config sysfs entry");
	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस;
	अगर (device_create_bin_file(dev, &bin_attr_npar_config))
		dev_info(dev, "failed to create npar config sysfs entry");
	अगर (device_create_bin_file(dev, &bin_attr_pm_config))
		dev_info(dev, "failed to create pm config sysfs entry");
	अगर (device_create_bin_file(dev, &bin_attr_esw_stats))
		dev_info(dev, "failed to create eswitch stats sysfs entry");
पूर्ण

अटल व्योम qlcnic_हटाओ_diag_entries(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	device_हटाओ_bin_file(dev, &bin_attr_port_stats);

	अगर (adapter->ahw->op_mode == QLCNIC_NON_PRIV_FUNC)
		वापस;
	device_हटाओ_file(dev, &dev_attr_diag_mode);
	device_हटाओ_bin_file(dev, &bin_attr_crb);
	device_हटाओ_bin_file(dev, &bin_attr_mem);

	अगर (test_bit(__QLCNIC_MAINTEन_अंकCE_MODE, &adapter->state))
		वापस;

	device_हटाओ_bin_file(dev, &bin_attr_pci_config);
	device_हटाओ_file(dev, &dev_attr_beacon);
	अगर (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		वापस;
	device_हटाओ_bin_file(dev, &bin_attr_esw_config);
	अगर (adapter->ahw->op_mode != QLCNIC_MGMT_FUNC)
		वापस;
	device_हटाओ_bin_file(dev, &bin_attr_npar_config);
	device_हटाओ_bin_file(dev, &bin_attr_pm_config);
	device_हटाओ_bin_file(dev, &bin_attr_esw_stats);
पूर्ण

व्योम qlcnic_82xx_add_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_create_diag_entries(adapter);
पूर्ण

व्योम qlcnic_82xx_हटाओ_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	qlcnic_हटाओ_diag_entries(adapter);
पूर्ण

व्योम qlcnic_83xx_add_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	qlcnic_create_diag_entries(adapter);

	अगर (sysfs_create_bin_file(&dev->kobj, &bin_attr_flash))
		dev_info(dev, "failed to create flash sysfs entry\n");
पूर्ण

व्योम qlcnic_83xx_हटाओ_sysfs(काष्ठा qlcnic_adapter *adapter)
अणु
	काष्ठा device *dev = &adapter->pdev->dev;

	qlcnic_हटाओ_diag_entries(adapter);
	sysfs_हटाओ_bin_file(&dev->kobj, &bin_attr_flash);
पूर्ण
