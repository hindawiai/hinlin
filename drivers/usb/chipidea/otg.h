<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2013-2014 Freescale Semiconductor, Inc.
 *
 * Author: Peter Chen
 */

#अगर_अघोषित __DRIVERS_USB_CHIPIDEA_OTG_H
#घोषणा __DRIVERS_USB_CHIPIDEA_OTG_H

u32 hw_पढ़ो_otgsc(काष्ठा ci_hdrc *ci, u32 mask);
व्योम hw_ग_लिखो_otgsc(काष्ठा ci_hdrc *ci, u32 mask, u32 data);
पूर्णांक ci_hdrc_otg_init(काष्ठा ci_hdrc *ci);
व्योम ci_hdrc_otg_destroy(काष्ठा ci_hdrc *ci);
क्रमागत ci_role ci_otg_role(काष्ठा ci_hdrc *ci);
व्योम ci_handle_vbus_change(काष्ठा ci_hdrc *ci);
अटल अंतरभूत व्योम ci_otg_queue_work(काष्ठा ci_hdrc *ci)
अणु
	disable_irq_nosync(ci->irq);
	अगर (queue_work(ci->wq, &ci->work) == false)
		enable_irq(ci->irq);
पूर्ण

#पूर्ण_अगर /* __DRIVERS_USB_CHIPIDEA_OTG_H */
