<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 1999 - 2010 Intel Corporation.
 * Copyright (C) 2010 LAPIS SEMICONDUCTOR CO., LTD.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/can.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/can/error.h>

#घोषणा PCH_CTRL_INIT		BIT(0) /* The INIT bit of CANCONT रेजिस्टर. */
#घोषणा PCH_CTRL_IE		BIT(1) /* The IE bit of CAN control रेजिस्टर */
#घोषणा PCH_CTRL_IE_SIE_EIE	(BIT(3) | BIT(2) | BIT(1))
#घोषणा PCH_CTRL_CCE		BIT(6)
#घोषणा PCH_CTRL_OPT		BIT(7) /* The OPT bit of CANCONT रेजिस्टर. */
#घोषणा PCH_OPT_SILENT		BIT(3) /* The Silent bit of CANOPT reg. */
#घोषणा PCH_OPT_LBACK		BIT(4) /* The LoopBack bit of CANOPT reg. */

#घोषणा PCH_CMASK_RX_TX_SET	0x00f3
#घोषणा PCH_CMASK_RX_TX_GET	0x0073
#घोषणा PCH_CMASK_ALL		0xff
#घोषणा PCH_CMASK_NEWDAT	BIT(2)
#घोषणा PCH_CMASK_CLRINTPND	BIT(3)
#घोषणा PCH_CMASK_CTRL		BIT(4)
#घोषणा PCH_CMASK_ARB		BIT(5)
#घोषणा PCH_CMASK_MASK		BIT(6)
#घोषणा PCH_CMASK_RDWR		BIT(7)
#घोषणा PCH_IF_MCONT_NEWDAT	BIT(15)
#घोषणा PCH_IF_MCONT_MSGLOST	BIT(14)
#घोषणा PCH_IF_MCONT_INTPND	BIT(13)
#घोषणा PCH_IF_MCONT_UMASK	BIT(12)
#घोषणा PCH_IF_MCONT_TXIE	BIT(11)
#घोषणा PCH_IF_MCONT_RXIE	BIT(10)
#घोषणा PCH_IF_MCONT_RMTEN	BIT(9)
#घोषणा PCH_IF_MCONT_TXRQXT	BIT(8)
#घोषणा PCH_IF_MCONT_EOB	BIT(7)
#घोषणा PCH_IF_MCONT_DLC	(BIT(0) | BIT(1) | BIT(2) | BIT(3))
#घोषणा PCH_MASK2_Mसूची_MXTD	(BIT(14) | BIT(15))
#घोषणा PCH_ID2_सूची		BIT(13)
#घोषणा PCH_ID2_XTD		BIT(14)
#घोषणा PCH_ID_MSGVAL		BIT(15)
#घोषणा PCH_IF_CREQ_BUSY	BIT(15)

#घोषणा PCH_STATUS_INT		0x8000
#घोषणा PCH_RP			0x00008000
#घोषणा PCH_REC			0x00007f00
#घोषणा PCH_TEC			0x000000ff

#घोषणा PCH_TX_OK		BIT(3)
#घोषणा PCH_RX_OK		BIT(4)
#घोषणा PCH_EPASSIV		BIT(5)
#घोषणा PCH_EWARN		BIT(6)
#घोषणा PCH_BUS_OFF		BIT(7)

/* bit position of certain controller bits. */
#घोषणा PCH_BIT_BRP_SHIFT	0
#घोषणा PCH_BIT_SJW_SHIFT	6
#घोषणा PCH_BIT_TSEG1_SHIFT	8
#घोषणा PCH_BIT_TSEG2_SHIFT	12
#घोषणा PCH_BIT_BRPE_BRPE_SHIFT	6

#घोषणा PCH_MSK_BITT_BRP	0x3f
#घोषणा PCH_MSK_BRPE_BRPE	0x3c0
#घोषणा PCH_MSK_CTRL_IE_SIE_EIE	0x07
#घोषणा PCH_COUNTER_LIMIT	10

#घोषणा PCH_CAN_CLK		50000000	/* 50MHz */

/*
 * Define the number of message object.
 * PCH CAN communications are करोne via Message RAM.
 * The Message RAM consists of 32 message objects.
 */
#घोषणा PCH_RX_OBJ_NUM		26
#घोषणा PCH_TX_OBJ_NUM		6
#घोषणा PCH_RX_OBJ_START	1
#घोषणा PCH_RX_OBJ_END		PCH_RX_OBJ_NUM
#घोषणा PCH_TX_OBJ_START	(PCH_RX_OBJ_END + 1)
#घोषणा PCH_TX_OBJ_END		(PCH_RX_OBJ_NUM + PCH_TX_OBJ_NUM)

#घोषणा PCH_FIFO_THRESH		16

/* TxRqst2 show status of MsgObjNo.17~32 */
#घोषणा PCH_TREQ2_TX_MASK	(((1 << PCH_TX_OBJ_NUM) - 1) <<\
							(PCH_RX_OBJ_END - 16))

क्रमागत pch_अगरreg अणु
	PCH_RX_IFREG,
	PCH_TX_IFREG,
पूर्ण;

क्रमागत pch_can_err अणु
	PCH_STUF_ERR = 1,
	PCH_FORM_ERR,
	PCH_ACK_ERR,
	PCH_BIT1_ERR,
	PCH_BIT0_ERR,
	PCH_CRC_ERR,
	PCH_LEC_ALL,
पूर्ण;

क्रमागत pch_can_mode अणु
	PCH_CAN_ENABLE,
	PCH_CAN_DISABLE,
	PCH_CAN_ALL,
	PCH_CAN_NONE,
	PCH_CAN_STOP,
	PCH_CAN_RUN,
पूर्ण;

काष्ठा pch_can_अगर_regs अणु
	u32 creq;
	u32 cmask;
	u32 mask1;
	u32 mask2;
	u32 id1;
	u32 id2;
	u32 mcont;
	u32 data[4];
	u32 rsv[13];
