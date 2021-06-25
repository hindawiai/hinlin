<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


Extended Message Function With Response Caching

(C) Copyright AudioScience Inc. 2002
*****************************************************************************/
#घोषणा SOURCEखाता_NAME "hpimsgx.c"
#समावेश "hpi_internal.h"
#समावेश "hpi_version.h"
#समावेश "hpimsginit.h"
#समावेश "hpicmn.h"
#समावेश "hpimsgx.h"
#समावेश "hpidebug.h"

अटल स्थिर काष्ठा pci_device_id asihpi_pci_tbl[] = अणु
#समावेश "hpipcida.h"
पूर्ण;

अटल काष्ठा hpios_spinlock msgx_lock;

अटल hpi_handler_func *hpi_entry_poपूर्णांकs[HPI_MAX_ADAPTERS];
अटल पूर्णांक logging_enabled = 1;

अटल hpi_handler_func *hpi_lookup_entry_poपूर्णांक_function(स्थिर काष्ठा hpi_pci
	*pci_info)
अणु

	पूर्णांक i;

	क्रम (i = 0; asihpi_pci_tbl[i].venकरोr != 0; i++) अणु
		अगर (asihpi_pci_tbl[i].venकरोr != PCI_ANY_ID
			&& asihpi_pci_tbl[i].venकरोr !=
			pci_info->pci_dev->venकरोr)
			जारी;
		अगर (asihpi_pci_tbl[i].device != PCI_ANY_ID
			&& asihpi_pci_tbl[i].device !=
			pci_info->pci_dev->device)
			जारी;
		अगर (asihpi_pci_tbl[i].subvenकरोr != PCI_ANY_ID
			&& asihpi_pci_tbl[i].subvenकरोr !=
			pci_info->pci_dev->subप्रणाली_venकरोr)
			जारी;
		अगर (asihpi_pci_tbl[i].subdevice != PCI_ANY_ID
			&& asihpi_pci_tbl[i].subdevice !=
			pci_info->pci_dev->subप्रणाली_device)
			जारी;

		/* HPI_DEBUG_LOG(DEBUG, " %x,%lx\n", i,
		   asihpi_pci_tbl[i].driver_data); */
		वापस (hpi_handler_func *) asihpi_pci_tbl[i].driver_data;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम hw_entry_poपूर्णांक(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	अगर ((phm->adapter_index < HPI_MAX_ADAPTERS)
		&& hpi_entry_poपूर्णांकs[phm->adapter_index])
		hpi_entry_poपूर्णांकs[phm->adapter_index] (phm, phr);
	अन्यथा
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_PROCESSING_MESSAGE);
पूर्ण

अटल व्योम adapter_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);
अटल व्योम adapter_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम mixer_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);
अटल व्योम mixer_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner);
अटल व्योम outstream_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner);
अटल व्योम instream_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner);
अटल व्योम instream_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner);

अटल व्योम HPIMSGX__reset(u16 adapter_index);

अटल u16 HPIMSGX__init(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);
अटल व्योम HPIMSGX__cleanup(u16 adapter_index, व्योम *h_owner);

#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(push, 1)
#पूर्ण_अगर

काष्ठा hpi_subsys_response अणु
	काष्ठा hpi_response_header h;
	काष्ठा hpi_subsys_res s;
पूर्ण;

काष्ठा hpi_adapter_response अणु
	काष्ठा hpi_response_header h;
	काष्ठा hpi_adapter_res a;
पूर्ण;

काष्ठा hpi_mixer_response अणु
	काष्ठा hpi_response_header h;
	काष्ठा hpi_mixer_res m;
पूर्ण;

काष्ठा hpi_stream_response अणु
	काष्ठा hpi_response_header h;
	काष्ठा hpi_stream_res d;
पूर्ण;

काष्ठा adapter_info अणु
	u16 type;
	u16 num_instreams;
	u16 num_outstreams;
पूर्ण;

काष्ठा asi_खोलो_state अणु
	पूर्णांक खोलो_flag;
	व्योम *h_owner;
पूर्ण;

#अगर_अघोषित DISABLE_PRAGMA_PACK1
#आशय pack(pop)
#पूर्ण_अगर

