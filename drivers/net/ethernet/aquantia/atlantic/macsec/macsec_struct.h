<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 * Copyright (C) 2020 Marvell International Ltd.
 */

#अगर_अघोषित _MACSEC_STRUCT_H_
#घोषणा _MACSEC_STRUCT_H_

/*! Represents the bitfields of a single row in the Egress CTL Filter
 *  table.
 */
काष्ठा aq_mss_egress_ctlf_record अणु
	/*! This is used to store the 48 bit value used to compare SA, DA or
	 *  halfDA+half SA value.
	 */
	u32 sa_da[2];
	/*! This is used to store the 16 bit ethertype value used क्रम
	 *  comparison.
	 */
	u32 eth_type;
	/*! The match mask is per-nibble. 0 means करोn't care, i.e. every value
	 *  will match successfully. The total data is 64 bit, i.e. 16 nibbles
	 *  masks.
	 */
	u32 match_mask;
	/*! 0: No compare, i.e. This entry is not used
	 *  1: compare DA only
	 *  2: compare SA only
	 *  3: compare half DA + half SA
	 *  4: compare ether type only
	 *  5: compare DA + ethertype
	 *  6: compare SA + ethertype
	 *  7: compare DA+ range.
	 */
	u32 match_type;
	/*! 0: Bypass the reमुख्यing modules अगर matched.
	 *  1: Forward to next module क्रम more classअगरications.
	 */
	u32 action;
पूर्ण;

/*! Represents the bitfields of a single row in the Egress Packet
 *  Classअगरier table.
 */
