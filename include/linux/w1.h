<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2004 Evgeniy Polyakov <zbr@ioremap.net>
 */

#अगर_अघोषित __LINUX_W1_H
#घोषणा __LINUX_W1_H

#समावेश <linux/device.h>

/**
 * काष्ठा w1_reg_num - broken out slave device id
 *
 * @family: identअगरies the type of device
 * @id: aदीर्घ with family is the unique device id
 * @crc: checksum of the other bytes
 */
काष्ठा w1_reg_num अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
	__u64	family:8,
		id:48,
		crc:8;
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
	__u64	crc:8,
		id:48,
		family:8;
#अन्यथा
#त्रुटि "Please fix <asm/byteorder.h>"
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित __KERNEL__

#घोषणा W1_MAXNAMELEN		32

#घोषणा W1_SEARCH		0xF0
#घोषणा W1_ALARM_SEARCH		0xEC
#घोषणा W1_CONVERT_TEMP		0x44
#घोषणा W1_SKIP_ROM		0xCC
#घोषणा W1_COPY_SCRATCHPAD	0x48
#घोषणा W1_WRITE_SCRATCHPAD	0x4E
#घोषणा W1_READ_SCRATCHPAD	0xBE
#घोषणा W1_READ_ROM		0x33
#घोषणा W1_READ_PSUPPLY		0xB4
#घोषणा W1_MATCH_ROM		0x55
#घोषणा W1_RESUME_CMD		0xA5

/**
 * काष्ठा w1_slave - holds a single slave device on the bus
 *
 * @owner: Poपूर्णांकs to the one wire "wire" kernel module.
 * @name: Device id is ascii.
 * @w1_slave_entry: data क्रम the linked list
 * @reg_num: the slave id in binary
 * @refcnt: reference count, delete when 0
 * @flags: bit flags क्रम W1_SLAVE_ACTIVE W1_SLAVE_DETACH
 * @ttl: decrement per search this slave isn't found, deatch at 0
 * @master: bus which this slave is on
 * @family: module क्रम device family type
 * @family_data: poपूर्णांकer क्रम use by the family module
 * @dev: kernel device identअगरier
 * @hwmon: poपूर्णांकer to hwmon device
 *
 */
काष्ठा w1_slave अणु
	काष्ठा module		*owner;
	अचिन्हित अक्षर		name[W1_MAXNAMELEN];
	काष्ठा list_head	w1_slave_entry;
	काष्ठा w1_reg_num	reg_num;
	atomic_t		refcnt;
	पूर्णांक			ttl;
	अचिन्हित दीर्घ		flags;

	काष्ठा w1_master	*master;
	काष्ठा w1_family	*family;
	व्योम			*family_data;
	काष्ठा device		dev;
	काष्ठा device		*hwmon;
पूर्ण;

प्रकार व्योम (*w1_slave_found_callback)(काष्ठा w1_master *, u64);

/**
 * काष्ठा w1_bus_master - operations available on a bus master
 *
 * @data: the first parameter in all the functions below
 *
 * @पढ़ो_bit: Sample the line level @वापस the level पढ़ो (0 or 1)
 *
 * @ग_लिखो_bit: Sets the line level
 *
 * @touch_bit: the lowest-level function क्रम devices that really support the
 * 1-wire protocol.
 * touch_bit(0) = ग_लिखो-0 cycle
 * touch_bit(1) = ग_लिखो-1 / पढ़ो cycle
 * @वापस the bit पढ़ो (0 or 1)
 *
 * @पढ़ो_byte: Reads a bytes. Same as 8 touch_bit(1) calls.
 * @वापस the byte पढ़ो
 *
 * @ग_लिखो_byte: Writes a byte. Same as 8 touch_bit(x) calls.
 *
 * @पढ़ो_block: Same as a series of पढ़ो_byte() calls
 * @वापस the number of bytes पढ़ो
 *
 * @ग_लिखो_block: Same as a series of ग_लिखो_byte() calls
 *
 * @triplet: Combines two पढ़ोs and a smart ग_लिखो क्रम ROM searches
 * @वापस bit0=Id bit1=comp_id bit2=dir_taken
 *
 * @reset_bus: दीर्घ ग_लिखो-0 with a पढ़ो क्रम the presence pulse detection
 * @वापस -1=Error, 0=Device present, 1=No device present
 *
 * @set_pullup: Put out a strong pull-up pulse of the specअगरied duration.
 * @वापस -1=Error, 0=completed
 *
 * @search: Really nice hardware can handles the dअगरferent types of ROM search
 * w1_master* is passed to the slave found callback.
 * u8 is search_type, W1_SEARCH or W1_ALARM_SEARCH
 *
 * @dev_id: Optional device id string, which w1 slaves could use क्रम
 * creating names, which then give a connection to the w1 master
 *
 * Note: पढ़ो_bit and ग_लिखो_bit are very low level functions and should only
 * be used with hardware that करोesn't really support 1-wire operations,
 * like a parallel/serial port.
 * Either define पढ़ो_bit and ग_लिखो_bit OR define, at minimum, touch_bit and
 * reset_bus.
 *
 */
