<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * soc-jack.h
 *
 * Copyright (C) 2019 Renesas Electronics Corp.
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#अगर_अघोषित __SOC_JACK_H
#घोषणा __SOC_JACK_H

/**
 * काष्ठा snd_soc_jack_pin - Describes a pin to update based on jack detection
 *
 * @pin:    name of the pin to update
 * @mask:   bits to check क्रम in reported jack status
 * @invert: अगर non-zero then pin is enabled when status is not reported
 * @list:   पूर्णांकernal list entry
 */
काष्ठा snd_soc_jack_pin अणु
	काष्ठा list_head list;
	स्थिर अक्षर *pin;
	पूर्णांक mask;
	bool invert;
पूर्ण;

/**
 * काष्ठा snd_soc_jack_zone - Describes voltage zones of jack detection
 *
 * @min_mv: start voltage in mv
 * @max_mv: end voltage in mv
 * @jack_type: type of jack that is expected क्रम this voltage
 * @debounce_समय: debounce_समय क्रम jack, codec driver should रुको क्रम this
 *		duration beक्रमe पढ़ोing the adc क्रम voltages
 * @list:   पूर्णांकernal list entry
 */
काष्ठा snd_soc_jack_zone अणु
	अचिन्हित पूर्णांक min_mv;
	अचिन्हित पूर्णांक max_mv;
	अचिन्हित पूर्णांक jack_type;
	अचिन्हित पूर्णांक debounce_समय;
	काष्ठा list_head list;
पूर्ण;

/**
 * काष्ठा snd_soc_jack_gpio - Describes a gpio pin क्रम jack detection
 *
 * @gpio:         legacy gpio number
 * @idx:          gpio descriptor index within the function of the GPIO
 *                consumer device
 * @gpiod_dev:    GPIO consumer device
 * @name:         gpio name. Also as connection ID क्रम the GPIO consumer
 *                device function name lookup
 * @report:       value to report when jack detected
 * @invert:       report presence in low state
 * @debounce_समय: debounce समय in ms
 * @wake:	  enable as wake source
 * @jack_status_check: callback function which overrides the detection
 *		       to provide more complex checks (eg, पढ़ोing an
 *		       ADC).
 */
काष्ठा snd_soc_jack_gpio अणु
	अचिन्हित पूर्णांक gpio;
	अचिन्हित पूर्णांक idx;
	काष्ठा device *gpiod_dev;
	स्थिर अक्षर *name;
	पूर्णांक report;
	पूर्णांक invert;
	पूर्णांक debounce_समय;
	bool wake;

	/* निजी: */
	काष्ठा snd_soc_jack *jack;
	काष्ठा delayed_work work;
	काष्ठा notअगरier_block pm_notअगरier;
	काष्ठा gpio_desc *desc;

	व्योम *data;
	/* खुला: */
	पूर्णांक (*jack_status_check)(व्योम *data);
पूर्ण;

काष्ठा snd_soc_jack अणु
	काष्ठा mutex mutex;
	काष्ठा snd_jack *jack;
	काष्ठा snd_soc_card *card;
	काष्ठा list_head pins;
	पूर्णांक status;
	काष्ठा blocking_notअगरier_head notअगरier;
	काष्ठा list_head jack_zones;
पूर्ण;

/* Jack reporting */
व्योम snd_soc_jack_report(काष्ठा snd_soc_jack *jack, पूर्णांक status, पूर्णांक mask);
पूर्णांक snd_soc_jack_add_pins(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			  काष्ठा snd_soc_jack_pin *pins);
व्योम snd_soc_jack_notअगरier_रेजिस्टर(काष्ठा snd_soc_jack *jack,
				    काष्ठा notअगरier_block *nb);
व्योम snd_soc_jack_notअगरier_unरेजिस्टर(काष्ठा snd_soc_jack *jack,
				      काष्ठा notअगरier_block *nb);
पूर्णांक snd_soc_jack_add_zones(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			   काष्ठा snd_soc_jack_zone *zones);
पूर्णांक snd_soc_jack_get_type(काष्ठा snd_soc_jack *jack, पूर्णांक micbias_voltage);
#अगर_घोषित CONFIG_GPIOLIB
पूर्णांक snd_soc_jack_add_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			   काष्ठा snd_soc_jack_gpio *gpios);
पूर्णांक snd_soc_jack_add_gpiods(काष्ठा device *gpiod_dev,
			    काष्ठा snd_soc_jack *jack,
			    पूर्णांक count, काष्ठा snd_soc_jack_gpio *gpios);
व्योम snd_soc_jack_मुक्त_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
			     काष्ठा snd_soc_jack_gpio *gpios);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_soc_jack_add_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
					 काष्ठा snd_soc_jack_gpio *gpios)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक snd_soc_jack_add_gpiods(काष्ठा device *gpiod_dev,
					  काष्ठा snd_soc_jack *jack,
					  पूर्णांक count,
					  काष्ठा snd_soc_jack_gpio *gpios)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम snd_soc_jack_मुक्त_gpios(काष्ठा snd_soc_jack *jack, पूर्णांक count,
					   काष्ठा snd_soc_jack_gpio *gpios)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __SOC_JACK_H */
