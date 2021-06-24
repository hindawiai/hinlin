<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic iSCSI Offload Driver
 * Copyright (c) 2016 Cavium Inc.
 */

#अगर_अघोषित NVM_ISCSI_CFG_H
#घोषणा NVM_ISCSI_CFG_H

#घोषणा NUM_OF_ISCSI_TARGET_PER_PF    4   /* Defined as per the
					   * ISCSI IBFT स्थिरraपूर्णांक
					   */
#घोषणा NUM_OF_ISCSI_PF_SUPPORTED     4   /* One PF per Port -
					   * assuming 4 port card
					   */

#घोषणा NVM_ISCSI_CFG_DHCP_NAME_MAX_LEN  256

जोड़ nvm_iscsi_dhcp_venकरोr_id अणु
	u32 value[NVM_ISCSI_CFG_DHCP_NAME_MAX_LEN / 4];
	u8  byte[NVM_ISCSI_CFG_DHCP_NAME_MAX_LEN];
पूर्ण;

#घोषणा NVM_ISCSI_IPV4_ADDR_BYTE_LEN 4
जोड़ nvm_iscsi_ipv4_addr अणु
	u32 addr;
	u8  byte[NVM_ISCSI_IPV4_ADDR_BYTE_LEN];
पूर्ण;

#घोषणा NVM_ISCSI_IPV6_ADDR_BYTE_LEN 16
जोड़ nvm_iscsi_ipv6_addr अणु
	u32 addr[4];
	u8  byte[NVM_ISCSI_IPV6_ADDR_BYTE_LEN];
पूर्ण;

काष्ठा nvm_iscsi_initiator_ipv4 अणु
	जोड़ nvm_iscsi_ipv4_addr addr;				/* 0x0 */
	जोड़ nvm_iscsi_ipv4_addr subnet_mask;			/* 0x4 */
	जोड़ nvm_iscsi_ipv4_addr gateway;			/* 0x8 */
	जोड़ nvm_iscsi_ipv4_addr primary_dns;			/* 0xC */
	जोड़ nvm_iscsi_ipv4_addr secondary_dns;		/* 0x10 */
	जोड़ nvm_iscsi_ipv4_addr dhcp_addr;			/* 0x14 */

	जोड़ nvm_iscsi_ipv4_addr isns_server;			/* 0x18 */
	जोड़ nvm_iscsi_ipv4_addr slp_server;			/* 0x1C */
	जोड़ nvm_iscsi_ipv4_addr primay_radius_server;		/* 0x20 */
	जोड़ nvm_iscsi_ipv4_addr secondary_radius_server;	/* 0x24 */

	जोड़ nvm_iscsi_ipv4_addr rsvd[4];			/* 0x28 */
पूर्ण;

काष्ठा nvm_iscsi_initiator_ipv6 अणु
	जोड़ nvm_iscsi_ipv6_addr addr;				/* 0x0 */
	जोड़ nvm_iscsi_ipv6_addr subnet_mask;			/* 0x10 */
	जोड़ nvm_iscsi_ipv6_addr gateway;			/* 0x20 */
	जोड़ nvm_iscsi_ipv6_addr primary_dns;			/* 0x30 */
	जोड़ nvm_iscsi_ipv6_addr secondary_dns;		/* 0x40 */
	जोड़ nvm_iscsi_ipv6_addr dhcp_addr;			/* 0x50 */

	जोड़ nvm_iscsi_ipv6_addr isns_server;			/* 0x60 */
	जोड़ nvm_iscsi_ipv6_addr slp_server;			/* 0x70 */
	जोड़ nvm_iscsi_ipv6_addr primay_radius_server;		/* 0x80 */
	जोड़ nvm_iscsi_ipv6_addr secondary_radius_server;	/* 0x90 */

	जोड़ nvm_iscsi_ipv6_addr rsvd[3];			/* 0xA0 */

	u32   config;						/* 0xD0 */
#घोषणा NVM_ISCSI_CFG_INITIATOR_IPV6_SUBNET_MASK_PREFIX_MASK      0x000000FF
#घोषणा NVM_ISCSI_CFG_INITIATOR_IPV6_SUBNET_MASK_PREFIX_OFFSET    0

	u32   rsvd_1[3];
