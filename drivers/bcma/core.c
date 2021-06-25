<शैली गुरु>
/*
 * Broadcom specअगरic AMBA
 * Core ops
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */

#समावेश "bcma_private.h"
#समावेश <linux/export.h>
#समावेश <linux/bcma/bcma.h>

अटल bool bcma_core_रुको_value(काष्ठा bcma_device *core, u16 reg, u32 mask,
				 u32 value, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ deadline = jअगरfies + समयout;
	u32 val;

	करो अणु
		val = bcma_aपढ़ो32(core, reg);
		अगर ((val & mask) == value)
			वापस true;
		cpu_relax();
		udelay(10);
	पूर्ण जबतक (!समय_after_eq(jअगरfies, deadline));

	bcma_warn(core->bus, "Timeout waiting for register 0x%04X!\n", reg);

	वापस false;
पूर्ण

bool bcma_core_is_enabled(काष्ठा bcma_device *core)
अणु
	अगर ((bcma_aपढ़ो32(core, BCMA_IOCTL) & (BCMA_IOCTL_CLK | BCMA_IOCTL_FGC))
	    != BCMA_IOCTL_CLK)
		वापस false;
	अगर (bcma_aपढ़ो32(core, BCMA_RESET_CTL) & BCMA_RESET_CTL_RESET)
		वापस false;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_is_enabled);

व्योम bcma_core_disable(काष्ठा bcma_device *core, u32 flags)
अणु
	अगर (bcma_aपढ़ो32(core, BCMA_RESET_CTL) & BCMA_RESET_CTL_RESET)
		वापस;

	bcma_core_रुको_value(core, BCMA_RESET_ST, ~0, 0, 300);

	bcma_aग_लिखो32(core, BCMA_RESET_CTL, BCMA_RESET_CTL_RESET);
	bcma_aपढ़ो32(core, BCMA_RESET_CTL);
	udelay(1);

	bcma_aग_लिखो32(core, BCMA_IOCTL, flags);
	bcma_aपढ़ो32(core, BCMA_IOCTL);
	udelay(10);
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_disable);

पूर्णांक bcma_core_enable(काष्ठा bcma_device *core, u32 flags)
अणु
	bcma_core_disable(core, flags);

	bcma_aग_लिखो32(core, BCMA_IOCTL, (BCMA_IOCTL_CLK | BCMA_IOCTL_FGC | flags));
	bcma_aपढ़ो32(core, BCMA_IOCTL);

	bcma_aग_लिखो32(core, BCMA_RESET_CTL, 0);
	bcma_aपढ़ो32(core, BCMA_RESET_CTL);
	udelay(1);

	bcma_aग_लिखो32(core, BCMA_IOCTL, (BCMA_IOCTL_CLK | flags));
	bcma_aपढ़ो32(core, BCMA_IOCTL);
	udelay(1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_enable);

व्योम bcma_core_set_घड़ीmode(काष्ठा bcma_device *core,
			     क्रमागत bcma_clkmode clkmode)
अणु
	u16 i;

	WARN_ON(core->id.id != BCMA_CORE_CHIPCOMMON &&
		core->id.id != BCMA_CORE_PCIE &&
		core->id.id != BCMA_CORE_80211);

	चयन (clkmode) अणु
	हाल BCMA_CLKMODE_FAST:
		bcma_set32(core, BCMA_CLKCTLST, BCMA_CLKCTLST_FORCEHT);
		usleep_range(64, 300);
		क्रम (i = 0; i < 1500; i++) अणु
			अगर (bcma_पढ़ो32(core, BCMA_CLKCTLST) &
			    BCMA_CLKCTLST_HAVEHT) अणु
				i = 0;
				अवरोध;
			पूर्ण
			udelay(10);
		पूर्ण
		अगर (i)
			bcma_err(core->bus, "HT force timeout\n");
		अवरोध;
	हाल BCMA_CLKMODE_DYNAMIC:
		bcma_set32(core, BCMA_CLKCTLST, ~BCMA_CLKCTLST_FORCEHT);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_set_घड़ीmode);

व्योम bcma_core_pll_ctl(काष्ठा bcma_device *core, u32 req, u32 status, bool on)
अणु
	u16 i;

	WARN_ON(req & ~BCMA_CLKCTLST_EXTRESREQ);
	WARN_ON(status & ~BCMA_CLKCTLST_EXTRESST);

	अगर (on) अणु
		bcma_set32(core, BCMA_CLKCTLST, req);
		क्रम (i = 0; i < 10000; i++) अणु
			अगर ((bcma_पढ़ो32(core, BCMA_CLKCTLST) & status) ==
			    status) अणु
				i = 0;
				अवरोध;
			पूर्ण
			udelay(10);
		पूर्ण
		अगर (i)
			bcma_err(core->bus, "PLL enable timeout\n");
	पूर्ण अन्यथा अणु
		/*
		 * Mask the PLL but करोn't रुको क्रम it to be disabled. PLL may be
		 * shared between cores and will be still up अगर there is another
		 * core using it.
		 */
		bcma_mask32(core, BCMA_CLKCTLST, ~req);
		bcma_पढ़ो32(core, BCMA_CLKCTLST);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(bcma_core_pll_ctl);

u32 bcma_core_dma_translation(काष्ठा bcma_device *core)
अणु
	चयन (core->bus->hosttype) अणु
	हाल BCMA_HOSTTYPE_SOC:
		वापस 0;
	हाल BCMA_HOSTTYPE_PCI:
		अगर (bcma_aपढ़ो32(core, BCMA_IOST) & BCMA_IOST_DMA64)
			वापस BCMA_DMA_TRANSLATION_DMA64_CMT;
		अन्यथा
			वापस BCMA_DMA_TRANSLATION_DMA32_CMT;
	शेष:
		bcma_err(core->bus, "DMA translation unknown for host %d\n",
			 core->bus->hosttype);
	पूर्ण
	वापस BCMA_DMA_TRANSLATION_NONE;
पूर्ण
EXPORT_SYMBOL(bcma_core_dma_translation);
