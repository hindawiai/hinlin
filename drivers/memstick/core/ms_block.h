<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  ms_block.h - Sony MemoryStick (legacy) storage support

 *  Copyright (C) 2013 Maxim Levitsky <maximlevitsky@gmail.com>
 *
 * Minor portions of the driver are copied from mspro_block.c which is
 * Copyright (C) 2007 Alex Dubov <oakad@yahoo.com>
 *
 * Also ms काष्ठाures were copied from old broken driver by same author
 * These probably come from MS spec
 */

#अगर_अघोषित MS_BLOCK_NEW_H
#घोषणा MS_BLOCK_NEW_H

#घोषणा MS_BLOCK_MAX_SEGS      32
#घोषणा MS_BLOCK_MAX_PAGES     ((2 << 16) - 1)

#घोषणा MS_BLOCK_MAX_BOOT_ADDR 0x000c
#घोषणा MS_BLOCK_BOOT_ID       0x0001
#घोषणा MS_BLOCK_INVALID       0xffff
#घोषणा MS_MAX_ZONES           16
#घोषणा MS_BLOCKS_IN_ZONE      512

#घोषणा MS_BLOCK_MAP_LINE_SZ   16
#घोषणा MS_BLOCK_PART_SHIFT    3


#घोषणा MEMSTICK_UNCORR_ERROR (MEMSTICK_STATUS1_UCFG | \
		MEMSTICK_STATUS1_UCEX | MEMSTICK_STATUS1_UCDT)

#घोषणा MEMSTICK_CORR_ERROR (MEMSTICK_STATUS1_FGER | MEMSTICK_STATUS1_EXER | \
	MEMSTICK_STATUS1_DTER)

#घोषणा MEMSTICK_INT_ERROR (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_ERR)

#घोषणा MEMSTICK_OVERWRITE_FLAG_NORMAL \
	(MEMSTICK_OVERWRITE_PGST1 | \
	MEMSTICK_OVERWRITE_PGST0  | \
	MEMSTICK_OVERWRITE_BKST)

#घोषणा MEMSTICK_OV_PG_NORMAL \
	(MEMSTICK_OVERWRITE_PGST1 | MEMSTICK_OVERWRITE_PGST0)

#घोषणा MEMSTICK_MANAGEMENT_FLAG_NORMAL \
	(MEMSTICK_MANAGEMENT_SYSFLG |  \
	MEMSTICK_MANAGEMENT_SCMS1   |  \
	MEMSTICK_MANAGEMENT_SCMS0)     \

काष्ठा ms_boot_header अणु
	अचिन्हित लघु block_id;
	अचिन्हित लघु क्रमmat_reserved;
	अचिन्हित अक्षर  reserved0[184];
	अचिन्हित अक्षर  data_entry;
	अचिन्हित अक्षर  reserved1[179];
पूर्ण __packed;


काष्ठा ms_प्रणाली_item अणु
	अचिन्हित पूर्णांक  start_addr;
	अचिन्हित पूर्णांक  data_size;
	अचिन्हित अक्षर data_type_id;
	अचिन्हित अक्षर reserved[3];
पूर्ण __packed;

काष्ठा ms_प्रणाली_entry अणु
	काष्ठा ms_प्रणाली_item disabled_block;
	काष्ठा ms_प्रणाली_item cis_idi;
	अचिन्हित अक्षर         reserved[24];
पूर्ण __packed;

