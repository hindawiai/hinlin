<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2011  AudioScience Inc. <support@audioscience.com>


 Hardware Programming Interface (HPI) क्रम AudioScience ASI6200 series adapters.
 These PCI bus adapters are based on the TI C6711 DSP.

 Exported functions:
 व्योम HPI_6000(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)

 #घोषणाs
 HIDE_PCI_ASSERTS to show the PCI निश्चितs
 PROखाता_DSP2 get profile data from DSP2 अगर present (instead of DSP 1)

(C) Copyright AudioScience Inc. 1998-2003
*******************************************************************************/
#घोषणा SOURCEखाता_NAME "hpi6000.c"

#समावेश "hpi_internal.h"
#समावेश "hpimsginit.h"
#समावेश "hpidebug.h"
#समावेश "hpi6000.h"
#समावेश "hpidspcd.h"
#समावेश "hpicmn.h"

#घोषणा HPI_HIF_BASE (0x00000200)	/* start of C67xx पूर्णांकernal RAM */
#घोषणा HPI_HIF_ADDR(member) \
	(HPI_HIF_BASE + दुरत्व(काष्ठा hpi_hअगर_6000, member))
#घोषणा HPI_HIF_ERROR_MASK      0x4000

/* HPI6000 specअगरic error codes */
#घोषणा HPI6000_ERROR_BASE 900	/* not actually used anywhere */

/* operational/messaging errors */
#घोषणा HPI6000_ERROR_MSG_RESP_IDLE_TIMEOUT             901
#घोषणा HPI6000_ERROR_RESP_GET_LEN                      902
#घोषणा HPI6000_ERROR_MSG_RESP_GET_RESP_ACK             903
#घोषणा HPI6000_ERROR_MSG_GET_ADR                       904
#घोषणा HPI6000_ERROR_RESP_GET_ADR                      905
#घोषणा HPI6000_ERROR_MSG_RESP_BLOCKWRITE32             906
#घोषणा HPI6000_ERROR_MSG_RESP_BLOCKREAD32              907

#घोषणा HPI6000_ERROR_CONTROL_CACHE_PARAMS              909

#घोषणा HPI6000_ERROR_SEND_DATA_IDLE_TIMEOUT            911
#घोषणा HPI6000_ERROR_SEND_DATA_ACK                     912
#घोषणा HPI6000_ERROR_SEND_DATA_ADR                     913
#घोषणा HPI6000_ERROR_SEND_DATA_TIMEOUT                 914
#घोषणा HPI6000_ERROR_SEND_DATA_CMD                     915
#घोषणा HPI6000_ERROR_SEND_DATA_WRITE                   916
#घोषणा HPI6000_ERROR_SEND_DATA_IDLECMD                 917

#घोषणा HPI6000_ERROR_GET_DATA_IDLE_TIMEOUT             921
#घोषणा HPI6000_ERROR_GET_DATA_ACK                      922
#घोषणा HPI6000_ERROR_GET_DATA_CMD                      923
#घोषणा HPI6000_ERROR_GET_DATA_READ                     924
#घोषणा HPI6000_ERROR_GET_DATA_IDLECMD                  925

#घोषणा HPI6000_ERROR_CONTROL_CACHE_ADDRLEN             951
#घोषणा HPI6000_ERROR_CONTROL_CACHE_READ                952
#घोषणा HPI6000_ERROR_CONTROL_CACHE_FLUSH               953

#घोषणा HPI6000_ERROR_MSG_RESP_GETRESPCMD               961
#घोषणा HPI6000_ERROR_MSG_RESP_IDLECMD                  962

/* Initialisation/bootload errors */
#घोषणा HPI6000_ERROR_UNHANDLED_SUBSYS_ID               930

/* can't access PCI2040 */
#घोषणा HPI6000_ERROR_INIT_PCI2040                      931
/* can't access DSP HPI i/f */
#घोषणा HPI6000_ERROR_INIT_DSPHPI                       932
/* can't access पूर्णांकernal DSP memory */
#घोषणा HPI6000_ERROR_INIT_DSPINTMEM                    933
/* can't access SDRAM - test#1 */
#घोषणा HPI6000_ERROR_INIT_SDRAM1                       934
/* can't access SDRAM - test#2 */
#घोषणा HPI6000_ERROR_INIT_SDRAM2                       935

#घोषणा HPI6000_ERROR_INIT_VERIFY                       938

#घोषणा HPI6000_ERROR_INIT_NOACK                        939

#घोषणा HPI6000_ERROR_INIT_PLDTEST1                     941
#घोषणा HPI6000_ERROR_INIT_PLDTEST2                     942

/* local defines */

#घोषणा HIDE_PCI_ASSERTS
#घोषणा PROखाता_DSP2

/* क्रम PCI2040 i/f chip */
/* HPI CSR रेजिस्टरs */
/* word offsets from CSR base */
/* use when io addresses defined as u32 * */

#घोषणा INTERRUPT_EVENT_SET     0
#घोषणा INTERRUPT_EVENT_CLEAR   1
#घोषणा INTERRUPT_MASK_SET      2
#घोषणा INTERRUPT_MASK_CLEAR    3
#घोषणा HPI_ERROR_REPORT        4
#घोषणा HPI_RESET               5
#घोषणा HPI_DATA_WIDTH          6

#घोषणा MAX_DSPS 2
/* HPI रेजिस्टरs, spaced 8K bytes = 2K words apart */
#घोषणा DSP_SPACING             0x800

#घोषणा CONTROL                 0x0000
#घोषणा ADDRESS                 0x0200
#घोषणा DATA_AUTOINC            0x0400
#घोषणा DATA                    0x0600

#घोषणा TIMEOUT 500000

काष्ठा dsp_obj अणु
	__iomem u32 *prHPI_control;
	__iomem u32 *prHPI_address;
	__iomem u32 *prHPI_data;
	__iomem u32 *prHPI_data_स्वतः_inc;
	अक्षर c_dsp_rev;		/*A, B */
	u32 control_cache_address_on_dsp;
	u32 control_cache_length_on_dsp;
	काष्ठा hpi_adapter_obj *pa_parent_adapter;
पूर्ण;

काष्ठा hpi_hw_obj अणु
	__iomem u32 *dw2040_HPICSR;
	__iomem u32 *dw2040_HPIDSP;

	u16 num_dsp;
	काष्ठा dsp_obj aकरो[MAX_DSPS];

	u32 message_buffer_address_on_dsp;
	u32 response_buffer_address_on_dsp;
	u32 pCI2040HPI_error_count;

	काष्ठा hpi_control_cache_single control_cache[HPI_NMIXER_CONTROLS];
	काष्ठा hpi_control_cache *p_cache;
पूर्ण;

अटल u16 hpi6000_dsp_block_ग_लिखो32(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 hpi_address, u32 *source, u32 count);
अटल u16 hpi6000_dsp_block_पढ़ो32(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 hpi_address, u32 *dest, u32 count);

अटल लघु hpi6000_adapter_boot_load_dsp(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code);
अटल लघु hpi6000_check_PCI2040_error_flag(काष्ठा hpi_adapter_obj *pao,
	u16 पढ़ो_or_ग_लिखो);
#घोषणा H6READ 1
#घोषणा H6WRITE 0

