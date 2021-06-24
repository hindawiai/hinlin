<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Cryptographic API.
 *
 * Support क्रम SAHARA cryptographic accelerator.
 *
 * Copyright (c) 2014 Steffen Trumtrar <s.trumtrar@pengutronix.de>
 * Copyright (c) 2013 Vista Silicon S.L.
 * Author: Javier Martin <javier.martin@vista-silicon.com>
 *
 * Based on omap-aes.c and tegra-aes.c
 */

#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/hash.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा SHA_BUFFER_LEN		PAGE_SIZE
#घोषणा SAHARA_MAX_SHA_BLOCK_SIZE	SHA256_BLOCK_SIZE

#घोषणा SAHARA_NAME "sahara"
#घोषणा SAHARA_VERSION_3	3
#घोषणा SAHARA_VERSION_4	4
#घोषणा SAHARA_TIMEOUT_MS	1000
#घोषणा SAHARA_MAX_HW_DESC	2
#घोषणा SAHARA_MAX_HW_LINK	20

#घोषणा FLAGS_MODE_MASK		0x000f
#घोषणा FLAGS_ENCRYPT		BIT(0)
#घोषणा FLAGS_CBC		BIT(1)
#घोषणा FLAGS_NEW_KEY		BIT(3)

#घोषणा SAHARA_HDR_BASE			0x00800000
#घोषणा SAHARA_HDR_SKHA_ALG_AES	0
#घोषणा SAHARA_HDR_SKHA_OP_ENC		(1 << 2)
#घोषणा SAHARA_HDR_SKHA_MODE_ECB	(0 << 3)
#घोषणा SAHARA_HDR_SKHA_MODE_CBC	(1 << 3)
#घोषणा SAHARA_HDR_FORM_DATA		(5 << 16)
#घोषणा SAHARA_HDR_FORM_KEY		(8 << 16)
#घोषणा SAHARA_HDR_LLO			(1 << 24)
#घोषणा SAHARA_HDR_CHA_SKHA		(1 << 28)
#घोषणा SAHARA_HDR_CHA_MDHA		(2 << 28)
#घोषणा SAHARA_HDR_PARITY_BIT		(1 << 31)

#घोषणा SAHARA_HDR_MDHA_SET_MODE_MD_KEY	0x20880000
#घोषणा SAHARA_HDR_MDHA_SET_MODE_HASH	0x208D0000
#घोषणा SAHARA_HDR_MDHA_HASH		0xA0850000
#घोषणा SAHARA_HDR_MDHA_STORE_DIGEST	0x20820000
#घोषणा SAHARA_HDR_MDHA_ALG_SHA1	0
#घोषणा SAHARA_HDR_MDHA_ALG_MD5		1
#घोषणा SAHARA_HDR_MDHA_ALG_SHA256	2
#घोषणा SAHARA_HDR_MDHA_ALG_SHA224	3
#घोषणा SAHARA_HDR_MDHA_PDATA		(1 << 2)
#घोषणा SAHARA_HDR_MDHA_HMAC		(1 << 3)
#घोषणा SAHARA_HDR_MDHA_INIT		(1 << 5)
#घोषणा SAHARA_HDR_MDHA_IPAD		(1 << 6)
#घोषणा SAHARA_HDR_MDHA_OPAD		(1 << 7)
#घोषणा SAHARA_HDR_MDHA_SWAP		(1 << 8)
#घोषणा SAHARA_HDR_MDHA_MAC_FULL	(1 << 9)
#घोषणा SAHARA_HDR_MDHA_SSL		(1 << 10)

/* SAHARA can only process one request at a समय */
#घोषणा SAHARA_QUEUE_LENGTH	1

#घोषणा SAHARA_REG_VERSION	0x00
#घोषणा SAHARA_REG_DAR		0x04
#घोषणा SAHARA_REG_CONTROL	0x08
#घोषणा		SAHARA_CONTROL_SET_THROTTLE(x)	(((x) & 0xff) << 24)
#घोषणा		SAHARA_CONTROL_SET_MAXBURST(x)	(((x) & 0xff) << 16)
#घोषणा		SAHARA_CONTROL_RNG_AUTORSD	(1 << 7)
#घोषणा		SAHARA_CONTROL_ENABLE_INT	(1 << 4)
#घोषणा SAHARA_REG_CMD		0x0C
#घोषणा		SAHARA_CMD_RESET		(1 << 0)
#घोषणा		SAHARA_CMD_CLEAR_INT		(1 << 8)
#घोषणा		SAHARA_CMD_CLEAR_ERR		(1 << 9)
#घोषणा		SAHARA_CMD_SINGLE_STEP		(1 << 10)
#घोषणा		SAHARA_CMD_MODE_BATCH		(1 << 16)
#घोषणा		SAHARA_CMD_MODE_DEBUG		(1 << 18)
#घोषणा	SAHARA_REG_STATUS	0x10
#घोषणा		SAHARA_STATUS_GET_STATE(x)	((x) & 0x7)
#घोषणा			SAHARA_STATE_IDLE	0
#घोषणा			SAHARA_STATE_BUSY	1
#घोषणा			SAHARA_STATE_ERR	2
#घोषणा			SAHARA_STATE_FAULT	3
#घोषणा			SAHARA_STATE_COMPLETE	4
#घोषणा			SAHARA_STATE_COMP_FLAG	(1 << 2)
#घोषणा		SAHARA_STATUS_DAR_FULL		(1 << 3)
#घोषणा		SAHARA_STATUS_ERROR		(1 << 4)
#घोषणा		SAHARA_STATUS_SECURE		(1 << 5)
#घोषणा		SAHARA_STATUS_FAIL		(1 << 6)
#घोषणा		SAHARA_STATUS_INIT		(1 << 7)
#घोषणा		SAHARA_STATUS_RNG_RESEED	(1 << 8)
#घोषणा		SAHARA_STATUS_ACTIVE_RNG	(1 << 9)
#घोषणा		SAHARA_STATUS_ACTIVE_MDHA	(1 << 10)
#घोषणा		SAHARA_STATUS_ACTIVE_SKHA	(1 << 11)
#घोषणा		SAHARA_STATUS_MODE_BATCH	(1 << 16)
#घोषणा		SAHARA_STATUS_MODE_DEDICATED	(1 << 17)
#घोषणा		SAHARA_STATUS_MODE_DEBUG	(1 << 18)
#घोषणा		SAHARA_STATUS_GET_ISTATE(x)	(((x) >> 24) & 0xff)
#घोषणा SAHARA_REG_ERRSTATUS	0x14
#घोषणा		SAHARA_ERRSTATUS_GET_SOURCE(x)	((x) & 0xf)
#घोषणा			SAHARA_ERRSOURCE_CHA	14
#घोषणा			SAHARA_ERRSOURCE_DMA	15
#घोषणा		SAHARA_ERRSTATUS_DMA_सूची	(1 << 8)
#घोषणा		SAHARA_ERRSTATUS_GET_DMASZ(x)(((x) >> 9) & 0x3)
#घोषणा		SAHARA_ERRSTATUS_GET_DMASRC(x) (((x) >> 13) & 0x7)
#घोषणा		SAHARA_ERRSTATUS_GET_CHASRC(x)	(((x) >> 16) & 0xfff)
#घोषणा		SAHARA_ERRSTATUS_GET_CHAERR(x)	(((x) >> 28) & 0x3)
#घोषणा SAHARA_REG_FADDR	0x18
#घोषणा SAHARA_REG_CDAR		0x1C
#घोषणा SAHARA_REG_IDAR		0x20

