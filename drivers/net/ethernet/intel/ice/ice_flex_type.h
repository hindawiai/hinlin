<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2019, Intel Corporation. */

#अगर_अघोषित _ICE_FLEX_TYPE_H_
#घोषणा _ICE_FLEX_TYPE_H_

#घोषणा ICE_FV_OFFSET_INVAL	0x1FF

/* Extraction Sequence (Field Vector) Table */
काष्ठा ice_fv_word अणु
	u8 prot_id;
	u16 off;		/* Offset within the protocol header */
	u8 resvrd;
पूर्ण __packed;

#घोषणा ICE_MAX_FV_WORDS 48
काष्ठा ice_fv अणु
	काष्ठा ice_fv_word ew[ICE_MAX_FV_WORDS];
पूर्ण;

/* Package and segment headers and tables */
काष्ठा ice_pkg_hdr अणु
	काष्ठा ice_pkg_ver pkg_क्रमmat_ver;
	__le32 seg_count;
	__le32 seg_offset[];
पूर्ण;

/* generic segment */
काष्ठा ice_generic_seg_hdr अणु
#घोषणा SEGMENT_TYPE_METADATA	0x00000001
#घोषणा SEGMENT_TYPE_ICE	0x00000010
	__le32 seg_type;
	काष्ठा ice_pkg_ver seg_क्रमmat_ver;
	__le32 seg_size;
	अक्षर seg_id[ICE_PKG_NAME_SIZE];
पूर्ण;

/* ice specअगरic segment */

जोड़ ice_device_id अणु
	काष्ठा अणु
		__le16 device_id;
		__le16 venकरोr_id;
	पूर्ण dev_vend_id;
	__le32 id;
पूर्ण;

काष्ठा ice_device_id_entry अणु
	जोड़ ice_device_id device;
	जोड़ ice_device_id sub_device;
पूर्ण;

काष्ठा ice_seg अणु
	काष्ठा ice_generic_seg_hdr hdr;
	__le32 device_table_count;
	काष्ठा ice_device_id_entry device_table[];
पूर्ण;

काष्ठा ice_nvm_table अणु
	__le32 table_count;
	__le32 vers[];
पूर्ण;

काष्ठा ice_buf अणु
#घोषणा ICE_PKG_BUF_SIZE	4096
	u8 buf[ICE_PKG_BUF_SIZE];
पूर्ण;

काष्ठा ice_buf_table अणु
	__le32 buf_count;
	काष्ठा ice_buf buf_array[];
पूर्ण;

/* global metadata specअगरic segment */
काष्ठा ice_global_metadata_seg अणु
	काष्ठा ice_generic_seg_hdr hdr;
	काष्ठा ice_pkg_ver pkg_ver;
	__le32 rsvd;
	अक्षर pkg_name[ICE_PKG_NAME_SIZE];
पूर्ण;

#घोषणा ICE_MIN_S_OFF		12
#घोषणा ICE_MAX_S_OFF		4095
#घोषणा ICE_MIN_S_SZ		1
#घोषणा ICE_MAX_S_SZ		4084

/* section inक्रमmation */
काष्ठा ice_section_entry अणु
	__le32 type;
	__le16 offset;
	__le16 size;
पूर्ण;

#घोषणा ICE_MIN_S_COUNT		1
#घोषणा ICE_MAX_S_COUNT		511
#घोषणा ICE_MIN_S_DATA_END	12
#घोषणा ICE_MAX_S_DATA_END	4096

#घोषणा ICE_METADATA_BUF	0x80000000

काष्ठा ice_buf_hdr अणु
	__le16 section_count;
	__le16 data_end;
	काष्ठा ice_section_entry section_entry[];
पूर्ण;

#घोषणा ICE_MAX_ENTRIES_IN_BUF(hd_sz, ent_sz) ((ICE_PKG_BUF_SIZE - \
	काष्ठा_size((काष्ठा ice_buf_hdr *)0, section_entry, 1) - (hd_sz)) /\
	(ent_sz))

