<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/पन.स>
#समावेश <linux/device.h>

#समावेश "lima_device.h"
#समावेश "lima_dlbu.h"
#समावेश "lima_vm.h"
#समावेश "lima_regs.h"

#घोषणा dlbu_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा dlbu_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

व्योम lima_dlbu_enable(काष्ठा lima_device *dev, पूर्णांक num_pp)
अणु
	काष्ठा lima_sched_pipe *pipe = dev->pipe + lima_pipe_pp;
	काष्ठा lima_ip *ip = dev->ip + lima_ip_dlbu;
	पूर्णांक i, mask = 0;

	क्रम (i = 0; i < num_pp; i++) अणु
		काष्ठा lima_ip *pp = pipe->processor[i];

		mask |= 1 << (pp->id - lima_ip_pp0);
	पूर्ण

	dlbu_ग_लिखो(LIMA_DLBU_PP_ENABLE_MASK, mask);
पूर्ण

व्योम lima_dlbu_disable(काष्ठा lima_device *dev)
अणु
	काष्ठा lima_ip *ip = dev->ip + lima_ip_dlbu;

	dlbu_ग_लिखो(LIMA_DLBU_PP_ENABLE_MASK, 0);
पूर्ण

व्योम lima_dlbu_set_reg(काष्ठा lima_ip *ip, u32 *reg)
अणु
	dlbu_ग_लिखो(LIMA_DLBU_TLLIST_VBASEADDR, reg[0]);
	dlbu_ग_लिखो(LIMA_DLBU_FB_DIM, reg[1]);
	dlbu_ग_लिखो(LIMA_DLBU_TLLIST_CONF, reg[2]);
	dlbu_ग_लिखो(LIMA_DLBU_START_TILE_POS, reg[3]);
पूर्ण

अटल पूर्णांक lima_dlbu_hw_init(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;

	dlbu_ग_लिखो(LIMA_DLBU_MASTER_TLLIST_PHYS_ADDR, dev->dlbu_dma | 1);
	dlbu_ग_लिखो(LIMA_DLBU_MASTER_TLLIST_VADDR, LIMA_VA_RESERVE_DLBU);

	वापस 0;
पूर्ण

पूर्णांक lima_dlbu_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_dlbu_hw_init(ip);
पूर्ण

व्योम lima_dlbu_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_dlbu_init(काष्ठा lima_ip *ip)
अणु
	वापस lima_dlbu_hw_init(ip);
पूर्ण

व्योम lima_dlbu_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण
