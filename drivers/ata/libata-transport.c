<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright 2008 ioogle, Inc.  All rights reserved.
 *
 * Libata transport class.
 *
 * The ATA transport class contains common code to deal with ATA HBAs,
 * an approximated representation of ATA topologies in the driver model,
 * and various sysfs attributes to expose these topologies and management
 * पूर्णांकerfaces to user-space.
 *
 * There are 3 objects defined in in this class:
 * - ata_port
 * - ata_link
 * - ata_device
 * Each port has a link object. Each link can have up to two devices क्रम PATA
 * and generally one क्रम SATA.
 * If there is SATA port multiplier [PMP], 15 additional ata_link object are
 * created.
 *
 * These objects are created when the ata host is initialized and when a PMP is
 * found. They are हटाओd only when the HBA is हटाओd, cleaned beक्रमe the
 * error handler runs.
 */


#समावेश <linux/kernel.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <linux/libata.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/pm_runसमय.स>

#समावेश "libata.h"
#समावेश "libata-transport.h"

#घोषणा ATA_PORT_ATTRS		3
#घोषणा ATA_LINK_ATTRS		3
#घोषणा ATA_DEV_ATTRS		9

काष्ठा scsi_transport_ढाँचा;
काष्ठा scsi_transport_ढाँचा *ata_scsi_transport_ढाँचा;

काष्ठा ata_पूर्णांकernal अणु
	काष्ठा scsi_transport_ढाँचा t;

	काष्ठा device_attribute निजी_port_attrs[ATA_PORT_ATTRS];
	काष्ठा device_attribute निजी_link_attrs[ATA_LINK_ATTRS];
	काष्ठा device_attribute निजी_dev_attrs[ATA_DEV_ATTRS];

	काष्ठा transport_container link_attr_cont;
	काष्ठा transport_container dev_attr_cont;

	/*
	 * The array of null terminated poपूर्णांकers to attributes
	 * needed by scsi_sysfs.c
	 */
	काष्ठा device_attribute *link_attrs[ATA_LINK_ATTRS + 1];
	काष्ठा device_attribute *port_attrs[ATA_PORT_ATTRS + 1];
	काष्ठा device_attribute *dev_attrs[ATA_DEV_ATTRS + 1];
पूर्ण;
#घोषणा to_ata_पूर्णांकernal(पंचांगpl)	container_of(पंचांगpl, काष्ठा ata_पूर्णांकernal, t)


#घोषणा tdev_to_device(d)					\
	container_of((d), काष्ठा ata_device, tdev)
#घोषणा transport_class_to_dev(dev)				\
	tdev_to_device((dev)->parent)

#घोषणा tdev_to_link(d)						\
	container_of((d), काष्ठा ata_link, tdev)
#घोषणा transport_class_to_link(dev)				\
	tdev_to_link((dev)->parent)

#घोषणा tdev_to_port(d)						\
	container_of((d), काष्ठा ata_port, tdev)
#घोषणा transport_class_to_port(dev)				\
	tdev_to_port((dev)->parent)


/* Device objects are always created whit link objects */
अटल पूर्णांक ata_tdev_add(काष्ठा ata_device *dev);
अटल व्योम ata_tdev_delete(काष्ठा ata_device *dev);


/*
 * Hack to allow attributes of the same name in dअगरferent objects.
 */
#घोषणा ATA_DEVICE_ATTR(_prefix,_name,_mode,_show,_store) \
	काष्ठा device_attribute device_attr_##_prefix##_##_name = \
	__ATTR(_name,_mode,_show,_store)

#घोषणा ata_bitfield_name_match(title, table)			\
अटल sमाप_प्रकार							\
get_ata_##title##_names(u32 table_key, अक्षर *buf)		\
अणु								\
	अक्षर *prefix = "";					\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		अगर (table[i].value & table_key) अणु		\
			len += प्र_लिखो(buf + len, "%s%s",	\
				prefix, table[i].name);		\
			prefix = ", ";				\
		पूर्ण						\
	पूर्ण							\
	len += प्र_लिखो(buf + len, "\n");			\
	वापस len;						\
पूर्ण

