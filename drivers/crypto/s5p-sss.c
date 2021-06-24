<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Cryptographic API.
//
// Support क्रम Samsung S5PV210 and Exynos HW acceleration.
//
// Copyright (C) 2011 NetUP Inc. All rights reserved.
// Copyright (c) 2017 Samsung Electronics Co., Ltd. All rights reserved.
//
// Hash part based on omap-sham.c driver.

#समावेश <linux/clk.h>
#समावेश <linux/crypto.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/scatterlist.h>

#समावेश <crypto/ctr.h>
#समावेश <crypto/aes.h>
#समावेश <crypto/algapi.h>
#समावेश <crypto/scatterwalk.h>

#समावेश <crypto/hash.h>
#समावेश <crypto/md5.h>
#समावेश <crypto/sha1.h>
#समावेश <crypto/sha2.h>
#समावेश <crypto/पूर्णांकernal/hash.h>

#घोषणा _SBF(s, v)			((v) << (s))

/* Feed control रेजिस्टरs */
#घोषणा SSS_REG_FCINTSTAT		0x0000
#घोषणा SSS_FCINTSTAT_HPARTINT		BIT(7)
#घोषणा SSS_FCINTSTAT_HDONEINT		BIT(5)
#घोषणा SSS_FCINTSTAT_BRDMAINT		BIT(3)
#घोषणा SSS_FCINTSTAT_BTDMAINT		BIT(2)
#घोषणा SSS_FCINTSTAT_HRDMAINT		BIT(1)
#घोषणा SSS_FCINTSTAT_PKDMAINT		BIT(0)

#घोषणा SSS_REG_FCINTENSET		0x0004
#घोषणा SSS_FCINTENSET_HPARTINTENSET	BIT(7)
#घोषणा SSS_FCINTENSET_HDONEINTENSET	BIT(5)
#घोषणा SSS_FCINTENSET_BRDMAINTENSET	BIT(3)
#घोषणा SSS_FCINTENSET_BTDMAINTENSET	BIT(2)
#घोषणा SSS_FCINTENSET_HRDMAINTENSET	BIT(1)
#घोषणा SSS_FCINTENSET_PKDMAINTENSET	BIT(0)

#घोषणा SSS_REG_FCINTENCLR		0x0008
#घोषणा SSS_FCINTENCLR_HPARTINTENCLR	BIT(7)
#घोषणा SSS_FCINTENCLR_HDONEINTENCLR	BIT(5)
#घोषणा SSS_FCINTENCLR_BRDMAINTENCLR	BIT(3)
#घोषणा SSS_FCINTENCLR_BTDMAINTENCLR	BIT(2)
#घोषणा SSS_FCINTENCLR_HRDMAINTENCLR	BIT(1)
#घोषणा SSS_FCINTENCLR_PKDMAINTENCLR	BIT(0)

#घोषणा SSS_REG_FCINTPEND		0x000C
#घोषणा SSS_FCINTPEND_HPARTINTP		BIT(7)
#घोषणा SSS_FCINTPEND_HDONEINTP		BIT(5)
#घोषणा SSS_FCINTPEND_BRDMAINTP		BIT(3)
#घोषणा SSS_FCINTPEND_BTDMAINTP		BIT(2)
#घोषणा SSS_FCINTPEND_HRDMAINTP		BIT(1)
#घोषणा SSS_FCINTPEND_PKDMAINTP		BIT(0)

#घोषणा SSS_REG_FCFIFOSTAT		0x0010
#घोषणा SSS_FCFIFOSTAT_BRFIFOFUL	BIT(7)
#घोषणा SSS_FCFIFOSTAT_BRFIFOEMP	BIT(6)
#घोषणा SSS_FCFIFOSTAT_BTFIFOFUL	BIT(5)
#घोषणा SSS_FCFIFOSTAT_BTFIFOEMP	BIT(4)
#घोषणा SSS_FCFIFOSTAT_HRFIFOFUL	BIT(3)
#घोषणा SSS_FCFIFOSTAT_HRFIFOEMP	BIT(2)
#घोषणा SSS_FCFIFOSTAT_PKFIFOFUL	BIT(1)
#घोषणा SSS_FCFIFOSTAT_PKFIFOEMP	BIT(0)

#घोषणा SSS_REG_FCFIFOCTRL		0x0014
#घोषणा SSS_FCFIFOCTRL_DESSEL		BIT(2)
#घोषणा SSS_HASHIN_INDEPENDENT		_SBF(0, 0x00)
#घोषणा SSS_HASHIN_CIPHER_INPUT		_SBF(0, 0x01)
#घोषणा SSS_HASHIN_CIPHER_OUTPUT	_SBF(0, 0x02)
#घोषणा SSS_HASHIN_MASK			_SBF(0, 0x03)

#घोषणा SSS_REG_FCBRDMAS		0x0020
#घोषणा SSS_REG_FCBRDMAL		0x0024
#घोषणा SSS_REG_FCBRDMAC		0x0028
#घोषणा SSS_FCBRDMAC_BYTESWAP		BIT(1)
#घोषणा SSS_FCBRDMAC_FLUSH		BIT(0)

#घोषणा SSS_REG_FCBTDMAS		0x0030
#घोषणा SSS_REG_FCBTDMAL		0x0034
#घोषणा SSS_REG_FCBTDMAC		0x0038
#घोषणा SSS_FCBTDMAC_BYTESWAP		BIT(1)
#घोषणा SSS_FCBTDMAC_FLUSH		BIT(0)

#घोषणा SSS_REG_FCHRDMAS		0x0040
#घोषणा SSS_REG_FCHRDMAL		0x0044
#घोषणा SSS_REG_FCHRDMAC		0x0048
#घोषणा SSS_FCHRDMAC_BYTESWAP		BIT(1)
#घोषणा SSS_FCHRDMAC_FLUSH		BIT(0)

#घोषणा SSS_REG_FCPKDMAS		0x0050
#घोषणा SSS_REG_FCPKDMAL		0x0054
#घोषणा SSS_REG_FCPKDMAC		0x0058
#घोषणा SSS_FCPKDMAC_BYTESWAP		BIT(3)
#घोषणा SSS_FCPKDMAC_DESCEND		BIT(2)
#घोषणा SSS_FCPKDMAC_TRANSMIT		BIT(1)
#घोषणा SSS_FCPKDMAC_FLUSH		BIT(0)

#घोषणा SSS_REG_FCPKDMAO		0x005C

/* AES रेजिस्टरs */
#घोषणा SSS_REG_AES_CONTROL		0x00
#घोषणा SSS_AES_BYTESWAP_DI		BIT(11)
#घोषणा SSS_AES_BYTESWAP_DO		BIT(10)
#घोषणा SSS_AES_BYTESWAP_IV		BIT(9)
#घोषणा SSS_AES_BYTESWAP_CNT		BIT(8)
#घोषणा SSS_AES_BYTESWAP_KEY		BIT(7)
#घोषणा SSS_AES_KEY_CHANGE_MODE		BIT(6)
#घोषणा SSS_AES_KEY_SIZE_128		_SBF(4, 0x00)
#घोषणा SSS_AES_KEY_SIZE_192		_SBF(4, 0x01)
#घोषणा SSS_AES_KEY_SIZE_256		_SBF(4, 0x02)
#घोषणा SSS_AES_FIFO_MODE		BIT(3)
#घोषणा SSS_AES_CHAIN_MODE_ECB		_SBF(1, 0x00)
#घोषणा SSS_AES_CHAIN_MODE_CBC		_SBF(1, 0x01)
#घोषणा SSS_AES_CHAIN_MODE_CTR		_SBF(1, 0x02)
#घोषणा SSS_AES_MODE_DECRYPT		BIT(0)

#घोषणा SSS_REG_AES_STATUS		0x04
#घोषणा SSS_AES_BUSY			BIT(2)
#घोषणा SSS_AES_INPUT_READY		BIT(1)
#घोषणा SSS_AES_OUTPUT_READY		BIT(0)

#घोषणा SSS_REG_AES_IN_DATA(s)		(0x10 + (s << 2))
#घोषणा SSS_REG_AES_OUT_DATA(s)		(0x20 + (s << 2))
#घोषणा SSS_REG_AES_IV_DATA(s)		(0x30 + (s << 2))
#घोषणा SSS_REG_AES_CNT_DATA(s)		(0x40 + (s << 2))
#घोषणा SSS_REG_AES_KEY_DATA(s)		(0x80 + (s << 2))

#घोषणा SSS_REG(dev, reg)		((dev)->ioaddr + (SSS_REG_##reg))
#घोषणा SSS_READ(dev, reg)		__raw_पढ़ोl(SSS_REG(dev, reg))
#घोषणा SSS_WRITE(dev, reg, val)	__raw_ग_लिखोl((val), SSS_REG(dev, reg))

#घोषणा SSS_AES_REG(dev, reg)		((dev)->aes_ioaddr + SSS_REG_##reg)
#घोषणा SSS_AES_WRITE(dev, reg, val)    __raw_ग_लिखोl((val), \
						SSS_AES_REG(dev, reg))

/* HW engine modes */
#घोषणा FLAGS_AES_DECRYPT		BIT(0)
#घोषणा FLAGS_AES_MODE_MASK		_SBF(1, 0x03)
#घोषणा FLAGS_AES_CBC			_SBF(1, 0x01)
#घोषणा FLAGS_AES_CTR			_SBF(1, 0x02)

#घोषणा AES_KEY_LEN			16
#घोषणा CRYPTO_QUEUE_LEN		1

/* HASH रेजिस्टरs */
#घोषणा SSS_REG_HASH_CTRL		0x00

#घोषणा SSS_HASH_USER_IV_EN		BIT(5)
#घोषणा SSS_HASH_INIT_BIT		BIT(4)
#घोषणा SSS_HASH_ENGINE_SHA1		_SBF(1, 0x00)
#घोषणा SSS_HASH_ENGINE_MD5		_SBF(1, 0x01)
#घोषणा SSS_HASH_ENGINE_SHA256		_SBF(1, 0x02)

#घोषणा SSS_HASH_ENGINE_MASK		_SBF(1, 0x03)

#घोषणा SSS_REG_HASH_CTRL_PAUSE		0x04

#घोषणा SSS_HASH_PAUSE			BIT(0)

#घोषणा SSS_REG_HASH_CTRL_FIFO		0x08

#घोषणा SSS_HASH_FIFO_MODE_DMA		BIT(0)
#घोषणा SSS_HASH_FIFO_MODE_CPU          0

#घोषणा SSS_REG_HASH_CTRL_SWAP		0x0C

#घोषणा SSS_HASH_BYTESWAP_DI		BIT(3)
#घोषणा SSS_HASH_BYTESWAP_DO		BIT(2)
#घोषणा SSS_HASH_BYTESWAP_IV		BIT(1)
#घोषणा SSS_HASH_BYTESWAP_KEY		BIT(0)

#घोषणा SSS_REG_HASH_STATUS		0x10

#घोषणा SSS_HASH_STATUS_MSG_DONE	BIT(6)
#घोषणा SSS_HASH_STATUS_PARTIAL_DONE	BIT(4)
#घोषणा SSS_HASH_STATUS_BUFFER_READY	BIT(0)

