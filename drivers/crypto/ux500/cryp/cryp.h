<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen <shujuan.chen@stericsson.com> क्रम ST-Ericsson.
 * Author: Jonas Linde <jonas.linde@stericsson.com> क्रम ST-Ericsson.
 * Author: Joakim Bech <joakim.xx.bech@stericsson.com> क्रम ST-Ericsson.
 * Author: Berne Hebark <berne.herbark@stericsson.com> क्रम ST-Ericsson.
 * Author: Niklas Hernaeus <niklas.hernaeus@stericsson.com> क्रम ST-Ericsson.
 */

#अगर_अघोषित _CRYP_H_
#घोषणा _CRYP_H_

#समावेश <linux/completion.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/klist.h>
#समावेश <linux/mutex.h>

#घोषणा DEV_DBG_NAME "crypX crypX:"

/* CRYP enable/disable */
क्रमागत cryp_crypen अणु
	CRYP_CRYPEN_DISABLE = 0,
	CRYP_CRYPEN_ENABLE = 1
पूर्ण;

/* CRYP Start Computation enable/disable */
क्रमागत cryp_start अणु
	CRYP_START_DISABLE = 0,
	CRYP_START_ENABLE = 1
पूर्ण;

/* CRYP Init Signal enable/disable */
क्रमागत cryp_init अणु
	CRYP_INIT_DISABLE = 0,
	CRYP_INIT_ENABLE = 1
पूर्ण;

/* Cryp State enable/disable */
क्रमागत cryp_state अणु
	CRYP_STATE_DISABLE = 0,
	CRYP_STATE_ENABLE = 1
पूर्ण;

/* Key preparation bit enable */
क्रमागत cryp_key_prep अणु
	KSE_DISABLED = 0,
	KSE_ENABLED = 1
पूर्ण;

/* Key size क्रम AES */
#घोषणा	CRYP_KEY_SIZE_128 (0)
#घोषणा	CRYP_KEY_SIZE_192 (1)
#घोषणा	CRYP_KEY_SIZE_256 (2)

/* AES modes */
क्रमागत cryp_algo_mode अणु
	CRYP_ALGO_TDES_ECB,
	CRYP_ALGO_TDES_CBC,
	CRYP_ALGO_DES_ECB,
	CRYP_ALGO_DES_CBC,
	CRYP_ALGO_AES_ECB,
	CRYP_ALGO_AES_CBC,
	CRYP_ALGO_AES_CTR,
	CRYP_ALGO_AES_XTS
पूर्ण;

/* Cryp Encryption or Decryption */
क्रमागत cryp_algorithm_dir अणु
	CRYP_ALGORITHM_ENCRYPT,
	CRYP_ALGORITHM_DECRYPT
पूर्ण;

/* Hardware access method */
क्रमागत cryp_mode अणु
	CRYP_MODE_POLLING,
	CRYP_MODE_INTERRUPT,
	CRYP_MODE_DMA
पूर्ण;

/**
 * काष्ठा cryp_config -
 * @keysize: Key size क्रम AES
 * @algomode: AES modes
 * @algodir: Cryp Encryption or Decryption
 *
 * CRYP configuration काष्ठाure to be passed to set configuration
 */
काष्ठा cryp_config अणु
	पूर्णांक keysize;
	क्रमागत cryp_algo_mode algomode;
	क्रमागत cryp_algorithm_dir algodir;
पूर्ण;

/**
 * काष्ठा cryp_protection_config -
 * @privilege_access: Privileged cryp state enable/disable
 * @secure_access: Secure cryp state enable/disable
 *
 * Protection configuration काष्ठाure क्रम setting privilage access
 */
काष्ठा cryp_protection_config अणु
	क्रमागत cryp_state privilege_access;
	क्रमागत cryp_state secure_access;
पूर्ण;

/* Cryp status */
क्रमागत cryp_status_id अणु
	CRYP_STATUS_BUSY = 0x10,
	CRYP_STATUS_OUTPUT_FIFO_FULL = 0x08,
	CRYP_STATUS_OUTPUT_FIFO_NOT_EMPTY = 0x04,
	CRYP_STATUS_INPUT_FIFO_NOT_FULL = 0x02,
	CRYP_STATUS_INPUT_FIFO_EMPTY = 0x01
