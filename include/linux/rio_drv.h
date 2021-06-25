<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * RapidIO driver services
 *
 * Copyright 2005 MontaVista Software, Inc.
 * Matt Porter <mporter@kernel.crashing.org>
 */

#अगर_अघोषित LINUX_RIO_DRV_H
#घोषणा LINUX_RIO_DRV_H

#समावेश <linux/types.h>
#समावेश <linux/ioport.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/rपन.स>

बाह्य पूर्णांक __rio_local_पढ़ो_config_32(काष्ठा rio_mport *port, u32 offset,
				      u32 * data);
बाह्य पूर्णांक __rio_local_ग_लिखो_config_32(काष्ठा rio_mport *port, u32 offset,
				       u32 data);
बाह्य पूर्णांक __rio_local_पढ़ो_config_16(काष्ठा rio_mport *port, u32 offset,
				      u16 * data);
बाह्य पूर्णांक __rio_local_ग_लिखो_config_16(काष्ठा rio_mport *port, u32 offset,
				       u16 data);
बाह्य पूर्णांक __rio_local_पढ़ो_config_8(काष्ठा rio_mport *port, u32 offset,
				     u8 * data);
बाह्य पूर्णांक __rio_local_ग_लिखो_config_8(काष्ठा rio_mport *port, u32 offset,
				      u8 data);

बाह्य पूर्णांक rio_mport_पढ़ो_config_32(काष्ठा rio_mport *port, u16 destid,
				    u8 hopcount, u32 offset, u32 * data);
बाह्य पूर्णांक rio_mport_ग_लिखो_config_32(काष्ठा rio_mport *port, u16 destid,
				     u8 hopcount, u32 offset, u32 data);
बाह्य पूर्णांक rio_mport_पढ़ो_config_16(काष्ठा rio_mport *port, u16 destid,
				    u8 hopcount, u32 offset, u16 * data);
बाह्य पूर्णांक rio_mport_ग_लिखो_config_16(काष्ठा rio_mport *port, u16 destid,
				     u8 hopcount, u32 offset, u16 data);
बाह्य पूर्णांक rio_mport_पढ़ो_config_8(काष्ठा rio_mport *port, u16 destid,
				   u8 hopcount, u32 offset, u8 * data);
बाह्य पूर्णांक rio_mport_ग_लिखो_config_8(काष्ठा rio_mport *port, u16 destid,
				    u8 hopcount, u32 offset, u8 data);

/**
 * rio_local_पढ़ो_config_32 - Read 32 bits from local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 32 bits of data from the specअगरied offset within the local
 * device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_local_पढ़ो_config_32(काष्ठा rio_mport *port, u32 offset,
					   u32 * data)
अणु
	वापस __rio_local_पढ़ो_config_32(port, offset, data);
पूर्ण

/**
 * rio_local_ग_लिखो_config_32 - Write 32 bits to local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Data to be written
 *
 * Writes 32 bits of data to the specअगरied offset within the local
 * device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_local_ग_लिखो_config_32(काष्ठा rio_mport *port, u32 offset,
					    u32 data)
अणु
	वापस __rio_local_ग_लिखो_config_32(port, offset, data);
पूर्ण

/**
 * rio_local_पढ़ो_config_16 - Read 16 bits from local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 16 bits of data from the specअगरied offset within the local
 * device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_local_पढ़ो_config_16(काष्ठा rio_mport *port, u32 offset,
					   u16 * data)
अणु
	वापस __rio_local_पढ़ो_config_16(port, offset, data);
पूर्ण

/**
 * rio_local_ग_लिखो_config_16 - Write 16 bits to local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Data to be written
 *
 * Writes 16 bits of data to the specअगरied offset within the local
 * device's configuration space.
 */

अटल अंतरभूत पूर्णांक rio_local_ग_लिखो_config_16(काष्ठा rio_mport *port, u32 offset,
					    u16 data)
अणु
	वापस __rio_local_ग_लिखो_config_16(port, offset, data);
पूर्ण