पूर्ण;

काष्ठा pch_can_regs अणु
	u32 cont;
	u32 stat;
	u32 errc;
	u32 bitt;
	u32 पूर्णांकr;
	u32 opt;
	u32 brpe;
	u32 reserve;
	काष्ठा pch_can_अगर_regs अगरregs[2]; /* [0]=अगर1  [1]=अगर2 */
	u32 reserve1[8];
	u32 treq1;
	u32 treq2;
	u32 reserve2[6];
	u32 data1;
	u32 data2;
	u32 reserve3[6];
	u32 canipend1;
	u32 canipend2;
	u32 reserve4[6];
	u32 canmval1;
	u32 canmval2;
	u32 reserve5[37];
	u32 srst;
पूर्ण;

काष्ठा pch_can_priv अणु
	काष्ठा can_priv can;
	काष्ठा pci_dev *dev;
	u32 tx_enable[PCH_TX_OBJ_END];
	u32 rx_enable[PCH_TX_OBJ_END];
	u32 rx_link[PCH_TX_OBJ_END];
	u32 पूर्णांक_enables;
	काष्ठा net_device *ndev;
	काष्ठा pch_can_regs __iomem *regs;
	काष्ठा napi_काष्ठा napi;
	पूर्णांक tx_obj;	/* Poपूर्णांक next Tx Obj index */
	पूर्णांक use_msi;
पूर्ण;

अटल स्थिर काष्ठा can_bittiming_स्थिर pch_can_bittiming_स्थिर = अणु
	.name = KBUILD_MODNAME,
	.tseg1_min = 2,
	.tseg1_max = 16,
	.tseg2_min = 1,
	.tseg2_max = 8,
	.sjw_max = 4,
	.brp_min = 1,
	.brp_max = 1024, /* 6bit + extended 4bit */
	.brp_inc = 1,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id pch_pci_tbl[] = अणु
	अणुPCI_VENDOR_ID_INTEL, 0x8818, PCI_ANY_ID, PCI_ANY_ID,पूर्ण,
	अणु0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, pch_pci_tbl);

अटल अंतरभूत व्योम pch_can_bit_set(व्योम __iomem *addr, u32 mask)
अणु
	ioग_लिखो32(ioपढ़ो32(addr) | mask, addr);
पूर्ण

अटल अंतरभूत व्योम pch_can_bit_clear(व्योम __iomem *addr, u32 mask)
अणु
	ioग_लिखो32(ioपढ़ो32(addr) & ~mask, addr);
पूर्ण

अटल व्योम pch_can_set_run_mode(काष्ठा pch_can_priv *priv,
				 क्रमागत pch_can_mode mode)
अणु
	चयन (mode) अणु
	हाल PCH_CAN_RUN:
		pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_INIT);
		अवरोध;

	हाल PCH_CAN_STOP:
		pch_can_bit_set(&priv->regs->cont, PCH_CTRL_INIT);
		अवरोध;

	शेष:
		netdev_err(priv->ndev, "%s -> Invalid Mode.\n", __func__);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pch_can_set_opपंचांगode(काष्ठा pch_can_priv *priv)
अणु
	u32 reg_val = ioपढ़ो32(&priv->regs->opt);

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg_val |= PCH_OPT_SILENT;

	अगर (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg_val |= PCH_OPT_LBACK;

	pch_can_bit_set(&priv->regs->cont, PCH_CTRL_OPT);
	ioग_लिखो32(reg_val, &priv->regs->opt);
पूर्ण

अटल व्योम pch_can_rw_msg_obj(व्योम __iomem *creq_addr, u32 num)
अणु
	पूर्णांक counter = PCH_COUNTER_LIMIT;
	u32 अगरx_creq;

	ioग_लिखो32(num, creq_addr);
	जबतक (counter) अणु
		अगरx_creq = ioपढ़ो32(creq_addr) & PCH_IF_CREQ_BUSY;
		अगर (!अगरx_creq)
			अवरोध;
		counter--;
		udelay(1);
	पूर्ण
	अगर (!counter)
		pr_err("%s:IF1 BUSY Flag is set forever.\n", __func__);
पूर्ण

अटल व्योम pch_can_set_पूर्णांक_enables(काष्ठा pch_can_priv *priv,
				    क्रमागत pch_can_mode पूर्णांकerrupt_no)
अणु
	चयन (पूर्णांकerrupt_no) अणु
	हाल PCH_CAN_DISABLE:
		pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_IE);
		अवरोध;

	हाल PCH_CAN_ALL:
		pch_can_bit_set(&priv->regs->cont, PCH_CTRL_IE_SIE_EIE);
		अवरोध;

	हाल PCH_CAN_NONE:
		pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_IE_SIE_EIE);
		अवरोध;

	शेष:
		netdev_err(priv->ndev, "Invalid interrupt number.\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम pch_can_set_rxtx(काष्ठा pch_can_priv *priv, u32 buff_num,
			     पूर्णांक set, क्रमागत pch_अगरreg dir)
अणु
	u32 ie;

	अगर (dir)
		ie = PCH_IF_MCONT_TXIE;
	अन्यथा
		ie = PCH_IF_MCONT_RXIE;

	/* Reading the Msg buffer from Message RAM to IF1/2 रेजिस्टरs. */
	ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[dir].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[dir].creq, buff_num);

	/* Setting the IF1/2MASK1 रेजिस्टर to access MsgVal and RxIE bits */
	ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_ARB | PCH_CMASK_CTRL,
		  &priv->regs->अगरregs[dir].cmask);

	अगर (set) अणु
		/* Setting the MsgVal and RxIE/TxIE bits */
		pch_can_bit_set(&priv->regs->अगरregs[dir].mcont, ie);
		pch_can_bit_set(&priv->regs->अगरregs[dir].id2, PCH_ID_MSGVAL);
	पूर्ण अन्यथा अणु
		/* Clearing the MsgVal and RxIE/TxIE bits */
		pch_can_bit_clear(&priv->regs->अगरregs[dir].mcont, ie);
		pch_can_bit_clear(&priv->regs->अगरregs[dir].id2, PCH_ID_MSGVAL);
	पूर्ण

	pch_can_rw_msg_obj(&priv->regs->अगरregs[dir].creq, buff_num);