#घोषणा ata_bitfield_name_search(title, table)			\
अटल sमाप_प्रकार							\
get_ata_##title##_names(u32 table_key, अक्षर *buf)		\
अणु								\
	sमाप_प्रकार len = 0;					\
	पूर्णांक i;							\
								\
	क्रम (i = 0; i < ARRAY_SIZE(table); i++) अणु		\
		अगर (table[i].value == table_key) अणु		\
			len += प्र_लिखो(buf + len, "%s",		\
				table[i].name);			\
			अवरोध;					\
		पूर्ण						\
	पूर्ण							\
	len += प्र_लिखो(buf + len, "\n");			\
	वापस len;						\
पूर्ण

अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण ata_class_names[] = अणु
	अणु ATA_DEV_UNKNOWN,		"unknown" पूर्ण,
	अणु ATA_DEV_ATA,			"ata" पूर्ण,
	अणु ATA_DEV_ATA_UNSUP,		"ata" पूर्ण,
	अणु ATA_DEV_ATAPI,		"atapi" पूर्ण,
	अणु ATA_DEV_ATAPI_UNSUP,		"atapi" पूर्ण,
	अणु ATA_DEV_PMP,			"pmp" पूर्ण,
	अणु ATA_DEV_PMP_UNSUP,		"pmp" पूर्ण,
	अणु ATA_DEV_SEMB,			"semb" पूर्ण,
	अणु ATA_DEV_SEMB_UNSUP,		"semb" पूर्ण,
	अणु ATA_DEV_ZAC,			"zac" पूर्ण,
	अणु ATA_DEV_NONE,			"none" पूर्ण
पूर्ण;
ata_bitfield_name_search(class, ata_class_names)


अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण ata_err_names[] = अणु
	अणु AC_ERR_DEV,			"DeviceError" पूर्ण,
	अणु AC_ERR_HSM,			"HostStateMachineError" पूर्ण,
	अणु AC_ERR_TIMEOUT,		"Timeout" पूर्ण,
	अणु AC_ERR_MEDIA,			"MediaError" पूर्ण,
	अणु AC_ERR_ATA_BUS,		"BusError" पूर्ण,
	अणु AC_ERR_HOST_BUS,		"HostBusError" पूर्ण,
	अणु AC_ERR_SYSTEM,		"SystemError" पूर्ण,
	अणु AC_ERR_INVALID,		"InvalidArg" पूर्ण,
	अणु AC_ERR_OTHER,			"Unknown" पूर्ण,
	अणु AC_ERR_NODEV_HINT,		"NoDeviceHint" पूर्ण,
	अणु AC_ERR_NCQ,		 	"NCQError" पूर्ण
पूर्ण;
ata_bitfield_name_match(err, ata_err_names)

अटल काष्ठा अणु
	u32		value;
	अक्षर		*name;
पूर्ण ata_xfer_names[] = अणु
	अणु XFER_UDMA_7,			"XFER_UDMA_7" पूर्ण,
	अणु XFER_UDMA_6,			"XFER_UDMA_6" पूर्ण,
	अणु XFER_UDMA_5,			"XFER_UDMA_5" पूर्ण,
	अणु XFER_UDMA_4,			"XFER_UDMA_4" पूर्ण,
	अणु XFER_UDMA_3,			"XFER_UDMA_3" पूर्ण,
	अणु XFER_UDMA_2,			"XFER_UDMA_2" पूर्ण,
	अणु XFER_UDMA_1,			"XFER_UDMA_1" पूर्ण,
	अणु XFER_UDMA_0,			"XFER_UDMA_0" पूर्ण,
	अणु XFER_MW_DMA_4,		"XFER_MW_DMA_4" पूर्ण,
	अणु XFER_MW_DMA_3,		"XFER_MW_DMA_3" पूर्ण,
	अणु XFER_MW_DMA_2,		"XFER_MW_DMA_2" पूर्ण,
	अणु XFER_MW_DMA_1,		"XFER_MW_DMA_1" पूर्ण,
	अणु XFER_MW_DMA_0,		"XFER_MW_DMA_0" पूर्ण,
	अणु XFER_SW_DMA_2,		"XFER_SW_DMA_2" पूर्ण,
	अणु XFER_SW_DMA_1,		"XFER_SW_DMA_1" पूर्ण,
	अणु XFER_SW_DMA_0,		"XFER_SW_DMA_0" पूर्ण,
	अणु XFER_PIO_6,			"XFER_PIO_6" पूर्ण,
	अणु XFER_PIO_5,			"XFER_PIO_5" पूर्ण,
	अणु XFER_PIO_4,			"XFER_PIO_4" पूर्ण,
	अणु XFER_PIO_3,			"XFER_PIO_3" पूर्ण,
	अणु XFER_PIO_2,			"XFER_PIO_2" पूर्ण,
	अणु XFER_PIO_1,			"XFER_PIO_1" पूर्ण,
	अणु XFER_PIO_0,			"XFER_PIO_0" पूर्ण,
	अणु XFER_PIO_SLOW,		"XFER_PIO_SLOW" पूर्ण
