<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#अगर_अघोषित __CC_HW_QUEUE_DEFS_H__
#घोषणा __CC_HW_QUEUE_DEFS_H__

#समावेश <linux/types.h>

#समावेश "cc_kernel_regs.h"
#समावेश <linux/bitfield.h>

/******************************************************************************
 *				DEFINITIONS
 ******************************************************************************/

#घोषणा HW_DESC_SIZE_WORDS		6
/* Define max. available slots in HW queue */
#घोषणा HW_QUEUE_SLOTS_MAX              15

#घोषणा CC_REG_LOW(name)  (name ## _BIT_SHIFT)
#घोषणा CC_REG_HIGH(name) (CC_REG_LOW(name) + name ## _BIT_SIZE - 1)
#घोषणा CC_GENMASK(name)  GENMASK(CC_REG_HIGH(name), CC_REG_LOW(name))

#घोषणा CC_HWQ_GENMASK(word, field) \
	CC_GENMASK(CC_DSCRPTR_QUEUE_WORD ## word ## _ ## field)

#घोषणा WORD0_VALUE		CC_HWQ_GENMASK(0, VALUE)
#घोषणा	WORD0_CPP_CIPHER_MODE	CC_HWQ_GENMASK(0, CPP_CIPHER_MODE)
#घोषणा WORD1_DIN_CONST_VALUE	CC_HWQ_GENMASK(1, DIN_CONST_VALUE)
#घोषणा WORD1_DIN_DMA_MODE	CC_HWQ_GENMASK(1, DIN_DMA_MODE)
#घोषणा WORD1_DIN_SIZE		CC_HWQ_GENMASK(1, DIN_SIZE)
#घोषणा WORD1_NOT_LAST		CC_HWQ_GENMASK(1, NOT_LAST)
#घोषणा WORD1_NS_BIT		CC_HWQ_GENMASK(1, NS_BIT)
#घोषणा WORD1_LOCK_QUEUE	CC_HWQ_GENMASK(1, LOCK_QUEUE)
#घोषणा WORD2_VALUE		CC_HWQ_GENMASK(2, VALUE)
#घोषणा WORD3_DOUT_DMA_MODE	CC_HWQ_GENMASK(3, DOUT_DMA_MODE)
#घोषणा WORD3_DOUT_LAST_IND	CC_HWQ_GENMASK(3, DOUT_LAST_IND)
#घोषणा WORD3_DOUT_SIZE		CC_HWQ_GENMASK(3, DOUT_SIZE)
#घोषणा WORD3_HASH_XOR_BIT	CC_HWQ_GENMASK(3, HASH_XOR_BIT)
#घोषणा WORD3_NS_BIT		CC_HWQ_GENMASK(3, NS_BIT)
#घोषणा WORD3_QUEUE_LAST_IND	CC_HWQ_GENMASK(3, QUEUE_LAST_IND)
#घोषणा WORD4_ACK_NEEDED	CC_HWQ_GENMASK(4, ACK_NEEDED)
#घोषणा WORD4_AES_SEL_N_HASH	CC_HWQ_GENMASK(4, AES_SEL_N_HASH)
#घोषणा WORD4_AES_XOR_CRYPTO_KEY CC_HWQ_GENMASK(4, AES_XOR_CRYPTO_KEY)
#घोषणा WORD4_BYTES_SWAP	CC_HWQ_GENMASK(4, BYTES_SWAP)
#घोषणा WORD4_CIPHER_CONF0	CC_HWQ_GENMASK(4, CIPHER_CONF0)
#घोषणा WORD4_CIPHER_CONF1	CC_HWQ_GENMASK(4, CIPHER_CONF1)
#घोषणा WORD4_CIPHER_CONF2	CC_HWQ_GENMASK(4, CIPHER_CONF2)
#घोषणा WORD4_CIPHER_DO		CC_HWQ_GENMASK(4, CIPHER_DO)
#घोषणा WORD4_CIPHER_MODE	CC_HWQ_GENMASK(4, CIPHER_MODE)
#घोषणा WORD4_CMAC_SIZE0	CC_HWQ_GENMASK(4, CMAC_SIZE0)
#घोषणा WORD4_DATA_FLOW_MODE	CC_HWQ_GENMASK(4, DATA_FLOW_MODE)
#घोषणा WORD4_KEY_SIZE		CC_HWQ_GENMASK(4, KEY_SIZE)
#घोषणा WORD4_SETUP_OPERATION	CC_HWQ_GENMASK(4, SETUP_OPERATION)
#घोषणा WORD5_DIN_ADDR_HIGH	CC_HWQ_GENMASK(5, DIN_ADDR_HIGH)
#घोषणा WORD5_DOUT_ADDR_HIGH	CC_HWQ_GENMASK(5, DOUT_ADDR_HIGH)

/******************************************************************************
 *				TYPE DEFINITIONS
 ******************************************************************************/

काष्ठा cc_hw_desc अणु
	जोड़ अणु
		u32 word[HW_DESC_SIZE_WORDS];
		u16 hword[HW_DESC_SIZE_WORDS * 2];
	पूर्ण;
पूर्ण;

क्रमागत cc_axi_sec अणु
	AXI_SECURE = 0,
	AXI_NOT_SECURE = 1
पूर्ण;

क्रमागत cc_desc_direction अणु
	DESC_सूचीECTION_ILLEGAL = -1,
	DESC_सूचीECTION_ENCRYPT_ENCRYPT = 0,
	DESC_सूचीECTION_DECRYPT_DECRYPT = 1,
	DESC_सूचीECTION_DECRYPT_ENCRYPT = 3,
	DESC_सूचीECTION_END = S32_MAX,
पूर्ण;

क्रमागत cc_dma_mode अणु
	DMA_MODE_शून्य		= -1,
	NO_DMA			= 0,
	DMA_SRAM		= 1,
	DMA_DLLI		= 2,
	DMA_MLLI		= 3,
	DMA_MODE_END		= S32_MAX,
पूर्ण;

क्रमागत cc_flow_mode अणु
	FLOW_MODE_शून्य		= -1,
	/* data flows */
	BYPASS			= 0,
	DIN_AES_DOUT		= 1,
	AES_to_HASH		= 2,
	AES_and_HASH		= 3,
	DIN_DES_DOUT		= 4,
	DES_to_HASH		= 5,
	DES_and_HASH		= 6,
	DIN_HASH		= 7,
	DIN_HASH_and_BYPASS	= 8,
	AESMAC_and_BYPASS	= 9,
	AES_to_HASH_and_DOUT	= 10,
	DIN_RC4_DOUT		= 11,
	DES_to_HASH_and_DOUT	= 12,
	AES_to_AES_to_HASH_and_DOUT	= 13,
	AES_to_AES_to_HASH	= 14,
	AES_to_HASH_and_AES	= 15,
	DIN_SM4_DOUT		= 16,
	DIN_AES_AESMAC		= 17,
	HASH_to_DOUT		= 18,
	/* setup flows */
	S_DIN_to_AES		= 32,
	S_DIN_to_AES2		= 33,
	S_DIN_to_DES		= 34,
	S_DIN_to_RC4		= 35,
	S_DIN_to_SM4		= 36,
	S_DIN_to_HASH		= 37,
	S_AES_to_DOUT		= 38,
	S_AES2_to_DOUT		= 39,
	S_SM4_to_DOUT		= 40,
	S_RC4_to_DOUT		= 41,
	S_DES_to_DOUT		= 42,
	S_HASH_to_DOUT		= 43,
	SET_FLOW_ID		= 44,
	FLOW_MODE_END = S32_MAX,
पूर्ण;

क्रमागत cc_setup_op अणु
	SETUP_LOAD_NOP		= 0,
	SETUP_LOAD_STATE0	= 1,
	SETUP_LOAD_STATE1	= 2,
	SETUP_LOAD_STATE2	= 3,
	SETUP_LOAD_KEY0		= 4,
	SETUP_LOAD_XEX_KEY	= 5,
	SETUP_WRITE_STATE0	= 8,
	SETUP_WRITE_STATE1	= 9,
	SETUP_WRITE_STATE2	= 10,
	SETUP_WRITE_STATE3	= 11,
	SETUP_OP_END = S32_MAX,
पूर्ण;

क्रमागत cc_hash_conf_pad अणु
	HASH_PADDING_DISABLED = 0,
	HASH_PADDING_ENABLED = 1,
	HASH_DIGEST_RESULT_LITTLE_ENDIAN = 2,
	HASH_CONFIG1_PADDING_RESERVE32 = S32_MAX,
पूर्ण;

क्रमागत cc_aes_mac_selector अणु
	AES_SK = 1,
	AES_CMAC_INIT = 2,
	AES_CMAC_SIZE0 = 3,
	AES_MAC_END = S32_MAX,
पूर्ण;

#घोषणा HW_KEY_MASK_CIPHER_DO	  0x3
#घोषणा HW_KEY_SHIFT_CIPHER_CFG2  2

/* HwCryptoKey[1:0] is mapped to cipher_करो[1:0] */
/* HwCryptoKey[2:3] is mapped to cipher_config2[1:0] */
क्रमागत cc_hw_crypto_key अणु
	USER_KEY = 0,			/* 0x0000 */
	ROOT_KEY = 1,			/* 0x0001 */
	PROVISIONING_KEY = 2,		/* 0x0010 */ /* ==KCP */
	SESSION_KEY = 3,		/* 0x0011 */
	RESERVED_KEY = 4,		/* NA */
	PLATFORM_KEY = 5,		/* 0x0101 */
	CUSTOMER_KEY = 6,		/* 0x0110 */
	KFDE0_KEY = 7,			/* 0x0111 */
	KFDE1_KEY = 9,			/* 0x1001 */
	KFDE2_KEY = 10,			/* 0x1010 */
	KFDE3_KEY = 11,			/* 0x1011 */
	END_OF_KEYS = S32_MAX,
पूर्ण;

#घोषणा CC_NUM_HW_KEY_SLOTS	4
#घोषणा CC_FIRST_HW_KEY_SLOT	0
#घोषणा CC_LAST_HW_KEY_SLOT	(CC_FIRST_HW_KEY_SLOT + CC_NUM_HW_KEY_SLOTS - 1)

#घोषणा CC_NUM_CPP_KEY_SLOTS	8
#घोषणा CC_FIRST_CPP_KEY_SLOT	16
#घोषणा CC_LAST_CPP_KEY_SLOT	(CC_FIRST_CPP_KEY_SLOT + \
					CC_NUM_CPP_KEY_SLOTS - 1)

