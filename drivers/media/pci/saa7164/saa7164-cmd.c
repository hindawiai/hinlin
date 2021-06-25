<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम the NXP SAA7164 PCIe bridge
 *
 *  Copyright (c) 2010-2015 Steven Toth <stoth@kernelद_असल.com>
 */

#समावेश <linux/रुको.h>

#समावेश "saa7164.h"

अटल पूर्णांक saa7164_cmd_alloc_seqno(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक i, ret = -1;

	mutex_lock(&dev->lock);
	क्रम (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) अणु
		अगर (dev->cmds[i].inuse == 0) अणु
			dev->cmds[i].inuse = 1;
			dev->cmds[i].संकेतled = 0;
			dev->cmds[i].समयout = 0;
			ret = dev->cmds[i].seqno;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

अटल व्योम saa7164_cmd_मुक्त_seqno(काष्ठा saa7164_dev *dev, u8 seqno)
अणु
	mutex_lock(&dev->lock);
	अगर ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) अणु
		dev->cmds[seqno].inuse = 0;
		dev->cmds[seqno].संकेतled = 0;
		dev->cmds[seqno].समयout = 0;
	पूर्ण
	mutex_unlock(&dev->lock);
पूर्ण

अटल व्योम saa7164_cmd_समयout_seqno(काष्ठा saa7164_dev *dev, u8 seqno)
अणु
	mutex_lock(&dev->lock);
	अगर ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) अणु
		dev->cmds[seqno].समयout = 1;
	पूर्ण
	mutex_unlock(&dev->lock);
पूर्ण

अटल u32 saa7164_cmd_समयout_get(काष्ठा saa7164_dev *dev, u8 seqno)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&dev->lock);
	अगर ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) अणु
		ret = dev->cmds[seqno].समयout;
	पूर्ण
	mutex_unlock(&dev->lock);

	वापस ret;
पूर्ण

/* Commands to the f/w get marshelled to/from this code then onto the PCI
 * -bus/c running buffer. */
पूर्णांक saa7164_irq_dequeue(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक ret = SAA_OK, i = 0;
	u32 समयout;
	रुको_queue_head_t *q = शून्य;
	u8 पंचांगp[512];
	dprपूर्णांकk(DBGLVL_CMD, "%s()\n", __func__);

	/* While any outstand message on the bus exists... */
	करो अणु

		/* Peek the msg bus */
		काष्ठा पंचांगComResInfo tRsp = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
		ret = saa7164_bus_get(dev, &tRsp, शून्य, 1);
		अगर (ret != SAA_OK)
			अवरोध;

		q = &dev->cmds[tRsp.seqno].रुको;
		समयout = saa7164_cmd_समयout_get(dev, tRsp.seqno);
		dprपूर्णांकk(DBGLVL_CMD, "%s() timeout = %d\n", __func__, समयout);
		अगर (!समयout) अणु
			dprपूर्णांकk(DBGLVL_CMD,
				"%s() signalled seqno(%d) (for dequeue)\n",
				__func__, tRsp.seqno);
			dev->cmds[tRsp.seqno].संकेतled = 1;
			wake_up(q);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR
				"%s() found timed out command on the bus\n",
					__func__);

			/* Clean the bus */
			ret = saa7164_bus_get(dev, &tRsp, &पंचांगp, 0);
			prपूर्णांकk(KERN_ERR "%s() ret = %x\n", __func__, ret);
			अगर (ret == SAA_ERR_EMPTY)
				/* Someone अन्यथा alपढ़ोy fetched the response */
				वापस SAA_OK;

			अगर (ret != SAA_OK)
				वापस ret;
		पूर्ण

		/* It's unlikely to have more than 4 or 5 pending messages,
		 * ensure we निकास at some poपूर्णांक regardless.
		 */
	पूर्ण जबतक (i++ < 32);

	वापस ret;
पूर्ण

/* Commands to the f/w get marshelled to/from this code then onto the PCI
 * -bus/c running buffer. */
