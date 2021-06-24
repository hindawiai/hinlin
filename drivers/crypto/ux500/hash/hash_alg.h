<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson SA 2010
 * Author: Shujuan Chen (shujuan.chen@stericsson.com)
 * Author: Joakim Bech (joakim.xx.bech@stericsson.com)
 * Author: Berne Hebark (berne.hebark@stericsson.com))
 */
#अगर_अघोषित _HASH_ALG_H
#घोषणा _HASH_ALG_H

#समावेश <linux/bitops.h>

#घोषणा HASH_BLOCK_SIZE			64
#घोषणा HASH_DMA_FIFO			4
#घोषणा HASH_DMA_ALIGN_SIZE		4
#घोषणा HASH_DMA_PERFORMANCE_MIN_SIZE	1024
#घोषणा HASH_BYTES_PER_WORD		4

/* Maximum value of the length's high word */
#घोषणा HASH_HIGH_WORD_MAX_VAL		0xFFFFFFFFUL

/* Power on Reset values HASH रेजिस्टरs */
#घोषणा HASH_RESET_CR_VALUE		0x0
#घोषणा HASH_RESET_STR_VALUE		0x0

/* Number of context swap रेजिस्टरs */
#घोषणा HASH_CSR_COUNT			52

#घोषणा HASH_RESET_CSRX_REG_VALUE	0x0
#घोषणा HASH_RESET_CSFULL_REG_VALUE	0x0
#घोषणा HASH_RESET_CSDATAIN_REG_VALUE	0x0

#घोषणा HASH_RESET_INDEX_VAL		0x0
#घोषणा HASH_RESET_BIT_INDEX_VAL	0x0
#घोषणा HASH_RESET_BUFFER_VAL		0x0
#घोषणा HASH_RESET_LEN_HIGH_VAL		0x0
#घोषणा HASH_RESET_LEN_LOW_VAL		0x0

/* Control रेजिस्टर bitfields */
#घोषणा HASH_CR_RESUME_MASK	0x11FCF

#घोषणा HASH_CR_SWITCHON_POS	31
#घोषणा HASH_CR_SWITCHON_MASK	BIT(31)

#घोषणा HASH_CR_EMPTYMSG_POS	20
#घोषणा HASH_CR_EMPTYMSG_MASK	BIT(20)

#घोषणा HASH_CR_DINF_POS	12
#घोषणा HASH_CR_DINF_MASK	BIT(12)

#घोषणा HASH_CR_NBW_POS		8
#घोषणा HASH_CR_NBW_MASK	0x00000F00UL

#घोषणा HASH_CR_LKEY_POS	16
#घोषणा HASH_CR_LKEY_MASK	BIT(16)

#घोषणा HASH_CR_ALGO_POS	7
#घोषणा HASH_CR_ALGO_MASK	BIT(7)

#घोषणा HASH_CR_MODE_POS	6
#घोषणा HASH_CR_MODE_MASK	BIT(6)

#घोषणा HASH_CR_DATAFORM_POS	4
#घोषणा HASH_CR_DATAFORM_MASK	(BIT(4) | BIT(5))

#घोषणा HASH_CR_DMAE_POS	3
#घोषणा HASH_CR_DMAE_MASK	BIT(3)

#घोषणा HASH_CR_INIT_POS	2
#घोषणा HASH_CR_INIT_MASK	BIT(2)

#घोषणा HASH_CR_PRIVN_POS	1
#घोषणा HASH_CR_PRIVN_MASK	BIT(1)

#घोषणा HASH_CR_SECN_POS	0
#घोषणा HASH_CR_SECN_MASK	BIT(0)

/* Start रेजिस्टर bitfields */
#घोषणा HASH_STR_DCAL_POS	8
#घोषणा HASH_STR_DCAL_MASK	BIT(8)
#घोषणा HASH_STR_DEFAULT	0x0

#घोषणा HASH_STR_NBLW_POS	0
#घोषणा HASH_STR_NBLW_MASK	0x0000001FUL

#घोषणा HASH_NBLW_MAX_VAL	0x1F

/* PrimeCell IDs */
#घोषणा HASH_P_ID0		0xE0
#घोषणा HASH_P_ID1		0x05
#घोषणा HASH_P_ID2		0x38
#घोषणा HASH_P_ID3		0x00
#घोषणा HASH_CELL_ID0		0x0D
#घोषणा HASH_CELL_ID1		0xF0
#घोषणा HASH_CELL_ID2		0x05
#घोषणा HASH_CELL_ID3		0xB1

