<शैली गुरु>
/*
 * include/linux/superhyway.h
 *
 * SuperHyway Bus definitions
 *
 * Copyright (C) 2004, 2005  Paul Mundt <lethal@linux-sh.org>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#अगर_अघोषित __LINUX_SUPERHYWAY_H
#घोषणा __LINUX_SUPERHYWAY_H

#समावेश <linux/device.h>

/*
 * SuperHyway IDs
 */
#घोषणा SUPERHYWAY_DEVICE_ID_SH5_DMAC	0x0183

काष्ठा superhyway_vcr_info अणु
	u8	perr_flags;	/* P-port Error flags */
	u8	merr_flags;	/* Module Error flags */
	u16	mod_vers;	/* Module Version */
	u16	mod_id;		/* Module ID */
	u8	bot_mb;		/* Bottom Memory block */
	u8	top_mb;		/* Top Memory block */
पूर्ण;

काष्ठा superhyway_ops अणु
	पूर्णांक (*पढ़ो_vcr)(अचिन्हित दीर्घ base, काष्ठा superhyway_vcr_info *vcr);
	पूर्णांक (*ग_लिखो_vcr)(अचिन्हित दीर्घ base, काष्ठा superhyway_vcr_info vcr);
पूर्ण;

काष्ठा superhyway_bus अणु
	काष्ठा superhyway_ops *ops;
पूर्ण;

बाह्य काष्ठा superhyway_bus superhyway_channels[];

काष्ठा superhyway_device_id अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ driver_data;
पूर्ण;

काष्ठा superhyway_device;
बाह्य काष्ठा bus_type superhyway_bus_type;

काष्ठा superhyway_driver अणु
	अक्षर *name;

	स्थिर काष्ठा superhyway_device_id *id_table;
	काष्ठा device_driver drv;

	पूर्णांक (*probe)(काष्ठा superhyway_device *dev, स्थिर काष्ठा superhyway_device_id *id);
	व्योम (*हटाओ)(काष्ठा superhyway_device *dev);
पूर्ण;

#घोषणा to_superhyway_driver(d)	container_of((d), काष्ठा superhyway_driver, drv)

काष्ठा superhyway_device अणु
	अक्षर name[32];

	काष्ठा device dev;

	काष्ठा superhyway_device_id id;
	काष्ठा superhyway_driver *drv;
	काष्ठा superhyway_bus *bus;

	पूर्णांक num_resources;
	काष्ठा resource *resource;
	काष्ठा superhyway_vcr_info vcr;
पूर्ण;

#घोषणा to_superhyway_device(d)	container_of((d), काष्ठा superhyway_device, dev)

#घोषणा superhyway_get_drvdata(d)	dev_get_drvdata(&(d)->dev)
#घोषणा superhyway_set_drvdata(d,p)	dev_set_drvdata(&(d)->dev, (p))

अटल अंतरभूत पूर्णांक
superhyway_पढ़ो_vcr(काष्ठा superhyway_device *dev, अचिन्हित दीर्घ base,
		    काष्ठा superhyway_vcr_info *vcr)
अणु
	वापस dev->bus->ops->पढ़ो_vcr(base, vcr);
पूर्ण

अटल अंतरभूत पूर्णांक
superhyway_ग_लिखो_vcr(काष्ठा superhyway_device *dev, अचिन्हित दीर्घ base,
		     काष्ठा superhyway_vcr_info vcr)
अणु
	वापस dev->bus->ops->ग_लिखो_vcr(base, vcr);
पूर्ण

बाह्य पूर्णांक superhyway_scan_bus(काष्ठा superhyway_bus *);

/* drivers/sh/superhyway/superhyway.c */
पूर्णांक superhyway_रेजिस्टर_driver(काष्ठा superhyway_driver *);
व्योम superhyway_unरेजिस्टर_driver(काष्ठा superhyway_driver *);
पूर्णांक superhyway_add_device(अचिन्हित दीर्घ base, काष्ठा superhyway_device *, काष्ठा superhyway_bus *);
पूर्णांक superhyway_add_devices(काष्ठा superhyway_bus *bus, काष्ठा superhyway_device **devices, पूर्णांक nr_devices);

/* drivers/sh/superhyway/superhyway-sysfs.c */
बाह्य स्थिर काष्ठा attribute_group *superhyway_dev_groups[];

#पूर्ण_अगर /* __LINUX_SUPERHYWAY_H */

