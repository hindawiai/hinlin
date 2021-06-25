<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice_common.h"
#समावेश "ice_flex_pipe.h"
#समावेश "ice_flow.h"

/* To support tunneling entries by PF, the package will append the PF number to
 * the label; क्रम example TNL_VXLAN_PF0, TNL_VXLAN_PF1, TNL_VXLAN_PF2, etc.
 */
अटल स्थिर काष्ठा ice_tunnel_type_scan tnls[] = अणु
	अणु TNL_VXLAN,		"TNL_VXLAN_PF" पूर्ण,
	अणु TNL_GENEVE,		"TNL_GENEVE_PF" पूर्ण,
	अणु TNL_LAST,		"" पूर्ण
पूर्ण;

अटल स्थिर u32 ice_sect_lkup[ICE_BLK_COUNT][ICE_SECT_COUNT] = अणु
	/* SWITCH */
	अणु
		ICE_SID_XLT0_SW,
		ICE_SID_XLT_KEY_BUILDER_SW,
		ICE_SID_XLT1_SW,
		ICE_SID_XLT2_SW,
		ICE_SID_PROFID_TCAM_SW,
		ICE_SID_PROFID_REसूची_SW,
		ICE_SID_FLD_VEC_SW,
		ICE_SID_CDID_KEY_BUILDER_SW,
		ICE_SID_CDID_REसूची_SW
	पूर्ण,

	/* ACL */
	अणु
		ICE_SID_XLT0_ACL,
		ICE_SID_XLT_KEY_BUILDER_ACL,
		ICE_SID_XLT1_ACL,
		ICE_SID_XLT2_ACL,
		ICE_SID_PROFID_TCAM_ACL,
		ICE_SID_PROFID_REसूची_ACL,
		ICE_SID_FLD_VEC_ACL,
		ICE_SID_CDID_KEY_BUILDER_ACL,
		ICE_SID_CDID_REसूची_ACL
	पूर्ण,

	/* FD */
	अणु
		ICE_SID_XLT0_FD,
		ICE_SID_XLT_KEY_BUILDER_FD,
		ICE_SID_XLT1_FD,
		ICE_SID_XLT2_FD,
		ICE_SID_PROFID_TCAM_FD,
		ICE_SID_PROFID_REसूची_FD,
		ICE_SID_FLD_VEC_FD,
		ICE_SID_CDID_KEY_BUILDER_FD,
		ICE_SID_CDID_REसूची_FD
	पूर्ण,

	/* RSS */
	अणु
		ICE_SID_XLT0_RSS,
		ICE_SID_XLT_KEY_BUILDER_RSS,
		ICE_SID_XLT1_RSS,
		ICE_SID_XLT2_RSS,
		ICE_SID_PROFID_TCAM_RSS,
		ICE_SID_PROFID_REसूची_RSS,
		ICE_SID_FLD_VEC_RSS,
		ICE_SID_CDID_KEY_BUILDER_RSS,
		ICE_SID_CDID_REसूची_RSS
	पूर्ण,

	/* PE */
	अणु
		ICE_SID_XLT0_PE,
		ICE_SID_XLT_KEY_BUILDER_PE,
		ICE_SID_XLT1_PE,
		ICE_SID_XLT2_PE,
		ICE_SID_PROFID_TCAM_PE,
		ICE_SID_PROFID_REसूची_PE,
		ICE_SID_FLD_VEC_PE,
		ICE_SID_CDID_KEY_BUILDER_PE,
		ICE_SID_CDID_REसूची_PE
	पूर्ण
पूर्ण;

/**
 * ice_sect_id - वापसs section ID
 * @blk: block type
 * @sect: section type
 *
 * This helper function वापसs the proper section ID given a block type and a
 * section type.
 */
अटल u32 ice_sect_id(क्रमागत ice_block blk, क्रमागत ice_sect sect)
अणु
	वापस ice_sect_lkup[blk][sect];
पूर्ण

/**
 * ice_pkg_val_buf
 * @buf: poपूर्णांकer to the ice buffer
 *
 * This helper function validates a buffer's header.
 */
अटल काष्ठा ice_buf_hdr *ice_pkg_val_buf(काष्ठा ice_buf *buf)
अणु
	काष्ठा ice_buf_hdr *hdr;
	u16 section_count;
	u16 data_end;

	hdr = (काष्ठा ice_buf_hdr *)buf->buf;
	/* verअगरy data */
	section_count = le16_to_cpu(hdr->section_count);
	अगर (section_count < ICE_MIN_S_COUNT || section_count > ICE_MAX_S_COUNT)
		वापस शून्य;

	data_end = le16_to_cpu(hdr->data_end);
	अगर (data_end < ICE_MIN_S_DATA_END || data_end > ICE_MAX_S_DATA_END)
		वापस शून्य;

	वापस hdr;
पूर्ण

/**
 * ice_find_buf_table
 * @ice_seg: poपूर्णांकer to the ice segment
 *
 * Returns the address of the buffer table within the ice segment.
 */
अटल काष्ठा ice_buf_table *ice_find_buf_table(काष्ठा ice_seg *ice_seg)
अणु
	काष्ठा ice_nvm_table *nvms;

	nvms = (काष्ठा ice_nvm_table *)
		(ice_seg->device_table +
		 le32_to_cpu(ice_seg->device_table_count));

	वापस (__क्रमce काष्ठा ice_buf_table *)
		(nvms->vers + le32_to_cpu(nvms->table_count));
पूर्ण

/**
 * ice_pkg_क्रमागत_buf
 * @ice_seg: poपूर्णांकer to the ice segment (or शून्य on subsequent calls)
 * @state: poपूर्णांकer to the क्रमागत state
 *
 * This function will क्रमागतerate all the buffers in the ice segment. The first
 * call is made with the ice_seg parameter non-शून्य; on subsequent calls,
 * ice_seg is set to शून्य which जारीs the क्रमागतeration. When the function
 * वापसs a शून्य poपूर्णांकer, then the end of the buffers has been reached, or an
 * unexpected value has been detected (क्रम example an invalid section count or
 * an invalid buffer end value).
 */
अटल काष्ठा ice_buf_hdr *
ice_pkg_क्रमागत_buf(काष्ठा ice_seg *ice_seg, काष्ठा ice_pkg_क्रमागत *state)
अणु
	अगर (ice_seg) अणु
		state->buf_table = ice_find_buf_table(ice_seg);
		अगर (!state->buf_table)
			वापस शून्य;

		state->buf_idx = 0;
		वापस ice_pkg_val_buf(state->buf_table->buf_array);
	पूर्ण

	अगर (++state->buf_idx < le32_to_cpu(state->buf_table->buf_count))
		वापस ice_pkg_val_buf(state->buf_table->buf_array +
				       state->buf_idx);
	अन्यथा
		वापस शून्य;
पूर्ण

/**
 * ice_pkg_advance_sect
 * @ice_seg: poपूर्णांकer to the ice segment (or शून्य on subsequent calls)
 * @state: poपूर्णांकer to the क्रमागत state
 *
 * This helper function will advance the section within the ice segment,
 * also advancing the buffer अगर needed.
 */
अटल bool
ice_pkg_advance_sect(काष्ठा ice_seg *ice_seg, काष्ठा ice_pkg_क्रमागत *state)
अणु
	अगर (!ice_seg && !state->buf)
		वापस false;

	अगर (!ice_seg && state->buf)
		अगर (++state->sect_idx < le16_to_cpu(state->buf->section_count))
			वापस true;

	state->buf = ice_pkg_क्रमागत_buf(ice_seg, state);
	अगर (!state->buf)
		वापस false;

	/* start of new buffer, reset section index */
	state->sect_idx = 0;
	वापस true;
पूर्ण

/**
 * ice_pkg_क्रमागत_section
 * @ice_seg: poपूर्णांकer to the ice segment (or शून्य on subsequent calls)
 * @state: poपूर्णांकer to the क्रमागत state
 * @sect_type: section type to क्रमागतerate
 *
 * This function will क्रमागतerate all the sections of a particular type in the
 * ice segment. The first call is made with the ice_seg parameter non-शून्य;
 * on subsequent calls, ice_seg is set to शून्य which जारीs the क्रमागतeration.
 * When the function वापसs a शून्य poपूर्णांकer, then the end of the matching
 * sections has been reached.
 */
अटल व्योम *
ice_pkg_क्रमागत_section(काष्ठा ice_seg *ice_seg, काष्ठा ice_pkg_क्रमागत *state,
		     u32 sect_type)
अणु
	u16 offset, size;

	अगर (ice_seg)
		state->type = sect_type;

	अगर (!ice_pkg_advance_sect(ice_seg, state))
		वापस शून्य;

	/* scan क्रम next matching section */
	जबतक (state->buf->section_entry[state->sect_idx].type !=
	       cpu_to_le32(state->type))
		अगर (!ice_pkg_advance_sect(शून्य, state))
			वापस शून्य;

	/* validate section */
	offset = le16_to_cpu(state->buf->section_entry[state->sect_idx].offset);
	अगर (offset < ICE_MIN_S_OFF || offset > ICE_MAX_S_OFF)
		वापस शून्य;

	size = le16_to_cpu(state->buf->section_entry[state->sect_idx].size);
	अगर (size < ICE_MIN_S_SZ || size > ICE_MAX_S_SZ)
		वापस शून्य;

	/* make sure the section fits in the buffer */
	अगर (offset + size > ICE_PKG_BUF_SIZE)
		वापस शून्य;

	state->sect_type =
		le32_to_cpu(state->buf->section_entry[state->sect_idx].type);

	/* calc poपूर्णांकer to this section */
	state->sect = ((u8 *)state->buf) +
		le16_to_cpu(state->buf->section_entry[state->sect_idx].offset);

	वापस state->sect;
पूर्ण

/**
 * ice_pkg_क्रमागत_entry
 * @ice_seg: poपूर्णांकer to the ice segment (or शून्य on subsequent calls)
 * @state: poपूर्णांकer to the क्रमागत state
 * @sect_type: section type to क्रमागतerate
 * @offset: poपूर्णांकer to variable that receives the offset in the table (optional)
 * @handler: function that handles access to the entries पूर्णांकo the section type
 *
 * This function will क्रमागतerate all the entries in particular section type in
 * the ice segment. The first call is made with the ice_seg parameter non-शून्य;
 * on subsequent calls, ice_seg is set to शून्य which जारीs the क्रमागतeration.
 * When the function वापसs a शून्य poपूर्णांकer, then the end of the entries has
 * been reached.
 *
 * Since each section may have a dअगरferent header and entry size, the handler
 * function is needed to determine the number and location entries in each
 * section.
 *
 * The offset parameter is optional, but should be used क्रम sections that
 * contain an offset क्रम each section table. For such हालs, the section handler
 * function must वापस the appropriate offset + index to give the असलolution
 * offset क्रम each entry. For example, अगर the base क्रम a section's header
 * indicates a base offset of 10, and the index क्रम the entry is 2, then
 * section handler function should set the offset to 10 + 2 = 12.
 */
अटल व्योम *
ice_pkg_क्रमागत_entry(काष्ठा ice_seg *ice_seg, काष्ठा ice_pkg_क्रमागत *state,
		   u32 sect_type, u32 *offset,
		   व्योम *(*handler)(u32 sect_type, व्योम *section,
				    u32 index, u32 *offset))
अणु
	व्योम *entry;

	अगर (ice_seg) अणु
		अगर (!handler)
			वापस शून्य;

		अगर (!ice_pkg_क्रमागत_section(ice_seg, state, sect_type))
			वापस शून्य;

		state->entry_idx = 0;
		state->handler = handler;
	पूर्ण अन्यथा अणु
		state->entry_idx++;
	पूर्ण

	अगर (!state->handler)
		वापस शून्य;

	/* get entry */
	entry = state->handler(state->sect_type, state->sect, state->entry_idx,
			       offset);
	अगर (!entry) अणु
		/* end of a section, look क्रम another section of this type */
		अगर (!ice_pkg_क्रमागत_section(शून्य, state, 0))
			वापस शून्य;

		state->entry_idx = 0;
		entry = state->handler(state->sect_type, state->sect,
				       state->entry_idx, offset);
	पूर्ण

	वापस entry;
पूर्ण

/**
 * ice_boost_tcam_handler
 * @sect_type: section type
 * @section: poपूर्णांकer to section
 * @index: index of the boost TCAM entry to be वापसed
 * @offset: poपूर्णांकer to receive असलolute offset, always 0 क्रम boost TCAM sections
 *
 * This is a callback function that can be passed to ice_pkg_क्रमागत_entry.
 * Handles क्रमागतeration of inभागidual boost TCAM entries.
 */
अटल व्योम *
ice_boost_tcam_handler(u32 sect_type, व्योम *section, u32 index, u32 *offset)
अणु
	काष्ठा ice_boost_tcam_section *boost;

	अगर (!section)
		वापस शून्य;

	अगर (sect_type != ICE_SID_RXPARSER_BOOST_TCAM)
		वापस शून्य;

	/* cppcheck-suppress nullPoपूर्णांकer */
	अगर (index > ICE_MAX_BST_TCAMS_IN_BUF)
		वापस शून्य;

	अगर (offset)
		*offset = 0;

	boost = section;
	अगर (index >= le16_to_cpu(boost->count))
		वापस शून्य;

	वापस boost->tcam + index;
पूर्ण

/**
 * ice_find_boost_entry
 * @ice_seg: poपूर्णांकer to the ice segment (non-शून्य)
 * @addr: Boost TCAM address of entry to search क्रम
 * @entry: वापसs poपूर्णांकer to the entry
 *
 * Finds a particular Boost TCAM entry and वापसs a poपूर्णांकer to that entry
 * अगर it is found. The ice_seg parameter must not be शून्य since the first call
 * to ice_pkg_क्रमागत_entry requires a poपूर्णांकer to an actual ice_segment काष्ठाure.
 */
अटल क्रमागत ice_status
ice_find_boost_entry(काष्ठा ice_seg *ice_seg, u16 addr,
		     काष्ठा ice_boost_tcam_entry **entry)
अणु
	काष्ठा ice_boost_tcam_entry *tcam;
	काष्ठा ice_pkg_क्रमागत state;

	स_रखो(&state, 0, माप(state));

	अगर (!ice_seg)
		वापस ICE_ERR_PARAM;

	करो अणु
		tcam = ice_pkg_क्रमागत_entry(ice_seg, &state,
					  ICE_SID_RXPARSER_BOOST_TCAM, शून्य,
					  ice_boost_tcam_handler);
		अगर (tcam && le16_to_cpu(tcam->addr) == addr) अणु
			*entry = tcam;
			वापस 0;
		पूर्ण

		ice_seg = शून्य;
	पूर्ण जबतक (tcam);

	*entry = शून्य;
	वापस ICE_ERR_CFG;
पूर्ण

/**
 * ice_label_क्रमागत_handler
 * @sect_type: section type
 * @section: poपूर्णांकer to section
 * @index: index of the label entry to be वापसed
 * @offset: poपूर्णांकer to receive असलolute offset, always zero क्रम label sections
 *
 * This is a callback function that can be passed to ice_pkg_क्रमागत_entry.
 * Handles क्रमागतeration of inभागidual label entries.
 */
अटल व्योम *
ice_label_क्रमागत_handler(u32 __always_unused sect_type, व्योम *section, u32 index,
		       u32 *offset)
अणु
	काष्ठा ice_label_section *labels;

	अगर (!section)
		वापस शून्य;

	/* cppcheck-suppress nullPoपूर्णांकer */
	अगर (index > ICE_MAX_LABELS_IN_BUF)
		वापस शून्य;

	अगर (offset)
		*offset = 0;

	labels = section;
	अगर (index >= le16_to_cpu(labels->count))
		वापस शून्य;

	वापस labels->label + index;
पूर्ण

/**
 * ice_क्रमागत_labels
 * @ice_seg: poपूर्णांकer to the ice segment (शून्य on subsequent calls)
 * @type: the section type that will contain the label (0 on subsequent calls)
 * @state: ice_pkg_क्रमागत काष्ठाure that will hold the state of the क्रमागतeration
 * @value: poपूर्णांकer to a value that will वापस the label's value अगर found
 *
 * Enumerates a list of labels in the package. The caller will call
 * ice_क्रमागत_labels(ice_seg, type, ...) to start the क्रमागतeration, then call
 * ice_क्रमागत_labels(शून्य, 0, ...) to जारी. When the function वापसs a शून्य
 * the end of the list has been reached.
 */
अटल अक्षर *
ice_क्रमागत_labels(काष्ठा ice_seg *ice_seg, u32 type, काष्ठा ice_pkg_क्रमागत *state,
		u16 *value)
अणु
	काष्ठा ice_label *label;

	/* Check क्रम valid label section on first call */
	अगर (type && !(type >= ICE_SID_LBL_FIRST && type <= ICE_SID_LBL_LAST))
		वापस शून्य;

	label = ice_pkg_क्रमागत_entry(ice_seg, state, type, शून्य,
				   ice_label_क्रमागत_handler);
	अगर (!label)
		वापस शून्य;

	*value = le16_to_cpu(label->value);
	वापस label->name;
पूर्ण

/**
 * ice_init_pkg_hपूर्णांकs
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @ice_seg: poपूर्णांकer to the segment of the package scan (non-शून्य)
 *
 * This function will scan the package and save off relevant inक्रमmation
 * (hपूर्णांकs or metadata) क्रम driver use. The ice_seg parameter must not be शून्य
 * since the first call to ice_क्रमागत_labels requires a poपूर्णांकer to an actual
 * ice_seg काष्ठाure.
 */
अटल व्योम ice_init_pkg_hपूर्णांकs(काष्ठा ice_hw *hw, काष्ठा ice_seg *ice_seg)
अणु
	काष्ठा ice_pkg_क्रमागत state;
	अक्षर *label_name;
	u16 val;
	पूर्णांक i;

	स_रखो(&hw->tnl, 0, माप(hw->tnl));
	स_रखो(&state, 0, माप(state));

	अगर (!ice_seg)
		वापस;

	label_name = ice_क्रमागत_labels(ice_seg, ICE_SID_LBL_RXPARSER_TMEM, &state,
				     &val);

	जबतक (label_name && hw->tnl.count < ICE_TUNNEL_MAX_ENTRIES) अणु
		क्रम (i = 0; tnls[i].type != TNL_LAST; i++) अणु
			माप_प्रकार len = म_माप(tnls[i].label_prefix);

			/* Look क्रम matching label start, beक्रमe continuing */
			अगर (म_भेदन(label_name, tnls[i].label_prefix, len))
				जारी;

			/* Make sure this label matches our PF. Note that the PF
			 * अक्षरacter ('0' - '7') will be located where our
			 * prefix string's null terminator is located.
			 */
			अगर ((label_name[len] - '0') == hw->pf_id) अणु
				hw->tnl.tbl[hw->tnl.count].type = tnls[i].type;
				hw->tnl.tbl[hw->tnl.count].valid = false;
				hw->tnl.tbl[hw->tnl.count].boost_addr = val;
				hw->tnl.tbl[hw->tnl.count].port = 0;
				hw->tnl.count++;
				अवरोध;
			पूर्ण
		पूर्ण

		label_name = ice_क्रमागत_labels(शून्य, 0, &state, &val);
	पूर्ण

	/* Cache the appropriate boost TCAM entry poपूर्णांकers */
	क्रम (i = 0; i < hw->tnl.count; i++) अणु
		ice_find_boost_entry(ice_seg, hw->tnl.tbl[i].boost_addr,
				     &hw->tnl.tbl[i].boost_entry);
		अगर (hw->tnl.tbl[i].boost_entry) अणु
			hw->tnl.tbl[i].valid = true;
			अगर (hw->tnl.tbl[i].type < __TNL_TYPE_CNT)
				hw->tnl.valid_count[hw->tnl.tbl[i].type]++;
		पूर्ण
	पूर्ण
पूर्ण

/* Key creation */

#घोषणा ICE_DC_KEY	0x1	/* करोn't care */
#घोषणा ICE_DC_KEYINV	0x1
#घोषणा ICE_NM_KEY	0x0	/* never match */
#घोषणा ICE_NM_KEYINV	0x0
#घोषणा ICE_0_KEY	0x1	/* match 0 */
#घोषणा ICE_0_KEYINV	0x0
#घोषणा ICE_1_KEY	0x0	/* match 1 */
#घोषणा ICE_1_KEYINV	0x1

/**
 * ice_gen_key_word - generate 16-bits of a key/mask word
 * @val: the value
 * @valid: valid bits mask (change only the valid bits)
 * @करोnt_care: करोn't care mask
 * @nvr_mtch: never match mask
 * @key: poपूर्णांकer to an array of where the resulting key portion
 * @key_inv: poपूर्णांकer to an array of where the resulting key invert portion
 *
 * This function generates 16-bits from a 8-bit value, an 8-bit करोn't care mask
 * and an 8-bit never match mask. The 16-bits of output are भागided पूर्णांकo 8 bits
 * of key and 8 bits of key invert.
 *
 *     '0' =    b01, always match a 0 bit
 *     '1' =    b10, always match a 1 bit
 *     '?' =    b11, don't care bit (always matches)
 *     '~' =    b00, never match bit
 *
 * Input:
 *          val:         b0  1  0  1  0  1
 *          करोnt_care:   b0  0  1  1  0  0
 *          never_mtch:  b0  0  0  0  1  1
 *          ------------------------------
 * Result:  key:        b01 10 11 11 00 00
 */
अटल क्रमागत ice_status
ice_gen_key_word(u8 val, u8 valid, u8 करोnt_care, u8 nvr_mtch, u8 *key,
		 u8 *key_inv)
अणु
	u8 in_key = *key, in_key_inv = *key_inv;
	u8 i;

	/* 'dont_care' and 'nvr_mtch' masks cannot overlap */
	अगर ((करोnt_care ^ nvr_mtch) != (करोnt_care | nvr_mtch))
		वापस ICE_ERR_CFG;

	*key = 0;
	*key_inv = 0;

	/* encode the 8 bits पूर्णांकo 8-bit key and 8-bit key invert */
	क्रम (i = 0; i < 8; i++) अणु
		*key >>= 1;
		*key_inv >>= 1;

		अगर (!(valid & 0x1)) अणु /* change only valid bits */
			*key |= (in_key & 0x1) << 7;
			*key_inv |= (in_key_inv & 0x1) << 7;
		पूर्ण अन्यथा अगर (करोnt_care & 0x1) अणु /* करोn't care bit */
			*key |= ICE_DC_KEY << 7;
			*key_inv |= ICE_DC_KEYINV << 7;
		पूर्ण अन्यथा अगर (nvr_mtch & 0x1) अणु /* never match bit */
			*key |= ICE_NM_KEY << 7;
			*key_inv |= ICE_NM_KEYINV << 7;
		पूर्ण अन्यथा अगर (val & 0x01) अणु /* exact 1 match */
			*key |= ICE_1_KEY << 7;
			*key_inv |= ICE_1_KEYINV << 7;
		पूर्ण अन्यथा अणु /* exact 0 match */
			*key |= ICE_0_KEY << 7;
			*key_inv |= ICE_0_KEYINV << 7;
		पूर्ण

		करोnt_care >>= 1;
		nvr_mtch >>= 1;
		valid >>= 1;
		val >>= 1;
		in_key >>= 1;
		in_key_inv >>= 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_bits_max_set - determine अगर the number of bits set is within a maximum
 * @mask: poपूर्णांकer to the byte array which is the mask
 * @size: the number of bytes in the mask
 * @max: the max number of set bits
 *
 * This function determines अगर there are at most 'max' number of bits set in an
 * array. Returns true अगर the number क्रम bits set is <= max or will वापस false
 * otherwise.
 */
