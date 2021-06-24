<शैली गुरु>
/*
 * B53 चयन driver मुख्य logic
 *
 * Copyright (C) 2011-2013 Jonas Gorski <jogo@खोलोwrt.org>
 * Copyright (C) 2016 Florian Fainelli <f.fainelli@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/b53.h>
#समावेश <linux/phy.h>
#समावेश <linux/phylink.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <net/dsa.h>

#समावेश "b53_regs.h"
#समावेश "b53_priv.h"

काष्ठा b53_mib_desc अणु
	u8 size;
	u8 offset;
	स्थिर अक्षर *name;
पूर्ण;

/* BCM5365 MIB counters */
अटल स्थिर काष्ठा b53_mib_desc b53_mibs_65[] = अणु
	अणु 8, 0x00, "TxOctets" पूर्ण,
	अणु 4, 0x08, "TxDropPkts" पूर्ण,
	अणु 4, 0x10, "TxBroadcastPkts" पूर्ण,
	अणु 4, 0x14, "TxMulticastPkts" पूर्ण,
	अणु 4, 0x18, "TxUnicastPkts" पूर्ण,
	अणु 4, 0x1c, "TxCollisions" पूर्ण,
	अणु 4, 0x20, "TxSingleCollision" पूर्ण,
	अणु 4, 0x24, "TxMultipleCollision" पूर्ण,
	अणु 4, 0x28, "TxDeferredTransmit" पूर्ण,
	अणु 4, 0x2c, "TxLateCollision" पूर्ण,
	अणु 4, 0x30, "TxExcessiveCollision" पूर्ण,
	अणु 4, 0x38, "TxPausePkts" पूर्ण,
	अणु 8, 0x44, "RxOctets" पूर्ण,
	अणु 4, 0x4c, "RxUndersizePkts" पूर्ण,
	अणु 4, 0x50, "RxPausePkts" पूर्ण,
	अणु 4, 0x54, "Pkts64Octets" पूर्ण,
	अणु 4, 0x58, "Pkts65to127Octets" पूर्ण,
	अणु 4, 0x5c, "Pkts128to255Octets" पूर्ण,
	अणु 4, 0x60, "Pkts256to511Octets" पूर्ण,
	अणु 4, 0x64, "Pkts512to1023Octets" पूर्ण,
	अणु 4, 0x68, "Pkts1024to1522Octets" पूर्ण,
	अणु 4, 0x6c, "RxOversizePkts" पूर्ण,
	अणु 4, 0x70, "RxJabbers" पूर्ण,
	अणु 4, 0x74, "RxAlignmentErrors" पूर्ण,
	अणु 4, 0x78, "RxFCSErrors" पूर्ण,
	अणु 8, 0x7c, "RxGoodOctets" पूर्ण,
	अणु 4, 0x84, "RxDropPkts" पूर्ण,
	अणु 4, 0x88, "RxUnicastPkts" पूर्ण,
	अणु 4, 0x8c, "RxMulticastPkts" पूर्ण,
	अणु 4, 0x90, "RxBroadcastPkts" पूर्ण,
	अणु 4, 0x94, "RxSAChanges" पूर्ण,
	अणु 4, 0x98, "RxFragments" पूर्ण,
पूर्ण;

#घोषणा B53_MIBS_65_SIZE	ARRAY_SIZE(b53_mibs_65)

/* BCM63xx MIB counters */
अटल स्थिर काष्ठा b53_mib_desc b53_mibs_63xx[] = अणु
	अणु 8, 0x00, "TxOctets" पूर्ण,
	अणु 4, 0x08, "TxDropPkts" पूर्ण,
	अणु 4, 0x0c, "TxQoSPkts" पूर्ण,
	अणु 4, 0x10, "TxBroadcastPkts" पूर्ण,
	अणु 4, 0x14, "TxMulticastPkts" पूर्ण,
	अणु 4, 0x18, "TxUnicastPkts" पूर्ण,
	अणु 4, 0x1c, "TxCollisions" पूर्ण,
	अणु 4, 0x20, "TxSingleCollision" पूर्ण,
	अणु 4, 0x24, "TxMultipleCollision" पूर्ण,
	अणु 4, 0x28, "TxDeferredTransmit" पूर्ण,
	अणु 4, 0x2c, "TxLateCollision" पूर्ण,
	अणु 4, 0x30, "TxExcessiveCollision" पूर्ण,
	अणु 4, 0x38, "TxPausePkts" पूर्ण,
	अणु 8, 0x3c, "TxQoSOctets" पूर्ण,
	अणु 8, 0x44, "RxOctets" पूर्ण,
	अणु 4, 0x4c, "RxUndersizePkts" पूर्ण,
	अणु 4, 0x50, "RxPausePkts" पूर्ण,
	अणु 4, 0x54, "Pkts64Octets" पूर्ण,
	अणु 4, 0x58, "Pkts65to127Octets" पूर्ण,
	अणु 4, 0x5c, "Pkts128to255Octets" पूर्ण,
	अणु 4, 0x60, "Pkts256to511Octets" पूर्ण,
	अणु 4, 0x64, "Pkts512to1023Octets" पूर्ण,
	अणु 4, 0x68, "Pkts1024to1522Octets" पूर्ण,
	अणु 4, 0x6c, "RxOversizePkts" पूर्ण,
	अणु 4, 0x70, "RxJabbers" पूर्ण,
	अणु 4, 0x74, "RxAlignmentErrors" पूर्ण,
	अणु 4, 0x78, "RxFCSErrors" पूर्ण,
	अणु 8, 0x7c, "RxGoodOctets" पूर्ण,
	अणु 4, 0x84, "RxDropPkts" पूर्ण,
	अणु 4, 0x88, "RxUnicastPkts" पूर्ण,
	अणु 4, 0x8c, "RxMulticastPkts" पूर्ण,
	अणु 4, 0x90, "RxBroadcastPkts" पूर्ण,
	अणु 4, 0x94, "RxSAChanges" पूर्ण,
	अणु 4, 0x98, "RxFragments" पूर्ण,
	अणु 4, 0xa0, "RxSymbolErrors" पूर्ण,
	अणु 4, 0xa4, "RxQoSPkts" पूर्ण,
	अणु 8, 0xa8, "RxQoSOctets" पूर्ण,
	अणु 4, 0xb0, "Pkts1523to2047Octets" पूर्ण,
	अणु 4, 0xb4, "Pkts2048to4095Octets" पूर्ण,
	अणु 4, 0xb8, "Pkts4096to8191Octets" पूर्ण,
	अणु 4, 0xbc, "Pkts8192to9728Octets" पूर्ण,
	अणु 4, 0xc0, "RxDiscarded" पूर्ण,
पूर्ण;

#घोषणा B53_MIBS_63XX_SIZE	ARRAY_SIZE(b53_mibs_63xx)

/* MIB counters */
अटल स्थिर काष्ठा b53_mib_desc b53_mibs[] = अणु
	अणु 8, 0x00, "TxOctets" पूर्ण,
	अणु 4, 0x08, "TxDropPkts" पूर्ण,
	अणु 4, 0x10, "TxBroadcastPkts" पूर्ण,
	अणु 4, 0x14, "TxMulticastPkts" पूर्ण,
	अणु 4, 0x18, "TxUnicastPkts" पूर्ण,
	अणु 4, 0x1c, "TxCollisions" पूर्ण,
	अणु 4, 0x20, "TxSingleCollision" पूर्ण,
	अणु 4, 0x24, "TxMultipleCollision" पूर्ण,
	अणु 4, 0x28, "TxDeferredTransmit" पूर्ण,
	अणु 4, 0x2c, "TxLateCollision" पूर्ण,
	अणु 4, 0x30, "TxExcessiveCollision" पूर्ण,
	अणु 4, 0x38, "TxPausePkts" पूर्ण,
	अणु 8, 0x50, "RxOctets" पूर्ण,
	अणु 4, 0x58, "RxUndersizePkts" पूर्ण,
	अणु 4, 0x5c, "RxPausePkts" पूर्ण,
	अणु 4, 0x60, "Pkts64Octets" पूर्ण,
	अणु 4, 0x64, "Pkts65to127Octets" पूर्ण,
	अणु 4, 0x68, "Pkts128to255Octets" पूर्ण,
	अणु 4, 0x6c, "Pkts256to511Octets" पूर्ण,
	अणु 4, 0x70, "Pkts512to1023Octets" पूर्ण,
	अणु 4, 0x74, "Pkts1024to1522Octets" पूर्ण,
	अणु 4, 0x78, "RxOversizePkts" पूर्ण,
	अणु 4, 0x7c, "RxJabbers" पूर्ण,
	अणु 4, 0x80, "RxAlignmentErrors" पूर्ण,
	अणु 4, 0x84, "RxFCSErrors" पूर्ण,
	अणु 8, 0x88, "RxGoodOctets" पूर्ण,
	अणु 4, 0x90, "RxDropPkts" पूर्ण,
	अणु 4, 0x94, "RxUnicastPkts" पूर्ण,
	अणु 4, 0x98, "RxMulticastPkts" पूर्ण,
	अणु 4, 0x9c, "RxBroadcastPkts" पूर्ण,
	अणु 4, 0xa0, "RxSAChanges" पूर्ण,
	अणु 4, 0xa4, "RxFragments" पूर्ण,
	अणु 4, 0xa8, "RxJumboPkts" पूर्ण,
	अणु 4, 0xac, "RxSymbolErrors" पूर्ण,
	अणु 4, 0xc0, "RxDiscarded" पूर्ण,
पूर्ण;

#घोषणा B53_MIBS_SIZE	ARRAY_SIZE(b53_mibs)

अटल स्थिर काष्ठा b53_mib_desc b53_mibs_58xx[] = अणु
	अणु 8, 0x00, "TxOctets" पूर्ण,
	अणु 4, 0x08, "TxDropPkts" पूर्ण,
	अणु 4, 0x0c, "TxQPKTQ0" पूर्ण,
	अणु 4, 0x10, "TxBroadcastPkts" पूर्ण,
	अणु 4, 0x14, "TxMulticastPkts" पूर्ण,
	अणु 4, 0x18, "TxUnicastPKts" पूर्ण,
	अणु 4, 0x1c, "TxCollisions" पूर्ण,
	अणु 4, 0x20, "TxSingleCollision" पूर्ण,
	अणु 4, 0x24, "TxMultipleCollision" पूर्ण,
	अणु 4, 0x28, "TxDeferredCollision" पूर्ण,
	अणु 4, 0x2c, "TxLateCollision" पूर्ण,
	अणु 4, 0x30, "TxExcessiveCollision" पूर्ण,
	अणु 4, 0x34, "TxFrameInDisc" पूर्ण,
	अणु 4, 0x38, "TxPausePkts" पूर्ण,
	अणु 4, 0x3c, "TxQPKTQ1" पूर्ण,
	अणु 4, 0x40, "TxQPKTQ2" पूर्ण,
	अणु 4, 0x44, "TxQPKTQ3" पूर्ण,
	अणु 4, 0x48, "TxQPKTQ4" पूर्ण,
	अणु 4, 0x4c, "TxQPKTQ5" पूर्ण,
	अणु 8, 0x50, "RxOctets" पूर्ण,
	अणु 4, 0x58, "RxUndersizePkts" पूर्ण,
	अणु 4, 0x5c, "RxPausePkts" पूर्ण,
	अणु 4, 0x60, "RxPkts64Octets" पूर्ण,
	अणु 4, 0x64, "RxPkts65to127Octets" पूर्ण,
	अणु 4, 0x68, "RxPkts128to255Octets" पूर्ण,
	अणु 4, 0x6c, "RxPkts256to511Octets" पूर्ण,
	अणु 4, 0x70, "RxPkts512to1023Octets" पूर्ण,
	अणु 4, 0x74, "RxPkts1024toMaxPktsOctets" पूर्ण,
	अणु 4, 0x78, "RxOversizePkts" पूर्ण,
	अणु 4, 0x7c, "RxJabbers" पूर्ण,
	अणु 4, 0x80, "RxAlignmentErrors" पूर्ण,
	अणु 4, 0x84, "RxFCSErrors" पूर्ण,
	अणु 8, 0x88, "RxGoodOctets" पूर्ण,
	अणु 4, 0x90, "RxDropPkts" पूर्ण,
	अणु 4, 0x94, "RxUnicastPkts" पूर्ण,
	अणु 4, 0x98, "RxMulticastPkts" पूर्ण,
	अणु 4, 0x9c, "RxBroadcastPkts" पूर्ण,
	अणु 4, 0xa0, "RxSAChanges" पूर्ण,
	अणु 4, 0xa4, "RxFragments" पूर्ण,
	अणु 4, 0xa8, "RxJumboPkt" पूर्ण,
	अणु 4, 0xac, "RxSymblErr" पूर्ण,
	अणु 4, 0xb0, "InRangeErrCount" पूर्ण,
	अणु 4, 0xb4, "OutRangeErrCount" पूर्ण,
	अणु 4, 0xb8, "EEELpiEvent" पूर्ण,
	अणु 4, 0xbc, "EEELpiDuration" पूर्ण,
	अणु 4, 0xc0, "RxDiscard" पूर्ण,
	अणु 4, 0xc8, "TxQPKTQ6" पूर्ण,
	अणु 4, 0xcc, "TxQPKTQ7" पूर्ण,
	अणु 4, 0xd0, "TxPkts64Octets" पूर्ण,
	अणु 4, 0xd4, "TxPkts65to127Octets" पूर्ण,
	अणु 4, 0xd8, "TxPkts128to255Octets" पूर्ण,
	अणु 4, 0xdc, "TxPkts256to511Ocets" पूर्ण,
	अणु 4, 0xe0, "TxPkts512to1023Ocets" पूर्ण,
	अणु 4, 0xe4, "TxPkts1024toMaxPktOcets" पूर्ण,
