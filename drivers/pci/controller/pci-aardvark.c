<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the Aardvark PCIe controller, used on Marvell Armada
 * 3700.
 *
 * Copyright (C) 2016 Marvell
 *
 * Author: Hezi Shahmoon <hezi.shahmoon@marvell.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci-ecam.h>
#समावेश <linux/init.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/msi.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_pci.h>

#समावेश "../pci.h"
#समावेश "../pci-bridge-emul.h"

/* PCIe core रेजिस्टरs */
#घोषणा PCIE_CORE_DEV_ID_REG					0x0
#घोषणा PCIE_CORE_CMD_STATUS_REG				0x4
#घोषणा     PCIE_CORE_CMD_IO_ACCESS_EN				BIT(0)
#घोषणा     PCIE_CORE_CMD_MEM_ACCESS_EN				BIT(1)
#घोषणा     PCIE_CORE_CMD_MEM_IO_REQ_EN				BIT(2)
#घोषणा PCIE_CORE_DEV_REV_REG					0x8
#घोषणा PCIE_CORE_PCIEXP_CAP					0xc0
#घोषणा PCIE_CORE_ERR_CAPCTL_REG				0x118
#घोषणा     PCIE_CORE_ERR_CAPCTL_ECRC_CHK_TX			BIT(5)
#घोषणा     PCIE_CORE_ERR_CAPCTL_ECRC_CHK_TX_EN			BIT(6)
#घोषणा     PCIE_CORE_ERR_CAPCTL_ECRC_CHCK			BIT(7)
#घोषणा     PCIE_CORE_ERR_CAPCTL_ECRC_CHCK_RCV			BIT(8)
#घोषणा     PCIE_CORE_INT_A_ASSERT_ENABLE			1
#घोषणा     PCIE_CORE_INT_B_ASSERT_ENABLE			2
#घोषणा     PCIE_CORE_INT_C_ASSERT_ENABLE			3
#घोषणा     PCIE_CORE_INT_D_ASSERT_ENABLE			4
/* PIO रेजिस्टरs base address and रेजिस्टर offsets */
#घोषणा PIO_BASE_ADDR				0x4000
#घोषणा PIO_CTRL				(PIO_BASE_ADDR + 0x0)
#घोषणा   PIO_CTRL_TYPE_MASK			GENMASK(3, 0)
#घोषणा   PIO_CTRL_ADDR_WIN_DISABLE		BIT(24)
#घोषणा PIO_STAT				(PIO_BASE_ADDR + 0x4)
#घोषणा   PIO_COMPLETION_STATUS_SHIFT		7
#घोषणा   PIO_COMPLETION_STATUS_MASK		GENMASK(9, 7)
#घोषणा   PIO_COMPLETION_STATUS_OK		0
#घोषणा   PIO_COMPLETION_STATUS_UR		1
#घोषणा   PIO_COMPLETION_STATUS_CRS		2
#घोषणा   PIO_COMPLETION_STATUS_CA		4
#घोषणा   PIO_NON_POSTED_REQ			BIT(0)
#घोषणा PIO_ADDR_LS				(PIO_BASE_ADDR + 0x8)
#घोषणा PIO_ADDR_MS				(PIO_BASE_ADDR + 0xc)
#घोषणा PIO_WR_DATA				(PIO_BASE_ADDR + 0x10)
#घोषणा PIO_WR_DATA_STRB			(PIO_BASE_ADDR + 0x14)
#घोषणा PIO_RD_DATA				(PIO_BASE_ADDR + 0x18)
#घोषणा PIO_START				(PIO_BASE_ADDR + 0x1c)
#घोषणा PIO_ISR					(PIO_BASE_ADDR + 0x20)
#घोषणा PIO_ISRM				(PIO_BASE_ADDR + 0x24)

/* Aardvark Control रेजिस्टरs */
#घोषणा CONTROL_BASE_ADDR			0x4800
#घोषणा PCIE_CORE_CTRL0_REG			(CONTROL_BASE_ADDR + 0x0)
#घोषणा     PCIE_GEN_SEL_MSK			0x3
#घोषणा     PCIE_GEN_SEL_SHIFT			0x0
#घोषणा     SPEED_GEN_1				0
#घोषणा     SPEED_GEN_2				1
#घोषणा     SPEED_GEN_3				2
#घोषणा     IS_RC_MSK				1
#घोषणा     IS_RC_SHIFT				2
#घोषणा     LANE_CNT_MSK			0x18
#घोषणा     LANE_CNT_SHIFT			0x3
#घोषणा     LANE_COUNT_1			(0 << LANE_CNT_SHIFT)
#घोषणा     LANE_COUNT_2			(1 << LANE_CNT_SHIFT)
#घोषणा     LANE_COUNT_4			(2 << LANE_CNT_SHIFT)
#घोषणा     LANE_COUNT_8			(3 << LANE_CNT_SHIFT)
#घोषणा     LINK_TRAINING_EN			BIT(6)
#घोषणा     LEGACY_INTA				BIT(28)
#घोषणा     LEGACY_INTB				BIT(29)
#घोषणा     LEGACY_INTC				BIT(30)
#घोषणा     LEGACY_INTD				BIT(31)
#घोषणा PCIE_CORE_CTRL1_REG			(CONTROL_BASE_ADDR + 0x4)
#घोषणा     HOT_RESET_GEN			BIT(0)
#घोषणा PCIE_CORE_CTRL2_REG			(CONTROL_BASE_ADDR + 0x8)
#घोषणा     PCIE_CORE_CTRL2_RESERVED		0x7
#घोषणा     PCIE_CORE_CTRL2_TD_ENABLE		BIT(4)
#घोषणा     PCIE_CORE_CTRL2_STRICT_ORDER_ENABLE	BIT(5)
#घोषणा     PCIE_CORE_CTRL2_OB_WIN_ENABLE	BIT(6)
#घोषणा     PCIE_CORE_CTRL2_MSI_ENABLE		BIT(10)
#घोषणा PCIE_CORE_REF_CLK_REG			(CONTROL_BASE_ADDR + 0x14)
#घोषणा     PCIE_CORE_REF_CLK_TX_ENABLE		BIT(1)
#घोषणा PCIE_MSG_LOG_REG			(CONTROL_BASE_ADDR + 0x30)
#घोषणा PCIE_ISR0_REG				(CONTROL_BASE_ADDR + 0x40)
#घोषणा PCIE_MSG_PM_PME_MASK			BIT(7)
#घोषणा PCIE_ISR0_MASK_REG			(CONTROL_BASE_ADDR + 0x44)
#घोषणा     PCIE_ISR0_MSI_INT_PENDING		BIT(24)
#घोषणा     PCIE_ISR0_INTX_ASSERT(val)		BIT(16 + (val))
#घोषणा     PCIE_ISR0_INTX_DEASSERT(val)	BIT(20 + (val))
#घोषणा	    PCIE_ISR0_ALL_MASK			GENMASK(26, 0)
#घोषणा PCIE_ISR1_REG				(CONTROL_BASE_ADDR + 0x48)
#घोषणा PCIE_ISR1_MASK_REG			(CONTROL_BASE_ADDR + 0x4C)
#घोषणा     PCIE_ISR1_POWER_STATE_CHANGE	BIT(4)
#घोषणा     PCIE_ISR1_FLUSH			BIT(5)
#घोषणा     PCIE_ISR1_INTX_ASSERT(val)		BIT(8 + (val))
#घोषणा     PCIE_ISR1_ALL_MASK			GENMASK(11, 4)
#घोषणा PCIE_MSI_ADDR_LOW_REG			(CONTROL_BASE_ADDR + 0x50)
#घोषणा PCIE_MSI_ADDR_HIGH_REG			(CONTROL_BASE_ADDR + 0x54)
#घोषणा PCIE_MSI_STATUS_REG			(CONTROL_BASE_ADDR + 0x58)
#घोषणा PCIE_MSI_MASK_REG			(CONTROL_BASE_ADDR + 0x5C)
#घोषणा PCIE_MSI_PAYLOAD_REG			(CONTROL_BASE_ADDR + 0x9C)

/* LMI रेजिस्टरs base address and रेजिस्टर offsets */
#घोषणा LMI_BASE_ADDR				0x6000
#घोषणा CFG_REG					(LMI_BASE_ADDR + 0x0)
#घोषणा     LTSSM_SHIFT				24
#घोषणा     LTSSM_MASK				0x3f
#घोषणा     LTSSM_L0				0x10
#घोषणा     RC_BAR_CONFIG			0x300

/* PCIe core controller रेजिस्टरs */
#घोषणा CTRL_CORE_BASE_ADDR			0x18000
#घोषणा CTRL_CONFIG_REG				(CTRL_CORE_BASE_ADDR + 0x0)
#घोषणा     CTRL_MODE_SHIFT			0x0
#घोषणा     CTRL_MODE_MASK			0x1
#घोषणा     PCIE_CORE_MODE_सूचीECT		0x0
#घोषणा     PCIE_CORE_MODE_COMMAND		0x1

/* PCIe Central Interrupts Registers */
#घोषणा CENTRAL_INT_BASE_ADDR			0x1b000
#घोषणा HOST_CTRL_INT_STATUS_REG		(CENTRAL_INT_BASE_ADDR + 0x0)
#घोषणा HOST_CTRL_INT_MASK_REG			(CENTRAL_INT_BASE_ADDR + 0x4)
#घोषणा     PCIE_IRQ_CMDQ_INT			BIT(0)
#घोषणा     PCIE_IRQ_MSI_STATUS_INT		BIT(1)
#घोषणा     PCIE_IRQ_CMD_SENT_DONE		BIT(3)
#घोषणा     PCIE_IRQ_DMA_INT			BIT(4)
#घोषणा     PCIE_IRQ_IB_DXFERDONE		BIT(5)
#घोषणा     PCIE_IRQ_OB_DXFERDONE		BIT(6)
#घोषणा     PCIE_IRQ_OB_RXFERDONE		BIT(7)
#घोषणा     PCIE_IRQ_COMPQ_INT			BIT(12)
#घोषणा     PCIE_IRQ_सूची_RD_DDR_DET		BIT(13)
#घोषणा     PCIE_IRQ_सूची_WR_DDR_DET		BIT(14)
#घोषणा     PCIE_IRQ_CORE_INT			BIT(16)
#घोषणा     PCIE_IRQ_CORE_INT_PIO		BIT(17)
#घोषणा     PCIE_IRQ_DPMU_INT			BIT(18)
#घोषणा     PCIE_IRQ_PCIE_MIS_INT		BIT(19)
#घोषणा     PCIE_IRQ_MSI_INT1_DET		BIT(20)
#घोषणा     PCIE_IRQ_MSI_INT2_DET		BIT(21)
#घोषणा     PCIE_IRQ_RC_DBELL_DET		BIT(22)
#घोषणा     PCIE_IRQ_EP_STATUS			BIT(23)
#घोषणा     PCIE_IRQ_ALL_MASK			0xfff0fb
#घोषणा     PCIE_IRQ_ENABLE_INTS_MASK		PCIE_IRQ_CORE_INT

/* Transaction types */
#घोषणा PCIE_CONFIG_RD_TYPE0			0x8
#घोषणा PCIE_CONFIG_RD_TYPE1			0x9
#घोषणा PCIE_CONFIG_WR_TYPE0			0xa
#घोषणा PCIE_CONFIG_WR_TYPE1			0xb

#घोषणा PIO_RETRY_CNT			500
#घोषणा PIO_RETRY_DELAY			2 /* 2 us*/

#घोषणा LINK_WAIT_MAX_RETRIES		10
#घोषणा LINK_WAIT_USLEEP_MIN		90000
#घोषणा LINK_WAIT_USLEEP_MAX		100000
#घोषणा RETRAIN_WAIT_MAX_RETRIES	10
#घोषणा RETRAIN_WAIT_USLEEP_US		2000

#घोषणा MSI_IRQ_NUM			32

काष्ठा advk_pcie अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *base;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;
	काष्ठा irq_chip irq_chip;
	काष्ठा irq_करोमुख्य *msi_करोमुख्य;
	काष्ठा irq_करोमुख्य *msi_inner_करोमुख्य;
	काष्ठा irq_chip msi_bottom_irq_chip;
	काष्ठा irq_chip msi_irq_chip;
	काष्ठा msi_करोमुख्य_info msi_करोमुख्य_info;
	DECLARE_BITMAP(msi_used, MSI_IRQ_NUM);
	काष्ठा mutex msi_used_lock;
	u16 msi_msg;
	पूर्णांक link_gen;
	काष्ठा pci_bridge_emul bridge;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा phy *phy;
पूर्ण;

अटल अंतरभूत व्योम advk_ग_लिखोl(काष्ठा advk_pcie *pcie, u32 val, u64 reg)
अणु
	ग_लिखोl(val, pcie->base + reg);
पूर्ण

अटल अंतरभूत u32 advk_पढ़ोl(काष्ठा advk_pcie *pcie, u64 reg)
अणु
	वापस पढ़ोl(pcie->base + reg);
पूर्ण

अटल अंतरभूत u16 advk_पढ़ो16(काष्ठा advk_pcie *pcie, u64 reg)
अणु
	वापस advk_पढ़ोl(pcie, (reg & ~0x3)) >> ((reg & 0x3) * 8);
पूर्ण

अटल पूर्णांक advk_pcie_link_up(काष्ठा advk_pcie *pcie)
अणु
	u32 val, ltssm_state;

	val = advk_पढ़ोl(pcie, CFG_REG);
	ltssm_state = (val >> LTSSM_SHIFT) & LTSSM_MASK;
	वापस ltssm_state >= LTSSM_L0;
पूर्ण

