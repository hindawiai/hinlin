<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ds.h -- 16-bit PCMCIA core support
 *
 * The initial developer of the original code is David A. Hinds
 * <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
 * are Copyright (C) 1999 David A. Hinds.  All Rights Reserved.
 *
 * (C) 1999		David A. Hinds
 * (C) 2003 - 2008	Dominik Broकरोwski
 */

#अगर_अघोषित _LINUX_DS_H
#घोषणा _LINUX_DS_H

#अगर_घोषित __KERNEL__
#समावेश <linux/mod_devicetable.h>
#पूर्ण_अगर

#समावेश <pcmcia/device_id.h>

#अगर_घोषित __KERNEL__
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <pcmcia/ss.h>
#समावेश <linux/atomic.h>


/*
 * PCMCIA device drivers (16-bit cards only; 32-bit cards require CardBus
 * a.k.a. PCI drivers
 */
काष्ठा pcmcia_socket;
काष्ठा pcmcia_device;
काष्ठा config_t;
काष्ठा net_device;

/* dynamic device IDs क्रम PCMCIA device drivers. See
 * Documentation/pcmcia/driver.rst क्रम details.
*/
काष्ठा pcmcia_dynids अणु
	काष्ठा mutex		lock;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा pcmcia_driver अणु
	स्थिर अक्षर		*name;

	पूर्णांक (*probe)		(काष्ठा pcmcia_device *dev);
	व्योम (*हटाओ)		(काष्ठा pcmcia_device *dev);

	पूर्णांक (*suspend)		(काष्ठा pcmcia_device *dev);
	पूर्णांक (*resume)		(काष्ठा pcmcia_device *dev);

	काष्ठा module		*owner;
	स्थिर काष्ठा pcmcia_device_id	*id_table;
	काष्ठा device_driver	drv;
	काष्ठा pcmcia_dynids	dynids;
पूर्ण;

/* driver registration */
पूर्णांक pcmcia_रेजिस्टर_driver(काष्ठा pcmcia_driver *driver);
व्योम pcmcia_unरेजिस्टर_driver(काष्ठा pcmcia_driver *driver);

/**
 * module_pcmcia_driver() - Helper macro क्रम रेजिस्टरing a pcmcia driver
 * @__pcmcia_driver: pcmcia_driver काष्ठा
 *
 * Helper macro क्रम pcmcia drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only use
 * this macro once, and calling it replaces module_init() and module_निकास().
 */
#घोषणा module_pcmcia_driver(__pcmcia_driver) \
	module_driver(__pcmcia_driver, pcmcia_रेजिस्टर_driver, \
			pcmcia_unरेजिस्टर_driver)

/* क्रम काष्ठा resource * array embedded in काष्ठा pcmcia_device */
क्रमागत अणु
	PCMCIA_IOPORT_0,
	PCMCIA_IOPORT_1,
	PCMCIA_IOMEM_0,
	PCMCIA_IOMEM_1,
	PCMCIA_IOMEM_2,
	PCMCIA_IOMEM_3,
	PCMCIA_NUM_RESOURCES,
पूर्ण;

