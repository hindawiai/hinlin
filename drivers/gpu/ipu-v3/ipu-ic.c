<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2014 Mentor Graphics Inc.
 * Copyright 2005-2012 Freescale Semiconductor, Inc. All Rights Reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/sizes.h>
#समावेश "ipu-prv.h"

/* IC Register Offsets */
#घोषणा IC_CONF                 0x0000
#घोषणा IC_PRP_ENC_RSC          0x0004
#घोषणा IC_PRP_VF_RSC           0x0008
#घोषणा IC_PP_RSC               0x000C
#घोषणा IC_CMBP_1               0x0010
#घोषणा IC_CMBP_2               0x0014
#घोषणा IC_IDMAC_1              0x0018
#घोषणा IC_IDMAC_2              0x001C
#घोषणा IC_IDMAC_3              0x0020
#घोषणा IC_IDMAC_4              0x0024

/* IC Register Fields */
#घोषणा IC_CONF_PRPENC_EN       (1 << 0)
#घोषणा IC_CONF_PRPENC_CSC1     (1 << 1)
#घोषणा IC_CONF_PRPENC_ROT_EN   (1 << 2)
#घोषणा IC_CONF_PRPVF_EN        (1 << 8)
#घोषणा IC_CONF_PRPVF_CSC1      (1 << 9)
#घोषणा IC_CONF_PRPVF_CSC2      (1 << 10)
#घोषणा IC_CONF_PRPVF_CMB       (1 << 11)
#घोषणा IC_CONF_PRPVF_ROT_EN    (1 << 12)
#घोषणा IC_CONF_PP_EN           (1 << 16)
#घोषणा IC_CONF_PP_CSC1         (1 << 17)
#घोषणा IC_CONF_PP_CSC2         (1 << 18)
#घोषणा IC_CONF_PP_CMB          (1 << 19)
#घोषणा IC_CONF_PP_ROT_EN       (1 << 20)
#घोषणा IC_CONF_IC_GLB_LOC_A    (1 << 28)
#घोषणा IC_CONF_KEY_COLOR_EN    (1 << 29)
#घोषणा IC_CONF_RWS_EN          (1 << 30)
#घोषणा IC_CONF_CSI_MEM_WR_EN   (1 << 31)

#घोषणा IC_IDMAC_1_CB0_BURST_16         (1 << 0)
#घोषणा IC_IDMAC_1_CB1_BURST_16         (1 << 1)
#घोषणा IC_IDMAC_1_CB2_BURST_16         (1 << 2)
#घोषणा IC_IDMAC_1_CB3_BURST_16         (1 << 3)
#घोषणा IC_IDMAC_1_CB4_BURST_16         (1 << 4)
#घोषणा IC_IDMAC_1_CB5_BURST_16         (1 << 5)
#घोषणा IC_IDMAC_1_CB6_BURST_16         (1 << 6)
#घोषणा IC_IDMAC_1_CB7_BURST_16         (1 << 7)
#घोषणा IC_IDMAC_1_PRPENC_ROT_MASK      (0x7 << 11)
#घोषणा IC_IDMAC_1_PRPENC_ROT_OFFSET    11
#घोषणा IC_IDMAC_1_PRPVF_ROT_MASK       (0x7 << 14)
#घोषणा IC_IDMAC_1_PRPVF_ROT_OFFSET     14
#घोषणा IC_IDMAC_1_PP_ROT_MASK          (0x7 << 17)
#घोषणा IC_IDMAC_1_PP_ROT_OFFSET        17
#घोषणा IC_IDMAC_1_PP_FLIP_RS           (1 << 22)
#घोषणा IC_IDMAC_1_PRPVF_FLIP_RS        (1 << 21)
#घोषणा IC_IDMAC_1_PRPENC_FLIP_RS       (1 << 20)