अटल bool ice_bits_max_set(स्थिर u8 *mask, u16 size, u16 max)
अणु
	u16 count = 0;
	u16 i;

	/* check each byte */
	क्रम (i = 0; i < size; i++) अणु
		/* अगर 0, go to next byte */
		अगर (!mask[i])
			जारी;

		/* We know there is at least one set bit in this byte because of
		 * the above check; अगर we alपढ़ोy have found 'max' number of
		 * bits set, then we can वापस failure now.
		 */
		अगर (count == max)
			वापस false;

		/* count the bits in this byte, checking threshold */
		count += hweight8(mask[i]);
		अगर (count > max)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ice_set_key - generate a variable sized key with multiples of 16-bits
 * @key: poपूर्णांकer to where the key will be stored
 * @size: the size of the complete key in bytes (must be even)
 * @val: array of 8-bit values that makes up the value portion of the key
 * @upd: array of 8-bit masks that determine what key portion to update
 * @dc: array of 8-bit masks that make up the करोn't care mask
 * @nm: array of 8-bit masks that make up the never match mask
 * @off: the offset of the first byte in the key to update
 * @len: the number of bytes in the key update
 *
 * This function generates a key from a value, a करोn't care mask and a never
 * match mask.
 * upd, dc, and nm are optional parameters, and can be शून्य:
 *	upd == शून्य --> upd mask is all 1's (update all bits)
 *	dc == शून्य --> dc mask is all 0's (no don't care bits)
 *	nm == शून्य --> nm mask is all 0's (no never match bits)
 */
अटल क्रमागत ice_status
ice_set_key(u8 *key, u16 size, u8 *val, u8 *upd, u8 *dc, u8 *nm, u16 off,
	    u16 len)
अणु
	u16 half_size;
	u16 i;

	/* size must be a multiple of 2 bytes. */
	अगर (size % 2)
		वापस ICE_ERR_CFG;

	half_size = size / 2;
	अगर (off + len > half_size)
		वापस ICE_ERR_CFG;

	/* Make sure at most one bit is set in the never match mask. Having more
	 * than one never match mask bit set will cause HW to consume excessive
	 * घातer otherwise; this is a घातer management efficiency check.
	 */
#घोषणा ICE_NVR_MTCH_BITS_MAX	1
	अगर (nm && !ice_bits_max_set(nm, len, ICE_NVR_MTCH_BITS_MAX))
		वापस ICE_ERR_CFG;

	क्रम (i = 0; i < len; i++)
		अगर (ice_gen_key_word(val[i], upd ? upd[i] : 0xff,
				     dc ? dc[i] : 0, nm ? nm[i] : 0,
				     key + off + i, key + half_size + off + i))
			वापस ICE_ERR_CFG;

	वापस 0;
पूर्ण

/**
 * ice_acquire_global_cfg_lock
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @access: access type (पढ़ो or ग_लिखो)
 *
 * This function will request ownership of the global config lock क्रम पढ़ोing
 * or writing of the package. When attempting to obtain ग_लिखो access, the
 * caller must check क्रम the following two वापस values:
 *
 * ICE_SUCCESS        - Means the caller has acquired the global config lock
 *                      and can perक्रमm writing of the package.
 * ICE_ERR_AQ_NO_WORK - Indicates another driver has alपढ़ोy written the
 *                      package or has found that no update was necessary; in
 *                      this हाल, the caller can just skip perक्रमming any
 *                      update of the package.
 */
अटल क्रमागत ice_status
ice_acquire_global_cfg_lock(काष्ठा ice_hw *hw,
			    क्रमागत ice_aq_res_access_type access)
अणु
	क्रमागत ice_status status;

	status = ice_acquire_res(hw, ICE_GLOBAL_CFG_LOCK_RES_ID, access,
				 ICE_GLOBAL_CFG_LOCK_TIMEOUT);

	अगर (!status)
		mutex_lock(&ice_global_cfg_lock_sw);
	अन्यथा अगर (status == ICE_ERR_AQ_NO_WORK)
		ice_debug(hw, ICE_DBG_PKG, "Global config lock: No work to do\n");

	वापस status;
पूर्ण

/**
 * ice_release_global_cfg_lock
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function will release the global config lock.
 */
अटल व्योम ice_release_global_cfg_lock(काष्ठा ice_hw *hw)
अणु
	mutex_unlock(&ice_global_cfg_lock_sw);
	ice_release_res(hw, ICE_GLOBAL_CFG_LOCK_RES_ID);
पूर्ण

/**
 * ice_acquire_change_lock
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @access: access type (पढ़ो or ग_लिखो)
 *
 * This function will request ownership of the change lock.
 */
अटल क्रमागत ice_status
ice_acquire_change_lock(काष्ठा ice_hw *hw, क्रमागत ice_aq_res_access_type access)
अणु
	वापस ice_acquire_res(hw, ICE_CHANGE_LOCK_RES_ID, access,
			       ICE_CHANGE_LOCK_TIMEOUT);
पूर्ण

/**
 * ice_release_change_lock
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function will release the change lock using the proper Admin Command.
 */
अटल व्योम ice_release_change_lock(काष्ठा ice_hw *hw)
अणु
	ice_release_res(hw, ICE_CHANGE_LOCK_RES_ID);
पूर्ण

/**
 * ice_aq_करोwnload_pkg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @pkg_buf: the package buffer to transfer
 * @buf_size: the size of the package buffer
 * @last_buf: last buffer indicator
 * @error_offset: वापसs error offset
 * @error_info: वापसs error inक्रमmation
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Download Package (0x0C40)
 */
अटल क्रमागत ice_status
ice_aq_करोwnload_pkg(काष्ठा ice_hw *hw, काष्ठा ice_buf_hdr *pkg_buf,
		    u16 buf_size, bool last_buf, u32 *error_offset,
		    u32 *error_info, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_करोwnload_pkg *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (error_offset)
		*error_offset = 0;
	अगर (error_info)
		*error_info = 0;

	cmd = &desc.params.करोwnload_pkg;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_करोwnload_pkg);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	अगर (last_buf)
		cmd->flags |= ICE_AQC_DOWNLOAD_PKG_LAST_BUF;

	status = ice_aq_send_cmd(hw, &desc, pkg_buf, buf_size, cd);
	अगर (status == ICE_ERR_AQ_ERROR) अणु
		/* Read error from buffer only when the FW वापसed an error */
		काष्ठा ice_aqc_करोwnload_pkg_resp *resp;

		resp = (काष्ठा ice_aqc_करोwnload_pkg_resp *)pkg_buf;
		अगर (error_offset)
			*error_offset = le32_to_cpu(resp->error_offset);
		अगर (error_info)
			*error_info = le32_to_cpu(resp->error_info);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_aq_update_pkg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @pkg_buf: the package cmd buffer
 * @buf_size: the size of the package cmd buffer
 * @last_buf: last buffer indicator
 * @error_offset: वापसs error offset
 * @error_info: वापसs error inक्रमmation
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Update Package (0x0C42)
 */
अटल क्रमागत ice_status
ice_aq_update_pkg(काष्ठा ice_hw *hw, काष्ठा ice_buf_hdr *pkg_buf, u16 buf_size,
		  bool last_buf, u32 *error_offset, u32 *error_info,
		  काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_करोwnload_pkg *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	अगर (error_offset)
		*error_offset = 0;
	अगर (error_info)
		*error_info = 0;

	cmd = &desc.params.करोwnload_pkg;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_update_pkg);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);

	अगर (last_buf)
		cmd->flags |= ICE_AQC_DOWNLOAD_PKG_LAST_BUF;

	status = ice_aq_send_cmd(hw, &desc, pkg_buf, buf_size, cd);
	अगर (status == ICE_ERR_AQ_ERROR) अणु
		/* Read error from buffer only when the FW वापसed an error */
		काष्ठा ice_aqc_करोwnload_pkg_resp *resp;

		resp = (काष्ठा ice_aqc_करोwnload_pkg_resp *)pkg_buf;
		अगर (error_offset)
			*error_offset = le32_to_cpu(resp->error_offset);
		अगर (error_info)
			*error_info = le32_to_cpu(resp->error_info);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_find_seg_in_pkg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @seg_type: the segment type to search क्रम (i.e., SEGMENT_TYPE_CPK)
 * @pkg_hdr: poपूर्णांकer to the package header to be searched
 *
 * This function searches a package file क्रम a particular segment type. On
 * success it वापसs a poपूर्णांकer to the segment header, otherwise it will
 * वापस शून्य.
 */
अटल काष्ठा ice_generic_seg_hdr *
ice_find_seg_in_pkg(काष्ठा ice_hw *hw, u32 seg_type,
		    काष्ठा ice_pkg_hdr *pkg_hdr)
अणु
	u32 i;

	ice_debug(hw, ICE_DBG_PKG, "Package format version: %d.%d.%d.%d\n",
		  pkg_hdr->pkg_क्रमmat_ver.major, pkg_hdr->pkg_क्रमmat_ver.minor,
		  pkg_hdr->pkg_क्रमmat_ver.update,
		  pkg_hdr->pkg_क्रमmat_ver.draft);

	/* Search all package segments क्रम the requested segment type */
	क्रम (i = 0; i < le32_to_cpu(pkg_hdr->seg_count); i++) अणु
		काष्ठा ice_generic_seg_hdr *seg;

		seg = (काष्ठा ice_generic_seg_hdr *)
			((u8 *)pkg_hdr + le32_to_cpu(pkg_hdr->seg_offset[i]));

		अगर (le32_to_cpu(seg->seg_type) == seg_type)
			वापस seg;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ice_update_pkg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @bufs: poपूर्णांकer to an array of buffers
 * @count: the number of buffers in the array
 *
 * Obtains change lock and updates package.
 */
अटल क्रमागत ice_status
ice_update_pkg(काष्ठा ice_hw *hw, काष्ठा ice_buf *bufs, u32 count)
अणु
	क्रमागत ice_status status;
	u32 offset, info, i;

	status = ice_acquire_change_lock(hw, ICE_RES_WRITE);
	अगर (status)
		वापस status;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा ice_buf_hdr *bh = (काष्ठा ice_buf_hdr *)(bufs + i);
		bool last = ((i + 1) == count);

		status = ice_aq_update_pkg(hw, bh, le16_to_cpu(bh->data_end),
					   last, &offset, &info, शून्य);

		अगर (status) अणु
			ice_debug(hw, ICE_DBG_PKG, "Update pkg failed: err %d off %d inf %d\n",
				  status, offset, info);
			अवरोध;
		पूर्ण
	पूर्ण

	ice_release_change_lock(hw);

	वापस status;
पूर्ण

/**
 * ice_dwnld_cfg_bufs
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @bufs: poपूर्णांकer to an array of buffers
 * @count: the number of buffers in the array
 *
 * Obtains global config lock and करोwnloads the package configuration buffers
 * to the firmware. Metadata buffers are skipped, and the first metadata buffer
 * found indicates that the rest of the buffers are all metadata buffers.
 */
अटल क्रमागत ice_status
ice_dwnld_cfg_bufs(काष्ठा ice_hw *hw, काष्ठा ice_buf *bufs, u32 count)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_buf_hdr *bh;
	u32 offset, info, i;

	अगर (!bufs || !count)
		वापस ICE_ERR_PARAM;

	/* If the first buffer's first section has its metadata bit set
	 * then there are no buffers to be करोwnloaded, and the operation is
	 * considered a success.
	 */
	bh = (काष्ठा ice_buf_hdr *)bufs;
	अगर (le32_to_cpu(bh->section_entry[0].type) & ICE_METADATA_BUF)
		वापस 0;

	/* reset pkg_dwnld_status in हाल this function is called in the
	 * reset/rebuild flow
	 */
	hw->pkg_dwnld_status = ICE_AQ_RC_OK;

	status = ice_acquire_global_cfg_lock(hw, ICE_RES_WRITE);
	अगर (status) अणु
		अगर (status == ICE_ERR_AQ_NO_WORK)
			hw->pkg_dwnld_status = ICE_AQ_RC_EEXIST;
		अन्यथा
			hw->pkg_dwnld_status = hw->adminq.sq_last_status;
		वापस status;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		bool last = ((i + 1) == count);

		अगर (!last) अणु
			/* check next buffer क्रम metadata flag */
			bh = (काष्ठा ice_buf_hdr *)(bufs + i + 1);

			/* A set metadata flag in the next buffer will संकेत
			 * that the current buffer will be the last buffer
			 * करोwnloaded
			 */
			अगर (le16_to_cpu(bh->section_count))
				अगर (le32_to_cpu(bh->section_entry[0].type) &
				    ICE_METADATA_BUF)
					last = true;
		पूर्ण

		bh = (काष्ठा ice_buf_hdr *)(bufs + i);

		status = ice_aq_करोwnload_pkg(hw, bh, ICE_PKG_BUF_SIZE, last,
					     &offset, &info, शून्य);

		/* Save AQ status from करोwnload package */
		hw->pkg_dwnld_status = hw->adminq.sq_last_status;
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_PKG, "Pkg download failed: err %d off %d inf %d\n",
				  status, offset, info);

			अवरोध;
		पूर्ण

		अगर (last)
			अवरोध;
	पूर्ण

	ice_release_global_cfg_lock(hw);

	वापस status;
पूर्ण

/**
 * ice_aq_get_pkg_info_list
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @pkg_info: the buffer which will receive the inक्रमmation list
 * @buf_size: the size of the pkg_info inक्रमmation buffer
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get Package Info List (0x0C43)
 */
अटल क्रमागत ice_status
ice_aq_get_pkg_info_list(काष्ठा ice_hw *hw,
			 काष्ठा ice_aqc_get_pkg_info_resp *pkg_info,
			 u16 buf_size, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_pkg_info_list);

	वापस ice_aq_send_cmd(hw, &desc, pkg_info, buf_size, cd);
पूर्ण

/**
 * ice_करोwnload_pkg
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @ice_seg: poपूर्णांकer to the segment of the package to be करोwnloaded
 *
 * Handles the करोwnload of a complete package.
 */
अटल क्रमागत ice_status
ice_करोwnload_pkg(काष्ठा ice_hw *hw, काष्ठा ice_seg *ice_seg)
अणु
	काष्ठा ice_buf_table *ice_buf_tbl;

	ice_debug(hw, ICE_DBG_PKG, "Segment format version: %d.%d.%d.%d\n",
		  ice_seg->hdr.seg_क्रमmat_ver.major,
		  ice_seg->hdr.seg_क्रमmat_ver.minor,
		  ice_seg->hdr.seg_क्रमmat_ver.update,
		  ice_seg->hdr.seg_क्रमmat_ver.draft);

	ice_debug(hw, ICE_DBG_PKG, "Seg: type 0x%X, size %d, name %s\n",
		  le32_to_cpu(ice_seg->hdr.seg_type),
		  le32_to_cpu(ice_seg->hdr.seg_size), ice_seg->hdr.seg_id);

	ice_buf_tbl = ice_find_buf_table(ice_seg);

	ice_debug(hw, ICE_DBG_PKG, "Seg buf count: %d\n",
		  le32_to_cpu(ice_buf_tbl->buf_count));

	वापस ice_dwnld_cfg_bufs(hw, ice_buf_tbl->buf_array,
				  le32_to_cpu(ice_buf_tbl->buf_count));
पूर्ण

/**
 * ice_init_pkg_info
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @pkg_hdr: poपूर्णांकer to the driver's package hdr
 *
 * Saves off the package details पूर्णांकo the HW काष्ठाure.
 */
अटल क्रमागत ice_status
ice_init_pkg_info(काष्ठा ice_hw *hw, काष्ठा ice_pkg_hdr *pkg_hdr)
अणु
	काष्ठा ice_generic_seg_hdr *seg_hdr;

	अगर (!pkg_hdr)
		वापस ICE_ERR_PARAM;

	seg_hdr = ice_find_seg_in_pkg(hw, SEGMENT_TYPE_ICE, pkg_hdr);
	अगर (seg_hdr) अणु
		काष्ठा ice_meta_sect *meta;
		काष्ठा ice_pkg_क्रमागत state;

		स_रखो(&state, 0, माप(state));

		/* Get package inक्रमmation from the Metadata Section */
		meta = ice_pkg_क्रमागत_section((काष्ठा ice_seg *)seg_hdr, &state,
					    ICE_SID_METADATA);
		अगर (!meta) अणु
			ice_debug(hw, ICE_DBG_INIT, "Did not find ice metadata section in package\n");
			वापस ICE_ERR_CFG;
		पूर्ण

		hw->pkg_ver = meta->ver;
		स_नकल(hw->pkg_name, meta->name, माप(meta->name));

		ice_debug(hw, ICE_DBG_PKG, "Pkg: %d.%d.%d.%d, %s\n",
			  meta->ver.major, meta->ver.minor, meta->ver.update,
			  meta->ver.draft, meta->name);

		hw->ice_seg_fmt_ver = seg_hdr->seg_क्रमmat_ver;
		स_नकल(hw->ice_seg_id, seg_hdr->seg_id,
		       माप(hw->ice_seg_id));

		ice_debug(hw, ICE_DBG_PKG, "Ice Seg: %d.%d.%d.%d, %s\n",
			  seg_hdr->seg_क्रमmat_ver.major,
			  seg_hdr->seg_क्रमmat_ver.minor,
			  seg_hdr->seg_क्रमmat_ver.update,
			  seg_hdr->seg_क्रमmat_ver.draft,
			  seg_hdr->seg_id);
	पूर्ण अन्यथा अणु
		ice_debug(hw, ICE_DBG_INIT, "Did not find ice segment in driver package\n");
		वापस ICE_ERR_CFG;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_get_pkg_info
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Store details of the package currently loaded in HW पूर्णांकo the HW काष्ठाure.
 */
अटल क्रमागत ice_status ice_get_pkg_info(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aqc_get_pkg_info_resp *pkg_info;
	क्रमागत ice_status status;
	u16 size;
	u32 i;

	size = काष्ठा_size(pkg_info, pkg_info, ICE_PKG_CNT);
	pkg_info = kzalloc(size, GFP_KERNEL);
	अगर (!pkg_info)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_aq_get_pkg_info_list(hw, pkg_info, size, शून्य);
	अगर (status)
		जाओ init_pkg_मुक्त_alloc;

	क्रम (i = 0; i < le32_to_cpu(pkg_info->count); i++) अणु
#घोषणा ICE_PKG_FLAG_COUNT	4
		अक्षर flags[ICE_PKG_FLAG_COUNT + 1] = अणु 0 पूर्ण;
		u8 place = 0;

		अगर (pkg_info->pkg_info[i].is_active) अणु
			flags[place++] = 'A';
			hw->active_pkg_ver = pkg_info->pkg_info[i].ver;
			hw->active_track_id =
				le32_to_cpu(pkg_info->pkg_info[i].track_id);
			स_नकल(hw->active_pkg_name,
			       pkg_info->pkg_info[i].name,
			       माप(pkg_info->pkg_info[i].name));
			hw->active_pkg_in_nvm = pkg_info->pkg_info[i].is_in_nvm;
		पूर्ण
		अगर (pkg_info->pkg_info[i].is_active_at_boot)
			flags[place++] = 'B';
		अगर (pkg_info->pkg_info[i].is_modअगरied)
			flags[place++] = 'M';
		अगर (pkg_info->pkg_info[i].is_in_nvm)
			flags[place++] = 'N';

		ice_debug(hw, ICE_DBG_PKG, "Pkg[%d]: %d.%d.%d.%d,%s,%s\n",
			  i, pkg_info->pkg_info[i].ver.major,
			  pkg_info->pkg_info[i].ver.minor,
			  pkg_info->pkg_info[i].ver.update,
			  pkg_info->pkg_info[i].ver.draft,
			  pkg_info->pkg_info[i].name, flags);
	पूर्ण

init_pkg_मुक्त_alloc:
	kमुक्त(pkg_info);

	वापस status;
पूर्ण

/**
 * ice_verअगरy_pkg - verअगरy package
 * @pkg: poपूर्णांकer to the package buffer
 * @len: size of the package buffer
 *
 * Verअगरies various attributes of the package file, including length, क्रमmat
 * version, and the requirement of at least one segment.
 */
अटल क्रमागत ice_status ice_verअगरy_pkg(काष्ठा ice_pkg_hdr *pkg, u32 len)
अणु
	u32 seg_count;
	u32 i;

	अगर (len < काष्ठा_size(pkg, seg_offset, 1))
		वापस ICE_ERR_BUF_TOO_SHORT;

	अगर (pkg->pkg_क्रमmat_ver.major != ICE_PKG_FMT_VER_MAJ ||
	    pkg->pkg_क्रमmat_ver.minor != ICE_PKG_FMT_VER_MNR ||
	    pkg->pkg_क्रमmat_ver.update != ICE_PKG_FMT_VER_UPD ||
	    pkg->pkg_क्रमmat_ver.draft != ICE_PKG_FMT_VER_DFT)
		वापस ICE_ERR_CFG;

	/* pkg must have at least one segment */
	seg_count = le32_to_cpu(pkg->seg_count);
	अगर (seg_count < 1)
		वापस ICE_ERR_CFG;

	/* make sure segment array fits in package length */
	अगर (len < काष्ठा_size(pkg, seg_offset, seg_count))
		वापस ICE_ERR_BUF_TOO_SHORT;

	/* all segments must fit within length */
	क्रम (i = 0; i < seg_count; i++) अणु
		u32 off = le32_to_cpu(pkg->seg_offset[i]);
		काष्ठा ice_generic_seg_hdr *seg;

		/* segment header must fit */
		अगर (len < off + माप(*seg))
			वापस ICE_ERR_BUF_TOO_SHORT;

		seg = (काष्ठा ice_generic_seg_hdr *)((u8 *)pkg + off);

		/* segment body must fit */
		अगर (len < off + le32_to_cpu(seg->seg_size))
			वापस ICE_ERR_BUF_TOO_SHORT;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_मुक्त_seg - मुक्त package segment poपूर्णांकer
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Frees the package segment poपूर्णांकer in the proper manner, depending on अगर the
 * segment was allocated or just the passed in poपूर्णांकer was stored.
 */
व्योम ice_मुक्त_seg(काष्ठा ice_hw *hw)
अणु
	अगर (hw->pkg_copy) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), hw->pkg_copy);
		hw->pkg_copy = शून्य;
		hw->pkg_size = 0;
	पूर्ण
	hw->seg = शून्य;
पूर्ण

/**
 * ice_init_pkg_regs - initialize additional package रेजिस्टरs
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
अटल व्योम ice_init_pkg_regs(काष्ठा ice_hw *hw)
अणु
#घोषणा ICE_SW_BLK_INP_MASK_L 0xFFFFFFFF
#घोषणा ICE_SW_BLK_INP_MASK_H 0x0000FFFF
#घोषणा ICE_SW_BLK_IDX	0

	/* setup Switch block input mask, which is 48-bits in two parts */
	wr32(hw, GL_PREEXT_L2_PMASK0(ICE_SW_BLK_IDX), ICE_SW_BLK_INP_MASK_L);
	wr32(hw, GL_PREEXT_L2_PMASK1(ICE_SW_BLK_IDX), ICE_SW_BLK_INP_MASK_H);
पूर्ण

/**
 * ice_chk_pkg_version - check package version क्रम compatibility with driver
 * @pkg_ver: poपूर्णांकer to a version काष्ठाure to check
 *
 * Check to make sure that the package about to be करोwnloaded is compatible with
 * the driver. To be compatible, the major and minor components of the package
 * version must match our ICE_PKG_SUPP_VER_MAJ and ICE_PKG_SUPP_VER_MNR
 * definitions.
 */
अटल क्रमागत ice_status ice_chk_pkg_version(काष्ठा ice_pkg_ver *pkg_ver)
अणु
	अगर (pkg_ver->major != ICE_PKG_SUPP_VER_MAJ ||
	    pkg_ver->minor != ICE_PKG_SUPP_VER_MNR)
		वापस ICE_ERR_NOT_SUPPORTED;

	वापस 0;
पूर्ण

/**
 * ice_chk_pkg_compat
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @ospkg: poपूर्णांकer to the package hdr
 * @seg: poपूर्णांकer to the package segment hdr
 *
 * This function checks the package version compatibility with driver and NVM
 */
अटल क्रमागत ice_status
ice_chk_pkg_compat(काष्ठा ice_hw *hw, काष्ठा ice_pkg_hdr *ospkg,
		   काष्ठा ice_seg **seg)
अणु
	काष्ठा ice_aqc_get_pkg_info_resp *pkg;
	क्रमागत ice_status status;
	u16 size;
	u32 i;

	/* Check package version compatibility */
	status = ice_chk_pkg_version(&hw->pkg_ver);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "Package version check failed.\n");
		वापस status;
	पूर्ण

	/* find ICE segment in given package */
	*seg = (काष्ठा ice_seg *)ice_find_seg_in_pkg(hw, SEGMENT_TYPE_ICE,
						     ospkg);
	अगर (!*seg) अणु
		ice_debug(hw, ICE_DBG_INIT, "no ice segment in package.\n");
		वापस ICE_ERR_CFG;
	पूर्ण

	/* Check अगर FW is compatible with the OS package */
	size = काष्ठा_size(pkg, pkg_info, ICE_PKG_CNT);
	pkg = kzalloc(size, GFP_KERNEL);
	अगर (!pkg)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_aq_get_pkg_info_list(hw, pkg, size, शून्य);
	अगर (status)
		जाओ fw_ddp_compat_मुक्त_alloc;

	क्रम (i = 0; i < le32_to_cpu(pkg->count); i++) अणु
		/* loop till we find the NVM package */
		अगर (!pkg->pkg_info[i].is_in_nvm)
			जारी;
		अगर ((*seg)->hdr.seg_क्रमmat_ver.major !=
			pkg->pkg_info[i].ver.major ||
		    (*seg)->hdr.seg_क्रमmat_ver.minor >
			pkg->pkg_info[i].ver.minor) अणु
			status = ICE_ERR_FW_DDP_MISMATCH;
			ice_debug(hw, ICE_DBG_INIT, "OS package is not compatible with NVM.\n");
		पूर्ण
		/* करोne processing NVM package so अवरोध */
		अवरोध;
	पूर्ण
fw_ddp_compat_मुक्त_alloc:
	kमुक्त(pkg);
	वापस status;
पूर्ण

/**
 * ice_init_pkg - initialize/करोwnload package
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @buf: poपूर्णांकer to the package buffer
 * @len: size of the package buffer
 *
 * This function initializes a package. The package contains HW tables
 * required to करो packet processing. First, the function extracts package
 * inक्रमmation such as version. Then it finds the ice configuration segment
 * within the package; this function then saves a copy of the segment poपूर्णांकer
 * within the supplied package buffer. Next, the function will cache any hपूर्णांकs
 * from the package, followed by करोwnloading the package itself. Note, that अगर
 * a previous PF driver has alपढ़ोy करोwnloaded the package successfully, then
 * the current driver will not have to करोwnload the package again.
 *
 * The local package contents will be used to query शेष behavior and to
 * update specअगरic sections of the HW's version of the package (e.g. to update
 * the parse graph to understand new protocols).
 *
 * This function stores a poपूर्णांकer to the package buffer memory, and it is
 * expected that the supplied buffer will not be मुक्तd immediately. If the
 * package buffer needs to be मुक्तd, such as when पढ़ो from a file, use
 * ice_copy_and_init_pkg() instead of directly calling ice_init_pkg() in this
 * हाल.
 */
