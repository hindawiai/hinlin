<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  smssdio.c - Siano 1xxx SDIO पूर्णांकerface driver
 *
 *  Copyright 2008 Pierre Ossman
 *
 * Based on code by Siano Mobile Silicon, Inc.,
 * Copyright (C) 2006-2008, Uri Shkolnik
 *
 * This hardware is a bit odd in that all transfers should be करोne
 * to/from the SMSSDIO_DATA रेजिस्टर, yet the "increase address" bit
 * always needs to be set.
 *
 * Also, buffers from the card are always aligned to 128 byte
 * boundaries.
 */

/*
 * General cleanup notes:
 *
 * - only प्रकारs should be name *_t
 *
 * - use ERR_PTR and मित्रs क्रम smscore_रेजिस्टर_device()
 *
 * - smscore_getbuffer should zero fields
 *
 * Fix stop command
 */

#समावेश "smscoreapi.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/module.h>

#समावेश "sms-cards.h"
#समावेश "smsendian.h"

/* Registers */

#घोषणा SMSSDIO_DATA		0x00
#घोषणा SMSSDIO_INT		0x04
#घोषणा SMSSDIO_BLOCK_SIZE	128

अटल स्थिर काष्ठा sdio_device_id smssdio_ids[] = अणु
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_STELLAR),
	 .driver_data = SMS1XXX_BOARD_SIANO_STELLARपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_NOVA_A0),
	 .driver_data = SMS1XXX_BOARD_SIANO_NOVA_Aपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_NOVA_B0),
	 .driver_data = SMS1XXX_BOARD_SIANO_NOVA_Bपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_VEGA_A0),
	 .driver_data = SMS1XXX_BOARD_SIANO_VEGAपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_VENICE),
	 .driver_data = SMS1XXX_BOARD_SIANO_VEGAपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_MING),
	.driver_data = SMS1XXX_BOARD_SIANO_MINGपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_PELE),
	.driver_data = SMS1XXX_BOARD_SIANO_PELEपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_RIO),
	.driver_data = SMS1XXX_BOARD_SIANO_RIOपूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_DENVER_2160),
	.driver_data = SMS1XXX_BOARD_SIANO_DENVER_2160पूर्ण,
	अणुSDIO_DEVICE(SDIO_VENDOR_ID_SIANO, SDIO_DEVICE_ID_SIANO_DENVER_1530),
	.driver_data = SMS1XXX_BOARD_SIANO_DENVER_1530पूर्ण,
	अणु /* end: all zeroes */ पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(sdio, smssdio_ids);

काष्ठा smssdio_device अणु
	काष्ठा sdio_func *func;

	काष्ठा smscore_device_t *coredev;

	काष्ठा smscore_buffer_t *split_cb;
पूर्ण;

/*******************************************************************/
/* Siano core callbacks                                            */
/*******************************************************************/