#घोषणा IC_IDMAC_2_PRPENC_HEIGHT_MASK   (0x3ff << 0)
#घोषणा IC_IDMAC_2_PRPENC_HEIGHT_OFFSET 0
#घोषणा IC_IDMAC_2_PRPVF_HEIGHT_MASK    (0x3ff << 10)
#घोषणा IC_IDMAC_2_PRPVF_HEIGHT_OFFSET  10
#घोषणा IC_IDMAC_2_PP_HEIGHT_MASK       (0x3ff << 20)
#घोषणा IC_IDMAC_2_PP_HEIGHT_OFFSET     20

#घोषणा IC_IDMAC_3_PRPENC_WIDTH_MASK    (0x3ff << 0)
#घोषणा IC_IDMAC_3_PRPENC_WIDTH_OFFSET  0
#घोषणा IC_IDMAC_3_PRPVF_WIDTH_MASK     (0x3ff << 10)
#घोषणा IC_IDMAC_3_PRPVF_WIDTH_OFFSET   10
#घोषणा IC_IDMAC_3_PP_WIDTH_MASK        (0x3ff << 20)
#घोषणा IC_IDMAC_3_PP_WIDTH_OFFSET      20

काष्ठा ic_task_regoffs अणु
	u32 rsc;
	u32 tpmem_csc[2];
पूर्ण;

काष्ठा ic_task_bitfields अणु
	u32 ic_conf_en;
	u32 ic_conf_rot_en;
	u32 ic_conf_cmb_en;
	u32 ic_conf_csc1_en;
	u32 ic_conf_csc2_en;
	u32 ic_cmb_galpha_bit;
पूर्ण;

अटल स्थिर काष्ठा ic_task_regoffs ic_task_reg[IC_NUM_TASKS] = अणु
	[IC_TASK_ENCODER] = अणु
		.rsc = IC_PRP_ENC_RSC,
		.tpmem_csc = अणु0x2008, 0पूर्ण,
	पूर्ण,
	[IC_TASK_VIEWFINDER] = अणु
		.rsc = IC_PRP_VF_RSC,
		.tpmem_csc = अणु0x4028, 0x4040पूर्ण,
	पूर्ण,
	[IC_TASK_POST_PROCESSOR] = अणु
		.rsc = IC_PP_RSC,
		.tpmem_csc = अणु0x6060, 0x6078पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ic_task_bitfields ic_task_bit[IC_NUM_TASKS] = अणु
	[IC_TASK_ENCODER] = अणु
		.ic_conf_en = IC_CONF_PRPENC_EN,
		.ic_conf_rot_en = IC_CONF_PRPENC_ROT_EN,
		.ic_conf_cmb_en = 0,    /* NA */
		.ic_conf_csc1_en = IC_CONF_PRPENC_CSC1,
		.ic_conf_csc2_en = 0,   /* NA */
		.ic_cmb_galpha_bit = 0, /* NA */
	पूर्ण,
	[IC_TASK_VIEWFINDER] = अणु
		.ic_conf_en = IC_CONF_PRPVF_EN,
		.ic_conf_rot_en = IC_CONF_PRPVF_ROT_EN,
		.ic_conf_cmb_en = IC_CONF_PRPVF_CMB,
		.ic_conf_csc1_en = IC_CONF_PRPVF_CSC1,
		.ic_conf_csc2_en = IC_CONF_PRPVF_CSC2,
		.ic_cmb_galpha_bit = 0,
	पूर्ण,
	[IC_TASK_POST_PROCESSOR] = अणु
		.ic_conf_en = IC_CONF_PP_EN,
		.ic_conf_rot_en = IC_CONF_PP_ROT_EN,
		.ic_conf_cmb_en = IC_CONF_PP_CMB,
		.ic_conf_csc1_en = IC_CONF_PP_CSC1,
		.ic_conf_csc2_en = IC_CONF_PP_CSC2,
		.ic_cmb_galpha_bit = 8,
	पूर्ण,
पूर्ण;

काष्ठा ipu_ic_priv;

