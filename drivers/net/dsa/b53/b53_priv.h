<शैली गुरु>
/*
 * B53 common definitions
 *
 * Copyright (C) 2011-2013 Jonas Gorski <jogo@खोलोwrt.org>
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

#अगर_अघोषित __B53_PRIV_H
#घोषणा __B53_PRIV_H

#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/phy.h>
#समावेश <linux/etherdevice.h>
#समावेश <net/dsa.h>

#समावेश "b53_regs.h"

काष्ठा b53_device;
काष्ठा net_device;
काष्ठा phylink_link_state;

काष्ठा b53_io_ops अणु
	पूर्णांक (*पढ़ो8)(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *value);
	पूर्णांक (*पढ़ो16)(काष्ठा b53_device *dev, u8 page, u8 reg, u16 *value);
	पूर्णांक (*पढ़ो32)(काष्ठा b53_device *dev, u8 page, u8 reg, u32 *value);
	पूर्णांक (*पढ़ो48)(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *value);
	पूर्णांक (*पढ़ो64)(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *value);
	पूर्णांक (*ग_लिखो8)(काष्ठा b53_device *dev, u8 page, u8 reg, u8 value);
	पूर्णांक (*ग_लिखो16)(काष्ठा b53_device *dev, u8 page, u8 reg, u16 value);
	पूर्णांक (*ग_लिखो32)(काष्ठा b53_device *dev, u8 page, u8 reg, u32 value);
	पूर्णांक (*ग_लिखो48)(काष्ठा b53_device *dev, u8 page, u8 reg, u64 value);
	पूर्णांक (*ग_लिखो64)(काष्ठा b53_device *dev, u8 page, u8 reg, u64 value);
	पूर्णांक (*phy_पढ़ो16)(काष्ठा b53_device *dev, पूर्णांक addr, पूर्णांक reg, u16 *value);
	पूर्णांक (*phy_ग_लिखो16)(काष्ठा b53_device *dev, पूर्णांक addr, पूर्णांक reg, u16 value);
	पूर्णांक (*irq_enable)(काष्ठा b53_device *dev, पूर्णांक port);
	व्योम (*irq_disable)(काष्ठा b53_device *dev, पूर्णांक port);
	u8 (*serdes_map_lane)(काष्ठा b53_device *dev, पूर्णांक port);
	पूर्णांक (*serdes_link_state)(काष्ठा b53_device *dev, पूर्णांक port,
				 काष्ठा phylink_link_state *state);
	व्योम (*serdes_config)(काष्ठा b53_device *dev, पूर्णांक port,
			      अचिन्हित पूर्णांक mode,
			      स्थिर काष्ठा phylink_link_state *state);
	व्योम (*serdes_an_restart)(काष्ठा b53_device *dev, पूर्णांक port);
	व्योम (*serdes_link_set)(काष्ठा b53_device *dev, पूर्णांक port,
				अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
				bool link_up);
	व्योम (*serdes_phylink_validate)(काष्ठा b53_device *dev, पूर्णांक port,
					अचिन्हित दीर्घ *supported,
					काष्ठा phylink_link_state *state);
पूर्ण;

#घोषणा B53_INVALID_LANE	0xff

क्रमागत अणु
	BCM4908_DEVICE_ID = 0x4908,
	BCM5325_DEVICE_ID = 0x25,
	BCM5365_DEVICE_ID = 0x65,
	BCM5389_DEVICE_ID = 0x89,
	BCM5395_DEVICE_ID = 0x95,
	BCM5397_DEVICE_ID = 0x97,
	BCM5398_DEVICE_ID = 0x98,
	BCM53115_DEVICE_ID = 0x53115,
	BCM53125_DEVICE_ID = 0x53125,
	BCM53128_DEVICE_ID = 0x53128,
	BCM63XX_DEVICE_ID = 0x6300,
	BCM53010_DEVICE_ID = 0x53010,
	BCM53011_DEVICE_ID = 0x53011,
	BCM53012_DEVICE_ID = 0x53012,
	BCM53018_DEVICE_ID = 0x53018,
	BCM53019_DEVICE_ID = 0x53019,
	BCM58XX_DEVICE_ID = 0x5800,
	BCM583XX_DEVICE_ID = 0x58300,
	BCM7445_DEVICE_ID = 0x7445,
	BCM7278_DEVICE_ID = 0x7278,
पूर्ण;

#घोषणा B53_N_PORTS	9
#घोषणा B53_N_PORTS_25	6

काष्ठा b53_port अणु
	u16		vlan_ctl_mask;
	काष्ठा ethtool_eee eee;
पूर्ण;

काष्ठा b53_vlan अणु
	u16 members;
	u16 untag;
	bool valid;
पूर्ण;

काष्ठा b53_device अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा b53_platक्रमm_data *pdata;
	स्थिर अक्षर *name;

	काष्ठा mutex reg_mutex;
	काष्ठा mutex stats_mutex;
	स्थिर काष्ठा b53_io_ops *ops;

	/* chip specअगरic data */
	u32 chip_id;
	u8 core_rev;
	u8 vta_regs[3];
	u8 duplex_reg;
	u8 jumbo_pm_reg;
	u8 jumbo_size_reg;
	पूर्णांक reset_gpio;
	u8 num_arl_bins;
	u16 num_arl_buckets;
	क्रमागत dsa_tag_protocol tag_protocol;

	/* used ports mask */
	u16 enabled_ports;
	अचिन्हित पूर्णांक cpu_port;

	/* connect specअगरic data */
	u8 current_page;
	काष्ठा device *dev;
	u8 serdes_lane;

	/* Master MDIO bus we got probed from */
	काष्ठा mii_bus *bus;

	व्योम *priv;

	/* run समय configuration */
	bool enable_jumbo;

	अचिन्हित पूर्णांक num_vlans;
	काष्ठा b53_vlan *vlans;
	bool vlan_enabled;
	अचिन्हित पूर्णांक num_ports;
	काष्ठा b53_port *ports;
