<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2012 Jonas Gorski <jonas.gorski@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_reset.h>

#घोषणा __GEN_RESET_BITS_TABLE(__cpu)					\
	[BCM63XX_RESET_SPI]		= BCM## __cpu ##_RESET_SPI,	\
	[BCM63XX_RESET_ENET]		= BCM## __cpu ##_RESET_ENET,	\
	[BCM63XX_RESET_USBH]		= BCM## __cpu ##_RESET_USBH,	\
	[BCM63XX_RESET_USBD]		= BCM## __cpu ##_RESET_USBD,	\
	[BCM63XX_RESET_DSL]		= BCM## __cpu ##_RESET_DSL,	\
	[BCM63XX_RESET_SAR]		= BCM## __cpu ##_RESET_SAR,	\
	[BCM63XX_RESET_EPHY]		= BCM## __cpu ##_RESET_EPHY,	\
	[BCM63XX_RESET_ENETSW]		= BCM## __cpu ##_RESET_ENETSW,	\
	[BCM63XX_RESET_PCM]		= BCM## __cpu ##_RESET_PCM,	\
	[BCM63XX_RESET_MPI]		= BCM## __cpu ##_RESET_MPI,	\
	[BCM63XX_RESET_PCIE]		= BCM## __cpu ##_RESET_PCIE,	\
	[BCM63XX_RESET_PCIE_EXT]	= BCM## __cpu ##_RESET_PCIE_EXT,

#घोषणा BCM3368_RESET_SPI	SOFTRESET_3368_SPI_MASK
#घोषणा BCM3368_RESET_ENET	SOFTRESET_3368_ENET_MASK
#घोषणा BCM3368_RESET_USBH	0
#घोषणा BCM3368_RESET_USBD	SOFTRESET_3368_USBS_MASK
#घोषणा BCM3368_RESET_DSL	0
#घोषणा BCM3368_RESET_SAR	0
#घोषणा BCM3368_RESET_EPHY	SOFTRESET_3368_EPHY_MASK
#घोषणा BCM3368_RESET_ENETSW	0
#घोषणा BCM3368_RESET_PCM	SOFTRESET_3368_PCM_MASK
#घोषणा BCM3368_RESET_MPI	SOFTRESET_3368_MPI_MASK
#घोषणा BCM3368_RESET_PCIE	0
#घोषणा BCM3368_RESET_PCIE_EXT	0

#घोषणा BCM6328_RESET_SPI	SOFTRESET_6328_SPI_MASK
#घोषणा BCM6328_RESET_ENET	0
#घोषणा BCM6328_RESET_USBH	SOFTRESET_6328_USBH_MASK
#घोषणा BCM6328_RESET_USBD	SOFTRESET_6328_USBS_MASK
#घोषणा BCM6328_RESET_DSL	0
#घोषणा BCM6328_RESET_SAR	SOFTRESET_6328_SAR_MASK
#घोषणा BCM6328_RESET_EPHY	SOFTRESET_6328_EPHY_MASK
#घोषणा BCM6328_RESET_ENETSW	SOFTRESET_6328_ENETSW_MASK
#घोषणा BCM6328_RESET_PCM	SOFTRESET_6328_PCM_MASK
#घोषणा BCM6328_RESET_MPI	0
#घोषणा BCM6328_RESET_PCIE	\
				(SOFTRESET_6328_PCIE_MASK |		\
				 SOFTRESET_6328_PCIE_CORE_MASK |	\
				 SOFTRESET_6328_PCIE_HARD_MASK)
#घोषणा BCM6328_RESET_PCIE_EXT	SOFTRESET_6328_PCIE_EXT_MASK

#घोषणा BCM6338_RESET_SPI	SOFTRESET_6338_SPI_MASK
#घोषणा BCM6338_RESET_ENET	SOFTRESET_6338_ENET_MASK
#घोषणा BCM6338_RESET_USBH	SOFTRESET_6338_USBH_MASK
#घोषणा BCM6338_RESET_USBD	SOFTRESET_6338_USBS_MASK
#घोषणा BCM6338_RESET_DSL	SOFTRESET_6338_ADSL_MASK
#घोषणा BCM6338_RESET_SAR	SOFTRESET_6338_SAR_MASK
#घोषणा BCM6338_RESET_EPHY	0
#घोषणा BCM6338_RESET_ENETSW	0
#घोषणा BCM6338_RESET_PCM	0
#घोषणा BCM6338_RESET_MPI	0
#घोषणा BCM6338_RESET_PCIE	0
#घोषणा BCM6338_RESET_PCIE_EXT	0

#घोषणा BCM6348_RESET_SPI	SOFTRESET_6348_SPI_MASK
#घोषणा BCM6348_RESET_ENET	SOFTRESET_6348_ENET_MASK
#घोषणा BCM6348_RESET_USBH	SOFTRESET_6348_USBH_MASK
#घोषणा BCM6348_RESET_USBD	SOFTRESET_6348_USBS_MASK
#घोषणा BCM6348_RESET_DSL	SOFTRESET_6348_ADSL_MASK
#घोषणा BCM6348_RESET_SAR	SOFTRESET_6348_SAR_MASK
#घोषणा BCM6348_RESET_EPHY	0
#घोषणा BCM6348_RESET_ENETSW	0
#घोषणा BCM6348_RESET_PCM	0
#घोषणा BCM6348_RESET_MPI	0
#घोषणा BCM6348_RESET_PCIE	0
#घोषणा BCM6348_RESET_PCIE_EXT	0

