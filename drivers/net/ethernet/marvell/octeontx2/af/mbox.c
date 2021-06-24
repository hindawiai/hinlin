<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>

#समावेश "rvu_reg.h"
#समावेश "mbox.h"
#समावेश "rvu_trace.h"

अटल स्थिर u16 msgs_offset = ALIGN(माप(काष्ठा mbox_hdr), MBOX_MSG_ALIGN);

व्योम __otx2_mbox_reset(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	काष्ठा mbox_hdr *tx_hdr, *rx_hdr;
	व्योम *hw_mbase = mdev->hwbase;

	tx_hdr = hw_mbase + mbox->tx_start;
	rx_hdr = hw_mbase + mbox->rx_start;

	mdev->msg_size = 0;
	mdev->rsp_size = 0;
	tx_hdr->num_msgs = 0;
	tx_hdr->msg_size = 0;
	rx_hdr->num_msgs = 0;
	rx_hdr->msg_size = 0;
पूर्ण
EXPORT_SYMBOL(__otx2_mbox_reset);

व्योम otx2_mbox_reset(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];

	spin_lock(&mdev->mbox_lock);
	__otx2_mbox_reset(mbox, devid);
	spin_unlock(&mdev->mbox_lock);
पूर्ण
EXPORT_SYMBOL(otx2_mbox_reset);

व्योम otx2_mbox_destroy(काष्ठा otx2_mbox *mbox)
अणु
	mbox->reg_base = शून्य;
	mbox->hwbase = शून्य;

	kमुक्त(mbox->dev);
	mbox->dev = शून्य;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_destroy);

अटल पूर्णांक otx2_mbox_setup(काष्ठा otx2_mbox *mbox, काष्ठा pci_dev *pdev,
			   व्योम *reg_base, पूर्णांक direction, पूर्णांक ndevs)
अणु
	चयन (direction) अणु
	हाल MBOX_सूची_AFPF:
	हाल MBOX_सूची_PFVF:
		mbox->tx_start = MBOX_DOWN_TX_START;
		mbox->rx_start = MBOX_DOWN_RX_START;
		mbox->tx_size  = MBOX_DOWN_TX_SIZE;
		mbox->rx_size  = MBOX_DOWN_RX_SIZE;
		अवरोध;
	हाल MBOX_सूची_PFAF:
	हाल MBOX_सूची_VFPF:
		mbox->tx_start = MBOX_DOWN_RX_START;
		mbox->rx_start = MBOX_DOWN_TX_START;
		mbox->tx_size  = MBOX_DOWN_RX_SIZE;
		mbox->rx_size  = MBOX_DOWN_TX_SIZE;
		अवरोध;
	हाल MBOX_सूची_AFPF_UP:
	हाल MBOX_सूची_PFVF_UP:
		mbox->tx_start = MBOX_UP_TX_START;
		mbox->rx_start = MBOX_UP_RX_START;
		mbox->tx_size  = MBOX_UP_TX_SIZE;
		mbox->rx_size  = MBOX_UP_RX_SIZE;
		अवरोध;
	हाल MBOX_सूची_PFAF_UP:
	हाल MBOX_सूची_VFPF_UP:
		mbox->tx_start = MBOX_UP_RX_START;
		mbox->rx_start = MBOX_UP_TX_START;
		mbox->tx_size  = MBOX_UP_RX_SIZE;
		mbox->rx_size  = MBOX_UP_TX_SIZE;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	चयन (direction) अणु
	हाल MBOX_सूची_AFPF:
	हाल MBOX_सूची_AFPF_UP:
		mbox->trigger = RVU_AF_AFPF_MBOX0;
		mbox->tr_shअगरt = 4;
		अवरोध;
	हाल MBOX_सूची_PFAF:
	हाल MBOX_सूची_PFAF_UP:
		mbox->trigger = RVU_PF_PFAF_MBOX1;
		mbox->tr_shअगरt = 0;
		अवरोध;
	हाल MBOX_सूची_PFVF:
	हाल MBOX_सूची_PFVF_UP:
		mbox->trigger = RVU_PF_VFX_PFVF_MBOX0;
		mbox->tr_shअगरt = 12;
		अवरोध;
	हाल MBOX_सूची_VFPF:
	हाल MBOX_सूची_VFPF_UP:
		mbox->trigger = RVU_VF_VFPF_MBOX1;
		mbox->tr_shअगरt = 0;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	mbox->reg_base = reg_base;
	mbox->pdev = pdev;

	mbox->dev = kसुस्मृति(ndevs, माप(काष्ठा otx2_mbox_dev), GFP_KERNEL);
	अगर (!mbox->dev) अणु
		otx2_mbox_destroy(mbox);
		वापस -ENOMEM;
	पूर्ण
	mbox->ndevs = ndevs;

	वापस 0;
पूर्ण

