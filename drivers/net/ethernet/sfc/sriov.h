<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2014-2015 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_SRIOV_H
#घोषणा EFX_SRIOV_H

#समावेश "net_driver.h"

#अगर_घोषित CONFIG_SFC_SRIOV

पूर्णांक efx_sriov_set_vf_mac(काष्ठा net_device *net_dev, पूर्णांक vf_i, u8 *mac);
पूर्णांक efx_sriov_set_vf_vlan(काष्ठा net_device *net_dev, पूर्णांक vf_i, u16 vlan,
			  u8 qos, __be16 vlan_proto);
पूर्णांक efx_sriov_set_vf_spoofchk(काष्ठा net_device *net_dev, पूर्णांक vf_i,
			      bool spoofchk);
पूर्णांक efx_sriov_get_vf_config(काष्ठा net_device *net_dev, पूर्णांक vf_i,
			    काष्ठा अगरla_vf_info *ivi);
पूर्णांक efx_sriov_set_vf_link_state(काष्ठा net_device *net_dev, पूर्णांक vf_i,
				पूर्णांक link_state);
#पूर्ण_अगर /* CONFIG_SFC_SRIOV */

#पूर्ण_अगर /* EFX_SRIOV_H */
