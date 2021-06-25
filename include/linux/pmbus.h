<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Hardware monitoring driver क्रम PMBus devices
 *
 * Copyright (c) 2010, 2011 Ericsson AB.
 */

#अगर_अघोषित _PMBUS_H_
#घोषणा _PMBUS_H_

#समावेश <linux/bits.h>

/* flags */

/*
 * PMBUS_SKIP_STATUS_CHECK
 *
 * During रेजिस्टर detection, skip checking the status रेजिस्टर क्रम
 * communication or command errors.
 *
 * Some PMBus chips respond with valid data when trying to पढ़ो an unsupported
 * रेजिस्टर. For such chips, checking the status रेजिस्टर is mandatory when
 * trying to determine अगर a chip रेजिस्टर exists or not.
 * Other PMBus chips करोn't support the STATUS_CML रेजिस्टर, or report
 * communication errors क्रम no explicable reason. For such chips, checking
 * the status रेजिस्टर must be disabled.
 */
#घोषणा PMBUS_SKIP_STATUS_CHECK	BIT(0)

/*
 * PMBUS_WRITE_PROTECTED
 * Set अगर the chip is ग_लिखो रक्षित and ग_लिखो protection is not determined
 * by the standard WRITE_PROTECT command.
 */
#घोषणा PMBUS_WRITE_PROTECTED	BIT(1)

/*
 * PMBUS_NO_CAPABILITY
 *
 * Some PMBus chips करोn't respond with valid data when पढ़ोing the CAPABILITY
 * रेजिस्टर. For such chips, this flag should be set so that the PMBus core
 * driver करोesn't use CAPABILITY to determine it's behavior.
 */
#घोषणा PMBUS_NO_CAPABILITY			BIT(2)

काष्ठा pmbus_platक्रमm_data अणु
	u32 flags;		/* Device specअगरic flags */

	/* regulator support */
	पूर्णांक num_regulators;
	काष्ठा regulator_init_data *reg_init_data;
पूर्ण;

#पूर्ण_अगर /* _PMBUS_H_ */
