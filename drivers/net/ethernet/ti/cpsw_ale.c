<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments N-Port Ethernet Switch Address Lookup Engine
 *
 * Copyright (C) 2012 Texas Instruments
 *
 */
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/etherdevice.h>

#समावेश "cpsw_ale.h"

#घोषणा BITMASK(bits)		(BIT(bits) - 1)

#घोषणा ALE_VERSION_MAJOR(rev, mask) (((rev) >> 8) & (mask))
#घोषणा ALE_VERSION_MINOR(rev)	(rev & 0xff)
#घोषणा ALE_VERSION_1R3		0x0103
#घोषणा ALE_VERSION_1R4		0x0104

/* ALE Registers */
#घोषणा ALE_IDVER		0x00
#घोषणा ALE_STATUS		0x04
#घोषणा ALE_CONTROL		0x08
#घोषणा ALE_PRESCALE		0x10
#घोषणा ALE_AGING_TIMER		0x14
#घोषणा ALE_UNKNOWNVLAN		0x18
#घोषणा ALE_TABLE_CONTROL	0x20
#घोषणा ALE_TABLE		0x34
#घोषणा ALE_PORTCTL		0x40

/* ALE NetCP NU चयन specअगरic Registers */
#घोषणा ALE_UNKNOWNVLAN_MEMBER			0x90
#घोषणा ALE_UNKNOWNVLAN_UNREG_MCAST_FLOOD	0x94
#घोषणा ALE_UNKNOWNVLAN_REG_MCAST_FLOOD		0x98
#घोषणा ALE_UNKNOWNVLAN_FORCE_UNTAG_EGRESS	0x9C
#घोषणा ALE_VLAN_MASK_MUX(reg)			(0xc0 + (0x4 * (reg)))

#घोषणा AM65_CPSW_ALE_THREAD_DEF_REG 0x134

/* ALE_AGING_TIMER */
#घोषणा ALE_AGING_TIMER_MASK	GENMASK(23, 0)

/**
 * काष्ठा ale_entry_fld - The ALE tbl entry field description
 * @start_bit: field start bit
 * @num_bits: field bit length
 * @flags: field flags
 */
काष्ठा ale_entry_fld अणु
	u8 start_bit;
	u8 num_bits;
	u8 flags;
पूर्ण;

क्रमागत अणु
	CPSW_ALE_F_STATUS_REG = BIT(0), /* Status रेजिस्टर present */
	CPSW_ALE_F_HW_AUTOAGING = BIT(1), /* HW स्वतः aging */

	CPSW_ALE_F_COUNT
पूर्ण;

/**
 * काष्ठा ale_dev_id - The ALE version/SoC specअगरic configuration
 * @dev_id: ALE version/SoC id
 * @features: features supported by ALE
 * @tbl_entries: number of ALE entries
 * @major_ver_mask: mask of ALE Major Version Value in ALE_IDVER reg.
 * @nu_चयन_ale: NU Switch ALE
 * @vlan_entry_tbl: ALE vlan entry fields description tbl
 */
काष्ठा cpsw_ale_dev_id अणु
	स्थिर अक्षर *dev_id;
	u32 features;
	u32 tbl_entries;
	u32 major_ver_mask;
	bool nu_चयन_ale;
	स्थिर काष्ठा ale_entry_fld *vlan_entry_tbl;
पूर्ण;

#घोषणा ALE_TABLE_WRITE		BIT(31)

#घोषणा ALE_TYPE_FREE			0
#घोषणा ALE_TYPE_ADDR			1
#घोषणा ALE_TYPE_VLAN			2
#घोषणा ALE_TYPE_VLAN_ADDR		3

#घोषणा ALE_UCAST_PERSISTANT		0
#घोषणा ALE_UCAST_UNTOUCHED		1
#घोषणा ALE_UCAST_OUI			2
#घोषणा ALE_UCAST_TOUCHED		3

#घोषणा ALE_TABLE_SIZE_MULTIPLIER	1024
#घोषणा ALE_STATUS_SIZE_MASK		0x1f

अटल अंतरभूत पूर्णांक cpsw_ale_get_field(u32 *ale_entry, u32 start, u32 bits)
अणु
	पूर्णांक idx;

	idx    = start / 32;
	start -= idx * 32;
	idx    = 2 - idx; /* flip */
	वापस (ale_entry[idx] >> start) & BITMASK(bits);
पूर्ण

अटल अंतरभूत व्योम cpsw_ale_set_field(u32 *ale_entry, u32 start, u32 bits,
				      u32 value)
अणु
	पूर्णांक idx;

	value &= BITMASK(bits);
	idx    = start / 32;
	start -= idx * 32;
	idx    = 2 - idx; /* flip */
	ale_entry[idx] &= ~(BITMASK(bits) << start);
	ale_entry[idx] |=  (value << start);
पूर्ण

#घोषणा DEFINE_ALE_FIELD(name, start, bits)				\
अटल अंतरभूत पूर्णांक cpsw_ale_get_##name(u32 *ale_entry)			\
अणु									\
	वापस cpsw_ale_get_field(ale_entry, start, bits);		\
पूर्ण									\
अटल अंतरभूत व्योम cpsw_ale_set_##name(u32 *ale_entry, u32 value)	\
अणु									\
	cpsw_ale_set_field(ale_entry, start, bits, value);		\
पूर्ण

#घोषणा DEFINE_ALE_FIELD1(name, start)					\
अटल अंतरभूत पूर्णांक cpsw_ale_get_##name(u32 *ale_entry, u32 bits)		\
अणु									\
	वापस cpsw_ale_get_field(ale_entry, start, bits);		\
पूर्ण									\
अटल अंतरभूत व्योम cpsw_ale_set_##name(u32 *ale_entry, u32 value,	\
		u32 bits)						\
अणु									\
	cpsw_ale_set_field(ale_entry, start, bits, value);		\
पूर्ण

क्रमागत अणु
	ALE_ENT_VID_MEMBER_LIST = 0,
	ALE_ENT_VID_UNREG_MCAST_MSK,
	ALE_ENT_VID_REG_MCAST_MSK,
	ALE_ENT_VID_FORCE_UNTAGGED_MSK,
	ALE_ENT_VID_UNREG_MCAST_IDX,
	ALE_ENT_VID_REG_MCAST_IDX,
	ALE_ENT_VID_LAST,
