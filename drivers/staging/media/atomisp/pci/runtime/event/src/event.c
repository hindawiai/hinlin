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

#समावेश "sh_css_sp.h"

#समावेश "dma.h"	/* N_DMA_CHANNEL_ID */

#समावेश <type_support.h>
#समावेश "ia_css_binary.h"
#समावेश "sh_css_hrt.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_internal.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_debug_internal.h"
#समावेश "sh_css_legacy.h"

#समावेश "gdc_device.h"				/* HRT_GDC_N */

/*#समावेश "sp.h"*/	/* host2sp_enqueue_frame_data() */

#समावेश "assert_support.h"

#समावेश "ia_css_queue.h"	/* host_sp_enqueue_XXX */
#समावेश "ia_css_event.h"	/* ia_css_event_encode */
/*
 * @brief Encode the inक्रमmation पूर्णांकo the software-event.
 * Refer to "sw_event_public.h" क्रम details.
 */
bool ia_css_event_encode(
    u8	*in,
    u8	nr,
    uपूर्णांक32_t	*out)
अणु
	bool ret;
	u32 nr_of_bits;
	u32 i;

	निश्चित(in);
	निश्चित(out);
	OP___निश्चित(nr > 0 && nr <= MAX_NR_OF_PAYLOADS_PER_SW_EVENT);

	/* initialize the output */
	*out = 0;

	/* get the number of bits per inक्रमmation */
	nr_of_bits = माप(uपूर्णांक32_t) * 8 / nr;

	/* compress the all inमाला_दो पूर्णांकo a signle output */
	क्रम (i = 0; i < nr; i++) अणु
		*out <<= nr_of_bits;
		*out |= in[i];
	पूर्ण

	/* get the वापस value */
	ret = (nr > 0 && nr <= MAX_NR_OF_PAYLOADS_PER_SW_EVENT);

	वापस ret;
पूर्ण

व्योम ia_css_event_decode(
    u32 event,
    uपूर्णांक8_t *payload)
अणु
	निश्चित(payload[1] == 0);
	निश्चित(payload[2] == 0);
	निश्चित(payload[3] == 0);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "ia_css_event_decode() enter:\n");

	/* First decode according to the common हाल
	 * In हाल of a PORT_खातापूर्ण event we overग_लिखो with
	 * the specअगरic values
	 * This is somewhat ugly but probably somewhat efficient
	 * (and it aव्योमs some code duplication)
	 */
	payload[0] = event & 0xff;  /*event_code */
	payload[1] = (event >> 8) & 0xff;
	payload[2] = (event >> 16) & 0xff;
	payload[3] = 0;

	चयन (payload[0]) अणु
	हाल SH_CSS_SP_EVENT_PORT_खातापूर्ण:
		payload[2] = 0;
		payload[3] = (event >> 24) & 0xff;
		अवरोध;

	हाल SH_CSS_SP_EVENT_ACC_STAGE_COMPLETE:
	हाल SH_CSS_SP_EVENT_TIMER:
	हाल SH_CSS_SP_EVENT_FRAME_TAGGED:
	हाल SH_CSS_SP_EVENT_FW_WARNING:
	हाल SH_CSS_SP_EVENT_FW_ASSERT:
		payload[3] = (event >> 24) & 0xff;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
