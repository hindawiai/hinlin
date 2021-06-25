<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 * Author: Erik Gilling <konkers@android.com>
 *
 * Copyright (C) 2011-2013 NVIDIA Corporation
 */

#समावेश "../dev.h"
#समावेश "../debug.h"
#समावेश "../cdma.h"
#समावेश "../channel.h"

#घोषणा HOST1X_DEBUG_MAX_PAGE_OFFSET 102400

क्रमागत अणु
	HOST1X_OPCODE_SETCLASS	= 0x00,
	HOST1X_OPCODE_INCR	= 0x01,
	HOST1X_OPCODE_NONINCR	= 0x02,
	HOST1X_OPCODE_MASK	= 0x03,
	HOST1X_OPCODE_IMM	= 0x04,
	HOST1X_OPCODE_RESTART	= 0x05,
	HOST1X_OPCODE_GATHER	= 0x06,
	HOST1X_OPCODE_SETSTRMID = 0x07,
	HOST1X_OPCODE_SETAPPID  = 0x08,
	HOST1X_OPCODE_SETPYLD   = 0x09,
	HOST1X_OPCODE_INCR_W    = 0x0a,
	HOST1X_OPCODE_NONINCR_W = 0x0b,
	HOST1X_OPCODE_GATHER_W  = 0x0c,
	HOST1X_OPCODE_RESTART_W = 0x0d,
	HOST1X_OPCODE_EXTEND	= 0x0e,
पूर्ण;

क्रमागत अणु
	HOST1X_OPCODE_EXTEND_ACQUIRE_MLOCK	= 0x00,
	HOST1X_OPCODE_EXTEND_RELEASE_MLOCK	= 0x01,
पूर्ण;

#घोषणा INVALID_PAYLOAD				0xffffffff

अटल अचिन्हित पूर्णांक show_channel_command(काष्ठा output *o, u32 val,
					 u32 *payload)
अणु
	अचिन्हित पूर्णांक mask, subop, num, opcode;

	opcode = val >> 28;

	चयन (opcode) अणु
	हाल HOST1X_OPCODE_SETCLASS:
		mask = val & 0x3f;
		अगर (mask) अणु
			host1x_debug_cont(o, "SETCL(class=%03x, offset=%03x, mask=%02x, [",
					    val >> 6 & 0x3ff,
					    val >> 16 & 0xfff, mask);
			वापस hweight8(mask);
		पूर्ण

		host1x_debug_cont(o, "SETCL(class=%03x)\n", val >> 6 & 0x3ff);
		वापस 0;

	हाल HOST1X_OPCODE_INCR:
		num = val & 0xffff;
		host1x_debug_cont(o, "INCR(offset=%03x, [",
				    val >> 16 & 0xfff);
		अगर (!num)
			host1x_debug_cont(o, "])\n");

		वापस num;

	हाल HOST1X_OPCODE_NONINCR:
		num = val & 0xffff;
		host1x_debug_cont(o, "NONINCR(offset=%03x, [",
				    val >> 16 & 0xfff);
		अगर (!num)
			host1x_debug_cont(o, "])\n");

		वापस num;

	हाल HOST1X_OPCODE_MASK:
		mask = val & 0xffff;
		host1x_debug_cont(o, "MASK(offset=%03x, mask=%03x, [",
				    val >> 16 & 0xfff, mask);
		अगर (!mask)
			host1x_debug_cont(o, "])\n");

		वापस hweight16(mask);

	हाल HOST1X_OPCODE_IMM:
		host1x_debug_cont(o, "IMM(offset=%03x, data=%03x)\n",
				    val >> 16 & 0xfff, val & 0xffff);
		वापस 0;

	हाल HOST1X_OPCODE_RESTART:
		host1x_debug_cont(o, "RESTART(offset=%08x)\n", val << 4);
		वापस 0;

	हाल HOST1X_OPCODE_GATHER:
		host1x_debug_cont(o, "GATHER(offset=%03x, insert=%d, type=%d, count=%04x, addr=[",
				    val >> 16 & 0xfff, val >> 15 & 0x1,
				    val >> 14 & 0x1, val & 0x3fff);
		वापस 1;

#अगर HOST1X_HW >= 6
	हाल HOST1X_OPCODE_SETSTRMID:
		host1x_debug_cont(o, "SETSTRMID(offset=%06x)\n",
				  val & 0x3fffff);
		वापस 0;

	हाल HOST1X_OPCODE_SETAPPID:
		host1x_debug_cont(o, "SETAPPID(appid=%02x)\n", val & 0xff);
		वापस 0;

	हाल HOST1X_OPCODE_SETPYLD:
		*payload = val & 0xffff;
		host1x_debug_cont(o, "SETPYLD(data=%04x)\n", *payload);
		वापस 0;

	हाल HOST1X_OPCODE_INCR_W:
	हाल HOST1X_OPCODE_NONINCR_W:
		host1x_debug_cont(o, "%s(offset=%06x, ",
				  opcode == HOST1X_OPCODE_INCR_W ?
					"INCR_W" : "NONINCR_W",
				  val & 0x3fffff);
		अगर (*payload == 0) अणु
			host1x_debug_cont(o, "[])\n");
			वापस 0;
		पूर्ण अन्यथा अगर (*payload == INVALID_PAYLOAD) अणु
			host1x_debug_cont(o, "unknown)\n");
			वापस 0;
		पूर्ण अन्यथा अणु
			host1x_debug_cont(o, "[");
			वापस *payload;
		पूर्ण

	हाल HOST1X_OPCODE_GATHER_W:
		host1x_debug_cont(o, "GATHER_W(count=%04x, addr=[",
				  val & 0x3fff);
		वापस 2;