पूर्ण;

#घोषणा NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN  256
जोड़ nvm_iscsi_name अणु
	u32 value[NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN / 4];
	u8  byte[NVM_ISCSI_CFG_ISCSI_NAME_MAX_LEN];
पूर्ण;

#घोषणा NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN  256
जोड़ nvm_iscsi_chap_name अणु
	u32 value[NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN / 4];
	u8  byte[NVM_ISCSI_CFG_CHAP_NAME_MAX_LEN];
पूर्ण;

#घोषणा NVM_ISCSI_CFG_CHAP_PWD_MAX_LEN  16 /* md5 need per RFC1996
					    * is 16 octets
					    */
जोड़ nvm_iscsi_chap_password अणु
	u32 value[NVM_ISCSI_CFG_CHAP_PWD_MAX_LEN / 4];
	u8 byte[NVM_ISCSI_CFG_CHAP_PWD_MAX_LEN];
पूर्ण;

जोड़ nvm_iscsi_lun अणु
	u8  byte[8];
	u32 value[2];
पूर्ण;

काष्ठा nvm_iscsi_generic अणु
	u32 ctrl_flags;						/* 0x0 */
#घोषणा NVM_ISCSI_CFG_GEN_CHAP_ENABLED                 BIT(0)
#घोषणा NVM_ISCSI_CFG_GEN_DHCP_TCPIP_CONFIG_ENABLED    BIT(1)
#घोषणा NVM_ISCSI_CFG_GEN_DHCP_ISCSI_CONFIG_ENABLED    BIT(2)
#घोषणा NVM_ISCSI_CFG_GEN_IPV6_ENABLED                 BIT(3)
#घोषणा NVM_ISCSI_CFG_GEN_IPV4_FALLBACK_ENABLED        BIT(4)
#घोषणा NVM_ISCSI_CFG_GEN_ISNS_WORLD_LOGIN             BIT(5)
#घोषणा NVM_ISCSI_CFG_GEN_ISNS_SELECTIVE_LOGIN         BIT(6)
#घोषणा NVM_ISCSI_CFG_GEN_ADDR_REसूचीECT_ENABLED	       BIT(7)
#घोषणा NVM_ISCSI_CFG_GEN_CHAP_MUTUAL_ENABLED          BIT(8)

	u32 समयout;						/* 0x4 */
#घोषणा NVM_ISCSI_CFG_GEN_DHCP_REQUEST_TIMEOUT_MASK       0x0000FFFF
#घोषणा NVM_ISCSI_CFG_GEN_DHCP_REQUEST_TIMEOUT_OFFSET     0
#घोषणा NVM_ISCSI_CFG_GEN_PORT_LOGIN_TIMEOUT_MASK         0xFFFF0000
#घोषणा NVM_ISCSI_CFG_GEN_PORT_LOGIN_TIMEOUT_OFFSET       16

	जोड़ nvm_iscsi_dhcp_venकरोr_id  dhcp_venकरोr_id;		/* 0x8  */
	u32 rsvd[62];						/* 0x108 */
पूर्ण;

काष्ठा nvm_iscsi_initiator अणु
	काष्ठा nvm_iscsi_initiator_ipv4 ipv4;			/* 0x0 */
	काष्ठा nvm_iscsi_initiator_ipv6 ipv6;			/* 0x38 */

	जोड़ nvm_iscsi_name           initiator_name;		/* 0x118 */
	जोड़ nvm_iscsi_chap_name      chap_name;		/* 0x218 */
	जोड़ nvm_iscsi_chap_password  chap_password;		/* 0x318 */

	u32 generic_cont0;					/* 0x398 */
#घोषणा NVM_ISCSI_CFG_INITIATOR_VLAN_MASK		0x0000FFFF
#घोषणा NVM_ISCSI_CFG_INITIATOR_VLAN_OFFSET		0
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_MASK		0x00030000
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_OFFSET	16
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_4		1
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_6		2
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_4_AND_6	3

	u32 ctrl_flags;
