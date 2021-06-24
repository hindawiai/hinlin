<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mfd/mcp-core.c
 *
 *  Copyright (C) 2001 Russell King
 *
 *  Generic MCP (Mulसमयdia Communications Port) layer.  All MCP locking
 *  is solely held within this file.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/smp.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/mfd/mcp.h>


#घोषणा to_mcp(d)		container_of(d, काष्ठा mcp, attached_device)
#घोषणा to_mcp_driver(d)	container_of(d, काष्ठा mcp_driver, drv)

अटल पूर्णांक mcp_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक mcp_bus_probe(काष्ठा device *dev)
अणु
	काष्ठा mcp *mcp = to_mcp(dev);
	काष्ठा mcp_driver *drv = to_mcp_driver(dev->driver);

	वापस drv->probe(mcp);
पूर्ण

अटल पूर्णांक mcp_bus_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा mcp *mcp = to_mcp(dev);
	काष्ठा mcp_driver *drv = to_mcp_driver(dev->driver);

	drv->हटाओ(mcp);
	वापस 0;
पूर्ण

अटल काष्ठा bus_type mcp_bus_type = अणु
	.name		= "mcp",
	.match		= mcp_bus_match,
	.probe		= mcp_bus_probe,
	.हटाओ		= mcp_bus_हटाओ,
पूर्ण;

/**
 *	mcp_set_telecom_भागisor - set the telecom भागisor
 *	@mcp: MCP पूर्णांकerface काष्ठाure
 *	@भाग: SIB घड़ी भागisor
 *
 *	Set the telecom भागisor on the MCP पूर्णांकerface.  The resulting
 *	sample rate is SIBCLOCK/भाग.
 */
व्योम mcp_set_telecom_भागisor(काष्ठा mcp *mcp, अचिन्हित पूर्णांक भाग)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcp->lock, flags);
	mcp->ops->set_telecom_भागisor(mcp, भाग);
	spin_unlock_irqrestore(&mcp->lock, flags);
पूर्ण
EXPORT_SYMBOL(mcp_set_telecom_भागisor);

/**
 *	mcp_set_audio_भागisor - set the audio भागisor
 *	@mcp: MCP पूर्णांकerface काष्ठाure
 *	@भाग: SIB घड़ी भागisor
 *
 *	Set the audio भागisor on the MCP पूर्णांकerface.
 */
व्योम mcp_set_audio_भागisor(काष्ठा mcp *mcp, अचिन्हित पूर्णांक भाग)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcp->lock, flags);
	mcp->ops->set_audio_भागisor(mcp, भाग);
	spin_unlock_irqrestore(&mcp->lock, flags);
पूर्ण
EXPORT_SYMBOL(mcp_set_audio_भागisor);

/**
 *	mcp_reg_ग_लिखो - ग_लिखो a device रेजिस्टर
 *	@mcp: MCP पूर्णांकerface काष्ठाure
 *	@reg: 4-bit रेजिस्टर index
 *	@val: 16-bit data value
 *
 *	Write a device रेजिस्टर.  The MCP पूर्णांकerface must be enabled
 *	to prevent this function hanging.
 */
व्योम mcp_reg_ग_लिखो(काष्ठा mcp *mcp, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcp->lock, flags);
	mcp->ops->reg_ग_लिखो(mcp, reg, val);
	spin_unlock_irqrestore(&mcp->lock, flags);
पूर्ण
EXPORT_SYMBOL(mcp_reg_ग_लिखो);

/**
 *	mcp_reg_पढ़ो - पढ़ो a device रेजिस्टर
 *	@mcp: MCP पूर्णांकerface काष्ठाure
 *	@reg: 4-bit रेजिस्टर index
 *
 *	Read a device रेजिस्टर and वापस its value.  The MCP पूर्णांकerface
 *	must be enabled to prevent this function hanging.
 */
अचिन्हित पूर्णांक mcp_reg_पढ़ो(काष्ठा mcp *mcp, अचिन्हित पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&mcp->lock, flags);
	val = mcp->ops->reg_पढ़ो(mcp, reg);
	spin_unlock_irqrestore(&mcp->lock, flags);

	वापस val;