#पूर्ण_अगर

	हाल HOST1X_OPCODE_EXTEND:
		subop = val >> 24 & 0xf;
		अगर (subop == HOST1X_OPCODE_EXTEND_ACQUIRE_MLOCK)
			host1x_debug_cont(o, "ACQUIRE_MLOCK(index=%d)\n",
					    val & 0xff);
		अन्यथा अगर (subop == HOST1X_OPCODE_EXTEND_RELEASE_MLOCK)
			host1x_debug_cont(o, "RELEASE_MLOCK(index=%d)\n",
					    val & 0xff);
		अन्यथा
			host1x_debug_cont(o, "EXTEND_UNKNOWN(%08x)\n", val);
		वापस 0;

	शेष:
		host1x_debug_cont(o, "UNKNOWN\n");
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम show_gather(काष्ठा output *o, phys_addr_t phys_addr,
			अचिन्हित पूर्णांक words, काष्ठा host1x_cdma *cdma,
			phys_addr_t pin_addr, u32 *map_addr)
अणु
	/* Map dmaget cursor to corresponding mem handle */
	u32 offset = phys_addr - pin_addr;
	अचिन्हित पूर्णांक data_count = 0, i;
	u32 payload = INVALID_PAYLOAD;

	/*
	 * Someबार we're given dअगरferent hardware address to the same
	 * page - in these हालs the offset will get an invalid number and
	 * we just have to bail out.
	 */
	अगर (offset > HOST1X_DEBUG_MAX_PAGE_OFFSET) अणु
		host1x_debug_output(o, "[address mismatch]\n");
		वापस;
	पूर्ण

	क्रम (i = 0; i < words; i++) अणु
		u32 addr = phys_addr + i * 4;
		u32 val = *(map_addr + offset / 4 + i);

		अगर (!data_count) अणु
			host1x_debug_output(o, "%08x: %08x: ", addr, val);
			data_count = show_channel_command(o, val, &payload);
		पूर्ण अन्यथा अणु
			host1x_debug_cont(o, "%08x%s", val,
					    data_count > 1 ? ", " : "])\n");
			data_count--;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम show_channel_gathers(काष्ठा output *o, काष्ठा host1x_cdma *cdma)
अणु
	काष्ठा push_buffer *pb = &cdma->push_buffer;
	काष्ठा host1x_job *job;

	host1x_debug_output(o, "PUSHBUF at %pad, %u words\n",
			    &pb->dma, pb->size / 4);

	show_gather(o, pb->dma, pb->size / 4, cdma, pb->dma, pb->mapped);

	list_क्रम_each_entry(job, &cdma->sync_queue, list) अणु
		अचिन्हित पूर्णांक i;

		host1x_debug_output(o, "\n%p: JOB, syncpt_id=%d, syncpt_val=%d, first_get=%08x, timeout=%d num_slots=%d, num_handles=%d\n",
				    job, job->syncpt->id, job->syncpt_end,
				    job->first_get, job->समयout,
				    job->num_slots, job->num_unpins);

		क्रम (i = 0; i < job->num_gathers; i++) अणु
			काष्ठा host1x_job_gather *g = &job->gathers[i];
			u32 *mapped;

			अगर (job->gather_copy_mapped)
				mapped = (u32 *)job->gather_copy_mapped;
			अन्यथा
				mapped = host1x_bo_mmap(g->bo);

			अगर (!mapped) अणु
				host1x_debug_output(o, "[could not mmap]\n");
				जारी;
			पूर्ण

			host1x_debug_output(o, "    GATHER at %pad+%#x, %d words\n",
					    &g->base, g->offset, g->words);

			show_gather(o, g->base + g->offset, g->words, cdma,
				    g->base, mapped);

			अगर (!job->gather_copy_mapped)
				host1x_bo_munmap(g->bo, mapped);
		पूर्ण
	पूर्ण
पूर्ण

#अगर HOST1X_HW >= 6
#समावेश "debug_hw_1x06.c"
#अन्यथा
#समावेश "debug_hw_1x01.c"
#पूर्ण_अगर

अटल स्थिर काष्ठा host1x_debug_ops host1x_debug_ops = अणु
	.show_channel_cdma = host1x_debug_show_channel_cdma,
	.show_channel_fअगरo = host1x_debug_show_channel_fअगरo,
	.show_mlocks = host1x_debug_show_mlocks,
पूर्ण;