/**
 * rio_local_पढ़ो_config_8 - Read 8 bits from local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 8 bits of data from the specअगरied offset within the local
 * device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_local_पढ़ो_config_8(काष्ठा rio_mport *port, u32 offset,
					  u8 * data)
अणु
	वापस __rio_local_पढ़ो_config_8(port, offset, data);
पूर्ण

/**
 * rio_local_ग_लिखो_config_8 - Write 8 bits to local configuration space
 * @port: Master port
 * @offset: Offset पूर्णांकo local configuration space
 * @data: Data to be written
 *
 * Writes 8 bits of data to the specअगरied offset within the local
 * device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_local_ग_लिखो_config_8(काष्ठा rio_mport *port, u32 offset,
					   u8 data)
अणु
	वापस __rio_local_ग_लिखो_config_8(port, offset, data);
पूर्ण

/**
 * rio_पढ़ो_config_32 - Read 32 bits from configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 32 bits of data from the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_पढ़ो_config_32(काष्ठा rio_dev *rdev, u32 offset,
				     u32 * data)
अणु
	वापस rio_mport_पढ़ो_config_32(rdev->net->hport, rdev->destid,
					rdev->hopcount, offset, data);
पूर्ण;

/**
 * rio_ग_लिखो_config_32 - Write 32 bits to configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Data to be written
 *
 * Writes 32 bits of data to the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_ग_लिखो_config_32(काष्ठा rio_dev *rdev, u32 offset,
				      u32 data)
अणु
	वापस rio_mport_ग_लिखो_config_32(rdev->net->hport, rdev->destid,
					 rdev->hopcount, offset, data);
पूर्ण;

/**
 * rio_पढ़ो_config_16 - Read 16 bits from configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 16 bits of data from the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_पढ़ो_config_16(काष्ठा rio_dev *rdev, u32 offset,
				     u16 * data)
अणु
	वापस rio_mport_पढ़ो_config_16(rdev->net->hport, rdev->destid,
					rdev->hopcount, offset, data);
पूर्ण;

/**
 * rio_ग_लिखो_config_16 - Write 16 bits to configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Data to be written
 *
 * Writes 16 bits of data to the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_ग_लिखो_config_16(काष्ठा rio_dev *rdev, u32 offset,
				      u16 data)
अणु
	वापस rio_mport_ग_लिखो_config_16(rdev->net->hport, rdev->destid,
					 rdev->hopcount, offset, data);
पूर्ण;

/**
 * rio_पढ़ो_config_8 - Read 8 bits from configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Poपूर्णांकer to पढ़ो data पूर्णांकo
 *
 * Reads 8 bits of data from the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_पढ़ो_config_8(काष्ठा rio_dev *rdev, u32 offset, u8 * data)
अणु
	वापस rio_mport_पढ़ो_config_8(rdev->net->hport, rdev->destid,
				       rdev->hopcount, offset, data);
पूर्ण;

/**
 * rio_ग_लिखो_config_8 - Write 8 bits to configuration space
 * @rdev: RIO device
 * @offset: Offset पूर्णांकo device configuration space
 * @data: Data to be written
 *
 * Writes 8 bits of data to the specअगरied offset within the
 * RIO device's configuration space.
 */
अटल अंतरभूत पूर्णांक rio_ग_लिखो_config_8(काष्ठा rio_dev *rdev, u32 offset, u8 data)
अणु
	वापस rio_mport_ग_लिखो_config_8(rdev->net->hport, rdev->destid,
					rdev->hopcount, offset, data);
पूर्ण;

बाह्य पूर्णांक rio_mport_send_करोorbell(काष्ठा rio_mport *mport, u16 destid,
				   u16 data);

/**
 * rio_send_करोorbell - Send a करोorbell message to a device
 * @rdev: RIO device
 * @data: Doorbell message data
 *
 * Send a करोorbell message to a RIO device. The करोorbell message
 * has a 16-bit info field provided by the @data argument.
 */
अटल अंतरभूत पूर्णांक rio_send_करोorbell(काष्ठा rio_dev *rdev, u16 data)
अणु
	वापस rio_mport_send_करोorbell(rdev->net->hport, rdev->destid, data);
पूर्ण;

/**
 * rio_init_mbox_res - Initialize a RIO mailbox resource
 * @res: resource काष्ठा
 * @start: start of mailbox range
 * @end: end of mailbox range
 *
 * This function is used to initialize the fields of a resource
 * क्रम use as a mailbox resource.  It initializes a range of
 * mailboxes using the start and end arguments.
 */
अटल अंतरभूत व्योम rio_init_mbox_res(काष्ठा resource *res, पूर्णांक start, पूर्णांक end)
अणु
	स_रखो(res, 0, माप(काष्ठा resource));
	res->start = start;
	res->end = end;
	res->flags = RIO_RESOURCE_MAILBOX;
पूर्ण

/**
 * rio_init_dbell_res - Initialize a RIO करोorbell resource
 * @res: resource काष्ठा
 * @start: start of करोorbell range
 * @end: end of करोorbell range
 *
 * This function is used to initialize the fields of a resource
 * क्रम use as a करोorbell resource.  It initializes a range of
 * करोorbell messages using the start and end arguments.
 */
अटल अंतरभूत व्योम rio_init_dbell_res(काष्ठा resource *res, u16 start, u16 end)
अणु
	स_रखो(res, 0, माप(काष्ठा resource));
	res->start = start;
	res->end = end;
	res->flags = RIO_RESOURCE_DOORBELL;
पूर्ण

/**
 * RIO_DEVICE - macro used to describe a specअगरic RIO device
 * @dev: the 16 bit RIO device ID
 * @ven: the 16 bit RIO venकरोr ID
 *
 * This macro is used to create a काष्ठा rio_device_id that matches a
 * specअगरic device.  The assembly venकरोr and assembly device fields
 * will be set to %RIO_ANY_ID.
 */
#घोषणा RIO_DEVICE(dev,ven) \
	.did = (dev), .vid = (ven), \
	.यंत्र_did = RIO_ANY_ID, .यंत्र_vid = RIO_ANY_ID

/* Mailbox management */
बाह्य पूर्णांक rio_request_outb_mbox(काष्ठा rio_mport *, व्योम *, पूर्णांक, पूर्णांक,
				 व्योम (*)(काष्ठा rio_mport *, व्योम *,पूर्णांक, पूर्णांक));
बाह्य पूर्णांक rio_release_outb_mbox(काष्ठा rio_mport *, पूर्णांक);

/**
 * rio_add_outb_message - Add RIO message to an outbound mailbox queue
 * @mport: RIO master port containing the outbound queue
 * @rdev: RIO device the message is be sent to
 * @mbox: The outbound mailbox queue
 * @buffer: Poपूर्णांकer to the message buffer
 * @len: Length of the message buffer
 *
 * Adds a RIO message buffer to an outbound mailbox queue क्रम
 * transmission. Returns 0 on success.
 */
अटल अंतरभूत पूर्णांक rio_add_outb_message(काष्ठा rio_mport *mport,
				       काष्ठा rio_dev *rdev, पूर्णांक mbox,
				       व्योम *buffer, माप_प्रकार len)
अणु
	वापस mport->ops->add_outb_message(mport, rdev, mbox,
						   buffer, len);
पूर्ण

बाह्य पूर्णांक rio_request_inb_mbox(काष्ठा rio_mport *, व्योम *, पूर्णांक, पूर्णांक,
				व्योम (*)(काष्ठा rio_mport *, व्योम *, पूर्णांक, पूर्णांक));
बाह्य पूर्णांक rio_release_inb_mbox(काष्ठा rio_mport *, पूर्णांक);

/**
 * rio_add_inb_buffer - Add buffer to an inbound mailbox queue
 * @mport: Master port containing the inbound mailbox
 * @mbox: The inbound mailbox number
 * @buffer: Poपूर्णांकer to the message buffer
 *
 * Adds a buffer to an inbound mailbox queue क्रम reception. Returns
 * 0 on success.
 */
अटल अंतरभूत पूर्णांक rio_add_inb_buffer(काष्ठा rio_mport *mport, पूर्णांक mbox,
				     व्योम *buffer)
अणु
	वापस mport->ops->add_inb_buffer(mport, mbox, buffer);
पूर्ण

/**
 * rio_get_inb_message - Get A RIO message from an inbound mailbox queue
 * @mport: Master port containing the inbound mailbox
 * @mbox: The inbound mailbox number
 *
 * Get a RIO message from an inbound mailbox queue. Returns 0 on success.
 */
अटल अंतरभूत व्योम *rio_get_inb_message(काष्ठा rio_mport *mport, पूर्णांक mbox)
अणु
	वापस mport->ops->get_inb_message(mport, mbox);
पूर्ण

/* Doorbell management */
बाह्य पूर्णांक rio_request_inb_dbell(काष्ठा rio_mport *, व्योम *, u16, u16,
				 व्योम (*)(काष्ठा rio_mport *, व्योम *, u16, u16, u16));
बाह्य पूर्णांक rio_release_inb_dbell(काष्ठा rio_mport *, u16, u16);
बाह्य काष्ठा resource *rio_request_outb_dbell(काष्ठा rio_dev *, u16, u16);
बाह्य पूर्णांक rio_release_outb_dbell(काष्ठा rio_dev *, काष्ठा resource *);

/* Memory region management */
पूर्णांक rio_claim_resource(काष्ठा rio_dev *, पूर्णांक);
पूर्णांक rio_request_regions(काष्ठा rio_dev *, अक्षर *);
व्योम rio_release_regions(काष्ठा rio_dev *);
पूर्णांक rio_request_region(काष्ठा rio_dev *, पूर्णांक, अक्षर *);
व्योम rio_release_region(काष्ठा rio_dev *, पूर्णांक);

/* Memory mapping functions */
बाह्य पूर्णांक rio_map_inb_region(काष्ठा rio_mport *mport, dma_addr_t local,
			u64 rbase, u32 size, u32 rflags);
