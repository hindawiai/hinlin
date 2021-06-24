<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "e1000.h"

/**
 *  e1000_calculate_checksum - Calculate checksum क्रम buffer
 *  @buffer: poपूर्णांकer to EEPROM
 *  @length: size of EEPROM to calculate a checksum क्रम
 *
 *  Calculates the checksum क्रम some buffer on a specअगरied length.  The
 *  checksum calculated is वापसed.
 **/
अटल u8 e1000_calculate_checksum(u8 *buffer, u32 length)
अणु
	u32 i;
	u8 sum = 0;

	अगर (!buffer)
		वापस 0;

	क्रम (i = 0; i < length; i++)
		sum += buffer[i];

	वापस (u8)(0 - sum);
पूर्ण

/**
 *  e1000_mng_enable_host_अगर - Checks host पूर्णांकerface is enabled
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Returns 0 upon success, अन्यथा -E1000_ERR_HOST_INTERFACE_COMMAND
 *
 *  This function checks whether the HOST IF is enabled क्रम command operation
 *  and also checks whether the previous command is completed.  It busy रुकोs
 *  in हाल of previous command is not completed.
 **/
अटल s32 e1000_mng_enable_host_अगर(काष्ठा e1000_hw *hw)
अणु
	u32 hicr;
	u8 i;

	अगर (!hw->mac.arc_subप्रणाली_valid) अणु
		e_dbg("ARC subsystem not valid.\n");
		वापस -E1000_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण

	/* Check that the host पूर्णांकerface is enabled. */
	hicr = er32(HICR);
	अगर (!(hicr & E1000_HICR_EN)) अणु
		e_dbg("E1000_HOST_EN bit disabled.\n");
		वापस -E1000_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण
	/* check the previous command is completed */
	क्रम (i = 0; i < E1000_MNG_DHCP_COMMAND_TIMEOUT; i++) अणु
		hicr = er32(HICR);
		अगर (!(hicr & E1000_HICR_C))
			अवरोध;
		mdelay(1);
	पूर्ण

	अगर (i == E1000_MNG_DHCP_COMMAND_TIMEOUT) अणु
		e_dbg("Previous command timeout failed.\n");
		वापस -E1000_ERR_HOST_INTERFACE_COMMAND;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_check_mng_mode_generic - Generic check management mode
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Reads the firmware semaphore रेजिस्टर and वापसs true (>0) अगर
 *  manageability is enabled, अन्यथा false (0).
 **/
bool e1000e_check_mng_mode_generic(काष्ठा e1000_hw *hw)
अणु
	u32 fwsm = er32(FWSM);

	वापस (fwsm & E1000_FWSM_MODE_MASK) ==
	    (E1000_MNG_IAMT_MODE << E1000_FWSM_MODE_SHIFT);
पूर्ण

/**
 *  e1000e_enable_tx_pkt_filtering - Enable packet filtering on Tx
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Enables packet filtering on transmit packets अगर manageability is enabled
 *  and host पूर्णांकerface is enabled.
 **/
bool e1000e_enable_tx_pkt_filtering(काष्ठा e1000_hw *hw)
अणु
	काष्ठा e1000_host_mng_dhcp_cookie *hdr = &hw->mng_cookie;
	u32 *buffer = (u32 *)&hw->mng_cookie;
	u32 offset;
	s32 ret_val, hdr_csum, csum;
	u8 i, len;

	hw->mac.tx_pkt_filtering = true;

	/* No manageability, no filtering */
	अगर (!hw->mac.ops.check_mng_mode(hw)) अणु
		hw->mac.tx_pkt_filtering = false;
		वापस hw->mac.tx_pkt_filtering;
	पूर्ण

	/* If we can't पढ़ो from the host पूर्णांकerface क्रम whatever
	 * reason, disable filtering.
	 */
	ret_val = e1000_mng_enable_host_अगर(hw);
	अगर (ret_val) अणु
		hw->mac.tx_pkt_filtering = false;
		वापस hw->mac.tx_pkt_filtering;
	पूर्ण

	/* Read in the header.  Length and offset are in dwords. */
	len = E1000_MNG_DHCP_COOKIE_LENGTH >> 2;
	offset = E1000_MNG_DHCP_COOKIE_OFFSET >> 2;
	क्रम (i = 0; i < len; i++)
		*(buffer + i) = E1000_READ_REG_ARRAY(hw, E1000_HOST_IF,
						     offset + i);
	hdr_csum = hdr->checksum;
	hdr->checksum = 0;
	csum = e1000_calculate_checksum((u8 *)hdr,
					E1000_MNG_DHCP_COOKIE_LENGTH);
	/* If either the checksums or signature करोn't match, then
	 * the cookie area isn't considered valid, in which हाल we
	 * take the safe route of assuming Tx filtering is enabled.
	 */
	अगर ((hdr_csum != csum) || (hdr->signature != E1000_IAMT_SIGNATURE)) अणु
		hw->mac.tx_pkt_filtering = true;
		वापस hw->mac.tx_pkt_filtering;
	पूर्ण

	/* Cookie area is valid, make the final check क्रम filtering. */
	अगर (!(hdr->status & E1000_MNG_DHCP_COOKIE_STATUS_PARSING))
		hw->mac.tx_pkt_filtering = false;

	वापस hw->mac.tx_pkt_filtering;
पूर्ण

/**
 *  e1000_mng_ग_लिखो_cmd_header - Writes manageability command header
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @hdr: poपूर्णांकer to the host पूर्णांकerface command header
 *
 *  Writes the command header after करोes the checksum calculation.
 **/
अटल s32 e1000_mng_ग_लिखो_cmd_header(काष्ठा e1000_hw *hw,
				      काष्ठा e1000_host_mng_command_header *hdr)
अणु
	u16 i, length = माप(काष्ठा e1000_host_mng_command_header);

	/* Write the whole command header काष्ठाure with new checksum. */

	hdr->checksum = e1000_calculate_checksum((u8 *)hdr, length);

	length >>= 2;
	/* Write the relevant command block पूर्णांकo the ram area. */
	क्रम (i = 0; i < length; i++) अणु
		E1000_WRITE_REG_ARRAY(hw, E1000_HOST_IF, i, *((u32 *)hdr + i));
		e1e_flush();
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000_mng_host_अगर_ग_लिखो - Write to the manageability host पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @buffer: poपूर्णांकer to the host पूर्णांकerface buffer
 *  @length: size of the buffer
 *  @offset: location in the buffer to ग_लिखो to
 *  @sum: sum of the data (not checksum)
 *
 *  This function ग_लिखोs the buffer content at the offset given on the host अगर.
 *  It also करोes alignment considerations to करो the ग_लिखोs in most efficient
 *  way.  Also fills up the sum of the buffer in *buffer parameter.
 **/
अटल s32 e1000_mng_host_अगर_ग_लिखो(काष्ठा e1000_hw *hw, u8 *buffer,
				   u16 length, u16 offset, u8 *sum)
अणु
	u8 *पंचांगp;
	u8 *bufptr = buffer;
	u32 data = 0;
	u16 reमुख्यing, i, j, prev_bytes;

	/* sum = only sum of the data and it is not checksum */

	अगर (length == 0 || offset + length > E1000_HI_MAX_MNG_DATA_LENGTH)
		वापस -E1000_ERR_PARAM;

	पंचांगp = (u8 *)&data;
	prev_bytes = offset & 0x3;
	offset >>= 2;

	अगर (prev_bytes) अणु
		data = E1000_READ_REG_ARRAY(hw, E1000_HOST_IF, offset);
		क्रम (j = prev_bytes; j < माप(u32); j++) अणु
			*(पंचांगp + j) = *bufptr++;
			*sum += *(पंचांगp + j);
		पूर्ण
		E1000_WRITE_REG_ARRAY(hw, E1000_HOST_IF, offset, data);
		length -= j - prev_bytes;
		offset++;
	पूर्ण

	reमुख्यing = length & 0x3;
	length -= reमुख्यing;

	/* Calculate length in DWORDs */
	length >>= 2;

	/* The device driver ग_लिखोs the relevant command block पूर्णांकo the
	 * ram area.
	 */
	क्रम (i = 0; i < length; i++) अणु
		क्रम (j = 0; j < माप(u32); j++) अणु
			*(पंचांगp + j) = *bufptr++;
			*sum += *(पंचांगp + j);
		पूर्ण

		E1000_WRITE_REG_ARRAY(hw, E1000_HOST_IF, offset + i, data);
	पूर्ण
	अगर (reमुख्यing) अणु
		क्रम (j = 0; j < माप(u32); j++) अणु
			अगर (j < reमुख्यing)
				*(पंचांगp + j) = *bufptr++;
			अन्यथा
				*(पंचांगp + j) = 0;

			*sum += *(पंचांगp + j);
		पूर्ण
		E1000_WRITE_REG_ARRAY(hw, E1000_HOST_IF, offset + i, data);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *  e1000e_mng_ग_लिखो_dhcp_info - Writes DHCP info to host पूर्णांकerface
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *  @buffer: poपूर्णांकer to the host पूर्णांकerface
 *  @length: size of the buffer
 *
 *  Writes the DHCP inक्रमmation to the host पूर्णांकerface.
 **/
