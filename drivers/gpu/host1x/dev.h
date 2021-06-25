<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2012-2015, NVIDIA Corporation.
 */

#अगर_अघोषित HOST1X_DEV_H
#घोषणा HOST1X_DEV_H

#समावेश <linux/device.h>
#समावेश <linux/iommu.h>
#समावेश <linux/iova.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>

#समावेश "cdma.h"
#समावेश "channel.h"
#समावेश "intr.h"
#समावेश "job.h"
#समावेश "syncpt.h"

काष्ठा host1x_syncpt;
काष्ठा host1x_syncpt_base;
काष्ठा host1x_channel;
काष्ठा host1x_cdma;
काष्ठा host1x_job;
काष्ठा push_buffer;
काष्ठा output;
काष्ठा dentry;

काष्ठा host1x_channel_ops अणु
	पूर्णांक (*init)(काष्ठा host1x_channel *channel, काष्ठा host1x *host,
		    अचिन्हित पूर्णांक id);
	पूर्णांक (*submit)(काष्ठा host1x_job *job);
पूर्ण;

काष्ठा host1x_cdma_ops अणु
	व्योम (*start)(काष्ठा host1x_cdma *cdma);
	व्योम (*stop)(काष्ठा host1x_cdma *cdma);
	व्योम (*flush)(काष्ठा  host1x_cdma *cdma);
	पूर्णांक (*समयout_init)(काष्ठा host1x_cdma *cdma);
	व्योम (*समयout_destroy)(काष्ठा host1x_cdma *cdma);
	व्योम (*मुक्तze)(काष्ठा host1x_cdma *cdma);
	व्योम (*resume)(काष्ठा host1x_cdma *cdma, u32 getptr);
	व्योम (*समयout_cpu_incr)(काष्ठा host1x_cdma *cdma, u32 getptr,
				 u32 syncpt_incrs, u32 syncval, u32 nr_slots);
पूर्ण;

काष्ठा host1x_pushbuffer_ops अणु
	व्योम (*init)(काष्ठा push_buffer *pb);
पूर्ण;

काष्ठा host1x_debug_ops अणु
	व्योम (*debug_init)(काष्ठा dentry *de);
	व्योम (*show_channel_cdma)(काष्ठा host1x *host,
				  काष्ठा host1x_channel *ch,
				  काष्ठा output *o);
	व्योम (*show_channel_fअगरo)(काष्ठा host1x *host,
				  काष्ठा host1x_channel *ch,
				  काष्ठा output *o);
	व्योम (*show_mlocks)(काष्ठा host1x *host, काष्ठा output *output);

पूर्ण;

काष्ठा host1x_syncpt_ops अणु
	व्योम (*restore)(काष्ठा host1x_syncpt *syncpt);
	व्योम (*restore_रुको_base)(काष्ठा host1x_syncpt *syncpt);
	व्योम (*load_रुको_base)(काष्ठा host1x_syncpt *syncpt);
	u32 (*load)(काष्ठा host1x_syncpt *syncpt);
	पूर्णांक (*cpu_incr)(काष्ठा host1x_syncpt *syncpt);
	व्योम (*assign_to_channel)(काष्ठा host1x_syncpt *syncpt,
	                          काष्ठा host1x_channel *channel);
	व्योम (*enable_protection)(काष्ठा host1x *host);
पूर्ण;

काष्ठा host1x_पूर्णांकr_ops अणु
	पूर्णांक (*init_host_sync)(काष्ठा host1x *host, u32 cpm,
		व्योम (*syncpt_thresh_work)(काष्ठा work_काष्ठा *work));
	व्योम (*set_syncpt_threshold)(
		काष्ठा host1x *host, अचिन्हित पूर्णांक id, u32 thresh);
	व्योम (*enable_syncpt_पूर्णांकr)(काष्ठा host1x *host, अचिन्हित पूर्णांक id);
	व्योम (*disable_syncpt_पूर्णांकr)(काष्ठा host1x *host, अचिन्हित पूर्णांक id);
	व्योम (*disable_all_syncpt_पूर्णांकrs)(काष्ठा host1x *host);
	पूर्णांक (*मुक्त_syncpt_irq)(काष्ठा host1x *host);
पूर्ण;

काष्ठा host1x_sid_entry अणु
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक limit;
पूर्ण;

