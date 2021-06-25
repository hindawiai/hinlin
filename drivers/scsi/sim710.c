<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sim710.c - Copyright (C) 1999 Riअक्षरd Hirst <riअक्षरd@sleepie.demon.co.uk>
 *
 *----------------------------------------------------------------------------
 *----------------------------------------------------------------------------
 *
 * MCA card detection code by Trent McNair. (now deleted)
 * Fixes to not explicitly nul bss data from Xavier Bestel.
 * Some multiboard fixes from Rolf Eike Beer.
 * Auto probing of EISA config space from Trevor Hemsley.
 *
 * Rewritten to use 53c700.c by James.Bottomley@SteelEye.com
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <linux/blkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/eisa.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_transport.h>
#समावेश <scsi/scsi_transport_spi.h>

#समावेश "53c700.h"


/* Must be enough क्रम EISA */
#घोषणा MAX_SLOTS 8
अटल __u8 __initdata id_array[MAX_SLOTS] = अणु [0 ... MAX_SLOTS-1] = 7 पूर्ण;

अटल अक्षर *sim710;		/* command line passed by insmod */

MODULE_AUTHOR("Richard Hirst");
MODULE_DESCRIPTION("Simple NCR53C710 driver");
MODULE_LICENSE("GPL");

module_param(sim710, अक्षरp, 0);

#अगर_घोषित MODULE
#घोषणा ARG_SEP ' '
#अन्यथा
#घोषणा ARG_SEP ','
#पूर्ण_अगर

अटल __init पूर्णांक
param_setup(अक्षर *str)
अणु
	अक्षर *pos = str, *next;
	पूर्णांक slot = -1;

	जबतक(pos != शून्य && (next = म_अक्षर(pos, ':')) != शून्य) अणु
		पूर्णांक val = (पूर्णांक)simple_म_से_अदीर्घ(++next, शून्य, 0);

		अगर(!म_भेदन(pos, "slot:", 5))
			slot = val;
		अन्यथा अगर(!म_भेदन(pos, "id:", 3)) अणु
			अगर(slot == -1) अणु
				prपूर्णांकk(KERN_WARNING "sim710: Must specify slot for id parameter\n");
			पूर्ण अन्यथा अगर(slot >= MAX_SLOTS) अणु
				prपूर्णांकk(KERN_WARNING "sim710: Illegal slot %d for id %d\n", slot, val);
			पूर्ण अन्यथा अणु
				id_array[slot] = val;
			पूर्ण
		पूर्ण
		अगर((pos = म_अक्षर(pos, ARG_SEP)) != शून्य)
			pos++;
	पूर्ण
	वापस 1;
पूर्ण
__setup("sim710=", param_setup);

अटल काष्ठा scsi_host_ढाँचा sim710_driver_ढाँचा = अणु
	.name			= "LSI (Symbios) 710 EISA",
	.proc_name		= "sim710",
	.this_id		= 7,
	.module			= THIS_MODULE,
पूर्ण;

अटल पूर्णांक sim710_probe_common(काष्ठा device *dev, अचिन्हित दीर्घ base_addr,
			       पूर्णांक irq, पूर्णांक घड़ी, पूर्णांक dअगरferential,
			       पूर्णांक scsi_id)