काष्ठा aq_mss_egress_class_record अणु
	/*! VLAN ID field. */
	u32 vlan_id;
	/*! VLAN UP field. */
	u32 vlan_up;
	/*! VLAN Present in the Packet. */
	u32 vlan_valid;
	/*! The 8 bit value used to compare with extracted value क्रम byte 3. */
	u32 byte3;
	/*! The 8 bit value used to compare with extracted value क्रम byte 2. */
	u32 byte2;
	/*! The 8 bit value used to compare with extracted value क्रम byte 1. */
	u32 byte1;
	/*! The 8 bit value used to compare with extracted value क्रम byte 0. */
	u32 byte0;
	/*! The 8 bit TCI field used to compare with extracted value. */
	u32 tci;
	/*! The 64 bit SCI field in the SecTAG. */
	u32 sci[2];
	/*! The 16 bit Ethertype (in the clear) field used to compare with
	 *  extracted value.
	 */
	u32 eth_type;
	/*! This is to specअगरy the 40bit SNAP header अगर the SNAP header's mask
	 *  is enabled.
	 */
	u32 snap[2];
	/*! This is to specअगरy the 24bit LLC header अगर the LLC header's mask is
	 *  enabled.
	 */
	u32 llc;
	/*! The 48 bit MAC_SA field used to compare with extracted value. */
	u32 mac_sa[2];
	/*! The 48 bit MAC_DA field used to compare with extracted value. */
	u32 mac_da[2];
	/*! The 32 bit Packet number used to compare with extracted value. */
	u32 pn;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte3_location;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted byte poपूर्णांकed by byte 3 location.
	 */
	u32 byte3_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte2_location;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted byte poपूर्णांकed by byte 2 location.
	 */
	u32 byte2_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte1_location;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted byte poपूर्णांकed by byte 1 location.
	 */
	u32 byte1_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte0_location;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted byte poपूर्णांकed by byte 0 location.
	 */
	u32 byte0_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of extracted VLAN ID field.
	 */
	u32 vlan_id_mask;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted VLAN UP field.
	 */
	u32 vlan_up_mask;
	/*! 0: करोn't care
	 *  1: enable comparison of extracted VLAN Valid field.
	 */
	u32 vlan_valid_mask;
	/*! This is bit mask to enable comparison the 8 bit TCI field,
	 *  including the AN field.
	 *  For explicit SECTAG, AN is hardware controlled. For sending
	 *  packet w/ explicit SECTAG, rest of the TCI fields are directly
	 *  from the SECTAG.
	 */
	u32 tci_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of SCI
	 *  Note: If this field is not 0, this means the input packet's
	 *  SECTAG is explicitly tagged and MACSEC module will only update
	 *  the MSDU.
	 *  PN number is hardware controlled.
	 */
	u32 sci_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of Ethertype.
	 */
	u32 eth_type_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care and no SNAP header exist.
	 *  1: compare the SNAP header.
	 *  If this bit is set to 1, the extracted filed will assume the
	 *  SNAP header exist as encapsulated in 802.3 (RFC 1042). I.E. the
	 *  next 5 bytes after the the LLC header is SNAP header.
	 */
	u32 snap_mask;
	/*! 0: करोn't care and no LLC header exist.
	 *  1: compare the LLC header.
	 *  If this bit is set to 1, the extracted filed will assume the
	 *  LLC header exist as encapsulated in 802.3 (RFC 1042). I.E. the
	 *  next three bytes after the 802.3MAC header is LLC header.
	 */
	u32 llc_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of MAC_SA.
	 */
	u32 sa_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of MAC_DA.
	 */
	u32 da_mask;
	/*! Mask is per-byte. */
	u32 pn_mask;
	/*! Reserved. This bit should be always 0. */
	u32 eight02करोt2;
	/*! 1: For explicit sectag हाल use TCI_SC from table
	 *  0: use TCI_SC from explicit sectag.
	 */
	u32 tci_sc;
	/*! 1: For explicit sectag हाल,use TCI_V,ES,SCB,E,C from table
	 *  0: use TCI_V,ES,SCB,E,C from explicit sectag.
	 */
	u32 tci_87543;
	/*! 1: indicates that incoming packet has explicit sectag. */
	u32 exp_sectag_en;
	/*! If packet matches and tagged as controlled-packet, this SC/SA
	 *  index is used क्रम later SC and SA table lookup.
	 */
	u32 sc_idx;
	/*! This field is used to specअगरy how many SA entries are
	 *  associated with 1 SC entry.
	 *  2'b00: 1 SC has 4 SA.
	 *  SC index is equivalent to अणुSC_Index[4:2], 1'b0पूर्ण.
	 *  SA index is equivalent to अणुSC_Index[4:2], SC entry's current AN[1:0]
	 *  2'b10: 1 SC has 2 SA.
	 *  SC index is equivalent to SC_Index[4:1]
	 *  SA index is equivalent to अणुSC_Index[4:1], SC entry's current AN[0]पूर्ण
	 *  2'b11: 1 SC has 1 SA. No SC entry exists क्रम the specअगरic SA.
	 *  SA index is equivalent to SC_Index[4:0]
	 *  Note: अगर specअगरied as 2'b11, hardware AN roll over is not
	 *  supported.
	 */
	u32 sc_sa;
	/*! 0: the packets will be sent to MAC FIFO
	 *  1: The packets will be sent to Debug/Loopback FIFO.
	 *  If the above's action is drop, this bit has no meaning.
	 */
	u32 debug;
	/*! 0: क्रमward to reमुख्यing modules
	 *  1: bypass the next encryption modules. This packet is considered
	 *     un-control packet.
	 *  2: drop
	 *  3: Reserved.
	 */
	u32 action;
	/*! 0: Not valid entry. This entry is not used
	 *  1: valid entry.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Egress SC Lookup table. */
