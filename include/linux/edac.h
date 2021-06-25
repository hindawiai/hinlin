<शैली गुरु>
/*
 * Generic EDAC defs
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2008 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */
#अगर_अघोषित _LINUX_EDAC_H_
#घोषणा _LINUX_EDAC_H_

#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/completion.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/numa.h>

#घोषणा EDAC_DEVICE_NAME_LEN	31

काष्ठा device;

#घोषणा EDAC_OPSTATE_INVAL	-1
#घोषणा EDAC_OPSTATE_POLL	0
#घोषणा EDAC_OPSTATE_NMI	1
#घोषणा EDAC_OPSTATE_INT	2

बाह्य पूर्णांक edac_op_state;

काष्ठा bus_type *edac_get_sysfs_subsys(व्योम);

अटल अंतरभूत व्योम opstate_init(व्योम)
अणु
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_NMI:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_POLL;
	पूर्ण
	वापस;
पूर्ण

/* Max length of a DIMM label*/
#घोषणा EDAC_MC_LABEL_LEN	31

/* Maximum size of the location string */
#घोषणा LOCATION_SIZE 256

/* Defines the maximum number of labels that can be reported */
#घोषणा EDAC_MAX_LABELS		8

/* String used to join two or more labels */
#घोषणा OTHER_LABEL " or "

/**
 * क्रमागत dev_type - describe the type of memory DRAM chips used at the stick
 * @DEV_UNKNOWN:	Can't be determined, or MC doesn't support detect it
 * @DEV_X1:		1 bit क्रम data
 * @DEV_X2:		2 bits क्रम data
 * @DEV_X4:		4 bits क्रम data
 * @DEV_X8:		8 bits क्रम data
 * @DEV_X16:		16 bits क्रम data
 * @DEV_X32:		32 bits क्रम data
 * @DEV_X64:		64 bits क्रम data
 *
 * Typical values are x4 and x8.
 */
क्रमागत dev_type अणु
	DEV_UNKNOWN = 0,
	DEV_X1,
	DEV_X2,
	DEV_X4,
	DEV_X8,
	DEV_X16,
	DEV_X32,		/* Do these parts exist? */
	DEV_X64			/* Do these parts exist? */
पूर्ण;

#घोषणा DEV_FLAG_UNKNOWN	BIT(DEV_UNKNOWN)
#घोषणा DEV_FLAG_X1		BIT(DEV_X1)
#घोषणा DEV_FLAG_X2		BIT(DEV_X2)
#घोषणा DEV_FLAG_X4		BIT(DEV_X4)
#घोषणा DEV_FLAG_X8		BIT(DEV_X8)
#घोषणा DEV_FLAG_X16		BIT(DEV_X16)
#घोषणा DEV_FLAG_X32		BIT(DEV_X32)
#घोषणा DEV_FLAG_X64		BIT(DEV_X64)

/**
 * क्रमागत hw_event_mc_err_type - type of the detected error
 *
 * @HW_EVENT_ERR_CORRECTED:	Corrected Error - Indicates that an ECC
 *				corrected error was detected
 * @HW_EVENT_ERR_UNCORRECTED:	Uncorrected Error - Indicates an error that
 *				can't be corrected by ECC, but it is not
 *				fatal (maybe it is on an unused memory area,
 *				or the memory controller could recover from
 *				it क्रम example, by re-trying the operation).
 * @HW_EVENT_ERR_DEFERRED:	Deferred Error - Indicates an uncorrectable
 *				error whose handling is not urgent. This could
 *				be due to hardware data poisoning where the
 *				प्रणाली can जारी operation until the poisoned
 *				data is consumed. Preemptive measures may also
 *				be taken, e.g. offlining pages, etc.
 * @HW_EVENT_ERR_FATAL:		Fatal Error - Uncorrected error that could not
 *				be recovered.
 * @HW_EVENT_ERR_INFO:		Inक्रमmational - The CPER spec defines a क्रमth
 *				type of error: inक्रमmational logs.
 */
क्रमागत hw_event_mc_err_type अणु
	HW_EVENT_ERR_CORRECTED,
	HW_EVENT_ERR_UNCORRECTED,
	HW_EVENT_ERR_DEFERRED,
	HW_EVENT_ERR_FATAL,
	HW_EVENT_ERR_INFO,