अटल लघु hpi6000_update_control_cache(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm);
अटल लघु hpi6000_message_response_sequence(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम hw_message(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr);

अटल लघु hpi6000_रुको_dsp_ack(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	u32 ack_value);

अटल लघु hpi6000_send_host_command(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 host_cmd);

अटल व्योम hpi6000_send_dsp_पूर्णांकerrupt(काष्ठा dsp_obj *pकरो);

अटल लघु hpi6000_send_data(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल लघु hpi6000_get_data(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम hpi_ग_लिखो_word(काष्ठा dsp_obj *pकरो, u32 address, u32 data);

अटल u32 hpi_पढ़ो_word(काष्ठा dsp_obj *pकरो, u32 address);

अटल व्योम hpi_ग_लिखो_block(काष्ठा dsp_obj *pकरो, u32 address, u32 *pdata,
	u32 length);

अटल व्योम hpi_पढ़ो_block(काष्ठा dsp_obj *pकरो, u32 address, u32 *pdata,
	u32 length);

अटल व्योम subsys_create_adapter(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr);

अटल व्योम adapter_delete(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम adapter_get_निश्चितs(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल लघु create_adapter_obj(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code);

अटल व्योम delete_adapter_obj(काष्ठा hpi_adapter_obj *pao);

/* local globals */

अटल u16 gw_pci_पढ़ो_निश्चितs;	/* used to count PCI2040 errors */
अटल u16 gw_pci_ग_लिखो_निश्चितs;	/* used to count PCI2040 errors */

अटल व्योम subsys_message(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->function) अणु
	हाल HPI_SUBSYS_CREATE_ADAPTER:
		subsys_create_adapter(phm, phr);
		अवरोध;
	शेष:
		phr->error = HPI_ERROR_INVALID_FUNC;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम control_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;

	चयन (phm->function) अणु
	हाल HPI_CONTROL_GET_STATE:
		अगर (pao->has_control_cache) अणु
			u16 err;
			err = hpi6000_update_control_cache(pao, phm);

			अगर (err) अणु
				अगर (err >= HPI_ERROR_BACKEND_BASE) अणु
					phr->error =
						HPI_ERROR_CONTROL_CACHING;
					phr->specअगरic_error = err;
				पूर्ण अन्यथा अणु
					phr->error = err;
				पूर्ण
				अवरोध;
			पूर्ण

			अगर (hpi_check_control_cache(phw->p_cache, phm, phr))
				अवरोध;
		पूर्ण
		hw_message(pao, phm, phr);
		अवरोध;
	हाल HPI_CONTROL_SET_STATE:
		hw_message(pao, phm, phr);
		hpi_cmn_control_cache_sync_to_msg(phw->p_cache, phm, phr);
		अवरोध;

	हाल HPI_CONTROL_GET_INFO:
	शेष:
		hw_message(pao, phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम adapter_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->function) अणु
	हाल HPI_ADAPTER_GET_ASSERT:
		adapter_get_निश्चितs(pao, phm, phr);
		अवरोध;

	हाल HPI_ADAPTER_DELETE:
		adapter_delete(pao, phm, phr);
		अवरोध;

	शेष:
		hw_message(pao, phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम outstream_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->function) अणु
	हाल HPI_OSTREAM_HOSTBUFFER_ALLOC:
	हाल HPI_OSTREAM_HOSTBUFFER_FREE:
		/* Don't let these messages go to the HW function because
		 * they're called without locking the spinlock.
		 * For the HPI6000 adapters the HW would वापस
		 * HPI_ERROR_INVALID_FUNC anyway.
		 */
		phr->error = HPI_ERROR_INVALID_FUNC;
		अवरोध;
	शेष:
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम instream_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु

	चयन (phm->function) अणु
	हाल HPI_ISTREAM_HOSTBUFFER_ALLOC:
	हाल HPI_ISTREAM_HOSTBUFFER_FREE:
		/* Don't let these messages go to the HW function because
		 * they're called without locking the spinlock.
		 * For the HPI6000 adapters the HW would वापस
		 * HPI_ERROR_INVALID_FUNC anyway.
		 */
		phr->error = HPI_ERROR_INVALID_FUNC;
		अवरोध;
	शेष:
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण
पूर्ण

/************************************************************************/
/** HPI_6000()
 * Entry poपूर्णांक from HPIMAN
 * All calls to the HPI start here
 */
व्योम HPI_6000(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_adapter_obj *pao = शून्य;

	अगर (phm->object != HPI_OBJ_SUBSYSTEM) अणु
		pao = hpi_find_adapter(phm->adapter_index);
		अगर (!pao) अणु
			hpi_init_response(phr, phm->object, phm->function,
				HPI_ERROR_BAD_ADAPTER_NUMBER);
			HPI_DEBUG_LOG(DEBUG, "invalid adapter index: %d \n",
				phm->adapter_index);
			वापस;
		पूर्ण

		/* Don't even try to communicate with crashed DSP */
		अगर (pao->dsp_crashed >= 10) अणु
			hpi_init_response(phr, phm->object, phm->function,
				HPI_ERROR_DSP_HARDWARE);
			HPI_DEBUG_LOG(DEBUG, "adapter %d dsp crashed\n",
				phm->adapter_index);
			वापस;
		पूर्ण
	पूर्ण
	/* Init शेष response including the size field */
	अगर (phm->function != HPI_SUBSYS_CREATE_ADAPTER)
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_PROCESSING_MESSAGE);

	चयन (phm->type) अणु
	हाल HPI_TYPE_REQUEST:
		चयन (phm->object) अणु
		हाल HPI_OBJ_SUBSYSTEM:
			subsys_message(phm, phr);
			अवरोध;

		हाल HPI_OBJ_ADAPTER:
			phr->size =
				माप(काष्ठा hpi_response_header) +
				माप(काष्ठा hpi_adapter_res);
			adapter_message(pao, phm, phr);
			अवरोध;

		हाल HPI_OBJ_CONTROL:
			control_message(pao, phm, phr);
			अवरोध;

		हाल HPI_OBJ_OSTREAM:
			outstream_message(pao, phm, phr);
			अवरोध;

		हाल HPI_OBJ_ISTREAM:
			instream_message(pao, phm, phr);
			अवरोध;

		शेष:
			hw_message(pao, phm, phr);
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		phr->error = HPI_ERROR_INVALID_TYPE;
		अवरोध;
	पूर्ण
पूर्ण

/************************************************************************/
/* SUBSYSTEM */

/* create an adapter object and initialise it based on resource inक्रमmation
 * passed in in the message
 * NOTE - you cannot use this function AND the FindAdapters function at the
 * same समय, the application must use only one of them to get the adapters
 */
अटल व्योम subsys_create_adapter(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	/* create temp adapter obj, because we करोn't know what index yet */
	काष्ठा hpi_adapter_obj ao;
	काष्ठा hpi_adapter_obj *pao;
	u32 os_error_code;
	u16 err = 0;
	u32 dsp_index = 0;

	HPI_DEBUG_LOG(VERBOSE, "subsys_create_adapter\n");

	स_रखो(&ao, 0, माप(ao));

	ao.priv = kzalloc(माप(काष्ठा hpi_hw_obj), GFP_KERNEL);
	अगर (!ao.priv) अणु
		HPI_DEBUG_LOG(ERROR, "can't get mem for adapter object\n");
		phr->error = HPI_ERROR_MEMORY_ALLOC;
		वापस;
	पूर्ण

	/* create the adapter object based on the resource inक्रमmation */
	ao.pci = *phm->u.s.resource.r.pci;

	err = create_adapter_obj(&ao, &os_error_code);
	अगर (err) अणु
		delete_adapter_obj(&ao);
		अगर (err >= HPI_ERROR_BACKEND_BASE) अणु
			phr->error = HPI_ERROR_DSP_BOOTLOAD;
			phr->specअगरic_error = err;
		पूर्ण अन्यथा अणु
			phr->error = err;
		पूर्ण

		phr->u.s.data = os_error_code;
		वापस;
	पूर्ण
	/* need to update paParentAdapter */
	pao = hpi_find_adapter(ao.index);
	अगर (!pao) अणु
		/* We just added this adapter, why can't we find it!? */
		HPI_DEBUG_LOG(ERROR, "lost adapter after boot\n");
		phr->error = HPI_ERROR_BAD_ADAPTER;
		वापस;
	पूर्ण

	क्रम (dsp_index = 0; dsp_index < MAX_DSPS; dsp_index++) अणु
		काष्ठा hpi_hw_obj *phw = pao->priv;
		phw->aकरो[dsp_index].pa_parent_adapter = pao;
	पूर्ण

	phr->u.s.adapter_type = ao.type;
	phr->u.s.adapter_index = ao.index;
	phr->error = 0;
पूर्ण

अटल व्योम adapter_delete(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	delete_adapter_obj(pao);
	hpi_delete_adapter(pao);
	phr->error = 0;
पूर्ण

/* this routine is called from SubSysFindAdapter and SubSysCreateAdapter */
अटल लघु create_adapter_obj(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code)
अणु
	लघु boot_error = 0;
	u32 dsp_index = 0;
	u32 control_cache_size = 0;
	u32 control_cache_count = 0;
	काष्ठा hpi_hw_obj *phw = pao->priv;

	/* The PCI2040 has the following address map */
	/* BAR0 - 4K = HPI control and status रेजिस्टरs on PCI2040 (HPI CSR) */
	/* BAR1 - 32K = HPI रेजिस्टरs on DSP */
	phw->dw2040_HPICSR = pao->pci.ap_mem_base[0];
	phw->dw2040_HPIDSP = pao->pci.ap_mem_base[1];
	HPI_DEBUG_LOG(VERBOSE, "csr %p, dsp %p\n", phw->dw2040_HPICSR,
		phw->dw2040_HPIDSP);

	/* set addresses क्रम the possible DSP HPI पूर्णांकerfaces */
	क्रम (dsp_index = 0; dsp_index < MAX_DSPS; dsp_index++) अणु
		phw->aकरो[dsp_index].prHPI_control =
			phw->dw2040_HPIDSP + (CONTROL +
			DSP_SPACING * dsp_index);

		phw->aकरो[dsp_index].prHPI_address =
			phw->dw2040_HPIDSP + (ADDRESS +
			DSP_SPACING * dsp_index);
		phw->aकरो[dsp_index].prHPI_data =
			phw->dw2040_HPIDSP + (DATA + DSP_SPACING * dsp_index);

		phw->aकरो[dsp_index].prHPI_data_स्वतः_inc =
			phw->dw2040_HPIDSP + (DATA_AUTOINC +
			DSP_SPACING * dsp_index);

		HPI_DEBUG_LOG(VERBOSE, "ctl %p, adr %p, dat %p, dat++ %p\n",
			phw->aकरो[dsp_index].prHPI_control,
			phw->aकरो[dsp_index].prHPI_address,
			phw->aकरो[dsp_index].prHPI_data,
			phw->aकरो[dsp_index].prHPI_data_स्वतः_inc);

		phw->aकरो[dsp_index].pa_parent_adapter = pao;
	पूर्ण

	phw->pCI2040HPI_error_count = 0;
	pao->has_control_cache = 0;

	/* Set the शेष number of DSPs on this card */
	/* This is (conditionally) adjusted after bootloading */
	/* of the first DSP in the bootload section. */
	phw->num_dsp = 1;

	boot_error = hpi6000_adapter_boot_load_dsp(pao, pos_error_code);
	अगर (boot_error)
		वापस boot_error;

	HPI_DEBUG_LOG(INFO, "bootload DSP OK\n");

	phw->message_buffer_address_on_dsp = 0L;
	phw->response_buffer_address_on_dsp = 0L;

	/* get info about the adapter by asking the adapter */
	/* send a HPI_ADAPTER_GET_INFO message */
	अणु
		काष्ठा hpi_message hm;
		काष्ठा hpi_response hr0;	/* response from DSP 0 */
		काष्ठा hpi_response hr1;	/* response from DSP 1 */
		u16 error = 0;

		HPI_DEBUG_LOG(VERBOSE, "send ADAPTER_GET_INFO\n");
		स_रखो(&hm, 0, माप(hm));
		hm.type = HPI_TYPE_REQUEST;
		hm.size = माप(काष्ठा hpi_message);
		hm.object = HPI_OBJ_ADAPTER;
		hm.function = HPI_ADAPTER_GET_INFO;
		hm.adapter_index = 0;
		स_रखो(&hr0, 0, माप(hr0));
		स_रखो(&hr1, 0, माप(hr1));
		hr0.size = माप(hr0);
		hr1.size = माप(hr1);

		error = hpi6000_message_response_sequence(pao, 0, &hm, &hr0);
		अगर (hr0.error) अणु
			HPI_DEBUG_LOG(DEBUG, "message error %d\n", hr0.error);
			वापस hr0.error;
		पूर्ण
		अगर (phw->num_dsp == 2) अणु
			error = hpi6000_message_response_sequence(pao, 1, &hm,
				&hr1);
			अगर (error)
				वापस error;
		पूर्ण
		pao->type = hr0.u.ax.info.adapter_type;
		pao->index = hr0.u.ax.info.adapter_index;
	पूर्ण

	स_रखो(&phw->control_cache[0], 0,
		माप(काष्ठा hpi_control_cache_single) *
		HPI_NMIXER_CONTROLS);
	/* Read the control cache length to figure out अगर it is turned on */
	control_cache_size =
		hpi_पढ़ो_word(&phw->aकरो[0],
		HPI_HIF_ADDR(control_cache_size_in_bytes));
	अगर (control_cache_size) अणु
		control_cache_count =
			hpi_पढ़ो_word(&phw->aकरो[0],
			HPI_HIF_ADDR(control_cache_count));

		phw->p_cache =
			hpi_alloc_control_cache(control_cache_count,
			control_cache_size, (अचिन्हित अक्षर *)
			&phw->control_cache[0]
			);
		अगर (phw->p_cache)
			pao->has_control_cache = 1;
	पूर्ण

	HPI_DEBUG_LOG(DEBUG, "get adapter info ASI%04X index %d\n", pao->type,
		pao->index);

	अगर (phw->p_cache)
		phw->p_cache->adap_idx = pao->index;

	वापस hpi_add_adapter(pao);
पूर्ण

अटल व्योम delete_adapter_obj(काष्ठा hpi_adapter_obj *pao)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;

	अगर (pao->has_control_cache)
		hpi_मुक्त_control_cache(phw->p_cache);

	/* reset DSPs on adapter */
	ioग_लिखो32(0x0003000F, phw->dw2040_HPICSR + HPI_RESET);

	kमुक्त(phw);
पूर्ण

/************************************************************************/
/* ADAPTER */

अटल व्योम adapter_get_निश्चितs(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
#अगर_अघोषित HIDE_PCI_ASSERTS
	/* अगर we have PCI2040 निश्चितs then collect them */
	अगर ((gw_pci_पढ़ो_निश्चितs > 0) || (gw_pci_ग_लिखो_निश्चितs > 0)) अणु
		phr->u.ax.निश्चित.p1 =
			gw_pci_पढ़ो_निश्चितs * 100 + gw_pci_ग_लिखो_निश्चितs;
		phr->u.ax.निश्चित.p2 = 0;
		phr->u.ax.निश्चित.count = 1;	/* निश्चित count */
		phr->u.ax.निश्चित.dsp_index = -1;	/* "dsp index" */
		म_नकल(phr->u.ax.निश्चित.sz_message, "PCI2040 error");
		phr->u.ax.निश्चित.dsp_msg_addr = 0;
		gw_pci_पढ़ो_निश्चितs = 0;
		gw_pci_ग_लिखो_निश्चितs = 0;
		phr->error = 0;
	पूर्ण अन्यथा
#पूर्ण_अगर
		hw_message(pao, phm, phr);	/*get DSP निश्चितs */

	वापस;
पूर्ण

/************************************************************************/
/* LOW-LEVEL */

अटल लघु hpi6000_adapter_boot_load_dsp(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	लघु error;
	u32 समयout;
	u32 पढ़ो = 0;
	u32 i = 0;
	u32 data = 0;
	u32 j = 0;
	u32 test_addr = 0x80000000;
	u32 test_data = 0x00000001;
	u32 dw2040_reset = 0;
	u32 dsp_index = 0;
	u32 endian = 0;
	u32 adapter_info = 0;
	u32 delay = 0;

	काष्ठा dsp_code dsp_code;
	u16 boot_load_family = 0;

	/* NOTE करोn't use wAdapterType in this routine. It is not setup yet */

	चयन (pao->pci.pci_dev->subप्रणाली_device) अणु
	हाल 0x5100:
	हाल 0x5110:	/* ASI5100 revB or higher with C6711D */
	हाल 0x5200:	/* ASI5200 PCIe version of ASI5100 */
	हाल 0x6100:
	हाल 0x6200:
		boot_load_family = HPI_ADAPTER_FAMILY_ASI(0x6200);
		अवरोध;
	शेष:
		वापस HPI6000_ERROR_UNHANDLED_SUBSYS_ID;
	पूर्ण

	/* reset all DSPs, indicate two DSPs are present
	 * set RST3-=1 to disconnect HAD8 to set DSP in little endian mode
	 */
	endian = 0;
	dw2040_reset = 0x0003000F;
	ioग_लिखो32(dw2040_reset, phw->dw2040_HPICSR + HPI_RESET);

	/* पढ़ो back रेजिस्टर to make sure PCI2040 chip is functioning
	 * note that bits 4..15 are पढ़ो-only and so should always वापस zero,
	 * even though we wrote 1 to them
	 */
	hpios_delay_micro_seconds(1000);
	delay = ioपढ़ो32(phw->dw2040_HPICSR + HPI_RESET);

	अगर (delay != dw2040_reset) अणु
		HPI_DEBUG_LOG(ERROR, "INIT_PCI2040 %x %x\n", dw2040_reset,
			delay);
		वापस HPI6000_ERROR_INIT_PCI2040;
	पूर्ण

	/* Indicate that DSP#0,1 is a C6X */
	ioग_लिखो32(0x00000003, phw->dw2040_HPICSR + HPI_DATA_WIDTH);
	/* set Bit30 and 29 - which will prevent Target पातs from being
	 * issued upon HPI or GP error
	 */
	ioग_लिखो32(0x60000000, phw->dw2040_HPICSR + INTERRUPT_MASK_SET);

	/* isolate DSP HAD8 line from PCI2040 so that
	 * Little endian can be set by pullup
	 */
	dw2040_reset = dw2040_reset & (~(endian << 3));
	ioग_लिखो32(dw2040_reset, phw->dw2040_HPICSR + HPI_RESET);

	phw->aकरो[0].c_dsp_rev = 'B';	/* revB */
	phw->aकरो[1].c_dsp_rev = 'B';	/* revB */

	/*Take both DSPs out of reset, setting HAD8 to the correct Endian */
	dw2040_reset = dw2040_reset & (~0x00000001);	/* start DSP 0 */
	ioग_लिखो32(dw2040_reset, phw->dw2040_HPICSR + HPI_RESET);
	dw2040_reset = dw2040_reset & (~0x00000002);	/* start DSP 1 */
	ioग_लिखो32(dw2040_reset, phw->dw2040_HPICSR + HPI_RESET);

	/* set HAD8 back to PCI2040, now that DSP set to little endian mode */
	dw2040_reset = dw2040_reset & (~0x00000008);
	ioग_लिखो32(dw2040_reset, phw->dw2040_HPICSR + HPI_RESET);
	/*delay to allow DSP to get going */
	hpios_delay_micro_seconds(100);

	/* loop through all DSPs, करोwnloading DSP code */
	क्रम (dsp_index = 0; dsp_index < phw->num_dsp; dsp_index++) अणु
		काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];

		/* configure DSP so that we करोwnload code पूर्णांकo the SRAM */
		/* set control reg क्रम little endian, HWOB=1 */
		ioग_लिखो32(0x00010001, pकरो->prHPI_control);

		/* test access to the HPI address रेजिस्टर (HPIA) */
		test_data = 0x00000001;
		क्रम (j = 0; j < 32; j++) अणु
			ioग_लिखो32(test_data, pकरो->prHPI_address);
			data = ioपढ़ो32(pकरो->prHPI_address);
			अगर (data != test_data) अणु
				HPI_DEBUG_LOG(ERROR, "INIT_DSPHPI %x %x %x\n",
					test_data, data, dsp_index);
				वापस HPI6000_ERROR_INIT_DSPHPI;
			पूर्ण
			test_data = test_data << 1;
		पूर्ण

/* अगर C6713 the setup PLL to generate 225MHz from 25MHz.
* Since the PLLDIV1 पढ़ो is someबार wrong, even on a C6713,
* we're going to करो this unconditionally
*/
/* PLLDIV1 should have a value of 8000 after reset */
/*
	अगर (HpiReadWord(pकरो,0x01B7C118) == 0x8000)
*/
		अणु
			/* C6713 datasheet says we cannot program PLL from HPI,
			 * and indeed अगर we try to set the PLL multiply from the
			 * HPI, the PLL करोes not seem to lock,
			 * so we enable the PLL and use the शेष of x 7
			 */
			/* bypass PLL */
			hpi_ग_लिखो_word(pकरो, 0x01B7C100, 0x0000);
			hpios_delay_micro_seconds(100);

			/*  ** use शेष of PLL  x7 ** */
			/* EMIF = 225/3=75MHz */
			hpi_ग_लिखो_word(pकरो, 0x01B7C120, 0x8002);
			hpios_delay_micro_seconds(100);

			/* peri = 225/2 */
			hpi_ग_लिखो_word(pकरो, 0x01B7C11C, 0x8001);
			hpios_delay_micro_seconds(100);

			/* cpu  = 225/1 */
			hpi_ग_लिखो_word(pकरो, 0x01B7C118, 0x8000);

			/* ~2ms delay */
			hpios_delay_micro_seconds(2000);

			/* PLL not bypassed */
			hpi_ग_लिखो_word(pकरो, 0x01B7C100, 0x0001);
			/* ~2ms delay */
			hpios_delay_micro_seconds(2000);
		पूर्ण

		/* test r/w to पूर्णांकernal DSP memory
		 * C6711 has L2 cache mapped to 0x0 when reset
		 *
		 *  revB - because of bug 3.0.1 last HPI पढ़ो
		 * (beक्रमe HPI address issued) must be non-स्वतःinc
		 */
		/* test each bit in the 32bit word */
		क्रम (i = 0; i < 100; i++) अणु
			test_addr = 0x00000000;
			test_data = 0x00000001;
			क्रम (j = 0; j < 32; j++) अणु
				hpi_ग_लिखो_word(pकरो, test_addr + i, test_data);
				data = hpi_पढ़ो_word(pकरो, test_addr + i);
				अगर (data != test_data) अणु
					HPI_DEBUG_LOG(ERROR,
						"DSP mem %x %x %x %x\n",
						test_addr + i, test_data,
						data, dsp_index);

					वापस HPI6000_ERROR_INIT_DSPINTMEM;
				पूर्ण
				test_data = test_data << 1;
			पूर्ण
		पूर्ण

		/* memory map of ASI6200
		   00000000-0000FFFF    16Kx32 पूर्णांकernal program
		   01800000-019FFFFF    Internal peripheral
		   80000000-807FFFFF    CE0 2Mx32 SDRAM running @ 100MHz
		   90000000-9000FFFF    CE1 Async peripherals:

		   EMIF config
		   ------------
		   Global EMIF control
		   0 -
		   1 -
		   2 -
		   3 CLK2EN = 1   CLKOUT2 enabled
		   4 CLK1EN = 0   CLKOUT1 disabled
		   5 EKEN = 1 <--!! C6713 specअगरic, enables ECLKOUT
		   6 -
		   7 NOHOLD = 1   बाह्यal HOLD disabled
		   8 HOLDA = 0    HOLDA output is low
		   9 HOLD = 0             HOLD input is low
		   10 ARDY = 1    ARDY input is high
		   11 BUSREQ = 0   BUSREQ output is low
		   12,13 Reserved = 1
		 */
		hpi_ग_लिखो_word(pकरो, 0x01800000, 0x34A8);

		/* EMIF CE0 setup - 2Mx32 Sync DRAM
		   31..28       Wr setup
		   27..22       Wr strobe
		   21..20       Wr hold
		   19..16       Rd setup
		   15..14       -
		   13..8        Rd strobe
		   7..4         MTYPE   0011            Sync DRAM 32bits
		   3            Wr hold MSB
		   2..0         Rd hold
		 */
		hpi_ग_लिखो_word(pकरो, 0x01800008, 0x00000030);

		/* EMIF SDRAM Extension
		   31-21        0
		   20           WR2RD = 0
		   19-18        WR2DEAC = 1
		   17           WR2WR = 0
		   16-15        R2WDQM = 2
		   14-12        RD2WR = 4
		   11-10        RD2DEAC = 1
		   9            RD2RD = 1
		   8-7          THZP = 10b
		   6-5          TWR  = 2-1 = 01b (tWR = 10ns)
		   4            TRRD = 0b = 2 ECLK (tRRD = 14ns)
		   3-1          TRAS = 5-1 = 100b (Tras=42ns = 5 ECLK)
		   1            CAS latency = 3 ECLK
		   (क्रम Micron 2M32-7 operating at 100Mhz)
		 */

		/* need to use this अन्यथा DSP code crashes */
		hpi_ग_लिखो_word(pकरो, 0x01800020, 0x001BDF29);

		/* EMIF SDRAM control - set up क्रम a 2Mx32 SDRAM (512x32x4 bank)
		   31           -               -
		   30           SDBSZ   1               4 bank
		   29..28       SDRSZ   00              11 row address pins
		   27..26       SDCSZ   01              8 column address pins
		   25           RFEN    1               refersh enabled
		   24           INIT    1               init SDRAM
		   23..20       TRCD    0001
		   19..16       TRP             0001
		   15..12       TRC             0110
		   11..0        -               -
		 */
		/*      need to use this अन्यथा DSP code crashes */
		hpi_ग_लिखो_word(pकरो, 0x01800018, 0x47117000);

		/* EMIF SDRAM Refresh Timing */
		hpi_ग_लिखो_word(pकरो, 0x0180001C, 0x00000410);

		/*MIF CE1 setup - Async peripherals
		   @100MHz bus speed, each cycle is 10ns,
		   31..28       Wr setup  = 1
		   27..22       Wr strobe = 3                   30ns
		   21..20       Wr hold = 1
		   19..16       Rd setup =1
		   15..14       Ta = 2
		   13..8        Rd strobe = 3                   30ns
		   7..4         MTYPE   0010            Async 32bits
		   3            Wr hold MSB =0
		   2..0         Rd hold = 1
		 */
		अणु
			u32 cE1 =
				(1L << 28) | (3L << 22) | (1L << 20) | (1L <<
				16) | (2L << 14) | (3L << 8) | (2L << 4) | 1L;
			hpi_ग_लिखो_word(pकरो, 0x01800004, cE1);
		पूर्ण

		/* delay a little to allow SDRAM and DSP to "get going" */
		hpios_delay_micro_seconds(1000);

		/* test access to SDRAM */
		अणु
			test_addr = 0x80000000;
			test_data = 0x00000001;
			/* test each bit in the 32bit word */
			क्रम (j = 0; j < 32; j++) अणु
				hpi_ग_लिखो_word(pकरो, test_addr, test_data);
				data = hpi_पढ़ो_word(pकरो, test_addr);
				अगर (data != test_data) अणु
					HPI_DEBUG_LOG(ERROR,
						"DSP dram %x %x %x %x\n",
						test_addr, test_data, data,
						dsp_index);

					वापस HPI6000_ERROR_INIT_SDRAM1;
				पूर्ण
				test_data = test_data << 1;
			पूर्ण
			/* test every Nth address in the DRAM */
#घोषणा DRAM_SIZE_WORDS 0x200000	/*2_mx32 */
#घोषणा DRAM_INC 1024
			test_addr = 0x80000000;
			test_data = 0x0;
			क्रम (i = 0; i < DRAM_SIZE_WORDS; i = i + DRAM_INC) अणु
				hpi_ग_लिखो_word(pकरो, test_addr + i, test_data);
				test_data++;
			पूर्ण
			test_addr = 0x80000000;
			test_data = 0x0;
			क्रम (i = 0; i < DRAM_SIZE_WORDS; i = i + DRAM_INC) अणु
				data = hpi_पढ़ो_word(pकरो, test_addr + i);
				अगर (data != test_data) अणु
					HPI_DEBUG_LOG(ERROR,
						"DSP dram %x %x %x %x\n",
						test_addr + i, test_data,
						data, dsp_index);
					वापस HPI6000_ERROR_INIT_SDRAM2;
				पूर्ण
				test_data++;
			पूर्ण

		पूर्ण

		/* ग_लिखो the DSP code करोwn पूर्णांकo the DSPs memory */
		error = hpi_dsp_code_खोलो(boot_load_family, pao->pci.pci_dev,
			&dsp_code, pos_error_code);

		अगर (error)
			वापस error;

		जबतक (1) अणु
			u32 length;
			u32 address;
			u32 type;
			u32 *pcode;

			error = hpi_dsp_code_पढ़ो_word(&dsp_code, &length);
			अगर (error)
				अवरोध;
			अगर (length == 0xFFFFFFFF)
				अवरोध;	/* end of code */

			error = hpi_dsp_code_पढ़ो_word(&dsp_code, &address);
			अगर (error)
				अवरोध;
			error = hpi_dsp_code_पढ़ो_word(&dsp_code, &type);
			अगर (error)
				अवरोध;
			error = hpi_dsp_code_पढ़ो_block(length, &dsp_code,
				&pcode);
			अगर (error)
				अवरोध;
			error = hpi6000_dsp_block_ग_लिखो32(pao, (u16)dsp_index,
				address, pcode, length);
			अगर (error)
				अवरोध;
		पूर्ण

		अगर (error) अणु
			hpi_dsp_code_बंद(&dsp_code);
			वापस error;
		पूर्ण
		/* verअगरy that code was written correctly */
		/* this समय through, assume no errors in DSP code file/array */
		hpi_dsp_code_शुरुआत(&dsp_code);
		जबतक (1) अणु
			u32 length;
			u32 address;
			u32 type;
			u32 *pcode;

			hpi_dsp_code_पढ़ो_word(&dsp_code, &length);
			अगर (length == 0xFFFFFFFF)
				अवरोध;	/* end of code */

			hpi_dsp_code_पढ़ो_word(&dsp_code, &address);
			hpi_dsp_code_पढ़ो_word(&dsp_code, &type);
			hpi_dsp_code_पढ़ो_block(length, &dsp_code, &pcode);

			क्रम (i = 0; i < length; i++) अणु
				data = hpi_पढ़ो_word(pकरो, address);
				अगर (data != *pcode) अणु
					error = HPI6000_ERROR_INIT_VERIFY;
					HPI_DEBUG_LOG(ERROR,
						"DSP verify %x %x %x %x\n",
						address, *pcode, data,
						dsp_index);
					अवरोध;
				पूर्ण
				pcode++;
				address += 4;
			पूर्ण
			अगर (error)
				अवरोध;
		पूर्ण
		hpi_dsp_code_बंद(&dsp_code);
		अगर (error)
			वापस error;

		/* zero out the hosपंचांगailbox */
		अणु
			u32 address = HPI_HIF_ADDR(host_cmd);
			क्रम (i = 0; i < 4; i++) अणु
				hpi_ग_लिखो_word(pकरो, address, 0);
				address += 4;
			पूर्ण
		पूर्ण
		/* ग_लिखो the DSP number पूर्णांकo the hosपंचांगailbox */
		/* काष्ठाure beक्रमe starting the DSP */
		hpi_ग_लिखो_word(pकरो, HPI_HIF_ADDR(dsp_number), dsp_index);

		/* ग_लिखो the DSP adapter Info पूर्णांकo the */
		/* hosपंचांगailbox beक्रमe starting the DSP */
		अगर (dsp_index > 0)
			hpi_ग_लिखो_word(pकरो, HPI_HIF_ADDR(adapter_info),
				adapter_info);

		/* step 3. Start code by sending पूर्णांकerrupt */
		ioग_लिखो32(0x00030003, pकरो->prHPI_control);
		hpios_delay_micro_seconds(10000);

		/* रुको क्रम a non-zero value in hostcmd -
		 * indicating initialization is complete
		 *
		 * Init could take a जबतक अगर DSP checks SDRAM memory
		 * Was 200000. Increased to 2000000 क्रम ASI8801 so we
		 * करोn't get 938 errors.
		 */
		समयout = 2000000;
		जबतक (समयout) अणु
			करो अणु
				पढ़ो = hpi_पढ़ो_word(pकरो,
					HPI_HIF_ADDR(host_cmd));
			पूर्ण जबतक (--समयout
				&& hpi6000_check_PCI2040_error_flag(pao,
					H6READ));

			अगर (पढ़ो)
				अवरोध;
			/* The following is a workaround क्रम bug #94:
			 * Bluescreen on install and subsequent boots on a
			 * DELL PowerEdge 600SC PC with 1.8GHz P4 and
			 * ServerWorks chipset. Without this delay the प्रणाली
			 * locks up with a bluescreen (NOT GPF or pagefault).
			 */
			अन्यथा
				hpios_delay_micro_seconds(10000);
		पूर्ण
		अगर (समयout == 0)
			वापस HPI6000_ERROR_INIT_NOACK;

		/* पढ़ो the DSP adapter Info from the */
		/* hosपंचांगailbox काष्ठाure after starting the DSP */
		अगर (dsp_index == 0) अणु
			/*u32 dwTestData=0; */
			u32 mask = 0;

			adapter_info =
				hpi_पढ़ो_word(pकरो,
				HPI_HIF_ADDR(adapter_info));
			अगर (HPI_ADAPTER_FAMILY_ASI
				(HPI_HIF_ADAPTER_INFO_EXTRACT_ADAPTER
					(adapter_info)) ==
				HPI_ADAPTER_FAMILY_ASI(0x6200))
				/* all 6200 cards have this many DSPs */
				phw->num_dsp = 2;

			/* test that the PLD is programmed */
			/* and we can पढ़ो/ग_लिखो 24bits */
#घोषणा PLD_BASE_ADDRESS 0x90000000L	/*क्रम ASI6100/6200/8800 */

			चयन (boot_load_family) अणु
			हाल HPI_ADAPTER_FAMILY_ASI(0x6200):
				/* ASI6100/6200 has 24bit path to FPGA */
				mask = 0xFFFFFF00L;
				/* ASI5100 uses AX6 code, */
				/* but has no PLD r/w रेजिस्टर to test */
				अगर (HPI_ADAPTER_FAMILY_ASI(pao->pci.pci_dev->
						subप्रणाली_device) ==
					HPI_ADAPTER_FAMILY_ASI(0x5100))
					mask = 0x00000000L;
				/* ASI5200 uses AX6 code, */
				/* but has no PLD r/w रेजिस्टर to test */
				अगर (HPI_ADAPTER_FAMILY_ASI(pao->pci.pci_dev->
						subप्रणाली_device) ==
					HPI_ADAPTER_FAMILY_ASI(0x5200))
					mask = 0x00000000L;
				अवरोध;
			हाल HPI_ADAPTER_FAMILY_ASI(0x8800):
				/* ASI8800 has 16bit path to FPGA */
				mask = 0xFFFF0000L;
				अवरोध;
			पूर्ण
			test_data = 0xAAAAAA00L & mask;
			/* ग_लिखो to 24 bit Debug रेजिस्टर (D31-D8) */
			hpi_ग_लिखो_word(pकरो, PLD_BASE_ADDRESS + 4L, test_data);
			पढ़ो = hpi_पढ़ो_word(pकरो,
				PLD_BASE_ADDRESS + 4L) & mask;
			अगर (पढ़ो != test_data) अणु
				HPI_DEBUG_LOG(ERROR, "PLD %x %x\n", test_data,
					पढ़ो);
				वापस HPI6000_ERROR_INIT_PLDTEST1;
			पूर्ण
			test_data = 0x55555500L & mask;
			hpi_ग_लिखो_word(pकरो, PLD_BASE_ADDRESS + 4L, test_data);
			पढ़ो = hpi_पढ़ो_word(pकरो,
				PLD_BASE_ADDRESS + 4L) & mask;
			अगर (पढ़ो != test_data) अणु
				HPI_DEBUG_LOG(ERROR, "PLD %x %x\n", test_data,
					पढ़ो);
				वापस HPI6000_ERROR_INIT_PLDTEST2;
			पूर्ण
		पूर्ण
	पूर्ण	/* क्रम numDSP */
	वापस 0;
पूर्ण

#घोषणा PCI_TIMEOUT 100

अटल पूर्णांक hpi_set_address(काष्ठा dsp_obj *pकरो, u32 address)
अणु
	u32 समयout = PCI_TIMEOUT;

	करो अणु
		ioग_लिखो32(address, pकरो->prHPI_address);
	पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pकरो->pa_parent_adapter,
			H6WRITE)
		&& --समयout);

	अगर (समयout)
		वापस 0;

	वापस 1;
पूर्ण

/* ग_लिखो one word to the HPI port */
अटल व्योम hpi_ग_लिखो_word(काष्ठा dsp_obj *pकरो, u32 address, u32 data)
अणु
	अगर (hpi_set_address(pकरो, address))
		वापस;
	ioग_लिखो32(data, pकरो->prHPI_data);
पूर्ण

/* पढ़ो one word from the HPI port */
अटल u32 hpi_पढ़ो_word(काष्ठा dsp_obj *pकरो, u32 address)
अणु
	u32 data = 0;

	अगर (hpi_set_address(pकरो, address))
		वापस 0;	/*? No way to वापस error */

	/* take care of errata in revB DSP (2.0.1) */
	data = ioपढ़ो32(pकरो->prHPI_data);
	वापस data;
पूर्ण

/* ग_लिखो a block of 32bit words to the DSP HPI port using स्वतः-inc mode */
अटल व्योम hpi_ग_लिखो_block(काष्ठा dsp_obj *pकरो, u32 address, u32 *pdata,
	u32 length)
अणु
	u16 length16 = length - 1;

	अगर (length == 0)
		वापस;

	अगर (hpi_set_address(pकरो, address))
		वापस;

	ioग_लिखो32_rep(pकरो->prHPI_data_स्वतः_inc, pdata, length16);

	/* take care of errata in revB DSP (2.0.1) */
	/* must end with non स्वतः-inc */
	ioग_लिखो32(*(pdata + length - 1), pकरो->prHPI_data);
पूर्ण

/** पढ़ो a block of 32bit words from the DSP HPI port using स्वतः-inc mode
 */
अटल व्योम hpi_पढ़ो_block(काष्ठा dsp_obj *pकरो, u32 address, u32 *pdata,
	u32 length)
अणु
	u16 length16 = length - 1;

	अगर (length == 0)
		वापस;

	अगर (hpi_set_address(pकरो, address))
		वापस;

	ioपढ़ो32_rep(pकरो->prHPI_data_स्वतः_inc, pdata, length16);

	/* take care of errata in revB DSP (2.0.1) */
	/* must end with non स्वतः-inc */
	*(pdata + length - 1) = ioपढ़ो32(pकरो->prHPI_data);
पूर्ण

अटल u16 hpi6000_dsp_block_ग_लिखो32(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 hpi_address, u32 *source, u32 count)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 समय_out = PCI_TIMEOUT;
	पूर्णांक c6711_burst_size = 128;
	u32 local_hpi_address = hpi_address;
	पूर्णांक local_count = count;
	पूर्णांक xfer_size;
	u32 *pdata = source;

	जबतक (local_count) अणु
		अगर (local_count > c6711_burst_size)
			xfer_size = c6711_burst_size;
		अन्यथा
			xfer_size = local_count;

		समय_out = PCI_TIMEOUT;
		करो अणु
			hpi_ग_लिखो_block(pकरो, local_hpi_address, pdata,
				xfer_size);
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6WRITE)
			&& --समय_out);

		अगर (!समय_out)
			अवरोध;
		pdata += xfer_size;
		local_hpi_address += माप(u32) * xfer_size;
		local_count -= xfer_size;
	पूर्ण

	अगर (समय_out)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल u16 hpi6000_dsp_block_पढ़ो32(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 hpi_address, u32 *dest, u32 count)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 समय_out = PCI_TIMEOUT;
	पूर्णांक c6711_burst_size = 16;
	u32 local_hpi_address = hpi_address;
	पूर्णांक local_count = count;
	पूर्णांक xfer_size;
	u32 *pdata = dest;
	u32 loop_count = 0;

	जबतक (local_count) अणु
		अगर (local_count > c6711_burst_size)
			xfer_size = c6711_burst_size;
		अन्यथा
			xfer_size = local_count;

		समय_out = PCI_TIMEOUT;
		करो अणु
			hpi_पढ़ो_block(pकरो, local_hpi_address, pdata,
				xfer_size);
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --समय_out);
		अगर (!समय_out)
			अवरोध;

		pdata += xfer_size;
		local_hpi_address += माप(u32) * xfer_size;
		local_count -= xfer_size;
		loop_count++;
	पूर्ण

	अगर (समय_out)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

अटल लघु hpi6000_message_response_sequence(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 समयout;
	u16 ack;
	u32 address;
	u32 length;
	u32 *p_data;
	u16 error = 0;

	ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_IDLE);
	अगर (ack & HPI_HIF_ERROR_MASK) अणु
		pao->dsp_crashed++;
		वापस HPI6000_ERROR_MSG_RESP_IDLE_TIMEOUT;
	पूर्ण
	pao->dsp_crashed = 0;

	/* get the message address and size */
	अगर (phw->message_buffer_address_on_dsp == 0) अणु
		समयout = TIMEOUT;
		करो अणु
			address =
				hpi_पढ़ो_word(pकरो,
				HPI_HIF_ADDR(message_buffer_address));
			phw->message_buffer_address_on_dsp = address;
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --समयout);
		अगर (!समयout)
			वापस HPI6000_ERROR_MSG_GET_ADR;
	पूर्ण अन्यथा
		address = phw->message_buffer_address_on_dsp;

	length = phm->size;

	/* send the message */
	p_data = (u32 *)phm;
	अगर (hpi6000_dsp_block_ग_लिखो32(pao, dsp_index, address, p_data,
			(u16)length / 4))
		वापस HPI6000_ERROR_MSG_RESP_BLOCKWRITE32;

	अगर (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_GET_RESP))
		वापस HPI6000_ERROR_MSG_RESP_GETRESPCMD;
	hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

	ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_GET_RESP);
	अगर (ack & HPI_HIF_ERROR_MASK)
		वापस HPI6000_ERROR_MSG_RESP_GET_RESP_ACK;

	/* get the response address */
	अगर (phw->response_buffer_address_on_dsp == 0) अणु
		समयout = TIMEOUT;
		करो अणु
			address =
				hpi_पढ़ो_word(pकरो,
				HPI_HIF_ADDR(response_buffer_address));
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ)
			&& --समयout);
		phw->response_buffer_address_on_dsp = address;

		अगर (!समयout)
			वापस HPI6000_ERROR_RESP_GET_ADR;
	पूर्ण अन्यथा
		address = phw->response_buffer_address_on_dsp;

	/* पढ़ो the length of the response back from the DSP */
	समयout = TIMEOUT;
	करो अणु
		length = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(length));
	पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ) && --समयout);
	अगर (!समयout)
		वापस HPI6000_ERROR_RESP_GET_LEN;

	अगर (length > phr->size)
		वापस HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;

	/* get the response */
	p_data = (u32 *)phr;
	अगर (hpi6000_dsp_block_पढ़ो32(pao, dsp_index, address, p_data,
			(u16)length / 4))
		वापस HPI6000_ERROR_MSG_RESP_BLOCKREAD32;

	/* set i/f back to idle */
	अगर (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDLE))
		वापस HPI6000_ERROR_MSG_RESP_IDLECMD;
	hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

	error = hpi_validate_response(phm, phr);
	वापस error;