अटल पूर्णांक smssdio_sendrequest(व्योम *context, व्योम *buffer, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	काष्ठा smssdio_device *smsdev;

	smsdev = context;

	sdio_claim_host(smsdev->func);

	smsendian_handle_tx_message((काष्ठा sms_msg_data *) buffer);
	जबतक (size >= smsdev->func->cur_blksize) अणु
		ret = sdio_स_नकल_toio(smsdev->func, SMSSDIO_DATA,
					buffer, smsdev->func->cur_blksize);
		अगर (ret)
			जाओ out;

		buffer += smsdev->func->cur_blksize;
		size -= smsdev->func->cur_blksize;
	पूर्ण

	अगर (size) अणु
		ret = sdio_स_नकल_toio(smsdev->func, SMSSDIO_DATA,
					buffer, size);
	पूर्ण

out:
	sdio_release_host(smsdev->func);

	वापस ret;
पूर्ण

/*******************************************************************/
/* SDIO callbacks                                                  */
/*******************************************************************/

अटल व्योम smssdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;

	काष्ठा smssdio_device *smsdev;
	काष्ठा smscore_buffer_t *cb;
	काष्ठा sms_msg_hdr *hdr;
	माप_प्रकार size;

	smsdev = sdio_get_drvdata(func);

	/*
	 * The पूर्णांकerrupt रेजिस्टर has no defined meaning. It is just
	 * a way of turning of the level triggered पूर्णांकerrupt.
	 */
	(व्योम)sdio_पढ़ोb(func, SMSSDIO_INT, &ret);
	अगर (ret) अणु
		pr_err("Unable to read interrupt register!\n");
		वापस;
	पूर्ण

	अगर (smsdev->split_cb == शून्य) अणु
		cb = smscore_getbuffer(smsdev->coredev);
		अगर (!cb) अणु
			pr_err("Unable to allocate data buffer!\n");
			वापस;
		पूर्ण

		ret = sdio_स_नकल_fromio(smsdev->func,
					 cb->p,
					 SMSSDIO_DATA,
					 SMSSDIO_BLOCK_SIZE);
		अगर (ret) अणु
			pr_err("Error %d reading initial block!\n", ret);
			वापस;
		पूर्ण

		hdr = cb->p;

		अगर (hdr->msg_flags & MSG_HDR_FLAG_SPLIT_MSG) अणु
			smsdev->split_cb = cb;
			वापस;
		पूर्ण

		अगर (hdr->msg_length > smsdev->func->cur_blksize)
			size = hdr->msg_length - smsdev->func->cur_blksize;
		अन्यथा
			size = 0;
	पूर्ण अन्यथा अणु
		cb = smsdev->split_cb;
		hdr = cb->p;

		size = hdr->msg_length - माप(काष्ठा sms_msg_hdr);

		smsdev->split_cb = शून्य;
	पूर्ण

	अगर (size) अणु
		व्योम *buffer;

		buffer = cb->p + (hdr->msg_length - size);
		size = ALIGN(size, SMSSDIO_BLOCK_SIZE);

		BUG_ON(smsdev->func->cur_blksize != SMSSDIO_BLOCK_SIZE);

		/*
		 * First attempt to transfer all of it in one go...
		 */
		ret = sdio_स_नकल_fromio(smsdev->func,
					 buffer,
					 SMSSDIO_DATA,
					 size);
		अगर (ret && ret != -EINVAL) अणु
			smscore_putbuffer(smsdev->coredev, cb);
			pr_err("Error %d reading data from card!\n", ret);
			वापस;
		पूर्ण

		/*
		 * ..then fall back to one block at a समय अगर that is
		 * not possible...
		 *
		 * (we have to करो this manually because of the
		 * problem with the "increase address" bit)
		 */
		अगर (ret == -EINVAL) अणु
			जबतक (size) अणु
				ret = sdio_स_नकल_fromio(smsdev->func,
						  buffer, SMSSDIO_DATA,
						  smsdev->func->cur_blksize);
				अगर (ret) अणु
					smscore_putbuffer(smsdev->coredev, cb);
					pr_err("Error %d reading data from card!\n",
					       ret);
					वापस;
				पूर्ण

				buffer += smsdev->func->cur_blksize;
				अगर (size > smsdev->func->cur_blksize)
					size -= smsdev->func->cur_blksize;
				अन्यथा
					size = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	cb->size = hdr->msg_length;
	cb->offset = 0;

	smsendian_handle_rx_message((काष्ठा sms_msg_data *) cb->p);
	smscore_onresponse(smsdev->coredev, cb);
पूर्ण

अटल पूर्णांक smssdio_probe(काष्ठा sdio_func *func,
			 स्थिर काष्ठा sdio_device_id *id)
अणु
	पूर्णांक ret;

	पूर्णांक board_id;
	काष्ठा smssdio_device *smsdev;
	काष्ठा smsdevice_params_t params;

	board_id = id->driver_data;

	smsdev = kzalloc(माप(काष्ठा smssdio_device), GFP_KERNEL);
	अगर (!smsdev)
		वापस -ENOMEM;

	smsdev->func = func;

	स_रखो(&params, 0, माप(काष्ठा smsdevice_params_t));

	params.device = &func->dev;
	params.buffer_size = 0x5000;	/* ?? */
	params.num_buffers = 22;	/* ?? */
	params.context = smsdev;

	snम_लिखो(params.devpath, माप(params.devpath),
		 "sdio\\%s", sdio_func_id(func));

	params.sendrequest_handler = smssdio_sendrequest;

	params.device_type = sms_get_board(board_id)->type;

	अगर (params.device_type != SMS_STELLAR)
		params.flags |= SMS_DEVICE_FAMILY2;
	अन्यथा अणु
		/*
		 * FIXME: Stellar needs special handling...
		 */
		ret = -ENODEV;
		जाओ मुक्त;
	पूर्ण

	ret = smscore_रेजिस्टर_device(&params, &smsdev->coredev, GFP_DMA, शून्य);
	अगर (ret < 0)
		जाओ मुक्त;

	smscore_set_board_id(smsdev->coredev, board_id);

	sdio_claim_host(func);

	ret = sdio_enable_func(func);
	अगर (ret)
		जाओ release;

	ret = sdio_set_block_size(func, SMSSDIO_BLOCK_SIZE);
	अगर (ret)
		जाओ disable;

	ret = sdio_claim_irq(func, smssdio_पूर्णांकerrupt);
	अगर (ret)
		जाओ disable;

	sdio_set_drvdata(func, smsdev);

	sdio_release_host(func);

	ret = smscore_start_device(smsdev->coredev);
	अगर (ret < 0)
		जाओ reclaim;

	वापस 0;

reclaim:
	sdio_claim_host(func);
	sdio_release_irq(func);
disable:
	sdio_disable_func(func);
release:
	sdio_release_host(func);
	smscore_unरेजिस्टर_device(smsdev->coredev);
मुक्त:
	kमुक्त(smsdev);

	वापस ret;
पूर्ण

अटल व्योम smssdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा smssdio_device *smsdev;

	smsdev = sdio_get_drvdata(func);

	/* FIXME: racy! */
	अगर (smsdev->split_cb)
		smscore_putbuffer(smsdev->coredev, smsdev->split_cb);

	smscore_unरेजिस्टर_device(smsdev->coredev);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);

	kमुक्त(smsdev);
पूर्ण

अटल काष्ठा sdio_driver smssdio_driver = अणु
	.name = "smssdio",
	.id_table = smssdio_ids,
	.probe = smssdio_probe,
	.हटाओ = smssdio_हटाओ,
पूर्ण;

/*******************************************************************/
/* Module functions                                                */
/*******************************************************************/

अटल पूर्णांक __init smssdio_module_init(व्योम)
अणु
	पूर्णांक ret = 0;

	prपूर्णांकk(KERN_INFO "smssdio: Siano SMS1xxx SDIO driver\n");
	prपूर्णांकk(KERN_INFO "smssdio: Copyright Pierre Ossman\n");

	ret = sdio_रेजिस्टर_driver(&smssdio_driver);

	वापस ret;
पूर्ण

अटल व्योम __निकास smssdio_module_निकास(व्योम)
अणु
	sdio_unरेजिस्टर_driver(&smssdio_driver);
पूर्ण

module_init(smssdio_module_init);
module_निकास(smssdio_module_निकास);

MODULE_DESCRIPTION("Siano SMS1xxx SDIO driver");
MODULE_AUTHOR("Pierre Ossman");
MODULE_LICENSE("GPL");
