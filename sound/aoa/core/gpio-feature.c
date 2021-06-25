<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Apple Onboard Audio feature call GPIO control
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 *
 * This file contains the GPIO control routines क्रम
 * direct (through feature calls) access to the GPIO
 * रेजिस्टरs.
 */

#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश "../aoa.h"

/* TODO: these are lots of global variables
 * that aren't used on most machines...
 * Move them पूर्णांकo a dynamically allocated
 * काष्ठाure and use that.
 */

/* these are the GPIO numbers (रेजिस्टर addresses as offsets पूर्णांकo
 * the GPIO space) */
अटल पूर्णांक headphone_mute_gpio;
अटल पूर्णांक master_mute_gpio;
अटल पूर्णांक amp_mute_gpio;
अटल पूर्णांक lineout_mute_gpio;
अटल पूर्णांक hw_reset_gpio;
अटल पूर्णांक lineout_detect_gpio;
अटल पूर्णांक headphone_detect_gpio;
अटल पूर्णांक linein_detect_gpio;

/* see the SWITCH_GPIO macro */
अटल पूर्णांक headphone_mute_gpio_activestate;
अटल पूर्णांक master_mute_gpio_activestate;
अटल पूर्णांक amp_mute_gpio_activestate;
अटल पूर्णांक lineout_mute_gpio_activestate;
अटल पूर्णांक hw_reset_gpio_activestate;
अटल पूर्णांक lineout_detect_gpio_activestate;
अटल पूर्णांक headphone_detect_gpio_activestate;
अटल पूर्णांक linein_detect_gpio_activestate;

/* node poपूर्णांकers that we save when getting the GPIO number
 * to get the पूर्णांकerrupt later */
अटल काष्ठा device_node *lineout_detect_node;
अटल काष्ठा device_node *linein_detect_node;
अटल काष्ठा device_node *headphone_detect_node;

अटल पूर्णांक lineout_detect_irq;
अटल पूर्णांक linein_detect_irq;
अटल पूर्णांक headphone_detect_irq;

अटल काष्ठा device_node *get_gpio(अक्षर *name,
				    अक्षर *altname,
				    पूर्णांक *gpioptr,
				    पूर्णांक *gpioactiveptr)
अणु
	काष्ठा device_node *np, *gpio;
	स्थिर u32 *reg;
	स्थिर अक्षर *audio_gpio;

	*gpioptr = -1;

	/* check अगर we can get it the easy way ... */
	np = of_find_node_by_name(शून्य, name);
	अगर (!np) अणु
		/* some machines have only gpioX/extपूर्णांक-gpioX nodes,
		 * and an audio-gpio property saying what it is ...
		 * So what we have to करो is क्रमागतerate all children
		 * of the gpio node and check them all. */
		gpio = of_find_node_by_name(शून्य, "gpio");
		अगर (!gpio)
			वापस शून्य;
		जबतक ((np = of_get_next_child(gpio, np))) अणु
			audio_gpio = of_get_property(np, "audio-gpio", शून्य);
			अगर (!audio_gpio)
				जारी;
			अगर (म_भेद(audio_gpio, name) == 0)
				अवरोध;
			अगर (altname && (म_भेद(audio_gpio, altname) == 0))
				अवरोध;
		पूर्ण
		of_node_put(gpio);
		/* still not found, assume not there */
		अगर (!np)
			वापस शून्य;
	पूर्ण

	reg = of_get_property(np, "reg", शून्य);
	अगर (!reg) अणु
		of_node_put(np);
		वापस शून्य;
	पूर्ण

	*gpioptr = *reg;

	/* this is a hack, usually the GPIOs 'reg' property
	 * should have the offset based from the GPIO space
	 * which is at 0x50, but apparently not always... */
	अगर (*gpioptr < 0x50)
		*gpioptr += 0x50;

	reg = of_get_property(np, "audio-gpio-active-state", शून्य);
	अगर (!reg)
		/* Apple seems to शेष to 1, but
		 * that करोesn't seem right at least on most
		 * machines. So until proven that the opposite
		 * is necessary, we शेष to 0
		 * (which, incidentally, snd-घातermac also करोes...) */
		*gpioactiveptr = 0;
	अन्यथा
		*gpioactiveptr = *reg;

	वापस np;