/* ice package section IDs */
#घोषणा ICE_SID_METADATA		1
#घोषणा ICE_SID_XLT0_SW			10
#घोषणा ICE_SID_XLT_KEY_BUILDER_SW	11
#घोषणा ICE_SID_XLT1_SW			12
#घोषणा ICE_SID_XLT2_SW			13
#घोषणा ICE_SID_PROFID_TCAM_SW		14
#घोषणा ICE_SID_PROFID_REसूची_SW		15
#घोषणा ICE_SID_FLD_VEC_SW		16
#घोषणा ICE_SID_CDID_KEY_BUILDER_SW	17

काष्ठा ice_meta_sect अणु
	काष्ठा ice_pkg_ver ver;
#घोषणा ICE_META_SECT_NAME_SIZE	28
	अक्षर name[ICE_META_SECT_NAME_SIZE];
	__le32 track_id;
पूर्ण;

#घोषणा ICE_SID_CDID_REसूची_SW		18

#घोषणा ICE_SID_XLT0_ACL		20
#घोषणा ICE_SID_XLT_KEY_BUILDER_ACL	21
#घोषणा ICE_SID_XLT1_ACL		22
#घोषणा ICE_SID_XLT2_ACL		23
#घोषणा ICE_SID_PROFID_TCAM_ACL		24
#घोषणा ICE_SID_PROFID_REसूची_ACL	25
#घोषणा ICE_SID_FLD_VEC_ACL		26
#घोषणा ICE_SID_CDID_KEY_BUILDER_ACL	27
#घोषणा ICE_SID_CDID_REसूची_ACL		28

#घोषणा ICE_SID_XLT0_FD			30
#घोषणा ICE_SID_XLT_KEY_BUILDER_FD	31
#घोषणा ICE_SID_XLT1_FD			32
#घोषणा ICE_SID_XLT2_FD			33
#घोषणा ICE_SID_PROFID_TCAM_FD		34
#घोषणा ICE_SID_PROFID_REसूची_FD		35
#घोषणा ICE_SID_FLD_VEC_FD		36
#घोषणा ICE_SID_CDID_KEY_BUILDER_FD	37
#घोषणा ICE_SID_CDID_REसूची_FD		38

#घोषणा ICE_SID_XLT0_RSS		40
#घोषणा ICE_SID_XLT_KEY_BUILDER_RSS	41
#घोषणा ICE_SID_XLT1_RSS		42
#घोषणा ICE_SID_XLT2_RSS		43
#घोषणा ICE_SID_PROFID_TCAM_RSS		44
#घोषणा ICE_SID_PROFID_REसूची_RSS	45
#घोषणा ICE_SID_FLD_VEC_RSS		46
#घोषणा ICE_SID_CDID_KEY_BUILDER_RSS	47
#घोषणा ICE_SID_CDID_REसूची_RSS		48

#घोषणा ICE_SID_RXPARSER_BOOST_TCAM	56
#घोषणा ICE_SID_TXPARSER_BOOST_TCAM	66

#घोषणा ICE_SID_XLT0_PE			80
#घोषणा ICE_SID_XLT_KEY_BUILDER_PE	81
#घोषणा ICE_SID_XLT1_PE			82
#घोषणा ICE_SID_XLT2_PE			83
#घोषणा ICE_SID_PROFID_TCAM_PE		84
#घोषणा ICE_SID_PROFID_REसूची_PE		85
#घोषणा ICE_SID_FLD_VEC_PE		86
#घोषणा ICE_SID_CDID_KEY_BUILDER_PE	87
#घोषणा ICE_SID_CDID_REसूची_PE		88

/* Label Metadata section IDs */
#घोषणा ICE_SID_LBL_FIRST		0x80000010
#घोषणा ICE_SID_LBL_RXPARSER_TMEM	0x80000018
/* The following define MUST be updated to reflect the last label section ID */
#घोषणा ICE_SID_LBL_LAST		0x80000038

क्रमागत ice_block अणु
	ICE_BLK_SW = 0,
	ICE_BLK_ACL,
	ICE_BLK_FD,
	ICE_BLK_RSS,
	ICE_BLK_PE,
	ICE_BLK_COUNT
पूर्ण;

क्रमागत ice_sect अणु
	ICE_XLT0 = 0,
	ICE_XLT_KB,
	ICE_XLT1,
	ICE_XLT2,
	ICE_PROF_TCAM,
	ICE_PROF_REसूची,
	ICE_VEC_TBL,
	ICE_CDID_KB,
	ICE_CDID_REसूची,
	ICE_SECT_COUNT
पूर्ण;

#घोषणा ICE_MAC_IPV4_GTPU_IPV4_FRAG	331
#घोषणा ICE_MAC_IPV4_GTPU_IPV4_PAY	332
#घोषणा ICE_MAC_IPV4_GTPU_IPV4_UDP_PAY	333
#घोषणा ICE_MAC_IPV4_GTPU_IPV4_TCP	334
#घोषणा ICE_MAC_IPV4_GTPU_IPV4_ICMP	335
#घोषणा ICE_MAC_IPV6_GTPU_IPV4_FRAG	336
#घोषणा ICE_MAC_IPV6_GTPU_IPV4_PAY	337
#घोषणा ICE_MAC_IPV6_GTPU_IPV4_UDP_PAY	338
#घोषणा ICE_MAC_IPV6_GTPU_IPV4_TCP	339
#घोषणा ICE_MAC_IPV6_GTPU_IPV4_ICMP	340
#घोषणा ICE_MAC_IPV4_GTPU_IPV6_FRAG	341
#घोषणा ICE_MAC_IPV4_GTPU_IPV6_PAY	342
#घोषणा ICE_MAC_IPV4_GTPU_IPV6_UDP_PAY	343
#घोषणा ICE_MAC_IPV4_GTPU_IPV6_TCP	344
#घोषणा ICE_MAC_IPV4_GTPU_IPV6_ICMPV6	345
#घोषणा ICE_MAC_IPV6_GTPU_IPV6_FRAG	346
#घोषणा ICE_MAC_IPV6_GTPU_IPV6_PAY	347
#घोषणा ICE_MAC_IPV6_GTPU_IPV6_UDP_PAY	348
#घोषणा ICE_MAC_IPV6_GTPU_IPV6_TCP	349
#घोषणा ICE_MAC_IPV6_GTPU_IPV6_ICMPV6	350

/* Attributes that can modअगरy PTYPE definitions.
 *
 * These values will represent special attributes क्रम PTYPEs, which will
 * resolve पूर्णांकo metadata packet flags definitions that can be used in the TCAM
 * क्रम identअगरying a PTYPE with specअगरic अक्षरacteristics.
 */
क्रमागत ice_ptype_attrib_type अणु
	/* GTP PTYPEs */
	ICE_PTYPE_ATTR_GTP_PDU_EH,
	ICE_PTYPE_ATTR_GTP_SESSION,
	ICE_PTYPE_ATTR_GTP_DOWNLINK,
	ICE_PTYPE_ATTR_GTP_UPLINK,
पूर्ण;

काष्ठा ice_ptype_attrib_info अणु
	u16 flags;
	u16 mask;
पूर्ण;

/* TCAM flag definitions */
#घोषणा ICE_GTP_PDU			BIT(14)
#घोषणा ICE_GTP_PDU_LINK		BIT(13)

/* GTP attributes */
#घोषणा ICE_GTP_PDU_FLAG_MASK		(ICE_GTP_PDU)
#घोषणा ICE_GTP_PDU_EH			ICE_GTP_PDU

#घोषणा ICE_GTP_FLAGS_MASK		(ICE_GTP_PDU | ICE_GTP_PDU_LINK)
#घोषणा ICE_GTP_SESSION			0
#घोषणा ICE_GTP_DOWNLINK		ICE_GTP_PDU
#घोषणा ICE_GTP_UPLINK			(ICE_GTP_PDU | ICE_GTP_PDU_LINK)

काष्ठा ice_ptype_attributes अणु
	u16 ptype;
	क्रमागत ice_ptype_attrib_type attrib;
पूर्ण;

/* package labels */
काष्ठा ice_label अणु
	__le16 value;
#घोषणा ICE_PKG_LABEL_SIZE	64
	अक्षर name[ICE_PKG_LABEL_SIZE];
पूर्ण;

काष्ठा ice_label_section अणु
	__le16 count;
	काष्ठा ice_label label[];
पूर्ण;

#घोषणा ICE_MAX_LABELS_IN_BUF ICE_MAX_ENTRIES_IN_BUF( \
	काष्ठा_size((काष्ठा ice_label_section *)0, label, 1) - \
	माप(काष्ठा ice_label), माप(काष्ठा ice_label))

काष्ठा ice_sw_fv_section अणु
	__le16 count;
	__le16 base_offset;
	काष्ठा ice_fv fv[];
पूर्ण;

/* The BOOST TCAM stores the match packet header in reverse order, meaning
 * the fields are reversed; in addition, this means that the normally big endian
 * fields of the packet are now little endian.
 */
काष्ठा ice_boost_key_value अणु
#घोषणा ICE_BOOST_REMAINING_HV_KEY	15
	u8 reमुख्यing_hv_key[ICE_BOOST_REMAINING_HV_KEY];
	__le16 hv_dst_port_key;
	__le16 hv_src_port_key;
	u8 tcam_search_key;
पूर्ण __packed;

काष्ठा ice_boost_key अणु
	काष्ठा ice_boost_key_value key;
	काष्ठा ice_boost_key_value key2;
पूर्ण;

/* package Boost TCAM entry */
काष्ठा ice_boost_tcam_entry अणु
	__le16 addr;
	__le16 reserved;
	/* अवरोध up the 40 bytes of key पूर्णांकo dअगरferent fields */
	काष्ठा ice_boost_key key;
	u8 boost_hit_index_group;
	/* The following contains bitfields which are not on byte boundaries.
	 * These fields are currently unused by driver software.
	 */
#घोषणा ICE_BOOST_BIT_FIELDS		43
	u8 bit_fields[ICE_BOOST_BIT_FIELDS];
पूर्ण;

काष्ठा ice_boost_tcam_section अणु
	__le16 count;
	__le16 reserved;
	काष्ठा ice_boost_tcam_entry tcam[];
पूर्ण;

#घोषणा ICE_MAX_BST_TCAMS_IN_BUF ICE_MAX_ENTRIES_IN_BUF( \
	काष्ठा_size((काष्ठा ice_boost_tcam_section *)0, tcam, 1) - \
	माप(काष्ठा ice_boost_tcam_entry), \
	माप(काष्ठा ice_boost_tcam_entry))

काष्ठा ice_xlt1_section अणु
	__le16 count;
	__le16 offset;
	u8 value[];
पूर्ण;

काष्ठा ice_xlt2_section अणु
	__le16 count;
	__le16 offset;
	__le16 value[];
पूर्ण;

काष्ठा ice_prof_redir_section अणु
	__le16 count;
	__le16 offset;
	u8 redir_value[];
पूर्ण;

/* package buffer building */

काष्ठा ice_buf_build अणु
	काष्ठा ice_buf buf;
	u16 reserved_section_table_entries;
पूर्ण;

काष्ठा ice_pkg_क्रमागत अणु
	काष्ठा ice_buf_table *buf_table;
	u32 buf_idx;

	u32 type;
	काष्ठा ice_buf_hdr *buf;
	u32 sect_idx;
	व्योम *sect;
	u32 sect_type;

	u32 entry_idx;
	व्योम *(*handler)(u32 sect_type, व्योम *section, u32 index, u32 *offset);
पूर्ण;

/* Tunnel enabling */

क्रमागत ice_tunnel_type अणु
	TNL_VXLAN = 0,
	TNL_GENEVE,
	__TNL_TYPE_CNT,
	TNL_LAST = 0xFF,
	TNL_ALL = 0xFF,
पूर्ण;

काष्ठा ice_tunnel_type_scan अणु
	क्रमागत ice_tunnel_type type;
	स्थिर अक्षर *label_prefix;
पूर्ण;

