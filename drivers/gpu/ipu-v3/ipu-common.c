<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2010 Sascha Hauer <s.hauer@pengutronix.de>
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/types.h>
#समावेश <linux/reset.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/list.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_fourcc.h>

#समावेश <video/imx-ipu-v3.h>
#समावेश "ipu-prv.h"

अटल अंतरभूत u32 ipu_cm_पढ़ो(काष्ठा ipu_soc *ipu, अचिन्हित offset)
अणु
	वापस पढ़ोl(ipu->cm_reg + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_cm_ग_लिखो(काष्ठा ipu_soc *ipu, u32 value, अचिन्हित offset)
अणु
	ग_लिखोl(value, ipu->cm_reg + offset);
पूर्ण

पूर्णांक ipu_get_num(काष्ठा ipu_soc *ipu)
अणु
	वापस ipu->id;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_get_num);

व्योम ipu_srm_dp_update(काष्ठा ipu_soc *ipu, bool sync)
अणु
	u32 val;

	val = ipu_cm_पढ़ो(ipu, IPU_SRM_PRI2);
	val &= ~DP_S_SRM_MODE_MASK;
	val |= sync ? DP_S_SRM_MODE_NEXT_FRAME :
		      DP_S_SRM_MODE_NOW;
	ipu_cm_ग_लिखो(ipu, val, IPU_SRM_PRI2);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_srm_dp_update);

क्रमागत ipu_color_space ipu_drm_fourcc_to_colorspace(u32 drm_fourcc)
अणु
	चयन (drm_fourcc) अणु
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_ABGR1555:
	हाल DRM_FORMAT_RGBA5551:
	हाल DRM_FORMAT_BGRA5551:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_BGR565:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_BGR888:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_RGBX8888:
	हाल DRM_FORMAT_BGRX8888:
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_RGBA8888:
	हाल DRM_FORMAT_BGRA8888:
	हाल DRM_FORMAT_RGB565_A8:
	हाल DRM_FORMAT_BGR565_A8:
	हाल DRM_FORMAT_RGB888_A8:
	हाल DRM_FORMAT_BGR888_A8:
	हाल DRM_FORMAT_RGBX8888_A8:
	हाल DRM_FORMAT_BGRX8888_A8:
		वापस IPUV3_COLORSPACE_RGB;
	हाल DRM_FORMAT_YUYV:
	हाल DRM_FORMAT_UYVY:
	हाल DRM_FORMAT_YUV420:
	हाल DRM_FORMAT_YVU420:
	हाल DRM_FORMAT_YUV422:
	हाल DRM_FORMAT_YVU422:
	हाल DRM_FORMAT_YUV444:
	हाल DRM_FORMAT_YVU444:
	हाल DRM_FORMAT_NV12:
	हाल DRM_FORMAT_NV21:
	हाल DRM_FORMAT_NV16:
	हाल DRM_FORMAT_NV61:
		वापस IPUV3_COLORSPACE_YUV;
	शेष:
		वापस IPUV3_COLORSPACE_UNKNOWN;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_drm_fourcc_to_colorspace);

क्रमागत ipu_color_space ipu_pixelक्रमmat_to_colorspace(u32 pixelक्रमmat)
अणु
	चयन (pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUV420:
	हाल V4L2_PIX_FMT_YVU420:
	हाल V4L2_PIX_FMT_YUV422P:
	हाल V4L2_PIX_FMT_UYVY:
	हाल V4L2_PIX_FMT_YUYV:
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV21:
	हाल V4L2_PIX_FMT_NV16:
	हाल V4L2_PIX_FMT_NV61:
		वापस IPUV3_COLORSPACE_YUV;
	हाल V4L2_PIX_FMT_RGB565:
	हाल V4L2_PIX_FMT_BGR24:
	हाल V4L2_PIX_FMT_RGB24:
	हाल V4L2_PIX_FMT_ABGR32:
	हाल V4L2_PIX_FMT_XBGR32:
	हाल V4L2_PIX_FMT_BGRA32:
	हाल V4L2_PIX_FMT_BGRX32:
	हाल V4L2_PIX_FMT_RGBA32:
	हाल V4L2_PIX_FMT_RGBX32:
	हाल V4L2_PIX_FMT_ARGB32:
	हाल V4L2_PIX_FMT_XRGB32:
	हाल V4L2_PIX_FMT_RGB32:
	हाल V4L2_PIX_FMT_BGR32:
		वापस IPUV3_COLORSPACE_RGB;
	शेष:
		वापस IPUV3_COLORSPACE_UNKNOWN;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ipu_pixelक्रमmat_to_colorspace);

पूर्णांक ipu_degrees_to_rot_mode(क्रमागत ipu_rotate_mode *mode, पूर्णांक degrees,
			    bool hflip, bool vflip)
अणु
	u32 r90, vf, hf;

	चयन (degrees) अणु
	हाल 0:
		vf = hf = r90 = 0;
		अवरोध;
	हाल 90:
		vf = hf = 0;
		r90 = 1;
		अवरोध;
	हाल 180:
		vf = hf = 1;
		r90 = 0;
		अवरोध;
	हाल 270:
		vf = hf = r90 = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	hf ^= (u32)hflip;
	vf ^= (u32)vflip;

	*mode = (क्रमागत ipu_rotate_mode)((r90 << 2) | (hf << 1) | vf);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_degrees_to_rot_mode);

पूर्णांक ipu_rot_mode_to_degrees(पूर्णांक *degrees, क्रमागत ipu_rotate_mode mode,
			    bool hflip, bool vflip)
अणु
	u32 r90, vf, hf;

	r90 = ((u32)mode >> 2) & 0x1;
	hf = ((u32)mode >> 1) & 0x1;
	vf = ((u32)mode >> 0) & 0x1;
	hf ^= (u32)hflip;
	vf ^= (u32)vflip;

	चयन ((क्रमागत ipu_rotate_mode)((r90 << 2) | (hf << 1) | vf)) अणु
	हाल IPU_ROTATE_NONE:
		*degrees = 0;
		अवरोध;
	हाल IPU_ROTATE_90_RIGHT:
		*degrees = 90;
		अवरोध;
	हाल IPU_ROTATE_180:
		*degrees = 180;
		अवरोध;
	हाल IPU_ROTATE_90_LEFT:
		*degrees = 270;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_rot_mode_to_degrees);

काष्ठा ipuv3_channel *ipu_idmac_get(काष्ठा ipu_soc *ipu, अचिन्हित num)
अणु
	काष्ठा ipuv3_channel *channel;

	dev_dbg(ipu->dev, "%s %d\n", __func__, num);

	अगर (num > 63)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&ipu->channel_lock);

	list_क्रम_each_entry(channel, &ipu->channels, list) अणु
		अगर (channel->num == num) अणु
			channel = ERR_PTR(-EBUSY);
			जाओ out;
		पूर्ण
	पूर्ण

	channel = kzalloc(माप(*channel), GFP_KERNEL);
	अगर (!channel) अणु
		channel = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	channel->num = num;
	channel->ipu = ipu;
	list_add(&channel->list, &ipu->channels);

