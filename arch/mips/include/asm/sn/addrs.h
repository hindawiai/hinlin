<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1992 - 1997, 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 1999, 2000 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_ADDRS_H
#घोषणा _ASM_SN_ADDRS_H


#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/smp.h>
#समावेश <linux/types.h>
#पूर्ण_अगर /* !__ASSEMBLY__ */

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/sn/klसूची.स>

#अगर defined(CONFIG_SGI_IP27)
#समावेश <यंत्र/sn/sn0/addrs.h>
#या_अगर defined(CONFIG_SGI_IP35)
#समावेश <यंत्र/sn/sn1/addrs.h>
#पूर्ण_अगर


#अगर_अघोषित __ASSEMBLY__

#घोषणा UINT64_CAST		(अचिन्हित दीर्घ)

#अन्यथा /* __ASSEMBLY__ */

#घोषणा UINT64_CAST

#पूर्ण_अगर /* __ASSEMBLY__ */


#घोषणा NASID_GET_META(_n)	((_n) >> NASID_LOCAL_BITS)
#अगर_घोषित CONFIG_SGI_IP27
#घोषणा NASID_GET_LOCAL(_n)	((_n) & 0xf)
#पूर्ण_अगर
#घोषणा NASID_MAKE(_m, _l)	(((_m) << NASID_LOCAL_BITS) | (_l))

#घोषणा NODE_ADDRSPACE_MASK	(NODE_ADDRSPACE_SIZE - 1)
#घोषणा TO_NODE_ADDRSPACE(_pa)	(UINT64_CAST (_pa) & NODE_ADDRSPACE_MASK)

#घोषणा CHANGE_ADDR_NASID(_pa, _nasid)	\
		((UINT64_CAST(_pa) & ~NASID_MASK) | \
		 (UINT64_CAST(_nasid) <<  NASID_SHFT))


/*
 * The following macros are used to index to the beginning of a specअगरic
 * node's address space.
 */

#घोषणा NODE_OFFSET(_n)		(UINT64_CAST (_n) << NODE_SIZE_BITS)

#घोषणा NODE_CAC_BASE(_n)	(CAC_BASE   + NODE_OFFSET(_n))
#घोषणा NODE_HSPEC_BASE(_n)	(HSPEC_BASE + NODE_OFFSET(_n))
#घोषणा NODE_IO_BASE(_n)	(IO_BASE    + NODE_OFFSET(_n))
#घोषणा NODE_MSPEC_BASE(_n)	(MSPEC_BASE + NODE_OFFSET(_n))
#घोषणा NODE_UNCAC_BASE(_n)	(UNCAC_BASE + NODE_OFFSET(_n))

#घोषणा TO_NODE(_n, _x)		(NODE_OFFSET(_n)     | ((_x)		   ))
#घोषणा TO_NODE_CAC(_n, _x)	(NODE_CAC_BASE(_n)   | ((_x) & TO_PHYS_MASK))
#घोषणा TO_NODE_UNCAC(_n, _x)	(NODE_UNCAC_BASE(_n) | ((_x) & TO_PHYS_MASK))
#घोषणा TO_NODE_MSPEC(_n, _x)	(NODE_MSPEC_BASE(_n) | ((_x) & TO_PHYS_MASK))
#घोषणा TO_NODE_HSPEC(_n, _x)	(NODE_HSPEC_BASE(_n) | ((_x) & TO_PHYS_MASK))


#घोषणा RAW_NODE_SWIN_BASE(nasid, widget)				\
	(NODE_IO_BASE(nasid) + (UINT64_CAST(widget) << SWIN_SIZE_BITS))

#घोषणा WIDGETID_GET(addr)	((अचिन्हित अक्षर)((addr >> SWIN_SIZE_BITS) & 0xff))

/*
 * The following definitions pertain to the IO special address
 * space.  They define the location of the big and little winकरोws
 * of any given node.
 */

#घोषणा SWIN_SIZE_BITS		24
#घोषणा SWIN_SIZE		(UINT64_CAST 1 << 24)
#घोषणा SWIN_SIZEMASK		(SWIN_SIZE - 1)
#घोषणा SWIN_WIDGET_MASK	0xF

/*
 * Convert smallwinकरोw address to xtalk address.
 *
 * 'addr' can be physical or भव address, but will be converted
 * to Xtalk address in the range 0 -> SWINZ_SIZEMASK
 */
