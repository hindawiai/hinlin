<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This is a combined i2c adapter and algorithm driver क्रम the
 * MPC107/Tsi107 PowerPC northbridge and processors that include
 * the same I2C unit (8240, 8245, 85xx).
 *
 * Copyright (C) 2003-2004 Humboldt Solutions Ltd, adrian@humboldt.co.uk
 * Copyright (C) 2021 Allied Telesis Lअसल
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/fsl_devices.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mpc52xx.h>
#समावेश <यंत्र/mpc85xx.h>
#समावेश <sysdev/fsl_soc.h>

#घोषणा DRV_NAME "mpc-i2c"

#घोषणा MPC_I2C_CLOCK_LEGACY   0
#घोषणा MPC_I2C_CLOCK_PRESERVE (~0U)

#घोषणा MPC_I2C_FDR   0x04
#घोषणा MPC_I2C_CR    0x08
#घोषणा MPC_I2C_SR    0x0c
#घोषणा MPC_I2C_DR    0x10
#घोषणा MPC_I2C_DFSRR 0x14

#घोषणा CCR_MEN  0x80
#घोषणा CCR_MIEN 0x40
#घोषणा CCR_MSTA 0x20
#घोषणा CCR_MTX  0x10
#घोषणा CCR_TXAK 0x08
#घोषणा CCR_RSTA 0x04
#घोषणा CCR_RSVD 0x02

#घोषणा CSR_MCF  0x80
#घोषणा CSR_MAAS 0x40
#घोषणा CSR_MBB  0x20
#घोषणा CSR_MAL  0x10
#घोषणा CSR_SRW  0x04
#घोषणा CSR_MIF  0x02
#घोषणा CSR_RXAK 0x01

क्रमागत mpc_i2c_action अणु
	MPC_I2C_ACTION_START = 1,
	MPC_I2C_ACTION_RESTART,
	MPC_I2C_ACTION_READ_BEGIN,
	MPC_I2C_ACTION_READ_BYTE,
	MPC_I2C_ACTION_WRITE,
	MPC_I2C_ACTION_STOP,

	__MPC_I2C_ACTION_CNT
पूर्ण;

अटल स्थिर अक्षर * स्थिर action_str[] = अणु
	"invalid",
	"start",
	"restart",
	"read begin",
	"read",
	"write",
	"stop",
पूर्ण;

अटल_निश्चित(ARRAY_SIZE(action_str) == __MPC_I2C_ACTION_CNT);

काष्ठा mpc_i2c अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	u32 पूर्णांकerrupt;
	रुको_queue_head_t रुकोq;
	spinlock_t lock;
	काष्ठा i2c_adapter adap;
	पूर्णांक irq;
	u32 real_clk;
	u8 fdr, dfsrr;
	काष्ठा clk *clk_per;
	u32 cntl_bits;
	क्रमागत mpc_i2c_action action;
	काष्ठा i2c_msg *msgs;
	पूर्णांक num_msgs;
	पूर्णांक curr_msg;
	u32 byte_posn;
	u32 block;
	पूर्णांक rc;
	पूर्णांक expect_rxack;
	bool has_errata_A004447;
पूर्ण;

काष्ठा mpc_i2c_भागider अणु
	u16 भागider;
	u16 fdr;	/* including dfsrr */
पूर्ण;

काष्ठा mpc_i2c_data अणु
	व्योम (*setup)(काष्ठा device_node *node, काष्ठा mpc_i2c *i2c, u32 घड़ी);
पूर्ण;

अटल अंतरभूत व्योम ग_लिखोccr(काष्ठा mpc_i2c *i2c, u32 x)
अणु
	ग_लिखोb(x, i2c->base + MPC_I2C_CR);
पूर्ण

/* Someबार 9th घड़ी pulse isn't generated, and slave doesn't release
 * the bus, because it wants to send ACK.
 * Following sequence of enabling/disabling and sending start/stop generates
 * the 9 pulses, so it's all OK.
 */
अटल व्योम mpc_i2c_fixup(काष्ठा mpc_i2c *i2c)
अणु
	पूर्णांक k;
	u32 delay_val = 1000000 / i2c->real_clk + 1;

	अगर (delay_val < 2)
		delay_val = 2;

	क्रम (k = 9; k; k--) अणु
		ग_लिखोccr(i2c, 0);
		ग_लिखोccr(i2c, CCR_MSTA | CCR_MTX | CCR_MEN);
		पढ़ोb(i2c->base + MPC_I2C_DR);
		ग_लिखोccr(i2c, CCR_MEN);
		udelay(delay_val << 1);
	पूर्ण
पूर्ण

अटल पूर्णांक i2c_mpc_रुको_sr(काष्ठा mpc_i2c *i2c, पूर्णांक mask)
अणु
	व्योम __iomem *addr = i2c->base + MPC_I2C_SR;
	u8 val;

	वापस पढ़ोb_poll_समयout(addr, val, val & mask, 0, 100);
पूर्ण

