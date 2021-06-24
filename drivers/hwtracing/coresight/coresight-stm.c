<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 *
 * Description: CoreSight System Trace Macrocell driver
 *
 * Initial implementation by Pratik Patel
 * (C) 2014-2015 Pratik Patel <pratikp@codeaurora.org>
 *
 * Serious refactoring, code cleanup and upgrading to the Coresight upstream
 * framework by Mathieu Poirier
 * (C) 2015-2016 Mathieu Poirier <mathieu.poirier@linaro.org>
 *
 * Guaranteed timing and support क्रम various packet type coming from the
 * generic STM API by Chunyan Zhang
 * (C) 2015-2016 Chunyan Zhang <zhang.chunyan@linaro.org>
 */
#समावेश <यंत्र/local.h>
#समावेश <linux/acpi.h>
#समावेश <linux/amba/bus.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/clk.h>
#समावेश <linux/coresight.h>
#समावेश <linux/coresight-sपंचांग.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/of_address.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sपंचांग.h>

#समावेश "coresight-priv.h"

#घोषणा STMDMASTARTR			0xc04
#घोषणा STMDMASTOPR			0xc08
#घोषणा STMDMASTATR			0xc0c
#घोषणा STMDMACTLR			0xc10
#घोषणा STMDMAIDR			0xcfc
#घोषणा STMHEER				0xd00
#घोषणा STMHETER			0xd20
#घोषणा STMHEBSR			0xd60
#घोषणा STMHEMCR			0xd64
#घोषणा STMHEMASTR			0xdf4
#घोषणा STMHEFEAT1R			0xdf8
#घोषणा STMHEIDR			0xdfc
#घोषणा STMSPER				0xe00
#घोषणा STMSPTER			0xe20
#घोषणा STMPRIVMASKR			0xe40
#घोषणा STMSPSCR			0xe60
#घोषणा STMSPMSCR			0xe64
#घोषणा STMSPOVERRIDER			0xe68
#घोषणा STMSPMOVERRIDER			0xe6c
#घोषणा STMSPTRIGCSR			0xe70
#घोषणा STMTCSR				0xe80
#घोषणा STMTSSTIMR			0xe84
#घोषणा STMTSFREQR			0xe8c
#घोषणा STMSYNCR			0xe90
#घोषणा STMAUXCR			0xe94
#घोषणा STMSPFEAT1R			0xea0
#घोषणा STMSPFEAT2R			0xea4
#घोषणा STMSPFEAT3R			0xea8
#घोषणा STMITTRIGGER			0xee8
#घोषणा STMITATBDATA0			0xeec
#घोषणा STMITATBCTR2			0xef0
#घोषणा STMITATBID			0xef4
#घोषणा STMITATBCTR0			0xef8

#घोषणा STM_32_CHANNEL			32
#घोषणा BYTES_PER_CHANNEL		256
#घोषणा STM_TRACE_BUF_SIZE		4096
#घोषणा STM_SW_MASTER_END		127

/* Register bit definition */
#घोषणा STMTCSR_BUSY_BIT		23
/* Reserve the first 10 channels क्रम kernel usage */
#घोषणा STM_CHANNEL_OFFSET		0

क्रमागत sपंचांग_pkt_type अणु
	STM_PKT_TYPE_DATA	= 0x98,
	STM_PKT_TYPE_FLAG	= 0xE8,
	STM_PKT_TYPE_TRIG	= 0xF8,
पूर्ण;

#घोषणा sपंचांग_channel_addr(drvdata, ch)	(drvdata->chs.base +	\
					(ch * BYTES_PER_CHANNEL))
#घोषणा sपंचांग_channel_off(type, opts)	(type & ~opts)

अटल पूर्णांक boot_nr_channel;

/*
 * Not really modular but using module_param is the easiest way to
 * reमुख्य consistent with existing use हालs क्रम now.
 */
module_param_named(
	boot_nr_channel, boot_nr_channel, पूर्णांक, S_IRUGO
);

/*
 * काष्ठा channel_space - central management entity क्रम extended ports
 * @base:		memory mapped base address where channels start.
 * @phys:		physical base address of channel region.
 * @guaraneed:		is the channel delivery guaranteed.
 */
