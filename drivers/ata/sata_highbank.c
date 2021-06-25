<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Calxeda Highbank AHCI SATA platक्रमm driver
 * Copyright 2012 Calxeda, Inc.
 *
 * based on the AHCI SATA platक्रमm driver by Jeff Garzik and Anton Vorontsov
 */
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/libata.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "ahci.h"

#घोषणा CPHY_MAP(dev, addr) ((((dev) & 0x1f) << 7) | (((addr) >> 9) & 0x7f))
#घोषणा CPHY_ADDR(addr) (((addr) & 0x1ff) << 2)
#घोषणा SERDES_CR_CTL			0x80a0
#घोषणा SERDES_CR_ADDR			0x80a1
#घोषणा SERDES_CR_DATA			0x80a2
#घोषणा CR_BUSY				0x0001
#घोषणा CR_START			0x0001
#घोषणा CR_WR_RDN			0x0002
#घोषणा CPHY_TX_INPUT_STS		0x2001
#घोषणा CPHY_RX_INPUT_STS		0x2002
#घोषणा CPHY_SATA_TX_OVERRIDE		0x8000
#घोषणा CPHY_SATA_RX_OVERRIDE	 	0x4000
#घोषणा CPHY_TX_OVERRIDE		0x2004
#घोषणा CPHY_RX_OVERRIDE		0x2005
#घोषणा SPHY_LANE			0x100
#घोषणा SPHY_HALF_RATE			0x0001
#घोषणा CPHY_SATA_DPLL_MODE		0x0700
#घोषणा CPHY_SATA_DPLL_SHIFT		8
#घोषणा CPHY_SATA_DPLL_RESET		(1 << 11)
#घोषणा CPHY_SATA_TX_ATTEN		0x1c00
#घोषणा CPHY_SATA_TX_ATTEN_SHIFT	10
#घोषणा CPHY_PHY_COUNT			6
#घोषणा CPHY_LANE_COUNT			4
#घोषणा CPHY_PORT_COUNT			(CPHY_PHY_COUNT * CPHY_LANE_COUNT)

अटल DEFINE_SPINLOCK(cphy_lock);
/* Each of the 6 phys can have up to 4 sata ports attached to i. Map 0-based
 * sata ports to their phys and then to their lanes within the phys
 */
काष्ठा phy_lane_info अणु
	व्योम __iomem *phy_base;
	u8 lane_mapping;
	u8 phy_devs;
	u8 tx_atten;
पूर्ण;
अटल काष्ठा phy_lane_info port_data[CPHY_PORT_COUNT];

अटल DEFINE_SPINLOCK(sgpio_lock);
#घोषणा SCLOCK				0
#घोषणा SLOAD				1
#घोषणा SDATA				2
#घोषणा SGPIO_PINS			3
#घोषणा SGPIO_PORTS			8

काष्ठा ecx_plat_data अणु
	u32		n_ports;
	/* number of extra घड़ीs that the SGPIO PIC controller expects */
	u32		pre_घड़ीs;
	u32		post_घड़ीs;
	काष्ठा gpio_desc *sgpio_gpiod[SGPIO_PINS];
	u32		sgpio_pattern;
	u32		port_to_sgpio[SGPIO_PORTS];
पूर्ण;

#घोषणा SGPIO_SIGNALS			3
#घोषणा ECX_ACTIVITY_BITS		0x300000
#घोषणा ECX_ACTIVITY_SHIFT		0
#घोषणा ECX_LOCATE_BITS			0x80000
#घोषणा ECX_LOCATE_SHIFT		1
#घोषणा ECX_FAULT_BITS			0x400000
#घोषणा ECX_FAULT_SHIFT			2
अटल अंतरभूत पूर्णांक sgpio_bit_shअगरt(काष्ठा ecx_plat_data *pdata, u32 port,
				u32 shअगरt)
अणु
	वापस 1 << (3 * pdata->port_to_sgpio[port] + shअगरt);
पूर्ण

अटल व्योम ecx_parse_sgpio(काष्ठा ecx_plat_data *pdata, u32 port, u32 state)
अणु
	अगर (state & ECX_ACTIVITY_BITS)
		pdata->sgpio_pattern |= sgpio_bit_shअगरt(pdata, port,
						ECX_ACTIVITY_SHIFT);
	अन्यथा
		pdata->sgpio_pattern &= ~sgpio_bit_shअगरt(pdata, port,
						ECX_ACTIVITY_SHIFT);
	अगर (state & ECX_LOCATE_BITS)
		pdata->sgpio_pattern |= sgpio_bit_shअगरt(pdata, port,
						ECX_LOCATE_SHIFT);
	अन्यथा
		pdata->sgpio_pattern &= ~sgpio_bit_shअगरt(pdata, port,
						ECX_LOCATE_SHIFT);
	अगर (state & ECX_FAULT_BITS)
		pdata->sgpio_pattern |= sgpio_bit_shअगरt(pdata, port,
						ECX_FAULT_SHIFT);
	अन्यथा
		pdata->sgpio_pattern &= ~sgpio_bit_shअगरt(pdata, port,
						ECX_FAULT_SHIFT);
पूर्ण

/*
 * Tell the LED controller that the संकेत has changed by raising the घड़ी
 * line क्रम 50 uS and then lowering it क्रम 50 uS.
 */
अटल व्योम ecx_led_cycle_घड़ी(काष्ठा ecx_plat_data *pdata)
अणु
	gpiod_set_value(pdata->sgpio_gpiod[SCLOCK], 1);
	udelay(50);
	gpiod_set_value(pdata->sgpio_gpiod[SCLOCK], 0);
	udelay(50);
पूर्ण

अटल sमाप_प्रकार ecx_transmit_led_message(काष्ठा ata_port *ap, u32 state,
					sमाप_प्रकार size)
अणु
	काष्ठा ahci_host_priv *hpriv =  ap->host->निजी_data;
	काष्ठा ecx_plat_data *pdata = hpriv->plat_data;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक pmp, i;
	काष्ठा ahci_em_priv *emp;
	u32 sgpio_out;

	/* get the slot number from the message */
	pmp = (state & EM_MSG_LED_PMP_SLOT) >> 8;
	अगर (pmp < EM_MAX_SLOTS)
		emp = &pp->em_priv[pmp];
	अन्यथा
		वापस -EINVAL;

	अगर (!(hpriv->em_msg_type & EM_MSG_TYPE_LED))
		वापस size;

	spin_lock_irqsave(&sgpio_lock, flags);
	ecx_parse_sgpio(pdata, ap->port_no, state);
	sgpio_out = pdata->sgpio_pattern;
	क्रम (i = 0; i < pdata->pre_घड़ीs; i++)
		ecx_led_cycle_घड़ी(pdata);

	gpiod_set_value(pdata->sgpio_gpiod[SLOAD], 1);
	ecx_led_cycle_घड़ी(pdata);
	gpiod_set_value(pdata->sgpio_gpiod[SLOAD], 0);
	/*
	 * bit-bang out the SGPIO pattern, by consuming a bit and then
	 * घड़ीing it out.
	 */
	क्रम (i = 0; i < (SGPIO_SIGNALS * pdata->n_ports); i++) अणु
		gpiod_set_value(pdata->sgpio_gpiod[SDATA], sgpio_out & 1);
		sgpio_out >>= 1;
		ecx_led_cycle_घड़ी(pdata);
	पूर्ण
	क्रम (i = 0; i < pdata->post_घड़ीs; i++)
		ecx_led_cycle_घड़ी(pdata);

	/* save off new led state क्रम port/slot */
	emp->led_state = state;

	spin_unlock_irqrestore(&sgpio_lock, flags);
	वापस size;
पूर्ण

अटल व्योम highbank_set_em_messages(काष्ठा device *dev,
					काष्ठा ahci_host_priv *hpriv,
					काष्ठा ata_port_info *pi)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ecx_plat_data *pdata = hpriv->plat_data;
	पूर्णांक i;

	क्रम (i = 0; i < SGPIO_PINS; i++) अणु
		काष्ठा gpio_desc *gpiod;

		gpiod = devm_gpiod_get_index(dev, "calxeda,sgpio", i,
					     GPIOD_OUT_HIGH);
		अगर (IS_ERR(gpiod)) अणु
			dev_err(dev, "failed to get GPIO %d\n", i);
			जारी;
		पूर्ण
		gpiod_set_consumer_name(gpiod, "CX SGPIO");

		pdata->sgpio_gpiod[i] = gpiod;
	पूर्ण
	of_property_पढ़ो_u32_array(np, "calxeda,led-order",
						pdata->port_to_sgpio,
						pdata->n_ports);
	अगर (of_property_पढ़ो_u32(np, "calxeda,pre-clocks", &pdata->pre_घड़ीs))
		pdata->pre_घड़ीs = 0;
	अगर (of_property_पढ़ो_u32(np, "calxeda,post-clocks",
				&pdata->post_घड़ीs))
		pdata->post_घड़ीs = 0;

	/* store em_loc */
	hpriv->em_loc = 0;
	hpriv->em_buf_sz = 4;
	hpriv->em_msg_type = EM_MSG_TYPE_LED;
	pi->flags |= ATA_FLAG_EM | ATA_FLAG_SW_ACTIVITY;
