<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs_पूर्णांकernal.h -- definitions पूर्णांकernal to the PCMCIA core modules
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 * (C) 2003 - 2010	Dominik Broकरोwski
 *
 * This file contains definitions _only_ needed by the PCMCIA core modules.
 * It must not be included by PCMCIA socket drivers or by PCMCIA device
 * drivers.
 */

#अगर_अघोषित _LINUX_CS_INTERNAL_H
#घोषणा _LINUX_CS_INTERNAL_H

#समावेश <linux/kref.h>

/* Flags in client state */
#घोषणा CLIENT_WIN_REQ(i)	(0x1<<(i))

/* Flag to access all functions */
#घोषणा BIND_FN_ALL	0xff

/* Each card function माला_लो one of these guys */
प्रकार काष्ठा config_t अणु
	काष्ठा kref	ref;
	अचिन्हित पूर्णांक	state;

	काष्ठा resource io[MAX_IO_WIN]; /* io ports */
	काष्ठा resource mem[MAX_WIN];   /* mem areas */
पूर्ण config_t;


काष्ठा cis_cache_entry अणु
	काष्ठा list_head	node;
	अचिन्हित पूर्णांक		addr;
	अचिन्हित पूर्णांक		len;
	अचिन्हित पूर्णांक		attr;
	अचिन्हित अक्षर		cache[];
पूर्ण;

काष्ठा pccard_resource_ops अणु
	पूर्णांक	(*validate_mem)		(काष्ठा pcmcia_socket *s);
	पूर्णांक	(*find_io)		(काष्ठा pcmcia_socket *s,
					 अचिन्हित पूर्णांक attr,
					 अचिन्हित पूर्णांक *base,
					 अचिन्हित पूर्णांक num,
					 अचिन्हित पूर्णांक align,
					 काष्ठा resource **parent);
	काष्ठा resource* (*find_mem)	(अचिन्हित दीर्घ base, अचिन्हित दीर्घ num,
					 अचिन्हित दीर्घ align, पूर्णांक low,
					 काष्ठा pcmcia_socket *s);
	पूर्णांक	(*init)			(काष्ठा pcmcia_socket *s);
	व्योम	(*निकास)			(काष्ठा pcmcia_socket *s);
पूर्ण;

/* Flags in config state */
#घोषणा CONFIG_LOCKED		0x01
#घोषणा CONFIG_IRQ_REQ		0x02
#घोषणा CONFIG_IO_REQ		0x04

/* Flags in socket state */
#घोषणा SOCKET_PRESENT		0x0008
#घोषणा SOCKET_INUSE		0x0010
#घोषणा SOCKET_IN_RESUME	0x0040
#घोषणा SOCKET_SUSPEND		0x0080
#घोषणा SOCKET_WIN_REQ(i)	(0x0100<<(i))
#घोषणा SOCKET_CARDBUS		0x8000
#घोषणा SOCKET_CARDBUS_CONFIG	0x10000


/*
 * Stuff पूर्णांकernal to module "pcmcia_rsrc":
 */
बाह्य पूर्णांक अटल_init(काष्ठा pcmcia_socket *s);
बाह्य काष्ठा resource *pcmcia_make_resource(resource_माप_प्रकार start,
					resource_माप_प्रकार end,
					अचिन्हित दीर्घ flags, स्थिर अक्षर *name);

/*
 * Stuff पूर्णांकernal to module "pcmcia_core":
 */

/* socket_sysfs.c */
बाह्य पूर्णांक pccard_sysfs_add_socket(काष्ठा device *dev);
बाह्य व्योम pccard_sysfs_हटाओ_socket(काष्ठा device *dev);

/* cardbus.c */
पूर्णांक cb_alloc(काष्ठा pcmcia_socket *s);
व्योम cb_मुक्त(काष्ठा pcmcia_socket *s);



/*
 * Stuff exported by module "pcmcia_core" to module "pcmcia"
 */