/* Globals */
अटल काष्ठा hpi_adapter_response rESP_HPI_ADAPTER_OPEN[HPI_MAX_ADAPTERS];

अटल काष्ठा hpi_stream_response
	rESP_HPI_OSTREAM_OPEN[HPI_MAX_ADAPTERS][HPI_MAX_STREAMS];

अटल काष्ठा hpi_stream_response
	rESP_HPI_ISTREAM_OPEN[HPI_MAX_ADAPTERS][HPI_MAX_STREAMS];

अटल काष्ठा hpi_mixer_response rESP_HPI_MIXER_OPEN[HPI_MAX_ADAPTERS];

अटल काष्ठा adapter_info aDAPTER_INFO[HPI_MAX_ADAPTERS];

/* use these to keep track of खोलोs from user mode apps/DLLs */
अटल काष्ठा asi_खोलो_state
	outstream_user_खोलो[HPI_MAX_ADAPTERS][HPI_MAX_STREAMS];

अटल काष्ठा asi_खोलो_state
	instream_user_खोलो[HPI_MAX_ADAPTERS][HPI_MAX_STREAMS];

अटल व्योम subsys_message(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु
	अगर (phm->adapter_index != HPI_ADAPTER_INDEX_INVALID)
		HPI_DEBUG_LOG(WARNING,
			"suspicious adapter index %d in subsys message 0x%x.\n",
			phm->adapter_index, phm->function);

	चयन (phm->function) अणु
	हाल HPI_SUBSYS_GET_VERSION:
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_GET_VERSION, 0);
		phr->u.s.version = HPI_VER >> 8;	/* वापस major.minor */
		phr->u.s.data = HPI_VER;	/* वापस major.minor.release */
		अवरोध;
	हाल HPI_SUBSYS_OPEN:
		/*करो not propagate the message करोwn the chain */
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM, HPI_SUBSYS_OPEN, 0);
		अवरोध;
	हाल HPI_SUBSYS_CLOSE:
		/*करो not propagate the message करोwn the chain */
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM, HPI_SUBSYS_CLOSE,
			0);
		HPIMSGX__cleanup(HPIMSGX_ALLADAPTERS, h_owner);
		अवरोध;
	हाल HPI_SUBSYS_DRIVER_LOAD:
		/* Initialize this module's पूर्णांकernal state */
		hpios_msgxlock_init(&msgx_lock);
		स_रखो(&hpi_entry_poपूर्णांकs, 0, माप(hpi_entry_poपूर्णांकs));
		/* Init subsys_findadapters response to no-adapters */
		HPIMSGX__reset(HPIMSGX_ALLADAPTERS);
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_DRIVER_LOAD, 0);
		/* inभागidual HPIs करोnt implement driver load */
		HPI_COMMON(phm, phr);
		अवरोध;
	हाल HPI_SUBSYS_DRIVER_UNLOAD:
		HPI_COMMON(phm, phr);
		HPIMSGX__cleanup(HPIMSGX_ALLADAPTERS, h_owner);
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM,
			HPI_SUBSYS_DRIVER_UNLOAD, 0);
		वापस;

	हाल HPI_SUBSYS_GET_NUM_ADAPTERS:
	हाल HPI_SUBSYS_GET_ADAPTER:
		HPI_COMMON(phm, phr);
		अवरोध;

	हाल HPI_SUBSYS_CREATE_ADAPTER:
		HPIMSGX__init(phm, phr);
		अवरोध;

	शेष:
		/* Must explicitly handle every subsys message in this चयन */
		hpi_init_response(phr, HPI_OBJ_SUBSYSTEM, phm->function,
			HPI_ERROR_INVALID_FUNC);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम adapter_message(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु
	चयन (phm->function) अणु
	हाल HPI_ADAPTER_OPEN:
		adapter_खोलो(phm, phr);
		अवरोध;
	हाल HPI_ADAPTER_CLOSE:
		adapter_बंद(phm, phr);
		अवरोध;
	हाल HPI_ADAPTER_DELETE:
		HPIMSGX__cleanup(phm->adapter_index, h_owner);
		अणु
			काष्ठा hpi_message hm;
			काष्ठा hpi_response hr;
			hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
				HPI_ADAPTER_CLOSE);
			hm.adapter_index = phm->adapter_index;
			hw_entry_poपूर्णांक(&hm, &hr);
		पूर्ण
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;

	शेष:
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mixer_message(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->function) अणु
	हाल HPI_MIXER_OPEN:
		mixer_खोलो(phm, phr);
		अवरोध;
	हाल HPI_MIXER_CLOSE:
		mixer_बंद(phm, phr);
		अवरोध;
	शेष:
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम outstream_message(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr, व्योम *h_owner)
अणु
	अगर (phm->obj_index >= aDAPTER_INFO[phm->adapter_index].num_outstreams) अणु
		hpi_init_response(phr, HPI_OBJ_OSTREAM, phm->function,
			HPI_ERROR_INVALID_OBJ_INDEX);
		वापस;
	पूर्ण

	चयन (phm->function) अणु
	हाल HPI_OSTREAM_OPEN:
		outstream_खोलो(phm, phr, h_owner);
		अवरोध;
	हाल HPI_OSTREAM_CLOSE:
		outstream_बंद(phm, phr, h_owner);
		अवरोध;
	शेष:
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम instream_message(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr, व्योम *h_owner)
अणु
	अगर (phm->obj_index >= aDAPTER_INFO[phm->adapter_index].num_instreams) अणु
		hpi_init_response(phr, HPI_OBJ_ISTREAM, phm->function,
			HPI_ERROR_INVALID_OBJ_INDEX);
		वापस;
	पूर्ण

	चयन (phm->function) अणु
	हाल HPI_ISTREAM_OPEN:
		instream_खोलो(phm, phr, h_owner);
		अवरोध;
	हाल HPI_ISTREAM_CLOSE:
		instream_बंद(phm, phr, h_owner);
		अवरोध;
	शेष:
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

