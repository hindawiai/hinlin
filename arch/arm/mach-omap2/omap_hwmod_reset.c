<शैली गुरु>
/*
 * OMAP IP block custom reset and preprogramming stubs
 *
 * Copyright (C) 2012 Texas Instruments, Inc.
 * Paul Walmsley
 *
 * A small number of IP blocks need custom reset and preprogramming
 * functions.  The stubs in this file provide a standard way क्रम the
 * hwmod code to call these functions, which are to be located under
 * drivers/.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA
 * 02110-1301 USA
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश "omap_hwmod.h"
#समावेश "common.h"

#घोषणा OMAP_RTC_STATUS_REG	0x44
#घोषणा OMAP_RTC_KICK0_REG	0x6c
#घोषणा OMAP_RTC_KICK1_REG	0x70

#घोषणा OMAP_RTC_KICK0_VALUE	0x83E70B13
#घोषणा OMAP_RTC_KICK1_VALUE	0x95A4F1E0
#घोषणा OMAP_RTC_STATUS_BUSY	BIT(0)
#घोषणा OMAP_RTC_MAX_READY_TIME	50

/**
 * omap_rtc_रुको_not_busy - Wait क्रम the RTC BUSY flag
 * @oh: काष्ठा omap_hwmod *
 *
 * For updating certain RTC रेजिस्टरs, the MPU must रुको
 * क्रम the BUSY status in OMAP_RTC_STATUS_REG to become zero.
 * Once the BUSY status is zero, there is a 15 microseconds access
 * period in which the MPU can program.
 */
अटल व्योम omap_rtc_रुको_not_busy(काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक i;

	/* BUSY may stay active क्रम 1/32768 second (~30 usec) */
	omap_test_समयout(omap_hwmod_पढ़ो(oh, OMAP_RTC_STATUS_REG)
			  & OMAP_RTC_STATUS_BUSY, OMAP_RTC_MAX_READY_TIME, i);
	/* now we have ~15 microseconds to पढ़ो/ग_लिखो various रेजिस्टरs */
पूर्ण

/**
 * omap_hwmod_rtc_unlock - Unlock the Kicker mechanism.
 * @oh: काष्ठा omap_hwmod *
 *
 * RTC IP have kicker feature. This prevents spurious ग_लिखोs to its रेजिस्टरs.
 * In order to ग_लिखो पूर्णांकo any of the RTC रेजिस्टरs, KICK values has te be
 * written in respective KICK रेजिस्टरs. This is needed क्रम hwmod to ग_लिखो पूर्णांकo
 * sysconfig रेजिस्टर.
 */
व्योम omap_hwmod_rtc_unlock(काष्ठा omap_hwmod *oh)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	omap_rtc_रुको_not_busy(oh);
	omap_hwmod_ग_लिखो(OMAP_RTC_KICK0_VALUE, oh, OMAP_RTC_KICK0_REG);
	omap_hwmod_ग_लिखो(OMAP_RTC_KICK1_VALUE, oh, OMAP_RTC_KICK1_REG);
	local_irq_restore(flags);
पूर्ण

/**
 * omap_hwmod_rtc_lock - Lock the Kicker mechanism.
 * @oh: काष्ठा omap_hwmod *
 *
 * RTC IP have kicker feature. This prevents spurious ग_लिखोs to its रेजिस्टरs.
 * Once the RTC रेजिस्टरs are written, KICK mechanism needs to be locked,
 * in order to prevent any spurious ग_लिखोs. This function locks back the RTC
 * रेजिस्टरs once hwmod completes its ग_लिखो पूर्णांकo sysconfig रेजिस्टर.
 */
व्योम omap_hwmod_rtc_lock(काष्ठा omap_hwmod *oh)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	omap_rtc_रुको_not_busy(oh);
	omap_hwmod_ग_लिखो(0x0, oh, OMAP_RTC_KICK0_REG);
	omap_hwmod_ग_लिखो(0x0, oh, OMAP_RTC_KICK1_REG);
	local_irq_restore(flags);
पूर्ण