क्रमागत ice_status ice_init_pkg(काष्ठा ice_hw *hw, u8 *buf, u32 len)
अणु
	काष्ठा ice_pkg_hdr *pkg;
	क्रमागत ice_status status;
	काष्ठा ice_seg *seg;

	अगर (!buf || !len)
		वापस ICE_ERR_PARAM;

	pkg = (काष्ठा ice_pkg_hdr *)buf;
	status = ice_verअगरy_pkg(pkg, len);
	अगर (status) अणु
		ice_debug(hw, ICE_DBG_INIT, "failed to verify pkg (err: %d)\n",
			  status);
		वापस status;
	पूर्ण

	/* initialize package info */
	status = ice_init_pkg_info(hw, pkg);
	अगर (status)
		वापस status;

	/* beक्रमe करोwnloading the package, check package version क्रम
	 * compatibility with driver
	 */
	status = ice_chk_pkg_compat(hw, pkg, &seg);
	अगर (status)
		वापस status;

	/* initialize package hपूर्णांकs and then करोwnload package */
	ice_init_pkg_hपूर्णांकs(hw, seg);
	status = ice_करोwnload_pkg(hw, seg);
	अगर (status == ICE_ERR_AQ_NO_WORK) अणु
		ice_debug(hw, ICE_DBG_INIT, "package previously loaded - no work.\n");
		status = 0;
	पूर्ण

	/* Get inक्रमmation on the package currently loaded in HW, then make sure
	 * the driver is compatible with this version.
	 */
	अगर (!status) अणु
		status = ice_get_pkg_info(hw);
		अगर (!status)
			status = ice_chk_pkg_version(&hw->active_pkg_ver);
	पूर्ण

	अगर (!status) अणु
		hw->seg = seg;
		/* on successful package करोwnload update other required
		 * रेजिस्टरs to support the package and fill HW tables
		 * with package content.
		 */
		ice_init_pkg_regs(hw);
		ice_fill_blk_tbls(hw);
	पूर्ण अन्यथा अणु
		ice_debug(hw, ICE_DBG_INIT, "package load failed, %d\n",
			  status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_copy_and_init_pkg - initialize/करोwnload a copy of the package
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @buf: poपूर्णांकer to the package buffer
 * @len: size of the package buffer
 *
 * This function copies the package buffer, and then calls ice_init_pkg() to
 * initialize the copied package contents.
 *
 * The copying is necessary अगर the package buffer supplied is स्थिरant, or अगर
 * the memory may disappear लघुly after calling this function.
 *
 * If the package buffer resides in the data segment and can be modअगरied, the
 * caller is मुक्त to use ice_init_pkg() instead of ice_copy_and_init_pkg().
 *
 * However, अगर the package buffer needs to be copied first, such as when being
 * पढ़ो from a file, the caller should use ice_copy_and_init_pkg().
 *
 * This function will first copy the package buffer, beक्रमe calling
 * ice_init_pkg(). The caller is मुक्त to immediately destroy the original
 * package buffer, as the new copy will be managed by this function and
 * related routines.
 */
क्रमागत ice_status ice_copy_and_init_pkg(काष्ठा ice_hw *hw, स्थिर u8 *buf, u32 len)
अणु
	क्रमागत ice_status status;
	u8 *buf_copy;

	अगर (!buf || !len)
		वापस ICE_ERR_PARAM;

	buf_copy = devm_kmemdup(ice_hw_to_dev(hw), buf, len, GFP_KERNEL);

	status = ice_init_pkg(hw, buf_copy, len);
	अगर (status) अणु
		/* Free the copy, since we failed to initialize the package */
		devm_kमुक्त(ice_hw_to_dev(hw), buf_copy);
	पूर्ण अन्यथा अणु
		/* Track the copied pkg so we can मुक्त it later */
		hw->pkg_copy = buf_copy;
		hw->pkg_size = len;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_pkg_buf_alloc
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Allocates a package buffer and वापसs a poपूर्णांकer to the buffer header.
 * Note: all package contents must be in Little Endian क्रमm.
 */
अटल काष्ठा ice_buf_build *ice_pkg_buf_alloc(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_buf_build *bld;
	काष्ठा ice_buf_hdr *buf;

	bld = devm_kzalloc(ice_hw_to_dev(hw), माप(*bld), GFP_KERNEL);
	अगर (!bld)
		वापस शून्य;

	buf = (काष्ठा ice_buf_hdr *)bld;
	buf->data_end = cpu_to_le16(दुरत्व(काष्ठा ice_buf_hdr,
					     section_entry));
	वापस bld;
पूर्ण

/**
 * ice_pkg_buf_मुक्त
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @bld: poपूर्णांकer to pkg build (allocated by ice_pkg_buf_alloc())
 *
 * Frees a package buffer
 */
अटल व्योम ice_pkg_buf_मुक्त(काष्ठा ice_hw *hw, काष्ठा ice_buf_build *bld)
अणु
	devm_kमुक्त(ice_hw_to_dev(hw), bld);
पूर्ण

/**
 * ice_pkg_buf_reserve_section
 * @bld: poपूर्णांकer to pkg build (allocated by ice_pkg_buf_alloc())
 * @count: the number of sections to reserve
 *
 * Reserves one or more section table entries in a package buffer. This routine
 * can be called multiple बार as दीर्घ as they are made beक्रमe calling
 * ice_pkg_buf_alloc_section(). Once ice_pkg_buf_alloc_section()
 * is called once, the number of sections that can be allocated will not be able
 * to be increased; not using all reserved sections is fine, but this will
 * result in some wasted space in the buffer.
 * Note: all package contents must be in Little Endian क्रमm.
 */
अटल क्रमागत ice_status
ice_pkg_buf_reserve_section(काष्ठा ice_buf_build *bld, u16 count)
अणु
	काष्ठा ice_buf_hdr *buf;
	u16 section_count;
	u16 data_end;

	अगर (!bld)
		वापस ICE_ERR_PARAM;

	buf = (काष्ठा ice_buf_hdr *)&bld->buf;

	/* alपढ़ोy an active section, can't increase table size */
	section_count = le16_to_cpu(buf->section_count);
	अगर (section_count > 0)
		वापस ICE_ERR_CFG;

	अगर (bld->reserved_section_table_entries + count > ICE_MAX_S_COUNT)
		वापस ICE_ERR_CFG;
	bld->reserved_section_table_entries += count;

	data_end = le16_to_cpu(buf->data_end) +
		flex_array_size(buf, section_entry, count);
	buf->data_end = cpu_to_le16(data_end);

	वापस 0;
पूर्ण

/**
 * ice_pkg_buf_alloc_section
 * @bld: poपूर्णांकer to pkg build (allocated by ice_pkg_buf_alloc())
 * @type: the section type value
 * @size: the size of the section to reserve (in bytes)
 *
 * Reserves memory in the buffer क्रम a section's content and updates the
 * buffers' status accordingly. This routine वापसs a poपूर्णांकer to the first
 * byte of the section start within the buffer, which is used to fill in the
 * section contents.
 * Note: all package contents must be in Little Endian क्रमm.
 */
अटल व्योम *
ice_pkg_buf_alloc_section(काष्ठा ice_buf_build *bld, u32 type, u16 size)
अणु
	काष्ठा ice_buf_hdr *buf;
	u16 sect_count;
	u16 data_end;

	अगर (!bld || !type || !size)
		वापस शून्य;

	buf = (काष्ठा ice_buf_hdr *)&bld->buf;

	/* check क्रम enough space left in buffer */
	data_end = le16_to_cpu(buf->data_end);

	/* section start must align on 4 byte boundary */
	data_end = ALIGN(data_end, 4);

	अगर ((data_end + size) > ICE_MAX_S_DATA_END)
		वापस शून्य;

	/* check क्रम more available section table entries */
	sect_count = le16_to_cpu(buf->section_count);
	अगर (sect_count < bld->reserved_section_table_entries) अणु
		व्योम *section_ptr = ((u8 *)buf) + data_end;

		buf->section_entry[sect_count].offset = cpu_to_le16(data_end);
		buf->section_entry[sect_count].size = cpu_to_le16(size);
		buf->section_entry[sect_count].type = cpu_to_le32(type);

		data_end += size;
		buf->data_end = cpu_to_le16(data_end);

		buf->section_count = cpu_to_le16(sect_count + 1);
		वापस section_ptr;
	पूर्ण

	/* no मुक्त section table entries */
	वापस शून्य;
पूर्ण

/**
 * ice_pkg_buf_get_active_sections
 * @bld: poपूर्णांकer to pkg build (allocated by ice_pkg_buf_alloc())
 *
 * Returns the number of active sections. Beक्रमe using the package buffer
 * in an update package command, the caller should make sure that there is at
 * least one active section - otherwise, the buffer is not legal and should
 * not be used.
 * Note: all package contents must be in Little Endian क्रमm.
 */
अटल u16 ice_pkg_buf_get_active_sections(काष्ठा ice_buf_build *bld)
अणु
	काष्ठा ice_buf_hdr *buf;

	अगर (!bld)
		वापस 0;

	buf = (काष्ठा ice_buf_hdr *)&bld->buf;
	वापस le16_to_cpu(buf->section_count);
पूर्ण

/**
 * ice_pkg_buf
 * @bld: poपूर्णांकer to pkg build (allocated by ice_pkg_buf_alloc())
 *
 * Return a poपूर्णांकer to the buffer's header
 */
अटल काष्ठा ice_buf *ice_pkg_buf(काष्ठा ice_buf_build *bld)
अणु
	अगर (!bld)
		वापस शून्य;

	वापस &bld->buf;
पूर्ण

/**
 * ice_get_खोलो_tunnel_port - retrieve an खोलो tunnel port
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @port: वापसs खोलो port
 */
bool
ice_get_खोलो_tunnel_port(काष्ठा ice_hw *hw, u16 *port)
अणु
	bool res = false;
	u16 i;

	mutex_lock(&hw->tnl_lock);

	क्रम (i = 0; i < hw->tnl.count && i < ICE_TUNNEL_MAX_ENTRIES; i++)
		अगर (hw->tnl.tbl[i].valid && hw->tnl.tbl[i].port) अणु
			*port = hw->tnl.tbl[i].port;
			res = true;
			अवरोध;
		पूर्ण

	mutex_unlock(&hw->tnl_lock);

	वापस res;
पूर्ण

/**
 * ice_tunnel_idx_to_entry - convert linear index to the sparse one
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @type: type of tunnel
 * @idx: linear index
 *
 * Stack assumes we have 2 linear tables with indexes [0, count_valid),
 * but really the port table may be sprase, and types are mixed, so convert
 * the stack index पूर्णांकo the device index.
 */
अटल u16 ice_tunnel_idx_to_entry(काष्ठा ice_hw *hw, क्रमागत ice_tunnel_type type,
				   u16 idx)
अणु
	u16 i;

	क्रम (i = 0; i < hw->tnl.count && i < ICE_TUNNEL_MAX_ENTRIES; i++)
		अगर (hw->tnl.tbl[i].valid &&
		    hw->tnl.tbl[i].type == type &&
		    idx--)
			वापस i;

	WARN_ON_ONCE(1);
	वापस 0;
पूर्ण

/**
 * ice_create_tunnel
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @index: device table entry
 * @type: type of tunnel
 * @port: port of tunnel to create
 *
 * Create a tunnel by updating the parse graph in the parser. We करो that by
 * creating a package buffer with the tunnel info and issuing an update package
 * command.
 */
अटल क्रमागत ice_status
ice_create_tunnel(काष्ठा ice_hw *hw, u16 index,
		  क्रमागत ice_tunnel_type type, u16 port)
अणु
	काष्ठा ice_boost_tcam_section *sect_rx, *sect_tx;
	क्रमागत ice_status status = ICE_ERR_MAX_LIMIT;
	काष्ठा ice_buf_build *bld;

	mutex_lock(&hw->tnl_lock);

	bld = ice_pkg_buf_alloc(hw);
	अगर (!bld) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ ice_create_tunnel_end;
	पूर्ण

	/* allocate 2 sections, one क्रम Rx parser, one क्रम Tx parser */
	अगर (ice_pkg_buf_reserve_section(bld, 2))
		जाओ ice_create_tunnel_err;

	sect_rx = ice_pkg_buf_alloc_section(bld, ICE_SID_RXPARSER_BOOST_TCAM,
					    काष्ठा_size(sect_rx, tcam, 1));
	अगर (!sect_rx)
		जाओ ice_create_tunnel_err;
	sect_rx->count = cpu_to_le16(1);

	sect_tx = ice_pkg_buf_alloc_section(bld, ICE_SID_TXPARSER_BOOST_TCAM,
					    काष्ठा_size(sect_tx, tcam, 1));
	अगर (!sect_tx)
		जाओ ice_create_tunnel_err;
	sect_tx->count = cpu_to_le16(1);

	/* copy original boost entry to update package buffer */
	स_नकल(sect_rx->tcam, hw->tnl.tbl[index].boost_entry,
	       माप(*sect_rx->tcam));

	/* over-ग_लिखो the never-match dest port key bits with the encoded port
	 * bits
	 */
	ice_set_key((u8 *)&sect_rx->tcam[0].key, माप(sect_rx->tcam[0].key),
		    (u8 *)&port, शून्य, शून्य, शून्य,
		    (u16)दुरत्व(काष्ठा ice_boost_key_value, hv_dst_port_key),
		    माप(sect_rx->tcam[0].key.key.hv_dst_port_key));

	/* exact copy of entry to Tx section entry */
	स_नकल(sect_tx->tcam, sect_rx->tcam, माप(*sect_tx->tcam));

	status = ice_update_pkg(hw, ice_pkg_buf(bld), 1);
	अगर (!status)
		hw->tnl.tbl[index].port = port;

ice_create_tunnel_err:
	ice_pkg_buf_मुक्त(hw, bld);

ice_create_tunnel_end:
	mutex_unlock(&hw->tnl_lock);

	वापस status;
पूर्ण

/**
 * ice_destroy_tunnel
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @index: device table entry
 * @type: type of tunnel
 * @port: port of tunnel to destroy (ignored अगर the all parameter is true)
 *
 * Destroys a tunnel or all tunnels by creating an update package buffer
 * targeting the specअगरic updates requested and then perक्रमming an update
 * package.
 */
अटल क्रमागत ice_status
ice_destroy_tunnel(काष्ठा ice_hw *hw, u16 index, क्रमागत ice_tunnel_type type,
		   u16 port)
अणु
	काष्ठा ice_boost_tcam_section *sect_rx, *sect_tx;
	क्रमागत ice_status status = ICE_ERR_MAX_LIMIT;
	काष्ठा ice_buf_build *bld;

	mutex_lock(&hw->tnl_lock);

	अगर (WARN_ON(!hw->tnl.tbl[index].valid ||
		    hw->tnl.tbl[index].type != type ||
		    hw->tnl.tbl[index].port != port)) अणु
		status = ICE_ERR_OUT_OF_RANGE;
		जाओ ice_destroy_tunnel_end;
	पूर्ण

	bld = ice_pkg_buf_alloc(hw);
	अगर (!bld) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ ice_destroy_tunnel_end;
	पूर्ण

	/* allocate 2 sections, one क्रम Rx parser, one क्रम Tx parser */
	अगर (ice_pkg_buf_reserve_section(bld, 2))
		जाओ ice_destroy_tunnel_err;

	sect_rx = ice_pkg_buf_alloc_section(bld, ICE_SID_RXPARSER_BOOST_TCAM,
					    काष्ठा_size(sect_rx, tcam, 1));
	अगर (!sect_rx)
		जाओ ice_destroy_tunnel_err;
	sect_rx->count = cpu_to_le16(1);

	sect_tx = ice_pkg_buf_alloc_section(bld, ICE_SID_TXPARSER_BOOST_TCAM,
					    काष्ठा_size(sect_tx, tcam, 1));
	अगर (!sect_tx)
		जाओ ice_destroy_tunnel_err;
	sect_tx->count = cpu_to_le16(1);

	/* copy original boost entry to update package buffer, one copy to Rx
	 * section, another copy to the Tx section
	 */
	स_नकल(sect_rx->tcam, hw->tnl.tbl[index].boost_entry,
	       माप(*sect_rx->tcam));
	स_नकल(sect_tx->tcam, hw->tnl.tbl[index].boost_entry,
	       माप(*sect_tx->tcam));

	status = ice_update_pkg(hw, ice_pkg_buf(bld), 1);
	अगर (!status)
		hw->tnl.tbl[index].port = 0;

ice_destroy_tunnel_err:
	ice_pkg_buf_मुक्त(hw, bld);

ice_destroy_tunnel_end:
	mutex_unlock(&hw->tnl_lock);

	वापस status;
पूर्ण

पूर्णांक ice_udp_tunnel_set_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			    अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_tunnel_type tnl_type;
	क्रमागत ice_status status;
	u16 index;

	tnl_type = ti->type == UDP_TUNNEL_TYPE_VXLAN ? TNL_VXLAN : TNL_GENEVE;
	index = ice_tunnel_idx_to_entry(&pf->hw, idx, tnl_type);

	status = ice_create_tunnel(&pf->hw, index, tnl_type, ntohs(ti->port));
	अगर (status) अणु
		netdev_err(netdev, "Error adding UDP tunnel - %s\n",
			   ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	udp_tunnel_nic_set_port_priv(netdev, table, idx, index);
	वापस 0;
पूर्ण

पूर्णांक ice_udp_tunnel_unset_port(काष्ठा net_device *netdev, अचिन्हित पूर्णांक table,
			      अचिन्हित पूर्णांक idx, काष्ठा udp_tunnel_info *ti)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_pf *pf = vsi->back;
	क्रमागत ice_tunnel_type tnl_type;
	क्रमागत ice_status status;

	tnl_type = ti->type == UDP_TUNNEL_TYPE_VXLAN ? TNL_VXLAN : TNL_GENEVE;

	status = ice_destroy_tunnel(&pf->hw, ti->hw_priv, tnl_type,
				    ntohs(ti->port));
	अगर (status) अणु
		netdev_err(netdev, "Error removing UDP tunnel - %s\n",
			   ice_stat_str(status));
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* PTG Management */

/**
 * ice_ptg_find_ptype - Search क्रम packet type group using packet type (ptype)
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @ptype: the ptype to search क्रम
 * @ptg: poपूर्णांकer to variable that receives the PTG
 *
 * This function will search the PTGs क्रम a particular ptype, वापसing the
 * PTG ID that contains it through the PTG parameter, with the value of
 * ICE_DEFAULT_PTG (0) meaning it is part the शेष PTG.
 */
अटल क्रमागत ice_status
ice_ptg_find_ptype(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 ptype, u8 *ptg)
अणु
	अगर (ptype >= ICE_XLT1_CNT || !ptg)
		वापस ICE_ERR_PARAM;

	*ptg = hw->blk[blk].xlt1.ptypes[ptype].ptg;
	वापस 0;
पूर्ण

/**
 * ice_ptg_alloc_val - Allocates a new packet type group ID by value
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @ptg: the PTG to allocate
 *
 * This function allocates a given packet type group ID specअगरied by the PTG
 * parameter.
 */
अटल व्योम ice_ptg_alloc_val(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 ptg)
अणु
	hw->blk[blk].xlt1.ptg_tbl[ptg].in_use = true;
पूर्ण

/**
 * ice_ptg_हटाओ_ptype - Removes ptype from a particular packet type group
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @ptype: the ptype to हटाओ
 * @ptg: the PTG to हटाओ the ptype from
 *
 * This function will हटाओ the ptype from the specअगरic PTG, and move it to
 * the शेष PTG (ICE_DEFAULT_PTG).
 */
अटल क्रमागत ice_status
ice_ptg_हटाओ_ptype(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 ptype, u8 ptg)
अणु
	काष्ठा ice_ptg_ptype **ch;
	काष्ठा ice_ptg_ptype *p;

	अगर (ptype > ICE_XLT1_CNT - 1)
		वापस ICE_ERR_PARAM;

	अगर (!hw->blk[blk].xlt1.ptg_tbl[ptg].in_use)
		वापस ICE_ERR_DOES_NOT_EXIST;

	/* Should not happen अगर .in_use is set, bad config */
	अगर (!hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype)
		वापस ICE_ERR_CFG;

	/* find the ptype within this PTG, and bypass the link over it */
	p = hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	ch = &hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	जबतक (p) अणु
		अगर (ptype == (p - hw->blk[blk].xlt1.ptypes)) अणु
			*ch = p->next_ptype;
			अवरोध;
		पूर्ण

		ch = &p->next_ptype;
		p = p->next_ptype;
	पूर्ण

	hw->blk[blk].xlt1.ptypes[ptype].ptg = ICE_DEFAULT_PTG;
	hw->blk[blk].xlt1.ptypes[ptype].next_ptype = शून्य;

	वापस 0;
पूर्ण

/**
 * ice_ptg_add_mv_ptype - Adds/moves ptype to a particular packet type group
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @ptype: the ptype to add or move
 * @ptg: the PTG to add or move the ptype to
 *
 * This function will either add or move a ptype to a particular PTG depending
 * on अगर the ptype is alपढ़ोy part of another group. Note that using a
 * a destination PTG ID of ICE_DEFAULT_PTG (0) will move the ptype to the
 * शेष PTG.
 */
अटल क्रमागत ice_status
ice_ptg_add_mv_ptype(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 ptype, u8 ptg)
अणु
	क्रमागत ice_status status;
	u8 original_ptg;

	अगर (ptype > ICE_XLT1_CNT - 1)
		वापस ICE_ERR_PARAM;

	अगर (!hw->blk[blk].xlt1.ptg_tbl[ptg].in_use && ptg != ICE_DEFAULT_PTG)
		वापस ICE_ERR_DOES_NOT_EXIST;

	status = ice_ptg_find_ptype(hw, blk, ptype, &original_ptg);
	अगर (status)
		वापस status;

	/* Is ptype alपढ़ोy in the correct PTG? */
	अगर (original_ptg == ptg)
		वापस 0;

	/* Remove from original PTG and move back to the शेष PTG */
	अगर (original_ptg != ICE_DEFAULT_PTG)
		ice_ptg_हटाओ_ptype(hw, blk, ptype, original_ptg);

	/* Moving to शेष PTG? Then we're करोne with this request */
	अगर (ptg == ICE_DEFAULT_PTG)
		वापस 0;

	/* Add ptype to PTG at beginning of list */
	hw->blk[blk].xlt1.ptypes[ptype].next_ptype =
		hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype;
	hw->blk[blk].xlt1.ptg_tbl[ptg].first_ptype =
		&hw->blk[blk].xlt1.ptypes[ptype];

	hw->blk[blk].xlt1.ptypes[ptype].ptg = ptg;
	hw->blk[blk].xlt1.t[ptype] = ptg;

	वापस 0;
पूर्ण

/* Block / table size info */
काष्ठा ice_blk_size_details अणु
	u16 xlt1;			/* # XLT1 entries */
	u16 xlt2;			/* # XLT2 entries */
	u16 prof_tcam;			/* # profile ID TCAM entries */
	u16 prof_id;			/* # profile IDs */
	u8 prof_cdid_bits;		/* # CDID one-hot bits used in key */
	u16 prof_redir;			/* # profile redirection entries */
	u16 es;				/* # extraction sequence entries */
	u16 fvw;			/* # field vector words */
	u8 overग_लिखो;			/* overग_लिखो existing entries allowed */
	u8 reverse;			/* reverse FV order */
पूर्ण;

अटल स्थिर काष्ठा ice_blk_size_details blk_sizes[ICE_BLK_COUNT] = अणु
	/**
	 * Table Definitions
	 * XLT1 - Number of entries in XLT1 table
	 * XLT2 - Number of entries in XLT2 table
	 * TCAM - Number of entries Profile ID TCAM table
	 * CDID - Control Doमुख्य ID of the hardware block
	 * PRED - Number of entries in the Profile Redirection Table
	 * FV   - Number of entries in the Field Vector
	 * FVW  - Width (in WORDs) of the Field Vector
	 * OVR  - Overग_लिखो existing table entries
	 * REV  - Reverse FV
	 */
	/*          XLT1        , XLT2        ,TCAM, PID,CDID,PRED,   FV, FVW */
	/*          Overग_लिखो   , Reverse FV */
	/* SW  */ अणु ICE_XLT1_CNT, ICE_XLT2_CNT, 512, 256,   0,  256, 256,  48,
		    false, false पूर्ण,
	/* ACL */ अणु ICE_XLT1_CNT, ICE_XLT2_CNT, 512, 128,   0,  128, 128,  32,
		    false, false पूर्ण,
	/* FD  */ अणु ICE_XLT1_CNT, ICE_XLT2_CNT, 512, 128,   0,  128, 128,  24,
		    false, true  पूर्ण,
	/* RSS */ अणु ICE_XLT1_CNT, ICE_XLT2_CNT, 512, 128,   0,  128, 128,  24,
		    true,  true  पूर्ण,
	/* PE  */ अणु ICE_XLT1_CNT, ICE_XLT2_CNT,  64,  32,   0,   32,  32,  24,
		    false, false पूर्ण,
पूर्ण;

क्रमागत ice_sid_all अणु
	ICE_SID_XLT1_OFF = 0,
	ICE_SID_XLT2_OFF,
	ICE_SID_PR_OFF,
	ICE_SID_PR_REसूची_OFF,
	ICE_SID_ES_OFF,
	ICE_SID_OFF_COUNT,
पूर्ण;

/* Characteristic handling */

/**
 * ice_match_prop_lst - determine अगर properties of two lists match
 * @list1: first properties list
 * @list2: second properties list
 *
 * Count, cookies and the order must match in order to be considered equivalent.
 */
अटल bool
ice_match_prop_lst(काष्ठा list_head *list1, काष्ठा list_head *list2)
अणु
	काष्ठा ice_vsig_prof *पंचांगp1;
	काष्ठा ice_vsig_prof *पंचांगp2;
	u16 chk_count = 0;
	u16 count = 0;

	/* compare counts */
	list_क्रम_each_entry(पंचांगp1, list1, list)
		count++;
	list_क्रम_each_entry(पंचांगp2, list2, list)
		chk_count++;
	/* cppcheck-suppress knownConditionTrueFalse */
	अगर (!count || count != chk_count)
		वापस false;

	पंचांगp1 = list_first_entry(list1, काष्ठा ice_vsig_prof, list);
	पंचांगp2 = list_first_entry(list2, काष्ठा ice_vsig_prof, list);

	/* profile cookies must compare, and in the exact same order to take
	 * पूर्णांकo account priority
	 */
	जबतक (count--) अणु
		अगर (पंचांगp2->profile_cookie != पंचांगp1->profile_cookie)
			वापस false;

		पंचांगp1 = list_next_entry(पंचांगp1, list);
		पंचांगp2 = list_next_entry(पंचांगp2, list);
	पूर्ण

	वापस true;
पूर्ण

/* VSIG Management */

/**
 * ice_vsig_find_vsi - find a VSIG that contains a specअगरied VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsi: VSI of पूर्णांकerest
 * @vsig: poपूर्णांकer to receive the VSI group
 *
 * This function will lookup the VSI entry in the XLT2 list and वापस
 * the VSI group its associated with.
 */
अटल क्रमागत ice_status
ice_vsig_find_vsi(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u16 *vsig)
अणु
	अगर (!vsig || vsi >= ICE_MAX_VSI)
		वापस ICE_ERR_PARAM;

	/* As दीर्घ as there's a शेष or valid VSIG associated with the input
	 * VSI, the functions वापसs a success. Any handling of VSIG will be
	 * करोne by the following add, update or हटाओ functions.
	 */
	*vsig = hw->blk[blk].xlt2.vsis[vsi].vsig;

	वापस 0;
पूर्ण

/**
 * ice_vsig_alloc_val - allocate a new VSIG by value
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsig: the VSIG to allocate
 *
 * This function will allocate a given VSIG specअगरied by the VSIG parameter.
 */
अटल u16 ice_vsig_alloc_val(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M;

	अगर (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use) अणु
		INIT_LIST_HEAD(&hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst);
		hw->blk[blk].xlt2.vsig_tbl[idx].in_use = true;
	पूर्ण

	वापस ICE_VSIG_VALUE(idx, hw->pf_id);
पूर्ण

/**
 * ice_vsig_alloc - Finds a मुक्त entry and allocates a new VSIG
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 *
 * This function will iterate through the VSIG list and mark the first
 * unused entry क्रम the new VSIG entry as used and वापस that value.
 */
अटल u16 ice_vsig_alloc(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 i;

	क्रम (i = 1; i < ICE_MAX_VSIGS; i++)
		अगर (!hw->blk[blk].xlt2.vsig_tbl[i].in_use)
			वापस ice_vsig_alloc_val(hw, blk, i);

	वापस ICE_DEFAULT_VSIG;
पूर्ण

/**
 * ice_find_dup_props_vsig - find VSI group with a specअगरied set of properties
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @chs: अक्षरacteristic list
 * @vsig: वापसs the VSIG with the matching profiles, अगर found
 *
 * Each VSIG is associated with a अक्षरacteristic set; i.e. all VSIs under
 * a group have the same अक्षरacteristic set. To check अगर there exists a VSIG
 * which has the same अक्षरacteristics as the input अक्षरacteristics; this
 * function will iterate through the XLT2 list and वापस the VSIG that has a
 * matching configuration. In order to make sure that priorities are accounted
 * क्रम, the list must match exactly, including the order in which the
 * अक्षरacteristics are listed.
 */
अटल क्रमागत ice_status
ice_find_dup_props_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
			काष्ठा list_head *chs, u16 *vsig)
अणु
	काष्ठा ice_xlt2 *xlt2 = &hw->blk[blk].xlt2;
	u16 i;

	क्रम (i = 0; i < xlt2->count; i++)
		अगर (xlt2->vsig_tbl[i].in_use &&
		    ice_match_prop_lst(chs, &xlt2->vsig_tbl[i].prop_lst)) अणु
			*vsig = ICE_VSIG_VALUE(i, hw->pf_id);
			वापस 0;
		पूर्ण

	वापस ICE_ERR_DOES_NOT_EXIST;
पूर्ण

/**
 * ice_vsig_मुक्त - मुक्त VSI group
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsig: VSIG to हटाओ
 *
 * The function will हटाओ all VSIs associated with the input VSIG and move
 * them to the DEFAULT_VSIG and mark the VSIG available.
 */
अटल क्रमागत ice_status
ice_vsig_मुक्त(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig)
अणु
	काष्ठा ice_vsig_prof *dपंचांगp, *del;
	काष्ठा ice_vsig_vsi *vsi_cur;
	u16 idx;

	idx = vsig & ICE_VSIG_IDX_M;
	अगर (idx >= ICE_MAX_VSIGS)
		वापस ICE_ERR_PARAM;

	अगर (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use)
		वापस ICE_ERR_DOES_NOT_EXIST;

	hw->blk[blk].xlt2.vsig_tbl[idx].in_use = false;

	vsi_cur = hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	/* If the VSIG has at least 1 VSI then iterate through the
	 * list and हटाओ the VSIs beक्रमe deleting the group.
	 */
	अगर (vsi_cur) अणु
		/* हटाओ all vsis associated with this VSIG XLT2 entry */
		करो अणु
			काष्ठा ice_vsig_vsi *पंचांगp = vsi_cur->next_vsi;

			vsi_cur->vsig = ICE_DEFAULT_VSIG;
			vsi_cur->changed = 1;
			vsi_cur->next_vsi = शून्य;
			vsi_cur = पंचांगp;
		पूर्ण जबतक (vsi_cur);

		/* शून्य terminate head of VSI list */
		hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi = शून्य;
	पूर्ण

	/* मुक्त अक्षरacteristic list */
	list_क्रम_each_entry_safe(del, dपंचांगp,
				 &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
				 list) अणु
		list_del(&del->list);
		devm_kमुक्त(ice_hw_to_dev(hw), del);
	पूर्ण

	/* अगर VSIG अक्षरacteristic list was cleared क्रम reset
	 * re-initialize the list head
	 */
	INIT_LIST_HEAD(&hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst);

	वापस 0;
पूर्ण

/**
 * ice_vsig_हटाओ_vsi - हटाओ VSI from VSIG
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsi: VSI to हटाओ
 * @vsig: VSI group to हटाओ from
 *
 * The function will हटाओ the input VSI from its VSI group and move it
 * to the DEFAULT_VSIG.
 */
अटल क्रमागत ice_status
ice_vsig_हटाओ_vsi(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u16 vsig)
अणु
	काष्ठा ice_vsig_vsi **vsi_head, *vsi_cur, *vsi_tgt;
	u16 idx;

	idx = vsig & ICE_VSIG_IDX_M;

	अगर (vsi >= ICE_MAX_VSI || idx >= ICE_MAX_VSIGS)
		वापस ICE_ERR_PARAM;

	अगर (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use)
		वापस ICE_ERR_DOES_NOT_EXIST;

	/* entry alपढ़ोy in शेष VSIG, करोn't have to हटाओ */
	अगर (idx == ICE_DEFAULT_VSIG)
		वापस 0;

	vsi_head = &hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	अगर (!(*vsi_head))
		वापस ICE_ERR_CFG;

	vsi_tgt = &hw->blk[blk].xlt2.vsis[vsi];
	vsi_cur = (*vsi_head);

	/* iterate the VSI list, skip over the entry to be हटाओd */
	जबतक (vsi_cur) अणु
		अगर (vsi_tgt == vsi_cur) अणु
			(*vsi_head) = vsi_cur->next_vsi;
			अवरोध;
		पूर्ण
		vsi_head = &vsi_cur->next_vsi;
		vsi_cur = vsi_cur->next_vsi;
	पूर्ण

	/* verअगरy अगर VSI was हटाओd from group list */
	अगर (!vsi_cur)
		वापस ICE_ERR_DOES_NOT_EXIST;

	vsi_cur->vsig = ICE_DEFAULT_VSIG;
	vsi_cur->changed = 1;
	vsi_cur->next_vsi = शून्य;

	वापस 0;
पूर्ण

/**
 * ice_vsig_add_mv_vsi - add or move a VSI to a VSI group
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsi: VSI to move
 * @vsig: destination VSI group
 *
 * This function will move or add the input VSI to the target VSIG.
 * The function will find the original VSIG the VSI beदीर्घs to and
 * move the entry to the DEFAULT_VSIG, update the original VSIG and
 * then move entry to the new VSIG.
 */
अटल क्रमागत ice_status
ice_vsig_add_mv_vsi(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u16 vsig)
अणु
	काष्ठा ice_vsig_vsi *पंचांगp;
	क्रमागत ice_status status;
	u16 orig_vsig, idx;

	idx = vsig & ICE_VSIG_IDX_M;

	अगर (vsi >= ICE_MAX_VSI || idx >= ICE_MAX_VSIGS)
		वापस ICE_ERR_PARAM;

	/* अगर VSIG not in use and VSIG is not शेष type this VSIG
	 * करोesn't exist.
	 */
	अगर (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use &&
	    vsig != ICE_DEFAULT_VSIG)
		वापस ICE_ERR_DOES_NOT_EXIST;

	status = ice_vsig_find_vsi(hw, blk, vsi, &orig_vsig);
	अगर (status)
		वापस status;

	/* no update required अगर vsigs match */
	अगर (orig_vsig == vsig)
		वापस 0;

	अगर (orig_vsig != ICE_DEFAULT_VSIG) अणु
		/* हटाओ entry from orig_vsig and add to शेष VSIG */
		status = ice_vsig_हटाओ_vsi(hw, blk, vsi, orig_vsig);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (idx == ICE_DEFAULT_VSIG)
		वापस 0;

	/* Create VSI entry and add VSIG and prop_mask values */
	hw->blk[blk].xlt2.vsis[vsi].vsig = vsig;
	hw->blk[blk].xlt2.vsis[vsi].changed = 1;

	/* Add new entry to the head of the VSIG list */
	पंचांगp = hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi =
		&hw->blk[blk].xlt2.vsis[vsi];
	hw->blk[blk].xlt2.vsis[vsi].next_vsi = पंचांगp;
	hw->blk[blk].xlt2.t[vsi] = vsig;

	वापस 0;
पूर्ण

/**
 * ice_prof_has_mask_idx - determine अगर profile index masking is identical
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @prof: profile to check
 * @idx: profile index to check
 * @mask: mask to match
 */
अटल bool
ice_prof_has_mask_idx(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof, u16 idx,
		      u16 mask)
अणु
	bool expect_no_mask = false;
	bool found = false;
	bool match = false;
	u16 i;

	/* If mask is 0x0000 or 0xffff, then there is no masking */
	अगर (mask == 0 || mask == 0xffff)
		expect_no_mask = true;

	/* Scan the enabled masks on this profile, क्रम the specअगरied idx */
	क्रम (i = hw->blk[blk].masks.first; i < hw->blk[blk].masks.first +
	     hw->blk[blk].masks.count; i++)
		अगर (hw->blk[blk].es.mask_ena[prof] & BIT(i))
			अगर (hw->blk[blk].masks.masks[i].in_use &&
			    hw->blk[blk].masks.masks[i].idx == idx) अणु
				found = true;
				अगर (hw->blk[blk].masks.masks[i].mask == mask)
					match = true;
				अवरोध;
			पूर्ण

	अगर (expect_no_mask) अणु
		अगर (found)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (!match)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ice_prof_has_mask - determine अगर profile masking is identical
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @prof: profile to check
 * @masks: masks to match
 */
अटल bool
ice_prof_has_mask(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof, u16 *masks)
अणु
	u16 i;

	/* es->mask_ena[prof] will have the mask */
	क्रम (i = 0; i < hw->blk[blk].es.fvw; i++)
		अगर (!ice_prof_has_mask_idx(hw, blk, prof, i, masks[i]))
			वापस false;

	वापस true;
पूर्ण

/**
 * ice_find_prof_id_with_mask - find profile ID क्रम a given field vector
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @fv: field vector to search क्रम
 * @masks: masks क्रम FV
 * @prof_id: receives the profile ID
 */
अटल क्रमागत ice_status
ice_find_prof_id_with_mask(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
			   काष्ठा ice_fv_word *fv, u16 *masks, u8 *prof_id)
अणु
	काष्ठा ice_es *es = &hw->blk[blk].es;
	u8 i;

	/* For FD, we करोn't want to re-use a existed profile with the same
	 * field vector and mask. This will cause rule पूर्णांकerference.
	 */
	अगर (blk == ICE_BLK_FD)
		वापस ICE_ERR_DOES_NOT_EXIST;

	क्रम (i = 0; i < (u8)es->count; i++) अणु
		u16 off = i * es->fvw;

		अगर (स_भेद(&es->t[off], fv, es->fvw * माप(*fv)))
			जारी;

		/* check अगर masks settings are the same क्रम this profile */
		अगर (masks && !ice_prof_has_mask(hw, blk, i, masks))
			जारी;

		*prof_id = i;
		वापस 0;
	पूर्ण

	वापस ICE_ERR_DOES_NOT_EXIST;
पूर्ण

/**
 * ice_prof_id_rsrc_type - get profile ID resource type क्रम a block type
 * @blk: the block type
 * @rsrc_type: poपूर्णांकer to variable to receive the resource type
 */
अटल bool ice_prof_id_rsrc_type(क्रमागत ice_block blk, u16 *rsrc_type)
अणु
	चयन (blk) अणु
	हाल ICE_BLK_FD:
		*rsrc_type = ICE_AQC_RES_TYPE_FD_PROF_BLDR_PROFID;
		अवरोध;
	हाल ICE_BLK_RSS:
		*rsrc_type = ICE_AQC_RES_TYPE_HASH_PROF_BLDR_PROFID;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * ice_tcam_ent_rsrc_type - get TCAM entry resource type क्रम a block type
 * @blk: the block type
 * @rsrc_type: poपूर्णांकer to variable to receive the resource type
 */
अटल bool ice_tcam_ent_rsrc_type(क्रमागत ice_block blk, u16 *rsrc_type)
अणु
	चयन (blk) अणु
	हाल ICE_BLK_FD:
		*rsrc_type = ICE_AQC_RES_TYPE_FD_PROF_BLDR_TCAM;
		अवरोध;
	हाल ICE_BLK_RSS:
		*rsrc_type = ICE_AQC_RES_TYPE_HASH_PROF_BLDR_TCAM;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

/**
 * ice_alloc_tcam_ent - allocate hardware TCAM entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block to allocate the TCAM क्रम
 * @bपंचांग: true to allocate from bottom of table, false to allocate from top
 * @tcam_idx: poपूर्णांकer to variable to receive the TCAM entry
 *
 * This function allocates a new entry in a Profile ID TCAM क्रम a specअगरic
 * block.
 */
अटल क्रमागत ice_status
ice_alloc_tcam_ent(काष्ठा ice_hw *hw, क्रमागत ice_block blk, bool bपंचांग,
		   u16 *tcam_idx)
अणु
	u16 res_type;

	अगर (!ice_tcam_ent_rsrc_type(blk, &res_type))
		वापस ICE_ERR_PARAM;

	वापस ice_alloc_hw_res(hw, res_type, 1, bपंचांग, tcam_idx);
पूर्ण

/**
 * ice_मुक्त_tcam_ent - मुक्त hardware TCAM entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block from which to मुक्त the TCAM entry
 * @tcam_idx: the TCAM entry to मुक्त
 *
 * This function मुक्तs an entry in a Profile ID TCAM क्रम a specअगरic block.
 */
अटल क्रमागत ice_status
ice_मुक्त_tcam_ent(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 tcam_idx)
अणु
	u16 res_type;

	अगर (!ice_tcam_ent_rsrc_type(blk, &res_type))
		वापस ICE_ERR_PARAM;

	वापस ice_मुक्त_hw_res(hw, res_type, 1, &tcam_idx);
पूर्ण

/**
 * ice_alloc_prof_id - allocate profile ID
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block to allocate the profile ID क्रम
 * @prof_id: poपूर्णांकer to variable to receive the profile ID
 *
 * This function allocates a new profile ID, which also corresponds to a Field
 * Vector (Extraction Sequence) entry.
 */
अटल क्रमागत ice_status
ice_alloc_prof_id(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 *prof_id)
अणु
	क्रमागत ice_status status;
	u16 res_type;
	u16 get_prof;

	अगर (!ice_prof_id_rsrc_type(blk, &res_type))
		वापस ICE_ERR_PARAM;

	status = ice_alloc_hw_res(hw, res_type, 1, false, &get_prof);
	अगर (!status)
		*prof_id = (u8)get_prof;

	वापस status;
पूर्ण

/**
 * ice_मुक्त_prof_id - मुक्त profile ID
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block from which to मुक्त the profile ID
 * @prof_id: the profile ID to मुक्त
 *
 * This function मुक्तs a profile ID, which also corresponds to a Field Vector.
 */
अटल क्रमागत ice_status
ice_मुक्त_prof_id(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof_id)
अणु
	u16 पंचांगp_prof_id = (u16)prof_id;
	u16 res_type;

	अगर (!ice_prof_id_rsrc_type(blk, &res_type))
		वापस ICE_ERR_PARAM;

	वापस ice_मुक्त_hw_res(hw, res_type, 1, &पंचांगp_prof_id);
पूर्ण

/**
 * ice_prof_inc_ref - increment reference count क्रम profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block from which to मुक्त the profile ID
 * @prof_id: the profile ID क्रम which to increment the reference count
 */
अटल क्रमागत ice_status
ice_prof_inc_ref(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof_id)
अणु
	अगर (prof_id > hw->blk[blk].es.count)
		वापस ICE_ERR_PARAM;

	hw->blk[blk].es.ref_count[prof_id]++;

	वापस 0;
पूर्ण

/**
 * ice_ग_लिखो_prof_mask_reg - ग_लिखो profile mask रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @mask_idx: mask index
 * @idx: index of the FV which will use the mask
 * @mask: the 16-bit mask
 */
अटल व्योम
ice_ग_लिखो_prof_mask_reg(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 mask_idx,
			u16 idx, u16 mask)
अणु
	u32 offset;
	u32 val;

	चयन (blk) अणु
	हाल ICE_BLK_RSS:
		offset = GLQF_HMASK(mask_idx);
		val = (idx << GLQF_HMASK_MSK_INDEX_S) & GLQF_HMASK_MSK_INDEX_M;
		val |= (mask << GLQF_HMASK_MASK_S) & GLQF_HMASK_MASK_M;
		अवरोध;
	हाल ICE_BLK_FD:
		offset = GLQF_FDMASK(mask_idx);
		val = (idx << GLQF_FDMASK_MSK_INDEX_S) & GLQF_FDMASK_MSK_INDEX_M;
		val |= (mask << GLQF_FDMASK_MASK_S) & GLQF_FDMASK_MASK_M;
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_PKG, "No profile masks for block %d\n",
			  blk);
		वापस;
	पूर्ण

	wr32(hw, offset, val);
	ice_debug(hw, ICE_DBG_PKG, "write mask, blk %d (%d): %x = %x\n",
		  blk, idx, offset, val);
पूर्ण

/**
 * ice_ग_लिखो_prof_mask_enable_res - ग_लिखो profile mask enable रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @prof_id: profile ID
 * @enable_mask: enable mask
 */
अटल व्योम
ice_ग_लिखो_prof_mask_enable_res(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
			       u16 prof_id, u32 enable_mask)
अणु
	u32 offset;

	चयन (blk) अणु
	हाल ICE_BLK_RSS:
		offset = GLQF_HMASK_SEL(prof_id);
		अवरोध;
	हाल ICE_BLK_FD:
		offset = GLQF_FDMASK_SEL(prof_id);
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_PKG, "No profile masks for block %d\n",
			  blk);
		वापस;
	पूर्ण

	wr32(hw, offset, enable_mask);
	ice_debug(hw, ICE_DBG_PKG, "write mask enable, blk %d (%d): %x = %x\n",
		  blk, prof_id, offset, enable_mask);
पूर्ण

/**
 * ice_init_prof_masks - initial prof masks
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 */
अटल व्योम ice_init_prof_masks(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 per_pf;
	u16 i;

	mutex_init(&hw->blk[blk].masks.lock);

	per_pf = ICE_PROF_MASK_COUNT / hw->dev_caps.num_funcs;

	hw->blk[blk].masks.count = per_pf;
	hw->blk[blk].masks.first = hw->pf_id * per_pf;

	स_रखो(hw->blk[blk].masks.masks, 0, माप(hw->blk[blk].masks.masks));

	क्रम (i = hw->blk[blk].masks.first;
	     i < hw->blk[blk].masks.first + hw->blk[blk].masks.count; i++)
		ice_ग_लिखो_prof_mask_reg(hw, blk, i, 0, 0);
पूर्ण

/**
 * ice_init_all_prof_masks - initialize all prof masks
 * @hw: poपूर्णांकer to the HW काष्ठा
 */
अटल व्योम ice_init_all_prof_masks(काष्ठा ice_hw *hw)
अणु
	ice_init_prof_masks(hw, ICE_BLK_RSS);
	ice_init_prof_masks(hw, ICE_BLK_FD);
पूर्ण

/**
 * ice_alloc_prof_mask - allocate profile mask
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @idx: index of FV which will use the mask
 * @mask: the 16-bit mask
 * @mask_idx: variable to receive the mask index
 */
अटल क्रमागत ice_status
ice_alloc_prof_mask(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 idx, u16 mask,
		    u16 *mask_idx)
अणु
	bool found_unused = false, found_copy = false;
	क्रमागत ice_status status = ICE_ERR_MAX_LIMIT;
	u16 unused_idx = 0, copy_idx = 0;
	u16 i;

	अगर (blk != ICE_BLK_RSS && blk != ICE_BLK_FD)
		वापस ICE_ERR_PARAM;

	mutex_lock(&hw->blk[blk].masks.lock);

	क्रम (i = hw->blk[blk].masks.first;
	     i < hw->blk[blk].masks.first + hw->blk[blk].masks.count; i++)
		अगर (hw->blk[blk].masks.masks[i].in_use) अणु
			/* अगर mask is in use and it exactly duplicates the
			 * desired mask and index, then in can be reused
			 */
			अगर (hw->blk[blk].masks.masks[i].mask == mask &&
			    hw->blk[blk].masks.masks[i].idx == idx) अणु
				found_copy = true;
				copy_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* save off unused index, but keep searching in हाल
			 * there is an exact match later on
			 */
			अगर (!found_unused) अणु
				found_unused = true;
				unused_idx = i;
			पूर्ण
		पूर्ण

	अगर (found_copy)
		i = copy_idx;
	अन्यथा अगर (found_unused)
		i = unused_idx;
	अन्यथा
		जाओ err_ice_alloc_prof_mask;

	/* update mask क्रम a new entry */
	अगर (found_unused) अणु
		hw->blk[blk].masks.masks[i].in_use = true;
		hw->blk[blk].masks.masks[i].mask = mask;
		hw->blk[blk].masks.masks[i].idx = idx;
		hw->blk[blk].masks.masks[i].ref = 0;
		ice_ग_लिखो_prof_mask_reg(hw, blk, i, idx, mask);
	पूर्ण

	hw->blk[blk].masks.masks[i].ref++;
	*mask_idx = i;
	status = 0;

err_ice_alloc_prof_mask:
	mutex_unlock(&hw->blk[blk].masks.lock);

	वापस status;
पूर्ण

/**
 * ice_मुक्त_prof_mask - मुक्त profile mask
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @mask_idx: index of mask
 */
अटल क्रमागत ice_status
ice_मुक्त_prof_mask(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 mask_idx)
अणु
	अगर (blk != ICE_BLK_RSS && blk != ICE_BLK_FD)
		वापस ICE_ERR_PARAM;

	अगर (!(mask_idx >= hw->blk[blk].masks.first &&
	      mask_idx < hw->blk[blk].masks.first + hw->blk[blk].masks.count))
		वापस ICE_ERR_DOES_NOT_EXIST;

	mutex_lock(&hw->blk[blk].masks.lock);

	अगर (!hw->blk[blk].masks.masks[mask_idx].in_use)
		जाओ निकास_ice_मुक्त_prof_mask;

	अगर (hw->blk[blk].masks.masks[mask_idx].ref > 1) अणु
		hw->blk[blk].masks.masks[mask_idx].ref--;
		जाओ निकास_ice_मुक्त_prof_mask;
	पूर्ण

	/* हटाओ mask */
	hw->blk[blk].masks.masks[mask_idx].in_use = false;
	hw->blk[blk].masks.masks[mask_idx].mask = 0;
	hw->blk[blk].masks.masks[mask_idx].idx = 0;

	/* update mask as unused entry */
	ice_debug(hw, ICE_DBG_PKG, "Free mask, blk %d, mask %d\n", blk,
		  mask_idx);
	ice_ग_लिखो_prof_mask_reg(hw, blk, mask_idx, 0, 0);

निकास_ice_मुक्त_prof_mask:
	mutex_unlock(&hw->blk[blk].masks.lock);

	वापस 0;
पूर्ण

/**
 * ice_मुक्त_prof_masks - मुक्त all profile masks क्रम a profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @prof_id: profile ID
 */
अटल क्रमागत ice_status
ice_मुक्त_prof_masks(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 prof_id)
अणु
	u32 mask_bm;
	u16 i;

	अगर (blk != ICE_BLK_RSS && blk != ICE_BLK_FD)
		वापस ICE_ERR_PARAM;

	mask_bm = hw->blk[blk].es.mask_ena[prof_id];
	क्रम (i = 0; i < BITS_PER_BYTE * माप(mask_bm); i++)
		अगर (mask_bm & BIT(i))
			ice_मुक्त_prof_mask(hw, blk, i);

	वापस 0;
पूर्ण

/**
 * ice_shutकरोwn_prof_masks - releases lock क्रम masking
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 *
 * This should be called beक्रमe unloading the driver
 */
अटल व्योम ice_shutकरोwn_prof_masks(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 i;

	mutex_lock(&hw->blk[blk].masks.lock);

	क्रम (i = hw->blk[blk].masks.first;
	     i < hw->blk[blk].masks.first + hw->blk[blk].masks.count; i++) अणु
		ice_ग_लिखो_prof_mask_reg(hw, blk, i, 0, 0);

		hw->blk[blk].masks.masks[i].in_use = false;
		hw->blk[blk].masks.masks[i].idx = 0;
		hw->blk[blk].masks.masks[i].mask = 0;
	पूर्ण

	mutex_unlock(&hw->blk[blk].masks.lock);
	mutex_destroy(&hw->blk[blk].masks.lock);
पूर्ण

/**
 * ice_shutकरोwn_all_prof_masks - releases all locks क्रम masking
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This should be called beक्रमe unloading the driver
 */
अटल व्योम ice_shutकरोwn_all_prof_masks(काष्ठा ice_hw *hw)
अणु
	ice_shutकरोwn_prof_masks(hw, ICE_BLK_RSS);
	ice_shutकरोwn_prof_masks(hw, ICE_BLK_FD);
पूर्ण

/**
 * ice_update_prof_masking - set रेजिस्टरs according to masking
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @prof_id: profile ID
 * @masks: masks
 */
अटल क्रमागत ice_status
ice_update_prof_masking(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 prof_id,
			u16 *masks)
अणु
	bool err = false;
	u32 ena_mask = 0;
	u16 idx;
	u16 i;

	/* Only support FD and RSS masking, otherwise nothing to be करोne */
	अगर (blk != ICE_BLK_RSS && blk != ICE_BLK_FD)
		वापस 0;

	क्रम (i = 0; i < hw->blk[blk].es.fvw; i++)
		अगर (masks[i] && masks[i] != 0xFFFF) अणु
			अगर (!ice_alloc_prof_mask(hw, blk, i, masks[i], &idx)) अणु
				ena_mask |= BIT(idx);
			पूर्ण अन्यथा अणु
				/* not enough biपंचांगaps */
				err = true;
				अवरोध;
			पूर्ण
		पूर्ण

	अगर (err) अणु
		/* मुक्त any biपंचांगaps we have allocated */
		क्रम (i = 0; i < BITS_PER_BYTE * माप(ena_mask); i++)
			अगर (ena_mask & BIT(i))
				ice_मुक्त_prof_mask(hw, blk, i);

		वापस ICE_ERR_OUT_OF_RANGE;
	पूर्ण

	/* enable the masks क्रम this profile */
	ice_ग_लिखो_prof_mask_enable_res(hw, blk, prof_id, ena_mask);

	/* store enabled masks with profile so that they can be मुक्तd later */
	hw->blk[blk].es.mask_ena[prof_id] = ena_mask;

	वापस 0;
पूर्ण

/**
 * ice_ग_लिखो_es - ग_लिखो an extraction sequence to hardware
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block in which to ग_लिखो the extraction sequence
 * @prof_id: the profile ID to ग_लिखो
 * @fv: poपूर्णांकer to the extraction sequence to ग_लिखो - शून्य to clear extraction
 */
अटल व्योम
ice_ग_लिखो_es(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof_id,
	     काष्ठा ice_fv_word *fv)
अणु
	u16 off;

	off = prof_id * hw->blk[blk].es.fvw;
	अगर (!fv) अणु
		स_रखो(&hw->blk[blk].es.t[off], 0,
		       hw->blk[blk].es.fvw * माप(*fv));
		hw->blk[blk].es.written[prof_id] = false;
	पूर्ण अन्यथा अणु
		स_नकल(&hw->blk[blk].es.t[off], fv,
		       hw->blk[blk].es.fvw * माप(*fv));
	पूर्ण
पूर्ण

/**
 * ice_prof_dec_ref - decrement reference count क्रम profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block from which to मुक्त the profile ID
 * @prof_id: the profile ID क्रम which to decrement the reference count
 */
अटल क्रमागत ice_status
ice_prof_dec_ref(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 prof_id)
अणु
	अगर (prof_id > hw->blk[blk].es.count)
		वापस ICE_ERR_PARAM;

	अगर (hw->blk[blk].es.ref_count[prof_id] > 0) अणु
		अगर (!--hw->blk[blk].es.ref_count[prof_id]) अणु
			ice_ग_लिखो_es(hw, blk, prof_id, शून्य);
			ice_मुक्त_prof_masks(hw, blk, prof_id);
			वापस ice_मुक्त_prof_id(hw, blk, prof_id);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Block / table section IDs */
अटल स्थिर u32 ice_blk_sids[ICE_BLK_COUNT][ICE_SID_OFF_COUNT] = अणु
	/* SWITCH */
	अणु	ICE_SID_XLT1_SW,
		ICE_SID_XLT2_SW,
		ICE_SID_PROFID_TCAM_SW,
		ICE_SID_PROFID_REसूची_SW,
		ICE_SID_FLD_VEC_SW
	पूर्ण,

	/* ACL */
	अणु	ICE_SID_XLT1_ACL,
		ICE_SID_XLT2_ACL,
		ICE_SID_PROFID_TCAM_ACL,
		ICE_SID_PROFID_REसूची_ACL,
		ICE_SID_FLD_VEC_ACL
	पूर्ण,

	/* FD */
	अणु	ICE_SID_XLT1_FD,
		ICE_SID_XLT2_FD,
		ICE_SID_PROFID_TCAM_FD,
		ICE_SID_PROFID_REसूची_FD,
		ICE_SID_FLD_VEC_FD
	पूर्ण,

	/* RSS */
	अणु	ICE_SID_XLT1_RSS,
		ICE_SID_XLT2_RSS,
		ICE_SID_PROFID_TCAM_RSS,
		ICE_SID_PROFID_REसूची_RSS,
		ICE_SID_FLD_VEC_RSS
	पूर्ण,

	/* PE */
	अणु	ICE_SID_XLT1_PE,
		ICE_SID_XLT2_PE,
		ICE_SID_PROFID_TCAM_PE,
		ICE_SID_PROFID_REसूची_PE,
		ICE_SID_FLD_VEC_PE
	पूर्ण
पूर्ण;

/**
 * ice_init_sw_xlt1_db - init software XLT1 database from HW tables
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: the HW block to initialize
 */
अटल व्योम ice_init_sw_xlt1_db(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 pt;

	क्रम (pt = 0; pt < hw->blk[blk].xlt1.count; pt++) अणु
		u8 ptg;

		ptg = hw->blk[blk].xlt1.t[pt];
		अगर (ptg != ICE_DEFAULT_PTG) अणु
			ice_ptg_alloc_val(hw, blk, ptg);
			ice_ptg_add_mv_ptype(hw, blk, pt, ptg);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_init_sw_xlt2_db - init software XLT2 database from HW tables
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: the HW block to initialize
 */
अटल व्योम ice_init_sw_xlt2_db(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 vsi;

	क्रम (vsi = 0; vsi < hw->blk[blk].xlt2.count; vsi++) अणु
		u16 vsig;

		vsig = hw->blk[blk].xlt2.t[vsi];
		अगर (vsig) अणु
			ice_vsig_alloc_val(hw, blk, vsig);
			ice_vsig_add_mv_vsi(hw, blk, vsi, vsig);
			/* no changes at this समय, since this has been
			 * initialized from the original package
			 */
			hw->blk[blk].xlt2.vsis[vsi].changed = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_init_sw_db - init software database from HW tables
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
अटल व्योम ice_init_sw_db(काष्ठा ice_hw *hw)
अणु
	u16 i;

	क्रम (i = 0; i < ICE_BLK_COUNT; i++) अणु
		ice_init_sw_xlt1_db(hw, (क्रमागत ice_block)i);
		ice_init_sw_xlt2_db(hw, (क्रमागत ice_block)i);
	पूर्ण
पूर्ण

/**
 * ice_fill_tbl - Reads content of a single table type पूर्णांकo database
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @block_id: Block ID of the table to copy
 * @sid: Section ID of the table to copy
 *
 * Will attempt to पढ़ो the entire content of a given table of a single block
 * पूर्णांकo the driver database. We assume that the buffer will always
 * be as large or larger than the data contained in the package. If
 * this condition is not met, there is most likely an error in the package
 * contents.
 */
अटल व्योम ice_fill_tbl(काष्ठा ice_hw *hw, क्रमागत ice_block block_id, u32 sid)
अणु
	u32 dst_len, sect_len, offset = 0;
	काष्ठा ice_prof_redir_section *pr;
	काष्ठा ice_prof_id_section *pid;
	काष्ठा ice_xlt1_section *xlt1;
	काष्ठा ice_xlt2_section *xlt2;
	काष्ठा ice_sw_fv_section *es;
	काष्ठा ice_pkg_क्रमागत state;
	u8 *src, *dst;
	व्योम *sect;

	/* अगर the HW segment poपूर्णांकer is null then the first iteration of
	 * ice_pkg_क्रमागत_section() will fail. In this हाल the HW tables will
	 * not be filled and वापस success.
	 */
	अगर (!hw->seg) अणु
		ice_debug(hw, ICE_DBG_PKG, "hw->seg is NULL, tables are not filled\n");
		वापस;
	पूर्ण

	स_रखो(&state, 0, माप(state));

	sect = ice_pkg_क्रमागत_section(hw->seg, &state, sid);

	जबतक (sect) अणु
		चयन (sid) अणु
		हाल ICE_SID_XLT1_SW:
		हाल ICE_SID_XLT1_FD:
		हाल ICE_SID_XLT1_RSS:
		हाल ICE_SID_XLT1_ACL:
		हाल ICE_SID_XLT1_PE:
			xlt1 = sect;
			src = xlt1->value;
			sect_len = le16_to_cpu(xlt1->count) *
				माप(*hw->blk[block_id].xlt1.t);
			dst = hw->blk[block_id].xlt1.t;
			dst_len = hw->blk[block_id].xlt1.count *
				माप(*hw->blk[block_id].xlt1.t);
			अवरोध;
		हाल ICE_SID_XLT2_SW:
		हाल ICE_SID_XLT2_FD:
		हाल ICE_SID_XLT2_RSS:
		हाल ICE_SID_XLT2_ACL:
		हाल ICE_SID_XLT2_PE:
			xlt2 = sect;
			src = (__क्रमce u8 *)xlt2->value;
			sect_len = le16_to_cpu(xlt2->count) *
				माप(*hw->blk[block_id].xlt2.t);
			dst = (u8 *)hw->blk[block_id].xlt2.t;
			dst_len = hw->blk[block_id].xlt2.count *
				माप(*hw->blk[block_id].xlt2.t);
			अवरोध;
		हाल ICE_SID_PROFID_TCAM_SW:
		हाल ICE_SID_PROFID_TCAM_FD:
		हाल ICE_SID_PROFID_TCAM_RSS:
		हाल ICE_SID_PROFID_TCAM_ACL:
		हाल ICE_SID_PROFID_TCAM_PE:
			pid = sect;
			src = (u8 *)pid->entry;
			sect_len = le16_to_cpu(pid->count) *
				माप(*hw->blk[block_id].prof.t);
			dst = (u8 *)hw->blk[block_id].prof.t;
			dst_len = hw->blk[block_id].prof.count *
				माप(*hw->blk[block_id].prof.t);
			अवरोध;
		हाल ICE_SID_PROFID_REसूची_SW:
		हाल ICE_SID_PROFID_REसूची_FD:
		हाल ICE_SID_PROFID_REसूची_RSS:
		हाल ICE_SID_PROFID_REसूची_ACL:
		हाल ICE_SID_PROFID_REसूची_PE:
			pr = sect;
			src = pr->redir_value;
			sect_len = le16_to_cpu(pr->count) *
				माप(*hw->blk[block_id].prof_redir.t);
			dst = hw->blk[block_id].prof_redir.t;
			dst_len = hw->blk[block_id].prof_redir.count *
				माप(*hw->blk[block_id].prof_redir.t);
			अवरोध;
		हाल ICE_SID_FLD_VEC_SW:
		हाल ICE_SID_FLD_VEC_FD:
		हाल ICE_SID_FLD_VEC_RSS:
		हाल ICE_SID_FLD_VEC_ACL:
		हाल ICE_SID_FLD_VEC_PE:
			es = sect;
			src = (u8 *)es->fv;
			sect_len = (u32)(le16_to_cpu(es->count) *
					 hw->blk[block_id].es.fvw) *
				माप(*hw->blk[block_id].es.t);
			dst = (u8 *)hw->blk[block_id].es.t;
			dst_len = (u32)(hw->blk[block_id].es.count *
					hw->blk[block_id].es.fvw) *
				माप(*hw->blk[block_id].es.t);
			अवरोध;
		शेष:
			वापस;
		पूर्ण

		/* अगर the section offset exceeds destination length, terminate
		 * table fill.
		 */
		अगर (offset > dst_len)
			वापस;

		/* अगर the sum of section size and offset exceed destination size
		 * then we are out of bounds of the HW table size क्रम that PF.
		 * Changing section length to fill the reमुख्यing table space
		 * of that PF.
		 */
		अगर ((offset + sect_len) > dst_len)
			sect_len = dst_len - offset;

		स_नकल(dst + offset, src, sect_len);
		offset += sect_len;
		sect = ice_pkg_क्रमागत_section(शून्य, &state, sid);
	पूर्ण
पूर्ण

/**
 * ice_fill_blk_tbls - Read package context क्रम tables
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * Reads the current package contents and populates the driver
 * database with the data iteratively क्रम all advanced feature
 * blocks. Assume that the HW tables have been allocated.
 */
व्योम ice_fill_blk_tbls(काष्ठा ice_hw *hw)
अणु
	u8 i;

	क्रम (i = 0; i < ICE_BLK_COUNT; i++) अणु
		क्रमागत ice_block blk_id = (क्रमागत ice_block)i;

		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].xlt1.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].xlt2.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].prof.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].prof_redir.sid);
		ice_fill_tbl(hw, blk_id, hw->blk[blk_id].es.sid);
	पूर्ण

	ice_init_sw_db(hw);
पूर्ण

/**
 * ice_मुक्त_prof_map - मुक्त profile map
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk_idx: HW block index
 */
अटल व्योम ice_मुक्त_prof_map(काष्ठा ice_hw *hw, u8 blk_idx)
अणु
	काष्ठा ice_es *es = &hw->blk[blk_idx].es;
	काष्ठा ice_prof_map *del, *पंचांगp;

	mutex_lock(&es->prof_map_lock);
	list_क्रम_each_entry_safe(del, पंचांगp, &es->prof_map, list) अणु
		list_del(&del->list);
		devm_kमुक्त(ice_hw_to_dev(hw), del);
	पूर्ण
	INIT_LIST_HEAD(&es->prof_map);
	mutex_unlock(&es->prof_map_lock);
पूर्ण

/**
 * ice_मुक्त_flow_profs - मुक्त flow profile entries
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk_idx: HW block index
 */
अटल व्योम ice_मुक्त_flow_profs(काष्ठा ice_hw *hw, u8 blk_idx)
अणु
	काष्ठा ice_flow_prof *p, *पंचांगp;

	mutex_lock(&hw->fl_profs_locks[blk_idx]);
	list_क्रम_each_entry_safe(p, पंचांगp, &hw->fl_profs[blk_idx], l_entry) अणु
		काष्ठा ice_flow_entry *e, *t;

		list_क्रम_each_entry_safe(e, t, &p->entries, l_entry)
			ice_flow_rem_entry(hw, (क्रमागत ice_block)blk_idx,
					   ICE_FLOW_ENTRY_HNDL(e));

		list_del(&p->l_entry);

		mutex_destroy(&p->entries_lock);
		devm_kमुक्त(ice_hw_to_dev(hw), p);
	पूर्ण
	mutex_unlock(&hw->fl_profs_locks[blk_idx]);

	/* अगर driver is in reset and tables are being cleared
	 * re-initialize the flow profile list heads
	 */
	INIT_LIST_HEAD(&hw->fl_profs[blk_idx]);
पूर्ण

/**
 * ice_मुक्त_vsig_tbl - मुक्त complete VSIG table entries
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: the HW block on which to मुक्त the VSIG table entries
 */
अटल व्योम ice_मुक्त_vsig_tbl(काष्ठा ice_hw *hw, क्रमागत ice_block blk)
अणु
	u16 i;

	अगर (!hw->blk[blk].xlt2.vsig_tbl)
		वापस;

	क्रम (i = 1; i < ICE_MAX_VSIGS; i++)
		अगर (hw->blk[blk].xlt2.vsig_tbl[i].in_use)
			ice_vsig_मुक्त(hw, blk, i);
पूर्ण

/**
 * ice_मुक्त_hw_tbls - मुक्त hardware table memory
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
व्योम ice_मुक्त_hw_tbls(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_rss_cfg *r, *rt;
	u8 i;

	क्रम (i = 0; i < ICE_BLK_COUNT; i++) अणु
		अगर (hw->blk[i].is_list_init) अणु
			काष्ठा ice_es *es = &hw->blk[i].es;

			ice_मुक्त_prof_map(hw, i);
			mutex_destroy(&es->prof_map_lock);

			ice_मुक्त_flow_profs(hw, i);
			mutex_destroy(&hw->fl_profs_locks[i]);

			hw->blk[i].is_list_init = false;
		पूर्ण
		ice_मुक्त_vsig_tbl(hw, (क्रमागत ice_block)i);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt1.ptypes);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt1.ptg_tbl);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt1.t);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt2.t);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt2.vsig_tbl);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].xlt2.vsis);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].prof.t);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].prof_redir.t);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].es.t);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].es.ref_count);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].es.written);
		devm_kमुक्त(ice_hw_to_dev(hw), hw->blk[i].es.mask_ena);
	पूर्ण

	list_क्रम_each_entry_safe(r, rt, &hw->rss_list_head, l_entry) अणु
		list_del(&r->l_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), r);
	पूर्ण
	mutex_destroy(&hw->rss_locks);
	ice_shutकरोwn_all_prof_masks(hw);
	स_रखो(hw->blk, 0, माप(hw->blk));
पूर्ण

/**
 * ice_init_flow_profs - init flow profile locks and list heads
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk_idx: HW block index
 */
अटल व्योम ice_init_flow_profs(काष्ठा ice_hw *hw, u8 blk_idx)
अणु
	mutex_init(&hw->fl_profs_locks[blk_idx]);
	INIT_LIST_HEAD(&hw->fl_profs[blk_idx]);
पूर्ण

/**
 * ice_clear_hw_tbls - clear HW tables and flow profiles
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
व्योम ice_clear_hw_tbls(काष्ठा ice_hw *hw)
अणु
	u8 i;

	क्रम (i = 0; i < ICE_BLK_COUNT; i++) अणु
		काष्ठा ice_prof_redir *prof_redir = &hw->blk[i].prof_redir;
		काष्ठा ice_prof_tcam *prof = &hw->blk[i].prof;
		काष्ठा ice_xlt1 *xlt1 = &hw->blk[i].xlt1;
		काष्ठा ice_xlt2 *xlt2 = &hw->blk[i].xlt2;
		काष्ठा ice_es *es = &hw->blk[i].es;

		अगर (hw->blk[i].is_list_init) अणु
			ice_मुक्त_prof_map(hw, i);
			ice_मुक्त_flow_profs(hw, i);
		पूर्ण

		ice_मुक्त_vsig_tbl(hw, (क्रमागत ice_block)i);

		स_रखो(xlt1->ptypes, 0, xlt1->count * माप(*xlt1->ptypes));
		स_रखो(xlt1->ptg_tbl, 0,
		       ICE_MAX_PTGS * माप(*xlt1->ptg_tbl));
		स_रखो(xlt1->t, 0, xlt1->count * माप(*xlt1->t));

		स_रखो(xlt2->vsis, 0, xlt2->count * माप(*xlt2->vsis));
		स_रखो(xlt2->vsig_tbl, 0,
		       xlt2->count * माप(*xlt2->vsig_tbl));
		स_रखो(xlt2->t, 0, xlt2->count * माप(*xlt2->t));

		स_रखो(prof->t, 0, prof->count * माप(*prof->t));
		स_रखो(prof_redir->t, 0,
		       prof_redir->count * माप(*prof_redir->t));

		स_रखो(es->t, 0, es->count * माप(*es->t) * es->fvw);
		स_रखो(es->ref_count, 0, es->count * माप(*es->ref_count));
		स_रखो(es->written, 0, es->count * माप(*es->written));
		स_रखो(es->mask_ena, 0, es->count * माप(*es->mask_ena));
	पूर्ण
पूर्ण

/**
 * ice_init_hw_tbls - init hardware table memory
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 */
क्रमागत ice_status ice_init_hw_tbls(काष्ठा ice_hw *hw)
अणु
	u8 i;

	mutex_init(&hw->rss_locks);
	INIT_LIST_HEAD(&hw->rss_list_head);
	ice_init_all_prof_masks(hw);
	क्रम (i = 0; i < ICE_BLK_COUNT; i++) अणु
		काष्ठा ice_prof_redir *prof_redir = &hw->blk[i].prof_redir;
		काष्ठा ice_prof_tcam *prof = &hw->blk[i].prof;
		काष्ठा ice_xlt1 *xlt1 = &hw->blk[i].xlt1;
		काष्ठा ice_xlt2 *xlt2 = &hw->blk[i].xlt2;
		काष्ठा ice_es *es = &hw->blk[i].es;
		u16 j;

		अगर (hw->blk[i].is_list_init)
			जारी;

		ice_init_flow_profs(hw, i);
		mutex_init(&es->prof_map_lock);
		INIT_LIST_HEAD(&es->prof_map);
		hw->blk[i].is_list_init = true;

		hw->blk[i].overग_लिखो = blk_sizes[i].overग_लिखो;
		es->reverse = blk_sizes[i].reverse;

		xlt1->sid = ice_blk_sids[i][ICE_SID_XLT1_OFF];
		xlt1->count = blk_sizes[i].xlt1;

		xlt1->ptypes = devm_kसुस्मृति(ice_hw_to_dev(hw), xlt1->count,
					    माप(*xlt1->ptypes), GFP_KERNEL);

		अगर (!xlt1->ptypes)
			जाओ err;

		xlt1->ptg_tbl = devm_kसुस्मृति(ice_hw_to_dev(hw), ICE_MAX_PTGS,
					     माप(*xlt1->ptg_tbl),
					     GFP_KERNEL);

		अगर (!xlt1->ptg_tbl)
			जाओ err;

		xlt1->t = devm_kसुस्मृति(ice_hw_to_dev(hw), xlt1->count,
				       माप(*xlt1->t), GFP_KERNEL);
		अगर (!xlt1->t)
			जाओ err;

		xlt2->sid = ice_blk_sids[i][ICE_SID_XLT2_OFF];
		xlt2->count = blk_sizes[i].xlt2;

		xlt2->vsis = devm_kसुस्मृति(ice_hw_to_dev(hw), xlt2->count,
					  माप(*xlt2->vsis), GFP_KERNEL);

		अगर (!xlt2->vsis)
			जाओ err;

		xlt2->vsig_tbl = devm_kसुस्मृति(ice_hw_to_dev(hw), xlt2->count,
					      माप(*xlt2->vsig_tbl),
					      GFP_KERNEL);
		अगर (!xlt2->vsig_tbl)
			जाओ err;

		क्रम (j = 0; j < xlt2->count; j++)
			INIT_LIST_HEAD(&xlt2->vsig_tbl[j].prop_lst);

		xlt2->t = devm_kसुस्मृति(ice_hw_to_dev(hw), xlt2->count,
				       माप(*xlt2->t), GFP_KERNEL);
		अगर (!xlt2->t)
			जाओ err;

		prof->sid = ice_blk_sids[i][ICE_SID_PR_OFF];
		prof->count = blk_sizes[i].prof_tcam;
		prof->max_prof_id = blk_sizes[i].prof_id;
		prof->cdid_bits = blk_sizes[i].prof_cdid_bits;
		prof->t = devm_kसुस्मृति(ice_hw_to_dev(hw), prof->count,
				       माप(*prof->t), GFP_KERNEL);

		अगर (!prof->t)
			जाओ err;

		prof_redir->sid = ice_blk_sids[i][ICE_SID_PR_REसूची_OFF];
		prof_redir->count = blk_sizes[i].prof_redir;
		prof_redir->t = devm_kसुस्मृति(ice_hw_to_dev(hw),
					     prof_redir->count,
					     माप(*prof_redir->t),
					     GFP_KERNEL);

		अगर (!prof_redir->t)
			जाओ err;

		es->sid = ice_blk_sids[i][ICE_SID_ES_OFF];
		es->count = blk_sizes[i].es;
		es->fvw = blk_sizes[i].fvw;
		es->t = devm_kसुस्मृति(ice_hw_to_dev(hw),
				     (u32)(es->count * es->fvw),
				     माप(*es->t), GFP_KERNEL);
		अगर (!es->t)
			जाओ err;

		es->ref_count = devm_kसुस्मृति(ice_hw_to_dev(hw), es->count,
					     माप(*es->ref_count),
					     GFP_KERNEL);
		अगर (!es->ref_count)
			जाओ err;

		es->written = devm_kसुस्मृति(ice_hw_to_dev(hw), es->count,
					   माप(*es->written), GFP_KERNEL);
		अगर (!es->written)
			जाओ err;

		es->mask_ena = devm_kसुस्मृति(ice_hw_to_dev(hw), es->count,
					    माप(*es->mask_ena), GFP_KERNEL);
		अगर (!es->mask_ena)
			जाओ err;
	पूर्ण
	वापस 0;

err:
	ice_मुक्त_hw_tbls(hw);
	वापस ICE_ERR_NO_MEMORY;
पूर्ण

/**
 * ice_prof_gen_key - generate profile ID key
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block in which to ग_लिखो profile ID to
 * @ptg: packet type group (PTG) portion of key
 * @vsig: VSIG portion of key
 * @cdid: CDID portion of key
 * @flags: flag portion of key
 * @vl_msk: valid mask
 * @dc_msk: करोn't care mask
 * @nm_msk: never match mask
 * @key: output of profile ID key
 */
अटल क्रमागत ice_status
ice_prof_gen_key(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u8 ptg, u16 vsig,
		 u8 cdid, u16 flags, u8 vl_msk[ICE_TCAM_KEY_VAL_SZ],
		 u8 dc_msk[ICE_TCAM_KEY_VAL_SZ], u8 nm_msk[ICE_TCAM_KEY_VAL_SZ],
		 u8 key[ICE_TCAM_KEY_SZ])
अणु
	काष्ठा ice_prof_id_key inkey;

	inkey.xlt1 = ptg;
	inkey.xlt2_cdid = cpu_to_le16(vsig);
	inkey.flags = cpu_to_le16(flags);

	चयन (hw->blk[blk].prof.cdid_bits) अणु
	हाल 0:
		अवरोध;
	हाल 2:
#घोषणा ICE_CD_2_M 0xC000U
#घोषणा ICE_CD_2_S 14
		inkey.xlt2_cdid &= ~cpu_to_le16(ICE_CD_2_M);
		inkey.xlt2_cdid |= cpu_to_le16(BIT(cdid) << ICE_CD_2_S);
		अवरोध;
	हाल 4:
#घोषणा ICE_CD_4_M 0xF000U
#घोषणा ICE_CD_4_S 12
		inkey.xlt2_cdid &= ~cpu_to_le16(ICE_CD_4_M);
		inkey.xlt2_cdid |= cpu_to_le16(BIT(cdid) << ICE_CD_4_S);
		अवरोध;
	हाल 8:
#घोषणा ICE_CD_8_M 0xFF00U
#घोषणा ICE_CD_8_S 16
		inkey.xlt2_cdid &= ~cpu_to_le16(ICE_CD_8_M);
		inkey.xlt2_cdid |= cpu_to_le16(BIT(cdid) << ICE_CD_8_S);
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_PKG, "Error in profile config\n");
		अवरोध;
	पूर्ण

	वापस ice_set_key(key, ICE_TCAM_KEY_SZ, (u8 *)&inkey, vl_msk, dc_msk,
			   nm_msk, 0, ICE_TCAM_KEY_SZ / 2);
