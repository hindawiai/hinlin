<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/iopoll.h>
#समावेश <linux/device.h>

#समावेश "lima_device.h"
#समावेश "lima_l2_cache.h"
#समावेश "lima_regs.h"

#घोषणा l2_cache_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा l2_cache_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

अटल पूर्णांक lima_l2_cache_रुको_idle(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;
	u32 v;

	err = पढ़ोl_poll_समयout(ip->iomem + LIMA_L2_CACHE_STATUS, v,
				 !(v & LIMA_L2_CACHE_STATUS_COMMAND_BUSY),
				 0, 1000);
	अगर (err) अणु
		dev_err(dev->dev, "l2 cache wait command timeout\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक lima_l2_cache_flush(काष्ठा lima_ip *ip)
अणु
	पूर्णांक ret;

	spin_lock(&ip->data.lock);
	l2_cache_ग_लिखो(LIMA_L2_CACHE_COMMAND, LIMA_L2_CACHE_COMMAND_CLEAR_ALL);
	ret = lima_l2_cache_रुको_idle(ip);
	spin_unlock(&ip->data.lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lima_l2_cache_hw_init(काष्ठा lima_ip *ip)
अणु
	पूर्णांक err;

	err = lima_l2_cache_flush(ip);
	अगर (err)
		वापस err;

	l2_cache_ग_लिखो(LIMA_L2_CACHE_ENABLE,
		       LIMA_L2_CACHE_ENABLE_ACCESS |
		       LIMA_L2_CACHE_ENABLE_READ_ALLOCATE);
	l2_cache_ग_लिखो(LIMA_L2_CACHE_MAX_READS, 0x1c);

	वापस 0;
पूर्ण

पूर्णांक lima_l2_cache_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_l2_cache_hw_init(ip);
पूर्ण

व्योम lima_l2_cache_suspend(काष्ठा lima_ip *ip)
अणु

पूर्ण

पूर्णांक lima_l2_cache_init(काष्ठा lima_ip *ip)
अणु
	पूर्णांक i;
	u32 size;
	काष्ठा lima_device *dev = ip->dev;

	/* l2_cache2 only exists when one of PP4-7 present */
	अगर (ip->id == lima_ip_l2_cache2) अणु
		क्रम (i = lima_ip_pp4; i <= lima_ip_pp7; i++) अणु
			अगर (dev->ip[i].present)
				अवरोध;
		पूर्ण
		अगर (i > lima_ip_pp7)
			वापस -ENODEV;
	पूर्ण

	spin_lock_init(&ip->data.lock);

	size = l2_cache_पढ़ो(LIMA_L2_CACHE_SIZE);
	dev_info(dev->dev, "l2 cache %uK, %u-way, %ubyte cache line, %ubit external bus\n",
		 1 << (((size >> 16) & 0xff) - 10),
		 1 << ((size >> 8) & 0xff),
		 1 << (size & 0xff),
		 1 << ((size >> 24) & 0xff));

	वापस lima_l2_cache_hw_init(ip);
पूर्ण

व्योम lima_l2_cache_fini(काष्ठा lima_ip *ip)
अणु

पूर्ण