#घोषणा SWIN_WIDGETADDR(addr)	((addr) & SWIN_SIZEMASK)
#घोषणा SWIN_WIDGETNUM(addr)	(((addr)  >> SWIN_SIZE_BITS) & SWIN_WIDGET_MASK)
/*
 * Verअगरy अगर addr beदीर्घs to small winकरोw address on node with "nasid"
 *
 *
 * NOTE: "addr" is expected to be XKPHYS address, and NOT physical
 * address
 *
 *
 */
#घोषणा NODE_SWIN_ADDR(nasid, addr)	\
		(((addr) >= NODE_SWIN_BASE(nasid, 0))  && \
		 ((addr) <  (NODE_SWIN_BASE(nasid, HUB_NUM_WIDGET) + SWIN_SIZE)\
		 ))

/*
 * The following define the major position-independent aliases used
 * in SN.
 *	UALIAS -- 256MB in size, पढ़ोs in the UALIAS result in
 *			uncached references to the memory of the पढ़ोer's node.
 *	CPU_UALIAS -- 128kb in size, the bottom part of UALIAS is flipped
 *			depending on which CPU करोes the access to provide
 *			all CPUs with unique uncached memory at low addresses.
 *	LBOOT  -- 256MB in size, पढ़ोs in the LBOOT area result in
 *			uncached references to the local hub's boot prom and
 *			other directory-bus connected devices.
 *	IALIAS -- 8MB in size, पढ़ोs in the IALIAS result in uncached
 *			references to the local hub's रेजिस्टरs.
 */

#घोषणा UALIAS_BASE		HSPEC_BASE
#घोषणा UALIAS_SIZE		0x10000000	/* 256 Megabytes */
#घोषणा UALIAS_LIMIT		(UALIAS_BASE + UALIAS_SIZE)

/*
 * The bottom of ualias space is flipped depending on whether you're
 * processor 0 or 1 within a node.
 */
#अगर_घोषित CONFIG_SGI_IP27
#घोषणा UALIAS_FLIP_BASE	UALIAS_BASE
#घोषणा UALIAS_FLIP_SIZE	0x20000
#घोषणा UALIAS_FLIP_BIT		0x10000
#घोषणा UALIAS_FLIP_ADDR(_x)	(cputoslice(smp_processor_id()) ? \
				 (_x) ^ UALIAS_FLIP_BIT : (_x))

#घोषणा LBOOT_BASE		(HSPEC_BASE + 0x10000000)
#घोषणा LBOOT_SIZE		0x10000000
#घोषणा LBOOT_LIMIT		(LBOOT_BASE + LBOOT_SIZE)
#घोषणा LBOOT_STRIDE		0		/* IP27 has only one CPU PROM */

#पूर्ण_अगर

#घोषणा HUB_REGISTER_WIDGET	1
#घोषणा IALIAS_BASE		NODE_SWIN_BASE(0, HUB_REGISTER_WIDGET)
#घोषणा IALIAS_SIZE		0x800000	/* 8 Megabytes */
#घोषणा IS_IALIAS(_a)		(((_a) >= IALIAS_BASE) &&		\
				 ((_a) < (IALIAS_BASE + IALIAS_SIZE)))

/*
 * Macro क्रम referring to Hub's RBOOT space
 */

#अगर_घोषित CONFIG_SGI_IP27
#घोषणा RBOOT_SIZE		0x10000000	/* 256 Megabytes */
#घोषणा NODE_RBOOT_BASE(_n)	(NODE_HSPEC_BASE(_n) + 0x30000000)
#घोषणा NODE_RBOOT_LIMIT(_n)	(NODE_RBOOT_BASE(_n) + RBOOT_SIZE)

#पूर्ण_अगर

/*
 * Macros क्रम referring the Hub's back करोor space
 *
 *   These macros correctly process addresses in any node's space.
 *   WARNING: They won't work in assembler.
 *
 *   BDसूची_ENTRY_LO वापसs the address of the low द्विगुन-word of the dir
 *		    entry corresponding to a physical (Cac or Uncac) address.
 *   BDसूची_ENTRY_HI वापसs the address of the high द्विगुन-word of the entry.
 *   BDPRT_ENTRY    वापसs the address of the द्विगुन-word protection entry
 *		    corresponding to the page containing the physical address.
 *   BDPRT_ENTRY_S  Stores the value पूर्णांकo the protection entry.
 *   BDPRT_ENTRY_L  Load the value from the protection entry.
 *   BDECC_ENTRY    वापसs the address of the ECC byte corresponding to a
 *		    द्विगुन-word at a specअगरied physical address.
 *   BDECC_ENTRY_H  वापसs the address of the two ECC bytes corresponding to a
 *		    quad-word at a specअगरied physical address.
 */