क्रमागत cc_hw_aes_key_size अणु
	AES_128_KEY = 0,
	AES_192_KEY = 1,
	AES_256_KEY = 2,
	END_OF_AES_KEYS = S32_MAX,
पूर्ण;

क्रमागत cc_hash_cipher_pad अणु
	DO_NOT_PAD = 0,
	DO_PAD = 1,
	HASH_CIPHER_DO_PADDING_RESERVE32 = S32_MAX,
पूर्ण;

#घोषणा CC_CPP_DIN_ADDR	0xFF00FF00UL
#घोषणा CC_CPP_DIN_SIZE 0xFF00FFUL

/*****************************/
/* Descriptor packing macros */
/*****************************/

/**
 * hw_desc_init() - Init a HW descriptor काष्ठा
 * @pdesc: poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम hw_desc_init(काष्ठा cc_hw_desc *pdesc)
अणु
	स_रखो(pdesc, 0, माप(काष्ठा cc_hw_desc));
पूर्ण

/**
 * set_queue_last_ind_bit() - Indicate the end of current HW descriptors flow
 * and release the HW engines.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_queue_last_ind_bit(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[3] |= FIELD_PREP(WORD3_QUEUE_LAST_IND, 1);
पूर्ण

/**
 * set_din_type() - Set the DIN field of a HW descriptor
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @dma_mode: The DMA mode: NO_DMA, SRAM, DLLI, MLLI, CONSTANT
 * @addr: DIN address
 * @size: Data size in bytes
 * @axi_sec: AXI secure bit
 */
