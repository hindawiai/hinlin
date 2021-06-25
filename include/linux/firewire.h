<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FIREWIRE_H
#घोषणा _LINUX_FIREWIRE_H

#समावेश <linux/completion.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/समयr.h>
#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/atomic.h>
#समावेश <यंत्र/byteorder.h>

#घोषणा CSR_REGISTER_BASE		0xfffff0000000ULL

/* रेजिस्टर offsets are relative to CSR_REGISTER_BASE */
#घोषणा CSR_STATE_CLEAR			0x0
#घोषणा CSR_STATE_SET			0x4
#घोषणा CSR_NODE_IDS			0x8
#घोषणा CSR_RESET_START			0xc
#घोषणा CSR_SPLIT_TIMEOUT_HI		0x18
#घोषणा CSR_SPLIT_TIMEOUT_LO		0x1c
#घोषणा CSR_CYCLE_TIME			0x200
#घोषणा CSR_BUS_TIME			0x204
#घोषणा CSR_BUSY_TIMEOUT		0x210
#घोषणा CSR_PRIORITY_BUDGET		0x218
#घोषणा CSR_BUS_MANAGER_ID		0x21c
#घोषणा CSR_BANDWIDTH_AVAILABLE		0x220
#घोषणा CSR_CHANNELS_AVAILABLE		0x224
#घोषणा CSR_CHANNELS_AVAILABLE_HI	0x224
#घोषणा CSR_CHANNELS_AVAILABLE_LO	0x228
#घोषणा CSR_MAINT_UTILITY		0x230
#घोषणा CSR_BROADCAST_CHANNEL		0x234
#घोषणा CSR_CONFIG_ROM			0x400
#घोषणा CSR_CONFIG_ROM_END		0x800
#घोषणा CSR_OMPR			0x900
#घोषणा CSR_OPCR(i)			(0x904 + (i) * 4)
#घोषणा CSR_IMPR			0x980
#घोषणा CSR_IPCR(i)			(0x984 + (i) * 4)
#घोषणा CSR_FCP_COMMAND			0xB00
#घोषणा CSR_FCP_RESPONSE		0xD00
#घोषणा CSR_FCP_END			0xF00
#घोषणा CSR_TOPOLOGY_MAP		0x1000
#घोषणा CSR_TOPOLOGY_MAP_END		0x1400
#घोषणा CSR_SPEED_MAP			0x2000
#घोषणा CSR_SPEED_MAP_END		0x3000

#घोषणा CSR_OFFSET		0x40
#घोषणा CSR_LEAF		0x80
#घोषणा CSR_सूचीECTORY		0xc0

#घोषणा CSR_DESCRIPTOR		0x01
#घोषणा CSR_VENDOR		0x03
#घोषणा CSR_HARDWARE_VERSION	0x04
#घोषणा CSR_UNIT		0x11
#घोषणा CSR_SPECIFIER_ID	0x12
#घोषणा CSR_VERSION		0x13
#घोषणा CSR_DEPENDENT_INFO	0x14
#घोषणा CSR_MODEL		0x17
#घोषणा CSR_सूचीECTORY_ID	0x20

काष्ठा fw_csr_iterator अणु
	स्थिर u32 *p;
	स्थिर u32 *end;
पूर्ण;

व्योम fw_csr_iterator_init(काष्ठा fw_csr_iterator *ci, स्थिर u32 *p);
पूर्णांक fw_csr_iterator_next(काष्ठा fw_csr_iterator *ci, पूर्णांक *key, पूर्णांक *value);
पूर्णांक fw_csr_string(स्थिर u32 *directory, पूर्णांक key, अक्षर *buf, माप_प्रकार size);

बाह्य काष्ठा bus_type fw_bus_type;

काष्ठा fw_card_driver;
काष्ठा fw_node;

काष्ठा fw_card अणु
	स्थिर काष्ठा fw_card_driver *driver;
	काष्ठा device *device;
	काष्ठा kref kref;
	काष्ठा completion करोne;

	पूर्णांक node_id;
	पूर्णांक generation;
	पूर्णांक current_tlabel;
	u64 tlabel_mask;
	काष्ठा list_head transaction_list;
	u64 reset_jअगरfies;

	u32 split_समयout_hi;
	u32 split_समयout_lo;
	अचिन्हित पूर्णांक split_समयout_cycles;
	अचिन्हित पूर्णांक split_समयout_jअगरfies;

	अचिन्हित दीर्घ दीर्घ guid;
	अचिन्हित max_receive;
	पूर्णांक link_speed;
	पूर्णांक config_rom_generation;

	spinlock_t lock; /* Take this lock when handling the lists in
			  * this काष्ठा. */
	काष्ठा fw_node *local_node;
	काष्ठा fw_node *root_node;
	काष्ठा fw_node *irm_node;
	u8 color; /* must be u8 to match the definition in काष्ठा fw_node */
	पूर्णांक gap_count;
	bool beta_repeaters_present;

	पूर्णांक index;
	काष्ठा list_head link;

	काष्ठा list_head phy_receiver_list;

	काष्ठा delayed_work br_work; /* bus reset job */
	bool br_लघु;

	काष्ठा delayed_work bm_work; /* bus manager job */
	पूर्णांक bm_retries;
	पूर्णांक bm_generation;
	पूर्णांक bm_node_id;
	bool bm_abdicate;

	bool priority_budget_implemented;	/* controller feature */
	bool broadcast_channel_स्वतः_allocated;	/* controller feature */

	bool broadcast_channel_allocated;
	u32 broadcast_channel;
	__be32 topology_map[(CSR_TOPOLOGY_MAP_END - CSR_TOPOLOGY_MAP) / 4];

	__be32 मुख्यt_utility_रेजिस्टर;
पूर्ण;

अटल अंतरभूत काष्ठा fw_card *fw_card_get(काष्ठा fw_card *card)
अणु
	kref_get(&card->kref);

	वापस card;
पूर्ण

व्योम fw_card_release(काष्ठा kref *kref);

अटल अंतरभूत व्योम fw_card_put(काष्ठा fw_card *card)
अणु
	kref_put(&card->kref, fw_card_release);
पूर्ण

काष्ठा fw_attribute_group अणु
	काष्ठा attribute_group *groups[2];
	काष्ठा attribute_group group;
	काष्ठा attribute *attrs[13];
पूर्ण;

क्रमागत fw_device_state अणु
	FW_DEVICE_INITIALIZING,
	FW_DEVICE_RUNNING,
	FW_DEVICE_GONE,
	FW_DEVICE_SHUTDOWN,
पूर्ण;

/*
 * Note, fw_device.generation always has to be पढ़ो beक्रमe fw_device.node_id.
 * Use SMP memory barriers to ensure this.  Otherwise requests will be sent
 * to an outdated node_id अगर the generation was updated in the meanसमय due
 * to a bus reset.
 *
 * Likewise, fw-core will take care to update .node_id beक्रमe .generation so
 * that whenever fw_device.generation is current WRT the actual bus generation,
 * fw_device.node_id is guaranteed to be current too.
 *
 * The same applies to fw_device.card->node_id vs. fw_device.generation.
 *
 * fw_device.config_rom and fw_device.config_rom_length may be accessed during
 * the lअगरeसमय of any fw_unit beदीर्घing to the fw_device, beक्रमe device_del()
 * was called on the last fw_unit.  Alternatively, they may be accessed जबतक
 * holding fw_device_rwsem.
 */
काष्ठा fw_device अणु
	atomic_t state;
	काष्ठा fw_node *node;
	पूर्णांक node_id;
	पूर्णांक generation;
	अचिन्हित max_speed;
	काष्ठा fw_card *card;
	काष्ठा device device;

	काष्ठा mutex client_list_mutex;
	काष्ठा list_head client_list;

	स्थिर u32 *config_rom;
	माप_प्रकार config_rom_length;
	पूर्णांक config_rom_retries;
	अचिन्हित is_local:1;
	अचिन्हित max_rec:4;
	अचिन्हित cmc:1;
	अचिन्हित irmc:1;
	अचिन्हित bc_implemented:2;

	work_func_t workfn;
	काष्ठा delayed_work work;
	काष्ठा fw_attribute_group attribute_group;
