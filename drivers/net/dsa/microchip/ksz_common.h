<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Microchip चयन driver common header
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#अगर_अघोषित __KSZ_COMMON_H
#घोषणा __KSZ_COMMON_H

#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mutex.h>
#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>
#समावेश <net/dsa.h>

काष्ठा vlan_table अणु
	u32 table[3];
पूर्ण;

काष्ठा ksz_port_mib अणु
	काष्ठा mutex cnt_mutex;		/* काष्ठाure access */
	u8 cnt_ptr;
	u64 *counters;
पूर्ण;

काष्ठा ksz_port अणु
	u16 member;
	u16 vid_member;
	पूर्णांक stp_state;
	काष्ठा phy_device phydev;

	u32 on:1;			/* port is not disabled by hardware */
	u32 phy:1;			/* port has a PHY */
	u32 fiber:1;			/* port is fiber */
	u32 sgmii:1;			/* port is SGMII */
	u32 क्रमce:1;
	u32 पढ़ो:1;			/* पढ़ो MIB counters in background */
	u32 मुक्तze:1;			/* MIB counter मुक्तze is enabled */

	काष्ठा ksz_port_mib mib;
	phy_पूर्णांकerface_t पूर्णांकerface;
पूर्ण;

काष्ठा ksz_device अणु
	काष्ठा dsa_चयन *ds;
	काष्ठा ksz_platक्रमm_data *pdata;
	स्थिर अक्षर *name;

	काष्ठा mutex dev_mutex;		/* device access */
	काष्ठा mutex regmap_mutex;	/* regmap access */
	काष्ठा mutex alu_mutex;		/* ALU access */
	काष्ठा mutex vlan_mutex;	/* vlan access */
	स्थिर काष्ठा ksz_dev_ops *dev_ops;

	काष्ठा device *dev;
	काष्ठा regmap *regmap[3];

	व्योम *priv;

	काष्ठा gpio_desc *reset_gpio;	/* Optional reset GPIO */

	/* chip specअगरic data */
	u32 chip_id;
	पूर्णांक num_vlans;
	पूर्णांक num_alus;
	पूर्णांक num_अटलs;
	पूर्णांक cpu_port;			/* port connected to CPU */
	पूर्णांक cpu_ports;			/* port biपंचांगap can be cpu port */
	पूर्णांक phy_port_cnt;
	पूर्णांक port_cnt;
	u8 reg_mib_cnt;
	पूर्णांक mib_cnt;
	स्थिर काष्ठा mib_names *mib_names;
	phy_पूर्णांकerface_t compat_पूर्णांकerface;
	u32 regs_size;
	bool phy_errata_9477;
	bool synclko_125;

	काष्ठा vlan_table *vlan_cache;

	काष्ठा ksz_port *ports;
	काष्ठा delayed_work mib_पढ़ो;
	अचिन्हित दीर्घ mib_पढ़ो_पूर्णांकerval;
	u16 br_member;
	u16 member;
	u16 mirror_rx;
	u16 mirror_tx;
	u32 features;			/* chip specअगरic features */
	u32 overrides;			/* chip functions set by user */
	u16 host_mask;
	u16 port_mask;
पूर्ण;

काष्ठा alu_काष्ठा अणु
	/* entry 1 */
	u8	is_अटल:1;
	u8	is_src_filter:1;
	u8	is_dst_filter:1;
	u8	prio_age:3;
	u32	_reserv_0_1:23;
	u8	mstp:3;
	/* entry 2 */
	u8	is_override:1;
	u8	is_use_fid:1;
	u32	_reserv_1_1:23;
	u8	port_क्रमward:7;
	/* entry 3 & 4*/
	u32	_reserv_2_1:9;
	u8	fid:7;
	u8	mac[ETH_ALEN];
पूर्ण;

