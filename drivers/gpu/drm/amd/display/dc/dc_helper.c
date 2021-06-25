<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 */
/*
 * dc_helper.c
 *
 *  Created on: Aug 30, 2016
 *      Author: agrodzov
 */

#समावेश <linux/delay.h>

#समावेश "dm_services.h"
#समावेश <मानकतर्क.स>

#समावेश "dc.h"
#समावेश "dc_dmub_srv.h"
#समावेश "reg_helper.h"

अटल अंतरभूत व्योम submit_dmub_पढ़ो_modअगरy_ग_लिखो(
	काष्ठा dc_reg_helper_state *offload,
	स्थिर काष्ठा dc_context *ctx)
अणु
	काष्ठा dmub_rb_cmd_पढ़ो_modअगरy_ग_लिखो *cmd_buf = &offload->cmd_data.पढ़ो_modअगरy_ग_लिखो;
	bool gather = false;

	offload->should_burst_ग_लिखो =
			(offload->same_addr_count == (DMUB_READ_MODIFY_WRITE_SEQ__MAX - 1));
	cmd_buf->header.payload_bytes =
			माप(काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence) * offload->reg_seq_count;

	gather = ctx->dmub_srv->reg_helper_offload.gather_in_progress;
	ctx->dmub_srv->reg_helper_offload.gather_in_progress = false;

	dc_dmub_srv_cmd_queue(ctx->dmub_srv, &offload->cmd_data);

	ctx->dmub_srv->reg_helper_offload.gather_in_progress = gather;

	स_रखो(cmd_buf, 0, माप(*cmd_buf));

	offload->reg_seq_count = 0;
	offload->same_addr_count = 0;
पूर्ण

अटल अंतरभूत व्योम submit_dmub_burst_ग_लिखो(
	काष्ठा dc_reg_helper_state *offload,
	स्थिर काष्ठा dc_context *ctx)
अणु
	काष्ठा dmub_rb_cmd_burst_ग_लिखो *cmd_buf = &offload->cmd_data.burst_ग_लिखो;
	bool gather = false;

	cmd_buf->header.payload_bytes =
			माप(uपूर्णांक32_t) * offload->reg_seq_count;

	gather = ctx->dmub_srv->reg_helper_offload.gather_in_progress;
	ctx->dmub_srv->reg_helper_offload.gather_in_progress = false;

	dc_dmub_srv_cmd_queue(ctx->dmub_srv, &offload->cmd_data);

	ctx->dmub_srv->reg_helper_offload.gather_in_progress = gather;

	स_रखो(cmd_buf, 0, माप(*cmd_buf));

	offload->reg_seq_count = 0;
पूर्ण

अटल अंतरभूत व्योम submit_dmub_reg_रुको(
		काष्ठा dc_reg_helper_state *offload,
		स्थिर काष्ठा dc_context *ctx)
अणु
	काष्ठा dmub_rb_cmd_reg_रुको *cmd_buf = &offload->cmd_data.reg_रुको;
	bool gather = false;

	gather = ctx->dmub_srv->reg_helper_offload.gather_in_progress;
	ctx->dmub_srv->reg_helper_offload.gather_in_progress = false;

	dc_dmub_srv_cmd_queue(ctx->dmub_srv, &offload->cmd_data);

	स_रखो(cmd_buf, 0, माप(*cmd_buf));
	offload->reg_seq_count = 0;

	ctx->dmub_srv->reg_helper_offload.gather_in_progress = gather;
पूर्ण

काष्ठा dc_reg_value_masks अणु
	uपूर्णांक32_t value;
	uपूर्णांक32_t mask;
पूर्ण;

काष्ठा dc_reg_sequence अणु
	uपूर्णांक32_t addr;
	काष्ठा dc_reg_value_masks value_masks;
पूर्ण;

अटल अंतरभूत व्योम set_reg_field_value_masks(
	काष्ठा dc_reg_value_masks *field_value_mask,
	uपूर्णांक32_t value,
	uपूर्णांक32_t mask,
	uपूर्णांक8_t shअगरt)
