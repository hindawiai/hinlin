<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


\पile hpicmn.c

 Common functions used by hpixxxx.c modules

(C) Copyright AudioScience Inc. 1998-2003
*******************************************************************************/
#घोषणा SOURCEखाता_NAME "hpicmn.c"

#समावेश "hpi_internal.h"
#समावेश "hpidebug.h"
#समावेश "hpimsginit.h"

#समावेश "hpicmn.h"

काष्ठा hpi_adapters_list अणु
	काष्ठा hpios_spinlock list_lock;
	काष्ठा hpi_adapter_obj adapter[HPI_MAX_ADAPTERS];
	u16 gw_num_adapters;
पूर्ण;

अटल काष्ठा hpi_adapters_list adapters;

/**
 * hpi_validate_response - Given an HPI Message that was sent out and
 * a response that was received, validate that the response has the
 * correct fields filled in, i.e ObjectType, Function etc
 * @phm: message
 * @phr: response
 */
u16 hpi_validate_response(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	अगर (phr->type != HPI_TYPE_RESPONSE) अणु
		HPI_DEBUG_LOG(ERROR, "header type %d invalid\n", phr->type);
		वापस HPI_ERROR_INVALID_RESPONSE;
	पूर्ण

	अगर (phr->object != phm->object) अणु
		HPI_DEBUG_LOG(ERROR, "header object %d invalid\n",
			phr->object);
		वापस HPI_ERROR_INVALID_RESPONSE;
	पूर्ण

	अगर (phr->function != phm->function) अणु
		HPI_DEBUG_LOG(ERROR, "header function %d invalid\n",
			phr->function);
		वापस HPI_ERROR_INVALID_RESPONSE;
	पूर्ण

	वापस 0;
पूर्ण

u16 hpi_add_adapter(काष्ठा hpi_adapter_obj *pao)
अणु
	u16 retval = 0;
	/*HPI_ASSERT(pao->type); */

	hpios_alistlock_lock(&adapters);

	अगर (pao->index >= HPI_MAX_ADAPTERS) अणु
		retval = HPI_ERROR_BAD_ADAPTER_NUMBER;
		जाओ unlock;
	पूर्ण

	अगर (adapters.adapter[pao->index].type) अणु
		पूर्णांक a;
		क्रम (a = HPI_MAX_ADAPTERS - 1; a >= 0; a--) अणु
			अगर (!adapters.adapter[a].type) अणु
				HPI_DEBUG_LOG(WARNING,
					"ASI%X duplicate index %d moved to %d\n",
					pao->type, pao->index, a);
				pao->index = a;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (a < 0) अणु
			retval = HPI_ERROR_DUPLICATE_ADAPTER_NUMBER;
			जाओ unlock;
		पूर्ण
	पूर्ण
	adapters.adapter[pao->index] = *pao;
	hpios_dsplock_init(&adapters.adapter[pao->index]);
	adapters.gw_num_adapters++;

unlock:
	hpios_alistlock_unlock(&adapters);
	वापस retval;
पूर्ण

व्योम hpi_delete_adapter(काष्ठा hpi_adapter_obj *pao)
अणु
	अगर (!pao->type) अणु
		HPI_DEBUG_LOG(ERROR, "removing null adapter?\n");
		वापस;
	पूर्ण

	hpios_alistlock_lock(&adapters);
	अगर (adapters.adapter[pao->index].type)
		adapters.gw_num_adapters--;
	स_रखो(&adapters.adapter[pao->index], 0, माप(adapters.adapter[0]));
	hpios_alistlock_unlock(&adapters);
पूर्ण

/**
 * hpi_find_adapter - FindAdapter वापसs a poपूर्णांकer to the काष्ठा
 * hpi_adapter_obj with index wAdapterIndex in an HPI_ADAPTERS_LIST
 * काष्ठाure.
 * @adapter_index: value in [0, HPI_MAX_ADAPTERS[
 */
काष्ठा hpi_adapter_obj *hpi_find_adapter(u16 adapter_index)
अणु
	काष्ठा hpi_adapter_obj *pao = शून्य;

	अगर (adapter_index >= HPI_MAX_ADAPTERS) अणु
		HPI_DEBUG_LOG(VERBOSE, "find_adapter invalid index %d\n",
			adapter_index);
		वापस शून्य;
	पूर्ण

	pao = &adapters.adapter[adapter_index];
	अगर (pao->type != 0) अणु
		/*
		   HPI_DEBUG_LOG(VERBOSE, "Found adapter index %d\n",
		   wAdapterIndex);
		 */
		वापस pao;
	पूर्ण अन्यथा अणु
		/*
		   HPI_DEBUG_LOG(VERBOSE, "No adapter index %d\n",
		   wAdapterIndex);
		 */
		वापस शून्य;
	पूर्ण
पूर्ण

/**
 * wipe_adapter_list - wipe an HPI_ADAPTERS_LIST काष्ठाure.
 *
 */
अटल व्योम wipe_adapter_list(व्योम)
अणु
	स_रखो(&adapters, 0, माप(adapters));
पूर्ण

अटल व्योम subsys_get_adapter(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	पूर्णांक count = phm->obj_index;
	u16 index = 0;

	/* find the nCount'th nonzero adapter in array */
	क्रम (index = 0; index < HPI_MAX_ADAPTERS; index++) अणु
		अगर (adapters.adapter[index].type) अणु
			अगर (!count)
				अवरोध;
			count--;
		पूर्ण
	पूर्ण

	अगर (index < HPI_MAX_ADAPTERS) अणु
		phr->u.s.adapter_index = adapters.adapter[index].index;
		phr->u.s.adapter_type = adapters.adapter[index].type;
	पूर्ण अन्यथा अणु
		phr->u.s.adapter_index = 0;
		phr->u.s.adapter_type = 0;
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक control_cache_alloc_check(काष्ठा hpi_control_cache *pC)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक cached = 0;
	अगर (!pC)
		वापस 0;

	अगर (pC->init)
		वापस pC->init;

	अगर (!pC->p_cache)
		वापस 0;

	अगर (pC->control_count && pC->cache_size_in_bytes) अणु
		अक्षर *p_master_cache;
		अचिन्हित पूर्णांक byte_count = 0;

		p_master_cache = (अक्षर *)pC->p_cache;
		HPI_DEBUG_LOG(DEBUG, "check %d controls\n",
			pC->control_count);
		क्रम (i = 0; i < pC->control_count; i++) अणु
			काष्ठा hpi_control_cache_info *info =
				(काष्ठा hpi_control_cache_info *)
				&p_master_cache[byte_count];
			u16 control_index = info->control_index;

			अगर (control_index >= pC->control_count) अणु
				HPI_DEBUG_LOG(INFO,
					"adap %d control index %d out of range, cache not ready?\n",
					pC->adap_idx, control_index);
				वापस 0;
			पूर्ण

			अगर (!info->size_in32bit_words) अणु
				अगर (!i) अणु
					HPI_DEBUG_LOG(INFO,
						"adap %d cache not ready?\n",
						pC->adap_idx);
					वापस 0;
				पूर्ण
				/* The cache is invalid.
				 * Minimum valid entry size is
				 * माप(काष्ठा hpi_control_cache_info)
				 */
				HPI_DEBUG_LOG(ERROR,
					"adap %d zero size cache entry %d\n",
					pC->adap_idx, i);
				अवरोध;
			पूर्ण

			अगर (info->control_type) अणु
				pC->p_info[control_index] = info;
				cached++;
			पूर्ण अन्यथा अणु	/* dummy cache entry */
				pC->p_info[control_index] = शून्य;
			पूर्ण

			byte_count += info->size_in32bit_words * 4;

			HPI_DEBUG_LOG(VERBOSE,
				"cached %d, pinfo %p index %d type %d size %d\n",
				cached, pC->p_info[info->control_index],
				info->control_index, info->control_type,
				info->size_in32bit_words);

			/* quit loop early अगर whole cache has been scanned.
			 * dwControlCount is the maximum possible entries
			 * but some may be असलent from the cache
			 */
			अगर (byte_count >= pC->cache_size_in_bytes)
				अवरोध;
			/* have seen last control index */
			अगर (info->control_index == pC->control_count - 1)
				अवरोध;
		पूर्ण

		अगर (byte_count != pC->cache_size_in_bytes)
			HPI_DEBUG_LOG(WARNING,
				"adap %d bytecount %d != cache size %d\n",
				pC->adap_idx, byte_count,
				pC->cache_size_in_bytes);
		अन्यथा
			HPI_DEBUG_LOG(DEBUG,
				"adap %d cache good, bytecount == cache size = %d\n",
				pC->adap_idx, byte_count);

		pC->init = (u16)cached;
	पूर्ण
	वापस pC->init;
पूर्ण

/** Find a control.
*/
अटल लघु find_control(u16 control_index,
	काष्ठा hpi_control_cache *p_cache, काष्ठा hpi_control_cache_info **pI)
अणु
	अगर (!control_cache_alloc_check(p_cache)) अणु
		HPI_DEBUG_LOG(VERBOSE,
			"control_cache_alloc_check() failed %d\n",
			control_index);
		वापस 0;
	पूर्ण

	*pI = p_cache->p_info[control_index];
	अगर (!*pI) अणु
		HPI_DEBUG_LOG(VERBOSE, "Uncached Control %d\n",
			control_index);
		वापस 0;
	पूर्ण अन्यथा अणु
		HPI_DEBUG_LOG(VERBOSE, "find_control() type %d\n",
			(*pI)->control_type);
	पूर्ण
	वापस 1;
पूर्ण

/* allow unअगरied treaपंचांगent of several string fields within काष्ठा */
#घोषणा HPICMN_PAD_OFS_AND_SIZE(m)  अणु\
	दुरत्व(काष्ठा hpi_control_cache_pad, m), \
	माप(((काष्ठा hpi_control_cache_pad *)(शून्य))->m) पूर्ण

काष्ठा pad_ofs_size अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक field_size;
पूर्ण;

अटल स्थिर काष्ठा pad_ofs_size pad_desc[] = अणु
	HPICMN_PAD_OFS_AND_SIZE(c_channel),	/* HPI_PAD_CHANNEL_NAME */
	HPICMN_PAD_OFS_AND_SIZE(c_artist),	/* HPI_PAD_ARTIST */
	HPICMN_PAD_OFS_AND_SIZE(c_title),	/* HPI_PAD_TITLE */
	HPICMN_PAD_OFS_AND_SIZE(c_comment),	/* HPI_PAD_COMMENT */
पूर्ण;

/** CheckControlCache checks the cache and fills the काष्ठा hpi_response
 * accordingly. It वापसs one अगर a cache hit occurred, zero otherwise.
 */
लघु hpi_check_control_cache_single(काष्ठा hpi_control_cache_single *pC,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	माप_प्रकार response_size;
	लघु found = 1;

	/* set the शेष response size */
	response_size =
		माप(काष्ठा hpi_response_header) +
		माप(काष्ठा hpi_control_res);

	चयन (pC->u.i.control_type) अणु

	हाल HPI_CONTROL_METER:
		अगर (phm->u.c.attribute == HPI_METER_PEAK) अणु
			phr->u.c.an_log_value[0] = pC->u.meter.an_log_peak[0];
			phr->u.c.an_log_value[1] = pC->u.meter.an_log_peak[1];
		पूर्ण अन्यथा अगर (phm->u.c.attribute == HPI_METER_RMS) अणु
			अगर (pC->u.meter.an_logRMS[0] ==
				HPI_CACHE_INVALID_SHORT) अणु
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				phr->u.c.an_log_value[0] = HPI_METER_MINIMUM;
				phr->u.c.an_log_value[1] = HPI_METER_MINIMUM;
			पूर्ण अन्यथा अणु
				phr->u.c.an_log_value[0] =
					pC->u.meter.an_logRMS[0];
				phr->u.c.an_log_value[1] =
					pC->u.meter.an_logRMS[1];
			पूर्ण
		पूर्ण अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_VOLUME:
		अगर (phm->u.c.attribute == HPI_VOLUME_GAIN) अणु
			phr->u.c.an_log_value[0] = pC->u.vol.an_log[0];
			phr->u.c.an_log_value[1] = pC->u.vol.an_log[1];
		पूर्ण अन्यथा अगर (phm->u.c.attribute == HPI_VOLUME_MUTE) अणु
			अगर (pC->u.vol.flags & HPI_VOLUME_FLAG_HAS_MUTE) अणु
				अगर (pC->u.vol.flags & HPI_VOLUME_FLAG_MUTED)
					phr->u.c.param1 =
						HPI_BITMASK_ALL_CHANNELS;
				अन्यथा
					phr->u.c.param1 = 0;
			पूर्ण अन्यथा अणु
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				phr->u.c.param1 = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			found = 0;
		पूर्ण
		अवरोध;
	हाल HPI_CONTROL_MULTIPLEXER:
		अगर (phm->u.c.attribute == HPI_MULTIPLEXER_SOURCE) अणु
			phr->u.c.param1 = pC->u.mux.source_node_type;
			phr->u.c.param2 = pC->u.mux.source_node_index;
		पूर्ण अन्यथा अणु
			found = 0;
		पूर्ण
		अवरोध;
	हाल HPI_CONTROL_CHANNEL_MODE:
		अगर (phm->u.c.attribute == HPI_CHANNEL_MODE_MODE)
			phr->u.c.param1 = pC->u.mode.mode;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_LEVEL:
		अगर (phm->u.c.attribute == HPI_LEVEL_GAIN) अणु
			phr->u.c.an_log_value[0] = pC->u.level.an_log[0];
			phr->u.c.an_log_value[1] = pC->u.level.an_log[1];
		पूर्ण अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_TUNER:
		अगर (phm->u.c.attribute == HPI_TUNER_FREQ)
			phr->u.c.param1 = pC->u.tuner.freq_ink_hz;
		अन्यथा अगर (phm->u.c.attribute == HPI_TUNER_BAND)
			phr->u.c.param1 = pC->u.tuner.band;
		अन्यथा अगर (phm->u.c.attribute == HPI_TUNER_LEVEL_AVG)
			अगर (pC->u.tuner.s_level_avg ==
				HPI_CACHE_INVALID_SHORT) अणु
				phr->u.cu.tuner.s_level = 0;
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
			पूर्ण अन्यथा
				phr->u.cu.tuner.s_level =
					pC->u.tuner.s_level_avg;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_AESEBU_RECEIVER:
		अगर (phm->u.c.attribute == HPI_AESEBURX_ERRORSTATUS)
			phr->u.c.param1 = pC->u.aes3rx.error_status;
		अन्यथा अगर (phm->u.c.attribute == HPI_AESEBURX_FORMAT)
			phr->u.c.param1 = pC->u.aes3rx.क्रमmat;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_AESEBU_TRANSMITTER:
		अगर (phm->u.c.attribute == HPI_AESEBUTX_FORMAT)
			phr->u.c.param1 = pC->u.aes3tx.क्रमmat;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_TONEDETECTOR:
		अगर (phm->u.c.attribute == HPI_TONEDETECTOR_STATE)
			phr->u.c.param1 = pC->u.tone.state;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_SILENCEDETECTOR:
		अगर (phm->u.c.attribute == HPI_SILENCEDETECTOR_STATE) अणु
			phr->u.c.param1 = pC->u.silence.state;
		पूर्ण अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_MICROPHONE:
		अगर (phm->u.c.attribute == HPI_MICROPHONE_PHANTOM_POWER)
			phr->u.c.param1 = pC->u.microphone.phantom_state;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_SAMPLECLOCK:
		अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE)
			phr->u.c.param1 = pC->u.clk.source;
		अन्यथा अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE_INDEX) अणु
			अगर (pC->u.clk.source_index ==
				HPI_CACHE_INVALID_UINT16) अणु
				phr->u.c.param1 = 0;
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
			पूर्ण अन्यथा
				phr->u.c.param1 = pC->u.clk.source_index;
		पूर्ण अन्यथा अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SAMPLERATE)
			phr->u.c.param1 = pC->u.clk.sample_rate;
		अन्यथा
			found = 0;
		अवरोध;
	हाल HPI_CONTROL_PAD:अणु
			काष्ठा hpi_control_cache_pad *p_pad;
			p_pad = (काष्ठा hpi_control_cache_pad *)pC;

			अगर (!(p_pad->field_valid_flags & (1 <<
						HPI_CTL_ATTR_INDEX(phm->u.c.
							attribute)))) अणु
				phr->error =
					HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
				अवरोध;
			पूर्ण

			अगर (phm->u.c.attribute == HPI_PAD_PROGRAM_ID)
				phr->u.c.param1 = p_pad->pI;
			अन्यथा अगर (phm->u.c.attribute == HPI_PAD_PROGRAM_TYPE)
				phr->u.c.param1 = p_pad->pTY;
			अन्यथा अणु
				अचिन्हित पूर्णांक index =
					HPI_CTL_ATTR_INDEX(phm->u.c.
					attribute) - 1;
				अचिन्हित पूर्णांक offset = phm->u.c.param1;
				अचिन्हित पूर्णांक pad_string_len, field_size;
				अक्षर *pad_string;
				अचिन्हित पूर्णांक tocopy;

				अगर (index > ARRAY_SIZE(pad_desc) - 1) अणु
					phr->error =
						HPI_ERROR_INVALID_CONTROL_ATTRIBUTE;
					अवरोध;
				पूर्ण

				pad_string =
					((अक्षर *)p_pad) +
					pad_desc[index].offset;
				field_size = pad_desc[index].field_size;
				/* Ensure null terminator */
				pad_string[field_size - 1] = 0;

				pad_string_len = म_माप(pad_string) + 1;

				अगर (offset > pad_string_len) अणु
					phr->error =
						HPI_ERROR_INVALID_CONTROL_VALUE;
					अवरोध;
				पूर्ण

				tocopy = pad_string_len - offset;
				अगर (tocopy > माप(phr->u.cu.अक्षरs8.sz_data))
					tocopy = माप(phr->u.cu.अक्षरs8.
						sz_data);

				स_नकल(phr->u.cu.अक्षरs8.sz_data,
					&pad_string[offset], tocopy);

				phr->u.cu.अक्षरs8.reमुख्यing_अक्षरs =
					pad_string_len - offset - tocopy;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		found = 0;
		अवरोध;
	पूर्ण

	HPI_DEBUG_LOG(VERBOSE, "%s Adap %d, Ctl %d, Type %d, Attr %d\n",
		found ? "Cached" : "Uncached", phm->adapter_index,
		pC->u.i.control_index, pC->u.i.control_type,
		phm->u.c.attribute);

	अगर (found) अणु
		phr->size = (u16)response_size;
		phr->type = HPI_TYPE_RESPONSE;
		phr->object = phm->object;
		phr->function = phm->function;
	पूर्ण

	वापस found;
