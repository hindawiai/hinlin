<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Copyright(c) 2020 Intel Corporation. All rights reserved.
//
// Author: Cezary Rojewski <cezary.rojewski@पूर्णांकel.com>
//

#समावेश <linux/slab.h>
#समावेश "core.h"
#समावेश "messages.h"
#समावेश "registers.h"

पूर्णांक catpt_ipc_get_fw_version(काष्ठा catpt_dev *cdev,
			     काष्ठा catpt_fw_version *version)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(GET_FW_VERSION);
	काष्ठा catpt_ipc_msg request = अणुअणु0पूर्णपूर्ण, reply;
	पूर्णांक ret;

	request.header = msg.val;
	reply.size = माप(*version);
	reply.data = version;

	ret = catpt_dsp_send_msg(cdev, request, &reply);
	अगर (ret)
		dev_err(cdev->dev, "get fw version failed: %d\n", ret);

	वापस ret;
पूर्ण

काष्ठा catpt_alloc_stream_input अणु
	क्रमागत catpt_path_id path_id:8;
	क्रमागत catpt_stream_type stream_type:8;
	क्रमागत catpt_क्रमmat_id क्रमmat_id:8;
	u8 reserved;
	काष्ठा catpt_audio_क्रमmat input_क्रमmat;
	काष्ठा catpt_ring_info ring_info;
	u8 num_entries;
	/* flex array with entries here */
	काष्ठा catpt_memory_info persistent_mem;
	काष्ठा catpt_memory_info scratch_mem;
	u32 num_notअगरications; /* obsolete */
पूर्ण __packed;

पूर्णांक catpt_ipc_alloc_stream(काष्ठा catpt_dev *cdev,
			   क्रमागत catpt_path_id path_id,
			   क्रमागत catpt_stream_type type,
			   काष्ठा catpt_audio_क्रमmat *afmt,
			   काष्ठा catpt_ring_info *rinfo,
			   u8 num_modules,
			   काष्ठा catpt_module_entry *modules,
			   काष्ठा resource *persistent,
			   काष्ठा resource *scratch,
			   काष्ठा catpt_stream_info *sinfo)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(ALLOCATE_STREAM);
	काष्ठा catpt_alloc_stream_input input;
	काष्ठा catpt_ipc_msg request, reply;
	माप_प्रकार size, arrsz;
	u8 *payload;
	off_t off;
	पूर्णांक ret;

	off = दुरत्व(काष्ठा catpt_alloc_stream_input, persistent_mem);
	arrsz = माप(*modules) * num_modules;
	size = माप(input) + arrsz;

	payload = kzalloc(size, GFP_KERNEL);
	अगर (!payload)
		वापस -ENOMEM;

	स_रखो(&input, 0, माप(input));
	input.path_id = path_id;
	input.stream_type = type;
	input.क्रमmat_id = CATPT_FORMAT_PCM;
	input.input_क्रमmat = *afmt;
	input.ring_info = *rinfo;
	input.num_entries = num_modules;
	input.persistent_mem.offset = catpt_to_dsp_offset(persistent->start);
	input.persistent_mem.size = resource_size(persistent);
	अगर (scratch) अणु
		input.scratch_mem.offset = catpt_to_dsp_offset(scratch->start);
		input.scratch_mem.size = resource_size(scratch);
	पूर्ण

	/* re-arrange the input: account क्रम flex array 'entries' */
	स_नकल(payload, &input, माप(input));
	स_हटाओ(payload + off + arrsz, payload + off, माप(input) - off);
	स_नकल(payload + off, modules, arrsz);

	request.header = msg.val;
	request.size = size;
	request.data = payload;
	reply.size = माप(*sinfo);
	reply.data = sinfo;

	ret = catpt_dsp_send_msg(cdev, request, &reply);
	अगर (ret)
		dev_err(cdev->dev, "alloc stream type %d failed: %d\n",
			type, ret);

	kमुक्त(payload);
	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_मुक्त_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(FREE_STREAM);
	काष्ठा catpt_ipc_msg request;
	पूर्णांक ret;

	request.header = msg.val;
	request.size = माप(stream_hw_id);
	request.data = &stream_hw_id;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "free stream %d failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_set_device_क्रमmat(काष्ठा catpt_dev *cdev,
				काष्ठा catpt_ssp_device_क्रमmat *devfmt)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(SET_DEVICE_FORMATS);
	काष्ठा catpt_ipc_msg request;
	पूर्णांक ret;

	request.header = msg.val;
	request.size = माप(*devfmt);
	request.data = devfmt;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "set device format failed: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_enter_dxstate(काष्ठा catpt_dev *cdev, क्रमागत catpt_dx_state state,
			    काष्ठा catpt_dx_context *context)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(ENTER_DX_STATE);
	काष्ठा catpt_ipc_msg request, reply;
	पूर्णांक ret;

	request.header = msg.val;
	request.size = माप(state);
	request.data = &state;
	reply.size = माप(*context);
	reply.data = context;

	ret = catpt_dsp_send_msg(cdev, request, &reply);
	अगर (ret)
		dev_err(cdev->dev, "enter dx state failed: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_get_mixer_stream_info(काष्ठा catpt_dev *cdev,
				    काष्ठा catpt_mixer_stream_info *info)
अणु
	जोड़ catpt_global_msg msg = CATPT_GLOBAL_MSG(GET_MIXER_STREAM_INFO);
	काष्ठा catpt_ipc_msg request = अणुअणु0पूर्णपूर्ण, reply;
	पूर्णांक ret;

	request.header = msg.val;
	reply.size = माप(*info);
	reply.data = info;

	ret = catpt_dsp_send_msg(cdev, request, &reply);
	अगर (ret)
		dev_err(cdev->dev, "get mixer info failed: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_reset_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STREAM_MSG(RESET_STREAM);
	काष्ठा catpt_ipc_msg request = अणुअणु0पूर्णपूर्ण;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	request.header = msg.val;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "reset stream %d failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_छोड़ो_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STREAM_MSG(PAUSE_STREAM);
	काष्ठा catpt_ipc_msg request = अणुअणु0पूर्णपूर्ण;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	request.header = msg.val;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "pause stream %d failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_resume_stream(काष्ठा catpt_dev *cdev, u8 stream_hw_id)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STREAM_MSG(RESUME_STREAM);
	काष्ठा catpt_ipc_msg request = अणुअणु0पूर्णपूर्ण;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	request.header = msg.val;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "resume stream %d failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

काष्ठा catpt_set_volume_input अणु
	u32 channel;
	u32 target_volume;
	u64 curve_duration;
	u32 curve_type;
पूर्ण __packed;

पूर्णांक catpt_ipc_set_volume(काष्ठा catpt_dev *cdev, u8 stream_hw_id,
			 u32 channel, u32 volume,
			 u32 curve_duration,
			 क्रमागत catpt_audio_curve_type curve_type)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STAGE_MSG(SET_VOLUME);
	काष्ठा catpt_ipc_msg request;
	काष्ठा catpt_set_volume_input input;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	input.channel = channel;
	input.target_volume = volume;
	input.curve_duration = curve_duration;
	input.curve_type = curve_type;

	request.header = msg.val;
	request.size = माप(input);
	request.data = &input;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "set stream %d volume failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

काष्ठा catpt_set_ग_लिखो_pos_input अणु
	u32 new_ग_लिखो_pos;
	bool end_of_buffer;
	bool low_latency;
पूर्ण __packed;

पूर्णांक catpt_ipc_set_ग_लिखो_pos(काष्ठा catpt_dev *cdev, u8 stream_hw_id,
			    u32 pos, bool eob, bool ll)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STAGE_MSG(SET_WRITE_POSITION);
	काष्ठा catpt_ipc_msg request;
	काष्ठा catpt_set_ग_लिखो_pos_input input;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	input.new_ग_लिखो_pos = pos;
	input.end_of_buffer = eob;
	input.low_latency = ll;

	request.header = msg.val;
	request.size = माप(input);
	request.data = &input;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "set stream %d write pos failed: %d\n",
			stream_hw_id, ret);

	वापस ret;
पूर्ण

पूर्णांक catpt_ipc_mute_loopback(काष्ठा catpt_dev *cdev, u8 stream_hw_id, bool mute)
अणु
	जोड़ catpt_stream_msg msg = CATPT_STAGE_MSG(MUTE_LOOPBACK);
	काष्ठा catpt_ipc_msg request;
	पूर्णांक ret;

	msg.stream_hw_id = stream_hw_id;
	request.header = msg.val;
	request.size = माप(mute);
	request.data = &mute;

	ret = catpt_dsp_send_msg(cdev, request, शून्य);
	अगर (ret)
		dev_err(cdev->dev, "mute loopback failed: %d\n", ret);

	वापस ret;
पूर्ण
