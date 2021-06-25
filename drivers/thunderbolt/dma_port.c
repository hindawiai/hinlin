<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt DMA configuration based mailbox support
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश "dma_port.h"
#समावेश "tb_regs.h"

#घोषणा DMA_PORT_CAP			0x3e

#घोषणा MAIL_DATA			1
#घोषणा MAIL_DATA_DWORDS		16

#घोषणा MAIL_IN				17
#घोषणा MAIL_IN_CMD_SHIFT		28
#घोषणा MAIL_IN_CMD_MASK		GENMASK(31, 28)
#घोषणा MAIL_IN_CMD_FLASH_WRITE		0x0
#घोषणा MAIL_IN_CMD_FLASH_UPDATE_AUTH	0x1
#घोषणा MAIL_IN_CMD_FLASH_READ		0x2
#घोषणा MAIL_IN_CMD_POWER_CYCLE		0x4
#घोषणा MAIL_IN_DWORDS_SHIFT		24
#घोषणा MAIL_IN_DWORDS_MASK		GENMASK(27, 24)
#घोषणा MAIL_IN_ADDRESS_SHIFT		2
#घोषणा MAIL_IN_ADDRESS_MASK		GENMASK(23, 2)
#घोषणा MAIL_IN_CSS			BIT(1)
#घोषणा MAIL_IN_OP_REQUEST		BIT(0)

#घोषणा MAIL_OUT			18
#घोषणा MAIL_OUT_STATUS_RESPONSE	BIT(29)
#घोषणा MAIL_OUT_STATUS_CMD_SHIFT	4
#घोषणा MAIL_OUT_STATUS_CMD_MASK	GENMASK(7, 4)
#घोषणा MAIL_OUT_STATUS_MASK		GENMASK(3, 0)
#घोषणा MAIL_OUT_STATUS_COMPLETED	0
#घोषणा MAIL_OUT_STATUS_ERR_AUTH	1
#घोषणा MAIL_OUT_STATUS_ERR_ACCESS	2

#घोषणा DMA_PORT_TIMEOUT		5000 /* ms */
#घोषणा DMA_PORT_RETRIES		3

/**
 * काष्ठा tb_dma_port - DMA control port
 * @sw: Switch the DMA port beदीर्घs to
 * @port: Switch port number where DMA capability is found
 * @base: Start offset of the mailbox रेजिस्टरs
 * @buf: Temporary buffer to store a single block
 */
काष्ठा tb_dma_port अणु
	काष्ठा tb_चयन *sw;
	u8 port;
	u32 base;
	u8 *buf;
पूर्ण;

/*
 * When the चयन is in safe mode it supports very little functionality
 * so we करोn't validate that much here.
 */
अटल bool dma_port_match(स्थिर काष्ठा tb_cfg_request *req,
			   स्थिर काष्ठा ctl_pkg *pkg)
अणु
	u64 route = tb_cfg_get_route(pkg->buffer) & ~BIT_ULL(63);

	अगर (pkg->frame.eof == TB_CFG_PKG_ERROR)
		वापस true;
	अगर (pkg->frame.eof != req->response_type)
		वापस false;
	अगर (route != tb_cfg_get_route(req->request))
		वापस false;
	अगर (pkg->frame.size != req->response_size)
		वापस false;

	वापस true;
पूर्ण

अटल bool dma_port_copy(काष्ठा tb_cfg_request *req, स्थिर काष्ठा ctl_pkg *pkg)
अणु
	स_नकल(req->response, pkg->buffer, req->response_size);
	वापस true;
पूर्ण

अटल पूर्णांक dma_port_पढ़ो(काष्ठा tb_ctl *ctl, व्योम *buffer, u64 route,
			 u32 port, u32 offset, u32 length, पूर्णांक समयout_msec)
अणु
	काष्ठा cfg_पढ़ो_pkg request = अणु
		.header = tb_cfg_make_header(route),
		.addr = अणु
			.seq = 1,
			.port = port,
			.space = TB_CFG_PORT,
			.offset = offset,
			.length = length,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_cfg_request *req;
	काष्ठा cfg_ग_लिखो_pkg reply;
	काष्ठा tb_cfg_result res;

	req = tb_cfg_request_alloc();
	अगर (!req)
		वापस -ENOMEM;

	req->match = dma_port_match;
	req->copy = dma_port_copy;
	req->request = &request;
	req->request_size = माप(request);
	req->request_type = TB_CFG_PKG_READ;
	req->response = &reply;
	req->response_size = 12 + 4 * length;
	req->response_type = TB_CFG_PKG_READ;

	res = tb_cfg_request_sync(ctl, req, समयout_msec);

	tb_cfg_request_put(req);

	अगर (res.err)
		वापस res.err;

	स_नकल(buffer, &reply.data, 4 * length);
	वापस 0;
