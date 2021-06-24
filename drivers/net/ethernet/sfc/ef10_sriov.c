<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2015 Solarflare Communications Inc.
 */
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश "net_driver.h"
#समावेश "ef10_sriov.h"
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "mcdi_pcol.h"

अटल पूर्णांक efx_ef10_evb_port_assign(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id,
				    अचिन्हित पूर्णांक vf_fn)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_EVB_PORT_ASSIGN_IN_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	MCDI_SET_DWORD(inbuf, EVB_PORT_ASSIGN_IN_PORT_ID, port_id);
	MCDI_POPULATE_DWORD_2(inbuf, EVB_PORT_ASSIGN_IN_FUNCTION,
			      EVB_PORT_ASSIGN_IN_PF, nic_data->pf_index,
			      EVB_PORT_ASSIGN_IN_VF, vf_fn);

	वापस efx_mcdi_rpc(efx, MC_CMD_EVB_PORT_ASSIGN, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_ef10_vचयन_alloc(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id,
				  अचिन्हित पूर्णांक vचयन_type)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VSWITCH_ALLOC_IN_LEN);
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, VSWITCH_ALLOC_IN_UPSTREAM_PORT_ID, port_id);
	MCDI_SET_DWORD(inbuf, VSWITCH_ALLOC_IN_TYPE, vचयन_type);
	MCDI_SET_DWORD(inbuf, VSWITCH_ALLOC_IN_NUM_VLAN_TAGS, 2);
	MCDI_POPULATE_DWORD_1(inbuf, VSWITCH_ALLOC_IN_FLAGS,
			      VSWITCH_ALLOC_IN_FLAG_AUTO_PORT, 0);

	/* Quietly try to allocate 2 VLAN tags */
	rc = efx_mcdi_rpc_quiet(efx, MC_CMD_VSWITCH_ALLOC, inbuf, माप(inbuf),
				शून्य, 0, शून्य);

	/* If 2 VLAN tags is too many, revert to trying with 1 VLAN tags */
	अगर (rc == -EPROTO) अणु
		MCDI_SET_DWORD(inbuf, VSWITCH_ALLOC_IN_NUM_VLAN_TAGS, 1);
		rc = efx_mcdi_rpc(efx, MC_CMD_VSWITCH_ALLOC, inbuf,
				  माप(inbuf), शून्य, 0, शून्य);
	पूर्ण अन्यथा अगर (rc) अणु
		efx_mcdi_display_error(efx, MC_CMD_VSWITCH_ALLOC,
				       MC_CMD_VSWITCH_ALLOC_IN_LEN,
				       शून्य, 0, rc);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_vचयन_मुक्त(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VSWITCH_FREE_IN_LEN);

	MCDI_SET_DWORD(inbuf, VSWITCH_FREE_IN_UPSTREAM_PORT_ID, port_id);

	वापस efx_mcdi_rpc(efx, MC_CMD_VSWITCH_FREE, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

अटल पूर्णांक efx_ef10_vport_alloc(काष्ठा efx_nic *efx,
				अचिन्हित पूर्णांक port_id_in,
				अचिन्हित पूर्णांक vport_type,
				u16 vlan,
				अचिन्हित पूर्णांक *port_id_out)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_ALLOC_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_VPORT_ALLOC_OUT_LEN);
	माप_प्रकार outlen;
	पूर्णांक rc;

	EFX_WARN_ON_PARANOID(!port_id_out);

	MCDI_SET_DWORD(inbuf, VPORT_ALLOC_IN_UPSTREAM_PORT_ID, port_id_in);
	MCDI_SET_DWORD(inbuf, VPORT_ALLOC_IN_TYPE, vport_type);
	MCDI_SET_DWORD(inbuf, VPORT_ALLOC_IN_NUM_VLAN_TAGS,
		       (vlan != EFX_EF10_NO_VLAN));
	MCDI_POPULATE_DWORD_1(inbuf, VPORT_ALLOC_IN_FLAGS,
			      VPORT_ALLOC_IN_FLAG_AUTO_PORT, 0);
	अगर (vlan != EFX_EF10_NO_VLAN)
		MCDI_POPULATE_DWORD_1(inbuf, VPORT_ALLOC_IN_VLAN_TAGS,
				      VPORT_ALLOC_IN_VLAN_TAG_0, vlan);

	rc = efx_mcdi_rpc(efx, MC_CMD_VPORT_ALLOC, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_VPORT_ALLOC_OUT_LEN)
		वापस -EIO;

	*port_id_out = MCDI_DWORD(outbuf, VPORT_ALLOC_OUT_VPORT_ID);
	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_vport_मुक्त(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_FREE_IN_LEN);

	MCDI_SET_DWORD(inbuf, VPORT_FREE_IN_VPORT_ID, port_id);

	वापस efx_mcdi_rpc(efx, MC_CMD_VPORT_FREE, inbuf, माप(inbuf),
			    शून्य, 0, शून्य);
