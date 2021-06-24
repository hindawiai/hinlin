<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/isa.h>
#समावेश <scsi/scsi_host.h>
#समावेश "fdomain.h"

#घोषणा MAXBOARDS_PARAM 4
अटल पूर्णांक io[MAXBOARDS_PARAM] = अणु 0, 0, 0, 0 पूर्ण;
module_param_hw_array(io, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(io, "base I/O address of controller (0x140, 0x150, 0x160, 0x170)");

अटल पूर्णांक irq[MAXBOARDS_PARAM] = अणु 0, 0, 0, 0 पूर्ण;
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "IRQ of controller (0=auto [default])");

अटल पूर्णांक scsi_id[MAXBOARDS_PARAM] = अणु 0, 0, 0, 0 पूर्ण;
module_param_hw_array(scsi_id, पूर्णांक, other, शून्य, 0);
MODULE_PARM_DESC(scsi_id, "SCSI ID of controller (default = 7)");

अटल अचिन्हित दीर्घ addresses[] = अणु
	0xc8000,
	0xca000,
	0xce000,
	0xde000,
पूर्ण;
#घोषणा ADDRESS_COUNT ARRAY_SIZE(addresses)

अटल अचिन्हित लघु ports[] = अणु 0x140, 0x150, 0x160, 0x170 पूर्ण;
#घोषणा PORT_COUNT ARRAY_SIZE(ports)

अटल अचिन्हित लघु irqs[] = अणु 3, 5, 10, 11, 12, 14, 15, 0 पूर्ण;

/* This driver works *ONLY* क्रम Future Doमुख्य cards using the TMC-1800,
 * TMC-18C50, or TMC-18C30 chip.  This includes models TMC-1650, 1660, 1670,
 * and 1680. These are all 16-bit cards.
 * BIOS versions prior to 3.2 asचिन्हित SCSI ID 6 to SCSI adapter.
 *
 * The following BIOS signature signatures are क्रम boards which करो *NOT*
 * work with this driver (these TMC-8xx and TMC-9xx boards may work with the
 * Seagate driver):
 *
 * FUTURE DOMAIN CORP. (C) 1986-1988 V4.0I 03/16/88
 * FUTURE DOMAIN CORP. (C) 1986-1989 V5.0C2/14/89
 * FUTURE DOMAIN CORP. (C) 1986-1989 V6.0A7/28/89
 * FUTURE DOMAIN CORP. (C) 1986-1990 V6.0105/31/90
 * FUTURE DOMAIN CORP. (C) 1986-1990 V6.0209/18/90
 * FUTURE DOMAIN CORP. (C) 1986-1990 V7.009/18/90
 * FUTURE DOMAIN CORP. (C) 1992 V8.00.004/02/92
 *
 * (The cards which करो *NOT* work are all 8-bit cards -- although some of
 * them have a 16-bit क्रमm-factor, the upper 8-bits are used only क्रम IRQs
 * and are *NOT* used क्रम data. You can tell the dअगरference by following
 * the tracings on the circuit board -- अगर only the IRQ lines are involved,
 * you have a "8-bit" card, and should *NOT* use this driver.)
 */

अटल काष्ठा signature अणु
	स्थिर अक्षर *signature;
	पूर्णांक offset;
	पूर्णांक length;
	पूर्णांक this_id;
	पूर्णांक base_offset;
पूर्ण signatures[] = अणु
/*          1         2         3         4         5         6 */
/* 123456789012345678901234567890123456789012345678901234567890 */
अणु "FUTURE DOMAIN CORP. (C) 1986-1990 1800-V2.07/28/89",	 5, 50,  6, 0x1fcc पूर्ण,
अणु "FUTURE DOMAIN CORP. (C) 1986-1990 1800-V1.07/28/89",	 5, 50,  6, 0x1fcc पूर्ण,
अणु "FUTURE DOMAIN CORP. (C) 1986-1990 1800-V2.07/28/89", 72, 50,  6, 0x1fa2 पूर्ण,
अणु "FUTURE DOMAIN CORP. (C) 1986-1990 1800-V2.0",	73, 43,  6, 0x1fa2 पूर्ण,
अणु "FUTURE DOMAIN CORP. (C) 1991 1800-V2.0.",		72, 39,  6, 0x1fa3 पूर्ण,
अणु "FUTURE DOMAIN CORP. (C) 1992 V3.00.004/02/92",	 5, 44,  6, 0 पूर्ण,
अणु "FUTURE DOMAIN TMC-18XX (C) 1993 V3.203/12/93",	 5, 44,  7, 0 पूर्ण,
अणु "IBM F1 P2 BIOS v1.0011/09/92",			 5, 28,  7, 0x1ff3 पूर्ण,
अणु "IBM F1 P2 BIOS v1.0104/29/93",			 5, 28,  7, 0 पूर्ण,
अणु "Future Domain Corp. V1.0008/18/93",			 5, 33,  7, 0 पूर्ण,
अणु "Future Domain Corp. V2.0108/18/93",			 5, 33,  7, 0 पूर्ण,
अणु "FUTURE DOMAIN CORP.  V3.5008/18/93",			 5, 34,  7, 0 पूर्ण,
अणु "FUTURE DOMAIN 18c30/18c50/1800 (C) 1994 V3.5",	 5, 44,  7, 0 पूर्ण,
अणु "FUTURE DOMAIN CORP.  V3.6008/18/93",			 5, 34,  7, 0 पूर्ण,
अणु "FUTURE DOMAIN CORP.  V3.6108/18/93",			 5, 34,  7, 0 पूर्ण,
पूर्ण;
#घोषणा SIGNATURE_COUNT ARRAY_SIZE(signatures)