काष्ठा aq_mss_egress_sc_record अणु
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 start_समय;
	/*! This is to specअगरy when the SC was last used. Set by HW. */
	u32 stop_समय;
	/*! This is to specअगरy which of the SA entries are used by current HW.
	 *  Note: This value need to be set by SW after reset.  It will be
	 *  स्वतःmatically updated by HW, अगर AN roll over is enabled.
	 */
	u32 curr_an;
	/*! 0: Clear the SA Valid Bit after PN expiry.
	 *  1: Do not Clear the SA Valid bit after PN expiry of the current SA.
	 *  When the Enable AN roll over is set, S/W करोes not need to
	 *  program the new SA's and the H/W will स्वतःmatically roll over
	 *  between the SA's without session expiry.
	 *  For normal operation, Enable AN Roll over will be set to '0'
	 *  and in which हाल, the SW needs to program the new SA values
	 *  after the current PN expires.
	 */
	u32 an_roll;
	/*! This is the TCI field used अगर packet is not explicitly tagged. */
	u32 tci;
	/*! This value indicates the offset where the decryption will start.
	 *  [[Values of 0, 4, 8-50].
	 */
	u32 enc_off;
	/*! 0: Do not protect frames, all the packets will be क्रमwarded
	 *     unchanged. MIB counter (OutPktsUntagged) will be updated.
	 *  1: Protect.
	 */
	u32 protect;
	/*! 0: when none of the SA related to SC has inUse set.
	 *  1: when either of the SA related to the SC has inUse set.
	 *  This bit is set by HW.
	 */
	u32 recv;
	/*! 0: H/W Clears this bit on the first use.
	 *  1: SW updates this entry, when programming the SC Table.
	 */
	u32 fresh;
	/*! AES Key size
	 *  00 - 128bits
	 *  01 - 192bits
	 *  10 - 256bits
	 *  11 - Reserved.
	 */
	u32 sak_len;
	/*! 0: Invalid SC
	 *  1: Valid SC.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Egress SA Lookup table. */
काष्ठा aq_mss_egress_sa_record अणु
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 start_समय;
	/*! This is to specअगरy when the SC was last used. Set by HW. */
	u32 stop_समय;
	/*! This is set by SW and updated by HW to store the Next PN number
	 *  used क्रम encryption.
	 */
	u32 next_pn;
	/*! The Next_PN number is going to wrapped around from 0xFFFF_FFFF
	 *  to 0. set by HW.
	 */
	u32 sat_pn;
	/*! 0: This SA is in use.
	 *  1: This SA is Fresh and set by SW.
	 */
	u32 fresh;
	/*! 0: Invalid SA
	 *  1: Valid SA.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Egress SA Key
 *  Lookup table.
 */
काष्ठा aq_mss_egress_sakey_record अणु
	/*! Key क्रम AES-GCM processing. */
	u32 key[8];
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress Pre-MACSec
 *  CTL Filter table.
 */
काष्ठा aq_mss_ingress_prectlf_record अणु
	/*! This is used to store the 48 bit value used to compare SA, DA
	 *  or halfDA+half SA value.
	 */
	u32 sa_da[2];
	/*! This is used to store the 16 bit ethertype value used क्रम
	 *  comparison.
	 */
	u32 eth_type;
	/*! The match mask is per-nibble. 0 means करोn't care, i.e. every
	 *  value will match successfully. The total data is 64 bit, i.e.
	 *  16 nibbles masks.
	 */
	u32 match_mask;
	/*! 0: No compare, i.e. This entry is not used
	 *  1: compare DA only
	 *  2: compare SA only
	 *  3: compare half DA + half SA
	 *  4: compare ether type only
	 *  5: compare DA + ethertype
	 *  6: compare SA + ethertype
	 *  7: compare DA+ range.
	 */
	u32 match_type;
	/*! 0: Bypass the reमुख्यing modules अगर matched.
	 *  1: Forward to next module क्रम more classअगरications.
	 */
	u32 action;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress Pre-MACSec
 *  Packet Classअगरier table.
 */