#घोषणा NODE_BDOOR_BASE(_n)	(NODE_HSPEC_BASE(_n) + (NODE_ADDRSPACE_SIZE/2))

#घोषणा NODE_BDECC_BASE(_n)	(NODE_BDOOR_BASE(_n))
#घोषणा NODE_BDसूची_BASE(_n)	(NODE_BDOOR_BASE(_n) + (NODE_ADDRSPACE_SIZE/4))
#अगर_घोषित CONFIG_SGI_IP27
#घोषणा BDसूची_ENTRY_LO(_pa)	((HSPEC_BASE +				      \
				  NODE_ADDRSPACE_SIZE * 3 / 4 +		      \
				  0x200)				    | \
				 UINT64_CAST(_pa)	 & NASID_MASK	    | \
				 UINT64_CAST(_pa) >> 2 & BDसूची_UPPER_MASK  | \
				 UINT64_CAST(_pa) >> 3 & 0x1f << 4)

#घोषणा BDसूची_ENTRY_HI(_pa)	((HSPEC_BASE +				      \
				  NODE_ADDRSPACE_SIZE * 3 / 4 +		      \
				  0x208)				    | \
				 UINT64_CAST(_pa)	 & NASID_MASK	    | \
				 UINT64_CAST(_pa) >> 2 & BDसूची_UPPER_MASK  | \
				 UINT64_CAST(_pa) >> 3 & 0x1f << 4)

#घोषणा BDPRT_ENTRY(_pa, _rgn)	((HSPEC_BASE +				      \
				  NODE_ADDRSPACE_SIZE * 3 / 4)		    | \
				 UINT64_CAST(_pa)	 & NASID_MASK	    | \
				 UINT64_CAST(_pa) >> 2 & BDसूची_UPPER_MASK  | \
				 (_rgn) << 3)
#घोषणा BDPRT_ENTRY_ADDR(_pa, _rgn) (BDPRT_ENTRY((_pa), (_rgn)))
#घोषणा BDPRT_ENTRY_S(_pa, _rgn, _val) (*(__psअचिन्हित_t *)BDPRT_ENTRY((_pa), (_rgn))=(_val))
#घोषणा BDPRT_ENTRY_L(_pa, _rgn)	(*(__psअचिन्हित_t *)BDPRT_ENTRY((_pa), (_rgn)))

#घोषणा BDECC_ENTRY(_pa)	((HSPEC_BASE +				      \
				  NODE_ADDRSPACE_SIZE / 2)		    | \
				 UINT64_CAST(_pa)	 & NASID_MASK	    | \
				 UINT64_CAST(_pa) >> 2 & BDECC_UPPER_MASK  | \
				 UINT64_CAST(_pa) >> 3 & 3)

/*
 * Macro to convert a back करोor directory or protection address पूर्णांकo the
 *   raw physical address of the associated cache line or protection page.
 */
#घोषणा BDADDR_IS_सूची(_ba)	((UINT64_CAST  (_ba) & 0x200) != 0)
#घोषणा BDADDR_IS_PRT(_ba)	((UINT64_CAST  (_ba) & 0x200) == 0)

#घोषणा BDसूची_TO_MEM(_ba)	(UINT64_CAST (_ba) & NASID_MASK		   | \
				 (UINT64_CAST(_ba) & BDसूची_UPPER_MASK)<<2  | \
				 (UINT64_CAST(_ba) & 0x1f << 4) << 3)

#घोषणा BDPRT_TO_MEM(_ba)	(UINT64_CAST (_ba) & NASID_MASK	    | \
				 (UINT64_CAST(_ba) & BDसूची_UPPER_MASK)<<2)

#घोषणा BDECC_TO_MEM(_ba)	(UINT64_CAST (_ba) & NASID_MASK	    | \
				 (UINT64_CAST(_ba) & BDECC_UPPER_MASK)<<2  | \
				 (UINT64_CAST(_ba) & 3) << 3)
#पूर्ण_अगर /* CONFIG_SGI_IP27 */