पूर्ण
EXPORT_SYMBOL(mcp_reg_पढ़ो);

/**
 *	mcp_enable - enable the MCP पूर्णांकerface
 *	@mcp: MCP पूर्णांकerface to enable
 *
 *	Enable the MCP पूर्णांकerface.  Each call to mcp_enable will need
 *	a corresponding call to mcp_disable to disable the पूर्णांकerface.
 */
व्योम mcp_enable(काष्ठा mcp *mcp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcp->lock, flags);
	अगर (mcp->use_count++ == 0)
		mcp->ops->enable(mcp);
	spin_unlock_irqrestore(&mcp->lock, flags);
पूर्ण
EXPORT_SYMBOL(mcp_enable);

/**
 *	mcp_disable - disable the MCP पूर्णांकerface
 *	@mcp: MCP पूर्णांकerface to disable
 *
 *	Disable the MCP पूर्णांकerface.  The MCP पूर्णांकerface will only be
 *	disabled once the number of calls to mcp_enable matches the
 *	number of calls to mcp_disable.
 */
व्योम mcp_disable(काष्ठा mcp *mcp)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mcp->lock, flags);
	अगर (--mcp->use_count == 0)
		mcp->ops->disable(mcp);
	spin_unlock_irqrestore(&mcp->lock, flags);
पूर्ण
EXPORT_SYMBOL(mcp_disable);

अटल व्योम mcp_release(काष्ठा device *dev)
अणु
	काष्ठा mcp *mcp = container_of(dev, काष्ठा mcp, attached_device);

	kमुक्त(mcp);
पूर्ण

काष्ठा mcp *mcp_host_alloc(काष्ठा device *parent, माप_प्रकार size)
अणु
	काष्ठा mcp *mcp;

	mcp = kzalloc(माप(काष्ठा mcp) + size, GFP_KERNEL);
	अगर (mcp) अणु
		spin_lock_init(&mcp->lock);
		device_initialize(&mcp->attached_device);
		mcp->attached_device.parent = parent;
		mcp->attached_device.bus = &mcp_bus_type;
		mcp->attached_device.dma_mask = parent->dma_mask;
		mcp->attached_device.release = mcp_release;
	पूर्ण
	वापस mcp;
पूर्ण
EXPORT_SYMBOL(mcp_host_alloc);

पूर्णांक mcp_host_add(काष्ठा mcp *mcp, व्योम *pdata)
अणु
	mcp->attached_device.platक्रमm_data = pdata;
	dev_set_name(&mcp->attached_device, "mcp0");
	वापस device_add(&mcp->attached_device);
पूर्ण
EXPORT_SYMBOL(mcp_host_add);

व्योम mcp_host_del(काष्ठा mcp *mcp)
अणु
	device_del(&mcp->attached_device);
पूर्ण
EXPORT_SYMBOL(mcp_host_del);

व्योम mcp_host_मुक्त(काष्ठा mcp *mcp)
अणु
	put_device(&mcp->attached_device);
पूर्ण
EXPORT_SYMBOL(mcp_host_मुक्त);

पूर्णांक mcp_driver_रेजिस्टर(काष्ठा mcp_driver *mcpdrv)
अणु
	mcpdrv->drv.bus = &mcp_bus_type;
	वापस driver_रेजिस्टर(&mcpdrv->drv);
पूर्ण
EXPORT_SYMBOL(mcp_driver_रेजिस्टर);

व्योम mcp_driver_unरेजिस्टर(काष्ठा mcp_driver *mcpdrv)
अणु
	driver_unरेजिस्टर(&mcpdrv->drv);
पूर्ण
EXPORT_SYMBOL(mcp_driver_unरेजिस्टर);

अटल पूर्णांक __init mcp_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&mcp_bus_type);
पूर्ण

अटल व्योम __निकास mcp_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&mcp_bus_type);
पूर्ण

module_init(mcp_init);
module_निकास(mcp_निकास);

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_DESCRIPTION("Core multimedia communications port driver");
MODULE_LICENSE("GPL");