अणु
	ASSERT(mask != 0);

	field_value_mask->value = (field_value_mask->value & ~mask) | (mask & (value << shअगरt));
	field_value_mask->mask = field_value_mask->mask | mask;
पूर्ण

अटल व्योम set_reg_field_values(काष्ठा dc_reg_value_masks *field_value_mask,
		uपूर्णांक32_t addr, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
		बहु_सूची ap)
अणु
	uपूर्णांक32_t shअगरt, mask, field_value;
	पूर्णांक i = 1;

	/* gather all bits value/mask getting updated in this रेजिस्टर */
	set_reg_field_value_masks(field_value_mask,
			field_value1, mask1, shअगरt1);

	जबतक (i < n) अणु
		shअगरt = बहु_तर्क(ap, uपूर्णांक32_t);
		mask = बहु_तर्क(ap, uपूर्णांक32_t);
		field_value = बहु_तर्क(ap, uपूर्णांक32_t);

		set_reg_field_value_masks(field_value_mask,
				field_value, mask, shअगरt);
		i++;
	पूर्ण
पूर्ण

अटल व्योम dmub_flush_buffer_execute(
		काष्ठा dc_reg_helper_state *offload,
		स्थिर काष्ठा dc_context *ctx)
अणु
	submit_dmub_पढ़ो_modअगरy_ग_लिखो(offload, ctx);
	dc_dmub_srv_cmd_execute(ctx->dmub_srv);
पूर्ण

अटल व्योम dmub_flush_burst_ग_लिखो_buffer_execute(
		काष्ठा dc_reg_helper_state *offload,
		स्थिर काष्ठा dc_context *ctx)
अणु
	submit_dmub_burst_ग_लिखो(offload, ctx);
	dc_dmub_srv_cmd_execute(ctx->dmub_srv);
पूर्ण

अटल bool dmub_reg_value_burst_set_pack(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक32_t reg_val)
अणु
	काष्ठा dc_reg_helper_state *offload = &ctx->dmub_srv->reg_helper_offload;
	काष्ठा dmub_rb_cmd_burst_ग_लिखो *cmd_buf = &offload->cmd_data.burst_ग_लिखो;

	/* flush command अगर buffer is full */
	अगर (offload->reg_seq_count == DMUB_BURST_WRITE_VALUES__MAX)
		dmub_flush_burst_ग_लिखो_buffer_execute(offload, ctx);

	अगर (offload->cmd_data.cmd_common.header.type == DMUB_CMD__REG_SEQ_BURST_WRITE &&
			addr != cmd_buf->addr) अणु
		dmub_flush_burst_ग_लिखो_buffer_execute(offload, ctx);
		वापस false;
	पूर्ण

	cmd_buf->header.type = DMUB_CMD__REG_SEQ_BURST_WRITE;
	cmd_buf->header.sub_type = 0;
	cmd_buf->addr = addr;
	cmd_buf->ग_लिखो_values[offload->reg_seq_count] = reg_val;
	offload->reg_seq_count++;

	वापस true;
पूर्ण

