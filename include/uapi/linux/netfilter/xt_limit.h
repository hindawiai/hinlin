<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_RATE_H
#घोषणा _XT_RATE_H

#समावेश <linux/types.h>

/* timings are in milliseconds. */
#घोषणा XT_LIMIT_SCALE 10000

काष्ठा xt_limit_priv;

/* 1/10,000 sec period => max of 10,000/sec.  Min rate is then 429490
   seconds, or one every 59 hours. */
काष्ठा xt_rateinfo अणु
	__u32 avg;    /* Average secs between packets * scale */
	__u32 burst;  /* Period multiplier क्रम upper limit. */

	/* Used पूर्णांकernally by the kernel */
	अचिन्हित दीर्घ prev; /* moved to xt_limit_priv */
	__u32 credit; /* moved to xt_limit_priv */
	__u32 credit_cap, cost;

	काष्ठा xt_limit_priv *master;
पूर्ण;
#पूर्ण_अगर /*_XT_RATE_H*/
