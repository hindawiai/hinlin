<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/pci.h>

#समावेश <drm/drm_irq.h>

#समावेश "qxl_drv.h"

irqवापस_t qxl_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	काष्ठा qxl_device *qdev = to_qxl(dev);
	uपूर्णांक32_t pending;

	pending = xchg(&qdev->ram_header->पूर्णांक_pending, 0);

	अगर (!pending)
		वापस IRQ_NONE;

	atomic_inc(&qdev->irq_received);

	अगर (pending & QXL_INTERRUPT_DISPLAY) अणु
		atomic_inc(&qdev->irq_received_display);
		wake_up_all(&qdev->display_event);
		qxl_queue_garbage_collect(qdev, false);
	पूर्ण
	अगर (pending & QXL_INTERRUPT_CURSOR) अणु
		atomic_inc(&qdev->irq_received_cursor);
		wake_up_all(&qdev->cursor_event);
	पूर्ण
	अगर (pending & QXL_INTERRUPT_IO_CMD) अणु
		atomic_inc(&qdev->irq_received_io_cmd);
		wake_up_all(&qdev->io_cmd_event);
	पूर्ण
	अगर (pending & QXL_INTERRUPT_ERROR) अणु
		/* TODO: log it, reset device (only way to निकास this condition)
		 * (करो it a certain number of बार, afterwards admit defeat,
		 * to aव्योम endless loops).
		 */
		qdev->irq_received_error++;
		DRM_WARN("driver is in bug mode\n");
	पूर्ण
	अगर (pending & QXL_INTERRUPT_CLIENT_MONITORS_CONFIG) अणु
		schedule_work(&qdev->client_monitors_config_work);
	पूर्ण
	qdev->ram_header->पूर्णांक_mask = QXL_INTERRUPT_MASK;
	outb(0, qdev->io_base + QXL_IO_UPDATE_IRQ);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम qxl_client_monitors_config_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qxl_device *qdev = container_of(work, काष्ठा qxl_device,
					       client_monitors_config_work);

	qxl_display_पढ़ो_client_monitors_config(qdev);
पूर्ण

पूर्णांक qxl_irq_init(काष्ठा qxl_device *qdev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(qdev->ddev.dev);
	पूर्णांक ret;

	init_रुकोqueue_head(&qdev->display_event);
	init_रुकोqueue_head(&qdev->cursor_event);
	init_रुकोqueue_head(&qdev->io_cmd_event);
	init_रुकोqueue_head(&qdev->release_event);
	INIT_WORK(&qdev->client_monitors_config_work,
		  qxl_client_monitors_config_work_func);
	atomic_set(&qdev->irq_received, 0);
	atomic_set(&qdev->irq_received_display, 0);
	atomic_set(&qdev->irq_received_cursor, 0);
	atomic_set(&qdev->irq_received_io_cmd, 0);
	qdev->irq_received_error = 0;
	ret = drm_irq_install(&qdev->ddev, pdev->irq);
	qdev->ram_header->पूर्णांक_mask = QXL_INTERRUPT_MASK;
	अगर (unlikely(ret != 0)) अणु
		DRM_ERROR("Failed installing irq: %d\n", ret);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण
