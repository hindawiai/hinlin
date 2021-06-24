<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cec-pin.h - low-level CEC pin control
 *
 * Copyright 2017 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित LINUX_CEC_PIN_H
#घोषणा LINUX_CEC_PIN_H

#समावेश <linux/types.h>
#समावेश <media/cec.h>

/**
 * काष्ठा cec_pin_ops - low-level CEC pin operations
 * @पढ़ो:	पढ़ो the CEC pin. Returns > 0 अगर high, 0 अगर low, or an error
 *		अगर negative.
 * @low:	drive the CEC pin low.
 * @high:	stop driving the CEC pin. The pull-up will drive the pin
 *		high, unless someone अन्यथा is driving the pin low.
 * @enable_irq:	optional, enable the पूर्णांकerrupt to detect pin voltage changes.
 * @disable_irq: optional, disable the पूर्णांकerrupt.
 * @मुक्त:	optional. Free any allocated resources. Called when the
 *		adapter is deleted.
 * @status:	optional, log status inक्रमmation.
 * @पढ़ो_hpd:	optional. Read the HPD pin. Returns > 0 अगर high, 0 अगर low or
 *		an error अगर negative.
 * @पढ़ो_5v:	optional. Read the 5V pin. Returns > 0 अगर high, 0 अगर low or
 *		an error अगर negative.
 * @received:	optional. High-level CEC message callback. Allows the driver
 *		to process CEC messages.
 *
 * These operations (except क्रम the @received op) are used by the
 * cec pin framework to manipulate the CEC pin.
 */
काष्ठा cec_pin_ops अणु
	पूर्णांक  (*पढ़ो)(काष्ठा cec_adapter *adap);
	व्योम (*low)(काष्ठा cec_adapter *adap);
	व्योम (*high)(काष्ठा cec_adapter *adap);
	bool (*enable_irq)(काष्ठा cec_adapter *adap);
	व्योम (*disable_irq)(काष्ठा cec_adapter *adap);
	व्योम (*मुक्त)(काष्ठा cec_adapter *adap);
	व्योम (*status)(काष्ठा cec_adapter *adap, काष्ठा seq_file *file);
	पूर्णांक  (*पढ़ो_hpd)(काष्ठा cec_adapter *adap);
	पूर्णांक  (*पढ़ो_5v)(काष्ठा cec_adapter *adap);

	/* High-level CEC message callback */
	पूर्णांक (*received)(काष्ठा cec_adapter *adap, काष्ठा cec_msg *msg);
पूर्ण;

/**
 * cec_pin_changed() - update pin state from पूर्णांकerrupt
 *
 * @adap:	poपूर्णांकer to the cec adapter
 * @value:	when true the pin is high, otherwise it is low
 *
 * If changes of the CEC voltage are detected via an पूर्णांकerrupt, then
 * cec_pin_changed is called from the पूर्णांकerrupt with the new value.
 */
व्योम cec_pin_changed(काष्ठा cec_adapter *adap, bool value);

/**
 * cec_pin_allocate_adapter() - allocate a pin-based cec adapter
 *
 * @pin_ops:	low-level pin operations
 * @priv:	will be stored in adap->priv and can be used by the adapter ops.
 *		Use cec_get_drvdata(adap) to get the priv poपूर्णांकer.
 * @name:	the name of the CEC adapter. Note: this name will be copied.
 * @caps:	capabilities of the CEC adapter. This will be ORed with
 *		CEC_CAP_MONITOR_ALL and CEC_CAP_MONITOR_PIN.
 *
 * Allocate a cec adapter using the cec pin framework.
 *
 * Return: a poपूर्णांकer to the cec adapter or an error poपूर्णांकer
 */
काष्ठा cec_adapter *cec_pin_allocate_adapter(स्थिर काष्ठा cec_pin_ops *pin_ops,
					व्योम *priv, स्थिर अक्षर *name, u32 caps);

#पूर्ण_अगर
