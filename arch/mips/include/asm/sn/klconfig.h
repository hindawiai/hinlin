<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Derived from IRIX <sys/SN/klconfig.h>.
 *
 * Copyright (C) 1992 - 1997, 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 1999, 2000 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_KLCONFIG_H
#घोषणा _ASM_SN_KLCONFIG_H

/*
 * The KLCONFIG काष्ठाures store info about the various BOARDs found
 * during Hardware Discovery. In addition, it stores info about the
 * components found on the BOARDs.
 */

/*
 * WARNING:
 *	Certain assembly language routines (notably xxxxx.s) in the IP27PROM
 *	will depend on the क्रमmat of the data काष्ठाures in this file.	In
 *	most हालs, rearranging the fields can seriously अवरोध things.
 *	Adding fields in the beginning or middle can also अवरोध things.
 *	Add fields अगर necessary, to the end of a काष्ठा in such a way
 *	that offsets of existing fields करो not change.
 */

#समावेश <linux/types.h>
#समावेश <यंत्र/sn/types.h>

#अगर defined(CONFIG_SGI_IP27)

#समावेश <यंत्र/sn/sn0/addrs.h>
//#समावेश <sys/SN/router.h>
// XXX Stolen from <sys/SN/router.h>:
#घोषणा MAX_ROUTER_PORTS (6)	/* Max. number of ports on a router */
#समावेश <यंत्र/sn/fru.h>
//#समावेश <sys/graph.h>
//#समावेश <sys/xtalk/xbow.h>

#या_अगर defined(CONFIG_SGI_IP35)

#समावेश <यंत्र/sn/sn1/addrs.h>
#समावेश <sys/sn/router.h>
#समावेश <sys/graph.h>
#समावेश <यंत्र/xtalk/xbow.h>

#पूर्ण_अगर /* !CONFIG_SGI_IP27 && !CONFIG_SGI_IP35 */

#अगर defined(CONFIG_SGI_IP27) || defined(CONFIG_SGI_IP35)
#समावेश <यंत्र/sn/agent.h>
#समावेश <यंत्र/fw/arc/types.h>
#समावेश <यंत्र/fw/arc/hinv.h>
#अगर defined(CONFIG_SGI_IP35)
// The hack file has to be beक्रमe vector and after sn0_fru....
#समावेश <यंत्र/hack.h>
#समावेश <यंत्र/sn/vector.h>
#समावेश <यंत्र/xtalk/xtalk.h>
#पूर्ण_अगर /* CONFIG_SGI_IP35 */
#पूर्ण_अगर /* CONFIG_SGI_IP27 || CONFIG_SGI_IP35 */

प्रकार u64  nic_t;

#घोषणा KLCFGINFO_MAGIC 0xbeedbabe

प्रकार s32 klconf_off_t;

/*
 * Some IMPORTANT OFFSETS. These are the offsets on all NODES.
 */
#घोषणा MAX_MODULE_ID		255
#घोषणा SIZE_PAD		4096 /* 4k padding क्रम काष्ठाures */
/*
 * 1 NODE brd, 2 Router brd (1 8p, 1 meta), 6 Widमाला_लो,
 * 2 Midplanes assuming no pci card cages
 */
#घोषणा MAX_SLOTS_PER_NODE	(1 + 2 + 6 + 2)

/* XXX अगर each node is guaranteed to have some memory */

#घोषणा MAX_PCI_DEVS		8

/* lboard_t->brd_flags fields */
/* All bits in this field are currently used. Try the pad fields अगर
   you need more flag bits */

#घोषणा ENABLE_BOARD		0x01
#घोषणा FAILED_BOARD		0x02
#घोषणा DUPLICATE_BOARD		0x04	/* Boards like midplanes/routers which
					   are discovered twice. Use one of them */
#घोषणा VISITED_BOARD		0x08	/* Used क्रम compact hub numbering. */
#घोषणा LOCAL_MASTER_IO6	0x10	/* master io6 क्रम that node */
#घोषणा GLOBAL_MASTER_IO6	0x20
#घोषणा THIRD_NIC_PRESENT	0x40	/* क्रम future use */
#घोषणा SECOND_NIC_PRESENT	0x80	/* adकरोns like MIO are present */

/* klinfo->flags fields */

#घोषणा KLINFO_ENABLE		0x01	/* This component is enabled */
#घोषणा KLINFO_FAILED		0x02	/* This component failed */
#घोषणा KLINFO_DEVICE		0x04	/* This component is a device */
#घोषणा KLINFO_VISITED		0x08	/* This component has been visited */
#घोषणा KLINFO_CONTROLLER	0x10	/* This component is a device controller */
#घोषणा KLINFO_INSTALL		0x20	/* Install a driver */
#घोषणा KLINFO_HEADLESS		0x40	/* Headless (or hubless) component */
#घोषणा IS_CONSOLE_IOC3(i)	((((klinfo_t *)i)->flags) & KLINFO_INSTALL)

#घोषणा GB2		0x80000000

#घोषणा MAX_RSV_PTRS	32

/* Structures to manage various data storage areas */
/* The numbers must be contiguous since the array index i
   is used in the code to allocate various areas.
*/

#घोषणा BOARD_STRUCT		0
#घोषणा COMPONENT_STRUCT	1
#घोषणा ERRINFO_STRUCT		2
#घोषणा KLMALLOC_TYPE_MAX	(ERRINFO_STRUCT + 1)
#घोषणा DEVICE_STRUCT		3


प्रकार काष्ठा console_s अणु
	अचिन्हित दीर्घ	uart_base;
	अचिन्हित दीर्घ	config_base;
	अचिन्हित दीर्घ	memory_base;
	लघु		baud;
	लघु		flag;
	पूर्णांक		type;
	nasid_t		nasid;
	अक्षर		wid;
	अक्षर		npci;
	nic_t		baseio_nic;
पूर्ण console_t;

प्रकार काष्ठा klc_दो_स्मृति_hdr अणु
	klconf_off_t km_base;
	klconf_off_t km_limit;
	klconf_off_t km_current;
पूर्ण klc_दो_स्मृति_hdr_t;

/* Functions/macros needed to use this काष्ठाure */

प्रकार काष्ठा kl_config_hdr अणु
	u64		ch_magic;	/* set this to KLCFGINFO_MAGIC */
	u32		ch_version;    /* काष्ठाure version number */
	klconf_off_t	ch_दो_स्मृति_hdr_off; /* offset of ch_दो_स्मृति_hdr */
	klconf_off_t	ch_cons_off;	   /* offset of ch_cons */
	klconf_off_t	ch_board_info;	/* the link list of boards */
	console_t	ch_cons_info;	/* address info of the console */
	klc_दो_स्मृति_hdr_t ch_दो_स्मृति_hdr[KLMALLOC_TYPE_MAX];
	confidence_t	ch_sw_belief;	/* confidence that software is bad*/
	confidence_t	ch_sn0net_belief; /* confidence that sn0net is bad */
पूर्ण kl_config_hdr_t;


#घोषणा KL_CONFIG_HDR(_nasid)	((kl_config_hdr_t *)(KLCONFIG_ADDR(_nasid)))
#घोषणा KL_CONFIG_INFO_OFFSET(_nasid)					\
	(KL_CONFIG_HDR(_nasid)->ch_board_info)
#घोषणा KL_CONFIG_INFO_SET_OFFSET(_nasid, _off)				\
	(KL_CONFIG_HDR(_nasid)->ch_board_info = (_off))

#घोषणा KL_CONFIG_INFO(_nasid)						\
	(lboard_t *)((KL_CONFIG_HDR(_nasid)->ch_board_info) ?		\
	 NODE_OFFSET_TO_K1((_nasid), KL_CONFIG_HDR(_nasid)->ch_board_info) : \
	 0)
#घोषणा KL_CONFIG_MAGIC(_nasid)		(KL_CONFIG_HDR(_nasid)->ch_magic)

#घोषणा KL_CONFIG_CHECK_MAGIC(_nasid)					\
	(KL_CONFIG_HDR(_nasid)->ch_magic == KLCFGINFO_MAGIC)

#घोषणा KL_CONFIG_HDR_INIT_MAGIC(_nasid)	\
		  (KL_CONFIG_HDR(_nasid)->ch_magic = KLCFGINFO_MAGIC)

/* --- New Macros क्रम the changed kl_config_hdr_t काष्ठाure --- */

#घोषणा PTR_CH_MALLOC_HDR(_k)	((klc_दो_स्मृति_hdr_t *)\
			((अचिन्हित दीर्घ)_k + (_k->ch_दो_स्मृति_hdr_off)))

#घोषणा KL_CONFIG_CH_MALLOC_HDR(_n)   PTR_CH_MALLOC_HDR(KL_CONFIG_HDR(_n))

#घोषणा PTR_CH_CONS_INFO(_k)	((console_t *)\
			((अचिन्हित दीर्घ)_k + (_k->ch_cons_off)))

#घोषणा KL_CONFIG_CH_CONS_INFO(_n)   PTR_CH_CONS_INFO(KL_CONFIG_HDR(_n))

/* ------------------------------------------------------------- */

#घोषणा KL_CONFIG_INFO_START(_nasid)	\
	(klconf_off_t)(KLCONFIG_OFFSET(_nasid) + माप(kl_config_hdr_t))

#घोषणा KL_CONFIG_BOARD_NASID(_brd)	((_brd)->brd_nasid)
#घोषणा KL_CONFIG_BOARD_SET_NEXT(_brd, _off)	((_brd)->brd_next = (_off))

#घोषणा KL_CONFIG_DUPLICATE_BOARD(_brd) ((_brd)->brd_flags & DUPLICATE_BOARD)

#घोषणा XBOW_PORT_TYPE_HUB(_xbowp, _link)	\
	       ((_xbowp)->xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag & XBOW_PORT_HUB)
#घोषणा XBOW_PORT_TYPE_IO(_xbowp, _link)	\
	       ((_xbowp)->xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag & XBOW_PORT_IO)

#घोषणा XBOW_PORT_IS_ENABLED(_xbowp, _link)	\
	       ((_xbowp)->xbow_port_info[(_link) - BASE_XBOW_PORT].port_flag & XBOW_PORT_ENABLE)
#घोषणा XBOW_PORT_NASID(_xbowp, _link)	\
	       ((_xbowp)->xbow_port_info[(_link) - BASE_XBOW_PORT].port_nasid)

#घोषणा XBOW_PORT_IO	 0x1
#घोषणा XBOW_PORT_HUB	 0x2
#घोषणा XBOW_PORT_ENABLE 0x4

#घोषणा SN0_PORT_FENCE_SHFT	0
#घोषणा SN0_PORT_FENCE_MASK	(1 << SN0_PORT_FENCE_SHFT)

/*
 * The KLCONFIG area is organized as a LINKED LIST of BOARDs. A BOARD
 * can be either 'LOCAL' or 'REMOTE'. LOCAL means it is attached to
 * the LOCAL/current NODE. REMOTE means it is attached to a dअगरferent
 * node.(TBD - Need a way to treat ROUTER boards.)
 *
 * There are 2 dअगरferent काष्ठाures to represent these boards -
 * lboard - Local board, rboard - remote board. These 2 काष्ठाures
 * can be arbitrarily mixed in the LINKED LIST of BOARDs. (Refer
 * Figure below). The first byte of the rboard or lboard काष्ठाure
 * is used to find out its type - no जोड़s are used.
 * If it is a lboard, then the config info of this board will be found
 * on the local node. (LOCAL NODE BASE + offset value gives poपूर्णांकer to
 * the काष्ठाure.
 * If it is a rboard, the local काष्ठाure contains the node number
 * and the offset of the beginning of the LINKED LIST on the remote node.
 * The details of the hardware on a remote node can be built locally,
 * अगर required, by पढ़ोing the LINKED LIST on the remote node and
 * ignoring all the rboards on that node.
 *
 * The local node uses the REMOTE NODE NUMBER + OFFSET to poपूर्णांक to the
 * First board info on the remote node. The remote node list is
 * traversed as the local list, using the REMOTE BASE ADDRESS and not
 * the local base address and ignoring all rboard values.
 *
 *
 KLCONFIG

 +------------+	     +------------+	 +------------+	     +------------+
 |  lboard    |	 +-->|	 lboard	  |  +-->|   rboard   |	 +-->|	 lboard	  |
 +------------+	 |   +------------+  |	 +------------+	 |   +------------+
 | board info |	 |   | board info |  |	 |errinfo,bptr|	 |   | board info |
 +------------+	 |   +------------+  |	 +------------+	 |   +------------+
 | offset     |--+   |	offset	  |--+	 |  offset    |--+   |offset=शून्य |
 +------------+	     +------------+	 +------------+	     +------------+


 +------------+
 | board info |
 +------------+	      +--------------------------------+
 | compt 1    |------>| type, rev, diaginfo, size ...  |  (CPU)
 +------------+	      +--------------------------------+
 | compt 2    |--+
 +------------+	 |    +--------------------------------+
 |  ...	      |	 +--->| type, rev, diaginfo, size ...  |  (MEM_BANK)
 +------------+	      +--------------------------------+
 | errinfo    |--+
 +------------+	 |    +--------------------------------+
		 +--->|r/l brd errinfo,compt err flags |
		      +--------------------------------+

 *
 * Each BOARD consists of COMPONENTs and the BOARD काष्ठाure has
 * poपूर्णांकers (offsets) to its COMPONENT काष्ठाure.
 * The COMPONENT काष्ठाure has version info, size and speed info, revision,
 * error info and the NIC info. This काष्ठाure can accommodate any
 * BOARD with arbitrary COMPONENT composition.
 *
 * The ERRORINFO part of each BOARD has error inक्रमmation
 * that describes errors about the BOARD itself. It also has flags to
 * indicate the COMPONENT(s) on the board that have errors. The error
 * inक्रमmation specअगरic to the COMPONENT is present in the respective
 * COMPONENT काष्ठाure.
 *
 * The ERRORINFO काष्ठाure is also treated like a COMPONENT, ie. the
 * BOARD has poपूर्णांकers(offset) to the ERRORINFO काष्ठाure. The rboard
 * काष्ठाure also has a poपूर्णांकer to the ERRORINFO काष्ठाure. This is
 * the place to store ERRORINFO about a REMOTE NODE, अगर the HUB on
 * that NODE is not working or अगर the REMOTE MEMORY is BAD. In हालs where
 * only the CPU of the REMOTE NODE is disabled, the ERRORINFO poपूर्णांकer can
 * be a NODE NUMBER, REMOTE OFFSET combination, poपूर्णांकing to error info
 * which is present on the REMOTE NODE.(TBD)
 * REMOTE ERRINFO can be stored on any of the nearest nodes
 * or on all the nearest nodes.(TBD)
 * Like BOARD काष्ठाures, REMOTE ERRINFO काष्ठाures can be built locally
 * using the rboard errinfo poपूर्णांकer.
 *
 * In order to get useful inक्रमmation from this Data organization, a set of
 * पूर्णांकerface routines are provided (TBD). The important thing to remember जबतक
 * manipulating the काष्ठाures, is that, the NODE number inक्रमmation should
 * be used. If the NODE is non-zero (remote) then each offset should
 * be added to the REMOTE BASE ADDR अन्यथा it should be added to the LOCAL BASE ADDR.
 * This includes offsets क्रम BOARDS, COMPONENTS and ERRORINFO.
 *
 * Note that these काष्ठाures करो not provide much info about connectivity.
 * That info will be part of HWGRAPH, which is an extension of the cfg_t
 * data काष्ठाure. (ref IP27prom/cfg.h) It has to be extended to include
 * the IO part of the Network(TBD).
 *
 * The data काष्ठाures below define the above concepts.
 */

/*
 * Values क्रम CPU types
 */
#घोषणा KL_CPU_R4000		0x1	/* Standard R4000 */
#घोषणा KL_CPU_TFP		0x2	/* TFP processor */
#घोषणा KL_CPU_R10000		0x3	/* R10000 (T5) */
#घोषणा KL_CPU_NONE		(-1)	/* no cpu present in slot */

/*
 * IP27 BOARD classes
 */

#घोषणा KLCLASS_MASK	0xf0
#घोषणा KLCLASS_NONE	0x00
#घोषणा KLCLASS_NODE	0x10		 /* CPU, Memory and HUB board */
#घोषणा KLCLASS_CPU	KLCLASS_NODE
#घोषणा KLCLASS_IO	0x20		 /* BaseIO, 4 ch SCSI, ethernet, FDDI
					    and the non-graphics widget boards */
#घोषणा KLCLASS_ROUTER	0x30		 /* Router board */
#घोषणा KLCLASS_MIDPLANE 0x40		 /* We need to treat this as a board
					    so that we can record error info */
#घोषणा KLCLASS_GFX	0x50		/* graphics boards */

#घोषणा KLCLASS_PSEUDO_GFX	0x60	/* HDTV type cards that use a gfx
					 * hw अगरc to xtalk and are not gfx
					 * class क्रम sw purposes */

#घोषणा KLCLASS_MAX	7		/* Bump this अगर a new CLASS is added */
#घोषणा KLTYPE_MAX	10		/* Bump this अगर a new CLASS is added */

#घोषणा KLCLASS_UNKNOWN 0xf0

#घोषणा KLCLASS(_x) ((_x) & KLCLASS_MASK)

/*
 * IP27 board types
 */

#घोषणा KLTYPE_MASK	0x0f
#घोषणा KLTYPE_NONE	0x00
#घोषणा KLTYPE_EMPTY	0x00

#घोषणा KLTYPE_WEIRDCPU (KLCLASS_CPU | 0x0)
#घोषणा KLTYPE_IP27	(KLCLASS_CPU | 0x1) /* 2 CPUs(R10K) per board */

#घोषणा KLTYPE_WEIRDIO	(KLCLASS_IO  | 0x0)
#घोषणा KLTYPE_BASEIO	(KLCLASS_IO  | 0x1) /* IOC3, SuperIO, Bridge, SCSI */
#घोषणा KLTYPE_IO6	KLTYPE_BASEIO	    /* Additional name */
#घोषणा KLTYPE_4CHSCSI	(KLCLASS_IO  | 0x2)
#घोषणा KLTYPE_MSCSI	KLTYPE_4CHSCSI	    /* Additional name */
#घोषणा KLTYPE_ETHERNET (KLCLASS_IO  | 0x3)
#घोषणा KLTYPE_MENET	KLTYPE_ETHERNET	    /* Additional name */
#घोषणा KLTYPE_FDDI	(KLCLASS_IO  | 0x4)
#घोषणा KLTYPE_UNUSED	(KLCLASS_IO  | 0x5) /* XXX UNUSED */
#घोषणा KLTYPE_HAROLD	(KLCLASS_IO  | 0x6) /* PCI SHOE BOX */
#घोषणा KLTYPE_PCI	KLTYPE_HAROLD
#घोषणा KLTYPE_VME	(KLCLASS_IO  | 0x7) /* Any 3rd party VME card */
#घोषणा KLTYPE_MIO	(KLCLASS_IO  | 0x8)
#घोषणा KLTYPE_FC	(KLCLASS_IO  | 0x9)
#घोषणा KLTYPE_LINC	(KLCLASS_IO  | 0xA)
#घोषणा KLTYPE_TPU	(KLCLASS_IO  | 0xB) /* Tensor Processing Unit */
#घोषणा KLTYPE_GSN_A	(KLCLASS_IO  | 0xC) /* Main GSN board */
#घोषणा KLTYPE_GSN_B	(KLCLASS_IO  | 0xD) /* Auxiliary GSN board */

#घोषणा KLTYPE_GFX	(KLCLASS_GFX | 0x0) /* unknown graphics type */
#घोषणा KLTYPE_GFX_KONA (KLCLASS_GFX | 0x1) /* KONA graphics on IP27 */
#घोषणा KLTYPE_GFX_MGRA (KLCLASS_GFX | 0x3) /* MGRAS graphics on IP27 */

#घोषणा KLTYPE_WEIRDROUTER (KLCLASS_ROUTER | 0x0)
#घोषणा KLTYPE_ROUTER	  (KLCLASS_ROUTER | 0x1)
#घोषणा KLTYPE_ROUTER2	  KLTYPE_ROUTER		/* Obsolete! */
#घोषणा KLTYPE_शून्य_ROUTER (KLCLASS_ROUTER | 0x2)
#घोषणा KLTYPE_META_ROUTER (KLCLASS_ROUTER | 0x3)

#घोषणा KLTYPE_WEIRDMIDPLANE (KLCLASS_MIDPLANE | 0x0)
#घोषणा KLTYPE_MIDPLANE8  (KLCLASS_MIDPLANE | 0x1) /* 8 slot backplane */
#घोषणा KLTYPE_MIDPLANE	   KLTYPE_MIDPLANE8
#घोषणा KLTYPE_PBRICK_XBOW	(KLCLASS_MIDPLANE | 0x2)

#घोषणा KLTYPE_IOBRICK		(KLCLASS_IOBRICK | 0x0)
#घोषणा KLTYPE_IBRICK		(KLCLASS_IOBRICK | 0x1)
#घोषणा KLTYPE_PBRICK		(KLCLASS_IOBRICK | 0x2)
#घोषणा KLTYPE_XBRICK		(KLCLASS_IOBRICK | 0x3)

#घोषणा KLTYPE_PBRICK_BRIDGE	KLTYPE_PBRICK

/* The value of type should be more than 8 so that hinv prपूर्णांकs
 * out the board name from the NIC string. For values less than
 * 8 the name of the board needs to be hard coded in a few places.
 * When bringup started nic names had not standardized and so we
 * had to hard code. (For people पूर्णांकerested in history.)
 */
#घोषणा KLTYPE_XTHD	(KLCLASS_PSEUDO_GFX | 0x9)

#घोषणा KLTYPE_UNKNOWN	(KLCLASS_UNKNOWN | 0xf)

#घोषणा KLTYPE(_x)	((_x) & KLTYPE_MASK)
#घोषणा IS_MIO_PRESENT(l)	((l->brd_type == KLTYPE_BASEIO) && \
				 (l->brd_flags & SECOND_NIC_PRESENT))
#घोषणा IS_MIO_IOC3(l, n)	(IS_MIO_PRESENT(l) && (n > 2))

/*
 * board काष्ठाures
 */

#घोषणा MAX_COMPTS_PER_BRD 24

#घोषणा LOCAL_BOARD 1
#घोषणा REMOTE_BOARD 2

#घोषणा LBOARD_STRUCT_VERSION	2

प्रकार काष्ठा lboard_s अणु
	klconf_off_t	brd_next;	  /* Next BOARD */
	अचिन्हित अक्षर	काष्ठा_type;	  /* type of काष्ठाure, local or remote */
	अचिन्हित अक्षर	brd_type;	  /* type+class */
	अचिन्हित अक्षर	brd_sversion;	  /* version of this काष्ठाure */
	अचिन्हित अक्षर	brd_brevision;	  /* board revision */
	अचिन्हित अक्षर	brd_promver;	  /* board prom version, अगर any */
	अचिन्हित अक्षर	brd_flags;	  /* Enabled, Disabled etc */
	अचिन्हित अक्षर	brd_slot;	  /* slot number */
	अचिन्हित लघु	brd_debugsw;	  /* Debug चयनes */
	moduleid_t	brd_module;	  /* module to which it beदीर्घs */
	partid_t	brd_partition;	  /* Partition number */
	अचिन्हित लघु	brd_diagval;	  /* diagnostic value */
	अचिन्हित लघु	brd_diagparm;	  /* diagnostic parameter */
	अचिन्हित अक्षर	brd_inventory;	  /* inventory history */
	अचिन्हित अक्षर	brd_numcompts;	  /* Number of components */
	nic_t		brd_nic;	  /* Number in CAN */
	nasid_t		brd_nasid;	  /* passed parameter */
	klconf_off_t	brd_compts[MAX_COMPTS_PER_BRD]; /* poपूर्णांकers to COMPONENTS */
	klconf_off_t	brd_errinfo;	  /* Board's error inक्रमmation */
	काष्ठा lboard_s *brd_parent;	  /* Logical parent क्रम this brd */
	vertex_hdl_t	brd_graph_link;	  /* vertex hdl to connect बाह्य compts */
	confidence_t	brd_confidence;	  /* confidence that the board is bad */
	nasid_t		brd_owner;	  /* who owns this board */
	अचिन्हित अक्षर	brd_nic_flags;	  /* To handle 8 more NICs */
	अक्षर		brd_name[32];
पूर्ण lboard_t;


/*
 *	Make sure we pass back the calias space address क्रम local boards.
 *	klconfig board traversal and error काष्ठाure extraction defines.
 */

#घोषणा BOARD_SLOT(_brd)	((_brd)->brd_slot)

#घोषणा KLCF_CLASS(_brd)	KLCLASS((_brd)->brd_type)
#घोषणा KLCF_TYPE(_brd)		KLTYPE((_brd)->brd_type)
#घोषणा KLCF_REMOTE(_brd)	(((_brd)->काष्ठा_type & LOCAL_BOARD) ? 0 : 1)
#घोषणा KLCF_NUM_COMPS(_brd)	((_brd)->brd_numcompts)
#घोषणा KLCF_MODULE_ID(_brd)	((_brd)->brd_module)

#घोषणा KLCF_NEXT(_brd)		\
	((_brd)->brd_next ?	\
	 (lboard_t *)(NODE_OFFSET_TO_K1(NASID_GET(_brd), (_brd)->brd_next)):\
	 शून्य)
#घोषणा KLCF_COMP(_brd, _ndx)	\
		(klinfo_t *)(NODE_OFFSET_TO_K1(NASID_GET(_brd), \
					       (_brd)->brd_compts[(_ndx)]))

#घोषणा KLCF_COMP_ERROR(_brd, _comp)	\
	       (NODE_OFFSET_TO_K1(NASID_GET(_brd), (_comp)->errinfo))

#घोषणा KLCF_COMP_TYPE(_comp)	((_comp)->काष्ठा_type)
#घोषणा KLCF_BRIDGE_W_ID(_comp) ((_comp)->physid)	/* Widget ID */



/*
 * Generic info काष्ठाure. This stores common info about a
 * component.
 */

प्रकार काष्ठा klinfo_s अणु		   /* Generic info */
	अचिन्हित अक्षर	काष्ठा_type;	   /* type of this काष्ठाure */
	अचिन्हित अक्षर	काष्ठा_version;	   /* version of this काष्ठाure */
	अचिन्हित अक्षर	flags;		  /* Enabled, disabled etc */
	अचिन्हित अक्षर	revision;	  /* component revision */
	अचिन्हित लघु	diagval;	  /* result of diagnostics */
	अचिन्हित लघु	diagparm;	  /* diagnostic parameter */
	अचिन्हित अक्षर	inventory;	  /* previous inventory status */
	nic_t		nic;		  /* MUst be aligned properly */
	अचिन्हित अक्षर	physid;		  /* physical id of component */
	अचिन्हित पूर्णांक	virtid;		  /* भव id as seen by प्रणाली */
	अचिन्हित अक्षर	widid;		  /* Widget id - अगर applicable */
	nasid_t		nasid;		  /* node number - from parent */
	अक्षर		pad1;		  /* pad out काष्ठाure. */
	अक्षर		pad2;		  /* pad out काष्ठाure. */
	COMPONENT	*arcs_compt;	  /* ptr to the arcs काष्ठा क्रम ease*/
	klconf_off_t	errinfo;	  /* component specअगरic errors */
	अचिन्हित लघु	pad3;		  /* pci fields have moved over to */
	अचिन्हित लघु	pad4;		  /* klbri_t */
पूर्ण klinfo_t ;

#घोषणा KLCONFIG_INFO_ENABLED(_i)	((_i)->flags & KLINFO_ENABLE)
/*
 * Component काष्ठाures.
 * Following are the currently identअगरied components:
 *	CPU, HUB, MEM_BANK,
 *	XBOW(consists of 16 WIDGETs, each of which can be HUB or GRAPHICS or BRIDGE)
 *	BRIDGE, IOC3, SuperIO, SCSI, FDDI
 *	ROUTER
 *	GRAPHICS
 */
#घोषणा KLSTRUCT_UNKNOWN	0
#घोषणा KLSTRUCT_CPU		1
#घोषणा KLSTRUCT_HUB		2
#घोषणा KLSTRUCT_MEMBNK		3
#घोषणा KLSTRUCT_XBOW		4
#घोषणा KLSTRUCT_BRI		5
#घोषणा KLSTRUCT_IOC3		6
#घोषणा KLSTRUCT_PCI		7
#घोषणा KLSTRUCT_VME		8
#घोषणा KLSTRUCT_ROU		9
#घोषणा KLSTRUCT_GFX		10
#घोषणा KLSTRUCT_SCSI		11
#घोषणा KLSTRUCT_FDDI		12
#घोषणा KLSTRUCT_MIO		13
#घोषणा KLSTRUCT_DISK		14
#घोषणा KLSTRUCT_TAPE		15
#घोषणा KLSTRUCT_CDROM		16
#घोषणा KLSTRUCT_HUB_UART	17
#घोषणा KLSTRUCT_IOC3ENET	18
#घोषणा KLSTRUCT_IOC3UART	19
#घोषणा KLSTRUCT_UNUSED		20 /* XXX UNUSED */
#घोषणा KLSTRUCT_IOC3PCKM	21
#घोषणा KLSTRUCT_RAD		22
#घोषणा KLSTRUCT_HUB_TTY	23
#घोषणा KLSTRUCT_IOC3_TTY	24

/* Early Access IO proms are compatible
   only with KLSTRUCT values up to 24. */

#घोषणा KLSTRUCT_FIBERCHANNEL	25
#घोषणा KLSTRUCT_MOD_SERIAL_NUM 26
#घोषणा KLSTRUCT_IOC3MS		27
#घोषणा KLSTRUCT_TPU		28
#घोषणा KLSTRUCT_GSN_A		29
#घोषणा KLSTRUCT_GSN_B		30
#घोषणा KLSTRUCT_XTHD		31

/*
 * These are the indices of various components within a lboard काष्ठाure.
 */

#घोषणा IP27_CPU0_INDEX 0
#घोषणा IP27_CPU1_INDEX 1
#घोषणा IP27_HUB_INDEX 2
#घोषणा IP27_MEM_INDEX 3

#घोषणा BASEIO_BRIDGE_INDEX 0
#घोषणा BASEIO_IOC3_INDEX 1
#घोषणा BASEIO_SCSI1_INDEX 2
#घोषणा BASEIO_SCSI2_INDEX 3

#घोषणा MIDPLANE_XBOW_INDEX 0
#घोषणा ROUTER_COMPONENT_INDEX 0

#घोषणा CH4SCSI_BRIDGE_INDEX 0

/* Info holders क्रम various hardware components */

प्रकार u64 *pci_t;
प्रकार u64 *vmeb_t;
प्रकार u64 *vmed_t;
प्रकार u64 *fddi_t;
प्रकार u64 *scsi_t;
प्रकार u64 *mio_t;
प्रकार u64 *graphics_t;
प्रकार u64 *router_t;

/*
 * The port info in ip27_cfg area translates to a lboart_t in the
 * KLCONFIG area. But since KLCONFIG करोes not use poपूर्णांकers, lboart_t
 * is stored in terms of a nasid and a offset from start of KLCONFIG
 * area	 on that nasid.
 */
प्रकार काष्ठा klport_s अणु
	nasid_t		port_nasid;
	अचिन्हित अक्षर	port_flag;
	klconf_off_t	port_offset;
पूर्ण klport_t;

प्रकार काष्ठा klcpu_s अणु			  /* CPU */
	klinfo_t	cpu_info;
	अचिन्हित लघु	cpu_prid;	/* Processor PRID value */
	अचिन्हित लघु	cpu_fpirr;	/* FPU IRR value */
	अचिन्हित लघु	cpu_speed;	/* Speed in MHZ */
	अचिन्हित लघु	cpu_scachesz;	/* secondary cache size in MB */
	अचिन्हित लघु	cpu_scachespeed;/* secondary cache speed in MHz */
पूर्ण klcpu_t ;

#घोषणा CPU_STRUCT_VERSION   2

प्रकार काष्ठा klhub_s अणु			/* HUB */
	klinfo_t	hub_info;
	अचिन्हित पूर्णांक		hub_flags;		/* PCFG_HUB_xxx flags */
	klport_t	hub_port;		/* hub is connected to this */
	nic_t		hub_box_nic;		/* nic of containing box */
	klconf_off_t	hub_mfg_nic;		/* MFG NIC string */
	u64		hub_speed;		/* Speed of hub in HZ */
पूर्ण klhub_t ;

प्रकार काष्ठा klhub_uart_s अणु			/* HUB */
	klinfo_t	hubuart_info;
	अचिन्हित पूर्णांक		hubuart_flags;		/* PCFG_HUB_xxx flags */
	nic_t		hubuart_box_nic;	/* nic of containing box */
पूर्ण klhub_uart_t ;

#घोषणा MEMORY_STRUCT_VERSION	2

प्रकार काष्ठा klmembnk_s अणु			/* MEMORY BANK */
	klinfo_t	membnk_info;
	लघु		membnk_memsz;		/* Total memory in megabytes */
	लघु		membnk_dimm_select; /* bank to physical addr mapping*/
	लघु		membnk_bnksz[MD_MEM_BANKS]; /* Memory bank sizes */
	लघु		membnk_attr;
पूर्ण klmembnk_t ;

#घोषणा KLCONFIG_MEMBNK_SIZE(_info, _bank)	\
			    ((_info)->membnk_bnksz[(_bank)])


#घोषणा MEMBNK_PREMIUM 1
#घोषणा KLCONFIG_MEMBNK_PREMIUM(_info, _bank)	\
			    ((_info)->membnk_attr & (MEMBNK_PREMIUM << (_bank)))

#घोषणा MAX_SERIAL_NUM_SIZE 10

प्रकार काष्ठा klmod_serial_num_s अणु
      klinfo_t	      snum_info;
      जोड़ अणु
	      अक्षर snum_str[MAX_SERIAL_NUM_SIZE];
	      अचिन्हित दीर्घ दीर्घ       snum_पूर्णांक;
      पूर्ण snum;
पूर्ण klmod_serial_num_t;

/* Macros needed to access serial number काष्ठाure in lboard_t.
   Hard coded values are necessary since we cannot treat
   serial number काष्ठा as a component without losing compatibility
   between prom versions. */

#घोषणा GET_SNUM_COMP(_l)	((klmod_serial_num_t *)\
				KLCF_COMP(_l, _l->brd_numcompts))

#घोषणा MAX_XBOW_LINKS 16

प्रकार काष्ठा klxbow_s अणु			   /* XBOW */
	klinfo_t	xbow_info ;
	klport_t	xbow_port_info[MAX_XBOW_LINKS] ; /* Module number */
	पूर्णांक		xbow_master_hub_link;
	/* type of brd connected+component काष्ठा ptr+flags */
पूर्ण klxbow_t ;

#घोषणा MAX_PCI_SLOTS 8

प्रकार काष्ठा klpci_device_s अणु
	s32	pci_device_id;	/* 32 bits of venकरोr/device ID. */
	s32	pci_device_pad; /* 32 bits of padding. */
पूर्ण klpci_device_t;

#घोषणा BRIDGE_STRUCT_VERSION	2

प्रकार काष्ठा klbri_s अणु			  /* BRIDGE */
	klinfo_t	bri_info ;
	अचिन्हित अक्षर	bri_eprominfo ;	   /* IO6prom connected to bridge */
	अचिन्हित अक्षर	bri_bustype ;	   /* PCI/VME BUS bridge/GIO */
	pci_t		pci_specअगरic  ;	   /* PCI Board config info */
	klpci_device_t	bri_devices[MAX_PCI_DEVS] ;	/* PCI IDs */
	klconf_off_t	bri_mfg_nic ;
पूर्ण klbri_t ;

#घोषणा MAX_IOC3_TTY	2

प्रकार काष्ठा klioc3_s अणु			   /* IOC3 */
	klinfo_t	ioc3_info ;
	अचिन्हित अक्षर	ioc3_ssram ;	    /* Info about ssram */
	अचिन्हित अक्षर	ioc3_nvram ;	    /* Info about nvram */
	klinfo_t	ioc3_superio ;	    /* Info about superio */
	klconf_off_t	ioc3_tty_off ;
	klinfo_t	ioc3_enet ;
	klconf_off_t	ioc3_enet_off ;
	klconf_off_t	ioc3_kbd_off ;
पूर्ण klioc3_t ;

#घोषणा MAX_VME_SLOTS 8

प्रकार काष्ठा klvmeb_s अणु			   /* VME BRIDGE - PCI CTLR */
	klinfo_t	vmeb_info ;
	vmeb_t		vmeb_specअगरic ;
	klconf_off_t	vmeb_brdinfo[MAX_VME_SLOTS]   ;	   /* VME Board config info */
पूर्ण klvmeb_t ;

प्रकार काष्ठा klvmed_s अणु			   /* VME DEVICE - VME BOARD */
	klinfo_t	vmed_info ;
	vmed_t		vmed_specअगरic ;
	klconf_off_t	vmed_brdinfo[MAX_VME_SLOTS]   ;	   /* VME Board config info */
पूर्ण klvmed_t ;

#घोषणा ROUTER_VECTOR_VERS	2

/* XXX - Don't we need the number of ports here?!? */
प्रकार काष्ठा klrou_s अणु			  /* ROUTER */
	klinfo_t	rou_info ;
	अचिन्हित पूर्णांक		rou_flags ;	      /* PCFG_ROUTER_xxx flags */
	nic_t		rou_box_nic ;	      /* nic of the containing module */
	klport_t	rou_port[MAX_ROUTER_PORTS + 1] ; /* array index 1 to 6 */
	klconf_off_t	rou_mfg_nic ;	  /* MFG NIC string */
	u64	rou_vector;	  /* vector from master node */
पूर्ण klrou_t ;

/*
 *  Graphics Controller/Device
 *
 *  (IP27/IO6) Prom versions 6.13 (and 6.5.1 kernels) and earlier
 *  used a couple dअगरferent काष्ठाures to store graphics inक्रमmation.
 *  For compatibility reasons, the newer data काष्ठाure preserves some
 *  of the layout so that fields that are used in the old versions reमुख्य
 *  in the same place (with the same info).  Determination of what version
 *  of this काष्ठाure we have is करोne by checking the cookie field.
 */
#घोषणा KLGFX_COOKIE	0x0c0de000

प्रकार काष्ठा klgfx_s अणु		/* GRAPHICS Device */
	klinfo_t	gfx_info;
	klconf_off_t	old_gndevs;	/* क्रम compatibility with older proms */
	klconf_off_t	old_gकरोff0;	/* क्रम compatibility with older proms */
	अचिन्हित पूर्णांक		cookie;		/* क्रम compatibility with older proms */
	अचिन्हित पूर्णांक		moduleslot;
	काष्ठा klgfx_s	*gfx_next_pipe;
	graphics_t	gfx_specअगरic;
	klconf_off_t	pad0;		/* क्रम compatibility with older proms */
	klconf_off_t	gfx_mfg_nic;
पूर्ण klgfx_t;

प्रकार काष्ठा klxthd_s अणु
	klinfo_t	xthd_info ;
	klconf_off_t	xthd_mfg_nic ;	      /* MFG NIC string */
पूर्ण klxthd_t ;

प्रकार काष्ठा kltpu_s अणु		     /* TPU board */
	klinfo_t	tpu_info ;
	klconf_off_t	tpu_mfg_nic ;	     /* MFG NIC string */
पूर्ण kltpu_t ;

प्रकार काष्ठा klgsn_s अणु		     /* GSN board */
	klinfo_t	gsn_info ;
	klconf_off_t	gsn_mfg_nic ;	     /* MFG NIC string */
पूर्ण klgsn_t ;

#घोषणा MAX_SCSI_DEVS 16

/*
 * NOTE: THis is the max sized kl* काष्ठाure and is used in klदो_स्मृति.c
 * to allocate space of type COMPONENT. Make sure that अगर the size of
 * any other component काष्ठा becomes more than this, then redefine
 * that as the size to be klदो_स्मृतिed.
 */

प्रकार काष्ठा klscsi_s अणु			   /* SCSI Controller */
	klinfo_t	scsi_info ;
	scsi_t		scsi_specअगरic	;
	अचिन्हित अक्षर	scsi_numdevs ;
	klconf_off_t	scsi_devinfo[MAX_SCSI_DEVS] ;
पूर्ण klscsi_t ;

प्रकार काष्ठा klscdev_s अणु			    /* SCSI device */
	klinfo_t	scdev_info ;
	काष्ठा scsidisk_data *scdev_cfg ; /* driver fills up this */
पूर्ण klscdev_t ;

प्रकार काष्ठा klttydev_s अणु			     /* TTY device */
	klinfo_t	ttydev_info ;
	काष्ठा terminal_data *ttydev_cfg ; /* driver fills up this */
पूर्ण klttydev_t ;

प्रकार काष्ठा klenetdev_s अणु			      /* ENET device */
	klinfo_t	enetdev_info ;
	काष्ठा net_data *enetdev_cfg ; /* driver fills up this */
पूर्ण klenetdev_t ;

प्रकार काष्ठा klkbddev_s अणु			     /* KBD device */
	klinfo_t	kbddev_info ;
	काष्ठा keyboard_data *kbddev_cfg ; /* driver fills up this */
पूर्ण klkbddev_t ;

प्रकार काष्ठा klmsdev_s अणु			    /* mouse device */
	klinfo_t	msdev_info ;
	व्योम		*msdev_cfg ;
पूर्ण klmsdev_t ;

#घोषणा MAX_FDDI_DEVS 10 /* XXX Is this true */

प्रकार काष्ठा klfddi_s अणु			   /* FDDI */
	klinfo_t	fddi_info ;
	fddi_t		fddi_specअगरic ;
	klconf_off_t	fddi_devinfo[MAX_FDDI_DEVS] ;
पूर्ण klfddi_t ;

प्रकार काष्ठा klmio_s अणु			  /* MIO */
	klinfo_t	mio_info ;
	mio_t		mio_specअगरic   ;
पूर्ण klmio_t ;


प्रकार जोड़ klcomp_s अणु
	klcpu_t		kc_cpu;
	klhub_t		kc_hub;
	klmembnk_t	kc_mem;
	klxbow_t	kc_xbow;
	klbri_t		kc_bri;
	klioc3_t	kc_ioc3;
	klvmeb_t	kc_vmeb;
	klvmed_t	kc_vmed;
	klrou_t		kc_rou;
	klgfx_t		kc_gfx;
	klscsi_t	kc_scsi;
	klscdev_t	kc_scsi_dev;
	klfddi_t	kc_fddi;
	klmio_t		kc_mio;
	klmod_serial_num_t kc_snum ;
पूर्ण klcomp_t;

प्रकार जोड़ kldev_s अणु	     /* क्रम device काष्ठाure allocation */
	klscdev_t	kc_scsi_dev ;
	klttydev_t	kc_tty_dev ;
	klenetdev_t	kc_enet_dev ;
	klkbddev_t	kc_kbd_dev ;
पूर्ण kldev_t ;

/* Data काष्ठाure पूर्णांकerface routines. TBD */

/* Include launch info in this file itself? TBD */

/*
 * TBD - Can the ARCS and device driver related info also be included in the
 * KLCONFIG area. On the IO4PROM, prom device driver info is part of cfgnode_t
 * काष्ठाure, viz निजी to the IO4prom.
 */

/*
 * TBD - Allocation issues.
 *
 * Do we need to Mark off sepatate heaps क्रम lboard_t, rboard_t, component,
 * errinfo and allocate from them, or have a single heap and allocate all
 * काष्ठाures from it. Debug is easier in the क्रमmer method since we can
 * dump all similar काष्ठाs in one command, but there will be lots of holes,
 * in memory and max limits are needed क्रम number of काष्ठाures.
 * Another way to make it organized, is to have a जोड़ of all components
 * and allocate a aligned chunk of memory greater than the biggest
 * component.
 */

प्रकार जोड़ अणु
	lboard_t *lbinfo ;
पूर्ण biptr_t ;


#घोषणा BRI_PER_XBOW 6
#घोषणा PCI_PER_BRI  8
#घोषणा DEV_PER_PCI  16


/* Virtual dipचयन values (starting from चयन "7"): */

#घोषणा VDS_NOGFX		0x8000	/* Don't enable gfx and स्वतःboot */
#घोषणा VDS_NOMP		0x100	/* Don't start slave processors */
#घोषणा VDS_MANUMODE		0x80	/* Manufacturing mode */
#घोषणा VDS_NOARB		0x40	/* No booपंचांगaster arbitration */
#घोषणा VDS_PODMODE		0x20	/* Go straight to POD mode */
#घोषणा VDS_NO_DIAGS		0x10	/* Don't run any diags after BM arb */
#घोषणा VDS_DEFAULTS		0x08	/* Use शेष environment values */
#घोषणा VDS_NOMEMCLEAR		0x04	/* Don't run mem cfg code */
#घोषणा VDS_2ND_IO4		0x02	/* Boot from the second IO4 */
#घोषणा VDS_DEBUG_PROM		0x01	/* Prपूर्णांक PROM debugging messages */

/* बाह्यal declarations of Linux kernel functions. */

बाह्य lboard_t *find_lboard(lboard_t *start, अचिन्हित अक्षर type);
बाह्य klinfo_t *find_component(lboard_t *brd, klinfo_t *kli, अचिन्हित अक्षर type);
बाह्य klinfo_t *find_first_component(lboard_t *brd, अचिन्हित अक्षर type);
बाह्य lboard_t *find_lboard_class(lboard_t *start, अचिन्हित अक्षर brd_class);

#पूर्ण_अगर /* _ASM_SN_KLCONFIG_H */
