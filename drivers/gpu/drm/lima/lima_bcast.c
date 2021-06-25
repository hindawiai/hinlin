<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/पन.स>
#समावेश <linux/device.h>

#समावेश "lima_device.h"
#समावेश "lima_bcast.h"
#समावेश "lima_regs.h"

#घोषणा bcast_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा bcast_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

व्योम lima_bcast_enable(काष्ठा lima_device *dev, पूर्णांक num_pp)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	काष्ठा lima_ip *ip = dev->ip + lima_ip_bcast;
	पूर्णांक i, mask = bcast_पढ़ो(LIMA_BCAST_BROADCAST_MASK) & 0xffff0000;

	क्रम (i = 0; i < num_pp; i++) अणु
		काष्ठा lima_ip *pp = pipe->processor[i];

		mask |= 1 << (pp->id - lima_ip_pp0);
	पूर्ण

	bcast_ग_लिखो(LIMA_BCAST_BROADCAST_MASK, mask);
पूर्ण

अटल पूर्णांक lima_bcast_hw_init(काष्ठा lima_ip *ip)
अणु
	bcast_ग_लिखो(LIMA_BCAST_BROADCAST_MASK, ip->data.mask << 16);
	bcast_ग_लिखो(LIMA_BCAST_INTERRUPT_MASK, ip->data.mask);
	वापस 0;
पूर्ण

पूर्णांक lima_bcast_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_bcast_hw_init(ip);
पूर्ण

व्योम lima_bcast_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_bcast_init(काष्ठा lima_ip *ip)
अणु
	पूर्णांक i;

	क्रम (i = lima_ip_pp0; i <= lima_ip_pp7; i++) अणु
		अगर (ip->dev->ip[i].present)
			ip->data.mask |= 1 << (i - lima_ip_pp0);
	पूर्ण

	वापस lima_bcast_hw_init(ip);
पूर्ण

व्योम lima_bcast_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण

