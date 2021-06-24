<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// CAN bus driver क्रम Bosch M_CAN controller
// Copyright (C) 2014 Freescale Semiconductor, Inc.
//      Dong Aisheng <b29396@मुक्तscale.com>
// Copyright (C) 2018-19 Texas Instruments Incorporated - http://www.ti.com/

/* Bosch M_CAN user manual can be obtained from:
 * https://github.com/linux-can/can-करोc/tree/master/m_can
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/pinctrl/consumer.h>

#समावेश "m_can.h"

/* रेजिस्टरs definition */
क्रमागत m_can_reg अणु
	M_CAN_CREL	= 0x0,
	M_CAN_ENDN	= 0x4,
	M_CAN_CUST	= 0x8,
	M_CAN_DBTP	= 0xc,
	M_CAN_TEST	= 0x10,
	M_CAN_RWD	= 0x14,
	M_CAN_CCCR	= 0x18,
	M_CAN_NBTP	= 0x1c,
	M_CAN_TSCC	= 0x20,
	M_CAN_TSCV	= 0x24,
	M_CAN_TOCC	= 0x28,
	M_CAN_TOCV	= 0x2c,
	M_CAN_ECR	= 0x40,
	M_CAN_PSR	= 0x44,
	/* TDCR Register only available क्रम version >=3.1.x */
	M_CAN_TDCR	= 0x48,
	M_CAN_IR	= 0x50,
	M_CAN_IE	= 0x54,
	M_CAN_ILS	= 0x58,
	M_CAN_ILE	= 0x5c,
	M_CAN_GFC	= 0x80,
	M_CAN_SIDFC	= 0x84,
	M_CAN_XIDFC	= 0x88,
	M_CAN_XIDAM	= 0x90,
	M_CAN_HPMS	= 0x94,
	M_CAN_NDAT1	= 0x98,
	M_CAN_NDAT2	= 0x9c,
	M_CAN_RXF0C	= 0xa0,
	M_CAN_RXF0S	= 0xa4,
	M_CAN_RXF0A	= 0xa8,
	M_CAN_RXBC	= 0xac,
	M_CAN_RXF1C	= 0xb0,
	M_CAN_RXF1S	= 0xb4,
	M_CAN_RXF1A	= 0xb8,
	M_CAN_RXESC	= 0xbc,
	M_CAN_TXBC	= 0xc0,
	M_CAN_TXFQS	= 0xc4,
	M_CAN_TXESC	= 0xc8,
	M_CAN_TXBRP	= 0xcc,
	M_CAN_TXBAR	= 0xd0,
	M_CAN_TXBCR	= 0xd4,
	M_CAN_TXBTO	= 0xd8,
	M_CAN_TXBCF	= 0xdc,
	M_CAN_TXBTIE	= 0xe0,
	M_CAN_TXBCIE	= 0xe4,
	M_CAN_TXEFC	= 0xf0,
	M_CAN_TXEFS	= 0xf4,
	M_CAN_TXEFA	= 0xf8,
पूर्ण;

/* napi related */
#घोषणा M_CAN_NAPI_WEIGHT	64

/* message ram configuration data length */
#घोषणा MRAM_CFG_LEN	8

/* Core Release Register (CREL) */
#घोषणा CREL_REL_SHIFT		28
#घोषणा CREL_REL_MASK		(0xF << CREL_REL_SHIFT)
#घोषणा CREL_STEP_SHIFT		24
#घोषणा CREL_STEP_MASK		(0xF << CREL_STEP_SHIFT)
#घोषणा CREL_SUBSTEP_SHIFT	20
#घोषणा CREL_SUBSTEP_MASK	(0xF << CREL_SUBSTEP_SHIFT)

/* Data Bit Timing & Prescaler Register (DBTP) */
#घोषणा DBTP_TDC		BIT(23)
#घोषणा DBTP_DBRP_SHIFT		16
#घोषणा DBTP_DBRP_MASK		(0x1f << DBTP_DBRP_SHIFT)
#घोषणा DBTP_DTSEG1_SHIFT	8
#घोषणा DBTP_DTSEG1_MASK	(0x1f << DBTP_DTSEG1_SHIFT)
#घोषणा DBTP_DTSEG2_SHIFT	4
#घोषणा DBTP_DTSEG2_MASK	(0xf << DBTP_DTSEG2_SHIFT)
#घोषणा DBTP_DSJW_SHIFT		0
#घोषणा DBTP_DSJW_MASK		(0xf << DBTP_DSJW_SHIFT)

/* Transmitter Delay Compensation Register (TDCR) */
#घोषणा TDCR_TDCO_SHIFT		8
#घोषणा TDCR_TDCO_MASK		(0x7F << TDCR_TDCO_SHIFT)
#घोषणा TDCR_TDCF_SHIFT		0
#घोषणा TDCR_TDCF_MASK		(0x7F << TDCR_TDCF_SHIFT)

/* Test Register (TEST) */
#घोषणा TEST_LBCK		BIT(4)

/* CC Control Register(CCCR) */
#घोषणा CCCR_CMR_MASK		0x3
#घोषणा CCCR_CMR_SHIFT		10
#घोषणा CCCR_CMR_CANFD		0x1
#घोषणा CCCR_CMR_CANFD_BRS	0x2
#घोषणा CCCR_CMR_CAN		0x3
#घोषणा CCCR_CME_MASK		0x3
#घोषणा CCCR_CME_SHIFT		8
#घोषणा CCCR_CME_CAN		0
#घोषणा CCCR_CME_CANFD		0x1
#घोषणा CCCR_CME_CANFD_BRS	0x2
#घोषणा CCCR_TXP		BIT(14)
#घोषणा CCCR_TEST		BIT(7)
#घोषणा CCCR_DAR		BIT(6)
#घोषणा CCCR_MON		BIT(5)
#घोषणा CCCR_CSR		BIT(4)
#घोषणा CCCR_CSA		BIT(3)
#घोषणा CCCR_ASM		BIT(2)
#घोषणा CCCR_CCE		BIT(1)
#घोषणा CCCR_INIT		BIT(0)
#घोषणा CCCR_CANFD		0x10
/* क्रम version >=3.1.x */
#घोषणा CCCR_EFBI		BIT(13)
#घोषणा CCCR_PXHD		BIT(12)
#घोषणा CCCR_BRSE		BIT(9)
#घोषणा CCCR_FDOE		BIT(8)
/* only क्रम version >=3.2.x */
#घोषणा CCCR_NISO		BIT(15)

/* Nominal Bit Timing & Prescaler Register (NBTP) */
#घोषणा NBTP_NSJW_SHIFT		25
#घोषणा NBTP_NSJW_MASK		(0x7f << NBTP_NSJW_SHIFT)
#घोषणा NBTP_NBRP_SHIFT		16
#घोषणा NBTP_NBRP_MASK		(0x1ff << NBTP_NBRP_SHIFT)
#घोषणा NBTP_NTSEG1_SHIFT	8
#घोषणा NBTP_NTSEG1_MASK	(0xff << NBTP_NTSEG1_SHIFT)
#घोषणा NBTP_NTSEG2_SHIFT	0
#घोषणा NBTP_NTSEG2_MASK	(0x7f << NBTP_NTSEG2_SHIFT)

/* Timestamp Counter Configuration Register (TSCC) */
#घोषणा TSCC_TCP_MASK		GENMASK(19, 16)
#घोषणा TSCC_TSS_MASK		GENMASK(1, 0)
#घोषणा TSCC_TSS_DISABLE	0x0
#घोषणा TSCC_TSS_INTERNAL	0x1
#घोषणा TSCC_TSS_EXTERNAL	0x2

/* Timestamp Counter Value Register (TSCV) */
#घोषणा TSCV_TSC_MASK		GENMASK(15, 0)

/* Error Counter Register(ECR) */
#घोषणा ECR_RP			BIT(15)
#घोषणा ECR_REC_SHIFT		8
#घोषणा ECR_REC_MASK		(0x7f << ECR_REC_SHIFT)
#घोषणा ECR_TEC_SHIFT		0
#घोषणा ECR_TEC_MASK		0xff

/* Protocol Status Register(PSR) */
#घोषणा PSR_BO		BIT(7)
#घोषणा PSR_EW		BIT(6)
#घोषणा PSR_EP		BIT(5)
#घोषणा PSR_LEC_MASK	0x7

/* Interrupt Register(IR) */
#घोषणा IR_ALL_INT	0xffffffff

/* Renamed bits क्रम versions > 3.1.x */
#घोषणा IR_ARA		BIT(29)
#घोषणा IR_PED		BIT(28)
#घोषणा IR_PEA		BIT(27)

/* Bits क्रम version 3.0.x */
#घोषणा IR_STE		BIT(31)
#घोषणा IR_FOE		BIT(30)
#घोषणा IR_ACKE		BIT(29)
#घोषणा IR_BE		BIT(28)
#घोषणा IR_CRCE		BIT(27)
#घोषणा IR_WDI		BIT(26)
#घोषणा IR_BO		BIT(25)
#घोषणा IR_EW		BIT(24)
#घोषणा IR_EP		BIT(23)
#घोषणा IR_ELO		BIT(22)
#घोषणा IR_BEU		BIT(21)
#घोषणा IR_BEC		BIT(20)
#घोषणा IR_DRX		BIT(19)
#घोषणा IR_TOO		BIT(18)
#घोषणा IR_MRAF		BIT(17)
#घोषणा IR_TSW		BIT(16)
#घोषणा IR_TEFL		BIT(15)
#घोषणा IR_TEFF		BIT(14)
#घोषणा IR_TEFW		BIT(13)
#घोषणा IR_TEFN		BIT(12)
#घोषणा IR_TFE		BIT(11)
#घोषणा IR_TCF		BIT(10)
#घोषणा IR_TC		BIT(9)
#घोषणा IR_HPM		BIT(8)
#घोषणा IR_RF1L		BIT(7)
#घोषणा IR_RF1F		BIT(6)
#घोषणा IR_RF1W		BIT(5)
#घोषणा IR_RF1N		BIT(4)
#घोषणा IR_RF0L		BIT(3)
#घोषणा IR_RF0F		BIT(2)
#घोषणा IR_RF0W		BIT(1)
#घोषणा IR_RF0N		BIT(0)
#घोषणा IR_ERR_STATE	(IR_BO | IR_EW | IR_EP)

