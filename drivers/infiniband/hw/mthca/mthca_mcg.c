<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>

#समावेश "mthca_dev.h"
#समावेश "mthca_cmd.h"

काष्ठा mthca_mgm अणु
	__be32 next_gid_index;
	u32    reserved[3];
	u8     gid[16];
	__be32 qp[MTHCA_QP_PER_MGM];
पूर्ण;

अटल स्थिर u8 zero_gid[16];	/* स्वतःmatically initialized to 0 */

/*
 * Caller must hold MCG table semaphore.  gid and mgm parameters must
 * be properly aligned क्रम command पूर्णांकerface.
 *
 *  Returns 0 unless a firmware command error occurs.
 *
 * If GID is found in MGM or MGM is empty, *index = *hash, *prev = -1
 * and *mgm holds MGM entry.
 *
 * अगर GID is found in AMGM, *index = index in AMGM, *prev = index of
 * previous entry in hash chain and *mgm holds AMGM entry.
 *
 * If no AMGM exists क्रम given gid, *index = -1, *prev = index of last
 * entry in hash chain and *mgm holds end of hash chain.
 */
अटल पूर्णांक find_mgm(काष्ठा mthca_dev *dev,
		    u8 *gid, काष्ठा mthca_mailbox *mgm_mailbox,
		    u16 *hash, पूर्णांक *prev, पूर्णांक *index)
अणु
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_mgm *mgm = mgm_mailbox->buf;
	u8 *mgid;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस -ENOMEM;
	mgid = mailbox->buf;

	स_नकल(mgid, gid, 16);

	err = mthca_MGID_HASH(dev, mailbox, hash);
	अगर (err) अणु
		mthca_err(dev, "MGID_HASH failed (%d)\n", err);
		जाओ out;
	पूर्ण

	अगर (0)
		mthca_dbg(dev, "Hash for %pI6 is %04x\n", gid, *hash);

	*index = *hash;
	*prev  = -1;

	करो अणु
		err = mthca_READ_MGM(dev, *index, mgm_mailbox);
		अगर (err) अणु
			mthca_err(dev, "READ_MGM failed (%d)\n", err);
			जाओ out;
		पूर्ण

		अगर (!स_भेद(mgm->gid, zero_gid, 16)) अणु
			अगर (*index != *hash) अणु
				mthca_err(dev, "Found zero MGID in AMGM.\n");
				err = -EINVAL;
			पूर्ण
			जाओ out;
		पूर्ण

		अगर (!स_भेद(mgm->gid, gid, 16))
			जाओ out;

		*prev = *index;
		*index = be32_to_cpu(mgm->next_gid_index) >> 6;
	पूर्ण जबतक (*index);

	*index = -1;

 out:
	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_multicast_attach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_mgm *mgm;
	u16 hash;
	पूर्णांक index, prev;
	पूर्णांक link = 0;
	पूर्णांक i;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	mgm = mailbox->buf;

	mutex_lock(&dev->mcg_table.mutex);

	err = find_mgm(dev, gid->raw, mailbox, &hash, &prev, &index);
	अगर (err)
		जाओ out;

	अगर (index != -1) अणु
		अगर (!स_भेद(mgm->gid, zero_gid, 16))
			स_नकल(mgm->gid, gid->raw, 16);
	पूर्ण अन्यथा अणु
		link = 1;

		index = mthca_alloc(&dev->mcg_table.alloc);
		अगर (index == -1) अणु
			mthca_err(dev, "No AMGM entries left\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		err = mthca_READ_MGM(dev, index, mailbox);
		अगर (err) अणु
			mthca_err(dev, "READ_MGM failed (%d)\n", err);
			जाओ out;
		पूर्ण
		स_रखो(mgm, 0, माप *mgm);
		स_नकल(mgm->gid, gid->raw, 16);
	पूर्ण

	क्रम (i = 0; i < MTHCA_QP_PER_MGM; ++i)
		अगर (mgm->qp[i] == cpu_to_be32(ibqp->qp_num | (1 << 31))) अणु
			mthca_dbg(dev, "QP %06x already a member of MGM\n",
				  ibqp->qp_num);
			err = 0;
			जाओ out;
		पूर्ण अन्यथा अगर (!(mgm->qp[i] & cpu_to_be32(1 << 31))) अणु
			mgm->qp[i] = cpu_to_be32(ibqp->qp_num | (1 << 31));
			अवरोध;
		पूर्ण

	अगर (i == MTHCA_QP_PER_MGM) अणु
		mthca_err(dev, "MGM at index %x is full.\n", index);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = mthca_WRITE_MGM(dev, index, mailbox);
	अगर (err) अणु
		mthca_err(dev, "WRITE_MGM failed %d\n", err);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!link)
		जाओ out;

	err = mthca_READ_MGM(dev, prev, mailbox);
	अगर (err) अणु
		mthca_err(dev, "READ_MGM failed %d\n", err);
		जाओ out;
	पूर्ण

	mgm->next_gid_index = cpu_to_be32(index << 6);

	err = mthca_WRITE_MGM(dev, prev, mailbox);
	अगर (err)
		mthca_err(dev, "WRITE_MGM returned %d\n", err);

 out:
	अगर (err && link && index != -1) अणु
		BUG_ON(index < dev->limits.num_mgms);
		mthca_मुक्त(&dev->mcg_table.alloc, index);
	पूर्ण
	mutex_unlock(&dev->mcg_table.mutex);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_multicast_detach(काष्ठा ib_qp *ibqp, जोड़ ib_gid *gid, u16 lid)
