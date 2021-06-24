<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * XGE PCSR module initialisation
 *
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		WingMan Kwok <w-kwok2@ti.com>
 *
 */
#समावेश "netcp.h"

/* XGBE रेजिस्टरs */
#घोषणा XGBE_CTRL_OFFSET		0x0c
#घोषणा XGBE_SGMII_1_OFFSET		0x0114
#घोषणा XGBE_SGMII_2_OFFSET		0x0214

/* PCS-R रेजिस्टरs */
#घोषणा PCSR_CPU_CTRL_OFFSET		0x1fd0
#घोषणा POR_EN				BIT(29)

#घोषणा reg_rmw(addr, value, mask) \
	ग_लिखोl(((पढ़ोl(addr) & (~(mask))) | \
			(value & (mask))), (addr))

/* bit mask of width w at offset s */
#घोषणा MASK_WID_SH(w, s)		(((1 << w) - 1) << s)

/* shअगरt value v to offset s */
#घोषणा VAL_SH(v, s)			(v << s)

#घोषणा PHY_A(serdes)			0

काष्ठा serdes_cfg अणु
	u32 ofs;
	u32 val;
	u32 mask;
पूर्ण;

अटल काष्ठा serdes_cfg cfg_phyb_1p25g_156p25mhz_cmu0[] = अणु
	अणु0x0000, 0x00800002, 0x00ff00ffपूर्ण,
	अणु0x0014, 0x00003838, 0x0000ffffपूर्ण,
	अणु0x0060, 0x1c44e438, 0xffffffffपूर्ण,
	अणु0x0064, 0x00c18400, 0x00ffffffपूर्ण,
	अणु0x0068, 0x17078200, 0xffffff00पूर्ण,
	अणु0x006c, 0x00000014, 0x000000ffपूर्ण,
	अणु0x0078, 0x0000c000, 0x0000ff00पूर्ण,
	अणु0x0000, 0x00000003, 0x000000ffपूर्ण,
पूर्ण;

अटल काष्ठा serdes_cfg cfg_phyb_10p3125g_156p25mhz_cmu1[] = अणु
	अणु0x0c00, 0x00030002, 0x00ff00ffपूर्ण,
	अणु0x0c14, 0x00005252, 0x0000ffffपूर्ण,
	अणु0x0c28, 0x80000000, 0xff000000पूर्ण,
	अणु0x0c2c, 0x000000f6, 0x000000ffपूर्ण,
	अणु0x0c3c, 0x04000405, 0xff00ffffपूर्ण,
	अणु0x0c40, 0xc0800000, 0xffff0000पूर्ण,
	अणु0x0c44, 0x5a202062, 0xffffffffपूर्ण,
	अणु0x0c48, 0x40040424, 0xffffffffपूर्ण,
	अणु0x0c4c, 0x00004002, 0x0000ffffपूर्ण,
	अणु0x0c50, 0x19001c00, 0xff00ff00पूर्ण,
	अणु0x0c54, 0x00002100, 0x0000ff00पूर्ण,
	अणु0x0c58, 0x00000060, 0x000000ffपूर्ण,
	अणु0x0c60, 0x80131e7c, 0xffffffffपूर्ण,
	अणु0x0c64, 0x8400cb02, 0xff00ffffपूर्ण,
	अणु0x0c68, 0x17078200, 0xffffff00पूर्ण,
	अणु0x0c6c, 0x00000016, 0x000000ffपूर्ण,
	अणु0x0c74, 0x00000400, 0x0000ff00पूर्ण,
	अणु0x0c78, 0x0000c000, 0x0000ff00पूर्ण,
	अणु0x0c00, 0x00000003, 0x000000ffपूर्ण,
पूर्ण;

