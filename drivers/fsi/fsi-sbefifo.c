<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) IBM Corporation 2017
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERGCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/fsi.h>
#समावेश <linux/fsi-sbefअगरo.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cdev.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/uपन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>

/*
 * The SBEFIFO is a pipe-like FSI device क्रम communicating with
 * the self boot engine on POWER processors.
 */

#घोषणा DEVICE_NAME		"sbefifo"
#घोषणा FSI_ENGID_SBE		0x22

/*
 * Register layout
 */

/* Register banks */
#घोषणा SBEFIFO_UP		0x00		/* FSI -> Host */
#घोषणा SBEFIFO_DOWN		0x40		/* Host -> FSI */

/* Per-bank रेजिस्टरs */
#घोषणा SBEFIFO_FIFO		0x00		/* The FIFO itself */
#घोषणा SBEFIFO_STS		0x04		/* Status रेजिस्टर */
#घोषणा   SBEFIFO_STS_PARITY_ERR	0x20000000
#घोषणा   SBEFIFO_STS_RESET_REQ		0x02000000
#घोषणा   SBEFIFO_STS_GOT_EOT		0x00800000
#घोषणा   SBEFIFO_STS_MAX_XFER_LIMIT	0x00400000
#घोषणा   SBEFIFO_STS_FULL		0x00200000
#घोषणा   SBEFIFO_STS_EMPTY		0x00100000
#घोषणा   SBEFIFO_STS_ECNT_MASK		0x000f0000
#घोषणा   SBEFIFO_STS_ECNT_SHIFT	16
#घोषणा   SBEFIFO_STS_VALID_MASK	0x0000ff00
#घोषणा   SBEFIFO_STS_VALID_SHIFT	8
#घोषणा   SBEFIFO_STS_EOT_MASK		0x000000ff
#घोषणा   SBEFIFO_STS_EOT_SHIFT		0
#घोषणा SBEFIFO_EOT_RAISE	0x08		/* (Up only) Set End Of Transfer */
#घोषणा SBEFIFO_REQ_RESET	0x0C		/* (Up only) Reset Request */
#घोषणा SBEFIFO_PERFORM_RESET	0x10		/* (Down only) Perक्रमm Reset */
#घोषणा SBEFIFO_EOT_ACK		0x14		/* (Down only) Acknowledge EOT */
#घोषणा SBEFIFO_DOWN_MAX	0x18		/* (Down only) Max transfer */

/* CFAM GP Mailbox SelfBoot Message रेजिस्टर */
#घोषणा CFAM_GP_MBOX_SBM_ADDR	0x2824	/* Converted 0x2809 */

#घोषणा CFAM_SBM_SBE_BOOTED		0x80000000
#घोषणा CFAM_SBM_SBE_ASYNC_FFDC		0x40000000
#घोषणा CFAM_SBM_SBE_STATE_MASK		0x00f00000
#घोषणा CFAM_SBM_SBE_STATE_SHIFT	20

क्रमागत sbe_state
अणु
	SBE_STATE_UNKNOWN = 0x0, // Unkown, initial state
	SBE_STATE_IPLING  = 0x1, // IPL'ing - स्वतःnomous mode (transient)
	SBE_STATE_ISTEP   = 0x2, // ISTEP - Running IPL by steps (transient)
	SBE_STATE_MPIPL   = 0x3, // MPIPL
	SBE_STATE_RUNTIME = 0x4, // SBE Runसमय
	SBE_STATE_DMT     = 0x5, // Dead Man Timer State (transient)
	SBE_STATE_DUMP    = 0x6, // Dumping
	SBE_STATE_FAILURE = 0x7, // Internal SBE failure
	SBE_STATE_QUIESCE = 0x8, // Final state - needs SBE reset to get out
पूर्ण;

/* FIFO depth */
#घोषणा SBEFIFO_FIFO_DEPTH		8

/* Helpers */
#घोषणा sbefअगरo_empty(sts)	((sts) & SBEFIFO_STS_EMPTY)
#घोषणा sbefअगरo_full(sts)	((sts) & SBEFIFO_STS_FULL)
#घोषणा sbefअगरo_parity_err(sts)	((sts) & SBEFIFO_STS_PARITY_ERR)
#घोषणा sbefअगरo_populated(sts)	(((sts) & SBEFIFO_STS_ECNT_MASK) >> SBEFIFO_STS_ECNT_SHIFT)
#घोषणा sbefअगरo_vacant(sts)	(SBEFIFO_FIFO_DEPTH - sbefअगरo_populated(sts))
#घोषणा sbefअगरo_eot_set(sts)	(((sts) & SBEFIFO_STS_EOT_MASK) >> SBEFIFO_STS_EOT_SHIFT)

/* Reset request समयout in ms */
#घोषणा SBEFIFO_RESET_TIMEOUT		10000

/* Timeouts क्रम commands in ms */
#घोषणा SBEFIFO_TIMEOUT_START_CMD	10000
#घोषणा SBEFIFO_TIMEOUT_IN_CMD		1000
#घोषणा SBEFIFO_TIMEOUT_START_RSP	10000
#घोषणा SBEFIFO_TIMEOUT_IN_RSP		1000

