<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) STMicroelectronics SA 2017
 * Author: Fabien Dessenne <fabien.dessenne@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>

#समावेश <crypto/aes.h>
#समावेश <crypto/पूर्णांकernal/des.h>
#समावेश <crypto/engine.h>
#समावेश <crypto/scatterwalk.h>
#समावेश <crypto/पूर्णांकernal/aead.h>
#समावेश <crypto/पूर्णांकernal/skcipher.h>

#घोषणा DRIVER_NAME             "stm32-cryp"

/* Bit [0] encrypt / decrypt */
#घोषणा FLG_ENCRYPT             BIT(0)
/* Bit [8..1] algo & operation mode */
#घोषणा FLG_AES                 BIT(1)
#घोषणा FLG_DES                 BIT(2)
#घोषणा FLG_TDES                BIT(3)
#घोषणा FLG_ECB                 BIT(4)
#घोषणा FLG_CBC                 BIT(5)
#घोषणा FLG_CTR                 BIT(6)
#घोषणा FLG_GCM                 BIT(7)
#घोषणा FLG_CCM                 BIT(8)
/* Mode mask = bits [15..0] */
#घोषणा FLG_MODE_MASK           GENMASK(15, 0)
/* Bit [31..16] status  */
#घोषणा FLG_CCM_PADDED_WA       BIT(16)

/* Registers */
#घोषणा CRYP_CR                 0x00000000
#घोषणा CRYP_SR                 0x00000004
#घोषणा CRYP_DIN                0x00000008
#घोषणा CRYP_DOUT               0x0000000C
#घोषणा CRYP_DMACR              0x00000010
#घोषणा CRYP_IMSCR              0x00000014
#घोषणा CRYP_RISR               0x00000018
#घोषणा CRYP_MISR               0x0000001C
#घोषणा CRYP_K0LR               0x00000020
#घोषणा CRYP_K0RR               0x00000024
#घोषणा CRYP_K1LR               0x00000028
#घोषणा CRYP_K1RR               0x0000002C
#घोषणा CRYP_K2LR               0x00000030
#घोषणा CRYP_K2RR               0x00000034
#घोषणा CRYP_K3LR               0x00000038
#घोषणा CRYP_K3RR               0x0000003C
#घोषणा CRYP_IV0LR              0x00000040
#घोषणा CRYP_IV0RR              0x00000044
#घोषणा CRYP_IV1LR              0x00000048
#घोषणा CRYP_IV1RR              0x0000004C
#घोषणा CRYP_CSGCMCCM0R         0x00000050
#घोषणा CRYP_CSGCM0R            0x00000070

/* Registers values */
#घोषणा CR_DEC_NOT_ENC          0x00000004
#घोषणा CR_TDES_ECB             0x00000000
#घोषणा CR_TDES_CBC             0x00000008
#घोषणा CR_DES_ECB              0x00000010
#घोषणा CR_DES_CBC              0x00000018
#घोषणा CR_AES_ECB              0x00000020
#घोषणा CR_AES_CBC              0x00000028
#घोषणा CR_AES_CTR              0x00000030
#घोषणा CR_AES_KP               0x00000038
#घोषणा CR_AES_GCM              0x00080000
#घोषणा CR_AES_CCM              0x00080008
#घोषणा CR_AES_UNKNOWN          0xFFFFFFFF
#घोषणा CR_ALGO_MASK            0x00080038
#घोषणा CR_DATA32               0x00000000
#घोषणा CR_DATA16               0x00000040
#घोषणा CR_DATA8                0x00000080
#घोषणा CR_DATA1                0x000000C0
#घोषणा CR_KEY128               0x00000000
#घोषणा CR_KEY192               0x00000100
#घोषणा CR_KEY256               0x00000200
#घोषणा CR_FFLUSH               0x00004000
#घोषणा CR_CRYPEN               0x00008000
#घोषणा CR_PH_INIT              0x00000000
#घोषणा CR_PH_HEADER            0x00010000
#घोषणा CR_PH_PAYLOAD           0x00020000
#घोषणा CR_PH_FINAL             0x00030000
#घोषणा CR_PH_MASK              0x00030000
#घोषणा CR_NBPBL_SHIFT          20

#घोषणा SR_BUSY                 0x00000010
#घोषणा SR_OFNE                 0x00000004

#घोषणा IMSCR_IN                BIT(0)
#घोषणा IMSCR_OUT               BIT(1)

#घोषणा MISR_IN                 BIT(0)
#घोषणा MISR_OUT                BIT(1)

/* Misc */
#घोषणा AES_BLOCK_32            (AES_BLOCK_SIZE / माप(u32))
#घोषणा GCM_CTR_INIT            2
#घोषणा _walked_in              (cryp->in_walk.offset - cryp->in_sg->offset)
#घोषणा _walked_out             (cryp->out_walk.offset - cryp->out_sg->offset)
#घोषणा CRYP_AUTOSUSPEND_DELAY	50

काष्ठा sपंचांग32_cryp_caps अणु
	bool                    swap_final;
	bool                    padding_wa;
पूर्ण;

काष्ठा sपंचांग32_cryp_ctx अणु
	काष्ठा crypto_engine_ctx enginectx;
	काष्ठा sपंचांग32_cryp       *cryp;
	पूर्णांक                     keylen;
	__be32                  key[AES_KEYSIZE_256 / माप(u32)];
	अचिन्हित दीर्घ           flags;
पूर्ण;

काष्ठा sपंचांग32_cryp_reqctx अणु
	अचिन्हित दीर्घ mode;
पूर्ण;

काष्ठा sपंचांग32_cryp अणु
	काष्ठा list_head        list;
	काष्ठा device           *dev;
	व्योम __iomem            *regs;
	काष्ठा clk              *clk;
	अचिन्हित दीर्घ           flags;
	u32                     irq_status;
	स्थिर काष्ठा sपंचांग32_cryp_caps *caps;
	काष्ठा sपंचांग32_cryp_ctx   *ctx;

	काष्ठा crypto_engine    *engine;

	काष्ठा skcipher_request *req;
	काष्ठा aead_request     *areq;

	माप_प्रकार                  authsize;
	माप_प्रकार                  hw_blocksize;

	माप_प्रकार                  total_in;
	माप_प्रकार                  total_in_save;
	माप_प्रकार                  total_out;
	माप_प्रकार                  total_out_save;

	काष्ठा scatterlist      *in_sg;
	काष्ठा scatterlist      *out_sg;
	काष्ठा scatterlist      *out_sg_save;

	काष्ठा scatterlist      in_sgl;
	काष्ठा scatterlist      out_sgl;
	bool                    sgs_copied;

	पूर्णांक                     in_sg_len;
	पूर्णांक                     out_sg_len;

	काष्ठा scatter_walk     in_walk;
	काष्ठा scatter_walk     out_walk;

	u32                     last_ctr[4];
	u32                     gcm_ctr;
पूर्ण;

काष्ठा sपंचांग32_cryp_list अणु
	काष्ठा list_head        dev_list;
	spinlock_t              lock; /* protect dev_list */
पूर्ण;

अटल काष्ठा sपंचांग32_cryp_list cryp_list = अणु
	.dev_list = LIST_HEAD_INIT(cryp_list.dev_list),
	.lock     = __SPIN_LOCK_UNLOCKED(cryp_list.lock),
पूर्ण;

