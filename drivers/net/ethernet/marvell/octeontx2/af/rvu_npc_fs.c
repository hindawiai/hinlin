<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2020 Marvell.
 */

#समावेश <linux/bitfield.h>

#समावेश "rvu_struct.h"
#समावेश "rvu_reg.h"
#समावेश "rvu.h"
#समावेश "npc.h"

#घोषणा NPC_BYTESM		GENMASK_ULL(19, 16)
#घोषणा NPC_HDR_OFFSET		GENMASK_ULL(15, 8)
#घोषणा NPC_KEY_OFFSET		GENMASK_ULL(5, 0)
#घोषणा NPC_LDATA_EN		BIT_ULL(7)

अटल स्थिर अक्षर * स्थिर npc_flow_names[] = अणु
	[NPC_DMAC]	= "dmac",
	[NPC_SMAC]	= "smac",
	[NPC_ETYPE]	= "ether type",
	[NPC_OUTER_VID]	= "outer vlan id",
	[NPC_TOS]	= "tos",
	[NPC_SIP_IPV4]	= "ipv4 source ip",
	[NPC_DIP_IPV4]	= "ipv4 destination ip",
	[NPC_SIP_IPV6]	= "ipv6 source ip",
	[NPC_DIP_IPV6]	= "ipv6 destination ip",
	[NPC_IPPROTO_TCP] = "ip proto tcp",
	[NPC_IPPROTO_UDP] = "ip proto udp",
	[NPC_IPPROTO_SCTP] = "ip proto sctp",
	[NPC_IPPROTO_ICMP] = "ip proto icmp",
	[NPC_IPPROTO_ICMP6] = "ip proto icmp6",
	[NPC_IPPROTO_AH] = "ip proto AH",
	[NPC_IPPROTO_ESP] = "ip proto ESP",
	[NPC_SPORT_TCP]	= "tcp source port",
	[NPC_DPORT_TCP]	= "tcp destination port",
	[NPC_SPORT_UDP]	= "udp source port",
	[NPC_DPORT_UDP]	= "udp destination port",
	[NPC_SPORT_SCTP] = "sctp source port",
	[NPC_DPORT_SCTP] = "sctp destination port",
	[NPC_UNKNOWN]	= "unknown",
पूर्ण;

स्थिर अक्षर *npc_get_field_name(u8 hdr)
अणु
	अगर (hdr >= ARRAY_SIZE(npc_flow_names))
		वापस npc_flow_names[NPC_UNKNOWN];

	वापस npc_flow_names[hdr];
पूर्ण

/* Compute keyword masks and figure out the number of keywords a field
 * spans in the key.
 */
अटल व्योम npc_set_kw_masks(काष्ठा npc_mcam *mcam, u8 type,
			     u8 nr_bits, पूर्णांक start_kwi, पूर्णांक offset, u8 पूर्णांकf)
अणु
	काष्ठा npc_key_field *field = &mcam->rx_key_fields[type];
	u8 bits_in_kw;
	पूर्णांक max_kwi;

	अगर (mcam->banks_per_entry == 1)
		max_kwi = 1; /* NPC_MCAM_KEY_X1 */
	अन्यथा अगर (mcam->banks_per_entry == 2)
		max_kwi = 3; /* NPC_MCAM_KEY_X2 */
	अन्यथा
		max_kwi = 6; /* NPC_MCAM_KEY_X4 */

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		field = &mcam->tx_key_fields[type];

	अगर (offset + nr_bits <= 64) अणु
		/* one KW only */
		अगर (start_kwi > max_kwi)
			वापस;
		field->kw_mask[start_kwi] |= GENMASK_ULL(nr_bits - 1, 0)
					     << offset;
		field->nr_kws = 1;
	पूर्ण अन्यथा अगर (offset + nr_bits > 64 &&
		   offset + nr_bits <= 128) अणु
		/* two KWs */
		अगर (start_kwi + 1 > max_kwi)
			वापस;
		/* first KW mask */
		bits_in_kw = 64 - offset;
		field->kw_mask[start_kwi] |= GENMASK_ULL(bits_in_kw - 1, 0)
					     << offset;
		/* second KW mask i.e. mask क्रम rest of bits */
		bits_in_kw = nr_bits + offset - 64;
		field->kw_mask[start_kwi + 1] |= GENMASK_ULL(bits_in_kw - 1, 0);
		field->nr_kws = 2;
	पूर्ण अन्यथा अणु
		/* three KWs */
		अगर (start_kwi + 2 > max_kwi)
			वापस;
		/* first KW mask */
		bits_in_kw = 64 - offset;
		field->kw_mask[start_kwi] |= GENMASK_ULL(bits_in_kw - 1, 0)
					     << offset;
		/* second KW mask */
		field->kw_mask[start_kwi + 1] = ~0ULL;
		/* third KW mask i.e. mask क्रम rest of bits */
		bits_in_kw = nr_bits + offset - 128;
		field->kw_mask[start_kwi + 2] |= GENMASK_ULL(bits_in_kw - 1, 0);
		field->nr_kws = 3;
	पूर्ण
पूर्ण

/* Helper function to figure out whether field exists in the key */
अटल bool npc_is_field_present(काष्ठा rvu *rvu, क्रमागत key_fields type, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा npc_key_field *input;

	input  = &mcam->rx_key_fields[type];
	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		input  = &mcam->tx_key_fields[type];

	वापस input->nr_kws > 0;
पूर्ण

अटल bool npc_is_same(काष्ठा npc_key_field *input,
			काष्ठा npc_key_field *field)
अणु
	पूर्णांक ret;

	ret = स_भेद(&input->layer_mdata, &field->layer_mdata,
		     माप(काष्ठा npc_layer_mdata));
	वापस ret == 0;
पूर्ण

अटल व्योम npc_set_layer_mdata(काष्ठा npc_mcam *mcam, क्रमागत key_fields type,
				u64 cfg, u8 lid, u8 lt, u8 पूर्णांकf)
अणु
	काष्ठा npc_key_field *input = &mcam->rx_key_fields[type];

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		input = &mcam->tx_key_fields[type];

	input->layer_mdata.hdr = FIELD_GET(NPC_HDR_OFFSET, cfg);
	input->layer_mdata.key = FIELD_GET(NPC_KEY_OFFSET, cfg);
	input->layer_mdata.len = FIELD_GET(NPC_BYTESM, cfg) + 1;
	input->layer_mdata.ltype = lt;
	input->layer_mdata.lid = lid;
पूर्ण

अटल bool npc_check_overlap_fields(काष्ठा npc_key_field *input1,
				     काष्ठा npc_key_field *input2)
अणु
	पूर्णांक kwi;

	/* Fields with same layer id and dअगरferent ltypes are mutually
	 * exclusive hence they can be overlapped
	 */
	अगर (input1->layer_mdata.lid == input2->layer_mdata.lid &&
	    input1->layer_mdata.ltype != input2->layer_mdata.ltype)
		वापस false;

	क्रम (kwi = 0; kwi < NPC_MAX_KWS_IN_KEY; kwi++) अणु
		अगर (input1->kw_mask[kwi] & input2->kw_mask[kwi])
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Helper function to check whether given field overlaps with any other fields
 * in the key. Due to limitations on key size and the key extraction profile in
 * use higher layers can overग_लिखो lower layer's header fields. Hence overlap
 * needs to be checked.
 */
अटल bool npc_check_overlap(काष्ठा rvu *rvu, पूर्णांक blkaddr,
			      क्रमागत key_fields type, u8 start_lid, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा npc_key_field *dummy, *input;
	पूर्णांक start_kwi, offset;
	u8 nr_bits, lid, lt, ld;
	u64 cfg;

	dummy = &mcam->rx_key_fields[NPC_UNKNOWN];
	input = &mcam->rx_key_fields[type];

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf)) अणु
		dummy = &mcam->tx_key_fields[NPC_UNKNOWN];
		input = &mcam->tx_key_fields[type];
	पूर्ण

	क्रम (lid = start_lid; lid < NPC_MAX_LID; lid++) अणु
		क्रम (lt = 0; lt < NPC_MAX_LT; lt++) अणु
			क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
				cfg = rvu_पढ़ो64(rvu, blkaddr,
						 NPC_AF_INTFX_LIDX_LTX_LDX_CFG
						 (पूर्णांकf, lid, lt, ld));
				अगर (!FIELD_GET(NPC_LDATA_EN, cfg))
					जारी;
				स_रखो(dummy, 0, माप(काष्ठा npc_key_field));
				npc_set_layer_mdata(mcam, NPC_UNKNOWN, cfg,
						    lid, lt, पूर्णांकf);
				/* exclude input */
				अगर (npc_is_same(input, dummy))
					जारी;
				start_kwi = dummy->layer_mdata.key / 8;
				offset = (dummy->layer_mdata.key * 8) % 64;
				nr_bits = dummy->layer_mdata.len * 8;
				/* क्रमm KW masks */
				npc_set_kw_masks(mcam, NPC_UNKNOWN, nr_bits,
						 start_kwi, offset, पूर्णांकf);
				/* check any input field bits falls in any
				 * other field bits.
				 */
				अगर (npc_check_overlap_fields(dummy, input))
					वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool npc_check_field(काष्ठा rvu *rvu, पूर्णांक blkaddr, क्रमागत key_fields type,
			    u8 पूर्णांकf)
अणु
	अगर (!npc_is_field_present(rvu, type, पूर्णांकf) ||
	    npc_check_overlap(rvu, blkaddr, type, 0, पूर्णांकf))
		वापस false;
	वापस true;
पूर्ण

अटल व्योम npc_scan_parse_result(काष्ठा npc_mcam *mcam, u8 bit_number,
				  u8 key_nibble, u8 पूर्णांकf)
अणु
	u8 offset = (key_nibble * 4) % 64; /* offset within key word */
	u8 kwi = (key_nibble * 4) / 64; /* which word in key */
	u8 nr_bits = 4; /* bits in a nibble */
	u8 type;

	चयन (bit_number) अणु
	हाल 0 ... 2:
		type = NPC_CHAN;
		अवरोध;
	हाल 3:
		type = NPC_ERRLEV;
		अवरोध;
	हाल 4 ... 5:
		type = NPC_ERRCODE;
		अवरोध;
	हाल 6:
		type = NPC_LXMB;
		अवरोध;
	/* check क्रम LTYPE only as of now */
	हाल 9:
		type = NPC_LA;
		अवरोध;
	हाल 12:
		type = NPC_LB;
		अवरोध;
	हाल 15:
		type = NPC_LC;
		अवरोध;
	हाल 18:
		type = NPC_LD;
		अवरोध;
	हाल 21:
		type = NPC_LE;
		अवरोध;
	हाल 24:
		type = NPC_LF;
		अवरोध;
	हाल 27:
		type = NPC_LG;
		अवरोध;
	हाल 30:
		type = NPC_LH;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	npc_set_kw_masks(mcam, type, nr_bits, kwi, offset, पूर्णांकf);
पूर्ण

अटल व्योम npc_handle_multi_layer_fields(काष्ठा rvu *rvu, पूर्णांक blkaddr, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा npc_key_field *key_fields;
	/* Ether type can come from three layers
	 * (ethernet, single tagged, द्विगुन tagged)
	 */
	काष्ठा npc_key_field *etype_ether;
	काष्ठा npc_key_field *etype_tag1;
	काष्ठा npc_key_field *etype_tag2;
	/* Outer VLAN TCI can come from two layers
	 * (single tagged, द्विगुन tagged)
	 */
	काष्ठा npc_key_field *vlan_tag1;
	काष्ठा npc_key_field *vlan_tag2;
	u64 *features;
	u8 start_lid;
	पूर्णांक i;

	key_fields = mcam->rx_key_fields;
	features = &mcam->rx_features;

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf)) अणु
		key_fields = mcam->tx_key_fields;
		features = &mcam->tx_features;
	पूर्ण

	/* Handle header fields which can come from multiple layers like
	 * etype, outer vlan tci. These fields should have same position in
	 * the key otherwise to install a mcam rule more than one entry is
	 * needed which complicates mcam space management.
	 */
	etype_ether = &key_fields[NPC_ETYPE_ETHER];
	etype_tag1 = &key_fields[NPC_ETYPE_TAG1];
	etype_tag2 = &key_fields[NPC_ETYPE_TAG2];
	vlan_tag1 = &key_fields[NPC_VLAN_TAG1];
	vlan_tag2 = &key_fields[NPC_VLAN_TAG2];

	/* अगर key profile programmed करोes not extract Ethertype at all */
	अगर (!etype_ether->nr_kws && !etype_tag1->nr_kws && !etype_tag2->nr_kws)
		जाओ vlan_tci;

	/* अगर key profile programmed extracts Ethertype from one layer */
	अगर (etype_ether->nr_kws && !etype_tag1->nr_kws && !etype_tag2->nr_kws)
		key_fields[NPC_ETYPE] = *etype_ether;
	अगर (!etype_ether->nr_kws && etype_tag1->nr_kws && !etype_tag2->nr_kws)
		key_fields[NPC_ETYPE] = *etype_tag1;
	अगर (!etype_ether->nr_kws && !etype_tag1->nr_kws && etype_tag2->nr_kws)
		key_fields[NPC_ETYPE] = *etype_tag2;

	/* अगर key profile programmed extracts Ethertype from multiple layers */
	अगर (etype_ether->nr_kws && etype_tag1->nr_kws) अणु
		क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
			अगर (etype_ether->kw_mask[i] != etype_tag1->kw_mask[i])
				जाओ vlan_tci;
		पूर्ण
		key_fields[NPC_ETYPE] = *etype_tag1;
	पूर्ण
	अगर (etype_ether->nr_kws && etype_tag2->nr_kws) अणु
		क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
			अगर (etype_ether->kw_mask[i] != etype_tag2->kw_mask[i])
				जाओ vlan_tci;
		पूर्ण
		key_fields[NPC_ETYPE] = *etype_tag2;
	पूर्ण
	अगर (etype_tag1->nr_kws && etype_tag2->nr_kws) अणु
		क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
			अगर (etype_tag1->kw_mask[i] != etype_tag2->kw_mask[i])
				जाओ vlan_tci;
		पूर्ण
		key_fields[NPC_ETYPE] = *etype_tag2;
	पूर्ण

	/* check none of higher layers overग_लिखो Ethertype */
	start_lid = key_fields[NPC_ETYPE].layer_mdata.lid + 1;
	अगर (npc_check_overlap(rvu, blkaddr, NPC_ETYPE, start_lid, पूर्णांकf))
		जाओ vlan_tci;
	*features |= BIT_ULL(NPC_ETYPE);
vlan_tci:
	/* अगर key profile करोes not extract outer vlan tci at all */
	अगर (!vlan_tag1->nr_kws && !vlan_tag2->nr_kws)
		जाओ करोne;

	/* अगर key profile extracts outer vlan tci from one layer */
	अगर (vlan_tag1->nr_kws && !vlan_tag2->nr_kws)
		key_fields[NPC_OUTER_VID] = *vlan_tag1;
	अगर (!vlan_tag1->nr_kws && vlan_tag2->nr_kws)
		key_fields[NPC_OUTER_VID] = *vlan_tag2;

	/* अगर key profile extracts outer vlan tci from multiple layers */
	अगर (vlan_tag1->nr_kws && vlan_tag2->nr_kws) अणु
		क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
			अगर (vlan_tag1->kw_mask[i] != vlan_tag2->kw_mask[i])
				जाओ करोne;
		पूर्ण
		key_fields[NPC_OUTER_VID] = *vlan_tag2;
	पूर्ण
	/* check none of higher layers overग_लिखो outer vlan tci */
	start_lid = key_fields[NPC_OUTER_VID].layer_mdata.lid + 1;
	अगर (npc_check_overlap(rvu, blkaddr, NPC_OUTER_VID, start_lid, पूर्णांकf))
		जाओ करोne;
	*features |= BIT_ULL(NPC_OUTER_VID);