पूर्ण

/* have to set up the below defines to match stuff in the MAP file */

#घोषणा MSG_ADDRESS (HPI_HIF_BASE+0x18)
#घोषणा MSG_LENGTH 11
#घोषणा RESP_ADDRESS (HPI_HIF_BASE+0x44)
#घोषणा RESP_LENGTH 16
#घोषणा QUEUE_START  (HPI_HIF_BASE+0x88)
#घोषणा QUEUE_SIZE 0x8000

अटल लघु hpi6000_send_data_check_adr(u32 address, u32 length_in_dwords)
अणु
/*#घोषणा CHECKING       // comment this line in to enable checking */
#अगर_घोषित CHECKING
	अगर (address < (u32)MSG_ADDRESS)
		वापस 0;
	अगर (address > (u32)(QUEUE_START + QUEUE_SIZE))
		वापस 0;
	अगर ((address + (length_in_dwords << 2)) >
		(u32)(QUEUE_START + QUEUE_SIZE))
		वापस 0;
#अन्यथा
	(व्योम)address;
	(व्योम)length_in_dwords;
	वापस 1;
#पूर्ण_अगर
पूर्ण

अटल लघु hpi6000_send_data(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 data_sent = 0;
	u16 ack;
	u32 length, address;
	u32 *p_data = (u32 *)phm->u.d.u.data.pb_data;
	u16 समय_out = 8;

	(व्योम)phr;

	/* round dwDataSize करोwn to nearest 4 bytes */
	जबतक ((data_sent < (phm->u.d.u.data.data_size & ~3L))
		&& --समय_out) अणु
		ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_IDLE);
		अगर (ack & HPI_HIF_ERROR_MASK)
			वापस HPI6000_ERROR_SEND_DATA_IDLE_TIMEOUT;

		अगर (hpi6000_send_host_command(pao, dsp_index,
				HPI_HIF_SEND_DATA))
			वापस HPI6000_ERROR_SEND_DATA_CMD;

		hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

		ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_SEND_DATA);

		अगर (ack & HPI_HIF_ERROR_MASK)
			वापस HPI6000_ERROR_SEND_DATA_ACK;

		करो अणु
			/* get the address and size */
			address = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(address));
			/* DSP वापसs number of DWORDS */
			length = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(length));
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ));

		अगर (!hpi6000_send_data_check_adr(address, length))
			वापस HPI6000_ERROR_SEND_DATA_ADR;

		/* send the data. अवरोध data पूर्णांकo 512 DWORD blocks (2K bytes)
		 * and send using block ग_लिखो. 2Kbytes is the max as this is the
		 * memory winकरोw given to the HPI data रेजिस्टर by the PCI2040
		 */

		अणु
			u32 len = length;
			u32 blk_len = 512;
			जबतक (len) अणु
				अगर (len < blk_len)
					blk_len = len;
				अगर (hpi6000_dsp_block_ग_लिखो32(pao, dsp_index,
						address, p_data, blk_len))
					वापस HPI6000_ERROR_SEND_DATA_WRITE;
				address += blk_len * 4;
				p_data += blk_len;
				len -= blk_len;
			पूर्ण
		पूर्ण

		अगर (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDLE))
			वापस HPI6000_ERROR_SEND_DATA_IDLECMD;

		hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

		data_sent += length * 4;
	पूर्ण
	अगर (!समय_out)
		वापस HPI6000_ERROR_SEND_DATA_TIMEOUT;
	वापस 0;