बाह्य व्योम rio_unmap_inb_region(काष्ठा rio_mport *mport, dma_addr_t lstart);
बाह्य पूर्णांक rio_map_outb_region(काष्ठा rio_mport *mport, u16 destid, u64 rbase,
			u32 size, u32 rflags, dma_addr_t *local);
बाह्य व्योम rio_unmap_outb_region(काष्ठा rio_mport *mport,
				  u16 destid, u64 rstart);

/* Port-Write management */
बाह्य पूर्णांक rio_request_inb_pग_लिखो(काष्ठा rio_dev *,
			पूर्णांक (*)(काष्ठा rio_dev *, जोड़ rio_pw_msg*, पूर्णांक));
बाह्य पूर्णांक rio_release_inb_pग_लिखो(काष्ठा rio_dev *);
बाह्य पूर्णांक rio_add_mport_pw_handler(काष्ठा rio_mport *mport, व्योम *dev_id,
			पूर्णांक (*pwcback)(काष्ठा rio_mport *mport, व्योम *dev_id,
			जोड़ rio_pw_msg *msg, पूर्णांक step));
बाह्य पूर्णांक rio_del_mport_pw_handler(काष्ठा rio_mport *mport, व्योम *dev_id,
			पूर्णांक (*pwcback)(काष्ठा rio_mport *mport, व्योम *dev_id,
			जोड़ rio_pw_msg *msg, पूर्णांक step));
बाह्य पूर्णांक rio_inb_pग_लिखो_handler(काष्ठा rio_mport *mport,
				  जोड़ rio_pw_msg *pw_msg);
बाह्य व्योम rio_pw_enable(काष्ठा rio_mport *mport, पूर्णांक enable);

/* LDM support */
पूर्णांक rio_रेजिस्टर_driver(काष्ठा rio_driver *);
व्योम rio_unरेजिस्टर_driver(काष्ठा rio_driver *);
काष्ठा rio_dev *rio_dev_get(काष्ठा rio_dev *);
व्योम rio_dev_put(काष्ठा rio_dev *);

#अगर_घोषित CONFIG_RAPIDIO_DMA_ENGINE
बाह्य काष्ठा dma_chan *rio_request_dma(काष्ठा rio_dev *rdev);
बाह्य काष्ठा dma_chan *rio_request_mport_dma(काष्ठा rio_mport *mport);
बाह्य व्योम rio_release_dma(काष्ठा dma_chan *dchan);
बाह्य काष्ठा dma_async_tx_descriptor *rio_dma_prep_slave_sg(
		काष्ठा rio_dev *rdev, काष्ठा dma_chan *dchan,
		काष्ठा rio_dma_data *data,
		क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags);
बाह्य काष्ठा dma_async_tx_descriptor *rio_dma_prep_xfer(
		काष्ठा dma_chan *dchan,	u16 destid,
		काष्ठा rio_dma_data *data,
		क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags);
#पूर्ण_अगर

/**
 * rio_name - Get the unique RIO device identअगरier
 * @rdev: RIO device
 *
 * Get the unique RIO device identअगरier. Returns the device
 * identअगरier string.
 */
अटल अंतरभूत स्थिर अक्षर *rio_name(काष्ठा rio_dev *rdev)
अणु
	वापस dev_name(&rdev->dev);
पूर्ण

/**
 * rio_get_drvdata - Get RIO driver specअगरic data
 * @rdev: RIO device
 *
 * Get RIO driver specअगरic data. Returns a poपूर्णांकer to the
 * driver specअगरic data.
 */
अटल अंतरभूत व्योम *rio_get_drvdata(काष्ठा rio_dev *rdev)
अणु
	वापस dev_get_drvdata(&rdev->dev);
पूर्ण

/**
 * rio_set_drvdata - Set RIO driver specअगरic data
 * @rdev: RIO device
 * @data: Poपूर्णांकer to driver specअगरic data
 *
 * Set RIO driver specअगरic data. device काष्ठा driver data poपूर्णांकer
 * is set to the @data argument.
 */
अटल अंतरभूत व्योम rio_set_drvdata(काष्ठा rio_dev *rdev, व्योम *data)
अणु
	dev_set_drvdata(&rdev->dev, data);
पूर्ण

/* Misc driver helpers */
बाह्य u16 rio_local_get_device_id(काष्ठा rio_mport *port);
बाह्य व्योम rio_local_set_device_id(काष्ठा rio_mport *port, u16 did);
बाह्य पूर्णांक rio_init_mports(व्योम);

#पूर्ण_अगर				/* LINUX_RIO_DRV_H */