अटल अंतरभूत bool is_aes(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_AES;
पूर्ण

अटल अंतरभूत bool is_des(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_DES;
पूर्ण

अटल अंतरभूत bool is_tdes(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_TDES;
पूर्ण

अटल अंतरभूत bool is_ecb(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_ECB;
पूर्ण

अटल अंतरभूत bool is_cbc(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_CBC;
पूर्ण

अटल अंतरभूत bool is_ctr(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_CTR;
पूर्ण

अटल अंतरभूत bool is_gcm(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_GCM;
पूर्ण

अटल अंतरभूत bool is_ccm(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_CCM;
पूर्ण

अटल अंतरभूत bool is_encrypt(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस cryp->flags & FLG_ENCRYPT;
पूर्ण

अटल अंतरभूत bool is_decrypt(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस !is_encrypt(cryp);
पूर्ण

अटल अंतरभूत u32 sपंचांग32_cryp_पढ़ो(काष्ठा sपंचांग32_cryp *cryp, u32 ofst)
अणु
	वापस पढ़ोl_relaxed(cryp->regs + ofst);
पूर्ण

अटल अंतरभूत व्योम sपंचांग32_cryp_ग_लिखो(काष्ठा sपंचांग32_cryp *cryp, u32 ofst, u32 val)
अणु
	ग_लिखोl_relaxed(val, cryp->regs + ofst);
पूर्ण

अटल अंतरभूत पूर्णांक sपंचांग32_cryp_रुको_busy(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 status;

	वापस पढ़ोl_relaxed_poll_समयout(cryp->regs + CRYP_SR, status,
			!(status & SR_BUSY), 10, 100000);
पूर्ण

अटल अंतरभूत पूर्णांक sपंचांग32_cryp_रुको_enable(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 status;

	वापस पढ़ोl_relaxed_poll_समयout(cryp->regs + CRYP_CR, status,
			!(status & CR_CRYPEN), 10, 100000);
पूर्ण

अटल अंतरभूत पूर्णांक sपंचांग32_cryp_रुको_output(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 status;

	वापस पढ़ोl_relaxed_poll_समयout(cryp->regs + CRYP_SR, status,
			status & SR_OFNE, 10, 100000);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_पढ़ो_auth_tag(काष्ठा sपंचांग32_cryp *cryp);

अटल काष्ठा sपंचांग32_cryp *sपंचांग32_cryp_find_dev(काष्ठा sपंचांग32_cryp_ctx *ctx)
अणु
	काष्ठा sपंचांग32_cryp *पंचांगp, *cryp = शून्य;

	spin_lock_bh(&cryp_list.lock);
	अगर (!ctx->cryp) अणु
		list_क्रम_each_entry(पंचांगp, &cryp_list.dev_list, list) अणु
			cryp = पंचांगp;
			अवरोध;
		पूर्ण
		ctx->cryp = cryp;
	पूर्ण अन्यथा अणु
		cryp = ctx->cryp;
	पूर्ण

	spin_unlock_bh(&cryp_list.lock);

	वापस cryp;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_check_aligned(काष्ठा scatterlist *sg, माप_प्रकार total,
				    माप_प्रकार align)
अणु
	पूर्णांक len = 0;

	अगर (!total)
		वापस 0;

	अगर (!IS_ALIGNED(total, align))
		वापस -EINVAL;

	जबतक (sg) अणु
		अगर (!IS_ALIGNED(sg->offset, माप(u32)))
			वापस -EINVAL;

		अगर (!IS_ALIGNED(sg->length, align))
			वापस -EINVAL;

		len += sg->length;
		sg = sg_next(sg);
	पूर्ण

	अगर (len != total)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_check_io_aligned(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक ret;

	ret = sपंचांग32_cryp_check_aligned(cryp->in_sg, cryp->total_in,
				       cryp->hw_blocksize);
	अगर (ret)
		वापस ret;

	ret = sपंचांग32_cryp_check_aligned(cryp->out_sg, cryp->total_out,
				       cryp->hw_blocksize);

	वापस ret;
पूर्ण

अटल व्योम sg_copy_buf(व्योम *buf, काष्ठा scatterlist *sg,
			अचिन्हित पूर्णांक start, अचिन्हित पूर्णांक nbytes, पूर्णांक out)
अणु
	काष्ठा scatter_walk walk;

	अगर (!nbytes)
		वापस;

	scatterwalk_start(&walk, sg);
	scatterwalk_advance(&walk, start);
	scatterwalk_copychunks(buf, &walk, nbytes, out);
	scatterwalk_करोne(&walk, out, 0);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_copy_sgs(काष्ठा sपंचांग32_cryp *cryp)
अणु
	व्योम *buf_in, *buf_out;
	पूर्णांक pages, total_in, total_out;

	अगर (!sपंचांग32_cryp_check_io_aligned(cryp)) अणु
		cryp->sgs_copied = 0;
		वापस 0;
	पूर्ण

	total_in = ALIGN(cryp->total_in, cryp->hw_blocksize);
	pages = total_in ? get_order(total_in) : 1;
	buf_in = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, pages);

	total_out = ALIGN(cryp->total_out, cryp->hw_blocksize);
	pages = total_out ? get_order(total_out) : 1;
	buf_out = (व्योम *)__get_मुक्त_pages(GFP_ATOMIC, pages);

	अगर (!buf_in || !buf_out) अणु
		dev_err(cryp->dev, "Can't allocate pages when unaligned\n");
		cryp->sgs_copied = 0;
		वापस -EFAULT;
	पूर्ण

	sg_copy_buf(buf_in, cryp->in_sg, 0, cryp->total_in, 0);

	sg_init_one(&cryp->in_sgl, buf_in, total_in);
	cryp->in_sg = &cryp->in_sgl;
	cryp->in_sg_len = 1;

	sg_init_one(&cryp->out_sgl, buf_out, total_out);
	cryp->out_sg_save = cryp->out_sg;
	cryp->out_sg = &cryp->out_sgl;
	cryp->out_sg_len = 1;

	cryp->sgs_copied = 1;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_cryp_hw_ग_लिखो_iv(काष्ठा sपंचांग32_cryp *cryp, __be32 *iv)
अणु
	अगर (!iv)
		वापस;

	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV0LR, be32_to_cpu(*iv++));
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV0RR, be32_to_cpu(*iv++));

	अगर (is_aes(cryp)) अणु
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV1LR, be32_to_cpu(*iv++));
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV1RR, be32_to_cpu(*iv++));
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_cryp_get_iv(काष्ठा sपंचांग32_cryp *cryp)
अणु
	काष्ठा skcipher_request *req = cryp->req;
	__be32 *पंचांगp = (व्योम *)req->iv;

	अगर (!पंचांगp)
		वापस;

	*पंचांगp++ = cpu_to_be32(sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV0LR));
	*पंचांगp++ = cpu_to_be32(sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV0RR));

	अगर (is_aes(cryp)) अणु
		*पंचांगp++ = cpu_to_be32(sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV1LR));
		*पंचांगp++ = cpu_to_be32(sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV1RR));
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_cryp_hw_ग_लिखो_key(काष्ठा sपंचांग32_cryp *c)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक r_id;

	अगर (is_des(c)) अणु
		sपंचांग32_cryp_ग_लिखो(c, CRYP_K1LR, be32_to_cpu(c->ctx->key[0]));
		sपंचांग32_cryp_ग_लिखो(c, CRYP_K1RR, be32_to_cpu(c->ctx->key[1]));
	पूर्ण अन्यथा अणु
		r_id = CRYP_K3RR;
		क्रम (i = c->ctx->keylen / माप(u32); i > 0; i--, r_id -= 4)
			sपंचांग32_cryp_ग_लिखो(c, r_id,
					 be32_to_cpu(c->ctx->key[i - 1]));
	पूर्ण
पूर्ण

अटल u32 sपंचांग32_cryp_get_hw_mode(काष्ठा sपंचांग32_cryp *cryp)
अणु
	अगर (is_aes(cryp) && is_ecb(cryp))
		वापस CR_AES_ECB;

	अगर (is_aes(cryp) && is_cbc(cryp))
		वापस CR_AES_CBC;

	अगर (is_aes(cryp) && is_ctr(cryp))
		वापस CR_AES_CTR;

	अगर (is_aes(cryp) && is_gcm(cryp))
		वापस CR_AES_GCM;

	अगर (is_aes(cryp) && is_ccm(cryp))
		वापस CR_AES_CCM;

	अगर (is_des(cryp) && is_ecb(cryp))
		वापस CR_DES_ECB;

	अगर (is_des(cryp) && is_cbc(cryp))
		वापस CR_DES_CBC;

	अगर (is_tdes(cryp) && is_ecb(cryp))
		वापस CR_TDES_ECB;

	अगर (is_tdes(cryp) && is_cbc(cryp))
		वापस CR_TDES_CBC;

	dev_err(cryp->dev, "Unknown mode\n");
	वापस CR_AES_UNKNOWN;
पूर्ण

अटल अचिन्हित पूर्णांक sपंचांग32_cryp_get_input_text_len(काष्ठा sपंचांग32_cryp *cryp)
अणु
	वापस is_encrypt(cryp) ? cryp->areq->cryptlen :
				  cryp->areq->cryptlen - cryp->authsize;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_gcm_init(काष्ठा sपंचांग32_cryp *cryp, u32 cfg)
अणु
	पूर्णांक ret;
	__be32 iv[4];

	/* Phase 1 : init */
	स_नकल(iv, cryp->areq->iv, 12);
	iv[3] = cpu_to_be32(GCM_CTR_INIT);
	cryp->gcm_ctr = GCM_CTR_INIT;
	sपंचांग32_cryp_hw_ग_लिखो_iv(cryp, iv);

	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg | CR_PH_INIT | CR_CRYPEN);

	/* Wait क्रम end of processing */
	ret = sपंचांग32_cryp_रुको_enable(cryp);
	अगर (ret)
		dev_err(cryp->dev, "Timeout (gcm init)\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_ccm_init(काष्ठा sपंचांग32_cryp *cryp, u32 cfg)
अणु
	पूर्णांक ret;
	u8 iv[AES_BLOCK_SIZE], b0[AES_BLOCK_SIZE];
	__be32 *bd;
	u32 *d;
	अचिन्हित पूर्णांक i, textlen;

	/* Phase 1 : init. Firstly set the CTR value to 1 (not 0) */
	स_नकल(iv, cryp->areq->iv, AES_BLOCK_SIZE);
	स_रखो(iv + AES_BLOCK_SIZE - 1 - iv[0], 0, iv[0] + 1);
	iv[AES_BLOCK_SIZE - 1] = 1;
	sपंचांग32_cryp_hw_ग_लिखो_iv(cryp, (__be32 *)iv);

	/* Build B0 */
	स_नकल(b0, iv, AES_BLOCK_SIZE);

	b0[0] |= (8 * ((cryp->authsize - 2) / 2));

	अगर (cryp->areq->assoclen)
		b0[0] |= 0x40;

	textlen = sपंचांग32_cryp_get_input_text_len(cryp);

	b0[AES_BLOCK_SIZE - 2] = textlen >> 8;
	b0[AES_BLOCK_SIZE - 1] = textlen & 0xFF;

	/* Enable HW */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg | CR_PH_INIT | CR_CRYPEN);

	/* Write B0 */
	d = (u32 *)b0;
	bd = (__be32 *)b0;

	क्रम (i = 0; i < AES_BLOCK_32; i++) अणु
		u32 xd = d[i];

		अगर (!cryp->caps->padding_wa)
			xd = be32_to_cpu(bd[i]);
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, xd);
	पूर्ण

	/* Wait क्रम end of processing */
	ret = sपंचांग32_cryp_रुको_enable(cryp);
	अगर (ret)
		dev_err(cryp->dev, "Timeout (ccm init)\n");

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_hw_init(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक ret;
	u32 cfg, hw_mode;

	pm_runसमय_resume_and_get(cryp->dev);

	/* Disable पूर्णांकerrupt */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);

	/* Set key */
	sपंचांग32_cryp_hw_ग_लिखो_key(cryp);

	/* Set configuration */
	cfg = CR_DATA8 | CR_FFLUSH;

	चयन (cryp->ctx->keylen) अणु
	हाल AES_KEYSIZE_128:
		cfg |= CR_KEY128;
		अवरोध;

	हाल AES_KEYSIZE_192:
		cfg |= CR_KEY192;
		अवरोध;

	शेष:
	हाल AES_KEYSIZE_256:
		cfg |= CR_KEY256;
		अवरोध;
	पूर्ण

	hw_mode = sपंचांग32_cryp_get_hw_mode(cryp);
	अगर (hw_mode == CR_AES_UNKNOWN)
		वापस -EINVAL;

	/* AES ECB/CBC decrypt: run key preparation first */
	अगर (is_decrypt(cryp) &&
	    ((hw_mode == CR_AES_ECB) || (hw_mode == CR_AES_CBC))) अणु
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg | CR_AES_KP | CR_CRYPEN);

		/* Wait क्रम end of processing */
		ret = sपंचांग32_cryp_रुको_busy(cryp);
		अगर (ret) अणु
			dev_err(cryp->dev, "Timeout (key preparation)\n");
			वापस ret;
		पूर्ण
	पूर्ण

	cfg |= hw_mode;

	अगर (is_decrypt(cryp))
		cfg |= CR_DEC_NOT_ENC;

	/* Apply config and flush (valid when CRYPEN = 0) */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	चयन (hw_mode) अणु
	हाल CR_AES_GCM:
	हाल CR_AES_CCM:
		/* Phase 1 : init */
		अगर (hw_mode == CR_AES_CCM)
			ret = sपंचांग32_cryp_ccm_init(cryp, cfg);
		अन्यथा
			ret = sपंचांग32_cryp_gcm_init(cryp, cfg);

		अगर (ret)
			वापस ret;

		/* Phase 2 : header (authenticated data) */
		अगर (cryp->areq->assoclen) अणु
			cfg |= CR_PH_HEADER;
		पूर्ण अन्यथा अगर (sपंचांग32_cryp_get_input_text_len(cryp)) अणु
			cfg |= CR_PH_PAYLOAD;
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);
		पूर्ण अन्यथा अणु
			cfg |= CR_PH_INIT;
		पूर्ण

		अवरोध;

	हाल CR_DES_CBC:
	हाल CR_TDES_CBC:
	हाल CR_AES_CBC:
	हाल CR_AES_CTR:
		sपंचांग32_cryp_hw_ग_लिखो_iv(cryp, (__be32 *)cryp->req->iv);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	/* Enable now */
	cfg |= CR_CRYPEN;

	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	cryp->flags &= ~FLG_CCM_PADDED_WA;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_cryp_finish_req(काष्ठा sपंचांग32_cryp *cryp, पूर्णांक err)
अणु
	अगर (!err && (is_gcm(cryp) || is_ccm(cryp)))
		/* Phase 4 : output tag */
		err = sपंचांग32_cryp_पढ़ो_auth_tag(cryp);

	अगर (!err && (!(is_gcm(cryp) || is_ccm(cryp))))
		sपंचांग32_cryp_get_iv(cryp);

	अगर (cryp->sgs_copied) अणु
		व्योम *buf_in, *buf_out;
		पूर्णांक pages, len;

		buf_in = sg_virt(&cryp->in_sgl);
		buf_out = sg_virt(&cryp->out_sgl);

		sg_copy_buf(buf_out, cryp->out_sg_save, 0,
			    cryp->total_out_save, 1);

		len = ALIGN(cryp->total_in_save, cryp->hw_blocksize);
		pages = len ? get_order(len) : 1;
		मुक्त_pages((अचिन्हित दीर्घ)buf_in, pages);

		len = ALIGN(cryp->total_out_save, cryp->hw_blocksize);
		pages = len ? get_order(len) : 1;
		मुक्त_pages((अचिन्हित दीर्घ)buf_out, pages);
	पूर्ण

	pm_runसमय_mark_last_busy(cryp->dev);
	pm_runसमय_put_स्वतःsuspend(cryp->dev);

	अगर (is_gcm(cryp) || is_ccm(cryp))
		crypto_finalize_aead_request(cryp->engine, cryp->areq, err);
	अन्यथा
		crypto_finalize_skcipher_request(cryp->engine, cryp->req,
						   err);

	स_रखो(cryp->ctx->key, 0, cryp->ctx->keylen);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_cpu_start(काष्ठा sपंचांग32_cryp *cryp)
अणु
	/* Enable पूर्णांकerrupt and let the IRQ handler करो everything */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, IMSCR_IN | IMSCR_OUT);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_cipher_one_req(काष्ठा crypto_engine *engine, व्योम *areq);
अटल पूर्णांक sपंचांग32_cryp_prepare_cipher_req(काष्ठा crypto_engine *engine,
					 व्योम *areq);

अटल पूर्णांक sपंचांग32_cryp_init_tfm(काष्ठा crypto_skcipher *tfm)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_skcipher_ctx(tfm);

	crypto_skcipher_set_reqsize(tfm, माप(काष्ठा sपंचांग32_cryp_reqctx));

	ctx->enginectx.op.करो_one_request = sपंचांग32_cryp_cipher_one_req;
	ctx->enginectx.op.prepare_request = sपंचांग32_cryp_prepare_cipher_req;
	ctx->enginectx.op.unprepare_request = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aead_one_req(काष्ठा crypto_engine *engine, व्योम *areq);
अटल पूर्णांक sपंचांग32_cryp_prepare_aead_req(काष्ठा crypto_engine *engine,
				       व्योम *areq);

अटल पूर्णांक sपंचांग32_cryp_aes_aead_init(काष्ठा crypto_aead *tfm)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_aead_ctx(tfm);

	tfm->reqsize = माप(काष्ठा sपंचांग32_cryp_reqctx);

	ctx->enginectx.op.करो_one_request = sपंचांग32_cryp_aead_one_req;
	ctx->enginectx.op.prepare_request = sपंचांग32_cryp_prepare_aead_req;
	ctx->enginectx.op.unprepare_request = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_crypt(काष्ठा skcipher_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा sपंचांग32_cryp_reqctx *rctx = skcipher_request_ctx(req);
	काष्ठा sपंचांग32_cryp *cryp = sपंचांग32_cryp_find_dev(ctx);

	अगर (!cryp)
		वापस -ENODEV;

	rctx->mode = mode;

	वापस crypto_transfer_skcipher_request_to_engine(cryp->engine, req);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aead_crypt(काष्ठा aead_request *req, अचिन्हित दीर्घ mode)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा sपंचांग32_cryp_reqctx *rctx = aead_request_ctx(req);
	काष्ठा sपंचांग32_cryp *cryp = sपंचांग32_cryp_find_dev(ctx);

	अगर (!cryp)
		वापस -ENODEV;

	rctx->mode = mode;

	वापस crypto_transfer_aead_request_to_engine(cryp->engine, req);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
			     अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_skcipher_ctx(tfm);

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	अगर (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;
	अन्यथा
		वापस sपंचांग32_cryp_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_des_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				 अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des_key(tfm, key) ?:
	       sपंचांग32_cryp_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_tdes_setkey(काष्ठा crypto_skcipher *tfm, स्थिर u8 *key,
				  अचिन्हित पूर्णांक keylen)
अणु
	वापस verअगरy_skcipher_des3_key(tfm, key) ?:
	       sपंचांग32_cryp_setkey(tfm, key, keylen);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_aead_setkey(काष्ठा crypto_aead *tfm, स्थिर u8 *key,
				      अचिन्हित पूर्णांक keylen)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_aead_ctx(tfm);

	अगर (keylen != AES_KEYSIZE_128 && keylen != AES_KEYSIZE_192 &&
	    keylen != AES_KEYSIZE_256)
		वापस -EINVAL;

	स_नकल(ctx->key, key, keylen);
	ctx->keylen = keylen;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_gcm_setauthsize(काष्ठा crypto_aead *tfm,
					  अचिन्हित पूर्णांक authsize)
अणु
	वापस authsize == AES_BLOCK_SIZE ? 0 : -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ccm_setauthsize(काष्ठा crypto_aead *tfm,
					  अचिन्हित पूर्णांक authsize)
अणु
	चयन (authsize) अणु
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 10:
	हाल 12:
	हाल 14:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_ECB | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_ECB);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_CBC | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_CBC);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ctr_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_CTR | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ctr_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_AES | FLG_CTR);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_gcm_encrypt(काष्ठा aead_request *req)
