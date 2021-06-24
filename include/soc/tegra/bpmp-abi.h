<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2014-2020, NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित ABI_BPMP_ABI_H
#घोषणा ABI_BPMP_ABI_H

#अगर defined(LK) || defined(BPMP_ABI_HAVE_STDC)
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>
#पूर्ण_अगर

#अगर_अघोषित BPMP_ABI_PACKED
#अगर_घोषित __ABI_PACKED
#घोषणा BPMP_ABI_PACKED __ABI_PACKED
#अन्यथा
#घोषणा BPMP_ABI_PACKED __attribute__((packed))
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित NO_GCC_EXTENSIONS
#घोषणा BPMP_ABI_EMPTY अक्षर empty;
#घोषणा BPMP_ABI_EMPTY_ARRAY 1
#अन्यथा
#घोषणा BPMP_ABI_EMPTY
#घोषणा BPMP_ABI_EMPTY_ARRAY 0
#पूर्ण_अगर

#अगर_अघोषित BPMP_UNION_ANON
#अगर_घोषित __UNION_ANON
#घोषणा BPMP_UNION_ANON __UNION_ANON
#अन्यथा
#घोषणा BPMP_UNION_ANON
#पूर्ण_अगर
#पूर्ण_अगर

/**
 * @file
 */

/**
 * @defgroup MRQ MRQ Messages
 * @brief Messages sent to/from BPMP via IPC
 * @अणु
 *   @defgroup MRQ_Format Message Format
 *   @defgroup MRQ_Codes Message Request (MRQ) Codes
 *   @defgroup MRQ_Payloads Message Payloads
 *   @defgroup Error_Codes Error Codes
 * @पूर्ण
 */

/**
 * @addtogroup MRQ_Format
 * @अणु
 * The CPU requests the BPMP to perक्रमm a particular service by
 * sending it an IVC frame containing a single MRQ message. An MRQ
 * message consists of a @ref mrq_request followed by a payload whose
 * क्रमmat depends on mrq_request::mrq.
 *
 * The BPMP processes the data and replies with an IVC frame (on the
 * same IVC channel) containing and MRQ response. An MRQ response
 * consists of a @ref mrq_response followed by a payload whose क्रमmat
 * depends on the associated mrq_request::mrq.
 *
 * A well-defined subset of the MRQ messages that the CPU sends to the
 * BPMP can lead to BPMP eventually sending an MRQ message to the
 * CPU. For example, when the CPU uses an #MRQ_THERMAL message to set
 * a thermal trip poपूर्णांक, the BPMP may eventually send a single
 * #MRQ_THERMAL message of its own to the CPU indicating that the trip
 * poपूर्णांक has been crossed.
 * @पूर्ण
 */

/**
 * @ingroup MRQ_Format
 * @brief Header क्रम an MRQ message
 *
 * Provides the MRQ number क्रम the MRQ message: #mrq. The reमुख्यder of
 * the MRQ message is a payload (immediately following the
 * mrq_request) whose क्रमmat depends on mrq.
 */
काष्ठा mrq_request अणु
	/** @brief MRQ number of the request */
	uपूर्णांक32_t mrq;

	/**
	 * @brief Flags providing follow up directions to the receiver
	 *
	 * | Bit | Description                                |
	 * |-----|--------------------------------------------|
	 * | 1   | ring the sender's करोorbell when responding |
	 * | 0   | should be 1                                |
	 */
	uपूर्णांक32_t flags;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Format
 * @brief Header क्रम an MRQ response
 *
 *  Provides an error code क्रम the associated MRQ message. The
 *  reमुख्यder of the MRQ response is a payload (immediately following
 *  the mrq_response) whose क्रमmat depends on the associated
 *  mrq_request::mrq
 */
काष्ठा mrq_response अणु
	/** @brief Error code क्रम the MRQ request itself */
	पूर्णांक32_t err;
	/** @brief Reserved क्रम future use */
	uपूर्णांक32_t flags;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Format
 * Minimum needed size क्रम an IPC message buffer
 */
#घोषणा MSG_MIN_SZ	128U
/**
 * @ingroup MRQ_Format
 *  Minimum size guaranteed क्रम data in an IPC message buffer
 */
#घोषणा MSG_DATA_MIN_SZ	120U

/**
 * @ingroup MRQ_Codes
 * @name Legal MRQ codes
 * These are the legal values क्रम mrq_request::mrq
 * @अणु
 */

#घोषणा MRQ_PING		0U
#घोषणा MRQ_QUERY_TAG		1U
#घोषणा MRQ_MODULE_LOAD		4U
#घोषणा MRQ_MODULE_UNLOAD	5U
#घोषणा MRQ_TRACE_MODIFY	7U
#घोषणा MRQ_WRITE_TRACE		8U
#घोषणा MRQ_THREADED_PING	9U
#घोषणा MRQ_MODULE_MAIL		11U
#घोषणा MRQ_DEBUGFS		19U
#घोषणा MRQ_RESET		20U
#घोषणा MRQ_I2C			21U
#घोषणा MRQ_CLK			22U
#घोषणा MRQ_QUERY_ABI		23U
#घोषणा MRQ_PG_READ_STATE	25U
#घोषणा MRQ_PG_UPDATE_STATE	26U
#घोषणा MRQ_THERMAL		27U
#घोषणा MRQ_CPU_VHINT		28U
#घोषणा MRQ_ABI_RATCHET		29U
#घोषणा MRQ_EMC_DVFS_LATENCY	31U
#घोषणा MRQ_TRACE_ITER		64U
#घोषणा MRQ_RINGBUF_CONSOLE	65U
#घोषणा MRQ_PG			66U
#घोषणा MRQ_CPU_NDIV_LIMITS	67U
#घोषणा MRQ_STRAP               68U
#घोषणा MRQ_UPHY		69U
#घोषणा MRQ_CPU_AUTO_CC3	70U
#घोषणा MRQ_QUERY_FW_TAG	71U
#घोषणा MRQ_FMON		72U
#घोषणा MRQ_EC			73U
#घोषणा MRQ_DEBUG		75U

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @brief Maximum MRQ code to be sent by CPU software to
 * BPMP. Subject to change in future
 */
#घोषणा MAX_CPU_MRQ_ID		75U

/**
 * @addtogroup MRQ_Payloads
 * @अणु
 *   @defgroup Ping Ping
 *   @defgroup Query_Tag Query Tag
 *   @defgroup Module Loadable Modules
 *   @defgroup Trace Trace
 *   @defgroup Debugfs Debug File System
 *   @defgroup Reset Reset
 *   @defgroup I2C I2C
 *   @defgroup Clocks Clocks
 *   @defgroup ABI_info ABI Info
 *   @defgroup Powergating Power Gating
 *   @defgroup Thermal Thermal
 *   @defgroup Vhपूर्णांक CPU Voltage hपूर्णांक
 *   @defgroup EMC EMC
 *   @defgroup CPU NDIV Limits
 *   @defgroup RingbufConsole Ring Buffer Console
 *   @defgroup Strap Straps
 *   @defgroup UPHY UPHY
 *   @defgroup CC3 Auto-CC3
 *   @defgroup FMON FMON
 *   @defgroup EC EC
 *   @defgroup Fbvolt_status Fuse Burn Voltage Status
 * @पूर्ण
 */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_PING
 * @brief A simple ping
 *
 * * Platक्रमms: All
 * * Initiators: Any
 * * Tarमाला_लो: Any
 * * Request Payload: @ref mrq_ping_request
 * * Response Payload: @ref mrq_ping_response
 *
 * @ingroup MRQ_Codes
 * @def MRQ_THREADED_PING
 * @brief A deeper ping
 *
 * * Platक्रमms: All
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_ping_request
 * * Response Payload: @ref mrq_ping_response
 *
 * Behavior is equivalent to a simple #MRQ_PING except that BPMP
 * responds from a thपढ़ो context (providing a slightly more robust
 * sign of lअगरe).
 *
 */

/**
 * @ingroup Ping
 * @brief Request with #MRQ_PING
 *
 * Used by the sender of an #MRQ_PING message to request a pong from
 * recipient. The response from the recipient is computed based on
 * #challenge.
 */
काष्ठा mrq_ping_request अणु
/** @brief Arbitrarily chosen value */
	uपूर्णांक32_t challenge;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Ping
 * @brief Response to #MRQ_PING
 *
 * Sent in response to an #MRQ_PING message. #reply should be the
 * mrq_ping_request challenge left shअगरted by 1 with the carry-bit
 * dropped.
 *
 */
काष्ठा mrq_ping_response अणु
	/** @brief Response to the MRQ_PING challege */
	uपूर्णांक32_t reply;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_QUERY_TAG
 * @brief Query BPMP firmware's tag (i.e. unique identअगरer)
 *
 * @deprecated Use #MRQ_QUERY_FW_TAG instead.
 *
 * * Platक्रमms: All
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_query_tag_request
 * * Response Payload: N/A
 *
 */

/**
 * @ingroup Query_Tag
 * @brief Request with #MRQ_QUERY_TAG
 *
 * @deprecated This काष्ठाure will be हटाओd in future version.
 * Use MRQ_QUERY_FW_TAG instead.
 */
काष्ठा mrq_query_tag_request अणु
  /** @brief Base address to store the firmware tag */
	uपूर्णांक32_t addr;
पूर्ण BPMP_ABI_PACKED;


/**
 * @ingroup MRQ_Codes
 * @def MRQ_QUERY_FW_TAG
 * @brief Query BPMP firmware's tag (i.e. unique identअगरier)
 *
 * * Platक्रमms: All
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: N/A
 * * Response Payload: @ref mrq_query_fw_tag_response
 *
 */

/**
 * @ingroup Query_Tag
 * @brief Response to #MRQ_QUERY_FW_TAG
 *
 * Sent in response to #MRQ_QUERY_FW_TAG message. #tag contains the unique
 * identअगरier क्रम the version of firmware issuing the reply.
 *
 */
काष्ठा mrq_query_fw_tag_response अणु
  /** @brief Array to store tag inक्रमmation */
	uपूर्णांक8_t tag[32];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_MODULE_LOAD
 * @brief Dynamically load a BPMP code module
 *
 * * Platक्रमms: T210, T210B01, T186
 * @cond (bpmp_t210 || bpmp_t210b01 || bpmp_t186)
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_module_load_request
 * * Response Payload: @ref mrq_module_load_response
 *
 * @note This MRQ is disabled on production प्रणालीs
 *
 */

/**
 * @ingroup Module
 * @brief Request with #MRQ_MODULE_LOAD
 *
 * Used by #MRQ_MODULE_LOAD calls to ask the recipient to dynamically
 * load the code located at #phys_addr and having size #size
 * bytes. #phys_addr is treated as a व्योम poपूर्णांकer.
 *
 * The recipient copies the code from #phys_addr to locally allocated
 * memory prior to responding to this message.
 *
 * @toकरो करोcument the module header क्रमmat
 *
 * The sender is responsible क्रम ensuring that the code is mapped in
 * the recipient's address map.
 *
 */
काष्ठा mrq_module_load_request अणु
	/** @brief Base address of the code to load */
	uपूर्णांक32_t phys_addr;
	/** @brief Size in bytes of code to load */
	uपूर्णांक32_t size;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Module
 * @brief Response to #MRQ_MODULE_LOAD
 *
 * @toकरो करोcument mrq_response::err
 */
काष्ठा mrq_module_load_response अणु
	/** @brief Handle to the loaded module */
	uपूर्णांक32_t base;
पूर्ण BPMP_ABI_PACKED;
/** @endcond*/

/**
 * @ingroup MRQ_Codes
 * @def MRQ_MODULE_UNLOAD
 * @brief Unload a previously loaded code module
 *
 * * Platक्रमms: T210, T210B01, T186
 * @cond (bpmp_t210 || bpmp_t210b01 || bpmp_t186)
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_module_unload_request
 * * Response Payload: N/A
 *
 * @note This MRQ is disabled on production प्रणालीs
 */

/**
 * @ingroup Module
 * @brief Request with #MRQ_MODULE_UNLOAD
 *
 * Used by #MRQ_MODULE_UNLOAD calls to request that a previously loaded
 * module be unloaded.
 */
काष्ठा mrq_module_unload_request अणु
	/** @brief Handle of the module to unload */
	uपूर्णांक32_t base;
पूर्ण BPMP_ABI_PACKED;
/** @endcond*/

/**
 * @ingroup MRQ_Codes
 * @def MRQ_TRACE_MODIFY
 * @brief Modअगरy the set of enabled trace events
 *
 * @deprecated
 *
 * * Platक्रमms: All
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_trace_modअगरy_request
 * * Response Payload: @ref mrq_trace_modअगरy_response
 *
 * @note This MRQ is disabled on production प्रणालीs
 */

