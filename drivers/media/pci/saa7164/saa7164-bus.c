<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश "saa7164.h"

/* The message bus to/from the firmware is a ring buffer in PCI address
 * space. Establish the शेषs.
 */
पूर्णांक saa7164_bus_setup(काष्ठा saa7164_dev *dev)
अणु
	काष्ठा पंचांगComResBusInfo *b	= &dev->bus;

	mutex_init(&b->lock);

	b->Type			= TYPE_BUS_PCIe;
	b->m_wMaxReqSize	= SAA_DEVICE_MAXREQUESTSIZE;

	b->m_pdwSetRing		= (u8 __iomem *)(dev->bmmio +
		((u32)dev->busdesc.CommandRing));

	b->m_dwSizeSetRing	= SAA_DEVICE_BUFFERBLOCKSIZE;

	b->m_pdwGetRing		= (u8 __iomem *)(dev->bmmio +
		((u32)dev->busdesc.ResponseRing));

	b->m_dwSizeGetRing	= SAA_DEVICE_BUFFERBLOCKSIZE;

	b->m_dwSetWritePos	= ((u32)dev->पूर्णांकfdesc.BARLocation) +
		(2 * माप(u64));
	b->m_dwSetReadPos	= b->m_dwSetWritePos + (1 * माप(u32));

	b->m_dwGetWritePos	= b->m_dwSetWritePos + (2 * माप(u32));
	b->m_dwGetReadPos	= b->m_dwSetWritePos + (3 * माप(u32));

	वापस 0;
पूर्ण

व्योम saa7164_bus_dump(काष्ठा saa7164_dev *dev)
अणु
	काष्ठा पंचांगComResBusInfo *b = &dev->bus;

	dprपूर्णांकk(DBGLVL_BUS, "Dumping the bus structure:\n");
	dprपूर्णांकk(DBGLVL_BUS, " .type             = %d\n", b->Type);
	dprपूर्णांकk(DBGLVL_BUS, " .dev->bmmio       = 0x%p\n", dev->bmmio);
	dprपूर्णांकk(DBGLVL_BUS, " .m_wMaxReqSize    = 0x%x\n", b->m_wMaxReqSize);
	dprपूर्णांकk(DBGLVL_BUS, " .m_pdwSetRing     = 0x%p\n", b->m_pdwSetRing);
	dprपूर्णांकk(DBGLVL_BUS, " .m_dwSizeSetRing  = 0x%x\n", b->m_dwSizeSetRing);
	dprपूर्णांकk(DBGLVL_BUS, " .m_pdwGetRing     = 0x%p\n", b->m_pdwGetRing);
	dprपूर्णांकk(DBGLVL_BUS, " .m_dwSizeGetRing  = 0x%x\n", b->m_dwSizeGetRing);

	dprपूर्णांकk(DBGLVL_BUS, " .m_dwSetReadPos   = 0x%x (0x%08x)\n",
		b->m_dwSetReadPos, saa7164_पढ़ोl(b->m_dwSetReadPos));

	dprपूर्णांकk(DBGLVL_BUS, " .m_dwSetWritePos  = 0x%x (0x%08x)\n",
		b->m_dwSetWritePos, saa7164_पढ़ोl(b->m_dwSetWritePos));

	dprपूर्णांकk(DBGLVL_BUS, " .m_dwGetReadPos   = 0x%x (0x%08x)\n",
		b->m_dwGetReadPos, saa7164_पढ़ोl(b->m_dwGetReadPos));

	dprपूर्णांकk(DBGLVL_BUS, " .m_dwGetWritePos  = 0x%x (0x%08x)\n",
		b->m_dwGetWritePos, saa7164_पढ़ोl(b->m_dwGetWritePos));

पूर्ण

/* Intensionally throw a BUG() अगर the state of the message bus looks corrupt */
अटल व्योम saa7164_bus_verअगरy(काष्ठा saa7164_dev *dev)
अणु
	काष्ठा पंचांगComResBusInfo *b = &dev->bus;
	पूर्णांक bug = 0;

	अगर (saa7164_पढ़ोl(b->m_dwSetReadPos) > b->m_dwSizeSetRing)
		bug++;

	अगर (saa7164_पढ़ोl(b->m_dwSetWritePos) > b->m_dwSizeSetRing)
		bug++;

	अगर (saa7164_पढ़ोl(b->m_dwGetReadPos) > b->m_dwSizeGetRing)
		bug++;

	अगर (saa7164_पढ़ोl(b->m_dwGetWritePos) > b->m_dwSizeGetRing)
		bug++;

	अगर (bug) अणु
		saa_debug = 0xffff; /* Ensure we get the bus dump */
		saa7164_bus_dump(dev);
		saa_debug = 1024; /* Ensure we get the bus dump */
		BUG();
	पूर्ण
पूर्ण

अटल व्योम saa7164_bus_dumpmsg(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo *m,
				व्योम *buf)
अणु
	dprपूर्णांकk(DBGLVL_BUS, "Dumping msg structure:\n");
	dprपूर्णांकk(DBGLVL_BUS, " .id               = %d\n",   m->id);
	dprपूर्णांकk(DBGLVL_BUS, " .flags            = 0x%x\n", m->flags);
	dprपूर्णांकk(DBGLVL_BUS, " .size             = 0x%x\n", m->size);
	dprपूर्णांकk(DBGLVL_BUS, " .command          = 0x%x\n", m->command);
	dprपूर्णांकk(DBGLVL_BUS, " .controlselector  = 0x%x\n", m->controlselector);
	dprपूर्णांकk(DBGLVL_BUS, " .seqno            = %d\n",   m->seqno);
	अगर (buf)
		dprपूर्णांकk(DBGLVL_BUS, " .buffer (ignored)\n");
पूर्ण

/*
 * Places a command or a response on the bus. The implementation करोes not
 * know अगर it is a command or a response it just places the data on the
 * bus depending on the bus inक्रमmation given in the काष्ठा पंचांगComResBusInfo
 * काष्ठाure. If the command or response करोes not fit पूर्णांकo the bus ring
 * buffer it will be refused.
 *
 * Return Value:
 *  SAA_OK     The function executed successfully.
 *  < 0        One or more members are not initialized.
 */
पूर्णांक saa7164_bus_set(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo* msg,
	व्योम *buf)