/*
 * The following macros produce the correct base भव address क्रम
 * the hub रेजिस्टरs.  The LOCAL_HUB_* macros produce the appropriate
 * address क्रम the local रेजिस्टरs.  The REMOTE_HUB_* macro produce
 * the address क्रम the specअगरied hub's रेजिस्टरs.  The पूर्णांकent is
 * that the appropriate PI, MD, NI, or II रेजिस्टर would be substituted
 * क्रम _x.
 */

/*
 * WARNING:
 *	When certain Hub chip workaround are defined, it's not sufficient
 *	to dereference the *_HUB_ADDR() macros.	 You should instead use
 *	HUB_L() and HUB_S() अगर you must deal with poपूर्णांकers to hub रेजिस्टरs.
 *	Otherwise, the recommended approach is to use *_HUB_L() and *_HUB_S().
 *	They're always safe.
 */
#घोषणा LOCAL_HUB_ADDR(_x)	(IALIAS_BASE + (_x))
#घोषणा REMOTE_HUB_ADDR(_n, _x) ((NODE_SWIN_BASE(_n, 1) + 0x800000 + (_x)))

#अगर_अघोषित __ASSEMBLY__

#घोषणा LOCAL_HUB_PTR(_x)	((u64 *)LOCAL_HUB_ADDR((_x)))
#घोषणा REMOTE_HUB_PTR(_n, _x)	((u64 *)REMOTE_HUB_ADDR((_n), (_x)))

#घोषणा LOCAL_HUB_L(_r)			__raw_पढ़ोq(LOCAL_HUB_PTR(_r))
#घोषणा LOCAL_HUB_S(_r, _d)		__raw_ग_लिखोq((_d), LOCAL_HUB_PTR(_r))
#घोषणा REMOTE_HUB_L(_n, _r)		__raw_पढ़ोq(REMOTE_HUB_PTR((_n), (_r)))
#घोषणा REMOTE_HUB_S(_n, _r, _d)	__raw_ग_लिखोq((_d),		\
						REMOTE_HUB_PTR((_n), (_r)))

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Software काष्ठाure locations -- permanently fixed
 *    See diagram in klसूची.स
 */

#घोषणा PHYS_RAMBASE		0x0
#घोषणा K0_RAMBASE		PHYS_TO_K0(PHYS_RAMBASE)

#घोषणा EX_HANDLER_OFFSET(slice) ((slice) << 16)
#घोषणा EX_HANDLER_ADDR(nasid, slice)					\
	PHYS_TO_K0(NODE_OFFSET(nasid) | EX_HANDLER_OFFSET(slice))
#घोषणा EX_HANDLER_SIZE		0x0400

#घोषणा EX_FRAME_OFFSET(slice)	((slice) << 16 | 0x400)
#घोषणा EX_FRAME_ADDR(nasid, slice)					\
	PHYS_TO_K0(NODE_OFFSET(nasid) | EX_FRAME_OFFSET(slice))
#घोषणा EX_FRAME_SIZE		0x0c00

#घोषणा ARCS_SPB_OFFSET		0x1000
#घोषणा ARCS_SPB_ADDR(nasid)						\
	PHYS_TO_K0(NODE_OFFSET(nasid) | ARCS_SPB_OFFSET)
#घोषणा ARCS_SPB_SIZE		0x0400

#घोषणा KLसूची_OFFSET		0x2000
#घोषणा KLसूची_ADDR(nasid)						\
	TO_NODE_UNCAC((nasid), KLसूची_OFFSET)
#घोषणा KLसूची_SIZE		0x0400


/*
 * Software काष्ठाure locations -- indirected through KLसूची
 *    See diagram in klसूची.स
 *
 * Important:	All low memory काष्ठाures must only be accessed
 *		uncached, except क्रम the symmon stacks.
 */

#घोषणा KLI_LAUNCH		0		/* Dir. entries */
#घोषणा KLI_KLCONFIG		1
#घोषणा KLI_NMI			2
#घोषणा KLI_GDA			3
#घोषणा KLI_FREEMEM		4
#घोषणा KLI_SYMMON_STK		5
#घोषणा KLI_PI_ERROR		6
#घोषणा KLI_KERN_VARS		7
#घोषणा KLI_KERN_XP		8
#घोषणा KLI_KERN_PARTID		9

#अगर_अघोषित __ASSEMBLY__

