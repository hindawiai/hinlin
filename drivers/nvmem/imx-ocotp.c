<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i.MX6 OCOTP fusebox driver
 *
 * Copyright (c) 2015 Pengutronix, Philipp Zabel <p.zabel@pengutronix.de>
 *
 * Copyright 2019 NXP
 *
 * Based on the barebox ocotp driver,
 * Copyright (c) 2010 Baruch Siach <baruch@tkos.co.il>,
 *	Orex Computed Radiography
 *
 * Write support based on the fsl_otp driver,
 * Copyright (C) 2010-2013 Freescale Semiconductor, Inc
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#घोषणा IMX_OCOTP_OFFSET_B0W0		0x400 /* Offset from base address of the
					       * OTP Bank0 Word0
					       */
#घोषणा IMX_OCOTP_OFFSET_PER_WORD	0x10  /* Offset between the start addr
					       * of two consecutive OTP words.
					       */

#घोषणा IMX_OCOTP_ADDR_CTRL		0x0000
#घोषणा IMX_OCOTP_ADDR_CTRL_SET		0x0004
#घोषणा IMX_OCOTP_ADDR_CTRL_CLR		0x0008
#घोषणा IMX_OCOTP_ADDR_TIMING		0x0010
#घोषणा IMX_OCOTP_ADDR_DATA0		0x0020
#घोषणा IMX_OCOTP_ADDR_DATA1		0x0030
#घोषणा IMX_OCOTP_ADDR_DATA2		0x0040
#घोषणा IMX_OCOTP_ADDR_DATA3		0x0050

#घोषणा IMX_OCOTP_BM_CTRL_ADDR		0x000000FF
#घोषणा IMX_OCOTP_BM_CTRL_BUSY		0x00000100
#घोषणा IMX_OCOTP_BM_CTRL_ERROR		0x00000200
#घोषणा IMX_OCOTP_BM_CTRL_REL_SHADOWS	0x00000400

#घोषणा IMX_OCOTP_BM_CTRL_ADDR_8MP		0x000001FF
#घोषणा IMX_OCOTP_BM_CTRL_BUSY_8MP		0x00000200
#घोषणा IMX_OCOTP_BM_CTRL_ERROR_8MP		0x00000400
#घोषणा IMX_OCOTP_BM_CTRL_REL_SHADOWS_8MP	0x00000800

#घोषणा IMX_OCOTP_BM_CTRL_DEFAULT				\
	अणु							\
		.bm_addr = IMX_OCOTP_BM_CTRL_ADDR,		\
		.bm_busy = IMX_OCOTP_BM_CTRL_BUSY,		\
		.bm_error = IMX_OCOTP_BM_CTRL_ERROR,		\
		.bm_rel_shaकरोws = IMX_OCOTP_BM_CTRL_REL_SHADOWS,\
	पूर्ण

#घोषणा IMX_OCOTP_BM_CTRL_8MP					\
	अणु							\
		.bm_addr = IMX_OCOTP_BM_CTRL_ADDR_8MP,		\
		.bm_busy = IMX_OCOTP_BM_CTRL_BUSY_8MP,		\
		.bm_error = IMX_OCOTP_BM_CTRL_ERROR_8MP,	\
		.bm_rel_shaकरोws = IMX_OCOTP_BM_CTRL_REL_SHADOWS_8MP,\
	पूर्ण

#घोषणा TIMING_STROBE_PROG_US		10	/* Min समय to blow a fuse */
#घोषणा TIMING_STROBE_READ_NS		37	/* Min समय beक्रमe पढ़ो */
#घोषणा TIMING_RELAX_NS			17
#घोषणा DEF_FSOURCE			1001	/* > 1000 ns */
#घोषणा DEF_STROBE_PROG			10000	/* IPG घड़ीs */
#घोषणा IMX_OCOTP_WR_UNLOCK		0x3E770000
#घोषणा IMX_OCOTP_READ_LOCKED_VAL	0xBADABADA

अटल DEFINE_MUTEX(ocotp_mutex);

काष्ठा ocotp_priv अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	व्योम __iomem *base;
	स्थिर काष्ठा ocotp_params *params;
	काष्ठा nvmem_config *config;
पूर्ण;

काष्ठा ocotp_ctrl_reg अणु
	u32 bm_addr;
	u32 bm_busy;
	u32 bm_error;
	u32 bm_rel_shaकरोws;
पूर्ण;

काष्ठा ocotp_params अणु
	अचिन्हित पूर्णांक nregs;
	अचिन्हित पूर्णांक bank_address_words;
	व्योम (*set_timing)(काष्ठा ocotp_priv *priv);
	काष्ठा ocotp_ctrl_reg ctrl;
पूर्ण;

अटल पूर्णांक imx_ocotp_रुको_क्रम_busy(काष्ठा ocotp_priv *priv, u32 flags)
अणु
	पूर्णांक count;
	u32 c, mask;
	u32 bm_ctrl_busy, bm_ctrl_error;
	व्योम __iomem *base = priv->base;

	bm_ctrl_busy = priv->params->ctrl.bm_busy;
	bm_ctrl_error = priv->params->ctrl.bm_error;

	mask = bm_ctrl_busy | bm_ctrl_error | flags;

	क्रम (count = 10000; count >= 0; count--) अणु
		c = पढ़ोl(base + IMX_OCOTP_ADDR_CTRL);
		अगर (!(c & mask))
			अवरोध;
		cpu_relax();
	पूर्ण

	अगर (count < 0) अणु
		/* HW_OCOTP_CTRL[ERROR] will be set under the following
		 * conditions:
		 * - A ग_लिखो is perक्रमmed to a shaकरोw रेजिस्टर during a shaकरोw
		 *   reload (essentially, जबतक HW_OCOTP_CTRL[RELOAD_SHADOWS] is
		 *   set. In addition, the contents of the shaकरोw रेजिस्टर shall
		 *   not be updated.
		 * - A ग_लिखो is perक्रमmed to a shaकरोw रेजिस्टर which has been
		 *   locked.
		 * - A पढ़ो is perक्रमmed to from a shaकरोw रेजिस्टर which has
		 *   been पढ़ो locked.
		 * - A program is perक्रमmed to a fuse word which has been locked
		 * - A पढ़ो is perक्रमmed to from a fuse word which has been पढ़ो
		 *   locked.
		 */
		अगर (c & bm_ctrl_error)
			वापस -EPERM;
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम imx_ocotp_clr_err_अगर_set(काष्ठा ocotp_priv *priv)
अणु
	u32 c, bm_ctrl_error;
	व्योम __iomem *base = priv->base;

	bm_ctrl_error = priv->params->ctrl.bm_error;

	c = पढ़ोl(base + IMX_OCOTP_ADDR_CTRL);
	अगर (!(c & bm_ctrl_error))
		वापस;

	ग_लिखोl(bm_ctrl_error, base + IMX_OCOTP_ADDR_CTRL_CLR);
पूर्ण

