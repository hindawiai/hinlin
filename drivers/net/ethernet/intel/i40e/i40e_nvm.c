<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2013 - 2018 Intel Corporation. */

#समावेश "i40e_prototype.h"

/**
 * i40e_init_nvm - Initialize NVM function poपूर्णांकers
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Setup the function poपूर्णांकers and the NVM info काष्ठाure. Should be called
 * once per NVM initialization, e.g. inside the i40e_init_shared_code().
 * Please notice that the NVM term is used here (& in all methods covered
 * in this file) as an equivalent of the FLASH part mapped पूर्णांकo the SR.
 * We are accessing FLASH always thru the Shaकरोw RAM.
 **/
i40e_status i40e_init_nvm(काष्ठा i40e_hw *hw)
अणु
	काष्ठा i40e_nvm_info *nvm = &hw->nvm;
	i40e_status ret_code = 0;
	u32 fla, gens;
	u8 sr_size;

	/* The SR size is stored regardless of the nvm programming mode
	 * as the blank mode may be used in the factory line.
	 */
	gens = rd32(hw, I40E_GLNVM_GENS);
	sr_size = ((gens & I40E_GLNVM_GENS_SR_SIZE_MASK) >>
			   I40E_GLNVM_GENS_SR_SIZE_SHIFT);
	/* Switching to words (sr_size contains घातer of 2KB) */
	nvm->sr_size = BIT(sr_size) * I40E_SR_WORDS_IN_1KB;

	/* Check अगर we are in the normal or blank NVM programming mode */
	fla = rd32(hw, I40E_GLNVM_FLA);
	अगर (fla & I40E_GLNVM_FLA_LOCKED_MASK) अणु /* Normal programming mode */
		/* Max NVM समयout */
		nvm->समयout = I40E_MAX_NVM_TIMEOUT;
		nvm->blank_nvm_mode = false;
	पूर्ण अन्यथा अणु /* Blank programming mode */
		nvm->blank_nvm_mode = true;
		ret_code = I40E_ERR_NVM_BLANK_MODE;
		i40e_debug(hw, I40E_DEBUG_NVM, "NVM init error: unsupported blank mode.\n");
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 * i40e_acquire_nvm - Generic request क्रम acquiring the NVM ownership
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @access: NVM access type (पढ़ो or ग_लिखो)
 *
 * This function will request NVM ownership क्रम पढ़ोing
 * via the proper Admin Command.
 **/
i40e_status i40e_acquire_nvm(काष्ठा i40e_hw *hw,
				       क्रमागत i40e_aq_resource_access_type access)
अणु
	i40e_status ret_code = 0;
	u64 gसमय, समयout;
	u64 समय_left = 0;

	अगर (hw->nvm.blank_nvm_mode)
		जाओ i40e_i40e_acquire_nvm_निकास;

	ret_code = i40e_aq_request_resource(hw, I40E_NVM_RESOURCE_ID, access,
					    0, &समय_left, शून्य);
	/* Reading the Global Device Timer */
	gसमय = rd32(hw, I40E_GLVFGEN_TIMER);

	/* Store the समयout */
	hw->nvm.hw_semaphore_समयout = I40E_MS_TO_GTIME(समय_left) + gसमय;

	अगर (ret_code)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM acquire type %d failed time_left=%llu ret=%d aq_err=%d\n",
			   access, समय_left, ret_code, hw->aq.asq_last_status);

	अगर (ret_code && समय_left) अणु
		/* Poll until the current NVM owner समयouts */
		समयout = I40E_MS_TO_GTIME(I40E_MAX_NVM_TIMEOUT) + gसमय;
		जबतक ((gसमय < समयout) && समय_left) अणु
			usleep_range(10000, 20000);
			gसमय = rd32(hw, I40E_GLVFGEN_TIMER);
			ret_code = i40e_aq_request_resource(hw,
							I40E_NVM_RESOURCE_ID,
							access, 0, &समय_left,
							शून्य);
			अगर (!ret_code) अणु
				hw->nvm.hw_semaphore_समयout =
					    I40E_MS_TO_GTIME(समय_left) + gसमय;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ret_code) अणु
			hw->nvm.hw_semaphore_समयout = 0;
			i40e_debug(hw, I40E_DEBUG_NVM,
				   "NVM acquire timed out, wait %llu ms before trying again. status=%d aq_err=%d\n",
				   समय_left, ret_code, hw->aq.asq_last_status);
		पूर्ण
	पूर्ण

i40e_i40e_acquire_nvm_निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_release_nvm - Generic request क्रम releasing the NVM ownership
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * This function will release NVM resource via the proper Admin Command.
 **/
व्योम i40e_release_nvm(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = I40E_SUCCESS;
	u32 total_delay = 0;

	अगर (hw->nvm.blank_nvm_mode)
		वापस;

	ret_code = i40e_aq_release_resource(hw, I40E_NVM_RESOURCE_ID, 0, शून्य);

	/* there are some rare हालs when trying to release the resource
	 * results in an admin Q समयout, so handle them correctly
	 */
	जबतक ((ret_code == I40E_ERR_ADMIN_QUEUE_TIMEOUT) &&
	       (total_delay < hw->aq.asq_cmd_समयout)) अणु
		usleep_range(1000, 2000);
		ret_code = i40e_aq_release_resource(hw,
						    I40E_NVM_RESOURCE_ID,
						    0, शून्य);
		total_delay++;
	पूर्ण
पूर्ण

/**
 * i40e_poll_sr_srctl_करोne_bit - Polls the GLNVM_SRCTL करोne bit
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * Polls the SRCTL Shaकरोw RAM रेजिस्टर करोne bit.
 **/
अटल i40e_status i40e_poll_sr_srctl_करोne_bit(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code = I40E_ERR_TIMEOUT;
	u32 srctl, रुको_cnt;

	/* Poll the I40E_GLNVM_SRCTL until the करोne bit is set */
	क्रम (रुको_cnt = 0; रुको_cnt < I40E_SRRD_SRCTL_ATTEMPTS; रुको_cnt++) अणु
		srctl = rd32(hw, I40E_GLNVM_SRCTL);
		अगर (srctl & I40E_GLNVM_SRCTL_DONE_MASK) अणु
			ret_code = 0;
			अवरोध;
		पूर्ण
		udelay(5);
	पूर्ण
	अगर (ret_code == I40E_ERR_TIMEOUT)
		i40e_debug(hw, I40E_DEBUG_NVM, "Done bit in GLNVM_SRCTL not set");
	वापस ret_code;
पूर्ण

/**
 * i40e_पढ़ो_nvm_word_srctl - Reads Shaकरोw RAM via SRCTL रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM using the GLNVM_SRCTL रेजिस्टर.
 **/
अटल i40e_status i40e_पढ़ो_nvm_word_srctl(काष्ठा i40e_hw *hw, u16 offset,
					    u16 *data)
अणु
	i40e_status ret_code = I40E_ERR_TIMEOUT;
	u32 sr_reg;

	अगर (offset >= hw->nvm.sr_size) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: offset %d beyond Shadow RAM limit %d\n",
			   offset, hw->nvm.sr_size);
		ret_code = I40E_ERR_PARAM;
		जाओ पढ़ो_nvm_निकास;
	पूर्ण

	/* Poll the करोne bit first */
	ret_code = i40e_poll_sr_srctl_करोne_bit(hw);
	अगर (!ret_code) अणु
		/* Write the address and start पढ़ोing */
		sr_reg = ((u32)offset << I40E_GLNVM_SRCTL_ADDR_SHIFT) |
			 BIT(I40E_GLNVM_SRCTL_START_SHIFT);
		wr32(hw, I40E_GLNVM_SRCTL, sr_reg);

		/* Poll I40E_GLNVM_SRCTL until the करोne bit is set */
		ret_code = i40e_poll_sr_srctl_करोne_bit(hw);
		अगर (!ret_code) अणु
			sr_reg = rd32(hw, I40E_GLNVM_SRDATA);
			*data = (u16)((sr_reg &
				       I40E_GLNVM_SRDATA_RDDATA_MASK)
				    >> I40E_GLNVM_SRDATA_RDDATA_SHIFT);
		पूर्ण
	पूर्ण
	अगर (ret_code)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM read error: Couldn't access Shadow RAM address: 0x%x\n",
			   offset);

