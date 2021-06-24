<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2014-2015 Solarflare Communications Inc.
 */
#समावेश <linux/module.h>
#समावेश "net_driver.h"
#समावेश "nic.h"
#समावेश "sriov.h"

पूर्णांक efx_sriov_set_vf_mac(काष्ठा net_device *net_dev, पूर्णांक vf_i, u8 *mac)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->sriov_set_vf_mac)
		वापस efx->type->sriov_set_vf_mac(efx, vf_i, mac);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक efx_sriov_set_vf_vlan(काष्ठा net_device *net_dev, पूर्णांक vf_i, u16 vlan,
			  u8 qos, __be16 vlan_proto)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->sriov_set_vf_vlan) अणु
		अगर ((vlan & ~VLAN_VID_MASK) ||
		    (qos & ~(VLAN_PRIO_MASK >> VLAN_PRIO_SHIFT)))
			वापस -EINVAL;

		अगर (vlan_proto != htons(ETH_P_8021Q))
			वापस -EPROTONOSUPPORT;

		वापस efx->type->sriov_set_vf_vlan(efx, vf_i, vlan, qos);
	पूर्ण अन्यथा अणु
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक efx_sriov_set_vf_spoofchk(काष्ठा net_device *net_dev, पूर्णांक vf_i,
			      bool spoofchk)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->sriov_set_vf_spoofchk)
		वापस efx->type->sriov_set_vf_spoofchk(efx, vf_i, spoofchk);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक efx_sriov_get_vf_config(काष्ठा net_device *net_dev, पूर्णांक vf_i,
			    काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->sriov_get_vf_config)
		वापस efx->type->sriov_get_vf_config(efx, vf_i, ivi);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक efx_sriov_set_vf_link_state(काष्ठा net_device *net_dev, पूर्णांक vf_i,
				पूर्णांक link_state)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);

	अगर (efx->type->sriov_set_vf_link_state)
		वापस efx->type->sriov_set_vf_link_state(efx, vf_i,
							  link_state);
	अन्यथा
		वापस -EOPNOTSUPP;
पूर्ण
