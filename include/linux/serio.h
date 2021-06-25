<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 1999-2002 Vojtech Pavlik
 */
#अगर_अघोषित _SERIO_H
#घोषणा _SERIO_H


#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <uapi/linux/serपन.स>

बाह्य काष्ठा bus_type serio_bus;

काष्ठा serio अणु
	व्योम *port_data;

	अक्षर name[32];
	अक्षर phys[32];
	अक्षर firmware_id[128];

	bool manual_bind;

	काष्ठा serio_device_id id;

	/* Protects critical sections from port's पूर्णांकerrupt handler */
	spinlock_t lock;

	पूर्णांक (*ग_लिखो)(काष्ठा serio *, अचिन्हित अक्षर);
	पूर्णांक (*खोलो)(काष्ठा serio *);
	व्योम (*बंद)(काष्ठा serio *);
	पूर्णांक (*start)(काष्ठा serio *);
	व्योम (*stop)(काष्ठा serio *);

	काष्ठा serio *parent;
	/* Entry in parent->children list */
	काष्ठा list_head child_node;
	काष्ठा list_head children;
	/* Level of nesting in serio hierarchy */
	अचिन्हित पूर्णांक depth;

	/*
	 * serio->drv is accessed from पूर्णांकerrupt handlers; when modअगरying
	 * caller should acquire serio->drv_mutex and serio->lock.
	 */
	काष्ठा serio_driver *drv;
	/* Protects serio->drv so attributes can pin current driver */
	काष्ठा mutex drv_mutex;

	काष्ठा device dev;

	काष्ठा list_head node;

	/*
	 * For use by PS/2 layer when several ports share hardware and
	 * may get indigestion when exposed to concurrent access (i8042).
	 */
	काष्ठा mutex *ps2_cmd_mutex;
पूर्ण;
#घोषणा to_serio_port(d)	container_of(d, काष्ठा serio, dev)

काष्ठा serio_driver अणु
	स्थिर अक्षर *description;

	स्थिर काष्ठा serio_device_id *id_table;
	bool manual_bind;

	व्योम (*ग_लिखो_wakeup)(काष्ठा serio *);
	irqवापस_t (*पूर्णांकerrupt)(काष्ठा serio *, अचिन्हित अक्षर, अचिन्हित पूर्णांक);
	पूर्णांक  (*connect)(काष्ठा serio *, काष्ठा serio_driver *drv);
	पूर्णांक  (*reconnect)(काष्ठा serio *);
	पूर्णांक  (*fast_reconnect)(काष्ठा serio *);
	व्योम (*disconnect)(काष्ठा serio *);
	व्योम (*cleanup)(काष्ठा serio *);

	काष्ठा device_driver driver;
पूर्ण;
#घोषणा to_serio_driver(d)	container_of(d, काष्ठा serio_driver, driver)

पूर्णांक serio_खोलो(काष्ठा serio *serio, काष्ठा serio_driver *drv);
व्योम serio_बंद(काष्ठा serio *serio);
व्योम serio_rescan(काष्ठा serio *serio);
व्योम serio_reconnect(काष्ठा serio *serio);
irqवापस_t serio_पूर्णांकerrupt(काष्ठा serio *serio, अचिन्हित अक्षर data, अचिन्हित पूर्णांक flags);

व्योम __serio_रेजिस्टर_port(काष्ठा serio *serio, काष्ठा module *owner);

/* use a define to aव्योम include chaining to get THIS_MODULE */
#घोषणा serio_रेजिस्टर_port(serio) \
	__serio_रेजिस्टर_port(serio, THIS_MODULE)

व्योम serio_unरेजिस्टर_port(काष्ठा serio *serio);
व्योम serio_unरेजिस्टर_child_port(काष्ठा serio *serio);

पूर्णांक __must_check __serio_रेजिस्टर_driver(काष्ठा serio_driver *drv,
				काष्ठा module *owner, स्थिर अक्षर *mod_name);

/* use a define to aव्योम include chaining to get THIS_MODULE & मित्रs */
#घोषणा serio_रेजिस्टर_driver(drv) \
	__serio_रेजिस्टर_driver(drv, THIS_MODULE, KBUILD_MODNAME)

व्योम serio_unरेजिस्टर_driver(काष्ठा serio_driver *drv);

/**
 * module_serio_driver() - Helper macro क्रम रेजिस्टरing a serio driver
 * @__serio_driver: serio_driver काष्ठा
 *
 * Helper macro क्रम serio drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module
 * may only use this macro once, and calling it replaces module_init()
 * and module_निकास().
 */
#घोषणा module_serio_driver(__serio_driver) \
	module_driver(__serio_driver, serio_रेजिस्टर_driver, \
		       serio_unरेजिस्टर_driver)

अटल अंतरभूत पूर्णांक serio_ग_लिखो(काष्ठा serio *serio, अचिन्हित अक्षर data)
अणु
	अगर (serio->ग_लिखो)
		वापस serio->ग_लिखो(serio, data);
	अन्यथा
		वापस -1;
पूर्ण

अटल अंतरभूत व्योम serio_drv_ग_लिखो_wakeup(काष्ठा serio *serio)
अणु
	अगर (serio->drv && serio->drv->ग_लिखो_wakeup)
		serio->drv->ग_लिखो_wakeup(serio);
पूर्ण

/*
 * Use the following functions to manipulate serio's per-port
 * driver-specअगरic data.
 */
अटल अंतरभूत व्योम *serio_get_drvdata(काष्ठा serio *serio)
अणु
	वापस dev_get_drvdata(&serio->dev);
पूर्ण

अटल अंतरभूत व्योम serio_set_drvdata(काष्ठा serio *serio, व्योम *data)
अणु
	dev_set_drvdata(&serio->dev, data);
पूर्ण

/*
 * Use the following functions to protect critical sections in
 * driver code from port's पूर्णांकerrupt handler
 */
अटल अंतरभूत व्योम serio_छोड़ो_rx(काष्ठा serio *serio)
अणु
	spin_lock_irq(&serio->lock);
पूर्ण

अटल अंतरभूत व्योम serio_जारी_rx(काष्ठा serio *serio)
अणु
	spin_unlock_irq(&serio->lock);
पूर्ण

#पूर्ण_अगर
