<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 or MIT)
/*
 * DSA driver क्रम:
 * Hirschmann Hellcreek TSN चयन.
 *
 * Copyright (C) 2019-2021 Linutronix GmbH
 * Author Kurt Kanzenbach <kurt@linutronix.de>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <net/dsa.h>

#समावेश "hellcreek.h"
#समावेश "hellcreek_ptp.h"
#समावेश "hellcreek_hwtstamp.h"

अटल स्थिर काष्ठा hellcreek_counter hellcreek_counter[] = अणु
	अणु 0x00, "RxFiltered", पूर्ण,
	अणु 0x01, "RxOctets1k", पूर्ण,
	अणु 0x02, "RxVTAG", पूर्ण,
	अणु 0x03, "RxL2BAD", पूर्ण,
	अणु 0x04, "RxOverloadDrop", पूर्ण,
	अणु 0x05, "RxUC", पूर्ण,
	अणु 0x06, "RxMC", पूर्ण,
	अणु 0x07, "RxBC", पूर्ण,
	अणु 0x08, "RxRS<64", पूर्ण,
	अणु 0x09, "RxRS64", पूर्ण,
	अणु 0x0a, "RxRS65_127", पूर्ण,
	अणु 0x0b, "RxRS128_255", पूर्ण,
	अणु 0x0c, "RxRS256_511", पूर्ण,
	अणु 0x0d, "RxRS512_1023", पूर्ण,
	अणु 0x0e, "RxRS1024_1518", पूर्ण,
	अणु 0x0f, "RxRS>1518", पूर्ण,
	अणु 0x10, "TxTailDropQueue0", पूर्ण,
	अणु 0x11, "TxTailDropQueue1", पूर्ण,
	अणु 0x12, "TxTailDropQueue2", पूर्ण,
	अणु 0x13, "TxTailDropQueue3", पूर्ण,
	अणु 0x14, "TxTailDropQueue4", पूर्ण,
	अणु 0x15, "TxTailDropQueue5", पूर्ण,
	अणु 0x16, "TxTailDropQueue6", पूर्ण,
	अणु 0x17, "TxTailDropQueue7", पूर्ण,
	अणु 0x18, "RxTrafficClass0", पूर्ण,
	अणु 0x19, "RxTrafficClass1", पूर्ण,
	अणु 0x1a, "RxTrafficClass2", पूर्ण,
	अणु 0x1b, "RxTrafficClass3", पूर्ण,
	अणु 0x1c, "RxTrafficClass4", पूर्ण,
	अणु 0x1d, "RxTrafficClass5", पूर्ण,
	अणु 0x1e, "RxTrafficClass6", पूर्ण,
	अणु 0x1f, "RxTrafficClass7", पूर्ण,
	अणु 0x21, "TxOctets1k", पूर्ण,
	अणु 0x22, "TxVTAG", पूर्ण,
	अणु 0x23, "TxL2BAD", पूर्ण,
	अणु 0x25, "TxUC", पूर्ण,
	अणु 0x26, "TxMC", पूर्ण,
	अणु 0x27, "TxBC", पूर्ण,
	अणु 0x28, "TxTS<64", पूर्ण,
	अणु 0x29, "TxTS64", पूर्ण,
	अणु 0x2a, "TxTS65_127", पूर्ण,
	अणु 0x2b, "TxTS128_255", पूर्ण,
	अणु 0x2c, "TxTS256_511", पूर्ण,
	अणु 0x2d, "TxTS512_1023", पूर्ण,
	अणु 0x2e, "TxTS1024_1518", पूर्ण,
	अणु 0x2f, "TxTS>1518", पूर्ण,
	अणु 0x30, "TxTrafficClassOverrun0", पूर्ण,
	अणु 0x31, "TxTrafficClassOverrun1", पूर्ण,
	अणु 0x32, "TxTrafficClassOverrun2", पूर्ण,
	अणु 0x33, "TxTrafficClassOverrun3", पूर्ण,
	अणु 0x34, "TxTrafficClassOverrun4", पूर्ण,
	अणु 0x35, "TxTrafficClassOverrun5", पूर्ण,
	अणु 0x36, "TxTrafficClassOverrun6", पूर्ण,
	अणु 0x37, "TxTrafficClassOverrun7", पूर्ण,
	अणु 0x38, "TxTrafficClass0", पूर्ण,
	अणु 0x39, "TxTrafficClass1", पूर्ण,
	अणु 0x3a, "TxTrafficClass2", पूर्ण,
	अणु 0x3b, "TxTrafficClass3", पूर्ण,
	अणु 0x3c, "TxTrafficClass4", पूर्ण,
	अणु 0x3d, "TxTrafficClass5", पूर्ण,
	अणु 0x3e, "TxTrafficClass6", पूर्ण,
	अणु 0x3f, "TxTrafficClass7", पूर्ण,
पूर्ण;

अटल u16 hellcreek_पढ़ो(काष्ठा hellcreek *hellcreek, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोw(hellcreek->base + offset);
पूर्ण

अटल u16 hellcreek_पढ़ो_ctrl(काष्ठा hellcreek *hellcreek)
अणु
	वापस पढ़ोw(hellcreek->base + HR_CTRL_C);
पूर्ण

अटल u16 hellcreek_पढ़ो_stat(काष्ठा hellcreek *hellcreek)
अणु
	वापस पढ़ोw(hellcreek->base + HR_SWSTAT);
पूर्ण

अटल व्योम hellcreek_ग_लिखो(काष्ठा hellcreek *hellcreek, u16 data,
			    अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोw(data, hellcreek->base + offset);
पूर्ण

अटल व्योम hellcreek_select_port(काष्ठा hellcreek *hellcreek, पूर्णांक port)
अणु
	u16 val = port << HR_PSEL_PTWSEL_SHIFT;

	hellcreek_ग_लिखो(hellcreek, val, HR_PSEL);
पूर्ण

अटल व्योम hellcreek_select_prio(काष्ठा hellcreek *hellcreek, पूर्णांक prio)
अणु
	u16 val = prio << HR_PSEL_PRTCWSEL_SHIFT;

	hellcreek_ग_लिखो(hellcreek, val, HR_PSEL);
पूर्ण

अटल व्योम hellcreek_select_counter(काष्ठा hellcreek *hellcreek, पूर्णांक counter)
अणु
	u16 val = counter << HR_CSEL_SHIFT;

	hellcreek_ग_लिखो(hellcreek, val, HR_CSEL);

	/* Data sheet states to रुको at least 20 पूर्णांकernal घड़ी cycles */
	ndelay(200);
पूर्ण

अटल व्योम hellcreek_select_vlan(काष्ठा hellcreek *hellcreek, पूर्णांक vid,
				  bool pvid)
अणु
	u16 val = 0;

	/* Set pvid bit first */
	अगर (pvid)
		val |= HR_VIDCFG_PVID;
	hellcreek_ग_लिखो(hellcreek, val, HR_VIDCFG);

	/* Set vlan */
	val |= vid << HR_VIDCFG_VID_SHIFT;
	hellcreek_ग_लिखो(hellcreek, val, HR_VIDCFG);
पूर्ण

अटल व्योम hellcreek_select_tgd(काष्ठा hellcreek *hellcreek, पूर्णांक port)
अणु
	u16 val = port << TR_TGDSEL_TDGSEL_SHIFT;

	hellcreek_ग_लिखो(hellcreek, val, TR_TGDSEL);
पूर्ण

अटल पूर्णांक hellcreek_रुको_until_पढ़ोy(काष्ठा hellcreek *hellcreek)
अणु
	u16 val;

	/* Wait up to 1ms, although 3 us should be enough */
	वापस पढ़ोx_poll_समयout(hellcreek_पढ़ो_ctrl, hellcreek,
				  val, val & HR_CTRL_C_READY,
				  3, 1000);
पूर्ण

अटल पूर्णांक hellcreek_रुको_until_transitioned(काष्ठा hellcreek *hellcreek)
अणु
	u16 val;

	वापस पढ़ोx_poll_समयout_atomic(hellcreek_पढ़ो_ctrl, hellcreek,
					 val, !(val & HR_CTRL_C_TRANSITION),
					 1, 1000);
पूर्ण

अटल पूर्णांक hellcreek_रुको_fdb_पढ़ोy(काष्ठा hellcreek *hellcreek)
अणु
	u16 val;

	वापस पढ़ोx_poll_समयout_atomic(hellcreek_पढ़ो_stat, hellcreek,
					 val, !(val & HR_SWSTAT_BUSY),
					 1, 1000);
पूर्ण