पूर्ण

अटल पूर्णांक dma_port_ग_लिखो(काष्ठा tb_ctl *ctl, स्थिर व्योम *buffer, u64 route,
			  u32 port, u32 offset, u32 length, पूर्णांक समयout_msec)
अणु
	काष्ठा cfg_ग_लिखो_pkg request = अणु
		.header = tb_cfg_make_header(route),
		.addr = अणु
			.seq = 1,
			.port = port,
			.space = TB_CFG_PORT,
			.offset = offset,
			.length = length,
		पूर्ण,
	पूर्ण;
	काष्ठा tb_cfg_request *req;
	काष्ठा cfg_पढ़ो_pkg reply;
	काष्ठा tb_cfg_result res;

	स_नकल(&request.data, buffer, length * 4);

	req = tb_cfg_request_alloc();
	अगर (!req)
		वापस -ENOMEM;

	req->match = dma_port_match;
	req->copy = dma_port_copy;
	req->request = &request;
	req->request_size = 12 + 4 * length;
	req->request_type = TB_CFG_PKG_WRITE;
	req->response = &reply;
	req->response_size = माप(reply);
	req->response_type = TB_CFG_PKG_WRITE;

	res = tb_cfg_request_sync(ctl, req, समयout_msec);

	tb_cfg_request_put(req);

	वापस res.err;
पूर्ण

अटल पूर्णांक dma_find_port(काष्ठा tb_चयन *sw)
अणु
	अटल स्थिर पूर्णांक ports[] = अणु 3, 5, 7 पूर्ण;
	पूर्णांक i;

	/*
	 * The DMA (NHI) port is either 3, 5 or 7 depending on the
	 * controller. Try all of them.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ports); i++) अणु
		u32 type;
		पूर्णांक ret;

		ret = dma_port_पढ़ो(sw->tb->ctl, &type, tb_route(sw), ports[i],
				    2, 1, DMA_PORT_TIMEOUT);
		अगर (!ret && (type & 0xffffff) == TB_TYPE_NHI)
			वापस ports[i];
	पूर्ण

	वापस -ENODEV;
पूर्ण

/**
 * dma_port_alloc() - Finds DMA control port from a चयन poपूर्णांकed by route
 * @sw: Switch from where find the DMA port
 *
 * Function checks अगर the चयन NHI port supports DMA configuration
 * based mailbox capability and अगर it करोes, allocates and initializes
 * DMA port काष्ठाure. Returns %शून्य अगर the capabity was not found.
 *
 * The DMA control port is functional also when the चयन is in safe
 * mode.
 */