/* Interrupts क्रम version 3.0.x */
#घोषणा IR_ERR_LEC_30X	(IR_STE	| IR_FOE | IR_ACKE | IR_BE | IR_CRCE)
#घोषणा IR_ERR_BUS_30X	(IR_ERR_LEC_30X | IR_WDI | IR_ELO | IR_BEU | \
			 IR_BEC | IR_TOO | IR_MRAF | IR_TSW | IR_TEFL | \
			 IR_RF1L | IR_RF0L)
#घोषणा IR_ERR_ALL_30X	(IR_ERR_STATE | IR_ERR_BUS_30X)
/* Interrupts क्रम version >= 3.1.x */
#घोषणा IR_ERR_LEC_31X	(IR_PED | IR_PEA)
#घोषणा IR_ERR_BUS_31X      (IR_ERR_LEC_31X | IR_WDI | IR_ELO | IR_BEU | \
			 IR_BEC | IR_TOO | IR_MRAF | IR_TSW | IR_TEFL | \
			 IR_RF1L | IR_RF0L)
#घोषणा IR_ERR_ALL_31X	(IR_ERR_STATE | IR_ERR_BUS_31X)

/* Interrupt Line Select (ILS) */
#घोषणा ILS_ALL_INT0	0x0
#घोषणा ILS_ALL_INT1	0xFFFFFFFF

/* Interrupt Line Enable (ILE) */
#घोषणा ILE_EINT1	BIT(1)
#घोषणा ILE_EINT0	BIT(0)

/* Rx FIFO 0/1 Configuration (RXF0C/RXF1C) */
#घोषणा RXFC_FWM_SHIFT	24
#घोषणा RXFC_FWM_MASK	(0x7f << RXFC_FWM_SHIFT)
#घोषणा RXFC_FS_SHIFT	16
#घोषणा RXFC_FS_MASK	(0x7f << RXFC_FS_SHIFT)

/* Rx FIFO 0/1 Status (RXF0S/RXF1S) */
#घोषणा RXFS_RFL	BIT(25)
#घोषणा RXFS_FF		BIT(24)
#घोषणा RXFS_FPI_SHIFT	16
#घोषणा RXFS_FPI_MASK	0x3f0000
#घोषणा RXFS_FGI_SHIFT	8
#घोषणा RXFS_FGI_MASK	0x3f00
#घोषणा RXFS_FFL_MASK	0x7f

/* Rx Buffer / FIFO Element Size Configuration (RXESC) */
#घोषणा M_CAN_RXESC_8BYTES	0x0
#घोषणा M_CAN_RXESC_64BYTES	0x777

/* Tx Buffer Configuration(TXBC) */
#घोषणा TXBC_NDTB_SHIFT		16
#घोषणा TXBC_NDTB_MASK		(0x3f << TXBC_NDTB_SHIFT)
#घोषणा TXBC_TFQS_SHIFT		24
#घोषणा TXBC_TFQS_MASK		(0x3f << TXBC_TFQS_SHIFT)

/* Tx FIFO/Queue Status (TXFQS) */
#घोषणा TXFQS_TFQF		BIT(21)
#घोषणा TXFQS_TFQPI_SHIFT	16
#घोषणा TXFQS_TFQPI_MASK	(0x1f << TXFQS_TFQPI_SHIFT)
#घोषणा TXFQS_TFGI_SHIFT	8
#घोषणा TXFQS_TFGI_MASK		(0x1f << TXFQS_TFGI_SHIFT)
#घोषणा TXFQS_TFFL_SHIFT	0
#घोषणा TXFQS_TFFL_MASK		(0x3f << TXFQS_TFFL_SHIFT)

/* Tx Buffer Element Size Configuration(TXESC) */
#घोषणा TXESC_TBDS_8BYTES	0x0
#घोषणा TXESC_TBDS_64BYTES	0x7

/* Tx Event FIFO Configuration (TXEFC) */
#घोषणा TXEFC_EFS_SHIFT		16
#घोषणा TXEFC_EFS_MASK		(0x3f << TXEFC_EFS_SHIFT)

/* Tx Event FIFO Status (TXEFS) */
#घोषणा TXEFS_TEFL		BIT(25)
#घोषणा TXEFS_EFF		BIT(24)
#घोषणा TXEFS_EFGI_SHIFT	8
#घोषणा	TXEFS_EFGI_MASK		(0x1f << TXEFS_EFGI_SHIFT)
#घोषणा TXEFS_EFFL_SHIFT	0
#घोषणा TXEFS_EFFL_MASK		(0x3f << TXEFS_EFFL_SHIFT)

/* Tx Event FIFO Acknowledge (TXEFA) */
#घोषणा TXEFA_EFAI_SHIFT	0
#घोषणा TXEFA_EFAI_MASK		(0x1f << TXEFA_EFAI_SHIFT)

/* Message RAM Configuration (in bytes) */
#घोषणा SIDF_ELEMENT_SIZE	4
#घोषणा XIDF_ELEMENT_SIZE	8
#घोषणा RXF0_ELEMENT_SIZE	72
#घोषणा RXF1_ELEMENT_SIZE	72
#घोषणा RXB_ELEMENT_SIZE	72
#घोषणा TXE_ELEMENT_SIZE	8
#घोषणा TXB_ELEMENT_SIZE	72

/* Message RAM Elements */
#घोषणा M_CAN_FIFO_ID		0x0
#घोषणा M_CAN_FIFO_DLC		0x4
#घोषणा M_CAN_FIFO_DATA(n)	(0x8 + ((n) << 2))

/* Rx Buffer Element */
/* R0 */
#घोषणा RX_BUF_ESI		BIT(31)
#घोषणा RX_BUF_XTD		BIT(30)
#घोषणा RX_BUF_RTR		BIT(29)
/* R1 */
#घोषणा RX_BUF_ANMF		BIT(31)
#घोषणा RX_BUF_FDF		BIT(21)
#घोषणा RX_BUF_BRS		BIT(20)
#घोषणा RX_BUF_RXTS_MASK	GENMASK(15, 0)

/* Tx Buffer Element */
/* T0 */
#घोषणा TX_BUF_ESI		BIT(31)
#घोषणा TX_BUF_XTD		BIT(30)
#घोषणा TX_BUF_RTR		BIT(29)
/* T1 */
#घोषणा TX_BUF_EFC		BIT(23)
#घोषणा TX_BUF_FDF		BIT(21)
#घोषणा TX_BUF_BRS		BIT(20)
#घोषणा TX_BUF_MM_SHIFT		24
#घोषणा TX_BUF_MM_MASK		(0xff << TX_BUF_MM_SHIFT)

/* Tx event FIFO Element */
/* E1 */
#घोषणा TX_EVENT_MM_SHIFT	TX_BUF_MM_SHIFT
#घोषणा TX_EVENT_MM_MASK	(0xff << TX_EVENT_MM_SHIFT)
#घोषणा TX_EVENT_TXTS_MASK	GENMASK(15, 0)

अटल अंतरभूत u32 m_can_पढ़ो(काष्ठा m_can_classdev *cdev, क्रमागत m_can_reg reg)
अणु
	वापस cdev->ops->पढ़ो_reg(cdev, reg);
पूर्ण

अटल अंतरभूत व्योम m_can_ग_लिखो(काष्ठा m_can_classdev *cdev, क्रमागत m_can_reg reg,
			       u32 val)
अणु
	cdev->ops->ग_लिखो_reg(cdev, reg, val);
पूर्ण

अटल u32 m_can_fअगरo_पढ़ो(काष्ठा m_can_classdev *cdev,
			   u32 fgi, अचिन्हित पूर्णांक offset)
अणु
	u32 addr_offset = cdev->mcfg[MRAM_RXF0].off + fgi * RXF0_ELEMENT_SIZE +
		offset;

	वापस cdev->ops->पढ़ो_fअगरo(cdev, addr_offset);
पूर्ण

अटल व्योम m_can_fअगरo_ग_लिखो(काष्ठा m_can_classdev *cdev,
			     u32 fpi, अचिन्हित पूर्णांक offset, u32 val)
अणु
	u32 addr_offset = cdev->mcfg[MRAM_TXB].off + fpi * TXB_ELEMENT_SIZE +
		offset;

	cdev->ops->ग_लिखो_fअगरo(cdev, addr_offset, val);
पूर्ण

अटल अंतरभूत व्योम m_can_fअगरo_ग_लिखो_no_off(काष्ठा m_can_classdev *cdev,
					   u32 fpi, u32 val)
अणु
	cdev->ops->ग_लिखो_fअगरo(cdev, fpi, val);
पूर्ण

अटल u32 m_can_txe_fअगरo_पढ़ो(काष्ठा m_can_classdev *cdev, u32 fgi, u32 offset)
अणु
	u32 addr_offset = cdev->mcfg[MRAM_TXE].off + fgi * TXE_ELEMENT_SIZE +
		offset;

	वापस cdev->ops->पढ़ो_fअगरo(cdev, addr_offset);
पूर्ण

अटल अंतरभूत bool m_can_tx_fअगरo_full(काष्ठा m_can_classdev *cdev)
अणु
	वापस !!(m_can_पढ़ो(cdev, M_CAN_TXFQS) & TXFQS_TFQF);