काष्ठा aq_mss_ingress_preclass_record अणु
	/*! The 64 bit SCI field used to compare with extracted value.
	 *  Should have SCI value in हाल TCI[SCI_SEND] == 0. This will be
	 *  used क्रम ICV calculation.
	 */
	u32 sci[2];
	/*! The 8 bit TCI field used to compare with extracted value. */
	u32 tci;
	/*! 8 bit encryption offset. */
	u32 encr_offset;
	/*! The 16 bit Ethertype (in the clear) field used to compare with
	 *  extracted value.
	 */
	u32 eth_type;
	/*! This is to specअगरy the 40bit SNAP header अगर the SNAP header's
	 *  mask is enabled.
	 */
	u32 snap[2];
	/*! This is to specअगरy the 24bit LLC header अगर the LLC header's
	 *  mask is enabled.
	 */
	u32 llc;
	/*! The 48 bit MAC_SA field used to compare with extracted value. */
	u32 mac_sa[2];
	/*! The 48 bit MAC_DA field used to compare with extracted value. */
	u32 mac_da[2];
	/*! 0: this is to compare with non-LPBK packet
	 *  1: this is to compare with LPBK packet.
	 *  This value is used to compare with a controlled-tag which goes
	 *  with the packet when looped back from Egress port.
	 */
	u32 lpbk_packet;
	/*! The value of this bit mask will affects how the SC index and SA
	 *  index created.
	 *  2'b00: 1 SC has 4 SA.
	 *    SC index is equivalent to अणुSC_Index[4:2], 1'b0पूर्ण.
	 *    SA index is equivalent to अणुSC_Index[4:2], SECTAG's AN[1:0]पूर्ण
	 *    Here AN bits are not compared.
	 *  2'b10: 1 SC has 2 SA.
	 *    SC index is equivalent to SC_Index[4:1]
	 *    SA index is equivalent to अणुSC_Index[4:1], SECTAG's AN[0]पूर्ण
	 *    Compare AN[1] field only
	 *  2'b11: 1 SC has 1 SA. No SC entry exists क्रम the specअगरic SA.
	 *    SA index is equivalent to SC_Index[4:0]
	 *    AN[1:0] bits are compared.
	 *    NOTE: This design is to supports dअगरferent usage of AN. User
	 *    can either ping-pong buffer 2 SA by using only the AN[0] bit.
	 *    Or use 4 SA per SC by use AN[1:0] bits. Or even treat each SA
	 *    as independent. i.e. AN[1:0] is just another matching poपूर्णांकer
	 *    to select SA.
	 */
	u32 an_mask;
	/*! This is bit mask to enable comparison the upper 6 bits TCI
	 *  field, which करोes not include the AN field.
	 *  0: करोn't compare
	 *  1: enable comparison of the bits.
	 */
	u32 tci_mask;
	/*! 0: करोn't care
	 *  1: enable comparison of SCI.
	 */
	u32 sci_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of Ethertype.
	 */
	u32 eth_type_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care and no SNAP header exist.
	 *  1: compare the SNAP header.
	 *  If this bit is set to 1, the extracted filed will assume the
	 *  SNAP header exist as encapsulated in 802.3 (RFC 1042). I.E. the
	 *  next 5 bytes after the the LLC header is SNAP header.
	 */
	u32 snap_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care and no LLC header exist.
	 *  1: compare the LLC header.
	 *  If this bit is set to 1, the extracted filed will assume the
	 *  LLC header exist as encapsulated in 802.3 (RFC 1042). I.E. the
	 *  next three bytes after the 802.3MAC header is LLC header.
	 */
	u32 llc_mask;
	/*! Reserved. This bit should be always 0. */
	u32 _802_2_encapsulate;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of MAC_SA.
	 */
	u32 sa_mask;
	/*! Mask is per-byte.
	 *  0: करोn't care
	 *  1: enable comparison of MAC_DA.
	 */
	u32 da_mask;
	/*! 0: करोn't care
	 *  1: enable checking अगर this is loopback packet or not.
	 */
	u32 lpbk_mask;
	/*! If packet matches and tagged as controlled-packet. This SC/SA
	 *  index is used क्रम later SC and SA table lookup.
	 */
	u32 sc_idx;
	/*! 0: the packets will be sent to MAC FIFO
	 *  1: The packets will be sent to Debug/Loopback FIFO.
	 *  If the above's action is drop. This bit has no meaning.
	 */
	u32 proc_dest;
	/*! 0: Process: Forward to next two modules क्रम 802.1AE decryption.
	 *  1: Process but keep SECTAG: Forward to next two modules क्रम
	 *     802.1AE decryption but keep the MACSEC header with added error
	 *     code inक्रमmation. ICV will be stripped क्रम all control packets.
	 *  2: Bypass: Bypass the next two decryption modules but processed
	 *     by post-classअगरication.
	 *  3: Drop: drop this packet and update counts accordingly.
	 */
	u32 action;
	/*! 0: This is a controlled-port packet अगर matched.
	 *  1: This is an uncontrolled-port packet अगर matched.
	 */
	u32 ctrl_unctrl;
	/*! Use the SCI value from the Table अगर 'SC' bit of the input
	 *  packet is not present.
	 */
	u32 sci_from_table;
	/*! Reserved. */
	u32 reserved;
	/*! 0: Not valid entry. This entry is not used
	 *  1: valid entry.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress SC Lookup table. */