अणु
	काष्ठा पंचांगComResBusInfo *bus = &dev->bus;
	u32 bytes_to_ग_लिखो, मुक्त_ग_लिखो_space, समयout, curr_srp, curr_swp;
	u32 new_swp, space_rem;
	पूर्णांक ret = SAA_ERR_BAD_PARAMETER;
	u16 size;

	अगर (!msg) अणु
		prपूर्णांकk(KERN_ERR "%s() !msg\n", __func__);
		वापस SAA_ERR_BAD_PARAMETER;
	पूर्ण

	dprपूर्णांकk(DBGLVL_BUS, "%s()\n", __func__);

	saa7164_bus_verअगरy(dev);

	अगर (msg->size > dev->bus.m_wMaxReqSize) अणु
		prपूर्णांकk(KERN_ERR "%s() Exceeded dev->bus.m_wMaxReqSize\n",
			__func__);
		वापस SAA_ERR_BAD_PARAMETER;
	पूर्ण

	अगर ((msg->size > 0) && (buf == शून्य)) अणु
		prपूर्णांकk(KERN_ERR "%s() Missing message buffer\n", __func__);
		वापस SAA_ERR_BAD_PARAMETER;
	पूर्ण

	/* Lock the bus from any other access */
	mutex_lock(&bus->lock);

	bytes_to_ग_लिखो = माप(*msg) + msg->size;
	मुक्त_ग_लिखो_space = 0;
	समयout = SAA_BUS_TIMEOUT;
	curr_srp = saa7164_पढ़ोl(bus->m_dwSetReadPos);
	curr_swp = saa7164_पढ़ोl(bus->m_dwSetWritePos);

	/* Deal with ring wrapping issues */
	अगर (curr_srp > curr_swp)
		/* Deal with the wrapped ring */
		मुक्त_ग_लिखो_space = curr_srp - curr_swp;
	अन्यथा
		/* The ring has not wrapped yet */
		मुक्त_ग_लिखो_space = (curr_srp + bus->m_dwSizeSetRing) - curr_swp;

	dprपूर्णांकk(DBGLVL_BUS, "%s() bytes_to_write = %d\n", __func__,
		bytes_to_ग_लिखो);

	dprपूर्णांकk(DBGLVL_BUS, "%s() free_write_space = %d\n", __func__,
		मुक्त_ग_लिखो_space);

	dprपूर्णांकk(DBGLVL_BUS, "%s() curr_srp = %x\n", __func__, curr_srp);
	dprपूर्णांकk(DBGLVL_BUS, "%s() curr_swp = %x\n", __func__, curr_swp);

	/* Process the msg and ग_लिखो the content onto the bus */
	जबतक (bytes_to_ग_लिखो >= मुक्त_ग_लिखो_space) अणु

		अगर (समयout-- == 0) अणु
			prपूर्णांकk(KERN_ERR "%s() bus timeout\n", __func__);
			ret = SAA_ERR_NO_RESOURCES;
			जाओ out;
		पूर्ण

		/* TODO: Review this delay, efficient? */
		/* Wait, allowing the hardware fetch समय */
		mdelay(1);

		/* Check the space usage again */
		curr_srp = saa7164_पढ़ोl(bus->m_dwSetReadPos);

		/* Deal with ring wrapping issues */
		अगर (curr_srp > curr_swp)
			/* Deal with the wrapped ring */
			मुक्त_ग_लिखो_space = curr_srp - curr_swp;
		अन्यथा
			/* Read didn't wrap around the buffer */
			मुक्त_ग_लिखो_space = (curr_srp + bus->m_dwSizeSetRing) -
				curr_swp;

	पूर्ण

	/* Calculate the new ग_लिखो position */
	new_swp = curr_swp + bytes_to_ग_लिखो;

	dprपूर्णांकk(DBGLVL_BUS, "%s() new_swp = %x\n", __func__, new_swp);
	dprपूर्णांकk(DBGLVL_BUS, "%s() bus->m_dwSizeSetRing = %x\n", __func__,
		bus->m_dwSizeSetRing);

	/*
	 * Make a copy of msg->size beक्रमe it is converted to le16 since it is
	 * used in the code below.
	 */
	size = msg->size;
	/* Convert to le16/le32 */
	msg->size = (__क्रमce u16)cpu_to_le16(msg->size);
	msg->command = (__क्रमce u32)cpu_to_le32(msg->command);
	msg->controlselector = (__क्रमce u16)cpu_to_le16(msg->controlselector);

	/* Mental Note: line 462 पंचांगmhComResBusPCIe.cpp */

	/* Check अगर we're going to wrap again */
	अगर (new_swp > bus->m_dwSizeSetRing) अणु

		/* Ring wraps */
		new_swp -= bus->m_dwSizeSetRing;

		space_rem = bus->m_dwSizeSetRing - curr_swp;

		dprपूर्णांकk(DBGLVL_BUS, "%s() space_rem = %x\n", __func__,
			space_rem);

		dprपूर्णांकk(DBGLVL_BUS, "%s() sizeof(*msg) = %d\n", __func__,
			(u32)माप(*msg));

		अगर (space_rem < माप(*msg)) अणु
			dprपूर्णांकk(DBGLVL_BUS, "%s() tr4\n", __func__);

			/* Split the msg पूर्णांकo pieces as the ring wraps */
			स_नकल_toio(bus->m_pdwSetRing + curr_swp, msg, space_rem);
			स_नकल_toio(bus->m_pdwSetRing, (u8 *)msg + space_rem,
				माप(*msg) - space_rem);

			स_नकल_toio(bus->m_pdwSetRing + माप(*msg) - space_rem,
				buf, size);

		पूर्ण अन्यथा अगर (space_rem == माप(*msg)) अणु
			dprपूर्णांकk(DBGLVL_BUS, "%s() tr5\n", __func__);

			/* Additional data at the beginning of the ring */
			स_नकल_toio(bus->m_pdwSetRing + curr_swp, msg, माप(*msg));
			स_नकल_toio(bus->m_pdwSetRing, buf, size);

		पूर्ण अन्यथा अणु
			/* Additional data wraps around the ring */
			स_नकल_toio(bus->m_pdwSetRing + curr_swp, msg, माप(*msg));
			अगर (size > 0) अणु
				स_नकल_toio(bus->m_pdwSetRing + curr_swp +
					माप(*msg), buf, space_rem -
					माप(*msg));
				स_नकल_toio(bus->m_pdwSetRing, (u8 *)buf +
					space_rem - माप(*msg),
					bytes_to_ग_लिखो - space_rem);
			पूर्ण

		पूर्ण

	पूर्ण /* (new_swp > bus->m_dwSizeSetRing) */
	अन्यथा अणु
		dprपूर्णांकk(DBGLVL_BUS, "%s() tr6\n", __func__);

		/* The ring buffer करोesn't wrap, two simple copies */
		स_नकल_toio(bus->m_pdwSetRing + curr_swp, msg, माप(*msg));
		स_नकल_toio(bus->m_pdwSetRing + curr_swp + माप(*msg), buf,
			size);
	पूर्ण

	dprपूर्णांकk(DBGLVL_BUS, "%s() new_swp = %x\n", __func__, new_swp);

	/* Update the bus ग_लिखो position */
	saa7164_ग_लिखोl(bus->m_dwSetWritePos, new_swp);

	/* Convert back to cpu after writing the msg to the ringbuffer. */
	msg->size = le16_to_cpu((__क्रमce __le16)msg->size);
	msg->command = le32_to_cpu((__क्रमce __le32)msg->command);
	msg->controlselector = le16_to_cpu((__क्रमce __le16)msg->controlselector);
	ret = SAA_OK;

