<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Xilinx CAN device driver
 *
 * Copyright (C) 2012 - 2014 Xilinx, Inc.
 * Copyright (C) 2009 PetaLogix. All rights reserved.
 * Copyright (C) 2017 - 2018 Sandvik Mining and Conकाष्ठाion Oy
 *
 * Description:
 * This driver is developed क्रम Axi CAN IP and क्रम Zynq CANPS Controller.
 */

#समावेश <linux/clk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>
#समावेश <linux/can/led.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा DRIVER_NAME	"xilinx_can"

/* CAN रेजिस्टरs set */
क्रमागत xcan_reg अणु
	XCAN_SRR_OFFSET		= 0x00, /* Software reset */
	XCAN_MSR_OFFSET		= 0x04, /* Mode select */
	XCAN_BRPR_OFFSET	= 0x08, /* Baud rate prescaler */
	XCAN_BTR_OFFSET		= 0x0C, /* Bit timing */
	XCAN_ECR_OFFSET		= 0x10, /* Error counter */
	XCAN_ESR_OFFSET		= 0x14, /* Error status */
	XCAN_SR_OFFSET		= 0x18, /* Status */
	XCAN_ISR_OFFSET		= 0x1C, /* Interrupt status */
	XCAN_IER_OFFSET		= 0x20, /* Interrupt enable */
	XCAN_ICR_OFFSET		= 0x24, /* Interrupt clear */

	/* not on CAN FD cores */
	XCAN_TXFIFO_OFFSET	= 0x30, /* TX FIFO base */
	XCAN_RXFIFO_OFFSET	= 0x50, /* RX FIFO base */
	XCAN_AFR_OFFSET		= 0x60, /* Acceptance Filter */

	/* only on CAN FD cores */
	XCAN_F_BRPR_OFFSET	= 0x088, /* Data Phase Baud Rate
					  * Prescalar
					  */
	XCAN_F_BTR_OFFSET	= 0x08C, /* Data Phase Bit Timing */
	XCAN_TRR_OFFSET		= 0x0090, /* TX Buffer Ready Request */
	XCAN_AFR_EXT_OFFSET	= 0x00E0, /* Acceptance Filter */
	XCAN_FSR_OFFSET		= 0x00E8, /* RX FIFO Status */
	XCAN_TXMSG_BASE_OFFSET	= 0x0100, /* TX Message Space */
	XCAN_RXMSG_BASE_OFFSET	= 0x1100, /* RX Message Space */
	XCAN_RXMSG_2_BASE_OFFSET	= 0x2100, /* RX Message Space */
	XCAN_AFR_2_MASK_OFFSET	= 0x0A00, /* Acceptance Filter MASK */
	XCAN_AFR_2_ID_OFFSET	= 0x0A04, /* Acceptance Filter ID */
पूर्ण;

#घोषणा XCAN_FRAME_ID_OFFSET(frame_base)	((frame_base) + 0x00)
#घोषणा XCAN_FRAME_DLC_OFFSET(frame_base)	((frame_base) + 0x04)
#घोषणा XCAN_FRAME_DW1_OFFSET(frame_base)	((frame_base) + 0x08)
#घोषणा XCAN_FRAME_DW2_OFFSET(frame_base)	((frame_base) + 0x0C)
#घोषणा XCANFD_FRAME_DW_OFFSET(frame_base)	((frame_base) + 0x08)

#घोषणा XCAN_CANFD_FRAME_SIZE		0x48
#घोषणा XCAN_TXMSG_FRAME_OFFSET(n)	(XCAN_TXMSG_BASE_OFFSET + \
					 XCAN_CANFD_FRAME_SIZE * (n))
#घोषणा XCAN_RXMSG_FRAME_OFFSET(n)	(XCAN_RXMSG_BASE_OFFSET + \
					 XCAN_CANFD_FRAME_SIZE * (n))
#घोषणा XCAN_RXMSG_2_FRAME_OFFSET(n)	(XCAN_RXMSG_2_BASE_OFFSET + \
					 XCAN_CANFD_FRAME_SIZE * (n))

/* the single TX mailbox used by this driver on CAN FD HW */
#घोषणा XCAN_TX_MAILBOX_IDX		0

/* CAN रेजिस्टर bit masks - XCAN_<REG>_<BIT>_MASK */
#घोषणा XCAN_SRR_CEN_MASK		0x00000002 /* CAN enable */
#घोषणा XCAN_SRR_RESET_MASK		0x00000001 /* Soft Reset the CAN core */
#घोषणा XCAN_MSR_LBACK_MASK		0x00000002 /* Loop back mode select */
#घोषणा XCAN_MSR_SLEEP_MASK		0x00000001 /* Sleep mode select */
#घोषणा XCAN_BRPR_BRP_MASK		0x000000FF /* Baud rate prescaler */
#घोषणा XCAN_BTR_SJW_MASK		0x00000180 /* Synchronous jump width */
#घोषणा XCAN_BTR_TS2_MASK		0x00000070 /* Time segment 2 */
#घोषणा XCAN_BTR_TS1_MASK		0x0000000F /* Time segment 1 */
#घोषणा XCAN_BTR_SJW_MASK_CANFD		0x000F0000 /* Synchronous jump width */
#घोषणा XCAN_BTR_TS2_MASK_CANFD		0x00000F00 /* Time segment 2 */
#घोषणा XCAN_BTR_TS1_MASK_CANFD		0x0000003F /* Time segment 1 */
#घोषणा XCAN_ECR_REC_MASK		0x0000FF00 /* Receive error counter */
#घोषणा XCAN_ECR_TEC_MASK		0x000000FF /* Transmit error counter */
#घोषणा XCAN_ESR_ACKER_MASK		0x00000010 /* ACK error */
#घोषणा XCAN_ESR_BERR_MASK		0x00000008 /* Bit error */
#घोषणा XCAN_ESR_STER_MASK		0x00000004 /* Stuff error */
#घोषणा XCAN_ESR_FMER_MASK		0x00000002 /* Form error */
#घोषणा XCAN_ESR_CRCER_MASK		0x00000001 /* CRC error */
#घोषणा XCAN_SR_TXFLL_MASK		0x00000400 /* TX FIFO is full */
#घोषणा XCAN_SR_ESTAT_MASK		0x00000180 /* Error status */
#घोषणा XCAN_SR_ERRWRN_MASK		0x00000040 /* Error warning */
#घोषणा XCAN_SR_NORMAL_MASK		0x00000008 /* Normal mode */
#घोषणा XCAN_SR_LBACK_MASK		0x00000002 /* Loop back mode */
#घोषणा XCAN_SR_CONFIG_MASK		0x00000001 /* Configuration mode */
#घोषणा XCAN_IXR_RXMNF_MASK		0x00020000 /* RX match not finished */
#घोषणा XCAN_IXR_TXFEMP_MASK		0x00004000 /* TX FIFO Empty */
#घोषणा XCAN_IXR_WKUP_MASK		0x00000800 /* Wake up पूर्णांकerrupt */
#घोषणा XCAN_IXR_SLP_MASK		0x00000400 /* Sleep पूर्णांकerrupt */
#घोषणा XCAN_IXR_BSOFF_MASK		0x00000200 /* Bus off पूर्णांकerrupt */
#घोषणा XCAN_IXR_ERROR_MASK		0x00000100 /* Error पूर्णांकerrupt */
#घोषणा XCAN_IXR_RXNEMP_MASK		0x00000080 /* RX FIFO NotEmpty पूर्णांकr */
#घोषणा XCAN_IXR_RXOFLW_MASK		0x00000040 /* RX FIFO Overflow पूर्णांकr */
#घोषणा XCAN_IXR_RXOK_MASK		0x00000010 /* Message received पूर्णांकr */
#घोषणा XCAN_IXR_TXFLL_MASK		0x00000004 /* Tx FIFO Full पूर्णांकr */
#घोषणा XCAN_IXR_TXOK_MASK		0x00000002 /* TX successful पूर्णांकr */
#घोषणा XCAN_IXR_ARBLST_MASK		0x00000001 /* Arbitration lost पूर्णांकr */
#घोषणा XCAN_IDR_ID1_MASK		0xFFE00000 /* Standard msg identअगरier */
#घोषणा XCAN_IDR_SRR_MASK		0x00100000 /* Substitute remote TXreq */
#घोषणा XCAN_IDR_IDE_MASK		0x00080000 /* Identअगरier extension */
#घोषणा XCAN_IDR_ID2_MASK		0x0007FFFE /* Extended message ident */
#घोषणा XCAN_IDR_RTR_MASK		0x00000001 /* Remote TX request */
#घोषणा XCAN_DLCR_DLC_MASK		0xF0000000 /* Data length code */
#घोषणा XCAN_FSR_FL_MASK		0x00003F00 /* RX Fill Level */
#घोषणा XCAN_2_FSR_FL_MASK		0x00007F00 /* RX Fill Level */
#घोषणा XCAN_FSR_IRI_MASK		0x00000080 /* RX Increment Read Index */
#घोषणा XCAN_FSR_RI_MASK		0x0000001F /* RX Read Index */
#घोषणा XCAN_2_FSR_RI_MASK		0x0000003F /* RX Read Index */
#घोषणा XCAN_DLCR_EDL_MASK		0x08000000 /* EDL Mask in DLC */
#घोषणा XCAN_DLCR_BRS_MASK		0x04000000 /* BRS Mask in DLC */

/* CAN रेजिस्टर bit shअगरt - XCAN_<REG>_<BIT>_SHIFT */
#घोषणा XCAN_BTR_SJW_SHIFT		7  /* Synchronous jump width */
#घोषणा XCAN_BTR_TS2_SHIFT		4  /* Time segment 2 */
#घोषणा XCAN_BTR_SJW_SHIFT_CANFD	16 /* Synchronous jump width */
#घोषणा XCAN_BTR_TS2_SHIFT_CANFD	8  /* Time segment 2 */
#घोषणा XCAN_IDR_ID1_SHIFT		21 /* Standard Messg Identअगरier */
#घोषणा XCAN_IDR_ID2_SHIFT		1  /* Extended Message Identअगरier */
#घोषणा XCAN_DLCR_DLC_SHIFT		28 /* Data length code */
#घोषणा XCAN_ESR_REC_SHIFT		8  /* Rx Error Count */

/* CAN frame length स्थिरants */
#घोषणा XCAN_FRAME_MAX_DATA_LEN		8
#घोषणा XCANFD_DW_BYTES			4
#घोषणा XCAN_TIMEOUT			(1 * HZ)

/* TX-FIFO-empty पूर्णांकerrupt available */
#घोषणा XCAN_FLAG_TXFEMP	0x0001
/* RX Match Not Finished पूर्णांकerrupt available */
#घोषणा XCAN_FLAG_RXMNF		0x0002
/* Extended acceptance filters with control at 0xE0 */
#घोषणा XCAN_FLAG_EXT_FILTERS	0x0004
/* TX mailboxes instead of TX FIFO */
#घोषणा XCAN_FLAG_TX_MAILBOXES	0x0008
/* RX FIFO with each buffer in separate रेजिस्टरs at 0x1100
 * instead of the regular FIFO at 0x50
 */
#घोषणा XCAN_FLAG_RX_FIFO_MULTI	0x0010
#घोषणा XCAN_FLAG_CANFD_2	0x0020

क्रमागत xcan_ip_type अणु
	XAXI_CAN = 0,
	XZYNQ_CANPS,
	XAXI_CANFD,
	XAXI_CANFD_2_0,
पूर्ण;

काष्ठा xcan_devtype_data अणु
	क्रमागत xcan_ip_type cantype;
	अचिन्हित पूर्णांक flags;
	स्थिर काष्ठा can_bittiming_स्थिर *bittiming_स्थिर;
	स्थिर अक्षर *bus_clk_name;
	अचिन्हित पूर्णांक btr_ts2_shअगरt;
	अचिन्हित पूर्णांक btr_sjw_shअगरt;
पूर्ण;

/**
 * काष्ठा xcan_priv - This definition define CAN driver instance
 * @can:			CAN निजी data काष्ठाure.
 * @tx_lock:			Lock क्रम synchronizing TX पूर्णांकerrupt handling
 * @tx_head:			Tx CAN packets पढ़ोy to send on the queue
 * @tx_tail:			Tx CAN packets successfully sended on the queue
 * @tx_max:			Maximum number packets the driver can send
 * @napi:			NAPI काष्ठाure
 * @पढ़ो_reg:			For पढ़ोing data from CAN रेजिस्टरs
 * @ग_लिखो_reg:			For writing data to CAN रेजिस्टरs
 * @dev:			Network device data काष्ठाure
 * @reg_base:			Ioremapped address to रेजिस्टरs
 * @irq_flags:			For request_irq()
 * @bus_clk:			Poपूर्णांकer to काष्ठा clk
 * @can_clk:			Poपूर्णांकer to काष्ठा clk
 * @devtype:			Device type specअगरic स्थिरants
 */
काष्ठा xcan_priv अणु
	काष्ठा can_priv can;
	spinlock_t tx_lock; /* Lock क्रम synchronizing TX पूर्णांकerrupt handling */
	अचिन्हित पूर्णांक tx_head;
	अचिन्हित पूर्णांक tx_tail;
	अचिन्हित पूर्णांक tx_max;
	काष्ठा napi_काष्ठा napi;
	u32 (*पढ़ो_reg)(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg);
	व्योम (*ग_लिखो_reg)(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg,
			  u32 val);
	काष्ठा device *dev;
	व्योम __iomem *reg_base;
	अचिन्हित दीर्घ irq_flags;
	काष्ठा clk *bus_clk;
	काष्ठा clk *can_clk;
	काष्ठा xcan_devtype_data devtype;
पूर्ण;

/* CAN Bittiming स्थिरants as per Xilinx CAN specs */
अटल स्थिर काष्ठा can_bittiming_स्थिर xcan_bittiming_स्थिर = अणु
	.name = DRIVER_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/* AXI CANFD Arbitration Bittiming स्थिरants as per AXI CANFD 1.0 spec */
अटल स्थिर काष्ठा can_bittiming_स्थिर xcan_bittiming_स्थिर_canfd = अणु
	.name = DRIVER_NAME,
	.tseg1_min = 1,
	.tseg1_max = 64,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/* AXI CANFD Data Bittiming स्थिरants as per AXI CANFD 1.0 specs */
अटल काष्ठा can_bittiming_स्थिर xcan_data_bittiming_स्थिर_canfd = अणु
	.name = DRIVER_NAME,
	.tseg1_min = 1,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 8,
	.brp_min = 1,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/* AXI CANFD 2.0 Arbitration Bittiming स्थिरants as per AXI CANFD 2.0 spec */
अटल स्थिर काष्ठा can_bittiming_स्थिर xcan_bittiming_स्थिर_canfd2 = अणु
	.name = DRIVER_NAME,
	.tseg1_min = 1,
	.tseg1_max = 256,
	.tseg2_min = 1,
	.tseg2_max = 128,
	.sjw_max = 128,
	.brp_min = 2,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/* AXI CANFD 2.0 Data Bittiming स्थिरants as per AXI CANFD 2.0 spec */
अटल काष्ठा can_bittiming_स्थिर xcan_data_bittiming_स्थिर_canfd2 = अणु
	.name = DRIVER_NAME,
	.tseg1_min = 1,
	.tseg1_max = 32,
	.tseg2_min = 1,
	.tseg2_max = 16,
	.sjw_max = 16,
	.brp_min = 2,
	.brp_max = 256,
	.brp_inc = 1,
पूर्ण;

/**
 * xcan_ग_लिखो_reg_le - Write a value to the device रेजिस्टर little endian
 * @priv:	Driver निजी data काष्ठाure
 * @reg:	Register offset
 * @val:	Value to ग_लिखो at the Register offset
 *
 * Write data to the paricular CAN रेजिस्टर
 */
अटल व्योम xcan_ग_लिखो_reg_le(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg,
			      u32 val)
अणु
	ioग_लिखो32(val, priv->reg_base + reg);
पूर्ण

/**
 * xcan_पढ़ो_reg_le - Read a value from the device रेजिस्टर little endian
 * @priv:	Driver निजी data काष्ठाure
 * @reg:	Register offset
 *
 * Read data from the particular CAN रेजिस्टर
 * Return: value पढ़ो from the CAN रेजिस्टर
 */
अटल u32 xcan_पढ़ो_reg_le(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg)
अणु
	वापस ioपढ़ो32(priv->reg_base + reg);
पूर्ण

/**
 * xcan_ग_लिखो_reg_be - Write a value to the device रेजिस्टर big endian
 * @priv:	Driver निजी data काष्ठाure
 * @reg:	Register offset
 * @val:	Value to ग_लिखो at the Register offset
 *
 * Write data to the paricular CAN रेजिस्टर
 */
अटल व्योम xcan_ग_लिखो_reg_be(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg,
			      u32 val)
अणु
	ioग_लिखो32be(val, priv->reg_base + reg);
पूर्ण

/**
 * xcan_पढ़ो_reg_be - Read a value from the device रेजिस्टर big endian
 * @priv:	Driver निजी data काष्ठाure
 * @reg:	Register offset
 *
 * Read data from the particular CAN रेजिस्टर
 * Return: value पढ़ो from the CAN रेजिस्टर
 */
अटल u32 xcan_पढ़ो_reg_be(स्थिर काष्ठा xcan_priv *priv, क्रमागत xcan_reg reg)
अणु
	वापस ioपढ़ो32be(priv->reg_base + reg);
पूर्ण

/**
 * xcan_rx_पूर्णांक_mask - Get the mask क्रम the receive पूर्णांकerrupt
 * @priv:	Driver निजी data काष्ठाure
 *
 * Return: The receive पूर्णांकerrupt mask used by the driver on this HW
 */