s32 e1000e_mng_ग_लिखो_dhcp_info(काष्ठा e1000_hw *hw, u8 *buffer, u16 length)
अणु
	काष्ठा e1000_host_mng_command_header hdr;
	s32 ret_val;
	u32 hicr;

	hdr.command_id = E1000_MNG_DHCP_TX_PAYLOAD_CMD;
	hdr.command_length = length;
	hdr.reserved1 = 0;
	hdr.reserved2 = 0;
	hdr.checksum = 0;

	/* Enable the host पूर्णांकerface */
	ret_val = e1000_mng_enable_host_अगर(hw);
	अगर (ret_val)
		वापस ret_val;

	/* Populate the host पूर्णांकerface with the contents of "buffer". */
	ret_val = e1000_mng_host_अगर_ग_लिखो(hw, buffer, length,
					  माप(hdr), &(hdr.checksum));
	अगर (ret_val)
		वापस ret_val;

	/* Write the manageability command header */
	ret_val = e1000_mng_ग_लिखो_cmd_header(hw, &hdr);
	अगर (ret_val)
		वापस ret_val;

	/* Tell the ARC a new command is pending. */
	hicr = er32(HICR);
	ew32(HICR, hicr | E1000_HICR_C);

	वापस 0;
पूर्ण

/**
 *  e1000e_enable_mng_pass_thru - Check अगर management passthrough is needed
 *  @hw: poपूर्णांकer to the HW काष्ठाure
 *
 *  Verअगरies the hardware needs to leave पूर्णांकerface enabled so that frames can
 *  be directed to and from the management पूर्णांकerface.
 **/
bool e1000e_enable_mng_pass_thru(काष्ठा e1000_hw *hw)
अणु
	u32 manc;
	u32 fwsm, factps;

	manc = er32(MANC);

	अगर (!(manc & E1000_MANC_RCV_TCO_EN))
		वापस false;

	अगर (hw->mac.has_fwsm) अणु
		fwsm = er32(FWSM);
		factps = er32(FACTPS);

		अगर (!(factps & E1000_FACTPS_MNGCG) &&
		    ((fwsm & E1000_FWSM_MODE_MASK) ==
		     (e1000_mng_mode_pt << E1000_FWSM_MODE_SHIFT)))
			वापस true;
	पूर्ण अन्यथा अगर ((hw->mac.type == e1000_82574) ||
		   (hw->mac.type == e1000_82583)) अणु
		u16 data;
		s32 ret_val;

		factps = er32(FACTPS);
		ret_val = e1000_पढ़ो_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &data);
		अगर (ret_val)
			वापस false;

		अगर (!(factps & E1000_FACTPS_MNGCG) &&
		    ((data & E1000_NVM_INIT_CTRL2_MNGM) ==
		     (e1000_mng_mode_pt << 13)))
			वापस true;
	पूर्ण अन्यथा अगर ((manc & E1000_MANC_SMBUS_EN) &&
		   !(manc & E1000_MANC_ASF_EN)) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण
