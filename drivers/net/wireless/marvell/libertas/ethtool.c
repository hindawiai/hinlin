<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/hardirq.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/delay.h>

#समावेश "decl.h"
#समावेश "cmd.h"
#समावेश "mesh.h"


अटल व्योम lbs_ethtool_get_drvinfo(काष्ठा net_device *dev,
					 काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	snम_लिखो(info->fw_version, माप(info->fw_version),
		"%u.%u.%u.p%u",
		priv->fwrelease >> 24 & 0xff,
		priv->fwrelease >> 16 & 0xff,
		priv->fwrelease >>  8 & 0xff,
		priv->fwrelease       & 0xff);
	strlcpy(info->driver, "libertas", माप(info->driver));
	strlcpy(info->version, lbs_driver_version, माप(info->version));
पूर्ण

/*
 * All 8388 parts have 16KiB EEPROM size at the समय of writing.
 * In हाल that changes this needs fixing.
 */
#घोषणा LBS_EEPROM_LEN 16384

अटल पूर्णांक lbs_ethtool_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस LBS_EEPROM_LEN;
पूर्ण

अटल पूर्णांक lbs_ethtool_get_eeprom(काष्ठा net_device *dev,
                                  काष्ठा ethtool_eeprom *eeprom, u8 * bytes)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;
	काष्ठा cmd_ds_802_11_eeprom_access cmd;
	पूर्णांक ret;

	अगर (eeprom->offset + eeprom->len > LBS_EEPROM_LEN ||
	    eeprom->len > LBS_EEPROM_READ_LEN) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cmd.hdr.size = cpu_to_le16(माप(काष्ठा cmd_ds_802_11_eeprom_access) -
		LBS_EEPROM_READ_LEN + eeprom->len);
	cmd.action = cpu_to_le16(CMD_ACT_GET);
	cmd.offset = cpu_to_le16(eeprom->offset);
	cmd.len    = cpu_to_le16(eeprom->len);
	ret = lbs_cmd_with_response(priv, CMD_802_11_EEPROM_ACCESS, &cmd);
	अगर (!ret)
		स_नकल(bytes, cmd.value, eeprom->len);

out:
        वापस ret;
पूर्ण

अटल व्योम lbs_ethtool_get_wol(काष्ठा net_device *dev,
				काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	wol->supported = WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY;

	अगर (priv->wol_criteria == EHS_REMOVE_WAKEUP)
		वापस;

	अगर (priv->wol_criteria & EHS_WAKE_ON_UNICAST_DATA)
		wol->wolopts |= WAKE_UCAST;
	अगर (priv->wol_criteria & EHS_WAKE_ON_MULTICAST_DATA)
		wol->wolopts |= WAKE_MCAST;
	अगर (priv->wol_criteria & EHS_WAKE_ON_BROADCAST_DATA)
		wol->wolopts |= WAKE_BCAST;
	अगर (priv->wol_criteria & EHS_WAKE_ON_MAC_EVENT)
		wol->wolopts |= WAKE_PHY;
पूर्ण

अटल पूर्णांक lbs_ethtool_set_wol(काष्ठा net_device *dev,
			       काष्ठा ethtool_wolinfo *wol)
अणु
	काष्ठा lbs_निजी *priv = dev->ml_priv;

	अगर (wol->wolopts & ~(WAKE_UCAST|WAKE_MCAST|WAKE_BCAST|WAKE_PHY))
		वापस -EOPNOTSUPP;

	priv->wol_criteria = 0;
	अगर (wol->wolopts & WAKE_UCAST)
		priv->wol_criteria |= EHS_WAKE_ON_UNICAST_DATA;
	अगर (wol->wolopts & WAKE_MCAST)
		priv->wol_criteria |= EHS_WAKE_ON_MULTICAST_DATA;
	अगर (wol->wolopts & WAKE_BCAST)
		priv->wol_criteria |= EHS_WAKE_ON_BROADCAST_DATA;
	अगर (wol->wolopts & WAKE_PHY)
		priv->wol_criteria |= EHS_WAKE_ON_MAC_EVENT;
	अगर (wol->wolopts == 0)
		priv->wol_criteria |= EHS_REMOVE_WAKEUP;
	वापस 0;
पूर्ण

स्थिर काष्ठा ethtool_ops lbs_ethtool_ops = अणु
	.get_drvinfo = lbs_ethtool_get_drvinfo,
	.get_eeprom =  lbs_ethtool_get_eeprom,
	.get_eeprom_len = lbs_ethtool_get_eeprom_len,
#अगर_घोषित CONFIG_LIBERTAS_MESH
	.get_sset_count = lbs_mesh_ethtool_get_sset_count,
	.get_ethtool_stats = lbs_mesh_ethtool_get_stats,
	.get_strings = lbs_mesh_ethtool_get_strings,
#पूर्ण_अगर
	.get_wol = lbs_ethtool_get_wol,
	.set_wol = lbs_ethtool_set_wol,
पूर्ण;

