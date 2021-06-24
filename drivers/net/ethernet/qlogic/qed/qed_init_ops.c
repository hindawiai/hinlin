<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_hsi.h"
#समावेश "qed_hw.h"
#समावेश "qed_init_ops.h"
#समावेश "qed_reg_addr.h"
#समावेश "qed_sriov.h"

#घोषणा QED_INIT_MAX_POLL_COUNT 100
#घोषणा QED_INIT_POLL_PERIOD_US 500

अटल u32 pxp_global_win[] = अणु
	0,
	0,
	0x1c02, /* win 2: addr=0x1c02000, size=4096 bytes */
	0x1c80, /* win 3: addr=0x1c80000, size=4096 bytes */
	0x1d00, /* win 4: addr=0x1d00000, size=4096 bytes */
	0x1d01, /* win 5: addr=0x1d01000, size=4096 bytes */
	0x1d02, /* win 6: addr=0x1d02000, size=4096 bytes */
	0x1d80, /* win 7: addr=0x1d80000, size=4096 bytes */
	0x1d81, /* win 8: addr=0x1d81000, size=4096 bytes */
	0x1d82, /* win 9: addr=0x1d82000, size=4096 bytes */
	0x1e00, /* win 10: addr=0x1e00000, size=4096 bytes */
	0x1e01, /* win 11: addr=0x1e01000, size=4096 bytes */
	0x1e80, /* win 12: addr=0x1e80000, size=4096 bytes */
	0x1f00, /* win 13: addr=0x1f00000, size=4096 bytes */
	0x1c08, /* win 14: addr=0x1c08000, size=4096 bytes */
	0,
	0,
	0,
	0,
पूर्ण;

/* IRO Array */
अटल स्थिर u32 iro_arr[] = अणु
	0x00000000, 0x00000000, 0x00080000,
	0x00003288, 0x00000088, 0x00880000,
	0x000058e8, 0x00000020, 0x00200000,
	0x00000b00, 0x00000008, 0x00040000,
	0x00000a80, 0x00000008, 0x00040000,
	0x00000000, 0x00000008, 0x00020000,
	0x00000080, 0x00000008, 0x00040000,
	0x00000084, 0x00000008, 0x00020000,
	0x00005718, 0x00000004, 0x00040000,
	0x00004dd0, 0x00000000, 0x00780000,
	0x00003e40, 0x00000000, 0x00780000,
	0x00004480, 0x00000000, 0x00780000,
	0x00003210, 0x00000000, 0x00780000,
	0x00003b50, 0x00000000, 0x00780000,
	0x00007f58, 0x00000000, 0x00780000,
	0x00005f58, 0x00000000, 0x00080000,
	0x00007100, 0x00000000, 0x00080000,
	0x0000aea0, 0x00000000, 0x00080000,
	0x00004398, 0x00000000, 0x00080000,
	0x0000a5a0, 0x00000000, 0x00080000,
	0x0000bde8, 0x00000000, 0x00080000,
	0x00000020, 0x00000004, 0x00040000,
	0x000056c8, 0x00000010, 0x00100000,
	0x0000c210, 0x00000030, 0x00300000,
	0x0000b088, 0x00000038, 0x00380000,
	0x00003d20, 0x00000080, 0x00400000,
	0x0000bf60, 0x00000000, 0x00040000,
	0x00004560, 0x00040080, 0x00040000,
	0x000001f8, 0x00000004, 0x00040000,
	0x00003d60, 0x00000080, 0x00200000,
	0x00008960, 0x00000040, 0x00300000,
	0x0000e840, 0x00000060, 0x00600000,
	0x00004618, 0x00000080, 0x00380000,
	0x00010738, 0x000000c0, 0x00c00000,
	0x000001f8, 0x00000002, 0x00020000,
	0x0000a2a0, 0x00000000, 0x01080000,
	0x0000a3a8, 0x00000008, 0x00080000,
	0x000001c0, 0x00000008, 0x00080000,
	0x000001f8, 0x00000008, 0x00080000,
	0x00000ac0, 0x00000008, 0x00080000,
	0x00002578, 0x00000008, 0x00080000,
	0x000024f8, 0x00000008, 0x00080000,
	0x00000280, 0x00000008, 0x00080000,
	0x00000680, 0x00080018, 0x00080000,
	0x00000b78, 0x00080018, 0x00020000,
	0x0000c640, 0x00000050, 0x003c0000,
	0x00012038, 0x00000018, 0x00100000,
	0x00011b00, 0x00000040, 0x00180000,
	0x000095d0, 0x00000050, 0x00200000,
	0x00008b10, 0x00000040, 0x00280000,
	0x00011640, 0x00000018, 0x00100000,
	0x0000c828, 0x00000048, 0x00380000,
	0x00011710, 0x00000020, 0x00200000,
	0x00004650, 0x00000080, 0x00100000,
	0x00003618, 0x00000010, 0x00100000,
	0x0000a968, 0x00000008, 0x00010000,
	0x000097a0, 0x00000008, 0x00010000,
	0x00011990, 0x00000008, 0x00010000,
	0x0000f018, 0x00000008, 0x00010000,
	0x00012628, 0x00000008, 0x00010000,
	0x00011da8, 0x00000008, 0x00010000,
	0x0000aa78, 0x00000030, 0x00100000,
	0x0000d768, 0x00000028, 0x00280000,
	0x00009a58, 0x00000018, 0x00180000,
	0x00009bd8, 0x00000008, 0x00080000,
	0x00013a18, 0x00000008, 0x00080000,
	0x000126e8, 0x00000018, 0x00180000,
	0x0000e608, 0x00500288, 0x00100000,
	0x00012970, 0x00000138, 0x00280000,
