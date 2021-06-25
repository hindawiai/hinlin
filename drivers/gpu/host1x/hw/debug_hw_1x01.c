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

अटल व्योम host1x_debug_show_channel_cdma(काष्ठा host1x *host,
					   काष्ठा host1x_channel *ch,
					   काष्ठा output *o)
अणु
	काष्ठा host1x_cdma *cdma = &ch->cdma;
	u32 dmaput, dmaget, dmactrl;
	u32 cbstat, cbपढ़ो;
	u32 val, base, baseval;

	dmaput = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAPUT);
	dmaget = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAGET);
	dmactrl = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMACTRL);
	cbपढ़ो = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CBREAD(ch->id));
	cbstat = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CBSTAT(ch->id));

	host1x_debug_output(o, "%u-%s: ", ch->id, dev_name(ch->dev));

	अगर (HOST1X_CHANNEL_DMACTRL_DMASTOP_V(dmactrl) ||
	    !ch->cdma.push_buffer.mapped) अणु
		host1x_debug_output(o, "inactive\n\n");
		वापस;
	पूर्ण

	अगर (HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat) == HOST1X_CLASS_HOST1X &&
	    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
			HOST1X_UCLASS_WAIT_SYNCPT)
		host1x_debug_output(o, "waiting on syncpt %d val %d\n",
				    cbपढ़ो >> 24, cbपढ़ो & 0xffffff);
	अन्यथा अगर (HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat) ==
				HOST1X_CLASS_HOST1X &&
		 HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat) ==
				HOST1X_UCLASS_WAIT_SYNCPT_BASE) अणु
		base = (cbपढ़ो >> 16) & 0xff;
		baseval =
			host1x_sync_पढ़ोl(host, HOST1X_SYNC_SYNCPT_BASE(base));
		val = cbपढ़ो & 0xffff;
		host1x_debug_output(o, "waiting on syncpt %d val %d (base %d = %d; offset = %d)\n",
				    cbपढ़ो >> 24, baseval + val, base,
				    baseval, val);
	पूर्ण अन्यथा
		host1x_debug_output(o, "active class %02x, offset %04x, val %08x\n",
				    HOST1X_SYNC_CBSTAT_CBCLASS_V(cbstat),
				    HOST1X_SYNC_CBSTAT_CBOFFSET_V(cbstat),
				    cbपढ़ो);

	host1x_debug_output(o, "DMAPUT %08x, DMAGET %08x, DMACTL %08x\n",
			    dmaput, dmaget, dmactrl);
	host1x_debug_output(o, "CBREAD %08x, CBSTAT %08x\n", cbपढ़ो, cbstat);

	show_channel_gathers(o, cdma);
	host1x_debug_output(o, "\n");
पूर्ण

अटल व्योम host1x_debug_show_channel_fअगरo(काष्ठा host1x *host,
					   काष्ठा host1x_channel *ch,
					   काष्ठा output *o)
अणु
	u32 val, rd_ptr, wr_ptr, start, end;
	अचिन्हित पूर्णांक data_count = 0;

	host1x_debug_output(o, "%u: fifo:\n", ch->id);

	val = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_FIFOSTAT);
	host1x_debug_output(o, "FIFOSTAT %08x\n", val);
	अगर (HOST1X_CHANNEL_FIFOSTAT_CFEMPTY_V(val)) अणु
		host1x_debug_output(o, "[empty]\n");
		वापस;
	पूर्ण

	host1x_sync_ग_लिखोl(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
	host1x_sync_ग_लिखोl(host, HOST1X_SYNC_CFPEEK_CTRL_ENA_F(1) |
			   HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F(ch->id),
			   HOST1X_SYNC_CFPEEK_CTRL);

	val = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CFPEEK_PTRS);
	rd_ptr = HOST1X_SYNC_CFPEEK_PTRS_CF_RD_PTR_V(val);
	wr_ptr = HOST1X_SYNC_CFPEEK_PTRS_CF_WR_PTR_V(val);

	val = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CF_SETUP(ch->id));
	start = HOST1X_SYNC_CF_SETUP_BASE_V(val);
	end = HOST1X_SYNC_CF_SETUP_LIMIT_V(val);

	करो अणु
		host1x_sync_ग_लिखोl(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
		host1x_sync_ग_लिखोl(host, HOST1X_SYNC_CFPEEK_CTRL_ENA_F(1) |
				   HOST1X_SYNC_CFPEEK_CTRL_CHANNR_F(ch->id) |
				   HOST1X_SYNC_CFPEEK_CTRL_ADDR_F(rd_ptr),
				   HOST1X_SYNC_CFPEEK_CTRL);
		val = host1x_sync_पढ़ोl(host, HOST1X_SYNC_CFPEEK_READ);

		अगर (!data_count) अणु
			host1x_debug_output(o, "%08x: ", val);
			data_count = show_channel_command(o, val, शून्य);
		पूर्ण अन्यथा अणु
			host1x_debug_cont(o, "%08x%s", val,
					  data_count > 1 ? ", " : "])\n");
			data_count--;
		पूर्ण

		अगर (rd_ptr == end)
			rd_ptr = start;
		अन्यथा
			rd_ptr++;
	पूर्ण जबतक (rd_ptr != wr_ptr);

	अगर (data_count)
		host1x_debug_cont(o, ", ...])\n");
	host1x_debug_output(o, "\n");

	host1x_sync_ग_लिखोl(host, 0x0, HOST1X_SYNC_CFPEEK_CTRL);
पूर्ण

अटल व्योम host1x_debug_show_mlocks(काष्ठा host1x *host, काष्ठा output *o)
अणु
	अचिन्हित पूर्णांक i;

	host1x_debug_output(o, "---- mlocks ----\n");

	क्रम (i = 0; i < host1x_syncpt_nb_mlocks(host); i++) अणु
		u32 owner =
			host1x_sync_पढ़ोl(host, HOST1X_SYNC_MLOCK_OWNER(i));
		अगर (HOST1X_SYNC_MLOCK_OWNER_CH_OWNS_V(owner))
			host1x_debug_output(o, "%u: locked by channel %u\n",
				i, HOST1X_SYNC_MLOCK_OWNER_CHID_V(owner));
		अन्यथा अगर (HOST1X_SYNC_MLOCK_OWNER_CPU_OWNS_V(owner))
			host1x_debug_output(o, "%u: locked by cpu\n", i);
		अन्यथा
			host1x_debug_output(o, "%u: unlocked\n", i);
	पूर्ण

	host1x_debug_output(o, "\n");
पूर्ण
