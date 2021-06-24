<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*

    AudioScience HPI driver
    Copyright (C) 1997-2014  AudioScience Inc. <support@audioscience.com>


*/

काष्ठा hpi_adapter_obj;

/* a function that takes an adapter obj and वापसs an पूर्णांक */
प्रकार पूर्णांक adapter_पूर्णांक_func(काष्ठा hpi_adapter_obj *pao, u32 message);

#घोषणा HPI_IRQ_NONE		(0)
#घोषणा HPI_IRQ_MESSAGE		(1)
#घोषणा HPI_IRQ_MIXER		(2)

काष्ठा hpi_adapter_obj अणु
	काष्ठा hpi_pci pci;	/* PCI info - bus#,dev#,address etc */
	u16 type;		/* 0x6644 == ASI6644 etc */
	u16 index;

	काष्ठा hpios_spinlock dsp_lock;

	u16 dsp_crashed;
	u16 has_control_cache;
	व्योम *priv;
	adapter_पूर्णांक_func *irq_query_and_clear;
	काष्ठा hpi_hostbuffer_status *instream_host_buffer_status;
	काष्ठा hpi_hostbuffer_status *outstream_host_buffer_status;
पूर्ण;

काष्ठा hpi_control_cache अणु
	/** indicates whether the काष्ठाures are initialized */
	u16 init;
	u16 adap_idx;
	u32 control_count;
	u32 cache_size_in_bytes;
	/** poपूर्णांकer to allocated memory of lookup poपूर्णांकers. */
	काष्ठा hpi_control_cache_info **p_info;
	/** poपूर्णांकer to DSP's control cache. */
	u8 *p_cache;
पूर्ण;

काष्ठा hpi_adapter_obj *hpi_find_adapter(u16 adapter_index);

u16 hpi_add_adapter(काष्ठा hpi_adapter_obj *pao);

व्योम hpi_delete_adapter(काष्ठा hpi_adapter_obj *pao);

लघु hpi_check_control_cache(काष्ठा hpi_control_cache *pC,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

लघु hpi_check_control_cache_single(काष्ठा hpi_control_cache_single *pC,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

काष्ठा hpi_control_cache *hpi_alloc_control_cache(स्थिर u32
	number_of_controls, स्थिर u32 size_in_bytes, u8 *pDSP_control_buffer);

व्योम hpi_मुक्त_control_cache(काष्ठा hpi_control_cache *p_cache);

व्योम hpi_cmn_control_cache_sync_to_msg(काष्ठा hpi_control_cache *pC,
	काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

व्योम hpi_cmn_control_cache_sync_to_msg_single(काष्ठा hpi_control_cache_single
	*pC, काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

u16 hpi_validate_response(काष्ठा hpi_message *phm, काष्ठा hpi_response *phr);

hpi_handler_func HPI_COMMON;