पूर्ण

अटल व्योम pch_can_set_rx_all(काष्ठा pch_can_priv *priv, पूर्णांक set)
अणु
	पूर्णांक i;

	/* Traversing to obtain the object configured as receivers. */
	क्रम (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++)
		pch_can_set_rxtx(priv, i, set, PCH_RX_IFREG);
पूर्ण

अटल व्योम pch_can_set_tx_all(काष्ठा pch_can_priv *priv, पूर्णांक set)
अणु
	पूर्णांक i;

	/* Traversing to obtain the object configured as transmit object. */
	क्रम (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++)
		pch_can_set_rxtx(priv, i, set, PCH_TX_IFREG);
पूर्ण

अटल u32 pch_can_पूर्णांक_pending(काष्ठा pch_can_priv *priv)
अणु
	वापस ioपढ़ो32(&priv->regs->पूर्णांकr) & 0xffff;
पूर्ण

अटल व्योम pch_can_clear_अगर_buffers(काष्ठा pch_can_priv *priv)
अणु
	पूर्णांक i; /* Msg Obj ID (1~32) */

	क्रम (i = PCH_RX_OBJ_START; i <= PCH_TX_OBJ_END; i++) अणु
		ioग_लिखो32(PCH_CMASK_RX_TX_SET, &priv->regs->अगरregs[0].cmask);
		ioग_लिखो32(0xffff, &priv->regs->अगरregs[0].mask1);
		ioग_लिखो32(0xffff, &priv->regs->अगरregs[0].mask2);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].id1);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].id2);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].mcont);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].data[0]);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].data[1]);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].data[2]);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].data[3]);
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_MASK |
			  PCH_CMASK_ARB | PCH_CMASK_CTRL,
			  &priv->regs->अगरregs[0].cmask);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, i);
	पूर्ण
पूर्ण

अटल व्योम pch_can_config_rx_tx_buffers(काष्ठा pch_can_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++) अणु
		ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[0].cmask);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, i);

		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].id1);
		ioग_लिखो32(0x0, &priv->regs->अगरregs[0].id2);

		pch_can_bit_set(&priv->regs->अगरregs[0].mcont,
				PCH_IF_MCONT_UMASK);

		/* In हाल FIFO mode, Last EoB of Rx Obj must be 1 */
		अगर (i == PCH_RX_OBJ_END)
			pch_can_bit_set(&priv->regs->अगरregs[0].mcont,
					PCH_IF_MCONT_EOB);
		अन्यथा
			pch_can_bit_clear(&priv->regs->अगरregs[0].mcont,
					  PCH_IF_MCONT_EOB);

		ioग_लिखो32(0, &priv->regs->अगरregs[0].mask1);
		pch_can_bit_clear(&priv->regs->अगरregs[0].mask2,
				  0x1fff | PCH_MASK2_Mसूची_MXTD);

		/* Setting CMASK क्रम writing */
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_MASK | PCH_CMASK_ARB |
			  PCH_CMASK_CTRL, &priv->regs->अगरregs[0].cmask);

		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, i);
	पूर्ण

	क्रम (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++) अणु
		ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[1].cmask);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[1].creq, i);

		/* Resetting सूची bit क्रम reception */
		ioग_लिखो32(0x0, &priv->regs->अगरregs[1].id1);
		ioग_लिखो32(PCH_ID2_सूची, &priv->regs->अगरregs[1].id2);

		/* Setting EOB bit क्रम transmitter */
		ioग_लिखो32(PCH_IF_MCONT_EOB | PCH_IF_MCONT_UMASK,
			  &priv->regs->अगरregs[1].mcont);

		ioग_लिखो32(0, &priv->regs->अगरregs[1].mask1);
		pch_can_bit_clear(&priv->regs->अगरregs[1].mask2, 0x1fff);

		/* Setting CMASK क्रम writing */
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_MASK | PCH_CMASK_ARB |
			  PCH_CMASK_CTRL, &priv->regs->अगरregs[1].cmask);

		pch_can_rw_msg_obj(&priv->regs->अगरregs[1].creq, i);
	पूर्ण
पूर्ण

अटल व्योम pch_can_init(काष्ठा pch_can_priv *priv)
अणु
	/* Stopping the Can device. */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Clearing all the message object buffers. */
	pch_can_clear_अगर_buffers(priv);

	/* Configuring the respective message object as either rx/tx object. */
	pch_can_config_rx_tx_buffers(priv);

	/* Enabling the पूर्णांकerrupts. */
	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_ALL);
पूर्ण

अटल व्योम pch_can_release(काष्ठा pch_can_priv *priv)
अणु
	/* Stooping the CAN device. */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Disabling the पूर्णांकerrupts. */
	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_NONE);

	/* Disabling all the receive object. */
	pch_can_set_rx_all(priv, 0);

	/* Disabling all the transmit object. */
	pch_can_set_tx_all(priv, 0);
पूर्ण