पूर्ण;
ata_bitfield_name_match(xfer,ata_xfer_names)

/*
 * ATA Port attributes
 */
#घोषणा ata_port_show_simple(field, name, क्रमmat_string, cast)		\
अटल sमाप_प्रकार								\
show_ata_port_##name(काष्ठा device *dev,				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा ata_port *ap = transport_class_to_port(dev);		\
									\
	वापस scnम_लिखो(buf, 20, क्रमmat_string, cast ap->field);	\
पूर्ण

#घोषणा ata_port_simple_attr(field, name, क्रमmat_string, type)		\
	ata_port_show_simple(field, name, क्रमmat_string, (type))	\
अटल DEVICE_ATTR(name, S_IRUGO, show_ata_port_##name, शून्य)

ata_port_simple_attr(nr_pmp_links, nr_pmp_links, "%d\n", पूर्णांक);
ata_port_simple_attr(stats.idle_irq, idle_irq, "%ld\n", अचिन्हित दीर्घ);
ata_port_simple_attr(local_port_no, port_no, "%u\n", अचिन्हित पूर्णांक);

अटल DECLARE_TRANSPORT_CLASS(ata_port_class,
			       "ata_port", शून्य, शून्य, शून्य);

अटल व्योम ata_tport_release(काष्ठा device *dev)
अणु
	काष्ठा ata_port *ap = tdev_to_port(dev);
	ata_host_put(ap->host);
पूर्ण

/**
 * ata_is_port --  check अगर a काष्ठा device represents a ATA port
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a ATA Port, %0 अन्यथा
 */
अटल पूर्णांक ata_is_port(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == ata_tport_release;
पूर्ण

अटल पूर्णांक ata_tport_match(काष्ठा attribute_container *cont,
			   काष्ठा device *dev)
अणु
	अगर (!ata_is_port(dev))
		वापस 0;
	वापस &ata_scsi_transport_ढाँचा->host_attrs.ac == cont;
पूर्ण

/**
 * ata_tport_delete  --  हटाओ ATA PORT
 * @ap:	ATA PORT to हटाओ
 *
 * Removes the specअगरied ATA PORT.  Remove the associated link as well.
 */
व्योम ata_tport_delete(काष्ठा ata_port *ap)
अणु
	काष्ठा device *dev = &ap->tdev;

	ata_tlink_delete(&ap->link);

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(dev);
पूर्ण

/** ata_tport_add - initialize a transport ATA port काष्ठाure
 *
 * @parent:	parent device
 * @ap:		existing ata_port काष्ठाure
 *
 * Initialize a ATA port काष्ठाure क्रम sysfs.  It will be added to the device
 * tree below the device specअगरied by @parent which could be a PCI device.
 *
 * Returns %0 on success
 */
पूर्णांक ata_tport_add(काष्ठा device *parent,
		  काष्ठा ata_port *ap)
अणु
	पूर्णांक error;
	काष्ठा device *dev = &ap->tdev;

	device_initialize(dev);
	dev->type = &ata_port_type;

	dev->parent = parent;
	ata_host_get(ap->host);
	dev->release = ata_tport_release;
	dev_set_name(dev, "ata%d", ap->prपूर्णांक_id);
	transport_setup_device(dev);
	ata_acpi_bind_port(ap);
	error = device_add(dev);
	अगर (error) अणु
		जाओ tport_err;
	पूर्ण

	device_enable_async_suspend(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_क्रमbid(dev);

	transport_add_device(dev);
	transport_configure_device(dev);

	error = ata_tlink_add(&ap->link);
	अगर (error) अणु
		जाओ tport_link_err;
	पूर्ण
	वापस 0;

 tport_link_err:
	transport_हटाओ_device(dev);
	device_del(dev);

 tport_err:
	transport_destroy_device(dev);
	put_device(dev);
	ata_host_put(ap->host);
	वापस error;
पूर्ण


/*
 * ATA link attributes
 */
अटल पूर्णांक noop(पूर्णांक x) अणु वापस x; पूर्ण

#घोषणा ata_link_show_linkspeed(field, क्रमmat)			        \
अटल sमाप_प्रकार								\
show_ata_link_##field(काष्ठा device *dev,				\
		      काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा ata_link *link = transport_class_to_link(dev);		\
									\
	वापस प्र_लिखो(buf, "%s\n", sata_spd_string(क्रमmat(link->field))); \
पूर्ण

#घोषणा ata_link_linkspeed_attr(field, क्रमmat)				\
	ata_link_show_linkspeed(field, क्रमmat)				\
अटल DEVICE_ATTR(field, S_IRUGO, show_ata_link_##field, शून्य)

ata_link_linkspeed_attr(hw_sata_spd_limit, fls);
ata_link_linkspeed_attr(sata_spd_limit, fls);
ata_link_linkspeed_attr(sata_spd, noop);


अटल DECLARE_TRANSPORT_CLASS(ata_link_class,
		"ata_link", शून्य, शून्य, शून्य);

अटल व्योम ata_tlink_release(काष्ठा device *dev)
अणु
पूर्ण

/**
 * ata_is_link --  check अगर a काष्ठा device represents a ATA link
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a ATA link, %0 अन्यथा
 */
अटल पूर्णांक ata_is_link(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == ata_tlink_release;
पूर्ण

अटल पूर्णांक ata_tlink_match(काष्ठा attribute_container *cont,
			   काष्ठा device *dev)
अणु
	काष्ठा ata_पूर्णांकernal* i = to_ata_पूर्णांकernal(ata_scsi_transport_ढाँचा);
	अगर (!ata_is_link(dev))
		वापस 0;
	वापस &i->link_attr_cont.ac == cont;
पूर्ण

/**
 * ata_tlink_delete  --  हटाओ ATA LINK
 * @link:	ATA LINK to हटाओ
 *
 * Removes the specअगरied ATA LINK.  हटाओ associated ATA device(s) as well.
 */
व्योम ata_tlink_delete(काष्ठा ata_link *link)
अणु
	काष्ठा device *dev = &link->tdev;
	काष्ठा ata_device *ata_dev;

	ata_क्रम_each_dev(ata_dev, link, ALL) अणु
		ata_tdev_delete(ata_dev);
	पूर्ण

	transport_हटाओ_device(dev);
	device_del(dev);
	transport_destroy_device(dev);
	put_device(dev);
पूर्ण

/**
 * ata_tlink_add  --  initialize a transport ATA link काष्ठाure
 * @link:	allocated ata_link काष्ठाure.
 *
 * Initialize an ATA LINK काष्ठाure क्रम sysfs.  It will be added in the
 * device tree below the ATA PORT it beदीर्घs to.
 *
 * Returns %0 on success
 */
पूर्णांक ata_tlink_add(काष्ठा ata_link *link)
अणु
	काष्ठा device *dev = &link->tdev;
	काष्ठा ata_port *ap = link->ap;
	काष्ठा ata_device *ata_dev;
	पूर्णांक error;

	device_initialize(dev);
	dev->parent = &ap->tdev;
	dev->release = ata_tlink_release;
	अगर (ata_is_host_link(link))
		dev_set_name(dev, "link%d", ap->prपूर्णांक_id);
        अन्यथा
		dev_set_name(dev, "link%d.%d", ap->prपूर्णांक_id, link->pmp);

	transport_setup_device(dev);

	error = device_add(dev);
	अगर (error) अणु
		जाओ tlink_err;
	पूर्ण

	transport_add_device(dev);
	transport_configure_device(dev);

	ata_क्रम_each_dev(ata_dev, link, ALL) अणु
		error = ata_tdev_add(ata_dev);
		अगर (error) अणु
			जाओ tlink_dev_err;
		पूर्ण
	पूर्ण
	वापस 0;
  tlink_dev_err:
	जबतक (--ata_dev >= link->device) अणु
		ata_tdev_delete(ata_dev);
	पूर्ण
	transport_हटाओ_device(dev);
	device_del(dev);
  tlink_err:
	transport_destroy_device(dev);
	put_device(dev);
	वापस error;
पूर्ण

/*
 * ATA device attributes
 */

#घोषणा ata_dev_show_class(title, field)				\
अटल sमाप_प्रकार								\
show_ata_dev_##field(काष्ठा device *dev,				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);	\
									\
	वापस get_ata_##title##_names(ata_dev->field, buf);		\
पूर्ण

#घोषणा ata_dev_attr(title, field)					\
	ata_dev_show_class(title, field)				\
अटल DEVICE_ATTR(field, S_IRUGO, show_ata_dev_##field, शून्य)

ata_dev_attr(class, class);
ata_dev_attr(xfer, pio_mode);
ata_dev_attr(xfer, dma_mode);
ata_dev_attr(xfer, xfer_mode);


#घोषणा ata_dev_show_simple(field, क्रमmat_string, cast)		\
अटल sमाप_प्रकार								\
show_ata_dev_##field(काष्ठा device *dev,				\
		     काष्ठा device_attribute *attr, अक्षर *buf)		\
अणु									\
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);	\
									\
	वापस scnम_लिखो(buf, 20, क्रमmat_string, cast ata_dev->field);	\
पूर्ण

#घोषणा ata_dev_simple_attr(field, क्रमmat_string, type)	\
	ata_dev_show_simple(field, क्रमmat_string, (type))	\
अटल DEVICE_ATTR(field, S_IRUGO, 			\
		   show_ata_dev_##field, शून्य)

ata_dev_simple_attr(spdn_cnt, "%d\n", पूर्णांक);

काष्ठा ata_show_ering_arg अणु
	अक्षर* buf;
	पूर्णांक written;
पूर्ण;

अटल पूर्णांक ata_show_ering(काष्ठा ata_ering_entry *ent, व्योम *व्योम_arg)
अणु
	काष्ठा ata_show_ering_arg* arg = व्योम_arg;
	u64 seconds;
	u32 rem;

	seconds = भाग_u64_rem(ent->बारtamp, HZ, &rem);
	arg->written += प्र_लिखो(arg->buf + arg->written,
			        "[%5llu.%09lu]", seconds,
				rem * NSEC_PER_SEC / HZ);
	arg->written += get_ata_err_names(ent->err_mask,
					  arg->buf + arg->written);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
show_ata_dev_ering(काष्ठा device *dev,
		   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);
	काष्ठा ata_show_ering_arg arg = अणु buf, 0 पूर्ण;

	ata_ering_map(&ata_dev->ering, ata_show_ering, &arg);
	वापस arg.written;
पूर्ण


अटल DEVICE_ATTR(ering, S_IRUGO, show_ata_dev_ering, शून्य);

अटल sमाप_प्रकार
show_ata_dev_id(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);
	पूर्णांक written = 0, i = 0;

	अगर (ata_dev->class == ATA_DEV_PMP)
		वापस 0;
	क्रम(i=0;i<ATA_ID_WORDS;i++)  अणु
		written += scnम_लिखो(buf+written, 20, "%04x%c",
				    ata_dev->id[i],
				    ((i+1) & 7) ? ' ' : '\n');
	पूर्ण
	वापस written;
पूर्ण

अटल DEVICE_ATTR(id, S_IRUGO, show_ata_dev_id, शून्य);

अटल sमाप_प्रकार
show_ata_dev_gscr(काष्ठा device *dev,
		  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);
	पूर्णांक written = 0, i = 0;

	अगर (ata_dev->class != ATA_DEV_PMP)
		वापस 0;
	क्रम(i=0;i<SATA_PMP_GSCR_DWORDS;i++)  अणु
		written += scnम_लिखो(buf+written, 20, "%08x%c",
				    ata_dev->gscr[i],
				    ((i+1) & 3) ? ' ' : '\n');
	पूर्ण
	अगर (SATA_PMP_GSCR_DWORDS & 3)
		buf[written-1] = '\n';
	वापस written;
पूर्ण

अटल DEVICE_ATTR(gscr, S_IRUGO, show_ata_dev_gscr, शून्य);

अटल sमाप_प्रकार
show_ata_dev_trim(काष्ठा device *dev,
		  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ata_device *ata_dev = transport_class_to_dev(dev);
	अचिन्हित अक्षर *mode;

	अगर (!ata_id_has_trim(ata_dev->id))
		mode = "unsupported";
	अन्यथा अगर (ata_dev->horkage & ATA_HORKAGE_NOTRIM)
		mode = "forced_unsupported";
	अन्यथा अगर (ata_dev->horkage & ATA_HORKAGE_NO_NCQ_TRIM)
			mode = "forced_unqueued";
	अन्यथा अगर (ata_fpdma_dsm_supported(ata_dev))
		mode = "queued";
	अन्यथा
		mode = "unqueued";

	वापस scnम_लिखो(buf, 20, "%s\n", mode);
पूर्ण

अटल DEVICE_ATTR(trim, S_IRUGO, show_ata_dev_trim, शून्य);

अटल DECLARE_TRANSPORT_CLASS(ata_dev_class,
			       "ata_device", शून्य, शून्य, शून्य);

अटल व्योम ata_tdev_release(काष्ठा device *dev)
अणु
पूर्ण

/**
 * ata_is_ata_dev  --  check अगर a काष्ठा device represents a ATA device
 * @dev:	device to check
 *
 * Returns:
 *	%1 अगर the device represents a ATA device, %0 अन्यथा
 */
अटल पूर्णांक ata_is_ata_dev(स्थिर काष्ठा device *dev)
अणु
	वापस dev->release == ata_tdev_release;
पूर्ण

अटल पूर्णांक ata_tdev_match(काष्ठा attribute_container *cont,
			  काष्ठा device *dev)
अणु
	काष्ठा ata_पूर्णांकernal* i = to_ata_पूर्णांकernal(ata_scsi_transport_ढाँचा);
	अगर (!ata_is_ata_dev(dev))
		वापस 0;
	वापस &i->dev_attr_cont.ac == cont;
पूर्ण

/**
 * ata_tdev_मुक्त  --  मुक्त a ATA LINK
 * @dev:	ATA PHY to मुक्त
 *
 * Frees the specअगरied ATA PHY.
 *
 * Note:
 *   This function must only be called on a PHY that has not
 *   successfully been added using ata_tdev_add().
 */
अटल व्योम ata_tdev_मुक्त(काष्ठा ata_device *dev)
अणु
	transport_destroy_device(&dev->tdev);
	put_device(&dev->tdev);
पूर्ण

/**
 * ata_tdev_delete  --  हटाओ ATA device
 * @ata_dev:	ATA device to हटाओ
 *
 * Removes the specअगरied ATA device.
 */
अटल व्योम ata_tdev_delete(काष्ठा ata_device *ata_dev)
अणु
	काष्ठा device *dev = &ata_dev->tdev;

	transport_हटाओ_device(dev);
	device_del(dev);
	ata_tdev_मुक्त(ata_dev);
पूर्ण


/**
 * ata_tdev_add  --  initialize a transport ATA device काष्ठाure.
 * @ata_dev:	ata_dev काष्ठाure.
 *
 * Initialize an ATA device काष्ठाure क्रम sysfs.  It will be added in the
 * device tree below the ATA LINK device it beदीर्घs to.
 *
 * Returns %0 on success
 */
अटल पूर्णांक ata_tdev_add(काष्ठा ata_device *ata_dev)
अणु
	काष्ठा device *dev = &ata_dev->tdev;
	काष्ठा ata_link *link = ata_dev->link;
	काष्ठा ata_port *ap = link->ap;
	पूर्णांक error;

	device_initialize(dev);
	dev->parent = &link->tdev;
	dev->release = ata_tdev_release;
	अगर (ata_is_host_link(link))
		dev_set_name(dev, "dev%d.%d", ap->prपूर्णांक_id,ata_dev->devno);
        अन्यथा
		dev_set_name(dev, "dev%d.%d.0", ap->prपूर्णांक_id, link->pmp);

	transport_setup_device(dev);
	ata_acpi_bind_dev(ata_dev);
	error = device_add(dev);
	अगर (error) अणु
		ata_tdev_मुक्त(ata_dev);
		वापस error;
	पूर्ण

	transport_add_device(dev);
	transport_configure_device(dev);
	वापस 0;
पूर्ण


/*
 * Setup / Tearकरोwn code
 */

#घोषणा SETUP_TEMPLATE(attrb, field, perm, test)			\
	i->निजी_##attrb[count] = dev_attr_##field;		       	\
	i->निजी_##attrb[count].attr.mode = perm;			\
	i->attrb[count] = &i->निजी_##attrb[count];			\
	अगर (test)							\
		count++

#घोषणा SETUP_LINK_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(link_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_PORT_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(port_attrs, field, S_IRUGO, 1)

#घोषणा SETUP_DEV_ATTRIBUTE(field)					\
	SETUP_TEMPLATE(dev_attrs, field, S_IRUGO, 1)

/**
 * ata_attach_transport  --  instantiate ATA transport ढाँचा
 */
काष्ठा scsi_transport_ढाँचा *ata_attach_transport(व्योम)
अणु
	काष्ठा ata_पूर्णांकernal *i;
	पूर्णांक count;

	i = kzalloc(माप(काष्ठा ata_पूर्णांकernal), GFP_KERNEL);
	अगर (!i)
		वापस शून्य;

	i->t.eh_strategy_handler	= ata_scsi_error;
	i->t.user_scan			= ata_scsi_user_scan;

	i->t.host_attrs.ac.attrs = &i->port_attrs[0];
	i->t.host_attrs.ac.class = &ata_port_class.class;
	i->t.host_attrs.ac.match = ata_tport_match;
	transport_container_रेजिस्टर(&i->t.host_attrs);

	i->link_attr_cont.ac.class = &ata_link_class.class;
	i->link_attr_cont.ac.attrs = &i->link_attrs[0];
	i->link_attr_cont.ac.match = ata_tlink_match;
	transport_container_रेजिस्टर(&i->link_attr_cont);

	i->dev_attr_cont.ac.class = &ata_dev_class.class;
	i->dev_attr_cont.ac.attrs = &i->dev_attrs[0];
	i->dev_attr_cont.ac.match = ata_tdev_match;
	transport_container_रेजिस्टर(&i->dev_attr_cont);

	count = 0;
	SETUP_PORT_ATTRIBUTE(nr_pmp_links);
	SETUP_PORT_ATTRIBUTE(idle_irq);
	SETUP_PORT_ATTRIBUTE(port_no);
	BUG_ON(count > ATA_PORT_ATTRS);
	i->port_attrs[count] = शून्य;

	count = 0;
	SETUP_LINK_ATTRIBUTE(hw_sata_spd_limit);
	SETUP_LINK_ATTRIBUTE(sata_spd_limit);
	SETUP_LINK_ATTRIBUTE(sata_spd);
	BUG_ON(count > ATA_LINK_ATTRS);
	i->link_attrs[count] = शून्य;

	count = 0;
	SETUP_DEV_ATTRIBUTE(class);
	SETUP_DEV_ATTRIBUTE(pio_mode);
	SETUP_DEV_ATTRIBUTE(dma_mode);
	SETUP_DEV_ATTRIBUTE(xfer_mode);
	SETUP_DEV_ATTRIBUTE(spdn_cnt);
	SETUP_DEV_ATTRIBUTE(ering);
	SETUP_DEV_ATTRIBUTE(id);
	SETUP_DEV_ATTRIBUTE(gscr);
	SETUP_DEV_ATTRIBUTE(trim);
	BUG_ON(count > ATA_DEV_ATTRS);
	i->dev_attrs[count] = शून्य;

	वापस &i->t;
पूर्ण

/**
 * ata_release_transport  --  release ATA transport ढाँचा instance
 * @t:		transport ढाँचा instance
 */
व्योम ata_release_transport(काष्ठा scsi_transport_ढाँचा *t)
अणु
	काष्ठा ata_पूर्णांकernal *i = to_ata_पूर्णांकernal(t);

	transport_container_unरेजिस्टर(&i->t.host_attrs);
	transport_container_unरेजिस्टर(&i->link_attr_cont);
	transport_container_unरेजिस्टर(&i->dev_attr_cont);

	kमुक्त(i);
पूर्ण

__init पूर्णांक libata_transport_init(व्योम)
अणु
	पूर्णांक error;

	error = transport_class_रेजिस्टर(&ata_link_class);
	अगर (error)
		जाओ out_unरेजिस्टर_transport;
	error = transport_class_रेजिस्टर(&ata_port_class);
	अगर (error)
		जाओ out_unरेजिस्टर_link;
	error = transport_class_रेजिस्टर(&ata_dev_class);
	अगर (error)
		जाओ out_unरेजिस्टर_port;
	वापस 0;

 out_unरेजिस्टर_port:
	transport_class_unरेजिस्टर(&ata_port_class);
 out_unरेजिस्टर_link:
	transport_class_unरेजिस्टर(&ata_link_class);
 out_unरेजिस्टर_transport:
	वापस error;

पूर्ण

व्योम __निकास libata_transport_निकास(व्योम)
अणु
	transport_class_unरेजिस्टर(&ata_link_class);
	transport_class_unरेजिस्टर(&ata_port_class);
	transport_class_unरेजिस्टर(&ata_dev_class);
पूर्ण
