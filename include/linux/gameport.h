<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (c) 1999-2002 Vojtech Pavlik
 */
#अगर_अघोषित _GAMEPORT_H
#घोषणा _GAMEPORT_H

#समावेश <यंत्र/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <uapi/linux/gameport.h>

काष्ठा gameport अणु

	व्योम *port_data;	/* Private poपूर्णांकer क्रम gameport drivers */
	अक्षर name[32];
	अक्षर phys[32];

	पूर्णांक io;
	पूर्णांक speed;
	पूर्णांक fuzz;

	व्योम (*trigger)(काष्ठा gameport *);
	अचिन्हित अक्षर (*पढ़ो)(काष्ठा gameport *);
	पूर्णांक (*cooked_पढ़ो)(काष्ठा gameport *, पूर्णांक *, पूर्णांक *);
	पूर्णांक (*calibrate)(काष्ठा gameport *, पूर्णांक *, पूर्णांक *);
	पूर्णांक (*खोलो)(काष्ठा gameport *, पूर्णांक);
	व्योम (*बंद)(काष्ठा gameport *);

	काष्ठा समयr_list poll_समयr;
	अचिन्हित पूर्णांक poll_पूर्णांकerval;	/* in msecs */
	spinlock_t समयr_lock;
	अचिन्हित पूर्णांक poll_cnt;
	व्योम (*poll_handler)(काष्ठा gameport *);

	काष्ठा gameport *parent, *child;

	काष्ठा gameport_driver *drv;
	काष्ठा mutex drv_mutex;		/* protects serio->drv so attributes can pin driver */

	काष्ठा device dev;

	काष्ठा list_head node;
पूर्ण;
#घोषणा to_gameport_port(d)	container_of(d, काष्ठा gameport, dev)

काष्ठा gameport_driver अणु
	स्थिर अक्षर *description;

	पूर्णांक (*connect)(काष्ठा gameport *, काष्ठा gameport_driver *drv);
	पूर्णांक (*reconnect)(काष्ठा gameport *);
	व्योम (*disconnect)(काष्ठा gameport *);

	काष्ठा device_driver driver;

	bool ignore;
पूर्ण;
#घोषणा to_gameport_driver(d)	container_of(d, काष्ठा gameport_driver, driver)

पूर्णांक gameport_खोलो(काष्ठा gameport *gameport, काष्ठा gameport_driver *drv, पूर्णांक mode);
व्योम gameport_बंद(काष्ठा gameport *gameport);

#अगर defined(CONFIG_GAMEPORT) || (defined(MODULE) && defined(CONFIG_GAMEPORT_MODULE))

व्योम __gameport_रेजिस्टर_port(काष्ठा gameport *gameport, काष्ठा module *owner);
/* use a define to aव्योम include chaining to get THIS_MODULE */
#घोषणा gameport_रेजिस्टर_port(gameport) \
	__gameport_रेजिस्टर_port(gameport, THIS_MODULE)

व्योम gameport_unरेजिस्टर_port(काष्ठा gameport *gameport);

__म_लिखो(2, 3)
व्योम gameport_set_phys(काष्ठा gameport *gameport, स्थिर अक्षर *fmt, ...);

#अन्यथा

अटल अंतरभूत व्योम gameport_रेजिस्टर_port(काष्ठा gameport *gameport)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम gameport_unरेजिस्टर_port(काष्ठा gameport *gameport)
अणु
	वापस;
पूर्ण

अटल अंतरभूत __म_लिखो(2, 3)
व्योम gameport_set_phys(काष्ठा gameport *gameport, स्थिर अक्षर *fmt, ...)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर

अटल अंतरभूत काष्ठा gameport *gameport_allocate_port(व्योम)
अणु
	काष्ठा gameport *gameport = kzalloc(माप(काष्ठा gameport), GFP_KERNEL);

	वापस gameport;
पूर्ण

अटल अंतरभूत व्योम gameport_मुक्त_port(काष्ठा gameport *gameport)
अणु
	kमुक्त(gameport);