काष्ठा host1x_info अणु
	अचिन्हित पूर्णांक nb_channels; /* host1x: number of channels supported */
	अचिन्हित पूर्णांक nb_pts; /* host1x: number of syncpoपूर्णांकs supported */
	अचिन्हित पूर्णांक nb_bases; /* host1x: number of syncpoपूर्णांक bases supported */
	अचिन्हित पूर्णांक nb_mlocks; /* host1x: number of mlocks supported */
	पूर्णांक (*init)(काष्ठा host1x *host1x); /* initialize per SoC ops */
	अचिन्हित पूर्णांक sync_offset; /* offset of syncpoपूर्णांक रेजिस्टरs */
	u64 dma_mask; /* mask of addressable memory */
	bool has_wide_gather; /* supports GATHER_W opcode */
	bool has_hypervisor; /* has hypervisor रेजिस्टरs */
	अचिन्हित पूर्णांक num_sid_entries;
	स्थिर काष्ठा host1x_sid_entry *sid_table;
	/*
	 * On T20-T148, the boot chain may setup DC to increment syncpoपूर्णांकs
	 * 26/27 on VBLANK. As such we cannot use these syncpoपूर्णांकs until
	 * the display driver disables VBLANK increments.
	 */
	bool reserve_vblank_syncpts;
पूर्ण;

काष्ठा host1x अणु
	स्थिर काष्ठा host1x_info *info;

	व्योम __iomem *regs;
	व्योम __iomem *hv_regs; /* hypervisor region */
	काष्ठा host1x_syncpt *syncpt;
	काष्ठा host1x_syncpt_base *bases;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा reset_control *rst;

	काष्ठा iommu_group *group;
	काष्ठा iommu_करोमुख्य *करोमुख्य;
	काष्ठा iova_करोमुख्य iova;
	dma_addr_t ioबहु_पूर्ण;

	काष्ठा mutex पूर्णांकr_mutex;
	पूर्णांक पूर्णांकr_syncpt_irq;

	स्थिर काष्ठा host1x_syncpt_ops *syncpt_op;
	स्थिर काष्ठा host1x_पूर्णांकr_ops *पूर्णांकr_op;
	स्थिर काष्ठा host1x_channel_ops *channel_op;
	स्थिर काष्ठा host1x_cdma_ops *cdma_op;
	स्थिर काष्ठा host1x_pushbuffer_ops *cdma_pb_op;
	स्थिर काष्ठा host1x_debug_ops *debug_op;

	काष्ठा host1x_syncpt *nop_sp;

	काष्ठा mutex syncpt_mutex;

	काष्ठा host1x_channel_list channel_list;

	काष्ठा dentry *debugfs;

	काष्ठा mutex devices_lock;
	काष्ठा list_head devices;

	काष्ठा list_head list;

	काष्ठा device_dma_parameters dma_parms;
पूर्ण;

व्योम host1x_hypervisor_ग_लिखोl(काष्ठा host1x *host1x, u32 r, u32 v);
u32 host1x_hypervisor_पढ़ोl(काष्ठा host1x *host1x, u32 r);
व्योम host1x_sync_ग_लिखोl(काष्ठा host1x *host1x, u32 r, u32 v);
u32 host1x_sync_पढ़ोl(काष्ठा host1x *host1x, u32 r);
व्योम host1x_ch_ग_लिखोl(काष्ठा host1x_channel *ch, u32 r, u32 v);
u32 host1x_ch_पढ़ोl(काष्ठा host1x_channel *ch, u32 r);

अटल अंतरभूत व्योम host1x_hw_syncpt_restore(काष्ठा host1x *host,
					    काष्ठा host1x_syncpt *sp)
अणु
	host->syncpt_op->restore(sp);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_syncpt_restore_रुको_base(काष्ठा host1x *host,
						      काष्ठा host1x_syncpt *sp)
अणु
	host->syncpt_op->restore_रुको_base(sp);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_syncpt_load_रुको_base(काष्ठा host1x *host,
						   काष्ठा host1x_syncpt *sp)
अणु
	host->syncpt_op->load_रुको_base(sp);
पूर्ण

अटल अंतरभूत u32 host1x_hw_syncpt_load(काष्ठा host1x *host,
					काष्ठा host1x_syncpt *sp)
अणु
	वापस host->syncpt_op->load(sp);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_syncpt_cpu_incr(काष्ठा host1x *host,
					    काष्ठा host1x_syncpt *sp)
अणु
	वापस host->syncpt_op->cpu_incr(sp);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_syncpt_assign_to_channel(
	काष्ठा host1x *host, काष्ठा host1x_syncpt *sp,
	काष्ठा host1x_channel *ch)
अणु
	वापस host->syncpt_op->assign_to_channel(sp, ch);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_syncpt_enable_protection(काष्ठा host1x *host)