#घोषणा HASH_SET_BITS(reg_name, mask)	\
	ग_लिखोl_relaxed((पढ़ोl_relaxed(reg_name) | mask), reg_name)

#घोषणा HASH_CLEAR_BITS(reg_name, mask)	\
	ग_लिखोl_relaxed((पढ़ोl_relaxed(reg_name) & ~mask), reg_name)

#घोषणा HASH_PUT_BITS(reg, val, shअगरt, mask)	\
	ग_लिखोl_relaxed(((पढ़ोl(reg) & ~(mask)) |	\
		(((u32)val << shअगरt) & (mask))), reg)

#घोषणा HASH_SET_DIN(val, len)	ग_लिखोsl(&device_data->base->din, (val), (len))

#घोषणा HASH_INITIALIZE			\
	HASH_PUT_BITS(			\
		&device_data->base->cr,	\
		0x01, HASH_CR_INIT_POS,	\
		HASH_CR_INIT_MASK)

#घोषणा HASH_SET_DATA_FORMAT(data_क्रमmat)				\
		HASH_PUT_BITS(						\
			&device_data->base->cr,				\
			(u32) (data_क्रमmat), HASH_CR_DATAFORM_POS,	\
			HASH_CR_DATAFORM_MASK)
#घोषणा HASH_SET_NBLW(val)					\
		HASH_PUT_BITS(					\
			&device_data->base->str,		\
			(u32) (val), HASH_STR_NBLW_POS,		\
			HASH_STR_NBLW_MASK)
#घोषणा HASH_SET_DCAL					\
		HASH_PUT_BITS(				\
			&device_data->base->str,	\
			0x01, HASH_STR_DCAL_POS,	\
			HASH_STR_DCAL_MASK)

/* Hardware access method */
क्रमागत hash_mode अणु
	HASH_MODE_CPU,
	HASH_MODE_DMA
पूर्ण;

/**
 * काष्ठा uपूर्णांक64 - Structure to handle 64 bits पूर्णांकegers.
 * @high_word:	Most signअगरicant bits.
 * @low_word:	Least signअगरicant bits.
 *
 * Used to handle 64 bits पूर्णांकegers.
 */
काष्ठा uपूर्णांक64 अणु
	u32 high_word;
	u32 low_word;
पूर्ण;

/**
 * काष्ठा hash_रेजिस्टर - Contains all रेजिस्टरs in ux500 hash hardware.
 * @cr:		HASH control रेजिस्टर (0x000).
 * @din:	HASH data input रेजिस्टर (0x004).
 * @str:	HASH start रेजिस्टर (0x008).
 * @hx:		HASH digest रेजिस्टर 0..7 (0x00c-0x01C).
 * @padding0:	Reserved (0x02C).
 * @itcr:	Integration test control रेजिस्टर (0x080).
 * @itip:	Integration test input रेजिस्टर (0x084).
 * @itop:	Integration test output रेजिस्टर (0x088).
 * @padding1:	Reserved (0x08C).
 * @csfull:	HASH context full रेजिस्टर (0x0F8).
 * @csdatain:	HASH context swap data input रेजिस्टर (0x0FC).
 * @csrx:	HASH context swap रेजिस्टर 0..51 (0x100-0x1CC).
 * @padding2:	Reserved (0x1D0).
 * @periphid0:	HASH peripheral identअगरication रेजिस्टर 0 (0xFE0).
 * @periphid1:	HASH peripheral identअगरication रेजिस्टर 1 (0xFE4).
 * @periphid2:	HASH peripheral identअगरication रेजिस्टर 2 (0xFE8).
 * @periphid3:	HASH peripheral identअगरication रेजिस्टर 3 (0xFEC).
 * @cellid0:	HASH PCell identअगरication रेजिस्टर 0 (0xFF0).
 * @cellid1:	HASH PCell identअगरication रेजिस्टर 1 (0xFF4).
 * @cellid2:	HASH PCell identअगरication रेजिस्टर 2 (0xFF8).
 * @cellid3:	HASH PCell identअगरication रेजिस्टर 3 (0xFFC).
 *
 * The device communicates to the HASH via 32-bit-wide control रेजिस्टरs
 * accessible via the 32-bit width AMBA rev. 2.0 AHB Bus. Below is a काष्ठाure
 * with the रेजिस्टरs used.
 */