पूर्ण

/**
 * ice_tcam_ग_लिखो_entry - ग_लिखो TCAM entry
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: the block in which to ग_लिखो profile ID to
 * @idx: the entry index to ग_लिखो to
 * @prof_id: profile ID
 * @ptg: packet type group (PTG) portion of key
 * @vsig: VSIG portion of key
 * @cdid: CDID portion of key
 * @flags: flag portion of key
 * @vl_msk: valid mask
 * @dc_msk: करोn't care mask
 * @nm_msk: never match mask
 */
अटल क्रमागत ice_status
ice_tcam_ग_लिखो_entry(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 idx,
		     u8 prof_id, u8 ptg, u16 vsig, u8 cdid, u16 flags,
		     u8 vl_msk[ICE_TCAM_KEY_VAL_SZ],
		     u8 dc_msk[ICE_TCAM_KEY_VAL_SZ],
		     u8 nm_msk[ICE_TCAM_KEY_VAL_SZ])
अणु
	काष्ठा ice_prof_tcam_entry;
	क्रमागत ice_status status;

	status = ice_prof_gen_key(hw, blk, ptg, vsig, cdid, flags, vl_msk,
				  dc_msk, nm_msk, hw->blk[blk].prof.t[idx].key);
	अगर (!status) अणु
		hw->blk[blk].prof.t[idx].addr = cpu_to_le16(idx);
		hw->blk[blk].prof.t[idx].prof_id = prof_id;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_vsig_get_ref - वापसs number of VSIs beदीर्घ to a VSIG
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsig: VSIG to query
 * @refs: poपूर्णांकer to variable to receive the reference count
 */
अटल क्रमागत ice_status
ice_vsig_get_ref(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig, u16 *refs)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M;
	काष्ठा ice_vsig_vsi *ptr;

	*refs = 0;

	अगर (!hw->blk[blk].xlt2.vsig_tbl[idx].in_use)
		वापस ICE_ERR_DOES_NOT_EXIST;

	ptr = hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	जबतक (ptr) अणु
		(*refs)++;
		ptr = ptr->next_vsi;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_has_prof_vsig - check to see अगर VSIG has a specअगरic profile
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @blk: HW block
 * @vsig: VSIG to check against
 * @hdl: profile handle
 */
अटल bool
ice_has_prof_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig, u64 hdl)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M;
	काष्ठा ice_vsig_prof *ent;

	list_क्रम_each_entry(ent, &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
			    list)
		अगर (ent->profile_cookie == hdl)
			वापस true;

	ice_debug(hw, ICE_DBG_INIT, "Characteristic list for VSI group %d not found.\n",
		  vsig);
	वापस false;
पूर्ण

/**
 * ice_prof_bld_es - build profile ID extraction sequence changes
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @bld: the update package buffer build to add to
 * @chgs: the list of changes to make in hardware
 */
अटल क्रमागत ice_status
ice_prof_bld_es(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		काष्ठा ice_buf_build *bld, काष्ठा list_head *chgs)
अणु
	u16 vec_size = hw->blk[blk].es.fvw * माप(काष्ठा ice_fv_word);
	काष्ठा ice_chs_chg *पंचांगp;

	list_क्रम_each_entry(पंचांगp, chgs, list_entry)
		अगर (पंचांगp->type == ICE_PTG_ES_ADD && पंचांगp->add_prof) अणु
			u16 off = पंचांगp->prof_id * hw->blk[blk].es.fvw;
			काष्ठा ice_pkg_es *p;
			u32 id;

			id = ice_sect_id(blk, ICE_VEC_TBL);
			p = ice_pkg_buf_alloc_section(bld, id,
						      काष्ठा_size(p, es, 1) +
						      vec_size -
						      माप(p->es[0]));

			अगर (!p)
				वापस ICE_ERR_MAX_LIMIT;

			p->count = cpu_to_le16(1);
			p->offset = cpu_to_le16(पंचांगp->prof_id);

			स_नकल(p->es, &hw->blk[blk].es.t[off], vec_size);
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_prof_bld_tcam - build profile ID TCAM changes
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @bld: the update package buffer build to add to
 * @chgs: the list of changes to make in hardware
 */
अटल क्रमागत ice_status
ice_prof_bld_tcam(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		  काष्ठा ice_buf_build *bld, काष्ठा list_head *chgs)
अणु
	काष्ठा ice_chs_chg *पंचांगp;

	list_क्रम_each_entry(पंचांगp, chgs, list_entry)
		अगर (पंचांगp->type == ICE_TCAM_ADD && पंचांगp->add_tcam_idx) अणु
			काष्ठा ice_prof_id_section *p;
			u32 id;

			id = ice_sect_id(blk, ICE_PROF_TCAM);
			p = ice_pkg_buf_alloc_section(bld, id,
						      काष्ठा_size(p, entry, 1));

			अगर (!p)
				वापस ICE_ERR_MAX_LIMIT;

			p->count = cpu_to_le16(1);
			p->entry[0].addr = cpu_to_le16(पंचांगp->tcam_idx);
			p->entry[0].prof_id = पंचांगp->prof_id;

			स_नकल(p->entry[0].key,
			       &hw->blk[blk].prof.t[पंचांगp->tcam_idx].key,
			       माप(hw->blk[blk].prof.t->key));
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_prof_bld_xlt1 - build XLT1 changes
 * @blk: hardware block
 * @bld: the update package buffer build to add to
 * @chgs: the list of changes to make in hardware
 */
अटल क्रमागत ice_status
ice_prof_bld_xlt1(क्रमागत ice_block blk, काष्ठा ice_buf_build *bld,
		  काष्ठा list_head *chgs)
अणु
	काष्ठा ice_chs_chg *पंचांगp;

	list_क्रम_each_entry(पंचांगp, chgs, list_entry)
		अगर (पंचांगp->type == ICE_PTG_ES_ADD && पंचांगp->add_ptg) अणु
			काष्ठा ice_xlt1_section *p;
			u32 id;

			id = ice_sect_id(blk, ICE_XLT1);
			p = ice_pkg_buf_alloc_section(bld, id,
						      काष्ठा_size(p, value, 1));

			अगर (!p)
				वापस ICE_ERR_MAX_LIMIT;

			p->count = cpu_to_le16(1);
			p->offset = cpu_to_le16(पंचांगp->ptype);
			p->value[0] = पंचांगp->ptg;
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_prof_bld_xlt2 - build XLT2 changes
 * @blk: hardware block
 * @bld: the update package buffer build to add to
 * @chgs: the list of changes to make in hardware
 */
अटल क्रमागत ice_status
ice_prof_bld_xlt2(क्रमागत ice_block blk, काष्ठा ice_buf_build *bld,
		  काष्ठा list_head *chgs)
अणु
	काष्ठा ice_chs_chg *पंचांगp;

	list_क्रम_each_entry(पंचांगp, chgs, list_entry) अणु
		काष्ठा ice_xlt2_section *p;
		u32 id;

		चयन (पंचांगp->type) अणु
		हाल ICE_VSIG_ADD:
		हाल ICE_VSI_MOVE:
		हाल ICE_VSIG_REM:
			id = ice_sect_id(blk, ICE_XLT2);
			p = ice_pkg_buf_alloc_section(bld, id,
						      काष्ठा_size(p, value, 1));

			अगर (!p)
				वापस ICE_ERR_MAX_LIMIT;

			p->count = cpu_to_le16(1);
			p->offset = cpu_to_le16(पंचांगp->vsi);
			p->value[0] = cpu_to_le16(पंचांगp->vsig);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_upd_prof_hw - update hardware using the change list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @chgs: the list of changes to make in hardware
 */
अटल क्रमागत ice_status
ice_upd_prof_hw(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		काष्ठा list_head *chgs)
अणु
	काष्ठा ice_buf_build *b;
	काष्ठा ice_chs_chg *पंचांगp;
	क्रमागत ice_status status;
	u16 pkg_sects;
	u16 xlt1 = 0;
	u16 xlt2 = 0;
	u16 tcam = 0;
	u16 es = 0;
	u16 sects;

	/* count number of sections we need */
	list_क्रम_each_entry(पंचांगp, chgs, list_entry) अणु
		चयन (पंचांगp->type) अणु
		हाल ICE_PTG_ES_ADD:
			अगर (पंचांगp->add_ptg)
				xlt1++;
			अगर (पंचांगp->add_prof)
				es++;
			अवरोध;
		हाल ICE_TCAM_ADD:
			tcam++;
			अवरोध;
		हाल ICE_VSIG_ADD:
		हाल ICE_VSI_MOVE:
		हाल ICE_VSIG_REM:
			xlt2++;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	sects = xlt1 + xlt2 + tcam + es;

	अगर (!sects)
		वापस 0;

	/* Build update package buffer */
	b = ice_pkg_buf_alloc(hw);
	अगर (!b)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_pkg_buf_reserve_section(b, sects);
	अगर (status)
		जाओ error_पंचांगp;

	/* Preserve order of table update: ES, TCAM, PTG, VSIG */
	अगर (es) अणु
		status = ice_prof_bld_es(hw, blk, b, chgs);
		अगर (status)
			जाओ error_पंचांगp;
	पूर्ण

	अगर (tcam) अणु
		status = ice_prof_bld_tcam(hw, blk, b, chgs);
		अगर (status)
			जाओ error_पंचांगp;
	पूर्ण

	अगर (xlt1) अणु
		status = ice_prof_bld_xlt1(blk, b, chgs);
		अगर (status)
			जाओ error_पंचांगp;
	पूर्ण

	अगर (xlt2) अणु
		status = ice_prof_bld_xlt2(blk, b, chgs);
		अगर (status)
			जाओ error_पंचांगp;
	पूर्ण

	/* After package buffer build check अगर the section count in buffer is
	 * non-zero and matches the number of sections detected क्रम package
	 * update.
	 */
	pkg_sects = ice_pkg_buf_get_active_sections(b);
	अगर (!pkg_sects || pkg_sects != sects) अणु
		status = ICE_ERR_INVAL_SIZE;
		जाओ error_पंचांगp;
	पूर्ण

	/* update package */
	status = ice_update_pkg(hw, ice_pkg_buf(b), 1);
	अगर (status == ICE_ERR_AQ_ERROR)
		ice_debug(hw, ICE_DBG_INIT, "Unable to update HW profile\n");

error_पंचांगp:
	ice_pkg_buf_मुक्त(hw, b);
	वापस status;
पूर्ण

/**
 * ice_update_fd_mask - set Flow Director Field Vector mask क्रम a profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @prof_id: profile ID
 * @mask_sel: mask select
 *
 * This function enable any of the masks selected by the mask select parameter
 * क्रम the profile specअगरied.
 */
अटल व्योम ice_update_fd_mask(काष्ठा ice_hw *hw, u16 prof_id, u32 mask_sel)
अणु
	wr32(hw, GLQF_FDMASK_SEL(prof_id), mask_sel);

	ice_debug(hw, ICE_DBG_INIT, "fd mask(%d): %x = %x\n", prof_id,
		  GLQF_FDMASK_SEL(prof_id), mask_sel);
पूर्ण

काष्ठा ice_fd_src_dst_pair अणु
	u8 prot_id;
	u8 count;
	u16 off;
पूर्ण;

अटल स्थिर काष्ठा ice_fd_src_dst_pair ice_fd_pairs[] = अणु
	/* These are defined in pairs */
	अणु ICE_PROT_IPV4_OF_OR_S, 2, 12 पूर्ण,
	अणु ICE_PROT_IPV4_OF_OR_S, 2, 16 पूर्ण,

	अणु ICE_PROT_IPV4_IL, 2, 12 पूर्ण,
	अणु ICE_PROT_IPV4_IL, 2, 16 पूर्ण,

	अणु ICE_PROT_IPV6_OF_OR_S, 8, 8 पूर्ण,
	अणु ICE_PROT_IPV6_OF_OR_S, 8, 24 पूर्ण,

	अणु ICE_PROT_IPV6_IL, 8, 8 पूर्ण,
	अणु ICE_PROT_IPV6_IL, 8, 24 पूर्ण,

	अणु ICE_PROT_TCP_IL, 1, 0 पूर्ण,
	अणु ICE_PROT_TCP_IL, 1, 2 पूर्ण,

	अणु ICE_PROT_UDP_OF, 1, 0 पूर्ण,
	अणु ICE_PROT_UDP_OF, 1, 2 पूर्ण,

	अणु ICE_PROT_UDP_IL_OR_S, 1, 0 पूर्ण,
	अणु ICE_PROT_UDP_IL_OR_S, 1, 2 पूर्ण,

	अणु ICE_PROT_SCTP_IL, 1, 0 पूर्ण,
	अणु ICE_PROT_SCTP_IL, 1, 2 पूर्ण
पूर्ण;

#घोषणा ICE_FD_SRC_DST_PAIR_COUNT	ARRAY_SIZE(ice_fd_pairs)