पढ़ो_nvm_निकास:
	वापस ret_code;
पूर्ण

/**
 * i40e_पढ़ो_nvm_aq - Read Shaकरोw RAM.
 * @hw: poपूर्णांकer to the HW काष्ठाure.
 * @module_poपूर्णांकer: module poपूर्णांकer location in words from the NVM beginning
 * @offset: offset in words from module start
 * @words: number of words to ग_लिखो
 * @data: buffer with words to ग_लिखो to the Shaकरोw RAM
 * @last_command: tells the AdminQ that this is the last command
 *
 * Writes a 16 bit words buffer to the Shaकरोw RAM using the admin command.
 **/
अटल i40e_status i40e_पढ़ो_nvm_aq(काष्ठा i40e_hw *hw,
				    u8 module_poपूर्णांकer, u32 offset,
				    u16 words, व्योम *data,
				    bool last_command)
अणु
	i40e_status ret_code = I40E_ERR_NVM;
	काष्ठा i40e_asq_cmd_details cmd_details;

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	/* Here we are checking the SR limit only क्रम the flat memory model.
	 * We cannot करो it क्रम the module-based model, as we did not acquire
	 * the NVM resource yet (we cannot get the module poपूर्णांकer value).
	 * Firmware will check the module-based model.
	 */
	अगर ((offset + words) > hw->nvm.sr_size)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write error: offset %d beyond Shadow RAM limit %d\n",
			   (offset + words), hw->nvm.sr_size);
	अन्यथा अगर (words > I40E_SR_SECTOR_SIZE_IN_WORDS)
		/* We can ग_लिखो only up to 4KB (one sector), in one AQ ग_लिखो */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write fail error: tried to write %d words, limit is %d.\n",
			   words, I40E_SR_SECTOR_SIZE_IN_WORDS);
	अन्यथा अगर (((offset + (words - 1)) / I40E_SR_SECTOR_SIZE_IN_WORDS)
		 != (offset / I40E_SR_SECTOR_SIZE_IN_WORDS))
		/* A single ग_लिखो cannot spपढ़ो over two sectors */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write error: cannot spread over two sectors in a single write offset=%d words=%d\n",
			   offset, words);
	अन्यथा
		ret_code = i40e_aq_पढ़ो_nvm(hw, module_poपूर्णांकer,
					    2 * offset,  /*bytes*/
					    2 * words,   /*bytes*/
					    data, last_command, &cmd_details);

	वापस ret_code;
पूर्ण

/**
 * i40e_पढ़ो_nvm_word_aq - Reads Shaकरोw RAM via AQ
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM using the AdminQ
 **/
अटल i40e_status i40e_पढ़ो_nvm_word_aq(काष्ठा i40e_hw *hw, u16 offset,
					 u16 *data)
अणु
	i40e_status ret_code = I40E_ERR_TIMEOUT;

	ret_code = i40e_पढ़ो_nvm_aq(hw, 0x0, offset, 1, data, true);
	*data = le16_to_cpu(*(__le16 *)data);

	वापस ret_code;
पूर्ण

/**
 * __i40e_पढ़ो_nvm_word - Reads nvm word, assumes caller करोes the locking
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM.
 *
 * Do not use this function except in हालs where the nvm lock is alपढ़ोy
 * taken via i40e_acquire_nvm().
 **/
अटल i40e_status __i40e_पढ़ो_nvm_word(काष्ठा i40e_hw *hw,
					u16 offset, u16 *data)
अणु
	अगर (hw->flags & I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE)
		वापस i40e_पढ़ो_nvm_word_aq(hw, offset, data);

	वापस i40e_पढ़ो_nvm_word_srctl(hw, offset, data);
पूर्ण

/**
 * i40e_पढ़ो_nvm_word - Reads nvm word and acquire lock अगर necessary
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF)
 * @data: word पढ़ो from the Shaकरोw RAM
 *
 * Reads one 16 bit word from the Shaकरोw RAM.
 **/
i40e_status i40e_पढ़ो_nvm_word(काष्ठा i40e_hw *hw, u16 offset,
			       u16 *data)
अणु
	i40e_status ret_code = 0;

	अगर (hw->flags & I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK)
		ret_code = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret_code)
		वापस ret_code;

	ret_code = __i40e_पढ़ो_nvm_word(hw, offset, data);

	अगर (hw->flags & I40E_HW_FLAG_NVM_READ_REQUIRES_LOCK)
		i40e_release_nvm(hw);

	वापस ret_code;
पूर्ण

/**
 * i40e_पढ़ो_nvm_module_data - Reads NVM Buffer to specअगरied memory location
 * @hw: Poपूर्णांकer to the HW काष्ठाure
 * @module_ptr: Poपूर्णांकer to module in words with respect to NVM beginning
 * @module_offset: Offset in words from module start
 * @data_offset: Offset in words from पढ़ोing data area start
 * @words_data_size: Words to पढ़ो from NVM
 * @data_ptr: Poपूर्णांकer to memory location where resulting buffer will be stored
 **/
क्रमागत i40e_status_code i40e_पढ़ो_nvm_module_data(काष्ठा i40e_hw *hw,
						u8 module_ptr,
						u16 module_offset,
						u16 data_offset,
						u16 words_data_size,
						u16 *data_ptr)
अणु
	i40e_status status;
	u16 specअगरic_ptr = 0;
	u16 ptr_value = 0;
	u32 offset = 0;

	अगर (module_ptr != 0) अणु
		status = i40e_पढ़ो_nvm_word(hw, module_ptr, &ptr_value);
		अगर (status) अणु
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Reading nvm word failed.Error code: %d.\n",
				   status);
			वापस I40E_ERR_NVM;
		पूर्ण
	पूर्ण
#घोषणा I40E_NVM_INVALID_PTR_VAL 0x7FFF
#घोषणा I40E_NVM_INVALID_VAL 0xFFFF

	/* Poपूर्णांकer not initialized */
	अगर (ptr_value == I40E_NVM_INVALID_PTR_VAL ||
	    ptr_value == I40E_NVM_INVALID_VAL) अणु
		i40e_debug(hw, I40E_DEBUG_ALL, "Pointer not initialized.\n");
		वापस I40E_ERR_BAD_PTR;
	पूर्ण

	/* Check whether the module is in SR mapped area or outside */
	अगर (ptr_value & I40E_PTR_TYPE) अणु
		/* Poपूर्णांकer poपूर्णांकs outside of the Shared RAM mapped area */
		i40e_debug(hw, I40E_DEBUG_ALL,
			   "Reading nvm data failed. Pointer points outside of the Shared RAM mapped area.\n");

		वापस I40E_ERR_PARAM;
	पूर्ण अन्यथा अणु
		/* Read from the Shaकरोw RAM */

		status = i40e_पढ़ो_nvm_word(hw, ptr_value + module_offset,
					    &specअगरic_ptr);
		अगर (status) अणु
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Reading nvm word failed.Error code: %d.\n",
				   status);
			वापस I40E_ERR_NVM;
		पूर्ण

		offset = ptr_value + module_offset + specअगरic_ptr +
			data_offset;

		status = i40e_पढ़ो_nvm_buffer(hw, offset, &words_data_size,
					      data_ptr);
		अगर (status) अणु
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "Reading nvm buffer failed.Error code: %d.\n",
				   status);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_पढ़ो_nvm_buffer_srctl - Reads Shaकरोw RAM buffer via SRCTL रेजिस्टर
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF).
 * @words: (in) number of words to पढ़ो; (out) number of words actually पढ़ो
 * @data: words पढ़ो from the Shaकरोw RAM
 *
 * Reads 16 bit words (data buffer) from the SR using the i40e_पढ़ो_nvm_srrd()
 * method. The buffer पढ़ो is preceded by the NVM ownership take
 * and followed by the release.
 **/