अणु
	वापस host->syncpt_op->enable_protection(host);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_पूर्णांकr_init_host_sync(काष्ठा host1x *host, u32 cpm,
			व्योम (*syncpt_thresh_work)(काष्ठा work_काष्ठा *))
अणु
	वापस host->पूर्णांकr_op->init_host_sync(host, cpm, syncpt_thresh_work);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_पूर्णांकr_set_syncpt_threshold(काष्ठा host1x *host,
						       अचिन्हित पूर्णांक id,
						       u32 thresh)
अणु
	host->पूर्णांकr_op->set_syncpt_threshold(host, id, thresh);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_पूर्णांकr_enable_syncpt_पूर्णांकr(काष्ठा host1x *host,
						     अचिन्हित पूर्णांक id)
अणु
	host->पूर्णांकr_op->enable_syncpt_पूर्णांकr(host, id);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_पूर्णांकr_disable_syncpt_पूर्णांकr(काष्ठा host1x *host,
						      अचिन्हित पूर्णांक id)
अणु
	host->पूर्णांकr_op->disable_syncpt_पूर्णांकr(host, id);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_पूर्णांकr_disable_all_syncpt_पूर्णांकrs(काष्ठा host1x *host)
अणु
	host->पूर्णांकr_op->disable_all_syncpt_पूर्णांकrs(host);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_पूर्णांकr_मुक्त_syncpt_irq(काष्ठा host1x *host)
अणु
	वापस host->पूर्णांकr_op->मुक्त_syncpt_irq(host);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_channel_init(काष्ठा host1x *host,
					 काष्ठा host1x_channel *channel,
					 अचिन्हित पूर्णांक id)
अणु
	वापस host->channel_op->init(channel, host, id);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_channel_submit(काष्ठा host1x *host,
					   काष्ठा host1x_job *job)
अणु
	वापस host->channel_op->submit(job);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_start(काष्ठा host1x *host,
					काष्ठा host1x_cdma *cdma)
अणु
	host->cdma_op->start(cdma);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_stop(काष्ठा host1x *host,
				       काष्ठा host1x_cdma *cdma)
अणु
	host->cdma_op->stop(cdma);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_flush(काष्ठा host1x *host,
					काष्ठा host1x_cdma *cdma)
अणु
	host->cdma_op->flush(cdma);
पूर्ण

अटल अंतरभूत पूर्णांक host1x_hw_cdma_समयout_init(काष्ठा host1x *host,
					      काष्ठा host1x_cdma *cdma)
अणु
	वापस host->cdma_op->समयout_init(cdma);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_समयout_destroy(काष्ठा host1x *host,
						  काष्ठा host1x_cdma *cdma)
अणु
	host->cdma_op->समयout_destroy(cdma);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_मुक्तze(काष्ठा host1x *host,
					 काष्ठा host1x_cdma *cdma)
अणु
	host->cdma_op->मुक्तze(cdma);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_resume(काष्ठा host1x *host,
					 काष्ठा host1x_cdma *cdma, u32 getptr)
अणु
	host->cdma_op->resume(cdma, getptr);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_cdma_समयout_cpu_incr(काष्ठा host1x *host,
						   काष्ठा host1x_cdma *cdma,
						   u32 getptr,
						   u32 syncpt_incrs,
						   u32 syncval, u32 nr_slots)
अणु
	host->cdma_op->समयout_cpu_incr(cdma, getptr, syncpt_incrs, syncval,
					nr_slots);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_pushbuffer_init(काष्ठा host1x *host,
					     काष्ठा push_buffer *pb)
अणु
	host->cdma_pb_op->init(pb);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_debug_init(काष्ठा host1x *host, काष्ठा dentry *de)
अणु
	अगर (host->debug_op && host->debug_op->debug_init)
		host->debug_op->debug_init(de);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_show_channel_cdma(काष्ठा host1x *host,
					       काष्ठा host1x_channel *channel,
					       काष्ठा output *o)
अणु
	host->debug_op->show_channel_cdma(host, channel, o);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_show_channel_fअगरo(काष्ठा host1x *host,
					       काष्ठा host1x_channel *channel,
					       काष्ठा output *o)
अणु
	host->debug_op->show_channel_fअगरo(host, channel, o);
पूर्ण

अटल अंतरभूत व्योम host1x_hw_show_mlocks(काष्ठा host1x *host, काष्ठा output *o)
अणु
	host->debug_op->show_mlocks(host, o);
पूर्ण

बाह्य काष्ठा platक्रमm_driver tegra_mipi_driver;

#पूर्ण_अगर
