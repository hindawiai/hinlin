<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_dr.c - dual role चयन and host glue layer
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

#समावेश "mtu3.h"
#समावेश "mtu3_dr.h"

/* mt8173 etc */
#घोषणा PERI_WK_CTRL1	0x4
#घोषणा WC1_IS_C(x)	(((x) & 0xf) << 26)  /* cycle debounce */
#घोषणा WC1_IS_EN	BIT(25)
#घोषणा WC1_IS_P	BIT(6)  /* polarity क्रम ip sleep */

/* mt8183 */
#घोषणा PERI_WK_CTRL0	0x0
#घोषणा WC0_IS_C(x)	((u32)(((x) & 0xf) << 28))  /* cycle debounce */
#घोषणा WC0_IS_P	BIT(12)	/* polarity */
#घोषणा WC0_IS_EN	BIT(6)

/* mt8192 */
#घोषणा WC0_SSUSB0_CDEN		BIT(6)
#घोषणा WC0_IS_SPM_EN		BIT(1)

/* mt2712 etc */
#घोषणा PERI_SSUSB_SPM_CTRL	0x0
#घोषणा SSC_IP_SLEEP_EN	BIT(4)
#घोषणा SSC_SPM_INT_EN		BIT(1)

क्रमागत ssusb_uwk_vers अणु
	SSUSB_UWK_V1 = 1,
	SSUSB_UWK_V2,
	SSUSB_UWK_V1_1 = 101,	/* specअगरic revision 1.01 */
	SSUSB_UWK_V1_2,		/* specअगरic revision 1.02 */
पूर्ण;

/*
 * ip-sleep wakeup mode:
 * all घड़ीs can be turn off, but घातer करोमुख्य should be kept on
 */
अटल व्योम ssusb_wakeup_ip_sleep_set(काष्ठा ssusb_mtk *ssusb, bool enable)
अणु
	u32 reg, msk, val;

	चयन (ssusb->uwk_vers) अणु
	हाल SSUSB_UWK_V1:
		reg = ssusb->uwk_reg_base + PERI_WK_CTRL1;
		msk = WC1_IS_EN | WC1_IS_C(0xf) | WC1_IS_P;
		val = enable ? (WC1_IS_EN | WC1_IS_C(0x8)) : 0;
		अवरोध;
	हाल SSUSB_UWK_V1_1:
		reg = ssusb->uwk_reg_base + PERI_WK_CTRL0;
		msk = WC0_IS_EN | WC0_IS_C(0xf) | WC0_IS_P;
		val = enable ? (WC0_IS_EN | WC0_IS_C(0x8)) : 0;
		अवरोध;
	हाल SSUSB_UWK_V1_2:
		reg = ssusb->uwk_reg_base + PERI_WK_CTRL0;
		msk = WC0_SSUSB0_CDEN | WC0_IS_SPM_EN;
		val = enable ? msk : 0;
		अवरोध;
	हाल SSUSB_UWK_V2:
		reg = ssusb->uwk_reg_base + PERI_SSUSB_SPM_CTRL;
		msk = SSC_IP_SLEEP_EN | SSC_SPM_INT_EN;
		val = enable ? msk : 0;
		अवरोध;
	शेष:
		वापस;
	पूर्ण
	regmap_update_bits(ssusb->uwk, reg, msk, val);
पूर्ण

पूर्णांक ssusb_wakeup_of_property_parse(काष्ठा ssusb_mtk *ssusb,
				काष्ठा device_node *dn)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक ret;

	/* wakeup function is optional */
	ssusb->uwk_en = of_property_पढ़ो_bool(dn, "wakeup-source");
	अगर (!ssusb->uwk_en)
		वापस 0;

	ret = of_parse_phandle_with_fixed_args(dn,
				"mediatek,syscon-wakeup", 2, 0, &args);
	अगर (ret)
		वापस ret;

	ssusb->uwk_reg_base = args.args[0];
	ssusb->uwk_vers = args.args[1];
	ssusb->uwk = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	dev_info(ssusb->dev, "uwk - reg:0x%x, version:%d\n",
			ssusb->uwk_reg_base, ssusb->uwk_vers);

	वापस PTR_ERR_OR_ZERO(ssusb->uwk);
पूर्ण

व्योम ssusb_wakeup_set(काष्ठा ssusb_mtk *ssusb, bool enable)
अणु
	अगर (ssusb->uwk_en)
		ssusb_wakeup_ip_sleep_set(ssusb, enable);
पूर्ण

अटल व्योम host_ports_num_get(काष्ठा ssusb_mtk *ssusb)
अणु
	u32 xhci_cap;

	xhci_cap = mtu3_पढ़ोl(ssusb->ippc_base, U3D_SSUSB_IP_XHCI_CAP);
	ssusb->u2_ports = SSUSB_IP_XHCI_U2_PORT_NUM(xhci_cap);
	ssusb->u3_ports = SSUSB_IP_XHCI_U3_PORT_NUM(xhci_cap);

	dev_dbg(ssusb->dev, "host - u2_ports:%d, u3_ports:%d\n",
		 ssusb->u2_ports, ssusb->u3_ports);
पूर्ण