पूर्ण;

अटल अंतरभूत काष्ठा fw_device *fw_device(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा fw_device, device);
पूर्ण

अटल अंतरभूत पूर्णांक fw_device_is_shutकरोwn(काष्ठा fw_device *device)
अणु
	वापस atomic_पढ़ो(&device->state) == FW_DEVICE_SHUTDOWN;
पूर्ण

पूर्णांक fw_device_enable_phys_dma(काष्ठा fw_device *device);

/*
 * fw_unit.directory must not be accessed after device_del(&fw_unit.device).
 */
काष्ठा fw_unit अणु
	काष्ठा device device;
	स्थिर u32 *directory;
	काष्ठा fw_attribute_group attribute_group;
पूर्ण;

अटल अंतरभूत काष्ठा fw_unit *fw_unit(काष्ठा device *dev)
अणु
	वापस container_of(dev, काष्ठा fw_unit, device);
पूर्ण

अटल अंतरभूत काष्ठा fw_unit *fw_unit_get(काष्ठा fw_unit *unit)
अणु
	get_device(&unit->device);

	वापस unit;
पूर्ण

अटल अंतरभूत व्योम fw_unit_put(काष्ठा fw_unit *unit)
अणु
	put_device(&unit->device);
पूर्ण

अटल अंतरभूत काष्ठा fw_device *fw_parent_device(काष्ठा fw_unit *unit)
अणु
	वापस fw_device(unit->device.parent);
पूर्ण

काष्ठा ieee1394_device_id;

काष्ठा fw_driver अणु
	काष्ठा device_driver driver;
	पूर्णांक (*probe)(काष्ठा fw_unit *unit, स्थिर काष्ठा ieee1394_device_id *id);
	/* Called when the parent device sits through a bus reset. */
	व्योम (*update)(काष्ठा fw_unit *unit);
	व्योम (*हटाओ)(काष्ठा fw_unit *unit);
	स्थिर काष्ठा ieee1394_device_id *id_table;
पूर्ण;

काष्ठा fw_packet;
काष्ठा fw_request;

प्रकार व्योम (*fw_packet_callback_t)(काष्ठा fw_packet *packet,
				     काष्ठा fw_card *card, पूर्णांक status);
प्रकार व्योम (*fw_transaction_callback_t)(काष्ठा fw_card *card, पूर्णांक rcode,
					  व्योम *data, माप_प्रकार length,
					  व्योम *callback_data);
/*
 * This callback handles an inbound request subaction.  It is called in
 * RCU पढ़ो-side context, thereक्रमe must not sleep.
 *
 * The callback should not initiate outbound request subactions directly.
 * Otherwise there is a danger of recursion of inbound and outbound
 * transactions from and to the local node.
 *
 * The callback is responsible that either fw_send_response() or kमुक्त()
 * is called on the @request, except क्रम FCP रेजिस्टरs क्रम which the core
 * takes care of that.
 */
प्रकार व्योम (*fw_address_callback_t)(काष्ठा fw_card *card,
				      काष्ठा fw_request *request,
				      पूर्णांक tcode, पूर्णांक destination, पूर्णांक source,
				      पूर्णांक generation,
				      अचिन्हित दीर्घ दीर्घ offset,
				      व्योम *data, माप_प्रकार length,
				      व्योम *callback_data);

काष्ठा fw_packet अणु
	पूर्णांक speed;
	पूर्णांक generation;
	u32 header[4];
	माप_प्रकार header_length;
	व्योम *payload;
	माप_प्रकार payload_length;
	dma_addr_t payload_bus;
	bool payload_mapped;
	u32 बारtamp;

	/*
	 * This callback is called when the packet transmission has completed.
	 * For successful transmission, the status code is the ack received
	 * from the destination.  Otherwise it is one of the juju-specअगरic
	 * rcodes:  RCODE_SEND_ERROR, _CANCELLED, _BUSY, _GENERATION, _NO_ACK.
	 * The callback can be called from tasklet context and thus
	 * must never block.
	 */
	fw_packet_callback_t callback;
	पूर्णांक ack;
	काष्ठा list_head link;
	व्योम *driver_data;