/* This function clears पूर्णांकerrupt(s) from the CAN device. */
अटल व्योम pch_can_पूर्णांक_clr(काष्ठा pch_can_priv *priv, u32 mask)
अणु
	/* Clear पूर्णांकerrupt क्रम transmit object */
	अगर ((mask >= PCH_RX_OBJ_START) && (mask <= PCH_RX_OBJ_END)) अणु
		/* Setting CMASK क्रम clearing the reception पूर्णांकerrupts. */
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->अगरregs[0].cmask);

		/* Clearing the Dir bit. */
		pch_can_bit_clear(&priv->regs->अगरregs[0].id2, PCH_ID2_सूची);

		/* Clearing NewDat & IntPnd */
		pch_can_bit_clear(&priv->regs->अगरregs[0].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND);

		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, mask);
	पूर्ण अन्यथा अगर ((mask >= PCH_TX_OBJ_START) && (mask <= PCH_TX_OBJ_END)) अणु
		/*
		 * Setting CMASK क्रम clearing पूर्णांकerrupts क्रम frame transmission.
		 */
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_CTRL | PCH_CMASK_ARB,
			  &priv->regs->अगरregs[1].cmask);

		/* Resetting the ID रेजिस्टरs. */
		pch_can_bit_set(&priv->regs->अगरregs[1].id2,
			       PCH_ID2_सूची | (0x7ff << 2));
		ioग_लिखो32(0x0, &priv->regs->अगरregs[1].id1);

		/* Clearing NewDat, TxRqst & IntPnd */
		pch_can_bit_clear(&priv->regs->अगरregs[1].mcont,
				  PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_INTPND |
				  PCH_IF_MCONT_TXRQXT);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[1].creq, mask);
	पूर्ण
पूर्ण

अटल व्योम pch_can_reset(काष्ठा pch_can_priv *priv)
अणु
	/* ग_लिखो to sw reset रेजिस्टर */
	ioग_लिखो32(1, &priv->regs->srst);
	ioग_लिखो32(0, &priv->regs->srst);
पूर्ण

अटल व्योम pch_can_error(काष्ठा net_device *ndev, u32 status)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf;
	u32 errc, lec;
	काष्ठा net_device_stats *stats = &(priv->ndev->stats);
	क्रमागत can_state state = priv->can.state;

	skb = alloc_can_err_skb(ndev, &cf);
	अगर (!skb)
		वापस;

	अगर (status & PCH_BUS_OFF) अणु
		pch_can_set_tx_all(priv, 0);
		pch_can_set_rx_all(priv, 0);
		state = CAN_STATE_BUS_OFF;
		cf->can_id |= CAN_ERR_BUSOFF;
		priv->can.can_stats.bus_off++;
		can_bus_off(ndev);
	पूर्ण

	errc = ioपढ़ो32(&priv->regs->errc);
	/* Warning पूर्णांकerrupt. */
	अगर (status & PCH_EWARN) अणु
		state = CAN_STATE_ERROR_WARNING;
		priv->can.can_stats.error_warning++;
		cf->can_id |= CAN_ERR_CRTL;
		अगर (((errc & PCH_REC) >> 8) > 96)
			cf->data[1] |= CAN_ERR_CRTL_RX_WARNING;
		अगर ((errc & PCH_TEC) > 96)
			cf->data[1] |= CAN_ERR_CRTL_TX_WARNING;
		netdev_dbg(ndev,
			"%s -> Error Counter is more than 96.\n", __func__);
	पूर्ण
	/* Error passive पूर्णांकerrupt. */
	अगर (status & PCH_EPASSIV) अणु
		priv->can.can_stats.error_passive++;
		state = CAN_STATE_ERROR_PASSIVE;
		cf->can_id |= CAN_ERR_CRTL;
		अगर (errc & PCH_RP)
			cf->data[1] |= CAN_ERR_CRTL_RX_PASSIVE;
		अगर ((errc & PCH_TEC) > 127)
			cf->data[1] |= CAN_ERR_CRTL_TX_PASSIVE;
		netdev_dbg(ndev,
			"%s -> CAN controller is ERROR PASSIVE .\n", __func__);
	पूर्ण

	lec = status & PCH_LEC_ALL;
	चयन (lec) अणु
	हाल PCH_STUF_ERR:
		cf->data[2] |= CAN_ERR_PROT_STUFF;
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;
		अवरोध;
	हाल PCH_FORM_ERR:
		cf->data[2] |= CAN_ERR_PROT_FORM;
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;
		अवरोध;
	हाल PCH_ACK_ERR:
		cf->can_id |= CAN_ERR_ACK;
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;
		अवरोध;
	हाल PCH_BIT1_ERR:
	हाल PCH_BIT0_ERR:
		cf->data[2] |= CAN_ERR_PROT_BIT;
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;
		अवरोध;
	हाल PCH_CRC_ERR:
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;
		priv->can.can_stats.bus_error++;
		stats->rx_errors++;
		अवरोध;
	हाल PCH_LEC_ALL: /* Written by CPU. No error status */
		अवरोध;
	पूर्ण

	cf->data[6] = errc & PCH_TEC;
	cf->data[7] = (errc & PCH_REC) >> 8;

	priv->can.state = state;
	netअगर_receive_skb(skb);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;
पूर्ण

अटल irqवापस_t pch_can_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);

	अगर (!pch_can_पूर्णांक_pending(priv))
		वापस IRQ_NONE;

	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_NONE);
	napi_schedule(&priv->napi);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम pch_fअगरo_thresh(काष्ठा pch_can_priv *priv, पूर्णांक obj_id)
अणु
	अगर (obj_id < PCH_FIFO_THRESH) अणु
		ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_CTRL |
			  PCH_CMASK_ARB, &priv->regs->अगरregs[0].cmask);

		/* Clearing the Dir bit. */
		pch_can_bit_clear(&priv->regs->अगरregs[0].id2, PCH_ID2_सूची);

		/* Clearing NewDat & IntPnd */
		pch_can_bit_clear(&priv->regs->अगरregs[0].mcont,
				  PCH_IF_MCONT_INTPND);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, obj_id);
	पूर्ण अन्यथा अगर (obj_id > PCH_FIFO_THRESH) अणु
		pch_can_पूर्णांक_clr(priv, obj_id);
	पूर्ण अन्यथा अगर (obj_id == PCH_FIFO_THRESH) अणु
		पूर्णांक cnt;
		क्रम (cnt = 0; cnt < PCH_FIFO_THRESH; cnt++)
			pch_can_पूर्णांक_clr(priv, cnt + 1);
	पूर्ण
पूर्ण

