<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * LCD Lowlevel Control Abstraction
 *
 * Copyright (C) 2003,2004 Hewlett-Packard Company
 *
 */

#अगर_अघोषित _LINUX_LCD_H
#घोषणा _LINUX_LCD_H

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/fb.h>

/* Notes on locking:
 *
 * lcd_device->ops_lock is an पूर्णांकernal backlight lock protecting the ops
 * field and no code outside the core should need to touch it.
 *
 * Access to set_घातer() is serialised by the update_lock mutex since
 * most drivers seem to need this and historically get it wrong.
 *
 * Most drivers करोn't need locking on their get_घातer() method.
 * If yours करोes, you need to implement it in the driver. You can use the
 * update_lock mutex अगर appropriate.
 *
 * Any other use of the locks below is probably wrong.
 */

काष्ठा lcd_device;
काष्ठा fb_info;

काष्ठा lcd_properties अणु
	/* The maximum value क्रम contrast (पढ़ो-only) */
	पूर्णांक max_contrast;
पूर्ण;

काष्ठा lcd_ops अणु
	/* Get the LCD panel घातer status (0: full on, 1..3: controller
	   घातer on, flat panel घातer off, 4: full off), see FB_BLANK_XXX */
	पूर्णांक (*get_घातer)(काष्ठा lcd_device *);
	/* Enable or disable घातer to the LCD (0: on; 4: off, see FB_BLANK_XXX) */
	पूर्णांक (*set_घातer)(काष्ठा lcd_device *, पूर्णांक घातer);
	/* Get the current contrast setting (0-max_contrast) */
	पूर्णांक (*get_contrast)(काष्ठा lcd_device *);
	/* Set LCD panel contrast */
        पूर्णांक (*set_contrast)(काष्ठा lcd_device *, पूर्णांक contrast);
	/* Set LCD panel mode (resolutions ...) */
	पूर्णांक (*set_mode)(काष्ठा lcd_device *, काष्ठा fb_videomode *);
	/* Check अगर given framebuffer device is the one LCD is bound to;
	   वापस 0 अगर not, !=0 अगर it is. If शून्य, lcd always matches the fb. */
	पूर्णांक (*check_fb)(काष्ठा lcd_device *, काष्ठा fb_info *);
पूर्ण;

काष्ठा lcd_device अणु
	काष्ठा lcd_properties props;
	/* This protects the 'ops' field. If 'ops' is शून्य, the driver that
	   रेजिस्टरed this device has been unloaded, and अगर class_get_devdata()
	   poपूर्णांकs to something in the body of that driver, it is also invalid. */
	काष्ठा mutex ops_lock;
	/* If this is शून्य, the backing module is unloaded */
	काष्ठा lcd_ops *ops;
	/* Serialise access to set_घातer method */
	काष्ठा mutex update_lock;
	/* The framebuffer notअगरier block */
	काष्ठा notअगरier_block fb_notअगर;

	काष्ठा device dev;
पूर्ण;

काष्ठा lcd_platक्रमm_data अणु
	/* reset lcd panel device. */
	पूर्णांक (*reset)(काष्ठा lcd_device *ld);
	/* on or off to lcd panel. अगर 'enable' is 0 then
	   lcd घातer off and 1, lcd घातer on. */
	पूर्णांक (*घातer_on)(काष्ठा lcd_device *ld, पूर्णांक enable);

	/* it indicates whether lcd panel was enabled
	   from bootloader or not. */
	पूर्णांक lcd_enabled;
	/* it means delay क्रम stable समय when it becomes low to high
	   or high to low that is dependent on whether reset gpio is
	   low active or high active. */
	अचिन्हित पूर्णांक reset_delay;
	/* stable समय needing to become lcd घातer on. */
	अचिन्हित पूर्णांक घातer_on_delay;
	/* stable समय needing to become lcd घातer off. */
	अचिन्हित पूर्णांक घातer_off_delay;

	/* it could be used क्रम any purpose. */
	व्योम *pdata;
पूर्ण;

अटल अंतरभूत व्योम lcd_set_घातer(काष्ठा lcd_device *ld, पूर्णांक घातer)
अणु
	mutex_lock(&ld->update_lock);
	अगर (ld->ops && ld->ops->set_घातer)
		ld->ops->set_घातer(ld, घातer);
	mutex_unlock(&ld->update_lock);
पूर्ण

बाह्य काष्ठा lcd_device *lcd_device_रेजिस्टर(स्थिर अक्षर *name,
	काष्ठा device *parent, व्योम *devdata, काष्ठा lcd_ops *ops);
बाह्य काष्ठा lcd_device *devm_lcd_device_रेजिस्टर(काष्ठा device *dev,
	स्थिर अक्षर *name, काष्ठा device *parent,
	व्योम *devdata, काष्ठा lcd_ops *ops);
बाह्य व्योम lcd_device_unरेजिस्टर(काष्ठा lcd_device *ld);
बाह्य व्योम devm_lcd_device_unरेजिस्टर(काष्ठा device *dev,
	काष्ठा lcd_device *ld);

#घोषणा to_lcd_device(obj) container_of(obj, काष्ठा lcd_device, dev)

अटल अंतरभूत व्योम * lcd_get_data(काष्ठा lcd_device *ld_dev)
अणु
	वापस dev_get_drvdata(&ld_dev->dev);
पूर्ण


#पूर्ण_अगर
