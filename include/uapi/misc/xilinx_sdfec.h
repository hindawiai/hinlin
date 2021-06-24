<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Xilinx SD-FEC
 *
 * Copyright (C) 2019 Xilinx, Inc.
 *
 * Description:
 * This driver is developed क्रम SDFEC16 IP. It provides a अक्षर device
 * in sysfs and supports file operations like खोलो(), बंद() and ioctl().
 */
#अगर_अघोषित __XILINX_SDFEC_H__
#घोषणा __XILINX_SDFEC_H__

#समावेश <linux/types.h>

/* Shared LDPC Tables */
#घोषणा XSDFEC_LDPC_SC_TABLE_ADDR_BASE (0x10000)
#घोषणा XSDFEC_LDPC_SC_TABLE_ADDR_HIGH (0x10400)
#घोषणा XSDFEC_LDPC_LA_TABLE_ADDR_BASE (0x18000)
#घोषणा XSDFEC_LDPC_LA_TABLE_ADDR_HIGH (0x19000)
#घोषणा XSDFEC_LDPC_QC_TABLE_ADDR_BASE (0x20000)
#घोषणा XSDFEC_LDPC_QC_TABLE_ADDR_HIGH (0x28000)

/* LDPC tables depth */
#घोषणा XSDFEC_SC_TABLE_DEPTH                                                  \
	(XSDFEC_LDPC_SC_TABLE_ADDR_HIGH - XSDFEC_LDPC_SC_TABLE_ADDR_BASE)
#घोषणा XSDFEC_LA_TABLE_DEPTH                                                  \
	(XSDFEC_LDPC_LA_TABLE_ADDR_HIGH - XSDFEC_LDPC_LA_TABLE_ADDR_BASE)
#घोषणा XSDFEC_QC_TABLE_DEPTH                                                  \
	(XSDFEC_LDPC_QC_TABLE_ADDR_HIGH - XSDFEC_LDPC_QC_TABLE_ADDR_BASE)

/**
 * क्रमागत xsdfec_code - Code Type.
 * @XSDFEC_TURBO_CODE: Driver is configured क्रम Turbo mode.
 * @XSDFEC_LDPC_CODE: Driver is configured क्रम LDPC mode.
 *
 * This क्रमागत is used to indicate the mode of the driver. The mode is determined
 * by checking which codes are set in the driver. Note that the mode cannot be
 * changed by the driver.
 */
क्रमागत xsdfec_code अणु
	XSDFEC_TURBO_CODE = 0,
	XSDFEC_LDPC_CODE,
पूर्ण;

/**
 * क्रमागत xsdfec_order - Order
 * @XSDFEC_MAINTAIN_ORDER: Maपूर्णांकain order execution of blocks.
 * @XSDFEC_OUT_OF_ORDER: Out-of-order execution of blocks.
 *
 * This क्रमागत is used to indicate whether the order of blocks can change from
 * input to output.
 */
क्रमागत xsdfec_order अणु
	XSDFEC_MAINTAIN_ORDER = 0,
	XSDFEC_OUT_OF_ORDER,
पूर्ण;

/**
 * क्रमागत xsdfec_turbo_alg - Turbo Algorithm Type.
 * @XSDFEC_MAX_SCALE: Max Log-Map algorithm with extrinsic scaling. When
 *		      scaling is set to this is equivalent to the Max Log-Map
 *		      algorithm.
 * @XSDFEC_MAX_STAR: Log-Map algorithm.
 * @XSDFEC_TURBO_ALG_MAX: Used to indicate out of bound Turbo algorithms.
 *
 * This क्रमागत specअगरies which Turbo Decode algorithm is in use.
 */
क्रमागत xsdfec_turbo_alg अणु
	XSDFEC_MAX_SCALE = 0,
	XSDFEC_MAX_STAR,
	XSDFEC_TURBO_ALG_MAX,
पूर्ण;

/**
 * क्रमागत xsdfec_state - State.
 * @XSDFEC_INIT: Driver is initialized.
 * @XSDFEC_STARTED: Driver is started.
 * @XSDFEC_STOPPED: Driver is stopped.
 * @XSDFEC_NEEDS_RESET: Driver needs to be reset.
 * @XSDFEC_PL_RECONFIGURE: Programmable Logic needs to be recofigured.
 *
 * This क्रमागत is used to indicate the state of the driver.
 */
क्रमागत xsdfec_state अणु
	XSDFEC_INIT = 0,
	XSDFEC_STARTED,
	XSDFEC_STOPPED,
	XSDFEC_NEEDS_RESET,
	XSDFEC_PL_RECONFIGURE,
