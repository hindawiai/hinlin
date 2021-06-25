<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub Software Trace Hub support
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sपंचांग.h>

#समावेश "intel_th.h"
#समावेश "sth.h"

काष्ठा sth_device अणु
	व्योम __iomem	*base;
	व्योम __iomem	*channels;
	phys_addr_t	channels_phys;
	काष्ठा device	*dev;
	काष्ठा sपंचांग_data	sपंचांग;
	अचिन्हित पूर्णांक	sw_nmasters;
पूर्ण;

अटल काष्ठा पूर्णांकel_th_channel __iomem *
sth_channel(काष्ठा sth_device *sth, अचिन्हित पूर्णांक master, अचिन्हित पूर्णांक channel)
अणु
	काष्ठा पूर्णांकel_th_channel __iomem *sw_map = sth->channels;

	वापस &sw_map[(master - sth->sपंचांग.sw_start) * sth->sपंचांग.sw_nchannels +
		       channel];
पूर्ण

अटल व्योम sth_ioग_लिखो(व्योम __iomem *dest, स्थिर अचिन्हित अक्षर *payload,
			अचिन्हित पूर्णांक size)
अणु
	चयन (size) अणु
#अगर_घोषित CONFIG_64BIT
	हाल 8:
		ग_लिखोq_relaxed(*(u64 *)payload, dest);
		अवरोध;
#पूर्ण_अगर
	हाल 4:
		ग_लिखोl_relaxed(*(u32 *)payload, dest);
		अवरोध;
	हाल 2:
		ग_लिखोw_relaxed(*(u16 *)payload, dest);
		अवरोध;
	हाल 1:
		ग_लिखोb_relaxed(*(u8 *)payload, dest);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार notrace sth_sपंचांग_packet(काष्ठा sपंचांग_data *sपंचांग_data,
				      अचिन्हित पूर्णांक master,
				      अचिन्हित पूर्णांक channel,
				      अचिन्हित पूर्णांक packet,
				      अचिन्हित पूर्णांक flags,
				      अचिन्हित पूर्णांक size,
				      स्थिर अचिन्हित अक्षर *payload)
अणु
	काष्ठा sth_device *sth = container_of(sपंचांग_data, काष्ठा sth_device, sपंचांग);
	काष्ठा पूर्णांकel_th_channel __iomem *out =
		sth_channel(sth, master, channel);
	u64 __iomem *outp = &out->Dn;
	अचिन्हित दीर्घ reg = REG_STH_TRIG;

#अगर_अघोषित CONFIG_64BIT
	अगर (size > 4)
		size = 4;
#पूर्ण_अगर

	size = roundकरोwn_घात_of_two(size);

	चयन (packet) अणु
	/* Global packets (GERR, XSYNC, TRIG) are sent with रेजिस्टर ग_लिखोs */
	हाल STP_PACKET_GERR:
		reg += 4;
		fallthrough;

	हाल STP_PACKET_XSYNC:
		reg += 8;
		fallthrough;

	हाल STP_PACKET_TRIG:
		अगर (flags & STP_PACKET_TIMESTAMPED)
			reg += 4;
		ग_लिखोb_relaxed(*payload, sth->base + reg);
		अवरोध;

	हाल STP_PACKET_MERR:
		अगर (size > 4)
			size = 4;

		sth_ioग_लिखो(&out->MERR, payload, size);
		अवरोध;

	हाल STP_PACKET_FLAG:
		अगर (flags & STP_PACKET_TIMESTAMPED)
			outp = (u64 __iomem *)&out->FLAG_TS;
		अन्यथा
			outp = (u64 __iomem *)&out->FLAG;

		size = 0;
		ग_लिखोb_relaxed(0, outp);
		अवरोध;

	हाल STP_PACKET_USER:
		अगर (flags & STP_PACKET_TIMESTAMPED)
			outp = &out->USER_TS;
		अन्यथा
			outp = &out->USER;
		sth_ioग_लिखो(outp, payload, size);
		अवरोध;

	हाल STP_PACKET_DATA:
		outp = &out->Dn;

		अगर (flags & STP_PACKET_TIMESTAMPED)
			outp += 2;
		अगर (flags & STP_PACKET_MARKED)
			outp++;

		sth_ioग_लिखो(outp, payload, size);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस size;
पूर्ण

अटल phys_addr_t
sth_sपंचांग_mmio_addr(काष्ठा sपंचांग_data *sपंचांग_data, अचिन्हित पूर्णांक master,
		  अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक nr_chans)
अणु
	काष्ठा sth_device *sth = container_of(sपंचांग_data, काष्ठा sth_device, sपंचांग);
	phys_addr_t addr;

	master -= sth->sपंचांग.sw_start;
	addr = sth->channels_phys + (master * sth->sपंचांग.sw_nchannels + channel) *
		माप(काष्ठा पूर्णांकel_th_channel);

	अगर (offset_in_page(addr) ||
	    offset_in_page(nr_chans * माप(काष्ठा पूर्णांकel_th_channel)))
		वापस 0;

	वापस addr;
पूर्ण

अटल पूर्णांक sth_sपंचांग_link(काष्ठा sपंचांग_data *sपंचांग_data, अचिन्हित पूर्णांक master,
			 अचिन्हित पूर्णांक channel)
अणु
	काष्ठा sth_device *sth = container_of(sपंचांग_data, काष्ठा sth_device, sपंचांग);

	वापस पूर्णांकel_th_set_output(to_पूर्णांकel_th_device(sth->dev), master);
पूर्ण

अटल पूर्णांक पूर्णांकel_th_sw_init(काष्ठा sth_device *sth)
अणु
	u32 reg;

	reg = ioपढ़ो32(sth->base + REG_STH_STHCAP1);
	sth->sपंचांग.sw_nchannels = reg & 0xff;

	reg = ioपढ़ो32(sth->base + REG_STH_STHCAP0);
	sth->sपंचांग.sw_start = reg & 0xffff;
	sth->sपंचांग.sw_end = reg >> 16;

	sth->sw_nmasters = sth->sपंचांग.sw_end - sth->sपंचांग.sw_start;
	dev_dbg(sth->dev, "sw_start: %x sw_end: %x masters: %x nchannels: %x\n",
		sth->sपंचांग.sw_start, sth->sपंचांग.sw_end, sth->sw_nmasters,
		sth->sपंचांग.sw_nchannels);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_sth_probe(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा device *dev = &thdev->dev;
	काष्ठा sth_device *sth;
	काष्ठा resource *res;
	व्योम __iomem *base, *channels;
	पूर्णांक err;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	base = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!base)
		वापस -ENOMEM;

	res = पूर्णांकel_th_device_get_resource(thdev, IORESOURCE_MEM, 1);
	अगर (!res)
		वापस -ENODEV;

	channels = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!channels)
		वापस -ENOMEM;

	sth = devm_kzalloc(dev, माप(*sth), GFP_KERNEL);
	अगर (!sth)
		वापस -ENOMEM;

	sth->dev = dev;
	sth->base = base;
	sth->channels = channels;
	sth->channels_phys = res->start;
	sth->sपंचांग.name = dev_name(dev);
	sth->sपंचांग.packet = sth_sपंचांग_packet;
	sth->sपंचांग.mmio_addr = sth_sपंचांग_mmio_addr;
	sth->sपंचांग.sw_mmiosz = माप(काष्ठा पूर्णांकel_th_channel);
	sth->sपंचांग.link = sth_sपंचांग_link;

	err = पूर्णांकel_th_sw_init(sth);
	अगर (err)
		वापस err;

	err = sपंचांग_रेजिस्टर_device(dev, &sth->sपंचांग, THIS_MODULE);
	अगर (err) अणु
		dev_err(dev, "stm_register_device failed\n");
		वापस err;
	पूर्ण

	dev_set_drvdata(dev, sth);

	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_th_sth_हटाओ(काष्ठा पूर्णांकel_th_device *thdev)
अणु
	काष्ठा sth_device *sth = dev_get_drvdata(&thdev->dev);

	sपंचांग_unरेजिस्टर_device(&sth->sपंचांग);
पूर्ण

अटल काष्ठा पूर्णांकel_th_driver पूर्णांकel_th_sth_driver = अणु
	.probe	= पूर्णांकel_th_sth_probe,
	.हटाओ	= पूर्णांकel_th_sth_हटाओ,
	.driver	= अणु
		.name	= "sth",
		.owner	= THIS_MODULE,
	पूर्ण,
पूर्ण;

module_driver(पूर्णांकel_th_sth_driver,
	      पूर्णांकel_th_driver_रेजिस्टर,
	      पूर्णांकel_th_driver_unरेजिस्टर);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub Software Trace Hub driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@intel.com>");