अटल काष्ठा serdes_cfg cfg_phyb_10p3125g_16bit_lane[] = अणु
	अणु0x0204, 0x00000080, 0x000000ffपूर्ण,
	अणु0x0208, 0x0000920d, 0x0000ffffपूर्ण,
	अणु0x0204, 0xfc000000, 0xff000000पूर्ण,
	अणु0x0208, 0x00009104, 0x0000ffffपूर्ण,
	अणु0x0210, 0x1a000000, 0xff000000पूर्ण,
	अणु0x0214, 0x00006b58, 0x00ffffffपूर्ण,
	अणु0x0218, 0x75800084, 0xffff00ffपूर्ण,
	अणु0x022c, 0x00300000, 0x00ff0000पूर्ण,
	अणु0x0230, 0x00003800, 0x0000ff00पूर्ण,
	अणु0x024c, 0x008f0000, 0x00ff0000पूर्ण,
	अणु0x0250, 0x30000000, 0xff000000पूर्ण,
	अणु0x0260, 0x00000002, 0x000000ffपूर्ण,
	अणु0x0264, 0x00000057, 0x000000ffपूर्ण,
	अणु0x0268, 0x00575700, 0x00ffff00पूर्ण,
	अणु0x0278, 0xff000000, 0xff000000पूर्ण,
	अणु0x0280, 0x00500050, 0x00ff00ffपूर्ण,
	अणु0x0284, 0x00001f15, 0x0000ffffपूर्ण,
	अणु0x028c, 0x00006f00, 0x0000ff00पूर्ण,
	अणु0x0294, 0x00000000, 0xffffff00पूर्ण,
	अणु0x0298, 0x00002640, 0xff00ffffपूर्ण,
	अणु0x029c, 0x00000003, 0x000000ffपूर्ण,
	अणु0x02a4, 0x00000f13, 0x0000ffffपूर्ण,
	अणु0x02a8, 0x0001b600, 0x00ffff00पूर्ण,
	अणु0x0380, 0x00000030, 0x000000ffपूर्ण,
	अणु0x03c0, 0x00000200, 0x0000ff00पूर्ण,
	अणु0x03cc, 0x00000018, 0x000000ffपूर्ण,
	अणु0x03cc, 0x00000000, 0x000000ffपूर्ण,
पूर्ण;

अटल काष्ठा serdes_cfg cfg_phyb_10p3125g_comlane[] = अणु
	अणु0x0a00, 0x00000800, 0x0000ff00पूर्ण,
	अणु0x0a84, 0x00000000, 0x000000ffपूर्ण,
	अणु0x0a8c, 0x00130000, 0x00ff0000पूर्ण,
	अणु0x0a90, 0x77a00000, 0xffff0000पूर्ण,
	अणु0x0a94, 0x00007777, 0x0000ffffपूर्ण,
	अणु0x0b08, 0x000f0000, 0xffff0000पूर्ण,
	अणु0x0b0c, 0x000f0000, 0x00ffffffपूर्ण,
	अणु0x0b10, 0xbe000000, 0xff000000पूर्ण,
	अणु0x0b14, 0x000000ff, 0x000000ffपूर्ण,
	अणु0x0b18, 0x00000014, 0x000000ffपूर्ण,
	अणु0x0b5c, 0x981b0000, 0xffff0000पूर्ण,
	अणु0x0b64, 0x00001100, 0x0000ff00पूर्ण,
	अणु0x0b78, 0x00000c00, 0x0000ff00पूर्ण,
	अणु0x0abc, 0xff000000, 0xff000000पूर्ण,
	अणु0x0ac0, 0x0000008b, 0x000000ffपूर्ण,
पूर्ण;

अटल काष्ठा serdes_cfg cfg_cm_c1_c2[] = अणु
	अणु0x0208, 0x00000000, 0x00000f00पूर्ण,
	अणु0x0208, 0x00000000, 0x0000001fपूर्ण,
	अणु0x0204, 0x00000000, 0x00040000पूर्ण,
	अणु0x0208, 0x000000a0, 0x000000e0पूर्ण,
पूर्ण;

अटल व्योम netcp_xgbe_serdes_cmu_init(व्योम __iomem *serdes_regs)
अणु
	पूर्णांक i;

	/* cmu0 setup */
	क्रम (i = 0; i < ARRAY_SIZE(cfg_phyb_1p25g_156p25mhz_cmu0); i++) अणु
		reg_rmw(serdes_regs + cfg_phyb_1p25g_156p25mhz_cmu0[i].ofs,
			cfg_phyb_1p25g_156p25mhz_cmu0[i].val,
			cfg_phyb_1p25g_156p25mhz_cmu0[i].mask);
	पूर्ण

	/* cmu1 setup */
	क्रम (i = 0; i < ARRAY_SIZE(cfg_phyb_10p3125g_156p25mhz_cmu1); i++) अणु
		reg_rmw(serdes_regs + cfg_phyb_10p3125g_156p25mhz_cmu1[i].ofs,
			cfg_phyb_10p3125g_156p25mhz_cmu1[i].val,
			cfg_phyb_10p3125g_156p25mhz_cmu1[i].mask);
	पूर्ण
पूर्ण

/* lane is 0 based */
अटल व्योम netcp_xgbe_serdes_lane_config(
			व्योम __iomem *serdes_regs, पूर्णांक lane)