#घोषणा SSS_REG_HASH_MSG_SIZE_LOW	0x20
#घोषणा SSS_REG_HASH_MSG_SIZE_HIGH	0x24

#घोषणा SSS_REG_HASH_PRE_MSG_SIZE_LOW	0x28
#घोषणा SSS_REG_HASH_PRE_MSG_SIZE_HIGH	0x2C

#घोषणा SSS_REG_HASH_IV(s)		(0xB0 + ((s) << 2))
#घोषणा SSS_REG_HASH_OUT(s)		(0x100 + ((s) << 2))

#घोषणा HASH_BLOCK_SIZE			64
#घोषणा HASH_REG_SIZखातापूर्ण			4
#घोषणा HASH_MD5_MAX_REG		(MD5_DIGEST_SIZE / HASH_REG_SIZखातापूर्ण)
#घोषणा HASH_SHA1_MAX_REG		(SHA1_DIGEST_SIZE / HASH_REG_SIZखातापूर्ण)
#घोषणा HASH_SHA256_MAX_REG		(SHA256_DIGEST_SIZE / HASH_REG_SIZखातापूर्ण)

/*
 * HASH bit numbers, used by device, setting in dev->hash_flags with
 * functions set_bit(), clear_bit() or tested with test_bit() or BIT(),
 * to keep HASH state BUSY or FREE, or to संकेत state from irq_handler
 * to hash_tasklet. SGS keep track of allocated memory क्रम scatterlist
 */
#घोषणा HASH_FLAGS_BUSY		0
#घोषणा HASH_FLAGS_FINAL	1
#घोषणा HASH_FLAGS_DMA_ACTIVE	2
#घोषणा HASH_FLAGS_OUTPUT_READY	3
#घोषणा HASH_FLAGS_DMA_READY	4
#घोषणा HASH_FLAGS_SGS_COPIED	5
#घोषणा HASH_FLAGS_SGS_ALLOCED	6

/* HASH HW स्थिरants */
#घोषणा BUFLEN			HASH_BLOCK_SIZE

#घोषणा SSS_HASH_DMA_LEN_ALIGN	8
#घोषणा SSS_HASH_DMA_ALIGN_MASK	(SSS_HASH_DMA_LEN_ALIGN - 1)

#घोषणा SSS_HASH_QUEUE_LENGTH	10

/**
 * काष्ठा samsung_aes_variant - platक्रमm specअगरic SSS driver data
 * @aes_offset: AES रेजिस्टर offset from SSS module's base.
 * @hash_offset: HASH रेजिस्टर offset from SSS module's base.
 * @clk_names: names of घड़ीs needed to run SSS IP
 *
 * Specअगरies platक्रमm specअगरic configuration of SSS module.
 * Note: A काष्ठाure क्रम driver specअगरic platक्रमm data is used क्रम future
 * expansion of its usage.
 */
काष्ठा samsung_aes_variant अणु
	अचिन्हित पूर्णांक			aes_offset;
	अचिन्हित पूर्णांक			hash_offset;
	स्थिर अक्षर			*clk_names[2];
पूर्ण;

काष्ठा s5p_aes_reqctx अणु
	अचिन्हित दीर्घ			mode;
पूर्ण;

काष्ठा s5p_aes_ctx अणु
	काष्ठा s5p_aes_dev		*dev;

	u8				aes_key[AES_MAX_KEY_SIZE];
	u8				nonce[CTR_RFC3686_NONCE_SIZE];
	पूर्णांक				keylen;
पूर्ण;

/**
 * काष्ठा s5p_aes_dev - Crypto device state container
 * @dev:	Associated device
 * @clk:	Clock क्रम accessing hardware
 * @pclk:	APB bus घड़ी necessary to access the hardware
 * @ioaddr:	Mapped IO memory region
 * @aes_ioaddr:	Per-varian offset क्रम AES block IO memory
 * @irq_fc:	Feed control पूर्णांकerrupt line
 * @req:	Crypto request currently handled by the device
 * @ctx:	Configuration क्रम currently handled crypto request
 * @sg_src:	Scatter list with source data क्रम currently handled block
 *		in device.  This is DMA-mapped पूर्णांकo device.
 * @sg_dst:	Scatter list with destination data क्रम currently handled block
 *		in device. This is DMA-mapped पूर्णांकo device.
 * @sg_src_cpy:	In हाल of unaligned access, copied scatter list
 *		with source data.
 * @sg_dst_cpy:	In हाल of unaligned access, copied scatter list
 *		with destination data.
 * @tasklet:	New request scheduling jib
 * @queue:	Crypto queue
 * @busy:	Indicates whether the device is currently handling some request
 *		thus it uses some of the fields from this state, like:
 *		req, ctx, sg_src/dst (and copies).  This essentially
 *		protects against concurrent access to these fields.
 * @lock:	Lock क्रम protecting both access to device hardware रेजिस्टरs
 *		and fields related to current request (including the busy field).
 * @res:	Resources क्रम hash.
 * @io_hash_base: Per-variant offset क्रम HASH block IO memory.
 * @hash_lock:	Lock क्रम protecting hash_req, hash_queue and hash_flags
 *		variable.
 * @hash_flags:	Flags क्रम current HASH op.
 * @hash_queue:	Async hash queue.
 * @hash_tasklet: New HASH request scheduling job.
 * @xmit_buf:	Buffer क्रम current HASH request transfer पूर्णांकo SSS block.
 * @hash_req:	Current request sending to SSS HASH block.
 * @hash_sg_iter: Scatterlist transferred through DMA पूर्णांकo SSS HASH block.
 * @hash_sg_cnt: Counter क्रम hash_sg_iter.
 *
 * @use_hash:	true अगर HASH algs enabled
 */
काष्ठा s5p_aes_dev अणु
	काष्ठा device			*dev;
	काष्ठा clk			*clk;
	काष्ठा clk			*pclk;
	व्योम __iomem			*ioaddr;
	व्योम __iomem			*aes_ioaddr;
	पूर्णांक				irq_fc;

	काष्ठा skcipher_request		*req;
	काष्ठा s5p_aes_ctx		*ctx;
	काष्ठा scatterlist		*sg_src;
	काष्ठा scatterlist		*sg_dst;

	काष्ठा scatterlist		*sg_src_cpy;
	काष्ठा scatterlist		*sg_dst_cpy;

	काष्ठा tasklet_काष्ठा		tasklet;
	काष्ठा crypto_queue		queue;
	bool				busy;
	spinlock_t			lock;

	काष्ठा resource			*res;
	व्योम __iomem			*io_hash_base;

	spinlock_t			hash_lock; /* protect hash_ vars */
	अचिन्हित दीर्घ			hash_flags;
	काष्ठा crypto_queue		hash_queue;
	काष्ठा tasklet_काष्ठा		hash_tasklet;

	u8				xmit_buf[BUFLEN];
	काष्ठा ahash_request		*hash_req;
	काष्ठा scatterlist		*hash_sg_iter;
	अचिन्हित पूर्णांक			hash_sg_cnt;

	bool				use_hash;
पूर्ण;

/**
 * काष्ठा s5p_hash_reqctx - HASH request context
 * @dd:		Associated device
 * @op_update:	Current request operation (OP_UPDATE or OP_FINAL)
 * @digcnt:	Number of bytes processed by HW (without buffer[] ones)
 * @digest:	Digest message or IV क्रम partial result
 * @nregs:	Number of HW रेजिस्टरs क्रम digest or IV पढ़ो/ग_लिखो
 * @engine:	Bits क्रम selecting type of HASH in SSS block
 * @sg:		sg क्रम DMA transfer
 * @sg_len:	Length of sg क्रम DMA transfer
 * @sgl:	sg क्रम joining buffer and req->src scatterlist
 * @skip:	Skip offset in req->src क्रम current op
 * @total:	Total number of bytes क्रम current request
 * @finup:	Keep state क्रम finup or final.
 * @error:	Keep track of error.
 * @bufcnt:	Number of bytes holded in buffer[]
 * @buffer:	For byte(s) from end of req->src in UPDATE op
 */
काष्ठा s5p_hash_reqctx अणु
	काष्ठा s5p_aes_dev	*dd;
	bool			op_update;

	u64			digcnt;
	u8			digest[SHA256_DIGEST_SIZE];

	अचिन्हित पूर्णांक		nregs; /* digest_size / माप(reg) */
	u32			engine;

	काष्ठा scatterlist	*sg;
	अचिन्हित पूर्णांक		sg_len;
	काष्ठा scatterlist	sgl[2];
	अचिन्हित पूर्णांक		skip;
	अचिन्हित पूर्णांक		total;
	bool			finup;
	bool			error;

	u32			bufcnt;
	u8			buffer[];
पूर्ण;

/**
 * काष्ठा s5p_hash_ctx - HASH transक्रमmation context
 * @dd:		Associated device
 * @flags:	Bits क्रम algorithm HASH.
 * @fallback:	Software transक्रमmation क्रम zero message or size < BUFLEN.
 */
काष्ठा s5p_hash_ctx अणु
	काष्ठा s5p_aes_dev	*dd;
	अचिन्हित दीर्घ		flags;
	काष्ठा crypto_shash	*fallback;
पूर्ण;

अटल स्थिर काष्ठा samsung_aes_variant s5p_aes_data = अणु
	.aes_offset	= 0x4000,
	.hash_offset	= 0x6000,
	.clk_names	= अणु "secss", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_aes_variant exynos_aes_data = अणु
	.aes_offset	= 0x200,
	.hash_offset	= 0x400,
	.clk_names	= अणु "secss", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_aes_variant exynos5433_slim_aes_data = अणु
	.aes_offset	= 0x400,
	.hash_offset	= 0x800,
	.clk_names	= अणु "aclk", "pclk", पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s5p_sss_dt_match[] = अणु
	अणु
		.compatible = "samsung,s5pv210-secss",
		.data = &s5p_aes_data,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos4210-secss",
		.data = &exynos_aes_data,
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5433-slim-sss",
		.data = &exynos5433_slim_aes_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, s5p_sss_dt_match);

अटल अंतरभूत स्थिर काष्ठा samsung_aes_variant *find_s5p_sss_version
				   (स्थिर काष्ठा platक्रमm_device *pdev)
अणु
	अगर (IS_ENABLED(CONFIG_OF) && (pdev->dev.of_node))
		वापस of_device_get_match_data(&pdev->dev);

	वापस (स्थिर काष्ठा samsung_aes_variant *)
			platक्रमm_get_device_id(pdev)->driver_data;
पूर्ण

अटल काष्ठा s5p_aes_dev *s5p_dev;

अटल व्योम s5p_set_dma_indata(काष्ठा s5p_aes_dev *dev,
			       स्थिर काष्ठा scatterlist *sg)
अणु
	SSS_WRITE(dev, FCBRDMAS, sg_dma_address(sg));
	SSS_WRITE(dev, FCBRDMAL, sg_dma_len(sg));
पूर्ण

अटल व्योम s5p_set_dma_outdata(काष्ठा s5p_aes_dev *dev,
				स्थिर काष्ठा scatterlist *sg)
अणु
	SSS_WRITE(dev, FCBTDMAS, sg_dma_address(sg));
	SSS_WRITE(dev, FCBTDMAL, sg_dma_len(sg));
पूर्ण

अटल व्योम s5p_मुक्त_sg_cpy(काष्ठा s5p_aes_dev *dev, काष्ठा scatterlist **sg)
अणु
	पूर्णांक len;

	अगर (!*sg)
		वापस;

	len = ALIGN(dev->req->cryptlen, AES_BLOCK_SIZE);
	मुक्त_pages((अचिन्हित दीर्घ)sg_virt(*sg), get_order(len));

	kमुक्त(*sg);
	*sg = शून्य;
पूर्ण

अटल व्योम s5p_sg_copy_buf(व्योम *buf, काष्ठा scatterlist *sg,
			    अचिन्हित पूर्णांक nbytes, पूर्णांक out)
अणु
	काष्ठा scatter_walk walk;

	अगर (!nbytes)
		वापस;

	scatterwalk_start(&walk, sg);
	scatterwalk_copychunks(buf, &walk, nbytes, out);
	scatterwalk_करोne(&walk, out, 0);
पूर्ण

अटल व्योम s5p_sg_करोne(काष्ठा s5p_aes_dev *dev)
अणु
	काष्ठा skcipher_request *req = dev->req;
	काष्ठा s5p_aes_reqctx *reqctx = skcipher_request_ctx(req);

	अगर (dev->sg_dst_cpy) अणु
		dev_dbg(dev->dev,
			"Copying %d bytes of output data back to original place\n",
			dev->req->cryptlen);
		s5p_sg_copy_buf(sg_virt(dev->sg_dst_cpy), dev->req->dst,
				dev->req->cryptlen, 1);
	पूर्ण
	s5p_मुक्त_sg_cpy(dev, &dev->sg_src_cpy);
	s5p_मुक्त_sg_cpy(dev, &dev->sg_dst_cpy);
	अगर (reqctx->mode & FLAGS_AES_CBC)
		स_नकल_fromio(req->iv, dev->aes_ioaddr + SSS_REG_AES_IV_DATA(0), AES_BLOCK_SIZE);

	अन्यथा अगर (reqctx->mode & FLAGS_AES_CTR)
		स_नकल_fromio(req->iv, dev->aes_ioaddr + SSS_REG_AES_CNT_DATA(0), AES_BLOCK_SIZE);
पूर्ण

/* Calls the completion. Cannot be called with dev->lock hold. */
अटल व्योम s5p_aes_complete(काष्ठा skcipher_request *req, पूर्णांक err)
अणु
	req->base.complete(&req->base, err);
पूर्ण

अटल व्योम s5p_unset_outdata(काष्ठा s5p_aes_dev *dev)
अणु
	dma_unmap_sg(dev->dev, dev->sg_dst, 1, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम s5p_unset_indata(काष्ठा s5p_aes_dev *dev)
अणु
	dma_unmap_sg(dev->dev, dev->sg_src, 1, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक s5p_make_sg_cpy(काष्ठा s5p_aes_dev *dev, काष्ठा scatterlist *src,
			   काष्ठा scatterlist **dst)
अणु
	व्योम *pages;
	पूर्णांक len;

	*dst = kदो_स्मृति(माप(**dst), GFP_ATOMIC);
	अगर (!*dst)
		वापस -ENOMEM;

	len = ALIGN(dev->req->cryptlen, AES_BLOCK_SIZE);
	pages = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, get_order(len));
	अगर (!pages) अणु
		kमुक्त(*dst);
		*dst = शून्य;
		वापस -ENOMEM;
	पूर्ण

	s5p_sg_copy_buf(pages, src, dev->req->cryptlen, 0);

	sg_init_table(*dst, 1);
	sg_set_buf(*dst, pages, len);

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_set_outdata(काष्ठा s5p_aes_dev *dev, काष्ठा scatterlist *sg)
अणु
	अगर (!sg->length)
		वापस -EINVAL;

	अगर (!dma_map_sg(dev->dev, sg, 1, DMA_FROM_DEVICE))
		वापस -ENOMEM;

	dev->sg_dst = sg;

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_set_indata(काष्ठा s5p_aes_dev *dev, काष्ठा scatterlist *sg)
अणु
	अगर (!sg->length)
		वापस -EINVAL;

	अगर (!dma_map_sg(dev->dev, sg, 1, DMA_TO_DEVICE))
		वापस -ENOMEM;

	dev->sg_src = sg;

	वापस 0;
पूर्ण

/*
 * Returns -ERRNO on error (mapping of new data failed).
 * On success वापसs:
 *  - 0 अगर there is no more data,
 *  - 1 अगर new transmitting (output) data is पढ़ोy and its address+length
 *     have to be written to device (by calling s5p_set_dma_outdata()).
 */
अटल पूर्णांक s5p_aes_tx(काष्ठा s5p_aes_dev *dev)
अणु
	पूर्णांक ret = 0;

	s5p_unset_outdata(dev);

	अगर (!sg_is_last(dev->sg_dst)) अणु
		ret = s5p_set_outdata(dev, sg_next(dev->sg_dst));
		अगर (!ret)
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Returns -ERRNO on error (mapping of new data failed).
 * On success वापसs:
 *  - 0 अगर there is no more data,
 *  - 1 अगर new receiving (input) data is पढ़ोy and its address+length
 *     have to be written to device (by calling s5p_set_dma_indata()).
 */
अटल पूर्णांक s5p_aes_rx(काष्ठा s5p_aes_dev *dev/*, bool *set_dma*/)
अणु
	पूर्णांक ret = 0;

	s5p_unset_indata(dev);

	अगर (!sg_is_last(dev->sg_src)) अणु
		ret = s5p_set_indata(dev, sg_next(dev->sg_src));
		अगर (!ret)
			ret = 1;
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत u32 s5p_hash_पढ़ो(काष्ठा s5p_aes_dev *dd, u32 offset)
अणु
	वापस __raw_पढ़ोl(dd->io_hash_base + offset);
पूर्ण

अटल अंतरभूत व्योम s5p_hash_ग_लिखो(काष्ठा s5p_aes_dev *dd,
				  u32 offset, u32 value)
अणु
	__raw_ग_लिखोl(value, dd->io_hash_base + offset);
पूर्ण

/**
 * s5p_set_dma_hashdata() - start DMA with sg
 * @dev:	device
 * @sg:		scatterlist पढ़ोy to DMA transmit
 */
अटल व्योम s5p_set_dma_hashdata(काष्ठा s5p_aes_dev *dev,
				 स्थिर काष्ठा scatterlist *sg)
अणु
	dev->hash_sg_cnt--;
	SSS_WRITE(dev, FCHRDMAS, sg_dma_address(sg));
	SSS_WRITE(dev, FCHRDMAL, sg_dma_len(sg)); /* DMA starts */
पूर्ण

/**
 * s5p_hash_rx() - get next hash_sg_iter
 * @dev:	device
 *
 * Return:
 * 2	अगर there is no more data and it is UPDATE op
 * 1	अगर new receiving (input) data is पढ़ोy and can be written to device
 * 0	अगर there is no more data and it is FINAL op
 */
अटल पूर्णांक s5p_hash_rx(काष्ठा s5p_aes_dev *dev)
अणु
	अगर (dev->hash_sg_cnt > 0) अणु
		dev->hash_sg_iter = sg_next(dev->hash_sg_iter);
		वापस 1;
	पूर्ण

	set_bit(HASH_FLAGS_DMA_READY, &dev->hash_flags);
	अगर (test_bit(HASH_FLAGS_FINAL, &dev->hash_flags))
		वापस 0;

	वापस 2;
पूर्ण

अटल irqवापस_t s5p_aes_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा platक्रमm_device *pdev = dev_id;
	काष्ठा s5p_aes_dev *dev = platक्रमm_get_drvdata(pdev);
	काष्ठा skcipher_request *req;
	पूर्णांक err_dma_tx = 0;
	पूर्णांक err_dma_rx = 0;
	पूर्णांक err_dma_hx = 0;
	bool tx_end = false;
	bool hx_end = false;
	अचिन्हित दीर्घ flags;
	u32 status, st_bits;
	पूर्णांक err;

	spin_lock_irqsave(&dev->lock, flags);

	/*
	 * Handle rx or tx पूर्णांकerrupt. If there is still data (scatterlist did not
	 * reach end), then map next scatterlist entry.
	 * In हाल of such mapping error, s5p_aes_complete() should be called.
	 *
	 * If there is no more data in tx scatter list, call s5p_aes_complete()
	 * and schedule new tasklet.
	 *
	 * Handle hx पूर्णांकerrupt. If there is still data map next entry.
	 */
	status = SSS_READ(dev, FCINTSTAT);
	अगर (status & SSS_FCINTSTAT_BRDMAINT)
		err_dma_rx = s5p_aes_rx(dev);

	अगर (status & SSS_FCINTSTAT_BTDMAINT) अणु
		अगर (sg_is_last(dev->sg_dst))
			tx_end = true;
		err_dma_tx = s5p_aes_tx(dev);
	पूर्ण

	अगर (status & SSS_FCINTSTAT_HRDMAINT)
		err_dma_hx = s5p_hash_rx(dev);

	st_bits = status & (SSS_FCINTSTAT_BRDMAINT | SSS_FCINTSTAT_BTDMAINT |
				SSS_FCINTSTAT_HRDMAINT);
	/* clear DMA bits */
	SSS_WRITE(dev, FCINTPEND, st_bits);

	/* clear HASH irq bits */
	अगर (status & (SSS_FCINTSTAT_HDONEINT | SSS_FCINTSTAT_HPARTINT)) अणु
		/* cannot have both HPART and HDONE */
		अगर (status & SSS_FCINTSTAT_HPARTINT)
			st_bits = SSS_HASH_STATUS_PARTIAL_DONE;

		अगर (status & SSS_FCINTSTAT_HDONEINT)
			st_bits = SSS_HASH_STATUS_MSG_DONE;

		set_bit(HASH_FLAGS_OUTPUT_READY, &dev->hash_flags);
		s5p_hash_ग_लिखो(dev, SSS_REG_HASH_STATUS, st_bits);
		hx_end = true;
		/* when DONE or PART, करो not handle HASH DMA */
		err_dma_hx = 0;
	पूर्ण

	अगर (err_dma_rx < 0) अणु
		err = err_dma_rx;
		जाओ error;
	पूर्ण
	अगर (err_dma_tx < 0) अणु
		err = err_dma_tx;
		जाओ error;
	पूर्ण

	अगर (tx_end) अणु
		s5p_sg_करोne(dev);
		अगर (err_dma_hx == 1)
			s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

		spin_unlock_irqrestore(&dev->lock, flags);

		s5p_aes_complete(dev->req, 0);
		/* Device is still busy */
		tasklet_schedule(&dev->tasklet);
	पूर्ण अन्यथा अणु
		/*
		 * Writing length of DMA block (either receiving or
		 * transmitting) will start the operation immediately, so this
		 * should be करोne at the end (even after clearing pending
		 * पूर्णांकerrupts to not miss the पूर्णांकerrupt).
		 */
		अगर (err_dma_tx == 1)
			s5p_set_dma_outdata(dev, dev->sg_dst);
		अगर (err_dma_rx == 1)
			s5p_set_dma_indata(dev, dev->sg_src);
		अगर (err_dma_hx == 1)
			s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

		spin_unlock_irqrestore(&dev->lock, flags);
	पूर्ण

	जाओ hash_irq_end;

error:
	s5p_sg_करोne(dev);
	dev->busy = false;
	req = dev->req;
	अगर (err_dma_hx == 1)
		s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

	spin_unlock_irqrestore(&dev->lock, flags);
	s5p_aes_complete(req, err);

hash_irq_end:
	/*
	 * Note about अन्यथा अगर:
	 *   when hash_sg_iter reaches end and its UPDATE op,
	 *   issue SSS_HASH_PAUSE and रुको क्रम HPART irq
	 */
	अगर (hx_end)
		tasklet_schedule(&dev->hash_tasklet);
	अन्यथा अगर (err_dma_hx == 2)
		s5p_hash_ग_लिखो(dev, SSS_REG_HASH_CTRL_PAUSE,
			       SSS_HASH_PAUSE);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * s5p_hash_पढ़ो_msg() - पढ़ो message or IV from HW
 * @req:	AHASH request
 */
अटल व्योम s5p_hash_पढ़ो_msg(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा s5p_aes_dev *dd = ctx->dd;
	u32 *hash = (u32 *)ctx->digest;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ctx->nregs; i++)
		hash[i] = s5p_hash_पढ़ो(dd, SSS_REG_HASH_OUT(i));
पूर्ण

/**
 * s5p_hash_ग_लिखो_ctx_iv() - ग_लिखो IV क्रम next partial/finup op.
 * @dd:		device
 * @ctx:	request context
 */
अटल व्योम s5p_hash_ग_लिखो_ctx_iv(काष्ठा s5p_aes_dev *dd,
				  स्थिर काष्ठा s5p_hash_reqctx *ctx)
अणु
	स्थिर u32 *hash = (स्थिर u32 *)ctx->digest;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ctx->nregs; i++)
		s5p_hash_ग_लिखो(dd, SSS_REG_HASH_IV(i), hash[i]);
