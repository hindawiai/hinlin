<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Code to support devices on the DIO and DIO-II bus
 * Copyright (C) 05/1998 Peter Maydell <pmaydell@chiark.greenend.org.uk>
 * Copyright (C) 2004 Jochen Friedrich <jochen@scram.de>
 * 
 * This code has basically these routines at the moment:
 * पूर्णांक dio_find(u_पूर्णांक deviceid)
 *    Search the list of DIO devices and वापस the select code
 *    of the next unconfigured device found that matches the given device ID.
 *    Note that the deviceid parameter should be the encoded ID.
 *    This means that framebuffers should pass it as 
 *    DIO_ENCODE_ID(DIO_ID_FBUFFER,DIO_ID2_TOPCAT)
 *    (or whatever); everybody अन्यथा just uses DIO_ID_FOOBAR.
 * अचिन्हित दीर्घ dio_scodetophysaddr(पूर्णांक scode)
 *    Return the physical address corresponding to the given select code.
 * पूर्णांक dio_scodetoipl(पूर्णांक scode)
 *    Every DIO card has a fixed पूर्णांकerrupt priority level. This function 
 *    वापसs it, whatever it is.
 * स्थिर अक्षर *dio_scodetoname(पूर्णांक scode)
 *    Return a अक्षरacter string describing this board [might be "" अगर 
 *    not CONFIG_DIO_CONSTANTS]
 * व्योम dio_config_board(पूर्णांक scode)     mark board as configured in the list
 * व्योम dio_unconfig_board(पूर्णांक scode)   mark board as no दीर्घer configured
 *
 * This file is based on the way the Amiga port handles Zorro II cards, 
 * although we aren't so complicated...
 */
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/dपन.स>
#समावेश <linux/slab.h>                         /* kदो_स्मृति() */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>                             /* पढ़ोb() */

काष्ठा dio_bus dio_bus = अणु
	.resources = अणु
		/* DIO range */
		अणु .name = "DIO mem", .start = 0x00600000, .end = 0x007fffff पूर्ण,
		/* DIO-II range */
		अणु .name = "DIO-II mem", .start = 0x01000000, .end = 0x1fffffff पूर्ण
	पूर्ण,
	.name = "DIO bus"
पूर्ण;

/* not a real config option yet! */
#घोषणा CONFIG_DIO_CONSTANTS

#अगर_घोषित CONFIG_DIO_CONSTANTS
/* We associate each numeric ID with an appropriate descriptive string
 * using a स्थिरant array of these काष्ठाs.
 * FIXME: we should be able to arrange to throw away most of the strings
 * using the initdata stuff. Then we wouldn't need to worry about 
 * carrying them around...
 * I think we करो this by copying them पूर्णांकo newly kदो_स्मृति()ed memory and 
 * marking the names[] array as .initdata ?
 */
काष्ठा dioname
अणु
        पूर्णांक id;
        स्थिर अक्षर *name;
पूर्ण;

/* useful macro */
#घोषणा DIONAME(x) अणु DIO_ID_##x, DIO_DESC_##x पूर्ण
#घोषणा DIOFBNAME(x) अणु DIO_ENCODE_ID( DIO_ID_FBUFFER, DIO_ID2_##x), DIO_DESC2_##x पूर्ण

अटल काष्ठा dioname names[] = 
अणु
        DIONAME(DCA0), DIONAME(DCA0REM), DIONAME(DCA1), DIONAME(DCA1REM),
        DIONAME(DCM), DIONAME(DCMREM),
        DIONAME(LAN),
        DIONAME(FHPIB), DIONAME(NHPIB),
        DIONAME(SCSI0), DIONAME(SCSI1), DIONAME(SCSI2), DIONAME(SCSI3),
        DIONAME(FBUFFER),
        DIONAME(PARALLEL), DIONAME(VME), DIONAME(DCL), DIONAME(DCLREM),
        DIONAME(MISC0), DIONAME(MISC1), DIONAME(MISC2), DIONAME(MISC3),
        DIONAME(MISC4), DIONAME(MISC5), DIONAME(MISC6), DIONAME(MISC7),
        DIONAME(MISC8), DIONAME(MISC9), DIONAME(MISC10), DIONAME(MISC11), 
        DIONAME(MISC12), DIONAME(MISC13),
        DIOFBNAME(GATORBOX), DIOFBNAME(TOPCAT), DIOFBNAME(RENAISSANCE),
        DIOFBNAME(LRCATSEYE), DIOFBNAME(HRCCATSEYE), DIOFBNAME(HRMCATSEYE),
        DIOFBNAME(DAVINCI), DIOFBNAME(XXXCATSEYE), DIOFBNAME(HYPERION),
        DIOFBNAME(XGENESIS), DIOFBNAME(TIGER), DIOFBNAME(YGENESIS)   
पूर्ण;

#अघोषित DIONAME
#अघोषित DIOFBNAME

अटल स्थिर अक्षर unknowndioname[]
	= "unknown DIO board, please email linux-m68k@lists.linux-m68k.org";

अटल स्थिर अक्षर *dio_getname(पूर्णांक id)
अणु
        /* वापस poपूर्णांकer to a स्थिरant string describing the board with given ID */
	अचिन्हित पूर्णांक i;
	क्रम (i = 0; i < ARRAY_SIZE(names); i++)
                अगर (names[i].id == id) 
                        वापस names[i].name;

        वापस unknowndioname;
पूर्ण

#अन्यथा

अटल अक्षर dio_no_name[] = अणु 0 पूर्ण;
#घोषणा dio_getname(_id)	(dio_no_name)

#पूर्ण_अगर /* CONFIG_DIO_CONSTANTS */