/* NOTE: HPI_Message() must be defined in the driver as a wrapper क्रम
 * HPI_MessageEx so that functions in hpअगरunc.c compile.
 */
व्योम hpi_send_recv_ex(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु

	अगर (logging_enabled)
		HPI_DEBUG_MESSAGE(DEBUG, phm);

	अगर (phm->type != HPI_TYPE_REQUEST) अणु
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_INVALID_TYPE);
		वापस;
	पूर्ण

	अगर (phm->adapter_index >= HPI_MAX_ADAPTERS
		&& phm->adapter_index != HPIMSGX_ALLADAPTERS) अणु
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_BAD_ADAPTER_NUMBER);
		वापस;
	पूर्ण

	चयन (phm->object) अणु
	हाल HPI_OBJ_SUBSYSTEM:
		subsys_message(phm, phr, h_owner);
		अवरोध;

	हाल HPI_OBJ_ADAPTER:
		adapter_message(phm, phr, h_owner);
		अवरोध;

	हाल HPI_OBJ_MIXER:
		mixer_message(phm, phr);
		अवरोध;

	हाल HPI_OBJ_OSTREAM:
		outstream_message(phm, phr, h_owner);
		अवरोध;

	हाल HPI_OBJ_ISTREAM:
		instream_message(phm, phr, h_owner);
		अवरोध;

	शेष:
		hw_entry_poपूर्णांक(phm, phr);
		अवरोध;
	पूर्ण

	अगर (logging_enabled)
		HPI_DEBUG_RESPONSE(phr);

	अगर (phr->error >= HPI_ERROR_DSP_COMMUNICATION) अणु
		hpi_debug_level_set(HPI_DEBUG_LEVEL_ERROR);
		logging_enabled = 0;
	पूर्ण
पूर्ण

अटल व्योम adapter_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	HPI_DEBUG_LOG(VERBOSE, "adapter_open\n");
	स_नकल(phr, &rESP_HPI_ADAPTER_OPEN[phm->adapter_index],
		माप(rESP_HPI_ADAPTER_OPEN[0]));
पूर्ण

