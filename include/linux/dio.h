<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* header file क्रम DIO boards क्रम the HP300 architecture.
 * Maybe this should handle DIO-II later?
 * The general काष्ठाure of this is vaguely based on how
 * the Amiga port handles Zorro boards.
 * Copyright (C) Peter Maydell 05/1998 <pmaydell@chiark.greenend.org.uk>
 * Converted to driver model Jochen Friedrich <jochen@scram.de>
 *
 * The board IDs are from the NetBSD kernel, which क्रम once provided
 * helpful comments...
 *
 * This goes with drivers/dio/dio.c
 */

#अगर_अघोषित _LINUX_DIO_H
#घोषणा _LINUX_DIO_H

/* The DIO boards in a प्रणाली are distinguished by 'select codes' which 
 * range from 0-63 (DIO) and 132-255 (DIO-II). 
 * The DIO board with select code sc is located at physical address 
 *     0x600000 + sc * 0x10000
 * So DIO cards cover [0x600000-0x800000); the areas [0x200000-0x400000) and
 * [0x800000-0x1000000) are क्रम additional space required by things
 * like framebuffers. [0x400000-0x600000) is क्रम miscellaneous पूर्णांकernal I/O.
 * On Linux, this is currently all mapped पूर्णांकo the भव address space
 * at 0xf0000000 on bootup.
 * DIO-II boards are at 0x1000000 + (sc - 132) * 0x400000
 * which is address range [0x1000000-0x20000000) -- too big to map completely,
 * so currently we just करोn't handle DIO-II boards.  It wouldn't be hard to 
 * करो with ioremap() though.
 */

#समावेश <linux/device.h>

#अगर_घोषित __KERNEL__

#समावेश <यंत्र/hp300hw.h>

प्रकार __u16 dio_id;

    /*
     *  DIO devices
     */

काष्ठा dio_dev अणु
	काष्ठा dio_bus *bus;
	dio_id id;
	पूर्णांक scode;
	काष्ठा dio_driver *driver;	/* which driver has allocated this device */
	काष्ठा device dev;		/* Generic device पूर्णांकerface */
	u8 ipl;
	अक्षर name[64];
	काष्ठा resource resource;
पूर्ण;

#घोषणा to_dio_dev(n) container_of(n, काष्ठा dio_dev, dev)

    /*
     *  DIO bus
     */

काष्ठा dio_bus अणु
	काष्ठा list_head devices;           /* list of devices on this bus */
	अचिन्हित पूर्णांक num_resources;         /* number of resources */
	काष्ठा resource resources[2];       /* address space routed to this bus */
	काष्ठा device dev;
	अक्षर name[10];
पूर्ण;

बाह्य काष्ठा dio_bus dio_bus;      /* Single DIO bus */
बाह्य काष्ठा bus_type dio_bus_type;

    /*
     *  DIO device IDs
     */

काष्ठा dio_device_id अणु
	dio_id id;                    /* Device ID or DIO_WILDCARD */
	अचिन्हित दीर्घ driver_data;    /* Data निजी to the driver */
पूर्ण;

    /*
     *  DIO device drivers
     */

काष्ठा dio_driver अणु
	काष्ठा list_head node;
	अक्षर *name;
	स्थिर काष्ठा dio_device_id *id_table;     /* शून्य अगर wants all devices */
	पूर्णांक (*probe)(काष्ठा dio_dev *z, स्थिर काष्ठा dio_device_id *id);
/* New device inserted */
	व्योम (*हटाओ)(काष्ठा dio_dev *z);        /* Device हटाओd (शून्य अगर not a hot-plug capable driver) */
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा to_dio_driver(drv)    container_of(drv, काष्ठा dio_driver, driver)

/* DIO/DIO-II boards all have the following 8bit रेजिस्टरs.
 * These are offsets from the base of the device.
 */
#घोषणा DIO_IDOFF     0x01             /* primary device ID */
#घोषणा DIO_IPLOFF    0x03             /* पूर्णांकerrupt priority level */
#घोषणा DIO_SECIDOFF  0x15             /* secondary device ID */
#घोषणा DIOII_SIZखातापूर्णF 0x101            /* device size, DIO-II only */
#घोषणा DIO_VIRADDRBASE 0xf0000000UL   /* vir addr where IOspace is mapped */

