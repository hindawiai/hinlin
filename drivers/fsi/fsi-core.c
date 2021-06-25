<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FSI core driver
 *
 * Copyright (C) IBM Corporation 2016
 *
 * TODO:
 *  - Rework topology
 *  - s/chip_id/chip_loc
 *  - s/cfam/chip (cfam_id -> chip_id etc...)
 */

#समावेश <linux/crc4.h>
#समावेश <linux/device.h>
#समावेश <linux/fsi.h>
#समावेश <linux/idr.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>

#समावेश "fsi-master.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fsi.h>

#घोषणा FSI_SLAVE_CONF_NEXT_MASK	GENMASK(31, 31)
#घोषणा FSI_SLAVE_CONF_SLOTS_MASK	GENMASK(23, 16)
#घोषणा FSI_SLAVE_CONF_SLOTS_SHIFT	16
#घोषणा FSI_SLAVE_CONF_VERSION_MASK	GENMASK(15, 12)
#घोषणा FSI_SLAVE_CONF_VERSION_SHIFT	12
#घोषणा FSI_SLAVE_CONF_TYPE_MASK	GENMASK(11, 4)
#घोषणा FSI_SLAVE_CONF_TYPE_SHIFT	4
#घोषणा FSI_SLAVE_CONF_CRC_SHIFT	4
#घोषणा FSI_SLAVE_CONF_CRC_MASK		GENMASK(3, 0)
#घोषणा FSI_SLAVE_CONF_DATA_BITS	28

#घोषणा FSI_PEEK_BASE			0x410

अटल स्थिर पूर्णांक engine_page_size = 0x400;

#घोषणा FSI_SLAVE_BASE			0x800

/*
 * FSI slave engine control रेजिस्टर offsets
 */
#घोषणा FSI_SMODE		0x0	/* R/W: Mode रेजिस्टर */
#घोषणा FSI_SISC		0x8	/* R/W: Interrupt condition */
#घोषणा FSI_SSTAT		0x14	/* R  : Slave status */
#घोषणा FSI_SLBUS		0x30	/* W  : LBUS Ownership */
#घोषणा FSI_LLMODE		0x100	/* R/W: Link layer mode रेजिस्टर */

/*
 * SMODE fields
 */
#घोषणा FSI_SMODE_WSC		0x80000000	/* Warm start करोne */
#घोषणा FSI_SMODE_ECRC		0x20000000	/* Hw CRC check */
#घोषणा FSI_SMODE_SID_SHIFT	24		/* ID shअगरt */
#घोषणा FSI_SMODE_SID_MASK	3		/* ID Mask */
#घोषणा FSI_SMODE_ED_SHIFT	20		/* Echo delay shअगरt */
#घोषणा FSI_SMODE_ED_MASK	0xf		/* Echo delay mask */
#घोषणा FSI_SMODE_SD_SHIFT	16		/* Send delay shअगरt */
#घोषणा FSI_SMODE_SD_MASK	0xf		/* Send delay mask */
#घोषणा FSI_SMODE_LBCRR_SHIFT	8		/* Clk ratio shअगरt */
#घोषणा FSI_SMODE_LBCRR_MASK	0xf		/* Clk ratio mask */

/*
 * SLBUS fields
 */
#घोषणा FSI_SLBUS_FORCE		0x80000000	/* Force LBUS ownership */

/*
 * LLMODE fields
 */
#घोषणा FSI_LLMODE_ASYNC	0x1

#घोषणा FSI_SLAVE_SIZE_23b		0x800000

अटल DEFINE_IDA(master_ida);

काष्ठा fsi_slave अणु
	काष्ठा device		dev;
	काष्ठा fsi_master	*master;
	काष्ठा cdev		cdev;
	पूर्णांक			cdev_idx;
	पूर्णांक			id;	/* FSI address */
	पूर्णांक			link;	/* FSI link# */
	u32			cfam_id;
	पूर्णांक			chip_id;
	uपूर्णांक32_t		size;	/* size of slave address space */
	u8			t_send_delay;
	u8			t_echo_delay;
पूर्ण;

#घोषणा to_fsi_master(d) container_of(d, काष्ठा fsi_master, dev)
#घोषणा to_fsi_slave(d) container_of(d, काष्ठा fsi_slave, dev)

अटल स्थिर पूर्णांक slave_retries = 2;
अटल पूर्णांक discard_errors;

अटल dev_t fsi_base_dev;
अटल DEFINE_IDA(fsi_minor_ida);
#घोषणा FSI_अक्षर_उच्च_DEVICES	0x1000

/* Legacy /dev numbering: 4 devices per chip, 16 chips */
#घोषणा FSI_CHAR_LEGACY_TOP	64

अटल पूर्णांक fsi_master_पढ़ो(काष्ठा fsi_master *master, पूर्णांक link,
		uपूर्णांक8_t slave_id, uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size);
अटल पूर्णांक fsi_master_ग_लिखो(काष्ठा fsi_master *master, पूर्णांक link,
		uपूर्णांक8_t slave_id, uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size);
अटल पूर्णांक fsi_master_अवरोध(काष्ठा fsi_master *master, पूर्णांक link);

/*
 * fsi_device_पढ़ो() / fsi_device_ग_लिखो() / fsi_device_peek()
 *
 * FSI endpoपूर्णांक-device support
 *
 * Read / ग_लिखो / peek accessors क्रम a client
 *
 * Parameters:
 * dev:  Structure passed to FSI client device drivers on probe().
 * addr: FSI address of given device.  Client should pass in its base address
 *       plus desired offset to access its रेजिस्टर space.
 * val:  For पढ़ो/peek this is the value पढ़ो at the specअगरied address. For
 *       ग_लिखो this is value to ग_लिखो to the specअगरied address.
 *       The data in val must be FSI bus endian (big endian).
 * size: Size in bytes of the operation.  Sizes supported are 1, 2 and 4 bytes.
 *       Addresses must be aligned on size boundaries or an error will result.
 */
