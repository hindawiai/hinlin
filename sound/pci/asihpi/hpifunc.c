<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "hpi_internal.h"
#समावेश "hpimsginit.h"

#समावेश "hpidebug.h"

काष्ठा hpi_handle अणु
	अचिन्हित पूर्णांक obj_index:12;
	अचिन्हित पूर्णांक obj_type:4;
	अचिन्हित पूर्णांक adapter_index:14;
	अचिन्हित पूर्णांक spare:1;
	अचिन्हित पूर्णांक पढ़ो_only:1;
पूर्ण;

जोड़ handle_word अणु
	काष्ठा hpi_handle h;
	u32 w;
पूर्ण;

u32 hpi_indexes_to_handle(स्थिर अक्षर c_object, स्थिर u16 adapter_index,
	स्थिर u16 object_index)
अणु
	जोड़ handle_word handle;

	handle.h.adapter_index = adapter_index;
	handle.h.spare = 0;
	handle.h.पढ़ो_only = 0;
	handle.h.obj_type = c_object;
	handle.h.obj_index = object_index;
	वापस handle.w;
पूर्ण

अटल u16 hpi_handle_indexes(स्थिर u32 h, u16 *p1, u16 *p2)
अणु
	जोड़ handle_word uhandle;
	अगर (!h)
		वापस HPI_ERROR_INVALID_HANDLE;

	uhandle.w = h;

	*p1 = (u16)uhandle.h.adapter_index;
	अगर (p2)
		*p2 = (u16)uhandle.h.obj_index;

	वापस 0;
पूर्ण

व्योम hpi_handle_to_indexes(स्थिर u32 handle, u16 *pw_adapter_index,
	u16 *pw_object_index)
अणु
	hpi_handle_indexes(handle, pw_adapter_index, pw_object_index);
पूर्ण

अक्षर hpi_handle_object(स्थिर u32 handle)
अणु
	जोड़ handle_word uhandle;
	uhandle.w = handle;
	वापस (अक्षर)uhandle.h.obj_type;
पूर्ण

व्योम hpi_क्रमmat_to_msg(काष्ठा hpi_msg_क्रमmat *pMF,
	स्थिर काष्ठा hpi_क्रमmat *pF)
अणु
	pMF->sample_rate = pF->sample_rate;
	pMF->bit_rate = pF->bit_rate;
	pMF->attributes = pF->attributes;
	pMF->channels = pF->channels;
	pMF->क्रमmat = pF->क्रमmat;
पूर्ण

अटल व्योम hpi_msg_to_क्रमmat(काष्ठा hpi_क्रमmat *pF,
	काष्ठा hpi_msg_क्रमmat *pMF)
अणु
	pF->sample_rate = pMF->sample_rate;
	pF->bit_rate = pMF->bit_rate;
	pF->attributes = pMF->attributes;
	pF->channels = pMF->channels;
	pF->क्रमmat = pMF->क्रमmat;
	pF->mode_legacy = 0;
	pF->unused = 0;
पूर्ण

व्योम hpi_stream_response_to_legacy(काष्ठा hpi_stream_res *pSR)
अणु
	pSR->u.legacy_stream_info.auxiliary_data_available =
		pSR->u.stream_info.auxiliary_data_available;
	pSR->u.legacy_stream_info.state = pSR->u.stream_info.state;
पूर्ण

अटल अंतरभूत व्योम hpi_send_recvV1(काष्ठा hpi_message_header *m,
	काष्ठा hpi_response_header *r)
अणु
	hpi_send_recv((काष्ठा hpi_message *)m, (काष्ठा hpi_response *)r);
पूर्ण

u16 hpi_subsys_get_version_ex(u32 *pversion_ex)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_VERSION);
	hpi_send_recv(&hm, &hr);
	*pversion_ex = hr.u.s.data;
	वापस hr.error;
पूर्ण

u16 hpi_subsys_get_num_adapters(पूर्णांक *pn_num_adapters)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_NUM_ADAPTERS);
	hpi_send_recv(&hm, &hr);
	*pn_num_adapters = (पूर्णांक)hr.u.s.num_adapters;
	वापस hr.error;
पूर्ण

u16 hpi_subsys_get_adapter(पूर्णांक iterator, u32 *padapter_index,
	u16 *pw_adapter_type)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_SUBSYSTEM,
		HPI_SUBSYS_GET_ADAPTER);
	hm.obj_index = (u16)iterator;
	hpi_send_recv(&hm, &hr);
	*padapter_index = (पूर्णांक)hr.u.s.adapter_index;
	*pw_adapter_type = hr.u.s.adapter_type;

	वापस hr.error;
पूर्ण

u16 hpi_adapter_खोलो(u16 adapter_index)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_OPEN);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;

पूर्ण

u16 hpi_adapter_बंद(u16 adapter_index)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_CLOSE);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_adapter_set_mode(u16 adapter_index, u32 adapter_mode)
अणु
	वापस hpi_adapter_set_mode_ex(adapter_index, adapter_mode,
		HPI_ADAPTER_MODE_SET);
पूर्ण

u16 hpi_adapter_set_mode_ex(u16 adapter_index, u32 adapter_mode,
	u16 query_or_set)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_SET_MODE);
	hm.adapter_index = adapter_index;
	hm.u.ax.mode.adapter_mode = adapter_mode;
	hm.u.ax.mode.query_or_set = query_or_set;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_adapter_get_mode(u16 adapter_index, u32 *padapter_mode)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_MODE);
	hm.adapter_index = adapter_index;
	hpi_send_recv(&hm, &hr);
	अगर (padapter_mode)
		*padapter_mode = hr.u.ax.mode.adapter_mode;
	वापस hr.error;
पूर्ण

u16 hpi_adapter_get_info(u16 adapter_index, u16 *pw_num_outstreams,
	u16 *pw_num_instreams, u16 *pw_version, u32 *pserial_number,
	u16 *pw_adapter_type)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_INFO);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	*pw_adapter_type = hr.u.ax.info.adapter_type;
	*pw_num_outstreams = hr.u.ax.info.num_outstreams;
	*pw_num_instreams = hr.u.ax.info.num_instreams;
	*pw_version = hr.u.ax.info.version;
	*pserial_number = hr.u.ax.info.serial_number;
	वापस hr.error;
पूर्ण

u16 hpi_adapter_get_module_by_index(u16 adapter_index, u16 module_index,
	u16 *pw_num_outमाला_दो, u16 *pw_num_inमाला_दो, u16 *pw_version,
	u32 *pserial_number, u16 *pw_module_type, u32 *ph_module)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_MODULE_INFO);
	hm.adapter_index = adapter_index;
	hm.u.ax.module_info.index = module_index;

	hpi_send_recv(&hm, &hr);

	*pw_module_type = hr.u.ax.info.adapter_type;
	*pw_num_outमाला_दो = hr.u.ax.info.num_outstreams;
	*pw_num_inमाला_दो = hr.u.ax.info.num_instreams;
	*pw_version = hr.u.ax.info.version;
	*pserial_number = hr.u.ax.info.serial_number;
	*ph_module = 0;

	वापस hr.error;
पूर्ण

u16 hpi_adapter_set_property(u16 adapter_index, u16 property, u16 parameter1,
	u16 parameter2)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_SET_PROPERTY);
	hm.adapter_index = adapter_index;
	hm.u.ax.property_set.property = property;
	hm.u.ax.property_set.parameter1 = parameter1;
	hm.u.ax.property_set.parameter2 = parameter2;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_adapter_get_property(u16 adapter_index, u16 property,
	u16 *pw_parameter1, u16 *pw_parameter2)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_PROPERTY);
	hm.adapter_index = adapter_index;
	hm.u.ax.property_set.property = property;

	hpi_send_recv(&hm, &hr);
	अगर (!hr.error) अणु
		अगर (pw_parameter1)
			*pw_parameter1 = hr.u.ax.property_get.parameter1;
		अगर (pw_parameter2)
			*pw_parameter2 = hr.u.ax.property_get.parameter2;
	पूर्ण

	वापस hr.error;
पूर्ण

u16 hpi_adapter_क्रमागतerate_property(u16 adapter_index, u16 index,
	u16 what_to_क्रमागतerate, u16 property_index, u32 *psetting)
अणु
	वापस 0;
पूर्ण

u16 hpi_क्रमmat_create(काष्ठा hpi_क्रमmat *p_क्रमmat, u16 channels, u16 क्रमmat,
	u32 sample_rate, u32 bit_rate, u32 attributes)
