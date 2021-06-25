<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2016 Mentor Graphics Inc.
 * Copyright (C) 2005-2009 Freescale Semiconductor, Inc.
 */
#समावेश <linux/पन.स>
#समावेश "ipu-prv.h"

काष्ठा ipu_vdi अणु
	व्योम __iomem *base;
	u32 module;
	spinlock_t lock;
	पूर्णांक use_count;
	काष्ठा ipu_soc *ipu;
पूर्ण;


/* VDI Register Offsets */
#घोषणा VDI_FSIZE 0x0000
#घोषणा VDI_C     0x0004

/* VDI Register Fields */
#घोषणा VDI_C_CH_420             (0 << 1)
#घोषणा VDI_C_CH_422             (1 << 1)
#घोषणा VDI_C_MOT_SEL_MASK       (0x3 << 2)
#घोषणा VDI_C_MOT_SEL_FULL       (2 << 2)
#घोषणा VDI_C_MOT_SEL_LOW        (1 << 2)
#घोषणा VDI_C_MOT_SEL_MED        (0 << 2)
#घोषणा VDI_C_BURST_SIZE1_4      (3 << 4)
#घोषणा VDI_C_BURST_SIZE2_4      (3 << 8)
#घोषणा VDI_C_BURST_SIZE3_4      (3 << 12)
#घोषणा VDI_C_BURST_SIZE_MASK    0xF
#घोषणा VDI_C_BURST_SIZE1_OFFSET 4
#घोषणा VDI_C_BURST_SIZE2_OFFSET 8
#घोषणा VDI_C_BURST_SIZE3_OFFSET 12
#घोषणा VDI_C_VWM1_SET_1         (0 << 16)
#घोषणा VDI_C_VWM1_SET_2         (1 << 16)
#घोषणा VDI_C_VWM1_CLR_2         (1 << 19)
#घोषणा VDI_C_VWM3_SET_1         (0 << 22)
#घोषणा VDI_C_VWM3_SET_2         (1 << 22)
#घोषणा VDI_C_VWM3_CLR_2         (1 << 25)
#घोषणा VDI_C_TOP_FIELD_MAN_1    (1 << 30)
#घोषणा VDI_C_TOP_FIELD_AUTO_1   (1 << 31)

अटल अंतरभूत u32 ipu_vdi_पढ़ो(काष्ठा ipu_vdi *vdi, अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोl(vdi->base + offset);
पूर्ण

अटल अंतरभूत व्योम ipu_vdi_ग_लिखो(काष्ठा ipu_vdi *vdi, u32 value,
				 अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोl(value, vdi->base + offset);
पूर्ण

व्योम ipu_vdi_set_field_order(काष्ठा ipu_vdi *vdi, v4l2_std_id std, u32 field)
अणु
	bool top_field_0 = false;
	अचिन्हित दीर्घ flags;
	u32 reg;

	चयन (field) अणु
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_TOP:
		top_field_0 = true;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_BT:
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_BOTTOM:
		top_field_0 = false;
		अवरोध;
	शेष:
		top_field_0 = (std & V4L2_STD_525_60) ? true : false;
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&vdi->lock, flags);

	reg = ipu_vdi_पढ़ो(vdi, VDI_C);
	अगर (top_field_0)
		reg &= ~(VDI_C_TOP_FIELD_MAN_1 | VDI_C_TOP_FIELD_AUTO_1);
	अन्यथा
		reg |= VDI_C_TOP_FIELD_MAN_1 | VDI_C_TOP_FIELD_AUTO_1;
	ipu_vdi_ग_लिखो(vdi, reg, VDI_C);

	spin_unlock_irqrestore(&vdi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_set_field_order);

व्योम ipu_vdi_set_motion(काष्ठा ipu_vdi *vdi, क्रमागत ipu_motion_sel motion_sel)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&vdi->lock, flags);

	reg = ipu_vdi_पढ़ो(vdi, VDI_C);

	reg &= ~VDI_C_MOT_SEL_MASK;

	चयन (motion_sel) अणु
	हाल MED_MOTION:
		reg |= VDI_C_MOT_SEL_MED;
		अवरोध;
	हाल HIGH_MOTION:
		reg |= VDI_C_MOT_SEL_FULL;
		अवरोध;
	शेष:
		reg |= VDI_C_MOT_SEL_LOW;
		अवरोध;
	पूर्ण

	ipu_vdi_ग_लिखो(vdi, reg, VDI_C);

	spin_unlock_irqrestore(&vdi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_set_motion);