अटल i40e_status i40e_पढ़ो_nvm_buffer_srctl(काष्ठा i40e_hw *hw, u16 offset,
					      u16 *words, u16 *data)
अणु
	i40e_status ret_code = 0;
	u16 index, word;

	/* Loop thru the selected region */
	क्रम (word = 0; word < *words; word++) अणु
		index = offset + word;
		ret_code = i40e_पढ़ो_nvm_word_srctl(hw, index, &data[word]);
		अगर (ret_code)
			अवरोध;
	पूर्ण

	/* Update the number of words पढ़ो from the Shaकरोw RAM */
	*words = word;

	वापस ret_code;
पूर्ण

/**
 * i40e_पढ़ो_nvm_buffer_aq - Reads Shaकरोw RAM buffer via AQ
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF).
 * @words: (in) number of words to पढ़ो; (out) number of words actually पढ़ो
 * @data: words पढ़ो from the Shaकरोw RAM
 *
 * Reads 16 bit words (data buffer) from the SR using the i40e_पढ़ो_nvm_aq()
 * method. The buffer पढ़ो is preceded by the NVM ownership take
 * and followed by the release.
 **/
अटल i40e_status i40e_पढ़ो_nvm_buffer_aq(काष्ठा i40e_hw *hw, u16 offset,
					   u16 *words, u16 *data)
अणु
	i40e_status ret_code;
	u16 पढ़ो_size;
	bool last_cmd = false;
	u16 words_पढ़ो = 0;
	u16 i = 0;

	करो अणु
		/* Calculate number of bytes we should पढ़ो in this step.
		 * FVL AQ करो not allow to पढ़ो more than one page at a समय or
		 * to cross page boundaries.
		 */
		अगर (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)
			पढ़ो_size = min(*words,
					(u16)(I40E_SR_SECTOR_SIZE_IN_WORDS -
				      (offset % I40E_SR_SECTOR_SIZE_IN_WORDS)));
		अन्यथा
			पढ़ो_size = min((*words - words_पढ़ो),
					I40E_SR_SECTOR_SIZE_IN_WORDS);

		/* Check अगर this is last command, अगर so set proper flag */
		अगर ((words_पढ़ो + पढ़ो_size) >= *words)
			last_cmd = true;

		ret_code = i40e_पढ़ो_nvm_aq(hw, 0x0, offset, पढ़ो_size,
					    data + words_पढ़ो, last_cmd);
		अगर (ret_code)
			जाओ पढ़ो_nvm_buffer_aq_निकास;

		/* Increment counter क्रम words alपढ़ोy पढ़ो and move offset to
		 * new पढ़ो location
		 */
		words_पढ़ो += पढ़ो_size;
		offset += पढ़ो_size;
	पूर्ण जबतक (words_पढ़ो < *words);

	क्रम (i = 0; i < *words; i++)
		data[i] = le16_to_cpu(((__le16 *)data)[i]);

पढ़ो_nvm_buffer_aq_निकास:
	*words = words_पढ़ो;
	वापस ret_code;
पूर्ण

/**
 * __i40e_पढ़ो_nvm_buffer - Reads nvm buffer, caller must acquire lock
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF).
 * @words: (in) number of words to पढ़ो; (out) number of words actually पढ़ो
 * @data: words पढ़ो from the Shaकरोw RAM
 *
 * Reads 16 bit words (data buffer) from the SR using the i40e_पढ़ो_nvm_srrd()
 * method.
 **/
अटल i40e_status __i40e_पढ़ो_nvm_buffer(काष्ठा i40e_hw *hw,
					  u16 offset, u16 *words,
					  u16 *data)
अणु
	अगर (hw->flags & I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE)
		वापस i40e_पढ़ो_nvm_buffer_aq(hw, offset, words, data);

	वापस i40e_पढ़ो_nvm_buffer_srctl(hw, offset, words, data);
पूर्ण

/**
 * i40e_पढ़ो_nvm_buffer - Reads Shaकरोw RAM buffer and acquire lock अगर necessary
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @offset: offset of the Shaकरोw RAM word to पढ़ो (0x000000 - 0x001FFF).
 * @words: (in) number of words to पढ़ो; (out) number of words actually पढ़ो
 * @data: words पढ़ो from the Shaकरोw RAM
 *
 * Reads 16 bit words (data buffer) from the SR using the i40e_पढ़ो_nvm_srrd()
 * method. The buffer पढ़ो is preceded by the NVM ownership take
 * and followed by the release.
 **/
i40e_status i40e_पढ़ो_nvm_buffer(काष्ठा i40e_hw *hw, u16 offset,
				 u16 *words, u16 *data)
अणु
	i40e_status ret_code = 0;

	अगर (hw->flags & I40E_HW_FLAG_AQ_SRCTL_ACCESS_ENABLE) अणु
		ret_code = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		अगर (!ret_code) अणु
			ret_code = i40e_पढ़ो_nvm_buffer_aq(hw, offset, words,
							   data);
			i40e_release_nvm(hw);
		पूर्ण
	पूर्ण अन्यथा अणु
		ret_code = i40e_पढ़ो_nvm_buffer_srctl(hw, offset, words, data);
	पूर्ण

	वापस ret_code;
पूर्ण

/**
 * i40e_ग_लिखो_nvm_aq - Writes Shaकरोw RAM.
 * @hw: poपूर्णांकer to the HW काष्ठाure.
 * @module_poपूर्णांकer: module poपूर्णांकer location in words from the NVM beginning
 * @offset: offset in words from module start
 * @words: number of words to ग_लिखो
 * @data: buffer with words to ग_लिखो to the Shaकरोw RAM
 * @last_command: tells the AdminQ that this is the last command
 *
 * Writes a 16 bit words buffer to the Shaकरोw RAM using the admin command.
 **/
अटल i40e_status i40e_ग_लिखो_nvm_aq(काष्ठा i40e_hw *hw, u8 module_poपूर्णांकer,
				     u32 offset, u16 words, व्योम *data,
				     bool last_command)