अणु
	u16 err = 0;
	काष्ठा hpi_msg_क्रमmat fmt;

	चयन (channels) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 16:
		अवरोध;
	शेष:
		err = HPI_ERROR_INVALID_CHANNELS;
		वापस err;
	पूर्ण
	fmt.channels = channels;

	चयन (क्रमmat) अणु
	हाल HPI_FORMAT_PCM16_SIGNED:
	हाल HPI_FORMAT_PCM24_SIGNED:
	हाल HPI_FORMAT_PCM32_SIGNED:
	हाल HPI_FORMAT_PCM32_FLOAT:
	हाल HPI_FORMAT_PCM16_BIGENDIAN:
	हाल HPI_FORMAT_PCM8_UNSIGNED:
	हाल HPI_FORMAT_MPEG_L1:
	हाल HPI_FORMAT_MPEG_L2:
	हाल HPI_FORMAT_MPEG_L3:
	हाल HPI_FORMAT_DOLBY_AC2:
	हाल HPI_FORMAT_AA_TAGIT1_HITS:
	हाल HPI_FORMAT_AA_TAGIT1_INSERTS:
	हाल HPI_FORMAT_RAW_BITSTREAM:
	हाल HPI_FORMAT_AA_TAGIT1_HITS_EX1:
	हाल HPI_FORMAT_OEM1:
	हाल HPI_FORMAT_OEM2:
		अवरोध;
	शेष:
		err = HPI_ERROR_INVALID_FORMAT;
		वापस err;
	पूर्ण
	fmt.क्रमmat = क्रमmat;

	अगर (sample_rate < 8000L) अणु
		err = HPI_ERROR_INCOMPATIBLE_SAMPLERATE;
		sample_rate = 8000L;
	पूर्ण
	अगर (sample_rate > 200000L) अणु
		err = HPI_ERROR_INCOMPATIBLE_SAMPLERATE;
		sample_rate = 200000L;
	पूर्ण
	fmt.sample_rate = sample_rate;

	चयन (क्रमmat) अणु
	हाल HPI_FORMAT_MPEG_L1:
	हाल HPI_FORMAT_MPEG_L2:
	हाल HPI_FORMAT_MPEG_L3:
		fmt.bit_rate = bit_rate;
		अवरोध;
	हाल HPI_FORMAT_PCM16_SIGNED:
	हाल HPI_FORMAT_PCM16_BIGENDIAN:
		fmt.bit_rate = channels * sample_rate * 2;
		अवरोध;
	हाल HPI_FORMAT_PCM32_SIGNED:
	हाल HPI_FORMAT_PCM32_FLOAT:
		fmt.bit_rate = channels * sample_rate * 4;
		अवरोध;
	हाल HPI_FORMAT_PCM8_UNSIGNED:
		fmt.bit_rate = channels * sample_rate;
		अवरोध;
	शेष:
		fmt.bit_rate = 0;
	पूर्ण

	चयन (क्रमmat) अणु
	हाल HPI_FORMAT_MPEG_L2:
		अगर ((channels == 1)
			&& (attributes != HPI_MPEG_MODE_DEFAULT)) अणु
			attributes = HPI_MPEG_MODE_DEFAULT;
			err = HPI_ERROR_INVALID_FORMAT;
		पूर्ण अन्यथा अगर (attributes > HPI_MPEG_MODE_DUALCHANNEL) अणु
			attributes = HPI_MPEG_MODE_DEFAULT;
			err = HPI_ERROR_INVALID_FORMAT;
		पूर्ण
		fmt.attributes = attributes;
		अवरोध;
	शेष:
		fmt.attributes = attributes;
	पूर्ण

	hpi_msg_to_क्रमmat(p_क्रमmat, &fmt);
	वापस err;
पूर्ण

u16 hpi_stream_estimate_buffer_size(काष्ठा hpi_क्रमmat *p_क्रमmat,
	u32 host_polling_rate_in_milli_seconds, u32 *recommended_buffer_size)
अणु

	u32 bytes_per_second;
	u32 size;
	u16 channels;
	काष्ठा hpi_क्रमmat *pF = p_क्रमmat;

	channels = pF->channels;

	चयन (pF->क्रमmat) अणु
	हाल HPI_FORMAT_PCM16_BIGENDIAN:
	हाल HPI_FORMAT_PCM16_SIGNED:
		bytes_per_second = pF->sample_rate * 2L * channels;
		अवरोध;
	हाल HPI_FORMAT_PCM24_SIGNED:
		bytes_per_second = pF->sample_rate * 3L * channels;
		अवरोध;
	हाल HPI_FORMAT_PCM32_SIGNED:
	हाल HPI_FORMAT_PCM32_FLOAT:
		bytes_per_second = pF->sample_rate * 4L * channels;
		अवरोध;
	हाल HPI_FORMAT_PCM8_UNSIGNED:
		bytes_per_second = pF->sample_rate * 1L * channels;
		अवरोध;
	हाल HPI_FORMAT_MPEG_L1:
	हाल HPI_FORMAT_MPEG_L2:
	हाल HPI_FORMAT_MPEG_L3:
		bytes_per_second = pF->bit_rate / 8L;
		अवरोध;
	हाल HPI_FORMAT_DOLBY_AC2:

		bytes_per_second = 256000L / 8L;
		अवरोध;
	शेष:
		वापस HPI_ERROR_INVALID_FORMAT;
	पूर्ण
	size = (bytes_per_second * host_polling_rate_in_milli_seconds * 2) /
		1000L;

	*recommended_buffer_size =
		roundup_घात_of_two(((size + 4095L) & ~4095L));
	वापस 0;
पूर्ण

u16 hpi_outstream_खोलो(u16 adapter_index, u16 outstream_index,
	u32 *ph_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_OPEN);
	hm.adapter_index = adapter_index;
	hm.obj_index = outstream_index;

	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0)
		*ph_outstream =
			hpi_indexes_to_handle(HPI_OBJ_OSTREAM, adapter_index,
			outstream_index);
	अन्यथा
		*ph_outstream = 0;
	वापस hr.error;
पूर्ण

u16 hpi_outstream_बंद(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_HOSTBUFFER_FREE);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_GROUP_RESET);
	hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index);
	hpi_send_recv(&hm, &hr);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_CLOSE);
	hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index);
	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_get_info_ex(u32 h_outstream, u16 *pw_state,
	u32 *pbuffer_size, u32 *pdata_to_play, u32 *psamples_played,
	u32 *pauxiliary_data_to_play)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_GET_INFO);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	अगर (pw_state)
		*pw_state = hr.u.d.u.stream_info.state;
	अगर (pbuffer_size)
		*pbuffer_size = hr.u.d.u.stream_info.buffer_size;
	अगर (pdata_to_play)
		*pdata_to_play = hr.u.d.u.stream_info.data_available;
	अगर (psamples_played)
		*psamples_played = hr.u.d.u.stream_info.samples_transferred;
	अगर (pauxiliary_data_to_play)
		*pauxiliary_data_to_play =
			hr.u.d.u.stream_info.auxiliary_data_available;
	वापस hr.error;
पूर्ण

u16 hpi_outstream_ग_लिखो_buf(u32 h_outstream, स्थिर u8 *pb_data,
	u32 bytes_to_ग_लिखो, स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_WRITE);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.pb_data = (u8 *)pb_data;
	hm.u.d.u.data.data_size = bytes_to_ग_लिखो;

	hpi_क्रमmat_to_msg(&hm.u.d.u.data.क्रमmat, p_क्रमmat);

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_start(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_START);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_रुको_start(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_WAIT_START);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_stop(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_STOP);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_sinegen(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SINEGEN);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_reset(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_RESET);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_query_क्रमmat(u32 h_outstream, काष्ठा hpi_क्रमmat *p_क्रमmat)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_QUERY_FORMAT);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_क्रमmat_to_msg(&hm.u.d.u.data.क्रमmat, p_क्रमmat);

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_set_क्रमmat(u32 h_outstream, काष्ठा hpi_क्रमmat *p_क्रमmat)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SET_FORMAT);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_क्रमmat_to_msg(&hm.u.d.u.data.क्रमmat, p_क्रमmat);

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_set_velocity(u32 h_outstream, लघु velocity)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SET_VELOCITY);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.velocity = velocity;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_set_punch_in_out(u32 h_outstream, u32 punch_in_sample,
	u32 punch_out_sample)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SET_PUNCHINOUT);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hm.u.d.u.pio.punch_in_sample = punch_in_sample;
	hm.u.d.u.pio.punch_out_sample = punch_out_sample;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_ancillary_reset(u32 h_outstream, u16 mode)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_ANC_RESET);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.क्रमmat.channels = mode;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_outstream_ancillary_get_info(u32 h_outstream, u32 *pframes_available)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_ANC_GET_INFO);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	अगर (hr.error == 0) अणु
		अगर (pframes_available)
			*pframes_available =
				hr.u.d.u.stream_info.data_available /
				माप(काष्ठा hpi_anc_frame);
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_outstream_ancillary_पढ़ो(u32 h_outstream,
	काष्ठा hpi_anc_frame *p_anc_frame_buffer,
	u32 anc_frame_buffer_size_in_bytes,
	u32 number_of_ancillary_frames_to_पढ़ो)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_ANC_READ);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.pb_data = (u8 *)p_anc_frame_buffer;
	hm.u.d.u.data.data_size =
		number_of_ancillary_frames_to_पढ़ो *
		माप(काष्ठा hpi_anc_frame);
	अगर (hm.u.d.u.data.data_size <= anc_frame_buffer_size_in_bytes)
		hpi_send_recv(&hm, &hr);
	अन्यथा
		hr.error = HPI_ERROR_INVALID_DATASIZE;
	वापस hr.error;
पूर्ण

u16 hpi_outstream_set_समय_scale(u32 h_outstream, u32 समय_scale)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_SET_TIMESCALE);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hm.u.d.u.समय_scale = समय_scale;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_outstream_host_buffer_allocate(u32 h_outstream, u32 size_in_bytes)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_HOSTBUFFER_ALLOC);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.data_size = size_in_bytes;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_outstream_host_buffer_get_info(u32 h_outstream, u8 **pp_buffer,
	काष्ठा hpi_hostbuffer_status **pp_status)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_HOSTBUFFER_GET_INFO);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0) अणु
		अगर (pp_buffer)
			*pp_buffer = hr.u.d.u.hostbuffer_info.p_buffer;
		अगर (pp_status)
			*pp_status = hr.u.d.u.hostbuffer_info.p_status;
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_outstream_host_buffer_मुक्त(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_HOSTBUFFER_FREE);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_outstream_group_add(u32 h_outstream, u32 h_stream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	u16 adapter;
	अक्षर c_obj_type;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_GROUP_ADD);

	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	अगर (hpi_handle_indexes(h_stream, &adapter,
			&hm.u.d.u.stream.stream_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	c_obj_type = hpi_handle_object(h_stream);
	चयन (c_obj_type) अणु
	हाल HPI_OBJ_OSTREAM:
	हाल HPI_OBJ_ISTREAM:
		hm.u.d.u.stream.object_type = c_obj_type;
		अवरोध;
	शेष:
		वापस HPI_ERROR_INVALID_OBJ;
	पूर्ण
	अगर (adapter != hm.adapter_index)
		वापस HPI_ERROR_NO_INTERADAPTER_GROUPS;

	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_outstream_group_get_map(u32 h_outstream, u32 *poutstream_map,
	u32 *pinstream_map)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_GROUP_GETMAP);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);

	अगर (poutstream_map)
		*poutstream_map = hr.u.d.u.group_info.outstream_group_map;
	अगर (pinstream_map)
		*pinstream_map = hr.u.d.u.group_info.instream_group_map;

	वापस hr.error;
