<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2014 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _LINUX_IOPOLL_H
#घोषणा _LINUX_IOPOLL_H

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>

/**
 * पढ़ो_poll_समयout - Periodically poll an address until a condition is
 *			met or a समयout occurs
 * @op: accessor function (takes @args as its arguments)
 * @val: Variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 * @sleep_beक्रमe_पढ़ो: अगर it is true, sleep @sleep_us beक्रमe पढ़ो.
 * @args: arguments क्रम @op poll
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @args is stored in @val. Must not
 * be called from atomic context अगर sleep_us or समयout_us are used.
 *
 * When available, you'll probably want to use one of the specialized
 * macros defined below rather than this macro directly.
 */
#घोषणा पढ़ो_poll_समयout(op, val, cond, sleep_us, समयout_us, \
				sleep_beक्रमe_पढ़ो, args...) \
(अणु \
	u64 __समयout_us = (समयout_us); \
	अचिन्हित दीर्घ __sleep_us = (sleep_us); \
	kसमय_प्रकार __समयout = kसमय_add_us(kसमय_get(), __समयout_us); \
	might_sleep_अगर((__sleep_us) != 0); \
	अगर (sleep_beक्रमe_पढ़ो && __sleep_us) \
		usleep_range((__sleep_us >> 2) + 1, __sleep_us); \
	क्रम (;;) अणु \
		(val) = op(args); \
		अगर (cond) \
			अवरोध; \
		अगर (__समयout_us && \
		    kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = op(args); \
			अवरोध; \
		पूर्ण \
		अगर (__sleep_us) \
			usleep_range((__sleep_us >> 2) + 1, __sleep_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

/**
 * पढ़ो_poll_समयout_atomic - Periodically poll an address until a condition is
 * 				met or a समयout occurs
 * @op: accessor function (takes @args as its arguments)
 * @val: Variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @delay_us: Time to udelay between पढ़ोs in us (0 tight-loops).  Should
 *            be less than ~10us since udelay is used (see
 *            Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 * @delay_beक्रमe_पढ़ो: अगर it is true, delay @delay_us beक्रमe पढ़ो.
 * @args: arguments क्रम @op poll
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @args is stored in @val.
 *
 * When available, you'll probably want to use one of the specialized
 * macros defined below rather than this macro directly.
 */
#घोषणा पढ़ो_poll_समयout_atomic(op, val, cond, delay_us, समयout_us, \
					delay_beक्रमe_पढ़ो, args...) \
(अणु \
	u64 __समयout_us = (समयout_us); \
	अचिन्हित दीर्घ __delay_us = (delay_us); \
	kसमय_प्रकार __समयout = kसमय_add_us(kसमय_get(), __समयout_us); \
	अगर (delay_beक्रमe_पढ़ो && __delay_us) \
		udelay(__delay_us); \
	क्रम (;;) अणु \
		(val) = op(args); \
		अगर (cond) \
			अवरोध; \
		अगर (__समयout_us && \
		    kसमय_compare(kसमय_get(), __समयout) > 0) अणु \
			(val) = op(args); \
			अवरोध; \
		पूर्ण \
		अगर (__delay_us) \
			udelay(__delay_us); \
	पूर्ण \
	(cond) ? 0 : -ETIMEDOUT; \
पूर्ण)

/**
 * पढ़ोx_poll_समयout - Periodically poll an address until a condition is met or a समयout occurs
 * @op: accessor function (takes @addr as its only argument)
 * @addr: Address to poll
 * @val: Variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @sleep_us: Maximum समय to sleep between पढ़ोs in us (0
 *            tight-loops).  Should be less than ~20ms since usleep_range
 *            is used (see Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @addr is stored in @val. Must not
 * be called from atomic context अगर sleep_us or समयout_us are used.
 *
 * When available, you'll probably want to use one of the specialized
 * macros defined below rather than this macro directly.
 */
#घोषणा पढ़ोx_poll_समयout(op, addr, val, cond, sleep_us, समयout_us)	\
	पढ़ो_poll_समयout(op, val, cond, sleep_us, समयout_us, false, addr)

/**
 * पढ़ोx_poll_समयout_atomic - Periodically poll an address until a condition is met or a समयout occurs
 * @op: accessor function (takes @addr as its only argument)
 * @addr: Address to poll
 * @val: Variable to पढ़ो the value पूर्णांकo
 * @cond: Break condition (usually involving @val)
 * @delay_us: Time to udelay between पढ़ोs in us (0 tight-loops).  Should
 *            be less than ~10us since udelay is used (see
 *            Documentation/समयrs/समयrs-howto.rst).
 * @समयout_us: Timeout in us, 0 means never समयout
 *
 * Returns 0 on success and -ETIMEDOUT upon a समयout. In either
 * हाल, the last पढ़ो value at @addr is stored in @val.
 *
 * When available, you'll probably want to use one of the specialized
 * macros defined below rather than this macro directly.
 */
#घोषणा पढ़ोx_poll_समयout_atomic(op, addr, val, cond, delay_us, समयout_us) \
	पढ़ो_poll_समयout_atomic(op, val, cond, delay_us, समयout_us, false, addr)

#घोषणा पढ़ोb_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोb, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोb_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोb, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोw_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोw, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोw_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोw, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोl_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोl, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोl_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोl, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोq_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोq, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोq_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोq, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोb_relaxed_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोb_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोb_relaxed_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोb_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोw_relaxed_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोw_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोw_relaxed_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोw_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोl_relaxed_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोl_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोl_relaxed_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोl_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोq_relaxed_poll_समयout(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout(पढ़ोq_relaxed, addr, val, cond, delay_us, समयout_us)

#घोषणा पढ़ोq_relaxed_poll_समयout_atomic(addr, val, cond, delay_us, समयout_us) \
	पढ़ोx_poll_समयout_atomic(पढ़ोq_relaxed, addr, val, cond, delay_us, समयout_us)

#पूर्ण_अगर /* _LINUX_IOPOLL_H */