पूर्ण;

अटल अंतरभूत अक्षर *mc_event_error_type(स्थिर अचिन्हित पूर्णांक err_type)
अणु
	चयन (err_type) अणु
	हाल HW_EVENT_ERR_CORRECTED:
		वापस "Corrected";
	हाल HW_EVENT_ERR_UNCORRECTED:
		वापस "Uncorrected";
	हाल HW_EVENT_ERR_DEFERRED:
		वापस "Deferred";
	हाल HW_EVENT_ERR_FATAL:
		वापस "Fatal";
	शेष:
	हाल HW_EVENT_ERR_INFO:
		वापस "Info";
	पूर्ण
पूर्ण

/**
 * क्रमागत mem_type - memory types. For a more detailed reference, please see
 *			http://en.wikipedia.org/wiki/DRAM
 *
 * @MEM_EMPTY:		Empty csrow
 * @MEM_RESERVED:	Reserved csrow type
 * @MEM_UNKNOWN:	Unknown csrow type
 * @MEM_FPM:		FPM - Fast Page Mode, used on प्रणालीs up to 1995.
 * @MEM_EDO:		EDO - Extended data out, used on प्रणालीs up to 1998.
 * @MEM_BEDO:		BEDO - Burst Extended data out, an EDO variant.
 * @MEM_SDR:		SDR - Single data rate SDRAM
 *			http://en.wikipedia.org/wiki/Synchronous_dynamic_अक्रमom-access_memory
 *			They use 3 pins क्रम chip select: Pins 0 and 2 are
 *			क्रम rank 0; pins 1 and 3 are क्रम rank 1, अगर the memory
 *			is dual-rank.
 * @MEM_RDR:		Registered SDR SDRAM
 * @MEM_DDR:		Double data rate SDRAM
 *			http://en.wikipedia.org/wiki/DDR_SDRAM
 * @MEM_RDDR:		Registered Double data rate SDRAM
 *			This is a variant of the DDR memories.
 *			A रेजिस्टरed memory has a buffer inside it, hiding
 *			part of the memory details to the memory controller.
 * @MEM_RMBS:		Rambus DRAM, used on a few Pentium III/IV controllers.
 * @MEM_DDR2:		DDR2 RAM, as described at JEDEC JESD79-2F.
 *			Those memories are labeled as "PC2-" instead of "PC" to
 *			dअगरferentiate from DDR.
 * @MEM_FB_DDR2:	Fully-Buffered DDR2, as described at JEDEC Std No. 205
 *			and JESD206.
 *			Those memories are accessed per DIMM slot, and not by
 *			a chip select संकेत.
 * @MEM_RDDR2:		Registered DDR2 RAM
 *			This is a variant of the DDR2 memories.
 * @MEM_XDR:		Rambus XDR
 *			It is an evolution of the original RAMBUS memories,
 *			created to compete with DDR2. Weren't used on any
 *			x86 arch, but cell_edac PPC memory controller uses it.
 * @MEM_DDR3:		DDR3 RAM
 * @MEM_RDDR3:		Registered DDR3 RAM
 *			This is a variant of the DDR3 memories.
 * @MEM_LRDDR3:		Load-Reduced DDR3 memory.
 * @MEM_LPDDR3:		Low-Power DDR3 memory.
 * @MEM_DDR4:		Unbuffered DDR4 RAM
 * @MEM_RDDR4:		Registered DDR4 RAM
 *			This is a variant of the DDR4 memories.
 * @MEM_LRDDR4:		Load-Reduced DDR4 memory.
 * @MEM_LPDDR4:		Low-Power DDR4 memory.
 * @MEM_DDR5:		Unbuffered DDR5 RAM
 * @MEM_NVDIMM:		Non-अस्थिर RAM
 * @MEM_WIO2:		Wide I/O 2.
 */
