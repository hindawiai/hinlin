<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**
 * Copyright (c) 2011 Jonathan Cameron
 *
 * Join together the various functionality of iio_simple_dummy driver
 */

#अगर_अघोषित _IIO_SIMPLE_DUMMY_H_
#घोषणा _IIO_SIMPLE_DUMMY_H_
#समावेश <linux/kernel.h>

काष्ठा iio_dummy_accel_calibscale;
काष्ठा iio_dummy_regs;

/**
 * काष्ठा iio_dummy_state - device instance specअगरic state.
 * @dac_val:			cache क्रम dac value
 * @single_ended_adc_val:	cache क्रम single ended adc value
 * @dअगरferential_adc_val:	cache क्रम dअगरferential adc value
 * @accel_val:			cache क्रम acceleration value
 * @accel_calibbias:		cache क्रम acceleration calibbias
 * @accel_calibscale:		cache क्रम acceleration calibscale
 * @lock:			lock to ensure state is consistent
 * @event_irq:			irq number क्रम event line (faked)
 * @event_val:			cache क्रम event threshold value
 * @event_en:			cache of whether event is enabled
 */
काष्ठा iio_dummy_state अणु
	पूर्णांक dac_val;
	पूर्णांक single_ended_adc_val;
	पूर्णांक dअगरferential_adc_val[2];
	पूर्णांक accel_val;
	पूर्णांक accel_calibbias;
	पूर्णांक activity_running;
	पूर्णांक activity_walking;
	स्थिर काष्ठा iio_dummy_accel_calibscale *accel_calibscale;
	काष्ठा mutex lock;
	काष्ठा iio_dummy_regs *regs;
	पूर्णांक steps_enabled;
	पूर्णांक steps;
	पूर्णांक height;
#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS
	पूर्णांक event_irq;
	पूर्णांक event_val;
	bool event_en;
	s64 event_बारtamp;
#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS */
पूर्ण;

#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_EVENTS

काष्ठा iio_dev;

पूर्णांक iio_simple_dummy_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir);

पूर्णांक iio_simple_dummy_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
					स्थिर काष्ठा iio_chan_spec *chan,
					क्रमागत iio_event_type type,
					क्रमागत iio_event_direction dir,
					पूर्णांक state);

पूर्णांक iio_simple_dummy_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      क्रमागत iio_event_info info, पूर्णांक *val,
				      पूर्णांक *val2);

पूर्णांक iio_simple_dummy_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				       स्थिर काष्ठा iio_chan_spec *chan,
				       क्रमागत iio_event_type type,
				       क्रमागत iio_event_direction dir,
				       क्रमागत iio_event_info info, पूर्णांक val,
				       पूर्णांक val2);

पूर्णांक iio_simple_dummy_events_रेजिस्टर(काष्ठा iio_dev *indio_dev);
व्योम iio_simple_dummy_events_unरेजिस्टर(काष्ठा iio_dev *indio_dev);

#अन्यथा /* Stubs क्रम when events are disabled at compile समय */

अटल अंतरभूत पूर्णांक
iio_simple_dummy_events_रेजिस्टर(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
iio_simple_dummy_events_unरेजिस्टर(काष्ठा iio_dev *indio_dev)
अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_EVENTS*/

/**
 * क्रमागत iio_simple_dummy_scan_elements - scan index क्रमागत
 * @DUMMY_INDEX_VOLTAGE_0:         the single ended voltage channel
 * @DUMMY_INDEX_DIFFVOLTAGE_1M2:   first dअगरferential channel
 * @DUMMY_INDEX_DIFFVOLTAGE_3M4:   second dअगरferential channel
 * @DUMMY_INDEX_ACCELX:            acceleration channel
 *
 * Enum provides convenient numbering क्रम the scan index.
 */
क्रमागत iio_simple_dummy_scan_elements अणु
	DUMMY_INDEX_VOLTAGE_0,
	DUMMY_INDEX_DIFFVOLTAGE_1M2,
	DUMMY_INDEX_DIFFVOLTAGE_3M4,
	DUMMY_INDEX_ACCELX,
पूर्ण;

#अगर_घोषित CONFIG_IIO_SIMPLE_DUMMY_BUFFER
पूर्णांक iio_simple_dummy_configure_buffer(काष्ठा iio_dev *indio_dev);
व्योम iio_simple_dummy_unconfigure_buffer(काष्ठा iio_dev *indio_dev);
#अन्यथा
अटल अंतरभूत पूर्णांक iio_simple_dummy_configure_buffer(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम iio_simple_dummy_unconfigure_buffer(काष्ठा iio_dev *indio_dev)
अणुपूर्ण

#पूर्ण_अगर /* CONFIG_IIO_SIMPLE_DUMMY_BUFFER */
#पूर्ण_अगर /* _IIO_SIMPLE_DUMMY_H_ */