काष्ठा pcmcia_callbackअणु
	काष्ठा module	*owner;
	पूर्णांक		(*add) (काष्ठा pcmcia_socket *s);
	पूर्णांक		(*हटाओ) (काष्ठा pcmcia_socket *s);
	व्योम		(*requery) (काष्ठा pcmcia_socket *s);
	पूर्णांक		(*validate) (काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक *i);
	पूर्णांक		(*suspend) (काष्ठा pcmcia_socket *s);
	पूर्णांक		(*early_resume) (काष्ठा pcmcia_socket *s);
	पूर्णांक		(*resume) (काष्ठा pcmcia_socket *s);
पूर्ण;

/* cs.c */
बाह्य काष्ठा rw_semaphore pcmcia_socket_list_rwsem;
बाह्य काष्ठा list_head pcmcia_socket_list;
बाह्य काष्ठा class pcmcia_socket_class;

पूर्णांक pccard_रेजिस्टर_pcmcia(काष्ठा pcmcia_socket *s, काष्ठा pcmcia_callback *c);
काष्ठा pcmcia_socket *pcmcia_get_socket_by_nr(अचिन्हित पूर्णांक nr);

व्योम pcmcia_parse_uevents(काष्ठा pcmcia_socket *socket, अचिन्हित पूर्णांक events);
#घोषणा PCMCIA_UEVENT_EJECT	0x0001
#घोषणा PCMCIA_UEVENT_INSERT	0x0002
#घोषणा PCMCIA_UEVENT_SUSPEND	0x0004
#घोषणा PCMCIA_UEVENT_RESUME	0x0008
#घोषणा PCMCIA_UEVENT_REQUERY	0x0010

काष्ठा pcmcia_socket *pcmcia_get_socket(काष्ठा pcmcia_socket *skt);
व्योम pcmcia_put_socket(काष्ठा pcmcia_socket *skt);

/*
 * Stuff पूर्णांकernal to module "pcmcia".
 */
/* ds.c */
बाह्य काष्ठा bus_type pcmcia_bus_type;

काष्ठा pcmcia_device;

/* pcmcia_resource.c */
बाह्य पूर्णांक pcmcia_release_configuration(काष्ठा pcmcia_device *p_dev);
बाह्य पूर्णांक pcmcia_validate_mem(काष्ठा pcmcia_socket *s);
बाह्य काष्ठा resource *pcmcia_find_mem_region(u_दीर्घ base,
					       u_दीर्घ num,
					       u_दीर्घ align,
					       पूर्णांक low,
					       काष्ठा pcmcia_socket *s);

व्योम pcmcia_cleanup_irq(काष्ठा pcmcia_socket *s);
पूर्णांक pcmcia_setup_irq(काष्ठा pcmcia_device *p_dev);

/* cistpl.c */
बाह्य स्थिर काष्ठा bin_attribute pccard_cis_attr;

पूर्णांक pcmcia_पढ़ो_cis_mem(काष्ठा pcmcia_socket *s, पूर्णांक attr,
			u_पूर्णांक addr, u_पूर्णांक len, व्योम *ptr);
पूर्णांक pcmcia_ग_लिखो_cis_mem(काष्ठा pcmcia_socket *s, पूर्णांक attr,
			u_पूर्णांक addr, u_पूर्णांक len, व्योम *ptr);
व्योम release_cis_mem(काष्ठा pcmcia_socket *s);
व्योम destroy_cis_cache(काष्ठा pcmcia_socket *s);
पूर्णांक pccard_पढ़ो_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
		      cisdata_t code, व्योम *parse);
पूर्णांक pcmcia_replace_cis(काष्ठा pcmcia_socket *s,
		       स्थिर u8 *data, स्थिर माप_प्रकार len);
पूर्णांक pccard_validate_cis(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक *count);
पूर्णांक verअगरy_cis_cache(काष्ठा pcmcia_socket *s);

पूर्णांक pccard_get_first_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
			tuple_t *tuple);

पूर्णांक pccard_get_next_tuple(काष्ठा pcmcia_socket *s, अचिन्हित पूर्णांक function,
			tuple_t *tuple);

पूर्णांक pccard_get_tuple_data(काष्ठा pcmcia_socket *s, tuple_t *tuple);

#पूर्ण_अगर /* _LINUX_CS_INTERNAL_H */