काष्ठा tb_dma_port *dma_port_alloc(काष्ठा tb_चयन *sw)
अणु
	काष्ठा tb_dma_port *dma;
	पूर्णांक port;

	port = dma_find_port(sw);
	अगर (port < 0)
		वापस शून्य;

	dma = kzalloc(माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस शून्य;

	dma->buf = kदो_स्मृति_array(MAIL_DATA_DWORDS, माप(u32), GFP_KERNEL);
	अगर (!dma->buf) अणु
		kमुक्त(dma);
		वापस शून्य;
	पूर्ण

	dma->sw = sw;
	dma->port = port;
	dma->base = DMA_PORT_CAP;

	वापस dma;
पूर्ण

/**
 * dma_port_मुक्त() - Release DMA control port काष्ठाure
 * @dma: DMA control port
 */
व्योम dma_port_मुक्त(काष्ठा tb_dma_port *dma)
अणु
	अगर (dma) अणु
		kमुक्त(dma->buf);
		kमुक्त(dma);
	पूर्ण
पूर्ण

अटल पूर्णांक dma_port_रुको_क्रम_completion(काष्ठा tb_dma_port *dma,
					अचिन्हित पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(समयout);
	काष्ठा tb_चयन *sw = dma->sw;

	करो अणु
		पूर्णांक ret;
		u32 in;

		ret = dma_port_पढ़ो(sw->tb->ctl, &in, tb_route(sw), dma->port,
				    dma->base + MAIL_IN, 1, 50);
		अगर (ret) अणु
			अगर (ret != -ETIMEDOUT)
				वापस ret;
		पूर्ण अन्यथा अगर (!(in & MAIL_IN_OP_REQUEST)) अणु
			वापस 0;
		पूर्ण

		usleep_range(50, 100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक status_to_त्रुटि_सं(u32 status)
अणु
	चयन (status & MAIL_OUT_STATUS_MASK) अणु
	हाल MAIL_OUT_STATUS_COMPLETED:
		वापस 0;
	हाल MAIL_OUT_STATUS_ERR_AUTH:
		वापस -EINVAL;
	हाल MAIL_OUT_STATUS_ERR_ACCESS:
		वापस -EACCES;
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक dma_port_request(काष्ठा tb_dma_port *dma, u32 in,
			    अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा tb_चयन *sw = dma->sw;
	u32 out;
	पूर्णांक ret;

	ret = dma_port_ग_लिखो(sw->tb->ctl, &in, tb_route(sw), dma->port,
			     dma->base + MAIL_IN, 1, DMA_PORT_TIMEOUT);
	अगर (ret)
		वापस ret;

	ret = dma_port_रुको_क्रम_completion(dma, समयout);
	अगर (ret)
		वापस ret;

	ret = dma_port_पढ़ो(sw->tb->ctl, &out, tb_route(sw), dma->port,
			    dma->base + MAIL_OUT, 1, DMA_PORT_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस status_to_त्रुटि_सं(out);
पूर्ण

अटल पूर्णांक dma_port_flash_पढ़ो_block(काष्ठा tb_dma_port *dma, u32 address,
				     व्योम *buf, u32 size)
अणु
	काष्ठा tb_चयन *sw = dma->sw;
	u32 in, dwaddress, dwords;
	पूर्णांक ret;

	dwaddress = address / 4;
	dwords = size / 4;

	in = MAIL_IN_CMD_FLASH_READ << MAIL_IN_CMD_SHIFT;
	अगर (dwords < MAIL_DATA_DWORDS)
		in |= (dwords << MAIL_IN_DWORDS_SHIFT) & MAIL_IN_DWORDS_MASK;
	in |= (dwaddress << MAIL_IN_ADDRESS_SHIFT) & MAIL_IN_ADDRESS_MASK;
	in |= MAIL_IN_OP_REQUEST;

	ret = dma_port_request(dma, in, DMA_PORT_TIMEOUT);
	अगर (ret)
		वापस ret;

	वापस dma_port_पढ़ो(sw->tb->ctl, buf, tb_route(sw), dma->port,
			     dma->base + MAIL_DATA, dwords, DMA_PORT_TIMEOUT);
पूर्ण

अटल पूर्णांक dma_port_flash_ग_लिखो_block(काष्ठा tb_dma_port *dma, u32 address,
				      स्थिर व्योम *buf, u32 size)
अणु
	काष्ठा tb_चयन *sw = dma->sw;
	u32 in, dwaddress, dwords;
	पूर्णांक ret;

	dwords = size / 4;

	/* Write the block to MAIL_DATA रेजिस्टरs */
	ret = dma_port_ग_लिखो(sw->tb->ctl, buf, tb_route(sw), dma->port,
			    dma->base + MAIL_DATA, dwords, DMA_PORT_TIMEOUT);
	अगर (ret)
		वापस ret;

	in = MAIL_IN_CMD_FLASH_WRITE << MAIL_IN_CMD_SHIFT;

	/* CSS header ग_लिखो is always करोne to the same magic address */
	अगर (address >= DMA_PORT_CSS_ADDRESS) अणु
		dwaddress = DMA_PORT_CSS_ADDRESS;
		in |= MAIL_IN_CSS;
	पूर्ण अन्यथा अणु
		dwaddress = address / 4;
	पूर्ण

	in |= ((dwords - 1) << MAIL_IN_DWORDS_SHIFT) & MAIL_IN_DWORDS_MASK;
	in |= (dwaddress << MAIL_IN_ADDRESS_SHIFT) & MAIL_IN_ADDRESS_MASK;
	in |= MAIL_IN_OP_REQUEST;

	वापस dma_port_request(dma, in, DMA_PORT_TIMEOUT);
पूर्ण

/**
 * dma_port_flash_पढ़ो() - Read from active flash region
 * @dma: DMA control port
 * @address: Address relative to the start of active region
 * @buf: Buffer where the data is पढ़ो
 * @size: Size of the buffer
 */
पूर्णांक dma_port_flash_पढ़ो(काष्ठा tb_dma_port *dma, अचिन्हित पूर्णांक address,
			व्योम *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक retries = DMA_PORT_RETRIES;

	करो अणु
		अचिन्हित पूर्णांक offset;
		माप_प्रकार nbytes;
		पूर्णांक ret;

		offset = address & 3;
		nbytes = min_t(माप_प्रकार, size + offset, MAIL_DATA_DWORDS * 4);

		ret = dma_port_flash_पढ़ो_block(dma, address, dma->buf,
						ALIGN(nbytes, 4));
		अगर (ret) अणु
			अगर (ret == -ETIMEDOUT) अणु
				अगर (retries--)
					जारी;
				ret = -EIO;
			पूर्ण
			वापस ret;
		पूर्ण

		nbytes -= offset;
		स_नकल(buf, dma->buf + offset, nbytes);

		size -= nbytes;
		address += nbytes;
		buf += nbytes;
	पूर्ण जबतक (size > 0);

	वापस 0;
पूर्ण

/**
 * dma_port_flash_ग_लिखो() - Write to non-active flash region
 * @dma: DMA control port
 * @address: Address relative to the start of non-active region
 * @buf: Data to ग_लिखो
 * @size: Size of the buffer
 *
 * Writes block of data to the non-active flash region of the चयन. If
 * the address is given as %DMA_PORT_CSS_ADDRESS the block is written
 * using CSS command.
 */
पूर्णांक dma_port_flash_ग_लिखो(काष्ठा tb_dma_port *dma, अचिन्हित पूर्णांक address,
			 स्थिर व्योम *buf, माप_प्रकार size)
अणु
	अचिन्हित पूर्णांक retries = DMA_PORT_RETRIES;
	अचिन्हित पूर्णांक offset;

	अगर (address >= DMA_PORT_CSS_ADDRESS) अणु
		offset = 0;
		अगर (size > DMA_PORT_CSS_MAX_SIZE)
			वापस -E2BIG;
	पूर्ण अन्यथा अणु
		offset = address & 3;
		address = address & ~3;
	पूर्ण

	करो अणु
		u32 nbytes = min_t(u32, size, MAIL_DATA_DWORDS * 4);
		पूर्णांक ret;

		स_नकल(dma->buf + offset, buf, nbytes);

		ret = dma_port_flash_ग_लिखो_block(dma, address, buf, nbytes);
		अगर (ret) अणु
			अगर (ret == -ETIMEDOUT) अणु
				अगर (retries--)
					जारी;
				ret = -EIO;
			पूर्ण
			वापस ret;
		पूर्ण

		size -= nbytes;
		address += nbytes;
		buf += nbytes;
	पूर्ण जबतक (size > 0);

	वापस 0;
पूर्ण

/**
 * dma_port_flash_update_auth() - Starts flash authenticate cycle
 * @dma: DMA control port
 *
 * Starts the flash update authentication cycle. If the image in the
 * non-active area was valid, the चयन starts upgrade process where
 * active and non-active area get swapped in the end. Caller should call
 * dma_port_flash_update_auth_status() to get status of this command.
 * This is because अगर the चयन in question is root चयन the
 * thunderbolt host controller माला_लो reset as well.
 */
पूर्णांक dma_port_flash_update_auth(काष्ठा tb_dma_port *dma)
अणु
	u32 in;

	in = MAIL_IN_CMD_FLASH_UPDATE_AUTH << MAIL_IN_CMD_SHIFT;
	in |= MAIL_IN_OP_REQUEST;

	वापस dma_port_request(dma, in, 150);
पूर्ण

/**
 * dma_port_flash_update_auth_status() - Reads status of update auth command
 * @dma: DMA control port
 * @status: Status code of the operation
 *
 * The function checks अगर there is status available from the last update
 * auth command. Returns %0 अगर there is no status and no further
 * action is required. If there is status, %1 is वापसed instead and
 * @status holds the failure code.
 *
 * Negative वापस means there was an error पढ़ोing status from the
 * चयन.
 */
पूर्णांक dma_port_flash_update_auth_status(काष्ठा tb_dma_port *dma, u32 *status)
अणु
	काष्ठा tb_चयन *sw = dma->sw;
	u32 out, cmd;
	पूर्णांक ret;

	ret = dma_port_पढ़ो(sw->tb->ctl, &out, tb_route(sw), dma->port,
			    dma->base + MAIL_OUT, 1, DMA_PORT_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Check अगर the status relates to flash update auth */
	cmd = (out & MAIL_OUT_STATUS_CMD_MASK) >> MAIL_OUT_STATUS_CMD_SHIFT;
	अगर (cmd == MAIL_IN_CMD_FLASH_UPDATE_AUTH) अणु
		अगर (status)
			*status = out & MAIL_OUT_STATUS_MASK;

		/* Reset is needed in any हाल */
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * dma_port_घातer_cycle() - Power cycles the चयन
 * @dma: DMA control port
 *
 * Triggers घातer cycle to the चयन.
 */
पूर्णांक dma_port_घातer_cycle(काष्ठा tb_dma_port *dma)
अणु
	u32 in;

	in = MAIL_IN_CMD_POWER_CYCLE << MAIL_IN_CMD_SHIFT;
	in |= MAIL_IN_OP_REQUEST;

	वापस dma_port_request(dma, in, 150);
पूर्ण
