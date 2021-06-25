<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * ChipCommon B Unit driver
 *
 * Copyright 2014, Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>

अटल bool bcma_रुको_reg(काष्ठा bcma_bus *bus, व्योम __iomem *addr, u32 mask,
			  u32 value, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + समयout;
	u32 val;

	करो अणु
		val = पढ़ोl(addr);
		अगर ((val & mask) == value)
			वापस true;
		cpu_relax();
		udelay(10);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	bcma_err(bus, "Timeout waiting for register %p\n", addr);

	वापस false;
पूर्ण

व्योम bcma_chipco_b_mii_ग_लिखो(काष्ठा bcma_drv_cc_b *ccb, u32 offset, u32 value)
अणु
	काष्ठा bcma_bus *bus = ccb->core->bus;
	व्योम __iomem *mii = ccb->mii;

	ग_लिखोl(offset, mii + BCMA_CCB_MII_MNG_CTL);
	bcma_रुको_reg(bus, mii + BCMA_CCB_MII_MNG_CTL, 0x0100, 0x0000, 100);
	ग_लिखोl(value, mii + BCMA_CCB_MII_MNG_CMD_DATA);
	bcma_रुको_reg(bus, mii + BCMA_CCB_MII_MNG_CTL, 0x0100, 0x0000, 100);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_chipco_b_mii_ग_लिखो);

पूर्णांक bcma_core_chipcommon_b_init(काष्ठा bcma_drv_cc_b *ccb)
अणु
	अगर (ccb->setup_करोne)
		वापस 0;

	ccb->setup_करोne = 1;
	ccb->mii = ioremap(ccb->core->addr_s[1], BCMA_CORE_SIZE);
	अगर (!ccb->mii)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम bcma_core_chipcommon_b_मुक्त(काष्ठा bcma_drv_cc_b *ccb)
अणु
	अगर (ccb->mii)
		iounmap(ccb->mii);
पूर्ण
