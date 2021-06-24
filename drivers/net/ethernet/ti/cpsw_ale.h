<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Texas Instruments N-Port Ethernet Switch Address Lookup Engine APIs
 *
 * Copyright (C) 2012 Texas Instruments
 *
 */
#अगर_अघोषित __TI_CPSW_ALE_H__
#घोषणा __TI_CPSW_ALE_H__

काष्ठा cpsw_ale_params अणु
	काष्ठा device		*dev;
	व्योम __iomem		*ale_regs;
	अचिन्हित दीर्घ		ale_ageout;	/* in secs */
	अचिन्हित दीर्घ		ale_entries;
	अचिन्हित दीर्घ		ale_ports;
	/* NU Switch has specअगरic handling as number of bits in ALE entries
	 * are dअगरferent than other versions of ALE. Also there are specअगरic
	 * रेजिस्टरs क्रम unknown vlan specअगरic fields. So use nu_चयन_ale
	 * to identअगरy this hardware.
	 */
	bool			nu_चयन_ale;
	/* mask bit used in NU Switch ALE is 3 bits instead of 8 bits. So
	 * pass it from caller.
	 */
	u32			major_ver_mask;
	स्थिर अक्षर		*dev_id;
	अचिन्हित दीर्घ		bus_freq;
पूर्ण;

काष्ठा ale_entry_fld;

काष्ठा cpsw_ale अणु
	काष्ठा cpsw_ale_params	params;
	काष्ठा समयr_list	समयr;
	अचिन्हित दीर्घ		ageout;
	u32			version;
	u32			features;
	/* These bits are dअगरferent on NetCP NU Switch ALE */
	u32			port_mask_bits;
	u32			port_num_bits;
	u32			vlan_field_bits;
	अचिन्हित दीर्घ		*p0_untag_vid_mask;
	स्थिर काष्ठा ale_entry_fld *vlan_entry_tbl;
पूर्ण;

क्रमागत cpsw_ale_control अणु
	/* global */
	ALE_ENABLE,
	ALE_CLEAR,
	ALE_AGEOUT,
	ALE_P0_UNI_FLOOD,
	ALE_VLAN_NOLEARN,
	ALE_NO_PORT_VLAN,
	ALE_OUI_DENY,
	ALE_BYPASS,
	ALE_RATE_LIMIT_TX,
	ALE_VLAN_AWARE,
	ALE_AUTH_ENABLE,
	ALE_RATE_LIMIT,
	/* port controls */
	ALE_PORT_STATE,
	ALE_PORT_DROP_UNTAGGED,
	ALE_PORT_DROP_UNKNOWN_VLAN,
	ALE_PORT_NOLEARN,
	ALE_PORT_NO_SA_UPDATE,
	ALE_PORT_UNKNOWN_VLAN_MEMBER,
	ALE_PORT_UNKNOWN_MCAST_FLOOD,
	ALE_PORT_UNKNOWN_REG_MCAST_FLOOD,
	ALE_PORT_UNTAGGED_EGRESS,
	ALE_PORT_MACONLY,
	ALE_PORT_MACONLY_CAF,
	ALE_PORT_BCAST_LIMIT,
	ALE_PORT_MCAST_LIMIT,
	ALE_DEFAULT_THREAD_ID,
	ALE_DEFAULT_THREAD_ENABLE,
	ALE_NUM_CONTROLS,
पूर्ण;

क्रमागत cpsw_ale_port_state अणु
	ALE_PORT_STATE_DISABLE	= 0x00,
	ALE_PORT_STATE_BLOCK	= 0x01,
	ALE_PORT_STATE_LEARN	= 0x02,
	ALE_PORT_STATE_FORWARD	= 0x03,
पूर्ण;

/* ALE unicast entry flags - passed पूर्णांकo cpsw_ale_add_ucast() */
#घोषणा ALE_SECURE			BIT(0)
#घोषणा ALE_BLOCKED			BIT(1)
#घोषणा ALE_SUPER			BIT(2)
#घोषणा ALE_VLAN			BIT(3)

#घोषणा ALE_PORT_HOST			BIT(0)
#घोषणा ALE_PORT_1			BIT(1)
#घोषणा ALE_PORT_2			BIT(2)

#घोषणा ALE_MCAST_FWD			0
#घोषणा ALE_MCAST_BLOCK_LEARN_FWD	1
#घोषणा ALE_MCAST_FWD_LEARN		2
#घोषणा ALE_MCAST_FWD_2			3

#घोषणा ALE_ENTRY_BITS		68
#घोषणा ALE_ENTRY_WORDS	DIV_ROUND_UP(ALE_ENTRY_BITS, 32)

काष्ठा cpsw_ale *cpsw_ale_create(काष्ठा cpsw_ale_params *params);

व्योम cpsw_ale_start(काष्ठा cpsw_ale *ale);
व्योम cpsw_ale_stop(काष्ठा cpsw_ale *ale);

पूर्णांक cpsw_ale_flush_multicast(काष्ठा cpsw_ale *ale, पूर्णांक port_mask, पूर्णांक vid);
पूर्णांक cpsw_ale_add_ucast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port,
		       पूर्णांक flags, u16 vid);
पूर्णांक cpsw_ale_del_ucast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port,
		       पूर्णांक flags, u16 vid);
पूर्णांक cpsw_ale_add_mcast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port_mask,
		       पूर्णांक flags, u16 vid, पूर्णांक mcast_state);
पूर्णांक cpsw_ale_del_mcast(काष्ठा cpsw_ale *ale, स्थिर u8 *addr, पूर्णांक port_mask,
		       पूर्णांक flags, u16 vid);
पूर्णांक cpsw_ale_add_vlan(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port, पूर्णांक untag,
			पूर्णांक reg_mcast, पूर्णांक unreg_mcast);
पूर्णांक cpsw_ale_del_vlan(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port);
व्योम cpsw_ale_set_allmulti(काष्ठा cpsw_ale *ale, पूर्णांक allmulti, पूर्णांक port);

पूर्णांक cpsw_ale_control_get(काष्ठा cpsw_ale *ale, पूर्णांक port, पूर्णांक control);
पूर्णांक cpsw_ale_control_set(काष्ठा cpsw_ale *ale, पूर्णांक port,
			 पूर्णांक control, पूर्णांक value);
व्योम cpsw_ale_dump(काष्ठा cpsw_ale *ale, u32 *data);
u32 cpsw_ale_get_num_entries(काष्ठा cpsw_ale *ale);

अटल अंतरभूत पूर्णांक cpsw_ale_get_vlan_p0_untag(काष्ठा cpsw_ale *ale, u16 vid)
अणु
	वापस test_bit(vid, ale->p0_untag_vid_mask);
पूर्ण

पूर्णांक cpsw_ale_vlan_add_modअगरy(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask,
			     पूर्णांक untag_mask, पूर्णांक reg_mcast, पूर्णांक unreg_mcast);
पूर्णांक cpsw_ale_vlan_del_modअगरy(काष्ठा cpsw_ale *ale, u16 vid, पूर्णांक port_mask);
व्योम cpsw_ale_set_unreg_mcast(काष्ठा cpsw_ale *ale, पूर्णांक unreg_mcast_mask,
			      bool add);

#पूर्ण_अगर
