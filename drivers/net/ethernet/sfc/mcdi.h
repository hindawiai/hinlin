<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2008-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_MCDI_H
#घोषणा EFX_MCDI_H

/**
 * क्रमागत efx_mcdi_state - MCDI request handling state
 * @MCDI_STATE_QUIESCENT: No pending MCDI requests. If the caller holds the
 *	mcdi @अगरace_lock then they are able to move to %MCDI_STATE_RUNNING
 * @MCDI_STATE_RUNNING_SYNC: There is a synchronous MCDI request pending.
 *	Only the thपढ़ो that moved पूर्णांकo this state is allowed to move out of it.
 * @MCDI_STATE_RUNNING_ASYNC: There is an asynchronous MCDI request pending.
 * @MCDI_STATE_PROXY_WAIT: An MCDI request has completed with a response that
 *	indicates we must रुको क्रम a proxy try again message.
 * @MCDI_STATE_COMPLETED: An MCDI request has completed, but the owning thपढ़ो
 *	has not yet consumed the result. For all other thपढ़ोs, equivalent to
 *	%MCDI_STATE_RUNNING.
 */
क्रमागत efx_mcdi_state अणु
	MCDI_STATE_QUIESCENT,
	MCDI_STATE_RUNNING_SYNC,
	MCDI_STATE_RUNNING_ASYNC,
	MCDI_STATE_PROXY_WAIT,
	MCDI_STATE_COMPLETED,
पूर्ण;

/**
 * क्रमागत efx_mcdi_mode - MCDI transaction mode
 * @MCDI_MODE_POLL: poll क्रम MCDI completion, until समयout
 * @MCDI_MODE_EVENTS: रुको क्रम an mcdi_event.  On समयout, poll once
 * @MCDI_MODE_FAIL: we think MCDI is dead, so fail-fast all calls
 */
क्रमागत efx_mcdi_mode अणु
	MCDI_MODE_POLL,
	MCDI_MODE_EVENTS,
	MCDI_MODE_FAIL,
पूर्ण;

/**
 * काष्ठा efx_mcdi_अगरace - MCDI protocol context
 * @efx: The associated NIC.
 * @state: Request handling state. Waited क्रम by @wq.
 * @mode: Poll क्रम mcdi completion, or रुको क्रम an mcdi_event.
 * @wq: Wait queue क्रम thपढ़ोs रुकोing क्रम @state != %MCDI_STATE_RUNNING
 * @new_epoch: Indicates start of day or start of MC reboot recovery
 * @अगरace_lock: Serialises access to @seqno, @credits and response metadata
 * @seqno: The next sequence number to use क्रम mcdi requests.
 * @credits: Number of spurious MCDI completion events allowed beक्रमe we
 *     trigger a fatal error
 * @resprc: Response error/success code (Linux numbering)
 * @resp_hdr_len: Response header length
 * @resp_data_len: Response data (SDU or error) length
 * @async_lock: Serialises access to @async_list जबतक event processing is
 *	enabled
 * @async_list: Queue of asynchronous requests
 * @async_समयr: Timer क्रम asynchronous request समयout
 * @logging_buffer: buffer that may be used to build MCDI tracing messages
 * @logging_enabled: whether to trace MCDI
 * @proxy_rx_handle: Most recently received proxy authorisation handle
 * @proxy_rx_status: Status of most recent proxy authorisation
 * @proxy_rx_wq: Wait queue क्रम updates to proxy_rx_handle
 */
काष्ठा efx_mcdi_अगरace अणु
	काष्ठा efx_nic *efx;
	क्रमागत efx_mcdi_state state;
	क्रमागत efx_mcdi_mode mode;
	रुको_queue_head_t wq;
	spinlock_t अगरace_lock;
	bool new_epoch;
	अचिन्हित पूर्णांक credits;
	अचिन्हित पूर्णांक seqno;
	पूर्णांक resprc;
	पूर्णांक resprc_raw;
	माप_प्रकार resp_hdr_len;
	माप_प्रकार resp_data_len;
	spinlock_t async_lock;
	काष्ठा list_head async_list;
	काष्ठा समयr_list async_समयr;
#अगर_घोषित CONFIG_SFC_MCDI_LOGGING
	अक्षर *logging_buffer;
	bool logging_enabled;
#पूर्ण_अगर
	अचिन्हित पूर्णांक proxy_rx_handle;
	पूर्णांक proxy_rx_status;
	रुको_queue_head_t proxy_rx_wq;
पूर्ण;

काष्ठा efx_mcdi_mon अणु
	काष्ठा efx_buffer dma_buf;
	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_update;
	काष्ठा device *device;
	काष्ठा efx_mcdi_mon_attribute *attrs;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	अचिन्हित पूर्णांक n_attrs;
पूर्ण;

काष्ठा efx_mcdi_mtd_partition अणु
	काष्ठा efx_mtd_partition common;
	bool updating;
	u16 nvram_type;
	u16 fw_subtype;
पूर्ण;

#घोषणा to_efx_mcdi_mtd_partition(mtd)				\
	container_of(mtd, काष्ठा efx_mcdi_mtd_partition, common.mtd)

/**
 * काष्ठा efx_mcdi_data - extra state क्रम NICs that implement MCDI
 * @अगरace: Interface/protocol state
 * @hwmon: Hardware monitor state
 * @fn_flags: Flags क्रम this function, as वापसed by %MC_CMD_DRV_ATTACH.
 */
काष्ठा efx_mcdi_data अणु
	काष्ठा efx_mcdi_अगरace अगरace;
#अगर_घोषित CONFIG_SFC_MCDI_MON
	काष्ठा efx_mcdi_mon hwmon;
#पूर्ण_अगर
	u32 fn_flags;
पूर्ण;

अटल अंतरभूत काष्ठा efx_mcdi_अगरace *efx_mcdi(काष्ठा efx_nic *efx)
अणु
	EFX_WARN_ON_PARANOID(!efx->mcdi);
	वापस &efx->mcdi->अगरace;
पूर्ण

#अगर_घोषित CONFIG_SFC_MCDI_MON
अटल अंतरभूत काष्ठा efx_mcdi_mon *efx_mcdi_mon(काष्ठा efx_nic *efx)
अणु
	EFX_WARN_ON_PARANOID(!efx->mcdi);
	वापस &efx->mcdi->hwmon;
पूर्ण
#पूर्ण_अगर

पूर्णांक efx_mcdi_init(काष्ठा efx_nic *efx);
व्योम efx_mcdi_detach(काष्ठा efx_nic *efx);
व्योम efx_mcdi_fini(काष्ठा efx_nic *efx);

पूर्णांक efx_mcdi_rpc(काष्ठा efx_nic *efx, अचिन्हित cmd, स्थिर efx_dword_t *inbuf,
		 माप_प्रकार inlen, efx_dword_t *outbuf, माप_प्रकार outlen,
		 माप_प्रकार *outlen_actual);
पूर्णांक efx_mcdi_rpc_quiet(काष्ठा efx_nic *efx, अचिन्हित cmd,
		       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
		       efx_dword_t *outbuf, माप_प्रकार outlen,
		       माप_प्रकार *outlen_actual);

पूर्णांक efx_mcdi_rpc_start(काष्ठा efx_nic *efx, अचिन्हित cmd,
		       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen);
पूर्णांक efx_mcdi_rpc_finish(काष्ठा efx_nic *efx, अचिन्हित cmd, माप_प्रकार inlen,
			efx_dword_t *outbuf, माप_प्रकार outlen,
			माप_प्रकार *outlen_actual);
पूर्णांक efx_mcdi_rpc_finish_quiet(काष्ठा efx_nic *efx, अचिन्हित cmd,
			      माप_प्रकार inlen, efx_dword_t *outbuf,
			      माप_प्रकार outlen, माप_प्रकार *outlen_actual);

