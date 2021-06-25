<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/******************************************************************************

    AudioScience HPI driver
    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


 Hardware Programming Interface (HPI) क्रम AudioScience
 ASI50xx, AS51xx, ASI6xxx, ASI87xx ASI89xx series adapters.
 These PCI and PCIe bus adapters are based on a
 TMS320C6205 PCI bus mastering DSP,
 and (except ASI50xx) TI TMS320C6xxx भग्नing poपूर्णांक DSP

 Exported function:
 व्योम HPI_6205(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)

(C) Copyright AudioScience Inc. 1998-2010
*******************************************************************************/
#घोषणा SOURCEखाता_NAME "hpi6205.c"

#समावेश "hpi_internal.h"
#समावेश "hpimsginit.h"
#समावेश "hpidebug.h"
#समावेश "hpi6205.h"
#समावेश "hpidspcd.h"
#समावेश "hpicmn.h"

/*****************************************************************************/
/* HPI6205 specअगरic error codes */
#घोषणा HPI6205_ERROR_BASE 1000	/* not actually used anywhere */

/* operational/messaging errors */
#घोषणा HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT     1015
#घोषणा HPI6205_ERROR_MSG_RESP_TIMEOUT          1016

/* initialization/bootload errors */
#घोषणा HPI6205_ERROR_6205_NO_IRQ       1002
#घोषणा HPI6205_ERROR_6205_INIT_FAILED  1003
#घोषणा HPI6205_ERROR_6205_REG          1006
#घोषणा HPI6205_ERROR_6205_DSPPAGE      1007
#घोषणा HPI6205_ERROR_C6713_HPIC        1009
#घोषणा HPI6205_ERROR_C6713_HPIA        1010
#घोषणा HPI6205_ERROR_C6713_PLL         1011
#घोषणा HPI6205_ERROR_DSP_INTMEM        1012
#घोषणा HPI6205_ERROR_DSP_EXTMEM        1013
#घोषणा HPI6205_ERROR_DSP_PLD           1014
#घोषणा HPI6205_ERROR_6205_EEPROM       1017
#घोषणा HPI6205_ERROR_DSP_EMIF1         1018
#घोषणा HPI6205_ERROR_DSP_EMIF2         1019
#घोषणा HPI6205_ERROR_DSP_EMIF3         1020
#घोषणा HPI6205_ERROR_DSP_EMIF4         1021

/*****************************************************************************/
/* क्रम C6205 PCI i/f */
/* Host Status Register (HSR) bitfields */
#घोषणा C6205_HSR_INTSRC        0x01
#घोषणा C6205_HSR_INTAVAL       0x02
#घोषणा C6205_HSR_INTAM         0x04
#घोषणा C6205_HSR_CFGERR        0x08
#घोषणा C6205_HSR_EEREAD        0x10
/* Host-to-DSP Control Register (HDCR) bitfields */
#घोषणा C6205_HDCR_WARMRESET    0x01
#घोषणा C6205_HDCR_DSPINT       0x02
#घोषणा C6205_HDCR_PCIBOOT      0x04
/* DSP Page Register (DSPP) bitfields, */
/* defines 4 Mbyte page that BAR0 poपूर्णांकs to */
#घोषणा C6205_DSPP_MAP1         0x400

/* BAR0 maps to prefetchable 4 Mbyte memory block set by DSPP.
 * BAR1 maps to non-prefetchable 8 Mbyte memory block
 * of DSP memory mapped रेजिस्टरs (starting at 0x01800000).
 * 0x01800000 is hardcoded in the PCI i/f, so that only the offset from this
 * needs to be added to the BAR1 base address set in the PCI config reg
 */
#घोषणा C6205_BAR1_PCI_IO_OFFSET (0x027FFF0L)
#घोषणा C6205_BAR1_HSR  (C6205_BAR1_PCI_IO_OFFSET)
#घोषणा C6205_BAR1_HDCR (C6205_BAR1_PCI_IO_OFFSET+4)
#घोषणा C6205_BAR1_DSPP (C6205_BAR1_PCI_IO_OFFSET+8)

/* used to control LED (revA) and reset C6713 (revB) */
#घोषणा C6205_BAR0_TIMER1_CTL (0x01980000L)

/* For first 6713 in CE1 space, using DA17,16,2 */
#घोषणा HPICL_ADDR      0x01400000L
#घोषणा HPICH_ADDR      0x01400004L
#घोषणा HPIAL_ADDR      0x01410000L
#घोषणा HPIAH_ADDR      0x01410004L
#घोषणा HPIDIL_ADDR     0x01420000L
#घोषणा HPIDIH_ADDR     0x01420004L
#घोषणा HPIDL_ADDR      0x01430000L
#घोषणा HPIDH_ADDR      0x01430004L

#घोषणा C6713_EMIF_GCTL         0x01800000
#घोषणा C6713_EMIF_CE1          0x01800004
#घोषणा C6713_EMIF_CE0          0x01800008
#घोषणा C6713_EMIF_CE2          0x01800010
#घोषणा C6713_EMIF_CE3          0x01800014
#घोषणा C6713_EMIF_SDRAMCTL     0x01800018
#घोषणा C6713_EMIF_SDRAMTIMING  0x0180001C
#घोषणा C6713_EMIF_SDRAMEXT     0x01800020

काष्ठा hpi_hw_obj अणु
	/* PCI रेजिस्टरs */
	__iomem u32 *prHSR;
	__iomem u32 *prHDCR;
	__iomem u32 *prDSPP;

	u32 dsp_page;

	काष्ठा consistent_dma_area h_locked_mem;
	काष्ठा bus_master_पूर्णांकerface *p_पूर्णांकerface_buffer;

	u16 flag_outstream_just_reset[HPI_MAX_STREAMS];
	/* a non-शून्य handle means there is an HPI allocated buffer */
	काष्ठा consistent_dma_area instream_host_buffers[HPI_MAX_STREAMS];
	काष्ठा consistent_dma_area outstream_host_buffers[HPI_MAX_STREAMS];
	/* non-zero size means a buffer exists, may be बाह्यal */
	u32 instream_host_buffer_size[HPI_MAX_STREAMS];
	u32 outstream_host_buffer_size[HPI_MAX_STREAMS];

	काष्ठा consistent_dma_area h_control_cache;
	काष्ठा hpi_control_cache *p_cache;
पूर्ण;

/*****************************************************************************/
/* local prototypes */

#घोषणा check_beक्रमe_bbm_copy(status, p_bbm_data, l_first_ग_लिखो, l_second_ग_लिखो)

अटल पूर्णांक रुको_dsp_ack(काष्ठा hpi_hw_obj *phw, पूर्णांक state, पूर्णांक समयout_us);

अटल व्योम send_dsp_command(काष्ठा hpi_hw_obj *phw, पूर्णांक cmd);

अटल u16 adapter_boot_load_dsp(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code);