अणु
	पूर्णांक i;

	/* lane setup */
	क्रम (i = 0; i < ARRAY_SIZE(cfg_phyb_10p3125g_16bit_lane); i++) अणु
		reg_rmw(serdes_regs +
				cfg_phyb_10p3125g_16bit_lane[i].ofs +
				(0x200 * lane),
			cfg_phyb_10p3125g_16bit_lane[i].val,
			cfg_phyb_10p3125g_16bit_lane[i].mask);
	पूर्ण

	/* disable स्वतः negotiation*/
	reg_rmw(serdes_regs + (0x200 * lane) + 0x0380,
		0x00000000, 0x00000010);

	/* disable link training */
	reg_rmw(serdes_regs + (0x200 * lane) + 0x03c0,
		0x00000000, 0x00000200);
पूर्ण

अटल व्योम netcp_xgbe_serdes_com_enable(व्योम __iomem *serdes_regs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cfg_phyb_10p3125g_comlane); i++) अणु
		reg_rmw(serdes_regs + cfg_phyb_10p3125g_comlane[i].ofs,
			cfg_phyb_10p3125g_comlane[i].val,
			cfg_phyb_10p3125g_comlane[i].mask);
	पूर्ण
पूर्ण

अटल व्योम netcp_xgbe_serdes_lane_enable(
			व्योम __iomem *serdes_regs, पूर्णांक lane)
अणु
	/* Set Lane Control Rate */
	ग_लिखोl(0xe0e9e038, serdes_regs + 0x1fe0 + (4 * lane));
पूर्ण

अटल व्योम netcp_xgbe_serdes_phyb_rst_clr(व्योम __iomem *serdes_regs)
अणु
	reg_rmw(serdes_regs + 0x0a00, 0x0000001f, 0x000000ff);
पूर्ण

अटल व्योम netcp_xgbe_serdes_pll_disable(व्योम __iomem *serdes_regs)
अणु
	ग_लिखोl(0x88000000, serdes_regs + 0x1ff4);
पूर्ण

अटल व्योम netcp_xgbe_serdes_pll_enable(व्योम __iomem *serdes_regs)
अणु
	netcp_xgbe_serdes_phyb_rst_clr(serdes_regs);
	ग_लिखोl(0xee000000, serdes_regs + 0x1ff4);
पूर्ण

अटल पूर्णांक netcp_xgbe_रुको_pll_locked(व्योम __iomem *sw_regs)
अणु
	अचिन्हित दीर्घ समयout;
	पूर्णांक ret = 0;
	u32 val_1, val_0;

	समयout = jअगरfies + msecs_to_jअगरfies(500);
	करो अणु
		val_0 = (पढ़ोl(sw_regs + XGBE_SGMII_1_OFFSET) & BIT(4));
		val_1 = (पढ़ोl(sw_regs + XGBE_SGMII_2_OFFSET) & BIT(4));

		अगर (val_1 && val_0)
			वापस 0;

		अगर (समय_after(jअगरfies, समयout)) अणु
			ret = -ETIMEDOUT;
			अवरोध;
		पूर्ण

		cpu_relax();
	पूर्ण जबतक (true);

	pr_err("XGBE serdes not locked: time out.\n");
	वापस ret;
पूर्ण

अटल व्योम netcp_xgbe_serdes_enable_xgmii_port(व्योम __iomem *sw_regs)
अणु
	ग_लिखोl(0x03, sw_regs + XGBE_CTRL_OFFSET);
पूर्ण

अटल u32 netcp_xgbe_serdes_पढ़ो_tbus_val(व्योम __iomem *serdes_regs)
अणु
	u32 पंचांगp;

	अगर (PHY_A(serdes_regs)) अणु
		पंचांगp  = (पढ़ोl(serdes_regs + 0x0ec) >> 24) & 0x0ff;
		पंचांगp |= ((पढ़ोl(serdes_regs + 0x0fc) >> 16) & 0x00f00);
	पूर्ण अन्यथा अणु
		पंचांगp  = (पढ़ोl(serdes_regs + 0x0f8) >> 16) & 0x0fff;
	पूर्ण

	वापस पंचांगp;
पूर्ण

अटल व्योम netcp_xgbe_serdes_ग_लिखो_tbus_addr(व्योम __iomem *serdes_regs,
					      पूर्णांक select, पूर्णांक ofs)
अणु
	अगर (PHY_A(serdes_regs)) अणु
		reg_rmw(serdes_regs + 0x0008, ((select << 5) + ofs) << 24,
			~0x00ffffff);
		वापस;
	पूर्ण

	/* For 2 lane Phy-B, lane0 is actually lane1 */
	चयन (select) अणु
	हाल 1:
		select = 2;
		अवरोध;
	हाल 2:
		select = 3;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	reg_rmw(serdes_regs + 0x00fc, ((select << 8) + ofs) << 16, ~0xf800ffff);
