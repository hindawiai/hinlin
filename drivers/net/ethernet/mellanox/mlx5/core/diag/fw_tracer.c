<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#घोषणा CREATE_TRACE_POINTS
#समावेश "lib/eq.h"
#समावेश "fw_tracer.h"
#समावेश "fw_tracer_tracepoint.h"

अटल पूर्णांक mlx5_query_mtrc_caps(काष्ठा mlx5_fw_tracer *tracer)
अणु
	u32 *string_db_base_address_out = tracer->str_db.base_address_out;
	u32 *string_db_size_out = tracer->str_db.size_out;
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 out[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;
	व्योम *mtrc_cap_sp;
	पूर्णांक err, i;

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_MTRC_CAP, 0, 0);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Error reading tracer caps %d\n",
			       err);
		वापस err;
	पूर्ण

	अगर (!MLX5_GET(mtrc_cap, out, trace_to_memory)) अणु
		mlx5_core_dbg(dev, "FWTracer: Device does not support logging traces to memory\n");
		वापस -ENOTSUPP;
	पूर्ण

	tracer->trc_ver = MLX5_GET(mtrc_cap, out, trc_ver);
	tracer->str_db.first_string_trace =
			MLX5_GET(mtrc_cap, out, first_string_trace);
	tracer->str_db.num_string_trace =
			MLX5_GET(mtrc_cap, out, num_string_trace);
	tracer->str_db.num_string_db = MLX5_GET(mtrc_cap, out, num_string_db);
	tracer->owner = !!MLX5_GET(mtrc_cap, out, trace_owner);

	क्रम (i = 0; i < tracer->str_db.num_string_db; i++) अणु
		mtrc_cap_sp = MLX5_ADDR_OF(mtrc_cap, out, string_db_param[i]);
		string_db_base_address_out[i] = MLX5_GET(mtrc_string_db_param,
							 mtrc_cap_sp,
							 string_db_base_address);
		string_db_size_out[i] = MLX5_GET(mtrc_string_db_param,
						 mtrc_cap_sp, string_db_size);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_set_mtrc_caps_trace_owner(काष्ठा mlx5_fw_tracer *tracer,
					  u32 *out, u32 out_size,
					  u8 trace_owner)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 in[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;

	MLX5_SET(mtrc_cap, in, trace_owner, trace_owner);

	वापस mlx5_core_access_reg(dev, in, माप(in), out, out_size,
				    MLX5_REG_MTRC_CAP, 0, 1);
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_ownership_acquire(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 out[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;
	पूर्णांक err;

	err = mlx5_set_mtrc_caps_trace_owner(tracer, out, माप(out),
					     MLX5_FW_TRACER_ACQUIRE_OWNERSHIP);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Acquire tracer ownership failed %d\n",
			       err);
		वापस err;
	पूर्ण

	tracer->owner = !!MLX5_GET(mtrc_cap, out, trace_owner);

	अगर (!tracer->owner)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल व्योम mlx5_fw_tracer_ownership_release(काष्ठा mlx5_fw_tracer *tracer)
अणु
	u32 out[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;

	mlx5_set_mtrc_caps_trace_owner(tracer, out, माप(out),
				       MLX5_FW_TRACER_RELEASE_OWNERSHIP);
	tracer->owner = false;
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_create_log_buf(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	काष्ठा device *ddev;
	dma_addr_t dma;
	व्योम *buff;
	gfp_t gfp;
	पूर्णांक err;

	tracer->buff.size = TRACE_BUFFER_SIZE_BYTE;

	gfp = GFP_KERNEL | __GFP_ZERO;
	buff = (व्योम *)__get_मुक्त_pages(gfp,
					get_order(tracer->buff.size));
	अगर (!buff) अणु
		err = -ENOMEM;
		mlx5_core_warn(dev, "FWTracer: Failed to allocate pages, %d\n", err);
		वापस err;
	पूर्ण
	tracer->buff.log_buf = buff;

	ddev = mlx5_core_dma_dev(dev);
	dma = dma_map_single(ddev, buff, tracer->buff.size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(ddev, dma)) अणु
		mlx5_core_warn(dev, "FWTracer: Unable to map DMA: %d\n",
			       dma_mapping_error(ddev, dma));
		err = -ENOMEM;
		जाओ मुक्त_pages;
	पूर्ण
	tracer->buff.dma = dma;

	वापस 0;

मुक्त_pages:
	मुक्त_pages((अचिन्हित दीर्घ)tracer->buff.log_buf, get_order(tracer->buff.size));

	वापस err;
पूर्ण

अटल व्योम mlx5_fw_tracer_destroy_log_buf(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	काष्ठा device *ddev;

	अगर (!tracer->buff.log_buf)
		वापस;

	ddev = mlx5_core_dma_dev(dev);
	dma_unmap_single(ddev, tracer->buff.dma, tracer->buff.size, DMA_FROM_DEVICE);
	मुक्त_pages((अचिन्हित दीर्घ)tracer->buff.log_buf, get_order(tracer->buff.size));
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_create_mkey(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	पूर्णांक err, inlen, i;
	__be64 *mtt;
	व्योम *mkc;
	u32 *in;

	inlen = MLX5_ST_SZ_BYTES(create_mkey_in) +
			माप(*mtt) * round_up(TRACER_BUFFER_PAGE_NUM, 2);

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	MLX5_SET(create_mkey_in, in, translations_octword_actual_size,
		 DIV_ROUND_UP(TRACER_BUFFER_PAGE_NUM, 2));
	mtt = (__be64 *)MLX5_ADDR_OF(create_mkey_in, in, klm_pas_mtt);
	क्रम (i = 0 ; i < TRACER_BUFFER_PAGE_NUM ; i++)
		mtt[i] = cpu_to_be64(tracer->buff.dma + i * PAGE_SIZE);

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_MTT);
	MLX5_SET(mkc, mkc, lr, 1);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, pd, tracer->buff.pdn);
	MLX5_SET(mkc, mkc, bsf_octword_size, 0);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);
	MLX5_SET(mkc, mkc, log_page_size, PAGE_SHIFT);
	MLX5_SET(mkc, mkc, translations_octword_size,
		 DIV_ROUND_UP(TRACER_BUFFER_PAGE_NUM, 2));
	MLX5_SET64(mkc, mkc, start_addr, tracer->buff.dma);
	MLX5_SET64(mkc, mkc, len, tracer->buff.size);
	err = mlx5_core_create_mkey(dev, &tracer->buff.mkey, in, inlen);
	अगर (err)
		mlx5_core_warn(dev, "FWTracer: Failed to create mkey, %d\n", err);

	kvमुक्त(in);

	वापस err;
पूर्ण

अटल व्योम mlx5_fw_tracer_मुक्त_strings_db(काष्ठा mlx5_fw_tracer *tracer)
अणु
	u32 num_string_db = tracer->str_db.num_string_db;
	पूर्णांक i;

	क्रम (i = 0; i < num_string_db; i++) अणु
		kमुक्त(tracer->str_db.buffer[i]);
		tracer->str_db.buffer[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_allocate_strings_db(काष्ठा mlx5_fw_tracer *tracer)
अणु
	u32 *string_db_size_out = tracer->str_db.size_out;
	u32 num_string_db = tracer->str_db.num_string_db;
	पूर्णांक i;

	क्रम (i = 0; i < num_string_db; i++) अणु
		tracer->str_db.buffer[i] = kzalloc(string_db_size_out[i], GFP_KERNEL);
		अगर (!tracer->str_db.buffer[i])
			जाओ मुक्त_strings_db;
	पूर्ण

	वापस 0;

मुक्त_strings_db:
	mlx5_fw_tracer_मुक्त_strings_db(tracer);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
mlx5_fw_tracer_init_saved_traces_array(काष्ठा mlx5_fw_tracer *tracer)
अणु
	tracer->st_arr.saved_traces_index = 0;
	mutex_init(&tracer->st_arr.lock);
पूर्ण

अटल व्योम
mlx5_fw_tracer_clean_saved_traces_array(काष्ठा mlx5_fw_tracer *tracer)
अणु
	mutex_destroy(&tracer->st_arr.lock);
पूर्ण

अटल व्योम mlx5_tracer_पढ़ो_strings_db(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_tracer *tracer = container_of(work, काष्ठा mlx5_fw_tracer,
						     पढ़ो_fw_strings_work);
	u32 num_of_पढ़ोs, num_string_db = tracer->str_db.num_string_db;
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 in[MLX5_ST_SZ_DW(mtrc_cap)] = अणु0पूर्ण;
	u32 leftovers, offset;
	पूर्णांक err = 0, i, j;
	u32 *out, outlen;
	व्योम *out_value;

	outlen = MLX5_ST_SZ_BYTES(mtrc_stdb) + STRINGS_DB_READ_SIZE_BYTES;
	out = kzalloc(outlen, GFP_KERNEL);
	अगर (!out) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < num_string_db; i++) अणु
		offset = 0;
		MLX5_SET(mtrc_stdb, in, string_db_index, i);
		num_of_पढ़ोs = tracer->str_db.size_out[i] /
				STRINGS_DB_READ_SIZE_BYTES;
		leftovers = (tracer->str_db.size_out[i] %
				STRINGS_DB_READ_SIZE_BYTES) /
					STRINGS_DB_LEFTOVER_SIZE_BYTES;

		MLX5_SET(mtrc_stdb, in, पढ़ो_size, STRINGS_DB_READ_SIZE_BYTES);
		क्रम (j = 0; j < num_of_पढ़ोs; j++) अणु
			MLX5_SET(mtrc_stdb, in, start_offset, offset);

			err = mlx5_core_access_reg(dev, in, माप(in), out,
						   outlen, MLX5_REG_MTRC_STDB,
						   0, 1);
			अगर (err) अणु
				mlx5_core_dbg(dev, "FWTracer: Failed to read strings DB %d\n",
					      err);
				जाओ out_मुक्त;
			पूर्ण

			out_value = MLX5_ADDR_OF(mtrc_stdb, out, string_db_data);
			स_नकल(tracer->str_db.buffer[i] + offset, out_value,
			       STRINGS_DB_READ_SIZE_BYTES);
			offset += STRINGS_DB_READ_SIZE_BYTES;
		पूर्ण

		/* Strings database is aligned to 64, need to पढ़ो leftovers*/
		MLX5_SET(mtrc_stdb, in, पढ़ो_size,
			 STRINGS_DB_LEFTOVER_SIZE_BYTES);
		क्रम (j = 0; j < leftovers; j++) अणु
			MLX5_SET(mtrc_stdb, in, start_offset, offset);

			err = mlx5_core_access_reg(dev, in, माप(in), out,
						   outlen, MLX5_REG_MTRC_STDB,
						   0, 1);
			अगर (err) अणु
				mlx5_core_dbg(dev, "FWTracer: Failed to read strings DB %d\n",
					      err);
				जाओ out_मुक्त;
			पूर्ण

			out_value = MLX5_ADDR_OF(mtrc_stdb, out, string_db_data);
			स_नकल(tracer->str_db.buffer[i] + offset, out_value,
			       STRINGS_DB_LEFTOVER_SIZE_BYTES);
			offset += STRINGS_DB_LEFTOVER_SIZE_BYTES;
		पूर्ण
	पूर्ण

	tracer->str_db.loaded = true;

out_मुक्त:
	kमुक्त(out);
out:
	वापस;
पूर्ण

अटल व्योम mlx5_fw_tracer_arm(काष्ठा mlx5_core_dev *dev)
अणु
	u32 out[MLX5_ST_SZ_DW(mtrc_ctrl)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtrc_ctrl)] = अणु0पूर्ण;
	पूर्णांक err;

	MLX5_SET(mtrc_ctrl, in, arm_event, 1);

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_MTRC_CTRL, 0, 1);
	अगर (err)
		mlx5_core_warn(dev, "FWTracer: Failed to arm tracer event %d\n", err);
पूर्ण

अटल स्थिर अक्षर *VAL_PARM		= "%llx";
अटल स्थिर अक्षर *REPLACE_64_VAL_PARM	= "%x%x";
अटल स्थिर अक्षर *PARAM_CHAR		= "%";

अटल पूर्णांक mlx5_tracer_message_hash(u32 message_id)
अणु
	वापस jhash_1word(message_id, 0) & (MESSAGE_HASH_SIZE - 1);
पूर्ण

अटल काष्ठा tracer_string_क्रमmat *mlx5_tracer_message_insert(काष्ठा mlx5_fw_tracer *tracer,
							       काष्ठा tracer_event *tracer_event)
अणु
	काष्ठा hlist_head *head =
		&tracer->hash[mlx5_tracer_message_hash(tracer_event->string_event.पंचांगsn)];
	काष्ठा tracer_string_क्रमmat *cur_string;

	cur_string = kzalloc(माप(*cur_string), GFP_KERNEL);
	अगर (!cur_string)
		वापस शून्य;

	hlist_add_head(&cur_string->hlist, head);

	वापस cur_string;
पूर्ण

अटल काष्ठा tracer_string_क्रमmat *mlx5_tracer_get_string(काष्ठा mlx5_fw_tracer *tracer,
							   काष्ठा tracer_event *tracer_event)
अणु
	काष्ठा tracer_string_क्रमmat *cur_string;
	u32 str_ptr, offset;
	पूर्णांक i;

	str_ptr = tracer_event->string_event.string_param;

	क्रम (i = 0; i < tracer->str_db.num_string_db; i++) अणु
		अगर (str_ptr > tracer->str_db.base_address_out[i] &&
		    str_ptr < tracer->str_db.base_address_out[i] +
		    tracer->str_db.size_out[i]) अणु
			offset = str_ptr - tracer->str_db.base_address_out[i];
			/* add it to the hash */
			cur_string = mlx5_tracer_message_insert(tracer, tracer_event);
			अगर (!cur_string)
				वापस शून्य;
			cur_string->string = (अक्षर *)(tracer->str_db.buffer[i] +
							offset);
			वापस cur_string;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mlx5_tracer_clean_message(काष्ठा tracer_string_क्रमmat *str_frmt)
अणु
	hlist_del(&str_frmt->hlist);
	kमुक्त(str_frmt);
पूर्ण

अटल पूर्णांक mlx5_tracer_get_num_of_params(अक्षर *str)
अणु
	अक्षर *substr, *pstr = str;
	पूर्णांक num_of_params = 0;

	/* replace %llx with %x%x */
	substr = म_माला(pstr, VAL_PARM);
	जबतक (substr) अणु
		स_नकल(substr, REPLACE_64_VAL_PARM, 4);
		pstr = substr;
		substr = म_माला(pstr, VAL_PARM);
	पूर्ण

	/* count all the % अक्षरacters */
	substr = म_माला(str, PARAM_CHAR);
	जबतक (substr) अणु
		num_of_params += 1;
		str = substr + 1;
		substr = म_माला(str, PARAM_CHAR);
	पूर्ण

	वापस num_of_params;
पूर्ण

अटल काष्ठा tracer_string_क्रमmat *mlx5_tracer_message_find(काष्ठा hlist_head *head,
							     u8 event_id, u32 पंचांगsn)
अणु
	काष्ठा tracer_string_क्रमmat *message;

	hlist_क्रम_each_entry(message, head, hlist)
		अगर (message->event_id == event_id && message->पंचांगsn == पंचांगsn)
			वापस message;

	वापस शून्य;
पूर्ण

अटल काष्ठा tracer_string_क्रमmat *mlx5_tracer_message_get(काष्ठा mlx5_fw_tracer *tracer,
							    काष्ठा tracer_event *tracer_event)
अणु
	काष्ठा hlist_head *head =
		&tracer->hash[mlx5_tracer_message_hash(tracer_event->string_event.पंचांगsn)];

	वापस mlx5_tracer_message_find(head, tracer_event->event_id, tracer_event->string_event.पंचांगsn);
पूर्ण

अटल व्योम poll_trace(काष्ठा mlx5_fw_tracer *tracer,
		       काष्ठा tracer_event *tracer_event, u64 *trace)
अणु
	u32 बारtamp_low, बारtamp_mid, बारtamp_high, urts;

	tracer_event->event_id = MLX5_GET(tracer_event, trace, event_id);
	tracer_event->lost_event = MLX5_GET(tracer_event, trace, lost);

	चयन (tracer_event->event_id) अणु
	हाल TRACER_EVENT_TYPE_TIMESTAMP:
		tracer_event->type = TRACER_EVENT_TYPE_TIMESTAMP;
		urts = MLX5_GET(tracer_बारtamp_event, trace, urts);
		अगर (tracer->trc_ver == 0)
			tracer_event->बारtamp_event.unreliable = !!(urts >> 2);
		अन्यथा
			tracer_event->बारtamp_event.unreliable = !!(urts & 1);

		बारtamp_low = MLX5_GET(tracer_बारtamp_event,
					 trace, बारtamp7_0);
		बारtamp_mid = MLX5_GET(tracer_बारtamp_event,
					 trace, बारtamp39_8);
		बारtamp_high = MLX5_GET(tracer_बारtamp_event,
					  trace, बारtamp52_40);

		tracer_event->बारtamp_event.बारtamp =
				((u64)बारtamp_high << 40) |
				((u64)बारtamp_mid << 8) |
				(u64)बारtamp_low;
		अवरोध;
	शेष:
		अगर (tracer_event->event_id >= tracer->str_db.first_string_trace ||
		    tracer_event->event_id <= tracer->str_db.first_string_trace +
					      tracer->str_db.num_string_trace) अणु
			tracer_event->type = TRACER_EVENT_TYPE_STRING;
			tracer_event->string_event.बारtamp =
				MLX5_GET(tracer_string_event, trace, बारtamp);
			tracer_event->string_event.string_param =
				MLX5_GET(tracer_string_event, trace, string_param);
			tracer_event->string_event.पंचांगsn =
				MLX5_GET(tracer_string_event, trace, पंचांगsn);
			tracer_event->string_event.tdsn =
				MLX5_GET(tracer_string_event, trace, tdsn);
		पूर्ण अन्यथा अणु
			tracer_event->type = TRACER_EVENT_TYPE_UNRECOGNIZED;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल u64 get_block_बारtamp(काष्ठा mlx5_fw_tracer *tracer, u64 *ts_event)
अणु
	काष्ठा tracer_event tracer_event;
	u8 event_id;

	event_id = MLX5_GET(tracer_event, ts_event, event_id);

	अगर (event_id == TRACER_EVENT_TYPE_TIMESTAMP)
		poll_trace(tracer, &tracer_event, ts_event);
	अन्यथा
		tracer_event.बारtamp_event.बारtamp = 0;

	वापस tracer_event.बारtamp_event.बारtamp;
पूर्ण

अटल व्योम mlx5_fw_tracer_clean_prपूर्णांक_hash(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा tracer_string_क्रमmat *str_frmt;
	काष्ठा hlist_node *n;
	पूर्णांक i;

	क्रम (i = 0; i < MESSAGE_HASH_SIZE; i++) अणु
		hlist_क्रम_each_entry_safe(str_frmt, n, &tracer->hash[i], hlist)
			mlx5_tracer_clean_message(str_frmt);
	पूर्ण
पूर्ण

अटल व्योम mlx5_fw_tracer_clean_पढ़ोy_list(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा tracer_string_क्रमmat *str_frmt, *पंचांगp_str;

	list_क्रम_each_entry_safe(str_frmt, पंचांगp_str, &tracer->पढ़ोy_strings_list,
				 list)
		list_del(&str_frmt->list);
पूर्ण

अटल व्योम mlx5_fw_tracer_save_trace(काष्ठा mlx5_fw_tracer *tracer,
				      u64 बारtamp, bool lost,
				      u8 event_id, अक्षर *msg)
अणु
	काष्ठा mlx5_fw_trace_data *trace_data;

	mutex_lock(&tracer->st_arr.lock);
	trace_data = &tracer->st_arr.straces[tracer->st_arr.saved_traces_index];
	trace_data->बारtamp = बारtamp;
	trace_data->lost = lost;
	trace_data->event_id = event_id;
	strscpy_pad(trace_data->msg, msg, TRACE_STR_MSG);

	tracer->st_arr.saved_traces_index =
		(tracer->st_arr.saved_traces_index + 1) & (SAVED_TRACES_NUM - 1);
	mutex_unlock(&tracer->st_arr.lock);
पूर्ण

अटल noअंतरभूत
व्योम mlx5_tracer_prपूर्णांक_trace(काष्ठा tracer_string_क्रमmat *str_frmt,
			     काष्ठा mlx5_core_dev *dev,
			     u64 trace_बारtamp)
अणु
	अक्षर	पंचांगp[512];

	snम_लिखो(पंचांगp, माप(पंचांगp), str_frmt->string,
		 str_frmt->params[0],
		 str_frmt->params[1],
		 str_frmt->params[2],
		 str_frmt->params[3],
		 str_frmt->params[4],
		 str_frmt->params[5],
		 str_frmt->params[6]);

	trace_mlx5_fw(dev->tracer, trace_बारtamp, str_frmt->lost,
		      str_frmt->event_id, पंचांगp);

	mlx5_fw_tracer_save_trace(dev->tracer, trace_बारtamp,
				  str_frmt->lost, str_frmt->event_id, पंचांगp);

	/* हटाओ it from hash */
	mlx5_tracer_clean_message(str_frmt);
पूर्ण

अटल पूर्णांक mlx5_tracer_handle_string_trace(काष्ठा mlx5_fw_tracer *tracer,
					   काष्ठा tracer_event *tracer_event)
अणु
	काष्ठा tracer_string_क्रमmat *cur_string;

	अगर (tracer_event->string_event.tdsn == 0) अणु
		cur_string = mlx5_tracer_get_string(tracer, tracer_event);
		अगर (!cur_string)
			वापस -1;

		cur_string->num_of_params = mlx5_tracer_get_num_of_params(cur_string->string);
		cur_string->last_param_num = 0;
		cur_string->event_id = tracer_event->event_id;
		cur_string->पंचांगsn = tracer_event->string_event.पंचांगsn;
		cur_string->बारtamp = tracer_event->string_event.बारtamp;
		cur_string->lost = tracer_event->lost_event;
		अगर (cur_string->num_of_params == 0) /* trace with no params */
			list_add_tail(&cur_string->list, &tracer->पढ़ोy_strings_list);
	पूर्ण अन्यथा अणु
		cur_string = mlx5_tracer_message_get(tracer, tracer_event);
		अगर (!cur_string) अणु
			pr_debug("%s Got string event for unknown string tdsm: %d\n",
				 __func__, tracer_event->string_event.पंचांगsn);
			वापस -1;
		पूर्ण
		cur_string->last_param_num += 1;
		अगर (cur_string->last_param_num > TRACER_MAX_PARAMS) अणु
			pr_debug("%s Number of params exceeds the max (%d)\n",
				 __func__, TRACER_MAX_PARAMS);
			list_add_tail(&cur_string->list, &tracer->पढ़ोy_strings_list);
			वापस 0;
		पूर्ण
		/* keep the new parameter */
		cur_string->params[cur_string->last_param_num - 1] =
			tracer_event->string_event.string_param;
		अगर (cur_string->last_param_num == cur_string->num_of_params)
			list_add_tail(&cur_string->list, &tracer->पढ़ोy_strings_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mlx5_tracer_handle_बारtamp_trace(काष्ठा mlx5_fw_tracer *tracer,
					       काष्ठा tracer_event *tracer_event)
अणु
	काष्ठा tracer_बारtamp_event बारtamp_event =
						tracer_event->बारtamp_event;
	काष्ठा tracer_string_क्रमmat *str_frmt, *पंचांगp_str;
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u64 trace_बारtamp;

	list_क्रम_each_entry_safe(str_frmt, पंचांगp_str, &tracer->पढ़ोy_strings_list, list) अणु
		list_del(&str_frmt->list);
		अगर (str_frmt->बारtamp < (बारtamp_event.बारtamp & MASK_6_0))
			trace_बारtamp = (बारtamp_event.बारtamp & MASK_52_7) |
					  (str_frmt->बारtamp & MASK_6_0);
		अन्यथा
			trace_बारtamp = ((बारtamp_event.बारtamp & MASK_52_7) - 1) |
					  (str_frmt->बारtamp & MASK_6_0);

		mlx5_tracer_prपूर्णांक_trace(str_frmt, dev, trace_बारtamp);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx5_tracer_handle_trace(काष्ठा mlx5_fw_tracer *tracer,
				    काष्ठा tracer_event *tracer_event)
अणु
	अगर (tracer_event->type == TRACER_EVENT_TYPE_STRING) अणु
		mlx5_tracer_handle_string_trace(tracer, tracer_event);
	पूर्ण अन्यथा अगर (tracer_event->type == TRACER_EVENT_TYPE_TIMESTAMP) अणु
		अगर (!tracer_event->बारtamp_event.unreliable)
			mlx5_tracer_handle_बारtamp_trace(tracer, tracer_event);
	पूर्ण अन्यथा अणु
		pr_debug("%s Got unrecognised type %d for parsing, exiting..\n",
			 __func__, tracer_event->type);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mlx5_fw_tracer_handle_traces(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_tracer *tracer =
			container_of(work, काष्ठा mlx5_fw_tracer, handle_traces_work);
	u64 block_बारtamp, last_block_बारtamp, पंचांगp_trace_block[TRACES_PER_BLOCK];
	u32 block_count, start_offset, prev_start_offset, prev_consumer_index;
	u32 trace_event_size = MLX5_ST_SZ_BYTES(tracer_event);
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	काष्ठा tracer_event tracer_event;
	पूर्णांक i;

	mlx5_core_dbg(dev, "FWTracer: Handle Trace event, owner=(%d)\n", tracer->owner);
	अगर (!tracer->owner)
		वापस;

	block_count = tracer->buff.size / TRACER_BLOCK_SIZE_BYTE;
	start_offset = tracer->buff.consumer_index * TRACER_BLOCK_SIZE_BYTE;

	/* Copy the block to local buffer to aव्योम HW override जबतक being processed */
	स_नकल(पंचांगp_trace_block, tracer->buff.log_buf + start_offset,
	       TRACER_BLOCK_SIZE_BYTE);

	block_बारtamp =
		get_block_बारtamp(tracer, &पंचांगp_trace_block[TRACES_PER_BLOCK - 1]);

	जबतक (block_बारtamp > tracer->last_बारtamp) अणु
		/* Check block override अगर it's not the first block */
		अगर (!tracer->last_बारtamp) अणु
			u64 *ts_event;
			/* To aव्योम block override be the HW in हाल of buffer
			 * wraparound, the समय stamp of the previous block
			 * should be compared to the last बारtamp handled
			 * by the driver.
			 */
			prev_consumer_index =
				(tracer->buff.consumer_index - 1) & (block_count - 1);
			prev_start_offset = prev_consumer_index * TRACER_BLOCK_SIZE_BYTE;

			ts_event = tracer->buff.log_buf + prev_start_offset +
				   (TRACES_PER_BLOCK - 1) * trace_event_size;
			last_block_बारtamp = get_block_बारtamp(tracer, ts_event);
			/* If previous बारtamp dअगरferent from last stored
			 * बारtamp then there is a good chance that the
			 * current buffer is overwritten and thereक्रमe should
			 * not be parsed.
			 */
			अगर (tracer->last_बारtamp != last_block_बारtamp) अणु
				mlx5_core_warn(dev, "FWTracer: Events were lost\n");
				tracer->last_बारtamp = block_बारtamp;
				tracer->buff.consumer_index =
					(tracer->buff.consumer_index + 1) & (block_count - 1);
				अवरोध;
			पूर्ण
		पूर्ण

		/* Parse events */
		क्रम (i = 0; i < TRACES_PER_BLOCK ; i++) अणु
			poll_trace(tracer, &tracer_event, &पंचांगp_trace_block[i]);
			mlx5_tracer_handle_trace(tracer, &tracer_event);
		पूर्ण

		tracer->buff.consumer_index =
			(tracer->buff.consumer_index + 1) & (block_count - 1);

		tracer->last_बारtamp = block_बारtamp;
		start_offset = tracer->buff.consumer_index * TRACER_BLOCK_SIZE_BYTE;
		स_नकल(पंचांगp_trace_block, tracer->buff.log_buf + start_offset,
		       TRACER_BLOCK_SIZE_BYTE);
		block_बारtamp = get_block_बारtamp(tracer,
						      &पंचांगp_trace_block[TRACES_PER_BLOCK - 1]);
	पूर्ण

	mlx5_fw_tracer_arm(dev);
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_set_mtrc_conf(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 out[MLX5_ST_SZ_DW(mtrc_conf)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtrc_conf)] = अणु0पूर्ण;
	पूर्णांक err;

	MLX5_SET(mtrc_conf, in, trace_mode, TRACE_TO_MEMORY);
	MLX5_SET(mtrc_conf, in, log_trace_buffer_size,
		 ilog2(TRACER_BUFFER_PAGE_NUM));
	MLX5_SET(mtrc_conf, in, trace_mkey, tracer->buff.mkey.key);

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_MTRC_CONF, 0, 1);
	अगर (err)
		mlx5_core_warn(dev, "FWTracer: Failed to set tracer configurations %d\n", err);

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_set_mtrc_ctrl(काष्ठा mlx5_fw_tracer *tracer, u8 status, u8 arm)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	u32 out[MLX5_ST_SZ_DW(mtrc_ctrl)] = अणु0पूर्ण;
	u32 in[MLX5_ST_SZ_DW(mtrc_ctrl)] = अणु0पूर्ण;
	पूर्णांक err;

	MLX5_SET(mtrc_ctrl, in, modअगरy_field_select, TRACE_STATUS);
	MLX5_SET(mtrc_ctrl, in, trace_status, status);
	MLX5_SET(mtrc_ctrl, in, arm_event, arm);

	err = mlx5_core_access_reg(dev, in, माप(in), out, माप(out),
				   MLX5_REG_MTRC_CTRL, 0, 1);

	अगर (!err && status)
		tracer->last_बारtamp = 0;

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_start(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	पूर्णांक err;

	err = mlx5_fw_tracer_ownership_acquire(tracer);
	अगर (err) अणु
		mlx5_core_dbg(dev, "FWTracer: Ownership was not granted %d\n", err);
		/* Don't fail since ownership can be acquired on a later FW event */
		वापस 0;
	पूर्ण

	err = mlx5_fw_tracer_set_mtrc_conf(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Failed to set tracer configuration %d\n", err);
		जाओ release_ownership;
	पूर्ण

	/* enable tracer & trace events */
	err = mlx5_fw_tracer_set_mtrc_ctrl(tracer, 1, 1);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Failed to enable tracer %d\n", err);
		जाओ release_ownership;
	पूर्ण

	mlx5_core_dbg(dev, "FWTracer: Ownership granted and active\n");
	वापस 0;

release_ownership:
	mlx5_fw_tracer_ownership_release(tracer);
	वापस err;
पूर्ण

अटल व्योम mlx5_fw_tracer_ownership_change(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_fw_tracer *tracer =
		container_of(work, काष्ठा mlx5_fw_tracer, ownership_change_work);

	mlx5_core_dbg(tracer->dev, "FWTracer: ownership changed, current=(%d)\n", tracer->owner);
	अगर (tracer->owner) अणु
		tracer->owner = false;
		tracer->buff.consumer_index = 0;
		वापस;
	पूर्ण

	mlx5_fw_tracer_start(tracer);
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_set_core_dump_reg(काष्ठा mlx5_core_dev *dev,
					    u32 *in, पूर्णांक size_in)
अणु
	u32 out[MLX5_ST_SZ_DW(core_dump_reg)] = अणुपूर्ण;

	अगर (!MLX5_CAP_DEBUG(dev, core_dump_general) &&
	    !MLX5_CAP_DEBUG(dev, core_dump_qp))
		वापस -EOPNOTSUPP;

	वापस mlx5_core_access_reg(dev, in, size_in, out, माप(out),
				    MLX5_REG_CORE_DUMP, 0, 1);
पूर्ण

पूर्णांक mlx5_fw_tracer_trigger_core_dump_general(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_tracer *tracer = dev->tracer;
	u32 in[MLX5_ST_SZ_DW(core_dump_reg)] = अणुपूर्ण;
	पूर्णांक err;

	अगर (!MLX5_CAP_DEBUG(dev, core_dump_general) || !tracer)
		वापस -EOPNOTSUPP;
	अगर (!tracer->owner)
		वापस -EPERM;

	MLX5_SET(core_dump_reg, in, core_dump_type, 0x0);

	err =  mlx5_fw_tracer_set_core_dump_reg(dev, in, माप(in));
	अगर (err)
		वापस err;
	queue_work(tracer->work_queue, &tracer->handle_traces_work);
	flush_workqueue(tracer->work_queue);
	वापस 0;
पूर्ण

अटल पूर्णांक
mlx5_devlink_fmsg_fill_trace(काष्ठा devlink_fmsg *fmsg,
			     काष्ठा mlx5_fw_trace_data *trace_data)
अणु
	पूर्णांक err;

	err = devlink_fmsg_obj_nest_start(fmsg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u64_pair_put(fmsg, "timestamp", trace_data->बारtamp);
	अगर (err)
		वापस err;

	err = devlink_fmsg_bool_pair_put(fmsg, "lost", trace_data->lost);
	अगर (err)
		वापस err;

	err = devlink_fmsg_u8_pair_put(fmsg, "event_id", trace_data->event_id);
	अगर (err)
		वापस err;

	err = devlink_fmsg_string_pair_put(fmsg, "msg", trace_data->msg);
	अगर (err)
		वापस err;

	err = devlink_fmsg_obj_nest_end(fmsg);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

पूर्णांक mlx5_fw_tracer_get_saved_traces_objects(काष्ठा mlx5_fw_tracer *tracer,
					    काष्ठा devlink_fmsg *fmsg)
अणु
	काष्ठा mlx5_fw_trace_data *straces = tracer->st_arr.straces;
	u32 index, start_index, end_index;
	u32 saved_traces_index;
	पूर्णांक err;

	अगर (!straces[0].बारtamp)
		वापस -ENOMSG;

	mutex_lock(&tracer->st_arr.lock);
	saved_traces_index = tracer->st_arr.saved_traces_index;
	अगर (straces[saved_traces_index].बारtamp)
		start_index = saved_traces_index;
	अन्यथा
		start_index = 0;
	end_index = (saved_traces_index - 1) & (SAVED_TRACES_NUM - 1);

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "dump fw traces");
	अगर (err)
		जाओ unlock;
	index = start_index;
	जबतक (index != end_index) अणु
		err = mlx5_devlink_fmsg_fill_trace(fmsg, &straces[index]);
		अगर (err)
			जाओ unlock;

		index = (index + 1) & (SAVED_TRACES_NUM - 1);
	पूर्ण

	err = devlink_fmsg_arr_pair_nest_end(fmsg);
unlock:
	mutex_unlock(&tracer->st_arr.lock);
	वापस err;
पूर्ण

/* Create software resources (Buffers, etc ..) */
काष्ठा mlx5_fw_tracer *mlx5_fw_tracer_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_fw_tracer *tracer = शून्य;
	पूर्णांक err;

	अगर (!MLX5_CAP_MCAM_REG(dev, tracer_रेजिस्टरs)) अणु
		mlx5_core_dbg(dev, "FWTracer: Tracer capability not present\n");
		वापस शून्य;
	पूर्ण

	tracer = kvzalloc(माप(*tracer), GFP_KERNEL);
	अगर (!tracer)
		वापस ERR_PTR(-ENOMEM);

	tracer->work_queue = create_singlethपढ़ो_workqueue("mlx5_fw_tracer");
	अगर (!tracer->work_queue) अणु
		err = -ENOMEM;
		जाओ मुक्त_tracer;
	पूर्ण

	tracer->dev = dev;

	INIT_LIST_HEAD(&tracer->पढ़ोy_strings_list);
	INIT_WORK(&tracer->ownership_change_work, mlx5_fw_tracer_ownership_change);
	INIT_WORK(&tracer->पढ़ो_fw_strings_work, mlx5_tracer_पढ़ो_strings_db);
	INIT_WORK(&tracer->handle_traces_work, mlx5_fw_tracer_handle_traces);


	err = mlx5_query_mtrc_caps(tracer);
	अगर (err) अणु
		mlx5_core_dbg(dev, "FWTracer: Failed to query capabilities %d\n", err);
		जाओ destroy_workqueue;
	पूर्ण

	err = mlx5_fw_tracer_create_log_buf(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Create log buffer failed %d\n", err);
		जाओ destroy_workqueue;
	पूर्ण

	err = mlx5_fw_tracer_allocate_strings_db(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Allocate strings database failed %d\n", err);
		जाओ मुक्त_log_buf;
	पूर्ण

	mlx5_fw_tracer_init_saved_traces_array(tracer);
	mlx5_core_dbg(dev, "FWTracer: Tracer created\n");

	वापस tracer;

मुक्त_log_buf:
	mlx5_fw_tracer_destroy_log_buf(tracer);
destroy_workqueue:
	tracer->dev = शून्य;
	destroy_workqueue(tracer->work_queue);
मुक्त_tracer:
	kvमुक्त(tracer);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक fw_tracer_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data);

/* Create HW resources + start tracer */
पूर्णांक mlx5_fw_tracer_init(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(tracer))
		वापस 0;

	dev = tracer->dev;

	अगर (!tracer->str_db.loaded)
		queue_work(tracer->work_queue, &tracer->पढ़ो_fw_strings_work);

	err = mlx5_core_alloc_pd(dev, &tracer->buff.pdn);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Failed to allocate PD %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5_fw_tracer_create_mkey(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Failed to create mkey %d\n", err);
		जाओ err_dealloc_pd;
	पूर्ण

	MLX5_NB_INIT(&tracer->nb, fw_tracer_event, DEVICE_TRACER);
	mlx5_eq_notअगरier_रेजिस्टर(dev, &tracer->nb);

	mlx5_fw_tracer_start(tracer);

	वापस 0;

err_dealloc_pd:
	mlx5_core_dealloc_pd(dev, tracer->buff.pdn);
	वापस err;
पूर्ण

/* Stop tracer + Cleanup HW resources */
व्योम mlx5_fw_tracer_cleanup(काष्ठा mlx5_fw_tracer *tracer)
अणु
	अगर (IS_ERR_OR_शून्य(tracer))
		वापस;

	mlx5_core_dbg(tracer->dev, "FWTracer: Cleanup, is owner ? (%d)\n",
		      tracer->owner);
	mlx5_eq_notअगरier_unरेजिस्टर(tracer->dev, &tracer->nb);
	cancel_work_sync(&tracer->ownership_change_work);
	cancel_work_sync(&tracer->handle_traces_work);

	अगर (tracer->owner)
		mlx5_fw_tracer_ownership_release(tracer);

	mlx5_core_destroy_mkey(tracer->dev, &tracer->buff.mkey);
	mlx5_core_dealloc_pd(tracer->dev, tracer->buff.pdn);
पूर्ण

/* Free software resources (Buffers, etc ..) */
व्योम mlx5_fw_tracer_destroy(काष्ठा mlx5_fw_tracer *tracer)
अणु
	अगर (IS_ERR_OR_शून्य(tracer))
		वापस;

	mlx5_core_dbg(tracer->dev, "FWTracer: Destroy\n");

	cancel_work_sync(&tracer->पढ़ो_fw_strings_work);
	mlx5_fw_tracer_clean_पढ़ोy_list(tracer);
	mlx5_fw_tracer_clean_prपूर्णांक_hash(tracer);
	mlx5_fw_tracer_clean_saved_traces_array(tracer);
	mlx5_fw_tracer_मुक्त_strings_db(tracer);
	mlx5_fw_tracer_destroy_log_buf(tracer);
	flush_workqueue(tracer->work_queue);
	destroy_workqueue(tracer->work_queue);
	kvमुक्त(tracer);
पूर्ण

अटल पूर्णांक mlx5_fw_tracer_recreate_strings_db(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक err;

	cancel_work_sync(&tracer->पढ़ो_fw_strings_work);
	mlx5_fw_tracer_clean_पढ़ोy_list(tracer);
	mlx5_fw_tracer_clean_prपूर्णांक_hash(tracer);
	mlx5_fw_tracer_clean_saved_traces_array(tracer);
	mlx5_fw_tracer_मुक्त_strings_db(tracer);

	dev = tracer->dev;
	err = mlx5_query_mtrc_caps(tracer);
	अगर (err) अणु
		mlx5_core_dbg(dev, "FWTracer: Failed to query capabilities %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5_fw_tracer_allocate_strings_db(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "FWTracer: Allocate strings DB failed %d\n", err);
		वापस err;
	पूर्ण
	mlx5_fw_tracer_init_saved_traces_array(tracer);

	वापस 0;
पूर्ण

पूर्णांक mlx5_fw_tracer_reload(काष्ठा mlx5_fw_tracer *tracer)
अणु
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(tracer))
		वापस 0;

	dev = tracer->dev;
	mlx5_fw_tracer_cleanup(tracer);
	err = mlx5_fw_tracer_recreate_strings_db(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "Failed to recreate FW tracer strings DB\n");
		वापस err;
	पूर्ण
	err = mlx5_fw_tracer_init(tracer);
	अगर (err) अणु
		mlx5_core_warn(dev, "Failed to re-initialize FW tracer\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fw_tracer_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा mlx5_fw_tracer *tracer = mlx5_nb_cof(nb, काष्ठा mlx5_fw_tracer, nb);
	काष्ठा mlx5_core_dev *dev = tracer->dev;
	काष्ठा mlx5_eqe *eqe = data;

	चयन (eqe->sub_type) अणु
	हाल MLX5_TRACER_SUBTYPE_OWNERSHIP_CHANGE:
		queue_work(tracer->work_queue, &tracer->ownership_change_work);
		अवरोध;
	हाल MLX5_TRACER_SUBTYPE_TRACES_AVAILABLE:
		अगर (likely(tracer->str_db.loaded))
			queue_work(tracer->work_queue, &tracer->handle_traces_work);
		अवरोध;
	शेष:
		mlx5_core_dbg(dev, "FWTracer: Event with unrecognized subtype: sub_type %d\n",
			      eqe->sub_type);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

EXPORT_TRACEPOINT_SYMBOL(mlx5_fw);
