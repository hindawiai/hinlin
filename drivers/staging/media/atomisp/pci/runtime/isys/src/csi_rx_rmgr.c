<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "system_global.h"

#अगर_घोषित ISP2401

#समावेश "assert_support.h"
#समावेश "platform_support.h"
#समावेश "ia_css_isys.h"
#समावेश "bitop_support.h"
#समावेश "ia_css_pipeline.h"	/* ia_css_pipeline_get_pipe_io_status() */
#समावेश "sh_css_internal.h"	/* sh_css_sp_pipeline_io_status
				 * SH_CSS_MAX_SP_THREADS
				 */
#समावेश "csi_rx_rmgr.h"

अटल isys_csi_rx_rsrc_t  isys_csi_rx_rsrc[N_CSI_RX_BACKEND_ID];

व्योम ia_css_isys_csi_rx_lut_rmgr_init(व्योम)
अणु
	स_रखो(isys_csi_rx_rsrc, 0, माप(isys_csi_rx_rsrc));
पूर्ण

व्योम ia_css_isys_csi_rx_lut_rmgr_uninit(व्योम)
अणु
	स_रखो(isys_csi_rx_rsrc, 0, माप(isys_csi_rx_rsrc));
पूर्ण

bool ia_css_isys_csi_rx_lut_rmgr_acquire(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry)
अणु
	bool retval = false;
	u32 max_num_packets_of_type;
	u32 num_active_of_type;
	isys_csi_rx_rsrc_t *cur_rsrc = शून्य;
	u16 i;

	निश्चित(backend < N_CSI_RX_BACKEND_ID);
	निश्चित((packet_type == CSI_MIPI_PACKET_TYPE_LONG) ||
	       (packet_type == CSI_MIPI_PACKET_TYPE_SHORT));
	निश्चित(entry);

	अगर ((backend < N_CSI_RX_BACKEND_ID) && (entry)) अणु
		cur_rsrc = &isys_csi_rx_rsrc[backend];
		अगर (packet_type == CSI_MIPI_PACKET_TYPE_LONG) अणु
			max_num_packets_of_type = N_LONG_PACKET_LUT_ENTRIES[backend];
			num_active_of_type = cur_rsrc->num_दीर्घ_packets;
		पूर्ण अन्यथा अणु
			max_num_packets_of_type = N_SHORT_PACKET_LUT_ENTRIES[backend];
			num_active_of_type = cur_rsrc->num_लघु_packets;
		पूर्ण

		अगर (num_active_of_type < max_num_packets_of_type) अणु
			क्रम (i = 0; i < max_num_packets_of_type; i++) अणु
				अगर (bitop_getbit(cur_rsrc->active_table, i) == 0) अणु
					bitop_setbit(cur_rsrc->active_table, i);

					अगर (packet_type == CSI_MIPI_PACKET_TYPE_LONG) अणु
						entry->दीर्घ_packet_entry = i;
						entry->लघु_packet_entry = 0;
						cur_rsrc->num_दीर्घ_packets++;
					पूर्ण अन्यथा अणु
						entry->दीर्घ_packet_entry = 0;
						entry->लघु_packet_entry = i;
						cur_rsrc->num_लघु_packets++;
					पूर्ण
					cur_rsrc->num_active++;
					retval = true;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

व्योम ia_css_isys_csi_rx_lut_rmgr_release(
    csi_rx_backend_ID_t		backend,
    csi_mipi_packet_type_t		packet_type,
    csi_rx_backend_lut_entry_t	*entry)
अणु
	u32 max_num_packets;
	isys_csi_rx_rsrc_t *cur_rsrc = शून्य;
	u32 packet_entry = 0;

	निश्चित(backend < N_CSI_RX_BACKEND_ID);
	निश्चित(entry);
	निश्चित((packet_type >= CSI_MIPI_PACKET_TYPE_LONG) ||
	       (packet_type <= CSI_MIPI_PACKET_TYPE_SHORT));

	अगर ((backend < N_CSI_RX_BACKEND_ID) && (entry)) अणु
		अगर (packet_type == CSI_MIPI_PACKET_TYPE_LONG) अणु
			max_num_packets = N_LONG_PACKET_LUT_ENTRIES[backend];
			packet_entry = entry->दीर्घ_packet_entry;
		पूर्ण अन्यथा अणु
			max_num_packets = N_SHORT_PACKET_LUT_ENTRIES[backend];
			packet_entry = entry->लघु_packet_entry;
		पूर्ण

		cur_rsrc = &isys_csi_rx_rsrc[backend];
		अगर ((packet_entry < max_num_packets) && (cur_rsrc->num_active > 0)) अणु
			अगर (bitop_getbit(cur_rsrc->active_table, packet_entry) == 1) अणु
				bitop_clearbit(cur_rsrc->active_table, packet_entry);

				अगर (packet_type == CSI_MIPI_PACKET_TYPE_LONG)
					cur_rsrc->num_दीर्घ_packets--;
				अन्यथा
					cur_rsrc->num_लघु_packets--;
				cur_rsrc->num_active--;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ia_css_isys_csi_rx_रेजिस्टर_stream(
    क्रमागत mipi_port_id port,
    uपूर्णांक32_t isys_stream_id)
अणु
	पूर्णांक retval = -EINVAL;

	अगर ((port < N_INPUT_SYSTEM_CSI_PORT) &&
	    (isys_stream_id < SH_CSS_MAX_ISYS_CHANNEL_NODES)) अणु
		काष्ठा sh_css_sp_pipeline_io_status *pipe_io_status;

		pipe_io_status = ia_css_pipeline_get_pipe_io_status();
		अगर (bitop_getbit(pipe_io_status->active[port], isys_stream_id) == 0) अणु
			bitop_setbit(pipe_io_status->active[port], isys_stream_id);
			pipe_io_status->running[port] = 0;
			retval = 0;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण

पूर्णांक ia_css_isys_csi_rx_unरेजिस्टर_stream(
    क्रमागत mipi_port_id port,
    uपूर्णांक32_t isys_stream_id)
अणु
	पूर्णांक retval = -EINVAL;

	अगर ((port < N_INPUT_SYSTEM_CSI_PORT) &&
	    (isys_stream_id < SH_CSS_MAX_ISYS_CHANNEL_NODES)) अणु
		काष्ठा sh_css_sp_pipeline_io_status *pipe_io_status;

		pipe_io_status = ia_css_pipeline_get_pipe_io_status();
		अगर (bitop_getbit(pipe_io_status->active[port], isys_stream_id) == 1) अणु
			bitop_clearbit(pipe_io_status->active[port], isys_stream_id);
			retval = 0;
		पूर्ण
	पूर्ण
	वापस retval;
पूर्ण
#पूर्ण_अगर
