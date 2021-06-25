<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2019 Netronome Systems, Inc. */

#समावेश <linux/bitfield.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_link.h>
#समावेश <linux/अगर_ether.h>

#समावेश "nfpcore/nfp_cpp.h"
#समावेश "nfp_app.h"
#समावेश "nfp_main.h"
#समावेश "nfp_net_ctrl.h"
#समावेश "nfp_net.h"
#समावेश "nfp_net_sriov.h"

अटल पूर्णांक
nfp_net_sriov_check(काष्ठा nfp_app *app, पूर्णांक vf, u16 cap, स्थिर अक्षर *msg)
अणु
	u16 cap_vf;

	अगर (!app || !app->pf->vfcfg_tbl2)
		वापस -EOPNOTSUPP;

	cap_vf = पढ़ोw(app->pf->vfcfg_tbl2 + NFP_NET_VF_CFG_MB_CAP);
	अगर ((cap_vf & cap) != cap) अणु
		nfp_warn(app->pf->cpp, "ndo_set_vf_%s not supported\n", msg);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vf < 0 || vf >= app->pf->num_vfs) अणु
		nfp_warn(app->pf->cpp, "invalid VF id %d\n", vf);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_net_sriov_update(काष्ठा nfp_app *app, पूर्णांक vf, u16 update, स्थिर अक्षर *msg)
अणु
	काष्ठा nfp_net *nn;
	पूर्णांक ret;

	/* Write update info to mailbox in VF config symbol */
	ग_लिखोb(vf, app->pf->vfcfg_tbl2 + NFP_NET_VF_CFG_MB_VF_NUM);
	ग_लिखोw(update, app->pf->vfcfg_tbl2 + NFP_NET_VF_CFG_MB_UPD);

	nn = list_first_entry(&app->pf->vnics, काष्ठा nfp_net, vnic_list);
	/* Signal VF reconfiguration */
	ret = nfp_net_reconfig(nn, NFP_NET_CFG_UPDATE_VF);
	अगर (ret)
		वापस ret;

	ret = पढ़ोw(app->pf->vfcfg_tbl2 + NFP_NET_VF_CFG_MB_RET);
	अगर (ret)
		nfp_warn(app->pf->cpp,
			 "FW refused VF %s update with errno: %d\n", msg, ret);
	वापस -ret;
पूर्ण

पूर्णांक nfp_app_set_vf_mac(काष्ठा net_device *netdev, पूर्णांक vf, u8 *mac)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_MAC, "mac");
	अगर (err)
		वापस err;

	अगर (is_multicast_ether_addr(mac)) अणु
		nfp_warn(app->pf->cpp,
			 "invalid Ethernet address %pM for VF id %d\n",
			 mac, vf);
		वापस -EINVAL;
	पूर्ण

	/* Write MAC to VF entry in VF config symbol */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	ग_लिखोl(get_unaligned_be32(mac), app->pf->vfcfg_tbl2 + vf_offset);
	ग_लिखोw(get_unaligned_be16(mac + 4),
	       app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_MAC_LO);

	err = nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_MAC, "MAC");
	अगर (!err)
		nfp_info(app->pf->cpp,
			 "MAC %pM set on VF %d, reload the VF driver to make this change effective.\n",
			 mac, vf);

	वापस err;
पूर्ण

पूर्णांक nfp_app_set_vf_vlan(काष्ठा net_device *netdev, पूर्णांक vf, u16 vlan, u8 qos,
			__be16 vlan_proto)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	u16 vlan_tci;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_VLAN, "vlan");
	अगर (err)
		वापस err;

	अगर (vlan_proto != htons(ETH_P_8021Q))
		वापस -EOPNOTSUPP;

	अगर (vlan > 4095 || qos > 7) अणु
		nfp_warn(app->pf->cpp,
			 "invalid vlan id or qos for VF id %d\n", vf);
		वापस -EINVAL;
	पूर्ण

	/* Write VLAN tag to VF entry in VF config symbol */
	vlan_tci = FIELD_PREP(NFP_NET_VF_CFG_VLAN_VID, vlan) |
		FIELD_PREP(NFP_NET_VF_CFG_VLAN_QOS, qos);
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;
	ग_लिखोw(vlan_tci, app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_VLAN);

	वापस nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_VLAN,
				    "vlan");
पूर्ण