काष्ठा ipu_ic अणु
	क्रमागत ipu_ic_task task;
	स्थिर काष्ठा ic_task_regoffs *reg;
	स्थिर काष्ठा ic_task_bitfields *bit;

	काष्ठा ipu_ic_colorspace in_cs;
	काष्ठा ipu_ic_colorspace g_in_cs;
	काष्ठा ipu_ic_colorspace out_cs;

	bool graphics;
	bool rotation;
	bool in_use;

	काष्ठा ipu_ic_priv *priv;
पूर्ण;

काष्ठा ipu_ic_priv अणु
	व्योम __iomem *base;
	व्योम __iomem *tpmem_base;
	spinlock_t lock;
	काष्ठा ipu_soc *ipu;
	पूर्णांक use_count;
	पूर्णांक irt_use_count;
	काष्ठा ipu_ic task[IC_NUM_TASKS];
पूर्ण;

अटल अंतरभूत u32 ipu_ic_पढ़ो(काष्ठा ipu_ic *ic, अचिन्हित offset)
अणु
	वापस पढ़ोl(ic->priv->base + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_ic_ग_लिखो(काष्ठा ipu_ic *ic, u32 value, अचिन्हित offset)
अणु
	ग_लिखोl(value, ic->priv->base + offset);
पूर्ण

अटल पूर्णांक init_csc(काष्ठा ipu_ic *ic,
		    स्थिर काष्ठा ipu_ic_csc *csc,
		    पूर्णांक csc_index)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	u32 __iomem *base;
	स्थिर u16 (*c)[3];
	स्थिर u16 *a;
	u32 param;

	base = (u32 __iomem *)
		(priv->tpmem_base + ic->reg->tpmem_csc[csc_index]);

	/* Cast to अचिन्हित */
	c = (स्थिर u16 (*)[3])csc->params.coeff;
	a = (स्थिर u16 *)csc->params.offset;

	param = ((a[0] & 0x1f) << 27) | ((c[0][0] & 0x1ff) << 18) |
		((c[1][1] & 0x1ff) << 9) | (c[2][2] & 0x1ff);
	ग_लिखोl(param, base++);

	param = ((a[0] & 0x1fe0) >> 5) | (csc->params.scale << 8) |
		(csc->params.sat << 10);
	ग_लिखोl(param, base++);

	param = ((a[1] & 0x1f) << 27) | ((c[0][1] & 0x1ff) << 18) |
		((c[1][0] & 0x1ff) << 9) | (c[2][0] & 0x1ff);
	ग_लिखोl(param, base++);

	param = ((a[1] & 0x1fe0) >> 5);
	ग_लिखोl(param, base++);

	param = ((a[2] & 0x1f) << 27) | ((c[0][2] & 0x1ff) << 18) |
		((c[1][2] & 0x1ff) << 9) | (c[2][1] & 0x1ff);
	ग_लिखोl(param, base++);

	param = ((a[2] & 0x1fe0) >> 5);
	ग_लिखोl(param, base++);

	वापस 0;
पूर्ण

अटल पूर्णांक calc_resize_coeffs(काष्ठा ipu_ic *ic,
			      u32 in_size, u32 out_size,
			      u32 *resize_coeff,
			      u32 *करोwnsize_coeff)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	काष्ठा ipu_soc *ipu = priv->ipu;
	u32 temp_size, temp_करोwnsize;

	/*
	 * Input size cannot be more than 4096, and output size cannot
	 * be more than 1024
	 */
	अगर (in_size > 4096) अणु
		dev_err(ipu->dev, "Unsupported resize (in_size > 4096)\n");
		वापस -EINVAL;
	पूर्ण
	अगर (out_size > 1024) अणु
		dev_err(ipu->dev, "Unsupported resize (out_size > 1024)\n");
		वापस -EINVAL;
	पूर्ण

	/* Cannot करोwnsize more than 4:1 */
	अगर ((out_size << 2) < in_size) अणु
		dev_err(ipu->dev, "Unsupported downsize\n");
		वापस -EINVAL;
	पूर्ण

	/* Compute करोwnsizing coefficient */
	temp_करोwnsize = 0;
	temp_size = in_size;
	जबतक (((temp_size > 1024) || (temp_size >= out_size * 2)) &&
	       (temp_करोwnsize < 2)) अणु
		temp_size >>= 1;
		temp_करोwnsize++;
	पूर्ण
	*करोwnsize_coeff = temp_करोwnsize;

	/*
	 * compute resizing coefficient using the following equation:
	 * resize_coeff = M * (SI - 1) / (SO - 1)
	 * where M = 2^13, SI = input size, SO = output size
	 */
	*resize_coeff = (8192L * (temp_size - 1)) / (out_size - 1);
	अगर (*resize_coeff >= 16384L) अणु
		dev_err(ipu->dev, "Warning! Overflow on resize coeff.\n");
		*resize_coeff = 0x3FFF;
	पूर्ण

	वापस 0;
पूर्ण

व्योम ipu_ic_task_enable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	अचिन्हित दीर्घ flags;
	u32 ic_conf;

	spin_lock_irqsave(&priv->lock, flags);

	ic_conf = ipu_ic_पढ़ो(ic, IC_CONF);

	ic_conf |= ic->bit->ic_conf_en;

	अगर (ic->rotation)
		ic_conf |= ic->bit->ic_conf_rot_en;

	अगर (ic->in_cs.cs != ic->out_cs.cs)
		ic_conf |= ic->bit->ic_conf_csc1_en;

	अगर (ic->graphics) अणु
		ic_conf |= ic->bit->ic_conf_cmb_en;
		ic_conf |= ic->bit->ic_conf_csc1_en;

		अगर (ic->g_in_cs.cs != ic->out_cs.cs)
			ic_conf |= ic->bit->ic_conf_csc2_en;
	पूर्ण

	ipu_ic_ग_लिखो(ic, ic_conf, IC_CONF);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_task_enable);