काष्ठा sahara_hw_desc अणु
	u32	hdr;
	u32	len1;
	u32	p1;
	u32	len2;
	u32	p2;
	u32	next;
पूर्ण;

काष्ठा sahara_hw_link अणु
	u32	len;
	u32	p;
	u32	next;
पूर्ण;

काष्ठा sahara_ctx अणु
	अचिन्हित दीर्घ flags;

	/* AES-specअगरic context */
	पूर्णांक keylen;
	u8 key[AES_KEYSIZE_128];
	काष्ठा crypto_skcipher *fallback;
पूर्ण;

काष्ठा sahara_aes_reqctx अणु
	अचिन्हित दीर्घ mode;
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

/*
 * काष्ठा sahara_sha_reqctx - निजी data per request
 * @buf: holds data क्रम requests smaller than block_size
 * @rembuf: used to prepare one block_size-aligned request
 * @context: hw-specअगरic context क्रम request. Digest is extracted from this
 * @mode: specअगरies what type of hw-descriptor needs to be built
 * @digest_size: length of digest क्रम this request
 * @context_size: length of hw-context क्रम this request.
 *                Always digest_size + 4
 * @buf_cnt: number of bytes saved in buf
 * @sg_in_idx: number of hw links
 * @in_sg: scatterlist क्रम input data
 * @in_sg_chain: scatterlists क्रम chained input data
 * @total: total number of bytes क्रम transfer
 * @last: is this the last block
 * @first: is this the first block
 * @active: inside a transfer
 */
काष्ठा sahara_sha_reqctx अणु
	u8			buf[SAHARA_MAX_SHA_BLOCK_SIZE];
	u8			rembuf[SAHARA_MAX_SHA_BLOCK_SIZE];
	u8			context[SHA256_DIGEST_SIZE + 4];
	अचिन्हित पूर्णांक		mode;
	अचिन्हित पूर्णांक		digest_size;
	अचिन्हित पूर्णांक		context_size;
	अचिन्हित पूर्णांक		buf_cnt;
	अचिन्हित पूर्णांक		sg_in_idx;
	काष्ठा scatterlist	*in_sg;
	काष्ठा scatterlist	in_sg_chain[2];
	माप_प्रकार			total;
	अचिन्हित पूर्णांक		last;
	अचिन्हित पूर्णांक		first;
	अचिन्हित पूर्णांक		active;
पूर्ण;

काष्ठा sahara_dev अणु
	काष्ठा device		*device;
	अचिन्हित पूर्णांक		version;
	व्योम __iomem		*regs_base;
	काष्ठा clk		*clk_ipg;
	काष्ठा clk		*clk_ahb;
	काष्ठा mutex		queue_mutex;
	काष्ठा task_काष्ठा	*kthपढ़ो;
	काष्ठा completion	dma_completion;

	काष्ठा sahara_ctx	*ctx;
	काष्ठा crypto_queue	queue;
	अचिन्हित दीर्घ		flags;

	काष्ठा sahara_hw_desc	*hw_desc[SAHARA_MAX_HW_DESC];
	dma_addr_t		hw_phys_desc[SAHARA_MAX_HW_DESC];

	u8			*key_base;
	dma_addr_t		key_phys_base;

	u8			*iv_base;
	dma_addr_t		iv_phys_base;

	u8			*context_base;
	dma_addr_t		context_phys_base;

	काष्ठा sahara_hw_link	*hw_link[SAHARA_MAX_HW_LINK];
	dma_addr_t		hw_phys_link[SAHARA_MAX_HW_LINK];

	माप_प्रकार			total;
	काष्ठा scatterlist	*in_sg;
	पूर्णांक		nb_in_sg;
	काष्ठा scatterlist	*out_sg;
	पूर्णांक		nb_out_sg;

	u32			error;
पूर्ण;

अटल काष्ठा sahara_dev *dev_ptr;

अटल अंतरभूत व्योम sahara_ग_लिखो(काष्ठा sahara_dev *dev, u32 data, u32 reg)
अणु
	ग_लिखोl(data, dev->regs_base + reg);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक sahara_पढ़ो(काष्ठा sahara_dev *dev, u32 reg)
अणु
	वापस पढ़ोl(dev->regs_base + reg);
पूर्ण

अटल u32 sahara_aes_key_hdr(काष्ठा sahara_dev *dev)
अणु
	u32 hdr = SAHARA_HDR_BASE | SAHARA_HDR_SKHA_ALG_AES |
			SAHARA_HDR_FORM_KEY | SAHARA_HDR_LLO |
			SAHARA_HDR_CHA_SKHA | SAHARA_HDR_PARITY_BIT;

	अगर (dev->flags & FLAGS_CBC) अणु
		hdr |= SAHARA_HDR_SKHA_MODE_CBC;
		hdr ^= SAHARA_HDR_PARITY_BIT;
	पूर्ण

	अगर (dev->flags & FLAGS_ENCRYPT) अणु
		hdr |= SAHARA_HDR_SKHA_OP_ENC;
		hdr ^= SAHARA_HDR_PARITY_BIT;
	पूर्ण

	वापस hdr;
पूर्ण

अटल u32 sahara_aes_data_link_hdr(काष्ठा sahara_dev *dev)
अणु
	वापस SAHARA_HDR_BASE | SAHARA_HDR_FORM_DATA |
			SAHARA_HDR_CHA_SKHA | SAHARA_HDR_PARITY_BIT;
पूर्ण

अटल स्थिर अक्षर *sahara_err_src[16] = अणु
	"No error",
	"Header error",
	"Descriptor length error",
	"Descriptor length or pointer error",
	"Link length error",
	"Link pointer error",
	"Input buffer error",
	"Output buffer error",
	"Output buffer starvation",
	"Internal state fault",
	"General descriptor problem",
	"Reserved",
	"Descriptor address error",
	"Link address error",
	"CHA error",
	"DMA error"
पूर्ण;

अटल स्थिर अक्षर *sahara_err_dmasize[4] = अणु
	"Byte transfer",
	"Half-word transfer",
	"Word transfer",
	"Reserved"
पूर्ण;

अटल स्थिर अक्षर *sahara_err_dmasrc[8] = अणु
	"No error",
	"AHB bus error",
	"Internal IP bus error",
	"Parity error",
	"DMA crosses 256 byte boundary",
	"DMA is busy",
	"Reserved",
	"DMA HW error"
पूर्ण;

अटल स्थिर अक्षर *sahara_cha_errsrc[12] = अणु
	"Input buffer non-empty",
	"Illegal address",
	"Illegal mode",
	"Illegal data size",
	"Illegal key size",
	"Write during processing",
	"CTX read during processing",
	"HW error",
	"Input buffer disabled/underflow",
	"Output buffer disabled/overflow",
	"DES key parity error",
	"Reserved"
पूर्ण;

अटल स्थिर अक्षर *sahara_cha_err[4] = अणु "No error", "SKHA", "MDHA", "RNG" पूर्ण;

अटल व्योम sahara_decode_error(काष्ठा sahara_dev *dev, अचिन्हित पूर्णांक error)
अणु
	u8 source = SAHARA_ERRSTATUS_GET_SOURCE(error);
	u16 chasrc = ffs(SAHARA_ERRSTATUS_GET_CHASRC(error));

	dev_err(dev->device, "%s: Error Register = 0x%08x\n", __func__, error);

	dev_err(dev->device, "	- %s.\n", sahara_err_src[source]);

	अगर (source == SAHARA_ERRSOURCE_DMA) अणु
		अगर (error & SAHARA_ERRSTATUS_DMA_सूची)
			dev_err(dev->device, "		* DMA read.\n");
		अन्यथा
			dev_err(dev->device, "		* DMA write.\n");

		dev_err(dev->device, "		* %s.\n",
		       sahara_err_dmasize[SAHARA_ERRSTATUS_GET_DMASZ(error)]);
		dev_err(dev->device, "		* %s.\n",
		       sahara_err_dmasrc[SAHARA_ERRSTATUS_GET_DMASRC(error)]);
	पूर्ण अन्यथा अगर (source == SAHARA_ERRSOURCE_CHA) अणु
		dev_err(dev->device, "		* %s.\n",
			sahara_cha_errsrc[chasrc]);
		dev_err(dev->device, "		* %s.\n",
		       sahara_cha_err[SAHARA_ERRSTATUS_GET_CHAERR(error)]);
	पूर्ण
	dev_err(dev->device, "\n");
पूर्ण

अटल स्थिर अक्षर *sahara_state[4] = अणु "Idle", "Busy", "Error", "HW Fault" पूर्ण;

अटल व्योम sahara_decode_status(काष्ठा sahara_dev *dev, अचिन्हित पूर्णांक status)
अणु
	u8 state;

	अगर (!__is_defined(DEBUG))
		वापस;

	state = SAHARA_STATUS_GET_STATE(status);

	dev_dbg(dev->device, "%s: Status Register = 0x%08x\n",
		__func__, status);

	dev_dbg(dev->device, "	- State = %d:\n", state);
	अगर (state & SAHARA_STATE_COMP_FLAG)
		dev_dbg(dev->device, "		* Descriptor completed. IRQ pending.\n");

	dev_dbg(dev->device, "		* %s.\n",
	       sahara_state[state & ~SAHARA_STATE_COMP_FLAG]);

	अगर (status & SAHARA_STATUS_DAR_FULL)
		dev_dbg(dev->device, "	- DAR Full.\n");
	अगर (status & SAHARA_STATUS_ERROR)
		dev_dbg(dev->device, "	- Error.\n");
	अगर (status & SAHARA_STATUS_SECURE)
		dev_dbg(dev->device, "	- Secure.\n");
	अगर (status & SAHARA_STATUS_FAIL)
		dev_dbg(dev->device, "	- Fail.\n");
	अगर (status & SAHARA_STATUS_RNG_RESEED)
		dev_dbg(dev->device, "	- RNG Reseed Request.\n");
	अगर (status & SAHARA_STATUS_ACTIVE_RNG)
		dev_dbg(dev->device, "	- RNG Active.\n");
	अगर (status & SAHARA_STATUS_ACTIVE_MDHA)
		dev_dbg(dev->device, "	- MDHA Active.\n");
	अगर (status & SAHARA_STATUS_ACTIVE_SKHA)
		dev_dbg(dev->device, "	- SKHA Active.\n");

	अगर (status & SAHARA_STATUS_MODE_BATCH)
		dev_dbg(dev->device, "	- Batch Mode.\n");
	अन्यथा अगर (status & SAHARA_STATUS_MODE_DEDICATED)
		dev_dbg(dev->device, "	- Dedicated Mode.\n");
	अन्यथा अगर (status & SAHARA_STATUS_MODE_DEBUG)
		dev_dbg(dev->device, "	- Debug Mode.\n");

	dev_dbg(dev->device, "	- Internal state = 0x%02x\n",
	       SAHARA_STATUS_GET_ISTATE(status));

	dev_dbg(dev->device, "Current DAR: 0x%08x\n",
		sahara_पढ़ो(dev, SAHARA_REG_CDAR));
	dev_dbg(dev->device, "Initial DAR: 0x%08x\n\n",
		sahara_पढ़ो(dev, SAHARA_REG_IDAR));
पूर्ण

अटल व्योम sahara_dump_descriptors(काष्ठा sahara_dev *dev)
अणु
	पूर्णांक i;

	अगर (!__is_defined(DEBUG))
		वापस;

	क्रम (i = 0; i < SAHARA_MAX_HW_DESC; i++) अणु
		dev_dbg(dev->device, "Descriptor (%d) (%pad):\n",
			i, &dev->hw_phys_desc[i]);
		dev_dbg(dev->device, "\thdr = 0x%08x\n", dev->hw_desc[i]->hdr);
		dev_dbg(dev->device, "\tlen1 = %u\n", dev->hw_desc[i]->len1);
		dev_dbg(dev->device, "\tp1 = 0x%08x\n", dev->hw_desc[i]->p1);
		dev_dbg(dev->device, "\tlen2 = %u\n", dev->hw_desc[i]->len2);
		dev_dbg(dev->device, "\tp2 = 0x%08x\n", dev->hw_desc[i]->p2);
		dev_dbg(dev->device, "\tnext = 0x%08x\n",
			dev->hw_desc[i]->next);
	पूर्ण
	dev_dbg(dev->device, "\n");
पूर्ण

अटल व्योम sahara_dump_links(काष्ठा sahara_dev *dev)
अणु
	पूर्णांक i;

	अगर (!__is_defined(DEBUG))
		वापस;

	क्रम (i = 0; i < SAHARA_MAX_HW_LINK; i++) अणु
		dev_dbg(dev->device, "Link (%d) (%pad):\n",
			i, &dev->hw_phys_link[i]);
		dev_dbg(dev->device, "\tlen = %u\n", dev->hw_link[i]->len);
		dev_dbg(dev->device, "\tp = 0x%08x\n", dev->hw_link[i]->p);
		dev_dbg(dev->device, "\tnext = 0x%08x\n",
			dev->hw_link[i]->next);
	पूर्ण
	dev_dbg(dev->device, "\n");
पूर्ण