पूर्ण;

/**
 * क्रमागत xsdfec_axis_width - AXIS_WIDTH.DIN Setting क्रम 128-bit width.
 * @XSDFEC_1x128b: DIN data input stream consists of a 128-bit lane
 * @XSDFEC_2x128b: DIN data input stream consists of two 128-bit lanes
 * @XSDFEC_4x128b: DIN data input stream consists of four 128-bit lanes
 *
 * This क्रमागत is used to indicate the AXIS_WIDTH.DIN setting क्रम 128-bit width.
 * The number of lanes of the DIN data input stream depends upon the
 * AXIS_WIDTH.DIN parameter.
 */
क्रमागत xsdfec_axis_width अणु
	XSDFEC_1x128b = 1,
	XSDFEC_2x128b = 2,
	XSDFEC_4x128b = 4,
पूर्ण;

/**
 * क्रमागत xsdfec_axis_word_include - Words Configuration.
 * @XSDFEC_FIXED_VALUE: Fixed, the DIN_WORDS AXI4-Stream पूर्णांकerface is हटाओd
 *			from the IP instance and is driven with the specअगरied
 *			number of words.
 * @XSDFEC_IN_BLOCK: In Block, configures the IP instance to expect a single
 *		     DIN_WORDS value per input code block. The DIN_WORDS
 *		     पूर्णांकerface is present.
 * @XSDFEC_PER_AXI_TRANSACTION: Per Transaction, configures the IP instance to
 * expect one DIN_WORDS value per input transaction on the DIN पूर्णांकerface. The
 * DIN_WORDS पूर्णांकerface is present.
 * @XSDFEC_AXIS_WORDS_INCLUDE_MAX: Used to indicate out of bound Words
 *				   Configurations.
 *
 * This क्रमागत is used to specअगरy the DIN_WORDS configuration.
 */
क्रमागत xsdfec_axis_word_include अणु
	XSDFEC_FIXED_VALUE = 0,
	XSDFEC_IN_BLOCK,
	XSDFEC_PER_AXI_TRANSACTION,
	XSDFEC_AXIS_WORDS_INCLUDE_MAX,
पूर्ण;

/**
 * काष्ठा xsdfec_turbo - User data क्रम Turbo codes.
 * @alg: Specअगरies which Turbo decode algorithm to use
 * @scale: Specअगरies the extrinsic scaling to apply when the Max Scale algorithm
 *	   has been selected
 *
 * Turbo code काष्ठाure to communicate parameters to XSDFEC driver.
 */
काष्ठा xsdfec_turbo अणु
	__u32 alg;
	__u8 scale;
पूर्ण;

/**
 * काष्ठा xsdfec_ldpc_params - User data क्रम LDPC codes.
 * @n: Number of code word bits
 * @k: Number of inक्रमmation bits
 * @psize: Size of sub-matrix
 * @nlayers: Number of layers in code
 * @nqc: Quasi Cyclic Number
 * @nmqc: Number of M-sized QC operations in parity check matrix
 * @nm: Number of M-size vectors in N
 * @norm_type: Normalization required or not
 * @no_packing: Determines अगर multiple QC ops should be perक्रमmed
 * @special_qc: Sub-Matrix property क्रम Circulant weight > 0
 * @no_final_parity: Decide अगर final parity check needs to be perक्रमmed
 * @max_schedule: Experimental code word scheduling limit
 * @sc_off: SC offset
 * @la_off: LA offset
 * @qc_off: QC offset
 * @sc_table: Poपूर्णांकer to SC Table which must be page aligned
 * @la_table: Poपूर्णांकer to LA Table which must be page aligned
 * @qc_table: Poपूर्णांकer to QC Table which must be page aligned
 * @code_id: LDPC Code
 *
 * This काष्ठाure describes the LDPC code that is passed to the driver by the
 * application.
 */
काष्ठा xsdfec_ldpc_params अणु
	__u32 n;
	__u32 k;
	__u32 psize;
	__u32 nlayers;
	__u32 nqc;
	__u32 nmqc;
	__u32 nm;
	__u32 norm_type;
	__u32 no_packing;
	__u32 special_qc;
	__u32 no_final_parity;
	__u32 max_schedule;
	__u32 sc_off;
	__u32 la_off;
	__u32 qc_off;
	__u32 *sc_table;
	__u32 *la_table;
	__u32 *qc_table;
	__u16 code_id;
पूर्ण;

/**
 * काष्ठा xsdfec_status - Status of SD-FEC core.
 * @state: State of the SD-FEC core
 * @activity: Describes अगर the SD-FEC instance is Active
 */