पूर्ण;

काष्ठा fw_transaction अणु
	पूर्णांक node_id; /* The generation is implied; it is always the current. */
	पूर्णांक tlabel;
	काष्ठा list_head link;
	काष्ठा fw_card *card;
	bool is_split_transaction;
	काष्ठा समयr_list split_समयout_समयr;

	काष्ठा fw_packet packet;

	/*
	 * The data passed to the callback is valid only during the
	 * callback.
	 */
	fw_transaction_callback_t callback;
	व्योम *callback_data;
पूर्ण;

काष्ठा fw_address_handler अणु
	u64 offset;
	u64 length;
	fw_address_callback_t address_callback;
	व्योम *callback_data;
	काष्ठा list_head link;
पूर्ण;

काष्ठा fw_address_region अणु
	u64 start;
	u64 end;
पूर्ण;

बाह्य स्थिर काष्ठा fw_address_region fw_high_memory_region;

पूर्णांक fw_core_add_address_handler(काष्ठा fw_address_handler *handler,
				स्थिर काष्ठा fw_address_region *region);
व्योम fw_core_हटाओ_address_handler(काष्ठा fw_address_handler *handler);
व्योम fw_send_response(काष्ठा fw_card *card,
		      काष्ठा fw_request *request, पूर्णांक rcode);
पूर्णांक fw_get_request_speed(काष्ठा fw_request *request);
व्योम fw_send_request(काष्ठा fw_card *card, काष्ठा fw_transaction *t,
		     पूर्णांक tcode, पूर्णांक destination_id, पूर्णांक generation, पूर्णांक speed,
		     अचिन्हित दीर्घ दीर्घ offset, व्योम *payload, माप_प्रकार length,
		     fw_transaction_callback_t callback, व्योम *callback_data);
पूर्णांक fw_cancel_transaction(काष्ठा fw_card *card,
			  काष्ठा fw_transaction *transaction);
पूर्णांक fw_run_transaction(काष्ठा fw_card *card, पूर्णांक tcode, पूर्णांक destination_id,
		       पूर्णांक generation, पूर्णांक speed, अचिन्हित दीर्घ दीर्घ offset,
		       व्योम *payload, माप_प्रकार length);
स्थिर अक्षर *fw_rcode_string(पूर्णांक rcode);

अटल अंतरभूत पूर्णांक fw_stream_packet_destination_id(पूर्णांक tag, पूर्णांक channel, पूर्णांक sy)
अणु
	वापस tag << 14 | channel << 8 | sy;
पूर्ण

व्योम fw_schedule_bus_reset(काष्ठा fw_card *card, bool delayed,
			   bool लघु_reset);

काष्ठा fw_descriptor अणु
	काष्ठा list_head link;
	माप_प्रकार length;
	u32 immediate;
	u32 key;
	स्थिर u32 *data;
पूर्ण;

पूर्णांक fw_core_add_descriptor(काष्ठा fw_descriptor *desc);
व्योम fw_core_हटाओ_descriptor(काष्ठा fw_descriptor *desc);

/*
 * The iso packet क्रमmat allows क्रम an immediate header/payload part
 * stored in 'header' immediately after the packet info plus an
 * indirect payload part that is poपूर्णांकer to by the 'payload' field.
 * Applications can use one or the other or both to implement simple
 * low-bandwidth streaming (e.g. audio) or more advanced
 * scatter-gather streaming (e.g. assembling video frame स्वतःmatically).
 */
काष्ठा fw_iso_packet अणु
	u16 payload_length;	/* Length of indirect payload		*/
	u32 पूर्णांकerrupt:1;	/* Generate पूर्णांकerrupt on this packet	*/
	u32 skip:1;		/* tx: Set to not send packet at all	*/
				/* rx: Sync bit, रुको क्रम matching sy	*/
	u32 tag:2;		/* tx: Tag in packet header		*/
	u32 sy:4;		/* tx: Sy in packet header		*/
	u32 header_length:8;	/* Length of immediate header		*/
	u32 header[0];		/* tx: Top of 1394 isoch. data_block	*/
