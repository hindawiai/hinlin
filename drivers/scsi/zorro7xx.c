<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Detection routine क्रम the NCR53c710 based Amiga SCSI Controllers क्रम Linux.
 *		Amiga MacroSystemUS WarpEngine SCSI controller.
 *		Amiga Technologies/DKB A4091 SCSI controller.
 *
 * Written 1997 by Alan Hourihane <alanh@fairlite.demon.co.uk>
 * plus modअगरications of the 53c7xx.c driver to support the Amiga.
 *
 * Rewritten to use 53c700.c by Kars de Jong <jongk@linux-m68k.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/zorro.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/amigahw.h>
#समावेश <यंत्र/amigaपूर्णांकs.h>

#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"

MODULE_AUTHOR("Alan Hourihane <alanh@fairlite.demon.co.uk> / Kars de Jong <jongk@linux-m68k.org>");
MODULE_DESCRIPTION("Amiga Zorro NCR53C710 driver");
MODULE_LICENSE("GPL");


अटल काष्ठा scsi_host_ढाँचा zorro7xx_scsi_driver_ढाँचा = अणु
	.proc_name	= "zorro7xx",
	.this_id	= 7,
	.module		= THIS_MODULE,
पूर्ण;

अटल काष्ठा zorro_driver_data अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ offset;
	पूर्णांक असलolute;	/* offset is असलolute address */
पूर्ण zorro7xx_driver_data[] = अणु
	अणु .name = "PowerUP 603e+", .offset = 0xf40000, .असलolute = 1 पूर्ण,
	अणु .name = "WarpEngine 40xx", .offset = 0x40000 पूर्ण,
	अणु .name = "A4091", .offset = 0x800000 पूर्ण,
	अणु .name = "GForce 040/060", .offset = 0x40000 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा zorro_device_id zorro7xx_zorro_tbl[] = अणु
	अणु
		.id = ZORRO_PROD_PHASE5_BLIZZARD_603E_PLUS,
		.driver_data = (अचिन्हित दीर्घ)&zorro7xx_driver_data[0],
	पूर्ण,
	अणु
		.id = ZORRO_PROD_MACROSYSTEMS_WARP_ENGINE_40xx,
		.driver_data = (अचिन्हित दीर्घ)&zorro7xx_driver_data[1],
	पूर्ण,
	अणु
		.id = ZORRO_PROD_CBM_A4091_1,
		.driver_data = (अचिन्हित दीर्घ)&zorro7xx_driver_data[2],
	पूर्ण,
	अणु
		.id = ZORRO_PROD_CBM_A4091_2,
		.driver_data = (अचिन्हित दीर्घ)&zorro7xx_driver_data[2],
	पूर्ण,
	अणु
		.id = ZORRO_PROD_GVP_GFORCE_040_060,
		.driver_data = (अचिन्हित दीर्घ)&zorro7xx_driver_data[3],
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(zorro, zorro7xx_zorro_tbl);

अटल पूर्णांक zorro7xx_init_one(काष्ठा zorro_dev *z,
			     स्थिर काष्ठा zorro_device_id *ent)
अणु
	काष्ठा Scsi_Host *host;
	काष्ठा NCR_700_Host_Parameters *hostdata;
	काष्ठा zorro_driver_data *zdd;
	अचिन्हित दीर्घ board, ioaddr;

	board = zorro_resource_start(z);
	zdd = (काष्ठा zorro_driver_data *)ent->driver_data;

	अगर (zdd->असलolute) अणु
		ioaddr = zdd->offset;
	पूर्ण अन्यथा अणु
		ioaddr = board + zdd->offset;
	पूर्ण

	अगर (!zorro_request_device(z, zdd->name)) अणु
		prपूर्णांकk(KERN_ERR "zorro7xx: cannot reserve region 0x%lx, abort\n",
		       board);
		वापस -EBUSY;
	पूर्ण

	hostdata = kzalloc(माप(काष्ठा NCR_700_Host_Parameters), GFP_KERNEL);
	अगर (!hostdata) अणु
		prपूर्णांकk(KERN_ERR "zorro7xx: Failed to allocate host data\n");
		जाओ out_release;
	पूर्ण

	/* Fill in the required pieces of hostdata */
	अगर (ioaddr > 0x01000000)
		hostdata->base = ioremap(ioaddr, zorro_resource_len(z));
	अन्यथा
		hostdata->base = ZTWO_VADDR(ioaddr);

	hostdata->घड़ी = 50;
	hostdata->chip710 = 1;

	/* Settings क्रम at least WarpEngine 40xx */
	hostdata->ctest7_extra = CTEST7_TT1;

	zorro7xx_scsi_driver_ढाँचा.name = zdd->name;

	/* and रेजिस्टर the chip */
	host = NCR_700_detect(&zorro7xx_scsi_driver_ढाँचा, hostdata,
			      &z->dev);
	अगर (!host) अणु
		prपूर्णांकk(KERN_ERR "zorro7xx: No host detected; "
				"board configuration problem?\n");
		जाओ out_मुक्त;
	पूर्ण

	host->this_id = 7;
	host->base = ioaddr;
	host->irq = IRQ_AMIGA_PORTS;

	अगर (request_irq(host->irq, NCR_700_पूर्णांकr, IRQF_SHARED, "zorro7xx-scsi",
			host)) अणु
		prपूर्णांकk(KERN_ERR "zorro7xx: request_irq failed\n");
		जाओ out_put_host;
	पूर्ण

	zorro_set_drvdata(z, host);
	scsi_scan_host(host);

	वापस 0;

 out_put_host:
	scsi_host_put(host);
 out_मुक्त:
	अगर (ioaddr > 0x01000000)
		iounmap(hostdata->base);
	kमुक्त(hostdata);
 out_release:
	zorro_release_device(z);

	वापस -ENODEV;
पूर्ण

अटल व्योम zorro7xx_हटाओ_one(काष्ठा zorro_dev *z)
अणु
	काष्ठा Scsi_Host *host = zorro_get_drvdata(z);
	काष्ठा NCR_700_Host_Parameters *hostdata = shost_priv(host);

	scsi_हटाओ_host(host);

	NCR_700_release(host);
	kमुक्त(hostdata);
	मुक्त_irq(host->irq, host);
	zorro_release_device(z);
पूर्ण

अटल काष्ठा zorro_driver zorro7xx_driver = अणु
	.name	  = "zorro7xx-scsi",
	.id_table = zorro7xx_zorro_tbl,
	.probe	  = zorro7xx_init_one,
	.हटाओ	  = zorro7xx_हटाओ_one,
पूर्ण;

अटल पूर्णांक __init zorro7xx_scsi_init(व्योम)
अणु
	वापस zorro_रेजिस्टर_driver(&zorro7xx_driver);
पूर्ण

अटल व्योम __निकास zorro7xx_scsi_निकास(व्योम)
अणु
	zorro_unरेजिस्टर_driver(&zorro7xx_driver);
पूर्ण

module_init(zorro7xx_scsi_init);
module_निकास(zorro7xx_scsi_निकास);