पूर्ण;

#घोषणा B53_MIBS_58XX_SIZE	ARRAY_SIZE(b53_mibs_58xx)

अटल पूर्णांक b53_करो_vlan_op(काष्ठा b53_device *dev, u8 op)
अणु
	अचिन्हित पूर्णांक i;

	b53_ग_लिखो8(dev, B53_ARLIO_PAGE, dev->vta_regs[0], VTA_START_CMD | op);

	क्रम (i = 0; i < 10; i++) अणु
		u8 vta;

		b53_पढ़ो8(dev, B53_ARLIO_PAGE, dev->vta_regs[0], &vta);
		अगर (!(vta & VTA_START_CMD))
			वापस 0;

		usleep_range(100, 200);
	पूर्ण

	वापस -EIO;
पूर्ण

अटल व्योम b53_set_vlan_entry(काष्ठा b53_device *dev, u16 vid,
			       काष्ठा b53_vlan *vlan)
अणु
	अगर (is5325(dev)) अणु
		u32 entry = 0;

		अगर (vlan->members) अणु
			entry = ((vlan->untag & VA_UNTAG_MASK_25) <<
				 VA_UNTAG_S_25) | vlan->members;
			अगर (dev->core_rev >= 3)
				entry |= VA_VALID_25_R4 | vid << VA_VID_HIGH_S;
			अन्यथा
				entry |= VA_VALID_25;
		पूर्ण

		b53_ग_लिखो32(dev, B53_VLAN_PAGE, B53_VLAN_WRITE_25, entry);
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_25, vid |
			    VTA_RW_STATE_WR | VTA_RW_OP_EN);
	पूर्ण अन्यथा अगर (is5365(dev)) अणु
		u16 entry = 0;

		अगर (vlan->members)
			entry = ((vlan->untag & VA_UNTAG_MASK_65) <<
				 VA_UNTAG_S_65) | vlan->members | VA_VALID_65;

		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_WRITE_65, entry);
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_65, vid |
			    VTA_RW_STATE_WR | VTA_RW_OP_EN);
	पूर्ण अन्यथा अणु
		b53_ग_लिखो16(dev, B53_ARLIO_PAGE, dev->vta_regs[1], vid);
		b53_ग_लिखो32(dev, B53_ARLIO_PAGE, dev->vta_regs[2],
			    (vlan->untag << VTE_UNTAG_S) | vlan->members);

		b53_करो_vlan_op(dev, VTA_CMD_WRITE);
	पूर्ण

	dev_dbg(dev->ds->dev, "VID: %d, members: 0x%04x, untag: 0x%04x\n",
		vid, vlan->members, vlan->untag);
पूर्ण

अटल व्योम b53_get_vlan_entry(काष्ठा b53_device *dev, u16 vid,
			       काष्ठा b53_vlan *vlan)
अणु
	अगर (is5325(dev)) अणु
		u32 entry = 0;

		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_25, vid |
			    VTA_RW_STATE_RD | VTA_RW_OP_EN);
		b53_पढ़ो32(dev, B53_VLAN_PAGE, B53_VLAN_WRITE_25, &entry);

		अगर (dev->core_rev >= 3)
			vlan->valid = !!(entry & VA_VALID_25_R4);
		अन्यथा
			vlan->valid = !!(entry & VA_VALID_25);
		vlan->members = entry & VA_MEMBER_MASK;
		vlan->untag = (entry >> VA_UNTAG_S_25) & VA_UNTAG_MASK_25;

	पूर्ण अन्यथा अगर (is5365(dev)) अणु
		u16 entry = 0;

		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_65, vid |
			    VTA_RW_STATE_WR | VTA_RW_OP_EN);
		b53_पढ़ो16(dev, B53_VLAN_PAGE, B53_VLAN_WRITE_65, &entry);

		vlan->valid = !!(entry & VA_VALID_65);
		vlan->members = entry & VA_MEMBER_MASK;
		vlan->untag = (entry >> VA_UNTAG_S_65) & VA_UNTAG_MASK_65;
	पूर्ण अन्यथा अणु
		u32 entry = 0;

		b53_ग_लिखो16(dev, B53_ARLIO_PAGE, dev->vta_regs[1], vid);
		b53_करो_vlan_op(dev, VTA_CMD_READ);
		b53_पढ़ो32(dev, B53_ARLIO_PAGE, dev->vta_regs[2], &entry);
		vlan->members = entry & VTE_MEMBERS;
		vlan->untag = (entry >> VTE_UNTAG_S) & VTE_MEMBERS;
		vlan->valid = true;
	पूर्ण
पूर्ण

अटल व्योम b53_set_क्रमwarding(काष्ठा b53_device *dev, पूर्णांक enable)
अणु
	u8 mgmt;

	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);

	अगर (enable)
		mgmt |= SM_SW_FWD_EN;
	अन्यथा
		mgmt &= ~SM_SW_FWD_EN;

	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);

	/* Include IMP port in dumb क्रमwarding mode
	 */
	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_CTRL, &mgmt);
	mgmt |= B53_MII_DUMB_FWDG_EN;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SWITCH_CTRL, mgmt);

	/* Look at B53_UC_FWD_EN and B53_MC_FWD_EN to decide whether
	 * frames should be flooded or not.
	 */
	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_IP_MULTICAST_CTRL, &mgmt);
	mgmt |= B53_UC_FWD_EN | B53_MC_FWD_EN | B53_IPMC_FWD_EN;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_IP_MULTICAST_CTRL, mgmt);
पूर्ण

अटल व्योम b53_enable_vlan(काष्ठा b53_device *dev, पूर्णांक port, bool enable,
			    bool enable_filtering)
अणु
	u8 mgmt, vc0, vc1, vc4 = 0, vc5;

	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);
	b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL0, &vc0);
	b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL1, &vc1);

	अगर (is5325(dev) || is5365(dev)) अणु
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_25, &vc4);
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_25, &vc5);
	पूर्ण अन्यथा अगर (is63xx(dev)) अणु
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_63XX, &vc4);
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_63XX, &vc5);
	पूर्ण अन्यथा अणु
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4, &vc4);
		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5, &vc5);
	पूर्ण

	अगर (enable) अणु
		vc0 |= VC0_VLAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID;
		vc1 |= VC1_RX_MCST_UNTAG_EN | VC1_RX_MCST_FWD_EN;
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		अगर (enable_filtering) अणु
			vc4 |= VC4_ING_VID_VIO_DROP << VC4_ING_VID_CHECK_S;
			vc5 |= VC5_DROP_VTABLE_MISS;
		पूर्ण अन्यथा अणु
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
			vc5 &= ~VC5_DROP_VTABLE_MISS;
		पूर्ण

		अगर (is5325(dev))
			vc0 &= ~VC0_RESERVED_1;

		अगर (is5325(dev) || is5365(dev))
			vc1 |= VC1_RX_MCST_TAG_EN;

	पूर्ण अन्यथा अणु
		vc0 &= ~(VC0_VLAN_EN | VC0_VID_CHK_EN | VC0_VID_HASH_VID);
		vc1 &= ~(VC1_RX_MCST_UNTAG_EN | VC1_RX_MCST_FWD_EN);
		vc4 &= ~VC4_ING_VID_CHECK_MASK;
		vc5 &= ~VC5_DROP_VTABLE_MISS;

		अगर (is5325(dev) || is5365(dev))
			vc4 |= VC4_ING_VID_VIO_FWD << VC4_ING_VID_CHECK_S;
		अन्यथा
			vc4 |= VC4_ING_VID_VIO_TO_IMP << VC4_ING_VID_CHECK_S;

		अगर (is5325(dev) || is5365(dev))
			vc1 &= ~VC1_RX_MCST_TAG_EN;
	पूर्ण

	अगर (!is5325(dev) && !is5365(dev))
		vc5 &= ~VC5_VID_FFF_EN;

	b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL0, vc0);
	b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL1, vc1);

	अगर (is5325(dev) || is5365(dev)) अणु
		/* enable the high 8 bit vid check on 5325 */
		अगर (is5325(dev) && enable)
			b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3,
				   VC3_HIGH_8BIT_EN);
		अन्यथा
			b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3, 0);

		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_25, vc4);
		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_25, vc5);
	पूर्ण अन्यथा अगर (is63xx(dev)) अणु
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3_63XX, 0);
		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_63XX, vc4);
		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5_63XX, vc5);
	पूर्ण अन्यथा अणु
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_CTRL3, 0);
		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4, vc4);
		b53_ग_लिखो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL5, vc5);
	पूर्ण

	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);

	dev->vlan_enabled = enable;

	dev_dbg(dev->dev, "Port %d VLAN enabled: %d, filtering: %d\n",
		port, enable, enable_filtering);
पूर्ण

अटल पूर्णांक b53_set_jumbo(काष्ठा b53_device *dev, bool enable, bool allow_10_100)
अणु
	u32 port_mask = 0;
	u16 max_size = JMS_MIN_SIZE;

	अगर (is5325(dev) || is5365(dev))
		वापस -EINVAL;

	अगर (enable) अणु
		port_mask = dev->enabled_ports;
		max_size = JMS_MAX_SIZE;
		अगर (allow_10_100)
			port_mask |= JPM_10_100_JUMBO_EN;
	पूर्ण

	b53_ग_लिखो32(dev, B53_JUMBO_PAGE, dev->jumbo_pm_reg, port_mask);
	वापस b53_ग_लिखो16(dev, B53_JUMBO_PAGE, dev->jumbo_size_reg, max_size);
पूर्ण

अटल पूर्णांक b53_flush_arl(काष्ठा b53_device *dev, u8 mask)
अणु
	अचिन्हित पूर्णांक i;

	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL,
		   FAST_AGE_DONE | FAST_AGE_DYNAMIC | mask);

	क्रम (i = 0; i < 10; i++) अणु
		u8 fast_age_ctrl;

		b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL,
			  &fast_age_ctrl);

		अगर (!(fast_age_ctrl & FAST_AGE_DONE))
			जाओ out;

		msleep(1);
	पूर्ण

	वापस -ETIMEDOUT;
out:
	/* Only age dynamic entries (शेष behavior) */
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL, FAST_AGE_DYNAMIC);
	वापस 0;
पूर्ण

अटल पूर्णांक b53_fast_age_port(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_FAST_AGE_PORT_CTRL, port);

	वापस b53_flush_arl(dev, FAST_AGE_PORT);
पूर्ण

अटल पूर्णांक b53_fast_age_vlan(काष्ठा b53_device *dev, u16 vid)
अणु
	b53_ग_लिखो16(dev, B53_CTRL_PAGE, B53_FAST_AGE_VID_CTRL, vid);

	वापस b53_flush_arl(dev, FAST_AGE_VLAN);
पूर्ण

व्योम b53_imp_vlan_setup(काष्ठा dsa_चयन *ds, पूर्णांक cpu_port)
अणु
	काष्ठा b53_device *dev = ds->priv;
	अचिन्हित पूर्णांक i;
	u16 pvlan;

	/* Enable the IMP port to be in the same VLAN as the other ports
	 * on a per-port basis such that we only have Port i and IMP in
	 * the same VLAN.
	 */
	b53_क्रम_each_port(dev, i) अणु
		b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), &pvlan);
		pvlan |= BIT(cpu_port);
		b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), pvlan);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(b53_imp_vlan_setup);

अटल व्योम b53_port_set_ucast_flood(काष्ठा b53_device *dev, पूर्णांक port,
				     bool unicast)
अणु
	u16 uc;

	b53_पढ़ो16(dev, B53_CTRL_PAGE, B53_UC_FLOOD_MASK, &uc);
	अगर (unicast)
		uc |= BIT(port);
	अन्यथा
		uc &= ~BIT(port);
	b53_ग_लिखो16(dev, B53_CTRL_PAGE, B53_UC_FLOOD_MASK, uc);
पूर्ण

अटल व्योम b53_port_set_mcast_flood(काष्ठा b53_device *dev, पूर्णांक port,
				     bool multicast)
अणु
	u16 mc;

	b53_पढ़ो16(dev, B53_CTRL_PAGE, B53_MC_FLOOD_MASK, &mc);
	अगर (multicast)
		mc |= BIT(port);
	अन्यथा
		mc &= ~BIT(port);
	b53_ग_लिखो16(dev, B53_CTRL_PAGE, B53_MC_FLOOD_MASK, mc);

	b53_पढ़ो16(dev, B53_CTRL_PAGE, B53_IPMC_FLOOD_MASK, &mc);
	अगर (multicast)
		mc |= BIT(port);
	अन्यथा
		mc &= ~BIT(port);
	b53_ग_लिखो16(dev, B53_CTRL_PAGE, B53_IPMC_FLOOD_MASK, mc);
पूर्ण

अटल व्योम b53_port_set_learning(काष्ठा b53_device *dev, पूर्णांक port,
				  bool learning)
अणु
	u16 reg;

	b53_पढ़ो16(dev, B53_CTRL_PAGE, B53_DIS_LEARNING, &reg);
	अगर (learning)
		reg &= ~BIT(port);
	अन्यथा
		reg |= BIT(port);
	b53_ग_लिखो16(dev, B53_CTRL_PAGE, B53_DIS_LEARNING, reg);
पूर्ण

पूर्णांक b53_enable_port(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy)
अणु
	काष्ठा b53_device *dev = ds->priv;
	अचिन्हित पूर्णांक cpu_port;
	पूर्णांक ret = 0;
	u16 pvlan;

	अगर (!dsa_is_user_port(ds, port))
		वापस 0;

	cpu_port = dsa_to_port(ds, port)->cpu_dp->index;

	b53_port_set_ucast_flood(dev, port, true);
	b53_port_set_mcast_flood(dev, port, true);
	b53_port_set_learning(dev, port, false);

	अगर (dev->ops->irq_enable)
		ret = dev->ops->irq_enable(dev, port);
	अगर (ret)
		वापस ret;

	/* Clear the Rx and Tx disable bits and set to no spanning tree */
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), 0);

	/* Set this port, and only this one to be in the शेष VLAN,
	 * अगर member of a bridge, restore its membership prior to
	 * bringing करोwn this port.
	 */
	b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), &pvlan);
	pvlan &= ~0x1ff;
	pvlan |= BIT(port);
	pvlan |= dev->ports[port].vlan_ctl_mask;
	b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), pvlan);

	b53_imp_vlan_setup(ds, cpu_port);

	/* If EEE was enabled, restore it */
	अगर (dev->ports[port].eee.eee_enabled)
		b53_eee_enable_set(ds, port, true);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_enable_port);

व्योम b53_disable_port(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा b53_device *dev = ds->priv;
	u8 reg;

	/* Disable Tx/Rx क्रम the port */
	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), &reg);
	reg |= PORT_CTRL_RX_DISABLE | PORT_CTRL_TX_DISABLE;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), reg);

	अगर (dev->ops->irq_disable)
		dev->ops->irq_disable(dev, port);
पूर्ण
EXPORT_SYMBOL(b53_disable_port);

व्योम b53_brcm_hdr_setup(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool tag_en = !(dev->tag_protocol == DSA_TAG_PROTO_NONE);
	u8 hdr_ctl, val;
	u16 reg;

	/* Resolve which bit controls the Broadcom tag */
	चयन (port) अणु
	हाल 8:
		val = BRCM_HDR_P8_EN;
		अवरोध;
	हाल 7:
		val = BRCM_HDR_P7_EN;
		अवरोध;
	हाल 5:
		val = BRCM_HDR_P5_EN;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	/* Enable management mode अगर tagging is requested */
	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &hdr_ctl);
	अगर (tag_en)
		hdr_ctl |= SM_SW_FWD_MODE;
	अन्यथा
		hdr_ctl &= ~SM_SW_FWD_MODE;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, hdr_ctl);

	/* Configure the appropriate IMP port */
	b53_पढ़ो8(dev, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, &hdr_ctl);
	अगर (port == 8)
		hdr_ctl |= GC_FRM_MGMT_PORT_MII;
	अन्यथा अगर (port == 5)
		hdr_ctl |= GC_FRM_MGMT_PORT_M;
	b53_ग_लिखो8(dev, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, hdr_ctl);

	/* Enable Broadcom tags क्रम IMP port */
	b53_पढ़ो8(dev, B53_MGMT_PAGE, B53_BRCM_HDR, &hdr_ctl);
	अगर (tag_en)
		hdr_ctl |= val;
	अन्यथा
		hdr_ctl &= ~val;
	b53_ग_लिखो8(dev, B53_MGMT_PAGE, B53_BRCM_HDR, hdr_ctl);

	/* Registers below are only accessible on newer devices */
	अगर (!is58xx(dev))
		वापस;

	/* Enable reception Broadcom tag क्रम CPU TX (चयन RX) to
	 * allow us to tag outgoing frames
	 */
	b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_BRCM_HDR_RX_DIS, &reg);
	अगर (tag_en)
		reg &= ~BIT(port);
	अन्यथा
		reg |= BIT(port);
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, B53_BRCM_HDR_RX_DIS, reg);

	/* Enable transmission of Broadcom tags from the चयन (CPU RX) to
	 * allow delivering frames to the per-port net_devices
	 */
	b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_BRCM_HDR_TX_DIS, &reg);
	अगर (tag_en)
		reg &= ~BIT(port);
	अन्यथा
		reg |= BIT(port);
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, B53_BRCM_HDR_TX_DIS, reg);
पूर्ण
EXPORT_SYMBOL(b53_brcm_hdr_setup);

अटल व्योम b53_enable_cpu_port(काष्ठा b53_device *dev, पूर्णांक port)
अणु
	u8 port_ctrl;

	/* BCM5325 CPU port is at 8 */
	अगर ((is5325(dev) || is5365(dev)) && port == B53_CPU_PORT_25)
		port = B53_CPU_PORT;

	port_ctrl = PORT_CTRL_RX_BCST_EN |
		    PORT_CTRL_RX_MCST_EN |
		    PORT_CTRL_RX_UCST_EN;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), port_ctrl);

	b53_brcm_hdr_setup(dev->ds, port);

	b53_port_set_ucast_flood(dev, port, true);
	b53_port_set_mcast_flood(dev, port, true);
	b53_port_set_learning(dev, port, false);
पूर्ण

अटल व्योम b53_enable_mib(काष्ठा b53_device *dev)
अणु
	u8 gc;

	b53_पढ़ो8(dev, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, &gc);
	gc &= ~(GC_RESET_MIB | GC_MIB_AC_EN);
	b53_ग_लिखो8(dev, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, gc);
पूर्ण

अटल u16 b53_शेष_pvid(काष्ठा b53_device *dev)
अणु
	अगर (is5325(dev) || is5365(dev))
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक b53_configure_vlan(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा b53_vlan vl = अणु 0 पूर्ण;
	काष्ठा b53_vlan *v;
	पूर्णांक i, def_vid;
	u16 vid;

	def_vid = b53_शेष_pvid(dev);

	/* clear all vlan entries */
	अगर (is5325(dev) || is5365(dev)) अणु
		क्रम (i = def_vid; i < dev->num_vlans; i++)
			b53_set_vlan_entry(dev, i, &vl);
	पूर्ण अन्यथा अणु
		b53_करो_vlan_op(dev, VTA_CMD_CLEAR);
	पूर्ण

	b53_enable_vlan(dev, -1, dev->vlan_enabled, ds->vlan_filtering);

	b53_क्रम_each_port(dev, i)
		b53_ग_लिखो16(dev, B53_VLAN_PAGE,
			    B53_VLAN_PORT_DEF_TAG(i), def_vid);

	/* Upon initial call we have not set-up any VLANs, but upon
	 * प्रणाली resume, we need to restore all VLAN entries.
	 */
	क्रम (vid = def_vid; vid < dev->num_vlans; vid++) अणु
		v = &dev->vlans[vid];

		अगर (!v->members)
			जारी;

		b53_set_vlan_entry(dev, vid, v);
		b53_fast_age_vlan(dev, vid);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_configure_vlan);

अटल व्योम b53_चयन_reset_gpio(काष्ठा b53_device *dev)
अणु
	पूर्णांक gpio = dev->reset_gpio;

	अगर (gpio < 0)
		वापस;

	/* Reset sequence: RESET low(50ms)->high(20ms)
	 */
	gpio_set_value(gpio, 0);
	mdelay(50);

	gpio_set_value(gpio, 1);
	mdelay(20);

	dev->current_page = 0xff;
पूर्ण