पूर्ण

अटल अंतरभूत व्योम gameport_set_name(काष्ठा gameport *gameport, स्थिर अक्षर *name)
अणु
	strlcpy(gameport->name, name, माप(gameport->name));
पूर्ण

/*
 * Use the following functions to manipulate gameport's per-port
 * driver-specअगरic data.
 */
अटल अंतरभूत व्योम *gameport_get_drvdata(काष्ठा gameport *gameport)
अणु
	वापस dev_get_drvdata(&gameport->dev);
पूर्ण

अटल अंतरभूत व्योम gameport_set_drvdata(काष्ठा gameport *gameport, व्योम *data)
अणु
	dev_set_drvdata(&gameport->dev, data);
पूर्ण

/*
 * Use the following functions to pin gameport's driver in process context
 */
अटल अंतरभूत पूर्णांक gameport_pin_driver(काष्ठा gameport *gameport)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&gameport->drv_mutex);
पूर्ण

अटल अंतरभूत व्योम gameport_unpin_driver(काष्ठा gameport *gameport)
अणु
	mutex_unlock(&gameport->drv_mutex);
पूर्ण

पूर्णांक __must_check __gameport_रेजिस्टर_driver(काष्ठा gameport_driver *drv,
				काष्ठा module *owner, स्थिर अक्षर *mod_name);

/* use a define to aव्योम include chaining to get THIS_MODULE & मित्रs */
#घोषणा gameport_रेजिस्टर_driver(drv) \
	__gameport_रेजिस्टर_driver(drv, THIS_MODULE, KBUILD_MODNAME)

व्योम gameport_unरेजिस्टर_driver(काष्ठा gameport_driver *drv);

/**
 * module_gameport_driver() - Helper macro क्रम रेजिस्टरing a gameport driver
 * @__gameport_driver: gameport_driver काष्ठा
 *
 * Helper macro क्रम gameport drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module may
 * only use this macro once, and calling it replaces module_init() and
 * module_निकास().
 */
#घोषणा module_gameport_driver(__gameport_driver) \
	module_driver(__gameport_driver, gameport_रेजिस्टर_driver, \
		       gameport_unरेजिस्टर_driver)


अटल अंतरभूत व्योम gameport_trigger(काष्ठा gameport *gameport)
अणु
	अगर (gameport->trigger)
		gameport->trigger(gameport);
	अन्यथा
		outb(0xff, gameport->io);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर gameport_पढ़ो(काष्ठा gameport *gameport)
अणु
	अगर (gameport->पढ़ो)
		वापस gameport->पढ़ो(gameport);
	अन्यथा
		वापस inb(gameport->io);
पूर्ण

अटल अंतरभूत पूर्णांक gameport_cooked_पढ़ो(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *buttons)
अणु
	अगर (gameport->cooked_पढ़ो)
		वापस gameport->cooked_पढ़ो(gameport, axes, buttons);
	अन्यथा
		वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक gameport_calibrate(काष्ठा gameport *gameport, पूर्णांक *axes, पूर्णांक *max)
अणु
	अगर (gameport->calibrate)
		वापस gameport->calibrate(gameport, axes, max);
	अन्यथा
		वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक gameport_समय(काष्ठा gameport *gameport, पूर्णांक समय)
अणु
	वापस (समय * gameport->speed) / 1000;
पूर्ण

अटल अंतरभूत व्योम gameport_set_poll_handler(काष्ठा gameport *gameport, व्योम (*handler)(काष्ठा gameport *))
अणु
	gameport->poll_handler = handler;
पूर्ण

अटल अंतरभूत व्योम gameport_set_poll_पूर्णांकerval(काष्ठा gameport *gameport, अचिन्हित पूर्णांक msecs)
अणु
	gameport->poll_पूर्णांकerval = msecs;
पूर्ण

व्योम gameport_start_polling(काष्ठा gameport *gameport);
व्योम gameport_stop_polling(काष्ठा gameport *gameport);

#पूर्ण_अगर