अणु
	वापस sपंचांग32_cryp_aead_crypt(req, FLG_AES | FLG_GCM | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_gcm_decrypt(काष्ठा aead_request *req)
अणु
	वापस sपंचांग32_cryp_aead_crypt(req, FLG_AES | FLG_GCM);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ccm_encrypt(काष्ठा aead_request *req)
अणु
	वापस sपंचांग32_cryp_aead_crypt(req, FLG_AES | FLG_CCM | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aes_ccm_decrypt(काष्ठा aead_request *req)
अणु
	वापस sपंचांग32_cryp_aead_crypt(req, FLG_AES | FLG_CCM);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_des_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_DES | FLG_ECB | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_des_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_DES | FLG_ECB);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_des_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_DES | FLG_CBC | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_des_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_DES | FLG_CBC);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_tdes_ecb_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_TDES | FLG_ECB | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_tdes_ecb_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_TDES | FLG_ECB);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_tdes_cbc_encrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_TDES | FLG_CBC | FLG_ENCRYPT);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_tdes_cbc_decrypt(काष्ठा skcipher_request *req)
अणु
	वापस sपंचांग32_cryp_crypt(req, FLG_TDES | FLG_CBC);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_prepare_req(काष्ठा skcipher_request *req,
				  काष्ठा aead_request *areq)
अणु
	काष्ठा sपंचांग32_cryp_ctx *ctx;
	काष्ठा sपंचांग32_cryp *cryp;
	काष्ठा sपंचांग32_cryp_reqctx *rctx;
	पूर्णांक ret;

	अगर (!req && !areq)
		वापस -EINVAL;

	ctx = req ? crypto_skcipher_ctx(crypto_skcipher_reqtfm(req)) :
		    crypto_aead_ctx(crypto_aead_reqtfm(areq));

	cryp = ctx->cryp;

	अगर (!cryp)
		वापस -ENODEV;

	rctx = req ? skcipher_request_ctx(req) : aead_request_ctx(areq);
	rctx->mode &= FLG_MODE_MASK;

	ctx->cryp = cryp;

	cryp->flags = (cryp->flags & ~FLG_MODE_MASK) | rctx->mode;
	cryp->hw_blocksize = is_aes(cryp) ? AES_BLOCK_SIZE : DES_BLOCK_SIZE;
	cryp->ctx = ctx;

	अगर (req) अणु
		cryp->req = req;
		cryp->areq = शून्य;
		cryp->total_in = req->cryptlen;
		cryp->total_out = cryp->total_in;
	पूर्ण अन्यथा अणु
		/*
		 * Length of input and output data:
		 * Encryption हाल:
		 *  INPUT  =   AssocData  ||   PlainText
		 *          <- assoclen ->  <- cryptlen ->
		 *          <------- total_in ----------->
		 *
		 *  OUTPUT =   AssocData  ||  CipherText  ||   AuthTag
		 *          <- assoclen ->  <- cryptlen ->  <- authsize ->
		 *          <---------------- total_out ----------------->
		 *
		 * Decryption हाल:
		 *  INPUT  =   AssocData  ||  CipherText  ||  AuthTag
		 *          <- assoclen ->  <--------- cryptlen --------->
		 *                                          <- authsize ->
		 *          <---------------- total_in ------------------>
		 *
		 *  OUTPUT =   AssocData  ||   PlainText
		 *          <- assoclen ->  <- crypten - authsize ->
		 *          <---------- total_out ----------------->
		 */
		cryp->areq = areq;
		cryp->req = शून्य;
		cryp->authsize = crypto_aead_authsize(crypto_aead_reqtfm(areq));
		cryp->total_in = areq->assoclen + areq->cryptlen;
		अगर (is_encrypt(cryp))
			/* Append auth tag to output */
			cryp->total_out = cryp->total_in + cryp->authsize;
		अन्यथा
			/* No auth tag in output */
			cryp->total_out = cryp->total_in - cryp->authsize;
	पूर्ण

	cryp->total_in_save = cryp->total_in;
	cryp->total_out_save = cryp->total_out;

	cryp->in_sg = req ? req->src : areq->src;
	cryp->out_sg = req ? req->dst : areq->dst;
	cryp->out_sg_save = cryp->out_sg;

	cryp->in_sg_len = sg_nents_क्रम_len(cryp->in_sg, cryp->total_in);
	अगर (cryp->in_sg_len < 0) अणु
		dev_err(cryp->dev, "Cannot get in_sg_len\n");
		ret = cryp->in_sg_len;
		वापस ret;
	पूर्ण

	cryp->out_sg_len = sg_nents_क्रम_len(cryp->out_sg, cryp->total_out);
	अगर (cryp->out_sg_len < 0) अणु
		dev_err(cryp->dev, "Cannot get out_sg_len\n");
		ret = cryp->out_sg_len;
		वापस ret;
	पूर्ण

	ret = sपंचांग32_cryp_copy_sgs(cryp);
	अगर (ret)
		वापस ret;

	scatterwalk_start(&cryp->in_walk, cryp->in_sg);
	scatterwalk_start(&cryp->out_walk, cryp->out_sg);

	अगर (is_gcm(cryp) || is_ccm(cryp)) अणु
		/* In output, jump after assoc data */
		scatterwalk_advance(&cryp->out_walk, cryp->areq->assoclen);
		cryp->total_out -= cryp->areq->assoclen;
	पूर्ण

	ret = sपंचांग32_cryp_hw_init(cryp);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_prepare_cipher_req(काष्ठा crypto_engine *engine,
					 व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq,
						      काष्ठा skcipher_request,
						      base);

	वापस sपंचांग32_cryp_prepare_req(req, शून्य);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_cipher_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा skcipher_request *req = container_of(areq,
						      काष्ठा skcipher_request,
						      base);
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_skcipher_ctx(
			crypto_skcipher_reqtfm(req));
	काष्ठा sपंचांग32_cryp *cryp = ctx->cryp;

	अगर (!cryp)
		वापस -ENODEV;

	वापस sपंचांग32_cryp_cpu_start(cryp);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_prepare_aead_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);

	वापस sपंचांग32_cryp_prepare_req(शून्य, req);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_aead_one_req(काष्ठा crypto_engine *engine, व्योम *areq)