क्रमागत mem_type अणु
	MEM_EMPTY = 0,
	MEM_RESERVED,
	MEM_UNKNOWN,
	MEM_FPM,
	MEM_EDO,
	MEM_BEDO,
	MEM_SDR,
	MEM_RDR,
	MEM_DDR,
	MEM_RDDR,
	MEM_RMBS,
	MEM_DDR2,
	MEM_FB_DDR2,
	MEM_RDDR2,
	MEM_XDR,
	MEM_DDR3,
	MEM_RDDR3,
	MEM_LRDDR3,
	MEM_LPDDR3,
	MEM_DDR4,
	MEM_RDDR4,
	MEM_LRDDR4,
	MEM_LPDDR4,
	MEM_DDR5,
	MEM_NVDIMM,
	MEM_WIO2,
पूर्ण;

#घोषणा MEM_FLAG_EMPTY		BIT(MEM_EMPTY)
#घोषणा MEM_FLAG_RESERVED	BIT(MEM_RESERVED)
#घोषणा MEM_FLAG_UNKNOWN	BIT(MEM_UNKNOWN)
#घोषणा MEM_FLAG_FPM		BIT(MEM_FPM)
#घोषणा MEM_FLAG_EDO		BIT(MEM_EDO)
#घोषणा MEM_FLAG_BEDO		BIT(MEM_BEDO)
#घोषणा MEM_FLAG_SDR		BIT(MEM_SDR)
#घोषणा MEM_FLAG_RDR		BIT(MEM_RDR)
#घोषणा MEM_FLAG_DDR		BIT(MEM_DDR)
#घोषणा MEM_FLAG_RDDR		BIT(MEM_RDDR)
#घोषणा MEM_FLAG_RMBS		BIT(MEM_RMBS)
#घोषणा MEM_FLAG_DDR2           BIT(MEM_DDR2)
#घोषणा MEM_FLAG_FB_DDR2        BIT(MEM_FB_DDR2)
#घोषणा MEM_FLAG_RDDR2          BIT(MEM_RDDR2)
#घोषणा MEM_FLAG_XDR            BIT(MEM_XDR)
#घोषणा MEM_FLAG_DDR3           BIT(MEM_DDR3)
#घोषणा MEM_FLAG_RDDR3          BIT(MEM_RDDR3)
#घोषणा MEM_FLAG_LPDDR3         BIT(MEM_LPDDR3)
#घोषणा MEM_FLAG_DDR4           BIT(MEM_DDR4)
#घोषणा MEM_FLAG_RDDR4          BIT(MEM_RDDR4)
#घोषणा MEM_FLAG_LRDDR4         BIT(MEM_LRDDR4)
#घोषणा MEM_FLAG_LPDDR4         BIT(MEM_LPDDR4)
#घोषणा MEM_FLAG_DDR5           BIT(MEM_DDR5)
#घोषणा MEM_FLAG_NVDIMM         BIT(MEM_NVDIMM)
#घोषणा MEM_FLAG_WIO2		BIT(MEM_WIO2)

/**
 * क्रमागत edac_type - Error Detection and Correction capabilities and mode
 * @EDAC_UNKNOWN:	Unknown अगर ECC is available
 * @EDAC_NONE:		Doesn't support ECC
 * @EDAC_RESERVED:	Reserved ECC type
 * @EDAC_PARITY:	Detects parity errors
 * @EDAC_EC:		Error Checking - no correction
 * @EDAC_SECDED:	Single bit error correction, Double detection
 * @EDAC_S2ECD2ED:	Chipसमाप्त x2 devices - करो these exist?
 * @EDAC_S4ECD4ED:	Chipसमाप्त x4 devices
 * @EDAC_S8ECD8ED:	Chipसमाप्त x8 devices
 * @EDAC_S16ECD16ED:	Chipसमाप्त x16 devices
 */
क्रमागत edac_type अणु
	EDAC_UNKNOWN =	0,
	EDAC_NONE,
	EDAC_RESERVED,
	EDAC_PARITY,
	EDAC_EC,
	EDAC_SECDED,
	EDAC_S2ECD2ED,
	EDAC_S4ECD4ED,
	EDAC_S8ECD8ED,
	EDAC_S16ECD16ED,
पूर्ण;

