<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/extcon/extcon-adc-jack.h
 *
 * Analog Jack extcon driver with ADC-based detection capability.
 *
 * Copyright (C) 2012 Samsung Electronics
 * MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#अगर_अघोषित _EXTCON_ADC_JACK_H_
#घोषणा _EXTCON_ADC_JACK_H_ __खाता__

#समावेश <linux/module.h>
#समावेश <linux/extcon.h>

/**
 * काष्ठा adc_jack_cond - condition to use an extcon state
 *			denotes the last adc_jack_cond element among the array)
 * @id:			the unique id of each बाह्यal connector
 * @min_adc:		min adc value क्रम this condition
 * @max_adc:		max adc value क्रम this condition
 *
 * For example, अगर अणु .state = 0x3, .min_adc = 100, .max_adc = 200पूर्ण, it means
 * that अगर ADC value is between (inclusive) 100 and 200, than the cable 0 and
 * 1 are attached (1<<0 | 1<<1 == 0x3)
 *
 * Note that you करोn't need to describe condition क्रम "no cable attached"
 * because when no adc_jack_cond is met, state = 0 is स्वतःmatically chosen.
 */
काष्ठा adc_jack_cond अणु
	अचिन्हित पूर्णांक id;
	u32 min_adc;
	u32 max_adc;
पूर्ण;

/**
 * काष्ठा adc_jack_pdata - platक्रमm data क्रम adc jack device.
 * @name:		name of the extcon device. If null, "adc-jack" is used.
 * @consumer_channel:	Unique name to identअगरy the channel on the consumer
 *			side. This typically describes the channels used within
 *			the consumer. E.g. 'battery_voltage'
 * @cable_names:	array of extcon id क्रम supported cables.
 * @adc_contitions:	array of काष्ठा adc_jack_cond conditions ending
 *			with .state = 0 entry. This describes how to decode
 *			adc values पूर्णांकo extcon state.
 * @irq_flags:		irq flags used क्रम the @irq
 * @handling_delay_ms:	in some devices, we need to पढ़ो ADC value some
 *			milli-seconds after the पूर्णांकerrupt occurs. You may
 *			describe such delays with @handling_delay_ms, which
 *			is rounded-off by jअगरfies.
 * @wakeup_source:	flag to wake up the प्रणाली क्रम extcon events.
 */
काष्ठा adc_jack_pdata अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *consumer_channel;

	स्थिर अचिन्हित पूर्णांक *cable_names;

	/* The last entry's state should be 0 */
	काष्ठा adc_jack_cond *adc_conditions;

	अचिन्हित दीर्घ irq_flags;
	अचिन्हित दीर्घ handling_delay_ms; /* in ms */
	bool wakeup_source;
पूर्ण;

#पूर्ण_अगर /* _EXTCON_ADC_JACK_H */