पूर्ण;

व्योम qed_init_iro_array(काष्ठा qed_dev *cdev)
अणु
	cdev->iro_arr = iro_arr;
पूर्ण

व्योम qed_init_store_rt_reg(काष्ठा qed_hwfn *p_hwfn, u32 rt_offset, u32 val)
अणु
	p_hwfn->rt_data.init_val[rt_offset] = val;
	p_hwfn->rt_data.b_valid[rt_offset] = true;
पूर्ण

व्योम qed_init_store_rt_agg(काष्ठा qed_hwfn *p_hwfn,
			   u32 rt_offset, u32 *p_val, माप_प्रकार size)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < size / माप(u32); i++) अणु
		p_hwfn->rt_data.init_val[rt_offset + i] = p_val[i];
		p_hwfn->rt_data.b_valid[rt_offset + i]	= true;
	पूर्ण
पूर्ण

अटल पूर्णांक qed_init_rt(काष्ठा qed_hwfn	*p_hwfn,
		       काष्ठा qed_ptt *p_ptt,
		       u32 addr, u16 rt_offset, u16 size, bool b_must_dmae)
अणु
	u32 *p_init_val = &p_hwfn->rt_data.init_val[rt_offset];
	bool *p_valid = &p_hwfn->rt_data.b_valid[rt_offset];
	u16 i, j, segment;
	पूर्णांक rc = 0;

	/* Since not all RT entries are initialized, go over the RT and
	 * क्रम each segment of initialized values use DMA.
	 */
	क्रम (i = 0; i < size; i++) अणु
		अगर (!p_valid[i])
			जारी;

		/* In हाल there isn't any wide-bus configuration here,
		 * simply ग_लिखो the data instead of using dmae.
		 */
		अगर (!b_must_dmae) अणु
			qed_wr(p_hwfn, p_ptt, addr + (i << 2), p_init_val[i]);
			p_valid[i] = false;
			जारी;
		पूर्ण

		/* Start of a new segment */
		क्रम (segment = 1; i + segment < size; segment++)
			अगर (!p_valid[i + segment])
				अवरोध;

		rc = qed_dmae_host2grc(p_hwfn, p_ptt,
				       (uपूर्णांकptr_t)(p_init_val + i),
				       addr + (i << 2), segment, शून्य);
		अगर (rc)
			वापस rc;

		/* invalidate after writing */
		क्रम (j = i; j < i + segment; j++)
			p_valid[j] = false;

		/* Jump over the entire segment, including invalid entry */
		i += segment;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक qed_init_alloc(काष्ठा qed_hwfn *p_hwfn)
अणु
	काष्ठा qed_rt_data *rt_data = &p_hwfn->rt_data;

	अगर (IS_VF(p_hwfn->cdev))
		वापस 0;

	rt_data->b_valid = kसुस्मृति(RUNTIME_ARRAY_SIZE, माप(bool),
				   GFP_KERNEL);
	अगर (!rt_data->b_valid)
		वापस -ENOMEM;

	rt_data->init_val = kसुस्मृति(RUNTIME_ARRAY_SIZE, माप(u32),
				    GFP_KERNEL);
	अगर (!rt_data->init_val) अणु
		kमुक्त(rt_data->b_valid);
		rt_data->b_valid = शून्य;
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम qed_init_मुक्त(काष्ठा qed_hwfn *p_hwfn)
अणु
	kमुक्त(p_hwfn->rt_data.init_val);
	p_hwfn->rt_data.init_val = शून्य;
	kमुक्त(p_hwfn->rt_data.b_valid);
	p_hwfn->rt_data.b_valid = शून्य;
पूर्ण

अटल पूर्णांक qed_init_array_dmae(काष्ठा qed_hwfn *p_hwfn,
			       काष्ठा qed_ptt *p_ptt,
			       u32 addr,
			       u32 dmae_data_offset,
			       u32 size,
			       स्थिर u32 *buf,
			       bool b_must_dmae,
			       bool b_can_dmae)
अणु
	पूर्णांक rc = 0;

	/* Perक्रमm DMAE only क्रम lengthy enough sections or क्रम wide-bus */
	अगर (!b_can_dmae || (!b_must_dmae && (size < 16))) अणु
		स्थिर u32 *data = buf + dmae_data_offset;
		u32 i;

		क्रम (i = 0; i < size; i++)
			qed_wr(p_hwfn, p_ptt, addr + (i << 2), data[i]);
	पूर्ण अन्यथा अणु
		rc = qed_dmae_host2grc(p_hwfn, p_ptt,
				       (uपूर्णांकptr_t)(buf + dmae_data_offset),
				       addr, size, शून्य);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक qed_init_fill_dmae(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      u32 addr, u32 fill, u32 fill_count)
अणु
	अटल u32 zero_buffer[DMAE_MAX_RW_SIZE];
	काष्ठा qed_dmae_params params = अणुपूर्ण;

	स_रखो(zero_buffer, 0, माप(u32) * DMAE_MAX_RW_SIZE);

	/* invoke the DMAE भव/physical buffer API with
	 * 1. DMAE init channel
	 * 2. addr,
	 * 3. p_hwfb->temp_data,
	 * 4. fill_count
	 */
	SET_FIELD(params.flags, QED_DMAE_PARAMS_RW_REPL_SRC, 0x1);
	वापस qed_dmae_host2grc(p_hwfn, p_ptt,
				 (uपूर्णांकptr_t)(&zero_buffer[0]),
				 addr, fill_count, &params);
पूर्ण

अटल व्योम qed_init_fill(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt,
			  u32 addr, u32 fill, u32 fill_count)
अणु
	u32 i;

	क्रम (i = 0; i < fill_count; i++, addr += माप(u32))
		qed_wr(p_hwfn, p_ptt, addr, fill);
पूर्ण

अटल पूर्णांक qed_init_cmd_array(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा qed_ptt *p_ptt,
			      काष्ठा init_ग_लिखो_op *cmd,
			      bool b_must_dmae, bool b_can_dmae)
अणु
	u32 dmae_array_offset = le32_to_cpu(cmd->args.array_offset);
	u32 data = le32_to_cpu(cmd->data);
	u32 addr = GET_FIELD(data, INIT_WRITE_OP_ADDRESS) << 2;

	u32 offset, output_len, input_len, max_size;
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	जोड़ init_array_hdr *hdr;
	स्थिर u32 *array_data;
	पूर्णांक rc = 0;
	u32 size;

	array_data = cdev->fw_data->arr_data;

	hdr = (जोड़ init_array_hdr *)(array_data + dmae_array_offset);
	data = le32_to_cpu(hdr->raw.data);
	चयन (GET_FIELD(data, INIT_ARRAY_RAW_HDR_TYPE)) अणु
	हाल INIT_ARR_ZIPPED:
		offset = dmae_array_offset + 1;
		input_len = GET_FIELD(data,
				      INIT_ARRAY_ZIPPED_HDR_ZIPPED_SIZE);
		max_size = MAX_ZIPPED_SIZE * 4;
		स_रखो(p_hwfn->unzip_buf, 0, max_size);

		output_len = qed_unzip_data(p_hwfn, input_len,
					    (u8 *)&array_data[offset],
					    max_size, (u8 *)p_hwfn->unzip_buf);
		अगर (output_len) अणु
			rc = qed_init_array_dmae(p_hwfn, p_ptt, addr, 0,
						 output_len,
						 p_hwfn->unzip_buf,
						 b_must_dmae, b_can_dmae);
		पूर्ण अन्यथा अणु
			DP_NOTICE(p_hwfn, "Failed to unzip dmae data\n");
			rc = -EINVAL;
		पूर्ण
		अवरोध;
	हाल INIT_ARR_PATTERN:
	अणु
		u32 repeats = GET_FIELD(data,
					INIT_ARRAY_PATTERN_HDR_REPETITIONS);
		u32 i;

		size = GET_FIELD(data, INIT_ARRAY_PATTERN_HDR_PATTERN_SIZE);

		क्रम (i = 0; i < repeats; i++, addr += size << 2) अणु
			rc = qed_init_array_dmae(p_hwfn, p_ptt, addr,
						 dmae_array_offset + 1,
						 size, array_data,
						 b_must_dmae, b_can_dmae);
			अगर (rc)
				अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल INIT_ARR_STANDARD:
		size = GET_FIELD(data, INIT_ARRAY_STANDARD_HDR_SIZE);
		rc = qed_init_array_dmae(p_hwfn, p_ptt, addr,
					 dmae_array_offset + 1,
					 size, array_data,
					 b_must_dmae, b_can_dmae);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