/**
 * @ingroup Trace
 * @brief Request with #MRQ_TRACE_MODIFY
 *
 * Used by %MRQ_TRACE_MODIFY calls to enable or disable specअगरy trace
 * events.  #set takes precedence क्रम any bit set in both #set and
 * #clr.
 */
काष्ठा mrq_trace_modअगरy_request अणु
	/** @brief Bit mask of trace events to disable */
	uपूर्णांक32_t clr;
	/** @brief Bit mask of trace events to enable */
	uपूर्णांक32_t set;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Trace
 * @brief Response to #MRQ_TRACE_MODIFY
 *
 * Sent in repsonse to an #MRQ_TRACE_MODIFY message. #mask reflects the
 * state of which events are enabled after the recipient acted on the
 * message.
 *
 */
काष्ठा mrq_trace_modअगरy_response अणु
	/** @brief Bit mask of trace event enable states */
	uपूर्णांक32_t mask;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_WRITE_TRACE
 * @brief Write trace data to a buffer
 *
 * @deprecated
 *
 * * Platक्रमms: All
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_ग_लिखो_trace_request
 * * Response Payload: @ref mrq_ग_लिखो_trace_response
 *
 * mrq_response::err depends on the @ref mrq_ग_लिखो_trace_request field
 * values. err is -#BPMP_EINVAL अगर size is zero or area is शून्य or
 * area is in an illegal range. A positive value क्रम err indicates the
 * number of bytes written to area.
 *
 * @note This MRQ is disabled on production प्रणालीs
 */

/**
 * @ingroup Trace
 * @brief Request with #MRQ_WRITE_TRACE
 *
 * Used by MRQ_WRITE_TRACE calls to ask the recipient to copy trace
 * data from the recipient's local buffer to the output buffer. #area
 * is treated as a byte-aligned poपूर्णांकer in the recipient's address
 * space.
 *
 * The sender is responsible क्रम ensuring that the output
 * buffer is mapped in the recipient's address map. The recipient is
 * responsible क्रम protecting its own code and data from accidental
 * overग_लिखोs.
 */
काष्ठा mrq_ग_लिखो_trace_request अणु
	/** @brief Base address of output buffer */
	uपूर्णांक32_t area;
	/** @brief Size in bytes of the output buffer */
	uपूर्णांक32_t size;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Trace
 * @brief Response to #MRQ_WRITE_TRACE
 *
 * Once this response is sent, the respondent will not access the
 * output buffer further.
 */
काष्ठा mrq_ग_लिखो_trace_response अणु
	/**
	 * @brief Flag whether more data reमुख्यs in local buffer
	 *
	 * Value is 1 अगर the entire local trace buffer has been
	 * drained to the outputbuffer. Value is 0 otherwise.
	 */
	uपूर्णांक32_t eof;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा mrq_thपढ़ोed_ping_request अणु
	uपूर्णांक32_t challenge;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा mrq_thपढ़ोed_ping_response अणु
	uपूर्णांक32_t reply;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_MODULE_MAIL
 * @brief Send a message to a loadable module
 *
 * * Platक्रमms: T210, T210B01, T186
 * @cond (bpmp_t210 || bpmp_t210b01 || bpmp_t186)
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_module_mail_request
 * * Response Payload: @ref mrq_module_mail_response
 *
 * @note This MRQ is disabled on production प्रणालीs
 */

/**
 * @ingroup Module
 * @brief Request with #MRQ_MODULE_MAIL
 */
काष्ठा mrq_module_mail_request अणु
	/** @brief Handle to the previously loaded module */
	uपूर्णांक32_t base;
	/** @brief Module-specअगरic mail payload
	 *
	 * The length of data[ ] is unknown to the BPMP core firmware
	 * but it is limited to the size of an IPC message.
	 */
	uपूर्णांक8_t data[BPMP_ABI_EMPTY_ARRAY];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Module
 * @brief Response to #MRQ_MODULE_MAIL
 */
काष्ठा mrq_module_mail_response अणु
	/** @brief Module-specअगरic mail payload
	 *
	 * The length of data[ ] is unknown to the BPMP core firmware
	 * but it is limited to the size of an IPC message.
	 */
	uपूर्णांक8_t data[BPMP_ABI_EMPTY_ARRAY];
पूर्ण BPMP_ABI_PACKED;
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_DEBUGFS
 * @brief Interact with BPMP's debugfs file nodes
 *
 * @deprecated use MRQ_DEBUG instead.
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_debugfs_request
 * * Response Payload: @ref mrq_debugfs_response
 */

/**
 * @addtogroup Debugfs
 * @अणु
 *
 * The BPMP firmware implements a pseuकरो-fileप्रणाली called
 * debugfs. Any driver within the firmware may रेजिस्टर with debugfs
 * to expose an arbitrary set of "files" in the fileप्रणाली. When
 * software on the CPU ग_लिखोs to a debugfs file, debugfs passes the
 * written data to a callback provided by the driver. When software on
 * the CPU पढ़ोs a debugfs file, debugfs queries the driver क्रम the
 * data to वापस to the CPU. The पूर्णांकention of the debugfs fileप्रणाली
 * is to provide inक्रमmation useful क्रम debugging the प्रणाली at
 * runसमय.
 *
 * @note The files exposed via debugfs are not part of the
 * BPMP firmware's ABI. debugfs files may be added or हटाओd in any
 * given version of the firmware. Typically the semantics of a debugfs
 * file are consistent from version to version but even that is not
 * guaranteed.
 *
 * @पूर्ण
 */

/** @ingroup Debugfs */
क्रमागत mrq_debugfs_commands अणु
	/** @brief Perक्रमm पढ़ो */
	CMD_DEBUGFS_READ = 1,
	/** @brief Perक्रमm ग_लिखो */
	CMD_DEBUGFS_WRITE = 2,
	/** @brief Perक्रमm dumping directory */
	CMD_DEBUGFS_DUMPसूची = 3,
	/** @brief Not a command */
	CMD_DEBUGFS_MAX
पूर्ण;

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUGFS_READ/WRITE command
 */
काष्ठा cmd_debugfs_fileop_request अणु
	/** @brief Physical address poपूर्णांकing at filename */
	uपूर्णांक32_t fnameaddr;
	/** @brief Length in bytes of filename buffer */
	uपूर्णांक32_t fnamelen;
	/** @brief Physical address poपूर्णांकing to data buffer */
	uपूर्णांक32_t dataaddr;
	/** @brief Length in bytes of data buffer */
	uपूर्णांक32_t datalen;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUGFS_READ/WRITE command
 */
काष्ठा cmd_debugfs_dumpdir_request अणु
	/** @brief Physical address poपूर्णांकing to data buffer */
	uपूर्णांक32_t dataaddr;
	/** @brief Length in bytes of data buffer */
	uपूर्णांक32_t datalen;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Response data क्रम CMD_DEBUGFS_READ/WRITE command
 */
काष्ठा cmd_debugfs_fileop_response अणु
	/** @brief Always 0 */
	uपूर्णांक32_t reserved;
	/** @brief Number of bytes पढ़ो from or written to data buffer */
	uपूर्णांक32_t nbytes;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Response data क्रम CMD_DEBUGFS_DUMPसूची command
 */
काष्ठा cmd_debugfs_dumpdir_response अणु
	/** @brief Always 0 */
	uपूर्णांक32_t reserved;
	/** @brief Number of bytes पढ़ो from or written to data buffer */
	uपूर्णांक32_t nbytes;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Request with #MRQ_DEBUGFS.
 *
 * The sender of an MRQ_DEBUGFS message uses #cmd to specअगरy a debugfs
 * command to execute. Legal commands are the values of @ref
 * mrq_debugfs_commands. Each command requires a specअगरic additional
 * payload of data.
 *
 * |command            |payload|
 * |-------------------|-------|
 * |CMD_DEBUGFS_READ   |fop    |
 * |CMD_DEBUGFS_WRITE  |fop    |
 * |CMD_DEBUGFS_DUMPसूची|dumpdir|
 */
काष्ठा mrq_debugfs_request अणु
	/** @brief Sub-command (@ref mrq_debugfs_commands) */
	uपूर्णांक32_t cmd;
	जोड़ अणु
		काष्ठा cmd_debugfs_fileop_request fop;
		काष्ठा cmd_debugfs_dumpdir_request dumpdir;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 */
काष्ठा mrq_debugfs_response अणु
	/** @brief Always 0 */
	पूर्णांक32_t reserved;
	जोड़ अणु
		/** @brief Response data क्रम CMD_DEBUGFS_READ OR
		 * CMD_DEBUGFS_WRITE command
		 */
		काष्ठा cmd_debugfs_fileop_response fop;
		/** @brief Response data क्रम CMD_DEBUGFS_DUMPसूची command */
		काष्ठा cmd_debugfs_dumpdir_response dumpdir;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @addtogroup Debugfs
 * @अणु
 */
#घोषणा DEBUGFS_S_ISसूची	(1 << 9)
#घोषणा DEBUGFS_S_IRUSR	(1 << 8)
#घोषणा DEBUGFS_S_IWUSR	(1 << 7)
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_DEBUG
 * @brief Interact with BPMP's debugfs file nodes. Use message payload
 * क्रम exchanging data. This is functionally equivalent to
 * @ref MRQ_DEBUGFS. But the way in which data is exchanged is dअगरferent.
 * When software running on CPU tries to पढ़ो a debugfs file,
 * the file path and पढ़ो data will be stored in message payload.
 * Since the message payload size is limited, a debugfs file
 * transaction might require multiple frames of data exchanged
 * between BPMP and CPU until the transaction completes.
 *
 * * Platक्रमms: T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_debug_request
 * * Response Payload: @ref mrq_debug_response
 */

/** @ingroup Debugfs */
क्रमागत mrq_debug_commands अणु
	/** @brief Open required file क्रम पढ़ो operation */
	CMD_DEBUG_OPEN_RO = 0,
	/** @brief Open required file क्रम ग_लिखो operation */
	CMD_DEBUG_OPEN_WO = 1,
	/** @brief Perक्रमm पढ़ो */
	CMD_DEBUG_READ = 2,
	/** @brief Perक्रमm ग_लिखो */
	CMD_DEBUG_WRITE = 3,
	/** @brief Close file */
	CMD_DEBUG_CLOSE = 4,
	/** @brief Not a command */
	CMD_DEBUG_MAX
पूर्ण;

/**
 * @ingroup Debugfs
 * @brief Maximum number of files that can be खोलो at a given समय
 */
#घोषणा DEBUG_MAX_OPEN_खाताS	1

/**
 * @ingroup Debugfs
 * @brief Maximum size of null-terminated file name string in bytes.
 * Value is derived from memory available in message payload जबतक
 * using @ref cmd_debug_ख_खोलो_request
 * Value 4 corresponds to size of @ref mrq_debug_commands
 * in @ref mrq_debug_request.
 * 120 - 4 dbg_cmd(32bit)  = 116
 */
#घोषणा DEBUG_FNAME_MAX_SZ	(MSG_DATA_MIN_SZ - 4)

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUG_OPEN command
 */
काष्ठा cmd_debug_ख_खोलो_request अणु
	/** @brief File name - Null-terminated string with maximum
	 * length @ref DEBUG_FNAME_MAX_SZ
	 */
	अक्षर name[DEBUG_FNAME_MAX_SZ];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Response data क्रम CMD_DEBUG_OPEN_RO/WO command
 */
काष्ठा cmd_debug_ख_खोलो_response अणु
	/** @brief Identअगरier क्रम file access */
	uपूर्णांक32_t fd;
	/** @brief Data length. File data size क्रम READ command.
	 * Maximum allowed length क्रम WRITE command
	 */
	uपूर्णांक32_t datalen;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUG_READ command
 */
काष्ठा cmd_debug_ख_पढ़ो_request अणु
	/** @brief File access identअगरier received in response
	 * to CMD_DEBUG_OPEN_RO request
	 */
	uपूर्णांक32_t fd;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Maximum size of पढ़ो data in bytes.
 * Value is derived from memory available in message payload जबतक
 * using @ref cmd_debug_ख_पढ़ो_response.
 */
#घोषणा DEBUG_READ_MAX_SZ	(MSG_DATA_MIN_SZ - 4)

/**
 * @ingroup Debugfs
 * @brief Response data क्रम CMD_DEBUG_READ command
 */
काष्ठा cmd_debug_ख_पढ़ो_response अणु
	/** @brief Size of data provided in this response in bytes */
	uपूर्णांक32_t पढ़ोlen;
	/** @brief File data from seek position */
	अक्षर data[DEBUG_READ_MAX_SZ];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Maximum size of ग_लिखो data in bytes.
 * Value is derived from memory available in message payload जबतक
 * using @ref cmd_debug_ख_डालो_request.
 */
#घोषणा DEBUG_WRITE_MAX_SZ	(MSG_DATA_MIN_SZ - 12)

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUG_WRITE command
 */