पूर्ण;

#घोषणा ALE_FLD_ALLOWED			BIT(0)
#घोषणा ALE_FLD_SIZE_PORT_MASK_BITS	BIT(1)
#घोषणा ALE_FLD_SIZE_PORT_NUM_BITS	BIT(2)

#घोषणा ALE_ENTRY_FLD(id, start, bits)	\
[id] = अणु				\
	.start_bit = start,		\
	.num_bits = bits,		\
	.flags = ALE_FLD_ALLOWED,	\
पूर्ण

#घोषणा ALE_ENTRY_FLD_DYN_MSK_SIZE(id, start)	\
[id] = अणु					\
	.start_bit = start,			\
	.num_bits = 0,				\
	.flags = ALE_FLD_ALLOWED |		\
		 ALE_FLD_SIZE_PORT_MASK_BITS,	\
पूर्ण

/* dm814x, am3/am4/am5, k2hk */
अटल स्थिर काष्ठा ale_entry_fld vlan_entry_cpsw[ALE_ENT_VID_LAST] = अणु
	ALE_ENTRY_FLD(ALE_ENT_VID_MEMBER_LIST, 0, 3),
	ALE_ENTRY_FLD(ALE_ENT_VID_UNREG_MCAST_MSK, 8, 3),
	ALE_ENTRY_FLD(ALE_ENT_VID_REG_MCAST_MSK, 16, 3),
	ALE_ENTRY_FLD(ALE_ENT_VID_FORCE_UNTAGGED_MSK, 24, 3),
पूर्ण;

/* k2e/k2l, k3 am65/j721e cpsw2g  */
अटल स्थिर काष्ठा ale_entry_fld vlan_entry_nu[ALE_ENT_VID_LAST] = अणु
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_MEMBER_LIST, 0),
	ALE_ENTRY_FLD(ALE_ENT_VID_UNREG_MCAST_IDX, 20, 3),
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_FORCE_UNTAGGED_MSK, 24),
	ALE_ENTRY_FLD(ALE_ENT_VID_REG_MCAST_IDX, 44, 3),
पूर्ण;

/* K3 j721e/j7200 cpsw9g/5g, am64x cpsw3g  */
अटल स्थिर काष्ठा ale_entry_fld vlan_entry_k3_cpswxg[] = अणु
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_MEMBER_LIST, 0),
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_UNREG_MCAST_MSK, 12),
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_FORCE_UNTAGGED_MSK, 24),
	ALE_ENTRY_FLD_DYN_MSK_SIZE(ALE_ENT_VID_REG_MCAST_MSK, 36),
पूर्ण;

DEFINE_ALE_FIELD(entry_type,		60,	2)
DEFINE_ALE_FIELD(vlan_id,		48,	12)
DEFINE_ALE_FIELD(mcast_state,		62,	2)
DEFINE_ALE_FIELD1(port_mask,		66)
DEFINE_ALE_FIELD(super,			65,	1)
DEFINE_ALE_FIELD(ucast_type,		62,     2)
DEFINE_ALE_FIELD1(port_num,		66)
DEFINE_ALE_FIELD(blocked,		65,     1)
DEFINE_ALE_FIELD(secure,		64,     1)
DEFINE_ALE_FIELD(mcast,			40,	1)

#घोषणा NU_VLAN_UNREG_MCAST_IDX	1

अटल पूर्णांक cpsw_ale_entry_get_fld(काष्ठा cpsw_ale *ale,
				  u32 *ale_entry,
				  स्थिर काष्ठा ale_entry_fld *entry_tbl,
				  पूर्णांक fld_id)
अणु
	स्थिर काष्ठा ale_entry_fld *entry_fld;
	u32 bits;

	अगर (!ale || !ale_entry)
		वापस -EINVAL;

	entry_fld = &entry_tbl[fld_id];
	अगर (!(entry_fld->flags & ALE_FLD_ALLOWED)) अणु
		dev_err(ale->params.dev, "get: wrong ale fld id %d\n", fld_id);
		वापस -ENOENT;
	पूर्ण

	bits = entry_fld->num_bits;
	अगर (entry_fld->flags & ALE_FLD_SIZE_PORT_MASK_BITS)
		bits = ale->port_mask_bits;

	वापस cpsw_ale_get_field(ale_entry, entry_fld->start_bit, bits);
पूर्ण

अटल व्योम cpsw_ale_entry_set_fld(काष्ठा cpsw_ale *ale,
				   u32 *ale_entry,
				   स्थिर काष्ठा ale_entry_fld *entry_tbl,
				   पूर्णांक fld_id,
				   u32 value)
अणु
	स्थिर काष्ठा ale_entry_fld *entry_fld;
	u32 bits;

	अगर (!ale || !ale_entry)
		वापस;

	entry_fld = &entry_tbl[fld_id];
	अगर (!(entry_fld->flags & ALE_FLD_ALLOWED)) अणु
		dev_err(ale->params.dev, "set: wrong ale fld id %d\n", fld_id);
		वापस;
	पूर्ण

	bits = entry_fld->num_bits;
	अगर (entry_fld->flags & ALE_FLD_SIZE_PORT_MASK_BITS)
		bits = ale->port_mask_bits;

	cpsw_ale_set_field(ale_entry, entry_fld->start_bit, bits, value);
पूर्ण

अटल पूर्णांक cpsw_ale_vlan_get_fld(काष्ठा cpsw_ale *ale,
				 u32 *ale_entry,
				 पूर्णांक fld_id)
अणु
	वापस cpsw_ale_entry_get_fld(ale, ale_entry,
				      ale->vlan_entry_tbl, fld_id);
पूर्ण

अटल व्योम cpsw_ale_vlan_set_fld(काष्ठा cpsw_ale *ale,
				  u32 *ale_entry,
				  पूर्णांक fld_id,
				  u32 value)
अणु
	cpsw_ale_entry_set_fld(ale, ale_entry,
			       ale->vlan_entry_tbl, fld_id, value);
पूर्ण