अटल पूर्णांक hellcreek_detect(काष्ठा hellcreek *hellcreek)
अणु
	u16 id, rel_low, rel_high, date_low, date_high, tgd_ver;
	u8 tgd_maj, tgd_min;
	u32 rel, date;

	id	  = hellcreek_पढ़ो(hellcreek, HR_MODID_C);
	rel_low	  = hellcreek_पढ़ो(hellcreek, HR_REL_L_C);
	rel_high  = hellcreek_पढ़ो(hellcreek, HR_REL_H_C);
	date_low  = hellcreek_पढ़ो(hellcreek, HR_BLD_L_C);
	date_high = hellcreek_पढ़ो(hellcreek, HR_BLD_H_C);
	tgd_ver   = hellcreek_पढ़ो(hellcreek, TR_TGDVER);

	अगर (id != hellcreek->pdata->module_id)
		वापस -ENODEV;

	rel	= rel_low | (rel_high << 16);
	date	= date_low | (date_high << 16);
	tgd_maj = (tgd_ver & TR_TGDVER_REV_MAJ_MASK) >> TR_TGDVER_REV_MAJ_SHIFT;
	tgd_min = (tgd_ver & TR_TGDVER_REV_MIN_MASK) >> TR_TGDVER_REV_MIN_SHIFT;

	dev_info(hellcreek->dev, "Module ID=%02x Release=%04x Date=%04x TGD Version=%02x.%02x\n",
		 id, rel, date, tgd_maj, tgd_min);

	वापस 0;
पूर्ण

अटल व्योम hellcreek_feature_detect(काष्ठा hellcreek *hellcreek)
अणु
	u16 features;

	features = hellcreek_पढ़ो(hellcreek, HR_FEABITS0);

	/* Only detect the size of the FDB table. The size and current
	 * utilization can be queried via devlink.
	 */
	hellcreek->fdb_entries = ((features & HR_FEABITS0_FDBBINS_MASK) >>
			       HR_FEABITS0_FDBBINS_SHIFT) * 32;
पूर्ण

अटल क्रमागत dsa_tag_protocol hellcreek_get_tag_protocol(काष्ठा dsa_चयन *ds,
							पूर्णांक port,
							क्रमागत dsa_tag_protocol mp)
अणु
	वापस DSA_TAG_PROTO_HELLCREEK;
पूर्ण

अटल पूर्णांक hellcreek_port_enable(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा phy_device *phy)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;
	u16 val;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "Enable port %d\n", port);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, port);
	val = hellcreek_port->ptcfg;
	val |= HR_PTCFG_ADMIN_EN;
	hellcreek_ग_लिखो(hellcreek, val, HR_PTCFG);
	hellcreek_port->ptcfg = val;

	mutex_unlock(&hellcreek->reg_lock);

	वापस 0;
पूर्ण

अटल व्योम hellcreek_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;
	u16 val;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "Disable port %d\n", port);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, port);
	val = hellcreek_port->ptcfg;
	val &= ~HR_PTCFG_ADMIN_EN;
	hellcreek_ग_लिखो(hellcreek, val, HR_PTCFG);
	hellcreek_port->ptcfg = val;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल व्योम hellcreek_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  u32 stringset, uपूर्णांक8_t *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hellcreek_counter); ++i) अणु
		स्थिर काष्ठा hellcreek_counter *counter = &hellcreek_counter[i];

		strlcpy(data + i * ETH_GSTRING_LEN,
			counter->name, ETH_GSTRING_LEN);
	पूर्ण
पूर्ण

अटल पूर्णांक hellcreek_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	अगर (sset != ETH_SS_STATS)
		वापस 0;

	वापस ARRAY_SIZE(hellcreek_counter);
पूर्ण

अटल व्योम hellcreek_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
					uपूर्णांक64_t *data)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;
	पूर्णांक i;

	hellcreek_port = &hellcreek->ports[port];

	क्रम (i = 0; i < ARRAY_SIZE(hellcreek_counter); ++i) अणु
		स्थिर काष्ठा hellcreek_counter *counter = &hellcreek_counter[i];
		u8 offset = counter->offset + port * 64;
		u16 high, low;
		u64 value;

		mutex_lock(&hellcreek->reg_lock);

		hellcreek_select_counter(hellcreek, offset);

		/* The रेजिस्टरs are locked पूर्णांकernally by selecting the
		 * counter. So low and high can be पढ़ो without पढ़ोing high
		 * again.
		 */
		high  = hellcreek_पढ़ो(hellcreek, HR_CRDH);
		low   = hellcreek_पढ़ो(hellcreek, HR_CRDL);
		value = ((u64)high << 16) | low;

		hellcreek_port->counter_values[i] += value;
		data[i] = hellcreek_port->counter_values[i];

		mutex_unlock(&hellcreek->reg_lock);
	पूर्ण
पूर्ण

अटल u16 hellcreek_निजी_vid(पूर्णांक port)
अणु
	वापस VLAN_N_VID - port + 1;
पूर्ण

अटल पूर्णांक hellcreek_vlan_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक i;

	dev_dbg(hellcreek->dev, "VLAN prepare for port %d\n", port);

	/* Restriction: Make sure that nobody uses the "private" VLANs. These
	 * VLANs are पूर्णांकernally used by the driver to ensure port
	 * separation. Thus, they cannot be used by someone अन्यथा.
	 */
	क्रम (i = 0; i < hellcreek->pdata->num_ports; ++i) अणु
		स्थिर u16 restricted_vid = hellcreek_निजी_vid(i);

		अगर (!dsa_is_user_port(ds, i))
			जारी;

		अगर (vlan->vid == restricted_vid) अणु
			NL_SET_ERR_MSG_MOD(extack, "VID restricted by driver");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hellcreek_select_vlan_params(काष्ठा hellcreek *hellcreek, पूर्णांक port,
					 पूर्णांक *shअगरt, पूर्णांक *mask)
अणु
	चयन (port) अणु
	हाल 0:
		*shअगरt = HR_VIDMBRCFG_P0MBR_SHIFT;
		*mask  = HR_VIDMBRCFG_P0MBR_MASK;
		अवरोध;
	हाल 1:
		*shअगरt = HR_VIDMBRCFG_P1MBR_SHIFT;
		*mask  = HR_VIDMBRCFG_P1MBR_MASK;
		अवरोध;
	हाल 2:
		*shअगरt = HR_VIDMBRCFG_P2MBR_SHIFT;
		*mask  = HR_VIDMBRCFG_P2MBR_MASK;
		अवरोध;
	हाल 3:
		*shअगरt = HR_VIDMBRCFG_P3MBR_SHIFT;
		*mask  = HR_VIDMBRCFG_P3MBR_MASK;
		अवरोध;
	शेष:
		*shअगरt = *mask = 0;
		dev_err(hellcreek->dev, "Unknown port %d selected!\n", port);
	पूर्ण
पूर्ण

अटल व्योम hellcreek_apply_vlan(काष्ठा hellcreek *hellcreek, पूर्णांक port, u16 vid,
				 bool pvid, bool untagged)
अणु
	पूर्णांक shअगरt, mask;
	u16 val;

	dev_dbg(hellcreek->dev, "Apply VLAN: port=%d vid=%u pvid=%d untagged=%d",
		port, vid, pvid, untagged);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, port);
	hellcreek_select_vlan(hellcreek, vid, pvid);

	/* Setup port vlan membership */
	hellcreek_select_vlan_params(hellcreek, port, &shअगरt, &mask);
	val = hellcreek->vidmbrcfg[vid];
	val &= ~mask;
	अगर (untagged)
		val |= HELLCREEK_VLAN_UNTAGGED_MEMBER << shअगरt;
	अन्यथा
		val |= HELLCREEK_VLAN_TAGGED_MEMBER << shअगरt;

	hellcreek_ग_लिखो(hellcreek, val, HR_VIDMBRCFG);
	hellcreek->vidmbrcfg[vid] = val;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल व्योम hellcreek_unapply_vlan(काष्ठा hellcreek *hellcreek, पूर्णांक port,
				   u16 vid)
अणु
	पूर्णांक shअगरt, mask;
	u16 val;

	dev_dbg(hellcreek->dev, "Unapply VLAN: port=%d vid=%u\n", port, vid);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_vlan(hellcreek, vid, false);

	/* Setup port vlan membership */
	hellcreek_select_vlan_params(hellcreek, port, &shअगरt, &mask);
	val = hellcreek->vidmbrcfg[vid];
	val &= ~mask;
	val |= HELLCREEK_VLAN_NO_MEMBER << shअगरt;

	hellcreek_ग_लिखो(hellcreek, val, HR_VIDMBRCFG);
	hellcreek->vidmbrcfg[vid] = val;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल पूर्णांक hellcreek_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
			      काष्ठा netlink_ext_ack *extack)
अणु
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक err;

	err = hellcreek_vlan_prepare(ds, port, vlan, extack);
	अगर (err)
		वापस err;

	dev_dbg(hellcreek->dev, "Add VLAN %d on port %d, %s, %s\n",
		vlan->vid, port, untagged ? "untagged" : "tagged",
		pvid ? "PVID" : "no PVID");

	hellcreek_apply_vlan(hellcreek, port, vlan->vid, pvid, untagged);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	dev_dbg(hellcreek->dev, "Remove VLAN %d on port %d\n", vlan->vid, port);

	hellcreek_unapply_vlan(hellcreek, port, vlan->vid);

	वापस 0;
पूर्ण

अटल व्योम hellcreek_port_stp_state_set(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 u8 state)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;
	स्थिर अक्षर *new_state;
	u16 val;

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_port = &hellcreek->ports[port];
	val = hellcreek_port->ptcfg;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		new_state = "DISABLED";
		val |= HR_PTCFG_BLOCKED;
		val &= ~HR_PTCFG_LEARNING_EN;
		अवरोध;
	हाल BR_STATE_BLOCKING:
		new_state = "BLOCKING";
		val |= HR_PTCFG_BLOCKED;
		val &= ~HR_PTCFG_LEARNING_EN;
		अवरोध;
	हाल BR_STATE_LISTENING:
		new_state = "LISTENING";
		val |= HR_PTCFG_BLOCKED;
		val &= ~HR_PTCFG_LEARNING_EN;
		अवरोध;
	हाल BR_STATE_LEARNING:
		new_state = "LEARNING";
		val |= HR_PTCFG_BLOCKED;
		val |= HR_PTCFG_LEARNING_EN;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		new_state = "FORWARDING";
		val &= ~HR_PTCFG_BLOCKED;
		val |= HR_PTCFG_LEARNING_EN;
		अवरोध;
	शेष:
		new_state = "UNKNOWN";
	पूर्ण

	hellcreek_select_port(hellcreek, port);
	hellcreek_ग_लिखो(hellcreek, val, HR_PTCFG);
	hellcreek_port->ptcfg = val;

	mutex_unlock(&hellcreek->reg_lock);

	dev_dbg(hellcreek->dev, "Configured STP state for port %d: %s\n",
		port, new_state);
पूर्ण

अटल व्योम hellcreek_setup_ingressflt(काष्ठा hellcreek *hellcreek, पूर्णांक port,
				       bool enable)
अणु
	काष्ठा hellcreek_port *hellcreek_port = &hellcreek->ports[port];
	u16 ptcfg;

	mutex_lock(&hellcreek->reg_lock);

	ptcfg = hellcreek_port->ptcfg;

	अगर (enable)
		ptcfg |= HR_PTCFG_INGRESSFLT;
	अन्यथा
		ptcfg &= ~HR_PTCFG_INGRESSFLT;

	hellcreek_select_port(hellcreek, port);
	hellcreek_ग_लिखो(hellcreek, ptcfg, HR_PTCFG);
	hellcreek_port->ptcfg = ptcfg;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल व्योम hellcreek_setup_vlan_awareness(काष्ठा hellcreek *hellcreek,
					   bool enable)
अणु
	u16 swcfg;

	mutex_lock(&hellcreek->reg_lock);

	swcfg = hellcreek->swcfg;

	अगर (enable)
		swcfg |= HR_SWCFG_VLAN_UNAWARE;
	अन्यथा
		swcfg &= ~HR_SWCFG_VLAN_UNAWARE;

	hellcreek_ग_लिखो(hellcreek, swcfg, HR_SWCFG);

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

/* Default setup क्रम DSA: VLAN <X>: CPU and Port <X> egress untagged. */
अटल व्योम hellcreek_setup_vlan_membership(काष्ठा dsa_चयन *ds, पूर्णांक port,
					    bool enabled)
अणु
	स्थिर u16 vid = hellcreek_निजी_vid(port);
	पूर्णांक upstream = dsa_upstream_port(ds, port);
	काष्ठा hellcreek *hellcreek = ds->priv;

	/* Apply vid to port as egress untagged and port vlan id */
	अगर (enabled)
		hellcreek_apply_vlan(hellcreek, port, vid, true, true);
	अन्यथा
		hellcreek_unapply_vlan(hellcreek, port, vid);

	/* Apply vid to cpu port as well */
	अगर (enabled)
		hellcreek_apply_vlan(hellcreek, upstream, vid, false, true);
	अन्यथा
		hellcreek_unapply_vlan(hellcreek, upstream, vid);
पूर्ण

अटल व्योम hellcreek_port_set_ucast_flood(काष्ठा hellcreek *hellcreek,
					   पूर्णांक port, bool enable)
अणु
	काष्ठा hellcreek_port *hellcreek_port;
	u16 val;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "%s unicast flooding on port %d\n",
		enable ? "Enable" : "Disable", port);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, port);
	val = hellcreek_port->ptcfg;
	अगर (enable)
		val &= ~HR_PTCFG_UUC_FLT;
	अन्यथा
		val |= HR_PTCFG_UUC_FLT;
	hellcreek_ग_लिखो(hellcreek, val, HR_PTCFG);
	hellcreek_port->ptcfg = val;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल व्योम hellcreek_port_set_mcast_flood(काष्ठा hellcreek *hellcreek,
					   पूर्णांक port, bool enable)
अणु
	काष्ठा hellcreek_port *hellcreek_port;
	u16 val;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "%s multicast flooding on port %d\n",
		enable ? "Enable" : "Disable", port);

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, port);
	val = hellcreek_port->ptcfg;
	अगर (enable)
		val &= ~HR_PTCFG_UMC_FLT;
	अन्यथा
		val |= HR_PTCFG_UMC_FLT;
	hellcreek_ग_लिखो(hellcreek, val, HR_PTCFG);
	hellcreek_port->ptcfg = val;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल पूर्णांक hellcreek_pre_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      काष्ठा चयनdev_brport_flags flags,
				      काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flags.mask & ~(BR_FLOOD | BR_MCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_bridge_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा चयनdev_brport_flags flags,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	अगर (flags.mask & BR_FLOOD)
		hellcreek_port_set_ucast_flood(hellcreek, port,
					       !!(flags.val & BR_FLOOD));

	अगर (flags.mask & BR_MCAST_FLOOD)
		hellcreek_port_set_mcast_flood(hellcreek, port,
					       !!(flags.val & BR_MCAST_FLOOD));

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
				      काष्ठा net_device *br)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	dev_dbg(hellcreek->dev, "Port %d joins a bridge\n", port);

	/* When joining a vlan_filtering bridge, keep the चयन VLAN aware */
	अगर (!ds->vlan_filtering)
		hellcreek_setup_vlan_awareness(hellcreek, false);

	/* Drop निजी vlans */
	hellcreek_setup_vlan_membership(ds, port, false);

	वापस 0;
पूर्ण

अटल व्योम hellcreek_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
					काष्ठा net_device *br)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	dev_dbg(hellcreek->dev, "Port %d leaves a bridge\n", port);

	/* Enable VLAN awareness */
	hellcreek_setup_vlan_awareness(hellcreek, true);

	/* Enable निजी vlans */
	hellcreek_setup_vlan_membership(ds, port, true);
पूर्ण

अटल पूर्णांक __hellcreek_fdb_add(काष्ठा hellcreek *hellcreek,
			       स्थिर काष्ठा hellcreek_fdb_entry *entry)
अणु
	u16 meta = 0;

	dev_dbg(hellcreek->dev, "Add static FDB entry: MAC=%pM, MASK=0x%02x, "
		"OBT=%d, REPRIO_EN=%d, PRIO=%d\n", entry->mac, entry->porपंचांगask,
		entry->is_obt, entry->reprio_en, entry->reprio_tc);

	/* Add mac address */
	hellcreek_ग_लिखो(hellcreek, entry->mac[1] | (entry->mac[0] << 8), HR_FDBWDH);
	hellcreek_ग_लिखो(hellcreek, entry->mac[3] | (entry->mac[2] << 8), HR_FDBWDM);
	hellcreek_ग_लिखो(hellcreek, entry->mac[5] | (entry->mac[4] << 8), HR_FDBWDL);

	/* Meta data */
	meta |= entry->porपंचांगask << HR_FDBWRM0_PORTMASK_SHIFT;
	अगर (entry->is_obt)
		meta |= HR_FDBWRM0_OBT;
	अगर (entry->reprio_en) अणु
		meta |= HR_FDBWRM0_REPRIO_EN;
		meta |= entry->reprio_tc << HR_FDBWRM0_REPRIO_TC_SHIFT;
	पूर्ण
	hellcreek_ग_लिखो(hellcreek, meta, HR_FDBWRM0);

	/* Commit */
	hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBWRCMD);

	/* Wait until करोne */
	वापस hellcreek_रुको_fdb_पढ़ोy(hellcreek);