काष्ठा hash_रेजिस्टर अणु
	u32 cr;
	u32 din;
	u32 str;
	u32 hx[8];

	u32 padding0[(0x080 - 0x02C) / माप(u32)];

	u32 itcr;
	u32 itip;
	u32 itop;

	u32 padding1[(0x0F8 - 0x08C) / माप(u32)];

	u32 csfull;
	u32 csdatain;
	u32 csrx[HASH_CSR_COUNT];

	u32 padding2[(0xFE0 - 0x1D0) / माप(u32)];

	u32 periphid0;
	u32 periphid1;
	u32 periphid2;
	u32 periphid3;

	u32 cellid0;
	u32 cellid1;
	u32 cellid2;
	u32 cellid3;
पूर्ण;

/**
 * काष्ठा hash_state - Hash context state.
 * @temp_cr:	Temporary HASH Control Register.
 * @str_reg:	HASH Start Register.
 * @din_reg:	HASH Data Input Register.
 * @csr[52]:	HASH Context Swap Registers 0-39.
 * @csfull:	HASH Context Swap Registers 40 ie Status flags.
 * @csdatain:	HASH Context Swap Registers 41 ie Input data.
 * @buffer:	Working buffer क्रम messages going to the hardware.
 * @length:	Length of the part of message hashed so far (न्यूनमान(N/64) * 64).
 * @index:	Valid number of bytes in buffer (N % 64).
 * @bit_index:	Valid number of bits in buffer (N % 8).
 *
 * This काष्ठाure is used between context चयनes, i.e. when ongoing jobs are
 * पूर्णांकerupted with new jobs. When this happens we need to store पूर्णांकermediate
 * results in software.
 *
 * WARNING: "index" is the  member of the काष्ठाure, to be sure  that "buffer"
 * is aligned on a 4-bytes boundary. This is highly implementation dependent
 * and MUST be checked whenever this code is ported on new platक्रमms.
 */
काष्ठा hash_state अणु
	u32		temp_cr;
	u32		str_reg;
	u32		din_reg;
	u32		csr[52];
	u32		csfull;
	u32		csdatain;
	u32		buffer[HASH_BLOCK_SIZE / माप(u32)];
	काष्ठा uपूर्णांक64	length;
	u8		index;
	u8		bit_index;
पूर्ण;

/**
 * क्रमागत hash_device_id - HASH device ID.
 * @HASH_DEVICE_ID_0: Hash hardware with ID 0
 * @HASH_DEVICE_ID_1: Hash hardware with ID 1
 */
क्रमागत hash_device_id अणु
	HASH_DEVICE_ID_0 = 0,
	HASH_DEVICE_ID_1 = 1
पूर्ण;

/**
 * क्रमागत hash_data_क्रमmat - HASH data क्रमmat.
 * @HASH_DATA_32_BITS:	32 bits data क्रमmat
 * @HASH_DATA_16_BITS:	16 bits data क्रमmat
 * @HASH_DATA_8_BITS:	8 bits data क्रमmat.
 * @HASH_DATA_1_BITS:	1 bit data क्रमmat.
 */
क्रमागत hash_data_क्रमmat अणु
	HASH_DATA_32_BITS	= 0x0,
	HASH_DATA_16_BITS	= 0x1,
	HASH_DATA_8_BITS	= 0x2,
	HASH_DATA_1_BIT		= 0x3
पूर्ण;

/**
 * क्रमागत hash_algo - Enumeration क्रम selecting between SHA1 or SHA2 algorithm.
 * @HASH_ALGO_SHA1: Indicates that SHA1 is used.
 * @HASH_ALGO_SHA2: Indicates that SHA2 (SHA256) is used.
 */
क्रमागत hash_algo अणु
	HASH_ALGO_SHA1		= 0x0,
	HASH_ALGO_SHA256	= 0x1
पूर्ण;

/**
 * क्रमागत hash_op - Enumeration क्रम selecting between HASH or HMAC mode.
 * @HASH_OPER_MODE_HASH: Indicates usage of normal HASH mode.
 * @HASH_OPER_MODE_HMAC: Indicates usage of HMAC.
 */
क्रमागत hash_op अणु
	HASH_OPER_MODE_HASH = 0x0,
	HASH_OPER_MODE_HMAC = 0x1
पूर्ण;

/**
 * काष्ठा hash_config - Configuration data क्रम the hardware.
 * @data_क्रमmat:	Format of data entered पूर्णांकo the hash data in रेजिस्टर.
 * @algorithm:		Algorithm selection bit.
 * @oper_mode:		Operating mode selection bit.
 */