पूर्ण

u16 hpi_outstream_group_reset(u32 h_outstream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
		HPI_OSTREAM_GROUP_RESET);
	अगर (hpi_handle_indexes(h_outstream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_instream_खोलो(u16 adapter_index, u16 instream_index, u32 *ph_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_OPEN);
	hm.adapter_index = adapter_index;
	hm.obj_index = instream_index;

	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0)
		*ph_instream =
			hpi_indexes_to_handle(HPI_OBJ_ISTREAM, adapter_index,
			instream_index);
	अन्यथा
		*ph_instream = 0;

	वापस hr.error;
पूर्ण

u16 hpi_instream_बंद(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_FREE);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GROUP_RESET);
	hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index);
	hpi_send_recv(&hm, &hr);

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_CLOSE);
	hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index);
	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_query_क्रमmat(u32 h_instream,
	स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_QUERY_FORMAT);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_क्रमmat_to_msg(&hm.u.d.u.data.क्रमmat, p_क्रमmat);

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_set_क्रमmat(u32 h_instream, स्थिर काष्ठा hpi_क्रमmat *p_क्रमmat)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_SET_FORMAT);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_क्रमmat_to_msg(&hm.u.d.u.data.क्रमmat, p_क्रमmat);

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_पढ़ो_buf(u32 h_instream, u8 *pb_data, u32 bytes_to_पढ़ो)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_READ);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.data_size = bytes_to_पढ़ो;
	hm.u.d.u.data.pb_data = pb_data;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_start(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_START);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_रुको_start(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_WAIT_START);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_stop(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_STOP);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_reset(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_RESET);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_instream_get_info_ex(u32 h_instream, u16 *pw_state, u32 *pbuffer_size,
	u32 *pdata_recorded, u32 *psamples_recorded,
	u32 *pauxiliary_data_recorded)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GET_INFO);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);

	अगर (pw_state)
		*pw_state = hr.u.d.u.stream_info.state;
	अगर (pbuffer_size)
		*pbuffer_size = hr.u.d.u.stream_info.buffer_size;
	अगर (pdata_recorded)
		*pdata_recorded = hr.u.d.u.stream_info.data_available;
	अगर (psamples_recorded)
		*psamples_recorded = hr.u.d.u.stream_info.samples_transferred;
	अगर (pauxiliary_data_recorded)
		*pauxiliary_data_recorded =
			hr.u.d.u.stream_info.auxiliary_data_available;
	वापस hr.error;
पूर्ण

u16 hpi_instream_ancillary_reset(u32 h_instream, u16 bytes_per_frame,
	u16 mode, u16 alignment, u16 idle_bit)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_RESET);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.क्रमmat.attributes = bytes_per_frame;
	hm.u.d.u.data.क्रमmat.क्रमmat = (mode << 8) | (alignment & 0xff);
	hm.u.d.u.data.क्रमmat.channels = idle_bit;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_instream_ancillary_get_info(u32 h_instream, u32 *pframe_space)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_GET_INFO);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	अगर (pframe_space)
		*pframe_space =
			(hr.u.d.u.stream_info.buffer_size -
			hr.u.d.u.stream_info.data_available) /
			माप(काष्ठा hpi_anc_frame);
	वापस hr.error;
पूर्ण

u16 hpi_instream_ancillary_ग_लिखो(u32 h_instream,
	स्थिर काष्ठा hpi_anc_frame *p_anc_frame_buffer,
	u32 anc_frame_buffer_size_in_bytes,
	u32 number_of_ancillary_frames_to_ग_लिखो)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_ANC_WRITE);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.pb_data = (u8 *)p_anc_frame_buffer;
	hm.u.d.u.data.data_size =
		number_of_ancillary_frames_to_ग_लिखो *
		माप(काष्ठा hpi_anc_frame);
	अगर (hm.u.d.u.data.data_size <= anc_frame_buffer_size_in_bytes)
		hpi_send_recv(&hm, &hr);
	अन्यथा
		hr.error = HPI_ERROR_INVALID_DATASIZE;
	वापस hr.error;
पूर्ण

u16 hpi_instream_host_buffer_allocate(u32 h_instream, u32 size_in_bytes)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_ALLOC);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.d.u.data.data_size = size_in_bytes;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_instream_host_buffer_get_info(u32 h_instream, u8 **pp_buffer,
	काष्ठा hpi_hostbuffer_status **pp_status)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_GET_INFO);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0) अणु
		अगर (pp_buffer)
			*pp_buffer = hr.u.d.u.hostbuffer_info.p_buffer;
		अगर (pp_status)
			*pp_status = hr.u.d.u.hostbuffer_info.p_status;
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_instream_host_buffer_मुक्त(u32 h_instream)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_FREE);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_instream_group_add(u32 h_instream, u32 h_stream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	u16 adapter;
	अक्षर c_obj_type;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GROUP_ADD);
	hr.error = 0;

	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	अगर (hpi_handle_indexes(h_stream, &adapter,
			&hm.u.d.u.stream.stream_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	c_obj_type = hpi_handle_object(h_stream);

	चयन (c_obj_type) अणु
	हाल HPI_OBJ_OSTREAM:
	हाल HPI_OBJ_ISTREAM:
		hm.u.d.u.stream.object_type = c_obj_type;
		अवरोध;
	शेष:
		वापस HPI_ERROR_INVALID_OBJ;
	पूर्ण

	अगर (adapter != hm.adapter_index)
		वापस HPI_ERROR_NO_INTERADAPTER_GROUPS;

	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_instream_group_get_map(u32 h_instream, u32 *poutstream_map,
	u32 *pinstream_map)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_HOSTBUFFER_FREE);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);

	अगर (poutstream_map)
		*poutstream_map = hr.u.d.u.group_info.outstream_group_map;
	अगर (pinstream_map)
		*pinstream_map = hr.u.d.u.group_info.instream_group_map;

	वापस hr.error;
पूर्ण

u16 hpi_instream_group_reset(u32 h_instream)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
		HPI_ISTREAM_GROUP_RESET);
	अगर (hpi_handle_indexes(h_instream, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_mixer_खोलो(u16 adapter_index, u32 *ph_mixer)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER, HPI_MIXER_OPEN);
	hm.adapter_index = adapter_index;

	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0)
		*ph_mixer =
			hpi_indexes_to_handle(HPI_OBJ_MIXER, adapter_index,
			0);
	अन्यथा
		*ph_mixer = 0;
	वापस hr.error;
पूर्ण

u16 hpi_mixer_बंद(u32 h_mixer)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER, HPI_MIXER_CLOSE);
	अगर (hpi_handle_indexes(h_mixer, &hm.adapter_index, शून्य))
		वापस HPI_ERROR_INVALID_HANDLE;

	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_mixer_get_control(u32 h_mixer, u16 src_node_type,
	u16 src_node_type_index, u16 dst_node_type, u16 dst_node_type_index,
	u16 control_type, u32 *ph_control)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER,
		HPI_MIXER_GET_CONTROL);
	अगर (hpi_handle_indexes(h_mixer, &hm.adapter_index, शून्य))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.m.node_type1 = src_node_type;
	hm.u.m.node_index1 = src_node_type_index;
	hm.u.m.node_type2 = dst_node_type;
	hm.u.m.node_index2 = dst_node_type_index;
	hm.u.m.control_type = control_type;

	hpi_send_recv(&hm, &hr);

	अगर (hr.error == 0)
		*ph_control =
			hpi_indexes_to_handle(HPI_OBJ_CONTROL,
			hm.adapter_index, hr.u.m.control_index);
	अन्यथा
		*ph_control = 0;
	वापस hr.error;
पूर्ण

u16 hpi_mixer_get_control_by_index(u32 h_mixer, u16 control_index,
	u16 *pw_src_node_type, u16 *pw_src_node_index, u16 *pw_dst_node_type,
	u16 *pw_dst_node_index, u16 *pw_control_type, u32 *ph_control)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER,
		HPI_MIXER_GET_CONTROL_BY_INDEX);
	अगर (hpi_handle_indexes(h_mixer, &hm.adapter_index, शून्य))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.m.control_index = control_index;
	hpi_send_recv(&hm, &hr);

	अगर (pw_src_node_type) अणु
		*pw_src_node_type =
			hr.u.m.src_node_type + HPI_SOURCENODE_NONE;
		*pw_src_node_index = hr.u.m.src_node_index;
		*pw_dst_node_type = hr.u.m.dst_node_type + HPI_DESTNODE_NONE;
		*pw_dst_node_index = hr.u.m.dst_node_index;
	पूर्ण
	अगर (pw_control_type)
		*pw_control_type = hr.u.m.control_index;

	अगर (ph_control) अणु
		अगर (hr.error == 0)
			*ph_control =
				hpi_indexes_to_handle(HPI_OBJ_CONTROL,
				hm.adapter_index, control_index);
		अन्यथा
			*ph_control = 0;
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_mixer_store(u32 h_mixer, क्रमागत HPI_MIXER_STORE_COMMAND command,
	u16 index)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER, HPI_MIXER_STORE);
	अगर (hpi_handle_indexes(h_mixer, &hm.adapter_index, शून्य))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.mx.store.command = command;
	hm.u.mx.store.index = index;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

