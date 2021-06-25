<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001, 2002 Broadcom Corporation
 */

/*
 *
 * Broadcom Common Firmware Environment (CFE)
 *
 * This module contains device function stubs (small routines to
 * call the standard "iocb" पूर्णांकerface entry poपूर्णांक to CFE).
 * There should be one routine here per iocb function call.
 *
 * Authors:  Mitch Lichtenberg, Chris Demetriou
 */

#समावेश <यंत्र/fw/cfe/cfe_api.h>
#समावेश "cfe_api_int.h"

/* Cast from a native poपूर्णांकer to a cfe_xptr_t and back.	 */
#घोषणा XPTR_FROM_NATIVE(n)	((cfe_xptr_t) (पूर्णांकptr_t) (n))
#घोषणा NATIVE_FROM_XPTR(x)	((व्योम *) (पूर्णांकptr_t) (x))

पूर्णांक cfe_iocb_dispatch(काष्ठा cfe_xiocb *xiocb);

/*
 * Declare the dispatch function with args of "intptr_t".
 * This makes sure whatever model we're compiling in
 * माला_दो the poपूर्णांकers in a single रेजिस्टर.  For example,
 * combining -mदीर्घ64 and -mips1 or -mips2 would lead to
 * trouble, since the handle and IOCB poपूर्णांकer will be
 * passed in two रेजिस्टरs each, and CFE expects one.
 */

अटल पूर्णांक (*cfe_dispfunc) (पूर्णांकptr_t handle, पूर्णांकptr_t xiocb);
अटल u64 cfe_handle;

पूर्णांक cfe_init(u64 handle, u64 ept)
अणु
	cfe_dispfunc = NATIVE_FROM_XPTR(ept);
	cfe_handle = handle;
	वापस 0;
पूर्ण

पूर्णांक cfe_iocb_dispatch(काष्ठा cfe_xiocb * xiocb)
अणु
	अगर (!cfe_dispfunc)
		वापस -1;
	वापस (*cfe_dispfunc) ((पूर्णांकptr_t) cfe_handle, (पूर्णांकptr_t) xiocb);
पूर्ण

पूर्णांक cfe_बंद(पूर्णांक handle)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_CLOSE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;

पूर्ण

पूर्णांक cfe_cpu_start(पूर्णांक cpu, व्योम (*fn) (व्योम), दीर्घ sp, दीर्घ gp, दीर्घ a1)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_CPUCTL;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_cpuctl);
	xiocb.plist.xiocb_cpuctl.cpu_number = cpu;
	xiocb.plist.xiocb_cpuctl.cpu_command = CFE_CPU_CMD_START;
	xiocb.plist.xiocb_cpuctl.gp_val = gp;
	xiocb.plist.xiocb_cpuctl.sp_val = sp;
	xiocb.plist.xiocb_cpuctl.a1_val = a1;
	xiocb.plist.xiocb_cpuctl.start_addr = (दीर्घ) fn;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_cpu_stop(पूर्णांक cpu)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_CPUCTL;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_cpuctl);
	xiocb.plist.xiocb_cpuctl.cpu_number = cpu;
	xiocb.plist.xiocb_cpuctl.cpu_command = CFE_CPU_CMD_STOP;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_क्रमागतenv(पूर्णांक idx, अक्षर *name, पूर्णांक namelen, अक्षर *val, पूर्णांक vallen)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_ENV_SET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_envbuf);
	xiocb.plist.xiocb_envbuf.क्रमागत_idx = idx;
	xiocb.plist.xiocb_envbuf.name_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_envbuf.name_length = namelen;
	xiocb.plist.xiocb_envbuf.val_ptr = XPTR_FROM_NATIVE(val);
	xiocb.plist.xiocb_envbuf.val_length = vallen;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक
cfe_क्रमागतmem(पूर्णांक idx, पूर्णांक flags, u64 *start, u64 *length, u64 *type)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_MEMENUM;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = flags;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_meminfo);
	xiocb.plist.xiocb_meminfo.mi_idx = idx;

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;

	*start = xiocb.plist.xiocb_meminfo.mi_addr;
	*length = xiocb.plist.xiocb_meminfo.mi_size;
	*type = xiocb.plist.xiocb_meminfo.mi_type;

	वापस 0;
पूर्ण

पूर्णांक cfe_निकास(पूर्णांक warm, पूर्णांक status)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_RESTART;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = warm ? CFE_FLG_WARMSTART : 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_निकासstat);
	xiocb.plist.xiocb_निकासstat.status = status;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_flushcache(पूर्णांक flg)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_FLUSHCACHE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = flg;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_getdevinfo(अक्षर *name)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_GETINFO;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = 0;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_buffer.buf_length = म_माप(name);

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.plist.xiocb_buffer.buf_ioctlcmd;
पूर्ण

