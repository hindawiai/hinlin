<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2010 Google, Inc.
 * Author: Erik Gilling <konkers@android.com>
 *
 * Copyright (C) 2011-2017 NVIDIA Corporation
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
	u32 offset, class;
	u32 ch_stat;

	dmaput = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAPUT);
	dmaget = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMAGET);
	dmactrl = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_DMACTRL);
	offset = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_CMDP_OFFSET);
	class = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_CMDP_CLASS);
	ch_stat = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_CHANNELSTAT);

	host1x_debug_output(o, "%u-%s: ", ch->id, dev_name(ch->dev));

	अगर (dmactrl & HOST1X_CHANNEL_DMACTRL_DMASTOP ||
	    !ch->cdma.push_buffer.mapped) अणु
		host1x_debug_output(o, "inactive\n\n");
		वापस;
	पूर्ण

	अगर (class == HOST1X_CLASS_HOST1X && offset == HOST1X_UCLASS_WAIT_SYNCPT)
		host1x_debug_output(o, "waiting on syncpt\n");
	अन्यथा
		host1x_debug_output(o, "active class %02x, offset %04x\n",
				    class, offset);

	host1x_debug_output(o, "DMAPUT %08x, DMAGET %08x, DMACTL %08x\n",
			    dmaput, dmaget, dmactrl);
	host1x_debug_output(o, "CHANNELSTAT %02x\n", ch_stat);

	show_channel_gathers(o, cdma);
	host1x_debug_output(o, "\n");
पूर्ण

अटल व्योम host1x_debug_show_channel_fअगरo(काष्ठा host1x *host,
					   काष्ठा host1x_channel *ch,
					   काष्ठा output *o)
अणु
#अगर HOST1X_HW <= 6
	u32 rd_ptr, wr_ptr, start, end;
	u32 payload = INVALID_PAYLOAD;
	अचिन्हित पूर्णांक data_count = 0;
#पूर्ण_अगर
	u32 val;

	host1x_debug_output(o, "%u: fifo:\n", ch->id);

	val = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_CMDFIFO_STAT);
	host1x_debug_output(o, "CMDFIFO_STAT %08x\n", val);
	अगर (val & HOST1X_CHANNEL_CMDFIFO_STAT_EMPTY) अणु
		host1x_debug_output(o, "[empty]\n");
		वापस;
	पूर्ण

	val = host1x_ch_पढ़ोl(ch, HOST1X_CHANNEL_CMDFIFO_RDATA);
	host1x_debug_output(o, "CMDFIFO_RDATA %08x\n", val);

#अगर HOST1X_HW <= 6
	/* Peek poपूर्णांकer values are invalid during SLCG, so disable it */
	host1x_hypervisor_ग_लिखोl(host, 0x1, HOST1X_HV_ICG_EN_OVERRIDE);

	val = 0;
	val |= HOST1X_HV_CMDFIFO_PEEK_CTRL_ENABLE;
	val |= HOST1X_HV_CMDFIFO_PEEK_CTRL_CHANNEL(ch->id);
	host1x_hypervisor_ग_लिखोl(host, val, HOST1X_HV_CMDFIFO_PEEK_CTRL);

	val = host1x_hypervisor_पढ़ोl(host, HOST1X_HV_CMDFIFO_PEEK_PTRS);
	rd_ptr = HOST1X_HV_CMDFIFO_PEEK_PTRS_RD_PTR_V(val);
	wr_ptr = HOST1X_HV_CMDFIFO_PEEK_PTRS_WR_PTR_V(val);

	val = host1x_hypervisor_पढ़ोl(host, HOST1X_HV_CMDFIFO_SETUP(ch->id));
	start = HOST1X_HV_CMDFIFO_SETUP_BASE_V(val);
	end = HOST1X_HV_CMDFIFO_SETUP_LIMIT_V(val);

	करो अणु
		val = 0;
		val |= HOST1X_HV_CMDFIFO_PEEK_CTRL_ENABLE;
		val |= HOST1X_HV_CMDFIFO_PEEK_CTRL_CHANNEL(ch->id);
		val |= HOST1X_HV_CMDFIFO_PEEK_CTRL_ADDR(rd_ptr);
		host1x_hypervisor_ग_लिखोl(host, val,
					 HOST1X_HV_CMDFIFO_PEEK_CTRL);

		val = host1x_hypervisor_पढ़ोl(host,
					      HOST1X_HV_CMDFIFO_PEEK_READ);

		अगर (!data_count) अणु
			host1x_debug_output(o, "%03x 0x%08x: ",
					    rd_ptr - start, val);
			data_count = show_channel_command(o, val, &payload);
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

	host1x_hypervisor_ग_लिखोl(host, 0x0, HOST1X_HV_CMDFIFO_PEEK_CTRL);
	host1x_hypervisor_ग_लिखोl(host, 0x0, HOST1X_HV_ICG_EN_OVERRIDE);
#पूर्ण_अगर
पूर्ण

अटल व्योम host1x_debug_show_mlocks(काष्ठा host1x *host, काष्ठा output *o)
अणु
	/* TODO */
पूर्ण
