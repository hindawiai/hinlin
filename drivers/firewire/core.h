<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _FIREWIRE_CORE_H
#घोषणा _FIREWIRE_CORE_H

#समावेश <linux/compiler.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/fs.h>
#समावेश <linux/list.h>
#समावेश <linux/idr.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/refcount.h>

काष्ठा device;
काष्ठा fw_card;
काष्ठा fw_device;
काष्ठा fw_iso_buffer;
काष्ठा fw_iso_context;
काष्ठा fw_iso_packet;
काष्ठा fw_node;
काष्ठा fw_packet;


/* -card */

बाह्य __म_लिखो(2, 3)
व्योम fw_err(स्थिर काष्ठा fw_card *card, स्थिर अक्षर *fmt, ...);
बाह्य __म_लिखो(2, 3)
व्योम fw_notice(स्थिर काष्ठा fw_card *card, स्थिर अक्षर *fmt, ...);

/* bitfields within the PHY रेजिस्टरs */
#घोषणा PHY_LINK_ACTIVE		0x80
#घोषणा PHY_CONTENDER		0x40
#घोषणा PHY_BUS_RESET		0x40
#घोषणा PHY_EXTENDED_REGISTERS	0xe0
#घोषणा PHY_BUS_SHORT_RESET	0x40
#घोषणा PHY_INT_STATUS_BITS	0x3c
#घोषणा PHY_ENABLE_ACCEL	0x02
#घोषणा PHY_ENABLE_MULTI	0x01
#घोषणा PHY_PAGE_SELECT		0xe0

#घोषणा BANDWIDTH_AVAILABLE_INITIAL	4915
#घोषणा BROADCAST_CHANNEL_INITIAL	(1 << 31 | 31)
#घोषणा BROADCAST_CHANNEL_VALID		(1 << 30)

#घोषणा CSR_STATE_BIT_CMSTR	(1 << 8)
#घोषणा CSR_STATE_BIT_ABDICATE	(1 << 10)

काष्ठा fw_card_driver अणु
	/*
	 * Enable the given card with the given initial config rom.
	 * This function is expected to activate the card, and either
	 * enable the PHY or set the link_on bit and initiate a bus
	 * reset.
	 */
	पूर्णांक (*enable)(काष्ठा fw_card *card,
		      स्थिर __be32 *config_rom, माप_प्रकार length);

	पूर्णांक (*पढ़ो_phy_reg)(काष्ठा fw_card *card, पूर्णांक address);
	पूर्णांक (*update_phy_reg)(काष्ठा fw_card *card, पूर्णांक address,
			      पूर्णांक clear_bits, पूर्णांक set_bits);

	/*
	 * Update the config rom क्रम an enabled card.  This function
	 * should change the config rom that is presented on the bus
	 * and initiate a bus reset.
	 */
	पूर्णांक (*set_config_rom)(काष्ठा fw_card *card,
			      स्थिर __be32 *config_rom, माप_प्रकार length);

	व्योम (*send_request)(काष्ठा fw_card *card, काष्ठा fw_packet *packet);
	व्योम (*send_response)(काष्ठा fw_card *card, काष्ठा fw_packet *packet);
	/* Calling cancel is valid once a packet has been submitted. */
	पूर्णांक (*cancel_packet)(काष्ठा fw_card *card, काष्ठा fw_packet *packet);

	/*
	 * Allow the specअगरied node ID to करो direct DMA out and in of
	 * host memory.  The card will disable this क्रम all node when
	 * a bus reset happens, so driver need to reenable this after
	 * bus reset.  Returns 0 on success, -ENODEV अगर the card
	 * करोesn't support this, -ESTALE if the generation doesn't
	 * match.
	 */
	पूर्णांक (*enable_phys_dma)(काष्ठा fw_card *card,
			       पूर्णांक node_id, पूर्णांक generation);

	u32 (*पढ़ो_csr)(काष्ठा fw_card *card, पूर्णांक csr_offset);
	व्योम (*ग_लिखो_csr)(काष्ठा fw_card *card, पूर्णांक csr_offset, u32 value);

	काष्ठा fw_iso_context *
	(*allocate_iso_context)(काष्ठा fw_card *card,
				पूर्णांक type, पूर्णांक channel, माप_प्रकार header_size);
	व्योम (*मुक्त_iso_context)(काष्ठा fw_iso_context *ctx);

	पूर्णांक (*start_iso)(काष्ठा fw_iso_context *ctx,
			 s32 cycle, u32 sync, u32 tags);

	पूर्णांक (*set_iso_channels)(काष्ठा fw_iso_context *ctx, u64 *channels);

	पूर्णांक (*queue_iso)(काष्ठा fw_iso_context *ctx,
			 काष्ठा fw_iso_packet *packet,
			 काष्ठा fw_iso_buffer *buffer,
			 अचिन्हित दीर्घ payload);

	व्योम (*flush_queue_iso)(काष्ठा fw_iso_context *ctx);

	पूर्णांक (*flush_iso_completions)(काष्ठा fw_iso_context *ctx);

	पूर्णांक (*stop_iso)(काष्ठा fw_iso_context *ctx);
पूर्ण;

व्योम fw_card_initialize(काष्ठा fw_card *card,
		स्थिर काष्ठा fw_card_driver *driver, काष्ठा device *device);
पूर्णांक fw_card_add(काष्ठा fw_card *card,
		u32 max_receive, u32 link_speed, u64 guid);
व्योम fw_core_हटाओ_card(काष्ठा fw_card *card);
पूर्णांक fw_compute_block_crc(__be32 *block);
व्योम fw_schedule_bm_work(काष्ठा fw_card *card, अचिन्हित दीर्घ delay);

/* -cdev */

बाह्य स्थिर काष्ठा file_operations fw_device_ops;

व्योम fw_device_cdev_update(काष्ठा fw_device *device);
व्योम fw_device_cdev_हटाओ(काष्ठा fw_device *device);
व्योम fw_cdev_handle_phy_packet(काष्ठा fw_card *card, काष्ठा fw_packet *p);


/* -device */

बाह्य काष्ठा rw_semaphore fw_device_rwsem;
बाह्य काष्ठा idr fw_device_idr;
बाह्य पूर्णांक fw_cdev_major;

अटल अंतरभूत काष्ठा fw_device *fw_device_get(काष्ठा fw_device *device)
अणु
	get_device(&device->device);

	वापस device;
पूर्ण

अटल अंतरभूत व्योम fw_device_put(काष्ठा fw_device *device)
अणु
	put_device(&device->device);
पूर्ण

काष्ठा fw_device *fw_device_get_by_devt(dev_t devt);
पूर्णांक fw_device_set_broadcast_channel(काष्ठा device *dev, व्योम *gen);
व्योम fw_node_event(काष्ठा fw_card *card, काष्ठा fw_node *node, पूर्णांक event);


/* -iso */

पूर्णांक fw_iso_buffer_alloc(काष्ठा fw_iso_buffer *buffer, पूर्णांक page_count);
पूर्णांक fw_iso_buffer_map_dma(काष्ठा fw_iso_buffer *buffer, काष्ठा fw_card *card,
			  क्रमागत dma_data_direction direction);


/* -topology */

क्रमागत अणु
	FW_NODE_CREATED,
	FW_NODE_UPDATED,
	FW_NODE_DESTROYED,
	FW_NODE_LINK_ON,
	FW_NODE_LINK_OFF,
	FW_NODE_INITIATED_RESET,
पूर्ण;

काष्ठा fw_node अणु
	u16 node_id;
	u8 color;
	u8 port_count;
	u8 link_on:1;
	u8 initiated_reset:1;
	u8 b_path:1;
	u8 phy_speed:2;	/* As in the self ID packet. */
	u8 max_speed:2;	/* Minimum of all phy-speeds on the path from the
			 * local node to this node. */
	u8 max_depth:4;	/* Maximum depth to any leaf node */
	u8 max_hops:4;	/* Max hops in this sub tree */
	refcount_t ref_count;

	/* For serializing node topology पूर्णांकo a list. */
	काष्ठा list_head link;

	/* Upper layer specअगरic data. */
	व्योम *data;

	काष्ठा fw_node *ports[];
पूर्ण;

अटल अंतरभूत काष्ठा fw_node *fw_node_get(काष्ठा fw_node *node)
अणु
	refcount_inc(&node->ref_count);

	वापस node;
पूर्ण

अटल अंतरभूत व्योम fw_node_put(काष्ठा fw_node *node)
अणु
	अगर (refcount_dec_and_test(&node->ref_count))
		kमुक्त(node);
पूर्ण

व्योम fw_core_handle_bus_reset(काष्ठा fw_card *card, पूर्णांक node_id,
	पूर्णांक generation, पूर्णांक self_id_count, u32 *self_ids, bool bm_abdicate);
व्योम fw_destroy_nodes(काष्ठा fw_card *card);

/*
 * Check whether new_generation is the immediate successor of old_generation.
 * Take counter roll-over at 255 (as per OHCI) पूर्णांकo account.
 */
अटल अंतरभूत bool is_next_generation(पूर्णांक new_generation, पूर्णांक old_generation)
अणु
	वापस (new_generation & 0xff) == ((old_generation + 1) & 0xff);
पूर्ण


/* -transaction */

#घोषणा TCODE_LINK_INTERNAL		0xe

#घोषणा TCODE_IS_READ_REQUEST(tcode)	(((tcode) & ~1) == 4)
#घोषणा TCODE_IS_BLOCK_PACKET(tcode)	(((tcode) &  1) != 0)
#घोषणा TCODE_IS_LINK_INTERNAL(tcode)	((tcode) == TCODE_LINK_INTERNAL)
#घोषणा TCODE_IS_REQUEST(tcode)		(((tcode) &  2) == 0)
#घोषणा TCODE_IS_RESPONSE(tcode)	(((tcode) &  2) != 0)
#घोषणा TCODE_HAS_REQUEST_DATA(tcode)	(((tcode) & 12) != 4)
#घोषणा TCODE_HAS_RESPONSE_DATA(tcode)	(((tcode) & 12) != 0)

#घोषणा LOCAL_BUS 0xffc0

/* OHCI-1394's शेष upper bound क्रम physical DMA: 4 GB */
#घोषणा FW_MAX_PHYSICAL_RANGE		(1ULL << 32)

व्योम fw_core_handle_request(काष्ठा fw_card *card, काष्ठा fw_packet *request);
व्योम fw_core_handle_response(काष्ठा fw_card *card, काष्ठा fw_packet *packet);
पूर्णांक fw_get_response_length(काष्ठा fw_request *request);
व्योम fw_fill_response(काष्ठा fw_packet *response, u32 *request_header,
		      पूर्णांक rcode, व्योम *payload, माप_प्रकार length);

#घोषणा FW_PHY_CONFIG_NO_NODE_ID	-1
#घोषणा FW_PHY_CONFIG_CURRENT_GAP_COUNT	-1
व्योम fw_send_phy_config(काष्ठा fw_card *card,
			पूर्णांक node_id, पूर्णांक generation, पूर्णांक gap_count);

अटल अंतरभूत bool is_ping_packet(u32 *data)
अणु
	वापस (data[0] & 0xc0ffffff) == 0 && ~data[0] == data[1];
पूर्ण

#पूर्ण_अगर /* _FIREWIRE_CORE_H */