काष्ठा cmd_debug_ख_डालो_request अणु
	/** @brief File access identअगरier received in response
	 * to CMD_DEBUG_OPEN_RO request
	 */
	uपूर्णांक32_t fd;
	/** @brief Size of ग_लिखो data in bytes */
	uपूर्णांक32_t datalen;
	/** @brief Data to be written */
	अक्षर data[DEBUG_WRITE_MAX_SZ];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Parameters क्रम CMD_DEBUG_CLOSE command
 */
काष्ठा cmd_debug_ख_बंद_request अणु
	/** @brief File access identअगरier received in response
	 * to CMD_DEBUG_OPEN_RO request
	 */
	uपूर्णांक32_t fd;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 * @brief Request with #MRQ_DEBUG.
 *
 * The sender of an MRQ_DEBUG message uses #cmd to specअगरy a debugfs
 * command to execute. Legal commands are the values of @ref
 * mrq_debug_commands. Each command requires a specअगरic additional
 * payload of data.
 *
 * |command            |payload|
 * |-------------------|-------|
 * |CMD_DEBUG_OPEN_RO  |fop    |
 * |CMD_DEBUG_OPEN_WO  |fop    |
 * |CMD_DEBUG_READ     |frd    |
 * |CMD_DEBUG_WRITE    |fwr    |
 * |CMD_DEBUG_CLOSE    |fcl    |
 */
काष्ठा mrq_debug_request अणु
	/** @brief Sub-command (@ref mrq_debug_commands) */
	uपूर्णांक32_t cmd;
	जोड़ अणु
		/** @brief Request payload क्रम CMD_DEBUG_OPEN_RO/WO command */
		काष्ठा cmd_debug_ख_खोलो_request fop;
		/** @brief Request payload क्रम CMD_DEBUG_READ command */
		काष्ठा cmd_debug_ख_पढ़ो_request frd;
		/** @brief Request payload क्रम CMD_DEBUG_WRITE command */
		काष्ठा cmd_debug_ख_डालो_request fwr;
		/** @brief Request payload क्रम CMD_DEBUG_CLOSE command */
		काष्ठा cmd_debug_ख_बंद_request fcl;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Debugfs
 */
काष्ठा mrq_debug_response अणु
	जोड़ अणु
		/** @brief Response data क्रम CMD_DEBUG_OPEN_RO/WO command */
		काष्ठा cmd_debug_ख_खोलो_response fop;
		/** @brief Response data क्रम CMD_DEBUG_READ command */
		काष्ठा cmd_debug_ख_पढ़ो_response frd;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_RESET
 * @brief Reset an IP block
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_reset_request
 * * Response Payload: @ref mrq_reset_response
 *
 * @addtogroup Reset
 * @अणु
 */

क्रमागत mrq_reset_commands अणु
	/**
	 * @brief Assert module reset
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_EINVAL अगर mrq_reset_request::reset_id is invalid @n
	 * -#BPMP_EACCES अगर mrq master is not an owner of target करोमुख्य reset @n
	 * -#BPMP_ENOTSUP अगर target करोमुख्य h/w state करोes not allow reset
	 */
	CMD_RESET_ASSERT = 1,
	/**
	 * @brief Deनिश्चित module reset
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_EINVAL अगर mrq_reset_request::reset_id is invalid @n
	 * -#BPMP_EACCES अगर mrq master is not an owner of target करोमुख्य reset @n
	 * -#BPMP_ENOTSUP अगर target करोमुख्य h/w state करोes not allow reset
	 */
	CMD_RESET_DEASSERT = 2,
	/**
	 * @brief Assert and deनिश्चित the module reset
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_EINVAL अगर mrq_reset_request::reset_id is invalid @n
	 * -#BPMP_EACCES अगर mrq master is not an owner of target करोमुख्य reset @n
	 * -#BPMP_ENOTSUP अगर target करोमुख्य h/w state करोes not allow reset
	 */
	CMD_RESET_MODULE = 3,
	/**
	 * @brief Get the highest reset ID
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_ENODEV अगर no reset करोमुख्यs are supported (number of IDs is 0)
	 */
	CMD_RESET_GET_MAX_ID = 4,

	/** @brief Not part of ABI and subject to change */
	CMD_RESET_MAX,
पूर्ण;

/**
 * @brief Request with MRQ_RESET
 *
 * Used by the sender of an #MRQ_RESET message to request BPMP to
 * निश्चित or or deनिश्चित a given reset line.
 */
काष्ठा mrq_reset_request अणु
	/** @brief Reset action to perक्रमm (@ref mrq_reset_commands) */
	uपूर्णांक32_t cmd;
	/** @brief Id of the reset to affected */
	uपूर्णांक32_t reset_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response क्रम MRQ_RESET sub-command CMD_RESET_GET_MAX_ID. When
 * this sub-command is not supported, firmware will वापस -BPMP_EBADCMD
 * in mrq_response::err.
 */
काष्ठा cmd_reset_get_max_id_response अणु
	/** @brief Max reset id */
	uपूर्णांक32_t max_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response with MRQ_RESET
 *
 * Each sub-command supported by @ref mrq_reset_request may वापस
 * sub-command-specअगरic data. Some करो and some करो not as indicated
 * in the following table
 *
 * | sub-command          | payload          |
 * |----------------------|------------------|
 * | CMD_RESET_ASSERT     | -                |
 * | CMD_RESET_DEASSERT   | -                |
 * | CMD_RESET_MODULE     | -                |
 * | CMD_RESET_GET_MAX_ID | reset_get_max_id |
 */
काष्ठा mrq_reset_response अणु
	जोड़ अणु
		काष्ठा cmd_reset_get_max_id_response reset_get_max_id;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_I2C
 * @brief Issue an i2c transaction
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_i2c_request
 * * Response Payload: @ref mrq_i2c_response
 *
 * @addtogroup I2C
 * @अणु
 */
#घोषणा TEGRA_I2C_IPC_MAX_IN_BUF_SIZE	(MSG_DATA_MIN_SZ - 12U)
#घोषणा TEGRA_I2C_IPC_MAX_OUT_BUF_SIZE	(MSG_DATA_MIN_SZ - 4U)

#घोषणा SERIALI2C_TEN           0x0010U
#घोषणा SERIALI2C_RD            0x0001U
#घोषणा SERIALI2C_STOP          0x8000U
#घोषणा SERIALI2C_NOSTART       0x4000U
#घोषणा SERIALI2C_REV_सूची_ADDR  0x2000U
#घोषणा SERIALI2C_IGNORE_NAK    0x1000U
#घोषणा SERIALI2C_NO_RD_ACK     0x0800U
#घोषणा SERIALI2C_RECV_LEN      0x0400U

क्रमागत अणु
	CMD_I2C_XFER = 1
पूर्ण;

/**
 * @brief Serializable i2c request
 *
 * Instances of this काष्ठाure are packed (little-endian) पूर्णांकo
 * cmd_i2c_xfer_request::data_buf. Each instance represents a single
 * transaction (or a portion of a transaction with repeated starts) on
 * an i2c bus.
 *
 * Because these काष्ठाures are packed, some instances are likely to
 * be misaligned. Additionally because #data is variable length, it is
 * not possible to iterate through a serialized list of these
 * काष्ठाures without inspecting #len in each instance.  It may be
 * easier to serialize or deserialize cmd_i2c_xfer_request::data_buf
 * manually rather than using this काष्ठाure definition.
*/
काष्ठा serial_i2c_request अणु
	/** @brief I2C slave address */
	uपूर्णांक16_t addr;
	/** @brief Biपंचांगask of SERIALI2C_ flags */
	uपूर्णांक16_t flags;
	/** @brief Length of I2C transaction in bytes */
	uपूर्णांक16_t len;
	/** @brief For ग_लिखो transactions only, #len bytes of data */
	uपूर्णांक8_t data[];
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Trigger one or more i2c transactions
 */
काष्ठा cmd_i2c_xfer_request अणु
	/** @brief Valid bus number from @ref bpmp_i2c_ids*/
	uपूर्णांक32_t bus_id;

	/** @brief Count of valid bytes in #data_buf*/
	uपूर्णांक32_t data_size;

	/** @brief Serialized packed instances of @ref serial_i2c_request*/
	uपूर्णांक8_t data_buf[TEGRA_I2C_IPC_MAX_IN_BUF_SIZE];
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Container क्रम data पढ़ो from the i2c bus
 *
 * Processing an cmd_i2c_xfer_request::data_buf causes BPMP to execute
 * zero or more I2C पढ़ोs. The data पढ़ो from the bus is serialized
 * पूर्णांकo #data_buf.
 */
काष्ठा cmd_i2c_xfer_response अणु
	/** @brief Count of valid bytes in #data_buf*/
	uपूर्णांक32_t data_size;
	/** @brief I2c पढ़ो data */
	uपूर्णांक8_t data_buf[TEGRA_I2C_IPC_MAX_OUT_BUF_SIZE];
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Request with #MRQ_I2C
 */
काष्ठा mrq_i2c_request अणु
	/** @brief Always CMD_I2C_XFER (i.e. 1) */
	uपूर्णांक32_t cmd;
	/** @brief Parameters of the transfer request */
	काष्ठा cmd_i2c_xfer_request xfer;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response to #MRQ_I2C
 *
 * mrq_response:err is
 *  0: Success
 *  -#BPMP_EBADCMD: अगर mrq_i2c_request::cmd is other than 1
 *  -#BPMP_EINVAL: अगर cmd_i2c_xfer_request करोes not contain correctly क्रमmatted request
 *  -#BPMP_ENODEV: अगर cmd_i2c_xfer_request::bus_id is not supported by BPMP
 *  -#BPMP_EACCES: अगर i2c transaction is not allowed due to firewall rules
 *  -#BPMP_ETIMEDOUT: अगर i2c transaction बार out
 *  -#BPMP_ENXIO: अगर i2c slave device करोes not reply with ACK to the transaction
 *  -#BPMP_EAGAIN: अगर ARB_LOST condition is detected by the i2c controller
 *  -#BPMP_EIO: any other i2c controller error code than NO_ACK or ARB_LOST
 */
काष्ठा mrq_i2c_response अणु
	काष्ठा cmd_i2c_xfer_response xfer;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_CLK
 * @brief Perक्रमm a घड़ी operation
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_clk_request
 * * Response Payload: @ref mrq_clk_response
 *
 * @addtogroup Clocks
 * @अणु
 */
क्रमागत अणु
	CMD_CLK_GET_RATE = 1,
	CMD_CLK_SET_RATE = 2,
	CMD_CLK_ROUND_RATE = 3,
	CMD_CLK_GET_PARENT = 4,
	CMD_CLK_SET_PARENT = 5,
	CMD_CLK_IS_ENABLED = 6,
	CMD_CLK_ENABLE = 7,
	CMD_CLK_DISABLE = 8,
	CMD_CLK_GET_ALL_INFO = 14,
	CMD_CLK_GET_MAX_CLK_ID = 15,
	CMD_CLK_GET_FMAX_AT_VMIN = 16,
	CMD_CLK_MAX,
पूर्ण;

#घोषणा BPMP_CLK_HAS_MUX	(1U << 0U)
#घोषणा BPMP_CLK_HAS_SET_RATE	(1U << 1U)
#घोषणा BPMP_CLK_IS_ROOT	(1U << 2U)
#घोषणा BPMP_CLK_IS_VAR_ROOT	(1U << 3U)

#घोषणा MRQ_CLK_NAME_MAXLEN	40U
#घोषणा MRQ_CLK_MAX_PARENTS	16U

/** @निजी */
काष्ठा cmd_clk_get_rate_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_get_rate_response अणु
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_set_rate_request अणु
	पूर्णांक32_t unused;
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_set_rate_response अणु
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_round_rate_request अणु
	पूर्णांक32_t unused;
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_round_rate_response अणु
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_get_parent_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_get_parent_response अणु
	uपूर्णांक32_t parent_id;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_set_parent_request अणु
	uपूर्णांक32_t parent_id;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_set_parent_response अणु
	uपूर्णांक32_t parent_id;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_is_enabled_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response data to #MRQ_CLK sub-command CMD_CLK_IS_ENABLED
 */