/* init_ops ग_लिखो command */
अटल पूर्णांक qed_init_cmd_wr(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt,
			   काष्ठा init_ग_लिखो_op *p_cmd, bool b_can_dmae)
अणु
	u32 data = le32_to_cpu(p_cmd->data);
	bool b_must_dmae = GET_FIELD(data, INIT_WRITE_OP_WIDE_BUS);
	u32 addr = GET_FIELD(data, INIT_WRITE_OP_ADDRESS) << 2;
	जोड़ init_ग_लिखो_args *arg = &p_cmd->args;
	पूर्णांक rc = 0;

	/* Sanitize */
	अगर (b_must_dmae && !b_can_dmae) अणु
		DP_NOTICE(p_hwfn,
			  "Need to write to %08x for Wide-bus but DMAE isn't allowed\n",
			  addr);
		वापस -EINVAL;
	पूर्ण

	चयन (GET_FIELD(data, INIT_WRITE_OP_SOURCE)) अणु
	हाल INIT_SRC_INLINE:
		data = le32_to_cpu(p_cmd->args.अंतरभूत_val);
		qed_wr(p_hwfn, p_ptt, addr, data);
		अवरोध;
	हाल INIT_SRC_ZEROS:
		data = le32_to_cpu(p_cmd->args.zeros_count);
		अगर (b_must_dmae || (b_can_dmae && (data >= 64)))
			rc = qed_init_fill_dmae(p_hwfn, p_ptt, addr, 0, data);
		अन्यथा
			qed_init_fill(p_hwfn, p_ptt, addr, 0, data);
		अवरोध;
	हाल INIT_SRC_ARRAY:
		rc = qed_init_cmd_array(p_hwfn, p_ptt, p_cmd,
					b_must_dmae, b_can_dmae);
		अवरोध;
	हाल INIT_SRC_RUNTIME:
		qed_init_rt(p_hwfn, p_ptt, addr,
			    le16_to_cpu(arg->runसमय.offset),
			    le16_to_cpu(arg->runसमय.size),
			    b_must_dmae);
		अवरोध;
	पूर्ण

	वापस rc;
पूर्ण

अटल अंतरभूत bool comp_eq(u32 val, u32 expected_val)
अणु
	वापस val == expected_val;
पूर्ण

अटल अंतरभूत bool comp_and(u32 val, u32 expected_val)
अणु
	वापस (val & expected_val) == expected_val;
पूर्ण

अटल अंतरभूत bool comp_or(u32 val, u32 expected_val)
अणु
	वापस (val | expected_val) > 0;
पूर्ण

/* init_ops पढ़ो/poll commands */
अटल व्योम qed_init_cmd_rd(काष्ठा qed_hwfn *p_hwfn,
			    काष्ठा qed_ptt *p_ptt, काष्ठा init_पढ़ो_op *cmd)