अटल पूर्णांक advk_pcie_रुको_क्रम_link(काष्ठा advk_pcie *pcie)
अणु
	पूर्णांक retries;

	/* check अगर the link is up or not */
	क्रम (retries = 0; retries < LINK_WAIT_MAX_RETRIES; retries++) अणु
		अगर (advk_pcie_link_up(pcie))
			वापस 0;

		usleep_range(LINK_WAIT_USLEEP_MIN, LINK_WAIT_USLEEP_MAX);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम advk_pcie_रुको_क्रम_retrain(काष्ठा advk_pcie *pcie)
अणु
	माप_प्रकार retries;

	क्रम (retries = 0; retries < RETRAIN_WAIT_MAX_RETRIES; ++retries) अणु
		अगर (!advk_pcie_link_up(pcie))
			अवरोध;
		udelay(RETRAIN_WAIT_USLEEP_US);
	पूर्ण
पूर्ण

अटल व्योम advk_pcie_issue_perst(काष्ठा advk_pcie *pcie)
अणु
	u32 reg;

	अगर (!pcie->reset_gpio)
		वापस;

	/*
	 * As required by PCI Express spec (PCI Express Base Specअगरication, REV.
	 * 4.0 PCI Express, February 19 2014, 6.6.1 Conventional Reset) a delay
	 * क्रम at least 100ms after de-निश्चितing PERST# संकेत is needed beक्रमe
	 * link training is enabled. So ensure that link training is disabled
	 * prior de-निश्चितing PERST# संकेत to fulfill that PCI Express spec
	 * requirement.
	 */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL0_REG);
	reg &= ~LINK_TRAINING_EN;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL0_REG);

	/* 10ms delay is needed क्रम some cards */
	dev_info(&pcie->pdev->dev, "issuing PERST via reset GPIO for 10ms\n");
	gpiod_set_value_cansleep(pcie->reset_gpio, 1);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(pcie->reset_gpio, 0);
पूर्ण

अटल पूर्णांक advk_pcie_train_at_gen(काष्ठा advk_pcie *pcie, पूर्णांक gen)
अणु
	पूर्णांक ret, neg_gen;
	u32 reg;

	/* Setup link speed */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL0_REG);
	reg &= ~PCIE_GEN_SEL_MSK;
	अगर (gen == 3)
		reg |= SPEED_GEN_3;
	अन्यथा अगर (gen == 2)
		reg |= SPEED_GEN_2;
	अन्यथा
		reg |= SPEED_GEN_1;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL0_REG);

	/*
	 * Enable link training. This is not needed in every call to this
	 * function, just once suffices, but it करोes not अवरोध anything either.
	 */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL0_REG);
	reg |= LINK_TRAINING_EN;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL0_REG);

	/*
	 * Start link training immediately after enabling it.
	 * This solves problems क्रम some buggy cards.
	 */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_PCIEXP_CAP + PCI_EXP_LNKCTL);
	reg |= PCI_EXP_LNKCTL_RL;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_PCIEXP_CAP + PCI_EXP_LNKCTL);

	ret = advk_pcie_रुको_क्रम_link(pcie);
	अगर (ret)
		वापस ret;

	reg = advk_पढ़ो16(pcie, PCIE_CORE_PCIEXP_CAP + PCI_EXP_LNKSTA);
	neg_gen = reg & PCI_EXP_LNKSTA_CLS;

	वापस neg_gen;
पूर्ण

अटल व्योम advk_pcie_train_link(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	पूर्णांक neg_gen = -1, gen;

	/*
	 * Reset PCIe card via PERST# संकेत. Some cards are not detected
	 * during link training when they are in some non-initial state.
	 */
	advk_pcie_issue_perst(pcie);

	/*
	 * PERST# संकेत could have been निश्चितed by pinctrl subप्रणाली beक्रमe
	 * probe() callback has been called or issued explicitly by reset gpio
	 * function advk_pcie_issue_perst(), making the endpoपूर्णांक going पूर्णांकo
	 * fundamental reset. As required by PCI Express spec a delay क्रम at
	 * least 100ms after such a reset beक्रमe link training is needed.
	 */
	msleep(PCI_PM_D3COLD_WAIT);

	/*
	 * Try link training at link gen specअगरied by device tree property
	 * 'max-link-speed'. If this fails, iteratively train at lower gen.
	 */
	क्रम (gen = pcie->link_gen; gen > 0; --gen) अणु
		neg_gen = advk_pcie_train_at_gen(pcie, gen);
		अगर (neg_gen > 0)
			अवरोध;
	पूर्ण

	अगर (neg_gen < 0)
		जाओ err;

	/*
	 * After successful training अगर negotiated gen is lower than requested,
	 * train again on negotiated gen. This solves some stability issues क्रम
	 * some buggy gen1 cards.
	 */
	अगर (neg_gen < gen) अणु
		gen = neg_gen;
		neg_gen = advk_pcie_train_at_gen(pcie, gen);
	पूर्ण

	अगर (neg_gen == gen) अणु
		dev_info(dev, "link up at gen %i\n", gen);
		वापस;
	पूर्ण

err:
	dev_err(dev, "link never came up\n");
पूर्ण

अटल व्योम advk_pcie_setup_hw(काष्ठा advk_pcie *pcie)
अणु
	u32 reg;

	/* Enable TX */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_REF_CLK_REG);
	reg |= PCIE_CORE_REF_CLK_TX_ENABLE;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_REF_CLK_REG);

	/* Set to Direct mode */
	reg = advk_पढ़ोl(pcie, CTRL_CONFIG_REG);
	reg &= ~(CTRL_MODE_MASK << CTRL_MODE_SHIFT);
	reg |= ((PCIE_CORE_MODE_सूचीECT & CTRL_MODE_MASK) << CTRL_MODE_SHIFT);
	advk_ग_लिखोl(pcie, reg, CTRL_CONFIG_REG);

	/* Set PCI global control रेजिस्टर to RC mode */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL0_REG);
	reg |= (IS_RC_MSK << IS_RC_SHIFT);
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL0_REG);

	/* Set Advanced Error Capabilities and Control PF0 रेजिस्टर */
	reg = PCIE_CORE_ERR_CAPCTL_ECRC_CHK_TX |
		PCIE_CORE_ERR_CAPCTL_ECRC_CHK_TX_EN |
		PCIE_CORE_ERR_CAPCTL_ECRC_CHCK |
		PCIE_CORE_ERR_CAPCTL_ECRC_CHCK_RCV;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_ERR_CAPCTL_REG);

	/* Set PCIe Device Control रेजिस्टर */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_PCIEXP_CAP + PCI_EXP_DEVCTL);
	reg &= ~PCI_EXP_DEVCTL_RELAX_EN;
	reg &= ~PCI_EXP_DEVCTL_NOSNOOP_EN;
	reg &= ~PCI_EXP_DEVCTL_READRQ;
	reg |= PCI_EXP_DEVCTL_PAYLOAD; /* Set max payload size */
	reg |= PCI_EXP_DEVCTL_READRQ_512B;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_PCIEXP_CAP + PCI_EXP_DEVCTL);

	/* Program PCIe Control 2 to disable strict ordering */
	reg = PCIE_CORE_CTRL2_RESERVED |
		PCIE_CORE_CTRL2_TD_ENABLE;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL2_REG);

	/* Set lane X1 */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL0_REG);
	reg &= ~LANE_CNT_MSK;
	reg |= LANE_COUNT_1;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL0_REG);

	/* Enable MSI */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL2_REG);
	reg |= PCIE_CORE_CTRL2_MSI_ENABLE;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL2_REG);

	/* Clear all पूर्णांकerrupts */
	advk_ग_लिखोl(pcie, PCIE_ISR0_ALL_MASK, PCIE_ISR0_REG);
	advk_ग_लिखोl(pcie, PCIE_ISR1_ALL_MASK, PCIE_ISR1_REG);
	advk_ग_लिखोl(pcie, PCIE_IRQ_ALL_MASK, HOST_CTRL_INT_STATUS_REG);

	/* Disable All ISR0/1 Sources */
	reg = PCIE_ISR0_ALL_MASK;
	reg &= ~PCIE_ISR0_MSI_INT_PENDING;
	advk_ग_लिखोl(pcie, reg, PCIE_ISR0_MASK_REG);

	advk_ग_लिखोl(pcie, PCIE_ISR1_ALL_MASK, PCIE_ISR1_MASK_REG);

	/* Unmask all MSIs */
	advk_ग_लिखोl(pcie, 0, PCIE_MSI_MASK_REG);

	/* Enable summary पूर्णांकerrupt क्रम GIC SPI source */
	reg = PCIE_IRQ_ALL_MASK & (~PCIE_IRQ_ENABLE_INTS_MASK);
	advk_ग_लिखोl(pcie, reg, HOST_CTRL_INT_MASK_REG);

	reg = advk_पढ़ोl(pcie, PCIE_CORE_CTRL2_REG);
	reg |= PCIE_CORE_CTRL2_OB_WIN_ENABLE;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CTRL2_REG);

	/* Bypass the address winकरोw mapping क्रम PIO */
	reg = advk_पढ़ोl(pcie, PIO_CTRL);
	reg |= PIO_CTRL_ADDR_WIN_DISABLE;
	advk_ग_लिखोl(pcie, reg, PIO_CTRL);

	advk_pcie_train_link(pcie);

	/*
	 * FIXME: The following रेजिस्टर update is suspicious. This रेजिस्टर is
	 * applicable only when the PCI controller is configured क्रम Endpoपूर्णांक
	 * mode, not as a Root Complex. But apparently when this code is
	 * हटाओd, some cards stop working. This should be investigated and
	 * a comment explaining this should be put here.
	 */
	reg = advk_पढ़ोl(pcie, PCIE_CORE_CMD_STATUS_REG);
	reg |= PCIE_CORE_CMD_MEM_ACCESS_EN |
		PCIE_CORE_CMD_IO_ACCESS_EN |
		PCIE_CORE_CMD_MEM_IO_REQ_EN;
	advk_ग_लिखोl(pcie, reg, PCIE_CORE_CMD_STATUS_REG);