अटल पूर्णांक fकरोमुख्य_isa_match(काष्ठा device *dev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा Scsi_Host *sh;
	पूर्णांक i, base = 0, irq = 0;
	अचिन्हित दीर्घ bios_base = 0;
	काष्ठा signature *sig = शून्य;
	व्योम __iomem *p;
	अटल काष्ठा signature *saved_sig;
	पूर्णांक this_id = 7;

	अगर (ndev < ADDRESS_COUNT) अणु	/* scan supported ISA BIOS addresses */
		p = ioremap(addresses[ndev], FDOMAIN_BIOS_SIZE);
		अगर (!p)
			वापस 0;
		क्रम (i = 0; i < SIGNATURE_COUNT; i++)
			अगर (check_signature(p + signatures[i].offset,
					    signatures[i].signature,
					    signatures[i].length))
				अवरोध;
		अगर (i == SIGNATURE_COUNT)	/* no signature found */
			जाओ fail_unmap;
		sig = &signatures[i];
		bios_base = addresses[ndev];
		/* पढ़ो I/O base from BIOS area */
		अगर (sig->base_offset)
			base = पढ़ोb(p + sig->base_offset) +
			      (पढ़ोb(p + sig->base_offset + 1) << 8);
		iounmap(p);
		अगर (base) अणु
			dev_info(dev, "BIOS at 0x%lx specifies I/O base 0x%x\n",
				 bios_base, base);
		पूर्ण अन्यथा अणु /* no I/O base in BIOS area */
			dev_info(dev, "BIOS at 0x%lx\n", bios_base);
			/* save BIOS signature क्रम later use in port probing */
			saved_sig = sig;
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा	/* scan supported I/O ports */
		base = ports[ndev - ADDRESS_COUNT];

	/* use saved BIOS signature अगर present */
	अगर (!sig && saved_sig)
		sig = saved_sig;

	अगर (!request_region(base, FDOMAIN_REGION_SIZE, "fdomain_isa"))
		वापस 0;

	irq = irqs[(inb(base + REG_CFG1) & CFG1_IRQ_MASK) >> 1];

	अगर (sig)
		this_id = sig->this_id;

	sh = fकरोमुख्य_create(base, irq, this_id, dev);
	अगर (!sh) अणु
		release_region(base, FDOMAIN_REGION_SIZE);
		वापस 0;
	पूर्ण

	dev_set_drvdata(dev, sh);
	वापस 1;
fail_unmap:
	iounmap(p);
	वापस 0;
पूर्ण

अटल पूर्णांक fकरोमुख्य_isa_param_match(काष्ठा device *dev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा Scsi_Host *sh;
	पूर्णांक irq_ = irq[ndev];

	अगर (!io[ndev])
		वापस 0;

	अगर (!request_region(io[ndev], FDOMAIN_REGION_SIZE, "fdomain_isa")) अणु
		dev_err(dev, "base 0x%x already in use", io[ndev]);
		वापस 0;
	पूर्ण

	अगर (irq_ <= 0)
		irq_ = irqs[(inb(io[ndev] + REG_CFG1) & CFG1_IRQ_MASK) >> 1];

	sh = fकरोमुख्य_create(io[ndev], irq_, scsi_id[ndev], dev);
	अगर (!sh) अणु
		dev_err(dev, "controller not found at base 0x%x", io[ndev]);
		release_region(io[ndev], FDOMAIN_REGION_SIZE);
		वापस 0;
	पूर्ण

	dev_set_drvdata(dev, sh);
	वापस 1;
पूर्ण

अटल व्योम fकरोमुख्य_isa_हटाओ(काष्ठा device *dev, अचिन्हित पूर्णांक ndev)
अणु
	काष्ठा Scsi_Host *sh = dev_get_drvdata(dev);
	पूर्णांक base = sh->io_port;

	fकरोमुख्य_destroy(sh);
	release_region(base, FDOMAIN_REGION_SIZE);
	dev_set_drvdata(dev, शून्य);
पूर्ण

अटल काष्ठा isa_driver fकरोमुख्य_isa_driver = अणु
	.match		= fकरोमुख्य_isa_match,
	.हटाओ		= fकरोमुख्य_isa_हटाओ,
	.driver = अणु
		.name	= "fdomain_isa",
		.pm	= FDOMAIN_PM_OPS,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init fकरोमुख्य_isa_init(व्योम)
अणु
	पूर्णांक isa_probe_count = ADDRESS_COUNT + PORT_COUNT;

	अगर (io[0]) अणु	/* use module parameters अगर present */
		fकरोमुख्य_isa_driver.match = fकरोमुख्य_isa_param_match;
		isa_probe_count = MAXBOARDS_PARAM;
	पूर्ण

	वापस isa_रेजिस्टर_driver(&fकरोमुख्य_isa_driver, isa_probe_count);
पूर्ण

अटल व्योम __निकास fकरोमुख्य_isa_निकास(व्योम)
अणु
	isa_unरेजिस्टर_driver(&fकरोमुख्य_isa_driver);
पूर्ण

module_init(fकरोमुख्य_isa_init);
module_निकास(fकरोमुख्य_isa_निकास);

MODULE_AUTHOR("Ondrej Zary, Rickard E. Faith");
MODULE_DESCRIPTION("Future Domain TMC-16x0 ISA SCSI driver");
MODULE_LICENSE("GPL");