अणु
	काष्ठा aead_request *req = container_of(areq, काष्ठा aead_request,
						base);
	काष्ठा sपंचांग32_cryp_ctx *ctx = crypto_aead_ctx(crypto_aead_reqtfm(req));
	काष्ठा sपंचांग32_cryp *cryp = ctx->cryp;

	अगर (!cryp)
		वापस -ENODEV;

	अगर (unlikely(!cryp->areq->assoclen &&
		     !sपंचांग32_cryp_get_input_text_len(cryp))) अणु
		/* No input data to process: get tag and finish */
		sपंचांग32_cryp_finish_req(cryp, 0);
		वापस 0;
	पूर्ण

	वापस sपंचांग32_cryp_cpu_start(cryp);
पूर्ण

अटल u32 *sपंचांग32_cryp_next_out(काष्ठा sपंचांग32_cryp *cryp, u32 *dst,
				अचिन्हित पूर्णांक n)
अणु
	scatterwalk_advance(&cryp->out_walk, n);

	अगर (unlikely(cryp->out_sg->length == _walked_out)) अणु
		cryp->out_sg = sg_next(cryp->out_sg);
		अगर (cryp->out_sg) अणु
			scatterwalk_start(&cryp->out_walk, cryp->out_sg);
			वापस (sg_virt(cryp->out_sg) + _walked_out);
		पूर्ण
	पूर्ण

	वापस (u32 *)((u8 *)dst + n);
पूर्ण

अटल u32 *sपंचांग32_cryp_next_in(काष्ठा sपंचांग32_cryp *cryp, u32 *src,
			       अचिन्हित पूर्णांक n)
अणु
	scatterwalk_advance(&cryp->in_walk, n);

	अगर (unlikely(cryp->in_sg->length == _walked_in)) अणु
		cryp->in_sg = sg_next(cryp->in_sg);
		अगर (cryp->in_sg) अणु
			scatterwalk_start(&cryp->in_walk, cryp->in_sg);
			वापस (sg_virt(cryp->in_sg) + _walked_in);
		पूर्ण
	पूर्ण

	वापस (u32 *)((u8 *)src + n);
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_पढ़ो_auth_tag(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 cfg, size_bit, *dst, d32;
	u8 *d8;
	अचिन्हित पूर्णांक i, j;
	पूर्णांक ret = 0;

	/* Update Config */
	cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);

	cfg &= ~CR_PH_MASK;
	cfg |= CR_PH_FINAL;
	cfg &= ~CR_DEC_NOT_ENC;
	cfg |= CR_CRYPEN;

	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	अगर (is_gcm(cryp)) अणु
		/* GCM: ग_लिखो aad and payload size (in bits) */
		size_bit = cryp->areq->assoclen * 8;
		अगर (cryp->caps->swap_final)
			size_bit = (__क्रमce u32)cpu_to_be32(size_bit);

		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, size_bit);

		size_bit = is_encrypt(cryp) ? cryp->areq->cryptlen :
				cryp->areq->cryptlen - AES_BLOCK_SIZE;
		size_bit *= 8;
		अगर (cryp->caps->swap_final)
			size_bit = (__क्रमce u32)cpu_to_be32(size_bit);

		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, size_bit);
	पूर्ण अन्यथा अणु
		/* CCM: ग_लिखो CTR0 */
		u8 iv[AES_BLOCK_SIZE];
		u32 *iv32 = (u32 *)iv;
		__be32 *biv;

		biv = (व्योम *)iv;

		स_नकल(iv, cryp->areq->iv, AES_BLOCK_SIZE);
		स_रखो(iv + AES_BLOCK_SIZE - 1 - iv[0], 0, iv[0] + 1);

		क्रम (i = 0; i < AES_BLOCK_32; i++) अणु
			u32 xiv = iv32[i];

			अगर (!cryp->caps->padding_wa)
				xiv = be32_to_cpu(biv[i]);
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, xiv);
		पूर्ण
	पूर्ण

	/* Wait क्रम output data */
	ret = sपंचांग32_cryp_रुको_output(cryp);
	अगर (ret) अणु
		dev_err(cryp->dev, "Timeout (read tag)\n");
		वापस ret;
	पूर्ण

	अगर (is_encrypt(cryp)) अणु
		/* Get and ग_लिखो tag */
		dst = sg_virt(cryp->out_sg) + _walked_out;

		क्रम (i = 0; i < AES_BLOCK_32; i++) अणु
			अगर (cryp->total_out >= माप(u32)) अणु
				/* Read a full u32 */
				*dst = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);

				dst = sपंचांग32_cryp_next_out(cryp, dst,
							  माप(u32));
				cryp->total_out -= माप(u32);
			पूर्ण अन्यथा अगर (!cryp->total_out) अणु
				/* Empty fअगरo out (data from input padding) */
				sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);
			पूर्ण अन्यथा अणु
				/* Read less than an u32 */
				d32 = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);
				d8 = (u8 *)&d32;

				क्रम (j = 0; j < cryp->total_out; j++) अणु
					*((u8 *)dst) = *(d8++);
					dst = sपंचांग32_cryp_next_out(cryp, dst, 1);
				पूर्ण
				cryp->total_out = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Get and check tag */
		u32 in_tag[AES_BLOCK_32], out_tag[AES_BLOCK_32];

		scatterwalk_map_and_copy(in_tag, cryp->in_sg,
					 cryp->total_in_save - cryp->authsize,
					 cryp->authsize, 0);

		क्रम (i = 0; i < AES_BLOCK_32; i++)
			out_tag[i] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);

		अगर (crypto_memneq(in_tag, out_tag, cryp->authsize))
			ret = -EBADMSG;
	पूर्ण

	/* Disable cryp */
	cfg &= ~CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_cryp_check_ctr_counter(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 cr;

	अगर (unlikely(cryp->last_ctr[3] == 0xFFFFFFFF)) अणु
		cryp->last_ctr[3] = 0;
		cryp->last_ctr[2]++;
		अगर (!cryp->last_ctr[2]) अणु
			cryp->last_ctr[1]++;
			अगर (!cryp->last_ctr[1])
				cryp->last_ctr[0]++;
		पूर्ण

		cr = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cr & ~CR_CRYPEN);

		sपंचांग32_cryp_hw_ग_लिखो_iv(cryp, (__be32 *)cryp->last_ctr);

		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cr);
	पूर्ण

	cryp->last_ctr[0] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV0LR);
	cryp->last_ctr[1] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV0RR);
	cryp->last_ctr[2] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV1LR);
	cryp->last_ctr[3] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_IV1RR);
पूर्ण