व्योम ipu_ic_task_disable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	अचिन्हित दीर्घ flags;
	u32 ic_conf;

	spin_lock_irqsave(&priv->lock, flags);

	ic_conf = ipu_ic_पढ़ो(ic, IC_CONF);

	ic_conf &= ~(ic->bit->ic_conf_en |
		     ic->bit->ic_conf_csc1_en |
		     ic->bit->ic_conf_rot_en);
	अगर (ic->bit->ic_conf_csc2_en)
		ic_conf &= ~ic->bit->ic_conf_csc2_en;
	अगर (ic->bit->ic_conf_cmb_en)
		ic_conf &= ~ic->bit->ic_conf_cmb_en;

	ipu_ic_ग_लिखो(ic, ic_conf, IC_CONF);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_task_disable);

पूर्णांक ipu_ic_task_graphics_init(काष्ठा ipu_ic *ic,
			      स्थिर काष्ठा ipu_ic_colorspace *g_in_cs,
			      bool galpha_en, u32 galpha,
			      bool colorkey_en, u32 colorkey)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	काष्ठा ipu_ic_csc csc2;
	अचिन्हित दीर्घ flags;
	u32 reg, ic_conf;
	पूर्णांक ret = 0;

	अगर (ic->task == IC_TASK_ENCODER)
		वापस -EINVAL;

	spin_lock_irqsave(&priv->lock, flags);

	ic_conf = ipu_ic_पढ़ो(ic, IC_CONF);

	अगर (!(ic_conf & ic->bit->ic_conf_csc1_en)) अणु
		काष्ठा ipu_ic_csc csc1;

		ret = ipu_ic_calc_csc(&csc1,
				      V4L2_YCBCR_ENC_601,
				      V4L2_QUANTIZATION_FULL_RANGE,
				      IPUV3_COLORSPACE_RGB,
				      V4L2_YCBCR_ENC_601,
				      V4L2_QUANTIZATION_FULL_RANGE,
				      IPUV3_COLORSPACE_RGB);
		अगर (ret)
			जाओ unlock;

		/* need transparent CSC1 conversion */
		ret = init_csc(ic, &csc1, 0);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	ic->g_in_cs = *g_in_cs;
	csc2.in_cs = ic->g_in_cs;
	csc2.out_cs = ic->out_cs;

	ret = __ipu_ic_calc_csc(&csc2);
	अगर (ret)
		जाओ unlock;

	ret = init_csc(ic, &csc2, 1);
	अगर (ret)
		जाओ unlock;

	अगर (galpha_en) अणु
		ic_conf |= IC_CONF_IC_GLB_LOC_A;
		reg = ipu_ic_पढ़ो(ic, IC_CMBP_1);
		reg &= ~(0xff << ic->bit->ic_cmb_galpha_bit);
		reg |= (galpha << ic->bit->ic_cmb_galpha_bit);
		ipu_ic_ग_लिखो(ic, reg, IC_CMBP_1);
	पूर्ण अन्यथा
		ic_conf &= ~IC_CONF_IC_GLB_LOC_A;

	अगर (colorkey_en) अणु
		ic_conf |= IC_CONF_KEY_COLOR_EN;
		ipu_ic_ग_लिखो(ic, colorkey, IC_CMBP_2);
	पूर्ण अन्यथा
		ic_conf &= ~IC_CONF_KEY_COLOR_EN;

	ipu_ic_ग_लिखो(ic, ic_conf, IC_CONF);

	ic->graphics = true;
unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_task_graphics_init);

पूर्णांक ipu_ic_task_init_rsc(काष्ठा ipu_ic *ic,
			 स्थिर काष्ठा ipu_ic_csc *csc,
			 पूर्णांक in_width, पूर्णांक in_height,
			 पूर्णांक out_width, पूर्णांक out_height,
			 u32 rsc)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	u32 करोwnsize_coeff, resize_coeff;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!rsc) अणु
		/* Setup vertical resizing */

		ret = calc_resize_coeffs(ic, in_height, out_height,
					 &resize_coeff, &करोwnsize_coeff);
		अगर (ret)
			वापस ret;

		rsc = (करोwnsize_coeff << 30) | (resize_coeff << 16);

		/* Setup horizontal resizing */
		ret = calc_resize_coeffs(ic, in_width, out_width,
					 &resize_coeff, &करोwnsize_coeff);
		अगर (ret)
			वापस ret;

		rsc |= (करोwnsize_coeff << 14) | resize_coeff;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);

	ipu_ic_ग_लिखो(ic, rsc, ic->reg->rsc);

	/* Setup color space conversion */
	ic->in_cs = csc->in_cs;
	ic->out_cs = csc->out_cs;

	ret = init_csc(ic, csc, 0);

	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण

पूर्णांक ipu_ic_task_init(काष्ठा ipu_ic *ic,
		     स्थिर काष्ठा ipu_ic_csc *csc,
		     पूर्णांक in_width, पूर्णांक in_height,
		     पूर्णांक out_width, पूर्णांक out_height)
अणु
	वापस ipu_ic_task_init_rsc(ic, csc,
				    in_width, in_height,
				    out_width, out_height, 0);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_task_init);