पूर्ण

अटल u32 netcp_xgbe_serdes_पढ़ो_select_tbus(व्योम __iomem *serdes_regs,
					      पूर्णांक select, पूर्णांक ofs)
अणु
	/* Set tbus address */
	netcp_xgbe_serdes_ग_लिखो_tbus_addr(serdes_regs, select, ofs);
	/* Get TBUS Value */
	वापस netcp_xgbe_serdes_पढ़ो_tbus_val(serdes_regs);
पूर्ण

अटल व्योम netcp_xgbe_serdes_reset_cdr(व्योम __iomem *serdes_regs,
					व्योम __iomem *sig_detect_reg, पूर्णांक lane)
अणु
	u32 पंचांगp, dlpf, tbus;

	/*Get the DLPF values */
	पंचांगp = netcp_xgbe_serdes_पढ़ो_select_tbus(
			serdes_regs, lane + 1, 5);

	dlpf = पंचांगp >> 2;

	अगर (dlpf < 400 || dlpf > 700) अणु
		reg_rmw(sig_detect_reg, VAL_SH(2, 1), MASK_WID_SH(2, 1));
		mdelay(1);
		reg_rmw(sig_detect_reg, VAL_SH(0, 1), MASK_WID_SH(2, 1));
	पूर्ण अन्यथा अणु
		tbus = netcp_xgbe_serdes_पढ़ो_select_tbus(serdes_regs, lane +
							  1, 0xe);

		pr_debug("XGBE: CDR centered, DLPF: %4d,%d,%d.\n",
			 पंचांगp >> 2, पंचांगp & 3, (tbus >> 2) & 3);
	पूर्ण
पूर्ण

/* Call every 100 ms */
अटल पूर्णांक netcp_xgbe_check_link_status(व्योम __iomem *serdes_regs,
					व्योम __iomem *sw_regs, u32 lanes,
					u32 *current_state, u32 *lane_करोwn)
अणु
	व्योम __iomem *pcsr_base = sw_regs + 0x0600;
	व्योम __iomem *sig_detect_reg;
	u32 pcsr_rx_stat, blk_lock, blk_errs;
	पूर्णांक loss, i, status = 1;

	क्रम (i = 0; i < lanes; i++) अणु
		/* Get the Loss bit */
		loss = पढ़ोl(serdes_regs + 0x1fc0 + 0x20 + (i * 0x04)) & 0x1;

		/* Get Block Errors and Block Lock bits */
		pcsr_rx_stat = पढ़ोl(pcsr_base + 0x0c + (i * 0x80));
		blk_lock = (pcsr_rx_stat >> 30) & 0x1;
		blk_errs = (pcsr_rx_stat >> 16) & 0x0ff;

		/* Get Signal Detect Overlay Address */
		sig_detect_reg = serdes_regs + (i * 0x200) + 0x200 + 0x04;

		/* If Block errors maxed out, attempt recovery! */
		अगर (blk_errs == 0x0ff)
			blk_lock = 0;

		चयन (current_state[i]) अणु
		हाल 0:
			/* अगर good link lock the संकेत detect ON! */
			अगर (!loss && blk_lock) अणु
				pr_debug("XGBE PCSR Linked Lane: %d\n", i);
				reg_rmw(sig_detect_reg, VAL_SH(3, 1),
					MASK_WID_SH(2, 1));
				current_state[i] = 1;
			पूर्ण अन्यथा अगर (!blk_lock) अणु
				/* अगर no lock, then reset CDR */
				pr_debug("XGBE PCSR Recover Lane: %d\n", i);
				netcp_xgbe_serdes_reset_cdr(serdes_regs,
							    sig_detect_reg, i);
			पूर्ण
			अवरोध;

		हाल 1:
			अगर (!blk_lock) अणु
				/* Link Lost? */
				lane_करोwn[i] = 1;
				current_state[i] = 2;
			पूर्ण
			अवरोध;

		हाल 2:
			अगर (blk_lock)
				/* Nope just noise */
				current_state[i] = 1;
			अन्यथा अणु
				/* Lost the block lock, reset CDR अगर it is
				 * not centered and go back to sync state
				 */
				netcp_xgbe_serdes_reset_cdr(serdes_regs,
							    sig_detect_reg, i);
				current_state[i] = 0;
			पूर्ण
			अवरोध;

		शेष:
			pr_err("XGBE: unknown current_state[%d] %d\n",
			       i, current_state[i]);
			अवरोध;
		पूर्ण

		अगर (blk_errs > 0) अणु
			/* Reset the Error counts! */
			reg_rmw(pcsr_base + 0x08 + (i * 0x80), VAL_SH(0x19, 0),
				MASK_WID_SH(8, 0));

			reg_rmw(pcsr_base + 0x08 + (i * 0x80), VAL_SH(0x00, 0),
				MASK_WID_SH(8, 0));
		पूर्ण

		status &= (current_state[i] == 1);
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक netcp_xgbe_serdes_check_lane(व्योम __iomem *serdes_regs,
					व्योम __iomem *sw_regs)