करोne:
	वापस;
पूर्ण

अटल व्योम npc_scan_ldata(काष्ठा rvu *rvu, पूर्णांक blkaddr, u8 lid,
			   u8 lt, u64 cfg, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u8 hdr, key, nr_bytes, bit_offset;
	u8 la_ltype, la_start;
	/* starting KW index and starting bit position */
	पूर्णांक start_kwi, offset;

	nr_bytes = FIELD_GET(NPC_BYTESM, cfg) + 1;
	hdr = FIELD_GET(NPC_HDR_OFFSET, cfg);
	key = FIELD_GET(NPC_KEY_OFFSET, cfg);
	start_kwi = key / 8;
	offset = (key * 8) % 64;

	/* For Tx, Layer A has NIX_INST_HDR_S(64 bytes) preceding
	 * ethernet header.
	 */
	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf)) अणु
		la_ltype = NPC_LT_LA_IH_NIX_ETHER;
		la_start = 8;
	पूर्ण अन्यथा अणु
		la_ltype = NPC_LT_LA_ETHER;
		la_start = 0;
	पूर्ण

#घोषणा NPC_SCAN_HDR(name, hlid, hlt, hstart, hlen)			       \
करो अणु									       \
	अगर (lid == (hlid) && lt == (hlt)) अणु				       \
		अगर ((hstart) >= hdr &&					       \
		    ((hstart) + (hlen)) <= (hdr + nr_bytes)) अणु	               \
			bit_offset = (hdr + nr_bytes - (hstart) - (hlen)) * 8; \
			npc_set_layer_mdata(mcam, (name), cfg, lid, lt, पूर्णांकf); \
			npc_set_kw_masks(mcam, (name), (hlen) * 8,	       \
					 start_kwi, offset + bit_offset, पूर्णांकf);\
		पूर्ण							       \
	पूर्ण								       \
पूर्ण जबतक (0)

	/* List LID, LTYPE, start offset from layer and length(in bytes) of
	 * packet header fields below.
	 * Example: Source IP is 4 bytes and starts at 12th byte of IP header
	 */
	NPC_SCAN_HDR(NPC_TOS, NPC_LID_LC, NPC_LT_LC_IP, 1, 1);
	NPC_SCAN_HDR(NPC_SIP_IPV4, NPC_LID_LC, NPC_LT_LC_IP, 12, 4);
	NPC_SCAN_HDR(NPC_DIP_IPV4, NPC_LID_LC, NPC_LT_LC_IP, 16, 4);
	NPC_SCAN_HDR(NPC_SIP_IPV6, NPC_LID_LC, NPC_LT_LC_IP6, 8, 16);
	NPC_SCAN_HDR(NPC_DIP_IPV6, NPC_LID_LC, NPC_LT_LC_IP6, 24, 16);
	NPC_SCAN_HDR(NPC_SPORT_UDP, NPC_LID_LD, NPC_LT_LD_UDP, 0, 2);
	NPC_SCAN_HDR(NPC_DPORT_UDP, NPC_LID_LD, NPC_LT_LD_UDP, 2, 2);
	NPC_SCAN_HDR(NPC_SPORT_TCP, NPC_LID_LD, NPC_LT_LD_TCP, 0, 2);
	NPC_SCAN_HDR(NPC_DPORT_TCP, NPC_LID_LD, NPC_LT_LD_TCP, 2, 2);
	NPC_SCAN_HDR(NPC_SPORT_SCTP, NPC_LID_LD, NPC_LT_LD_SCTP, 0, 2);
	NPC_SCAN_HDR(NPC_DPORT_SCTP, NPC_LID_LD, NPC_LT_LD_SCTP, 2, 2);
	NPC_SCAN_HDR(NPC_ETYPE_ETHER, NPC_LID_LA, NPC_LT_LA_ETHER, 12, 2);
	NPC_SCAN_HDR(NPC_ETYPE_TAG1, NPC_LID_LB, NPC_LT_LB_CTAG, 4, 2);
	NPC_SCAN_HDR(NPC_ETYPE_TAG2, NPC_LID_LB, NPC_LT_LB_STAG_QINQ, 8, 2);
	NPC_SCAN_HDR(NPC_VLAN_TAG1, NPC_LID_LB, NPC_LT_LB_CTAG, 2, 2);
	NPC_SCAN_HDR(NPC_VLAN_TAG2, NPC_LID_LB, NPC_LT_LB_STAG_QINQ, 2, 2);
	NPC_SCAN_HDR(NPC_DMAC, NPC_LID_LA, la_ltype, la_start, 6);
	NPC_SCAN_HDR(NPC_SMAC, NPC_LID_LA, la_ltype, la_start, 6);
	/* PF_FUNC is 2 bytes at 0th byte of NPC_LT_LA_IH_NIX_ETHER */
	NPC_SCAN_HDR(NPC_PF_FUNC, NPC_LID_LA, NPC_LT_LA_IH_NIX_ETHER, 0, 2);
पूर्ण