अटल व्योम adapter_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	HPI_DEBUG_LOG(VERBOSE, "adapter_close\n");
	hpi_init_response(phr, HPI_OBJ_ADAPTER, HPI_ADAPTER_CLOSE, 0);
पूर्ण

अटल व्योम mixer_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	स_नकल(phr, &rESP_HPI_MIXER_OPEN[phm->adapter_index],
		माप(rESP_HPI_MIXER_OPEN[0]));
पूर्ण

अटल व्योम mixer_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	hpi_init_response(phr, HPI_OBJ_MIXER, HPI_MIXER_CLOSE, 0);
पूर्ण

अटल व्योम instream_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_ISTREAM, HPI_ISTREAM_OPEN, 0);

	hpios_msgxlock_lock(&msgx_lock);

	अगर (instream_user_खोलो[phm->adapter_index][phm->obj_index].खोलो_flag)
		phr->error = HPI_ERROR_OBJ_ALREADY_OPEN;
	अन्यथा अगर (rESP_HPI_ISTREAM_OPEN[phm->adapter_index]
		[phm->obj_index].h.error)
		स_नकल(phr,
			&rESP_HPI_ISTREAM_OPEN[phm->adapter_index][phm->
				obj_index],
			माप(rESP_HPI_ISTREAM_OPEN[0][0]));
	अन्यथा अणु
		instream_user_खोलो[phm->adapter_index][phm->
			obj_index].खोलो_flag = 1;
		hpios_msgxlock_unlock(&msgx_lock);

		/* issue a reset */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_poपूर्णांक(&hm, &hr);

		hpios_msgxlock_lock(&msgx_lock);
		अगर (hr.error) अणु
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 0;
			phr->error = hr.error;
		पूर्ण अन्यथा अणु
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 1;
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			स_नकल(phr,
				&rESP_HPI_ISTREAM_OPEN[phm->adapter_index]
				[phm->obj_index],
				माप(rESP_HPI_ISTREAM_OPEN[0][0]));
		पूर्ण
	पूर्ण
	hpios_msgxlock_unlock(&msgx_lock);
पूर्ण

अटल व्योम instream_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_ISTREAM, HPI_ISTREAM_CLOSE, 0);

	hpios_msgxlock_lock(&msgx_lock);
	अगर (h_owner ==
		instream_user_खोलो[phm->adapter_index][phm->
			obj_index].h_owner) अणु
		/* HPI_DEBUG_LOG(INFO,"closing adapter %d "
		   "instream %d owned by %p\n",
		   phm->wAdapterIndex, phm->wObjIndex, hOwner); */
		instream_user_खोलो[phm->adapter_index][phm->
			obj_index].h_owner = शून्य;
		hpios_msgxlock_unlock(&msgx_lock);
		/* issue a reset */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_poपूर्णांक(&hm, &hr);
		hpios_msgxlock_lock(&msgx_lock);
		अगर (hr.error) अणु
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			phr->error = hr.error;
		पूर्ण अन्यथा अणु
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 0;
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		HPI_DEBUG_LOG(WARNING,
			"%p trying to close %d instream %d owned by %p\n",
			h_owner, phm->adapter_index, phm->obj_index,
			instream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner);
		phr->error = HPI_ERROR_OBJ_NOT_OPEN;
	पूर्ण
	hpios_msgxlock_unlock(&msgx_lock);
पूर्ण

अटल व्योम outstream_खोलो(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_OSTREAM, HPI_OSTREAM_OPEN, 0);

	hpios_msgxlock_lock(&msgx_lock);

	अगर (outstream_user_खोलो[phm->adapter_index][phm->obj_index].खोलो_flag)
		phr->error = HPI_ERROR_OBJ_ALREADY_OPEN;
	अन्यथा अगर (rESP_HPI_OSTREAM_OPEN[phm->adapter_index]
		[phm->obj_index].h.error)
		स_नकल(phr,
			&rESP_HPI_OSTREAM_OPEN[phm->adapter_index][phm->
				obj_index],
			माप(rESP_HPI_OSTREAM_OPEN[0][0]));
	अन्यथा अणु
		outstream_user_खोलो[phm->adapter_index][phm->
			obj_index].खोलो_flag = 1;
		hpios_msgxlock_unlock(&msgx_lock);

		/* issue a reset */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_poपूर्णांक(&hm, &hr);

		hpios_msgxlock_lock(&msgx_lock);
		अगर (hr.error) अणु
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 0;
			phr->error = hr.error;
		पूर्ण अन्यथा अणु
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 1;
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			स_नकल(phr,
				&rESP_HPI_OSTREAM_OPEN[phm->adapter_index]
				[phm->obj_index],
				माप(rESP_HPI_OSTREAM_OPEN[0][0]));
		पूर्ण
	पूर्ण
	hpios_msgxlock_unlock(&msgx_lock);