अटल पूर्णांक saa7164_cmd_dequeue(काष्ठा saa7164_dev *dev)
अणु
	पूर्णांक ret;
	u32 समयout;
	रुको_queue_head_t *q = शून्य;
	u8 पंचांगp[512];
	dprपूर्णांकk(DBGLVL_CMD, "%s()\n", __func__);

	जबतक (true) अणु

		काष्ठा पंचांगComResInfo tRsp = अणु 0, 0, 0, 0, 0, 0 पूर्ण;
		ret = saa7164_bus_get(dev, &tRsp, शून्य, 1);
		अगर (ret == SAA_ERR_EMPTY)
			वापस SAA_OK;

		अगर (ret != SAA_OK)
			वापस ret;

		q = &dev->cmds[tRsp.seqno].रुको;
		समयout = saa7164_cmd_समयout_get(dev, tRsp.seqno);
		dprपूर्णांकk(DBGLVL_CMD, "%s() timeout = %d\n", __func__, समयout);
		अगर (समयout) अणु
			prपूर्णांकk(KERN_ERR "found timed out command on the bus\n");

			/* Clean the bus */
			ret = saa7164_bus_get(dev, &tRsp, &पंचांगp, 0);
			prपूर्णांकk(KERN_ERR "ret = %x\n", ret);
			अगर (ret == SAA_ERR_EMPTY)
				/* Someone अन्यथा alपढ़ोy fetched the response */
				वापस SAA_OK;

			अगर (ret != SAA_OK)
				वापस ret;

			अगर (tRsp.flags & PVC_CMDFLAG_CONTINUE)
				prपूर्णांकk(KERN_ERR "split response\n");
			अन्यथा
				saa7164_cmd_मुक्त_seqno(dev, tRsp.seqno);

			prपूर्णांकk(KERN_ERR " timeout continue\n");
			जारी;
		पूर्ण

		dprपूर्णांकk(DBGLVL_CMD, "%s() signalled seqno(%d) (for dequeue)\n",
			__func__, tRsp.seqno);
		dev->cmds[tRsp.seqno].संकेतled = 1;
		wake_up(q);
		वापस SAA_OK;
	पूर्ण
पूर्ण

अटल पूर्णांक saa7164_cmd_set(काष्ठा saa7164_dev *dev, काष्ठा पंचांगComResInfo *msg,
			   व्योम *buf)
अणु
	काष्ठा पंचांगComResBusInfo *bus = &dev->bus;
	u8 cmd_sent;
	u16 size, idx;
	u32 cmds;
	व्योम *पंचांगp;
	पूर्णांक ret = -1;

	अगर (!msg) अणु
		prपूर्णांकk(KERN_ERR "%s() !msg\n", __func__);
		वापस SAA_ERR_BAD_PARAMETER;
	पूर्ण

	mutex_lock(&dev->cmds[msg->id].lock);

	size = msg->size;
	idx = 0;
	cmds = size / bus->m_wMaxReqSize;
	अगर (size % bus->m_wMaxReqSize == 0)
		cmds -= 1;

	cmd_sent = 0;

	/* Split the request पूर्णांकo smaller chunks */
	क्रम (idx = 0; idx < cmds; idx++) अणु

		msg->flags |= SAA_CMDFLAG_CONTINUE;
		msg->size = bus->m_wMaxReqSize;
		पंचांगp = buf + idx * bus->m_wMaxReqSize;

		ret = saa7164_bus_set(dev, msg, पंचांगp);
		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "%s() set failed %d\n", __func__, ret);

			अगर (cmd_sent) अणु
				ret = SAA_ERR_BUSY;
				जाओ out;
			पूर्ण
			ret = SAA_ERR_OVERFLOW;
			जाओ out;
		पूर्ण
		cmd_sent = 1;
	पूर्ण

	/* If not the last command... */
	अगर (idx != 0)
		msg->flags &= ~SAA_CMDFLAG_CONTINUE;

	msg->size = size - idx * bus->m_wMaxReqSize;

	ret = saa7164_bus_set(dev, msg, buf + idx * bus->m_wMaxReqSize);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() set last failed %d\n", __func__, ret);

		अगर (cmd_sent) अणु
			ret = SAA_ERR_BUSY;
			जाओ out;
		पूर्ण
		ret = SAA_ERR_OVERFLOW;
		जाओ out;
	पूर्ण
	ret = SAA_OK;

out:
	mutex_unlock(&dev->cmds[msg->id].lock);
	वापस ret;
पूर्ण

/* Wait क्रम a संकेत event, without holding a mutex. Either वापस TIMEOUT अगर
 * the event never occurred, or SAA_OK अगर it was संकेतed during the रुको.
 */
