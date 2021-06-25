<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Paul Burton <paul.burton@mips.com>
 */

#समावेश <generated/utsrelease.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

काष्ठा img_ascii_lcd_ctx;

/**
 * काष्ठा img_ascii_lcd_config - Configuration inक्रमmation about an LCD model
 * @num_अक्षरs: the number of अक्षरacters the LCD can display
 * @बाह्यal_regmap: true अगर रेजिस्टरs are in a प्रणाली controller, अन्यथा false
 * @update: function called to update the LCD
 */
काष्ठा img_ascii_lcd_config अणु
	अचिन्हित पूर्णांक num_अक्षरs;
	bool बाह्यal_regmap;
	व्योम (*update)(काष्ठा img_ascii_lcd_ctx *ctx);
पूर्ण;

/**
 * काष्ठा img_ascii_lcd_ctx - Private data काष्ठाure
 * @pdev: the ASCII LCD platक्रमm device
 * @base: the base address of the LCD रेजिस्टरs
 * @regmap: the regmap through which LCD रेजिस्टरs are accessed
 * @offset: the offset within regmap to the start of the LCD रेजिस्टरs
 * @cfg: poपूर्णांकer to the LCD model configuration
 * @message: the full message to display or scroll on the LCD
 * @message_len: the length of the @message string
 * @scroll_pos: index of the first अक्षरacter of @message currently displayed
 * @scroll_rate: scroll पूर्णांकerval in jअगरfies
 * @समयr: समयr used to implement scrolling
 * @curr: the string currently displayed on the LCD
 */
काष्ठा img_ascii_lcd_ctx अणु
	काष्ठा platक्रमm_device *pdev;
	जोड़ अणु
		व्योम __iomem *base;
		काष्ठा regmap *regmap;
	पूर्ण;
	u32 offset;
	स्थिर काष्ठा img_ascii_lcd_config *cfg;
	अक्षर *message;
	अचिन्हित पूर्णांक message_len;
	अचिन्हित पूर्णांक scroll_pos;
	अचिन्हित पूर्णांक scroll_rate;
	काष्ठा समयr_list समयr;
	अक्षर curr[] __aligned(8);
पूर्ण;

/*
 * MIPS Boston development board
 */

अटल व्योम boston_update(काष्ठा img_ascii_lcd_ctx *ctx)
अणु
	uदीर्घ val;

#अगर BITS_PER_LONG == 64
	val = *((u64 *)&ctx->curr[0]);
	__raw_ग_लिखोq(val, ctx->base);
#या_अगर BITS_PER_LONG == 32
	val = *((u32 *)&ctx->curr[0]);
	__raw_ग_लिखोl(val, ctx->base);
	val = *((u32 *)&ctx->curr[4]);
	__raw_ग_लिखोl(val, ctx->base + 4);
#अन्यथा
# error Not 32 or 64 bit
#पूर्ण_अगर
पूर्ण

अटल काष्ठा img_ascii_lcd_config boston_config = अणु
	.num_अक्षरs = 8,
	.update = boston_update,
पूर्ण;

/*
 * MIPS Malta development board
 */

