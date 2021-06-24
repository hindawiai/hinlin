<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  Infrared device support routines - non-input, non-vl42_subdev routines
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-ir.h"
#समावेश "cx23885-input.h"

#समावेश <media/v4l2-device.h>

#घोषणा CX23885_IR_RX_FIFO_SERVICE_REQ		0
#घोषणा CX23885_IR_RX_END_OF_RX_DETECTED	1
#घोषणा CX23885_IR_RX_HW_FIFO_OVERRUN		2
#घोषणा CX23885_IR_RX_SW_FIFO_OVERRUN		3

#घोषणा CX23885_IR_TX_FIFO_SERVICE_REQ		0


व्योम cx23885_ir_rx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx23885_dev *dev =
			     container_of(work, काष्ठा cx23885_dev, ir_rx_work);
	u32 events = 0;
	अचिन्हित दीर्घ *notअगरications = &dev->ir_rx_notअगरications;

	अगर (test_and_clear_bit(CX23885_IR_RX_SW_FIFO_OVERRUN, notअगरications))
		events |= V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN;
	अगर (test_and_clear_bit(CX23885_IR_RX_HW_FIFO_OVERRUN, notअगरications))
		events |= V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN;
	अगर (test_and_clear_bit(CX23885_IR_RX_END_OF_RX_DETECTED, notअगरications))
		events |= V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED;
	अगर (test_and_clear_bit(CX23885_IR_RX_FIFO_SERVICE_REQ, notअगरications))
		events |= V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ;

	अगर (events == 0)
		वापस;

	अगर (dev->kernel_ir)
		cx23885_input_rx_work_handler(dev, events);
पूर्ण

व्योम cx23885_ir_tx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx23885_dev *dev =
			     container_of(work, काष्ठा cx23885_dev, ir_tx_work);
	u32 events = 0;
	अचिन्हित दीर्घ *notअगरications = &dev->ir_tx_notअगरications;

	अगर (test_and_clear_bit(CX23885_IR_TX_FIFO_SERVICE_REQ, notअगरications))
		events |= V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ;

	अगर (events == 0)
		वापस;

पूर्ण

/* Possibly called in an IRQ context */
व्योम cx23885_ir_rx_v4l2_dev_notअगरy(काष्ठा v4l2_subdev *sd, u32 events)
अणु
	काष्ठा cx23885_dev *dev = to_cx23885(sd->v4l2_dev);
	अचिन्हित दीर्घ *notअगरications = &dev->ir_rx_notअगरications;

	अगर (events & V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ)
		set_bit(CX23885_IR_RX_FIFO_SERVICE_REQ, notअगरications);
	अगर (events & V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED)
		set_bit(CX23885_IR_RX_END_OF_RX_DETECTED, notअगरications);
	अगर (events & V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN)
		set_bit(CX23885_IR_RX_HW_FIFO_OVERRUN, notअगरications);
	अगर (events & V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN)
		set_bit(CX23885_IR_RX_SW_FIFO_OVERRUN, notअगरications);

	/*
	 * For the पूर्णांकegrated AV core, we are alपढ़ोy in a workqueue context.
	 * For the CX23888 पूर्णांकegrated IR, we are in an पूर्णांकerrupt context.
	 */
	अगर (sd == dev->sd_cx25840)
		cx23885_ir_rx_work_handler(&dev->ir_rx_work);
	अन्यथा
		schedule_work(&dev->ir_rx_work);
पूर्ण

/* Possibly called in an IRQ context */
व्योम cx23885_ir_tx_v4l2_dev_notअगरy(काष्ठा v4l2_subdev *sd, u32 events)
अणु
	काष्ठा cx23885_dev *dev = to_cx23885(sd->v4l2_dev);
	अचिन्हित दीर्घ *notअगरications = &dev->ir_tx_notअगरications;

	अगर (events & V4L2_SUBDEV_IR_TX_FIFO_SERVICE_REQ)
		set_bit(CX23885_IR_TX_FIFO_SERVICE_REQ, notअगरications);

	/*
	 * For the पूर्णांकegrated AV core, we are alपढ़ोy in a workqueue context.
	 * For the CX23888 पूर्णांकegrated IR, we are in an पूर्णांकerrupt context.
	 */
	अगर (sd == dev->sd_cx25840)
		cx23885_ir_tx_work_handler(&dev->ir_tx_work);
	अन्यथा
		schedule_work(&dev->ir_tx_work);
पूर्ण