पूर्ण

अटल पूर्णांक __hellcreek_fdb_del(काष्ठा hellcreek *hellcreek,
			       स्थिर काष्ठा hellcreek_fdb_entry *entry)
अणु
	dev_dbg(hellcreek->dev, "Delete FDB entry: MAC=%pM!\n", entry->mac);

	/* Delete by matching idx */
	hellcreek_ग_लिखो(hellcreek, entry->idx | HR_FDBWRCMD_FDBDEL, HR_FDBWRCMD);

	/* Wait until करोne */
	वापस hellcreek_रुको_fdb_पढ़ोy(hellcreek);
पूर्ण

अटल व्योम hellcreek_populate_fdb_entry(काष्ठा hellcreek *hellcreek,
					 काष्ठा hellcreek_fdb_entry *entry,
					 माप_प्रकार idx)
अणु
	अचिन्हित अक्षर addr[ETH_ALEN];
	u16 meta, mac;

	/* Read values */
	meta	= hellcreek_पढ़ो(hellcreek, HR_FDBMDRD);
	mac	= hellcreek_पढ़ो(hellcreek, HR_FDBRDL);
	addr[5] = mac & 0xff;
	addr[4] = (mac & 0xff00) >> 8;
	mac	= hellcreek_पढ़ो(hellcreek, HR_FDBRDM);
	addr[3] = mac & 0xff;
	addr[2] = (mac & 0xff00) >> 8;
	mac	= hellcreek_पढ़ो(hellcreek, HR_FDBRDH);
	addr[1] = mac & 0xff;
	addr[0] = (mac & 0xff00) >> 8;

	/* Populate @entry */
	स_नकल(entry->mac, addr, माप(addr));
	entry->idx	    = idx;
	entry->porपंचांगask	    = (meta & HR_FDBMDRD_PORTMASK_MASK) >>
		HR_FDBMDRD_PORTMASK_SHIFT;
	entry->age	    = (meta & HR_FDBMDRD_AGE_MASK) >>
		HR_FDBMDRD_AGE_SHIFT;
	entry->is_obt	    = !!(meta & HR_FDBMDRD_OBT);
	entry->pass_blocked = !!(meta & HR_FDBMDRD_PASS_BLOCKED);
	entry->is_अटल    = !!(meta & HR_FDBMDRD_STATIC);
	entry->reprio_tc    = (meta & HR_FDBMDRD_REPRIO_TC_MASK) >>
		HR_FDBMDRD_REPRIO_TC_SHIFT;
	entry->reprio_en    = !!(meta & HR_FDBMDRD_REPRIO_EN);
पूर्ण

/* Retrieve the index of a FDB entry by mac address. Currently we search through
 * the complete table in hardware. If that's too slow, we might have to cache
 * the complete FDB table in software.
 */
अटल पूर्णांक hellcreek_fdb_get(काष्ठा hellcreek *hellcreek,
			     स्थिर अचिन्हित अक्षर *dest,
			     काष्ठा hellcreek_fdb_entry *entry)