काष्ठा cmd_clk_is_enabled_response अणु
	/**
	 * @brief The state of the घड़ी that has been succesfully
	 * requested with CMD_CLK_ENABLE or CMD_CLK_DISABLE by the
	 * master invoking the command earlier.
	 *
	 * The state may not reflect the physical state of the घड़ी
	 * अगर there are some other masters requesting it to be
	 * enabled.
	 *
	 * Value 0 is disabled, all other values indicate enabled.
	 */
	पूर्णांक32_t state;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_enable_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_enable_response अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_disable_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_disable_response अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_get_all_info_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_get_all_info_response अणु
	uपूर्णांक32_t flags;
	uपूर्णांक32_t parent;
	uपूर्णांक32_t parents[MRQ_CLK_MAX_PARENTS];
	uपूर्णांक8_t num_parents;
	uपूर्णांक8_t name[MRQ_CLK_NAME_MAXLEN];
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_get_max_clk_id_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_get_max_clk_id_response अणु
	uपूर्णांक32_t max_id;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_clk_get_fmax_at_vmin_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_clk_get_fmax_at_vmin_response अणु
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Clocks
 * @brief Request with #MRQ_CLK
 *
 * Used by the sender of an #MRQ_CLK message to control घड़ीs. The
 * clk_request is split पूर्णांकo several sub-commands. Some sub-commands
 * require no additional data. Others have a sub-command specअगरic
 * payload
 *
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |CMD_CLK_GET_RATE            |-                      |
 * |CMD_CLK_SET_RATE            |clk_set_rate           |
 * |CMD_CLK_ROUND_RATE          |clk_round_rate         |
 * |CMD_CLK_GET_PARENT          |-                      |
 * |CMD_CLK_SET_PARENT          |clk_set_parent         |
 * |CMD_CLK_IS_ENABLED          |-                      |
 * |CMD_CLK_ENABLE              |-                      |
 * |CMD_CLK_DISABLE             |-                      |
 * |CMD_CLK_GET_ALL_INFO        |-                      |
 * |CMD_CLK_GET_MAX_CLK_ID      |-                      |
 * |CMD_CLK_GET_FMAX_AT_VMIN    |-
 * |
 *
 */

काष्ठा mrq_clk_request अणु
	/** @brief Sub-command and घड़ी id concatenated to 32-bit word.
	 * - bits[31..24] is the sub-cmd.
	 * - bits[23..0] is the घड़ी id
	 */
	uपूर्णांक32_t cmd_and_id;

	जोड़ अणु
		/** @निजी */
		काष्ठा cmd_clk_get_rate_request clk_get_rate;
		काष्ठा cmd_clk_set_rate_request clk_set_rate;
		काष्ठा cmd_clk_round_rate_request clk_round_rate;
		/** @निजी */
		काष्ठा cmd_clk_get_parent_request clk_get_parent;
		काष्ठा cmd_clk_set_parent_request clk_set_parent;
		/** @निजी */
		काष्ठा cmd_clk_enable_request clk_enable;
		/** @निजी */
		काष्ठा cmd_clk_disable_request clk_disable;
		/** @निजी */
		काष्ठा cmd_clk_is_enabled_request clk_is_enabled;
		/** @निजी */
		काष्ठा cmd_clk_get_all_info_request clk_get_all_info;
		/** @निजी */
		काष्ठा cmd_clk_get_max_clk_id_request clk_get_max_clk_id;
		/** @निजी */
		काष्ठा cmd_clk_get_fmax_at_vmin_request clk_get_fmax_at_vmin;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Clocks
 * @brief Response to MRQ_CLK
 *
 * Each sub-command supported by @ref mrq_clk_request may वापस
 * sub-command-specअगरic data. Some करो and some करो not as indicated in
 * the following table
 *
 * |sub-command                 |payload                 |
 * |----------------------------|------------------------|
 * |CMD_CLK_GET_RATE            |clk_get_rate            |
 * |CMD_CLK_SET_RATE            |clk_set_rate            |
 * |CMD_CLK_ROUND_RATE          |clk_round_rate          |
 * |CMD_CLK_GET_PARENT          |clk_get_parent          |
 * |CMD_CLK_SET_PARENT          |clk_set_parent          |
 * |CMD_CLK_IS_ENABLED          |clk_is_enabled          |
 * |CMD_CLK_ENABLE              |-                       |
 * |CMD_CLK_DISABLE             |-                       |
 * |CMD_CLK_GET_ALL_INFO        |clk_get_all_info        |
 * |CMD_CLK_GET_MAX_CLK_ID      |clk_get_max_id          |
 * |CMD_CLK_GET_FMAX_AT_VMIN    |clk_get_fmax_at_vmin    |
 *
 */

काष्ठा mrq_clk_response अणु
	जोड़ अणु
		काष्ठा cmd_clk_get_rate_response clk_get_rate;
		काष्ठा cmd_clk_set_rate_response clk_set_rate;
		काष्ठा cmd_clk_round_rate_response clk_round_rate;
		काष्ठा cmd_clk_get_parent_response clk_get_parent;
		काष्ठा cmd_clk_set_parent_response clk_set_parent;
		/** @निजी */
		काष्ठा cmd_clk_enable_response clk_enable;
		/** @निजी */
		काष्ठा cmd_clk_disable_response clk_disable;
		काष्ठा cmd_clk_is_enabled_response clk_is_enabled;
		काष्ठा cmd_clk_get_all_info_response clk_get_all_info;
		काष्ठा cmd_clk_get_max_clk_id_response clk_get_max_clk_id;
		काष्ठा cmd_clk_get_fmax_at_vmin_response clk_get_fmax_at_vmin;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_QUERY_ABI
 * @brief Check अगर an MRQ is implemented
 *
 * * Platक्रमms: All
 * * Initiators: Any
 * * Tarमाला_लो: Any except DMCE
 * * Request Payload: @ref mrq_query_abi_request
 * * Response Payload: @ref mrq_query_abi_response
 */

/**
 * @ingroup ABI_info
 * @brief Request with MRQ_QUERY_ABI
 *
 * Used by #MRQ_QUERY_ABI call to check अगर MRQ code #mrq is supported
 * by the recipient.
 */
काष्ठा mrq_query_abi_request अणु
	/** @brief MRQ code to query */
	uपूर्णांक32_t mrq;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup ABI_info
 * @brief Response to MRQ_QUERY_ABI
 *
 * @note mrq_response::err of 0 indicates that the query was
 * successful, not that the MRQ itself is supported!
 */
काष्ठा mrq_query_abi_response अणु
	/** @brief 0 अगर queried MRQ is supported. Else, -#BPMP_ENODEV */
	पूर्णांक32_t status;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup MRQ_Codes
 * @def MRQ_PG_READ_STATE
 * @brief Read the घातer-gating state of a partition
 *
 * * Platक्रमms: T186
 * @cond bpmp_t186
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_pg_पढ़ो_state_request
 * * Response Payload: @ref mrq_pg_पढ़ो_state_response
 */

/**
 * @ingroup Powergating
 * @brief Request with #MRQ_PG_READ_STATE
 *
 * Used by MRQ_PG_READ_STATE call to पढ़ो the current state of a
 * partition.
 */
काष्ठा mrq_pg_पढ़ो_state_request अणु
	/** @brief ID of partition */
	uपूर्णांक32_t partition_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup Powergating
 * @brief Response to MRQ_PG_READ_STATE
 * @toकरो define possible errors.
 */
काष्ठा mrq_pg_पढ़ो_state_response अणु
	/** @brief Read as करोn't care */
	uपूर्णांक32_t sram_state;
	/** @brief State of घातer partition
	 * * 0 : off
	 * * 1 : on
	 */
	uपूर्णांक32_t logic_state;
पूर्ण BPMP_ABI_PACKED;
/** @endcond*/
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_PG_UPDATE_STATE
 * @brief Modअगरy the घातer-gating state of a partition. In contrast to
 * MRQ_PG calls, the operations that change state (on/off) of घातer
 * partition are reference counted.
 *
 * * Platक्रमms: T186
 * @cond bpmp_t186
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_pg_update_state_request
 * * Response Payload: N/A
 */

/**
 * @ingroup Powergating
 * @brief Request with mrq_pg_update_state_request
 *
 * Used by #MRQ_PG_UPDATE_STATE call to request BPMP to change the
 * state of a घातer partition #partition_id.
 */
काष्ठा mrq_pg_update_state_request अणु
	/** @brief ID of partition */
	uपूर्णांक32_t partition_id;
	/** @brief Secondary control of घातer partition
	 *  @details Ignored by many versions of the BPMP
	 *  firmware. For maximum compatibility, set the value
	 *  according to @ref logic_state
	 * *  0x1: घातer ON partition (@ref logic_state == 0x3)
	 * *  0x3: घातer OFF partition (@ref logic_state == 0x1)
	 */
	uपूर्णांक32_t sram_state;
	/** @brief Controls state of घातer partition, legal values are
	 * *  0x1 : घातer OFF partition
	 * *  0x3 : घातer ON partition
	 */
	uपूर्णांक32_t logic_state;
	/** @brief Change state of घड़ीs of the घातer partition, legal values
	 * *  0x0 : करो not change घड़ी state
	 * *  0x1 : disable partition घड़ीs (only applicable when
	 *          @ref logic_state == 0x1)
	 * *  0x3 : enable partition घड़ीs (only applicable when
	 *          @ref logic_state == 0x3)
	 */
	uपूर्णांक32_t घड़ी_state;
पूर्ण BPMP_ABI_PACKED;
/** @endcond*/

/**
 * @ingroup MRQ_Codes
 * @def MRQ_PG
 * @brief Control घातer-gating state of a partition. In contrast to
 * MRQ_PG_UPDATE_STATE, operations that change the घातer partition
 * state are NOT reference counted
 *
 * @note BPMP-FW क्रमcefully turns off some partitions as part of SC7 entry
 * because their state cannot be adequately restored on निकास. Thereक्रमe,
 * it is recommended to घातer off all करोमुख्यs via MRQ_PG prior to SC7 entry.
 * See @ref bpmp_pकरोमुख्य_ids क्रम further detail.
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_pg_request
 * * Response Payload: @ref mrq_pg_response
 *
 * @addtogroup Powergating
 * @अणु
 */
क्रमागत mrq_pg_cmd अणु
	/**
	 * @brief Check whether the BPMP driver supports the specअगरied
	 * request type
	 *
	 * mrq_response::err is 0 अगर the specअगरied request is
	 * supported and -#BPMP_ENODEV otherwise.
	 */
	CMD_PG_QUERY_ABI = 0,

	/**
	 * @brief Set the current state of specअगरied घातer करोमुख्य. The
	 * possible values क्रम घातer करोमुख्यs are defined in क्रमागत
	 * pg_states
	 *
	 * mrq_response:err is
	 * 0: Success
	 * -#BPMP_EINVAL: Invalid request parameters
	 */
	CMD_PG_SET_STATE = 1,

	/**
	 * @brief Get the current state of specअगरied घातer करोमुख्य. The
	 * possible values क्रम घातer करोमुख्यs are defined in क्रमागत
	 * pg_states
	 *
	 * mrq_response:err is
	 * 0: Success
	 * -#BPMP_EINVAL: Invalid request parameters
	 */
	CMD_PG_GET_STATE = 2,

	/**
	 * @brief Get the name string of specअगरied घातer करोमुख्य id.
	 *
	 * mrq_response:err is
	 * 0: Success
	 * -#BPMP_EINVAL: Invalid request parameters
	 */
	CMD_PG_GET_NAME = 3,


	/**
	 * @brief Get the highest घातer करोमुख्य id in the प्रणाली. Not
	 * all IDs between 0 and max_id are valid IDs.
	 *
	 * mrq_response:err is
	 * 0: Success
	 * -#BPMP_EINVAL: Invalid request parameters
	 */
	CMD_PG_GET_MAX_ID = 4,
पूर्ण;

#घोषणा MRQ_PG_NAME_MAXLEN	40

क्रमागत pg_states अणु
	/** @brief Power करोमुख्य is OFF */
	PG_STATE_OFF = 0,
	/** @brief Power करोमुख्य is ON */
	PG_STATE_ON = 1,
	/**
	 * @brief a legacy state where घातer करोमुख्य and the घड़ी
	 * associated to the करोमुख्य are ON.
	 * This state is only supported in T186, and the use of it is
	 * deprecated.
	 */
	PG_STATE_RUNNING = 2,
पूर्ण;

काष्ठा cmd_pg_query_abi_request अणु
	/** @ref mrq_pg_cmd */
	uपूर्णांक32_t type;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_pg_set_state_request अणु
	/** @ref pg_states */
	uपूर्णांक32_t state;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response data to #MRQ_PG sub command #CMD_PG_GET_STATE
 */
काष्ठा cmd_pg_get_state_response अणु
	/**
	 * @brief The state of the घातer partition that has been
	 * succesfuly requested by the master earlier using #MRQ_PG
	 * command #CMD_PG_SET_STATE.
	 *
	 * The state may not reflect the physical state of the घातer
	 * partition अगर there are some other masters requesting it to
	 * be enabled.
	 *
	 * See @ref pg_states क्रम possible values
	 */
	uपूर्णांक32_t state;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_pg_get_name_response अणु
	uपूर्णांक8_t name[MRQ_PG_NAME_MAXLEN];
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_pg_get_max_id_response अणु
	uपूर्णांक32_t max_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Request with #MRQ_PG
 *
 * Used by the sender of an #MRQ_PG message to control घातer
 * partitions. The pg_request is split पूर्णांकo several sub-commands. Some
 * sub-commands require no additional data. Others have a sub-command
 * specअगरic payload
 *
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |CMD_PG_QUERY_ABI            | query_abi             |
 * |CMD_PG_SET_STATE            | set_state             |
 * |CMD_PG_GET_STATE            | -                     |
 * |CMD_PG_GET_NAME             | -                     |
 * |CMD_PG_GET_MAX_ID           | -                     |
 *
 */
