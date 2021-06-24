<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
** hppb.c:
**      HP-PB bus driver क्रम the NOVA and K-Class प्रणालीs.
**
**      (c) Copyright 2002 Ryan Bradetich
**      (c) Copyright 2002 Hewlett-Packard Company
**
**
*/

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/parisc-device.h>

#समावेश "iommu.h"

काष्ठा hppb_card अणु
	अचिन्हित दीर्घ hpa;
	काष्ठा resource mmio_region;
	काष्ठा hppb_card *next;
पूर्ण;

अटल काष्ठा hppb_card hppb_card_head = अणु
	.hpa = 0,
	.next = शून्य,
पूर्ण;

#घोषणा IO_IO_LOW  दुरत्व(काष्ठा bc_module, io_io_low)
#घोषणा IO_IO_HIGH दुरत्व(काष्ठा bc_module, io_io_high)

/**
 * hppb_probe - Determine अगर the hppb driver should claim this device.
 * @dev: The device which has been found
 *
 * Determine अगर hppb driver should claim this chip (वापस 0) or not 
 * (वापस 1). If so, initialize the chip and tell other partners in crime 
 * they have work to करो.
 */
अटल पूर्णांक __init hppb_probe(काष्ठा parisc_device *dev)
अणु
	पूर्णांक status;
	काष्ठा hppb_card *card = &hppb_card_head;

	जबतक(card->next) अणु
		card = card->next;
	पूर्ण

	अगर(card->hpa) अणु
		card->next = kzalloc(माप(काष्ठा hppb_card), GFP_KERNEL);
		अगर(!card->next) अणु
			prपूर्णांकk(KERN_ERR "HP-PB: Unable to allocate memory.\n");
			वापस 1;
		पूर्ण
		card = card->next;
	पूर्ण

	card->hpa = dev->hpa.start;
	card->mmio_region.name = "HP-PB Bus";
	card->mmio_region.flags = IORESOURCE_MEM;

	card->mmio_region.start = gsc_पढ़ोl(dev->hpa.start + IO_IO_LOW);
	card->mmio_region.end = gsc_पढ़ोl(dev->hpa.start + IO_IO_HIGH) - 1;

	status = ccio_request_resource(dev, &card->mmio_region);

	pr_info("Found GeckoBoa at %pap, bus space %pR,%s claimed.\n",
			&dev->hpa.start,
			&card->mmio_region,
			(status < 0) ? " not":"" );

        वापस 0;
पूर्ण

अटल स्थिर काष्ठा parisc_device_id hppb_tbl[] __initस्थिर = अणु
        अणु HPHW_BCPORT, HVERSION_REV_ANY_ID, 0x500, 0xc पूर्ण, /* E25 and K */
        अणु HPHW_BCPORT, 0x0, 0x501, 0xc पूर्ण, /* E35 */
        अणु HPHW_BCPORT, 0x0, 0x502, 0xc पूर्ण, /* E45 */
        अणु HPHW_BCPORT, 0x0, 0x503, 0xc पूर्ण, /* E55 */
        अणु 0, पूर्ण
पूर्ण;

अटल काष्ठा parisc_driver hppb_driver __refdata = अणु
        .name =         "gecko_boa",
        .id_table =     hppb_tbl,
	.probe =        hppb_probe,
पूर्ण;

/**
 * hppb_init - HP-PB bus initialization procedure.
 *
 * Register this driver.   
 */
व्योम __init hppb_init(व्योम)
अणु
        रेजिस्टर_parisc_driver(&hppb_driver);
पूर्ण
