<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/***************************************************************************/

/*
 *	clk.c -- general ColdFire CPU kernel clk handling
 *
 *	Copyright (C) 2009, Greg Ungerer (gerg@snapgear.com)
 */

/***************************************************************************/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <यंत्र/coldfire.h>
#समावेश <यंत्र/mcfsim.h>
#समावेश <यंत्र/mcfclk.h>

अटल DEFINE_SPINLOCK(clk_lock);

#अगर_घोषित MCFPM_PPMCR0
/*
 *	For more advanced ColdFire parts that have घड़ीs that can be enabled
 *	we supply enable/disable functions. These must properly define their
 *	घड़ीs in their platक्रमm specअगरic code.
 */
व्योम __clk_init_enabled(काष्ठा clk *clk)
अणु
	clk->enabled = 1;
	clk->clk_ops->enable(clk);
पूर्ण

व्योम __clk_init_disabled(काष्ठा clk *clk)
अणु
	clk->enabled = 0;
	clk->clk_ops->disable(clk);
पूर्ण

अटल व्योम __clk_enable0(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोb(clk->slot, MCFPM_PPMCR0);
पूर्ण

अटल व्योम __clk_disable0(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोb(clk->slot, MCFPM_PPMSR0);
पूर्ण

काष्ठा clk_ops clk_ops0 = अणु
	.enable		= __clk_enable0,
	.disable	= __clk_disable0,
पूर्ण;

#अगर_घोषित MCFPM_PPMCR1
अटल व्योम __clk_enable1(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोb(clk->slot, MCFPM_PPMCR1);
पूर्ण

अटल व्योम __clk_disable1(काष्ठा clk *clk)
अणु
	__raw_ग_लिखोb(clk->slot, MCFPM_PPMSR1);
पूर्ण

काष्ठा clk_ops clk_ops1 = अणु
	.enable		= __clk_enable1,
	.disable	= __clk_disable1,
पूर्ण;
#पूर्ण_अगर /* MCFPM_PPMCR1 */
#पूर्ण_अगर /* MCFPM_PPMCR0 */

काष्ठा clk *clk_get(काष्ठा device *dev, स्थिर अक्षर *id)
अणु
	स्थिर अक्षर *clk_name = dev ? dev_name(dev) : id ? id : शून्य;
	काष्ठा clk *clk;
	अचिन्हित i;

	क्रम (i = 0; (clk = mcf_clks[i]) != शून्य; ++i)
		अगर (!म_भेद(clk->name, clk_name))
			वापस clk;
	pr_warn("clk_get: didn't find clock %s\n", clk_name);
	वापस ERR_PTR(-ENOENT);
पूर्ण
EXPORT_SYMBOL(clk_get);

पूर्णांक clk_enable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस -EINVAL;

	spin_lock_irqsave(&clk_lock, flags);
	अगर ((clk->enabled++ == 0) && clk->clk_ops)
		clk->clk_ops->enable(clk);
	spin_unlock_irqrestore(&clk_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_enable);

व्योम clk_disable(काष्ठा clk *clk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!clk)
		वापस;

	spin_lock_irqsave(&clk_lock, flags);
	अगर ((--clk->enabled == 0) && clk->clk_ops)
		clk->clk_ops->disable(clk);
	spin_unlock_irqrestore(&clk_lock, flags);
पूर्ण
EXPORT_SYMBOL(clk_disable);

व्योम clk_put(काष्ठा clk *clk)
अणु
	अगर (clk->enabled != 0)
		pr_warn("clk_put %s still enabled\n", clk->name);
पूर्ण
EXPORT_SYMBOL(clk_put);

अचिन्हित दीर्घ clk_get_rate(काष्ठा clk *clk)
अणु
	अगर (!clk)
		वापस 0;

	वापस clk->rate;
पूर्ण
EXPORT_SYMBOL(clk_get_rate);

/* dummy functions, should not be called */
दीर्घ clk_round_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_round_rate);

पूर्णांक clk_set_rate(काष्ठा clk *clk, अचिन्हित दीर्घ rate)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_rate);

पूर्णांक clk_set_parent(काष्ठा clk *clk, काष्ठा clk *parent)
अणु
	WARN_ON(clk);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(clk_set_parent);

काष्ठा clk *clk_get_parent(काष्ठा clk *clk)
अणु
	WARN_ON(clk);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(clk_get_parent);

/***************************************************************************/