/* The MAC address field in the ALE entry cannot be macroized as above */
अटल अंतरभूत व्योम cpsw_ale_get_addr(u32 *ale_entry, u8 *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		addr[i] = cpsw_ale_get_field(ale_entry, 40 - 8*i, 8);
पूर्ण

अटल अंतरभूत व्योम cpsw_ale_set_addr(u32 *ale_entry, स्थिर u8 *addr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 6; i++)
		cpsw_ale_set_field(ale_entry, 40 - 8*i, 8, addr[i]);
पूर्ण

अटल पूर्णांक cpsw_ale_पढ़ो(काष्ठा cpsw_ale *ale, पूर्णांक idx, u32 *ale_entry)
अणु
	पूर्णांक i;

	WARN_ON(idx > ale->params.ale_entries);

	ग_लिखोl_relaxed(idx, ale->params.ale_regs + ALE_TABLE_CONTROL);

	क्रम (i = 0; i < ALE_ENTRY_WORDS; i++)
		ale_entry[i] = पढ़ोl_relaxed(ale->params.ale_regs +
					     ALE_TABLE + 4 * i);

	वापस idx;
पूर्ण

अटल पूर्णांक cpsw_ale_ग_लिखो(काष्ठा cpsw_ale *ale, पूर्णांक idx, u32 *ale_entry)
अणु
	पूर्णांक i;

	WARN_ON(idx > ale->params.ale_entries);

	क्रम (i = 0; i < ALE_ENTRY_WORDS; i++)
		ग_लिखोl_relaxed(ale_entry[i], ale->params.ale_regs +
			       ALE_TABLE + 4 * i);

	ग_लिखोl_relaxed(idx | ALE_TABLE_WRITE, ale->params.ale_regs +
		       ALE_TABLE_CONTROL);

	वापस idx;
पूर्ण

अटल पूर्णांक cpsw_ale_match_addr(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, u16 vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		u8 entry_addr[6];

		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type != ALE_TYPE_ADDR && type != ALE_TYPE_VLAN_ADDR)
			जारी;
		अगर (cpsw_ale_get_vlan_id(ale_entry) != vid)
			जारी;
		cpsw_ale_get_addr(ale_entry, entry_addr);
		अगर (ether_addr_equal(entry_addr, addr))
			वापस idx;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक cpsw_ale_match_vlan(काष्ठा cpsw_ale *ale, u16 vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type != ALE_TYPE_VLAN)
			जारी;
		अगर (cpsw_ale_get_vlan_id(ale_entry) == vid)
			वापस idx;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक cpsw_ale_match_मुक्त(काष्ठा cpsw_ale *ale)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type == ALE_TYPE_FREE)
			वापस idx;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक cpsw_ale_find_ageable(काष्ठा cpsw_ale *ale)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type != ALE_TYPE_ADDR && type != ALE_TYPE_VLAN_ADDR)
			जारी;
		अगर (cpsw_ale_get_mcast(ale_entry))
			जारी;
		type = cpsw_ale_get_ucast_type(ale_entry);
		अगर (type != ALE_UCAST_PERSISTANT &&
		    type != ALE_UCAST_OUI)
			वापस idx;
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल व्योम cpsw_ale_flush_mcast(काष्ठा cpsw_ale *ale, u32 *ale_entry,
				 पूर्णांक port_mask)
अणु
	पूर्णांक mask;

	mask = cpsw_ale_get_port_mask(ale_entry,
				      ale->port_mask_bits);
	अगर ((mask & port_mask) == 0)
		वापस; /* ports करोnt पूर्णांकersect, not पूर्णांकerested */
	mask &= ~port_mask;

	/* मुक्त अगर only reमुख्यing port is host port */
	अगर (mask)
		cpsw_ale_set_port_mask(ale_entry, mask,
				       ale->port_mask_bits);
	अन्यथा
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);
पूर्ण

पूर्णांक cpsw_ale_flush_multicast(काष्ठा cpsw_ale *ale, पूर्णांक port_mask, पूर्णांक vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक ret, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		ret = cpsw_ale_get_entry_type(ale_entry);
		अगर (ret != ALE_TYPE_ADDR && ret != ALE_TYPE_VLAN_ADDR)
			जारी;

		/* अगर vid passed is -1 then हटाओ all multicast entry from
		 * the table irrespective of vlan id, अगर a valid vlan id is
		 * passed then हटाओ only multicast added to that vlan id.
		 * अगर vlan id करोesn't match then move on to next entry.
		 */
		अगर (vid != -1 && cpsw_ale_get_vlan_id(ale_entry) != vid)
			जारी;

		अगर (cpsw_ale_get_mcast(ale_entry)) अणु
			u8 addr[6];

			अगर (cpsw_ale_get_super(ale_entry))
				जारी;

			cpsw_ale_get_addr(ale_entry, addr);
			अगर (!is_broadcast_ether_addr(addr))
				cpsw_ale_flush_mcast(ale, ale_entry, port_mask);
		पूर्ण

		cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम cpsw_ale_set_vlan_entry_type(u32 *ale_entry,
						पूर्णांक flags, u16 vid)
अणु
	अगर (flags & ALE_VLAN) अणु
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_VLAN_ADDR);
		cpsw_ale_set_vlan_id(ale_entry, vid);
	पूर्ण अन्यथा अणु
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_ADDR);
	पूर्ण
पूर्ण