अटल व्योम pch_can_rx_msg_lost(काष्ठा net_device *ndev, पूर्णांक obj_id)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &(priv->ndev->stats);
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;

	netdev_dbg(priv->ndev, "Msg Obj is overwritten.\n");
	pch_can_bit_clear(&priv->regs->अगरregs[0].mcont,
			  PCH_IF_MCONT_MSGLOST);
	ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_CTRL,
		  &priv->regs->अगरregs[0].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, obj_id);

	skb = alloc_can_err_skb(ndev, &cf);
	अगर (!skb)
		वापस;

	cf->can_id |= CAN_ERR_CRTL;
	cf->data[1] = CAN_ERR_CRTL_RX_OVERFLOW;
	stats->rx_over_errors++;
	stats->rx_errors++;

	netअगर_receive_skb(skb);
पूर्ण

अटल पूर्णांक pch_can_rx_normal(काष्ठा net_device *ndev, u32 obj_num, पूर्णांक quota)
अणु
	u32 reg;
	canid_t id;
	पूर्णांक rcv_pkts = 0;
	काष्ठा sk_buff *skb;
	काष्ठा can_frame *cf;
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &(priv->ndev->stats);
	पूर्णांक i;
	u32 id2;
	u16 data_reg;

	करो अणु
		/* Reading the message object from the Message RAM */
		ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[0].cmask);
		pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, obj_num);

		/* Reading the MCONT रेजिस्टर. */
		reg = ioपढ़ो32(&priv->regs->अगरregs[0].mcont);

		अगर (reg & PCH_IF_MCONT_EOB)
			अवरोध;

		/* If MsgLost bit set. */
		अगर (reg & PCH_IF_MCONT_MSGLOST) अणु
			pch_can_rx_msg_lost(ndev, obj_num);
			rcv_pkts++;
			quota--;
			obj_num++;
			जारी;
		पूर्ण अन्यथा अगर (!(reg & PCH_IF_MCONT_NEWDAT)) अणु
			obj_num++;
			जारी;
		पूर्ण

		skb = alloc_can_skb(priv->ndev, &cf);
		अगर (!skb) अणु
			netdev_err(ndev, "alloc_can_skb Failed\n");
			वापस rcv_pkts;
		पूर्ण

		/* Get Received data */
		id2 = ioपढ़ो32(&priv->regs->अगरregs[0].id2);
		अगर (id2 & PCH_ID2_XTD) अणु
			id = (ioपढ़ो32(&priv->regs->अगरregs[0].id1) & 0xffff);
			id |= (((id2) & 0x1fff) << 16);
			cf->can_id = id | CAN_EFF_FLAG;
		पूर्ण अन्यथा अणु
			id = (id2 >> 2) & CAN_SFF_MASK;
			cf->can_id = id;
		पूर्ण

		अगर (id2 & PCH_ID2_सूची)
			cf->can_id |= CAN_RTR_FLAG;

		cf->len = can_cc_dlc2len((ioपढ़ो32(&priv->regs->
						    अगरregs[0].mcont)) & 0xF);

		क्रम (i = 0; i < cf->len; i += 2) अणु
			data_reg = ioपढ़ो16(&priv->regs->अगरregs[0].data[i / 2]);
			cf->data[i] = data_reg;
			cf->data[i + 1] = data_reg >> 8;
		पूर्ण

		netअगर_receive_skb(skb);
		rcv_pkts++;
		stats->rx_packets++;
		quota--;
		stats->rx_bytes += cf->len;

		pch_fअगरo_thresh(priv, obj_num);
		obj_num++;
	पूर्ण जबतक (quota > 0);

	वापस rcv_pkts;
पूर्ण

अटल व्योम pch_can_tx_complete(काष्ठा net_device *ndev, u32 पूर्णांक_stat)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &(priv->ndev->stats);
	u32 dlc;

	can_get_echo_skb(ndev, पूर्णांक_stat - PCH_RX_OBJ_END - 1, शून्य);
	ioग_लिखो32(PCH_CMASK_RX_TX_GET | PCH_CMASK_CLRINTPND,
		  &priv->regs->अगरregs[1].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[1].creq, पूर्णांक_stat);
	dlc = can_cc_dlc2len(ioपढ़ो32(&priv->regs->अगरregs[1].mcont) &
			  PCH_IF_MCONT_DLC);
	stats->tx_bytes += dlc;
	stats->tx_packets++;
	अगर (पूर्णांक_stat == PCH_TX_OBJ_END)
		netअगर_wake_queue(ndev);
पूर्ण

अटल पूर्णांक pch_can_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक quota)
अणु
	काष्ठा net_device *ndev = napi->dev;
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	u32 पूर्णांक_stat;
	u32 reg_stat;
	पूर्णांक quota_save = quota;

	पूर्णांक_stat = pch_can_पूर्णांक_pending(priv);
	अगर (!पूर्णांक_stat)
		जाओ end;

	अगर (पूर्णांक_stat == PCH_STATUS_INT) अणु
		reg_stat = ioपढ़ो32(&priv->regs->stat);

		अगर ((reg_stat & (PCH_BUS_OFF | PCH_LEC_ALL)) &&
		   ((reg_stat & PCH_LEC_ALL) != PCH_LEC_ALL)) अणु
			pch_can_error(ndev, reg_stat);
			quota--;
		पूर्ण

		अगर (reg_stat & (PCH_TX_OK | PCH_RX_OK))
			pch_can_bit_clear(&priv->regs->stat,
					  reg_stat & (PCH_TX_OK | PCH_RX_OK));

		पूर्णांक_stat = pch_can_पूर्णांक_pending(priv);
	पूर्ण

	अगर (quota == 0)
		जाओ end;

	अगर ((पूर्णांक_stat >= PCH_RX_OBJ_START) && (पूर्णांक_stat <= PCH_RX_OBJ_END)) अणु
		quota -= pch_can_rx_normal(ndev, पूर्णांक_stat, quota);
	पूर्ण अन्यथा अगर ((पूर्णांक_stat >= PCH_TX_OBJ_START) &&
		   (पूर्णांक_stat <= PCH_TX_OBJ_END)) अणु
		/* Handle transmission पूर्णांकerrupt */
		pch_can_tx_complete(ndev, पूर्णांक_stat);
	पूर्ण

