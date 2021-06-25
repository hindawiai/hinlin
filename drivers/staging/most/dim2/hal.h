<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * hal.h - DIM2 HAL पूर्णांकerface
 * (MediaLB, Device Interface Macro IP, OS62420)
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

#अगर_अघोषित _DIM2_HAL_H
#घोषणा _DIM2_HAL_H

#समावेश <linux/types.h>
#समावेश "reg.h"

/*
 * The values below are specअगरied in the hardware specअगरication.
 * So, they should not be changed until the hardware specअगरication changes.
 */
क्रमागत mlb_clk_speed अणु
	CLK_256FS = 0,
	CLK_512FS = 1,
	CLK_1024FS = 2,
	CLK_2048FS = 3,
	CLK_3072FS = 4,
	CLK_4096FS = 5,
	CLK_6144FS = 6,
	CLK_8192FS = 7,
पूर्ण;

काष्ठा dim_ch_state_t अणु
	bool पढ़ोy; /* Shows पढ़ोiness to enqueue next buffer */
	u16 करोne_buffers; /* Number of completed buffers */
पूर्ण;

काष्ठा पूर्णांक_ch_state अणु
	/* changed only in पूर्णांकerrupt context */
	अस्थिर पूर्णांक request_counter;

	/* changed only in task context */
	अस्थिर पूर्णांक service_counter;

	u8 idx1;
	u8 idx2;
	u8 level; /* [0..2], buffering level */
पूर्ण;

काष्ठा dim_channel अणु
	काष्ठा पूर्णांक_ch_state state;
	u8 addr;
	u16 dbr_addr;
	u16 dbr_size;
	u16 packet_length; /*< Isochronous packet length in bytes. */
	u16 bytes_per_frame; /*< Synchronous bytes per frame. */
	u16 करोne_sw_buffers_number; /*< Done software buffers number. */
पूर्ण;

u8 dim_startup(काष्ठा dim2_regs __iomem *dim_base_address, u32 mlb_घड़ी,
	       u32 fcnt);

व्योम dim_shutकरोwn(व्योम);

bool dim_get_lock_state(व्योम);

u16 dim_norm_ctrl_async_buffer_size(u16 buf_size);

u16 dim_norm_isoc_buffer_size(u16 buf_size, u16 packet_length);

u16 dim_norm_sync_buffer_size(u16 buf_size, u16 bytes_per_frame);

u8 dim_init_control(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		    u16 max_buffer_size);

u8 dim_init_async(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		  u16 max_buffer_size);

u8 dim_init_isoc(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		 u16 packet_length);

u8 dim_init_sync(काष्ठा dim_channel *ch, u8 is_tx, u16 ch_address,
		 u16 bytes_per_frame);

u8 dim_destroy_channel(काष्ठा dim_channel *ch);

व्योम dim_service_mlb_पूर्णांक_irq(व्योम);

व्योम dim_service_ahb_पूर्णांक_irq(काष्ठा dim_channel *स्थिर *channels);

u8 dim_service_channel(काष्ठा dim_channel *ch);

काष्ठा dim_ch_state_t *dim_get_channel_state(काष्ठा dim_channel *ch,
					     काष्ठा dim_ch_state_t *state_ptr);

u16 dim_dbr_space(काष्ठा dim_channel *ch);

bool dim_enqueue_buffer(काष्ठा dim_channel *ch, u32 buffer_addr,
			u16 buffer_size);

bool dim_detach_buffers(काष्ठा dim_channel *ch, u16 buffers_number);

व्योम dimcb_on_error(u8 error_id, स्थिर अक्षर *error_message);

#पूर्ण_अगर /* _DIM2_HAL_H */
