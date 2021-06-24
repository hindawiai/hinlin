<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * FireDTV driver -- firewire I/O backend
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/firewire.h>
#समावेश <linux/firewire-स्थिरants.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>

#समावेश <यंत्र/page.h>

#समावेश <media/dvb_demux.h>

#समावेश "firedtv.h"

अटल LIST_HEAD(node_list);
अटल DEFINE_SPINLOCK(node_list_lock);

अटल अंतरभूत काष्ठा fw_device *device_of(काष्ठा firedtv *fdtv)
अणु
	वापस fw_device(fdtv->device->parent);
पूर्ण

अटल पूर्णांक node_req(काष्ठा firedtv *fdtv, u64 addr, व्योम *data, माप_प्रकार len,
		    पूर्णांक tcode)
अणु
	काष्ठा fw_device *device = device_of(fdtv);
	पूर्णांक rcode, generation = device->generation;

	smp_rmb(); /* node_id vs. generation */

	rcode = fw_run_transaction(device->card, tcode, device->node_id,
			generation, device->max_speed, addr, data, len);

	वापस rcode != RCODE_COMPLETE ? -EIO : 0;
पूर्ण

पूर्णांक fdtv_lock(काष्ठा firedtv *fdtv, u64 addr, व्योम *data)
अणु
	वापस node_req(fdtv, addr, data, 8, TCODE_LOCK_COMPARE_SWAP);
पूर्ण

पूर्णांक fdtv_पढ़ो(काष्ठा firedtv *fdtv, u64 addr, व्योम *data)
अणु
	वापस node_req(fdtv, addr, data, 4, TCODE_READ_QUADLET_REQUEST);
पूर्ण

पूर्णांक fdtv_ग_लिखो(काष्ठा firedtv *fdtv, u64 addr, व्योम *data, माप_प्रकार len)
अणु
	वापस node_req(fdtv, addr, data, len, TCODE_WRITE_BLOCK_REQUEST);
पूर्ण

#घोषणा ISO_HEADER_SIZE			4
#घोषणा CIP_HEADER_SIZE			8
#घोषणा MPEG2_TS_HEADER_SIZE		4
#घोषणा MPEG2_TS_SOURCE_PACKET_SIZE	(4 + 188)

#घोषणा MAX_PACKET_SIZE		1024  /* 776, rounded up to 2^n */
#घोषणा PACKETS_PER_PAGE	(PAGE_SIZE / MAX_PACKET_SIZE)
#घोषणा N_PACKETS		64    /* buffer size */
#घोषणा N_PAGES			DIV_ROUND_UP(N_PACKETS, PACKETS_PER_PAGE)
#घोषणा IRQ_INTERVAL		16

काष्ठा fdtv_ir_context अणु
	काष्ठा fw_iso_context *context;
	काष्ठा fw_iso_buffer buffer;
	पूर्णांक पूर्णांकerrupt_packet;
	पूर्णांक current_packet;
	अक्षर *pages[N_PAGES];
पूर्ण;

अटल पूर्णांक queue_iso(काष्ठा fdtv_ir_context *ctx, पूर्णांक index)
अणु
	काष्ठा fw_iso_packet p;

	p.payload_length = MAX_PACKET_SIZE;
	p.पूर्णांकerrupt = !(++ctx->पूर्णांकerrupt_packet & (IRQ_INTERVAL - 1));
	p.skip = 0;
	p.header_length = ISO_HEADER_SIZE;

	वापस fw_iso_context_queue(ctx->context, &p, &ctx->buffer,
				    index * MAX_PACKET_SIZE);
पूर्ण

अटल व्योम handle_iso(काष्ठा fw_iso_context *context, u32 cycle,
		       माप_प्रकार header_length, व्योम *header, व्योम *data)
अणु
	काष्ठा firedtv *fdtv = data;
	काष्ठा fdtv_ir_context *ctx = fdtv->ir_context;
	__be32 *h, *h_end;
	पूर्णांक length, err, i = ctx->current_packet;
	अक्षर *p, *p_end;

	क्रम (h = header, h_end = h + header_length / 4; h < h_end; h++) अणु
		length = be32_to_cpup(h) >> 16;
		अगर (unlikely(length > MAX_PACKET_SIZE)) अणु
			dev_err(fdtv->device, "length = %d\n", length);
			length = MAX_PACKET_SIZE;
		पूर्ण

		p = ctx->pages[i / PACKETS_PER_PAGE]
				+ (i % PACKETS_PER_PAGE) * MAX_PACKET_SIZE;
		p_end = p + length;

		क्रम (p += CIP_HEADER_SIZE + MPEG2_TS_HEADER_SIZE; p < p_end;
		     p += MPEG2_TS_SOURCE_PACKET_SIZE)
			dvb_dmx_swfilter_packets(&fdtv->demux, p, 1);

		err = queue_iso(ctx, i);
		अगर (unlikely(err))
			dev_err(fdtv->device, "requeue failed\n");

		i = (i + 1) & (N_PACKETS - 1);
	पूर्ण
	fw_iso_context_queue_flush(ctx->context);
	ctx->current_packet = i;
पूर्ण