पूर्ण

अटल u32 __combo_phy_reg_पढ़ो(u8 sata_port, u32 addr)
अणु
	u32 data;
	u8 dev = port_data[sata_port].phy_devs;
	spin_lock(&cphy_lock);
	ग_लिखोl(CPHY_MAP(dev, addr), port_data[sata_port].phy_base + 0x800);
	data = पढ़ोl(port_data[sata_port].phy_base + CPHY_ADDR(addr));
	spin_unlock(&cphy_lock);
	वापस data;
पूर्ण

अटल व्योम __combo_phy_reg_ग_लिखो(u8 sata_port, u32 addr, u32 data)
अणु
	u8 dev = port_data[sata_port].phy_devs;
	spin_lock(&cphy_lock);
	ग_लिखोl(CPHY_MAP(dev, addr), port_data[sata_port].phy_base + 0x800);
	ग_लिखोl(data, port_data[sata_port].phy_base + CPHY_ADDR(addr));
	spin_unlock(&cphy_lock);
पूर्ण

अटल व्योम combo_phy_रुको_क्रम_पढ़ोy(u8 sata_port)
अणु
	जबतक (__combo_phy_reg_पढ़ो(sata_port, SERDES_CR_CTL) & CR_BUSY)
		udelay(5);
पूर्ण

अटल u32 combo_phy_पढ़ो(u8 sata_port, u32 addr)
अणु
	combo_phy_रुको_क्रम_पढ़ोy(sata_port);
	__combo_phy_reg_ग_लिखो(sata_port, SERDES_CR_ADDR, addr);
	__combo_phy_reg_ग_लिखो(sata_port, SERDES_CR_CTL, CR_START);
	combo_phy_रुको_क्रम_पढ़ोy(sata_port);
	वापस __combo_phy_reg_पढ़ो(sata_port, SERDES_CR_DATA);
पूर्ण

अटल व्योम combo_phy_ग_लिखो(u8 sata_port, u32 addr, u32 data)
अणु
	combo_phy_रुको_क्रम_पढ़ोy(sata_port);
	__combo_phy_reg_ग_लिखो(sata_port, SERDES_CR_ADDR, addr);
	__combo_phy_reg_ग_लिखो(sata_port, SERDES_CR_DATA, data);
	__combo_phy_reg_ग_लिखो(sata_port, SERDES_CR_CTL, CR_WR_RDN | CR_START);
पूर्ण

अटल व्योम highbank_cphy_disable_overrides(u8 sata_port)
अणु
	u8 lane = port_data[sata_port].lane_mapping;
	u32 पंचांगp;
	अगर (unlikely(port_data[sata_port].phy_base == शून्य))
		वापस;
	पंचांगp = combo_phy_पढ़ो(sata_port, CPHY_RX_INPUT_STS + lane * SPHY_LANE);
	पंचांगp &= ~CPHY_SATA_RX_OVERRIDE;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);
पूर्ण