अटल
u16 hpi_control_param_set(स्थिर u32 h_control, स्थिर u16 attrib,
	स्थिर u32 param1, स्थिर u32 param2)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = attrib;
	hm.u.c.param1 = param1;
	hm.u.c.param2 = param2;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

अटल u16 hpi_control_log_set2(u32 h_control, u16 attrib, लघु sv0,
	लघु sv1)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = attrib;
	hm.u.c.an_log_value[0] = sv0;
	hm.u.c.an_log_value[1] = sv1;
	hpi_send_recv(&hm, &hr);
	वापस hr.error;
पूर्ण

अटल
u16 hpi_control_param_get(स्थिर u32 h_control, स्थिर u16 attrib, u32 param1,
	u32 param2, u32 *pparam1, u32 *pparam2)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = attrib;
	hm.u.c.param1 = param1;
	hm.u.c.param2 = param2;
	hpi_send_recv(&hm, &hr);

	*pparam1 = hr.u.c.param1;
	अगर (pparam2)
		*pparam2 = hr.u.c.param2;

	वापस hr.error;
पूर्ण

#घोषणा hpi_control_param1_get(h, a, p1) \
		hpi_control_param_get(h, a, 0, 0, p1, शून्य)
#घोषणा hpi_control_param2_get(h, a, p1, p2) \
		hpi_control_param_get(h, a, 0, 0, p1, p2)

अटल u16 hpi_control_log_get2(u32 h_control, u16 attrib, लघु *sv0,
	लघु *sv1)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = attrib;

	hpi_send_recv(&hm, &hr);
	*sv0 = hr.u.c.an_log_value[0];
	अगर (sv1)
		*sv1 = hr.u.c.an_log_value[1];
	वापस hr.error;
पूर्ण

अटल
u16 hpi_control_query(स्थिर u32 h_control, स्थिर u16 attrib, स्थिर u32 index,
	स्थिर u32 param, u32 *psetting)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_INFO);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hm.u.c.attribute = attrib;
	hm.u.c.param1 = index;
	hm.u.c.param2 = param;

	hpi_send_recv(&hm, &hr);
	*psetting = hr.u.c.param1;

	वापस hr.error;
पूर्ण

अटल u16 hpi_control_get_string(स्थिर u32 h_control, स्थिर u16 attribute,
	अक्षर *psz_string, स्थिर u32 string_length)
अणु
	अचिन्हित पूर्णांक sub_string_index = 0, j = 0;
	अक्षर c = 0;
	अचिन्हित पूर्णांक n = 0;
	u16 err = 0;

	अगर ((string_length < 1) || (string_length > 256))
		वापस HPI_ERROR_INVALID_CONTROL_VALUE;
	क्रम (sub_string_index = 0; sub_string_index < string_length;
		sub_string_index += 8) अणु
		काष्ठा hpi_message hm;
		काष्ठा hpi_response hr;

		hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
			HPI_CONTROL_GET_STATE);
		अगर (hpi_handle_indexes(h_control, &hm.adapter_index,
				&hm.obj_index))
			वापस HPI_ERROR_INVALID_HANDLE;
		hm.u.c.attribute = attribute;
		hm.u.c.param1 = sub_string_index;
		hm.u.c.param2 = 0;
		hpi_send_recv(&hm, &hr);

		अगर (sub_string_index == 0
			&& (hr.u.cu.अक्षरs8.reमुख्यing_अक्षरs + 8) >
			string_length)
			वापस HPI_ERROR_INVALID_CONTROL_VALUE;

		अगर (hr.error) अणु
			err = hr.error;
			अवरोध;
		पूर्ण
		क्रम (j = 0; j < 8; j++) अणु
			c = hr.u.cu.अक्षरs8.sz_data[j];
			psz_string[sub_string_index + j] = c;
			n++;
			अगर (n >= string_length) अणु
				psz_string[string_length - 1] = 0;
				err = HPI_ERROR_INVALID_CONTROL_VALUE;
				अवरोध;
			पूर्ण
			अगर (c == 0)
				अवरोध;
		पूर्ण

		अगर ((hr.u.cu.अक्षरs8.reमुख्यing_अक्षरs == 0)
			&& ((sub_string_index + j) < string_length)
			&& (c != 0)) अणु
			c = 0;
			psz_string[sub_string_index + j] = c;
		पूर्ण
		अगर (c == 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

u16 hpi_aesebu_receiver_query_क्रमmat(स्थिर u32 h_aes_rx, स्थिर u32 index,
	u16 *pw_क्रमmat)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_aes_rx, HPI_AESEBURX_FORMAT, index, 0, &qr);
	*pw_क्रमmat = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_aesebu_receiver_set_क्रमmat(u32 h_control, u16 क्रमmat)
अणु
	वापस hpi_control_param_set(h_control, HPI_AESEBURX_FORMAT, क्रमmat,
		0);
पूर्ण

u16 hpi_aesebu_receiver_get_क्रमmat(u32 h_control, u16 *pw_क्रमmat)
अणु
	u16 err;
	u32 param;

	err = hpi_control_param1_get(h_control, HPI_AESEBURX_FORMAT, &param);
	अगर (!err && pw_क्रमmat)
		*pw_क्रमmat = (u16)param;

	वापस err;
पूर्ण

u16 hpi_aesebu_receiver_get_sample_rate(u32 h_control, u32 *psample_rate)
अणु
	वापस hpi_control_param1_get(h_control, HPI_AESEBURX_SAMPLERATE,
		psample_rate);
पूर्ण

u16 hpi_aesebu_receiver_get_user_data(u32 h_control, u16 index, u16 *pw_data)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_AESEBURX_USERDATA;
	hm.u.c.param1 = index;

	hpi_send_recv(&hm, &hr);

	अगर (pw_data)
		*pw_data = (u16)hr.u.c.param2;
	वापस hr.error;
पूर्ण

u16 hpi_aesebu_receiver_get_channel_status(u32 h_control, u16 index,
	u16 *pw_data)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_AESEBURX_CHANNELSTATUS;
	hm.u.c.param1 = index;

	hpi_send_recv(&hm, &hr);

	अगर (pw_data)
		*pw_data = (u16)hr.u.c.param2;
	वापस hr.error;
पूर्ण

u16 hpi_aesebu_receiver_get_error_status(u32 h_control, u16 *pw_error_data)
अणु
	u32 error_data = 0;
	u16 err = 0;

	err = hpi_control_param1_get(h_control, HPI_AESEBURX_ERRORSTATUS,
		&error_data);
	अगर (pw_error_data)
		*pw_error_data = (u16)error_data;
	वापस err;
पूर्ण

u16 hpi_aesebu_transmitter_set_sample_rate(u32 h_control, u32 sample_rate)
अणु
	वापस hpi_control_param_set(h_control, HPI_AESEBUTX_SAMPLERATE,
		sample_rate, 0);
पूर्ण

u16 hpi_aesebu_transmitter_set_user_data(u32 h_control, u16 index, u16 data)
अणु
	वापस hpi_control_param_set(h_control, HPI_AESEBUTX_USERDATA, index,
		data);
पूर्ण

u16 hpi_aesebu_transmitter_set_channel_status(u32 h_control, u16 index,
	u16 data)
अणु
	वापस hpi_control_param_set(h_control, HPI_AESEBUTX_CHANNELSTATUS,
		index, data);
पूर्ण

u16 hpi_aesebu_transmitter_get_channel_status(u32 h_control, u16 index,
	u16 *pw_data)
अणु
	वापस HPI_ERROR_INVALID_OPERATION;
पूर्ण

u16 hpi_aesebu_transmitter_query_क्रमmat(स्थिर u32 h_aes_tx, स्थिर u32 index,
	u16 *pw_क्रमmat)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_aes_tx, HPI_AESEBUTX_FORMAT, index, 0, &qr);
	*pw_क्रमmat = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_aesebu_transmitter_set_क्रमmat(u32 h_control, u16 output_क्रमmat)
अणु
	वापस hpi_control_param_set(h_control, HPI_AESEBUTX_FORMAT,
		output_क्रमmat, 0);
पूर्ण

u16 hpi_aesebu_transmitter_get_क्रमmat(u32 h_control, u16 *pw_output_क्रमmat)
अणु
	u16 err;
	u32 param;

	err = hpi_control_param1_get(h_control, HPI_AESEBUTX_FORMAT, &param);
	अगर (!err && pw_output_क्रमmat)
		*pw_output_क्रमmat = (u16)param;

	वापस err;
पूर्ण

u16 hpi_bitstream_set_घड़ी_edge(u32 h_control, u16 edge_type)
अणु
	वापस hpi_control_param_set(h_control, HPI_BITSTREAM_CLOCK_EDGE,
		edge_type, 0);
पूर्ण

u16 hpi_bitstream_set_data_polarity(u32 h_control, u16 polarity)
अणु
	वापस hpi_control_param_set(h_control, HPI_BITSTREAM_DATA_POLARITY,
		polarity, 0);
पूर्ण

u16 hpi_bitstream_get_activity(u32 h_control, u16 *pw_clk_activity,
	u16 *pw_data_activity)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_BITSTREAM_ACTIVITY;
	hpi_send_recv(&hm, &hr);
	अगर (pw_clk_activity)
		*pw_clk_activity = (u16)hr.u.c.param1;
	अगर (pw_data_activity)
		*pw_data_activity = (u16)hr.u.c.param2;
	वापस hr.error;