पूर्ण

अटल लघु hpi6000_get_data(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 data_got = 0;
	u16 ack;
	u32 length, address;
	u32 *p_data = (u32 *)phm->u.d.u.data.pb_data;

	(व्योम)phr;	/* this parameter not used! */

	/* round dwDataSize करोwn to nearest 4 bytes */
	जबतक (data_got < (phm->u.d.u.data.data_size & ~3L)) अणु
		ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_IDLE);
		अगर (ack & HPI_HIF_ERROR_MASK)
			वापस HPI6000_ERROR_GET_DATA_IDLE_TIMEOUT;

		अगर (hpi6000_send_host_command(pao, dsp_index,
				HPI_HIF_GET_DATA))
			वापस HPI6000_ERROR_GET_DATA_CMD;
		hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

		ack = hpi6000_रुको_dsp_ack(pao, dsp_index, HPI_HIF_GET_DATA);

		अगर (ack & HPI_HIF_ERROR_MASK)
			वापस HPI6000_ERROR_GET_DATA_ACK;

		/* get the address and size */
		करो अणु
			address = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(address));
			length = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(length));
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ));

		/* पढ़ो the data */
		अणु
			u32 len = length;
			u32 blk_len = 512;
			जबतक (len) अणु
				अगर (len < blk_len)
					blk_len = len;
				अगर (hpi6000_dsp_block_पढ़ो32(pao, dsp_index,
						address, p_data, blk_len))
					वापस HPI6000_ERROR_GET_DATA_READ;
				address += blk_len * 4;
				p_data += blk_len;
				len -= blk_len;
			पूर्ण
		पूर्ण

		अगर (hpi6000_send_host_command(pao, dsp_index, HPI_HIF_IDLE))
			वापस HPI6000_ERROR_GET_DATA_IDLECMD;
		hpi6000_send_dsp_पूर्णांकerrupt(pकरो);

		data_got += length * 4;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hpi6000_send_dsp_पूर्णांकerrupt(काष्ठा dsp_obj *pकरो)
