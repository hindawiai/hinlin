<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */


#समावेश "dc_bios_types.h"
#समावेश "dcn30_vpg.h"
#समावेश "reg_helper.h"

#घोषणा DC_LOGGER \
		vpg3->base.ctx->logger

#घोषणा REG(reg)\
	(vpg3->regs->reg)

#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	vpg3->vpg_shअगरt->field_name, vpg3->vpg_mask->field_name


#घोषणा CTX \
	vpg3->base.ctx


अटल व्योम vpg3_update_generic_info_packet(
	काष्ठा vpg *vpg,
	uपूर्णांक32_t packet_index,
	स्थिर काष्ठा dc_info_packet *info_packet)
अणु
	काष्ठा dcn30_vpg *vpg3 = DCN30_VPG_FROM_VPG(vpg);
	uपूर्णांक32_t i;

	/* TODOFPGA Figure out a proper number क्रम max_retries polling क्रम lock
	 * use 50 क्रम now.
	 */
	uपूर्णांक32_t max_retries = 50;

	अगर (packet_index > 14)
		ASSERT(0);

	/* poll dig_update_lock is not locked -> asic पूर्णांकernal संकेत
	 * assume otg master lock will unlock it
	 */
	/* REG_WAIT(AFMT_VBI_PACKET_CONTROL, AFMT_GENERIC_LOCK_STATUS,
	 * 		0, 10, max_retries);
	 */

	/* TODO: Check अगर this is required */
	/* check अगर HW पढ़ोing GSP memory */
	REG_WAIT(VPG_GENERIC_STATUS, VPG_GENERIC_CONFLICT_OCCURED,
			0, 10, max_retries);

	/* HW करोes is not पढ़ोing GSP memory not पढ़ोing too दीर्घ ->
	 * something wrong. clear GPS memory access and notअगरy?
	 * hw SW is writing to GSP memory
	 */
	REG_UPDATE(VPG_GENERIC_STATUS, VPG_GENERIC_CONFLICT_CLR, 1);

	/* choose which generic packet to use */
	REG_UPDATE(VPG_GENERIC_PACKET_ACCESS_CTRL,
			VPG_GENERIC_DATA_INDEX, packet_index*9);

	/* ग_लिखो generic packet header
	 * (4th byte is क्रम GENERIC0 only)
	 */
	REG_SET_4(VPG_GENERIC_PACKET_DATA, 0,
			VPG_GENERIC_DATA_BYTE0, info_packet->hb0,
			VPG_GENERIC_DATA_BYTE1, info_packet->hb1,
			VPG_GENERIC_DATA_BYTE2, info_packet->hb2,
			VPG_GENERIC_DATA_BYTE3, info_packet->hb3);

	/* ग_लिखो generic packet contents
	 * (we never use last 4 bytes)
	 * there are 8 (0-7) mmDIG0_AFMT_GENERIC0_x रेजिस्टरs
	 */
	अणु
		स्थिर uपूर्णांक32_t *content =
			(स्थिर uपूर्णांक32_t *) &info_packet->sb[0];

		क्रम (i = 0; i < 8; i++) अणु
			REG_WRITE(VPG_GENERIC_PACKET_DATA, *content++);
		पूर्ण
	पूर्ण

	/* atomically update द्विगुन-buffered GENERIC0 रेजिस्टरs in immediate mode
	 * (update at next block_update when block_update_lock == 0).
	 */
	चयन (packet_index) अणु
	हाल 0:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC0_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 1:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC1_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 2:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC2_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 3:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC3_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 4:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC4_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 5:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC5_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 6:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC6_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 7:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC7_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 8:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC8_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 9:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC9_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 10:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC10_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 11:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC11_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 12:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC12_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 13:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC13_IMMEDIATE_UPDATE, 1);
		अवरोध;
	हाल 14:
		REG_UPDATE(VPG_GSP_IMMEDIATE_UPDATE_CTRL,
				VPG_GENERIC14_IMMEDIATE_UPDATE, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा vpg_funcs dcn30_vpg_funcs = अणु
	.update_generic_info_packet	= vpg3_update_generic_info_packet,
पूर्ण;

व्योम vpg3_स्थिरruct(काष्ठा dcn30_vpg *vpg3,
	काष्ठा dc_context *ctx,
	uपूर्णांक32_t inst,
	स्थिर काष्ठा dcn30_vpg_रेजिस्टरs *vpg_regs,
	स्थिर काष्ठा dcn30_vpg_shअगरt *vpg_shअगरt,
	स्थिर काष्ठा dcn30_vpg_mask *vpg_mask)
अणु
	vpg3->base.ctx = ctx;

	vpg3->base.inst = inst;
	vpg3->base.funcs = &dcn30_vpg_funcs;

	vpg3->regs = vpg_regs;
	vpg3->vpg_shअगरt = vpg_shअगरt;
	vpg3->vpg_mask = vpg_mask;
पूर्ण