पूर्णांक cpsw_ale_add_ucast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port,
		       पूर्णांक flags, u16 vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक idx;

	cpsw_ale_set_vlan_entry_type(ale_entry, flags, vid);

	cpsw_ale_set_addr(ale_entry, addr);
	cpsw_ale_set_ucast_type(ale_entry, ALE_UCAST_PERSISTANT);
	cpsw_ale_set_secure(ale_entry, (flags & ALE_SECURE) ? 1 : 0);
	cpsw_ale_set_blocked(ale_entry, (flags & ALE_BLOCKED) ? 1 : 0);
	cpsw_ale_set_port_num(ale_entry, port, ale->port_num_bits);

	idx = cpsw_ale_match_addr(ale, addr, (flags & ALE_VLAN) ? vid : 0);
	अगर (idx < 0)
		idx = cpsw_ale_match_मुक्त(ale);
	अगर (idx < 0)
		idx = cpsw_ale_find_ageable(ale);
	अगर (idx < 0)
		वापस -ENOMEM;

	cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_del_ucast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port,
		       पूर्णांक flags, u16 vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक idx;

	idx = cpsw_ale_match_addr(ale, addr, (flags & ALE_VLAN) ? vid : 0);
	अगर (idx < 0)
		वापस -ENOENT;

	cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);
	cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_add_mcast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port_mask,
		       पूर्णांक flags, u16 vid, पूर्णांक mcast_state)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक idx, mask;

	idx = cpsw_ale_match_addr(ale, addr, (flags & ALE_VLAN) ? vid : 0);
	अगर (idx >= 0)
		cpsw_ale_पढ़ो(ale, idx, ale_entry);

	cpsw_ale_set_vlan_entry_type(ale_entry, flags, vid);

	cpsw_ale_set_addr(ale_entry, addr);
	cpsw_ale_set_super(ale_entry, (flags & ALE_SUPER) ? 1 : 0);
	cpsw_ale_set_mcast_state(ale_entry, mcast_state);

	mask = cpsw_ale_get_port_mask(ale_entry,
				      ale->port_mask_bits);
	port_mask |= mask;
	cpsw_ale_set_port_mask(ale_entry, port_mask,
			       ale->port_mask_bits);

	अगर (idx < 0)
		idx = cpsw_ale_match_मुक्त(ale);
	अगर (idx < 0)
		idx = cpsw_ale_find_ageable(ale);
	अगर (idx < 0)
		वापस -ENOMEM;

	cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_del_mcast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port_mask,
		       पूर्णांक flags, u16 vid)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक mcast_members = 0;
	पूर्णांक idx;

	idx = cpsw_ale_match_addr(ale, addr, (flags & ALE_VLAN) ? vid : 0);
	अगर (idx < 0)
		वापस -ENOENT;

	cpsw_ale_पढ़ो(ale, idx, ale_entry);

	अगर (port_mask) अणु
		mcast_members = cpsw_ale_get_port_mask(ale_entry,
						       ale->port_mask_bits);
		mcast_members &= ~port_mask;
	पूर्ण

	अगर (mcast_members)
		cpsw_ale_set_port_mask(ale_entry, mcast_members,
				       ale->port_mask_bits);
	अन्यथा
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);

	cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	वापस 0;
पूर्ण

/* ALE NetCP NU चयन specअगरic vlan functions */
अटल व्योम cpsw_ale_set_vlan_mcast(काष्ठा cpsw_ale *ale, u32 *ale_entry,
				    पूर्णांक reg_mcast, पूर्णांक unreg_mcast)
अणु
	पूर्णांक idx;

	/* Set VLAN रेजिस्टरed multicast flood mask */
	idx = cpsw_ale_vlan_get_fld(ale, ale_entry,
				    ALE_ENT_VID_REG_MCAST_IDX);
	ग_लिखोl(reg_mcast, ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));

	/* Set VLAN unरेजिस्टरed multicast flood mask */
	idx = cpsw_ale_vlan_get_fld(ale, ale_entry,
				    ALE_ENT_VID_UNREG_MCAST_IDX);
	ग_लिखोl(unreg_mcast, ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));
पूर्ण

अटल व्योम cpsw_ale_set_vlan_untag(काष्ठा cpsw_ale *ale, u32 *ale_entry,
				    u16 vid, पूर्णांक untag_mask)
अणु
	cpsw_ale_vlan_set_fld(ale, ale_entry,
			      ALE_ENT_VID_FORCE_UNTAGGED_MSK,
			      untag_mask);
	अगर (untag_mask & ALE_PORT_HOST)
		biपंचांगap_set(ale->p0_untag_vid_mask, vid, 1);
	अन्यथा
		biपंचांगap_clear(ale->p0_untag_vid_mask, vid, 1);
पूर्ण

पूर्णांक cpsw_ale_add_vlan(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask, पूर्णांक untag,
		      पूर्णांक reg_mcast, पूर्णांक unreg_mcast)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक idx;

	idx = cpsw_ale_match_vlan(ale, vid);
	अगर (idx >= 0)
		cpsw_ale_पढ़ो(ale, idx, ale_entry);

	cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_VLAN);
	cpsw_ale_set_vlan_id(ale_entry, vid);
	cpsw_ale_set_vlan_untag(ale, ale_entry, vid, untag);

	अगर (!ale->params.nu_चयन_ale) अणु
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_REG_MCAST_MSK, reg_mcast);
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_UNREG_MCAST_MSK, unreg_mcast);
	पूर्ण अन्यथा अणु
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_UNREG_MCAST_IDX,
				      NU_VLAN_UNREG_MCAST_IDX);
		cpsw_ale_set_vlan_mcast(ale, ale_entry, reg_mcast, unreg_mcast);
	पूर्ण

	cpsw_ale_vlan_set_fld(ale, ale_entry,
			      ALE_ENT_VID_MEMBER_LIST, port_mask);

	अगर (idx < 0)
		idx = cpsw_ale_match_मुक्त(ale);
	अगर (idx < 0)
		idx = cpsw_ale_find_ageable(ale);
	अगर (idx < 0)
		वापस -ENOMEM;

	cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	वापस 0;
पूर्ण

अटल व्योम cpsw_ale_vlan_del_modअगरy_पूर्णांक(काष्ठा cpsw_ale *ale,  u32 *ale_entry,
					 u16 vid, पूर्णांक port_mask)
अणु
	पूर्णांक reg_mcast, unreg_mcast;
	पूर्णांक members, untag;

	members = cpsw_ale_vlan_get_fld(ale, ale_entry,
					ALE_ENT_VID_MEMBER_LIST);
	members &= ~port_mask;
	अगर (!members) अणु
		cpsw_ale_set_vlan_untag(ale, ale_entry, vid, 0);
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);
		वापस;
	पूर्ण

	untag = cpsw_ale_vlan_get_fld(ale, ale_entry,
				      ALE_ENT_VID_FORCE_UNTAGGED_MSK);
	reg_mcast = cpsw_ale_vlan_get_fld(ale, ale_entry,
					  ALE_ENT_VID_REG_MCAST_MSK);
	unreg_mcast = cpsw_ale_vlan_get_fld(ale, ale_entry,
					    ALE_ENT_VID_UNREG_MCAST_MSK);
	untag &= members;
	reg_mcast &= members;
	unreg_mcast &= members;

	cpsw_ale_set_vlan_untag(ale, ale_entry, vid, untag);

	अगर (!ale->params.nu_चयन_ale) अणु
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_REG_MCAST_MSK, reg_mcast);
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_UNREG_MCAST_MSK, unreg_mcast);
	पूर्ण अन्यथा अणु
		cpsw_ale_set_vlan_mcast(ale, ale_entry, reg_mcast,
					unreg_mcast);
	पूर्ण
	cpsw_ale_vlan_set_fld(ale, ale_entry,
			      ALE_ENT_VID_MEMBER_LIST, members);