पूर्ण

अटल व्योम outstream_बंद(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr,
	व्योम *h_owner)
अणु

	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	hpi_init_response(phr, HPI_OBJ_OSTREAM, HPI_OSTREAM_CLOSE, 0);

	hpios_msgxlock_lock(&msgx_lock);

	अगर (h_owner ==
		outstream_user_खोलो[phm->adapter_index][phm->
			obj_index].h_owner) अणु
		/* HPI_DEBUG_LOG(INFO,"closing adapter %d "
		   "outstream %d owned by %p\n",
		   phm->wAdapterIndex, phm->wObjIndex, hOwner); */
		outstream_user_खोलो[phm->adapter_index][phm->
			obj_index].h_owner = शून्य;
		hpios_msgxlock_unlock(&msgx_lock);
		/* issue a reset */
		hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_RESET);
		hm.adapter_index = phm->adapter_index;
		hm.obj_index = phm->obj_index;
		hw_entry_poपूर्णांक(&hm, &hr);
		hpios_msgxlock_lock(&msgx_lock);
		अगर (hr.error) अणु
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = h_owner;
			phr->error = hr.error;
		पूर्ण अन्यथा अणु
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].खोलो_flag = 0;
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		HPI_DEBUG_LOG(WARNING,
			"%p trying to close %d outstream %d owned by %p\n",
			h_owner, phm->adapter_index, phm->obj_index,
			outstream_user_खोलो[phm->adapter_index][phm->
				obj_index].h_owner);
		phr->error = HPI_ERROR_OBJ_NOT_OPEN;
	पूर्ण
	hpios_msgxlock_unlock(&msgx_lock);
पूर्ण

अटल u16 adapter_prepare(u16 adapter)
अणु
	काष्ठा hpi_message hm;
	काष्ठा hpi_response hr;

	/* Open the adapter and streams */
	u16 i;

	/* call to HPI_ADAPTER_OPEN */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_OPEN);
	hm.adapter_index = adapter;
	hw_entry_poपूर्णांक(&hm, &hr);
	स_नकल(&rESP_HPI_ADAPTER_OPEN[adapter], &hr,
		माप(rESP_HPI_ADAPTER_OPEN[0]));
	अगर (hr.error)
		वापस hr.error;

	/* call to HPI_ADAPTER_GET_INFO */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_ADAPTER,
		HPI_ADAPTER_GET_INFO);
	hm.adapter_index = adapter;
	hw_entry_poपूर्णांक(&hm, &hr);
	अगर (hr.error)
		वापस hr.error;

	aDAPTER_INFO[adapter].num_outstreams = hr.u.ax.info.num_outstreams;
	aDAPTER_INFO[adapter].num_instreams = hr.u.ax.info.num_instreams;
	aDAPTER_INFO[adapter].type = hr.u.ax.info.adapter_type;

	/* call to HPI_OSTREAM_OPEN */
	क्रम (i = 0; i < aDAPTER_INFO[adapter].num_outstreams; i++) अणु
		hpi_init_message_response(&hm, &hr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_OPEN);
		hm.adapter_index = adapter;
		hm.obj_index = i;
		hw_entry_poपूर्णांक(&hm, &hr);
		स_नकल(&rESP_HPI_OSTREAM_OPEN[adapter][i], &hr,
			माप(rESP_HPI_OSTREAM_OPEN[0][0]));
		outstream_user_खोलो[adapter][i].खोलो_flag = 0;
		outstream_user_खोलो[adapter][i].h_owner = शून्य;
	पूर्ण

	/* call to HPI_ISTREAM_OPEN */
	क्रम (i = 0; i < aDAPTER_INFO[adapter].num_instreams; i++) अणु
		hpi_init_message_response(&hm, &hr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_OPEN);
		hm.adapter_index = adapter;
		hm.obj_index = i;
		hw_entry_poपूर्णांक(&hm, &hr);
		स_नकल(&rESP_HPI_ISTREAM_OPEN[adapter][i], &hr,
			माप(rESP_HPI_ISTREAM_OPEN[0][0]));
		instream_user_खोलो[adapter][i].खोलो_flag = 0;
		instream_user_खोलो[adapter][i].h_owner = शून्य;
	पूर्ण

	/* call to HPI_MIXER_OPEN */
	hpi_init_message_response(&hm, &hr, HPI_OBJ_MIXER, HPI_MIXER_OPEN);
	hm.adapter_index = adapter;
	hw_entry_poपूर्णांक(&hm, &hr);
	स_नकल(&rESP_HPI_MIXER_OPEN[adapter], &hr,
		माप(rESP_HPI_MIXER_OPEN[0]));

	वापस 0;
