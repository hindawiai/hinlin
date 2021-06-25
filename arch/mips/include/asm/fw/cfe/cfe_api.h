<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2000, 2001, 2002 Broadcom Corporation
 */
/*
 * Broadcom Common Firmware Environment (CFE)
 *
 * This file contains declarations क्रम करोing callbacks to
 * cfe from an application.  It should be the only header
 * needed by the application to use this library
 *
 * Authors:  Mitch Lichtenberg, Chris Demetriou
 */
#अगर_अघोषित CFE_API_H
#घोषणा CFE_API_H

#समावेश <linux/types.h>
#समावेश <linux/माला.स>

प्रकार दीर्घ पूर्णांकptr_t;


/*
 * Constants
 */

/* Seal indicating CFE's presence, passed to user program. */
#घोषणा CFE_EPTSEAL 0x43464531

#घोषणा CFE_MI_RESERVED 0	/* memory is reserved, करो not use */
#घोषणा CFE_MI_AVAILABLE 1	/* memory is available */

#घोषणा CFE_FLG_WARMSTART     0x00000001
#घोषणा CFE_FLG_FULL_ARENA    0x00000001
#घोषणा CFE_FLG_ENV_PERMANENT 0x00000001

#घोषणा CFE_CPU_CMD_START 1
#घोषणा CFE_CPU_CMD_STOP 0

#घोषणा CFE_STDHANDLE_CONSOLE	0

#घोषणा CFE_DEV_NETWORK		1
#घोषणा CFE_DEV_DISK		2
#घोषणा CFE_DEV_FLASH		3
#घोषणा CFE_DEV_SERIAL		4
#घोषणा CFE_DEV_CPU		5
#घोषणा CFE_DEV_NVRAM		6
#घोषणा CFE_DEV_CLOCK		7
#घोषणा CFE_DEV_OTHER		8
#घोषणा CFE_DEV_MASK		0x0F

#घोषणा CFE_CACHE_FLUSH_D	1
#घोषणा CFE_CACHE_INVAL_I	2
#घोषणा CFE_CACHE_INVAL_D	4
#घोषणा CFE_CACHE_INVAL_L2	8

#घोषणा CFE_FWI_64BIT		0x00000001
#घोषणा CFE_FWI_32BIT		0x00000002
#घोषणा CFE_FWI_RELOC		0x00000004
#घोषणा CFE_FWI_UNCACHED	0x00000008
#घोषणा CFE_FWI_MULTICPU	0x00000010
#घोषणा CFE_FWI_FUNCSIM		0x00000020
#घोषणा CFE_FWI_RTLSIM		0x00000040

प्रकार काष्ठा अणु
	पूर्णांक64_t fwi_version;		/* major, minor, eco version */
	पूर्णांक64_t fwi_totalmem;		/* total installed mem */
	पूर्णांक64_t fwi_flags;		/* various flags */
	पूर्णांक64_t fwi_boardid;		/* board ID */
	पूर्णांक64_t fwi_bootarea_va;	/* VA of boot area */
	पूर्णांक64_t fwi_bootarea_pa;	/* PA of boot area */
	पूर्णांक64_t fwi_bootarea_size;	/* size of boot area */
पूर्ण cfe_fwinfo_t;


/*
 * Defines and prototypes क्रम functions which take no arguments.
 */
पूर्णांक64_t cfe_getticks(व्योम);

/*
 * Defines and prototypes क्रम the rest of the functions.
 */
पूर्णांक cfe_बंद(पूर्णांक handle);
पूर्णांक cfe_cpu_start(पूर्णांक cpu, व्योम (*fn) (व्योम), दीर्घ sp, दीर्घ gp, दीर्घ a1);
पूर्णांक cfe_cpu_stop(पूर्णांक cpu);
पूर्णांक cfe_क्रमागतenv(पूर्णांक idx, अक्षर *name, पूर्णांक namelen, अक्षर *val, पूर्णांक vallen);
पूर्णांक cfe_क्रमागतmem(पूर्णांक idx, पूर्णांक flags, uपूर्णांक64_t * start, uपूर्णांक64_t * length,
		uपूर्णांक64_t * type);
पूर्णांक cfe_निकास(पूर्णांक warm, पूर्णांक status);
पूर्णांक cfe_flushcache(पूर्णांक flg);
पूर्णांक cfe_getdevinfo(अक्षर *name);
पूर्णांक cfe_दो_पर्या(अक्षर *name, अक्षर *dest, पूर्णांक destlen);
पूर्णांक cfe_getfwinfo(cfe_fwinfo_t * info);
पूर्णांक cfe_माला_लोtdhandle(पूर्णांक flg);
पूर्णांक cfe_init(uपूर्णांक64_t handle, uपूर्णांक64_t ept);
पूर्णांक cfe_inpstat(पूर्णांक handle);
पूर्णांक cfe_ioctl(पूर्णांक handle, अचिन्हित पूर्णांक ioctlnum, अचिन्हित अक्षर *buffer,
	      पूर्णांक length, पूर्णांक *retlen, uपूर्णांक64_t offset);
पूर्णांक cfe_खोलो(अक्षर *name);
पूर्णांक cfe_पढ़ो(पूर्णांक handle, अचिन्हित अक्षर *buffer, पूर्णांक length);
पूर्णांक cfe_पढ़ोblk(पूर्णांक handle, पूर्णांक64_t offset, अचिन्हित अक्षर *buffer,
		पूर्णांक length);
पूर्णांक cfe_setenv(अक्षर *name, अक्षर *val);
पूर्णांक cfe_ग_लिखो(पूर्णांक handle, स्थिर अक्षर *buffer, पूर्णांक length);
पूर्णांक cfe_ग_लिखोblk(पूर्णांक handle, पूर्णांक64_t offset, स्थिर अक्षर *buffer,
		 पूर्णांक length);

#पूर्ण_अगर				/* CFE_API_H */