अटल व्योम npc_set_features(काष्ठा rvu *rvu, पूर्णांक blkaddr, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u64 *features = &mcam->rx_features;
	u64 tcp_udp_sctp;
	पूर्णांक hdr;

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		features = &mcam->tx_features;

	क्रम (hdr = NPC_DMAC; hdr < NPC_HEADER_FIELDS_MAX; hdr++) अणु
		अगर (npc_check_field(rvu, blkaddr, hdr, पूर्णांकf))
			*features |= BIT_ULL(hdr);
	पूर्ण

	tcp_udp_sctp = BIT_ULL(NPC_SPORT_TCP) | BIT_ULL(NPC_SPORT_UDP) |
		       BIT_ULL(NPC_DPORT_TCP) | BIT_ULL(NPC_DPORT_UDP) |
		       BIT_ULL(NPC_SPORT_SCTP) | BIT_ULL(NPC_DPORT_SCTP);

	/* क्रम tcp/udp/sctp corresponding layer type should be in the key */
	अगर (*features & tcp_udp_sctp) अणु
		अगर (!npc_check_field(rvu, blkaddr, NPC_LD, पूर्णांकf))
			*features &= ~tcp_udp_sctp;
		अन्यथा
			*features |= BIT_ULL(NPC_IPPROTO_TCP) |
				     BIT_ULL(NPC_IPPROTO_UDP) |
				     BIT_ULL(NPC_IPPROTO_SCTP);
	पूर्ण

	/* क्रम AH/ICMP/ICMPv6/, check अगर corresponding layer type is present in the key */
	अगर (npc_check_field(rvu, blkaddr, NPC_LD, पूर्णांकf)) अणु
		*features |= BIT_ULL(NPC_IPPROTO_AH);
		*features |= BIT_ULL(NPC_IPPROTO_ICMP);
		*features |= BIT_ULL(NPC_IPPROTO_ICMP6);
	पूर्ण

	/* क्रम ESP, check अगर corresponding layer type is present in the key */
	अगर (npc_check_field(rvu, blkaddr, NPC_LE, पूर्णांकf))
		*features |= BIT_ULL(NPC_IPPROTO_ESP);

	/* क्रम vlan corresponding layer type should be in the key */
	अगर (*features & BIT_ULL(NPC_OUTER_VID))
		अगर (!npc_check_field(rvu, blkaddr, NPC_LB, पूर्णांकf))
			*features &= ~BIT_ULL(NPC_OUTER_VID);
पूर्ण

/* Scan key extraction profile and record how fields of our पूर्णांकerest
 * fill the key काष्ठाure. Also verअगरy Channel and DMAC exists in
 * key and not overwritten by other header fields.
 */
अटल पूर्णांक npc_scan_kex(काष्ठा rvu *rvu, पूर्णांक blkaddr, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u8 lid, lt, ld, bitnr;
	u8 key_nibble = 0;
	u64 cfg;

	/* Scan and note how parse result is going to be in key.
	 * A bit set in PARSE_NIBBLE_ENA corresponds to a nibble from
	 * parse result in the key. The enabled nibbles from parse result
	 * will be concatenated in key.
	 */
	cfg = rvu_पढ़ो64(rvu, blkaddr, NPC_AF_INTFX_KEX_CFG(पूर्णांकf));
	cfg &= NPC_PARSE_NIBBLE;
	क्रम_each_set_bit(bitnr, (अचिन्हित दीर्घ *)&cfg, 31) अणु
		npc_scan_parse_result(mcam, bitnr, key_nibble, पूर्णांकf);
		key_nibble++;
	पूर्ण

	/* Scan and note how layer data is going to be in key */
	क्रम (lid = 0; lid < NPC_MAX_LID; lid++) अणु
		क्रम (lt = 0; lt < NPC_MAX_LT; lt++) अणु
			क्रम (ld = 0; ld < NPC_MAX_LD; ld++) अणु
				cfg = rvu_पढ़ो64(rvu, blkaddr,
						 NPC_AF_INTFX_LIDX_LTX_LDX_CFG
						 (पूर्णांकf, lid, lt, ld));
				अगर (!FIELD_GET(NPC_LDATA_EN, cfg))
					जारी;
				npc_scan_ldata(rvu, blkaddr, lid, lt, cfg,
					       पूर्णांकf);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npc_scan_verअगरy_kex(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	पूर्णांक err;

	err = npc_scan_kex(rvu, blkaddr, NIX_INTF_RX);
	अगर (err)
		वापस err;

	err = npc_scan_kex(rvu, blkaddr, NIX_INTF_TX);
	अगर (err)
		वापस err;

	/* Channel is mandatory */
	अगर (!npc_is_field_present(rvu, NPC_CHAN, NIX_INTF_RX)) अणु
		dev_err(rvu->dev, "Channel not present in Key\n");
		वापस -EINVAL;
	पूर्ण
	/* check that none of the fields overग_लिखो channel */
	अगर (npc_check_overlap(rvu, blkaddr, NPC_CHAN, 0, NIX_INTF_RX)) अणु
		dev_err(rvu->dev, "Channel cannot be overwritten\n");
		वापस -EINVAL;
	पूर्ण
	/* DMAC should be present in key क्रम unicast filter to work */
	अगर (!npc_is_field_present(rvu, NPC_DMAC, NIX_INTF_RX)) अणु
		dev_err(rvu->dev, "DMAC not present in Key\n");
		वापस -EINVAL;
	पूर्ण
	/* check that none of the fields overग_लिखो DMAC */
	अगर (npc_check_overlap(rvu, blkaddr, NPC_DMAC, 0, NIX_INTF_RX)) अणु
		dev_err(rvu->dev, "DMAC cannot be overwritten\n");
		वापस -EINVAL;
	पूर्ण

	npc_set_features(rvu, blkaddr, NIX_INTF_TX);
	npc_set_features(rvu, blkaddr, NIX_INTF_RX);
	npc_handle_multi_layer_fields(rvu, blkaddr, NIX_INTF_TX);
	npc_handle_multi_layer_fields(rvu, blkaddr, NIX_INTF_RX);

	वापस 0;
पूर्ण

पूर्णांक npc_flow_steering_init(काष्ठा rvu *rvu, पूर्णांक blkaddr)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;

	INIT_LIST_HEAD(&mcam->mcam_rules);

	वापस npc_scan_verअगरy_kex(rvu, blkaddr);
पूर्ण

अटल पूर्णांक npc_check_unsupported_flows(काष्ठा rvu *rvu, u64 features, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	u64 *mcam_features = &mcam->rx_features;
	u64 unsupported;
	u8 bit;

	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		mcam_features = &mcam->tx_features;

	unsupported = (*mcam_features ^ features) & ~(*mcam_features);
	अगर (unsupported) अणु
		dev_info(rvu->dev, "Unsupported flow(s):\n");
		क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&unsupported, 64)
			dev_info(rvu->dev, "%s ", npc_get_field_name(bit));
		वापस NIX_AF_ERR_NPC_KEY_NOT_SUPP;
	पूर्ण

	वापस 0;
पूर्ण

/* npc_update_entry - Based on the masks generated during
 * the key scanning, updates the given entry with value and
 * masks क्रम the field of पूर्णांकerest. Maximum 16 bytes of a packet
 * header can be extracted by HW hence lo and hi are sufficient.
 * When field bytes are less than or equal to 8 then hi should be
 * 0 क्रम value and mask.
 *
 * If exact match of value is required then mask should be all 1's.
 * If any bits in mask are 0 then corresponding bits in value are
 * करोnt care.
 */
अटल व्योम npc_update_entry(काष्ठा rvu *rvu, क्रमागत key_fields type,
			     काष्ठा mcam_entry *entry, u64 val_lo,
			     u64 val_hi, u64 mask_lo, u64 mask_hi, u8 पूर्णांकf)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा mcam_entry dummy = अणु अणु0पूर्ण पूर्ण;
	काष्ठा npc_key_field *field;
	u64 kw1, kw2, kw3;
	u8 shअगरt;
	पूर्णांक i;

	field = &mcam->rx_key_fields[type];
	अगर (is_npc_पूर्णांकf_tx(पूर्णांकf))
		field = &mcam->tx_key_fields[type];

	अगर (!field->nr_kws)
		वापस;

	क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
		अगर (!field->kw_mask[i])
			जारी;
		/* place key value in kw[x] */
		shअगरt = __ffs64(field->kw_mask[i]);
		/* update entry value */
		kw1 = (val_lo << shअगरt) & field->kw_mask[i];
		dummy.kw[i] = kw1;
		/* update entry mask */
		kw1 = (mask_lo << shअगरt) & field->kw_mask[i];
		dummy.kw_mask[i] = kw1;

		अगर (field->nr_kws == 1)
			अवरोध;
		/* place reमुख्यing bits of key value in kw[x + 1] */
		अगर (field->nr_kws == 2) अणु
			/* update entry value */
			kw2 = shअगरt ? val_lo >> (64 - shअगरt) : 0;
			kw2 |= (val_hi << shअगरt);
			kw2 &= field->kw_mask[i + 1];
			dummy.kw[i + 1] = kw2;
			/* update entry mask */
			kw2 = shअगरt ? mask_lo >> (64 - shअगरt) : 0;
			kw2 |= (mask_hi << shअगरt);
			kw2 &= field->kw_mask[i + 1];
			dummy.kw_mask[i + 1] = kw2;
			अवरोध;
		पूर्ण
		/* place reमुख्यing bits of key value in kw[x + 1], kw[x + 2] */
		अगर (field->nr_kws == 3) अणु
			/* update entry value */
			kw2 = shअगरt ? val_lo >> (64 - shअगरt) : 0;
			kw2 |= (val_hi << shअगरt);
			kw2 &= field->kw_mask[i + 1];
			kw3 = shअगरt ? val_hi >> (64 - shअगरt) : 0;
			kw3 &= field->kw_mask[i + 2];
			dummy.kw[i + 1] = kw2;
			dummy.kw[i + 2] = kw3;
			/* update entry mask */
			kw2 = shअगरt ? mask_lo >> (64 - shअगरt) : 0;
			kw2 |= (mask_hi << shअगरt);
			kw2 &= field->kw_mask[i + 1];
			kw3 = shअगरt ? mask_hi >> (64 - shअगरt) : 0;
			kw3 &= field->kw_mask[i + 2];
			dummy.kw_mask[i + 1] = kw2;
			dummy.kw_mask[i + 2] = kw3;
			अवरोध;
		पूर्ण
	पूर्ण
	/* dummy is पढ़ोy with values and masks क्रम given key
	 * field now clear and update input entry with those
	 */
	क्रम (i = 0; i < NPC_MAX_KWS_IN_KEY; i++) अणु
		अगर (!field->kw_mask[i])
			जारी;
		entry->kw[i] &= ~field->kw_mask[i];
		entry->kw_mask[i] &= ~field->kw_mask[i];

		entry->kw[i] |= dummy.kw[i];
		entry->kw_mask[i] |= dummy.kw_mask[i];
	पूर्ण
पूर्ण

#घोषणा IPV6_WORDS     4

अटल व्योम npc_update_ipv6_flow(काष्ठा rvu *rvu, काष्ठा mcam_entry *entry,
				 u64 features, काष्ठा flow_msg *pkt,
				 काष्ठा flow_msg *mask,
				 काष्ठा rvu_npc_mcam_rule *output, u8 पूर्णांकf)
अणु
	u32 src_ip[IPV6_WORDS], src_ip_mask[IPV6_WORDS];
	u32 dst_ip[IPV6_WORDS], dst_ip_mask[IPV6_WORDS];
	काष्ठा flow_msg *opkt = &output->packet;
	काष्ठा flow_msg *omask = &output->mask;
	u64 mask_lo, mask_hi;
	u64 val_lo, val_hi;

	/* For an ipv6 address fe80::2c68:63ff:fe5e:2d0a the packet
	 * values to be programmed in MCAM should as below:
	 * val_high: 0xfe80000000000000
	 * val_low: 0x2c6863fffe5e2d0a
	 */
	अगर (features & BIT_ULL(NPC_SIP_IPV6)) अणु
		be32_to_cpu_array(src_ip_mask, mask->ip6src, IPV6_WORDS);
		be32_to_cpu_array(src_ip, pkt->ip6src, IPV6_WORDS);

		mask_hi = (u64)src_ip_mask[0] << 32 | src_ip_mask[1];
		mask_lo = (u64)src_ip_mask[2] << 32 | src_ip_mask[3];
		val_hi = (u64)src_ip[0] << 32 | src_ip[1];
		val_lo = (u64)src_ip[2] << 32 | src_ip[3];

		npc_update_entry(rvu, NPC_SIP_IPV6, entry, val_lo, val_hi,
				 mask_lo, mask_hi, पूर्णांकf);
		स_नकल(opkt->ip6src, pkt->ip6src, माप(opkt->ip6src));
		स_नकल(omask->ip6src, mask->ip6src, माप(omask->ip6src));
	पूर्ण
	अगर (features & BIT_ULL(NPC_DIP_IPV6)) अणु
		be32_to_cpu_array(dst_ip_mask, mask->ip6dst, IPV6_WORDS);
		be32_to_cpu_array(dst_ip, pkt->ip6dst, IPV6_WORDS);

		mask_hi = (u64)dst_ip_mask[0] << 32 | dst_ip_mask[1];
		mask_lo = (u64)dst_ip_mask[2] << 32 | dst_ip_mask[3];
		val_hi = (u64)dst_ip[0] << 32 | dst_ip[1];
		val_lo = (u64)dst_ip[2] << 32 | dst_ip[3];

		npc_update_entry(rvu, NPC_DIP_IPV6, entry, val_lo, val_hi,
				 mask_lo, mask_hi, पूर्णांकf);
		स_नकल(opkt->ip6dst, pkt->ip6dst, माप(opkt->ip6dst));
		स_नकल(omask->ip6dst, mask->ip6dst, माप(omask->ip6dst));
	पूर्ण
पूर्ण

अटल व्योम npc_update_flow(काष्ठा rvu *rvu, काष्ठा mcam_entry *entry,
			    u64 features, काष्ठा flow_msg *pkt,
			    काष्ठा flow_msg *mask,
			    काष्ठा rvu_npc_mcam_rule *output, u8 पूर्णांकf)
अणु
	u64 dmac_mask = ether_addr_to_u64(mask->dmac);
	u64 smac_mask = ether_addr_to_u64(mask->smac);
	u64 dmac_val = ether_addr_to_u64(pkt->dmac);
	u64 smac_val = ether_addr_to_u64(pkt->smac);
	काष्ठा flow_msg *opkt = &output->packet;
	काष्ठा flow_msg *omask = &output->mask;

	अगर (!features)
		वापस;

	/* For tcp/udp/sctp LTYPE should be present in entry */
	अगर (features & BIT_ULL(NPC_IPPROTO_TCP))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_TCP,
				 0, ~0ULL, 0, पूर्णांकf);
	अगर (features & BIT_ULL(NPC_IPPROTO_UDP))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_UDP,
				 0, ~0ULL, 0, पूर्णांकf);
	अगर (features & BIT_ULL(NPC_IPPROTO_SCTP))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_SCTP,
				 0, ~0ULL, 0, पूर्णांकf);
	अगर (features & BIT_ULL(NPC_IPPROTO_ICMP))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_ICMP,
				 0, ~0ULL, 0, पूर्णांकf);
	अगर (features & BIT_ULL(NPC_IPPROTO_ICMP6))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_ICMP6,
				 0, ~0ULL, 0, पूर्णांकf);

	अगर (features & BIT_ULL(NPC_OUTER_VID))
		npc_update_entry(rvu, NPC_LB, entry,
				 NPC_LT_LB_STAG_QINQ | NPC_LT_LB_CTAG, 0,
				 NPC_LT_LB_STAG_QINQ & NPC_LT_LB_CTAG, 0, पूर्णांकf);

	/* For AH, LTYPE should be present in entry */
	अगर (features & BIT_ULL(NPC_IPPROTO_AH))
		npc_update_entry(rvu, NPC_LD, entry, NPC_LT_LD_AH,
				 0, ~0ULL, 0, पूर्णांकf);
	/* For ESP, LTYPE should be present in entry */
	अगर (features & BIT_ULL(NPC_IPPROTO_ESP))
		npc_update_entry(rvu, NPC_LE, entry, NPC_LT_LE_ESP,
				 0, ~0ULL, 0, पूर्णांकf);