अणु
	काष्ठा Scsi_Host * host = शून्य;
	काष्ठा NCR_700_Host_Parameters *hostdata =
		kzalloc(माप(काष्ठा NCR_700_Host_Parameters),	GFP_KERNEL);

	prपूर्णांकk(KERN_NOTICE "sim710: %s\n", dev_name(dev));
	prपूर्णांकk(KERN_NOTICE "sim710: irq = %d, clock = %d, base = 0x%lx, scsi_id = %d\n",
	       irq, घड़ी, base_addr, scsi_id);

	अगर(hostdata == शून्य) अणु
		prपूर्णांकk(KERN_ERR "sim710: Failed to allocate host data\n");
		जाओ out;
	पूर्ण

	अगर(request_region(base_addr, 64, "sim710") == शून्य) अणु
		prपूर्णांकk(KERN_ERR "sim710: Failed to reserve IO region 0x%lx\n",
		       base_addr);
		जाओ out_मुक्त;
	पूर्ण

	/* Fill in the three required pieces of hostdata */
	hostdata->base = ioport_map(base_addr, 64);
	hostdata->dअगरferential = dअगरferential;
	hostdata->घड़ी = घड़ी;
	hostdata->chip710 = 1;
	hostdata->burst_length = 8;

	/* and रेजिस्टर the chip */
	अगर((host = NCR_700_detect(&sim710_driver_ढाँचा, hostdata, dev))
	   == शून्य) अणु
		prपूर्णांकk(KERN_ERR "sim710: No host detected; card configuration problem?\n");
		जाओ out_release;
	पूर्ण
	host->this_id = scsi_id;
	host->base = base_addr;
	host->irq = irq;
	अगर (request_irq(irq, NCR_700_पूर्णांकr, IRQF_SHARED, "sim710", host)) अणु
		prपूर्णांकk(KERN_ERR "sim710: request_irq failed\n");
		जाओ out_put_host;
	पूर्ण

	dev_set_drvdata(dev, host);
	scsi_scan_host(host);

	वापस 0;

 out_put_host:
	scsi_host_put(host);
 out_release:
	release_region(base_addr, 64);
 out_मुक्त:
	kमुक्त(hostdata);
 out:
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक sim710_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा Scsi_Host *host = dev_get_drvdata(dev);
	काष्ठा NCR_700_Host_Parameters *hostdata =
		(काष्ठा NCR_700_Host_Parameters *)host->hostdata[0];

	scsi_हटाओ_host(host);
	NCR_700_release(host);
	kमुक्त(hostdata);
	मुक्त_irq(host->irq, host);
	release_region(host->base, 64);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_EISA
अटल काष्ठा eisa_device_id sim710_eisa_ids[] = अणु
	अणु "CPQ4410" पूर्ण,
	अणु "CPQ4411" पूर्ण,
	अणु "HWP0C80" पूर्ण,
	अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, sim710_eisa_ids);

अटल पूर्णांक sim710_eisa_probe(काष्ठा device *dev)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	अचिन्हित दीर्घ io_addr = edev->base_addr;
	अक्षर eisa_cpq_irqs[] = अणु 11, 14, 15, 10, 9, 0 पूर्ण;
	अक्षर eisa_hwp_irqs[] = अणु 3, 4, 5, 7, 12, 10, 11, 0पूर्ण;
	अक्षर *eisa_irqs;
	अचिन्हित अक्षर irq_index;
	अचिन्हित अक्षर irq, dअगरferential = 0, scsi_id = 7;

	अगर(म_भेद(edev->id.sig, "HWP0C80") == 0) अणु
		__u8 val;
		eisa_irqs =  eisa_hwp_irqs;
		irq_index = (inb(io_addr + 0xc85) & 0x7) - 1;

		val = inb(io_addr + 0x4);
		scsi_id = ffs(val) - 1;

		अगर(scsi_id > 7 || (val & ~(1<<scsi_id)) != 0) अणु
			prपूर्णांकk(KERN_ERR "sim710.c, EISA card %s has incorrect scsi_id, setting to 7\n", dev_name(dev));
			scsi_id = 7;
		पूर्ण
	पूर्ण अन्यथा अणु
		eisa_irqs = eisa_cpq_irqs;
		irq_index = inb(io_addr + 0xc88) & 0x07;
	पूर्ण

	अगर(irq_index >= म_माप(eisa_irqs)) अणु
		prपूर्णांकk("sim710.c: irq nasty\n");
		वापस -ENODEV;
	पूर्ण

	irq = eisa_irqs[irq_index];
		
	वापस sim710_probe_common(dev, io_addr, irq, 50,
				   dअगरferential, scsi_id);
पूर्ण

अटल काष्ठा eisa_driver sim710_eisa_driver = अणु
	.id_table		= sim710_eisa_ids,
	.driver = अणु
		.name		= "sim710",
		.probe		= sim710_eisa_probe,
		.हटाओ		= sim710_device_हटाओ,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर /* CONFIG_EISA */

अटल पूर्णांक __init sim710_init(व्योम)
अणु
#अगर_घोषित MODULE
	अगर (sim710)
		param_setup(sim710);
#पूर्ण_अगर

#अगर_घोषित CONFIG_EISA
	/*
	 * FIXME: We'd really like to वापस -ENODEV अगर no devices have actually
	 * been found.  However eisa_driver_रेजिस्टर() only reports problems
	 * with kobject_रेजिस्टर() so simply वापस success क्रम now.
	 */
	eisa_driver_रेजिस्टर(&sim710_eisa_driver);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम __निकास sim710_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_EISA
	eisa_driver_unरेजिस्टर(&sim710_eisa_driver);
#पूर्ण_अगर
पूर्ण

module_init(sim710_init);
module_निकास(sim710_निकास);