पूर्ण

/**
 * s5p_hash_ग_लिखो_iv() - ग_लिखो IV क्रम next partial/finup op.
 * @req:	AHASH request
 */
अटल व्योम s5p_hash_ग_लिखो_iv(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	s5p_hash_ग_लिखो_ctx_iv(ctx->dd, ctx);
पूर्ण

/**
 * s5p_hash_copy_result() - copy digest पूर्णांकo req->result
 * @req:	AHASH request
 */
अटल व्योम s5p_hash_copy_result(काष्ठा ahash_request *req)
अणु
	स्थिर काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	अगर (!req->result)
		वापस;

	स_नकल(req->result, ctx->digest, ctx->nregs * HASH_REG_SIZखातापूर्ण);
पूर्ण

/**
 * s5p_hash_dma_flush() - flush HASH DMA
 * @dev:	secss device
 */
अटल व्योम s5p_hash_dma_flush(काष्ठा s5p_aes_dev *dev)
अणु
	SSS_WRITE(dev, FCHRDMAC, SSS_FCHRDMAC_FLUSH);
पूर्ण

/**
 * s5p_hash_dma_enable() - enable DMA mode क्रम HASH
 * @dev:	secss device
 *
 * enable DMA mode क्रम HASH
 */
अटल व्योम s5p_hash_dma_enable(काष्ठा s5p_aes_dev *dev)
अणु
	s5p_hash_ग_लिखो(dev, SSS_REG_HASH_CTRL_FIFO, SSS_HASH_FIFO_MODE_DMA);
पूर्ण

/**
 * s5p_hash_irq_disable() - disable irq HASH संकेतs
 * @dev:	secss device
 * @flags:	bitfield with irq's to be disabled
 */
अटल व्योम s5p_hash_irq_disable(काष्ठा s5p_aes_dev *dev, u32 flags)
अणु
	SSS_WRITE(dev, FCINTENCLR, flags);
पूर्ण

/**
 * s5p_hash_irq_enable() - enable irq संकेतs
 * @dev:	secss device
 * @flags:	bitfield with irq's to be enabled
 */
अटल व्योम s5p_hash_irq_enable(काष्ठा s5p_aes_dev *dev, पूर्णांक flags)
अणु
	SSS_WRITE(dev, FCINTENSET, flags);
पूर्ण

/**
 * s5p_hash_set_flow() - set flow inside SecSS AES/DES with/without HASH
 * @dev:	secss device
 * @hashflow:	HASH stream flow with/without crypto AES/DES
 */
अटल व्योम s5p_hash_set_flow(काष्ठा s5p_aes_dev *dev, u32 hashflow)
अणु
	अचिन्हित दीर्घ flags;
	u32 flow;

	spin_lock_irqsave(&dev->lock, flags);

	flow = SSS_READ(dev, FCFIFOCTRL);
	flow &= ~SSS_HASHIN_MASK;
	flow |= hashflow;
	SSS_WRITE(dev, FCFIFOCTRL, flow);

	spin_unlock_irqrestore(&dev->lock, flags);
पूर्ण

/**
 * s5p_ahash_dma_init() - enable DMA and set HASH flow inside SecSS
 * @dev:	secss device
 * @hashflow:	HASH stream flow with/without AES/DES
 *
 * flush HASH DMA and enable DMA, set HASH stream flow inside SecSS HW,
 * enable HASH irq's HRDMA, HDONE, HPART
 */
अटल व्योम s5p_ahash_dma_init(काष्ठा s5p_aes_dev *dev, u32 hashflow)
अणु
	s5p_hash_irq_disable(dev, SSS_FCINTENCLR_HRDMAINTENCLR |
			     SSS_FCINTENCLR_HDONEINTENCLR |
			     SSS_FCINTENCLR_HPARTINTENCLR);
	s5p_hash_dma_flush(dev);

	s5p_hash_dma_enable(dev);
	s5p_hash_set_flow(dev, hashflow & SSS_HASHIN_MASK);
	s5p_hash_irq_enable(dev, SSS_FCINTENSET_HRDMAINTENSET |
			    SSS_FCINTENSET_HDONEINTENSET |
			    SSS_FCINTENSET_HPARTINTENSET);
पूर्ण

/**
 * s5p_hash_ग_लिखो_ctrl() - prepare HASH block in SecSS क्रम processing
 * @dd:		secss device
 * @length:	length क्रम request
 * @final:	true अगर final op
 *
 * Prepare SSS HASH block क्रम processing bytes in DMA mode. If it is called
 * after previous updates, fill up IV words. For final, calculate and set
 * lengths क्रम HASH so SecSS can finalize hash. For partial, set SSS HASH
 * length as 2^63 so it will be never reached and set to zero prelow and
 * prehigh.
 *
 * This function करोes not start DMA transfer.
 */
अटल व्योम s5p_hash_ग_लिखो_ctrl(काष्ठा s5p_aes_dev *dd, माप_प्रकार length,
				bool final)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(dd->hash_req);
	u32 prelow, prehigh, low, high;
	u32 configflags, swapflags;
	u64 पंचांगplen;

	configflags = ctx->engine | SSS_HASH_INIT_BIT;

	अगर (likely(ctx->digcnt)) अणु
		s5p_hash_ग_लिखो_ctx_iv(dd, ctx);
		configflags |= SSS_HASH_USER_IV_EN;
	पूर्ण

	अगर (final) अणु
		/* number of bytes क्रम last part */
		low = length;
		high = 0;
		/* total number of bits prev hashed */
		पंचांगplen = ctx->digcnt * 8;
		prelow = (u32)पंचांगplen;
		prehigh = (u32)(पंचांगplen >> 32);
	पूर्ण अन्यथा अणु
		prelow = 0;
		prehigh = 0;
		low = 0;
		high = BIT(31);
	पूर्ण

	swapflags = SSS_HASH_BYTESWAP_DI | SSS_HASH_BYTESWAP_DO |
		    SSS_HASH_BYTESWAP_IV | SSS_HASH_BYTESWAP_KEY;

	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_MSG_SIZE_LOW, low);
	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_MSG_SIZE_HIGH, high);
	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_PRE_MSG_SIZE_LOW, prelow);
	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_PRE_MSG_SIZE_HIGH, prehigh);

	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_CTRL_SWAP, swapflags);
	s5p_hash_ग_लिखो(dd, SSS_REG_HASH_CTRL, configflags);
पूर्ण

/**
 * s5p_hash_xmit_dma() - start DMA hash processing
 * @dd:		secss device
 * @length:	length क्रम request
 * @final:	true अगर final op
 *
 * Update digcnt here, as it is needed क्रम finup/final op.
 */
अटल पूर्णांक s5p_hash_xmit_dma(काष्ठा s5p_aes_dev *dd, माप_प्रकार length,
			     bool final)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(dd->hash_req);
	अचिन्हित पूर्णांक cnt;

	cnt = dma_map_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE);
	अगर (!cnt) अणु
		dev_err(dd->dev, "dma_map_sg error\n");
		ctx->error = true;
		वापस -EINVAL;
	पूर्ण

	set_bit(HASH_FLAGS_DMA_ACTIVE, &dd->hash_flags);
	dd->hash_sg_iter = ctx->sg;
	dd->hash_sg_cnt = cnt;
	s5p_hash_ग_लिखो_ctrl(dd, length, final);
	ctx->digcnt += length;
	ctx->total -= length;

	/* catch last पूर्णांकerrupt */
	अगर (final)
		set_bit(HASH_FLAGS_FINAL, &dd->hash_flags);

	s5p_set_dma_hashdata(dd, dd->hash_sg_iter); /* DMA starts */

	वापस -EINPROGRESS;
पूर्ण

/**
 * s5p_hash_copy_sgs() - copy request's bytes पूर्णांकo new buffer
 * @ctx:	request context
 * @sg:		source scatterlist request
 * @new_len:	number of bytes to process from sg
 *
 * Allocate new buffer, copy data क्रम HASH पूर्णांकo it. If there was xmit_buf
 * filled, copy it first, then copy data from sg पूर्णांकo it. Prepare one sgl[0]
 * with allocated buffer.
 *
 * Set bit in dd->hash_flag so we can मुक्त it after irq ends processing.
 */
अटल पूर्णांक s5p_hash_copy_sgs(काष्ठा s5p_hash_reqctx *ctx,
			     काष्ठा scatterlist *sg, अचिन्हित पूर्णांक new_len)
अणु
	अचिन्हित पूर्णांक pages, len;
	व्योम *buf;

	len = new_len + ctx->bufcnt;
	pages = get_order(len);

	buf = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, pages);
	अगर (!buf) अणु
		dev_err(ctx->dd->dev, "alloc pages for unaligned case.\n");
		ctx->error = true;
		वापस -ENOMEM;
	पूर्ण

	अगर (ctx->bufcnt)
		स_नकल(buf, ctx->dd->xmit_buf, ctx->bufcnt);

	scatterwalk_map_and_copy(buf + ctx->bufcnt, sg, ctx->skip,
				 new_len, 0);
	sg_init_table(ctx->sgl, 1);
	sg_set_buf(ctx->sgl, buf, len);
	ctx->sg = ctx->sgl;
	ctx->sg_len = 1;
	ctx->bufcnt = 0;
	ctx->skip = 0;
	set_bit(HASH_FLAGS_SGS_COPIED, &ctx->dd->hash_flags);

	वापस 0;