अटल पूर्णांक sahara_hw_descriptor_create(काष्ठा sahara_dev *dev)
अणु
	काष्ठा sahara_ctx *ctx = dev->ctx;
	काष्ठा scatterlist *sg;
	पूर्णांक ret;
	पूर्णांक i, j;
	पूर्णांक idx = 0;

	/* Copy new key अगर necessary */
	अगर (ctx->flags & FLAGS_NEW_KEY) अणु
		स_नकल(dev->key_base, ctx->key, ctx->keylen);
		ctx->flags &= ~FLAGS_NEW_KEY;

		अगर (dev->flags & FLAGS_CBC) अणु
			dev->hw_desc[idx]->len1 = AES_BLOCK_SIZE;
			dev->hw_desc[idx]->p1 = dev->iv_phys_base;
		पूर्ण अन्यथा अणु
			dev->hw_desc[idx]->len1 = 0;
			dev->hw_desc[idx]->p1 = 0;
		पूर्ण
		dev->hw_desc[idx]->len2 = ctx->keylen;
		dev->hw_desc[idx]->p2 = dev->key_phys_base;
		dev->hw_desc[idx]->next = dev->hw_phys_desc[1];

		dev->hw_desc[idx]->hdr = sahara_aes_key_hdr(dev);

		idx++;
	पूर्ण

	dev->nb_in_sg = sg_nents_क्रम_len(dev->in_sg, dev->total);
	अगर (dev->nb_in_sg < 0) अणु
		dev_err(dev->device, "Invalid numbers of src SG.\n");
		वापस dev->nb_in_sg;
	पूर्ण
	dev->nb_out_sg = sg_nents_क्रम_len(dev->out_sg, dev->total);
	अगर (dev->nb_out_sg < 0) अणु
		dev_err(dev->device, "Invalid numbers of dst SG.\n");
		वापस dev->nb_out_sg;
	पूर्ण
	अगर ((dev->nb_in_sg + dev->nb_out_sg) > SAHARA_MAX_HW_LINK) अणु
		dev_err(dev->device, "not enough hw links (%d)\n",
			dev->nb_in_sg + dev->nb_out_sg);
		वापस -EINVAL;
	पूर्ण

	ret = dma_map_sg(dev->device, dev->in_sg, dev->nb_in_sg,
			 DMA_TO_DEVICE);
	अगर (ret != dev->nb_in_sg) अणु
		dev_err(dev->device, "couldn't map in sg\n");
		जाओ unmap_in;
	पूर्ण
	ret = dma_map_sg(dev->device, dev->out_sg, dev->nb_out_sg,
			 DMA_FROM_DEVICE);
	अगर (ret != dev->nb_out_sg) अणु
		dev_err(dev->device, "couldn't map out sg\n");
		जाओ unmap_out;
	पूर्ण

	/* Create input links */
	dev->hw_desc[idx]->p1 = dev->hw_phys_link[0];
	sg = dev->in_sg;
	क्रम (i = 0; i < dev->nb_in_sg; i++) अणु
		dev->hw_link[i]->len = sg->length;
		dev->hw_link[i]->p = sg->dma_address;
		अगर (i == (dev->nb_in_sg - 1)) अणु
			dev->hw_link[i]->next = 0;
		पूर्ण अन्यथा अणु
			dev->hw_link[i]->next = dev->hw_phys_link[i + 1];
			sg = sg_next(sg);
		पूर्ण
	पूर्ण

	/* Create output links */
	dev->hw_desc[idx]->p2 = dev->hw_phys_link[i];
	sg = dev->out_sg;
	क्रम (j = i; j < dev->nb_out_sg + i; j++) अणु
		dev->hw_link[j]->len = sg->length;
		dev->hw_link[j]->p = sg->dma_address;
		अगर (j == (dev->nb_out_sg + i - 1)) अणु
			dev->hw_link[j]->next = 0;
		पूर्ण अन्यथा अणु
			dev->hw_link[j]->next = dev->hw_phys_link[j + 1];
			sg = sg_next(sg);
		पूर्ण
	पूर्ण

	/* Fill reमुख्यing fields of hw_desc[1] */
	dev->hw_desc[idx]->hdr = sahara_aes_data_link_hdr(dev);
	dev->hw_desc[idx]->len1 = dev->total;
	dev->hw_desc[idx]->len2 = dev->total;
	dev->hw_desc[idx]->next = 0;

	sahara_dump_descriptors(dev);
	sahara_dump_links(dev);

	sahara_ग_लिखो(dev, dev->hw_phys_desc[0], SAHARA_REG_DAR);

	वापस 0;

unmap_out:
	dma_unmap_sg(dev->device, dev->out_sg, dev->nb_out_sg,
		DMA_FROM_DEVICE);
unmap_in:
	dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
		DMA_TO_DEVICE);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sahara_aes_process(काष्ठा skcipher_request *req)
अणु
	काष्ठा sahara_dev *dev = dev_ptr;
	काष्ठा sahara_ctx *ctx;
	काष्ठा sahara_aes_reqctx *rctx;
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	/* Request is पढ़ोy to be dispatched by the device */
	dev_dbg(dev->device,
		"dispatch request (nbytes=%d, src=%p, dst=%p)\n",
		req->cryptlen, req->src, req->dst);

	/* assign new request to device */
	dev->total = req->cryptlen;
	dev->in_sg = req->src;
	dev->out_sg = req->dst;

	rctx = skcipher_request_ctx(req);
	ctx = crypto_skcipher_ctx(crypto_skcipher_reqtfm(req));
	rctx->mode &= FLAGS_MODE_MASK;
	dev->flags = (dev->flags & ~FLAGS_MODE_MASK) | rctx->mode;

	अगर ((dev->flags & FLAGS_CBC) && req->iv)
		स_नकल(dev->iv_base, req->iv, AES_KEYSIZE_128);

	/* assign new context to device */
	dev->ctx = ctx;

	reinit_completion(&dev->dma_completion);

	ret = sahara_hw_descriptor_create(dev);
	अगर (ret)
		वापस -EINVAL;

	समयout = रुको_क्रम_completion_समयout(&dev->dma_completion,
				msecs_to_jअगरfies(SAHARA_TIMEOUT_MS));
	अगर (!समयout) अणु
		dev_err(dev->device, "AES timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	dma_unmap_sg(dev->device, dev->out_sg, dev->nb_out_sg,
		DMA_FROM_DEVICE);
	dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
		DMA_TO_DEVICE);

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->keylen = keylen;

	/* SAHARA only supports 128bit keys */
	अगर (keylen == AES_KEYSIZE_128) अणु
		स_नकल(ctx->key, key, keylen);
		ctx->flags |= FLAGS_NEW_KEY;
		वापस 0;
	पूर्ण

	अगर (keylen != AES_KEYSIZE_192 && keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	/*
	 * The requested key size is not supported by HW, करो a fallback.
	 */
	crypto_skcipher_clear_flags(ctx->fallback, CRYPTO_TFM_REQ_MASK);
	crypto_skcipher_set_flags(ctx->fallback, tfm->base.crt_flags &
						 CRYPTO_TFM_REQ_MASK);
	वापस crypto_skcipher_setkey(ctx->fallback, key, keylen);
पूर्ण

अटल पूर्णांक sahara_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा sahara_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sahara_dev *dev = dev_ptr;
	पूर्णांक err = 0;

	dev_dbg(dev->device, "nbytes: %d, enc: %d, cbc: %d\n",
		req->cryptlen, !!(mode & FLAGS_ENCRYPT), !!(mode & FLAGS_CBC));

	अगर (!IS_ALIGNED(req->cryptlen, AES_BLOCK_SIZE)) अणु
		dev_err(dev->device,
			"request size is not exact amount of AES blocks\n");
		वापस -EINVAL;
	पूर्ण

	rctx->mode = mode;

	mutex_lock(&dev->queue_mutex);
	err = crypto_enqueue_request(&dev->queue, &req->base);
	mutex_unlock(&dev->queue_mutex);

	wake_up_process(dev->kthपढ़ो);

	वापस err;
पूर्ण

अटल पूर्णांक sahara_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा sahara_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(
		crypto_skcipher_reqtfm(req));

	अगर (unlikely(ctx->keylen != AES_KEYSIZE_128)) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);
		वापस crypto_skcipher_encrypt(&rctx->fallback_req);
	पूर्ण

	वापस sahara_aes_crypt(req, FLAGS_ENCRYPT);