अणु
	काष्ठा mthca_dev *dev = to_mdev(ibqp->device);
	काष्ठा mthca_mailbox *mailbox;
	काष्ठा mthca_mgm *mgm;
	u16 hash;
	पूर्णांक prev, index;
	पूर्णांक i, loc;
	पूर्णांक err;

	mailbox = mthca_alloc_mailbox(dev, GFP_KERNEL);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	mgm = mailbox->buf;

	mutex_lock(&dev->mcg_table.mutex);

	err = find_mgm(dev, gid->raw, mailbox, &hash, &prev, &index);
	अगर (err)
		जाओ out;

	अगर (index == -1) अणु
		mthca_err(dev, "MGID %pI6 not found\n", gid->raw);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (loc = -1, i = 0; i < MTHCA_QP_PER_MGM; ++i) अणु
		अगर (mgm->qp[i] == cpu_to_be32(ibqp->qp_num | (1 << 31)))
			loc = i;
		अगर (!(mgm->qp[i] & cpu_to_be32(1 << 31)))
			अवरोध;
	पूर्ण

	अगर (loc == -1) अणु
		mthca_err(dev, "QP %06x not found in MGM\n", ibqp->qp_num);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	mgm->qp[loc]   = mgm->qp[i - 1];
	mgm->qp[i - 1] = 0;

	err = mthca_WRITE_MGM(dev, index, mailbox);
	अगर (err) अणु
		mthca_err(dev, "WRITE_MGM returned %d\n", err);
		जाओ out;
	पूर्ण

	अगर (i != 1)
		जाओ out;

	अगर (prev == -1) अणु
		/* Remove entry from MGM */
		पूर्णांक amgm_index_to_मुक्त = be32_to_cpu(mgm->next_gid_index) >> 6;
		अगर (amgm_index_to_मुक्त) अणु
			err = mthca_READ_MGM(dev, amgm_index_to_मुक्त,
					     mailbox);
			अगर (err) अणु
				mthca_err(dev, "READ_MGM returned %d\n", err);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा
			स_रखो(mgm->gid, 0, 16);

		err = mthca_WRITE_MGM(dev, index, mailbox);
		अगर (err) अणु
			mthca_err(dev, "WRITE_MGM returned %d\n", err);
			जाओ out;
		पूर्ण
		अगर (amgm_index_to_मुक्त) अणु
			BUG_ON(amgm_index_to_मुक्त < dev->limits.num_mgms);
			mthca_मुक्त(&dev->mcg_table.alloc, amgm_index_to_मुक्त);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Remove entry from AMGM */
		पूर्णांक curr_next_index = be32_to_cpu(mgm->next_gid_index) >> 6;
		err = mthca_READ_MGM(dev, prev, mailbox);
		अगर (err) अणु
			mthca_err(dev, "READ_MGM returned %d\n", err);
			जाओ out;
		पूर्ण

		mgm->next_gid_index = cpu_to_be32(curr_next_index << 6);

		err = mthca_WRITE_MGM(dev, prev, mailbox);
		अगर (err) अणु
			mthca_err(dev, "WRITE_MGM returned %d\n", err);
			जाओ out;
		पूर्ण
		BUG_ON(index < dev->limits.num_mgms);
		mthca_मुक्त(&dev->mcg_table.alloc, index);
	पूर्ण

 out:
	mutex_unlock(&dev->mcg_table.mutex);

	mthca_मुक्त_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mthca_init_mcg_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;
	पूर्णांक table_size = dev->limits.num_mgms + dev->limits.num_amgms;

	err = mthca_alloc_init(&dev->mcg_table.alloc,
			       table_size,
			       table_size - 1,
			       dev->limits.num_mgms);
	अगर (err)
		वापस err;

	mutex_init(&dev->mcg_table.mutex);

	वापस 0;
पूर्ण

व्योम mthca_cleanup_mcg_table(काष्ठा mthca_dev *dev)
अणु
	mthca_alloc_cleanup(&dev->mcg_table.alloc);
पूर्ण