काष्ठा pcmcia_device अणु
	/* the socket and the device_no [क्रम multअगरunction devices]
	   uniquely define a pcmcia_device */
	काष्ठा pcmcia_socket	*socket;

	अक्षर			*devname;

	u8			device_no;

	/* the hardware "function" device; certain subdevices can
	 * share one hardware "function" device. */
	u8			func;
	काष्ठा config_t		*function_config;

	काष्ठा list_head	socket_device_list;

	/* device setup */
	अचिन्हित पूर्णांक		irq;
	काष्ठा resource		*resource[PCMCIA_NUM_RESOURCES];
	resource_माप_प्रकार		card_addr;	/* क्रम the 1st IOMEM resource */
	अचिन्हित पूर्णांक		vpp;

	अचिन्हित पूर्णांक		config_flags;	/* CONF_ENABLE_ flags below */
	अचिन्हित पूर्णांक		config_base;
	अचिन्हित पूर्णांक		config_index;
	अचिन्हित पूर्णांक		config_regs;	/* PRESENT_ flags below */
	अचिन्हित पूर्णांक		io_lines;	/* number of I/O lines */

	/* Is the device suspended? */
	u16			suspended:1;

	/* Flags whether io, irq, win configurations were
	 * requested, and whether the configuration is "locked" */
	u16			_irq:1;
	u16			_io:1;
	u16			_win:4;
	u16			_locked:1;

	/* Flag whether a "fuzzy" func_id based match is
	 * allowed. */
	u16			allow_func_id_match:1;

	/* inक्रमmation about this device */
	u16			has_manf_id:1;
	u16			has_card_id:1;
	u16			has_func_id:1;

	u16			reserved:4;

	u8			func_id;
	u16			manf_id;
	u16			card_id;

	अक्षर			*prod_id[4];

	u64			dma_mask;
	काष्ठा device		dev;

	/* data निजी to drivers */
	व्योम			*priv;
	अचिन्हित पूर्णांक		खोलो;
पूर्ण;

#घोषणा to_pcmcia_dev(n) container_of(n, काष्ठा pcmcia_device, dev)
#घोषणा to_pcmcia_drv(n) container_of(n, काष्ठा pcmcia_driver, drv)


/*
 * CIS access.
 *
 * Please use the following functions to access CIS tuples:
 * - pcmcia_get_tuple()
 * - pcmcia_loop_tuple()
 * - pcmcia_get_mac_from_cis()
 *
 * To parse a tuple_t, pcmcia_parse_tuple() exists. Its पूर्णांकerface
 * might change in future.
 */

/* get the very first CIS entry of type @code. Note that buf is poपूर्णांकer
 * to u8 *buf; and that you need to kमुक्त(buf) afterwards. */
माप_प्रकार pcmcia_get_tuple(काष्ठा pcmcia_device *p_dev, cisdata_t code,
			u8 **buf);

/* loop over CIS entries */
पूर्णांक pcmcia_loop_tuple(काष्ठा pcmcia_device *p_dev, cisdata_t code,
		      पूर्णांक (*loop_tuple) (काष्ठा pcmcia_device *p_dev,
					 tuple_t *tuple,
					 व्योम *priv_data),
		      व्योम *priv_data);

/* get the MAC address from CISTPL_FUNCE */
पूर्णांक pcmcia_get_mac_from_cis(काष्ठा pcmcia_device *p_dev,
			    काष्ठा net_device *dev);


/* parse a tuple_t */
पूर्णांक pcmcia_parse_tuple(tuple_t *tuple, cisparse_t *parse);

/* loop CIS entries क्रम valid configuration */
पूर्णांक pcmcia_loop_config(काष्ठा pcmcia_device *p_dev,
		       पूर्णांक	(*conf_check)	(काष्ठा pcmcia_device *p_dev,
						 व्योम *priv_data),
		       व्योम *priv_data);

/* is the device still there? */
काष्ठा pcmcia_device *pcmcia_dev_present(काष्ठा pcmcia_device *p_dev);

/* low-level पूर्णांकerface reset */
पूर्णांक pcmcia_reset_card(काष्ठा pcmcia_socket *skt);

/* CIS config */
पूर्णांक pcmcia_पढ़ो_config_byte(काष्ठा pcmcia_device *p_dev, off_t where, u8 *val);
पूर्णांक pcmcia_ग_लिखो_config_byte(काष्ठा pcmcia_device *p_dev, off_t where, u8 val);

/* device configuration */
पूर्णांक pcmcia_request_io(काष्ठा pcmcia_device *p_dev);

पूर्णांक __must_check pcmcia_request_irq(काष्ठा pcmcia_device *p_dev,
				irq_handler_t handler);