पूर्ण

अटल पूर्णांक sahara_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा sahara_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(
		crypto_skcipher_reqtfm(req));

	अगर (unlikely(ctx->keylen != AES_KEYSIZE_128)) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);
		वापस crypto_skcipher_decrypt(&rctx->fallback_req);
	पूर्ण

	वापस sahara_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक sahara_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा sahara_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(
		crypto_skcipher_reqtfm(req));

	अगर (unlikely(ctx->keylen != AES_KEYSIZE_128)) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);
		वापस crypto_skcipher_encrypt(&rctx->fallback_req);
	पूर्ण

	वापस sahara_aes_crypt(req, FLAGS_ENCRYPT | FLAGS_CBC);
पूर्ण

अटल पूर्णांक sahara_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	काष्ठा sahara_aes_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(
		crypto_skcipher_reqtfm(req));

	अगर (unlikely(ctx->keylen != AES_KEYSIZE_128)) अणु
		skcipher_request_set_tfm(&rctx->fallback_req, ctx->fallback);
		skcipher_request_set_callback(&rctx->fallback_req,
					      req->base.flags,
					      req->base.complete,
					      req->base.data);
		skcipher_request_set_crypt(&rctx->fallback_req, req->src,
					   req->dst, req->cryptlen, req->iv);
		वापस crypto_skcipher_decrypt(&rctx->fallback_req);
	पूर्ण

	वापस sahara_aes_crypt(req, FLAGS_CBC);
पूर्ण

अटल पूर्णांक sahara_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	स्थिर अक्षर *name = crypto_tfm_alg_name(&tfm->base);
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->fallback = crypto_alloc_skcipher(name, 0,
					      CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(ctx->fallback)) अणु
		pr_err("Error allocating fallback algo %s\n", name);
		वापस PTR_ERR(ctx->fallback);
	पूर्ण

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा sahara_aes_reqctx) +
					 crypto_skcipher_reqsize(ctx->fallback));

	वापस 0;
पूर्ण

अटल व्योम sahara_aes_निकास_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sahara_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_मुक्त_skcipher(ctx->fallback);
पूर्ण

अटल u32 sahara_sha_init_hdr(काष्ठा sahara_dev *dev,
			      काष्ठा sahara_sha_reqctx *rctx)
अणु
	u32 hdr = 0;

	hdr = rctx->mode;

	अगर (rctx->first) अणु
		hdr |= SAHARA_HDR_MDHA_SET_MODE_HASH;
		hdr |= SAHARA_HDR_MDHA_INIT;
	पूर्ण अन्यथा अणु
		hdr |= SAHARA_HDR_MDHA_SET_MODE_MD_KEY;
	पूर्ण

	अगर (rctx->last)
		hdr |= SAHARA_HDR_MDHA_PDATA;

	अगर (hweight_दीर्घ(hdr) % 2 == 0)
		hdr |= SAHARA_HDR_PARITY_BIT;

	वापस hdr;
पूर्ण

अटल पूर्णांक sahara_sha_hw_links_create(काष्ठा sahara_dev *dev,
				       काष्ठा sahara_sha_reqctx *rctx,
				       पूर्णांक start)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	dev->in_sg = rctx->in_sg;

	dev->nb_in_sg = sg_nents_क्रम_len(dev->in_sg, rctx->total);
	अगर (dev->nb_in_sg < 0) अणु
		dev_err(dev->device, "Invalid numbers of src SG.\n");
		वापस dev->nb_in_sg;
	पूर्ण
	अगर ((dev->nb_in_sg) > SAHARA_MAX_HW_LINK) अणु
		dev_err(dev->device, "not enough hw links (%d)\n",
			dev->nb_in_sg + dev->nb_out_sg);
		वापस -EINVAL;
	पूर्ण

	sg = dev->in_sg;
	ret = dma_map_sg(dev->device, dev->in_sg, dev->nb_in_sg, DMA_TO_DEVICE);
	अगर (!ret)
		वापस -EFAULT;

	क्रम (i = start; i < dev->nb_in_sg + start; i++) अणु
		dev->hw_link[i]->len = sg->length;
		dev->hw_link[i]->p = sg->dma_address;
		अगर (i == (dev->nb_in_sg + start - 1)) अणु
			dev->hw_link[i]->next = 0;
		पूर्ण अन्यथा अणु
			dev->hw_link[i]->next = dev->hw_phys_link[i + 1];
			sg = sg_next(sg);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक sahara_sha_hw_data_descriptor_create(काष्ठा sahara_dev *dev,
						काष्ठा sahara_sha_reqctx *rctx,
						काष्ठा ahash_request *req,
						पूर्णांक index)
अणु
	अचिन्हित result_len;
	पूर्णांक i = index;

	अगर (rctx->first)
		/* Create initial descriptor: #8*/
		dev->hw_desc[index]->hdr = sahara_sha_init_hdr(dev, rctx);
	अन्यथा
		/* Create hash descriptor: #10. Must follow #6. */
		dev->hw_desc[index]->hdr = SAHARA_HDR_MDHA_HASH;

	dev->hw_desc[index]->len1 = rctx->total;
	अगर (dev->hw_desc[index]->len1 == 0) अणु
		/* अगर len1 is 0, p1 must be 0, too */
		dev->hw_desc[index]->p1 = 0;
		rctx->sg_in_idx = 0;
	पूर्ण अन्यथा अणु
		/* Create input links */
		dev->hw_desc[index]->p1 = dev->hw_phys_link[index];
		i = sahara_sha_hw_links_create(dev, rctx, index);

		rctx->sg_in_idx = index;
		अगर (i < 0)
			वापस i;
	पूर्ण

	dev->hw_desc[index]->p2 = dev->hw_phys_link[i];

	/* Save the context क्रम the next operation */
	result_len = rctx->context_size;
	dev->hw_link[i]->p = dev->context_phys_base;

	dev->hw_link[i]->len = result_len;
	dev->hw_desc[index]->len2 = result_len;

	dev->hw_link[i]->next = 0;

	वापस 0;
पूर्ण

/*
 * Load descriptor aka #6
 *
 * To load a previously saved context back to the MDHA unit
 *
 * p1: Saved Context
 * p2: शून्य
 *
 */
अटल पूर्णांक sahara_sha_hw_context_descriptor_create(काष्ठा sahara_dev *dev,
						काष्ठा sahara_sha_reqctx *rctx,
						काष्ठा ahash_request *req,
						पूर्णांक index)
अणु
	dev->hw_desc[index]->hdr = sahara_sha_init_hdr(dev, rctx);

	dev->hw_desc[index]->len1 = rctx->context_size;
	dev->hw_desc[index]->p1 = dev->hw_phys_link[index];
	dev->hw_desc[index]->len2 = 0;
	dev->hw_desc[index]->p2 = 0;

	dev->hw_link[index]->len = rctx->context_size;
	dev->hw_link[index]->p = dev->context_phys_base;
	dev->hw_link[index]->next = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_walk_and_recalc(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक nbytes)