पूर्णांक fdtv_start_iso(काष्ठा firedtv *fdtv)
अणु
	काष्ठा fdtv_ir_context *ctx;
	काष्ठा fw_device *device = device_of(fdtv);
	पूर्णांक i, err;

	ctx = kदो_स्मृति(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->context = fw_iso_context_create(device->card,
			FW_ISO_CONTEXT_RECEIVE, fdtv->isochannel,
			device->max_speed, ISO_HEADER_SIZE, handle_iso, fdtv);
	अगर (IS_ERR(ctx->context)) अणु
		err = PTR_ERR(ctx->context);
		जाओ fail_मुक्त;
	पूर्ण

	err = fw_iso_buffer_init(&ctx->buffer, device->card,
				 N_PAGES, DMA_FROM_DEVICE);
	अगर (err)
		जाओ fail_context_destroy;

	ctx->पूर्णांकerrupt_packet = 0;
	ctx->current_packet = 0;

	क्रम (i = 0; i < N_PAGES; i++)
		ctx->pages[i] = page_address(ctx->buffer.pages[i]);

	क्रम (i = 0; i < N_PACKETS; i++) अणु
		err = queue_iso(ctx, i);
		अगर (err)
			जाओ fail;
	पूर्ण

	err = fw_iso_context_start(ctx->context, -1, 0,
				   FW_ISO_CONTEXT_MATCH_ALL_TAGS);
	अगर (err)
		जाओ fail;

	fdtv->ir_context = ctx;

	वापस 0;
fail:
	fw_iso_buffer_destroy(&ctx->buffer, device->card);
fail_context_destroy:
	fw_iso_context_destroy(ctx->context);
fail_मुक्त:
	kमुक्त(ctx);

	वापस err;
पूर्ण

व्योम fdtv_stop_iso(काष्ठा firedtv *fdtv)
अणु
	काष्ठा fdtv_ir_context *ctx = fdtv->ir_context;

	fw_iso_context_stop(ctx->context);
	fw_iso_buffer_destroy(&ctx->buffer, device_of(fdtv)->card);
	fw_iso_context_destroy(ctx->context);
	kमुक्त(ctx);
पूर्ण

अटल व्योम handle_fcp(काष्ठा fw_card *card, काष्ठा fw_request *request,
		       पूर्णांक tcode, पूर्णांक destination, पूर्णांक source, पूर्णांक generation,
		       अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		       व्योम *callback_data)
अणु
	काष्ठा firedtv *f, *fdtv = शून्य;
	काष्ठा fw_device *device;
	अचिन्हित दीर्घ flags;
	पूर्णांक su;

	अगर (length < 2 || (((u8 *)payload)[0] & 0xf0) != 0)
		वापस;

	su = ((u8 *)payload)[1] & 0x7;

	spin_lock_irqsave(&node_list_lock, flags);
	list_क्रम_each_entry(f, &node_list, list) अणु
		device = device_of(f);
		अगर (device->generation != generation)
			जारी;

		smp_rmb(); /* node_id vs. generation */

		अगर (device->card == card &&
		    device->node_id == source &&
		    (f->subunit == su || (f->subunit == 0 && su == 0x7))) अणु
			fdtv = f;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&node_list_lock, flags);

	अगर (fdtv)
		avc_recv(fdtv, payload, length);
पूर्ण

अटल काष्ठा fw_address_handler fcp_handler = अणु
	.length           = CSR_FCP_END - CSR_FCP_RESPONSE,
	.address_callback = handle_fcp,
पूर्ण;

अटल स्थिर काष्ठा fw_address_region fcp_region = अणु
	.start	= CSR_REGISTER_BASE + CSR_FCP_RESPONSE,
	.end	= CSR_REGISTER_BASE + CSR_FCP_END,
पूर्ण;

अटल स्थिर अक्षर * स्थिर model_names[] = अणु
	[FIREDTV_UNKNOWN] = "unknown type",
	[FIREDTV_DVB_S]   = "FireDTV S/CI",
	[FIREDTV_DVB_C]   = "FireDTV C/CI",
	[FIREDTV_DVB_T]   = "FireDTV T/CI",
	[FIREDTV_DVB_S2]  = "FireDTV S2  ",
पूर्ण;

/* Adjust the ढाँचा string अगर models with दीर्घer names appear. */
#घोषणा MAX_MODEL_NAME_LEN माप("FireDTV ????")