अटल u32 xcan_rx_पूर्णांक_mask(स्थिर काष्ठा xcan_priv *priv)
अणु
	/* RXNEMP is better suited क्रम our use हाल as it cannot be cleared
	 * जबतक the FIFO is non-empty, but CAN FD HW करोes not have it
	 */
	अगर (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI)
		वापस XCAN_IXR_RXOK_MASK;
	अन्यथा
		वापस XCAN_IXR_RXNEMP_MASK;
पूर्ण

/**
 * set_reset_mode - Resets the CAN device mode
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This is the driver reset mode routine.The driver
 * enters पूर्णांकo configuration mode.
 *
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक set_reset_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ समयout;

	priv->ग_लिखो_reg(priv, XCAN_SRR_OFFSET, XCAN_SRR_RESET_MASK);

	समयout = jअगरfies + XCAN_TIMEOUT;
	जबतक (!(priv->पढ़ो_reg(priv, XCAN_SR_OFFSET) & XCAN_SR_CONFIG_MASK)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			netdev_warn(ndev, "timed out for config mode\n");
			वापस -ETIMEDOUT;
		पूर्ण
		usleep_range(500, 10000);
	पूर्ण

	/* reset clears FIFOs */
	priv->tx_head = 0;
	priv->tx_tail = 0;

	वापस 0;
पूर्ण

/**
 * xcan_set_bittiming - CAN set bit timing routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This is the driver set bittiming  routine.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_set_bittiming(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	काष्ठा can_bittiming *bt = &priv->can.bittiming;
	काष्ठा can_bittiming *dbt = &priv->can.data_bittiming;
	u32 btr0, btr1;
	u32 is_config_mode;

	/* Check whether Xilinx CAN is in configuration mode.
	 * It cannot set bit timing अगर Xilinx CAN is not in configuration mode.
	 */
	is_config_mode = priv->पढ़ो_reg(priv, XCAN_SR_OFFSET) &
				XCAN_SR_CONFIG_MASK;
	अगर (!is_config_mode) अणु
		netdev_alert(ndev,
			     "BUG! Cannot set bittiming - CAN is not in config mode\n");
		वापस -EPERM;
	पूर्ण

	/* Setting Baud Rate prescalar value in BRPR Register */
	btr0 = (bt->brp - 1);

	/* Setting Time Segment 1 in BTR Register */
	btr1 = (bt->prop_seg + bt->phase_seg1 - 1);

	/* Setting Time Segment 2 in BTR Register */
	btr1 |= (bt->phase_seg2 - 1) << priv->devtype.btr_ts2_shअगरt;

	/* Setting Synchronous jump width in BTR Register */
	btr1 |= (bt->sjw - 1) << priv->devtype.btr_sjw_shअगरt;

	priv->ग_लिखो_reg(priv, XCAN_BRPR_OFFSET, btr0);
	priv->ग_लिखो_reg(priv, XCAN_BTR_OFFSET, btr1);

	अगर (priv->devtype.cantype == XAXI_CANFD ||
	    priv->devtype.cantype == XAXI_CANFD_2_0) अणु
		/* Setting Baud Rate prescalar value in F_BRPR Register */
		btr0 = dbt->brp - 1;

		/* Setting Time Segment 1 in BTR Register */
		btr1 = dbt->prop_seg + dbt->phase_seg1 - 1;

		/* Setting Time Segment 2 in BTR Register */
		btr1 |= (dbt->phase_seg2 - 1) << priv->devtype.btr_ts2_shअगरt;

		/* Setting Synchronous jump width in BTR Register */
		btr1 |= (dbt->sjw - 1) << priv->devtype.btr_sjw_shअगरt;

		priv->ग_लिखो_reg(priv, XCAN_F_BRPR_OFFSET, btr0);
		priv->ग_लिखो_reg(priv, XCAN_F_BTR_OFFSET, btr1);
	पूर्ण

	netdev_dbg(ndev, "BRPR=0x%08x, BTR=0x%08x\n",
		   priv->पढ़ो_reg(priv, XCAN_BRPR_OFFSET),
		   priv->पढ़ो_reg(priv, XCAN_BTR_OFFSET));

	वापस 0;
पूर्ण

/**
 * xcan_chip_start - This the drivers start routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This is the drivers start routine.
 * Based on the State of the CAN device it माला_दो
 * the CAN device पूर्णांकo a proper mode.
 *
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_chip_start(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	u32 reg_msr;
	पूर्णांक err;
	u32 ier;

	/* Check अगर it is in reset mode */
	err = set_reset_mode(ndev);
	अगर (err < 0)
		वापस err;

	err = xcan_set_bittiming(ndev);
	अगर (err < 0)
		वापस err;

	/* Enable पूर्णांकerrupts
	 *
	 * We enable the ERROR पूर्णांकerrupt even with
	 * CAN_CTRLMODE_BERR_REPORTING disabled as there is no
	 * dedicated पूर्णांकerrupt क्रम a state change to
	 * ERROR_WARNING/ERROR_PASSIVE.
	 */
	ier = XCAN_IXR_TXOK_MASK | XCAN_IXR_BSOFF_MASK |
		XCAN_IXR_WKUP_MASK | XCAN_IXR_SLP_MASK |
		XCAN_IXR_ERROR_MASK | XCAN_IXR_RXOFLW_MASK |
		XCAN_IXR_ARBLST_MASK | xcan_rx_पूर्णांक_mask(priv);

	अगर (priv->devtype.flags & XCAN_FLAG_RXMNF)
		ier |= XCAN_IXR_RXMNF_MASK;

	priv->ग_लिखो_reg(priv, XCAN_IER_OFFSET, ier);

	/* Check whether it is loopback mode or normal mode  */
	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg_msr = XCAN_MSR_LBACK_MASK;
	अन्यथा
		reg_msr = 0x0;

	/* enable the first extended filter, अगर any, as cores with extended
	 * filtering शेष to non-receipt अगर all filters are disabled
	 */
	अगर (priv->devtype.flags & XCAN_FLAG_EXT_FILTERS)
		priv->ग_लिखो_reg(priv, XCAN_AFR_EXT_OFFSET, 0x00000001);

	priv->ग_लिखो_reg(priv, XCAN_MSR_OFFSET, reg_msr);
	priv->ग_लिखो_reg(priv, XCAN_SRR_OFFSET, XCAN_SRR_CEN_MASK);

	netdev_dbg(ndev, "status:#x%08x\n",
		   priv->पढ़ो_reg(priv, XCAN_SR_OFFSET));

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	वापस 0;
पूर्ण

/**
 * xcan_करो_set_mode - This sets the mode of the driver
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @mode:	Tells the mode of the driver
 *
 * This check the drivers state and calls the
 * the corresponding modes to set.
 *
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_करो_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		ret = xcan_chip_start(ndev);
		अगर (ret < 0) अणु
			netdev_err(ndev, "xcan_chip_start failed!\n");
			वापस ret;
		पूर्ण
		netअगर_wake_queue(ndev);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * xcan_ग_लिखो_frame - Write a frame to HW
 * @ndev:		Poपूर्णांकer to net_device काष्ठाure
 * @skb:		sk_buff poपूर्णांकer that contains data to be Txed
 * @frame_offset:	Register offset to ग_लिखो the frame to
 */
अटल व्योम xcan_ग_लिखो_frame(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
			     पूर्णांक frame_offset)
