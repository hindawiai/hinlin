<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ss.h
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999             David A. Hinds
 */

#अगर_अघोषित _LINUX_SS_H
#घोषणा _LINUX_SS_H

#समावेश <linux/device.h>
#समावेश <linux/sched.h>	/* task_काष्ठा, completion */
#समावेश <linux/mutex.h>

#अगर_घोषित CONFIG_CARDBUS
#समावेश <linux/pci.h>
#पूर्ण_अगर

/* Definitions क्रम card status flags क्रम GetStatus */
#घोषणा SS_WRPROT	0x0001
#घोषणा SS_CARDLOCK	0x0002
#घोषणा SS_EJECTION	0x0004
#घोषणा SS_INSERTION	0x0008
#घोषणा SS_BATDEAD	0x0010
#घोषणा SS_BATWARN	0x0020
#घोषणा SS_READY	0x0040
#घोषणा SS_DETECT	0x0080
#घोषणा SS_POWERON	0x0100
#घोषणा SS_GPI		0x0200
#घोषणा SS_STSCHG	0x0400
#घोषणा SS_CARDBUS	0x0800
#घोषणा SS_3VCARD	0x1000
#घोषणा SS_XVCARD	0x2000
#घोषणा SS_PENDING	0x4000
#घोषणा SS_ZVCARD	0x8000

/* InquireSocket capabilities */
#घोषणा SS_CAP_PAGE_REGS	0x0001
#घोषणा SS_CAP_VIRTUAL_BUS	0x0002
#घोषणा SS_CAP_MEM_ALIGN	0x0004
#घोषणा SS_CAP_STATIC_MAP	0x0008
#घोषणा SS_CAP_PCCARD		0x4000
#घोषणा SS_CAP_CARDBUS		0x8000

/* क्रम GetSocket, SetSocket */
प्रकार काष्ठा socket_state_t अणु
	u_पूर्णांक	flags;
	u_पूर्णांक	csc_mask;
	u_अक्षर	Vcc, Vpp;
	u_अक्षर	io_irq;
पूर्ण socket_state_t;

बाह्य socket_state_t dead_socket;

/* Socket configuration flags */
#घोषणा SS_PWR_AUTO	0x0010
#घोषणा SS_IOCARD	0x0020
#घोषणा SS_RESET	0x0040
#घोषणा SS_DMA_MODE	0x0080
#घोषणा SS_SPKR_ENA	0x0100
#घोषणा SS_OUTPUT_ENA	0x0200

/* Flags क्रम I/O port and memory winकरोws */
#घोषणा MAP_ACTIVE	0x01
#घोषणा MAP_16BIT	0x02
#घोषणा MAP_AUTOSZ	0x04
#घोषणा MAP_0WS		0x08
#घोषणा MAP_WRPROT	0x10
#घोषणा MAP_ATTRIB	0x20
#घोषणा MAP_USE_WAIT	0x40
#घोषणा MAP_PREFETCH	0x80

/* Use this just क्रम bridge winकरोws */
#घोषणा MAP_IOSPACE	0x20

/* घातer hook operations */
#घोषणा HOOK_POWER_PRE	0x01
#घोषणा HOOK_POWER_POST	0x02

प्रकार काष्ठा pccard_io_map अणु
	u_अक्षर	map;
	u_अक्षर	flags;
	u_लघु	speed;
	phys_addr_t start, stop;
पूर्ण pccard_io_map;

प्रकार काष्ठा pccard_mem_map अणु
	u_अक्षर		map;
	u_अक्षर		flags;
	u_लघु		speed;
	phys_addr_t	अटल_start;
	u_पूर्णांक		card_start;
	काष्ठा resource	*res;
पूर्ण pccard_mem_map;

प्रकार काष्ठा io_winकरोw_t अणु
	u_पूर्णांक			InUse, Config;
	काष्ठा resource		*res;
पूर्ण io_winकरोw_t;

/* Maximum number of IO winकरोws per socket */
#घोषणा MAX_IO_WIN 2

/* Maximum number of memory winकरोws per socket */
#घोषणा MAX_WIN 4


/*
 * Socket operations.
 */
काष्ठा pcmcia_socket;
काष्ठा pccard_resource_ops;
काष्ठा config_t;
काष्ठा pcmcia_callback;
काष्ठा user_info_t;

काष्ठा pccard_operations अणु
	पूर्णांक (*init)(काष्ठा pcmcia_socket *s);
	पूर्णांक (*suspend)(काष्ठा pcmcia_socket *s);
	पूर्णांक (*get_status)(काष्ठा pcmcia_socket *s, u_पूर्णांक *value);
	पूर्णांक (*set_socket)(काष्ठा pcmcia_socket *s, socket_state_t *state);
	पूर्णांक (*set_io_map)(काष्ठा pcmcia_socket *s, काष्ठा pccard_io_map *io);
	पूर्णांक (*set_mem_map)(काष्ठा pcmcia_socket *s, काष्ठा pccard_mem_map *mem);
पूर्ण;