अटल uपूर्णांक32_t dmub_reg_value_pack(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		काष्ठा dc_reg_value_masks *field_value_mask)
अणु
	काष्ठा dc_reg_helper_state *offload = &ctx->dmub_srv->reg_helper_offload;
	काष्ठा dmub_rb_cmd_पढ़ो_modअगरy_ग_लिखो *cmd_buf = &offload->cmd_data.पढ़ो_modअगरy_ग_लिखो;
	काष्ठा dmub_cmd_पढ़ो_modअगरy_ग_लिखो_sequence *seq;

	/* flush command अगर buffer is full */
	अगर (offload->cmd_data.cmd_common.header.type != DMUB_CMD__REG_SEQ_BURST_WRITE &&
			offload->reg_seq_count == DMUB_READ_MODIFY_WRITE_SEQ__MAX)
		dmub_flush_buffer_execute(offload, ctx);

	अगर (offload->should_burst_ग_लिखो) अणु
		अगर (dmub_reg_value_burst_set_pack(ctx, addr, field_value_mask->value))
			वापस field_value_mask->value;
		अन्यथा
			offload->should_burst_ग_लिखो = false;
	पूर्ण

	/* pack commands */
	cmd_buf->header.type = DMUB_CMD__REG_SEQ_READ_MODIFY_WRITE;
	cmd_buf->header.sub_type = 0;
	seq = &cmd_buf->seq[offload->reg_seq_count];

	अगर (offload->reg_seq_count) अणु
		अगर (cmd_buf->seq[offload->reg_seq_count - 1].addr == addr)
			offload->same_addr_count++;
		अन्यथा
			offload->same_addr_count = 0;
	पूर्ण

	seq->addr = addr;
	seq->modअगरy_mask = field_value_mask->mask;
	seq->modअगरy_value = field_value_mask->value;
	offload->reg_seq_count++;

	वापस field_value_mask->value;
पूर्ण

अटल व्योम dmub_reg_रुको_करोne_pack(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक32_t mask, uपूर्णांक32_t shअगरt, uपूर्णांक32_t condition_value, uपूर्णांक32_t समय_out_us)
अणु
	काष्ठा dc_reg_helper_state *offload = &ctx->dmub_srv->reg_helper_offload;
	काष्ठा dmub_rb_cmd_reg_रुको *cmd_buf = &offload->cmd_data.reg_रुको;

	cmd_buf->header.type = DMUB_CMD__REG_REG_WAIT;
	cmd_buf->header.sub_type = 0;
	cmd_buf->reg_रुको.addr = addr;
	cmd_buf->reg_रुको.condition_field_value = mask & (condition_value << shअगरt);
	cmd_buf->reg_रुको.mask = mask;
	cmd_buf->reg_रुको.समय_out_us = समय_out_us;
पूर्ण

uपूर्णांक32_t generic_reg_update_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
		...)
अणु
	काष्ठा dc_reg_value_masks field_value_mask = अणु0पूर्ण;
	uपूर्णांक32_t reg_val;
	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);

	set_reg_field_values(&field_value_mask, addr, n, shअगरt1, mask1,
			field_value1, ap);

	बहु_पूर्ण(ap);

	अगर (ctx->dmub_srv &&
	    ctx->dmub_srv->reg_helper_offload.gather_in_progress)
		वापस dmub_reg_value_pack(ctx, addr, &field_value_mask);
		/* toकरो: वापस व्योम so we can decouple code running in driver from रेजिस्टर states */

	/* mmio ग_लिखो directly */
	reg_val = dm_पढ़ो_reg(ctx, addr);
	reg_val = (reg_val & ~field_value_mask.mask) | field_value_mask.value;
	dm_ग_लिखो_reg(ctx, addr, reg_val);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_set_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr, uपूर्णांक32_t reg_val, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
		...)