पूर्ण;

#घोषणा b53_क्रम_each_port(dev, i) \
	क्रम (i = 0; i < B53_N_PORTS; i++) \
		अगर (dev->enabled_ports & BIT(i))


अटल अंतरभूत पूर्णांक is5325(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM5325_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is5365(काष्ठा b53_device *dev)
अणु
#अगर_घोषित CONFIG_BCM47XX
	वापस dev->chip_id == BCM5365_DEVICE_ID;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक is5397_98(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM5397_DEVICE_ID ||
		dev->chip_id == BCM5398_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is539x(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM5395_DEVICE_ID ||
		dev->chip_id == BCM5397_DEVICE_ID ||
		dev->chip_id == BCM5398_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is531x5(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM53115_DEVICE_ID ||
		dev->chip_id == BCM53125_DEVICE_ID ||
		dev->chip_id == BCM53128_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is63xx(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM63XX_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is5301x(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM53010_DEVICE_ID ||
		dev->chip_id == BCM53011_DEVICE_ID ||
		dev->chip_id == BCM53012_DEVICE_ID ||
		dev->chip_id == BCM53018_DEVICE_ID ||
		dev->chip_id == BCM53019_DEVICE_ID;
पूर्ण

अटल अंतरभूत पूर्णांक is58xx(काष्ठा b53_device *dev)
अणु
	वापस dev->chip_id == BCM58XX_DEVICE_ID ||
		dev->chip_id == BCM583XX_DEVICE_ID ||
		dev->chip_id == BCM7445_DEVICE_ID ||
		dev->chip_id == BCM7278_DEVICE_ID;
पूर्ण

#घोषणा B53_CPU_PORT_25	5
#घोषणा B53_CPU_PORT	8

अटल अंतरभूत अचिन्हित पूर्णांक b53_max_arl_entries(काष्ठा b53_device *dev)
अणु
	वापस dev->num_arl_buckets * dev->num_arl_bins;
पूर्ण

काष्ठा b53_device *b53_चयन_alloc(काष्ठा device *base,
				    स्थिर काष्ठा b53_io_ops *ops,
				    व्योम *priv);

पूर्णांक b53_चयन_detect(काष्ठा b53_device *dev);

पूर्णांक b53_चयन_रेजिस्टर(काष्ठा b53_device *dev);

अटल अंतरभूत व्योम b53_चयन_हटाओ(काष्ठा b53_device *dev)
अणु
	dsa_unरेजिस्टर_चयन(dev->ds);
पूर्ण

#घोषणा b53_build_op(type_op_size, val_type)				\
अटल अंतरभूत पूर्णांक b53_##type_op_size(काष्ठा b53_device *dev, u8 page,	\
				     u8 reg, val_type val)		\
अणु									\
	पूर्णांक ret;							\
									\
	mutex_lock(&dev->reg_mutex);					\
	ret = dev->ops->type_op_size(dev, page, reg, val);		\
	mutex_unlock(&dev->reg_mutex);					\
									\
	वापस ret;							\
पूर्ण

b53_build_op(पढ़ो8, u8 *);
b53_build_op(पढ़ो16, u16 *);
b53_build_op(पढ़ो32, u32 *);
b53_build_op(पढ़ो48, u64 *);
b53_build_op(पढ़ो64, u64 *);

b53_build_op(ग_लिखो8, u8);
b53_build_op(ग_लिखो16, u16);
b53_build_op(ग_लिखो32, u32);
b53_build_op(ग_लिखो48, u64);
b53_build_op(ग_लिखो64, u64);

काष्ठा b53_arl_entry अणु
	u16 port;
	u8 mac[ETH_ALEN];
	u16 vid;
	u8 is_valid:1;
	u8 is_age:1;
	u8 is_अटल:1;
पूर्ण;

अटल अंतरभूत व्योम b53_arl_to_entry(काष्ठा b53_arl_entry *ent,
				    u64 mac_vid, u32 fwd_entry)
अणु
	स_रखो(ent, 0, माप(*ent));
	ent->port = fwd_entry & ARLTBL_DATA_PORT_ID_MASK;
	ent->is_valid = !!(fwd_entry & ARLTBL_VALID);
	ent->is_age = !!(fwd_entry & ARLTBL_AGE);
	ent->is_अटल = !!(fwd_entry & ARLTBL_STATIC);
	u64_to_ether_addr(mac_vid, ent->mac);
	ent->vid = mac_vid >> ARLTBL_VID_S;
पूर्ण

अटल अंतरभूत व्योम b53_arl_from_entry(u64 *mac_vid, u32 *fwd_entry,
				      स्थिर काष्ठा b53_arl_entry *ent)
अणु
	*mac_vid = ether_addr_to_u64(ent->mac);
	*mac_vid |= (u64)(ent->vid & ARLTBL_VID_MASK) << ARLTBL_VID_S;
	*fwd_entry = ent->port & ARLTBL_DATA_PORT_ID_MASK;
	अगर (ent->is_valid)
		*fwd_entry |= ARLTBL_VALID;
	अगर (ent->is_अटल)
		*fwd_entry |= ARLTBL_STATIC;
	अगर (ent->is_age)
		*fwd_entry |= ARLTBL_AGE;
पूर्ण

#अगर_घोषित CONFIG_BCM47XX

#समावेश <linux/bcm47xx_nvram.h>
#समावेश <bcm47xx_board.h>
अटल अंतरभूत पूर्णांक b53_चयन_get_reset_gpio(काष्ठा b53_device *dev)
अणु
	क्रमागत bcm47xx_board board = bcm47xx_board_get();

	चयन (board) अणु
	हाल BCM47XX_BOARD_LINKSYS_WRT300NV11:
	हाल BCM47XX_BOARD_LINKSYS_WRT310NV1:
		वापस 8;
	शेष:
		वापस bcm47xx_nvram_gpio_pin("robo_reset");
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक b53_चयन_get_reset_gpio(काष्ठा b53_device *dev)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

/* Exported functions towards other drivers */
व्योम b53_imp_vlan_setup(काष्ठा dsa_चयन *ds, पूर्णांक cpu_port);
पूर्णांक b53_configure_vlan(काष्ठा dsa_चयन *ds);
व्योम b53_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
		     uपूर्णांक8_t *data);
व्योम b53_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data);
पूर्णांक b53_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);
व्योम b53_get_ethtool_phy_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data);
पूर्णांक b53_br_join(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *bridge);
व्योम b53_br_leave(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा net_device *bridge);
व्योम b53_br_set_stp_state(काष्ठा dsa_चयन *ds, पूर्णांक port, u8 state);
व्योम b53_br_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port);
पूर्णांक b53_br_flags_pre(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     काष्ठा चयनdev_brport_flags flags,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक b53_br_flags(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 काष्ठा चयनdev_brport_flags flags,
		 काष्ठा netlink_ext_ack *extack);
पूर्णांक b53_set_mrouter(काष्ठा dsa_चयन *ds, पूर्णांक port, bool mrouter,
		    काष्ठा netlink_ext_ack *extack);
पूर्णांक b53_setup_devlink_resources(काष्ठा dsa_चयन *ds);
व्योम b53_port_event(काष्ठा dsa_चयन *ds, पूर्णांक port);
व्योम b53_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
			  अचिन्हित दीर्घ *supported,
			  काष्ठा phylink_link_state *state);