अणु
	u32 id, dlc, data[2] = अणु0, 0पूर्ण;
	काष्ठा canfd_frame *cf = (काष्ठा canfd_frame *)skb->data;
	u32 ramoff, dwindex = 0, i;
	काष्ठा xcan_priv *priv = netdev_priv(ndev);

	/* Watch carefully on the bit sequence */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		/* Extended CAN ID क्रमmat */
		id = ((cf->can_id & CAN_EFF_MASK) << XCAN_IDR_ID2_SHIFT) &
			XCAN_IDR_ID2_MASK;
		id |= (((cf->can_id & CAN_EFF_MASK) >>
			(CAN_EFF_ID_BITS - CAN_SFF_ID_BITS)) <<
			XCAN_IDR_ID1_SHIFT) & XCAN_IDR_ID1_MASK;

		/* The substibute remote TX request bit should be "1"
		 * क्रम extended frames as in the Xilinx CAN datasheet
		 */
		id |= XCAN_IDR_IDE_MASK | XCAN_IDR_SRR_MASK;

		अगर (cf->can_id & CAN_RTR_FLAG)
			/* Extended frames remote TX request */
			id |= XCAN_IDR_RTR_MASK;
	पूर्ण अन्यथा अणु
		/* Standard CAN ID क्रमmat */
		id = ((cf->can_id & CAN_SFF_MASK) << XCAN_IDR_ID1_SHIFT) &
			XCAN_IDR_ID1_MASK;

		अगर (cf->can_id & CAN_RTR_FLAG)
			/* Standard frames remote TX request */
			id |= XCAN_IDR_SRR_MASK;
	पूर्ण

	dlc = can_fd_len2dlc(cf->len) << XCAN_DLCR_DLC_SHIFT;
	अगर (can_is_canfd_skb(skb)) अणु
		अगर (cf->flags & CANFD_BRS)
			dlc |= XCAN_DLCR_BRS_MASK;
		dlc |= XCAN_DLCR_EDL_MASK;
	पूर्ण

	अगर (!(priv->devtype.flags & XCAN_FLAG_TX_MAILBOXES) &&
	    (priv->devtype.flags & XCAN_FLAG_TXFEMP))
		can_put_echo_skb(skb, ndev, priv->tx_head % priv->tx_max, 0);
	अन्यथा
		can_put_echo_skb(skb, ndev, 0, 0);

	priv->tx_head++;

	priv->ग_लिखो_reg(priv, XCAN_FRAME_ID_OFFSET(frame_offset), id);
	/* If the CAN frame is RTR frame this ग_लिखो triggers transmission
	 * (not on CAN FD)
	 */
	priv->ग_लिखो_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_offset), dlc);
	अगर (priv->devtype.cantype == XAXI_CANFD ||
	    priv->devtype.cantype == XAXI_CANFD_2_0) अणु
		क्रम (i = 0; i < cf->len; i += 4) अणु
			ramoff = XCANFD_FRAME_DW_OFFSET(frame_offset) +
					(dwindex * XCANFD_DW_BYTES);
			priv->ग_लिखो_reg(priv, ramoff,
					be32_to_cpup((__be32 *)(cf->data + i)));
			dwindex++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cf->len > 0)
			data[0] = be32_to_cpup((__be32 *)(cf->data + 0));
		अगर (cf->len > 4)
			data[1] = be32_to_cpup((__be32 *)(cf->data + 4));

		अगर (!(cf->can_id & CAN_RTR_FLAG)) अणु
			priv->ग_लिखो_reg(priv,
					XCAN_FRAME_DW1_OFFSET(frame_offset),
					data[0]);
			/* If the CAN frame is Standard/Extended frame this
			 * ग_लिखो triggers transmission (not on CAN FD)
			 */
			priv->ग_लिखो_reg(priv,
					XCAN_FRAME_DW2_OFFSET(frame_offset),
					data[1]);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * xcan_start_xmit_fअगरo - Starts the transmission (FIFO mode)
 * @skb:	sk_buff poपूर्णांकer that contains data to be Txed
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Return: 0 on success, -ENOSPC अगर FIFO is full.
 */
अटल पूर्णांक xcan_start_xmit_fअगरo(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	/* Check अगर the TX buffer is full */
	अगर (unlikely(priv->पढ़ो_reg(priv, XCAN_SR_OFFSET) &
			XCAN_SR_TXFLL_MASK))
		वापस -ENOSPC;

	spin_lock_irqsave(&priv->tx_lock, flags);

	xcan_ग_लिखो_frame(ndev, skb, XCAN_TXFIFO_OFFSET);

	/* Clear TX-FIFO-empty पूर्णांकerrupt क्रम xcan_tx_पूर्णांकerrupt() */
	अगर (priv->tx_max > 1)
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXFEMP_MASK);

	/* Check अगर the TX buffer is full */
	अगर ((priv->tx_head - priv->tx_tail) == priv->tx_max)
		netअगर_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	वापस 0;
पूर्ण

/**
 * xcan_start_xmit_mailbox - Starts the transmission (mailbox mode)
 * @skb:	sk_buff poपूर्णांकer that contains data to be Txed
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Return: 0 on success, -ENOSPC अगर there is no space
 */
अटल पूर्णांक xcan_start_xmit_mailbox(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	अचिन्हित दीर्घ flags;

	अगर (unlikely(priv->पढ़ो_reg(priv, XCAN_TRR_OFFSET) &
		     BIT(XCAN_TX_MAILBOX_IDX)))
		वापस -ENOSPC;

	spin_lock_irqsave(&priv->tx_lock, flags);

	xcan_ग_लिखो_frame(ndev, skb,
			 XCAN_TXMSG_FRAME_OFFSET(XCAN_TX_MAILBOX_IDX));

	/* Mark buffer as पढ़ोy क्रम transmit */
	priv->ग_लिखो_reg(priv, XCAN_TRR_OFFSET, BIT(XCAN_TX_MAILBOX_IDX));

	netअगर_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	वापस 0;
पूर्ण

/**
 * xcan_start_xmit - Starts the transmission
 * @skb:	sk_buff poपूर्णांकer that contains data to be Txed
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This function is invoked from upper layers to initiate transmission.
 *
 * Return: NETDEV_TX_OK on success and NETDEV_TX_BUSY when the tx queue is full
 */
अटल netdev_tx_t xcan_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	अगर (priv->devtype.flags & XCAN_FLAG_TX_MAILBOXES)
		ret = xcan_start_xmit_mailbox(skb, ndev);
	अन्यथा
		ret = xcan_start_xmit_fअगरo(skb, ndev);

	अगर (ret < 0) अणु
		netdev_err(ndev, "BUG!, TX full when queue awake!\n");
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * xcan_rx -  Is called from CAN isr to complete the received
 *		frame  processing
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @frame_base:	Register offset to the frame to be पढ़ो
 *
 * This function is invoked from the CAN isr(poll) to process the Rx frames. It
 * करोes minimal processing and invokes "netif_receive_skb" to complete further
 * processing.
 * Return: 1 on success and 0 on failure.
 */
अटल पूर्णांक xcan_rx(काष्ठा net_device *ndev, पूर्णांक frame_base)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame *cf;
	काष्ठा sk_buff *skb;
	u32 id_xcan, dlc, data[2] = अणु0, 0पूर्ण;

	skb = alloc_can_skb(ndev, &cf);
	अगर (unlikely(!skb)) अणु
		stats->rx_dropped++;
		वापस 0;
	पूर्ण

	/* Read a frame from Xilinx zynq CANPS */
	id_xcan = priv->पढ़ो_reg(priv, XCAN_FRAME_ID_OFFSET(frame_base));
	dlc = priv->पढ़ो_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_base)) >>
				   XCAN_DLCR_DLC_SHIFT;

	/* Change Xilinx CAN data length क्रमmat to socketCAN data क्रमmat */
	cf->len = can_cc_dlc2len(dlc);

	/* Change Xilinx CAN ID क्रमmat to socketCAN ID क्रमmat */
	अगर (id_xcan & XCAN_IDR_IDE_MASK) अणु
		/* The received frame is an Extended क्रमmat frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >> 3;
		cf->can_id |= (id_xcan & XCAN_IDR_ID2_MASK) >>
				XCAN_IDR_ID2_SHIFT;
		cf->can_id |= CAN_EFF_FLAG;
		अगर (id_xcan & XCAN_IDR_RTR_MASK)
			cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		/* The received frame is a standard क्रमmat frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >>
				XCAN_IDR_ID1_SHIFT;
		अगर (id_xcan & XCAN_IDR_SRR_MASK)
			cf->can_id |= CAN_RTR_FLAG;
	पूर्ण

	/* DW1/DW2 must always be पढ़ो to हटाओ message from RXFIFO */
	data[0] = priv->पढ़ो_reg(priv, XCAN_FRAME_DW1_OFFSET(frame_base));
	data[1] = priv->पढ़ो_reg(priv, XCAN_FRAME_DW2_OFFSET(frame_base));

	अगर (!(cf->can_id & CAN_RTR_FLAG)) अणु
		/* Change Xilinx CAN data क्रमmat to socketCAN data क्रमmat */
		अगर (cf->len > 0)
			*(__be32 *)(cf->data) = cpu_to_be32(data[0]);
		अगर (cf->len > 4)
			*(__be32 *)(cf->data + 4) = cpu_to_be32(data[1]);
	पूर्ण

	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

/**
 * xcanfd_rx -  Is called from CAN isr to complete the received
 *		frame  processing
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @frame_base:	Register offset to the frame to be पढ़ो
 *
 * This function is invoked from the CAN isr(poll) to process the Rx frames. It
 * करोes minimal processing and invokes "netif_receive_skb" to complete further
 * processing.
 * Return: 1 on success and 0 on failure.
 */