अटल पूर्णांक saa7164_cmd_रुको(काष्ठा saa7164_dev *dev, u8 seqno)
अणु
	रुको_queue_head_t *q = शून्य;
	पूर्णांक ret = SAA_BUS_TIMEOUT;
	अचिन्हित दीर्घ stamp;
	पूर्णांक r;

	अगर (saa_debug >= 4)
		saa7164_bus_dump(dev);

	dprपूर्णांकk(DBGLVL_CMD, "%s(seqno=%d)\n", __func__, seqno);

	mutex_lock(&dev->lock);
	अगर ((dev->cmds[seqno].inuse == 1) &&
		(dev->cmds[seqno].seqno == seqno)) अणु
		q = &dev->cmds[seqno].रुको;
	पूर्ण
	mutex_unlock(&dev->lock);

	अगर (q) अणु
		/* If we haven't been संकेतled we need to रुको */
		अगर (dev->cmds[seqno].संकेतled == 0) अणु
			stamp = jअगरfies;
			dprपूर्णांकk(DBGLVL_CMD,
				"%s(seqno=%d) Waiting (signalled=%d)\n",
				__func__, seqno, dev->cmds[seqno].संकेतled);

			/* Wait क्रम संकेतled to be flagged or समयout */
			/* In a highly stressed प्रणाली this can easily extend
			 * पूर्णांकo multiple seconds beक्रमe the deferred worker
			 * is scheduled, and we're woken up via संकेत.
			 * We typically are संकेतled in < 50ms but it can
			 * take MUCH दीर्घer.
			 */
			रुको_event_समयout(*q, dev->cmds[seqno].संकेतled,
				(HZ * रुकोsecs));
			r = समय_beक्रमe(jअगरfies, stamp + (HZ * रुकोsecs));
			अगर (r)
				ret = SAA_OK;
			अन्यथा
				saa7164_cmd_समयout_seqno(dev, seqno);

			dprपूर्णांकk(DBGLVL_CMD, "%s(seqno=%d) Waiting res = %d (signalled=%d)\n",
				__func__, seqno, r,
				dev->cmds[seqno].संकेतled);
		पूर्ण अन्यथा
			ret = SAA_OK;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "%s(seqno=%d) seqno is invalid\n",
			__func__, seqno);

	वापस ret;
पूर्ण

व्योम saa7164_cmd_संकेत(काष्ठा saa7164_dev *dev, u8 seqno)
अणु
	पूर्णांक i;
	dprपूर्णांकk(DBGLVL_CMD, "%s()\n", __func__);

	mutex_lock(&dev->lock);
	क्रम (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) अणु
		अगर (dev->cmds[i].inuse == 1) अणु
			dprपूर्णांकk(DBGLVL_CMD,
				"seqno %d inuse, sig = %d, t/out = %d\n",
				dev->cmds[i].seqno,
				dev->cmds[i].संकेतled,
				dev->cmds[i].समयout);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SAA_CMD_MAX_MSG_UNITS; i++) अणु
		अगर ((dev->cmds[i].inuse == 1) && ((i == 0) ||
			(dev->cmds[i].संकेतled) || (dev->cmds[i].समयout))) अणु
			dprपूर्णांकk(DBGLVL_CMD, "%s(seqno=%d) calling wake_up\n",
				__func__, i);
			dev->cmds[i].संकेतled = 1;
			wake_up(&dev->cmds[i].रुको);
		पूर्ण
	पूर्ण
	mutex_unlock(&dev->lock);
पूर्ण

पूर्णांक saa7164_cmd_send(काष्ठा saa7164_dev *dev, u8 id, क्रमागत पंचांगComResCmd command,
	u16 controlselector, u16 size, व्योम *buf)