पूर्ण

पूर्णांक cpsw_ale_vlan_del_modअगरy(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक idx;

	idx = cpsw_ale_match_vlan(ale, vid);
	अगर (idx < 0)
		वापस -ENOENT;

	cpsw_ale_पढ़ो(ale, idx, ale_entry);

	cpsw_ale_vlan_del_modअगरy_पूर्णांक(ale, ale_entry, vid, port_mask);
	cpsw_ale_ग_लिखो(ale, idx, ale_entry);

	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_del_vlan(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक members, idx;

	idx = cpsw_ale_match_vlan(ale, vid);
	अगर (idx < 0)
		वापस -ENOENT;

	cpsw_ale_पढ़ो(ale, idx, ale_entry);

	/* अगर !port_mask - क्रमce हटाओ VLAN (legacy).
	 * Check अगर there are other VLAN members ports
	 * अगर no - हटाओ VLAN.
	 * अगर yes it means same VLAN was added to >1 port in multi port mode, so
	 * हटाओ port_mask ports from VLAN ALE entry excluding Host port.
	 */
	members = cpsw_ale_vlan_get_fld(ale, ale_entry, ALE_ENT_VID_MEMBER_LIST);
	members &= ~port_mask;

	अगर (!port_mask || !members) अणु
		/* last port or क्रमce हटाओ - हटाओ VLAN */
		cpsw_ale_set_vlan_untag(ale, ale_entry, vid, 0);
		cpsw_ale_set_entry_type(ale_entry, ALE_TYPE_FREE);
	पूर्ण अन्यथा अणु
		port_mask &= ~ALE_PORT_HOST;
		cpsw_ale_vlan_del_modअगरy_पूर्णांक(ale, ale_entry, vid, port_mask);
	पूर्ण

	cpsw_ale_ग_लिखो(ale, idx, ale_entry);

	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_vlan_add_modअगरy(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask,
			     पूर्णांक untag_mask, पूर्णांक reg_mask, पूर्णांक unreg_mask)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS] = अणु0, 0, 0पूर्ण;
	पूर्णांक reg_mcast_members, unreg_mcast_members;
	पूर्णांक vlan_members, untag_members;
	पूर्णांक idx, ret = 0;

	idx = cpsw_ale_match_vlan(ale, vid);
	अगर (idx >= 0)
		cpsw_ale_पढ़ो(ale, idx, ale_entry);

	vlan_members = cpsw_ale_vlan_get_fld(ale, ale_entry,
					     ALE_ENT_VID_MEMBER_LIST);
	reg_mcast_members = cpsw_ale_vlan_get_fld(ale, ale_entry,
						  ALE_ENT_VID_REG_MCAST_MSK);
	unreg_mcast_members =
		cpsw_ale_vlan_get_fld(ale, ale_entry,
				      ALE_ENT_VID_UNREG_MCAST_MSK);
	untag_members = cpsw_ale_vlan_get_fld(ale, ale_entry,
					      ALE_ENT_VID_FORCE_UNTAGGED_MSK);

	vlan_members |= port_mask;
	untag_members = (untag_members & ~port_mask) | untag_mask;
	reg_mcast_members = (reg_mcast_members & ~port_mask) | reg_mask;
	unreg_mcast_members = (unreg_mcast_members & ~port_mask) | unreg_mask;

	ret = cpsw_ale_add_vlan(ale, vid, vlan_members, untag_members,
				reg_mcast_members, unreg_mcast_members);
	अगर (ret) अणु
		dev_err(ale->params.dev, "Unable to add vlan\n");
		वापस ret;
	पूर्ण
	dev_dbg(ale->params.dev, "port mask 0x%x untag 0x%x\n", vlan_members,
		untag_mask);

	वापस ret;
पूर्ण

व्योम cpsw_ale_set_unreg_mcast(काष्ठा cpsw_ale *ale, पूर्णांक unreg_mcast_mask,
			      bool add)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक unreg_members = 0;
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type != ALE_TYPE_VLAN)
			जारी;

		unreg_members =
			cpsw_ale_vlan_get_fld(ale, ale_entry,
					      ALE_ENT_VID_UNREG_MCAST_MSK);
		अगर (add)
			unreg_members |= unreg_mcast_mask;
		अन्यथा
			unreg_members &= ~unreg_mcast_mask;
		cpsw_ale_vlan_set_fld(ale, ale_entry,
				      ALE_ENT_VID_UNREG_MCAST_MSK,
				      unreg_members);
		cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	पूर्ण
पूर्ण

अटल व्योम cpsw_ale_vlan_set_unreg_mcast(काष्ठा cpsw_ale *ale, u32 *ale_entry,
					  पूर्णांक allmulti)
अणु
	पूर्णांक unreg_mcast;

	unreg_mcast = cpsw_ale_vlan_get_fld(ale, ale_entry,
					    ALE_ENT_VID_UNREG_MCAST_MSK);
	अगर (allmulti)
		unreg_mcast |= ALE_PORT_HOST;
	अन्यथा
		unreg_mcast &= ~ALE_PORT_HOST;

	cpsw_ale_vlan_set_fld(ale, ale_entry,
			      ALE_ENT_VID_UNREG_MCAST_MSK, unreg_mcast);
पूर्ण

अटल व्योम
cpsw_ale_vlan_set_unreg_mcast_idx(काष्ठा cpsw_ale *ale, u32 *ale_entry,
				  पूर्णांक allmulti)