पूर्णांक cfe_दो_पर्या(अक्षर *name, अक्षर *dest, पूर्णांक destlen)
अणु
	काष्ठा cfe_xiocb xiocb;

	*dest = 0;

	xiocb.xiocb_fcode = CFE_CMD_ENV_GET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_envbuf);
	xiocb.plist.xiocb_envbuf.क्रमागत_idx = 0;
	xiocb.plist.xiocb_envbuf.name_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_envbuf.name_length = म_माप(name);
	xiocb.plist.xiocb_envbuf.val_ptr = XPTR_FROM_NATIVE(dest);
	xiocb.plist.xiocb_envbuf.val_length = destlen;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_getfwinfo(cfe_fwinfo_t * info)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_GETINFO;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_fwinfo);

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;

	info->fwi_version = xiocb.plist.xiocb_fwinfo.fwi_version;
	info->fwi_totalmem = xiocb.plist.xiocb_fwinfo.fwi_totalmem;
	info->fwi_flags = xiocb.plist.xiocb_fwinfo.fwi_flags;
	info->fwi_boardid = xiocb.plist.xiocb_fwinfo.fwi_boardid;
	info->fwi_bootarea_va = xiocb.plist.xiocb_fwinfo.fwi_bootarea_va;
	info->fwi_bootarea_pa = xiocb.plist.xiocb_fwinfo.fwi_bootarea_pa;
	info->fwi_bootarea_size =
	    xiocb.plist.xiocb_fwinfo.fwi_bootarea_size;

	वापस 0;
पूर्ण

पूर्णांक cfe_माला_लोtdhandle(पूर्णांक flg)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_GETHANDLE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = flg;
	xiocb.xiocb_psize = 0;

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.xiocb_handle;
पूर्ण

पूर्णांक64_t
cfe_getticks(व्योम)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_FW_GETTIME;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_समय);
	xiocb.plist.xiocb_समय.ticks = 0;

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.plist.xiocb_समय.ticks;

पूर्ण

पूर्णांक cfe_inpstat(पूर्णांक handle)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_INPSTAT;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_inpstat);
	xiocb.plist.xiocb_inpstat.inp_status = 0;

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.plist.xiocb_inpstat.inp_status;
पूर्ण

पूर्णांक
cfe_ioctl(पूर्णांक handle, अचिन्हित पूर्णांक ioctlnum, अचिन्हित अक्षर *buffer,
	  पूर्णांक length, पूर्णांक *retlen, u64 offset)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_IOCTL;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = offset;
	xiocb.plist.xiocb_buffer.buf_ioctlcmd = ioctlnum;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(buffer);
	xiocb.plist.xiocb_buffer.buf_length = length;

	cfe_iocb_dispatch(&xiocb);

	अगर (retlen)
		*retlen = xiocb.plist.xiocb_buffer.buf_retlen;
	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_खोलो(अक्षर *name)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_OPEN;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = 0;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_buffer.buf_length = म_माप(name);

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.xiocb_handle;
पूर्ण

पूर्णांक cfe_पढ़ो(पूर्णांक handle, अचिन्हित अक्षर *buffer, पूर्णांक length)
अणु
	वापस cfe_पढ़ोblk(handle, 0, buffer, length);
पूर्ण

पूर्णांक cfe_पढ़ोblk(पूर्णांक handle, s64 offset, अचिन्हित अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_READ;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = offset;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(buffer);
	xiocb.plist.xiocb_buffer.buf_length = length;

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.plist.xiocb_buffer.buf_retlen;
पूर्ण

पूर्णांक cfe_setenv(अक्षर *name, अक्षर *val)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_ENV_SET;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = 0;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_envbuf);
	xiocb.plist.xiocb_envbuf.क्रमागत_idx = 0;
	xiocb.plist.xiocb_envbuf.name_ptr = XPTR_FROM_NATIVE(name);
	xiocb.plist.xiocb_envbuf.name_length = म_माप(name);
	xiocb.plist.xiocb_envbuf.val_ptr = XPTR_FROM_NATIVE(val);
	xiocb.plist.xiocb_envbuf.val_length = म_माप(val);

	cfe_iocb_dispatch(&xiocb);

	वापस xiocb.xiocb_status;
पूर्ण

पूर्णांक cfe_ग_लिखो(पूर्णांक handle, स्थिर अक्षर *buffer, पूर्णांक length)
अणु
	वापस cfe_ग_लिखोblk(handle, 0, buffer, length);
पूर्ण

पूर्णांक cfe_ग_लिखोblk(पूर्णांक handle, s64 offset, स्थिर अक्षर *buffer, पूर्णांक length)
अणु
	काष्ठा cfe_xiocb xiocb;

	xiocb.xiocb_fcode = CFE_CMD_DEV_WRITE;
	xiocb.xiocb_status = 0;
	xiocb.xiocb_handle = handle;
	xiocb.xiocb_flags = 0;
	xiocb.xiocb_psize = माप(काष्ठा xiocb_buffer);
	xiocb.plist.xiocb_buffer.buf_offset = offset;
	xiocb.plist.xiocb_buffer.buf_ptr = XPTR_FROM_NATIVE(buffer);
	xiocb.plist.xiocb_buffer.buf_length = length;

	cfe_iocb_dispatch(&xiocb);

	अगर (xiocb.xiocb_status < 0)
		वापस xiocb.xiocb_status;
	वापस xiocb.plist.xiocb_buffer.buf_retlen;
पूर्ण