पूर्ण;

/* Cryp DMA पूर्णांकerface */
#घोषणा CRYP_DMA_TX_FIFO	0x08
#घोषणा CRYP_DMA_RX_FIFO	0x10

क्रमागत cryp_dma_req_type अणु
	CRYP_DMA_DISABLE_BOTH,
	CRYP_DMA_ENABLE_IN_DATA,
	CRYP_DMA_ENABLE_OUT_DATA,
	CRYP_DMA_ENABLE_BOTH_सूचीECTIONS
पूर्ण;

क्रमागत cryp_dma_channel अणु
	CRYP_DMA_RX = 0,
	CRYP_DMA_TX
पूर्ण;

/* Key रेजिस्टरs */
क्रमागत cryp_key_reg_index अणु
	CRYP_KEY_REG_1,
	CRYP_KEY_REG_2,
	CRYP_KEY_REG_3,
	CRYP_KEY_REG_4
पूर्ण;

/* Key रेजिस्टर left and right */
काष्ठा cryp_key_value अणु
	u32 key_value_left;
	u32 key_value_right;
पूर्ण;

/* Cryp Initialization काष्ठाure */
क्रमागत cryp_init_vector_index अणु
	CRYP_INIT_VECTOR_INDEX_0,
	CRYP_INIT_VECTOR_INDEX_1
पूर्ण;

/* काष्ठा cryp_init_vector_value -
 * @init_value_left
 * @init_value_right
 * */
काष्ठा cryp_init_vector_value अणु
	u32 init_value_left;
	u32 init_value_right;
पूर्ण;

/**
 * काष्ठा cryp_device_context - काष्ठाure क्रम a cryp context.
 * @cr: control रेजिस्टर
 * @dmacr: DMA control रेजिस्टर
 * @imsc: Interrupt mask set/clear रेजिस्टर
 * @key_1_l: Key 1l रेजिस्टर
 * @key_1_r: Key 1r रेजिस्टर
 * @key_2_l: Key 2l रेजिस्टर
 * @key_2_r: Key 2r रेजिस्टर
 * @key_3_l: Key 3l रेजिस्टर
 * @key_3_r: Key 3r रेजिस्टर
 * @key_4_l: Key 4l रेजिस्टर
 * @key_4_r: Key 4r रेजिस्टर
 * @init_vect_0_l: Initialization vector 0l रेजिस्टर
 * @init_vect_0_r: Initialization vector 0r रेजिस्टर
 * @init_vect_1_l: Initialization vector 1l रेजिस्टर
 * @init_vect_1_r: Initialization vector 0r रेजिस्टर
 * @din: Data in रेजिस्टर
 * @करोut: Data out रेजिस्टर
 *
 * CRYP घातer management specअगरc काष्ठाure.
 */
काष्ठा cryp_device_context अणु
	u32 cr;
	u32 dmacr;
	u32 imsc;

	u32 key_1_l;
	u32 key_1_r;
	u32 key_2_l;
	u32 key_2_r;
	u32 key_3_l;
	u32 key_3_r;
	u32 key_4_l;
	u32 key_4_r;

	u32 init_vect_0_l;
	u32 init_vect_0_r;
	u32 init_vect_1_l;
	u32 init_vect_1_r;

	u32 din;
	u32 करोut;
पूर्ण;

काष्ठा cryp_dma अणु
	dma_cap_mask_t mask;
	काष्ठा completion cryp_dma_complete;
	काष्ठा dma_chan *chan_cryp2mem;
	काष्ठा dma_chan *chan_mem2cryp;
	काष्ठा stedma40_chan_cfg *cfg_cryp2mem;
	काष्ठा stedma40_chan_cfg *cfg_mem2cryp;
	पूर्णांक sg_src_len;
	पूर्णांक sg_dst_len;
	काष्ठा scatterlist *sg_src;
	काष्ठा scatterlist *sg_dst;
	पूर्णांक nents_src;
	पूर्णांक nents_dst;
पूर्ण;

