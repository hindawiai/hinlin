<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Low-level I/O functions.
 *
 * Copyright (c) 2017-2020, Silicon Laboratories, Inc.
 * Copyright (c) 2010, ST-Ericsson
 */
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "hwio.h"
#समावेश "wfx.h"
#समावेश "bus.h"
#समावेश "traces.h"

/*
 * Internal helpers.
 *
 * About CONFIG_VMAP_STACK:
 * When CONFIG_VMAP_STACK is enabled, it is not possible to run DMA on stack
 * allocated data. Functions below that work with रेजिस्टरs (aka functions
 * ending with "32") स्वतःmatically पुनः_स्मृतिate buffers with kदो_स्मृति. However,
 * functions that work with arbitrary length buffers let's caller to handle
 * memory location. In करोubt, enable CONFIG_DEBUG_SG to detect badly located
 * buffer.
 */

अटल पूर्णांक पढ़ो32(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 *val)
अणु
	पूर्णांक ret;
	__le32 *पंचांगp = kदो_स्मृति(माप(u32), GFP_KERNEL);

	*val = ~0; // Never वापस undefined value
	अगर (!पंचांगp)
		वापस -ENOMEM;
	ret = wdev->hwbus_ops->copy_from_io(wdev->hwbus_priv, reg, पंचांगp,
					    माप(u32));
	अगर (ret >= 0)
		*val = le32_to_cpu(*पंचांगp);
	kमुक्त(पंचांगp);
	अगर (ret)
		dev_err(wdev->dev, "%s: bus communication error: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो32(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 val)
अणु
	पूर्णांक ret;
	__le32 *पंचांगp = kदो_स्मृति(माप(u32), GFP_KERNEL);

	अगर (!पंचांगp)
		वापस -ENOMEM;
	*पंचांगp = cpu_to_le32(val);
	ret = wdev->hwbus_ops->copy_to_io(wdev->hwbus_priv, reg, पंचांगp,
					  माप(u32));
	kमुक्त(पंचांगp);
	अगर (ret)
		dev_err(wdev->dev, "%s: bus communication error: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक पढ़ो32_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 *val)
अणु
	पूर्णांक ret;

	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = पढ़ो32(wdev, reg, val);
	_trace_io_पढ़ो32(reg, *val);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो32_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 val)
अणु
	पूर्णांक ret;

	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = ग_लिखो32(wdev, reg, val);
	_trace_io_ग_लिखो32(reg, val);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक ग_लिखो32_bits_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 mask, u32 val)
अणु
	पूर्णांक ret;
	u32 val_r, val_w;

	WARN_ON(~mask & val);
	val &= mask;
	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = पढ़ो32(wdev, reg, &val_r);
	_trace_io_पढ़ो32(reg, val_r);
	अगर (ret < 0)
		जाओ err;
	val_w = (val_r & ~mask) | val;
	अगर (val_w != val_r) अणु
		ret = ग_लिखो32(wdev, reg, val_w);
		_trace_io_ग_लिखो32(reg, val_w);
	पूर्ण