/**
 * ice_update_fd_swap - set रेजिस्टर appropriately क्रम a FD FV extraction
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @prof_id: profile ID
 * @es: extraction sequence (length of array is determined by the block)
 */
अटल क्रमागत ice_status
ice_update_fd_swap(काष्ठा ice_hw *hw, u16 prof_id, काष्ठा ice_fv_word *es)
अणु
	DECLARE_BITMAP(pair_list, ICE_FD_SRC_DST_PAIR_COUNT);
	u8 pair_start[ICE_FD_SRC_DST_PAIR_COUNT] = अणु 0 पूर्ण;
#घोषणा ICE_FD_FV_NOT_FOUND (-2)
	s8 first_मुक्त = ICE_FD_FV_NOT_FOUND;
	u8 used[ICE_MAX_FV_WORDS] = अणु 0 पूर्ण;
	s8 orig_मुक्त, si;
	u32 mask_sel = 0;
	u8 i, j, k;

	biपंचांगap_zero(pair_list, ICE_FD_SRC_DST_PAIR_COUNT);

	/* This code assumes that the Flow Director field vectors are asचिन्हित
	 * from the end of the FV indexes working towards the zero index, that
	 * only complete fields will be included and will be consecutive, and
	 * that there are no gaps between valid indexes.
	 */

	/* Determine swap fields present */
	क्रम (i = 0; i < hw->blk[ICE_BLK_FD].es.fvw; i++) अणु
		/* Find the first मुक्त entry, assuming right to left population.
		 * This is where we can start adding additional pairs अगर needed.
		 */
		अगर (first_मुक्त == ICE_FD_FV_NOT_FOUND && es[i].prot_id !=
		    ICE_PROT_INVALID)
			first_मुक्त = i - 1;

		क्रम (j = 0; j < ICE_FD_SRC_DST_PAIR_COUNT; j++)
			अगर (es[i].prot_id == ice_fd_pairs[j].prot_id &&
			    es[i].off == ice_fd_pairs[j].off) अणु
				set_bit(j, pair_list);
				pair_start[j] = i;
			पूर्ण
	पूर्ण

	orig_मुक्त = first_मुक्त;

	/* determine missing swap fields that need to be added */
	क्रम (i = 0; i < ICE_FD_SRC_DST_PAIR_COUNT; i += 2) अणु
		u8 bit1 = test_bit(i + 1, pair_list);
		u8 bit0 = test_bit(i, pair_list);

		अगर (bit0 ^ bit1) अणु
			u8 index;

			/* add the appropriate 'paired' entry */
			अगर (!bit0)
				index = i;
			अन्यथा
				index = i + 1;

			/* check क्रम room */
			अगर (first_मुक्त + 1 < (s8)ice_fd_pairs[index].count)
				वापस ICE_ERR_MAX_LIMIT;

			/* place in extraction sequence */
			क्रम (k = 0; k < ice_fd_pairs[index].count; k++) अणु
				es[first_मुक्त - k].prot_id =
					ice_fd_pairs[index].prot_id;
				es[first_मुक्त - k].off =
					ice_fd_pairs[index].off + (k * 2);

				अगर (k > first_मुक्त)
					वापस ICE_ERR_OUT_OF_RANGE;

				/* keep track of non-relevant fields */
				mask_sel |= BIT(first_मुक्त - k);
			पूर्ण

			pair_start[index] = first_मुक्त;
			first_मुक्त -= ice_fd_pairs[index].count;
		पूर्ण
	पूर्ण

	/* fill in the swap array */
	si = hw->blk[ICE_BLK_FD].es.fvw - 1;
	जबतक (si >= 0) अणु
		u8 indexes_used = 1;

		/* assume flat at this index */
#घोषणा ICE_SWAP_VALID	0x80
		used[si] = si | ICE_SWAP_VALID;

		अगर (orig_मुक्त == ICE_FD_FV_NOT_FOUND || si <= orig_मुक्त) अणु
			si -= indexes_used;
			जारी;
		पूर्ण

		/* check क्रम a swap location */
		क्रम (j = 0; j < ICE_FD_SRC_DST_PAIR_COUNT; j++)
			अगर (es[si].prot_id == ice_fd_pairs[j].prot_id &&
			    es[si].off == ice_fd_pairs[j].off) अणु
				u8 idx;

				/* determine the appropriate matching field */
				idx = j + ((j % 2) ? -1 : 1);

				indexes_used = ice_fd_pairs[idx].count;
				क्रम (k = 0; k < indexes_used; k++) अणु
					used[si - k] = (pair_start[idx] - k) |
						ICE_SWAP_VALID;
				पूर्ण

				अवरोध;
			पूर्ण

		si -= indexes_used;
	पूर्ण

	/* क्रम each set of 4 swap and 4 inset indexes, ग_लिखो the appropriate
	 * रेजिस्टर
	 */
	क्रम (j = 0; j < hw->blk[ICE_BLK_FD].es.fvw / 4; j++) अणु
		u32 raw_swap = 0;
		u32 raw_in = 0;

		क्रम (k = 0; k < 4; k++) अणु
			u8 idx;

			idx = (j * 4) + k;
			अगर (used[idx] && !(mask_sel & BIT(idx))) अणु
				raw_swap |= used[idx] << (k * BITS_PER_BYTE);
#घोषणा ICE_INSET_DFLT 0x9f
				raw_in |= ICE_INSET_DFLT << (k * BITS_PER_BYTE);
			पूर्ण
		पूर्ण

		/* ग_लिखो the appropriate swap रेजिस्टर set */
		wr32(hw, GLQF_FDSWAP(prof_id, j), raw_swap);

		ice_debug(hw, ICE_DBG_INIT, "swap wr(%d, %d): %x = %08x\n",
			  prof_id, j, GLQF_FDSWAP(prof_id, j), raw_swap);

		/* ग_लिखो the appropriate inset रेजिस्टर set */
		wr32(hw, GLQF_FDINSET(prof_id, j), raw_in);

		ice_debug(hw, ICE_DBG_INIT, "inset wr(%d, %d): %x = %08x\n",
			  prof_id, j, GLQF_FDINSET(prof_id, j), raw_in);
	पूर्ण

	/* initially clear the mask select क्रम this profile */
	ice_update_fd_mask(hw, prof_id, 0);

	वापस 0;
पूर्ण

/* The entries here needs to match the order of क्रमागत ice_ptype_attrib */
अटल स्थिर काष्ठा ice_ptype_attrib_info ice_ptype_attributes[] = अणु
	अणु ICE_GTP_PDU_EH,	ICE_GTP_PDU_FLAG_MASK पूर्ण,
	अणु ICE_GTP_SESSION,	ICE_GTP_FLAGS_MASK पूर्ण,
	अणु ICE_GTP_DOWNLINK,	ICE_GTP_FLAGS_MASK पूर्ण,
	अणु ICE_GTP_UPLINK,	ICE_GTP_FLAGS_MASK पूर्ण,
पूर्ण;

/**
 * ice_get_ptype_attrib_info - get PTYPE attribute inक्रमmation
 * @type: attribute type
 * @info: poपूर्णांकer to variable to the attribute inक्रमmation
 */
अटल व्योम
ice_get_ptype_attrib_info(क्रमागत ice_ptype_attrib_type type,
			  काष्ठा ice_ptype_attrib_info *info)
अणु
	*info = ice_ptype_attributes[type];
पूर्ण

/**
 * ice_add_prof_attrib - add any PTG with attributes to profile
 * @prof: poपूर्णांकer to the profile to which PTG entries will be added
 * @ptg: PTG to be added
 * @ptype: PTYPE that needs to be looked up
 * @attr: array of attributes that will be considered
 * @attr_cnt: number of elements in the attribute array
 */
अटल क्रमागत ice_status
ice_add_prof_attrib(काष्ठा ice_prof_map *prof, u8 ptg, u16 ptype,
		    स्थिर काष्ठा ice_ptype_attributes *attr, u16 attr_cnt)
अणु
	bool found = false;
	u16 i;

	क्रम (i = 0; i < attr_cnt; i++)
		अगर (attr[i].ptype == ptype) अणु
			found = true;

			prof->ptg[prof->ptg_cnt] = ptg;
			ice_get_ptype_attrib_info(attr[i].attrib,
						  &prof->attr[prof->ptg_cnt]);

			अगर (++prof->ptg_cnt >= ICE_MAX_PTG_PER_PROखाता)
				वापस ICE_ERR_MAX_LIMIT;
		पूर्ण

	अगर (!found)
		वापस ICE_ERR_DOES_NOT_EXIST;

	वापस 0;
पूर्ण

/**
 * ice_add_prof - add profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @id: profile tracking ID
 * @ptypes: array of biपंचांगaps indicating ptypes (ICE_FLOW_PTYPE_MAX bits)
 * @attr: array of attributes
 * @attr_cnt: number of elements in attr array
 * @es: extraction sequence (length of array is determined by the block)
 * @masks: mask क्रम extraction sequence
 *
 * This function रेजिस्टरs a profile, which matches a set of PTYPES with a
 * particular extraction sequence. While the hardware profile is allocated
 * it will not be written until the first call to ice_add_flow that specअगरies
 * the ID value used here.
 */
क्रमागत ice_status
ice_add_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id, u8 ptypes[],
	     स्थिर काष्ठा ice_ptype_attributes *attr, u16 attr_cnt,
	     काष्ठा ice_fv_word *es, u16 *masks)
अणु
	u32 bytes = DIV_ROUND_UP(ICE_FLOW_PTYPE_MAX, BITS_PER_BYTE);
	DECLARE_BITMAP(ptgs_used, ICE_XLT1_CNT);
	काष्ठा ice_prof_map *prof;
	क्रमागत ice_status status;
	u8 byte = 0;
	u8 prof_id;

	biपंचांगap_zero(ptgs_used, ICE_XLT1_CNT);

	mutex_lock(&hw->blk[blk].es.prof_map_lock);

	/* search क्रम existing profile */
	status = ice_find_prof_id_with_mask(hw, blk, es, masks, &prof_id);
	अगर (status) अणु
		/* allocate profile ID */
		status = ice_alloc_prof_id(hw, blk, &prof_id);
		अगर (status)
			जाओ err_ice_add_prof;
		अगर (blk == ICE_BLK_FD) अणु
			/* For Flow Director block, the extraction sequence may
			 * need to be altered in the हाल where there are paired
			 * fields that have no match. This is necessary because
			 * क्रम Flow Director, src and dest fields need to paired
			 * क्रम filter programming and these values are swapped
			 * during Tx.
			 */
			status = ice_update_fd_swap(hw, prof_id, es);
			अगर (status)
				जाओ err_ice_add_prof;
		पूर्ण
		status = ice_update_prof_masking(hw, blk, prof_id, masks);
		अगर (status)
			जाओ err_ice_add_prof;

		/* and ग_लिखो new es */
		ice_ग_लिखो_es(hw, blk, prof_id, es);
	पूर्ण

	ice_prof_inc_ref(hw, blk, prof_id);

	/* add profile info */
	prof = devm_kzalloc(ice_hw_to_dev(hw), माप(*prof), GFP_KERNEL);
	अगर (!prof) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ err_ice_add_prof;
	पूर्ण

	prof->profile_cookie = id;
	prof->prof_id = prof_id;
	prof->ptg_cnt = 0;
	prof->context = 0;

	/* build list of ptgs */
	जबतक (bytes && prof->ptg_cnt < ICE_MAX_PTG_PER_PROखाता) अणु
		u8 bit;

		अगर (!ptypes[byte]) अणु
			bytes--;
			byte++;
			जारी;
		पूर्ण

		/* Examine 8 bits per byte */
		क्रम_each_set_bit(bit, (अचिन्हित दीर्घ *)&ptypes[byte],
				 BITS_PER_BYTE) अणु
			u16 ptype;
			u8 ptg;

			ptype = byte * BITS_PER_BYTE + bit;

			/* The package should place all ptypes in a non-zero
			 * PTG, so the following call should never fail.
			 */
			अगर (ice_ptg_find_ptype(hw, blk, ptype, &ptg))
				जारी;

			/* If PTG is alपढ़ोy added, skip and जारी */
			अगर (test_bit(ptg, ptgs_used))
				जारी;

			set_bit(ptg, ptgs_used);
			/* Check to see there are any attributes क्रम
			 * this PTYPE, and add them अगर found.
			 */
			status = ice_add_prof_attrib(prof, ptg, ptype,
						     attr, attr_cnt);
			अगर (status == ICE_ERR_MAX_LIMIT)
				अवरोध;
			अगर (status) अणु
				/* This is simple a PTYPE/PTG with no
				 * attribute
				 */
				prof->ptg[prof->ptg_cnt] = ptg;
				prof->attr[prof->ptg_cnt].flags = 0;
				prof->attr[prof->ptg_cnt].mask = 0;

				अगर (++prof->ptg_cnt >=
				    ICE_MAX_PTG_PER_PROखाता)
					अवरोध;
			पूर्ण
		पूर्ण

		bytes--;
		byte++;
	पूर्ण

	list_add(&prof->list, &hw->blk[blk].es.prof_map);
	status = 0;

err_ice_add_prof:
	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	वापस status;
पूर्ण

/**
 * ice_search_prof_id - Search क्रम a profile tracking ID
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @id: profile tracking ID
 *
 * This will search क्रम a profile tracking ID which was previously added.
 * The profile map lock should be held beक्रमe calling this function.
 */
अटल काष्ठा ice_prof_map *
ice_search_prof_id(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id)
अणु
	काष्ठा ice_prof_map *entry = शून्य;
	काष्ठा ice_prof_map *map;

	list_क्रम_each_entry(map, &hw->blk[blk].es.prof_map, list)
		अगर (map->profile_cookie == id) अणु
			entry = map;
			अवरोध;
		पूर्ण

	वापस entry;
पूर्ण

/**
 * ice_vsig_prof_id_count - count profiles in a VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: VSIG to हटाओ the profile from
 */
अटल u16
ice_vsig_prof_id_count(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M, count = 0;
	काष्ठा ice_vsig_prof *p;

	list_क्रम_each_entry(p, &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
			    list)
		count++;

	वापस count;
पूर्ण

/**
 * ice_rel_tcam_idx - release a TCAM index
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @idx: the index to release
 */
अटल क्रमागत ice_status
ice_rel_tcam_idx(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 idx)
अणु
	/* Masks to invoke a never match entry */
	u8 vl_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	u8 dc_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFE, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	u8 nm_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0x01, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	क्रमागत ice_status status;

	/* ग_लिखो the TCAM entry */
	status = ice_tcam_ग_लिखो_entry(hw, blk, idx, 0, 0, 0, 0, 0, vl_msk,
				      dc_msk, nm_msk);
	अगर (status)
		वापस status;

	/* release the TCAM entry */
	status = ice_मुक्त_tcam_ent(hw, blk, idx);

	वापस status;
पूर्ण

/**
 * ice_rem_prof_id - हटाओ one profile from a VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @prof: poपूर्णांकer to profile काष्ठाure to हटाओ
 */
अटल क्रमागत ice_status
ice_rem_prof_id(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		काष्ठा ice_vsig_prof *prof)
अणु
	क्रमागत ice_status status;
	u16 i;

	क्रम (i = 0; i < prof->tcam_count; i++)
		अगर (prof->tcam[i].in_use) अणु
			prof->tcam[i].in_use = false;
			status = ice_rel_tcam_idx(hw, blk,
						  prof->tcam[i].tcam_idx);
			अगर (status)
				वापस ICE_ERR_HW_TABLE;
		पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_rem_vsig - हटाओ VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: the VSIG to हटाओ
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_rem_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig,
	     काष्ठा list_head *chg)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M;
	काष्ठा ice_vsig_vsi *vsi_cur;
	काष्ठा ice_vsig_prof *d, *t;
	क्रमागत ice_status status;

	/* हटाओ TCAM entries */
	list_क्रम_each_entry_safe(d, t,
				 &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
				 list) अणु
		status = ice_rem_prof_id(hw, blk, d);
		अगर (status)
			वापस status;

		list_del(&d->list);
		devm_kमुक्त(ice_hw_to_dev(hw), d);
	पूर्ण

	/* Move all VSIS associated with this VSIG to the शेष VSIG */
	vsi_cur = hw->blk[blk].xlt2.vsig_tbl[idx].first_vsi;
	/* If the VSIG has at least 1 VSI then iterate through the list
	 * and हटाओ the VSIs beक्रमe deleting the group.
	 */
	अगर (vsi_cur)
		करो अणु
			काष्ठा ice_vsig_vsi *पंचांगp = vsi_cur->next_vsi;
			काष्ठा ice_chs_chg *p;

			p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p),
					 GFP_KERNEL);
			अगर (!p)
				वापस ICE_ERR_NO_MEMORY;

			p->type = ICE_VSIG_REM;
			p->orig_vsig = vsig;
			p->vsig = ICE_DEFAULT_VSIG;
			p->vsi = vsi_cur - hw->blk[blk].xlt2.vsis;

			list_add(&p->list_entry, chg);

			vsi_cur = पंचांगp;
		पूर्ण जबतक (vsi_cur);

	वापस ice_vsig_मुक्त(hw, blk, vsig);
पूर्ण

/**
 * ice_rem_prof_id_vsig - हटाओ a specअगरic profile from a VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: VSIG to हटाओ the profile from
 * @hdl: profile handle indicating which profile to हटाओ
 * @chg: list to receive a record of changes
 */
अटल क्रमागत ice_status
ice_rem_prof_id_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig, u64 hdl,
		     काष्ठा list_head *chg)
अणु
	u16 idx = vsig & ICE_VSIG_IDX_M;
	काष्ठा ice_vsig_prof *p, *t;
	क्रमागत ice_status status;

	list_क्रम_each_entry_safe(p, t,
				 &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
				 list)
		अगर (p->profile_cookie == hdl) अणु
			अगर (ice_vsig_prof_id_count(hw, blk, vsig) == 1)
				/* this is the last profile, हटाओ the VSIG */
				वापस ice_rem_vsig(hw, blk, vsig, chg);

			status = ice_rem_prof_id(hw, blk, p);
			अगर (!status) अणु
				list_del(&p->list);
				devm_kमुक्त(ice_hw_to_dev(hw), p);
			पूर्ण
			वापस status;
		पूर्ण

	वापस ICE_ERR_DOES_NOT_EXIST;
पूर्ण

/**
 * ice_rem_flow_all - हटाओ all flows with a particular profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @id: profile tracking ID
 */
अटल क्रमागत ice_status
ice_rem_flow_all(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id)
अणु
	काष्ठा ice_chs_chg *del, *पंचांगp;
	क्रमागत ice_status status;
	काष्ठा list_head chg;
	u16 i;

	INIT_LIST_HEAD(&chg);

	क्रम (i = 1; i < ICE_MAX_VSIGS; i++)
		अगर (hw->blk[blk].xlt2.vsig_tbl[i].in_use) अणु
			अगर (ice_has_prof_vsig(hw, blk, i, id)) अणु
				status = ice_rem_prof_id_vsig(hw, blk, i, id,
							      &chg);
				अगर (status)
					जाओ err_ice_rem_flow_all;
			पूर्ण
		पूर्ण

	status = ice_upd_prof_hw(hw, blk, &chg);

err_ice_rem_flow_all:
	list_क्रम_each_entry_safe(del, पंचांगp, &chg, list_entry) अणु
		list_del(&del->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), del);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_rem_prof - हटाओ profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @id: profile tracking ID
 *
 * This will हटाओ the profile specअगरied by the ID parameter, which was
 * previously created through ice_add_prof. If any existing entries
 * are associated with this profile, they will be हटाओd as well.
 */
क्रमागत ice_status ice_rem_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 id)
अणु
	काष्ठा ice_prof_map *pmap;
	क्रमागत ice_status status;

	mutex_lock(&hw->blk[blk].es.prof_map_lock);

	pmap = ice_search_prof_id(hw, blk, id);
	अगर (!pmap) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ err_ice_rem_prof;
	पूर्ण

	/* हटाओ all flows with this profile */
	status = ice_rem_flow_all(hw, blk, pmap->profile_cookie);
	अगर (status)
		जाओ err_ice_rem_prof;

	/* dereference profile, and possibly हटाओ */
	ice_prof_dec_ref(hw, blk, pmap->prof_id);

	list_del(&pmap->list);
	devm_kमुक्त(ice_hw_to_dev(hw), pmap);

err_ice_rem_prof:
	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	वापस status;
पूर्ण

/**
 * ice_get_prof - get profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @hdl: profile handle
 * @chg: change list
 */
अटल क्रमागत ice_status
ice_get_prof(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 hdl,
	     काष्ठा list_head *chg)
अणु
	क्रमागत ice_status status = 0;
	काष्ठा ice_prof_map *map;
	काष्ठा ice_chs_chg *p;
	u16 i;

	mutex_lock(&hw->blk[blk].es.prof_map_lock);
	/* Get the details on the profile specअगरied by the handle ID */
	map = ice_search_prof_id(hw, blk, hdl);
	अगर (!map) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ err_ice_get_prof;
	पूर्ण

	क्रम (i = 0; i < map->ptg_cnt; i++)
		अगर (!hw->blk[blk].es.written[map->prof_id]) अणु
			/* add ES to change list */
			p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p),
					 GFP_KERNEL);
			अगर (!p) अणु
				status = ICE_ERR_NO_MEMORY;
				जाओ err_ice_get_prof;
			पूर्ण

			p->type = ICE_PTG_ES_ADD;
			p->ptype = 0;
			p->ptg = map->ptg[i];
			p->add_ptg = 0;

			p->add_prof = 1;
			p->prof_id = map->prof_id;

			hw->blk[blk].es.written[map->prof_id] = true;

			list_add(&p->list_entry, chg);
		पूर्ण

err_ice_get_prof:
	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	/* let caller clean up the change list */
	वापस status;
पूर्ण

/**
 * ice_get_profs_vsig - get a copy of the list of profiles from a VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: VSIG from which to copy the list
 * @lst: output list
 *
 * This routine makes a copy of the list of profiles in the specअगरied VSIG.
 */
अटल क्रमागत ice_status
ice_get_profs_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig,
		   काष्ठा list_head *lst)
अणु
	काष्ठा ice_vsig_prof *ent1, *ent2;
	u16 idx = vsig & ICE_VSIG_IDX_M;

	list_क्रम_each_entry(ent1, &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
			    list) अणु
		काष्ठा ice_vsig_prof *p;

		/* copy to the input list */
		p = devm_kmemdup(ice_hw_to_dev(hw), ent1, माप(*p),
				 GFP_KERNEL);
		अगर (!p)
			जाओ err_ice_get_profs_vsig;

		list_add_tail(&p->list, lst);
	पूर्ण

	वापस 0;

err_ice_get_profs_vsig:
	list_क्रम_each_entry_safe(ent1, ent2, lst, list) अणु
		list_del(&ent1->list);
		devm_kमुक्त(ice_hw_to_dev(hw), ent1);
	पूर्ण

	वापस ICE_ERR_NO_MEMORY;
पूर्ण

/**
 * ice_add_prof_to_lst - add profile entry to a list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @lst: the list to be added to
 * @hdl: profile handle of entry to add
 */
अटल क्रमागत ice_status
ice_add_prof_to_lst(काष्ठा ice_hw *hw, क्रमागत ice_block blk,
		    काष्ठा list_head *lst, u64 hdl)
अणु
	क्रमागत ice_status status = 0;
	काष्ठा ice_prof_map *map;
	काष्ठा ice_vsig_prof *p;
	u16 i;

	mutex_lock(&hw->blk[blk].es.prof_map_lock);
	map = ice_search_prof_id(hw, blk, hdl);
	अगर (!map) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ err_ice_add_prof_to_lst;
	पूर्ण

	p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p), GFP_KERNEL);
	अगर (!p) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ err_ice_add_prof_to_lst;
	पूर्ण

	p->profile_cookie = map->profile_cookie;
	p->prof_id = map->prof_id;
	p->tcam_count = map->ptg_cnt;

	क्रम (i = 0; i < map->ptg_cnt; i++) अणु
		p->tcam[i].prof_id = map->prof_id;
		p->tcam[i].tcam_idx = ICE_INVALID_TCAM;
		p->tcam[i].ptg = map->ptg[i];
	पूर्ण

	list_add(&p->list, lst);