अटल पूर्णांक xcanfd_rx(काष्ठा net_device *ndev, पूर्णांक frame_base)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा canfd_frame *cf;
	काष्ठा sk_buff *skb;
	u32 id_xcan, dlc, data[2] = अणु0, 0पूर्ण, dwindex = 0, i, dw_offset;

	id_xcan = priv->पढ़ो_reg(priv, XCAN_FRAME_ID_OFFSET(frame_base));
	dlc = priv->पढ़ो_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_base));
	अगर (dlc & XCAN_DLCR_EDL_MASK)
		skb = alloc_canfd_skb(ndev, &cf);
	अन्यथा
		skb = alloc_can_skb(ndev, (काष्ठा can_frame **)&cf);

	अगर (unlikely(!skb)) अणु
		stats->rx_dropped++;
		वापस 0;
	पूर्ण

	/* Change Xilinx CANFD data length क्रमmat to socketCAN data
	 * क्रमmat
	 */
	अगर (dlc & XCAN_DLCR_EDL_MASK)
		cf->len = can_fd_dlc2len((dlc & XCAN_DLCR_DLC_MASK) >>
				  XCAN_DLCR_DLC_SHIFT);
	अन्यथा
		cf->len = can_cc_dlc2len((dlc & XCAN_DLCR_DLC_MASK) >>
					  XCAN_DLCR_DLC_SHIFT);

	/* Change Xilinx CAN ID क्रमmat to socketCAN ID क्रमmat */
	अगर (id_xcan & XCAN_IDR_IDE_MASK) अणु
		/* The received frame is an Extended क्रमmat frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >> 3;
		cf->can_id |= (id_xcan & XCAN_IDR_ID2_MASK) >>
				XCAN_IDR_ID2_SHIFT;
		cf->can_id |= CAN_EFF_FLAG;
		अगर (id_xcan & XCAN_IDR_RTR_MASK)
			cf->can_id |= CAN_RTR_FLAG;
	पूर्ण अन्यथा अणु
		/* The received frame is a standard क्रमmat frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >>
				XCAN_IDR_ID1_SHIFT;
		अगर (!(dlc & XCAN_DLCR_EDL_MASK) && (id_xcan &
					XCAN_IDR_SRR_MASK))
			cf->can_id |= CAN_RTR_FLAG;
	पूर्ण

	/* Check the frame received is FD or not*/
	अगर (dlc & XCAN_DLCR_EDL_MASK) अणु
		क्रम (i = 0; i < cf->len; i += 4) अणु
			dw_offset = XCANFD_FRAME_DW_OFFSET(frame_base) +
					(dwindex * XCANFD_DW_BYTES);
			data[0] = priv->पढ़ो_reg(priv, dw_offset);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
			dwindex++;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < cf->len; i += 4) अणु
			dw_offset = XCANFD_FRAME_DW_OFFSET(frame_base);
			data[0] = priv->पढ़ो_reg(priv, dw_offset + i);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
		पूर्ण
	पूर्ण
	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netअगर_receive_skb(skb);

	वापस 1;
पूर्ण

/**
 * xcan_current_error_state - Get current error state from HW
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Checks the current CAN error state from the HW. Note that this
 * only checks क्रम ERROR_PASSIVE and ERROR_WARNING.
 *
 * Return:
 * ERROR_PASSIVE or ERROR_WARNING अगर either is active, ERROR_ACTIVE
 * otherwise.
 */
अटल क्रमागत can_state xcan_current_error_state(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	u32 status = priv->पढ़ो_reg(priv, XCAN_SR_OFFSET);

	अगर ((status & XCAN_SR_ESTAT_MASK) == XCAN_SR_ESTAT_MASK)
		वापस CAN_STATE_ERROR_PASSIVE;
	अन्यथा अगर (status & XCAN_SR_ERRWRN_MASK)
		वापस CAN_STATE_ERROR_WARNING;
	अन्यथा
		वापस CAN_STATE_ERROR_ACTIVE;
पूर्ण

/**
 * xcan_set_error_state - Set new CAN error state
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @new_state:	The new CAN state to be set
 * @cf:		Error frame to be populated or शून्य
 *
 * Set new CAN error state क्रम the device, updating statistics and
 * populating the error frame अगर given.
 */
अटल व्योम xcan_set_error_state(काष्ठा net_device *ndev,
				 क्रमागत can_state new_state,
				 काष्ठा can_frame *cf)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	u32 ecr = priv->पढ़ो_reg(priv, XCAN_ECR_OFFSET);
	u32 txerr = ecr & XCAN_ECR_TEC_MASK;
	u32 rxerr = (ecr & XCAN_ECR_REC_MASK) >> XCAN_ESR_REC_SHIFT;
	क्रमागत can_state tx_state = txerr >= rxerr ? new_state : 0;
	क्रमागत can_state rx_state = txerr <= rxerr ? new_state : 0;

	/* non-ERROR states are handled अन्यथाwhere */
	अगर (WARN_ON(new_state > CAN_STATE_ERROR_PASSIVE))
		वापस;

	can_change_state(ndev, cf, tx_state, rx_state);

	अगर (cf) अणु
		cf->data[6] = txerr;
		cf->data[7] = rxerr;
	पूर्ण
पूर्ण

/**
 * xcan_update_error_state_after_rxtx - Update CAN error state after RX/TX
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * If the device is in a ERROR-WARNING or ERROR-PASSIVE state, check अगर
 * the perक्रमmed RX/TX has caused it to drop to a lesser state and set
 * the पूर्णांकerface state accordingly.
 */
अटल व्योम xcan_update_error_state_after_rxtx(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	क्रमागत can_state old_state = priv->can.state;
	क्रमागत can_state new_state;

	/* changing error state due to successful frame RX/TX can only
	 * occur from these states
	 */
	अगर (old_state != CAN_STATE_ERROR_WARNING &&
	    old_state != CAN_STATE_ERROR_PASSIVE)
		वापस;

	new_state = xcan_current_error_state(ndev);

	अगर (new_state != old_state) अणु
		काष्ठा sk_buff *skb;
		काष्ठा can_frame *cf;

		skb = alloc_can_err_skb(ndev, &cf);

		xcan_set_error_state(ndev, new_state, skb ? cf : शून्य);

		अगर (skb) अणु
			काष्ठा net_device_stats *stats = &ndev->stats;

			stats->rx_packets++;
			stats->rx_bytes += cf->len;
			netअगर_rx(skb);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * xcan_err_पूर्णांकerrupt - error frame Isr
 * @ndev:	net_device poपूर्णांकer
 * @isr:	पूर्णांकerrupt status रेजिस्टर value
 *
 * This is the CAN error पूर्णांकerrupt and it will
 * check the the type of error and क्रमward the error
 * frame to upper layers.
 */
अटल व्योम xcan_err_पूर्णांकerrupt(काष्ठा net_device *ndev, u32 isr)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा can_frame cf = अणु पूर्ण;
	u32 err_status;

	err_status = priv->पढ़ो_reg(priv, XCAN_ESR_OFFSET);
	priv->ग_लिखो_reg(priv, XCAN_ESR_OFFSET, err_status);

	अगर (isr & XCAN_IXR_BSOFF_MASK) अणु
		priv->can.state = CAN_STATE_BUS_OFF;
		priv->can.can_stats.bus_off++;
		/* Leave device in Config Mode in bus-off state */
		priv->ग_लिखो_reg(priv, XCAN_SRR_OFFSET, XCAN_SRR_RESET_MASK);
		can_bus_off(ndev);
		cf.can_id |= CAN_ERR_BUSOFF;
	पूर्ण अन्यथा अणु
		क्रमागत can_state new_state = xcan_current_error_state(ndev);

		अगर (new_state != priv->can.state)
			xcan_set_error_state(ndev, new_state, &cf);
	पूर्ण

	/* Check क्रम Arbitration lost पूर्णांकerrupt */
	अगर (isr & XCAN_IXR_ARBLST_MASK) अणु
		priv->can.can_stats.arbitration_lost++;
		cf.can_id |= CAN_ERR_LOSTARB;
		cf.data[0] = CAN_ERR_LOSTARB_UNSPEC;
	पूर्ण

	/* Check क्रम RX FIFO Overflow पूर्णांकerrupt */
	अगर (isr & XCAN_IXR_RXOFLW_MASK) अणु
		stats->rx_over_errors++;
		stats->rx_errors++;
		cf.can_id |= CAN_ERR_CRTL;
		cf.data[1] |= CAN_ERR_CRTL_RX_OVERFLOW;
	पूर्ण

	/* Check क्रम RX Match Not Finished पूर्णांकerrupt */
	अगर (isr & XCAN_IXR_RXMNF_MASK) अणु
		stats->rx_dropped++;
		stats->rx_errors++;
		netdev_err(ndev, "RX match not finished, frame discarded\n");
		cf.can_id |= CAN_ERR_CRTL;
		cf.data[1] |= CAN_ERR_CRTL_UNSPEC;
	पूर्ण

	/* Check क्रम error पूर्णांकerrupt */
	अगर (isr & XCAN_IXR_ERROR_MASK) अणु
		bool berr_reporting = false;

		अगर (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING) अणु
			berr_reporting = true;
			cf.can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;
		पूर्ण

		/* Check क्रम Ack error पूर्णांकerrupt */
		अगर (err_status & XCAN_ESR_ACKER_MASK) अणु
			stats->tx_errors++;
			अगर (berr_reporting) अणु
				cf.can_id |= CAN_ERR_ACK;
				cf.data[3] = CAN_ERR_PROT_LOC_ACK;
			पूर्ण
		पूर्ण

		/* Check क्रम Bit error पूर्णांकerrupt */
		अगर (err_status & XCAN_ESR_BERR_MASK) अणु
			stats->tx_errors++;
			अगर (berr_reporting) अणु
				cf.can_id |= CAN_ERR_PROT;
				cf.data[2] = CAN_ERR_PROT_BIT;
			पूर्ण
		पूर्ण

		/* Check क्रम Stuff error पूर्णांकerrupt */
		अगर (err_status & XCAN_ESR_STER_MASK) अणु
			stats->rx_errors++;
			अगर (berr_reporting) अणु
				cf.can_id |= CAN_ERR_PROT;
				cf.data[2] = CAN_ERR_PROT_STUFF;
			पूर्ण
		पूर्ण

		/* Check क्रम Form error पूर्णांकerrupt */
		अगर (err_status & XCAN_ESR_FMER_MASK) अणु
			stats->rx_errors++;
			अगर (berr_reporting) अणु
				cf.can_id |= CAN_ERR_PROT;
				cf.data[2] = CAN_ERR_PROT_FORM;
			पूर्ण
		पूर्ण

		/* Check क्रम CRC error पूर्णांकerrupt */
		अगर (err_status & XCAN_ESR_CRCER_MASK) अणु
			stats->rx_errors++;
			अगर (berr_reporting) अणु
				cf.can_id |= CAN_ERR_PROT;
				cf.data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
			पूर्ण
		पूर्ण
		priv->can.can_stats.bus_error++;
	पूर्ण

	अगर (cf.can_id) अणु
		काष्ठा can_frame *skb_cf;
		काष्ठा sk_buff *skb = alloc_can_err_skb(ndev, &skb_cf);

		अगर (skb) अणु
			skb_cf->can_id |= cf.can_id;
			स_नकल(skb_cf->data, cf.data, CAN_ERR_DLC);
			stats->rx_packets++;
			stats->rx_bytes += CAN_ERR_DLC;
			netअगर_rx(skb);
		पूर्ण
	पूर्ण

	netdev_dbg(ndev, "%s: error status register:0x%x\n",
		   __func__, priv->पढ़ो_reg(priv, XCAN_ESR_OFFSET));
पूर्ण

/**
 * xcan_state_पूर्णांकerrupt - It will check the state of the CAN device
 * @ndev:	net_device poपूर्णांकer
 * @isr:	पूर्णांकerrupt status रेजिस्टर value
 *
 * This will checks the state of the CAN device
 * and माला_दो the device पूर्णांकo appropriate state.
 */
अटल व्योम xcan_state_पूर्णांकerrupt(काष्ठा net_device *ndev, u32 isr)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);

	/* Check क्रम Sleep पूर्णांकerrupt अगर set put CAN device in sleep state */
	अगर (isr & XCAN_IXR_SLP_MASK)
		priv->can.state = CAN_STATE_SLEEPING;

	/* Check क्रम Wake up पूर्णांकerrupt अगर set put CAN device in Active state */
	अगर (isr & XCAN_IXR_WKUP_MASK)
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
पूर्ण

/**
 * xcan_rx_fअगरo_get_next_frame - Get रेजिस्टर offset of next RX frame
 * @priv:	Driver निजी data काष्ठाure
 *
 * Return: Register offset of the next frame in RX FIFO.
 */
अटल पूर्णांक xcan_rx_fअगरo_get_next_frame(काष्ठा xcan_priv *priv)
अणु
	पूर्णांक offset;

	अगर (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI) अणु
		u32 fsr, mask;

		/* clear RXOK beक्रमe the is-empty check so that any newly
		 * received frame will reनिश्चित it without a race
		 */
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_RXOK_MASK);

		fsr = priv->पढ़ो_reg(priv, XCAN_FSR_OFFSET);

		/* check अगर RX FIFO is empty */
		अगर (priv->devtype.flags & XCAN_FLAG_CANFD_2)
			mask = XCAN_2_FSR_FL_MASK;
		अन्यथा
			mask = XCAN_FSR_FL_MASK;

		अगर (!(fsr & mask))
			वापस -ENOENT;

		अगर (priv->devtype.flags & XCAN_FLAG_CANFD_2)
			offset =
			  XCAN_RXMSG_2_FRAME_OFFSET(fsr & XCAN_2_FSR_RI_MASK);
		अन्यथा
			offset =
			  XCAN_RXMSG_FRAME_OFFSET(fsr & XCAN_FSR_RI_MASK);

	पूर्ण अन्यथा अणु
		/* check अगर RX FIFO is empty */
		अगर (!(priv->पढ़ो_reg(priv, XCAN_ISR_OFFSET) &
		      XCAN_IXR_RXNEMP_MASK))
			वापस -ENOENT;

		/* frames are पढ़ो from a अटल offset */
		offset = XCAN_RXFIFO_OFFSET;
	पूर्ण

	वापस offset;