अटल अंतरभूत व्योम set_din_type(काष्ठा cc_hw_desc *pdesc,
				क्रमागत cc_dma_mode dma_mode, dma_addr_t addr,
				u32 size, क्रमागत cc_axi_sec axi_sec)
अणु
	pdesc->word[0] = lower_32_bits(addr);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	pdesc->word[5] |= FIELD_PREP(WORD5_DIN_ADDR_HIGH, upper_32_bits(addr));
#पूर्ण_अगर
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_DMA_MODE, dma_mode) |
				FIELD_PREP(WORD1_DIN_SIZE, size) |
				FIELD_PREP(WORD1_NS_BIT, axi_sec);
पूर्ण

/**
 * set_din_no_dma() - Set the DIN field of a HW descriptor to NO DMA mode.
 * Used क्रम NOP descriptor, रेजिस्टर patches and other special modes.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DIN address
 * @size: Data size in bytes
 */
अटल अंतरभूत व्योम set_din_no_dma(काष्ठा cc_hw_desc *pdesc, u32 addr, u32 size)
अणु
	pdesc->word[0] = addr;
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_SIZE, size);
पूर्ण

/**
 * set_cpp_crypto_key() - Setup the special CPP descriptor
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @slot: Slot number
 */
अटल अंतरभूत व्योम set_cpp_crypto_key(काष्ठा cc_hw_desc *pdesc, u8 slot)
अणु
	pdesc->word[0] |= CC_CPP_DIN_ADDR;

	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_SIZE, CC_CPP_DIN_SIZE);
	pdesc->word[1] |= FIELD_PREP(WORD1_LOCK_QUEUE, 1);

	pdesc->word[4] |= FIELD_PREP(WORD4_SETUP_OPERATION, slot);