अटल bool sपंचांग32_cryp_irq_पढ़ो_data(काष्ठा sपंचांग32_cryp *cryp)
अणु
	अचिन्हित पूर्णांक i, j;
	u32 d32, *dst;
	u8 *d8;
	माप_प्रकार tag_size;

	/* Do no पढ़ो tag now (अगर any) */
	अगर (is_encrypt(cryp) && (is_gcm(cryp) || is_ccm(cryp)))
		tag_size = cryp->authsize;
	अन्यथा
		tag_size = 0;

	dst = sg_virt(cryp->out_sg) + _walked_out;

	क्रम (i = 0; i < cryp->hw_blocksize / माप(u32); i++) अणु
		अगर (likely(cryp->total_out - tag_size >= माप(u32))) अणु
			/* Read a full u32 */
			*dst = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);

			dst = sपंचांग32_cryp_next_out(cryp, dst, माप(u32));
			cryp->total_out -= माप(u32);
		पूर्ण अन्यथा अगर (cryp->total_out == tag_size) अणु
			/* Empty fअगरo out (data from input padding) */
			d32 = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);
		पूर्ण अन्यथा अणु
			/* Read less than an u32 */
			d32 = sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);
			d8 = (u8 *)&d32;

			क्रम (j = 0; j < cryp->total_out - tag_size; j++) अणु
				*((u8 *)dst) = *(d8++);
				dst = sपंचांग32_cryp_next_out(cryp, dst, 1);
			पूर्ण
			cryp->total_out = tag_size;
		पूर्ण
	पूर्ण

	वापस !(cryp->total_out - tag_size) || !cryp->total_in;
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_block(काष्ठा sपंचांग32_cryp *cryp)
अणु
	अचिन्हित पूर्णांक i, j;
	u32 *src;
	u8 d8[4];
	माप_प्रकार tag_size;

	/* Do no ग_लिखो tag (अगर any) */
	अगर (is_decrypt(cryp) && (is_gcm(cryp) || is_ccm(cryp)))
		tag_size = cryp->authsize;
	अन्यथा
		tag_size = 0;

	src = sg_virt(cryp->in_sg) + _walked_in;

	क्रम (i = 0; i < cryp->hw_blocksize / माप(u32); i++) अणु
		अगर (likely(cryp->total_in - tag_size >= माप(u32))) अणु
			/* Write a full u32 */
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *src);

			src = sपंचांग32_cryp_next_in(cryp, src, माप(u32));
			cryp->total_in -= माप(u32);
		पूर्ण अन्यथा अगर (cryp->total_in == tag_size) अणु
			/* Write padding data */
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);
		पूर्ण अन्यथा अणु
			/* Write less than an u32 */
			स_रखो(d8, 0, माप(u32));
			क्रम (j = 0; j < cryp->total_in - tag_size; j++) अणु
				d8[j] = *((u8 *)src);
				src = sपंचांग32_cryp_next_in(cryp, src, 1);
			पूर्ण

			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *(u32 *)d8);
			cryp->total_in = tag_size;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_gcm_padded_data(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक err;
	u32 cfg, पंचांगp[AES_BLOCK_32];
	माप_प्रकार total_in_ori = cryp->total_in;
	काष्ठा scatterlist *out_sg_ori = cryp->out_sg;
	अचिन्हित पूर्णांक i;

	/* 'Special workaround' procedure described in the datasheet */

	/* a) disable ip */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);
	cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
	cfg &= ~CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* b) Update IV1R */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV1RR, cryp->gcm_ctr - 2);

	/* c) change mode to CTR */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_CTR;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* a) enable IP */
	cfg |= CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* b) pad and ग_लिखो the last block */
	sपंचांग32_cryp_irq_ग_लिखो_block(cryp);
	cryp->total_in = total_in_ori;
	err = sपंचांग32_cryp_रुको_output(cryp);
	अगर (err) अणु
		dev_err(cryp->dev, "Timeout (write gcm header)\n");
		वापस sपंचांग32_cryp_finish_req(cryp, err);
	पूर्ण

	/* c) get and store encrypted data */
	sपंचांग32_cryp_irq_पढ़ो_data(cryp);
	scatterwalk_map_and_copy(पंचांगp, out_sg_ori,
				 cryp->total_in_save - total_in_ori,
				 total_in_ori, 0);

	/* d) change mode back to AES GCM */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_GCM;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* e) change phase to Final */
	cfg &= ~CR_PH_MASK;
	cfg |= CR_PH_FINAL;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* f) ग_लिखो padded data */
	क्रम (i = 0; i < AES_BLOCK_32; i++) अणु
		अगर (cryp->total_in)
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, पंचांगp[i]);
		अन्यथा
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);

		cryp->total_in -= min_t(माप_प्रकार, माप(u32), cryp->total_in);
	पूर्ण

	/* g) Empty fअगरo out */
	err = sपंचांग32_cryp_रुको_output(cryp);
	अगर (err) अणु
		dev_err(cryp->dev, "Timeout (write gcm header)\n");
		वापस sपंचांग32_cryp_finish_req(cryp, err);
	पूर्ण

	क्रम (i = 0; i < AES_BLOCK_32; i++)
		sपंचांग32_cryp_पढ़ो(cryp, CRYP_DOUT);

	/* h) run the he normal Final phase */
	sपंचांग32_cryp_finish_req(cryp, 0);
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_set_npblb(काष्ठा sपंचांग32_cryp *cryp)
अणु
	u32 cfg, payload_bytes;

	/* disable ip, set NPBLB and reneable ip */
	cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
	cfg &= ~CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	payload_bytes = is_decrypt(cryp) ? cryp->total_in - cryp->authsize :
					   cryp->total_in;
	cfg |= (cryp->hw_blocksize - payload_bytes) << CR_NBPBL_SHIFT;
	cfg |= CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_ccm_padded_data(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक err = 0;
	u32 cfg, iv1पंचांगp;
	u32 csपंचांगp1[AES_BLOCK_32], csपंचांगp2[AES_BLOCK_32], पंचांगp[AES_BLOCK_32];
	माप_प्रकार last_total_out, total_in_ori = cryp->total_in;
	काष्ठा scatterlist *out_sg_ori = cryp->out_sg;
	अचिन्हित पूर्णांक i;

	/* 'Special workaround' procedure described in the datasheet */
	cryp->flags |= FLG_CCM_PADDED_WA;

	/* a) disable ip */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);

	cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
	cfg &= ~CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* b) get IV1 from CRYP_CSGCMCCM7 */
	iv1पंचांगp = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CSGCMCCM0R + 7 * 4);

	/* c) Load CRYP_CSGCMCCMxR */
	क्रम (i = 0; i < ARRAY_SIZE(csपंचांगp1); i++)
		csपंचांगp1[i] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CSGCMCCM0R + i * 4);

	/* d) Write IV1R */
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IV1RR, iv1पंचांगp);

	/* e) change mode to CTR */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_CTR;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* a) enable IP */
	cfg |= CR_CRYPEN;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* b) pad and ग_लिखो the last block */
	sपंचांग32_cryp_irq_ग_लिखो_block(cryp);
	cryp->total_in = total_in_ori;
	err = sपंचांग32_cryp_रुको_output(cryp);
	अगर (err) अणु
		dev_err(cryp->dev, "Timeout (wite ccm padded data)\n");
		वापस sपंचांग32_cryp_finish_req(cryp, err);
	पूर्ण

	/* c) get and store decrypted data */
	last_total_out = cryp->total_out;
	sपंचांग32_cryp_irq_पढ़ो_data(cryp);

	स_रखो(पंचांगp, 0, माप(पंचांगp));
	scatterwalk_map_and_copy(पंचांगp, out_sg_ori,
				 cryp->total_out_save - last_total_out,
				 last_total_out, 0);

	/* d) Load again CRYP_CSGCMCCMxR */
	क्रम (i = 0; i < ARRAY_SIZE(csपंचांगp2); i++)
		csपंचांगp2[i] = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CSGCMCCM0R + i * 4);

	/* e) change mode back to AES CCM */
	cfg &= ~CR_ALGO_MASK;
	cfg |= CR_AES_CCM;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* f) change phase to header */
	cfg &= ~CR_PH_MASK;
	cfg |= CR_PH_HEADER;
	sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

	/* g) XOR and ग_लिखो padded data */
	क्रम (i = 0; i < ARRAY_SIZE(पंचांगp); i++) अणु
		पंचांगp[i] ^= csपंचांगp1[i];
		पंचांगp[i] ^= csपंचांगp2[i];
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, पंचांगp[i]);
	पूर्ण

	/* h) रुको क्रम completion */
	err = sपंचांग32_cryp_रुको_busy(cryp);
	अगर (err)
		dev_err(cryp->dev, "Timeout (wite ccm padded data)\n");

	/* i) run the he normal Final phase */
	sपंचांग32_cryp_finish_req(cryp, err);
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_data(काष्ठा sपंचांग32_cryp *cryp)
अणु
	अगर (unlikely(!cryp->total_in)) अणु
		dev_warn(cryp->dev, "No more data to process\n");
		वापस;
	पूर्ण

	अगर (unlikely(cryp->total_in < AES_BLOCK_SIZE &&
		     (sपंचांग32_cryp_get_hw_mode(cryp) == CR_AES_GCM) &&
		     is_encrypt(cryp))) अणु
		/* Padding क्रम AES GCM encryption */
		अगर (cryp->caps->padding_wa)
			/* Special हाल 1 */
			वापस sपंचांग32_cryp_irq_ग_लिखो_gcm_padded_data(cryp);

		/* Setting padding bytes (NBBLB) */
		sपंचांग32_cryp_irq_set_npblb(cryp);
	पूर्ण

	अगर (unlikely((cryp->total_in - cryp->authsize < AES_BLOCK_SIZE) &&
		     (sपंचांग32_cryp_get_hw_mode(cryp) == CR_AES_CCM) &&
		     is_decrypt(cryp))) अणु
		/* Padding क्रम AES CCM decryption */
		अगर (cryp->caps->padding_wa)
			/* Special हाल 2 */
			वापस sपंचांग32_cryp_irq_ग_लिखो_ccm_padded_data(cryp);

		/* Setting padding bytes (NBBLB) */
		sपंचांग32_cryp_irq_set_npblb(cryp);
	पूर्ण

	अगर (is_aes(cryp) && is_ctr(cryp))
		sपंचांग32_cryp_check_ctr_counter(cryp);

	sपंचांग32_cryp_irq_ग_लिखो_block(cryp);
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_gcm_header(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i, j;
	u32 cfg, *src;

	src = sg_virt(cryp->in_sg) + _walked_in;

	क्रम (i = 0; i < AES_BLOCK_32; i++) अणु
		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *src);

		src = sपंचांग32_cryp_next_in(cryp, src, माप(u32));
		cryp->total_in -= min_t(माप_प्रकार, माप(u32), cryp->total_in);

		/* Check अगर whole header written */
		अगर ((cryp->total_in_save - cryp->total_in) ==
				cryp->areq->assoclen) अणु
			/* Write padding अगर needed */
			क्रम (j = i + 1; j < AES_BLOCK_32; j++)
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);

			/* Wait क्रम completion */
			err = sपंचांग32_cryp_रुको_busy(cryp);
			अगर (err) अणु
				dev_err(cryp->dev, "Timeout (gcm header)\n");
				वापस sपंचांग32_cryp_finish_req(cryp, err);
			पूर्ण

			अगर (sपंचांग32_cryp_get_input_text_len(cryp)) अणु
				/* Phase 3 : payload */
				cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
				cfg &= ~CR_CRYPEN;
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

				cfg &= ~CR_PH_MASK;
				cfg |= CR_PH_PAYLOAD;
				cfg |= CR_CRYPEN;
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);
			पूर्ण अन्यथा अणु
				/* Phase 4 : tag */
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);
				sपंचांग32_cryp_finish_req(cryp, 0);
			पूर्ण

			अवरोध;
		पूर्ण

		अगर (!cryp->total_in)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_cryp_irq_ग_लिखो_ccm_header(काष्ठा sपंचांग32_cryp *cryp)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i = 0, j, k;
	u32 alen, cfg, *src;
	u8 d8[4];

	src = sg_virt(cryp->in_sg) + _walked_in;
	alen = cryp->areq->assoclen;

	अगर (!_walked_in) अणु
		अगर (cryp->areq->assoclen <= 65280) अणु
			/* Write first u32 of B1 */
			d8[0] = (alen >> 8) & 0xFF;
			d8[1] = alen & 0xFF;
			d8[2] = *((u8 *)src);
			src = sपंचांग32_cryp_next_in(cryp, src, 1);
			d8[3] = *((u8 *)src);
			src = sपंचांग32_cryp_next_in(cryp, src, 1);

			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *(u32 *)d8);
			i++;

			cryp->total_in -= min_t(माप_प्रकार, 2, cryp->total_in);
		पूर्ण अन्यथा अणु
			/* Build the two first u32 of B1 */
			d8[0] = 0xFF;
			d8[1] = 0xFE;
			d8[2] = alen & 0xFF000000;
			d8[3] = alen & 0x00FF0000;

			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *(u32 *)d8);
			i++;

			d8[0] = alen & 0x0000FF00;
			d8[1] = alen & 0x000000FF;
			d8[2] = *((u8 *)src);
			src = sपंचांग32_cryp_next_in(cryp, src, 1);
			d8[3] = *((u8 *)src);
			src = sपंचांग32_cryp_next_in(cryp, src, 1);

			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *(u32 *)d8);
			i++;

			cryp->total_in -= min_t(माप_प्रकार, 2, cryp->total_in);
		पूर्ण
	पूर्ण

	/* Write next u32 */
	क्रम (; i < AES_BLOCK_32; i++) अणु
		/* Build an u32 */
		स_रखो(d8, 0, माप(u32));
		क्रम (k = 0; k < माप(u32); k++) अणु
			d8[k] = *((u8 *)src);
			src = sपंचांग32_cryp_next_in(cryp, src, 1);

			cryp->total_in -= min_t(माप_प्रकार, 1, cryp->total_in);
			अगर ((cryp->total_in_save - cryp->total_in) == alen)
				अवरोध;
		पूर्ण

		sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, *(u32 *)d8);

		अगर ((cryp->total_in_save - cryp->total_in) == alen) अणु
			/* Write padding अगर needed */
			क्रम (j = i + 1; j < AES_BLOCK_32; j++)
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_DIN, 0);

			/* Wait क्रम completion */
			err = sपंचांग32_cryp_रुको_busy(cryp);
			अगर (err) अणु
				dev_err(cryp->dev, "Timeout (ccm header)\n");
				वापस sपंचांग32_cryp_finish_req(cryp, err);
			पूर्ण

			अगर (sपंचांग32_cryp_get_input_text_len(cryp)) अणु
				/* Phase 3 : payload */
				cfg = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR);
				cfg &= ~CR_CRYPEN;
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);

				cfg &= ~CR_PH_MASK;
				cfg |= CR_PH_PAYLOAD;
				cfg |= CR_CRYPEN;
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_CR, cfg);
			पूर्ण अन्यथा अणु
				/* Phase 4 : tag */
				sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);
				sपंचांग32_cryp_finish_req(cryp, 0);
			पूर्ण

			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t sपंचांग32_cryp_irq_thपढ़ो(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_cryp *cryp = arg;
	u32 ph;

	अगर (cryp->irq_status & MISR_OUT)
		/* Output FIFO IRQ: पढ़ो data */
		अगर (unlikely(sपंचांग32_cryp_irq_पढ़ो_data(cryp))) अणु
			/* All bytes processed, finish */
			sपंचांग32_cryp_ग_लिखो(cryp, CRYP_IMSCR, 0);
			sपंचांग32_cryp_finish_req(cryp, 0);
			वापस IRQ_HANDLED;
		पूर्ण

	अगर (cryp->irq_status & MISR_IN) अणु
		अगर (is_gcm(cryp)) अणु
			ph = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR) & CR_PH_MASK;
			अगर (unlikely(ph == CR_PH_HEADER))
				/* Write Header */
				sपंचांग32_cryp_irq_ग_लिखो_gcm_header(cryp);
			अन्यथा
				/* Input FIFO IRQ: ग_लिखो data */
				sपंचांग32_cryp_irq_ग_लिखो_data(cryp);
			cryp->gcm_ctr++;
		पूर्ण अन्यथा अगर (is_ccm(cryp)) अणु
			ph = sपंचांग32_cryp_पढ़ो(cryp, CRYP_CR) & CR_PH_MASK;
			अगर (unlikely(ph == CR_PH_HEADER))
				/* Write Header */
				sपंचांग32_cryp_irq_ग_लिखो_ccm_header(cryp);
			अन्यथा
				/* Input FIFO IRQ: ग_लिखो data */
				sपंचांग32_cryp_irq_ग_लिखो_data(cryp);
		पूर्ण अन्यथा अणु
			/* Input FIFO IRQ: ग_लिखो data */
			sपंचांग32_cryp_irq_ग_लिखो_data(cryp);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sपंचांग32_cryp_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा sपंचांग32_cryp *cryp = arg;

	cryp->irq_status = sपंचांग32_cryp_पढ़ो(cryp, CRYP_MISR);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल काष्ठा skcipher_alg crypto_algs[] = अणु
