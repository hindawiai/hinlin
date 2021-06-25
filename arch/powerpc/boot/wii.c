<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/घातerpc/boot/wii.c
 *
 * Nपूर्णांकenकरो Wii bootwrapper support
 * Copyright (C) 2008-2009 The GameCube Linux Team
 * Copyright (C) 2008,2009 Albert Herranz
 */

#समावेश <मानकघोष.स>
#समावेश "stdio.h"
#समावेश "types.h"
#समावेश "io.h"
#समावेश "ops.h"

#समावेश "ugecon.h"

BSS_STACK(8192);

#घोषणा HW_REG(x)		((व्योम *)(x))

#घोषणा EXI_CTRL		HW_REG(0x0d800070)
#घोषणा EXI_CTRL_ENABLE		(1<<0)

#घोषणा MEM2_TOP		(0x10000000 + 64*1024*1024)
#घोषणा FIRMWARE_DEFAULT_SIZE	(12*1024*1024)


काष्ठा mipc_infohdr अणु
	अक्षर magic[3];
	u8 version;
	u32 mem2_boundary;
	u32 ipc_in;
	माप_प्रकार ipc_in_size;
	u32 ipc_out;
	माप_प्रकार ipc_out_size;
पूर्ण;

अटल पूर्णांक mipc_check_address(u32 pa)
अणु
	/* only MEM2 addresses */
	अगर (pa < 0x10000000 || pa > 0x14000000)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल काष्ठा mipc_infohdr *mipc_get_infohdr(व्योम)
अणु
	काष्ठा mipc_infohdr **hdrp, *hdr;

	/* 'mini' header poपूर्णांकer is the last word of MEM2 memory */
	hdrp = (काष्ठा mipc_infohdr **)0x13fffffc;
	अगर (mipc_check_address((u32)hdrp)) अणु
		म_लिखो("mini: invalid hdrp %08X\n", (u32)hdrp);
		hdr = शून्य;
		जाओ out;
	पूर्ण

	hdr = *hdrp;
	अगर (mipc_check_address((u32)hdr)) अणु
		म_लिखो("mini: invalid hdr %08X\n", (u32)hdr);
		hdr = शून्य;
		जाओ out;
	पूर्ण
	अगर (स_भेद(hdr->magic, "IPC", 3)) अणु
		म_लिखो("mini: invalid magic\n");
		hdr = शून्य;
		जाओ out;
	पूर्ण

out:
	वापस hdr;
पूर्ण

अटल पूर्णांक mipc_get_mem2_boundary(u32 *mem2_boundary)
अणु
	काष्ठा mipc_infohdr *hdr;
	पूर्णांक error;

	hdr = mipc_get_infohdr();
	अगर (!hdr) अणु
		error = -1;
		जाओ out;
	पूर्ण

	अगर (mipc_check_address(hdr->mem2_boundary)) अणु
		म_लिखो("mini: invalid mem2_boundary %08X\n",
		       hdr->mem2_boundary);
		error = -EINVAL;
		जाओ out;
	पूर्ण
	*mem2_boundary = hdr->mem2_boundary;
	error = 0;
out:
	वापस error;

पूर्ण

अटल व्योम platक्रमm_fixups(व्योम)
अणु
	व्योम *mem;
	u32 reg[4];
	u32 mem2_boundary;
	पूर्णांक len;
	पूर्णांक error;

	mem = finddevice("/memory");
	अगर (!mem)
		fatal("Can't find memory node\n");

	/* two ranges of (address, size) words */
	len = getprop(mem, "reg", reg, माप(reg));
	अगर (len != माप(reg)) अणु
		/* nothing to करो */
		जाओ out;
	पूर्ण

	/* retrieve MEM2 boundary from 'mini' */
	error = mipc_get_mem2_boundary(&mem2_boundary);
	अगर (error) अणु
		/* अगर that fails use a sane value */
		mem2_boundary = MEM2_TOP - FIRMWARE_DEFAULT_SIZE;
	पूर्ण

	अगर (mem2_boundary > reg[2] && mem2_boundary < reg[2] + reg[3]) अणु
		reg[3] = mem2_boundary - reg[2];
		म_लिखो("top of MEM2 @ %08X\n", reg[2] + reg[3]);
		setprop(mem, "reg", reg, माप(reg));
	पूर्ण

out:
	वापस;
पूर्ण

व्योम platक्रमm_init(अचिन्हित दीर्घ r3, अचिन्हित दीर्घ r4, अचिन्हित दीर्घ r5)
अणु
	u32 heapsize = 24*1024*1024 - (u32)_end;

	simple_alloc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_start);

	/*
	 * 'mini' boots the Broadway processor with EXI disabled.
	 * We need it enabled beक्रमe probing क्रम the USB Gecko.
	 */
	out_be32(EXI_CTRL, in_be32(EXI_CTRL) | EXI_CTRL_ENABLE);

	अगर (ug_probe())
		console_ops.ग_लिखो = ug_console_ग_लिखो;

	platक्रमm_ops.fixups = platक्रमm_fixups;
पूर्ण

