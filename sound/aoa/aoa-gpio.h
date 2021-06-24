<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Apple Onboard Audio GPIO definitions
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#अगर_अघोषित __AOA_GPIO_H
#घोषणा __AOA_GPIO_H
#समावेश <linux/workqueue.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/prom.h>

प्रकार व्योम (*notअगरy_func_t)(व्योम *data);

क्रमागत notअगरy_type अणु
	AOA_NOTIFY_HEADPHONE,
	AOA_NOTIFY_LINE_IN,
	AOA_NOTIFY_LINE_OUT,
पूर्ण;

काष्ठा gpio_runसमय;
काष्ठा gpio_methods अणु
	/* क्रम initialisation/de-initialisation of the GPIO layer */
	व्योम (*init)(काष्ठा gpio_runसमय *rt);
	व्योम (*निकास)(काष्ठा gpio_runसमय *rt);

	/* turn off headphone, speakers, lineout */
	व्योम (*all_amps_off)(काष्ठा gpio_runसमय *rt);
	/* turn headphone, speakers, lineout back to previous setting */
	व्योम (*all_amps_restore)(काष्ठा gpio_runसमय *rt);

	व्योम (*set_headphone)(काष्ठा gpio_runसमय *rt, पूर्णांक on);
	व्योम (*set_speakers)(काष्ठा gpio_runसमय *rt, पूर्णांक on);
	व्योम (*set_lineout)(काष्ठा gpio_runसमय *rt, पूर्णांक on);
	व्योम (*set_master)(काष्ठा gpio_runसमय *rt, पूर्णांक on);

	पूर्णांक (*get_headphone)(काष्ठा gpio_runसमय *rt);
	पूर्णांक (*get_speakers)(काष्ठा gpio_runसमय *rt);
	पूर्णांक (*get_lineout)(काष्ठा gpio_runसमय *rt);
	पूर्णांक (*get_master)(काष्ठा gpio_runसमय *rt);

	व्योम (*set_hw_reset)(काष्ठा gpio_runसमय *rt, पूर्णांक on);

	/* use this to be notअगरied of any events. The notअगरication
	 * function is passed the data, and is called in process
	 * context by the use of schedule_work.
	 * The पूर्णांकerface क्रम it is that setting a function to शून्य
	 * हटाओs it, and they वापस 0 अगर the operation succeeded,
	 * and -EBUSY अगर the notअगरication is alपढ़ोy asचिन्हित by
	 * someone अन्यथा. */
	पूर्णांक (*set_notअगरy)(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type,
			  notअगरy_func_t notअगरy,
			  व्योम *data);
	/* वापसs 0 अगर not plugged in, 1 अगर plugged in
	 * or a negative error code */
	पूर्णांक (*get_detect)(काष्ठा gpio_runसमय *rt,
			  क्रमागत notअगरy_type type);
पूर्ण;

काष्ठा gpio_notअगरication अणु
	काष्ठा delayed_work work;
	notअगरy_func_t notअगरy;
	व्योम *data;
	व्योम *gpio_निजी;
	काष्ठा mutex mutex;
पूर्ण;

काष्ठा gpio_runसमय अणु
	/* to be asचिन्हित by fabric */
	काष्ठा device_node *node;
	/* since everyone needs this poपूर्णांकer anyway... */
	काष्ठा gpio_methods *methods;
	/* to be used by the gpio implementation */
	पूर्णांक implementation_निजी;
	काष्ठा gpio_notअगरication headphone_notअगरy;
	काष्ठा gpio_notअगरication line_in_notअगरy;
	काष्ठा gpio_notअगरication line_out_notअगरy;
पूर्ण;

#पूर्ण_अगर /* __AOA_GPIO_H */
