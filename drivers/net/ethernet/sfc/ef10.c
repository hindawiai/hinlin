<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2012-2013 Solarflare Communications Inc.
 */

#समावेश "net_driver.h"
#समावेश "rx_common.h"
#समावेश "tx_common.h"
#समावेश "ef10_regs.h"
#समावेश "io.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"
#समावेश "mcdi_port.h"
#समावेश "mcdi_port_common.h"
#समावेश "mcdi_functions.h"
#समावेश "nic.h"
#समावेश "mcdi_filters.h"
#समावेश "workarounds.h"
#समावेश "selftest.h"
#समावेश "ef10_sriov.h"
#समावेश <linux/in.h>
#समावेश <linux/jhash.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <net/udp_tunnel.h>

/* Hardware control क्रम EF10 architecture including 'Huntington'. */

#घोषणा EFX_EF10_DRVGEN_EV		7
क्रमागत अणु
	EFX_EF10_TEST = 1,
	EFX_EF10_REFILL,
पूर्ण;

/* VLAN list entry */
काष्ठा efx_ef10_vlan अणु
	काष्ठा list_head list;
	u16 vid;
पूर्ण;

अटल पूर्णांक efx_ef10_set_udp_tnl_ports(काष्ठा efx_nic *efx, bool unloading);
अटल स्थिर काष्ठा udp_tunnel_nic_info efx_ef10_udp_tunnels;

अटल पूर्णांक efx_ef10_get_warm_boot_count(काष्ठा efx_nic *efx)
अणु
	efx_dword_t reg;

	efx_पढ़ोd(efx, &reg, ER_DZ_BIU_MC_SFT_STATUS);
	वापस EFX_DWORD_FIELD(reg, EFX_WORD_1) == 0xb007 ?
		EFX_DWORD_FIELD(reg, EFX_WORD_0) : -EIO;
पूर्ण

/* On all EF10s up to and including SFC9220 (Medक्रमd1), all PFs use BAR 0 क्रम
 * I/O space and BAR 2(&3) क्रम memory.  On SFC9250 (Medक्रमd2), there is no I/O
 * bar; PFs use BAR 0/1 क्रम memory.
 */
अटल अचिन्हित पूर्णांक efx_ef10_pf_mem_bar(काष्ठा efx_nic *efx)
अणु
	चयन (efx->pci_dev->device) अणु
	हाल 0x0b03: /* SFC9250 PF */
		वापस 0;
	शेष:
		वापस 2;
	पूर्ण
पूर्ण

/* All VFs use BAR 0/1 क्रम memory */
अटल अचिन्हित पूर्णांक efx_ef10_vf_mem_bar(काष्ठा efx_nic *efx)
अणु
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक efx_ef10_mem_map_size(काष्ठा efx_nic *efx)
अणु
	पूर्णांक bar;

	bar = efx->type->mem_bar(efx);
	वापस resource_size(&efx->pci_dev->resource[bar]);
पूर्ण

अटल bool efx_ef10_is_vf(काष्ठा efx_nic *efx)
अणु
	वापस efx->type->is_vf;
पूर्ण

#अगर_घोषित CONFIG_SFC_SRIOV
अटल पूर्णांक efx_ef10_get_vf_index(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_FUNCTION_INFO_OUT_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	माप_प्रकार outlen;
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_FUNCTION_INFO, शून्य, 0, outbuf,
			  माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < माप(outbuf))
		वापस -EIO;

	nic_data->vf_index = MCDI_DWORD(outbuf, GET_FUNCTION_INFO_OUT_VF);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक efx_ef10_init_datapath_caps(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_CAPABILITIES_V4_OUT_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_CAPABILITIES_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_CAPABILITIES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_GET_CAPABILITIES_OUT_LEN) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "unable to read datapath firmware capabilities\n");
		वापस -EIO;
	पूर्ण

	nic_data->datapath_caps =
		MCDI_DWORD(outbuf, GET_CAPABILITIES_OUT_FLAGS1);

	अगर (outlen >= MC_CMD_GET_CAPABILITIES_V2_OUT_LEN) अणु
		nic_data->datapath_caps2 = MCDI_DWORD(outbuf,
				GET_CAPABILITIES_V2_OUT_FLAGS2);
		nic_data->piobuf_size = MCDI_WORD(outbuf,
				GET_CAPABILITIES_V2_OUT_SIZE_PIO_BUFF);
	पूर्ण अन्यथा अणु
		nic_data->datapath_caps2 = 0;
		nic_data->piobuf_size = ER_DZ_TX_PIOBUF_SIZE;
	पूर्ण

	/* record the DPCPU firmware IDs to determine VEB vचयनing support.
	 */
	nic_data->rx_dpcpu_fw_id =
		MCDI_WORD(outbuf, GET_CAPABILITIES_OUT_RX_DPCPU_FW_ID);
	nic_data->tx_dpcpu_fw_id =
		MCDI_WORD(outbuf, GET_CAPABILITIES_OUT_TX_DPCPU_FW_ID);

	अगर (!(nic_data->datapath_caps &
	      (1 << MC_CMD_GET_CAPABILITIES_OUT_RX_PREFIX_LEN_14_LBN))) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "current firmware does not support an RX prefix\n");
		वापस -ENODEV;
	पूर्ण

	अगर (outlen >= MC_CMD_GET_CAPABILITIES_V3_OUT_LEN) अणु
		u8 vi_winकरोw_mode = MCDI_BYTE(outbuf,
				GET_CAPABILITIES_V3_OUT_VI_WINDOW_MODE);

		rc = efx_mcdi_winकरोw_mode_to_stride(efx, vi_winकरोw_mode);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		/* keep शेष VI stride */
		netअगर_dbg(efx, probe, efx->net_dev,
			  "firmware did not report VI window mode, assuming vi_stride = %u\n",
			  efx->vi_stride);
	पूर्ण

	अगर (outlen >= MC_CMD_GET_CAPABILITIES_V4_OUT_LEN) अणु
		efx->num_mac_stats = MCDI_WORD(outbuf,
				GET_CAPABILITIES_V4_OUT_MAC_STATS_NUM_STATS);
		netअगर_dbg(efx, probe, efx->net_dev,
			  "firmware reports num_mac_stats = %u\n",
			  efx->num_mac_stats);
	पूर्ण अन्यथा अणु
		/* leave num_mac_stats as the शेष value, MC_CMD_MAC_NSTATS */
		netअगर_dbg(efx, probe, efx->net_dev,
			  "firmware did not report num_mac_stats, assuming %u\n",
			  efx->num_mac_stats);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम efx_ef10_पढ़ो_licensed_features(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LICENSING_V3_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_LICENSING_V3_OUT_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, LICENSING_V3_IN_OP,
		       MC_CMD_LICENSING_V3_IN_OP_REPORT_LICENSE);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_LICENSING_V3, inbuf, माप(inbuf),
				outbuf, माप(outbuf), &outlen);
	अगर (rc || (outlen < MC_CMD_LICENSING_V3_OUT_LEN))
		वापस;

	nic_data->licensed_features = MCDI_QWORD(outbuf,
					 LICENSING_V3_OUT_LICENSED_FEATURES);
पूर्ण

अटल पूर्णांक efx_ef10_get_sysclk_freq(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_CLOCK_OUT_LEN);
	पूर्णांक rc;

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_CLOCK, शून्य, 0,
			  outbuf, माप(outbuf), शून्य);
	अगर (rc)
		वापस rc;
	rc = MCDI_DWORD(outbuf, GET_CLOCK_OUT_SYS_FREQ);
	वापस rc > 0 ? rc : -दुस्फल;
पूर्ण

अटल पूर्णांक efx_ef10_get_समयr_workarounds(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक implemented;
	अचिन्हित पूर्णांक enabled;
	पूर्णांक rc;

	nic_data->workaround_35388 = false;
	nic_data->workaround_61265 = false;

	rc = efx_mcdi_get_workarounds(efx, &implemented, &enabled);

	अगर (rc == -ENOSYS) अणु
		/* Firmware without GET_WORKAROUNDS - not a problem. */
		rc = 0;
	पूर्ण अन्यथा अगर (rc == 0) अणु
		/* Bug61265 workaround is always enabled अगर implemented. */
		अगर (enabled & MC_CMD_GET_WORKAROUNDS_OUT_BUG61265)
			nic_data->workaround_61265 = true;

		अगर (enabled & MC_CMD_GET_WORKAROUNDS_OUT_BUG35388) अणु
			nic_data->workaround_35388 = true;
		पूर्ण अन्यथा अगर (implemented & MC_CMD_GET_WORKAROUNDS_OUT_BUG35388) अणु
			/* Workaround is implemented but not enabled.
			 * Try to enable it.
			 */
			rc = efx_mcdi_set_workaround(efx,
						     MC_CMD_WORKAROUND_BUG35388,
						     true, शून्य);
			अगर (rc == 0)
				nic_data->workaround_35388 = true;
			/* If we failed to set the workaround just carry on. */
			rc = 0;
		पूर्ण
	पूर्ण

	netअगर_dbg(efx, probe, efx->net_dev,
		  "workaround for bug 35388 is %sabled\n",
		  nic_data->workaround_35388 ? "en" : "dis");
	netअगर_dbg(efx, probe, efx->net_dev,
		  "workaround for bug 61265 is %sabled\n",
		  nic_data->workaround_61265 ? "en" : "dis");

	वापस rc;
पूर्ण

अटल व्योम efx_ef10_process_समयr_config(काष्ठा efx_nic *efx,
					  स्थिर efx_dword_t *data)
अणु
	अचिन्हित पूर्णांक max_count;

	अगर (EFX_EF10_WORKAROUND_61265(efx)) अणु
		efx->समयr_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_STEP_NS);
		efx->समयr_max_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_MCDI_TMR_MAX_NS);
	पूर्ण अन्यथा अगर (EFX_EF10_WORKAROUND_35388(efx)) अणु
		efx->समयr_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_NS_PER_COUNT);
		max_count = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_BUG35388_TMR_MAX_COUNT);
		efx->समयr_max_ns = max_count * efx->समयr_quantum_ns;
	पूर्ण अन्यथा अणु
		efx->समयr_quantum_ns = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_NS_PER_COUNT);
		max_count = MCDI_DWORD(data,
			GET_EVQ_TMR_PROPERTIES_OUT_TMR_REG_MAX_COUNT);
		efx->समयr_max_ns = max_count * efx->समयr_quantum_ns;
	पूर्ण

	netअगर_dbg(efx, probe, efx->net_dev,
		  "got timer properties from MC: quantum %u ns; max %u ns\n",
		  efx->समयr_quantum_ns, efx->समयr_max_ns);
पूर्ण

अटल पूर्णांक efx_ef10_get_समयr_config(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_EVQ_TMR_PROPERTIES_OUT_LEN);
	पूर्णांक rc;

	rc = efx_ef10_get_समयr_workarounds(efx);
	अगर (rc)
		वापस rc;

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_GET_EVQ_TMR_PROPERTIES, शून्य, 0,
				outbuf, माप(outbuf), शून्य);

	अगर (rc == 0) अणु
		efx_ef10_process_समयr_config(efx, outbuf);
	पूर्ण अन्यथा अगर (rc == -ENOSYS || rc == -EPERM) अणु
		/* Not available - fall back to Huntington शेषs. */
		अचिन्हित पूर्णांक quantum;

		rc = efx_ef10_get_sysclk_freq(efx);
		अगर (rc < 0)
			वापस rc;

		quantum = 1536000 / rc; /* 1536 cycles */
		efx->समयr_quantum_ns = quantum;
		efx->समयr_max_ns = efx->type->समयr_period_max * quantum;
		rc = 0;
	पूर्ण अन्यथा अणु
		efx_mcdi_display_error(efx, MC_CMD_GET_EVQ_TMR_PROPERTIES,
				       MC_CMD_GET_EVQ_TMR_PROPERTIES_OUT_LEN,
				       शून्य, 0, rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_get_mac_address_pf(काष्ठा efx_nic *efx, u8 *mac_address)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_GET_MAC_ADDRESSES_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_GET_MAC_ADDRESSES_IN_LEN != 0);

	rc = efx_mcdi_rpc(efx, MC_CMD_GET_MAC_ADDRESSES, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_GET_MAC_ADDRESSES_OUT_LEN)
		वापस -EIO;

	ether_addr_copy(mac_address,
			MCDI_PTR(outbuf, GET_MAC_ADDRESSES_OUT_MAC_ADDR_BASE));
	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_get_mac_address_vf(काष्ठा efx_nic *efx, u8 *mac_address)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_GET_MAC_ADDRESSES_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_VPORT_GET_MAC_ADDRESSES_OUT_LENMAX);
	माप_प्रकार outlen;
	पूर्णांक num_addrs, rc;

	MCDI_SET_DWORD(inbuf, VPORT_GET_MAC_ADDRESSES_IN_VPORT_ID,
		       EVB_PORT_ID_ASSIGNED);
	rc = efx_mcdi_rpc(efx, MC_CMD_VPORT_GET_MAC_ADDRESSES, inbuf,
			  माप(inbuf), outbuf, माप(outbuf), &outlen);

	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_VPORT_GET_MAC_ADDRESSES_OUT_LENMIN)
		वापस -EIO;

	num_addrs = MCDI_DWORD(outbuf,
			       VPORT_GET_MAC_ADDRESSES_OUT_MACADDR_COUNT);

	WARN_ON(num_addrs != 1);

	ether_addr_copy(mac_address,
			MCDI_PTR(outbuf, VPORT_GET_MAC_ADDRESSES_OUT_MACADDR));

	वापस 0;
पूर्ण

अटल sमाप_प्रकार efx_ef10_show_link_control_flag(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       अक्षर *buf)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       ((efx->mcdi->fn_flags) &
			(1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_LINKCTRL))
		       ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार efx_ef10_show_primary_flag(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा efx_nic *efx = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n",
		       ((efx->mcdi->fn_flags) &
			(1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_PRIMARY))
		       ? 1 : 0);
पूर्ण

अटल काष्ठा efx_ef10_vlan *efx_ef10_find_vlan(काष्ठा efx_nic *efx, u16 vid)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_ef10_vlan *vlan;

	WARN_ON(!mutex_is_locked(&nic_data->vlan_lock));

	list_क्रम_each_entry(vlan, &nic_data->vlan_list, list) अणु
		अगर (vlan->vid == vid)
			वापस vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक efx_ef10_add_vlan(काष्ठा efx_nic *efx, u16 vid)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_ef10_vlan *vlan;
	पूर्णांक rc;

	mutex_lock(&nic_data->vlan_lock);

	vlan = efx_ef10_find_vlan(efx, vid);
	अगर (vlan) अणु
		/* We add VID 0 on init. 8021q adds it on module init
		 * क्रम all पूर्णांकerfaces with VLAN filtring feature.
		 */
		अगर (vid == 0)
			जाओ करोne_unlock;
		netअगर_warn(efx, drv, efx->net_dev,
			   "VLAN %u already added\n", vid);
		rc = -EALREADY;
		जाओ fail_exist;
	पूर्ण

	rc = -ENOMEM;
	vlan = kzalloc(माप(*vlan), GFP_KERNEL);
	अगर (!vlan)
		जाओ fail_alloc;

	vlan->vid = vid;

	list_add_tail(&vlan->list, &nic_data->vlan_list);

	अगर (efx->filter_state) अणु
		mutex_lock(&efx->mac_lock);
		करोwn_ग_लिखो(&efx->filter_sem);
		rc = efx_mcdi_filter_add_vlan(efx, vlan->vid);
		up_ग_लिखो(&efx->filter_sem);
		mutex_unlock(&efx->mac_lock);
		अगर (rc)
			जाओ fail_filter_add_vlan;
	पूर्ण

करोne_unlock:
	mutex_unlock(&nic_data->vlan_lock);
	वापस 0;

fail_filter_add_vlan:
	list_del(&vlan->list);
	kमुक्त(vlan);
fail_alloc:
fail_exist:
	mutex_unlock(&nic_data->vlan_lock);
	वापस rc;
पूर्ण

अटल व्योम efx_ef10_del_vlan_पूर्णांकernal(काष्ठा efx_nic *efx,
				       काष्ठा efx_ef10_vlan *vlan)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	WARN_ON(!mutex_is_locked(&nic_data->vlan_lock));

	अगर (efx->filter_state) अणु
		करोwn_ग_लिखो(&efx->filter_sem);
		efx_mcdi_filter_del_vlan(efx, vlan->vid);
		up_ग_लिखो(&efx->filter_sem);
	पूर्ण

	list_del(&vlan->list);
	kमुक्त(vlan);
पूर्ण

अटल पूर्णांक efx_ef10_del_vlan(काष्ठा efx_nic *efx, u16 vid)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_ef10_vlan *vlan;
	पूर्णांक rc = 0;

	/* 8021q हटाओs VID 0 on module unload क्रम all पूर्णांकerfaces
	 * with VLAN filtering feature. We need to keep it to receive
	 * untagged traffic.
	 */
	अगर (vid == 0)
		वापस 0;

	mutex_lock(&nic_data->vlan_lock);

	vlan = efx_ef10_find_vlan(efx, vid);
	अगर (!vlan) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "VLAN %u to be deleted not found\n", vid);
		rc = -ENOENT;
	पूर्ण अन्यथा अणु
		efx_ef10_del_vlan_पूर्णांकernal(efx, vlan);
	पूर्ण

	mutex_unlock(&nic_data->vlan_lock);

	वापस rc;
पूर्ण

अटल व्योम efx_ef10_cleanup_vlans(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_ef10_vlan *vlan, *next_vlan;

	mutex_lock(&nic_data->vlan_lock);
	list_क्रम_each_entry_safe(vlan, next_vlan, &nic_data->vlan_list, list)
		efx_ef10_del_vlan_पूर्णांकernal(efx, vlan);
	mutex_unlock(&nic_data->vlan_lock);
पूर्ण

अटल DEVICE_ATTR(link_control_flag, 0444, efx_ef10_show_link_control_flag,
		   शून्य);
अटल DEVICE_ATTR(primary_flag, 0444, efx_ef10_show_primary_flag, शून्य);

अटल पूर्णांक efx_ef10_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data;
	पूर्णांक i, rc;

	nic_data = kzalloc(माप(*nic_data), GFP_KERNEL);
	अगर (!nic_data)
		वापस -ENOMEM;
	efx->nic_data = nic_data;

	/* we assume later that we can copy from this buffer in dwords */
	BUILD_BUG_ON(MCDI_CTL_SDU_LEN_MAX_V2 % 4);

	rc = efx_nic_alloc_buffer(efx, &nic_data->mcdi_buf,
				  8 + MCDI_CTL_SDU_LEN_MAX_V2, GFP_KERNEL);
	अगर (rc)
		जाओ fail1;

	/* Get the MC's warm boot count.  In case it's rebooting right
	 * now, be prepared to retry.
	 */
	i = 0;
	क्रम (;;) अणु
		rc = efx_ef10_get_warm_boot_count(efx);
		अगर (rc >= 0)
			अवरोध;
		अगर (++i == 5)
			जाओ fail2;
		ssleep(1);
	पूर्ण
	nic_data->warm_boot_count = rc;

	/* In हाल we're recovering from a crash (kexec), we want to
	 * cancel any outstanding request by the previous user of this
	 * function.  We send a special message using the least
	 * signअगरicant bits of the 'high' (करोorbell) रेजिस्टर.
	 */
	_efx_ग_लिखोd(efx, cpu_to_le32(1), ER_DZ_MC_DB_HWRD);

	rc = efx_mcdi_init(efx);
	अगर (rc)
		जाओ fail2;

	mutex_init(&nic_data->udp_tunnels_lock);
	क्रम (i = 0; i < ARRAY_SIZE(nic_data->udp_tunnels); ++i)
		nic_data->udp_tunnels[i].type =
			TUNNEL_ENCAP_UDP_PORT_ENTRY_INVALID;

	/* Reset (most) configuration क्रम this function */
	rc = efx_mcdi_reset(efx, RESET_TYPE_ALL);
	अगर (rc)
		जाओ fail3;

	/* Enable event logging */
	rc = efx_mcdi_log_ctrl(efx, true, false, 0);
	अगर (rc)
		जाओ fail3;

	rc = device_create_file(&efx->pci_dev->dev,
				&dev_attr_link_control_flag);
	अगर (rc)
		जाओ fail3;

	rc = device_create_file(&efx->pci_dev->dev, &dev_attr_primary_flag);
	अगर (rc)
		जाओ fail4;

	rc = efx_get_pf_index(efx, &nic_data->pf_index);
	अगर (rc)
		जाओ fail5;

	rc = efx_ef10_init_datapath_caps(efx);
	अगर (rc < 0)
		जाओ fail5;

	efx_ef10_पढ़ो_licensed_features(efx);

	/* We can have one VI क्रम each vi_stride-byte region.
	 * However, until we use TX option descriptors we need up to four
	 * TX queues per channel क्रम dअगरferent checksumming combinations.
	 */
	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN))
		efx->tx_queues_per_channel = 4;
	अन्यथा
		efx->tx_queues_per_channel = 2;
	efx->max_vis = efx_ef10_mem_map_size(efx) / efx->vi_stride;
	अगर (!efx->max_vis) अणु
		netअगर_err(efx, drv, efx->net_dev, "error determining max VIs\n");
		rc = -EIO;
		जाओ fail5;
	पूर्ण
	efx->max_channels = min_t(अचिन्हित पूर्णांक, EFX_MAX_CHANNELS,
				  efx->max_vis / efx->tx_queues_per_channel);
	efx->max_tx_channels = efx->max_channels;
	अगर (WARN_ON(efx->max_channels == 0)) अणु
		rc = -EIO;
		जाओ fail5;
	पूर्ण

	efx->rx_packet_len_offset =
		ES_DZ_RX_PREFIX_PKTLEN_OFST - ES_DZ_RX_PREFIX_SIZE;

	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_RX_INCLUDE_FCS_LBN))
		efx->net_dev->hw_features |= NETIF_F_RXFCS;

	rc = efx_mcdi_port_get_number(efx);
	अगर (rc < 0)
		जाओ fail5;
	efx->port_num = rc;

	rc = efx->type->get_mac_address(efx, efx->net_dev->perm_addr);
	अगर (rc)
		जाओ fail5;

	rc = efx_ef10_get_समयr_config(efx);
	अगर (rc < 0)
		जाओ fail5;

	rc = efx_mcdi_mon_probe(efx);
	अगर (rc && rc != -EPERM)
		जाओ fail5;

	efx_ptp_defer_probe_with_channel(efx);

#अगर_घोषित CONFIG_SFC_SRIOV
	अगर ((efx->pci_dev->physfn) && (!efx->pci_dev->is_physfn)) अणु
		काष्ठा pci_dev *pci_dev_pf = efx->pci_dev->physfn;
		काष्ठा efx_nic *efx_pf = pci_get_drvdata(pci_dev_pf);

		efx_pf->type->get_mac_address(efx_pf, nic_data->port_id);
	पूर्ण अन्यथा
#पूर्ण_अगर
		ether_addr_copy(nic_data->port_id, efx->net_dev->perm_addr);

	INIT_LIST_HEAD(&nic_data->vlan_list);
	mutex_init(&nic_data->vlan_lock);

	/* Add unspecअगरied VID to support VLAN filtering being disabled */
	rc = efx_ef10_add_vlan(efx, EFX_FILTER_VID_UNSPEC);
	अगर (rc)
		जाओ fail_add_vid_unspec;

	/* If VLAN filtering is enabled, we need VID 0 to get untagged
	 * traffic.  It is added स्वतःmatically अगर 8021q module is loaded,
	 * but we can't rely on it since module may be not loaded.
	 */
	rc = efx_ef10_add_vlan(efx, 0);
	अगर (rc)
		जाओ fail_add_vid_0;

	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN) &&
	    efx->mcdi->fn_flags &
	    (1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_TRUSTED))
		efx->net_dev->udp_tunnel_nic_info = &efx_ef10_udp_tunnels;

	वापस 0;

fail_add_vid_0:
	efx_ef10_cleanup_vlans(efx);
fail_add_vid_unspec:
	mutex_destroy(&nic_data->vlan_lock);
	efx_ptp_हटाओ(efx);
	efx_mcdi_mon_हटाओ(efx);
fail5:
	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_primary_flag);
fail4:
	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_link_control_flag);
fail3:
	efx_mcdi_detach(efx);

	mutex_lock(&nic_data->udp_tunnels_lock);
	स_रखो(nic_data->udp_tunnels, 0, माप(nic_data->udp_tunnels));
	(व्योम)efx_ef10_set_udp_tnl_ports(efx, true);
	mutex_unlock(&nic_data->udp_tunnels_lock);
	mutex_destroy(&nic_data->udp_tunnels_lock);

	efx_mcdi_fini(efx);
fail2:
	efx_nic_मुक्त_buffer(efx, &nic_data->mcdi_buf);
fail1:
	kमुक्त(nic_data);
	efx->nic_data = शून्य;
	वापस rc;
पूर्ण

#अगर_घोषित EFX_USE_PIO

अटल व्योम efx_ef10_मुक्त_piobufs(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_FREE_PIOBUF_IN_LEN);
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_FREE_PIOBUF_OUT_LEN != 0);

	क्रम (i = 0; i < nic_data->n_piobufs; i++) अणु
		MCDI_SET_DWORD(inbuf, FREE_PIOBUF_IN_PIOBUF_HANDLE,
			       nic_data->piobuf_handle[i]);
		rc = efx_mcdi_rpc(efx, MC_CMD_FREE_PIOBUF, inbuf, माप(inbuf),
				  शून्य, 0, शून्य);
		WARN_ON(rc);
	पूर्ण

	nic_data->n_piobufs = 0;
पूर्ण

अटल पूर्णांक efx_ef10_alloc_piobufs(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक n)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	MCDI_DECLARE_BUF(outbuf, MC_CMD_ALLOC_PIOBUF_OUT_LEN);
	अचिन्हित पूर्णांक i;
	माप_प्रकार outlen;
	पूर्णांक rc = 0;

	BUILD_BUG_ON(MC_CMD_ALLOC_PIOBUF_IN_LEN != 0);

	क्रम (i = 0; i < n; i++) अणु
		rc = efx_mcdi_rpc_quiet(efx, MC_CMD_ALLOC_PIOBUF, शून्य, 0,
					outbuf, माप(outbuf), &outlen);
		अगर (rc) अणु
			/* Don't display the MC error if we didn't have space
			 * क्रम a VF.
			 */
			अगर (!(efx_ef10_is_vf(efx) && rc == -ENOSPC))
				efx_mcdi_display_error(efx, MC_CMD_ALLOC_PIOBUF,
						       0, outbuf, outlen, rc);
			अवरोध;
		पूर्ण
		अगर (outlen < MC_CMD_ALLOC_PIOBUF_OUT_LEN) अणु
			rc = -EIO;
			अवरोध;
		पूर्ण
		nic_data->piobuf_handle[i] =
			MCDI_DWORD(outbuf, ALLOC_PIOBUF_OUT_PIOBUF_HANDLE);
		netअगर_dbg(efx, probe, efx->net_dev,
			  "allocated PIO buffer %u handle %x\n", i,
			  nic_data->piobuf_handle[i]);
	पूर्ण

	nic_data->n_piobufs = i;
	अगर (rc)
		efx_ef10_मुक्त_piobufs(efx);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_link_piobufs(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LINK_PIOBUF_IN_LEN);
	काष्ठा efx_channel *channel;
	काष्ठा efx_tx_queue *tx_queue;
	अचिन्हित पूर्णांक offset, index;
	पूर्णांक rc;

	BUILD_BUG_ON(MC_CMD_LINK_PIOBUF_OUT_LEN != 0);
	BUILD_BUG_ON(MC_CMD_UNLINK_PIOBUF_OUT_LEN != 0);

	/* Link a buffer to each VI in the ग_लिखो-combining mapping */
	क्रम (index = 0; index < nic_data->n_piobufs; ++index) अणु
		MCDI_SET_DWORD(inbuf, LINK_PIOBUF_IN_PIOBUF_HANDLE,
			       nic_data->piobuf_handle[index]);
		MCDI_SET_DWORD(inbuf, LINK_PIOBUF_IN_TXQ_INSTANCE,
			       nic_data->pio_ग_लिखो_vi_base + index);
		rc = efx_mcdi_rpc(efx, MC_CMD_LINK_PIOBUF,
				  inbuf, MC_CMD_LINK_PIOBUF_IN_LEN,
				  शून्य, 0, शून्य);
		अगर (rc) अणु
			netअगर_err(efx, drv, efx->net_dev,
				  "failed to link VI %u to PIO buffer %u (%d)\n",
				  nic_data->pio_ग_लिखो_vi_base + index, index,
				  rc);
			जाओ fail;
		पूर्ण
		netअगर_dbg(efx, probe, efx->net_dev,
			  "linked VI %u to PIO buffer %u\n",
			  nic_data->pio_ग_लिखो_vi_base + index, index);
	पूर्ण

	/* Link a buffer to each TX queue */
	efx_क्रम_each_channel(channel, efx) अणु
		/* Extra channels, even those with TXQs (PTP), करो not require
		 * PIO resources.
		 */
		अगर (!channel->type->want_pio ||
		    channel->channel >= efx->xdp_channel_offset)
			जारी;

		efx_क्रम_each_channel_tx_queue(tx_queue, channel) अणु
			/* We assign the PIO buffers to queues in
			 * reverse order to allow क्रम the following
			 * special हाल.
			 */
			offset = ((efx->tx_channel_offset + efx->n_tx_channels -
				   tx_queue->channel->channel - 1) *
				  efx_piobuf_size);
			index = offset / nic_data->piobuf_size;
			offset = offset % nic_data->piobuf_size;

			/* When the host page size is 4K, the first
			 * host page in the WC mapping may be within
			 * the same VI page as the last TX queue.  We
			 * can only link one buffer to each VI.
			 */
			अगर (tx_queue->queue == nic_data->pio_ग_लिखो_vi_base) अणु
				BUG_ON(index != 0);
				rc = 0;
			पूर्ण अन्यथा अणु
				MCDI_SET_DWORD(inbuf,
					       LINK_PIOBUF_IN_PIOBUF_HANDLE,
					       nic_data->piobuf_handle[index]);
				MCDI_SET_DWORD(inbuf,
					       LINK_PIOBUF_IN_TXQ_INSTANCE,
					       tx_queue->queue);
				rc = efx_mcdi_rpc(efx, MC_CMD_LINK_PIOBUF,
						  inbuf, MC_CMD_LINK_PIOBUF_IN_LEN,
						  शून्य, 0, शून्य);
			पूर्ण

			अगर (rc) अणु
				/* This is non-fatal; the TX path just
				 * won't use PIO क्रम this queue
				 */
				netअगर_err(efx, drv, efx->net_dev,
					  "failed to link VI %u to PIO buffer %u (%d)\n",
					  tx_queue->queue, index, rc);
				tx_queue->piobuf = शून्य;
			पूर्ण अन्यथा अणु
				tx_queue->piobuf =
					nic_data->pio_ग_लिखो_base +
					index * efx->vi_stride + offset;
				tx_queue->piobuf_offset = offset;
				netअगर_dbg(efx, probe, efx->net_dev,
					  "linked VI %u to PIO buffer %u offset %x addr %p\n",
					  tx_queue->queue, index,
					  tx_queue->piobuf_offset,
					  tx_queue->piobuf);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	/* inbuf was defined क्रम MC_CMD_LINK_PIOBUF.  We can use the same
	 * buffer क्रम MC_CMD_UNLINK_PIOBUF because it's लघुer.
	 */
	BUILD_BUG_ON(MC_CMD_LINK_PIOBUF_IN_LEN < MC_CMD_UNLINK_PIOBUF_IN_LEN);
	जबतक (index--) अणु
		MCDI_SET_DWORD(inbuf, UNLINK_PIOBUF_IN_TXQ_INSTANCE,
			       nic_data->pio_ग_लिखो_vi_base + index);
		efx_mcdi_rpc(efx, MC_CMD_UNLINK_PIOBUF,
			     inbuf, MC_CMD_UNLINK_PIOBUF_IN_LEN,
			     शून्य, 0, शून्य);
	पूर्ण
	वापस rc;
पूर्ण

अटल व्योम efx_ef10_क्रमget_old_piobufs(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_channel *channel;
	काष्ठा efx_tx_queue *tx_queue;

	/* All our existing PIO buffers went away */
	efx_क्रम_each_channel(channel, efx)
		efx_क्रम_each_channel_tx_queue(tx_queue, channel)
			tx_queue->piobuf = शून्य;
पूर्ण

#अन्यथा /* !EFX_USE_PIO */

अटल पूर्णांक efx_ef10_alloc_piobufs(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक n)
अणु
	वापस n == 0 ? 0 : -ENOBUFS;
पूर्ण

अटल पूर्णांक efx_ef10_link_piobufs(काष्ठा efx_nic *efx)
अणु
	वापस 0;
पूर्ण

अटल व्योम efx_ef10_मुक्त_piobufs(काष्ठा efx_nic *efx)
अणु
पूर्ण

अटल व्योम efx_ef10_क्रमget_old_piobufs(काष्ठा efx_nic *efx)
अणु
पूर्ण

#पूर्ण_अगर /* EFX_USE_PIO */

अटल व्योम efx_ef10_हटाओ(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

#अगर_घोषित CONFIG_SFC_SRIOV
	काष्ठा efx_ef10_nic_data *nic_data_pf;
	काष्ठा pci_dev *pci_dev_pf;
	काष्ठा efx_nic *efx_pf;
	काष्ठा ef10_vf *vf;

	अगर (efx->pci_dev->is_virtfn) अणु
		pci_dev_pf = efx->pci_dev->physfn;
		अगर (pci_dev_pf) अणु
			efx_pf = pci_get_drvdata(pci_dev_pf);
			nic_data_pf = efx_pf->nic_data;
			vf = nic_data_pf->vf + nic_data->vf_index;
			vf->efx = शून्य;
		पूर्ण अन्यथा
			netअगर_info(efx, drv, efx->net_dev,
				   "Could not get the PF id from VF\n");
	पूर्ण
#पूर्ण_अगर

	efx_ef10_cleanup_vlans(efx);
	mutex_destroy(&nic_data->vlan_lock);

	efx_ptp_हटाओ(efx);

	efx_mcdi_mon_हटाओ(efx);

	efx_mcdi_rx_मुक्त_indir_table(efx);

	अगर (nic_data->wc_membase)
		iounmap(nic_data->wc_membase);

	rc = efx_mcdi_मुक्त_vis(efx);
	WARN_ON(rc != 0);

	अगर (!nic_data->must_restore_piobufs)
		efx_ef10_मुक्त_piobufs(efx);

	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_primary_flag);
	device_हटाओ_file(&efx->pci_dev->dev, &dev_attr_link_control_flag);

	efx_mcdi_detach(efx);

	स_रखो(nic_data->udp_tunnels, 0, माप(nic_data->udp_tunnels));
	mutex_lock(&nic_data->udp_tunnels_lock);
	(व्योम)efx_ef10_set_udp_tnl_ports(efx, true);
	mutex_unlock(&nic_data->udp_tunnels_lock);

	mutex_destroy(&nic_data->udp_tunnels_lock);

	efx_mcdi_fini(efx);
	efx_nic_मुक्त_buffer(efx, &nic_data->mcdi_buf);
	kमुक्त(nic_data);
पूर्ण

अटल पूर्णांक efx_ef10_probe_pf(काष्ठा efx_nic *efx)
अणु
	वापस efx_ef10_probe(efx);
पूर्ण

पूर्णांक efx_ef10_vadaptor_query(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id,
			    u32 *port_flags, u32 *vadaptor_flags,
			    अचिन्हित पूर्णांक *vlan_tags)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VADAPTOR_QUERY_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_VADAPTOR_QUERY_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_VADAPTOR_QUERY_LBN)) अणु
		MCDI_SET_DWORD(inbuf, VADAPTOR_QUERY_IN_UPSTREAM_PORT_ID,
			       port_id);

		rc = efx_mcdi_rpc(efx, MC_CMD_VADAPTOR_QUERY, inbuf, माप(inbuf),
				  outbuf, माप(outbuf), &outlen);
		अगर (rc)
			वापस rc;

		अगर (outlen < माप(outbuf)) अणु
			rc = -EIO;
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (port_flags)
		*port_flags = MCDI_DWORD(outbuf, VADAPTOR_QUERY_OUT_PORT_FLAGS);
	अगर (vadaptor_flags)
		*vadaptor_flags =
			MCDI_DWORD(outbuf, VADAPTOR_QUERY_OUT_VADAPTOR_FLAGS);
	अगर (vlan_tags)
		*vlan_tags =
			MCDI_DWORD(outbuf,
				   VADAPTOR_QUERY_OUT_NUM_AVAILABLE_VLAN_TAGS);

	वापस 0;
पूर्ण

पूर्णांक efx_ef10_vadaptor_alloc(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VADAPTOR_ALLOC_IN_LEN);

	MCDI_SET_DWORD(inbuf, VADAPTOR_ALLOC_IN_UPSTREAM_PORT_ID, port_id);
	वापस efx_mcdi_rpc(efx, MC_CMD_VADAPTOR_ALLOC, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

पूर्णांक efx_ef10_vadaptor_मुक्त(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VADAPTOR_FREE_IN_LEN);

	MCDI_SET_DWORD(inbuf, VADAPTOR_FREE_IN_UPSTREAM_PORT_ID, port_id);
	वापस efx_mcdi_rpc(efx, MC_CMD_VADAPTOR_FREE, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

पूर्णांक efx_ef10_vport_add_mac(काष्ठा efx_nic *efx,
			   अचिन्हित पूर्णांक port_id, u8 *mac)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_ADD_MAC_ADDRESS_IN_LEN);

	MCDI_SET_DWORD(inbuf, VPORT_ADD_MAC_ADDRESS_IN_VPORT_ID, port_id);
	ether_addr_copy(MCDI_PTR(inbuf, VPORT_ADD_MAC_ADDRESS_IN_MACADDR), mac);

	वापस efx_mcdi_rpc(efx, MC_CMD_VPORT_ADD_MAC_ADDRESS, inbuf,
			    माप(inbuf), शून्य, 0, शून्य);
पूर्ण

पूर्णांक efx_ef10_vport_del_mac(काष्ठा efx_nic *efx,
			   अचिन्हित पूर्णांक port_id, u8 *mac)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_DEL_MAC_ADDRESS_IN_LEN);

	MCDI_SET_DWORD(inbuf, VPORT_DEL_MAC_ADDRESS_IN_VPORT_ID, port_id);
	ether_addr_copy(MCDI_PTR(inbuf, VPORT_DEL_MAC_ADDRESS_IN_MACADDR), mac);

	वापस efx_mcdi_rpc(efx, MC_CMD_VPORT_DEL_MAC_ADDRESS, inbuf,
			    माप(inbuf), शून्य, 0, शून्य);
पूर्ण