काष्ठा channel_space अणु
	व्योम __iomem		*base;
	phys_addr_t		phys;
	अचिन्हित दीर्घ		*guaranteed;
पूर्ण;

DEFINE_CORESIGHT_DEVLIST(sपंचांग_devs, "stm");

/**
 * काष्ठा sपंचांग_drvdata - specअगरics associated to an STM component
 * @base:		memory mapped base address क्रम this component.
 * @atclk:		optional घड़ी क्रम the core parts of the STM.
 * @csdev:		component vitals needed by the framework.
 * @spinlock:		only one at a समय pls.
 * @chs:		the channels accociated to this STM.
 * @sपंचांग:		काष्ठाure associated to the generic STM पूर्णांकerface.
 * @mode:		this tracer's mode, i.e sysFS, or disabled.
 * @traceid:		value of the current ID क्रम this component.
 * @ग_लिखो_bytes:	Maximus bytes this STM can ग_लिखो at a समय.
 * @sपंचांगsper:		settings क्रम रेजिस्टर STMSPER.
 * @sपंचांगspscr:		settings क्रम रेजिस्टर STMSPSCR.
 * @numsp:		the total number of stimulus port support by this STM.
 * @sपंचांगheer:		settings क्रम रेजिस्टर STMHEER.
 * @sपंचांगheter:		settings क्रम रेजिस्टर STMHETER.
 * @sपंचांगhebsr:		settings क्रम रेजिस्टर STMHEBSR.
 */
काष्ठा sपंचांग_drvdata अणु
	व्योम __iomem		*base;
	काष्ठा clk		*atclk;
	काष्ठा coresight_device	*csdev;
	spinlock_t		spinlock;
	काष्ठा channel_space	chs;
	काष्ठा sपंचांग_data		sपंचांग;
	local_t			mode;
	u8			traceid;
	u32			ग_लिखो_bytes;
	u32			sपंचांगsper;
	u32			sपंचांगspscr;
	u32			numsp;
	u32			sपंचांगheer;
	u32			sपंचांगheter;
	u32			sपंचांगhebsr;
पूर्ण;

अटल व्योम sपंचांग_hwevent_enable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	ग_लिखोl_relaxed(drvdata->sपंचांगhebsr, drvdata->base + STMHEBSR);
	ग_लिखोl_relaxed(drvdata->sपंचांगheter, drvdata->base + STMHETER);
	ग_लिखोl_relaxed(drvdata->sपंचांगheer, drvdata->base + STMHEER);
	ग_लिखोl_relaxed(0x01 |	/* Enable HW event tracing */
		       0x04,	/* Error detection on event tracing */
		       drvdata->base + STMHEMCR);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम sपंचांग_port_enable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);
	/* ATB trigger enable on direct ग_लिखोs to TRIG locations */
	ग_लिखोl_relaxed(0x10,
		       drvdata->base + STMSPTRIGCSR);
	ग_लिखोl_relaxed(drvdata->sपंचांगspscr, drvdata->base + STMSPSCR);
	ग_लिखोl_relaxed(drvdata->sपंचांगsper, drvdata->base + STMSPER);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम sपंचांग_enable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	अगर (drvdata->sपंचांगheer)
		sपंचांग_hwevent_enable_hw(drvdata);

	sपंचांग_port_enable_hw(drvdata);

	CS_UNLOCK(drvdata->base);

	/* 4096 byte between synchronisation packets */
	ग_लिखोl_relaxed(0xFFF, drvdata->base + STMSYNCR);
	ग_लिखोl_relaxed((drvdata->traceid << 16 | /* trace id */
			0x02 |			 /* बारtamp enable */
			0x01),			 /* global STM enable */
			drvdata->base + STMTCSR);

	CS_LOCK(drvdata->base);
पूर्ण

अटल पूर्णांक sपंचांग_enable(काष्ठा coresight_device *csdev,
		      काष्ठा perf_event *event, u32 mode)