काष्ठा aq_mss_ingress_sc_record अणु
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 stop_समय;
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 start_समय;
	/*! 0: Strict
	 *  1: Check
	 *  2: Disabled.
	 */
	u32 validate_frames;
	/*! 1: Replay control enabled.
	 *  0: replay control disabled.
	 */
	u32 replay_protect;
	/*! This is to specअगरy the winकरोw range क्रम anti-replay. Default is 0.
	 *  0: is strict order enक्रमcement.
	 */
	u32 anti_replay_winकरोw;
	/*! 0: when none of the SA related to SC has inUse set.
	 *  1: when either of the SA related to the SC has inUse set.
	 *  This bit is set by HW.
	 */
	u32 receiving;
	/*! 0: when hardware processed the SC क्रम the first समय, it clears
	 *     this bit
	 *  1: This bit is set by SW, when it sets up the SC.
	 */
	u32 fresh;
	/*! 0: The AN number will not स्वतःmatically roll over अगर Next_PN is
	 *     saturated.
	 *  1: The AN number will स्वतःmatically roll over अगर Next_PN is
	 *     saturated.
	 *  Rollover is valid only after expiry. Normal roll over between
	 *  SA's should be normal process.
	 */
	u32 an_rol;
	/*! Reserved. */
	u32 reserved;
	/*! 0: Invalid SC
	 *  1: Valid SC.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress SA Lookup table. */
काष्ठा aq_mss_ingress_sa_record अणु
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 stop_समय;
	/*! This is to specअगरy when the SC was first used. Set by HW. */
	u32 start_समय;
	/*! This is updated by HW to store the expected NextPN number क्रम
	 *  anti-replay.
	 */
	u32 next_pn;
	/*! The Next_PN number is going to wrapped around from 0XFFFF_FFFF
	 *  to 0. set by HW.
	 */
	u32 sat_nextpn;
	/*! 0: This SA is not yet used.
	 *  1: This SA is inUse.
	 */
	u32 in_use;
	/*! 0: when hardware processed the SC क्रम the first समय, it clears
	 *     this समयr
	 *  1: This bit is set by SW, when it sets up the SC.
	 */
	u32 fresh;
	/*! Reserved. */
	u32 reserved;
	/*! 0: Invalid SA.
	 *  1: Valid SA.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress SA Key
 *  Lookup table.
 */
काष्ठा aq_mss_ingress_sakey_record अणु
	/*! Key क्रम AES-GCM processing. */
	u32 key[8];
	/*! AES key size
	 *  00 - 128bits
	 *  01 - 192bits
	 *  10 - 256bits
	 *  11 - reserved.
	 */
	u32 key_len;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress Post-
 *  MACSec Packet Classअगरier table.
 */