/*
 * Workaround क्रम Erratum A004447. From the P2040CE Rev Q
 *
 * 1.  Set up the frequency भागider and sampling rate.
 * 2.  I2CCR - a0h
 * 3.  Poll क्रम I2CSR[MBB] to get set.
 * 4.  If I2CSR[MAL] is set (an indication that SDA is stuck low), then go to
 *     step 5. If MAL is not set, then go to step 13.
 * 5.  I2CCR - 00h
 * 6.  I2CCR - 22h
 * 7.  I2CCR - a2h
 * 8.  Poll क्रम I2CSR[MBB] to get set.
 * 9.  Issue पढ़ो to I2CDR.
 * 10. Poll क्रम I2CSR[MIF] to be set.
 * 11. I2CCR - 82h
 * 12. Workaround complete. Skip the next steps.
 * 13. Issue पढ़ो to I2CDR.
 * 14. Poll क्रम I2CSR[MIF] to be set.
 * 15. I2CCR - 80h
 */
अटल व्योम mpc_i2c_fixup_A004447(काष्ठा mpc_i2c *i2c)
अणु
	पूर्णांक ret;
	u32 val;

	ग_लिखोccr(i2c, CCR_MEN | CCR_MSTA);
	ret = i2c_mpc_रुको_sr(i2c, CSR_MBB);
	अगर (ret) अणु
		dev_err(i2c->dev, "timeout waiting for CSR_MBB\n");
		वापस;
	पूर्ण

	val = पढ़ोb(i2c->base + MPC_I2C_SR);

	अगर (val & CSR_MAL) अणु
		ग_लिखोccr(i2c, 0x00);
		ग_लिखोccr(i2c, CCR_MSTA | CCR_RSVD);
		ग_लिखोccr(i2c, CCR_MEN | CCR_MSTA | CCR_RSVD);
		ret = i2c_mpc_रुको_sr(i2c, CSR_MBB);
		अगर (ret) अणु
			dev_err(i2c->dev, "timeout waiting for CSR_MBB\n");
			वापस;
		पूर्ण
		val = पढ़ोb(i2c->base + MPC_I2C_DR);
		ret = i2c_mpc_रुको_sr(i2c, CSR_MIF);
		अगर (ret) अणु
			dev_err(i2c->dev, "timeout waiting for CSR_MIF\n");
			वापस;
		पूर्ण
		ग_लिखोccr(i2c, CCR_MEN | CCR_RSVD);
	पूर्ण अन्यथा अणु
		val = पढ़ोb(i2c->base + MPC_I2C_DR);
		ret = i2c_mpc_रुको_sr(i2c, CSR_MIF);
		अगर (ret) अणु
			dev_err(i2c->dev, "timeout waiting for CSR_MIF\n");
			वापस;
		पूर्ण
		ग_लिखोccr(i2c, CCR_MEN);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_PPC_MPC52xx) || defined(CONFIG_PPC_MPC512x)
अटल स्थिर काष्ठा mpc_i2c_भागider mpc_i2c_भागiders_52xx[] = अणु
	अणु20, 0x20पूर्ण, अणु22, 0x21पूर्ण, अणु24, 0x22पूर्ण, अणु26, 0x23पूर्ण,
	अणु28, 0x24पूर्ण, अणु30, 0x01पूर्ण, अणु32, 0x25पूर्ण, अणु34, 0x02पूर्ण,
	अणु36, 0x26पूर्ण, अणु40, 0x27पूर्ण, अणु44, 0x04पूर्ण, अणु48, 0x28पूर्ण,
	अणु52, 0x63पूर्ण, अणु56, 0x29पूर्ण, अणु60, 0x41पूर्ण, अणु64, 0x2aपूर्ण,
	अणु68, 0x07पूर्ण, अणु72, 0x2bपूर्ण, अणु80, 0x2cपूर्ण, अणु88, 0x09पूर्ण,
	अणु96, 0x2dपूर्ण, अणु104, 0x0aपूर्ण, अणु112, 0x2eपूर्ण, अणु120, 0x81पूर्ण,
	अणु128, 0x2fपूर्ण, अणु136, 0x47पूर्ण, अणु144, 0x0cपूर्ण, अणु160, 0x30पूर्ण,
	अणु176, 0x49पूर्ण, अणु192, 0x31पूर्ण, अणु208, 0x4aपूर्ण, अणु224, 0x32पूर्ण,
	अणु240, 0x0fपूर्ण, अणु256, 0x33पूर्ण, अणु272, 0x87पूर्ण, अणु288, 0x10पूर्ण,
	अणु320, 0x34पूर्ण, अणु352, 0x89पूर्ण, अणु384, 0x35पूर्ण, अणु416, 0x8aपूर्ण,
	अणु448, 0x36पूर्ण, अणु480, 0x13पूर्ण, अणु512, 0x37पूर्ण, अणु576, 0x14पूर्ण,
	अणु640, 0x38पूर्ण, अणु768, 0x39पूर्ण, अणु896, 0x3aपूर्ण, अणु960, 0x17पूर्ण,
	अणु1024, 0x3bपूर्ण, अणु1152, 0x18पूर्ण, अणु1280, 0x3cपूर्ण, अणु1536, 0x3dपूर्ण,
	अणु1792, 0x3eपूर्ण, अणु1920, 0x1bपूर्ण, अणु2048, 0x3fपूर्ण, अणु2304, 0x1cपूर्ण,
	अणु2560, 0x1dपूर्ण, अणु3072, 0x1eपूर्ण, अणु3584, 0x7eपूर्ण, अणु3840, 0x1fपूर्ण,
	अणु4096, 0x7fपूर्ण, अणु4608, 0x5cपूर्ण, अणु5120, 0x5dपूर्ण, अणु6144, 0x5eपूर्ण,
	अणु7168, 0xbeपूर्ण, अणु7680, 0x5fपूर्ण, अणु8192, 0xbfपूर्ण, अणु9216, 0x9cपूर्ण,
	अणु10240, 0x9dपूर्ण, अणु12288, 0x9eपूर्ण, अणु15360, 0x9fपूर्ण