पूर्णांक pcmcia_enable_device(काष्ठा pcmcia_device *p_dev);

पूर्णांक pcmcia_request_winकरोw(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res,
			अचिन्हित पूर्णांक speed);
पूर्णांक pcmcia_release_winकरोw(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res);
पूर्णांक pcmcia_map_mem_page(काष्ठा pcmcia_device *p_dev, काष्ठा resource *res,
			अचिन्हित पूर्णांक offset);

पूर्णांक pcmcia_fixup_vpp(काष्ठा pcmcia_device *p_dev, अचिन्हित अक्षर new_vpp);
पूर्णांक pcmcia_fixup_iowidth(काष्ठा pcmcia_device *p_dev);

व्योम pcmcia_disable_device(काष्ठा pcmcia_device *p_dev);

/* IO ports */
#घोषणा IO_DATA_PATH_WIDTH	0x18
#घोषणा IO_DATA_PATH_WIDTH_8	0x00
#घोषणा IO_DATA_PATH_WIDTH_16	0x08
#घोषणा IO_DATA_PATH_WIDTH_AUTO	0x10

/* IO memory */
#घोषणा WIN_MEMORY_TYPE_CM	0x00 /* शेष */
#घोषणा WIN_MEMORY_TYPE_AM	0x20 /* MAP_ATTRIB */
#घोषणा WIN_DATA_WIDTH_8	0x00 /* शेष */
#घोषणा WIN_DATA_WIDTH_16	0x02 /* MAP_16BIT */
#घोषणा WIN_ENABLE		0x01 /* MAP_ACTIVE */
#घोषणा WIN_USE_WAIT		0x40 /* MAP_USE_WAIT */

#घोषणा WIN_FLAGS_MAP		0x63 /* MAP_ATTRIB | MAP_16BIT | MAP_ACTIVE |
					MAP_USE_WAIT */
#घोषणा WIN_FLAGS_REQ		0x1c /* mapping to socket->win[i]:
					0x04 -> 0
					0x08 -> 1
					0x0c -> 2
					0x10 -> 3 */

/* config_regअणुisterपूर्णs present क्रम this PCMCIA device */
#घोषणा PRESENT_OPTION		0x001
#घोषणा PRESENT_STATUS		0x002
#घोषणा PRESENT_PIN_REPLACE	0x004
#घोषणा PRESENT_COPY		0x008
#घोषणा PRESENT_EXT_STATUS	0x010
#घोषणा PRESENT_IOBASE_0	0x020
#घोषणा PRESENT_IOBASE_1	0x040
#घोषणा PRESENT_IOBASE_2	0x080
#घोषणा PRESENT_IOBASE_3	0x100
#घोषणा PRESENT_IOSIZE		0x200

/* flags to be passed to pcmcia_enable_device() */
#घोषणा CONF_ENABLE_IRQ         0x0001
#घोषणा CONF_ENABLE_SPKR        0x0002
#घोषणा CONF_ENABLE_PULSE_IRQ   0x0004
#घोषणा CONF_ENABLE_ESR         0x0008
#घोषणा CONF_ENABLE_IOCARD	0x0010 /* स्वतः-enabled अगर IO resources or IRQ
					* (CONF_ENABLE_IRQ) in use */
#घोषणा CONF_ENABLE_ZVCARD	0x0020

/* flags used by pcmcia_loop_config() स्वतःconfiguration */
#घोषणा CONF_AUTO_CHECK_VCC	0x0100 /* check क्रम matching Vcc? */
#घोषणा CONF_AUTO_SET_VPP	0x0200 /* set Vpp? */
#घोषणा CONF_AUTO_AUDIO		0x0400 /* enable audio line? */
#घोषणा CONF_AUTO_SET_IO	0x0800 /* set ->resource[0,1] */
#घोषणा CONF_AUTO_SET_IOMEM	0x1000 /* set ->resource[2] */

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* _LINUX_DS_H */