पूर्ण

/**
 * set_din_sram() - Set the DIN field of a HW descriptor to SRAM mode.
 * Note: No need to check SRAM alignment since host requests करो not use SRAM and
 * the adaptor will enक्रमce alignment checks.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DIN address
 * @size: Data size in bytes
 */
अटल अंतरभूत व्योम set_din_sram(काष्ठा cc_hw_desc *pdesc, u32 addr, u32 size)
अणु
	pdesc->word[0] = addr;
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_SIZE, size) |
				FIELD_PREP(WORD1_DIN_DMA_MODE, DMA_SRAM);
पूर्ण

/**
 * set_din_स्थिर() - Set the DIN field of a HW descriptor to CONST mode
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @val: DIN स्थिर value
 * @size: Data size in bytes
 */
अटल अंतरभूत व्योम set_din_स्थिर(काष्ठा cc_hw_desc *pdesc, u32 val, u32 size)
अणु
	pdesc->word[0] = val;
	pdesc->word[1] |= FIELD_PREP(WORD1_DIN_CONST_VALUE, 1) |
			FIELD_PREP(WORD1_DIN_DMA_MODE, DMA_SRAM) |
			FIELD_PREP(WORD1_DIN_SIZE, size);
पूर्ण

/**
 * set_din_not_last_indication() - Set the DIN not last input data indicator
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_din_not_last_indication(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[1] |= FIELD_PREP(WORD1_NOT_LAST, 1);
पूर्ण

/**
 * set_करोut_type() - Set the DOUT field of a HW descriptor
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @dma_mode: The DMA mode: NO_DMA, SRAM, DLLI, MLLI, CONSTANT
 * @addr: DOUT address
 * @size: Data size in bytes
 * @axi_sec: AXI secure bit
 */
अटल अंतरभूत व्योम set_करोut_type(काष्ठा cc_hw_desc *pdesc,
				 क्रमागत cc_dma_mode dma_mode, dma_addr_t addr,
				 u32 size, क्रमागत cc_axi_sec axi_sec)
अणु
	pdesc->word[2] = lower_32_bits(addr);
#अगर_घोषित CONFIG_ARCH_DMA_ADDR_T_64BIT
	pdesc->word[5] |= FIELD_PREP(WORD5_DOUT_ADDR_HIGH, upper_32_bits(addr));
#पूर्ण_अगर
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_DMA_MODE, dma_mode) |
				FIELD_PREP(WORD3_DOUT_SIZE, size) |
				FIELD_PREP(WORD3_NS_BIT, axi_sec);
पूर्ण

/**
 * set_करोut_dlli() - Set the DOUT field of a HW descriptor to DLLI type
 * The LAST INDICATION is provided by the user
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DOUT address
 * @size: Data size in bytes
 * @axi_sec: AXI secure bit
 * @last_ind: The last indication bit
 */
अटल अंतरभूत व्योम set_करोut_dlli(काष्ठा cc_hw_desc *pdesc, dma_addr_t addr,
				 u32 size, क्रमागत cc_axi_sec axi_sec,
				 u32 last_ind)
अणु
	set_करोut_type(pdesc, DMA_DLLI, addr, size, axi_sec);
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_LAST_IND, last_ind);
पूर्ण

