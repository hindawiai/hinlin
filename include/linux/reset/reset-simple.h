<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Simple Reset Controller ops
 *
 * Based on Allwinner SoCs Reset Controller driver
 *
 * Copyright 2013 Maxime Ripard
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#अगर_अघोषित __RESET_SIMPLE_H__
#घोषणा __RESET_SIMPLE_H__

#समावेश <linux/पन.स>
#समावेश <linux/reset-controller.h>
#समावेश <linux/spinlock.h>

/**
 * काष्ठा reset_simple_data - driver data क्रम simple reset controllers
 * @lock: spinlock to protect रेजिस्टरs during पढ़ो-modअगरy-ग_लिखो cycles
 * @membase: memory mapped I/O रेजिस्टर range
 * @rcdev: reset controller device base काष्ठाure
 * @active_low: अगर true, bits are cleared to निश्चित the reset. Otherwise, bits
 *              are set to निश्चित the reset. Note that this says nothing about
 *              the voltage level of the actual reset line.
 * @status_active_low: अगर true, bits पढ़ो back as cleared जबतक the reset is
 *                     निश्चितed. Otherwise, bits पढ़ो back as set जबतक the
 *                     reset is निश्चितed.
 * @reset_us: Minimum delay in microseconds needed that needs to be
 *            रुकोed क्रम between an निश्चित and a deनिश्चित to reset the
 *            device. If multiple consumers with dअगरferent delay
 *            requirements are connected to this controller, it must
 *            be the largest minimum delay. 0 means that such a delay is
 *            unknown and the reset operation is unsupported.
 */
काष्ठा reset_simple_data अणु
	spinlock_t			lock;
	व्योम __iomem			*membase;
	काष्ठा reset_controller_dev	rcdev;
	bool				active_low;
	bool				status_active_low;
	अचिन्हित पूर्णांक			reset_us;
पूर्ण;

बाह्य स्थिर काष्ठा reset_control_ops reset_simple_ops;

#पूर्ण_अगर /* __RESET_SIMPLE_H__ */