काष्ठा ms_boot_attr_info अणु
	अचिन्हित अक्षर      memorystick_class;
	अचिन्हित अक्षर      क्रमmat_unique_value1;
	अचिन्हित लघु     block_size;
	अचिन्हित लघु     number_of_blocks;
	अचिन्हित लघु     number_of_effective_blocks;
	अचिन्हित लघु     page_size;
	अचिन्हित अक्षर      extra_data_size;
	अचिन्हित अक्षर      क्रमmat_unique_value2;
	अचिन्हित अक्षर      assembly_समय[8];
	अचिन्हित अक्षर      क्रमmat_unique_value3;
	अचिन्हित अक्षर      serial_number[3];
	अचिन्हित अक्षर      assembly_manufacturer_code;
	अचिन्हित अक्षर      assembly_model_code[3];
	अचिन्हित लघु     memory_manufacturer_code;
	अचिन्हित लघु     memory_device_code;
	अचिन्हित लघु     implemented_capacity;
	अचिन्हित अक्षर      क्रमmat_unique_value4[2];
	अचिन्हित अक्षर      vcc;
	अचिन्हित अक्षर      vpp;
	अचिन्हित लघु     controller_number;
	अचिन्हित लघु     controller_function;
	अचिन्हित अक्षर      reserved0[9];
	अचिन्हित अक्षर      transfer_supporting;
	अचिन्हित लघु     क्रमmat_unique_value5;
	अचिन्हित अक्षर      क्रमmat_type;
	अचिन्हित अक्षर      memorystick_application;
	अचिन्हित अक्षर      device_type;
	अचिन्हित अक्षर      reserved1[22];
	अचिन्हित अक्षर      क्रमmat_uniqure_value6[2];
	अचिन्हित अक्षर      reserved2[15];
पूर्ण __packed;

काष्ठा ms_cis_idi अणु
	अचिन्हित लघु general_config;
	अचिन्हित लघु logical_cylinders;
	अचिन्हित लघु reserved0;
	अचिन्हित लघु logical_heads;
	अचिन्हित लघु track_size;
	अचिन्हित लघु page_size;
	अचिन्हित लघु pages_per_track;
	अचिन्हित लघु msw;
	अचिन्हित लघु lsw;
	अचिन्हित लघु reserved1;
	अचिन्हित अक्षर  serial_number[20];
	अचिन्हित लघु buffer_type;
	अचिन्हित लघु buffer_size_increments;
	अचिन्हित लघु दीर्घ_command_ecc;
	अचिन्हित अक्षर  firmware_version[28];
	अचिन्हित अक्षर  model_name[18];
	अचिन्हित लघु reserved2[5];
	अचिन्हित लघु pio_mode_number;
	अचिन्हित लघु dma_mode_number;
	अचिन्हित लघु field_validity;
	अचिन्हित लघु current_logical_cylinders;
	अचिन्हित लघु current_logical_heads;
	अचिन्हित लघु current_pages_per_track;
	अचिन्हित पूर्णांक   current_page_capacity;
	अचिन्हित लघु mutiple_page_setting;
	अचिन्हित पूर्णांक   addressable_pages;
	अचिन्हित लघु single_word_dma;
	अचिन्हित लघु multi_word_dma;
	अचिन्हित अक्षर  reserved3[128];
पूर्ण __packed;


काष्ठा ms_boot_page अणु
	काष्ठा ms_boot_header    header;
	काष्ठा ms_प्रणाली_entry   entry;
	काष्ठा ms_boot_attr_info attr;
पूर्ण __packed;

काष्ठा msb_data अणु
	अचिन्हित पूर्णांक			usage_count;
	काष्ठा memstick_dev		*card;
	काष्ठा gendisk			*disk;
	काष्ठा request_queue		*queue;
	spinlock_t			q_lock;
	काष्ठा blk_mq_tag_set		tag_set;
	काष्ठा hd_geometry		geometry;
	काष्ठा attribute_group		attr_group;
	काष्ठा request			*req;
	पूर्णांक				caps;
	पूर्णांक				disk_id;

	/* IO */
	काष्ठा workqueue_काष्ठा		*io_queue;
	bool				io_queue_stopped;
	काष्ठा work_काष्ठा		io_work;
	bool				card_dead;

	/* Media properties */
	काष्ठा ms_boot_page		*boot_page;
	u16				boot_block_locations[2];
	पूर्णांक				boot_block_count;

	bool				पढ़ो_only;
	अचिन्हित लघु			page_size;
	पूर्णांक				block_size;
	पूर्णांक				pages_in_block;
	पूर्णांक				zone_count;
	पूर्णांक				block_count;
	पूर्णांक				logical_block_count;

	/* FTL tables */
	अचिन्हित दीर्घ			*used_blocks_biपंचांगap;
	अचिन्हित दीर्घ			*erased_blocks_biपंचांगap;
	u16				*lba_to_pba_table;
	पूर्णांक				मुक्त_block_count[MS_MAX_ZONES];
	bool				ftl_initialized;

	/* Cache */
	अचिन्हित अक्षर			*cache;
	अचिन्हित दीर्घ			valid_cache_biपंचांगap;
	पूर्णांक				cache_block_lba;
	bool				need_flush_cache;
	काष्ठा समयr_list		cache_flush_समयr;

	/* Pपुनः_स्मृतिated buffers */
	अचिन्हित अक्षर			*block_buffer;
	काष्ठा scatterlist		pपुनः_स्मृति_sg[MS_BLOCK_MAX_SEGS+1];


	/* handler's local data */
	काष्ठा ms_रेजिस्टर_addr		reg_addr;
	bool				addr_valid;

	u8				command_value;
	bool				command_need_oob;
	काष्ठा scatterlist		*current_sg;
	पूर्णांक				current_sg_offset;

	काष्ठा ms_रेजिस्टर		regs;
	पूर्णांक				current_page;

	पूर्णांक				state;
	पूर्णांक				निकास_error;
	bool				पूर्णांक_polling;
	अचिन्हित दीर्घ			पूर्णांक_समयout;