पूर्ण;

#घोषणा FW_ISO_CONTEXT_TRANSMIT			0
#घोषणा FW_ISO_CONTEXT_RECEIVE			1
#घोषणा FW_ISO_CONTEXT_RECEIVE_MULTICHANNEL	2

#घोषणा FW_ISO_CONTEXT_MATCH_TAG0	 1
#घोषणा FW_ISO_CONTEXT_MATCH_TAG1	 2
#घोषणा FW_ISO_CONTEXT_MATCH_TAG2	 4
#घोषणा FW_ISO_CONTEXT_MATCH_TAG3	 8
#घोषणा FW_ISO_CONTEXT_MATCH_ALL_TAGS	15

/*
 * An iso buffer is just a set of pages mapped क्रम DMA in the
 * specअगरied direction.  Since the pages are to be used क्रम DMA, they
 * are not mapped पूर्णांकo the kernel भव address space.  We store the
 * DMA address in the page निजी. The helper function
 * fw_iso_buffer_map() will map the pages पूर्णांकo a given vma.
 */
काष्ठा fw_iso_buffer अणु
	क्रमागत dma_data_direction direction;
	काष्ठा page **pages;
	पूर्णांक page_count;
	पूर्णांक page_count_mapped;
पूर्ण;

पूर्णांक fw_iso_buffer_init(काष्ठा fw_iso_buffer *buffer, काष्ठा fw_card *card,
		       पूर्णांक page_count, क्रमागत dma_data_direction direction);
व्योम fw_iso_buffer_destroy(काष्ठा fw_iso_buffer *buffer, काष्ठा fw_card *card);
माप_प्रकार fw_iso_buffer_lookup(काष्ठा fw_iso_buffer *buffer, dma_addr_t completed);

काष्ठा fw_iso_context;
प्रकार व्योम (*fw_iso_callback_t)(काष्ठा fw_iso_context *context,
				  u32 cycle, माप_प्रकार header_length,
				  व्योम *header, व्योम *data);
प्रकार व्योम (*fw_iso_mc_callback_t)(काष्ठा fw_iso_context *context,
				     dma_addr_t completed, व्योम *data);
काष्ठा fw_iso_context अणु
	काष्ठा fw_card *card;
	पूर्णांक type;
	पूर्णांक channel;
	पूर्णांक speed;
	bool drop_overflow_headers;
	माप_प्रकार header_size;
	जोड़ अणु
		fw_iso_callback_t sc;
		fw_iso_mc_callback_t mc;
	पूर्ण callback;
	व्योम *callback_data;
पूर्ण;

काष्ठा fw_iso_context *fw_iso_context_create(काष्ठा fw_card *card,
		पूर्णांक type, पूर्णांक channel, पूर्णांक speed, माप_प्रकार header_size,
		fw_iso_callback_t callback, व्योम *callback_data);
पूर्णांक fw_iso_context_set_channels(काष्ठा fw_iso_context *ctx, u64 *channels);
पूर्णांक fw_iso_context_queue(काष्ठा fw_iso_context *ctx,
			 काष्ठा fw_iso_packet *packet,
			 काष्ठा fw_iso_buffer *buffer,
			 अचिन्हित दीर्घ payload);
व्योम fw_iso_context_queue_flush(काष्ठा fw_iso_context *ctx);
पूर्णांक fw_iso_context_flush_completions(काष्ठा fw_iso_context *ctx);
पूर्णांक fw_iso_context_start(काष्ठा fw_iso_context *ctx,
			 पूर्णांक cycle, पूर्णांक sync, पूर्णांक tags);
पूर्णांक fw_iso_context_stop(काष्ठा fw_iso_context *ctx);
व्योम fw_iso_context_destroy(काष्ठा fw_iso_context *ctx);
व्योम fw_iso_resource_manage(काष्ठा fw_card *card, पूर्णांक generation,
			    u64 channels_mask, पूर्णांक *channel, पूर्णांक *bandwidth,
			    bool allocate);

बाह्य काष्ठा workqueue_काष्ठा *fw_workqueue;

#पूर्ण_अगर /* _LINUX_FIREWIRE_H */