अणु
	ioग_लिखो32(0x00030003, pकरो->prHPI_control);	/* DSPINT */
पूर्ण

अटल लघु hpi6000_send_host_command(काष्ठा hpi_adapter_obj *pao,
	u16 dsp_index, u32 host_cmd)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 समयout = TIMEOUT;

	/* set command */
	करो अणु
		hpi_ग_लिखो_word(pकरो, HPI_HIF_ADDR(host_cmd), host_cmd);
		/* flush the FIFO */
		hpi_set_address(pकरो, HPI_HIF_ADDR(host_cmd));
	पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6WRITE) && --समयout);

	/* reset the पूर्णांकerrupt bit */
	ioग_लिखो32(0x00040004, pकरो->prHPI_control);

	अगर (समयout)
		वापस 0;
	अन्यथा
		वापस 1;
पूर्ण

/* अगर the PCI2040 has recorded an HPI समयout, reset the error and वापस 1 */
अटल लघु hpi6000_check_PCI2040_error_flag(काष्ठा hpi_adapter_obj *pao,
	u16 पढ़ो_or_ग_लिखो)
अणु
	u32 hPI_error;

	काष्ठा hpi_hw_obj *phw = pao->priv;

	/* पढ़ो the error bits from the PCI2040 */
	hPI_error = ioपढ़ो32(phw->dw2040_HPICSR + HPI_ERROR_REPORT);
	अगर (hPI_error) अणु
		/* reset the error flag */
		ioग_लिखो32(0L, phw->dw2040_HPICSR + HPI_ERROR_REPORT);
		phw->pCI2040HPI_error_count++;
		अगर (पढ़ो_or_ग_लिखो == 1)
			gw_pci_पढ़ो_निश्चितs++;	   /************* inc global */
		अन्यथा
			gw_pci_ग_लिखो_निश्चितs++;
		वापस 1;
	पूर्ण अन्यथा
		वापस 0;
