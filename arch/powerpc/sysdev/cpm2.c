<शैली गुरु>
/*
 * General Purpose functions क्रम the global management of the
 * 8260 Communication Processor Module.
 * Copyright (c) 1999-2001 Dan Malek <dan@embeddedalley.com>
 * Copyright (c) 2000 MontaVista Software, Inc (source@mvista.com)
 *	2.3.99 Updates
 *
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 * 	Merged to arch/घातerpc from arch/ppc/syslib/cpm2_common.c
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

/*
 *
 * In addition to the inभागidual control of the communication
 * channels, there are a few functions that globally affect the
 * communication processor.
 *
 * Buffer descriptors must be allocated from the dual ported memory
 * space.  The allocator क्रम that is here.  When the communication
 * process is reset, we reclaim the memory available.  There is
 * currently no deallocator क्रम this memory.
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/param.h>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mpc8260.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cpm2.h>
#समावेश <यंत्र/rheap.h>
#समावेश <यंत्र/fs_pd.h>

#समावेश <sysdev/fsl_soc.h>

cpm_cpm2_t __iomem *cpmp; /* Poपूर्णांकer to comm processor space */

/* We allocate this here because it is used almost exclusively क्रम
 * the communication processor devices.
 */
cpm2_map_t __iomem *cpm2_immr;
EXPORT_SYMBOL(cpm2_immr);

#घोषणा CPM_MAP_SIZE	(0x40000)	/* 256k - the PQ3 reserve this amount
					   of space क्रम CPM as it is larger
					   than on PQ2 */

व्योम __init cpm2_reset(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_85xx
	cpm2_immr = ioremap(get_immrbase() + 0x80000, CPM_MAP_SIZE);
#अन्यथा
	cpm2_immr = ioremap(get_immrbase(), CPM_MAP_SIZE);
#पूर्ण_अगर

	/* Tell everyone where the comm processor resides.
	 */
	cpmp = &cpm2_immr->im_cpm;

#अगर_अघोषित CONFIG_PPC_EARLY_DEBUG_CPM
	/* Reset the CPM.
	 */
	cpm_command(CPM_CR_RST, 0);
#पूर्ण_अगर
पूर्ण

अटल DEFINE_SPINLOCK(cmd_lock);

#घोषणा MAX_CR_CMD_LOOPS        10000

पूर्णांक cpm_command(u32 command, u8 opcode)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cmd_lock, flags);

	ret = 0;
	out_be32(&cpmp->cp_cpcr, command | opcode | CPM_CR_FLG);
	क्रम (i = 0; i < MAX_CR_CMD_LOOPS; i++)
		अगर ((in_be32(&cpmp->cp_cpcr) & CPM_CR_FLG) == 0)
			जाओ out;

	prपूर्णांकk(KERN_ERR "%s(): Not able to issue CPM command\n", __func__);
	ret = -EIO;
out:
	spin_unlock_irqrestore(&cmd_lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cpm_command);

/* Set a baud rate generator.  This needs lots of work.  There are
 * eight BRGs, which can be connected to the CPM channels or output
 * as घड़ीs.  The BRGs are in two dअगरferent block of पूर्णांकernal
 * memory mapped space.
 * The baud rate घड़ी is the प्रणाली घड़ी भागided by something.
 * It was set up दीर्घ ago during the initial boot phase and is
 * is given to us.
 * Baud rate घड़ीs are zero-based in the driver code (as that maps
 * to port numbers).  Documentation uses 1-based numbering.
 */
व्योम __cpm2_setbrg(uपूर्णांक brg, uपूर्णांक rate, uपूर्णांक clk, पूर्णांक भाग16, पूर्णांक src)
अणु
	u32 __iomem *bp;
	u32 val;

	/* This is good enough to get SMCs running.....
	*/
	अगर (brg < 4) अणु
		bp = cpm2_map_size(im_brgc1, 16);
	पूर्ण अन्यथा अणु
		bp = cpm2_map_size(im_brgc5, 16);
		brg -= 4;
	पूर्ण
	bp += brg;
	/* Round the घड़ी भागider to the nearest पूर्णांकeger. */
	val = (((clk * 2 / rate) - 1) & ~1) | CPM_BRG_EN | src;
	अगर (भाग16)
		val |= CPM_BRG_DIV16;

	out_be32(bp, val);
	cpm2_unmap(bp);
पूर्ण
EXPORT_SYMBOL(__cpm2_setbrg);

पूर्णांक cpm2_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी, पूर्णांक mode)
अणु
	पूर्णांक ret = 0;
	पूर्णांक shअगरt;
	पूर्णांक i, bits = 0;
	cpmux_t __iomem *im_cpmux;
	u32 __iomem *reg;
	u32 mask = 7;

	u8 clk_map[][3] = अणु
		अणुCPM_CLK_FCC1, CPM_BRG5, 0पूर्ण,
		अणुCPM_CLK_FCC1, CPM_BRG6, 1पूर्ण,
		अणुCPM_CLK_FCC1, CPM_BRG7, 2पूर्ण,
		अणुCPM_CLK_FCC1, CPM_BRG8, 3पूर्ण,
		अणुCPM_CLK_FCC1, CPM_CLK9, 4पूर्ण,
		अणुCPM_CLK_FCC1, CPM_CLK10, 5पूर्ण,
		अणुCPM_CLK_FCC1, CPM_CLK11, 6पूर्ण,
		अणुCPM_CLK_FCC1, CPM_CLK12, 7पूर्ण,
		अणुCPM_CLK_FCC2, CPM_BRG5, 0पूर्ण,
		अणुCPM_CLK_FCC2, CPM_BRG6, 1पूर्ण,
		अणुCPM_CLK_FCC2, CPM_BRG7, 2पूर्ण,
		अणुCPM_CLK_FCC2, CPM_BRG8, 3पूर्ण,
		अणुCPM_CLK_FCC2, CPM_CLK13, 4पूर्ण,
		अणुCPM_CLK_FCC2, CPM_CLK14, 5पूर्ण,
		अणुCPM_CLK_FCC2, CPM_CLK15, 6पूर्ण,
		अणुCPM_CLK_FCC2, CPM_CLK16, 7पूर्ण,
		अणुCPM_CLK_FCC3, CPM_BRG5, 0पूर्ण,
		अणुCPM_CLK_FCC3, CPM_BRG6, 1पूर्ण,
		अणुCPM_CLK_FCC3, CPM_BRG7, 2पूर्ण,
		अणुCPM_CLK_FCC3, CPM_BRG8, 3पूर्ण,
		अणुCPM_CLK_FCC3, CPM_CLK13, 4पूर्ण,
		अणुCPM_CLK_FCC3, CPM_CLK14, 5पूर्ण,
		अणुCPM_CLK_FCC3, CPM_CLK15, 6पूर्ण,
		अणुCPM_CLK_FCC3, CPM_CLK16, 7पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC1, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK11, 4पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK12, 5पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK3, 6पूर्ण,
		अणुCPM_CLK_SCC1, CPM_CLK4, 7पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC2, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK11, 4पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK12, 5पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK3, 6पूर्ण,
		अणुCPM_CLK_SCC2, CPM_CLK4, 7पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC3, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK5, 4पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK6, 5पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK7, 6पूर्ण,
		अणुCPM_CLK_SCC3, CPM_CLK8, 7पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG2, 1पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG3, 2पूर्ण,
		अणुCPM_CLK_SCC4, CPM_BRG4, 3पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK5, 4पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK6, 5पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK7, 6पूर्ण,
		अणुCPM_CLK_SCC4, CPM_CLK8, 7पूर्ण,
	पूर्ण;

	im_cpmux = cpm2_map(im_cpmux);

	चयन (target) अणु
	हाल CPM_CLK_SCC1:
		reg = &im_cpmux->cmx_scr;
		shअगरt = 24;
		अवरोध;
	हाल CPM_CLK_SCC2:
		reg = &im_cpmux->cmx_scr;
		shअगरt = 16;
		अवरोध;
	हाल CPM_CLK_SCC3:
		reg = &im_cpmux->cmx_scr;
		shअगरt = 8;
		अवरोध;
	हाल CPM_CLK_SCC4:
		reg = &im_cpmux->cmx_scr;
		shअगरt = 0;
		अवरोध;
	हाल CPM_CLK_FCC1:
		reg = &im_cpmux->cmx_fcr;
		shअगरt = 24;
		अवरोध;
	हाल CPM_CLK_FCC2:
		reg = &im_cpmux->cmx_fcr;
		shअगरt = 16;
		अवरोध;
	हाल CPM_CLK_FCC3:
		reg = &im_cpmux->cmx_fcr;
		shअगरt = 8;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "cpm2_clock_setup: invalid clock target\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(clk_map); i++) अणु
		अगर (clk_map[i][0] == target && clk_map[i][1] == घड़ी) अणु
			bits = clk_map[i][2];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(clk_map))
	    ret = -EINVAL;

	bits <<= shअगरt;
	mask <<= shअगरt;

	अगर (mode == CPM_CLK_RTX) अणु
		bits |= bits << 3;
		mask |= mask << 3;
	पूर्ण अन्यथा अगर (mode == CPM_CLK_RX) अणु
		bits <<= 3;
		mask <<= 3;
	पूर्ण

	out_be32(reg, (in_be32(reg) & ~mask) | bits);

	cpm2_unmap(im_cpmux);
	वापस ret;
पूर्ण

पूर्णांक cpm2_smc_clk_setup(क्रमागत cpm_clk_target target, पूर्णांक घड़ी)
अणु
	पूर्णांक ret = 0;
	पूर्णांक shअगरt;
	पूर्णांक i, bits = 0;
	cpmux_t __iomem *im_cpmux;
	u8 __iomem *reg;
	u8 mask = 3;

	u8 clk_map[][3] = अणु
		अणुCPM_CLK_SMC1, CPM_BRG1, 0पूर्ण,
		अणुCPM_CLK_SMC1, CPM_BRG7, 1पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK7, 2पूर्ण,
		अणुCPM_CLK_SMC1, CPM_CLK9, 3पूर्ण,
		अणुCPM_CLK_SMC2, CPM_BRG2, 0पूर्ण,
		अणुCPM_CLK_SMC2, CPM_BRG8, 1पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK4, 2पूर्ण,
		अणुCPM_CLK_SMC2, CPM_CLK15, 3पूर्ण,
	पूर्ण;

	im_cpmux = cpm2_map(im_cpmux);

	चयन (target) अणु
	हाल CPM_CLK_SMC1:
		reg = &im_cpmux->cmx_smr;
		mask = 3;
		shअगरt = 4;
		अवरोध;
	हाल CPM_CLK_SMC2:
		reg = &im_cpmux->cmx_smr;
		mask = 3;
		shअगरt = 0;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "cpm2_smc_clock_setup: invalid clock target\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(clk_map); i++) अणु
		अगर (clk_map[i][0] == target && clk_map[i][1] == घड़ी) अणु
			bits = clk_map[i][2];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == ARRAY_SIZE(clk_map))
	    ret = -EINVAL;

	bits <<= shअगरt;
	mask <<= shअगरt;

	out_8(reg, (in_8(reg) & ~mask) | bits);

	cpm2_unmap(im_cpmux);
	वापस ret;
पूर्ण

काष्ठा cpm2_ioports अणु
	u32 dir, par, sor, odr, dat;
	u32 res[3];
पूर्ण;

व्योम cpm2_set_pin(पूर्णांक port, पूर्णांक pin, पूर्णांक flags)
अणु
	काष्ठा cpm2_ioports __iomem *iop =
		(काष्ठा cpm2_ioports __iomem *)&cpm2_immr->im_ioport;

	pin = 1 << (31 - pin);

	अगर (flags & CPM_PIN_OUTPUT)
		setbits32(&iop[port].dir, pin);
	अन्यथा
		clrbits32(&iop[port].dir, pin);

	अगर (!(flags & CPM_PIN_GPIO))
		setbits32(&iop[port].par, pin);
	अन्यथा
		clrbits32(&iop[port].par, pin);

	अगर (flags & CPM_PIN_SECONDARY)
		setbits32(&iop[port].sor, pin);
	अन्यथा
		clrbits32(&iop[port].sor, pin);

	अगर (flags & CPM_PIN_OPENDRAIN)
		setbits32(&iop[port].odr, pin);
	अन्यथा
		clrbits32(&iop[port].odr, pin);
पूर्ण