अणु
	पूर्णांक unreg_mcast;
	पूर्णांक idx;

	idx = cpsw_ale_vlan_get_fld(ale, ale_entry,
				    ALE_ENT_VID_UNREG_MCAST_IDX);

	unreg_mcast = पढ़ोl(ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));

	अगर (allmulti)
		unreg_mcast |= ALE_PORT_HOST;
	अन्यथा
		unreg_mcast &= ~ALE_PORT_HOST;

	ग_लिखोl(unreg_mcast, ale->params.ale_regs + ALE_VLAN_MASK_MUX(idx));
पूर्ण

व्योम cpsw_ale_set_allmulti(काष्ठा cpsw_ale *ale, पूर्णांक allmulti, पूर्णांक port)
अणु
	u32 ale_entry[ALE_ENTRY_WORDS];
	पूर्णांक type, idx;

	क्रम (idx = 0; idx < ale->params.ale_entries; idx++) अणु
		पूर्णांक vlan_members;

		cpsw_ale_पढ़ो(ale, idx, ale_entry);
		type = cpsw_ale_get_entry_type(ale_entry);
		अगर (type != ALE_TYPE_VLAN)
			जारी;

		vlan_members = cpsw_ale_vlan_get_fld(ale, ale_entry,
						     ALE_ENT_VID_MEMBER_LIST);

		अगर (port != -1 && !(vlan_members & BIT(port)))
			जारी;

		अगर (!ale->params.nu_चयन_ale)
			cpsw_ale_vlan_set_unreg_mcast(ale, ale_entry, allmulti);
		अन्यथा
			cpsw_ale_vlan_set_unreg_mcast_idx(ale, ale_entry,
							  allmulti);

		cpsw_ale_ग_लिखो(ale, idx, ale_entry);
	पूर्ण
पूर्ण

काष्ठा ale_control_info अणु
	स्थिर अक्षर	*name;
	पूर्णांक		offset, port_offset;
	पूर्णांक		shअगरt, port_shअगरt;
	पूर्णांक		bits;
पूर्ण;

अटल काष्ठा ale_control_info ale_controls[ALE_NUM_CONTROLS] = अणु
	[ALE_ENABLE]		= अणु
		.name		= "enable",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 31,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_CLEAR]		= अणु
		.name		= "clear",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 30,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_AGEOUT]		= अणु
		.name		= "ageout",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 29,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_P0_UNI_FLOOD]	= अणु
		.name		= "port0_unicast_flood",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 8,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_VLAN_NOLEARN]	= अणु
		.name		= "vlan_nolearn",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 7,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_NO_PORT_VLAN]	= अणु
		.name		= "no_port_vlan",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 6,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_OUI_DENY]		= अणु
		.name		= "oui_deny",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 5,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_BYPASS]		= अणु
		.name		= "bypass",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 4,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_RATE_LIMIT_TX]	= अणु
		.name		= "rate_limit_tx",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 3,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_VLAN_AWARE]	= अणु
		.name		= "vlan_aware",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 2,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_AUTH_ENABLE]	= अणु
		.name		= "auth_enable",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 1,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_RATE_LIMIT]	= अणु
		.name		= "rate_limit",
		.offset		= ALE_CONTROL,
		.port_offset	= 0,
		.shअगरt		= 0,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_STATE]	= अणु
		.name		= "port_state",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 0,
		.port_shअगरt	= 0,
		.bits		= 2,
	पूर्ण,
	[ALE_PORT_DROP_UNTAGGED] = अणु
		.name		= "drop_untagged",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 2,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_DROP_UNKNOWN_VLAN] = अणु
		.name		= "drop_unknown",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 3,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_NOLEARN]	= अणु
		.name		= "nolearn",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 4,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_NO_SA_UPDATE]	= अणु
		.name		= "no_source_update",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 5,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_MACONLY]	= अणु
		.name		= "mac_only_port_mode",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 11,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_MACONLY_CAF]	= अणु
		.name		= "mac_only_port_caf",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 13,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
	[ALE_PORT_MCAST_LIMIT]	= अणु
		.name		= "mcast_limit",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 16,
		.port_shअगरt	= 0,
		.bits		= 8,
	पूर्ण,
	[ALE_PORT_BCAST_LIMIT]	= अणु
		.name		= "bcast_limit",
		.offset		= ALE_PORTCTL,
		.port_offset	= 4,
		.shअगरt		= 24,
		.port_shअगरt	= 0,
		.bits		= 8,
	पूर्ण,
	[ALE_PORT_UNKNOWN_VLAN_MEMBER] = अणु
		.name		= "unknown_vlan_member",
		.offset		= ALE_UNKNOWNVLAN,
		.port_offset	= 0,
		.shअगरt		= 0,
		.port_shअगरt	= 0,
		.bits		= 6,
	पूर्ण,
	[ALE_PORT_UNKNOWN_MCAST_FLOOD] = अणु
		.name		= "unknown_mcast_flood",
		.offset		= ALE_UNKNOWNVLAN,
		.port_offset	= 0,
		.shअगरt		= 8,
		.port_shअगरt	= 0,
		.bits		= 6,
	पूर्ण,
	[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD] = अणु
		.name		= "unknown_reg_flood",
		.offset		= ALE_UNKNOWNVLAN,
		.port_offset	= 0,
		.shअगरt		= 16,
		.port_shअगरt	= 0,
		.bits		= 6,
	पूर्ण,
	[ALE_PORT_UNTAGGED_EGRESS] = अणु
		.name		= "untagged_egress",
		.offset		= ALE_UNKNOWNVLAN,
		.port_offset	= 0,
		.shअगरt		= 24,
		.port_shअगरt	= 0,
		.bits		= 6,
	पूर्ण,
	[ALE_DEFAULT_THREAD_ID] = अणु
		.name		= "default_thread_id",
		.offset		= AM65_CPSW_ALE_THREAD_DEF_REG,
		.port_offset	= 0,
		.shअगरt		= 0,
		.port_shअगरt	= 0,
		.bits		= 6,
	पूर्ण,
	[ALE_DEFAULT_THREAD_ENABLE] = अणु
		.name		= "default_thread_id_enable",
		.offset		= AM65_CPSW_ALE_THREAD_DEF_REG,
		.port_offset	= 0,
		.shअगरt		= 15,
		.port_shअगरt	= 0,
		.bits		= 1,
	पूर्ण,
पूर्ण;

पूर्णांक cpsw_ale_control_set(काष्ठा cpsw_ale *ale, पूर्णांक port, पूर्णांक control,
			 पूर्णांक value)