पूर्ण

अटल व्योम advk_pcie_check_pio_status(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	u32 reg;
	अचिन्हित पूर्णांक status;
	अक्षर *strcomp_status, *str_posted;

	reg = advk_पढ़ोl(pcie, PIO_STAT);
	status = (reg & PIO_COMPLETION_STATUS_MASK) >>
		PIO_COMPLETION_STATUS_SHIFT;

	अगर (!status)
		वापस;

	चयन (status) अणु
	हाल PIO_COMPLETION_STATUS_UR:
		strcomp_status = "UR";
		अवरोध;
	हाल PIO_COMPLETION_STATUS_CRS:
		strcomp_status = "CRS";
		अवरोध;
	हाल PIO_COMPLETION_STATUS_CA:
		strcomp_status = "CA";
		अवरोध;
	शेष:
		strcomp_status = "Unknown";
		अवरोध;
	पूर्ण

	अगर (reg & PIO_NON_POSTED_REQ)
		str_posted = "Non-posted";
	अन्यथा
		str_posted = "Posted";

	dev_err(dev, "%s PIO Response Status: %s, %#x @ %#x\n",
		str_posted, strcomp_status, reg, advk_पढ़ोl(pcie, PIO_ADDR_LS));
पूर्ण

अटल पूर्णांक advk_pcie_रुको_pio(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	पूर्णांक i;

	क्रम (i = 0; i < PIO_RETRY_CNT; i++) अणु
		u32 start, isr;

		start = advk_पढ़ोl(pcie, PIO_START);
		isr = advk_पढ़ोl(pcie, PIO_ISR);
		अगर (!start && isr)
			वापस 0;
		udelay(PIO_RETRY_DELAY);
	पूर्ण

	dev_err(dev, "PIO read/write transfer time out\n");
	वापस -ETIMEDOUT;
पूर्ण


अटल pci_bridge_emul_पढ़ो_status_t
advk_pci_bridge_emul_pcie_conf_पढ़ो(काष्ठा pci_bridge_emul *bridge,
				    पूर्णांक reg, u32 *value)
अणु
	काष्ठा advk_pcie *pcie = bridge->data;


	चयन (reg) अणु
	हाल PCI_EXP_SLTCTL:
		*value = PCI_EXP_SLTSTA_PDS << 16;
		वापस PCI_BRIDGE_EMUL_HANDLED;

	हाल PCI_EXP_RTCTL: अणु
		u32 val = advk_पढ़ोl(pcie, PCIE_ISR0_MASK_REG);
		*value = (val & PCIE_MSG_PM_PME_MASK) ? 0 : PCI_EXP_RTCTL_PMEIE;
		वापस PCI_BRIDGE_EMUL_HANDLED;
	पूर्ण

	हाल PCI_EXP_RTSTA: अणु
		u32 isr0 = advk_पढ़ोl(pcie, PCIE_ISR0_REG);
		u32 msglog = advk_पढ़ोl(pcie, PCIE_MSG_LOG_REG);
		*value = (isr0 & PCIE_MSG_PM_PME_MASK) << 16 | (msglog >> 16);
		वापस PCI_BRIDGE_EMUL_HANDLED;
	पूर्ण

	हाल PCI_EXP_LNKCTL: अणु
		/* u32 contains both PCI_EXP_LNKCTL and PCI_EXP_LNKSTA */
		u32 val = advk_पढ़ोl(pcie, PCIE_CORE_PCIEXP_CAP + reg) &
			~(PCI_EXP_LNKSTA_LT << 16);
		अगर (!advk_pcie_link_up(pcie))
			val |= (PCI_EXP_LNKSTA_LT << 16);
		*value = val;
		वापस PCI_BRIDGE_EMUL_HANDLED;
	पूर्ण

	हाल PCI_CAP_LIST_ID:
	हाल PCI_EXP_DEVCAP:
	हाल PCI_EXP_DEVCTL:
	हाल PCI_EXP_LNKCAP:
		*value = advk_पढ़ोl(pcie, PCIE_CORE_PCIEXP_CAP + reg);
		वापस PCI_BRIDGE_EMUL_HANDLED;
	शेष:
		वापस PCI_BRIDGE_EMUL_NOT_HANDLED;
	पूर्ण

पूर्ण

अटल व्योम
advk_pci_bridge_emul_pcie_conf_ग_लिखो(काष्ठा pci_bridge_emul *bridge,
				     पूर्णांक reg, u32 old, u32 new, u32 mask)
अणु
	काष्ठा advk_pcie *pcie = bridge->data;

	चयन (reg) अणु
	हाल PCI_EXP_DEVCTL:
		advk_ग_लिखोl(pcie, new, PCIE_CORE_PCIEXP_CAP + reg);
		अवरोध;

	हाल PCI_EXP_LNKCTL:
		advk_ग_लिखोl(pcie, new, PCIE_CORE_PCIEXP_CAP + reg);
		अगर (new & PCI_EXP_LNKCTL_RL)
			advk_pcie_रुको_क्रम_retrain(pcie);
		अवरोध;

	हाल PCI_EXP_RTCTL: अणु
		/* Only mask/unmask PME पूर्णांकerrupt */
		u32 val = advk_पढ़ोl(pcie, PCIE_ISR0_MASK_REG) &
			~PCIE_MSG_PM_PME_MASK;
		अगर ((new & PCI_EXP_RTCTL_PMEIE) == 0)
			val |= PCIE_MSG_PM_PME_MASK;
		advk_ग_लिखोl(pcie, val, PCIE_ISR0_MASK_REG);
		अवरोध;
	पूर्ण

	हाल PCI_EXP_RTSTA:
		new = (new & PCI_EXP_RTSTA_PME) >> 9;
		advk_ग_लिखोl(pcie, new, PCIE_ISR0_REG);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा pci_bridge_emul_ops advk_pci_bridge_emul_ops = अणु
	.पढ़ो_pcie = advk_pci_bridge_emul_pcie_conf_पढ़ो,
	.ग_लिखो_pcie = advk_pci_bridge_emul_pcie_conf_ग_लिखो,
पूर्ण;

/*
 * Initialize the configuration space of the PCI-to-PCI bridge
 * associated with the given PCIe पूर्णांकerface.
 */
अटल पूर्णांक advk_sw_pci_bridge_init(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा pci_bridge_emul *bridge = &pcie->bridge;

	bridge->conf.venकरोr =
		cpu_to_le16(advk_पढ़ोl(pcie, PCIE_CORE_DEV_ID_REG) & 0xffff);
	bridge->conf.device =
		cpu_to_le16(advk_पढ़ोl(pcie, PCIE_CORE_DEV_ID_REG) >> 16);
	bridge->conf.class_revision =
		cpu_to_le32(advk_पढ़ोl(pcie, PCIE_CORE_DEV_REV_REG) & 0xff);

	/* Support 32 bits I/O addressing */
	bridge->conf.iobase = PCI_IO_RANGE_TYPE_32;
	bridge->conf.iolimit = PCI_IO_RANGE_TYPE_32;

	/* Support 64 bits memory pref */
	bridge->conf.pref_mem_base = cpu_to_le16(PCI_PREF_RANGE_TYPE_64);
	bridge->conf.pref_mem_limit = cpu_to_le16(PCI_PREF_RANGE_TYPE_64);

	/* Support पूर्णांकerrupt A क्रम MSI feature */
	bridge->conf.पूर्णांकpin = PCIE_CORE_INT_A_ASSERT_ENABLE;

	bridge->has_pcie = true;
	bridge->data = pcie;
	bridge->ops = &advk_pci_bridge_emul_ops;

	वापस pci_bridge_emul_init(bridge, 0);
पूर्ण

अटल bool advk_pcie_valid_device(काष्ठा advk_pcie *pcie, काष्ठा pci_bus *bus,
				  पूर्णांक devfn)
अणु
	अगर (pci_is_root_bus(bus) && PCI_SLOT(devfn) != 0)
		वापस false;

	/*
	 * If the link goes करोwn after we check क्रम link-up, nothing bad
	 * happens but the config access बार out.
	 */
	अगर (!pci_is_root_bus(bus) && !advk_pcie_link_up(pcie))
		वापस false;

	वापस true;
पूर्ण

अटल bool advk_pcie_pio_is_running(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;

	/*
	 * Trying to start a new PIO transfer when previous has not completed
	 * cause External Abort on CPU which results in kernel panic:
	 *
	 *     SError Interrupt on CPU0, code 0xbf000002 -- SError
	 *     Kernel panic - not syncing: Asynchronous SError Interrupt
	 *
	 * Functions advk_pcie_rd_conf() and advk_pcie_wr_conf() are रक्षित
	 * by raw_spin_lock_irqsave() at pci_lock_config() level to prevent
	 * concurrent calls at the same समय. But because PIO transfer may take
	 * about 1.5s when link is करोwn or card is disconnected, it means that
	 * advk_pcie_रुको_pio() करोes not always have to रुको क्रम completion.
	 *
	 * Some versions of ARM Trusted Firmware handles this External Abort at
	 * EL3 level and mask it to prevent kernel panic. Relevant TF-A commit:
	 * https://git.trustedfirmware.org/TF-A/trusted-firmware-a.git/commit/?id=3c7dcdac5c50
	 */
	अगर (advk_पढ़ोl(pcie, PIO_START)) अणु
		dev_err(dev, "Previous PIO read/write transfer is still running\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक advk_pcie_rd_conf(काष्ठा pci_bus *bus, u32 devfn,
			     पूर्णांक where, पूर्णांक size, u32 *val)
अणु
	काष्ठा advk_pcie *pcie = bus->sysdata;
	u32 reg;
	पूर्णांक ret;

	अगर (!advk_pcie_valid_device(pcie, bus, devfn)) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_DEVICE_NOT_FOUND;
	पूर्ण

	अगर (pci_is_root_bus(bus))
		वापस pci_bridge_emul_conf_पढ़ो(&pcie->bridge, where,
						 size, val);

	अगर (advk_pcie_pio_is_running(pcie)) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_SET_FAILED;
	पूर्ण

	/* Program the control रेजिस्टर */
	reg = advk_पढ़ोl(pcie, PIO_CTRL);
	reg &= ~PIO_CTRL_TYPE_MASK;
	अगर (pci_is_root_bus(bus->parent))
		reg |= PCIE_CONFIG_RD_TYPE0;
	अन्यथा
		reg |= PCIE_CONFIG_RD_TYPE1;
	advk_ग_लिखोl(pcie, reg, PIO_CTRL);

	/* Program the address रेजिस्टरs */
	reg = ALIGN_DOWN(PCIE_ECAM_OFFSET(bus->number, devfn, where), 4);
	advk_ग_लिखोl(pcie, reg, PIO_ADDR_LS);
	advk_ग_लिखोl(pcie, 0, PIO_ADDR_MS);

	/* Program the data strobe */
	advk_ग_लिखोl(pcie, 0xf, PIO_WR_DATA_STRB);

	/* Clear PIO DONE ISR and start the transfer */
	advk_ग_लिखोl(pcie, 1, PIO_ISR);
	advk_ग_लिखोl(pcie, 1, PIO_START);

	ret = advk_pcie_रुको_pio(pcie);
	अगर (ret < 0) अणु
		*val = 0xffffffff;
		वापस PCIBIOS_SET_FAILED;
	पूर्ण

	advk_pcie_check_pio_status(pcie);

	/* Get the पढ़ो result */
	*val = advk_पढ़ोl(pcie, PIO_RD_DATA);
	अगर (size == 1)
		*val = (*val >> (8 * (where & 3))) & 0xff;
	अन्यथा अगर (size == 2)
		*val = (*val >> (8 * (where & 3))) & 0xffff;

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल पूर्णांक advk_pcie_wr_conf(काष्ठा pci_bus *bus, u32 devfn,
				पूर्णांक where, पूर्णांक size, u32 val)
अणु
	काष्ठा advk_pcie *pcie = bus->sysdata;
	u32 reg;
	u32 data_strobe = 0x0;
	पूर्णांक offset;
	पूर्णांक ret;

	अगर (!advk_pcie_valid_device(pcie, bus, devfn))
		वापस PCIBIOS_DEVICE_NOT_FOUND;

	अगर (pci_is_root_bus(bus))
		वापस pci_bridge_emul_conf_ग_लिखो(&pcie->bridge, where,
						  size, val);

	अगर (where % size)
		वापस PCIBIOS_SET_FAILED;

	अगर (advk_pcie_pio_is_running(pcie))
		वापस PCIBIOS_SET_FAILED;

	/* Program the control रेजिस्टर */
	reg = advk_पढ़ोl(pcie, PIO_CTRL);
	reg &= ~PIO_CTRL_TYPE_MASK;
	अगर (pci_is_root_bus(bus->parent))
		reg |= PCIE_CONFIG_WR_TYPE0;
	अन्यथा
		reg |= PCIE_CONFIG_WR_TYPE1;
	advk_ग_लिखोl(pcie, reg, PIO_CTRL);

	/* Program the address रेजिस्टरs */
	reg = ALIGN_DOWN(PCIE_ECAM_OFFSET(bus->number, devfn, where), 4);
	advk_ग_लिखोl(pcie, reg, PIO_ADDR_LS);
	advk_ग_लिखोl(pcie, 0, PIO_ADDR_MS);

	/* Calculate the ग_लिखो strobe */
	offset      = where & 0x3;
	reg         = val << (8 * offset);
	data_strobe = GENMASK(size - 1, 0) << offset;

	/* Program the data रेजिस्टर */
	advk_ग_लिखोl(pcie, reg, PIO_WR_DATA);

	/* Program the data strobe */
	advk_ग_लिखोl(pcie, data_strobe, PIO_WR_DATA_STRB);

	/* Clear PIO DONE ISR and start the transfer */
	advk_ग_लिखोl(pcie, 1, PIO_ISR);
	advk_ग_लिखोl(pcie, 1, PIO_START);

	ret = advk_pcie_रुको_pio(pcie);
	अगर (ret < 0)
		वापस PCIBIOS_SET_FAILED;

	advk_pcie_check_pio_status(pcie);

	वापस PCIBIOS_SUCCESSFUL;
पूर्ण

अटल काष्ठा pci_ops advk_pcie_ops = अणु
	.पढ़ो = advk_pcie_rd_conf,
	.ग_लिखो = advk_pcie_wr_conf,
पूर्ण;

अटल व्योम advk_msi_irq_compose_msi_msg(काष्ठा irq_data *data,
					 काष्ठा msi_msg *msg)
अणु
	काष्ठा advk_pcie *pcie = irq_data_get_irq_chip_data(data);
	phys_addr_t msi_msg = virt_to_phys(&pcie->msi_msg);

	msg->address_lo = lower_32_bits(msi_msg);
	msg->address_hi = upper_32_bits(msi_msg);
	msg->data = data->irq;
पूर्ण

अटल पूर्णांक advk_msi_set_affinity(काष्ठा irq_data *irq_data,
				 स्थिर काष्ठा cpumask *mask, bool क्रमce)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक advk_msi_irq_करोमुख्य_alloc(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq,
				     अचिन्हित पूर्णांक nr_irqs, व्योम *args)
अणु
	काष्ठा advk_pcie *pcie = करोमुख्य->host_data;
	पूर्णांक hwirq, i;

	mutex_lock(&pcie->msi_used_lock);
	hwirq = biपंचांगap_find_next_zero_area(pcie->msi_used, MSI_IRQ_NUM,
					   0, nr_irqs, 0);
	अगर (hwirq >= MSI_IRQ_NUM) अणु
		mutex_unlock(&pcie->msi_used_lock);
		वापस -ENOSPC;
	पूर्ण

	biपंचांगap_set(pcie->msi_used, hwirq, nr_irqs);
	mutex_unlock(&pcie->msi_used_lock);

	क्रम (i = 0; i < nr_irqs; i++)
		irq_करोमुख्य_set_info(करोमुख्य, virq + i, hwirq + i,
				    &pcie->msi_bottom_irq_chip,
				    करोमुख्य->host_data, handle_simple_irq,
				    शून्य, शून्य);

	वापस hwirq;
पूर्ण

अटल व्योम advk_msi_irq_करोमुख्य_मुक्त(काष्ठा irq_करोमुख्य *करोमुख्य,
				     अचिन्हित पूर्णांक virq, अचिन्हित पूर्णांक nr_irqs)
अणु
	काष्ठा irq_data *d = irq_करोमुख्य_get_irq_data(करोमुख्य, virq);
	काष्ठा advk_pcie *pcie = करोमुख्य->host_data;

	mutex_lock(&pcie->msi_used_lock);
	biपंचांगap_clear(pcie->msi_used, d->hwirq, nr_irqs);
	mutex_unlock(&pcie->msi_used_lock);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops advk_msi_करोमुख्य_ops = अणु
	.alloc = advk_msi_irq_करोमुख्य_alloc,
	.मुक्त = advk_msi_irq_करोमुख्य_मुक्त,
पूर्ण;

अटल व्योम advk_pcie_irq_mask(काष्ठा irq_data *d)
अणु
	काष्ठा advk_pcie *pcie = d->करोमुख्य->host_data;
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	u32 mask;

	mask = advk_पढ़ोl(pcie, PCIE_ISR1_MASK_REG);
	mask |= PCIE_ISR1_INTX_ASSERT(hwirq);
	advk_ग_लिखोl(pcie, mask, PCIE_ISR1_MASK_REG);
पूर्ण

अटल व्योम advk_pcie_irq_unmask(काष्ठा irq_data *d)
अणु
	काष्ठा advk_pcie *pcie = d->करोमुख्य->host_data;
	irq_hw_number_t hwirq = irqd_to_hwirq(d);
	u32 mask;

	mask = advk_पढ़ोl(pcie, PCIE_ISR1_MASK_REG);
	mask &= ~PCIE_ISR1_INTX_ASSERT(hwirq);
	advk_ग_लिखोl(pcie, mask, PCIE_ISR1_MASK_REG);
पूर्ण

अटल पूर्णांक advk_pcie_irq_map(काष्ठा irq_करोमुख्य *h,
			     अचिन्हित पूर्णांक virq, irq_hw_number_t hwirq)
अणु
	काष्ठा advk_pcie *pcie = h->host_data;

	advk_pcie_irq_mask(irq_get_irq_data(virq));
	irq_set_status_flags(virq, IRQ_LEVEL);
	irq_set_chip_and_handler(virq, &pcie->irq_chip,
				 handle_level_irq);
	irq_set_chip_data(virq, pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops advk_pcie_irq_करोमुख्य_ops = अणु
	.map = advk_pcie_irq_map,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक advk_pcie_init_msi_irq_करोमुख्य(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा irq_chip *bottom_ic, *msi_ic;
	काष्ठा msi_करोमुख्य_info *msi_di;
	phys_addr_t msi_msg_phys;

	mutex_init(&pcie->msi_used_lock);

	bottom_ic = &pcie->msi_bottom_irq_chip;

	bottom_ic->name = "MSI";
	bottom_ic->irq_compose_msi_msg = advk_msi_irq_compose_msi_msg;
	bottom_ic->irq_set_affinity = advk_msi_set_affinity;

	msi_ic = &pcie->msi_irq_chip;
	msi_ic->name = "advk-MSI";

	msi_di = &pcie->msi_करोमुख्य_info;
	msi_di->flags = MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		MSI_FLAG_MULTI_PCI_MSI;
	msi_di->chip = msi_ic;

	msi_msg_phys = virt_to_phys(&pcie->msi_msg);

	advk_ग_लिखोl(pcie, lower_32_bits(msi_msg_phys),
		    PCIE_MSI_ADDR_LOW_REG);
	advk_ग_लिखोl(pcie, upper_32_bits(msi_msg_phys),
		    PCIE_MSI_ADDR_HIGH_REG);

	pcie->msi_inner_करोमुख्य =
		irq_करोमुख्य_add_linear(शून्य, MSI_IRQ_NUM,
				      &advk_msi_करोमुख्य_ops, pcie);
	अगर (!pcie->msi_inner_करोमुख्य)
		वापस -ENOMEM;

	pcie->msi_करोमुख्य =
		pci_msi_create_irq_करोमुख्य(of_node_to_fwnode(node),
					  msi_di, pcie->msi_inner_करोमुख्य);
	अगर (!pcie->msi_करोमुख्य) अणु
		irq_करोमुख्य_हटाओ(pcie->msi_inner_करोमुख्य);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम advk_pcie_हटाओ_msi_irq_करोमुख्य(काष्ठा advk_pcie *pcie)
अणु
	irq_करोमुख्य_हटाओ(pcie->msi_करोमुख्य);
	irq_करोमुख्य_हटाओ(pcie->msi_inner_करोमुख्य);
पूर्ण

अटल पूर्णांक advk_pcie_init_irq_करोमुख्य(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा device_node *pcie_पूर्णांकc_node;
	काष्ठा irq_chip *irq_chip;
	पूर्णांक ret = 0;

	pcie_पूर्णांकc_node =  of_get_next_child(node, शून्य);
	अगर (!pcie_पूर्णांकc_node) अणु
		dev_err(dev, "No PCIe Intc node found\n");
		वापस -ENODEV;
	पूर्ण

	irq_chip = &pcie->irq_chip;

	irq_chip->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "%s-irq",
					dev_name(dev));
	अगर (!irq_chip->name) अणु
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	irq_chip->irq_mask = advk_pcie_irq_mask;
	irq_chip->irq_mask_ack = advk_pcie_irq_mask;
	irq_chip->irq_unmask = advk_pcie_irq_unmask;

	pcie->irq_करोमुख्य =
		irq_करोमुख्य_add_linear(pcie_पूर्णांकc_node, PCI_NUM_INTX,
				      &advk_pcie_irq_करोमुख्य_ops, pcie);
	अगर (!pcie->irq_करोमुख्य) अणु
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

out_put_node:
	of_node_put(pcie_पूर्णांकc_node);
	वापस ret;
पूर्ण

अटल व्योम advk_pcie_हटाओ_irq_करोमुख्य(काष्ठा advk_pcie *pcie)
अणु
	irq_करोमुख्य_हटाओ(pcie->irq_करोमुख्य);
पूर्ण

अटल व्योम advk_pcie_handle_msi(काष्ठा advk_pcie *pcie)
अणु
	u32 msi_val, msi_mask, msi_status, msi_idx;
	u16 msi_data;

	msi_mask = advk_पढ़ोl(pcie, PCIE_MSI_MASK_REG);
	msi_val = advk_पढ़ोl(pcie, PCIE_MSI_STATUS_REG);
	msi_status = msi_val & ~msi_mask;

	क्रम (msi_idx = 0; msi_idx < MSI_IRQ_NUM; msi_idx++) अणु
		अगर (!(BIT(msi_idx) & msi_status))
			जारी;

		advk_ग_लिखोl(pcie, BIT(msi_idx), PCIE_MSI_STATUS_REG);
		msi_data = advk_पढ़ोl(pcie, PCIE_MSI_PAYLOAD_REG) & 0xFF;
		generic_handle_irq(msi_data);
	पूर्ण

	advk_ग_लिखोl(pcie, PCIE_ISR0_MSI_INT_PENDING,
		    PCIE_ISR0_REG);
पूर्ण

अटल व्योम advk_pcie_handle_पूर्णांक(काष्ठा advk_pcie *pcie)
अणु
	u32 isr0_val, isr0_mask, isr0_status;
	u32 isr1_val, isr1_mask, isr1_status;
	पूर्णांक i, virq;

	isr0_val = advk_पढ़ोl(pcie, PCIE_ISR0_REG);
	isr0_mask = advk_पढ़ोl(pcie, PCIE_ISR0_MASK_REG);
	isr0_status = isr0_val & ((~isr0_mask) & PCIE_ISR0_ALL_MASK);

	isr1_val = advk_पढ़ोl(pcie, PCIE_ISR1_REG);
	isr1_mask = advk_पढ़ोl(pcie, PCIE_ISR1_MASK_REG);
	isr1_status = isr1_val & ((~isr1_mask) & PCIE_ISR1_ALL_MASK);

	अगर (!isr0_status && !isr1_status) अणु
		advk_ग_लिखोl(pcie, isr0_val, PCIE_ISR0_REG);
		advk_ग_लिखोl(pcie, isr1_val, PCIE_ISR1_REG);
		वापस;
	पूर्ण

	/* Process MSI पूर्णांकerrupts */
	अगर (isr0_status & PCIE_ISR0_MSI_INT_PENDING)
		advk_pcie_handle_msi(pcie);

	/* Process legacy पूर्णांकerrupts */
	क्रम (i = 0; i < PCI_NUM_INTX; i++) अणु
		अगर (!(isr1_status & PCIE_ISR1_INTX_ASSERT(i)))
			जारी;

		advk_ग_लिखोl(pcie, PCIE_ISR1_INTX_ASSERT(i),
			    PCIE_ISR1_REG);

		virq = irq_find_mapping(pcie->irq_करोमुख्य, i);
		generic_handle_irq(virq);
	पूर्ण
पूर्ण

अटल irqवापस_t advk_pcie_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा advk_pcie *pcie = arg;
	u32 status;

	status = advk_पढ़ोl(pcie, HOST_CTRL_INT_STATUS_REG);
	अगर (!(status & PCIE_IRQ_CORE_INT))
		वापस IRQ_NONE;

	advk_pcie_handle_पूर्णांक(pcie);

	/* Clear पूर्णांकerrupt */
	advk_ग_लिखोl(pcie, PCIE_IRQ_CORE_INT, HOST_CTRL_INT_STATUS_REG);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __maybe_unused advk_pcie_disable_phy(काष्ठा advk_pcie *pcie)
अणु
	phy_घातer_off(pcie->phy);
	phy_निकास(pcie->phy);
पूर्ण

अटल पूर्णांक advk_pcie_enable_phy(काष्ठा advk_pcie *pcie)
अणु
	पूर्णांक ret;

	अगर (!pcie->phy)
		वापस 0;

	ret = phy_init(pcie->phy);
	अगर (ret)
		वापस ret;

	ret = phy_set_mode(pcie->phy, PHY_MODE_PCIE);
	अगर (ret) अणु
		phy_निकास(pcie->phy);
		वापस ret;
	पूर्ण

	ret = phy_घातer_on(pcie->phy);
	अगर (ret == -EOPNOTSUPP) अणु
		dev_warn(&pcie->pdev->dev, "PHY unsupported by firmware\n");
	पूर्ण अन्यथा अगर (ret) अणु
		phy_निकास(pcie->phy);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक advk_pcie_setup_phy(काष्ठा advk_pcie *pcie)
अणु
	काष्ठा device *dev = &pcie->pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	पूर्णांक ret = 0;

	pcie->phy = devm_of_phy_get(dev, node, शून्य);
	अगर (IS_ERR(pcie->phy) && (PTR_ERR(pcie->phy) == -EPROBE_DEFER))
		वापस PTR_ERR(pcie->phy);

	/* Old bindings miss the PHY handle */
	अगर (IS_ERR(pcie->phy)) अणु
		dev_warn(dev, "PHY unavailable (%ld)\n", PTR_ERR(pcie->phy));
		pcie->phy = शून्य;
		वापस 0;
	पूर्ण

	ret = advk_pcie_enable_phy(pcie);
	अगर (ret)
		dev_err(dev, "Failed to initialize PHY (%d)\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक advk_pcie_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा advk_pcie *pcie;
	काष्ठा pci_host_bridge *bridge;
	पूर्णांक ret, irq;

	bridge = devm_pci_alloc_host_bridge(dev, माप(काष्ठा advk_pcie));
	अगर (!bridge)
		वापस -ENOMEM;

	pcie = pci_host_bridge_priv(bridge);
	pcie->pdev = pdev;
	platक्रमm_set_drvdata(pdev, pcie);

	pcie->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pcie->base))
		वापस PTR_ERR(pcie->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, advk_pcie_irq_handler,
			       IRQF_SHARED | IRQF_NO_THREAD, "advk-pcie",
			       pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to register interrupt\n");
		वापस ret;
	पूर्ण

	pcie->reset_gpio = devm_gpiod_get_from_of_node(dev, dev->of_node,
						       "reset-gpios", 0,
						       GPIOD_OUT_LOW,
						       "pcie1-reset");
	ret = PTR_ERR_OR_ZERO(pcie->reset_gpio);
	अगर (ret) अणु
		अगर (ret == -ENOENT) अणु
			pcie->reset_gpio = शून्य;
		पूर्ण अन्यथा अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get reset-gpio: %i\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = of_pci_get_max_link_speed(dev->of_node);
	अगर (ret <= 0 || ret > 3)
		pcie->link_gen = 3;
	अन्यथा
		pcie->link_gen = ret;

	ret = advk_pcie_setup_phy(pcie);
	अगर (ret)
		वापस ret;

	advk_pcie_setup_hw(pcie);

	ret = advk_sw_pci_bridge_init(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to register emulated root PCI bridge\n");
		वापस ret;
	पूर्ण

	ret = advk_pcie_init_irq_करोमुख्य(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize irq\n");
		वापस ret;
	पूर्ण

	ret = advk_pcie_init_msi_irq_करोमुख्य(pcie);
	अगर (ret) अणु
		dev_err(dev, "Failed to initialize irq\n");
		advk_pcie_हटाओ_irq_करोमुख्य(pcie);
		वापस ret;
	पूर्ण

	bridge->sysdata = pcie;
	bridge->ops = &advk_pcie_ops;

	ret = pci_host_probe(bridge);
	अगर (ret < 0) अणु
		advk_pcie_हटाओ_msi_irq_करोमुख्य(pcie);
		advk_pcie_हटाओ_irq_करोमुख्य(pcie);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक advk_pcie_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा advk_pcie *pcie = platक्रमm_get_drvdata(pdev);
	काष्ठा pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);

	pci_lock_rescan_हटाओ();
	pci_stop_root_bus(bridge->bus);
	pci_हटाओ_root_bus(bridge->bus);
	pci_unlock_rescan_हटाओ();

	advk_pcie_हटाओ_msi_irq_करोमुख्य(pcie);
	advk_pcie_हटाओ_irq_करोमुख्य(pcie);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id advk_pcie_of_match_table[] = अणु
	अणु .compatible = "marvell,armada-3700-pcie", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, advk_pcie_of_match_table);

अटल काष्ठा platक्रमm_driver advk_pcie_driver = अणु
	.driver = अणु
		.name = "advk-pcie",
		.of_match_table = advk_pcie_of_match_table,
	पूर्ण,
	.probe = advk_pcie_probe,
	.हटाओ = advk_pcie_हटाओ,
पूर्ण;
module_platक्रमm_driver(advk_pcie_driver);

MODULE_DESCRIPTION("Aardvark PCIe controller");
MODULE_LICENSE("GPL v2");
