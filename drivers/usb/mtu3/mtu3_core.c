<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mtu3_core.c - hardware access layer and gadget init/निकास of
 *                     MediaTek usb3 Dual-Role Controller Driver
 *
 * Copyright (C) 2016 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "mtu3.h"
#समावेश "mtu3_dr.h"
#समावेश "mtu3_debug.h"
#समावेश "mtu3_trace.h"

अटल पूर्णांक ep_fअगरo_alloc(काष्ठा mtu3_ep *mep, u32 seg_size)
अणु
	काष्ठा mtu3_fअगरo_info *fअगरo = mep->fअगरo;
	u32 num_bits = DIV_ROUND_UP(seg_size, MTU3_EP_FIFO_UNIT);
	u32 start_bit;

	/* ensure that @mep->fअगरo_seg_size is घातer of two */
	num_bits = roundup_घात_of_two(num_bits);
	अगर (num_bits > fअगरo->limit)
		वापस -EINVAL;

	mep->fअगरo_seg_size = num_bits * MTU3_EP_FIFO_UNIT;
	num_bits = num_bits * (mep->slot + 1);
	start_bit = biपंचांगap_find_next_zero_area(fअगरo->biपंचांगap,
			fअगरo->limit, 0, num_bits, 0);
	अगर (start_bit >= fअगरo->limit)
		वापस -EOVERFLOW;

	biपंचांगap_set(fअगरo->biपंचांगap, start_bit, num_bits);
	mep->fअगरo_size = num_bits * MTU3_EP_FIFO_UNIT;
	mep->fअगरo_addr = fअगरo->base + MTU3_EP_FIFO_UNIT * start_bit;

	dev_dbg(mep->mtu->dev, "%s fifo:%#x/%#x, start_bit: %d\n",
		__func__, mep->fअगरo_seg_size, mep->fअगरo_size, start_bit);

	वापस mep->fअगरo_addr;
पूर्ण

अटल व्योम ep_fअगरo_मुक्त(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3_fअगरo_info *fअगरo = mep->fअगरo;
	u32 addr = mep->fअगरo_addr;
	u32 bits = mep->fअगरo_size / MTU3_EP_FIFO_UNIT;
	u32 start_bit;

	अगर (unlikely(addr < fअगरo->base || bits > fअगरo->limit))
		वापस;

	start_bit = (addr - fअगरo->base) / MTU3_EP_FIFO_UNIT;
	biपंचांगap_clear(fअगरo->biपंचांगap, start_bit, bits);
	mep->fअगरo_size = 0;
	mep->fअगरo_seg_size = 0;

	dev_dbg(mep->mtu->dev, "%s size:%#x/%#x, start_bit: %d\n",
		__func__, mep->fअगरo_seg_size, mep->fअगरo_size, start_bit);
पूर्ण

/* enable/disable U3D SS function */
अटल अंतरभूत व्योम mtu3_ss_func_set(काष्ठा mtu3 *mtu, bool enable)
अणु
	/* If usb3_en==0, LTSSM will go to SS.Disable state */
	अगर (enable)
		mtu3_setbits(mtu->mac_base, U3D_USB3_CONFIG, USB3_EN);
	अन्यथा
		mtu3_clrbits(mtu->mac_base, U3D_USB3_CONFIG, USB3_EN);

	dev_dbg(mtu->dev, "USB3_EN = %d\n", !!enable);
पूर्ण

/* set/clear U3D HS device soft connect */
अटल अंतरभूत व्योम mtu3_hs_softconn_set(काष्ठा mtu3 *mtu, bool enable)
अणु
	अगर (enable) अणु
		mtu3_setbits(mtu->mac_base, U3D_POWER_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABLE);
	पूर्ण अन्यथा अणु
		mtu3_clrbits(mtu->mac_base, U3D_POWER_MANAGEMENT,
			SOFT_CONN | SUSPENDM_ENABLE);
	पूर्ण
	dev_dbg(mtu->dev, "SOFTCONN = %d\n", !!enable);
पूर्ण

/* only port0 of U2/U3 supports device mode */
अटल पूर्णांक mtu3_device_enable(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *ibase = mtu->ippc_base;
	u32 check_clk = 0;

	mtu3_clrbits(ibase, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);

	अगर (mtu->is_u3_ip) अणु
		check_clk = SSUSB_U3_MAC_RST_B_STS;
		mtu3_clrbits(ibase, SSUSB_U3_CTRL(0),
			(SSUSB_U3_PORT_DIS | SSUSB_U3_PORT_PDN |
			SSUSB_U3_PORT_HOST_SEL));
	पूर्ण
	mtu3_clrbits(ibase, SSUSB_U2_CTRL(0),
		(SSUSB_U2_PORT_DIS | SSUSB_U2_PORT_PDN |
		SSUSB_U2_PORT_HOST_SEL));

	अगर (mtu->ssusb->dr_mode == USB_DR_MODE_OTG) अणु
		mtu3_setbits(ibase, SSUSB_U2_CTRL(0), SSUSB_U2_PORT_OTG_SEL);
		अगर (mtu->is_u3_ip)
			mtu3_setbits(ibase, SSUSB_U3_CTRL(0),
				     SSUSB_U3_PORT_DUAL_MODE);
	पूर्ण

	वापस ssusb_check_घड़ीs(mtu->ssusb, check_clk);
पूर्ण

अटल व्योम mtu3_device_disable(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *ibase = mtu->ippc_base;

	अगर (mtu->is_u3_ip)
		mtu3_setbits(ibase, SSUSB_U3_CTRL(0),
			(SSUSB_U3_PORT_DIS | SSUSB_U3_PORT_PDN));

	mtu3_setbits(ibase, SSUSB_U2_CTRL(0),
		SSUSB_U2_PORT_DIS | SSUSB_U2_PORT_PDN);

	अगर (mtu->ssusb->dr_mode == USB_DR_MODE_OTG) अणु
		mtu3_clrbits(ibase, SSUSB_U2_CTRL(0), SSUSB_U2_PORT_OTG_SEL);
		अगर (mtu->is_u3_ip)
			mtu3_clrbits(ibase, SSUSB_U3_CTRL(0),
				     SSUSB_U3_PORT_DUAL_MODE);
	पूर्ण

	mtu3_setbits(ibase, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);
पूर्ण

/* reset U3D's device module. */
अटल व्योम mtu3_device_reset(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *ibase = mtu->ippc_base;

	mtu3_setbits(ibase, U3D_SSUSB_DEV_RST_CTRL, SSUSB_DEV_SW_RST);
	udelay(1);
	mtu3_clrbits(ibase, U3D_SSUSB_DEV_RST_CTRL, SSUSB_DEV_SW_RST);
पूर्ण

अटल व्योम mtu3_पूर्णांकr_status_clear(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;

	/* Clear EP0 and Tx/Rx EPn पूर्णांकerrupts status */
	mtu3_ग_लिखोl(mbase, U3D_EPISR, ~0x0);
	/* Clear U2 USB common पूर्णांकerrupts status */
	mtu3_ग_लिखोl(mbase, U3D_COMMON_USB_INTR, ~0x0);
	/* Clear U3 LTSSM पूर्णांकerrupts status */
	mtu3_ग_लिखोl(mbase, U3D_LTSSM_INTR, ~0x0);
	/* Clear speed change पूर्णांकerrupt status */
	mtu3_ग_लिखोl(mbase, U3D_DEV_LINK_INTR, ~0x0);
	/* Clear QMU पूर्णांकerrupt status */
	mtu3_ग_लिखोl(mbase, U3D_QISAR0, ~0x0);
पूर्ण

/* disable all पूर्णांकerrupts */
अटल व्योम mtu3_पूर्णांकr_disable(काष्ठा mtu3 *mtu)
अणु
	/* Disable level 1 पूर्णांकerrupts */
	mtu3_ग_लिखोl(mtu->mac_base, U3D_LV1IECR, ~0x0);
	/* Disable endpoपूर्णांक पूर्णांकerrupts */
	mtu3_ग_लिखोl(mtu->mac_base, U3D_EPIECR, ~0x0);
	mtu3_पूर्णांकr_status_clear(mtu);
पूर्ण

/* enable प्रणाली global पूर्णांकerrupt */
अटल व्योम mtu3_पूर्णांकr_enable(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 value;

	/*Enable level 1 पूर्णांकerrupts (BMU, QMU, MAC3, DMA, MAC2, EPCTL) */
	value = BMU_INTR | QMU_INTR | MAC3_INTR | MAC2_INTR | EP_CTRL_INTR;
	mtu3_ग_लिखोl(mbase, U3D_LV1IESR, value);

	/* Enable U2 common USB पूर्णांकerrupts */
	value = SUSPEND_INTR | RESUME_INTR | RESET_INTR;
	mtu3_ग_लिखोl(mbase, U3D_COMMON_USB_INTR_ENABLE, value);

	अगर (mtu->is_u3_ip) अणु
		/* Enable U3 LTSSM पूर्णांकerrupts */
		value = HOT_RST_INTR | WARM_RST_INTR |
			ENTER_U3_INTR | EXIT_U3_INTR;
		mtu3_ग_लिखोl(mbase, U3D_LTSSM_INTR_ENABLE, value);
	पूर्ण

	/* Enable QMU पूर्णांकerrupts. */
	value = TXQ_CSERR_INT | TXQ_LENERR_INT | RXQ_CSERR_INT |
			RXQ_LENERR_INT | RXQ_ZLPERR_INT;
	mtu3_ग_लिखोl(mbase, U3D_QIESR1, value);

	/* Enable speed change पूर्णांकerrupt */
	mtu3_ग_लिखोl(mbase, U3D_DEV_LINK_INTR_ENABLE, SSUSB_DEV_SPEED_CHG_INTR);
पूर्ण

व्योम mtu3_set_speed(काष्ठा mtu3 *mtu, क्रमागत usb_device_speed speed)
अणु
	व्योम __iomem *mbase = mtu->mac_base;

	अगर (speed > mtu->max_speed)
		speed = mtu->max_speed;

	चयन (speed) अणु
	हाल USB_SPEED_FULL:
		/* disable U3 SS function */
		mtu3_clrbits(mbase, U3D_USB3_CONFIG, USB3_EN);
		/* disable HS function */
		mtu3_clrbits(mbase, U3D_POWER_MANAGEMENT, HS_ENABLE);
		अवरोध;
	हाल USB_SPEED_HIGH:
		mtu3_clrbits(mbase, U3D_USB3_CONFIG, USB3_EN);
		/* HS/FS detected by HW */
		mtu3_setbits(mbase, U3D_POWER_MANAGEMENT, HS_ENABLE);
		अवरोध;
	हाल USB_SPEED_SUPER:
		mtu3_clrbits(mtu->ippc_base, SSUSB_U3_CTRL(0),
			     SSUSB_U3_PORT_SSP_SPEED);
		अवरोध;
	हाल USB_SPEED_SUPER_PLUS:
			mtu3_setbits(mtu->ippc_base, SSUSB_U3_CTRL(0),
			     SSUSB_U3_PORT_SSP_SPEED);
		अवरोध;
	शेष:
		dev_err(mtu->dev, "invalid speed: %s\n",
			usb_speed_string(speed));
		वापस;
	पूर्ण

	mtu->speed = speed;
	dev_dbg(mtu->dev, "set speed: %s\n", usb_speed_string(speed));
पूर्ण

/* CSR रेजिस्टरs will be reset to शेष value अगर port is disabled */
अटल व्योम mtu3_csr_init(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;

	अगर (mtu->is_u3_ip) अणु
		/* disable LGO_U1/U2 by शेष */
		mtu3_clrbits(mbase, U3D_LINK_POWER_CONTROL,
				SW_U1_REQUEST_ENABLE | SW_U2_REQUEST_ENABLE);
		/* enable accept LGO_U1/U2 link command from host */
		mtu3_setbits(mbase, U3D_LINK_POWER_CONTROL,
				SW_U1_ACCEPT_ENABLE | SW_U2_ACCEPT_ENABLE);
		/* device responses to u3_निकास from host स्वतःmatically */
		mtu3_clrbits(mbase, U3D_LTSSM_CTRL, SOFT_U3_EXIT_EN);
		/* स्वतःmatically build U2 link when U3 detect fail */
		mtu3_setbits(mbase, U3D_USB2_TEST_MODE, U2U3_AUTO_SWITCH);
		/* स्वतः clear SOFT_CONN when clear USB3_EN अगर work as HS */
		mtu3_setbits(mbase, U3D_U3U2_SWITCH_CTRL, SOFTCON_CLR_AUTO_EN);
	पूर्ण

	/* delay about 0.1us from detecting reset to send chirp-K */
	mtu3_clrbits(mbase, U3D_LINK_RESET_INFO, WTCHRP_MSK);
	/* enable स्वतःmatical HWRW from L1 */
	mtu3_setbits(mbase, U3D_POWER_MANAGEMENT, LPM_HRWE);
पूर्ण

/* reset: u2 - data toggle, u3 - SeqN, flow control status etc */
अटल व्योम mtu3_ep_reset(काष्ठा mtu3_ep *mep)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;
	u32 rst_bit = EP_RST(mep->is_in, mep->epnum);

	mtu3_setbits(mtu->mac_base, U3D_EP_RST, rst_bit);
	mtu3_clrbits(mtu->mac_base, U3D_EP_RST, rst_bit);
पूर्ण

/* set/clear the stall and toggle bits क्रम non-ep0 */
व्योम mtu3_ep_stall_set(काष्ठा mtu3_ep *mep, bool set)
अणु
	काष्ठा mtu3 *mtu = mep->mtu;
	व्योम __iomem *mbase = mtu->mac_base;
	u8 epnum = mep->epnum;
	u32 csr;

	अगर (mep->is_in) अणु	/* TX */
		csr = mtu3_पढ़ोl(mbase, MU3D_EP_TXCR0(epnum)) & TX_W1C_BITS;
		अगर (set)
			csr |= TX_SENDSTALL;
		अन्यथा
			csr = (csr & (~TX_SENDSTALL)) | TX_SENTSTALL;
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR0(epnum), csr);
	पूर्ण अन्यथा अणु	/* RX */
		csr = mtu3_पढ़ोl(mbase, MU3D_EP_RXCR0(epnum)) & RX_W1C_BITS;
		अगर (set)
			csr |= RX_SENDSTALL;
		अन्यथा
			csr = (csr & (~RX_SENDSTALL)) | RX_SENTSTALL;
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR0(epnum), csr);
	पूर्ण

	अगर (!set) अणु
		mtu3_ep_reset(mep);
		mep->flags &= ~MTU3_EP_STALL;
	पूर्ण अन्यथा अणु
		mep->flags |= MTU3_EP_STALL;
	पूर्ण

	dev_dbg(mtu->dev, "%s: %s\n", mep->name,
		set ? "SEND STALL" : "CLEAR STALL, with EP RESET");
पूर्ण

व्योम mtu3_dev_on_off(काष्ठा mtu3 *mtu, पूर्णांक is_on)
अणु
	अगर (mtu->is_u3_ip && mtu->speed >= USB_SPEED_SUPER)
		mtu3_ss_func_set(mtu, is_on);
	अन्यथा
		mtu3_hs_softconn_set(mtu, is_on);

	dev_info(mtu->dev, "gadget (%s) pullup D%s\n",
		usb_speed_string(mtu->speed), is_on ? "+" : "-");
पूर्ण

व्योम mtu3_start(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;

	dev_dbg(mtu->dev, "%s devctl 0x%x\n", __func__,
		mtu3_पढ़ोl(mbase, U3D_DEVICE_CONTROL));

	mtu3_clrbits(mtu->ippc_base, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);

	mtu3_csr_init(mtu);
	mtu3_set_speed(mtu, mtu->speed);

	/* Initialize the शेष पूर्णांकerrupts */
	mtu3_पूर्णांकr_enable(mtu);
	mtu->is_active = 1;

	अगर (mtu->softconnect)
		mtu3_dev_on_off(mtu, 1);
पूर्ण

व्योम mtu3_stop(काष्ठा mtu3 *mtu)
अणु
	dev_dbg(mtu->dev, "%s\n", __func__);

	mtu3_पूर्णांकr_disable(mtu);

	अगर (mtu->softconnect)
		mtu3_dev_on_off(mtu, 0);

	mtu->is_active = 0;
	mtu3_setbits(mtu->ippc_base, U3D_SSUSB_IP_PW_CTRL2, SSUSB_IP_DEV_PDN);
पूर्ण

/* क्रम non-ep0 */
पूर्णांक mtu3_config_ep(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep,
			पूर्णांक पूर्णांकerval, पूर्णांक burst, पूर्णांक mult)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	bool gen2cp = mtu->gen2cp;
	पूर्णांक epnum = mep->epnum;
	u32 csr0, csr1, csr2;
	पूर्णांक fअगरo_sgsz, fअगरo_addr;
	पूर्णांक num_pkts;

	fअगरo_addr = ep_fअगरo_alloc(mep, mep->maxp);
	अगर (fअगरo_addr < 0) अणु
		dev_err(mtu->dev, "alloc ep fifo failed(%d)\n", mep->maxp);
		वापस -ENOMEM;
	पूर्ण
	fअगरo_sgsz = ilog2(mep->fअगरo_seg_size);
	dev_dbg(mtu->dev, "%s fifosz: %x(%x/%x)\n", __func__, fअगरo_sgsz,
		mep->fअगरo_seg_size, mep->fअगरo_size);

	अगर (mep->is_in) अणु
		csr0 = TX_TXMAXPKTSZ(mep->maxp);
		csr0 |= TX_DMAREQEN;

		num_pkts = (burst + 1) * (mult + 1) - 1;
		csr1 = TX_SS_BURST(burst) | TX_SLOT(mep->slot);
		csr1 |= TX_MAX_PKT(gen2cp, num_pkts) | TX_MULT(gen2cp, mult);

		csr2 = TX_FIFOADDR(fअगरo_addr >> 4);
		csr2 |= TX_FIFOSEGSIZE(fअगरo_sgsz);

		चयन (mep->type) अणु
		हाल USB_ENDPOINT_XFER_BULK:
			csr1 |= TX_TYPE(TYPE_BULK);
			अवरोध;
		हाल USB_ENDPOINT_XFER_ISOC:
			csr1 |= TX_TYPE(TYPE_ISO);
			csr2 |= TX_BINTERVAL(पूर्णांकerval);
			अवरोध;
		हाल USB_ENDPOINT_XFER_INT:
			csr1 |= TX_TYPE(TYPE_INT);
			csr2 |= TX_BINTERVAL(पूर्णांकerval);
			अवरोध;
		पूर्ण

		/* Enable QMU Done पूर्णांकerrupt */
		mtu3_setbits(mbase, U3D_QIESR0, QMU_TX_DONE_INT(epnum));

		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR0(epnum), csr0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR1(epnum), csr1);
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR2(epnum), csr2);

		dev_dbg(mtu->dev, "U3D_TX%d CSR0:%#x, CSR1:%#x, CSR2:%#x\n",
			epnum, mtu3_पढ़ोl(mbase, MU3D_EP_TXCR0(epnum)),
			mtu3_पढ़ोl(mbase, MU3D_EP_TXCR1(epnum)),
			mtu3_पढ़ोl(mbase, MU3D_EP_TXCR2(epnum)));
	पूर्ण अन्यथा अणु
		csr0 = RX_RXMAXPKTSZ(mep->maxp);
		csr0 |= RX_DMAREQEN;

		num_pkts = (burst + 1) * (mult + 1) - 1;
		csr1 = RX_SS_BURST(burst) | RX_SLOT(mep->slot);
		csr1 |= RX_MAX_PKT(gen2cp, num_pkts) | RX_MULT(gen2cp, mult);

		csr2 = RX_FIFOADDR(fअगरo_addr >> 4);
		csr2 |= RX_FIFOSEGSIZE(fअगरo_sgsz);

		चयन (mep->type) अणु
		हाल USB_ENDPOINT_XFER_BULK:
			csr1 |= RX_TYPE(TYPE_BULK);
			अवरोध;
		हाल USB_ENDPOINT_XFER_ISOC:
			csr1 |= RX_TYPE(TYPE_ISO);
			csr2 |= RX_BINTERVAL(पूर्णांकerval);
			अवरोध;
		हाल USB_ENDPOINT_XFER_INT:
			csr1 |= RX_TYPE(TYPE_INT);
			csr2 |= RX_BINTERVAL(पूर्णांकerval);
			अवरोध;
		पूर्ण

		/*Enable QMU Done पूर्णांकerrupt */
		mtu3_setbits(mbase, U3D_QIESR0, QMU_RX_DONE_INT(epnum));

		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR0(epnum), csr0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR1(epnum), csr1);
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR2(epnum), csr2);

		dev_dbg(mtu->dev, "U3D_RX%d CSR0:%#x, CSR1:%#x, CSR2:%#x\n",
			epnum, mtu3_पढ़ोl(mbase, MU3D_EP_RXCR0(epnum)),
			mtu3_पढ़ोl(mbase, MU3D_EP_RXCR1(epnum)),
			mtu3_पढ़ोl(mbase, MU3D_EP_RXCR2(epnum)));
	पूर्ण

	dev_dbg(mtu->dev, "csr0:%#x, csr1:%#x, csr2:%#x\n", csr0, csr1, csr2);
	dev_dbg(mtu->dev, "%s: %s, fifo-addr:%#x, fifo-size:%#x(%#x/%#x)\n",
		__func__, mep->name, mep->fअगरo_addr, mep->fअगरo_size,
		fअगरo_sgsz, mep->fअगरo_seg_size);

	वापस 0;
पूर्ण

/* क्रम non-ep0 */
व्योम mtu3_deconfig_ep(काष्ठा mtu3 *mtu, काष्ठा mtu3_ep *mep)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	पूर्णांक epnum = mep->epnum;

	अगर (mep->is_in) अणु
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR0(epnum), 0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR1(epnum), 0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_TXCR2(epnum), 0);
		mtu3_setbits(mbase, U3D_QIECR0, QMU_TX_DONE_INT(epnum));
	पूर्ण अन्यथा अणु
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR0(epnum), 0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR1(epnum), 0);
		mtu3_ग_लिखोl(mbase, MU3D_EP_RXCR2(epnum), 0);
		mtu3_setbits(mbase, U3D_QIECR0, QMU_RX_DONE_INT(epnum));
	पूर्ण

	mtu3_ep_reset(mep);
	ep_fअगरo_मुक्त(mep);

	dev_dbg(mtu->dev, "%s: %s\n", __func__, mep->name);