अणु
	i40e_status ret_code = I40E_ERR_NVM;
	काष्ठा i40e_asq_cmd_details cmd_details;

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	/* Here we are checking the SR limit only क्रम the flat memory model.
	 * We cannot करो it क्रम the module-based model, as we did not acquire
	 * the NVM resource yet (we cannot get the module poपूर्णांकer value).
	 * Firmware will check the module-based model.
	 */
	अगर ((offset + words) > hw->nvm.sr_size)
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write error: offset %d beyond Shadow RAM limit %d\n",
			   (offset + words), hw->nvm.sr_size);
	अन्यथा अगर (words > I40E_SR_SECTOR_SIZE_IN_WORDS)
		/* We can ग_लिखो only up to 4KB (one sector), in one AQ ग_लिखो */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write fail error: tried to write %d words, limit is %d.\n",
			   words, I40E_SR_SECTOR_SIZE_IN_WORDS);
	अन्यथा अगर (((offset + (words - 1)) / I40E_SR_SECTOR_SIZE_IN_WORDS)
		 != (offset / I40E_SR_SECTOR_SIZE_IN_WORDS))
		/* A single ग_लिखो cannot spपढ़ो over two sectors */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVM write error: cannot spread over two sectors in a single write offset=%d words=%d\n",
			   offset, words);
	अन्यथा
		ret_code = i40e_aq_update_nvm(hw, module_poपूर्णांकer,
					      2 * offset,  /*bytes*/
					      2 * words,   /*bytes*/
					      data, last_command, 0,
					      &cmd_details);

	वापस ret_code;
पूर्ण

/**
 * i40e_calc_nvm_checksum - Calculates and वापसs the checksum
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @checksum: poपूर्णांकer to the checksum
 *
 * This function calculates SW Checksum that covers the whole 64kB shaकरोw RAM
 * except the VPD and PCIe ALT Auto-load modules. The काष्ठाure and size of VPD
 * is customer specअगरic and unknown. Thereक्रमe, this function skips all maximum
 * possible size of VPD (1kB).
 **/
अटल i40e_status i40e_calc_nvm_checksum(काष्ठा i40e_hw *hw,
						    u16 *checksum)
अणु
	i40e_status ret_code;
	काष्ठा i40e_virt_mem vmem;
	u16 pcie_alt_module = 0;
	u16 checksum_local = 0;
	u16 vpd_module = 0;
	u16 *data;
	u16 i = 0;

	ret_code = i40e_allocate_virt_mem(hw, &vmem,
				    I40E_SR_SECTOR_SIZE_IN_WORDS * माप(u16));
	अगर (ret_code)
		जाओ i40e_calc_nvm_checksum_निकास;
	data = (u16 *)vmem.va;

	/* पढ़ो poपूर्णांकer to VPD area */
	ret_code = __i40e_पढ़ो_nvm_word(hw, I40E_SR_VPD_PTR, &vpd_module);
	अगर (ret_code) अणु
		ret_code = I40E_ERR_NVM_CHECKSUM;
		जाओ i40e_calc_nvm_checksum_निकास;
	पूर्ण

	/* पढ़ो poपूर्णांकer to PCIe Alt Auto-load module */
	ret_code = __i40e_पढ़ो_nvm_word(hw, I40E_SR_PCIE_ALT_AUTO_LOAD_PTR,
					&pcie_alt_module);
	अगर (ret_code) अणु
		ret_code = I40E_ERR_NVM_CHECKSUM;
		जाओ i40e_calc_nvm_checksum_निकास;
	पूर्ण

	/* Calculate SW checksum that covers the whole 64kB shaकरोw RAM
	 * except the VPD and PCIe ALT Auto-load modules
	 */
	क्रम (i = 0; i < hw->nvm.sr_size; i++) अणु
		/* Read SR page */
		अगर ((i % I40E_SR_SECTOR_SIZE_IN_WORDS) == 0) अणु
			u16 words = I40E_SR_SECTOR_SIZE_IN_WORDS;

			ret_code = __i40e_पढ़ो_nvm_buffer(hw, i, &words, data);
			अगर (ret_code) अणु
				ret_code = I40E_ERR_NVM_CHECKSUM;
				जाओ i40e_calc_nvm_checksum_निकास;
			पूर्ण
		पूर्ण

		/* Skip Checksum word */
		अगर (i == I40E_SR_SW_CHECKSUM_WORD)
			जारी;
		/* Skip VPD module (convert byte size to word count) */
		अगर ((i >= (u32)vpd_module) &&
		    (i < ((u32)vpd_module +
		     (I40E_SR_VPD_MODULE_MAX_SIZE / 2)))) अणु
			जारी;
		पूर्ण
		/* Skip PCIe ALT module (convert byte size to word count) */
		अगर ((i >= (u32)pcie_alt_module) &&
		    (i < ((u32)pcie_alt_module +
		     (I40E_SR_PCIE_ALT_MODULE_MAX_SIZE / 2)))) अणु
			जारी;
		पूर्ण

		checksum_local += data[i % I40E_SR_SECTOR_SIZE_IN_WORDS];
	पूर्ण

	*checksum = (u16)I40E_SR_SW_CHECKSUM_BASE - checksum_local;

i40e_calc_nvm_checksum_निकास:
	i40e_मुक्त_virt_mem(hw, &vmem);
	वापस ret_code;
पूर्ण

/**
 * i40e_update_nvm_checksum - Updates the NVM checksum
 * @hw: poपूर्णांकer to hardware काष्ठाure
 *
 * NVM ownership must be acquired beक्रमe calling this function and released
 * on ARQ completion event reception by caller.
 * This function will commit SR to NVM.
 **/
i40e_status i40e_update_nvm_checksum(काष्ठा i40e_hw *hw)
अणु
	i40e_status ret_code;
	u16 checksum;
	__le16 le_sum;

	ret_code = i40e_calc_nvm_checksum(hw, &checksum);
	le_sum = cpu_to_le16(checksum);
	अगर (!ret_code)
		ret_code = i40e_ग_लिखो_nvm_aq(hw, 0x00, I40E_SR_SW_CHECKSUM_WORD,
					     1, &le_sum, true);

	वापस ret_code;
पूर्ण

/**
 * i40e_validate_nvm_checksum - Validate EEPROM checksum
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @checksum: calculated checksum
 *
 * Perक्रमms checksum calculation and validates the NVM SW checksum. If the
 * caller करोes not need checksum, the value can be शून्य.
 **/
i40e_status i40e_validate_nvm_checksum(काष्ठा i40e_hw *hw,
						 u16 *checksum)
अणु
	i40e_status ret_code = 0;
	u16 checksum_sr = 0;
	u16 checksum_local = 0;

	/* We must acquire the NVM lock in order to correctly synchronize the
	 * NVM accesses across multiple PFs. Without करोing so it is possible
	 * क्रम one of the PFs to पढ़ो invalid data potentially indicating that
	 * the checksum is invalid.
	 */
	ret_code = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
	अगर (ret_code)
		वापस ret_code;
	ret_code = i40e_calc_nvm_checksum(hw, &checksum_local);
	__i40e_पढ़ो_nvm_word(hw, I40E_SR_SW_CHECKSUM_WORD, &checksum_sr);
	i40e_release_nvm(hw);
	अगर (ret_code)
		वापस ret_code;

	/* Verअगरy पढ़ो checksum from EEPROM is the same as
	 * calculated checksum
	 */
	अगर (checksum_local != checksum_sr)
		ret_code = I40E_ERR_NVM_CHECKSUM;

	/* If the user cares, वापस the calculated checksum */
	अगर (checksum)
		*checksum = checksum_local;

	वापस ret_code;
पूर्ण