व्योम ipu_vdi_setup(काष्ठा ipu_vdi *vdi, u32 code, पूर्णांक xres, पूर्णांक yres)
अणु
	अचिन्हित दीर्घ flags;
	u32 pixel_fmt, reg;

	spin_lock_irqsave(&vdi->lock, flags);

	reg = ((yres - 1) << 16) | (xres - 1);
	ipu_vdi_ग_लिखो(vdi, reg, VDI_FSIZE);

	/*
	 * Full motion, only vertical filter is used.
	 * Burst size is 4 accesses
	 */
	अगर (code == MEDIA_BUS_FMT_UYVY8_2X8 ||
	    code == MEDIA_BUS_FMT_UYVY8_1X16 ||
	    code == MEDIA_BUS_FMT_YUYV8_2X8 ||
	    code == MEDIA_BUS_FMT_YUYV8_1X16)
		pixel_fmt = VDI_C_CH_422;
	अन्यथा
		pixel_fmt = VDI_C_CH_420;

	reg = ipu_vdi_पढ़ो(vdi, VDI_C);
	reg |= pixel_fmt;
	reg |= VDI_C_BURST_SIZE2_4;
	reg |= VDI_C_BURST_SIZE1_4 | VDI_C_VWM1_CLR_2;
	reg |= VDI_C_BURST_SIZE3_4 | VDI_C_VWM3_CLR_2;
	ipu_vdi_ग_लिखो(vdi, reg, VDI_C);

	spin_unlock_irqrestore(&vdi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_setup);

व्योम ipu_vdi_unsetup(काष्ठा ipu_vdi *vdi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdi->lock, flags);
	ipu_vdi_ग_लिखो(vdi, 0, VDI_FSIZE);
	ipu_vdi_ग_लिखो(vdi, 0, VDI_C);
	spin_unlock_irqrestore(&vdi->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_unsetup);

पूर्णांक ipu_vdi_enable(काष्ठा ipu_vdi *vdi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdi->lock, flags);

	अगर (!vdi->use_count)
		ipu_module_enable(vdi->ipu, vdi->module);

	vdi->use_count++;

	spin_unlock_irqrestore(&vdi->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_enable);

पूर्णांक ipu_vdi_disable(काष्ठा ipu_vdi *vdi)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vdi->lock, flags);

	अगर (vdi->use_count) अणु
		अगर (!--vdi->use_count)
			ipu_module_disable(vdi->ipu, vdi->module);
	पूर्ण

	spin_unlock_irqrestore(&vdi->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_disable);

काष्ठा ipu_vdi *ipu_vdi_get(काष्ठा ipu_soc *ipu)
अणु
	वापस ipu->vdi_priv;
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_get);

व्योम ipu_vdi_put(काष्ठा ipu_vdi *vdi)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(ipu_vdi_put);

पूर्णांक ipu_vdi_init(काष्ठा ipu_soc *ipu, काष्ठा device *dev,
		 अचिन्हित दीर्घ base, u32 module)
अणु
	काष्ठा ipu_vdi *vdi;

	vdi = devm_kzalloc(dev, माप(*vdi), GFP_KERNEL);
	अगर (!vdi)
		वापस -ENOMEM;

	ipu->vdi_priv = vdi;

	spin_lock_init(&vdi->lock);
	vdi->module = module;
	vdi->base = devm_ioremap(dev, base, PAGE_SIZE);
	अगर (!vdi->base)
		वापस -ENOMEM;

	dev_dbg(dev, "VDI base: 0x%08lx remapped to %p\n", base, vdi->base);
	vdi->ipu = ipu;

	वापस 0;
पूर्ण

व्योम ipu_vdi_निकास(काष्ठा ipu_soc *ipu)
अणु
पूर्ण
