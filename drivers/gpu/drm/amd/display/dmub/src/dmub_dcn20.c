<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
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

#समावेश "../dmub_srv.h"
#समावेश "dmub_reg.h"
#समावेश "dmub_dcn20.h"

#समावेश "dcn/dcn_2_0_0_offset.h"
#समावेश "dcn/dcn_2_0_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#घोषणा BASE_INNER(seg) DCN_BASE__INST0_SEG##seg
#घोषणा CTX dmub
#घोषणा REGS dmub->regs

/* Registers. */

स्थिर काष्ठा dmub_srv_common_regs dmub_srv_dcn20_regs = अणु
#घोषणा DMUB_SR(reg) REG_OFFSET(reg),
	अणु DMUB_COMMON_REGS() पूर्ण,
#अघोषित DMUB_SR

#घोषणा DMUB_SF(reg, field) FD_MASK(reg, field),
	अणु DMUB_COMMON_FIELDS() पूर्ण,
#अघोषित DMUB_SF

#घोषणा DMUB_SF(reg, field) FD_SHIFT(reg, field),
	अणु DMUB_COMMON_FIELDS() पूर्ण,
#अघोषित DMUB_SF
पूर्ण;

/* Shared functions. */

अटल व्योम dmub_dcn20_get_fb_base_offset(काष्ठा dmub_srv *dmub,
					  uपूर्णांक64_t *fb_base,
					  uपूर्णांक64_t *fb_offset)
अणु
	uपूर्णांक32_t पंचांगp;

	अगर (dmub->fb_base || dmub->fb_offset) अणु
		*fb_base = dmub->fb_base;
		*fb_offset = dmub->fb_offset;
		वापस;
	पूर्ण

	REG_GET(DCN_VM_FB_LOCATION_BASE, FB_BASE, &पंचांगp);
	*fb_base = (uपूर्णांक64_t)पंचांगp << 24;

	REG_GET(DCN_VM_FB_OFFSET, FB_OFFSET, &पंचांगp);
	*fb_offset = (uपूर्णांक64_t)पंचांगp << 24;
पूर्ण

अटल अंतरभूत व्योम dmub_dcn20_translate_addr(स्थिर जोड़ dmub_addr *addr_in,
					     uपूर्णांक64_t fb_base,
					     uपूर्णांक64_t fb_offset,
					     जोड़ dmub_addr *addr_out)
अणु
	addr_out->quad_part = addr_in->quad_part - fb_base + fb_offset;
पूर्ण

bool dmub_dcn20_use_cached_inbox(काष्ठा dmub_srv *dmub)
अणु
	/* Cached inbox is not supported in this fw version range */
	वापस !(dmub->fw_version >= DMUB_FW_VERSION(1, 0, 0) &&
		 dmub->fw_version <= DMUB_FW_VERSION(1, 10, 0));
पूर्ण

व्योम dmub_dcn20_reset(काष्ठा dmub_srv *dmub)
अणु
	जोड़ dmub_gpपूर्णांक_data_रेजिस्टर cmd;
	स्थिर uपूर्णांक32_t समयout = 30;
	uपूर्णांक32_t in_reset, scratch, i;

	REG_GET(DMCUB_CNTL, DMCUB_SOFT_RESET, &in_reset);

	अगर (in_reset == 0) अणु
		cmd.bits.status = 1;
		cmd.bits.command_code = DMUB_GPINT__STOP_FW;
		cmd.bits.param = 0;

		dmub->hw_funcs.set_gpपूर्णांक(dmub, cmd);

		/**
		 * Timeout covers both the ACK and the रुको
		 * क्रम reमुख्यing work to finish.
		 *
		 * This is mostly bound by the PHY disable sequence.
		 * Each रेजिस्टर check will be greater than 1us, so
		 * करोn't bother using udelay.
		 */

		क्रम (i = 0; i < समयout; ++i) अणु
			अगर (dmub->hw_funcs.is_gpपूर्णांक_acked(dmub, cmd))
				अवरोध;
		पूर्ण

		क्रम (i = 0; i < समयout; ++i) अणु
			scratch = dmub->hw_funcs.get_gpपूर्णांक_response(dmub);
			अगर (scratch == DMUB_GPINT__STOP_FW_RESPONSE)
				अवरोध;
		पूर्ण

		/* Clear the GPINT command manually so we करोn't reset again. */
		cmd.all = 0;
		dmub->hw_funcs.set_gpपूर्णांक(dmub, cmd);

		/* Force reset in हाल we समयd out, DMCUB is likely hung. */
	पूर्ण

	REG_UPDATE(DMCUB_CNTL, DMCUB_SOFT_RESET, 1);
	REG_UPDATE(DMCUB_CNTL, DMCUB_ENABLE, 0);
	REG_UPDATE(MMHUBBUB_SOFT_RESET, DMUIF_SOFT_RESET, 1);
	REG_WRITE(DMCUB_INBOX1_RPTR, 0);
	REG_WRITE(DMCUB_INBOX1_WPTR, 0);
	REG_WRITE(DMCUB_OUTBOX1_RPTR, 0);
	REG_WRITE(DMCUB_OUTBOX1_WPTR, 0);
	REG_WRITE(DMCUB_SCRATCH0, 0);
