<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* drivers/media/platक्रमm/s5p-cec/s5p_cec.h
 *
 * Samsung S5P HDMI CEC driver
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 */

#अगर_अघोषित _S5P_CEC_H_
#घोषणा _S5P_CEC_H_ __खाता__

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/समयr.h>
#समावेश <linux/workqueue.h>
#समावेश <media/cec.h>

#समावेश "exynos_hdmi_cec.h"
#समावेश "regs-cec.h"
#समावेश "s5p_cec.h"

#घोषणा CEC_NAME	"s5p-cec"

#घोषणा CEC_STATUS_TX_RUNNING		(1 << 0)
#घोषणा CEC_STATUS_TX_TRANSFERRING	(1 << 1)
#घोषणा CEC_STATUS_TX_DONE		(1 << 2)
#घोषणा CEC_STATUS_TX_ERROR		(1 << 3)
#घोषणा CEC_STATUS_TX_NACK		(1 << 4)
#घोषणा CEC_STATUS_TX_BYTES		(0xFF << 8)
#घोषणा CEC_STATUS_RX_RUNNING		(1 << 16)
#घोषणा CEC_STATUS_RX_RECEIVING		(1 << 17)
#घोषणा CEC_STATUS_RX_DONE		(1 << 18)
#घोषणा CEC_STATUS_RX_ERROR		(1 << 19)
#घोषणा CEC_STATUS_RX_BCAST		(1 << 20)
#घोषणा CEC_STATUS_RX_BYTES		(0xFF << 24)

#घोषणा CEC_WORKER_TX_DONE		(1 << 0)
#घोषणा CEC_WORKER_RX_MSG		(1 << 1)

/* CEC Rx buffer size */
#घोषणा CEC_RX_BUFF_SIZE		16
/* CEC Tx buffer size */
#घोषणा CEC_TX_BUFF_SIZE		16

क्रमागत cec_state अणु
	STATE_IDLE,
	STATE_BUSY,
	STATE_DONE,
	STATE_NACK,
	STATE_ERROR
पूर्ण;

काष्ठा cec_notअगरier;

काष्ठा s5p_cec_dev अणु
	काष्ठा cec_adapter	*adap;
	काष्ठा clk		*clk;
	काष्ठा device		*dev;
	काष्ठा mutex		lock;
	काष्ठा regmap           *pmu;
	काष्ठा cec_notअगरier	*notअगरier;
	पूर्णांक			irq;
	व्योम __iomem		*reg;

	क्रमागत cec_state		rx;
	क्रमागत cec_state		tx;
	काष्ठा cec_msg		msg;
पूर्ण;

#पूर्ण_अगर /* _S5P_CEC_H_ */