पूर्ण

/*
 * Two scenarios:
 * 1. when device IP supports SS, the fअगरo of EP0, TX EPs, RX EPs
 *	are separated;
 * 2. when supports only HS, the fअगरo is shared क्रम all EPs, and
 *	the capability रेजिस्टरs of @EPNTXFFSZ or @EPNRXFFSZ indicate
 *	the total fअगरo size of non-ep0, and ep0's is fixed to 64B,
 *	so the total fअगरo size is 64B + @EPNTXFFSZ;
 *	Due to the first 64B should be reserved क्रम EP0, non-ep0's fअगरo
 *	starts from offset 64 and are भागided पूर्णांकo two equal parts क्रम
 *	TX or RX EPs क्रम simplअगरication.
 */
अटल व्योम get_ep_fअगरo_config(काष्ठा mtu3 *mtu)
अणु
	काष्ठा mtu3_fअगरo_info *tx_fअगरo;
	काष्ठा mtu3_fअगरo_info *rx_fअगरo;
	u32 fअगरosize;

	अगर (mtu->is_u3_ip) अणु
		fअगरosize = mtu3_पढ़ोl(mtu->mac_base, U3D_CAP_EPNTXFFSZ);
		tx_fअगरo = &mtu->tx_fअगरo;
		tx_fअगरo->base = 0;
		tx_fअगरo->limit = fअगरosize / MTU3_EP_FIFO_UNIT;
		biपंचांगap_zero(tx_fअगरo->biपंचांगap, MTU3_FIFO_BIT_SIZE);

		fअगरosize = mtu3_पढ़ोl(mtu->mac_base, U3D_CAP_EPNRXFFSZ);
		rx_fअगरo = &mtu->rx_fअगरo;
		rx_fअगरo->base = 0;
		rx_fअगरo->limit = fअगरosize / MTU3_EP_FIFO_UNIT;
		biपंचांगap_zero(rx_fअगरo->biपंचांगap, MTU3_FIFO_BIT_SIZE);
		mtu->slot = MTU3_U3_IP_SLOT_DEFAULT;
	पूर्ण अन्यथा अणु
		fअगरosize = mtu3_पढ़ोl(mtu->mac_base, U3D_CAP_EPNTXFFSZ);
		tx_fअगरo = &mtu->tx_fअगरo;
		tx_fअगरo->base = MTU3_U2_IP_EP0_FIFO_SIZE;
		tx_fअगरo->limit = (fअगरosize / MTU3_EP_FIFO_UNIT) >> 1;
		biपंचांगap_zero(tx_fअगरo->biपंचांगap, MTU3_FIFO_BIT_SIZE);

		rx_fअगरo = &mtu->rx_fअगरo;
		rx_fअगरo->base =
			tx_fअगरo->base + tx_fअगरo->limit * MTU3_EP_FIFO_UNIT;
		rx_fअगरo->limit = tx_fअगरo->limit;
		biपंचांगap_zero(rx_fअगरo->biपंचांगap, MTU3_FIFO_BIT_SIZE);
		mtu->slot = MTU3_U2_IP_SLOT_DEFAULT;
	पूर्ण

	dev_dbg(mtu->dev, "%s, TX: base-%d, limit-%d; RX: base-%d, limit-%d\n",
		__func__, tx_fअगरo->base, tx_fअगरo->limit,
		rx_fअगरo->base, rx_fअगरo->limit);
पूर्ण

व्योम mtu3_ep0_setup(काष्ठा mtu3 *mtu)
अणु
	u32 maxpacket = mtu->g.ep0->maxpacket;
	u32 csr;

	dev_dbg(mtu->dev, "%s maxpacket: %d\n", __func__, maxpacket);

	csr = mtu3_पढ़ोl(mtu->mac_base, U3D_EP0CSR);
	csr &= ~EP0_MAXPKTSZ_MSK;
	csr |= EP0_MAXPKTSZ(maxpacket);
	csr &= EP0_W1C_BITS;
	mtu3_ग_लिखोl(mtu->mac_base, U3D_EP0CSR, csr);

	/* Enable EP0 पूर्णांकerrupt */
	mtu3_ग_लिखोl(mtu->mac_base, U3D_EPIESR, EP0ISR | SETUPENDISR);
पूर्ण

अटल पूर्णांक mtu3_mem_alloc(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	काष्ठा mtu3_ep *ep_array;
	पूर्णांक in_ep_num, out_ep_num;
	u32 cap_epinfo;
	पूर्णांक ret;
	पूर्णांक i;

	cap_epinfo = mtu3_पढ़ोl(mbase, U3D_CAP_EPINFO);
	in_ep_num = CAP_TX_EP_NUM(cap_epinfo);
	out_ep_num = CAP_RX_EP_NUM(cap_epinfo);

	dev_info(mtu->dev, "fifosz/epnum: Tx=%#x/%d, Rx=%#x/%d\n",
		 mtu3_पढ़ोl(mbase, U3D_CAP_EPNTXFFSZ), in_ep_num,
		 mtu3_पढ़ोl(mbase, U3D_CAP_EPNRXFFSZ), out_ep_num);

	/* one क्रम ep0, another is reserved */
	mtu->num_eps = min(in_ep_num, out_ep_num) + 1;
	ep_array = kसुस्मृति(mtu->num_eps * 2, माप(*ep_array), GFP_KERNEL);
	अगर (ep_array == शून्य)
		वापस -ENOMEM;

	mtu->ep_array = ep_array;
	mtu->in_eps = ep_array;
	mtu->out_eps = &ep_array[mtu->num_eps];
	/* ep0 uses in_eps[0], out_eps[0] is reserved */
	mtu->ep0 = mtu->in_eps;
	mtu->ep0->mtu = mtu;
	mtu->ep0->epnum = 0;

	क्रम (i = 1; i < mtu->num_eps; i++) अणु
		काष्ठा mtu3_ep *mep = mtu->in_eps + i;

		mep->fअगरo = &mtu->tx_fअगरo;
		mep = mtu->out_eps + i;
		mep->fअगरo = &mtu->rx_fअगरo;
	पूर्ण

	get_ep_fअगरo_config(mtu);

	ret = mtu3_qmu_init(mtu);
	अगर (ret)
		kमुक्त(mtu->ep_array);

	वापस ret;
पूर्ण

अटल व्योम mtu3_mem_मुक्त(काष्ठा mtu3 *mtu)
अणु
	mtu3_qmu_निकास(mtu);
	kमुक्त(mtu->ep_array);
पूर्ण

अटल व्योम mtu3_regs_init(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;

	/* be sure पूर्णांकerrupts are disabled beक्रमe registration of ISR */
	mtu3_पूर्णांकr_disable(mtu);

	mtu3_csr_init(mtu);

	/* U2/U3 detected by HW */
	mtu3_ग_लिखोl(mbase, U3D_DEVICE_CONF, 0);
	/* vbus detected by HW */
	mtu3_clrbits(mbase, U3D_MISC_CTRL, VBUS_FRC_EN | VBUS_ON);
	/* use new QMU क्रमmat when HW version >= 0x1003 */
	अगर (mtu->gen2cp)
		mtu3_ग_लिखोl(mbase, U3D_QFCR, ~0x0);
पूर्ण

अटल irqवापस_t mtu3_link_isr(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	क्रमागत usb_device_speed udev_speed;
	u32 maxpkt = 64;
	u32 link;
	u32 speed;

	link = mtu3_पढ़ोl(mbase, U3D_DEV_LINK_INTR);
	link &= mtu3_पढ़ोl(mbase, U3D_DEV_LINK_INTR_ENABLE);
	mtu3_ग_लिखोl(mbase, U3D_DEV_LINK_INTR, link); /* W1C */
	dev_dbg(mtu->dev, "=== LINK[%x] ===\n", link);

	अगर (!(link & SSUSB_DEV_SPEED_CHG_INTR))
		वापस IRQ_NONE;

	speed = SSUSB_DEV_SPEED(mtu3_पढ़ोl(mbase, U3D_DEVICE_CONF));

	चयन (speed) अणु
	हाल MTU3_SPEED_FULL:
		udev_speed = USB_SPEED_FULL;
		/*BESLCK = 4 < BESLCK_U3 = 10 < BESLDCK = 15 */
		mtu3_ग_लिखोl(mbase, U3D_USB20_LPM_PARAMETER, LPM_BESLDCK(0xf)
				| LPM_BESLCK(4) | LPM_BESLCK_U3(0xa));
		mtu3_setbits(mbase, U3D_POWER_MANAGEMENT,
				LPM_BESL_STALL | LPM_BESLD_STALL);
		अवरोध;
	हाल MTU3_SPEED_HIGH:
		udev_speed = USB_SPEED_HIGH;
		/*BESLCK = 4 < BESLCK_U3 = 10 < BESLDCK = 15 */
		mtu3_ग_लिखोl(mbase, U3D_USB20_LPM_PARAMETER, LPM_BESLDCK(0xf)
				| LPM_BESLCK(4) | LPM_BESLCK_U3(0xa));
		mtu3_setbits(mbase, U3D_POWER_MANAGEMENT,
				LPM_BESL_STALL | LPM_BESLD_STALL);
		अवरोध;
	हाल MTU3_SPEED_SUPER:
		udev_speed = USB_SPEED_SUPER;
		maxpkt = 512;
		अवरोध;
	हाल MTU3_SPEED_SUPER_PLUS:
		udev_speed = USB_SPEED_SUPER_PLUS;
		maxpkt = 512;
		अवरोध;
	शेष:
		udev_speed = USB_SPEED_UNKNOWN;
		अवरोध;
	पूर्ण
	dev_dbg(mtu->dev, "%s: %s\n", __func__, usb_speed_string(udev_speed));
	mtu3_dbg_trace(mtu->dev, "link speed %s",
		       usb_speed_string(udev_speed));

	mtu->g.speed = udev_speed;
	mtu->g.ep0->maxpacket = maxpkt;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;

	अगर (udev_speed == USB_SPEED_UNKNOWN)
		mtu3_gadget_disconnect(mtu);
	अन्यथा
		mtu3_ep0_setup(mtu);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtu3_u3_ltssm_isr(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 ltssm;

	ltssm = mtu3_पढ़ोl(mbase, U3D_LTSSM_INTR);
	ltssm &= mtu3_पढ़ोl(mbase, U3D_LTSSM_INTR_ENABLE);
	mtu3_ग_लिखोl(mbase, U3D_LTSSM_INTR, ltssm); /* W1C */
	dev_dbg(mtu->dev, "=== LTSSM[%x] ===\n", ltssm);
	trace_mtu3_u3_ltssm_isr(ltssm);

	अगर (ltssm & (HOT_RST_INTR | WARM_RST_INTR))
		mtu3_gadget_reset(mtu);

	अगर (ltssm & VBUS_FALL_INTR) अणु
		mtu3_ss_func_set(mtu, false);
		mtu3_gadget_reset(mtu);
	पूर्ण

	अगर (ltssm & VBUS_RISE_INTR)
		mtu3_ss_func_set(mtu, true);

	अगर (ltssm & EXIT_U3_INTR)
		mtu3_gadget_resume(mtu);

	अगर (ltssm & ENTER_U3_INTR)
		mtu3_gadget_suspend(mtu);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtu3_u2_common_isr(काष्ठा mtu3 *mtu)
अणु
	व्योम __iomem *mbase = mtu->mac_base;
	u32 u2comm;

	u2comm = mtu3_पढ़ोl(mbase, U3D_COMMON_USB_INTR);
	u2comm &= mtu3_पढ़ोl(mbase, U3D_COMMON_USB_INTR_ENABLE);
	mtu3_ग_लिखोl(mbase, U3D_COMMON_USB_INTR, u2comm); /* W1C */
	dev_dbg(mtu->dev, "=== U2COMM[%x] ===\n", u2comm);
	trace_mtu3_u2_common_isr(u2comm);

	अगर (u2comm & SUSPEND_INTR)
		mtu3_gadget_suspend(mtu);

	अगर (u2comm & RESUME_INTR)
		mtu3_gadget_resume(mtu);

	अगर (u2comm & RESET_INTR)
		mtu3_gadget_reset(mtu);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtu3_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mtu3 *mtu = (काष्ठा mtu3 *)data;
	अचिन्हित दीर्घ flags;
	u32 level1;

	spin_lock_irqsave(&mtu->lock, flags);

	/* U3D_LV1ISR is RU */
	level1 = mtu3_पढ़ोl(mtu->mac_base, U3D_LV1ISR);
	level1 &= mtu3_पढ़ोl(mtu->mac_base, U3D_LV1IER);

	अगर (level1 & EP_CTRL_INTR)
		mtu3_link_isr(mtu);

	अगर (level1 & MAC2_INTR)
		mtu3_u2_common_isr(mtu);

	अगर (level1 & MAC3_INTR)
		mtu3_u3_ltssm_isr(mtu);

	अगर (level1 & BMU_INTR)
		mtu3_ep0_isr(mtu);

	अगर (level1 & QMU_INTR)
		mtu3_qmu_isr(mtu);

	spin_unlock_irqrestore(&mtu->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mtu3_check_params(काष्ठा mtu3 *mtu)
अणु
	/* check the max_speed parameter */
	चयन (mtu->max_speed) अणु
	हाल USB_SPEED_FULL:
	हाल USB_SPEED_HIGH:
	हाल USB_SPEED_SUPER:
	हाल USB_SPEED_SUPER_PLUS:
		अवरोध;
	शेष:
		dev_err(mtu->dev, "invalid max_speed: %s\n",
			usb_speed_string(mtu->max_speed));
		fallthrough;
	हाल USB_SPEED_UNKNOWN:
		/* शेष as SSP */
		mtu->max_speed = USB_SPEED_SUPER_PLUS;
		अवरोध;
	पूर्ण

	अगर (!mtu->is_u3_ip && (mtu->max_speed > USB_SPEED_HIGH))
		mtu->max_speed = USB_SPEED_HIGH;

	mtu->speed = mtu->max_speed;

	dev_info(mtu->dev, "max_speed: %s\n",
		 usb_speed_string(mtu->max_speed));
पूर्ण

अटल पूर्णांक mtu3_hw_init(काष्ठा mtu3 *mtu)
अणु
	u32 value;
	पूर्णांक ret;

	value = mtu3_पढ़ोl(mtu->ippc_base, U3D_SSUSB_IP_TRUNK_VERS);
	mtu->hw_version = IP_TRUNK_VERS(value);
	mtu->gen2cp = !!(mtu->hw_version >= MTU3_TRUNK_VERS_1003);

	value = mtu3_पढ़ोl(mtu->ippc_base, U3D_SSUSB_IP_DEV_CAP);
	mtu->is_u3_ip = !!SSUSB_IP_DEV_U3_PORT_NUM(value);

	dev_info(mtu->dev, "IP version 0x%x(%s IP)\n", mtu->hw_version,
		mtu->is_u3_ip ? "U3" : "U2");

	mtu3_check_params(mtu);

	mtu3_device_reset(mtu);

	ret = mtu3_device_enable(mtu);
	अगर (ret) अणु
		dev_err(mtu->dev, "device enable failed %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mtu3_mem_alloc(mtu);
	अगर (ret)
		वापस -ENOMEM;

	mtu3_regs_init(mtu);

	वापस 0;
पूर्ण

अटल व्योम mtu3_hw_निकास(काष्ठा mtu3 *mtu)
अणु
	mtu3_device_disable(mtu);
	mtu3_mem_मुक्त(mtu);
पूर्ण

/*
 * we set 32-bit DMA mask by शेष, here check whether the controller
 * supports 36-bit DMA or not, अगर it करोes, set 36-bit DMA mask.
 */
अटल पूर्णांक mtu3_set_dma_mask(काष्ठा mtu3 *mtu)
अणु
	काष्ठा device *dev = mtu->dev;
	bool is_36bit = false;
	पूर्णांक ret = 0;
	u32 value;

	value = mtu3_पढ़ोl(mtu->mac_base, U3D_MISC_CTRL);
	अगर (value & DMA_ADDR_36BIT) अणु
		is_36bit = true;
		ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(36));
		/* If set 36-bit DMA mask fails, fall back to 32-bit DMA mask */
		अगर (ret) अणु
			is_36bit = false;
			ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
		पूर्ण
	पूर्ण
	dev_info(dev, "dma mask: %s bits\n", is_36bit ? "36" : "32");

	वापस ret;
पूर्ण

पूर्णांक ssusb_gadget_init(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा device *dev = ssusb->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा mtu3 *mtu = शून्य;
	पूर्णांक ret = -ENOMEM;

	mtu = devm_kzalloc(dev, माप(काष्ठा mtu3), GFP_KERNEL);
	अगर (mtu == शून्य)
		वापस -ENOMEM;

	mtu->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mtu->irq < 0)
		वापस mtu->irq;
	dev_info(dev, "irq %d\n", mtu->irq);

	mtu->mac_base = devm_platक्रमm_ioremap_resource_byname(pdev, "mac");
	अगर (IS_ERR(mtu->mac_base)) अणु
		dev_err(dev, "error mapping memory for dev mac\n");
		वापस PTR_ERR(mtu->mac_base);
	पूर्ण

	spin_lock_init(&mtu->lock);
	mtu->dev = dev;
	mtu->ippc_base = ssusb->ippc_base;
	ssusb->mac_base	= mtu->mac_base;
	ssusb->u3d = mtu;
	mtu->ssusb = ssusb;
	mtu->max_speed = usb_get_maximum_speed(dev);

	dev_dbg(dev, "mac_base=0x%p, ippc_base=0x%p\n",
		mtu->mac_base, mtu->ippc_base);

	ret = mtu3_hw_init(mtu);
	अगर (ret) अणु
		dev_err(dev, "mtu3 hw init failed:%d\n", ret);
		वापस ret;
	पूर्ण

	ret = mtu3_set_dma_mask(mtu);
	अगर (ret) अणु
		dev_err(dev, "mtu3 set dma_mask failed:%d\n", ret);
		जाओ dma_mask_err;
	पूर्ण

	ret = devm_request_irq(dev, mtu->irq, mtu3_irq, 0, dev_name(dev), mtu);
	अगर (ret) अणु
		dev_err(dev, "request irq %d failed!\n", mtu->irq);
		जाओ irq_err;
	पूर्ण

	device_init_wakeup(dev, true);

	ret = mtu3_gadget_setup(mtu);
	अगर (ret) अणु
		dev_err(dev, "mtu3 gadget init failed:%d\n", ret);
		जाओ gadget_err;
	पूर्ण

	/* init as host mode, घातer करोwn device IP क्रम घातer saving */
	अगर (mtu->ssusb->dr_mode == USB_DR_MODE_OTG)
		mtu3_stop(mtu);

	ssusb_dev_debugfs_init(ssusb);

	dev_dbg(dev, " %s() done...\n", __func__);

	वापस 0;

gadget_err:
	device_init_wakeup(dev, false);

dma_mask_err:
irq_err:
	mtu3_hw_निकास(mtu);
	ssusb->u3d = शून्य;
	dev_err(dev, " %s() fail...\n", __func__);

	वापस ret;
पूर्ण

व्योम ssusb_gadget_निकास(काष्ठा ssusb_mtk *ssusb)
अणु
	काष्ठा mtu3 *mtu = ssusb->u3d;

	mtu3_gadget_cleanup(mtu);
	device_init_wakeup(ssusb->dev, false);
	mtu3_hw_निकास(mtu);
पूर्ण
