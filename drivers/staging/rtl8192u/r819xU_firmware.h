<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __INC_FIRMWARE_H
#घोषणा __INC_FIRMWARE_H

#घोषणा GET_COMMAND_PACKET_FRAG_THRESHOLD(v) \
	(4 * ((v) / 4) - 8 - USB_HWDESC_HEADER_LEN)

क्रमागत firmware_init_step_e अणु
	FW_INIT_STEP0_BOOT = 0,
	FW_INIT_STEP1_MAIN = 1,
	FW_INIT_STEP2_DATA = 2,
पूर्ण;

क्रमागत opt_rst_type_e अणु
	OPT_SYSTEM_RESET = 0,
	OPT_FIRMWARE_RESET = 1,
पूर्ण;

#पूर्ण_अगर