अणु
	u32 val;
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	अगर (mode != CS_MODE_SYSFS)
		वापस -EINVAL;

	val = local_cmpxchg(&drvdata->mode, CS_MODE_DISABLED, mode);

	/* Someone is alपढ़ोy using the tracer */
	अगर (val)
		वापस -EBUSY;

	pm_runसमय_get_sync(csdev->dev.parent);

	spin_lock(&drvdata->spinlock);
	sपंचांग_enable_hw(drvdata);
	spin_unlock(&drvdata->spinlock);

	dev_dbg(&csdev->dev, "STM tracing enabled\n");
	वापस 0;
पूर्ण

अटल व्योम sपंचांग_hwevent_disable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	ग_लिखोl_relaxed(0x0, drvdata->base + STMHEMCR);
	ग_लिखोl_relaxed(0x0, drvdata->base + STMHEER);
	ग_लिखोl_relaxed(0x0, drvdata->base + STMHETER);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम sपंचांग_port_disable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	CS_UNLOCK(drvdata->base);

	ग_लिखोl_relaxed(0x0, drvdata->base + STMSPER);
	ग_लिखोl_relaxed(0x0, drvdata->base + STMSPTRIGCSR);

	CS_LOCK(drvdata->base);
पूर्ण

अटल व्योम sपंचांग_disable_hw(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	u32 val;

	CS_UNLOCK(drvdata->base);

	val = पढ़ोl_relaxed(drvdata->base + STMTCSR);
	val &= ~0x1; /* clear global STM enable [0] */
	ग_लिखोl_relaxed(val, drvdata->base + STMTCSR);

	CS_LOCK(drvdata->base);

	sपंचांग_port_disable_hw(drvdata);
	अगर (drvdata->sपंचांगheer)
		sपंचांग_hwevent_disable_hw(drvdata);
पूर्ण

अटल व्योम sपंचांग_disable(काष्ठा coresight_device *csdev,
			काष्ठा perf_event *event)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा csdev_access *csa = &csdev->access;

	/*
	 * For as दीर्घ as the tracer isn't disabled another entity can't
	 * change its status.  As such we can पढ़ो the status here without
	 * fearing it will change under us.
	 */
	अगर (local_पढ़ो(&drvdata->mode) == CS_MODE_SYSFS) अणु
		spin_lock(&drvdata->spinlock);
		sपंचांग_disable_hw(drvdata);
		spin_unlock(&drvdata->spinlock);

		/* Wait until the engine has completely stopped */
		coresight_समयout(csa, STMTCSR, STMTCSR_BUSY_BIT, 0);

		pm_runसमय_put(csdev->dev.parent);

		local_set(&drvdata->mode, CS_MODE_DISABLED);
		dev_dbg(&csdev->dev, "STM tracing disabled\n");
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग_trace_id(काष्ठा coresight_device *csdev)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	वापस drvdata->traceid;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_source sपंचांग_source_ops = अणु
	.trace_id	= sपंचांग_trace_id,
	.enable		= sपंचांग_enable,
	.disable	= sपंचांग_disable,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops sपंचांग_cs_ops = अणु
	.source_ops	= &sपंचांग_source_ops,
पूर्ण;

अटल अंतरभूत bool sपंचांग_addr_unaligned(स्थिर व्योम *addr, u8 ग_लिखो_bytes)
अणु
	वापस ((अचिन्हित दीर्घ)addr & (ग_लिखो_bytes - 1));
पूर्ण

अटल व्योम sपंचांग_send(व्योम __iomem *addr, स्थिर व्योम *data,
		     u32 size, u8 ग_लिखो_bytes)
अणु
	u8 paload[8];

	अगर (sपंचांग_addr_unaligned(data, ग_लिखो_bytes)) अणु
		स_नकल(paload, data, size);
		data = paload;
	पूर्ण

	/* now we are 64bit/32bit aligned */
	चयन (size) अणु
#अगर_घोषित CONFIG_64BIT
	हाल 8:
		ग_लिखोq_relaxed(*(u64 *)data, addr);
		अवरोध;
#पूर्ण_अगर
	हाल 4:
		ग_लिखोl_relaxed(*(u32 *)data, addr);
		अवरोध;
	हाल 2:
		ग_लिखोw_relaxed(*(u16 *)data, addr);
		अवरोध;
	हाल 1:
		ग_लिखोb_relaxed(*(u8 *)data, addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग_generic_link(काष्ठा sपंचांग_data *sपंचांग_data,
			    अचिन्हित पूर्णांक master,  अचिन्हित पूर्णांक channel)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = container_of(sपंचांग_data,
						   काष्ठा sपंचांग_drvdata, sपंचांग);
	अगर (!drvdata || !drvdata->csdev)
		वापस -EINVAL;

	वापस coresight_enable(drvdata->csdev);
पूर्ण

अटल व्योम sपंचांग_generic_unlink(काष्ठा sपंचांग_data *sपंचांग_data,
			       अचिन्हित पूर्णांक master,  अचिन्हित पूर्णांक channel)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = container_of(sपंचांग_data,
						   काष्ठा sपंचांग_drvdata, sपंचांग);
	अगर (!drvdata || !drvdata->csdev)
		वापस;

	coresight_disable(drvdata->csdev);
पूर्ण

अटल phys_addr_t
sपंचांग_mmio_addr(काष्ठा sपंचांग_data *sपंचांग_data, अचिन्हित पूर्णांक master,
	      अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक nr_chans)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = container_of(sपंचांग_data,
						   काष्ठा sपंचांग_drvdata, sपंचांग);
	phys_addr_t addr;

	addr = drvdata->chs.phys + channel * BYTES_PER_CHANNEL;

	अगर (offset_in_page(addr) ||
	    offset_in_page(nr_chans * BYTES_PER_CHANNEL))
		वापस 0;

	वापस addr;
पूर्ण

अटल दीर्घ sपंचांग_generic_set_options(काष्ठा sपंचांग_data *sपंचांग_data,
				    अचिन्हित पूर्णांक master,
				    अचिन्हित पूर्णांक channel,
				    अचिन्हित पूर्णांक nr_chans,
				    अचिन्हित दीर्घ options)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = container_of(sपंचांग_data,
						   काष्ठा sपंचांग_drvdata, sपंचांग);
	अगर (!(drvdata && local_पढ़ो(&drvdata->mode)))
		वापस -EINVAL;

	अगर (channel >= drvdata->numsp)
		वापस -EINVAL;

	चयन (options) अणु
	हाल STM_OPTION_GUARANTEED:
		set_bit(channel, drvdata->chs.guaranteed);
		अवरोध;

	हाल STM_OPTION_INVARIANT:
		clear_bit(channel, drvdata->chs.guaranteed);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार notrace sपंचांग_generic_packet(काष्ठा sपंचांग_data *sपंचांग_data,
				  अचिन्हित पूर्णांक master,
				  अचिन्हित पूर्णांक channel,
				  अचिन्हित पूर्णांक packet,
				  अचिन्हित पूर्णांक flags,
				  अचिन्हित पूर्णांक size,
				  स्थिर अचिन्हित अक्षर *payload)
अणु
	व्योम __iomem *ch_addr;
	काष्ठा sपंचांग_drvdata *drvdata = container_of(sपंचांग_data,
						   काष्ठा sपंचांग_drvdata, sपंचांग);
	अचिन्हित पूर्णांक sपंचांग_flags;

	अगर (!(drvdata && local_पढ़ो(&drvdata->mode)))
		वापस -EACCES;

	अगर (channel >= drvdata->numsp)
		वापस -EINVAL;

	ch_addr = sपंचांग_channel_addr(drvdata, channel);

	sपंचांग_flags = (flags & STP_PACKET_TIMESTAMPED) ?
			STM_FLAG_TIMESTAMPED : 0;
	sपंचांग_flags |= test_bit(channel, drvdata->chs.guaranteed) ?
			   STM_FLAG_GUARANTEED : 0;

	अगर (size > drvdata->ग_लिखो_bytes)
		size = drvdata->ग_लिखो_bytes;
	अन्यथा
		size = roundकरोwn_घात_of_two(size);

	चयन (packet) अणु
	हाल STP_PACKET_FLAG:
		ch_addr += sपंचांग_channel_off(STM_PKT_TYPE_FLAG, sपंचांग_flags);

		/*
		 * The generic STM core sets a size of '0' on flag packets.
		 * As such send a flag packet of size '1' and tell the
		 * core we did so.
		 */
		sपंचांग_send(ch_addr, payload, 1, drvdata->ग_लिखो_bytes);
		size = 1;
		अवरोध;

	हाल STP_PACKET_DATA:
		sपंचांग_flags |= (flags & STP_PACKET_MARKED) ? STM_FLAG_MARKED : 0;
		ch_addr += sपंचांग_channel_off(STM_PKT_TYPE_DATA, sपंचांग_flags);
		sपंचांग_send(ch_addr, payload, size,
				drvdata->ग_लिखो_bytes);
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस size;
पूर्ण

अटल sमाप_प्रकार hwevent_enable_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val = drvdata->sपंचांगheer;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार hwevent_enable_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 0;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस -EINVAL;

	drvdata->sपंचांगheer = val;
	/* HW event enable and trigger go hand in hand */
	drvdata->sपंचांगheter = val;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(hwevent_enable);

अटल sमाप_प्रकार hwevent_select_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val = drvdata->sपंचांगhebsr;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार hwevent_select_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 0;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस -EINVAL;

	drvdata->sपंचांगhebsr = val;

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(hwevent_select);

अटल sमाप_प्रकार port_select_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val;

	अगर (!local_पढ़ो(&drvdata->mode)) अणु
		val = drvdata->sपंचांगspscr;
	पूर्ण अन्यथा अणु
		spin_lock(&drvdata->spinlock);
		val = पढ़ोl_relaxed(drvdata->base + STMSPSCR);
		spin_unlock(&drvdata->spinlock);
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार port_select_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val, sपंचांगsper;
	पूर्णांक ret = 0;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	drvdata->sपंचांगspscr = val;

	अगर (local_पढ़ो(&drvdata->mode)) अणु
		CS_UNLOCK(drvdata->base);
		/* Process as per ARM's TRM recommendation */
		sपंचांगsper = पढ़ोl_relaxed(drvdata->base + STMSPER);
		ग_लिखोl_relaxed(0x0, drvdata->base + STMSPER);
		ग_लिखोl_relaxed(drvdata->sपंचांगspscr, drvdata->base + STMSPSCR);
		ग_लिखोl_relaxed(sपंचांगsper, drvdata->base + STMSPER);
		CS_LOCK(drvdata->base);
	पूर्ण
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(port_select);

अटल sमाप_प्रकार port_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val;

	अगर (!local_पढ़ो(&drvdata->mode)) अणु
		val = drvdata->sपंचांगsper;
	पूर्ण अन्यथा अणु
		spin_lock(&drvdata->spinlock);
		val = पढ़ोl_relaxed(drvdata->base + STMSPER);
		spin_unlock(&drvdata->spinlock);
	पूर्ण

	वापस scnम_लिखो(buf, PAGE_SIZE, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार port_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = 0;

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	spin_lock(&drvdata->spinlock);
	drvdata->sपंचांगsper = val;

	अगर (local_पढ़ो(&drvdata->mode)) अणु
		CS_UNLOCK(drvdata->base);
		ग_लिखोl_relaxed(drvdata->sपंचांगsper, drvdata->base + STMSPER);
		CS_LOCK(drvdata->base);
	पूर्ण
	spin_unlock(&drvdata->spinlock);

	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(port_enable);

अटल sमाप_प्रकार traceid_show(काष्ठा device *dev,
			    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित दीर्घ val;
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	val = drvdata->traceid;
	वापस प्र_लिखो(buf, "%#lx\n", val);
पूर्ण

अटल sमाप_प्रकार traceid_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ val;
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kम_से_अदीर्घ(buf, 16, &val);
	अगर (ret)
		वापस ret;

	/* traceid field is 7bit wide on STM32 */
	drvdata->traceid = val & 0x7f;
	वापस size;
पूर्ण
अटल DEVICE_ATTR_RW(traceid);

#घोषणा coresight_sपंचांग_reg(name, offset)	\
	coresight_simple_reg32(काष्ठा sपंचांग_drvdata, name, offset)

coresight_sपंचांग_reg(tcsr, STMTCSR);
coresight_sपंचांग_reg(tsfreqr, STMTSFREQR);
coresight_sपंचांग_reg(syncr, STMSYNCR);
coresight_sपंचांग_reg(sper, STMSPER);
coresight_sपंचांग_reg(spter, STMSPTER);
coresight_sपंचांग_reg(privmaskr, STMPRIVMASKR);
coresight_sपंचांग_reg(spscr, STMSPSCR);
coresight_sपंचांग_reg(spmscr, STMSPMSCR);
coresight_sपंचांग_reg(spfeat1r, STMSPFEAT1R);
coresight_sपंचांग_reg(spfeat2r, STMSPFEAT2R);
coresight_sपंचांग_reg(spfeat3r, STMSPFEAT3R);
coresight_sपंचांग_reg(devid, CORESIGHT_DEVID);

अटल काष्ठा attribute *coresight_sपंचांग_attrs[] = अणु
	&dev_attr_hwevent_enable.attr,
	&dev_attr_hwevent_select.attr,
	&dev_attr_port_enable.attr,
	&dev_attr_port_select.attr,
	&dev_attr_traceid.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *coresight_sपंचांग_mgmt_attrs[] = अणु
	&dev_attr_tcsr.attr,
	&dev_attr_tsfreqr.attr,
	&dev_attr_syncr.attr,
	&dev_attr_sper.attr,
	&dev_attr_spter.attr,
	&dev_attr_privmaskr.attr,
	&dev_attr_spscr.attr,
	&dev_attr_spmscr.attr,
	&dev_attr_spfeat1r.attr,
	&dev_attr_spfeat2r.attr,
	&dev_attr_spfeat3r.attr,
	&dev_attr_devid.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_sपंचांग_group = अणु
	.attrs = coresight_sपंचांग_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group coresight_sपंचांग_mgmt_group = अणु
	.attrs = coresight_sपंचांग_mgmt_attrs,
	.name = "mgmt",
पूर्ण;

अटल स्थिर काष्ठा attribute_group *coresight_sपंचांग_groups[] = अणु
	&coresight_sपंचांग_group,
	&coresight_sपंचांग_mgmt_group,
	शून्य,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक of_sपंचांग_get_stimulus_area(काष्ठा device *dev, काष्ठा resource *res)
अणु
	स्थिर अक्षर *name = शून्य;
	पूर्णांक index = 0, found = 0;
	काष्ठा device_node *np = dev->of_node;

	जबतक (!of_property_पढ़ो_string_index(np, "reg-names", index, &name)) अणु
		अगर (म_भेद("stm-stimulus-base", name)) अणु
			index++;
			जारी;
		पूर्ण

		/* We have a match and @index is where it's at */
		found = 1;
		अवरोध;
	पूर्ण

	अगर (!found)
		वापस -EINVAL;

	वापस of_address_to_resource(np, index, res);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक of_sपंचांग_get_stimulus_area(काष्ठा device *dev,
					   काष्ठा resource *res)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल पूर्णांक acpi_sपंचांग_get_stimulus_area(काष्ठा device *dev, काष्ठा resource *res)
अणु
	पूर्णांक rc;
	bool found_base = false;
	काष्ठा resource_entry *rent;
	LIST_HEAD(res_list);

	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	rc = acpi_dev_get_resources(adev, &res_list, शून्य, शून्य);
	अगर (rc < 0)
		वापस rc;

	/*
	 * The stimulus base क्रम STM device must be listed as the second memory
	 * resource, followed by the programming base address as described in
	 * "Section 2.3 Resources" in ACPI क्रम CoreSightTM 1.0 Platक्रमm Design
	 * करोcument (DEN0067).
	 */
	rc = -ENOENT;
	list_क्रम_each_entry(rent, &res_list, node) अणु
		अगर (resource_type(rent->res) != IORESOURCE_MEM)
			जारी;
		अगर (found_base) अणु
			*res = *rent->res;
			rc = 0;
			अवरोध;
		पूर्ण

		found_base = true;
	पूर्ण

	acpi_dev_मुक्त_resource_list(&res_list);
	वापस rc;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_sपंचांग_get_stimulus_area(काष्ठा device *dev,
					     काष्ठा resource *res)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक sपंचांग_get_stimulus_area(काष्ठा device *dev, काष्ठा resource *res)
अणु
	काष्ठा fwnode_handle *fwnode = dev_fwnode(dev);

	अगर (is_of_node(fwnode))
		वापस of_sपंचांग_get_stimulus_area(dev, res);
	अन्यथा अगर (is_acpi_node(fwnode))
		वापस acpi_sपंचांग_get_stimulus_area(dev, res);
	वापस -ENOENT;
पूर्ण

अटल u32 sपंचांग_fundamental_data_size(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	u32 sपंचांगspfeat2r;

	अगर (!IS_ENABLED(CONFIG_64BIT))
		वापस 4;

	sपंचांगspfeat2r = पढ़ोl_relaxed(drvdata->base + STMSPFEAT2R);

	/*
	 * bit[15:12] represents the fundamental data size
	 * 0 - 32-bit data
	 * 1 - 64-bit data
	 */
	वापस BMVAL(sपंचांगspfeat2r, 12, 15) ? 8 : 4;
पूर्ण

अटल u32 sपंचांग_num_stimulus_port(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	u32 numsp;

	numsp = पढ़ोl_relaxed(drvdata->base + CORESIGHT_DEVID);
	/*
	 * NUMPS in STMDEVID is 17 bit दीर्घ and अगर equal to 0x0,
	 * 32 stimulus ports are supported.
	 */
	numsp &= 0x1ffff;
	अगर (!numsp)
		numsp = STM_32_CHANNEL;
	वापस numsp;
पूर्ण

अटल व्योम sपंचांग_init_शेष_data(काष्ठा sपंचांग_drvdata *drvdata)
अणु
	/* Don't use port selection */
	drvdata->sपंचांगspscr = 0x0;
	/*
	 * Enable all channel regardless of their number.  When port
	 * selection isn't used (see above) STMSPER applies to all
	 * 32 channel group available, hence setting all 32 bits to 1
	 */
	drvdata->sपंचांगsper = ~0x0;

	/*
	 * The trace ID value क्रम *ETM* tracers start at CPU_ID * 2 + 0x10 and
	 * anything equal to or higher than 0x70 is reserved.  Since 0x00 is
	 * also reserved the STM trace ID needs to be higher than 0x00 and
	 * lowner than 0x10.
	 */
	drvdata->traceid = 0x1;

	/* Set invariant transaction timing on all channels */
	biपंचांगap_clear(drvdata->chs.guaranteed, 0, drvdata->numsp);
पूर्ण

अटल व्योम sपंचांग_init_generic_data(काष्ठा sपंचांग_drvdata *drvdata,
				  स्थिर अक्षर *name)
अणु
	drvdata->sपंचांग.name = name;

	/*
	 * MasterIDs are asचिन्हित at HW design phase. As such the core is
	 * using a single master क्रम पूर्णांकeraction with this device.
	 */
	drvdata->sपंचांग.sw_start = 1;
	drvdata->sपंचांग.sw_end = 1;
	drvdata->sपंचांग.hw_override = true;
	drvdata->sपंचांग.sw_nchannels = drvdata->numsp;
	drvdata->sपंचांग.sw_mmiosz = BYTES_PER_CHANNEL;
	drvdata->sपंचांग.packet = sपंचांग_generic_packet;
	drvdata->sपंचांग.mmio_addr = sपंचांग_mmio_addr;
	drvdata->sपंचांग.link = sपंचांग_generic_link;
	drvdata->sपंचांग.unlink = sपंचांग_generic_unlink;
	drvdata->sपंचांग.set_options = sपंचांग_generic_set_options;
पूर्ण

अटल पूर्णांक sपंचांग_probe(काष्ठा amba_device *adev, स्थिर काष्ठा amba_id *id)
अणु
	पूर्णांक ret;
	व्योम __iomem *base;
	अचिन्हित दीर्घ *guaranteed;
	काष्ठा device *dev = &adev->dev;
	काष्ठा coresight_platक्रमm_data *pdata = शून्य;
	काष्ठा sपंचांग_drvdata *drvdata;
	काष्ठा resource *res = &adev->res;
	काष्ठा resource ch_res;
	माप_प्रकार biपंचांगap_size;
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;

	desc.name = coresight_alloc_device_name(&sपंचांग_devs, dev);
	अगर (!desc.name)
		वापस -ENOMEM;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	drvdata->atclk = devm_clk_get(&adev->dev, "atclk"); /* optional */
	अगर (!IS_ERR(drvdata->atclk)) अणु
		ret = clk_prepare_enable(drvdata->atclk);
		अगर (ret)
			वापस ret;
	पूर्ण
	dev_set_drvdata(dev, drvdata);

	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	drvdata->base = base;
	desc.access = CSDEV_ACCESS_IOMEM(base);

	ret = sपंचांग_get_stimulus_area(dev, &ch_res);
	अगर (ret)
		वापस ret;
	drvdata->chs.phys = ch_res.start;

	base = devm_ioremap_resource(dev, &ch_res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);
	drvdata->chs.base = base;

	drvdata->ग_लिखो_bytes = sपंचांग_fundamental_data_size(drvdata);

	अगर (boot_nr_channel)
		drvdata->numsp = boot_nr_channel;
	अन्यथा
		drvdata->numsp = sपंचांग_num_stimulus_port(drvdata);

	biपंचांगap_size = BITS_TO_LONGS(drvdata->numsp) * माप(दीर्घ);

	guaranteed = devm_kzalloc(dev, biपंचांगap_size, GFP_KERNEL);
	अगर (!guaranteed)
		वापस -ENOMEM;
	drvdata->chs.guaranteed = guaranteed;

	spin_lock_init(&drvdata->spinlock);

	sपंचांग_init_शेष_data(drvdata);
	sपंचांग_init_generic_data(drvdata, desc.name);

	अगर (sपंचांग_रेजिस्टर_device(dev, &drvdata->sपंचांग, THIS_MODULE)) अणु
		dev_info(dev,
			 "%s : stm_register_device failed, probing deferred\n",
			 desc.name);
		वापस -EPROBE_DEFER;
	पूर्ण

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata)) अणु
		ret = PTR_ERR(pdata);
		जाओ sपंचांग_unरेजिस्टर;
	पूर्ण
	adev->dev.platक्रमm_data = pdata;

	desc.type = CORESIGHT_DEV_TYPE_SOURCE;
	desc.subtype.source_subtype = CORESIGHT_DEV_SUBTYPE_SOURCE_SOFTWARE;
	desc.ops = &sपंचांग_cs_ops;
	desc.pdata = pdata;
	desc.dev = dev;
	desc.groups = coresight_sपंचांग_groups;
	drvdata->csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(drvdata->csdev)) अणु
		ret = PTR_ERR(drvdata->csdev);
		जाओ sपंचांग_unरेजिस्टर;
	पूर्ण

	pm_runसमय_put(&adev->dev);

	dev_info(&drvdata->csdev->dev, "%s initialized\n",
		 (अक्षर *)coresight_get_uci_data(id));
	वापस 0;

sपंचांग_unरेजिस्टर:
	sपंचांग_unरेजिस्टर_device(&drvdata->sपंचांग);
	वापस ret;
पूर्ण

अटल व्योम sपंचांग_हटाओ(काष्ठा amba_device *adev)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(&adev->dev);

	coresight_unरेजिस्टर(drvdata->csdev);

	sपंचांग_unरेजिस्टर_device(&drvdata->sपंचांग);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग_drvdata *drvdata = dev_get_drvdata(dev);

	अगर (drvdata && !IS_ERR(drvdata->atclk))
		clk_prepare_enable(drvdata->atclk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sपंचांग_runसमय_suspend, sपंचांग_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा amba_id sपंचांग_ids[] = अणु
	CS_AMBA_ID_DATA(0x000bb962, "STM32"),
	CS_AMBA_ID_DATA(0x000bb963, "STM500"),
	अणु 0, 0पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(amba, sपंचांग_ids);

अटल काष्ठा amba_driver sपंचांग_driver = अणु
	.drv = अणु
		.name   = "coresight-stm",
		.owner	= THIS_MODULE,
		.pm	= &sपंचांग_dev_pm_ops,
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe          = sपंचांग_probe,
	.हटाओ         = sपंचांग_हटाओ,
	.id_table	= sपंचांग_ids,
पूर्ण;

module_amba_driver(sपंचांग_driver);

MODULE_AUTHOR("Pratik Patel <pratikp@codeaurora.org>");
MODULE_DESCRIPTION("Arm CoreSight System Trace Macrocell driver");
MODULE_LICENSE("GPL v2");