अटल u16 message_response_sequence(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम hw_message(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr);

#घोषणा HPI6205_TIMEOUT 1000000

अटल व्योम subsys_create_adapter(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr);
अटल व्योम adapter_delete(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल u16 create_adapter_obj(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code);

अटल व्योम delete_adapter_obj(काष्ठा hpi_adapter_obj *pao);

अटल पूर्णांक adapter_irq_query_and_clear(काष्ठा hpi_adapter_obj *pao,
	u32 message);

अटल व्योम outstream_host_buffer_allocate(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_host_buffer_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_host_buffer_मुक्त(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);
अटल व्योम outstream_ग_लिखो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_start(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_खोलो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम outstream_reset(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_host_buffer_allocate(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_host_buffer_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_host_buffer_मुक्त(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_पढ़ो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल व्योम instream_start(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

अटल u32 boot_loader_पढ़ो_mem32(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index,
	u32 address);

अटल व्योम boot_loader_ग_लिखो_mem32(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index, u32 address, u32 data);

अटल u16 boot_loader_config_emअगर(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index);

अटल u16 boot_loader_test_memory(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index,
	u32 address, u32 length);

अटल u16 boot_loader_test_पूर्णांकernal_memory(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index);

अटल u16 boot_loader_test_बाह्यal_memory(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index);

अटल u16 boot_loader_test_pld(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index);

/*****************************************************************************/

अटल व्योम subsys_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
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
	u16 pending_cache_error = 0;

	चयन (phm->function) अणु
	हाल HPI_CONTROL_GET_STATE:
		अगर (pao->has_control_cache) अणु
			rmb();	/* make sure we see updates DMAed from DSP */
			अगर (hpi_check_control_cache(phw->p_cache, phm, phr)) अणु
				अवरोध;
			पूर्ण अन्यथा अगर (phm->u.c.attribute == HPI_METER_PEAK) अणु
				pending_cache_error =
					HPI_ERROR_CONTROL_CACHING;
			पूर्ण
		पूर्ण
		hw_message(pao, phm, phr);
		अगर (pending_cache_error && !phr->error)
			phr->error = pending_cache_error;
		अवरोध;
	हाल HPI_CONTROL_GET_INFO:
		hw_message(pao, phm, phr);
		अवरोध;
	हाल HPI_CONTROL_SET_STATE:
		hw_message(pao, phm, phr);
		अगर (pao->has_control_cache)
			hpi_cmn_control_cache_sync_to_msg(phw->p_cache, phm,
				phr);
		अवरोध;
	शेष:
		phr->error = HPI_ERROR_INVALID_FUNC;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम adapter_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	चयन (phm->function) अणु
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

	अगर (phm->obj_index >= HPI_MAX_STREAMS) अणु
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
		HPI_DEBUG_LOG(WARNING,
			"Message referencing invalid stream %d "
			"on adapter index %d\n", phm->obj_index,
			phm->adapter_index);
		वापस;
	पूर्ण

	चयन (phm->function) अणु
	हाल HPI_OSTREAM_WRITE:
		outstream_ग_लिखो(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_GET_INFO:
		outstream_get_info(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_HOSTBUFFER_ALLOC:
		outstream_host_buffer_allocate(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_HOSTBUFFER_GET_INFO:
		outstream_host_buffer_get_info(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_HOSTBUFFER_FREE:
		outstream_host_buffer_मुक्त(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_START:
		outstream_start(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_OPEN:
		outstream_खोलो(pao, phm, phr);
		अवरोध;
	हाल HPI_OSTREAM_RESET:
		outstream_reset(pao, phm, phr);
		अवरोध;
	शेष:
		hw_message(pao, phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम instream_message(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु

	अगर (phm->obj_index >= HPI_MAX_STREAMS) अणु
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
		HPI_DEBUG_LOG(WARNING,
			"Message referencing invalid stream %d "
			"on adapter index %d\n", phm->obj_index,
			phm->adapter_index);
		वापस;
	पूर्ण

	चयन (phm->function) अणु
	हाल HPI_ISTREAM_READ:
		instream_पढ़ो(pao, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_GET_INFO:
		instream_get_info(pao, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_HOSTBUFFER_ALLOC:
		instream_host_buffer_allocate(pao, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_HOSTBUFFER_GET_INFO:
		instream_host_buffer_get_info(pao, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_HOSTBUFFER_FREE:
		instream_host_buffer_मुक्त(pao, phm, phr);
		अवरोध;
	हाल HPI_ISTREAM_START:
		instream_start(pao, phm, phr);
		अवरोध;
	शेष:
		hw_message(pao, phm, phr);
		अवरोध;
	पूर्ण
पूर्ण

/*****************************************************************************/
/** Entry poपूर्णांक to this HPI backend
 * All calls to the HPI start here
 */
अटल
व्योम _HPI_6205(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	अगर (pao && (pao->dsp_crashed >= 10)
		&& (phm->function != HPI_ADAPTER_DEBUG_READ)) अणु
		/* allow last resort debug पढ़ो even after crash */
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_DSP_HARDWARE);
		HPI_DEBUG_LOG(WARNING, " %d,%d dsp crashed.\n", phm->object,
			phm->function);
		वापस;
	पूर्ण

	/* Init शेष response  */
	अगर (phm->function != HPI_SUBSYS_CREATE_ADAPTER)
		phr->error = HPI_ERROR_PROCESSING_MESSAGE;

	HPI_DEBUG_LOG(VERBOSE, "start of switch\n");
	चयन (phm->type) अणु
	हाल HPI_TYPE_REQUEST:
		चयन (phm->object) अणु
		हाल HPI_OBJ_SUBSYSTEM:
			subsys_message(pao, phm, phr);
			अवरोध;

		हाल HPI_OBJ_ADAPTER:
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

व्योम HPI_6205(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_adapter_obj *pao = शून्य;

	अगर (phm->object != HPI_OBJ_SUBSYSTEM) अणु
		/* normal messages must have valid adapter index */
		pao = hpi_find_adapter(phm->adapter_index);
	पूर्ण अन्यथा अणु
		/* subsys messages करोn't address an adapter */
		_HPI_6205(शून्य, phm, phr);
		वापस;
	पूर्ण

	अगर (pao)
		_HPI_6205(pao, phm, phr);
	अन्यथा
		hpi_init_response(phr, phm->object, phm->function,
			HPI_ERROR_BAD_ADAPTER_NUMBER);
पूर्ण

/*****************************************************************************/
/* SUBSYSTEM */

/** Create an adapter object and initialise it based on resource inक्रमmation
 * passed in in the message
 * *** NOTE - you cannot use this function AND the FindAdapters function at the
 * same समय, the application must use only one of them to get the adapters ***
 */
अटल व्योम subsys_create_adapter(काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु
	/* create temp adapter obj, because we करोn't know what index yet */
	काष्ठा hpi_adapter_obj ao;
	u32 os_error_code;
	u16 err;

	HPI_DEBUG_LOG(DEBUG, " subsys_create_adapter\n");

	स_रखो(&ao, 0, माप(ao));

	ao.priv = kzalloc(माप(काष्ठा hpi_hw_obj), GFP_KERNEL);
	अगर (!ao.priv) अणु
		HPI_DEBUG_LOG(ERROR, "can't get mem for adapter object\n");
		phr->error = HPI_ERROR_MEMORY_ALLOC;
		वापस;
	पूर्ण

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

	phr->u.s.adapter_type = ao.type;
	phr->u.s.adapter_index = ao.index;
	phr->error = 0;
पूर्ण

/** delete an adapter - required by WDM driver */
अटल व्योम adapter_delete(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw;

	अगर (!pao) अणु
		phr->error = HPI_ERROR_INVALID_OBJ_INDEX;
		वापस;
	पूर्ण
	phw = pao->priv;
	/* reset adapter h/w */
	/* Reset C6713 #1 */
	boot_loader_ग_लिखो_mem32(pao, 0, C6205_BAR0_TIMER1_CTL, 0);
	/* reset C6205 */
	ioग_लिखो32(C6205_HDCR_WARMRESET, phw->prHDCR);

	delete_adapter_obj(pao);
	hpi_delete_adapter(pao);
	phr->error = 0;
पूर्ण

/** Create adapter object
  allocate buffers, bootload DSPs, initialise control cache
*/
अटल u16 create_adapter_obj(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface;
	u32 phys_addr;
	पूर्णांक i;
	u16 err;

	/* init error reporting */
	pao->dsp_crashed = 0;

	क्रम (i = 0; i < HPI_MAX_STREAMS; i++)
		phw->flag_outstream_just_reset[i] = 1;

	/* The C6205 memory area 1 is 8Mbyte winकरोw पूर्णांकo DSP रेजिस्टरs */
	phw->prHSR =
		pao->pci.ap_mem_base[1] +
		C6205_BAR1_HSR / माप(*pao->pci.ap_mem_base[1]);
	phw->prHDCR =
		pao->pci.ap_mem_base[1] +
		C6205_BAR1_HDCR / माप(*pao->pci.ap_mem_base[1]);
	phw->prDSPP =
		pao->pci.ap_mem_base[1] +
		C6205_BAR1_DSPP / माप(*pao->pci.ap_mem_base[1]);

	pao->has_control_cache = 0;

	अगर (hpios_locked_mem_alloc(&phw->h_locked_mem,
			माप(काष्ठा bus_master_पूर्णांकerface),
			pao->pci.pci_dev))
		phw->p_पूर्णांकerface_buffer = शून्य;
	अन्यथा अगर (hpios_locked_mem_get_virt_addr(&phw->h_locked_mem,
			(व्योम *)&phw->p_पूर्णांकerface_buffer))
		phw->p_पूर्णांकerface_buffer = शून्य;

	HPI_DEBUG_LOG(DEBUG, "interface buffer address %p\n",
		phw->p_पूर्णांकerface_buffer);

	अगर (phw->p_पूर्णांकerface_buffer) अणु
		स_रखो((व्योम *)phw->p_पूर्णांकerface_buffer, 0,
			माप(काष्ठा bus_master_पूर्णांकerface));
		phw->p_पूर्णांकerface_buffer->dsp_ack = H620_HIF_UNKNOWN;
	पूर्ण

	err = adapter_boot_load_dsp(pao, pos_error_code);
	अगर (err) अणु
		HPI_DEBUG_LOG(ERROR, "DSP code load failed\n");
		/* no need to clean up as SubSysCreateAdapter */
		/* calls DeleteAdapter on error. */
		वापस err;
	पूर्ण
	HPI_DEBUG_LOG(INFO, "load DSP code OK\n");

	/* allow boot load even अगर mem alloc wont work */
	अगर (!phw->p_पूर्णांकerface_buffer)
		वापस HPI_ERROR_MEMORY_ALLOC;

	पूर्णांकerface = phw->p_पूर्णांकerface_buffer;

	/* make sure the DSP has started ok */
	अगर (!रुको_dsp_ack(phw, H620_HIF_RESET, HPI6205_TIMEOUT * 10)) अणु
		HPI_DEBUG_LOG(ERROR, "timed out waiting reset state \n");
		वापस HPI6205_ERROR_6205_INIT_FAILED;
	पूर्ण
	/* Note that *pao, *phw are zeroed after allocation,
	 * so poपूर्णांकers and flags are शून्य by शेष.
	 * Allocate bus mastering control cache buffer and tell the DSP about it
	 */
	अगर (पूर्णांकerface->control_cache.number_of_controls) अणु
		u8 *p_control_cache_भव;

		err = hpios_locked_mem_alloc(&phw->h_control_cache,
			पूर्णांकerface->control_cache.size_in_bytes,
			pao->pci.pci_dev);
		अगर (!err)
			err = hpios_locked_mem_get_virt_addr(&phw->
				h_control_cache,
				(व्योम *)&p_control_cache_भव);
		अगर (!err) अणु
			स_रखो(p_control_cache_भव, 0,
				पूर्णांकerface->control_cache.size_in_bytes);

			phw->p_cache =
				hpi_alloc_control_cache(पूर्णांकerface->
				control_cache.number_of_controls,
				पूर्णांकerface->control_cache.size_in_bytes,
				p_control_cache_भव);

			अगर (!phw->p_cache)
				err = HPI_ERROR_MEMORY_ALLOC;
		पूर्ण
		अगर (!err) अणु
			err = hpios_locked_mem_get_phys_addr(&phw->
				h_control_cache, &phys_addr);
			पूर्णांकerface->control_cache.physical_address32 =
				phys_addr;
		पूर्ण

		अगर (!err)
			pao->has_control_cache = 1;
		अन्यथा अणु
			अगर (hpios_locked_mem_valid(&phw->h_control_cache))
				hpios_locked_mem_मुक्त(&phw->h_control_cache);
			pao->has_control_cache = 0;
		पूर्ण
	पूर्ण
	send_dsp_command(phw, H620_HIF_IDLE);

	अणु
		काष्ठा hpi_message hm;
		काष्ठा hpi_response hr;

		HPI_DEBUG_LOG(VERBOSE, "init ADAPTER_GET_INFO\n");
		स_रखो(&hm, 0, माप(hm));
		/* wAdapterIndex == version == 0 */
		hm.type = HPI_TYPE_REQUEST;
		hm.size = माप(hm);
		hm.object = HPI_OBJ_ADAPTER;
		hm.function = HPI_ADAPTER_GET_INFO;

		स_रखो(&hr, 0, माप(hr));
		hr.size = माप(hr);

		err = message_response_sequence(pao, &hm, &hr);
		अगर (err) अणु
			HPI_DEBUG_LOG(ERROR, "message transport error %d\n",
				err);
			वापस err;
		पूर्ण
		अगर (hr.error)
			वापस hr.error;

		pao->type = hr.u.ax.info.adapter_type;
		pao->index = hr.u.ax.info.adapter_index;

		HPI_DEBUG_LOG(VERBOSE,
			"got adapter info type %x index %d serial %d\n",
			hr.u.ax.info.adapter_type, hr.u.ax.info.adapter_index,
			hr.u.ax.info.serial_number);
	पूर्ण

	अगर (phw->p_cache)
		phw->p_cache->adap_idx = pao->index;

	HPI_DEBUG_LOG(INFO, "bootload DSP OK\n");

	pao->irq_query_and_clear = adapter_irq_query_and_clear;
	pao->instream_host_buffer_status =
		phw->p_पूर्णांकerface_buffer->instream_host_buffer_status;
	pao->outstream_host_buffer_status =
		phw->p_पूर्णांकerface_buffer->outstream_host_buffer_status;

	वापस hpi_add_adapter(pao);
पूर्ण

/** Free memory areas allocated by adapter
 * this routine is called from AdapterDelete,
  * and SubSysCreateAdapter अगर duplicate index
*/
अटल व्योम delete_adapter_obj(काष्ठा hpi_adapter_obj *pao)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	पूर्णांक i;

	अगर (hpios_locked_mem_valid(&phw->h_control_cache)) अणु
		hpios_locked_mem_मुक्त(&phw->h_control_cache);
		hpi_मुक्त_control_cache(phw->p_cache);
	पूर्ण

	अगर (hpios_locked_mem_valid(&phw->h_locked_mem)) अणु
		hpios_locked_mem_मुक्त(&phw->h_locked_mem);
		phw->p_पूर्णांकerface_buffer = शून्य;
	पूर्ण

	क्रम (i = 0; i < HPI_MAX_STREAMS; i++)
		अगर (hpios_locked_mem_valid(&phw->instream_host_buffers[i])) अणु
			hpios_locked_mem_मुक्त(&phw->instream_host_buffers[i]);
			/*?phw->InStreamHostBuffers[i] = शून्य; */
			phw->instream_host_buffer_size[i] = 0;
		पूर्ण

	क्रम (i = 0; i < HPI_MAX_STREAMS; i++)
		अगर (hpios_locked_mem_valid(&phw->outstream_host_buffers[i])) अणु
			hpios_locked_mem_मुक्त(&phw->outstream_host_buffers
				[i]);
			phw->outstream_host_buffer_size[i] = 0;
		पूर्ण
	kमुक्त(phw);
पूर्ण

/*****************************************************************************/
/* Adapter functions */
अटल पूर्णांक adapter_irq_query_and_clear(काष्ठा hpi_adapter_obj *pao,
	u32 message)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u32 hsr = 0;

	hsr = ioपढ़ो32(phw->prHSR);
	अगर (hsr & C6205_HSR_INTSRC) अणु
		/* reset the पूर्णांकerrupt from the DSP */
		ioग_लिखो32(C6205_HSR_INTSRC, phw->prHSR);
		वापस HPI_IRQ_MIXER;
	पूर्ण

	वापस HPI_IRQ_NONE;
पूर्ण

/*****************************************************************************/
/* OutStream Host buffer functions */

/** Allocate or attach buffer क्रम busmastering
*/
अटल व्योम outstream_host_buffer_allocate(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	u16 err = 0;
	u32 command = phm->u.d.u.buffer.command;
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;

	hpi_init_response(phr, phm->object, phm->function, 0);

	अगर (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_ALLOC) अणु
		/* ALLOC phase, allocate a buffer with घातer of 2 size,
		   get its bus address क्रम PCI bus mastering
		 */
		phm->u.d.u.buffer.buffer_size =
			roundup_घात_of_two(phm->u.d.u.buffer.buffer_size);
		/* वापस old size and allocated size,
		   so caller can detect change */
		phr->u.d.u.stream_info.data_available =
			phw->outstream_host_buffer_size[phm->obj_index];
		phr->u.d.u.stream_info.buffer_size =
			phm->u.d.u.buffer.buffer_size;

		अगर (phw->outstream_host_buffer_size[phm->obj_index] ==
			phm->u.d.u.buffer.buffer_size) अणु
			/* Same size, no action required */
			वापस;
		पूर्ण

		अगर (hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
					obj_index]))
			hpios_locked_mem_मुक्त(&phw->outstream_host_buffers
				[phm->obj_index]);

		err = hpios_locked_mem_alloc(&phw->outstream_host_buffers
			[phm->obj_index], phm->u.d.u.buffer.buffer_size,
			pao->pci.pci_dev);

		अगर (err) अणु
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			phw->outstream_host_buffer_size[phm->obj_index] = 0;
			वापस;
		पूर्ण

		err = hpios_locked_mem_get_phys_addr
			(&phw->outstream_host_buffers[phm->obj_index],
			&phm->u.d.u.buffer.pci_address);
		/* get the phys addr पूर्णांकo msg क्रम single call alloc caller
		 * needs to करो this क्रम split alloc (or use the same message)
		 * वापस the phy address क्रम split alloc in the respose too
		 */
		phr->u.d.u.stream_info.auxiliary_data_available =
			phm->u.d.u.buffer.pci_address;

		अगर (err) अणु
			hpios_locked_mem_मुक्त(&phw->outstream_host_buffers
				[phm->obj_index]);
			phw->outstream_host_buffer_size[phm->obj_index] = 0;
			phr->error = HPI_ERROR_MEMORY_ALLOC;
			वापस;
		पूर्ण
	पूर्ण

	अगर (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER) अणु
		/* GRANT phase.  Set up the BBM status, tell the DSP about
		   the buffer so it can start using BBM.
		 */
		काष्ठा hpi_hostbuffer_status *status;

		अगर (phm->u.d.u.buffer.buffer_size & (phm->u.d.u.buffer.
				buffer_size - 1)) अणु
			HPI_DEBUG_LOG(ERROR,
				"Buffer size must be 2^N not %d\न",
				phm->u.d.u.buffer.buffer_size);
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			वापस;
		पूर्ण
		phw->outstream_host_buffer_size[phm->obj_index] =
			phm->u.d.u.buffer.buffer_size;
		status = &पूर्णांकerface->outstream_host_buffer_status[phm->
			obj_index];
		status->samples_processed = 0;
		status->stream_state = HPI_STATE_STOPPED;
		status->dsp_index = 0;
		status->host_index = status->dsp_index;
		status->size_in_bytes = phm->u.d.u.buffer.buffer_size;
		status->auxiliary_data_available = 0;

		hw_message(pao, phm, phr);

		अगर (phr->error
			&& hpios_locked_mem_valid(&phw->
				outstream_host_buffers[phm->obj_index])) अणु
			hpios_locked_mem_मुक्त(&phw->outstream_host_buffers
				[phm->obj_index]);
			phw->outstream_host_buffer_size[phm->obj_index] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम outstream_host_buffer_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;
	u8 *p_bbm_data;

	अगर (hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
				obj_index])) अणु
		अगर (hpios_locked_mem_get_virt_addr(&phw->
				outstream_host_buffers[phm->obj_index],
				(व्योम *)&p_bbm_data)) अणु
			phr->error = HPI_ERROR_INVALID_OPERATION;
			वापस;
		पूर्ण
		status = &पूर्णांकerface->outstream_host_buffer_status[phm->
			obj_index];
		hpi_init_response(phr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_HOSTBUFFER_GET_INFO, 0);
		phr->u.d.u.hostbuffer_info.p_buffer = p_bbm_data;
		phr->u.d.u.hostbuffer_info.p_status = status;
	पूर्ण अन्यथा अणु
		hpi_init_response(phr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_HOSTBUFFER_GET_INFO,
			HPI_ERROR_INVALID_OPERATION);
	पूर्ण
पूर्ण

अटल व्योम outstream_host_buffer_मुक्त(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u32 command = phm->u.d.u.buffer.command;

	अगर (phw->outstream_host_buffer_size[phm->obj_index]) अणु
		अगर (command == HPI_BUFFER_CMD_EXTERNAL
			|| command == HPI_BUFFER_CMD_INTERNAL_REVOKEADAPTER) अणु
			phw->outstream_host_buffer_size[phm->obj_index] = 0;
			hw_message(pao, phm, phr);
			/* Tell adapter to stop using the host buffer. */
		पूर्ण
		अगर (command == HPI_BUFFER_CMD_EXTERNAL
			|| command == HPI_BUFFER_CMD_INTERNAL_FREE)
			hpios_locked_mem_मुक्त(&phw->outstream_host_buffers
				[phm->obj_index]);
	पूर्ण
	/* Should HPI_ERROR_INVALID_OPERATION be वापसed
	   अगर no host buffer is allocated? */
	अन्यथा
		hpi_init_response(phr, HPI_OBJ_OSTREAM,
			HPI_OSTREAM_HOSTBUFFER_FREE, 0);

पूर्ण

अटल u32 outstream_get_space_available(काष्ठा hpi_hostbuffer_status *status)
अणु
	वापस status->size_in_bytes - (status->host_index -
		status->dsp_index);
पूर्ण

अटल व्योम outstream_ग_लिखो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;
	u32 space_available;

	अगर (!phw->outstream_host_buffer_size[phm->obj_index]) अणु
		/* there  is no BBM buffer, ग_लिखो via message */
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण

	hpi_init_response(phr, phm->object, phm->function, 0);
	status = &पूर्णांकerface->outstream_host_buffer_status[phm->obj_index];

	space_available = outstream_get_space_available(status);
	अगर (space_available < phm->u.d.u.data.data_size) अणु
		phr->error = HPI_ERROR_INVALID_DATASIZE;
		वापस;
	पूर्ण

	/* HostBuffers is used to indicate host buffer is पूर्णांकernally allocated.
	   otherwise, assumed बाह्यal, data written बाह्यally */
	अगर (phm->u.d.u.data.pb_data
		&& hpios_locked_mem_valid(&phw->outstream_host_buffers[phm->
				obj_index])) अणु
		u8 *p_bbm_data;
		u32 l_first_ग_लिखो;
		u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

		अगर (hpios_locked_mem_get_virt_addr(&phw->
				outstream_host_buffers[phm->obj_index],
				(व्योम *)&p_bbm_data)) अणु
			phr->error = HPI_ERROR_INVALID_OPERATION;
			वापस;
		पूर्ण

		/* either all data,
		   or enough to fit from current to end of BBM buffer */
		l_first_ग_लिखो =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		स_नकल(p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			p_app_data, l_first_ग_लिखो);
		/* reमुख्यing data अगर any */
		स_नकल(p_bbm_data, p_app_data + l_first_ग_लिखो,
			phm->u.d.u.data.data_size - l_first_ग_लिखो);
	पूर्ण

	/*
	 * This version relies on the DSP code triggering an OStream buffer
	 * update immediately following a SET_FORMAT call. The host has
	 * alपढ़ोy written data पूर्णांकo the BBM buffer, but the DSP won't know
	 * about it until dwHostIndex is adjusted.
	 */
	अगर (phw->flag_outstream_just_reset[phm->obj_index]) अणु
		/* Format can only change after reset. Must tell DSP. */
		u16 function = phm->function;
		phw->flag_outstream_just_reset[phm->obj_index] = 0;
		phm->function = HPI_OSTREAM_SET_FORMAT;
		hw_message(pao, phm, phr);	/* send the क्रमmat to the DSP */
		phm->function = function;
		अगर (phr->error)
			वापस;
	पूर्ण

	status->host_index += phm->u.d.u.data.data_size;
पूर्ण

अटल व्योम outstream_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;

	अगर (!phw->outstream_host_buffer_size[phm->obj_index]) अणु
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण

	hpi_init_response(phr, phm->object, phm->function, 0);

	status = &पूर्णांकerface->outstream_host_buffer_status[phm->obj_index];

	phr->u.d.u.stream_info.state = (u16)status->stream_state;
	phr->u.d.u.stream_info.samples_transferred =
		status->samples_processed;
	phr->u.d.u.stream_info.buffer_size = status->size_in_bytes;
	phr->u.d.u.stream_info.data_available =
		status->size_in_bytes - outstream_get_space_available(status);
	phr->u.d.u.stream_info.auxiliary_data_available =
		status->auxiliary_data_available;
पूर्ण

अटल व्योम outstream_start(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	hw_message(pao, phm, phr);
पूर्ण

अटल व्योम outstream_reset(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	phw->flag_outstream_just_reset[phm->obj_index] = 1;
	hw_message(pao, phm, phr);
पूर्ण

अटल व्योम outstream_खोलो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	outstream_reset(pao, phm, phr);
पूर्ण

/*****************************************************************************/
/* InStream Host buffer functions */

अटल व्योम instream_host_buffer_allocate(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	u16 err = 0;
	u32 command = phm->u.d.u.buffer.command;
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;

	hpi_init_response(phr, phm->object, phm->function, 0);

	अगर (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_ALLOC) अणु

		phm->u.d.u.buffer.buffer_size =
			roundup_घात_of_two(phm->u.d.u.buffer.buffer_size);
		phr->u.d.u.stream_info.data_available =
			phw->instream_host_buffer_size[phm->obj_index];
		phr->u.d.u.stream_info.buffer_size =
			phm->u.d.u.buffer.buffer_size;

		अगर (phw->instream_host_buffer_size[phm->obj_index] ==
			phm->u.d.u.buffer.buffer_size) अणु
			/* Same size, no action required */
			वापस;
		पूर्ण

		अगर (hpios_locked_mem_valid(&phw->instream_host_buffers[phm->
					obj_index]))
			hpios_locked_mem_मुक्त(&phw->instream_host_buffers
				[phm->obj_index]);

		err = hpios_locked_mem_alloc(&phw->instream_host_buffers[phm->
				obj_index], phm->u.d.u.buffer.buffer_size,
			pao->pci.pci_dev);

		अगर (err) अणु
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			phw->instream_host_buffer_size[phm->obj_index] = 0;
			वापस;
		पूर्ण

		err = hpios_locked_mem_get_phys_addr
			(&phw->instream_host_buffers[phm->obj_index],
			&phm->u.d.u.buffer.pci_address);
		/* get the phys addr पूर्णांकo msg क्रम single call alloc. Caller
		   needs to करो this क्रम split alloc so वापस the phy address */
		phr->u.d.u.stream_info.auxiliary_data_available =
			phm->u.d.u.buffer.pci_address;
		अगर (err) अणु
			hpios_locked_mem_मुक्त(&phw->instream_host_buffers
				[phm->obj_index]);
			phw->instream_host_buffer_size[phm->obj_index] = 0;
			phr->error = HPI_ERROR_MEMORY_ALLOC;
			वापस;
		पूर्ण
	पूर्ण

	अगर (command == HPI_BUFFER_CMD_EXTERNAL
		|| command == HPI_BUFFER_CMD_INTERNAL_GRANTADAPTER) अणु
		काष्ठा hpi_hostbuffer_status *status;

		अगर (phm->u.d.u.buffer.buffer_size & (phm->u.d.u.buffer.
				buffer_size - 1)) अणु
			HPI_DEBUG_LOG(ERROR,
				"Buffer size must be 2^N not %d\न",
				phm->u.d.u.buffer.buffer_size);
			phr->error = HPI_ERROR_INVALID_DATASIZE;
			वापस;
		पूर्ण

		phw->instream_host_buffer_size[phm->obj_index] =
			phm->u.d.u.buffer.buffer_size;
		status = &पूर्णांकerface->instream_host_buffer_status[phm->
			obj_index];
		status->samples_processed = 0;
		status->stream_state = HPI_STATE_STOPPED;
		status->dsp_index = 0;
		status->host_index = status->dsp_index;
		status->size_in_bytes = phm->u.d.u.buffer.buffer_size;
		status->auxiliary_data_available = 0;

		hw_message(pao, phm, phr);

		अगर (phr->error
			&& hpios_locked_mem_valid(&phw->
				instream_host_buffers[phm->obj_index])) अणु
			hpios_locked_mem_मुक्त(&phw->instream_host_buffers
				[phm->obj_index]);
			phw->instream_host_buffer_size[phm->obj_index] = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम instream_host_buffer_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;
	u8 *p_bbm_data;

	अगर (hpios_locked_mem_valid(&phw->instream_host_buffers[phm->
				obj_index])) अणु
		अगर (hpios_locked_mem_get_virt_addr(&phw->
				instream_host_buffers[phm->obj_index],
				(व्योम *)&p_bbm_data)) अणु
			phr->error = HPI_ERROR_INVALID_OPERATION;
			वापस;
		पूर्ण
		status = &पूर्णांकerface->instream_host_buffer_status[phm->
			obj_index];
		hpi_init_response(phr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_HOSTBUFFER_GET_INFO, 0);
		phr->u.d.u.hostbuffer_info.p_buffer = p_bbm_data;
		phr->u.d.u.hostbuffer_info.p_status = status;
	पूर्ण अन्यथा अणु
		hpi_init_response(phr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_HOSTBUFFER_GET_INFO,
			HPI_ERROR_INVALID_OPERATION);
	पूर्ण
पूर्ण

अटल व्योम instream_host_buffer_मुक्त(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u32 command = phm->u.d.u.buffer.command;

	अगर (phw->instream_host_buffer_size[phm->obj_index]) अणु
		अगर (command == HPI_BUFFER_CMD_EXTERNAL
			|| command == HPI_BUFFER_CMD_INTERNAL_REVOKEADAPTER) अणु
			phw->instream_host_buffer_size[phm->obj_index] = 0;
			hw_message(pao, phm, phr);
		पूर्ण

		अगर (command == HPI_BUFFER_CMD_EXTERNAL
			|| command == HPI_BUFFER_CMD_INTERNAL_FREE)
			hpios_locked_mem_मुक्त(&phw->instream_host_buffers
				[phm->obj_index]);

	पूर्ण अन्यथा अणु
		/* Should HPI_ERROR_INVALID_OPERATION be वापसed
		   अगर no host buffer is allocated? */
		hpi_init_response(phr, HPI_OBJ_ISTREAM,
			HPI_ISTREAM_HOSTBUFFER_FREE, 0);

	पूर्ण

पूर्ण

अटल व्योम instream_start(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	hw_message(pao, phm, phr);
पूर्ण

अटल u32 instream_get_bytes_available(काष्ठा hpi_hostbuffer_status *status)
अणु
	वापस status->dsp_index - status->host_index;
पूर्ण

अटल व्योम instream_पढ़ो(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;
	u32 data_available;
	u8 *p_bbm_data;
	u32 l_first_पढ़ो;
	u8 *p_app_data = (u8 *)phm->u.d.u.data.pb_data;

	अगर (!phw->instream_host_buffer_size[phm->obj_index]) अणु
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण
	hpi_init_response(phr, phm->object, phm->function, 0);

	status = &पूर्णांकerface->instream_host_buffer_status[phm->obj_index];
	data_available = instream_get_bytes_available(status);
	अगर (data_available < phm->u.d.u.data.data_size) अणु
		phr->error = HPI_ERROR_INVALID_DATASIZE;
		वापस;
	पूर्ण

	अगर (hpios_locked_mem_valid(&phw->instream_host_buffers[phm->
				obj_index])) अणु
		अगर (hpios_locked_mem_get_virt_addr(&phw->
				instream_host_buffers[phm->obj_index],
				(व्योम *)&p_bbm_data)) अणु
			phr->error = HPI_ERROR_INVALID_OPERATION;
			वापस;
		पूर्ण

		/* either all data,
		   or enough to fit from current to end of BBM buffer */
		l_first_पढ़ो =
			min(phm->u.d.u.data.data_size,
			status->size_in_bytes -
			(status->host_index & (status->size_in_bytes - 1)));

		स_नकल(p_app_data,
			p_bbm_data +
			(status->host_index & (status->size_in_bytes - 1)),
			l_first_पढ़ो);
		/* reमुख्यing data अगर any */
		स_नकल(p_app_data + l_first_पढ़ो, p_bbm_data,
			phm->u.d.u.data.data_size - l_first_पढ़ो);
	पूर्ण
	status->host_index += phm->u.d.u.data.data_size;
पूर्ण

अटल व्योम instream_get_info(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	काष्ठा hpi_hostbuffer_status *status;
	अगर (!phw->instream_host_buffer_size[phm->obj_index]) अणु
		hw_message(pao, phm, phr);
		वापस;
	पूर्ण

	status = &पूर्णांकerface->instream_host_buffer_status[phm->obj_index];

	hpi_init_response(phr, phm->object, phm->function, 0);

	phr->u.d.u.stream_info.state = (u16)status->stream_state;
	phr->u.d.u.stream_info.samples_transferred =
		status->samples_processed;
	phr->u.d.u.stream_info.buffer_size = status->size_in_bytes;
	phr->u.d.u.stream_info.data_available =
		instream_get_bytes_available(status);
	phr->u.d.u.stream_info.auxiliary_data_available =
		status->auxiliary_data_available;
पूर्ण

/*****************************************************************************/
/* LOW-LEVEL */
#घोषणा HPI6205_MAX_खाताS_TO_LOAD 2

अटल u16 adapter_boot_load_dsp(काष्ठा hpi_adapter_obj *pao,
	u32 *pos_error_code)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा dsp_code dsp_code;
	u16 boot_code_id[HPI6205_MAX_खाताS_TO_LOAD];
	u32 temp;
	पूर्णांक dsp = 0, i = 0;
	u16 err = 0;

	boot_code_id[0] = HPI_ADAPTER_ASI(0x6205);

	boot_code_id[1] = pao->pci.pci_dev->subप्रणाली_device;
	boot_code_id[1] = HPI_ADAPTER_FAMILY_ASI(boot_code_id[1]);

	/* fix up हालs where bootcode id[1] != subsys id */
	चयन (boot_code_id[1]) अणु
	हाल HPI_ADAPTER_FAMILY_ASI(0x5000):
		boot_code_id[0] = boot_code_id[1];
		boot_code_id[1] = 0;
		अवरोध;
	हाल HPI_ADAPTER_FAMILY_ASI(0x5300):
	हाल HPI_ADAPTER_FAMILY_ASI(0x5400):
	हाल HPI_ADAPTER_FAMILY_ASI(0x6300):
		boot_code_id[1] = HPI_ADAPTER_FAMILY_ASI(0x6400);
		अवरोध;
	हाल HPI_ADAPTER_FAMILY_ASI(0x5500):
	हाल HPI_ADAPTER_FAMILY_ASI(0x5600):
	हाल HPI_ADAPTER_FAMILY_ASI(0x6500):
		boot_code_id[1] = HPI_ADAPTER_FAMILY_ASI(0x6600);
		अवरोध;
	हाल HPI_ADAPTER_FAMILY_ASI(0x8800):
		boot_code_id[1] = HPI_ADAPTER_FAMILY_ASI(0x8900);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* reset DSP by writing a 1 to the WARMRESET bit */
	temp = C6205_HDCR_WARMRESET;
	ioग_लिखो32(temp, phw->prHDCR);
	hpios_delay_micro_seconds(1000);

	/* check that PCI i/f was configured by EEPROM */
	temp = ioपढ़ो32(phw->prHSR);
	अगर ((temp & (C6205_HSR_CFGERR | C6205_HSR_EEREAD)) !=
		C6205_HSR_EEREAD)
		वापस HPI6205_ERROR_6205_EEPROM;
	temp |= 0x04;
	/* disable PINTA पूर्णांकerrupt */
	ioग_लिखो32(temp, phw->prHSR);

	/* check control रेजिस्टर reports PCI boot mode */
	temp = ioपढ़ो32(phw->prHDCR);
	अगर (!(temp & C6205_HDCR_PCIBOOT))
		वापस HPI6205_ERROR_6205_REG;

	/* try writing a few numbers to the DSP page रेजिस्टर */
	/* and पढ़ोing them back. */
	temp = 3;
	ioग_लिखो32(temp, phw->prDSPP);
	अगर ((temp | C6205_DSPP_MAP1) != ioपढ़ो32(phw->prDSPP))
		वापस HPI6205_ERROR_6205_DSPPAGE;
	temp = 2;
	ioग_लिखो32(temp, phw->prDSPP);
	अगर ((temp | C6205_DSPP_MAP1) != ioपढ़ो32(phw->prDSPP))
		वापस HPI6205_ERROR_6205_DSPPAGE;
	temp = 1;
	ioग_लिखो32(temp, phw->prDSPP);
	अगर ((temp | C6205_DSPP_MAP1) != ioपढ़ो32(phw->prDSPP))
		वापस HPI6205_ERROR_6205_DSPPAGE;
	/* reset DSP page to the correct number */
	temp = 0;
	ioग_लिखो32(temp, phw->prDSPP);
	अगर ((temp | C6205_DSPP_MAP1) != ioपढ़ो32(phw->prDSPP))
		वापस HPI6205_ERROR_6205_DSPPAGE;
	phw->dsp_page = 0;

	/* release 6713 from reset beक्रमe 6205 is bootloaded.
	   This ensures that the EMIF is inactive,
	   and the 6713 HPI माला_लो the correct booपंचांगode etc
	 */
	अगर (boot_code_id[1] != 0) अणु
		/* DSP 1 is a C6713 */
		/* CLKX0 <- '1' release the C6205 booपंचांगode pullकरोwns */
		boot_loader_ग_लिखो_mem32(pao, 0, 0x018C0024, 0x00002202);
		hpios_delay_micro_seconds(100);
		/* Reset the 6713 #1 - revB */
		boot_loader_ग_लिखो_mem32(pao, 0, C6205_BAR0_TIMER1_CTL, 0);
		/* value of bit 3 is unknown after DSP reset, other bits shoudl be 0 */
		अगर (0 != (boot_loader_पढ़ो_mem32(pao, 0,
					(C6205_BAR0_TIMER1_CTL)) & ~8))
			वापस HPI6205_ERROR_6205_REG;
		hpios_delay_micro_seconds(100);

		/* Release C6713 from reset - revB */
		boot_loader_ग_लिखो_mem32(pao, 0, C6205_BAR0_TIMER1_CTL, 4);
		अगर (4 != (boot_loader_पढ़ो_mem32(pao, 0,
					(C6205_BAR0_TIMER1_CTL)) & ~8))
			वापस HPI6205_ERROR_6205_REG;
		hpios_delay_micro_seconds(100);
	पूर्ण

	क्रम (dsp = 0; dsp < HPI6205_MAX_खाताS_TO_LOAD; dsp++) अणु
		/* is there a DSP to load? */
		अगर (boot_code_id[dsp] == 0)
			जारी;

		err = boot_loader_config_emअगर(pao, dsp);
		अगर (err)
			वापस err;

		err = boot_loader_test_पूर्णांकernal_memory(pao, dsp);
		अगर (err)
			वापस err;

		err = boot_loader_test_बाह्यal_memory(pao, dsp);
		अगर (err)
			वापस err;

		err = boot_loader_test_pld(pao, dsp);
		अगर (err)
			वापस err;

		/* ग_लिखो the DSP code करोwn पूर्णांकo the DSPs memory */
		err = hpi_dsp_code_खोलो(boot_code_id[dsp], pao->pci.pci_dev,
			&dsp_code, pos_error_code);
		अगर (err)
			वापस err;

		जबतक (1) अणु
			u32 length;
			u32 address;
			u32 type;
			u32 *pcode;

			err = hpi_dsp_code_पढ़ो_word(&dsp_code, &length);
			अगर (err)
				अवरोध;
			अगर (length == 0xFFFFFFFF)
				अवरोध;	/* end of code */

			err = hpi_dsp_code_पढ़ो_word(&dsp_code, &address);
			अगर (err)
				अवरोध;
			err = hpi_dsp_code_पढ़ो_word(&dsp_code, &type);
			अगर (err)
				अवरोध;
			err = hpi_dsp_code_पढ़ो_block(length, &dsp_code,
				&pcode);
			अगर (err)
				अवरोध;
			क्रम (i = 0; i < (पूर्णांक)length; i++) अणु
				boot_loader_ग_लिखो_mem32(pao, dsp, address,
					*pcode);
				/* dummy पढ़ो every 4 words */
				/* क्रम 6205 advisory 1.4.4 */
				अगर (i % 4 == 0)
					boot_loader_पढ़ो_mem32(pao, dsp,
						address);
				pcode++;
				address += 4;
			पूर्ण

		पूर्ण
		अगर (err) अणु
			hpi_dsp_code_बंद(&dsp_code);
			वापस err;
		पूर्ण

		/* verअगरy code */
		hpi_dsp_code_शुरुआत(&dsp_code);
		जबतक (1) अणु
			u32 length = 0;
			u32 address = 0;
			u32 type = 0;
			u32 *pcode = शून्य;
			u32 data = 0;

			hpi_dsp_code_पढ़ो_word(&dsp_code, &length);
			अगर (length == 0xFFFFFFFF)
				अवरोध;	/* end of code */

			hpi_dsp_code_पढ़ो_word(&dsp_code, &address);
			hpi_dsp_code_पढ़ो_word(&dsp_code, &type);
			hpi_dsp_code_पढ़ो_block(length, &dsp_code, &pcode);

			क्रम (i = 0; i < (पूर्णांक)length; i++) अणु
				data = boot_loader_पढ़ो_mem32(pao, dsp,
					address);
				अगर (data != *pcode) अणु
					err = 0;
					अवरोध;
				पूर्ण
				pcode++;
				address += 4;
			पूर्ण
			अगर (err)
				अवरोध;
		पूर्ण
		hpi_dsp_code_बंद(&dsp_code);
		अगर (err)
			वापस err;
	पूर्ण

	/* After bootloading all DSPs, start DSP0 running
	 * The DSP0 code will handle starting and synchronizing with its slaves
	 */
	अगर (phw->p_पूर्णांकerface_buffer) अणु
		/* we need to tell the card the physical PCI address */
		u32 physicalPC_iaddress;
		काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface =
			phw->p_पूर्णांकerface_buffer;
		u32 host_mailbox_address_on_dsp;
		u32 physicalPC_iaddress_verअगरy = 0;
		पूर्णांक समय_out = 10;
		/* set ack so we know when DSP is पढ़ोy to go */
		/* (dwDspAck will be changed to HIF_RESET) */
		पूर्णांकerface->dsp_ack = H620_HIF_UNKNOWN;
		wmb();	/* ensure ack is written beक्रमe dsp ग_लिखोs back */

		err = hpios_locked_mem_get_phys_addr(&phw->h_locked_mem,
			&physicalPC_iaddress);

		/* locate the host mailbox on the DSP. */
		host_mailbox_address_on_dsp = 0x80000000;
		जबतक ((physicalPC_iaddress != physicalPC_iaddress_verअगरy)
			&& समय_out--) अणु
			boot_loader_ग_लिखो_mem32(pao, 0,
				host_mailbox_address_on_dsp,
				physicalPC_iaddress);
			physicalPC_iaddress_verअगरy =
				boot_loader_पढ़ो_mem32(pao, 0,
				host_mailbox_address_on_dsp);
		पूर्ण
	पूर्ण
	HPI_DEBUG_LOG(DEBUG, "starting DS_ps running\n");
	/* enable पूर्णांकerrupts */
	temp = ioपढ़ो32(phw->prHSR);
	temp &= ~(u32)C6205_HSR_INTAM;
	ioग_लिखो32(temp, phw->prHSR);

	/* start code running... */
	temp = ioपढ़ो32(phw->prHDCR);
	temp |= (u32)C6205_HDCR_DSPINT;
	ioग_लिखो32(temp, phw->prHDCR);

	/* give the DSP 10ms to start up */
	hpios_delay_micro_seconds(10000);
	वापस err;

पूर्ण

/*****************************************************************************/
/* Bootloader utility functions */

अटल u32 boot_loader_पढ़ो_mem32(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index,
	u32 address)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u32 data = 0;
	__iomem u32 *p_data;

	अगर (dsp_index == 0) अणु
		/* DSP 0 is always C6205 */
		अगर ((address >= 0x01800000) & (address < 0x02000000)) अणु
			/* BAR1 रेजिस्टर access */
			p_data = pao->pci.ap_mem_base[1] +
				(address & 0x007fffff) /
				माप(*pao->pci.ap_mem_base[1]);
			/* HPI_DEBUG_LOG(WARNING,
			   "BAR1 access %08x\n", dwAddress); */
		पूर्ण अन्यथा अणु
			u32 dw4M_page = address >> 22L;
			अगर (dw4M_page != phw->dsp_page) अणु
				phw->dsp_page = dw4M_page;
				/* *INDENT OFF* */
				ioग_लिखो32(phw->dsp_page, phw->prDSPP);
				/* *INDENT-ON* */
			पूर्ण
			address &= 0x3fffff;	/* address within 4M page */
			/* BAR0 memory access */
			p_data = pao->pci.ap_mem_base[0] +
				address / माप(u32);
		पूर्ण
		data = ioपढ़ो32(p_data);
	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* DSP 1 is a C6713 */
		u32 lsb;
		boot_loader_ग_लिखो_mem32(pao, 0, HPIAL_ADDR, address);
		boot_loader_ग_लिखो_mem32(pao, 0, HPIAH_ADDR, address >> 16);
		lsb = boot_loader_पढ़ो_mem32(pao, 0, HPIDL_ADDR);
		data = boot_loader_पढ़ो_mem32(pao, 0, HPIDH_ADDR);
		data = (data << 16) | (lsb & 0xFFFF);
	पूर्ण
	वापस data;
पूर्ण

अटल व्योम boot_loader_ग_लिखो_mem32(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index, u32 address, u32 data)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	__iomem u32 *p_data;
	/*      u32 dwVerअगरyData=0; */

	अगर (dsp_index == 0) अणु
		/* DSP 0 is always C6205 */
		अगर ((address >= 0x01800000) & (address < 0x02000000)) अणु
			/* BAR1 - DSP  रेजिस्टर access using */
			/* Non-prefetchable PCI access */
			p_data = pao->pci.ap_mem_base[1] +
				(address & 0x007fffff) /
				माप(*pao->pci.ap_mem_base[1]);
		पूर्ण अन्यथा अणु
			/* BAR0 access - all of DSP memory using */
			/* pre-fetchable PCI access */
			u32 dw4M_page = address >> 22L;
			अगर (dw4M_page != phw->dsp_page) अणु
				phw->dsp_page = dw4M_page;
				/* *INDENT-OFF* */
				ioग_लिखो32(phw->dsp_page, phw->prDSPP);
				/* *INDENT-ON* */
			पूर्ण
			address &= 0x3fffff;	/* address within 4M page */
			p_data = pao->pci.ap_mem_base[0] +
				address / माप(u32);
		पूर्ण
		ioग_लिखो32(data, p_data);
	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* DSP 1 is a C6713 */
		boot_loader_ग_लिखो_mem32(pao, 0, HPIAL_ADDR, address);
		boot_loader_ग_लिखो_mem32(pao, 0, HPIAH_ADDR, address >> 16);

		/* dummy पढ़ो every 4 words क्रम 6205 advisory 1.4.4 */
		boot_loader_पढ़ो_mem32(pao, 0, 0);

		boot_loader_ग_लिखो_mem32(pao, 0, HPIDL_ADDR, data);
		boot_loader_ग_लिखो_mem32(pao, 0, HPIDH_ADDR, data >> 16);

		/* dummy पढ़ो every 4 words क्रम 6205 advisory 1.4.4 */
		boot_loader_पढ़ो_mem32(pao, 0, 0);
	पूर्ण
पूर्ण

अटल u16 boot_loader_config_emअगर(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index)
अणु
	अगर (dsp_index == 0) अणु
		u32 setting;

		/* DSP 0 is always C6205 */

		/* Set the EMIF */
		/* memory map of C6205 */
		/* 00000000-0000FFFF    16Kx32 पूर्णांकernal program */
		/* 00400000-00BFFFFF    CE0     2Mx32 SDRAM running @ 100MHz */

		/* EMIF config */
		/*------------ */
		/* Global EMIF control */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800000, 0x3779);
#घोषणा WS_OFS 28
#घोषणा WST_OFS 22
#घोषणा WH_OFS 20
#घोषणा RS_OFS 16
#घोषणा RST_OFS 8
#घोषणा MTYPE_OFS 4
#घोषणा RH_OFS 0

		/* EMIF CE0 setup - 2Mx32 Sync DRAM on ASI5000 cards only */
		setting = 0x00000030;
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800008, setting);
		अगर (setting != boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x01800008))
			वापस HPI6205_ERROR_DSP_EMIF1;

		/* EMIF CE1 setup - 32 bit async. This is 6713 #1 HPI, */
		/* which occupies D15..0. 6713 starts at 27MHz, so need */
		/* plenty of रुको states. See dsn8701.rtf, and 6713 errata. */
		/* WST should be 71, but 63  is max possible */
		setting =
			(1L << WS_OFS) | (63L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (63L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800004, setting);
		अगर (setting != boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x01800004))
			वापस HPI6205_ERROR_DSP_EMIF2;

		/* EMIF CE2 setup - 32 bit async. This is 6713 #2 HPI, */
		/* which occupies D15..0. 6713 starts at 27MHz, so need */
		/* plenty of रुको states */
		setting =
			(1L << WS_OFS) | (28L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (63L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800010, setting);
		अगर (setting != boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x01800010))
			वापस HPI6205_ERROR_DSP_EMIF3;

		/* EMIF CE3 setup - 32 bit async. */
		/* This is the PLD on the ASI5000 cards only */
		setting =
			(1L << WS_OFS) | (10L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (10L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS);
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800014, setting);
		अगर (setting != boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x01800014))
			वापस HPI6205_ERROR_DSP_EMIF4;

		/* set EMIF SDRAM control क्रम 2Mx32 SDRAM (512x32x4 bank) */
		/*  need to use this अन्यथा DSP code crashes? */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01800018,
			0x07117000);

		/* EMIF SDRAM Refresh Timing */
		/* EMIF SDRAM timing  (orig = 0x410, emulator = 0x61a) */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x0180001C,
			0x00000410);

	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* test access to the C6713s HPI रेजिस्टरs */
		u32 ग_लिखो_data = 0, पढ़ो_data = 0, i = 0;

		/* Set up HPIC क्रम little endian, by setiing HPIC:HWOB=1 */
		ग_लिखो_data = 1;
		boot_loader_ग_लिखो_mem32(pao, 0, HPICL_ADDR, ग_लिखो_data);
		boot_loader_ग_लिखो_mem32(pao, 0, HPICH_ADDR, ग_लिखो_data);
		/* C67 HPI is on lower 16bits of 32bit EMIF */
		पढ़ो_data =
			0xFFF7 & boot_loader_पढ़ो_mem32(pao, 0, HPICL_ADDR);
		अगर (ग_लिखो_data != पढ़ो_data) अणु
			HPI_DEBUG_LOG(ERROR, "HPICL %x %x\n", ग_लिखो_data,
				पढ़ो_data);
			वापस HPI6205_ERROR_C6713_HPIC;
		पूर्ण
		/* HPIA - walking ones test */
		ग_लिखो_data = 1;
		क्रम (i = 0; i < 32; i++) अणु
			boot_loader_ग_लिखो_mem32(pao, 0, HPIAL_ADDR,
				ग_लिखो_data);
			boot_loader_ग_लिखो_mem32(pao, 0, HPIAH_ADDR,
				(ग_लिखो_data >> 16));
			पढ़ो_data =
				0xFFFF & boot_loader_पढ़ो_mem32(pao, 0,
				HPIAL_ADDR);
			पढ़ो_data =
				पढ़ो_data | ((0xFFFF &
					boot_loader_पढ़ो_mem32(pao, 0,
						HPIAH_ADDR))
				<< 16);
			अगर (पढ़ो_data != ग_लिखो_data) अणु
				HPI_DEBUG_LOG(ERROR, "HPIA %x %x\n",
					ग_लिखो_data, पढ़ो_data);
				वापस HPI6205_ERROR_C6713_HPIA;
			पूर्ण
			ग_लिखो_data = ग_लिखो_data << 1;
		पूर्ण

		/* setup C67x PLL
		 *  ** C6713 datasheet says we cannot program PLL from HPI,
		 * and indeed अगर we try to set the PLL multiply from the HPI,
		 * the PLL करोes not seem to lock, so we enable the PLL and
		 * use the शेष multiply of x 7, which क्रम a 27MHz घड़ी
		 * gives a DSP speed of 189MHz
		 */
		/* bypass PLL */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01B7C100, 0x0000);
		hpios_delay_micro_seconds(1000);
		/* EMIF = 189/3=63MHz */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01B7C120, 0x8002);
		/* peri = 189/2 */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01B7C11C, 0x8001);
		/* cpu  = 189/1 */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01B7C118, 0x8000);
		hpios_delay_micro_seconds(1000);
		/* ** SGT test to take GPO3 high when we start the PLL */
		/* and low when the delay is completed */
		/* FSX0 <- '1' (GPO3) */
		boot_loader_ग_लिखो_mem32(pao, 0, (0x018C0024L), 0x00002A0A);
		/* PLL not bypassed */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x01B7C100, 0x0001);
		hpios_delay_micro_seconds(1000);
		/* FSX0 <- '0' (GPO3) */
		boot_loader_ग_लिखो_mem32(pao, 0, (0x018C0024L), 0x00002A02);

		/* 6205 EMIF CE1 resetup - 32 bit async. */
		/* Now 6713 #1 is running at 189MHz can reduce रुकोstates */
		boot_loader_ग_लिखो_mem32(pao, 0, 0x01800004,	/* CE1 */
			(1L << WS_OFS) | (8L << WST_OFS) | (1L << WH_OFS) |
			(1L << RS_OFS) | (12L << RST_OFS) | (1L << RH_OFS) |
			(2L << MTYPE_OFS));

		hpios_delay_micro_seconds(1000);

		/* check that we can पढ़ो one of the PLL रेजिस्टरs */
		/* PLL should not be bypassed! */
		अगर ((boot_loader_पढ़ो_mem32(pao, dsp_index, 0x01B7C100) & 0xF)
			!= 0x0001) अणु
			वापस HPI6205_ERROR_C6713_PLL;
		पूर्ण
		/* setup C67x EMIF  (note this is the only use of
		   BAR1 via BootLoader_WriteMem32) */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, C6713_EMIF_GCTL,
			0x000034A8);

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
		boot_loader_ग_लिखो_mem32(pao, dsp_index, C6713_EMIF_CE0,
			0x00000030);

		/* EMIF SDRAM Extension
		   0x00
		   31-21        0000b 0000b 000b
		   20           WR2RD = 2cycles-1  = 1b

		   19-18        WR2DEAC = 3cycle-1 = 10b
		   17           WR2WR = 2cycle-1   = 1b
		   16-15        R2WDQM = 4cycle-1  = 11b
		   14-12        RD2WR = 6cycles-1  = 101b

		   11-10        RD2DEAC = 4cycle-1 = 11b
		   9            RD2RD = 2cycle-1   = 1b
		   8-7          THZP = 3cycle-1    = 10b
		   6-5          TWR  = 2cycle-1    = 01b (tWR = 17ns)
		   4            TRRD = 2cycle      = 0b  (tRRD = 14ns)
		   3-1          TRAS = 5cycle-1    = 100b (Tras=42ns)
		   1            CAS latency = 3cyc = 1b
		   (क्रम Micron 2M32-7 operating at 100MHz)
		 */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, C6713_EMIF_SDRAMEXT,
			0x001BDF29);

		/* EMIF SDRAM control - set up क्रम a 2Mx32 SDRAM (512x32x4 bank)
		   31           -       0b       -
		   30           SDBSZ   1b              4 bank
		   29..28       SDRSZ   00b             11 row address pins

		   27..26       SDCSZ   01b             8 column address pins
		   25           RFEN    1b              refersh enabled
		   24           INIT    1b              init SDRAM!

		   23..20       TRCD    0001b                   (Trcd/Tcyc)-1 = (20/10)-1 = 1

		   19..16       TRP     0001b                   (Trp/Tcyc)-1 = (20/10)-1 = 1

		   15..12       TRC     0110b                   (Trc/Tcyc)-1 = (70/10)-1 = 6

		   11..0        -       0000b 0000b 0000b
		 */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, C6713_EMIF_SDRAMCTL,
			0x47116000);

		/* SDRAM refresh timing
		   Need 4,096 refresh cycles every 64ms = 15.625us = 1562cycles of 100MHz = 0x61A
		 */
		boot_loader_ग_लिखो_mem32(pao, dsp_index,
			C6713_EMIF_SDRAMTIMING, 0x00000410);

		hpios_delay_micro_seconds(1000);
	पूर्ण अन्यथा अगर (dsp_index == 2) अणु
		/* DSP 2 is a C6713 */
	पूर्ण

	वापस 0;
पूर्ण

अटल u16 boot_loader_test_memory(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index,
	u32 start_address, u32 length)
अणु
	u32 i = 0, j = 0;
	u32 test_addr = 0;
	u32 test_data = 0, data = 0;

	length = 1000;

	/* क्रम 1st word, test each bit in the 32bit word, */
	/* dwLength specअगरies number of 32bit words to test */
	/*क्रम(i=0; i<dwLength; i++) */
	i = 0;
	अणु
		test_addr = start_address + i * 4;
		test_data = 0x00000001;
		क्रम (j = 0; j < 32; j++) अणु
			boot_loader_ग_लिखो_mem32(pao, dsp_index, test_addr,
				test_data);
			data = boot_loader_पढ़ो_mem32(pao, dsp_index,
				test_addr);
			अगर (data != test_data) अणु
				HPI_DEBUG_LOG(VERBOSE,
					"Memtest error details  "
					"%08x %08x %08x %i\n", test_addr,
					test_data, data, dsp_index);
				वापस 1;	/* error */
			पूर्ण
			test_data = test_data << 1;
		पूर्ण	/* क्रम(j) */
	पूर्ण	/* क्रम(i) */

	/* क्रम the next 100 locations test each location, leaving it as zero */
	/* ग_लिखो a zero to the next word in memory beक्रमe we पढ़ो */
	/* the previous ग_लिखो to make sure every memory location is unique */
	क्रम (i = 0; i < 100; i++) अणु
		test_addr = start_address + i * 4;
		test_data = 0xA5A55A5A;
		boot_loader_ग_लिखो_mem32(pao, dsp_index, test_addr, test_data);
		boot_loader_ग_लिखो_mem32(pao, dsp_index, test_addr + 4, 0);
		data = boot_loader_पढ़ो_mem32(pao, dsp_index, test_addr);
		अगर (data != test_data) अणु
			HPI_DEBUG_LOG(VERBOSE,
				"Memtest error details  "
				"%08x %08x %08x %i\n", test_addr, test_data,
				data, dsp_index);
			वापस 1;	/* error */
		पूर्ण
		/* leave location as zero */
		boot_loader_ग_लिखो_mem32(pao, dsp_index, test_addr, 0x0);
	पूर्ण

	/* zero out entire memory block */
	क्रम (i = 0; i < length; i++) अणु
		test_addr = start_address + i * 4;
		boot_loader_ग_लिखो_mem32(pao, dsp_index, test_addr, 0x0);
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 boot_loader_test_पूर्णांकernal_memory(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index)
अणु
	पूर्णांक err = 0;
	अगर (dsp_index == 0) अणु
		/* DSP 0 is a C6205 */
		/* 64K prog mem */
		err = boot_loader_test_memory(pao, dsp_index, 0x00000000,
			0x10000);
		अगर (!err)
			/* 64K data mem */
			err = boot_loader_test_memory(pao, dsp_index,
				0x80000000, 0x10000);
	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* DSP 1 is a C6713 */
		/* 192K पूर्णांकernal mem */
		err = boot_loader_test_memory(pao, dsp_index, 0x00000000,
			0x30000);
		अगर (!err)
			/* 64K पूर्णांकernal mem / L2 cache */
			err = boot_loader_test_memory(pao, dsp_index,
				0x00030000, 0x10000);
	पूर्ण

	अगर (err)
		वापस HPI6205_ERROR_DSP_INTMEM;
	अन्यथा
		वापस 0;
पूर्ण

अटल u16 boot_loader_test_बाह्यal_memory(काष्ठा hpi_adapter_obj *pao,
	पूर्णांक dsp_index)
अणु
	u32 dRAM_start_address = 0;
	u32 dRAM_size = 0;

	अगर (dsp_index == 0) अणु
		/* only test क्रम SDRAM अगर an ASI5000 card */
		अगर (pao->pci.pci_dev->subप्रणाली_device == 0x5000) अणु
			/* DSP 0 is always C6205 */
			dRAM_start_address = 0x00400000;
			dRAM_size = 0x200000;
			/*dwDRAMinc=1024; */
		पूर्ण अन्यथा
			वापस 0;
	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* DSP 1 is a C6713 */
		dRAM_start_address = 0x80000000;
		dRAM_size = 0x200000;
		/*dwDRAMinc=1024; */
	पूर्ण

	अगर (boot_loader_test_memory(pao, dsp_index, dRAM_start_address,
			dRAM_size))
		वापस HPI6205_ERROR_DSP_EXTMEM;
	वापस 0;
पूर्ण

अटल u16 boot_loader_test_pld(काष्ठा hpi_adapter_obj *pao, पूर्णांक dsp_index)
अणु
	u32 data = 0;
	अगर (dsp_index == 0) अणु
		/* only test क्रम DSP0 PLD on ASI5000 card */
		अगर (pao->pci.pci_dev->subप्रणाली_device == 0x5000) अणु
			/* PLD is located at CE3=0x03000000 */
			data = boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x03000008);
			अगर ((data & 0xF) != 0x5)
				वापस HPI6205_ERROR_DSP_PLD;
			data = boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x0300000C);
			अगर ((data & 0xF) != 0xA)
				वापस HPI6205_ERROR_DSP_PLD;
		पूर्ण
	पूर्ण अन्यथा अगर (dsp_index == 1) अणु
		/* DSP 1 is a C6713 */
		अगर (pao->pci.pci_dev->subप्रणाली_device == 0x8700) अणु
			/* PLD is located at CE1=0x90000000 */
			data = boot_loader_पढ़ो_mem32(pao, dsp_index,
				0x90000010);
			अगर ((data & 0xFF) != 0xAA)
				वापस HPI6205_ERROR_DSP_PLD;
			/* 8713 - LED on */
			boot_loader_ग_लिखो_mem32(pao, dsp_index, 0x90000000,
				0x02);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/** Transfer data to or from DSP
 nOperation = H620_H620_HIF_SEND_DATA or H620_HIF_GET_DATA
*/
अटल लघु hpi6205_transfer_data(काष्ठा hpi_adapter_obj *pao, u8 *p_data,
	u32 data_size, पूर्णांक operation)
अणु
	काष्ठा hpi_hw_obj *phw = pao->priv;
	u32 data_transferred = 0;
	u16 err = 0;
	u32 temp2;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;

	अगर (!p_data)
		वापस HPI_ERROR_INVALID_DATA_POINTER;

	data_size &= ~3L;	/* round data_size करोwn to nearest 4 bytes */

	/* make sure state is IDLE */
	अगर (!रुको_dsp_ack(phw, H620_HIF_IDLE, HPI6205_TIMEOUT))
		वापस HPI_ERROR_DSP_HARDWARE;

	जबतक (data_transferred < data_size) अणु
		u32 this_copy = data_size - data_transferred;

		अगर (this_copy > HPI6205_SIZखातापूर्ण_DATA)
			this_copy = HPI6205_SIZखातापूर्ण_DATA;

		अगर (operation == H620_HIF_SEND_DATA)
			स_नकल((व्योम *)&पूर्णांकerface->u.b_data[0],
				&p_data[data_transferred], this_copy);

		पूर्णांकerface->transfer_size_in_bytes = this_copy;

		/* DSP must change this back to nOperation */
		पूर्णांकerface->dsp_ack = H620_HIF_IDLE;
		send_dsp_command(phw, operation);

		temp2 = रुको_dsp_ack(phw, operation, HPI6205_TIMEOUT);
		HPI_DEBUG_LOG(DEBUG, "spun %d times for data xfer of %d\n",
			HPI6205_TIMEOUT - temp2, this_copy);

		अगर (!temp2) अणु
			/* समयd out */
			HPI_DEBUG_LOG(ERROR,
				"Timed out waiting for " "state %d got %d\n",
				operation, पूर्णांकerface->dsp_ack);

			अवरोध;
		पूर्ण
		अगर (operation == H620_HIF_GET_DATA)
			स_नकल(&p_data[data_transferred],
				(व्योम *)&पूर्णांकerface->u.b_data[0], this_copy);

		data_transferred += this_copy;
	पूर्ण
	अगर (पूर्णांकerface->dsp_ack != operation)
		HPI_DEBUG_LOG(DEBUG, "interface->dsp_ack=%d, expected %d\n",
			पूर्णांकerface->dsp_ack, operation);
	/*                      err=HPI_ERROR_DSP_HARDWARE; */

	send_dsp_command(phw, H620_HIF_IDLE);

	वापस err;
पूर्ण

/* रुको क्रम up to समयout_us microseconds क्रम the DSP
   to संकेत state by DMA पूर्णांकo dwDspAck
*/
अटल पूर्णांक रुको_dsp_ack(काष्ठा hpi_hw_obj *phw, पूर्णांक state, पूर्णांक समयout_us)
अणु
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	पूर्णांक t = समयout_us / 4;

	rmb();	/* ensure पूर्णांकerface->dsp_ack is up to date */
	जबतक ((पूर्णांकerface->dsp_ack != state) && --t) अणु
		hpios_delay_micro_seconds(4);
		rmb();	/* DSP changes dsp_ack by DMA */
	पूर्ण

	/*HPI_DEBUG_LOG(VERBOSE, "Spun %d for %d\n", समयout_us/4-t, state); */
	वापस t * 4;
पूर्ण

/* set the busmaster पूर्णांकerface to cmd, then पूर्णांकerrupt the DSP */
अटल व्योम send_dsp_command(काष्ठा hpi_hw_obj *phw, पूर्णांक cmd)
अणु
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	u32 r;

	पूर्णांकerface->host_cmd = cmd;
	wmb();	/* DSP माला_लो state by DMA, make sure it is written to memory */
	/* beक्रमe we पूर्णांकerrupt the DSP */
	r = ioपढ़ो32(phw->prHDCR);
	r |= (u32)C6205_HDCR_DSPINT;
	ioग_लिखो32(r, phw->prHDCR);
	r &= ~(u32)C6205_HDCR_DSPINT;
	ioग_लिखो32(r, phw->prHDCR);
पूर्ण

अटल अचिन्हित पूर्णांक message_count;

अटल u16 message_response_sequence(काष्ठा hpi_adapter_obj *pao,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr)
अणु
	u32 समय_out, समय_out2;
	काष्ठा hpi_hw_obj *phw = pao->priv;
	काष्ठा bus_master_पूर्णांकerface *पूर्णांकerface = phw->p_पूर्णांकerface_buffer;
	u16 err = 0;

	message_count++;
	अगर (phm->size > माप(पूर्णांकerface->u.message_buffer)) अणु
		phr->error = HPI_ERROR_MESSAGE_BUFFER_TOO_SMALL;
		phr->specअगरic_error = माप(पूर्णांकerface->u.message_buffer);
		phr->size = माप(काष्ठा hpi_response_header);
		HPI_DEBUG_LOG(ERROR,
			"message len %d too big for buffer %zd \n", phm->size,
			माप(पूर्णांकerface->u.message_buffer));
		वापस 0;
	पूर्ण

	/* Assume buffer of type काष्ठा bus_master_पूर्णांकerface_62
	   is allocated "noncacheable" */

	अगर (!रुको_dsp_ack(phw, H620_HIF_IDLE, HPI6205_TIMEOUT)) अणु
		HPI_DEBUG_LOG(DEBUG, "timeout waiting for idle\n");
		वापस HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT;
	पूर्ण

	स_नकल(&पूर्णांकerface->u.message_buffer, phm, phm->size);
	/* संकेत we want a response */
	send_dsp_command(phw, H620_HIF_GET_RESP);

	समय_out2 = रुको_dsp_ack(phw, H620_HIF_GET_RESP, HPI6205_TIMEOUT);

	अगर (!समय_out2) अणु
		HPI_DEBUG_LOG(ERROR,
			"(%u) Timed out waiting for " "GET_RESP state [%x]\n",
			message_count, पूर्णांकerface->dsp_ack);
	पूर्ण अन्यथा अणु
		HPI_DEBUG_LOG(VERBOSE,
			"(%u) transition to GET_RESP after %u\n",
			message_count, HPI6205_TIMEOUT - समय_out2);
	पूर्ण
	/* spin रुकोing on HIF पूर्णांकerrupt flag (end of msg process) */
	समय_out = HPI6205_TIMEOUT;

	/* पढ़ो the result */
	अगर (समय_out) अणु
		अगर (पूर्णांकerface->u.response_buffer.response.size <= phr->size)
			स_नकल(phr, &पूर्णांकerface->u.response_buffer,
				पूर्णांकerface->u.response_buffer.response.size);
		अन्यथा अणु
			HPI_DEBUG_LOG(ERROR,
				"response len %d too big for buffer %d\n",
				पूर्णांकerface->u.response_buffer.response.size,
				phr->size);
			स_नकल(phr, &पूर्णांकerface->u.response_buffer,
				माप(काष्ठा hpi_response_header));
			phr->error = HPI_ERROR_RESPONSE_BUFFER_TOO_SMALL;
			phr->specअगरic_error =
				पूर्णांकerface->u.response_buffer.response.size;
			phr->size = माप(काष्ठा hpi_response_header);
		पूर्ण
	पूर्ण
	/* set पूर्णांकerface back to idle */
	send_dsp_command(phw, H620_HIF_IDLE);

	अगर (!समय_out || !समय_out2) अणु
		HPI_DEBUG_LOG(DEBUG, "something timed out!\n");
		वापस HPI6205_ERROR_MSG_RESP_TIMEOUT;
	पूर्ण
	/* special हाल क्रम adapter बंद - */
	/* रुको क्रम the DSP to indicate it is idle */
	अगर (phm->function == HPI_ADAPTER_CLOSE) अणु
		अगर (!रुको_dsp_ack(phw, H620_HIF_IDLE, HPI6205_TIMEOUT)) अणु
			HPI_DEBUG_LOG(DEBUG,
				"Timeout waiting for idle "
				"(on adapter_close)\n");
			वापस HPI6205_ERROR_MSG_RESP_IDLE_TIMEOUT;
		पूर्ण
	पूर्ण
	err = hpi_validate_response(phm, phr);
	वापस err;
पूर्ण

अटल व्योम hw_message(काष्ठा hpi_adapter_obj *pao, काष्ठा hpi_message *phm,
	काष्ठा hpi_response *phr)
अणु

	u16 err = 0;

	hpios_dsplock_lock(pao);

	err = message_response_sequence(pao, phm, phr);

	/* maybe an error response */
	अगर (err) अणु
		/* something failed in the HPI/DSP पूर्णांकerface */
		अगर (err >= HPI_ERROR_BACKEND_BASE) अणु
			phr->error = HPI_ERROR_DSP_COMMUNICATION;
			phr->specअगरic_error = err;
		पूर्ण अन्यथा अणु
			phr->error = err;
		पूर्ण

		pao->dsp_crashed++;

		/* just the header of the response is valid */
		phr->size = माप(काष्ठा hpi_response_header);
		जाओ err;
	पूर्ण अन्यथा
		pao->dsp_crashed = 0;

	अगर (phr->error != 0)	/* something failed in the DSP */
		जाओ err;

	चयन (phm->function) अणु
	हाल HPI_OSTREAM_WRITE:
	हाल HPI_ISTREAM_ANC_WRITE:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_SEND_DATA);
		अवरोध;

	हाल HPI_ISTREAM_READ:
	हाल HPI_OSTREAM_ANC_READ:
		err = hpi6205_transfer_data(pao, phm->u.d.u.data.pb_data,
			phm->u.d.u.data.data_size, H620_HIF_GET_DATA);
		अवरोध;

	पूर्ण
	phr->error = err;

err:
	hpios_dsplock_unlock(pao);

	वापस;
पूर्ण
