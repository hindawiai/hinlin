<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2009 - 2018 Intel Corporation. */

#अगर_अघोषित _E1000_VF_H_
#घोषणा _E1000_VF_H_

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/अगर_ether.h>

#समावेश "regs.h"
#समावेश "defines.h"

काष्ठा e1000_hw;

#घोषणा E1000_DEV_ID_82576_VF		0x10CA
#घोषणा E1000_DEV_ID_I350_VF		0x1520
#घोषणा E1000_REVISION_0	0
#घोषणा E1000_REVISION_1	1
#घोषणा E1000_REVISION_2	2
#घोषणा E1000_REVISION_3	3
#घोषणा E1000_REVISION_4	4

#घोषणा E1000_FUNC_0	0
#घोषणा E1000_FUNC_1	1

/* Receive Address Register Count
 * Number of high/low रेजिस्टर pairs in the RAR.  The RAR (Receive Address
 * Registers) holds the directed and multicast addresses that we monitor.
 * These entries are also used क्रम MAC-based filtering.
 */
#घोषणा E1000_RAR_ENTRIES_VF	1

/* Receive Descriptor - Advanced */
जोड़ e1000_adv_rx_desc अणु
	काष्ठा अणु
		u64 pkt_addr; /* Packet buffer address */
		u64 hdr_addr; /* Header buffer address */
	पूर्ण पढ़ो;
	काष्ठा अणु
		काष्ठा अणु
			जोड़ अणु
				u32 data;
				काष्ठा अणु
					u16 pkt_info; /* RSS/Packet type */
					/* Split Header, hdr buffer length */
					u16 hdr_info;
				पूर्ण hs_rss;
			पूर्ण lo_dword;
			जोड़ अणु
				u32 rss; /* RSS Hash */
				काष्ठा अणु
					u16 ip_id; /* IP id */
					u16 csum;  /* Packet Checksum */
				पूर्ण csum_ip;
			पूर्ण hi_dword;
		पूर्ण lower;
		काष्ठा अणु
			u32 status_error; /* ext status/error */
			u16 length; /* Packet length */
			u16 vlan;   /* VLAN tag */
		पूर्ण upper;
	पूर्ण wb;  /* ग_लिखोback */
पूर्ण;

#घोषणा E1000_RXDADV_HDRBUFLEN_MASK	0x7FE0
#घोषणा E1000_RXDADV_HDRBUFLEN_SHIFT	5

/* Transmit Descriptor - Advanced */
जोड़ e1000_adv_tx_desc अणु
	काष्ठा अणु
		u64 buffer_addr; /* Address of descriptor's data buf */
		u32 cmd_type_len;
		u32 olinfo_status;
	पूर्ण पढ़ो;
	काष्ठा अणु
		u64 rsvd; /* Reserved */
		u32 nxtseq_seed;
		u32 status;
	पूर्ण wb;
पूर्ण;

/* Adv Transmit Descriptor Config Masks */
#घोषणा E1000_ADVTXD_DTYP_CTXT	0x00200000 /* Advanced Context Descriptor */
#घोषणा E1000_ADVTXD_DTYP_DATA	0x00300000 /* Advanced Data Descriptor */
#घोषणा E1000_ADVTXD_DCMD_EOP	0x01000000 /* End of Packet */
#घोषणा E1000_ADVTXD_DCMD_IFCS	0x02000000 /* Insert FCS (Ethernet CRC) */
#घोषणा E1000_ADVTXD_DCMD_RS	0x08000000 /* Report Status */
#घोषणा E1000_ADVTXD_DCMD_DEXT	0x20000000 /* Descriptor extension (1=Adv) */
#घोषणा E1000_ADVTXD_DCMD_VLE	0x40000000 /* VLAN pkt enable */
#घोषणा E1000_ADVTXD_DCMD_TSE	0x80000000 /* TCP Seg enable */
#घोषणा E1000_ADVTXD_PAYLEN_SHIFT	14 /* Adv desc PAYLEN shअगरt */

/* Context descriptors */
काष्ठा e1000_adv_tx_context_desc अणु
	u32 vlan_macip_lens;
	u32 seqnum_seed;
	u32 type_tucmd_mlhl;
	u32 mss_l4len_idx;
पूर्ण;

#घोषणा E1000_ADVTXD_MACLEN_SHIFT	9  /* Adv ctxt desc mac len shअगरt */
#घोषणा E1000_ADVTXD_TUCMD_IPV4		0x00000400 /* IP Packet Type: 1=IPv4 */
#घोषणा E1000_ADVTXD_TUCMD_L4T_TCP	0x00000800 /* L4 Packet TYPE of TCP */
#घोषणा E1000_ADVTXD_TUCMD_L4T_SCTP	0x00001000 /* L4 packet TYPE of SCTP */
#घोषणा E1000_ADVTXD_L4LEN_SHIFT	8  /* Adv ctxt L4LEN shअगरt */
#घोषणा E1000_ADVTXD_MSS_SHIFT		16 /* Adv ctxt MSS shअगरt */

