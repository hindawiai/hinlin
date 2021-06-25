<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*****************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


Host Interface module क्रम an ASI6205 based
bus mastering PCI adapter.

Copyright AudioScience, Inc., 2003
******************************************************************************/

#अगर_अघोषित _HPI6205_H_
#घोषणा _HPI6205_H_

#समावेश "hpi_internal.h"

/***********************************************************
	Defines used क्रम basic messaging
************************************************************/
#घोषणा H620_HIF_RESET          0
#घोषणा H620_HIF_IDLE           1
#घोषणा H620_HIF_GET_RESP       2
#घोषणा H620_HIF_DATA_DONE      3
#घोषणा H620_HIF_DATA_MASK      0x10
#घोषणा H620_HIF_SEND_DATA      0x14
#घोषणा H620_HIF_GET_DATA       0x15
#घोषणा H620_HIF_UNKNOWN                0x0000ffff

/***********************************************************
	Types used क्रम mixer control caching
************************************************************/

#घोषणा H620_MAX_ISTREAMS 32
#घोषणा H620_MAX_OSTREAMS 32
#घोषणा HPI_NMIXER_CONTROLS 2048

/*********************************************************************
This is used क्रम dynamic control cache allocation
**********************************************************************/
काष्ठा controlcache_6205 अणु
	u32 number_of_controls;
	u32 physical_address32;
	u32 size_in_bytes;
पूर्ण;

/*********************************************************************
This is used क्रम dynamic allocation of async event array
**********************************************************************/
काष्ठा async_event_buffer_6205 अणु
	u32 physical_address32;
	u32 spare;
	काष्ठा hpi_fअगरo_buffer b;
पूर्ण;

/***********************************************************
The Host located memory buffer that the 6205 will bus master
in and out of.
************************************************************/
#घोषणा HPI6205_SIZखातापूर्ण_DATA (16*1024)

काष्ठा message_buffer_6205 अणु
	काष्ठा hpi_message message;
	अक्षर data[256];
पूर्ण;

काष्ठा response_buffer_6205 अणु
	काष्ठा hpi_response response;
	अक्षर data[256];
पूर्ण;

जोड़ buffer_6205 अणु
	काष्ठा message_buffer_6205 message_buffer;
	काष्ठा response_buffer_6205 response_buffer;
	u8 b_data[HPI6205_SIZखातापूर्ण_DATA];
पूर्ण;

काष्ठा bus_master_पूर्णांकerface अणु
	u32 host_cmd;
	u32 dsp_ack;
	u32 transfer_size_in_bytes;
	जोड़ buffer_6205 u;
	काष्ठा controlcache_6205 control_cache;
	काष्ठा async_event_buffer_6205 async_buffer;
	काष्ठा hpi_hostbuffer_status
	 instream_host_buffer_status[H620_MAX_ISTREAMS];
	काष्ठा hpi_hostbuffer_status
	 outstream_host_buffer_status[H620_MAX_OSTREAMS];
पूर्ण;

#पूर्ण_अगर
