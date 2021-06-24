<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * ARC firmware पूर्णांकerface defines.
 *
 * Copyright (C) 1996 David S. Miller (davem@davemloft.net)
 * Copyright (C) 1999, 2001 Ralf Baechle (ralf@gnu.org)
 * Copyright (C) 1999 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SGIARCS_H
#घोषणा _ASM_SGIARCS_H

#समावेश <linux/kernel.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/fw/arc/types.h>

/* Various ARCS error codes. */
#घोषणा PROM_ESUCCESS			0x00
#घोषणा PROM_E2BIG			0x01
#घोषणा PROM_EACCESS			0x02
#घोषणा PROM_EAGAIN			0x03
#घोषणा PROM_EBADF			0x04
#घोषणा PROM_EBUSY			0x05
#घोषणा PROM_EFAULT			0x06
#घोषणा PROM_EINVAL			0x07
#घोषणा PROM_EIO			0x08
#घोषणा PROM_EISसूची			0x09
#घोषणा PROM_EMखाता			0x0a
#घोषणा PROM_EMLINK			0x0b
#घोषणा PROM_ENAMETOOLONG		0x0c
#घोषणा PROM_ENODEV			0x0d
#घोषणा PROM_ENOENT			0x0e
#घोषणा PROM_ENOEXEC			0x0f
#घोषणा PROM_ENOMEM			0x10
#घोषणा PROM_ENOSPC			0x11
#घोषणा PROM_ENOTसूची			0x12
#घोषणा PROM_ENOTTY			0x13
#घोषणा PROM_ENXIO			0x14
#घोषणा PROM_EROFS			0x15
/* SGI ARCS specअगरic त्रुटि_सं's. */
#घोषणा PROM_EADDRNOTAVAIL		0x1f
#घोषणा PROM_ETIMEDOUT			0x20
#घोषणा PROM_ECONNABORTED		0x21
#घोषणा PROM_ENOCONNECT			0x22

/* Device classes, types, and identअगरiers क्रम prom
 * device inventory queries.
 */
क्रमागत linux_devclass अणु
	प्रणाली, processor, cache, adapter, controller, peripheral, memory
पूर्ण;

क्रमागत linux_devtypes अणु
	/* Generic stuff. */
	Arc, Cpu, Fpu,

	/* Primary insn and data caches. */
	picache, pdcache,

	/* Secondary insn, data, and combined caches. */
	sicache, sdcache, sccache,

	memdev, eisa_adapter, tc_adapter, scsi_adapter, dti_adapter,
	multअगरunc_adapter, dsk_controller, tp_controller, cdrom_controller,
	worm_controller, serial_controller, net_controller, disp_controller,
	parallel_controller, ptr_controller, kbd_controller, audio_controller,
	misc_controller, disk_peripheral, flpy_peripheral, tp_peripheral,
	modem_peripheral, monitor_peripheral, prपूर्णांकer_peripheral,
	ptr_peripheral, kbd_peripheral, term_peripheral, line_peripheral,
	net_peripheral, misc_peripheral, anon
पूर्ण;

क्रमागत linux_identअगरier अणु
	bogus, ronly, removable, consin, consout, input, output
पूर्ण;

/* A prom device tree component. */
काष्ठा linux_component अणु
	क्रमागत linux_devclass	class;	/* node class */
	क्रमागत linux_devtypes	type;	/* node type */
	क्रमागत linux_identअगरier	अगरlags; /* node flags */
	USHORT			vers;	/* node version */
	USHORT			rev;	/* node revision */
	ULONG			key;	/* completely magic */
	ULONG			amask;	/* XXX affinity mask??? */
	ULONG			cdsize; /* size of configuration data */
	ULONG			ilen;	/* length of string identअगरier */
	_PULONG			iname;	/* string identअगरier */
पूर्ण;
प्रकार काष्ठा linux_component pcomponent;

काष्ठा linux_sysid अणु
	अक्षर vend[8], prod[8];
पूर्ण;

/* ARCS prom memory descriptors. */
क्रमागत arcs_memtypes अणु
	arcs_eblock,  /* exception block */
	arcs_rvpage,  /* ARCS romvec page */
	arcs_fcontig, /* Contiguous and मुक्त */
	arcs_मुक्त,    /* Generic मुक्त memory */
	arcs_bmem,    /* Borken memory, करोn't use */
	arcs_prog,    /* A loaded program resides here */
	arcs_aपंचांगp,    /* ARCS temporary storage area, wish Sparc OpenBoot told this */
	arcs_aperm,   /* ARCS permanent storage... */
