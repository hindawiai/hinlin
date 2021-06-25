<शैली गुरु>
/*
 * Linux driver attachment glue क्रम aic7770 based controllers.
 *
 * Copyright (c) 2000-2003 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7770_osm.c#14 $
 */

#समावेश "aic7xxx_osm.h"

#समावेश <linux/device.h>
#समावेश <linux/eisa.h>

पूर्णांक
aic7770_map_रेजिस्टरs(काष्ठा ahc_softc *ahc, u_पूर्णांक port)
अणु
	/*
	 * Lock out other contenders क्रम our i/o space.
	 */
	अगर (!request_region(port, AHC_EISA_IOSIZE, "aic7xxx"))
		वापस (ENOMEM);
	ahc->tag = BUS_SPACE_PIO;
	ahc->bsh.ioport = port;
	वापस (0);
पूर्ण

पूर्णांक
aic7770_map_पूर्णांक(काष्ठा ahc_softc *ahc, u_पूर्णांक irq)
अणु
	पूर्णांक error;
	पूर्णांक shared;

	shared = 0;
	अगर ((ahc->flags & AHC_EDGE_INTERRUPT) == 0)
		shared = IRQF_SHARED;

	error = request_irq(irq, ahc_linux_isr, shared, "aic7xxx", ahc);
	अगर (error == 0)
		ahc->platक्रमm_data->irq = irq;
	
	वापस (-error);
पूर्ण

अटल पूर्णांक
aic7770_probe(काष्ठा device *dev)
अणु
	काष्ठा eisa_device *edev = to_eisa_device(dev);
	u_पूर्णांक eisaBase = edev->base_addr+AHC_EISA_SLOT_OFFSET;
	काष्ठा	ahc_softc *ahc;
	अक्षर	buf[80];
	अक्षर   *name;
	पूर्णांक	error;

	प्र_लिखो(buf, "ahc_eisa:%d", eisaBase >> 12);
	name = kstrdup(buf, GFP_ATOMIC);
	अगर (name == शून्य)
		वापस (ENOMEM);
	ahc = ahc_alloc(&aic7xxx_driver_ढाँचा, name);
	अगर (ahc == शून्य)
		वापस (ENOMEM);
	ahc->dev = dev;
	error = aic7770_config(ahc, aic7770_ident_table + edev->id.driver_data,
			       eisaBase);
	अगर (error != 0) अणु
		ahc->bsh.ioport = 0;
		ahc_मुक्त(ahc);
		वापस (error);
	पूर्ण

 	dev_set_drvdata(dev, ahc);

	error = ahc_linux_रेजिस्टर_host(ahc, &aic7xxx_driver_ढाँचा);
	वापस (error);
पूर्ण

अटल पूर्णांक
aic7770_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा ahc_softc *ahc = dev_get_drvdata(dev);
	u_दीर्घ s;

	अगर (ahc->platक्रमm_data && ahc->platक्रमm_data->host)
			scsi_हटाओ_host(ahc->platक्रमm_data->host);

	ahc_lock(ahc, &s);
	ahc_पूर्णांकr_enable(ahc, FALSE);
	ahc_unlock(ahc, &s);

	ahc_मुक्त(ahc);
	वापस 0;
पूर्ण
 
अटल काष्ठा eisa_device_id aic7770_ids[] = अणु
	अणु "ADP7771", 0 पूर्ण, /* AHA 274x */
	अणु "ADP7756", 1 पूर्ण, /* AHA 284x BIOS enabled */
	अणु "ADP7757", 2 पूर्ण, /* AHA 284x BIOS disabled */
	अणु "ADP7782", 3 पूर्ण, /* AHA 274x Olivetti OEM */
	अणु "ADP7783", 4 पूर्ण, /* AHA 274x Olivetti OEM (Dअगरferential) */
	अणु "ADP7770", 5 पूर्ण, /* AIC7770 generic */
	अणु "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(eisa, aic7770_ids);

अटल काष्ठा eisa_driver aic7770_driver = अणु
	.id_table	= aic7770_ids,
	.driver = अणु
		.name   = "aic7xxx",
		.probe  = aic7770_probe,
		.हटाओ = aic7770_हटाओ,
	पूर्ण
पूर्ण;
  
पूर्णांक
ahc_linux_eisa_init(व्योम)
अणु
	वापस eisa_driver_रेजिस्टर(&aic7770_driver);
पूर्ण
  
व्योम
ahc_linux_eisa_निकास(व्योम)
अणु
	eisa_driver_unरेजिस्टर(&aic7770_driver);
पूर्ण