अणु
	काष्ठा dc_reg_value_masks field_value_mask = अणु0पूर्ण;
	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);

	set_reg_field_values(&field_value_mask, addr, n, shअगरt1, mask1,
			field_value1, ap);

	बहु_पूर्ण(ap);


	/* mmio ग_लिखो directly */
	reg_val = (reg_val & ~field_value_mask.mask) | field_value_mask.value;

	अगर (ctx->dmub_srv &&
	    ctx->dmub_srv->reg_helper_offload.gather_in_progress) अणु
		वापस dmub_reg_value_burst_set_pack(ctx, addr, reg_val);
		/* toकरो: वापस व्योम so we can decouple code running in driver from रेजिस्टर states */
	पूर्ण

	dm_ग_लिखो_reg(ctx, addr, reg_val);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt, uपूर्णांक32_t mask, uपूर्णांक32_t *field_value)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value = get_reg_field_value_ex(reg_val, mask, shअगरt);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get2(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get3(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get4(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shअगरt4);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get5(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shअगरt4);
	*field_value5 = get_reg_field_value_ex(reg_val, mask5, shअगरt5);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get6(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shअगरt4);
	*field_value5 = get_reg_field_value_ex(reg_val, mask5, shअगरt5);
	*field_value6 = get_reg_field_value_ex(reg_val, mask6, shअगरt6);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get7(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6,
		uपूर्णांक8_t shअगरt7, uपूर्णांक32_t mask7, uपूर्णांक32_t *field_value7)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shअगरt4);
	*field_value5 = get_reg_field_value_ex(reg_val, mask5, shअगरt5);
	*field_value6 = get_reg_field_value_ex(reg_val, mask6, shअगरt6);
	*field_value7 = get_reg_field_value_ex(reg_val, mask7, shअगरt7);
	वापस reg_val;
पूर्ण

uपूर्णांक32_t generic_reg_get8(स्थिर काष्ठा dc_context *ctx, uपूर्णांक32_t addr,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		uपूर्णांक8_t shअगरt2, uपूर्णांक32_t mask2, uपूर्णांक32_t *field_value2,
		uपूर्णांक8_t shअगरt3, uपूर्णांक32_t mask3, uपूर्णांक32_t *field_value3,
		uपूर्णांक8_t shअगरt4, uपूर्णांक32_t mask4, uपूर्णांक32_t *field_value4,
		uपूर्णांक8_t shअगरt5, uपूर्णांक32_t mask5, uपूर्णांक32_t *field_value5,
		uपूर्णांक8_t shअगरt6, uपूर्णांक32_t mask6, uपूर्णांक32_t *field_value6,
		uपूर्णांक8_t shअगरt7, uपूर्णांक32_t mask7, uपूर्णांक32_t *field_value7,
		uपूर्णांक8_t shअगरt8, uपूर्णांक32_t mask8, uपूर्णांक32_t *field_value8)
अणु
	uपूर्णांक32_t reg_val = dm_पढ़ो_reg(ctx, addr);
	*field_value1 = get_reg_field_value_ex(reg_val, mask1, shअगरt1);
	*field_value2 = get_reg_field_value_ex(reg_val, mask2, shअगरt2);
	*field_value3 = get_reg_field_value_ex(reg_val, mask3, shअगरt3);
	*field_value4 = get_reg_field_value_ex(reg_val, mask4, shअगरt4);
	*field_value5 = get_reg_field_value_ex(reg_val, mask5, shअगरt5);
	*field_value6 = get_reg_field_value_ex(reg_val, mask6, shअगरt6);
	*field_value7 = get_reg_field_value_ex(reg_val, mask7, shअगरt7);
	*field_value8 = get_reg_field_value_ex(reg_val, mask8, shअगरt8);
	वापस reg_val;
पूर्ण
/* note:  va version of this is pretty bad idea, since there is a output parameter pass by poपूर्णांकer
 * compiler won't be able to check क्रम size match and is prone to stack corruption type of bugs

uपूर्णांक32_t generic_reg_get(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr, पूर्णांक n, ...)
अणु
	uपूर्णांक32_t shअगरt, mask;
	uपूर्णांक32_t *field_value;
	uपूर्णांक32_t reg_val;
	पूर्णांक i = 0;

	reg_val = dm_पढ़ो_reg(ctx, addr);

	बहु_सूची ap;
	बहु_शुरू(ap, n);

	जबतक (i < n) अणु
		shअगरt = बहु_तर्क(ap, uपूर्णांक32_t);
		mask = बहु_तर्क(ap, uपूर्णांक32_t);
		field_value = बहु_तर्क(ap, uपूर्णांक32_t *);

		*field_value = get_reg_field_value_ex(reg_val, mask, shअगरt);
		i++;
	पूर्ण

	बहु_पूर्ण(ap);

	वापस reg_val;
पूर्ण
*/

व्योम generic_reg_रुको(स्थिर काष्ठा dc_context *ctx,
	uपूर्णांक32_t addr, uपूर्णांक32_t shअगरt, uपूर्णांक32_t mask, uपूर्णांक32_t condition_value,
	अचिन्हित पूर्णांक delay_between_poll_us, अचिन्हित पूर्णांक समय_out_num_tries,
	स्थिर अक्षर *func_name, पूर्णांक line)
अणु
	uपूर्णांक32_t field_value;
	uपूर्णांक32_t reg_val;
	पूर्णांक i;

	अगर (ctx->dmub_srv &&
	    ctx->dmub_srv->reg_helper_offload.gather_in_progress) अणु
		dmub_reg_रुको_करोne_pack(ctx, addr, mask, shअगरt, condition_value,
				delay_between_poll_us * समय_out_num_tries);
		वापस;
	पूर्ण

	/*
	 * Something is terribly wrong अगर समय out is > 3000ms.
	 * 3000ms is the maximum समय needed क्रम SMU to pass values back.
	 * This value comes from experiments.
	 *
	 */
	ASSERT(delay_between_poll_us * समय_out_num_tries <= 3000000);

	क्रम (i = 0; i <= समय_out_num_tries; i++) अणु
		अगर (i) अणु
			अगर (delay_between_poll_us >= 1000)
				msleep(delay_between_poll_us/1000);
			अन्यथा अगर (delay_between_poll_us > 0)
				udelay(delay_between_poll_us);
		पूर्ण

		reg_val = dm_पढ़ो_reg(ctx, addr);

		field_value = get_reg_field_value_ex(reg_val, mask, shअगरt);

		अगर (field_value == condition_value) अणु
			अगर (i * delay_between_poll_us > 1000 &&
					!IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
				DC_LOG_DC("REG_WAIT taking a while: %dms in %s line:%d\n",
						delay_between_poll_us * i / 1000,
						func_name, line);
			वापस;
		पूर्ण
	पूर्ण

	DC_LOG_WARNING("REG_WAIT timeout %dus * %d tries - %s line:%d\n",
			delay_between_poll_us, समय_out_num_tries,
			func_name, line);

	अगर (!IS_FPGA_MAXIMUS_DC(ctx->dce_environment))
		BREAK_TO_DEBUGGER();
पूर्ण

व्योम generic_ग_लिखो_indirect_reg(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, uपूर्णांक32_t data)
अणु
	dm_ग_लिखो_reg(ctx, addr_index, index);
	dm_ग_लिखो_reg(ctx, addr_data, data);
पूर्ण

uपूर्णांक32_t generic_पढ़ो_indirect_reg(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index)
अणु
	uपूर्णांक32_t value = 0;

	// when reg पढ़ो, there should not be any offload.
	अगर (ctx->dmub_srv &&
	    ctx->dmub_srv->reg_helper_offload.gather_in_progress) अणु
		ASSERT(false);
	पूर्ण

	dm_ग_लिखो_reg(ctx, addr_index, index);
	value = dm_पढ़ो_reg(ctx, addr_data);

	वापस value;
पूर्ण

uपूर्णांक32_t generic_indirect_reg_get(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t *field_value1,
		...)
अणु
	uपूर्णांक32_t shअगरt, mask, *field_value;
	uपूर्णांक32_t value = 0;
	पूर्णांक i = 1;

	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);

	value = generic_पढ़ो_indirect_reg(ctx, addr_index, addr_data, index);
	*field_value1 = get_reg_field_value_ex(value, mask1, shअगरt1);

	जबतक (i < n) अणु
		shअगरt = बहु_तर्क(ap, uपूर्णांक32_t);
		mask = बहु_तर्क(ap, uपूर्णांक32_t);
		field_value = बहु_तर्क(ap, uपूर्णांक32_t *);

		*field_value = get_reg_field_value_ex(value, mask, shअगरt);
		i++;
	पूर्ण

	बहु_पूर्ण(ap);

	वापस value;
पूर्ण

uपूर्णांक32_t generic_indirect_reg_update_ex(स्थिर काष्ठा dc_context *ctx,
		uपूर्णांक32_t addr_index, uपूर्णांक32_t addr_data,
		uपूर्णांक32_t index, uपूर्णांक32_t reg_val, पूर्णांक n,
		uपूर्णांक8_t shअगरt1, uपूर्णांक32_t mask1, uपूर्णांक32_t field_value1,
		...)
अणु
	uपूर्णांक32_t shअगरt, mask, field_value;
	पूर्णांक i = 1;

	बहु_सूची ap;

	बहु_शुरू(ap, field_value1);

	reg_val = set_reg_field_value_ex(reg_val, field_value1, mask1, shअगरt1);

	जबतक (i < n) अणु
		shअगरt = बहु_तर्क(ap, uपूर्णांक32_t);
		mask = बहु_तर्क(ap, uपूर्णांक32_t);
		field_value = बहु_तर्क(ap, uपूर्णांक32_t);

		reg_val = set_reg_field_value_ex(reg_val, field_value, mask, shअगरt);
		i++;
	पूर्ण

	generic_ग_लिखो_indirect_reg(ctx, addr_index, addr_data, index, reg_val);
	बहु_पूर्ण(ap);

	वापस reg_val;
पूर्ण

व्योम reg_sequence_start_gather(स्थिर काष्ठा dc_context *ctx)
अणु
	/* अगर reg sequence is supported and enabled, set flag to
	 * indicate we want to have REG_SET, REG_UPDATE macro build
	 * reg sequence command buffer rather than MMIO directly.
	 */

	अगर (ctx->dmub_srv && ctx->dc->debug.dmub_offload_enabled) अणु
		काष्ठा dc_reg_helper_state *offload =
			&ctx->dmub_srv->reg_helper_offload;

		/* caller sequence mismatch.  need to debug caller.  offload will not work!!! */
		ASSERT(!offload->gather_in_progress);

		offload->gather_in_progress = true;
	पूर्ण
पूर्ण

व्योम reg_sequence_start_execute(स्थिर काष्ठा dc_context *ctx)
अणु
	काष्ठा dc_reg_helper_state *offload;

	अगर (!ctx->dmub_srv)
		वापस;

	offload = &ctx->dmub_srv->reg_helper_offload;

	अगर (offload && offload->gather_in_progress) अणु
		offload->gather_in_progress = false;
		offload->should_burst_ग_लिखो = false;
		चयन (offload->cmd_data.cmd_common.header.type) अणु
		हाल DMUB_CMD__REG_SEQ_READ_MODIFY_WRITE:
			submit_dmub_पढ़ो_modअगरy_ग_लिखो(offload, ctx);
			अवरोध;
		हाल DMUB_CMD__REG_REG_WAIT:
			submit_dmub_reg_रुको(offload, ctx);
			अवरोध;
		हाल DMUB_CMD__REG_SEQ_BURST_WRITE:
			submit_dmub_burst_ग_लिखो(offload, ctx);
			अवरोध;
		शेष:
			वापस;
		पूर्ण

		dc_dmub_srv_cmd_execute(ctx->dmub_srv);
	पूर्ण
पूर्ण

व्योम reg_sequence_रुको_करोne(स्थिर काष्ठा dc_context *ctx)
अणु
	/* callback to DM to poll क्रम last submission करोne*/
	काष्ठा dc_reg_helper_state *offload;

	अगर (!ctx->dmub_srv)
		वापस;

	offload = &ctx->dmub_srv->reg_helper_offload;

	अगर (offload &&
	    ctx->dc->debug.dmub_offload_enabled &&
	    !ctx->dc->debug.dmcub_emulation) अणु
		dc_dmub_srv_रुको_idle(ctx->dmub_srv);
	पूर्ण
पूर्ण