अणु
	u32 current_state[2] = अणु0, 0पूर्ण;
	पूर्णांक retries = 0, link_up;
	u32 lane_करोwn[2];

	करो अणु
		lane_करोwn[0] = 0;
		lane_करोwn[1] = 0;

		link_up = netcp_xgbe_check_link_status(serdes_regs, sw_regs, 2,
						       current_state,
						       lane_करोwn);

		/* अगर we did not get link up then रुको 100ms beक्रमe calling
		 * it again
		 */
		अगर (link_up)
			अवरोध;

		अगर (lane_करोwn[0])
			pr_debug("XGBE: detected link down on lane 0\n");

		अगर (lane_करोwn[1])
			pr_debug("XGBE: detected link down on lane 1\n");

		अगर (++retries > 1) अणु
			pr_debug("XGBE: timeout waiting for serdes link up\n");
			वापस -ETIMEDOUT;
		पूर्ण
		mdelay(100);
	पूर्ण जबतक (!link_up);

	pr_debug("XGBE: PCSR link is up\n");
	वापस 0;
पूर्ण

अटल व्योम netcp_xgbe_serdes_setup_cm_c1_c2(व्योम __iomem *serdes_regs,
					     पूर्णांक lane, पूर्णांक cm, पूर्णांक c1, पूर्णांक c2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cfg_cm_c1_c2); i++) अणु
		reg_rmw(serdes_regs + cfg_cm_c1_c2[i].ofs + (0x200 * lane),
			cfg_cm_c1_c2[i].val,
			cfg_cm_c1_c2[i].mask);
	पूर्ण
पूर्ण

अटल व्योम netcp_xgbe_reset_serdes(व्योम __iomem *serdes_regs)
अणु
	/* Toggle the POR_EN bit in CONFIG.CPU_CTRL */
	/* enable POR_EN bit */
	reg_rmw(serdes_regs + PCSR_CPU_CTRL_OFFSET, POR_EN, POR_EN);
	usleep_range(10, 100);

	/* disable POR_EN bit */
	reg_rmw(serdes_regs + PCSR_CPU_CTRL_OFFSET, 0, POR_EN);
	usleep_range(10, 100);
पूर्ण

अटल पूर्णांक netcp_xgbe_serdes_config(व्योम __iomem *serdes_regs,
				    व्योम __iomem *sw_regs)
अणु
	u32 ret, i;

	netcp_xgbe_serdes_pll_disable(serdes_regs);
	netcp_xgbe_serdes_cmu_init(serdes_regs);

	क्रम (i = 0; i < 2; i++)
		netcp_xgbe_serdes_lane_config(serdes_regs, i);

	netcp_xgbe_serdes_com_enable(serdes_regs);
	/* This is EVM + RTM-BOC specअगरic */
	क्रम (i = 0; i < 2; i++)
		netcp_xgbe_serdes_setup_cm_c1_c2(serdes_regs, i, 0, 0, 5);

	netcp_xgbe_serdes_pll_enable(serdes_regs);
	क्रम (i = 0; i < 2; i++)
		netcp_xgbe_serdes_lane_enable(serdes_regs, i);

	/* SB PLL Status Poll */
	ret = netcp_xgbe_रुको_pll_locked(sw_regs);
	अगर (ret)
		वापस ret;

	netcp_xgbe_serdes_enable_xgmii_port(sw_regs);
	netcp_xgbe_serdes_check_lane(serdes_regs, sw_regs);
	वापस ret;
पूर्ण

पूर्णांक netcp_xgbe_serdes_init(व्योम __iomem *serdes_regs, व्योम __iomem *xgbe_regs)
अणु
	u32 val;

	/* पढ़ो COMLANE bits 4:0 */
	val = पढ़ोl(serdes_regs + 0xa00);
	अगर (val & 0x1f) अणु
		pr_debug("XGBE: serdes already in operation - reset\n");
		netcp_xgbe_reset_serdes(serdes_regs);
	पूर्ण
	वापस netcp_xgbe_serdes_config(serdes_regs, xgbe_regs);
पूर्ण