अटल व्योम cphy_override_tx_attenuation(u8 sata_port, u32 val)
अणु
	u8 lane = port_data[sata_port].lane_mapping;
	u32 पंचांगp;

	अगर (val & 0x8)
		वापस;

	पंचांगp = combo_phy_पढ़ो(sata_port, CPHY_TX_INPUT_STS + lane * SPHY_LANE);
	पंचांगp &= ~CPHY_SATA_TX_OVERRIDE;
	combo_phy_ग_लिखो(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp |= CPHY_SATA_TX_OVERRIDE;
	combo_phy_ग_लिखो(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp |= (val << CPHY_SATA_TX_ATTEN_SHIFT) & CPHY_SATA_TX_ATTEN;
	combo_phy_ग_लिखो(sata_port, CPHY_TX_OVERRIDE + lane * SPHY_LANE, पंचांगp);
पूर्ण

अटल व्योम cphy_override_rx_mode(u8 sata_port, u32 val)
अणु
	u8 lane = port_data[sata_port].lane_mapping;
	u32 पंचांगp;
	पंचांगp = combo_phy_पढ़ो(sata_port, CPHY_RX_INPUT_STS + lane * SPHY_LANE);
	पंचांगp &= ~CPHY_SATA_RX_OVERRIDE;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp |= CPHY_SATA_RX_OVERRIDE;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp &= ~CPHY_SATA_DPLL_MODE;
	पंचांगp |= val << CPHY_SATA_DPLL_SHIFT;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp |= CPHY_SATA_DPLL_RESET;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	पंचांगp &= ~CPHY_SATA_DPLL_RESET;
	combo_phy_ग_लिखो(sata_port, CPHY_RX_OVERRIDE + lane * SPHY_LANE, पंचांगp);

	msleep(15);
पूर्ण

अटल व्योम highbank_cphy_override_lane(u8 sata_port)
अणु
	u8 lane = port_data[sata_port].lane_mapping;
	u32 पंचांगp, k = 0;

	अगर (unlikely(port_data[sata_port].phy_base == शून्य))
		वापस;
	करो अणु
		पंचांगp = combo_phy_पढ़ो(sata_port, CPHY_RX_INPUT_STS +
						lane * SPHY_LANE);
	पूर्ण जबतक ((पंचांगp & SPHY_HALF_RATE) && (k++ < 1000));
	cphy_override_rx_mode(sata_port, 3);
	cphy_override_tx_attenuation(sata_port, port_data[sata_port].tx_atten);
पूर्ण

अटल पूर्णांक highbank_initialize_phys(काष्ठा device *dev, व्योम __iomem *addr)
अणु
	काष्ठा device_node *sata_node = dev->of_node;
	पूर्णांक phy_count = 0, phy, port = 0, i;
	व्योम __iomem *cphy_base[CPHY_PHY_COUNT] = अणुपूर्ण;
	काष्ठा device_node *phy_nodes[CPHY_PHY_COUNT] = अणुपूर्ण;
	u32 tx_atten[CPHY_PORT_COUNT] = अणुपूर्ण;

	स_रखो(port_data, 0, माप(काष्ठा phy_lane_info) * CPHY_PORT_COUNT);

	करो अणु
		u32 पंचांगp;
		काष्ठा of_phandle_args phy_data;
		अगर (of_parse_phandle_with_args(sata_node,
				"calxeda,port-phys", "#phy-cells",
				port, &phy_data))
			अवरोध;
		क्रम (phy = 0; phy < phy_count; phy++) अणु
			अगर (phy_nodes[phy] == phy_data.np)
				अवरोध;
		पूर्ण
		अगर (phy_nodes[phy] == शून्य) अणु
			phy_nodes[phy] = phy_data.np;
			cphy_base[phy] = of_iomap(phy_nodes[phy], 0);
			अगर (cphy_base[phy] == शून्य) अणु
				वापस 0;
			पूर्ण
			phy_count += 1;
		पूर्ण
		port_data[port].lane_mapping = phy_data.args[0];
		of_property_पढ़ो_u32(phy_nodes[phy], "phydev", &पंचांगp);
		port_data[port].phy_devs = पंचांगp;
		port_data[port].phy_base = cphy_base[phy];
		of_node_put(phy_data.np);
		port += 1;
	पूर्ण जबतक (port < CPHY_PORT_COUNT);
	of_property_पढ़ो_u32_array(sata_node, "calxeda,tx-atten",
				tx_atten, port);
	क्रम (i = 0; i < port; i++)
		port_data[i].tx_atten = (u8) tx_atten[i];
	वापस 0;
पूर्ण

/*
 * The Calxeda SATA phy पूर्णांकermittently fails to bring up a link with Gen3
 * Retrying the phy hard reset can work around the issue, but the drive
 * may fail again. In less than 150 out of 15000 test runs, it took more
 * than 10 tries क्रम the link to be established (but never more than 35).
 * Triple the maximum observed retry count to provide plenty of margin क्रम
 * rare events and to guarantee that the link is established.
 *
 * Also, the शेष 2 second समय-out on a failed drive is too दीर्घ in
 * this situation. The uboot implementation of the same driver function
 * uses a much लघुer समय-out period and never experiences a समय out
 * issue. Reducing the समय-out to 500ms improves the responsiveness.
 * The other timing स्थिरants were kept the same as the stock AHCI driver.
 * This change was also tested 15000 बार on 24 drives and none of them
 * experienced a समय out.
 */
अटल पूर्णांक ahci_highbank_hardreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *class,
				अचिन्हित दीर्घ deadline)
अणु
	अटल स्थिर अचिन्हित दीर्घ timing[] = अणु 5, 100, 500पूर्ण;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ahci_port_priv *pp = ap->निजी_data;
	काष्ठा ahci_host_priv *hpriv = ap->host->निजी_data;
	u8 *d2h_fis = pp->rx_fis + RX_FIS_D2H_REG;
	काष्ठा ata_taskfile tf;
	bool online;
	u32 sstatus;
	पूर्णांक rc;
	पूर्णांक retry = 100;

	hpriv->stop_engine(ap);

	/* clear D2H reception area to properly रुको क्रम D2H FIS */
	ata_tf_init(link->device, &tf);
	tf.command = ATA_BUSY;
	ata_tf_to_fis(&tf, 0, 0, d2h_fis);

	करो अणु
		highbank_cphy_disable_overrides(link->ap->port_no);
		rc = sata_link_hardreset(link, timing, deadline, &online, शून्य);
		highbank_cphy_override_lane(link->ap->port_no);

		/* If the status is 1, we are connected, but the link did not
		 * come up. So retry resetting the link again.
		 */
		अगर (sata_scr_पढ़ो(link, SCR_STATUS, &sstatus))
			अवरोध;
		अगर (!(sstatus & 0x3))
			अवरोध;
	पूर्ण जबतक (!online && retry--);

	hpriv->start_engine(ap);

	अगर (online)
		*class = ahci_dev_classअगरy(ap);

	वापस rc;
पूर्ण

अटल काष्ठा ata_port_operations ahci_highbank_ops = अणु
	.inherits		= &ahci_ops,
	.hardreset		= ahci_highbank_hardreset,
	.transmit_led_message   = ecx_transmit_led_message,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info ahci_highbank_port_info = अणु
	.flags          = AHCI_FLAG_COMMON,
	.pio_mask       = ATA_PIO4,
	.udma_mask      = ATA_UDMA6,
	.port_ops       = &ahci_highbank_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_highbank_platक्रमm_sht = अणु
	AHCI_SHT("sata_highbank"),
पूर्ण;

अटल स्थिर काष्ठा of_device_id ahci_of_match[] = अणु
	अणु .compatible = "calxeda,hb-ahci" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ahci_of_match);

अटल पूर्णांक ahci_highbank_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ahci_host_priv *hpriv;
	काष्ठा ecx_plat_data *pdata;
	काष्ठा ata_host *host;
	काष्ठा resource *mem;
	पूर्णांक irq;
	पूर्णांक i;
	पूर्णांक rc;
	u32 n_ports;
	काष्ठा ata_port_info pi = ahci_highbank_port_info;
	स्थिर काष्ठा ata_port_info *ppi[] = अणु &pi, शून्य पूर्ण;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!mem) अणु
		dev_err(dev, "no mmio space\n");
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		dev_err(dev, "no irq\n");
		वापस -EINVAL;
	पूर्ण

	hpriv = devm_kzalloc(dev, माप(*hpriv), GFP_KERNEL);
	अगर (!hpriv) अणु
		dev_err(dev, "can't alloc ahci_host_priv\n");
		वापस -ENOMEM;
	पूर्ण
	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(dev, "can't alloc ecx_plat_data\n");
		वापस -ENOMEM;
	पूर्ण

	hpriv->irq = irq;
	hpriv->flags |= (अचिन्हित दीर्घ)pi.निजी_data;

	hpriv->mmio = devm_ioremap(dev, mem->start, resource_size(mem));
	अगर (!hpriv->mmio) अणु
		dev_err(dev, "can't map %pR\n", mem);
		वापस -ENOMEM;
	पूर्ण

	rc = highbank_initialize_phys(dev, hpriv->mmio);
	अगर (rc)
		वापस rc;


	ahci_save_initial_config(dev, hpriv);

	/* prepare host */
	अगर (hpriv->cap & HOST_CAP_NCQ)
		pi.flags |= ATA_FLAG_NCQ;

	अगर (hpriv->cap & HOST_CAP_PMP)
		pi.flags |= ATA_FLAG_PMP;

	अगर (hpriv->cap & HOST_CAP_64)
		dma_set_coherent_mask(dev, DMA_BIT_MASK(64));

	/* CAP.NP someबार indicate the index of the last enabled
	 * port, at other बार, that of the last possible port, so
	 * determining the maximum port number requires looking at
	 * both CAP.NP and port_map.
	 */
	n_ports = max(ahci_nr_ports(hpriv->cap), fls(hpriv->port_map));

	pdata->n_ports = n_ports;
	hpriv->plat_data = pdata;
	highbank_set_em_messages(dev, hpriv, &pi);

	host = ata_host_alloc_pinfo(dev, ppi, n_ports);
	अगर (!host) अणु
		rc = -ENOMEM;
		जाओ err0;
	पूर्ण

	host->निजी_data = hpriv;

	अगर (!(hpriv->cap & HOST_CAP_SSS) || ahci_ignore_sss)
		host->flags |= ATA_HOST_PARALLEL_SCAN;

	क्रम (i = 0; i < host->n_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ata_port_desc(ap, "mmio %pR", mem);
		ata_port_desc(ap, "port 0x%x", 0x100 + ap->port_no * 0x80);

		/* set enclosure management message type */
		अगर (ap->flags & ATA_FLAG_EM)
			ap->em_message_type = hpriv->em_msg_type;

		/* disabled/not-implemented port */
		अगर (!(hpriv->port_map & (1 << i)))
			ap->ops = &ata_dummy_port_ops;
	पूर्ण

	rc = ahci_reset_controller(host);
	अगर (rc)
		जाओ err0;

	ahci_init_controller(host);
	ahci_prपूर्णांक_info(host, "platform");

	rc = ahci_host_activate(host, &ahci_highbank_platक्रमm_sht);
	अगर (rc)
		जाओ err0;

	वापस 0;
err0:
	वापस rc;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ahci_highbank_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	व्योम __iomem *mmio = hpriv->mmio;
	u32 ctl;

	अगर (hpriv->flags & AHCI_HFLAG_NO_SUSPEND) अणु
		dev_err(dev, "firmware update required for suspend/resume\n");
		वापस -EIO;
	पूर्ण

	/*
	 * AHCI spec rev1.1 section 8.3.3:
	 * Software must disable पूर्णांकerrupts prior to requesting a
	 * transition of the HBA to D3 state.
	 */
	ctl = पढ़ोl(mmio + HOST_CTL);
	ctl &= ~HOST_IRQ_EN;
	ग_लिखोl(ctl, mmio + HOST_CTL);
	पढ़ोl(mmio + HOST_CTL); /* flush */

	वापस ata_host_suspend(host, PMSG_SUSPEND);
पूर्ण

अटल पूर्णांक ahci_highbank_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	पूर्णांक rc;

	अगर (dev->घातer.घातer_state.event == PM_EVENT_SUSPEND) अणु
		rc = ahci_reset_controller(host);
		अगर (rc)
			वापस rc;

		ahci_init_controller(host);
	पूर्ण

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ahci_highbank_pm_ops,
		  ahci_highbank_suspend, ahci_highbank_resume);

अटल काष्ठा platक्रमm_driver ahci_highbank_driver = अणु
	.हटाओ = ata_platक्रमm_हटाओ_one,
        .driver = अणु
                .name = "highbank-ahci",
                .of_match_table = ahci_of_match,
                .pm = &ahci_highbank_pm_ops,
        पूर्ण,
	.probe = ahci_highbank_probe,
पूर्ण;

module_platक्रमm_driver(ahci_highbank_driver);

MODULE_DESCRIPTION("Calxeda Highbank AHCI SATA platform driver");
MODULE_AUTHOR("Mark Langsdorf <mark.langsdorf@calxeda.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("sata:highbank");