पूर्णांक fsi_device_पढ़ो(काष्ठा fsi_device *dev, uपूर्णांक32_t addr, व्योम *val,
		माप_प्रकार size)
अणु
	अगर (addr > dev->size || size > dev->size || addr > dev->size - size)
		वापस -EINVAL;

	वापस fsi_slave_पढ़ो(dev->slave, dev->addr + addr, val, size);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_device_पढ़ो);

पूर्णांक fsi_device_ग_लिखो(काष्ठा fsi_device *dev, uपूर्णांक32_t addr, स्थिर व्योम *val,
		माप_प्रकार size)
अणु
	अगर (addr > dev->size || size > dev->size || addr > dev->size - size)
		वापस -EINVAL;

	वापस fsi_slave_ग_लिखो(dev->slave, dev->addr + addr, val, size);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_device_ग_लिखो);

पूर्णांक fsi_device_peek(काष्ठा fsi_device *dev, व्योम *val)
अणु
	uपूर्णांक32_t addr = FSI_PEEK_BASE + ((dev->unit - 2) * माप(uपूर्णांक32_t));

	वापस fsi_slave_पढ़ो(dev->slave, addr, val, माप(uपूर्णांक32_t));
पूर्ण

अटल व्योम fsi_device_release(काष्ठा device *_device)
अणु
	काष्ठा fsi_device *device = to_fsi_dev(_device);

	of_node_put(device->dev.of_node);
	kमुक्त(device);
पूर्ण

अटल काष्ठा fsi_device *fsi_create_device(काष्ठा fsi_slave *slave)
अणु
	काष्ठा fsi_device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	dev->dev.parent = &slave->dev;
	dev->dev.bus = &fsi_bus_type;
	dev->dev.release = fsi_device_release;

	वापस dev;
पूर्ण

/* FSI slave support */
अटल पूर्णांक fsi_slave_calc_addr(काष्ठा fsi_slave *slave, uपूर्णांक32_t *addrp,
		uपूर्णांक8_t *idp)
अणु
	uपूर्णांक32_t addr = *addrp;
	uपूर्णांक8_t id = *idp;

	अगर (addr > slave->size)
		वापस -EINVAL;

	/* For 23 bit addressing, we encode the extra two bits in the slave
	 * id (and the slave's actual ID needs to be 0).
	 */
	अगर (addr > 0x1fffff) अणु
		अगर (slave->id != 0)
			वापस -EINVAL;
		id = (addr >> 21) & 0x3;
		addr &= 0x1fffff;
	पूर्ण

	*addrp = addr;
	*idp = id;
	वापस 0;
पूर्ण

अटल पूर्णांक fsi_slave_report_and_clear_errors(काष्ठा fsi_slave *slave)
अणु
	काष्ठा fsi_master *master = slave->master;
	__be32 irq, stat;
	पूर्णांक rc, link;
	uपूर्णांक8_t id;

	link = slave->link;
	id = slave->id;

	rc = fsi_master_पढ़ो(master, link, id, FSI_SLAVE_BASE + FSI_SISC,
			&irq, माप(irq));
	अगर (rc)
		वापस rc;

	rc =  fsi_master_पढ़ो(master, link, id, FSI_SLAVE_BASE + FSI_SSTAT,
			&stat, माप(stat));
	अगर (rc)
		वापस rc;

	dev_dbg(&slave->dev, "status: 0x%08x, sisc: 0x%08x\n",
			be32_to_cpu(stat), be32_to_cpu(irq));

	/* clear पूर्णांकerrupts */
	वापस fsi_master_ग_लिखो(master, link, id, FSI_SLAVE_BASE + FSI_SISC,
			&irq, माप(irq));
पूर्ण

/* Encode slave local bus echo delay */
अटल अंतरभूत uपूर्णांक32_t fsi_smode_echodly(पूर्णांक x)
अणु
	वापस (x & FSI_SMODE_ED_MASK) << FSI_SMODE_ED_SHIFT;
पूर्ण

/* Encode slave local bus send delay */
अटल अंतरभूत uपूर्णांक32_t fsi_smode_senddly(पूर्णांक x)
अणु
	वापस (x & FSI_SMODE_SD_MASK) << FSI_SMODE_SD_SHIFT;
पूर्ण

/* Encode slave local bus घड़ी rate ratio */
अटल अंतरभूत uपूर्णांक32_t fsi_smode_lbcrr(पूर्णांक x)
अणु
	वापस (x & FSI_SMODE_LBCRR_MASK) << FSI_SMODE_LBCRR_SHIFT;
पूर्ण

/* Encode slave ID */
अटल अंतरभूत uपूर्णांक32_t fsi_smode_sid(पूर्णांक x)
अणु
	वापस (x & FSI_SMODE_SID_MASK) << FSI_SMODE_SID_SHIFT;
पूर्ण

अटल uपूर्णांक32_t fsi_slave_smode(पूर्णांक id, u8 t_senddly, u8 t_echodly)
अणु
	वापस FSI_SMODE_WSC | FSI_SMODE_ECRC
		| fsi_smode_sid(id)
		| fsi_smode_echodly(t_echodly - 1) | fsi_smode_senddly(t_senddly - 1)
		| fsi_smode_lbcrr(0x8);
पूर्ण

अटल पूर्णांक fsi_slave_set_smode(काष्ठा fsi_slave *slave)
अणु
	uपूर्णांक32_t smode;
	__be32 data;

	/* set our smode रेजिस्टर with the slave ID field to 0; this enables
	 * extended slave addressing
	 */
	smode = fsi_slave_smode(slave->id, slave->t_send_delay, slave->t_echo_delay);
	data = cpu_to_be32(smode);

	वापस fsi_master_ग_लिखो(slave->master, slave->link, slave->id,
				FSI_SLAVE_BASE + FSI_SMODE,
				&data, माप(data));