अणु
	bool (*comp_check)(u32 val, u32 expected_val);
	u32 delay = QED_INIT_POLL_PERIOD_US, val;
	u32 data, addr, poll;
	पूर्णांक i;

	data = le32_to_cpu(cmd->op_data);
	addr = GET_FIELD(data, INIT_READ_OP_ADDRESS) << 2;
	poll = GET_FIELD(data, INIT_READ_OP_POLL_TYPE);


	val = qed_rd(p_hwfn, p_ptt, addr);

	अगर (poll == INIT_POLL_NONE)
		वापस;

	चयन (poll) अणु
	हाल INIT_POLL_EQ:
		comp_check = comp_eq;
		अवरोध;
	हाल INIT_POLL_OR:
		comp_check = comp_or;
		अवरोध;
	हाल INIT_POLL_AND:
		comp_check = comp_and;
		अवरोध;
	शेष:
		DP_ERR(p_hwfn, "Invalid poll comparison type %08x\n",
		       cmd->op_data);
		वापस;
	पूर्ण

	data = le32_to_cpu(cmd->expected_val);
	क्रम (i = 0;
	     i < QED_INIT_MAX_POLL_COUNT && !comp_check(val, data);
	     i++) अणु
		udelay(delay);
		val = qed_rd(p_hwfn, p_ptt, addr);
	पूर्ण

	अगर (i == QED_INIT_MAX_POLL_COUNT) अणु
		DP_ERR(p_hwfn,
		       "Timeout when polling reg: 0x%08x [ Waiting-for: %08x Got: %08x (comparison %08x)]\n",
		       addr, le32_to_cpu(cmd->expected_val),
		       val, le32_to_cpu(cmd->op_data));
	पूर्ण
पूर्ण

/* init_ops callbacks entry poपूर्णांक */
अटल पूर्णांक qed_init_cmd_cb(काष्ठा qed_hwfn *p_hwfn,
			   काष्ठा qed_ptt *p_ptt,
			   काष्ठा init_callback_op *p_cmd)
अणु
	पूर्णांक rc;

	चयन (p_cmd->callback_id) अणु
	हाल DMAE_READY_CB:
		rc = qed_dmae_sanity(p_hwfn, p_ptt, "engine_phase");
		अवरोध;
	शेष:
		DP_NOTICE(p_hwfn, "Unexpected init op callback ID %d\n",
			  p_cmd->callback_id);
		वापस -EINVAL;
	पूर्ण

	वापस rc;
पूर्ण

अटल u8 qed_init_cmd_mode_match(काष्ठा qed_hwfn *p_hwfn,
				  u16 *p_offset, पूर्णांक modes)
अणु
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	स्थिर u8 *modes_tree_buf;
	u8 arg1, arg2, tree_val;

	modes_tree_buf = cdev->fw_data->modes_tree_buf;
	tree_val = modes_tree_buf[(*p_offset)++];
	चयन (tree_val) अणु
	हाल INIT_MODE_OP_NOT:
		वापस qed_init_cmd_mode_match(p_hwfn, p_offset, modes) ^ 1;
	हाल INIT_MODE_OP_OR:
		arg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		arg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		वापस arg1 | arg2;
	हाल INIT_MODE_OP_AND:
		arg1 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		arg2 = qed_init_cmd_mode_match(p_hwfn, p_offset, modes);
		वापस arg1 & arg2;
	शेष:
		tree_val -= MAX_INIT_MODE_OPS;
		वापस (modes & BIT(tree_val)) ? 1 : 0;
	पूर्ण
पूर्ण

अटल u32 qed_init_cmd_mode(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा init_अगर_mode_op *p_cmd, पूर्णांक modes)
अणु
	u16 offset = le16_to_cpu(p_cmd->modes_buf_offset);

	अगर (qed_init_cmd_mode_match(p_hwfn, &offset, modes))
		वापस 0;
	अन्यथा
		वापस GET_FIELD(le32_to_cpu(p_cmd->op_data),
				 INIT_IF_MODE_OP_CMD_OFFSET);
पूर्ण

अटल u32 qed_init_cmd_phase(काष्ठा qed_hwfn *p_hwfn,
			      काष्ठा init_अगर_phase_op *p_cmd,
			      u32 phase, u32 phase_id)
अणु
	u32 data = le32_to_cpu(p_cmd->phase_data);
	u32 op_data = le32_to_cpu(p_cmd->op_data);

	अगर (!(GET_FIELD(data, INIT_IF_PHASE_OP_PHASE) == phase &&
	      (GET_FIELD(data, INIT_IF_PHASE_OP_PHASE_ID) == ANY_PHASE_ID ||
	       GET_FIELD(data, INIT_IF_PHASE_OP_PHASE_ID) == phase_id)))
		वापस GET_FIELD(op_data, INIT_IF_PHASE_OP_CMD_OFFSET);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक qed_init_run(काष्ठा qed_hwfn *p_hwfn,
		 काष्ठा qed_ptt *p_ptt, पूर्णांक phase, पूर्णांक phase_id, पूर्णांक modes)
अणु
	bool b_dmae = (phase != PHASE_ENGINE);
	काष्ठा qed_dev *cdev = p_hwfn->cdev;
	u32 cmd_num, num_init_ops;
	जोड़ init_op *init_ops;
	पूर्णांक rc = 0;

	num_init_ops = cdev->fw_data->init_ops_size;
	init_ops = cdev->fw_data->init_ops;

	p_hwfn->unzip_buf = kzalloc(MAX_ZIPPED_SIZE * 4, GFP_ATOMIC);
	अगर (!p_hwfn->unzip_buf)
		वापस -ENOMEM;

	क्रम (cmd_num = 0; cmd_num < num_init_ops; cmd_num++) अणु
		जोड़ init_op *cmd = &init_ops[cmd_num];
		u32 data = le32_to_cpu(cmd->raw.op_data);

		चयन (GET_FIELD(data, INIT_CALLBACK_OP_OP)) अणु
		हाल INIT_OP_WRITE:
			rc = qed_init_cmd_wr(p_hwfn, p_ptt, &cmd->ग_लिखो,
					     b_dmae);
			अवरोध;
		हाल INIT_OP_READ:
			qed_init_cmd_rd(p_hwfn, p_ptt, &cmd->पढ़ो);
			अवरोध;
		हाल INIT_OP_IF_MODE:
			cmd_num += qed_init_cmd_mode(p_hwfn, &cmd->अगर_mode,
						     modes);
			अवरोध;
		हाल INIT_OP_IF_PHASE:
			cmd_num += qed_init_cmd_phase(p_hwfn, &cmd->अगर_phase,
						      phase, phase_id);
			अवरोध;
		हाल INIT_OP_DELAY:
			/* qed_init_run is always invoked from
			 * sleep-able context
			 */
			udelay(le32_to_cpu(cmd->delay.delay));
			अवरोध;

		हाल INIT_OP_CALLBACK:
			rc = qed_init_cmd_cb(p_hwfn, p_ptt, &cmd->callback);
			अगर (phase == PHASE_ENGINE &&
			    cmd->callback.callback_id == DMAE_READY_CB)
				b_dmae = true;
			अवरोध;
		पूर्ण

		अगर (rc)
			अवरोध;
	पूर्ण

	kमुक्त(p_hwfn->unzip_buf);
	p_hwfn->unzip_buf = शून्य;
	वापस rc;
पूर्ण

व्योम qed_gtt_init(काष्ठा qed_hwfn *p_hwfn)
अणु
	u32 gtt_base;
	u32 i;

	/* Set the global winकरोws */
	gtt_base = PXP_PF_WINDOW_ADMIN_START + PXP_PF_WINDOW_ADMIN_GLOBAL_START;

	क्रम (i = 0; i < ARRAY_SIZE(pxp_global_win); i++)
		अगर (pxp_global_win[i])
			REG_WR(p_hwfn, gtt_base + i * PXP_GLOBAL_ENTRY_SIZE,
			       pxp_global_win[i]);
पूर्ण

पूर्णांक qed_init_fw_data(काष्ठा qed_dev *cdev, स्थिर u8 *data)
अणु
	काष्ठा qed_fw_data *fw = cdev->fw_data;
	काष्ठा bin_buffer_hdr *buf_hdr;
	u32 offset, len;

	अगर (!data) अणु
		DP_NOTICE(cdev, "Invalid fw data\n");
		वापस -EINVAL;
	पूर्ण

	/* First Dword contains metadata and should be skipped */
	buf_hdr = (काष्ठा bin_buffer_hdr *)data;

	offset = buf_hdr[BIN_BUF_INIT_FW_VER_INFO].offset;
	fw->fw_ver_info = (काष्ठा fw_ver_info *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_CMD].offset;
	fw->init_ops = (जोड़ init_op *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_VAL].offset;
	fw->arr_data = (u32 *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_MODE_TREE].offset;
	fw->modes_tree_buf = (u8 *)(data + offset);
	len = buf_hdr[BIN_BUF_INIT_CMD].length;
	fw->init_ops_size = len / माप(काष्ठा init_raw_op);

	offset = buf_hdr[BIN_BUF_INIT_OVERLAYS].offset;
	fw->fw_overlays = (u32 *)(data + offset);
	len = buf_hdr[BIN_BUF_INIT_OVERLAYS].length;
	fw->fw_overlays_len = len;

	वापस 0;
पूर्ण
