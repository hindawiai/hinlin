<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */
#अगर_अघोषित EFX_MCDI_PORT_COMMON_H
#घोषणा EFX_MCDI_PORT_COMMON_H

#समावेश "net_driver.h"
#समावेश "mcdi.h"
#समावेश "mcdi_pcol.h"

काष्ठा efx_mcdi_phy_data अणु
	u32 flags;
	u32 type;
	u32 supported_cap;
	u32 channel;
	u32 port;
	u32 stats_mask;
	u8 name[20];
	u32 media;
	u32 mmd_mask;
	u8 revision[20];
	u32 क्रमced_cap;
पूर्ण;

पूर्णांक efx_mcdi_get_phy_cfg(काष्ठा efx_nic *efx, काष्ठा efx_mcdi_phy_data *cfg);
व्योम efx_link_set_advertising(काष्ठा efx_nic *efx,
			      स्थिर अचिन्हित दीर्घ *advertising);
पूर्णांक efx_mcdi_set_link(काष्ठा efx_nic *efx, u32 capabilities,
		      u32 flags, u32 loopback_mode, u32 loopback_speed);
पूर्णांक efx_mcdi_loopback_modes(काष्ठा efx_nic *efx, u64 *loopback_modes);
व्योम mcdi_to_ethtool_linkset(u32 media, u32 cap, अचिन्हित दीर्घ *linkset);
u32 ethtool_linkset_to_mcdi_cap(स्थिर अचिन्हित दीर्घ *linkset);
u32 efx_get_mcdi_phy_flags(काष्ठा efx_nic *efx);
u8 mcdi_to_ethtool_media(u32 media);
व्योम efx_mcdi_phy_decode_link(काष्ठा efx_nic *efx,
			      काष्ठा efx_link_state *link_state,
			      u32 speed, u32 flags, u32 fcntl);
u32 ethtool_fec_caps_to_mcdi(u32 supported_cap, u32 ethtool_cap);
u32 mcdi_fec_caps_to_ethtool(u32 caps, bool is_25g);
व्योम efx_mcdi_phy_check_fcntl(काष्ठा efx_nic *efx, u32 lpa);
bool efx_mcdi_phy_poll(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_phy_probe(काष्ठा efx_nic *efx);
व्योम efx_mcdi_phy_हटाओ(काष्ठा efx_nic *efx);
व्योम efx_mcdi_phy_get_link_ksettings(काष्ठा efx_nic *efx, काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक efx_mcdi_phy_set_link_ksettings(काष्ठा efx_nic *efx, स्थिर काष्ठा ethtool_link_ksettings *cmd);
पूर्णांक efx_mcdi_phy_get_fecparam(काष्ठा efx_nic *efx, काष्ठा ethtool_fecparam *fec);
पूर्णांक efx_mcdi_phy_set_fecparam(काष्ठा efx_nic *efx, स्थिर काष्ठा ethtool_fecparam *fec);
पूर्णांक efx_mcdi_phy_test_alive(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_port_reconfigure(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_phy_run_tests(काष्ठा efx_nic *efx, पूर्णांक *results, अचिन्हित पूर्णांक flags);
स्थिर अक्षर *efx_mcdi_phy_test_name(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक index);
पूर्णांक efx_mcdi_phy_get_module_eeprom(काष्ठा efx_nic *efx, काष्ठा ethtool_eeprom *ee, u8 *data);
पूर्णांक efx_mcdi_phy_get_module_info(काष्ठा efx_nic *efx, काष्ठा ethtool_modinfo *modinfo);
पूर्णांक efx_mcdi_set_mac(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_set_mtu(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_mac_init_stats(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mac_fini_stats(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_port_get_number(काष्ठा efx_nic *efx);
व्योम efx_mcdi_process_link_change(काष्ठा efx_nic *efx, efx_qword_t *ev);

#पूर्ण_अगर
