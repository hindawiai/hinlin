<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the Conexant CX23885/7/8 PCIe bridge
 *
 *  AV device support routines - non-input, non-vl42_subdev routines
 *
 *  Copyright (C) 2010  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx23885.h"
#समावेश "cx23885-av.h"
#समावेश "cx23885-video.h"

व्योम cx23885_av_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cx23885_dev *dev =
			   container_of(work, काष्ठा cx23885_dev, cx25840_work);
	bool handled = false;

	v4l2_subdev_call(dev->sd_cx25840, core, पूर्णांकerrupt_service_routine,
			 PCI_MSK_AV_CORE, &handled);

	/* Getting here with the पूर्णांकerrupt not handled
	   then probbaly flatiron करोes have pending पूर्णांकerrupts.
	*/
	अगर (!handled) अणु
		/* clear left and right adc channel पूर्णांकerrupt request flag */
		cx23885_flatiron_ग_लिखो(dev, 0x1f,
			cx23885_flatiron_पढ़ो(dev, 0x1f) | 0x80);
		cx23885_flatiron_ग_लिखो(dev, 0x23,
			cx23885_flatiron_पढ़ो(dev, 0x23) | 0x80);
	पूर्ण

	cx23885_irq_enable(dev, PCI_MSK_AV_CORE);
पूर्ण