out:
	mutex_unlock(&ipu->channel_lock);

	वापस channel;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_get);

व्योम ipu_idmac_put(काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;

	dev_dbg(ipu->dev, "%s %d\n", __func__, channel->num);

	mutex_lock(&ipu->channel_lock);

	list_del(&channel->list);
	kमुक्त(channel);

	mutex_unlock(&ipu->channel_lock);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_put);

#घोषणा idma_mask(ch)			(1 << ((ch) & 0x1f))

/*
 * This is an unकरोcumented feature, a ग_लिखो one to a channel bit in
 * IPU_CHA_CUR_BUF and IPU_CHA_TRIPLE_CUR_BUF will reset the channel's
 * पूर्णांकernal current buffer poपूर्णांकer so that transfers start from buffer
 * 0 on the next channel enable (that's the theory anyway, the imx6 TRM
 * only says these are पढ़ो-only रेजिस्टरs). This operation is required
 * क्रम channel linking to work correctly, क्रम instance video capture
 * pipelines that carry out image rotations will fail after the first
 * streaming unless this function is called क्रम each channel beक्रमe
 * re-enabling the channels.
 */
अटल व्योम __ipu_idmac_reset_current_buffer(काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित पूर्णांक chno = channel->num;

	ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_CUR_BUF(chno));
पूर्ण

व्योम ipu_idmac_set_द्विगुन_buffer(काष्ठा ipuv3_channel *channel,
		bool द्विगुनbuffer)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&ipu->lock, flags);

	reg = ipu_cm_पढ़ो(ipu, IPU_CHA_DB_MODE_SEL(channel->num));
	अगर (द्विगुनbuffer)
		reg |= idma_mask(channel->num);
	अन्यथा
		reg &= ~idma_mask(channel->num);
	ipu_cm_ग_लिखो(ipu, reg, IPU_CHA_DB_MODE_SEL(channel->num));

	__ipu_idmac_reset_current_buffer(channel);

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_set_द्विगुन_buffer);

अटल स्थिर काष्ठा अणु
	पूर्णांक chnum;
	u32 reg;
	पूर्णांक shअगरt;
पूर्ण idmac_lock_en_info[] = अणु
	अणु .chnum =  5, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt =  0, पूर्ण,
	अणु .chnum = 11, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt =  2, पूर्ण,
	अणु .chnum = 12, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt =  4, पूर्ण,
	अणु .chnum = 14, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt =  6, पूर्ण,
	अणु .chnum = 15, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt =  8, पूर्ण,
	अणु .chnum = 20, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 10, पूर्ण,
	अणु .chnum = 21, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 12, पूर्ण,
	अणु .chnum = 22, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 14, पूर्ण,
	अणु .chnum = 23, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 16, पूर्ण,
	अणु .chnum = 27, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 18, पूर्ण,
	अणु .chnum = 28, .reg = IDMAC_CH_LOCK_EN_1, .shअगरt = 20, पूर्ण,
	अणु .chnum = 45, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt =  0, पूर्ण,
	अणु .chnum = 46, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt =  2, पूर्ण,
	अणु .chnum = 47, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt =  4, पूर्ण,
	अणु .chnum = 48, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt =  6, पूर्ण,
	अणु .chnum = 49, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt =  8, पूर्ण,
	अणु .chnum = 50, .reg = IDMAC_CH_LOCK_EN_2, .shअगरt = 10, पूर्ण,
पूर्ण;

पूर्णांक ipu_idmac_lock_enable(काष्ठा ipuv3_channel *channel, पूर्णांक num_bursts)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित दीर्घ flags;
	u32 bursts, regval;
	पूर्णांक i;

	चयन (num_bursts) अणु
	हाल 0:
	हाल 1:
		bursts = 0x00; /* locking disabled */
		अवरोध;
	हाल 2:
		bursts = 0x01;
		अवरोध;
	हाल 4:
		bursts = 0x02;
		अवरोध;
	हाल 8:
		bursts = 0x03;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * IPUv3EX / i.MX51 has a dअगरferent रेजिस्टर layout, and on IPUv3M /
	 * i.MX53 channel arbitration locking करोesn't seem to work properly.
	 * Allow enabling the lock feature on IPUv3H / i.MX6 only.
	 */
	अगर (bursts && ipu->ipu_type != IPUV3H)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(idmac_lock_en_info); i++) अणु
		अगर (channel->num == idmac_lock_en_info[i].chnum)
			अवरोध;
	पूर्ण
	अगर (i >= ARRAY_SIZE(idmac_lock_en_info))
		वापस -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	regval = ipu_idmac_पढ़ो(ipu, idmac_lock_en_info[i].reg);
	regval &= ~(0x03 << idmac_lock_en_info[i].shअगरt);
	regval |= (bursts << idmac_lock_en_info[i].shअगरt);
	ipu_idmac_ग_लिखो(ipu, regval, idmac_lock_en_info[i].reg);

	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_lock_enable);

पूर्णांक ipu_module_enable(काष्ठा ipu_soc *ipu, u32 mask)
अणु
	अचिन्हित दीर्घ lock_flags;
	u32 val;

	spin_lock_irqsave(&ipu->lock, lock_flags);

	val = ipu_cm_पढ़ो(ipu, IPU_DISP_GEN);

	अगर (mask & IPU_CONF_DI0_EN)
		val |= IPU_DI0_COUNTER_RELEASE;
	अगर (mask & IPU_CONF_DI1_EN)
		val |= IPU_DI1_COUNTER_RELEASE;

	ipu_cm_ग_लिखो(ipu, val, IPU_DISP_GEN);

	val = ipu_cm_पढ़ो(ipu, IPU_CONF);
	val |= mask;
	ipu_cm_ग_लिखो(ipu, val, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, lock_flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_module_enable);

पूर्णांक ipu_module_disable(काष्ठा ipu_soc *ipu, u32 mask)
अणु
	अचिन्हित दीर्घ lock_flags;
	u32 val;

	spin_lock_irqsave(&ipu->lock, lock_flags);

	val = ipu_cm_पढ़ो(ipu, IPU_CONF);
	val &= ~mask;
	ipu_cm_ग_लिखो(ipu, val, IPU_CONF);

	val = ipu_cm_पढ़ो(ipu, IPU_DISP_GEN);

	अगर (mask & IPU_CONF_DI0_EN)
		val &= ~IPU_DI0_COUNTER_RELEASE;
	अगर (mask & IPU_CONF_DI1_EN)
		val &= ~IPU_DI1_COUNTER_RELEASE;

	ipu_cm_ग_लिखो(ipu, val, IPU_DISP_GEN);

	spin_unlock_irqrestore(&ipu->lock, lock_flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_module_disable);

