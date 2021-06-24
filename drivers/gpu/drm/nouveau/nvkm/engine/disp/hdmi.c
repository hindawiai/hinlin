<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश "hdmi.h"

व्योम pack_hdmi_infoframe(काष्ठा packed_hdmi_infoframe *packed_frame,
			 u8 *raw_frame, sमाप_प्रकार len)
अणु
	u32 header = 0;
	u32 subpack0_low = 0;
	u32 subpack0_high = 0;
	u32 subpack1_low = 0;
	u32 subpack1_high = 0;

	चयन (len) अणु
		/*
		 * "When in doubt, use brute force."
		 *     -- Ken Thompson.
		 */
	शेष:
		/*
		 * We presume that no valid frame is दीर्घer than 17
		 * octets, including header...  And truncate to that
		 * अगर it's दीर्घer.
		 */
	हाल 17:
		subpack1_high = (raw_frame[16] << 16);
		fallthrough;
	हाल 16:
		subpack1_high |= (raw_frame[15] << 8);
		fallthrough;
	हाल 15:
		subpack1_high |= raw_frame[14];
		fallthrough;
	हाल 14:
		subpack1_low = (raw_frame[13] << 24);
		fallthrough;
	हाल 13:
		subpack1_low |= (raw_frame[12] << 16);
		fallthrough;
	हाल 12:
		subpack1_low |= (raw_frame[11] << 8);
		fallthrough;
	हाल 11:
		subpack1_low |= raw_frame[10];
		fallthrough;
	हाल 10:
		subpack0_high = (raw_frame[9] << 16);
		fallthrough;
	हाल 9:
		subpack0_high |= (raw_frame[8] << 8);
		fallthrough;
	हाल 8:
		subpack0_high |= raw_frame[7];
		fallthrough;
	हाल 7:
		subpack0_low = (raw_frame[6] << 24);
		fallthrough;
	हाल 6:
		subpack0_low |= (raw_frame[5] << 16);
		fallthrough;
	हाल 5:
		subpack0_low |= (raw_frame[4] << 8);
		fallthrough;
	हाल 4:
		subpack0_low |= raw_frame[3];
		fallthrough;
	हाल 3:
		header = (raw_frame[2] << 16);
		fallthrough;
	हाल 2:
		header |= (raw_frame[1] << 8);
		fallthrough;
	हाल 1:
		header |= raw_frame[0];
		fallthrough;
	हाल 0:
		अवरोध;
	पूर्ण

	packed_frame->header = header;
	packed_frame->subpack0_low = subpack0_low;
	packed_frame->subpack0_high = subpack0_high;
	packed_frame->subpack1_low = subpack1_low;
	packed_frame->subpack1_high = subpack1_high;
पूर्ण