पूर्ण

/**
 * s5p_hash_copy_sg_lists() - copy sg list and make fixes in copy
 * @ctx:	request context
 * @sg:		source scatterlist request
 * @new_len:	number of bytes to process from sg
 *
 * Allocate new scatterlist table, copy data क्रम HASH पूर्णांकo it. If there was
 * xmit_buf filled, prepare it first, then copy page, length and offset from
 * source sg पूर्णांकo it, adjusting begin and/or end क्रम skip offset and
 * hash_later value.
 *
 * Resulting sg table will be asचिन्हित to ctx->sg. Set flag so we can मुक्त
 * it after irq ends processing.
 */
अटल पूर्णांक s5p_hash_copy_sg_lists(काष्ठा s5p_hash_reqctx *ctx,
				  काष्ठा scatterlist *sg, अचिन्हित पूर्णांक new_len)
अणु
	अचिन्हित पूर्णांक skip = ctx->skip, n = sg_nents(sg);
	काष्ठा scatterlist *पंचांगp;
	अचिन्हित पूर्णांक len;

	अगर (ctx->bufcnt)
		n++;

	ctx->sg = kदो_स्मृति_array(n, माप(*sg), GFP_KERNEL);
	अगर (!ctx->sg) अणु
		ctx->error = true;
		वापस -ENOMEM;
	पूर्ण

	sg_init_table(ctx->sg, n);

	पंचांगp = ctx->sg;

	ctx->sg_len = 0;

	अगर (ctx->bufcnt) अणु
		sg_set_buf(पंचांगp, ctx->dd->xmit_buf, ctx->bufcnt);
		पंचांगp = sg_next(पंचांगp);
		ctx->sg_len++;
	पूर्ण

	जबतक (sg && skip >= sg->length) अणु
		skip -= sg->length;
		sg = sg_next(sg);
	पूर्ण

	जबतक (sg && new_len) अणु
		len = sg->length - skip;
		अगर (new_len < len)
			len = new_len;

		new_len -= len;
		sg_set_page(पंचांगp, sg_page(sg), len, sg->offset + skip);
		skip = 0;
		अगर (new_len <= 0)
			sg_mark_end(पंचांगp);

		पंचांगp = sg_next(पंचांगp);
		ctx->sg_len++;
		sg = sg_next(sg);
	पूर्ण

	set_bit(HASH_FLAGS_SGS_ALLOCED, &ctx->dd->hash_flags);

	वापस 0;
पूर्ण

/**
 * s5p_hash_prepare_sgs() - prepare sg क्रम processing
 * @ctx:	request context
 * @sg:		source scatterlist request
 * @new_len:	number of bytes to process from sg
 * @final:	final flag
 *
 * Check two conditions: (1) अगर buffers in sg have len aligned data, and (2)
 * sg table have good aligned elements (list_ok). If one of this checks fails,
 * then either (1) allocates new buffer क्रम data with s5p_hash_copy_sgs, copy
 * data पूर्णांकo this buffer and prepare request in sgl, or (2) allocates new sg
 * table and prepare sg elements.
 *
 * For digest or finup all conditions can be good, and we may not need any
 * fixes.
 */
अटल पूर्णांक s5p_hash_prepare_sgs(काष्ठा s5p_hash_reqctx *ctx,
				काष्ठा scatterlist *sg,
				अचिन्हित पूर्णांक new_len, bool final)
अणु
	अचिन्हित पूर्णांक skip = ctx->skip, nbytes = new_len, n = 0;
	bool aligned = true, list_ok = true;
	काष्ठा scatterlist *sg_पंचांगp = sg;

	अगर (!sg || !sg->length || !new_len)
		वापस 0;

	अगर (skip || !final)
		list_ok = false;

	जबतक (nbytes > 0 && sg_पंचांगp) अणु
		n++;
		अगर (skip >= sg_पंचांगp->length) अणु
			skip -= sg_पंचांगp->length;
			अगर (!sg_पंचांगp->length) अणु
				aligned = false;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!IS_ALIGNED(sg_पंचांगp->length - skip, BUFLEN)) अणु
				aligned = false;
				अवरोध;
			पूर्ण

			अगर (nbytes < sg_पंचांगp->length - skip) अणु
				list_ok = false;
				अवरोध;
			पूर्ण

			nbytes -= sg_पंचांगp->length - skip;
			skip = 0;
		पूर्ण

		sg_पंचांगp = sg_next(sg_पंचांगp);
	पूर्ण

	अगर (!aligned)
		वापस s5p_hash_copy_sgs(ctx, sg, new_len);
	अन्यथा अगर (!list_ok)
		वापस s5p_hash_copy_sg_lists(ctx, sg, new_len);

	/*
	 * Have aligned data from previous operation and/or current
	 * Note: will enter here only अगर (digest or finup) and aligned
	 */
	अगर (ctx->bufcnt) अणु
		ctx->sg_len = n;
		sg_init_table(ctx->sgl, 2);
		sg_set_buf(ctx->sgl, ctx->dd->xmit_buf, ctx->bufcnt);
		sg_chain(ctx->sgl, 2, sg);
		ctx->sg = ctx->sgl;
		ctx->sg_len++;
	पूर्ण अन्यथा अणु
		ctx->sg = sg;
		ctx->sg_len = n;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s5p_hash_prepare_request() - prepare request क्रम processing
 * @req:	AHASH request
 * @update:	true अगर UPDATE op
 *
 * Note 1: we can have update flag _and_ final flag at the same समय.
 * Note 2: we enter here when digcnt > BUFLEN (=HASH_BLOCK_SIZE) or
 *	   either req->nbytes or ctx->bufcnt + req->nbytes is > BUFLEN or
 *	   we have final op
 */
अटल पूर्णांक s5p_hash_prepare_request(काष्ठा ahash_request *req, bool update)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	bool final = ctx->finup;
	पूर्णांक xmit_len, hash_later, nbytes;
	पूर्णांक ret;

	अगर (update)
		nbytes = req->nbytes;
	अन्यथा
		nbytes = 0;

	ctx->total = nbytes + ctx->bufcnt;
	अगर (!ctx->total)
		वापस 0;

	अगर (nbytes && (!IS_ALIGNED(ctx->bufcnt, BUFLEN))) अणु
		/* bytes left from previous request, so fill up to BUFLEN */
		पूर्णांक len = BUFLEN - ctx->bufcnt % BUFLEN;

		अगर (len > nbytes)
			len = nbytes;

		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, req->src,
					 0, len, 0);
		ctx->bufcnt += len;
		nbytes -= len;
		ctx->skip = len;
	पूर्ण अन्यथा अणु
		ctx->skip = 0;
	पूर्ण

	अगर (ctx->bufcnt)
		स_नकल(ctx->dd->xmit_buf, ctx->buffer, ctx->bufcnt);

	xmit_len = ctx->total;
	अगर (final) अणु
		hash_later = 0;
	पूर्ण अन्यथा अणु
		अगर (IS_ALIGNED(xmit_len, BUFLEN))
			xmit_len -= BUFLEN;
		अन्यथा
			xmit_len -= xmit_len & (BUFLEN - 1);

		hash_later = ctx->total - xmit_len;
		/* copy hash_later bytes from end of req->src */
		/* previous bytes are in xmit_buf, so no overग_लिखो */
		scatterwalk_map_and_copy(ctx->buffer, req->src,
					 req->nbytes - hash_later,
					 hash_later, 0);
	पूर्ण

	अगर (xmit_len > BUFLEN) अणु
		ret = s5p_hash_prepare_sgs(ctx, req->src, nbytes - hash_later,
					   final);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* have buffered data only */
		अगर (unlikely(!ctx->bufcnt)) अणु
			/* first update didn't fill up buffer */
			scatterwalk_map_and_copy(ctx->dd->xmit_buf, req->src,
						 0, xmit_len, 0);
		पूर्ण

		sg_init_table(ctx->sgl, 1);
		sg_set_buf(ctx->sgl, ctx->dd->xmit_buf, xmit_len);

		ctx->sg = ctx->sgl;
		ctx->sg_len = 1;
	पूर्ण

	ctx->bufcnt = hash_later;
	अगर (!final)
		ctx->total = xmit_len;

	वापस 0;
पूर्ण

/**
 * s5p_hash_update_dma_stop() - unmap DMA
 * @dd:		secss device
 *
 * Unmap scatterlist ctx->sg.
 */
अटल व्योम s5p_hash_update_dma_stop(काष्ठा s5p_aes_dev *dd)
अणु
	स्थिर काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(dd->hash_req);

	dma_unmap_sg(dd->dev, ctx->sg, ctx->sg_len, DMA_TO_DEVICE);
	clear_bit(HASH_FLAGS_DMA_ACTIVE, &dd->hash_flags);
पूर्ण

/**
 * s5p_hash_finish() - copy calculated digest to crypto layer
 * @req:	AHASH request
 */
अटल व्योम s5p_hash_finish(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा s5p_aes_dev *dd = ctx->dd;

	अगर (ctx->digcnt)
		s5p_hash_copy_result(req);

	dev_dbg(dd->dev, "hash_finish digcnt: %lld\n", ctx->digcnt);
पूर्ण

/**
 * s5p_hash_finish_req() - finish request
 * @req:	AHASH request
 * @err:	error
 */
अटल व्योम s5p_hash_finish_req(काष्ठा ahash_request *req, पूर्णांक err)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा s5p_aes_dev *dd = ctx->dd;
	अचिन्हित दीर्घ flags;

	अगर (test_bit(HASH_FLAGS_SGS_COPIED, &dd->hash_flags))
		मुक्त_pages((अचिन्हित दीर्घ)sg_virt(ctx->sg),
			   get_order(ctx->sg->length));

	अगर (test_bit(HASH_FLAGS_SGS_ALLOCED, &dd->hash_flags))
		kमुक्त(ctx->sg);

	ctx->sg = शून्य;
	dd->hash_flags &= ~(BIT(HASH_FLAGS_SGS_ALLOCED) |
			    BIT(HASH_FLAGS_SGS_COPIED));

	अगर (!err && !ctx->error) अणु
		s5p_hash_पढ़ो_msg(req);
		अगर (test_bit(HASH_FLAGS_FINAL, &dd->hash_flags))
			s5p_hash_finish(req);
	पूर्ण अन्यथा अणु
		ctx->error = true;
	पूर्ण

	spin_lock_irqsave(&dd->hash_lock, flags);
	dd->hash_flags &= ~(BIT(HASH_FLAGS_BUSY) | BIT(HASH_FLAGS_FINAL) |
			    BIT(HASH_FLAGS_DMA_READY) |
			    BIT(HASH_FLAGS_OUTPUT_READY));
	spin_unlock_irqrestore(&dd->hash_lock, flags);

	अगर (req->base.complete)
		req->base.complete(&req->base, err);
पूर्ण

/**
 * s5p_hash_handle_queue() - handle hash queue
 * @dd:		device s5p_aes_dev
 * @req:	AHASH request
 *
 * If req!=शून्य enqueue it on dd->queue, अगर FLAGS_BUSY is not set on the
 * device then processes the first request from the dd->queue
 *
 * Returns: see s5p_hash_final below.
 */
अटल पूर्णांक s5p_hash_handle_queue(काष्ठा s5p_aes_dev *dd,
				 काष्ठा ahash_request *req)
अणु
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा s5p_hash_reqctx *ctx;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0, ret = 0;

retry:
	spin_lock_irqsave(&dd->hash_lock, flags);
	अगर (req)
		ret = ahash_enqueue_request(&dd->hash_queue, req);

	अगर (test_bit(HASH_FLAGS_BUSY, &dd->hash_flags)) अणु
		spin_unlock_irqrestore(&dd->hash_lock, flags);
		वापस ret;
	पूर्ण

	backlog = crypto_get_backlog(&dd->hash_queue);
	async_req = crypto_dequeue_request(&dd->hash_queue);
	अगर (async_req)
		set_bit(HASH_FLAGS_BUSY, &dd->hash_flags);

	spin_unlock_irqrestore(&dd->hash_lock, flags);

	अगर (!async_req)
		वापस ret;

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	req = ahash_request_cast(async_req);
	dd->hash_req = req;
	ctx = ahash_request_ctx(req);

	err = s5p_hash_prepare_request(req, ctx->op_update);
	अगर (err || !ctx->total)
		जाओ out;

	dev_dbg(dd->dev, "handling new req, op_update: %u, nbytes: %d\n",
		ctx->op_update, req->nbytes);

	s5p_ahash_dma_init(dd, SSS_HASHIN_INDEPENDENT);
	अगर (ctx->digcnt)
		s5p_hash_ग_लिखो_iv(req); /* restore hash IV */

	अगर (ctx->op_update) अणु /* HASH_OP_UPDATE */
		err = s5p_hash_xmit_dma(dd, ctx->total, ctx->finup);
		अगर (err != -EINPROGRESS && ctx->finup && !ctx->error)
			/* no final() after finup() */
			err = s5p_hash_xmit_dma(dd, ctx->total, true);
	पूर्ण अन्यथा अणु /* HASH_OP_FINAL */
		err = s5p_hash_xmit_dma(dd, ctx->total, true);
	पूर्ण
out:
	अगर (err != -EINPROGRESS) अणु
		/* hash_tasklet_cb will not finish it, so करो it here */
		s5p_hash_finish_req(req, err);
		req = शून्य;

		/*
		 * Execute next request immediately अगर there is anything
		 * in queue.
		 */
		जाओ retry;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * s5p_hash_tasklet_cb() - hash tasklet
 * @data:	ptr to s5p_aes_dev
 */
अटल व्योम s5p_hash_tasklet_cb(अचिन्हित दीर्घ data)
अणु
	काष्ठा s5p_aes_dev *dd = (काष्ठा s5p_aes_dev *)data;

	अगर (!test_bit(HASH_FLAGS_BUSY, &dd->hash_flags)) अणु
		s5p_hash_handle_queue(dd, शून्य);
		वापस;
	पूर्ण

	अगर (test_bit(HASH_FLAGS_DMA_READY, &dd->hash_flags)) अणु
		अगर (test_and_clear_bit(HASH_FLAGS_DMA_ACTIVE,
				       &dd->hash_flags)) अणु
			s5p_hash_update_dma_stop(dd);
		पूर्ण

		अगर (test_and_clear_bit(HASH_FLAGS_OUTPUT_READY,
				       &dd->hash_flags)) अणु
			/* hash or semi-hash पढ़ोy */
			clear_bit(HASH_FLAGS_DMA_READY, &dd->hash_flags);
			जाओ finish;
		पूर्ण
	पूर्ण

	वापस;

finish:
	/* finish curent request */
	s5p_hash_finish_req(dd->hash_req, 0);

	/* If we are not busy, process next req */
	अगर (!test_bit(HASH_FLAGS_BUSY, &dd->hash_flags))
		s5p_hash_handle_queue(dd, शून्य);
पूर्ण

/**
 * s5p_hash_enqueue() - enqueue request
 * @req:	AHASH request
 * @op:		operation UPDATE (true) or FINAL (false)
 *
 * Returns: see s5p_hash_final below.
 */
अटल पूर्णांक s5p_hash_enqueue(काष्ठा ahash_request *req, bool op)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा s5p_hash_ctx *tctx = crypto_tfm_ctx(req->base.tfm);

	ctx->op_update = op;

	वापस s5p_hash_handle_queue(tctx->dd, req);
पूर्ण

/**
 * s5p_hash_update() - process the hash input data
 * @req:	AHASH request
 *
 * If request will fit in buffer, copy it and वापस immediately
 * अन्यथा enqueue it with OP_UPDATE.
 *
 * Returns: see s5p_hash_final below.
 */
अटल पूर्णांक s5p_hash_update(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	अगर (!req->nbytes)
		वापस 0;

	अगर (ctx->bufcnt + req->nbytes <= BUFLEN) अणु
		scatterwalk_map_and_copy(ctx->buffer + ctx->bufcnt, req->src,
					 0, req->nbytes, 0);
		ctx->bufcnt += req->nbytes;
		वापस 0;
	पूर्ण

	वापस s5p_hash_enqueue(req, true); /* HASH_OP_UPDATE */
पूर्ण

/**
 * s5p_hash_final() - बंद up hash and calculate digest
 * @req:	AHASH request
 *
 * Note: in final req->src करो not have any data, and req->nbytes can be
 * non-zero.
 *
 * If there were no input data processed yet and the buffered hash data is
 * less than BUFLEN (64) then calculate the final hash immediately by using
 * SW algorithm fallback.
 *
 * Otherwise enqueues the current AHASH request with OP_FINAL operation op
 * and finalize hash message in HW. Note that अगर digcnt!=0 then there were
 * previous update op, so there are always some buffered bytes in ctx->buffer,
 * which means that ctx->bufcnt!=0
 *
 * Returns:
 * 0 अगर the request has been processed immediately,
 * -EINPROGRESS अगर the operation has been queued क्रम later execution or is set
 *		to processing by HW,
 * -EBUSY अगर queue is full and request should be resubmitted later,
 * other negative values denotes an error.
 */
अटल पूर्णांक s5p_hash_final(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	ctx->finup = true;
	अगर (ctx->error)
		वापस -EINVAL; /* uncompleted hash is not needed */

	अगर (!ctx->digcnt && ctx->bufcnt < BUFLEN) अणु
		काष्ठा s5p_hash_ctx *tctx = crypto_tfm_ctx(req->base.tfm);

		वापस crypto_shash_tfm_digest(tctx->fallback, ctx->buffer,
					       ctx->bufcnt, req->result);
	पूर्ण

	वापस s5p_hash_enqueue(req, false); /* HASH_OP_FINAL */
पूर्ण

/**
 * s5p_hash_finup() - process last req->src and calculate digest
 * @req:	AHASH request containing the last update data
 *
 * Return values: see s5p_hash_final above.
 */
अटल पूर्णांक s5p_hash_finup(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	पूर्णांक err1, err2;

	ctx->finup = true;

	err1 = s5p_hash_update(req);
	अगर (err1 == -EINPROGRESS || err1 == -EBUSY)
		वापस err1;

	/*
	 * final() has to be always called to cleanup resources even अगर
	 * update() failed, except EINPROGRESS or calculate digest क्रम small
	 * size
	 */
	err2 = s5p_hash_final(req);

	वापस err1 ?: err2;
पूर्ण

/**
 * s5p_hash_init() - initialize AHASH request contex
 * @req:	AHASH request
 *
 * Init async hash request context.
 */
अटल पूर्णांक s5p_hash_init(काष्ठा ahash_request *req)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा s5p_hash_ctx *tctx = crypto_ahash_ctx(tfm);

	ctx->dd = tctx->dd;
	ctx->error = false;
	ctx->finup = false;
	ctx->bufcnt = 0;
	ctx->digcnt = 0;
	ctx->total = 0;
	ctx->skip = 0;

	dev_dbg(tctx->dd->dev, "init: digest size: %d\n",
		crypto_ahash_digestsize(tfm));

	चयन (crypto_ahash_digestsize(tfm)) अणु
	हाल MD5_DIGEST_SIZE:
		ctx->engine = SSS_HASH_ENGINE_MD5;
		ctx->nregs = HASH_MD5_MAX_REG;
		अवरोध;
	हाल SHA1_DIGEST_SIZE:
		ctx->engine = SSS_HASH_ENGINE_SHA1;
		ctx->nregs = HASH_SHA1_MAX_REG;
		अवरोध;
	हाल SHA256_DIGEST_SIZE:
		ctx->engine = SSS_HASH_ENGINE_SHA256;
		ctx->nregs = HASH_SHA256_MAX_REG;
		अवरोध;
	शेष:
		ctx->error = true;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s5p_hash_digest - calculate digest from req->src
 * @req:	AHASH request
 *
 * Return values: see s5p_hash_final above.
 */
अटल पूर्णांक s5p_hash_digest(काष्ठा ahash_request *req)
अणु
	वापस s5p_hash_init(req) ?: s5p_hash_finup(req);
पूर्ण

/**
 * s5p_hash_cra_init_alg - init crypto alg transक्रमmation
 * @tfm:	crypto transक्रमmation
 */
अटल पूर्णांक s5p_hash_cra_init_alg(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा s5p_hash_ctx *tctx = crypto_tfm_ctx(tfm);
	स्थिर अक्षर *alg_name = crypto_tfm_alg_name(tfm);

	tctx->dd = s5p_dev;
	/* Allocate a fallback and पात अगर it failed. */
	tctx->fallback = crypto_alloc_shash(alg_name, 0,
					    CRYPTO_ALG_NEED_FALLBACK);
	अगर (IS_ERR(tctx->fallback)) अणु
		pr_err("fallback alloc fails for '%s'\n", alg_name);
		वापस PTR_ERR(tctx->fallback);
	पूर्ण

	crypto_ahash_set_reqsize(__crypto_ahash_cast(tfm),
				 माप(काष्ठा s5p_hash_reqctx) + BUFLEN);

	वापस 0;
पूर्ण

/**
 * s5p_hash_cra_init - init crypto tfm
 * @tfm:	crypto transक्रमmation
 */
अटल पूर्णांक s5p_hash_cra_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस s5p_hash_cra_init_alg(tfm);
पूर्ण

/**
 * s5p_hash_cra_निकास - निकास crypto tfm
 * @tfm:	crypto transक्रमmation
 *
 * मुक्त allocated fallback
 */
अटल व्योम s5p_hash_cra_निकास(काष्ठा crypto_tfm *tfm)
अणु
	काष्ठा s5p_hash_ctx *tctx = crypto_tfm_ctx(tfm);

	crypto_मुक्त_shash(tctx->fallback);
	tctx->fallback = शून्य;
पूर्ण

/**
 * s5p_hash_export - export hash state
 * @req:	AHASH request
 * @out:	buffer क्रम exported state
 */
अटल पूर्णांक s5p_hash_export(काष्ठा ahash_request *req, व्योम *out)
अणु
	स्थिर काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);

	स_नकल(out, ctx, माप(*ctx) + ctx->bufcnt);

	वापस 0;
पूर्ण

/**
 * s5p_hash_import - import hash state
 * @req:	AHASH request
 * @in:		buffer with state to be imported from
 */
अटल पूर्णांक s5p_hash_import(काष्ठा ahash_request *req, स्थिर व्योम *in)
अणु
	काष्ठा s5p_hash_reqctx *ctx = ahash_request_ctx(req);
	काष्ठा crypto_ahash *tfm = crypto_ahash_reqtfm(req);
	काष्ठा s5p_hash_ctx *tctx = crypto_ahash_ctx(tfm);
	स्थिर काष्ठा s5p_hash_reqctx *ctx_in = in;

	स_नकल(ctx, in, माप(*ctx) + BUFLEN);
	अगर (ctx_in->bufcnt > BUFLEN) अणु
		ctx->error = true;
		वापस -EINVAL;
	पूर्ण

	ctx->dd = tctx->dd;
	ctx->error = false;

	वापस 0;
पूर्ण

अटल काष्ठा ahash_alg algs_sha1_md5_sha256[] = अणु
अणु
	.init		= s5p_hash_init,
	.update		= s5p_hash_update,
	.final		= s5p_hash_final,
	.finup		= s5p_hash_finup,
	.digest		= s5p_hash_digest,
	.export		= s5p_hash_export,
	.import		= s5p_hash_import,
	.halg.statesize = माप(काष्ठा s5p_hash_reqctx) + BUFLEN,
	.halg.digestsize	= SHA1_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha1",
		.cra_driver_name	= "exynos-sha1",
		.cra_priority		= 100,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= HASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा s5p_hash_ctx),
		.cra_alignmask		= SSS_HASH_DMA_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= s5p_hash_cra_init,
		.cra_निकास		= s5p_hash_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= s5p_hash_init,
	.update		= s5p_hash_update,
	.final		= s5p_hash_final,
	.finup		= s5p_hash_finup,
	.digest		= s5p_hash_digest,
	.export		= s5p_hash_export,
	.import		= s5p_hash_import,
	.halg.statesize = माप(काष्ठा s5p_hash_reqctx) + BUFLEN,
	.halg.digestsize	= MD5_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "md5",
		.cra_driver_name	= "exynos-md5",
		.cra_priority		= 100,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= HASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा s5p_hash_ctx),
		.cra_alignmask		= SSS_HASH_DMA_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= s5p_hash_cra_init,
		.cra_निकास		= s5p_hash_cra_निकास,
	पूर्ण
पूर्ण,
अणु
	.init		= s5p_hash_init,
	.update		= s5p_hash_update,
	.final		= s5p_hash_final,
	.finup		= s5p_hash_finup,
	.digest		= s5p_hash_digest,
	.export		= s5p_hash_export,
	.import		= s5p_hash_import,
	.halg.statesize = माप(काष्ठा s5p_hash_reqctx) + BUFLEN,
	.halg.digestsize	= SHA256_DIGEST_SIZE,
	.halg.base	= अणु
		.cra_name		= "sha256",
		.cra_driver_name	= "exynos-sha256",
		.cra_priority		= 100,
		.cra_flags		= CRYPTO_ALG_KERN_DRIVER_ONLY |
					  CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_NEED_FALLBACK,
		.cra_blocksize		= HASH_BLOCK_SIZE,
		.cra_ctxsize		= माप(काष्ठा s5p_hash_ctx),
		.cra_alignmask		= SSS_HASH_DMA_ALIGN_MASK,
		.cra_module		= THIS_MODULE,
		.cra_init		= s5p_hash_cra_init,
		.cra_निकास		= s5p_hash_cra_निकास,
	पूर्ण
पूर्ण

पूर्ण;

अटल व्योम s5p_set_aes(काष्ठा s5p_aes_dev *dev,
			स्थिर u8 *key, स्थिर u8 *iv, स्थिर u8 *ctr,
			अचिन्हित पूर्णांक keylen)
अणु
	व्योम __iomem *keystart;

	अगर (iv)
		स_नकल_toio(dev->aes_ioaddr + SSS_REG_AES_IV_DATA(0), iv,
			    AES_BLOCK_SIZE);

	अगर (ctr)
		स_नकल_toio(dev->aes_ioaddr + SSS_REG_AES_CNT_DATA(0), ctr,
			    AES_BLOCK_SIZE);

	अगर (keylen == AES_KEYSIZE_256)
		keystart = dev->aes_ioaddr + SSS_REG_AES_KEY_DATA(0);
	अन्यथा अगर (keylen == AES_KEYSIZE_192)
		keystart = dev->aes_ioaddr + SSS_REG_AES_KEY_DATA(2);
	अन्यथा
		keystart = dev->aes_ioaddr + SSS_REG_AES_KEY_DATA(4);

	स_नकल_toio(keystart, key, keylen);
पूर्ण

अटल bool s5p_is_sg_aligned(काष्ठा scatterlist *sg)
अणु
	जबतक (sg) अणु
		अगर (!IS_ALIGNED(sg->length, AES_BLOCK_SIZE))
			वापस false;
		sg = sg_next(sg);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक s5p_set_indata_start(काष्ठा s5p_aes_dev *dev,
				काष्ठा skcipher_request *req)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक err;

	dev->sg_src_cpy = शून्य;
	sg = req->src;
	अगर (!s5p_is_sg_aligned(sg)) अणु
		dev_dbg(dev->dev,
			"At least one unaligned source scatter list, making a copy\n");
		err = s5p_make_sg_cpy(dev, sg, &dev->sg_src_cpy);
		अगर (err)
			वापस err;

		sg = dev->sg_src_cpy;
	पूर्ण

	err = s5p_set_indata(dev, sg);
	अगर (err) अणु
		s5p_मुक्त_sg_cpy(dev, &dev->sg_src_cpy);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_set_outdata_start(काष्ठा s5p_aes_dev *dev,
				 काष्ठा skcipher_request *req)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक err;

	dev->sg_dst_cpy = शून्य;
	sg = req->dst;
	अगर (!s5p_is_sg_aligned(sg)) अणु
		dev_dbg(dev->dev,
			"At least one unaligned dest scatter list, making a copy\n");
		err = s5p_make_sg_cpy(dev, sg, &dev->sg_dst_cpy);
		अगर (err)
			वापस err;

		sg = dev->sg_dst_cpy;
	पूर्ण

	err = s5p_set_outdata(dev, sg);
	अगर (err) अणु
		s5p_मुक्त_sg_cpy(dev, &dev->sg_dst_cpy);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम s5p_aes_crypt_start(काष्ठा s5p_aes_dev *dev, अचिन्हित दीर्घ mode)
अणु
	काष्ठा skcipher_request *req = dev->req;
	u32 aes_control;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	u8 *iv, *ctr;

	/* This sets bit [13:12] to 00, which selects 128-bit counter */
	aes_control = SSS_AES_KEY_CHANGE_MODE;
	अगर (mode & FLAGS_AES_DECRYPT)
		aes_control |= SSS_AES_MODE_DECRYPT;

	अगर ((mode & FLAGS_AES_MODE_MASK) == FLAGS_AES_CBC) अणु
		aes_control |= SSS_AES_CHAIN_MODE_CBC;
		iv = req->iv;
		ctr = शून्य;
	पूर्ण अन्यथा अगर ((mode & FLAGS_AES_MODE_MASK) == FLAGS_AES_CTR) अणु
		aes_control |= SSS_AES_CHAIN_MODE_CTR;
		iv = शून्य;
		ctr = req->iv;
	पूर्ण अन्यथा अणु
		iv = शून्य; /* AES_ECB */
		ctr = शून्य;
	पूर्ण

	अगर (dev->ctx->keylen == AES_KEYSIZE_192)
		aes_control |= SSS_AES_KEY_SIZE_192;
	अन्यथा अगर (dev->ctx->keylen == AES_KEYSIZE_256)
		aes_control |= SSS_AES_KEY_SIZE_256;

	aes_control |= SSS_AES_FIFO_MODE;

	/* as a variant it is possible to use byte swapping on DMA side */
	aes_control |= SSS_AES_BYTESWAP_DI
		    |  SSS_AES_BYTESWAP_DO
		    |  SSS_AES_BYTESWAP_IV
		    |  SSS_AES_BYTESWAP_KEY
		    |  SSS_AES_BYTESWAP_CNT;

	spin_lock_irqsave(&dev->lock, flags);

	SSS_WRITE(dev, FCINTENCLR,
		  SSS_FCINTENCLR_BTDMAINTENCLR | SSS_FCINTENCLR_BRDMAINTENCLR);
	SSS_WRITE(dev, FCFIFOCTRL, 0x00);

	err = s5p_set_indata_start(dev, req);
	अगर (err)
		जाओ indata_error;

	err = s5p_set_outdata_start(dev, req);
	अगर (err)
		जाओ outdata_error;

	SSS_AES_WRITE(dev, AES_CONTROL, aes_control);
	s5p_set_aes(dev, dev->ctx->aes_key, iv, ctr, dev->ctx->keylen);

	s5p_set_dma_indata(dev,  dev->sg_src);
	s5p_set_dma_outdata(dev, dev->sg_dst);

	SSS_WRITE(dev, FCINTENSET,
		  SSS_FCINTENSET_BTDMAINTENSET | SSS_FCINTENSET_BRDMAINTENSET);

	spin_unlock_irqrestore(&dev->lock, flags);

	वापस;

outdata_error:
	s5p_unset_indata(dev);

indata_error:
	s5p_sg_करोne(dev);
	dev->busy = false;
	spin_unlock_irqrestore(&dev->lock, flags);
	s5p_aes_complete(req, err);
पूर्ण

अटल व्योम s5p_tasklet_cb(अचिन्हित दीर्घ data)
अणु
	काष्ठा s5p_aes_dev *dev = (काष्ठा s5p_aes_dev *)data;
	काष्ठा crypto_async_request *async_req, *backlog;
	काष्ठा s5p_aes_reqctx *reqctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->lock, flags);
	backlog   = crypto_get_backlog(&dev->queue);
	async_req = crypto_dequeue_request(&dev->queue);

	अगर (!async_req) अणु
		dev->busy = false;
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&dev->lock, flags);

	अगर (backlog)
		backlog->complete(backlog, -EINPROGRESS);

	dev->req = skcipher_request_cast(async_req);
	dev->ctx = crypto_tfm_ctx(dev->req->base.tfm);
	reqctx   = skcipher_request_ctx(dev->req);

	s5p_aes_crypt_start(dev, reqctx->mode);