पूर्ण

अटल पूर्णांक fsi_slave_handle_error(काष्ठा fsi_slave *slave, bool ग_लिखो,
				  uपूर्णांक32_t addr, माप_प्रकार size)
अणु
	काष्ठा fsi_master *master = slave->master;
	पूर्णांक rc, link;
	uपूर्णांक32_t reg;
	uपूर्णांक8_t id, send_delay, echo_delay;

	अगर (discard_errors)
		वापस -1;

	link = slave->link;
	id = slave->id;

	dev_dbg(&slave->dev, "handling error on %s to 0x%08x[%zd]",
			ग_लिखो ? "write" : "read", addr, size);

	/* try a simple clear of error conditions, which may fail अगर we've lost
	 * communication with the slave
	 */
	rc = fsi_slave_report_and_clear_errors(slave);
	अगर (!rc)
		वापस 0;

	/* send a TERM and retry */
	अगर (master->term) अणु
		rc = master->term(master, link, id);
		अगर (!rc) अणु
			rc = fsi_master_पढ़ो(master, link, id, 0,
					&reg, माप(reg));
			अगर (!rc)
				rc = fsi_slave_report_and_clear_errors(slave);
			अगर (!rc)
				वापस 0;
		पूर्ण
	पूर्ण

	send_delay = slave->t_send_delay;
	echo_delay = slave->t_echo_delay;

	/* getting serious, reset the slave via BREAK */
	rc = fsi_master_अवरोध(master, link);
	अगर (rc)
		वापस rc;

	slave->t_send_delay = send_delay;
	slave->t_echo_delay = echo_delay;

	rc = fsi_slave_set_smode(slave);
	अगर (rc)
		वापस rc;

	अगर (master->link_config)
		master->link_config(master, link,
				    slave->t_send_delay,
				    slave->t_echo_delay);

	वापस fsi_slave_report_and_clear_errors(slave);
पूर्ण

पूर्णांक fsi_slave_पढ़ो(काष्ठा fsi_slave *slave, uपूर्णांक32_t addr,
			व्योम *val, माप_प्रकार size)
अणु
	uपूर्णांक8_t id = slave->id;
	पूर्णांक rc, err_rc, i;

	rc = fsi_slave_calc_addr(slave, &addr, &id);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < slave_retries; i++) अणु
		rc = fsi_master_पढ़ो(slave->master, slave->link,
				id, addr, val, size);
		अगर (!rc)
			अवरोध;

		err_rc = fsi_slave_handle_error(slave, false, addr, size);
		अगर (err_rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_slave_पढ़ो);

पूर्णांक fsi_slave_ग_लिखो(काष्ठा fsi_slave *slave, uपूर्णांक32_t addr,
			स्थिर व्योम *val, माप_प्रकार size)
अणु
	uपूर्णांक8_t id = slave->id;
	पूर्णांक rc, err_rc, i;

	rc = fsi_slave_calc_addr(slave, &addr, &id);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < slave_retries; i++) अणु
		rc = fsi_master_ग_लिखो(slave->master, slave->link,
				id, addr, val, size);
		अगर (!rc)
			अवरोध;

		err_rc = fsi_slave_handle_error(slave, true, addr, size);
		अगर (err_rc)
			अवरोध;
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_slave_ग_लिखो);

बाह्य पूर्णांक fsi_slave_claim_range(काष्ठा fsi_slave *slave,
		uपूर्णांक32_t addr, uपूर्णांक32_t size)
अणु
	अगर (addr + size < addr)
		वापस -EINVAL;

	अगर (addr + size > slave->size)
		वापस -EINVAL;

	/* toकरो: check क्रम overlapping claims */
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_slave_claim_range);

बाह्य व्योम fsi_slave_release_range(काष्ठा fsi_slave *slave,
		uपूर्णांक32_t addr, uपूर्णांक32_t size)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(fsi_slave_release_range);

अटल bool fsi_device_node_matches(काष्ठा device *dev, काष्ठा device_node *np,
		uपूर्णांक32_t addr, uपूर्णांक32_t size)
अणु
	अचिन्हित पूर्णांक len, na, ns;
	स्थिर __be32 *prop;
	uपूर्णांक32_t psize;

	na = of_n_addr_cells(np);
	ns = of_n_size_cells(np);

	अगर (na != 1 || ns != 1)
		वापस false;

	prop = of_get_property(np, "reg", &len);
	अगर (!prop || len != 8)
		वापस false;

	अगर (of_पढ़ो_number(prop, 1) != addr)
		वापस false;

	psize = of_पढ़ो_number(prop + 1, 1);
	अगर (psize != size) अणु
		dev_warn(dev,
			"node %s matches probed address, but not size (got 0x%x, expected 0x%x)",
			of_node_full_name(np), psize, size);
	पूर्ण

	वापस true;
पूर्ण

/* Find a matching node क्रम the slave engine at @address, using @size bytes
 * of space. Returns शून्य अगर not found, or a matching node with refcount
 * alपढ़ोy incremented.
 */
अटल काष्ठा device_node *fsi_device_find_of_node(काष्ठा fsi_device *dev)
अणु
	काष्ठा device_node *parent, *np;

	parent = dev_of_node(&dev->slave->dev);
	अगर (!parent)
		वापस शून्य;

	क्रम_each_child_of_node(parent, np) अणु
		अगर (fsi_device_node_matches(&dev->dev, np,
					dev->addr, dev->size))
			वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक fsi_slave_scan(काष्ठा fsi_slave *slave)