/* only configure ports will be used later */
पूर्णांक ssusb_host_enable(काष्ठा ssusb_mtk *ssusb)
अणु
	व्योम __iomem *ibase = ssusb->ippc_base;
	पूर्णांक num_u3p = ssusb->u3_ports;
	पूर्णांक num_u2p = ssusb->u2_ports;
	पूर्णांक u3_ports_disabled;
	u32 check_clk;
	u32 value;
	पूर्णांक i;

	/* घातer on host ip */
	mtu3_clrbits(ibase, U3D_SSUSB_IP_PW_CTRL1, SSUSB_IP_HOST_PDN);

	/* घातer on and enable u3 ports except skipped ones */
	u3_ports_disabled = 0;
	क्रम (i = 0; i < num_u3p; i++) अणु
		अगर ((0x1 << i) & ssusb->u3p_dis_msk) अणु
			u3_ports_disabled++;
			जारी;
		पूर्ण

		value = mtu3_पढ़ोl(ibase, SSUSB_U3_CTRL(i));
		value &= ~(SSUSB_U3_PORT_PDN | SSUSB_U3_PORT_DIS);
		value |= SSUSB_U3_PORT_HOST_SEL;
		mtu3_ग_लिखोl(ibase, SSUSB_U3_CTRL(i), value);
	पूर्ण

	/* घातer on and enable all u2 ports */
	क्रम (i = 0; i < num_u2p; i++) अणु
		value = mtu3_पढ़ोl(ibase, SSUSB_U2_CTRL(i));
		value &= ~(SSUSB_U2_PORT_PDN | SSUSB_U2_PORT_DIS);
		value |= SSUSB_U2_PORT_HOST_SEL;
		mtu3_ग_लिखोl(ibase, SSUSB_U2_CTRL(i), value);
	पूर्ण

	check_clk = SSUSB_XHCI_RST_B_STS;
	अगर (num_u3p > u3_ports_disabled)
		check_clk = SSUSB_U3_MAC_RST_B_STS;

	वापस ssusb_check_घड़ीs(ssusb, check_clk);
पूर्ण

पूर्णांक ssusb_host_disable(काष्ठा ssusb_mtk *ssusb, bool suspend)
अणु
	व्योम __iomem *ibase = ssusb->ippc_base;
	पूर्णांक num_u3p = ssusb->u3_ports;
	पूर्णांक num_u2p = ssusb->u2_ports;
	u32 value;
	पूर्णांक ret;
	पूर्णांक i;

	/* घातer करोwn and disable u3 ports except skipped ones */
	क्रम (i = 0; i < num_u3p; i++) अणु
		अगर ((0x1 << i) & ssusb->u3p_dis_msk)
			जारी;

		value = mtu3_पढ़ोl(ibase, SSUSB_U3_CTRL(i));
		value |= SSUSB_U3_PORT_PDN;
		value |= suspend ? 0 : SSUSB_U3_PORT_DIS;
		mtu3_ग_लिखोl(ibase, SSUSB_U3_CTRL(i), value);
	पूर्ण

	/* घातer करोwn and disable all u2 ports */
	क्रम (i = 0; i < num_u2p; i++) अणु
		value = mtu3_पढ़ोl(ibase, SSUSB_U2_CTRL(i));
		value |= SSUSB_U2_PORT_PDN;
		value |= suspend ? 0 : SSUSB_U2_PORT_DIS;
		mtu3_ग_लिखोl(ibase, SSUSB_U2_CTRL(i), value);
	पूर्ण

	/* घातer करोwn host ip */
	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTRL1, SSUSB_IP_HOST_PDN);

	अगर (!suspend)
		वापस 0;

	/* रुको क्रम host ip to sleep */
	ret = पढ़ोl_poll_समयout(ibase + U3D_SSUSB_IP_PW_STS1, value,
			  (value & SSUSB_IP_SLEEP_STS), 100, 100000);
	अगर (ret)
		dev_err(ssusb->dev, "ip sleep failed!!!\n");

	वापस ret;
पूर्ण

अटल व्योम ssusb_host_setup(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा otg_चयन_mtk *otg_sx = &ssusb->otg_चयन;

	host_ports_num_get(ssusb);

	/*
	 * घातer on host and घातer on/enable all ports
	 * अगर support OTG, gadget driver will चयन port0 to device mode
	 */
	ssusb_host_enable(ssusb);

	अगर (otg_sx->manual_drd_enabled)
		ssusb_set_क्रमce_mode(ssusb, MTU3_DR_FORCE_HOST);

	/* अगर port0 supports dual-role, works as host mode by शेष */
	ssusb_set_vbus(&ssusb->otg_चयन, 1);
पूर्ण

अटल व्योम ssusb_host_cleanup(काष्ठा ssusb_mtk *ssusb)
अणु
	अगर (ssusb->is_host)
		ssusb_set_vbus(&ssusb->otg_चयन, 0);

	ssusb_host_disable(ssusb, false);
पूर्ण

/*
 * If host supports multiple ports, the VBUSes(5V) of ports except port0
 * which supports OTG are better to be enabled by शेष in DTS.
 * Because the host driver will keep link with devices attached when प्रणाली
 * enters suspend mode, so no need to control VBUSes after initialization.
 */
पूर्णांक ssusb_host_init(काष्ठा ssusb_mtk *ssusb, काष्ठा device_node *parent_dn)
अणु
	काष्ठा device *parent_dev = ssusb->dev;
	पूर्णांक ret;

	ssusb_host_setup(ssusb);

	ret = of_platक्रमm_populate(parent_dn, शून्य, शून्य, parent_dev);
	अगर (ret) अणु
		dev_dbg(parent_dev, "failed to create child devices at %pOF\n",
				parent_dn);
		वापस ret;
	पूर्ण

	dev_info(parent_dev, "xHCI platform device register success...\n");

	वापस 0;
पूर्ण

व्योम ssusb_host_निकास(काष्ठा ssusb_mtk *ssusb)
अणु
	of_platक्रमm_depopulate(ssusb->dev);
	ssusb_host_cleanup(ssusb);
पूर्ण