पूर्ण

अटल पूर्णांक s5p_aes_handle_req(काष्ठा s5p_aes_dev *dev,
			      काष्ठा skcipher_request *req)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&dev->lock, flags);
	err = crypto_enqueue_request(&dev->queue, &req->base);
	अगर (dev->busy) अणु
		spin_unlock_irqrestore(&dev->lock, flags);
		वापस err;
	पूर्ण
	dev->busy = true;

	spin_unlock_irqrestore(&dev->lock, flags);

	tasklet_schedule(&dev->tasklet);

	वापस err;
पूर्ण

अटल पूर्णांक s5p_aes_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा crypto_skcipher *tfm = crypto_skcipher_reqtfm(req);
	काष्ठा s5p_aes_reqctx *reqctx = skcipher_request_ctx(req);
	काष्ठा s5p_aes_ctx *ctx = crypto_skcipher_ctx(tfm);
	काष्ठा s5p_aes_dev *dev = ctx->dev;

	अगर (!req->cryptlen)
		वापस 0;

	अगर (!IS_ALIGNED(req->cryptlen, AES_BLOCK_SIZE) &&
			((mode & FLAGS_AES_MODE_MASK) != FLAGS_AES_CTR)) अणु
		dev_dbg(dev->dev, "request size is not exact amount of AES blocks\n");
		वापस -EINVAL;
	पूर्ण

	reqctx->mode = mode;

	वापस s5p_aes_handle_req(dev, req);