काष्ठा xsdfec_status अणु
	__u32 state;
	__s8 activity;
पूर्ण;

/**
 * काष्ठा xsdfec_irq - Enabling or Disabling Interrupts.
 * @enable_isr: If true enables the ISR
 * @enable_ecc_isr: If true enables the ECC ISR
 */
काष्ठा xsdfec_irq अणु
	__s8 enable_isr;
	__s8 enable_ecc_isr;
पूर्ण;

/**
 * काष्ठा xsdfec_config - Configuration of SD-FEC core.
 * @code: The codes being used by the SD-FEC instance
 * @order: Order of Operation
 * @din_width: Width of the DIN AXI4-Stream
 * @din_word_include: How DIN_WORDS are inputted
 * @करोut_width: Width of the DOUT AXI4-Stream
 * @करोut_word_include: HOW DOUT_WORDS are outputted
 * @irq: Enabling or disabling पूर्णांकerrupts
 * @bypass: Is the core being bypassed
 * @code_wr_protect: Is ग_लिखो protection of LDPC codes enabled
 */
काष्ठा xsdfec_config अणु
	__u32 code;
	__u32 order;
	__u32 din_width;
	__u32 din_word_include;
	__u32 करोut_width;
	__u32 करोut_word_include;
	काष्ठा xsdfec_irq irq;
	__s8 bypass;
	__s8 code_wr_protect;
पूर्ण;

/**
 * काष्ठा xsdfec_stats - Stats retrived by ioctl XSDFEC_GET_STATS. Used
 *			 to buffer atomic_t variables from काष्ठा
 *			 xsdfec_dev. Counts are accumulated until
 *			 the user clears them.
 * @isr_err_count: Count of ISR errors
 * @cecc_count: Count of Correctable ECC errors (SBE)
 * @uecc_count: Count of Uncorrectable ECC errors (MBE)
 */
काष्ठा xsdfec_stats अणु
	__u32 isr_err_count;
	__u32 cecc_count;
	__u32 uecc_count;
पूर्ण;

/**
 * काष्ठा xsdfec_ldpc_param_table_sizes - Used to store sizes of SD-FEC table
 *					  entries क्रम an inभागidual LPDC code
 *					  parameter.
 * @sc_size: Size of SC table used
 * @la_size: Size of LA table used
 * @qc_size: Size of QC table used
 */
काष्ठा xsdfec_ldpc_param_table_sizes अणु
	__u32 sc_size;
	__u32 la_size;
	__u32 qc_size;
पूर्ण;

/*
 * XSDFEC IOCTL List
 */
#घोषणा XSDFEC_MAGIC 'f'
/**
 * DOC: XSDFEC_START_DEV
 *
 * @Description
 *
 * ioctl to start SD-FEC core
 *
 * This fails अगर the XSDFEC_SET_ORDER ioctl has not been previously called
 */
#घोषणा XSDFEC_START_DEV _IO(XSDFEC_MAGIC, 0)
/**
 * DOC: XSDFEC_STOP_DEV
 *
 * @Description
 *
 * ioctl to stop the SD-FEC core
 */
#घोषणा XSDFEC_STOP_DEV _IO(XSDFEC_MAGIC, 1)
/**
 * DOC: XSDFEC_GET_STATUS
 *
 * @Description
 *
 * ioctl that वापसs status of SD-FEC core
 */
#घोषणा XSDFEC_GET_STATUS _IOR(XSDFEC_MAGIC, 2, काष्ठा xsdfec_status)
/**
 * DOC: XSDFEC_SET_IRQ
 * @Parameters
 *
 * @काष्ठा xsdfec_irq *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_irq that contains the पूर्णांकerrupt settings
 *	क्रम the SD-FEC core
 *
 * @Description
 *
 * ioctl to enable or disable irq
 */
#घोषणा XSDFEC_SET_IRQ _IOW(XSDFEC_MAGIC, 3, काष्ठा xsdfec_irq)
/**
 * DOC: XSDFEC_SET_TURBO
 * @Parameters
 *
 * @काष्ठा xsdfec_turbo *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_turbo that contains the Turbo decode
 *	settings क्रम the SD-FEC core
 *
 * @Description
 *
 * ioctl that sets the SD-FEC Turbo parameter values
 *
 * This can only be used when the driver is in the XSDFEC_STOPPED state
 */
