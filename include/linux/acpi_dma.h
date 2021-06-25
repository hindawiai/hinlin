<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ACPI helpers क्रम DMA request / controller
 *
 * Based on of_dma.h
 *
 * Copyright (C) 2013, Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#अगर_अघोषित __LINUX_ACPI_DMA_H
#घोषणा __LINUX_ACPI_DMA_H

#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/dmaengine.h>

/**
 * काष्ठा acpi_dma_spec - slave device DMA resources
 * @chan_id:	channel unique id
 * @slave_id:	request line unique id
 * @dev:	काष्ठा device of the DMA controller to be used in the filter
 *		function
 */
काष्ठा acpi_dma_spec अणु
	पूर्णांक		chan_id;
	पूर्णांक		slave_id;
	काष्ठा device	*dev;
पूर्ण;

/**
 * काष्ठा acpi_dma - representation of the रेजिस्टरed DMAC
 * @dma_controllers:	linked list node
 * @dev:		काष्ठा device of this controller
 * @acpi_dma_xlate:	callback function to find a suitable channel
 * @data:		निजी data used by a callback function
 * @base_request_line:	first supported request line (CSRT)
 * @end_request_line:	last supported request line (CSRT)
 */
काष्ठा acpi_dma अणु
	काष्ठा list_head	dma_controllers;
	काष्ठा device		*dev;
	काष्ठा dma_chan		*(*acpi_dma_xlate)
				(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *);
	व्योम			*data;
	अचिन्हित लघु		base_request_line;
	अचिन्हित लघु		end_request_line;
पूर्ण;

/* Used with acpi_dma_simple_xlate() */
काष्ठा acpi_dma_filter_info अणु
	dma_cap_mask_t	dma_cap;
	dma_filter_fn	filter_fn;
पूर्ण;

#अगर_घोषित CONFIG_DMA_ACPI

पूर्णांक acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data);
पूर्णांक acpi_dma_controller_मुक्त(काष्ठा device *dev);
पूर्णांक devm_acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data);
व्योम devm_acpi_dma_controller_मुक्त(काष्ठा device *dev);

काष्ठा dma_chan *acpi_dma_request_slave_chan_by_index(काष्ठा device *dev,
						      माप_प्रकार index);
काष्ठा dma_chan *acpi_dma_request_slave_chan_by_name(काष्ठा device *dev,
						     स्थिर अक्षर *name);

काष्ठा dma_chan *acpi_dma_simple_xlate(काष्ठा acpi_dma_spec *dma_spec,
				       काष्ठा acpi_dma *adma);
#अन्यथा

अटल अंतरभूत पूर्णांक acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_dma_controller_मुक्त(काष्ठा device *dev)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत पूर्णांक devm_acpi_dma_controller_रेजिस्टर(काष्ठा device *dev,
		काष्ठा dma_chan *(*acpi_dma_xlate)
		(काष्ठा acpi_dma_spec *, काष्ठा acpi_dma *),
		व्योम *data)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम devm_acpi_dma_controller_मुक्त(काष्ठा device *dev)
अणु
पूर्ण

अटल अंतरभूत काष्ठा dma_chan *acpi_dma_request_slave_chan_by_index(
		काष्ठा device *dev, माप_प्रकार index)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
अटल अंतरभूत काष्ठा dma_chan *acpi_dma_request_slave_chan_by_name(
		काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

#घोषणा acpi_dma_simple_xlate	शून्य

#पूर्ण_अगर

#घोषणा acpi_dma_request_slave_channel	acpi_dma_request_slave_chan_by_index

#पूर्ण_अगर /* __LINUX_ACPI_DMA_H */