पूर्ण

अटल व्योम efx_ef10_sriov_मुक्त_vf_vports(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक i;

	अगर (!nic_data->vf)
		वापस;

	क्रम (i = 0; i < efx->vf_count; i++) अणु
		काष्ठा ef10_vf *vf = nic_data->vf + i;

		/* If VF is asचिन्हित, करो not मुक्त the vport  */
		अगर (vf->pci_dev &&
		    vf->pci_dev->dev_flags & PCI_DEV_FLAGS_ASSIGNED)
			जारी;

		अगर (vf->vport_asचिन्हित) अणु
			efx_ef10_evb_port_assign(efx, EVB_PORT_ID_शून्य, i);
			vf->vport_asचिन्हित = 0;
		पूर्ण

		अगर (!is_zero_ether_addr(vf->mac)) अणु
			efx_ef10_vport_del_mac(efx, vf->vport_id, vf->mac);
			eth_zero_addr(vf->mac);
		पूर्ण

		अगर (vf->vport_id) अणु
			efx_ef10_vport_मुक्त(efx, vf->vport_id);
			vf->vport_id = 0;
		पूर्ण

		vf->efx = शून्य;
	पूर्ण
पूर्ण

अटल व्योम efx_ef10_sriov_मुक्त_vf_vचयनing(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	efx_ef10_sriov_मुक्त_vf_vports(efx);
	kमुक्त(nic_data->vf);
	nic_data->vf = शून्य;
पूर्ण

अटल पूर्णांक efx_ef10_sriov_assign_vf_vport(काष्ठा efx_nic *efx,
					  अचिन्हित पूर्णांक vf_i)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा ef10_vf *vf = nic_data->vf + vf_i;
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(!nic_data->vf))
		वापस -EOPNOTSUPP;

	rc = efx_ef10_vport_alloc(efx, EVB_PORT_ID_ASSIGNED,
				  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL,
				  vf->vlan, &vf->vport_id);
	अगर (rc)
		वापस rc;

	rc = efx_ef10_vport_add_mac(efx, vf->vport_id, vf->mac);
	अगर (rc) अणु
		eth_zero_addr(vf->mac);
		वापस rc;
	पूर्ण

	rc =  efx_ef10_evb_port_assign(efx, vf->vport_id, vf_i);
	अगर (rc)
		वापस rc;

	vf->vport_asचिन्हित = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक efx_ef10_sriov_alloc_vf_vचयनing(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	nic_data->vf = kसुस्मृति(efx->vf_count, माप(काष्ठा ef10_vf),
			       GFP_KERNEL);
	अगर (!nic_data->vf)
		वापस -ENOMEM;

	क्रम (i = 0; i < efx->vf_count; i++) अणु
		eth_अक्रमom_addr(nic_data->vf[i].mac);
		nic_data->vf[i].efx = शून्य;
		nic_data->vf[i].vlan = EFX_EF10_NO_VLAN;

		rc = efx_ef10_sriov_assign_vf_vport(efx, i);
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस 0;
fail:
	efx_ef10_sriov_मुक्त_vf_vports(efx);
	kमुक्त(nic_data->vf);
	nic_data->vf = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_sriov_restore_vf_vचयनing(काष्ठा efx_nic *efx)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	क्रम (i = 0; i < efx->vf_count; i++) अणु
		rc = efx_ef10_sriov_assign_vf_vport(efx, i);
		अगर (rc)
			जाओ fail;
	पूर्ण

	वापस 0;
fail:
	efx_ef10_sriov_मुक्त_vf_vचयनing(efx);
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_vadaptor_alloc_set_features(काष्ठा efx_nic *efx)
अणु
	u32 port_flags;
	पूर्णांक rc;

	rc = efx_ef10_vadaptor_alloc(efx, efx->vport_id);
	अगर (rc)
		जाओ fail_vadaptor_alloc;

	rc = efx_ef10_vadaptor_query(efx, efx->vport_id,
				     &port_flags, शून्य, शून्य);
	अगर (rc)
		जाओ fail_vadaptor_query;

	अगर (port_flags &
	    (1 << MC_CMD_VPORT_ALLOC_IN_FLAG_VLAN_RESTRICT_LBN))
		efx->fixed_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	अन्यथा
		efx->fixed_features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;

	वापस 0;

fail_vadaptor_query:
	efx_ef10_vadaptor_मुक्त(efx, EVB_PORT_ID_ASSIGNED);
fail_vadaptor_alloc:
	वापस rc;
पूर्ण

/* On top of the शेष firmware vचयन setup, create a VEB vचयन and
 * expansion vport क्रम use by this function.
 */
पूर्णांक efx_ef10_vचयनing_probe_pf(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा net_device *net_dev = efx->net_dev;
	पूर्णांक rc;

	अगर (pci_sriov_get_totalvfs(efx->pci_dev) <= 0) अणु
		/* vचयन not needed as we have no VFs */
		efx_ef10_vadaptor_alloc_set_features(efx);
		वापस 0;
	पूर्ण

	rc = efx_ef10_vचयन_alloc(efx, EVB_PORT_ID_ASSIGNED,
				    MC_CMD_VSWITCH_ALLOC_IN_VSWITCH_TYPE_VEB);
	अगर (rc)
		जाओ fail1;

	rc = efx_ef10_vport_alloc(efx, EVB_PORT_ID_ASSIGNED,
				  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL,
				  EFX_EF10_NO_VLAN, &efx->vport_id);
	अगर (rc)
		जाओ fail2;

	rc = efx_ef10_vport_add_mac(efx, efx->vport_id, net_dev->dev_addr);
	अगर (rc)
		जाओ fail3;
	ether_addr_copy(nic_data->vport_mac, net_dev->dev_addr);

	rc = efx_ef10_vadaptor_alloc_set_features(efx);
	अगर (rc)
		जाओ fail4;

	वापस 0;
fail4:
	efx_ef10_vport_del_mac(efx, efx->vport_id, nic_data->vport_mac);
	eth_zero_addr(nic_data->vport_mac);
fail3:
	efx_ef10_vport_मुक्त(efx, efx->vport_id);
	efx->vport_id = EVB_PORT_ID_ASSIGNED;
fail2:
	efx_ef10_vचयन_मुक्त(efx, EVB_PORT_ID_ASSIGNED);
fail1:
	वापस rc;
पूर्ण

पूर्णांक efx_ef10_vचयनing_probe_vf(काष्ठा efx_nic *efx)
अणु
	वापस efx_ef10_vadaptor_alloc_set_features(efx);
पूर्ण

पूर्णांक efx_ef10_vचयनing_restore_pf(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	अगर (!nic_data->must_probe_vचयनing)
		वापस 0;

	rc = efx_ef10_vचयनing_probe_pf(efx);
	अगर (rc)
		जाओ fail;

	rc = efx_ef10_sriov_restore_vf_vचयनing(efx);
	अगर (rc)
		जाओ fail;

	nic_data->must_probe_vचयनing = false;
fail:
	वापस rc;
पूर्ण

पूर्णांक efx_ef10_vचयनing_restore_vf(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	पूर्णांक rc;

	अगर (!nic_data->must_probe_vचयनing)
		वापस 0;

	rc = efx_ef10_vadaptor_मुक्त(efx, EVB_PORT_ID_ASSIGNED);
	अगर (rc)
		वापस rc;

	nic_data->must_probe_vचयनing = false;
	वापस 0;
पूर्ण

व्योम efx_ef10_vचयनing_हटाओ_pf(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	efx_ef10_sriov_मुक्त_vf_vचयनing(efx);

	efx_ef10_vadaptor_मुक्त(efx, efx->vport_id);

	अगर (efx->vport_id == EVB_PORT_ID_ASSIGNED)
		वापस; /* No vचयन was ever created */

	अगर (!is_zero_ether_addr(nic_data->vport_mac)) अणु
		efx_ef10_vport_del_mac(efx, efx->vport_id,
				       efx->net_dev->dev_addr);
		eth_zero_addr(nic_data->vport_mac);
	पूर्ण
	efx_ef10_vport_मुक्त(efx, efx->vport_id);
	efx->vport_id = EVB_PORT_ID_ASSIGNED;

	/* Only मुक्त the vचयन अगर no VFs are asचिन्हित */
	अगर (!pci_vfs_asचिन्हित(efx->pci_dev))
		efx_ef10_vचयन_मुक्त(efx, efx->vport_id);
पूर्ण

व्योम efx_ef10_vचयनing_हटाओ_vf(काष्ठा efx_nic *efx)
अणु
	efx_ef10_vadaptor_मुक्त(efx, EVB_PORT_ID_ASSIGNED);
पूर्ण

अटल पूर्णांक efx_ef10_pci_sriov_enable(काष्ठा efx_nic *efx, पूर्णांक num_vfs)
अणु
	पूर्णांक rc = 0;
	काष्ठा pci_dev *dev = efx->pci_dev;

	efx->vf_count = num_vfs;

	rc = efx_ef10_sriov_alloc_vf_vचयनing(efx);
	अगर (rc)
		जाओ fail1;

	rc = pci_enable_sriov(dev, num_vfs);
	अगर (rc)
		जाओ fail2;

	वापस 0;
fail2:
	efx_ef10_sriov_मुक्त_vf_vचयनing(efx);
fail1:
	efx->vf_count = 0;
	netअगर_err(efx, probe, efx->net_dev,
		  "Failed to enable SRIOV VFs\n");
	वापस rc;
पूर्ण

अटल पूर्णांक efx_ef10_pci_sriov_disable(काष्ठा efx_nic *efx, bool क्रमce)
अणु
	काष्ठा pci_dev *dev = efx->pci_dev;
	अचिन्हित पूर्णांक vfs_asचिन्हित = 0;

	vfs_asचिन्हित = pci_vfs_asचिन्हित(dev);

	अगर (vfs_asचिन्हित && !क्रमce) अणु
		netअगर_info(efx, drv, efx->net_dev, "VFs are assigned to guests; "
			   "please detach them before disabling SR-IOV\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!vfs_asचिन्हित)
		pci_disable_sriov(dev);

	efx_ef10_sriov_मुक्त_vf_vचयनing(efx);
	efx->vf_count = 0;
	वापस 0;
पूर्ण

पूर्णांक efx_ef10_sriov_configure(काष्ठा efx_nic *efx, पूर्णांक num_vfs)
अणु
	अगर (num_vfs == 0)
		वापस efx_ef10_pci_sriov_disable(efx, false);
	अन्यथा
		वापस efx_ef10_pci_sriov_enable(efx, num_vfs);
पूर्ण

पूर्णांक efx_ef10_sriov_init(काष्ठा efx_nic *efx)
अणु
	वापस 0;
पूर्ण

व्योम efx_ef10_sriov_fini(काष्ठा efx_nic *efx)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	अगर (!nic_data->vf) अणु
		/* Remove any un-asचिन्हित orphaned VFs */
		अगर (pci_num_vf(efx->pci_dev) && !pci_vfs_asचिन्हित(efx->pci_dev))
			pci_disable_sriov(efx->pci_dev);
		वापस;
	पूर्ण

	/* Remove any VFs in the host */
	क्रम (i = 0; i < efx->vf_count; ++i) अणु
		काष्ठा efx_nic *vf_efx = nic_data->vf[i].efx;

		अगर (vf_efx)
			vf_efx->pci_dev->driver->हटाओ(vf_efx->pci_dev);
	पूर्ण

	rc = efx_ef10_pci_sriov_disable(efx, true);
	अगर (rc)
		netअगर_dbg(efx, drv, efx->net_dev,
			  "Disabling SRIOV was not successful rc=%d\n", rc);
	अन्यथा
		netअगर_dbg(efx, drv, efx->net_dev, "SRIOV disabled\n");
पूर्ण

अटल पूर्णांक efx_ef10_vport_del_vf_mac(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id,
				     u8 *mac)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_VPORT_DEL_MAC_ADDRESS_IN_LEN);
	MCDI_DECLARE_BUF_ERR(outbuf);
	माप_प्रकार outlen;
	पूर्णांक rc;

	MCDI_SET_DWORD(inbuf, VPORT_DEL_MAC_ADDRESS_IN_VPORT_ID, port_id);
	ether_addr_copy(MCDI_PTR(inbuf, VPORT_DEL_MAC_ADDRESS_IN_MACADDR), mac);

	rc = efx_mcdi_rpc(efx, MC_CMD_VPORT_DEL_MAC_ADDRESS, inbuf,
			  माप(inbuf), outbuf, माप(outbuf), &outlen);

	वापस rc;
पूर्ण

पूर्णांक efx_ef10_sriov_set_vf_mac(काष्ठा efx_nic *efx, पूर्णांक vf_i, u8 *mac)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा ef10_vf *vf;
	पूर्णांक rc;

	अगर (!nic_data->vf)
		वापस -EOPNOTSUPP;

	अगर (vf_i >= efx->vf_count)
		वापस -EINVAL;
	vf = nic_data->vf + vf_i;

	अगर (vf->efx) अणु
		efx_device_detach_sync(vf->efx);
		efx_net_stop(vf->efx->net_dev);

		करोwn_ग_लिखो(&vf->efx->filter_sem);
		vf->efx->type->filter_table_हटाओ(vf->efx);

		rc = efx_ef10_vadaptor_मुक्त(vf->efx, EVB_PORT_ID_ASSIGNED);
		अगर (rc) अणु
			up_ग_लिखो(&vf->efx->filter_sem);
			वापस rc;
		पूर्ण
	पूर्ण

	rc = efx_ef10_evb_port_assign(efx, EVB_PORT_ID_शून्य, vf_i);
	अगर (rc)
		वापस rc;

	अगर (!is_zero_ether_addr(vf->mac)) अणु
		rc = efx_ef10_vport_del_vf_mac(efx, vf->vport_id, vf->mac);
		अगर (rc)
			वापस rc;
	पूर्ण

	अगर (!is_zero_ether_addr(mac)) अणु
		rc = efx_ef10_vport_add_mac(efx, vf->vport_id, mac);
		अगर (rc)
			जाओ fail;

		अगर (vf->efx)
			ether_addr_copy(vf->efx->net_dev->dev_addr, mac);
	पूर्ण

	ether_addr_copy(vf->mac, mac);

	rc = efx_ef10_evb_port_assign(efx, vf->vport_id, vf_i);
	अगर (rc)
		जाओ fail;

	अगर (vf->efx) अणु
		/* VF cannot use the vport_id that the PF created */
		rc = efx_ef10_vadaptor_alloc(vf->efx, EVB_PORT_ID_ASSIGNED);
		अगर (rc) अणु
			up_ग_लिखो(&vf->efx->filter_sem);
			वापस rc;
		पूर्ण
		vf->efx->type->filter_table_probe(vf->efx);
		up_ग_लिखो(&vf->efx->filter_sem);
		efx_net_खोलो(vf->efx->net_dev);
		efx_device_attach_अगर_not_resetting(vf->efx);
	पूर्ण

	वापस 0;

fail:
	eth_zero_addr(vf->mac);
	वापस rc;
पूर्ण

पूर्णांक efx_ef10_sriov_set_vf_vlan(काष्ठा efx_nic *efx, पूर्णांक vf_i, u16 vlan,
			       u8 qos)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा ef10_vf *vf;
	u16 new_vlan;
	पूर्णांक rc = 0, rc2 = 0;

	अगर (vf_i >= efx->vf_count)
		वापस -EINVAL;
	अगर (qos != 0)
		वापस -EINVAL;

	vf = nic_data->vf + vf_i;

	new_vlan = (vlan == 0) ? EFX_EF10_NO_VLAN : vlan;
	अगर (new_vlan == vf->vlan)
		वापस 0;

	अगर (vf->efx) अणु
		efx_device_detach_sync(vf->efx);
		efx_net_stop(vf->efx->net_dev);

		mutex_lock(&vf->efx->mac_lock);
		करोwn_ग_लिखो(&vf->efx->filter_sem);
		vf->efx->type->filter_table_हटाओ(vf->efx);

		rc = efx_ef10_vadaptor_मुक्त(vf->efx, EVB_PORT_ID_ASSIGNED);
		अगर (rc)
			जाओ restore_filters;
	पूर्ण

	अगर (vf->vport_asचिन्हित) अणु
		rc = efx_ef10_evb_port_assign(efx, EVB_PORT_ID_शून्य, vf_i);
		अगर (rc) अणु
			netअगर_warn(efx, drv, efx->net_dev,
				   "Failed to change vlan on VF %d.\n", vf_i);
			netअगर_warn(efx, drv, efx->net_dev,
				   "This is likely because the VF is bound to a driver in a VM.\n");
			netअगर_warn(efx, drv, efx->net_dev,
				   "Please unload the driver in the VM.\n");
			जाओ restore_vadaptor;
		पूर्ण
		vf->vport_asचिन्हित = 0;
	पूर्ण

	अगर (!is_zero_ether_addr(vf->mac)) अणु
		rc = efx_ef10_vport_del_mac(efx, vf->vport_id, vf->mac);
		अगर (rc)
			जाओ restore_evb_port;
	पूर्ण

	अगर (vf->vport_id) अणु
		rc = efx_ef10_vport_मुक्त(efx, vf->vport_id);
		अगर (rc)
			जाओ restore_mac;
		vf->vport_id = 0;
	पूर्ण

	/* Do the actual vlan change */
	vf->vlan = new_vlan;

	/* Restore everything in reverse order */
	rc = efx_ef10_vport_alloc(efx, EVB_PORT_ID_ASSIGNED,
				  MC_CMD_VPORT_ALLOC_IN_VPORT_TYPE_NORMAL,
				  vf->vlan, &vf->vport_id);
	अगर (rc)
		जाओ reset_nic_up_ग_लिखो;

restore_mac:
	अगर (!is_zero_ether_addr(vf->mac)) अणु
		rc2 = efx_ef10_vport_add_mac(efx, vf->vport_id, vf->mac);
		अगर (rc2) अणु
			eth_zero_addr(vf->mac);
			जाओ reset_nic_up_ग_लिखो;
		पूर्ण
	पूर्ण

restore_evb_port:
	rc2 = efx_ef10_evb_port_assign(efx, vf->vport_id, vf_i);
	अगर (rc2)
		जाओ reset_nic_up_ग_लिखो;
	अन्यथा
		vf->vport_asचिन्हित = 1;

restore_vadaptor:
	अगर (vf->efx) अणु
		rc2 = efx_ef10_vadaptor_alloc(vf->efx, EVB_PORT_ID_ASSIGNED);
		अगर (rc2)
			जाओ reset_nic_up_ग_लिखो;
	पूर्ण

restore_filters:
	अगर (vf->efx) अणु
		rc2 = vf->efx->type->filter_table_probe(vf->efx);
		अगर (rc2)
			जाओ reset_nic_up_ग_लिखो;

		up_ग_लिखो(&vf->efx->filter_sem);
		mutex_unlock(&vf->efx->mac_lock);

		rc2 = efx_net_खोलो(vf->efx->net_dev);
		अगर (rc2)
			जाओ reset_nic;

		efx_device_attach_अगर_not_resetting(vf->efx);
	पूर्ण
	वापस rc;

reset_nic_up_ग_लिखो:
	अगर (vf->efx) अणु
		up_ग_लिखो(&vf->efx->filter_sem);
		mutex_unlock(&vf->efx->mac_lock);
	पूर्ण
reset_nic:
	अगर (vf->efx) अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Failed to restore VF - scheduling reset.\n");
		efx_schedule_reset(vf->efx, RESET_TYPE_DATAPATH);
	पूर्ण अन्यथा अणु
		netअगर_err(efx, drv, efx->net_dev,
			  "Failed to restore the VF and cannot reset the VF "
			  "- VF is not functional.\n");
		netअगर_err(efx, drv, efx->net_dev,
			  "Please reload the driver attached to the VF.\n");
	पूर्ण

	वापस rc ? rc : rc2;
पूर्ण

अटल पूर्णांक efx_ef10_sriov_set_privilege_mask(काष्ठा efx_nic *efx, पूर्णांक vf_i,
					     u32 mask, u32 value)
अणु
	MCDI_DECLARE_BUF(pm_outbuf, MC_CMD_PRIVILEGE_MASK_OUT_LEN);
	MCDI_DECLARE_BUF(pm_inbuf, MC_CMD_PRIVILEGE_MASK_IN_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	u32 old_mask, new_mask;
	माप_प्रकार outlen;
	पूर्णांक rc;

	EFX_WARN_ON_PARANOID((value & ~mask) != 0);

	/* Get privilege mask */
	MCDI_POPULATE_DWORD_2(pm_inbuf, PRIVILEGE_MASK_IN_FUNCTION,
			      PRIVILEGE_MASK_IN_FUNCTION_PF, nic_data->pf_index,
			      PRIVILEGE_MASK_IN_FUNCTION_VF, vf_i);

	rc = efx_mcdi_rpc(efx, MC_CMD_PRIVILEGE_MASK,
			  pm_inbuf, माप(pm_inbuf),
			  pm_outbuf, माप(pm_outbuf), &outlen);

	अगर (rc != 0)
		वापस rc;
	अगर (outlen != MC_CMD_PRIVILEGE_MASK_OUT_LEN)
		वापस -EIO;

	old_mask = MCDI_DWORD(pm_outbuf, PRIVILEGE_MASK_OUT_OLD_MASK);

	new_mask = old_mask & ~mask;
	new_mask |= value;

	अगर (new_mask == old_mask)
		वापस 0;

	new_mask |= MC_CMD_PRIVILEGE_MASK_IN_DO_CHANGE;

	/* Set privilege mask */
	MCDI_SET_DWORD(pm_inbuf, PRIVILEGE_MASK_IN_NEW_MASK, new_mask);

	rc = efx_mcdi_rpc(efx, MC_CMD_PRIVILEGE_MASK,
			  pm_inbuf, माप(pm_inbuf),
			  pm_outbuf, माप(pm_outbuf), &outlen);

	अगर (rc != 0)
		वापस rc;
	अगर (outlen != MC_CMD_PRIVILEGE_MASK_OUT_LEN)
		वापस -EIO;

	वापस 0;
पूर्ण

पूर्णांक efx_ef10_sriov_set_vf_spoofchk(काष्ठा efx_nic *efx, पूर्णांक vf_i, bool spoofchk)
अणु
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	/* Can't enable spoofchk if firmware doesn't support it. */
	अगर (!(nic_data->datapath_caps &
	      BIT(MC_CMD_GET_CAPABILITIES_OUT_TX_MAC_SECURITY_FILTERING_LBN)) &&
	    spoofchk)
		वापस -EOPNOTSUPP;

	वापस efx_ef10_sriov_set_privilege_mask(efx, vf_i,
		MC_CMD_PRIVILEGE_MASK_IN_GRP_MAC_SPOOFING_TX,
		spoofchk ? 0 : MC_CMD_PRIVILEGE_MASK_IN_GRP_MAC_SPOOFING_TX);
पूर्ण

पूर्णांक efx_ef10_sriov_set_vf_link_state(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				     पूर्णांक link_state)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LINK_STATE_MODE_IN_LEN);
	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;

	BUILD_BUG_ON(IFLA_VF_LINK_STATE_AUTO !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_AUTO);
	BUILD_BUG_ON(IFLA_VF_LINK_STATE_ENABLE !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_UP);
	BUILD_BUG_ON(IFLA_VF_LINK_STATE_DISABLE !=
		     MC_CMD_LINK_STATE_MODE_IN_LINK_STATE_DOWN);
	MCDI_POPULATE_DWORD_2(inbuf, LINK_STATE_MODE_IN_FUNCTION,
			      LINK_STATE_MODE_IN_FUNCTION_PF,
			      nic_data->pf_index,
			      LINK_STATE_MODE_IN_FUNCTION_VF, vf_i);
	MCDI_SET_DWORD(inbuf, LINK_STATE_MODE_IN_NEW_MODE, link_state);
	वापस efx_mcdi_rpc(efx, MC_CMD_LINK_STATE_MODE, inbuf, माप(inbuf),
			    शून्य, 0, शून्य); /* करोn't care what old mode was */
पूर्ण

पूर्णांक efx_ef10_sriov_get_vf_config(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				 काष्ठा अगरla_vf_info *ivf)
अणु
	MCDI_DECLARE_BUF(inbuf, MC_CMD_LINK_STATE_MODE_IN_LEN);
	MCDI_DECLARE_BUF(outbuf, MC_CMD_LINK_STATE_MODE_OUT_LEN);

	काष्ठा efx_ef10_nic_data *nic_data = efx->nic_data;
	काष्ठा ef10_vf *vf;
	माप_प्रकार outlen;
	पूर्णांक rc;

	अगर (vf_i >= efx->vf_count)
		वापस -EINVAL;

	अगर (!nic_data->vf)
		वापस -EOPNOTSUPP;

	vf = nic_data->vf + vf_i;

	ivf->vf = vf_i;
	ivf->min_tx_rate = 0;
	ivf->max_tx_rate = 0;
	ether_addr_copy(ivf->mac, vf->mac);
	ivf->vlan = (vf->vlan == EFX_EF10_NO_VLAN) ? 0 : vf->vlan;
	ivf->qos = 0;

	MCDI_POPULATE_DWORD_2(inbuf, LINK_STATE_MODE_IN_FUNCTION,
			      LINK_STATE_MODE_IN_FUNCTION_PF,
			      nic_data->pf_index,
			      LINK_STATE_MODE_IN_FUNCTION_VF, vf_i);
	MCDI_SET_DWORD(inbuf, LINK_STATE_MODE_IN_NEW_MODE,
		       MC_CMD_LINK_STATE_MODE_IN_DO_NOT_CHANGE);
	rc = efx_mcdi_rpc(efx, MC_CMD_LINK_STATE_MODE, inbuf, माप(inbuf),
			  outbuf, माप(outbuf), &outlen);
	अगर (rc)
		वापस rc;
	अगर (outlen < MC_CMD_LINK_STATE_MODE_OUT_LEN)
		वापस -EIO;
	ivf->linkstate = MCDI_DWORD(outbuf, LINK_STATE_MODE_OUT_OLD_MODE);

	वापस 0;
पूर्ण