काष्ठा ksz_dev_ops अणु
	u32 (*get_port_addr)(पूर्णांक port, पूर्णांक offset);
	व्योम (*cfg_port_member)(काष्ठा ksz_device *dev, पूर्णांक port, u8 member);
	व्योम (*flush_dyn_mac_table)(काष्ठा ksz_device *dev, पूर्णांक port);
	व्योम (*port_cleanup)(काष्ठा ksz_device *dev, पूर्णांक port);
	व्योम (*port_setup)(काष्ठा ksz_device *dev, पूर्णांक port, bool cpu_port);
	व्योम (*r_phy)(काष्ठा ksz_device *dev, u16 phy, u16 reg, u16 *val);
	व्योम (*w_phy)(काष्ठा ksz_device *dev, u16 phy, u16 reg, u16 val);
	पूर्णांक (*r_dyn_mac_table)(काष्ठा ksz_device *dev, u16 addr, u8 *mac_addr,
			       u8 *fid, u8 *src_port, u8 *बारtamp,
			       u16 *entries);
	पूर्णांक (*r_sta_mac_table)(काष्ठा ksz_device *dev, u16 addr,
			       काष्ठा alu_काष्ठा *alu);
	व्योम (*w_sta_mac_table)(काष्ठा ksz_device *dev, u16 addr,
				काष्ठा alu_काष्ठा *alu);
	व्योम (*r_mib_cnt)(काष्ठा ksz_device *dev, पूर्णांक port, u16 addr,
			  u64 *cnt);
	व्योम (*r_mib_pkt)(काष्ठा ksz_device *dev, पूर्णांक port, u16 addr,
			  u64 *dropped, u64 *cnt);
	व्योम (*मुक्तze_mib)(काष्ठा ksz_device *dev, पूर्णांक port, bool मुक्तze);
	व्योम (*port_init_cnt)(काष्ठा ksz_device *dev, पूर्णांक port);
	पूर्णांक (*shutकरोwn)(काष्ठा ksz_device *dev);
	पूर्णांक (*detect)(काष्ठा ksz_device *dev);
	पूर्णांक (*init)(काष्ठा ksz_device *dev);
	व्योम (*निकास)(काष्ठा ksz_device *dev);
पूर्ण;

काष्ठा ksz_device *ksz_चयन_alloc(काष्ठा device *base, व्योम *priv);
पूर्णांक ksz_चयन_रेजिस्टर(काष्ठा ksz_device *dev,
			स्थिर काष्ठा ksz_dev_ops *ops);
व्योम ksz_चयन_हटाओ(काष्ठा ksz_device *dev);

पूर्णांक ksz8_चयन_रेजिस्टर(काष्ठा ksz_device *dev);
पूर्णांक ksz9477_चयन_रेजिस्टर(काष्ठा ksz_device *dev);

व्योम ksz_update_port_member(काष्ठा ksz_device *dev, पूर्णांक port);
व्योम ksz_init_mib_समयr(काष्ठा ksz_device *dev);

/* Common DSA access functions */

पूर्णांक ksz_phy_पढ़ो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg);
पूर्णांक ksz_phy_ग_लिखो16(काष्ठा dsa_चयन *ds, पूर्णांक addr, पूर्णांक reg, u16 val);
व्योम ksz_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port, अचिन्हित पूर्णांक mode,
		       phy_पूर्णांकerface_t पूर्णांकerface);
पूर्णांक ksz_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);
व्योम ksz_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port, uपूर्णांक64_t *buf);
पूर्णांक ksz_port_bridge_join(काष्ठा dsa_चयन *ds, पूर्णांक port,
			 काष्ठा net_device *br);
व्योम ksz_port_bridge_leave(काष्ठा dsa_चयन *ds, पूर्णांक port,
			   काष्ठा net_device *br);
व्योम ksz_port_fast_age(काष्ठा dsa_चयन *ds, पूर्णांक port);
पूर्णांक ksz_port_fdb_dump(काष्ठा dsa_चयन *ds, पूर्णांक port, dsa_fdb_dump_cb_t *cb,
		      व्योम *data);