#घोषणा NPC_WRITE_FLOW(field, member, val_lo, val_hi, mask_lo, mask_hi)	      \
करो अणु									      \
	अगर (features & BIT_ULL((field))) अणु				      \
		npc_update_entry(rvu, (field), entry, (val_lo), (val_hi),     \
				 (mask_lo), (mask_hi), पूर्णांकf);		      \
		स_नकल(&opkt->member, &pkt->member, माप(pkt->member));     \
		स_नकल(&omask->member, &mask->member, माप(mask->member));  \
	पूर्ण								      \
पूर्ण जबतक (0)

	NPC_WRITE_FLOW(NPC_DMAC, dmac, dmac_val, 0, dmac_mask, 0);
	NPC_WRITE_FLOW(NPC_SMAC, smac, smac_val, 0, smac_mask, 0);
	NPC_WRITE_FLOW(NPC_ETYPE, etype, ntohs(pkt->etype), 0,
		       ntohs(mask->etype), 0);
	NPC_WRITE_FLOW(NPC_TOS, tos, pkt->tos, 0, mask->tos, 0);
	NPC_WRITE_FLOW(NPC_SIP_IPV4, ip4src, ntohl(pkt->ip4src), 0,
		       ntohl(mask->ip4src), 0);
	NPC_WRITE_FLOW(NPC_DIP_IPV4, ip4dst, ntohl(pkt->ip4dst), 0,
		       ntohl(mask->ip4dst), 0);
	NPC_WRITE_FLOW(NPC_SPORT_TCP, sport, ntohs(pkt->sport), 0,
		       ntohs(mask->sport), 0);
	NPC_WRITE_FLOW(NPC_SPORT_UDP, sport, ntohs(pkt->sport), 0,
		       ntohs(mask->sport), 0);
	NPC_WRITE_FLOW(NPC_DPORT_TCP, dport, ntohs(pkt->dport), 0,
		       ntohs(mask->dport), 0);
	NPC_WRITE_FLOW(NPC_DPORT_UDP, dport, ntohs(pkt->dport), 0,
		       ntohs(mask->dport), 0);
	NPC_WRITE_FLOW(NPC_SPORT_SCTP, sport, ntohs(pkt->sport), 0,
		       ntohs(mask->sport), 0);
	NPC_WRITE_FLOW(NPC_DPORT_SCTP, dport, ntohs(pkt->dport), 0,
		       ntohs(mask->dport), 0);

	NPC_WRITE_FLOW(NPC_OUTER_VID, vlan_tci, ntohs(pkt->vlan_tci), 0,
		       ntohs(mask->vlan_tci), 0);

	npc_update_ipv6_flow(rvu, entry, features, pkt, mask, output, पूर्णांकf);