पूर्ण

अटल लघु hpi6000_रुको_dsp_ack(काष्ठा hpi_adapter_obj *pao, u16 dsp_index,
	u32 ack_value)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 ack = 0L;
	u32 समयout;
	u32 hPIC = 0L;

	/* रुको क्रम host पूर्णांकerrupt to संकेत ack is पढ़ोy */
	समयout = TIMEOUT;
	जबतक (--समयout) अणु
		hPIC = ioपढ़ो32(pकरो->prHPI_control);
		अगर (hPIC & 0x04)	/* 0x04 = HINT from DSP */
			अवरोध;
	पूर्ण
	अगर (समयout == 0)
		वापस HPI_HIF_ERROR_MASK;

	/* रुको क्रम dwAckValue */
	समयout = TIMEOUT;
	जबतक (--समयout) अणु
		/* पढ़ो the ack mailbox */
		ack = hpi_पढ़ो_word(pकरो, HPI_HIF_ADDR(dsp_ack));
		अगर (ack == ack_value)
			अवरोध;
		अगर ((ack & HPI_HIF_ERROR_MASK)
			&& !hpi6000_check_PCI2040_error_flag(pao, H6READ))
			अवरोध;
		/*क्रम (i=0;i<1000;i++) */
		/*      dwPause=i+1; */
	पूर्ण
	अगर (ack & HPI_HIF_ERROR_MASK)
		/* indicates bad पढ़ो from DSP -
		   typically 0xffffff is पढ़ो क्रम some reason */
		ack = HPI_HIF_ERROR_MASK;

	अगर (समयout == 0)
		ack = HPI_HIF_ERROR_MASK;
	वापस (लघु)ack;
