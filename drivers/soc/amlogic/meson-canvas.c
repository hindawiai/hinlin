<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 * Copyright (C) 2014 Endless Mobile
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/soc/amlogic/meson-canvas.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पन.स>

#घोषणा NUM_CANVAS 256

/* DMC Registers */
#घोषणा DMC_CAV_LUT_DATAL	0x00
	#घोषणा CANVAS_WIDTH_LBIT	29
	#घोषणा CANVAS_WIDTH_LWID	3
#घोषणा DMC_CAV_LUT_DATAH	0x04
	#घोषणा CANVAS_WIDTH_HBIT	0
	#घोषणा CANVAS_HEIGHT_BIT	9
	#घोषणा CANVAS_WRAP_BIT		22
	#घोषणा CANVAS_BLKMODE_BIT	24
	#घोषणा CANVAS_ENDIAN_BIT	26
#घोषणा DMC_CAV_LUT_ADDR	0x08
	#घोषणा CANVAS_LUT_WR_EN	BIT(9)
	#घोषणा CANVAS_LUT_RD_EN	BIT(8)

काष्ठा meson_canvas अणु
	काष्ठा device *dev;
	व्योम __iomem *reg_base;
	spinlock_t lock; /* canvas device lock */
	u8 used[NUM_CANVAS];
	bool supports_endianness;
पूर्ण;

अटल व्योम canvas_ग_लिखो(काष्ठा meson_canvas *canvas, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, canvas->reg_base + reg);
पूर्ण

अटल u32 canvas_पढ़ो(काष्ठा meson_canvas *canvas, u32 reg)
अणु
	वापस पढ़ोl_relaxed(canvas->reg_base + reg);
पूर्ण

काष्ठा meson_canvas *meson_canvas_get(काष्ठा device *dev)
अणु
	काष्ठा device_node *canvas_node;
	काष्ठा platक्रमm_device *canvas_pdev;
	काष्ठा meson_canvas *canvas;

	canvas_node = of_parse_phandle(dev->of_node, "amlogic,canvas", 0);
	अगर (!canvas_node)
		वापस ERR_PTR(-ENODEV);

	canvas_pdev = of_find_device_by_node(canvas_node);
	अगर (!canvas_pdev) अणु
		of_node_put(canvas_node);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	of_node_put(canvas_node);

	/*
	 * If priv is शून्य, it's probably because the canvas hasn't
	 * properly initialized. Bail out with -EINVAL because, in the
	 * current state, this driver probe cannot वापस -EPROBE_DEFER
	 */
	canvas = dev_get_drvdata(&canvas_pdev->dev);
	अगर (!canvas) अणु
		put_device(&canvas_pdev->dev);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस canvas;
पूर्ण
EXPORT_SYMBOL_GPL(meson_canvas_get);

पूर्णांक meson_canvas_config(काष्ठा meson_canvas *canvas, u8 canvas_index,
			u32 addr, u32 stride, u32 height,
			अचिन्हित पूर्णांक wrap,
			अचिन्हित पूर्णांक blkmode,
			अचिन्हित पूर्णांक endian)
अणु
	अचिन्हित दीर्घ flags;

	अगर (endian && !canvas->supports_endianness) अणु
		dev_err(canvas->dev,
			"Endianness is not supported on this SoC\n");
		वापस -EINVAL;
	पूर्ण

	spin_lock_irqsave(&canvas->lock, flags);
	अगर (!canvas->used[canvas_index]) अणु
		dev_err(canvas->dev,
			"Trying to setup non allocated canvas %u\n",
			canvas_index);
		spin_unlock_irqrestore(&canvas->lock, flags);
		वापस -EINVAL;
	पूर्ण

	canvas_ग_लिखो(canvas, DMC_CAV_LUT_DATAL,
		     ((addr + 7) >> 3) |
		     (((stride + 7) >> 3) << CANVAS_WIDTH_LBIT));

	canvas_ग_लिखो(canvas, DMC_CAV_LUT_DATAH,
		     ((((stride + 7) >> 3) >> CANVAS_WIDTH_LWID) <<
						CANVAS_WIDTH_HBIT) |
		     (height << CANVAS_HEIGHT_BIT) |
		     (wrap << CANVAS_WRAP_BIT) |
		     (blkmode << CANVAS_BLKMODE_BIT) |
		     (endian << CANVAS_ENDIAN_BIT));

	canvas_ग_लिखो(canvas, DMC_CAV_LUT_ADDR,
		     CANVAS_LUT_WR_EN | canvas_index);

	/* Force a पढ़ो-back to make sure everything is flushed. */
	canvas_पढ़ो(canvas, DMC_CAV_LUT_DATAH);
	spin_unlock_irqrestore(&canvas->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_canvas_config);

पूर्णांक meson_canvas_alloc(काष्ठा meson_canvas *canvas, u8 *canvas_index)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&canvas->lock, flags);
	क्रम (i = 0; i < NUM_CANVAS; ++i) अणु
		अगर (!canvas->used[i]) अणु
			canvas->used[i] = 1;
			spin_unlock_irqrestore(&canvas->lock, flags);
			*canvas_index = i;
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&canvas->lock, flags);

	dev_err(canvas->dev, "No more canvas available\n");
	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(meson_canvas_alloc);

पूर्णांक meson_canvas_मुक्त(काष्ठा meson_canvas *canvas, u8 canvas_index)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&canvas->lock, flags);
	अगर (!canvas->used[canvas_index]) अणु
		dev_err(canvas->dev,
			"Trying to free unused canvas %u\n", canvas_index);
		spin_unlock_irqrestore(&canvas->lock, flags);
		वापस -EINVAL;
	पूर्ण
	canvas->used[canvas_index] = 0;
	spin_unlock_irqrestore(&canvas->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(meson_canvas_मुक्त);

अटल पूर्णांक meson_canvas_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा meson_canvas *canvas;
	काष्ठा device *dev = &pdev->dev;

	canvas = devm_kzalloc(dev, माप(*canvas), GFP_KERNEL);
	अगर (!canvas)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	canvas->reg_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(canvas->reg_base))
		वापस PTR_ERR(canvas->reg_base);

	canvas->supports_endianness = of_device_get_match_data(dev);

	canvas->dev = dev;
	spin_lock_init(&canvas->lock);
	dev_set_drvdata(dev, canvas);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id canvas_dt_match[] = अणु
	अणु .compatible = "amlogic,meson8-canvas", .data = (व्योम *)false, पूर्ण,
	अणु .compatible = "amlogic,meson8b-canvas", .data = (व्योम *)false, पूर्ण,
	अणु .compatible = "amlogic,meson8m2-canvas", .data = (व्योम *)false, पूर्ण,
	अणु .compatible = "amlogic,canvas", .data = (व्योम *)true, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, canvas_dt_match);

अटल काष्ठा platक्रमm_driver meson_canvas_driver = अणु
	.probe = meson_canvas_probe,
	.driver = अणु
		.name = "amlogic-canvas",
		.of_match_table = canvas_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(meson_canvas_driver);

MODULE_DESCRIPTION("Amlogic Canvas driver");
MODULE_AUTHOR("Maxime Jourdan <mjourdan@baylibre.com>");
MODULE_LICENSE("GPL");