अणु
	uपूर्णांक32_t engine_addr;
	पूर्णांक rc, i;

	/*
	 * scan engines
	 *
	 * We keep the peek mode and slave engines क्रम the core; so start
	 * at the third slot in the configuration table. We also need to
	 * skip the chip ID entry at the start of the address space.
	 */
	engine_addr = engine_page_size * 3;
	क्रम (i = 2; i < engine_page_size / माप(uपूर्णांक32_t); i++) अणु
		uपूर्णांक8_t slots, version, type, crc;
		काष्ठा fsi_device *dev;
		uपूर्णांक32_t conf;
		__be32 data;

		rc = fsi_slave_पढ़ो(slave, (i + 1) * माप(data),
				&data, माप(data));
		अगर (rc) अणु
			dev_warn(&slave->dev,
				"error reading slave registers\n");
			वापस -1;
		पूर्ण
		conf = be32_to_cpu(data);

		crc = crc4(0, conf, 32);
		अगर (crc) अणु
			dev_warn(&slave->dev,
				"crc error in slave register at 0x%04x\n",
				i);
			वापस -1;
		पूर्ण

		slots = (conf & FSI_SLAVE_CONF_SLOTS_MASK)
			>> FSI_SLAVE_CONF_SLOTS_SHIFT;
		version = (conf & FSI_SLAVE_CONF_VERSION_MASK)
			>> FSI_SLAVE_CONF_VERSION_SHIFT;
		type = (conf & FSI_SLAVE_CONF_TYPE_MASK)
			>> FSI_SLAVE_CONF_TYPE_SHIFT;

		/*
		 * Unused address areas are marked by a zero type value; this
		 * skips the defined address areas
		 */
		अगर (type != 0 && slots != 0) अणु

			/* create device */
			dev = fsi_create_device(slave);
			अगर (!dev)
				वापस -ENOMEM;

			dev->slave = slave;
			dev->engine_type = type;
			dev->version = version;
			dev->unit = i;
			dev->addr = engine_addr;
			dev->size = slots * engine_page_size;

			dev_dbg(&slave->dev,
			"engine[%i]: type %x, version %x, addr %x size %x\n",
					dev->unit, dev->engine_type, version,
					dev->addr, dev->size);

			dev_set_name(&dev->dev, "%02x:%02x:%02x:%02x",
					slave->master->idx, slave->link,
					slave->id, i - 2);
			dev->dev.of_node = fsi_device_find_of_node(dev);

			rc = device_रेजिस्टर(&dev->dev);
			अगर (rc) अणु
				dev_warn(&slave->dev, "add failed: %d\n", rc);
				put_device(&dev->dev);
			पूर्ण
		पूर्ण

		engine_addr += slots * engine_page_size;

		अगर (!(conf & FSI_SLAVE_CONF_NEXT_MASK))
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ aligned_access_size(माप_प्रकार offset, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ offset_unit, count_unit;

	/* Criteria:
	 *
	 * 1. Access size must be less than or equal to the maximum access
	 *    width or the highest घातer-of-two factor of offset
	 * 2. Access size must be less than or equal to the amount specअगरied by
	 *    count
	 *
	 * The access width is optimal अगर we can calculate 1 to be strictly
	 * equal जबतक still satisfying 2.
	 */

	/* Find 1 by the bottom bit of offset (with a 4 byte access cap) */
	offset_unit = BIT(__builtin_ctzl(offset | 4));

	/* Find 2 by the top bit of count */
	count_unit = BIT(8 * माप(अचिन्हित दीर्घ) - 1 - __builtin_clzl(count));

	/* Constrain the maximum access width to the minimum of both criteria */
	वापस BIT(__builtin_ctzl(offset_unit | count_unit));
पूर्ण

अटल sमाप_प्रकार fsi_slave_sysfs_raw_पढ़ो(काष्ठा file *file,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr, अक्षर *buf,
		loff_t off, माप_प्रकार count)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(kobj_to_dev(kobj));
	माप_प्रकार total_len, पढ़ो_len;
	पूर्णांक rc;

	अगर (off < 0)
		वापस -EINVAL;

	अगर (off > 0xffffffff || count > 0xffffffff || off + count > 0xffffffff)
		वापस -EINVAL;

	क्रम (total_len = 0; total_len < count; total_len += पढ़ो_len) अणु
		पढ़ो_len = aligned_access_size(off, count - total_len);

		rc = fsi_slave_पढ़ो(slave, off, buf + total_len, पढ़ो_len);
		अगर (rc)
			वापस rc;

		off += पढ़ो_len;
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार fsi_slave_sysfs_raw_ग_लिखो(काष्ठा file *file,
		काष्ठा kobject *kobj, काष्ठा bin_attribute *attr,
		अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(kobj_to_dev(kobj));
	माप_प्रकार total_len, ग_लिखो_len;
	पूर्णांक rc;

	अगर (off < 0)
		वापस -EINVAL;

	अगर (off > 0xffffffff || count > 0xffffffff || off + count > 0xffffffff)
		वापस -EINVAL;

	क्रम (total_len = 0; total_len < count; total_len += ग_लिखो_len) अणु
		ग_लिखो_len = aligned_access_size(off, count - total_len);

		rc = fsi_slave_ग_लिखो(slave, off, buf + total_len, ग_लिखो_len);
		अगर (rc)
			वापस rc;

		off += ग_लिखो_len;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute fsi_slave_raw_attr = अणु
	.attr = अणु
		.name = "raw",
		.mode = 0600,
	पूर्ण,
	.size = 0,
	.पढ़ो = fsi_slave_sysfs_raw_पढ़ो,
	.ग_लिखो = fsi_slave_sysfs_raw_ग_लिखो,
पूर्ण;

अटल व्योम fsi_slave_release(काष्ठा device *dev)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

	fsi_मुक्त_minor(slave->dev.devt);
	of_node_put(dev->of_node);
	kमुक्त(slave);
पूर्ण

अटल bool fsi_slave_node_matches(काष्ठा device_node *np,
		पूर्णांक link, uपूर्णांक8_t id)
अणु
	अचिन्हित पूर्णांक len, na, ns;
	स्थिर __be32 *prop;

	na = of_n_addr_cells(np);
	ns = of_n_size_cells(np);

	/* Ensure we have the correct क्रमmat क्रम addresses and sizes in
	 * reg properties
	 */
	अगर (na != 2 || ns != 0)
		वापस false;

	prop = of_get_property(np, "reg", &len);
	अगर (!prop || len != 8)
		वापस false;

	वापस (of_पढ़ो_number(prop, 1) == link) &&
		(of_पढ़ो_number(prop + 1, 1) == id);
पूर्ण

/* Find a matching node क्रम the slave at (link, id). Returns शून्य अगर none
 * found, or a matching node with refcount alपढ़ोy incremented.
 */
अटल काष्ठा device_node *fsi_slave_find_of_node(काष्ठा fsi_master *master,
		पूर्णांक link, uपूर्णांक8_t id)
अणु
	काष्ठा device_node *parent, *np;

	parent = dev_of_node(&master->dev);
	अगर (!parent)
		वापस शून्य;

	क्रम_each_child_of_node(parent, np) अणु
		अगर (fsi_slave_node_matches(np, link, id))
			वापस np;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल sमाप_प्रकार cfam_पढ़ो(काष्ठा file *filep, अक्षर __user *buf, माप_प्रकार count,
			 loff_t *offset)
अणु
	काष्ठा fsi_slave *slave = filep->निजी_data;
	माप_प्रकार total_len, पढ़ो_len;
	loff_t off = *offset;
	sमाप_प्रकार rc;

	अगर (off < 0)
		वापस -EINVAL;

	अगर (off > 0xffffffff || count > 0xffffffff || off + count > 0xffffffff)
		वापस -EINVAL;

	क्रम (total_len = 0; total_len < count; total_len += पढ़ो_len) अणु
		__be32 data;

		पढ़ो_len = min_t(माप_प्रकार, count, 4);
		पढ़ो_len -= off & 0x3;

		rc = fsi_slave_पढ़ो(slave, off, &data, पढ़ो_len);
		अगर (rc)
			जाओ fail;
		rc = copy_to_user(buf + total_len, &data, पढ़ो_len);
		अगर (rc) अणु
			rc = -EFAULT;
			जाओ fail;
		पूर्ण
		off += पढ़ो_len;
	पूर्ण
	rc = count;
 fail:
	*offset = off;
	वापस count;
पूर्ण

अटल sमाप_प्रकार cfam_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *offset)
अणु
	काष्ठा fsi_slave *slave = filep->निजी_data;
	माप_प्रकार total_len, ग_लिखो_len;
	loff_t off = *offset;
	sमाप_प्रकार rc;


	अगर (off < 0)
		वापस -EINVAL;

	अगर (off > 0xffffffff || count > 0xffffffff || off + count > 0xffffffff)
		वापस -EINVAL;

	क्रम (total_len = 0; total_len < count; total_len += ग_लिखो_len) अणु
		__be32 data;

		ग_लिखो_len = min_t(माप_प्रकार, count, 4);
		ग_लिखो_len -= off & 0x3;

		rc = copy_from_user(&data, buf + total_len, ग_लिखो_len);
		अगर (rc) अणु
			rc = -EFAULT;
			जाओ fail;
		पूर्ण
		rc = fsi_slave_ग_लिखो(slave, off, &data, ग_लिखो_len);
		अगर (rc)
			जाओ fail;
		off += ग_लिखो_len;
	पूर्ण
	rc = count;
 fail:
	*offset = off;
	वापस count;
पूर्ण

अटल loff_t cfam_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल प्रस्तुत_से:
		अवरोध;
	हाल शुरू_से:
		file->f_pos = offset;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस offset;
पूर्ण

अटल पूर्णांक cfam_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा fsi_slave *slave = container_of(inode->i_cdev, काष्ठा fsi_slave, cdev);

	file->निजी_data = slave;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations cfam_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= cfam_खोलो,
	.llseek		= cfam_llseek,
	.पढ़ो		= cfam_पढ़ो,
	.ग_लिखो		= cfam_ग_लिखो,
पूर्ण;

अटल sमाप_प्रकार send_term_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);
	काष्ठा fsi_master *master = slave->master;

	अगर (!master->term)
		वापस -ENODEV;

	master->term(master, slave->link, slave->id);
	वापस count;