पूर्ण

अटल काष्ठा rvu_npc_mcam_rule *rvu_mcam_find_rule(काष्ठा npc_mcam *mcam,
						    u16 entry)
अणु
	काष्ठा rvu_npc_mcam_rule *iter;

	mutex_lock(&mcam->lock);
	list_क्रम_each_entry(iter, &mcam->mcam_rules, list) अणु
		अगर (iter->entry == entry) अणु
			mutex_unlock(&mcam->lock);
			वापस iter;
		पूर्ण
	पूर्ण
	mutex_unlock(&mcam->lock);

	वापस शून्य;
पूर्ण

अटल व्योम rvu_mcam_add_rule(काष्ठा npc_mcam *mcam,
			      काष्ठा rvu_npc_mcam_rule *rule)
अणु
	काष्ठा list_head *head = &mcam->mcam_rules;
	काष्ठा rvu_npc_mcam_rule *iter;

	mutex_lock(&mcam->lock);
	list_क्रम_each_entry(iter, &mcam->mcam_rules, list) अणु
		अगर (iter->entry > rule->entry)
			अवरोध;
		head = &iter->list;
	पूर्ण

	list_add(&rule->list, head);
	mutex_unlock(&mcam->lock);
पूर्ण

अटल व्योम rvu_mcam_हटाओ_counter_from_rule(काष्ठा rvu *rvu, u16 pcअगरunc,
					      काष्ठा rvu_npc_mcam_rule *rule)
अणु
	काष्ठा npc_mcam_oper_counter_req मुक्त_req = अणु 0 पूर्ण;
	काष्ठा msg_rsp मुक्त_rsp;

	अगर (!rule->has_cntr)
		वापस;

	मुक्त_req.hdr.pcअगरunc = pcअगरunc;
	मुक्त_req.cntr = rule->cntr;

	rvu_mbox_handler_npc_mcam_मुक्त_counter(rvu, &मुक्त_req, &मुक्त_rsp);
	rule->has_cntr = false;
पूर्ण

अटल व्योम rvu_mcam_add_counter_to_rule(काष्ठा rvu *rvu, u16 pcअगरunc,
					 काष्ठा rvu_npc_mcam_rule *rule,
					 काष्ठा npc_install_flow_rsp *rsp)
अणु
	काष्ठा npc_mcam_alloc_counter_req cntr_req = अणु 0 पूर्ण;
	काष्ठा npc_mcam_alloc_counter_rsp cntr_rsp = अणु 0 पूर्ण;
	पूर्णांक err;

	cntr_req.hdr.pcअगरunc = pcअगरunc;
	cntr_req.contig = true;
	cntr_req.count = 1;

	/* we try to allocate a counter to track the stats of this
	 * rule. If counter could not be allocated then proceed
	 * without counter because counters are limited than entries.
	 */
	err = rvu_mbox_handler_npc_mcam_alloc_counter(rvu, &cntr_req,
						      &cntr_rsp);
	अगर (!err && cntr_rsp.count) अणु
		rule->cntr = cntr_rsp.cntr;
		rule->has_cntr = true;
		rsp->counter = rule->cntr;
	पूर्ण अन्यथा अणु
		rsp->counter = err;
	पूर्ण
पूर्ण

अटल व्योम npc_update_rx_entry(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				काष्ठा mcam_entry *entry,
				काष्ठा npc_install_flow_req *req, u16 target)
अणु
	काष्ठा nix_rx_action action;
	u64 chan_mask;

	chan_mask = req->chan_mask ? req->chan_mask : ~0ULL;
	npc_update_entry(rvu, NPC_CHAN, entry, req->channel, 0, chan_mask, 0,
			 NIX_INTF_RX);

	*(u64 *)&action = 0x00;
	action.pf_func = target;
	action.op = req->op;
	action.index = req->index;
	action.match_id = req->match_id;
	action.flow_key_alg = req->flow_key_alg;

	अगर (req->op == NIX_RX_ACTION_DEFAULT && pfvf->def_ucast_rule)
		action = pfvf->def_ucast_rule->rx_action;

	entry->action = *(u64 *)&action;

	/* VTAG0 starts at 0th byte of LID_B.
	 * VTAG1 starts at 4th byte of LID_B.
	 */
	entry->vtag_action = FIELD_PREP(RX_VTAG0_VALID_BIT, req->vtag0_valid) |
			     FIELD_PREP(RX_VTAG0_TYPE_MASK, req->vtag0_type) |
			     FIELD_PREP(RX_VTAG0_LID_MASK, NPC_LID_LB) |
			     FIELD_PREP(RX_VTAG0_RELPTR_MASK, 0) |
			     FIELD_PREP(RX_VTAG1_VALID_BIT, req->vtag1_valid) |
			     FIELD_PREP(RX_VTAG1_TYPE_MASK, req->vtag1_type) |
			     FIELD_PREP(RX_VTAG1_LID_MASK, NPC_LID_LB) |
			     FIELD_PREP(RX_VTAG1_RELPTR_MASK, 4);
पूर्ण

अटल व्योम npc_update_tx_entry(काष्ठा rvu *rvu, काष्ठा rvu_pfvf *pfvf,
				काष्ठा mcam_entry *entry,
				काष्ठा npc_install_flow_req *req, u16 target)
अणु
	काष्ठा nix_tx_action action;

	npc_update_entry(rvu, NPC_PF_FUNC, entry, (__क्रमce u16)htons(target),
			 0, ~0ULL, 0, NIX_INTF_TX);

	*(u64 *)&action = 0x00;
	action.op = req->op;
	action.index = req->index;
	action.match_id = req->match_id;

	entry->action = *(u64 *)&action;

	/* VTAG0 starts at 0th byte of LID_B.
	 * VTAG1 starts at 4th byte of LID_B.
	 */
	entry->vtag_action = FIELD_PREP(TX_VTAG0_DEF_MASK, req->vtag0_def) |
			     FIELD_PREP(TX_VTAG0_OP_MASK, req->vtag0_op) |
			     FIELD_PREP(TX_VTAG0_LID_MASK, NPC_LID_LA) |
			     FIELD_PREP(TX_VTAG0_RELPTR_MASK, 20) |
			     FIELD_PREP(TX_VTAG1_DEF_MASK, req->vtag1_def) |
			     FIELD_PREP(TX_VTAG1_OP_MASK, req->vtag1_op) |
			     FIELD_PREP(TX_VTAG1_LID_MASK, NPC_LID_LA) |
			     FIELD_PREP(TX_VTAG1_RELPTR_MASK, 24);
पूर्ण

अटल पूर्णांक npc_install_flow(काष्ठा rvu *rvu, पूर्णांक blkaddr, u16 target,
			    पूर्णांक nixlf, काष्ठा rvu_pfvf *pfvf,
			    काष्ठा npc_install_flow_req *req,
			    काष्ठा npc_install_flow_rsp *rsp, bool enable,
			    bool pf_set_vfs_mac)