काष्ठा pcmcia_socket अणु
	काष्ठा module			*owner;
	socket_state_t			socket;
	u_पूर्णांक				state;
	u_पूर्णांक				suspended_state;	/* state beक्रमe suspend */
	u_लघु				functions;
	u_लघु				lock_count;
	pccard_mem_map			cis_mem;
	व्योम __iomem 			*cis_virt;
	io_winकरोw_t			io[MAX_IO_WIN];
	pccard_mem_map			win[MAX_WIN];
	काष्ठा list_head		cis_cache;
	माप_प्रकार				fake_cis_len;
	u8				*fake_cis;

	काष्ठा list_head		socket_list;
	काष्ठा completion		socket_released;

	/* deprecated */
	अचिन्हित पूर्णांक			sock;		/* socket number */


	/* socket capabilities */
	u_पूर्णांक				features;
	u_पूर्णांक				irq_mask;
	u_पूर्णांक				map_size;
	u_पूर्णांक				io_offset;
	u_पूर्णांक				pci_irq;
	काष्ठा pci_dev			*cb_dev;

	/* socket setup is करोne so resources should be able to be allocated.
	 * Only अगर set to 1, calls to find_अणुio,memपूर्ण_region are handled, and
	 * insertio events are actually managed by the PCMCIA layer.*/
	u8				resource_setup_करोne;

	/* socket operations */
	काष्ठा pccard_operations	*ops;
	काष्ठा pccard_resource_ops	*resource_ops;
	व्योम				*resource_data;

	/* Zoom video behaviour is so chip specअगरic its not worth adding
	   this to _ops */
	व्योम 				(*zoom_video)(काष्ठा pcmcia_socket *,
						      पूर्णांक);

	/* so is घातer hook */
	पूर्णांक (*घातer_hook)(काष्ठा pcmcia_socket *sock, पूर्णांक operation);

	/* allows tuning the CB bridge beक्रमe loading driver क्रम the CB card */
#अगर_घोषित CONFIG_CARDBUS
	व्योम (*tune_bridge)(काष्ठा pcmcia_socket *sock, काष्ठा pci_bus *bus);
#पूर्ण_अगर

	/* state thपढ़ो */
	काष्ठा task_काष्ठा		*thपढ़ो;
	काष्ठा completion		thपढ़ो_करोne;
	अचिन्हित पूर्णांक			thपढ़ो_events;
	अचिन्हित पूर्णांक			sysfs_events;

	/* For the non-trivial पूर्णांकeraction between these locks,
	 * see Documentation/pcmcia/locking.rst */
	काष्ठा mutex			skt_mutex;
	काष्ठा mutex			ops_mutex;

	/* protects thपढ़ो_events and sysfs_events */
	spinlock_t			thपढ़ो_lock;

	/* pcmcia (16-bit) */
	काष्ठा pcmcia_callback		*callback;

#अगर defined(CONFIG_PCMCIA) || defined(CONFIG_PCMCIA_MODULE)
	/* The following elements refer to 16-bit PCMCIA devices inserted
	 * पूर्णांकo the socket */
	काष्ठा list_head		devices_list;

	/* the number of devices, used only पूर्णांकernally and subject to
	 * incorrectness and change */
	u8				device_count;

	/* करोes the PCMCIA card consist of two pseuकरो devices? */
	u8				pcmcia_pfc;

	/* non-zero अगर PCMCIA card is present */
	atomic_t			present;

	/* IRQ to be used by PCMCIA devices. May not be IRQ 0. */
	अचिन्हित पूर्णांक			pcmcia_irq;

#पूर्ण_अगर /* CONFIG_PCMCIA */

	/* socket device */
	काष्ठा device			dev;
	/* data पूर्णांकernal to the socket driver */
	व्योम				*driver_data;
	/* status of the card during resume from a प्रणाली sleep state */
	पूर्णांक				resume_status;
पूर्ण;


/* socket drivers must define the resource operations type they use. There
 * are three options:
 * - pccard_अटल_ops		iomem and ioport areas are asचिन्हित अटलally
 * - pccard_iodyn_ops		iomem areas is asचिन्हित अटलally, ioport
 *				areas dynamically
 *				If this option is selected, use
 *				"select PCCARD_IODYN" in Kconfig.
 * - pccard_nonअटल_ops	iomem and ioport areas are asचिन्हित dynamically.
 *				If this option is selected, use
 *				"select PCCARD_NONSTATIC" in Kconfig.
 *
 */
बाह्य काष्ठा pccard_resource_ops pccard_अटल_ops;
#अगर defined(CONFIG_PCMCIA) || defined(CONFIG_PCMCIA_MODULE)
बाह्य काष्ठा pccard_resource_ops pccard_iodyn_ops;
बाह्य काष्ठा pccard_resource_ops pccard_nonअटल_ops;
#अन्यथा
/* If PCMCIA is not used, but only CARDBUS, these functions are not used
 * at all. Thereक्रमe, करो not use the large (240K!) rsrc_nonअटल module
 */
#घोषणा pccard_iodyn_ops pccard_अटल_ops
#घोषणा pccard_nonअटल_ops pccard_अटल_ops
#पूर्ण_अगर


/* socket drivers use this callback in their IRQ handler */
बाह्य व्योम pcmcia_parse_events(काष्ठा pcmcia_socket *socket,
				अचिन्हित पूर्णांक events);

/* to रेजिस्टर and unरेजिस्टर a socket */
बाह्य पूर्णांक pcmcia_रेजिस्टर_socket(काष्ठा pcmcia_socket *socket);
बाह्य व्योम pcmcia_unरेजिस्टर_socket(काष्ठा pcmcia_socket *socket);


#पूर्ण_अगर /* _LINUX_SS_H */