पूर्ण

/**
 * xcan_rx_poll - Poll routine क्रम rx packets (NAPI)
 * @napi:	napi काष्ठाure poपूर्णांकer
 * @quota:	Max number of rx packets to be processed.
 *
 * This is the poll routine क्रम rx part.
 * It will process the packets maximux quota value.
 *
 * Return: number of packets received
 */
अटल पूर्णांक xcan_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	u32 ier;
	पूर्णांक work_करोne = 0;
	पूर्णांक frame_offset;

	जबतक ((frame_offset = xcan_rx_fअगरo_get_next_frame(priv)) >= 0 &&
	       (work_करोne < quota)) अणु
		अगर (xcan_rx_पूर्णांक_mask(priv) & XCAN_IXR_RXOK_MASK)
			work_करोne += xcanfd_rx(ndev, frame_offset);
		अन्यथा
			work_करोne += xcan_rx(ndev, frame_offset);

		अगर (priv->devtype.flags & XCAN_FLAG_RX_FIFO_MULTI)
			/* increment पढ़ो index */
			priv->ग_लिखो_reg(priv, XCAN_FSR_OFFSET,
					XCAN_FSR_IRI_MASK);
		अन्यथा
			/* clear rx-not-empty (will actually clear only अगर
			 * empty)
			 */
			priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET,
					XCAN_IXR_RXNEMP_MASK);
	पूर्ण

	अगर (work_करोne) अणु
		can_led_event(ndev, CAN_LED_EVENT_RX);
		xcan_update_error_state_after_rxtx(ndev);
	पूर्ण

	अगर (work_करोne < quota) अणु
		napi_complete_करोne(napi, work_करोne);
		ier = priv->पढ़ो_reg(priv, XCAN_IER_OFFSET);
		ier |= xcan_rx_पूर्णांक_mask(priv);
		priv->ग_लिखो_reg(priv, XCAN_IER_OFFSET, ier);
	पूर्ण
	वापस work_करोne;
पूर्ण

/**
 * xcan_tx_पूर्णांकerrupt - Tx Done Isr
 * @ndev:	net_device poपूर्णांकer
 * @isr:	Interrupt status रेजिस्टर value
 */
अटल व्योम xcan_tx_पूर्णांकerrupt(काष्ठा net_device *ndev, u32 isr)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित पूर्णांक frames_in_fअगरo;
	पूर्णांक frames_sent = 1; /* TXOK => at least 1 frame was sent */
	अचिन्हित दीर्घ flags;
	पूर्णांक retries = 0;

	/* Synchronize with xmit as we need to know the exact number
	 * of frames in the FIFO to stay in sync due to the TXFEMP
	 * handling.
	 * This also prevents a race between netअगर_wake_queue() and
	 * netअगर_stop_queue().
	 */
	spin_lock_irqsave(&priv->tx_lock, flags);

	frames_in_fअगरo = priv->tx_head - priv->tx_tail;

	अगर (WARN_ON_ONCE(frames_in_fअगरo == 0)) अणु
		/* clear TXOK anyway to aव्योम getting back here */
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXOK_MASK);
		spin_unlock_irqrestore(&priv->tx_lock, flags);
		वापस;
	पूर्ण

	/* Check अगर 2 frames were sent (TXOK only means that at least 1
	 * frame was sent).
	 */
	अगर (frames_in_fअगरo > 1) अणु
		WARN_ON(frames_in_fअगरo > priv->tx_max);

		/* Synchronize TXOK and isr so that after the loop:
		 * (1) isr variable is up-to-date at least up to TXOK clear
		 *     समय. This aव्योमs us clearing a TXOK of a second frame
		 *     but not noticing that the FIFO is now empty and thus
		 *     marking only a single frame as sent.
		 * (2) No TXOK is left. Having one could mean leaving a
		 *     stray TXOK as we might process the associated frame
		 *     via TXFEMP handling as we पढ़ो TXFEMP *after* TXOK
		 *     clear to satisfy (1).
		 */
		जबतक ((isr & XCAN_IXR_TXOK_MASK) &&
		       !WARN_ON(++retries == 100)) अणु
			priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET,
					XCAN_IXR_TXOK_MASK);
			isr = priv->पढ़ो_reg(priv, XCAN_ISR_OFFSET);
		पूर्ण

		अगर (isr & XCAN_IXR_TXFEMP_MASK) अणु
			/* nothing in FIFO anymore */
			frames_sent = frames_in_fअगरo;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* single frame in fअगरo, just clear TXOK */
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXOK_MASK);
	पूर्ण

	जबतक (frames_sent--) अणु
		stats->tx_bytes += can_get_echo_skb(ndev, priv->tx_tail %
						    priv->tx_max, शून्य);
		priv->tx_tail++;
		stats->tx_packets++;
	पूर्ण

	netअगर_wake_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	can_led_event(ndev, CAN_LED_EVENT_TX);
	xcan_update_error_state_after_rxtx(ndev);
पूर्ण