अणु
	अगर (!sg || !sg->length)
		वापस nbytes;

	जबतक (nbytes && sg) अणु
		अगर (nbytes <= sg->length) अणु
			sg->length = nbytes;
			sg_mark_end(sg);
			अवरोध;
		पूर्ण
		nbytes -= sg->length;
		sg = sg_next(sg);
	पूर्ण

	वापस nbytes;
पूर्ण

अटल पूर्णांक sahara_sha_prepare_request(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	अचिन्हित पूर्णांक hash_later;
	अचिन्हित पूर्णांक block_size;
	अचिन्हित पूर्णांक len;

	block_size = crypto_tfm_alg_blocksize(crypto_ahash_tfm(tfm));

	/* append bytes from previous operation */
	len = rctx->buf_cnt + req->nbytes;

	/* only the last transfer can be padded in hardware */
	अगर (!rctx->last && (len < block_size)) अणु
		/* to few data, save क्रम next operation */
		scatterwalk_map_and_copy(rctx->buf + rctx->buf_cnt, req->src,
					 0, req->nbytes, 0);
		rctx->buf_cnt += req->nbytes;

		वापस 0;
	पूर्ण

	/* add data from previous operation first */
	अगर (rctx->buf_cnt)
		स_नकल(rctx->rembuf, rctx->buf, rctx->buf_cnt);

	/* data must always be a multiple of block_size */
	hash_later = rctx->last ? 0 : len & (block_size - 1);
	अगर (hash_later) अणु
		अचिन्हित पूर्णांक offset = req->nbytes - hash_later;
		/* Save reमुख्यing bytes क्रम later use */
		scatterwalk_map_and_copy(rctx->buf, req->src, offset,
					hash_later, 0);
	पूर्ण

	/* nbytes should now be multiple of blocksize */
	req->nbytes = req->nbytes - hash_later;

	sahara_walk_and_recalc(req->src, req->nbytes);

	/* have data from previous operation and current */
	अगर (rctx->buf_cnt && req->nbytes) अणु
		sg_init_table(rctx->in_sg_chain, 2);
		sg_set_buf(rctx->in_sg_chain, rctx->rembuf, rctx->buf_cnt);

		sg_chain(rctx->in_sg_chain, 2, req->src);

		rctx->total = req->nbytes + rctx->buf_cnt;
		rctx->in_sg = rctx->in_sg_chain;

		req->src = rctx->in_sg_chain;
	/* only data from previous operation */
	पूर्ण अन्यथा अगर (rctx->buf_cnt) अणु
		अगर (req->src)
			rctx->in_sg = req->src;
		अन्यथा
			rctx->in_sg = rctx->in_sg_chain;
		/* buf was copied पूर्णांकo rembuf above */
		sg_init_one(rctx->in_sg, rctx->rembuf, rctx->buf_cnt);
		rctx->total = rctx->buf_cnt;
	/* no data from previous operation */
	पूर्ण अन्यथा अणु
		rctx->in_sg = req->src;
		rctx->total = req->nbytes;
		req->src = rctx->in_sg;
	पूर्ण

	/* on next call, we only have the reमुख्यing data in the buffer */
	rctx->buf_cnt = hash_later;

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक sahara_sha_process(काष्ठा ahash_request *req)
अणु
	काष्ठा sahara_dev *dev = dev_ptr;
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	पूर्णांक ret;
	अचिन्हित दीर्घ समयout;

	ret = sahara_sha_prepare_request(req);
	अगर (!ret)
		वापस ret;

	अगर (rctx->first) अणु
		sahara_sha_hw_data_descriptor_create(dev, rctx, req, 0);
		dev->hw_desc[0]->next = 0;
		rctx->first = 0;
	पूर्ण अन्यथा अणु
		स_नकल(dev->context_base, rctx->context, rctx->context_size);

		sahara_sha_hw_context_descriptor_create(dev, rctx, req, 0);
		dev->hw_desc[0]->next = dev->hw_phys_desc[1];
		sahara_sha_hw_data_descriptor_create(dev, rctx, req, 1);
		dev->hw_desc[1]->next = 0;
	पूर्ण

	sahara_dump_descriptors(dev);
	sahara_dump_links(dev);

	reinit_completion(&dev->dma_completion);

	sahara_ग_लिखो(dev, dev->hw_phys_desc[0], SAHARA_REG_DAR);

	समयout = रुको_क्रम_completion_समयout(&dev->dma_completion,
				msecs_to_jअगरfies(SAHARA_TIMEOUT_MS));
	अगर (!समयout) अणु
		dev_err(dev->device, "SHA timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (rctx->sg_in_idx)
		dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
			     DMA_TO_DEVICE);

	स_नकल(rctx->context, dev->context_base, rctx->context_size);

	अगर (req->result)
		स_नकल(req->result, rctx->context, rctx->digest_size);

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_queue_manage(व्योम *data)
अणु
	काष्ठा sahara_dev *dev = (काष्ठा sahara_dev *)data;
	काष्ठा crypto_async_request *async_req;
	काष्ठा crypto_async_request *backlog;
	पूर्णांक ret = 0;

	करो अणु
		__set_current_state(TASK_INTERRUPTIBLE);

		mutex_lock(&dev->queue_mutex);
		backlog = crypto_get_backlog(&dev->queue);
		async_req = crypto_dequeue_request(&dev->queue);
		mutex_unlock(&dev->queue_mutex);

		अगर (backlog)
			backlog->complete(backlog, -EINPROGRESS);

		अगर (async_req) अणु
			अगर (crypto_tfm_alg_type(async_req->tfm) ==
			    CRYPTO_ALG_TYPE_AHASH) अणु
				काष्ठा ahash_request *req =
					ahash_request_cast(async_req);

				ret = sahara_sha_process(req);
			पूर्ण अन्यथा अणु
				काष्ठा skcipher_request *req =
					skcipher_request_cast(async_req);

				ret = sahara_aes_process(req);
			पूर्ण

			async_req->complete(async_req, ret);

			जारी;
		पूर्ण

		schedule();
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_sha_enqueue(काष्ठा ahash_request *req, पूर्णांक last)
अणु
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);
	काष्ठा sahara_dev *dev = dev_ptr;
	पूर्णांक ret;

	अगर (!req->nbytes && !last)
		वापस 0;

	rctx->last = last;

	अगर (!rctx->active) अणु
		rctx->active = 1;
		rctx->first = 1;
	पूर्ण

	mutex_lock(&dev->queue_mutex);
	ret = crypto_enqueue_request(&dev->queue, &req->base);
	mutex_unlock(&dev->queue_mutex);

	wake_up_process(dev->kthपढ़ो);

	वापस ret;
पूर्ण

अटल पूर्णांक sahara_sha_init(काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);

	स_रखो(rctx, 0, माप(*rctx));

	चयन (crypto_ahash_digestsize(tfm)) अणु
	हाल SHA1_DIGEST_SIZE:
		rctx->mode |= SAHARA_HDR_MDHA_ALG_SHA1;
		rctx->digest_size = SHA1_DIGEST_SIZE;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		rctx->mode |= SAHARA_HDR_MDHA_ALG_SHA256;
		rctx->digest_size = SHA256_DIGEST_SIZE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rctx->context_size = rctx->digest_size + 4;
	rctx->active = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_sha_update(काष्ठा ahash_request *req)