#घोषणा EDAC_FLAG_UNKNOWN	BIT(EDAC_UNKNOWN)
#घोषणा EDAC_FLAG_NONE		BIT(EDAC_NONE)
#घोषणा EDAC_FLAG_PARITY	BIT(EDAC_PARITY)
#घोषणा EDAC_FLAG_EC		BIT(EDAC_EC)
#घोषणा EDAC_FLAG_SECDED	BIT(EDAC_SECDED)
#घोषणा EDAC_FLAG_S2ECD2ED	BIT(EDAC_S2ECD2ED)
#घोषणा EDAC_FLAG_S4ECD4ED	BIT(EDAC_S4ECD4ED)
#घोषणा EDAC_FLAG_S8ECD8ED	BIT(EDAC_S8ECD8ED)
#घोषणा EDAC_FLAG_S16ECD16ED	BIT(EDAC_S16ECD16ED)

/**
 * क्रमागत scrub_type - scrubbing capabilities
 * @SCRUB_UNKNOWN:		Unknown अगर scrubber is available
 * @SCRUB_NONE:			No scrubber
 * @SCRUB_SW_PROG:		SW progressive (sequential) scrubbing
 * @SCRUB_SW_SRC:		Software scrub only errors
 * @SCRUB_SW_PROG_SRC:		Progressive software scrub from an error
 * @SCRUB_SW_TUNABLE:		Software scrub frequency is tunable
 * @SCRUB_HW_PROG:		HW progressive (sequential) scrubbing
 * @SCRUB_HW_SRC:		Hardware scrub only errors
 * @SCRUB_HW_PROG_SRC:		Progressive hardware scrub from an error
 * @SCRUB_HW_TUNABLE:		Hardware scrub frequency is tunable
 */
क्रमागत scrub_type अणु
	SCRUB_UNKNOWN =	0,
	SCRUB_NONE,
	SCRUB_SW_PROG,
	SCRUB_SW_SRC,
	SCRUB_SW_PROG_SRC,
	SCRUB_SW_TUNABLE,
	SCRUB_HW_PROG,
	SCRUB_HW_SRC,
	SCRUB_HW_PROG_SRC,
	SCRUB_HW_TUNABLE
पूर्ण;

#घोषणा SCRUB_FLAG_SW_PROG	BIT(SCRUB_SW_PROG)
#घोषणा SCRUB_FLAG_SW_SRC	BIT(SCRUB_SW_SRC)
#घोषणा SCRUB_FLAG_SW_PROG_SRC	BIT(SCRUB_SW_PROG_SRC)
#घोषणा SCRUB_FLAG_SW_TUN	BIT(SCRUB_SW_SCRUB_TUNABLE)
#घोषणा SCRUB_FLAG_HW_PROG	BIT(SCRUB_HW_PROG)
#घोषणा SCRUB_FLAG_HW_SRC	BIT(SCRUB_HW_SRC)
#घोषणा SCRUB_FLAG_HW_PROG_SRC	BIT(SCRUB_HW_PROG_SRC)
#घोषणा SCRUB_FLAG_HW_TUN	BIT(SCRUB_HW_TUNABLE)

/* FIXME - should have notअगरy capabilities: NMI, LOG, PROC, etc */

/* EDAC पूर्णांकernal operation states */
#घोषणा	OP_ALLOC		0x100
#घोषणा OP_RUNNING_POLL		0x201
#घोषणा OP_RUNNING_INTERRUPT	0x202
#घोषणा OP_RUNNING_POLL_INTR	0x203
#घोषणा OP_OFFLINE		0x300

/**
 * क्रमागत edac_mc_layer_type - memory controller hierarchy layer
 *
 * @EDAC_MC_LAYER_BRANCH:	memory layer is named "branch"
 * @EDAC_MC_LAYER_CHANNEL:	memory layer is named "channel"
 * @EDAC_MC_LAYER_SLOT:		memory layer is named "slot"
 * @EDAC_MC_LAYER_CHIP_SELECT:	memory layer is named "chip select"
 * @EDAC_MC_LAYER_ALL_MEM:	memory layout is unknown. All memory is mapped
 *				as a single memory area. This is used when
 *				retrieving errors from a firmware driven driver.
 *
 * This क्रमागत is used by the drivers to tell edac_mc_sysfs what name should
 * be used when describing a memory stick location.
 */
क्रमागत edac_mc_layer_type अणु
	EDAC_MC_LAYER_BRANCH,
	EDAC_MC_LAYER_CHANNEL,
	EDAC_MC_LAYER_SLOT,
	EDAC_MC_LAYER_CHIP_SELECT,
	EDAC_MC_LAYER_ALL_MEM,