काष्ठा hash_config अणु
	पूर्णांक data_क्रमmat;
	पूर्णांक algorithm;
	पूर्णांक oper_mode;
पूर्ण;

/**
 * काष्ठा hash_dma - Structure used क्रम dma.
 * @mask:		DMA capabilities biपंचांगap mask.
 * @complete:		Used to मुख्यtain state क्रम a "completion".
 * @chan_mem2hash:	DMA channel.
 * @cfg_mem2hash:	DMA channel configuration.
 * @sg_len:		Scatterlist length.
 * @sg:			Scatterlist.
 * @nents:		Number of sg entries.
 */
काष्ठा hash_dma अणु
	dma_cap_mask_t		mask;
	काष्ठा completion	complete;
	काष्ठा dma_chan		*chan_mem2hash;
	व्योम			*cfg_mem2hash;
	पूर्णांक			sg_len;
	काष्ठा scatterlist	*sg;
	पूर्णांक			nents;
पूर्ण;

/**
 * काष्ठा hash_ctx - The context used क्रम hash calculations.
 * @key:	The key used in the operation.
 * @keylen:	The length of the key.
 * @state:	The state of the current calculations.
 * @config:	The current configuration.
 * @digestsize:	The size of current digest.
 * @device:	Poपूर्णांकer to the device काष्ठाure.
 */
काष्ठा hash_ctx अणु
	u8			*key;
	u32			keylen;
	काष्ठा hash_config	config;
	पूर्णांक			digestsize;
	काष्ठा hash_device_data	*device;
पूर्ण;

/**
 * काष्ठा hash_ctx - The request context used क्रम hash calculations.
 * @state:	The state of the current calculations.
 * @dma_mode:	Used in special हालs (workaround), e.g. need to change to
 *		cpu mode, अगर not supported/working in dma mode.
 * @updated:	Indicates अगर hardware is initialized क्रम new operations.
 */
काष्ठा hash_req_ctx अणु
	काष्ठा hash_state	state;
	bool			dma_mode;
	u8			updated;
पूर्ण;

/**
 * काष्ठा hash_device_data - काष्ठाure क्रम a hash device.
 * @base:		Poपूर्णांकer to भव base address of the hash device.
 * @phybase:		Poपूर्णांकer to physical memory location of the hash device.
 * @list_node:		For inclusion in klist.
 * @dev:		Poपूर्णांकer to the device dev काष्ठाure.
 * @ctx_lock:		Spinlock क्रम current_ctx.
 * @current_ctx:	Poपूर्णांकer to the currently allocated context.
 * @घातer_state:	TRUE = घातer state on, FALSE = घातer state off.
 * @घातer_state_lock:	Spinlock क्रम घातer_state.
 * @regulator:		Poपूर्णांकer to the device's घातer control.
 * @clk:		Poपूर्णांकer to the device's घड़ी control.
 * @restore_dev_state:	TRUE = saved state, FALSE = no saved state.
 * @dma:		Structure used क्रम dma.
 */
काष्ठा hash_device_data अणु
	काष्ठा hash_रेजिस्टर __iomem	*base;
	phys_addr_t             phybase;
	काष्ठा klist_node	list_node;
	काष्ठा device		*dev;
	spinlock_t		ctx_lock;
	काष्ठा hash_ctx		*current_ctx;
	bool			घातer_state;
	spinlock_t		घातer_state_lock;
	काष्ठा regulator	*regulator;
	काष्ठा clk		*clk;
	bool			restore_dev_state;
	काष्ठा hash_state	state; /* Used क्रम saving and resuming state */
	काष्ठा hash_dma		dma;
पूर्ण;

पूर्णांक hash_check_hw(काष्ठा hash_device_data *device_data);

पूर्णांक hash_setconfiguration(काष्ठा hash_device_data *device_data,
		काष्ठा hash_config *config);

व्योम hash_begin(काष्ठा hash_device_data *device_data, काष्ठा hash_ctx *ctx);

व्योम hash_get_digest(काष्ठा hash_device_data *device_data,
		u8 *digest, पूर्णांक algorithm);

पूर्णांक hash_hw_update(काष्ठा ahash_request *req);

पूर्णांक hash_save_state(काष्ठा hash_device_data *device_data,
		काष्ठा hash_state *state);

पूर्णांक hash_resume_state(काष्ठा hash_device_data *device_data,
		स्थिर काष्ठा hash_state *state);

#पूर्ण_अगर