पूर्ण;

अटल पूर्णांक mpc_i2c_get_fdr_52xx(काष्ठा device_node *node, u32 घड़ी,
					  u32 *real_clk)
अणु
	स्थिर काष्ठा mpc_i2c_भागider *भाग = शून्य;
	अचिन्हित पूर्णांक pvr = mfspr(SPRN_PVR);
	u32 भागider;
	पूर्णांक i;

	अगर (घड़ी == MPC_I2C_CLOCK_LEGACY) अणु
		/* see below - शेष fdr = 0x3f -> भाग = 2048 */
		*real_clk = mpc5xxx_get_bus_frequency(node) / 2048;
		वापस -EINVAL;
	पूर्ण

	/* Determine भागider value */
	भागider = mpc5xxx_get_bus_frequency(node) / घड़ी;

	/*
	 * We want to choose an FDR/DFSR that generates an I2C bus speed that
	 * is equal to or lower than the requested speed.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(mpc_i2c_भागiders_52xx); i++) अणु
		भाग = &mpc_i2c_भागiders_52xx[i];
		/* Old MPC5200 rev A CPUs करो not support the high bits */
		अगर (भाग->fdr & 0xc0 && pvr == 0x80822011)
			जारी;
		अगर (भाग->भागider >= भागider)
			अवरोध;
	पूर्ण

	*real_clk = mpc5xxx_get_bus_frequency(node) / भाग->भागider;
	वापस (पूर्णांक)भाग->fdr;
पूर्ण