पूर्ण

लघु hpi_check_control_cache(काष्ठा hpi_control_cache *p_cache,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_control_cache_info *pI;

	अगर (!find_control(phm->obj_index, p_cache, &pI)) अणु
		HPI_DEBUG_LOG(VERBOSE,
			"HPICMN find_control() failed for adap %d\n",
			phm->adapter_index);
		वापस 0;
	पूर्ण

	phr->error = 0;
	phr->specअगरic_error = 0;
	phr->version = 0;

	वापस hpi_check_control_cache_single((काष्ठा hpi_control_cache_single
			*)pI, phm, phr);
पूर्ण

/** Updates the cache with Set values.

Only update अगर no error.
Volume and Level वापस the limited values in the response, so use these
Multiplexer करोes so use sent values
*/
व्योम hpi_cmn_control_cache_sync_to_msg_single(काष्ठा hpi_control_cache_single
	*pC, काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (pC->u.i.control_type) अणु
	हाल HPI_CONTROL_VOLUME:
		अगर (phm->u.c.attribute == HPI_VOLUME_GAIN) अणु
			pC->u.vol.an_log[0] = phr->u.c.an_log_value[0];
			pC->u.vol.an_log[1] = phr->u.c.an_log_value[1];
		पूर्ण अन्यथा अगर (phm->u.c.attribute == HPI_VOLUME_MUTE) अणु
			अगर (phm->u.c.param1)
				pC->u.vol.flags |= HPI_VOLUME_FLAG_MUTED;
			अन्यथा
				pC->u.vol.flags &= ~HPI_VOLUME_FLAG_MUTED;
		पूर्ण
		अवरोध;
	हाल HPI_CONTROL_MULTIPLEXER:
		/* mux करोes not वापस its setting on Set command. */
		अगर (phm->u.c.attribute == HPI_MULTIPLEXER_SOURCE) अणु
			pC->u.mux.source_node_type = (u16)phm->u.c.param1;
			pC->u.mux.source_node_index = (u16)phm->u.c.param2;
		पूर्ण
		अवरोध;
	हाल HPI_CONTROL_CHANNEL_MODE:
		/* mode करोes not वापस its setting on Set command. */
		अगर (phm->u.c.attribute == HPI_CHANNEL_MODE_MODE)
			pC->u.mode.mode = (u16)phm->u.c.param1;
		अवरोध;
	हाल HPI_CONTROL_LEVEL:
		अगर (phm->u.c.attribute == HPI_LEVEL_GAIN) अणु
			pC->u.vol.an_log[0] = phr->u.c.an_log_value[0];
			pC->u.vol.an_log[1] = phr->u.c.an_log_value[1];
		पूर्ण
		अवरोध;
	हाल HPI_CONTROL_MICROPHONE:
		अगर (phm->u.c.attribute == HPI_MICROPHONE_PHANTOM_POWER)
			pC->u.microphone.phantom_state = (u16)phm->u.c.param1;
		अवरोध;
	हाल HPI_CONTROL_AESEBU_TRANSMITTER:
		अगर (phm->u.c.attribute == HPI_AESEBUTX_FORMAT)
			pC->u.aes3tx.क्रमmat = phm->u.c.param1;
		अवरोध;
	हाल HPI_CONTROL_AESEBU_RECEIVER:
		अगर (phm->u.c.attribute == HPI_AESEBURX_FORMAT)
			pC->u.aes3rx.क्रमmat = phm->u.c.param1;
		अवरोध;
	हाल HPI_CONTROL_SAMPLECLOCK:
		अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE)
			pC->u.clk.source = (u16)phm->u.c.param1;
		अन्यथा अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SOURCE_INDEX)
			pC->u.clk.source_index = (u16)phm->u.c.param1;
		अन्यथा अगर (phm->u.c.attribute == HPI_SAMPLECLOCK_SAMPLERATE)
			pC->u.clk.sample_rate = phm->u.c.param1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम hpi_cmn_control_cache_sync_to_msg(काष्ठा hpi_control_cache *p_cache,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_control_cache_single *pC;
	काष्ठा hpi_control_cache_info *pI;

	अगर (phr->error)
		वापस;

	अगर (!find_control(phm->obj_index, p_cache, &pI)) अणु
		HPI_DEBUG_LOG(VERBOSE,
			"HPICMN find_control() failed for adap %d\n",
			phm->adapter_index);
		वापस;
	पूर्ण

	/* pC is the शेष cached control strucure.
	   May be cast to something अन्यथा in the following चयन statement.
	 */
	pC = (काष्ठा hpi_control_cache_single *)pI;

	hpi_cmn_control_cache_sync_to_msg_single(pC, phm, phr);
पूर्ण

/** Allocate control cache.

\लeturn Cache poपूर्णांकer, or शून्य अगर allocation fails.
*/
काष्ठा hpi_control_cache *hpi_alloc_control_cache(स्थिर u32 control_count,
	स्थिर u32 size_in_bytes, u8 *p_dsp_control_buffer)
अणु
	काष्ठा hpi_control_cache *p_cache =
		kदो_स्मृति(माप(*p_cache), GFP_KERNEL);
	अगर (!p_cache)
		वापस शून्य;

	p_cache->p_info =
		kसुस्मृति(control_count, माप(*p_cache->p_info), GFP_KERNEL);
	अगर (!p_cache->p_info) अणु
		kमुक्त(p_cache);
		वापस शून्य;
	पूर्ण

	p_cache->cache_size_in_bytes = size_in_bytes;
	p_cache->control_count = control_count;
	p_cache->p_cache = p_dsp_control_buffer;
	p_cache->init = 0;
	वापस p_cache;
पूर्ण

व्योम hpi_मुक्त_control_cache(काष्ठा hpi_control_cache *p_cache)
अणु
	अगर (p_cache) अणु
		kमुक्त(p_cache->p_info);
		kमुक्त(p_cache);
	पूर्ण
पूर्ण

अटल व्योम subsys_message(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	hpi_init_response(phr, HPI_OBJ_SUBSYSTEM, phm->function, 0);

	चयन (phm->function) अणु
	हाल HPI_SUBSYS_OPEN:
	हाल HPI_SUBSYS_CLOSE:
	हाल HPI_SUBSYS_DRIVER_UNLOAD:
		अवरोध;
	हाल HPI_SUBSYS_DRIVER_LOAD:
		wipe_adapter_list();
		hpios_alistlock_init(&adapters);
		अवरोध;
	हाल HPI_SUBSYS_GET_ADAPTER:
		subsys_get_adapter(phm, phr);
		अवरोध;
	हाल HPI_SUBSYS_GET_NUM_ADAPTERS:
		phr->u.s.num_adapters = adapters.gw_num_adapters;
		अवरोध;
	हाल HPI_SUBSYS_CREATE_ADAPTER:
		अवरोध;
	शेष:
		phr->error = HPI_ERROR_INVALID_FUNC;
		अवरोध;
	पूर्ण
पूर्ण

व्योम HPI_COMMON(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->type) अणु
	हाल HPI_TYPE_REQUEST:
		चयन (phm->object) अणु
		हाल HPI_OBJ_SUBSYSTEM:
			subsys_message(phm, phr);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		phr->error = HPI_ERROR_INVALID_TYPE;
		अवरोध;
	पूर्ण
पूर्ण