err_ice_add_prof_to_lst:
	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	वापस status;
पूर्ण

/**
 * ice_move_vsi - move VSI to another VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsi: the VSI to move
 * @vsig: the VSIG to move the VSI to
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_move_vsi(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u16 vsig,
	     काष्ठा list_head *chg)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_chs_chg *p;
	u16 orig_vsig;

	p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_vsig_find_vsi(hw, blk, vsi, &orig_vsig);
	अगर (!status)
		status = ice_vsig_add_mv_vsi(hw, blk, vsi, vsig);

	अगर (status) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), p);
		वापस status;
	पूर्ण

	p->type = ICE_VSI_MOVE;
	p->vsi = vsi;
	p->orig_vsig = orig_vsig;
	p->vsig = vsig;

	list_add(&p->list_entry, chg);

	वापस 0;
पूर्ण

/**
 * ice_rem_chg_tcam_ent - हटाओ a specअगरic TCAM entry from change list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @idx: the index of the TCAM entry to हटाओ
 * @chg: the list of change काष्ठाures to search
 */
अटल व्योम
ice_rem_chg_tcam_ent(काष्ठा ice_hw *hw, u16 idx, काष्ठा list_head *chg)
अणु
	काष्ठा ice_chs_chg *pos, *पंचांगp;

	list_क्रम_each_entry_safe(पंचांगp, pos, chg, list_entry)
		अगर (पंचांगp->type == ICE_TCAM_ADD && पंचांगp->tcam_idx == idx) अणु
			list_del(&पंचांगp->list_entry);
			devm_kमुक्त(ice_hw_to_dev(hw), पंचांगp);
		पूर्ण
पूर्ण

/**
 * ice_prof_tcam_ena_dis - add enable or disable TCAM change
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @enable: true to enable, false to disable
 * @vsig: the VSIG of the TCAM entry
 * @tcam: poपूर्णांकer the TCAM info काष्ठाure of the TCAM to disable
 * @chg: the change list
 *
 * This function appends an enable or disable TCAM entry in the change log
 */
अटल क्रमागत ice_status
ice_prof_tcam_ena_dis(काष्ठा ice_hw *hw, क्रमागत ice_block blk, bool enable,
		      u16 vsig, काष्ठा ice_tcam_inf *tcam,
		      काष्ठा list_head *chg)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_chs_chg *p;

	u8 vl_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	u8 dc_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFF, 0xFF, 0x00, 0x00, 0x00 पूर्ण;
	u8 nm_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;

	/* अगर disabling, मुक्त the TCAM */
	अगर (!enable) अणु
		status = ice_rel_tcam_idx(hw, blk, tcam->tcam_idx);

		/* अगर we have alपढ़ोy created a change क्रम this TCAM entry, then
		 * we need to हटाओ that entry, in order to prevent writing to
		 * a TCAM entry we no दीर्घer will have ownership of.
		 */
		ice_rem_chg_tcam_ent(hw, tcam->tcam_idx, chg);
		tcam->tcam_idx = 0;
		tcam->in_use = 0;
		वापस status;
	पूर्ण

	/* क्रम re-enabling, पुनः_स्मृतिate a TCAM */
	/* क्रम entries with empty attribute masks, allocate entry from
	 * the bottom of the TCAM table; otherwise, allocate from the
	 * top of the table in order to give it higher priority
	 */
	status = ice_alloc_tcam_ent(hw, blk, tcam->attr.mask == 0,
				    &tcam->tcam_idx);
	अगर (status)
		वापस status;

	/* add TCAM to change list */
	p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_tcam_ग_लिखो_entry(hw, blk, tcam->tcam_idx, tcam->prof_id,
				      tcam->ptg, vsig, 0, tcam->attr.flags,
				      vl_msk, dc_msk, nm_msk);
	अगर (status)
		जाओ err_ice_prof_tcam_ena_dis;

	tcam->in_use = 1;

	p->type = ICE_TCAM_ADD;
	p->add_tcam_idx = true;
	p->prof_id = tcam->prof_id;
	p->ptg = tcam->ptg;
	p->vsig = 0;
	p->tcam_idx = tcam->tcam_idx;

	/* log change */
	list_add(&p->list_entry, chg);

	वापस 0;

err_ice_prof_tcam_ena_dis:
	devm_kमुक्त(ice_hw_to_dev(hw), p);
	वापस status;
पूर्ण

/**
 * ice_adj_prof_priorities - adjust profile based on priorities
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: the VSIG क्रम which to adjust profile priorities
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_adj_prof_priorities(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig,
			काष्ठा list_head *chg)
अणु
	DECLARE_BITMAP(ptgs_used, ICE_XLT1_CNT);
	काष्ठा ice_vsig_prof *t;
	क्रमागत ice_status status;
	u16 idx;

	biपंचांगap_zero(ptgs_used, ICE_XLT1_CNT);
	idx = vsig & ICE_VSIG_IDX_M;

	/* Priority is based on the order in which the profiles are added. The
	 * newest added profile has highest priority and the oldest added
	 * profile has the lowest priority. Since the profile property list क्रम
	 * a VSIG is sorted from newest to oldest, this code traverses the list
	 * in order and enables the first of each PTG that it finds (that is not
	 * alपढ़ोy enabled); it also disables any duplicate PTGs that it finds
	 * in the older profiles (that are currently enabled).
	 */

	list_क्रम_each_entry(t, &hw->blk[blk].xlt2.vsig_tbl[idx].prop_lst,
			    list) अणु
		u16 i;

		क्रम (i = 0; i < t->tcam_count; i++) अणु
			/* Scan the priorities from newest to oldest.
			 * Make sure that the newest profiles take priority.
			 */
			अगर (test_bit(t->tcam[i].ptg, ptgs_used) &&
			    t->tcam[i].in_use) अणु
				/* need to mark this PTG as never match, as it
				 * was alपढ़ोy in use and thereक्रमe duplicate
				 * (and lower priority)
				 */
				status = ice_prof_tcam_ena_dis(hw, blk, false,
							       vsig,
							       &t->tcam[i],
							       chg);
				अगर (status)
					वापस status;
			पूर्ण अन्यथा अगर (!test_bit(t->tcam[i].ptg, ptgs_used) &&
				   !t->tcam[i].in_use) अणु
				/* need to enable this PTG, as it in not in use
				 * and not enabled (highest priority)
				 */
				status = ice_prof_tcam_ena_dis(hw, blk, true,
							       vsig,
							       &t->tcam[i],
							       chg);
				अगर (status)
					वापस status;
			पूर्ण

			/* keep track of used ptgs */
			set_bit(t->tcam[i].ptg, ptgs_used);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_add_prof_id_vsig - add profile to VSIG
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsig: the VSIG to which this profile is to be added
 * @hdl: the profile handle indicating the profile to add
 * @rev: true to add entries to the end of the list
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_add_prof_id_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsig, u64 hdl,
		     bool rev, काष्ठा list_head *chg)
अणु
	/* Masks that ignore flags */
	u8 vl_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;
	u8 dc_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0xFF, 0xFF, 0x00, 0x00, 0x00 पूर्ण;
	u8 nm_msk[ICE_TCAM_KEY_VAL_SZ] = अणु 0x00, 0x00, 0x00, 0x00, 0x00 पूर्ण;
	क्रमागत ice_status status = 0;
	काष्ठा ice_prof_map *map;
	काष्ठा ice_vsig_prof *t;
	काष्ठा ice_chs_chg *p;
	u16 vsig_idx, i;

	/* Error, अगर this VSIG alपढ़ोy has this profile */
	अगर (ice_has_prof_vsig(hw, blk, vsig, hdl))
		वापस ICE_ERR_ALREADY_EXISTS;

	/* new VSIG profile काष्ठाure */
	t = devm_kzalloc(ice_hw_to_dev(hw), माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस ICE_ERR_NO_MEMORY;

	mutex_lock(&hw->blk[blk].es.prof_map_lock);
	/* Get the details on the profile specअगरied by the handle ID */
	map = ice_search_prof_id(hw, blk, hdl);
	अगर (!map) अणु
		status = ICE_ERR_DOES_NOT_EXIST;
		जाओ err_ice_add_prof_id_vsig;
	पूर्ण

	t->profile_cookie = map->profile_cookie;
	t->prof_id = map->prof_id;
	t->tcam_count = map->ptg_cnt;

	/* create TCAM entries */
	क्रम (i = 0; i < map->ptg_cnt; i++) अणु
		u16 tcam_idx;

		/* add TCAM to change list */
		p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p), GFP_KERNEL);
		अगर (!p) अणु
			status = ICE_ERR_NO_MEMORY;
			जाओ err_ice_add_prof_id_vsig;
		पूर्ण

		/* allocate the TCAM entry index */
		/* क्रम entries with empty attribute masks, allocate entry from
		 * the bottom of the TCAM table; otherwise, allocate from the
		 * top of the table in order to give it higher priority
		 */
		status = ice_alloc_tcam_ent(hw, blk, map->attr[i].mask == 0,
					    &tcam_idx);
		अगर (status) अणु
			devm_kमुक्त(ice_hw_to_dev(hw), p);
			जाओ err_ice_add_prof_id_vsig;
		पूर्ण

		t->tcam[i].ptg = map->ptg[i];
		t->tcam[i].prof_id = map->prof_id;
		t->tcam[i].tcam_idx = tcam_idx;
		t->tcam[i].attr = map->attr[i];
		t->tcam[i].in_use = true;

		p->type = ICE_TCAM_ADD;
		p->add_tcam_idx = true;
		p->prof_id = t->tcam[i].prof_id;
		p->ptg = t->tcam[i].ptg;
		p->vsig = vsig;
		p->tcam_idx = t->tcam[i].tcam_idx;

		/* ग_लिखो the TCAM entry */
		status = ice_tcam_ग_लिखो_entry(hw, blk, t->tcam[i].tcam_idx,
					      t->tcam[i].prof_id,
					      t->tcam[i].ptg, vsig, 0, 0,
					      vl_msk, dc_msk, nm_msk);
		अगर (status) अणु
			devm_kमुक्त(ice_hw_to_dev(hw), p);
			जाओ err_ice_add_prof_id_vsig;
		पूर्ण

		/* log change */
		list_add(&p->list_entry, chg);
	पूर्ण

	/* add profile to VSIG */
	vsig_idx = vsig & ICE_VSIG_IDX_M;
	अगर (rev)
		list_add_tail(&t->list,
			      &hw->blk[blk].xlt2.vsig_tbl[vsig_idx].prop_lst);
	अन्यथा
		list_add(&t->list,
			 &hw->blk[blk].xlt2.vsig_tbl[vsig_idx].prop_lst);

	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	वापस status;

err_ice_add_prof_id_vsig:
	mutex_unlock(&hw->blk[blk].es.prof_map_lock);
	/* let caller clean up the change list */
	devm_kमुक्त(ice_hw_to_dev(hw), t);
	वापस status;
पूर्ण

/**
 * ice_create_prof_id_vsig - add a new VSIG with a single profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsi: the initial VSI that will be in VSIG
 * @hdl: the profile handle of the profile that will be added to the VSIG
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_create_prof_id_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u64 hdl,
			काष्ठा list_head *chg)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_chs_chg *p;
	u16 new_vsig;

	p = devm_kzalloc(ice_hw_to_dev(hw), माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस ICE_ERR_NO_MEMORY;

	new_vsig = ice_vsig_alloc(hw, blk);
	अगर (!new_vsig) अणु
		status = ICE_ERR_HW_TABLE;
		जाओ err_ice_create_prof_id_vsig;
	पूर्ण

	status = ice_move_vsi(hw, blk, vsi, new_vsig, chg);
	अगर (status)
		जाओ err_ice_create_prof_id_vsig;

	status = ice_add_prof_id_vsig(hw, blk, new_vsig, hdl, false, chg);
	अगर (status)
		जाओ err_ice_create_prof_id_vsig;

	p->type = ICE_VSIG_ADD;
	p->vsi = vsi;
	p->orig_vsig = ICE_DEFAULT_VSIG;
	p->vsig = new_vsig;

	list_add(&p->list_entry, chg);

	वापस 0;

err_ice_create_prof_id_vsig:
	/* let caller clean up the change list */
	devm_kमुक्त(ice_hw_to_dev(hw), p);
	वापस status;
पूर्ण

/**
 * ice_create_vsig_from_lst - create a new VSIG with a list of profiles
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsi: the initial VSI that will be in VSIG
 * @lst: the list of profile that will be added to the VSIG
 * @new_vsig: वापस of new VSIG
 * @chg: the change list
 */
अटल क्रमागत ice_status
ice_create_vsig_from_lst(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi,
			 काष्ठा list_head *lst, u16 *new_vsig,
			 काष्ठा list_head *chg)
अणु
	काष्ठा ice_vsig_prof *t;
	क्रमागत ice_status status;
	u16 vsig;

	vsig = ice_vsig_alloc(hw, blk);
	अगर (!vsig)
		वापस ICE_ERR_HW_TABLE;

	status = ice_move_vsi(hw, blk, vsi, vsig, chg);
	अगर (status)
		वापस status;

	list_क्रम_each_entry(t, lst, list) अणु
		/* Reverse the order here since we are copying the list */
		status = ice_add_prof_id_vsig(hw, blk, vsig, t->profile_cookie,
					      true, chg);
		अगर (status)
			वापस status;
	पूर्ण

	*new_vsig = vsig;

	वापस 0;
पूर्ण

/**
 * ice_find_prof_vsig - find a VSIG with a specअगरic profile handle
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @hdl: the profile handle of the profile to search क्रम
 * @vsig: वापसs the VSIG with the matching profile
 */
अटल bool
ice_find_prof_vsig(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u64 hdl, u16 *vsig)
अणु
	काष्ठा ice_vsig_prof *t;
	क्रमागत ice_status status;
	काष्ठा list_head lst;

	INIT_LIST_HEAD(&lst);

	t = kzalloc(माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस false;

	t->profile_cookie = hdl;
	list_add(&t->list, &lst);

	status = ice_find_dup_props_vsig(hw, blk, &lst, vsig);

	list_del(&t->list);
	kमुक्त(t);

	वापस !status;
पूर्ण

/**
 * ice_add_prof_id_flow - add profile flow
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsi: the VSI to enable with the profile specअगरied by ID
 * @hdl: profile handle
 *
 * Calling this function will update the hardware tables to enable the
 * profile indicated by the ID parameter क्रम the VSIs specअगरied in the VSI
 * array. Once successfully called, the flow will be enabled.
 */
क्रमागत ice_status
ice_add_prof_id_flow(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u64 hdl)
अणु
	काष्ठा ice_vsig_prof *पंचांगp1, *del1;
	काष्ठा ice_chs_chg *पंचांगp, *del;
	काष्ठा list_head जोड़_lst;
	क्रमागत ice_status status;
	काष्ठा list_head chg;
	u16 vsig;

	INIT_LIST_HEAD(&जोड़_lst);
	INIT_LIST_HEAD(&chg);

	/* Get profile */
	status = ice_get_prof(hw, blk, hdl, &chg);
	अगर (status)
		वापस status;

	/* determine अगर VSI is alपढ़ोy part of a VSIG */
	status = ice_vsig_find_vsi(hw, blk, vsi, &vsig);
	अगर (!status && vsig) अणु
		bool only_vsi;
		u16 or_vsig;
		u16 ref;

		/* found in VSIG */
		or_vsig = vsig;

		/* make sure that there is no overlap/conflict between the new
		 * अक्षरacteristics and the existing ones; we करोn't support that
		 * scenario
		 */
		अगर (ice_has_prof_vsig(hw, blk, vsig, hdl)) अणु
			status = ICE_ERR_ALREADY_EXISTS;
			जाओ err_ice_add_prof_id_flow;
		पूर्ण

		/* last VSI in the VSIG? */
		status = ice_vsig_get_ref(hw, blk, vsig, &ref);
		अगर (status)
			जाओ err_ice_add_prof_id_flow;
		only_vsi = (ref == 1);

		/* create a जोड़ of the current profiles and the one being
		 * added
		 */
		status = ice_get_profs_vsig(hw, blk, vsig, &जोड़_lst);
		अगर (status)
			जाओ err_ice_add_prof_id_flow;

		status = ice_add_prof_to_lst(hw, blk, &जोड़_lst, hdl);
		अगर (status)
			जाओ err_ice_add_prof_id_flow;

		/* search क्रम an existing VSIG with an exact अक्षरc match */
		status = ice_find_dup_props_vsig(hw, blk, &जोड़_lst, &vsig);
		अगर (!status) अणु
			/* move VSI to the VSIG that matches */
			status = ice_move_vsi(hw, blk, vsi, vsig, &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;

			/* VSI has been moved out of or_vsig. If the or_vsig had
			 * only that VSI it is now empty and can be हटाओd.
			 */
			अगर (only_vsi) अणु
				status = ice_rem_vsig(hw, blk, or_vsig, &chg);
				अगर (status)
					जाओ err_ice_add_prof_id_flow;
			पूर्ण
		पूर्ण अन्यथा अगर (only_vsi) अणु
			/* If the original VSIG only contains one VSI, then it
			 * will be the requesting VSI. In this हाल the VSI is
			 * not sharing entries and we can simply add the new
			 * profile to the VSIG.
			 */
			status = ice_add_prof_id_vsig(hw, blk, vsig, hdl, false,
						      &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;

			/* Adjust priorities */
			status = ice_adj_prof_priorities(hw, blk, vsig, &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;
		पूर्ण अन्यथा अणु
			/* No match, so we need a new VSIG */
			status = ice_create_vsig_from_lst(hw, blk, vsi,
							  &जोड़_lst, &vsig,
							  &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;

			/* Adjust priorities */
			status = ice_adj_prof_priorities(hw, blk, vsig, &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* need to find or add a VSIG */
		/* search क्रम an existing VSIG with an exact अक्षरc match */
		अगर (ice_find_prof_vsig(hw, blk, hdl, &vsig)) अणु
			/* found an exact match */
			/* add or move VSI to the VSIG that matches */
			status = ice_move_vsi(hw, blk, vsi, vsig, &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;
		पूर्ण अन्यथा अणु
			/* we did not find an exact match */
			/* we need to add a VSIG */
			status = ice_create_prof_id_vsig(hw, blk, vsi, hdl,
							 &chg);
			अगर (status)
				जाओ err_ice_add_prof_id_flow;
		पूर्ण
	पूर्ण

	/* update hardware */
	अगर (!status)
		status = ice_upd_prof_hw(hw, blk, &chg);

err_ice_add_prof_id_flow:
	list_क्रम_each_entry_safe(del, पंचांगp, &chg, list_entry) अणु
		list_del(&del->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), del);
	पूर्ण

	list_क्रम_each_entry_safe(del1, पंचांगp1, &जोड़_lst, list) अणु
		list_del(&del1->list);
		devm_kमुक्त(ice_hw_to_dev(hw), del1);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_rem_prof_from_list - हटाओ a profile from list
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @lst: list to हटाओ the profile from
 * @hdl: the profile handle indicating the profile to हटाओ
 */
अटल क्रमागत ice_status
ice_rem_prof_from_list(काष्ठा ice_hw *hw, काष्ठा list_head *lst, u64 hdl)
अणु
	काष्ठा ice_vsig_prof *ent, *पंचांगp;

	list_क्रम_each_entry_safe(ent, पंचांगp, lst, list)
		अगर (ent->profile_cookie == hdl) अणु
			list_del(&ent->list);
			devm_kमुक्त(ice_hw_to_dev(hw), ent);
			वापस 0;
		पूर्ण

	वापस ICE_ERR_DOES_NOT_EXIST;
पूर्ण

/**
 * ice_rem_prof_id_flow - हटाओ flow
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @blk: hardware block
 * @vsi: the VSI from which to हटाओ the profile specअगरied by ID
 * @hdl: profile tracking handle
 *
 * Calling this function will update the hardware tables to हटाओ the
 * profile indicated by the ID parameter क्रम the VSIs specअगरied in the VSI
 * array. Once successfully called, the flow will be disabled.
 */
क्रमागत ice_status
ice_rem_prof_id_flow(काष्ठा ice_hw *hw, क्रमागत ice_block blk, u16 vsi, u64 hdl)
अणु
	काष्ठा ice_vsig_prof *पंचांगp1, *del1;
	काष्ठा ice_chs_chg *पंचांगp, *del;
	काष्ठा list_head chg, copy;
	क्रमागत ice_status status;
	u16 vsig;

	INIT_LIST_HEAD(&copy);
	INIT_LIST_HEAD(&chg);

	/* determine अगर VSI is alपढ़ोy part of a VSIG */
	status = ice_vsig_find_vsi(hw, blk, vsi, &vsig);
	अगर (!status && vsig) अणु
		bool last_profile;
		bool only_vsi;
		u16 ref;

		/* found in VSIG */
		last_profile = ice_vsig_prof_id_count(hw, blk, vsig) == 1;
		status = ice_vsig_get_ref(hw, blk, vsig, &ref);
		अगर (status)
			जाओ err_ice_rem_prof_id_flow;
		only_vsi = (ref == 1);

		अगर (only_vsi) अणु
			/* If the original VSIG only contains one reference,
			 * which will be the requesting VSI, then the VSI is not
			 * sharing entries and we can simply हटाओ the specअगरic
			 * अक्षरacteristics from the VSIG.
			 */

			अगर (last_profile) अणु
				/* If there are no profiles left क्रम this VSIG,
				 * then simply हटाओ the VSIG.
				 */
				status = ice_rem_vsig(hw, blk, vsig, &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;
			पूर्ण अन्यथा अणु
				status = ice_rem_prof_id_vsig(hw, blk, vsig,
							      hdl, &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;

				/* Adjust priorities */
				status = ice_adj_prof_priorities(hw, blk, vsig,
								 &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;
			पूर्ण

		पूर्ण अन्यथा अणु
			/* Make a copy of the VSIG's list of Profiles */
			status = ice_get_profs_vsig(hw, blk, vsig, &copy);
			अगर (status)
				जाओ err_ice_rem_prof_id_flow;

			/* Remove specअगरied profile entry from the list */
			status = ice_rem_prof_from_list(hw, &copy, hdl);
			अगर (status)
				जाओ err_ice_rem_prof_id_flow;

			अगर (list_empty(&copy)) अणु
				status = ice_move_vsi(hw, blk, vsi,
						      ICE_DEFAULT_VSIG, &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;

			पूर्ण अन्यथा अगर (!ice_find_dup_props_vsig(hw, blk, &copy,
							    &vsig)) अणु
				/* found an exact match */
				/* add or move VSI to the VSIG that matches */
				/* Search क्रम a VSIG with a matching profile
				 * list
				 */

				/* Found match, move VSI to the matching VSIG */
				status = ice_move_vsi(hw, blk, vsi, vsig, &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;
			पूर्ण अन्यथा अणु
				/* since no existing VSIG supports this
				 * अक्षरacteristic pattern, we need to create a
				 * new VSIG and TCAM entries
				 */
				status = ice_create_vsig_from_lst(hw, blk, vsi,
								  &copy, &vsig,
								  &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;

				/* Adjust priorities */
				status = ice_adj_prof_priorities(hw, blk, vsig,
								 &chg);
				अगर (status)
					जाओ err_ice_rem_prof_id_flow;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		status = ICE_ERR_DOES_NOT_EXIST;
	पूर्ण

	/* update hardware tables */
	अगर (!status)
		status = ice_upd_prof_hw(hw, blk, &chg);

err_ice_rem_prof_id_flow:
	list_क्रम_each_entry_safe(del, पंचांगp, &chg, list_entry) अणु
		list_del(&del->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), del);
	पूर्ण

	list_क्रम_each_entry_safe(del1, पंचांगp1, &copy, list) अणु
		list_del(&del1->list);
		devm_kमुक्त(ice_hw_to_dev(hw), del1);
	पूर्ण

	वापस status;
पूर्ण