अणु
	स्थिर काष्ठा ale_control_info *info;
	पूर्णांक offset, shअगरt;
	u32 पंचांगp, mask;

	अगर (control < 0 || control >= ARRAY_SIZE(ale_controls))
		वापस -EINVAL;

	info = &ale_controls[control];
	अगर (info->port_offset == 0 && info->port_shअगरt == 0)
		port = 0; /* global, port is a करोnt care */

	अगर (port < 0 || port >= ale->params.ale_ports)
		वापस -EINVAL;

	mask = BITMASK(info->bits);
	अगर (value & ~mask)
		वापस -EINVAL;

	offset = info->offset + (port * info->port_offset);
	shअगरt  = info->shअगरt  + (port * info->port_shअगरt);

	पंचांगp = पढ़ोl_relaxed(ale->params.ale_regs + offset);
	पंचांगp = (पंचांगp & ~(mask << shअगरt)) | (value << shअगरt);
	ग_लिखोl_relaxed(पंचांगp, ale->params.ale_regs + offset);

	वापस 0;
पूर्ण

पूर्णांक cpsw_ale_control_get(काष्ठा cpsw_ale *ale, पूर्णांक port, पूर्णांक control)
अणु
	स्थिर काष्ठा ale_control_info *info;
	पूर्णांक offset, shअगरt;
	u32 पंचांगp;

	अगर (control < 0 || control >= ARRAY_SIZE(ale_controls))
		वापस -EINVAL;

	info = &ale_controls[control];
	अगर (info->port_offset == 0 && info->port_shअगरt == 0)
		port = 0; /* global, port is a करोnt care */

	अगर (port < 0 || port >= ale->params.ale_ports)
		वापस -EINVAL;

	offset = info->offset + (port * info->port_offset);
	shअगरt  = info->shअगरt  + (port * info->port_shअगरt);

	पंचांगp = पढ़ोl_relaxed(ale->params.ale_regs + offset) >> shअगरt;
	वापस पंचांगp & BITMASK(info->bits);
पूर्ण

अटल व्योम cpsw_ale_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा cpsw_ale *ale = from_समयr(ale, t, समयr);

	cpsw_ale_control_set(ale, 0, ALE_AGEOUT, 1);

	अगर (ale->ageout) अणु
		ale->समयr.expires = jअगरfies + ale->ageout;
		add_समयr(&ale->समयr);
	पूर्ण
पूर्ण

अटल व्योम cpsw_ale_hw_aging_समयr_start(काष्ठा cpsw_ale *ale)
अणु
	u32 aging_समयr;

	aging_समयr = ale->params.bus_freq / 1000000;
	aging_समयr *= ale->params.ale_ageout;

	अगर (aging_समयr & ~ALE_AGING_TIMER_MASK) अणु
		aging_समयr = ALE_AGING_TIMER_MASK;
		dev_warn(ale->params.dev,
			 "ALE aging timer overflow, set to max\n");
	पूर्ण

	ग_लिखोl(aging_समयr, ale->params.ale_regs + ALE_AGING_TIMER);
पूर्ण

अटल व्योम cpsw_ale_hw_aging_समयr_stop(काष्ठा cpsw_ale *ale)
अणु
	ग_लिखोl(0, ale->params.ale_regs + ALE_AGING_TIMER);
पूर्ण

अटल व्योम cpsw_ale_aging_start(काष्ठा cpsw_ale *ale)
अणु
	अगर (!ale->params.ale_ageout)
		वापस;

	अगर (ale->features & CPSW_ALE_F_HW_AUTOAGING) अणु
		cpsw_ale_hw_aging_समयr_start(ale);
		वापस;
	पूर्ण

	समयr_setup(&ale->समयr, cpsw_ale_समयr, 0);
	ale->समयr.expires = jअगरfies + ale->ageout;
	add_समयr(&ale->समयr);
पूर्ण

अटल व्योम cpsw_ale_aging_stop(काष्ठा cpsw_ale *ale)
अणु
	अगर (!ale->params.ale_ageout)
		वापस;

	अगर (ale->features & CPSW_ALE_F_HW_AUTOAGING) अणु
		cpsw_ale_hw_aging_समयr_stop(ale);
		वापस;
	पूर्ण

	del_समयr_sync(&ale->समयr);
पूर्ण

व्योम cpsw_ale_start(काष्ठा cpsw_ale *ale)
अणु
	cpsw_ale_control_set(ale, 0, ALE_ENABLE, 1);
	cpsw_ale_control_set(ale, 0, ALE_CLEAR, 1);

	cpsw_ale_aging_start(ale);
पूर्ण

व्योम cpsw_ale_stop(काष्ठा cpsw_ale *ale)
अणु
	cpsw_ale_aging_stop(ale);
	cpsw_ale_control_set(ale, 0, ALE_CLEAR, 1);
	cpsw_ale_control_set(ale, 0, ALE_ENABLE, 0);
पूर्ण

अटल स्थिर काष्ठा cpsw_ale_dev_id cpsw_ale_id_match[] = अणु
	अणु
		/* am3/4/5, dra7. dm814x, 66ak2hk-gbe */
		.dev_id = "cpsw",
		.tbl_entries = 1024,
		.major_ver_mask = 0xff,
		.vlan_entry_tbl = vlan_entry_cpsw,
	पूर्ण,
	अणु
		/* 66ak2h_xgbe */
		.dev_id = "66ak2h-xgbe",
		.tbl_entries = 2048,
		.major_ver_mask = 0xff,
		.vlan_entry_tbl = vlan_entry_cpsw,
	पूर्ण,
	अणु
		.dev_id = "66ak2el",
		.features = CPSW_ALE_F_STATUS_REG,
		.major_ver_mask = 0x7,
		.nu_चयन_ale = true,
		.vlan_entry_tbl = vlan_entry_nu,
	पूर्ण,
	अणु
		.dev_id = "66ak2g",
		.features = CPSW_ALE_F_STATUS_REG,
		.tbl_entries = 64,
		.major_ver_mask = 0x7,
		.nu_चयन_ale = true,
		.vlan_entry_tbl = vlan_entry_nu,
	पूर्ण,
	अणु
		.dev_id = "am65x-cpsw2g",
		.features = CPSW_ALE_F_STATUS_REG | CPSW_ALE_F_HW_AUTOAGING,
		.tbl_entries = 64,
		.major_ver_mask = 0x7,
		.nu_चयन_ale = true,
		.vlan_entry_tbl = vlan_entry_nu,
	पूर्ण,
	अणु
		.dev_id = "j721e-cpswxg",
		.features = CPSW_ALE_F_STATUS_REG | CPSW_ALE_F_HW_AUTOAGING,
		.major_ver_mask = 0x7,
		.vlan_entry_tbl = vlan_entry_k3_cpswxg,
	पूर्ण,
	अणु
		.dev_id = "am64-cpswxg",
		.features = CPSW_ALE_F_STATUS_REG | CPSW_ALE_F_HW_AUTOAGING,
		.major_ver_mask = 0x7,
		.vlan_entry_tbl = vlan_entry_k3_cpswxg,
		.tbl_entries = 512,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