पूर्ण;

/**
 * काष्ठा edac_mc_layer - describes the memory controller hierarchy
 * @type:		layer type
 * @size:		number of components per layer. For example,
 *			अगर the channel layer has two channels, size = 2
 * @is_virt_csrow:	This layer is part of the "csrow" when old API
 *			compatibility mode is enabled. Otherwise, it is
 *			a channel
 */
काष्ठा edac_mc_layer अणु
	क्रमागत edac_mc_layer_type	type;
	अचिन्हित		size;
	bool			is_virt_csrow;
पूर्ण;

/*
 * Maximum number of layers used by the memory controller to uniquely
 * identअगरy a single memory stick.
 * NOTE: Changing this स्थिरant requires not only to change the स्थिरant
 * below, but also to change the existing code at the core, as there are
 * some code there that are optimized क्रम 3 layers.
 */
#घोषणा EDAC_MAX_LAYERS		3

काष्ठा dimm_info अणु
	काष्ठा device dev;

	अक्षर label[EDAC_MC_LABEL_LEN + 1];	/* DIMM label on motherboard */

	/* Memory location data */
	अचिन्हित पूर्णांक location[EDAC_MAX_LAYERS];

	काष्ठा mem_ctl_info *mci;	/* the parent */
	अचिन्हित पूर्णांक idx;		/* index within the parent dimm array */

	u32 grain;		/* granularity of reported error in bytes */
	क्रमागत dev_type dtype;	/* memory device type */
	क्रमागत mem_type mtype;	/* memory dimm type */
	क्रमागत edac_type edac_mode;	/* EDAC mode क्रम this dimm */

	u32 nr_pages;			/* number of pages on this dimm */

	अचिन्हित पूर्णांक csrow, cschannel;	/* Poपूर्णांकs to the old API data */

	u16 smbios_handle;              /* Handle क्रम SMBIOS type 17 */

	u32 ce_count;
	u32 ue_count;
पूर्ण;

/**
 * काष्ठा rank_info - contains the inक्रमmation क्रम one DIMM rank
 *
 * @chan_idx:	channel number where the rank is (typically, 0 or 1)
 * @ce_count:	number of correctable errors क्रम this rank
 * @csrow:	A poपूर्णांकer to the chip select row काष्ठाure (the parent
 *		काष्ठाure). The location of the rank is given by
 *		the (csrow->csrow_idx, chan_idx) vector.
 * @dimm:	A poपूर्णांकer to the DIMM काष्ठाure, where the DIMM label
 *		inक्रमmation is stored.
 *
 * FIXME: Currently, the EDAC core model will assume one DIMM per rank.
 *	  This is a bad assumption, but it makes this patch easier. Later
 *	  patches in this series will fix this issue.
 */
काष्ठा rank_info अणु
	पूर्णांक chan_idx;
	काष्ठा csrow_info *csrow;
	काष्ठा dimm_info *dimm;

	u32 ce_count;		/* Correctable Errors क्रम this csrow */
पूर्ण;

काष्ठा csrow_info अणु
	काष्ठा device dev;

	/* Used only by edac_mc_find_csrow_by_page() */
	अचिन्हित दीर्घ first_page;	/* first page number in csrow */
	अचिन्हित दीर्घ last_page;	/* last page number in csrow */
	अचिन्हित दीर्घ page_mask;	/* used क्रम पूर्णांकerleaving -
					 * 0UL क्रम non पूर्णांकlv */

	पूर्णांक csrow_idx;			/* the chip-select row */

	u32 ue_count;		/* Uncorrectable Errors क्रम this csrow */
	u32 ce_count;		/* Correctable Errors क्रम this csrow */

	काष्ठा mem_ctl_info *mci;	/* the parent */

	/* channel inक्रमmation क्रम this csrow */
	u32 nr_channels;
	काष्ठा rank_info **channels;
पूर्ण;

/*
 * काष्ठा errcount_attribute - used to store the several error counts
 */
काष्ठा errcount_attribute_data अणु
	पूर्णांक n_layers;
	पूर्णांक pos[EDAC_MAX_LAYERS];
	पूर्णांक layer0, layer1, layer2;