काष्ठा w1_bus_master अणु
	व्योम		*data;

	u8		(*पढ़ो_bit)(व्योम *);

	व्योम		(*ग_लिखो_bit)(व्योम *, u8);

	u8		(*touch_bit)(व्योम *, u8);

	u8		(*पढ़ो_byte)(व्योम *);

	व्योम		(*ग_लिखो_byte)(व्योम *, u8);

	u8		(*पढ़ो_block)(व्योम *, u8 *, पूर्णांक);

	व्योम		(*ग_लिखो_block)(व्योम *, स्थिर u8 *, पूर्णांक);

	u8		(*triplet)(व्योम *, u8);

	u8		(*reset_bus)(व्योम *);

	u8		(*set_pullup)(व्योम *, पूर्णांक);

	व्योम		(*search)(व्योम *, काष्ठा w1_master *,
		u8, w1_slave_found_callback);

	अक्षर		*dev_id;
पूर्ण;

/**
 * क्रमागत w1_master_flags - bitfields used in w1_master.flags
 * @W1_ABORT_SEARCH: पात searching early on shutकरोwn
 * @W1_WARN_MAX_COUNT: limit warning when the maximum count is reached
 */
क्रमागत w1_master_flags अणु
	W1_ABORT_SEARCH = 0,
	W1_WARN_MAX_COUNT = 1,
पूर्ण;

/**
 * काष्ठा w1_master - one per bus master
 * @w1_master_entry:	master linked list
 * @owner:		module owner
 * @name:		dynamically allocate bus name
 * @list_mutex:		protect slist and async_list
 * @slist:		linked list of slaves
 * @async_list:		linked list of netlink commands to execute
 * @max_slave_count:	maximum number of slaves to search क्रम at a समय
 * @slave_count:	current number of slaves known
 * @attempts:		number of searches ran
 * @slave_ttl:		number of searches beक्रमe a slave is समयd out
 * @initialized:	prevent init/removal race conditions
 * @id:			w1 bus number
 * @search_count:	number of स्वतःmatic searches to run, -1 unlimited
 * @search_id:		allows continuing a search
 * @refcnt:		reference count
 * @priv:		निजी data storage
 * @enable_pullup:	allows a strong pullup
 * @pullup_duration:	समय क्रम the next strong pullup
 * @flags:		one of w1_master_flags
 * @thपढ़ो:		thपढ़ो क्रम bus search and netlink commands
 * @mutex:		protect most of w1_master
 * @bus_mutex:		pretect concurrent bus access
 * @driver:		sysfs driver
 * @dev:		sysfs device
 * @bus_master:		io operations available
 * @seq:		sequence number used क्रम netlink broadcasts
 */
काष्ठा w1_master अणु
	काष्ठा list_head	w1_master_entry;
	काष्ठा module		*owner;
	अचिन्हित अक्षर		name[W1_MAXNAMELEN];
	/* list_mutex protects just slist and async_list so slaves can be
	 * searched क्रम and async commands added जबतक the master has
	 * w1_master.mutex locked and is operating on the bus.
	 * lock order w1_mlock, w1_master.mutex, w1_master.list_mutex
	 */
	काष्ठा mutex		list_mutex;
	काष्ठा list_head	slist;
	काष्ठा list_head	async_list;
	पूर्णांक			max_slave_count, slave_count;
	अचिन्हित दीर्घ		attempts;
	पूर्णांक			slave_ttl;
	पूर्णांक			initialized;
	u32			id;
	पूर्णांक			search_count;
	/* id to start searching on, to जारी a search or 0 to restart */
	u64			search_id;

	atomic_t		refcnt;

	व्योम			*priv;

	/** 5V strong pullup enabled flag, 1 enabled, zero disabled. */
	पूर्णांक			enable_pullup;
	/** 5V strong pullup duration in milliseconds, zero disabled. */
	पूर्णांक			pullup_duration;

	दीर्घ			flags;

	काष्ठा task_काष्ठा	*thपढ़ो;
	काष्ठा mutex		mutex;
	काष्ठा mutex		bus_mutex;

	काष्ठा device_driver	*driver;
	काष्ठा device		dev;

	काष्ठा w1_bus_master	*bus_master;

	u32			seq;
पूर्ण;

पूर्णांक w1_add_master_device(काष्ठा w1_bus_master *master);
व्योम w1_हटाओ_master_device(काष्ठा w1_bus_master *master);

/**
 * काष्ठा w1_family_ops - operations क्रम a family type
 * @add_slave: add_slave
 * @हटाओ_slave: हटाओ_slave
 * @groups: sysfs group
 * @chip_info: poपूर्णांकer to काष्ठा hwmon_chip_info
 */
काष्ठा w1_family_ops अणु
	पूर्णांक  (*add_slave)(काष्ठा w1_slave *sl);
	व्योम (*हटाओ_slave)(काष्ठा w1_slave *sl);
	स्थिर काष्ठा attribute_group **groups;
	स्थिर काष्ठा hwmon_chip_info *chip_info;
पूर्ण;

/**
 * काष्ठा w1_family - reference counted family काष्ठाure.
 * @family_entry:	family linked list
 * @fid:		8 bit family identअगरier
 * @fops:		operations क्रम this family
 * @of_match_table: खोलो firmware match table
 * @refcnt:		reference counter
 */
काष्ठा w1_family अणु
	काष्ठा list_head	family_entry;
	u8			fid;

	स्थिर काष्ठा w1_family_ops *fops;

	स्थिर काष्ठा of_device_id *of_match_table;

	atomic_t		refcnt;
पूर्ण;

पूर्णांक w1_रेजिस्टर_family(काष्ठा w1_family *family);
व्योम w1_unरेजिस्टर_family(काष्ठा w1_family *family);

/**
 * module_w1_family() - Helper macro क्रम रेजिस्टरing a 1-Wire families
 * @__w1_family: w1_family काष्ठा
 *
 * Helper macro क्रम 1-Wire families which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_w1_family(__w1_family) \
	module_driver(__w1_family, w1_रेजिस्टर_family, \
			w1_unरेजिस्टर_family)

u8 w1_triplet(काष्ठा w1_master *dev, पूर्णांक bdir);
u8 w1_touch_bit(काष्ठा w1_master *dev, पूर्णांक bit);
व्योम w1_ग_लिखो_8(काष्ठा w1_master *, u8);
u8 w1_पढ़ो_8(काष्ठा w1_master *);
पूर्णांक w1_reset_bus(काष्ठा w1_master *);
u8 w1_calc_crc8(u8 *, पूर्णांक);
व्योम w1_ग_लिखो_block(काष्ठा w1_master *, स्थिर u8 *, पूर्णांक);
व्योम w1_touch_block(काष्ठा w1_master *, u8 *, पूर्णांक);
u8 w1_पढ़ो_block(काष्ठा w1_master *, u8 *, पूर्णांक);
पूर्णांक w1_reset_select_slave(काष्ठा w1_slave *sl);
पूर्णांक w1_reset_resume_command(काष्ठा w1_master *);
व्योम w1_next_pullup(काष्ठा w1_master *, पूर्णांक);

अटल अंतरभूत काष्ठा w1_slave* dev_to_w1_slave(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा w1_slave, dev);
पूर्ण

अटल अंतरभूत काष्ठा w1_slave* kobj_to_w1_slave(काष्ठा kobject *kobj)
अणु
	वापस dev_to_w1_slave(container_of(kobj, काष्ठा device, kobj));
पूर्ण

अटल अंतरभूत काष्ठा w1_master* dev_to_w1_master(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा w1_master, dev);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */

#पूर्ण_अगर /* __LINUX_W1_H */