पूर्ण

u16 hpi_channel_mode_query_mode(स्थिर u32 h_mode, स्थिर u32 index,
	u16 *pw_mode)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_mode, HPI_CHANNEL_MODE_MODE, index, 0, &qr);
	*pw_mode = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_channel_mode_set(u32 h_control, u16 mode)
अणु
	वापस hpi_control_param_set(h_control, HPI_CHANNEL_MODE_MODE, mode,
		0);
पूर्ण

u16 hpi_channel_mode_get(u32 h_control, u16 *mode)
अणु
	u32 mode32 = 0;
	u16 err = hpi_control_param1_get(h_control,
		HPI_CHANNEL_MODE_MODE, &mode32);
	अगर (mode)
		*mode = (u16)mode32;
	वापस err;
पूर्ण

u16 hpi_cobranet_hmi_ग_लिखो(u32 h_control, u32 hmi_address, u32 byte_count,
	u8 *pb_data)
अणु
	काष्ठा hpi_msg_cobranet_hmiग_लिखो hm;
	काष्ठा hpi_response_header hr;

	hpi_init_message_responseV1(&hm.h, माप(hm), &hr, माप(hr),
		HPI_OBJ_CONTROL, HPI_CONTROL_SET_STATE);

	अगर (hpi_handle_indexes(h_control, &hm.h.adapter_index,
			&hm.h.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	अगर (byte_count > माप(hm.bytes))
		वापस HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL;

	hm.p.attribute = HPI_COBRANET_SET;
	hm.p.byte_count = byte_count;
	hm.p.hmi_address = hmi_address;
	स_नकल(hm.bytes, pb_data, byte_count);
	hm.h.size = (u16)(माप(hm.h) + माप(hm.p) + byte_count);

	hpi_send_recvV1(&hm.h, &hr);
	वापस hr.error;
पूर्ण

u16 hpi_cobranet_hmi_पढ़ो(u32 h_control, u32 hmi_address, u32 max_byte_count,
	u32 *pbyte_count, u8 *pb_data)
अणु
	काष्ठा hpi_msg_cobranet_hmiपढ़ो hm;
	काष्ठा hpi_res_cobranet_hmiपढ़ो hr;

	hpi_init_message_responseV1(&hm.h, माप(hm), &hr.h, माप(hr),
		HPI_OBJ_CONTROL, HPI_CONTROL_GET_STATE);

	अगर (hpi_handle_indexes(h_control, &hm.h.adapter_index,
			&hm.h.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	अगर (max_byte_count > माप(hr.bytes))
		वापस HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

	hm.p.attribute = HPI_COBRANET_GET;
	hm.p.byte_count = max_byte_count;
	hm.p.hmi_address = hmi_address;

	hpi_send_recvV1(&hm.h, &hr.h);

	अगर (!hr.h.error && pb_data) अणु
		अगर (hr.byte_count > माप(hr.bytes))

			वापस HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

		*pbyte_count = hr.byte_count;

		अगर (hr.byte_count < max_byte_count)
			max_byte_count = *pbyte_count;

		स_नकल(pb_data, hr.bytes, max_byte_count);
	पूर्ण
	वापस hr.h.error;
पूर्ण

u16 hpi_cobranet_hmi_get_status(u32 h_control, u32 *pstatus,
	u32 *pपढ़ोable_size, u32 *pग_लिखोable_size)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hm.u.c.attribute = HPI_COBRANET_GET_STATUS;

	hpi_send_recv(&hm, &hr);
	अगर (!hr.error) अणु
		अगर (pstatus)
			*pstatus = hr.u.cu.cobranet.status.status;
		अगर (pपढ़ोable_size)
			*pपढ़ोable_size =
				hr.u.cu.cobranet.status.पढ़ोable_size;
		अगर (pग_लिखोable_size)
			*pग_लिखोable_size =
				hr.u.cu.cobranet.status.ग_लिखोable_size;
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_cobranet_get_ip_address(u32 h_control, u32 *pdw_ip_address)
अणु
	u32 byte_count;
	u32 iP;
	u16 err;

	err = hpi_cobranet_hmi_पढ़ो(h_control,
		HPI_COBRANET_HMI_cobra_ip_mon_currentIP, 4, &byte_count,
		(u8 *)&iP);

	*pdw_ip_address =
		((iP & 0xff000000) >> 8) | ((iP & 0x00ff0000) << 8) | ((iP &
			0x0000ff00) >> 8) | ((iP & 0x000000ff) << 8);

	अगर (err)
		*pdw_ip_address = 0;

	वापस err;

पूर्ण

u16 hpi_cobranet_set_ip_address(u32 h_control, u32 dw_ip_address)
अणु
	u32 iP;
	u16 err;

	iP = ((dw_ip_address & 0xff000000) >> 8) | ((dw_ip_address &
			0x00ff0000) << 8) | ((dw_ip_address & 0x0000ff00) >>
		8) | ((dw_ip_address & 0x000000ff) << 8);

	err = hpi_cobranet_hmi_ग_लिखो(h_control,
		HPI_COBRANET_HMI_cobra_ip_mon_currentIP, 4, (u8 *)&iP);

	वापस err;

पूर्ण

u16 hpi_cobranet_get_अटल_ip_address(u32 h_control, u32 *pdw_ip_address)
अणु
	u32 byte_count;
	u32 iP;
	u16 err;
	err = hpi_cobranet_hmi_पढ़ो(h_control,
		HPI_COBRANET_HMI_cobra_ip_mon_अटलIP, 4, &byte_count,
		(u8 *)&iP);

	*pdw_ip_address =
		((iP & 0xff000000) >> 8) | ((iP & 0x00ff0000) << 8) | ((iP &
			0x0000ff00) >> 8) | ((iP & 0x000000ff) << 8);

	अगर (err)
		*pdw_ip_address = 0;

	वापस err;

पूर्ण

u16 hpi_cobranet_set_अटल_ip_address(u32 h_control, u32 dw_ip_address)
अणु
	u32 iP;
	u16 err;

	iP = ((dw_ip_address & 0xff000000) >> 8) | ((dw_ip_address &
			0x00ff0000) << 8) | ((dw_ip_address & 0x0000ff00) >>
		8) | ((dw_ip_address & 0x000000ff) << 8);

	err = hpi_cobranet_hmi_ग_लिखो(h_control,
		HPI_COBRANET_HMI_cobra_ip_mon_अटलIP, 4, (u8 *)&iP);

	वापस err;

पूर्ण

u16 hpi_cobranet_get_macaddress(u32 h_control, u32 *p_mac_msbs,
	u32 *p_mac_lsbs)
अणु
	u32 byte_count;
	u16 err;
	u32 mac;

	err = hpi_cobranet_hmi_पढ़ो(h_control,
		HPI_COBRANET_HMI_cobra_अगर_phy_address, 4, &byte_count,
		(u8 *)&mac);

	अगर (!err) अणु
		*p_mac_msbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);

		err = hpi_cobranet_hmi_पढ़ो(h_control,
			HPI_COBRANET_HMI_cobra_अगर_phy_address + 1, 4,
			&byte_count, (u8 *)&mac);
	पूर्ण

	अगर (!err) अणु
		*p_mac_lsbs =
			((mac & 0xff000000) >> 8) | ((mac & 0x00ff0000) << 8)
			| ((mac & 0x0000ff00) >> 8) | ((mac & 0x000000ff) <<
			8);
	पूर्ण अन्यथा अणु
		*p_mac_msbs = 0;
		*p_mac_lsbs = 0;
	पूर्ण

	वापस err;
पूर्ण

u16 hpi_compander_set_enable(u32 h_control, u32 enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_GENERIC_ENABLE, enable,
		0);
पूर्ण

u16 hpi_compander_get_enable(u32 h_control, u32 *enable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_GENERIC_ENABLE, enable);
पूर्ण

u16 hpi_compander_set_makeup_gain(u32 h_control, लघु makeup_gain0_01dB)
अणु
	वापस hpi_control_log_set2(h_control, HPI_COMPANDER_MAKEUPGAIN,
		makeup_gain0_01dB, 0);
पूर्ण

u16 hpi_compander_get_makeup_gain(u32 h_control, लघु *makeup_gain0_01dB)
अणु
	वापस hpi_control_log_get2(h_control, HPI_COMPANDER_MAKEUPGAIN,
		makeup_gain0_01dB, शून्य);
पूर्ण

u16 hpi_compander_set_attack_समय_स्थिरant(u32 h_control, अचिन्हित पूर्णांक index,
	u32 attack)
अणु
	वापस hpi_control_param_set(h_control, HPI_COMPANDER_ATTACK, attack,
		index);
पूर्ण

u16 hpi_compander_get_attack_समय_स्थिरant(u32 h_control, अचिन्हित पूर्णांक index,
	u32 *attack)
अणु
	वापस hpi_control_param_get(h_control, HPI_COMPANDER_ATTACK, 0,
		index, attack, शून्य);
पूर्ण

u16 hpi_compander_set_decay_समय_स्थिरant(u32 h_control, अचिन्हित पूर्णांक index,
	u32 decay)
अणु
	वापस hpi_control_param_set(h_control, HPI_COMPANDER_DECAY, decay,
		index);
पूर्ण

u16 hpi_compander_get_decay_समय_स्थिरant(u32 h_control, अचिन्हित पूर्णांक index,
	u32 *decay)
अणु
	वापस hpi_control_param_get(h_control, HPI_COMPANDER_DECAY, 0, index,
		decay, शून्य);

पूर्ण

u16 hpi_compander_set_threshold(u32 h_control, अचिन्हित पूर्णांक index,
	लघु threshold0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_COMPANDER_THRESHOLD;
	hm.u.c.param2 = index;
	hm.u.c.an_log_value[0] = threshold0_01dB;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_compander_get_threshold(u32 h_control, अचिन्हित पूर्णांक index,
	लघु *threshold0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_COMPANDER_THRESHOLD;
	hm.u.c.param2 = index;

	hpi_send_recv(&hm, &hr);
	*threshold0_01dB = hr.u.c.an_log_value[0];

	वापस hr.error;
पूर्ण

u16 hpi_compander_set_ratio(u32 h_control, u32 index, u32 ratio100)
अणु
	वापस hpi_control_param_set(h_control, HPI_COMPANDER_RATIO, ratio100,
		index);
पूर्ण

u16 hpi_compander_get_ratio(u32 h_control, u32 index, u32 *ratio100)
अणु
	वापस hpi_control_param_get(h_control, HPI_COMPANDER_RATIO, 0, index,
		ratio100, शून्य);
पूर्ण

u16 hpi_level_query_range(u32 h_control, लघु *min_gain_01dB,
	लघु *max_gain_01dB, लघु *step_gain_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_LEVEL_RANGE;

	hpi_send_recv(&hm, &hr);
	अगर (hr.error) अणु
		hr.u.c.an_log_value[0] = 0;
		hr.u.c.an_log_value[1] = 0;
		hr.u.c.param1 = 0;
	पूर्ण
	अगर (min_gain_01dB)
		*min_gain_01dB = hr.u.c.an_log_value[0];
	अगर (max_gain_01dB)
		*max_gain_01dB = hr.u.c.an_log_value[1];
	अगर (step_gain_01dB)
		*step_gain_01dB = (लघु)hr.u.c.param1;
	वापस hr.error;
पूर्ण

u16 hpi_level_set_gain(u32 h_control, लघु an_gain0_01dB[HPI_MAX_CHANNELS]
	)
अणु
	वापस hpi_control_log_set2(h_control, HPI_LEVEL_GAIN,
		an_gain0_01dB[0], an_gain0_01dB[1]);
पूर्ण

u16 hpi_level_get_gain(u32 h_control, लघु an_gain0_01dB[HPI_MAX_CHANNELS]
	)
अणु
	वापस hpi_control_log_get2(h_control, HPI_LEVEL_GAIN,
		&an_gain0_01dB[0], &an_gain0_01dB[1]);
पूर्ण

u16 hpi_meter_query_channels(स्थिर u32 h_meter, u32 *p_channels)
अणु
	वापस hpi_control_query(h_meter, HPI_METER_NUM_CHANNELS, 0, 0,
		p_channels);
पूर्ण

u16 hpi_meter_get_peak(u32 h_control, लघु an_peakdB[HPI_MAX_CHANNELS]
	)
अणु
	लघु i = 0;

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.obj_index = hm.obj_index;
	hm.u.c.attribute = HPI_METER_PEAK;

	hpi_send_recv(&hm, &hr);

	अगर (!hr.error)
		स_नकल(an_peakdB, hr.u.c.an_log_value,
			माप(लघु) * HPI_MAX_CHANNELS);
	अन्यथा
		क्रम (i = 0; i < HPI_MAX_CHANNELS; i++)
			an_peakdB[i] = HPI_METER_MINIMUM;
	वापस hr.error;
पूर्ण

u16 hpi_meter_get_rms(u32 h_control, लघु an_rmsdB[HPI_MAX_CHANNELS]
	)
अणु
	लघु i = 0;

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_METER_RMS;

	hpi_send_recv(&hm, &hr);

	अगर (!hr.error)
		स_नकल(an_rmsdB, hr.u.c.an_log_value,
			माप(लघु) * HPI_MAX_CHANNELS);
	अन्यथा
		क्रम (i = 0; i < HPI_MAX_CHANNELS; i++)
			an_rmsdB[i] = HPI_METER_MINIMUM;

	वापस hr.error;
पूर्ण

u16 hpi_meter_set_rms_ballistics(u32 h_control, u16 attack, u16 decay)
अणु
	वापस hpi_control_param_set(h_control, HPI_METER_RMS_BALLISTICS,
		attack, decay);
पूर्ण

u16 hpi_meter_get_rms_ballistics(u32 h_control, u16 *pn_attack, u16 *pn_decay)
अणु
	u32 attack;
	u32 decay;
	u16 error;

	error = hpi_control_param2_get(h_control, HPI_METER_RMS_BALLISTICS,
		&attack, &decay);

	अगर (pn_attack)
		*pn_attack = (अचिन्हित लघु)attack;
	अगर (pn_decay)
		*pn_decay = (अचिन्हित लघु)decay;

	वापस error;
पूर्ण

u16 hpi_meter_set_peak_ballistics(u32 h_control, u16 attack, u16 decay)
अणु
	वापस hpi_control_param_set(h_control, HPI_METER_PEAK_BALLISTICS,
		attack, decay);
पूर्ण

u16 hpi_meter_get_peak_ballistics(u32 h_control, u16 *pn_attack,
	u16 *pn_decay)
अणु
	u32 attack;
	u32 decay;
	u16 error;

	error = hpi_control_param2_get(h_control, HPI_METER_PEAK_BALLISTICS,
		&attack, &decay);

	अगर (pn_attack)
		*pn_attack = (लघु)attack;
	अगर (pn_decay)
		*pn_decay = (लघु)decay;

	वापस error;
पूर्ण

u16 hpi_microphone_set_phantom_घातer(u32 h_control, u16 on_off)
अणु
	वापस hpi_control_param_set(h_control, HPI_MICROPHONE_PHANTOM_POWER,
		(u32)on_off, 0);
पूर्ण

u16 hpi_microphone_get_phantom_घातer(u32 h_control, u16 *pw_on_off)
अणु
	u16 error = 0;
	u32 on_off = 0;
	error = hpi_control_param1_get(h_control,
		HPI_MICROPHONE_PHANTOM_POWER, &on_off);
	अगर (pw_on_off)
		*pw_on_off = (u16)on_off;
	वापस error;
पूर्ण

u16 hpi_multiplexer_set_source(u32 h_control, u16 source_node_type,
	u16 source_node_index)
अणु
	वापस hpi_control_param_set(h_control, HPI_MULTIPLEXER_SOURCE,
		source_node_type, source_node_index);
पूर्ण

u16 hpi_multiplexer_get_source(u32 h_control, u16 *source_node_type,
	u16 *source_node_index)
अणु
	u32 node, index;
	u16 err = hpi_control_param2_get(h_control,
		HPI_MULTIPLEXER_SOURCE, &node,
		&index);
	अगर (source_node_type)
		*source_node_type = (u16)node;
	अगर (source_node_index)
		*source_node_index = (u16)index;
	वापस err;
पूर्ण

u16 hpi_multiplexer_query_source(u32 h_control, u16 index,
	u16 *source_node_type, u16 *source_node_index)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_MULTIPLEXER_QUERYSOURCE;
	hm.u.c.param1 = index;

	hpi_send_recv(&hm, &hr);

	अगर (source_node_type)
		*source_node_type = (u16)hr.u.c.param1;
	अगर (source_node_index)
		*source_node_index = (u16)hr.u.c.param2;
	वापस hr.error;
पूर्ण

u16 hpi_parametric_eq_get_info(u32 h_control, u16 *pw_number_of_bands,
	u16 *pw_on_off)
अणु
	u32 oB = 0;
	u32 oO = 0;
	u16 error = 0;

	error = hpi_control_param2_get(h_control, HPI_EQUALIZER_NUM_FILTERS,
		&oO, &oB);
	अगर (pw_number_of_bands)
		*pw_number_of_bands = (u16)oB;
	अगर (pw_on_off)
		*pw_on_off = (u16)oO;
	वापस error;
पूर्ण

u16 hpi_parametric_eq_set_state(u32 h_control, u16 on_off)
अणु
	वापस hpi_control_param_set(h_control, HPI_EQUALIZER_NUM_FILTERS,
		on_off, 0);
पूर्ण

u16 hpi_parametric_eq_get_band(u32 h_control, u16 index, u16 *pn_type,
	u32 *pfrequency_hz, लघु *pnQ100, लघु *pn_gain0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_EQUALIZER_FILTER;
	hm.u.c.param2 = index;

	hpi_send_recv(&hm, &hr);

	अगर (pfrequency_hz)
		*pfrequency_hz = hr.u.c.param1;
	अगर (pn_type)
		*pn_type = (u16)(hr.u.c.param2 >> 16);
	अगर (pnQ100)
		*pnQ100 = hr.u.c.an_log_value[1];
	अगर (pn_gain0_01dB)
		*pn_gain0_01dB = hr.u.c.an_log_value[0];

	वापस hr.error;
पूर्ण

u16 hpi_parametric_eq_set_band(u32 h_control, u16 index, u16 type,
	u32 frequency_hz, लघु q100, लघु gain0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	hm.u.c.param1 = frequency_hz;
	hm.u.c.param2 = (index & 0xFFFFL) + ((u32)type << 16);
	hm.u.c.an_log_value[0] = gain0_01dB;
	hm.u.c.an_log_value[1] = q100;
	hm.u.c.attribute = HPI_EQUALIZER_FILTER;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_parametric_eq_get_coeffs(u32 h_control, u16 index, लघु coeffs[5]
	)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_EQUALIZER_COEFFICIENTS;
	hm.u.c.param2 = index;

	hpi_send_recv(&hm, &hr);

	coeffs[0] = (लघु)hr.u.c.an_log_value[0];
	coeffs[1] = (लघु)hr.u.c.an_log_value[1];
	coeffs[2] = (लघु)hr.u.c.param1;
	coeffs[3] = (लघु)(hr.u.c.param1 >> 16);
	coeffs[4] = (लघु)hr.u.c.param2;

	वापस hr.error;
पूर्ण

u16 hpi_sample_घड़ी_query_source(स्थिर u32 h_घड़ी, स्थिर u32 index,
	u16 *pw_source)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_घड़ी, HPI_SAMPLECLOCK_SOURCE, index, 0,
		&qr);
	*pw_source = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_set_source(u32 h_control, u16 source)
अणु
	वापस hpi_control_param_set(h_control, HPI_SAMPLECLOCK_SOURCE,
		source, 0);
पूर्ण

u16 hpi_sample_घड़ी_get_source(u32 h_control, u16 *pw_source)
अणु
	u16 err = 0;
	u32 source = 0;
	err = hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_SOURCE,
		&source);
	अगर (!err)
		अगर (pw_source)
			*pw_source = (u16)source;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_query_source_index(स्थिर u32 h_घड़ी, स्थिर u32 index,
	स्थिर u32 source, u16 *pw_source_index)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_घड़ी, HPI_SAMPLECLOCK_SOURCE_INDEX, index,
		source, &qr);
	*pw_source_index = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_set_source_index(u32 h_control, u16 source_index)
अणु
	वापस hpi_control_param_set(h_control, HPI_SAMPLECLOCK_SOURCE_INDEX,
		source_index, 0);
पूर्ण

u16 hpi_sample_घड़ी_get_source_index(u32 h_control, u16 *pw_source_index)
अणु
	u16 err = 0;
	u32 source_index = 0;
	err = hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_SOURCE_INDEX,
		&source_index);
	अगर (!err)
		अगर (pw_source_index)
			*pw_source_index = (u16)source_index;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_query_local_rate(स्थिर u32 h_घड़ी, स्थिर u32 index,
	u32 *prate)
अणु
	वापस hpi_control_query(h_घड़ी, HPI_SAMPLECLOCK_LOCAL_SAMPLERATE,
				 index, 0, prate);
पूर्ण

u16 hpi_sample_घड़ी_set_local_rate(u32 h_control, u32 sample_rate)
अणु
	वापस hpi_control_param_set(h_control,
		HPI_SAMPLECLOCK_LOCAL_SAMPLERATE, sample_rate, 0);
पूर्ण

u16 hpi_sample_घड़ी_get_local_rate(u32 h_control, u32 *psample_rate)
अणु
	u16 err = 0;
	u32 sample_rate = 0;
	err = hpi_control_param1_get(h_control,
		HPI_SAMPLECLOCK_LOCAL_SAMPLERATE, &sample_rate);
	अगर (!err)
		अगर (psample_rate)
			*psample_rate = sample_rate;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_get_sample_rate(u32 h_control, u32 *psample_rate)
अणु
	u16 err = 0;
	u32 sample_rate = 0;
	err = hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_SAMPLERATE,
		&sample_rate);
	अगर (!err)
		अगर (psample_rate)
			*psample_rate = sample_rate;
	वापस err;
पूर्ण

u16 hpi_sample_घड़ी_set_स्वतः(u32 h_control, u32 enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_SAMPLECLOCK_AUTO, enable,
		0);
पूर्ण

u16 hpi_sample_घड़ी_get_स्वतः(u32 h_control, u32 *penable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_AUTO,
		penable);
पूर्ण

u16 hpi_sample_घड़ी_set_local_rate_lock(u32 h_control, u32 lock)
अणु
	वापस hpi_control_param_set(h_control, HPI_SAMPLECLOCK_LOCAL_LOCK,
		lock, 0);
पूर्ण

u16 hpi_sample_घड़ी_get_local_rate_lock(u32 h_control, u32 *plock)
अणु
	वापस hpi_control_param1_get(h_control, HPI_SAMPLECLOCK_LOCAL_LOCK,
		plock);
पूर्ण

u16 hpi_tone_detector_get_frequency(u32 h_control, u32 index, u32 *frequency)
अणु
	वापस hpi_control_param_get(h_control, HPI_TONEDETECTOR_FREQUENCY,
		index, 0, frequency, शून्य);
पूर्ण

u16 hpi_tone_detector_get_state(u32 h_control, u32 *state)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TONEDETECTOR_STATE,
		state);
पूर्ण

u16 hpi_tone_detector_set_enable(u32 h_control, u32 enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_GENERIC_ENABLE, enable,
		0);
पूर्ण

u16 hpi_tone_detector_get_enable(u32 h_control, u32 *enable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_GENERIC_ENABLE, enable);
पूर्ण

u16 hpi_tone_detector_set_event_enable(u32 h_control, u32 event_enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_GENERIC_EVENT_ENABLE,
		(u32)event_enable, 0);
पूर्ण

u16 hpi_tone_detector_get_event_enable(u32 h_control, u32 *event_enable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_GENERIC_EVENT_ENABLE,
		event_enable);
पूर्ण

u16 hpi_tone_detector_set_threshold(u32 h_control, पूर्णांक threshold)
अणु
	वापस hpi_control_param_set(h_control, HPI_TONEDETECTOR_THRESHOLD,
		(u32)threshold, 0);
पूर्ण

u16 hpi_tone_detector_get_threshold(u32 h_control, पूर्णांक *threshold)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TONEDETECTOR_THRESHOLD,
		(u32 *)threshold);
पूर्ण

u16 hpi_silence_detector_get_state(u32 h_control, u32 *state)
अणु
	वापस hpi_control_param1_get(h_control, HPI_SILENCEDETECTOR_STATE,
		state);
पूर्ण

u16 hpi_silence_detector_set_enable(u32 h_control, u32 enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_GENERIC_ENABLE, enable,
		0);
पूर्ण

u16 hpi_silence_detector_get_enable(u32 h_control, u32 *enable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_GENERIC_ENABLE, enable);
पूर्ण

u16 hpi_silence_detector_set_event_enable(u32 h_control, u32 event_enable)
अणु
	वापस hpi_control_param_set(h_control, HPI_GENERIC_EVENT_ENABLE,
		event_enable, 0);
पूर्ण

u16 hpi_silence_detector_get_event_enable(u32 h_control, u32 *event_enable)
अणु
	वापस hpi_control_param1_get(h_control, HPI_GENERIC_EVENT_ENABLE,
		event_enable);
पूर्ण

u16 hpi_silence_detector_set_delay(u32 h_control, u32 delay)
अणु
	वापस hpi_control_param_set(h_control, HPI_SILENCEDETECTOR_DELAY,
		delay, 0);
पूर्ण

u16 hpi_silence_detector_get_delay(u32 h_control, u32 *delay)
अणु
	वापस hpi_control_param1_get(h_control, HPI_SILENCEDETECTOR_DELAY,
		delay);
पूर्ण

u16 hpi_silence_detector_set_threshold(u32 h_control, पूर्णांक threshold)
अणु
	वापस hpi_control_param_set(h_control, HPI_SILENCEDETECTOR_THRESHOLD,
		threshold, 0);
पूर्ण

u16 hpi_silence_detector_get_threshold(u32 h_control, पूर्णांक *threshold)
अणु
	वापस hpi_control_param1_get(h_control,
		HPI_SILENCEDETECTOR_THRESHOLD, (u32 *)threshold);
पूर्ण

u16 hpi_tuner_query_band(स्थिर u32 h_tuner, स्थिर u32 index, u16 *pw_band)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_tuner, HPI_TUNER_BAND, index, 0, &qr);
	*pw_band = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_tuner_set_band(u32 h_control, u16 band)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_BAND, band, 0);