पूर्ण

अटल व्योम HPIMSGX__reset(u16 adapter_index)
अणु
	पूर्णांक i;
	u16 adapter;
	काष्ठा hpi_response hr;

	अगर (adapter_index == HPIMSGX_ALLADAPTERS) अणु
		क्रम (adapter = 0; adapter < HPI_MAX_ADAPTERS; adapter++) अणु

			hpi_init_response(&hr, HPI_OBJ_ADAPTER,
				HPI_ADAPTER_OPEN, HPI_ERROR_BAD_ADAPTER);
			स_नकल(&rESP_HPI_ADAPTER_OPEN[adapter], &hr,
				माप(rESP_HPI_ADAPTER_OPEN[adapter]));

			hpi_init_response(&hr, HPI_OBJ_MIXER, HPI_MIXER_OPEN,
				HPI_ERROR_INVALID_OBJ);
			स_नकल(&rESP_HPI_MIXER_OPEN[adapter], &hr,
				माप(rESP_HPI_MIXER_OPEN[adapter]));

			क्रम (i = 0; i < HPI_MAX_STREAMS; i++) अणु
				hpi_init_response(&hr, HPI_OBJ_OSTREAM,
					HPI_OSTREAM_OPEN,
					HPI_ERROR_INVALID_OBJ);
				स_नकल(&rESP_HPI_OSTREAM_OPEN[adapter][i],
					&hr,
					माप(rESP_HPI_OSTREAM_OPEN[adapter]
						[i]));
				hpi_init_response(&hr, HPI_OBJ_ISTREAM,
					HPI_ISTREAM_OPEN,
					HPI_ERROR_INVALID_OBJ);
				स_नकल(&rESP_HPI_ISTREAM_OPEN[adapter][i],
					&hr,
					माप(rESP_HPI_ISTREAM_OPEN[adapter]
						[i]));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (adapter_index < HPI_MAX_ADAPTERS) अणु
		rESP_HPI_ADAPTER_OPEN[adapter_index].h.error =
			HPI_ERROR_BAD_ADAPTER;
		rESP_HPI_MIXER_OPEN[adapter_index].h.error =
			HPI_ERROR_INVALID_OBJ;
		क्रम (i = 0; i < HPI_MAX_STREAMS; i++) अणु
			rESP_HPI_OSTREAM_OPEN[adapter_index][i].h.error =
				HPI_ERROR_INVALID_OBJ;
			rESP_HPI_ISTREAM_OPEN[adapter_index][i].h.error =
				HPI_ERROR_INVALID_OBJ;
		पूर्ण
	पूर्ण
पूर्ण

अटल u16 HPIMSGX__init(काष्ठा hpi_message *phm,
	/* HPI_SUBSYS_CREATE_ADAPTER काष्ठाure with */
	/* resource list or शून्य=find all */
	काष्ठा hpi_response *phr
	/* response from HPI_ADAPTER_GET_INFO */
	)
