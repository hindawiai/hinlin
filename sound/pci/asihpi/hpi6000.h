<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*****************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


Public declarations क्रम DSP Proramming Interface to TI C6701

Shared between hpi6000.c and DSP code

(C) Copyright AudioScience Inc. 1998-2003
******************************************************************************/

#अगर_अघोषित _HPI6000_H_
#घोषणा _HPI6000_H_

#घोषणा HPI_NMIXER_CONTROLS 200

/*
 * Control caching is always supported in the HPI code.
 * The DSP should make sure that dwControlCacheSizeInBytes is initialized to 0
 * during boot to make it in-active.
 */
काष्ठा hpi_hअगर_6000 अणु
	u32 host_cmd;
	u32 dsp_ack;
	u32 address;
	u32 length;
	u32 message_buffer_address;
	u32 response_buffer_address;
	u32 dsp_number;
	u32 adapter_info;
	u32 control_cache_is_dirty;
	u32 control_cache_address;
	u32 control_cache_size_in_bytes;
	u32 control_cache_count;
पूर्ण;

#घोषणा HPI_HIF_PACK_ADAPTER_INFO(adapter, version_major, version_minor) \
		((adapter << 16) | (version_major << 8) | version_minor)
#घोषणा HPI_HIF_ADAPTER_INFO_EXTRACT_ADAPTER(adapterinfo) \
		((adapterinfo >> 16) & 0xffff)
#घोषणा HPI_HIF_ADAPTER_INFO_EXTRACT_HWVERSION_MAJOR(adapterinfo) \
		((adapterinfo >> 8) & 0xff)
#घोषणा HPI_HIF_ADAPTER_INFO_EXTRACT_HWVERSION_MINOR(adapterinfo) \
		(adapterinfo & 0xff)

/* Command/status exchanged between host and DSP */
#घोषणा HPI_HIF_IDLE            0
#घोषणा HPI_HIF_SEND_MSG        1
#घोषणा HPI_HIF_GET_RESP        2
#घोषणा HPI_HIF_DATA_MASK       0x10
#घोषणा HPI_HIF_SEND_DATA       0x13
#घोषणा HPI_HIF_GET_DATA        0x14
#घोषणा HPI_HIF_SEND_DONE       5
#घोषणा HPI_HIF_RESET           9

#पूर्ण_अगर				/* _HPI6000_H_ */