पूर्ण

u16 hpi_tuner_get_band(u32 h_control, u16 *pw_band)
अणु
	u32 band = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_BAND, &band);
	अगर (pw_band)
		*pw_band = (u16)band;
	वापस error;
पूर्ण

u16 hpi_tuner_query_frequency(स्थिर u32 h_tuner, स्थिर u32 index,
	स्थिर u16 band, u32 *pfreq)
अणु
	वापस hpi_control_query(h_tuner, HPI_TUNER_FREQ, index, band, pfreq);
पूर्ण

u16 hpi_tuner_set_frequency(u32 h_control, u32 freq_ink_hz)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_FREQ, freq_ink_hz,
		0);
पूर्ण

u16 hpi_tuner_get_frequency(u32 h_control, u32 *pw_freq_ink_hz)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TUNER_FREQ,
		pw_freq_ink_hz);
पूर्ण

u16 hpi_tuner_query_gain(स्थिर u32 h_tuner, स्थिर u32 index, u16 *pw_gain)
अणु
	u32 qr;
	u16 err;

	err = hpi_control_query(h_tuner, HPI_TUNER_BAND, index, 0, &qr);
	*pw_gain = (u16)qr;
	वापस err;
पूर्ण

u16 hpi_tuner_set_gain(u32 h_control, लघु gain)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_GAIN, gain, 0);
पूर्ण

