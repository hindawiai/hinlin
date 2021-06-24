<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "dmub_dcn30.h"

#समावेश "sienna_cichlid_ip_offset.h"
#समावेश "dcn/dcn_3_0_0_offset.h"
#समावेश "dcn/dcn_3_0_0_sh_mask.h"

#घोषणा BASE_INNER(seg) DCN_BASE__INST0_SEG##seg
#घोषणा CTX dmub
#घोषणा REGS dmub->regs

/* Registers. */

स्थिर काष्ठा dmub_srv_common_regs dmub_srv_dcn30_regs = अणु
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

अटल व्योम dmub_dcn30_get_fb_base_offset(काष्ठा dmub_srv *dmub,
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

अटल अंतरभूत व्योम dmub_dcn30_translate_addr(स्थिर जोड़ dmub_addr *addr_in,
					     uपूर्णांक64_t fb_base,
					     uपूर्णांक64_t fb_offset,
					     जोड़ dmub_addr *addr_out)
अणु
	addr_out->quad_part = addr_in->quad_part - fb_base + fb_offset;
पूर्ण

व्योम dmub_dcn30_backकरोor_load(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw0,
			      स्थिर काष्ठा dmub_winकरोw *cw1)
अणु
	जोड़ dmub_addr offset;
	uपूर्णांक64_t fb_base, fb_offset;

	dmub_dcn30_get_fb_base_offset(dmub, &fb_base, &fb_offset);

	REG_UPDATE(DMCUB_SEC_CNTL, DMCUB_SEC_RESET, 1);

	/* MEM_CTNL पढ़ो/ग_लिखो space करोesn't exist. */

	dmub_dcn30_translate_addr(&cw0->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW0_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW0_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW0_BASE_ADDRESS, cw0->region.base);
	REG_SET_2(DMCUB_REGION3_CW0_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW0_TOP_ADDRESS, cw0->region.top,
		  DMCUB_REGION3_CW0_ENABLE, 1);

	dmub_dcn30_translate_addr(&cw1->offset, fb_base, fb_offset, &offset);

	REG_WRITE(DMCUB_REGION3_CW1_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW1_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW1_BASE_ADDRESS, cw1->region.base);
	REG_SET_2(DMCUB_REGION3_CW1_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW1_TOP_ADDRESS, cw1->region.top,
		  DMCUB_REGION3_CW1_ENABLE, 1);

	REG_UPDATE_2(DMCUB_SEC_CNTL, DMCUB_SEC_RESET, 0, DMCUB_MEM_UNIT_ID,
		     0x20);
पूर्ण

व्योम dmub_dcn30_setup_winकरोws(काष्ठा dmub_srv *dmub,
			      स्थिर काष्ठा dmub_winकरोw *cw2,
			      स्थिर काष्ठा dmub_winकरोw *cw3,
			      स्थिर काष्ठा dmub_winकरोw *cw4,
			      स्थिर काष्ठा dmub_winकरोw *cw5,
			      स्थिर काष्ठा dmub_winकरोw *cw6)
अणु
	जोड़ dmub_addr offset;

	/* sienna_cichlid  has hardwired भव addressing क्रम CW2-CW7 */

	offset = cw2->offset;

	अगर (cw2->region.base != cw2->region.top) अणु
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

	offset = cw3->offset;

	REG_WRITE(DMCUB_REGION3_CW3_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW3_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW3_BASE_ADDRESS, cw3->region.base);
	REG_SET_2(DMCUB_REGION3_CW3_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW3_TOP_ADDRESS, cw3->region.top,
		  DMCUB_REGION3_CW3_ENABLE, 1);

	offset = cw4->offset;

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

	offset = cw5->offset;

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

	offset = cw6->offset;

	REG_WRITE(DMCUB_REGION3_CW6_OFFSET, offset.u.low_part);
	REG_WRITE(DMCUB_REGION3_CW6_OFFSET_HIGH, offset.u.high_part);
	REG_WRITE(DMCUB_REGION3_CW6_BASE_ADDRESS, cw6->region.base);
	REG_SET_2(DMCUB_REGION3_CW6_TOP_ADDRESS, 0,
		  DMCUB_REGION3_CW6_TOP_ADDRESS, cw6->region.top,
		  DMCUB_REGION3_CW6_ENABLE, 1);
पूर्ण