/* Other स्थिरants */
#घोषणा SBEFIFO_MAX_USER_CMD_LEN	(0x100000 + PAGE_SIZE)
#घोषणा SBEFIFO_RESET_MAGIC		0x52534554 /* "RSET" */

काष्ठा sbefअगरo अणु
	uपूर्णांक32_t		magic;
#घोषणा SBEFIFO_MAGIC		0x53424546 /* "SBEF" */
	काष्ठा fsi_device	*fsi_dev;
	काष्ठा device		dev;
	काष्ठा cdev		cdev;
	काष्ठा mutex		lock;
	bool			broken;
	bool			dead;
	bool			async_ffdc;
पूर्ण;

काष्ठा sbefअगरo_user अणु
	काष्ठा sbefअगरo		*sbefअगरo;
	काष्ठा mutex		file_lock;
	व्योम			*cmd_page;
	व्योम			*pending_cmd;
	माप_प्रकार			pending_len;
पूर्ण;

अटल DEFINE_MUTEX(sbefअगरo_ffdc_mutex);


अटल व्योम __sbefअगरo_dump_ffdc(काष्ठा device *dev, स्थिर __be32 *ffdc,
				माप_प्रकार ffdc_sz, bool पूर्णांकernal)
अणु
	पूर्णांक pack = 0;
#घोषणा FFDC_LSIZE	60
	अटल अक्षर ffdc_line[FFDC_LSIZE];
	अक्षर *p = ffdc_line;

	जबतक (ffdc_sz) अणु
		u32 w0, w1, w2, i;
		अगर (ffdc_sz < 3) अणु
			dev_err(dev, "SBE invalid FFDC package size %zd\n", ffdc_sz);
			वापस;
		पूर्ण
		w0 = be32_to_cpu(*(ffdc++));
		w1 = be32_to_cpu(*(ffdc++));
		w2 = be32_to_cpu(*(ffdc++));
		ffdc_sz -= 3;
		अगर ((w0 >> 16) != 0xFFDC) अणु
			dev_err(dev, "SBE invalid FFDC package signature %08x %08x %08x\n",
				w0, w1, w2);
			अवरोध;
		पूर्ण
		w0 &= 0xffff;
		अगर (w0 > ffdc_sz) अणु
			dev_err(dev, "SBE FFDC package len %d words but only %zd remaining\n",
				w0, ffdc_sz);
			w0 = ffdc_sz;
			अवरोध;
		पूर्ण
		अगर (पूर्णांकernal) अणु
			dev_warn(dev, "+---- SBE FFDC package %d for async err -----+\n",
				 pack++);
		पूर्ण अन्यथा अणु
			dev_warn(dev, "+---- SBE FFDC package %d for cmd %02x:%02x -----+\n",
				 pack++, (w1 >> 8) & 0xff, w1 & 0xff);
		पूर्ण
		dev_warn(dev, "| Response code: %08x                   |\n", w2);
		dev_warn(dev, "|-------------------------------------------|\n");
		क्रम (i = 0; i < w0; i++) अणु
			अगर ((i & 3) == 0) अणु
				p = ffdc_line;
				p += प्र_लिखो(p, "| %04x:", i << 4);
			पूर्ण
			p += प्र_लिखो(p, " %08x", be32_to_cpu(*(ffdc++)));
			ffdc_sz--;
			अगर ((i & 3) == 3 || i == (w0 - 1)) अणु
				जबतक ((i & 3) < 3) अणु
					p += प्र_लिखो(p, "         ");
					i++;
				पूर्ण
				dev_warn(dev, "%s |\n", ffdc_line);
			पूर्ण
		पूर्ण
		dev_warn(dev, "+-------------------------------------------+\n");
	पूर्ण
पूर्ण

अटल व्योम sbefअगरo_dump_ffdc(काष्ठा device *dev, स्थिर __be32 *ffdc,
			      माप_प्रकार ffdc_sz, bool पूर्णांकernal)
अणु
	mutex_lock(&sbefअगरo_ffdc_mutex);
	__sbefअगरo_dump_ffdc(dev, ffdc, ffdc_sz, पूर्णांकernal);
	mutex_unlock(&sbefअगरo_ffdc_mutex);
पूर्ण

पूर्णांक sbefअगरo_parse_status(काष्ठा device *dev, u16 cmd, __be32 *response,
			 माप_प्रकार resp_len, माप_प्रकार *data_len)
अणु
	u32 dh, s0, s1;
	माप_प्रकार ffdc_sz;

	अगर (resp_len < 3) अणु
		pr_debug("sbefifo: cmd %04x, response too small: %zd\n",
			 cmd, resp_len);
		वापस -ENXIO;
	पूर्ण
	dh = be32_to_cpu(response[resp_len - 1]);
	अगर (dh > resp_len || dh < 3) अणु
		dev_err(dev, "SBE cmd %02x:%02x status offset out of range: %d/%zd\n",
			cmd >> 8, cmd & 0xff, dh, resp_len);
		वापस -ENXIO;
	पूर्ण
	s0 = be32_to_cpu(response[resp_len - dh]);
	s1 = be32_to_cpu(response[resp_len - dh + 1]);
	अगर (((s0 >> 16) != 0xC0DE) || ((s0 & 0xffff) != cmd)) अणु
		dev_err(dev, "SBE cmd %02x:%02x, status signature invalid: 0x%08x 0x%08x\n",
			cmd >> 8, cmd & 0xff, s0, s1);
		वापस -ENXIO;
	पूर्ण
	अगर (s1 != 0) अणु
		ffdc_sz = dh - 3;
		dev_warn(dev, "SBE error cmd %02x:%02x status=%04x:%04x\n",
			 cmd >> 8, cmd & 0xff, s1 >> 16, s1 & 0xffff);
		अगर (ffdc_sz)
			sbefअगरo_dump_ffdc(dev, &response[resp_len - dh + 2],
					  ffdc_sz, false);
	पूर्ण
	अगर (data_len)
		*data_len = resp_len - dh;

	/*
	 * Primary status करोn't have the top bit set, so can't be confused with
	 * Linux negative error codes, so वापस the status word whole.
	 */
	वापस s1;
पूर्ण
EXPORT_SYMBOL_GPL(sbefअगरo_parse_status);

अटल पूर्णांक sbefअगरo_regr(काष्ठा sbefअगरo *sbefअगरo, पूर्णांक reg, u32 *word)
अणु
	__be32 raw_word;
	पूर्णांक rc;

	rc = fsi_device_पढ़ो(sbefअगरo->fsi_dev, reg, &raw_word,
			     माप(raw_word));
	अगर (rc)
		वापस rc;

	*word = be32_to_cpu(raw_word);

	वापस 0;
पूर्ण

अटल पूर्णांक sbefअगरo_regw(काष्ठा sbefअगरo *sbefअगरo, पूर्णांक reg, u32 word)
अणु
	__be32 raw_word = cpu_to_be32(word);

	वापस fsi_device_ग_लिखो(sbefअगरo->fsi_dev, reg, &raw_word,
				माप(raw_word));
पूर्ण

अटल पूर्णांक sbefअगरo_check_sbe_state(काष्ठा sbefअगरo *sbefअगरo)
अणु
	__be32 raw_word;
	u32 sbm;
	पूर्णांक rc;

	rc = fsi_slave_पढ़ो(sbefअगरo->fsi_dev->slave, CFAM_GP_MBOX_SBM_ADDR,
			    &raw_word, माप(raw_word));
	अगर (rc)
		वापस rc;
	sbm = be32_to_cpu(raw_word);

	/* SBE booted at all ? */
	अगर (!(sbm & CFAM_SBM_SBE_BOOTED))
		वापस -ESHUTDOWN;

	/* Check its state */
	चयन ((sbm & CFAM_SBM_SBE_STATE_MASK) >> CFAM_SBM_SBE_STATE_SHIFT) अणु
	हाल SBE_STATE_UNKNOWN:
		वापस -ESHUTDOWN;
	हाल SBE_STATE_DMT:
		वापस -EBUSY;
	हाल SBE_STATE_IPLING:
	हाल SBE_STATE_ISTEP:
	हाल SBE_STATE_MPIPL:
	हाल SBE_STATE_RUNTIME:
	हाल SBE_STATE_DUMP: /* Not sure about that one */
		अवरोध;
	हाल SBE_STATE_FAILURE:
	हाल SBE_STATE_QUIESCE:
		वापस -ESHUTDOWN;
	पूर्ण

	/* Is there async FFDC available ? Remember it */
	अगर (sbm & CFAM_SBM_SBE_ASYNC_FFDC)
		sbefअगरo->async_ffdc = true;

	वापस 0;
पूर्ण

/* Don't flip endianness of data to/from FIFO, just pass through. */
अटल पूर्णांक sbefअगरo_करोwn_पढ़ो(काष्ठा sbefअगरo *sbefअगरo, __be32 *word)
अणु
	वापस fsi_device_पढ़ो(sbefअगरo->fsi_dev, SBEFIFO_DOWN, word,
			       माप(*word));
पूर्ण

अटल पूर्णांक sbefअगरo_up_ग_लिखो(काष्ठा sbefअगरo *sbefअगरo, __be32 word)
अणु
	वापस fsi_device_ग_लिखो(sbefअगरo->fsi_dev, SBEFIFO_UP, &word,
				माप(word));
पूर्ण