u16 hpi_tuner_get_gain(u32 h_control, लघु *pn_gain)
अणु
	u32 gain = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_GAIN, &gain);
	अगर (pn_gain)
		*pn_gain = (u16)gain;
	वापस error;
पूर्ण

u16 hpi_tuner_get_rf_level(u32 h_control, लघु *pw_level)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.cu.attribute = HPI_TUNER_LEVEL_AVG;
	hpi_send_recv(&hm, &hr);
	अगर (pw_level)
		*pw_level = hr.u.cu.tuner.s_level;
	वापस hr.error;
पूर्ण

u16 hpi_tuner_get_raw_rf_level(u32 h_control, लघु *pw_level)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.cu.attribute = HPI_TUNER_LEVEL_RAW;
	hpi_send_recv(&hm, &hr);
	अगर (pw_level)
		*pw_level = hr.u.cu.tuner.s_level;
	वापस hr.error;
पूर्ण

u16 hpi_tuner_query_deemphasis(स्थिर u32 h_tuner, स्थिर u32 index,
	स्थिर u16 band, u32 *pdeemphasis)
अणु
	वापस hpi_control_query(h_tuner, HPI_TUNER_DEEMPHASIS, index, band,
		pdeemphasis);
पूर्ण

u16 hpi_tuner_set_deemphasis(u32 h_control, u32 deemphasis)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_DEEMPHASIS,
		deemphasis, 0);