end:
	napi_complete(napi);
	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_ALL);

	वापस quota_save - quota;
पूर्ण

अटल पूर्णांक pch_set_bittiming(काष्ठा net_device *ndev)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	स्थिर काष्ठा can_bittiming *bt = &priv->can.bittiming;
	u32 canbit;
	u32 bepe;

	/* Setting the CCE bit क्रम accessing the Can Timing रेजिस्टर. */
	pch_can_bit_set(&priv->regs->cont, PCH_CTRL_CCE);

	canbit = (bt->brp - 1) & PCH_MSK_BITT_BRP;
	canbit |= (bt->sjw - 1) << PCH_BIT_SJW_SHIFT;
	canbit |= (bt->phase_seg1 + bt->prop_seg - 1) << PCH_BIT_TSEG1_SHIFT;
	canbit |= (bt->phase_seg2 - 1) << PCH_BIT_TSEG2_SHIFT;
	bepe = ((bt->brp - 1) & PCH_MSK_BRPE_BRPE) >> PCH_BIT_BRPE_BRPE_SHIFT;
	ioग_लिखो32(canbit, &priv->regs->bitt);
	ioग_लिखो32(bepe, &priv->regs->brpe);
	pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_CCE);

	वापस 0;
पूर्ण

अटल व्योम pch_can_start(काष्ठा net_device *ndev)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);

	अगर (priv->can.state != CAN_STATE_STOPPED)
		pch_can_reset(priv);

	pch_set_bittiming(ndev);
	pch_can_set_opपंचांगode(priv);

	pch_can_set_tx_all(priv, 1);
	pch_can_set_rx_all(priv, 1);

	/* Setting the CAN to run mode. */
	pch_can_set_run_mode(priv, PCH_CAN_RUN);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	वापस;
पूर्ण

अटल पूर्णांक pch_can_करो_set_mode(काष्ठा net_device *ndev, क्रमागत can_mode mode)
अणु
	पूर्णांक ret = 0;

	चयन (mode) अणु
	हाल CAN_MODE_START:
		pch_can_start(ndev);
		netअगर_wake_queue(ndev);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pch_can_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	पूर्णांक retval;

	/* Registering the पूर्णांकerrupt. */
	retval = request_irq(priv->dev->irq, pch_can_पूर्णांकerrupt, IRQF_SHARED,
			     ndev->name, ndev);
	अगर (retval) अणु
		netdev_err(ndev, "request_irq failed.\n");
		जाओ req_irq_err;
	पूर्ण

	/* Open common can device */
	retval = खोलो_candev(ndev);
	अगर (retval) अणु
		netdev_err(ndev, "open_candev() failed %d\n", retval);
		जाओ err_खोलो_candev;
	पूर्ण

	pch_can_init(priv);
	pch_can_start(ndev);
	napi_enable(&priv->napi);
	netअगर_start_queue(ndev);

	वापस 0;

err_खोलो_candev:
	मुक्त_irq(priv->dev->irq, ndev);
req_irq_err:
	pch_can_release(priv);

	वापस retval;
पूर्ण

अटल पूर्णांक pch_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);
	pch_can_release(priv);
	मुक्त_irq(priv->dev->irq, ndev);
	बंद_candev(ndev);
	priv->can.state = CAN_STATE_STOPPED;
	वापस 0;
पूर्ण

अटल netdev_tx_t pch_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);
	काष्ठा can_frame *cf = (काष्ठा can_frame *)skb->data;
	पूर्णांक tx_obj_no;
	पूर्णांक i;
	u32 id2;

	अगर (can_dropped_invalid_skb(ndev, skb))
		वापस NETDEV_TX_OK;

	tx_obj_no = priv->tx_obj;
	अगर (priv->tx_obj == PCH_TX_OBJ_END) अणु
		अगर (ioपढ़ो32(&priv->regs->treq2) & PCH_TREQ2_TX_MASK)
			netअगर_stop_queue(ndev);

		priv->tx_obj = PCH_TX_OBJ_START;
	पूर्ण अन्यथा अणु
		priv->tx_obj++;
	पूर्ण

	/* Setting the CMASK रेजिस्टर. */
	pch_can_bit_set(&priv->regs->अगरregs[1].cmask, PCH_CMASK_ALL);

	/* If ID extended is set. */
	अगर (cf->can_id & CAN_EFF_FLAG) अणु
		ioग_लिखो32(cf->can_id & 0xffff, &priv->regs->अगरregs[1].id1);
		id2 = ((cf->can_id >> 16) & 0x1fff) | PCH_ID2_XTD;
	पूर्ण अन्यथा अणु
		ioग_लिखो32(0, &priv->regs->अगरregs[1].id1);
		id2 = (cf->can_id & CAN_SFF_MASK) << 2;
	पूर्ण

	id2 |= PCH_ID_MSGVAL;

	/* If remote frame has to be transmitted.. */
	अगर (!(cf->can_id & CAN_RTR_FLAG))
		id2 |= PCH_ID2_सूची;

	ioग_लिखो32(id2, &priv->regs->अगरregs[1].id2);

	/* Copy data to रेजिस्टर */
	क्रम (i = 0; i < cf->len; i += 2) अणु
		ioग_लिखो16(cf->data[i] | (cf->data[i + 1] << 8),
			  &priv->regs->अगरregs[1].data[i / 2]);
	पूर्ण

	can_put_echo_skb(skb, ndev, tx_obj_no - PCH_RX_OBJ_END - 1, 0);

	/* Set the size of the data. Update अगर2_mcont */
	ioग_लिखो32(cf->len | PCH_IF_MCONT_NEWDAT | PCH_IF_MCONT_TXRQXT |
		  PCH_IF_MCONT_TXIE, &priv->regs->अगरregs[1].mcont);

	pch_can_rw_msg_obj(&priv->regs->अगरregs[1].creq, tx_obj_no);

	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops pch_can_netdev_ops = अणु
	.nकरो_खोलो		= pch_can_खोलो,
	.nकरो_stop		= pch_बंद,
	.nकरो_start_xmit		= pch_xmit,
	.nकरो_change_mtu		= can_change_mtu,