अटल पूर्णांक imx_ocotp_पढ़ो(व्योम *context, अचिन्हित पूर्णांक offset,
			  व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा ocotp_priv *priv = context;
	अचिन्हित पूर्णांक count;
	u8 *buf, *p;
	पूर्णांक i, ret;
	u32 index, num_bytes;

	index = offset >> 2;
	num_bytes = round_up((offset % 4) + bytes, 4);
	count = num_bytes >> 2;

	अगर (count > (priv->params->nregs - index))
		count = priv->params->nregs - index;

	p = kzalloc(num_bytes, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	mutex_lock(&ocotp_mutex);

	buf = p;

	ret = clk_prepare_enable(priv->clk);
	अगर (ret < 0) अणु
		mutex_unlock(&ocotp_mutex);
		dev_err(priv->dev, "failed to prepare/enable ocotp clk\n");
		kमुक्त(p);
		वापस ret;
	पूर्ण

	ret = imx_ocotp_रुको_क्रम_busy(priv, 0);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "timeout during read setup\n");
		जाओ पढ़ो_end;
	पूर्ण

	क्रम (i = index; i < (index + count); i++) अणु
		*(u32 *)buf = पढ़ोl(priv->base + IMX_OCOTP_OFFSET_B0W0 +
			       i * IMX_OCOTP_OFFSET_PER_WORD);

		/* 47.3.1.2
		 * For "read locked" रेजिस्टरs 0xBADABADA will be वापसed and
		 * HW_OCOTP_CTRL[ERROR] will be set. It must be cleared by
		 * software beक्रमe any new ग_लिखो, पढ़ो or reload access can be
		 * issued
		 */
		अगर (*((u32 *)buf) == IMX_OCOTP_READ_LOCKED_VAL)
			imx_ocotp_clr_err_अगर_set(priv);

		buf += 4;
	पूर्ण

	index = offset % 4;
	स_नकल(val, &p[index], bytes);

पढ़ो_end:
	clk_disable_unprepare(priv->clk);
	mutex_unlock(&ocotp_mutex);

	kमुक्त(p);

	वापस ret;
पूर्ण

अटल व्योम imx_ocotp_set_imx6_timing(काष्ठा ocotp_priv *priv)
अणु
	अचिन्हित दीर्घ clk_rate;
	अचिन्हित दीर्घ strobe_पढ़ो, relax, strobe_prog;
	u32 timing;

	/* 47.3.1.3.1
	 * Program HW_OCOTP_TIMING[STROBE_PROG] and HW_OCOTP_TIMING[RELAX]
	 * fields with timing values to match the current frequency of the
	 * ipg_clk. OTP ग_लिखोs will work at maximum bus frequencies as दीर्घ
	 * as the HW_OCOTP_TIMING parameters are set correctly.
	 *
	 * Note: there are minimum timings required to ensure an OTP fuse burns
	 * correctly that are independent of the ipg_clk. Those values are not
	 * क्रमmally करोcumented anywhere however, working from the minimum
	 * timings given in u-boot we can say:
	 *
	 * - Minimum STROBE_PROG समय is 10 microseconds. Intuitively 10
	 *   microseconds feels about right as representative of a minimum समय
	 *   to physically burn out a fuse.
	 *
	 * - Minimum STROBE_READ i.e. the समय to रुको post OTP fuse burn beक्रमe
	 *   perक्रमming another पढ़ो is 37 nanoseconds
	 *
	 * - Minimum RELAX timing is 17 nanoseconds. This final RELAX minimum
	 *   timing is not entirely clear the करोcumentation says "This
	 *   count value specअगरies the समय to add to all शेष timing
	 *   parameters other than the Tpgm and Trd. It is given in number
	 *   of ipg_clk periods." where Tpgm and Trd refer to STROBE_PROG
	 *   and STROBE_READ respectively. What the other timing parameters
	 *   are though, is not specअगरied. Experience shows a zero RELAX
	 *   value will mess up a re-load of the shaकरोw रेजिस्टरs post OTP
	 *   burn.
	 */
	clk_rate = clk_get_rate(priv->clk);

	relax = DIV_ROUND_UP(clk_rate * TIMING_RELAX_NS, 1000000000) - 1;
	strobe_पढ़ो = DIV_ROUND_UP(clk_rate * TIMING_STROBE_READ_NS,
				   1000000000);
	strobe_पढ़ो += 2 * (relax + 1) - 1;
	strobe_prog = DIV_ROUND_CLOSEST(clk_rate * TIMING_STROBE_PROG_US,
					1000000);
	strobe_prog += 2 * (relax + 1) - 1;

	timing = पढ़ोl(priv->base + IMX_OCOTP_ADDR_TIMING) & 0x0FC00000;
	timing |= strobe_prog & 0x00000FFF;
	timing |= (relax       << 12) & 0x0000F000;
	timing |= (strobe_पढ़ो << 16) & 0x003F0000;

	ग_लिखोl(timing, priv->base + IMX_OCOTP_ADDR_TIMING);
पूर्ण

अटल व्योम imx_ocotp_set_imx7_timing(काष्ठा ocotp_priv *priv)
अणु
	अचिन्हित दीर्घ clk_rate;
	u64 fsource, strobe_prog;
	u32 timing;

	/* i.MX 7Solo Applications Processor Reference Manual, Rev. 0.1
	 * 6.4.3.3
	 */
	clk_rate = clk_get_rate(priv->clk);
	fsource = DIV_ROUND_UP_ULL((u64)clk_rate * DEF_FSOURCE,
				   NSEC_PER_SEC) + 1;
	strobe_prog = DIV_ROUND_CLOSEST_ULL((u64)clk_rate * DEF_STROBE_PROG,
					    NSEC_PER_SEC) + 1;

	timing = strobe_prog & 0x00000FFF;
	timing |= (fsource << 12) & 0x000FF000;

	ग_लिखोl(timing, priv->base + IMX_OCOTP_ADDR_TIMING);
पूर्ण

अटल पूर्णांक imx_ocotp_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक offset, व्योम *val,
			   माप_प्रकार bytes)