अटल पूर्णांक sbefअगरo_request_reset(काष्ठा sbefअगरo *sbefअगरo)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	u32 status, समयout;
	पूर्णांक rc;

	dev_dbg(dev, "Requesting FIFO reset\n");

	/* Mark broken first, will be cleared अगर reset succeeds */
	sbefअगरo->broken = true;

	/* Send reset request */
	rc = sbefअगरo_regw(sbefअगरo, SBEFIFO_UP | SBEFIFO_REQ_RESET, 1);
	अगर (rc) अणु
		dev_err(dev, "Sending reset request failed, rc=%d\n", rc);
		वापस rc;
	पूर्ण

	/* Wait क्रम it to complete */
	क्रम (समयout = 0; समयout < SBEFIFO_RESET_TIMEOUT; समयout++) अणु
		rc = sbefअगरo_regr(sbefअगरo, SBEFIFO_UP | SBEFIFO_STS, &status);
		अगर (rc) अणु
			dev_err(dev, "Failed to read UP fifo status during reset"
				" , rc=%d\n", rc);
			वापस rc;
		पूर्ण

		अगर (!(status & SBEFIFO_STS_RESET_REQ)) अणु
			dev_dbg(dev, "FIFO reset done\n");
			sbefअगरo->broken = false;
			वापस 0;
		पूर्ण

		msleep(1);
	पूर्ण
	dev_err(dev, "FIFO reset timed out\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sbefअगरo_cleanup_hw(काष्ठा sbefअगरo *sbefअगरo)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	u32 up_status, करोwn_status;
	bool need_reset = false;
	पूर्णांक rc;

	rc = sbefअगरo_check_sbe_state(sbefअगरo);
	अगर (rc) अणु
		dev_dbg(dev, "SBE state=%d\n", rc);
		वापस rc;
	पूर्ण

	/* If broken, we करोn't need to look at status, go straight to reset */
	अगर (sbefअगरo->broken)
		जाओ करो_reset;

	rc = sbefअगरo_regr(sbefअगरo, SBEFIFO_UP | SBEFIFO_STS, &up_status);
	अगर (rc) अणु
		dev_err(dev, "Cleanup: Reading UP status failed, rc=%d\n", rc);

		/* Will try reset again on next attempt at using it */
		sbefअगरo->broken = true;
		वापस rc;
	पूर्ण

	rc = sbefअगरo_regr(sbefअगरo, SBEFIFO_DOWN | SBEFIFO_STS, &करोwn_status);
	अगर (rc) अणु
		dev_err(dev, "Cleanup: Reading DOWN status failed, rc=%d\n", rc);

		/* Will try reset again on next attempt at using it */
		sbefअगरo->broken = true;
		वापस rc;
	पूर्ण

	/* The FIFO alपढ़ोy contains a reset request from the SBE ? */
	अगर (करोwn_status & SBEFIFO_STS_RESET_REQ) अणु
		dev_info(dev, "Cleanup: FIFO reset request set, resetting\n");
		rc = sbefअगरo_regw(sbefअगरo, SBEFIFO_UP, SBEFIFO_PERFORM_RESET);
		अगर (rc) अणु
			sbefअगरo->broken = true;
			dev_err(dev, "Cleanup: Reset reg write failed, rc=%d\n", rc);
			वापस rc;
		पूर्ण
		sbefअगरo->broken = false;
		वापस 0;
	पूर्ण

	/* Parity error on either FIFO ? */
	अगर ((up_status | करोwn_status) & SBEFIFO_STS_PARITY_ERR)
		need_reset = true;

	/* Either FIFO not empty ? */
	अगर (!((up_status & करोwn_status) & SBEFIFO_STS_EMPTY))
		need_reset = true;

	अगर (!need_reset)
		वापस 0;

	dev_info(dev, "Cleanup: FIFO not clean (up=0x%08x down=0x%08x)\n",
		 up_status, करोwn_status);

 करो_reset:

	/* Mark broken, will be cleared अगर/when reset succeeds */
	वापस sbefअगरo_request_reset(sbefअगरo);
पूर्ण

अटल पूर्णांक sbefअगरo_रुको(काष्ठा sbefअगरo *sbefअगरo, bool up,
			u32 *status, अचिन्हित दीर्घ समयout)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	अचिन्हित दीर्घ end_समय;
	bool पढ़ोy = false;
	u32 addr, sts = 0;
	पूर्णांक rc;

	dev_vdbg(dev, "Wait on %s fifo...\n", up ? "up" : "down");

	addr = (up ? SBEFIFO_UP : SBEFIFO_DOWN) | SBEFIFO_STS;

	end_समय = jअगरfies + समयout;
	जबतक (!समय_after(jअगरfies, end_समय)) अणु
		cond_resched();
		rc = sbefअगरo_regr(sbefअगरo, addr, &sts);
		अगर (rc < 0) अणु
			dev_err(dev, "FSI error %d reading status register\n", rc);
			वापस rc;
		पूर्ण
		अगर (!up && sbefअगरo_parity_err(sts)) अणु
			dev_err(dev, "Parity error in DOWN FIFO\n");
			वापस -ENXIO;
		पूर्ण
		पढ़ोy = !(up ? sbefअगरo_full(sts) : sbefअगरo_empty(sts));
		अगर (पढ़ोy)
			अवरोध;
	पूर्ण
	अगर (!पढ़ोy) अणु
		dev_err(dev, "%s FIFO Timeout ! status=%08x\n", up ? "UP" : "DOWN", sts);
		वापस -ETIMEDOUT;
	पूर्ण
	dev_vdbg(dev, "End of wait status: %08x\n", sts);

	*status = sts;

	वापस 0;
पूर्ण

अटल पूर्णांक sbefअगरo_send_command(काष्ठा sbefअगरo *sbefअगरo,
				स्थिर __be32 *command, माप_प्रकार cmd_len)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	माप_प्रकार len, chunk, vacant = 0, reमुख्यing = cmd_len;
	अचिन्हित दीर्घ समयout;
	u32 status;
	पूर्णांक rc;

	dev_vdbg(dev, "sending command (%zd words, cmd=%04x)\n",
		 cmd_len, be32_to_cpu(command[1]));

	/* As दीर्घ as there's something to send */
	समयout = msecs_to_jअगरfies(SBEFIFO_TIMEOUT_START_CMD);
	जबतक (reमुख्यing) अणु
		/* Wait क्रम room in the FIFO */
		rc = sbefअगरo_रुको(sbefअगरo, true, &status, समयout);
		अगर (rc < 0)
			वापस rc;
		समयout = msecs_to_jअगरfies(SBEFIFO_TIMEOUT_IN_CMD);

		vacant = sbefअगरo_vacant(status);
		len = chunk = min(vacant, reमुख्यing);

		dev_vdbg(dev, "  status=%08x vacant=%zd chunk=%zd\n",
			 status, vacant, chunk);

		/* Write as much as we can */
		जबतक (len--) अणु
			rc = sbefअगरo_up_ग_लिखो(sbefअगरo, *(command++));
			अगर (rc) अणु
				dev_err(dev, "FSI error %d writing UP FIFO\n", rc);
				वापस rc;
			पूर्ण
		पूर्ण
		reमुख्यing -= chunk;
		vacant -= chunk;
	पूर्ण

	/* If there's no room left, रुको क्रम some to ग_लिखो EOT */
	अगर (!vacant) अणु
		rc = sbefअगरo_रुको(sbefअगरo, true, &status, समयout);
		अगर (rc)
			वापस rc;
	पूर्ण

	/* Send an EOT */
	rc = sbefअगरo_regw(sbefअगरo, SBEFIFO_UP | SBEFIFO_EOT_RAISE, 0);
	अगर (rc)
		dev_err(dev, "FSI error %d writing EOT\n", rc);
	वापस rc;
पूर्ण

अटल पूर्णांक sbefअगरo_पढ़ो_response(काष्ठा sbefअगरo *sbefअगरo, काष्ठा iov_iter *response)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	u32 status, eot_set;
	अचिन्हित दीर्घ समयout;
	bool overflow = false;
	__be32 data;
	माप_प्रकार len;
	पूर्णांक rc;

	dev_vdbg(dev, "reading response, buflen = %zd\n", iov_iter_count(response));

	समयout = msecs_to_jअगरfies(SBEFIFO_TIMEOUT_START_RSP);
	क्रम (;;) अणु
		/* Grab FIFO status (this will handle parity errors) */
		rc = sbefअगरo_रुको(sbefअगरo, false, &status, समयout);
		अगर (rc < 0)
			वापस rc;
		समयout = msecs_to_jअगरfies(SBEFIFO_TIMEOUT_IN_RSP);

		/* Decode status */
		len = sbefअगरo_populated(status);
		eot_set = sbefअगरo_eot_set(status);

		dev_vdbg(dev, "  chunk size %zd eot_set=0x%x\n", len, eot_set);

		/* Go through the chunk */
		जबतक(len--) अणु
			/* Read the data */
			rc = sbefअगरo_करोwn_पढ़ो(sbefअगरo, &data);
			अगर (rc < 0)
				वापस rc;

			/* Was it an EOT ? */
			अगर (eot_set & 0x80) अणु
				/*
				 * There should be nothing अन्यथा in the FIFO,
				 * अगर there is, mark broken, this will क्रमce
				 * a reset on next use, but करोn't fail the
				 * command.
				 */
				अगर (len) अणु
					dev_warn(dev, "FIFO read hit"
						 " EOT with still %zd data\n",
						 len);
					sbefअगरo->broken = true;
				पूर्ण

				/* We are करोne */
				rc = sbefअगरo_regw(sbefअगरo,
						  SBEFIFO_DOWN | SBEFIFO_EOT_ACK, 0);

				/*
				 * If that ग_लिखो fail, still complete the request but mark
				 * the fअगरo as broken क्रम subsequent reset (not much अन्यथा
				 * we can करो here).
				 */
				अगर (rc) अणु
					dev_err(dev, "FSI error %d ack'ing EOT\n", rc);
					sbefअगरo->broken = true;
				पूर्ण

				/* Tell whether we overflowed */
				वापस overflow ? -EOVERFLOW : 0;
			पूर्ण

			/* Store it अगर there is room */
			अगर (iov_iter_count(response) >= माप(__be32)) अणु
				अगर (copy_to_iter(&data, माप(__be32), response) < माप(__be32))
					वापस -EFAULT;
			पूर्ण अन्यथा अणु
				dev_vdbg(dev, "Response overflowed !\n");

				overflow = true;
			पूर्ण

			/* Next EOT bit */
			eot_set <<= 1;
		पूर्ण
	पूर्ण
	/* Shouldn't happen */
	वापस -EIO;
पूर्ण

अटल पूर्णांक sbefअगरo_करो_command(काष्ठा sbefअगरo *sbefअगरo,
			      स्थिर __be32 *command, माप_प्रकार cmd_len,
			      काष्ठा iov_iter *response)
अणु
	/* Try sending the command */
	पूर्णांक rc = sbefअगरo_send_command(sbefअगरo, command, cmd_len);
	अगर (rc)
		वापस rc;

	/* Now, get the response */
	वापस sbefअगरo_पढ़ो_response(sbefअगरo, response);
पूर्ण

अटल व्योम sbefअगरo_collect_async_ffdc(काष्ठा sbefअगरo *sbefअगरo)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
        काष्ठा iov_iter ffdc_iter;
        काष्ठा kvec ffdc_iov;
	__be32 *ffdc;
	माप_प्रकार ffdc_sz;
	__be32 cmd[2];
	पूर्णांक rc;

	sbefअगरo->async_ffdc = false;
	ffdc = vदो_स्मृति(SBEFIFO_MAX_FFDC_SIZE);
	अगर (!ffdc) अणु
		dev_err(dev, "Failed to allocate SBE FFDC buffer\n");
		वापस;
	पूर्ण
        ffdc_iov.iov_base = ffdc;
	ffdc_iov.iov_len = SBEFIFO_MAX_FFDC_SIZE;
        iov_iter_kvec(&ffdc_iter, WRITE, &ffdc_iov, 1, SBEFIFO_MAX_FFDC_SIZE);
	cmd[0] = cpu_to_be32(2);
	cmd[1] = cpu_to_be32(SBEFIFO_CMD_GET_SBE_FFDC);
	rc = sbefअगरo_करो_command(sbefअगरo, cmd, 2, &ffdc_iter);
	अगर (rc != 0) अणु
		dev_err(dev, "Error %d retrieving SBE FFDC\n", rc);
		जाओ bail;
	पूर्ण
	ffdc_sz = SBEFIFO_MAX_FFDC_SIZE - iov_iter_count(&ffdc_iter);
	ffdc_sz /= माप(__be32);
	rc = sbefअगरo_parse_status(dev, SBEFIFO_CMD_GET_SBE_FFDC, ffdc,
				  ffdc_sz, &ffdc_sz);
	अगर (rc != 0) अणु
		dev_err(dev, "Error %d decoding SBE FFDC\n", rc);
		जाओ bail;
	पूर्ण
	अगर (ffdc_sz > 0)
		sbefअगरo_dump_ffdc(dev, ffdc, ffdc_sz, true);
 bail:
	vमुक्त(ffdc);

पूर्ण

अटल पूर्णांक __sbefअगरo_submit(काष्ठा sbefअगरo *sbefअगरo,
			    स्थिर __be32 *command, माप_प्रकार cmd_len,
			    काष्ठा iov_iter *response)
अणु
	काष्ठा device *dev = &sbefअगरo->fsi_dev->dev;
	पूर्णांक rc;

	अगर (sbefअगरo->dead)
		वापस -ENODEV;

	अगर (cmd_len < 2 || be32_to_cpu(command[0]) != cmd_len) अणु
		dev_vdbg(dev, "Invalid command len %zd (header: %d)\n",
			 cmd_len, be32_to_cpu(command[0]));
		वापस -EINVAL;
	पूर्ण

	/* First ensure the HW is in a clean state */
	rc = sbefअगरo_cleanup_hw(sbefअगरo);
	अगर (rc)
		वापस rc;

	/* Look क्रम async FFDC first अगर any */
	अगर (sbefअगरo->async_ffdc)
		sbefअगरo_collect_async_ffdc(sbefअगरo);

	rc = sbefअगरo_करो_command(sbefअगरo, command, cmd_len, response);
	अगर (rc != 0 && rc != -EOVERFLOW)
		जाओ fail;
	वापस rc;
 fail:
	/*
	 * On failure, attempt a reset. Ignore the result, it will mark
	 * the fअगरo broken अगर the reset fails
	 */
        sbefअगरo_request_reset(sbefअगरo);

	/* Return original error */
	वापस rc;
पूर्ण

/**
 * sbefअगरo_submit() - Submit and SBE fअगरo command and receive response
 * @dev: The sbefअगरo device
 * @command: The raw command data
 * @cmd_len: The command size (in 32-bit words)
 * @response: The output response buffer
 * @resp_len: In: Response buffer size, Out: Response size
 *
 * This will perक्रमm the entire operation. If the reponse buffer
 * overflows, वापसs -EOVERFLOW
 */
पूर्णांक sbefअगरo_submit(काष्ठा device *dev, स्थिर __be32 *command, माप_प्रकार cmd_len,
		   __be32 *response, माप_प्रकार *resp_len)
अणु
	काष्ठा sbefअगरo *sbefअगरo;
        काष्ठा iov_iter resp_iter;
        काष्ठा kvec resp_iov;
	माप_प्रकार rbytes;
	पूर्णांक rc;

	अगर (!dev)
		वापस -ENODEV;
	sbefअगरo = dev_get_drvdata(dev);
	अगर (!sbefअगरo)
		वापस -ENODEV;
	अगर (WARN_ON_ONCE(sbefअगरo->magic != SBEFIFO_MAGIC))
		वापस -ENODEV;
	अगर (!resp_len || !command || !response)
		वापस -EINVAL;

	/* Prepare iov iterator */
	rbytes = (*resp_len) * माप(__be32);
	resp_iov.iov_base = response;
	resp_iov.iov_len = rbytes;
        iov_iter_kvec(&resp_iter, WRITE, &resp_iov, 1, rbytes);

	/* Perक्रमm the command */
	mutex_lock(&sbefअगरo->lock);
	rc = __sbefअगरo_submit(sbefअगरo, command, cmd_len, &resp_iter);
	mutex_unlock(&sbefअगरo->lock);

	/* Extract the response length */
	rbytes -= iov_iter_count(&resp_iter);
	*resp_len = rbytes / माप(__be32);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(sbefअगरo_submit);

/*
 * Char device पूर्णांकerface
 */

अटल व्योम sbefअगरo_release_command(काष्ठा sbefअगरo_user *user)
अणु
	अगर (is_vदो_स्मृति_addr(user->pending_cmd))
		vमुक्त(user->pending_cmd);
	user->pending_cmd = शून्य;
	user->pending_len = 0;
पूर्ण

अटल पूर्णांक sbefअगरo_user_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sbefअगरo *sbefअगरo = container_of(inode->i_cdev, काष्ठा sbefअगरo, cdev);
	काष्ठा sbefअगरo_user *user;

	user = kzalloc(माप(काष्ठा sbefअगरo_user), GFP_KERNEL);
	अगर (!user)
		वापस -ENOMEM;

	file->निजी_data = user;
	user->sbefअगरo = sbefअगरo;
	user->cmd_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!user->cmd_page) अणु
		kमुक्त(user);
		वापस -ENOMEM;
	पूर्ण
	mutex_init(&user->file_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार sbefअगरo_user_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा sbefअगरo_user *user = file->निजी_data;
	काष्ठा sbefअगरo *sbefअगरo;
	काष्ठा iov_iter resp_iter;
        काष्ठा iovec resp_iov;
	माप_प्रकार cmd_len;
	पूर्णांक rc;

	अगर (!user)
		वापस -EINVAL;
	sbefअगरo = user->sbefअगरo;
	अगर (len & 3)
		वापस -EINVAL;

	mutex_lock(&user->file_lock);

	/* Cronus relies on -EAGAIN after a लघु पढ़ो */
	अगर (user->pending_len == 0) अणु
		rc = -EAGAIN;
		जाओ bail;
	पूर्ण
	अगर (user->pending_len < 8) अणु
		rc = -EINVAL;
		जाओ bail;
	पूर्ण
	cmd_len = user->pending_len >> 2;

	/* Prepare iov iterator */
	resp_iov.iov_base = buf;
	resp_iov.iov_len = len;
	iov_iter_init(&resp_iter, WRITE, &resp_iov, 1, len);

	/* Perक्रमm the command */
	mutex_lock(&sbefअगरo->lock);
	rc = __sbefअगरo_submit(sbefअगरo, user->pending_cmd, cmd_len, &resp_iter);
	mutex_unlock(&sbefअगरo->lock);
	अगर (rc < 0)
		जाओ bail;

	/* Extract the response length */
	rc = len - iov_iter_count(&resp_iter);
 bail:
	sbefअगरo_release_command(user);
	mutex_unlock(&user->file_lock);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार sbefअगरo_user_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार len, loff_t *offset)