काष्ठा mrq_pg_request अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t id;
	जोड़ अणु
		काष्ठा cmd_pg_query_abi_request query_abi;
		काष्ठा cmd_pg_set_state_request set_state;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response to MRQ_PG
 *
 * Each sub-command supported by @ref mrq_pg_request may वापस
 * sub-command-specअगरic data. Some करो and some करो not as indicated in
 * the following table
 *
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |CMD_PG_QUERY_ABI            | -                     |
 * |CMD_PG_SET_STATE            | -                     |
 * |CMD_PG_GET_STATE            | get_state             |
 * |CMD_PG_GET_NAME             | get_name              |
 * |CMD_PG_GET_MAX_ID           | get_max_id            |
 */
काष्ठा mrq_pg_response अणु
	जोड़ अणु
		काष्ठा cmd_pg_get_state_response get_state;
		काष्ठा cmd_pg_get_name_response get_name;
		काष्ठा cmd_pg_get_max_id_response get_max_id;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_THERMAL
 * @brief Interact with BPMP thermal framework
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: Any
 * * Request Payload: TODO
 * * Response Payload: TODO
 *
 * @addtogroup Thermal
 *
 * The BPMP firmware includes a thermal framework. Drivers within the
 * bpmp firmware रेजिस्टर with the framework to provide thermal
 * zones. Each thermal zone corresponds to an entity whose temperature
 * can be measured. The framework also has a notion of trip poपूर्णांकs. A
 * trip poपूर्णांक consists of a thermal zone id, a temperature, and a
 * callback routine. The framework invokes the callback when the zone
 * hits the indicated temperature. The BPMP firmware uses this thermal
 * framework पूर्णांकerally to implement various temperature-dependent
 * functions.
 *
 * Software on the CPU can use #MRQ_THERMAL (with payload @ref
 * mrq_thermal_host_to_bpmp_request) to पूर्णांकeract with the BPMP thermal
 * framework. The CPU must It can query the number of supported zones,
 * query zone temperatures, and set trip poपूर्णांकs.
 *
 * When a trip poपूर्णांक set by the CPU माला_लो crossed, BPMP firmware issues
 * an IPC to the CPU having mrq_request::mrq = #MRQ_THERMAL and a
 * payload of @ref mrq_thermal_bpmp_to_host_request.
 * @अणु
 */
क्रमागत mrq_thermal_host_to_bpmp_cmd अणु
	/**
	 * @brief Check whether the BPMP driver supports the specअगरied
	 * request type.
	 *
	 * Host needs to supply request parameters.
	 *
	 * mrq_response::err is 0 अगर the specअगरied request is
	 * supported and -#BPMP_ENODEV otherwise.
	 */
	CMD_THERMAL_QUERY_ABI = 0,

	/**
	 * @brief Get the current temperature of the specअगरied zone.
	 *
	 * Host needs to supply request parameters.
	 *
	 * mrq_response::err is
	 * *  0: Temperature query succeeded.
	 * *  -#BPMP_EINVAL: Invalid request parameters.
	 * *  -#BPMP_ENOENT: No driver रेजिस्टरed क्रम thermal zone..
	 * *  -#BPMP_EFAULT: Problem पढ़ोing temperature measurement.
	 */
	CMD_THERMAL_GET_TEMP = 1,

	/**
	 * @brief Enable or disable and set the lower and upper
	 *   thermal limits क्रम a thermal trip poपूर्णांक. Each zone has
	 *   one trip poपूर्णांक.
	 *
	 * Host needs to supply request parameters. Once the
	 * temperature hits a trip poपूर्णांक, the BPMP will send a message
	 * to the CPU having MRQ=MRQ_THERMAL and
	 * type=CMD_THERMAL_HOST_TRIP_REACHED
	 *
	 * mrq_response::err is
	 * *  0: Trip successfully set.
	 * *  -#BPMP_EINVAL: Invalid request parameters.
	 * *  -#BPMP_ENOENT: No driver रेजिस्टरed क्रम thermal zone.
	 * *  -#BPMP_EFAULT: Problem setting trip poपूर्णांक.
	 */
	CMD_THERMAL_SET_TRIP = 2,

	/**
	 * @brief Get the number of supported thermal zones.
	 *
	 * No request parameters required.
	 *
	 * mrq_response::err is always 0, indicating success.
	 */
	CMD_THERMAL_GET_NUM_ZONES = 3,

	/**
	 * @brief Get the thermtrip of the specअगरied zone.
	 *
	 * Host needs to supply request parameters.
	 *
	 * mrq_response::err is
	 * *  0: Valid zone inक्रमmation वापसed.
	 * *  -#BPMP_EINVAL: Invalid request parameters.
	 * *  -#BPMP_ENOENT: No driver रेजिस्टरed क्रम thermal zone.
	 * *  -#BPMP_दुस्फल अगर thermtrip is invalid or disabled.
	 * *  -#BPMP_EFAULT: Problem पढ़ोing zone inक्रमmation.
	 */
	CMD_THERMAL_GET_THERMTRIP = 4,

	/** @brief: number of supported host-to-bpmp commands. May
	 * increase in future
	 */
	CMD_THERMAL_HOST_TO_BPMP_NUM
पूर्ण;

क्रमागत mrq_thermal_bpmp_to_host_cmd अणु
	/**
	 * @brief Indication that the temperature क्रम a zone has
	 *   exceeded the range indicated in the thermal trip poपूर्णांक
	 *   क्रम the zone.
	 *
	 * BPMP needs to supply request parameters. Host only needs to
	 * acknowledge.
	 */
	CMD_THERMAL_HOST_TRIP_REACHED = 100,

	/** @brief: number of supported bpmp-to-host commands. May
	 * increase in future
	 */
	CMD_THERMAL_BPMP_TO_HOST_NUM
पूर्ण;

/*
 * Host->BPMP request data क्रम request type CMD_THERMAL_QUERY_ABI
 *
 * zone: Request type क्रम which to check existence.
 */
काष्ठा cmd_thermal_query_abi_request अणु
	uपूर्णांक32_t type;
पूर्ण BPMP_ABI_PACKED;

/*
 * Host->BPMP request data क्रम request type CMD_THERMAL_GET_TEMP
 *
 * zone: Number of thermal zone.
 */
काष्ठा cmd_thermal_get_temp_request अणु
	uपूर्णांक32_t zone;
पूर्ण BPMP_ABI_PACKED;

/*
 * BPMP->Host reply data क्रम request CMD_THERMAL_GET_TEMP
 *
 * error: 0 अगर request succeeded.
 *	-BPMP_EINVAL अगर request parameters were invalid.
 *      -BPMP_ENOENT अगर no driver was रेजिस्टरed क्रम the specअगरied thermal zone.
 *      -BPMP_EFAULT क्रम other thermal zone driver errors.
 * temp: Current temperature in millicelsius.
 */
काष्ठा cmd_thermal_get_temp_response अणु
	पूर्णांक32_t temp;
पूर्ण BPMP_ABI_PACKED;

/*
 * Host->BPMP request data क्रम request type CMD_THERMAL_SET_TRIP
 *
 * zone: Number of thermal zone.
 * low: Temperature of lower trip poपूर्णांक in millicelsius
 * high: Temperature of upper trip poपूर्णांक in millicelsius
 * enabled: 1 to enable trip poपूर्णांक, 0 to disable trip poपूर्णांक
 */
काष्ठा cmd_thermal_set_trip_request अणु
	uपूर्णांक32_t zone;
	पूर्णांक32_t low;
	पूर्णांक32_t high;
	uपूर्णांक32_t enabled;
पूर्ण BPMP_ABI_PACKED;

/*
 * BPMP->Host request data क्रम request type CMD_THERMAL_HOST_TRIP_REACHED
 *
 * zone: Number of thermal zone where trip poपूर्णांक was reached.
 */
काष्ठा cmd_thermal_host_trip_reached_request अणु
	uपूर्णांक32_t zone;
पूर्ण BPMP_ABI_PACKED;

/*
 * BPMP->Host reply data क्रम request type CMD_THERMAL_GET_NUM_ZONES
 *
 * num: Number of supported thermal zones. The thermal zones are indexed
 *      starting from zero.
 */
काष्ठा cmd_thermal_get_num_zones_response अणु
	uपूर्णांक32_t num;
पूर्ण BPMP_ABI_PACKED;

/*
 * Host->BPMP request data क्रम request type CMD_THERMAL_GET_THERMTRIP
 *
 * zone: Number of thermal zone.
 */
काष्ठा cmd_thermal_get_thermtrip_request अणु
	uपूर्णांक32_t zone;
पूर्ण BPMP_ABI_PACKED;

/*
 * BPMP->Host reply data क्रम request CMD_THERMAL_GET_THERMTRIP
 *
 * thermtrip: HW shutकरोwn temperature in millicelsius.
 */
काष्ठा cmd_thermal_get_thermtrip_response अणु
	पूर्णांक32_t thermtrip;
पूर्ण BPMP_ABI_PACKED;

/*
 * Host->BPMP request data.
 *
 * Reply type is जोड़ mrq_thermal_bpmp_to_host_response.
 *
 * type: Type of request. Values listed in क्रमागत mrq_thermal_type.
 * data: Request type specअगरic parameters.
 */
काष्ठा mrq_thermal_host_to_bpmp_request अणु
	uपूर्णांक32_t type;
	जोड़ अणु
		काष्ठा cmd_thermal_query_abi_request query_abi;
		काष्ठा cmd_thermal_get_temp_request get_temp;
		काष्ठा cmd_thermal_set_trip_request set_trip;
		काष्ठा cmd_thermal_get_thermtrip_request get_thermtrip;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/*
 * BPMP->Host request data.
 *
 * type: Type of request. Values listed in क्रमागत mrq_thermal_type.
 * data: Request type specअगरic parameters.
 */
काष्ठा mrq_thermal_bpmp_to_host_request अणु
	uपूर्णांक32_t type;
	जोड़ अणु
		काष्ठा cmd_thermal_host_trip_reached_request host_trip_reached;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/*
 * Data in reply to a Host->BPMP request.
 */
जोड़ mrq_thermal_bpmp_to_host_response अणु
	काष्ठा cmd_thermal_get_temp_response get_temp;
	काष्ठा cmd_thermal_get_thermtrip_response get_thermtrip;
	काष्ठा cmd_thermal_get_num_zones_response get_num_zones;
पूर्ण BPMP_ABI_PACKED;
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_CPU_VHINT
 * @brief Query CPU voltage hपूर्णांक data
 *
 * * Platक्रमms: T186
 * @cond bpmp_t186
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_cpu_vhपूर्णांक_request
 * * Response Payload: N/A
 *
 * @addtogroup Vhपूर्णांक
 * @अणु
 */

/**
 * @brief Request with #MRQ_CPU_VHINT
 *
 * Used by #MRQ_CPU_VHINT call by CCPLEX to retrieve voltage hपूर्णांक data
 * from BPMP to memory space poपूर्णांकed by #addr. CCPLEX is responsible
 * to allocate माप(cpu_vhपूर्णांक_data) sized block of memory and
 * appropriately map it क्रम BPMP beक्रमe sending the request.
 */
काष्ठा mrq_cpu_vhपूर्णांक_request अणु
	/** @brief IOVA address क्रम the #cpu_vhपूर्णांक_data */
	uपूर्णांक32_t addr;
	/** @brief ID of the cluster whose data is requested */
	uपूर्णांक32_t cluster_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Description of the CPU v/f relation
 *
 * Used by #MRQ_CPU_VHINT call to carry data poपूर्णांकed by
 * #mrq_cpu_vhपूर्णांक_request::addr
 */
काष्ठा cpu_vhपूर्णांक_data अणु
	uपूर्णांक32_t ref_clk_hz; /**< reference frequency in Hz */
	uपूर्णांक16_t pभाग; /**< post भागider value */
	uपूर्णांक16_t mभाग; /**< input भागider value */
	uपूर्णांक16_t nभाग_max; /**< fMAX expressed with max NDIV value */
	/** table of nभाग values as a function of vINDEX (voltage index) */
	uपूर्णांक16_t nभाग[80];
	/** minimum allowed NDIV value */
	uपूर्णांक16_t nभाग_min;
	/** minimum allowed voltage hपूर्णांक value (as in vINDEX) */
	uपूर्णांक16_t vन्यूनमान;
	/** maximum allowed voltage hपूर्णांक value (as in vINDEX) */
	uपूर्णांक16_t vउच्चमान;
	/** post-multiplier क्रम vindex value */
	uपूर्णांक16_t vindex_mult;
	/** post-भागider क्रम vindex value */
	uपूर्णांक16_t vindex_भाग;
	/** reserved क्रम future use */
	uपूर्णांक16_t reserved[328];