अणु
	काष्ठा ocotp_priv *priv = context;
	u32 *buf = val;
	पूर्णांक ret;

	u32 ctrl;
	u8 waddr;
	u8 word = 0;

	/* allow only writing one complete OTP word at a समय */
	अगर ((bytes != priv->config->word_size) ||
	    (offset % priv->config->word_size))
		वापस -EINVAL;

	mutex_lock(&ocotp_mutex);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret < 0) अणु
		mutex_unlock(&ocotp_mutex);
		dev_err(priv->dev, "failed to prepare/enable ocotp clk\n");
		वापस ret;
	पूर्ण

	/* Setup the ग_लिखो timing values */
	priv->params->set_timing(priv);

	/* 47.3.1.3.2
	 * Check that HW_OCOTP_CTRL[BUSY] and HW_OCOTP_CTRL[ERROR] are clear.
	 * Overlapped accesses are not supported by the controller. Any pending
	 * ग_लिखो or reload must be completed beक्रमe a ग_लिखो access can be
	 * requested.
	 */
	ret = imx_ocotp_रुको_क्रम_busy(priv, 0);
	अगर (ret < 0) अणु
		dev_err(priv->dev, "timeout during timing setup\n");
		जाओ ग_लिखो_end;
	पूर्ण

	/* 47.3.1.3.3
	 * Write the requested address to HW_OCOTP_CTRL[ADDR] and program the
	 * unlock code पूर्णांकo HW_OCOTP_CTRL[WR_UNLOCK]. This must be programmed
	 * क्रम each ग_लिखो access. The lock code is करोcumented in the रेजिस्टर
	 * description. Both the unlock code and address can be written in the
	 * same operation.
	 */
	अगर (priv->params->bank_address_words != 0) अणु
		/*
		 * In banked/i.MX7 mode the OTP रेजिस्टर bank goes पूर्णांकo waddr
		 * see i.MX 7Solo Applications Processor Reference Manual, Rev.
		 * 0.1 section 6.4.3.1
		 */
		offset = offset / priv->config->word_size;
		waddr = offset / priv->params->bank_address_words;
		word  = offset & (priv->params->bank_address_words - 1);
	पूर्ण अन्यथा अणु
		/*
		 * Non-banked i.MX6 mode.
		 * OTP ग_लिखो/पढ़ो address specअगरies one of 128 word address
		 * locations
		 */
		waddr = offset / 4;
	पूर्ण

	ctrl = पढ़ोl(priv->base + IMX_OCOTP_ADDR_CTRL);
	ctrl &= ~priv->params->ctrl.bm_addr;
	ctrl |= waddr & priv->params->ctrl.bm_addr;
	ctrl |= IMX_OCOTP_WR_UNLOCK;

	ग_लिखोl(ctrl, priv->base + IMX_OCOTP_ADDR_CTRL);

	/* 47.3.1.3.4
	 * Write the data to the HW_OCOTP_DATA रेजिस्टर. This will स्वतःmatically
	 * set HW_OCOTP_CTRL[BUSY] and clear HW_OCOTP_CTRL[WR_UNLOCK]. To
	 * protect programming same OTP bit twice, beक्रमe program OCOTP will
	 * स्वतःmatically पढ़ो fuse value in OTP and use पढ़ो value to mask
	 * program data. The controller will use masked program data to program
	 * a 32-bit word in the OTP per the address in HW_OCOTP_CTRL[ADDR]. Bit
	 * fields with 1's will result in that OTP bit being programmed. Bit
	 * fields with 0's will be ignored. At the same समय that the ग_लिखो is
	 * accepted, the controller makes an पूर्णांकernal copy of
	 * HW_OCOTP_CTRL[ADDR] which cannot be updated until the next ग_लिखो
	 * sequence is initiated. This copy guarantees that erroneous ग_लिखोs to
	 * HW_OCOTP_CTRL[ADDR] will not affect an active ग_लिखो operation. It
	 * should also be noted that during the programming HW_OCOTP_DATA will
	 * shअगरt right (with zero fill). This shअगरting is required to program
	 * the OTP serially. During the ग_लिखो operation, HW_OCOTP_DATA cannot be
	 * modअगरied.
	 * Note: on i.MX7 there are four data fields to ग_लिखो क्रम banked ग_लिखो
	 *       with the fuse blowing operation only taking place after data0
	 *	 has been written. This is why data0 must always be the last
	 *	 रेजिस्टर written.
	 */
	अगर (priv->params->bank_address_words != 0) अणु
		/* Banked/i.MX7 mode */
		चयन (word) अणु
		हाल 0:
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA1);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA2);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA3);
			ग_लिखोl(*buf, priv->base + IMX_OCOTP_ADDR_DATA0);
			अवरोध;
		हाल 1:
			ग_लिखोl(*buf, priv->base + IMX_OCOTP_ADDR_DATA1);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA2);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA3);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA0);
			अवरोध;
		हाल 2:
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA1);
			ग_लिखोl(*buf, priv->base + IMX_OCOTP_ADDR_DATA2);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA3);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA0);
			अवरोध;
		हाल 3:
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA1);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA2);
			ग_लिखोl(*buf, priv->base + IMX_OCOTP_ADDR_DATA3);
			ग_लिखोl(0, priv->base + IMX_OCOTP_ADDR_DATA0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non-banked i.MX6 mode */
		ग_लिखोl(*buf, priv->base + IMX_OCOTP_ADDR_DATA0);
	पूर्ण

	/* 47.4.1.4.5
	 * Once complete, the controller will clear BUSY. A ग_लिखो request to a
	 * रक्षित or locked region will result in no OTP access and no
	 * setting of HW_OCOTP_CTRL[BUSY]. In addition HW_OCOTP_CTRL[ERROR] will
	 * be set. It must be cleared by software beक्रमe any new ग_लिखो access
	 * can be issued.
	 */
	ret = imx_ocotp_रुको_क्रम_busy(priv, 0);
	अगर (ret < 0) अणु
		अगर (ret == -EPERM) अणु
			dev_err(priv->dev, "failed write to locked region");
			imx_ocotp_clr_err_अगर_set(priv);
		पूर्ण अन्यथा अणु
			dev_err(priv->dev, "timeout during data write\n");
		पूर्ण
		जाओ ग_लिखो_end;
	पूर्ण

	/* 47.3.1.4
	 * Write Postamble: Due to पूर्णांकernal electrical अक्षरacteristics of the
	 * OTP during ग_लिखोs, all OTP operations following a ग_लिखो must be
	 * separated by 2 us after the clearing of HW_OCOTP_CTRL_BUSY following
	 * the ग_लिखो.
	 */
	udelay(2);

	/* reload all shaकरोw रेजिस्टरs */
	ग_लिखोl(priv->params->ctrl.bm_rel_shaकरोws,
	       priv->base + IMX_OCOTP_ADDR_CTRL_SET);
	ret = imx_ocotp_रुको_क्रम_busy(priv,
				      priv->params->ctrl.bm_rel_shaकरोws);
	अगर (ret < 0)
		dev_err(priv->dev, "timeout during shadow register reload\n");

ग_लिखो_end:
	clk_disable_unprepare(priv->clk);
	mutex_unlock(&ocotp_mutex);
	वापस ret < 0 ? ret : bytes;
पूर्ण

अटल काष्ठा nvmem_config imx_ocotp_nvmem_config = अणु
	.name = "imx-ocotp",
	.पढ़ो_only = false,
	.word_size = 4,
	.stride = 1,
	.reg_पढ़ो = imx_ocotp_पढ़ो,
	.reg_ग_लिखो = imx_ocotp_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6q_params = अणु
	.nregs = 128,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6sl_params = अणु
	.nregs = 64,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6sll_params = अणु
	.nregs = 128,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6sx_params = अणु
	.nregs = 128,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6ul_params = अणु
	.nregs = 128,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx6ull_params = अणु
	.nregs = 64,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx7d_params = अणु
	.nregs = 64,
	.bank_address_words = 4,
	.set_timing = imx_ocotp_set_imx7_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx7ulp_params = अणु
	.nregs = 256,
	.bank_address_words = 0,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx8mq_params = अणु
	.nregs = 256,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx8mm_params = अणु
	.nregs = 256,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx8mn_params = अणु
	.nregs = 256,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_DEFAULT,
पूर्ण;

अटल स्थिर काष्ठा ocotp_params imx8mp_params = अणु
	.nregs = 384,
	.bank_address_words = 0,
	.set_timing = imx_ocotp_set_imx6_timing,
	.ctrl = IMX_OCOTP_BM_CTRL_8MP,
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_ocotp_dt_ids[] = अणु
	अणु .compatible = "fsl,imx6q-ocotp",  .data = &imx6q_params पूर्ण,
	अणु .compatible = "fsl,imx6sl-ocotp", .data = &imx6sl_params पूर्ण,
	अणु .compatible = "fsl,imx6sx-ocotp", .data = &imx6sx_params पूर्ण,
	अणु .compatible = "fsl,imx6ul-ocotp", .data = &imx6ul_params पूर्ण,
	अणु .compatible = "fsl,imx6ull-ocotp", .data = &imx6ull_params पूर्ण,
	अणु .compatible = "fsl,imx7d-ocotp",  .data = &imx7d_params पूर्ण,
	अणु .compatible = "fsl,imx6sll-ocotp", .data = &imx6sll_params पूर्ण,
	अणु .compatible = "fsl,imx7ulp-ocotp", .data = &imx7ulp_params पूर्ण,
	अणु .compatible = "fsl,imx8mq-ocotp", .data = &imx8mq_params पूर्ण,
	अणु .compatible = "fsl,imx8mm-ocotp", .data = &imx8mm_params पूर्ण,
	अणु .compatible = "fsl,imx8mn-ocotp", .data = &imx8mn_params पूर्ण,
	अणु .compatible = "fsl,imx8mp-ocotp", .data = &imx8mp_params पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_ocotp_dt_ids);

अटल पूर्णांक imx_ocotp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ocotp_priv *priv;
	काष्ठा nvmem_device *nvmem;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base))
		वापस PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->params = of_device_get_match_data(&pdev->dev);
	imx_ocotp_nvmem_config.size = 4 * priv->params->nregs;
	imx_ocotp_nvmem_config.dev = dev;
	imx_ocotp_nvmem_config.priv = priv;
	priv->config = &imx_ocotp_nvmem_config;

	clk_prepare_enable(priv->clk);
	imx_ocotp_clr_err_अगर_set(priv);
	clk_disable_unprepare(priv->clk);

	nvmem = devm_nvmem_रेजिस्टर(dev, &imx_ocotp_nvmem_config);

	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल काष्ठा platक्रमm_driver imx_ocotp_driver = अणु
	.probe	= imx_ocotp_probe,
	.driver = अणु
		.name	= "imx_ocotp",
		.of_match_table = imx_ocotp_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(imx_ocotp_driver);

MODULE_AUTHOR("Philipp Zabel <p.zabel@pengutronix.de>");
MODULE_DESCRIPTION("i.MX6/i.MX7 OCOTP fuse box driver");
MODULE_LICENSE("GPL v2");
