<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_LIMIT_H
#घोषणा __LINUX_BRIDGE_EBT_LIMIT_H

#समावेश <linux/types.h>

#घोषणा EBT_LIMIT_MATCH "limit"

/* timings are in milliseconds. */
#घोषणा EBT_LIMIT_SCALE 10000

/* 1/10,000 sec period => max of 10,000/sec.  Min rate is then 429490
   seconds, or one every 59 hours. */

काष्ठा ebt_limit_info अणु
	__u32 avg;    /* Average secs between packets * scale */
	__u32 burst;  /* Period multiplier क्रम upper limit. */

	/* Used पूर्णांकernally by the kernel */
	अचिन्हित दीर्घ prev;
	__u32 credit;
	__u32 credit_cap, cost;
पूर्ण;

#पूर्ण_अगर