अटल व्योम mpc_i2c_setup_52xx(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
	पूर्णांक ret, fdr;

	अगर (घड़ी == MPC_I2C_CLOCK_PRESERVE) अणु
		dev_dbg(i2c->dev, "using fdr %d\n",
			पढ़ोb(i2c->base + MPC_I2C_FDR));
		वापस;
	पूर्ण

	ret = mpc_i2c_get_fdr_52xx(node, घड़ी, &i2c->real_clk);
	fdr = (ret >= 0) ? ret : 0x3f; /* backward compatibility */

	ग_लिखोb(fdr & 0xff, i2c->base + MPC_I2C_FDR);

	अगर (ret >= 0)
		dev_info(i2c->dev, "clock %u Hz (fdr=%d)\n", i2c->real_clk,
			 fdr);
पूर्ण
#अन्यथा /* !(CONFIG_PPC_MPC52xx || CONFIG_PPC_MPC512x) */
अटल व्योम mpc_i2c_setup_52xx(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC52xx || CONFIG_PPC_MPC512x */

#अगर_घोषित CONFIG_PPC_MPC512x
अटल व्योम mpc_i2c_setup_512x(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
	काष्ठा device_node *node_ctrl;
	व्योम __iomem *ctrl;
	स्थिर u32 *pval;
	u32 idx;

	/* Enable I2C पूर्णांकerrupts क्रम mpc5121 */
	node_ctrl = of_find_compatible_node(शून्य, शून्य,
					    "fsl,mpc5121-i2c-ctrl");
	अगर (node_ctrl) अणु
		ctrl = of_iomap(node_ctrl, 0);
		अगर (ctrl) अणु
			/* Interrupt enable bits क्रम i2c-0/1/2: bit 24/26/28 */
			pval = of_get_property(node, "reg", शून्य);
			idx = (*pval & 0xff) / 0x20;
			setbits32(ctrl, 1 << (24 + idx * 2));
			iounmap(ctrl);
		पूर्ण
		of_node_put(node_ctrl);
	पूर्ण

	/* The घड़ी setup क्रम the 52xx works also fine क्रम the 512x */
	mpc_i2c_setup_52xx(node, i2c, घड़ी);
पूर्ण
#अन्यथा /* CONFIG_PPC_MPC512x */
अटल व्योम mpc_i2c_setup_512x(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_MPC512x */

#अगर_घोषित CONFIG_FSL_SOC
अटल स्थिर काष्ठा mpc_i2c_भागider mpc_i2c_भागiders_8xxx[] = अणु
	अणु160, 0x0120पूर्ण, अणु192, 0x0121पूर्ण, अणु224, 0x0122पूर्ण, अणु256, 0x0123पूर्ण,
	अणु288, 0x0100पूर्ण, अणु320, 0x0101पूर्ण, अणु352, 0x0601पूर्ण, अणु384, 0x0102पूर्ण,
	अणु416, 0x0602पूर्ण, अणु448, 0x0126पूर्ण, अणु480, 0x0103पूर्ण, अणु512, 0x0127पूर्ण,
	अणु544, 0x0b03पूर्ण, अणु576, 0x0104पूर्ण, अणु608, 0x1603पूर्ण, अणु640, 0x0105पूर्ण,
	अणु672, 0x2003पूर्ण, अणु704, 0x0b05पूर्ण, अणु736, 0x2b03पूर्ण, अणु768, 0x0106पूर्ण,
	अणु800, 0x3603पूर्ण, अणु832, 0x0b06पूर्ण, अणु896, 0x012aपूर्ण, अणु960, 0x0107पूर्ण,
	अणु1024, 0x012bपूर्ण, अणु1088, 0x1607पूर्ण, अणु1152, 0x0108पूर्ण, अणु1216, 0x2b07पूर्ण,
	अणु1280, 0x0109पूर्ण, अणु1408, 0x1609पूर्ण, अणु1536, 0x010aपूर्ण, अणु1664, 0x160aपूर्ण,
	अणु1792, 0x012eपूर्ण, अणु1920, 0x010bपूर्ण, अणु2048, 0x012fपूर्ण, अणु2176, 0x2b0bपूर्ण,
	अणु2304, 0x010cपूर्ण, अणु2560, 0x010dपूर्ण, अणु2816, 0x2b0dपूर्ण, अणु3072, 0x010eपूर्ण,
	अणु3328, 0x2b0eपूर्ण, अणु3584, 0x0132पूर्ण, अणु3840, 0x010fपूर्ण, अणु4096, 0x0133पूर्ण,
	अणु4608, 0x0110पूर्ण, अणु5120, 0x0111पूर्ण, अणु6144, 0x0112पूर्ण, अणु7168, 0x0136पूर्ण,
	अणु7680, 0x0113पूर्ण, अणु8192, 0x0137पूर्ण, अणु9216, 0x0114पूर्ण, अणु10240, 0x0115पूर्ण,
	अणु12288, 0x0116पूर्ण, अणु14336, 0x013aपूर्ण, अणु15360, 0x0117पूर्ण, अणु16384, 0x013bपूर्ण,
	अणु18432, 0x0118पूर्ण, अणु20480, 0x0119पूर्ण, अणु24576, 0x011aपूर्ण, अणु28672, 0x013eपूर्ण,
	अणु30720, 0x011bपूर्ण, अणु32768, 0x013fपूर्ण, अणु36864, 0x011cपूर्ण, अणु40960, 0x011dपूर्ण,
	अणु49152, 0x011eपूर्ण, अणु61440, 0x011fपूर्ण
पूर्ण;

अटल u32 mpc_i2c_get_sec_cfg_8xxx(व्योम)
अणु
	काष्ठा device_node *node;
	u32 __iomem *reg;
	u32 val = 0;

	node = of_find_node_by_name(शून्य, "global-utilities");
	अगर (node) अणु
		स्थिर u32 *prop = of_get_property(node, "reg", शून्य);
		अगर (prop) अणु
			/*
			 * Map and check POR Device Status Register 2
			 * (PORDEVSR2) at 0xE0014. Note than जबतक MPC8533
			 * and MPC8544 indicate SEC frequency ratio
			 * configuration as bit 26 in PORDEVSR2, other MPC8xxx
			 * parts may store it dअगरferently or may not have it
			 * at all.
			 */
			reg = ioremap(get_immrbase() + *prop + 0x14, 0x4);
			अगर (!reg)
				prपूर्णांकk(KERN_ERR
				       "Error: couldn't map PORDEVSR2\n");
			अन्यथा
				val = in_be32(reg) & 0x00000020; /* sec-cfg */
			iounmap(reg);
		पूर्ण
	पूर्ण
	of_node_put(node);

	वापस val;
पूर्ण

अटल u32 mpc_i2c_get_prescaler_8xxx(व्योम)
अणु
	/*
	 * According to the AN2919 all MPC824x have prescaler 1, जबतक MPC83xx
	 * may have prescaler 1, 2, or 3, depending on the घातer-on
	 * configuration.
	 */
	u32 prescaler = 1;

	/* mpc85xx */
	अगर (pvr_version_is(PVR_VER_E500V1) || pvr_version_is(PVR_VER_E500V2)
		|| pvr_version_is(PVR_VER_E500MC)
		|| pvr_version_is(PVR_VER_E5500)
		|| pvr_version_is(PVR_VER_E6500)) अणु
		अचिन्हित पूर्णांक svr = mfspr(SPRN_SVR);

		अगर ((SVR_SOC_VER(svr) == SVR_8540)
			|| (SVR_SOC_VER(svr) == SVR_8541)
			|| (SVR_SOC_VER(svr) == SVR_8560)
			|| (SVR_SOC_VER(svr) == SVR_8555)
			|| (SVR_SOC_VER(svr) == SVR_8610))
			/* the above 85xx SoCs have prescaler 1 */
			prescaler = 1;
		अन्यथा अगर ((SVR_SOC_VER(svr) == SVR_8533)
			|| (SVR_SOC_VER(svr) == SVR_8544))
			/* the above 85xx SoCs have prescaler 3 or 2 */
			prescaler = mpc_i2c_get_sec_cfg_8xxx() ? 3 : 2;
		अन्यथा
			/* all the other 85xx have prescaler 2 */
			prescaler = 2;
	पूर्ण

	वापस prescaler;
पूर्ण

अटल पूर्णांक mpc_i2c_get_fdr_8xxx(काष्ठा device_node *node, u32 घड़ी,
					  u32 *real_clk)
अणु
	स्थिर काष्ठा mpc_i2c_भागider *भाग = शून्य;
	u32 prescaler = mpc_i2c_get_prescaler_8xxx();
	u32 भागider;
	पूर्णांक i;

	अगर (घड़ी == MPC_I2C_CLOCK_LEGACY) अणु
		/* see below - शेष fdr = 0x1031 -> भाग = 16 * 3072 */
		*real_clk = fsl_get_sys_freq() / prescaler / (16 * 3072);
		वापस -EINVAL;
	पूर्ण

	भागider = fsl_get_sys_freq() / घड़ी / prescaler;

	pr_debug("I2C: src_clock=%d clock=%d divider=%d\n",
		 fsl_get_sys_freq(), घड़ी, भागider);

	/*
	 * We want to choose an FDR/DFSR that generates an I2C bus speed that
	 * is equal to or lower than the requested speed.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(mpc_i2c_भागiders_8xxx); i++) अणु
		भाग = &mpc_i2c_भागiders_8xxx[i];
		अगर (भाग->भागider >= भागider)
			अवरोध;
	पूर्ण

	*real_clk = fsl_get_sys_freq() / prescaler / भाग->भागider;
	वापस (पूर्णांक)भाग->fdr;
पूर्ण

अटल व्योम mpc_i2c_setup_8xxx(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
	पूर्णांक ret, fdr;

	अगर (घड़ी == MPC_I2C_CLOCK_PRESERVE) अणु
		dev_dbg(i2c->dev, "using dfsrr %d, fdr %d\n",
			पढ़ोb(i2c->base + MPC_I2C_DFSRR),
			पढ़ोb(i2c->base + MPC_I2C_FDR));
		वापस;
	पूर्ण

	ret = mpc_i2c_get_fdr_8xxx(node, घड़ी, &i2c->real_clk);
	fdr = (ret >= 0) ? ret : 0x1031; /* backward compatibility */

	ग_लिखोb(fdr & 0xff, i2c->base + MPC_I2C_FDR);
	ग_लिखोb((fdr >> 8) & 0xff, i2c->base + MPC_I2C_DFSRR);

	अगर (ret >= 0)
		dev_info(i2c->dev, "clock %d Hz (dfsrr=%d fdr=%d)\n",
			 i2c->real_clk, fdr >> 8, fdr & 0xff);
पूर्ण

#अन्यथा /* !CONFIG_FSL_SOC */
अटल व्योम mpc_i2c_setup_8xxx(काष्ठा device_node *node,
					 काष्ठा mpc_i2c *i2c,
					 u32 घड़ी)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FSL_SOC */

अटल व्योम mpc_i2c_finish(काष्ठा mpc_i2c *i2c, पूर्णांक rc)
अणु
	i2c->rc = rc;
	i2c->block = 0;
	i2c->cntl_bits = CCR_MEN;
	ग_लिखोccr(i2c, i2c->cntl_bits);
	wake_up(&i2c->रुकोq);
पूर्ण

अटल व्योम mpc_i2c_करो_action(काष्ठा mpc_i2c *i2c)
अणु
	काष्ठा i2c_msg *msg = &i2c->msgs[i2c->curr_msg];
	पूर्णांक dir = 0;
	पूर्णांक recv_len = 0;
	u8 byte;

	dev_dbg(i2c->dev, "action = %s\n", action_str[i2c->action]);

	i2c->cntl_bits &= ~(CCR_RSTA | CCR_MTX | CCR_TXAK);

	अगर (msg->flags & I2C_M_RD)
		dir = 1;
	अगर (msg->flags & I2C_M_RECV_LEN)
		recv_len = 1;

	चयन (i2c->action) अणु
	हाल MPC_I2C_ACTION_RESTART:
		i2c->cntl_bits |= CCR_RSTA;
		fallthrough;

	हाल MPC_I2C_ACTION_START:
		i2c->cntl_bits |= CCR_MSTA | CCR_MTX;
		ग_लिखोccr(i2c, i2c->cntl_bits);
		ग_लिखोb((msg->addr << 1) | dir, i2c->base + MPC_I2C_DR);
		i2c->expect_rxack = 1;
		i2c->action = dir ? MPC_I2C_ACTION_READ_BEGIN : MPC_I2C_ACTION_WRITE;
		अवरोध;

	हाल MPC_I2C_ACTION_READ_BEGIN:
		अगर (msg->len) अणु
			अगर (msg->len == 1 && !(msg->flags & I2C_M_RECV_LEN))
				i2c->cntl_bits |= CCR_TXAK;

			ग_लिखोccr(i2c, i2c->cntl_bits);
			/* Dummy पढ़ो */
			पढ़ोb(i2c->base + MPC_I2C_DR);
		पूर्ण
		i2c->action = MPC_I2C_ACTION_READ_BYTE;
		अवरोध;

	हाल MPC_I2C_ACTION_READ_BYTE:
		अगर (i2c->byte_posn || !recv_len) अणु
			/* Generate Tx ACK on next to last byte */
			अगर (i2c->byte_posn == msg->len - 2)
				i2c->cntl_bits |= CCR_TXAK;
			/* Do not generate stop on last byte */
			अगर (i2c->byte_posn == msg->len - 1)
				i2c->cntl_bits |= CCR_MTX;

			ग_लिखोccr(i2c, i2c->cntl_bits);
		पूर्ण

		byte = पढ़ोb(i2c->base + MPC_I2C_DR);

		अगर (i2c->byte_posn == 0 && recv_len) अणु
			अगर (byte == 0 || byte > I2C_SMBUS_BLOCK_MAX) अणु
				mpc_i2c_finish(i2c, -EPROTO);
				वापस;
			पूर्ण
			msg->len += byte;
			/*
			 * For block पढ़ोs, generate Tx ACK here अगर data length
			 * is 1 byte (total length is 2 bytes).
			 */
			अगर (msg->len == 2) अणु
				i2c->cntl_bits |= CCR_TXAK;
				ग_लिखोccr(i2c, i2c->cntl_bits);
			पूर्ण
		पूर्ण

		dev_dbg(i2c->dev, "%s %02x\n", action_str[i2c->action], byte);
		msg->buf[i2c->byte_posn++] = byte;
		अवरोध;

	हाल MPC_I2C_ACTION_WRITE:
		dev_dbg(i2c->dev, "%s %02x\n", action_str[i2c->action],
			msg->buf[i2c->byte_posn]);
		ग_लिखोb(msg->buf[i2c->byte_posn++], i2c->base + MPC_I2C_DR);
		i2c->expect_rxack = 1;
		अवरोध;

	हाल MPC_I2C_ACTION_STOP:
		mpc_i2c_finish(i2c, 0);
		अवरोध;

	शेष:
		WARN(1, "Unexpected action %d\n", i2c->action);
		अवरोध;
	पूर्ण

	अगर (msg->len == i2c->byte_posn) अणु
		i2c->curr_msg++;
		i2c->byte_posn = 0;

		अगर (i2c->curr_msg == i2c->num_msgs) अणु
			i2c->action = MPC_I2C_ACTION_STOP;
			/*
			 * We करोn't get another पूर्णांकerrupt on पढ़ो so
			 * finish the transfer now
			 */
			अगर (dir)
				mpc_i2c_finish(i2c, 0);
		पूर्ण अन्यथा अणु
			i2c->action = MPC_I2C_ACTION_RESTART;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mpc_i2c_करो_पूर्णांकr(काष्ठा mpc_i2c *i2c, u8 status)
अणु
	spin_lock(&i2c->lock);

	अगर (!(status & CSR_MCF)) अणु
		dev_dbg(i2c->dev, "unfinished\n");
		mpc_i2c_finish(i2c, -EIO);
		जाओ out;
	पूर्ण

	अगर (status & CSR_MAL) अणु
		dev_dbg(i2c->dev, "arbitration lost\n");
		mpc_i2c_finish(i2c, -EAGAIN);
		जाओ out;
	पूर्ण

	अगर (i2c->expect_rxack && (status & CSR_RXAK)) अणु
		dev_dbg(i2c->dev, "no Rx ACK\n");
		mpc_i2c_finish(i2c, -ENXIO);
		जाओ out;
	पूर्ण
	i2c->expect_rxack = 0;

	mpc_i2c_करो_action(i2c);

out:
	spin_unlock(&i2c->lock);
पूर्ण

अटल irqवापस_t mpc_i2c_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mpc_i2c *i2c = dev_id;
	u8 status;

	status = पढ़ोb(i2c->base + MPC_I2C_SR);
	अगर (status & CSR_MIF) अणु
		ग_लिखोb(0, i2c->base + MPC_I2C_SR);
		mpc_i2c_करो_पूर्णांकr(i2c, status);
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक mpc_i2c_रुको_क्रम_completion(काष्ठा mpc_i2c *i2c)
अणु
	दीर्घ समय_left;

	समय_left = रुको_event_समयout(i2c->रुकोq, !i2c->block, i2c->adap.समयout);
	अगर (!समय_left)
		वापस -ETIMEDOUT;
	अगर (समय_left < 0)
		वापस समय_left;

	वापस 0;
पूर्ण

अटल पूर्णांक mpc_i2c_execute_msg(काष्ठा mpc_i2c *i2c)
अणु
	अचिन्हित दीर्घ orig_jअगरfies;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	spin_lock_irqsave(&i2c->lock, flags);

	i2c->curr_msg = 0;
	i2c->rc = 0;
	i2c->byte_posn = 0;
	i2c->block = 1;
	i2c->action = MPC_I2C_ACTION_START;

	i2c->cntl_bits = CCR_MEN | CCR_MIEN;
	ग_लिखोb(0, i2c->base + MPC_I2C_SR);
	ग_लिखोccr(i2c, i2c->cntl_bits);

	mpc_i2c_करो_action(i2c);

	spin_unlock_irqrestore(&i2c->lock, flags);

	ret = mpc_i2c_रुको_क्रम_completion(i2c);
	अगर (ret)
		i2c->rc = ret;

	अगर (i2c->rc == -EIO || i2c->rc == -EAGAIN || i2c->rc == -ETIMEDOUT)
		i2c_recover_bus(&i2c->adap);

	orig_jअगरfies = jअगरfies;
	/* Wait until STOP is seen, allow up to 1 s */
	जबतक (पढ़ोb(i2c->base + MPC_I2C_SR) & CSR_MBB) अणु
		अगर (समय_after(jअगरfies, orig_jअगरfies + HZ)) अणु
			u8 status = पढ़ोb(i2c->base + MPC_I2C_SR);

			dev_dbg(i2c->dev, "timeout\n");
			अगर ((status & (CSR_MCF | CSR_MBB | CSR_RXAK)) != 0) अणु
				ग_लिखोb(status & ~CSR_MAL,
				       i2c->base + MPC_I2C_SR);
				i2c_recover_bus(&i2c->adap);
			पूर्ण
			वापस -EIO;
		पूर्ण
		cond_resched();
	पूर्ण

	वापस i2c->rc;
पूर्ण

अटल पूर्णांक mpc_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	पूर्णांक rc, ret = num;
	काष्ठा mpc_i2c *i2c = i2c_get_adapdata(adap);
	पूर्णांक i;

	dev_dbg(i2c->dev, "num = %d\n", num);
	क्रम (i = 0; i < num; i++)
		dev_dbg(i2c->dev, "  addr = %02x, flags = %02x, len = %d, %*ph\n",
			msgs[i].addr, msgs[i].flags, msgs[i].len,
			msgs[i].flags & I2C_M_RD ? 0 : msgs[i].len,
			msgs[i].buf);

	WARN_ON(i2c->msgs != शून्य);
	i2c->msgs = msgs;
	i2c->num_msgs = num;

	rc = mpc_i2c_execute_msg(i2c);
	अगर (rc < 0)
		ret = rc;

	i2c->num_msgs = 0;
	i2c->msgs = शून्य;

	वापस ret;
पूर्ण

अटल u32 mpc_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL
	  | I2C_FUNC_SMBUS_READ_BLOCK_DATA | I2C_FUNC_SMBUS_BLOCK_PROC_CALL;
पूर्ण

अटल पूर्णांक fsl_i2c_bus_recovery(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा mpc_i2c *i2c = i2c_get_adapdata(adap);

	अगर (i2c->has_errata_A004447)
		mpc_i2c_fixup_A004447(i2c);
	अन्यथा
		mpc_i2c_fixup(i2c);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm mpc_algo = अणु
	.master_xfer = mpc_xfer,
	.functionality = mpc_functionality,
पूर्ण;

अटल काष्ठा i2c_adapter mpc_ops = अणु
	.owner = THIS_MODULE,
	.algo = &mpc_algo,
	.समयout = HZ,
पूर्ण;

अटल काष्ठा i2c_bus_recovery_info fsl_i2c_recovery_info = अणु
	.recover_bus = fsl_i2c_bus_recovery,
पूर्ण;

अटल पूर्णांक fsl_i2c_probe(काष्ठा platक्रमm_device *op)
अणु
	स्थिर काष्ठा mpc_i2c_data *data;
	काष्ठा mpc_i2c *i2c;
	स्थिर u32 *prop;
	u32 घड़ी = MPC_I2C_CLOCK_LEGACY;
	पूर्णांक result = 0;
	पूर्णांक plen;
	काष्ठा clk *clk;
	पूर्णांक err;

	i2c = devm_kzalloc(&op->dev, माप(*i2c), GFP_KERNEL);
	अगर (!i2c)
		वापस -ENOMEM;

	i2c->dev = &op->dev; /* क्रम debug and error output */

	init_रुकोqueue_head(&i2c->रुकोq);
	spin_lock_init(&i2c->lock);

	i2c->base = devm_platक्रमm_ioremap_resource(op, 0);
	अगर (IS_ERR(i2c->base))
		वापस PTR_ERR(i2c->base);

	i2c->irq = platक्रमm_get_irq(op, 0);
	अगर (i2c->irq < 0)
		वापस i2c->irq;

	result = devm_request_irq(&op->dev, i2c->irq, mpc_i2c_isr,
			IRQF_SHARED, "i2c-mpc", i2c);
	अगर (result < 0) अणु
		dev_err(i2c->dev, "failed to attach interrupt\n");
		वापस result;
	पूर्ण

	/*
	 * enable घड़ी क्रम the I2C peripheral (non fatal),
	 * keep a reference upon successful allocation
	 */
	clk = devm_clk_get_optional(&op->dev, शून्य);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	err = clk_prepare_enable(clk);
	अगर (err) अणु
		dev_err(&op->dev, "failed to enable clock\n");
		वापस err;
	पूर्ण

	i2c->clk_per = clk;

	अगर (of_property_पढ़ो_bool(op->dev.of_node, "fsl,preserve-clocking")) अणु
		घड़ी = MPC_I2C_CLOCK_PRESERVE;
	पूर्ण अन्यथा अणु
		prop = of_get_property(op->dev.of_node, "clock-frequency",
					&plen);
		अगर (prop && plen == माप(u32))
			घड़ी = *prop;
	पूर्ण

	data = device_get_match_data(&op->dev);
	अगर (data) अणु
		data->setup(op->dev.of_node, i2c, घड़ी);
	पूर्ण अन्यथा अणु
		/* Backwards compatibility */
		अगर (of_get_property(op->dev.of_node, "dfsrr", शून्य))
			mpc_i2c_setup_8xxx(op->dev.of_node, i2c, घड़ी);
	पूर्ण

	prop = of_get_property(op->dev.of_node, "fsl,timeout", &plen);
	अगर (prop && plen == माप(u32)) अणु
		mpc_ops.समयout = *prop * HZ / 1000000;
		अगर (mpc_ops.समयout < 5)
			mpc_ops.समयout = 5;
	पूर्ण
	dev_info(i2c->dev, "timeout %u us\n", mpc_ops.समयout * 1000000 / HZ);

	अगर (of_property_पढ़ो_bool(op->dev.of_node, "fsl,i2c-erratum-a004447"))
		i2c->has_errata_A004447 = true;

	i2c->adap = mpc_ops;
	scnम_लिखो(i2c->adap.name, माप(i2c->adap.name),
		  "MPC adapter (%s)", of_node_full_name(op->dev.of_node));
	i2c->adap.dev.parent = &op->dev;
	i2c->adap.nr = op->id;
	i2c->adap.dev.of_node = of_node_get(op->dev.of_node);
	i2c->adap.bus_recovery_info = &fsl_i2c_recovery_info;
	platक्रमm_set_drvdata(op, i2c);
	i2c_set_adapdata(&i2c->adap, i2c);

	result = i2c_add_numbered_adapter(&i2c->adap);
	अगर (result)
		जाओ fail_add;

	वापस 0;

 fail_add:
	clk_disable_unprepare(i2c->clk_per);

	वापस result;
पूर्ण;

अटल पूर्णांक fsl_i2c_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा mpc_i2c *i2c = platक्रमm_get_drvdata(op);

	i2c_del_adapter(&i2c->adap);

	clk_disable_unprepare(i2c->clk_per);

	वापस 0;
पूर्ण;

अटल पूर्णांक __maybe_unused mpc_i2c_suspend(काष्ठा device *dev)
अणु
	काष्ठा mpc_i2c *i2c = dev_get_drvdata(dev);

	i2c->fdr = पढ़ोb(i2c->base + MPC_I2C_FDR);
	i2c->dfsrr = पढ़ोb(i2c->base + MPC_I2C_DFSRR);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused mpc_i2c_resume(काष्ठा device *dev)
अणु
	काष्ठा mpc_i2c *i2c = dev_get_drvdata(dev);

	ग_लिखोb(i2c->fdr, i2c->base + MPC_I2C_FDR);
	ग_लिखोb(i2c->dfsrr, i2c->base + MPC_I2C_DFSRR);

	वापस 0;
पूर्ण
अटल SIMPLE_DEV_PM_OPS(mpc_i2c_pm_ops, mpc_i2c_suspend, mpc_i2c_resume);

अटल स्थिर काष्ठा mpc_i2c_data mpc_i2c_data_512x = अणु
	.setup = mpc_i2c_setup_512x,
पूर्ण;

अटल स्थिर काष्ठा mpc_i2c_data mpc_i2c_data_52xx = अणु
	.setup = mpc_i2c_setup_52xx,
पूर्ण;

अटल स्थिर काष्ठा mpc_i2c_data mpc_i2c_data_8313 = अणु
	.setup = mpc_i2c_setup_8xxx,
पूर्ण;

अटल स्थिर काष्ठा mpc_i2c_data mpc_i2c_data_8543 = अणु
	.setup = mpc_i2c_setup_8xxx,
पूर्ण;

अटल स्थिर काष्ठा mpc_i2c_data mpc_i2c_data_8544 = अणु
	.setup = mpc_i2c_setup_8xxx,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mpc_i2c_of_match[] = अणु
	अणु.compatible = "mpc5200-i2c", .data = &mpc_i2c_data_52xx, पूर्ण,
	अणु.compatible = "fsl,mpc5200b-i2c", .data = &mpc_i2c_data_52xx, पूर्ण,
	अणु.compatible = "fsl,mpc5200-i2c", .data = &mpc_i2c_data_52xx, पूर्ण,
	अणु.compatible = "fsl,mpc5121-i2c", .data = &mpc_i2c_data_512x, पूर्ण,
	अणु.compatible = "fsl,mpc8313-i2c", .data = &mpc_i2c_data_8313, पूर्ण,
	अणु.compatible = "fsl,mpc8543-i2c", .data = &mpc_i2c_data_8543, पूर्ण,
	अणु.compatible = "fsl,mpc8544-i2c", .data = &mpc_i2c_data_8544, पूर्ण,
	/* Backward compatibility */
	अणु.compatible = "fsl-i2c", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mpc_i2c_of_match);

/* Structure क्रम a device driver */
अटल काष्ठा platक्रमm_driver mpc_i2c_driver = अणु
	.probe		= fsl_i2c_probe,
	.हटाओ		= fsl_i2c_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = mpc_i2c_of_match,
		.pm = &mpc_i2c_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mpc_i2c_driver);

MODULE_AUTHOR("Adrian Cox <adrian@humboldt.co.uk>");
MODULE_DESCRIPTION("I2C-Bus adapter for MPC107 bridge and "
		   "MPC824x/83xx/85xx/86xx/512x/52xx processors");
MODULE_LICENSE("GPL");