अणु
	माप_प्रकार i;

	/* Set पढ़ो poपूर्णांकer to zero: The पढ़ो of HR_FDBMAX (पढ़ो-only रेजिस्टर)
	 * should reset the पूर्णांकernal poपूर्णांकer. But, that करोesn't work. The venकरोr
	 * suggested a subsequent ग_लिखो as workaround. Same क्रम HR_FDBRDH below.
	 */
	hellcreek_पढ़ो(hellcreek, HR_FDBMAX);
	hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBMAX);

	/* We have to पढ़ो the complete table, because the चयन/driver might
	 * enter new entries anywhere.
	 */
	क्रम (i = 0; i < hellcreek->fdb_entries; ++i) अणु
		काष्ठा hellcreek_fdb_entry पंचांगp = अणु 0 पूर्ण;

		/* Read entry */
		hellcreek_populate_fdb_entry(hellcreek, &पंचांगp, i);

		/* Force next entry */
		hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBRDH);

		अगर (स_भेद(पंचांगp.mac, dest, ETH_ALEN))
			जारी;

		/* Match found */
		स_नकल(entry, &पंचांगp, माप(*entry));

		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक hellcreek_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा hellcreek_fdb_entry entry = अणु 0 पूर्ण;
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक ret;

	dev_dbg(hellcreek->dev, "Add FDB entry for MAC=%pM\n", addr);

	mutex_lock(&hellcreek->reg_lock);

	ret = hellcreek_fdb_get(hellcreek, addr, &entry);
	अगर (ret) अणु
		/* Not found */
		स_नकल(entry.mac, addr, माप(entry.mac));
		entry.porपंचांगask = BIT(port);

		ret = __hellcreek_fdb_add(hellcreek, &entry);
		अगर (ret) अणु
			dev_err(hellcreek->dev, "Failed to add FDB entry!\n");
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Found */
		ret = __hellcreek_fdb_del(hellcreek, &entry);
		अगर (ret) अणु
			dev_err(hellcreek->dev, "Failed to delete FDB entry!\n");
			जाओ out;
		पूर्ण

		entry.porपंचांगask |= BIT(port);

		ret = __hellcreek_fdb_add(hellcreek, &entry);
		अगर (ret) अणु
			dev_err(hellcreek->dev, "Failed to add FDB entry!\n");
			जाओ out;
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&hellcreek->reg_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hellcreek_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा hellcreek_fdb_entry entry = अणु 0 पूर्ण;
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक ret;

	dev_dbg(hellcreek->dev, "Delete FDB entry for MAC=%pM\n", addr);

	mutex_lock(&hellcreek->reg_lock);

	ret = hellcreek_fdb_get(hellcreek, addr, &entry);
	अगर (ret) अणु
		/* Not found */
		dev_err(hellcreek->dev, "FDB entry for deletion not found!\n");
	पूर्ण अन्यथा अणु
		/* Found */
		ret = __hellcreek_fdb_del(hellcreek, &entry);
		अगर (ret) अणु
			dev_err(hellcreek->dev, "Failed to delete FDB entry!\n");
			जाओ out;
		पूर्ण

		entry.porपंचांगask &= ~BIT(port);

		अगर (entry.porपंचांगask != 0x00) अणु
			ret = __hellcreek_fdb_add(hellcreek, &entry);
			अगर (ret) अणु
				dev_err(hellcreek->dev, "Failed to add FDB entry!\n");
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	mutex_unlock(&hellcreek->reg_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hellcreek_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	u16 entries;
	माप_प्रकार i;

	mutex_lock(&hellcreek->reg_lock);

	/* Set पढ़ो poपूर्णांकer to zero: The पढ़ो of HR_FDBMAX (पढ़ो-only रेजिस्टर)
	 * should reset the पूर्णांकernal poपूर्णांकer. But, that करोesn't work. The venकरोr
	 * suggested a subsequent ग_लिखो as workaround. Same क्रम HR_FDBRDH below.
	 */
	entries = hellcreek_पढ़ो(hellcreek, HR_FDBMAX);
	hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBMAX);

	dev_dbg(hellcreek->dev, "FDB dump for port %d, entries=%d!\n", port, entries);

	/* Read table */
	क्रम (i = 0; i < hellcreek->fdb_entries; ++i) अणु
		अचिन्हित अक्षर null_addr[ETH_ALEN] = अणु 0 पूर्ण;
		काष्ठा hellcreek_fdb_entry entry = अणु 0 पूर्ण;

		/* Read entry */
		hellcreek_populate_fdb_entry(hellcreek, &entry, i);

		/* Force next entry */
		hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBRDH);

		/* Check valid */
		अगर (!स_भेद(entry.mac, null_addr, ETH_ALEN))
			जारी;

		/* Check port mask */
		अगर (!(entry.porपंचांगask & BIT(port)))
			जारी;

		cb(entry.mac, 0, entry.is_अटल, data);
	पूर्ण

	mutex_unlock(&hellcreek->reg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    bool vlan_filtering,
				    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	dev_dbg(hellcreek->dev, "%s VLAN filtering on port %d\n",
		vlan_filtering ? "Enable" : "Disable", port);

	/* Configure port to drop packages with not known vids */
	hellcreek_setup_ingressflt(hellcreek, port, vlan_filtering);

	/* Enable VLAN awareness on the चयन. This save due to
	 * ds->vlan_filtering_is_global.
	 */
	hellcreek_setup_vlan_awareness(hellcreek, vlan_filtering);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_enable_ip_core(काष्ठा hellcreek *hellcreek)
अणु
	पूर्णांक ret;
	u16 val;

	mutex_lock(&hellcreek->reg_lock);

	val = hellcreek_पढ़ो(hellcreek, HR_CTRL_C);
	val |= HR_CTRL_C_ENABLE;
	hellcreek_ग_लिखो(hellcreek, val, HR_CTRL_C);
	ret = hellcreek_रुको_until_transitioned(hellcreek);

	mutex_unlock(&hellcreek->reg_lock);

	वापस ret;
पूर्ण

अटल व्योम hellcreek_setup_cpu_and_tunnel_port(काष्ठा hellcreek *hellcreek)
अणु
	काष्ठा hellcreek_port *tunnel_port = &hellcreek->ports[TUNNEL_PORT];
	काष्ठा hellcreek_port *cpu_port = &hellcreek->ports[CPU_PORT];
	u16 ptcfg = 0;

	ptcfg |= HR_PTCFG_LEARNING_EN | HR_PTCFG_ADMIN_EN;

	mutex_lock(&hellcreek->reg_lock);

	hellcreek_select_port(hellcreek, CPU_PORT);
	hellcreek_ग_लिखो(hellcreek, ptcfg, HR_PTCFG);

	hellcreek_select_port(hellcreek, TUNNEL_PORT);
	hellcreek_ग_लिखो(hellcreek, ptcfg, HR_PTCFG);

	cpu_port->ptcfg	   = ptcfg;
	tunnel_port->ptcfg = ptcfg;

	mutex_unlock(&hellcreek->reg_lock);
पूर्ण

अटल व्योम hellcreek_setup_tc_identity_mapping(काष्ठा hellcreek *hellcreek)
अणु
	पूर्णांक i;

	/* The चयन has multiple egress queues per port. The queue is selected
	 * via the PCP field in the VLAN header. The चयन पूर्णांकernally deals
	 * with traffic classes instead of PCP values and this mapping is
	 * configurable.
	 *
	 * The शेष mapping is (PCP - TC):
	 *  7 - 7
	 *  6 - 6
	 *  5 - 5
	 *  4 - 4
	 *  3 - 3
	 *  2 - 1
	 *  1 - 0
	 *  0 - 2
	 *
	 * The शेष should be an identity mapping.
	 */

	क्रम (i = 0; i < 8; ++i) अणु
		mutex_lock(&hellcreek->reg_lock);

		hellcreek_select_prio(hellcreek, i);
		hellcreek_ग_लिखो(hellcreek,
				i << HR_PRTCCFG_PCP_TC_MAP_SHIFT,
				HR_PRTCCFG);

		mutex_unlock(&hellcreek->reg_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक hellcreek_setup_fdb(काष्ठा hellcreek *hellcreek)
अणु
	अटल काष्ठा hellcreek_fdb_entry ptp = अणु
		/* MAC: 01-1B-19-00-00-00 */
		.mac	      = अणु 0x01, 0x1b, 0x19, 0x00, 0x00, 0x00 पूर्ण,
		.porपंचांगask     = 0x03,	/* Management ports */
		.age	      = 0,
		.is_obt	      = 0,
		.pass_blocked = 0,
		.is_अटल    = 1,
		.reprio_tc    = 6,	/* TC: 6 as per IEEE 802.1AS */
		.reprio_en    = 1,
	पूर्ण;
	अटल काष्ठा hellcreek_fdb_entry p2p = अणु
		/* MAC: 01-80-C2-00-00-0E */
		.mac	      = अणु 0x01, 0x80, 0xc2, 0x00, 0x00, 0x0e पूर्ण,
		.porपंचांगask     = 0x03,	/* Management ports */
		.age	      = 0,
		.is_obt	      = 0,
		.pass_blocked = 0,
		.is_अटल    = 1,
		.reprio_tc    = 6,	/* TC: 6 as per IEEE 802.1AS */
		.reprio_en    = 1,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&hellcreek->reg_lock);
	ret = __hellcreek_fdb_add(hellcreek, &ptp);
	अगर (ret)
		जाओ out;
	ret = __hellcreek_fdb_add(hellcreek, &p2p);
out:
	mutex_unlock(&hellcreek->reg_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hellcreek_devlink_info_get(काष्ठा dsa_चयन *ds,
				      काष्ठा devlink_info_req *req,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक ret;

	ret = devlink_info_driver_name_put(req, "hellcreek");
	अगर (ret)
		वापस ret;

	वापस devlink_info_version_fixed_put(req,
					      DEVLINK_INFO_VERSION_GENERIC_ASIC_ID,
					      hellcreek->pdata->name);
पूर्ण

अटल u64 hellcreek_devlink_vlan_table_get(व्योम *priv)
अणु
	काष्ठा hellcreek *hellcreek = priv;
	u64 count = 0;
	पूर्णांक i;

	mutex_lock(&hellcreek->reg_lock);
	क्रम (i = 0; i < VLAN_N_VID; ++i)
		अगर (hellcreek->vidmbrcfg[i])
			count++;
	mutex_unlock(&hellcreek->reg_lock);

	वापस count;
पूर्ण

अटल u64 hellcreek_devlink_fdb_table_get(व्योम *priv)
अणु
	काष्ठा hellcreek *hellcreek = priv;
	u64 count = 0;

	/* Reading this रेजिस्टर has side effects. Synchronize against the other
	 * FDB operations.
	 */
	mutex_lock(&hellcreek->reg_lock);
	count = hellcreek_पढ़ो(hellcreek, HR_FDBMAX);
	mutex_unlock(&hellcreek->reg_lock);

	वापस count;
पूर्ण

अटल पूर्णांक hellcreek_setup_devlink_resources(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा devlink_resource_size_params size_vlan_params;
	काष्ठा devlink_resource_size_params size_fdb_params;
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक err;

	devlink_resource_size_params_init(&size_vlan_params, VLAN_N_VID,
					  VLAN_N_VID,
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	devlink_resource_size_params_init(&size_fdb_params,
					  hellcreek->fdb_entries,
					  hellcreek->fdb_entries,
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	err = dsa_devlink_resource_रेजिस्टर(ds, "VLAN", VLAN_N_VID,
					    HELLCREEK_DEVLINK_PARAM_ID_VLAN_TABLE,
					    DEVLINK_RESOURCE_ID_PARENT_TOP,
					    &size_vlan_params);
	अगर (err)
		जाओ out;

	err = dsa_devlink_resource_रेजिस्टर(ds, "FDB", hellcreek->fdb_entries,
					    HELLCREEK_DEVLINK_PARAM_ID_FDB_TABLE,
					    DEVLINK_RESOURCE_ID_PARENT_TOP,
					    &size_fdb_params);
	अगर (err)
		जाओ out;

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      HELLCREEK_DEVLINK_PARAM_ID_VLAN_TABLE,
					      hellcreek_devlink_vlan_table_get,
					      hellcreek);

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      HELLCREEK_DEVLINK_PARAM_ID_FDB_TABLE,
					      hellcreek_devlink_fdb_table_get,
					      hellcreek);

	वापस 0;

out:
	dsa_devlink_resources_unरेजिस्टर(ds);

	वापस err;
पूर्ण

अटल पूर्णांक hellcreek_devlink_region_vlan_snapshot(काष्ठा devlink *dl,
						  स्थिर काष्ठा devlink_region_ops *ops,
						  काष्ठा netlink_ext_ack *extack,
						  u8 **data)
अणु
	काष्ठा hellcreek_devlink_vlan_entry *table, *entry;
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा hellcreek *hellcreek = ds->priv;
	पूर्णांक i;

	table = kसुस्मृति(VLAN_N_VID, माप(*entry), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	entry = table;

	mutex_lock(&hellcreek->reg_lock);
	क्रम (i = 0; i < VLAN_N_VID; ++i, ++entry) अणु
		entry->member = hellcreek->vidmbrcfg[i];
		entry->vid    = i;
	पूर्ण
	mutex_unlock(&hellcreek->reg_lock);

	*data = (u8 *)table;

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_devlink_region_fdb_snapshot(काष्ठा devlink *dl,
						 स्थिर काष्ठा devlink_region_ops *ops,
						 काष्ठा netlink_ext_ack *extack,
						 u8 **data)
अणु
	काष्ठा dsa_चयन *ds = dsa_devlink_to_ds(dl);
	काष्ठा hellcreek_fdb_entry *table, *entry;
	काष्ठा hellcreek *hellcreek = ds->priv;
	माप_प्रकार i;

	table = kसुस्मृति(hellcreek->fdb_entries, माप(*entry), GFP_KERNEL);
	अगर (!table)
		वापस -ENOMEM;

	entry = table;

	mutex_lock(&hellcreek->reg_lock);

	/* Start table पढ़ो */
	hellcreek_पढ़ो(hellcreek, HR_FDBMAX);
	hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBMAX);

	क्रम (i = 0; i < hellcreek->fdb_entries; ++i, ++entry) अणु
		/* Read current entry */
		hellcreek_populate_fdb_entry(hellcreek, entry, i);

		/* Advance पढ़ो poपूर्णांकer */
		hellcreek_ग_लिखो(hellcreek, 0x00, HR_FDBRDH);
	पूर्ण

	mutex_unlock(&hellcreek->reg_lock);

	*data = (u8 *)table;

	वापस 0;
पूर्ण

अटल काष्ठा devlink_region_ops hellcreek_region_vlan_ops = अणु
	.name	    = "vlan",
	.snapshot   = hellcreek_devlink_region_vlan_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

अटल काष्ठा devlink_region_ops hellcreek_region_fdb_ops = अणु
	.name	    = "fdb",
	.snapshot   = hellcreek_devlink_region_fdb_snapshot,
	.deकाष्ठाor = kमुक्त,
पूर्ण;

अटल पूर्णांक hellcreek_setup_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा devlink_region_ops *ops;
	काष्ठा devlink_region *region;
	u64 size;
	पूर्णांक ret;

	/* VLAN table */
	size = VLAN_N_VID * माप(काष्ठा hellcreek_devlink_vlan_entry);
	ops  = &hellcreek_region_vlan_ops;

	region = dsa_devlink_region_create(ds, ops, 1, size);
	अगर (IS_ERR(region))
		वापस PTR_ERR(region);

	hellcreek->vlan_region = region;

	/* FDB table */
	size = hellcreek->fdb_entries * माप(काष्ठा hellcreek_fdb_entry);
	ops  = &hellcreek_region_fdb_ops;

	region = dsa_devlink_region_create(ds, ops, 1, size);
	अगर (IS_ERR(region)) अणु
		ret = PTR_ERR(region);
		जाओ err_fdb;
	पूर्ण

	hellcreek->fdb_region = region;

	वापस 0;

err_fdb:
	dsa_devlink_region_destroy(hellcreek->vlan_region);

	वापस ret;
पूर्ण

अटल व्योम hellcreek_tearकरोwn_devlink_regions(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;

	dsa_devlink_region_destroy(hellcreek->fdb_region);
	dsa_devlink_region_destroy(hellcreek->vlan_region);
पूर्ण

अटल पूर्णांक hellcreek_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	u16 swcfg = 0;
	पूर्णांक ret, i;

	dev_dbg(hellcreek->dev, "Set up the switch\n");

	/* Let's go */
	ret = hellcreek_enable_ip_core(hellcreek);
	अगर (ret) अणु
		dev_err(hellcreek->dev, "Failed to enable IP core!\n");
		वापस ret;
	पूर्ण

	/* Enable CPU/Tunnel ports */
	hellcreek_setup_cpu_and_tunnel_port(hellcreek);

	/* Switch config: Keep शेषs, enable FDB aging and learning and tag
	 * each frame from/to cpu port क्रम DSA tagging.  Also enable the length
	 * aware shaping mode. This eliminates the need क्रम Qbv guard bands.
	 */
	swcfg |= HR_SWCFG_FDBAGE_EN |
		HR_SWCFG_FDBLRN_EN  |
		HR_SWCFG_ALWAYS_OBT |
		(HR_SWCFG_LAS_ON << HR_SWCFG_LAS_MODE_SHIFT);
	hellcreek->swcfg = swcfg;
	hellcreek_ग_लिखो(hellcreek, swcfg, HR_SWCFG);

	/* Initial vlan membership to reflect port separation */
	क्रम (i = 0; i < ds->num_ports; ++i) अणु
		अगर (!dsa_is_user_port(ds, i))
			जारी;

		hellcreek_setup_vlan_membership(ds, i, true);
	पूर्ण

	/* Configure PCP <-> TC mapping */
	hellcreek_setup_tc_identity_mapping(hellcreek);

	/* The VLAN awareness is a global चयन setting. Thereक्रमe, mixed vlan
	 * filtering setups are not supported.
	 */
	ds->vlan_filtering_is_global = true;

	/* Intercept _all_ PTP multicast traffic */
	ret = hellcreek_setup_fdb(hellcreek);
	अगर (ret) अणु
		dev_err(hellcreek->dev,
			"Failed to insert static PTP FDB entries\n");
		वापस ret;
	पूर्ण

	/* Register devlink resources with DSA */
	ret = hellcreek_setup_devlink_resources(ds);
	अगर (ret) अणु
		dev_err(hellcreek->dev,
			"Failed to setup devlink resources!\n");
		वापस ret;
	पूर्ण

	ret = hellcreek_setup_devlink_regions(ds);
	अगर (ret) अणु
		dev_err(hellcreek->dev,
			"Failed to setup devlink regions!\n");
		जाओ err_regions;
	पूर्ण

	वापस 0;

err_regions:
	dsa_devlink_resources_unरेजिस्टर(ds);

	वापस ret;
पूर्ण

अटल व्योम hellcreek_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	hellcreek_tearकरोwn_devlink_regions(ds);
	dsa_devlink_resources_unरेजिस्टर(ds);
पूर्ण

अटल व्योम hellcreek_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       अचिन्हित दीर्घ *supported,
				       काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;
	काष्ठा hellcreek *hellcreek = ds->priv;

	dev_dbg(hellcreek->dev, "Phylink validate for port %d\n", port);

	/* The MAC settings are a hardware configuration option and cannot be
	 * changed at run समय or by strapping. Thereक्रमe the attached PHYs
	 * should be programmed to only advertise settings which are supported
	 * by the hardware.
	 */
	अगर (hellcreek->pdata->is_100_mbits)
		phylink_set(mask, 100baseT_Full);
	अन्यथा
		phylink_set(mask, 1000baseT_Full);

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल पूर्णांक
hellcreek_port_prechangeupper(काष्ठा dsa_चयन *ds, पूर्णांक port,
			      काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	bool used = true;
	पूर्णांक ret = -EBUSY;
	u16 vid;
	पूर्णांक i;

	dev_dbg(hellcreek->dev, "Pre change upper for port %d\n", port);

	/*
	 * Deny VLAN devices on top of lan ports with the same VLAN ids, because
	 * it अवरोधs the port separation due to the निजी VLANs. Example:
	 *
	 * lan0.100 *and* lan1.100 cannot be used in parallel. However, lan0.99
	 * and lan1.100 works.
	 */

	अगर (!is_vlan_dev(info->upper_dev))
		वापस 0;

	vid = vlan_dev_vlan_id(info->upper_dev);

	/* For all ports, check biपंचांगaps */
	mutex_lock(&hellcreek->vlan_lock);
	क्रम (i = 0; i < hellcreek->pdata->num_ports; ++i) अणु
		अगर (!dsa_is_user_port(ds, i))
			जारी;

		अगर (port == i)
			जारी;

		used = used && test_bit(vid, hellcreek->ports[i].vlan_dev_biपंचांगap);
	पूर्ण

	अगर (used)
		जाओ out;

	/* Update biपंचांगap */
	set_bit(vid, hellcreek->ports[port].vlan_dev_biपंचांगap);

	ret = 0;

out:
	mutex_unlock(&hellcreek->vlan_lock);

	वापस ret;
पूर्ण

अटल व्योम hellcreek_setup_gcl(काष्ठा hellcreek *hellcreek, पूर्णांक port,
				स्थिर काष्ठा tc_taprio_qopt_offload *schedule)
अणु
	स्थिर काष्ठा tc_taprio_sched_entry *cur, *initial, *next;
	माप_प्रकार i;

	cur = initial = &schedule->entries[0];
	next = cur + 1;

	क्रम (i = 1; i <= schedule->num_entries; ++i) अणु
		u16 data;
		u8 gates;

		cur++;
		next++;

		अगर (i == schedule->num_entries)
			gates = initial->gate_mask ^
				cur->gate_mask;
		अन्यथा
			gates = next->gate_mask ^
				cur->gate_mask;

		data = gates;

		अगर (i == schedule->num_entries)
			data |= TR_GCLDAT_GCLWRLAST;

		/* Gates states */
		hellcreek_ग_लिखो(hellcreek, data, TR_GCLDAT);

		/* Time पूर्णांकerval */
		hellcreek_ग_लिखो(hellcreek,
				cur->पूर्णांकerval & 0x0000ffff,
				TR_GCLTIL);
		hellcreek_ग_लिखो(hellcreek,
				(cur->पूर्णांकerval & 0xffff0000) >> 16,
				TR_GCLTIH);

		/* Commit entry */
		data = ((i - 1) << TR_GCLCMD_GCLWRADR_SHIFT) |
			(initial->gate_mask <<
			 TR_GCLCMD_INIT_GATE_STATES_SHIFT);
		hellcreek_ग_लिखो(hellcreek, data, TR_GCLCMD);
	पूर्ण
पूर्ण

अटल व्योम hellcreek_set_cycle_समय(काष्ठा hellcreek *hellcreek,
				     स्थिर काष्ठा tc_taprio_qopt_offload *schedule)
अणु
	u32 cycle_समय = schedule->cycle_समय;

	hellcreek_ग_लिखो(hellcreek, cycle_समय & 0x0000ffff, TR_CTWRL);
	hellcreek_ग_लिखो(hellcreek, (cycle_समय & 0xffff0000) >> 16, TR_CTWRH);
पूर्ण

अटल व्योम hellcreek_चयन_schedule(काष्ठा hellcreek *hellcreek,
				      kसमय_प्रकार start_समय)
अणु
	काष्ठा बारpec64 ts = kसमय_प्रकारo_बारpec64(start_समय);

	/* Start schedule at this poपूर्णांक of समय */
	hellcreek_ग_लिखो(hellcreek, ts.tv_nsec & 0x0000ffff, TR_ESTWRL);
	hellcreek_ग_लिखो(hellcreek, (ts.tv_nsec & 0xffff0000) >> 16, TR_ESTWRH);

	/* Arm समयr, set seconds and चयन schedule */
	hellcreek_ग_लिखो(hellcreek, TR_ESTCMD_ESTARM | TR_ESTCMD_ESTSWCFG |
			((ts.tv_sec & TR_ESTCMD_ESTSEC_MASK) <<
			 TR_ESTCMD_ESTSEC_SHIFT), TR_ESTCMD);
पूर्ण

अटल bool hellcreek_schedule_startable(काष्ठा hellcreek *hellcreek, पूर्णांक port)
अणु
	काष्ठा hellcreek_port *hellcreek_port = &hellcreek->ports[port];
	s64 base_समय_ns, current_ns;

	/* The चयन allows a schedule to be started only eight seconds within
	 * the future. Thereक्रमe, check the current PTP समय अगर the schedule is
	 * startable or not.
	 */

	/* Use the "cached" समय. That should be alright, as it's updated quite
	 * frequently in the PTP code.
	 */
	mutex_lock(&hellcreek->ptp_lock);
	current_ns = hellcreek->seconds * NSEC_PER_SEC + hellcreek->last_ts;
	mutex_unlock(&hellcreek->ptp_lock);

	/* Calculate dअगरference to admin base समय */
	base_समय_ns = kसमय_प्रकारo_ns(hellcreek_port->current_schedule->base_समय);

	वापस base_समय_ns - current_ns < (s64)8 * NSEC_PER_SEC;
पूर्ण

अटल व्योम hellcreek_start_schedule(काष्ठा hellcreek *hellcreek, पूर्णांक port)
अणु
	काष्ठा hellcreek_port *hellcreek_port = &hellcreek->ports[port];
	kसमय_प्रकार base_समय, current_समय;
	s64 current_ns;
	u32 cycle_समय;

	/* First select port */
	hellcreek_select_tgd(hellcreek, port);

	/* Forward base समय पूर्णांकo the future अगर needed */
	mutex_lock(&hellcreek->ptp_lock);
	current_ns = hellcreek->seconds * NSEC_PER_SEC + hellcreek->last_ts;
	mutex_unlock(&hellcreek->ptp_lock);

	current_समय = ns_to_kसमय(current_ns);
	base_समय    = hellcreek_port->current_schedule->base_समय;
	cycle_समय   = hellcreek_port->current_schedule->cycle_समय;

	अगर (kसमय_compare(current_समय, base_समय) > 0) अणु
		s64 n;

		n = भाग64_s64(kसमय_sub_ns(current_समय, base_समय),
			      cycle_समय);
		base_समय = kसमय_add_ns(base_समय, (n + 1) * cycle_समय);
	पूर्ण

	/* Set admin base समय and चयन schedule */
	hellcreek_चयन_schedule(hellcreek, base_समय);

	taprio_offload_मुक्त(hellcreek_port->current_schedule);
	hellcreek_port->current_schedule = शून्य;

	dev_dbg(hellcreek->dev, "Armed EST timer for port %d\n",
		hellcreek_port->port);
पूर्ण

अटल व्योम hellcreek_check_schedule(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा hellcreek_port *hellcreek_port;
	काष्ठा hellcreek *hellcreek;
	bool startable;

	hellcreek_port = dw_to_hellcreek_port(dw);
	hellcreek = hellcreek_port->hellcreek;

	mutex_lock(&hellcreek->reg_lock);

	/* Check starting समय */
	startable = hellcreek_schedule_startable(hellcreek,
						 hellcreek_port->port);
	अगर (startable) अणु
		hellcreek_start_schedule(hellcreek, hellcreek_port->port);
		mutex_unlock(&hellcreek->reg_lock);
		वापस;
	पूर्ण

	mutex_unlock(&hellcreek->reg_lock);

	/* Reschedule */
	schedule_delayed_work(&hellcreek_port->schedule_work,
			      HELLCREEK_SCHEDULE_PERIOD);
पूर्ण

अटल पूर्णांक hellcreek_port_set_schedule(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       काष्ठा tc_taprio_qopt_offload *taprio)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;
	bool startable;
	u16 ctrl;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "Configure traffic schedule on port %d\n",
		port);

	/* First cancel delayed work */
	cancel_delayed_work_sync(&hellcreek_port->schedule_work);

	mutex_lock(&hellcreek->reg_lock);

	अगर (hellcreek_port->current_schedule) अणु
		taprio_offload_मुक्त(hellcreek_port->current_schedule);
		hellcreek_port->current_schedule = शून्य;
	पूर्ण
	hellcreek_port->current_schedule = taprio_offload_get(taprio);

	/* Then select port */
	hellcreek_select_tgd(hellcreek, port);

	/* Enable gating and keep शेषs */
	ctrl = (0xff << TR_TGDCTRL_ADMINGATESTATES_SHIFT) | TR_TGDCTRL_GATE_EN;
	hellcreek_ग_लिखो(hellcreek, ctrl, TR_TGDCTRL);

	/* Cancel pending schedule */
	hellcreek_ग_लिखो(hellcreek, 0x00, TR_ESTCMD);

	/* Setup a new schedule */
	hellcreek_setup_gcl(hellcreek, port, hellcreek_port->current_schedule);

	/* Configure cycle समय */
	hellcreek_set_cycle_समय(hellcreek, hellcreek_port->current_schedule);

	/* Check starting समय */
	startable = hellcreek_schedule_startable(hellcreek, port);
	अगर (startable) अणु
		hellcreek_start_schedule(hellcreek, port);
		mutex_unlock(&hellcreek->reg_lock);
		वापस 0;
	पूर्ण

	mutex_unlock(&hellcreek->reg_lock);

	/* Schedule periodic schedule check */
	schedule_delayed_work(&hellcreek_port->schedule_work,
			      HELLCREEK_SCHEDULE_PERIOD);

	वापस 0;
पूर्ण

अटल पूर्णांक hellcreek_port_del_schedule(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा hellcreek *hellcreek = ds->priv;
	काष्ठा hellcreek_port *hellcreek_port;

	hellcreek_port = &hellcreek->ports[port];

	dev_dbg(hellcreek->dev, "Remove traffic schedule on port %d\n", port);

	/* First cancel delayed work */
	cancel_delayed_work_sync(&hellcreek_port->schedule_work);

	mutex_lock(&hellcreek->reg_lock);

	अगर (hellcreek_port->current_schedule) अणु
		taprio_offload_मुक्त(hellcreek_port->current_schedule);
		hellcreek_port->current_schedule = शून्य;
	पूर्ण

	/* Then select port */
	hellcreek_select_tgd(hellcreek, port);

	/* Disable gating and वापस to regular चयनing flow */
	hellcreek_ग_लिखो(hellcreek, 0xff << TR_TGDCTRL_ADMINGATESTATES_SHIFT,
			TR_TGDCTRL);

	mutex_unlock(&hellcreek->reg_lock);

	वापस 0;
पूर्ण

अटल bool hellcreek_validate_schedule(काष्ठा hellcreek *hellcreek,
					काष्ठा tc_taprio_qopt_offload *schedule)
अणु
	माप_प्रकार i;

	/* Does this hellcreek version support Qbv in hardware? */
	अगर (!hellcreek->pdata->qbv_support)
		वापस false;

	/* cycle समय can only be 32bit */
	अगर (schedule->cycle_समय > (u32)-1)
		वापस false;

	/* cycle समय extension is not supported */
	अगर (schedule->cycle_समय_extension)
		वापस false;

	/* Only set command is supported */
	क्रम (i = 0; i < schedule->num_entries; ++i)
		अगर (schedule->entries[i].command != TC_TAPRIO_CMD_SET_GATES)
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक hellcreek_port_setup_tc(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   क्रमागत tc_setup_type type, व्योम *type_data)
अणु
	काष्ठा tc_taprio_qopt_offload *taprio = type_data;
	काष्ठा hellcreek *hellcreek = ds->priv;

	अगर (type != TC_SETUP_QDISC_TAPRIO)
		वापस -EOPNOTSUPP;

	अगर (!hellcreek_validate_schedule(hellcreek, taprio))
		वापस -EOPNOTSUPP;

	अगर (taprio->enable)
		वापस hellcreek_port_set_schedule(ds, port, taprio);

	वापस hellcreek_port_del_schedule(ds, port);
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops hellcreek_ds_ops = अणु
	.devlink_info_get      = hellcreek_devlink_info_get,
	.get_ethtool_stats     = hellcreek_get_ethtool_stats,
	.get_sset_count	       = hellcreek_get_sset_count,
	.get_strings	       = hellcreek_get_strings,
	.get_tag_protocol      = hellcreek_get_tag_protocol,
	.get_ts_info	       = hellcreek_get_ts_info,
	.phylink_validate      = hellcreek_phylink_validate,
	.port_bridge_flags     = hellcreek_bridge_flags,
	.port_bridge_join      = hellcreek_port_bridge_join,
	.port_bridge_leave     = hellcreek_port_bridge_leave,
	.port_disable	       = hellcreek_port_disable,
	.port_enable	       = hellcreek_port_enable,
	.port_fdb_add	       = hellcreek_fdb_add,
	.port_fdb_del	       = hellcreek_fdb_del,
	.port_fdb_dump	       = hellcreek_fdb_dump,
	.port_hwtstamp_set     = hellcreek_port_hwtstamp_set,
	.port_hwtstamp_get     = hellcreek_port_hwtstamp_get,
	.port_pre_bridge_flags = hellcreek_pre_bridge_flags,
	.port_prechangeupper   = hellcreek_port_prechangeupper,
	.port_rxtstamp	       = hellcreek_port_rxtstamp,
	.port_setup_tc	       = hellcreek_port_setup_tc,
	.port_stp_state_set    = hellcreek_port_stp_state_set,
	.port_txtstamp	       = hellcreek_port_txtstamp,
	.port_vlan_add	       = hellcreek_vlan_add,
	.port_vlan_del	       = hellcreek_vlan_del,
	.port_vlan_filtering   = hellcreek_vlan_filtering,
	.setup		       = hellcreek_setup,
	.tearकरोwn	       = hellcreek_tearकरोwn,
पूर्ण;

अटल पूर्णांक hellcreek_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hellcreek *hellcreek;
	काष्ठा resource *res;
	पूर्णांक ret, i;

	hellcreek = devm_kzalloc(dev, माप(*hellcreek), GFP_KERNEL);
	अगर (!hellcreek)
		वापस -ENOMEM;

	hellcreek->vidmbrcfg = devm_kसुस्मृति(dev, VLAN_N_VID,
					    माप(*hellcreek->vidmbrcfg),
					    GFP_KERNEL);
	अगर (!hellcreek->vidmbrcfg)
		वापस -ENOMEM;

	hellcreek->pdata = of_device_get_match_data(dev);

	hellcreek->ports = devm_kसुस्मृति(dev, hellcreek->pdata->num_ports,
					माप(*hellcreek->ports),
					GFP_KERNEL);
	अगर (!hellcreek->ports)
		वापस -ENOMEM;

	क्रम (i = 0; i < hellcreek->pdata->num_ports; ++i) अणु
		काष्ठा hellcreek_port *port = &hellcreek->ports[i];

		port->counter_values =
			devm_kसुस्मृति(dev,
				     ARRAY_SIZE(hellcreek_counter),
				     माप(*port->counter_values),
				     GFP_KERNEL);
		अगर (!port->counter_values)
			वापस -ENOMEM;

		port->vlan_dev_biपंचांगap =
			devm_kसुस्मृति(dev,
				     BITS_TO_LONGS(VLAN_N_VID),
				     माप(अचिन्हित दीर्घ),
				     GFP_KERNEL);
		अगर (!port->vlan_dev_biपंचांगap)
			वापस -ENOMEM;

		port->hellcreek	= hellcreek;
		port->port	= i;

		INIT_DELAYED_WORK(&port->schedule_work,
				  hellcreek_check_schedule);
	पूर्ण

	mutex_init(&hellcreek->reg_lock);
	mutex_init(&hellcreek->vlan_lock);
	mutex_init(&hellcreek->ptp_lock);

	hellcreek->dev = dev;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "tsn");
	अगर (!res) अणु
		dev_err(dev, "No memory region provided!\n");
		वापस -ENODEV;
	पूर्ण

	hellcreek->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hellcreek->base))
		वापस PTR_ERR(hellcreek->base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "ptp");
	अगर (!res) अणु
		dev_err(dev, "No PTP memory region provided!\n");
		वापस -ENODEV;
	पूर्ण

	hellcreek->ptp_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(hellcreek->ptp_base))
		वापस PTR_ERR(hellcreek->ptp_base);

	ret = hellcreek_detect(hellcreek);
	अगर (ret) अणु
		dev_err(dev, "No (known) chip found!\n");
		वापस ret;
	पूर्ण

	ret = hellcreek_रुको_until_पढ़ोy(hellcreek);
	अगर (ret) अणु
		dev_err(dev, "Switch didn't become ready!\n");
		वापस ret;
	पूर्ण

	hellcreek_feature_detect(hellcreek);

	hellcreek->ds = devm_kzalloc(dev, माप(*hellcreek->ds), GFP_KERNEL);
	अगर (!hellcreek->ds)
		वापस -ENOMEM;

	hellcreek->ds->dev	     = dev;
	hellcreek->ds->priv	     = hellcreek;
	hellcreek->ds->ops	     = &hellcreek_ds_ops;
	hellcreek->ds->num_ports     = hellcreek->pdata->num_ports;
	hellcreek->ds->num_tx_queues = HELLCREEK_NUM_EGRESS_QUEUES;

	ret = dsa_रेजिस्टर_चयन(hellcreek->ds);
	अगर (ret) अणु
		dev_err_probe(dev, ret, "Unable to register switch\n");
		वापस ret;
	पूर्ण

	ret = hellcreek_ptp_setup(hellcreek);
	अगर (ret) अणु
		dev_err(dev, "Failed to setup PTP!\n");
		जाओ err_ptp_setup;
	पूर्ण

	ret = hellcreek_hwtstamp_setup(hellcreek);
	अगर (ret) अणु
		dev_err(dev, "Failed to setup hardware timestamping!\n");
		जाओ err_tstamp_setup;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hellcreek);

	वापस 0;

err_tstamp_setup:
	hellcreek_ptp_मुक्त(hellcreek);
err_ptp_setup:
	dsa_unरेजिस्टर_चयन(hellcreek->ds);

	वापस ret;
पूर्ण

अटल पूर्णांक hellcreek_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hellcreek *hellcreek = platक्रमm_get_drvdata(pdev);

	hellcreek_hwtstamp_मुक्त(hellcreek);
	hellcreek_ptp_मुक्त(hellcreek);
	dsa_unरेजिस्टर_चयन(hellcreek->ds);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hellcreek_platक्रमm_data de1soc_r1_pdata = अणु
	.name		 = "r4c30",
	.num_ports	 = 4,
	.is_100_mbits	 = 1,
	.qbv_support	 = 1,
	.qbv_on_cpu_port = 1,
	.qbu_support	 = 0,
	.module_id	 = 0x4c30,
पूर्ण;

अटल स्थिर काष्ठा of_device_id hellcreek_of_match[] = अणु
	अणु
		.compatible = "hirschmann,hellcreek-de1soc-r1",
		.data	    = &de1soc_r1_pdata,
	पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hellcreek_of_match);

अटल काष्ठा platक्रमm_driver hellcreek_driver = अणु
	.probe	= hellcreek_probe,
	.हटाओ = hellcreek_हटाओ,
	.driver = अणु
		.name = "hellcreek",
		.of_match_table = hellcreek_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hellcreek_driver);

MODULE_AUTHOR("Kurt Kanzenbach <kurt@linutronix.de>");
MODULE_DESCRIPTION("Hirschmann Hellcreek driver");
MODULE_LICENSE("Dual MIT/GPL");
