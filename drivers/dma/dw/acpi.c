<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2013,2019 Intel Corporation

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_dma.h>

#समावेश "internal.h"

अटल bool dw_dma_acpi_filter(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा acpi_dma_spec *dma_spec = param;
	काष्ठा dw_dma_slave slave = अणु
		.dma_dev = dma_spec->dev,
		.src_id = dma_spec->slave_id,
		.dst_id = dma_spec->slave_id,
		.m_master = 0,
		.p_master = 1,
	पूर्ण;

	वापस dw_dma_filter(chan, &slave);
पूर्ण

व्योम dw_dma_acpi_controller_रेजिस्टर(काष्ठा dw_dma *dw)
अणु
	काष्ठा device *dev = dw->dma.dev;
	काष्ठा acpi_dma_filter_info *info;
	पूर्णांक ret;

	अगर (!has_acpi_companion(dev))
		वापस;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस;

	dma_cap_zero(info->dma_cap);
	dma_cap_set(DMA_SLAVE, info->dma_cap);
	info->filter_fn = dw_dma_acpi_filter;

	ret = acpi_dma_controller_रेजिस्टर(dev, acpi_dma_simple_xlate, info);
	अगर (ret)
		dev_err(dev, "could not register acpi_dma_controller\n");
पूर्ण
EXPORT_SYMBOL_GPL(dw_dma_acpi_controller_रेजिस्टर);

व्योम dw_dma_acpi_controller_मुक्त(काष्ठा dw_dma *dw)
अणु
	काष्ठा device *dev = dw->dma.dev;

	अगर (!has_acpi_companion(dev))
		वापस;

	acpi_dma_controller_मुक्त(dev);
पूर्ण
EXPORT_SYMBOL_GPL(dw_dma_acpi_controller_मुक्त);