पूर्णांक ipu_ic_task_idma_init(काष्ठा ipu_ic *ic, काष्ठा ipuv3_channel *channel,
			  u32 width, u32 height, पूर्णांक burst_size,
			  क्रमागत ipu_rotate_mode rot)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	काष्ठा ipu_soc *ipu = priv->ipu;
	u32 ic_idmac_1, ic_idmac_2, ic_idmac_3;
	u32 temp_rot = bitrev8(rot) >> 5;
	bool need_hor_flip = false;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर ((burst_size != 8) && (burst_size != 16)) अणु
		dev_err(ipu->dev, "Illegal burst length for IC\n");
		वापस -EINVAL;
	पूर्ण

	width--;
	height--;

	अगर (temp_rot & 0x2)	/* Need horizontal flip */
		need_hor_flip = true;

	spin_lock_irqsave(&priv->lock, flags);

	ic_idmac_1 = ipu_ic_पढ़ो(ic, IC_IDMAC_1);
	ic_idmac_2 = ipu_ic_पढ़ो(ic, IC_IDMAC_2);
	ic_idmac_3 = ipu_ic_पढ़ो(ic, IC_IDMAC_3);

	चयन (channel->num) अणु
	हाल IPUV3_CHANNEL_IC_PP_MEM:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB2_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB2_BURST_16;

		अगर (need_hor_flip)
			ic_idmac_1 |= IC_IDMAC_1_PP_FLIP_RS;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_PP_FLIP_RS;

		ic_idmac_2 &= ~IC_IDMAC_2_PP_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PP_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PP_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PP_WIDTH_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_MEM_IC_PP:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB5_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB5_BURST_16;
		अवरोध;
	हाल IPUV3_CHANNEL_MEM_ROT_PP:
		ic_idmac_1 &= ~IC_IDMAC_1_PP_ROT_MASK;
		ic_idmac_1 |= temp_rot << IC_IDMAC_1_PP_ROT_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_MEM_IC_PRP_VF:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB6_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB6_BURST_16;
		अवरोध;
	हाल IPUV3_CHANNEL_IC_PRP_ENC_MEM:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB0_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB0_BURST_16;

		अगर (need_hor_flip)
			ic_idmac_1 |= IC_IDMAC_1_PRPENC_FLIP_RS;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_PRPENC_FLIP_RS;

		ic_idmac_2 &= ~IC_IDMAC_2_PRPENC_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PRPENC_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PRPENC_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PRPENC_WIDTH_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_MEM_ROT_ENC:
		ic_idmac_1 &= ~IC_IDMAC_1_PRPENC_ROT_MASK;
		ic_idmac_1 |= temp_rot << IC_IDMAC_1_PRPENC_ROT_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_IC_PRP_VF_MEM:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB1_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB1_BURST_16;

		अगर (need_hor_flip)
			ic_idmac_1 |= IC_IDMAC_1_PRPVF_FLIP_RS;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_PRPVF_FLIP_RS;

		ic_idmac_2 &= ~IC_IDMAC_2_PRPVF_HEIGHT_MASK;
		ic_idmac_2 |= height << IC_IDMAC_2_PRPVF_HEIGHT_OFFSET;

		ic_idmac_3 &= ~IC_IDMAC_3_PRPVF_WIDTH_MASK;
		ic_idmac_3 |= width << IC_IDMAC_3_PRPVF_WIDTH_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_MEM_ROT_VF:
		ic_idmac_1 &= ~IC_IDMAC_1_PRPVF_ROT_MASK;
		ic_idmac_1 |= temp_rot << IC_IDMAC_1_PRPVF_ROT_OFFSET;
		अवरोध;
	हाल IPUV3_CHANNEL_G_MEM_IC_PRP_VF:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB3_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB3_BURST_16;
		अवरोध;
	हाल IPUV3_CHANNEL_G_MEM_IC_PP:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB4_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB4_BURST_16;
		अवरोध;
	हाल IPUV3_CHANNEL_VDI_MEM_IC_VF:
		अगर (burst_size == 16)
			ic_idmac_1 |= IC_IDMAC_1_CB7_BURST_16;
		अन्यथा
			ic_idmac_1 &= ~IC_IDMAC_1_CB7_BURST_16;
		अवरोध;
	शेष:
		जाओ unlock;
	पूर्ण

	ipu_ic_ग_लिखो(ic, ic_idmac_1, IC_IDMAC_1);
	ipu_ic_ग_लिखो(ic, ic_idmac_2, IC_IDMAC_2);
	ipu_ic_ग_लिखो(ic, ic_idmac_3, IC_IDMAC_3);

	अगर (ipu_rot_mode_is_irt(rot))
		ic->rotation = true;

unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_task_idma_init);

अटल व्योम ipu_irt_enable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;

	अगर (!priv->irt_use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_ROT_EN);

	priv->irt_use_count++;
