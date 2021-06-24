<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2015 Solarflare Communications Inc.
 */

#अगर_अघोषित EF10_SRIOV_H
#घोषणा EF10_SRIOV_H

#समावेश "net_driver.h"

/**
 * काष्ठा ef10_vf - PF's store of VF data
 * @efx: efx_nic काष्ठा क्रम the current VF
 * @pci_dev: the pci_dev काष्ठा क्रम the VF, retained जबतक the VF is asचिन्हित
 * @vport_id: vport ID क्रम the VF
 * @vport_asचिन्हित: record whether the vport is currently asचिन्हित to the VF
 * @mac: MAC address क्रम the VF, zero when address is हटाओd from the vport
 * @vlan: Default VLAN क्रम the VF or #EFX_EF10_NO_VLAN
 */
काष्ठा ef10_vf अणु
	काष्ठा efx_nic *efx;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित पूर्णांक vport_id;
	अचिन्हित पूर्णांक vport_asचिन्हित;
	u8 mac[ETH_ALEN];
	u16 vlan;
#घोषणा EFX_EF10_NO_VLAN       0
पूर्ण;

अटल अंतरभूत bool efx_ef10_sriov_wanted(काष्ठा efx_nic *efx)
अणु
	वापस false;
पूर्ण

पूर्णांक efx_ef10_sriov_configure(काष्ठा efx_nic *efx, पूर्णांक num_vfs);
पूर्णांक efx_ef10_sriov_init(काष्ठा efx_nic *efx);
अटल अंतरभूत व्योम efx_ef10_sriov_reset(काष्ठा efx_nic *efx) अणुपूर्ण
व्योम efx_ef10_sriov_fini(काष्ठा efx_nic *efx);
अटल अंतरभूत व्योम efx_ef10_sriov_flr(काष्ठा efx_nic *efx, अचिन्हित vf_i) अणुपूर्ण

पूर्णांक efx_ef10_sriov_set_vf_mac(काष्ठा efx_nic *efx, पूर्णांक vf, u8 *mac);

पूर्णांक efx_ef10_sriov_set_vf_vlan(काष्ठा efx_nic *efx, पूर्णांक vf_i,
			       u16 vlan, u8 qos);

पूर्णांक efx_ef10_sriov_set_vf_spoofchk(काष्ठा efx_nic *efx, पूर्णांक vf,
				   bool spoofchk);

पूर्णांक efx_ef10_sriov_get_vf_config(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				 काष्ठा अगरla_vf_info *ivf);

पूर्णांक efx_ef10_sriov_set_vf_link_state(काष्ठा efx_nic *efx, पूर्णांक vf_i,
				     पूर्णांक link_state);

पूर्णांक efx_ef10_vचयनing_probe_pf(काष्ठा efx_nic *efx);
पूर्णांक efx_ef10_vचयनing_probe_vf(काष्ठा efx_nic *efx);
पूर्णांक efx_ef10_vचयनing_restore_pf(काष्ठा efx_nic *efx);
पूर्णांक efx_ef10_vचयनing_restore_vf(काष्ठा efx_nic *efx);
व्योम efx_ef10_vचयनing_हटाओ_pf(काष्ठा efx_nic *efx);
व्योम efx_ef10_vचयनing_हटाओ_vf(काष्ठा efx_nic *efx);
पूर्णांक efx_ef10_vport_add_mac(काष्ठा efx_nic *efx,
			   अचिन्हित पूर्णांक port_id, u8 *mac);
पूर्णांक efx_ef10_vport_del_mac(काष्ठा efx_nic *efx,
			   अचिन्हित पूर्णांक port_id, u8 *mac);
पूर्णांक efx_ef10_vadaptor_alloc(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id);
पूर्णांक efx_ef10_vadaptor_query(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id,
			    u32 *port_flags, u32 *vadaptor_flags,
			    अचिन्हित पूर्णांक *vlan_tags);
पूर्णांक efx_ef10_vadaptor_मुक्त(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक port_id);

#पूर्ण_अगर /* EF10_SRIOV_H */
