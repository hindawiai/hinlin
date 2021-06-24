<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* CAN bus driver क्रम Bosch M_CAN controller
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 */

#अगर_अघोषित _CAN_M_CAN_H_
#घोषणा _CAN_M_CAN_H_

#समावेश <linux/can/core.h>
#समावेश <linux/can/led.h>
#समावेश <linux/can/rx-offload.h>
#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/can/dev.h>
#समावेश <linux/pinctrl/consumer.h>

/* m_can lec values */
क्रमागत m_can_lec_type अणु
	LEC_NO_ERROR = 0,
	LEC_STUFF_ERROR,
	LEC_FORM_ERROR,
	LEC_ACK_ERROR,
	LEC_BIT1_ERROR,
	LEC_BIT0_ERROR,
	LEC_CRC_ERROR,
	LEC_UNUSED,
पूर्ण;

क्रमागत m_can_mram_cfg अणु
	MRAM_SIDF = 0,
	MRAM_XIDF,
	MRAM_RXF0,
	MRAM_RXF1,
	MRAM_RXB,
	MRAM_TXE,
	MRAM_TXB,
	MRAM_CFG_NUM,
पूर्ण;

/* address offset and element number क्रम each FIFO/Buffer in the Message RAM */
काष्ठा mram_cfg अणु
	u16 off;
	u8  num;
पूर्ण;

काष्ठा m_can_classdev;
काष्ठा m_can_ops अणु
	/* Device specअगरic call backs */
	पूर्णांक (*clear_पूर्णांकerrupts)(काष्ठा m_can_classdev *cdev);
	u32 (*पढ़ो_reg)(काष्ठा m_can_classdev *cdev, पूर्णांक reg);
	पूर्णांक (*ग_लिखो_reg)(काष्ठा m_can_classdev *cdev, पूर्णांक reg, पूर्णांक val);
	u32 (*पढ़ो_fअगरo)(काष्ठा m_can_classdev *cdev, पूर्णांक addr_offset);
	पूर्णांक (*ग_लिखो_fअगरo)(काष्ठा m_can_classdev *cdev, पूर्णांक addr_offset,
			  पूर्णांक val);
	पूर्णांक (*init)(काष्ठा m_can_classdev *cdev);
पूर्ण;

काष्ठा m_can_classdev अणु
	काष्ठा can_priv can;
	काष्ठा can_rx_offload offload;
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *net;
	काष्ठा device *dev;
	काष्ठा clk *hclk;
	काष्ठा clk *cclk;

	काष्ठा workqueue_काष्ठा *tx_wq;
	काष्ठा work_काष्ठा tx_work;
	काष्ठा sk_buff *tx_skb;

	काष्ठा can_bittiming_स्थिर *bit_timing;
	काष्ठा can_bittiming_स्थिर *data_timing;

	काष्ठा m_can_ops *ops;

	पूर्णांक version;
	u32 irqstatus;

	पूर्णांक pm_घड़ी_support;
	पूर्णांक is_peripheral;

	काष्ठा mram_cfg mcfg[MRAM_CFG_NUM];
पूर्ण;

काष्ठा m_can_classdev *m_can_class_allocate_dev(काष्ठा device *dev, पूर्णांक माप_priv);
व्योम m_can_class_मुक्त_dev(काष्ठा net_device *net);
पूर्णांक m_can_class_रेजिस्टर(काष्ठा m_can_classdev *cdev);
व्योम m_can_class_unरेजिस्टर(काष्ठा m_can_classdev *cdev);
पूर्णांक m_can_class_get_घड़ीs(काष्ठा m_can_classdev *cdev);
व्योम m_can_init_ram(काष्ठा m_can_classdev *priv);

पूर्णांक m_can_class_suspend(काष्ठा device *dev);
पूर्णांक m_can_class_resume(काष्ठा device *dev);
#पूर्ण_अगर	/* _CAN_M_H_ */