/**
 * set_करोut_mlli() - Set the DOUT field of a HW descriptor to MLLI type
 * The LAST INDICATION is provided by the user
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DOUT address
 * @size: Data size in bytes
 * @axi_sec: AXI secure bit
 * @last_ind: The last indication bit
 */
अटल अंतरभूत व्योम set_करोut_mlli(काष्ठा cc_hw_desc *pdesc, u32 addr, u32 size,
				 क्रमागत cc_axi_sec axi_sec, bool last_ind)
अणु
	set_करोut_type(pdesc, DMA_MLLI, addr, size, axi_sec);
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_LAST_IND, last_ind);
पूर्ण

/**
 * set_करोut_no_dma() - Set the DOUT field of a HW descriptor to NO DMA mode.
 * Used क्रम NOP descriptor, रेजिस्टर patches and other special modes.
 *
 * @pdesc: poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DOUT address
 * @size: Data size in bytes
 * @ग_लिखो_enable: Enables a ग_लिखो operation to a रेजिस्टर
 */
अटल अंतरभूत व्योम set_करोut_no_dma(काष्ठा cc_hw_desc *pdesc, u32 addr,
				   u32 size, bool ग_लिखो_enable)
अणु
	pdesc->word[2] = addr;
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_SIZE, size) |
			FIELD_PREP(WORD3_DOUT_LAST_IND, ग_लिखो_enable);
पूर्ण

/**
 * set_xor_val() - Set the word क्रम the XOR operation.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @val: XOR data value
 */
अटल अंतरभूत व्योम set_xor_val(काष्ठा cc_hw_desc *pdesc, u32 val)
अणु
	pdesc->word[2] = val;
पूर्ण

/**
 * set_xor_active() - Set the XOR indicator bit in the descriptor
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_xor_active(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[3] |= FIELD_PREP(WORD3_HASH_XOR_BIT, 1);
पूर्ण

/**
 * set_aes_not_hash_mode() - Select the AES engine instead of HASH engine when
 * setting up combined mode with AES XCBC MAC
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_aes_not_hash_mode(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_AES_SEL_N_HASH, 1);
पूर्ण

/**
 * set_aes_xor_crypto_key() - Set aes xor crypto key, which in some scenarios
 * selects the SM3 engine
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_aes_xor_crypto_key(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_AES_XOR_CRYPTO_KEY, 1);
पूर्ण

/**
 * set_करोut_sram() - Set the DOUT field of a HW descriptor to SRAM mode
 * Note: No need to check SRAM alignment since host requests करो not use SRAM and
 * the adaptor will enक्रमce alignment checks.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @addr: DOUT address
 * @size: Data size in bytes
 */
अटल अंतरभूत व्योम set_करोut_sram(काष्ठा cc_hw_desc *pdesc, u32 addr, u32 size)
अणु
	pdesc->word[2] = addr;
	pdesc->word[3] |= FIELD_PREP(WORD3_DOUT_DMA_MODE, DMA_SRAM) |
			FIELD_PREP(WORD3_DOUT_SIZE, size);
पूर्ण

/**
 * set_xex_data_unit_size() - Set the data unit size क्रम XEX mode in
 * data_out_addr[15:0]
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @size: Data unit size क्रम XEX mode
 */
अटल अंतरभूत व्योम set_xex_data_unit_size(काष्ठा cc_hw_desc *pdesc, u32 size)
अणु
	pdesc->word[2] = size;
पूर्ण

/**
 * set_multi2_num_rounds() - Set the number of rounds क्रम Multi2 in
 * data_out_addr[15:0]
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @num: Number of rounds क्रम Multi2
 */
अटल अंतरभूत व्योम set_multi2_num_rounds(काष्ठा cc_hw_desc *pdesc, u32 num)
अणु
	pdesc->word[2] = num;
पूर्ण

/**
 * set_flow_mode() - Set the flow mode.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
अटल अंतरभूत व्योम set_flow_mode(काष्ठा cc_hw_desc *pdesc,
				 क्रमागत cc_flow_mode mode)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_DATA_FLOW_MODE, mode);
पूर्ण

/**
 * set_cipher_mode() - Set the cipher mode.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
अटल अंतरभूत व्योम set_cipher_mode(काष्ठा cc_hw_desc *pdesc, पूर्णांक mode)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_MODE, mode);
पूर्ण

/**
 * set_hash_cipher_mode() - Set the cipher mode क्रम hash algorithms.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @cipher_mode: Any one of the modes defined in [CC7x-DESC]
 * @hash_mode: specअगरies which hash is being handled
 */