पूर्ण

अटल DEVICE_ATTR_WO(send_term);

अटल sमाप_प्रकार slave_send_echo_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

	वापस प्र_लिखो(buf, "%u\n", slave->t_send_delay);
पूर्ण

अटल sमाप_प्रकार slave_send_echo_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);
	काष्ठा fsi_master *master = slave->master;
	अचिन्हित दीर्घ val;
	पूर्णांक rc;

	अगर (kम_से_अदीर्घ(buf, 0, &val) < 0)
		वापस -EINVAL;

	अगर (val < 1 || val > 16)
		वापस -EINVAL;

	अगर (!master->link_config)
		वापस -ENXIO;

	/* Current HW mandates that send and echo delay are identical */
	slave->t_send_delay = val;
	slave->t_echo_delay = val;

	rc = fsi_slave_set_smode(slave);
	अगर (rc < 0)
		वापस rc;
	अगर (master->link_config)
		master->link_config(master, slave->link,
				    slave->t_send_delay,
				    slave->t_echo_delay);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(send_echo_delays, 0600,
		   slave_send_echo_show, slave_send_echo_store);

अटल sमाप_प्रकार chip_id_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

	वापस प्र_लिखो(buf, "%d\n", slave->chip_id);
पूर्ण

अटल DEVICE_ATTR_RO(chip_id);

अटल sमाप_प्रकार cfam_id_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

	वापस प्र_लिखो(buf, "0x%x\n", slave->cfam_id);
पूर्ण

अटल DEVICE_ATTR_RO(cfam_id);

अटल काष्ठा attribute *cfam_attr[] = अणु
	&dev_attr_send_echo_delays.attr,
	&dev_attr_chip_id.attr,
	&dev_attr_cfam_id.attr,
	&dev_attr_send_term.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group cfam_attr_group = अणु
	.attrs = cfam_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cfam_attr_groups[] = अणु
	&cfam_attr_group,
	शून्य,
पूर्ण;

अटल अक्षर *cfam_devnode(काष्ठा device *dev, umode_t *mode,
			  kuid_t *uid, kgid_t *gid)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

#अगर_घोषित CONFIG_FSI_NEW_DEV_NODE
	वापस kaप्र_लिखो(GFP_KERNEL, "fsi/cfam%d", slave->cdev_idx);
#अन्यथा
	वापस kaप्र_लिखो(GFP_KERNEL, "cfam%d", slave->cdev_idx);
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा device_type cfam_type = अणु
	.name = "cfam",
	.devnode = cfam_devnode,
	.groups = cfam_attr_groups
पूर्ण;

अटल अक्षर *fsi_cdev_devnode(काष्ठा device *dev, umode_t *mode,
			      kuid_t *uid, kgid_t *gid)
अणु
#अगर_घोषित CONFIG_FSI_NEW_DEV_NODE
	वापस kaप्र_लिखो(GFP_KERNEL, "fsi/%s", dev_name(dev));
#अन्यथा
	वापस kaप्र_लिखो(GFP_KERNEL, "%s", dev_name(dev));
#पूर्ण_अगर
पूर्ण

स्थिर काष्ठा device_type fsi_cdev_type = अणु
	.name = "fsi-cdev",
	.devnode = fsi_cdev_devnode,
पूर्ण;
EXPORT_SYMBOL_GPL(fsi_cdev_type);

/* Backward compatible /dev/ numbering in "old style" mode */
अटल पूर्णांक fsi_adjust_index(पूर्णांक index)
अणु
#अगर_घोषित CONFIG_FSI_NEW_DEV_NODE
	वापस index;
#अन्यथा
	वापस index + 1;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __fsi_get_new_minor(काष्ठा fsi_slave *slave, क्रमागत fsi_dev_type type,
			       dev_t *out_dev, पूर्णांक *out_index)
अणु
	पूर्णांक cid = slave->chip_id;
	पूर्णांक id;

	/* Check अगर we qualअगरy क्रम legacy numbering */
	अगर (cid >= 0 && cid < 16 && type < 4) अणु
		/* Try reserving the legacy number */
		id = (cid << 4) | type;
		id = ida_simple_get(&fsi_minor_ida, id, id + 1, GFP_KERNEL);
		अगर (id >= 0) अणु
			*out_index = fsi_adjust_index(cid);
			*out_dev = fsi_base_dev + id;
			वापस 0;
		पूर्ण
		/* Other failure */
		अगर (id != -ENOSPC)
			वापस id;
		/* Fallback to non-legacy allocation */
	पूर्ण
	id = ida_simple_get(&fsi_minor_ida, FSI_CHAR_LEGACY_TOP,
			    FSI_अक्षर_उच्च_DEVICES, GFP_KERNEL);
	अगर (id < 0)
		वापस id;
	*out_index = fsi_adjust_index(id);
	*out_dev = fsi_base_dev + id;
	वापस 0;
पूर्ण

पूर्णांक fsi_get_new_minor(काष्ठा fsi_device *fdev, क्रमागत fsi_dev_type type,
		      dev_t *out_dev, पूर्णांक *out_index)
अणु
	वापस __fsi_get_new_minor(fdev->slave, type, out_dev, out_index);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_get_new_minor);

व्योम fsi_मुक्त_minor(dev_t dev)
अणु
	ida_simple_हटाओ(&fsi_minor_ida, MINOR(dev));
पूर्ण
EXPORT_SYMBOL_GPL(fsi_मुक्त_minor);

अटल पूर्णांक fsi_slave_init(काष्ठा fsi_master *master, पूर्णांक link, uपूर्णांक8_t id)
अणु
	uपूर्णांक32_t cfam_id;
	काष्ठा fsi_slave *slave;
	uपूर्णांक8_t crc;
	__be32 data, llmode, slbus;
	पूर्णांक rc;

	/* Currently, we only support single slaves on a link, and use the
	 * full 23-bit address range
	 */
	अगर (id != 0)
		वापस -EINVAL;

	rc = fsi_master_पढ़ो(master, link, id, 0, &data, माप(data));
	अगर (rc) अणु
		dev_dbg(&master->dev, "can't read slave %02x:%02x %d\n",
				link, id, rc);
		वापस -ENODEV;
	पूर्ण
	cfam_id = be32_to_cpu(data);

	crc = crc4(0, cfam_id, 32);
	अगर (crc) अणु
		dev_warn(&master->dev, "slave %02x:%02x invalid cfam id CRC!\n",
				link, id);
		वापस -EIO;
	पूर्ण

	dev_dbg(&master->dev, "fsi: found chip %08x at %02x:%02x:%02x\n",
			cfam_id, master->idx, link, id);

	/* If we're behind a master that doesn't provide a self-running bus
	 * घड़ी, put the slave पूर्णांकo async mode
	 */
	अगर (master->flags & FSI_MASTER_FLAG_SWCLOCK) अणु
		llmode = cpu_to_be32(FSI_LLMODE_ASYNC);
		rc = fsi_master_ग_लिखो(master, link, id,
				FSI_SLAVE_BASE + FSI_LLMODE,
				&llmode, माप(llmode));
		अगर (rc)
			dev_warn(&master->dev,
				"can't set llmode on slave:%02x:%02x %d\n",
				link, id, rc);
	पूर्ण

	/* We can communicate with a slave; create the slave device and
	 * रेजिस्टर.
	 */
	slave = kzalloc(माप(*slave), GFP_KERNEL);
	अगर (!slave)
		वापस -ENOMEM;

	dev_set_name(&slave->dev, "slave@%02x:%02x", link, id);
	slave->dev.type = &cfam_type;
	slave->dev.parent = &master->dev;
	slave->dev.of_node = fsi_slave_find_of_node(master, link, id);
	slave->dev.release = fsi_slave_release;
	device_initialize(&slave->dev);
	slave->cfam_id = cfam_id;
	slave->master = master;
	slave->link = link;
	slave->id = id;
	slave->size = FSI_SLAVE_SIZE_23b;
	slave->t_send_delay = 16;
	slave->t_echo_delay = 16;

	/* Get chip ID अगर any */
	slave->chip_id = -1;
	अगर (slave->dev.of_node) अणु
		uपूर्णांक32_t prop;
		अगर (!of_property_पढ़ो_u32(slave->dev.of_node, "chip-id", &prop))
			slave->chip_id = prop;

	पूर्ण

	slbus = cpu_to_be32(FSI_SLBUS_FORCE);
	rc = fsi_master_ग_लिखो(master, link, id, FSI_SLAVE_BASE + FSI_SLBUS,
			      &slbus, माप(slbus));
	अगर (rc)
		dev_warn(&master->dev,
			 "can't set slbus on slave:%02x:%02x %d\n", link, id,
			 rc);

	rc = fsi_slave_set_smode(slave);
	अगर (rc) अणु
		dev_warn(&master->dev,
				"can't set smode on slave:%02x:%02x %d\n",
				link, id, rc);
		जाओ err_मुक्त;
	पूर्ण

	/* Allocate a minor in the FSI space */
	rc = __fsi_get_new_minor(slave, fsi_dev_cfam, &slave->dev.devt,
				 &slave->cdev_idx);
	अगर (rc)
		जाओ err_मुक्त;

	/* Create अक्षरdev क्रम userspace access */
	cdev_init(&slave->cdev, &cfam_fops);
	rc = cdev_device_add(&slave->cdev, &slave->dev);
	अगर (rc) अणु
		dev_err(&slave->dev, "Error %d creating slave device\n", rc);
		जाओ err_मुक्त_ida;
	पूर्ण

	/* Now that we have the cdev रेजिस्टरed with the core, any fatal
	 * failures beyond this poपूर्णांक will need to clean up through
	 * cdev_device_del(). Fortunately though, nothing past here is fatal.
	 */

	अगर (master->link_config)
		master->link_config(master, link,
				    slave->t_send_delay,
				    slave->t_echo_delay);

	/* Legacy raw file -> to be हटाओd */
	rc = device_create_bin_file(&slave->dev, &fsi_slave_raw_attr);
	अगर (rc)
		dev_warn(&slave->dev, "failed to create raw attr: %d\n", rc);


	rc = fsi_slave_scan(slave);
	अगर (rc)
		dev_dbg(&master->dev, "failed during slave scan with: %d\n",
				rc);

	वापस 0;

err_मुक्त_ida:
	fsi_मुक्त_minor(slave->dev.devt);
err_मुक्त:
	of_node_put(slave->dev.of_node);
	kमुक्त(slave);
	वापस rc;
पूर्ण