#घोषणा DIO_BASE                0x600000        /* start of DIO space */
#घोषणा DIO_END                 0x1000000       /* end of DIO space */
#घोषणा DIO_DEVSIZE             0x10000         /* size of a DIO device */

#घोषणा DIOII_BASE              0x01000000      /* start of DIO-II space */
#घोषणा DIOII_END               0x20000000      /* end of DIO-II space */
#घोषणा DIOII_DEVSIZE           0x00400000      /* size of a DIO-II device */

/* Highest valid select code. If we add DIO-II support this should become
 * 256 क्रम everything except HP320, which only has DIO.
 */
#घोषणा DIO_SCMAX (hp300_model == HP_320 ? 32 : 256)
#घोषणा DIOII_SCBASE 132 /* lowest DIO-II select code */
#घोषणा DIO_SCINHOLE(scode) (((scode) >= 32) && ((scode) < DIOII_SCBASE))
#घोषणा DIO_ISDIOII(scode) ((scode) >= 132 && (scode) < 256)

/* macros to पढ़ो device IDs, given base address */
#घोषणा DIO_ID(baseaddr) in_8((baseaddr) + DIO_IDOFF)
#घोषणा DIO_SECID(baseaddr) in_8((baseaddr) + DIO_SECIDOFF)

/* extract the पूर्णांकerrupt level */
#घोषणा DIO_IPL(baseaddr) (((in_8((baseaddr) + DIO_IPLOFF) >> 4) & 0x03) + 3)

/* find the size of a DIO-II board's address space.
 * DIO boards are all fixed length.
 */
#घोषणा DIOII_SIZE(baseaddr) ((in_8((baseaddr) + DIOII_SIZखातापूर्णF) + 1) * 0x100000)

/* general purpose macro क्रम both DIO and DIO-II */
#घोषणा DIO_SIZE(scode, base) (DIO_ISDIOII((scode)) ? DIOII_SIZE((base)) : DIO_DEVSIZE)

/* The hardware has primary and secondary IDs; we encode these in a single
 * पूर्णांक as PRIMARY ID & (SECONDARY ID << 8).
 * In practice this is only important क्रम framebuffers,
 * and everybody अन्यथा just sets ID fields equal to the DIO_ID_FOO value.
 */
#घोषणा DIO_ENCODE_ID(pr,sec) ((((पूर्णांक)sec & 0xff) << 8) | ((पूर्णांक)pr & 0xff))
/* macro to determine whether a given primary ID requires a secondary ID byte */
#घोषणा DIO_NEEDSSECID(id) ((id) == DIO_ID_FBUFFER)
#घोषणा DIO_WILDCARD 0xff

