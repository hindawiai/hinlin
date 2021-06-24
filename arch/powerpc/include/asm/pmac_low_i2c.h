<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 *  include/यंत्र-ppc/pmac_low_i2c.h
 *
 *  Copyright (C) 2003 Ben. Herrenschmidt (benh@kernel.crashing.org)
 */
#अगर_अघोषित __PMAC_LOW_I2C_H__
#घोषणा __PMAC_LOW_I2C_H__
#अगर_घोषित __KERNEL__

/* i2c mode (based on the platक्रमm functions क्रमmat) */
क्रमागत अणु
	pmac_i2c_mode_dumb	= 1,
	pmac_i2c_mode_std	= 2,
	pmac_i2c_mode_stdsub	= 3,
	pmac_i2c_mode_combined	= 4,
पूर्ण;

/* RW bit in address */
क्रमागत अणु
	pmac_i2c_पढ़ो		= 0x01,
	pmac_i2c_ग_लिखो		= 0x00
पूर्ण;

/* i2c bus type */
क्रमागत अणु
	pmac_i2c_bus_keywest	= 0,
	pmac_i2c_bus_pmu	= 1,
	pmac_i2c_bus_smu	= 2,
पूर्ण;

/* i2c bus features */
क्रमागत अणु
	/* can_largesub : supports >1 byte subaddresses (SMU only) */
	pmac_i2c_can_largesub	= 0x00000001u,

	/* multibus : device node holds multiple busses, bus number is
	 * encoded in bits 0xff00 of "reg" of a given device
	 */
	pmac_i2c_multibus	= 0x00000002u,
पूर्ण;

/* i2c busses in the प्रणाली */
काष्ठा pmac_i2c_bus;
काष्ठा i2c_adapter;

/* Init, called early during boot */
बाह्य पूर्णांक pmac_i2c_init(व्योम);

/* Lookup an i2c bus क्रम a device-node. The node can be either the bus
 * node itself or a device below it. In the हाल of a multibus, the bus
 * node itself is the controller node, अन्यथा, it's a child of the controller
 * node
 */
बाह्य काष्ठा pmac_i2c_bus *pmac_i2c_find_bus(काष्ठा device_node *node);

/* Get the address क्रम an i2c device. This strips the bus number अगर
 * necessary. The 7 bits address is वापसed 1 bit right shअगरted so that the
 * direction can be directly ored in
 */
बाह्य u8 pmac_i2c_get_dev_addr(काष्ठा device_node *device);

/* Get infos about a bus */
बाह्य काष्ठा device_node *pmac_i2c_get_controller(काष्ठा pmac_i2c_bus *bus);
बाह्य काष्ठा device_node *pmac_i2c_get_bus_node(काष्ठा pmac_i2c_bus *bus);
बाह्य पूर्णांक pmac_i2c_get_type(काष्ठा pmac_i2c_bus *bus);
बाह्य पूर्णांक pmac_i2c_get_flags(काष्ठा pmac_i2c_bus *bus);
बाह्य पूर्णांक pmac_i2c_get_channel(काष्ठा pmac_i2c_bus *bus);

/* i2c layer adapter helpers */
बाह्य काष्ठा i2c_adapter *pmac_i2c_get_adapter(काष्ठा pmac_i2c_bus *bus);
बाह्य काष्ठा pmac_i2c_bus *pmac_i2c_adapter_to_bus(काष्ठा i2c_adapter *adapter);

/* March a device or bus with an i2c adapter काष्ठाure, to be used by drivers
 * to match device-tree nodes with i2c adapters during adapter discovery
 * callbacks
 */
बाह्य पूर्णांक pmac_i2c_match_adapter(काष्ठा device_node *dev,
				  काष्ठा i2c_adapter *adapter);


/* (legacy) Locking functions exposed to i2c-keywest */
बाह्य पूर्णांक pmac_low_i2c_lock(काष्ठा device_node *np);
बाह्य पूर्णांक pmac_low_i2c_unlock(काष्ठा device_node *np);

/* Access functions क्रम platक्रमm code */
बाह्य पूर्णांक pmac_i2c_खोलो(काष्ठा pmac_i2c_bus *bus, पूर्णांक polled);
बाह्य व्योम pmac_i2c_बंद(काष्ठा pmac_i2c_bus *bus);
बाह्य पूर्णांक pmac_i2c_seपंचांगode(काष्ठा pmac_i2c_bus *bus, पूर्णांक mode);
बाह्य पूर्णांक pmac_i2c_xfer(काष्ठा pmac_i2c_bus *bus, u8 addrdir, पूर्णांक subsize,
			 u32 subaddr, u8 *data,  पूर्णांक len);

/* Suspend/resume code called by via-pmu directly क्रम now */
बाह्य व्योम pmac_pfunc_i2c_suspend(व्योम);
बाह्य व्योम pmac_pfunc_i2c_resume(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __PMAC_LOW_I2C_H__ */
