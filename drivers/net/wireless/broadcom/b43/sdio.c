<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom B43 wireless driver
 *
 * SDIO over Sonics Silicon Backplane bus glue क्रम b43.
 *
 * Copyright (C) 2009 Albert Herranz
 * Copyright (C) 2009 Michael Buesch <m@bues.ch>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/slab.h>
#समावेश <linux/ssb/ssb.h>

#समावेश "sdio.h"
#समावेश "b43.h"


#घोषणा HNBU_CHIPID		0x01	/* venकरोr & device id */

#घोषणा B43_SDIO_BLOCK_SIZE	64	/* rx fअगरo max size in bytes */


अटल स्थिर काष्ठा b43_sdio_quirk अणु
	u16 venकरोr;
	u16 device;
	अचिन्हित पूर्णांक quirks;
पूर्ण b43_sdio_quirks[] = अणु
	अणु 0x14E4, 0x4318, SSB_QUIRK_SDIO_READ_AFTER_WRITE32, पूर्ण,
	अणु पूर्ण,
पूर्ण;


अटल अचिन्हित पूर्णांक b43_sdio_get_quirks(u16 venकरोr, u16 device)
अणु
	स्थिर काष्ठा b43_sdio_quirk *q;

	क्रम (q = b43_sdio_quirks; q->quirks; q++) अणु
		अगर (venकरोr == q->venकरोr && device == q->device)
			वापस q->quirks;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम b43_sdio_पूर्णांकerrupt_dispatcher(काष्ठा sdio_func *func)
अणु
	काष्ठा b43_sdio *sdio = sdio_get_drvdata(func);
	काष्ठा b43_wldev *dev = sdio->irq_handler_opaque;

	अगर (unlikely(b43_status(dev) < B43_STAT_STARTED))
		वापस;

	sdio_release_host(func);
	sdio->irq_handler(dev);
	sdio_claim_host(func);
पूर्ण

पूर्णांक b43_sdio_request_irq(काष्ठा b43_wldev *dev,
			 व्योम (*handler)(काष्ठा b43_wldev *dev))
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	काष्ठा sdio_func *func = bus->host_sdio;
	काष्ठा b43_sdio *sdio = sdio_get_drvdata(func);
	पूर्णांक err;

	sdio->irq_handler_opaque = dev;
	sdio->irq_handler = handler;
	sdio_claim_host(func);
	err = sdio_claim_irq(func, b43_sdio_पूर्णांकerrupt_dispatcher);
	sdio_release_host(func);

	वापस err;
पूर्ण

व्योम b43_sdio_मुक्त_irq(काष्ठा b43_wldev *dev)
अणु
	काष्ठा ssb_bus *bus = dev->dev->sdev->bus;
	काष्ठा sdio_func *func = bus->host_sdio;
	काष्ठा b43_sdio *sdio = sdio_get_drvdata(func);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_release_host(func);
	sdio->irq_handler_opaque = शून्य;
	sdio->irq_handler = शून्य;
पूर्ण

अटल पूर्णांक b43_sdio_probe(काष्ठा sdio_func *func,
				    स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा b43_sdio *sdio;
	काष्ठा sdio_func_tuple *tuple;
	u16 venकरोr = 0, device = 0;
	पूर्णांक error;

	/* Look क्रम the card chip identअगरier. */
	tuple = func->tuples;
	जबतक (tuple) अणु
		चयन (tuple->code) अणु
		हाल 0x80:
			चयन (tuple->data[0]) अणु
			हाल HNBU_CHIPID:
				अगर (tuple->size != 5)
					अवरोध;
				venकरोr = tuple->data[1] | (tuple->data[2]<<8);
				device = tuple->data[3] | (tuple->data[4]<<8);
				dev_info(&func->dev, "Chip ID %04x:%04x\n",
					 venकरोr, device);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		tuple = tuple->next;
	पूर्ण
	अगर (!venकरोr || !device) अणु
		error = -ENODEV;
		जाओ out;
	पूर्ण

	sdio_claim_host(func);
	error = sdio_set_block_size(func, B43_SDIO_BLOCK_SIZE);
	अगर (error) अणु
		dev_err(&func->dev, "failed to set block size to %u bytes,"
			" error %d\n", B43_SDIO_BLOCK_SIZE, error);
		जाओ err_release_host;
	पूर्ण
	error = sdio_enable_func(func);
	अगर (error) अणु
		dev_err(&func->dev, "failed to enable func, error %d\n", error);
		जाओ err_release_host;
	पूर्ण
	sdio_release_host(func);

	sdio = kzalloc(माप(*sdio), GFP_KERNEL);
	अगर (!sdio) अणु
		error = -ENOMEM;
		dev_err(&func->dev, "failed to allocate ssb bus\n");
		जाओ err_disable_func;
	पूर्ण
	error = ssb_bus_sdiobus_रेजिस्टर(&sdio->ssb, func,
					 b43_sdio_get_quirks(venकरोr, device));
	अगर (error) अणु
		dev_err(&func->dev, "failed to register ssb sdio bus,"
			" error %d\n", error);
		जाओ err_मुक्त_ssb;
	पूर्ण
	sdio_set_drvdata(func, sdio);

	वापस 0;

err_मुक्त_ssb:
	kमुक्त(sdio);
err_disable_func:
	sdio_claim_host(func);
	sdio_disable_func(func);
err_release_host:
	sdio_release_host(func);
out:
	वापस error;
पूर्ण

अटल व्योम b43_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा b43_sdio *sdio = sdio_get_drvdata(func);

	ssb_bus_unरेजिस्टर(&sdio->ssb);
	sdio_claim_host(func);
	sdio_disable_func(func);
	sdio_release_host(func);
	kमुक्त(sdio);
	sdio_set_drvdata(func, शून्य);
पूर्ण

अटल स्थिर काष्ठा sdio_device_id b43_sdio_ids[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_BROADCOM, SDIO_DEVICE_ID_BROADCOM_NINTENDO_WII) पूर्ण,
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_CGUYS, SDIO_DEVICE_ID_CGUYS_EW_CG1102GC) पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा sdio_driver b43_sdio_driver = अणु
	.name		= "b43-sdio",
	.id_table	= b43_sdio_ids,
	.probe		= b43_sdio_probe,
	.हटाओ		= b43_sdio_हटाओ,
पूर्ण;

पूर्णांक b43_sdio_init(व्योम)
अणु
	वापस sdio_रेजिस्टर_driver(&b43_sdio_driver);
पूर्ण

व्योम b43_sdio_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&b43_sdio_driver);
पूर्ण