#अगर_घोषित CONFIG_SFC_SRIOV
अटल पूर्णांक efx_ef10_probe_vf(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;
	काष्ठा pci_dev *pci_dev_pf;

	/* If the parent PF has no VF data काष्ठाure, it करोesn't know about this
	 * VF so fail probe.  The VF needs to be re-created.  This can happen
	 * अगर the PF driver is unloaded जबतक the VF is asचिन्हित to a guest.
	 */
	pci_dev_pf = efx->pci_dev->physfn;
	अगर (pci_dev_pf) अणु
		काष्ठा efx_nic *efx_pf = pci_get_drvdata(pci_dev_pf);
		काष्ठा efx_ef10_nic_data *nic_data_pf = efx_pf->nic_data;

		अगर (!nic_data_pf->vf) अणु
			netअगर_info(efx, drv, efx->net_dev,
				   "The VF cannot link to its parent PF; "
				   "please destroy and re-create the VF\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	rc = efx_ef10_probe(efx);
	अगर (rc)
		वापस rc;

	rc = efx_ef10_get_vf_index(efx);
	अगर (rc)
		जाओ fail;

	अगर (efx->pci_dev->is_virtfn) अणु
		अगर (efx->pci_dev->physfn) अणु
			काष्ठा efx_nic *efx_pf =
				pci_get_drvdata(efx->pci_dev->physfn);
			काष्ठा efx_ef10_nic_data *nic_data_p = efx_pf->nic_data;
			काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

			nic_data_p->vf[nic_data->vf_index].efx = efx;
			nic_data_p->vf[nic_data->vf_index].pci_dev =
				efx->pci_dev;
		पूर्ण अन्यथा
			netअगर_info(efx, drv, efx->net_dev,
				   "Could not get the PF id from VF\n");
	पूर्ण

	वापस 0;

fail:
	efx_ef10_हटाओ(efx);
	वापस rc;
पूर्ण
#अन्यथा
अटल पूर्णांक efx_ef10_probe_vf(काष्ठा efx_nic *efx __attribute__ ((unused)))
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक efx_ef10_alloc_vis(काष्ठा efx_nic *efx,
			      अचिन्हित पूर्णांक min_vis, अचिन्हित पूर्णांक max_vis)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	वापस efx_mcdi_alloc_vis(efx, min_vis, max_vis, &nic_data->vi_base,
				  &nic_data->n_allocated_vis);
पूर्ण

/* Note that the failure path of this function करोes not मुक्त
 * resources, as this will be करोne by efx_ef10_हटाओ().
 */
अटल पूर्णांक efx_ef10_dimension_resources(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक min_vis = max_t(अचिन्हित पूर्णांक, efx->tx_queues_per_channel,
				     efx_separate_tx_channels ? 2 : 1);
	अचिन्हित पूर्णांक channel_vis, pio_ग_लिखो_vi_base, max_vis;
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक uc_mem_map_size, wc_mem_map_size;
	व्योम __iomem *membase;
	पूर्णांक rc;

	channel_vis = max(efx->n_channels,
			  ((efx->n_tx_channels + efx->n_extra_tx_channels) *
			   efx->tx_queues_per_channel) +
			   efx->n_xdp_channels * efx->xdp_tx_per_channel);
	अगर (efx->max_vis && efx->max_vis < channel_vis) अणु
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Reducing channel VIs from %u to %u\n",
			  channel_vis, efx->max_vis);
		channel_vis = efx->max_vis;
	पूर्ण

#अगर_घोषित EFX_USE_PIO
	/* Try to allocate PIO buffers अगर wanted and अगर the full
	 * number of PIO buffers would be sufficient to allocate one
	 * copy-buffer per TX channel.  Failure is non-fatal, as there
	 * are only a small number of PIO buffers shared between all
	 * functions of the controller.
	 */
	अगर (efx_piobuf_size != 0 &&
	    nic_data->piobuf_size / efx_piobuf_size * EF10_TX_PIOBUF_COUNT >=
	    efx->n_tx_channels) अणु
		अचिन्हित पूर्णांक n_piobufs =
			DIV_ROUND_UP(efx->n_tx_channels,
				     nic_data->piobuf_size / efx_piobuf_size);

		rc = efx_ef10_alloc_piobufs(efx, n_piobufs);
		अगर (rc == -ENOSPC)
			netअगर_dbg(efx, probe, efx->net_dev,
				  "out of PIO buffers; cannot allocate more\n");
		अन्यथा अगर (rc == -EPERM)
			netअगर_dbg(efx, probe, efx->net_dev,
				  "not permitted to allocate PIO buffers\n");
		अन्यथा अगर (rc)
			netअगर_err(efx, probe, efx->net_dev,
				  "failed to allocate PIO buffers (%d)\n", rc);
		अन्यथा
			netअगर_dbg(efx, probe, efx->net_dev,
				  "allocated %u PIO buffers\n", n_piobufs);
	पूर्ण
#अन्यथा
	nic_data->n_piobufs = 0;
#पूर्ण_अगर

	/* PIO buffers should be mapped with ग_लिखो-combining enabled,
	 * and we want to make single UC and WC mappings rather than
	 * several of each (in fact that's the only option अगर host
	 * page size is >4K).  So we may allocate some extra VIs just
	 * क्रम writing PIO buffers through.
	 *
	 * The UC mapping contains (channel_vis - 1) complete VIs and the
	 * first 4K of the next VI.  Then the WC mapping begins with
	 * the reमुख्यder of this last VI.
	 */
	uc_mem_map_size = PAGE_ALIGN((channel_vis - 1) * efx->vi_stride +
				     ER_DZ_TX_PIOBUF);
	अगर (nic_data->n_piobufs) अणु
		/* pio_ग_लिखो_vi_base rounds करोwn to give the number of complete
		 * VIs inside the UC mapping.
		 */
		pio_ग_लिखो_vi_base = uc_mem_map_size / efx->vi_stride;
		wc_mem_map_size = (PAGE_ALIGN((pio_ग_लिखो_vi_base +
					       nic_data->n_piobufs) *
					      efx->vi_stride) -
				   uc_mem_map_size);
		max_vis = pio_ग_लिखो_vi_base + nic_data->n_piobufs;
	पूर्ण अन्यथा अणु
		pio_ग_लिखो_vi_base = 0;
		wc_mem_map_size = 0;
		max_vis = channel_vis;
	पूर्ण

	/* In हाल the last attached driver failed to मुक्त VIs, करो it now */
	rc = efx_mcdi_मुक्त_vis(efx);
	अगर (rc != 0)
		वापस rc;

	rc = efx_ef10_alloc_vis(efx, min_vis, max_vis);
	अगर (rc != 0)
		वापस rc;

	अगर (nic_data->n_allocated_vis < channel_vis) अणु
		netअगर_info(efx, drv, efx->net_dev,
			   "Could not allocate enough VIs to satisfy RSS"
			   " requirements. Performance may not be optimal.\n");
		/* We didn't get the VIs to populate our channels.
		 * We could keep what we got but then we'd have more
		 * पूर्णांकerrupts than we need.
		 * Instead calculate new max_channels and restart
		 */
		efx->max_channels = nic_data->n_allocated_vis;
		efx->max_tx_channels =
			nic_data->n_allocated_vis / efx->tx_queues_per_channel;

		efx_mcdi_मुक्त_vis(efx);
		वापस -EAGAIN;
	पूर्ण

	/* If we didn't get enough VIs to map all the PIO buffers, मुक्त the
	 * PIO buffers
	 */
	अगर (nic_data->n_piobufs &&
	    nic_data->n_allocated_vis <
	    pio_ग_लिखो_vi_base + nic_data->n_piobufs) अणु
		netअगर_dbg(efx, probe, efx->net_dev,
			  "%u VIs are not sufficient to map %u PIO buffers\n",
			  nic_data->n_allocated_vis, nic_data->n_piobufs);
		efx_ef10_मुक्त_piobufs(efx);
	पूर्ण

	/* Shrink the original UC mapping of the memory BAR */
	membase = ioremap(efx->membase_phys, uc_mem_map_size);
	अगर (!membase) अणु
		netअगर_err(efx, probe, efx->net_dev,
			  "could not shrink memory BAR to %x\n",
			  uc_mem_map_size);
		वापस -ENOMEM;
	पूर्ण
	iounmap(efx->membase);
	efx->membase = membase;

	/* Set up the WC mapping अगर needed */
	अगर (wc_mem_map_size) अणु
		nic_data->wc_membase = ioremap_wc(efx->membase_phys +
						  uc_mem_map_size,
						  wc_mem_map_size);
		अगर (!nic_data->wc_membase) अणु
			netअगर_err(efx, probe, efx->net_dev,
				  "could not allocate WC mapping of size %x\n",
				  wc_mem_map_size);
			वापस -ENOMEM;
		पूर्ण
		nic_data->pio_ग_लिखो_vi_base = pio_ग_लिखो_vi_base;
		nic_data->pio_ग_लिखो_base =
			nic_data->wc_membase +
			(pio_ग_लिखो_vi_base * efx->vi_stride + ER_DZ_TX_PIOBUF -
			 uc_mem_map_size);

		rc = efx_ef10_link_piobufs(efx);
		अगर (rc)
			efx_ef10_मुक्त_piobufs(efx);
	पूर्ण

	netअगर_dbg(efx, probe, efx->net_dev,
		  "memory BAR at %pa (virtual %p+%x UC, %p+%x WC)\n",
		  &efx->membase_phys, efx->membase, uc_mem_map_size,
		  nic_data->wc_membase, wc_mem_map_size);

	वापस 0;
पूर्ण

अटल व्योम efx_ef10_fini_nic(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	kमुक्त(nic_data->mc_stats);
	nic_data->mc_stats = शून्य;
पूर्ण

अटल पूर्णांक efx_ef10_init_nic(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	netdev_features_t hw_enc_features = 0;
	पूर्णांक rc;

	अगर (nic_data->must_check_datapath_caps) अणु
		rc = efx_ef10_init_datapath_caps(efx);
		अगर (rc)
			वापस rc;
		nic_data->must_check_datapath_caps = false;
	पूर्ण

	अगर (efx->must_पुनः_स्मृति_vis) अणु
		/* We cannot let the number of VIs change now */
		rc = efx_ef10_alloc_vis(efx, nic_data->n_allocated_vis,
					nic_data->n_allocated_vis);
		अगर (rc)
			वापस rc;
		efx->must_पुनः_स्मृति_vis = false;
	पूर्ण

	nic_data->mc_stats = kदो_स्मृति(efx->num_mac_stats * माप(__le64),
				     GFP_KERNEL);
	अगर (!nic_data->mc_stats)
		वापस -ENOMEM;

	अगर (nic_data->must_restore_piobufs && nic_data->n_piobufs) अणु
		rc = efx_ef10_alloc_piobufs(efx, nic_data->n_piobufs);
		अगर (rc == 0) अणु
			rc = efx_ef10_link_piobufs(efx);
			अगर (rc)
				efx_ef10_मुक्त_piobufs(efx);
		पूर्ण

		/* Log an error on failure, but this is non-fatal.
		 * Permission errors are less important - we've presumably
		 * had the PIO buffer licence हटाओd.
		 */
		अगर (rc == -EPERM)
			netअगर_dbg(efx, drv, efx->net_dev,
				  "not permitted to restore PIO buffers\n");
		अन्यथा अगर (rc)
			netअगर_err(efx, drv, efx->net_dev,
				  "failed to restore PIO buffers (%d)\n", rc);
		nic_data->must_restore_piobufs = false;
	पूर्ण

	/* add encapsulated checksum offload features */
	अगर (efx_has_cap(efx, VXLAN_NVGRE) && !efx_ef10_is_vf(efx))
		hw_enc_features |= NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	/* add encapsulated TSO features */
	अगर (efx_has_cap(efx, TX_TSO_V2_ENCAP)) अणु
		netdev_features_t encap_tso_features;

		encap_tso_features = NETIF_F_GSO_UDP_TUNNEL | NETIF_F_GSO_GRE |
			NETIF_F_GSO_UDP_TUNNEL_CSUM | NETIF_F_GSO_GRE_CSUM;

		hw_enc_features |= encap_tso_features | NETIF_F_TSO;
		efx->net_dev->features |= encap_tso_features;
	पूर्ण
	efx->net_dev->hw_enc_features = hw_enc_features;

	/* करोn't fail init if RSS setup doesn't work */
	rc = efx->type->rx_push_rss_config(efx, false,
					   efx->rss_context.rx_indir_table, शून्य);

	वापस 0;
पूर्ण

अटल व्योम efx_ef10_table_reset_mc_allocations(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
#अगर_घोषित CONFIG_SFC_SRIOV
	अचिन्हित पूर्णांक i;
#पूर्ण_अगर

	/* All our allocations have been reset */
	efx->must_पुनः_स्मृति_vis = true;
	efx_mcdi_filter_table_reset_mc_allocations(efx);
	nic_data->must_restore_piobufs = true;
	efx_ef10_क्रमget_old_piobufs(efx);
	efx->rss_context.context_id = EFX_MCDI_RSS_CONTEXT_INVALID;

	/* Driver-created vचयनes and vports must be re-created */
	nic_data->must_probe_vचयनing = true;
	efx->vport_id = EVB_PORT_ID_ASSIGNED;
#अगर_घोषित CONFIG_SFC_SRIOV
	अगर (nic_data->vf)
		क्रम (i = 0; i < efx->vf_count; i++)
			nic_data->vf[i].vport_id = 0;
#पूर्ण_अगर
पूर्ण

अटल क्रमागत reset_type efx_ef10_map_reset_reason(क्रमागत reset_type reason)
अणु
	अगर (reason == RESET_TYPE_MC_FAILURE)
		वापस RESET_TYPE_DATAPATH;

	वापस efx_mcdi_map_reset_reason(reason);
पूर्ण

अटल पूर्णांक efx_ef10_map_reset_flags(u32 *flags)
अणु
	क्रमागत अणु
		EF10_RESET_PORT = ((ETH_RESET_MAC | ETH_RESET_PHY) <<
				   ETH_RESET_SHARED_SHIFT),
		EF10_RESET_MC = ((ETH_RESET_DMA | ETH_RESET_FILTER |
				  ETH_RESET_OFFLOAD | ETH_RESET_MAC |
				  ETH_RESET_PHY | ETH_RESET_MGMT) <<
				 ETH_RESET_SHARED_SHIFT)
	पूर्ण;

	/* We assume क्रम now that our PCI function is permitted to
	 * reset everything.
	 */

	अगर ((*flags & EF10_RESET_MC) == EF10_RESET_MC) अणु
		*flags &= ~EF10_RESET_MC;
		वापस RESET_TYPE_WORLD;
	पूर्ण

	अगर ((*flags & EF10_RESET_PORT) == EF10_RESET_PORT) अणु
		*flags &= ~EF10_RESET_PORT;
		वापस RESET_TYPE_ALL;
	पूर्ण

	/* no invisible reset implemented */

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक efx_ef10_reset(काष्ठा efx_nic *efx, क्रमागत reset_type reset_type)
अणु
	पूर्णांक rc = efx_mcdi_reset(efx, reset_type);

	/* Unprivileged functions वापस -EPERM, but need to वापस success
	 * here so that the datapath is brought back up.
	 */
	अगर (reset_type == RESET_TYPE_WORLD && rc == -EPERM)
		rc = 0;

	/* If it was a port reset, trigger पुनः_स्मृतिation of MC resources.
	 * Note that on an MC reset nothing needs to be करोne now because we'll
	 * detect the MC reset later and handle it then.
	 * For an FLR, we never get an MC reset event, but the MC has reset all
	 * resources asचिन्हित to us, so we have to trigger पुनः_स्मृतिation now.
	 */
	अगर ((reset_type == RESET_TYPE_ALL ||
	     reset_type == RESET_TYPE_MCDI_TIMEOUT) && !rc)
		efx_ef10_table_reset_mc_allocations(efx);
	वापस rc;
पूर्ण

#घोषणा EF10_DMA_STAT(ext_name, mcdi_name)			\
	[EF10_STAT_ ## ext_name] =				\
	अणु #ext_name, 64, 8 * MC_CMD_MAC_ ## mcdi_name पूर्ण
#घोषणा EF10_DMA_INVIS_STAT(पूर्णांक_name, mcdi_name)		\
	[EF10_STAT_ ## पूर्णांक_name] =				\
	अणु शून्य, 64, 8 * MC_CMD_MAC_ ## mcdi_name पूर्ण
#घोषणा EF10_OTHER_STAT(ext_name)				\
	[EF10_STAT_ ## ext_name] = अणु #ext_name, 0, 0 पूर्ण

अटल स्थिर काष्ठा efx_hw_stat_desc efx_ef10_stat_desc[EF10_STAT_COUNT] = अणु
	EF10_DMA_STAT(port_tx_bytes, TX_BYTES),
	EF10_DMA_STAT(port_tx_packets, TX_PKTS),
	EF10_DMA_STAT(port_tx_छोड़ो, TX_PAUSE_PKTS),
	EF10_DMA_STAT(port_tx_control, TX_CONTROL_PKTS),
	EF10_DMA_STAT(port_tx_unicast, TX_UNICAST_PKTS),
	EF10_DMA_STAT(port_tx_multicast, TX_MULTICAST_PKTS),
	EF10_DMA_STAT(port_tx_broadcast, TX_BROADCAST_PKTS),
	EF10_DMA_STAT(port_tx_lt64, TX_LT64_PKTS),
	EF10_DMA_STAT(port_tx_64, TX_64_PKTS),
	EF10_DMA_STAT(port_tx_65_to_127, TX_65_TO_127_PKTS),
	EF10_DMA_STAT(port_tx_128_to_255, TX_128_TO_255_PKTS),
	EF10_DMA_STAT(port_tx_256_to_511, TX_256_TO_511_PKTS),
	EF10_DMA_STAT(port_tx_512_to_1023, TX_512_TO_1023_PKTS),
	EF10_DMA_STAT(port_tx_1024_to_15xx, TX_1024_TO_15XX_PKTS),
	EF10_DMA_STAT(port_tx_15xx_to_jumbo, TX_15XX_TO_JUMBO_PKTS),
	EF10_DMA_STAT(port_rx_bytes, RX_BYTES),
	EF10_DMA_INVIS_STAT(port_rx_bytes_minus_good_bytes, RX_BAD_BYTES),
	EF10_OTHER_STAT(port_rx_good_bytes),
	EF10_OTHER_STAT(port_rx_bad_bytes),
	EF10_DMA_STAT(port_rx_packets, RX_PKTS),
	EF10_DMA_STAT(port_rx_good, RX_GOOD_PKTS),
	EF10_DMA_STAT(port_rx_bad, RX_BAD_FCS_PKTS),
	EF10_DMA_STAT(port_rx_छोड़ो, RX_PAUSE_PKTS),
	EF10_DMA_STAT(port_rx_control, RX_CONTROL_PKTS),
	EF10_DMA_STAT(port_rx_unicast, RX_UNICAST_PKTS),
	EF10_DMA_STAT(port_rx_multicast, RX_MULTICAST_PKTS),
	EF10_DMA_STAT(port_rx_broadcast, RX_BROADCAST_PKTS),
	EF10_DMA_STAT(port_rx_lt64, RX_UNDERSIZE_PKTS),
	EF10_DMA_STAT(port_rx_64, RX_64_PKTS),
	EF10_DMA_STAT(port_rx_65_to_127, RX_65_TO_127_PKTS),
	EF10_DMA_STAT(port_rx_128_to_255, RX_128_TO_255_PKTS),
	EF10_DMA_STAT(port_rx_256_to_511, RX_256_TO_511_PKTS),
	EF10_DMA_STAT(port_rx_512_to_1023, RX_512_TO_1023_PKTS),
	EF10_DMA_STAT(port_rx_1024_to_15xx, RX_1024_TO_15XX_PKTS),
	EF10_DMA_STAT(port_rx_15xx_to_jumbo, RX_15XX_TO_JUMBO_PKTS),
	EF10_DMA_STAT(port_rx_gtjumbo, RX_GTJUMBO_PKTS),
	EF10_DMA_STAT(port_rx_bad_gtjumbo, RX_JABBER_PKTS),
	EF10_DMA_STAT(port_rx_overflow, RX_OVERFLOW_PKTS),
	EF10_DMA_STAT(port_rx_align_error, RX_ALIGN_ERROR_PKTS),
	EF10_DMA_STAT(port_rx_length_error, RX_LENGTH_ERROR_PKTS),
	EF10_DMA_STAT(port_rx_nodesc_drops, RX_NODESC_DROPS),
	EFX_GENERIC_SW_STAT(rx_nodesc_trunc),
	EFX_GENERIC_SW_STAT(rx_noskb_drops),
	EF10_DMA_STAT(port_rx_pm_trunc_bb_overflow, PM_TRUNC_BB_OVERFLOW),
	EF10_DMA_STAT(port_rx_pm_discard_bb_overflow, PM_DISCARD_BB_OVERFLOW),
	EF10_DMA_STAT(port_rx_pm_trunc_vfअगरo_full, PM_TRUNC_VFIFO_FULL),
	EF10_DMA_STAT(port_rx_pm_discard_vfअगरo_full, PM_DISCARD_VFIFO_FULL),
	EF10_DMA_STAT(port_rx_pm_trunc_qbb, PM_TRUNC_QBB),
	EF10_DMA_STAT(port_rx_pm_discard_qbb, PM_DISCARD_QBB),
	EF10_DMA_STAT(port_rx_pm_discard_mapping, PM_DISCARD_MAPPING),
	EF10_DMA_STAT(port_rx_dp_q_disabled_packets, RXDP_Q_DISABLED_PKTS),
	EF10_DMA_STAT(port_rx_dp_di_dropped_packets, RXDP_DI_DROPPED_PKTS),
	EF10_DMA_STAT(port_rx_dp_streaming_packets, RXDP_STREAMING_PKTS),
	EF10_DMA_STAT(port_rx_dp_hlb_fetch, RXDP_HLB_FETCH_CONDITIONS),
	EF10_DMA_STAT(port_rx_dp_hlb_रुको, RXDP_HLB_WAIT_CONDITIONS),
	EF10_DMA_STAT(rx_unicast, VADAPTER_RX_UNICAST_PACKETS),
	EF10_DMA_STAT(rx_unicast_bytes, VADAPTER_RX_UNICAST_BYTES),
	EF10_DMA_STAT(rx_multicast, VADAPTER_RX_MULTICAST_PACKETS),
	EF10_DMA_STAT(rx_multicast_bytes, VADAPTER_RX_MULTICAST_BYTES),
	EF10_DMA_STAT(rx_broadcast, VADAPTER_RX_BROADCAST_PACKETS),
	EF10_DMA_STAT(rx_broadcast_bytes, VADAPTER_RX_BROADCAST_BYTES),
	EF10_DMA_STAT(rx_bad, VADAPTER_RX_BAD_PACKETS),
	EF10_DMA_STAT(rx_bad_bytes, VADAPTER_RX_BAD_BYTES),
	EF10_DMA_STAT(rx_overflow, VADAPTER_RX_OVERFLOW),
	EF10_DMA_STAT(tx_unicast, VADAPTER_TX_UNICAST_PACKETS),
	EF10_DMA_STAT(tx_unicast_bytes, VADAPTER_TX_UNICAST_BYTES),
	EF10_DMA_STAT(tx_multicast, VADAPTER_TX_MULTICAST_PACKETS),
	EF10_DMA_STAT(tx_multicast_bytes, VADAPTER_TX_MULTICAST_BYTES),
	EF10_DMA_STAT(tx_broadcast, VADAPTER_TX_BROADCAST_PACKETS),
	EF10_DMA_STAT(tx_broadcast_bytes, VADAPTER_TX_BROADCAST_BYTES),
	EF10_DMA_STAT(tx_bad, VADAPTER_TX_BAD_PACKETS),
	EF10_DMA_STAT(tx_bad_bytes, VADAPTER_TX_BAD_BYTES),
	EF10_DMA_STAT(tx_overflow, VADAPTER_TX_OVERFLOW),
	EF10_DMA_STAT(fec_uncorrected_errors, FEC_UNCORRECTED_ERRORS),
	EF10_DMA_STAT(fec_corrected_errors, FEC_CORRECTED_ERRORS),
	EF10_DMA_STAT(fec_corrected_symbols_lane0, FEC_CORRECTED_SYMBOLS_LANE0),
	EF10_DMA_STAT(fec_corrected_symbols_lane1, FEC_CORRECTED_SYMBOLS_LANE1),
	EF10_DMA_STAT(fec_corrected_symbols_lane2, FEC_CORRECTED_SYMBOLS_LANE2),
	EF10_DMA_STAT(fec_corrected_symbols_lane3, FEC_CORRECTED_SYMBOLS_LANE3),
	EF10_DMA_STAT(ctpio_vi_busy_fallback, CTPIO_VI_BUSY_FALLBACK),
	EF10_DMA_STAT(ctpio_दीर्घ_ग_लिखो_success, CTPIO_LONG_WRITE_SUCCESS),
	EF10_DMA_STAT(ctpio_missing_dbell_fail, CTPIO_MISSING_DBELL_FAIL),
	EF10_DMA_STAT(ctpio_overflow_fail, CTPIO_OVERFLOW_FAIL),
	EF10_DMA_STAT(ctpio_underflow_fail, CTPIO_UNDERFLOW_FAIL),
	EF10_DMA_STAT(ctpio_समयout_fail, CTPIO_TIMEOUT_FAIL),
	EF10_DMA_STAT(ctpio_noncontig_wr_fail, CTPIO_NONCONTIG_WR_FAIL),
	EF10_DMA_STAT(ctpio_frm_clobber_fail, CTPIO_FRM_CLOBBER_FAIL),
	EF10_DMA_STAT(ctpio_invalid_wr_fail, CTPIO_INVALID_WR_FAIL),
	EF10_DMA_STAT(ctpio_vi_clobber_fallback, CTPIO_VI_CLOBBER_FALLBACK),
	EF10_DMA_STAT(ctpio_unqualअगरied_fallback, CTPIO_UNQUALIFIED_FALLBACK),
	EF10_DMA_STAT(ctpio_runt_fallback, CTPIO_RUNT_FALLBACK),
	EF10_DMA_STAT(ctpio_success, CTPIO_SUCCESS),
	EF10_DMA_STAT(ctpio_fallback, CTPIO_FALLBACK),
	EF10_DMA_STAT(ctpio_poison, CTPIO_POISON),
	EF10_DMA_STAT(ctpio_erase, CTPIO_ERASE),
पूर्ण;

#घोषणा HUNT_COMMON_STAT_MASK ((1ULL << EF10_STAT_port_tx_bytes) |	\
			       (1ULL << EF10_STAT_port_tx_packets) |	\
			       (1ULL << EF10_STAT_port_tx_छोड़ो) |	\
			       (1ULL << EF10_STAT_port_tx_unicast) |	\
			       (1ULL << EF10_STAT_port_tx_multicast) |	\
			       (1ULL << EF10_STAT_port_tx_broadcast) |	\
			       (1ULL << EF10_STAT_port_rx_bytes) |	\
			       (1ULL <<                                 \
				EF10_STAT_port_rx_bytes_minus_good_bytes) | \
			       (1ULL << EF10_STAT_port_rx_good_bytes) |	\
			       (1ULL << EF10_STAT_port_rx_bad_bytes) |	\
			       (1ULL << EF10_STAT_port_rx_packets) |	\
			       (1ULL << EF10_STAT_port_rx_good) |	\
			       (1ULL << EF10_STAT_port_rx_bad) |	\
			       (1ULL << EF10_STAT_port_rx_छोड़ो) |	\
			       (1ULL << EF10_STAT_port_rx_control) |	\
			       (1ULL << EF10_STAT_port_rx_unicast) |	\
			       (1ULL << EF10_STAT_port_rx_multicast) |	\
			       (1ULL << EF10_STAT_port_rx_broadcast) |	\
			       (1ULL << EF10_STAT_port_rx_lt64) |	\
			       (1ULL << EF10_STAT_port_rx_64) |		\
			       (1ULL << EF10_STAT_port_rx_65_to_127) |	\
			       (1ULL << EF10_STAT_port_rx_128_to_255) |	\
			       (1ULL << EF10_STAT_port_rx_256_to_511) |	\
			       (1ULL << EF10_STAT_port_rx_512_to_1023) |\
			       (1ULL << EF10_STAT_port_rx_1024_to_15xx) |\
			       (1ULL << EF10_STAT_port_rx_15xx_to_jumbo) |\
			       (1ULL << EF10_STAT_port_rx_gtjumbo) |	\
			       (1ULL << EF10_STAT_port_rx_bad_gtjumbo) |\
			       (1ULL << EF10_STAT_port_rx_overflow) |	\
			       (1ULL << EF10_STAT_port_rx_nodesc_drops) |\
			       (1ULL << GENERIC_STAT_rx_nodesc_trunc) |	\
			       (1ULL << GENERIC_STAT_rx_noskb_drops))

/* On 7000 series NICs, these statistics are only provided by the 10G MAC.
 * For a 10G/40G चयनable port we करो not expose these because they might
 * not include all the packets they should.
 * On 8000 series NICs these statistics are always provided.
 */
#घोषणा HUNT_10G_ONLY_STAT_MASK ((1ULL << EF10_STAT_port_tx_control) |	\
				 (1ULL << EF10_STAT_port_tx_lt64) |	\
				 (1ULL << EF10_STAT_port_tx_64) |	\
				 (1ULL << EF10_STAT_port_tx_65_to_127) |\
				 (1ULL << EF10_STAT_port_tx_128_to_255) |\
				 (1ULL << EF10_STAT_port_tx_256_to_511) |\
				 (1ULL << EF10_STAT_port_tx_512_to_1023) |\
				 (1ULL << EF10_STAT_port_tx_1024_to_15xx) |\
				 (1ULL << EF10_STAT_port_tx_15xx_to_jumbo))

/* These statistics are only provided by the 40G MAC.  For a 10G/40G
 * चयनable port we करो expose these because the errors will otherwise
 * be silent.
 */
#घोषणा HUNT_40G_EXTRA_STAT_MASK ((1ULL << EF10_STAT_port_rx_align_error) |\
				  (1ULL << EF10_STAT_port_rx_length_error))

/* These statistics are only provided अगर the firmware supports the
 * capability PM_AND_RXDP_COUNTERS.
 */
#घोषणा HUNT_PM_AND_RXDP_STAT_MASK (					\
	(1ULL << EF10_STAT_port_rx_pm_trunc_bb_overflow) |		\
	(1ULL << EF10_STAT_port_rx_pm_discard_bb_overflow) |		\
	(1ULL << EF10_STAT_port_rx_pm_trunc_vfअगरo_full) |		\
	(1ULL << EF10_STAT_port_rx_pm_discard_vfअगरo_full) |		\
	(1ULL << EF10_STAT_port_rx_pm_trunc_qbb) |			\
	(1ULL << EF10_STAT_port_rx_pm_discard_qbb) |			\
	(1ULL << EF10_STAT_port_rx_pm_discard_mapping) |		\
	(1ULL << EF10_STAT_port_rx_dp_q_disabled_packets) |		\
	(1ULL << EF10_STAT_port_rx_dp_di_dropped_packets) |		\
	(1ULL << EF10_STAT_port_rx_dp_streaming_packets) |		\
	(1ULL << EF10_STAT_port_rx_dp_hlb_fetch) |			\
	(1ULL << EF10_STAT_port_rx_dp_hlb_रुको))

/* These statistics are only provided अगर the NIC supports MC_CMD_MAC_STATS_V2,
 * indicated by वापसing a value >= MC_CMD_MAC_NSTATS_V2 in
 * MC_CMD_GET_CAPABILITIES_V4_OUT_MAC_STATS_NUM_STATS.
 * These bits are in the second u64 of the raw mask.
 */
#घोषणा EF10_FEC_STAT_MASK (						\
	(1ULL << (EF10_STAT_fec_uncorrected_errors - 64)) |		\
	(1ULL << (EF10_STAT_fec_corrected_errors - 64)) |		\
	(1ULL << (EF10_STAT_fec_corrected_symbols_lane0 - 64)) |	\
	(1ULL << (EF10_STAT_fec_corrected_symbols_lane1 - 64)) |	\
	(1ULL << (EF10_STAT_fec_corrected_symbols_lane2 - 64)) |	\
	(1ULL << (EF10_STAT_fec_corrected_symbols_lane3 - 64)))

/* These statistics are only provided अगर the NIC supports MC_CMD_MAC_STATS_V3,
 * indicated by वापसing a value >= MC_CMD_MAC_NSTATS_V3 in
 * MC_CMD_GET_CAPABILITIES_V4_OUT_MAC_STATS_NUM_STATS.
 * These bits are in the second u64 of the raw mask.
 */
#घोषणा EF10_CTPIO_STAT_MASK (						\
	(1ULL << (EF10_STAT_ctpio_vi_busy_fallback - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_दीर्घ_ग_लिखो_success - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_missing_dbell_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_overflow_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_underflow_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_समयout_fail - 64)) |			\
	(1ULL << (EF10_STAT_ctpio_noncontig_wr_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_frm_clobber_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_invalid_wr_fail - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_vi_clobber_fallback - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_unqualअगरied_fallback - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_runt_fallback - 64)) |		\
	(1ULL << (EF10_STAT_ctpio_success - 64)) |			\
	(1ULL << (EF10_STAT_ctpio_fallback - 64)) |			\
	(1ULL << (EF10_STAT_ctpio_poison - 64)) |			\
	(1ULL << (EF10_STAT_ctpio_erase - 64)))

अटल u64 efx_ef10_raw_stat_mask(काष्ठा efx_nic *efx)
अणु
	u64 raw_mask = HUNT_COMMON_STAT_MASK;
	u32 port_caps = efx_mcdi_phy_get_caps(efx);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	अगर (!(efx->mcdi->fn_flags &
	      1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_LINKCTRL))
		वापस 0;

	अगर (port_caps & (1 << MC_CMD_PHY_CAP_40000FDX_LBN)) अणु
		raw_mask |= HUNT_40G_EXTRA_STAT_MASK;
		/* 8000 series have everything even at 40G */
		अगर (nic_data->datapath_caps2 &
		    (1 << MC_CMD_GET_CAPABILITIES_V2_OUT_MAC_STATS_40G_TX_SIZE_BINS_LBN))
			raw_mask |= HUNT_10G_ONLY_STAT_MASK;
	पूर्ण अन्यथा अणु
		raw_mask |= HUNT_10G_ONLY_STAT_MASK;
	पूर्ण

	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_PM_AND_RXDP_COUNTERS_LBN))
		raw_mask |= HUNT_PM_AND_RXDP_STAT_MASK;

	वापस raw_mask;