पूर्ण

अटल लघु hpi6000_update_control_cache(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm)
अणु
	स्थिर u16 dsp_index = 0;
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_obj *pकरो = &phw->aकरो[dsp_index];
	u32 समयout;
	u32 cache_dirty_flag;
	u16 err;

	hpios_dsplock_lock(pao);

	समयout = TIMEOUT;
	करो अणु
		cache_dirty_flag =
			hpi_पढ़ो_word((काष्ठा dsp_obj *)pकरो,
			HPI_HIF_ADDR(control_cache_is_dirty));
	पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ) && --समयout);
	अगर (!समयout) अणु
		err = HPI6000_ERROR_CONTROL_CACHE_PARAMS;
		जाओ unlock;
	पूर्ण

	अगर (cache_dirty_flag) अणु
		/* पढ़ो the cached controls */
		u32 address;
		u32 length;

		समयout = TIMEOUT;
		अगर (pकरो->control_cache_address_on_dsp == 0) अणु
			करो अणु
				address =
					hpi_पढ़ो_word((काष्ठा dsp_obj *)pकरो,
					HPI_HIF_ADDR(control_cache_address));

				length = hpi_पढ़ो_word((काष्ठा dsp_obj *)pकरो,
					HPI_HIF_ADDR
					(control_cache_size_in_bytes));
			पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6READ)
				&& --समयout);
			अगर (!समयout) अणु
				err = HPI6000_ERROR_CONTROL_CACHE_ADDRLEN;
				जाओ unlock;
			पूर्ण
			pकरो->control_cache_address_on_dsp = address;
			pकरो->control_cache_length_on_dsp = length;
		पूर्ण अन्यथा अणु
			address = pकरो->control_cache_address_on_dsp;
			length = pकरो->control_cache_length_on_dsp;
		पूर्ण

		अगर (hpi6000_dsp_block_पढ़ो32(pao, dsp_index, address,
				(u32 *)&phw->control_cache[0],
				length / माप(u32))) अणु
			err = HPI6000_ERROR_CONTROL_CACHE_READ;
			जाओ unlock;
		पूर्ण
		करो अणु
			hpi_ग_लिखो_word((काष्ठा dsp_obj *)pकरो,
				HPI_HIF_ADDR(control_cache_is_dirty), 0);
			/* flush the FIFO */
			hpi_set_address(pकरो, HPI_HIF_ADDR(host_cmd));
		पूर्ण जबतक (hpi6000_check_PCI2040_error_flag(pao, H6WRITE)
			&& --समयout);
		अगर (!समयout) अणु
			err = HPI6000_ERROR_CONTROL_CACHE_FLUSH;
			जाओ unlock;
		पूर्ण

	पूर्ण
	err = 0;

