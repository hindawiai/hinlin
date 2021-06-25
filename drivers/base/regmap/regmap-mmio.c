<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Register map access API - MMIO support
//
// Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

काष्ठा regmap_mmio_context अणु
	व्योम __iomem *regs;
	अचिन्हित val_bytes;
	bool relaxed_mmio;

	bool attached_clk;
	काष्ठा clk *clk;

	व्योम (*reg_ग_लिखो)(काष्ठा regmap_mmio_context *ctx,
			  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
	अचिन्हित पूर्णांक (*reg_पढ़ो)(काष्ठा regmap_mmio_context *ctx,
			         अचिन्हित पूर्णांक reg);
पूर्ण;

अटल पूर्णांक regmap_mmio_regbits_check(माप_प्रकार reg_bits)
अणु
	चयन (reg_bits) अणु
	हाल 8:
	हाल 16:
	हाल 32:
#अगर_घोषित CONFIG_64BIT
	हाल 64:
#पूर्ण_अगर
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक regmap_mmio_get_min_stride(माप_प्रकार val_bits)
अणु
	पूर्णांक min_stride;

	चयन (val_bits) अणु
	हाल 8:
		/* The core treats 0 as 1 */
		min_stride = 0;
		वापस 0;
	हाल 16:
		min_stride = 2;
		अवरोध;
	हाल 32:
		min_stride = 4;
		अवरोध;
#अगर_घोषित CONFIG_64BIT
	हाल 64:
		min_stride = 8;
		अवरोध;
#पूर्ण_अगर
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस min_stride;
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो8(काष्ठा regmap_mmio_context *ctx,
				अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	ग_लिखोb(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो8_relaxed(काष्ठा regmap_mmio_context *ctx,
				अचिन्हित पूर्णांक reg,
				अचिन्हित पूर्णांक val)
अणु
	ग_लिखोb_relaxed(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो16le(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोw(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो16le_relaxed(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोw_relaxed(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो16be(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ioग_लिखो16be(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो32le(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो32le_relaxed(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोl_relaxed(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो32be(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ioग_लिखो32be(val, ctx->regs + reg);
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल व्योम regmap_mmio_ग_लिखो64le(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोq(val, ctx->regs + reg);
पूर्ण

अटल व्योम regmap_mmio_ग_लिखो64le_relaxed(काष्ठा regmap_mmio_context *ctx,
				  अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक val)
अणु
	ग_लिखोq_relaxed(val, ctx->regs + reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक regmap_mmio_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा regmap_mmio_context *ctx = context;
	पूर्णांक ret;

	अगर (!IS_ERR(ctx->clk)) अणु
		ret = clk_enable(ctx->clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ctx->reg_ग_लिखो(ctx, reg, val);

	अगर (!IS_ERR(ctx->clk))
		clk_disable(ctx->clk);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो8(काष्ठा regmap_mmio_context *ctx,
				      अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो8_relaxed(काष्ठा regmap_mmio_context *ctx,
				      अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोb_relaxed(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो16le(काष्ठा regmap_mmio_context *ctx,
				         अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोw(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो16le_relaxed(काष्ठा regmap_mmio_context *ctx,
						 अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोw_relaxed(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो16be(काष्ठा regmap_mmio_context *ctx,
				         अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो16be(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो32le(काष्ठा regmap_mmio_context *ctx,
				         अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो32le_relaxed(काष्ठा regmap_mmio_context *ctx,
						 अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl_relaxed(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो32be(काष्ठा regmap_mmio_context *ctx,
				         अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32be(ctx->regs + reg);
पूर्ण

#अगर_घोषित CONFIG_64BIT
अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो64le(काष्ठा regmap_mmio_context *ctx,
				         अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोq(ctx->regs + reg);
पूर्ण

अटल अचिन्हित पूर्णांक regmap_mmio_पढ़ो64le_relaxed(काष्ठा regmap_mmio_context *ctx,
						 अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोq_relaxed(ctx->regs + reg);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक regmap_mmio_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा regmap_mmio_context *ctx = context;
	पूर्णांक ret;

	अगर (!IS_ERR(ctx->clk)) अणु
		ret = clk_enable(ctx->clk);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	*val = ctx->reg_पढ़ो(ctx, reg);

	अगर (!IS_ERR(ctx->clk))
		clk_disable(ctx->clk);

	वापस 0;
पूर्ण

अटल व्योम regmap_mmio_मुक्त_context(व्योम *context)
अणु
	काष्ठा regmap_mmio_context *ctx = context;

	अगर (!IS_ERR(ctx->clk)) अणु
		clk_unprepare(ctx->clk);
		अगर (!ctx->attached_clk)
			clk_put(ctx->clk);
	पूर्ण
	kमुक्त(context);
पूर्ण

अटल स्थिर काष्ठा regmap_bus regmap_mmio = अणु
	.fast_io = true,
	.reg_ग_लिखो = regmap_mmio_ग_लिखो,
	.reg_पढ़ो = regmap_mmio_पढ़ो,
	.मुक्त_context = regmap_mmio_मुक्त_context,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल काष्ठा regmap_mmio_context *regmap_mmio_gen_context(काष्ठा device *dev,
					स्थिर अक्षर *clk_id,
					व्योम __iomem *regs,
					स्थिर काष्ठा regmap_config *config)
अणु
	काष्ठा regmap_mmio_context *ctx;
	पूर्णांक min_stride;
	पूर्णांक ret;

	ret = regmap_mmio_regbits_check(config->reg_bits);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (config->pad_bits)
		वापस ERR_PTR(-EINVAL);

	min_stride = regmap_mmio_get_min_stride(config->val_bits);
	अगर (min_stride < 0)
		वापस ERR_PTR(min_stride);

	अगर (config->reg_stride < min_stride)
		वापस ERR_PTR(-EINVAL);

	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	ctx->regs = regs;
	ctx->val_bytes = config->val_bits / 8;
	ctx->relaxed_mmio = config->use_relaxed_mmio;
	ctx->clk = ERR_PTR(-ENODEV);

	चयन (regmap_get_val_endian(dev, &regmap_mmio, config)) अणु
	हाल REGMAP_ENDIAN_DEFAULT:
	हाल REGMAP_ENDIAN_LITTLE:
#अगर_घोषित __LITTLE_ENDIAN
	हाल REGMAP_ENDIAN_NATIVE:
#पूर्ण_अगर
		चयन (config->val_bits) अणु
		हाल 8:
			अगर (ctx->relaxed_mmio) अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो8_relaxed;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो8_relaxed;
			पूर्ण अन्यथा अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो8;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो8;
			पूर्ण
			अवरोध;
		हाल 16:
			अगर (ctx->relaxed_mmio) अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो16le_relaxed;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो16le_relaxed;
			पूर्ण अन्यथा अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो16le;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो16le;
			पूर्ण
			अवरोध;
		हाल 32:
			अगर (ctx->relaxed_mmio) अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो32le_relaxed;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो32le_relaxed;
			पूर्ण अन्यथा अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो32le;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो32le;
			पूर्ण
			अवरोध;
#अगर_घोषित CONFIG_64BIT
		हाल 64:
			अगर (ctx->relaxed_mmio) अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो64le_relaxed;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो64le_relaxed;
			पूर्ण अन्यथा अणु
				ctx->reg_पढ़ो = regmap_mmio_पढ़ो64le;
				ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो64le;
			पूर्ण
			अवरोध;
#पूर्ण_अगर
		शेष:
			ret = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
		अवरोध;
	हाल REGMAP_ENDIAN_BIG:
#अगर_घोषित __BIG_ENDIAN
	हाल REGMAP_ENDIAN_NATIVE:
#पूर्ण_अगर
		चयन (config->val_bits) अणु
		हाल 8:
			ctx->reg_पढ़ो = regmap_mmio_पढ़ो8;
			ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो8;
			अवरोध;
		हाल 16:
			ctx->reg_पढ़ो = regmap_mmio_पढ़ो16be;
			ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो16be;
			अवरोध;
		हाल 32:
			ctx->reg_पढ़ो = regmap_mmio_पढ़ो32be;
			ctx->reg_ग_लिखो = regmap_mmio_ग_लिखो32be;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	अगर (clk_id == शून्य)
		वापस ctx;

	ctx->clk = clk_get(dev, clk_id);
	अगर (IS_ERR(ctx->clk)) अणु
		ret = PTR_ERR(ctx->clk);
		जाओ err_मुक्त;
	पूर्ण

	ret = clk_prepare(ctx->clk);
	अगर (ret < 0) अणु
		clk_put(ctx->clk);
		जाओ err_मुक्त;
	पूर्ण

	वापस ctx;

err_मुक्त:
	kमुक्त(ctx);

	वापस ERR_PTR(ret);
पूर्ण

काष्ठा regmap *__regmap_init_mmio_clk(काष्ठा device *dev, स्थिर अक्षर *clk_id,
				      व्योम __iomem *regs,
				      स्थिर काष्ठा regmap_config *config,
				      काष्ठा lock_class_key *lock_key,
				      स्थिर अक्षर *lock_name)
अणु
	काष्ठा regmap_mmio_context *ctx;

	ctx = regmap_mmio_gen_context(dev, clk_id, regs, config);
	अगर (IS_ERR(ctx))
		वापस ERR_CAST(ctx);

	वापस __regmap_init(dev, &regmap_mmio, ctx, config,
			     lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__regmap_init_mmio_clk);

काष्ठा regmap *__devm_regmap_init_mmio_clk(काष्ठा device *dev,
					   स्थिर अक्षर *clk_id,
					   व्योम __iomem *regs,
					   स्थिर काष्ठा regmap_config *config,
					   काष्ठा lock_class_key *lock_key,
					   स्थिर अक्षर *lock_name)
अणु
	काष्ठा regmap_mmio_context *ctx;

	ctx = regmap_mmio_gen_context(dev, clk_id, regs, config);
	अगर (IS_ERR(ctx))
		वापस ERR_CAST(ctx);

	वापस __devm_regmap_init(dev, &regmap_mmio, ctx, config,
				  lock_key, lock_name);
पूर्ण
EXPORT_SYMBOL_GPL(__devm_regmap_init_mmio_clk);

पूर्णांक regmap_mmio_attach_clk(काष्ठा regmap *map, काष्ठा clk *clk)
अणु
	काष्ठा regmap_mmio_context *ctx = map->bus_context;

	ctx->clk = clk;
	ctx->attached_clk = true;

	वापस clk_prepare(ctx->clk);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_mmio_attach_clk);

व्योम regmap_mmio_detach_clk(काष्ठा regmap *map)
अणु
	काष्ठा regmap_mmio_context *ctx = map->bus_context;

	clk_unprepare(ctx->clk);

	ctx->attached_clk = false;
	ctx->clk = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_mmio_detach_clk);

MODULE_LICENSE("GPL v2");