अटल पूर्णांक b53_चयन_reset(काष्ठा b53_device *dev)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u8 mgmt, reg;

	b53_चयन_reset_gpio(dev);

	अगर (is539x(dev)) अणु
		b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SOFTRESET, 0x83);
		b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SOFTRESET, 0x00);
	पूर्ण

	/* This is specअगरic to 58xx devices here, करो not use is58xx() which
	 * covers the larger Starfigther 2 family, including 7445/7278 which
	 * still use this driver as a library and need to perक्रमm the reset
	 * earlier.
	 */
	अगर (dev->chip_id == BCM58XX_DEVICE_ID ||
	    dev->chip_id == BCM583XX_DEVICE_ID) अणु
		b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SOFTRESET, &reg);
		reg |= SW_RST | EN_SW_RST | EN_CH_RST;
		b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SOFTRESET, reg);

		करो अणु
			b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SOFTRESET, &reg);
			अगर (!(reg & SW_RST))
				अवरोध;

			usleep_range(1000, 2000);
		पूर्ण जबतक (समयout-- > 0);

		अगर (समयout == 0) अणु
			dev_err(dev->dev,
				"Timeout waiting for SW_RST to clear!\n");
			वापस -ETIMEDOUT;
		पूर्ण
	पूर्ण

	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);

	अगर (!(mgmt & SM_SW_FWD_EN)) अणु
		mgmt &= ~SM_SW_FWD_MODE;
		mgmt |= SM_SW_FWD_EN;

		b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, mgmt);
		b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_SWITCH_MODE, &mgmt);

		अगर (!(mgmt & SM_SW_FWD_EN)) अणु
			dev_err(dev->dev, "Failed to enable switch!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	b53_enable_mib(dev);

	वापस b53_flush_arl(dev, FAST_AGE_STATIC);
पूर्ण

अटल पूर्णांक b53_phy_पढ़ो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा b53_device *priv = ds->priv;
	u16 value = 0;
	पूर्णांक ret;

	अगर (priv->ops->phy_पढ़ो16)
		ret = priv->ops->phy_पढ़ो16(priv, addr, reg, &value);
	अन्यथा
		ret = b53_पढ़ो16(priv, B53_PORT_MII_PAGE(addr),
				 reg * 2, &value);

	वापस ret ? ret : value;
पूर्ण

अटल पूर्णांक b53_phy_ग_लिखो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा b53_device *priv = ds->priv;

	अगर (priv->ops->phy_ग_लिखो16)
		वापस priv->ops->phy_ग_लिखो16(priv, addr, reg, val);

	वापस b53_ग_लिखो16(priv, B53_PORT_MII_PAGE(addr), reg * 2, val);
पूर्ण

अटल पूर्णांक b53_reset_चयन(काष्ठा b53_device *priv)
अणु
	/* reset vlans */
	स_रखो(priv->vlans, 0, माप(*priv->vlans) * priv->num_vlans);
	स_रखो(priv->ports, 0, माप(*priv->ports) * priv->num_ports);

	priv->serdes_lane = B53_INVALID_LANE;

	वापस b53_चयन_reset(priv);
पूर्ण

अटल पूर्णांक b53_apply_config(काष्ठा b53_device *priv)
अणु
	/* disable चयनing */
	b53_set_क्रमwarding(priv, 0);

	b53_configure_vlan(priv->ds);

	/* enable चयनing */
	b53_set_क्रमwarding(priv, 1);

	वापस 0;
पूर्ण

अटल व्योम b53_reset_mib(काष्ठा b53_device *priv)
अणु
	u8 gc;

	b53_पढ़ो8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, &gc);

	b53_ग_लिखो8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, gc | GC_RESET_MIB);
	msleep(1);
	b53_ग_लिखो8(priv, B53_MGMT_PAGE, B53_GLOBAL_CONFIG, gc & ~GC_RESET_MIB);
	msleep(1);
पूर्ण

अटल स्थिर काष्ठा b53_mib_desc *b53_get_mib(काष्ठा b53_device *dev)
अणु
	अगर (is5365(dev))
		वापस b53_mibs_65;
	अन्यथा अगर (is63xx(dev))
		वापस b53_mibs_63xx;
	अन्यथा अगर (is58xx(dev))
		वापस b53_mibs_58xx;
	अन्यथा
		वापस b53_mibs;
पूर्ण

अटल अचिन्हित पूर्णांक b53_get_mib_size(काष्ठा b53_device *dev)
अणु
	अगर (is5365(dev))
		वापस B53_MIBS_65_SIZE;
	अन्यथा अगर (is63xx(dev))
		वापस B53_MIBS_63XX_SIZE;
	अन्यथा अगर (is58xx(dev))
		वापस B53_MIBS_58XX_SIZE;
	अन्यथा
		वापस B53_MIBS_SIZE;
पूर्ण

अटल काष्ठा phy_device *b53_get_phy_device(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	/* These ports typically करो not have built-in PHYs */
	चयन (port) अणु
	हाल B53_CPU_PORT_25:
	हाल 7:
	हाल B53_CPU_PORT:
		वापस शून्य;
	पूर्ण

	वापस mdiobus_get_phy(ds->slave_mii_bus, port);
पूर्ण

व्योम b53_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
		     uपूर्णांक8_t *data)
अणु
	काष्ठा b53_device *dev = ds->priv;
	स्थिर काष्ठा b53_mib_desc *mibs = b53_get_mib(dev);
	अचिन्हित पूर्णांक mib_size = b53_get_mib_size(dev);
	काष्ठा phy_device *phydev;
	अचिन्हित पूर्णांक i;

	अगर (stringset == ETH_SS_STATS) अणु
		क्रम (i = 0; i < mib_size; i++)
			strlcpy(data + i * ETH_GSTRING_LEN,
				mibs[i].name, ETH_GSTRING_LEN);
	पूर्ण अन्यथा अगर (stringset == ETH_SS_PHY_STATS) अणु
		phydev = b53_get_phy_device(ds, port);
		अगर (!phydev)
			वापस;

		phy_ethtool_get_strings(phydev, data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(b53_get_strings);

व्योम b53_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data)
अणु
	काष्ठा b53_device *dev = ds->priv;
	स्थिर काष्ठा b53_mib_desc *mibs = b53_get_mib(dev);
	अचिन्हित पूर्णांक mib_size = b53_get_mib_size(dev);
	स्थिर काष्ठा b53_mib_desc *s;
	अचिन्हित पूर्णांक i;
	u64 val = 0;

	अगर (is5365(dev) && port == 5)
		port = 8;

	mutex_lock(&dev->stats_mutex);

	क्रम (i = 0; i < mib_size; i++) अणु
		s = &mibs[i];

		अगर (s->size == 8) अणु
			b53_पढ़ो64(dev, B53_MIB_PAGE(port), s->offset, &val);
		पूर्ण अन्यथा अणु
			u32 val32;

			b53_पढ़ो32(dev, B53_MIB_PAGE(port), s->offset,
				   &val32);
			val = val32;
		पूर्ण
		data[i] = (u64)val;
	पूर्ण

	mutex_unlock(&dev->stats_mutex);
पूर्ण
EXPORT_SYMBOL(b53_get_ethtool_stats);

व्योम b53_get_ethtool_phy_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data)
अणु
	काष्ठा phy_device *phydev;

	phydev = b53_get_phy_device(ds, port);
	अगर (!phydev)
		वापस;

	phy_ethtool_get_stats(phydev, शून्य, data);
पूर्ण
EXPORT_SYMBOL(b53_get_ethtool_phy_stats);

पूर्णांक b53_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा phy_device *phydev;

	अगर (sset == ETH_SS_STATS) अणु
		वापस b53_get_mib_size(dev);
	पूर्ण अन्यथा अगर (sset == ETH_SS_PHY_STATS) अणु
		phydev = b53_get_phy_device(ds, port);
		अगर (!phydev)
			वापस 0;

		वापस phy_ethtool_get_sset_count(phydev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_get_sset_count);

क्रमागत b53_devlink_resource_id अणु
	B53_DEVLINK_PARAM_ID_VLAN_TABLE,
पूर्ण;

अटल u64 b53_devlink_vlan_table_get(व्योम *priv)
अणु
	काष्ठा b53_device *dev = priv;
	काष्ठा b53_vlan *vl;
	अचिन्हित पूर्णांक i;
	u64 count = 0;

	क्रम (i = 0; i < dev->num_vlans; i++) अणु
		vl = &dev->vlans[i];
		अगर (vl->members)
			count++;
	पूर्ण

	वापस count;
पूर्ण

पूर्णांक b53_setup_devlink_resources(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा devlink_resource_size_params size_params;
	काष्ठा b53_device *dev = ds->priv;
	पूर्णांक err;

	devlink_resource_size_params_init(&size_params, dev->num_vlans,
					  dev->num_vlans,
					  1, DEVLINK_RESOURCE_UNIT_ENTRY);

	err = dsa_devlink_resource_रेजिस्टर(ds, "VLAN", dev->num_vlans,
					    B53_DEVLINK_PARAM_ID_VLAN_TABLE,
					    DEVLINK_RESOURCE_ID_PARENT_TOP,
					    &size_params);
	अगर (err)
		जाओ out;

	dsa_devlink_resource_occ_get_रेजिस्टर(ds,
					      B53_DEVLINK_PARAM_ID_VLAN_TABLE,
					      b53_devlink_vlan_table_get, dev);

	वापस 0;
out:
	dsa_devlink_resources_unरेजिस्टर(ds);
	वापस err;
पूर्ण
EXPORT_SYMBOL(b53_setup_devlink_resources);

अटल पूर्णांक b53_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा b53_device *dev = ds->priv;
	अचिन्हित पूर्णांक port;
	पूर्णांक ret;

	ret = b53_reset_चयन(dev);
	अगर (ret) अणु
		dev_err(ds->dev, "failed to reset switch\n");
		वापस ret;
	पूर्ण

	b53_reset_mib(dev);

	ret = b53_apply_config(dev);
	अगर (ret) अणु
		dev_err(ds->dev, "failed to apply configuration\n");
		वापस ret;
	पूर्ण

	/* Configure IMP/CPU port, disable all other ports. Enabled
	 * ports will be configured with .port_enable
	 */
	क्रम (port = 0; port < dev->num_ports; port++) अणु
		अगर (dsa_is_cpu_port(ds, port))
			b53_enable_cpu_port(dev, port);
		अन्यथा
			b53_disable_port(ds, port);
	पूर्ण

	वापस b53_setup_devlink_resources(ds);
पूर्ण

अटल व्योम b53_tearकरोwn(काष्ठा dsa_चयन *ds)
अणु
	dsa_devlink_resources_unरेजिस्टर(ds);
पूर्ण

अटल व्योम b53_क्रमce_link(काष्ठा b53_device *dev, पूर्णांक port, पूर्णांक link)
अणु
	u8 reg, val, off;

	/* Override the port settings */
	अगर (port == dev->cpu_port) अणु
		off = B53_PORT_OVERRIDE_CTRL;
		val = PORT_OVERRIDE_EN;
	पूर्ण अन्यथा अणु
		off = B53_GMII_PORT_OVERRIDE_CTRL(port);
		val = GMII_PO_EN;
	पूर्ण

	b53_पढ़ो8(dev, B53_CTRL_PAGE, off, &reg);
	reg |= val;
	अगर (link)
		reg |= PORT_OVERRIDE_LINK;
	अन्यथा
		reg &= ~PORT_OVERRIDE_LINK;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, off, reg);
पूर्ण

