<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014 Intel Corporation
 *
 * Adjustable fractional भागider घड़ी implementation.
 * Output rate = (m / n) * parent_rate.
 * Uses rational best approximation algorithm.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/rational.h>

अटल अंतरभूत u32 clk_fd_पढ़ोl(काष्ठा clk_fractional_भागider *fd)
अणु
	अगर (fd->flags & CLK_FRAC_DIVIDER_BIG_ENDIAN)
		वापस ioपढ़ो32be(fd->reg);

	वापस पढ़ोl(fd->reg);
पूर्ण

अटल अंतरभूत व्योम clk_fd_ग_लिखोl(काष्ठा clk_fractional_भागider *fd, u32 val)
अणु
	अगर (fd->flags & CLK_FRAC_DIVIDER_BIG_ENDIAN)
		ioग_लिखो32be(val, fd->reg);
	अन्यथा
		ग_लिखोl(val, fd->reg);
पूर्ण

अटल अचिन्हित दीर्घ clk_fd_recalc_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fractional_भागider *fd = to_clk_fd(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ m, n;
	u32 val;
	u64 ret;

	अगर (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	अन्यथा
		__acquire(fd->lock);

	val = clk_fd_पढ़ोl(fd);

	अगर (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	अन्यथा
		__release(fd->lock);

	m = (val & fd->mmask) >> fd->mshअगरt;
	n = (val & fd->nmask) >> fd->nshअगरt;

	अगर (fd->flags & CLK_FRAC_DIVIDER_ZERO_BASED) अणु
		m++;
		n++;
	पूर्ण

	अगर (!n || !m)
		वापस parent_rate;

	ret = (u64)parent_rate * m;
	करो_भाग(ret, n);

	वापस ret;
पूर्ण

अटल व्योम clk_fd_general_approximation(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					 अचिन्हित दीर्घ *parent_rate,
					 अचिन्हित दीर्घ *m, अचिन्हित दीर्घ *n)
अणु
	काष्ठा clk_fractional_भागider *fd = to_clk_fd(hw);
	अचिन्हित दीर्घ scale;

	/*
	 * Get rate बंदr to *parent_rate to guarantee there is no overflow
	 * क्रम m and n. In the result it will be the nearest rate left shअगरted
	 * by (scale - fd->nwidth) bits.
	 */
	scale = fls_दीर्घ(*parent_rate / rate - 1);
	अगर (scale > fd->nwidth)
		rate <<= scale - fd->nwidth;

	rational_best_approximation(rate, *parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			m, n);
पूर्ण

अटल दीर्घ clk_fd_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			      अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा clk_fractional_भागider *fd = to_clk_fd(hw);
	अचिन्हित दीर्घ m, n;
	u64 ret;

	अगर (!rate || (!clk_hw_can_set_rate_parent(hw) && rate >= *parent_rate))
		वापस *parent_rate;

	अगर (fd->approximation)
		fd->approximation(hw, rate, parent_rate, &m, &n);
	अन्यथा
		clk_fd_general_approximation(hw, rate, parent_rate, &m, &n);

	ret = (u64)*parent_rate * m;
	करो_भाग(ret, n);

	वापस ret;
पूर्ण

अटल पूर्णांक clk_fd_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fractional_भागider *fd = to_clk_fd(hw);
	अचिन्हित दीर्घ flags = 0;
	अचिन्हित दीर्घ m, n;
	u32 val;

	rational_best_approximation(rate, parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			&m, &n);

	अगर (fd->flags & CLK_FRAC_DIVIDER_ZERO_BASED) अणु
		m--;
		n--;
	पूर्ण

	अगर (fd->lock)
		spin_lock_irqsave(fd->lock, flags);
	अन्यथा
		__acquire(fd->lock);

	val = clk_fd_पढ़ोl(fd);
	val &= ~(fd->mmask | fd->nmask);
	val |= (m << fd->mshअगरt) | (n << fd->nshअगरt);
	clk_fd_ग_लिखोl(fd, val);

	अगर (fd->lock)
		spin_unlock_irqrestore(fd->lock, flags);
	अन्यथा
		__release(fd->lock);

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_fractional_भागider_ops = अणु
	.recalc_rate = clk_fd_recalc_rate,
	.round_rate = clk_fd_round_rate,
	.set_rate = clk_fd_set_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_fractional_भागider_ops);

काष्ठा clk_hw *clk_hw_रेजिस्टर_fractional_भागider(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 mshअगरt, u8 mwidth, u8 nshअगरt, u8 nwidth,
		u8 clk_भागider_flags, spinlock_t *lock)
अणु
	काष्ठा clk_fractional_भागider *fd;
	काष्ठा clk_init_data init;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	fd = kzalloc(माप(*fd), GFP_KERNEL);
	अगर (!fd)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fractional_भागider_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.num_parents = parent_name ? 1 : 0;

	fd->reg = reg;
	fd->mshअगरt = mshअगरt;
	fd->mwidth = mwidth;
	fd->mmask = GENMASK(mwidth - 1, 0) << mshअगरt;
	fd->nshअगरt = nshअगरt;
	fd->nwidth = nwidth;
	fd->nmask = GENMASK(nwidth - 1, 0) << nshअगरt;
	fd->flags = clk_भागider_flags;
	fd->lock = lock;
	fd->hw.init = &init;

	hw = &fd->hw;
	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		kमुक्त(fd);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_रेजिस्टर_fractional_भागider);

काष्ठा clk *clk_रेजिस्टर_fractional_भागider(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		व्योम __iomem *reg, u8 mshअगरt, u8 mwidth, u8 nshअगरt, u8 nwidth,
		u8 clk_भागider_flags, spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_fractional_भागider(dev, name, parent_name, flags,
			reg, mshअगरt, mwidth, nshअगरt, nwidth, clk_भागider_flags,
			lock);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_fractional_भागider);

व्योम clk_hw_unरेजिस्टर_fractional_भागider(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_fractional_भागider *fd;

	fd = to_clk_fd(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(fd);
पूर्ण