अणु
	काष्ठा sbefअगरo_user *user = file->निजी_data;
	काष्ठा sbefअगरo *sbefअगरo;
	पूर्णांक rc = len;

	अगर (!user)
		वापस -EINVAL;
	sbefअगरo = user->sbefअगरo;
	अगर (len > SBEFIFO_MAX_USER_CMD_LEN)
		वापस -EINVAL;
	अगर (len & 3)
		वापस -EINVAL;

	mutex_lock(&user->file_lock);

	/* Can we use the pre-allocate buffer ? If not, allocate */
	अगर (len <= PAGE_SIZE)
		user->pending_cmd = user->cmd_page;
	अन्यथा
		user->pending_cmd = vदो_स्मृति(len);
	अगर (!user->pending_cmd) अणु
		rc = -ENOMEM;
		जाओ bail;
	पूर्ण

	/* Copy the command पूर्णांकo the staging buffer */
	अगर (copy_from_user(user->pending_cmd, buf, len)) अणु
		rc = -EFAULT;
		जाओ bail;
	पूर्ण

	/* Check क्रम the magic reset command */
	अगर (len == 4 && be32_to_cpu(*(__be32 *)user->pending_cmd) ==
	    SBEFIFO_RESET_MAGIC)  अणु

		/* Clear out any pending command */
		user->pending_len = 0;

		/* Trigger reset request */
		mutex_lock(&sbefअगरo->lock);
		rc = sbefअगरo_request_reset(user->sbefअगरo);
		mutex_unlock(&sbefअगरo->lock);
		अगर (rc == 0)
			rc = 4;
		जाओ bail;
	पूर्ण

	/* Update the staging buffer size */
	user->pending_len = len;
 bail:
	अगर (!user->pending_len)
		sbefअगरo_release_command(user);

	mutex_unlock(&user->file_lock);

	/* And that's it, we'll issue the command on a पढ़ो */
	वापस rc;
