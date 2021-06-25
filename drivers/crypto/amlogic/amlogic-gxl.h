<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * amlogic.h - hardware cryptographic offloader क्रम Amlogic SoC
 *
 * Copyright (C) 2018-2019 Corentin LABBE <clabbe@baylibre.com>
 */
#समावेश <crypto/aes.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/skcipher.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/crypto.h>
#समावेश <linux/scatterlist.h>

#घोषणा MODE_KEY 1
#घोषणा MODE_AES_128 0x8
#घोषणा MODE_AES_192 0x9
#घोषणा MODE_AES_256 0xa

#घोषणा MESON_DECRYPT 0
#घोषणा MESON_ENCRYPT 1

#घोषणा MESON_OPMODE_ECB 0
#घोषणा MESON_OPMODE_CBC 1

#घोषणा MAXFLOW 2

#घोषणा MAXDESC 64

#घोषणा DESC_LAST BIT(18)
#घोषणा DESC_ENCRYPTION BIT(28)
#घोषणा DESC_OWN BIT(31)

/*
 * काष्ठा meson_desc - Descriptor क्रम DMA operations
 * Note that without datasheet, some are unknown
 * @t_status:	Descriptor of the cipher operation (see description below)
 * @t_src:	Physical address of data to पढ़ो
 * @t_dst:	Physical address of data to ग_लिखो
 * t_status is segmented like this:
 * @len:	0-16	length of data to operate
 * @irq:	17	Ignored by hardware
 * @eoc:	18	End means the descriptor is the last
 * @loop:	19	Unknown
 * @mode:	20-23	Type of algorithm (AES, SHA)
 * @begin:	24	Unknown
 * @end:	25	Unknown
 * @op_mode:	26-27	Blockmode (CBC, ECB)
 * @enc:	28	0 means decryption, 1 is क्रम encryption
 * @block:	29	Unknown
 * @error:	30	Unknown
 * @owner:	31	owner of the descriptor, 1 own by HW
 */
काष्ठा meson_desc अणु
	__le32 t_status;
	__le32 t_src;
	__le32 t_dst;
पूर्ण;

/*
 * काष्ठा meson_flow - Inक्रमmation used by each flow
 * @engine:	ptr to the crypto_engine क्रम this flow
 * @keylen:	keylen क्रम this flow operation
 * @complete:	completion क्रम the current task on this flow
 * @status:	set to 1 by पूर्णांकerrupt अगर task is करोne
 * @t_phy:	Physical address of task
 * @tl:		poपूर्णांकer to the current ce_task क्रम this flow
 * @stat_req:	number of request करोne by this flow
 */
काष्ठा meson_flow अणु
	काष्ठा crypto_engine *engine;
	काष्ठा completion complete;
	पूर्णांक status;
	अचिन्हित पूर्णांक keylen;
	dma_addr_t t_phy;
	काष्ठा meson_desc *tl;
#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	अचिन्हित दीर्घ stat_req;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा meson_dev - मुख्य container क्रम all this driver inक्रमmation
 * @base:	base address of amlogic-crypto
 * @busclk:	bus घड़ी क्रम amlogic-crypto
 * @dev:	the platक्रमm device
 * @chanlist:	array of all flow
 * @flow:	flow to use in next request
 * @irqs:	IRQ numbers क्रम amlogic-crypto
 * @dbgfs_dir:	Debugfs dentry क्रम statistic directory
 * @dbgfs_stats: Debugfs dentry क्रम statistic counters
 */
काष्ठा meson_dev अणु
	व्योम __iomem *base;
	काष्ठा clk *busclk;
	काष्ठा device *dev;
	काष्ठा meson_flow *chanlist;
	atomic_t flow;
	पूर्णांक *irqs;
#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	काष्ठा dentry *dbgfs_dir;
#पूर्ण_अगर
पूर्ण;

/*
 * काष्ठा meson_cipher_req_ctx - context क्रम a skcipher request
 * @op_dir:	direction (encrypt vs decrypt) क्रम this request
 * @flow:	the flow to use क्रम this request
 */
काष्ठा meson_cipher_req_ctx अणु
	u32 op_dir;
	पूर्णांक flow;
	काष्ठा skcipher_request fallback_req;	// keep at the end
पूर्ण;

/*
 * काष्ठा meson_cipher_tfm_ctx - context क्रम a skcipher TFM
 * @enginectx:		crypto_engine used by this TFM
 * @key:		poपूर्णांकer to key data
 * @keylen:		len of the key
 * @keymode:		The keymode(type and size of key) associated with this TFM
 * @mc:			poपूर्णांकer to the निजी data of driver handling this TFM
 * @fallback_tfm:	poपूर्णांकer to the fallback TFM
 */
काष्ठा meson_cipher_tfm_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	u32 *key;
	u32 keylen;
	u32 keymode;
	काष्ठा meson_dev *mc;
	काष्ठा crypto_skcipher *fallback_tfm;
पूर्ण;

/*
 * काष्ठा meson_alg_ढाँचा - crypto_alg ढाँचा
 * @type:		the CRYPTO_ALG_TYPE क्रम this ढाँचा
 * @blockmode:		the type of block operation
 * @mc:			poपूर्णांकer to the meson_dev काष्ठाure associated with this ढाँचा
 * @alg:		one of sub काष्ठा must be used
 * @stat_req:		number of request करोne on this ढाँचा
 * @stat_fb:		total of all data len करोne on this ढाँचा
 */
काष्ठा meson_alg_ढाँचा अणु
	u32 type;
	u32 blockmode;
	जोड़ अणु
		काष्ठा skcipher_alg skcipher;
	पूर्ण alg;
	काष्ठा meson_dev *mc;
#अगर_घोषित CONFIG_CRYPTO_DEV_AMLOGIC_GXL_DEBUG
	अचिन्हित दीर्घ stat_req;
	अचिन्हित दीर्घ stat_fb;
#पूर्ण_अगर
पूर्ण;

पूर्णांक meson_enqueue(काष्ठा crypto_async_request *areq, u32 type);

पूर्णांक meson_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
		     अचिन्हित पूर्णांक keylen);
पूर्णांक meson_cipher_init(काष्ठा crypto_tfm *tfm);
व्योम meson_cipher_निकास(काष्ठा crypto_tfm *tfm);
पूर्णांक meson_skdecrypt(काष्ठा skcipher_request *areq);
पूर्णांक meson_skencrypt(काष्ठा skcipher_request *areq);
