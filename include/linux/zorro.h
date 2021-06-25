<शैली गुरु>
/*
 *  linux/zorro.h -- Amiga AutoConfig (Zorro) Bus Definitions
 *
 *  Copyright (C) 1995--2003 Geert Uytterhoeven
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive
 *  क्रम more details.
 */

#अगर_अघोषित _LINUX_ZORRO_H
#घोषणा _LINUX_ZORRO_H


#समावेश <uapi/linux/zorro.h>

#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <यंत्र/zorro.h>


    /*
     *  Zorro devices
     */

काष्ठा zorro_dev अणु
    काष्ठा ExpansionRom rom;
    zorro_id id;
    काष्ठा zorro_driver *driver;	/* which driver has allocated this device */
    काष्ठा device dev;			/* Generic device पूर्णांकerface */
    u16 slotaddr;
    u16 slotsize;
    अक्षर name[64];
    काष्ठा resource resource;
पूर्ण;

#घोषणा	to_zorro_dev(n)	container_of(n, काष्ठा zorro_dev, dev)


    /*
     *  Zorro device drivers
     */

काष्ठा zorro_driver अणु
    काष्ठा list_head node;
    अक्षर *name;
    स्थिर काष्ठा zorro_device_id *id_table;	/* शून्य अगर wants all devices */
    पूर्णांक (*probe)(काष्ठा zorro_dev *z, स्थिर काष्ठा zorro_device_id *id);	/* New device inserted */
    व्योम (*हटाओ)(काष्ठा zorro_dev *z);	/* Device हटाओd (शून्य अगर not a hot-plug capable driver) */
    काष्ठा device_driver driver;
पूर्ण;

#घोषणा	to_zorro_driver(drv)	container_of(drv, काष्ठा zorro_driver, driver)


#घोषणा zorro_क्रम_each_dev(dev)	\
	क्रम (dev = &zorro_स्वतःcon[0]; dev < zorro_स्वतःcon+zorro_num_स्वतःcon; dev++)


/* New-style probing */
बाह्य पूर्णांक zorro_रेजिस्टर_driver(काष्ठा zorro_driver *);
बाह्य व्योम zorro_unरेजिस्टर_driver(काष्ठा zorro_driver *);


बाह्य अचिन्हित पूर्णांक zorro_num_स्वतःcon;	/* # of स्वतःconfig devices found */
बाह्य काष्ठा zorro_dev *zorro_स्वतःcon;


    /*
     * Minimal inक्रमmation about a Zorro device, passed from bootinfo
     * Only available temporarily, i.e. until iniपंचांगem has been मुक्तd!
     */

काष्ठा zorro_dev_init अणु
	काष्ठा ExpansionRom rom;
	u16 slotaddr;
	u16 slotsize;
	u32 boardaddr;
	u32 boardsize;
पूर्ण;

बाह्य काष्ठा zorro_dev_init zorro_स्वतःcon_init[ZORRO_NUM_AUTO] __initdata;


    /*
     *  Zorro Functions
     */

बाह्य काष्ठा zorro_dev *zorro_find_device(zorro_id id,
					   काष्ठा zorro_dev *from);

#घोषणा zorro_resource_start(z)	((z)->resource.start)
#घोषणा zorro_resource_end(z)	((z)->resource.end)
#घोषणा zorro_resource_len(z)	(resource_size(&(z)->resource))
#घोषणा zorro_resource_flags(z)	((z)->resource.flags)

#घोषणा zorro_request_device(z, name) \
    request_mem_region(zorro_resource_start(z), zorro_resource_len(z), name)
#घोषणा zorro_release_device(z) \
    release_mem_region(zorro_resource_start(z), zorro_resource_len(z))

/* Similar to the helpers above, these manipulate per-zorro_dev
 * driver-specअगरic data.  They are really just a wrapper around
 * the generic device काष्ठाure functions of these calls.
 */
अटल अंतरभूत व्योम *zorro_get_drvdata (काष्ठा zorro_dev *z)
अणु
	वापस dev_get_drvdata(&z->dev);
पूर्ण

अटल अंतरभूत व्योम zorro_set_drvdata (काष्ठा zorro_dev *z, व्योम *data)
अणु
	dev_set_drvdata(&z->dev, data);
पूर्ण


    /*
     *  Biपंचांगask indicating portions of available Zorro II RAM that are unused
     *  by the प्रणाली. Every bit represents a 64K chunk, क्रम a maximum of 8MB
     *  (128 chunks, physical 0x00200000-0x009fffff).
     *
     *  If you want to use (= allocate) portions of this RAM, you should clear
     *  the corresponding bits.
     */

बाह्य DECLARE_BITMAP(zorro_unused_z2ram, 128);

#घोषणा Z2RAM_START		(0x00200000)
#घोषणा Z2RAM_END		(0x00a00000)
#घोषणा Z2RAM_SIZE		(0x00800000)
#घोषणा Z2RAM_CHUNKSIZE		(0x00010000)
#घोषणा Z2RAM_CHUNKMASK		(0x0000ffff)
#घोषणा Z2RAM_CHUNKSHIFT	(16)


#पूर्ण_अगर /* _LINUX_ZORRO_H */