पूर्ण

अटल व्योम efx_ef10_get_stat_mask(काष्ठा efx_nic *efx, अचिन्हित दीर्घ *mask)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u64 raw_mask[2];

	raw_mask[0] = efx_ef10_raw_stat_mask(efx);

	/* Only show vadaptor stats when EVB capability is present */
	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_EVB_LBN)) अणु
		raw_mask[0] |= ~((1ULL << EF10_STAT_rx_unicast) - 1);
		raw_mask[1] = (1ULL << (EF10_STAT_V1_COUNT - 64)) - 1;
	पूर्ण अन्यथा अणु
		raw_mask[1] = 0;
	पूर्ण
	/* Only show FEC stats when NIC supports MC_CMD_MAC_STATS_V2 */
	अगर (efx->num_mac_stats >= MC_CMD_MAC_NSTATS_V2)
		raw_mask[1] |= EF10_FEC_STAT_MASK;

	/* CTPIO stats appear in V3. Only show them on devices that actually
	 * support CTPIO. Although this driver करोesn't use CTPIO others might,
	 * and we may be reporting the stats क्रम the underlying port.
	 */
	अगर (efx->num_mac_stats >= MC_CMD_MAC_NSTATS_V3 &&
	    (nic_data->datapath_caps2 &
	     (1 << MC_CMD_GET_CAPABILITIES_V4_OUT_CTPIO_LBN)))
		raw_mask[1] |= EF10_CTPIO_STAT_MASK;

#अगर BITS_PER_LONG == 64
	BUILD_BUG_ON(BITS_TO_LONGS(EF10_STAT_COUNT) != 2);
	mask[0] = raw_mask[0];
	mask[1] = raw_mask[1];
#अन्यथा
	BUILD_BUG_ON(BITS_TO_LONGS(EF10_STAT_COUNT) != 3);
	mask[0] = raw_mask[0] & 0xffffffff;
	mask[1] = raw_mask[0] >> 32;
	mask[2] = raw_mask[1] & 0xffffffff;
#पूर्ण_अगर
पूर्ण

अटल माप_प्रकार efx_ef10_describe_stats(काष्ठा efx_nic *efx, u8 *names)
अणु
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);

	efx_ef10_get_stat_mask(efx, mask);
	वापस efx_nic_describe_stats(efx_ef10_stat_desc, EF10_STAT_COUNT,
				      mask, names);
पूर्ण

अटल व्योम efx_ef10_get_fec_stats(काष्ठा efx_nic *efx,
				   काष्ठा ethtool_fec_stats *fec_stats)
अणु
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;

	efx_ef10_get_stat_mask(efx, mask);
	अगर (test_bit(EF10_STAT_fec_corrected_errors, mask))
		fec_stats->corrected_blocks.total =
			stats[EF10_STAT_fec_corrected_errors];
	अगर (test_bit(EF10_STAT_fec_uncorrected_errors, mask))
		fec_stats->uncorrectable_blocks.total =
			stats[EF10_STAT_fec_uncorrected_errors];
पूर्ण

अटल माप_प्रकार efx_ef10_update_stats_common(काष्ठा efx_nic *efx, u64 *full_stats,
					   काष्ठा rtnl_link_stats64 *core_stats)
अणु
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u64 *stats = nic_data->stats;
	माप_प्रकार stats_count = 0, index;

	efx_ef10_get_stat_mask(efx, mask);

	अगर (full_stats) अणु
		क्रम_each_set_bit(index, mask, EF10_STAT_COUNT) अणु
			अगर (efx_ef10_stat_desc[index].name) अणु
				*full_stats++ = stats[index];
				++stats_count;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!core_stats)
		वापस stats_count;

	अगर (nic_data->datapath_caps &
			1 << MC_CMD_GET_CAPABILITIES_OUT_EVB_LBN) अणु
		/* Use vadaptor stats. */
		core_stats->rx_packets = stats[EF10_STAT_rx_unicast] +
					 stats[EF10_STAT_rx_multicast] +
					 stats[EF10_STAT_rx_broadcast];
		core_stats->tx_packets = stats[EF10_STAT_tx_unicast] +
					 stats[EF10_STAT_tx_multicast] +
					 stats[EF10_STAT_tx_broadcast];
		core_stats->rx_bytes = stats[EF10_STAT_rx_unicast_bytes] +
				       stats[EF10_STAT_rx_multicast_bytes] +
				       stats[EF10_STAT_rx_broadcast_bytes];
		core_stats->tx_bytes = stats[EF10_STAT_tx_unicast_bytes] +
				       stats[EF10_STAT_tx_multicast_bytes] +
				       stats[EF10_STAT_tx_broadcast_bytes];
		core_stats->rx_dropped = stats[GENERIC_STAT_rx_nodesc_trunc] +
					 stats[GENERIC_STAT_rx_noskb_drops];
		core_stats->multicast = stats[EF10_STAT_rx_multicast];
		core_stats->rx_crc_errors = stats[EF10_STAT_rx_bad];
		core_stats->rx_fअगरo_errors = stats[EF10_STAT_rx_overflow];
		core_stats->rx_errors = core_stats->rx_crc_errors;
		core_stats->tx_errors = stats[EF10_STAT_tx_bad];
	पूर्ण अन्यथा अणु
		/* Use port stats. */
		core_stats->rx_packets = stats[EF10_STAT_port_rx_packets];
		core_stats->tx_packets = stats[EF10_STAT_port_tx_packets];
		core_stats->rx_bytes = stats[EF10_STAT_port_rx_bytes];
		core_stats->tx_bytes = stats[EF10_STAT_port_tx_bytes];
		core_stats->rx_dropped = stats[EF10_STAT_port_rx_nodesc_drops] +
					 stats[GENERIC_STAT_rx_nodesc_trunc] +
					 stats[GENERIC_STAT_rx_noskb_drops];
		core_stats->multicast = stats[EF10_STAT_port_rx_multicast];
		core_stats->rx_length_errors =
				stats[EF10_STAT_port_rx_gtjumbo] +
				stats[EF10_STAT_port_rx_length_error];
		core_stats->rx_crc_errors = stats[EF10_STAT_port_rx_bad];
		core_stats->rx_frame_errors =
				stats[EF10_STAT_port_rx_align_error];
		core_stats->rx_fअगरo_errors = stats[EF10_STAT_port_rx_overflow];
		core_stats->rx_errors = (core_stats->rx_length_errors +
					 core_stats->rx_crc_errors +
					 core_stats->rx_frame_errors);
	पूर्ण

	वापस stats_count;
पूर्ण

अटल माप_प्रकार efx_ef10_update_stats_pf(काष्ठा efx_nic *efx, u64 *full_stats,
				       काष्ठा rtnl_link_stats64 *core_stats)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);
	u64 *stats = nic_data->stats;

	efx_ef10_get_stat_mask(efx, mask);

	efx_nic_copy_stats(efx, nic_data->mc_stats);
	efx_nic_update_stats(efx_ef10_stat_desc, EF10_STAT_COUNT,
			     mask, stats, nic_data->mc_stats, false);

	/* Update derived statistics */
	efx_nic_fix_nodesc_drop_stat(efx,
				     &stats[EF10_STAT_port_rx_nodesc_drops]);
	/* MC Firmware पढ़ोs RX_BYTES and RX_GOOD_BYTES from the MAC.
	 * It then calculates RX_BAD_BYTES and DMAs it to us with RX_BYTES.
	 * We report these as port_rx_ stats. We are not given RX_GOOD_BYTES.
	 * Here we calculate port_rx_good_bytes.
	 */
	stats[EF10_STAT_port_rx_good_bytes] =
		stats[EF10_STAT_port_rx_bytes] -
		stats[EF10_STAT_port_rx_bytes_minus_good_bytes];

	/* The asynchronous पढ़ोs used to calculate RX_BAD_BYTES in
	 * MC Firmware are करोne such that we should not see an increase in
	 * RX_BAD_BYTES when a good packet has arrived. Unक्रमtunately this
	 * करोes mean that the stat can decrease at बार. Here we करो not
	 * update the stat unless it has increased or has gone to zero
	 * (In the हाल of the NIC rebooting).
	 * Please see Bug 33781 क्रम a discussion of why things work this way.
	 */
	efx_update_dअगरf_stat(&stats[EF10_STAT_port_rx_bad_bytes],
			     stats[EF10_STAT_port_rx_bytes_minus_good_bytes]);
	efx_update_sw_stats(efx, stats);

	वापस efx_ef10_update_stats_common(efx, full_stats, core_stats);
पूर्ण

अटल पूर्णांक efx_ef10_try_update_nic_stats_vf(काष्ठा efx_nic *efx)
	__must_hold(&efx->stats_lock)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_MAC_STATS_IN_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	DECLARE_BITMAP(mask, EF10_STAT_COUNT);
	__le64 generation_start, generation_end;
	u64 *stats = nic_data->stats;
	u32 dma_len = efx->num_mac_stats * माप(u64);
	काष्ठा efx_buffer stats_buf;
	__le64 *dma_stats;
	पूर्णांक rc;

	spin_unlock_bh(&efx->stats_lock);

	efx_ef10_get_stat_mask(efx, mask);

	rc = efx_nic_alloc_buffer(efx, &stats_buf, dma_len, GFP_KERNEL);
	अगर (rc) अणु
		spin_lock_bh(&efx->stats_lock);
		वापस rc;
	पूर्ण

	dma_stats = stats_buf.addr;
	dma_stats[efx->num_mac_stats - 1] = EFX_MC_STATS_GENERATION_INVALID;

	MCDI_SET_QWORD(inbuf, MAC_STATS_IN_DMA_ADDR, stats_buf.dma_addr);
	MCDI_POPULATE_DWORD_1(inbuf, MAC_STATS_IN_CMD,
			      MAC_STATS_IN_DMA, 1);
	MCDI_SET_DWORD(inbuf, MAC_STATS_IN_DMA_LEN, dma_len);
	MCDI_SET_DWORD(inbuf, MAC_STATS_IN_PORT_ID, EVB_PORT_ID_ASSIGNED);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_MAC_STATS, inbuf, माप(inbuf),
				शून्य, 0, शून्य);
	spin_lock_bh(&efx->stats_lock);
	अगर (rc) अणु
		/* Expect ENOENT अगर DMA queues have not been set up */
		अगर (rc != -ENOENT || atomic_पढ़ो(&efx->active_queues))
			efx_mcdi_display_error(efx, MC_CMD_MAC_STATS,
					       माप(inbuf), शून्य, 0, rc);
		जाओ out;
	पूर्ण

	generation_end = dma_stats[efx->num_mac_stats - 1];
	अगर (generation_end == EFX_MC_STATS_GENERATION_INVALID) अणु
		WARN_ON_ONCE(1);
		जाओ out;
	पूर्ण
	rmb();
	efx_nic_update_stats(efx_ef10_stat_desc, EF10_STAT_COUNT, mask,
			     stats, stats_buf.addr, false);
	rmb();
	generation_start = dma_stats[MC_CMD_MAC_GENERATION_START];
	अगर (generation_end != generation_start) अणु
		rc = -EAGAIN;
		जाओ out;
	पूर्ण

	efx_update_sw_stats(efx, stats);
out:
	efx_nic_मुक्त_buffer(efx, &stats_buf);
	वापस rc;
पूर्ण

अटल माप_प्रकार efx_ef10_update_stats_vf(काष्ठा efx_nic *efx, u64 *full_stats,
				       काष्ठा rtnl_link_stats64 *core_stats)
अणु
	अगर (efx_ef10_try_update_nic_stats_vf(efx))
		वापस 0;

	वापस efx_ef10_update_stats_common(efx, full_stats, core_stats);
पूर्ण

अटल माप_प्रकार efx_ef10_update_stats_atomic_vf(काष्ठा efx_nic *efx, u64 *full_stats,
					      काष्ठा rtnl_link_stats64 *core_stats)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	/* In atomic context, cannot update HW stats.  Just update the
	 * software stats and वापस so the caller can जारी.
	 */
	efx_update_sw_stats(efx, nic_data->stats);
	वापस efx_ef10_update_stats_common(efx, full_stats, core_stats);
पूर्ण

अटल व्योम efx_ef10_push_irq_moderation(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित पूर्णांक mode, usecs;
	efx_dword_t समयr_cmd;

	अगर (channel->irq_moderation_us) अणु
		mode = 3;
		usecs = channel->irq_moderation_us;
	पूर्ण अन्यथा अणु
		mode = 0;
		usecs = 0;
	पूर्ण

	अगर (EFX_EF10_WORKAROUND_61265(efx)) अणु
		MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_EVQ_TMR_IN_LEN);
		अचिन्हित पूर्णांक ns = usecs * 1000;

		MCDI_SET_DWORD(inbuf, SET_EVQ_TMR_IN_INSTANCE,
			       channel->channel);
		MCDI_SET_DWORD(inbuf, SET_EVQ_TMR_IN_TMR_LOAD_REQ_NS, ns);
		MCDI_SET_DWORD(inbuf, SET_EVQ_TMR_IN_TMR_RELOAD_REQ_NS, ns);
		MCDI_SET_DWORD(inbuf, SET_EVQ_TMR_IN_TMR_MODE, mode);

		efx_mcdi_rpc_async(efx, MC_CMD_SET_EVQ_TMR,
				   inbuf, माप(inbuf), 0, शून्य, 0);
	पूर्ण अन्यथा अगर (EFX_EF10_WORKAROUND_35388(efx)) अणु
		अचिन्हित पूर्णांक ticks = efx_usecs_to_ticks(efx, usecs);

		EFX_POPULATE_DWORD_3(समयr_cmd, ERF_DD_EVQ_IND_TIMER_FLAGS,
				     EFE_DD_EVQ_IND_TIMER_FLAGS,
				     ERF_DD_EVQ_IND_TIMER_MODE, mode,
				     ERF_DD_EVQ_IND_TIMER_VAL, ticks);
		efx_ग_लिखोd_page(efx, &समयr_cmd, ER_DD_EVQ_INसूचीECT,
				channel->channel);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ticks = efx_usecs_to_ticks(efx, usecs);

		EFX_POPULATE_DWORD_3(समयr_cmd, ERF_DZ_TC_TIMER_MODE, mode,
				     ERF_DZ_TC_TIMER_VAL, ticks,
				     ERF_FZ_TC_TMR_REL_VAL, ticks);
		efx_ग_लिखोd_page(efx, &समयr_cmd, ER_DZ_EVQ_TMR,
				channel->channel);
	पूर्ण
पूर्ण

अटल व्योम efx_ef10_get_wol_vf(काष्ठा efx_nic *efx,
				काष्ठा ethtool_wolinfo *wol) अणुपूर्ण

अटल पूर्णांक efx_ef10_set_wol_vf(काष्ठा efx_nic *efx, u32 type)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम efx_ef10_get_wol(काष्ठा efx_nic *efx, काष्ठा ethtool_wolinfo *wol)
अणु
	wol->supported = 0;
	wol->wolopts = 0;
	स_रखो(&wol->sopass, 0, माप(wol->sopass));
पूर्ण

