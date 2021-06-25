<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2019 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित EFX_ETHTOOL_COMMON_H
#घोषणा EFX_ETHTOOL_COMMON_H

व्योम efx_ethtool_get_drvinfo(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_drvinfo *info);
u32 efx_ethtool_get_msglevel(काष्ठा net_device *net_dev);
व्योम efx_ethtool_set_msglevel(काष्ठा net_device *net_dev, u32 msg_enable);
व्योम efx_ethtool_self_test(काष्ठा net_device *net_dev,
			   काष्ठा ethtool_test *test, u64 *data);
व्योम efx_ethtool_get_छोड़ोparam(काष्ठा net_device *net_dev,
				काष्ठा ethtool_छोड़ोparam *छोड़ो);
पूर्णांक efx_ethtool_set_छोड़ोparam(काष्ठा net_device *net_dev,
			       काष्ठा ethtool_छोड़ोparam *छोड़ो);
पूर्णांक efx_ethtool_fill_self_tests(काष्ठा efx_nic *efx,
				काष्ठा efx_self_tests *tests,
				u8 *strings, u64 *data);
पूर्णांक efx_ethtool_get_sset_count(काष्ठा net_device *net_dev, पूर्णांक string_set);
व्योम efx_ethtool_get_strings(काष्ठा net_device *net_dev, u32 string_set,
			     u8 *strings);
व्योम efx_ethtool_get_stats(काष्ठा net_device *net_dev,
			   काष्ठा ethtool_stats *stats __attribute__ ((unused)),
			   u64 *data);
पूर्णांक efx_ethtool_get_link_ksettings(काष्ठा net_device *net_dev,
				   काष्ठा ethtool_link_ksettings *out);
पूर्णांक efx_ethtool_set_link_ksettings(काष्ठा net_device *net_dev,
				   स्थिर काष्ठा ethtool_link_ksettings *settings);
पूर्णांक efx_ethtool_get_fecparam(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_fecparam *fecparam);
पूर्णांक efx_ethtool_set_fecparam(काष्ठा net_device *net_dev,
			     काष्ठा ethtool_fecparam *fecparam);
पूर्णांक efx_ethtool_get_rxnfc(काष्ठा net_device *net_dev,
			  काष्ठा ethtool_rxnfc *info, u32 *rule_locs);
पूर्णांक efx_ethtool_set_rxnfc(काष्ठा net_device *net_dev,
			  काष्ठा ethtool_rxnfc *info);
u32 efx_ethtool_get_rxfh_indir_size(काष्ठा net_device *net_dev);
u32 efx_ethtool_get_rxfh_key_size(काष्ठा net_device *net_dev);
पूर्णांक efx_ethtool_get_rxfh(काष्ठा net_device *net_dev, u32 *indir, u8 *key,
			 u8 *hfunc);
पूर्णांक efx_ethtool_set_rxfh(काष्ठा net_device *net_dev,
			 स्थिर u32 *indir, स्थिर u8 *key, स्थिर u8 hfunc);
पूर्णांक efx_ethtool_get_rxfh_context(काष्ठा net_device *net_dev, u32 *indir,
				 u8 *key, u8 *hfunc, u32 rss_context);
पूर्णांक efx_ethtool_set_rxfh_context(काष्ठा net_device *net_dev,
				 स्थिर u32 *indir, स्थिर u8 *key,
				 स्थिर u8 hfunc, u32 *rss_context,
				 bool delete);
पूर्णांक efx_ethtool_reset(काष्ठा net_device *net_dev, u32 *flags);
पूर्णांक efx_ethtool_get_module_eeprom(काष्ठा net_device *net_dev,
				  काष्ठा ethtool_eeprom *ee,
				  u8 *data);
पूर्णांक efx_ethtool_get_module_info(काष्ठा net_device *net_dev,
				काष्ठा ethtool_modinfo *modinfo);
#पूर्ण_अगर