अणु
	.base.cra_name		= "ecb(aes)",
	.base.cra_driver_name	= "stm32-ecb-aes",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.setkey			= sपंचांग32_cryp_aes_setkey,
	.encrypt		= sपंचांग32_cryp_aes_ecb_encrypt,
	.decrypt		= sपंचांग32_cryp_aes_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(aes)",
	.base.cra_driver_name	= "stm32-cbc-aes",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= AES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_aes_setkey,
	.encrypt		= sपंचांग32_cryp_aes_cbc_encrypt,
	.decrypt		= sपंचांग32_cryp_aes_cbc_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "ctr(aes)",
	.base.cra_driver_name	= "stm32-ctr-aes",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= 1,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_aes_setkey,
	.encrypt		= sपंचांग32_cryp_aes_ctr_encrypt,
	.decrypt		= sपंचांग32_cryp_aes_ctr_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "ecb(des)",
	.base.cra_driver_name	= "stm32-ecb-des",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= DES_BLOCK_SIZE,
	.max_keysize		= DES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_des_setkey,
	.encrypt		= sपंचांग32_cryp_des_ecb_encrypt,
	.decrypt		= sपंचांग32_cryp_des_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des)",
	.base.cra_driver_name	= "stm32-cbc-des",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= DES_BLOCK_SIZE,
	.max_keysize		= DES_BLOCK_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_des_setkey,
	.encrypt		= sपंचांग32_cryp_des_cbc_encrypt,
	.decrypt		= sपंचांग32_cryp_des_cbc_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "ecb(des3_ede)",
	.base.cra_driver_name	= "stm32-ecb-des3",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= 3 * DES_BLOCK_SIZE,
	.max_keysize		= 3 * DES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_tdes_setkey,
	.encrypt		= sपंचांग32_cryp_tdes_ecb_encrypt,
	.decrypt		= sपंचांग32_cryp_tdes_ecb_decrypt,