पूर्ण

अटल पूर्णांक sbefअगरo_user_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा sbefअगरo_user *user = file->निजी_data;

	अगर (!user)
		वापस -EINVAL;

	sbefअगरo_release_command(user);
	मुक्त_page((अचिन्हित दीर्घ)user->cmd_page);
	kमुक्त(user);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations sbefअगरo_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= sbefअगरo_user_खोलो,
	.पढ़ो		= sbefअगरo_user_पढ़ो,
	.ग_लिखो		= sbefअगरo_user_ग_लिखो,
	.release	= sbefअगरo_user_release,
पूर्ण;

अटल व्योम sbefअगरo_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा sbefअगरo *sbefअगरo = container_of(dev, काष्ठा sbefअगरo, dev);

	put_device(&sbefअगरo->fsi_dev->dev);
	kमुक्त(sbefअगरo);
पूर्ण

/*
 * Probe/हटाओ
 */

अटल पूर्णांक sbefअगरo_probe(काष्ठा device *dev)
अणु
	काष्ठा fsi_device *fsi_dev = to_fsi_dev(dev);
	काष्ठा sbefअगरo *sbefअगरo;
	काष्ठा device_node *np;
	काष्ठा platक्रमm_device *child;
	अक्षर child_name[32];
	पूर्णांक rc, didx, child_idx = 0;

	dev_dbg(dev, "Found sbefifo device\n");

	sbefअगरo = kzalloc(माप(*sbefअगरo), GFP_KERNEL);
	अगर (!sbefअगरo)
		वापस -ENOMEM;

	/* Grab a reference to the device (parent of our cdev), we'll drop it later */
	अगर (!get_device(dev)) अणु
		kमुक्त(sbefअगरo);
		वापस -ENODEV;
	पूर्ण

	sbefअगरo->magic = SBEFIFO_MAGIC;
	sbefअगरo->fsi_dev = fsi_dev;
	dev_set_drvdata(dev, sbefअगरo);
	mutex_init(&sbefअगरo->lock);

	/*
	 * Try cleaning up the FIFO. If this fails, we still रेजिस्टर the
	 * driver and will try cleaning things up again on the next access.
	 */
	rc = sbefअगरo_cleanup_hw(sbefअगरo);
	अगर (rc && rc != -ESHUTDOWN)
		dev_err(dev, "Initial HW cleanup failed, will retry later\n");

	/* Create अक्षरdev क्रम userspace access */
	sbefअगरo->dev.type = &fsi_cdev_type;
	sbefअगरo->dev.parent = dev;
	sbefअगरo->dev.release = sbefअगरo_मुक्त;
	device_initialize(&sbefअगरo->dev);

	/* Allocate a minor in the FSI space */
	rc = fsi_get_new_minor(fsi_dev, fsi_dev_sbefअगरo, &sbefअगरo->dev.devt, &didx);
	अगर (rc)
		जाओ err;

	dev_set_name(&sbefअगरo->dev, "sbefifo%d", didx);
	cdev_init(&sbefअगरo->cdev, &sbefअगरo_fops);
	rc = cdev_device_add(&sbefअगरo->cdev, &sbefअगरo->dev);
	अगर (rc) अणु
		dev_err(dev, "Error %d creating char device %s\n",
			rc, dev_name(&sbefअगरo->dev));
		जाओ err_मुक्त_minor;
	पूर्ण

	/* Create platक्रमm devs क्रम dts child nodes (occ, etc) */
	क्रम_each_available_child_of_node(dev->of_node, np) अणु
		snम_लिखो(child_name, माप(child_name), "%s-dev%d",
			 dev_name(&sbefअगरo->dev), child_idx++);
		child = of_platक्रमm_device_create(np, child_name, dev);
		अगर (!child)
			dev_warn(dev, "failed to create child %s dev\n",
				 child_name);
	पूर्ण

	वापस 0;
 err_मुक्त_minor:
	fsi_मुक्त_minor(sbefअगरo->dev.devt);
 err:
	put_device(&sbefअगरo->dev);
	वापस rc;