पूर्ण;

/* ARC has slightly dअगरferent types than ARCS */
क्रमागत arc_memtypes अणु
	arc_eblock,  /* exception block */
	arc_rvpage,  /* romvec page */
	arc_मुक्त,    /* Generic मुक्त memory */
	arc_bmem,    /* Borken memory, करोn't use */
	arc_prog,    /* A loaded program resides here */
	arc_aपंचांगp,    /* temporary storage area */
	arc_aperm,   /* permanent storage */
	arc_fcontig, /* Contiguous and मुक्त */
पूर्ण;

जोड़ linux_memtypes अणु
    क्रमागत arcs_memtypes arcs;
    क्रमागत arc_memtypes arc;
पूर्ण;

काष्ठा linux_mdesc अणु
	जोड़ linux_memtypes type;
	ULONG base;
	ULONG pages;
पूर्ण;

/* Time of day descriptor. */
काष्ठा linux_tinfo अणु
	अचिन्हित लघु yr;
	अचिन्हित लघु mnth;
	अचिन्हित लघु day;
	अचिन्हित लघु hr;
	अचिन्हित लघु min;
	अचिन्हित लघु sec;
	अचिन्हित लघु msec;
पूर्ण;

/* ARCS भव dirents. */
काष्ठा linux_vdirent अणु
	ULONG namelen;
	अचिन्हित अक्षर attr;
	अक्षर fname[32]; /* XXX empirical, should be a define */
पूर्ण;

/* Other stuff क्रम files. */
क्रमागत linux_omode अणु
	rकरोnly, wronly, rdwr, wronly_creat, rdwr_creat,
	wronly_ssede, rdwr_ssede, dirent, dirent_creat
पूर्ण;

क्रमागत linux_seekmode अणु
	असलolute, relative
पूर्ण;

क्रमागत linux_mountops अणु
	media_load, media_unload
पूर्ण;

/* This prom has a bolixed design. */
काष्ठा linux_bigपूर्णांक अणु
#अगर_घोषित __MIPSEL__
	u32 lo;
	s32 hi;
#अन्यथा /* !(__MIPSEL__) */
	s32 hi;
	u32 lo;
#पूर्ण_अगर
पूर्ण;

काष्ठा linux_finfo अणु
	काष्ठा linux_bigपूर्णांक   begin;
	काष्ठा linux_bigपूर्णांक   end;
	काष्ठा linux_bigपूर्णांक   cur;
	क्रमागत linux_devtypes   dtype;
	अचिन्हित दीर्घ	      namelen;
	अचिन्हित अक्षर	      attr;
	अक्षर		      name[32]; /* XXX empirical, should be define */
पूर्ण;

/* This describes the vector containing function poपूर्णांकers to the ARC
   firmware functions.	*/
काष्ठा linux_romvec अणु
	LONG	load;			/* Load an executable image. */
	LONG	invoke;			/* Invoke a standaदीर्घ image. */
	LONG	exec;			/* Load and begin execution of a
					   standalone image. */
	LONG	halt;			/* Halt the machine. */
	LONG	pकरोwn;			/* Power करोwn the machine. */
	LONG	restart;		/* XXX soft reset??? */
	LONG	reboot;			/* Reboot the machine. */
	LONG	imode;			/* Enter PROM पूर्णांकeractive mode. */
	LONG	_unused1;		/* Was ReturnFromMain(). */

	/* PROM device tree पूर्णांकerface. */
	LONG	next_component;
	LONG	child_component;
	LONG	parent_component;
	LONG	component_data;
	LONG	child_add;
	LONG	comp_del;
	LONG	component_by_path;

	/* Misc. stuff. */
	LONG	cfg_save;
	LONG	get_sysid;

	/* Probing क्रम memory. */
	LONG	get_mdesc;
	LONG	_unused2;		/* was Signal() */

	LONG	get_tinfo;
	LONG	get_rसमय;

	/* File type operations. */
	LONG	get_vdirent;
	LONG	खोलो;
	LONG	बंद;
	LONG	पढ़ो;
	LONG	get_rstatus;
	LONG	ग_लिखो;
	LONG	seek;
	LONG	mount;

	/* Dealing with firmware environment variables. */
	LONG	get_evar;
	LONG	set_evar;

	LONG	get_finfo;
	LONG	set_finfo;

	/* Miscellaneous. */
	LONG	cache_flush;
	LONG	TestUnicodeCharacter;		/* ARC; not sure अगर ARCS too */
	LONG	GetDisplayStatus;