पूर्ण BPMP_ABI_PACKED;
/** @endcond */
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_ABI_RATCHET
 * @brief ABI ratchet value query
 *
 * * Platक्रमms: T186, T194
 * * Initiators: Any
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_abi_ratchet_request
 * * Response Payload: @ref mrq_abi_ratchet_response
 * @addtogroup ABI_info
 * @अणु
 */

/**
 * @brief An ABI compatibility mechanism
 *
 * BPMP_ABI_RATCHET_VALUE may increase क्रम various reasons in a future
 * revision of this header file.
 * 1. That future revision deprecates some MRQ
 * 2. That future revision पूर्णांकroduces a अवरोधing change to an existing
 *    MRQ or
 * 3. A bug is discovered in an existing implementation of the BPMP-FW
 *    (or possibly one of its clients) which warrants deprecating that
 *    implementation.
 */
#घोषणा BPMP_ABI_RATCHET_VALUE 3

/**
 * @brief Request with #MRQ_ABI_RATCHET.
 *
 * #ratchet should be #BPMP_ABI_RATCHET_VALUE from the ABI header
 * against which the requester was compiled.
 *
 * If ratchet is less than BPMP's #BPMP_ABI_RATCHET_VALUE, BPMP may
 * reply with mrq_response::err = -#BPMP_दुस्फल to indicate that
 * BPMP-FW cannot पूर्णांकeroperate correctly with the requester. Requester
 * should cease further communication with BPMP.
 *
 * Otherwise, err shall be 0.
 */
काष्ठा mrq_abi_ratchet_request अणु
	/** @brief Requester's ratchet value */
	uपूर्णांक16_t ratchet;
पूर्ण;

/**
 * @brief Response to #MRQ_ABI_RATCHET
 *
 * #ratchet shall be #BPMP_ABI_RATCHET_VALUE from the ABI header
 * against which BPMP firwmare was compiled.
 *
 * If #ratchet is less than the requester's #BPMP_ABI_RATCHET_VALUE,
 * the requster must either पूर्णांकeroperate with BPMP according to an ABI
 * header version with BPMP_ABI_RATCHET_VALUE = ratchet or cease
 * communication with BPMP.
 *
 * If mrq_response::err is 0 and ratchet is greater than or equal to the
 * requester's BPMP_ABI_RATCHET_VALUE, the requester should जारी
 * normal operation.
 */
काष्ठा mrq_abi_ratchet_response अणु
	/** @brief BPMP's ratchet value */
	uपूर्णांक16_t ratchet;
पूर्ण;
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_EMC_DVFS_LATENCY
 * @brief Query frequency dependent EMC DVFS latency
 *
 * * Platक्रमms: T186, T194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: N/A
 * * Response Payload: @ref mrq_emc_dvfs_latency_response
 * @addtogroup EMC
 * @अणु
 */

/**
 * @brief Used by @ref mrq_emc_dvfs_latency_response
 */
काष्ठा emc_dvfs_latency अणु
	/** @brief EMC DVFS node frequency in kHz */
	uपूर्णांक32_t freq;
	/** @brief EMC DVFS latency in nanoseconds */
	uपूर्णांक32_t latency;
पूर्ण BPMP_ABI_PACKED;

#घोषणा EMC_DVFS_LATENCY_MAX_SIZE	14
/**
 * @brief Response to #MRQ_EMC_DVFS_LATENCY
 */
काष्ठा mrq_emc_dvfs_latency_response अणु
	/** @brief The number valid entries in #pairs */
	uपूर्णांक32_t num_pairs;
	/** @brief EMC DVFS node <frequency, latency> inक्रमmation */
	काष्ठा emc_dvfs_latency pairs[EMC_DVFS_LATENCY_MAX_SIZE];
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_CPU_NDIV_LIMITS
 * @brief CPU freq. limits in nभाग
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_cpu_nभाग_limits_request
 * * Response Payload: @ref mrq_cpu_nभाग_limits_response
 * @addtogroup CPU
 * @अणु
 */

/**
 * @brief Request क्रम nभाग limits of a cluster
 */
काष्ठा mrq_cpu_nभाग_limits_request अणु
	/** @brief Enum cluster_id */
	uपूर्णांक32_t cluster_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response to #MRQ_CPU_NDIV_LIMITS
 */
काष्ठा mrq_cpu_nभाग_limits_response अणु
	/** @brief Reference frequency in Hz */
	uपूर्णांक32_t ref_clk_hz;
	/** @brief Post भागider value */
	uपूर्णांक16_t pभाग;
	/** @brief Input भागider value */
	uपूर्णांक16_t mभाग;
	/** @brief FMAX expressed with max NDIV value */
	uपूर्णांक16_t nभाग_max;
	/** @brief Minimum allowed NDIV value */
	uपूर्णांक16_t nभाग_min;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_CPU_AUTO_CC3
 * @brief Query CPU cluster स्वतः-CC3 configuration
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_cpu_स्वतः_cc3_request
 * * Response Payload: @ref mrq_cpu_स्वतः_cc3_response
 * @addtogroup CC3
 *
 * Queries from BPMP स्वतः-CC3 configuration (allowed/not allowed) क्रम a
 * specअगरied cluster. CCPLEX s/w uses this inक्रमmation to override its own
 * device tree स्वतः-CC3 settings, so that BPMP device tree is a single source of
 * स्वतः-CC3 platक्रमm configuration.
 *
 * @अणु
 */

/**
 * @brief Request क्रम स्वतः-CC3 configuration of a cluster
 */
काष्ठा mrq_cpu_स्वतः_cc3_request अणु
	/** @brief Enum cluster_id (logical cluster id, known to CCPLEX s/w) */
	uपूर्णांक32_t cluster_id;
पूर्ण BPMP_ABI_PACKED;

/**
 * @brief Response to #MRQ_CPU_AUTO_CC3
 */
काष्ठा mrq_cpu_स्वतः_cc3_response अणु
	/**
	 * @brief स्वतः-CC3 configuration
	 *
	 * - bits[31..10] reserved.
	 * - bits[9..1] cc3 nभाग
	 * - bit [0] अगर "1" स्वतः-CC3 is allowed, अगर "0" स्वतः-CC3 is not allowed
	 */
	uपूर्णांक32_t स्वतः_cc3_config;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_TRACE_ITER
 * @brief Manage the trace iterator
 *
 * @deprecated
 *
 * * Platक्रमms: All
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: N/A
 * * Response Payload: @ref mrq_trace_iter_request
 * @addtogroup Trace
 * @अणु
 */
क्रमागत अणु
	/** @brief (re)start the tracing now. Ignore older events */
	TRACE_ITER_INIT = 0,
	/** @brief Clobber all events in the trace buffer */
	TRACE_ITER_CLEAN = 1
पूर्ण;

/**
 * @brief Request with #MRQ_TRACE_ITER
 */
काष्ठा mrq_trace_iter_request अणु
	/** @brief TRACE_ITER_INIT or TRACE_ITER_CLEAN */
	uपूर्णांक32_t cmd;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_RINGBUF_CONSOLE
 * @brief A ring buffer debug console क्रम BPMP
 * @addtogroup RingbufConsole
 *
 * The ring buffer debug console aims to be a substitute क्रम the UART debug
 * console. The debug console is implemented with two ring buffers in the
 * BPMP-FW, the RX (receive) and TX (transmit) buffers. Characters can be पढ़ो
 * and written to the buffers by the host via the MRQ पूर्णांकerface.
 *
 * @अणु
 */

/**
 * @brief Maximum number of bytes transferred in a single ग_लिखो command to the
 * BPMP
 *
 * This is determined by the number of मुक्त bytes in the message काष्ठा,
 * rounded करोwn to a multiple of four.
 */
#घोषणा MRQ_RINGBUF_CONSOLE_MAX_WRITE_LEN 112

/**
 * @brief Maximum number of bytes transferred in a single पढ़ो command to the
 * BPMP
 *
 * This is determined by the number of मुक्त bytes in the message काष्ठा,
 * rounded करोwn to a multiple of four.
 */
#घोषणा MRQ_RINGBUF_CONSOLE_MAX_READ_LEN 116

क्रमागत mrq_ringbuf_console_host_to_bpmp_cmd अणु
	/**
	 * @brief Check whether the BPMP driver supports the specअगरied request
	 * type
	 *
	 * mrq_response::err is 0 अगर the specअगरied request is supported and
	 * -#BPMP_ENODEV otherwise
	 */
	CMD_RINGBUF_CONSOLE_QUERY_ABI = 0,
	/**
	 * @brief Perक्रमm a पढ़ो operation on the BPMP TX buffer
	 *
	 * mrq_response::err is 0
	 */
	CMD_RINGBUF_CONSOLE_READ = 1,
	/**
	 * @brief Perक्रमm a ग_लिखो operation on the BPMP RX buffer
	 *
	 * mrq_response::err is 0 अगर the operation was successful and
	 * -#BPMP_ENODEV otherwise
	 */
	CMD_RINGBUF_CONSOLE_WRITE = 2,
	/**
	 * @brief Get the length of the buffer and the physical addresses of
	 * the buffer data and the head and tail counters
	 *
	 * mrq_response::err is 0 अगर the operation was successful and
	 * -#BPMP_ENODEV otherwise
	 */
	CMD_RINGBUF_CONSOLE_GET_FIFO = 3,
पूर्ण;

/**
 * @ingroup RingbufConsole
 * @brief Host->BPMP request data क्रम request type
 * #CMD_RINGBUF_CONSOLE_QUERY_ABI
 */
काष्ठा cmd_ringbuf_console_query_abi_req अणु
	/** @brief Command identअगरier to be queried */
	uपूर्णांक32_t cmd;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_ringbuf_console_query_abi_resp अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief Host->BPMP request data क्रम request type #CMD_RINGBUF_CONSOLE_READ
 */
काष्ठा cmd_ringbuf_console_पढ़ो_req अणु
	/**
	 * @brief Number of bytes requested to be पढ़ो from the BPMP TX buffer
	 */
	uपूर्णांक8_t len;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief BPMP->Host response data क्रम request type #CMD_RINGBUF_CONSOLE_READ
 */
काष्ठा cmd_ringbuf_console_पढ़ो_resp अणु
	/** @brief The actual data पढ़ो from the BPMP TX buffer */
	uपूर्णांक8_t data[MRQ_RINGBUF_CONSOLE_MAX_READ_LEN];
	/** @brief Number of bytes in cmd_ringbuf_console_पढ़ो_resp::data */
	uपूर्णांक8_t len;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief Host->BPMP request data क्रम request type #CMD_RINGBUF_CONSOLE_WRITE
 */
काष्ठा cmd_ringbuf_console_ग_लिखो_req अणु
	/** @brief The actual data to be written to the BPMP RX buffer */
	uपूर्णांक8_t data[MRQ_RINGBUF_CONSOLE_MAX_WRITE_LEN];
	/** @brief Number of bytes in cmd_ringbuf_console_ग_लिखो_req::data */
	uपूर्णांक8_t len;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief BPMP->Host response data क्रम request type #CMD_RINGBUF_CONSOLE_WRITE
 */
काष्ठा cmd_ringbuf_console_ग_लिखो_resp अणु
	/** @brief Number of bytes of available space in the BPMP RX buffer */
	uपूर्णांक32_t space_avail;
	/** @brief Number of bytes that were written to the BPMP RX buffer */
	uपूर्णांक8_t len;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_ringbuf_console_get_fअगरo_req अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief BPMP->Host reply data क्रम request type #CMD_RINGBUF_CONSOLE_GET_FIFO
 */
काष्ठा cmd_ringbuf_console_get_fअगरo_resp अणु
	/** @brief Physical address of the BPMP TX buffer */
	uपूर्णांक64_t bpmp_tx_buf_addr;
	/** @brief Physical address of the BPMP TX buffer head counter */
	uपूर्णांक64_t bpmp_tx_head_addr;
	/** @brief Physical address of the BPMP TX buffer tail counter */
	uपूर्णांक64_t bpmp_tx_tail_addr;
	/** @brief Length of the BPMP TX buffer */
	uपूर्णांक32_t bpmp_tx_buf_len;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief Host->BPMP request data.
 *
 * Reply type is जोड़ #mrq_ringbuf_console_bpmp_to_host_response .
 */
