<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ChromeOS Embedded Controller core पूर्णांकerface.
 *
 * Copyright (C) 2020 Google LLC
 */

#अगर_अघोषित __CROS_EC_H
#घोषणा __CROS_EC_H

#समावेश <linux/पूर्णांकerrupt.h>

पूर्णांक cros_ec_रेजिस्टर(काष्ठा cros_ec_device *ec_dev);
पूर्णांक cros_ec_unरेजिस्टर(काष्ठा cros_ec_device *ec_dev);

पूर्णांक cros_ec_suspend(काष्ठा cros_ec_device *ec_dev);
पूर्णांक cros_ec_resume(काष्ठा cros_ec_device *ec_dev);

irqवापस_t cros_ec_irq_thपढ़ो(पूर्णांक irq, व्योम *data);

#पूर्ण_अगर /* __CROS_EC_H */