अणु
	काष्ठा rvu_npc_mcam_rule *def_ucast_rule = pfvf->def_ucast_rule;
	u64 features, installed_features, missing_features = 0;
	काष्ठा npc_mcam_ग_लिखो_entry_req ग_लिखो_req = अणु 0 पूर्ण;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_npc_mcam_rule dummy = अणु 0 पूर्ण;
	काष्ठा rvu_npc_mcam_rule *rule;
	bool new = false, msg_from_vf;
	u16 owner = req->hdr.pcअगरunc;
	काष्ठा msg_rsp ग_लिखो_rsp;
	काष्ठा mcam_entry *entry;
	पूर्णांक entry_index, err;

	msg_from_vf = !!(owner & RVU_PFVF_FUNC_MASK);

	installed_features = req->features;
	features = req->features;
	entry = &ग_लिखो_req.entry_data;
	entry_index = req->entry;

	npc_update_flow(rvu, entry, features, &req->packet, &req->mask, &dummy,
			req->पूर्णांकf);

	अगर (is_npc_पूर्णांकf_rx(req->पूर्णांकf))
		npc_update_rx_entry(rvu, pfvf, entry, req, target);
	अन्यथा
		npc_update_tx_entry(rvu, pfvf, entry, req, target);

	/* Default unicast rules करो not exist क्रम TX */
	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		जाओ find_rule;

	अगर (req->शेष_rule) अणु
		entry_index = npc_get_nixlf_mcam_index(mcam, target, nixlf,
						       NIXLF_UCAST_ENTRY);
		enable = is_mcam_entry_enabled(rvu, mcam, blkaddr, entry_index);
	पूर्ण

	/* update mcam entry with शेष unicast rule attributes */
	अगर (def_ucast_rule && (msg_from_vf || (req->शेष_rule && req->append))) अणु
		missing_features = (def_ucast_rule->features ^ features) &
					def_ucast_rule->features;
		अगर (missing_features)
			npc_update_flow(rvu, entry, missing_features,
					&def_ucast_rule->packet,
					&def_ucast_rule->mask,
					&dummy, req->पूर्णांकf);
		installed_features = req->features | missing_features;
	पूर्ण

find_rule:
	rule = rvu_mcam_find_rule(mcam, entry_index);
	अगर (!rule) अणु
		rule = kzalloc(माप(*rule), GFP_KERNEL);
		अगर (!rule)
			वापस -ENOMEM;
		new = true;
	पूर्ण

	/* allocate new counter अगर rule has no counter */
	अगर (!req->शेष_rule && req->set_cntr && !rule->has_cntr)
		rvu_mcam_add_counter_to_rule(rvu, owner, rule, rsp);

	/* अगर user wants to delete an existing counter क्रम a rule then
	 * मुक्त the counter
	 */
	अगर (!req->set_cntr && rule->has_cntr)
		rvu_mcam_हटाओ_counter_from_rule(rvu, owner, rule);

	ग_लिखो_req.hdr.pcअगरunc = owner;

	/* AF owns the शेष rules so change the owner just to relax
	 * the checks in rvu_mbox_handler_npc_mcam_ग_लिखो_entry
	 */
	अगर (req->शेष_rule)
		ग_लिखो_req.hdr.pcअगरunc = 0;

	ग_लिखो_req.entry = entry_index;
	ग_लिखो_req.पूर्णांकf = req->पूर्णांकf;
	ग_लिखो_req.enable_entry = (u8)enable;
	/* अगर counter is available then clear and use it */
	अगर (req->set_cntr && rule->has_cntr) अणु
		rvu_ग_लिखो64(rvu, blkaddr, NPC_AF_MATCH_STATX(rule->cntr), 0x00);
		ग_लिखो_req.set_cntr = 1;
		ग_लिखो_req.cntr = rule->cntr;
	पूर्ण

	err = rvu_mbox_handler_npc_mcam_ग_लिखो_entry(rvu, &ग_लिखो_req,
						    &ग_लिखो_rsp);
	अगर (err) अणु
		rvu_mcam_हटाओ_counter_from_rule(rvu, owner, rule);
		अगर (new)
			kमुक्त(rule);
		वापस err;
	पूर्ण
	/* update rule */
	स_नकल(&rule->packet, &dummy.packet, माप(rule->packet));
	स_नकल(&rule->mask, &dummy.mask, माप(rule->mask));
	rule->entry = entry_index;
	स_नकल(&rule->rx_action, &entry->action, माप(काष्ठा nix_rx_action));
	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		स_नकल(&rule->tx_action, &entry->action,
		       माप(काष्ठा nix_tx_action));
	rule->vtag_action = entry->vtag_action;
	rule->features = installed_features;
	rule->शेष_rule = req->शेष_rule;
	rule->owner = owner;
	rule->enable = enable;
	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		rule->पूर्णांकf = pfvf->nix_tx_पूर्णांकf;
	अन्यथा
		rule->पूर्णांकf = pfvf->nix_rx_पूर्णांकf;

	अगर (new)
		rvu_mcam_add_rule(mcam, rule);
	अगर (req->शेष_rule)
		pfvf->def_ucast_rule = rule;

	/* VF's MAC address is being changed via PF  */
	अगर (pf_set_vfs_mac) अणु
		ether_addr_copy(pfvf->शेष_mac, req->packet.dmac);
		ether_addr_copy(pfvf->mac_addr, req->packet.dmac);
	पूर्ण

	अगर (pfvf->pf_set_vf_cfg && req->vtag0_type == NIX_AF_LFX_RX_VTAG_TYPE7)
		rule->vfvlan_cfg = true;

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_npc_install_flow(काष्ठा rvu *rvu,
				      काष्ठा npc_install_flow_req *req,
				      काष्ठा npc_install_flow_rsp *rsp)
अणु
	bool from_vf = !!(req->hdr.pcअगरunc & RVU_PFVF_FUNC_MASK);
	पूर्णांक blkaddr, nixlf, err;
	काष्ठा rvu_pfvf *pfvf;
	bool pf_set_vfs_mac = false;
	bool enable = true;
	u16 target;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0) अणु
		dev_err(rvu->dev, "%s: NPC block not implemented\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!is_npc_पूर्णांकerface_valid(rvu, req->पूर्णांकf))
		वापस -EINVAL;

	अगर (from_vf && req->शेष_rule)
		वापस NPC_MCAM_PERM_DENIED;

	/* Each PF/VF info is मुख्यtained in काष्ठा rvu_pfvf.
	 * rvu_pfvf क्रम the target PF/VF needs to be retrieved
	 * hence modअगरy pcअगरunc accordingly.
	 */

	/* AF installing क्रम a PF/VF */
	अगर (!req->hdr.pcअगरunc)
		target = req->vf;
	/* PF installing क्रम its VF */
	अन्यथा अगर (!from_vf && req->vf) अणु
		target = (req->hdr.pcअगरunc & ~RVU_PFVF_FUNC_MASK) | req->vf;
		pf_set_vfs_mac = req->शेष_rule &&
				(req->features & BIT_ULL(NPC_DMAC));
	पूर्ण
	/* msg received from PF/VF */
	अन्यथा
		target = req->hdr.pcअगरunc;

	/* ignore chan_mask in हाल pf func is not AF, revisit later */
	अगर (!is_pffunc_af(req->hdr.pcअगरunc))
		req->chan_mask = 0xFFF;

	err = npc_check_unsupported_flows(rvu, req->features, req->पूर्णांकf);
	अगर (err)
		वापस err;

	अगर (npc_mcam_verअगरy_channel(rvu, target, req->पूर्णांकf, req->channel))
		वापस -EINVAL;

	pfvf = rvu_get_pfvf(rvu, target);

	/* PF installing क्रम its VF */
	अगर (req->hdr.pcअगरunc && !from_vf && req->vf)
		pfvf->pf_set_vf_cfg = 1;

	/* update req destination mac addr */
	अगर ((req->features & BIT_ULL(NPC_DMAC)) && is_npc_पूर्णांकf_rx(req->पूर्णांकf) &&
	    is_zero_ether_addr(req->packet.dmac)) अणु
		ether_addr_copy(req->packet.dmac, pfvf->mac_addr);
		eth_broadcast_addr((u8 *)&req->mask.dmac);
	पूर्ण

	err = nix_get_nixlf(rvu, target, &nixlf, शून्य);

	/* If पूर्णांकerface is uninitialized then करो not enable entry */
	अगर (err || (!req->शेष_rule && !pfvf->def_ucast_rule))
		enable = false;

	/* Packets reaching NPC in Tx path implies that a
	 * NIXLF is properly setup and transmitting.
	 * Hence rules can be enabled क्रम Tx.
	 */
	अगर (is_npc_पूर्णांकf_tx(req->पूर्णांकf))
		enable = true;

	/* Do not allow requests from uninitialized VFs */
	अगर (from_vf && !enable)
		वापस -EINVAL;

	/* If message is from VF then its flow should not overlap with
	 * reserved unicast flow.
	 */
	अगर (from_vf && pfvf->def_ucast_rule && is_npc_पूर्णांकf_rx(req->पूर्णांकf) &&
	    pfvf->def_ucast_rule->features & req->features)
		वापस -EINVAL;

	वापस npc_install_flow(rvu, blkaddr, target, nixlf, pfvf, req, rsp,
				enable, pf_set_vfs_mac);
पूर्ण

अटल पूर्णांक npc_delete_flow(काष्ठा rvu *rvu, काष्ठा rvu_npc_mcam_rule *rule,
			   u16 pcअगरunc)
अणु
	काष्ठा npc_mcam_ena_dis_entry_req dis_req = अणु 0 पूर्ण;
	काष्ठा msg_rsp dis_rsp;

	अगर (rule->शेष_rule)
		वापस 0;

	अगर (rule->has_cntr)
		rvu_mcam_हटाओ_counter_from_rule(rvu, pcअगरunc, rule);

	dis_req.hdr.pcअगरunc = pcअगरunc;
	dis_req.entry = rule->entry;

	list_del(&rule->list);
	kमुक्त(rule);

	वापस rvu_mbox_handler_npc_mcam_dis_entry(rvu, &dis_req, &dis_rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_npc_delete_flow(काष्ठा rvu *rvu,
				     काष्ठा npc_delete_flow_req *req,
				     काष्ठा msg_rsp *rsp)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_npc_mcam_rule *iter, *पंचांगp;
	u16 pcअगरunc = req->hdr.pcअगरunc;
	काष्ठा list_head del_list;

	INIT_LIST_HEAD(&del_list);

	mutex_lock(&mcam->lock);
	list_क्रम_each_entry_safe(iter, पंचांगp, &mcam->mcam_rules, list) अणु
		अगर (iter->owner == pcअगरunc) अणु
			/* All rules */
			अगर (req->all) अणु
				list_move_tail(&iter->list, &del_list);
			/* Range of rules */
			पूर्ण अन्यथा अगर (req->end && iter->entry >= req->start &&
				   iter->entry <= req->end) अणु
				list_move_tail(&iter->list, &del_list);
			/* single rule */
			पूर्ण अन्यथा अगर (req->entry == iter->entry) अणु
				list_move_tail(&iter->list, &del_list);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&mcam->lock);

	list_क्रम_each_entry_safe(iter, पंचांगp, &del_list, list) अणु
		u16 entry = iter->entry;

		/* clear the mcam entry target pcअगरunc */
		mcam->entry2target_pffunc[entry] = 0x0;
		अगर (npc_delete_flow(rvu, iter, pcअगरunc))
			dev_err(rvu->dev, "rule deletion failed for entry:%u",
				entry);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक npc_update_dmac_value(काष्ठा rvu *rvu, पूर्णांक npcblkaddr,
				 काष्ठा rvu_npc_mcam_rule *rule,
				 काष्ठा rvu_pfvf *pfvf)
अणु
	काष्ठा npc_mcam_ग_लिखो_entry_req ग_लिखो_req = अणु 0 पूर्ण;
	काष्ठा mcam_entry *entry = &ग_लिखो_req.entry_data;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा msg_rsp rsp;
	u8 पूर्णांकf, enable;
	पूर्णांक err;

	ether_addr_copy(rule->packet.dmac, pfvf->mac_addr);

	npc_पढ़ो_mcam_entry(rvu, mcam, npcblkaddr, rule->entry,
			    entry, &पूर्णांकf,  &enable);

	npc_update_entry(rvu, NPC_DMAC, entry,
			 ether_addr_to_u64(pfvf->mac_addr), 0,
			 0xffffffffffffull, 0, पूर्णांकf);

	ग_लिखो_req.hdr.pcअगरunc = rule->owner;
	ग_लिखो_req.entry = rule->entry;
	ग_लिखो_req.पूर्णांकf = pfvf->nix_rx_पूर्णांकf;

	mutex_unlock(&mcam->lock);
	err = rvu_mbox_handler_npc_mcam_ग_लिखो_entry(rvu, &ग_लिखो_req, &rsp);
	mutex_lock(&mcam->lock);

	वापस err;
पूर्ण

व्योम npc_mcam_enable_flows(काष्ठा rvu *rvu, u16 target)
अणु
	काष्ठा rvu_pfvf *pfvf = rvu_get_pfvf(rvu, target);
	काष्ठा rvu_npc_mcam_rule *def_ucast_rule;
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	काष्ठा rvu_npc_mcam_rule *rule;
	पूर्णांक blkaddr, bank, index;
	u64 def_action;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	def_ucast_rule = pfvf->def_ucast_rule;

	mutex_lock(&mcam->lock);
	list_क्रम_each_entry(rule, &mcam->mcam_rules, list) अणु
		अगर (is_npc_पूर्णांकf_rx(rule->पूर्णांकf) &&
		    rule->rx_action.pf_func == target && !rule->enable) अणु
			अगर (rule->शेष_rule) अणु
				npc_enable_mcam_entry(rvu, mcam, blkaddr,
						      rule->entry, true);
				rule->enable = true;
				जारी;
			पूर्ण

			अगर (rule->vfvlan_cfg)
				npc_update_dmac_value(rvu, blkaddr, rule, pfvf);

			अगर (rule->rx_action.op == NIX_RX_ACTION_DEFAULT) अणु
				अगर (!def_ucast_rule)
					जारी;
				/* Use शेष unicast entry action */
				rule->rx_action = def_ucast_rule->rx_action;
				def_action = *(u64 *)&def_ucast_rule->rx_action;
				bank = npc_get_bank(mcam, rule->entry);
				rvu_ग_लिखो64(rvu, blkaddr,
					    NPC_AF_MCAMEX_BANKX_ACTION
					    (rule->entry, bank), def_action);
			पूर्ण

			npc_enable_mcam_entry(rvu, mcam, blkaddr,
					      rule->entry, true);
			rule->enable = true;
		पूर्ण
	पूर्ण

	/* Enable MCAM entries installed by PF with target as VF pcअगरunc */
	क्रम (index = 0; index < mcam->bmap_entries; index++) अणु
		अगर (mcam->entry2target_pffunc[index] == target)
			npc_enable_mcam_entry(rvu, mcam, blkaddr,
					      index, true);
	पूर्ण
	mutex_unlock(&mcam->lock);
पूर्ण

व्योम npc_mcam_disable_flows(काष्ठा rvu *rvu, u16 target)
अणु
	काष्ठा npc_mcam *mcam = &rvu->hw->mcam;
	पूर्णांक blkaddr, index;

	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NPC, 0);
	अगर (blkaddr < 0)
		वापस;

	mutex_lock(&mcam->lock);
	/* Disable MCAM entries installed by PF with target as VF pcअगरunc */
	क्रम (index = 0; index < mcam->bmap_entries; index++) अणु
		अगर (mcam->entry2target_pffunc[index] == target)
			npc_enable_mcam_entry(rvu, mcam, blkaddr,
					      index, false);
	पूर्ण
	mutex_unlock(&mcam->lock);
पूर्ण