out:
	saa7164_bus_dump(dev);
	mutex_unlock(&bus->lock);
	saa7164_bus_verअगरy(dev);
	वापस ret;
पूर्ण

/*
 * Receive a command or a response from the bus. The implementation करोes not
 * know अगर it is a command or a response it simply dequeues the data,
 * depending on the bus inक्रमmation given in the काष्ठा पंचांगComResBusInfo
 * काष्ठाure.
 *
 * Return Value:
 *  0          The function executed successfully.
 *  < 0        One or more members are not initialized.
 */
पूर्णांक saa7164_bus_get(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo* msg,
	व्योम *buf, पूर्णांक peekonly)
अणु
	काष्ठा पंचांगComResBusInfo *bus = &dev->bus;
	u32 bytes_to_पढ़ो, ग_लिखो_distance, curr_grp, curr_gwp,
		new_grp, buf_size, space_rem;
	काष्ठा पंचांगComResInfo msg_पंचांगp;
	पूर्णांक ret = SAA_ERR_BAD_PARAMETER;

	saa7164_bus_verअगरy(dev);

	अगर (msg == शून्य)
		वापस ret;

	अगर (msg->size > dev->bus.m_wMaxReqSize) अणु
		prपूर्णांकk(KERN_ERR "%s() Exceeded dev->bus.m_wMaxReqSize\n",
			__func__);
		वापस ret;
	पूर्ण

	अगर ((peekonly == 0) && (msg->size > 0) && (buf == शून्य)) अणु
		prपूर्णांकk(KERN_ERR
			"%s() Missing msg buf, size should be %d bytes\n",
			__func__, msg->size);
		वापस ret;
	पूर्ण

	mutex_lock(&bus->lock);

	/* Peek the bus to see अगर a msg exists, अगर it's not what we're expecting
	 * then वापस cleanly अन्यथा पढ़ो the message from the bus.
	 */
	curr_gwp = saa7164_पढ़ोl(bus->m_dwGetWritePos);
	curr_grp = saa7164_पढ़ोl(bus->m_dwGetReadPos);

	अगर (curr_gwp == curr_grp) अणु
		ret = SAA_ERR_EMPTY;
		जाओ out;
	पूर्ण

	bytes_to_पढ़ो = माप(*msg);

	/* Calculate ग_लिखो distance to current पढ़ो position */
	ग_लिखो_distance = 0;
	अगर (curr_gwp >= curr_grp)
		/* Write करोesn't wrap around the ring */
		ग_लिखो_distance = curr_gwp - curr_grp;
	अन्यथा
		/* Write wraps around the ring */
		ग_लिखो_distance = curr_gwp + bus->m_dwSizeGetRing - curr_grp;

	अगर (bytes_to_पढ़ो > ग_लिखो_distance) अणु
		prपूर्णांकk(KERN_ERR "%s() No message/response found\n", __func__);
		ret = SAA_ERR_INVALID_COMMAND;
		जाओ out;
	पूर्ण

	/* Calculate the new पढ़ो position */
	new_grp = curr_grp + bytes_to_पढ़ो;
	अगर (new_grp > bus->m_dwSizeGetRing) अणु

		/* Ring wraps */
		new_grp -= bus->m_dwSizeGetRing;
		space_rem = bus->m_dwSizeGetRing - curr_grp;

		स_नकल_fromio(&msg_पंचांगp, bus->m_pdwGetRing + curr_grp, space_rem);
		स_नकल_fromio((u8 *)&msg_पंचांगp + space_rem, bus->m_pdwGetRing,
			bytes_to_पढ़ो - space_rem);

	पूर्ण अन्यथा अणु
		/* No wrapping */
		स_नकल_fromio(&msg_पंचांगp, bus->m_pdwGetRing + curr_grp, bytes_to_पढ़ो);
	पूर्ण
	/* Convert from little endian to CPU */
	msg_पंचांगp.size = le16_to_cpu((__क्रमce __le16)msg_पंचांगp.size);
	msg_पंचांगp.command = le32_to_cpu((__क्रमce __le32)msg_पंचांगp.command);
	msg_पंचांगp.controlselector = le16_to_cpu((__क्रमce __le16)msg_पंचांगp.controlselector);
	स_नकल(msg, &msg_पंचांगp, माप(*msg));

	/* No need to update the पढ़ो positions, because this was a peek */
	/* If the caller specअगरically want to peek, वापस */
	अगर (peekonly) अणु
		जाओ peekout;
	पूर्ण

	/* Check अगर the command/response matches what is expected */
	अगर ((msg_पंचांगp.id != msg->id) || (msg_पंचांगp.command != msg->command) ||
		(msg_पंचांगp.controlselector != msg->controlselector) ||
		(msg_पंचांगp.seqno != msg->seqno) || (msg_पंचांगp.size != msg->size)) अणु

		prपूर्णांकk(KERN_ERR "%s() Unexpected msg miss-match\n", __func__);
		saa7164_bus_dumpmsg(dev, msg, buf);
		saa7164_bus_dumpmsg(dev, &msg_पंचांगp, शून्य);
		ret = SAA_ERR_INVALID_COMMAND;
		जाओ out;
	पूर्ण

	/* Get the actual command and response from the bus */
	buf_size = msg->size;

	bytes_to_पढ़ो = माप(*msg) + msg->size;
	/* Calculate ग_लिखो distance to current पढ़ो position */
	ग_लिखो_distance = 0;
	अगर (curr_gwp >= curr_grp)
		/* Write करोesn't wrap around the ring */
		ग_लिखो_distance = curr_gwp - curr_grp;
	अन्यथा
		/* Write wraps around the ring */
		ग_लिखो_distance = curr_gwp + bus->m_dwSizeGetRing - curr_grp;

	अगर (bytes_to_पढ़ो > ग_लिखो_distance) अणु
		prपूर्णांकk(KERN_ERR "%s() Invalid bus state, missing msg or mangled ring, faulty H/W / bad code?\n",
		       __func__);
		ret = SAA_ERR_INVALID_COMMAND;
		जाओ out;
	पूर्ण

	/* Calculate the new पढ़ो position */
	new_grp = curr_grp + bytes_to_पढ़ो;
	अगर (new_grp > bus->m_dwSizeGetRing) अणु

		/* Ring wraps */
		new_grp -= bus->m_dwSizeGetRing;
		space_rem = bus->m_dwSizeGetRing - curr_grp;

		अगर (space_rem < माप(*msg)) अणु
			अगर (buf)
				स_नकल_fromio(buf, bus->m_pdwGetRing + माप(*msg) -
					space_rem, buf_size);

		पूर्ण अन्यथा अगर (space_rem == माप(*msg)) अणु
			अगर (buf)
				स_नकल_fromio(buf, bus->m_pdwGetRing, buf_size);
		पूर्ण अन्यथा अणु
			/* Additional data wraps around the ring */
			अगर (buf) अणु
				स_नकल_fromio(buf, bus->m_pdwGetRing + curr_grp +
					माप(*msg), space_rem - माप(*msg));
				स_नकल_fromio(buf + space_rem - माप(*msg),
					bus->m_pdwGetRing, bytes_to_पढ़ो -
					space_rem);
			पूर्ण

		पूर्ण

	पूर्ण अन्यथा अणु
		/* No wrapping */
		अगर (buf)
			स_नकल_fromio(buf, bus->m_pdwGetRing + curr_grp + माप(*msg),
				buf_size);
	पूर्ण

	/* Update the पढ़ो positions, adjusting the ring */
	saa7164_ग_लिखोl(bus->m_dwGetReadPos, new_grp);

peekout:
	ret = SAA_OK;
out:
	mutex_unlock(&bus->lock);
	saa7164_bus_verअगरy(dev);
	वापस ret;
पूर्ण