पूर्णांक ksz_port_mdb_add(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक ksz_port_mdb_del(काष्ठा dsa_चयन *ds, पूर्णांक port,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक ksz_enable_port(काष्ठा dsa_चयन *ds, पूर्णांक port, काष्ठा phy_device *phy);

/* Common रेजिस्टर access functions */

अटल अंतरभूत पूर्णांक ksz_पढ़ो8(काष्ठा ksz_device *dev, u32 reg, u8 *val)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret = regmap_पढ़ो(dev->regmap[0], reg, &value);

	*val = value;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ksz_पढ़ो16(काष्ठा ksz_device *dev, u32 reg, u16 *val)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret = regmap_पढ़ो(dev->regmap[1], reg, &value);

	*val = value;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ksz_पढ़ो32(काष्ठा ksz_device *dev, u32 reg, u32 *val)
अणु
	अचिन्हित पूर्णांक value;
	पूर्णांक ret = regmap_पढ़ो(dev->regmap[2], reg, &value);

	*val = value;
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ksz_पढ़ो64(काष्ठा ksz_device *dev, u32 reg, u64 *val)
अणु
	u32 value[2];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(dev->regmap[2], reg, value, 2);
	अगर (!ret) अणु
		/* Ick! ToDo: Add 64bit R/W to regmap on 32bit प्रणालीs */
		value[0] = swab32(value[0]);
		value[1] = swab32(value[1]);
		*val = swab64((u64)*value);
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ksz_ग_लिखो8(काष्ठा ksz_device *dev, u32 reg, u8 value)
अणु
	वापस regmap_ग_लिखो(dev->regmap[0], reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक ksz_ग_लिखो16(काष्ठा ksz_device *dev, u32 reg, u16 value)
अणु
	वापस regmap_ग_लिखो(dev->regmap[1], reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक ksz_ग_लिखो32(काष्ठा ksz_device *dev, u32 reg, u32 value)
अणु
	वापस regmap_ग_लिखो(dev->regmap[2], reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक ksz_ग_लिखो64(काष्ठा ksz_device *dev, u32 reg, u64 value)
अणु
	u32 val[2];

	/* Ick! ToDo: Add 64bit R/W to regmap on 32bit प्रणालीs */
	value = swab64(value);
	val[0] = swab32(value & 0xffffffffULL);
	val[1] = swab32(value >> 32ULL);

	वापस regmap_bulk_ग_लिखो(dev->regmap[2], reg, val, 2);
पूर्ण

अटल अंतरभूत व्योम ksz_pपढ़ो8(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
			      u8 *data)
अणु
	ksz_पढ़ो8(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_pपढ़ो16(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
			       u16 *data)
अणु
	ksz_पढ़ो16(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_pपढ़ो32(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
			       u32 *data)
अणु
	ksz_पढ़ो32(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_pग_लिखो8(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
			       u8 data)
अणु
	ksz_ग_लिखो8(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_pग_लिखो16(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
				u16 data)
अणु
	ksz_ग_लिखो16(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_pग_लिखो32(काष्ठा ksz_device *dev, पूर्णांक port, पूर्णांक offset,
				u32 data)
अणु
	ksz_ग_लिखो32(dev, dev->dev_ops->get_port_addr(port, offset), data);
पूर्ण

अटल अंतरभूत व्योम ksz_regmap_lock(व्योम *__mtx)
अणु
	काष्ठा mutex *mtx = __mtx;
	mutex_lock(mtx);
पूर्ण

अटल अंतरभूत व्योम ksz_regmap_unlock(व्योम *__mtx)
अणु
	काष्ठा mutex *mtx = __mtx;
	mutex_unlock(mtx);
पूर्ण

/* Regmap tables generation */
#घोषणा KSZ_SPI_OP_RD		3
#घोषणा KSZ_SPI_OP_WR		2

#घोषणा swabnot_used(x)		0

#घोषणा KSZ_SPI_OP_FLAG_MASK(opcode, swp, regbits, regpad)		\
	swab##swp((opcode) << ((regbits) + (regpad)))

#घोषणा KSZ_REGMAP_ENTRY(width, swp, regbits, regpad, regalign)		\
	अणु								\
		.name = #width,						\
		.val_bits = (width),					\
		.reg_stride = 1,					\
		.reg_bits = (regbits) + (regalign),			\
		.pad_bits = (regpad),					\
		.max_रेजिस्टर = BIT(regbits) - 1,			\
		.cache_type = REGCACHE_NONE,				\
		.पढ़ो_flag_mask =					\
			KSZ_SPI_OP_FLAG_MASK(KSZ_SPI_OP_RD, swp,	\
					     regbits, regpad),		\
		.ग_लिखो_flag_mask =					\
			KSZ_SPI_OP_FLAG_MASK(KSZ_SPI_OP_WR, swp,	\
					     regbits, regpad),		\
		.lock = ksz_regmap_lock,				\
		.unlock = ksz_regmap_unlock,				\
		.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,			\
		.val_क्रमmat_endian = REGMAP_ENDIAN_BIG			\
	पूर्ण

#घोषणा KSZ_REGMAP_TABLE(ksz, swp, regbits, regpad, regalign)		\
	अटल स्थिर काष्ठा regmap_config ksz##_regmap_config[] = अणु	\
		KSZ_REGMAP_ENTRY(8, swp, (regbits), (regpad), (regalign)), \
		KSZ_REGMAP_ENTRY(16, swp, (regbits), (regpad), (regalign)), \
		KSZ_REGMAP_ENTRY(32, swp, (regbits), (regpad), (regalign)), \
	पूर्ण

#पूर्ण_अगर