#घोषणा XSDFEC_SET_TURBO _IOW(XSDFEC_MAGIC, 4, काष्ठा xsdfec_turbo)
/**
 * DOC: XSDFEC_ADD_LDPC_CODE_PARAMS
 * @Parameters
 *
 * @काष्ठा xsdfec_ldpc_params *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_ldpc_params that contains the LDPC code
 *	parameters to be added to the SD-FEC Block
 *
 * @Description
 * ioctl to add an LDPC code to the SD-FEC LDPC codes
 *
 * This can only be used when:
 *
 * - Driver is in the XSDFEC_STOPPED state
 *
 * - SD-FEC core is configured as LPDC
 *
 * - SD-FEC Code Write Protection is disabled
 */
#घोषणा XSDFEC_ADD_LDPC_CODE_PARAMS                                            \
	_IOW(XSDFEC_MAGIC, 5, काष्ठा xsdfec_ldpc_params)
/**
 * DOC: XSDFEC_GET_CONFIG
 * @Parameters
 *
 * @काष्ठा xsdfec_config *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_config that contains the current
 *	configuration settings of the SD-FEC Block
 *
 * @Description
 *
 * ioctl that वापसs SD-FEC core configuration
 */
#घोषणा XSDFEC_GET_CONFIG _IOR(XSDFEC_MAGIC, 6, काष्ठा xsdfec_config)
/**
 * DOC: XSDFEC_GET_TURBO
 * @Parameters
 *
 * @काष्ठा xsdfec_turbo *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_turbo that contains the current Turbo
 *	decode settings of the SD-FEC Block
 *
 * @Description
 *
 * ioctl that वापसs SD-FEC turbo param values
 */
#घोषणा XSDFEC_GET_TURBO _IOR(XSDFEC_MAGIC, 7, काष्ठा xsdfec_turbo)
/**
 * DOC: XSDFEC_SET_ORDER
 * @Parameters
 *
 * @काष्ठा अचिन्हित दीर्घ *
 *	Poपूर्णांकer to the अचिन्हित दीर्घ that contains a value from the
 *	@क्रमागत xsdfec_order
 *
 * @Description
 *
 * ioctl that sets order, अगर order of blocks can change from input to output
 *
 * This can only be used when the driver is in the XSDFEC_STOPPED state
 */
#घोषणा XSDFEC_SET_ORDER _IOW(XSDFEC_MAGIC, 8, अचिन्हित दीर्घ)
/**
 * DOC: XSDFEC_SET_BYPASS
 * @Parameters
 *
 * @काष्ठा bool *
 *	Poपूर्णांकer to bool that sets the bypass value, where false results in
 *	normal operation and false results in the SD-FEC perक्रमming the
 *	configured operations (same number of cycles) but output data matches
 *	the input data
 *
 * @Description
 *
 * ioctl that sets bypass.
 *
 * This can only be used when the driver is in the XSDFEC_STOPPED state
 */
#घोषणा XSDFEC_SET_BYPASS _IOW(XSDFEC_MAGIC, 9, bool)
/**
 * DOC: XSDFEC_IS_ACTIVE
 * @Parameters
 *
 * @काष्ठा bool *
 *	Poपूर्णांकer to bool that वापसs true अगर the SD-FEC is processing data
 *
 * @Description
 *
 * ioctl that determines अगर SD-FEC is processing data
 */
#घोषणा XSDFEC_IS_ACTIVE _IOR(XSDFEC_MAGIC, 10, bool)
/**
 * DOC: XSDFEC_CLEAR_STATS
 *
 * @Description
 *
 * ioctl that clears error stats collected during पूर्णांकerrupts
 */
#घोषणा XSDFEC_CLEAR_STATS _IO(XSDFEC_MAGIC, 11)
/**
 * DOC: XSDFEC_GET_STATS
 * @Parameters
 *
 * @काष्ठा xsdfec_stats *
 *	Poपूर्णांकer to the &काष्ठा xsdfec_stats that will contain the updated stats
 *	values
 *
 * @Description
 *
 * ioctl that वापसs SD-FEC core stats
 *
 * This can only be used when the driver is in the XSDFEC_STOPPED state
 */
#घोषणा XSDFEC_GET_STATS _IOR(XSDFEC_MAGIC, 12, काष्ठा xsdfec_stats)
/**
 * DOC: XSDFEC_SET_DEFAULT_CONFIG
 *
 * @Description
 *
 * ioctl that वापसs SD-FEC core to शेष config, use after a reset
 *
 * This can only be used when the driver is in the XSDFEC_STOPPED state
 */
#घोषणा XSDFEC_SET_DEFAULT_CONFIG _IO(XSDFEC_MAGIC, 13)

#पूर्ण_अगर /* __XILINX_SDFEC_H__ */