पूर्ण

अटल व्योम m_can_config_endisable(काष्ठा m_can_classdev *cdev, bool enable)
अणु
	u32 cccr = m_can_पढ़ो(cdev, M_CAN_CCCR);
	u32 समयout = 10;
	u32 val = 0;

	/* Clear the Clock stop request अगर it was set */
	अगर (cccr & CCCR_CSR)
		cccr &= ~CCCR_CSR;

	अगर (enable) अणु
		/* enable m_can configuration */
		m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr | CCCR_INIT);
		udelay(5);
		/* CCCR.CCE can only be set/reset जबतक CCCR.INIT = '1' */
		m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr | CCCR_INIT | CCCR_CCE);
	पूर्ण अन्यथा अणु
		m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr & ~(CCCR_INIT | CCCR_CCE));
	पूर्ण

	/* there's a delay क्रम module initialization */
	अगर (enable)
		val = CCCR_INIT | CCCR_CCE;

	जबतक ((m_can_पढ़ो(cdev, M_CAN_CCCR) & (CCCR_INIT | CCCR_CCE)) != val) अणु
		अगर (समयout == 0) अणु
			netdev_warn(cdev->net, "Failed to init module\n");
			वापस;
		पूर्ण
		समयout--;
		udelay(1);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम m_can_enable_all_पूर्णांकerrupts(काष्ठा m_can_classdev *cdev)
अणु
	/* Only पूर्णांकerrupt line 0 is used in this driver */
	m_can_ग_लिखो(cdev, M_CAN_ILE, ILE_EINT0);
पूर्ण

अटल अंतरभूत व्योम m_can_disable_all_पूर्णांकerrupts(काष्ठा m_can_classdev *cdev)
अणु
	m_can_ग_लिखो(cdev, M_CAN_ILE, 0x0);
पूर्ण

/* Retrieve पूर्णांकernal बारtamp counter from TSCV.TSC, and shअगरt it to 32-bit
 * width.
 */
अटल u32 m_can_get_बारtamp(काष्ठा m_can_classdev *cdev)
अणु
	u32 tscv;
	u32 tsc;

	tscv = m_can_पढ़ो(cdev, M_CAN_TSCV);
	tsc = FIELD_GET(TSCV_TSC_MASK, tscv);

	वापस (tsc << 16);
पूर्ण

अटल व्योम m_can_clean(काष्ठा net_device *net)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(net);

	अगर (cdev->tx_skb) अणु
		पूर्णांक putidx = 0;

		net->stats.tx_errors++;
		अगर (cdev->version > 30)
			putidx = ((m_can_पढ़ो(cdev, M_CAN_TXFQS) &
				   TXFQS_TFQPI_MASK) >> TXFQS_TFQPI_SHIFT);

		can_मुक्त_echo_skb(cdev->net, putidx, शून्य);
		cdev->tx_skb = शून्य;
	पूर्ण
पूर्ण

/* For peripherals, pass skb to rx-offload, which will push skb from
 * napi. For non-peripherals, RX is करोne in napi alपढ़ोy, so push
 * directly. बारtamp is used to ensure good skb ordering in
 * rx-offload and is ignored क्रम non-peripherals.
*/
अटल व्योम m_can_receive_skb(काष्ठा m_can_classdev *cdev,
			      काष्ठा sk_buff *skb,
			      u32 बारtamp)
अणु
	अगर (cdev->is_peripheral) अणु
		काष्ठा net_device_stats *stats = &cdev->net->stats;
		पूर्णांक err;

		err = can_rx_offload_queue_sorted(&cdev->offload, skb,
						  बारtamp);
		अगर (err)
			stats->rx_fअगरo_errors++;
	पूर्ण अन्यथा अणु
		netअगर_receive_skb(skb);
	पूर्ण
पूर्ण

अटल व्योम m_can_पढ़ो_fअगरo(काष्ठा net_device *dev, u32 rxfs)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	u32 id, fgi, dlc;
	u32 बारtamp = 0;
	पूर्णांक i;

	/* calculate the fअगरo get index क्रम where to पढ़ो data */
	fgi = (rxfs & RXFS_FGI_MASK) >> RXFS_FGI_SHIFT;
	dlc = m_can_fअगरo_पढ़ो(cdev, fgi, M_CAN_FIFO_DLC);
	अगर (dlc & RX_BUF_FDF)
		skb = alloc_canfd_skb(dev, &cf);
	अन्यथा
		skb = alloc_can_skb(dev, (काष्ठा can_frame **)&cf);
	अगर (!skb) अणु
		stats->rx_dropped++;
		वापस;
	पूर्ण

	अगर (dlc & RX_BUF_FDF)
		cf->len = can_fd_dlc2len((dlc >> 16) & 0x0F);
	अन्यथा
		cf->len = can_cc_dlc2len((dlc >> 16) & 0x0F);

	id = m_can_fअगरo_पढ़ो(cdev, fgi, M_CAN_FIFO_ID);
	अगर (id & RX_BUF_XTD)
		cf->can_id = (id & CAN_EFF_MASK) | CAN_EFF_FLAG;
	अन्यथा
		cf->can_id = (id >> 18) & CAN_SFF_MASK;

	अगर (id & RX_BUF_ESI) अणु
		cf->flags |= CANFD_ESI;
		netdev_dbg(dev, "ESI Error\n");
	पूर्ण

	अगर (!(dlc & RX_BUF_FDF) && (id & RX_BUF_RTR)) अणु
		cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		अगर (dlc & RX_BUF_BRS)
			cf->flags |= CANFD_BRS;

		क्रम (i = 0; i < cf->len; i += 4)
			*(u32 *)(cf->data + i) =
				m_can_fअगरo_पढ़ो(cdev, fgi,
						M_CAN_FIFO_DATA(i / 4));
	पूर्ण

	/* acknowledge rx fअगरo 0 */
	m_can_ग_लिखो(cdev, M_CAN_RXF0A, fgi);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	बारtamp = FIELD_GET(RX_BUF_RXTS_MASK, dlc);

	m_can_receive_skb(cdev, skb, बारtamp);
पूर्ण

अटल पूर्णांक m_can_करो_rx_poll(काष्ठा net_device *dev, पूर्णांक quota)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	u32 pkts = 0;
	u32 rxfs;

	rxfs = m_can_पढ़ो(cdev, M_CAN_RXF0S);
	अगर (!(rxfs & RXFS_FFL_MASK)) अणु
		netdev_dbg(dev, "no messages in fifo0\n");
		वापस 0;
	पूर्ण

	जबतक ((rxfs & RXFS_FFL_MASK) && (quota > 0)) अणु
		m_can_पढ़ो_fअगरo(dev, rxfs);

		quota--;
		pkts++;
		rxfs = m_can_पढ़ो(cdev, M_CAN_RXF0S);
	पूर्ण

	अगर (pkts)
		can_led_event(dev, CAN_LED_EVENT_RX);

	वापस pkts;
पूर्ण