cpsw_ale_dev_id *cpsw_ale_match_id(स्थिर काष्ठा cpsw_ale_dev_id *id,
				   स्थिर अक्षर *dev_id)
अणु
	अगर (!dev_id)
		वापस शून्य;

	जबतक (id->dev_id) अणु
		अगर (म_भेद(dev_id, id->dev_id) == 0)
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा cpsw_ale *cpsw_ale_create(काष्ठा cpsw_ale_params *params)
अणु
	स्थिर काष्ठा cpsw_ale_dev_id *ale_dev_id;
	काष्ठा cpsw_ale *ale;
	u32 rev, ale_entries;

	ale_dev_id = cpsw_ale_match_id(cpsw_ale_id_match, params->dev_id);
	अगर (!ale_dev_id)
		वापस ERR_PTR(-EINVAL);

	params->ale_entries = ale_dev_id->tbl_entries;
	params->major_ver_mask = ale_dev_id->major_ver_mask;
	params->nu_चयन_ale = ale_dev_id->nu_चयन_ale;

	ale = devm_kzalloc(params->dev, माप(*ale), GFP_KERNEL);
	अगर (!ale)
		वापस ERR_PTR(-ENOMEM);

	ale->p0_untag_vid_mask =
		devm_kदो_स्मृति_array(params->dev, BITS_TO_LONGS(VLAN_N_VID),
				   माप(अचिन्हित दीर्घ),
				   GFP_KERNEL);
	अगर (!ale->p0_untag_vid_mask)
		वापस ERR_PTR(-ENOMEM);

	ale->params = *params;
	ale->ageout = ale->params.ale_ageout * HZ;
	ale->features = ale_dev_id->features;
	ale->vlan_entry_tbl = ale_dev_id->vlan_entry_tbl;

	rev = पढ़ोl_relaxed(ale->params.ale_regs + ALE_IDVER);
	ale->version =
		(ALE_VERSION_MAJOR(rev, ale->params.major_ver_mask) << 8) |
		 ALE_VERSION_MINOR(rev);
	dev_info(ale->params.dev, "initialized cpsw ale version %d.%d\n",
		 ALE_VERSION_MAJOR(rev, ale->params.major_ver_mask),
		 ALE_VERSION_MINOR(rev));

	अगर (ale->features & CPSW_ALE_F_STATUS_REG &&
	    !ale->params.ale_entries) अणु
		ale_entries =
			पढ़ोl_relaxed(ale->params.ale_regs + ALE_STATUS) &
			ALE_STATUS_SIZE_MASK;
		/* ALE available on newer NetCP चयनes has पूर्णांकroduced
		 * a रेजिस्टर, ALE_STATUS, to indicate the size of ALE
		 * table which shows the size as a multiple of 1024 entries.
		 * For these, params.ale_entries will be set to zero. So
		 * पढ़ो the रेजिस्टर and update the value of ale_entries.
		 * वापस error अगर ale_entries is zero in ALE_STATUS.
		 */
		अगर (!ale_entries)
			वापस ERR_PTR(-EINVAL);

		ale_entries *= ALE_TABLE_SIZE_MULTIPLIER;
		ale->params.ale_entries = ale_entries;
	पूर्ण
	dev_info(ale->params.dev,
		 "ALE Table size %ld\n", ale->params.ale_entries);

	/* set शेष bits क्रम existing h/w */
	ale->port_mask_bits = ale->params.ale_ports;
	ale->port_num_bits = order_base_2(ale->params.ale_ports);
	ale->vlan_field_bits = ale->params.ale_ports;

	/* Set शेषs override क्रम ALE on NetCP NU चयन and क्रम version
	 * 1R3
	 */
	अगर (ale->params.nu_चयन_ale) अणु
		/* Separate रेजिस्टरs क्रम unknown vlan configuration.
		 * Also there are N bits, where N is number of ale
		 * ports and shअगरt value should be 0
		 */
		ale_controls[ALE_PORT_UNKNOWN_VLAN_MEMBER].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_VLAN_MEMBER].offset =
					ALE_UNKNOWNVLAN_MEMBER;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].shअगरt = 0;
		ale_controls[ALE_PORT_UNKNOWN_MCAST_FLOOD].offset =
					ALE_UNKNOWNVLAN_UNREG_MCAST_FLOOD;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].shअगरt = 0;
		ale_controls[ALE_PORT_UNKNOWN_REG_MCAST_FLOOD].offset =
					ALE_UNKNOWNVLAN_REG_MCAST_FLOOD;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].bits =
					ale->params.ale_ports;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].shअगरt = 0;
		ale_controls[ALE_PORT_UNTAGGED_EGRESS].offset =
					ALE_UNKNOWNVLAN_FORCE_UNTAG_EGRESS;
	पूर्ण

	cpsw_ale_control_set(ale, 0, ALE_CLEAR, 1);
	वापस ale;
पूर्ण

व्योम cpsw_ale_dump(काष्ठा cpsw_ale *ale, u32 *data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ale->params.ale_entries; i++) अणु
		cpsw_ale_पढ़ो(ale, i, data);
		data += ALE_ENTRY_WORDS;
	पूर्ण
पूर्ण

u32 cpsw_ale_get_num_entries(काष्ठा cpsw_ale *ale)
अणु
	वापस ale ? ale->params.ale_entries : 0;
पूर्ण