क्रमागत e1000_mac_type अणु
	e1000_undefined = 0,
	e1000_vfadapt,
	e1000_vfadapt_i350,
	e1000_num_macs  /* List is 1-based, so subtract 1 क्रम true count. */
पूर्ण;

काष्ठा e1000_vf_stats अणु
	u64 base_gprc;
	u64 base_gptc;
	u64 base_gorc;
	u64 base_gotc;
	u64 base_mprc;
	u64 base_gotlbc;
	u64 base_gptlbc;
	u64 base_gorlbc;
	u64 base_gprlbc;

	u32 last_gprc;
	u32 last_gptc;
	u32 last_gorc;
	u32 last_gotc;
	u32 last_mprc;
	u32 last_gotlbc;
	u32 last_gptlbc;
	u32 last_gorlbc;
	u32 last_gprlbc;

	u64 gprc;
	u64 gptc;
	u64 gorc;
	u64 gotc;
	u64 mprc;
	u64 gotlbc;
	u64 gptlbc;
	u64 gorlbc;
	u64 gprlbc;
पूर्ण;

#समावेश "mbx.h"

काष्ठा e1000_mac_operations अणु
	/* Function poपूर्णांकers क्रम the MAC. */
	s32  (*init_params)(काष्ठा e1000_hw *);
	s32  (*check_क्रम_link)(काष्ठा e1000_hw *);
	व्योम (*clear_vfta)(काष्ठा e1000_hw *);
	s32  (*get_bus_info)(काष्ठा e1000_hw *);
	s32  (*get_link_up_info)(काष्ठा e1000_hw *, u16 *, u16 *);
	व्योम (*update_mc_addr_list)(काष्ठा e1000_hw *, u8 *, u32, u32, u32);
	s32  (*set_uc_addr)(काष्ठा e1000_hw *, u32, u8 *);
	s32  (*reset_hw)(काष्ठा e1000_hw *);
	s32  (*init_hw)(काष्ठा e1000_hw *);
	s32  (*setup_link)(काष्ठा e1000_hw *);
	व्योम (*ग_लिखो_vfta)(काष्ठा e1000_hw *, u32, u32);
	व्योम (*mta_set)(काष्ठा e1000_hw *, u32);
	व्योम (*rar_set)(काष्ठा e1000_hw *, u8*, u32);
	s32  (*पढ़ो_mac_addr)(काष्ठा e1000_hw *);
	s32  (*set_vfta)(काष्ठा e1000_hw *, u16, bool);
पूर्ण;

काष्ठा e1000_mac_info अणु
	काष्ठा e1000_mac_operations ops;
	u8 addr[6];
	u8 perm_addr[6];

	क्रमागत e1000_mac_type type;

	u16 mta_reg_count;
	u16 rar_entry_count;

	bool get_link_status;
पूर्ण;

काष्ठा e1000_mbx_operations अणु
	s32 (*init_params)(काष्ठा e1000_hw *hw);
	s32 (*पढ़ो)(काष्ठा e1000_hw *, u32 *, u16);
	s32 (*ग_लिखो)(काष्ठा e1000_hw *, u32 *, u16);
	s32 (*पढ़ो_posted)(काष्ठा e1000_hw *, u32 *, u16);
	s32 (*ग_लिखो_posted)(काष्ठा e1000_hw *, u32 *, u16);
	s32 (*check_क्रम_msg)(काष्ठा e1000_hw *);
	s32 (*check_क्रम_ack)(काष्ठा e1000_hw *);
	s32 (*check_क्रम_rst)(काष्ठा e1000_hw *);
पूर्ण;

काष्ठा e1000_mbx_stats अणु
	u32 msgs_tx;
	u32 msgs_rx;

	u32 acks;
	u32 reqs;
	u32 rsts;
पूर्ण;

काष्ठा e1000_mbx_info अणु
	काष्ठा e1000_mbx_operations ops;
	काष्ठा e1000_mbx_stats stats;
	u32 समयout;
	u32 usec_delay;
	u16 size;
पूर्ण;

काष्ठा e1000_dev_spec_vf अणु
	u32 vf_number;
	u32 v2p_mailbox;
पूर्ण;

काष्ठा e1000_hw अणु
	व्योम *back;

	u8 __iomem *hw_addr;
	u8 __iomem *flash_address;
	अचिन्हित दीर्घ io_base;

	काष्ठा e1000_mac_info  mac;
	काष्ठा e1000_mbx_info mbx;
	spinlock_t mbx_lock;		/* serializes mailbox ops */

	जोड़ अणु
		काष्ठा e1000_dev_spec_vf vf;
	पूर्ण dev_spec;

	u16 device_id;
	u16 subप्रणाली_venकरोr_id;
	u16 subप्रणाली_device_id;
	u16 venकरोr_id;

	u8  revision_id;
पूर्ण;

/* These functions must be implemented by drivers */
व्योम e1000_rlpml_set_vf(काष्ठा e1000_hw *, u16);
व्योम e1000_init_function_poपूर्णांकers_vf(काष्ठा e1000_hw *hw);

#पूर्ण_अगर /* _E1000_VF_H_ */
