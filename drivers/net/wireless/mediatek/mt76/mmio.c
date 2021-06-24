<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (C) 2016 Felix Fietkau <nbd@nbd.name>
 */

#समावेश "mt76.h"
#समावेश "trace.h"

अटल u32 mt76_mmio_rr(काष्ठा mt76_dev *dev, u32 offset)
अणु
	u32 val;

	val = पढ़ोl(dev->mmio.regs + offset);
	trace_reg_rr(dev, offset, val);

	वापस val;
पूर्ण

अटल व्योम mt76_mmio_wr(काष्ठा mt76_dev *dev, u32 offset, u32 val)
अणु
	trace_reg_wr(dev, offset, val);
	ग_लिखोl(val, dev->mmio.regs + offset);
पूर्ण

अटल u32 mt76_mmio_rmw(काष्ठा mt76_dev *dev, u32 offset, u32 mask, u32 val)
अणु
	val |= mt76_mmio_rr(dev, offset) & ~mask;
	mt76_mmio_wr(dev, offset, val);
	वापस val;
पूर्ण

अटल व्योम mt76_mmio_ग_लिखो_copy(काष्ठा mt76_dev *dev, u32 offset,
				 स्थिर व्योम *data, पूर्णांक len)
अणु
	__ioग_लिखो32_copy(dev->mmio.regs + offset, data, DIV_ROUND_UP(len, 4));
पूर्ण

अटल व्योम mt76_mmio_पढ़ो_copy(काष्ठा mt76_dev *dev, u32 offset,
				व्योम *data, पूर्णांक len)
अणु
	__ioपढ़ो32_copy(data, dev->mmio.regs + offset, DIV_ROUND_UP(len, 4));
पूर्ण

अटल पूर्णांक mt76_mmio_wr_rp(काष्ठा mt76_dev *dev, u32 base,
			   स्थिर काष्ठा mt76_reg_pair *data, पूर्णांक len)
अणु
	जबतक (len > 0) अणु
		mt76_mmio_wr(dev, data->reg, data->value);
		data++;
		len--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mt76_mmio_rd_rp(काष्ठा mt76_dev *dev, u32 base,
			   काष्ठा mt76_reg_pair *data, पूर्णांक len)
अणु
	जबतक (len > 0) अणु
		data->value = mt76_mmio_rr(dev, data->reg);
		data++;
		len--;
	पूर्ण

	वापस 0;
पूर्ण

व्योम mt76_set_irq_mask(काष्ठा mt76_dev *dev, u32 addr,
		       u32 clear, u32 set)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dev->mmio.irq_lock, flags);
	dev->mmio.irqmask &= ~clear;
	dev->mmio.irqmask |= set;
	अगर (addr)
		mt76_mmio_wr(dev, addr, dev->mmio.irqmask);
	spin_unlock_irqrestore(&dev->mmio.irq_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_set_irq_mask);

व्योम mt76_mmio_init(काष्ठा mt76_dev *dev, व्योम __iomem *regs)
अणु
	अटल स्थिर काष्ठा mt76_bus_ops mt76_mmio_ops = अणु
		.rr = mt76_mmio_rr,
		.rmw = mt76_mmio_rmw,
		.wr = mt76_mmio_wr,
		.ग_लिखो_copy = mt76_mmio_ग_लिखो_copy,
		.पढ़ो_copy = mt76_mmio_पढ़ो_copy,
		.wr_rp = mt76_mmio_wr_rp,
		.rd_rp = mt76_mmio_rd_rp,
		.type = MT76_BUS_MMIO,
	पूर्ण;

	dev->bus = &mt76_mmio_ops;
	dev->mmio.regs = regs;

	spin_lock_init(&dev->mmio.irq_lock);
पूर्ण
EXPORT_SYMBOL_GPL(mt76_mmio_init);