पूर्ण

अटल व्योम ipu_irt_disable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;

	अगर (priv->irt_use_count) अणु
		अगर (!--priv->irt_use_count)
			ipu_module_disable(priv->ipu, IPU_CONF_ROT_EN);
	पूर्ण
पूर्ण

पूर्णांक ipu_ic_enable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	अगर (!priv->use_count)
		ipu_module_enable(priv->ipu, IPU_CONF_IC_EN);

	priv->use_count++;

	अगर (ic->rotation)
		ipu_irt_enable(ic);

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_enable);

पूर्णांक ipu_ic_disable(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	priv->use_count--;

	अगर (!priv->use_count)
		ipu_module_disable(priv->ipu, IPU_CONF_IC_EN);

	अगर (priv->use_count < 0)
		priv->use_count = 0;

	अगर (ic->rotation)
		ipu_irt_disable(ic);

	ic->rotation = ic->graphics = false;

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_disable);

काष्ठा ipu_ic *ipu_ic_get(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task task)
अणु
	काष्ठा ipu_ic_priv *priv = ipu->ic_priv;
	अचिन्हित दीर्घ flags;
	काष्ठा ipu_ic *ic, *ret;

	अगर (task >= IC_NUM_TASKS)
		वापस ERR_PTR(-EINVAL);

	ic = &priv->task[task];

	spin_lock_irqsave(&priv->lock, flags);

	अगर (ic->in_use) अणु
		ret = ERR_PTR(-EBUSY);
		जाओ unlock;
	पूर्ण

	ic->in_use = true;
	ret = ic;

unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_get);

व्योम ipu_ic_put(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);
	ic->in_use = false;
	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_put);

पूर्णांक ipu_ic_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		अचिन्हित दीर्घ base, अचिन्हित दीर्घ tpmem_base)
अणु
	काष्ठा ipu_ic_priv *priv;
	पूर्णांक i;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ipu->ic_priv = priv;

	spin_lock_init(&priv->lock);
	priv->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!priv->base)
		वापस -ENOMEM;
	priv->tpmem_base = devm_ioremap(dev, tpmem_base, SZ_64K);
	अगर (!priv->tpmem_base)
		वापस -ENOMEM;

	dev_dbg(dev, "IC base: 0x%08lx remapped to %p\n", base, priv->base);

	priv->ipu = ipu;

	क्रम (i = 0; i < IC_NUM_TASKS; i++) अणु
		priv->task[i].task = i;
		priv->task[i].priv = priv;
		priv->task[i].reg = &ic_task_reg[i];
		priv->task[i].bit = &ic_task_bit[i];
	पूर्ण

	वापस 0;
पूर्ण

व्योम ipu_ic_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण

व्योम ipu_ic_dump(काष्ठा ipu_ic *ic)
अणु
	काष्ठा ipu_ic_priv *priv = ic->priv;
	काष्ठा ipu_soc *ipu = priv->ipu;

	dev_dbg(ipu->dev, "IC_CONF = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_CONF));
	dev_dbg(ipu->dev, "IC_PRP_ENC_RSC = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_PRP_ENC_RSC));
	dev_dbg(ipu->dev, "IC_PRP_VF_RSC = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_PRP_VF_RSC));
	dev_dbg(ipu->dev, "IC_PP_RSC = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_PP_RSC));
	dev_dbg(ipu->dev, "IC_CMBP_1 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_CMBP_1));
	dev_dbg(ipu->dev, "IC_CMBP_2 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_CMBP_2));
	dev_dbg(ipu->dev, "IC_IDMAC_1 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_IDMAC_1));
	dev_dbg(ipu->dev, "IC_IDMAC_2 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_IDMAC_2));
	dev_dbg(ipu->dev, "IC_IDMAC_3 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_IDMAC_3));
	dev_dbg(ipu->dev, "IC_IDMAC_4 = \t0x%08X\n",
		ipu_ic_पढ़ो(ic, IC_IDMAC_4));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_ic_dump);