पूर्ण;

/* The SGI ARCS parameter block is in a fixed location क्रम standalone
 * programs to access PROM facilities easily.
 */
प्रकार काष्ठा _SYSTEM_PARAMETER_BLOCK अणु
	ULONG			magic;		/* magic cookie */
#घोषणा PROMBLOCK_MAGIC	     0x53435241

	ULONG			len;		/* length of parm block */
	USHORT			ver;		/* ARCS firmware version */
	USHORT			rev;		/* ARCS firmware revision */
	_PLONG			rs_block;	/* Restart block. */
	_PLONG			dbg_block;	/* Debug block. */
	_PLONG			gevect;		/* XXX General vector??? */
	_PLONG			utlbvect;	/* XXX UTLB vector??? */
	ULONG			rveclen;	/* Size of romvec काष्ठा. */
	_PVOID			romvec;		/* Function पूर्णांकerface. */
	ULONG			pveclen;	/* Length of निजी vector. */
	_PVOID			pvector;	/* Private vector. */
	ULONG			adap_cnt;	/* Adapter count. */
	ULONG			adap_typ0;	/* First adapter type. */
	ULONG			adap_vcnt0;	/* Adapter 0 vector count. */
	_PVOID			adap_vector;	/* Adapter 0 vector ptr. */
	ULONG			adap_typ1;	/* Second adapter type. */
	ULONG			adap_vcnt1;	/* Adapter 1 vector count. */
	_PVOID			adap_vector1;	/* Adapter 1 vector ptr. */
	/* More adapter vectors go here... */
पूर्ण SYSTEM_PARAMETER_BLOCK, *PSYSTEM_PARAMETER_BLOCK;

#घोषणा PROMBLOCK ((PSYSTEM_PARAMETER_BLOCK) (पूर्णांक)0xA0001000)
#घोषणा ROMVECTOR ((काष्ठा linux_romvec *) (दीर्घ)(PROMBLOCK)->romvec)

/* Cache layout parameter block. */
जोड़ linux_cache_key अणु
	काष्ठा param अणु
#अगर_घोषित __MIPSEL__
		अचिन्हित लघु size;
		अचिन्हित अक्षर lsize;
		अचिन्हित अक्षर bsize;
#अन्यथा /* !(__MIPSEL__) */
		अचिन्हित अक्षर bsize;
		अचिन्हित अक्षर lsize;
		अचिन्हित लघु size;
#पूर्ण_अगर
	पूर्ण info;
	अचिन्हित दीर्घ allinfo;
पूर्ण;

/* Configuration data. */
काष्ठा linux_cdata अणु
	अक्षर *name;
	पूर्णांक mlen;
	क्रमागत linux_devtypes type;
पूर्ण;

/* Common SGI ARCS firmware file descriptors. */
#घोषणा SGIPROM_STDIN	  0
#घोषणा SGIPROM_STDOUT	  1

/* Common SGI ARCS firmware file types. */
#घोषणा SGIPROM_ROखाता	  0x01	/* पढ़ो-only file */
#घोषणा SGIPROM_Hखाता	  0x02	/* hidden file */
#घोषणा SGIPROM_Sखाता	  0x04	/* System file */
#घोषणा SGIPROM_Aखाता	  0x08	/* Archive file */
#घोषणा SGIPROM_Dखाता	  0x10	/* Directory file */
#घोषणा SGIPROM_DELखाता	  0x20	/* Deleted file */

/* SGI ARCS boot record inक्रमmation. */
काष्ठा sgi_partition अणु
	अचिन्हित अक्षर flag;
#घोषणा SGIPART_UNUSED 0x00
#घोषणा SGIPART_ACTIVE 0x80

	अचिन्हित अक्षर shead, ssect, scyl; /* unused */
	अचिन्हित अक्षर systype; /* OS type, Irix or NT */
	अचिन्हित अक्षर ehead, esect, ecyl; /* unused */
	अचिन्हित अक्षर rsect0, rsect1, rsect2, rsect3;
	अचिन्हित अक्षर tsect0, tsect1, tsect2, tsect3;
पूर्ण;

#घोषणा SGIBBLOCK_MAGIC	  0xaa55
#घोषणा SGIBBLOCK_MAXPART 0x0004

काष्ठा sgi_bootblock अणु
	अचिन्हित अक्षर _unused[446];
	काष्ठा sgi_partition partitions[SGIBBLOCK_MAXPART];
	अचिन्हित लघु magic;
पूर्ण;

/* BIOS parameter block. */
काष्ठा sgi_bparm_block अणु
	अचिन्हित लघु bytes_sect;    /* bytes per sector */
	अचिन्हित अक्षर  sect_clust;    /* sectors per cluster */
	अचिन्हित लघु sect_resv;     /* reserved sectors */
	अचिन्हित अक्षर  nfats;	      /* # of allocation tables */
	अचिन्हित लघु nroot_dirents; /* # of root directory entries */
	अचिन्हित लघु sect_volume;   /* sectors in volume */
	अचिन्हित अक्षर  media_type;    /* media descriptor */
	अचिन्हित लघु sect_fat;      /* sectors per allocation table */
	अचिन्हित लघु sect_track;    /* sectors per track */
	अचिन्हित लघु nheads;	      /* # of heads */
	अचिन्हित लघु nhsects;	      /* # of hidden sectors */
पूर्ण;

काष्ठा sgi_bsector अणु
	अचिन्हित अक्षर	jmpinfo[3];
	अचिन्हित अक्षर	manuf_name[8];
	काष्ठा sgi_bparm_block info;
पूर्ण;

/* Debugging block used with SGI symmon symbolic debugger. */
#घोषणा SMB_DEBUG_MAGIC	  0xfeeddead
काष्ठा linux_smonblock अणु
	अचिन्हित दीर्घ	magic;
	व्योम		(*handler)(व्योम);  /* Breakpoपूर्णांक routine. */
	अचिन्हित दीर्घ	dtable_base;	   /* Base addr of dbg table. */
	पूर्णांक		(*म_लिखो)(स्थिर अक्षर *fmt, ...);
	अचिन्हित दीर्घ	btable_base;	   /* Breakpoपूर्णांक table. */
	अचिन्हित दीर्घ	mpflushreqs;	   /* SMP cache flush request list. */
	अचिन्हित दीर्घ	ntab;		   /* Name table. */
	अचिन्हित दीर्घ	stab;		   /* Symbol table. */
	पूर्णांक		smax;		   /* Max # of symbols. */
पूर्ण;

/*
 * Macros क्रम calling a 32-bit ARC implementation from 64-bit code
 */

#अगर defined(CONFIG_64BIT) && defined(CONFIG_FW_ARC32)

बाह्य दीर्घ call_o32(दीर्घ vec, व्योम *stack, ...);

बाह्य u64 o32_stk[4096];
#घोषणा O32_STK	(&o32_stk[ARRAY_SIZE(o32_stk)])

#घोषणा ARC_CALL0(dest)							\
(अणु	दीर्घ __res;							\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK);				\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL1(dest, a1)						\
(अणु	दीर्घ __res;							\
	पूर्णांक  __a1 = (पूर्णांक) (दीर्घ) (a1);					\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK, __a1);				\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL2(dest, a1, a2)						\
(अणु	दीर्घ __res;							\
	पूर्णांक  __a1 = (पूर्णांक) (दीर्घ) (a1);					\
	पूर्णांक  __a2 = (पूर्णांक) (दीर्घ) (a2);					\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK, __a1, __a2);			\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL3(dest, a1, a2, a3)					\
(अणु	दीर्घ __res;							\
	पूर्णांक  __a1 = (पूर्णांक) (दीर्घ) (a1);					\
	पूर्णांक  __a2 = (पूर्णांक) (दीर्घ) (a2);					\
	पूर्णांक  __a3 = (पूर्णांक) (दीर्घ) (a3);					\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK, __a1, __a2, __a3);		\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL4(dest, a1, a2, a3, a4)					\
(अणु	दीर्घ __res;							\
	पूर्णांक  __a1 = (पूर्णांक) (दीर्घ) (a1);					\
	पूर्णांक  __a2 = (पूर्णांक) (दीर्घ) (a2);					\
	पूर्णांक  __a3 = (पूर्णांक) (दीर्घ) (a3);					\
	पूर्णांक  __a4 = (पूर्णांक) (दीर्घ) (a4);					\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK, __a1, __a2, __a3, __a4);	\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL5(dest, a1, a2, a3, a4, a5)				\
(अणु	दीर्घ __res;							\
	पूर्णांक  __a1 = (पूर्णांक) (दीर्घ) (a1);					\
	पूर्णांक  __a2 = (पूर्णांक) (दीर्घ) (a2);					\
	पूर्णांक  __a3 = (पूर्णांक) (दीर्घ) (a3);					\
	पूर्णांक  __a4 = (पूर्णांक) (दीर्घ) (a4);					\
	पूर्णांक  __a5 = (पूर्णांक) (दीर्घ) (a5);					\
	दीर्घ __vec = (दीर्घ) romvec->dest;				\
	__res = call_o32(__vec, O32_STK, __a1, __a2, __a3, __a4, __a5);	\
	__res;								\
पूर्ण)

#पूर्ण_अगर /* defined(CONFIG_64BIT) && defined(CONFIG_FW_ARC32) */

#अगर (defined(CONFIG_32BIT) && defined(CONFIG_FW_ARC32)) ||		\
    (defined(CONFIG_64BIT) && defined(CONFIG_FW_ARC64))

#घोषणा ARC_CALL0(dest)							\
(अणु	दीर्घ __res;							\
	दीर्घ (*__vec)(व्योम) = (व्योम *) romvec->dest;			\
									\
	__res = __vec();						\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL1(dest, a1)						\
(अणु	दीर्घ __res;							\
	दीर्घ __a1 = (दीर्घ) (a1);					\
	दीर्घ (*__vec)(दीर्घ) = (व्योम *) romvec->dest;			\
									\
	__res = __vec(__a1);						\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL2(dest, a1, a2)						\
(अणु	दीर्घ __res;							\
	दीर्घ __a1 = (दीर्घ) (a1);					\
	दीर्घ __a2 = (दीर्घ) (a2);					\
	दीर्घ (*__vec)(दीर्घ, दीर्घ) = (व्योम *) romvec->dest;		\
									\
	__res = __vec(__a1, __a2);					\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL3(dest, a1, a2, a3)					\
(अणु	दीर्घ __res;							\
	दीर्घ __a1 = (दीर्घ) (a1);					\
	दीर्घ __a2 = (दीर्घ) (a2);					\
	दीर्घ __a3 = (दीर्घ) (a3);					\
	दीर्घ (*__vec)(दीर्घ, दीर्घ, दीर्घ) = (व्योम *) romvec->dest;	\
									\
	__res = __vec(__a1, __a2, __a3);				\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL4(dest, a1, a2, a3, a4)					\
(अणु	दीर्घ __res;							\
	दीर्घ __a1 = (दीर्घ) (a1);					\
	दीर्घ __a2 = (दीर्घ) (a2);					\
	दीर्घ __a3 = (दीर्घ) (a3);					\
	दीर्घ __a4 = (दीर्घ) (a4);					\
	दीर्घ (*__vec)(दीर्घ, दीर्घ, दीर्घ, दीर्घ) = (व्योम *) romvec->dest;	\
									\
	__res = __vec(__a1, __a2, __a3, __a4);				\
	__res;								\
पूर्ण)

#घोषणा ARC_CALL5(dest, a1, a2, a3, a4, a5)				\
(अणु	दीर्घ __res;							\
	दीर्घ __a1 = (दीर्घ) (a1);					\
	दीर्घ __a2 = (दीर्घ) (a2);					\
	दीर्घ __a3 = (दीर्घ) (a3);					\
	दीर्घ __a4 = (दीर्घ) (a4);					\
	दीर्घ __a5 = (दीर्घ) (a5);					\
	दीर्घ (*__vec)(दीर्घ, दीर्घ, दीर्घ, दीर्घ, दीर्घ);			\
	__vec = (व्योम *) romvec->dest;					\
									\
	__res = __vec(__a1, __a2, __a3, __a4, __a5);			\
	__res;								\
पूर्ण)
#पूर्ण_अगर /* both kernel and ARC either 32-bit or 64-bit */

#पूर्ण_अगर /* _ASM_SGIARCS_H */
