<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hisilicon Reset Controller Driver
 *
 * Copyright (c) 2015-2016 HiSilicon Technologies Co., Ltd.
 */

#समावेश <linux/पन.स>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश "reset.h"

#घोषणा	HISI_RESET_BIT_MASK	0x1f
#घोषणा	HISI_RESET_OFFSET_SHIFT	8
#घोषणा	HISI_RESET_OFFSET_MASK	0xffff00

काष्ठा hisi_reset_controller अणु
	spinlock_t	lock;
	व्योम __iomem	*membase;
	काष्ठा reset_controller_dev	rcdev;
पूर्ण;


#घोषणा to_hisi_reset_controller(rcdev)  \
	container_of(rcdev, काष्ठा hisi_reset_controller, rcdev)

अटल पूर्णांक hisi_reset_of_xlate(काष्ठा reset_controller_dev *rcdev,
			स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	u32 offset;
	u8 bit;

	offset = (reset_spec->args[0] << HISI_RESET_OFFSET_SHIFT)
		& HISI_RESET_OFFSET_MASK;
	bit = reset_spec->args[1] & HISI_RESET_BIT_MASK;

	वापस (offset | bit);
पूर्ण

अटल पूर्णांक hisi_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
			      अचिन्हित दीर्घ id)
अणु
	काष्ठा hisi_reset_controller *rstc = to_hisi_reset_controller(rcdev);
	अचिन्हित दीर्घ flags;
	u32 offset, reg;
	u8 bit;

	offset = (id & HISI_RESET_OFFSET_MASK) >> HISI_RESET_OFFSET_SHIFT;
	bit = id & HISI_RESET_BIT_MASK;

	spin_lock_irqsave(&rstc->lock, flags);

	reg = पढ़ोl(rstc->membase + offset);
	ग_लिखोl(reg | BIT(bit), rstc->membase + offset);

	spin_unlock_irqrestore(&rstc->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा hisi_reset_controller *rstc = to_hisi_reset_controller(rcdev);
	अचिन्हित दीर्घ flags;
	u32 offset, reg;
	u8 bit;

	offset = (id & HISI_RESET_OFFSET_MASK) >> HISI_RESET_OFFSET_SHIFT;
	bit = id & HISI_RESET_BIT_MASK;

	spin_lock_irqsave(&rstc->lock, flags);

	reg = पढ़ोl(rstc->membase + offset);
	ग_लिखोl(reg & ~BIT(bit), rstc->membase + offset);

	spin_unlock_irqrestore(&rstc->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops hisi_reset_ops = अणु
	.निश्चित		= hisi_reset_निश्चित,
	.deनिश्चित	= hisi_reset_deनिश्चित,
पूर्ण;

काष्ठा hisi_reset_controller *hisi_reset_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_reset_controller *rstc;

	rstc = devm_kदो_स्मृति(&pdev->dev, माप(*rstc), GFP_KERNEL);
	अगर (!rstc)
		वापस शून्य;

	rstc->membase = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(rstc->membase))
		वापस शून्य;

	spin_lock_init(&rstc->lock);
	rstc->rcdev.owner = THIS_MODULE;
	rstc->rcdev.ops = &hisi_reset_ops;
	rstc->rcdev.of_node = pdev->dev.of_node;
	rstc->rcdev.of_reset_n_cells = 2;
	rstc->rcdev.of_xlate = hisi_reset_of_xlate;
	reset_controller_रेजिस्टर(&rstc->rcdev);

	वापस rstc;
पूर्ण
EXPORT_SYMBOL_GPL(hisi_reset_init);

व्योम hisi_reset_निकास(काष्ठा hisi_reset_controller *rstc)
अणु
	reset_controller_unरेजिस्टर(&rstc->rcdev);
पूर्ण
EXPORT_SYMBOL_GPL(hisi_reset_निकास);