पूर्ण

अटल पूर्णांक s5p_aes_setkey(काष्ठा crypto_skcipher *cipher,
			  स्थिर u8 *key, अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा crypto_tfm *tfm = crypto_skcipher_tfm(cipher);
	काष्ठा s5p_aes_ctx *ctx = crypto_tfm_ctx(tfm);

	अगर (keylen != AES_KEYSIZE_128 &&
	    keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	स_नकल(ctx->aes_key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस s5p_aes_crypt(req, 0);
पूर्ण

अटल पूर्णांक s5p_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस s5p_aes_crypt(req, FLAGS_AES_DECRYPT);
पूर्ण

अटल पूर्णांक s5p_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस s5p_aes_crypt(req, FLAGS_AES_CBC);
पूर्ण

अटल पूर्णांक s5p_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस s5p_aes_crypt(req, FLAGS_AES_DECRYPT | FLAGS_AES_CBC);
पूर्ण

अटल पूर्णांक s5p_aes_ctr_crypt(काष्ठा skcipher_request *req)
अणु
	वापस s5p_aes_crypt(req, FLAGS_AES_CTR);
पूर्ण

अटल पूर्णांक s5p_aes_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा s5p_aes_ctx *ctx = crypto_skcipher_ctx(tfm);

	ctx->dev = s5p_dev;
	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा s5p_aes_reqctx));

	वापस 0;
पूर्ण

अटल काष्ठा skcipher_alg algs[] = अणु
	अणु
		.base.cra_name		= "ecb(aes)",
		.base.cra_driver_name	= "ecb-aes-s5p",
		.base.cra_priority	= 100,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा s5p_aes_ctx),
		.base.cra_alignmask	= 0x0f,
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.setkey			= s5p_aes_setkey,
		.encrypt		= s5p_aes_ecb_encrypt,
		.decrypt		= s5p_aes_ecb_decrypt,
		.init			= s5p_aes_init_tfm,
	पूर्ण,
	अणु
		.base.cra_name		= "cbc(aes)",
		.base.cra_driver_name	= "cbc-aes-s5p",
		.base.cra_priority	= 100,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize	= AES_BLOCK_SIZE,
		.base.cra_ctxsize	= माप(काष्ठा s5p_aes_ctx),
		.base.cra_alignmask	= 0x0f,
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= s5p_aes_setkey,
		.encrypt		= s5p_aes_cbc_encrypt,
		.decrypt		= s5p_aes_cbc_decrypt,
		.init			= s5p_aes_init_tfm,
	पूर्ण,
	अणु
		.base.cra_name		= "ctr(aes)",
		.base.cra_driver_name	= "ctr-aes-s5p",
		.base.cra_priority	= 100,
		.base.cra_flags		= CRYPTO_ALG_ASYNC |
					  CRYPTO_ALG_KERN_DRIVER_ONLY,
		.base.cra_blocksize	= 1,
		.base.cra_ctxsize	= माप(काष्ठा s5p_aes_ctx),
		.base.cra_alignmask	= 0x0f,
		.base.cra_module	= THIS_MODULE,

		.min_keysize		= AES_MIN_KEY_SIZE,
		.max_keysize		= AES_MAX_KEY_SIZE,
		.ivsize			= AES_BLOCK_SIZE,
		.setkey			= s5p_aes_setkey,
		.encrypt		= s5p_aes_ctr_crypt,
		.decrypt		= s5p_aes_ctr_crypt,
		.init			= s5p_aes_init_tfm,
	पूर्ण,
पूर्ण;

अटल पूर्णांक s5p_aes_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, j, err;
	स्थिर काष्ठा samsung_aes_variant *variant;
	काष्ठा s5p_aes_dev *pdata;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक hash_i;

	अगर (s5p_dev)
		वापस -EEXIST;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	variant = find_s5p_sss_version(pdev);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	/*
	 * Note: HASH and PRNG uses the same रेजिस्टरs in secss, aव्योम
	 * overग_लिखो each other. This will drop HASH when CONFIG_EXYNOS_RNG
	 * is enabled in config. We need larger size क्रम HASH रेजिस्टरs in
	 * secss, current describe only AES/DES
	 */
	अगर (IS_ENABLED(CONFIG_CRYPTO_DEV_EXYNOS_HASH)) अणु
		अगर (variant == &exynos_aes_data) अणु
			res->end += 0x300;
			pdata->use_hash = true;
		पूर्ण
	पूर्ण

	pdata->res = res;
	pdata->ioaddr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(pdata->ioaddr)) अणु
		अगर (!pdata->use_hash)
			वापस PTR_ERR(pdata->ioaddr);
		/* try AES without HASH */
		res->end -= 0x300;
		pdata->use_hash = false;
		pdata->ioaddr = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(pdata->ioaddr))
			वापस PTR_ERR(pdata->ioaddr);
	पूर्ण

	pdata->clk = devm_clk_get(dev, variant->clk_names[0]);
	अगर (IS_ERR(pdata->clk))
		वापस dev_err_probe(dev, PTR_ERR(pdata->clk),
				     "failed to find secss clock %s\n",
				     variant->clk_names[0]);

	err = clk_prepare_enable(pdata->clk);
	अगर (err < 0) अणु
		dev_err(dev, "Enabling clock %s failed, err %d\n",
			variant->clk_names[0], err);
		वापस err;
	पूर्ण

	अगर (variant->clk_names[1]) अणु
		pdata->pclk = devm_clk_get(dev, variant->clk_names[1]);
		अगर (IS_ERR(pdata->pclk)) अणु
			err = dev_err_probe(dev, PTR_ERR(pdata->pclk),
					    "failed to find clock %s\n",
					    variant->clk_names[1]);
			जाओ err_clk;
		पूर्ण

		err = clk_prepare_enable(pdata->pclk);
		अगर (err < 0) अणु
			dev_err(dev, "Enabling clock %s failed, err %d\n",
				variant->clk_names[0], err);
			जाओ err_clk;
		पूर्ण
	पूर्ण अन्यथा अणु
		pdata->pclk = शून्य;
	पूर्ण

	spin_lock_init(&pdata->lock);
	spin_lock_init(&pdata->hash_lock);

	pdata->aes_ioaddr = pdata->ioaddr + variant->aes_offset;
	pdata->io_hash_base = pdata->ioaddr + variant->hash_offset;

	pdata->irq_fc = platक्रमm_get_irq(pdev, 0);
	अगर (pdata->irq_fc < 0) अणु
		err = pdata->irq_fc;
		dev_warn(dev, "feed control interrupt is not available.\n");
		जाओ err_irq;
	पूर्ण
	err = devm_request_thपढ़ोed_irq(dev, pdata->irq_fc, शून्य,
					s5p_aes_पूर्णांकerrupt, IRQF_ONESHOT,
					pdev->name, pdev);
	अगर (err < 0) अणु
		dev_warn(dev, "feed control interrupt is not available.\n");
		जाओ err_irq;
	पूर्ण

	pdata->busy = false;
	pdata->dev = dev;
	platक्रमm_set_drvdata(pdev, pdata);
	s5p_dev = pdata;

	tasklet_init(&pdata->tasklet, s5p_tasklet_cb, (अचिन्हित दीर्घ)pdata);
	crypto_init_queue(&pdata->queue, CRYPTO_QUEUE_LEN);

	क्रम (i = 0; i < ARRAY_SIZE(algs); i++) अणु
		err = crypto_रेजिस्टर_skcipher(&algs[i]);
		अगर (err)
			जाओ err_algs;
	पूर्ण

	अगर (pdata->use_hash) अणु
		tasklet_init(&pdata->hash_tasklet, s5p_hash_tasklet_cb,
			     (अचिन्हित दीर्घ)pdata);
		crypto_init_queue(&pdata->hash_queue, SSS_HASH_QUEUE_LENGTH);

		क्रम (hash_i = 0; hash_i < ARRAY_SIZE(algs_sha1_md5_sha256);
		     hash_i++) अणु
			काष्ठा ahash_alg *alg;

			alg = &algs_sha1_md5_sha256[hash_i];
			err = crypto_रेजिस्टर_ahash(alg);
			अगर (err) अणु
				dev_err(dev, "can't register '%s': %d\n",
					alg->halg.base.cra_driver_name, err);
				जाओ err_hash;
			पूर्ण
		पूर्ण
	पूर्ण

	dev_info(dev, "s5p-sss driver registered\n");

	वापस 0;

err_hash:
	क्रम (j = hash_i - 1; j >= 0; j--)
		crypto_unरेजिस्टर_ahash(&algs_sha1_md5_sha256[j]);

	tasklet_समाप्त(&pdata->hash_tasklet);
	res->end -= 0x300;

err_algs:
	अगर (i < ARRAY_SIZE(algs))
		dev_err(dev, "can't register '%s': %d\n", algs[i].base.cra_name,
			err);

	क्रम (j = 0; j < i; j++)
		crypto_unरेजिस्टर_skcipher(&algs[j]);

	tasklet_समाप्त(&pdata->tasklet);

err_irq:
	clk_disable_unprepare(pdata->pclk);

err_clk:
	clk_disable_unprepare(pdata->clk);
	s5p_dev = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक s5p_aes_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s5p_aes_dev *pdata = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	अगर (!pdata)
		वापस -ENODEV;

	क्रम (i = 0; i < ARRAY_SIZE(algs); i++)
		crypto_unरेजिस्टर_skcipher(&algs[i]);

	tasklet_समाप्त(&pdata->tasklet);
	अगर (pdata->use_hash) अणु
		क्रम (i = ARRAY_SIZE(algs_sha1_md5_sha256) - 1; i >= 0; i--)
			crypto_unरेजिस्टर_ahash(&algs_sha1_md5_sha256[i]);

		pdata->res->end -= 0x300;
		tasklet_समाप्त(&pdata->hash_tasklet);
		pdata->use_hash = false;
	पूर्ण

	clk_disable_unprepare(pdata->pclk);

	clk_disable_unprepare(pdata->clk);
	s5p_dev = शून्य;

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver s5p_aes_crypto = अणु
	.probe	= s5p_aes_probe,
	.हटाओ	= s5p_aes_हटाओ,
	.driver	= अणु
		.name	= "s5p-secss",
		.of_match_table = s5p_sss_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s5p_aes_crypto);

MODULE_DESCRIPTION("S5PV210 AES hw acceleration support.");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Vladimir Zapolskiy <vzapolskiy@gmail.com>");
MODULE_AUTHOR("Kamil Konieczny <k.konieczny@partner.samsung.com>");