/**
 * xcan_पूर्णांकerrupt - CAN Isr
 * @irq:	irq number
 * @dev_id:	device id poपूर्णांकer
 *
 * This is the xilinx CAN Isr. It checks क्रम the type of पूर्णांकerrupt
 * and invokes the corresponding ISR.
 *
 * Return:
 * IRQ_NONE - If CAN device is in sleep mode, IRQ_HANDLED otherwise
 */
अटल irqवापस_t xcan_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	u32 isr, ier;
	u32 isr_errors;
	u32 rx_पूर्णांक_mask = xcan_rx_पूर्णांक_mask(priv);

	/* Get the पूर्णांकerrupt status from Xilinx CAN */
	isr = priv->पढ़ो_reg(priv, XCAN_ISR_OFFSET);
	अगर (!isr)
		वापस IRQ_NONE;

	/* Check क्रम the type of पूर्णांकerrupt and Processing it */
	अगर (isr & (XCAN_IXR_SLP_MASK | XCAN_IXR_WKUP_MASK)) अणु
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, (XCAN_IXR_SLP_MASK |
				XCAN_IXR_WKUP_MASK));
		xcan_state_पूर्णांकerrupt(ndev, isr);
	पूर्ण

	/* Check क्रम Tx पूर्णांकerrupt and Processing it */
	अगर (isr & XCAN_IXR_TXOK_MASK)
		xcan_tx_पूर्णांकerrupt(ndev, isr);

	/* Check क्रम the type of error पूर्णांकerrupt and Processing it */
	isr_errors = isr & (XCAN_IXR_ERROR_MASK | XCAN_IXR_RXOFLW_MASK |
			    XCAN_IXR_BSOFF_MASK | XCAN_IXR_ARBLST_MASK |
			    XCAN_IXR_RXMNF_MASK);
	अगर (isr_errors) अणु
		priv->ग_लिखो_reg(priv, XCAN_ICR_OFFSET, isr_errors);
		xcan_err_पूर्णांकerrupt(ndev, isr);
	पूर्ण

	/* Check क्रम the type of receive पूर्णांकerrupt and Processing it */
	अगर (isr & rx_पूर्णांक_mask) अणु
		ier = priv->पढ़ो_reg(priv, XCAN_IER_OFFSET);
		ier &= ~rx_पूर्णांक_mask;
		priv->ग_लिखो_reg(priv, XCAN_IER_OFFSET, ier);
		napi_schedule(&priv->napi);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * xcan_chip_stop - Driver stop routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This is the drivers stop routine. It will disable the
 * पूर्णांकerrupts and put the device पूर्णांकo configuration mode.
 */
अटल व्योम xcan_chip_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	/* Disable पूर्णांकerrupts and leave the can in configuration mode */
	ret = set_reset_mode(ndev);
	अगर (ret < 0)
		netdev_dbg(ndev, "set_reset_mode() Failed\n");

	priv->can.state = CAN_STATE_STOPPED;
पूर्ण

/**
 * xcan_खोलो - Driver खोलो routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * This is the driver खोलो routine.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "%s: pm_runtime_get failed(%d)\n",
			   __func__, ret);
		जाओ err;
	पूर्ण

	ret = request_irq(ndev->irq, xcan_पूर्णांकerrupt, priv->irq_flags,
			  ndev->name, ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "irq allocation for CAN failed\n");
		जाओ err;
	पूर्ण

	/* Set chip पूर्णांकo reset mode */
	ret = set_reset_mode(ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "mode resetting failed!\n");
		जाओ err_irq;
	पूर्ण

	/* Common खोलो */
	ret = खोलो_candev(ndev);
	अगर (ret)
		जाओ err_irq;

	ret = xcan_chip_start(ndev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "xcan_chip_start failed!\n");
		जाओ err_candev;
	पूर्ण

	can_led_event(ndev, CAN_LED_EVENT_OPEN);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);

	वापस 0;

err_candev:
	बंद_candev(ndev);
err_irq:
	मुक्त_irq(ndev->irq, ndev);
err:
	pm_runसमय_put(priv->dev);

	वापस ret;
पूर्ण

/**
 * xcan_बंद - Driver बंद routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 *
 * Return: 0 always
 */
अटल पूर्णांक xcan_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);
	xcan_chip_stop(ndev);
	मुक्त_irq(ndev->irq, ndev);
	बंद_candev(ndev);

	can_led_event(ndev, CAN_LED_EVENT_STOP);
	pm_runसमय_put(priv->dev);

	वापस 0;
पूर्ण

/**
 * xcan_get_berr_counter - error counter routine
 * @ndev:	Poपूर्णांकer to net_device काष्ठाure
 * @bec:	Poपूर्णांकer to can_berr_counter काष्ठाure
 *
 * This is the driver error counter routine.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_get_berr_counter(स्थिर काष्ठा net_device *ndev,
				 काष्ठा can_berr_counter *bec)
अणु
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(priv->dev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "%s: pm_runtime_get failed(%d)\n",
			   __func__, ret);
		pm_runसमय_put(priv->dev);
		वापस ret;
	पूर्ण

	bec->txerr = priv->पढ़ो_reg(priv, XCAN_ECR_OFFSET) & XCAN_ECR_TEC_MASK;
	bec->rxerr = ((priv->पढ़ो_reg(priv, XCAN_ECR_OFFSET) &
			XCAN_ECR_REC_MASK) >> XCAN_ESR_REC_SHIFT);

	pm_runसमय_put(priv->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops xcan_netdev_ops = अणु
	.nकरो_खोलो	= xcan_खोलो,
	.nकरो_stop	= xcan_बंद,
	.nकरो_start_xmit	= xcan_start_xmit,
	.nकरो_change_mtu	= can_change_mtu,
पूर्ण;

/**
 * xcan_suspend - Suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक __maybe_unused xcan_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);

	अगर (netअगर_running(ndev)) अणु
		netअगर_stop_queue(ndev);
		netअगर_device_detach(ndev);
		xcan_chip_stop(ndev);
	पूर्ण

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

/**
 * xcan_resume - Resume from suspend
 * @dev:	Address of the device काष्ठाure
 *
 * Resume operation after suspend.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक __maybe_unused xcan_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret) अणु
		dev_err(dev, "pm_runtime_force_resume failed on resume\n");
		वापस ret;
	पूर्ण

	अगर (netअगर_running(ndev)) अणु
		ret = xcan_chip_start(ndev);
		अगर (ret) अणु
			dev_err(dev, "xcan_chip_start failed on resume\n");
			वापस ret;
		पूर्ण

		netअगर_device_attach(ndev);
		netअगर_start_queue(ndev);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xcan_runसमय_suspend - Runसमय suspend method क्रम the driver
 * @dev:	Address of the device काष्ठाure
 *
 * Put the driver पूर्णांकo low घातer mode.
 * Return: 0 always
 */
अटल पूर्णांक __maybe_unused xcan_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा xcan_priv *priv = netdev_priv(ndev);

	clk_disable_unprepare(priv->bus_clk);
	clk_disable_unprepare(priv->can_clk);

	वापस 0;
पूर्ण

/**
 * xcan_runसमय_resume - Runसमय resume from suspend
 * @dev:	Address of the device काष्ठाure
 *
 * Resume operation after suspend.
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक __maybe_unused xcan_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा xcan_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->bus_clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable clock.\n");
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(priv->can_clk);
	अगर (ret) अणु
		dev_err(dev, "Cannot enable clock.\n");
		clk_disable_unprepare(priv->bus_clk);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops xcan_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(xcan_suspend, xcan_resume)
	SET_RUNTIME_PM_OPS(xcan_runसमय_suspend, xcan_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा xcan_devtype_data xcan_zynq_data = अणु
	.cantype = XZYNQ_CANPS,
	.flags = XCAN_FLAG_TXFEMP,
	.bittiming_स्थिर = &xcan_bittiming_स्थिर,
	.btr_ts2_shअगरt = XCAN_BTR_TS2_SHIFT,
	.btr_sjw_shअगरt = XCAN_BTR_SJW_SHIFT,
	.bus_clk_name = "pclk",
पूर्ण;

अटल स्थिर काष्ठा xcan_devtype_data xcan_axi_data = अणु
	.cantype = XAXI_CAN,
	.bittiming_स्थिर = &xcan_bittiming_स्थिर,
	.btr_ts2_shअगरt = XCAN_BTR_TS2_SHIFT,
	.btr_sjw_shअगरt = XCAN_BTR_SJW_SHIFT,
	.bus_clk_name = "s_axi_aclk",
पूर्ण;

अटल स्थिर काष्ठा xcan_devtype_data xcan_canfd_data = अणु
	.cantype = XAXI_CANFD,
	.flags = XCAN_FLAG_EXT_FILTERS |
		 XCAN_FLAG_RXMNF |
		 XCAN_FLAG_TX_MAILBOXES |
		 XCAN_FLAG_RX_FIFO_MULTI,
	.bittiming_स्थिर = &xcan_bittiming_स्थिर_canfd,
	.btr_ts2_shअगरt = XCAN_BTR_TS2_SHIFT_CANFD,
	.btr_sjw_shअगरt = XCAN_BTR_SJW_SHIFT_CANFD,
	.bus_clk_name = "s_axi_aclk",
पूर्ण;

अटल स्थिर काष्ठा xcan_devtype_data xcan_canfd2_data = अणु
	.cantype = XAXI_CANFD_2_0,
	.flags = XCAN_FLAG_EXT_FILTERS |
		 XCAN_FLAG_RXMNF |
		 XCAN_FLAG_TX_MAILBOXES |
		 XCAN_FLAG_CANFD_2 |
		 XCAN_FLAG_RX_FIFO_MULTI,
	.bittiming_स्थिर = &xcan_bittiming_स्थिर_canfd2,
	.btr_ts2_shअगरt = XCAN_BTR_TS2_SHIFT_CANFD,
	.btr_sjw_shअगरt = XCAN_BTR_SJW_SHIFT_CANFD,
	.bus_clk_name = "s_axi_aclk",
पूर्ण;

/* Match table क्रम OF platक्रमm binding */
अटल स्थिर काष्ठा of_device_id xcan_of_match[] = अणु
	अणु .compatible = "xlnx,zynq-can-1.0", .data = &xcan_zynq_data पूर्ण,
	अणु .compatible = "xlnx,axi-can-1.00.a", .data = &xcan_axi_data पूर्ण,
	अणु .compatible = "xlnx,canfd-1.0", .data = &xcan_canfd_data पूर्ण,
	अणु .compatible = "xlnx,canfd-2.0", .data = &xcan_canfd2_data पूर्ण,
	अणु /* end of list */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xcan_of_match);