पूर्ण;

अटल व्योम pch_can_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *ndev = pci_get_drvdata(pdev);
	काष्ठा pch_can_priv *priv = netdev_priv(ndev);

	unरेजिस्टर_candev(priv->ndev);
	अगर (priv->use_msi)
		pci_disable_msi(priv->dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pch_can_reset(priv);
	pci_iounmap(pdev, priv->regs);
	मुक्त_candev(priv->ndev);
पूर्ण

अटल व्योम __maybe_unused pch_can_set_पूर्णांक_custom(काष्ठा pch_can_priv *priv)
अणु
	/* Clearing the IE, SIE and EIE bits of Can control रेजिस्टर. */
	pch_can_bit_clear(&priv->regs->cont, PCH_CTRL_IE_SIE_EIE);

	/* Appropriately setting them. */
	pch_can_bit_set(&priv->regs->cont,
			((priv->पूर्णांक_enables & PCH_MSK_CTRL_IE_SIE_EIE) << 1));
पूर्ण

/* This function retrieves पूर्णांकerrupt enabled क्रम the CAN device. */
अटल u32 __maybe_unused pch_can_get_पूर्णांक_enables(काष्ठा pch_can_priv *priv)
अणु
	/* Obtaining the status of IE, SIE and EIE पूर्णांकerrupt bits. */
	वापस (ioपढ़ो32(&priv->regs->cont) & PCH_CTRL_IE_SIE_EIE) >> 1;
पूर्ण

अटल u32 __maybe_unused pch_can_get_rxtx_ir(काष्ठा pch_can_priv *priv,
					      u32 buff_num, क्रमागत pch_अगरreg dir)
अणु
	u32 ie, enable;

	अगर (dir)
		ie = PCH_IF_MCONT_RXIE;
	अन्यथा
		ie = PCH_IF_MCONT_TXIE;

	ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[dir].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[dir].creq, buff_num);

	अगर (((ioपढ़ो32(&priv->regs->अगरregs[dir].id2)) & PCH_ID_MSGVAL) &&
			((ioपढ़ो32(&priv->regs->अगरregs[dir].mcont)) & ie))
		enable = 1;
	अन्यथा
		enable = 0;

	वापस enable;
पूर्ण

अटल व्योम __maybe_unused pch_can_set_rx_buffer_link(काष्ठा pch_can_priv *priv,
						      u32 buffer_num, पूर्णांक set)
अणु
	ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[0].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, buffer_num);
	ioग_लिखो32(PCH_CMASK_RDWR | PCH_CMASK_CTRL,
		  &priv->regs->अगरregs[0].cmask);
	अगर (set)
		pch_can_bit_clear(&priv->regs->अगरregs[0].mcont,
				  PCH_IF_MCONT_EOB);
	अन्यथा
		pch_can_bit_set(&priv->regs->अगरregs[0].mcont, PCH_IF_MCONT_EOB);

	pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, buffer_num);
पूर्ण

अटल u32 __maybe_unused pch_can_get_rx_buffer_link(काष्ठा pch_can_priv *priv,
						     u32 buffer_num)
अणु
	u32 link;

	ioग_लिखो32(PCH_CMASK_RX_TX_GET, &priv->regs->अगरregs[0].cmask);
	pch_can_rw_msg_obj(&priv->regs->अगरregs[0].creq, buffer_num);

	अगर (ioपढ़ो32(&priv->regs->अगरregs[0].mcont) & PCH_IF_MCONT_EOB)
		link = 0;
	अन्यथा
		link = 1;
	वापस link;
पूर्ण

अटल पूर्णांक __maybe_unused pch_can_get_buffer_status(काष्ठा pch_can_priv *priv)
अणु
	वापस (ioपढ़ो32(&priv->regs->treq1) & 0xffff) |
	       (ioपढ़ो32(&priv->regs->treq2) << 16);
पूर्ण