काष्ठा mrq_ringbuf_console_host_to_bpmp_request अणु
	/**
	 * @brief Type of request. Values listed in क्रमागत
	 * #mrq_ringbuf_console_host_to_bpmp_cmd.
	 */
	uपूर्णांक32_t type;
	/** @brief  request type specअगरic parameters. */
	जोड़ अणु
		काष्ठा cmd_ringbuf_console_query_abi_req query_abi;
		काष्ठा cmd_ringbuf_console_पढ़ो_req पढ़ो;
		काष्ठा cmd_ringbuf_console_ग_लिखो_req ग_लिखो;
		काष्ठा cmd_ringbuf_console_get_fअगरo_req get_fअगरo;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup RingbufConsole
 * @brief Host->BPMP reply data
 *
 * In response to काष्ठा #mrq_ringbuf_console_host_to_bpmp_request.
 */
जोड़ mrq_ringbuf_console_bpmp_to_host_response अणु
	काष्ठा cmd_ringbuf_console_query_abi_resp query_abi;
	काष्ठा cmd_ringbuf_console_पढ़ो_resp पढ़ो;
	काष्ठा cmd_ringbuf_console_ग_लिखो_resp ग_लिखो;
	काष्ठा cmd_ringbuf_console_get_fअगरo_resp get_fअगरo;
पूर्ण BPMP_ABI_PACKED;
/** @पूर्ण */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_STRAP
 * @brief Set a strap value controlled by BPMP
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_strap_request
 * * Response Payload: N/A
 * @addtogroup Strap
 *
 * A strap is an input that is sampled by a hardware unit during the
 * unit's startup process. The sampled value of a strap affects the
 * behavior of the unit until the unit is restarted. Many hardware
 * units sample their straps at the instant that their resets are
 * deनिश्चितed.
 *
 * BPMP owns रेजिस्टरs which act as straps to various units. It
 * exposes limited control of those straps via #MRQ_STRAP.
 *
 * @अणु
 */
क्रमागत mrq_strap_cmd अणु
	/** @निजी */
	STRAP_RESERVED = 0,
	/** @brief Set a strap value */
	STRAP_SET = 1
पूर्ण;

/**
 * @brief Request with #MRQ_STRAP
 */
काष्ठा mrq_strap_request अणु
	/** @brief @ref mrq_strap_cmd */
	uपूर्णांक32_t cmd;
	/** @brief Strap ID from @ref Strap_Ids */
	uपूर्णांक32_t id;
	/** @brief Desired value क्रम strap (अगर cmd is #STRAP_SET) */
	uपूर्णांक32_t value;
पूर्ण BPMP_ABI_PACKED;

/**
 * @defgroup Strap_Ids Strap Identअगरiers
 * @पूर्ण
 */
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_UPHY
 * @brief Perक्रमm a UPHY operation
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_uphy_request
 * * Response Payload: @ref mrq_uphy_response
 *
 * @addtogroup UPHY
 * @अणु
 */
क्रमागत अणु
	CMD_UPHY_PCIE_LANE_MARGIN_CONTROL = 1,
	CMD_UPHY_PCIE_LANE_MARGIN_STATUS = 2,
	CMD_UPHY_PCIE_EP_CONTROLLER_PLL_INIT = 3,
	CMD_UPHY_PCIE_CONTROLLER_STATE = 4,
	CMD_UPHY_PCIE_EP_CONTROLLER_PLL_OFF = 5,
	CMD_UPHY_MAX,
पूर्ण;

काष्ठा cmd_uphy_margin_control_request अणु
	/** @brief Enable margin */
	पूर्णांक32_t en;
	/** @brief Clear the number of error and sections */
	पूर्णांक32_t clr;
	/** @brief Set x offset (1's complement) क्रम left/right margin type (y should be 0) */
	uपूर्णांक32_t x;
	/** @brief Set y offset (1's complement) क्रम left/right margin type (x should be 0) */
	uपूर्णांक32_t y;
	/** @brief Set number of bit blocks क्रम each margin section */
	uपूर्णांक32_t nblks;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_uphy_margin_status_response अणु
	/** @brief Number of errors observed */
	uपूर्णांक32_t status;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_uphy_ep_controller_pll_init_request अणु
	/** @brief EP controller number, valid: 0, 4, 5 */
	uपूर्णांक8_t ep_controller;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_uphy_pcie_controller_state_request अणु
	/** @brief PCIE controller number, valid: 0, 1, 2, 3, 4 */
	uपूर्णांक8_t pcie_controller;
	uपूर्णांक8_t enable;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_uphy_ep_controller_pll_off_request अणु
	/** @brief EP controller number, valid: 0, 4, 5 */
	uपूर्णांक8_t ep_controller;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup UPHY
 * @brief Request with #MRQ_UPHY
 *
 * Used by the sender of an #MRQ_UPHY message to control UPHY Lane RX margining.
 * The uphy_request is split पूर्णांकo several sub-commands. Some sub-commands
 * require no additional data. Others have a sub-command specअगरic payload
 *
 * |sub-command                          |payload                                 |
 * |------------------------------------ |----------------------------------------|
 * |CMD_UPHY_PCIE_LANE_MARGIN_CONTROL    |uphy_set_margin_control                 |
 * |CMD_UPHY_PCIE_LANE_MARGIN_STATUS     |                                        |
 * |CMD_UPHY_PCIE_EP_CONTROLLER_PLL_INIT |cmd_uphy_ep_controller_pll_init_request |
 * |CMD_UPHY_PCIE_CONTROLLER_STATE       |cmd_uphy_pcie_controller_state_request  |
 * |CMD_UPHY_PCIE_EP_CONTROLLER_PLL_OFF  |cmd_uphy_ep_controller_pll_off_request  |
 *
 */

काष्ठा mrq_uphy_request अणु
	/** @brief Lane number. */
	uपूर्णांक16_t lane;
	/** @brief Sub-command id. */
	uपूर्णांक16_t cmd;

	जोड़ अणु
		काष्ठा cmd_uphy_margin_control_request uphy_set_margin_control;
		काष्ठा cmd_uphy_ep_controller_pll_init_request ep_ctrlr_pll_init;
		काष्ठा cmd_uphy_pcie_controller_state_request controller_state;
		काष्ठा cmd_uphy_ep_controller_pll_off_request ep_ctrlr_pll_off;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup UPHY
 * @brief Response to MRQ_UPHY
 *
 * Each sub-command supported by @ref mrq_uphy_request may वापस
 * sub-command-specअगरic data. Some करो and some करो not as indicated in
 * the following table
 *
 * |sub-command                       |payload                 |
 * |----------------------------      |------------------------|
 * |CMD_UPHY_PCIE_LANE_MARGIN_CONTROL |                        |
 * |CMD_UPHY_PCIE_LANE_MARGIN_STATUS  |uphy_get_margin_status  |
 *
 */

काष्ठा mrq_uphy_response अणु
	जोड़ अणु
		काष्ठा cmd_uphy_margin_status_response uphy_get_margin_status;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_FMON
 * @brief Perक्रमm a frequency monitor configuration operations
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_fmon_request
 * * Response Payload: @ref mrq_fmon_response
 *
 * @addtogroup FMON
 * @अणु
 */
क्रमागत अणु
	/**
	 * @brief Clamp FMON configuration to specअगरied rate.
	 *
	 * The monitored घड़ी must be running क्रम clamp to succeed. If
	 * clamped, FMON configuration is preserved when घड़ी rate
	 * and/or state is changed.
	 */
	CMD_FMON_GEAR_CLAMP = 1,
	/**
	 * @brief Release clamped FMON configuration.
	 *
	 * Allow FMON configuration to follow monitored घड़ी rate
	 * and/or state changes.
	 */
	CMD_FMON_GEAR_FREE = 2,
	/**
	 * @brief Return rate FMON is clamped at, or 0 अगर FMON is not
	 *         clamped.
	 *
	 * Inherently racy, since clamp state can be changed
	 * concurrently. Useful क्रम testing.
	 */
	CMD_FMON_GEAR_GET = 3,
	CMD_FMON_NUM,
पूर्ण;

काष्ठा cmd_fmon_gear_clamp_request अणु
	पूर्णांक32_t unused;
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_fmon_gear_clamp_response अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_fmon_gear_मुक्त_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_fmon_gear_मुक्त_response अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

/** @निजी */
काष्ठा cmd_fmon_gear_get_request अणु
	BPMP_ABI_EMPTY
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_fmon_gear_get_response अणु
	पूर्णांक64_t rate;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup FMON
 * @brief Request with #MRQ_FMON
 *
 * Used by the sender of an #MRQ_FMON message to configure घड़ी
 * frequency monitors. The FMON request is split पूर्णांकo several
 * sub-commands. Some sub-commands require no additional data.
 * Others have a sub-command specअगरic payload
 *
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |CMD_FMON_GEAR_CLAMP         |fmon_gear_clamp        |
 * |CMD_FMON_GEAR_FREE          |-                      |
 * |CMD_FMON_GEAR_GET           |-                      |
 *
 */

काष्ठा mrq_fmon_request अणु
	/** @brief Sub-command and घड़ी id concatenated to 32-bit word.
	 * - bits[31..24] is the sub-cmd.
	 * - bits[23..0] is monitored घड़ी id used to select target
	 *   FMON
	 */
	uपूर्णांक32_t cmd_and_id;

	जोड़ अणु
		काष्ठा cmd_fmon_gear_clamp_request fmon_gear_clamp;
		/** @निजी */
		काष्ठा cmd_fmon_gear_मुक्त_request fmon_gear_मुक्त;
		/** @निजी */
		काष्ठा cmd_fmon_gear_get_request fmon_gear_get;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup FMON
 * @brief Response to MRQ_FMON
 *
 * Each sub-command supported by @ref mrq_fmon_request may
 * वापस sub-command-specअगरic data as indicated below.
 *
 * |sub-command                 |payload                 |
 * |----------------------------|------------------------|
 * |CMD_FMON_GEAR_CLAMP         |-                       |
 * |CMD_FMON_GEAR_FREE          |-                       |
 * |CMD_FMON_GEAR_GET           |fmon_gear_get           |
 *
 */

काष्ठा mrq_fmon_response अणु
	जोड़ अणु
		/** @निजी */
		काष्ठा cmd_fmon_gear_clamp_response fmon_gear_clamp;
		/** @निजी */
		काष्ठा cmd_fmon_gear_मुक्त_response fmon_gear_मुक्त;
		काष्ठा cmd_fmon_gear_get_response fmon_gear_get;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */
/** @endcond */

/**
 * @ingroup MRQ_Codes
 * @def MRQ_EC
 * @brief Provide status inक्रमmation on faults reported by Error
 *        Collator (EC) to HSM.
 *
 * * Platक्रमms: T194 onwards
 * @cond bpmp_t194
 * * Initiators: CCPLEX
 * * Tarमाला_लो: BPMP
 * * Request Payload: @ref mrq_ec_request
 * * Response Payload: @ref mrq_ec_response
 *
 * @note This MRQ ABI is under स्थिरruction, and subject to change
 *
 * @addtogroup EC
 * @अणु
 */
क्रमागत अणु
	/**
	 * @cond DEPRECATED
	 * @brief Retrieve specअगरied EC status.
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_ENODEV अगर target EC is not owned by BPMP @n
	 * -#BPMP_EACCES अगर target EC घातer करोमुख्य is turned off @n
	 * -#BPMP_EBADCMD अगर subcommand is not supported
	 * @endcond
	 */
	CMD_EC_STATUS_GET = 1,	/* deprecated */

	/**
	 * @brief Retrieve specअगरied EC extended status (includes error
	 *        counter and user values).
	 *
	 * mrq_response::err is 0 अगर the operation was successful, or @n
	 * -#BPMP_ENODEV अगर target EC is not owned by BPMP @n
	 * -#BPMP_EACCES अगर target EC घातer करोमुख्य is turned off @n
	 * -#BPMP_EBADCMD अगर subcommand is not supported
	 */
	CMD_EC_STATUS_EX_GET = 2,
	CMD_EC_NUM,
पूर्ण;

/** @brief BPMP ECs error types */
क्रमागत bpmp_ec_err_type अणु
	/** @brief Parity error on पूर्णांकernal data path
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_PARITY_INTERNAL		= 1,

	/** @brief ECC SEC error on पूर्णांकernal data path
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_ECC_SEC_INTERNAL		= 2,

	/** @brief ECC DED error on पूर्णांकernal data path
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_ECC_DED_INTERNAL		= 3,

	/** @brief Comparator error
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_COMPARATOR			= 4,

	/** @brief Register parity error
	 *
	 *  Error descriptor @ref ec_err_reg_parity_desc.
	 */
	EC_ERR_TYPE_REGISTER_PARITY		= 5,

	/** @brief Parity error from on-chip SRAM/FIFO
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_PARITY_SRAM			= 6,

	/** @brief Clock Monitor error
	 *
	 *  Error descriptor @ref ec_err_fmon_desc.
	 */
	EC_ERR_TYPE_CLOCK_MONITOR		= 9,

	/** @brief Voltage Monitor error
	 *
	 *  Error descriptor @ref ec_err_vmon_desc.
	 */
	EC_ERR_TYPE_VOLTAGE_MONITOR		= 10,

	/** @brief SW Correctable error
	 *
	 *  Error descriptor @ref ec_err_sw_error_desc.
	 */
	EC_ERR_TYPE_SW_CORRECTABLE		= 16,

	/** @brief SW Uncorrectable error
	 *
	 *  Error descriptor @ref ec_err_sw_error_desc.
	 */
	EC_ERR_TYPE_SW_UNCORRECTABLE		= 17,

	/** @brief Other HW Correctable error
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_OTHER_HW_CORRECTABLE	= 32,

	/** @brief Other HW Uncorrectable error
	 *
	 *  Error descriptor @ref ec_err_simple_desc.
	 */
	EC_ERR_TYPE_OTHER_HW_UNCORRECTABLE	= 33,