/**
 * काष्ठा cryp_device_data - काष्ठाure क्रम a cryp device.
 * @base: Poपूर्णांकer to भव base address of the cryp device.
 * @phybase: Poपूर्णांकer to physical memory location of the cryp device.
 * @dev: Poपूर्णांकer to the devices dev काष्ठाure.
 * @clk: Poपूर्णांकer to the device's घड़ी control.
 * @pwr_regulator: Poपूर्णांकer to the device's घातer control.
 * @घातer_status: Current status of the घातer.
 * @ctx_lock: Lock क्रम current_ctx.
 * @current_ctx: Poपूर्णांकer to the currently allocated context.
 * @list_node: For inclusion पूर्णांकo a klist.
 * @dma: The dma काष्ठाure holding channel configuration.
 * @घातer_state: TRUE = घातer state on, FALSE = घातer state off.
 * @घातer_state_spinlock: Spinlock क्रम घातer_state.
 * @restore_dev_ctx: TRUE = saved ctx, FALSE = no saved ctx.
 */
काष्ठा cryp_device_data अणु
	काष्ठा cryp_रेजिस्टर __iomem *base;
	phys_addr_t phybase;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा regulator *pwr_regulator;
	पूर्णांक घातer_status;
	spinlock_t ctx_lock;
	काष्ठा cryp_ctx *current_ctx;
	काष्ठा klist_node list_node;
	काष्ठा cryp_dma dma;
	bool घातer_state;
	spinlock_t घातer_state_spinlock;
	bool restore_dev_ctx;
पूर्ण;

व्योम cryp_रुको_until_करोne(काष्ठा cryp_device_data *device_data);

/* Initialization functions */

पूर्णांक cryp_check(काष्ठा cryp_device_data *device_data);

व्योम cryp_activity(काष्ठा cryp_device_data *device_data,
		   क्रमागत cryp_crypen cryp_crypen);

व्योम cryp_flush_inoutfअगरo(काष्ठा cryp_device_data *device_data);

पूर्णांक cryp_set_configuration(काष्ठा cryp_device_data *device_data,
			   काष्ठा cryp_config *cryp_config,
			   u32 *control_रेजिस्टर);

व्योम cryp_configure_क्रम_dma(काष्ठा cryp_device_data *device_data,
			    क्रमागत cryp_dma_req_type dma_req);

पूर्णांक cryp_configure_key_values(काष्ठा cryp_device_data *device_data,
			      क्रमागत cryp_key_reg_index key_reg_index,
			      काष्ठा cryp_key_value key_value);

पूर्णांक cryp_configure_init_vector(काष्ठा cryp_device_data *device_data,
			       क्रमागत cryp_init_vector_index
			       init_vector_index,
			       काष्ठा cryp_init_vector_value
			       init_vector_value);

पूर्णांक cryp_configure_protection(काष्ठा cryp_device_data *device_data,
			      काष्ठा cryp_protection_config *p_protect_config);

/* Power management funtions */
व्योम cryp_save_device_context(काष्ठा cryp_device_data *device_data,
			      काष्ठा cryp_device_context *ctx,
			      पूर्णांक cryp_mode);

व्योम cryp_restore_device_context(काष्ठा cryp_device_data *device_data,
				 काष्ठा cryp_device_context *ctx);

/* Data transfer and status bits. */
पूर्णांक cryp_is_logic_busy(काष्ठा cryp_device_data *device_data);

पूर्णांक cryp_get_status(काष्ठा cryp_device_data *device_data);

/**
 * cryp_ग_लिखो_indata - This routine ग_लिखोs 32 bit data पूर्णांकo the data input
 *		       रेजिस्टर of the cryptography IP.
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @ग_लिखो_data: Data to ग_लिखो.
 */
पूर्णांक cryp_ग_लिखो_indata(काष्ठा cryp_device_data *device_data, u32 ग_लिखो_data);

/**
 * cryp_पढ़ो_outdata - This routine पढ़ोs the data from the data output
 *		       रेजिस्टर of the CRYP logic
 * @device_data: Poपूर्णांकer to the device data काष्ठा क्रम base address.
 * @पढ़ो_data: Read the data from the output FIFO.
 */
पूर्णांक cryp_पढ़ो_outdata(काष्ठा cryp_device_data *device_data, u32 *पढ़ो_data);

#पूर्ण_अगर /* _CRYP_H_ */