अटल i40e_status i40e_nvmupd_state_init(काष्ठा i40e_hw *hw,
					  काष्ठा i40e_nvm_access *cmd,
					  u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_state_पढ़ोing(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_state_writing(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *त्रुटि_सं);
अटल क्रमागत i40e_nvmupd_cmd i40e_nvmupd_validate_command(काष्ठा i40e_hw *hw,
						काष्ठा i40e_nvm_access *cmd,
						पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_nvm_erase(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_nvm_access *cmd,
					 पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_nvm_ग_लिखो(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_nvm_access *cmd,
					 u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_nvm_पढ़ो(काष्ठा i40e_hw *hw,
					काष्ठा i40e_nvm_access *cmd,
					u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_exec_aq(काष्ठा i40e_hw *hw,
				       काष्ठा i40e_nvm_access *cmd,
				       u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_get_aq_result(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल i40e_status i40e_nvmupd_get_aq_event(काष्ठा i40e_hw *hw,
					    काष्ठा i40e_nvm_access *cmd,
					    u8 *bytes, पूर्णांक *pत्रुटि_सं);
अटल अंतरभूत u8 i40e_nvmupd_get_module(u32 val)
अणु
	वापस (u8)(val & I40E_NVM_MOD_PNT_MASK);
पूर्ण
अटल अंतरभूत u8 i40e_nvmupd_get_transaction(u32 val)
अणु
	वापस (u8)((val & I40E_NVM_TRANS_MASK) >> I40E_NVM_TRANS_SHIFT);
पूर्ण

अटल अंतरभूत u8 i40e_nvmupd_get_preservation_flags(u32 val)
अणु
	वापस (u8)((val & I40E_NVM_PRESERVATION_FLAGS_MASK) >>
		    I40E_NVM_PRESERVATION_FLAGS_SHIFT);
पूर्ण

अटल स्थिर अक्षर * स्थिर i40e_nvm_update_state_str[] = अणु
	"I40E_NVMUPD_INVALID",
	"I40E_NVMUPD_READ_CON",
	"I40E_NVMUPD_READ_SNT",
	"I40E_NVMUPD_READ_LCB",
	"I40E_NVMUPD_READ_SA",
	"I40E_NVMUPD_WRITE_ERA",
	"I40E_NVMUPD_WRITE_CON",
	"I40E_NVMUPD_WRITE_SNT",
	"I40E_NVMUPD_WRITE_LCB",
	"I40E_NVMUPD_WRITE_SA",
	"I40E_NVMUPD_CSUM_CON",
	"I40E_NVMUPD_CSUM_SA",
	"I40E_NVMUPD_CSUM_LCB",
	"I40E_NVMUPD_STATUS",
	"I40E_NVMUPD_EXEC_AQ",
	"I40E_NVMUPD_GET_AQ_RESULT",
	"I40E_NVMUPD_GET_AQ_EVENT",
पूर्ण;

/**
 * i40e_nvmupd_command - Process an NVM update command
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * Dispatches command depending on what update state is current
 **/
i40e_status i40e_nvmupd_command(काष्ठा i40e_hw *hw,
				काष्ठा i40e_nvm_access *cmd,
				u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status;
	क्रमागत i40e_nvmupd_cmd upd_cmd;

	/* assume success */
	*pत्रुटि_सं = 0;

	/* early check क्रम status command and debug msgs */
	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, pत्रुटि_सं);

	i40e_debug(hw, I40E_DEBUG_NVM, "%s state %d nvm_release_on_hold %d opc 0x%04x cmd 0x%08x config 0x%08x offset 0x%08x data_size 0x%08x\n",
		   i40e_nvm_update_state_str[upd_cmd],
		   hw->nvmupd_state,
		   hw->nvm_release_on_करोne, hw->nvm_रुको_opcode,
		   cmd->command, cmd->config, cmd->offset, cmd->data_size);

	अगर (upd_cmd == I40E_NVMUPD_INVALID) अणु
		*pत्रुटि_सं = -EFAULT;
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_validate_command returns %d errno %d\n",
			   upd_cmd, *pत्रुटि_सं);
	पूर्ण

	/* a status request वापसs immediately rather than
	 * going पूर्णांकo the state machine
	 */
	अगर (upd_cmd == I40E_NVMUPD_STATUS) अणु
		अगर (!cmd->data_size) अणु
			*pत्रुटि_सं = -EFAULT;
			वापस I40E_ERR_BUF_TOO_SHORT;
		पूर्ण

		bytes[0] = hw->nvmupd_state;

		अगर (cmd->data_size >= 4) अणु
			bytes[1] = 0;
			*((u16 *)&bytes[2]) = hw->nvm_रुको_opcode;
		पूर्ण

		/* Clear error status on पढ़ो */
		अगर (hw->nvmupd_state == I40E_NVMUPD_STATE_ERROR)
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;

		वापस 0;
	पूर्ण

	/* Clear status even it is not पढ़ो and log */
	अगर (hw->nvmupd_state == I40E_NVMUPD_STATE_ERROR) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "Clearing I40E_NVMUPD_STATE_ERROR state without reading\n");
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
	पूर्ण

	/* Acquire lock to prevent race condition where adminq_task
	 * can execute after i40e_nvmupd_nvm_पढ़ो/ग_लिखो but beक्रमe state
	 * variables (nvm_रुको_opcode, nvm_release_on_करोne) are updated.
	 *
	 * During NVMUpdate, it is observed that lock could be held क्रम
	 * ~5ms क्रम most commands. However lock is held क्रम ~60ms क्रम
	 * NVMUPD_CSUM_LCB command.
	 */
	mutex_lock(&hw->aq.arq_mutex);
	चयन (hw->nvmupd_state) अणु
	हाल I40E_NVMUPD_STATE_INIT:
		status = i40e_nvmupd_state_init(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_STATE_READING:
		status = i40e_nvmupd_state_पढ़ोing(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_STATE_WRITING:
		status = i40e_nvmupd_state_writing(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_STATE_INIT_WAIT:
	हाल I40E_NVMUPD_STATE_WRITE_WAIT:
		/* अगर we need to stop रुकोing क्रम an event, clear
		 * the रुको info and वापस beक्रमe करोing anything अन्यथा
		 */
		अगर (cmd->offset == 0xffff) अणु
			i40e_nvmupd_clear_रुको_state(hw);
			status = 0;
			अवरोध;
		पूर्ण

		status = I40E_ERR_NOT_READY;
		*pत्रुटि_सं = -EBUSY;
		अवरोध;

	शेष:
		/* invalid state, should never happen */
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: no such state %d\n", hw->nvmupd_state);
		status = I40E_NOT_SUPPORTED;
		*pत्रुटि_सं = -ESRCH;
		अवरोध;
	पूर्ण

	mutex_unlock(&hw->aq.arq_mutex);
	वापस status;
पूर्ण

/**
 * i40e_nvmupd_state_init - Handle NVM update state Init
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * Process legitimate commands of the Init state and conditionally set next
 * state. Reject all other commands.
 **/
अटल i40e_status i40e_nvmupd_state_init(काष्ठा i40e_hw *hw,
					  काष्ठा i40e_nvm_access *cmd,
					  u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status = 0;
	क्रमागत i40e_nvmupd_cmd upd_cmd;

	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, pत्रुटि_सं);

	चयन (upd_cmd) अणु
	हाल I40E_NVMUPD_READ_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_nvmupd_nvm_पढ़ो(hw, cmd, bytes, pत्रुटि_सं);
			i40e_release_nvm(hw);
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_READ_SNT:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_READ);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_nvmupd_nvm_पढ़ो(hw, cmd, bytes, pत्रुटि_सं);
			अगर (status)
				i40e_release_nvm(hw);
			अन्यथा
				hw->nvmupd_state = I40E_NVMUPD_STATE_READING;
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_WRITE_ERA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_nvmupd_nvm_erase(hw, cmd, pत्रुटि_सं);
			अगर (status) अणु
				i40e_release_nvm(hw);
			पूर्ण अन्यथा अणु
				hw->nvm_release_on_करोne = true;
				hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_erase;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_WRITE_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_nvmupd_nvm_ग_लिखो(hw, cmd, bytes, pत्रुटि_सं);
			अगर (status) अणु
				i40e_release_nvm(hw);
			पूर्ण अन्यथा अणु
				hw->nvm_release_on_करोne = true;
				hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_WRITE_SNT:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_nvmupd_nvm_ग_लिखो(hw, cmd, bytes, pत्रुटि_सं);
			अगर (status) अणु
				i40e_release_nvm(hw);
			पूर्ण अन्यथा अणु
				hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_WRITE_WAIT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_CSUM_SA:
		status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
		अगर (status) अणु
			*pत्रुटि_सं = i40e_aq_rc_to_posix(status,
						     hw->aq.asq_last_status);
		पूर्ण अन्यथा अणु
			status = i40e_update_nvm_checksum(hw);
			अगर (status) अणु
				*pत्रुटि_सं = hw->aq.asq_last_status ?
				   i40e_aq_rc_to_posix(status,
						       hw->aq.asq_last_status) :
				   -EIO;
				i40e_release_nvm(hw);
			पूर्ण अन्यथा अणु
				hw->nvm_release_on_करोne = true;
				hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
				hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_EXEC_AQ:
		status = i40e_nvmupd_exec_aq(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_GET_AQ_RESULT:
		status = i40e_nvmupd_get_aq_result(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_GET_AQ_EVENT:
		status = i40e_nvmupd_get_aq_event(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	शेष:
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: bad cmd %s in init state\n",
			   i40e_nvm_update_state_str[upd_cmd]);
		status = I40E_ERR_NVM;
		*pत्रुटि_सं = -ESRCH;
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_nvmupd_state_पढ़ोing - Handle NVM update state Reading
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * NVM ownership is alपढ़ोy held.  Process legitimate commands and set any
 * change in state; reject all other commands.
 **/
अटल i40e_status i40e_nvmupd_state_पढ़ोing(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status = 0;
	क्रमागत i40e_nvmupd_cmd upd_cmd;

	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, pत्रुटि_सं);

	चयन (upd_cmd) अणु
	हाल I40E_NVMUPD_READ_SA:
	हाल I40E_NVMUPD_READ_CON:
		status = i40e_nvmupd_nvm_पढ़ो(hw, cmd, bytes, pत्रुटि_सं);
		अवरोध;

	हाल I40E_NVMUPD_READ_LCB:
		status = i40e_nvmupd_nvm_पढ़ो(hw, cmd, bytes, pत्रुटि_सं);
		i40e_release_nvm(hw);
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		अवरोध;

	शेष:
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: bad cmd %s in reading state.\n",
			   i40e_nvm_update_state_str[upd_cmd]);
		status = I40E_NOT_SUPPORTED;
		*pत्रुटि_सं = -ESRCH;
		अवरोध;
	पूर्ण
	वापस status;
पूर्ण

/**
 * i40e_nvmupd_state_writing - Handle NVM update state Writing
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * NVM ownership is alपढ़ोy held.  Process legitimate commands and set any
 * change in state; reject all other commands
 **/
अटल i40e_status i40e_nvmupd_state_writing(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status = 0;
	क्रमागत i40e_nvmupd_cmd upd_cmd;
	bool retry_attempt = false;

	upd_cmd = i40e_nvmupd_validate_command(hw, cmd, pत्रुटि_सं);

retry:
	चयन (upd_cmd) अणु
	हाल I40E_NVMUPD_WRITE_CON:
		status = i40e_nvmupd_nvm_ग_लिखो(hw, cmd, bytes, pत्रुटि_सं);
		अगर (!status) अणु
			hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
			hw->nvmupd_state = I40E_NVMUPD_STATE_WRITE_WAIT;
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_WRITE_LCB:
		status = i40e_nvmupd_nvm_ग_लिखो(hw, cmd, bytes, pत्रुटि_सं);
		अगर (status) अणु
			*pत्रुटि_सं = hw->aq.asq_last_status ?
				   i40e_aq_rc_to_posix(status,
						       hw->aq.asq_last_status) :
				   -EIO;
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		पूर्ण अन्यथा अणु
			hw->nvm_release_on_करोne = true;
			hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_CSUM_CON:
		/* Assumes the caller has acquired the nvm */
		status = i40e_update_nvm_checksum(hw);
		अगर (status) अणु
			*pत्रुटि_सं = hw->aq.asq_last_status ?
				   i40e_aq_rc_to_posix(status,
						       hw->aq.asq_last_status) :
				   -EIO;
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		पूर्ण अन्यथा अणु
			hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
			hw->nvmupd_state = I40E_NVMUPD_STATE_WRITE_WAIT;
		पूर्ण
		अवरोध;

	हाल I40E_NVMUPD_CSUM_LCB:
		/* Assumes the caller has acquired the nvm */
		status = i40e_update_nvm_checksum(hw);
		अगर (status) अणु
			*pत्रुटि_सं = hw->aq.asq_last_status ?
				   i40e_aq_rc_to_posix(status,
						       hw->aq.asq_last_status) :
				   -EIO;
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		पूर्ण अन्यथा अणु
			hw->nvm_release_on_करोne = true;
			hw->nvm_रुको_opcode = i40e_aqc_opc_nvm_update;
			hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
		पूर्ण
		अवरोध;

	शेष:
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: bad cmd %s in writing state.\n",
			   i40e_nvm_update_state_str[upd_cmd]);
		status = I40E_NOT_SUPPORTED;
		*pत्रुटि_सं = -ESRCH;
		अवरोध;
	पूर्ण

	/* In some circumstances, a multi-ग_लिखो transaction takes दीर्घer
	 * than the शेष 3 minute समयout on the ग_लिखो semaphore.  If
	 * the ग_लिखो failed with an EBUSY status, this is likely the problem,
	 * so here we try to reacquire the semaphore then retry the ग_लिखो.
	 * We only करो one retry, then give up.
	 */
	अगर (status && (hw->aq.asq_last_status == I40E_AQ_RC_EBUSY) &&
	    !retry_attempt) अणु
		i40e_status old_status = status;
		u32 old_asq_status = hw->aq.asq_last_status;
		u32 gसमय;

		gसमय = rd32(hw, I40E_GLVFGEN_TIMER);
		अगर (gसमय >= hw->nvm.hw_semaphore_समयout) अणु
			i40e_debug(hw, I40E_DEBUG_ALL,
				   "NVMUPD: write semaphore expired (%d >= %lld), retrying\n",
				   gसमय, hw->nvm.hw_semaphore_समयout);
			i40e_release_nvm(hw);
			status = i40e_acquire_nvm(hw, I40E_RESOURCE_WRITE);
			अगर (status) अणु
				i40e_debug(hw, I40E_DEBUG_ALL,
					   "NVMUPD: write semaphore reacquire failed aq_err = %d\n",
					   hw->aq.asq_last_status);
				status = old_status;
				hw->aq.asq_last_status = old_asq_status;
			पूर्ण अन्यथा अणु
				retry_attempt = true;
				जाओ retry;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_nvmupd_clear_रुको_state - clear रुको state on hw
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 **/
व्योम i40e_nvmupd_clear_रुको_state(काष्ठा i40e_hw *hw)
अणु
	i40e_debug(hw, I40E_DEBUG_NVM,
		   "NVMUPD: clearing wait on opcode 0x%04x\n",
		   hw->nvm_रुको_opcode);

	अगर (hw->nvm_release_on_करोne) अणु
		i40e_release_nvm(hw);
		hw->nvm_release_on_करोne = false;
	पूर्ण
	hw->nvm_रुको_opcode = 0;

	अगर (hw->aq.arq_last_status) अणु
		hw->nvmupd_state = I40E_NVMUPD_STATE_ERROR;
		वापस;
	पूर्ण

	चयन (hw->nvmupd_state) अणु
	हाल I40E_NVMUPD_STATE_INIT_WAIT:
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT;
		अवरोध;

	हाल I40E_NVMUPD_STATE_WRITE_WAIT:
		hw->nvmupd_state = I40E_NVMUPD_STATE_WRITING;
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * i40e_nvmupd_check_रुको_event - handle NVM update operation events
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @opcode: the event that just happened
 * @desc: AdminQ descriptor
 **/
व्योम i40e_nvmupd_check_रुको_event(काष्ठा i40e_hw *hw, u16 opcode,
				  काष्ठा i40e_aq_desc *desc)
अणु
	u32 aq_desc_len = माप(काष्ठा i40e_aq_desc);

	अगर (opcode == hw->nvm_रुको_opcode) अणु
		स_नकल(&hw->nvm_aq_event_desc, desc, aq_desc_len);
		i40e_nvmupd_clear_रुको_state(hw);
	पूर्ण
पूर्ण

/**
 * i40e_nvmupd_validate_command - Validate given command
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * Return one of the valid command types or I40E_NVMUPD_INVALID
 **/
अटल क्रमागत i40e_nvmupd_cmd i40e_nvmupd_validate_command(काष्ठा i40e_hw *hw,
						 काष्ठा i40e_nvm_access *cmd,
						 पूर्णांक *pत्रुटि_सं)
अणु
	क्रमागत i40e_nvmupd_cmd upd_cmd;
	u8 module, transaction;

	/* anything that करोesn't match a recognized हाल is an error */
	upd_cmd = I40E_NVMUPD_INVALID;

	transaction = i40e_nvmupd_get_transaction(cmd->config);
	module = i40e_nvmupd_get_module(cmd->config);

	/* limits on data size */
	अगर ((cmd->data_size < 1) ||
	    (cmd->data_size > I40E_NVMUPD_MAX_DATA)) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_validate_command data_size %d\n",
			   cmd->data_size);
		*pत्रुटि_सं = -EFAULT;
		वापस I40E_NVMUPD_INVALID;
	पूर्ण

	चयन (cmd->command) अणु
	हाल I40E_NVM_READ:
		चयन (transaction) अणु
		हाल I40E_NVM_CON:
			upd_cmd = I40E_NVMUPD_READ_CON;
			अवरोध;
		हाल I40E_NVM_SNT:
			upd_cmd = I40E_NVMUPD_READ_SNT;
			अवरोध;
		हाल I40E_NVM_LCB:
			upd_cmd = I40E_NVMUPD_READ_LCB;
			अवरोध;
		हाल I40E_NVM_SA:
			upd_cmd = I40E_NVMUPD_READ_SA;
			अवरोध;
		हाल I40E_NVM_EXEC:
			अगर (module == 0xf)
				upd_cmd = I40E_NVMUPD_STATUS;
			अन्यथा अगर (module == 0)
				upd_cmd = I40E_NVMUPD_GET_AQ_RESULT;
			अवरोध;
		हाल I40E_NVM_AQE:
			upd_cmd = I40E_NVMUPD_GET_AQ_EVENT;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल I40E_NVM_WRITE:
		चयन (transaction) अणु
		हाल I40E_NVM_CON:
			upd_cmd = I40E_NVMUPD_WRITE_CON;
			अवरोध;
		हाल I40E_NVM_SNT:
			upd_cmd = I40E_NVMUPD_WRITE_SNT;
			अवरोध;
		हाल I40E_NVM_LCB:
			upd_cmd = I40E_NVMUPD_WRITE_LCB;
			अवरोध;
		हाल I40E_NVM_SA:
			upd_cmd = I40E_NVMUPD_WRITE_SA;
			अवरोध;
		हाल I40E_NVM_ERA:
			upd_cmd = I40E_NVMUPD_WRITE_ERA;
			अवरोध;
		हाल I40E_NVM_CSUM:
			upd_cmd = I40E_NVMUPD_CSUM_CON;
			अवरोध;
		हाल (I40E_NVM_CSUM|I40E_NVM_SA):
			upd_cmd = I40E_NVMUPD_CSUM_SA;
			अवरोध;
		हाल (I40E_NVM_CSUM|I40E_NVM_LCB):
			upd_cmd = I40E_NVMUPD_CSUM_LCB;
			अवरोध;
		हाल I40E_NVM_EXEC:
			अगर (module == 0)
				upd_cmd = I40E_NVMUPD_EXEC_AQ;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस upd_cmd;
पूर्ण

/**
 * i40e_nvmupd_exec_aq - Run an AQ command
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * cmd काष्ठाure contains identअगरiers and data buffer
 **/
अटल i40e_status i40e_nvmupd_exec_aq(काष्ठा i40e_hw *hw,
				       काष्ठा i40e_nvm_access *cmd,
				       u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	काष्ठा i40e_asq_cmd_details cmd_details;
	i40e_status status;
	काष्ठा i40e_aq_desc *aq_desc;
	u32 buff_size = 0;
	u8 *buff = शून्य;
	u32 aq_desc_len;
	u32 aq_data_len;

	i40e_debug(hw, I40E_DEBUG_NVM, "NVMUPD: %s\n", __func__);
	अगर (cmd->offset == 0xffff)
		वापस 0;

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	aq_desc_len = माप(काष्ठा i40e_aq_desc);
	स_रखो(&hw->nvm_wb_desc, 0, aq_desc_len);

	/* get the aq descriptor */
	अगर (cmd->data_size < aq_desc_len) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "NVMUPD: not enough aq desc bytes for exec, size %d < %d\n",
			   cmd->data_size, aq_desc_len);
		*pत्रुटि_सं = -EINVAL;
		वापस I40E_ERR_PARAM;
	पूर्ण
	aq_desc = (काष्ठा i40e_aq_desc *)bytes;

	/* अगर data buffer needed, make sure it's पढ़ोy */
	aq_data_len = cmd->data_size - aq_desc_len;
	buff_size = max_t(u32, aq_data_len, le16_to_cpu(aq_desc->datalen));
	अगर (buff_size) अणु
		अगर (!hw->nvm_buff.va) अणु
			status = i40e_allocate_virt_mem(hw, &hw->nvm_buff,
							hw->aq.asq_buf_size);
			अगर (status)
				i40e_debug(hw, I40E_DEBUG_NVM,
					   "NVMUPD: i40e_allocate_virt_mem for exec buff failed, %d\n",
					   status);
		पूर्ण

		अगर (hw->nvm_buff.va) अणु
			buff = hw->nvm_buff.va;
			स_नकल(buff, &bytes[aq_desc_len], aq_data_len);
		पूर्ण
	पूर्ण

	अगर (cmd->offset)
		स_रखो(&hw->nvm_aq_event_desc, 0, aq_desc_len);

	/* and away we go! */
	status = i40e_asq_send_command(hw, aq_desc, buff,
				       buff_size, &cmd_details);
	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_exec_aq err %s aq_err %s\n",
			   i40e_stat_str(hw, status),
			   i40e_aq_str(hw, hw->aq.asq_last_status));
		*pत्रुटि_सं = i40e_aq_rc_to_posix(status, hw->aq.asq_last_status);
		वापस status;
	पूर्ण

	/* should we रुको क्रम a followup event? */
	अगर (cmd->offset) अणु
		hw->nvm_रुको_opcode = cmd->offset;
		hw->nvmupd_state = I40E_NVMUPD_STATE_INIT_WAIT;
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_nvmupd_get_aq_result - Get the results from the previous exec_aq
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * cmd काष्ठाure contains identअगरiers and data buffer
 **/
अटल i40e_status i40e_nvmupd_get_aq_result(काष्ठा i40e_hw *hw,
					     काष्ठा i40e_nvm_access *cmd,
					     u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	u32 aq_total_len;
	u32 aq_desc_len;
	पूर्णांक reमुख्यder;
	u8 *buff;

	i40e_debug(hw, I40E_DEBUG_NVM, "NVMUPD: %s\n", __func__);

	aq_desc_len = माप(काष्ठा i40e_aq_desc);
	aq_total_len = aq_desc_len + le16_to_cpu(hw->nvm_wb_desc.datalen);

	/* check offset range */
	अगर (cmd->offset > aq_total_len) अणु
		i40e_debug(hw, I40E_DEBUG_NVM, "%s: offset too big %d > %d\n",
			   __func__, cmd->offset, aq_total_len);
		*pत्रुटि_सं = -EINVAL;
		वापस I40E_ERR_PARAM;
	पूर्ण

	/* check copylength range */
	अगर (cmd->data_size > (aq_total_len - cmd->offset)) अणु
		पूर्णांक new_len = aq_total_len - cmd->offset;

		i40e_debug(hw, I40E_DEBUG_NVM, "%s: copy length %d too big, trimming to %d\n",
			   __func__, cmd->data_size, new_len);
		cmd->data_size = new_len;
	पूर्ण

	reमुख्यder = cmd->data_size;
	अगर (cmd->offset < aq_desc_len) अणु
		u32 len = aq_desc_len - cmd->offset;

		len = min(len, cmd->data_size);
		i40e_debug(hw, I40E_DEBUG_NVM, "%s: aq_desc bytes %d to %d\n",
			   __func__, cmd->offset, cmd->offset + len);

		buff = ((u8 *)&hw->nvm_wb_desc) + cmd->offset;
		स_नकल(bytes, buff, len);

		bytes += len;
		reमुख्यder -= len;
		buff = hw->nvm_buff.va;
	पूर्ण अन्यथा अणु
		buff = hw->nvm_buff.va + (cmd->offset - aq_desc_len);
	पूर्ण

	अगर (reमुख्यder > 0) अणु
		पूर्णांक start_byte = buff - (u8 *)hw->nvm_buff.va;

		i40e_debug(hw, I40E_DEBUG_NVM, "%s: databuf bytes %d to %d\n",
			   __func__, start_byte, start_byte + reमुख्यder);
		स_नकल(bytes, buff, reमुख्यder);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_nvmupd_get_aq_event - Get the Admin Queue event from previous exec_aq
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * cmd काष्ठाure contains identअगरiers and data buffer
 **/
अटल i40e_status i40e_nvmupd_get_aq_event(काष्ठा i40e_hw *hw,
					    काष्ठा i40e_nvm_access *cmd,
					    u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	u32 aq_total_len;
	u32 aq_desc_len;

	i40e_debug(hw, I40E_DEBUG_NVM, "NVMUPD: %s\n", __func__);

	aq_desc_len = माप(काष्ठा i40e_aq_desc);
	aq_total_len = aq_desc_len + le16_to_cpu(hw->nvm_aq_event_desc.datalen);

	/* check copylength range */
	अगर (cmd->data_size > aq_total_len) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "%s: copy length %d too big, trimming to %d\n",
			   __func__, cmd->data_size, aq_total_len);
		cmd->data_size = aq_total_len;
	पूर्ण

	स_नकल(bytes, &hw->nvm_aq_event_desc, cmd->data_size);

	वापस 0;
पूर्ण

/**
 * i40e_nvmupd_nvm_पढ़ो - Read NVM
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * cmd काष्ठाure contains identअगरiers and data buffer
 **/
अटल i40e_status i40e_nvmupd_nvm_पढ़ो(काष्ठा i40e_hw *hw,
					काष्ठा i40e_nvm_access *cmd,
					u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	काष्ठा i40e_asq_cmd_details cmd_details;
	i40e_status status;
	u8 module, transaction;
	bool last;

	transaction = i40e_nvmupd_get_transaction(cmd->config);
	module = i40e_nvmupd_get_module(cmd->config);
	last = (transaction == I40E_NVM_LCB) || (transaction == I40E_NVM_SA);

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	status = i40e_aq_पढ़ो_nvm(hw, module, cmd->offset, (u16)cmd->data_size,
				  bytes, last, &cmd_details);
	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_read mod 0x%x  off 0x%x  len 0x%x\n",
			   module, cmd->offset, cmd->data_size);
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_read status %d aq %d\n",
			   status, hw->aq.asq_last_status);
		*pत्रुटि_सं = i40e_aq_rc_to_posix(status, hw->aq.asq_last_status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_nvmupd_nvm_erase - Erase an NVM module
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * module, offset, data_size and data are in cmd काष्ठाure
 **/
अटल i40e_status i40e_nvmupd_nvm_erase(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_nvm_access *cmd,
					 पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status = 0;
	काष्ठा i40e_asq_cmd_details cmd_details;
	u8 module, transaction;
	bool last;

	transaction = i40e_nvmupd_get_transaction(cmd->config);
	module = i40e_nvmupd_get_module(cmd->config);
	last = (transaction & I40E_NVM_LCB);

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	status = i40e_aq_erase_nvm(hw, module, cmd->offset, (u16)cmd->data_size,
				   last, &cmd_details);
	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_erase mod 0x%x  off 0x%x len 0x%x\n",
			   module, cmd->offset, cmd->data_size);
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_erase status %d aq %d\n",
			   status, hw->aq.asq_last_status);
		*pत्रुटि_सं = i40e_aq_rc_to_posix(status, hw->aq.asq_last_status);
	पूर्ण

	वापस status;
पूर्ण

/**
 * i40e_nvmupd_nvm_ग_लिखो - Write NVM
 * @hw: poपूर्णांकer to hardware काष्ठाure
 * @cmd: poपूर्णांकer to nvm update command buffer
 * @bytes: poपूर्णांकer to the data buffer
 * @pत्रुटि_सं: poपूर्णांकer to वापस error code
 *
 * module, offset, data_size and data are in cmd काष्ठाure
 **/
अटल i40e_status i40e_nvmupd_nvm_ग_लिखो(काष्ठा i40e_hw *hw,
					 काष्ठा i40e_nvm_access *cmd,
					 u8 *bytes, पूर्णांक *pत्रुटि_सं)
अणु
	i40e_status status = 0;
	काष्ठा i40e_asq_cmd_details cmd_details;
	u8 module, transaction;
	u8 preservation_flags;
	bool last;

	transaction = i40e_nvmupd_get_transaction(cmd->config);
	module = i40e_nvmupd_get_module(cmd->config);
	last = (transaction & I40E_NVM_LCB);
	preservation_flags = i40e_nvmupd_get_preservation_flags(cmd->config);

	स_रखो(&cmd_details, 0, माप(cmd_details));
	cmd_details.wb_desc = &hw->nvm_wb_desc;

	status = i40e_aq_update_nvm(hw, module, cmd->offset,
				    (u16)cmd->data_size, bytes, last,
				    preservation_flags, &cmd_details);
	अगर (status) अणु
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_write mod 0x%x off 0x%x len 0x%x\n",
			   module, cmd->offset, cmd->data_size);
		i40e_debug(hw, I40E_DEBUG_NVM,
			   "i40e_nvmupd_nvm_write status %d aq %d\n",
			   status, hw->aq.asq_last_status);
		*pत्रुटि_सं = i40e_aq_rc_to_posix(status, hw->aq.asq_last_status);
	पूर्ण

	वापस status;
पूर्ण