#घोषणा KLD_BASE(nasid)		((kldir_ent_t *) KLसूची_ADDR(nasid))
#घोषणा KLD_LAUNCH(nasid)	(KLD_BASE(nasid) + KLI_LAUNCH)
#घोषणा KLD_NMI(nasid)		(KLD_BASE(nasid) + KLI_NMI)
#घोषणा KLD_KLCONFIG(nasid)	(KLD_BASE(nasid) + KLI_KLCONFIG)
#घोषणा KLD_PI_ERROR(nasid)	(KLD_BASE(nasid) + KLI_PI_ERROR)
#घोषणा KLD_GDA(nasid)		(KLD_BASE(nasid) + KLI_GDA)
#घोषणा KLD_SYMMON_STK(nasid)	(KLD_BASE(nasid) + KLI_SYMMON_STK)
#घोषणा KLD_FREEMEM(nasid)	(KLD_BASE(nasid) + KLI_FREEMEM)
#घोषणा KLD_KERN_VARS(nasid)	(KLD_BASE(nasid) + KLI_KERN_VARS)
#घोषणा KLD_KERN_XP(nasid)	(KLD_BASE(nasid) + KLI_KERN_XP)
#घोषणा KLD_KERN_PARTID(nasid)	(KLD_BASE(nasid) + KLI_KERN_PARTID)

#घोषणा LAUNCH_OFFSET(nasid, slice)					\
	(KLD_LAUNCH(nasid)->offset +					\
	 KLD_LAUNCH(nasid)->stride * (slice))
#घोषणा LAUNCH_ADDR(nasid, slice)					\
	TO_NODE_UNCAC((nasid), LAUNCH_OFFSET(nasid, slice))
#घोषणा LAUNCH_SIZE(nasid)	KLD_LAUNCH(nasid)->size

#घोषणा SN_NMI_OFFSET(nasid, slice)					\
	(KLD_NMI(nasid)->offset +					\
	 KLD_NMI(nasid)->stride * (slice))
#घोषणा NMI_ADDR(nasid, slice)						\
	TO_NODE_UNCAC((nasid), SN_NMI_OFFSET(nasid, slice))
#घोषणा NMI_SIZE(nasid) KLD_NMI(nasid)->size

#घोषणा KLCONFIG_OFFSET(nasid)	KLD_KLCONFIG(nasid)->offset
#घोषणा KLCONFIG_ADDR(nasid)						\
	TO_NODE_UNCAC((nasid), KLCONFIG_OFFSET(nasid))
#घोषणा KLCONFIG_SIZE(nasid)	KLD_KLCONFIG(nasid)->size

#घोषणा GDA_ADDR(nasid)		KLD_GDA(nasid)->poपूर्णांकer
#घोषणा GDA_SIZE(nasid)		KLD_GDA(nasid)->size

#घोषणा SYMMON_STK_OFFSET(nasid, slice)					\
	(KLD_SYMMON_STK(nasid)->offset +				\
	 KLD_SYMMON_STK(nasid)->stride * (slice))
#घोषणा SYMMON_STK_STRIDE(nasid)	KLD_SYMMON_STK(nasid)->stride

#घोषणा SYMMON_STK_ADDR(nasid, slice)					\
	TO_NODE_CAC((nasid), SYMMON_STK_OFFSET(nasid, slice))

#घोषणा SYMMON_STK_SIZE(nasid)	KLD_SYMMON_STK(nasid)->stride

#घोषणा SYMMON_STK_END(nasid)	(SYMMON_STK_ADDR(nasid, 0) + KLD_SYMMON_STK(nasid)->size)

#घोषणा NODE_OFFSET_TO_K0(_nasid, _off)					\
	PHYS_TO_K0((NODE_OFFSET(_nasid) + (_off)) | CAC_BASE)
#घोषणा NODE_OFFSET_TO_K1(_nasid, _off)					\
	TO_UNCAC((NODE_OFFSET(_nasid) + (_off)) | UNCAC_BASE)

#घोषणा KERN_VARS_ADDR(nasid)	KLD_KERN_VARS(nasid)->poपूर्णांकer
#घोषणा KERN_VARS_SIZE(nasid)	KLD_KERN_VARS(nasid)->size

#पूर्ण_अगर /* !__ASSEMBLY__ */


#पूर्ण_अगर /* _ASM_SN_ADDRS_H */