/* FSI master support */
अटल पूर्णांक fsi_check_access(uपूर्णांक32_t addr, माप_प्रकार size)
अणु
	अगर (size == 4) अणु
		अगर (addr & 0x3)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (size == 2) अणु
		अगर (addr & 0x1)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (size != 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_पढ़ो(काष्ठा fsi_master *master, पूर्णांक link,
		uपूर्णांक8_t slave_id, uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size)
अणु
	पूर्णांक rc;

	trace_fsi_master_पढ़ो(master, link, slave_id, addr, size);

	rc = fsi_check_access(addr, size);
	अगर (!rc)
		rc = master->पढ़ो(master, link, slave_id, addr, val, size);

	trace_fsi_master_rw_result(master, link, slave_id, addr, size,
			false, val, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_ग_लिखो(काष्ठा fsi_master *master, पूर्णांक link,
		uपूर्णांक8_t slave_id, uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size)
अणु
	पूर्णांक rc;

	trace_fsi_master_ग_लिखो(master, link, slave_id, addr, size, val);

	rc = fsi_check_access(addr, size);
	अगर (!rc)
		rc = master->ग_लिखो(master, link, slave_id, addr, val, size);

	trace_fsi_master_rw_result(master, link, slave_id, addr, size,
			true, val, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_link_disable(काष्ठा fsi_master *master, पूर्णांक link)
अणु
	अगर (master->link_enable)
		वापस master->link_enable(master, link, false);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_link_enable(काष्ठा fsi_master *master, पूर्णांक link)
अणु
	अगर (master->link_enable)
		वापस master->link_enable(master, link, true);

	वापस 0;
पूर्ण

/*
 * Issue a अवरोध command on this link
 */
अटल पूर्णांक fsi_master_अवरोध(काष्ठा fsi_master *master, पूर्णांक link)
अणु
	पूर्णांक rc = 0;

	trace_fsi_master_अवरोध(master, link);

	अगर (master->send_अवरोध)
		rc = master->send_अवरोध(master, link);
	अगर (master->link_config)
		master->link_config(master, link, 16, 16);

	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_scan(काष्ठा fsi_master *master)
अणु
	पूर्णांक link, rc;

	क्रम (link = 0; link < master->n_links; link++) अणु
		rc = fsi_master_link_enable(master, link);
		अगर (rc) अणु
			dev_dbg(&master->dev,
				"enable link %d failed: %d\n", link, rc);
			जारी;
		पूर्ण
		rc = fsi_master_अवरोध(master, link);
		अगर (rc) अणु
			fsi_master_link_disable(master, link);
			dev_dbg(&master->dev,
				"break to link %d failed: %d\n", link, rc);
			जारी;
		पूर्ण

		rc = fsi_slave_init(master, link, 0);
		अगर (rc)
			fsi_master_link_disable(master, link);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_slave_हटाओ_device(काष्ठा device *dev, व्योम *arg)
अणु
	device_unरेजिस्टर(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_हटाओ_slave(काष्ठा device *dev, व्योम *arg)
अणु
	काष्ठा fsi_slave *slave = to_fsi_slave(dev);

	device_क्रम_each_child(dev, शून्य, fsi_slave_हटाओ_device);
	cdev_device_del(&slave->cdev, &slave->dev);
	put_device(dev);
	वापस 0;
पूर्ण

अटल व्योम fsi_master_unscan(काष्ठा fsi_master *master)
अणु
	device_क्रम_each_child(&master->dev, शून्य, fsi_master_हटाओ_slave);
पूर्ण

पूर्णांक fsi_master_rescan(काष्ठा fsi_master *master)
अणु
	पूर्णांक rc;

	mutex_lock(&master->scan_lock);
	fsi_master_unscan(master);
	rc = fsi_master_scan(master);
	mutex_unlock(&master->scan_lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_master_rescan);

अटल sमाप_प्रकार master_rescan_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_master *master = to_fsi_master(dev);
	पूर्णांक rc;

	rc = fsi_master_rescan(master);
	अगर (rc < 0)
		वापस rc;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(rescan, 0200, शून्य, master_rescan_store);

अटल sमाप_प्रकार master_अवरोध_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_master *master = to_fsi_master(dev);

	fsi_master_अवरोध(master, 0);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(अवरोध, 0200, शून्य, master_अवरोध_store);

अटल काष्ठा attribute *master_attrs[] = अणु
	&dev_attr_अवरोध.attr,
	&dev_attr_rescan.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(master);

अटल काष्ठा class fsi_master_class = अणु
	.name = "fsi-master",
	.dev_groups = master_groups,
पूर्ण;

पूर्णांक fsi_master_रेजिस्टर(काष्ठा fsi_master *master)
अणु
	पूर्णांक rc;
	काष्ठा device_node *np;

	mutex_init(&master->scan_lock);
	master->idx = ida_simple_get(&master_ida, 0, पूर्णांक_उच्च, GFP_KERNEL);
	dev_set_name(&master->dev, "fsi%d", master->idx);
	master->dev.class = &fsi_master_class;

	rc = device_रेजिस्टर(&master->dev);
	अगर (rc) अणु
		ida_simple_हटाओ(&master_ida, master->idx);
		वापस rc;
	पूर्ण

	np = dev_of_node(&master->dev);
	अगर (!of_property_पढ़ो_bool(np, "no-scan-on-init")) अणु
		mutex_lock(&master->scan_lock);
		fsi_master_scan(master);
		mutex_unlock(&master->scan_lock);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fsi_master_रेजिस्टर);

व्योम fsi_master_unरेजिस्टर(काष्ठा fsi_master *master)
अणु
	अगर (master->idx >= 0) अणु
		ida_simple_हटाओ(&master_ida, master->idx);
		master->idx = -1;
	पूर्ण

	mutex_lock(&master->scan_lock);
	fsi_master_unscan(master);
	mutex_unlock(&master->scan_lock);
	device_unरेजिस्टर(&master->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_master_unरेजिस्टर);

/* FSI core & Linux bus type definitions */

अटल पूर्णांक fsi_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा fsi_device *fsi_dev = to_fsi_dev(dev);
	काष्ठा fsi_driver *fsi_drv = to_fsi_drv(drv);
	स्थिर काष्ठा fsi_device_id *id;

	अगर (!fsi_drv->id_table)
		वापस 0;

	क्रम (id = fsi_drv->id_table; id->engine_type; id++) अणु
		अगर (id->engine_type != fsi_dev->engine_type)
			जारी;
		अगर (id->version == FSI_VERSION_ANY ||
				id->version == fsi_dev->version)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fsi_driver_रेजिस्टर(काष्ठा fsi_driver *fsi_drv)
अणु
	अगर (!fsi_drv)
		वापस -EINVAL;
	अगर (!fsi_drv->id_table)
		वापस -EINVAL;

	वापस driver_रेजिस्टर(&fsi_drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_driver_रेजिस्टर);

व्योम fsi_driver_unरेजिस्टर(काष्ठा fsi_driver *fsi_drv)
अणु
	driver_unरेजिस्टर(&fsi_drv->drv);
पूर्ण
EXPORT_SYMBOL_GPL(fsi_driver_unरेजिस्टर);

काष्ठा bus_type fsi_bus_type = अणु
	.name		= "fsi",
	.match		= fsi_bus_match,
पूर्ण;
EXPORT_SYMBOL_GPL(fsi_bus_type);

अटल पूर्णांक __init fsi_init(व्योम)
अणु
	पूर्णांक rc;

	rc = alloc_chrdev_region(&fsi_base_dev, 0, FSI_अक्षर_उच्च_DEVICES, "fsi");
	अगर (rc)
		वापस rc;
	rc = bus_रेजिस्टर(&fsi_bus_type);
	अगर (rc)
		जाओ fail_bus;

	rc = class_रेजिस्टर(&fsi_master_class);
	अगर (rc)
		जाओ fail_class;

	वापस 0;

 fail_class:
	bus_unरेजिस्टर(&fsi_bus_type);
 fail_bus:
	unरेजिस्टर_chrdev_region(fsi_base_dev, FSI_अक्षर_उच्च_DEVICES);
	वापस rc;
पूर्ण
postcore_initcall(fsi_init);

अटल व्योम fsi_निकास(व्योम)
अणु
	class_unरेजिस्टर(&fsi_master_class);
	bus_unरेजिस्टर(&fsi_bus_type);
	unरेजिस्टर_chrdev_region(fsi_base_dev, FSI_अक्षर_उच्च_DEVICES);
	ida_destroy(&fsi_minor_ida);
पूर्ण
module_निकास(fsi_निकास);
module_param(discard_errors, पूर्णांक, 0664);
MODULE_LICENSE("GPL");
MODULE_PARM_DESC(discard_errors, "Don't invoke error handling on bus accesses");
