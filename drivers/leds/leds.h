<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * LED Core
 *
 * Copyright 2005 Openedhand Ltd.
 *
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */
#अगर_अघोषित __LEDS_H_INCLUDED
#घोषणा __LEDS_H_INCLUDED

#समावेश <linux/rwsem.h>
#समावेश <linux/leds.h>

अटल अंतरभूत पूर्णांक led_get_brightness(काष्ठा led_classdev *led_cdev)
अणु
	वापस led_cdev->brightness;
पूर्ण

व्योम led_init_core(काष्ठा led_classdev *led_cdev);
व्योम led_stop_software_blink(काष्ठा led_classdev *led_cdev);
व्योम led_set_brightness_nopm(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value);
व्योम led_set_brightness_nosleep(काष्ठा led_classdev *led_cdev, अचिन्हित पूर्णांक value);
sमाप_प्रकार led_trigger_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *attr, अक्षर *buf,
			loff_t pos, माप_प्रकार count);
sमाप_प्रकार led_trigger_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj,
			काष्ठा bin_attribute *bin_attr, अक्षर *buf,
			loff_t pos, माप_प्रकार count);

बाह्य काष्ठा rw_semaphore leds_list_lock;
बाह्य काष्ठा list_head leds_list;
बाह्य काष्ठा list_head trigger_list;
बाह्य स्थिर अक्षर * स्थिर led_colors[LED_COLOR_ID_MAX];

#पूर्ण_अगर	/* __LEDS_H_INCLUDED */