अटल पूर्णांक node_probe(काष्ठा fw_unit *unit, स्थिर काष्ठा ieee1394_device_id *id)
अणु
	काष्ठा firedtv *fdtv;
	अक्षर name[MAX_MODEL_NAME_LEN];
	पूर्णांक name_len, i, err;

	fdtv = kzalloc(माप(*fdtv), GFP_KERNEL);
	अगर (!fdtv)
		वापस -ENOMEM;

	dev_set_drvdata(&unit->device, fdtv);
	fdtv->device		= &unit->device;
	fdtv->isochannel	= -1;
	fdtv->voltage		= 0xff;
	fdtv->tone		= 0xff;

	mutex_init(&fdtv->avc_mutex);
	init_रुकोqueue_head(&fdtv->avc_रुको);
	mutex_init(&fdtv->demux_mutex);
	INIT_WORK(&fdtv->remote_ctrl_work, avc_remote_ctrl_work);

	name_len = fw_csr_string(unit->directory, CSR_MODEL,
				 name, माप(name));
	अगर (name_len < 0) अणु
		err = name_len;
		जाओ fail_मुक्त;
	पूर्ण
	क्रम (i = ARRAY_SIZE(model_names); --i; )
		अगर (म_माप(model_names[i]) <= name_len &&
		    म_भेदन(name, model_names[i], name_len) == 0)
			अवरोध;
	fdtv->type = i;

	err = fdtv_रेजिस्टर_rc(fdtv, &unit->device);
	अगर (err)
		जाओ fail_मुक्त;

	spin_lock_irq(&node_list_lock);
	list_add_tail(&fdtv->list, &node_list);
	spin_unlock_irq(&node_list_lock);

	err = avc_identअगरy_subunit(fdtv);
	अगर (err)
		जाओ fail;

	err = fdtv_dvb_रेजिस्टर(fdtv, model_names[fdtv->type]);
	अगर (err)
		जाओ fail;

	avc_रेजिस्टर_remote_control(fdtv);

	वापस 0;
fail:
	spin_lock_irq(&node_list_lock);
	list_del(&fdtv->list);
	spin_unlock_irq(&node_list_lock);
	fdtv_unरेजिस्टर_rc(fdtv);
fail_मुक्त:
	kमुक्त(fdtv);

	वापस err;
पूर्ण

अटल व्योम node_हटाओ(काष्ठा fw_unit *unit)
अणु
	काष्ठा firedtv *fdtv = dev_get_drvdata(&unit->device);

	fdtv_dvb_unरेजिस्टर(fdtv);

	spin_lock_irq(&node_list_lock);
	list_del(&fdtv->list);
	spin_unlock_irq(&node_list_lock);

	fdtv_unरेजिस्टर_rc(fdtv);

	kमुक्त(fdtv);
पूर्ण

अटल व्योम node_update(काष्ठा fw_unit *unit)
अणु
	काष्ठा firedtv *fdtv = dev_get_drvdata(&unit->device);

	अगर (fdtv->isochannel >= 0)
		cmp_establish_pp_connection(fdtv, fdtv->subunit,
					    fdtv->isochannel);
पूर्ण

#घोषणा MATCH_FLAGS (IEEE1394_MATCH_VENDOR_ID | IEEE1394_MATCH_MODEL_ID | \
		     IEEE1394_MATCH_SPECIFIER_ID | IEEE1394_MATCH_VERSION)

#घोषणा DIGITAL_EVERYWHERE_OUI	0x001287
#घोषणा AVC_UNIT_SPEC_ID_ENTRY	0x00a02d
#घोषणा AVC_SW_VERSION_ENTRY	0x010001

अटल स्थिर काष्ठा ieee1394_device_id fdtv_id_table[] = अणु
	अणु
		/* FloppyDTV S/CI and FloppyDTV S2 */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000024,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणु
		/* FloppyDTV T/CI */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000025,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणु
		/* FloppyDTV C/CI */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000026,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणु
		/* FireDTV S/CI and FloppyDTV S2 */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000034,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणु
		/* FireDTV T/CI */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000035,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणु
		/* FireDTV C/CI */
		.match_flags	= MATCH_FLAGS,
		.venकरोr_id	= DIGITAL_EVERYWHERE_OUI,
		.model_id	= 0x000036,
		.specअगरier_id	= AVC_UNIT_SPEC_ID_ENTRY,
		.version	= AVC_SW_VERSION_ENTRY,
	पूर्ण, अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(ieee1394, fdtv_id_table);

अटल काष्ठा fw_driver fdtv_driver = अणु
	.driver   = अणु
		.owner  = THIS_MODULE,
		.name   = "firedtv",
		.bus    = &fw_bus_type,
	पूर्ण,
	.probe    = node_probe,
	.update   = node_update,
	.हटाओ   = node_हटाओ,
	.id_table = fdtv_id_table,
पूर्ण;

अटल पूर्णांक __init fdtv_init(व्योम)
अणु
	पूर्णांक ret;

	ret = fw_core_add_address_handler(&fcp_handler, &fcp_region);
	अगर (ret < 0)
		वापस ret;

	ret = driver_रेजिस्टर(&fdtv_driver.driver);
	अगर (ret < 0)
		fw_core_हटाओ_address_handler(&fcp_handler);

	वापस ret;
पूर्ण

अटल व्योम __निकास fdtv_निकास(व्योम)
अणु
	driver_unरेजिस्टर(&fdtv_driver.driver);
	fw_core_हटाओ_address_handler(&fcp_handler);
पूर्ण

module_init(fdtv_init);
module_निकास(fdtv_निकास);

MODULE_AUTHOR("Andreas Monitzer <andy@monitzer.com>");
MODULE_AUTHOR("Ben Backx <ben@bbackx.com>");
MODULE_DESCRIPTION("FireDTV DVB Driver");
MODULE_LICENSE("GPL");
