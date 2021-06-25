<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * न_अंकD flash simulator.
 *
 * Author: Artem B. Bityuckiy <dedekind@oktetद_असल.ru>, <dedekind@infradead.org>
 *
 * Copyright (C) 2004 Nokia Corporation
 *
 * Note: NS means "NAND Simulator".
 * Note: Input means input TO flash chip, output means output FROM chip.
 */

#घोषणा pr_fmt(fmt)  "[nandsim]" fmt

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/math64.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>

/* Default simulator parameters values */
#अगर !defined(CONFIG_न_अंकDSIM_FIRST_ID_BYTE)  || \
    !defined(CONFIG_न_अंकDSIM_SECOND_ID_BYTE) || \
    !defined(CONFIG_न_अंकDSIM_THIRD_ID_BYTE)  || \
    !defined(CONFIG_न_अंकDSIM_FOURTH_ID_BYTE)
#घोषणा CONFIG_न_अंकDSIM_FIRST_ID_BYTE  0x98
#घोषणा CONFIG_न_अंकDSIM_SECOND_ID_BYTE 0x39
#घोषणा CONFIG_न_अंकDSIM_THIRD_ID_BYTE  0xFF /* No byte */
#घोषणा CONFIG_न_अंकDSIM_FOURTH_ID_BYTE 0xFF /* No byte */
#पूर्ण_अगर

#अगर_अघोषित CONFIG_न_अंकDSIM_ACCESS_DELAY
#घोषणा CONFIG_न_अंकDSIM_ACCESS_DELAY 25
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_PROGRAMM_DELAY
#घोषणा CONFIG_न_अंकDSIM_PROGRAMM_DELAY 200
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_ERASE_DELAY
#घोषणा CONFIG_न_अंकDSIM_ERASE_DELAY 2
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_OUTPUT_CYCLE
#घोषणा CONFIG_न_अंकDSIM_OUTPUT_CYCLE 40
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_INPUT_CYCLE
#घोषणा CONFIG_न_अंकDSIM_INPUT_CYCLE  50
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_BUS_WIDTH
#घोषणा CONFIG_न_अंकDSIM_BUS_WIDTH  8
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_DO_DELAYS
#घोषणा CONFIG_न_अंकDSIM_DO_DELAYS  0
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_LOG
#घोषणा CONFIG_न_अंकDSIM_LOG        0
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_DBG
#घोषणा CONFIG_न_अंकDSIM_DBG        0
#पूर्ण_अगर
#अगर_अघोषित CONFIG_न_अंकDSIM_MAX_PARTS
#घोषणा CONFIG_न_अंकDSIM_MAX_PARTS  32
#पूर्ण_अगर

अटल uपूर्णांक access_delay   = CONFIG_न_अंकDSIM_ACCESS_DELAY;
अटल uपूर्णांक programm_delay = CONFIG_न_अंकDSIM_PROGRAMM_DELAY;
अटल uपूर्णांक erase_delay    = CONFIG_न_अंकDSIM_ERASE_DELAY;
अटल uपूर्णांक output_cycle   = CONFIG_न_अंकDSIM_OUTPUT_CYCLE;
अटल uपूर्णांक input_cycle    = CONFIG_न_अंकDSIM_INPUT_CYCLE;
अटल uपूर्णांक bus_width      = CONFIG_न_अंकDSIM_BUS_WIDTH;
अटल uपूर्णांक करो_delays      = CONFIG_न_अंकDSIM_DO_DELAYS;
अटल uपूर्णांक log            = CONFIG_न_अंकDSIM_LOG;
अटल uपूर्णांक dbg            = CONFIG_न_अंकDSIM_DBG;
अटल अचिन्हित दीर्घ parts[CONFIG_न_अंकDSIM_MAX_PARTS];
अटल अचिन्हित पूर्णांक parts_num;
अटल अक्षर *badblocks = शून्य;
अटल अक्षर *weakblocks = शून्य;
अटल अक्षर *weakpages = शून्य;
अटल अचिन्हित पूर्णांक bitflips = 0;
अटल अक्षर *gravepages = शून्य;
अटल अचिन्हित पूर्णांक overridesize = 0;
अटल अक्षर *cache_file = शून्य;
अटल अचिन्हित पूर्णांक bbt;
अटल अचिन्हित पूर्णांक bch;
अटल u_अक्षर id_bytes[8] = अणु
	[0] = CONFIG_न_अंकDSIM_FIRST_ID_BYTE,
	[1] = CONFIG_न_अंकDSIM_SECOND_ID_BYTE,
	[2] = CONFIG_न_अंकDSIM_THIRD_ID_BYTE,
	[3] = CONFIG_न_अंकDSIM_FOURTH_ID_BYTE,
	[4 ... 7] = 0xFF,
पूर्ण;

module_param_array(id_bytes, byte, शून्य, 0400);
module_param_named(first_id_byte, id_bytes[0], byte, 0400);
module_param_named(second_id_byte, id_bytes[1], byte, 0400);
module_param_named(third_id_byte, id_bytes[2], byte, 0400);
module_param_named(fourth_id_byte, id_bytes[3], byte, 0400);
module_param(access_delay,   uपूर्णांक, 0400);
module_param(programm_delay, uपूर्णांक, 0400);
module_param(erase_delay,    uपूर्णांक, 0400);
module_param(output_cycle,   uपूर्णांक, 0400);
module_param(input_cycle,    uपूर्णांक, 0400);
module_param(bus_width,      uपूर्णांक, 0400);
module_param(करो_delays,      uपूर्णांक, 0400);
module_param(log,            uपूर्णांक, 0400);
module_param(dbg,            uपूर्णांक, 0400);
module_param_array(parts, uदीर्घ, &parts_num, 0400);
module_param(badblocks,      अक्षरp, 0400);
module_param(weakblocks,     अक्षरp, 0400);
module_param(weakpages,      अक्षरp, 0400);
module_param(bitflips,       uपूर्णांक, 0400);
module_param(gravepages,     अक्षरp, 0400);
module_param(overridesize,   uपूर्णांक, 0400);
module_param(cache_file,     अक्षरp, 0400);
module_param(bbt,	     uपूर्णांक, 0400);
module_param(bch,	     uपूर्णांक, 0400);

MODULE_PARM_DESC(id_bytes,       "The ID bytes returned by NAND Flash 'read ID' command");
MODULE_PARM_DESC(first_id_byte,  "The first byte returned by NAND Flash 'read ID' command (manufacturer ID) (obsolete)");
MODULE_PARM_DESC(second_id_byte, "The second byte returned by NAND Flash 'read ID' command (chip ID) (obsolete)");
MODULE_PARM_DESC(third_id_byte,  "The third byte returned by NAND Flash 'read ID' command (obsolete)");
MODULE_PARM_DESC(fourth_id_byte, "The fourth byte returned by NAND Flash 'read ID' command (obsolete)");
MODULE_PARM_DESC(access_delay,   "Initial page access delay (microseconds)");
MODULE_PARM_DESC(programm_delay, "Page programm delay (microseconds");
MODULE_PARM_DESC(erase_delay,    "Sector erase delay (milliseconds)");
MODULE_PARM_DESC(output_cycle,   "Word output (from flash) time (nanoseconds)");
MODULE_PARM_DESC(input_cycle,    "Word input (to flash) time (nanoseconds)");
MODULE_PARM_DESC(bus_width,      "Chip's bus width (8- or 16-bit)");
MODULE_PARM_DESC(करो_delays,      "Simulate NAND delays using busy-waits if not zero");
MODULE_PARM_DESC(log,            "Perform logging if not zero");
MODULE_PARM_DESC(dbg,            "Output debug information if not zero");
MODULE_PARM_DESC(parts,          "Partition sizes (in erase blocks) separated by commas");
/* Page and erase block positions क्रम the following parameters are independent of any partitions */
MODULE_PARM_DESC(badblocks,      "Erase blocks that are initially marked bad, separated by commas");
MODULE_PARM_DESC(weakblocks,     "Weak erase blocks [: remaining erase cycles (defaults to 3)]"
				 " separated by commas e.g. 113:2 means eb 113"
				 " can be erased only twice before failing");
MODULE_PARM_DESC(weakpages,      "Weak pages [: maximum writes (defaults to 3)]"
				 " separated by commas e.g. 1401:2 means page 1401"
				 " can be written only twice before failing");
MODULE_PARM_DESC(bitflips,       "Maximum number of random bit flips per page (zero by default)");
MODULE_PARM_DESC(gravepages,     "Pages that lose data [: maximum reads (defaults to 3)]"
				 " separated by commas e.g. 1401:2 means page 1401"
				 " can be read only twice before failing");
MODULE_PARM_DESC(overridesize,   "Specifies the NAND Flash size overriding the ID bytes. "
				 "The size is specified in erase blocks and as the exponent of a power of two"
				 " e.g. 5 means a size of 32 erase blocks");
MODULE_PARM_DESC(cache_file,     "File to use to cache nand pages instead of memory");
MODULE_PARM_DESC(bbt,		 "0 OOB, 1 BBT with marker in OOB, 2 BBT with marker in data area");
MODULE_PARM_DESC(bch,		 "Enable BCH ecc and set how many bits should "
				 "be correctable in 512-byte blocks");

/* The largest possible page size */
#घोषणा NS_LARGEST_PAGE_SIZE	4096

/* Simulator's output macros (logging, debugging, warning, error) */
#घोषणा NS_LOG(args...) \
	करो अणु अगर (log) pr_debug(" log: " args); पूर्ण जबतक(0)
#घोषणा NS_DBG(args...) \
	करो अणु अगर (dbg) pr_debug(" debug: " args); पूर्ण जबतक(0)
#घोषणा NS_WARN(args...) \
	करो अणु pr_warn(" warning: " args); पूर्ण जबतक(0)
#घोषणा NS_ERR(args...) \
	करो अणु pr_err(" error: " args); पूर्ण जबतक(0)
#घोषणा NS_INFO(args...) \
	करो अणु pr_info(" " args); पूर्ण जबतक(0)

/* Busy-रुको delay macros (microseconds, milliseconds) */
#घोषणा NS_UDELAY(us) \
        करो अणु अगर (करो_delays) udelay(us); पूर्ण जबतक(0)
#घोषणा NS_MDELAY(us) \
        करो अणु अगर (करो_delays) mdelay(us); पूर्ण जबतक(0)

/* Is the nandsim काष्ठाure initialized ? */
#घोषणा NS_IS_INITIALIZED(ns) ((ns)->geom.totsz != 0)

/* Good operation completion status */
#घोषणा NS_STATUS_OK(ns) (न_अंकD_STATUS_READY | (न_अंकD_STATUS_WP * ((ns)->lines.wp == 0)))

/* Operation failed completion status */
#घोषणा NS_STATUS_FAILED(ns) (न_अंकD_STATUS_FAIL | NS_STATUS_OK(ns))

/* Calculate the page offset in flash RAM image by (row, column) address */
#घोषणा NS_RAW_OFFSET(ns) \
	(((ns)->regs.row * (ns)->geom.pgszoob) + (ns)->regs.column)

/* Calculate the OOB offset in flash RAM image by (row, column) address */
#घोषणा NS_RAW_OFFSET_OOB(ns) (NS_RAW_OFFSET(ns) + ns->geom.pgsz)

/* After a command is input, the simulator goes to one of the following states */
#घोषणा STATE_CMD_READ0        0x00000001 /* पढ़ो data from the beginning of page */
#घोषणा STATE_CMD_READ1        0x00000002 /* पढ़ो data from the second half of page */
#घोषणा STATE_CMD_READSTART    0x00000003 /* पढ़ो data second command (large page devices) */
#घोषणा STATE_CMD_PAGEPROG     0x00000004 /* start page program */
#घोषणा STATE_CMD_READOOB      0x00000005 /* पढ़ो OOB area */
#घोषणा STATE_CMD_ERASE1       0x00000006 /* sector erase first command */
#घोषणा STATE_CMD_STATUS       0x00000007 /* पढ़ो status */
#घोषणा STATE_CMD_SEQIN        0x00000009 /* sequential data input */
#घोषणा STATE_CMD_READID       0x0000000A /* पढ़ो ID */
#घोषणा STATE_CMD_ERASE2       0x0000000B /* sector erase second command */
#घोषणा STATE_CMD_RESET        0x0000000C /* reset */
#घोषणा STATE_CMD_RNDOUT       0x0000000D /* अक्रमom output command */
#घोषणा STATE_CMD_RNDOUTSTART  0x0000000E /* अक्रमom output start command */
#घोषणा STATE_CMD_MASK         0x0000000F /* command states mask */

/* After an address is input, the simulator goes to one of these states */
#घोषणा STATE_ADDR_PAGE        0x00000010 /* full (row, column) address is accepted */
#घोषणा STATE_ADDR_SEC         0x00000020 /* sector address was accepted */
#घोषणा STATE_ADDR_COLUMN      0x00000030 /* column address was accepted */
#घोषणा STATE_ADDR_ZERO        0x00000040 /* one byte zero address was accepted */
#घोषणा STATE_ADDR_MASK        0x00000070 /* address states mask */

/* During data input/output the simulator is in these states */
#घोषणा STATE_DATAIN           0x00000100 /* रुकोing क्रम data input */
#घोषणा STATE_DATAIN_MASK      0x00000100 /* data input states mask */

#घोषणा STATE_DATAOUT          0x00001000 /* रुकोing क्रम page data output */
#घोषणा STATE_DATAOUT_ID       0x00002000 /* रुकोing क्रम ID bytes output */
#घोषणा STATE_DATAOUT_STATUS   0x00003000 /* रुकोing क्रम status output */
#घोषणा STATE_DATAOUT_MASK     0x00007000 /* data output states mask */

/* Previous operation is करोne, पढ़ोy to accept new requests */
#घोषणा STATE_READY            0x00000000

/* This state is used to mark that the next state isn't known yet */
#घोषणा STATE_UNKNOWN          0x10000000

/* Simulator's actions bit masks */
#घोषणा ACTION_CPY       0x00100000 /* copy page/OOB to the पूर्णांकernal buffer */
#घोषणा ACTION_PRGPAGE   0x00200000 /* program the पूर्णांकernal buffer to flash */
#घोषणा ACTION_SECERASE  0x00300000 /* erase sector */
#घोषणा ACTION_ZEROOFF   0x00400000 /* करोn't add any offset to address */
#घोषणा ACTION_HALFOFF   0x00500000 /* add to address half of page */
#घोषणा ACTION_OOBOFF    0x00600000 /* add to address OOB offset */
#घोषणा ACTION_MASK      0x00700000 /* action mask */

#घोषणा NS_OPER_NUM      13 /* Number of operations supported by the simulator */
#घोषणा NS_OPER_STATES   6  /* Maximum number of states in operation */

#घोषणा OPT_ANY          0xFFFFFFFF /* any chip supports this operation */
#घोषणा OPT_PAGE512      0x00000002 /* 512-byte  page chips */
#घोषणा OPT_PAGE2048     0x00000008 /* 2048-byte page chips */
#घोषणा OPT_PAGE512_8BIT 0x00000040 /* 512-byte page chips with 8-bit bus width */
#घोषणा OPT_PAGE4096     0x00000080 /* 4096-byte page chips */
#घोषणा OPT_LARGEPAGE    (OPT_PAGE2048 | OPT_PAGE4096) /* 2048 & 4096-byte page chips */
#घोषणा OPT_SMALLPAGE    (OPT_PAGE512) /* 512-byte page chips */

/* Remove action bits from state */
#घोषणा NS_STATE(x) ((x) & ~ACTION_MASK)

/*
 * Maximum previous states which need to be saved. Currently saving is
 * only needed क्रम page program operation with preceded पढ़ो command
 * (which is only valid क्रम 512-byte pages).
 */
#घोषणा NS_MAX_PREVSTATES 1

/* Maximum page cache pages needed to पढ़ो or ग_लिखो a न_अंकD page to the cache_file */
#घोषणा NS_MAX_HELD_PAGES 16

/*
 * A जोड़ to represent flash memory contents and flash buffer.
 */
जोड़ ns_mem अणु
	u_अक्षर *byte;    /* क्रम byte access */
	uपूर्णांक16_t *word;  /* क्रम 16-bit word access */
पूर्ण;

/*
 * The काष्ठाure which describes all the पूर्णांकernal simulator data.
 */
काष्ठा nandsim अणु
	काष्ठा nand_chip chip;
	काष्ठा nand_controller base;
	काष्ठा mtd_partition partitions[CONFIG_न_अंकDSIM_MAX_PARTS];
	अचिन्हित पूर्णांक nbparts;

	uपूर्णांक busw;              /* flash chip bus width (8 or 16) */
	u_अक्षर ids[8];          /* chip's ID bytes */
	uपूर्णांक32_t options;       /* chip's अक्षरacteristic bits */
	uपूर्णांक32_t state;         /* current chip state */
	uपूर्णांक32_t nxstate;       /* next expected state */

	uपूर्णांक32_t *op;           /* current operation, शून्य operations isn't known yet  */
	uपूर्णांक32_t pstates[NS_MAX_PREVSTATES]; /* previous states */
	uपूर्णांक16_t npstates;      /* number of previous states saved */
	uपूर्णांक16_t stateidx;      /* current state index */

	/* The simulated न_अंकD flash pages array */
	जोड़ ns_mem *pages;

	/* Slab allocator क्रम nand pages */
	काष्ठा kmem_cache *nand_pages_slab;

	/* Internal buffer of page + OOB size bytes */
	जोड़ ns_mem buf;

	/* न_अंकD flash "geometry" */
	काष्ठा अणु
		uपूर्णांक64_t totsz;     /* total flash size, bytes */
		uपूर्णांक32_t secsz;     /* flash sector (erase block) size, bytes */
		uपूर्णांक pgsz;          /* न_अंकD flash page size, bytes */
		uपूर्णांक oobsz;         /* page OOB area size, bytes */
		uपूर्णांक64_t totszoob;  /* total flash size including OOB, bytes */
		uपूर्णांक pgszoob;       /* page size including OOB , bytes*/
		uपूर्णांक secszoob;      /* sector size including OOB, bytes */
		uपूर्णांक pgnum;         /* total number of pages */
		uपूर्णांक pgsec;         /* number of pages per sector */
		uपूर्णांक secshअगरt;      /* bits number in sector size */
		uपूर्णांक pgshअगरt;       /* bits number in page size */
		uपूर्णांक pgaddrbytes;   /* bytes per page address */
		uपूर्णांक secaddrbytes;  /* bytes per sector address */
		uपूर्णांक idbytes;       /* the number ID bytes that this chip outमाला_दो */
	पूर्ण geom;

	/* न_अंकD flash पूर्णांकernal रेजिस्टरs */
	काष्ठा अणु
		अचिन्हित command; /* the command रेजिस्टर */
		u_अक्षर   status;  /* the status रेजिस्टर */
		uपूर्णांक     row;     /* the page number */
		uपूर्णांक     column;  /* the offset within page */
		uपूर्णांक     count;   /* पूर्णांकernal counter */
		uपूर्णांक     num;     /* number of bytes which must be processed */
		uपूर्णांक     off;     /* fixed page offset */
	पूर्ण regs;

	/* न_अंकD flash lines state */
        काष्ठा अणु
                पूर्णांक ce;  /* chip Enable */
                पूर्णांक cle; /* command Latch Enable */
                पूर्णांक ale; /* address Latch Enable */
                पूर्णांक wp;  /* ग_लिखो Protect */
        पूर्ण lines;

	/* Fields needed when using a cache file */
	काष्ठा file *cfile; /* Open file */
	अचिन्हित दीर्घ *pages_written; /* Which pages have been written */
	व्योम *file_buf;
	काष्ठा page *held_pages[NS_MAX_HELD_PAGES];
	पूर्णांक held_cnt;

	/* debugfs entry */
	काष्ठा dentry *dent;
पूर्ण;

/*
 * Operations array. To perक्रमm any operation the simulator must pass
 * through the correspondent states chain.
 */
अटल काष्ठा nandsim_operations अणु
	uपूर्णांक32_t reqopts;  /* options which are required to perक्रमm the operation */
	uपूर्णांक32_t states[NS_OPER_STATES]; /* operation's states */
पूर्ण ops[NS_OPER_NUM] = अणु
	/* Read page + OOB from the beginning */
	अणुOPT_SMALLPAGE, अणुSTATE_CMD_READ0 | ACTION_ZEROOFF, STATE_ADDR_PAGE | ACTION_CPY,
			STATE_DATAOUT, STATE_READYपूर्णपूर्ण,
	/* Read page + OOB from the second half */
	अणुOPT_PAGE512_8BIT, अणुSTATE_CMD_READ1 | ACTION_HALFOFF, STATE_ADDR_PAGE | ACTION_CPY,
			STATE_DATAOUT, STATE_READYपूर्णपूर्ण,
	/* Read OOB */
	अणुOPT_SMALLPAGE, अणुSTATE_CMD_READOOB | ACTION_OOBOFF, STATE_ADDR_PAGE | ACTION_CPY,
			STATE_DATAOUT, STATE_READYपूर्णपूर्ण,
	/* Program page starting from the beginning */
	अणुOPT_ANY, अणुSTATE_CMD_SEQIN, STATE_ADDR_PAGE, STATE_DATAIN,
			STATE_CMD_PAGEPROG | ACTION_PRGPAGE, STATE_READYपूर्णपूर्ण,
	/* Program page starting from the beginning */
	अणुOPT_SMALLPAGE, अणुSTATE_CMD_READ0, STATE_CMD_SEQIN | ACTION_ZEROOFF, STATE_ADDR_PAGE,
			      STATE_DATAIN, STATE_CMD_PAGEPROG | ACTION_PRGPAGE, STATE_READYपूर्णपूर्ण,
	/* Program page starting from the second half */
	अणुOPT_PAGE512, अणुSTATE_CMD_READ1, STATE_CMD_SEQIN | ACTION_HALFOFF, STATE_ADDR_PAGE,
			      STATE_DATAIN, STATE_CMD_PAGEPROG | ACTION_PRGPAGE, STATE_READYपूर्णपूर्ण,
	/* Program OOB */
	अणुOPT_SMALLPAGE, अणुSTATE_CMD_READOOB, STATE_CMD_SEQIN | ACTION_OOBOFF, STATE_ADDR_PAGE,
			      STATE_DATAIN, STATE_CMD_PAGEPROG | ACTION_PRGPAGE, STATE_READYपूर्णपूर्ण,
	/* Erase sector */
	अणुOPT_ANY, अणुSTATE_CMD_ERASE1, STATE_ADDR_SEC, STATE_CMD_ERASE2 | ACTION_SECERASE, STATE_READYपूर्णपूर्ण,
	/* Read status */
	अणुOPT_ANY, अणुSTATE_CMD_STATUS, STATE_DATAOUT_STATUS, STATE_READYपूर्णपूर्ण,
	/* Read ID */
	अणुOPT_ANY, अणुSTATE_CMD_READID, STATE_ADDR_ZERO, STATE_DATAOUT_ID, STATE_READYपूर्णपूर्ण,
	/* Large page devices पढ़ो page */
	अणुOPT_LARGEPAGE, अणुSTATE_CMD_READ0, STATE_ADDR_PAGE, STATE_CMD_READSTART | ACTION_CPY,
			       STATE_DATAOUT, STATE_READYपूर्णपूर्ण,
	/* Large page devices अक्रमom page पढ़ो */
	अणुOPT_LARGEPAGE, अणुSTATE_CMD_RNDOUT, STATE_ADDR_COLUMN, STATE_CMD_RNDOUTSTART | ACTION_CPY,
			       STATE_DATAOUT, STATE_READYपूर्णपूर्ण,
पूर्ण;

काष्ठा weak_block अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक erase_block_no;
	अचिन्हित पूर्णांक max_erases;
	अचिन्हित पूर्णांक erases_करोne;
पूर्ण;

अटल LIST_HEAD(weak_blocks);

काष्ठा weak_page अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक page_no;
	अचिन्हित पूर्णांक max_ग_लिखोs;
	अचिन्हित पूर्णांक ग_लिखोs_करोne;
पूर्ण;

अटल LIST_HEAD(weak_pages);

काष्ठा grave_page अणु
	काष्ठा list_head list;
	अचिन्हित पूर्णांक page_no;
	अचिन्हित पूर्णांक max_पढ़ोs;
	अचिन्हित पूर्णांक पढ़ोs_करोne;
पूर्ण;

अटल LIST_HEAD(grave_pages);

अटल अचिन्हित दीर्घ *erase_block_wear = शून्य;
अटल अचिन्हित पूर्णांक wear_eb_count = 0;
अटल अचिन्हित दीर्घ total_wear = 0;

/* MTD काष्ठाure क्रम न_अंकD controller */
अटल काष्ठा mtd_info *nsmtd;

अटल पूर्णांक ns_show(काष्ठा seq_file *m, व्योम *निजी)
अणु
	अचिन्हित दीर्घ wmin = -1, wmax = 0, avg;
	अचिन्हित दीर्घ deciles[10], decile_max[10], tot = 0;
	अचिन्हित पूर्णांक i;

	/* Calc wear stats */
	क्रम (i = 0; i < wear_eb_count; ++i) अणु
		अचिन्हित दीर्घ wear = erase_block_wear[i];
		अगर (wear < wmin)
			wmin = wear;
		अगर (wear > wmax)
			wmax = wear;
		tot += wear;
	पूर्ण

	क्रम (i = 0; i < 9; ++i) अणु
		deciles[i] = 0;
		decile_max[i] = (wmax * (i + 1) + 5) / 10;
	पूर्ण
	deciles[9] = 0;
	decile_max[9] = wmax;
	क्रम (i = 0; i < wear_eb_count; ++i) अणु
		पूर्णांक d;
		अचिन्हित दीर्घ wear = erase_block_wear[i];
		क्रम (d = 0; d < 10; ++d)
			अगर (wear <= decile_max[d]) अणु
				deciles[d] += 1;
				अवरोध;
			पूर्ण
	पूर्ण
	avg = tot / wear_eb_count;

	/* Output wear report */
	seq_म_लिखो(m, "Total numbers of erases:  %lu\n", tot);
	seq_म_लिखो(m, "Number of erase blocks:   %u\n", wear_eb_count);
	seq_म_लिखो(m, "Average number of erases: %lu\n", avg);
	seq_म_लिखो(m, "Maximum number of erases: %lu\n", wmax);
	seq_म_लिखो(m, "Minimum number of erases: %lu\n", wmin);
	क्रम (i = 0; i < 10; ++i) अणु
		अचिन्हित दीर्घ from = (i ? decile_max[i - 1] + 1 : 0);
		अगर (from > decile_max[i])
			जारी;
		seq_म_लिखो(m, "Number of ebs with erase counts from %lu to %lu : %lu\n",
			from,
			decile_max[i],
			deciles[i]);
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ns);

/**
 * ns_debugfs_create - initialize debugfs
 * @ns: nandsim device description object
 *
 * This function creates all debugfs files क्रम UBI device @ubi. Returns zero in
 * हाल of success and a negative error code in हाल of failure.
 */
अटल पूर्णांक ns_debugfs_create(काष्ठा nandsim *ns)
अणु
	काष्ठा dentry *root = nsmtd->dbg.dfs_dir;

	/*
	 * Just skip debugfs initialization when the debugfs directory is
	 * missing.
	 */
	अगर (IS_ERR_OR_शून्य(root)) अणु
		अगर (IS_ENABLED(CONFIG_DEBUG_FS) &&
		    !IS_ENABLED(CONFIG_MTD_PARTITIONED_MASTER))
			NS_WARN("CONFIG_MTD_PARTITIONED_MASTER must be enabled to expose debugfs stuff\n");
		वापस 0;
	पूर्ण

	ns->dent = debugfs_create_file("nandsim_wear_report", 0400, root, ns,
				       &ns_fops);
	अगर (IS_ERR_OR_शून्य(ns->dent)) अणु
		NS_ERR("cannot create \"nandsim_wear_report\" debugfs entry\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ns_debugfs_हटाओ(काष्ठा nandsim *ns)
अणु
	debugfs_हटाओ_recursive(ns->dent);
पूर्ण

/*
 * Allocate array of page poपूर्णांकers, create slab allocation क्रम an array
 * and initialize the array by शून्य poपूर्णांकers.
 *
 * RETURNS: 0 अगर success, -ENOMEM अगर memory alloc fails.
 */
अटल पूर्णांक __init ns_alloc_device(काष्ठा nandsim *ns)
अणु
	काष्ठा file *cfile;
	पूर्णांक i, err;

	अगर (cache_file) अणु
		cfile = filp_खोलो(cache_file, O_CREAT | O_RDWR | O_LARGEखाता, 0600);
		अगर (IS_ERR(cfile))
			वापस PTR_ERR(cfile);
		अगर (!(cfile->f_mode & FMODE_CAN_READ)) अणु
			NS_ERR("alloc_device: cache file not readable\n");
			err = -EINVAL;
			जाओ err_बंद_filp;
		पूर्ण
		अगर (!(cfile->f_mode & FMODE_CAN_WRITE)) अणु
			NS_ERR("alloc_device: cache file not writeable\n");
			err = -EINVAL;
			जाओ err_बंद_filp;
		पूर्ण
		ns->pages_written =
			vzalloc(array_size(माप(अचिन्हित दीर्घ),
					   BITS_TO_LONGS(ns->geom.pgnum)));
		अगर (!ns->pages_written) अणु
			NS_ERR("alloc_device: unable to allocate pages written array\n");
			err = -ENOMEM;
			जाओ err_बंद_filp;
		पूर्ण
		ns->file_buf = kदो_स्मृति(ns->geom.pgszoob, GFP_KERNEL);
		अगर (!ns->file_buf) अणु
			NS_ERR("alloc_device: unable to allocate file buf\n");
			err = -ENOMEM;
			जाओ err_मुक्त_pw;
		पूर्ण
		ns->cfile = cfile;

		वापस 0;

err_मुक्त_pw:
		vमुक्त(ns->pages_written);
err_बंद_filp:
		filp_बंद(cfile, शून्य);

		वापस err;
	पूर्ण

	ns->pages = vदो_स्मृति(array_size(माप(जोड़ ns_mem), ns->geom.pgnum));
	अगर (!ns->pages) अणु
		NS_ERR("alloc_device: unable to allocate page array\n");
		वापस -ENOMEM;
	पूर्ण
	क्रम (i = 0; i < ns->geom.pgnum; i++) अणु
		ns->pages[i].byte = शून्य;
	पूर्ण
	ns->nand_pages_slab = kmem_cache_create("nandsim",
						ns->geom.pgszoob, 0, 0, शून्य);
	अगर (!ns->nand_pages_slab) अणु
		NS_ERR("cache_create: unable to create kmem_cache\n");
		err = -ENOMEM;
		जाओ err_मुक्त_pg;
	पूर्ण

	वापस 0;

err_मुक्त_pg:
	vमुक्त(ns->pages);

	वापस err;
पूर्ण

/*
 * Free any allocated pages, and मुक्त the array of page poपूर्णांकers.
 */
अटल व्योम ns_मुक्त_device(काष्ठा nandsim *ns)
अणु
	पूर्णांक i;

	अगर (ns->cfile) अणु
		kमुक्त(ns->file_buf);
		vमुक्त(ns->pages_written);
		filp_बंद(ns->cfile, शून्य);
		वापस;
	पूर्ण

	अगर (ns->pages) अणु
		क्रम (i = 0; i < ns->geom.pgnum; i++) अणु
			अगर (ns->pages[i].byte)
				kmem_cache_मुक्त(ns->nand_pages_slab,
						ns->pages[i].byte);
		पूर्ण
		kmem_cache_destroy(ns->nand_pages_slab);
		vमुक्त(ns->pages);
	पूर्ण
पूर्ण

अटल अक्षर __init *ns_get_partition_name(पूर्णांक i)
अणु
	वापस kaप्र_लिखो(GFP_KERNEL, "NAND simulator partition %d", i);
पूर्ण

/*
 * Initialize the nandsim काष्ठाure.
 *
 * RETURNS: 0 अगर success, -ERRNO अगर failure.
 */
अटल पूर्णांक __init ns_init(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nandsim   *ns   = nand_get_controller_data(chip);
	पूर्णांक i, ret = 0;
	uपूर्णांक64_t reमुख्यs;
	uपूर्णांक64_t next_offset;

	अगर (NS_IS_INITIALIZED(ns)) अणु
		NS_ERR("init_nandsim: nandsim is already initialized\n");
		वापस -EIO;
	पूर्ण

	/* Initialize the न_अंकD flash parameters */
	ns->busw = chip->options & न_अंकD_BUSWIDTH_16 ? 16 : 8;
	ns->geom.totsz    = mtd->size;
	ns->geom.pgsz     = mtd->ग_लिखोsize;
	ns->geom.oobsz    = mtd->oobsize;
	ns->geom.secsz    = mtd->erasesize;
	ns->geom.pgszoob  = ns->geom.pgsz + ns->geom.oobsz;
	ns->geom.pgnum    = भाग_u64(ns->geom.totsz, ns->geom.pgsz);
	ns->geom.totszoob = ns->geom.totsz + (uपूर्णांक64_t)ns->geom.pgnum * ns->geom.oobsz;
	ns->geom.secshअगरt = ffs(ns->geom.secsz) - 1;
	ns->geom.pgshअगरt  = chip->page_shअगरt;
	ns->geom.pgsec    = ns->geom.secsz / ns->geom.pgsz;
	ns->geom.secszoob = ns->geom.secsz + ns->geom.oobsz * ns->geom.pgsec;
	ns->options = 0;

	अगर (ns->geom.pgsz == 512) अणु
		ns->options |= OPT_PAGE512;
		अगर (ns->busw == 8)
			ns->options |= OPT_PAGE512_8BIT;
	पूर्ण अन्यथा अगर (ns->geom.pgsz == 2048) अणु
		ns->options |= OPT_PAGE2048;
	पूर्ण अन्यथा अगर (ns->geom.pgsz == 4096) अणु
		ns->options |= OPT_PAGE4096;
	पूर्ण अन्यथा अणु
		NS_ERR("init_nandsim: unknown page size %u\n", ns->geom.pgsz);
		वापस -EIO;
	पूर्ण

	अगर (ns->options & OPT_SMALLPAGE) अणु
		अगर (ns->geom.totsz <= (32 << 20)) अणु
			ns->geom.pgaddrbytes  = 3;
			ns->geom.secaddrbytes = 2;
		पूर्ण अन्यथा अणु
			ns->geom.pgaddrbytes  = 4;
			ns->geom.secaddrbytes = 3;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ns->geom.totsz <= (128 << 20)) अणु
			ns->geom.pgaddrbytes  = 4;
			ns->geom.secaddrbytes = 2;
		पूर्ण अन्यथा अणु
			ns->geom.pgaddrbytes  = 5;
			ns->geom.secaddrbytes = 3;
		पूर्ण
	पूर्ण

	/* Fill the partition_info काष्ठाure */
	अगर (parts_num > ARRAY_SIZE(ns->partitions)) अणु
		NS_ERR("too many partitions.\n");
		वापस -EINVAL;
	पूर्ण
	reमुख्यs = ns->geom.totsz;
	next_offset = 0;
	क्रम (i = 0; i < parts_num; ++i) अणु
		uपूर्णांक64_t part_sz = (uपूर्णांक64_t)parts[i] * ns->geom.secsz;

		अगर (!part_sz || part_sz > reमुख्यs) अणु
			NS_ERR("bad partition size.\n");
			वापस -EINVAL;
		पूर्ण
		ns->partitions[i].name = ns_get_partition_name(i);
		अगर (!ns->partitions[i].name) अणु
			NS_ERR("unable to allocate memory.\n");
			वापस -ENOMEM;
		पूर्ण
		ns->partitions[i].offset = next_offset;
		ns->partitions[i].size   = part_sz;
		next_offset += ns->partitions[i].size;
		reमुख्यs -= ns->partitions[i].size;
	पूर्ण
	ns->nbparts = parts_num;
	अगर (reमुख्यs) अणु
		अगर (parts_num + 1 > ARRAY_SIZE(ns->partitions)) अणु
			NS_ERR("too many partitions.\n");
			ret = -EINVAL;
			जाओ मुक्त_partition_names;
		पूर्ण
		ns->partitions[i].name = ns_get_partition_name(i);
		अगर (!ns->partitions[i].name) अणु
			NS_ERR("unable to allocate memory.\n");
			ret = -ENOMEM;
			जाओ मुक्त_partition_names;
		पूर्ण
		ns->partitions[i].offset = next_offset;
		ns->partitions[i].size   = reमुख्यs;
		ns->nbparts += 1;
	पूर्ण

	अगर (ns->busw == 16)
		NS_WARN("16-bit flashes support wasn't tested\n");

	prपूर्णांकk("flash size: %llu MiB\n",
			(अचिन्हित दीर्घ दीर्घ)ns->geom.totsz >> 20);
	prपूर्णांकk("page size: %u bytes\n",         ns->geom.pgsz);
	prपूर्णांकk("OOB area size: %u bytes\n",     ns->geom.oobsz);
	prपूर्णांकk("sector size: %u KiB\n",         ns->geom.secsz >> 10);
	prपूर्णांकk("pages number: %u\n",            ns->geom.pgnum);
	prपूर्णांकk("pages per sector: %u\n",        ns->geom.pgsec);
	prपूर्णांकk("bus width: %u\n",               ns->busw);
	prपूर्णांकk("bits in sector size: %u\n",     ns->geom.secshअगरt);
	prपूर्णांकk("bits in page size: %u\n",       ns->geom.pgshअगरt);
	prपूर्णांकk("bits in OOB size: %u\n",	ffs(ns->geom.oobsz) - 1);
	prपूर्णांकk("flash size with OOB: %llu KiB\n",
			(अचिन्हित दीर्घ दीर्घ)ns->geom.totszoob >> 10);
	prपूर्णांकk("page address bytes: %u\n",      ns->geom.pgaddrbytes);
	prपूर्णांकk("sector address bytes: %u\n",    ns->geom.secaddrbytes);
	prपूर्णांकk("options: %#x\n",                ns->options);

	ret = ns_alloc_device(ns);
	अगर (ret)
		जाओ मुक्त_partition_names;

	/* Allocate / initialize the पूर्णांकernal buffer */
	ns->buf.byte = kदो_स्मृति(ns->geom.pgszoob, GFP_KERNEL);
	अगर (!ns->buf.byte) अणु
		NS_ERR("init_nandsim: unable to allocate %u bytes for the internal buffer\n",
			ns->geom.pgszoob);
		ret = -ENOMEM;
		जाओ मुक्त_device;
	पूर्ण
	स_रखो(ns->buf.byte, 0xFF, ns->geom.pgszoob);

	वापस 0;

मुक्त_device:
	ns_मुक्त_device(ns);
मुक्त_partition_names:
	क्रम (i = 0; i < ARRAY_SIZE(ns->partitions); ++i)
		kमुक्त(ns->partitions[i].name);

	वापस ret;
पूर्ण

/*
 * Free the nandsim काष्ठाure.
 */
अटल व्योम ns_मुक्त(काष्ठा nandsim *ns)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ns->partitions); ++i)
		kमुक्त(ns->partitions[i].name);

	kमुक्त(ns->buf.byte);
	ns_मुक्त_device(ns);

	वापस;
पूर्ण

अटल पूर्णांक ns_parse_badblocks(काष्ठा nandsim *ns, काष्ठा mtd_info *mtd)
अणु
	अक्षर *w;
	पूर्णांक zero_ok;
	अचिन्हित पूर्णांक erase_block_no;
	loff_t offset;

	अगर (!badblocks)
		वापस 0;
	w = badblocks;
	करो अणु
		zero_ok = (*w == '0' ? 1 : 0);
		erase_block_no = simple_म_से_अदीर्घ(w, &w, 0);
		अगर (!zero_ok && !erase_block_no) अणु
			NS_ERR("invalid badblocks.\n");
			वापस -EINVAL;
		पूर्ण
		offset = (loff_t)erase_block_no * ns->geom.secsz;
		अगर (mtd_block_markbad(mtd, offset)) अणु
			NS_ERR("invalid badblocks.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (*w == ',')
			w += 1;
	पूर्ण जबतक (*w);
	वापस 0;
पूर्ण

अटल पूर्णांक ns_parse_weakblocks(व्योम)
अणु
	अक्षर *w;
	पूर्णांक zero_ok;
	अचिन्हित पूर्णांक erase_block_no;
	अचिन्हित पूर्णांक max_erases;
	काष्ठा weak_block *wb;

	अगर (!weakblocks)
		वापस 0;
	w = weakblocks;
	करो अणु
		zero_ok = (*w == '0' ? 1 : 0);
		erase_block_no = simple_म_से_अदीर्घ(w, &w, 0);
		अगर (!zero_ok && !erase_block_no) अणु
			NS_ERR("invalid weakblocks.\n");
			वापस -EINVAL;
		पूर्ण
		max_erases = 3;
		अगर (*w == ':') अणु
			w += 1;
			max_erases = simple_म_से_अदीर्घ(w, &w, 0);
		पूर्ण
		अगर (*w == ',')
			w += 1;
		wb = kzalloc(माप(*wb), GFP_KERNEL);
		अगर (!wb) अणु
			NS_ERR("unable to allocate memory.\n");
			वापस -ENOMEM;
		पूर्ण
		wb->erase_block_no = erase_block_no;
		wb->max_erases = max_erases;
		list_add(&wb->list, &weak_blocks);
	पूर्ण जबतक (*w);
	वापस 0;
पूर्ण

अटल पूर्णांक ns_erase_error(अचिन्हित पूर्णांक erase_block_no)
अणु
	काष्ठा weak_block *wb;

	list_क्रम_each_entry(wb, &weak_blocks, list)
		अगर (wb->erase_block_no == erase_block_no) अणु
			अगर (wb->erases_करोne >= wb->max_erases)
				वापस 1;
			wb->erases_करोne += 1;
			वापस 0;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ns_parse_weakpages(व्योम)
अणु
	अक्षर *w;
	पूर्णांक zero_ok;
	अचिन्हित पूर्णांक page_no;
	अचिन्हित पूर्णांक max_ग_लिखोs;
	काष्ठा weak_page *wp;

	अगर (!weakpages)
		वापस 0;
	w = weakpages;
	करो अणु
		zero_ok = (*w == '0' ? 1 : 0);
		page_no = simple_म_से_अदीर्घ(w, &w, 0);
		अगर (!zero_ok && !page_no) अणु
			NS_ERR("invalid weakpages.\n");
			वापस -EINVAL;
		पूर्ण
		max_ग_लिखोs = 3;
		अगर (*w == ':') अणु
			w += 1;
			max_ग_लिखोs = simple_म_से_अदीर्घ(w, &w, 0);
		पूर्ण
		अगर (*w == ',')
			w += 1;
		wp = kzalloc(माप(*wp), GFP_KERNEL);
		अगर (!wp) अणु
			NS_ERR("unable to allocate memory.\n");
			वापस -ENOMEM;
		पूर्ण
		wp->page_no = page_no;
		wp->max_ग_लिखोs = max_ग_लिखोs;
		list_add(&wp->list, &weak_pages);
	पूर्ण जबतक (*w);
	वापस 0;
पूर्ण

अटल पूर्णांक ns_ग_लिखो_error(अचिन्हित पूर्णांक page_no)
अणु
	काष्ठा weak_page *wp;

	list_क्रम_each_entry(wp, &weak_pages, list)
		अगर (wp->page_no == page_no) अणु
			अगर (wp->ग_लिखोs_करोne >= wp->max_ग_लिखोs)
				वापस 1;
			wp->ग_लिखोs_करोne += 1;
			वापस 0;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ns_parse_gravepages(व्योम)
अणु
	अक्षर *g;
	पूर्णांक zero_ok;
	अचिन्हित पूर्णांक page_no;
	अचिन्हित पूर्णांक max_पढ़ोs;
	काष्ठा grave_page *gp;

	अगर (!gravepages)
		वापस 0;
	g = gravepages;
	करो अणु
		zero_ok = (*g == '0' ? 1 : 0);
		page_no = simple_म_से_अदीर्घ(g, &g, 0);
		अगर (!zero_ok && !page_no) अणु
			NS_ERR("invalid gravepagess.\n");
			वापस -EINVAL;
		पूर्ण
		max_पढ़ोs = 3;
		अगर (*g == ':') अणु
			g += 1;
			max_पढ़ोs = simple_म_से_अदीर्घ(g, &g, 0);
		पूर्ण
		अगर (*g == ',')
			g += 1;
		gp = kzalloc(माप(*gp), GFP_KERNEL);
		अगर (!gp) अणु
			NS_ERR("unable to allocate memory.\n");
			वापस -ENOMEM;
		पूर्ण
		gp->page_no = page_no;
		gp->max_पढ़ोs = max_पढ़ोs;
		list_add(&gp->list, &grave_pages);
	पूर्ण जबतक (*g);
	वापस 0;
पूर्ण

अटल पूर्णांक ns_पढ़ो_error(अचिन्हित पूर्णांक page_no)
अणु
	काष्ठा grave_page *gp;

	list_क्रम_each_entry(gp, &grave_pages, list)
		अगर (gp->page_no == page_no) अणु
			अगर (gp->पढ़ोs_करोne >= gp->max_पढ़ोs)
				वापस 1;
			gp->पढ़ोs_करोne += 1;
			वापस 0;
		पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ns_setup_wear_reporting(काष्ठा mtd_info *mtd)
अणु
	माप_प्रकार mem;

	wear_eb_count = भाग_u64(mtd->size, mtd->erasesize);
	mem = wear_eb_count * माप(अचिन्हित दीर्घ);
	अगर (mem / माप(अचिन्हित दीर्घ) != wear_eb_count) अणु
		NS_ERR("Too many erase blocks for wear reporting\n");
		वापस -ENOMEM;
	पूर्ण
	erase_block_wear = kzalloc(mem, GFP_KERNEL);
	अगर (!erase_block_wear) अणु
		NS_ERR("Too many erase blocks for wear reporting\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ns_update_wear(अचिन्हित पूर्णांक erase_block_no)
अणु
	अगर (!erase_block_wear)
		वापस;
	total_wear += 1;
	/*
	 * TODO: Notअगरy this through a debugfs entry,
	 * instead of showing an error message.
	 */
	अगर (total_wear == 0)
		NS_ERR("Erase counter total overflow\n");
	erase_block_wear[erase_block_no] += 1;
	अगर (erase_block_wear[erase_block_no] == 0)
		NS_ERR("Erase counter overflow for erase block %u\n", erase_block_no);
पूर्ण

/*
 * Returns the string representation of 'state' state.
 */
अटल अक्षर *ns_get_state_name(uपूर्णांक32_t state)
अणु
	चयन (NS_STATE(state)) अणु
		हाल STATE_CMD_READ0:
			वापस "STATE_CMD_READ0";
		हाल STATE_CMD_READ1:
			वापस "STATE_CMD_READ1";
		हाल STATE_CMD_PAGEPROG:
			वापस "STATE_CMD_PAGEPROG";
		हाल STATE_CMD_READOOB:
			वापस "STATE_CMD_READOOB";
		हाल STATE_CMD_READSTART:
			वापस "STATE_CMD_READSTART";
		हाल STATE_CMD_ERASE1:
			वापस "STATE_CMD_ERASE1";
		हाल STATE_CMD_STATUS:
			वापस "STATE_CMD_STATUS";
		हाल STATE_CMD_SEQIN:
			वापस "STATE_CMD_SEQIN";
		हाल STATE_CMD_READID:
			वापस "STATE_CMD_READID";
		हाल STATE_CMD_ERASE2:
			वापस "STATE_CMD_ERASE2";
		हाल STATE_CMD_RESET:
			वापस "STATE_CMD_RESET";
		हाल STATE_CMD_RNDOUT:
			वापस "STATE_CMD_RNDOUT";
		हाल STATE_CMD_RNDOUTSTART:
			वापस "STATE_CMD_RNDOUTSTART";
		हाल STATE_ADDR_PAGE:
			वापस "STATE_ADDR_PAGE";
		हाल STATE_ADDR_SEC:
			वापस "STATE_ADDR_SEC";
		हाल STATE_ADDR_ZERO:
			वापस "STATE_ADDR_ZERO";
		हाल STATE_ADDR_COLUMN:
			वापस "STATE_ADDR_COLUMN";
		हाल STATE_DATAIN:
			वापस "STATE_DATAIN";
		हाल STATE_DATAOUT:
			वापस "STATE_DATAOUT";
		हाल STATE_DATAOUT_ID:
			वापस "STATE_DATAOUT_ID";
		हाल STATE_DATAOUT_STATUS:
			वापस "STATE_DATAOUT_STATUS";
		हाल STATE_READY:
			वापस "STATE_READY";
		हाल STATE_UNKNOWN:
			वापस "STATE_UNKNOWN";
	पूर्ण

	NS_ERR("get_state_name: unknown state, BUG\n");
	वापस शून्य;
पूर्ण

/*
 * Check अगर command is valid.
 *
 * RETURNS: 1 अगर wrong command, 0 अगर right.
 */
अटल पूर्णांक ns_check_command(पूर्णांक cmd)
अणु
	चयन (cmd) अणु

	हाल न_अंकD_CMD_READ0:
	हाल न_अंकD_CMD_READ1:
	हाल न_अंकD_CMD_READSTART:
	हाल न_अंकD_CMD_PAGEPROG:
	हाल न_अंकD_CMD_READOOB:
	हाल न_अंकD_CMD_ERASE1:
	हाल न_अंकD_CMD_STATUS:
	हाल न_अंकD_CMD_SEQIN:
	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_ERASE2:
	हाल न_अंकD_CMD_RESET:
	हाल न_अंकD_CMD_RNDOUT:
	हाल न_अंकD_CMD_RNDOUTSTART:
		वापस 0;

	शेष:
		वापस 1;
	पूर्ण
पूर्ण

/*
 * Returns state after command is accepted by command number.
 */
अटल uपूर्णांक32_t ns_get_state_by_command(अचिन्हित command)
अणु
	चयन (command) अणु
		हाल न_अंकD_CMD_READ0:
			वापस STATE_CMD_READ0;
		हाल न_अंकD_CMD_READ1:
			वापस STATE_CMD_READ1;
		हाल न_अंकD_CMD_PAGEPROG:
			वापस STATE_CMD_PAGEPROG;
		हाल न_अंकD_CMD_READSTART:
			वापस STATE_CMD_READSTART;
		हाल न_अंकD_CMD_READOOB:
			वापस STATE_CMD_READOOB;
		हाल न_अंकD_CMD_ERASE1:
			वापस STATE_CMD_ERASE1;
		हाल न_अंकD_CMD_STATUS:
			वापस STATE_CMD_STATUS;
		हाल न_अंकD_CMD_SEQIN:
			वापस STATE_CMD_SEQIN;
		हाल न_अंकD_CMD_READID:
			वापस STATE_CMD_READID;
		हाल न_अंकD_CMD_ERASE2:
			वापस STATE_CMD_ERASE2;
		हाल न_अंकD_CMD_RESET:
			वापस STATE_CMD_RESET;
		हाल न_अंकD_CMD_RNDOUT:
			वापस STATE_CMD_RNDOUT;
		हाल न_अंकD_CMD_RNDOUTSTART:
			वापस STATE_CMD_RNDOUTSTART;
	पूर्ण

	NS_ERR("get_state_by_command: unknown command, BUG\n");
	वापस 0;
पूर्ण

/*
 * Move an address byte to the correspondent पूर्णांकernal रेजिस्टर.
 */
अटल अंतरभूत व्योम ns_accept_addr_byte(काष्ठा nandsim *ns, u_अक्षर bt)
अणु
	uपूर्णांक byte = (uपूर्णांक)bt;

	अगर (ns->regs.count < (ns->geom.pgaddrbytes - ns->geom.secaddrbytes))
		ns->regs.column |= (byte << 8 * ns->regs.count);
	अन्यथा अणु
		ns->regs.row |= (byte << 8 * (ns->regs.count -
						ns->geom.pgaddrbytes +
						ns->geom.secaddrbytes));
	पूर्ण

	वापस;
पूर्ण

/*
 * Switch to STATE_READY state.
 */
अटल अंतरभूत व्योम ns_चयन_to_पढ़ोy_state(काष्ठा nandsim *ns, u_अक्षर status)
अणु
	NS_DBG("switch_to_ready_state: switch to %s state\n",
	       ns_get_state_name(STATE_READY));

	ns->state       = STATE_READY;
	ns->nxstate     = STATE_UNKNOWN;
	ns->op          = शून्य;
	ns->npstates    = 0;
	ns->stateidx    = 0;
	ns->regs.num    = 0;
	ns->regs.count  = 0;
	ns->regs.off    = 0;
	ns->regs.row    = 0;
	ns->regs.column = 0;
	ns->regs.status = status;
पूर्ण

/*
 * If the operation isn't known yet, try to find it in the global array
 * of supported operations.
 *
 * Operation can be unknown because of the following.
 *   1. New command was accepted and this is the first call to find the
 *      correspondent states chain. In this हाल ns->npstates = 0;
 *   2. There are several operations which begin with the same command(s)
 *      (क्रम example program from the second half and पढ़ो from the
 *      second half operations both begin with the READ1 command). In this
 *      हाल the ns->pstates[] array contains previous states.
 *
 * Thus, the function tries to find operation containing the following
 * states (अगर the 'flag' parameter is 0):
 *    ns->pstates[0], ... ns->pstates[ns->npstates], ns->state
 *
 * If (one and only one) matching operation is found, it is accepted (
 * ns->ops, ns->state, ns->nxstate are initialized, ns->npstate is
 * zeroed).
 *
 * If there are several matches, the current state is pushed to the
 * ns->pstates.
 *
 * The operation can be unknown only जबतक commands are input to the chip.
 * As soon as address command is accepted, the operation must be known.
 * In such situation the function is called with 'flag' != 0, and the
 * operation is searched using the following pattern:
 *     ns->pstates[0], ... ns->pstates[ns->npstates], <address input>
 *
 * It is supposed that this pattern must either match one operation or
 * none. There can't be ambiguity in that हाल.
 *
 * If no matches found, the function करोes the following:
 *   1. अगर there are saved states present, try to ignore them and search
 *      again only using the last command. If nothing was found, चयन
 *      to the STATE_READY state.
 *   2. अगर there are no saved states, चयन to the STATE_READY state.
 *
 * RETURNS: -2 - no matched operations found.
 *          -1 - several matches.
 *           0 - operation is found.
 */
अटल पूर्णांक ns_find_operation(काष्ठा nandsim *ns, uपूर्णांक32_t flag)
अणु
	पूर्णांक opsfound = 0;
	पूर्णांक i, j, idx = 0;

	क्रम (i = 0; i < NS_OPER_NUM; i++) अणु

		पूर्णांक found = 1;

		अगर (!(ns->options & ops[i].reqopts))
			/* Ignore operations we can't perक्रमm */
			जारी;

		अगर (flag) अणु
			अगर (!(ops[i].states[ns->npstates] & STATE_ADDR_MASK))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (NS_STATE(ns->state) != NS_STATE(ops[i].states[ns->npstates]))
				जारी;
		पूर्ण

		क्रम (j = 0; j < ns->npstates; j++)
			अगर (NS_STATE(ops[i].states[j]) != NS_STATE(ns->pstates[j])
				&& (ns->options & ops[idx].reqopts)) अणु
				found = 0;
				अवरोध;
			पूर्ण

		अगर (found) अणु
			idx = i;
			opsfound += 1;
		पूर्ण
	पूर्ण

	अगर (opsfound == 1) अणु
		/* Exact match */
		ns->op = &ops[idx].states[0];
		अगर (flag) अणु
			/*
			 * In this हाल the find_operation function was
			 * called when address has just began input. But it isn't
			 * yet fully input and the current state must
			 * not be one of STATE_ADDR_*, but the STATE_ADDR_*
			 * state must be the next state (ns->nxstate).
			 */
			ns->stateidx = ns->npstates - 1;
		पूर्ण अन्यथा अणु
			ns->stateidx = ns->npstates;
		पूर्ण
		ns->npstates = 0;
		ns->state = ns->op[ns->stateidx];
		ns->nxstate = ns->op[ns->stateidx + 1];
		NS_DBG("find_operation: operation found, index: %d, state: %s, nxstate %s\n",
		       idx, ns_get_state_name(ns->state),
		       ns_get_state_name(ns->nxstate));
		वापस 0;
	पूर्ण

	अगर (opsfound == 0) अणु
		/* Nothing was found. Try to ignore previous commands (अगर any) and search again */
		अगर (ns->npstates != 0) अणु
			NS_DBG("find_operation: no operation found, try again with state %s\n",
			       ns_get_state_name(ns->state));
			ns->npstates = 0;
			वापस ns_find_operation(ns, 0);

		पूर्ण
		NS_DBG("find_operation: no operations found\n");
		ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
		वापस -2;
	पूर्ण

	अगर (flag) अणु
		/* This shouldn't happen */
		NS_DBG("find_operation: BUG, operation must be known if address is input\n");
		वापस -2;
	पूर्ण

	NS_DBG("find_operation: there is still ambiguity\n");

	ns->pstates[ns->npstates++] = ns->state;

	वापस -1;
पूर्ण

अटल व्योम ns_put_pages(काष्ठा nandsim *ns)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ns->held_cnt; i++)
		put_page(ns->held_pages[i]);
पूर्ण

/* Get page cache pages in advance to provide NOFS memory allocation */
अटल पूर्णांक ns_get_pages(काष्ठा nandsim *ns, काष्ठा file *file, माप_प्रकार count,
			loff_t pos)
अणु
	pgoff_t index, start_index, end_index;
	काष्ठा page *page;
	काष्ठा address_space *mapping = file->f_mapping;

	start_index = pos >> PAGE_SHIFT;
	end_index = (pos + count - 1) >> PAGE_SHIFT;
	अगर (end_index - start_index + 1 > NS_MAX_HELD_PAGES)
		वापस -EINVAL;
	ns->held_cnt = 0;
	क्रम (index = start_index; index <= end_index; index++) अणु
		page = find_get_page(mapping, index);
		अगर (page == शून्य) अणु
			page = find_or_create_page(mapping, index, GFP_NOFS);
			अगर (page == शून्य) अणु
				ग_लिखो_inode_now(mapping->host, 1);
				page = find_or_create_page(mapping, index, GFP_NOFS);
			पूर्ण
			अगर (page == शून्य) अणु
				ns_put_pages(ns);
				वापस -ENOMEM;
			पूर्ण
			unlock_page(page);
		पूर्ण
		ns->held_pages[ns->held_cnt++] = page;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार ns_पढ़ो_file(काष्ठा nandsim *ns, काष्ठा file *file, व्योम *buf,
			    माप_प्रकार count, loff_t pos)
अणु
	sमाप_प्रकार tx;
	पूर्णांक err;
	अचिन्हित पूर्णांक noreclaim_flag;

	err = ns_get_pages(ns, file, count, pos);
	अगर (err)
		वापस err;
	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	tx = kernel_पढ़ो(file, buf, count, &pos);
	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	ns_put_pages(ns);
	वापस tx;
पूर्ण

अटल sमाप_प्रकार ns_ग_लिखो_file(काष्ठा nandsim *ns, काष्ठा file *file, व्योम *buf,
			     माप_प्रकार count, loff_t pos)
अणु
	sमाप_प्रकार tx;
	पूर्णांक err;
	अचिन्हित पूर्णांक noreclaim_flag;

	err = ns_get_pages(ns, file, count, pos);
	अगर (err)
		वापस err;
	noreclaim_flag = meदो_स्मृति_noreclaim_save();
	tx = kernel_ग_लिखो(file, buf, count, &pos);
	meदो_स्मृति_noreclaim_restore(noreclaim_flag);
	ns_put_pages(ns);
	वापस tx;
पूर्ण

/*
 * Returns a poपूर्णांकer to the current page.
 */
अटल अंतरभूत जोड़ ns_mem *NS_GET_PAGE(काष्ठा nandsim *ns)
अणु
	वापस &(ns->pages[ns->regs.row]);
पूर्ण

/*
 * Retuns a poपूर्णांकer to the current byte, within the current page.
 */
अटल अंतरभूत u_अक्षर *NS_PAGE_BYTE_OFF(काष्ठा nandsim *ns)
अणु
	वापस NS_GET_PAGE(ns)->byte + ns->regs.column + ns->regs.off;
पूर्ण

अटल पूर्णांक ns_करो_पढ़ो_error(काष्ठा nandsim *ns, पूर्णांक num)
अणु
	अचिन्हित पूर्णांक page_no = ns->regs.row;

	अगर (ns_पढ़ो_error(page_no)) अणु
		pअक्रमom_bytes(ns->buf.byte, num);
		NS_WARN("simulating read error in page %u\n", page_no);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ns_करो_bit_flips(काष्ठा nandsim *ns, पूर्णांक num)
अणु
	अगर (bitflips && pअक्रमom_u32() < (1 << 22)) अणु
		पूर्णांक flips = 1;
		अगर (bitflips > 1)
			flips = (pअक्रमom_u32() % (पूर्णांक) bitflips) + 1;
		जबतक (flips--) अणु
			पूर्णांक pos = pअक्रमom_u32() % (num * 8);
			ns->buf.byte[pos / 8] ^= (1 << (pos % 8));
			NS_WARN("read_page: flipping bit %d in page %d "
				"reading from %d ecc: corrected=%u failed=%u\n",
				pos, ns->regs.row, ns->regs.column + ns->regs.off,
				nsmtd->ecc_stats.corrected, nsmtd->ecc_stats.failed);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Fill the न_अंकD buffer with data पढ़ो from the specअगरied page.
 */
अटल व्योम ns_पढ़ो_page(काष्ठा nandsim *ns, पूर्णांक num)
अणु
	जोड़ ns_mem *mypage;

	अगर (ns->cfile) अणु
		अगर (!test_bit(ns->regs.row, ns->pages_written)) अणु
			NS_DBG("read_page: page %d not written\n", ns->regs.row);
			स_रखो(ns->buf.byte, 0xFF, num);
		पूर्ण अन्यथा अणु
			loff_t pos;
			sमाप_प्रकार tx;

			NS_DBG("read_page: page %d written, reading from %d\n",
				ns->regs.row, ns->regs.column + ns->regs.off);
			अगर (ns_करो_पढ़ो_error(ns, num))
				वापस;
			pos = (loff_t)NS_RAW_OFFSET(ns) + ns->regs.off;
			tx = ns_पढ़ो_file(ns, ns->cfile, ns->buf.byte, num,
					  pos);
			अगर (tx != num) अणु
				NS_ERR("read_page: read error for page %d ret %ld\n", ns->regs.row, (दीर्घ)tx);
				वापस;
			पूर्ण
			ns_करो_bit_flips(ns, num);
		पूर्ण
		वापस;
	पूर्ण

	mypage = NS_GET_PAGE(ns);
	अगर (mypage->byte == शून्य) अणु
		NS_DBG("read_page: page %d not allocated\n", ns->regs.row);
		स_रखो(ns->buf.byte, 0xFF, num);
	पूर्ण अन्यथा अणु
		NS_DBG("read_page: page %d allocated, reading from %d\n",
			ns->regs.row, ns->regs.column + ns->regs.off);
		अगर (ns_करो_पढ़ो_error(ns, num))
			वापस;
		स_नकल(ns->buf.byte, NS_PAGE_BYTE_OFF(ns), num);
		ns_करो_bit_flips(ns, num);
	पूर्ण
पूर्ण

/*
 * Erase all pages in the specअगरied sector.
 */
अटल व्योम ns_erase_sector(काष्ठा nandsim *ns)
अणु
	जोड़ ns_mem *mypage;
	पूर्णांक i;

	अगर (ns->cfile) अणु
		क्रम (i = 0; i < ns->geom.pgsec; i++)
			अगर (__test_and_clear_bit(ns->regs.row + i,
						 ns->pages_written)) अणु
				NS_DBG("erase_sector: freeing page %d\n", ns->regs.row + i);
			पूर्ण
		वापस;
	पूर्ण

	mypage = NS_GET_PAGE(ns);
	क्रम (i = 0; i < ns->geom.pgsec; i++) अणु
		अगर (mypage->byte != शून्य) अणु
			NS_DBG("erase_sector: freeing page %d\n", ns->regs.row+i);
			kmem_cache_मुक्त(ns->nand_pages_slab, mypage->byte);
			mypage->byte = शून्य;
		पूर्ण
		mypage++;
	पूर्ण
पूर्ण

/*
 * Program the specअगरied page with the contents from the न_अंकD buffer.
 */
अटल पूर्णांक ns_prog_page(काष्ठा nandsim *ns, पूर्णांक num)
अणु
	पूर्णांक i;
	जोड़ ns_mem *mypage;
	u_अक्षर *pg_off;

	अगर (ns->cfile) अणु
		loff_t off;
		sमाप_प्रकार tx;
		पूर्णांक all;

		NS_DBG("prog_page: writing page %d\n", ns->regs.row);
		pg_off = ns->file_buf + ns->regs.column + ns->regs.off;
		off = (loff_t)NS_RAW_OFFSET(ns) + ns->regs.off;
		अगर (!test_bit(ns->regs.row, ns->pages_written)) अणु
			all = 1;
			स_रखो(ns->file_buf, 0xff, ns->geom.pgszoob);
		पूर्ण अन्यथा अणु
			all = 0;
			tx = ns_पढ़ो_file(ns, ns->cfile, pg_off, num, off);
			अगर (tx != num) अणु
				NS_ERR("prog_page: read error for page %d ret %ld\n", ns->regs.row, (दीर्घ)tx);
				वापस -1;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < num; i++)
			pg_off[i] &= ns->buf.byte[i];
		अगर (all) अणु
			loff_t pos = (loff_t)ns->regs.row * ns->geom.pgszoob;
			tx = ns_ग_लिखो_file(ns, ns->cfile, ns->file_buf,
					   ns->geom.pgszoob, pos);
			अगर (tx != ns->geom.pgszoob) अणु
				NS_ERR("prog_page: write error for page %d ret %ld\n", ns->regs.row, (दीर्घ)tx);
				वापस -1;
			पूर्ण
			__set_bit(ns->regs.row, ns->pages_written);
		पूर्ण अन्यथा अणु
			tx = ns_ग_लिखो_file(ns, ns->cfile, pg_off, num, off);
			अगर (tx != num) अणु
				NS_ERR("prog_page: write error for page %d ret %ld\n", ns->regs.row, (दीर्घ)tx);
				वापस -1;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	mypage = NS_GET_PAGE(ns);
	अगर (mypage->byte == शून्य) अणु
		NS_DBG("prog_page: allocating page %d\n", ns->regs.row);
		/*
		 * We allocate memory with GFP_NOFS because a flash FS may
		 * utilize this. If it is holding an FS lock, then माला_लो here,
		 * then kernel memory alloc runs ग_लिखोback which goes to the FS
		 * again and deadlocks. This was seen in practice.
		 */
		mypage->byte = kmem_cache_alloc(ns->nand_pages_slab, GFP_NOFS);
		अगर (mypage->byte == शून्य) अणु
			NS_ERR("prog_page: error allocating memory for page %d\n", ns->regs.row);
			वापस -1;
		पूर्ण
		स_रखो(mypage->byte, 0xFF, ns->geom.pgszoob);
	पूर्ण

	pg_off = NS_PAGE_BYTE_OFF(ns);
	क्रम (i = 0; i < num; i++)
		pg_off[i] &= ns->buf.byte[i];

	वापस 0;
पूर्ण

/*
 * If state has any action bit, perक्रमm this action.
 *
 * RETURNS: 0 अगर success, -1 अगर error.
 */
अटल पूर्णांक ns_करो_state_action(काष्ठा nandsim *ns, uपूर्णांक32_t action)
अणु
	पूर्णांक num;
	पूर्णांक busभाग = ns->busw == 8 ? 1 : 2;
	अचिन्हित पूर्णांक erase_block_no, page_no;

	action &= ACTION_MASK;

	/* Check that page address input is correct */
	अगर (action != ACTION_SECERASE && ns->regs.row >= ns->geom.pgnum) अणु
		NS_WARN("do_state_action: wrong page number (%#x)\n", ns->regs.row);
		वापस -1;
	पूर्ण

	चयन (action) अणु

	हाल ACTION_CPY:
		/*
		 * Copy page data to the पूर्णांकernal buffer.
		 */

		/* Column shouldn't be very large */
		अगर (ns->regs.column >= (ns->geom.pgszoob - ns->regs.off)) अणु
			NS_ERR("do_state_action: column number is too large\n");
			अवरोध;
		पूर्ण
		num = ns->geom.pgszoob - ns->regs.off - ns->regs.column;
		ns_पढ़ो_page(ns, num);

		NS_DBG("do_state_action: (ACTION_CPY:) copy %d bytes to int buf, raw offset %d\n",
			num, NS_RAW_OFFSET(ns) + ns->regs.off);

		अगर (ns->regs.off == 0)
			NS_LOG("read page %d\n", ns->regs.row);
		अन्यथा अगर (ns->regs.off < ns->geom.pgsz)
			NS_LOG("read page %d (second half)\n", ns->regs.row);
		अन्यथा
			NS_LOG("read OOB of page %d\n", ns->regs.row);

		NS_UDELAY(access_delay);
		NS_UDELAY(input_cycle * ns->geom.pgsz / 1000 / busभाग);

		अवरोध;

	हाल ACTION_SECERASE:
		/*
		 * Erase sector.
		 */

		अगर (ns->lines.wp) अणु
			NS_ERR("do_state_action: device is write-protected, ignore sector erase\n");
			वापस -1;
		पूर्ण

		अगर (ns->regs.row >= ns->geom.pgnum - ns->geom.pgsec
			|| (ns->regs.row & ~(ns->geom.secsz - 1))) अणु
			NS_ERR("do_state_action: wrong sector address (%#x)\n", ns->regs.row);
			वापस -1;
		पूर्ण

		ns->regs.row = (ns->regs.row <<
				8 * (ns->geom.pgaddrbytes - ns->geom.secaddrbytes)) | ns->regs.column;
		ns->regs.column = 0;

		erase_block_no = ns->regs.row >> (ns->geom.secshअगरt - ns->geom.pgshअगरt);

		NS_DBG("do_state_action: erase sector at address %#x, off = %d\n",
				ns->regs.row, NS_RAW_OFFSET(ns));
		NS_LOG("erase sector %u\n", erase_block_no);

		ns_erase_sector(ns);

		NS_MDELAY(erase_delay);

		अगर (erase_block_wear)
			ns_update_wear(erase_block_no);

		अगर (ns_erase_error(erase_block_no)) अणु
			NS_WARN("simulating erase failure in erase block %u\n", erase_block_no);
			वापस -1;
		पूर्ण

		अवरोध;

	हाल ACTION_PRGPAGE:
		/*
		 * Program page - move पूर्णांकernal buffer data to the page.
		 */

		अगर (ns->lines.wp) अणु
			NS_WARN("do_state_action: device is write-protected, programm\n");
			वापस -1;
		पूर्ण

		num = ns->geom.pgszoob - ns->regs.off - ns->regs.column;
		अगर (num != ns->regs.count) अणु
			NS_ERR("do_state_action: too few bytes were input (%d instead of %d)\n",
					ns->regs.count, num);
			वापस -1;
		पूर्ण

		अगर (ns_prog_page(ns, num) == -1)
			वापस -1;

		page_no = ns->regs.row;

		NS_DBG("do_state_action: copy %d bytes from int buf to (%#x, %#x), raw off = %d\n",
			num, ns->regs.row, ns->regs.column, NS_RAW_OFFSET(ns) + ns->regs.off);
		NS_LOG("programm page %d\n", ns->regs.row);

		NS_UDELAY(programm_delay);
		NS_UDELAY(output_cycle * ns->geom.pgsz / 1000 / busभाग);

		अगर (ns_ग_लिखो_error(page_no)) अणु
			NS_WARN("simulating write failure in page %u\n", page_no);
			वापस -1;
		पूर्ण

		अवरोध;

	हाल ACTION_ZEROOFF:
		NS_DBG("do_state_action: set internal offset to 0\n");
		ns->regs.off = 0;
		अवरोध;

	हाल ACTION_HALFOFF:
		अगर (!(ns->options & OPT_PAGE512_8BIT)) अणु
			NS_ERR("do_state_action: BUG! can't skip half of page for non-512"
				"byte page size 8x chips\n");
			वापस -1;
		पूर्ण
		NS_DBG("do_state_action: set internal offset to %d\n", ns->geom.pgsz/2);
		ns->regs.off = ns->geom.pgsz/2;
		अवरोध;

	हाल ACTION_OOBOFF:
		NS_DBG("do_state_action: set internal offset to %d\n", ns->geom.pgsz);
		ns->regs.off = ns->geom.pgsz;
		अवरोध;

	शेष:
		NS_DBG("do_state_action: BUG! unknown action\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Switch simulator's state.
 */
अटल व्योम ns_चयन_state(काष्ठा nandsim *ns)
अणु
	अगर (ns->op) अणु
		/*
		 * The current operation have alपढ़ोy been identअगरied.
		 * Just follow the states chain.
		 */

		ns->stateidx += 1;
		ns->state = ns->nxstate;
		ns->nxstate = ns->op[ns->stateidx + 1];

		NS_DBG("switch_state: operation is known, switch to the next state, "
			"state: %s, nxstate: %s\n",
		       ns_get_state_name(ns->state),
		       ns_get_state_name(ns->nxstate));

		/* See, whether we need to करो some action */
		अगर ((ns->state & ACTION_MASK) &&
		    ns_करो_state_action(ns, ns->state) < 0) अणु
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
			वापस;
		पूर्ण

	पूर्ण अन्यथा अणु
		/*
		 * We करोn't yet know which operation we perक्रमm.
		 * Try to identअगरy it.
		 */

		/*
		 *  The only event causing the चयन_state function to
		 *  be called with yet unknown operation is new command.
		 */
		ns->state = ns_get_state_by_command(ns->regs.command);

		NS_DBG("switch_state: operation is unknown, try to find it\n");

		अगर (ns_find_operation(ns, 0))
			वापस;

		अगर ((ns->state & ACTION_MASK) &&
		    ns_करो_state_action(ns, ns->state) < 0) अणु
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
			वापस;
		पूर्ण
	पूर्ण

	/* For 16x devices column means the page offset in words */
	अगर ((ns->nxstate & STATE_ADDR_MASK) && ns->busw == 16) अणु
		NS_DBG("switch_state: double the column number for 16x device\n");
		ns->regs.column <<= 1;
	पूर्ण

	अगर (NS_STATE(ns->nxstate) == STATE_READY) अणु
		/*
		 * The current state is the last. Return to STATE_READY
		 */

		u_अक्षर status = NS_STATUS_OK(ns);

		/* In हाल of data states, see अगर all bytes were input/output */
		अगर ((ns->state & (STATE_DATAIN_MASK | STATE_DATAOUT_MASK))
			&& ns->regs.count != ns->regs.num) अणु
			NS_WARN("switch_state: not all bytes were processed, %d left\n",
					ns->regs.num - ns->regs.count);
			status = NS_STATUS_FAILED(ns);
		पूर्ण

		NS_DBG("switch_state: operation complete, switch to STATE_READY state\n");

		ns_चयन_to_पढ़ोy_state(ns, status);

		वापस;
	पूर्ण अन्यथा अगर (ns->nxstate & (STATE_DATAIN_MASK | STATE_DATAOUT_MASK)) अणु
		/*
		 * If the next state is data input/output, चयन to it now
		 */

		ns->state      = ns->nxstate;
		ns->nxstate    = ns->op[++ns->stateidx + 1];
		ns->regs.num   = ns->regs.count = 0;

		NS_DBG("switch_state: the next state is data I/O, switch, "
			"state: %s, nxstate: %s\n",
		       ns_get_state_name(ns->state),
		       ns_get_state_name(ns->nxstate));

		/*
		 * Set the पूर्णांकernal रेजिस्टर to the count of bytes which
		 * are expected to be input or output
		 */
		चयन (NS_STATE(ns->state)) अणु
			हाल STATE_DATAIN:
			हाल STATE_DATAOUT:
				ns->regs.num = ns->geom.pgszoob - ns->regs.off - ns->regs.column;
				अवरोध;

			हाल STATE_DATAOUT_ID:
				ns->regs.num = ns->geom.idbytes;
				अवरोध;

			हाल STATE_DATAOUT_STATUS:
				ns->regs.count = ns->regs.num = 0;
				अवरोध;

			शेष:
				NS_ERR("switch_state: BUG! unknown data state\n");
		पूर्ण

	पूर्ण अन्यथा अगर (ns->nxstate & STATE_ADDR_MASK) अणु
		/*
		 * If the next state is address input, set the पूर्णांकernal
		 * रेजिस्टर to the number of expected address bytes
		 */

		ns->regs.count = 0;

		चयन (NS_STATE(ns->nxstate)) अणु
			हाल STATE_ADDR_PAGE:
				ns->regs.num = ns->geom.pgaddrbytes;

				अवरोध;
			हाल STATE_ADDR_SEC:
				ns->regs.num = ns->geom.secaddrbytes;
				अवरोध;

			हाल STATE_ADDR_ZERO:
				ns->regs.num = 1;
				अवरोध;

			हाल STATE_ADDR_COLUMN:
				/* Column address is always 2 bytes */
				ns->regs.num = ns->geom.pgaddrbytes - ns->geom.secaddrbytes;
				अवरोध;

			शेष:
				NS_ERR("switch_state: BUG! unknown address state\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Just reset पूर्णांकernal counters.
		 */

		ns->regs.num = 0;
		ns->regs.count = 0;
	पूर्ण
पूर्ण

अटल u_अक्षर ns_nand_पढ़ो_byte(काष्ठा nand_chip *chip)
अणु
	काष्ठा nandsim *ns = nand_get_controller_data(chip);
	u_अक्षर outb = 0x00;

	/* Sanity and correctness checks */
	अगर (!ns->lines.ce) अणु
		NS_ERR("read_byte: chip is disabled, return %#x\n", (uपूर्णांक)outb);
		वापस outb;
	पूर्ण
	अगर (ns->lines.ale || ns->lines.cle) अणु
		NS_ERR("read_byte: ALE or CLE pin is high, return %#x\n", (uपूर्णांक)outb);
		वापस outb;
	पूर्ण
	अगर (!(ns->state & STATE_DATAOUT_MASK)) अणु
		NS_WARN("read_byte: unexpected data output cycle, state is %s return %#x\n",
			ns_get_state_name(ns->state), (uपूर्णांक)outb);
		वापस outb;
	पूर्ण

	/* Status रेजिस्टर may be पढ़ो as many बार as it is wanted */
	अगर (NS_STATE(ns->state) == STATE_DATAOUT_STATUS) अणु
		NS_DBG("read_byte: return %#x status\n", ns->regs.status);
		वापस ns->regs.status;
	पूर्ण

	/* Check अगर there is any data in the पूर्णांकernal buffer which may be पढ़ो */
	अगर (ns->regs.count == ns->regs.num) अणु
		NS_WARN("read_byte: no more data to output, return %#x\n", (uपूर्णांक)outb);
		वापस outb;
	पूर्ण

	चयन (NS_STATE(ns->state)) अणु
		हाल STATE_DATAOUT:
			अगर (ns->busw == 8) अणु
				outb = ns->buf.byte[ns->regs.count];
				ns->regs.count += 1;
			पूर्ण अन्यथा अणु
				outb = (u_अक्षर)cpu_to_le16(ns->buf.word[ns->regs.count >> 1]);
				ns->regs.count += 2;
			पूर्ण
			अवरोध;
		हाल STATE_DATAOUT_ID:
			NS_DBG("read_byte: read ID byte %d, total = %d\n", ns->regs.count, ns->regs.num);
			outb = ns->ids[ns->regs.count];
			ns->regs.count += 1;
			अवरोध;
		शेष:
			BUG();
	पूर्ण

	अगर (ns->regs.count == ns->regs.num) अणु
		NS_DBG("read_byte: all bytes were read\n");

		अगर (NS_STATE(ns->nxstate) == STATE_READY)
			ns_चयन_state(ns);
	पूर्ण

	वापस outb;
पूर्ण

अटल व्योम ns_nand_ग_लिखो_byte(काष्ठा nand_chip *chip, u_अक्षर byte)
अणु
	काष्ठा nandsim *ns = nand_get_controller_data(chip);

	/* Sanity and correctness checks */
	अगर (!ns->lines.ce) अणु
		NS_ERR("write_byte: chip is disabled, ignore write\n");
		वापस;
	पूर्ण
	अगर (ns->lines.ale && ns->lines.cle) अणु
		NS_ERR("write_byte: ALE and CLE pins are high simultaneously, ignore write\n");
		वापस;
	पूर्ण

	अगर (ns->lines.cle == 1) अणु
		/*
		 * The byte written is a command.
		 */

		अगर (byte == न_अंकD_CMD_RESET) अणु
			NS_LOG("reset chip\n");
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_OK(ns));
			वापस;
		पूर्ण

		/* Check that the command byte is correct */
		अगर (ns_check_command(byte)) अणु
			NS_ERR("write_byte: unknown command %#x\n", (uपूर्णांक)byte);
			वापस;
		पूर्ण

		अगर (NS_STATE(ns->state) == STATE_DATAOUT_STATUS
			|| NS_STATE(ns->state) == STATE_DATAOUT) अणु
			पूर्णांक row = ns->regs.row;

			ns_चयन_state(ns);
			अगर (byte == न_अंकD_CMD_RNDOUT)
				ns->regs.row = row;
		पूर्ण

		/* Check अगर chip is expecting command */
		अगर (NS_STATE(ns->nxstate) != STATE_UNKNOWN && !(ns->nxstate & STATE_CMD_MASK)) अणु
			/* Do not warn अगर only 2 id bytes are पढ़ो */
			अगर (!(ns->regs.command == न_अंकD_CMD_READID &&
			    NS_STATE(ns->state) == STATE_DATAOUT_ID && ns->regs.count == 2)) अणु
				/*
				 * We are in situation when something अन्यथा (not command)
				 * was expected but command was input. In this हाल ignore
				 * previous command(s)/state(s) and accept the last one.
				 */
				NS_WARN("write_byte: command (%#x) wasn't expected, expected state is %s, ignore previous states\n",
					(uपूर्णांक)byte,
					ns_get_state_name(ns->nxstate));
			पूर्ण
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
		पूर्ण

		NS_DBG("command byte corresponding to %s state accepted\n",
			ns_get_state_name(ns_get_state_by_command(byte)));
		ns->regs.command = byte;
		ns_चयन_state(ns);

	पूर्ण अन्यथा अगर (ns->lines.ale == 1) अणु
		/*
		 * The byte written is an address.
		 */

		अगर (NS_STATE(ns->nxstate) == STATE_UNKNOWN) अणु

			NS_DBG("write_byte: operation isn't known yet, identify it\n");

			अगर (ns_find_operation(ns, 1) < 0)
				वापस;

			अगर ((ns->state & ACTION_MASK) &&
			    ns_करो_state_action(ns, ns->state) < 0) अणु
				ns_चयन_to_पढ़ोy_state(ns,
							 NS_STATUS_FAILED(ns));
				वापस;
			पूर्ण

			ns->regs.count = 0;
			चयन (NS_STATE(ns->nxstate)) अणु
				हाल STATE_ADDR_PAGE:
					ns->regs.num = ns->geom.pgaddrbytes;
					अवरोध;
				हाल STATE_ADDR_SEC:
					ns->regs.num = ns->geom.secaddrbytes;
					अवरोध;
				हाल STATE_ADDR_ZERO:
					ns->regs.num = 1;
					अवरोध;
				शेष:
					BUG();
			पूर्ण
		पूर्ण

		/* Check that chip is expecting address */
		अगर (!(ns->nxstate & STATE_ADDR_MASK)) अणु
			NS_ERR("write_byte: address (%#x) isn't expected, expected state is %s, switch to STATE_READY\n",
			       (uपूर्णांक)byte, ns_get_state_name(ns->nxstate));
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
			वापस;
		पूर्ण

		/* Check अगर this is expected byte */
		अगर (ns->regs.count == ns->regs.num) अणु
			NS_ERR("write_byte: no more address bytes expected\n");
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
			वापस;
		पूर्ण

		ns_accept_addr_byte(ns, byte);

		ns->regs.count += 1;

		NS_DBG("write_byte: address byte %#x was accepted (%d bytes input, %d expected)\n",
				(uपूर्णांक)byte, ns->regs.count, ns->regs.num);

		अगर (ns->regs.count == ns->regs.num) अणु
			NS_DBG("address (%#x, %#x) is accepted\n", ns->regs.row, ns->regs.column);
			ns_चयन_state(ns);
		पूर्ण

	पूर्ण अन्यथा अणु
		/*
		 * The byte written is an input data.
		 */

		/* Check that chip is expecting data input */
		अगर (!(ns->state & STATE_DATAIN_MASK)) अणु
			NS_ERR("write_byte: data input (%#x) isn't expected, state is %s, switch to %s\n",
			       (uपूर्णांक)byte, ns_get_state_name(ns->state),
			       ns_get_state_name(STATE_READY));
			ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
			वापस;
		पूर्ण

		/* Check अगर this is expected byte */
		अगर (ns->regs.count == ns->regs.num) अणु
			NS_WARN("write_byte: %u input bytes has already been accepted, ignore write\n",
					ns->regs.num);
			वापस;
		पूर्ण

		अगर (ns->busw == 8) अणु
			ns->buf.byte[ns->regs.count] = byte;
			ns->regs.count += 1;
		पूर्ण अन्यथा अणु
			ns->buf.word[ns->regs.count >> 1] = cpu_to_le16((uपूर्णांक16_t)byte);
			ns->regs.count += 2;
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल व्योम ns_nand_ग_लिखो_buf(काष्ठा nand_chip *chip, स्थिर u_अक्षर *buf,
			      पूर्णांक len)
अणु
	काष्ठा nandsim *ns = nand_get_controller_data(chip);

	/* Check that chip is expecting data input */
	अगर (!(ns->state & STATE_DATAIN_MASK)) अणु
		NS_ERR("write_buf: data input isn't expected, state is %s, switch to STATE_READY\n",
		       ns_get_state_name(ns->state));
		ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
		वापस;
	पूर्ण

	/* Check अगर these are expected bytes */
	अगर (ns->regs.count + len > ns->regs.num) अणु
		NS_ERR("write_buf: too many input bytes\n");
		ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
		वापस;
	पूर्ण

	स_नकल(ns->buf.byte + ns->regs.count, buf, len);
	ns->regs.count += len;

	अगर (ns->regs.count == ns->regs.num) अणु
		NS_DBG("write_buf: %d bytes were written\n", ns->regs.count);
	पूर्ण
पूर्ण

अटल व्योम ns_nand_पढ़ो_buf(काष्ठा nand_chip *chip, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा nandsim *ns = nand_get_controller_data(chip);

	/* Sanity and correctness checks */
	अगर (!ns->lines.ce) अणु
		NS_ERR("read_buf: chip is disabled\n");
		वापस;
	पूर्ण
	अगर (ns->lines.ale || ns->lines.cle) अणु
		NS_ERR("read_buf: ALE or CLE pin is high\n");
		वापस;
	पूर्ण
	अगर (!(ns->state & STATE_DATAOUT_MASK)) अणु
		NS_WARN("read_buf: unexpected data output cycle, current state is %s\n",
			ns_get_state_name(ns->state));
		वापस;
	पूर्ण

	अगर (NS_STATE(ns->state) != STATE_DATAOUT) अणु
		पूर्णांक i;

		क्रम (i = 0; i < len; i++)
			buf[i] = ns_nand_पढ़ो_byte(chip);

		वापस;
	पूर्ण

	/* Check अगर these are expected bytes */
	अगर (ns->regs.count + len > ns->regs.num) अणु
		NS_ERR("read_buf: too many bytes to read\n");
		ns_चयन_to_पढ़ोy_state(ns, NS_STATUS_FAILED(ns));
		वापस;
	पूर्ण

	स_नकल(buf, ns->buf.byte + ns->regs.count, len);
	ns->regs.count += len;

	अगर (ns->regs.count == ns->regs.num) अणु
		अगर (NS_STATE(ns->nxstate) == STATE_READY)
			ns_चयन_state(ns);
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक ns_exec_op(काष्ठा nand_chip *chip, स्थिर काष्ठा nand_operation *op,
		      bool check_only)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक op_id;
	स्थिर काष्ठा nand_op_instr *instr = शून्य;
	काष्ठा nandsim *ns = nand_get_controller_data(chip);

	अगर (check_only)
		वापस 0;

	ns->lines.ce = 1;

	क्रम (op_id = 0; op_id < op->ninstrs; op_id++) अणु
		instr = &op->instrs[op_id];
		ns->lines.cle = 0;
		ns->lines.ale = 0;

		चयन (instr->type) अणु
		हाल न_अंकD_OP_CMD_INSTR:
			ns->lines.cle = 1;
			ns_nand_ग_लिखो_byte(chip, instr->ctx.cmd.opcode);
			अवरोध;
		हाल न_अंकD_OP_ADDR_INSTR:
			ns->lines.ale = 1;
			क्रम (i = 0; i < instr->ctx.addr.naddrs; i++)
				ns_nand_ग_लिखो_byte(chip, instr->ctx.addr.addrs[i]);
			अवरोध;
		हाल न_अंकD_OP_DATA_IN_INSTR:
			ns_nand_पढ़ो_buf(chip, instr->ctx.data.buf.in, instr->ctx.data.len);
			अवरोध;
		हाल न_अंकD_OP_DATA_OUT_INSTR:
			ns_nand_ग_लिखो_buf(chip, instr->ctx.data.buf.out, instr->ctx.data.len);
			अवरोध;
		हाल न_अंकD_OP_WAITRDY_INSTR:
			/* we are always पढ़ोy */
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ns_attach_chip(काष्ठा nand_chip *chip)
अणु
	अचिन्हित पूर्णांक eccsteps, eccbytes;

	chip->ecc.engine_type = न_अंकD_ECC_ENGINE_TYPE_SOFT;
	chip->ecc.algo = bch ? न_अंकD_ECC_ALGO_BCH : न_अंकD_ECC_ALGO_HAMMING;

	अगर (!bch)
		वापस 0;

	अगर (!IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_BCH)) अणु
		NS_ERR("BCH ECC support is disabled\n");
		वापस -EINVAL;
	पूर्ण

	/* Use 512-byte ecc blocks */
	eccsteps = nsmtd->ग_लिखोsize / 512;
	eccbytes = ((bch * 13) + 7) / 8;

	/* Do not bother supporting small page devices */
	अगर (nsmtd->oobsize < 64 || !eccsteps) अणु
		NS_ERR("BCH not available on small page devices\n");
		वापस -EINVAL;
	पूर्ण

	अगर (((eccbytes * eccsteps) + 2) > nsmtd->oobsize) अणु
		NS_ERR("Invalid BCH value %u\n", bch);
		वापस -EINVAL;
	पूर्ण

	chip->ecc.size = 512;
	chip->ecc.strength = bch;
	chip->ecc.bytes = eccbytes;

	NS_INFO("Using %u-bit/%u bytes BCH ECC\n", bch, chip->ecc.size);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops ns_controller_ops = अणु
	.attach_chip = ns_attach_chip,
	.exec_op = ns_exec_op,
पूर्ण;

/*
 * Module initialization function
 */
अटल पूर्णांक __init ns_init_module(व्योम)
अणु
	काष्ठा list_head *pos, *n;
	काष्ठा nand_chip *chip;
	काष्ठा nandsim *ns;
	पूर्णांक ret;

	अगर (bus_width != 8 && bus_width != 16) अणु
		NS_ERR("wrong bus width (%d), use only 8 or 16\n", bus_width);
		वापस -EINVAL;
	पूर्ण

	ns = kzalloc(माप(काष्ठा nandsim), GFP_KERNEL);
	अगर (!ns) अणु
		NS_ERR("unable to allocate core structures.\n");
		वापस -ENOMEM;
	पूर्ण
	chip	    = &ns->chip;
	nsmtd       = nand_to_mtd(chip);
	nand_set_controller_data(chip, (व्योम *)ns);

	/* The न_अंकD_SKIP_BBTSCAN option is necessary क्रम 'overridesize' */
	/* and 'badblocks' parameters to work */
	chip->options   |= न_अंकD_SKIP_BBTSCAN;

	चयन (bbt) अणु
	हाल 2:
		chip->bbt_options |= न_अंकD_BBT_NO_OOB;
		fallthrough;
	हाल 1:
		chip->bbt_options |= न_अंकD_BBT_USE_FLASH;
		fallthrough;
	हाल 0:
		अवरोध;
	शेष:
		NS_ERR("bbt has to be 0..2\n");
		ret = -EINVAL;
		जाओ मुक्त_ns_काष्ठा;
	पूर्ण
	/*
	 * Perक्रमm minimum nandsim काष्ठाure initialization to handle
	 * the initial ID पढ़ो command correctly
	 */
	अगर (id_bytes[6] != 0xFF || id_bytes[7] != 0xFF)
		ns->geom.idbytes = 8;
	अन्यथा अगर (id_bytes[4] != 0xFF || id_bytes[5] != 0xFF)
		ns->geom.idbytes = 6;
	अन्यथा अगर (id_bytes[2] != 0xFF || id_bytes[3] != 0xFF)
		ns->geom.idbytes = 4;
	अन्यथा
		ns->geom.idbytes = 2;
	ns->regs.status = NS_STATUS_OK(ns);
	ns->nxstate = STATE_UNKNOWN;
	ns->options |= OPT_PAGE512; /* temporary value */
	स_नकल(ns->ids, id_bytes, माप(ns->ids));
	अगर (bus_width == 16) अणु
		ns->busw = 16;
		chip->options |= न_अंकD_BUSWIDTH_16;
	पूर्ण

	nsmtd->owner = THIS_MODULE;

	ret = ns_parse_weakblocks();
	अगर (ret)
		जाओ मुक्त_ns_काष्ठा;

	ret = ns_parse_weakpages();
	अगर (ret)
		जाओ मुक्त_wb_list;

	ret = ns_parse_gravepages();
	अगर (ret)
		जाओ मुक्त_wp_list;

	nand_controller_init(&ns->base);
	ns->base.ops = &ns_controller_ops;
	chip->controller = &ns->base;

	ret = nand_scan(chip, 1);
	अगर (ret) अणु
		NS_ERR("Could not scan NAND Simulator device\n");
		जाओ मुक्त_gp_list;
	पूर्ण

	अगर (overridesize) अणु
		uपूर्णांक64_t new_size = (uपूर्णांक64_t)nsmtd->erasesize << overridesize;
		काष्ठा nand_memory_organization *memorg;
		u64 tarमाला_लोize;

		memorg = nanddev_get_memorg(&chip->base);

		अगर (new_size >> overridesize != nsmtd->erasesize) अणु
			NS_ERR("overridesize is too big\n");
			ret = -EINVAL;
			जाओ cleanup_nand;
		पूर्ण

		/* N.B. This relies on nand_scan not करोing anything with the size beक्रमe we change it */
		nsmtd->size = new_size;
		memorg->eraseblocks_per_lun = 1 << overridesize;
		tarमाला_लोize = nanddev_target_size(&chip->base);
		chip->chip_shअगरt = ffs(nsmtd->erasesize) + overridesize - 1;
		chip->pagemask = (tarमाला_लोize >> chip->page_shअगरt) - 1;
	पूर्ण

	ret = ns_setup_wear_reporting(nsmtd);
	अगर (ret)
		जाओ cleanup_nand;

	ret = ns_init(nsmtd);
	अगर (ret)
		जाओ मुक्त_ebw;

	ret = nand_create_bbt(chip);
	अगर (ret)
		जाओ मुक्त_ns_object;

	ret = ns_parse_badblocks(ns, nsmtd);
	अगर (ret)
		जाओ मुक्त_ns_object;

	/* Register न_अंकD partitions */
	ret = mtd_device_रेजिस्टर(nsmtd, &ns->partitions[0], ns->nbparts);
	अगर (ret)
		जाओ मुक्त_ns_object;

	ret = ns_debugfs_create(ns);
	अगर (ret)
		जाओ unरेजिस्टर_mtd;

        वापस 0;

unरेजिस्टर_mtd:
	WARN_ON(mtd_device_unरेजिस्टर(nsmtd));
मुक्त_ns_object:
	ns_मुक्त(ns);
मुक्त_ebw:
	kमुक्त(erase_block_wear);
cleanup_nand:
	nand_cleanup(chip);
मुक्त_gp_list:
	list_क्रम_each_safe(pos, n, &grave_pages) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा grave_page, list));
	पूर्ण
मुक्त_wp_list:
	list_क्रम_each_safe(pos, n, &weak_pages) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा weak_page, list));
	पूर्ण
मुक्त_wb_list:
	list_क्रम_each_safe(pos, n, &weak_blocks) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा weak_block, list));
	पूर्ण
मुक्त_ns_काष्ठा:
	kमुक्त(ns);

	वापस ret;
पूर्ण

module_init(ns_init_module);

/*
 * Module clean-up function
 */
अटल व्योम __निकास ns_cleanup_module(व्योम)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(nsmtd);
	काष्ठा nandsim *ns = nand_get_controller_data(chip);
	काष्ठा list_head *pos, *n;

	ns_debugfs_हटाओ(ns);
	WARN_ON(mtd_device_unरेजिस्टर(nsmtd));
	ns_मुक्त(ns);
	kमुक्त(erase_block_wear);
	nand_cleanup(chip);

	list_क्रम_each_safe(pos, n, &grave_pages) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा grave_page, list));
	पूर्ण

	list_क्रम_each_safe(pos, n, &weak_pages) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा weak_page, list));
	पूर्ण

	list_क्रम_each_safe(pos, n, &weak_blocks) अणु
		list_del(pos);
		kमुक्त(list_entry(pos, काष्ठा weak_block, list));
	पूर्ण

	kमुक्त(ns);
पूर्ण

module_निकास(ns_cleanup_module);

MODULE_LICENSE ("GPL");
MODULE_AUTHOR ("Artem B. Bityuckiy");
MODULE_DESCRIPTION ("The NAND flash simulator");