अटल अंतरभूत व्योम set_hash_cipher_mode(काष्ठा cc_hw_desc *pdesc,
					क्रमागत drv_cipher_mode cipher_mode,
					क्रमागत drv_hash_mode hash_mode)
अणु
	set_cipher_mode(pdesc, cipher_mode);
	अगर (hash_mode == DRV_HASH_SM3)
		set_aes_xor_crypto_key(pdesc);
पूर्ण

/**
 * set_cipher_config0() - Set the cipher configuration fields.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @mode: Any one of the modes defined in [CC7x-DESC]
 */
अटल अंतरभूत व्योम set_cipher_config0(काष्ठा cc_hw_desc *pdesc, पूर्णांक mode)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_CONF0, mode);
पूर्ण

/**
 * set_cipher_config1() - Set the cipher configuration fields.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @config: Padding mode
 */
अटल अंतरभूत व्योम set_cipher_config1(काष्ठा cc_hw_desc *pdesc,
				      क्रमागत cc_hash_conf_pad config)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_CONF1, config);
पूर्ण

/**
 * set_hw_crypto_key() - Set HW key configuration fields.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @hw_key: The HW key slot asdefined in क्रमागत cc_hw_crypto_key
 */
अटल अंतरभूत व्योम set_hw_crypto_key(काष्ठा cc_hw_desc *pdesc,
				     क्रमागत cc_hw_crypto_key hw_key)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_DO,
				     (hw_key & HW_KEY_MASK_CIPHER_DO)) |
			FIELD_PREP(WORD4_CIPHER_CONF2,
				   (hw_key >> HW_KEY_SHIFT_CIPHER_CFG2));
पूर्ण

/**
 * set_bytes_swap() - Set byte order of all setup-finalize descriptors.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @config: True to enable byte swapping
 */
अटल अंतरभूत व्योम set_bytes_swap(काष्ठा cc_hw_desc *pdesc, bool config)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_BYTES_SWAP, config);
पूर्ण

/**
 * set_cmac_size0_mode() - Set CMAC_SIZE0 mode.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 */
अटल अंतरभूत व्योम set_cmac_size0_mode(काष्ठा cc_hw_desc *pdesc)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CMAC_SIZE0, 1);
पूर्ण

/**
 * set_key_size() - Set key size descriptor field.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @size: Key size in bytes (NOT size code)
 */
अटल अंतरभूत व्योम set_key_size(काष्ठा cc_hw_desc *pdesc, u32 size)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_KEY_SIZE, size);
पूर्ण

/**
 * set_key_size_aes() - Set AES key size.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @size: Key size in bytes (NOT size code)
 */
अटल अंतरभूत व्योम set_key_size_aes(काष्ठा cc_hw_desc *pdesc, u32 size)
अणु
	set_key_size(pdesc, ((size >> 3) - 2));
पूर्ण

/**
 * set_key_size_des() - Set DES key size.
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @size: Key size in bytes (NOT size code)
 */
अटल अंतरभूत व्योम set_key_size_des(काष्ठा cc_hw_desc *pdesc, u32 size)
अणु
	set_key_size(pdesc, ((size >> 3) - 1));
पूर्ण

/**
 * set_setup_mode() - Set the descriptor setup mode
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @mode: Any one of the setup modes defined in [CC7x-DESC]
 */
अटल अंतरभूत व्योम set_setup_mode(काष्ठा cc_hw_desc *pdesc,
				  क्रमागत cc_setup_op mode)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_SETUP_OPERATION, mode);
पूर्ण

/**
 * set_cipher_करो() - Set the descriptor cipher DO
 *
 * @pdesc: Poपूर्णांकer to HW descriptor काष्ठा
 * @config: Any one of the cipher करो defined in [CC7x-DESC]
 */
अटल अंतरभूत व्योम set_cipher_करो(काष्ठा cc_hw_desc *pdesc,
				 क्रमागत cc_hash_cipher_pad config)
अणु
	pdesc->word[4] |= FIELD_PREP(WORD4_CIPHER_DO,
				(config & HW_KEY_MASK_CIPHER_DO));
पूर्ण

#पूर्ण_अगर /*__CC_HW_QUEUE_DEFS_H__*/
