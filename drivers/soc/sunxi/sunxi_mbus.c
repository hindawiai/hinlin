<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2020 Maxime Ripard <maxime@cerno.tech> */

#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/init.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर अक्षर * स्थिर sunxi_mbus_devices[] = अणु
	/*
	 * The display engine भव devices are not strictly speaking
	 * connected to the MBUS, but since DRM will perक्रमm all the
	 * memory allocations and DMA operations through that device, we
	 * need to have the quirk on those devices too.
	 */
	"allwinner,sun4i-a10-display-engine",
	"allwinner,sun5i-a10s-display-engine",
	"allwinner,sun5i-a13-display-engine",
	"allwinner,sun6i-a31-display-engine",
	"allwinner,sun6i-a31s-display-engine",
	"allwinner,sun7i-a20-display-engine",
	"allwinner,sun8i-a23-display-engine",
	"allwinner,sun8i-a33-display-engine",
	"allwinner,sun9i-a80-display-engine",

	/*
	 * And now we have the regular devices connected to the MBUS
	 * (that we know of).
	 */
	"allwinner,sun4i-a10-csi1",
	"allwinner,sun4i-a10-display-backend",
	"allwinner,sun4i-a10-display-frontend",
	"allwinner,sun4i-a10-video-engine",
	"allwinner,sun5i-a13-display-backend",
	"allwinner,sun5i-a13-video-engine",
	"allwinner,sun6i-a31-csi",
	"allwinner,sun6i-a31-display-backend",
	"allwinner,sun7i-a20-csi0",
	"allwinner,sun7i-a20-display-backend",
	"allwinner,sun7i-a20-display-frontend",
	"allwinner,sun7i-a20-video-engine",
	"allwinner,sun8i-a23-display-backend",
	"allwinner,sun8i-a23-display-frontend",
	"allwinner,sun8i-a33-display-backend",
	"allwinner,sun8i-a33-display-frontend",
	"allwinner,sun8i-a33-video-engine",
	"allwinner,sun8i-a83t-csi",
	"allwinner,sun8i-h3-csi",
	"allwinner,sun8i-h3-video-engine",
	"allwinner,sun8i-v3s-csi",
	"allwinner,sun9i-a80-display-backend",
	"allwinner,sun50i-a64-csi",
	"allwinner,sun50i-a64-video-engine",
	"allwinner,sun50i-h5-video-engine",
	शून्य,
पूर्ण;

अटल पूर्णांक sunxi_mbus_notअगरier(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *__dev)
अणु
	काष्ठा device *dev = __dev;
	पूर्णांक ret;

	अगर (event != BUS_NOTIFY_ADD_DEVICE)
		वापस NOTIFY_DONE;

	/*
	 * Only the devices that need a large memory bandwidth करो DMA
	 * directly over the memory bus (called MBUS), instead of going
	 * through the regular प्रणाली bus.
	 */
	अगर (!of_device_compatible_match(dev->of_node, sunxi_mbus_devices))
		वापस NOTIFY_DONE;

	/*
	 * Devices with an पूर्णांकerconnects property have the MBUS
	 * relationship described in their DT and dealt with by
	 * of_dma_configure, so we can just skip them.
	 *
	 * Older DTs or SoCs who are not clearly understood need to set
	 * that DMA offset though.
	 */
	अगर (of_find_property(dev->of_node, "interconnects", शून्य))
		वापस NOTIFY_DONE;

	ret = dma_direct_set_offset(dev, PHYS_OFFSET, 0, SZ_4G);
	अगर (ret)
		dev_err(dev, "Couldn't setup our DMA offset: %d\n", ret);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block sunxi_mbus_nb = अणु
	.notअगरier_call = sunxi_mbus_notअगरier,
पूर्ण;

अटल स्थिर अक्षर * स्थिर sunxi_mbus_platक्रमms[] __initस्थिर = अणु
	"allwinner,sun4i-a10",
	"allwinner,sun5i-a10s",
	"allwinner,sun5i-a13",
	"allwinner,sun6i-a31",
	"allwinner,sun7i-a20",
	"allwinner,sun8i-a23",
	"allwinner,sun8i-a33",
	"allwinner,sun8i-a83t",
	"allwinner,sun8i-h3",
	"allwinner,sun8i-r40",
	"allwinner,sun8i-v3",
	"allwinner,sun8i-v3s",
	"allwinner,sun9i-a80",
	"allwinner,sun50i-a64",
	"allwinner,sun50i-h5",
	"nextthing,gr8",
	शून्य,
पूर्ण;

अटल पूर्णांक __init sunxi_mbus_init(व्योम)
अणु
	अगर (!of_device_compatible_match(of_root, sunxi_mbus_platक्रमms))
		वापस 0;

	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &sunxi_mbus_nb);
	वापस 0;
पूर्ण
arch_initcall(sunxi_mbus_init);