पूर्णांक nfp_app_set_vf_spoofchk(काष्ठा net_device *netdev, पूर्णांक vf, bool enable)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	u8 vf_ctrl;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_SPOOF,
				  "spoofchk");
	अगर (err)
		वापस err;

	/* Write spoof check control bit to VF entry in VF config symbol */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTRL;
	vf_ctrl = पढ़ोb(app->pf->vfcfg_tbl2 + vf_offset);
	vf_ctrl &= ~NFP_NET_VF_CFG_CTRL_SPOOF;
	vf_ctrl |= FIELD_PREP(NFP_NET_VF_CFG_CTRL_SPOOF, enable);
	ग_लिखोb(vf_ctrl, app->pf->vfcfg_tbl2 + vf_offset);

	वापस nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_SPOOF,
				    "spoofchk");
पूर्ण

पूर्णांक nfp_app_set_vf_trust(काष्ठा net_device *netdev, पूर्णांक vf, bool enable)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	u8 vf_ctrl;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_TRUST,
				  "trust");
	अगर (err)
		वापस err;

	/* Write trust control bit to VF entry in VF config symbol */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTRL;
	vf_ctrl = पढ़ोb(app->pf->vfcfg_tbl2 + vf_offset);
	vf_ctrl &= ~NFP_NET_VF_CFG_CTRL_TRUST;
	vf_ctrl |= FIELD_PREP(NFP_NET_VF_CFG_CTRL_TRUST, enable);
	ग_लिखोb(vf_ctrl, app->pf->vfcfg_tbl2 + vf_offset);

	वापस nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_TRUST,
				    "trust");
पूर्ण

पूर्णांक nfp_app_set_vf_link_state(काष्ठा net_device *netdev, पूर्णांक vf,
			      पूर्णांक link_state)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	u8 vf_ctrl;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, NFP_NET_VF_CFG_MB_CAP_LINK_STATE,
				  "link_state");
	अगर (err)
		वापस err;

	चयन (link_state) अणु
	हाल IFLA_VF_LINK_STATE_AUTO:
	हाल IFLA_VF_LINK_STATE_ENABLE:
	हाल IFLA_VF_LINK_STATE_DISABLE:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Write link state to VF entry in VF config symbol */
	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ +
		NFP_NET_VF_CFG_CTRL;
	vf_ctrl = पढ़ोb(app->pf->vfcfg_tbl2 + vf_offset);
	vf_ctrl &= ~NFP_NET_VF_CFG_CTRL_LINK_STATE;
	vf_ctrl |= FIELD_PREP(NFP_NET_VF_CFG_CTRL_LINK_STATE, link_state);
	ग_लिखोb(vf_ctrl, app->pf->vfcfg_tbl2 + vf_offset);

	वापस nfp_net_sriov_update(app, vf, NFP_NET_VF_CFG_MB_UPD_LINK_STATE,
				    "link state");
पूर्ण

पूर्णांक nfp_app_get_vf_config(काष्ठा net_device *netdev, पूर्णांक vf,
			  काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा nfp_app *app = nfp_app_from_netdev(netdev);
	अचिन्हित पूर्णांक vf_offset;
	u16 vlan_tci;
	u32 mac_hi;
	u16 mac_lo;
	u8 flags;
	पूर्णांक err;

	err = nfp_net_sriov_check(app, vf, 0, "");
	अगर (err)
		वापस err;

	vf_offset = NFP_NET_VF_CFG_MB_SZ + vf * NFP_NET_VF_CFG_SZ;

	mac_hi = पढ़ोl(app->pf->vfcfg_tbl2 + vf_offset);
	mac_lo = पढ़ोw(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_MAC_LO);

	flags = पढ़ोb(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_CTRL);
	vlan_tci = पढ़ोw(app->pf->vfcfg_tbl2 + vf_offset + NFP_NET_VF_CFG_VLAN);

	स_रखो(ivi, 0, माप(*ivi));
	ivi->vf = vf;

	put_unaligned_be32(mac_hi, &ivi->mac[0]);
	put_unaligned_be16(mac_lo, &ivi->mac[4]);

	ivi->vlan = FIELD_GET(NFP_NET_VF_CFG_VLAN_VID, vlan_tci);
	ivi->qos = FIELD_GET(NFP_NET_VF_CFG_VLAN_QOS, vlan_tci);

	ivi->spoofchk = FIELD_GET(NFP_NET_VF_CFG_CTRL_SPOOF, flags);
	ivi->trusted = FIELD_GET(NFP_NET_VF_CFG_CTRL_TRUST, flags);
	ivi->linkstate = FIELD_GET(NFP_NET_VF_CFG_CTRL_LINK_STATE, flags);

	वापस 0;
पूर्ण