अणु
	वापस sahara_sha_enqueue(req, 0);
पूर्ण

अटल पूर्णांक sahara_sha_final(काष्ठा ahash_request *req)
अणु
	req->nbytes = 0;
	वापस sahara_sha_enqueue(req, 1);
पूर्ण

अटल पूर्णांक sahara_sha_finup(काष्ठा ahash_request *req)
अणु
	वापस sahara_sha_enqueue(req, 1);
पूर्ण

अटल पूर्णांक sahara_sha_digest(काष्ठा ahash_request *req)
अणु
	sahara_sha_init(req);

	वापस sahara_sha_finup(req);
पूर्ण

अटल पूर्णांक sahara_sha_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);

	स_नकल(out, rctx, माप(काष्ठा sahara_sha_reqctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_sha_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा sahara_sha_reqctx *rctx = ahash_request_ctx(req);

	स_नकल(rctx, in, माप(काष्ठा sahara_sha_reqctx));

	वापस 0;
पूर्ण

अटल पूर्णांक sahara_sha_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा sahara_sha_reqctx) +
				 SHA_BUFFER_LEN + SHA256_BLOCK_SIZE);

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg aes_algs[] = अणु
अणु
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "sahara-ecb-aes",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sahara_ctx),
	.base.cra_alignmask	= 0x0,
	.base.cra_module	= THIS_MODULE,

	.init			= sahara_aes_init_tfm,
	.निकास			= sahara_aes_निकास_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE ,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= sahara_aes_setkey,
	.encrypt		= sahara_aes_ecb_encrypt,
	.decrypt		= sahara_aes_ecb_decrypt,
पूर्ण, अणु
	.base.cra_name		= "cbc(aes)",
	.base.cra_driver_name	= "sahara-cbc-aes",
	.base.cra_priority	= 300,
	.base.cra_flags		= CRYPTO_ALG_ASYNC | CRYPTO_ALG_NEED_FALLBACK,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sahara_ctx),
	.base.cra_alignmask	= 0x0,
	.base.cra_module	= THIS_MODULE,

	.init			= sahara_aes_init_tfm,
	.निकास			= sahara_aes_निकास_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE ,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= sahara_aes_setkey,
	.encrypt		= sahara_aes_cbc_encrypt,
	.decrypt		= sahara_aes_cbc_decrypt,
पूर्ण
पूर्ण;

अटल काष्ठा ahash_alg sha_v3_algs[] = अणु
अणु
	.init		= sahara_sha_init,
	.update		= sahara_sha_update,
	.final		= sahara_sha_final,
	.finup		= sahara_sha_finup,
	.digest		= sahara_sha_digest,
	.export		= sahara_sha_export,
	.import		= sahara_sha_import,
	.halg.digestsize	= SHA1_DIGEST_SIZE,
	.halg.statesize         = माप(काष्ठा sahara_sha_reqctx),
	.halg.base	= अणु
		.cra_name		= "sha1",
		.cra_driver_name	= "sahara-sha1",
		.cra_priority		= 300,
		.cra_flags		= CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA1_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा sahara_ctx),
		.cra_alignmask		= 0,
		.cra_module		= THIS_MODULE,
		.cra_init		= sahara_sha_cra_init,
	पूर्ण
पूर्ण,
पूर्ण;

अटल काष्ठा ahash_alg sha_v4_algs[] = अणु
अणु
	.init		= sahara_sha_init,
	.update		= sahara_sha_update,
	.final		= sahara_sha_final,
	.finup		= sahara_sha_finup,
	.digest		= sahara_sha_digest,
	.export		= sahara_sha_export,
	.import		= sahara_sha_import,
	.halg.digestsize	= SHA256_DIGEST_SIZE,
	.halg.statesize         = माप(काष्ठा sahara_sha_reqctx),
	.halg.base	= अणु
		.cra_name		= "sha256",
		.cra_driver_name	= "sahara-sha256",
		.cra_priority		= 300,
		.cra_flags		= CRYPTO_ALG_ASYNC |
						CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= SHA256_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा sahara_ctx),
		.cra_alignmask		= 0,
		.cra_module		= THIS_MODULE,
		.cra_init		= sahara_sha_cra_init,
	पूर्ण
पूर्ण,
पूर्ण;

अटल irqवापस_t sahara_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sahara_dev *dev = (काष्ठा sahara_dev *)data;
	अचिन्हित पूर्णांक stat = sahara_पढ़ो(dev, SAHARA_REG_STATUS);
	अचिन्हित पूर्णांक err = sahara_पढ़ो(dev, SAHARA_REG_ERRSTATUS);

	sahara_ग_लिखो(dev, SAHARA_CMD_CLEAR_INT | SAHARA_CMD_CLEAR_ERR,
		     SAHARA_REG_CMD);

	sahara_decode_status(dev, stat);

	अगर (SAHARA_STATUS_GET_STATE(stat) == SAHARA_STATE_BUSY) अणु
		वापस IRQ_NONE;
	पूर्ण अन्यथा अगर (SAHARA_STATUS_GET_STATE(stat) == SAHARA_STATE_COMPLETE) अणु
		dev->error = 0;
	पूर्ण अन्यथा अणु
		sahara_decode_error(dev, err);
		dev->error = -EINVAL;
	पूर्ण

	complete(&dev->dma_completion);

	वापस IRQ_HANDLED;
पूर्ण


अटल पूर्णांक sahara_रेजिस्टर_algs(काष्ठा sahara_dev *dev)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i, j, k, l;

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++) अणु
		err = crypto_रेजिस्टर_skcipher(&aes_algs[i]);
		अगर (err)
			जाओ err_aes_algs;
	पूर्ण

	क्रम (k = 0; k < ARRAY_SIZE(sha_v3_algs); k++) अणु
		err = crypto_रेजिस्टर_ahash(&sha_v3_algs[k]);
		अगर (err)
			जाओ err_sha_v3_algs;
	पूर्ण

	अगर (dev->version > SAHARA_VERSION_3)
		क्रम (l = 0; l < ARRAY_SIZE(sha_v4_algs); l++) अणु
			err = crypto_रेजिस्टर_ahash(&sha_v4_algs[l]);
			अगर (err)
				जाओ err_sha_v4_algs;
		पूर्ण

	वापस 0;

err_sha_v4_algs:
	क्रम (j = 0; j < l; j++)
		crypto_unरेजिस्टर_ahash(&sha_v4_algs[j]);

err_sha_v3_algs:
	क्रम (j = 0; j < k; j++)
		crypto_unरेजिस्टर_ahash(&sha_v3_algs[j]);

err_aes_algs:
	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_skcipher(&aes_algs[j]);

	वापस err;
पूर्ण

अटल व्योम sahara_unरेजिस्टर_algs(काष्ठा sahara_dev *dev)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(aes_algs); i++)
		crypto_unरेजिस्टर_skcipher(&aes_algs[i]);

	क्रम (i = 0; i < ARRAY_SIZE(sha_v3_algs); i++)
		crypto_unरेजिस्टर_ahash(&sha_v3_algs[i]);

	अगर (dev->version > SAHARA_VERSION_3)
		क्रम (i = 0; i < ARRAY_SIZE(sha_v4_algs); i++)
			crypto_unरेजिस्टर_ahash(&sha_v4_algs[i]);