अटल व्योम b53_क्रमce_port_config(काष्ठा b53_device *dev, पूर्णांक port,
				  पूर्णांक speed, पूर्णांक duplex,
				  bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	u8 reg, val, off;

	/* Override the port settings */
	अगर (port == dev->cpu_port) अणु
		off = B53_PORT_OVERRIDE_CTRL;
		val = PORT_OVERRIDE_EN;
	पूर्ण अन्यथा अणु
		off = B53_GMII_PORT_OVERRIDE_CTRL(port);
		val = GMII_PO_EN;
	पूर्ण

	b53_पढ़ो8(dev, B53_CTRL_PAGE, off, &reg);
	reg |= val;
	अगर (duplex == DUPLEX_FULL)
		reg |= PORT_OVERRIDE_FULL_DUPLEX;
	अन्यथा
		reg &= ~PORT_OVERRIDE_FULL_DUPLEX;

	चयन (speed) अणु
	हाल 2000:
		reg |= PORT_OVERRIDE_SPEED_2000M;
		fallthrough;
	हाल SPEED_1000:
		reg |= PORT_OVERRIDE_SPEED_1000M;
		अवरोध;
	हाल SPEED_100:
		reg |= PORT_OVERRIDE_SPEED_100M;
		अवरोध;
	हाल SPEED_10:
		reg |= PORT_OVERRIDE_SPEED_10M;
		अवरोध;
	शेष:
		dev_err(dev->dev, "unknown speed: %d\n", speed);
		वापस;
	पूर्ण

	अगर (rx_छोड़ो)
		reg |= PORT_OVERRIDE_RX_FLOW;
	अगर (tx_छोड़ो)
		reg |= PORT_OVERRIDE_TX_FLOW;

	b53_ग_लिखो8(dev, B53_CTRL_PAGE, off, reg);
पूर्ण

अटल व्योम b53_adjust_link(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    काष्ठा phy_device *phydev)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा ethtool_eee *p = &dev->ports[port].eee;
	u8 rgmii_ctrl = 0, reg = 0, off;
	bool tx_छोड़ो = false;
	bool rx_छोड़ो = false;

	अगर (!phy_is_pseuकरो_fixed_link(phydev))
		वापस;

	/* Enable flow control on BCM5301x's CPU port */
	अगर (is5301x(dev) && port == dev->cpu_port)
		tx_छोड़ो = rx_छोड़ो = true;

	अगर (phydev->छोड़ो) अणु
		अगर (phydev->asym_छोड़ो)
			tx_छोड़ो = true;
		rx_छोड़ो = true;
	पूर्ण

	b53_क्रमce_port_config(dev, port, phydev->speed, phydev->duplex,
			      tx_छोड़ो, rx_छोड़ो);
	b53_क्रमce_link(dev, port, phydev->link);

	अगर (is531x5(dev) && phy_पूर्णांकerface_is_rgmii(phydev)) अणु
		अगर (port == 8)
			off = B53_RGMII_CTRL_IMP;
		अन्यथा
			off = B53_RGMII_CTRL_P(port);

		/* Configure the port RGMII घड़ी delay by DLL disabled and
		 * tx_clk aligned timing (restoring to reset शेषs)
		 */
		b53_पढ़ो8(dev, B53_CTRL_PAGE, off, &rgmii_ctrl);
		rgmii_ctrl &= ~(RGMII_CTRL_DLL_RXC | RGMII_CTRL_DLL_TXC |
				RGMII_CTRL_TIMING_SEL);

		/* PHY_INTERFACE_MODE_RGMII_TXID means TX पूर्णांकernal delay, make
		 * sure that we enable the port TX घड़ी पूर्णांकernal delay to
		 * account क्रम this पूर्णांकernal delay that is inserted, otherwise
		 * the चयन won't be able to receive correctly.
		 *
		 * PHY_INTERFACE_MODE_RGMII means that we are not पूर्णांकroducing
		 * any delay neither on transmission nor reception, so the
		 * BCM53125 must also be configured accordingly to account क्रम
		 * the lack of delay and पूर्णांकroduce
		 *
		 * The BCM53125 चयन has its RX घड़ी and TX घड़ी control
		 * swapped, hence the reason why we modअगरy the TX घड़ी path in
		 * the "RGMII" हाल
		 */
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID)
			rgmii_ctrl |= RGMII_CTRL_DLL_TXC;
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
			rgmii_ctrl |= RGMII_CTRL_DLL_TXC | RGMII_CTRL_DLL_RXC;
		rgmii_ctrl |= RGMII_CTRL_TIMING_SEL;
		b53_ग_लिखो8(dev, B53_CTRL_PAGE, off, rgmii_ctrl);

		dev_info(ds->dev, "Configured port %d for %s\n", port,
			 phy_modes(phydev->पूर्णांकerface));
	पूर्ण

	/* configure MII port अगर necessary */
	अगर (is5325(dev)) अणु
		b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
			  &reg);

		/* reverse mii needs to be enabled */
		अगर (!(reg & PORT_OVERRIDE_RV_MII_25)) अणु
			b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				   reg | PORT_OVERRIDE_RV_MII_25);
			b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				  &reg);

			अगर (!(reg & PORT_OVERRIDE_RV_MII_25)) अणु
				dev_err(ds->dev,
					"Failed to enable reverse MII mode\n");
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (is5301x(dev)) अणु
		अगर (port != dev->cpu_port) अणु
			b53_क्रमce_port_config(dev, dev->cpu_port, 2000,
					      DUPLEX_FULL, true, true);
			b53_क्रमce_link(dev, dev->cpu_port, 1);
		पूर्ण
	पूर्ण

	/* Re-negotiate EEE अगर it was enabled alपढ़ोy */
	p->eee_enabled = b53_eee_init(ds, port, phydev);
पूर्ण

व्योम b53_port_event(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool link;
	u16 sts;

	b53_पढ़ो16(dev, B53_STAT_PAGE, B53_LINK_STAT, &sts);
	link = !!(sts & BIT(port));
	dsa_port_phylink_mac_change(ds, port, link);
पूर्ण
EXPORT_SYMBOL(b53_port_event);

व्योम b53_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  अचिन्हित दीर्घ *supported,
			  काष्ठा phylink_link_state *state)
अणु
	काष्ठा b53_device *dev = ds->priv;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (dev->ops->serdes_phylink_validate)
		dev->ops->serdes_phylink_validate(dev, port, mask, state);

	/* Allow all the expected bits */
	phylink_set(mask, Autoneg);
	phylink_set_port_modes(mask);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	/* With the exclusion of 5325/5365, MII, Reverse MII and 802.3z, we
	 * support Gigabit, including Half duplex.
	 */
	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_REVMII &&
	    !phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) &&
	    !(is5325(dev) || is5365(dev))) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseT_Half);
	पूर्ण

	अगर (!phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	phylink_helper_basex_speed(state);
पूर्ण
EXPORT_SYMBOL(b53_phylink_validate);

पूर्णांक b53_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा phylink_link_state *state)
अणु
	काष्ठा b53_device *dev = ds->priv;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर ((phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) ||
	     state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) &&
	     dev->ops->serdes_link_state)
		ret = dev->ops->serdes_link_state(dev, port, state);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(b53_phylink_mac_link_state);

व्योम b53_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    अचिन्हित पूर्णांक mode,
			    स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (mode == MLO_AN_PHY || mode == MLO_AN_FIXED)
		वापस;

	अगर ((phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) ||
	     state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII) &&
	     dev->ops->serdes_config)
		dev->ops->serdes_config(dev, port, mode, state);
पूर्ण
EXPORT_SYMBOL(b53_phylink_mac_config);

व्योम b53_phylink_mac_an_restart(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (dev->ops->serdes_an_restart)
		dev->ops->serdes_an_restart(dev, port);
पूर्ण
EXPORT_SYMBOL(b53_phylink_mac_an_restart);

व्योम b53_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (mode == MLO_AN_PHY)
		वापस;

	अगर (mode == MLO_AN_FIXED) अणु
		b53_क्रमce_link(dev, port, false);
		वापस;
	पूर्ण

	अगर (phy_पूर्णांकerface_mode_is_8023z(पूर्णांकerface) &&
	    dev->ops->serdes_link_set)
		dev->ops->serdes_link_set(dev, port, mode, पूर्णांकerface, false);
पूर्ण
EXPORT_SYMBOL(b53_phylink_mac_link_करोwn);

व्योम b53_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     अचिन्हित पूर्णांक mode,
			     phy_पूर्णांकerface_t पूर्णांकerface,
			     काष्ठा phy_device *phydev,
			     पूर्णांक speed, पूर्णांक duplex,
			     bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (mode == MLO_AN_PHY)
		वापस;

	अगर (mode == MLO_AN_FIXED) अणु
		b53_क्रमce_port_config(dev, port, speed, duplex,
				      tx_छोड़ो, rx_छोड़ो);
		b53_क्रमce_link(dev, port, true);
		वापस;
	पूर्ण

	अगर (phy_पूर्णांकerface_mode_is_8023z(पूर्णांकerface) &&
	    dev->ops->serdes_link_set)
		dev->ops->serdes_link_set(dev, port, mode, पूर्णांकerface, true);
पूर्ण
EXPORT_SYMBOL(b53_phylink_mac_link_up);

पूर्णांक b53_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
		       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा b53_device *dev = ds->priv;

	b53_enable_vlan(dev, port, dev->vlan_enabled, vlan_filtering);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_vlan_filtering);

अटल पूर्णांक b53_vlan_prepare(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर ((is5325(dev) || is5365(dev)) && vlan->vid == 0)
		वापस -EOPNOTSUPP;

	/* Port 7 on 7278 connects to the ASP's UniMAC which is not capable of
	 * receiving VLAN tagged frames at all, we can still allow the port to
	 * be configured क्रम egress untagged.
	 */
	अगर (dev->chip_id == BCM7278_DEVICE_ID && port == 7 &&
	    !(vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED))
		वापस -EINVAL;

	अगर (vlan->vid >= dev->num_vlans)
		वापस -दुस्फल;

	b53_enable_vlan(dev, port, true, ds->vlan_filtering);

	वापस 0;
पूर्ण

पूर्णांक b53_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा b53_vlan *vl;
	पूर्णांक err;

	err = b53_vlan_prepare(ds, port, vlan);
	अगर (err)
		वापस err;

	vl = &dev->vlans[vlan->vid];

	b53_get_vlan_entry(dev, vlan->vid, vl);

	अगर (vlan->vid == 0 && vlan->vid == b53_शेष_pvid(dev))
		untagged = true;

	vl->members |= BIT(port);
	अगर (untagged && !dsa_is_cpu_port(ds, port))
		vl->untag |= BIT(port);
	अन्यथा
		vl->untag &= ~BIT(port);

	b53_set_vlan_entry(dev, vlan->vid, vl);
	b53_fast_age_vlan(dev, vlan->vid);

	अगर (pvid && !dsa_is_cpu_port(ds, port)) अणु
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_PORT_DEF_TAG(port),
			    vlan->vid);
		b53_fast_age_vlan(dev, vlan->vid);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_vlan_add);

पूर्णांक b53_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	काष्ठा b53_vlan *vl;
	u16 pvid;

	b53_पढ़ो16(dev, B53_VLAN_PAGE, B53_VLAN_PORT_DEF_TAG(port), &pvid);

	vl = &dev->vlans[vlan->vid];

	b53_get_vlan_entry(dev, vlan->vid, vl);

	vl->members &= ~BIT(port);

	अगर (pvid == vlan->vid)
		pvid = b53_शेष_pvid(dev);

	अगर (untagged && !dsa_is_cpu_port(ds, port))
		vl->untag &= ~(BIT(port));

	b53_set_vlan_entry(dev, vlan->vid, vl);
	b53_fast_age_vlan(dev, vlan->vid);

	b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_PORT_DEF_TAG(port), pvid);
	b53_fast_age_vlan(dev, pvid);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_vlan_del);

/* Address Resolution Logic routines */
अटल पूर्णांक b53_arl_op_रुको(काष्ठा b53_device *dev)
अणु
	अचिन्हित पूर्णांक समयout = 10;
	u8 reg;

	करो अणु
		b53_पढ़ो8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, &reg);
		अगर (!(reg & ARLTBL_START_DONE))
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout--);

	dev_warn(dev->dev, "timeout waiting for ARL to finish: 0x%02x\n", reg);

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक b53_arl_rw_op(काष्ठा b53_device *dev, अचिन्हित पूर्णांक op)
अणु
	u8 reg;

	अगर (op > ARLTBL_RW)
		वापस -EINVAL;

	b53_पढ़ो8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, &reg);
	reg |= ARLTBL_START_DONE;
	अगर (op)
		reg |= ARLTBL_RW;
	अन्यथा
		reg &= ~ARLTBL_RW;
	अगर (dev->vlan_enabled)
		reg &= ~ARLTBL_IVL_SVL_SELECT;
	अन्यथा
		reg |= ARLTBL_IVL_SVL_SELECT;
	b53_ग_लिखो8(dev, B53_ARLIO_PAGE, B53_ARLTBL_RW_CTRL, reg);

	वापस b53_arl_op_रुको(dev);
पूर्ण

अटल पूर्णांक b53_arl_पढ़ो(काष्ठा b53_device *dev, u64 mac,
			u16 vid, काष्ठा b53_arl_entry *ent, u8 *idx)