अटल व्योम malta_update(काष्ठा img_ascii_lcd_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < ctx->cfg->num_अक्षरs; i++) अणु
		err = regmap_ग_लिखो(ctx->regmap,
				   ctx->offset + (i * 8), ctx->curr[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (unlikely(err))
		pr_err_ratelimited("Failed to update LCD display: %d\n", err);
पूर्ण

अटल काष्ठा img_ascii_lcd_config malta_config = अणु
	.num_अक्षरs = 8,
	.बाह्यal_regmap = true,
	.update = malta_update,
पूर्ण;

/*
 * MIPS SEAD3 development board
 */

क्रमागत अणु
	SEAD3_REG_LCD_CTRL		= 0x00,
#घोषणा SEAD3_REG_LCD_CTRL_SETDRAM	BIT(7)
	SEAD3_REG_LCD_DATA		= 0x08,
	SEAD3_REG_CPLD_STATUS		= 0x10,
#घोषणा SEAD3_REG_CPLD_STATUS_BUSY	BIT(0)
	SEAD3_REG_CPLD_DATA		= 0x18,
#घोषणा SEAD3_REG_CPLD_DATA_BUSY	BIT(7)
पूर्ण;

अटल पूर्णांक sead3_रुको_sm_idle(काष्ठा img_ascii_lcd_ctx *ctx)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक err;

	करो अणु
		err = regmap_पढ़ो(ctx->regmap,
				  ctx->offset + SEAD3_REG_CPLD_STATUS,
				  &status);
		अगर (err)
			वापस err;
	पूर्ण जबतक (status & SEAD3_REG_CPLD_STATUS_BUSY);

	वापस 0;

पूर्ण

अटल पूर्णांक sead3_रुको_lcd_idle(काष्ठा img_ascii_lcd_ctx *ctx)
अणु
	अचिन्हित पूर्णांक cpld_data;
	पूर्णांक err;

	err = sead3_रुको_sm_idle(ctx);
	अगर (err)
		वापस err;

	करो अणु
		err = regmap_पढ़ो(ctx->regmap,
				  ctx->offset + SEAD3_REG_LCD_CTRL,
				  &cpld_data);
		अगर (err)
			वापस err;

		err = sead3_रुको_sm_idle(ctx);
		अगर (err)
			वापस err;

		err = regmap_पढ़ो(ctx->regmap,
				  ctx->offset + SEAD3_REG_CPLD_DATA,
				  &cpld_data);
		अगर (err)
			वापस err;
	पूर्ण जबतक (cpld_data & SEAD3_REG_CPLD_DATA_BUSY);

	वापस 0;
पूर्ण

अटल व्योम sead3_update(काष्ठा img_ascii_lcd_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;

	क्रम (i = 0; i < ctx->cfg->num_अक्षरs; i++) अणु
		err = sead3_रुको_lcd_idle(ctx);
		अगर (err)
			अवरोध;

		err = regmap_ग_लिखो(ctx->regmap,
				   ctx->offset + SEAD3_REG_LCD_CTRL,
				   SEAD3_REG_LCD_CTRL_SETDRAM | i);
		अगर (err)
			अवरोध;

		err = sead3_रुको_lcd_idle(ctx);
		अगर (err)
			अवरोध;

		err = regmap_ग_लिखो(ctx->regmap,
				   ctx->offset + SEAD3_REG_LCD_DATA,
				   ctx->curr[i]);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (unlikely(err))
		pr_err_ratelimited("Failed to update LCD display: %d\n", err);
पूर्ण

अटल काष्ठा img_ascii_lcd_config sead3_config = अणु
	.num_अक्षरs = 16,
	.बाह्यal_regmap = true,
	.update = sead3_update,
पूर्ण;

अटल स्थिर काष्ठा of_device_id img_ascii_lcd_matches[] = अणु
	अणु .compatible = "img,boston-lcd", .data = &boston_config पूर्ण,
	अणु .compatible = "mti,malta-lcd", .data = &malta_config पूर्ण,
	अणु .compatible = "mti,sead3-lcd", .data = &sead3_config पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, img_ascii_lcd_matches);

/**
 * img_ascii_lcd_scroll() - scroll the display by a अक्षरacter
 * @t: really a poपूर्णांकer to the निजी data काष्ठाure
 *
 * Scroll the current message aदीर्घ the LCD by one अक्षरacter, rearming the
 * समयr अगर required.
 */
अटल व्योम img_ascii_lcd_scroll(काष्ठा समयr_list *t)
अणु
	काष्ठा img_ascii_lcd_ctx *ctx = from_समयr(ctx, t, समयr);
	अचिन्हित पूर्णांक i, ch = ctx->scroll_pos;
	अचिन्हित पूर्णांक num_अक्षरs = ctx->cfg->num_अक्षरs;

	/* update the current message string */
	क्रम (i = 0; i < num_अक्षरs;) अणु
		/* copy as many अक्षरacters from the string as possible */
		क्रम (; i < num_अक्षरs && ch < ctx->message_len; i++, ch++)
			ctx->curr[i] = ctx->message[ch];

		/* wrap around to the start of the string */
		ch = 0;
	पूर्ण

	/* update the LCD */
	ctx->cfg->update(ctx);

	/* move on to the next अक्षरacter */
	ctx->scroll_pos++;
	ctx->scroll_pos %= ctx->message_len;

	/* rearm the समयr */
	अगर (ctx->message_len > ctx->cfg->num_अक्षरs)
		mod_समयr(&ctx->समयr, jअगरfies + ctx->scroll_rate);
पूर्ण

/**
 * img_ascii_lcd_display() - set the message to be displayed
 * @ctx: poपूर्णांकer to the निजी data काष्ठाure
 * @msg: the message to display
 * @count: length of msg, or -1
 *
 * Display a new message @msg on the LCD. @msg can be दीर्घer than the number of
 * अक्षरacters the LCD can display, in which हाल it will begin scrolling across
 * the LCD display.
 *
 * Return: 0 on success, -ENOMEM on memory allocation failure
 */
अटल पूर्णांक img_ascii_lcd_display(काष्ठा img_ascii_lcd_ctx *ctx,
			     स्थिर अक्षर *msg, sमाप_प्रकार count)
अणु
	अक्षर *new_msg;

	/* stop the scroll समयr */
	del_समयr_sync(&ctx->समयr);

	अगर (count == -1)
		count = म_माप(msg);

	/* अगर the string ends with a newline, trim it */
	अगर (msg[count - 1] == '\n')
		count--;

	new_msg = devm_kदो_स्मृति(&ctx->pdev->dev, count + 1, GFP_KERNEL);
	अगर (!new_msg)
		वापस -ENOMEM;

	स_नकल(new_msg, msg, count);
	new_msg[count] = 0;

	अगर (ctx->message)
		devm_kमुक्त(&ctx->pdev->dev, ctx->message);

	ctx->message = new_msg;
	ctx->message_len = count;
	ctx->scroll_pos = 0;

	/* update the LCD */
	img_ascii_lcd_scroll(&ctx->समयr);

	वापस 0;
पूर्ण

/**
 * message_show() - पढ़ो message via sysfs
 * @dev: the LCD device
 * @attr: the LCD message attribute
 * @buf: the buffer to पढ़ो the message पूर्णांकo
 *
 * Read the current message being displayed or scrolled across the LCD display
 * पूर्णांकo @buf, क्रम पढ़ोs from sysfs.
 *
 * Return: the number of अक्षरacters written to @buf
 */
अटल sमाप_प्रकार message_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा img_ascii_lcd_ctx *ctx = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", ctx->message);
पूर्ण

/**
 * message_store() - ग_लिखो a new message via sysfs
 * @dev: the LCD device
 * @attr: the LCD message attribute
 * @buf: the buffer containing the new message
 * @count: the size of the message in @buf
 *
 * Write a new message to display or scroll across the LCD display from sysfs.
 *
 * Return: the size of the message on success, अन्यथा -ERRNO
 */
अटल sमाप_प्रकार message_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा img_ascii_lcd_ctx *ctx = dev_get_drvdata(dev);
	पूर्णांक err;

	err = img_ascii_lcd_display(ctx, buf, count);
	वापस err ?: count;
पूर्ण

अटल DEVICE_ATTR_RW(message);

/**
 * img_ascii_lcd_probe() - probe an LCD display device
 * @pdev: the LCD platक्रमm device
 *
 * Probe an LCD display device, ensuring that we have the required resources in
 * order to access the LCD & setting up निजी data as well as sysfs files.
 *
 * Return: 0 on success, अन्यथा -ERRNO
 */
अटल पूर्णांक img_ascii_lcd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	स्थिर काष्ठा img_ascii_lcd_config *cfg;
	काष्ठा img_ascii_lcd_ctx *ctx;
	पूर्णांक err;

	match = of_match_device(img_ascii_lcd_matches, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;

	cfg = match->data;
	ctx = devm_kzalloc(&pdev->dev, माप(*ctx) + cfg->num_अक्षरs,
			   GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	अगर (cfg->बाह्यal_regmap) अणु
		ctx->regmap = syscon_node_to_regmap(pdev->dev.parent->of_node);
		अगर (IS_ERR(ctx->regmap))
			वापस PTR_ERR(ctx->regmap);

		अगर (of_property_पढ़ो_u32(pdev->dev.of_node, "offset",
					 &ctx->offset))
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		ctx->base = devm_platक्रमm_ioremap_resource(pdev, 0);
		अगर (IS_ERR(ctx->base))
			वापस PTR_ERR(ctx->base);
	पूर्ण

	ctx->pdev = pdev;
	ctx->cfg = cfg;
	ctx->message = शून्य;
	ctx->scroll_pos = 0;
	ctx->scroll_rate = HZ / 2;

	/* initialise a समयr क्रम scrolling the message */
	समयr_setup(&ctx->समयr, img_ascii_lcd_scroll, 0);

	platक्रमm_set_drvdata(pdev, ctx);

	/* display a शेष message */
	err = img_ascii_lcd_display(ctx, "Linux " UTS_RELEASE "       ", -1);
	अगर (err)
		जाओ out_del_समयr;

	err = device_create_file(&pdev->dev, &dev_attr_message);
	अगर (err)
		जाओ out_del_समयr;

	वापस 0;
out_del_समयr:
	del_समयr_sync(&ctx->समयr);
	वापस err;
पूर्ण

/**
 * img_ascii_lcd_हटाओ() - हटाओ an LCD display device
 * @pdev: the LCD platक्रमm device
 *
 * Remove an LCD display device, मुक्तing निजी resources & ensuring that the
 * driver stops using the LCD display रेजिस्टरs.
 *
 * Return: 0
 */
अटल पूर्णांक img_ascii_lcd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा img_ascii_lcd_ctx *ctx = platक्रमm_get_drvdata(pdev);

	device_हटाओ_file(&pdev->dev, &dev_attr_message);
	del_समयr_sync(&ctx->समयr);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver img_ascii_lcd_driver = अणु
	.driver = अणु
		.name		= "img-ascii-lcd",
		.of_match_table	= img_ascii_lcd_matches,
	पूर्ण,
	.probe	= img_ascii_lcd_probe,
	.हटाओ	= img_ascii_lcd_हटाओ,
पूर्ण;
module_platक्रमm_driver(img_ascii_lcd_driver);

MODULE_DESCRIPTION("Imagination Technologies ASCII LCD Display");
MODULE_AUTHOR("Paul Burton <paul.burton@mips.com>");
MODULE_LICENSE("GPL");