unlock:
	hpios_dsplock_unlock(pao);
	वापस err;
पूर्ण

/** Get dsp index क्रम multi DSP adapters only */
अटल u16 get_dsp_index(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm)
अणु
	u16 ret = 0;
	चयन (phm->object) अणु
	हाल HPI_OBJ_ISTREAM:
		अगर (phm->obj_index < 2)
			ret = 1;
		अवरोध;
	हाल HPI_OBJ_PROखाता:
		ret = phm->obj_index;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/** Complete transaction with DSP

Send message, get response, send or get stream data अगर any.
*/
अटल व्योम hw_message(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	u16 error = 0;
	u16 dsp_index = 0;
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u16 num_dsp = phw->num_dsp;

	अगर (num_dsp < 2)
		dsp_index = 0;
	अन्यथा अणु
		dsp_index = get_dsp_index(pao, phm);

		/* is this  checked on the DSP anyway? */
		अगर ((phm->function == HPI_ISTREAM_GROUP_ADD)
			|| (phm->function == HPI_OSTREAM_GROUP_ADD)) अणु
			काष्ठा hpi_message hm;
			u16 add_index;
			hm.obj_index = phm->u.d.u.stream.stream_index;
			hm.object = phm->u.d.u.stream.object_type;
			add_index = get_dsp_index(pao, &hm);
			अगर (add_index != dsp_index) अणु
				phr->error = HPI_ERROR_NO_INTERDSP_GROUPS;
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण

	hpios_dsplock_lock(pao);
	error = hpi6000_message_response_sequence(pao, dsp_index, phm, phr);

	अगर (error)	/* something failed in the HPI/DSP पूर्णांकerface */
		जाओ err;

	अगर (phr->error)	/* something failed in the DSP */
		जाओ out;

	चयन (phm->function) अणु
	हाल HPI_OSTREAM_WRITE:
	हाल HPI_ISTREAM_ANC_WRITE:
		error = hpi6000_send_data(pao, dsp_index, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_READ:
	हाल HPI_OSTREAM_ANC_READ:
		error = hpi6000_get_data(pao, dsp_index, phm, phr);
		अवरोध;
	हाल HPI_ADAPTER_GET_ASSERT:
		phr->u.ax.निश्चित.dsp_index = 0;	/* dsp 0 शेष */
		अगर (num_dsp == 2) अणु
			अगर (!phr->u.ax.निश्चित.count) अणु
				/* no निश्चित from dsp 0, check dsp 1 */
				error = hpi6000_message_response_sequence(pao,
					1, phm, phr);
				phr->u.ax.निश्चित.dsp_index = 1;
			पूर्ण
		पूर्ण
	पूर्ण

err:
	अगर (error) अणु
		अगर (error >= HPI_ERROR_BACKEND_BASE) अणु
			phr->error = HPI_ERROR_DSP_COMMUNICATION;
			phr->specअगरic_error = error;
		पूर्ण अन्यथा अणु
			phr->error = error;
		पूर्ण

		/* just the header of the response is valid */
		phr->size = माप(काष्ठा hpi_response_header);
	पूर्ण
out:
	hpios_dsplock_unlock(pao);
	वापस;
पूर्ण