पूर्ण

अटल पूर्णांक sbefअगरo_unरेजिस्टर_child(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *child = to_platक्रमm_device(dev);

	of_device_unरेजिस्टर(child);
	अगर (dev->of_node)
		of_node_clear_flag(dev->of_node, OF_POPULATED);

	वापस 0;
पूर्ण

अटल पूर्णांक sbefअगरo_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा sbefअगरo *sbefअगरo = dev_get_drvdata(dev);

	dev_dbg(dev, "Removing sbefifo device...\n");

	mutex_lock(&sbefअगरo->lock);
	sbefअगरo->dead = true;
	mutex_unlock(&sbefअगरo->lock);

	cdev_device_del(&sbefअगरo->cdev, &sbefअगरo->dev);
	fsi_मुक्त_minor(sbefअगरo->dev.devt);
	device_क्रम_each_child(dev, शून्य, sbefअगरo_unरेजिस्टर_child);
	put_device(&sbefअगरo->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsi_device_id sbefअगरo_ids[] = अणु
	अणु
		.engine_type = FSI_ENGID_SBE,
		.version = FSI_VERSION_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा fsi_driver sbefअगरo_drv = अणु
	.id_table = sbefअगरo_ids,
	.drv = अणु
		.name = DEVICE_NAME,
		.bus = &fsi_bus_type,
		.probe = sbefअगरo_probe,
		.हटाओ = sbefअगरo_हटाओ,
	पूर्ण
पूर्ण;

अटल पूर्णांक sbefअगरo_init(व्योम)
अणु
	वापस fsi_driver_रेजिस्टर(&sbefअगरo_drv);
पूर्ण

अटल व्योम sbefअगरo_निकास(व्योम)
अणु
	fsi_driver_unरेजिस्टर(&sbefअगरo_drv);
पूर्ण

module_init(sbefअगरo_init);
module_निकास(sbefअगरo_निकास);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Brad Bishop <bradleyb@fuzziesquirrel.com>");
MODULE_AUTHOR("Eddie James <eajames@linux.vnet.ibm.com>");
MODULE_AUTHOR("Andrew Jeffery <andrew@aj.id.au>");
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("Linux device interface to the POWER Self Boot Engine");