अणु
	काष्ठा पंचांगComResInfo command_t, *pcommand_t;
	काष्ठा पंचांगComResInfo response_t, *presponse_t;
	u8 errdata[256];
	u16 resp_dsize;
	u16 data_recd;
	u32 loop;
	पूर्णांक ret;
	पूर्णांक safety = 0;

	dprपूर्णांकk(DBGLVL_CMD, "%s(unitid = %s (%d) , command = 0x%x, sel = 0x%x)\n",
		__func__, saa7164_unitid_name(dev, id), id,
		command, controlselector);

	अगर ((size == 0) || (buf == शून्य)) अणु
		prपूर्णांकk(KERN_ERR "%s() Invalid param\n", __func__);
		वापस SAA_ERR_BAD_PARAMETER;
	पूर्ण

	/* Prepare some basic command/response काष्ठाures */
	स_रखो(&command_t, 0, माप(command_t));
	स_रखो(&response_t, 0, माप(response_t));
	pcommand_t = &command_t;
	presponse_t = &response_t;
	command_t.id = id;
	command_t.command = command;
	command_t.controlselector = controlselector;
	command_t.size = size;

	/* Allocate a unique sequence number */
	ret = saa7164_cmd_alloc_seqno(dev);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s() No free sequences\n", __func__);
		ret = SAA_ERR_NO_RESOURCES;
		जाओ out;
	पूर्ण

	command_t.seqno = (u8)ret;

	/* Send Command */
	resp_dsize = size;
	pcommand_t->size = size;

	dprपूर्णांकk(DBGLVL_CMD, "%s() pcommand_t.seqno = %d\n",
		__func__, pcommand_t->seqno);

	dprपूर्णांकk(DBGLVL_CMD, "%s() pcommand_t.size = %d\n",
		__func__, pcommand_t->size);

	ret = saa7164_cmd_set(dev, pcommand_t, buf);
	अगर (ret != SAA_OK) अणु
		prपूर्णांकk(KERN_ERR "%s() set command failed %d\n", __func__, ret);

		अगर (ret != SAA_ERR_BUSY)
			saa7164_cmd_मुक्त_seqno(dev, pcommand_t->seqno);
		अन्यथा
			/* Flag a समयout, because at least one
			 * command was sent */
			saa7164_cmd_समयout_seqno(dev, pcommand_t->seqno);

		जाओ out;
	पूर्ण

	/* With split responses we have to collect the msgs piece by piece */
	data_recd = 0;
	loop = 1;
	जबतक (loop) अणु
		dprपूर्णांकk(DBGLVL_CMD, "%s() loop\n", __func__);

		ret = saa7164_cmd_रुको(dev, pcommand_t->seqno);
		dprपूर्णांकk(DBGLVL_CMD, "%s() loop ret = %d\n", __func__, ret);

		/* अगर घातer is करोwn and this is not a घातer command ... */

		अगर (ret == SAA_BUS_TIMEOUT) अणु
			prपूर्णांकk(KERN_ERR "Event timed out\n");
			saa7164_cmd_समयout_seqno(dev, pcommand_t->seqno);
			वापस ret;
		पूर्ण

		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "spurious error\n");
			वापस ret;
		पूर्ण

		/* Peek response */
		ret = saa7164_bus_get(dev, presponse_t, शून्य, 1);
		अगर (ret == SAA_ERR_EMPTY) अणु
			dprपूर्णांकk(4, "%s() SAA_ERR_EMPTY\n", __func__);
			जारी;
		पूर्ण
		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "peek failed\n");
			वापस ret;
		पूर्ण

		dprपूर्णांकk(DBGLVL_CMD, "%s() presponse_t->seqno = %d\n",
			__func__, presponse_t->seqno);

		dprपूर्णांकk(DBGLVL_CMD, "%s() presponse_t->flags = 0x%x\n",
			__func__, presponse_t->flags);

		dprपूर्णांकk(DBGLVL_CMD, "%s() presponse_t->size = %d\n",
			__func__, presponse_t->size);

		/* Check अगर the response was क्रम our command */
		अगर (presponse_t->seqno != pcommand_t->seqno) अणु

			dprपूर्णांकk(DBGLVL_CMD,
				"wrong event: seqno = %d, expected seqno = %d, will dequeue regardless\n",
				presponse_t->seqno, pcommand_t->seqno);

			ret = saa7164_cmd_dequeue(dev);
			अगर (ret != SAA_OK) अणु
				prपूर्णांकk(KERN_ERR "dequeue failed, ret = %d\n",
					ret);
				अगर (safety++ > 16) अणु
					prपूर्णांकk(KERN_ERR
					"dequeue exceeded, safety exit\n");
					वापस SAA_ERR_BUSY;
				पूर्ण
			पूर्ण

			जारी;
		पूर्ण

		अगर ((presponse_t->flags & PVC_RESPONSEFLAG_ERROR) != 0) अणु

			स_रखो(&errdata[0], 0, माप(errdata));

			ret = saa7164_bus_get(dev, presponse_t, &errdata[0], 0);
			अगर (ret != SAA_OK) अणु
				prपूर्णांकk(KERN_ERR "get error(2)\n");
				वापस ret;
			पूर्ण

			saa7164_cmd_मुक्त_seqno(dev, pcommand_t->seqno);

			dprपूर्णांकk(DBGLVL_CMD, "%s() errdata %02x%02x%02x%02x\n",
				__func__, errdata[0], errdata[1], errdata[2],
				errdata[3]);

			/* Map error codes */
			dprपूर्णांकk(DBGLVL_CMD, "%s() cmd, error code  = 0x%x\n",
				__func__, errdata[0]);

			चयन (errdata[0]) अणु
			हाल PVC_ERRORCODE_INVALID_COMMAND:
				dprपूर्णांकk(DBGLVL_CMD, "%s() INVALID_COMMAND\n",
					__func__);
				ret = SAA_ERR_INVALID_COMMAND;
				अवरोध;
			हाल PVC_ERRORCODE_INVALID_DATA:
				dprपूर्णांकk(DBGLVL_CMD, "%s() INVALID_DATA\n",
					__func__);
				ret = SAA_ERR_BAD_PARAMETER;
				अवरोध;
			हाल PVC_ERRORCODE_TIMEOUT:
				dprपूर्णांकk(DBGLVL_CMD, "%s() TIMEOUT\n", __func__);
				ret = SAA_ERR_TIMEOUT;
				अवरोध;
			हाल PVC_ERRORCODE_NAK:
				dprपूर्णांकk(DBGLVL_CMD, "%s() NAK\n", __func__);
				ret = SAA_ERR_शून्य_PACKET;
				अवरोध;
			हाल PVC_ERRORCODE_UNKNOWN:
			हाल PVC_ERRORCODE_INVALID_CONTROL:
				dprपूर्णांकk(DBGLVL_CMD,
					"%s() UNKNOWN OR INVALID CONTROL\n",
					__func__);
				ret = SAA_ERR_NOT_SUPPORTED;
				अवरोध;
			शेष:
				dprपूर्णांकk(DBGLVL_CMD, "%s() UNKNOWN\n", __func__);
				ret = SAA_ERR_NOT_SUPPORTED;
			पूर्ण

			/* See of other commands are on the bus */
			अगर (saa7164_cmd_dequeue(dev) != SAA_OK)
				prपूर्णांकk(KERN_ERR "dequeue(2) failed\n");

			वापस ret;
		पूर्ण

		/* If response is invalid */
		अगर ((presponse_t->id != pcommand_t->id) ||
			(presponse_t->command != pcommand_t->command) ||
			(presponse_t->controlselector !=
				pcommand_t->controlselector) ||
			(((resp_dsize - data_recd) != presponse_t->size) &&
				!(presponse_t->flags & PVC_CMDFLAG_CONTINUE)) ||
			((resp_dsize - data_recd) < presponse_t->size)) अणु

			/* Invalid */
			dprपूर्णांकk(DBGLVL_CMD, "%s() Invalid\n", __func__);
			ret = saa7164_bus_get(dev, presponse_t, शून्य, 0);
			अगर (ret != SAA_OK) अणु
				prपूर्णांकk(KERN_ERR "get failed\n");
				वापस ret;
			पूर्ण

			/* See of other commands are on the bus */
			अगर (saa7164_cmd_dequeue(dev) != SAA_OK)
				prपूर्णांकk(KERN_ERR "dequeue(3) failed\n");
			जारी;
		पूर्ण

		/* OK, now we're actually getting out correct response */
		ret = saa7164_bus_get(dev, presponse_t, buf + data_recd, 0);
		अगर (ret != SAA_OK) अणु
			prपूर्णांकk(KERN_ERR "get failed\n");
			वापस ret;
		पूर्ण

		data_recd = presponse_t->size + data_recd;
		अगर (resp_dsize == data_recd) अणु
			dprपूर्णांकk(DBGLVL_CMD, "%s() Resp recd\n", __func__);
			अवरोध;
		पूर्ण

		/* See of other commands are on the bus */
		अगर (saa7164_cmd_dequeue(dev) != SAA_OK)
			prपूर्णांकk(KERN_ERR "dequeue(3) failed\n");

		जारी;

	पूर्ण /* (loop) */

	/* Release the sequence number allocation */
	saa7164_cmd_मुक्त_seqno(dev, pcommand_t->seqno);

	/* अगर घातerकरोwn संकेत all pending commands */

	dprपूर्णांकk(DBGLVL_CMD, "%s() Calling dequeue then exit\n", __func__);

	/* See of other commands are on the bus */
	अगर (saa7164_cmd_dequeue(dev) != SAA_OK)
		prपूर्णांकk(KERN_ERR "dequeue(4) failed\n");

	ret = SAA_OK;
out:
	वापस ret;
पूर्ण