पूर्ण

व्योम dmub_dcn20_reset_release(काष्ठा dmub_srv *dmub)
अणु
	REG_UPDATE(MMHUBBUB_SOFT_RESET, DMUIF_SOFT_RESET, 0);
	REG_WRITE(DMCUB_SCRATCH15, dmub->psp_version & 0x001100FF);
	REG_UPDATE_2(DMCUB_CNTL, DMCUB_ENABLE, 1, DMCUB_TRACEPORT_EN, 1);
	REG_UPDATE(DMCUB_CNTL, DMCUB_SOFT_RESET, 0);
पूर्ण

व्योम dmub_dcn20_backकरोor_load(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw0,
			      स्थिर काष्ठा dmub_winकरोw *cw1)
अणु
	जोड़ dmub_addr offset;
	uपूर्णांक64_t fb_base, fb_offset;

	dmub_dcn20_get_fb_base_offset(dmub, &fb_base, &fb_offset);

	REG_UPDATE(DMCUB_SEC_CNTL, DMCUB_SEC_RESET, 1);
	REG_UPDATE_2(DMCUB_MEM_CNTL, DMCUB_MEM_READ_SPACE, 0x3,
		     DMCUB_MEM_WRITE_SPACE, 0x3);

	dmub_dcn20_translate_addr(&cw0->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW0_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW0_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW0_BASE_ADDRESS, cw0->region.base);
	REG_SET_2(DMCUB_REGION3_CW0_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW0_TOP_ADDRESS, cw0->region.top,
		  DMCUB_REGION3_CW0_ENABLE, 1);

	dmub_dcn20_translate_addr(&cw1->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW1_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW1_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW1_BASE_ADDRESS, cw1->region.base);
	REG_SET_2(DMCUB_REGION3_CW1_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW1_TOP_ADDRESS, cw1->region.top,
		  DMCUB_REGION3_CW1_ENABLE, 1);

	REG_UPDATE_2(DMCUB_SEC_CNTL, DMCUB_SEC_RESET, 0, DMCUB_MEM_UNIT_ID,
		     0x20);
पूर्ण

व्योम dmub_dcn20_setup_winकरोws(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw2,
			      स्थिर काष्ठा dmub_winकरोw *cw3,
			      स्थिर काष्ठा dmub_winकरोw *cw4,
			      स्थिर काष्ठा dmub_winकरोw *cw5,
			      स्थिर काष्ठा dmub_winकरोw *cw6)