पूर्णांक ipu_idmac_get_current_buffer(काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित पूर्णांक chno = channel->num;

	वापस (ipu_cm_पढ़ो(ipu, IPU_CHA_CUR_BUF(chno)) & idma_mask(chno)) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_get_current_buffer);

bool ipu_idmac_buffer_is_पढ़ोy(काष्ठा ipuv3_channel *channel, u32 buf_num)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित दीर्घ flags;
	u32 reg = 0;

	spin_lock_irqsave(&ipu->lock, flags);
	चयन (buf_num) अणु
	हाल 0:
		reg = ipu_cm_पढ़ो(ipu, IPU_CHA_BUF0_RDY(channel->num));
		अवरोध;
	हाल 1:
		reg = ipu_cm_पढ़ो(ipu, IPU_CHA_BUF1_RDY(channel->num));
		अवरोध;
	हाल 2:
		reg = ipu_cm_पढ़ो(ipu, IPU_CHA_BUF2_RDY(channel->num));
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस ((reg & idma_mask(channel->num)) != 0);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_buffer_is_पढ़ोy);

व्योम ipu_idmac_select_buffer(काष्ठा ipuv3_channel *channel, u32 buf_num)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित पूर्णांक chno = channel->num;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu->lock, flags);

	/* Mark buffer as पढ़ोy. */
	अगर (buf_num == 0)
		ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_BUF0_RDY(chno));
	अन्यथा
		ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_BUF1_RDY(chno));

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_select_buffer);

व्योम ipu_idmac_clear_buffer(काष्ठा ipuv3_channel *channel, u32 buf_num)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित पूर्णांक chno = channel->num;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu->lock, flags);

	ipu_cm_ग_लिखो(ipu, 0xF0300000, IPU_GPR); /* ग_लिखो one to clear */
	चयन (buf_num) अणु
	हाल 0:
		ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_BUF0_RDY(chno));
		अवरोध;
	हाल 1:
		ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_BUF1_RDY(chno));
		अवरोध;
	हाल 2:
		ipu_cm_ग_लिखो(ipu, idma_mask(chno), IPU_CHA_BUF2_RDY(chno));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ipu_cm_ग_लिखो(ipu, 0x0, IPU_GPR); /* ग_लिखो one to set */

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_clear_buffer);

पूर्णांक ipu_idmac_enable_channel(काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_idmac_पढ़ो(ipu, IDMAC_CHA_EN(channel->num));
	val |= idma_mask(channel->num);
	ipu_idmac_ग_लिखो(ipu, val, IDMAC_CHA_EN(channel->num));

	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_enable_channel);

bool ipu_idmac_channel_busy(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक chno)
अणु
	वापस (ipu_idmac_पढ़ो(ipu, IDMAC_CHA_BUSY(chno)) & idma_mask(chno));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_channel_busy);

पूर्णांक ipu_idmac_रुको_busy(काष्ठा ipuv3_channel *channel, पूर्णांक ms)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(ms);
	जबतक (ipu_idmac_पढ़ो(ipu, IDMAC_CHA_BUSY(channel->num)) &
			idma_mask(channel->num)) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIMEDOUT;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_रुको_busy);

पूर्णांक ipu_idmac_disable_channel(काष्ठा ipuv3_channel *channel)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	u32 val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ipu->lock, flags);

	/* Disable DMA channel(s) */
	val = ipu_idmac_पढ़ो(ipu, IDMAC_CHA_EN(channel->num));
	val &= ~idma_mask(channel->num);
	ipu_idmac_ग_लिखो(ipu, val, IDMAC_CHA_EN(channel->num));

	__ipu_idmac_reset_current_buffer(channel);

	/* Set channel buffers NOT to be पढ़ोy */
	ipu_cm_ग_लिखो(ipu, 0xf0000000, IPU_GPR); /* ग_लिखो one to clear */

	अगर (ipu_cm_पढ़ो(ipu, IPU_CHA_BUF0_RDY(channel->num)) &
			idma_mask(channel->num)) अणु
		ipu_cm_ग_लिखो(ipu, idma_mask(channel->num),
			     IPU_CHA_BUF0_RDY(channel->num));
	पूर्ण

	अगर (ipu_cm_पढ़ो(ipu, IPU_CHA_BUF1_RDY(channel->num)) &
			idma_mask(channel->num)) अणु
		ipu_cm_ग_लिखो(ipu, idma_mask(channel->num),
			     IPU_CHA_BUF1_RDY(channel->num));
	पूर्ण

	ipu_cm_ग_लिखो(ipu, 0x0, IPU_GPR); /* ग_लिखो one to set */

	/* Reset the द्विगुन buffer */
	val = ipu_cm_पढ़ो(ipu, IPU_CHA_DB_MODE_SEL(channel->num));
	val &= ~idma_mask(channel->num);
	ipu_cm_ग_लिखो(ipu, val, IPU_CHA_DB_MODE_SEL(channel->num));

	spin_unlock_irqrestore(&ipu->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_disable_channel);

/*
 * The imx6 rev. D TRM says that enabling the WM feature will increase
 * a channel's priority. Refer to Table 36-8 Calculated priority value.
 * The sub-module that is the sink or source क्रम the channel must enable
 * watermark संकेत क्रम this to take effect (SMFC_WM क्रम instance).
 */
व्योम ipu_idmac_enable_watermark(काष्ठा ipuv3_channel *channel, bool enable)
अणु
	काष्ठा ipu_soc *ipu = channel->ipu;
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_idmac_पढ़ो(ipu, IDMAC_WM_EN(channel->num));
	अगर (enable)
		val |= 1 << (channel->num % 32);
	अन्यथा
		val &= ~(1 << (channel->num % 32));
	ipu_idmac_ग_लिखो(ipu, val, IDMAC_WM_EN(channel->num));

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_enable_watermark);

अटल पूर्णांक ipu_memory_reset(काष्ठा ipu_soc *ipu)
अणु
	अचिन्हित दीर्घ समयout;

	ipu_cm_ग_लिखो(ipu, 0x807FFFFF, IPU_MEM_RST);

	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (ipu_cm_पढ़ो(ipu, IPU_MEM_RST) & 0x80000000) अणु
		अगर (समय_after(jअगरfies, समयout))
			वापस -ETIME;
		cpu_relax();
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set the source mux क्रम the given CSI. Selects either parallel or
 * MIPI CSI2 sources.
 */
व्योम ipu_set_csi_src_mux(काष्ठा ipu_soc *ipu, पूर्णांक csi_id, bool mipi_csi2)
अणु
	अचिन्हित दीर्घ flags;
	u32 val, mask;

	mask = (csi_id == 1) ? IPU_CONF_CSI1_DATA_SOURCE :
		IPU_CONF_CSI0_DATA_SOURCE;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_cm_पढ़ो(ipu, IPU_CONF);
	अगर (mipi_csi2)
		val |= mask;
	अन्यथा
		val &= ~mask;
	ipu_cm_ग_लिखो(ipu, val, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_set_csi_src_mux);

/*
 * Set the source mux क्रम the IC. Selects either CSI[01] or the VDI.
 */
व्योम ipu_set_ic_src_mux(काष्ठा ipu_soc *ipu, पूर्णांक csi_id, bool vdi)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_cm_पढ़ो(ipu, IPU_CONF);
	अगर (vdi)
		val |= IPU_CONF_IC_INPUT;
	अन्यथा
		val &= ~IPU_CONF_IC_INPUT;

	अगर (csi_id == 1)
		val |= IPU_CONF_CSI_SEL;
	अन्यथा
		val &= ~IPU_CONF_CSI_SEL;

	ipu_cm_ग_लिखो(ipu, val, IPU_CONF);

	spin_unlock_irqrestore(&ipu->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_set_ic_src_mux);


/* Frame Synchronization Unit Channel Linking */

काष्ठा fsu_link_reg_info अणु
	पूर्णांक chno;
	u32 reg;
	u32 mask;
	u32 val;
पूर्ण;

काष्ठा fsu_link_info अणु
	काष्ठा fsu_link_reg_info src;
	काष्ठा fsu_link_reg_info sink;
पूर्ण;

अटल स्थिर काष्ठा fsu_link_info fsu_link_info[] = अणु
	अणु
		.src  = अणु IPUV3_CHANNEL_IC_PRP_ENC_MEM, IPU_FS_PROC_FLOW2,
			  FS_PRP_ENC_DEST_SEL_MASK, FS_PRP_ENC_DEST_SEL_IRT_ENC पूर्ण,
		.sink = अणु IPUV3_CHANNEL_MEM_ROT_ENC, IPU_FS_PROC_FLOW1,
			  FS_PRPENC_ROT_SRC_SEL_MASK, FS_PRPENC_ROT_SRC_SEL_ENC पूर्ण,
	पूर्ण, अणु
		.src =  अणु IPUV3_CHANNEL_IC_PRP_VF_MEM, IPU_FS_PROC_FLOW2,
			  FS_PRPVF_DEST_SEL_MASK, FS_PRPVF_DEST_SEL_IRT_VF पूर्ण,
		.sink = अणु IPUV3_CHANNEL_MEM_ROT_VF, IPU_FS_PROC_FLOW1,
			  FS_PRPVF_ROT_SRC_SEL_MASK, FS_PRPVF_ROT_SRC_SEL_VF पूर्ण,
	पूर्ण, अणु
		.src =  अणु IPUV3_CHANNEL_IC_PP_MEM, IPU_FS_PROC_FLOW2,
			  FS_PP_DEST_SEL_MASK, FS_PP_DEST_SEL_IRT_PP पूर्ण,
		.sink = अणु IPUV3_CHANNEL_MEM_ROT_PP, IPU_FS_PROC_FLOW1,
			  FS_PP_ROT_SRC_SEL_MASK, FS_PP_ROT_SRC_SEL_PP पूर्ण,
	पूर्ण, अणु
		.src =  अणु IPUV3_CHANNEL_CSI_सूचीECT, 0 पूर्ण,
		.sink = अणु IPUV3_CHANNEL_CSI_VDI_PREV, IPU_FS_PROC_FLOW1,
			  FS_VDI_SRC_SEL_MASK, FS_VDI_SRC_SEL_CSI_सूचीECT पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा fsu_link_info *find_fsu_link_info(पूर्णांक src, पूर्णांक sink)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fsu_link_info); i++) अणु
		अगर (src == fsu_link_info[i].src.chno &&
		    sink == fsu_link_info[i].sink.chno)
			वापस &fsu_link_info[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Links a source channel to a sink channel in the FSU.
 */
पूर्णांक ipu_fsu_link(काष्ठा ipu_soc *ipu, पूर्णांक src_ch, पूर्णांक sink_ch)
अणु
	स्थिर काष्ठा fsu_link_info *link;
	u32 src_reg, sink_reg;
	अचिन्हित दीर्घ flags;

	link = find_fsu_link_info(src_ch, sink_ch);
	अगर (!link)
		वापस -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	अगर (link->src.mask) अणु
		src_reg = ipu_cm_पढ़ो(ipu, link->src.reg);
		src_reg &= ~link->src.mask;
		src_reg |= link->src.val;
		ipu_cm_ग_लिखो(ipu, src_reg, link->src.reg);
	पूर्ण

	अगर (link->sink.mask) अणु
		sink_reg = ipu_cm_पढ़ो(ipu, link->sink.reg);
		sink_reg &= ~link->sink.mask;
		sink_reg |= link->sink.val;
		ipu_cm_ग_लिखो(ipu, sink_reg, link->sink.reg);
	पूर्ण

	spin_unlock_irqrestore(&ipu->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_fsu_link);

/*
 * Unlinks source and sink channels in the FSU.
 */
पूर्णांक ipu_fsu_unlink(काष्ठा ipu_soc *ipu, पूर्णांक src_ch, पूर्णांक sink_ch)
अणु
	स्थिर काष्ठा fsu_link_info *link;
	u32 src_reg, sink_reg;
	अचिन्हित दीर्घ flags;

	link = find_fsu_link_info(src_ch, sink_ch);
	अगर (!link)
		वापस -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	अगर (link->src.mask) अणु
		src_reg = ipu_cm_पढ़ो(ipu, link->src.reg);
		src_reg &= ~link->src.mask;
		ipu_cm_ग_लिखो(ipu, src_reg, link->src.reg);
	पूर्ण

	अगर (link->sink.mask) अणु
		sink_reg = ipu_cm_पढ़ो(ipu, link->sink.reg);
		sink_reg &= ~link->sink.mask;
		ipu_cm_ग_लिखो(ipu, sink_reg, link->sink.reg);
	पूर्ण

	spin_unlock_irqrestore(&ipu->lock, flags);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_fsu_unlink);

/* Link IDMAC channels in the FSU */
पूर्णांक ipu_idmac_link(काष्ठा ipuv3_channel *src, काष्ठा ipuv3_channel *sink)
अणु
	वापस ipu_fsu_link(src->ipu, src->num, sink->num);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_link);

/* Unlink IDMAC channels in the FSU */
पूर्णांक ipu_idmac_unlink(काष्ठा ipuv3_channel *src, काष्ठा ipuv3_channel *sink)
अणु
	वापस ipu_fsu_unlink(src->ipu, src->num, sink->num);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_unlink);

काष्ठा ipu_devtype अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ cm_ofs;
	अचिन्हित दीर्घ cpmem_ofs;
	अचिन्हित दीर्घ srm_ofs;
	अचिन्हित दीर्घ tpm_ofs;
	अचिन्हित दीर्घ csi0_ofs;
	अचिन्हित दीर्घ csi1_ofs;
	अचिन्हित दीर्घ ic_ofs;
	अचिन्हित दीर्घ disp0_ofs;
	अचिन्हित दीर्घ disp1_ofs;
	अचिन्हित दीर्घ dc_पंचांगpl_ofs;
	अचिन्हित दीर्घ vdi_ofs;
	क्रमागत ipuv3_type type;
पूर्ण;

अटल काष्ठा ipu_devtype ipu_type_imx51 = अणु
	.name = "IPUv3EX",
	.cm_ofs = 0x1e000000,
	.cpmem_ofs = 0x1f000000,
	.srm_ofs = 0x1f040000,
	.tpm_ofs = 0x1f060000,
	.csi0_ofs = 0x1e030000,
	.csi1_ofs = 0x1e038000,
	.ic_ofs = 0x1e020000,
	.disp0_ofs = 0x1e040000,
	.disp1_ofs = 0x1e048000,
	.dc_पंचांगpl_ofs = 0x1f080000,
	.vdi_ofs = 0x1e068000,
	.type = IPUV3EX,
पूर्ण;

अटल काष्ठा ipu_devtype ipu_type_imx53 = अणु
	.name = "IPUv3M",
	.cm_ofs = 0x06000000,
	.cpmem_ofs = 0x07000000,
	.srm_ofs = 0x07040000,
	.tpm_ofs = 0x07060000,
	.csi0_ofs = 0x06030000,
	.csi1_ofs = 0x06038000,
	.ic_ofs = 0x06020000,
	.disp0_ofs = 0x06040000,
	.disp1_ofs = 0x06048000,
	.dc_पंचांगpl_ofs = 0x07080000,
	.vdi_ofs = 0x06068000,
	.type = IPUV3M,
पूर्ण;

अटल काष्ठा ipu_devtype ipu_type_imx6q = अणु
	.name = "IPUv3H",
	.cm_ofs = 0x00200000,
	.cpmem_ofs = 0x00300000,
	.srm_ofs = 0x00340000,
	.tpm_ofs = 0x00360000,
	.csi0_ofs = 0x00230000,
	.csi1_ofs = 0x00238000,
	.ic_ofs = 0x00220000,
	.disp0_ofs = 0x00240000,
	.disp1_ofs = 0x00248000,
	.dc_पंचांगpl_ofs = 0x00380000,
	.vdi_ofs = 0x00268000,
	.type = IPUV3H,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_ipu_dt_ids[] = अणु
	अणु .compatible = "fsl,imx51-ipu", .data = &ipu_type_imx51, पूर्ण,
	अणु .compatible = "fsl,imx53-ipu", .data = &ipu_type_imx53, पूर्ण,
	अणु .compatible = "fsl,imx6q-ipu", .data = &ipu_type_imx6q, पूर्ण,
	अणु .compatible = "fsl,imx6qp-ipu", .data = &ipu_type_imx6q, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_ipu_dt_ids);

अटल पूर्णांक ipu_submodules_init(काष्ठा ipu_soc *ipu,
		काष्ठा platक्रमm_device *pdev, अचिन्हित दीर्घ ipu_base,
		काष्ठा clk *ipu_clk)
अणु
	अक्षर *unit;
	पूर्णांक ret;
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा ipu_devtype *devtype = ipu->devtype;

	ret = ipu_cpmem_init(ipu, dev, ipu_base + devtype->cpmem_ofs);
	अगर (ret) अणु
		unit = "cpmem";
		जाओ err_cpmem;
	पूर्ण

	ret = ipu_csi_init(ipu, dev, 0, ipu_base + devtype->csi0_ofs,
			   IPU_CONF_CSI0_EN, ipu_clk);
	अगर (ret) अणु
		unit = "csi0";
		जाओ err_csi_0;
	पूर्ण

	ret = ipu_csi_init(ipu, dev, 1, ipu_base + devtype->csi1_ofs,
			   IPU_CONF_CSI1_EN, ipu_clk);
	अगर (ret) अणु
		unit = "csi1";
		जाओ err_csi_1;
	पूर्ण

	ret = ipu_ic_init(ipu, dev,
			  ipu_base + devtype->ic_ofs,
			  ipu_base + devtype->tpm_ofs);
	अगर (ret) अणु
		unit = "ic";
		जाओ err_ic;
	पूर्ण

	ret = ipu_vdi_init(ipu, dev, ipu_base + devtype->vdi_ofs,
			   IPU_CONF_VDI_EN | IPU_CONF_ISP_EN |
			   IPU_CONF_IC_INPUT);
	अगर (ret) अणु
		unit = "vdi";
		जाओ err_vdi;
	पूर्ण

	ret = ipu_image_convert_init(ipu, dev);
	अगर (ret) अणु
		unit = "image_convert";
		जाओ err_image_convert;
	पूर्ण

	ret = ipu_di_init(ipu, dev, 0, ipu_base + devtype->disp0_ofs,
			  IPU_CONF_DI0_EN, ipu_clk);
	अगर (ret) अणु
		unit = "di0";
		जाओ err_di_0;
	पूर्ण

	ret = ipu_di_init(ipu, dev, 1, ipu_base + devtype->disp1_ofs,
			IPU_CONF_DI1_EN, ipu_clk);
	अगर (ret) अणु
		unit = "di1";
		जाओ err_di_1;
	पूर्ण

	ret = ipu_dc_init(ipu, dev, ipu_base + devtype->cm_ofs +
			IPU_CM_DC_REG_OFS, ipu_base + devtype->dc_पंचांगpl_ofs);
	अगर (ret) अणु
		unit = "dc_template";
		जाओ err_dc;
	पूर्ण

	ret = ipu_dmfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_DMFC_REG_OFS, ipu_clk);
	अगर (ret) अणु
		unit = "dmfc";
		जाओ err_dmfc;
	पूर्ण

	ret = ipu_dp_init(ipu, dev, ipu_base + devtype->srm_ofs);
	अगर (ret) अणु
		unit = "dp";
		जाओ err_dp;
	पूर्ण

	ret = ipu_smfc_init(ipu, dev, ipu_base +
			devtype->cm_ofs + IPU_CM_SMFC_REG_OFS);
	अगर (ret) अणु
		unit = "smfc";
		जाओ err_smfc;
	पूर्ण

	वापस 0;

err_smfc:
	ipu_dp_निकास(ipu);
err_dp:
	ipu_dmfc_निकास(ipu);
err_dmfc:
	ipu_dc_निकास(ipu);
err_dc:
	ipu_di_निकास(ipu, 1);
err_di_1:
	ipu_di_निकास(ipu, 0);
err_di_0:
	ipu_image_convert_निकास(ipu);
err_image_convert:
	ipu_vdi_निकास(ipu);
err_vdi:
	ipu_ic_निकास(ipu);
err_ic:
	ipu_csi_निकास(ipu, 1);
err_csi_1:
	ipu_csi_निकास(ipu, 0);
err_csi_0:
	ipu_cpmem_निकास(ipu);
err_cpmem:
	dev_err(&pdev->dev, "init %s failed with %d\n", unit, ret);
	वापस ret;
पूर्ण

अटल व्योम ipu_irq_handle(काष्ठा ipu_soc *ipu, स्थिर पूर्णांक *regs, पूर्णांक num_regs)
अणु
	अचिन्हित दीर्घ status;
	पूर्णांक i, bit, irq;

	क्रम (i = 0; i < num_regs; i++) अणु

		status = ipu_cm_पढ़ो(ipu, IPU_INT_STAT(regs[i]));
		status &= ipu_cm_पढ़ो(ipu, IPU_INT_CTRL(regs[i]));

		क्रम_each_set_bit(bit, &status, 32) अणु
			irq = irq_linear_revmap(ipu->करोमुख्य,
						regs[i] * 32 + bit);
			अगर (irq)
				generic_handle_irq(irq);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ipu_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ipu_soc *ipu = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अटल स्थिर पूर्णांक पूर्णांक_reg[] = अणु 0, 1, 2, 3, 10, 11, 12, 13, 14पूर्ण;

	chained_irq_enter(chip, desc);

	ipu_irq_handle(ipu, पूर्णांक_reg, ARRAY_SIZE(पूर्णांक_reg));

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम ipu_err_irq_handler(काष्ठा irq_desc *desc)
अणु
	काष्ठा ipu_soc *ipu = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	अटल स्थिर पूर्णांक पूर्णांक_reg[] = अणु 4, 5, 8, 9पूर्ण;

	chained_irq_enter(chip, desc);

	ipu_irq_handle(ipu, पूर्णांक_reg, ARRAY_SIZE(पूर्णांक_reg));

	chained_irq_निकास(chip, desc);
पूर्ण

पूर्णांक ipu_map_irq(काष्ठा ipu_soc *ipu, पूर्णांक irq)
अणु
	पूर्णांक virq;

	virq = irq_linear_revmap(ipu->करोमुख्य, irq);
	अगर (!virq)
		virq = irq_create_mapping(ipu->करोमुख्य, irq);

	वापस virq;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_map_irq);

पूर्णांक ipu_idmac_channel_irq(काष्ठा ipu_soc *ipu, काष्ठा ipuv3_channel *channel,
		क्रमागत ipu_channel_irq irq_type)
अणु
	वापस ipu_map_irq(ipu, irq_type + channel->num);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_idmac_channel_irq);

अटल व्योम ipu_submodules_निकास(काष्ठा ipu_soc *ipu)
अणु
	ipu_smfc_निकास(ipu);
	ipu_dp_निकास(ipu);
	ipu_dmfc_निकास(ipu);
	ipu_dc_निकास(ipu);
	ipu_di_निकास(ipu, 1);
	ipu_di_निकास(ipu, 0);
	ipu_image_convert_निकास(ipu);
	ipu_vdi_निकास(ipu);
	ipu_ic_निकास(ipu);
	ipu_csi_निकास(ipu, 1);
	ipu_csi_निकास(ipu, 0);
	ipu_cpmem_निकास(ipu);
पूर्ण

अटल पूर्णांक platक्रमm_हटाओ_devices_fn(काष्ठा device *dev, व्योम *unused)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);

	platक्रमm_device_unरेजिस्टर(pdev);

	वापस 0;
पूर्ण

अटल व्योम platक्रमm_device_unरेजिस्टर_children(काष्ठा platक्रमm_device *pdev)
अणु
	device_क्रम_each_child(&pdev->dev, शून्य, platक्रमm_हटाओ_devices_fn);
पूर्ण

काष्ठा ipu_platक्रमm_reg अणु
	काष्ठा ipu_client_platक्रमmdata pdata;
	स्थिर अक्षर *name;
पूर्ण;

/* These must be in the order of the corresponding device tree port nodes */
अटल काष्ठा ipu_platक्रमm_reg client_reg[] = अणु
	अणु
		.pdata = अणु
			.csi = 0,
			.dma[0] = IPUV3_CHANNEL_CSI0,
			.dma[1] = -EINVAL,
		पूर्ण,
		.name = "imx-ipuv3-csi",
	पूर्ण, अणु
		.pdata = अणु
			.csi = 1,
			.dma[0] = IPUV3_CHANNEL_CSI1,
			.dma[1] = -EINVAL,
		पूर्ण,
		.name = "imx-ipuv3-csi",
	पूर्ण, अणु
		.pdata = अणु
			.di = 0,
			.dc = 5,
			.dp = IPU_DP_FLOW_SYNC_BG,
			.dma[0] = IPUV3_CHANNEL_MEM_BG_SYNC,
			.dma[1] = IPUV3_CHANNEL_MEM_FG_SYNC,
		पूर्ण,
		.name = "imx-ipuv3-crtc",
	पूर्ण, अणु
		.pdata = अणु
			.di = 1,
			.dc = 1,
			.dp = -EINVAL,
			.dma[0] = IPUV3_CHANNEL_MEM_DC_SYNC,
			.dma[1] = -EINVAL,
		पूर्ण,
		.name = "imx-ipuv3-crtc",
	पूर्ण,
पूर्ण;

अटल DEFINE_MUTEX(ipu_client_id_mutex);
अटल पूर्णांक ipu_client_id;