अटल पूर्णांक __maybe_unused pch_can_suspend(काष्ठा device *dev_d)
अणु
	पूर्णांक i;
	u32 buf_stat;	/* Variable क्रम पढ़ोing the transmit buffer status. */
	पूर्णांक counter = PCH_COUNTER_LIMIT;

	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा pch_can_priv *priv = netdev_priv(dev);

	/* Stop the CAN controller */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Indicate that we are aboutto/in suspend */
	priv->can.state = CAN_STATE_STOPPED;

	/* Waiting क्रम all transmission to complete. */
	जबतक (counter) अणु
		buf_stat = pch_can_get_buffer_status(priv);
		अगर (!buf_stat)
			अवरोध;
		counter--;
		udelay(1);
	पूर्ण
	अगर (!counter)
		dev_err(dev_d, "%s -> Transmission time out.\n", __func__);

	/* Save पूर्णांकerrupt configuration and then disable them */
	priv->पूर्णांक_enables = pch_can_get_पूर्णांक_enables(priv);
	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_DISABLE);

	/* Save Tx buffer enable state */
	क्रम (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++)
		priv->tx_enable[i - 1] = pch_can_get_rxtx_ir(priv, i,
							     PCH_TX_IFREG);

	/* Disable all Transmit buffers */
	pch_can_set_tx_all(priv, 0);

	/* Save Rx buffer enable state */
	क्रम (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++) अणु
		priv->rx_enable[i - 1] = pch_can_get_rxtx_ir(priv, i,
							     PCH_RX_IFREG);
		priv->rx_link[i - 1] = pch_can_get_rx_buffer_link(priv, i);
	पूर्ण

	/* Disable all Receive buffers */
	pch_can_set_rx_all(priv, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pch_can_resume(काष्ठा device *dev_d)
अणु
	पूर्णांक i;
	काष्ठा net_device *dev = dev_get_drvdata(dev_d);
	काष्ठा pch_can_priv *priv = netdev_priv(dev);

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	/* Disabling all पूर्णांकerrupts. */
	pch_can_set_पूर्णांक_enables(priv, PCH_CAN_DISABLE);

	/* Setting the CAN device in Stop Mode. */
	pch_can_set_run_mode(priv, PCH_CAN_STOP);

	/* Configuring the transmit and receive buffers. */
	pch_can_config_rx_tx_buffers(priv);

	/* Restore the CAN state */
	pch_set_bittiming(dev);

	/* Listen/Active */
	pch_can_set_opपंचांगode(priv);

	/* Enabling the transmit buffer. */
	क्रम (i = PCH_TX_OBJ_START; i <= PCH_TX_OBJ_END; i++)
		pch_can_set_rxtx(priv, i, priv->tx_enable[i - 1], PCH_TX_IFREG);

	/* Configuring the receive buffer and enabling them. */
	क्रम (i = PCH_RX_OBJ_START; i <= PCH_RX_OBJ_END; i++) अणु
		/* Restore buffer link */
		pch_can_set_rx_buffer_link(priv, i, priv->rx_link[i - 1]);

		/* Restore buffer enables */
		pch_can_set_rxtx(priv, i, priv->rx_enable[i - 1], PCH_RX_IFREG);
	पूर्ण

	/* Enable CAN Interrupts */
	pch_can_set_पूर्णांक_custom(priv);

	/* Restore Run Mode */
	pch_can_set_run_mode(priv, PCH_CAN_RUN);

	वापस 0;
पूर्ण

अटल पूर्णांक pch_can_get_berr_counter(स्थिर काष्ठा net_device *dev,
				    काष्ठा can_berr_counter *bec)
अणु
	काष्ठा pch_can_priv *priv = netdev_priv(dev);
	u32 errc = ioपढ़ो32(&priv->regs->errc);

	bec->txerr = errc & PCH_TEC;
	bec->rxerr = (errc & PCH_REC) >> 8;

	वापस 0;
पूर्ण

अटल पूर्णांक pch_can_probe(काष्ठा pci_dev *pdev,
				   स्थिर काष्ठा pci_device_id *id)
अणु
	काष्ठा net_device *ndev;
	काष्ठा pch_can_priv *priv;
	पूर्णांक rc;
	व्योम __iomem *addr;

	rc = pci_enable_device(pdev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed pci_enable_device %d\n", rc);
		जाओ probe_निकास_endev;
	पूर्ण

	rc = pci_request_regions(pdev, KBUILD_MODNAME);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed pci_request_regions %d\n", rc);
		जाओ probe_निकास_pcireq;
	पूर्ण

	addr = pci_iomap(pdev, 1, 0);
	अगर (!addr) अणु
		rc = -EIO;
		dev_err(&pdev->dev, "Failed pci_iomap\n");
		जाओ probe_निकास_ipmap;
	पूर्ण

	ndev = alloc_candev(माप(काष्ठा pch_can_priv), PCH_TX_OBJ_END);
	अगर (!ndev) अणु
		rc = -ENOMEM;
		dev_err(&pdev->dev, "Failed alloc_candev\n");
		जाओ probe_निकास_alloc_candev;
	पूर्ण

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	priv->regs = addr;
	priv->dev = pdev;
	priv->can.bittiming_स्थिर = &pch_can_bittiming_स्थिर;
	priv->can.करो_set_mode = pch_can_करो_set_mode;
	priv->can.करो_get_berr_counter = pch_can_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LISTENONLY |
				       CAN_CTRLMODE_LOOPBACK;
	priv->tx_obj = PCH_TX_OBJ_START; /* Poपूर्णांक head of Tx Obj */

	ndev->irq = pdev->irq;
	ndev->flags |= IFF_ECHO;

	pci_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);
	ndev->netdev_ops = &pch_can_netdev_ops;
	priv->can.घड़ी.freq = PCH_CAN_CLK; /* Hz */

	netअगर_napi_add(ndev, &priv->napi, pch_can_poll, PCH_RX_OBJ_END);

	rc = pci_enable_msi(priv->dev);
	अगर (rc) अणु
		netdev_err(ndev, "PCH CAN opened without MSI\n");
		priv->use_msi = 0;
	पूर्ण अन्यथा अणु
		netdev_err(ndev, "PCH CAN opened with MSI\n");
		pci_set_master(pdev);
		priv->use_msi = 1;
	पूर्ण

	rc = रेजिस्टर_candev(ndev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Failed register_candev %d\n", rc);
		जाओ probe_निकास_reg_candev;
	पूर्ण

	वापस 0;

probe_निकास_reg_candev:
	अगर (priv->use_msi)
		pci_disable_msi(priv->dev);
	मुक्त_candev(ndev);
probe_निकास_alloc_candev:
	pci_iounmap(pdev, addr);
probe_निकास_ipmap:
	pci_release_regions(pdev);
probe_निकास_pcireq:
	pci_disable_device(pdev);
probe_निकास_endev:
	वापस rc;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pch_can_pm_ops,
			 pch_can_suspend,
			 pch_can_resume);

अटल काष्ठा pci_driver pch_can_pci_driver = अणु
	.name = "pch_can",
	.id_table = pch_pci_tbl,
	.probe = pch_can_probe,
	.हटाओ = pch_can_हटाओ,
	.driver.pm = &pch_can_pm_ops,
पूर्ण;

module_pci_driver(pch_can_pci_driver);

MODULE_DESCRIPTION("Intel EG20T PCH CAN(Controller Area Network) Driver");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("0.94");
