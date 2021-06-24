<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/log2.h>
#समावेश <bcm63xx_cpu.h>
#समावेश <bcm63xx_पन.स>
#समावेश <bcm63xx_regs.h>
#समावेश <bcm63xx_cs.h>

अटल DEFINE_SPINLOCK(bcm63xx_cs_lock);

/*
 * check अगर given chip select exists
 */
अटल पूर्णांक is_valid_cs(अचिन्हित पूर्णांक cs)
अणु
	अगर (cs > 6)
		वापस 0;
	वापस 1;
पूर्ण

/*
 * Configure chipselect base address and size (bytes).
 * Size must be a घातer of two between 8k and 256M.
 */
पूर्णांक bcm63xx_set_cs_base(अचिन्हित पूर्णांक cs, u32 base, अचिन्हित पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!is_valid_cs(cs))
		वापस -EINVAL;

	/* sanity check on size */
	अगर (size != roundup_घात_of_two(size))
		वापस -EINVAL;

	अगर (size < 8 * 1024 || size > 256 * 1024 * 1024)
		वापस -EINVAL;

	val = (base & MPI_CSBASE_BASE_MASK);
	/* 8k => 0 - 256M => 15 */
	val |= (ilog2(size) - ilog2(8 * 1024)) << MPI_CSBASE_SIZE_SHIFT;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	bcm_mpi_ग_लिखोl(val, MPI_CSBASE_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_set_cs_base);

/*
 * configure chipselect timing (ns)
 */
पूर्णांक bcm63xx_set_cs_timing(अचिन्हित पूर्णांक cs, अचिन्हित पूर्णांक रुको,
			   अचिन्हित पूर्णांक setup, अचिन्हित पूर्णांक hold)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!is_valid_cs(cs))
		वापस -EINVAL;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	val = bcm_mpi_पढ़ोl(MPI_CSCTL_REG(cs));
	val &= ~(MPI_CSCTL_WAIT_MASK);
	val &= ~(MPI_CSCTL_SETUP_MASK);
	val &= ~(MPI_CSCTL_HOLD_MASK);
	val |= रुको << MPI_CSCTL_WAIT_SHIFT;
	val |= setup << MPI_CSCTL_SETUP_SHIFT;
	val |= hold << MPI_CSCTL_HOLD_SHIFT;
	bcm_mpi_ग_लिखोl(val, MPI_CSCTL_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_set_cs_timing);

/*
 * configure other chipselect parameter (data bus size, ...)
 */
पूर्णांक bcm63xx_set_cs_param(अचिन्हित पूर्णांक cs, u32 params)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!is_valid_cs(cs))
		वापस -EINVAL;

	/* none of this fields apply to pcmcia */
	अगर (cs == MPI_CS_PCMCIA_COMMON ||
	    cs == MPI_CS_PCMCIA_ATTR ||
	    cs == MPI_CS_PCMCIA_IO)
		वापस -EINVAL;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	val = bcm_mpi_पढ़ोl(MPI_CSCTL_REG(cs));
	val &= ~(MPI_CSCTL_DATA16_MASK);
	val &= ~(MPI_CSCTL_SYNCMODE_MASK);
	val &= ~(MPI_CSCTL_TSIZE_MASK);
	val &= ~(MPI_CSCTL_ENDIANSWAP_MASK);
	val |= params;
	bcm_mpi_ग_लिखोl(val, MPI_CSCTL_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);

	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_set_cs_param);

/*
 * set cs status (enable/disable)
 */
पूर्णांक bcm63xx_set_cs_status(अचिन्हित पूर्णांक cs, पूर्णांक enable)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!is_valid_cs(cs))
		वापस -EINVAL;

	spin_lock_irqsave(&bcm63xx_cs_lock, flags);
	val = bcm_mpi_पढ़ोl(MPI_CSCTL_REG(cs));
	अगर (enable)
		val |= MPI_CSCTL_ENABLE_MASK;
	अन्यथा
		val &= ~MPI_CSCTL_ENABLE_MASK;
	bcm_mpi_ग_लिखोl(val, MPI_CSCTL_REG(cs));
	spin_unlock_irqrestore(&bcm63xx_cs_lock, flags);
	वापस 0;
पूर्ण

EXPORT_SYMBOL(bcm63xx_set_cs_status);
