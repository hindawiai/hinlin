<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Realtek SMI पूर्णांकerface driver defines
 *
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 * Copyright (C) 2009-2010 Gabor Juhos <juhosg@खोलोwrt.org>
 */

#अगर_अघोषित _REALTEK_SMI_H
#घोषणा _REALTEK_SMI_H

#समावेश <linux/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <net/dsa.h>

काष्ठा realtek_smi_ops;
काष्ठा dentry;
काष्ठा inode;
काष्ठा file;

काष्ठा rtl8366_mib_counter अणु
	अचिन्हित पूर्णांक	base;
	अचिन्हित पूर्णांक	offset;
	अचिन्हित पूर्णांक	length;
	स्थिर अक्षर	*name;
पूर्ण;

/**
 * काष्ठा rtl8366_vlan_mc - Virtual LAN member configuration
 */
काष्ठा rtl8366_vlan_mc अणु
	u16	vid;
	u16	untag;
	u16	member;
	u8	fid;
	u8	priority;
पूर्ण;

काष्ठा rtl8366_vlan_4k अणु
	u16	vid;
	u16	untag;
	u16	member;
	u8	fid;
पूर्ण;

काष्ठा realtek_smi अणु
	काष्ठा device		*dev;
	काष्ठा gpio_desc	*reset;
	काष्ठा gpio_desc	*mdc;
	काष्ठा gpio_desc	*mdio;
	काष्ठा regmap		*map;
	काष्ठा mii_bus		*slave_mii_bus;

	अचिन्हित पूर्णांक		clk_delay;
	u8			cmd_पढ़ो;
	u8			cmd_ग_लिखो;
	spinlock_t		lock; /* Locks around command ग_लिखोs */
	काष्ठा dsa_चयन	*ds;
	काष्ठा irq_करोमुख्य	*irqकरोमुख्य;
	bool			leds_disabled;

	अचिन्हित पूर्णांक		cpu_port;
	अचिन्हित पूर्णांक		num_ports;
	अचिन्हित पूर्णांक		num_vlan_mc;
	अचिन्हित पूर्णांक		num_mib_counters;
	काष्ठा rtl8366_mib_counter *mib_counters;

	स्थिर काष्ठा realtek_smi_ops *ops;

	पूर्णांक			vlan_enabled;
	पूर्णांक			vlan4k_enabled;

	अक्षर			buf[4096];
	व्योम			*chip_data; /* Per-chip extra variant data */
पूर्ण;

/**
 * काष्ठा realtek_smi_ops - vtable क्रम the per-SMI-chiptype operations
 * @detect: detects the chiptype
 */
काष्ठा realtek_smi_ops अणु
	पूर्णांक	(*detect)(काष्ठा realtek_smi *smi);
	पूर्णांक	(*reset_chip)(काष्ठा realtek_smi *smi);
	पूर्णांक	(*setup)(काष्ठा realtek_smi *smi);
	व्योम	(*cleanup)(काष्ठा realtek_smi *smi);
	पूर्णांक	(*get_mib_counter)(काष्ठा realtek_smi *smi,
				   पूर्णांक port,
				   काष्ठा rtl8366_mib_counter *mib,
				   u64 *mibvalue);
	पूर्णांक	(*get_vlan_mc)(काष्ठा realtek_smi *smi, u32 index,
			       काष्ठा rtl8366_vlan_mc *vlanmc);
	पूर्णांक	(*set_vlan_mc)(काष्ठा realtek_smi *smi, u32 index,
			       स्थिर काष्ठा rtl8366_vlan_mc *vlanmc);
	पूर्णांक	(*get_vlan_4k)(काष्ठा realtek_smi *smi, u32 vid,
			       काष्ठा rtl8366_vlan_4k *vlan4k);
	पूर्णांक	(*set_vlan_4k)(काष्ठा realtek_smi *smi,
			       स्थिर काष्ठा rtl8366_vlan_4k *vlan4k);
	पूर्णांक	(*get_mc_index)(काष्ठा realtek_smi *smi, पूर्णांक port, पूर्णांक *val);
	पूर्णांक	(*set_mc_index)(काष्ठा realtek_smi *smi, पूर्णांक port, पूर्णांक index);
	bool	(*is_vlan_valid)(काष्ठा realtek_smi *smi, अचिन्हित पूर्णांक vlan);
	पूर्णांक	(*enable_vlan)(काष्ठा realtek_smi *smi, bool enable);
	पूर्णांक	(*enable_vlan4k)(काष्ठा realtek_smi *smi, bool enable);
	पूर्णांक	(*enable_port)(काष्ठा realtek_smi *smi, पूर्णांक port, bool enable);
	पूर्णांक	(*phy_पढ़ो)(काष्ठा realtek_smi *smi, पूर्णांक phy, पूर्णांक regnum);
	पूर्णांक	(*phy_ग_लिखो)(काष्ठा realtek_smi *smi, पूर्णांक phy, पूर्णांक regnum,
			     u16 val);
पूर्ण;

काष्ठा realtek_smi_variant अणु
	स्थिर काष्ठा dsa_चयन_ops *ds_ops;
	स्थिर काष्ठा realtek_smi_ops *ops;
	अचिन्हित पूर्णांक clk_delay;
	u8 cmd_पढ़ो;
	u8 cmd_ग_लिखो;
	माप_प्रकार chip_data_sz;
पूर्ण;

/* SMI core calls */
पूर्णांक realtek_smi_ग_लिखो_reg_noack(काष्ठा realtek_smi *smi, u32 addr,
				u32 data);
पूर्णांक realtek_smi_setup_mdio(काष्ठा realtek_smi *smi);

/* RTL8366 library helpers */
पूर्णांक rtl8366_mc_is_used(काष्ठा realtek_smi *smi, पूर्णांक mc_index, पूर्णांक *used);
पूर्णांक rtl8366_set_vlan(काष्ठा realtek_smi *smi, पूर्णांक vid, u32 member,
		     u32 untag, u32 fid);
पूर्णांक rtl8366_set_pvid(काष्ठा realtek_smi *smi, अचिन्हित पूर्णांक port,
		     अचिन्हित पूर्णांक vid);
पूर्णांक rtl8366_enable_vlan4k(काष्ठा realtek_smi *smi, bool enable);
पूर्णांक rtl8366_enable_vlan(काष्ठा realtek_smi *smi, bool enable);
पूर्णांक rtl8366_reset_vlan(काष्ठा realtek_smi *smi);
पूर्णांक rtl8366_init_vlan(काष्ठा realtek_smi *smi);
पूर्णांक rtl8366_vlan_filtering(काष्ठा dsa_चयन *ds, पूर्णांक port, bool vlan_filtering,
			   काष्ठा netlink_ext_ack *extack);
पूर्णांक rtl8366_vlan_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक rtl8366_vlan_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
व्योम rtl8366_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port, u32 stringset,
			 uपूर्णांक8_t *data);
पूर्णांक rtl8366_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);
व्योम rtl8366_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *data);

बाह्य स्थिर काष्ठा realtek_smi_variant rtl8366rb_variant;

#पूर्ण_अगर /*  _REALTEK_SMI_H */