पूर्ण

अटल व्योम get_irq(काष्ठा device_node * np, पूर्णांक *irqptr)
अणु
	अगर (np)
		*irqptr = irq_of_parse_and_map(np, 0);
	अन्यथा
		*irqptr = 0;
पूर्ण

/* 0x4 is outenable, 0x1 is out, thus 4 or 5 */
#घोषणा SWITCH_GPIO(name, v, on)				\
	(((v)&~1) | ((on)?					\
			(name##_gpio_activestate==0?4:5):	\
			(name##_gpio_activestate==0?5:4)))

#घोषणा FTR_GPIO(name, bit)					\
अटल व्योम ftr_gpio_set_##name(काष्ठा gpio_runसमय *rt, पूर्णांक on)\
अणु								\
	पूर्णांक v;							\
								\
	अगर (unlikely(!rt)) वापस;				\
								\
	अगर (name##_mute_gpio < 0)				\
		वापस;						\
								\
	v = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य,		\
			      name##_mute_gpio,			\
			      0);				\
								\
	/* muted = !on... */					\
	v = SWITCH_GPIO(name##_mute, v, !on);			\
								\
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य,		\
			  name##_mute_gpio, v);			\
								\
	rt->implementation_निजी &= ~(1<<bit);		\
	rt->implementation_निजी |= (!!on << bit);		\
पूर्ण								\
अटल पूर्णांक ftr_gpio_get_##name(काष्ठा gpio_runसमय *rt)		\
अणु								\
	अगर (unlikely(!rt)) वापस 0;				\
	वापस (rt->implementation_निजी>>bit)&1;		\
पूर्ण

FTR_GPIO(headphone, 0);
FTR_GPIO(amp, 1);
FTR_GPIO(lineout, 2);
FTR_GPIO(master, 3);

अटल व्योम ftr_gpio_set_hw_reset(काष्ठा gpio_runसमय *rt, पूर्णांक on)
अणु
	पूर्णांक v;

	अगर (unlikely(!rt)) वापस;
	अगर (hw_reset_gpio < 0)
		वापस;

	v = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य,
			      hw_reset_gpio, 0);
	v = SWITCH_GPIO(hw_reset, v, on);
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य,
			  hw_reset_gpio, v);
पूर्ण

अटल काष्ठा gpio_methods methods;

अटल व्योम ftr_gpio_all_amps_off(काष्ठा gpio_runसमय *rt)
अणु
	पूर्णांक saved;

	अगर (unlikely(!rt)) वापस;
	saved = rt->implementation_निजी;
	ftr_gpio_set_headphone(rt, 0);
	ftr_gpio_set_amp(rt, 0);
	ftr_gpio_set_lineout(rt, 0);
	अगर (methods.set_master)
		ftr_gpio_set_master(rt, 0);
	rt->implementation_निजी = saved;
पूर्ण

अटल व्योम ftr_gpio_all_amps_restore(काष्ठा gpio_runसमय *rt)
अणु
	पूर्णांक s;

	अगर (unlikely(!rt)) वापस;
	s = rt->implementation_निजी;
	ftr_gpio_set_headphone(rt, (s>>0)&1);
	ftr_gpio_set_amp(rt, (s>>1)&1);
	ftr_gpio_set_lineout(rt, (s>>2)&1);
	अगर (methods.set_master)
		ftr_gpio_set_master(rt, (s>>3)&1);
पूर्ण

अटल व्योम ftr_handle_notअगरy(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gpio_notअगरication *notअगर =
		container_of(work, काष्ठा gpio_notअगरication, work.work);

	mutex_lock(&notअगर->mutex);
	अगर (notअगर->notअगरy)
		notअगर->notअगरy(notअगर->data);
	mutex_unlock(&notअगर->mutex);
पूर्ण

अटल व्योम gpio_enable_dual_edge(पूर्णांक gpio)
अणु
	पूर्णांक v;

	अगर (gpio == -1)
		वापस;
	v = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, gpio, 0);
	v |= 0x80; /* enable dual edge */
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, gpio, v);
पूर्ण

अटल व्योम ftr_gpio_init(काष्ठा gpio_runसमय *rt)
अणु
	get_gpio("headphone-mute", शून्य,
		 &headphone_mute_gpio,
		 &headphone_mute_gpio_activestate);
	get_gpio("amp-mute", शून्य,
		 &amp_mute_gpio,
		 &amp_mute_gpio_activestate);
	get_gpio("lineout-mute", शून्य,
		 &lineout_mute_gpio,
		 &lineout_mute_gpio_activestate);
	get_gpio("hw-reset", "audio-hw-reset",
		 &hw_reset_gpio,
		 &hw_reset_gpio_activestate);
	अगर (get_gpio("master-mute", शून्य,
		     &master_mute_gpio,
		     &master_mute_gpio_activestate)) अणु
		methods.set_master = ftr_gpio_set_master;
		methods.get_master = ftr_gpio_get_master;
	पूर्ण

	headphone_detect_node = get_gpio("headphone-detect", शून्य,
					 &headphone_detect_gpio,
					 &headphone_detect_gpio_activestate);
	/* go Apple, and thanks क्रम giving these dअगरferent names
	 * across the board... */
	lineout_detect_node = get_gpio("lineout-detect", "line-output-detect",
				       &lineout_detect_gpio,
				       &lineout_detect_gpio_activestate);
	linein_detect_node = get_gpio("linein-detect", "line-input-detect",
				      &linein_detect_gpio,
				      &linein_detect_gpio_activestate);

	gpio_enable_dual_edge(headphone_detect_gpio);
	gpio_enable_dual_edge(lineout_detect_gpio);
	gpio_enable_dual_edge(linein_detect_gpio);

	get_irq(headphone_detect_node, &headphone_detect_irq);
	get_irq(lineout_detect_node, &lineout_detect_irq);
	get_irq(linein_detect_node, &linein_detect_irq);

	ftr_gpio_all_amps_off(rt);
	rt->implementation_निजी = 0;
	INIT_DELAYED_WORK(&rt->headphone_notअगरy.work, ftr_handle_notअगरy);
	INIT_DELAYED_WORK(&rt->line_in_notअगरy.work, ftr_handle_notअगरy);
	INIT_DELAYED_WORK(&rt->line_out_notअगरy.work, ftr_handle_notअगरy);
	mutex_init(&rt->headphone_notअगरy.mutex);
	mutex_init(&rt->line_in_notअगरy.mutex);
	mutex_init(&rt->line_out_notअगरy.mutex);
पूर्ण

अटल व्योम ftr_gpio_निकास(काष्ठा gpio_runसमय *rt)
अणु
	ftr_gpio_all_amps_off(rt);
	rt->implementation_निजी = 0;
	अगर (rt->headphone_notअगरy.notअगरy)
		मुक्त_irq(headphone_detect_irq, &rt->headphone_notअगरy);
	अगर (rt->line_in_notअगरy.gpio_निजी)
		मुक्त_irq(linein_detect_irq, &rt->line_in_notअगरy);
	अगर (rt->line_out_notअगरy.gpio_निजी)
		मुक्त_irq(lineout_detect_irq, &rt->line_out_notअगरy);
	cancel_delayed_work_sync(&rt->headphone_notअगरy.work);
	cancel_delayed_work_sync(&rt->line_in_notअगरy.work);
	cancel_delayed_work_sync(&rt->line_out_notअगरy.work);
	mutex_destroy(&rt->headphone_notअगरy.mutex);
	mutex_destroy(&rt->line_in_notअगरy.mutex);
	mutex_destroy(&rt->line_out_notअगरy.mutex);
पूर्ण

अटल irqवापस_t ftr_handle_notअगरy_irq(पूर्णांक xx, व्योम *data)
अणु
	काष्ठा gpio_notअगरication *notअगर = data;

	schedule_delayed_work(&notअगर->work, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ftr_set_notअगरy(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type,
			  notअगरy_func_t notअगरy,
			  व्योम *data)
अणु
	काष्ठा gpio_notअगरication *notअगर;
	notअगरy_func_t old;
	पूर्णांक irq;
	अक्षर *name;
	पूर्णांक err = -EBUSY;

	चयन (type) अणु
	हाल AOA_NOTIFY_HEADPHONE:
		notअगर = &rt->headphone_notअगरy;
		name = "headphone-detect";
		irq = headphone_detect_irq;
		अवरोध;
	हाल AOA_NOTIFY_LINE_IN:
		notअगर = &rt->line_in_notअगरy;
		name = "linein-detect";
		irq = linein_detect_irq;
		अवरोध;
	हाल AOA_NOTIFY_LINE_OUT:
		notअगर = &rt->line_out_notअगरy;
		name = "lineout-detect";
		irq = lineout_detect_irq;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!irq)
		वापस -ENODEV;

	mutex_lock(&notअगर->mutex);

	old = notअगर->notअगरy;

	अगर (!old && !notअगरy) अणु
		err = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (old && notअगरy) अणु
		अगर (old == notअगरy && notअगर->data == data)
			err = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (old && !notअगरy)
		मुक्त_irq(irq, notअगर);

	अगर (!old && notअगरy) अणु
		err = request_irq(irq, ftr_handle_notअगरy_irq, 0, name, notअगर);
		अगर (err)
			जाओ out_unlock;
	पूर्ण

	notअगर->notअगरy = notअगरy;
	notअगर->data = data;

	err = 0;
 out_unlock:
	mutex_unlock(&notअगर->mutex);
	वापस err;
पूर्ण

अटल पूर्णांक ftr_get_detect(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type)
अणु
	पूर्णांक gpio, ret, active;

	चयन (type) अणु
	हाल AOA_NOTIFY_HEADPHONE:
		gpio = headphone_detect_gpio;
		active = headphone_detect_gpio_activestate;
		अवरोध;
	हाल AOA_NOTIFY_LINE_IN:
		gpio = linein_detect_gpio;
		active = linein_detect_gpio_activestate;
		अवरोध;
	हाल AOA_NOTIFY_LINE_OUT:
		gpio = lineout_detect_gpio;
		active = lineout_detect_gpio_activestate;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (gpio == -1)
		वापस -ENODEV;

	ret = pmac_call_feature(PMAC_FTR_READ_GPIO, शून्य, gpio, 0);
	अगर (ret < 0)
		वापस ret;
	वापस ((ret >> 1) & 1) == active;
पूर्ण

अटल काष्ठा gpio_methods methods = अणु
	.init			= ftr_gpio_init,
	.निकास			= ftr_gpio_निकास,
	.all_amps_off		= ftr_gpio_all_amps_off,
	.all_amps_restore	= ftr_gpio_all_amps_restore,
	.set_headphone		= ftr_gpio_set_headphone,
	.set_speakers		= ftr_gpio_set_amp,
	.set_lineout		= ftr_gpio_set_lineout,
	.set_hw_reset		= ftr_gpio_set_hw_reset,
	.get_headphone		= ftr_gpio_get_headphone,
	.get_speakers		= ftr_gpio_get_amp,
	.get_lineout		= ftr_gpio_get_lineout,
	.set_notअगरy		= ftr_set_notअगरy,
	.get_detect		= ftr_get_detect,
पूर्ण;

काष्ठा gpio_methods *ftr_gpio_methods = &methods;
EXPORT_SYMBOL_GPL(ftr_gpio_methods);