/**
 * xcan_probe - Platक्रमm registration call
 * @pdev:	Handle to the platक्रमm device काष्ठाure
 *
 * This function करोes all the memory allocation and registration क्रम the CAN
 * device.
 *
 * Return: 0 on success and failure value on error
 */
अटल पूर्णांक xcan_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा xcan_priv *priv;
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा xcan_devtype_data *devtype = &xcan_axi_data;
	व्योम __iomem *addr;
	पूर्णांक ret;
	पूर्णांक rx_max, tx_max;
	u32 hw_tx_max = 0, hw_rx_max = 0;
	स्थिर अक्षर *hw_tx_max_property;

	/* Get the भव base address क्रम the device */
	addr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(addr)) अणु
		ret = PTR_ERR(addr);
		जाओ err;
	पूर्ण

	of_id = of_match_device(xcan_of_match, &pdev->dev);
	अगर (of_id && of_id->data)
		devtype = of_id->data;

	hw_tx_max_property = devtype->flags & XCAN_FLAG_TX_MAILBOXES ?
			     "tx-mailbox-count" : "tx-fifo-depth";

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, hw_tx_max_property,
				   &hw_tx_max);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "missing %s property\n",
			hw_tx_max_property);
		जाओ err;
	पूर्ण

	ret = of_property_पढ़ो_u32(pdev->dev.of_node, "rx-fifo-depth",
				   &hw_rx_max);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"missing rx-fifo-depth property (mailbox mode is not supported)\n");
		जाओ err;
	पूर्ण

	/* With TX FIFO:
	 *
	 * There is no way to directly figure out how many frames have been
	 * sent when the TXOK पूर्णांकerrupt is processed. If TXFEMP
	 * is supported, we can have 2 frames in the FIFO and use TXFEMP
	 * to determine अगर 1 or 2 frames have been sent.
	 * Theoretically we should be able to use TXFWMEMP to determine up
	 * to 3 frames, but it seems that after putting a second frame in the
	 * FIFO, with watermark at 2 frames, it can happen that TXFWMEMP (less
	 * than 2 frames in FIFO) is set anyway with no TXOK (a frame was
	 * sent), which is not a sensible state - possibly TXFWMEMP is not
	 * completely synchronized with the rest of the bits?
	 *
	 * With TX mailboxes:
	 *
	 * HW sends frames in CAN ID priority order. To preserve FIFO ordering
	 * we submit frames one at a समय.
	 */
	अगर (!(devtype->flags & XCAN_FLAG_TX_MAILBOXES) &&
	    (devtype->flags & XCAN_FLAG_TXFEMP))
		tx_max = min(hw_tx_max, 2U);
	अन्यथा
		tx_max = 1;

	rx_max = hw_rx_max;

	/* Create a CAN device instance */
	ndev = alloc_candev(माप(काष्ठा xcan_priv), tx_max);
	अगर (!ndev)
		वापस -ENOMEM;

	priv = netdev_priv(ndev);
	priv->dev = &pdev->dev;
	priv->can.bittiming_स्थिर = devtype->bittiming_स्थिर;
	priv->can.करो_set_mode = xcan_करो_set_mode;
	priv->can.करो_get_berr_counter = xcan_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
					CAN_CTRLMODE_BERR_REPORTING;

	अगर (devtype->cantype == XAXI_CANFD)
		priv->can.data_bittiming_स्थिर =
			&xcan_data_bittiming_स्थिर_canfd;

	अगर (devtype->cantype == XAXI_CANFD_2_0)
		priv->can.data_bittiming_स्थिर =
			&xcan_data_bittiming_स्थिर_canfd2;

	अगर (devtype->cantype == XAXI_CANFD ||
	    devtype->cantype == XAXI_CANFD_2_0)
		priv->can.ctrlmode_supported |= CAN_CTRLMODE_FD;

	priv->reg_base = addr;
	priv->tx_max = tx_max;
	priv->devtype = *devtype;
	spin_lock_init(&priv->tx_lock);

	/* Get IRQ क्रम the device */
	ndev->irq = platक्रमm_get_irq(pdev, 0);
	ndev->flags |= IFF_ECHO;	/* We support local echo */

	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &xcan_netdev_ops;

	/* Getting the CAN can_clk info */
	priv->can_clk = devm_clk_get(&pdev->dev, "can_clk");
	अगर (IS_ERR(priv->can_clk)) अणु
		ret = dev_err_probe(&pdev->dev, PTR_ERR(priv->can_clk),
				    "device clock not found\n");
		जाओ err_मुक्त;
	पूर्ण

	priv->bus_clk = devm_clk_get(&pdev->dev, devtype->bus_clk_name);
	अगर (IS_ERR(priv->bus_clk)) अणु
		ret = dev_err_probe(&pdev->dev, PTR_ERR(priv->bus_clk),
				    "bus clock not found\n");
		जाओ err_मुक्त;
	पूर्ण

	priv->ग_लिखो_reg = xcan_ग_लिखो_reg_le;
	priv->पढ़ो_reg = xcan_पढ़ो_reg_le;

	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		netdev_err(ndev, "%s: pm_runtime_get failed(%d)\n",
			   __func__, ret);
		जाओ err_disableclks;
	पूर्ण

	अगर (priv->पढ़ो_reg(priv, XCAN_SR_OFFSET) != XCAN_SR_CONFIG_MASK) अणु
		priv->ग_लिखो_reg = xcan_ग_लिखो_reg_be;
		priv->पढ़ो_reg = xcan_पढ़ो_reg_be;
	पूर्ण

	priv->can.घड़ी.freq = clk_get_rate(priv->can_clk);

	netअगर_napi_add(ndev, &priv->napi, xcan_rx_poll, rx_max);

	ret = रेजिस्टर_candev(ndev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "fail to register failed (err=%d)\n", ret);
		जाओ err_disableclks;
	पूर्ण

	devm_can_led_init(ndev);

	pm_runसमय_put(&pdev->dev);

	अगर (priv->devtype.flags & XCAN_FLAG_CANFD_2) अणु
		priv->ग_लिखो_reg(priv, XCAN_AFR_2_ID_OFFSET, 0x00000000);
		priv->ग_लिखो_reg(priv, XCAN_AFR_2_MASK_OFFSET, 0x00000000);
	पूर्ण

	netdev_dbg(ndev, "reg_base=0x%p irq=%d clock=%d, tx buffers: actual %d, using %d\n",
		   priv->reg_base, ndev->irq, priv->can.घड़ी.freq,
		   hw_tx_max, priv->tx_max);

	वापस 0;

err_disableclks:
	pm_runसमय_put(priv->dev);
	pm_runसमय_disable(&pdev->dev);
err_मुक्त:
	मुक्त_candev(ndev);
err:
	वापस ret;
पूर्ण

/**
 * xcan_हटाओ - Unरेजिस्टर the device after releasing the resources
 * @pdev:	Handle to the platक्रमm device काष्ठाure
 *
 * This function मुक्तs all the resources allocated to the device.
 * Return: 0 always
 */
अटल पूर्णांक xcan_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा xcan_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_candev(ndev);
	pm_runसमय_disable(&pdev->dev);
	netअगर_napi_del(&priv->napi);
	मुक्त_candev(ndev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xcan_driver = अणु
	.probe = xcan_probe,
	.हटाओ	= xcan_हटाओ,
	.driver	= अणु
		.name = DRIVER_NAME,
		.pm = &xcan_dev_pm_ops,
		.of_match_table	= xcan_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xcan_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Xilinx Inc");
MODULE_DESCRIPTION("Xilinx CAN interface");