पूर्णांक otx2_mbox_init(काष्ठा otx2_mbox *mbox, व्योम *hwbase, काष्ठा pci_dev *pdev,
		   व्योम *reg_base, पूर्णांक direction, पूर्णांक ndevs)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	पूर्णांक devid, err;

	err = otx2_mbox_setup(mbox, pdev, reg_base, direction, ndevs);
	अगर (err)
		वापस err;

	mbox->hwbase = hwbase;

	क्रम (devid = 0; devid < ndevs; devid++) अणु
		mdev = &mbox->dev[devid];
		mdev->mbase = mbox->hwbase + (devid * MBOX_SIZE);
		mdev->hwbase = mdev->mbase;
		spin_lock_init(&mdev->mbox_lock);
		/* Init header to reset value */
		otx2_mbox_reset(mbox, devid);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_init);

/* Initialize mailbox with the set of mailbox region addresses
 * in the array hwbase.
 */
पूर्णांक otx2_mbox_regions_init(काष्ठा otx2_mbox *mbox, व्योम **hwbase,
			   काष्ठा pci_dev *pdev, व्योम *reg_base,
			   पूर्णांक direction, पूर्णांक ndevs)
अणु
	काष्ठा otx2_mbox_dev *mdev;
	पूर्णांक devid, err;

	err = otx2_mbox_setup(mbox, pdev, reg_base, direction, ndevs);
	अगर (err)
		वापस err;

	mbox->hwbase = hwbase[0];

	क्रम (devid = 0; devid < ndevs; devid++) अणु
		mdev = &mbox->dev[devid];
		mdev->mbase = hwbase[devid];
		mdev->hwbase = hwbase[devid];
		spin_lock_init(&mdev->mbox_lock);
		/* Init header to reset value */
		otx2_mbox_reset(mbox, devid);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_regions_init);

पूर्णांक otx2_mbox_रुको_क्रम_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(MBOX_RSP_TIMEOUT);
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	काष्ठा device *sender = &mbox->pdev->dev;

	जबतक (!समय_after(jअगरfies, समयout)) अणु
		अगर (mdev->num_msgs == mdev->msgs_acked)
			वापस 0;
		usleep_range(800, 1000);
	पूर्ण
	dev_dbg(sender, "timed out while waiting for rsp\n");
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_रुको_क्रम_rsp);

पूर्णांक otx2_mbox_busy_poll_क्रम_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	अचिन्हित दीर्घ समयout = jअगरfies + 1 * HZ;

	जबतक (!समय_after(jअगरfies, समयout)) अणु
		अगर (mdev->num_msgs == mdev->msgs_acked)
			वापस 0;
		cpu_relax();
	पूर्ण
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_busy_poll_क्रम_rsp);

व्योम otx2_mbox_msg_send(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	काष्ठा mbox_hdr *tx_hdr, *rx_hdr;
	व्योम *hw_mbase = mdev->hwbase;

	tx_hdr = hw_mbase + mbox->tx_start;
	rx_hdr = hw_mbase + mbox->rx_start;

	/* If bounce buffer is implemented copy mbox messages from
	 * bounce buffer to hw mbox memory.
	 */
	अगर (mdev->mbase != hw_mbase)
		स_नकल(hw_mbase + mbox->tx_start + msgs_offset,
		       mdev->mbase + mbox->tx_start + msgs_offset,
		       mdev->msg_size);

	spin_lock(&mdev->mbox_lock);

	tx_hdr->msg_size = mdev->msg_size;

	/* Reset header क्रम next messages */
	mdev->msg_size = 0;
	mdev->rsp_size = 0;
	mdev->msgs_acked = 0;

	/* Sync mbox data पूर्णांकo memory */
	smp_wmb();

	/* num_msgs != 0 संकेतs to the peer that the buffer has a number of
	 * messages.  So this should be written after writing all the messages
	 * to the shared memory.
	 */
	tx_hdr->num_msgs = mdev->num_msgs;
	rx_hdr->num_msgs = 0;

	trace_otx2_msg_send(mbox->pdev, tx_hdr->num_msgs, tx_hdr->msg_size);

	spin_unlock(&mdev->mbox_lock);

	/* The पूर्णांकerrupt should be fired after num_msgs is written
	 * to the shared memory
	 */
	ग_लिखोq(1, (व्योम __iomem *)mbox->reg_base +
	       (mbox->trigger | (devid << mbox->tr_shअगरt)));
पूर्ण
EXPORT_SYMBOL(otx2_mbox_msg_send);

काष्ठा mbox_msghdr *otx2_mbox_alloc_msg_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
					    पूर्णांक size, पूर्णांक size_rsp)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	काष्ठा mbox_msghdr *msghdr = शून्य;

	spin_lock(&mdev->mbox_lock);
	size = ALIGN(size, MBOX_MSG_ALIGN);
	size_rsp = ALIGN(size_rsp, MBOX_MSG_ALIGN);
	/* Check अगर there is space in mailbox */
	अगर ((mdev->msg_size + size) > mbox->tx_size - msgs_offset)
		जाओ निकास;
	अगर ((mdev->rsp_size + size_rsp) > mbox->rx_size - msgs_offset)
		जाओ निकास;

	अगर (mdev->msg_size == 0)
		mdev->num_msgs = 0;
	mdev->num_msgs++;

	msghdr = mdev->mbase + mbox->tx_start + msgs_offset + mdev->msg_size;

	/* Clear the whole msg region */
	स_रखो(msghdr, 0, size);
	/* Init message header with reset values */
	msghdr->ver = OTX2_MBOX_VERSION;
	mdev->msg_size += size;
	mdev->rsp_size += size_rsp;
	msghdr->next_msgoff = mdev->msg_size + msgs_offset;