काष्ठा ice_tunnel_entry अणु
	क्रमागत ice_tunnel_type type;
	u16 boost_addr;
	u16 port;
	काष्ठा ice_boost_tcam_entry *boost_entry;
	u8 valid;
पूर्ण;

#घोषणा ICE_TUNNEL_MAX_ENTRIES	16

काष्ठा ice_tunnel_table अणु
	काष्ठा ice_tunnel_entry tbl[ICE_TUNNEL_MAX_ENTRIES];
	u16 count;
	u16 valid_count[__TNL_TYPE_CNT];
पूर्ण;

काष्ठा ice_pkg_es अणु
	__le16 count;
	__le16 offset;
	काष्ठा ice_fv_word es[];
पूर्ण;

काष्ठा ice_es अणु
	u32 sid;
	u16 count;
	u16 fvw;
	u16 *ref_count;
	u32 *mask_ena;
	काष्ठा list_head prof_map;
	काष्ठा ice_fv_word *t;
	काष्ठा mutex prof_map_lock;	/* protect access to profiles list */
	u8 *written;
	u8 reverse; /* set to true to reverse FV order */
पूर्ण;

/* PTYPE Group management */

/* Note: XLT1 table takes 13-bit as input, and results in an 8-bit packet type
 * group (PTG) ID as output.
 *
 * Note: PTG 0 is the शेष packet type group and it is assumed that all PTYPE
 * are a part of this group until moved to a new PTG.
 */
#घोषणा ICE_DEFAULT_PTG	0

काष्ठा ice_ptg_entry अणु
	काष्ठा ice_ptg_ptype *first_ptype;
	u8 in_use;
पूर्ण;

काष्ठा ice_ptg_ptype अणु
	काष्ठा ice_ptg_ptype *next_ptype;
	u8 ptg;
पूर्ण;

#घोषणा ICE_MAX_TCAM_PER_PROखाता	32
#घोषणा ICE_MAX_PTG_PER_PROखाता		32

काष्ठा ice_prof_map अणु
	काष्ठा list_head list;
	u64 profile_cookie;
	u64 context;
	u8 prof_id;
	u8 ptg_cnt;
	u8 ptg[ICE_MAX_PTG_PER_PROखाता];
	काष्ठा ice_ptype_attrib_info attr[ICE_MAX_PTG_PER_PROखाता];
पूर्ण;

#घोषणा ICE_INVALID_TCAM	0xFFFF

काष्ठा ice_tcam_inf अणु
	u16 tcam_idx;
	काष्ठा ice_ptype_attrib_info attr;
	u8 ptg;
	u8 prof_id;
	u8 in_use;
पूर्ण;

काष्ठा ice_vsig_prof अणु
	काष्ठा list_head list;
	u64 profile_cookie;
	u8 prof_id;
	u8 tcam_count;
	काष्ठा ice_tcam_inf tcam[ICE_MAX_TCAM_PER_PROखाता];
पूर्ण;

काष्ठा ice_vsig_entry अणु
	काष्ठा list_head prop_lst;
	काष्ठा ice_vsig_vsi *first_vsi;
	u8 in_use;
पूर्ण;

काष्ठा ice_vsig_vsi अणु
	काष्ठा ice_vsig_vsi *next_vsi;
	u32 prop_mask;
	u16 changed;
	u16 vsig;
पूर्ण;

#घोषणा ICE_XLT1_CNT	1024
#घोषणा ICE_MAX_PTGS	256

/* XLT1 Table */
काष्ठा ice_xlt1 अणु
	काष्ठा ice_ptg_entry *ptg_tbl;
	काष्ठा ice_ptg_ptype *ptypes;
	u8 *t;
	u32 sid;
	u16 count;
पूर्ण;

#घोषणा ICE_XLT2_CNT	768
#घोषणा ICE_MAX_VSIGS	768

/* VSIG bit layout:
 * [0:12]: incremental VSIG index 1 to ICE_MAX_VSIGS
 * [13:15]: PF number of device
 */
