<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Conexant CX25821 PCIe bridge
 *
 *  Copyright (C) 2009 Conexant Systems Inc.
 *  Authors  <shu.lin@conexant.com>, <hiep.huynh@conexant.com>
 *  Based on Steven Toth <stoth@linuxtv.org> cx23885 driver
 */

#अगर_अघोषित CX25821_VIDEO_H_
#घोषणा CX25821_VIDEO_H_

#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kmod.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "cx25821.h"
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-event.h>

#घोषणा VIDEO_DEBUG 0

#घोषणा dprपूर्णांकk(level, fmt, arg...)					\
करो अणु									\
	अगर (VIDEO_DEBUG >= level)					\
		prपूर्णांकk(KERN_DEBUG "%s/0: " fmt, dev->name, ##arg);	\
पूर्ण जबतक (0)

#घोषणा FORMAT_FLAGS_PACKED       0x01
बाह्य व्योम cx25821_video_wakeup(काष्ठा cx25821_dev *dev,
				 काष्ठा cx25821_dmaqueue *q, u32 count);

बाह्य पूर्णांक cx25821_start_video_dma(काष्ठा cx25821_dev *dev,
				   काष्ठा cx25821_dmaqueue *q,
				   काष्ठा cx25821_buffer *buf,
				   स्थिर काष्ठा sram_channel *channel);

बाह्य पूर्णांक cx25821_video_irq(काष्ठा cx25821_dev *dev, पूर्णांक chan_num, u32 status);
बाह्य व्योम cx25821_video_unरेजिस्टर(काष्ठा cx25821_dev *dev, पूर्णांक chan_num);
बाह्य पूर्णांक cx25821_video_रेजिस्टर(काष्ठा cx25821_dev *dev);

#पूर्ण_अगर