अणु
	DECLARE_BITMAP(मुक्त_bins, B53_ARLTBL_MAX_BIN_ENTRIES);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = b53_arl_op_रुको(dev);
	अगर (ret)
		वापस ret;

	biपंचांगap_zero(मुक्त_bins, dev->num_arl_bins);

	/* Read the bins */
	क्रम (i = 0; i < dev->num_arl_bins; i++) अणु
		u64 mac_vid;
		u32 fwd_entry;

		b53_पढ़ो64(dev, B53_ARLIO_PAGE,
			   B53_ARLTBL_MAC_VID_ENTRY(i), &mac_vid);
		b53_पढ़ो32(dev, B53_ARLIO_PAGE,
			   B53_ARLTBL_DATA_ENTRY(i), &fwd_entry);
		b53_arl_to_entry(ent, mac_vid, fwd_entry);

		अगर (!(fwd_entry & ARLTBL_VALID)) अणु
			set_bit(i, मुक्त_bins);
			जारी;
		पूर्ण
		अगर ((mac_vid & ARLTBL_MAC_MASK) != mac)
			जारी;
		अगर (dev->vlan_enabled &&
		    ((mac_vid >> ARLTBL_VID_S) & ARLTBL_VID_MASK) != vid)
			जारी;
		*idx = i;
		वापस 0;
	पूर्ण

	अगर (biपंचांगap_weight(मुक्त_bins, dev->num_arl_bins) == 0)
		वापस -ENOSPC;

	*idx = find_first_bit(मुक्त_bins, dev->num_arl_bins);

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक b53_arl_op(काष्ठा b53_device *dev, पूर्णांक op, पूर्णांक port,
		      स्थिर अचिन्हित अक्षर *addr, u16 vid, bool is_valid)
अणु
	काष्ठा b53_arl_entry ent;
	u32 fwd_entry;
	u64 mac, mac_vid = 0;
	u8 idx = 0;
	पूर्णांक ret;

	/* Convert the array पूर्णांकo a 64-bit MAC */
	mac = ether_addr_to_u64(addr);

	/* Perक्रमm a पढ़ो क्रम the given MAC and VID */
	b53_ग_लिखो48(dev, B53_ARLIO_PAGE, B53_MAC_ADDR_IDX, mac);
	b53_ग_लिखो16(dev, B53_ARLIO_PAGE, B53_VLAN_ID_IDX, vid);

	/* Issue a पढ़ो operation क्रम this MAC */
	ret = b53_arl_rw_op(dev, 1);
	अगर (ret)
		वापस ret;

	ret = b53_arl_पढ़ो(dev, mac, vid, &ent, &idx);

	/* If this is a पढ़ो, just finish now */
	अगर (op)
		वापस ret;

	चयन (ret) अणु
	हाल -ETIMEDOUT:
		वापस ret;
	हाल -ENOSPC:
		dev_dbg(dev->dev, "{%pM,%.4d} no space left in ARL\n",
			addr, vid);
		वापस is_valid ? ret : 0;
	हाल -ENOENT:
		/* We could not find a matching MAC, so reset to a new entry */
		dev_dbg(dev->dev, "{%pM,%.4d} not found, using idx: %d\n",
			addr, vid, idx);
		fwd_entry = 0;
		अवरोध;
	शेष:
		dev_dbg(dev->dev, "{%pM,%.4d} found, using idx: %d\n",
			addr, vid, idx);
		अवरोध;
	पूर्ण

	/* For multicast address, the port is a biपंचांगask and the validity
	 * is determined by having at least one port being still active
	 */
	अगर (!is_multicast_ether_addr(addr)) अणु
		ent.port = port;
		ent.is_valid = is_valid;
	पूर्ण अन्यथा अणु
		अगर (is_valid)
			ent.port |= BIT(port);
		अन्यथा
			ent.port &= ~BIT(port);

		ent.is_valid = !!(ent.port);
	पूर्ण

	ent.vid = vid;
	ent.is_अटल = true;
	ent.is_age = false;
	स_नकल(ent.mac, addr, ETH_ALEN);
	b53_arl_from_entry(&mac_vid, &fwd_entry, &ent);

	b53_ग_लिखो64(dev, B53_ARLIO_PAGE,
		    B53_ARLTBL_MAC_VID_ENTRY(idx), mac_vid);
	b53_ग_लिखो32(dev, B53_ARLIO_PAGE,
		    B53_ARLTBL_DATA_ENTRY(idx), fwd_entry);

	वापस b53_arl_rw_op(dev, 0);
पूर्ण

पूर्णांक b53_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा b53_device *priv = ds->priv;

	/* 5325 and 5365 require some more massaging, but could
	 * be supported eventually
	 */
	अगर (is5325(priv) || is5365(priv))
		वापस -EOPNOTSUPP;

	वापस b53_arl_op(priv, 0, port, addr, vid, true);
पूर्ण
EXPORT_SYMBOL(b53_fdb_add);

पूर्णांक b53_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा b53_device *priv = ds->priv;

	वापस b53_arl_op(priv, 0, port, addr, vid, false);
पूर्ण
EXPORT_SYMBOL(b53_fdb_del);

अटल पूर्णांक b53_arl_search_रुको(काष्ठा b53_device *dev)
अणु
	अचिन्हित पूर्णांक समयout = 1000;
	u8 reg;

	करो अणु
		b53_पढ़ो8(dev, B53_ARLIO_PAGE, B53_ARL_SRCH_CTL, &reg);
		अगर (!(reg & ARL_SRCH_STDN))
			वापस 0;

		अगर (reg & ARL_SRCH_VLID)
			वापस 0;

		usleep_range(1000, 2000);
	पूर्ण जबतक (समयout--);

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम b53_arl_search_rd(काष्ठा b53_device *dev, u8 idx,
			      काष्ठा b53_arl_entry *ent)
अणु
	u64 mac_vid;
	u32 fwd_entry;

	b53_पढ़ो64(dev, B53_ARLIO_PAGE,
		   B53_ARL_SRCH_RSTL_MACVID(idx), &mac_vid);
	b53_पढ़ो32(dev, B53_ARLIO_PAGE,
		   B53_ARL_SRCH_RSTL(idx), &fwd_entry);
	b53_arl_to_entry(ent, mac_vid, fwd_entry);
पूर्ण

अटल पूर्णांक b53_fdb_copy(पूर्णांक port, स्थिर काष्ठा b53_arl_entry *ent,
			dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	अगर (!ent->is_valid)
		वापस 0;

	अगर (port != ent->port)
		वापस 0;

	वापस cb(ent->mac, ent->vid, ent->is_अटल, data);
पूर्ण

पूर्णांक b53_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा b53_device *priv = ds->priv;
	काष्ठा b53_arl_entry results[2];
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक ret;
	u8 reg;

	/* Start search operation */
	reg = ARL_SRCH_STDN;
	b53_ग_लिखो8(priv, B53_ARLIO_PAGE, B53_ARL_SRCH_CTL, reg);

	करो अणु
		ret = b53_arl_search_रुको(priv);
		अगर (ret)
			वापस ret;

		b53_arl_search_rd(priv, 0, &results[0]);
		ret = b53_fdb_copy(port, &results[0], cb, data);
		अगर (ret)
			वापस ret;

		अगर (priv->num_arl_bins > 2) अणु
			b53_arl_search_rd(priv, 1, &results[1]);
			ret = b53_fdb_copy(port, &results[1], cb, data);
			अगर (ret)
				वापस ret;

			अगर (!results[0].is_valid && !results[1].is_valid)
				अवरोध;
		पूर्ण

	पूर्ण जबतक (count++ < b53_max_arl_entries(priv) / 2);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_fdb_dump);

पूर्णांक b53_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा b53_device *priv = ds->priv;

	/* 5325 and 5365 require some more massaging, but could
	 * be supported eventually
	 */
	अगर (is5325(priv) || is5365(priv))
		वापस -EOPNOTSUPP;

	वापस b53_arl_op(priv, 0, port, mdb->addr, mdb->vid, true);
पूर्ण
EXPORT_SYMBOL(b53_mdb_add);

पूर्णांक b53_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा b53_device *priv = ds->priv;
	पूर्णांक ret;

	ret = b53_arl_op(priv, 0, port, mdb->addr, mdb->vid, false);
	अगर (ret)
		dev_err(ds->dev, "failed to delete MDB entry\n");

	वापस ret;
पूर्ण
EXPORT_SYMBOL(b53_mdb_del);

पूर्णांक b53_br_join(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा b53_device *dev = ds->priv;
	s8 cpu_port = dsa_to_port(ds, port)->cpu_dp->index;
	u16 pvlan, reg;
	अचिन्हित पूर्णांक i;

	/* On 7278, port 7 which connects to the ASP should only receive
	 * traffic from matching CFP rules.
	 */
	अगर (dev->chip_id == BCM7278_DEVICE_ID && port == 7)
		वापस -EINVAL;

	/* Make this port leave the all VLANs join since we will have proper
	 * VLAN entries from now on
	 */
	अगर (is58xx(dev)) अणु
		b53_पढ़ो16(dev, B53_VLAN_PAGE, B53_JOIN_ALL_VLAN_EN, &reg);
		reg &= ~BIT(port);
		अगर ((reg & BIT(cpu_port)) == BIT(cpu_port))
			reg &= ~BIT(cpu_port);
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_JOIN_ALL_VLAN_EN, reg);
	पूर्ण

	b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), &pvlan);

	b53_क्रम_each_port(dev, i) अणु
		अगर (dsa_to_port(ds, i)->bridge_dev != br)
			जारी;

		/* Add this local port to the remote port VLAN control
		 * membership and update the remote port biपंचांगask
		 */
		b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), &reg);
		reg |= BIT(port);
		b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), reg);
		dev->ports[i].vlan_ctl_mask = reg;

		pvlan |= BIT(i);
	पूर्ण

	/* Configure the local port VLAN control membership to include
	 * remote ports and update the local port biपंचांगask
	 */
	b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), pvlan);
	dev->ports[port].vlan_ctl_mask = pvlan;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_br_join);

व्योम b53_br_leave(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *br)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा b53_vlan *vl = &dev->vlans[0];
	s8 cpu_port = dsa_to_port(ds, port)->cpu_dp->index;
	अचिन्हित पूर्णांक i;
	u16 pvlan, reg, pvid;

	b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), &pvlan);

	b53_क्रम_each_port(dev, i) अणु
		/* Don't touch the reमुख्यing ports */
		अगर (dsa_to_port(ds, i)->bridge_dev != br)
			जारी;

		b53_पढ़ो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), &reg);
		reg &= ~BIT(port);
		b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(i), reg);
		dev->ports[port].vlan_ctl_mask = reg;

		/* Prevent self removal to preserve isolation */
		अगर (port != i)
			pvlan &= ~BIT(i);
	पूर्ण

	b53_ग_लिखो16(dev, B53_PVLAN_PAGE, B53_PVLAN_PORT_MASK(port), pvlan);
	dev->ports[port].vlan_ctl_mask = pvlan;

	pvid = b53_शेष_pvid(dev);

	/* Make this port join all VLANs without VLAN entries */
	अगर (is58xx(dev)) अणु
		b53_पढ़ो16(dev, B53_VLAN_PAGE, B53_JOIN_ALL_VLAN_EN, &reg);
		reg |= BIT(port);
		अगर (!(reg & BIT(cpu_port)))
			reg |= BIT(cpu_port);
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_JOIN_ALL_VLAN_EN, reg);
	पूर्ण अन्यथा अणु
		b53_get_vlan_entry(dev, pvid, vl);
		vl->members |= BIT(port) | BIT(cpu_port);
		vl->untag |= BIT(port) | BIT(cpu_port);
		b53_set_vlan_entry(dev, pvid, vl);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(b53_br_leave);

व्योम b53_br_set_stp_state(काष्ठा dsa_चयन *ds, पूर्णांक port, u8 state)
अणु
	काष्ठा b53_device *dev = ds->priv;
	u8 hw_state;
	u8 reg;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		hw_state = PORT_CTRL_DIS_STATE;
		अवरोध;
	हाल BR_STATE_LISTENING:
		hw_state = PORT_CTRL_LISTEN_STATE;
		अवरोध;
	हाल BR_STATE_LEARNING:
		hw_state = PORT_CTRL_LEARN_STATE;
		अवरोध;
	हाल BR_STATE_FORWARDING:
		hw_state = PORT_CTRL_FWD_STATE;
		अवरोध;
	हाल BR_STATE_BLOCKING:
		hw_state = PORT_CTRL_BLOCK_STATE;
		अवरोध;
	शेष:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		वापस;
	पूर्ण

	b53_पढ़ो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), &reg);
	reg &= ~PORT_CTRL_STP_STATE_MASK;
	reg |= hw_state;
	b53_ग_लिखो8(dev, B53_CTRL_PAGE, B53_PORT_CTRL(port), reg);
पूर्ण
EXPORT_SYMBOL(b53_br_set_stp_state);

व्योम b53_br_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (b53_fast_age_port(dev, port))
		dev_err(ds->dev, "fast ageing failed\n");
पूर्ण
EXPORT_SYMBOL(b53_br_fast_age);

पूर्णांक b53_br_flags_pre(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     काष्ठा चयनdev_brport_flags flags,
		     काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flags.mask & ~(BR_FLOOD | BR_MCAST_FLOOD | BR_LEARNING))
		वापस -EINVAL;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_br_flags_pre);

पूर्णांक b53_br_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 काष्ठा चयनdev_brport_flags flags,
		 काष्ठा netlink_ext_ack *extack)
अणु
	अगर (flags.mask & BR_FLOOD)
		b53_port_set_ucast_flood(ds->priv, port,
					 !!(flags.val & BR_FLOOD));
	अगर (flags.mask & BR_MCAST_FLOOD)
		b53_port_set_mcast_flood(ds->priv, port,
					 !!(flags.val & BR_MCAST_FLOOD));
	अगर (flags.mask & BR_LEARNING)
		b53_port_set_learning(ds->priv, port,
				      !!(flags.val & BR_LEARNING));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_br_flags);

पूर्णांक b53_set_mrouter(काष्ठा dsa_चयन *ds, पूर्णांक port, bool mrouter,
		    काष्ठा netlink_ext_ack *extack)
अणु
	b53_port_set_mcast_flood(ds->priv, port, mrouter);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_set_mrouter);

अटल bool b53_possible_cpu_port(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	/* Broadcom चयनes will accept enabling Broadcom tags on the
	 * following ports: 5, 7 and 8, any other port is not supported
	 */
	चयन (port) अणु
	हाल B53_CPU_PORT_25:
	हाल 7:
	हाल B53_CPU_PORT:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool b53_can_enable_brcm_tags(काष्ठा dsa_चयन *ds, पूर्णांक port,
				     क्रमागत dsa_tag_protocol tag_protocol)
अणु
	bool ret = b53_possible_cpu_port(ds, port);

	अगर (!ret) अणु
		dev_warn(ds->dev, "Port %d is not Broadcom tag capable\n",
			 port);
		वापस ret;
	पूर्ण

	चयन (tag_protocol) अणु
	हाल DSA_TAG_PROTO_BRCM:
	हाल DSA_TAG_PROTO_BRCM_PREPEND:
		dev_warn(ds->dev,
			 "Port %d is stacked to Broadcom tag switch\n", port);
		ret = false;
		अवरोध;
	शेष:
		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

क्रमागत dsa_tag_protocol b53_get_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
					   क्रमागत dsa_tag_protocol mprot)
अणु
	काष्ठा b53_device *dev = ds->priv;

	अगर (!b53_can_enable_brcm_tags(ds, port, mprot)) अणु
		dev->tag_protocol = DSA_TAG_PROTO_NONE;
		जाओ out;
	पूर्ण

	/* Older models require a dअगरferent 6 byte tag */
	अगर (is5325(dev) || is5365(dev) || is63xx(dev)) अणु
		dev->tag_protocol = DSA_TAG_PROTO_BRCM_LEGACY;
		जाओ out;
	पूर्ण

	/* Broadcom BCM58xx chips have a flow accelerator on Port 8
	 * which requires us to use the prepended Broadcom tag type
	 */
	अगर (dev->chip_id == BCM58XX_DEVICE_ID && port == B53_CPU_PORT) अणु
		dev->tag_protocol = DSA_TAG_PROTO_BRCM_PREPEND;
		जाओ out;
	पूर्ण

	dev->tag_protocol = DSA_TAG_PROTO_BRCM;
out:
	वापस dev->tag_protocol;
पूर्ण
EXPORT_SYMBOL(b53_get_tag_protocol);

पूर्णांक b53_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		   काष्ठा dsa_mall_mirror_tc_entry *mirror, bool ingress)
अणु
	काष्ठा b53_device *dev = ds->priv;
	u16 reg, loc;

	अगर (ingress)
		loc = B53_IG_MIR_CTL;
	अन्यथा
		loc = B53_EG_MIR_CTL;

	b53_पढ़ो16(dev, B53_MGMT_PAGE, loc, &reg);
	reg |= BIT(port);
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, loc, reg);

	b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, &reg);
	reg &= ~CAP_PORT_MASK;
	reg |= mirror->to_local_port;
	reg |= MIRROR_EN;
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_mirror_add);

व्योम b53_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    काष्ठा dsa_mall_mirror_tc_entry *mirror)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool loc_disable = false, other_loc_disable = false;
	u16 reg, loc;

	अगर (mirror->ingress)
		loc = B53_IG_MIR_CTL;
	अन्यथा
		loc = B53_EG_MIR_CTL;

	/* Update the desired ingress/egress रेजिस्टर */
	b53_पढ़ो16(dev, B53_MGMT_PAGE, loc, &reg);
	reg &= ~BIT(port);
	अगर (!(reg & MIRROR_MASK))
		loc_disable = true;
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, loc, reg);

	/* Now look at the other one to know अगर we can disable mirroring
	 * entirely
	 */
	अगर (mirror->ingress)
		b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_EG_MIR_CTL, &reg);
	अन्यथा
		b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_IG_MIR_CTL, &reg);
	अगर (!(reg & MIRROR_MASK))
		other_loc_disable = true;

	b53_पढ़ो16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, &reg);
	/* Both no दीर्घer have ports, let's disable mirroring */
	अगर (loc_disable && other_loc_disable) अणु
		reg &= ~MIRROR_EN;
		reg &= ~mirror->to_local_port;
	पूर्ण
	b53_ग_लिखो16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, reg);
पूर्ण
EXPORT_SYMBOL(b53_mirror_del);

व्योम b53_eee_enable_set(काष्ठा dsa_चयन *ds, पूर्णांक port, bool enable)
अणु
	काष्ठा b53_device *dev = ds->priv;
	u16 reg;

	b53_पढ़ो16(dev, B53_EEE_PAGE, B53_EEE_EN_CTRL, &reg);
	अगर (enable)
		reg |= BIT(port);
	अन्यथा
		reg &= ~BIT(port);
	b53_ग_लिखो16(dev, B53_EEE_PAGE, B53_EEE_EN_CTRL, reg);
पूर्ण
EXPORT_SYMBOL(b53_eee_enable_set);


/* Returns 0 अगर EEE was not enabled, or 1 otherwise
 */
पूर्णांक b53_eee_init(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy)
अणु
	पूर्णांक ret;

	ret = phy_init_eee(phy, 0);
	अगर (ret)
		वापस 0;

	b53_eee_enable_set(ds, port, true);

	वापस 1;
पूर्ण
EXPORT_SYMBOL(b53_eee_init);

पूर्णांक b53_get_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *e)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा ethtool_eee *p = &dev->ports[port].eee;
	u16 reg;

	अगर (is5325(dev) || is5365(dev))
		वापस -EOPNOTSUPP;

	b53_पढ़ो16(dev, B53_EEE_PAGE, B53_EEE_LPI_INDICATE, &reg);
	e->eee_enabled = p->eee_enabled;
	e->eee_active = !!(reg & BIT(port));

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_get_mac_eee);

पूर्णांक b53_set_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *e)
अणु
	काष्ठा b53_device *dev = ds->priv;
	काष्ठा ethtool_eee *p = &dev->ports[port].eee;

	अगर (is5325(dev) || is5365(dev))
		वापस -EOPNOTSUPP;

	p->eee_enabled = e->eee_enabled;
	b53_eee_enable_set(ds, port, e->eee_enabled);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(b53_set_mac_eee);

अटल पूर्णांक b53_change_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक mtu)
अणु
	काष्ठा b53_device *dev = ds->priv;
	bool enable_jumbo;
	bool allow_10_100;

	अगर (is5325(dev) || is5365(dev))
		वापस -EOPNOTSUPP;

	enable_jumbo = (mtu >= JMS_MIN_SIZE);
	allow_10_100 = (dev->chip_id == BCM583XX_DEVICE_ID);

	वापस b53_set_jumbo(dev, enable_jumbo, allow_10_100);
पूर्ण