पूर्ण

u16 hpi_tuner_get_deemphasis(u32 h_control, u32 *pdeemphasis)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TUNER_DEEMPHASIS,
		pdeemphasis);
पूर्ण

u16 hpi_tuner_query_program(स्थिर u32 h_tuner, u32 *pbiपंचांगap_program)
अणु
	वापस hpi_control_query(h_tuner, HPI_TUNER_PROGRAM, 0, 0,
		pbiपंचांगap_program);
पूर्ण

u16 hpi_tuner_set_program(u32 h_control, u32 program)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_PROGRAM, program,
		0);
पूर्ण

u16 hpi_tuner_get_program(u32 h_control, u32 *pprogram)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TUNER_PROGRAM, pprogram);
पूर्ण

u16 hpi_tuner_get_hd_radio_dsp_version(u32 h_control, अक्षर *psz_dsp_version,
	स्थिर u32 string_size)
अणु
	वापस hpi_control_get_string(h_control,
		HPI_TUNER_HDRADIO_DSP_VERSION, psz_dsp_version, string_size);
पूर्ण

u16 hpi_tuner_get_hd_radio_sdk_version(u32 h_control, अक्षर *psz_sdk_version,
	स्थिर u32 string_size)
अणु
	वापस hpi_control_get_string(h_control,
		HPI_TUNER_HDRADIO_SDK_VERSION, psz_sdk_version, string_size);
पूर्ण

u16 hpi_tuner_get_status(u32 h_control, u16 *pw_status_mask, u16 *pw_status)
अणु
	u32 status = 0;
	u16 error = 0;

	error = hpi_control_param1_get(h_control, HPI_TUNER_STATUS, &status);
	अगर (pw_status) अणु
		अगर (!error) अणु
			*pw_status_mask = (u16)(status >> 16);
			*pw_status = (u16)(status & 0xFFFF);
		पूर्ण अन्यथा अणु
			*pw_status_mask = 0;
			*pw_status = 0;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

u16 hpi_tuner_set_mode(u32 h_control, u32 mode, u32 value)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_MODE, mode, value);
पूर्ण

u16 hpi_tuner_get_mode(u32 h_control, u32 mode, u32 *pn_value)
अणु
	वापस hpi_control_param_get(h_control, HPI_TUNER_MODE, mode, 0,
		pn_value, शून्य);
पूर्ण

u16 hpi_tuner_get_hd_radio_संकेत_quality(u32 h_control, u32 *pquality)
अणु
	वापस hpi_control_param1_get(h_control,
		HPI_TUNER_HDRADIO_SIGNAL_QUALITY, pquality);
पूर्ण

u16 hpi_tuner_get_hd_radio_संकेत_blend(u32 h_control, u32 *pblend)
अणु
	वापस hpi_control_param1_get(h_control, HPI_TUNER_HDRADIO_BLEND,
		pblend);
पूर्ण

u16 hpi_tuner_set_hd_radio_संकेत_blend(u32 h_control, स्थिर u32 blend)
अणु
	वापस hpi_control_param_set(h_control, HPI_TUNER_HDRADIO_BLEND,
		blend, 0);
पूर्ण

u16 hpi_tuner_get_rds(u32 h_control, अक्षर *p_data)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_TUNER_RDS;
	hpi_send_recv(&hm, &hr);
	अगर (p_data) अणु
		*(u32 *)&p_data[0] = hr.u.cu.tuner.rds.data[0];
		*(u32 *)&p_data[4] = hr.u.cu.tuner.rds.data[1];
		*(u32 *)&p_data[8] = hr.u.cu.tuner.rds.bLER;
	पूर्ण
	वापस hr.error;
पूर्ण

u16 hpi_pad_get_channel_name(u32 h_control, अक्षर *psz_string,
	स्थिर u32 data_length)
अणु
	वापस hpi_control_get_string(h_control, HPI_PAD_CHANNEL_NAME,
		psz_string, data_length);
पूर्ण

u16 hpi_pad_get_artist(u32 h_control, अक्षर *psz_string, स्थिर u32 data_length)
अणु
	वापस hpi_control_get_string(h_control, HPI_PAD_ARTIST, psz_string,
		data_length);
पूर्ण

u16 hpi_pad_get_title(u32 h_control, अक्षर *psz_string, स्थिर u32 data_length)
अणु
	वापस hpi_control_get_string(h_control, HPI_PAD_TITLE, psz_string,
		data_length);
पूर्ण

u16 hpi_pad_get_comment(u32 h_control, अक्षर *psz_string,
	स्थिर u32 data_length)
अणु
	वापस hpi_control_get_string(h_control, HPI_PAD_COMMENT, psz_string,
		data_length);
पूर्ण

u16 hpi_pad_get_program_type(u32 h_control, u32 *ppTY)
अणु
	वापस hpi_control_param1_get(h_control, HPI_PAD_PROGRAM_TYPE, ppTY);
पूर्ण

u16 hpi_pad_get_rdsPI(u32 h_control, u32 *ppI)
अणु
	वापस hpi_control_param1_get(h_control, HPI_PAD_PROGRAM_ID, ppI);
पूर्ण

u16 hpi_volume_query_channels(स्थिर u32 h_volume, u32 *p_channels)
अणु
	वापस hpi_control_query(h_volume, HPI_VOLUME_NUM_CHANNELS, 0, 0,
		p_channels);
पूर्ण

u16 hpi_volume_set_gain(u32 h_control, लघु an_log_gain[HPI_MAX_CHANNELS]
	)
अणु
	वापस hpi_control_log_set2(h_control, HPI_VOLUME_GAIN,
		an_log_gain[0], an_log_gain[1]);
पूर्ण

u16 hpi_volume_get_gain(u32 h_control, लघु an_log_gain[HPI_MAX_CHANNELS]
	)
अणु
	वापस hpi_control_log_get2(h_control, HPI_VOLUME_GAIN,
		&an_log_gain[0], &an_log_gain[1]);
पूर्ण

u16 hpi_volume_set_mute(u32 h_control, u32 mute)
अणु
	वापस hpi_control_param_set(h_control, HPI_VOLUME_MUTE, mute, 0);
पूर्ण

u16 hpi_volume_get_mute(u32 h_control, u32 *mute)
अणु
	वापस hpi_control_param1_get(h_control, HPI_VOLUME_MUTE, mute);
पूर्ण

u16 hpi_volume_query_range(u32 h_control, लघु *min_gain_01dB,
	लघु *max_gain_01dB, लघु *step_gain_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_VOLUME_RANGE;

	hpi_send_recv(&hm, &hr);
	अगर (hr.error) अणु
		hr.u.c.an_log_value[0] = 0;
		hr.u.c.an_log_value[1] = 0;
		hr.u.c.param1 = 0;
	पूर्ण
	अगर (min_gain_01dB)
		*min_gain_01dB = hr.u.c.an_log_value[0];
	अगर (max_gain_01dB)
		*max_gain_01dB = hr.u.c.an_log_value[1];
	अगर (step_gain_01dB)
		*step_gain_01dB = (लघु)hr.u.c.param1;
	वापस hr.error;
पूर्ण

u16 hpi_volume_स्वतः_fade_profile(u32 h_control,
	लघु an_stop_gain0_01dB[HPI_MAX_CHANNELS], u32 duration_ms,
	u16 profile)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;

	स_नकल(hm.u.c.an_log_value, an_stop_gain0_01dB,
		माप(लघु) * HPI_MAX_CHANNELS);

	hm.u.c.attribute = HPI_VOLUME_AUTOFADE;
	hm.u.c.param1 = duration_ms;
	hm.u.c.param2 = profile;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_volume_स्वतः_fade(u32 h_control,
	लघु an_stop_gain0_01dB[HPI_MAX_CHANNELS], u32 duration_ms)
अणु
	वापस hpi_volume_स्वतः_fade_profile(h_control, an_stop_gain0_01dB,
		duration_ms, HPI_VOLUME_AUTOFADE_LOG);
पूर्ण

u16 hpi_volume_query_स्वतः_fade_profile(स्थिर u32 h_volume, स्थिर u32 i,
	u16 *profile)
अणु
	u16 e;
	u32 u;
	e = hpi_control_query(h_volume, HPI_VOLUME_AUTOFADE, i, 0, &u);
	*profile = (u16)u;
	वापस e;
पूर्ण

u16 hpi_vox_set_threshold(u32 h_control, लघु an_gain0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_SET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_VOX_THRESHOLD;

	hm.u.c.an_log_value[0] = an_gain0_01dB;

	hpi_send_recv(&hm, &hr);

	वापस hr.error;
पूर्ण

u16 hpi_vox_get_threshold(u32 h_control, लघु *an_gain0_01dB)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;
	hpi_init_message_response(&hm, &hr, HPI_OBJ_CONTROL,
		HPI_CONTROL_GET_STATE);
	अगर (hpi_handle_indexes(h_control, &hm.adapter_index, &hm.obj_index))
		वापस HPI_ERROR_INVALID_HANDLE;
	hm.u.c.attribute = HPI_VOX_THRESHOLD;

	hpi_send_recv(&hm, &hr);

	*an_gain0_01dB = hr.u.c.an_log_value[0];

	वापस hr.error;
पूर्ण