err:
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक indirect_पढ़ो(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 addr,
			 व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u32 cfg;
	u32 prefetch;

	WARN_ON(len >= 0x2000);
	WARN_ON(reg != WFX_REG_AHB_DPORT && reg != WFX_REG_SRAM_DPORT);

	अगर (reg == WFX_REG_AHB_DPORT)
		prefetch = CFG_PREFETCH_AHB;
	अन्यथा अगर (reg == WFX_REG_SRAM_DPORT)
		prefetch = CFG_PREFETCH_SRAM;
	अन्यथा
		वापस -ENODEV;

	ret = ग_लिखो32(wdev, WFX_REG_BASE_ADDR, addr);
	अगर (ret < 0)
		जाओ err;

	ret = पढ़ो32(wdev, WFX_REG_CONFIG, &cfg);
	अगर (ret < 0)
		जाओ err;

	ret = ग_लिखो32(wdev, WFX_REG_CONFIG, cfg | prefetch);
	अगर (ret < 0)
		जाओ err;

	क्रम (i = 0; i < 20; i++) अणु
		ret = पढ़ो32(wdev, WFX_REG_CONFIG, &cfg);
		अगर (ret < 0)
			जाओ err;
		अगर (!(cfg & prefetch))
			अवरोध;
		usleep_range(200, 250);
	पूर्ण
	अगर (i == 20) अणु
		ret = -ETIMEDOUT;
		जाओ err;
	पूर्ण

	ret = wdev->hwbus_ops->copy_from_io(wdev->hwbus_priv, reg, buf, len);

err:
	अगर (ret < 0)
		स_रखो(buf, 0xFF, len); // Never वापस undefined value
	वापस ret;
पूर्ण

अटल पूर्णांक indirect_ग_लिखो(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 addr,
			  स्थिर व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	WARN_ON(len >= 0x2000);
	WARN_ON(reg != WFX_REG_AHB_DPORT && reg != WFX_REG_SRAM_DPORT);
	ret = ग_लिखो32(wdev, WFX_REG_BASE_ADDR, addr);
	अगर (ret < 0)
		वापस ret;

	वापस wdev->hwbus_ops->copy_to_io(wdev->hwbus_priv, reg, buf, len);
पूर्ण

अटल पूर्णांक indirect_पढ़ो_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 addr,
				व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = indirect_पढ़ो(wdev, reg, addr, buf, len);
	_trace_io_ind_पढ़ो(reg, addr, buf, len);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक indirect_ग_लिखो_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg, u32 addr,
				 स्थिर व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = indirect_ग_लिखो(wdev, reg, addr, buf, len);
	_trace_io_ind_ग_लिखो(reg, addr, buf, len);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	वापस ret;
पूर्ण

अटल पूर्णांक indirect_पढ़ो32_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg,
				  u32 addr, u32 *val)
अणु
	पूर्णांक ret;
	__le32 *पंचांगp = kदो_स्मृति(माप(u32), GFP_KERNEL);

	अगर (!पंचांगp)
		वापस -ENOMEM;
	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = indirect_पढ़ो(wdev, reg, addr, पंचांगp, माप(u32));
	*val = le32_to_cpu(*पंचांगp);
	_trace_io_ind_पढ़ो32(reg, addr, *val);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल पूर्णांक indirect_ग_लिखो32_locked(काष्ठा wfx_dev *wdev, पूर्णांक reg,
				   u32 addr, u32 val)
अणु
	पूर्णांक ret;
	__le32 *पंचांगp = kदो_स्मृति(माप(u32), GFP_KERNEL);

	अगर (!पंचांगp)
		वापस -ENOMEM;
	*पंचांगp = cpu_to_le32(val);
	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = indirect_ग_लिखो(wdev, reg, addr, पंचांगp, माप(u32));
	_trace_io_ind_ग_लिखो32(reg, addr, val);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

पूर्णांक wfx_data_पढ़ो(काष्ठा wfx_dev *wdev, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	WARN((दीर्घ)buf & 3, "%s: unaligned buffer", __func__);
	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = wdev->hwbus_ops->copy_from_io(wdev->hwbus_priv,
					    WFX_REG_IN_OUT_QUEUE, buf, len);
	_trace_io_पढ़ो(WFX_REG_IN_OUT_QUEUE, buf, len);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	अगर (ret)
		dev_err(wdev->dev, "%s: bus communication error: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

पूर्णांक wfx_data_ग_लिखो(काष्ठा wfx_dev *wdev, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	WARN((दीर्घ)buf & 3, "%s: unaligned buffer", __func__);
	wdev->hwbus_ops->lock(wdev->hwbus_priv);
	ret = wdev->hwbus_ops->copy_to_io(wdev->hwbus_priv,
					  WFX_REG_IN_OUT_QUEUE, buf, len);
	_trace_io_ग_लिखो(WFX_REG_IN_OUT_QUEUE, buf, len);
	wdev->hwbus_ops->unlock(wdev->hwbus_priv);
	अगर (ret)
		dev_err(wdev->dev, "%s: bus communication error: %d\n",
			__func__, ret);
	वापस ret;
पूर्ण

पूर्णांक sram_buf_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, व्योम *buf, माप_प्रकार len)
अणु
	वापस indirect_पढ़ो_locked(wdev, WFX_REG_SRAM_DPORT, addr, buf, len);
पूर्ण

पूर्णांक ahb_buf_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, व्योम *buf, माप_प्रकार len)
अणु
	वापस indirect_पढ़ो_locked(wdev, WFX_REG_AHB_DPORT, addr, buf, len);
पूर्ण

पूर्णांक sram_buf_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	वापस indirect_ग_लिखो_locked(wdev, WFX_REG_SRAM_DPORT, addr, buf, len);
पूर्ण

पूर्णांक ahb_buf_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, स्थिर व्योम *buf, माप_प्रकार len)
अणु
	वापस indirect_ग_लिखो_locked(wdev, WFX_REG_AHB_DPORT, addr, buf, len);
पूर्ण

पूर्णांक sram_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, u32 *val)
अणु
	वापस indirect_पढ़ो32_locked(wdev, WFX_REG_SRAM_DPORT, addr, val);
पूर्ण

पूर्णांक ahb_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 addr, u32 *val)
अणु
	वापस indirect_पढ़ो32_locked(wdev, WFX_REG_AHB_DPORT, addr, val);
पूर्ण

पूर्णांक sram_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, u32 val)
अणु
	वापस indirect_ग_लिखो32_locked(wdev, WFX_REG_SRAM_DPORT, addr, val);
पूर्ण

पूर्णांक ahb_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 addr, u32 val)
अणु
	वापस indirect_ग_लिखो32_locked(wdev, WFX_REG_AHB_DPORT, addr, val);
पूर्ण

पूर्णांक config_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 *val)
अणु
	वापस पढ़ो32_locked(wdev, WFX_REG_CONFIG, val);
पूर्ण

पूर्णांक config_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 val)
अणु
	वापस ग_लिखो32_locked(wdev, WFX_REG_CONFIG, val);
पूर्ण

पूर्णांक config_reg_ग_लिखो_bits(काष्ठा wfx_dev *wdev, u32 mask, u32 val)
अणु
	वापस ग_लिखो32_bits_locked(wdev, WFX_REG_CONFIG, mask, val);
पूर्ण

पूर्णांक control_reg_पढ़ो(काष्ठा wfx_dev *wdev, u32 *val)
अणु
	वापस पढ़ो32_locked(wdev, WFX_REG_CONTROL, val);
पूर्ण

पूर्णांक control_reg_ग_लिखो(काष्ठा wfx_dev *wdev, u32 val)
अणु
	वापस ग_लिखो32_locked(wdev, WFX_REG_CONTROL, val);
पूर्ण

पूर्णांक control_reg_ग_लिखो_bits(काष्ठा wfx_dev *wdev, u32 mask, u32 val)
अणु
	वापस ग_लिखो32_bits_locked(wdev, WFX_REG_CONTROL, mask, val);
पूर्ण

पूर्णांक igpr_reg_पढ़ो(काष्ठा wfx_dev *wdev, पूर्णांक index, u32 *val)
अणु
	पूर्णांक ret;

	*val = ~0; // Never वापस undefined value
	ret = ग_लिखो32_locked(wdev, WFX_REG_SET_GEN_R_W, IGPR_RW | index << 24);
	अगर (ret)
		वापस ret;
	ret = पढ़ो32_locked(wdev, WFX_REG_SET_GEN_R_W, val);
	अगर (ret)
		वापस ret;
	*val &= IGPR_VALUE;
	वापस ret;
पूर्ण

पूर्णांक igpr_reg_ग_लिखो(काष्ठा wfx_dev *wdev, पूर्णांक index, u32 val)
अणु
	वापस ग_लिखो32_locked(wdev, WFX_REG_SET_GEN_R_W, index << 24 | val);
पूर्ण