पूर्ण;

/**
 * काष्ठा edac_raw_error_desc - Raw error report काष्ठाure
 * @grain:			minimum granularity क्रम an error report, in bytes
 * @error_count:		number of errors of the same type
 * @type:			severity of the error (CE/UE/Fatal)
 * @top_layer:			top layer of the error (layer[0])
 * @mid_layer:			middle layer of the error (layer[1])
 * @low_layer:			low layer of the error (layer[2])
 * @page_frame_number:		page where the error happened
 * @offset_in_page:		page offset
 * @syndrome:			syndrome of the error (or 0 अगर unknown or अगर
 * 				the syndrome is not applicable)
 * @msg:			error message
 * @location:			location of the error
 * @label:			label of the affected DIMM(s)
 * @other_detail:		other driver-specअगरic detail about the error
 */
काष्ठा edac_raw_error_desc अणु
	अक्षर location[LOCATION_SIZE];
	अक्षर label[(EDAC_MC_LABEL_LEN + 1 + माप(OTHER_LABEL)) * EDAC_MAX_LABELS];
	दीर्घ grain;

	u16 error_count;
	क्रमागत hw_event_mc_err_type type;
	पूर्णांक top_layer;
	पूर्णांक mid_layer;
	पूर्णांक low_layer;
	अचिन्हित दीर्घ page_frame_number;
	अचिन्हित दीर्घ offset_in_page;
	अचिन्हित दीर्घ syndrome;
	स्थिर अक्षर *msg;
	स्थिर अक्षर *other_detail;
पूर्ण;

/* MEMORY controller inक्रमmation काष्ठाure
 */
काष्ठा mem_ctl_info अणु
	काष्ठा device			dev;
	काष्ठा bus_type			*bus;

	काष्ठा list_head link;	/* क्रम global list of mem_ctl_info काष्ठाs */

	काष्ठा module *owner;	/* Module owner of this control काष्ठा */

	अचिन्हित दीर्घ mtype_cap;	/* memory types supported by mc */
	अचिन्हित दीर्घ edac_ctl_cap;	/* Mem controller EDAC capabilities */
	अचिन्हित दीर्घ edac_cap;	/* configuration capabilities - this is
				 * बंदly related to edac_ctl_cap.  The
				 * dअगरference is that the controller may be
				 * capable of s4ecd4ed which would be listed
				 * in edac_ctl_cap, but अगर channels aren't
				 * capable of s4ecd4ed then the edac_cap would
				 * not have that capability.
				 */
	अचिन्हित दीर्घ scrub_cap;	/* chipset scrub capabilities */
	क्रमागत scrub_type scrub_mode;	/* current scrub mode */

	/* Translates sdram memory scrub rate given in bytes/sec to the
	   पूर्णांकernal representation and configures whatever अन्यथा needs
	   to be configured.
	 */
	पूर्णांक (*set_sdram_scrub_rate) (काष्ठा mem_ctl_info * mci, u32 bw);

	/* Get the current sdram memory scrub rate from the पूर्णांकernal
	   representation and converts it to the बंदst matching
	   bandwidth in bytes/sec.
	 */
	पूर्णांक (*get_sdram_scrub_rate) (काष्ठा mem_ctl_info * mci);


	/* poपूर्णांकer to edac checking routine */
	व्योम (*edac_check) (काष्ठा mem_ctl_info * mci);

	/*
	 * Remaps memory pages: controller pages to physical pages.
	 * For most MC's, this will be शून्य.
	 */
	/* FIXME - why not send the phys page to begin with? */
	अचिन्हित दीर्घ (*ctl_page_to_phys) (काष्ठा mem_ctl_info * mci,
					   अचिन्हित दीर्घ page);
	पूर्णांक mc_idx;
	काष्ठा csrow_info **csrows;
	अचिन्हित पूर्णांक nr_csrows, num_cschannel;

	/*
	 * Memory Controller hierarchy
	 *
	 * There are basically two types of memory controller: the ones that
	 * sees memory sticks ("dimms"), and the ones that sees memory ranks.
	 * All old memory controllers क्रमागतerate memories per rank, but most
	 * of the recent drivers क्रमागतerate memories per DIMM, instead.
	 * When the memory controller is per rank, csbased is true.
	 */
	अचिन्हित पूर्णांक n_layers;
	काष्ठा edac_mc_layer *layers;
	bool csbased;

	/*
	 * DIMM info. Will eventually हटाओ the entire csrows_info some day
	 */
	अचिन्हित पूर्णांक tot_dimms;
	काष्ठा dimm_info **dimms;

	/*
	 * FIXME - what about controllers on other busses? - IDs must be
	 * unique.  dev poपूर्णांकer should be sufficiently unique, but
	 * BUS:SLOT.FUNC numbers may not be unique.
	 */
	काष्ठा device *pdev;
	स्थिर अक्षर *mod_name;
	स्थिर अक्षर *ctl_name;
	स्थिर अक्षर *dev_name;
	व्योम *pvt_info;
	अचिन्हित दीर्घ start_समय;	/* mci load start समय (in jअगरfies) */

	/*
	 * drivers shouldn't access those fields directly, as the core
	 * alपढ़ोy handles that.
	 */
	u32 ce_noinfo_count, ue_noinfo_count;
	u32 ue_mc, ce_mc;

	काष्ठा completion complete;

	/* Additional top controller level attributes, but specअगरied
	 * by the low level driver.
	 *
	 * Set by the low level driver to provide attributes at the
	 * controller level.
	 * An array of काष्ठाures, शून्य terminated
	 *
	 * If attributes are desired, then set to array of attributes
	 * If no attributes are desired, leave शून्य
	 */
	स्थिर काष्ठा mcidev_sysfs_attribute *mc_driver_sysfs_attributes;

	/* work काष्ठा क्रम this MC */
	काष्ठा delayed_work work;

	/*
	 * Used to report an error - by being at the global काष्ठा
	 * makes the memory allocated by the EDAC core
	 */
	काष्ठा edac_raw_error_desc error_desc;

	/* the पूर्णांकernal state of this controller instance */
	पूर्णांक op_state;

	काष्ठा dentry *debugfs;
	u8 fake_inject_layer[EDAC_MAX_LAYERS];
	bool fake_inject_ue;
	u16 fake_inject_count;
पूर्ण;

#घोषणा mci_क्रम_each_dimm(mci, dimm)				\
	क्रम ((dimm) = (mci)->dimms[0];				\
	     (dimm);						\
	     (dimm) = (dimm)->idx + 1 < (mci)->tot_dimms	\
		     ? (mci)->dimms[(dimm)->idx + 1]		\
		     : शून्य)

/**
 * edac_get_dimm - Get DIMM info from a memory controller given by
 *                 [layer0,layer1,layer2] position
 *
 * @mci:	MC descriptor काष्ठा mem_ctl_info
 * @layer0:	layer0 position
 * @layer1:	layer1 position. Unused अगर n_layers < 2
 * @layer2:	layer2 position. Unused अगर n_layers < 3
 *
 * For 1 layer, this function वापसs "dimms[layer0]";
 *
 * For 2 layers, this function is similar to allocating a two-dimensional
 * array and वापसing "dimms[layer0][layer1]";
 *
 * For 3 layers, this function is similar to allocating a tri-dimensional
 * array and वापसing "dimms[layer0][layer1][layer2]";
 */
अटल अंतरभूत काष्ठा dimm_info *edac_get_dimm(काष्ठा mem_ctl_info *mci,
	पूर्णांक layer0, पूर्णांक layer1, पूर्णांक layer2)
अणु
	पूर्णांक index;

	अगर (layer0 < 0
	    || (mci->n_layers > 1 && layer1 < 0)
	    || (mci->n_layers > 2 && layer2 < 0))
		वापस शून्य;

	index = layer0;

	अगर (mci->n_layers > 1)
		index = index * mci->layers[1].size + layer1;

	अगर (mci->n_layers > 2)
		index = index * mci->layers[2].size + layer2;

	अगर (index < 0 || index >= mci->tot_dimms)
		वापस शून्य;

	अगर (WARN_ON_ONCE(mci->dimms[index]->idx != index))
		वापस शून्य;

	वापस mci->dimms[index];
पूर्ण
#पूर्ण_अगर /* _LINUX_EDAC_H_ */
