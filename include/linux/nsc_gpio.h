<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
   nsc_gpio.c

   National Semiconductor GPIO common access methods.

   काष्ठा nsc_gpio_ops असलtracts the low-level access
   operations क्रम the GPIO units on 2 NSC chip families; the GEODE
   पूर्णांकegrated CPU, and the PC-8736[03456] पूर्णांकegrated PC-peripheral
   chips.

   The GPIO units on these chips have the same pin architecture, but
   the access methods dअगरfer.  Thus, scx200_gpio and pc8736x_gpio
   implement their own versions of these routines; and use the common
   file-operations routines implemented in nsc_gpio module.

   Copyright (c) 2005 Jim Cromie <jim.cromie@gmail.com>

   NB: this work was tested on the Geode SC-1100 and PC-87366 chips.
   NSC sold the GEODE line to AMD, and the PC-8736x line to Winbond.
*/

काष्ठा nsc_gpio_ops अणु
	काष्ठा module*	owner;
	u32	(*gpio_config)	(अचिन्हित iminor, u32 mask, u32 bits);
	व्योम	(*gpio_dump)	(काष्ठा nsc_gpio_ops *amp, अचिन्हित iminor);
	पूर्णांक	(*gpio_get)	(अचिन्हित iminor);
	व्योम	(*gpio_set)	(अचिन्हित iminor, पूर्णांक state);
	व्योम	(*gpio_change)	(अचिन्हित iminor);
	पूर्णांक	(*gpio_current)	(अचिन्हित iminor);
	काष्ठा device*	dev;	/* क्रम dev_dbg() support, set in init  */
पूर्ण;

बाह्य sमाप_प्रकार nsc_gpio_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
			      माप_प्रकार len, loff_t *ppos);

बाह्य sमाप_प्रकार nsc_gpio_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार len, loff_t *ppos);

बाह्य व्योम nsc_gpio_dump(काष्ठा nsc_gpio_ops *amp, अचिन्हित index);

