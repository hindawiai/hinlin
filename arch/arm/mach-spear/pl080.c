<शैली गुरु>
/*
 * arch/arm/plat-spear/pl080.c
 *
 * DMAC pl080 definitions क्रम SPEAr platक्रमm
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/amba/pl08x.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/bug.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock_types.h>
#समावेश <mach/spear.h>
#समावेश <mach/misc_regs.h>

अटल spinlock_t lock = __SPIN_LOCK_UNLOCKED(x);

काष्ठा अणु
	अचिन्हित अक्षर busy;
	अचिन्हित अक्षर val;
पूर्ण संकेतs[16] = अणुअणु0, 0पूर्ण, पूर्ण;

पूर्णांक pl080_get_संकेत(स्थिर काष्ठा pl08x_channel_data *cd)
अणु
	अचिन्हित पूर्णांक संकेत = cd->min_संकेत, val;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lock, flags);

	/* Return अगर संकेत is alपढ़ोy acquired by somebody अन्यथा */
	अगर (संकेतs[संकेत].busy &&
			(संकेतs[संकेत].val != cd->muxval)) अणु
		spin_unlock_irqrestore(&lock, flags);
		वापस -EBUSY;
	पूर्ण

	/* If acquiring क्रम the first समय, configure it */
	अगर (!संकेतs[संकेत].busy) अणु
		val = पढ़ोl(DMA_CHN_CFG);

		/*
		 * Each request line has two bits in DMA_CHN_CFG रेजिस्टर. To
		 * जाओ the bits of current request line, करो left shअगरt of
		 * value by 2 * संकेत number.
		 */
		val &= ~(0x3 << (संकेत * 2));
		val |= cd->muxval << (संकेत * 2);
		ग_लिखोl(val, DMA_CHN_CFG);
	पूर्ण

	संकेतs[संकेत].busy++;
	संकेतs[संकेत].val = cd->muxval;
	spin_unlock_irqrestore(&lock, flags);

	वापस संकेत;
पूर्ण

व्योम pl080_put_संकेत(स्थिर काष्ठा pl08x_channel_data *cd, पूर्णांक संकेत)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&lock, flags);

	/* अगर संकेत is not used */
	अगर (!संकेतs[संकेत].busy)
		BUG();

	संकेतs[संकेत].busy--;

	spin_unlock_irqrestore(&lock, flags);
पूर्ण