अटल पूर्णांक b53_get_max_mtu(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	वापस JMS_MAX_SIZE;
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops b53_चयन_ops = अणु
	.get_tag_protocol	= b53_get_tag_protocol,
	.setup			= b53_setup,
	.tearकरोwn		= b53_tearकरोwn,
	.get_strings		= b53_get_strings,
	.get_ethtool_stats	= b53_get_ethtool_stats,
	.get_sset_count		= b53_get_sset_count,
	.get_ethtool_phy_stats	= b53_get_ethtool_phy_stats,
	.phy_पढ़ो		= b53_phy_पढ़ो16,
	.phy_ग_लिखो		= b53_phy_ग_लिखो16,
	.adjust_link		= b53_adjust_link,
	.phylink_validate	= b53_phylink_validate,
	.phylink_mac_link_state	= b53_phylink_mac_link_state,
	.phylink_mac_config	= b53_phylink_mac_config,
	.phylink_mac_an_restart	= b53_phylink_mac_an_restart,
	.phylink_mac_link_करोwn	= b53_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= b53_phylink_mac_link_up,
	.port_enable		= b53_enable_port,
	.port_disable		= b53_disable_port,
	.get_mac_eee		= b53_get_mac_eee,
	.set_mac_eee		= b53_set_mac_eee,
	.port_bridge_join	= b53_br_join,
	.port_bridge_leave	= b53_br_leave,
	.port_pre_bridge_flags	= b53_br_flags_pre,
	.port_bridge_flags	= b53_br_flags,
	.port_set_mrouter	= b53_set_mrouter,
	.port_stp_state_set	= b53_br_set_stp_state,
	.port_fast_age		= b53_br_fast_age,
	.port_vlan_filtering	= b53_vlan_filtering,
	.port_vlan_add		= b53_vlan_add,
	.port_vlan_del		= b53_vlan_del,
	.port_fdb_dump		= b53_fdb_dump,
	.port_fdb_add		= b53_fdb_add,
	.port_fdb_del		= b53_fdb_del,
	.port_mirror_add	= b53_mirror_add,
	.port_mirror_del	= b53_mirror_del,
	.port_mdb_add		= b53_mdb_add,
	.port_mdb_del		= b53_mdb_del,
	.port_max_mtu		= b53_get_max_mtu,
	.port_change_mtu	= b53_change_mtu,
पूर्ण;

काष्ठा b53_chip_data अणु
	u32 chip_id;
	स्थिर अक्षर *dev_name;
	u16 vlans;
	u16 enabled_ports;
	u8 cpu_port;
	u8 vta_regs[3];
	u8 arl_bins;
	u16 arl_buckets;
	u8 duplex_reg;
	u8 jumbo_pm_reg;
	u8 jumbo_size_reg;
पूर्ण;

#घोषणा B53_VTA_REGS	\
	अणु B53_VT_ACCESS, B53_VT_INDEX, B53_VT_ENTRY पूर्ण
#घोषणा B53_VTA_REGS_9798 \
	अणु B53_VT_ACCESS_9798, B53_VT_INDEX_9798, B53_VT_ENTRY_9798 पूर्ण
#घोषणा B53_VTA_REGS_63XX \
	अणु B53_VT_ACCESS_63XX, B53_VT_INDEX_63XX, B53_VT_ENTRY_63XX पूर्ण

अटल स्थिर काष्ठा b53_chip_data b53_चयन_chips[] = अणु
	अणु
		.chip_id = BCM5325_DEVICE_ID,
		.dev_name = "BCM5325",
		.vlans = 16,
		.enabled_ports = 0x1f,
		.arl_bins = 2,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25,
		.duplex_reg = B53_DUPLEX_STAT_FE,
	पूर्ण,
	अणु
		.chip_id = BCM5365_DEVICE_ID,
		.dev_name = "BCM5365",
		.vlans = 256,
		.enabled_ports = 0x1f,
		.arl_bins = 2,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25,
		.duplex_reg = B53_DUPLEX_STAT_FE,
	पूर्ण,
	अणु
		.chip_id = BCM5389_DEVICE_ID,
		.dev_name = "BCM5389",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM5395_DEVICE_ID,
		.dev_name = "BCM5395",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM5397_DEVICE_ID,
		.dev_name = "BCM5397",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS_9798,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM5398_DEVICE_ID,
		.dev_name = "BCM5398",
		.vlans = 4096,
		.enabled_ports = 0x7f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS_9798,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53115_DEVICE_ID,
		.dev_name = "BCM53115",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.vta_regs = B53_VTA_REGS,
		.cpu_port = B53_CPU_PORT,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53125_DEVICE_ID,
		.dev_name = "BCM53125",
		.vlans = 4096,
		.enabled_ports = 0xff,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53128_DEVICE_ID,
		.dev_name = "BCM53128",
		.vlans = 4096,
		.enabled_ports = 0x1ff,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM63XX_DEVICE_ID,
		.dev_name = "BCM63xx",
		.vlans = 4096,
		.enabled_ports = 0, /* pdata must provide them */
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS_63XX,
		.duplex_reg = B53_DUPLEX_STAT_63XX,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK_63XX,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE_63XX,
	पूर्ण,
	अणु
		.chip_id = BCM53010_DEVICE_ID,
		.dev_name = "BCM53010",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25, /* TODO: स्वतः detect */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53011_DEVICE_ID,
		.dev_name = "BCM53011",
		.vlans = 4096,
		.enabled_ports = 0x1bf,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25, /* TODO: स्वतः detect */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53012_DEVICE_ID,
		.dev_name = "BCM53012",
		.vlans = 4096,
		.enabled_ports = 0x1bf,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25, /* TODO: स्वतः detect */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53018_DEVICE_ID,
		.dev_name = "BCM53018",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25, /* TODO: स्वतः detect */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM53019_DEVICE_ID,
		.dev_name = "BCM53019",
		.vlans = 4096,
		.enabled_ports = 0x1f,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT_25, /* TODO: स्वतः detect */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM58XX_DEVICE_ID,
		.dev_name = "BCM585xx/586xx/88312",
		.vlans	= 4096,
		.enabled_ports = 0x1ff,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM583XX_DEVICE_ID,
		.dev_name = "BCM583xx/11360",
		.vlans = 4096,
		.enabled_ports = 0x103,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	/* Starfighter 2 */
	अणु
		.chip_id = BCM4908_DEVICE_ID,
		.dev_name = "BCM4908",
		.vlans = 4096,
		.enabled_ports = 0x1bf,
		.arl_bins = 4,
		.arl_buckets = 256,
		.cpu_port = 8, /* TODO: ports 4, 5, 8 */
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM7445_DEVICE_ID,
		.dev_name = "BCM7445",
		.vlans	= 4096,
		.enabled_ports = 0x1ff,
		.arl_bins = 4,
		.arl_buckets = 1024,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
	अणु
		.chip_id = BCM7278_DEVICE_ID,
		.dev_name = "BCM7278",
		.vlans = 4096,
		.enabled_ports = 0x1ff,
		.arl_bins = 4,
		.arl_buckets = 256,
		.cpu_port = B53_CPU_PORT,
		.vta_regs = B53_VTA_REGS,
		.duplex_reg = B53_DUPLEX_STAT_GE,
		.jumbo_pm_reg = B53_JUMBO_PORT_MASK,
		.jumbo_size_reg = B53_JUMBO_MAX_SIZE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक b53_चयन_init(काष्ठा b53_device *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(b53_चयन_chips); i++) अणु
		स्थिर काष्ठा b53_chip_data *chip = &b53_चयन_chips[i];

		अगर (chip->chip_id == dev->chip_id) अणु
			अगर (!dev->enabled_ports)
				dev->enabled_ports = chip->enabled_ports;
			dev->name = chip->dev_name;
			dev->duplex_reg = chip->duplex_reg;
			dev->vta_regs[0] = chip->vta_regs[0];
			dev->vta_regs[1] = chip->vta_regs[1];
			dev->vta_regs[2] = chip->vta_regs[2];
			dev->jumbo_pm_reg = chip->jumbo_pm_reg;
			dev->cpu_port = chip->cpu_port;
			dev->num_vlans = chip->vlans;
			dev->num_arl_bins = chip->arl_bins;
			dev->num_arl_buckets = chip->arl_buckets;
			अवरोध;
		पूर्ण
	पूर्ण

	/* check which BCM5325x version we have */
	अगर (is5325(dev)) अणु
		u8 vc4;

		b53_पढ़ो8(dev, B53_VLAN_PAGE, B53_VLAN_CTRL4_25, &vc4);

		/* check reserved bits */
		चयन (vc4 & 3) अणु
		हाल 1:
			/* BCM5325E */
			अवरोध;
		हाल 3:
			/* BCM5325F - करो not use port 4 */
			dev->enabled_ports &= ~BIT(4);
			अवरोध;
		शेष:
/* On the BCM47XX SoCs this is the supported पूर्णांकernal चयन.*/
#अगर_अघोषित CONFIG_BCM47XX
			/* BCM5325M */
			वापस -EINVAL;
#अन्यथा
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण अन्यथा अगर (dev->chip_id == BCM53115_DEVICE_ID) अणु
		u64 strap_value;

		b53_पढ़ो48(dev, B53_STAT_PAGE, B53_STRAP_VALUE, &strap_value);
		/* use second IMP port अगर GMII is enabled */
		अगर (strap_value & SV_GMII_CTRL_115)
			dev->cpu_port = 5;
	पूर्ण

	/* cpu port is always last */
	dev->num_ports = dev->cpu_port + 1;
	dev->enabled_ports |= BIT(dev->cpu_port);

	/* Include non standard CPU port built-in PHYs to be probed */
	अगर (is539x(dev) || is531x5(dev)) अणु
		क्रम (i = 0; i < dev->num_ports; i++) अणु
			अगर (!(dev->ds->phys_mii_mask & BIT(i)) &&
			    !b53_possible_cpu_port(dev->ds, i))
				dev->ds->phys_mii_mask |= BIT(i);
		पूर्ण
	पूर्ण

	dev->ports = devm_kसुस्मृति(dev->dev,
				  dev->num_ports, माप(काष्ठा b53_port),
				  GFP_KERNEL);
	अगर (!dev->ports)
		वापस -ENOMEM;

	dev->vlans = devm_kसुस्मृति(dev->dev,
				  dev->num_vlans, माप(काष्ठा b53_vlan),
				  GFP_KERNEL);
	अगर (!dev->vlans)
		वापस -ENOMEM;

	dev->reset_gpio = b53_चयन_get_reset_gpio(dev);
	अगर (dev->reset_gpio >= 0) अणु
		ret = devm_gpio_request_one(dev->dev, dev->reset_gpio,
					    GPIOF_OUT_INIT_HIGH, "robo_reset");
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा b53_device *b53_चयन_alloc(काष्ठा device *base,
				    स्थिर काष्ठा b53_io_ops *ops,
				    व्योम *priv)
अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा b53_device *dev;

	ds = devm_kzalloc(base, माप(*ds), GFP_KERNEL);
	अगर (!ds)
		वापस शून्य;

	ds->dev = base;
	ds->num_ports = DSA_MAX_PORTS;

	dev = devm_kzalloc(base, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	ds->priv = dev;
	dev->dev = base;

	dev->ds = ds;
	dev->priv = priv;
	dev->ops = ops;
	ds->ops = &b53_चयन_ops;
	ds->untag_bridge_pvid = true;
	dev->vlan_enabled = true;
	/* Let DSA handle the हाल were multiple bridges span the same चयन
	 * device and dअगरferent VLAN awareness settings are requested, which
	 * would be अवरोधing filtering semantics क्रम any of the other bridge
	 * devices. (not hardware supported)
	 */
	ds->vlan_filtering_is_global = true;

	mutex_init(&dev->reg_mutex);
	mutex_init(&dev->stats_mutex);

	वापस dev;
पूर्ण
EXPORT_SYMBOL(b53_चयन_alloc);

पूर्णांक b53_चयन_detect(काष्ठा b53_device *dev)
अणु
	u32 id32;
	u16 पंचांगp;
	u8 id8;
	पूर्णांक ret;

	ret = b53_पढ़ो8(dev, B53_MGMT_PAGE, B53_DEVICE_ID, &id8);
	अगर (ret)
		वापस ret;

	चयन (id8) अणु
	हाल 0:
		/* BCM5325 and BCM5365 करो not have this रेजिस्टर so पढ़ोs
		 * वापस 0. But the पढ़ो operation did succeed, so assume this
		 * is one of them.
		 *
		 * Next check अगर we can ग_लिखो to the 5325's VTA रेजिस्टर; क्रम
		 * 5365 it is पढ़ो only.
		 */
		b53_ग_लिखो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_25, 0xf);
		b53_पढ़ो16(dev, B53_VLAN_PAGE, B53_VLAN_TABLE_ACCESS_25, &पंचांगp);

		अगर (पंचांगp == 0xf)
			dev->chip_id = BCM5325_DEVICE_ID;
		अन्यथा
			dev->chip_id = BCM5365_DEVICE_ID;
		अवरोध;
	हाल BCM5389_DEVICE_ID:
	हाल BCM5395_DEVICE_ID:
	हाल BCM5397_DEVICE_ID:
	हाल BCM5398_DEVICE_ID:
		dev->chip_id = id8;
		अवरोध;
	शेष:
		ret = b53_पढ़ो32(dev, B53_MGMT_PAGE, B53_DEVICE_ID, &id32);
		अगर (ret)
			वापस ret;

		चयन (id32) अणु
		हाल BCM53115_DEVICE_ID:
		हाल BCM53125_DEVICE_ID:
		हाल BCM53128_DEVICE_ID:
		हाल BCM53010_DEVICE_ID:
		हाल BCM53011_DEVICE_ID:
		हाल BCM53012_DEVICE_ID:
		हाल BCM53018_DEVICE_ID:
		हाल BCM53019_DEVICE_ID:
			dev->chip_id = id32;
			अवरोध;
		शेष:
			dev_err(dev->dev,
				"unsupported switch detected (BCM53%02x/BCM%x)\n",
				id8, id32);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	अगर (dev->chip_id == BCM5325_DEVICE_ID)
		वापस b53_पढ़ो8(dev, B53_STAT_PAGE, B53_REV_ID_25,
				 &dev->core_rev);
	अन्यथा
		वापस b53_पढ़ो8(dev, B53_MGMT_PAGE, B53_REV_ID,
				 &dev->core_rev);
पूर्ण
EXPORT_SYMBOL(b53_चयन_detect);

पूर्णांक b53_चयन_रेजिस्टर(काष्ठा b53_device *dev)
अणु
	पूर्णांक ret;

	अगर (dev->pdata) अणु
		dev->chip_id = dev->pdata->chip_id;
		dev->enabled_ports = dev->pdata->enabled_ports;
	पूर्ण

	अगर (!dev->chip_id && b53_चयन_detect(dev))
		वापस -EINVAL;

	ret = b53_चयन_init(dev);
	अगर (ret)
		वापस ret;

	dev_info(dev->dev, "found switch: %s, rev %i\n",
		 dev->name, dev->core_rev);

	वापस dsa_रेजिस्टर_चयन(dev->ds);
पूर्ण
EXPORT_SYMBOL(b53_चयन_रेजिस्टर);

MODULE_AUTHOR("Jonas Gorski <jogo@openwrt.org>");
MODULE_DESCRIPTION("B53 switch library");
MODULE_LICENSE("Dual BSD/GPL");