अणु
	hpi_handler_func *entry_poपूर्णांक_func;
	काष्ठा hpi_response hr;

	/* Init response here so we can pass in previous adapter list */
	hpi_init_response(&hr, phm->object, phm->function,
		HPI_ERROR_INVALID_OBJ);

	entry_poपूर्णांक_func =
		hpi_lookup_entry_poपूर्णांक_function(phm->u.s.resource.r.pci);

	अगर (entry_poपूर्णांक_func) अणु
		HPI_DEBUG_MESSAGE(DEBUG, phm);
		entry_poपूर्णांक_func(phm, &hr);
	पूर्ण अन्यथा अणु
		phr->error = HPI_ERROR_PROCESSING_MESSAGE;
		वापस phr->error;
	पूर्ण
	अगर (hr.error == 0) अणु
		/* the adapter was created successfully
		   save the mapping क्रम future use */
		hpi_entry_poपूर्णांकs[hr.u.s.adapter_index] = entry_poपूर्णांक_func;
		/* prepare adapter (pre-खोलो streams etc.) */
		HPI_DEBUG_LOG(DEBUG,
			"HPI_SUBSYS_CREATE_ADAPTER successful,"
			" preparing adapter\n");
		adapter_prepare(hr.u.s.adapter_index);
	पूर्ण
	स_नकल(phr, &hr, hr.size);
	वापस phr->error;
पूर्ण

अटल व्योम HPIMSGX__cleanup(u16 adapter_index, व्योम *h_owner)
अणु
	पूर्णांक i, adapter, adapter_limit;

	अगर (!h_owner)
		वापस;

	अगर (adapter_index == HPIMSGX_ALLADAPTERS) अणु
		adapter = 0;
		adapter_limit = HPI_MAX_ADAPTERS;
	पूर्ण अन्यथा अणु
		adapter = adapter_index;
		adapter_limit = adapter + 1;
	पूर्ण

	क्रम (; adapter < adapter_limit; adapter++) अणु
		/*      prपूर्णांकk(KERN_INFO "Cleanup adapter #%d\n",wAdapter); */
		क्रम (i = 0; i < HPI_MAX_STREAMS; i++) अणु
			अगर (h_owner ==
				outstream_user_खोलो[adapter][i].h_owner) अणु
				काष्ठा hpi_message hm;
				काष्ठा hpi_response hr;

				HPI_DEBUG_LOG(DEBUG,
					"Close adapter %d ostream %d\n",
					adapter, i);

				hpi_init_message_response(&hm, &hr,
					HPI_OBJ_OSTREAM, HPI_OSTREAM_RESET);
				hm.adapter_index = (u16)adapter;
				hm.obj_index = (u16)i;
				hw_entry_poपूर्णांक(&hm, &hr);

				hm.function = HPI_OSTREAM_HOSTBUFFER_FREE;
				hw_entry_poपूर्णांक(&hm, &hr);

				hm.function = HPI_OSTREAM_GROUP_RESET;
				hw_entry_poपूर्णांक(&hm, &hr);

				outstream_user_खोलो[adapter][i].खोलो_flag = 0;
				outstream_user_खोलो[adapter][i].h_owner =
					शून्य;
			पूर्ण
			अगर (h_owner == instream_user_खोलो[adapter][i].h_owner) अणु
				काष्ठा hpi_message hm;
				काष्ठा hpi_response hr;

				HPI_DEBUG_LOG(DEBUG,
					"Close adapter %d istream %d\n",
					adapter, i);

				hpi_init_message_response(&hm, &hr,
					HPI_OBJ_ISTREAM, HPI_ISTREAM_RESET);
				hm.adapter_index = (u16)adapter;
				hm.obj_index = (u16)i;
				hw_entry_poपूर्णांक(&hm, &hr);

				hm.function = HPI_ISTREAM_HOSTBUFFER_FREE;
				hw_entry_poपूर्णांक(&hm, &hr);

				hm.function = HPI_ISTREAM_GROUP_RESET;
				hw_entry_poपूर्णांक(&hm, &hr);

				instream_user_खोलो[adapter][i].खोलो_flag = 0;
				instream_user_खोलो[adapter][i].h_owner = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