पूर्ण,
अणु
	.base.cra_name		= "cbc(des3_ede)",
	.base.cra_driver_name	= "stm32-cbc-des3",
	.base.cra_priority	= 200,
	.base.cra_flags		= CRYPTO_ALG_ASYNC,
	.base.cra_blocksize	= DES_BLOCK_SIZE,
	.base.cra_ctxsize	= माप(काष्ठा sपंचांग32_cryp_ctx),
	.base.cra_alignmask	= 0xf,
	.base.cra_module	= THIS_MODULE,

	.init			= sपंचांग32_cryp_init_tfm,
	.min_keysize		= 3 * DES_BLOCK_SIZE,
	.max_keysize		= 3 * DES_BLOCK_SIZE,
	.ivsize			= DES_BLOCK_SIZE,
	.setkey			= sपंचांग32_cryp_tdes_setkey,
	.encrypt		= sपंचांग32_cryp_tdes_cbc_encrypt,
	.decrypt		= sपंचांग32_cryp_tdes_cbc_decrypt,
पूर्ण,
पूर्ण;

अटल काष्ठा aead_alg aead_algs[] = अणु
अणु
	.setkey		= sपंचांग32_cryp_aes_aead_setkey,
	.setauthsize	= sपंचांग32_cryp_aes_gcm_setauthsize,
	.encrypt	= sपंचांग32_cryp_aes_gcm_encrypt,
	.decrypt	= sपंचांग32_cryp_aes_gcm_decrypt,
	.init		= sपंचांग32_cryp_aes_aead_init,
	.ivsize		= 12,
	.maxauthsize	= AES_BLOCK_SIZE,

	.base = अणु
		.cra_name		= "gcm(aes)",
		.cra_driver_name	= "stm32-gcm-aes",
		.cra_priority		= 200,
		.cra_flags		= CRYPTO_ALG_ASYNC,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा sपंचांग32_cryp_ctx),
		.cra_alignmask		= 0xf,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण,
अणु
	.setkey		= sपंचांग32_cryp_aes_aead_setkey,
	.setauthsize	= sपंचांग32_cryp_aes_ccm_setauthsize,
	.encrypt	= sपंचांग32_cryp_aes_ccm_encrypt,
	.decrypt	= sपंचांग32_cryp_aes_ccm_decrypt,
	.init		= sपंचांग32_cryp_aes_aead_init,
	.ivsize		= AES_BLOCK_SIZE,
	.maxauthsize	= AES_BLOCK_SIZE,

	.base = अणु
		.cra_name		= "ccm(aes)",
		.cra_driver_name	= "stm32-ccm-aes",
		.cra_priority		= 200,
		.cra_flags		= CRYPTO_ALG_ASYNC,
		.cra_blocksize		= 1,
		.cra_ctxsize		= माप(काष्ठा sपंचांग32_cryp_ctx),
		.cra_alignmask		= 0xf,
		.cra_module		= THIS_MODULE,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_cryp_caps f7_data = अणु
	.swap_final = true,
	.padding_wa = true,
पूर्ण;

अटल स्थिर काष्ठा sपंचांग32_cryp_caps mp1_data = अणु
	.swap_final = false,
	.padding_wa = false,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग32_dt_ids[] = अणु
	अणु .compatible = "st,stm32f756-cryp", .data = &f7_dataपूर्ण,
	अणु .compatible = "st,stm32mp1-cryp", .data = &mp1_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dt_ids);

अटल पूर्णांक sपंचांग32_cryp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_cryp *cryp;
	काष्ठा reset_control *rst;
	पूर्णांक irq, ret;

	cryp = devm_kzalloc(dev, माप(*cryp), GFP_KERNEL);
	अगर (!cryp)
		वापस -ENOMEM;

	cryp->caps = of_device_get_match_data(dev);
	अगर (!cryp->caps)
		वापस -ENODEV;

	cryp->dev = dev;

	cryp->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(cryp->regs))
		वापस PTR_ERR(cryp->regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_thपढ़ोed_irq(dev, irq, sपंचांग32_cryp_irq,
					sपंचांग32_cryp_irq_thपढ़ो, IRQF_ONESHOT,
					dev_name(dev), cryp);
	अगर (ret) अणु
		dev_err(dev, "Cannot grab IRQ\n");
		वापस ret;
	पूर्ण

	cryp->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(cryp->clk)) अणु
		dev_err(dev, "Could not get clock\n");
		वापस PTR_ERR(cryp->clk);
	पूर्ण

	ret = clk_prepare_enable(cryp->clk);
	अगर (ret) अणु
		dev_err(cryp->dev, "Failed to enable clock\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_स्वतःsuspend_delay(dev, CRYP_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(dev);

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	rst = devm_reset_control_get(dev, शून्य);
	अगर (!IS_ERR(rst)) अणु
		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	platक्रमm_set_drvdata(pdev, cryp);

	spin_lock(&cryp_list.lock);
	list_add(&cryp->list, &cryp_list.dev_list);
	spin_unlock(&cryp_list.lock);

	/* Initialize crypto engine */
	cryp->engine = crypto_engine_alloc_init(dev, 1);
	अगर (!cryp->engine) अणु
		dev_err(dev, "Could not init crypto engine\n");
		ret = -ENOMEM;
		जाओ err_engine1;
	पूर्ण

	ret = crypto_engine_start(cryp->engine);
	अगर (ret) अणु
		dev_err(dev, "Could not start crypto engine\n");
		जाओ err_engine2;
	पूर्ण

	ret = crypto_रेजिस्टर_skciphers(crypto_algs, ARRAY_SIZE(crypto_algs));
	अगर (ret) अणु
		dev_err(dev, "Could not register algs\n");
		जाओ err_algs;
	पूर्ण

	ret = crypto_रेजिस्टर_aeads(aead_algs, ARRAY_SIZE(aead_algs));
	अगर (ret)
		जाओ err_aead_algs;

	dev_info(dev, "Initialized\n");

	pm_runसमय_put_sync(dev);

	वापस 0;

err_aead_algs:
	crypto_unरेजिस्टर_skciphers(crypto_algs, ARRAY_SIZE(crypto_algs));
err_algs:
err_engine2:
	crypto_engine_निकास(cryp->engine);
err_engine1:
	spin_lock(&cryp_list.lock);
	list_del(&cryp->list);
	spin_unlock(&cryp_list.lock);

	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	pm_runसमय_put_noidle(dev);

	clk_disable_unprepare(cryp->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_cryp *cryp = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	अगर (!cryp)
		वापस -ENODEV;

	ret = pm_runसमय_resume_and_get(cryp->dev);
	अगर (ret < 0)
		वापस ret;

	crypto_unरेजिस्टर_aeads(aead_algs, ARRAY_SIZE(aead_algs));
	crypto_unरेजिस्टर_skciphers(crypto_algs, ARRAY_SIZE(crypto_algs));

	crypto_engine_निकास(cryp->engine);

	spin_lock(&cryp_list.lock);
	list_del(&cryp->list);
	spin_unlock(&cryp_list.lock);

	pm_runसमय_disable(cryp->dev);
	pm_runसमय_put_noidle(cryp->dev);

	clk_disable_unprepare(cryp->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_cryp_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_cryp *cryp = dev_get_drvdata(dev);

	clk_disable_unprepare(cryp->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_cryp_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_cryp *cryp = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(cryp->clk);
	अगर (ret) अणु
		dev_err(cryp->dev, "Failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_cryp_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_cryp_runसमय_suspend,
			   sपंचांग32_cryp_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_cryp_driver = अणु
	.probe  = sपंचांग32_cryp_probe,
	.हटाओ = sपंचांग32_cryp_हटाओ,
	.driver = अणु
		.name           = DRIVER_NAME,
		.pm		= &sपंचांग32_cryp_pm_ops,
		.of_match_table = sपंचांग32_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sपंचांग32_cryp_driver);

MODULE_AUTHOR("Fabien Dessenne <fabien.dessenne@st.com>");
MODULE_DESCRIPTION("STMicrolectronics STM32 CRYP hardware driver");
MODULE_LICENSE("GPL");