अणु
	जोड़ dmub_addr offset;
	uपूर्णांक64_t fb_base, fb_offset;

	dmub_dcn20_get_fb_base_offset(dmub, &fb_base, &fb_offset);

	अगर (cw2->region.base != cw2->region.top) अणु
		dmub_dcn20_translate_addr(&cw2->offset, fb_base, fb_offset,
					  &offset);

		REG_WRITE(DMCUB_REGION3_CW2_OFFSET, offset.u.low_part);
		REG_WRITE(DMCUB_REGION3_CW2_OFFSET_HIGH, offset.u.high_part);
		REG_WRITE(DMCUB_REGION3_CW2_BASE_ADDRESS, cw2->region.base);
		REG_SET_2(DMCUB_REGION3_CW2_TOP_ADDRESS, 0,
			  DMCUB_REGION3_CW2_TOP_ADDRESS, cw2->region.top,
			  DMCUB_REGION3_CW2_ENABLE, 1);
	पूर्ण अन्यथा अणु
		REG_WRITE(DMCUB_REGION3_CW2_OFFSET, 0);
		REG_WRITE(DMCUB_REGION3_CW2_OFFSET_HIGH, 0);
		REG_WRITE(DMCUB_REGION3_CW2_BASE_ADDRESS, 0);
		REG_WRITE(DMCUB_REGION3_CW2_TOP_ADDRESS, 0);
	पूर्ण

	dmub_dcn20_translate_addr(&cw3->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW3_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW3_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW3_BASE_ADDRESS, cw3->region.base);
	REG_SET_2(DMCUB_REGION3_CW3_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW3_TOP_ADDRESS, cw3->region.top,
		  DMCUB_REGION3_CW3_ENABLE, 1);

	/* TODO: Move this to CW4. */
	dmub_dcn20_translate_addr(&cw4->offset, fb_base, fb_offset, &offset);

	/* New firmware can support CW4. */
	अगर (dmub_dcn20_use_cached_inbox(dmub)) अणु
		REG_WRITE(DMCUB_REGION3_CW4_OFFSET, offset.u.low_part);
		REG_WRITE(DMCUB_REGION3_CW4_OFFSET_HIGH, offset.u.high_part);
		REG_WRITE(DMCUB_REGION3_CW4_BASE_ADDRESS, cw4->region.base);
		REG_SET_2(DMCUB_REGION3_CW4_TOP_ADDRESS, 0,
			  DMCUB_REGION3_CW4_TOP_ADDRESS, cw4->region.top,
			  DMCUB_REGION3_CW4_ENABLE, 1);
	पूर्ण अन्यथा अणु
		REG_WRITE(DMCUB_REGION4_OFFSET, offset.u.low_part);
		REG_WRITE(DMCUB_REGION4_OFFSET_HIGH, offset.u.high_part);
		REG_SET_2(DMCUB_REGION4_TOP_ADDRESS, 0,
			  DMCUB_REGION4_TOP_ADDRESS,
			  cw4->region.top - cw4->region.base - 1,
			  DMCUB_REGION4_ENABLE, 1);
	पूर्ण

	dmub_dcn20_translate_addr(&cw5->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW5_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW5_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW5_BASE_ADDRESS, cw5->region.base);
	REG_SET_2(DMCUB_REGION3_CW5_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW5_TOP_ADDRESS, cw5->region.top,
		  DMCUB_REGION3_CW5_ENABLE, 1);

	REG_WRITE(DMCUB_REGION5_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION5_OFFSET_HIGH, offset.u.high_part);
	REG_SET_2(DMCUB_REGION5_TOP_ADDRESS, 0,
		  DMCUB_REGION5_TOP_ADDRESS,
		  cw5->region.top - cw5->region.base - 1,
		  DMCUB_REGION5_ENABLE, 1);

	dmub_dcn20_translate_addr(&cw6->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW6_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW6_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW6_BASE_ADDRESS, cw6->region.base);
	REG_SET_2(DMCUB_REGION3_CW6_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW6_TOP_ADDRESS, cw6->region.top,
		  DMCUB_REGION3_CW6_ENABLE, 1);
पूर्ण

व्योम dmub_dcn20_setup_mailbox(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *inbox1)
अणु
	/* New firmware can support CW4 क्रम the inbox. */
	अगर (dmub_dcn20_use_cached_inbox(dmub))
		REG_WRITE(DMCUB_INBOX1_BASE_ADDRESS, inbox1->base);
	अन्यथा
		REG_WRITE(DMCUB_INBOX1_BASE_ADDRESS, 0x80000000);

	REG_WRITE(DMCUB_INBOX1_SIZE, inbox1->top - inbox1->base);
पूर्ण

uपूर्णांक32_t dmub_dcn20_get_inbox1_rptr(काष्ठा dmub_srv *dmub)
अणु
	वापस REG_READ(DMCUB_INBOX1_RPTR);
पूर्ण

व्योम dmub_dcn20_set_inbox1_wptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t wptr_offset)
अणु
	REG_WRITE(DMCUB_INBOX1_WPTR, wptr_offset);
पूर्ण

व्योम dmub_dcn20_setup_out_mailbox(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox1)
अणु
	/* New firmware can support CW4 क्रम the outbox. */
	अगर (dmub_dcn20_use_cached_inbox(dmub))
		REG_WRITE(DMCUB_OUTBOX1_BASE_ADDRESS, outbox1->base);
	अन्यथा
		REG_WRITE(DMCUB_OUTBOX1_BASE_ADDRESS, 0x80002000);

	REG_WRITE(DMCUB_OUTBOX1_SIZE, outbox1->top - outbox1->base);
