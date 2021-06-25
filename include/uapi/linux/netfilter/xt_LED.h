<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _XT_LED_H
#घोषणा _XT_LED_H

#समावेश <linux/types.h>

काष्ठा xt_led_info अणु
	अक्षर id[27];        /* Unique ID क्रम this trigger in the LED class */
	__u8 always_blink;  /* Blink even अगर the LED is alपढ़ोy on */
	__u32 delay;        /* Delay until LED is चयनed off after trigger */

	/* Kernel data used in the module */
	व्योम *पूर्णांकernal_data __attribute__((aligned(8)));
पूर्ण;

#पूर्ण_अगर /* _XT_LED_H */
