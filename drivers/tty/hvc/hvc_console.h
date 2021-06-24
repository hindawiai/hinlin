<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * hvc_console.h
 * Copyright (C) 2005 IBM Corporation
 *
 * Author(s):
 * 	Ryan S. Arnold <rsa@us.ibm.com>
 *
 * hvc_console header inक्रमmation:
 *      moved here from arch/घातerpc/include/यंत्र/hvconsole.h
 *      and drivers/अक्षर/hvc_console.c
 */

#अगर_अघोषित HVC_CONSOLE_H
#घोषणा HVC_CONSOLE_H
#समावेश <linux/kref.h>
#समावेश <linux/tty.h>
#समावेश <linux/spinlock.h>

/*
 * This is the max number of console adapters that can/will be found as
 * console devices on first stage console init.  Any number beyond this range
 * can't be used as a console device but is still a valid tty device.
 */
#घोषणा MAX_NR_HVC_CONSOLES	16

/*
 * The Linux TTY code करोes not support dynamic addition of tty derived devices
 * so we need to know how many tty devices we might need when space is allocated
 * क्रम the tty device.  Since this driver supports hotplug of vty adapters we
 * need to make sure we have enough allocated.
 */
#घोषणा HVC_ALLOC_TTY_ADAPTERS	8

काष्ठा hvc_काष्ठा अणु
	काष्ठा tty_port port;
	spinlock_t lock;
	पूर्णांक index;
	पूर्णांक करो_wakeup;
	अक्षर *outbuf;
	पूर्णांक outbuf_size;
	पूर्णांक n_outbuf;
	uपूर्णांक32_t vtermno;
	स्थिर काष्ठा hv_ops *ops;
	पूर्णांक irq_requested;
	पूर्णांक data;
	काष्ठा winsize ws;
	काष्ठा work_काष्ठा tty_resize;
	काष्ठा list_head next;
	अचिन्हित दीर्घ flags;
पूर्ण;

/* implemented by a low level driver */
काष्ठा hv_ops अणु
	पूर्णांक (*get_अक्षरs)(uपूर्णांक32_t vtermno, अक्षर *buf, पूर्णांक count);
	पूर्णांक (*put_अक्षरs)(uपूर्णांक32_t vtermno, स्थिर अक्षर *buf, पूर्णांक count);
	पूर्णांक (*flush)(uपूर्णांक32_t vtermno, bool रुको);

	/* Callbacks क्रम notअगरication. Called in खोलो, बंद and hangup */
	पूर्णांक (*notअगरier_add)(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq);
	व्योम (*notअगरier_del)(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq);
	व्योम (*notअगरier_hangup)(काष्ठा hvc_काष्ठा *hp, पूर्णांक irq);

	/* tiocmget/set implementation */
	पूर्णांक (*tiocmget)(काष्ठा hvc_काष्ठा *hp);
	पूर्णांक (*tiocmset)(काष्ठा hvc_काष्ठा *hp, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clear);

	/* Callbacks to handle tty ports */
	व्योम (*dtr_rts)(काष्ठा hvc_काष्ठा *hp, पूर्णांक उठाओ);
पूर्ण;

/* Register a vterm and a slot index क्रम use as a console (console_init) */
बाह्य पूर्णांक hvc_instantiate(uपूर्णांक32_t vtermno, पूर्णांक index,
			   स्थिर काष्ठा hv_ops *ops);

/* रेजिस्टर a vterm क्रम hvc tty operation (module_init or hotplug add) */
बाह्य काष्ठा hvc_काष्ठा * hvc_alloc(uपूर्णांक32_t vtermno, पूर्णांक data,
				     स्थिर काष्ठा hv_ops *ops, पूर्णांक outbuf_size);
/* हटाओ a vterm from hvc tty operation (module_निकास or hotplug हटाओ) */
बाह्य पूर्णांक hvc_हटाओ(काष्ठा hvc_काष्ठा *hp);

/* data available */
पूर्णांक hvc_poll(काष्ठा hvc_काष्ठा *hp);
व्योम hvc_kick(व्योम);

/* Resize hvc tty terminal winकरोw */
बाह्य व्योम __hvc_resize(काष्ठा hvc_काष्ठा *hp, काष्ठा winsize ws);

अटल अंतरभूत व्योम hvc_resize(काष्ठा hvc_काष्ठा *hp, काष्ठा winsize ws)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hp->lock, flags);
	__hvc_resize(hp, ws);
	spin_unlock_irqrestore(&hp->lock, flags);
पूर्ण

/* शेष notअगरier क्रम irq based notअगरication */
बाह्य पूर्णांक notअगरier_add_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक data);
बाह्य व्योम notअगरier_del_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक data);
बाह्य व्योम notअगरier_hangup_irq(काष्ठा hvc_काष्ठा *hp, पूर्णांक data);


#अगर defined(CONFIG_XMON) && defined(CONFIG_SMP)
#समावेश <यंत्र/xmon.h>
#अन्यथा
अटल अंतरभूत पूर्णांक cpus_are_in_xmon(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर // HVC_CONSOLE_H