प्रकार व्योम efx_mcdi_async_completer(काष्ठा efx_nic *efx,
				      अचिन्हित दीर्घ cookie, पूर्णांक rc,
				      efx_dword_t *outbuf,
				      माप_प्रकार outlen_actual);
पूर्णांक efx_mcdi_rpc_async(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
		       स्थिर efx_dword_t *inbuf, माप_प्रकार inlen, माप_प्रकार outlen,
		       efx_mcdi_async_completer *complete,
		       अचिन्हित दीर्घ cookie);
पूर्णांक efx_mcdi_rpc_async_quiet(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक cmd,
			     स्थिर efx_dword_t *inbuf, माप_प्रकार inlen,
			     माप_प्रकार outlen,
			     efx_mcdi_async_completer *complete,
			     अचिन्हित दीर्घ cookie);

व्योम efx_mcdi_display_error(काष्ठा efx_nic *efx, अचिन्हित cmd,
			    माप_प्रकार inlen, efx_dword_t *outbuf,
			    माप_प्रकार outlen, पूर्णांक rc);

पूर्णांक efx_mcdi_poll_reboot(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mode_poll(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mode_event(काष्ठा efx_nic *efx);
व्योम efx_mcdi_flush_async(काष्ठा efx_nic *efx);

व्योम efx_mcdi_process_event(काष्ठा efx_channel *channel, efx_qword_t *event);
व्योम efx_mcdi_sensor_event(काष्ठा efx_nic *efx, efx_qword_t *ev);

/* We expect that 16- and 32-bit fields in MCDI requests and responses
 * are appropriately aligned, but 64-bit fields are only
 * 32-bit-aligned.  Also, on Siena we must copy to the MC shared
 * memory strictly 32 bits at a समय, so add any necessary padding.
 */
#घोषणा MCDI_TX_BUF_LEN(_len) DIV_ROUND_UP((_len), 4)
#घोषणा _MCDI_DECLARE_BUF(_name, _len)					\
	efx_dword_t _name[DIV_ROUND_UP(_len, 4)]
#घोषणा MCDI_DECLARE_BUF(_name, _len)					\
	_MCDI_DECLARE_BUF(_name, _len) = अणुअणुअणु0पूर्णपूर्णपूर्ण
#घोषणा MCDI_DECLARE_BUF_ERR(_name)					\
	MCDI_DECLARE_BUF(_name, 8)
#घोषणा _MCDI_PTR(_buf, _offset)					\
	((u8 *)(_buf) + (_offset))
#घोषणा MCDI_PTR(_buf, _field)						\
	_MCDI_PTR(_buf, MC_CMD_ ## _field ## _OFST)
#घोषणा _MCDI_CHECK_ALIGN(_ofst, _align)				\
	((_ofst) + BUILD_BUG_ON_ZERO((_ofst) & (_align - 1)))
#घोषणा _MCDI_DWORD(_buf, _field)					\
	((_buf) + (_MCDI_CHECK_ALIGN(MC_CMD_ ## _field ## _OFST, 4) >> 2))

#घोषणा MCDI_BYTE(_buf, _field)						\
	((व्योम)BUILD_BUG_ON_ZERO(MC_CMD_ ## _field ## _LEN != 1),	\
	 *MCDI_PTR(_buf, _field))
#घोषणा MCDI_WORD(_buf, _field)						\
	((u16)BUILD_BUG_ON_ZERO(MC_CMD_ ## _field ## _LEN != 2) +	\
	 le16_to_cpu(*(__क्रमce स्थिर __le16 *)MCDI_PTR(_buf, _field)))
#घोषणा MCDI_SET_DWORD(_buf, _field, _value)				\
	EFX_POPULATE_DWORD_1(*_MCDI_DWORD(_buf, _field), EFX_DWORD_0, _value)
#घोषणा MCDI_DWORD(_buf, _field)					\
	EFX_DWORD_FIELD(*_MCDI_DWORD(_buf, _field), EFX_DWORD_0)
#घोषणा MCDI_POPULATE_DWORD_1(_buf, _field, _name1, _value1)		\
	EFX_POPULATE_DWORD_1(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1)
#घोषणा MCDI_POPULATE_DWORD_2(_buf, _field, _name1, _value1,		\
			      _name2, _value2)				\
	EFX_POPULATE_DWORD_2(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2)
#घोषणा MCDI_POPULATE_DWORD_3(_buf, _field, _name1, _value1,		\
			      _name2, _value2, _name3, _value3)		\
	EFX_POPULATE_DWORD_3(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2,		\
			     MC_CMD_ ## _name3, _value3)
#घोषणा MCDI_POPULATE_DWORD_4(_buf, _field, _name1, _value1,		\
			      _name2, _value2, _name3, _value3,		\
			      _name4, _value4)				\
	EFX_POPULATE_DWORD_4(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2,		\
			     MC_CMD_ ## _name3, _value3,		\
			     MC_CMD_ ## _name4, _value4)
#घोषणा MCDI_POPULATE_DWORD_5(_buf, _field, _name1, _value1,		\
			      _name2, _value2, _name3, _value3,		\
			      _name4, _value4, _name5, _value5)		\
	EFX_POPULATE_DWORD_5(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2,		\
			     MC_CMD_ ## _name3, _value3,		\
			     MC_CMD_ ## _name4, _value4,		\
			     MC_CMD_ ## _name5, _value5)
#घोषणा MCDI_POPULATE_DWORD_6(_buf, _field, _name1, _value1,		\
			      _name2, _value2, _name3, _value3,		\
			      _name4, _value4, _name5, _value5,		\
			      _name6, _value6)				\
	EFX_POPULATE_DWORD_6(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2,		\
			     MC_CMD_ ## _name3, _value3,		\
			     MC_CMD_ ## _name4, _value4,		\
			     MC_CMD_ ## _name5, _value5,		\
			     MC_CMD_ ## _name6, _value6)
#घोषणा MCDI_POPULATE_DWORD_7(_buf, _field, _name1, _value1,		\
			      _name2, _value2, _name3, _value3,		\
			      _name4, _value4, _name5, _value5,		\
			      _name6, _value6, _name7, _value7)		\
	EFX_POPULATE_DWORD_7(*_MCDI_DWORD(_buf, _field),		\
			     MC_CMD_ ## _name1, _value1,		\
			     MC_CMD_ ## _name2, _value2,		\
			     MC_CMD_ ## _name3, _value3,		\
			     MC_CMD_ ## _name4, _value4,		\
			     MC_CMD_ ## _name5, _value5,		\
			     MC_CMD_ ## _name6, _value6,		\
			     MC_CMD_ ## _name7, _value7)
#घोषणा MCDI_SET_QWORD(_buf, _field, _value)				\
	करो अणु								\
		EFX_POPULATE_DWORD_1(_MCDI_DWORD(_buf, _field)[0],	\
				     EFX_DWORD_0, (u32)(_value));	\
		EFX_POPULATE_DWORD_1(_MCDI_DWORD(_buf, _field)[1],	\
				     EFX_DWORD_0, (u64)(_value) >> 32);	\
	पूर्ण जबतक (0)
#घोषणा MCDI_QWORD(_buf, _field)					\
	(EFX_DWORD_FIELD(_MCDI_DWORD(_buf, _field)[0], EFX_DWORD_0) |	\
	(u64)EFX_DWORD_FIELD(_MCDI_DWORD(_buf, _field)[1], EFX_DWORD_0) << 32)
#घोषणा MCDI_FIELD(_ptr, _type, _field)					\
	EFX_EXTRACT_DWORD(						\
		*(efx_dword_t *)					\
		_MCDI_PTR(_ptr, MC_CMD_ ## _type ## _ ## _field ## _OFST & ~3),\
		MC_CMD_ ## _type ## _ ## _field ## _LBN & 0x1f,	\
		(MC_CMD_ ## _type ## _ ## _field ## _LBN & 0x1f) +	\
		MC_CMD_ ## _type ## _ ## _field ## _WIDTH - 1)

#घोषणा _MCDI_ARRAY_PTR(_buf, _field, _index, _align)			\
	(_MCDI_PTR(_buf, _MCDI_CHECK_ALIGN(MC_CMD_ ## _field ## _OFST, _align))\
	 + (_index) * _MCDI_CHECK_ALIGN(MC_CMD_ ## _field ## _LEN, _align))
#घोषणा MCDI_DECLARE_STRUCT_PTR(_name)					\
	efx_dword_t *_name
#घोषणा MCDI_ARRAY_STRUCT_PTR(_buf, _field, _index)			\
	((efx_dword_t *)_MCDI_ARRAY_PTR(_buf, _field, _index, 4))
#घोषणा MCDI_VAR_ARRAY_LEN(_len, _field)				\
	min_t(माप_प्रकार, MC_CMD_ ## _field ## _MAXNUM,			\
	      ((_len) - MC_CMD_ ## _field ## _OFST) / MC_CMD_ ## _field ## _LEN)
#घोषणा MCDI_ARRAY_WORD(_buf, _field, _index)				\
	(BUILD_BUG_ON_ZERO(MC_CMD_ ## _field ## _LEN != 2) +		\
	 le16_to_cpu(*(__क्रमce स्थिर __le16 *)				\
		     _MCDI_ARRAY_PTR(_buf, _field, _index, 2)))
#घोषणा _MCDI_ARRAY_DWORD(_buf, _field, _index)				\
	(BUILD_BUG_ON_ZERO(MC_CMD_ ## _field ## _LEN != 4) +		\
	 (efx_dword_t *)_MCDI_ARRAY_PTR(_buf, _field, _index, 4))
#घोषणा MCDI_SET_ARRAY_DWORD(_buf, _field, _index, _value)		\
	EFX_SET_DWORD_FIELD(*_MCDI_ARRAY_DWORD(_buf, _field, _index),	\
			    EFX_DWORD_0, _value)
#घोषणा MCDI_ARRAY_DWORD(_buf, _field, _index)				\
	EFX_DWORD_FIELD(*_MCDI_ARRAY_DWORD(_buf, _field, _index), EFX_DWORD_0)
#घोषणा _MCDI_ARRAY_QWORD(_buf, _field, _index)				\
	(BUILD_BUG_ON_ZERO(MC_CMD_ ## _field ## _LEN != 8) +		\
	 (efx_dword_t *)_MCDI_ARRAY_PTR(_buf, _field, _index, 4))
#घोषणा MCDI_SET_ARRAY_QWORD(_buf, _field, _index, _value)		\
	करो अणु								\
		EFX_SET_DWORD_FIELD(_MCDI_ARRAY_QWORD(_buf, _field, _index)[0],\
				    EFX_DWORD_0, (u32)(_value));	\
		EFX_SET_DWORD_FIELD(_MCDI_ARRAY_QWORD(_buf, _field, _index)[1],\
				    EFX_DWORD_0, (u64)(_value) >> 32);	\
	पूर्ण जबतक (0)
#घोषणा MCDI_ARRAY_FIELD(_buf, _field1, _type, _index, _field2)		\
	MCDI_FIELD(MCDI_ARRAY_STRUCT_PTR(_buf, _field1, _index),	\
		   _type ## _TYPEDEF, _field2)

#घोषणा MCDI_EVENT_FIELD(_ev, _field)			\
	EFX_QWORD_FIELD(_ev, MCDI_EVENT_ ## _field)

#घोषणा MCDI_CAPABILITY(field)						\
	MC_CMD_GET_CAPABILITIES_V8_OUT_ ## field ## _LBN

#घोषणा MCDI_CAPABILITY_OFST(field) \
	MC_CMD_GET_CAPABILITIES_V8_OUT_ ## field ## _OFST

#घोषणा efx_has_cap(efx, field) \
	efx->type->check_caps(efx, \
			      MCDI_CAPABILITY(field), \
			      MCDI_CAPABILITY_OFST(field))

व्योम efx_mcdi_prपूर्णांक_fwver(काष्ठा efx_nic *efx, अक्षर *buf, माप_प्रकार len);
पूर्णांक efx_mcdi_get_board_cfg(काष्ठा efx_nic *efx, u8 *mac_address,
			   u16 *fw_subtype_list, u32 *capabilities);
पूर्णांक efx_mcdi_log_ctrl(काष्ठा efx_nic *efx, bool evq, bool uart, u32 dest_evq);
पूर्णांक efx_mcdi_nvram_types(काष्ठा efx_nic *efx, u32 *nvram_types_out);
पूर्णांक efx_mcdi_nvram_info(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक type,
			माप_प्रकार *size_out, माप_प्रकार *erase_size_out,
			bool *रक्षित_out);
पूर्णांक efx_new_mcdi_nvram_test_all(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_nvram_test_all(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_handle_निश्चितion(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_set_id_led(काष्ठा efx_nic *efx, क्रमागत efx_led_mode mode);
पूर्णांक efx_mcdi_wol_filter_set_magic(काष्ठा efx_nic *efx, स्थिर u8 *mac,
				  पूर्णांक *id_out);
पूर्णांक efx_mcdi_wol_filter_get_magic(काष्ठा efx_nic *efx, पूर्णांक *id_out);
पूर्णांक efx_mcdi_wol_filter_हटाओ(काष्ठा efx_nic *efx, पूर्णांक id);
पूर्णांक efx_mcdi_wol_filter_reset(काष्ठा efx_nic *efx);
पूर्णांक efx_mcdi_flush_rxqs(काष्ठा efx_nic *efx);
व्योम efx_mcdi_process_link_change(काष्ठा efx_nic *efx, efx_qword_t *ev);
व्योम efx_mcdi_mac_start_stats(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mac_stop_stats(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mac_pull_stats(काष्ठा efx_nic *efx);
क्रमागत reset_type efx_mcdi_map_reset_reason(क्रमागत reset_type reason);
पूर्णांक efx_mcdi_reset(काष्ठा efx_nic *efx, क्रमागत reset_type method);
पूर्णांक efx_mcdi_set_workaround(काष्ठा efx_nic *efx, u32 type, bool enabled,
			    अचिन्हित पूर्णांक *flags);
पूर्णांक efx_mcdi_get_workarounds(काष्ठा efx_nic *efx, अचिन्हित पूर्णांक *impl_out,
			     अचिन्हित पूर्णांक *enabled_out);

#अगर_घोषित CONFIG_SFC_MCDI_MON
पूर्णांक efx_mcdi_mon_probe(काष्ठा efx_nic *efx);
व्योम efx_mcdi_mon_हटाओ(काष्ठा efx_nic *efx);
#अन्यथा
अटल अंतरभूत पूर्णांक efx_mcdi_mon_probe(काष्ठा efx_nic *efx) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम efx_mcdi_mon_हटाओ(काष्ठा efx_nic *efx) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_SFC_MTD
पूर्णांक efx_mcdi_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
		      माप_प्रकार *retlen, u8 *buffer);
पूर्णांक efx_mcdi_mtd_erase(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len);
पूर्णांक efx_mcdi_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t start, माप_प्रकार len,
		       माप_प्रकार *retlen, स्थिर u8 *buffer);
पूर्णांक efx_mcdi_mtd_sync(काष्ठा mtd_info *mtd);
व्योम efx_mcdi_mtd_नाम(काष्ठा efx_mtd_partition *part);
#पूर्ण_अगर

#पूर्ण_अगर /* EFX_MCDI_H */