पूर्ण;

/** @brief Group of रेजिस्टरs with parity error. */
क्रमागत ec_रेजिस्टरs_group अणु
	/** @brief Functional रेजिस्टरs group */
	EC_ERR_GROUP_FUNC_REG		= 0U,
	/** @brief SCR रेजिस्टरs group */
	EC_ERR_GROUP_SCR_REG		= 1U,
पूर्ण;

/**
 * @defgroup bpmp_ec_status_flags EC Status Flags
 * @addtogroup bpmp_ec_status_flags
 * @अणु
 */
/** @brief No EC error found flag */
#घोषणा EC_STATUS_FLAG_NO_ERROR		0x0001U
/** @brief Last EC error found flag */
#घोषणा EC_STATUS_FLAG_LAST_ERROR	0x0002U
/** @brief EC latent error flag */
#घोषणा EC_STATUS_FLAG_LATENT_ERROR	0x0004U
/** @पूर्ण */

/**
 * @defgroup bpmp_ec_desc_flags EC Descriptor Flags
 * @addtogroup bpmp_ec_desc_flags
 * @अणु
 */
/** @brief EC descriptor error resolved flag */
#घोषणा EC_DESC_FLAG_RESOLVED		0x0001U
/** @brief EC descriptor failed to retrieve id flag */
#घोषणा EC_DESC_FLAG_NO_ID		0x0002U
/** @पूर्ण */

/**
 * |error type                       | fmon_clk_id values        |
 * |---------------------------------|---------------------------|
 * |@ref EC_ERR_TYPE_CLOCK_MONITOR   |@ref bpmp_घड़ी_ids        |
 */
काष्ठा ec_err_fmon_desc अणु
	/** @brief Biपंचांगask of @ref bpmp_ec_desc_flags  */
	uपूर्णांक16_t desc_flags;
	/** @brief FMON monitored घड़ी id */
	uपूर्णांक16_t fmon_clk_id;
	/** @brief Biपंचांगask of @ref bpmp_fmon_faults_flags */
	uपूर्णांक32_t fmon_faults;
	/** @brief FMON faults access error */
	पूर्णांक32_t fmon_access_error;
पूर्ण BPMP_ABI_PACKED;

/**
 * |error type                       | vmon_adc_id values        |
 * |---------------------------------|---------------------------|
 * |@ref EC_ERR_TYPE_VOLTAGE_MONITOR |@ref bpmp_adc_ids          |
 */
काष्ठा ec_err_vmon_desc अणु
	/** @brief Biपंचांगask of @ref bpmp_ec_desc_flags  */
	uपूर्णांक16_t desc_flags;
	/** @brief VMON rail adc id */
	uपूर्णांक16_t vmon_adc_id;
	/** @brief Biपंचांगask of @ref bpmp_vmon_faults_flags */
	uपूर्णांक32_t vmon_faults;
	/** @brief VMON faults access error */
	पूर्णांक32_t vmon_access_error;
पूर्ण BPMP_ABI_PACKED;

/**
 * |error type                       | reg_id values             |
 * |---------------------------------|---------------------------|
 * |@ref EC_ERR_TYPE_REGISTER_PARITY |@ref bpmp_ec_रेजिस्टरs_ids |
 */
काष्ठा ec_err_reg_parity_desc अणु
	/** @brief Biपंचांगask of @ref bpmp_ec_desc_flags  */
	uपूर्णांक16_t desc_flags;
	/** @brief Register id */
	uपूर्णांक16_t reg_id;
	/** @brief Register group @ref ec_रेजिस्टरs_group */
	uपूर्णांक16_t reg_group;
पूर्ण BPMP_ABI_PACKED;

/**
 * |error type                        | err_source_id values     |
 * |--------------------------------- |--------------------------|
 * |@ref EC_ERR_TYPE_SW_CORRECTABLE   | @ref bpmp_ec_ce_swd_ids  |
 * |@ref EC_ERR_TYPE_SW_UNCORRECTABLE | @ref bpmp_ec_ue_swd_ids  |
 */
काष्ठा ec_err_sw_error_desc अणु
	/** @brief Biपंचांगask of @ref bpmp_ec_desc_flags  */
	uपूर्णांक16_t desc_flags;
	/** @brief Error source id */
	uपूर्णांक16_t err_source_id;
	/** @brief Sw error data */
	uपूर्णांक32_t sw_error_data;
पूर्ण BPMP_ABI_PACKED;

/**
 * |error type                              | err_source_id values      |
 * |----------------------------------------|---------------------------|
 * |@ref EC_ERR_TYPE_PARITY_INTERNAL        |@ref bpmp_ec_ipath_ids     |
 * |@ref EC_ERR_TYPE_ECC_SEC_INTERNAL       |@ref bpmp_ec_ipath_ids     |
 * |@ref EC_ERR_TYPE_ECC_DED_INTERNAL       |@ref bpmp_ec_ipath_ids     |
 * |@ref EC_ERR_TYPE_COMPARATOR             |@ref bpmp_ec_comparator_ids|
 * |@ref EC_ERR_TYPE_PARITY_SRAM            |@ref bpmp_घड़ी_ids        |
 * |@ref EC_ERR_TYPE_OTHER_HW_CORRECTABLE   |@ref bpmp_ec_misc_hwd_ids  |
 * |@ref EC_ERR_TYPE_OTHER_HW_UNCORRECTABLE |@ref bpmp_ec_misc_hwd_ids  |
 */
काष्ठा ec_err_simple_desc अणु
	/** @brief Biपंचांगask of @ref bpmp_ec_desc_flags  */
	uपूर्णांक16_t desc_flags;
	/** @brief Error source id. Id space depends on error type. */
	uपूर्णांक16_t err_source_id;
पूर्ण BPMP_ABI_PACKED;

/** @brief Union of EC error descriptors */
जोड़ ec_err_desc अणु
	काष्ठा ec_err_fmon_desc fmon_desc;
	काष्ठा ec_err_vmon_desc vmon_desc;
	काष्ठा ec_err_reg_parity_desc reg_parity_desc;
	काष्ठा ec_err_sw_error_desc sw_error_desc;
	काष्ठा ec_err_simple_desc simple_desc;
पूर्ण BPMP_ABI_PACKED;

काष्ठा cmd_ec_status_get_request अणु
	/** @brief HSM error line number that identअगरies target EC. */
	uपूर्णांक32_t ec_hsm_id;
पूर्ण BPMP_ABI_PACKED;

/** EC status maximum number of descriptors */
#घोषणा EC_ERR_STATUS_DESC_MAX_NUM	4U

/**
 * @cond DEPRECATED
 */
काष्ठा cmd_ec_status_get_response अणु
	/** @brief Target EC id (the same id received with request). */
	uपूर्णांक32_t ec_hsm_id;
	/**
	 * @brief Biपंचांगask of @ref bpmp_ec_status_flags
	 *
	 * If NO_ERROR flag is set, error_ fields should be ignored
	 */
	uपूर्णांक32_t ec_status_flags;
	/** @brief Found EC error index. */
	uपूर्णांक32_t error_idx;
	/** @brief  Found EC error type @ref bpmp_ec_err_type. */
	uपूर्णांक32_t error_type;
	/** @brief  Number of वापसed EC error descriptors */
	uपूर्णांक32_t error_desc_num;
	/** @brief  EC error descriptors */
	जोड़ ec_err_desc error_descs[EC_ERR_STATUS_DESC_MAX_NUM];
पूर्ण BPMP_ABI_PACKED;
/** @endcond */

काष्ठा cmd_ec_status_ex_get_response अणु
	/** @brief Target EC id (the same id received with request). */
	uपूर्णांक32_t ec_hsm_id;
	/**
	 * @brief Biपंचांगask of @ref bpmp_ec_status_flags
	 *
	 * If NO_ERROR flag is set, error_ fields should be ignored
	 */
	uपूर्णांक32_t ec_status_flags;
	/** @brief Found EC error index. */
	uपूर्णांक32_t error_idx;
	/** @brief  Found EC error type @ref bpmp_ec_err_type. */
	uपूर्णांक32_t error_type;
	/** @brief  Found EC mission error counter value */
	uपूर्णांक32_t error_counter;
	/** @brief  Found EC mission error user value */
	uपूर्णांक32_t error_uval;
	/** @brief  Reserved entry    */
	uपूर्णांक32_t reserved;
	/** @brief  Number of वापसed EC error descriptors */
	uपूर्णांक32_t error_desc_num;
	/** @brief  EC error descriptors */
	जोड़ ec_err_desc error_descs[EC_ERR_STATUS_DESC_MAX_NUM];
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup EC
 * @brief Request with #MRQ_EC
 *
 * Used by the sender of an #MRQ_EC message to access ECs owned
 * by BPMP.
 *
 * @cond DEPRECATED
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |@ref CMD_EC_STATUS_GET      |ec_status_get          |
 * @endcond
 *
 * |sub-command                 |payload                |
 * |----------------------------|-----------------------|
 * |@ref CMD_EC_STATUS_EX_GET   |ec_status_get          |
 *
 */

काष्ठा mrq_ec_request अणु
	/** @brief Sub-command id. */
	uपूर्णांक32_t cmd_id;

	जोड़ अणु
		काष्ठा cmd_ec_status_get_request ec_status_get;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/**
 * @ingroup EC
 * @brief Response to MRQ_EC
 *
 * Each sub-command supported by @ref mrq_ec_request may वापस
 * sub-command-specअगरic data as indicated below.
 *
 * @cond DEPRECATED
 * |sub-command                 |payload                 |
 * |----------------------------|------------------------|
 * |@ref CMD_EC_STATUS_GET      |ec_status_get           |
 * @endcond
 *
 * |sub-command                 |payload                 |
 * |----------------------------|------------------------|
 * |@ref CMD_EC_STATUS_EX_GET   |ec_status_ex_get        |
 *
 */

काष्ठा mrq_ec_response अणु
	जोड़ अणु
		/**
		 * @cond DEPRECATED
		 */
		काष्ठा cmd_ec_status_get_response ec_status_get;
		/** @endcond */
		काष्ठा cmd_ec_status_ex_get_response ec_status_ex_get;
	पूर्ण BPMP_UNION_ANON;
पूर्ण BPMP_ABI_PACKED;

/** @पूर्ण */
/** @endcond */

/**
 * @addtogroup Error_Codes
 * Negative values क्रम mrq_response::err generally indicate some
 * error. The ABI defines the following error codes. Negating these
 * defines is an exercise left to the user.
 * @अणु
 */

/** @brief Operation not permitted */
#घोषणा BPMP_EPERM	1
/** @brief No such file or directory */
#घोषणा BPMP_ENOENT	2
/** @brief No MRQ handler */
#घोषणा BPMP_ENOHANDLER	3
/** @brief I/O error */
#घोषणा BPMP_EIO	5
/** @brief Bad sub-MRQ command */
#घोषणा BPMP_EBADCMD	6
/** @brief Resource temporarily unavailable */
#घोषणा BPMP_EAGAIN	11
/** @brief Not enough memory */
#घोषणा BPMP_ENOMEM	12
/** @brief Permission denied */
#घोषणा BPMP_EACCES	13
/** @brief Bad address */
#घोषणा BPMP_EFAULT	14
/** @brief Resource busy */
#घोषणा BPMP_EBUSY	16
/** @brief No such device */
#घोषणा BPMP_ENODEV	19
/** @brief Argument is a directory */
#घोषणा BPMP_EISसूची	21
/** @brief Invalid argument */
#घोषणा BPMP_EINVAL	22
/** @brief Timeout during operation */
#घोषणा BPMP_ETIMEDOUT  23
/** @brief Out of range */
#घोषणा BPMP_दुस्फल	34
/** @brief Function not implemented */
#घोषणा BPMP_ENOSYS	38
/** @brief Invalid slot */
#घोषणा BPMP_EBADSLT	57
/** @brief Not supported */
#घोषणा BPMP_ENOTSUP	134
/** @brief No such device or address */
#घोषणा BPMP_ENXIO	140

/** @पूर्ण */

#अगर defined(BPMP_ABI_CHECKS)
#समावेश "bpmp_abi_checks.h"
#पूर्ण_अगर

#पूर्ण_अगर