/* Now a whole slew of macros giving device IDs and descriptive strings: */
#घोषणा DIO_ID_DCA0     0x02 /* 98644A serial */
#घोषणा DIO_DESC_DCA0 "98644A DCA0 serial"
#घोषणा DIO_ID_DCA0REM  0x82 /* 98644A serial */
#घोषणा DIO_DESC_DCA0REM "98644A DCA0REM serial"
#घोषणा DIO_ID_DCA1     0x42 /* 98644A serial */
#घोषणा DIO_DESC_DCA1 "98644A DCA1 serial"
#घोषणा DIO_ID_DCA1REM  0xc2 /* 98644A serial */
#घोषणा DIO_DESC_DCA1REM "98644A DCA1REM serial"
#घोषणा DIO_ID_DCM      0x05 /* 98642A serial MUX */
#घोषणा DIO_DESC_DCM "98642A DCM serial MUX"
#घोषणा DIO_ID_DCMREM   0x85 /* 98642A serial MUX */
#घोषणा DIO_DESC_DCMREM "98642A DCMREM serial MUX"
#घोषणा DIO_ID_LAN      0x15 /* 98643A LAN */
#घोषणा DIO_DESC_LAN "98643A LANCE ethernet"
#घोषणा DIO_ID_FHPIB    0x08 /* 98625A/98625B fast HP-IB */
#घोषणा DIO_DESC_FHPIB "98625A/98625B fast HPIB"
#घोषणा DIO_ID_NHPIB    0x01 /* 98624A HP-IB (normal ie slow) */
#घोषणा DIO_DESC_NHPIB "98624A HPIB"
#घोषणा DIO_ID_SCSI0    0x07 /* 98265A SCSI */
#घोषणा DIO_DESC_SCSI0 "98265A SCSI0"
#घोषणा DIO_ID_SCSI1    0x27 /* ditto */
#घोषणा DIO_DESC_SCSI1 "98265A SCSI1"
#घोषणा DIO_ID_SCSI2    0x47 /* ditto */
#घोषणा DIO_DESC_SCSI2 "98265A SCSI2"
#घोषणा DIO_ID_SCSI3    0x67 /* ditto */
#घोषणा DIO_DESC_SCSI3 "98265A SCSI3"
#घोषणा DIO_ID_FBUFFER  0x39 /* framebuffer: flavour is distinguished by secondary ID */
#घोषणा DIO_DESC_FBUFFER "bitmapped display"
/* the NetBSD kernel source is a bit unsure as to what these next IDs actually करो :-> */
#घोषणा DIO_ID_MISC0    0x03 /* 98622A */
#घोषणा DIO_DESC_MISC0 "98622A"
#घोषणा DIO_ID_MISC1    0x04 /* 98623A */
#घोषणा DIO_DESC_MISC1 "98623A"
#घोषणा DIO_ID_PARALLEL 0x06 /* पूर्णांकernal parallel */
#घोषणा DIO_DESC_PARALLEL "internal parallel"
#घोषणा DIO_ID_MISC2    0x09 /* 98287A keyboard */
#घोषणा DIO_DESC_MISC2 "98287A keyboard"
#घोषणा DIO_ID_MISC3    0x0a /* HP98635A FP accelerator */
#घोषणा DIO_DESC_MISC3 "HP98635A FP accelerator"
#घोषणा DIO_ID_MISC4    0x0b /* समयr */
#घोषणा DIO_DESC_MISC4 "timer"
#घोषणा DIO_ID_MISC5    0x12 /* 98640A */
#घोषणा DIO_DESC_MISC5 "98640A"
#घोषणा DIO_ID_MISC6    0x16 /* 98659A */
#घोषणा DIO_DESC_MISC6 "98659A"
#घोषणा DIO_ID_MISC7    0x19 /* 237 display */
#घोषणा DIO_DESC_MISC7 "237 display"
#घोषणा DIO_ID_MISC8    0x1a /* quad-wide card */
#घोषणा DIO_DESC_MISC8 "quad-wide card"
#घोषणा DIO_ID_MISC9    0x1b /* 98253A */
#घोषणा DIO_DESC_MISC9 "98253A"
#घोषणा DIO_ID_MISC10   0x1c /* 98627A */
#घोषणा DIO_DESC_MISC10 "98253A"
#घोषणा DIO_ID_MISC11   0x1d /* 98633A */
#घोषणा DIO_DESC_MISC11 "98633A"
#घोषणा DIO_ID_MISC12   0x1e /* 98259A */
#घोषणा DIO_DESC_MISC12 "98259A"
#घोषणा DIO_ID_MISC13   0x1f /* 8741 */
#घोषणा DIO_DESC_MISC13 "8741"
#घोषणा DIO_ID_VME      0x31 /* 98577A VME adapter */
#घोषणा DIO_DESC_VME "98577A VME adapter"
#घोषणा DIO_ID_DCL      0x34 /* 98628A serial */
#घोषणा DIO_DESC_DCL "98628A DCL serial"
#घोषणा DIO_ID_DCLREM   0xb4 /* 98628A serial */
#घोषणा DIO_DESC_DCLREM "98628A DCLREM serial"
/* These are the secondary IDs क्रम the framebuffers */
#घोषणा DIO_ID2_GATORBOX    0x01 /* 98700/98710 "gatorbox" */
#घोषणा DIO_DESC2_GATORBOX       "98700/98710 \"gatorbox\" display"
#घोषणा DIO_ID2_TOPCAT      0x02 /* 98544/98545/98547 "topcat" */
#घोषणा DIO_DESC2_TOPCAT         "98544/98545/98547 \"topcat\" display"
#घोषणा DIO_ID2_RENAISSANCE 0x04 /* 98720/98721 "renaissance" */
#घोषणा DIO_DESC2_RENAISSANCE    "98720/98721 \"renaissance\" display"
#घोषणा DIO_ID2_LRCATSEYE   0x05 /* lowres "catseye" */
#घोषणा DIO_DESC2_LRCATSEYE      "low-res catseye display"
#घोषणा DIO_ID2_HRCCATSEYE  0x06 /* highres colour "catseye" */
#घोषणा DIO_DESC2_HRCCATSEYE     "high-res color catseye display"
#घोषणा DIO_ID2_HRMCATSEYE  0x07 /* highres mono "catseye" */
#घोषणा DIO_DESC2_HRMCATSEYE     "high-res mono catseye display"
#घोषणा DIO_ID2_DAVINCI     0x08 /* 98730/98731 "davinci" */
#घोषणा DIO_DESC2_DAVINCI        "98730/98731 \"davinci\" display"
#घोषणा DIO_ID2_XXXCATSEYE  0x09 /* "catseye" */
#घोषणा DIO_DESC2_XXXCATSEYE     "catseye display"
#घोषणा DIO_ID2_HYPERION    0x0e /* A1096A "hyperion" */
#घोषणा DIO_DESC2_HYPERION       "A1096A \"hyperion\" display"
#घोषणा DIO_ID2_XGENESIS    0x0b /* "x-genesis"; no NetBSD support */
#घोषणा DIO_DESC2_XGENESIS       "\"x-genesis\" display"
#घोषणा DIO_ID2_TIGER       0x0c /* "tiger"; no NetBSD support */
#घोषणा DIO_DESC2_TIGER          "\"tiger\" display"
#घोषणा DIO_ID2_YGENESIS    0x0d /* "y-genesis"; no NetBSD support */
#घोषणा DIO_DESC2_YGENESIS       "\"y-genesis\" display"
/* अगर you add new IDs then you should tell dio.c about them so it can
 * identअगरy them...
 */

बाह्य पूर्णांक dio_find(पूर्णांक deviceid);
बाह्य अचिन्हित दीर्घ dio_scodetophysaddr(पूर्णांक scode);
बाह्य पूर्णांक dio_create_sysfs_dev_files(काष्ठा dio_dev *);

/* New-style probing */
बाह्य पूर्णांक dio_रेजिस्टर_driver(काष्ठा dio_driver *);
बाह्य व्योम dio_unरेजिस्टर_driver(काष्ठा dio_driver *);

#घोषणा dio_resource_start(d) ((d)->resource.start)
#घोषणा dio_resource_end(d)   ((d)->resource.end)
#घोषणा dio_resource_len(d)   (resource_size(&(d)->resource))
#घोषणा dio_resource_flags(d) ((d)->resource.flags)

#घोषणा dio_request_device(d, name) \
    request_mem_region(dio_resource_start(d), dio_resource_len(d), name)
#घोषणा dio_release_device(d) \
    release_mem_region(dio_resource_start(d), dio_resource_len(d))

/* Similar to the helpers above, these manipulate per-dio_dev
 * driver-specअगरic data.  They are really just a wrapper around
 * the generic device काष्ठाure functions of these calls.
 */
अटल अंतरभूत व्योम *dio_get_drvdata (काष्ठा dio_dev *d)
अणु
	वापस dev_get_drvdata(&d->dev);
पूर्ण

अटल अंतरभूत व्योम dio_set_drvdata (काष्ठा dio_dev *d, व्योम *data)
अणु
	dev_set_drvdata(&d->dev, data);
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* ndef _LINUX_DIO_H */