काष्ठा aq_mss_ingress_postclass_record अणु
	/*! The 8 bit value used to compare with extracted value क्रम byte 0. */
	u32 byte0;
	/*! The 8 bit value used to compare with extracted value क्रम byte 1. */
	u32 byte1;
	/*! The 8 bit value used to compare with extracted value क्रम byte 2. */
	u32 byte2;
	/*! The 8 bit value used to compare with extracted value क्रम byte 3. */
	u32 byte3;
	/*! Ethertype in the packet. */
	u32 eth_type;
	/*! Ether Type value > 1500 (0x5dc). */
	u32 eth_type_valid;
	/*! VLAN ID after parsing. */
	u32 vlan_id;
	/*! VLAN priority after parsing. */
	u32 vlan_up;
	/*! Valid VLAN coding. */
	u32 vlan_valid;
	/*! SA index. */
	u32 sai;
	/*! SAI hit, i.e. controlled packet. */
	u32 sai_hit;
	/*! Mask क्रम payload ethertype field. */
	u32 eth_type_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte3_location;
	/*! Mask क्रम Byte Offset 3. */
	u32 byte3_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte2_location;
	/*! Mask क्रम Byte Offset 2. */
	u32 byte2_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte1_location;
	/*! Mask क्रम Byte Offset 1. */
	u32 byte1_mask;
	/*! 0~63: byte location used extracted by packets comparator, which
	 *  can be anything from the first 64 bytes of the MAC packets.
	 *  This byte location counted from MAC' DA address. i.e. set to 0
	 *  will poपूर्णांक to byte 0 of DA address.
	 */
	u32 byte0_location;
	/*! Mask क्रम Byte Offset 0. */
	u32 byte0_mask;
	/*! Mask क्रम Ethertype valid field. Indicates 802.3 vs. Other. */
	u32 eth_type_valid_mask;
	/*! Mask क्रम VLAN ID field. */
	u32 vlan_id_mask;
	/*! Mask क्रम VLAN UP field. */
	u32 vlan_up_mask;
	/*! Mask क्रम VLAN valid field. */
	u32 vlan_valid_mask;
	/*! Mask क्रम SAI. */
	u32 sai_mask;
	/*! Mask क्रम SAI_HIT. */
	u32 sai_hit_mask;
	/*! Action अगर only first level matches and second level करोes not.
	 *  0: pass
	 *  1: drop (fail).
	 */
	u32 firstlevel_actions;
	/*! Action अगर both first and second level matched.
	 *  0: pass
	 *  1: drop (fail).
	 */
	u32 secondlevel_actions;
	/*! Reserved. */
	u32 reserved;
	/*! 0: Not valid entry. This entry is not used
	 *  1: valid entry.
	 */
	u32 valid;
पूर्ण;

/*! Represents the bitfields of a single row in the Ingress Post-
 *  MACSec CTL Filter table.
 */
काष्ठा aq_mss_ingress_postctlf_record अणु
	/*! This is used to store the 48 bit value used to compare SA, DA
	 *  or halfDA+half SA value.
	 */
	u32 sa_da[2];
	/*! This is used to store the 16 bit ethertype value used क्रम
	 *  comparison.
	 */
	u32 eth_type;
	/*! The match mask is per-nibble. 0 means करोn't care, i.e. every
	 *  value will match successfully. The total data is 64 bit, i.e.
	 *  16 nibbles masks.
	 */
	u32 match_mask;
	/*! 0: No compare, i.e. This entry is not used
	 *  1: compare DA only
	 *  2: compare SA only
	 *  3: compare half DA + half SA
	 *  4: compare ether type only
	 *  5: compare DA + ethertype
	 *  6: compare SA + ethertype
	 *  7: compare DA+ range.
	 */
	u32 match_type;
	/*! 0: Bypass the reमुख्यing modules अगर matched.
	 *  1: Forward to next module क्रम more classअगरications.
	 */
	u32 action;
पूर्ण;

/*! Represents the Egress MIB counters क्रम a single SC. Counters are
 *  64 bits, lower 32 bits in field[0].
 */
काष्ठा aq_mss_egress_sc_counters अणु
	/*! The number of पूर्णांकegrity रक्षित but not encrypted packets
	 *  क्रम this transmitting SC.
	 */
	u32 sc_रक्षित_pkts[2];
	/*! The number of पूर्णांकegrity रक्षित and encrypted packets क्रम
	 *  this transmitting SC.
	 */
	u32 sc_encrypted_pkts[2];
	/*! The number of plain text octets that are पूर्णांकegrity रक्षित
	 *  but not encrypted on the transmitting SC.
	 */
	u32 sc_रक्षित_octets[2];
	/*! The number of plain text octets that are पूर्णांकegrity रक्षित
	 *  and encrypted on the transmitting SC.
	 */
	u32 sc_encrypted_octets[2];
पूर्ण;

/*! Represents the Egress MIB counters क्रम a single SA. Counters are
 *  64 bits, lower 32 bits in field[0].
 */