पूर्णांक b53_phylink_mac_link_state(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा phylink_link_state *state);
व्योम b53_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
			    अचिन्हित पूर्णांक mode,
			    स्थिर काष्ठा phylink_link_state *state);
व्योम b53_phylink_mac_an_restart(काष्ठा dsa_चयन *ds, पूर्णांक port);
व्योम b53_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       अचिन्हित पूर्णांक mode,
			       phy_पूर्णांकerface_t पूर्णांकerface);
व्योम b53_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     अचिन्हित पूर्णांक mode,
			     phy_पूर्णांकerface_t पूर्णांकerface,
			     काष्ठा phy_device *phydev,
			     पूर्णांक speed, पूर्णांक duplex,
			     bool tx_छोड़ो, bool rx_छोड़ो);
पूर्णांक b53_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
		       काष्ठा netlink_ext_ack *extack);
पूर्णांक b53_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		 काष्ठा netlink_ext_ack *extack);
पूर्णांक b53_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
पूर्णांक b53_fdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक b53_fdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर अचिन्हित अक्षर *addr, u16 vid);
पूर्णांक b53_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port,
		 dsa_fdb_dump_cb_t *cb, व्योम *data);
पूर्णांक b53_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक b53_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक b53_mirror_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		   काष्ठा dsa_mall_mirror_tc_entry *mirror, bool ingress);
क्रमागत dsa_tag_protocol b53_get_tag_protocol(काष्ठा dsa_चयन *ds, पूर्णांक port,
					   क्रमागत dsa_tag_protocol mprot);
व्योम b53_mirror_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		    काष्ठा dsa_mall_mirror_tc_entry *mirror);
पूर्णांक b53_enable_port(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy);
व्योम b53_disable_port(काष्ठा dsa_चयन *ds, पूर्णांक port);
व्योम b53_brcm_hdr_setup(काष्ठा dsa_चयन *ds, पूर्णांक port);
व्योम b53_eee_enable_set(काष्ठा dsa_चयन *ds, पूर्णांक port, bool enable);
पूर्णांक b53_eee_init(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy);
पूर्णांक b53_get_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *e);
पूर्णांक b53_set_mac_eee(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा ethtool_eee *e);

#पूर्ण_अगर