#घोषणा ICE_VSIG_IDX_M	(0x1FFF)
#घोषणा ICE_PF_NUM_S	13
#घोषणा ICE_PF_NUM_M	(0x07 << ICE_PF_NUM_S)
#घोषणा ICE_VSIG_VALUE(vsig, pf_id) \
	((u16)((((u16)(vsig)) & ICE_VSIG_IDX_M) | \
	       (((u16)(pf_id) << ICE_PF_NUM_S) & ICE_PF_NUM_M)))
#घोषणा ICE_DEFAULT_VSIG	0

/* XLT2 Table */
काष्ठा ice_xlt2 अणु
	काष्ठा ice_vsig_entry *vsig_tbl;
	काष्ठा ice_vsig_vsi *vsis;
	u16 *t;
	u32 sid;
	u16 count;
पूर्ण;

/* Profile ID Management */
काष्ठा ice_prof_id_key अणु
	__le16 flags;
	u8 xlt1;
	__le16 xlt2_cdid;
पूर्ण __packed;

/* Keys are made up of two values, each one-half the size of the key.
 * For TCAM, the entire key is 80 bits wide (or 2, 40-bit wide values)
 */
#घोषणा ICE_TCAM_KEY_VAL_SZ	5
#घोषणा ICE_TCAM_KEY_SZ		(2 * ICE_TCAM_KEY_VAL_SZ)

काष्ठा ice_prof_tcam_entry अणु
	__le16 addr;
	u8 key[ICE_TCAM_KEY_SZ];
	u8 prof_id;
पूर्ण __packed;

काष्ठा ice_prof_id_section अणु
	__le16 count;
	काष्ठा ice_prof_tcam_entry entry[];
पूर्ण;

काष्ठा ice_prof_tcam अणु
	u32 sid;
	u16 count;
	u16 max_prof_id;
	काष्ठा ice_prof_tcam_entry *t;
	u8 cdid_bits; /* # CDID bits to use in key, 0, 2, 4, or 8 */
पूर्ण;

काष्ठा ice_prof_redir अणु
	u8 *t;
	u32 sid;
	u16 count;
पूर्ण;

काष्ठा ice_mask अणु
	u16 mask;	/* 16-bit mask */
	u16 idx;	/* index */
	u16 ref;	/* reference count */
	u8 in_use;	/* non-zero अगर used */
पूर्ण;

काष्ठा ice_masks अणु
	काष्ठा mutex lock; /* lock to protect this काष्ठाure */
	u16 first;	/* first mask owned by the PF */
	u16 count;	/* number of masks owned by the PF */
#घोषणा ICE_PROF_MASK_COUNT 32
	काष्ठा ice_mask masks[ICE_PROF_MASK_COUNT];
पूर्ण;

/* Tables per block */
काष्ठा ice_blk_info अणु
	काष्ठा ice_xlt1 xlt1;
	काष्ठा ice_xlt2 xlt2;
	काष्ठा ice_prof_tcam prof;
	काष्ठा ice_prof_redir prof_redir;
	काष्ठा ice_es es;
	काष्ठा ice_masks masks;
	u8 overग_लिखो; /* set to true to allow overग_लिखो of table entries */
	u8 is_list_init;
पूर्ण;

क्रमागत ice_chg_type अणु
	ICE_TCAM_NONE = 0,
	ICE_PTG_ES_ADD,
	ICE_TCAM_ADD,
	ICE_VSIG_ADD,
	ICE_VSIG_REM,
	ICE_VSI_MOVE,
पूर्ण;

काष्ठा ice_chs_chg अणु
	काष्ठा list_head list_entry;
	क्रमागत ice_chg_type type;

	u8 add_ptg;
	u8 add_vsig;
	u8 add_tcam_idx;
	u8 add_prof;
	u16 ptype;
	u8 ptg;
	u8 prof_id;
	u16 vsi;
	u16 vsig;
	u16 orig_vsig;
	u16 tcam_idx;
	काष्ठा ice_ptype_attrib_info attr;
पूर्ण;

#घोषणा ICE_FLOW_PTYPE_MAX		ICE_XLT1_CNT
#पूर्ण_अगर /* _ICE_FLEX_TYPE_H_ */