निकास:
	spin_unlock(&mdev->mbox_lock);

	वापस msghdr;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_alloc_msg_rsp);

काष्ठा mbox_msghdr *otx2_mbox_get_rsp(काष्ठा otx2_mbox *mbox, पूर्णांक devid,
				      काष्ठा mbox_msghdr *msg)
अणु
	अचिन्हित दीर्घ imsg = mbox->tx_start + msgs_offset;
	अचिन्हित दीर्घ irsp = mbox->rx_start + msgs_offset;
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	u16 msgs;

	spin_lock(&mdev->mbox_lock);

	अगर (mdev->num_msgs != mdev->msgs_acked)
		जाओ error;

	क्रम (msgs = 0; msgs < mdev->msgs_acked; msgs++) अणु
		काष्ठा mbox_msghdr *pmsg = mdev->mbase + imsg;
		काष्ठा mbox_msghdr *prsp = mdev->mbase + irsp;

		अगर (msg == pmsg) अणु
			अगर (pmsg->id != prsp->id)
				जाओ error;
			spin_unlock(&mdev->mbox_lock);
			वापस prsp;
		पूर्ण

		imsg = mbox->tx_start + pmsg->next_msgoff;
		irsp = mbox->rx_start + prsp->next_msgoff;
	पूर्ण

error:
	spin_unlock(&mdev->mbox_lock);
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL(otx2_mbox_get_rsp);

पूर्णांक otx2_mbox_check_rsp_msgs(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	अचिन्हित दीर्घ ireq = mbox->tx_start + msgs_offset;
	अचिन्हित दीर्घ irsp = mbox->rx_start + msgs_offset;
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	पूर्णांक rc = -ENODEV;
	u16 msgs;

	spin_lock(&mdev->mbox_lock);

	अगर (mdev->num_msgs != mdev->msgs_acked)
		जाओ निकास;

	क्रम (msgs = 0; msgs < mdev->msgs_acked; msgs++) अणु
		काष्ठा mbox_msghdr *preq = mdev->mbase + ireq;
		काष्ठा mbox_msghdr *prsp = mdev->mbase + irsp;

		अगर (preq->id != prsp->id) अणु
			trace_otx2_msg_check(mbox->pdev, preq->id,
					     prsp->id, prsp->rc);
			जाओ निकास;
		पूर्ण
		अगर (prsp->rc) अणु
			rc = prsp->rc;
			trace_otx2_msg_check(mbox->pdev, preq->id,
					     prsp->id, prsp->rc);
			जाओ निकास;
		पूर्ण

		ireq = mbox->tx_start + preq->next_msgoff;
		irsp = mbox->rx_start + prsp->next_msgoff;
	पूर्ण
	rc = 0;
निकास:
	spin_unlock(&mdev->mbox_lock);
	वापस rc;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_check_rsp_msgs);

पूर्णांक
otx2_reply_invalid_msg(काष्ठा otx2_mbox *mbox, पूर्णांक devid, u16 pcअगरunc, u16 id)
अणु
	काष्ठा msg_rsp *rsp;

	rsp = (काष्ठा msg_rsp *)
	       otx2_mbox_alloc_msg(mbox, devid, माप(*rsp));
	अगर (!rsp)
		वापस -ENOMEM;
	rsp->hdr.id = id;
	rsp->hdr.sig = OTX2_MBOX_RSP_SIG;
	rsp->hdr.rc = MBOX_MSG_INVALID;
	rsp->hdr.pcअगरunc = pcअगरunc;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_reply_invalid_msg);

bool otx2_mbox_nonempty(काष्ठा otx2_mbox *mbox, पूर्णांक devid)
अणु
	काष्ठा otx2_mbox_dev *mdev = &mbox->dev[devid];
	bool ret;

	spin_lock(&mdev->mbox_lock);
	ret = mdev->num_msgs != 0;
	spin_unlock(&mdev->mbox_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(otx2_mbox_nonempty);

स्थिर अक्षर *otx2_mbox_id2name(u16 id)
अणु
	चयन (id) अणु
#घोषणा M(_name, _id, _1, _2, _3) हाल _id: वापस # _name;
	MBOX_MESSAGES
#अघोषित M
	शेष:
		वापस "INVALID ID";
	पूर्ण
पूर्ण
EXPORT_SYMBOL(otx2_mbox_id2name);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_LICENSE("GPL v2");