अटल पूर्णांक efx_ef10_set_wol(काष्ठा efx_nic *efx, u32 type)
अणु
	अगर (type != 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम efx_ef10_mcdi_request(काष्ठा efx_nic *efx,
				  स्थिर efx_dword_t *hdr, माप_प्रकार hdr_len,
				  स्थिर efx_dword_t *sdu, माप_प्रकार sdu_len)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u8 *pdu = nic_data->mcdi_buf.addr;

	स_नकल(pdu, hdr, hdr_len);
	स_नकल(pdu + hdr_len, sdu, sdu_len);
	wmb();

	/* The hardware provides 'low' and 'high' (करोorbell) रेजिस्टरs
	 * क्रम passing the 64-bit address of an MCDI request to
	 * firmware.  However the dwords are swapped by firmware.  The
	 * least signअगरicant bits of the करोorbell are then 0 क्रम all
	 * MCDI requests due to alignment.
	 */
	_efx_ग_लिखोd(efx, cpu_to_le32((u64)nic_data->mcdi_buf.dma_addr >> 32),
		    ER_DZ_MC_DB_LWRD);
	_efx_ग_लिखोd(efx, cpu_to_le32((u32)nic_data->mcdi_buf.dma_addr),
		    ER_DZ_MC_DB_HWRD);
पूर्ण

अटल bool efx_ef10_mcdi_poll_response(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	स्थिर efx_dword_t hdr = *(स्थिर efx_dword_t *)nic_data->mcdi_buf.addr;

	rmb();
	वापस EFX_DWORD_FIELD(hdr, MCDI_HEADER_RESPONSE);
पूर्ण

अटल व्योम
efx_ef10_mcdi_पढ़ो_response(काष्ठा efx_nic *efx, efx_dword_t *outbuf,
			    माप_प्रकार offset, माप_प्रकार outlen)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	स्थिर u8 *pdu = nic_data->mcdi_buf.addr;

	स_नकल(outbuf, pdu + offset, outlen);
पूर्ण

अटल व्योम efx_ef10_mcdi_reboot_detected(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	/* All our allocations have been reset */
	efx_ef10_table_reset_mc_allocations(efx);

	/* The datapath firmware might have been changed */
	nic_data->must_check_datapath_caps = true;

	/* MAC statistics have been cleared on the NIC; clear the local
	 * statistic that we update with efx_update_dअगरf_stat().
	 */
	nic_data->stats[EF10_STAT_port_rx_bad_bytes] = 0;
पूर्ण

अटल पूर्णांक efx_ef10_mcdi_poll_reboot(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	rc = efx_ef10_get_warm_boot_count(efx);
	अगर (rc < 0) अणु
		/* The firmware is presumably in the process of
		 * rebooting.  However, we are supposed to report each
		 * reboot just once, so we must only करो that once we
		 * can पढ़ो and store the updated warm boot count.
		 */
		वापस 0;
	पूर्ण

	अगर (rc == nic_data->warm_boot_count)
		वापस 0;

	nic_data->warm_boot_count = rc;
	efx_ef10_mcdi_reboot_detected(efx);

	वापस -EIO;
पूर्ण

/* Handle an MSI पूर्णांकerrupt
 *
 * Handle an MSI hardware पूर्णांकerrupt.  This routine schedules event
 * queue processing.  No पूर्णांकerrupt acknowledgement cycle is necessary.
 * Also, we never need to check that the पूर्णांकerrupt is क्रम us, since
 * MSI पूर्णांकerrupts cannot be shared.
 */
अटल irqवापस_t efx_ef10_msi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा efx_msi_context *context = dev_id;
	काष्ठा efx_nic *efx = context->efx;

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "IRQ %d on CPU %d\n", irq, raw_smp_processor_id());

	अगर (likely(READ_ONCE(efx->irq_soft_enabled))) अणु
		/* Note test पूर्णांकerrupts */
		अगर (context->index == efx->irq_level)
			efx->last_irq_cpu = raw_smp_processor_id();

		/* Schedule processing of the channel */
		efx_schedule_channel_irq(efx->channel[context->index]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t efx_ef10_legacy_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा efx_nic *efx = dev_id;
	bool soft_enabled = READ_ONCE(efx->irq_soft_enabled);
	काष्ठा efx_channel *channel;
	efx_dword_t reg;
	u32 queues;

	/* Read the ISR which also ACKs the पूर्णांकerrupts */
	efx_पढ़ोd(efx, &reg, ER_DZ_BIU_INT_ISR);
	queues = EFX_DWORD_FIELD(reg, ERF_DZ_ISR_REG);

	अगर (queues == 0)
		वापस IRQ_NONE;

	अगर (likely(soft_enabled)) अणु
		/* Note test पूर्णांकerrupts */
		अगर (queues & (1U << efx->irq_level))
			efx->last_irq_cpu = raw_smp_processor_id();

		efx_क्रम_each_channel(channel, efx) अणु
			अगर (queues & 1)
				efx_schedule_channel_irq(channel);
			queues >>= 1;
		पूर्ण
	पूर्ण

	netअगर_vdbg(efx, पूर्णांकr, efx->net_dev,
		   "IRQ %d on CPU %d status " EFX_DWORD_FMT "\n",
		   irq, raw_smp_processor_id(), EFX_DWORD_VAL(reg));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक efx_ef10_irq_test_generate(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_TRIGGER_INTERRUPT_IN_LEN);

	अगर (efx_mcdi_set_workaround(efx, MC_CMD_WORKAROUND_BUG41750, true,
				    शून्य) == 0)
		वापस -ENOTSUPP;

	BUILD_BUG_ON(MC_CMD_TRIGGER_INTERRUPT_OUT_LEN != 0);

	MCDI_SET_DWORD(inbuf, TRIGGER_INTERRUPT_IN_INTR_LEVEL, efx->irq_level);
	वापस efx_mcdi_rpc(efx, MC_CMD_TRIGGER_INTERRUPT,
			    inbuf, माप(inbuf), शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_ef10_tx_probe(काष्ठा efx_tx_queue *tx_queue)
अणु
	/* low two bits of label are what we want क्रम type */
	BUILD_BUG_ON((EFX_TXQ_TYPE_OUTER_CSUM | EFX_TXQ_TYPE_INNER_CSUM) != 3);
	tx_queue->type = tx_queue->label & 3;
	वापस efx_nic_alloc_buffer(tx_queue->efx, &tx_queue->txd.buf,
				    (tx_queue->ptr_mask + 1) *
				    माप(efx_qword_t),
				    GFP_KERNEL);
पूर्ण

/* This ग_लिखोs to the TX_DESC_WPTR and also pushes data */
अटल अंतरभूत व्योम efx_ef10_push_tx_desc(काष्ठा efx_tx_queue *tx_queue,
					 स्थिर efx_qword_t *txd)
अणु
	अचिन्हित पूर्णांक ग_लिखो_ptr;
	efx_oword_t reg;

	ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
	EFX_POPULATE_OWORD_1(reg, ERF_DZ_TX_DESC_WPTR, ग_लिखो_ptr);
	reg.qword[0] = *txd;
	efx_ग_लिखोo_page(tx_queue->efx, &reg,
			ER_DZ_TX_DESC_UPD, tx_queue->queue);
पूर्ण

/* Add Firmware-Assisted TSO v2 option descriptors to a queue.
 */
पूर्णांक efx_ef10_tx_tso_desc(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb,
			 bool *data_mapped)
अणु
	काष्ठा efx_tx_buffer *buffer;
	u16 inner_ipv4_id = 0;
	u16 outer_ipv4_id = 0;
	काष्ठा tcphdr *tcp;
	काष्ठा iphdr *ip;
	u16 ip_tot_len;
	u32 seqnum;
	u32 mss;

	EFX_WARN_ON_ONCE_PARANOID(tx_queue->tso_version != 2);

	mss = skb_shinfo(skb)->gso_size;

	अगर (unlikely(mss < 4)) अणु
		WARN_ONCE(1, "MSS of %u is too small for TSO v2\n", mss);
		वापस -EINVAL;
	पूर्ण

	अगर (skb->encapsulation) अणु
		अगर (!tx_queue->tso_encap)
			वापस -EINVAL;
		ip = ip_hdr(skb);
		अगर (ip->version == 4)
			outer_ipv4_id = ntohs(ip->id);

		ip = inner_ip_hdr(skb);
		tcp = inner_tcp_hdr(skb);
	पूर्ण अन्यथा अणु
		ip = ip_hdr(skb);
		tcp = tcp_hdr(skb);
	पूर्ण

	/* 8000-series EF10 hardware requires that IP Total Length be
	 * greater than or equal to the value it will have in each segment
	 * (which is at most mss + 208 + TCP header length), but also less
	 * than (0x10000 - inner_network_header).  Otherwise the TCP
	 * checksum calculation will be broken क्रम encapsulated packets.
	 * We fill in ip->tot_len with 0xff30, which should satisfy the
	 * first requirement unless the MSS is ridiculously large (which
	 * should be impossible as the driver max MTU is 9216); it is
	 * guaranteed to satisfy the second as we only attempt TSO अगर
	 * inner_network_header <= 208.
	 */
	ip_tot_len = -EFX_TSO2_MAX_HDRLEN;
	EFX_WARN_ON_ONCE_PARANOID(mss + EFX_TSO2_MAX_HDRLEN +
				  (tcp->करोff << 2u) > ip_tot_len);

	अगर (ip->version == 4) अणु
		ip->tot_len = htons(ip_tot_len);
		ip->check = 0;
		inner_ipv4_id = ntohs(ip->id);
	पूर्ण अन्यथा अणु
		((काष्ठा ipv6hdr *)ip)->payload_len = htons(ip_tot_len);
	पूर्ण

	seqnum = ntohl(tcp->seq);

	buffer = efx_tx_queue_get_insert_buffer(tx_queue);

	buffer->flags = EFX_TX_BUF_OPTION;
	buffer->len = 0;
	buffer->unmap_len = 0;
	EFX_POPULATE_QWORD_5(buffer->option,
			ESF_DZ_TX_DESC_IS_OPT, 1,
			ESF_DZ_TX_OPTION_TYPE, ESE_DZ_TX_OPTION_DESC_TSO,
			ESF_DZ_TX_TSO_OPTION_TYPE,
			ESE_DZ_TX_TSO_OPTION_DESC_FATSO2A,
			ESF_DZ_TX_TSO_IP_ID, inner_ipv4_id,
			ESF_DZ_TX_TSO_TCP_SEQNO, seqnum
			);
	++tx_queue->insert_count;

	buffer = efx_tx_queue_get_insert_buffer(tx_queue);

	buffer->flags = EFX_TX_BUF_OPTION;
	buffer->len = 0;
	buffer->unmap_len = 0;
	EFX_POPULATE_QWORD_5(buffer->option,
			ESF_DZ_TX_DESC_IS_OPT, 1,
			ESF_DZ_TX_OPTION_TYPE, ESE_DZ_TX_OPTION_DESC_TSO,
			ESF_DZ_TX_TSO_OPTION_TYPE,
			ESE_DZ_TX_TSO_OPTION_DESC_FATSO2B,
			ESF_DZ_TX_TSO_OUTER_IPID, outer_ipv4_id,
			ESF_DZ_TX_TSO_TCP_MSS, mss
			);
	++tx_queue->insert_count;

	वापस 0;
पूर्ण

अटल u32 efx_ef10_tso_versions(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 tso_versions = 0;

	अगर (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_TX_TSO_LBN))
		tso_versions |= BIT(1);
	अगर (nic_data->datapath_caps2 &
	    (1 << MC_CMD_GET_CAPABILITIES_V2_OUT_TX_TSO_V2_LBN))
		tso_versions |= BIT(2);
	वापस tso_versions;
पूर्ण

अटल व्योम efx_ef10_tx_init(काष्ठा efx_tx_queue *tx_queue)
अणु
	bool csum_offload = tx_queue->type & EFX_TXQ_TYPE_OUTER_CSUM;
	bool inner_csum = tx_queue->type & EFX_TXQ_TYPE_INNER_CSUM;
	काष्ठा efx_channel *channel = tx_queue->channel;
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा efx_ef10_nic_data *nic_data;
	efx_qword_t *txd;
	पूर्णांक rc;

	nic_data = efx->nic_data;

	/* Only attempt to enable TX बारtamping अगर we have the license क्रम it,
	 * otherwise TXQ init will fail
	 */
	अगर (!(nic_data->licensed_features &
	      (1 << LICENSED_V3_FEATURES_TX_TIMESTAMPS_LBN))) अणु
		tx_queue->बारtamping = false;
		/* Disable sync events on this channel. */
		अगर (efx->type->ptp_set_ts_sync_events)
			efx->type->ptp_set_ts_sync_events(efx, false, false);
	पूर्ण

	/* TSOv2 is a limited resource that can only be configured on a limited
	 * number of queues. TSO without checksum offload is not really a thing,
	 * so we only enable it क्रम those queues.
	 * TSOv2 cannot be used with Hardware बारtamping, and is never needed
	 * क्रम XDP tx.
	 */
	अगर (efx_has_cap(efx, TX_TSO_V2)) अणु
		अगर ((csum_offload || inner_csum) &&
		    !tx_queue->बारtamping && !tx_queue->xdp_tx) अणु
			tx_queue->tso_version = 2;
			netअगर_dbg(efx, hw, efx->net_dev, "Using TSOv2 for channel %u\n",
				  channel->channel);
		पूर्ण
	पूर्ण अन्यथा अगर (efx_has_cap(efx, TX_TSO)) अणु
		tx_queue->tso_version = 1;
	पूर्ण

	rc = efx_mcdi_tx_init(tx_queue);
	अगर (rc)
		जाओ fail;

	/* A previous user of this TX queue might have set us up the
	 * bomb by writing a descriptor to the TX push collector but
	 * not the करोorbell.  (Each collector beदीर्घs to a port, not a
	 * queue or function, so cannot easily be reset.)  We must
	 * attempt to push a no-op descriptor in its place.
	 */
	tx_queue->buffer[0].flags = EFX_TX_BUF_OPTION;
	tx_queue->insert_count = 1;
	txd = efx_tx_desc(tx_queue, 0);
	EFX_POPULATE_QWORD_7(*txd,
			     ESF_DZ_TX_DESC_IS_OPT, true,
			     ESF_DZ_TX_OPTION_TYPE,
			     ESE_DZ_TX_OPTION_DESC_CRC_CSUM,
			     ESF_DZ_TX_OPTION_UDP_TCP_CSUM, csum_offload,
			     ESF_DZ_TX_OPTION_IP_CSUM, csum_offload && tx_queue->tso_version != 2,
			     ESF_DZ_TX_OPTION_INNER_UDP_TCP_CSUM, inner_csum,
			     ESF_DZ_TX_OPTION_INNER_IP_CSUM, inner_csum && tx_queue->tso_version != 2,
			     ESF_DZ_TX_TIMESTAMP, tx_queue->बारtamping);
	tx_queue->ग_लिखो_count = 1;

	अगर (tx_queue->tso_version == 2 && efx_has_cap(efx, TX_TSO_V2_ENCAP))
		tx_queue->tso_encap = true;

	wmb();
	efx_ef10_push_tx_desc(tx_queue, txd);

	वापस;

fail:
	netdev_WARN(efx->net_dev, "failed to initialise TXQ %d\n",
		    tx_queue->queue);
पूर्ण

/* This ग_लिखोs to the TX_DESC_WPTR; ग_लिखो poपूर्णांकer क्रम TX descriptor ring */
अटल अंतरभूत व्योम efx_ef10_notअगरy_tx_desc(काष्ठा efx_tx_queue *tx_queue)
अणु
	अचिन्हित पूर्णांक ग_लिखो_ptr;
	efx_dword_t reg;

	ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
	EFX_POPULATE_DWORD_1(reg, ERF_DZ_TX_DESC_WPTR_DWORD, ग_लिखो_ptr);
	efx_ग_लिखोd_page(tx_queue->efx, &reg,
			ER_DZ_TX_DESC_UPD_DWORD, tx_queue->queue);
पूर्ण

#घोषणा EFX_EF10_MAX_TX_DESCRIPTOR_LEN 0x3fff

अटल अचिन्हित पूर्णांक efx_ef10_tx_limit_len(काष्ठा efx_tx_queue *tx_queue,
					  dma_addr_t dma_addr, अचिन्हित पूर्णांक len)
अणु
	अगर (len > EFX_EF10_MAX_TX_DESCRIPTOR_LEN) अणु
		/* If we need to अवरोध across multiple descriptors we should
		 * stop at a page boundary. This assumes the length limit is
		 * greater than the page size.
		 */
		dma_addr_t end = dma_addr + EFX_EF10_MAX_TX_DESCRIPTOR_LEN;

		BUILD_BUG_ON(EFX_EF10_MAX_TX_DESCRIPTOR_LEN < EFX_PAGE_SIZE);
		len = (end & (~(EFX_PAGE_SIZE - 1))) - dma_addr;
	पूर्ण

	वापस len;
पूर्ण

अटल व्योम efx_ef10_tx_ग_लिखो(काष्ठा efx_tx_queue *tx_queue)
अणु
	अचिन्हित पूर्णांक old_ग_लिखो_count = tx_queue->ग_लिखो_count;
	काष्ठा efx_tx_buffer *buffer;
	अचिन्हित पूर्णांक ग_लिखो_ptr;
	efx_qword_t *txd;

	tx_queue->xmit_pending = false;
	अगर (unlikely(tx_queue->ग_लिखो_count == tx_queue->insert_count))
		वापस;

	करो अणु
		ग_लिखो_ptr = tx_queue->ग_लिखो_count & tx_queue->ptr_mask;
		buffer = &tx_queue->buffer[ग_लिखो_ptr];
		txd = efx_tx_desc(tx_queue, ग_लिखो_ptr);
		++tx_queue->ग_लिखो_count;

		/* Create TX descriptor ring entry */
		अगर (buffer->flags & EFX_TX_BUF_OPTION) अणु
			*txd = buffer->option;
			अगर (EFX_QWORD_FIELD(*txd, ESF_DZ_TX_OPTION_TYPE) == 1)
				/* PIO descriptor */
				tx_queue->packet_ग_लिखो_count = tx_queue->ग_लिखो_count;
		पूर्ण अन्यथा अणु
			tx_queue->packet_ग_लिखो_count = tx_queue->ग_लिखो_count;
			BUILD_BUG_ON(EFX_TX_BUF_CONT != 1);
			EFX_POPULATE_QWORD_3(
				*txd,
				ESF_DZ_TX_KER_CONT,
				buffer->flags & EFX_TX_BUF_CONT,
				ESF_DZ_TX_KER_BYTE_CNT, buffer->len,
				ESF_DZ_TX_KER_BUF_ADDR, buffer->dma_addr);
		पूर्ण
	पूर्ण जबतक (tx_queue->ग_लिखो_count != tx_queue->insert_count);

	wmb(); /* Ensure descriptors are written beक्रमe they are fetched */

	अगर (efx_nic_may_push_tx_desc(tx_queue, old_ग_लिखो_count)) अणु
		txd = efx_tx_desc(tx_queue,
				  old_ग_लिखो_count & tx_queue->ptr_mask);
		efx_ef10_push_tx_desc(tx_queue, txd);
		++tx_queue->pushes;
	पूर्ण अन्यथा अणु
		efx_ef10_notअगरy_tx_desc(tx_queue);
	पूर्ण
पूर्ण

अटल पूर्णांक efx_ef10_probe_multicast_chaining(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक enabled, implemented;
	bool want_workaround_26807;
	पूर्णांक rc;

	rc = efx_mcdi_get_workarounds(efx, &implemented, &enabled);
	अगर (rc == -ENOSYS) अणु
		/* GET_WORKAROUNDS was implemented beक्रमe this workaround,
		 * thus it must be unavailable in this firmware.
		 */
		nic_data->workaround_26807 = false;
		वापस 0;
	पूर्ण
	अगर (rc)
		वापस rc;
	want_workaround_26807 =
		implemented & MC_CMD_GET_WORKAROUNDS_OUT_BUG26807;
	nic_data->workaround_26807 =
		!!(enabled & MC_CMD_GET_WORKAROUNDS_OUT_BUG26807);

	अगर (want_workaround_26807 && !nic_data->workaround_26807) अणु
		अचिन्हित पूर्णांक flags;

		rc = efx_mcdi_set_workaround(efx,
					     MC_CMD_WORKAROUND_BUG26807,
					     true, &flags);
		अगर (!rc) अणु
			अगर (flags &
			    1 << MC_CMD_WORKAROUND_EXT_OUT_FLR_DONE_LBN) अणु
				netअगर_info(efx, drv, efx->net_dev,
					   "other functions on NIC have been reset\n");

				/* With MCFW v4.6.x and earlier, the
				 * boot count will have incremented,
				 * so re-पढ़ो the warm_boot_count
				 * value now to ensure this function
				 * करोesn't think it has changed next
				 * समय it checks.
				 */
				rc = efx_ef10_get_warm_boot_count(efx);
				अगर (rc >= 0) अणु
					nic_data->warm_boot_count = rc;
					rc = 0;
				पूर्ण
			पूर्ण
			nic_data->workaround_26807 = true;
		पूर्ण अन्यथा अगर (rc == -EPERM) अणु
			rc = 0;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_filter_table_probe(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc = efx_ef10_probe_multicast_chaining(efx);
	काष्ठा efx_mcdi_filter_vlan *vlan;

	अगर (rc)
		वापस rc;
	rc = efx_mcdi_filter_table_probe(efx, nic_data->workaround_26807);

	अगर (rc)
		वापस rc;

	list_क्रम_each_entry(vlan, &nic_data->vlan_list, list) अणु
		rc = efx_mcdi_filter_add_vlan(efx, vlan->vid);
		अगर (rc)
			जाओ fail_add_vlan;
	पूर्ण
	वापस 0;

fail_add_vlan:
	efx_mcdi_filter_table_हटाओ(efx);
	वापस rc;
पूर्ण

/* This creates an entry in the RX descriptor queue */
अटल अंतरभूत व्योम
efx_ef10_build_rx_desc(काष्ठा efx_rx_queue *rx_queue, अचिन्हित पूर्णांक index)
अणु
	काष्ठा efx_rx_buffer *rx_buf;
	efx_qword_t *rxd;

	rxd = efx_rx_desc(rx_queue, index);
	rx_buf = efx_rx_buffer(rx_queue, index);
	EFX_POPULATE_QWORD_2(*rxd,
			     ESF_DZ_RX_KER_BYTE_CNT, rx_buf->len,
			     ESF_DZ_RX_KER_BUF_ADDR, rx_buf->dma_addr);
पूर्ण

अटल व्योम efx_ef10_rx_ग_लिखो(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक ग_लिखो_count;
	efx_dword_t reg;

	/* Firmware requires that RX_DESC_WPTR be a multiple of 8 */
	ग_लिखो_count = rx_queue->added_count & ~7;
	अगर (rx_queue->notअगरied_count == ग_लिखो_count)
		वापस;

	करो
		efx_ef10_build_rx_desc(
			rx_queue,
			rx_queue->notअगरied_count & rx_queue->ptr_mask);
	जबतक (++rx_queue->notअगरied_count != ग_लिखो_count);

	wmb();
	EFX_POPULATE_DWORD_1(reg, ERF_DZ_RX_DESC_WPTR,
			     ग_लिखो_count & rx_queue->ptr_mask);
	efx_ग_लिखोd_page(efx, &reg, ER_DZ_RX_DESC_UPD,
			efx_rx_queue_index(rx_queue));
पूर्ण

अटल efx_mcdi_async_completer efx_ef10_rx_defer_refill_complete;

अटल व्योम efx_ef10_rx_defer_refill(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	MCDI_DECLARE_BUF(inbuf, MC_CMD_DRIVER_EVENT_IN_LEN);
	efx_qword_t event;

	EFX_POPULATE_QWORD_2(event,
			     ESF_DZ_EV_CODE, EFX_EF10_DRVGEN_EV,
			     ESF_DZ_EV_DATA, EFX_EF10_REFILL);

	MCDI_SET_DWORD(inbuf, DRIVER_EVENT_IN_EVQ, channel->channel);

	/* MCDI_SET_QWORD is not appropriate here since EFX_POPULATE_* has
	 * alपढ़ोy swapped the data to little-endian order.
	 */
	स_नकल(MCDI_PTR(inbuf, DRIVER_EVENT_IN_DATA), &event.u64[0],
	       माप(efx_qword_t));

	efx_mcdi_rpc_async(channel->efx, MC_CMD_DRIVER_EVENT,
			   inbuf, माप(inbuf), 0,
			   efx_ef10_rx_defer_refill_complete, 0);
पूर्ण

अटल व्योम
efx_ef10_rx_defer_refill_complete(काष्ठा efx_nic *efx, अचिन्हित दीर्घ cookie,
				  पूर्णांक rc, efx_dword_t *outbuf,
				  माप_प्रकार outlen_actual)
अणु
	/* nothing to करो */
पूर्ण

अटल पूर्णांक efx_ef10_ev_init(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_ef10_nic_data *nic_data;
	bool use_v2, cut_thru;

	nic_data = efx->nic_data;
	use_v2 = nic_data->datapath_caps2 &
			    1 << MC_CMD_GET_CAPABILITIES_V2_OUT_INIT_EVQ_V2_LBN;
	cut_thru = !(nic_data->datapath_caps &
			      1 << MC_CMD_GET_CAPABILITIES_OUT_RX_BATCHING_LBN);
	वापस efx_mcdi_ev_init(channel, cut_thru, use_v2);
पूर्ण

अटल व्योम efx_ef10_handle_rx_wrong_queue(काष्ठा efx_rx_queue *rx_queue,
					   अचिन्हित पूर्णांक rx_queue_label)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;

	netअगर_info(efx, hw, efx->net_dev,
		   "rx event arrived on queue %d labeled as queue %u\n",
		   efx_rx_queue_index(rx_queue), rx_queue_label);

	efx_schedule_reset(efx, RESET_TYPE_DISABLE);
पूर्ण

अटल व्योम
efx_ef10_handle_rx_bad_lbits(काष्ठा efx_rx_queue *rx_queue,
			     अचिन्हित पूर्णांक actual, अचिन्हित पूर्णांक expected)
अणु
	अचिन्हित पूर्णांक dropped = (actual - expected) & rx_queue->ptr_mask;
	काष्ठा efx_nic *efx = rx_queue->efx;

	netअगर_info(efx, hw, efx->net_dev,
		   "dropped %d events (index=%d expected=%d)\n",
		   dropped, actual, expected);

	efx_schedule_reset(efx, RESET_TYPE_DISABLE);
पूर्ण

/* partially received RX was पातed. clean up. */
अटल व्योम efx_ef10_handle_rx_पात(काष्ठा efx_rx_queue *rx_queue)
अणु
	अचिन्हित पूर्णांक rx_desc_ptr;

	netअगर_dbg(rx_queue->efx, hw, rx_queue->efx->net_dev,
		  "scattered RX aborted (dropping %u buffers)\n",
		  rx_queue->scatter_n);

	rx_desc_ptr = rx_queue->हटाओd_count & rx_queue->ptr_mask;

	efx_rx_packet(rx_queue, rx_desc_ptr, rx_queue->scatter_n,
		      0, EFX_RX_PKT_DISCARD);

	rx_queue->हटाओd_count += rx_queue->scatter_n;
	rx_queue->scatter_n = 0;
	rx_queue->scatter_len = 0;
	++efx_rx_queue_channel(rx_queue)->n_rx_nodesc_trunc;
पूर्ण

अटल u16 efx_ef10_handle_rx_event_errors(काष्ठा efx_channel *channel,
					   अचिन्हित पूर्णांक n_packets,
					   अचिन्हित पूर्णांक rx_encap_hdr,
					   अचिन्हित पूर्णांक rx_l3_class,
					   अचिन्हित पूर्णांक rx_l4_class,
					   स्थिर efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	bool handled = false;

	अगर (EFX_QWORD_FIELD(*event, ESF_DZ_RX_ECRC_ERR)) अणु
		अगर (!(efx->net_dev->features & NETIF_F_RXALL)) अणु
			अगर (!efx->loopback_selftest)
				channel->n_rx_eth_crc_err += n_packets;
			वापस EFX_RX_PKT_DISCARD;
		पूर्ण
		handled = true;
	पूर्ण
	अगर (EFX_QWORD_FIELD(*event, ESF_DZ_RX_IPCKSUM_ERR)) अणु
		अगर (unlikely(rx_encap_hdr != ESE_EZ_ENCAP_HDR_VXLAN &&
			     rx_l3_class != ESE_DZ_L3_CLASS_IP4 &&
			     rx_l3_class != ESE_DZ_L3_CLASS_IP4_FRAG &&
			     rx_l3_class != ESE_DZ_L3_CLASS_IP6 &&
			     rx_l3_class != ESE_DZ_L3_CLASS_IP6_FRAG))
			netdev_WARN(efx->net_dev,
				    "invalid class for RX_IPCKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अगर (!efx->loopback_selftest)
			*(rx_encap_hdr ?
			  &channel->n_rx_outer_ip_hdr_chksum_err :
			  &channel->n_rx_ip_hdr_chksum_err) += n_packets;
		वापस 0;
	पूर्ण
	अगर (EFX_QWORD_FIELD(*event, ESF_DZ_RX_TCPUDP_CKSUM_ERR)) अणु
		अगर (unlikely(rx_encap_hdr != ESE_EZ_ENCAP_HDR_VXLAN &&
			     ((rx_l3_class != ESE_DZ_L3_CLASS_IP4 &&
			       rx_l3_class != ESE_DZ_L3_CLASS_IP6) ||
			      (rx_l4_class != ESE_FZ_L4_CLASS_TCP &&
			       rx_l4_class != ESE_FZ_L4_CLASS_UDP))))
			netdev_WARN(efx->net_dev,
				    "invalid class for RX_TCPUDP_CKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अगर (!efx->loopback_selftest)
			*(rx_encap_hdr ?
			  &channel->n_rx_outer_tcp_udp_chksum_err :
			  &channel->n_rx_tcp_udp_chksum_err) += n_packets;
		वापस 0;
	पूर्ण
	अगर (EFX_QWORD_FIELD(*event, ESF_EZ_RX_IP_INNER_CHKSUM_ERR)) अणु
		अगर (unlikely(!rx_encap_hdr))
			netdev_WARN(efx->net_dev,
				    "invalid encapsulation type for RX_IP_INNER_CHKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अन्यथा अगर (unlikely(rx_l3_class != ESE_DZ_L3_CLASS_IP4 &&
				  rx_l3_class != ESE_DZ_L3_CLASS_IP4_FRAG &&
				  rx_l3_class != ESE_DZ_L3_CLASS_IP6 &&
				  rx_l3_class != ESE_DZ_L3_CLASS_IP6_FRAG))
			netdev_WARN(efx->net_dev,
				    "invalid class for RX_IP_INNER_CHKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अगर (!efx->loopback_selftest)
			channel->n_rx_inner_ip_hdr_chksum_err += n_packets;
		वापस 0;
	पूर्ण
	अगर (EFX_QWORD_FIELD(*event, ESF_EZ_RX_TCP_UDP_INNER_CHKSUM_ERR)) अणु
		अगर (unlikely(!rx_encap_hdr))
			netdev_WARN(efx->net_dev,
				    "invalid encapsulation type for RX_TCP_UDP_INNER_CHKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अन्यथा अगर (unlikely((rx_l3_class != ESE_DZ_L3_CLASS_IP4 &&
				   rx_l3_class != ESE_DZ_L3_CLASS_IP6) ||
				  (rx_l4_class != ESE_FZ_L4_CLASS_TCP &&
				   rx_l4_class != ESE_FZ_L4_CLASS_UDP)))
			netdev_WARN(efx->net_dev,
				    "invalid class for RX_TCP_UDP_INNER_CHKSUM_ERR: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		अगर (!efx->loopback_selftest)
			channel->n_rx_inner_tcp_udp_chksum_err += n_packets;
		वापस 0;
	पूर्ण

	WARN_ON(!handled); /* No error bits were recognised */
	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_handle_rx_event(काष्ठा efx_channel *channel,
				    स्थिर efx_qword_t *event)
अणु
	अचिन्हित पूर्णांक rx_bytes, next_ptr_lbits, rx_queue_label;
	अचिन्हित पूर्णांक rx_l3_class, rx_l4_class, rx_encap_hdr;
	अचिन्हित पूर्णांक n_descs, n_packets, i;
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा efx_rx_queue *rx_queue;
	efx_qword_t errors;
	bool rx_cont;
	u16 flags = 0;

	अगर (unlikely(READ_ONCE(efx->reset_pending)))
		वापस 0;

	/* Basic packet inक्रमmation */
	rx_bytes = EFX_QWORD_FIELD(*event, ESF_DZ_RX_BYTES);
	next_ptr_lbits = EFX_QWORD_FIELD(*event, ESF_DZ_RX_DSC_PTR_LBITS);
	rx_queue_label = EFX_QWORD_FIELD(*event, ESF_DZ_RX_QLABEL);
	rx_l3_class = EFX_QWORD_FIELD(*event, ESF_DZ_RX_L3_CLASS);
	rx_l4_class = EFX_QWORD_FIELD(*event, ESF_FZ_RX_L4_CLASS);
	rx_cont = EFX_QWORD_FIELD(*event, ESF_DZ_RX_CONT);
	rx_encap_hdr =
		nic_data->datapath_caps &
			(1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN) ?
		EFX_QWORD_FIELD(*event, ESF_EZ_RX_ENCAP_HDR) :
		ESE_EZ_ENCAP_HDR_NONE;

	अगर (EFX_QWORD_FIELD(*event, ESF_DZ_RX_DROP_EVENT))
		netdev_WARN(efx->net_dev, "saw RX_DROP_EVENT: event="
			    EFX_QWORD_FMT "\n",
			    EFX_QWORD_VAL(*event));

	rx_queue = efx_channel_get_rx_queue(channel);

	अगर (unlikely(rx_queue_label != efx_rx_queue_index(rx_queue)))
		efx_ef10_handle_rx_wrong_queue(rx_queue, rx_queue_label);

	n_descs = ((next_ptr_lbits - rx_queue->हटाओd_count) &
		   ((1 << ESF_DZ_RX_DSC_PTR_LBITS_WIDTH) - 1));

	अगर (n_descs != rx_queue->scatter_n + 1) अणु
		काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

		/* detect rx पात */
		अगर (unlikely(n_descs == rx_queue->scatter_n)) अणु
			अगर (rx_queue->scatter_n == 0 || rx_bytes != 0)
				netdev_WARN(efx->net_dev,
					    "invalid RX abort: scatter_n=%u event="
					    EFX_QWORD_FMT "\n",
					    rx_queue->scatter_n,
					    EFX_QWORD_VAL(*event));
			efx_ef10_handle_rx_पात(rx_queue);
			वापस 0;
		पूर्ण

		/* Check that RX completion merging is valid, i.e.
		 * the current firmware supports it and this is a
		 * non-scattered packet.
		 */
		अगर (!(nic_data->datapath_caps &
		      (1 << MC_CMD_GET_CAPABILITIES_OUT_RX_BATCHING_LBN)) ||
		    rx_queue->scatter_n != 0 || rx_cont) अणु
			efx_ef10_handle_rx_bad_lbits(
				rx_queue, next_ptr_lbits,
				(rx_queue->हटाओd_count +
				 rx_queue->scatter_n + 1) &
				((1 << ESF_DZ_RX_DSC_PTR_LBITS_WIDTH) - 1));
			वापस 0;
		पूर्ण

		/* Merged completion क्रम multiple non-scattered packets */
		rx_queue->scatter_n = 1;
		rx_queue->scatter_len = 0;
		n_packets = n_descs;
		++channel->n_rx_merge_events;
		channel->n_rx_merge_packets += n_packets;
		flags |= EFX_RX_PKT_PREFIX_LEN;
	पूर्ण अन्यथा अणु
		++rx_queue->scatter_n;
		rx_queue->scatter_len += rx_bytes;
		अगर (rx_cont)
			वापस 0;
		n_packets = 1;
	पूर्ण

	EFX_POPULATE_QWORD_5(errors, ESF_DZ_RX_ECRC_ERR, 1,
				     ESF_DZ_RX_IPCKSUM_ERR, 1,
				     ESF_DZ_RX_TCPUDP_CKSUM_ERR, 1,
				     ESF_EZ_RX_IP_INNER_CHKSUM_ERR, 1,
				     ESF_EZ_RX_TCP_UDP_INNER_CHKSUM_ERR, 1);
	EFX_AND_QWORD(errors, *event, errors);
	अगर (unlikely(!EFX_QWORD_IS_ZERO(errors))) अणु
		flags |= efx_ef10_handle_rx_event_errors(channel, n_packets,
							 rx_encap_hdr,
							 rx_l3_class, rx_l4_class,
							 event);
	पूर्ण अन्यथा अणु
		bool tcpudp = rx_l4_class == ESE_FZ_L4_CLASS_TCP ||
			      rx_l4_class == ESE_FZ_L4_CLASS_UDP;

		चयन (rx_encap_hdr) अणु
		हाल ESE_EZ_ENCAP_HDR_VXLAN: /* VxLAN or GENEVE */
			flags |= EFX_RX_PKT_CSUMMED; /* outer UDP csum */
			अगर (tcpudp)
				flags |= EFX_RX_PKT_CSUM_LEVEL; /* inner L4 */
			अवरोध;
		हाल ESE_EZ_ENCAP_HDR_GRE:
		हाल ESE_EZ_ENCAP_HDR_NONE:
			अगर (tcpudp)
				flags |= EFX_RX_PKT_CSUMMED;
			अवरोध;
		शेष:
			netdev_WARN(efx->net_dev,
				    "unknown encapsulation type: event="
				    EFX_QWORD_FMT "\n",
				    EFX_QWORD_VAL(*event));
		पूर्ण
	पूर्ण

	अगर (rx_l4_class == ESE_FZ_L4_CLASS_TCP)
		flags |= EFX_RX_PKT_TCP;

	channel->irq_mod_score += 2 * n_packets;

	/* Handle received packet(s) */
	क्रम (i = 0; i < n_packets; i++) अणु
		efx_rx_packet(rx_queue,
			      rx_queue->हटाओd_count & rx_queue->ptr_mask,
			      rx_queue->scatter_n, rx_queue->scatter_len,
			      flags);
		rx_queue->हटाओd_count += rx_queue->scatter_n;
	पूर्ण

	rx_queue->scatter_n = 0;
	rx_queue->scatter_len = 0;

	वापस n_packets;
पूर्ण

अटल u32 efx_ef10_extract_event_ts(efx_qword_t *event)
अणु
	u32 tstamp;

	tstamp = EFX_QWORD_FIELD(*event, TX_TIMESTAMP_EVENT_TSTAMP_DATA_HI);
	tstamp <<= 16;
	tstamp |= EFX_QWORD_FIELD(*event, TX_TIMESTAMP_EVENT_TSTAMP_DATA_LO);

	वापस tstamp;
पूर्ण

अटल व्योम
efx_ef10_handle_tx_event(काष्ठा efx_channel *channel, efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_tx_queue *tx_queue;
	अचिन्हित पूर्णांक tx_ev_desc_ptr;
	अचिन्हित पूर्णांक tx_ev_q_label;
	अचिन्हित पूर्णांक tx_ev_type;
	u64 ts_part;

	अगर (unlikely(READ_ONCE(efx->reset_pending)))
		वापस;

	अगर (unlikely(EFX_QWORD_FIELD(*event, ESF_DZ_TX_DROP_EVENT)))
		वापस;

	/* Get the transmit queue */
	tx_ev_q_label = EFX_QWORD_FIELD(*event, ESF_DZ_TX_QLABEL);
	tx_queue = channel->tx_queue + (tx_ev_q_label % EFX_MAX_TXQ_PER_CHANNEL);

	अगर (!tx_queue->बारtamping) अणु
		/* Transmit completion */
		tx_ev_desc_ptr = EFX_QWORD_FIELD(*event, ESF_DZ_TX_DESCR_INDX);
		efx_xmit_करोne(tx_queue, tx_ev_desc_ptr & tx_queue->ptr_mask);
		वापस;
	पूर्ण

	/* Transmit बारtamps are only available क्रम 8XXX series. They result
	 * in up to three events per packet. These occur in order, and are:
	 *  - the normal completion event (may be omitted)
	 *  - the low part of the बारtamp
	 *  - the high part of the बारtamp
	 *
	 * It's possible क्रम multiple completion events to appear beक्रमe the
	 * corresponding बारtamps. So we can क्रम example get:
	 *  COMP N
	 *  COMP N+1
	 *  TS_LO N
	 *  TS_HI N
	 *  TS_LO N+1
	 *  TS_HI N+1
	 *
	 * In addition it's also possible क्रम the adjacent completions to be
	 * merged, so we may not see COMP N above. As such, the completion
	 * events are not very useful here.
	 *
	 * Each part of the बारtamp is itself split across two 16 bit
	 * fields in the event.
	 */
	tx_ev_type = EFX_QWORD_FIELD(*event, ESF_EZ_TX_SOFT1);

	चयन (tx_ev_type) अणु
	हाल TX_TIMESTAMP_EVENT_TX_EV_COMPLETION:
		/* Ignore this event - see above. */
		अवरोध;

	हाल TX_TIMESTAMP_EVENT_TX_EV_TSTAMP_LO:
		ts_part = efx_ef10_extract_event_ts(event);
		tx_queue->completed_बारtamp_minor = ts_part;
		अवरोध;

	हाल TX_TIMESTAMP_EVENT_TX_EV_TSTAMP_HI:
		ts_part = efx_ef10_extract_event_ts(event);
		tx_queue->completed_बारtamp_major = ts_part;

		efx_xmit_करोne_single(tx_queue);
		अवरोध;

	शेष:
		netअगर_err(efx, hw, efx->net_dev,
			  "channel %d unknown tx event type %d (data "
			  EFX_QWORD_FMT ")\n",
			  channel->channel, tx_ev_type,
			  EFX_QWORD_VAL(*event));
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
efx_ef10_handle_driver_event(काष्ठा efx_channel *channel, efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	पूर्णांक subcode;

	subcode = EFX_QWORD_FIELD(*event, ESF_DZ_DRV_SUB_CODE);

	चयन (subcode) अणु
	हाल ESE_DZ_DRV_TIMER_EV:
	हाल ESE_DZ_DRV_WAKE_UP_EV:
		अवरोध;
	हाल ESE_DZ_DRV_START_UP_EV:
		/* event queue init complete. ok. */
		अवरोध;
	शेष:
		netअगर_err(efx, hw, efx->net_dev,
			  "channel %d unknown driver event type %d"
			  " (data " EFX_QWORD_FMT ")\n",
			  channel->channel, subcode,
			  EFX_QWORD_VAL(*event));

	पूर्ण
पूर्ण

अटल व्योम efx_ef10_handle_driver_generated_event(काष्ठा efx_channel *channel,
						   efx_qword_t *event)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	u32 subcode;

	subcode = EFX_QWORD_FIELD(*event, EFX_DWORD_0);

	चयन (subcode) अणु
	हाल EFX_EF10_TEST:
		channel->event_test_cpu = raw_smp_processor_id();
		अवरोध;
	हाल EFX_EF10_REFILL:
		/* The queue must be empty, so we won't receive any rx
		 * events, so efx_process_channel() won't refill the
		 * queue. Refill it here
		 */
		efx_fast_push_rx_descriptors(&channel->rx_queue, true);
		अवरोध;
	शेष:
		netअगर_err(efx, hw, efx->net_dev,
			  "channel %d unknown driver event type %u"
			  " (data " EFX_QWORD_FMT ")\n",
			  channel->channel, (अचिन्हित) subcode,
			  EFX_QWORD_VAL(*event));
	पूर्ण
पूर्ण

अटल पूर्णांक efx_ef10_ev_process(काष्ठा efx_channel *channel, पूर्णांक quota)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	efx_qword_t event, *p_event;
	अचिन्हित पूर्णांक पढ़ो_ptr;
	पूर्णांक ev_code;
	पूर्णांक spent = 0;

	अगर (quota <= 0)
		वापस spent;

	पढ़ो_ptr = channel->eventq_पढ़ो_ptr;

	क्रम (;;) अणु
		p_event = efx_event(channel, पढ़ो_ptr);
		event = *p_event;

		अगर (!efx_event_present(&event))
			अवरोध;

		EFX_SET_QWORD(*p_event);

		++पढ़ो_ptr;

		ev_code = EFX_QWORD_FIELD(event, ESF_DZ_EV_CODE);

		netअगर_vdbg(efx, drv, efx->net_dev,
			   "processing event on %d " EFX_QWORD_FMT "\n",
			   channel->channel, EFX_QWORD_VAL(event));

		चयन (ev_code) अणु
		हाल ESE_DZ_EV_CODE_MCDI_EV:
			efx_mcdi_process_event(channel, &event);
			अवरोध;
		हाल ESE_DZ_EV_CODE_RX_EV:
			spent += efx_ef10_handle_rx_event(channel, &event);
			अगर (spent >= quota) अणु
				/* XXX can we split a merged event to
				 * aव्योम going over-quota?
				 */
				spent = quota;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल ESE_DZ_EV_CODE_TX_EV:
			efx_ef10_handle_tx_event(channel, &event);
			अवरोध;
		हाल ESE_DZ_EV_CODE_DRIVER_EV:
			efx_ef10_handle_driver_event(channel, &event);
			अगर (++spent == quota)
				जाओ out;
			अवरोध;
		हाल EFX_EF10_DRVGEN_EV:
			efx_ef10_handle_driver_generated_event(channel, &event);
			अवरोध;
		शेष:
			netअगर_err(efx, hw, efx->net_dev,
				  "channel %d unknown event type %d"
				  " (data " EFX_QWORD_FMT ")\n",
				  channel->channel, ev_code,
				  EFX_QWORD_VAL(event));
		पूर्ण
	पूर्ण

out:
	channel->eventq_पढ़ो_ptr = पढ़ो_ptr;
	वापस spent;
पूर्ण

अटल व्योम efx_ef10_ev_पढ़ो_ack(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	efx_dword_t rptr;

	अगर (EFX_EF10_WORKAROUND_35388(efx)) अणु
		BUILD_BUG_ON(EFX_MIN_EVQ_SIZE <
			     (1 << ERF_DD_EVQ_IND_RPTR_WIDTH));
		BUILD_BUG_ON(EFX_MAX_EVQ_SIZE >
			     (1 << 2 * ERF_DD_EVQ_IND_RPTR_WIDTH));

		EFX_POPULATE_DWORD_2(rptr, ERF_DD_EVQ_IND_RPTR_FLAGS,
				     EFE_DD_EVQ_IND_RPTR_FLAGS_HIGH,
				     ERF_DD_EVQ_IND_RPTR,
				     (channel->eventq_पढ़ो_ptr &
				      channel->eventq_mask) >>
				     ERF_DD_EVQ_IND_RPTR_WIDTH);
		efx_ग_लिखोd_page(efx, &rptr, ER_DD_EVQ_INसूचीECT,
				channel->channel);
		EFX_POPULATE_DWORD_2(rptr, ERF_DD_EVQ_IND_RPTR_FLAGS,
				     EFE_DD_EVQ_IND_RPTR_FLAGS_LOW,
				     ERF_DD_EVQ_IND_RPTR,
				     channel->eventq_पढ़ो_ptr &
				     ((1 << ERF_DD_EVQ_IND_RPTR_WIDTH) - 1));
		efx_ग_लिखोd_page(efx, &rptr, ER_DD_EVQ_INसूचीECT,
				channel->channel);
	पूर्ण अन्यथा अणु
		EFX_POPULATE_DWORD_1(rptr, ERF_DZ_EVQ_RPTR,
				     channel->eventq_पढ़ो_ptr &
				     channel->eventq_mask);
		efx_ग_लिखोd_page(efx, &rptr, ER_DZ_EVQ_RPTR, channel->channel);
	पूर्ण
पूर्ण

अटल व्योम efx_ef10_ev_test_generate(काष्ठा efx_channel *channel)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_DRIVER_EVENT_IN_LEN);
	काष्ठा efx_nic *efx = channel->efx;
	efx_qword_t event;
	पूर्णांक rc;

	EFX_POPULATE_QWORD_2(event,
			     ESF_DZ_EV_CODE, EFX_EF10_DRVGEN_EV,
			     ESF_DZ_EV_DATA, EFX_EF10_TEST);

	MCDI_SET_DWORD(inbuf, DRIVER_EVENT_IN_EVQ, channel->channel);

	/* MCDI_SET_QWORD is not appropriate here since EFX_POPULATE_* has
	 * alपढ़ोy swapped the data to little-endian order.
	 */
	स_नकल(MCDI_PTR(inbuf, DRIVER_EVENT_IN_DATA), &event.u64[0],
	       माप(efx_qword_t));

	rc = efx_mcdi_rpc(efx, MC_CMD_DRIVER_EVENT, inbuf, माप(inbuf),
			  शून्य, 0, शून्य);
	अगर (rc != 0)
		जाओ fail;

	वापस;

fail:
	WARN_ON(true);
	netअगर_err(efx, hw, efx->net_dev, "%s: failed rc=%d\n", __func__, rc);
पूर्ण

अटल व्योम efx_ef10_prepare_flr(काष्ठा efx_nic *efx)
अणु
	atomic_set(&efx->active_queues, 0);
पूर्ण

अटल पूर्णांक efx_ef10_vport_set_mac_address(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u8 mac_old[ETH_ALEN];
	पूर्णांक rc, rc2;

	/* Only reconfigure a PF-created vport */
	अगर (is_zero_ether_addr(nic_data->vport_mac))
		वापस 0;

	efx_device_detach_sync(efx);
	efx_net_stop(efx->net_dev);
	करोwn_ग_लिखो(&efx->filter_sem);
	efx_mcdi_filter_table_हटाओ(efx);
	up_ग_लिखो(&efx->filter_sem);

	rc = efx_ef10_vadaptor_मुक्त(efx, efx->vport_id);
	अगर (rc)
		जाओ restore_filters;

	ether_addr_copy(mac_old, nic_data->vport_mac);
	rc = efx_ef10_vport_del_mac(efx, efx->vport_id,
				    nic_data->vport_mac);
	अगर (rc)
		जाओ restore_vadaptor;

	rc = efx_ef10_vport_add_mac(efx, efx->vport_id,
				    efx->net_dev->dev_addr);
	अगर (!rc) अणु
		ether_addr_copy(nic_data->vport_mac, efx->net_dev->dev_addr);
	पूर्ण अन्यथा अणु
		rc2 = efx_ef10_vport_add_mac(efx, efx->vport_id, mac_old);
		अगर (rc2) अणु
			/* Failed to add original MAC, so clear vport_mac */
			eth_zero_addr(nic_data->vport_mac);
			जाओ reset_nic;
		पूर्ण
	पूर्ण

restore_vadaptor:
	rc2 = efx_ef10_vadaptor_alloc(efx, efx->vport_id);
	अगर (rc2)
		जाओ reset_nic;
restore_filters:
	करोwn_ग_लिखो(&efx->filter_sem);
	rc2 = efx_ef10_filter_table_probe(efx);
	up_ग_लिखो(&efx->filter_sem);
	अगर (rc2)
		जाओ reset_nic;

	rc2 = efx_net_खोलो(efx->net_dev);
	अगर (rc2)
		जाओ reset_nic;

	efx_device_attach_अगर_not_resetting(efx);

	वापस rc;

reset_nic:
	netअगर_err(efx, drv, efx->net_dev,
		  "Failed to restore when changing MAC address - scheduling reset\n");
	efx_schedule_reset(efx, RESET_TYPE_DATAPATH);

	वापस rc ? rc : rc2;
पूर्ण

अटल पूर्णांक efx_ef10_set_mac_address(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VADAPTOR_SET_MAC_IN_LEN);
	bool was_enabled = efx->port_enabled;
	पूर्णांक rc;

	efx_device_detach_sync(efx);
	efx_net_stop(efx->net_dev);

	mutex_lock(&efx->mac_lock);
	करोwn_ग_लिखो(&efx->filter_sem);
	efx_mcdi_filter_table_हटाओ(efx);

	ether_addr_copy(MCDI_PTR(inbuf, VADAPTOR_SET_MAC_IN_MACADDR),
			efx->net_dev->dev_addr);
	MCDI_SET_DWORD(inbuf, VADAPTOR_SET_MAC_IN_UPSTREAM_PORT_ID,
		       efx->vport_id);
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_VADAPTOR_SET_MAC, inbuf,
				माप(inbuf), शून्य, 0, शून्य);

	efx_ef10_filter_table_probe(efx);
	up_ग_लिखो(&efx->filter_sem);
	mutex_unlock(&efx->mac_lock);

	अगर (was_enabled)
		efx_net_खोलो(efx->net_dev);
	efx_device_attach_अगर_not_resetting(efx);

#अगर_घोषित CONFIG_SFC_SRIOV
	अगर (efx->pci_dev->is_virtfn && efx->pci_dev->physfn) अणु
		काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
		काष्ठा pci_dev *pci_dev_pf = efx->pci_dev->physfn;

		अगर (rc == -EPERM) अणु
			काष्ठा efx_nic *efx_pf;

			/* Switch to PF and change MAC address on vport */
			efx_pf = pci_get_drvdata(pci_dev_pf);

			rc = efx_ef10_sriov_set_vf_mac(efx_pf,
						       nic_data->vf_index,
						       efx->net_dev->dev_addr);
		पूर्ण अन्यथा अगर (!rc) अणु
			काष्ठा efx_nic *efx_pf = pci_get_drvdata(pci_dev_pf);
			काष्ठा efx_ef10_nic_data *nic_data = efx_pf->nic_data;
			अचिन्हित पूर्णांक i;

			/* MAC address successfully changed by VF (with MAC
			 * spoofing) so update the parent PF अगर possible.
			 */
			क्रम (i = 0; i < efx_pf->vf_count; ++i) अणु
				काष्ठा ef10_vf *vf = nic_data->vf + i;

				अगर (vf->efx == efx) अणु
					ether_addr_copy(vf->mac,
							efx->net_dev->dev_addr);
					वापस 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (rc == -EPERM) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Cannot change MAC address; use sfboot to enable"
			  " mac-spoofing on this interface\n");
	पूर्ण अन्यथा अगर (rc == -ENOSYS && !efx_ef10_is_vf(efx)) अणु
		/* If the active MCFW करोes not support MC_CMD_VADAPTOR_SET_MAC
		 * fall-back to the method of changing the MAC address on the
		 * vport.  This only applies to PFs because such versions of
		 * MCFW करो not support VFs.
		 */
		rc = efx_ef10_vport_set_mac_address(efx);
	पूर्ण अन्यथा अगर (rc) अणु
		efx_mcdi_display_error(efx, MC_CMD_VADAPTOR_SET_MAC,
				       माप(inbuf), शून्य, 0, rc);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_mac_reconfigure(काष्ठा efx_nic *efx, bool mtu_only)
अणु
	WARN_ON(!mutex_is_locked(&efx->mac_lock));

	efx_mcdi_filter_sync_rx_mode(efx);

	अगर (mtu_only && efx_has_cap(efx, SET_MAC_ENHANCED))
		वापस efx_mcdi_set_mtu(efx);
	वापस efx_mcdi_set_mac(efx);
पूर्ण

अटल पूर्णांक efx_ef10_start_bist(काष्ठा efx_nic *efx, u32 bist_type)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_START_BIST_IN_LEN);

	MCDI_SET_DWORD(inbuf, START_BIST_IN_TYPE, bist_type);
	वापस efx_mcdi_rpc(efx, MC_CMD_START_BIST, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

/* MC BISTs follow a dअगरferent poll mechanism to phy BISTs.
 * The BIST is करोne in the poll handler on the MC, and the MCDI command
 * will block until the BIST is करोne.
 */
अटल पूर्णांक efx_ef10_poll_bist(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;
	MCDI_DECLARE_BUF(outbuf, MC_CMD_POLL_BIST_OUT_LEN);
	माप_प्रकार outlen;
	u32 result;

	rc = efx_mcdi_rpc(efx, MC_CMD_POLL_BIST, शून्य, 0,
			   outbuf, माप(outbuf), &outlen);
	अगर (rc != 0)
		वापस rc;

	अगर (outlen < MC_CMD_POLL_BIST_OUT_LEN)
		वापस -EIO;

	result = MCDI_DWORD(outbuf, POLL_BIST_OUT_RESULT);
	चयन (result) अणु
	हाल MC_CMD_POLL_BIST_PASSED:
		netअगर_dbg(efx, hw, efx->net_dev, "BIST passed.\n");
		वापस 0;
	हाल MC_CMD_POLL_BIST_TIMEOUT:
		netअगर_err(efx, hw, efx->net_dev, "BIST timed out\n");
		वापस -EIO;
	हाल MC_CMD_POLL_BIST_FAILED:
		netअगर_err(efx, hw, efx->net_dev, "BIST failed.\n");
		वापस -EIO;
	शेष:
		netअगर_err(efx, hw, efx->net_dev,
			  "BIST returned unknown result %u", result);
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_ef10_run_bist(काष्ठा efx_nic *efx, u32 bist_type)
अणु
	पूर्णांक rc;

	netअगर_dbg(efx, drv, efx->net_dev, "starting BIST type %u\n", bist_type);

	rc = efx_ef10_start_bist(efx, bist_type);
	अगर (rc != 0)
		वापस rc;

	वापस efx_ef10_poll_bist(efx);
पूर्ण

अटल पूर्णांक
efx_ef10_test_chip(काष्ठा efx_nic *efx, काष्ठा efx_self_tests *tests)
अणु
	पूर्णांक rc, rc2;

	efx_reset_करोwn(efx, RESET_TYPE_WORLD);

	rc = efx_mcdi_rpc(efx, MC_CMD_ENABLE_OFFLINE_BIST,
			  शून्य, 0, शून्य, 0, शून्य);
	अगर (rc != 0)
		जाओ out;

	tests->memory = efx_ef10_run_bist(efx, MC_CMD_MC_MEM_BIST) ? -1 : 1;
	tests->रेजिस्टरs = efx_ef10_run_bist(efx, MC_CMD_REG_BIST) ? -1 : 1;

	rc = efx_mcdi_reset(efx, RESET_TYPE_WORLD);

out:
	अगर (rc == -EPERM)
		rc = 0;
	rc2 = efx_reset_up(efx, RESET_TYPE_WORLD, rc == 0);
	वापस rc ? rc : rc2;
पूर्ण

#अगर_घोषित CONFIG_SFC_MTD

काष्ठा efx_ef10_nvram_type_info अणु
	u16 type, type_mask;
	u8 port;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा efx_ef10_nvram_type_info efx_ef10_nvram_types[] = अणु
	अणु NVRAM_PARTITION_TYPE_MC_FIRMWARE,	   0,    0, "sfc_mcfw" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_MC_FIRMWARE_BACKUP, 0,    0, "sfc_mcfw_backup" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPANSION_ROM,	   0,    0, "sfc_exp_rom" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_STATIC_CONFIG,	   0,    0, "sfc_static_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_DYNAMIC_CONFIG,	   0,    0, "sfc_dynamic_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPROM_CONFIG_PORT0, 0,   0, "sfc_exp_rom_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPROM_CONFIG_PORT1, 0,   1, "sfc_exp_rom_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPROM_CONFIG_PORT2, 0,   2, "sfc_exp_rom_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPROM_CONFIG_PORT3, 0,   3, "sfc_exp_rom_cfg" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_LICENSE,		   0,    0, "sfc_license" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_PHY_MIN,		   0xff, 0, "sfc_phy_fw" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_MUM_FIRMWARE,	   0,    0, "sfc_mumfw" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_EXPANSION_UEFI,	   0,    0, "sfc_uefi" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_DYNCONFIG_DEFAULTS, 0,    0, "sfc_dynamic_cfg_dflt" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_ROMCONFIG_DEFAULTS, 0,    0, "sfc_exp_rom_cfg_dflt" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_STATUS,		   0,    0, "sfc_status" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_BUNDLE,		   0,    0, "sfc_bundle" पूर्ण,
	अणु NVRAM_PARTITION_TYPE_BUNDLE_METADATA,	   0,    0, "sfc_bundle_metadata" पूर्ण,
पूर्ण;
#घोषणा EF10_NVRAM_PARTITION_COUNT	ARRAY_SIZE(efx_ef10_nvram_types)

अटल पूर्णांक efx_ef10_mtd_probe_partition(काष्ठा efx_nic *efx,
					काष्ठा efx_mcdi_mtd_partition *part,
					अचिन्हित पूर्णांक type,
					अचिन्हित दीर्घ *found)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_NVRAM_METADATA_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_METADATA_OUT_LENMAX);
	स्थिर काष्ठा efx_ef10_nvram_type_info *info;
	माप_प्रकार size, erase_size, outlen;
	पूर्णांक type_idx = 0;
	bool रक्षित;
	पूर्णांक rc;

	क्रम (type_idx = 0; ; type_idx++) अणु
		अगर (type_idx == EF10_NVRAM_PARTITION_COUNT)
			वापस -ENODEV;
		info = efx_ef10_nvram_types + type_idx;
		अगर ((type & ~info->type_mask) == info->type)
			अवरोध;
	पूर्ण
	अगर (info->port != efx_port_num(efx))
		वापस -ENODEV;

	rc = efx_mcdi_nvram_info(efx, type, &size, &erase_size, &रक्षित);
	अगर (rc)
		वापस rc;
	अगर (रक्षित &&
	    (type != NVRAM_PARTITION_TYPE_DYNCONFIG_DEFAULTS &&
	     type != NVRAM_PARTITION_TYPE_ROMCONFIG_DEFAULTS))
		/* Hide रक्षित partitions that करोn't provide शेषs. */
		वापस -ENODEV;

	अगर (रक्षित)
		/* Protected partitions are पढ़ो only. */
		erase_size = 0;

	/* If we've alपढ़ोy exposed a partition of this type, hide this
	 * duplicate.  All operations on MTDs are keyed by the type anyway,
	 * so we can't act on the duplicate.
	 */
	अगर (__test_and_set_bit(type_idx, found))
		वापस -EEXIST;

	part->nvram_type = type;

	MCDI_SET_DWORD(inbuf, NVRAM_METADATA_IN_TYPE, type);
	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_METADATA, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_NVRAM_METADATA_OUT_LENMIN)
		वापस -EIO;
	अगर (MCDI_DWORD(outbuf, NVRAM_METADATA_OUT_FLAGS) &
	    (1 << MC_CMD_NVRAM_METADATA_OUT_SUBTYPE_VALID_LBN))
		part->fw_subtype = MCDI_DWORD(outbuf,
					      NVRAM_METADATA_OUT_SUBTYPE);

	part->common.dev_type_name = "EF10 NVRAM manager";
	part->common.type_name = info->name;

	part->common.mtd.type = MTD_NORFLASH;
	part->common.mtd.flags = MTD_CAP_NORFLASH;
	part->common.mtd.size = size;
	part->common.mtd.erasesize = erase_size;
	/* sfc_status is पढ़ो-only */
	अगर (!erase_size)
		part->common.mtd.flags |= MTD_NO_ERASE;

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_mtd_probe(काष्ठा efx_nic *efx)
अणु
	MCDI_DECLARE_BUF(outbuf, MC_CMD_NVRAM_PARTITIONS_OUT_LENMAX);
	DECLARE_BITMAP(found, EF10_NVRAM_PARTITION_COUNT) = अणु 0 पूर्ण;
	काष्ठा efx_mcdi_mtd_partition *parts;
	माप_प्रकार outlen, n_parts_total, i, n_parts;
	अचिन्हित पूर्णांक type;
	पूर्णांक rc;

	ASSERT_RTNL();

	BUILD_BUG_ON(MC_CMD_NVRAM_PARTITIONS_IN_LEN != 0);
	rc = efx_mcdi_rpc(efx, MC_CMD_NVRAM_PARTITIONS, शून्य, 0,
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_NVRAM_PARTITIONS_OUT_LENMIN)
		वापस -EIO;

	n_parts_total = MCDI_DWORD(outbuf, NVRAM_PARTITIONS_OUT_NUM_PARTITIONS);
	अगर (n_parts_total >
	    MCDI_VAR_ARRAY_LEN(outlen, NVRAM_PARTITIONS_OUT_TYPE_ID))
		वापस -EIO;

	parts = kसुस्मृति(n_parts_total, माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	n_parts = 0;
	क्रम (i = 0; i < n_parts_total; i++) अणु
		type = MCDI_ARRAY_DWORD(outbuf, NVRAM_PARTITIONS_OUT_TYPE_ID,
					i);
		rc = efx_ef10_mtd_probe_partition(efx, &parts[n_parts], type,
						  found);
		अगर (rc == -EEXIST || rc == -ENODEV)
			जारी;
		अगर (rc)
			जाओ fail;
		n_parts++;
	पूर्ण

	rc = efx_mtd_add(efx, &parts[0].common, n_parts, माप(*parts));
fail:
	अगर (rc)
		kमुक्त(parts);
	वापस rc;
पूर्ण

#पूर्ण_अगर /* CONFIG_SFC_MTD */

अटल व्योम efx_ef10_ptp_ग_लिखो_host_समय(काष्ठा efx_nic *efx, u32 host_समय)
अणु
	_efx_ग_लिखोd(efx, cpu_to_le32(host_समय), ER_DZ_MC_DB_LWRD);
पूर्ण

अटल व्योम efx_ef10_ptp_ग_लिखो_host_समय_vf(काष्ठा efx_nic *efx,
					    u32 host_समय) अणुपूर्ण

अटल पूर्णांक efx_ef10_rx_enable_बारtamping(काष्ठा efx_channel *channel,
					   bool temp)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_TIME_EVENT_SUBSCRIBE_LEN);
	पूर्णांक rc;

	अगर (channel->sync_events_state == SYNC_EVENTS_REQUESTED ||
	    channel->sync_events_state == SYNC_EVENTS_VALID ||
	    (temp && channel->sync_events_state == SYNC_EVENTS_DISABLED))
		वापस 0;
	channel->sync_events_state = SYNC_EVENTS_REQUESTED;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_TIME_EVENT_SUBSCRIBE);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_DWORD(inbuf, PTP_IN_TIME_EVENT_SUBSCRIBE_QUEUE,
		       channel->channel);

	rc = efx_mcdi_rpc(channel->efx, MC_CMD_PTP,
			  inbuf, माप(inbuf), शून्य, 0, शून्य);

	अगर (rc != 0)
		channel->sync_events_state = temp ? SYNC_EVENTS_QUIESCENT :
						    SYNC_EVENTS_DISABLED;

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_rx_disable_बारtamping(काष्ठा efx_channel *channel,
					    bool temp)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_PTP_IN_TIME_EVENT_UNSUBSCRIBE_LEN);
	पूर्णांक rc;

	अगर (channel->sync_events_state == SYNC_EVENTS_DISABLED ||
	    (temp && channel->sync_events_state == SYNC_EVENTS_QUIESCENT))
		वापस 0;
	अगर (channel->sync_events_state == SYNC_EVENTS_QUIESCENT) अणु
		channel->sync_events_state = SYNC_EVENTS_DISABLED;
		वापस 0;
	पूर्ण
	channel->sync_events_state = temp ? SYNC_EVENTS_QUIESCENT :
					    SYNC_EVENTS_DISABLED;

	MCDI_SET_DWORD(inbuf, PTP_IN_OP, MC_CMD_PTP_OP_TIME_EVENT_UNSUBSCRIBE);
	MCDI_SET_DWORD(inbuf, PTP_IN_PERIPH_ID, 0);
	MCDI_SET_DWORD(inbuf, PTP_IN_TIME_EVENT_UNSUBSCRIBE_CONTROL,
		       MC_CMD_PTP_IN_TIME_EVENT_UNSUBSCRIBE_SINGLE);
	MCDI_SET_DWORD(inbuf, PTP_IN_TIME_EVENT_UNSUBSCRIBE_QUEUE,
		       channel->channel);

	rc = efx_mcdi_rpc(channel->efx, MC_CMD_PTP,
			  inbuf, माप(inbuf), शून्य, 0, शून्य);

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_ptp_set_ts_sync_events(काष्ठा efx_nic *efx, bool en,
					   bool temp)
अणु
	पूर्णांक (*set)(काष्ठा efx_channel *channel, bool temp);
	काष्ठा efx_channel *channel;

	set = en ?
	      efx_ef10_rx_enable_बारtamping :
	      efx_ef10_rx_disable_बारtamping;

	channel = efx_ptp_channel(efx);
	अगर (channel) अणु
		पूर्णांक rc = set(channel, temp);
		अगर (en && rc != 0) अणु
			efx_ef10_ptp_set_ts_sync_events(efx, false, temp);
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_ptp_set_ts_config_vf(काष्ठा efx_nic *efx,
					 काष्ठा hwtstamp_config *init)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक efx_ef10_ptp_set_ts_config(काष्ठा efx_nic *efx,
				      काष्ठा hwtstamp_config *init)
अणु
	पूर्णांक rc;

	चयन (init->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		efx_ef10_ptp_set_ts_sync_events(efx, false, false);
		/* अगर TX बारtamping is still requested then leave PTP on */
		वापस efx_ptp_change_mode(efx,
					   init->tx_type != HWTSTAMP_TX_OFF, 0);
	हाल HWTSTAMP_FILTER_ALL:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_NTP_ALL:
		init->rx_filter = HWTSTAMP_FILTER_ALL;
		rc = efx_ptp_change_mode(efx, true, 0);
		अगर (!rc)
			rc = efx_ef10_ptp_set_ts_sync_events(efx, true, false);
		अगर (rc)
			efx_ptp_change_mode(efx, false, 0);
		वापस rc;
	शेष:
		वापस -दुस्फल;
	पूर्ण
पूर्ण

अटल पूर्णांक efx_ef10_get_phys_port_id(काष्ठा efx_nic *efx,
				     काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	अगर (!is_valid_ether_addr(nic_data->port_id))
		वापस -EOPNOTSUPP;

	ppid->id_len = ETH_ALEN;
	स_नकल(ppid->id, nic_data->port_id, ppid->id_len);

	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_vlan_rx_add_vid(काष्ठा efx_nic *efx, __be16 proto, u16 vid)
अणु
	अगर (proto != htons(ETH_P_8021Q))
		वापस -EINVAL;

	वापस efx_ef10_add_vlan(efx, vid);
पूर्ण

अटल पूर्णांक efx_ef10_vlan_rx_समाप्त_vid(काष्ठा efx_nic *efx, __be16 proto, u16 vid)
अणु
	अगर (proto != htons(ETH_P_8021Q))
		वापस -EINVAL;

	वापस efx_ef10_del_vlan(efx, vid);
पूर्ण

/* We rely on the MCDI wiping out our TX rings अगर it made any changes to the
 * ports table, ensuring that any TSO descriptors that were made on a now-
 * हटाओd tunnel port will be blown away and won't अवरोध things when we try
 * to transmit them using the new ports table.
 */
अटल पूर्णांक efx_ef10_set_udp_tnl_ports(काष्ठा efx_nic *efx, bool unloading)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	MCDI_DECLARE_BUF(inbuf, MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_LENMAX);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_OUT_LEN);
	bool will_reset = false;
	माप_प्रकार num_entries = 0;
	माप_प्रकार inlen, outlen;
	माप_प्रकार i;
	पूर्णांक rc;
	efx_dword_t flags_and_num_entries;

	WARN_ON(!mutex_is_locked(&nic_data->udp_tunnels_lock));

	nic_data->udp_tunnels_dirty = false;

	अगर (!(nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN))) अणु
		efx_device_attach_अगर_not_resetting(efx);
		वापस 0;
	पूर्ण

	BUILD_BUG_ON(ARRAY_SIZE(nic_data->udp_tunnels) >
		     MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_ENTRIES_MAXNUM);

	क्रम (i = 0; i < ARRAY_SIZE(nic_data->udp_tunnels); ++i) अणु
		अगर (nic_data->udp_tunnels[i].type !=
		    TUNNEL_ENCAP_UDP_PORT_ENTRY_INVALID) अणु
			efx_dword_t entry;

			EFX_POPULATE_DWORD_2(entry,
				TUNNEL_ENCAP_UDP_PORT_ENTRY_UDP_PORT,
					ntohs(nic_data->udp_tunnels[i].port),
				TUNNEL_ENCAP_UDP_PORT_ENTRY_PROTOCOL,
					nic_data->udp_tunnels[i].type);
			*_MCDI_ARRAY_DWORD(inbuf,
				SET_TUNNEL_ENCAP_UDP_PORTS_IN_ENTRIES,
				num_entries++) = entry;
		पूर्ण
	पूर्ण

	BUILD_BUG_ON((MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_NUM_ENTRIES_OFST -
		      MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_FLAGS_OFST) * 8 !=
		     EFX_WORD_1_LBN);
	BUILD_BUG_ON(MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_NUM_ENTRIES_LEN * 8 !=
		     EFX_WORD_1_WIDTH);
	EFX_POPULATE_DWORD_2(flags_and_num_entries,
			     MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_UNLOADING,
				!!unloading,
			     EFX_WORD_1, num_entries);
	*_MCDI_DWORD(inbuf, SET_TUNNEL_ENCAP_UDP_PORTS_IN_FLAGS) =
		flags_and_num_entries;

	inlen = MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_IN_LEN(num_entries);

	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS,
				inbuf, inlen, outbuf, माप(outbuf), &outlen);
	अगर (rc == -EIO) अणु
		/* Most likely the MC rebooted due to another function also
		 * setting its tunnel port list. Mark the tunnel port list as
		 * dirty, so it will be pushed upon coming up from the reboot.
		 */
		nic_data->udp_tunnels_dirty = true;
		वापस 0;
	पूर्ण

	अगर (rc) अणु
		/* expected not available on unprivileged functions */
		अगर (rc != -EPERM)
			netअगर_warn(efx, drv, efx->net_dev,
				   "Unable to set UDP tunnel ports; rc=%d.\n", rc);
	पूर्ण अन्यथा अगर (MCDI_DWORD(outbuf, SET_TUNNEL_ENCAP_UDP_PORTS_OUT_FLAGS) &
		   (1 << MC_CMD_SET_TUNNEL_ENCAP_UDP_PORTS_OUT_RESETTING_LBN)) अणु
		netअगर_info(efx, drv, efx->net_dev,
			   "Rebooting MC due to UDP tunnel port list change\n");
		will_reset = true;
		अगर (unloading)
			/* Delay क्रम the MC reset to complete. This will make
			 * unloading other functions a bit smoother. This is a
			 * race, but the other unload will work whichever way
			 * it goes, this just aव्योमs an unnecessary error
			 * message.
			 */
			msleep(100);
	पूर्ण
	अगर (!will_reset && !unloading) अणु
		/* The caller will have detached, relying on the MC reset to
		 * trigger a re-attach.  Since there won't be an MC reset, we
		 * have to करो the attach ourselves.
		 */
		efx_device_attach_अगर_not_resetting(efx);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_udp_tnl_push_ports(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc = 0;

	mutex_lock(&nic_data->udp_tunnels_lock);
	अगर (nic_data->udp_tunnels_dirty) अणु
		/* Make sure all TX are stopped जबतक we modअगरy the table, अन्यथा
		 * we might race against an efx_features_check().
		 */
		efx_device_detach_sync(efx);
		rc = efx_ef10_set_udp_tnl_ports(efx, false);
	पूर्ण
	mutex_unlock(&nic_data->udp_tunnels_lock);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_udp_tnl_set_port(काष्ठा net_device *dev,
				     अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				     काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा efx_nic *efx = netdev_priv(dev);
	काष्ठा efx_ef10_nic_data *nic_data;
	पूर्णांक efx_tunnel_type, rc;

	अगर (ti->type == UDP_TUNNEL_TYPE_VXLAN)
		efx_tunnel_type = TUNNEL_ENCAP_UDP_PORT_ENTRY_VXLAN;
	अन्यथा
		efx_tunnel_type = TUNNEL_ENCAP_UDP_PORT_ENTRY_GENEVE;

	nic_data = efx->nic_data;
	अगर (!(nic_data->datapath_caps &
	      (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN)))
		वापस -EOPNOTSUPP;

	mutex_lock(&nic_data->udp_tunnels_lock);
	/* Make sure all TX are stopped जबतक we add to the table, अन्यथा we
	 * might race against an efx_features_check().
	 */
	efx_device_detach_sync(efx);
	nic_data->udp_tunnels[entry].type = efx_tunnel_type;
	nic_data->udp_tunnels[entry].port = ti->port;
	rc = efx_ef10_set_udp_tnl_ports(efx, false);
	mutex_unlock(&nic_data->udp_tunnels_lock);

	वापस rc;
पूर्ण

/* Called under the TX lock with the TX queue running, hence no-one can be
 * in the middle of updating the UDP tunnels table.  However, they could
 * have tried and failed the MCDI, in which हाल they'll have set the dirty
 * flag beक्रमe dropping their locks.
 */
अटल bool efx_ef10_udp_tnl_has_port(काष्ठा efx_nic *efx, __be16 port)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	माप_प्रकार i;

	अगर (!(nic_data->datapath_caps &
	      (1 << MC_CMD_GET_CAPABILITIES_OUT_VXLAN_NVGRE_LBN)))
		वापस false;

	अगर (nic_data->udp_tunnels_dirty)
		/* SW table may not match HW state, so just assume we can't
		 * use any UDP tunnel offloads.
		 */
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(nic_data->udp_tunnels); ++i)
		अगर (nic_data->udp_tunnels[i].type !=
		    TUNNEL_ENCAP_UDP_PORT_ENTRY_INVALID &&
		    nic_data->udp_tunnels[i].port == port)
			वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक efx_ef10_udp_tnl_unset_port(काष्ठा net_device *dev,
				       अचिन्हित पूर्णांक table, अचिन्हित पूर्णांक entry,
				       काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा efx_nic *efx = netdev_priv(dev);
	काष्ठा efx_ef10_nic_data *nic_data;
	पूर्णांक rc;

	nic_data = efx->nic_data;

	mutex_lock(&nic_data->udp_tunnels_lock);
	/* Make sure all TX are stopped जबतक we हटाओ from the table, अन्यथा we
	 * might race against an efx_features_check().
	 */
	efx_device_detach_sync(efx);
	nic_data->udp_tunnels[entry].type = TUNNEL_ENCAP_UDP_PORT_ENTRY_INVALID;
	nic_data->udp_tunnels[entry].port = 0;
	rc = efx_ef10_set_udp_tnl_ports(efx, false);
	mutex_unlock(&nic_data->udp_tunnels_lock);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा udp_tunnel_nic_info efx_ef10_udp_tunnels = अणु
	.set_port	= efx_ef10_udp_tnl_set_port,
	.unset_port	= efx_ef10_udp_tnl_unset_port,
	.flags          = UDP_TUNNEL_NIC_INFO_MAY_SLEEP,
	.tables         = अणु
		अणु
			.n_entries = 16,
			.tunnel_types = UDP_TUNNEL_TYPE_VXLAN |
					UDP_TUNNEL_TYPE_GENEVE,
		पूर्ण,
	पूर्ण,
पूर्ण;

/* EF10 may have multiple datapath firmware variants within a
 * single version.  Report which variants are running.
 */
अटल माप_प्रकार efx_ef10_prपूर्णांक_additional_fwver(काष्ठा efx_nic *efx, अक्षर *buf,
					      माप_प्रकार len)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	वापस scnम_लिखो(buf, len, " rx%x tx%x",
			 nic_data->rx_dpcpu_fw_id,
			 nic_data->tx_dpcpu_fw_id);
पूर्ण

अटल अचिन्हित पूर्णांक ef10_check_caps(स्थिर काष्ठा efx_nic *efx,
				    u8 flag,
				    u32 offset)
अणु
	स्थिर काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	चयन (offset) अणु
	हाल(MC_CMD_GET_CAPABILITIES_V4_OUT_FLAGS1_OFST):
		वापस nic_data->datapath_caps & BIT_ULL(flag);
	हाल(MC_CMD_GET_CAPABILITIES_V4_OUT_FLAGS2_OFST):
		वापस nic_data->datapath_caps2 & BIT_ULL(flag);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा EF10_OFFLOAD_FEATURES		\
	(NETIF_F_IP_CSUM |		\
	 NETIF_F_HW_VLAN_CTAG_FILTER |	\
	 NETIF_F_IPV6_CSUM |		\
	 NETIF_F_RXHASH |		\
	 NETIF_F_NTUPLE)

स्थिर काष्ठा efx_nic_type efx_hunt_a0_vf_nic_type = अणु
	.is_vf = true,
	.mem_bar = efx_ef10_vf_mem_bar,
	.mem_map_size = efx_ef10_mem_map_size,
	.probe = efx_ef10_probe_vf,
	.हटाओ = efx_ef10_हटाओ,
	.dimension_resources = efx_ef10_dimension_resources,
	.init = efx_ef10_init_nic,
	.fini = efx_ef10_fini_nic,
	.map_reset_reason = efx_ef10_map_reset_reason,
	.map_reset_flags = efx_ef10_map_reset_flags,
	.reset = efx_ef10_reset,
	.probe_port = efx_mcdi_port_probe,
	.हटाओ_port = efx_mcdi_port_हटाओ,
	.fini_dmaq = efx_fini_dmaq,
	.prepare_flr = efx_ef10_prepare_flr,
	.finish_flr = efx_port_dummy_op_व्योम,
	.describe_stats = efx_ef10_describe_stats,
	.update_stats = efx_ef10_update_stats_vf,
	.update_stats_atomic = efx_ef10_update_stats_atomic_vf,
	.start_stats = efx_port_dummy_op_व्योम,
	.pull_stats = efx_port_dummy_op_व्योम,
	.stop_stats = efx_port_dummy_op_व्योम,
	.push_irq_moderation = efx_ef10_push_irq_moderation,
	.reconfigure_mac = efx_ef10_mac_reconfigure,
	.check_mac_fault = efx_mcdi_mac_check_fault,
	.reconfigure_port = efx_mcdi_port_reconfigure,
	.get_wol = efx_ef10_get_wol_vf,
	.set_wol = efx_ef10_set_wol_vf,
	.resume_wol = efx_port_dummy_op_व्योम,
	.mcdi_request = efx_ef10_mcdi_request,
	.mcdi_poll_response = efx_ef10_mcdi_poll_response,
	.mcdi_पढ़ो_response = efx_ef10_mcdi_पढ़ो_response,
	.mcdi_poll_reboot = efx_ef10_mcdi_poll_reboot,
	.mcdi_reboot_detected = efx_ef10_mcdi_reboot_detected,
	.irq_enable_master = efx_port_dummy_op_व्योम,
	.irq_test_generate = efx_ef10_irq_test_generate,
	.irq_disable_non_ev = efx_port_dummy_op_व्योम,
	.irq_handle_msi = efx_ef10_msi_पूर्णांकerrupt,
	.irq_handle_legacy = efx_ef10_legacy_पूर्णांकerrupt,
	.tx_probe = efx_ef10_tx_probe,
	.tx_init = efx_ef10_tx_init,
	.tx_हटाओ = efx_mcdi_tx_हटाओ,
	.tx_ग_लिखो = efx_ef10_tx_ग_लिखो,
	.tx_limit_len = efx_ef10_tx_limit_len,
	.tx_enqueue = __efx_enqueue_skb,
	.rx_push_rss_config = efx_mcdi_vf_rx_push_rss_config,
	.rx_pull_rss_config = efx_mcdi_rx_pull_rss_config,
	.rx_probe = efx_mcdi_rx_probe,
	.rx_init = efx_mcdi_rx_init,
	.rx_हटाओ = efx_mcdi_rx_हटाओ,
	.rx_ग_लिखो = efx_ef10_rx_ग_लिखो,
	.rx_defer_refill = efx_ef10_rx_defer_refill,
	.rx_packet = __efx_rx_packet,
	.ev_probe = efx_mcdi_ev_probe,
	.ev_init = efx_ef10_ev_init,
	.ev_fini = efx_mcdi_ev_fini,
	.ev_हटाओ = efx_mcdi_ev_हटाओ,
	.ev_process = efx_ef10_ev_process,
	.ev_पढ़ो_ack = efx_ef10_ev_पढ़ो_ack,
	.ev_test_generate = efx_ef10_ev_test_generate,
	.filter_table_probe = efx_ef10_filter_table_probe,
	.filter_table_restore = efx_mcdi_filter_table_restore,
	.filter_table_हटाओ = efx_mcdi_filter_table_हटाओ,
	.filter_update_rx_scatter = efx_mcdi_update_rx_scatter,
	.filter_insert = efx_mcdi_filter_insert,
	.filter_हटाओ_safe = efx_mcdi_filter_हटाओ_safe,
	.filter_get_safe = efx_mcdi_filter_get_safe,
	.filter_clear_rx = efx_mcdi_filter_clear_rx,
	.filter_count_rx_used = efx_mcdi_filter_count_rx_used,
	.filter_get_rx_id_limit = efx_mcdi_filter_get_rx_id_limit,
	.filter_get_rx_ids = efx_mcdi_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_expire_one = efx_mcdi_filter_rfs_expire_one,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_MTD
	.mtd_probe = efx_port_dummy_op_पूर्णांक,
#पूर्ण_अगर
	.ptp_ग_लिखो_host_समय = efx_ef10_ptp_ग_लिखो_host_समय_vf,
	.ptp_set_ts_config = efx_ef10_ptp_set_ts_config_vf,
	.vlan_rx_add_vid = efx_ef10_vlan_rx_add_vid,
	.vlan_rx_समाप्त_vid = efx_ef10_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_SFC_SRIOV
	.vचयनing_probe = efx_ef10_vचयनing_probe_vf,
	.vचयनing_restore = efx_ef10_vचयनing_restore_vf,
	.vचयनing_हटाओ = efx_ef10_vचयनing_हटाओ_vf,
#पूर्ण_अगर
	.get_mac_address = efx_ef10_get_mac_address_vf,
	.set_mac_address = efx_ef10_set_mac_address,

	.get_phys_port_id = efx_ef10_get_phys_port_id,
	.revision = EFX_REV_HUNT_A0,
	.max_dma_mask = DMA_BIT_MASK(ESF_DZ_TX_KER_BUF_ADDR_WIDTH),
	.rx_prefix_size = ES_DZ_RX_PREFIX_SIZE,
	.rx_hash_offset = ES_DZ_RX_PREFIX_HASH_OFST,
	.rx_ts_offset = ES_DZ_RX_PREFIX_TSTAMP_OFST,
	.can_rx_scatter = true,
	.always_rx_scatter = true,
	.min_पूर्णांकerrupt_mode = EFX_INT_MODE_MSIX,
	.समयr_period_max = 1 << ERF_DD_EVQ_IND_TIMER_VAL_WIDTH,
	.offload_features = EF10_OFFLOAD_FEATURES,
	.mcdi_max_ver = 2,
	.max_rx_ip_filters = EFX_MCDI_FILTER_TBL_ROWS,
	.hwtstamp_filters = 1 << HWTSTAMP_FILTER_NONE |
			    1 << HWTSTAMP_FILTER_ALL,
	.rx_hash_key_size = 40,
	.check_caps = ef10_check_caps,
	.prपूर्णांक_additional_fwver = efx_ef10_prपूर्णांक_additional_fwver,
	.sensor_event = efx_mcdi_sensor_event,
पूर्ण;

स्थिर काष्ठा efx_nic_type efx_hunt_a0_nic_type = अणु
	.is_vf = false,
	.mem_bar = efx_ef10_pf_mem_bar,
	.mem_map_size = efx_ef10_mem_map_size,
	.probe = efx_ef10_probe_pf,
	.हटाओ = efx_ef10_हटाओ,
	.dimension_resources = efx_ef10_dimension_resources,
	.init = efx_ef10_init_nic,
	.fini = efx_ef10_fini_nic,
	.map_reset_reason = efx_ef10_map_reset_reason,
	.map_reset_flags = efx_ef10_map_reset_flags,
	.reset = efx_ef10_reset,
	.probe_port = efx_mcdi_port_probe,
	.हटाओ_port = efx_mcdi_port_हटाओ,
	.fini_dmaq = efx_fini_dmaq,
	.prepare_flr = efx_ef10_prepare_flr,
	.finish_flr = efx_port_dummy_op_व्योम,
	.describe_stats = efx_ef10_describe_stats,
	.update_stats = efx_ef10_update_stats_pf,
	.start_stats = efx_mcdi_mac_start_stats,
	.pull_stats = efx_mcdi_mac_pull_stats,
	.stop_stats = efx_mcdi_mac_stop_stats,
	.push_irq_moderation = efx_ef10_push_irq_moderation,
	.reconfigure_mac = efx_ef10_mac_reconfigure,
	.check_mac_fault = efx_mcdi_mac_check_fault,
	.reconfigure_port = efx_mcdi_port_reconfigure,
	.get_wol = efx_ef10_get_wol,
	.set_wol = efx_ef10_set_wol,
	.resume_wol = efx_port_dummy_op_व्योम,
	.get_fec_stats = efx_ef10_get_fec_stats,
	.test_chip = efx_ef10_test_chip,
	.test_nvram = efx_mcdi_nvram_test_all,
	.mcdi_request = efx_ef10_mcdi_request,
	.mcdi_poll_response = efx_ef10_mcdi_poll_response,
	.mcdi_पढ़ो_response = efx_ef10_mcdi_पढ़ो_response,
	.mcdi_poll_reboot = efx_ef10_mcdi_poll_reboot,
	.mcdi_reboot_detected = efx_ef10_mcdi_reboot_detected,
	.irq_enable_master = efx_port_dummy_op_व्योम,
	.irq_test_generate = efx_ef10_irq_test_generate,
	.irq_disable_non_ev = efx_port_dummy_op_व्योम,
	.irq_handle_msi = efx_ef10_msi_पूर्णांकerrupt,
	.irq_handle_legacy = efx_ef10_legacy_पूर्णांकerrupt,
	.tx_probe = efx_ef10_tx_probe,
	.tx_init = efx_ef10_tx_init,
	.tx_हटाओ = efx_mcdi_tx_हटाओ,
	.tx_ग_लिखो = efx_ef10_tx_ग_लिखो,
	.tx_limit_len = efx_ef10_tx_limit_len,
	.tx_enqueue = __efx_enqueue_skb,
	.rx_push_rss_config = efx_mcdi_pf_rx_push_rss_config,
	.rx_pull_rss_config = efx_mcdi_rx_pull_rss_config,
	.rx_push_rss_context_config = efx_mcdi_rx_push_rss_context_config,
	.rx_pull_rss_context_config = efx_mcdi_rx_pull_rss_context_config,
	.rx_restore_rss_contexts = efx_mcdi_rx_restore_rss_contexts,
	.rx_probe = efx_mcdi_rx_probe,
	.rx_init = efx_mcdi_rx_init,
	.rx_हटाओ = efx_mcdi_rx_हटाओ,
	.rx_ग_लिखो = efx_ef10_rx_ग_लिखो,
	.rx_defer_refill = efx_ef10_rx_defer_refill,
	.rx_packet = __efx_rx_packet,
	.ev_probe = efx_mcdi_ev_probe,
	.ev_init = efx_ef10_ev_init,
	.ev_fini = efx_mcdi_ev_fini,
	.ev_हटाओ = efx_mcdi_ev_हटाओ,
	.ev_process = efx_ef10_ev_process,
	.ev_पढ़ो_ack = efx_ef10_ev_पढ़ो_ack,
	.ev_test_generate = efx_ef10_ev_test_generate,
	.filter_table_probe = efx_ef10_filter_table_probe,
	.filter_table_restore = efx_mcdi_filter_table_restore,
	.filter_table_हटाओ = efx_mcdi_filter_table_हटाओ,
	.filter_update_rx_scatter = efx_mcdi_update_rx_scatter,
	.filter_insert = efx_mcdi_filter_insert,
	.filter_हटाओ_safe = efx_mcdi_filter_हटाओ_safe,
	.filter_get_safe = efx_mcdi_filter_get_safe,
	.filter_clear_rx = efx_mcdi_filter_clear_rx,
	.filter_count_rx_used = efx_mcdi_filter_count_rx_used,
	.filter_get_rx_id_limit = efx_mcdi_filter_get_rx_id_limit,
	.filter_get_rx_ids = efx_mcdi_filter_get_rx_ids,
#अगर_घोषित CONFIG_RFS_ACCEL
	.filter_rfs_expire_one = efx_mcdi_filter_rfs_expire_one,
#पूर्ण_अगर
#अगर_घोषित CONFIG_SFC_MTD
	.mtd_probe = efx_ef10_mtd_probe,
	.mtd_नाम = efx_mcdi_mtd_नाम,
	.mtd_पढ़ो = efx_mcdi_mtd_पढ़ो,
	.mtd_erase = efx_mcdi_mtd_erase,
	.mtd_ग_लिखो = efx_mcdi_mtd_ग_लिखो,
	.mtd_sync = efx_mcdi_mtd_sync,
#पूर्ण_अगर
	.ptp_ग_लिखो_host_समय = efx_ef10_ptp_ग_लिखो_host_समय,
	.ptp_set_ts_sync_events = efx_ef10_ptp_set_ts_sync_events,
	.ptp_set_ts_config = efx_ef10_ptp_set_ts_config,
	.vlan_rx_add_vid = efx_ef10_vlan_rx_add_vid,
	.vlan_rx_समाप्त_vid = efx_ef10_vlan_rx_समाप्त_vid,
	.udp_tnl_push_ports = efx_ef10_udp_tnl_push_ports,
	.udp_tnl_has_port = efx_ef10_udp_tnl_has_port,
#अगर_घोषित CONFIG_SFC_SRIOV
	.sriov_configure = efx_ef10_sriov_configure,
	.sriov_init = efx_ef10_sriov_init,
	.sriov_fini = efx_ef10_sriov_fini,
	.sriov_wanted = efx_ef10_sriov_wanted,
	.sriov_reset = efx_ef10_sriov_reset,
	.sriov_flr = efx_ef10_sriov_flr,
	.sriov_set_vf_mac = efx_ef10_sriov_set_vf_mac,
	.sriov_set_vf_vlan = efx_ef10_sriov_set_vf_vlan,
	.sriov_set_vf_spoofchk = efx_ef10_sriov_set_vf_spoofchk,
	.sriov_get_vf_config = efx_ef10_sriov_get_vf_config,
	.sriov_set_vf_link_state = efx_ef10_sriov_set_vf_link_state,
	.vचयनing_probe = efx_ef10_vचयनing_probe_pf,
	.vचयनing_restore = efx_ef10_vचयनing_restore_pf,
	.vचयनing_हटाओ = efx_ef10_vचयनing_हटाओ_pf,
#पूर्ण_अगर
	.get_mac_address = efx_ef10_get_mac_address_pf,
	.set_mac_address = efx_ef10_set_mac_address,
	.tso_versions = efx_ef10_tso_versions,

	.get_phys_port_id = efx_ef10_get_phys_port_id,
	.revision = EFX_REV_HUNT_A0,
	.max_dma_mask = DMA_BIT_MASK(ESF_DZ_TX_KER_BUF_ADDR_WIDTH),
	.rx_prefix_size = ES_DZ_RX_PREFIX_SIZE,
	.rx_hash_offset = ES_DZ_RX_PREFIX_HASH_OFST,
	.rx_ts_offset = ES_DZ_RX_PREFIX_TSTAMP_OFST,
	.can_rx_scatter = true,
	.always_rx_scatter = true,
	.option_descriptors = true,
	.min_पूर्णांकerrupt_mode = EFX_INT_MODE_LEGACY,
	.समयr_period_max = 1 << ERF_DD_EVQ_IND_TIMER_VAL_WIDTH,
	.offload_features = EF10_OFFLOAD_FEATURES,
	.mcdi_max_ver = 2,
	.max_rx_ip_filters = EFX_MCDI_FILTER_TBL_ROWS,
	.hwtstamp_filters = 1 << HWTSTAMP_FILTER_NONE |
			    1 << HWTSTAMP_FILTER_ALL,
	.rx_hash_key_size = 40,
	.check_caps = ef10_check_caps,
	.prपूर्णांक_additional_fwver = efx_ef10_prपूर्णांक_additional_fwver,
	.sensor_event = efx_mcdi_sensor_event,
पूर्ण;