पूर्ण;

क्रमागत msb_पढ़ोpage_states अणु
	MSB_RP_SEND_BLOCK_ADDRESS = 0,
	MSB_RP_SEND_READ_COMMAND,

	MSB_RP_SEND_INT_REQ,
	MSB_RP_RECEIVE_INT_REQ_RESULT,

	MSB_RP_SEND_READ_STATUS_REG,
	MSB_RP_RECEIVE_STATUS_REG,

	MSB_RP_SEND_OOB_READ,
	MSB_RP_RECEIVE_OOB_READ,

	MSB_RP_SEND_READ_DATA,
	MSB_RP_RECEIVE_READ_DATA,
पूर्ण;

क्रमागत msb_ग_लिखो_block_states अणु
	MSB_WB_SEND_WRITE_PARAMS = 0,
	MSB_WB_SEND_WRITE_OOB,
	MSB_WB_SEND_WRITE_COMMAND,

	MSB_WB_SEND_INT_REQ,
	MSB_WB_RECEIVE_INT_REQ,

	MSB_WB_SEND_WRITE_DATA,
	MSB_WB_RECEIVE_WRITE_CONFIRMATION,
पूर्ण;

क्रमागत msb_send_command_states अणु
	MSB_SC_SEND_WRITE_PARAMS,
	MSB_SC_SEND_WRITE_OOB,
	MSB_SC_SEND_COMMAND,

	MSB_SC_SEND_INT_REQ,
	MSB_SC_RECEIVE_INT_REQ,

पूर्ण;

क्रमागत msb_reset_states अणु
	MSB_RS_SEND,
	MSB_RS_CONFIRM,
पूर्ण;

क्रमागत msb_par_चयन_states अणु
	MSB_PS_SEND_SWITCH_COMMAND,
	MSB_PS_SWICH_HOST,
	MSB_PS_CONFIRM,
पूर्ण;

काष्ठा chs_entry अणु
	अचिन्हित दीर्घ size;
	अचिन्हित अक्षर sec;
	अचिन्हित लघु cyl;
	अचिन्हित अक्षर head;
पूर्ण;

अटल पूर्णांक msb_reset(काष्ठा msb_data *msb, bool full);

अटल पूर्णांक h_msb_शेष_bad(काष्ठा memstick_dev *card,
						काष्ठा memstick_request **mrq);

#घोषणा __dbg(level, क्रमmat, ...) \
	करो अणु \
		अगर (debug >= level) \
			pr_err(क्रमmat "\n", ## __VA_ARGS__); \
	पूर्ण जबतक (0)


#घोषणा dbg(क्रमmat, ...)		__dbg(1, क्रमmat, ## __VA_ARGS__)
#घोषणा dbg_verbose(क्रमmat, ...)	__dbg(2, क्रमmat, ## __VA_ARGS__)

#पूर्ण_अगर