#घोषणा BCM6358_RESET_SPI	SOFTRESET_6358_SPI_MASK
#घोषणा BCM6358_RESET_ENET	SOFTRESET_6358_ENET_MASK
#घोषणा BCM6358_RESET_USBH	SOFTRESET_6358_USBH_MASK
#घोषणा BCM6358_RESET_USBD	0
#घोषणा BCM6358_RESET_DSL	SOFTRESET_6358_ADSL_MASK
#घोषणा BCM6358_RESET_SAR	SOFTRESET_6358_SAR_MASK
#घोषणा BCM6358_RESET_EPHY	SOFTRESET_6358_EPHY_MASK
#घोषणा BCM6358_RESET_ENETSW	0
#घोषणा BCM6358_RESET_PCM	SOFTRESET_6358_PCM_MASK
#घोषणा BCM6358_RESET_MPI	SOFTRESET_6358_MPI_MASK
#घोषणा BCM6358_RESET_PCIE	0
#घोषणा BCM6358_RESET_PCIE_EXT	0

#घोषणा BCM6362_RESET_SPI	SOFTRESET_6362_SPI_MASK
#घोषणा BCM6362_RESET_ENET	0
#घोषणा BCM6362_RESET_USBH	SOFTRESET_6362_USBH_MASK
#घोषणा BCM6362_RESET_USBD	SOFTRESET_6362_USBS_MASK
#घोषणा BCM6362_RESET_DSL	0
#घोषणा BCM6362_RESET_SAR	SOFTRESET_6362_SAR_MASK
#घोषणा BCM6362_RESET_EPHY	SOFTRESET_6362_EPHY_MASK
#घोषणा BCM6362_RESET_ENETSW	SOFTRESET_6362_ENETSW_MASK
#घोषणा BCM6362_RESET_PCM	SOFTRESET_6362_PCM_MASK
#घोषणा BCM6362_RESET_MPI	0
#घोषणा BCM6362_RESET_PCIE      (SOFTRESET_6362_PCIE_MASK | \
				 SOFTRESET_6362_PCIE_CORE_MASK)
#घोषणा BCM6362_RESET_PCIE_EXT	SOFTRESET_6362_PCIE_EXT_MASK

#घोषणा BCM6368_RESET_SPI	SOFTRESET_6368_SPI_MASK
#घोषणा BCM6368_RESET_ENET	0
#घोषणा BCM6368_RESET_USBH	SOFTRESET_6368_USBH_MASK
#घोषणा BCM6368_RESET_USBD	SOFTRESET_6368_USBS_MASK
#घोषणा BCM6368_RESET_DSL	0
#घोषणा BCM6368_RESET_SAR	SOFTRESET_6368_SAR_MASK
#घोषणा BCM6368_RESET_EPHY	SOFTRESET_6368_EPHY_MASK
#घोषणा BCM6368_RESET_ENETSW	SOFTRESET_6368_ENETSW_MASK
#घोषणा BCM6368_RESET_PCM	SOFTRESET_6368_PCM_MASK
#घोषणा BCM6368_RESET_MPI	SOFTRESET_6368_MPI_MASK
#घोषणा BCM6368_RESET_PCIE	0
#घोषणा BCM6368_RESET_PCIE_EXT	0

/*
 * core reset bits
 */
अटल स्थिर u32 bcm3368_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(3368)
पूर्ण;

अटल स्थिर u32 bcm6328_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6328)
पूर्ण;

अटल स्थिर u32 bcm6338_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6338)
पूर्ण;

अटल स्थिर u32 bcm6348_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6348)
पूर्ण;

अटल स्थिर u32 bcm6358_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6358)
पूर्ण;

अटल स्थिर u32 bcm6362_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6362)
पूर्ण;

अटल स्थिर u32 bcm6368_reset_bits[] = अणु
	__GEN_RESET_BITS_TABLE(6368)
पूर्ण;

स्थिर u32 *bcm63xx_reset_bits;
अटल पूर्णांक reset_reg;

अटल पूर्णांक __init bcm63xx_reset_bits_init(व्योम)
अणु
	अगर (BCMCPU_IS_3368()) अणु
		reset_reg = PERF_SOFTRESET_6358_REG;
		bcm63xx_reset_bits = bcm3368_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6328()) अणु
		reset_reg = PERF_SOFTRESET_6328_REG;
		bcm63xx_reset_bits = bcm6328_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6338()) अणु
		reset_reg = PERF_SOFTRESET_REG;
		bcm63xx_reset_bits = bcm6338_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6348()) अणु
		reset_reg = PERF_SOFTRESET_REG;
		bcm63xx_reset_bits = bcm6348_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6358()) अणु
		reset_reg = PERF_SOFTRESET_6358_REG;
		bcm63xx_reset_bits = bcm6358_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6362()) अणु
		reset_reg = PERF_SOFTRESET_6362_REG;
		bcm63xx_reset_bits = bcm6362_reset_bits;
	पूर्ण अन्यथा अगर (BCMCPU_IS_6368()) अणु
		reset_reg = PERF_SOFTRESET_6368_REG;
		bcm63xx_reset_bits = bcm6368_reset_bits;
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_SPINLOCK(reset_mutex);

अटल व्योम __bcm63xx_core_set_reset(u32 mask, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!mask)
		वापस;

	spin_lock_irqsave(&reset_mutex, flags);
	val = bcm_perf_पढ़ोl(reset_reg);

	अगर (enable)
		val &= ~mask;
	अन्यथा
		val |= mask;

	bcm_perf_ग_लिखोl(val, reset_reg);
	spin_unlock_irqrestore(&reset_mutex, flags);
पूर्ण

व्योम bcm63xx_core_set_reset(क्रमागत bcm63xx_core_reset core, पूर्णांक reset)
अणु
	__bcm63xx_core_set_reset(bcm63xx_reset_bits[core], reset);
पूर्ण
EXPORT_SYMBOL(bcm63xx_core_set_reset);

postcore_initcall(bcm63xx_reset_bits_init);