पूर्णांक __init dio_find(पूर्णांक deviceid)
अणु
	/* Called to find a DIO device beक्रमe the full bus scan has run.
	 * Only used by the console driver.
	 */
	पूर्णांक scode, id;
	u_अक्षर prid, secid, i;

	क्रम (scode = 0; scode < DIO_SCMAX; scode++) अणु
		व्योम *va;
		अचिन्हित दीर्घ pa;

                अगर (DIO_SCINHOLE(scode))
                        जारी;

                pa = dio_scodetophysaddr(scode);

		अगर (!pa)
			जारी;

		अगर (scode < DIOII_SCBASE)
			va = (व्योम *)(pa + DIO_VIRADDRBASE);
		अन्यथा
			va = ioremap(pa, PAGE_SIZE);

		अगर (copy_from_kernel_nofault(&i,
				(अचिन्हित अक्षर *)va + DIO_IDOFF, 1)) अणु
			अगर (scode >= DIOII_SCBASE)
				iounmap(va);
                        जारी;             /* no board present at that select code */
		पूर्ण

		prid = DIO_ID(va);

                अगर (DIO_NEEDSSECID(prid)) अणु
                        secid = DIO_SECID(va);
                        id = DIO_ENCODE_ID(prid, secid);
                पूर्ण अन्यथा
			id = prid;

		अगर (id == deviceid) अणु
			अगर (scode >= DIOII_SCBASE)
				iounmap(va);
			वापस scode;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

/* This is the function that scans the DIO space and works out what
 * hardware is actually present.
 */
अटल पूर्णांक __init dio_init(व्योम)
अणु
	पूर्णांक scode;
	पूर्णांक i;
	काष्ठा dio_dev *dev;
	पूर्णांक error;

	अगर (!MACH_IS_HP300)
		वापस 0;

        prपूर्णांकk(KERN_INFO "Scanning for DIO devices...\n");

	/* Initialize the DIO bus */ 
	INIT_LIST_HEAD(&dio_bus.devices);
	dev_set_name(&dio_bus.dev, "dio");
	error = device_रेजिस्टर(&dio_bus.dev);
	अगर (error) अणु
		pr_err("DIO: Error registering dio_bus\n");
		वापस error;
	पूर्ण

	/* Request all resources */
	dio_bus.num_resources = (hp300_model == HP_320 ? 1 : 2);
	क्रम (i = 0; i < dio_bus.num_resources; i++)
		request_resource(&iomem_resource, &dio_bus.resources[i]);

	/* Register all devices */
        क्रम (scode = 0; scode < DIO_SCMAX; ++scode)
        अणु
                u_अक्षर prid, secid = 0;        /* primary, secondary ID bytes */
                u_अक्षर *va;
		अचिन्हित दीर्घ pa;
                
                अगर (DIO_SCINHOLE(scode))
                        जारी;

		pa = dio_scodetophysaddr(scode);

		अगर (!pa)
			जारी;

		अगर (scode < DIOII_SCBASE)
			va = (व्योम *)(pa + DIO_VIRADDRBASE);
		अन्यथा
			va = ioremap(pa, PAGE_SIZE);

		अगर (copy_from_kernel_nofault(&i,
				(अचिन्हित अक्षर *)va + DIO_IDOFF, 1)) अणु
			अगर (scode >= DIOII_SCBASE)
				iounmap(va);
                        जारी;              /* no board present at that select code */
		पूर्ण

                /* Found a board, allocate it an entry in the list */
		dev = kzalloc(माप(काष्ठा dio_dev), GFP_KERNEL);
		अगर (!dev)
			वापस 0;

		dev->bus = &dio_bus;
		dev->dev.parent = &dio_bus.dev;
		dev->dev.bus = &dio_bus_type;
		dev->scode = scode;
		dev->resource.start = pa;
		dev->resource.end = pa + DIO_SIZE(scode, va);
		dev_set_name(&dev->dev, "%02x", scode);

                /* पढ़ो the ID byte(s) and encode अगर necessary. */
		prid = DIO_ID(va);

                अगर (DIO_NEEDSSECID(prid)) अणु
                        secid = DIO_SECID(va);
                        dev->id = DIO_ENCODE_ID(prid, secid);
                पूर्ण अन्यथा
                        dev->id = prid;

                dev->ipl = DIO_IPL(va);
                म_नकल(dev->name,dio_getname(dev->id));
                prपूर्णांकk(KERN_INFO "select code %3d: ipl %d: ID %02X", dev->scode, dev->ipl, prid);
                अगर (DIO_NEEDSSECID(prid))
                        prपूर्णांकk(":%02X", secid);
                prपूर्णांकk(": %s\n", dev->name);

		अगर (scode >= DIOII_SCBASE)
			iounmap(va);
		error = device_रेजिस्टर(&dev->dev);
		अगर (error) अणु
			pr_err("DIO: Error registering device %s\n",
			       dev->name);
			जारी;
		पूर्ण
		error = dio_create_sysfs_dev_files(dev);
		अगर (error)
			dev_err(&dev->dev, "Error creating sysfs files\n");
        पूर्ण
	वापस 0;
पूर्ण

subsys_initcall(dio_init);

/* Bear in mind that this is called in the very early stages of initialisation
 * in order to get the address of the serial port क्रम the console...
 */
अचिन्हित दीर्घ dio_scodetophysaddr(पूर्णांक scode)
अणु
        अगर (scode >= DIOII_SCBASE) अणु
                वापस (DIOII_BASE + (scode - 132) * DIOII_DEVSIZE);
        पूर्ण अन्यथा अगर (scode > DIO_SCMAX || scode < 0)
                वापस 0;
        अन्यथा अगर (DIO_SCINHOLE(scode))
                वापस 0;

        वापस (DIO_BASE + scode * DIO_DEVSIZE);
पूर्ण