पूर्ण

uपूर्णांक32_t dmub_dcn20_get_outbox1_wptr(काष्ठा dmub_srv *dmub)
अणु
	/**
	 * outbox1 wptr रेजिस्टर is accessed without locks (dal & dc)
	 * and to be called only by dmub_srv_stat_get_notअगरication()
	 */
	वापस REG_READ(DMCUB_OUTBOX1_WPTR);
पूर्ण

व्योम dmub_dcn20_set_outbox1_rptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset)
अणु
	/**
	 * outbox1 rptr रेजिस्टर is accessed without locks (dal & dc)
	 * and to be called only by dmub_srv_stat_get_notअगरication()
	 */
	REG_WRITE(DMCUB_OUTBOX1_RPTR, rptr_offset);
पूर्ण

व्योम dmub_dcn20_setup_outbox0(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_region *outbox0)
अणु
	REG_WRITE(DMCUB_OUTBOX0_BASE_ADDRESS, outbox0->base);

	REG_WRITE(DMCUB_OUTBOX0_SIZE, outbox0->top - outbox0->base);
पूर्ण

uपूर्णांक32_t dmub_dcn20_get_outbox0_wptr(काष्ठा dmub_srv *dmub)
अणु
	वापस REG_READ(DMCUB_OUTBOX0_WPTR);
पूर्ण

व्योम dmub_dcn20_set_outbox0_rptr(काष्ठा dmub_srv *dmub, uपूर्णांक32_t rptr_offset)
अणु
	REG_WRITE(DMCUB_OUTBOX0_RPTR, rptr_offset);
पूर्ण

bool dmub_dcn20_is_hw_init(काष्ठा dmub_srv *dmub)
अणु
	uपूर्णांक32_t is_hw_init;

	REG_GET(DMCUB_CNTL, DMCUB_ENABLE, &is_hw_init);

	वापस is_hw_init != 0;
पूर्ण

bool dmub_dcn20_is_supported(काष्ठा dmub_srv *dmub)
अणु
	uपूर्णांक32_t supported = 0;

	REG_GET(CC_DC_PIPE_DIS, DC_DMCUB_ENABLE, &supported);

	वापस supported;
पूर्ण

व्योम dmub_dcn20_set_gpपूर्णांक(काष्ठा dmub_srv *dmub,
			  जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg)
अणु
	REG_WRITE(DMCUB_GPINT_DATAIN1, reg.all);
पूर्ण

bool dmub_dcn20_is_gpपूर्णांक_acked(काष्ठा dmub_srv *dmub,
			       जोड़ dmub_gpपूर्णांक_data_रेजिस्टर reg)
अणु
	जोड़ dmub_gpपूर्णांक_data_रेजिस्टर test;

	reg.bits.status = 0;
	test.all = REG_READ(DMCUB_GPINT_DATAIN1);

	वापस test.all == reg.all;
पूर्ण

uपूर्णांक32_t dmub_dcn20_get_gpपूर्णांक_response(काष्ठा dmub_srv *dmub)
अणु
	वापस REG_READ(DMCUB_SCRATCH7);
पूर्ण

जोड़ dmub_fw_boot_status dmub_dcn20_get_fw_boot_status(काष्ठा dmub_srv *dmub)
अणु
	जोड़ dmub_fw_boot_status status;

	status.all = REG_READ(DMCUB_SCRATCH0);
	वापस status;
पूर्ण

व्योम dmub_dcn20_enable_dmub_boot_options(काष्ठा dmub_srv *dmub)
अणु
	जोड़ dmub_fw_boot_options boot_options = अणु0पूर्ण;

	REG_WRITE(DMCUB_SCRATCH14, boot_options.all);
पूर्ण

व्योम dmub_dcn20_skip_dmub_panel_घातer_sequence(काष्ठा dmub_srv *dmub, bool skip)
अणु
	जोड़ dmub_fw_boot_options boot_options;
	boot_options.all = REG_READ(DMCUB_SCRATCH14);
	boot_options.bits.skip_phy_init_panel_sequence = skip;
	REG_WRITE(DMCUB_SCRATCH14, boot_options.all);
पूर्ण