अटल पूर्णांक ipu_add_client_devices(काष्ठा ipu_soc *ipu, अचिन्हित दीर्घ ipu_base)
अणु
	काष्ठा device *dev = ipu->dev;
	अचिन्हित i;
	पूर्णांक id, ret;

	mutex_lock(&ipu_client_id_mutex);
	id = ipu_client_id;
	ipu_client_id += ARRAY_SIZE(client_reg);
	mutex_unlock(&ipu_client_id_mutex);

	क्रम (i = 0; i < ARRAY_SIZE(client_reg); i++) अणु
		काष्ठा ipu_platक्रमm_reg *reg = &client_reg[i];
		काष्ठा platक्रमm_device *pdev;
		काष्ठा device_node *of_node;

		/* Associate subdevice with the corresponding port node */
		of_node = of_graph_get_port_by_id(dev->of_node, i);
		अगर (!of_node) अणु
			dev_info(dev,
				 "no port@%d node in %pOF, not using %s%d\n",
				 i, dev->of_node,
				 (i / 2) ? "DI" : "CSI", i % 2);
			जारी;
		पूर्ण

		pdev = platक्रमm_device_alloc(reg->name, id++);
		अगर (!pdev) अणु
			ret = -ENOMEM;
			जाओ err_रेजिस्टर;
		पूर्ण

		pdev->dev.parent = dev;

		reg->pdata.of_node = of_node;
		ret = platक्रमm_device_add_data(pdev, &reg->pdata,
					       माप(reg->pdata));
		अगर (!ret)
			ret = platक्रमm_device_add(pdev);
		अगर (ret) अणु
			platक्रमm_device_put(pdev);
			जाओ err_रेजिस्टर;
		पूर्ण
	पूर्ण

	वापस 0;

err_रेजिस्टर:
	platक्रमm_device_unरेजिस्टर_children(to_platक्रमm_device(dev));

	वापस ret;
पूर्ण


अटल पूर्णांक ipu_irq_init(काष्ठा ipu_soc *ipu)
अणु
	काष्ठा irq_chip_generic *gc;
	काष्ठा irq_chip_type *ct;
	अचिन्हित दीर्घ unused[IPU_NUM_IRQS / 32] = अणु
		0x400100d0, 0xffe000fd,
		0x400100d0, 0xffe000fd,
		0x400100d0, 0xffe000fd,
		0x4077ffff, 0xffe7e1fd,
		0x23fffffe, 0x8880fff0,
		0xf98fe7d0, 0xfff81fff,
		0x400100d0, 0xffe000fd,
		0x00000000,
	पूर्ण;
	पूर्णांक ret, i;

	ipu->करोमुख्य = irq_करोमुख्य_add_linear(ipu->dev->of_node, IPU_NUM_IRQS,
					    &irq_generic_chip_ops, ipu);
	अगर (!ipu->करोमुख्य) अणु
		dev_err(ipu->dev, "failed to add irq domain\n");
		वापस -ENODEV;
	पूर्ण

	ret = irq_alloc_करोमुख्य_generic_chips(ipu->करोमुख्य, 32, 1, "IPU",
					     handle_level_irq, 0, 0, 0);
	अगर (ret < 0) अणु
		dev_err(ipu->dev, "failed to alloc generic irq chips\n");
		irq_करोमुख्य_हटाओ(ipu->करोमुख्य);
		वापस ret;
	पूर्ण

	/* Mask and clear all पूर्णांकerrupts */
	क्रम (i = 0; i < IPU_NUM_IRQS; i += 32) अणु
		ipu_cm_ग_लिखो(ipu, 0, IPU_INT_CTRL(i / 32));
		ipu_cm_ग_लिखो(ipu, ~unused[i / 32], IPU_INT_STAT(i / 32));
	पूर्ण

	क्रम (i = 0; i < IPU_NUM_IRQS; i += 32) अणु
		gc = irq_get_करोमुख्य_generic_chip(ipu->करोमुख्य, i);
		gc->reg_base = ipu->cm_reg;
		gc->unused = unused[i / 32];
		ct = gc->chip_types;
		ct->chip.irq_ack = irq_gc_ack_set_bit;
		ct->chip.irq_mask = irq_gc_mask_clr_bit;
		ct->chip.irq_unmask = irq_gc_mask_set_bit;
		ct->regs.ack = IPU_INT_STAT(i / 32);
		ct->regs.mask = IPU_INT_CTRL(i / 32);
	पूर्ण

	irq_set_chained_handler_and_data(ipu->irq_sync, ipu_irq_handler, ipu);
	irq_set_chained_handler_and_data(ipu->irq_err, ipu_err_irq_handler,
					 ipu);

	वापस 0;
पूर्ण

अटल व्योम ipu_irq_निकास(काष्ठा ipu_soc *ipu)
अणु
	पूर्णांक i, irq;

	irq_set_chained_handler_and_data(ipu->irq_err, शून्य, शून्य);
	irq_set_chained_handler_and_data(ipu->irq_sync, शून्य, शून्य);

	/* TODO: हटाओ irq_करोमुख्य_generic_chips */

	क्रम (i = 0; i < IPU_NUM_IRQS; i++) अणु
		irq = irq_linear_revmap(ipu->करोमुख्य, i);
		अगर (irq)
			irq_dispose_mapping(irq);
	पूर्ण

	irq_करोमुख्य_हटाओ(ipu->करोमुख्य);
पूर्ण

व्योम ipu_dump(काष्ठा ipu_soc *ipu)
अणु
	पूर्णांक i;

	dev_dbg(ipu->dev, "IPU_CONF = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_CONF));
	dev_dbg(ipu->dev, "IDMAC_CONF = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_CONF));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN1 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_CHA_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_EN2 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_CHA_EN(32)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PRI1 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_CHA_PRI(0)));
	dev_dbg(ipu->dev, "IDMAC_CHA_PRI2 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_CHA_PRI(32)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN1 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_BAND_EN(0)));
	dev_dbg(ipu->dev, "IDMAC_BAND_EN2 = \t0x%08X\n",
		ipu_idmac_पढ़ो(ipu, IDMAC_BAND_EN(32)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEL0 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_CHA_DB_MODE_SEL(0)));
	dev_dbg(ipu->dev, "IPU_CHA_DB_MODE_SEL1 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_CHA_DB_MODE_SEL(32)));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW1 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_FS_PROC_FLOW1));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW2 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_FS_PROC_FLOW2));
	dev_dbg(ipu->dev, "IPU_FS_PROC_FLOW3 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_FS_PROC_FLOW3));
	dev_dbg(ipu->dev, "IPU_FS_DISP_FLOW1 = \t0x%08X\n",
		ipu_cm_पढ़ो(ipu, IPU_FS_DISP_FLOW1));
	क्रम (i = 0; i < 15; i++)
		dev_dbg(ipu->dev, "IPU_INT_CTRL(%d) = \t%08X\n", i,
			ipu_cm_पढ़ो(ipu, IPU_INT_CTRL(i)));
पूर्ण
EXPORT_SYMBOL_GPL(ipu_dump);

अटल पूर्णांक ipu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ipu_soc *ipu;
	काष्ठा resource *res;
	अचिन्हित दीर्घ ipu_base;
	पूर्णांक ret, irq_sync, irq_err;
	स्थिर काष्ठा ipu_devtype *devtype;

	devtype = of_device_get_match_data(&pdev->dev);
	अगर (!devtype)
		वापस -EINVAL;

	irq_sync = platक्रमm_get_irq(pdev, 0);
	irq_err = platक्रमm_get_irq(pdev, 1);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	dev_dbg(&pdev->dev, "irq_sync: %d irq_err: %d\n",
			irq_sync, irq_err);

	अगर (!res || irq_sync < 0 || irq_err < 0)
		वापस -ENODEV;

	ipu_base = res->start;

	ipu = devm_kzalloc(&pdev->dev, माप(*ipu), GFP_KERNEL);
	अगर (!ipu)
		वापस -ENODEV;

	ipu->id = of_alias_get_id(np, "ipu");
	अगर (ipu->id < 0)
		ipu->id = 0;

	अगर (of_device_is_compatible(np, "fsl,imx6qp-ipu") &&
	    IS_ENABLED(CONFIG_DRM)) अणु
		ipu->prg_priv = ipu_prg_lookup_by_phandle(&pdev->dev,
							  "fsl,prg", ipu->id);
		अगर (!ipu->prg_priv)
			वापस -EPROBE_DEFER;
	पूर्ण

	ipu->devtype = devtype;
	ipu->ipu_type = devtype->type;

	spin_lock_init(&ipu->lock);
	mutex_init(&ipu->channel_lock);
	INIT_LIST_HEAD(&ipu->channels);

	dev_dbg(&pdev->dev, "cm_reg:   0x%08lx\n",
			ipu_base + devtype->cm_ofs);
	dev_dbg(&pdev->dev, "idmac:    0x%08lx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_IDMAC_REG_OFS);
	dev_dbg(&pdev->dev, "cpmem:    0x%08lx\n",
			ipu_base + devtype->cpmem_ofs);
	dev_dbg(&pdev->dev, "csi0:    0x%08lx\n",
			ipu_base + devtype->csi0_ofs);
	dev_dbg(&pdev->dev, "csi1:    0x%08lx\n",
			ipu_base + devtype->csi1_ofs);
	dev_dbg(&pdev->dev, "ic:      0x%08lx\n",
			ipu_base + devtype->ic_ofs);
	dev_dbg(&pdev->dev, "disp0:    0x%08lx\n",
			ipu_base + devtype->disp0_ofs);
	dev_dbg(&pdev->dev, "disp1:    0x%08lx\n",
			ipu_base + devtype->disp1_ofs);
	dev_dbg(&pdev->dev, "srm:      0x%08lx\n",
			ipu_base + devtype->srm_ofs);
	dev_dbg(&pdev->dev, "tpm:      0x%08lx\n",
			ipu_base + devtype->tpm_ofs);
	dev_dbg(&pdev->dev, "dc:       0x%08lx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_DC_REG_OFS);
	dev_dbg(&pdev->dev, "ic:       0x%08lx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_IC_REG_OFS);
	dev_dbg(&pdev->dev, "dmfc:     0x%08lx\n",
			ipu_base + devtype->cm_ofs + IPU_CM_DMFC_REG_OFS);
	dev_dbg(&pdev->dev, "vdi:      0x%08lx\n",
			ipu_base + devtype->vdi_ofs);

	ipu->cm_reg = devm_ioremap(&pdev->dev,
			ipu_base + devtype->cm_ofs, PAGE_SIZE);
	ipu->idmac_reg = devm_ioremap(&pdev->dev,
			ipu_base + devtype->cm_ofs + IPU_CM_IDMAC_REG_OFS,
			PAGE_SIZE);

	अगर (!ipu->cm_reg || !ipu->idmac_reg)
		वापस -ENOMEM;

	ipu->clk = devm_clk_get(&pdev->dev, "bus");
	अगर (IS_ERR(ipu->clk)) अणु
		ret = PTR_ERR(ipu->clk);
		dev_err(&pdev->dev, "clk_get failed with %d", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, ipu);

	ret = clk_prepare_enable(ipu->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "clk_prepare_enable failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ipu->dev = &pdev->dev;
	ipu->irq_sync = irq_sync;
	ipu->irq_err = irq_err;

	ret = device_reset(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to reset: %d\n", ret);
		जाओ out_failed_reset;
	पूर्ण
	ret = ipu_memory_reset(ipu);
	अगर (ret)
		जाओ out_failed_reset;

	ret = ipu_irq_init(ipu);
	अगर (ret)
		जाओ out_failed_irq;

	/* Set MCU_T to भागide MCU access winकरोw पूर्णांकo 2 */
	ipu_cm_ग_लिखो(ipu, 0x00400000L | (IPU_MCU_T_DEFAULT << 18),
			IPU_DISP_GEN);

	ret = ipu_submodules_init(ipu, pdev, ipu_base, ipu->clk);
	अगर (ret)
		जाओ failed_submodules_init;

	ret = ipu_add_client_devices(ipu, ipu_base);
	अगर (ret) अणु
		dev_err(&pdev->dev, "adding client devices failed with %d\n",
				ret);
		जाओ failed_add_clients;
	पूर्ण

	dev_info(&pdev->dev, "%s probed\n", devtype->name);

	वापस 0;

failed_add_clients:
	ipu_submodules_निकास(ipu);
failed_submodules_init:
	ipu_irq_निकास(ipu);
out_failed_irq:
out_failed_reset:
	clk_disable_unprepare(ipu->clk);
	वापस ret;
पूर्ण

अटल पूर्णांक ipu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ipu_soc *ipu = platक्रमm_get_drvdata(pdev);

	platक्रमm_device_unरेजिस्टर_children(pdev);
	ipu_submodules_निकास(ipu);
	ipu_irq_निकास(ipu);

	clk_disable_unprepare(ipu->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imx_ipu_driver = अणु
	.driver = अणु
		.name = "imx-ipuv3",
		.of_match_table = imx_ipu_dt_ids,
	पूर्ण,
	.probe = ipu_probe,
	.हटाओ = ipu_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_driver * स्थिर drivers[] = अणु
#अगर IS_ENABLED(CONFIG_DRM)
	&ipu_pre_drv,
	&ipu_prg_drv,
#पूर्ण_अगर
	&imx_ipu_driver,
पूर्ण;

अटल पूर्णांक __init imx_ipu_init(व्योम)
अणु
	वापस platक्रमm_रेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_init(imx_ipu_init);

अटल व्योम __निकास imx_ipu_निकास(व्योम)
अणु
	platक्रमm_unरेजिस्टर_drivers(drivers, ARRAY_SIZE(drivers));
पूर्ण
module_निकास(imx_ipu_निकास);

MODULE_ALIAS("platform:imx-ipuv3");
MODULE_DESCRIPTION("i.MX IPU v3 driver");
MODULE_AUTHOR("Sascha Hauer <s.hauer@pengutronix.de>");
MODULE_LICENSE("GPL");