अटल पूर्णांक m_can_handle_lost_msg(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *frame;
	u32 बारtamp = 0;

	netdev_err(dev, "msg lost in rxf0\n");

	stats->rx_errors++;
	stats->rx_over_errors++;

	skb = alloc_can_err_skb(dev, &frame);
	अगर (unlikely(!skb))
		वापस 0;

	frame->can_id |= CAN_ERR_CRTL;
	frame->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;

	अगर (cdev->is_peripheral)
		बारtamp = m_can_get_बारtamp(cdev);

	m_can_receive_skb(cdev, skb, बारtamp);

	वापस 1;
पूर्ण

अटल पूर्णांक m_can_handle_lec_err(काष्ठा net_device *dev,
				क्रमागत m_can_lec_type lec_type)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 बारtamp = 0;

	cdev->can.can_stats.bus_error++;
	stats->rx_errors++;

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	/* check क्रम 'last error code' which tells us the
	 * type of the last error to occur on the CAN bus
	 */
	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	चयन (lec_type) अणु
	हाल LEC_STUFF_ERROR:
		netdev_dbg(dev, "stuff error\n");
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		अवरोध;
	हाल LEC_FORM_ERROR:
		netdev_dbg(dev, "form error\n");
		cf->data[2] |= CAN_ERR_PROT_FORM;
		अवरोध;
	हाल LEC_ACK_ERROR:
		netdev_dbg(dev, "ack error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;
		अवरोध;
	हाल LEC_BIT1_ERROR:
		netdev_dbg(dev, "bit1 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT1;
		अवरोध;
	हाल LEC_BIT0_ERROR:
		netdev_dbg(dev, "bit0 error\n");
		cf->data[2] |= CAN_ERR_PROT_BIT0;
		अवरोध;
	हाल LEC_CRC_ERROR:
		netdev_dbg(dev, "CRC error\n");
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	अगर (cdev->is_peripheral)
		बारtamp = m_can_get_बारtamp(cdev);

	m_can_receive_skb(cdev, skb, बारtamp);

	वापस 1;
पूर्ण

अटल पूर्णांक __m_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				    काष्ठा can_berr_counter *bec)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	अचिन्हित पूर्णांक ecr;

	ecr = m_can_पढ़ो(cdev, M_CAN_ECR);
	bec->rxerr = (ecr & ECR_REC_MASK) >> ECR_REC_SHIFT;
	bec->txerr = (ecr & ECR_TEC_MASK) >> ECR_TEC_SHIFT;

	वापस 0;
पूर्ण

अटल पूर्णांक m_can_clk_start(काष्ठा m_can_classdev *cdev)
अणु
	अगर (cdev->pm_घड़ी_support == 0)
		वापस 0;

	वापस pm_runसमय_resume_and_get(cdev->dev);
पूर्ण

अटल व्योम m_can_clk_stop(काष्ठा m_can_classdev *cdev)
अणु
	अगर (cdev->pm_घड़ी_support)
		pm_runसमय_put_sync(cdev->dev);
पूर्ण

अटल पूर्णांक m_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				  काष्ठा can_berr_counter *bec)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक err;

	err = m_can_clk_start(cdev);
	अगर (err)
		वापस err;

	__m_can_get_berr_counter(dev, bec);

	m_can_clk_stop(cdev);

	वापस 0;
पूर्ण

अटल पूर्णांक m_can_handle_state_change(काष्ठा net_device *dev,
				     क्रमागत can_state new_state)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	काष्ठा can_berr_counter bec;
	अचिन्हित पूर्णांक ecr;
	u32 बारtamp = 0;

	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_WARNING:
		/* error warning state */
		cdev->can.can_stats.error_warning++;
		cdev->can.state = CAN_STATE_ERROR_WARNING;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		cdev->can.can_stats.error_passive++;
		cdev->can.state = CAN_STATE_ERROR_PASSIVE;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		/* bus-off state */
		cdev->can.state = CAN_STATE_BUS_OFF;
		m_can_disable_all_पूर्णांकerrupts(cdev);
		cdev->can.can_stats.bus_off++;
		can_bus_off(dev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);
	अगर (unlikely(!skb))
		वापस 0;

	__m_can_get_berr_counter(dev, &bec);

	चयन (new_state) अणु
	हाल CAN_STATE_ERROR_WARNING:
		/* error warning state */
		cf->can_id |= CAN_ERR_CRTL;
		cf->data[1] = (bec.txerr > bec.rxerr) ?
			CAN_ERR_CRTL_TX_WARNING :
			CAN_ERR_CRTL_RX_WARNING;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल CAN_STATE_ERROR_PASSIVE:
		/* error passive state */
		cf->can_id |= CAN_ERR_CRTL;
		ecr = m_can_पढ़ो(cdev, M_CAN_ECR);
		अगर (ecr & ECR_RP)
			cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		अगर (bec.txerr > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
		cf->data[6] = bec.txerr;
		cf->data[7] = bec.rxerr;
		अवरोध;
	हाल CAN_STATE_BUS_OFF:
		/* bus-off state */
		cf->can_id |= CAN_ERR_BUSOFF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	अगर (cdev->is_peripheral)
		बारtamp = m_can_get_बारtamp(cdev);

	m_can_receive_skb(cdev, skb, बारtamp);

	वापस 1;
पूर्ण

अटल पूर्णांक m_can_handle_state_errors(काष्ठा net_device *dev, u32 psr)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक work_करोne = 0;

	अगर (psr & PSR_EW && cdev->can.state != CAN_STATE_ERROR_WARNING) अणु
		netdev_dbg(dev, "entered error warning state\n");
		work_करोne += m_can_handle_state_change(dev,
						       CAN_STATE_ERROR_WARNING);
	पूर्ण

	अगर (psr & PSR_EP && cdev->can.state != CAN_STATE_ERROR_PASSIVE) अणु
		netdev_dbg(dev, "entered error passive state\n");
		work_करोne += m_can_handle_state_change(dev,
						       CAN_STATE_ERROR_PASSIVE);
	पूर्ण

	अगर (psr & PSR_BO && cdev->can.state != CAN_STATE_BUS_OFF) अणु
		netdev_dbg(dev, "entered error bus off state\n");
		work_करोne += m_can_handle_state_change(dev,
						       CAN_STATE_BUS_OFF);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम m_can_handle_other_err(काष्ठा net_device *dev, u32 irqstatus)
अणु
	अगर (irqstatus & IR_WDI)
		netdev_err(dev, "Message RAM Watchdog event due to missing READY\n");
	अगर (irqstatus & IR_ELO)
		netdev_err(dev, "Error Logging Overflow\n");
	अगर (irqstatus & IR_BEU)
		netdev_err(dev, "Bit Error Uncorrected\n");
	अगर (irqstatus & IR_BEC)
		netdev_err(dev, "Bit Error Corrected\n");
	अगर (irqstatus & IR_TOO)
		netdev_err(dev, "Timeout reached\n");
	अगर (irqstatus & IR_MRAF)
		netdev_err(dev, "Message RAM access failure occurred\n");
पूर्ण

अटल अंतरभूत bool is_lec_err(u32 psr)
अणु
	psr &= LEC_UNUSED;

	वापस psr && (psr != LEC_UNUSED);
पूर्ण

अटल अंतरभूत bool m_can_is_protocol_err(u32 irqstatus)
अणु
	वापस irqstatus & IR_ERR_LEC_31X;
पूर्ण

अटल पूर्णांक m_can_handle_protocol_error(काष्ठा net_device *dev, u32 irqstatus)
अणु
	काष्ठा net_device_stats *stats = &dev->stats;
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 बारtamp = 0;

	/* propagate the error condition to the CAN stack */
	skb = alloc_can_err_skb(dev, &cf);

	/* update tx error stats since there is protocol error */
	stats->tx_errors++;

	/* update arbitration lost status */
	अगर (cdev->version >= 31 && (irqstatus & IR_PEA)) अणु
		netdev_dbg(dev, "Protocol error in Arbitration fail\n");
		cdev->can.can_stats.arbitration_lost++;
		अगर (skb) अणु
			cf->can_id |= CAN_ERR_LOSTARB;
			cf->data[0] |= CAN_ERR_LOSTARB_UNSPEC;
		पूर्ण
	पूर्ण

	अगर (unlikely(!skb)) अणु
		netdev_dbg(dev, "allocation of skb failed\n");
		वापस 0;
	पूर्ण

	अगर (cdev->is_peripheral)
		बारtamp = m_can_get_बारtamp(cdev);

	m_can_receive_skb(cdev, skb, बारtamp);

	वापस 1;
पूर्ण

अटल पूर्णांक m_can_handle_bus_errors(काष्ठा net_device *dev, u32 irqstatus,
				   u32 psr)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक work_करोne = 0;

	अगर (irqstatus & IR_RF0L)
		work_करोne += m_can_handle_lost_msg(dev);

	/* handle lec errors on the bus */
	अगर ((cdev->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) &&
	    is_lec_err(psr))
		work_करोne += m_can_handle_lec_err(dev, psr & LEC_UNUSED);

	/* handle protocol errors in arbitration phase */
	अगर ((cdev->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) &&
	    m_can_is_protocol_err(irqstatus))
		work_करोne += m_can_handle_protocol_error(dev, irqstatus);

	/* other unproccessed error पूर्णांकerrupts */
	m_can_handle_other_err(dev, irqstatus);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक m_can_rx_handler(काष्ठा net_device *dev, पूर्णांक quota)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक work_करोne = 0;
	u32 irqstatus, psr;

	irqstatus = cdev->irqstatus | m_can_पढ़ो(cdev, M_CAN_IR);
	अगर (!irqstatus)
		जाओ end;

	/* Errata workaround क्रम issue "Needless activation of MRAF irq"
	 * During frame reception जबतक the MCAN is in Error Passive state
	 * and the Receive Error Counter has the value MCAN_ECR.REC = 127,
	 * it may happen that MCAN_IR.MRAF is set although there was no
	 * Message RAM access failure.
	 * If MCAN_IR.MRAF is enabled, an पूर्णांकerrupt to the Host CPU is generated
	 * The Message RAM Access Failure पूर्णांकerrupt routine needs to check
	 * whether MCAN_ECR.RP = ै 1ै  and MCAN_ECR.REC = 127.
	 * In this हाल, reset MCAN_IR.MRAF. No further action is required.
	 */
	अगर (cdev->version <= 31 && irqstatus & IR_MRAF &&
	    m_can_पढ़ो(cdev, M_CAN_ECR) & ECR_RP) अणु
		काष्ठा can_berr_counter bec;

		__m_can_get_berr_counter(dev, &bec);
		अगर (bec.rxerr == 127) अणु
			m_can_ग_लिखो(cdev, M_CAN_IR, IR_MRAF);
			irqstatus &= ~IR_MRAF;
		पूर्ण
	पूर्ण

	psr = m_can_पढ़ो(cdev, M_CAN_PSR);

	अगर (irqstatus & IR_ERR_STATE)
		work_करोne += m_can_handle_state_errors(dev, psr);

	अगर (irqstatus & IR_ERR_BUS_30X)
		work_करोne += m_can_handle_bus_errors(dev, irqstatus, psr);

	अगर (irqstatus & IR_RF0N)
		work_करोne += m_can_करो_rx_poll(dev, (quota - work_करोne));
end:
	वापस work_करोne;
पूर्ण

अटल पूर्णांक m_can_rx_peripheral(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	m_can_rx_handler(dev, M_CAN_NAPI_WEIGHT);

	m_can_enable_all_पूर्णांकerrupts(cdev);

	वापस 0;
पूर्ण

अटल पूर्णांक m_can_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *dev = napi->dev;
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक work_करोne;

	work_करोne = m_can_rx_handler(dev, quota);
	अगर (work_करोne < quota) अणु
		napi_complete_करोne(napi, work_करोne);
		m_can_enable_all_पूर्णांकerrupts(cdev);
	पूर्ण

	वापस work_करोne;
पूर्ण

/* Echo tx skb and update net stats. Peripherals use rx-offload क्रम
 * echo. बारtamp is used क्रम peripherals to ensure correct ordering
 * by rx-offload, and is ignored क्रम non-peripherals.
*/
अटल व्योम m_can_tx_update_stats(काष्ठा m_can_classdev *cdev,
				  अचिन्हित पूर्णांक msg_mark,
				  u32 बारtamp)
अणु
	काष्ठा net_device *dev = cdev->net;
	काष्ठा net_device_stats *stats = &dev->stats;

	अगर (cdev->is_peripheral)
		stats->tx_bytes +=
			can_rx_offload_get_echo_skb(&cdev->offload,
						    msg_mark,
						    बारtamp,
						    शून्य);
	अन्यथा
		stats->tx_bytes += can_get_echo_skb(dev, msg_mark, शून्य);

	stats->tx_packets++;
पूर्ण

अटल व्योम m_can_echo_tx_event(काष्ठा net_device *dev)
अणु
	u32 txe_count = 0;
	u32 m_can_txefs;
	u32 fgi = 0;
	पूर्णांक i = 0;
	अचिन्हित पूर्णांक msg_mark;

	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	/* पढ़ो tx event fअगरo status */
	m_can_txefs = m_can_पढ़ो(cdev, M_CAN_TXEFS);

	/* Get Tx Event fअगरo element count */
	txe_count = (m_can_txefs & TXEFS_EFFL_MASK) >> TXEFS_EFFL_SHIFT;

	/* Get and process all sent elements */
	क्रम (i = 0; i < txe_count; i++) अणु
		u32 txe, बारtamp = 0;

		/* retrieve get index */
		fgi = (m_can_पढ़ो(cdev, M_CAN_TXEFS) & TXEFS_EFGI_MASK) >>
			TXEFS_EFGI_SHIFT;

		/* get message marker, बारtamp */
		txe = m_can_txe_fअगरo_पढ़ो(cdev, fgi, 4);
		msg_mark = (txe & TX_EVENT_MM_MASK) >> TX_EVENT_MM_SHIFT;
		बारtamp = FIELD_GET(TX_EVENT_TXTS_MASK, txe);

		/* ack txe element */
		m_can_ग_लिखो(cdev, M_CAN_TXEFA, (TXEFA_EFAI_MASK &
						(fgi << TXEFA_EFAI_SHIFT)));

		/* update stats */
		m_can_tx_update_stats(cdev, msg_mark, बारtamp);
	पूर्ण
पूर्ण

अटल irqवापस_t m_can_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	u32 ir;

	अगर (pm_runसमय_suspended(cdev->dev))
		वापस IRQ_NONE;
	ir = m_can_पढ़ो(cdev, M_CAN_IR);
	अगर (!ir)
		वापस IRQ_NONE;

	/* ACK all irqs */
	अगर (ir & IR_ALL_INT)
		m_can_ग_लिखो(cdev, M_CAN_IR, ir);

	अगर (cdev->ops->clear_पूर्णांकerrupts)
		cdev->ops->clear_पूर्णांकerrupts(cdev);

	/* schedule NAPI in हाल of
	 * - rx IRQ
	 * - state change IRQ
	 * - bus error IRQ and bus error reporting
	 */
	अगर ((ir & IR_RF0N) || (ir & IR_ERR_ALL_30X)) अणु
		cdev->irqstatus = ir;
		m_can_disable_all_पूर्णांकerrupts(cdev);
		अगर (!cdev->is_peripheral)
			napi_schedule(&cdev->napi);
		अन्यथा
			m_can_rx_peripheral(dev);
	पूर्ण

	अगर (cdev->version == 30) अणु
		अगर (ir & IR_TC) अणु
			/* Transmission Complete Interrupt*/
			u32 बारtamp = 0;

			अगर (cdev->is_peripheral)
				बारtamp = m_can_get_बारtamp(cdev);
			m_can_tx_update_stats(cdev, 0, बारtamp);

			can_led_event(dev, CAN_LED_EVENT_TX);
			netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण अन्यथा  अणु
		अगर (ir & IR_TEFN) अणु
			/* New TX FIFO Element arrived */
			m_can_echo_tx_event(dev);
			can_led_event(dev, CAN_LED_EVENT_TX);
			अगर (netअगर_queue_stopped(dev) &&
			    !m_can_tx_fअगरo_full(cdev))
				netअगर_wake_queue(dev);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा can_bittiming_स्थिर m_can_bittiming_स्थिर_30X = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 64,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 1024,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर m_can_data_bittiming_स्थिर_30X = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 16,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 32,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर m_can_bittiming_स्थिर_31X = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 256,
	.tseg2_min = 2,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 128,
	.sjw_max = 128,
	.brp_min = 1,
	.brp_max = 512,
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर m_can_data_bittiming_स्थिर_31X = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 1,		/* Time segment 1 = prop_seg + phase_seg1 */
	.tseg1_max = 32,
	.tseg2_min = 1,		/* Time segment 2 = phase_seg2 */
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 32,
	.brp_inc = 1,
पूर्ण;

अटल पूर्णांक m_can_set_bittiming(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	स्थिर काष्ठा can_bittiming *bt = &cdev->can.bittiming;
	स्थिर काष्ठा can_bittiming *dbt = &cdev->can.data_bittiming;
	u16 brp, sjw, tseg1, tseg2;
	u32 reg_btp;

	brp = bt->brp - 1;
	sjw = bt->sjw - 1;
	tseg1 = bt->prop_seg + bt->phase_seg1 - 1;
	tseg2 = bt->phase_seg2 - 1;
	reg_btp = (brp << NBTP_NBRP_SHIFT) | (sjw << NBTP_NSJW_SHIFT) |
		(tseg1 << NBTP_NTSEG1_SHIFT) | (tseg2 << NBTP_NTSEG2_SHIFT);
	m_can_ग_लिखो(cdev, M_CAN_NBTP, reg_btp);

	अगर (cdev->can.ctrlmode & CAN_CTRLMODE_FD) अणु
		reg_btp = 0;
		brp = dbt->brp - 1;
		sjw = dbt->sjw - 1;
		tseg1 = dbt->prop_seg + dbt->phase_seg1 - 1;
		tseg2 = dbt->phase_seg2 - 1;

		/* TDC is only needed क्रम bitrates beyond 2.5 MBit/s.
		 * This is mentioned in the "Bit Time Requirements for CAN FD"
		 * paper presented at the International CAN Conference 2013
		 */
		अगर (dbt->bitrate > 2500000) अणु
			u32 tdco, ssp;

			/* Use the same value of secondary sampling poपूर्णांक
			 * as the data sampling poपूर्णांक
			 */
			ssp = dbt->sample_poपूर्णांक;

			/* Equation based on Bosch's M_CAN User Manual's
			 * Transmitter Delay Compensation Section
			 */
			tdco = (cdev->can.घड़ी.freq / 1000) *
				ssp / dbt->bitrate;

			/* Max valid TDCO value is 127 */
			अगर (tdco > 127) अणु
				netdev_warn(dev, "TDCO value of %u is beyond maximum. Using maximum possible value\n",
					    tdco);
				tdco = 127;
			पूर्ण

			reg_btp |= DBTP_TDC;
			m_can_ग_लिखो(cdev, M_CAN_TDCR,
				    tdco << TDCR_TDCO_SHIFT);
		पूर्ण

		reg_btp |= (brp << DBTP_DBRP_SHIFT) |
			(sjw << DBTP_DSJW_SHIFT) |
			(tseg1 << DBTP_DTSEG1_SHIFT) |
			(tseg2 << DBTP_DTSEG2_SHIFT);

		m_can_ग_लिखो(cdev, M_CAN_DBTP, reg_btp);
	पूर्ण

	वापस 0;
पूर्ण

/* Configure M_CAN chip:
 * - set rx buffer/fअगरo element size
 * - configure rx fअगरo
 * - accept non-matching frame पूर्णांकo fअगरo 0
 * - configure tx buffer
 *		- >= v3.1.x: TX FIFO is used
 * - configure mode
 * - setup bittiming
 * - configure बारtamp generation
 */
अटल व्योम m_can_chip_config(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	u32 cccr, test;

	m_can_config_endisable(cdev, true);

	/* RX Buffer/FIFO Element Size 64 bytes data field */
	m_can_ग_लिखो(cdev, M_CAN_RXESC, M_CAN_RXESC_64BYTES);

	/* Accept Non-matching Frames Into FIFO 0 */
	m_can_ग_लिखो(cdev, M_CAN_GFC, 0x0);

	अगर (cdev->version == 30) अणु
		/* only support one Tx Buffer currently */
		m_can_ग_लिखो(cdev, M_CAN_TXBC, (1 << TXBC_NDTB_SHIFT) |
			    cdev->mcfg[MRAM_TXB].off);
	पूर्ण अन्यथा अणु
		/* TX FIFO is used क्रम newer IP Core versions */
		m_can_ग_लिखो(cdev, M_CAN_TXBC,
			    (cdev->mcfg[MRAM_TXB].num << TXBC_TFQS_SHIFT) |
			    (cdev->mcfg[MRAM_TXB].off));
	पूर्ण

	/* support 64 bytes payload */
	m_can_ग_लिखो(cdev, M_CAN_TXESC, TXESC_TBDS_64BYTES);

	/* TX Event FIFO */
	अगर (cdev->version == 30) अणु
		m_can_ग_लिखो(cdev, M_CAN_TXEFC, (1 << TXEFC_EFS_SHIFT) |
			    cdev->mcfg[MRAM_TXE].off);
	पूर्ण अन्यथा अणु
		/* Full TX Event FIFO is used */
		m_can_ग_लिखो(cdev, M_CAN_TXEFC,
			    ((cdev->mcfg[MRAM_TXE].num << TXEFC_EFS_SHIFT)
			     & TXEFC_EFS_MASK) |
			    cdev->mcfg[MRAM_TXE].off);
	पूर्ण

	/* rx fअगरo configuration, blocking mode, fअगरo size 1 */
	m_can_ग_लिखो(cdev, M_CAN_RXF0C,
		    (cdev->mcfg[MRAM_RXF0].num << RXFC_FS_SHIFT) |
		    cdev->mcfg[MRAM_RXF0].off);

	m_can_ग_लिखो(cdev, M_CAN_RXF1C,
		    (cdev->mcfg[MRAM_RXF1].num << RXFC_FS_SHIFT) |
		    cdev->mcfg[MRAM_RXF1].off);

	cccr = m_can_पढ़ो(cdev, M_CAN_CCCR);
	test = m_can_पढ़ो(cdev, M_CAN_TEST);
	test &= ~TEST_LBCK;
	अगर (cdev->version == 30) अणु
		/* Version 3.0.x */

		cccr &= ~(CCCR_TEST | CCCR_MON | CCCR_DAR |
			  (CCCR_CMR_MASK << CCCR_CMR_SHIFT) |
			  (CCCR_CME_MASK << CCCR_CME_SHIFT));

		अगर (cdev->can.ctrlmode & CAN_CTRLMODE_FD)
			cccr |= CCCR_CME_CANFD_BRS << CCCR_CME_SHIFT;

	पूर्ण अन्यथा अणु
		/* Version 3.1.x or 3.2.x */
		cccr &= ~(CCCR_TEST | CCCR_MON | CCCR_BRSE | CCCR_FDOE |
			  CCCR_NISO | CCCR_DAR);

		/* Only 3.2.x has NISO Bit implemented */
		अगर (cdev->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO)
			cccr |= CCCR_NISO;

		अगर (cdev->can.ctrlmode & CAN_CTRLMODE_FD)
			cccr |= (CCCR_BRSE | CCCR_FDOE);
	पूर्ण

	/* Loopback Mode */
	अगर (cdev->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) अणु
		cccr |= CCCR_TEST | CCCR_MON;
		test |= TEST_LBCK;
	पूर्ण

	/* Enable Monitoring (all versions) */
	अगर (cdev->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		cccr |= CCCR_MON;

	/* Disable Auto Retransmission (all versions) */
	अगर (cdev->can.ctrlmode & CAN_CTRLMODE_ONE_SHOT)
		cccr |= CCCR_DAR;

	/* Write config */
	m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr);
	m_can_ग_लिखो(cdev, M_CAN_TEST, test);

	/* Enable पूर्णांकerrupts */
	m_can_ग_लिखो(cdev, M_CAN_IR, IR_ALL_INT);
	अगर (!(cdev->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING))
		अगर (cdev->version == 30)
			m_can_ग_लिखो(cdev, M_CAN_IE, IR_ALL_INT &
				    ~(IR_ERR_LEC_30X));
		अन्यथा
			m_can_ग_लिखो(cdev, M_CAN_IE, IR_ALL_INT &
				    ~(IR_ERR_LEC_31X));
	अन्यथा
		m_can_ग_लिखो(cdev, M_CAN_IE, IR_ALL_INT);

	/* route all पूर्णांकerrupts to INT0 */
	m_can_ग_लिखो(cdev, M_CAN_ILS, ILS_ALL_INT0);

	/* set bittiming params */
	m_can_set_bittiming(dev);

	/* enable पूर्णांकernal बारtamp generation, with a prescalar of 16. The
	 * prescalar is applied to the nominal bit timing */
	m_can_ग_लिखो(cdev, M_CAN_TSCC, FIELD_PREP(TSCC_TCP_MASK, 0xf));

	m_can_config_endisable(cdev, false);

	अगर (cdev->ops->init)
		cdev->ops->init(cdev);
पूर्ण

अटल व्योम m_can_start(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	/* basic m_can configuration */
	m_can_chip_config(dev);

	cdev->can.state = CAN_STATE_ERROR_ACTIVE;

	m_can_enable_all_पूर्णांकerrupts(cdev);
पूर्ण

अटल पूर्णांक m_can_set_mode(काष्ठा net_device *dev, क्रमागत can_mode mode)
अणु
	चयन (mode) अणु
	हाल CAN_MODE_START:
		m_can_clean(dev);
		m_can_start(dev);
		netअगर_wake_queue(dev);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

/* Checks core release number of M_CAN
 * वापसs 0 अगर an unsupported device is detected
 * अन्यथा it वापसs the release and step coded as:
 * वापस value = 10 * <release> + 1 * <step>
 */
अटल पूर्णांक m_can_check_core_release(काष्ठा m_can_classdev *cdev)
अणु
	u32 crel_reg;
	u8 rel;
	u8 step;
	पूर्णांक res;

	/* Read Core Release Version and split पूर्णांकo version number
	 * Example: Version 3.2.1 => rel = 3; step = 2; substep = 1;
	 */
	crel_reg = m_can_पढ़ो(cdev, M_CAN_CREL);
	rel = (u8)((crel_reg & CREL_REL_MASK) >> CREL_REL_SHIFT);
	step = (u8)((crel_reg & CREL_STEP_MASK) >> CREL_STEP_SHIFT);

	अगर (rel == 3) अणु
		/* M_CAN v3.x.y: create वापस value */
		res = 30 + step;
	पूर्ण अन्यथा अणु
		/* Unsupported M_CAN version */
		res = 0;
	पूर्ण

	वापस res;
पूर्ण

/* Selectable Non ISO support only in version 3.2.x
 * This function checks अगर the bit is writable.
 */
अटल bool m_can_niso_supported(काष्ठा m_can_classdev *cdev)
अणु
	u32 cccr_reg, cccr_poll = 0;
	पूर्णांक niso_समयout = -ETIMEDOUT;
	पूर्णांक i;

	m_can_config_endisable(cdev, true);
	cccr_reg = m_can_पढ़ो(cdev, M_CAN_CCCR);
	cccr_reg |= CCCR_NISO;
	m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr_reg);

	क्रम (i = 0; i <= 10; i++) अणु
		cccr_poll = m_can_पढ़ो(cdev, M_CAN_CCCR);
		अगर (cccr_poll == cccr_reg) अणु
			niso_समयout = 0;
			अवरोध;
		पूर्ण

		usleep_range(1, 5);
	पूर्ण

	/* Clear NISO */
	cccr_reg &= ~(CCCR_NISO);
	m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr_reg);

	m_can_config_endisable(cdev, false);

	/* वापस false अगर समय out (-ETIMEDOUT), अन्यथा वापस true */
	वापस !niso_समयout;
पूर्ण

अटल पूर्णांक m_can_dev_setup(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा net_device *dev = cdev->net;
	पूर्णांक m_can_version;

	m_can_version = m_can_check_core_release(cdev);
	/* वापस अगर unsupported version */
	अगर (!m_can_version) अणु
		dev_err(cdev->dev, "Unsupported version number: %2d",
			m_can_version);
		वापस -EINVAL;
	पूर्ण

	अगर (!cdev->is_peripheral)
		netअगर_napi_add(dev, &cdev->napi,
			       m_can_poll, M_CAN_NAPI_WEIGHT);

	/* Shared properties of all M_CAN versions */
	cdev->version = m_can_version;
	cdev->can.करो_set_mode = m_can_set_mode;
	cdev->can.करो_get_berr_counter = m_can_get_berr_counter;

	/* Set M_CAN supported operations */
	cdev->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
		CAN_CTRLMODE_LISTENONLY |
		CAN_CTRLMODE_BERR_REPORTING |
		CAN_CTRLMODE_FD |
		CAN_CTRLMODE_ONE_SHOT;

	/* Set properties depending on M_CAN version */
	चयन (cdev->version) अणु
	हाल 30:
		/* CAN_CTRLMODE_FD_NON_ISO is fixed with M_CAN IP v3.0.x */
		can_set_अटल_ctrlmode(dev, CAN_CTRLMODE_FD_NON_ISO);
		cdev->can.bittiming_स्थिर = cdev->bit_timing ?
			cdev->bit_timing : &m_can_bittiming_स्थिर_30X;

		cdev->can.data_bittiming_स्थिर = cdev->data_timing ?
			cdev->data_timing :
			&m_can_data_bittiming_स्थिर_30X;
		अवरोध;
	हाल 31:
		/* CAN_CTRLMODE_FD_NON_ISO is fixed with M_CAN IP v3.1.x */
		can_set_अटल_ctrlmode(dev, CAN_CTRLMODE_FD_NON_ISO);
		cdev->can.bittiming_स्थिर = cdev->bit_timing ?
			cdev->bit_timing : &m_can_bittiming_स्थिर_31X;

		cdev->can.data_bittiming_स्थिर = cdev->data_timing ?
			cdev->data_timing :
			&m_can_data_bittiming_स्थिर_31X;
		अवरोध;
	हाल 32:
	हाल 33:
		/* Support both MCAN version v3.2.x and v3.3.0 */
		cdev->can.bittiming_स्थिर = cdev->bit_timing ?
			cdev->bit_timing : &m_can_bittiming_स्थिर_31X;

		cdev->can.data_bittiming_स्थिर = cdev->data_timing ?
			cdev->data_timing :
			&m_can_data_bittiming_स्थिर_31X;

		cdev->can.ctrlmode_supported |=
			(m_can_niso_supported(cdev) ?
			 CAN_CTRLMODE_FD_NON_ISO : 0);
		अवरोध;
	शेष:
		dev_err(cdev->dev, "Unsupported version number: %2d",
			cdev->version);
		वापस -EINVAL;
	पूर्ण

	अगर (cdev->ops->init)
		cdev->ops->init(cdev);

	वापस 0;
पूर्ण

अटल व्योम m_can_stop(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	/* disable all पूर्णांकerrupts */
	m_can_disable_all_पूर्णांकerrupts(cdev);

	/* Set init mode to disengage from the network */
	m_can_config_endisable(cdev, true);

	/* set the state as STOPPED */
	cdev->can.state = CAN_STATE_STOPPED;
पूर्ण

अटल पूर्णांक m_can_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	netअगर_stop_queue(dev);

	अगर (!cdev->is_peripheral)
		napi_disable(&cdev->napi);

	m_can_stop(dev);
	m_can_clk_stop(cdev);
	मुक्त_irq(dev->irq, dev);

	अगर (cdev->is_peripheral) अणु
		cdev->tx_skb = शून्य;
		destroy_workqueue(cdev->tx_wq);
		cdev->tx_wq = शून्य;
	पूर्ण

	अगर (cdev->is_peripheral)
		can_rx_offload_disable(&cdev->offload);

	बंद_candev(dev);
	can_led_event(dev, CAN_LED_EVENT_STOP);

	वापस 0;
पूर्ण

अटल पूर्णांक m_can_next_echo_skb_occupied(काष्ठा net_device *dev, पूर्णांक putidx)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	/*get wrap around क्रम loopback skb index */
	अचिन्हित पूर्णांक wrap = cdev->can.echo_skb_max;
	पूर्णांक next_idx;

	/* calculate next index */
	next_idx = (++putidx >= wrap ? 0 : putidx);

	/* check अगर occupied */
	वापस !!cdev->can.echo_skb[next_idx];
पूर्ण

अटल netdev_tx_t m_can_tx_handler(काष्ठा m_can_classdev *cdev)
अणु
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)cdev->tx_skb->data;
	काष्ठा net_device *dev = cdev->net;
	काष्ठा sk_buff *skb = cdev->tx_skb;
	u32 id, cccr, fdflags;
	पूर्णांक i;
	पूर्णांक putidx;

	cdev->tx_skb = शून्य;

	/* Generate ID field क्रम TX buffer Element */
	/* Common to all supported M_CAN versions */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		id = cf->can_id & CAN_EFF_MASK;
		id |= TX_BUF_XTD;
	पूर्ण अन्यथा अणु
		id = ((cf->can_id & CAN_SFF_MASK) << 18);
	पूर्ण

	अगर (cf->can_id & CAN_RTR_FLAG)
		id |= TX_BUF_RTR;

	अगर (cdev->version == 30) अणु
		netअगर_stop_queue(dev);

		/* message ram configuration */
		m_can_fअगरo_ग_लिखो(cdev, 0, M_CAN_FIFO_ID, id);
		m_can_fअगरo_ग_लिखो(cdev, 0, M_CAN_FIFO_DLC,
				 can_fd_len2dlc(cf->len) << 16);

		क्रम (i = 0; i < cf->len; i += 4)
			m_can_fअगरo_ग_लिखो(cdev, 0,
					 M_CAN_FIFO_DATA(i / 4),
					 *(u32 *)(cf->data + i));

		can_put_echo_skb(skb, dev, 0, 0);

		अगर (cdev->can.ctrlmode & CAN_CTRLMODE_FD) अणु
			cccr = m_can_पढ़ो(cdev, M_CAN_CCCR);
			cccr &= ~(CCCR_CMR_MASK << CCCR_CMR_SHIFT);
			अगर (can_is_canfd_skb(skb)) अणु
				अगर (cf->flags & CANFD_BRS)
					cccr |= CCCR_CMR_CANFD_BRS <<
						CCCR_CMR_SHIFT;
				अन्यथा
					cccr |= CCCR_CMR_CANFD <<
						CCCR_CMR_SHIFT;
			पूर्ण अन्यथा अणु
				cccr |= CCCR_CMR_CAN << CCCR_CMR_SHIFT;
			पूर्ण
			m_can_ग_लिखो(cdev, M_CAN_CCCR, cccr);
		पूर्ण
		m_can_ग_लिखो(cdev, M_CAN_TXBTIE, 0x1);
		m_can_ग_लिखो(cdev, M_CAN_TXBAR, 0x1);
		/* End of xmit function क्रम version 3.0.x */
	पूर्ण अन्यथा अणु
		/* Transmit routine क्रम version >= v3.1.x */

		/* Check अगर FIFO full */
		अगर (m_can_tx_fअगरo_full(cdev)) अणु
			/* This shouldn't happen */
			netअगर_stop_queue(dev);
			netdev_warn(dev,
				    "TX queue active although FIFO is full.");

			अगर (cdev->is_peripheral) अणु
				kमुक्त_skb(skb);
				dev->stats.tx_dropped++;
				वापस NETDEV_TX_OK;
			पूर्ण अन्यथा अणु
				वापस NETDEV_TX_BUSY;
			पूर्ण
		पूर्ण

		/* get put index क्रम frame */
		putidx = ((m_can_पढ़ो(cdev, M_CAN_TXFQS) & TXFQS_TFQPI_MASK)
			  >> TXFQS_TFQPI_SHIFT);
		/* Write ID Field to FIFO Element */
		m_can_fअगरo_ग_लिखो(cdev, putidx, M_CAN_FIFO_ID, id);

		/* get CAN FD configuration of frame */
		fdflags = 0;
		अगर (can_is_canfd_skb(skb)) अणु
			fdflags |= TX_BUF_FDF;
			अगर (cf->flags & CANFD_BRS)
				fdflags |= TX_BUF_BRS;
		पूर्ण

		/* Conकाष्ठा DLC Field. Also contains CAN-FD configuration
		 * use put index of fअगरo as message marker
		 * it is used in TX पूर्णांकerrupt क्रम
		 * sending the correct echo frame
		 */
		m_can_fअगरo_ग_लिखो(cdev, putidx, M_CAN_FIFO_DLC,
				 ((putidx << TX_BUF_MM_SHIFT) &
				  TX_BUF_MM_MASK) |
				 (can_fd_len2dlc(cf->len) << 16) |
				 fdflags | TX_BUF_EFC);

		क्रम (i = 0; i < cf->len; i += 4)
			m_can_fअगरo_ग_लिखो(cdev, putidx, M_CAN_FIFO_DATA(i / 4),
					 *(u32 *)(cf->data + i));

		/* Push loopback echo.
		 * Will be looped back on TX पूर्णांकerrupt based on message marker
		 */
		can_put_echo_skb(skb, dev, putidx, 0);

		/* Enable TX FIFO element to start transfer  */
		m_can_ग_लिखो(cdev, M_CAN_TXBAR, (1 << putidx));

		/* stop network queue अगर fअगरo full */
		अगर (m_can_tx_fअगरo_full(cdev) ||
		    m_can_next_echo_skb_occupied(dev, putidx))
			netअगर_stop_queue(dev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम m_can_tx_work_queue(काष्ठा work_काष्ठा *ws)
अणु
	काष्ठा m_can_classdev *cdev = container_of(ws, काष्ठा m_can_classdev,
						   tx_work);

	m_can_tx_handler(cdev);
पूर्ण

अटल netdev_tx_t m_can_start_xmit(काष्ठा sk_buff *skb,
				    काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);

	अगर (can_dropped_invalid_skb(dev, skb))
		वापस NETDEV_TX_OK;

	अगर (cdev->is_peripheral) अणु
		अगर (cdev->tx_skb) अणु
			netdev_err(dev, "hard_xmit called while tx busy\n");
			वापस NETDEV_TX_BUSY;
		पूर्ण

		अगर (cdev->can.state == CAN_STATE_BUS_OFF) अणु
			m_can_clean(dev);
		पूर्ण अन्यथा अणु
			/* Need to stop the queue to aव्योम numerous requests
			 * from being sent.  Suggested improvement is to create
			 * a queueing mechanism that will queue the skbs and
			 * process them in order.
			 */
			cdev->tx_skb = skb;
			netअगर_stop_queue(cdev->net);
			queue_work(cdev->tx_wq, &cdev->tx_work);
		पूर्ण
	पूर्ण अन्यथा अणु
		cdev->tx_skb = skb;
		वापस m_can_tx_handler(cdev);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक m_can_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा m_can_classdev *cdev = netdev_priv(dev);
	पूर्णांक err;

	err = m_can_clk_start(cdev);
	अगर (err)
		वापस err;

	/* खोलो the can device */
	err = खोलो_candev(dev);
	अगर (err) अणु
		netdev_err(dev, "failed to open can device\n");
		जाओ निकास_disable_clks;
	पूर्ण

	अगर (cdev->is_peripheral)
		can_rx_offload_enable(&cdev->offload);

	/* रेजिस्टर पूर्णांकerrupt handler */
	अगर (cdev->is_peripheral) अणु
		cdev->tx_skb = शून्य;
		cdev->tx_wq = alloc_workqueue("mcan_wq",
					      WQ_FREEZABLE | WQ_MEM_RECLAIM, 0);
		अगर (!cdev->tx_wq) अणु
			err = -ENOMEM;
			जाओ out_wq_fail;
		पूर्ण

		INIT_WORK(&cdev->tx_work, m_can_tx_work_queue);

		err = request_thपढ़ोed_irq(dev->irq, शून्य, m_can_isr,
					   IRQF_ONESHOT,
					   dev->name, dev);
	पूर्ण अन्यथा अणु
		err = request_irq(dev->irq, m_can_isr, IRQF_SHARED, dev->name,
				  dev);
	पूर्ण

	अगर (err < 0) अणु
		netdev_err(dev, "failed to request interrupt\n");
		जाओ निकास_irq_fail;
	पूर्ण

	/* start the m_can controller */
	m_can_start(dev);

	can_led_event(dev, CAN_LED_EVENT_OPEN);

	अगर (!cdev->is_peripheral)
		napi_enable(&cdev->napi);

	netअगर_start_queue(dev);

	वापस 0;

निकास_irq_fail:
	अगर (cdev->is_peripheral)
		destroy_workqueue(cdev->tx_wq);
out_wq_fail:
	अगर (cdev->is_peripheral)
		can_rx_offload_disable(&cdev->offload);
	बंद_candev(dev);
निकास_disable_clks:
	m_can_clk_stop(cdev);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा net_device_ops m_can_netdev_ops = अणु
	.nकरो_खोलो = m_can_खोलो,
	.nकरो_stop = m_can_बंद,
	.nकरो_start_xmit = m_can_start_xmit,
	.nकरो_change_mtu = can_change_mtu,
पूर्ण;

अटल पूर्णांक रेजिस्टर_m_can_dev(काष्ठा net_device *dev)
अणु
	dev->flags |= IFF_ECHO;	/* we support local echo */
	dev->netdev_ops = &m_can_netdev_ops;

	वापस रेजिस्टर_candev(dev);
पूर्ण

अटल व्योम m_can_of_parse_mram(काष्ठा m_can_classdev *cdev,
				स्थिर u32 *mram_config_vals)
अणु
	cdev->mcfg[MRAM_SIDF].off = mram_config_vals[0];
	cdev->mcfg[MRAM_SIDF].num = mram_config_vals[1];
	cdev->mcfg[MRAM_XIDF].off = cdev->mcfg[MRAM_SIDF].off +
		cdev->mcfg[MRAM_SIDF].num * SIDF_ELEMENT_SIZE;
	cdev->mcfg[MRAM_XIDF].num = mram_config_vals[2];
	cdev->mcfg[MRAM_RXF0].off = cdev->mcfg[MRAM_XIDF].off +
		cdev->mcfg[MRAM_XIDF].num * XIDF_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXF0].num = mram_config_vals[3] &
		(RXFC_FS_MASK >> RXFC_FS_SHIFT);
	cdev->mcfg[MRAM_RXF1].off = cdev->mcfg[MRAM_RXF0].off +
		cdev->mcfg[MRAM_RXF0].num * RXF0_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXF1].num = mram_config_vals[4] &
		(RXFC_FS_MASK >> RXFC_FS_SHIFT);
	cdev->mcfg[MRAM_RXB].off = cdev->mcfg[MRAM_RXF1].off +
		cdev->mcfg[MRAM_RXF1].num * RXF1_ELEMENT_SIZE;
	cdev->mcfg[MRAM_RXB].num = mram_config_vals[5];
	cdev->mcfg[MRAM_TXE].off = cdev->mcfg[MRAM_RXB].off +
		cdev->mcfg[MRAM_RXB].num * RXB_ELEMENT_SIZE;
	cdev->mcfg[MRAM_TXE].num = mram_config_vals[6];
	cdev->mcfg[MRAM_TXB].off = cdev->mcfg[MRAM_TXE].off +
		cdev->mcfg[MRAM_TXE].num * TXE_ELEMENT_SIZE;
	cdev->mcfg[MRAM_TXB].num = mram_config_vals[7] &
		(TXBC_NDTB_MASK >> TXBC_NDTB_SHIFT);

	dev_dbg(cdev->dev,
		"sidf 0x%x %d xidf 0x%x %d rxf0 0x%x %d rxf1 0x%x %d rxb 0x%x %d txe 0x%x %d txb 0x%x %d\n",
		cdev->mcfg[MRAM_SIDF].off, cdev->mcfg[MRAM_SIDF].num,
		cdev->mcfg[MRAM_XIDF].off, cdev->mcfg[MRAM_XIDF].num,
		cdev->mcfg[MRAM_RXF0].off, cdev->mcfg[MRAM_RXF0].num,
		cdev->mcfg[MRAM_RXF1].off, cdev->mcfg[MRAM_RXF1].num,
		cdev->mcfg[MRAM_RXB].off, cdev->mcfg[MRAM_RXB].num,
		cdev->mcfg[MRAM_TXE].off, cdev->mcfg[MRAM_TXE].num,
		cdev->mcfg[MRAM_TXB].off, cdev->mcfg[MRAM_TXB].num);
पूर्ण

व्योम m_can_init_ram(काष्ठा m_can_classdev *cdev)
अणु
	पूर्णांक end, i, start;

	/* initialize the entire Message RAM in use to aव्योम possible
	 * ECC/parity checksum errors when पढ़ोing an uninitialized buffer
	 */
	start = cdev->mcfg[MRAM_SIDF].off;
	end = cdev->mcfg[MRAM_TXB].off +
		cdev->mcfg[MRAM_TXB].num * TXB_ELEMENT_SIZE;

	क्रम (i = start; i < end; i += 4)
		m_can_fअगरo_ग_लिखो_no_off(cdev, i, 0x0);
पूर्ण
EXPORT_SYMBOL_GPL(m_can_init_ram);

पूर्णांक m_can_class_get_घड़ीs(काष्ठा m_can_classdev *cdev)
अणु
	पूर्णांक ret = 0;

	cdev->hclk = devm_clk_get(cdev->dev, "hclk");
	cdev->cclk = devm_clk_get(cdev->dev, "cclk");

	अगर (IS_ERR(cdev->cclk)) अणु
		dev_err(cdev->dev, "no clock found\n");
		ret = -ENODEV;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_get_घड़ीs);

काष्ठा m_can_classdev *m_can_class_allocate_dev(काष्ठा device *dev,
						पूर्णांक माप_priv)
अणु
	काष्ठा m_can_classdev *class_dev = शून्य;
	u32 mram_config_vals[MRAM_CFG_LEN];
	काष्ठा net_device *net_dev;
	u32 tx_fअगरo_size;
	पूर्णांक ret;

	ret = fwnode_property_पढ़ो_u32_array(dev_fwnode(dev),
					     "bosch,mram-cfg",
					     mram_config_vals,
					     माप(mram_config_vals) / 4);
	अगर (ret) अणु
		dev_err(dev, "Could not get Message RAM configuration.");
		जाओ out;
	पूर्ण

	/* Get TX FIFO size
	 * Defines the total amount of echo buffers क्रम loopback
	 */
	tx_fअगरo_size = mram_config_vals[7];

	/* allocate the m_can device */
	net_dev = alloc_candev(माप_priv, tx_fअगरo_size);
	अगर (!net_dev) अणु
		dev_err(dev, "Failed to allocate CAN device");
		जाओ out;
	पूर्ण

	class_dev = netdev_priv(net_dev);
	class_dev->net = net_dev;
	class_dev->dev = dev;
	SET_NETDEV_DEV(net_dev, dev);

	m_can_of_parse_mram(class_dev, mram_config_vals);
out:
	वापस class_dev;
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_allocate_dev);

व्योम m_can_class_मुक्त_dev(काष्ठा net_device *net)
अणु
	मुक्त_candev(net);
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_मुक्त_dev);

पूर्णांक m_can_class_रेजिस्टर(काष्ठा m_can_classdev *cdev)
अणु
	पूर्णांक ret;

	अगर (cdev->pm_घड़ी_support) अणु
		ret = m_can_clk_start(cdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (cdev->is_peripheral) अणु
		ret = can_rx_offload_add_manual(cdev->net, &cdev->offload,
						M_CAN_NAPI_WEIGHT);
		अगर (ret)
			जाओ clk_disable;
	पूर्ण

	ret = m_can_dev_setup(cdev);
	अगर (ret)
		जाओ rx_offload_del;

	ret = रेजिस्टर_m_can_dev(cdev->net);
	अगर (ret) अणु
		dev_err(cdev->dev, "registering %s failed (err=%d)\n",
			cdev->net->name, ret);
		जाओ rx_offload_del;
	पूर्ण

	devm_can_led_init(cdev->net);

	of_can_transceiver(cdev->net);

	dev_info(cdev->dev, "%s device registered (irq=%d, version=%d)\n",
		 KBUILD_MODNAME, cdev->net->irq, cdev->version);

	/* Probe finished
	 * Stop घड़ीs. They will be reactivated once the M_CAN device is खोलोed
	 */
	m_can_clk_stop(cdev);

	वापस 0;

rx_offload_del:
	अगर (cdev->is_peripheral)
		can_rx_offload_del(&cdev->offload);
clk_disable:
	m_can_clk_stop(cdev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_रेजिस्टर);

व्योम m_can_class_unरेजिस्टर(काष्ठा m_can_classdev *cdev)
अणु
	अगर (cdev->is_peripheral)
		can_rx_offload_del(&cdev->offload);
	unरेजिस्टर_candev(cdev->net);
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_unरेजिस्टर);

पूर्णांक m_can_class_suspend(काष्ठा device *dev)
अणु
	काष्ठा m_can_classdev *cdev = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = cdev->net;

	अगर (netअगर_running(ndev)) अणु
		netअगर_stop_queue(ndev);
		netअगर_device_detach(ndev);
		m_can_stop(ndev);
		m_can_clk_stop(cdev);
	पूर्ण

	pinctrl_pm_select_sleep_state(dev);

	cdev->can.state = CAN_STATE_SLEEPING;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_suspend);

पूर्णांक m_can_class_resume(काष्ठा device *dev)
अणु
	काष्ठा m_can_classdev *cdev = dev_get_drvdata(dev);
	काष्ठा net_device *ndev = cdev->net;

	pinctrl_pm_select_शेष_state(dev);

	cdev->can.state = CAN_STATE_ERROR_ACTIVE;

	अगर (netअगर_running(ndev)) अणु
		पूर्णांक ret;

		ret = m_can_clk_start(cdev);
		अगर (ret)
			वापस ret;

		m_can_init_ram(cdev);
		m_can_start(ndev);
		netअगर_device_attach(ndev);
		netअगर_start_queue(ndev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(m_can_class_resume);

MODULE_AUTHOR("Dong Aisheng <b29396@freescale.com>");
MODULE_AUTHOR("Dan Murphy <dmurphy@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CAN bus driver for Bosch M_CAN controller");