#घोषणा NVM_ISCSI_CFG_INITIATOR_IP_VERSION_PRIORITY_V6     BIT(0)
#घोषणा NVM_ISCSI_CFG_INITIATOR_VLAN_ENABLED               BIT(1)

	u32 rsvd[116];						/* 0x32C */
पूर्ण;

काष्ठा nvm_iscsi_target अणु
	u32 ctrl_flags;						/* 0x0 */
#घोषणा NVM_ISCSI_CFG_TARGET_ENABLED            BIT(0)
#घोषणा NVM_ISCSI_CFG_BOOT_TIME_LOGIN_STATUS    BIT(1)

	u32 generic_cont0;					/* 0x4 */
#घोषणा NVM_ISCSI_CFG_TARGET_TCP_PORT_MASK      0x0000FFFF
#घोषणा NVM_ISCSI_CFG_TARGET_TCP_PORT_OFFSET    0

	u32 ip_ver;
#घोषणा NVM_ISCSI_CFG_IPv4       4
#घोषणा NVM_ISCSI_CFG_IPv6       6

	u32 rsvd_1[7];						/* 0x24 */
	जोड़ nvm_iscsi_ipv4_addr ipv4_addr;			/* 0x28 */
	जोड़ nvm_iscsi_ipv6_addr ipv6_addr;			/* 0x2C */
	जोड़ nvm_iscsi_lun lun;				/* 0x3C */

	जोड़ nvm_iscsi_name           target_name;		/* 0x44 */
	जोड़ nvm_iscsi_chap_name      chap_name;		/* 0x144 */
	जोड़ nvm_iscsi_chap_password  chap_password;		/* 0x244 */

	u32 rsvd_2[107];					/* 0x2C4 */
पूर्ण;

काष्ठा nvm_iscsi_block अणु
	u32 id;							/* 0x0 */
#घोषणा NVM_ISCSI_CFG_BLK_MAPPED_PF_ID_MASK         0x0000000F
#घोषणा NVM_ISCSI_CFG_BLK_MAPPED_PF_ID_OFFSET       0
#घोषणा NVM_ISCSI_CFG_BLK_CTRL_FLAG_MASK            0x00000FF0
#घोषणा NVM_ISCSI_CFG_BLK_CTRL_FLAG_OFFSET          4
#घोषणा NVM_ISCSI_CFG_BLK_CTRL_FLAG_IS_NOT_EMPTY    BIT(0)
#घोषणा NVM_ISCSI_CFG_BLK_CTRL_FLAG_PF_MAPPED       BIT(1)

	u32 rsvd_1[5];						/* 0x4 */

	काष्ठा nvm_iscsi_generic     generic;			/* 0x18 */
	काष्ठा nvm_iscsi_initiator   initiator;			/* 0x218 */
	काष्ठा nvm_iscsi_target      target[NUM_OF_ISCSI_TARGET_PER_PF];
								/* 0x718 */

	u32 rsvd_2[58];						/* 0x1718 */
	/* total size - 0x1800 - 6K block */
पूर्ण;

काष्ठा nvm_iscsi_cfg अणु
	u32 id;							/* 0x0 */
#घोषणा NVM_ISCSI_CFG_BLK_VERSION_MINOR_MASK     0x000000FF
#घोषणा NVM_ISCSI_CFG_BLK_VERSION_MAJOR_MASK     0x0000FF00
#घोषणा NVM_ISCSI_CFG_BLK_SIGNATURE_MASK         0xFFFF0000
#घोषणा NVM_ISCSI_CFG_BLK_SIGNATURE              0x49430000 /* IC - Iscsi
							     * Config
							     */

#घोषणा NVM_ISCSI_CFG_BLK_VERSION_MAJOR          0
#घोषणा NVM_ISCSI_CFG_BLK_VERSION_MINOR          10
#घोषणा NVM_ISCSI_CFG_BLK_VERSION ((NVM_ISCSI_CFG_BLK_VERSION_MAJOR << 8) | \
				   NVM_ISCSI_CFG_BLK_VERSION_MINOR)

	काष्ठा nvm_iscsi_block	block[NUM_OF_ISCSI_PF_SUPPORTED]; /* 0x4 */
पूर्ण;

#पूर्ण_अगर