काष्ठा aq_mss_egress_sa_counters अणु
	/*! The number of dropped packets क्रम this transmitting SA. */
	u32 sa_hit_drop_redirect[2];
	/*! TODO */
	u32 sa_रक्षित2_pkts[2];
	/*! The number of पूर्णांकegrity रक्षित but not encrypted packets
	 *  क्रम this transmitting SA.
	 */
	u32 sa_रक्षित_pkts[2];
	/*! The number of पूर्णांकegrity रक्षित and encrypted packets क्रम
	 *  this transmitting SA.
	 */
	u32 sa_encrypted_pkts[2];
पूर्ण;

/*! Represents the common Egress MIB counters; the counter not
 *  associated with a particular SC/SA. Counters are 64 bits, lower 32
 *  bits in field[0].
 */
काष्ठा aq_mss_egress_common_counters अणु
	/*! The number of transmitted packets classअगरied as MAC_CTL packets. */
	u32 ctl_pkt[2];
	/*! The number of transmitted packets that did not match any rows
	 *  in the Egress Packet Classअगरier table.
	 */
	u32 unknown_sa_pkts[2];
	/*! The number of transmitted packets where the SC table entry has
	 *  protect=0 (so packets are क्रमwarded unchanged).
	 */
	u32 untagged_pkts[2];
	/*! The number of transmitted packets discarded because the packet
	 *  length is greater than the अगरMtu of the Common Port पूर्णांकerface.
	 */
	u32 too_दीर्घ[2];
	/*! The number of transmitted packets क्रम which table memory was
	 *  affected by an ECC error during processing.
	 */
	u32 ecc_error_pkts[2];
	/*! The number of transmitted packets क्रम where the matched row in
	 *  the Egress Packet Classअगरier table has action=drop.
	 */
	u32 unctrl_hit_drop_redir[2];
पूर्ण;

/*! Represents the Ingress MIB counters क्रम a single SA. Counters are
 *  64 bits, lower 32 bits in field[0].
 */
काष्ठा aq_mss_ingress_sa_counters अणु
	/*! For this SA, the number of received packets without a SecTAG. */
	u32 untagged_hit_pkts[2];
	/*! For this SA, the number of received packets that were dropped. */
	u32 ctrl_hit_drop_redir_pkts[2];
	/*! For this SA which is not currently in use, the number of
	 *  received packets that have been discarded, and have either the
	 *  packets encrypted or the matched row in the Ingress SC Lookup
	 *  table has validate_frames=Strict.
	 */
	u32 not_using_sa[2];
	/*! For this SA which is not currently in use, the number of
	 *  received, unencrypted, packets with the matched row in the
	 *  Ingress SC Lookup table has validate_frames!=Strict.
	 */
	u32 unused_sa[2];
	/*! For this SA, the number discarded packets with the condition
	 *  that the packets are not valid and one of the following
	 *  conditions are true: either the matched row in the Ingress SC
	 *  Lookup table has validate_frames=Strict or the packets
	 *  encrypted.
	 */
	u32 not_valid_pkts[2];
	/*! For this SA, the number of packets with the condition that the
	 *  packets are not valid and the matched row in the Ingress SC
	 *  Lookup table has validate_frames=Check.
	 */
	u32 invalid_pkts[2];
	/*! For this SA, the number of validated packets. */
	u32 ok_pkts[2];
	/*! For this SC, the number of received packets that have been
	 *  discarded with the condition: the matched row in the Ingress
	 *  SC Lookup table has replay_protect=1 and the PN of the packet
	 *  is lower than the lower bound replay check PN.
	 */
	u32 late_pkts[2];
	/*! For this SA, the number of packets with the condition that the
	 *  PN of the packets is lower than the lower bound replay
	 *  protection PN.
	 */
	u32 delayed_pkts[2];
	/*! For this SC, the number of packets with the following condition:
	 *  - the matched row in the Ingress SC Lookup table has
	 *    replay_protect=0 or
	 *  - the matched row in the Ingress SC Lookup table has
	 *    replay_protect=1 and the packet is not encrypted and the
	 *    पूर्णांकegrity check has failed or
	 *  - the matched row in the Ingress SC Lookup table has
	 *    replay_protect=1 and the packet is encrypted and पूर्णांकegrity
	 *    check has failed.
	 */
	u32 unchecked_pkts[2];
	/*! The number of octets of plaपूर्णांकext recovered from received
	 *  packets that were पूर्णांकegrity रक्षित but not encrypted.
	 */
	u32 validated_octets[2];
	/*! The number of octets of plaपूर्णांकext recovered from received
	 *  packets that were पूर्णांकegrity रक्षित and encrypted.
	 */
	u32 decrypted_octets[2];