पूर्ण

अटल स्थिर काष्ठा of_device_id sahara_dt_ids[] = अणु
	अणु .compatible = "fsl,imx53-sahara" पूर्ण,
	अणु .compatible = "fsl,imx27-sahara" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sahara_dt_ids);

अटल पूर्णांक sahara_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sahara_dev *dev;
	u32 version;
	पूर्णांक irq;
	पूर्णांक err;
	पूर्णांक i;

	dev = devm_kzalloc(&pdev->dev, माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;

	dev->device = &pdev->dev;
	platक्रमm_set_drvdata(pdev, dev);

	/* Get the base address */
	dev->regs_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(dev->regs_base))
		वापस PTR_ERR(dev->regs_base);

	/* Get the IRQ */
	irq = platक्रमm_get_irq(pdev,  0);
	अगर (irq < 0)
		वापस irq;

	err = devm_request_irq(&pdev->dev, irq, sahara_irq_handler,
			       0, dev_name(&pdev->dev), dev);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to request irq\n");
		वापस err;
	पूर्ण

	/* घड़ीs */
	dev->clk_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(dev->clk_ipg)) अणु
		dev_err(&pdev->dev, "Could not get ipg clock\n");
		वापस PTR_ERR(dev->clk_ipg);
	पूर्ण

	dev->clk_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(dev->clk_ahb)) अणु
		dev_err(&pdev->dev, "Could not get ahb clock\n");
		वापस PTR_ERR(dev->clk_ahb);
	पूर्ण

	/* Allocate HW descriptors */
	dev->hw_desc[0] = dmam_alloc_coherent(&pdev->dev,
			SAHARA_MAX_HW_DESC * माप(काष्ठा sahara_hw_desc),
			&dev->hw_phys_desc[0], GFP_KERNEL);
	अगर (!dev->hw_desc[0]) अणु
		dev_err(&pdev->dev, "Could not allocate hw descriptors\n");
		वापस -ENOMEM;
	पूर्ण
	dev->hw_desc[1] = dev->hw_desc[0] + 1;
	dev->hw_phys_desc[1] = dev->hw_phys_desc[0] +
				माप(काष्ठा sahara_hw_desc);

	/* Allocate space क्रम iv and key */
	dev->key_base = dmam_alloc_coherent(&pdev->dev, 2 * AES_KEYSIZE_128,
				&dev->key_phys_base, GFP_KERNEL);
	अगर (!dev->key_base) अणु
		dev_err(&pdev->dev, "Could not allocate memory for key\n");
		वापस -ENOMEM;
	पूर्ण
	dev->iv_base = dev->key_base + AES_KEYSIZE_128;
	dev->iv_phys_base = dev->key_phys_base + AES_KEYSIZE_128;

	/* Allocate space क्रम context: largest digest + message length field */
	dev->context_base = dmam_alloc_coherent(&pdev->dev,
					SHA256_DIGEST_SIZE + 4,
					&dev->context_phys_base, GFP_KERNEL);
	अगर (!dev->context_base) अणु
		dev_err(&pdev->dev, "Could not allocate memory for MDHA context\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate space क्रम HW links */
	dev->hw_link[0] = dmam_alloc_coherent(&pdev->dev,
			SAHARA_MAX_HW_LINK * माप(काष्ठा sahara_hw_link),
			&dev->hw_phys_link[0], GFP_KERNEL);
	अगर (!dev->hw_link[0]) अणु
		dev_err(&pdev->dev, "Could not allocate hw links\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 1; i < SAHARA_MAX_HW_LINK; i++) अणु
		dev->hw_phys_link[i] = dev->hw_phys_link[i - 1] +
					माप(काष्ठा sahara_hw_link);
		dev->hw_link[i] = dev->hw_link[i - 1] + 1;
	पूर्ण

	crypto_init_queue(&dev->queue, SAHARA_QUEUE_LENGTH);

	mutex_init(&dev->queue_mutex);

	dev_ptr = dev;

	dev->kthपढ़ो = kthपढ़ो_run(sahara_queue_manage, dev, "sahara_crypto");
	अगर (IS_ERR(dev->kthपढ़ो)) अणु
		वापस PTR_ERR(dev->kthपढ़ो);
	पूर्ण

	init_completion(&dev->dma_completion);

	err = clk_prepare_enable(dev->clk_ipg);
	अगर (err)
		वापस err;
	err = clk_prepare_enable(dev->clk_ahb);
	अगर (err)
		जाओ clk_ipg_disable;

	version = sahara_पढ़ो(dev, SAHARA_REG_VERSION);
	अगर (of_device_is_compatible(pdev->dev.of_node, "fsl,imx27-sahara")) अणु
		अगर (version != SAHARA_VERSION_3)
			err = -ENODEV;
	पूर्ण अन्यथा अगर (of_device_is_compatible(pdev->dev.of_node,
			"fsl,imx53-sahara")) अणु
		अगर (((version >> 8) & 0xff) != SAHARA_VERSION_4)
			err = -ENODEV;
		version = (version >> 8) & 0xff;
	पूर्ण
	अगर (err == -ENODEV) अणु
		dev_err(&pdev->dev, "SAHARA version %d not supported\n",
				version);
		जाओ err_algs;
	पूर्ण

	dev->version = version;

	sahara_ग_लिखो(dev, SAHARA_CMD_RESET | SAHARA_CMD_MODE_BATCH,
		     SAHARA_REG_CMD);
	sahara_ग_लिखो(dev, SAHARA_CONTROL_SET_THROTTLE(0) |
			SAHARA_CONTROL_SET_MAXBURST(8) |
			SAHARA_CONTROL_RNG_AUTORSD |
			SAHARA_CONTROL_ENABLE_INT,
			SAHARA_REG_CONTROL);

	err = sahara_रेजिस्टर_algs(dev);
	अगर (err)
		जाओ err_algs;

	dev_info(&pdev->dev, "SAHARA version %d initialized\n", version);

	वापस 0;

err_algs:
	kthपढ़ो_stop(dev->kthपढ़ो);
	dev_ptr = शून्य;
	clk_disable_unprepare(dev->clk_ahb);
clk_ipg_disable:
	clk_disable_unprepare(dev->clk_ipg);

	वापस err;
पूर्ण

अटल पूर्णांक sahara_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sahara_dev *dev = platक्रमm_get_drvdata(pdev);

	kthपढ़ो_stop(dev->kthपढ़ो);

	sahara_unरेजिस्टर_algs(dev);

	clk_disable_unprepare(dev->clk_ipg);
	clk_disable_unprepare(dev->clk_ahb);

	dev_ptr = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sahara_driver = अणु
	.probe		= sahara_probe,
	.हटाओ		= sahara_हटाओ,
	.driver		= अणु
		.name	= SAHARA_NAME,
		.of_match_table = sahara_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sahara_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Javier Martin <javier.martin@vista-silicon.com>");
MODULE_AUTHOR("Steffen Trumtrar <s.trumtrar@pengutronix.de>");
MODULE_DESCRIPTION("SAHARA2 HW crypto accelerator");