पूर्ण;

/*! Represents the common Ingress MIB counters; the counter not
 *  associated with a particular SA. Counters are 64 bits, lower 32
 *  bits in field[0].
 */
काष्ठा aq_mss_ingress_common_counters अणु
	/*! The number of received packets classअगरied as MAC_CTL packets. */
	u32 ctl_pkts[2];
	/*! The number of received packets with the MAC security tag
	 *  (SecTAG), not matching any rows in the Ingress Pre-MACSec
	 *  Packet Classअगरier table.
	 */
	u32 tagged_miss_pkts[2];
	/*! The number of received packets without the MAC security tag
	 *  (SecTAG), not matching any rows in the Ingress Pre-MACSec
	 *  Packet Classअगरier table.
	 */
	u32 untagged_miss_pkts[2];
	/*! The number of received packets discarded without the MAC
	 *  security tag (SecTAG) and with the matched row in the Ingress
	 *  SC Lookup table having validate_frames=Strict.
	 */
	u32 notag_pkts[2];
	/*! The number of received packets without the MAC security tag
	 *  (SecTAG) and with the matched row in the Ingress SC Lookup
	 *  table having validate_frames!=Strict.
	 */
	u32 untagged_pkts[2];
	/*! The number of received packets discarded with an invalid
	 *  SecTAG or a zero value PN or an invalid ICV.
	 */
	u32 bad_tag_pkts[2];
	/*! The number of received packets discarded with unknown SCI
	 *  inक्रमmation with the condition:
	 *  the matched row in the Ingress SC Lookup table has
	 *  validate_frames=Strict or the C bit in the SecTAG is set.
	 */
	u32 no_sci_pkts[2];
	/*! The number of received packets with unknown SCI with the condition:
	 *  The matched row in the Ingress SC Lookup table has
	 *  validate_frames!=Strict and the C bit in the SecTAG is not set.
	 */
	u32 unknown_sci_pkts[2];
	/*! The number of received packets by the controlled port service
	 *  that passed the Ingress Post-MACSec Packet Classअगरier table
	 *  check.
	 */
	u32 ctrl_prt_pass_pkts[2];
	/*! The number of received packets by the uncontrolled port
	 *  service that passed the Ingress Post-MACSec Packet Classअगरier
	 *  table check.
	 */
	u32 unctrl_prt_pass_pkts[2];
	/*! The number of received packets by the controlled port service
	 *  that failed the Ingress Post-MACSec Packet Classअगरier table
	 *  check.
	 */
	u32 ctrl_prt_fail_pkts[2];
	/*! The number of received packets by the uncontrolled port
	 *  service that failed the Ingress Post-MACSec Packet Classअगरier
	 *  table check.
	 */
	u32 unctrl_prt_fail_pkts[2];
	/*! The number of received packets discarded because the packet
	 *  length is greater than the अगरMtu of the Common Port पूर्णांकerface.
	 */
	u32 too_दीर्घ_pkts[2];
	/*! The number of received packets classअगरied as MAC_CTL by the
	 *  Ingress Post-MACSec CTL Filter table.
	 */
	u32 igpoc_ctl_pkts[2];
	/*! The number of received packets क्रम which table memory was
	 *  affected by an ECC error during processing.
	 */
	u32 ecc_error_pkts[2];
	/*! The number of received packets by the uncontrolled port
	 *  service that were dropped.
	 */
	u32 unctrl_hit_drop_redir[2];
पूर्ण;

#पूर्ण_अगर
