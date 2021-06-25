<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2007, 2008 Mellanox Technologies. All rights reserved.
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
#समावेश <linux/etherdevice.h>

#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/export.h>

#समावेश "mlx4.h"

पूर्णांक mlx4_get_mgm_entry_size(काष्ठा mlx4_dev *dev)
अणु
	वापस 1 << dev->oper_log_mgm_entry_size;
पूर्ण

पूर्णांक mlx4_get_qp_per_mgm(काष्ठा mlx4_dev *dev)
अणु
	वापस 4 * (mlx4_get_mgm_entry_size(dev) / 16 - 2);
पूर्ण

अटल पूर्णांक mlx4_QP_FLOW_STEERING_ATTACH(काष्ठा mlx4_dev *dev,
					काष्ठा mlx4_cmd_mailbox *mailbox,
					u32 size,
					u64 *reg_id)
अणु
	u64 imm;
	पूर्णांक err = 0;

	err = mlx4_cmd_imm(dev, mailbox->dma, &imm, size, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	अगर (err)
		वापस err;
	*reg_id = imm;

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_QP_FLOW_STEERING_DETACH(काष्ठा mlx4_dev *dev, u64 regid)
अणु
	पूर्णांक err = 0;

	err = mlx4_cmd(dev, regid, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);

	वापस err;
पूर्ण

अटल पूर्णांक mlx4_READ_ENTRY(काष्ठा mlx4_dev *dev, पूर्णांक index,
			   काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
	वापस mlx4_cmd_box(dev, 0, mailbox->dma, index, 0, MLX4_CMD_READ_MCG,
			    MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_WRITE_ENTRY(काष्ठा mlx4_dev *dev, पूर्णांक index,
			    काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
	वापस mlx4_cmd(dev, mailbox->dma, index, 0, MLX4_CMD_WRITE_MCG,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_WRITE_PROMISC(काष्ठा mlx4_dev *dev, u8 port, u8 steer,
			      काष्ठा mlx4_cmd_mailbox *mailbox)
अणु
	u32 in_mod;

	in_mod = (u32) port << 16 | steer << 1;
	वापस mlx4_cmd(dev, mailbox->dma, in_mod, 0x1,
			MLX4_CMD_WRITE_MCG, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_NATIVE);
पूर्ण

अटल पूर्णांक mlx4_GID_HASH(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *mailbox,
			 u16 *hash, u8 op_mod)
अणु
	u64 imm;
	पूर्णांक err;

	err = mlx4_cmd_imm(dev, mailbox->dma, &imm, 0, op_mod,
			   MLX4_CMD_MGID_HASH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);

	अगर (!err)
		*hash = imm;

	वापस err;
पूर्ण

अटल काष्ठा mlx4_promisc_qp *get_promisc_qp(काष्ठा mlx4_dev *dev, u8 port,
					      क्रमागत mlx4_steer_type steer,
					      u32 qpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_promisc_qp *pqp;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस शून्य;

	s_steer = &mlx4_priv(dev)->steer[port - 1];

	list_क्रम_each_entry(pqp, &s_steer->promisc_qps[steer], list) अणु
		अगर (pqp->qpn == qpn)
			वापस pqp;
	पूर्ण
	/* not found */
	वापस शून्य;
पूर्ण

/*
 * Add new entry to steering data काष्ठाure.
 * All promisc QPs should be added as well
 */
अटल पूर्णांक new_steering_entry(काष्ठा mlx4_dev *dev, u8 port,
			      क्रमागत mlx4_steer_type steer,
			      अचिन्हित पूर्णांक index, u32 qpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	u32 members_count;
	काष्ठा mlx4_steer_index *new_entry;
	काष्ठा mlx4_promisc_qp *pqp;
	काष्ठा mlx4_promisc_qp *dqp = शून्य;
	u32 prot;
	पूर्णांक err;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस -EINVAL;

	s_steer = &mlx4_priv(dev)->steer[port - 1];
	new_entry = kzalloc(माप(*new_entry), GFP_KERNEL);
	अगर (!new_entry)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&new_entry->duplicates);
	new_entry->index = index;
	list_add_tail(&new_entry->list, &s_steer->steer_entries[steer]);

	/* If the given qpn is also a promisc qp,
	 * it should be inserted to duplicates list
	 */
	pqp = get_promisc_qp(dev, port, steer, qpn);
	अगर (pqp) अणु
		dqp = kदो_स्मृति(माप(*dqp), GFP_KERNEL);
		अगर (!dqp) अणु
			err = -ENOMEM;
			जाओ out_alloc;
		पूर्ण
		dqp->qpn = qpn;
		list_add_tail(&dqp->list, &new_entry->duplicates);
	पूर्ण

	/* अगर no promisc qps क्रम this vep, we are करोne */
	अगर (list_empty(&s_steer->promisc_qps[steer]))
		वापस 0;

	/* now need to add all the promisc qps to the new
	 * steering entry, as they should also receive the packets
	 * destined to this address */
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = -ENOMEM;
		जाओ out_alloc;
	पूर्ण
	mgm = mailbox->buf;

	err = mlx4_READ_ENTRY(dev, index, mailbox);
	अगर (err)
		जाओ out_mailbox;

	members_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	prot = be32_to_cpu(mgm->members_count) >> 30;
	list_क्रम_each_entry(pqp, &s_steer->promisc_qps[steer], list) अणु
		/* करोn't add alपढ़ोy existing qpn */
		अगर (pqp->qpn == qpn)
			जारी;
		अगर (members_count == dev->caps.num_qp_per_mgm) अणु
			/* out of space */
			err = -ENOMEM;
			जाओ out_mailbox;
		पूर्ण

		/* add the qpn */
		mgm->qp[members_count++] = cpu_to_be32(pqp->qpn & MGM_QPN_MASK);
	पूर्ण
	/* update the qps count and update the entry with all the promisc qps*/
	mgm->members_count = cpu_to_be32(members_count | (prot << 30));
	err = mlx4_WRITE_ENTRY(dev, index, mailbox);

out_mailbox:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (!err)
		वापस 0;
out_alloc:
	अगर (dqp) अणु
		list_del(&dqp->list);
		kमुक्त(dqp);
	पूर्ण
	list_del(&new_entry->list);
	kमुक्त(new_entry);
	वापस err;
पूर्ण

/* update the data काष्ठाures with existing steering entry */
अटल पूर्णांक existing_steering_entry(काष्ठा mlx4_dev *dev, u8 port,
				   क्रमागत mlx4_steer_type steer,
				   अचिन्हित पूर्णांक index, u32 qpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_steer_index *पंचांगp_entry, *entry = शून्य;
	काष्ठा mlx4_promisc_qp *pqp;
	काष्ठा mlx4_promisc_qp *dqp;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस -EINVAL;

	s_steer = &mlx4_priv(dev)->steer[port - 1];

	pqp = get_promisc_qp(dev, port, steer, qpn);
	अगर (!pqp)
		वापस 0; /* nothing to करो */

	list_क्रम_each_entry(पंचांगp_entry, &s_steer->steer_entries[steer], list) अणु
		अगर (पंचांगp_entry->index == index) अणु
			entry = पंचांगp_entry;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (unlikely(!entry)) अणु
		mlx4_warn(dev, "Steering entry at index %x is not registered\n", index);
		वापस -EINVAL;
	पूर्ण

	/* the given qpn is listed as a promisc qpn
	 * we need to add it as a duplicate to this entry
	 * क्रम future references */
	list_क्रम_each_entry(dqp, &entry->duplicates, list) अणु
		अगर (qpn == dqp->qpn)
			वापस 0; /* qp is alपढ़ोy duplicated */
	पूर्ण

	/* add the qp as a duplicate on this index */
	dqp = kदो_स्मृति(माप(*dqp), GFP_KERNEL);
	अगर (!dqp)
		वापस -ENOMEM;
	dqp->qpn = qpn;
	list_add_tail(&dqp->list, &entry->duplicates);

	वापस 0;
पूर्ण

/* Check whether a qpn is a duplicate on steering entry
 * If so, it should not be हटाओd from mgm */
अटल bool check_duplicate_entry(काष्ठा mlx4_dev *dev, u8 port,
				  क्रमागत mlx4_steer_type steer,
				  अचिन्हित पूर्णांक index, u32 qpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_steer_index *पंचांगp_entry, *entry = शून्य;
	काष्ठा mlx4_promisc_qp *dqp, *पंचांगp_dqp;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस शून्य;

	s_steer = &mlx4_priv(dev)->steer[port - 1];

	/* अगर qp is not promisc, it cannot be duplicated */
	अगर (!get_promisc_qp(dev, port, steer, qpn))
		वापस false;

	/* The qp is promisc qp so it is a duplicate on this index
	 * Find the index entry, and हटाओ the duplicate */
	list_क्रम_each_entry(पंचांगp_entry, &s_steer->steer_entries[steer], list) अणु
		अगर (पंचांगp_entry->index == index) अणु
			entry = पंचांगp_entry;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (unlikely(!entry)) अणु
		mlx4_warn(dev, "Steering entry for index %x is not registered\n", index);
		वापस false;
	पूर्ण
	list_क्रम_each_entry_safe(dqp, पंचांगp_dqp, &entry->duplicates, list) अणु
		अगर (dqp->qpn == qpn) अणु
			list_del(&dqp->list);
			kमुक्त(dqp);
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

/* Returns true अगर all the QPs != tqpn contained in this entry
 * are Promisc QPs. Returns false otherwise.
 */
अटल bool promisc_steering_entry(काष्ठा mlx4_dev *dev, u8 port,
				   क्रमागत mlx4_steer_type steer,
				   अचिन्हित पूर्णांक index, u32 tqpn,
				   u32 *members_count)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	u32 m_count;
	bool ret = false;
	पूर्णांक i;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस false;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस false;
	mgm = mailbox->buf;

	अगर (mlx4_READ_ENTRY(dev, index, mailbox))
		जाओ out;
	m_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	अगर (members_count)
		*members_count = m_count;

	क्रम (i = 0;  i < m_count; i++) अणु
		u32 qpn = be32_to_cpu(mgm->qp[i]) & MGM_QPN_MASK;
		अगर (!get_promisc_qp(dev, port, steer, qpn) && qpn != tqpn) अणु
			/* the qp is not promisc, the entry can't be हटाओd */
			जाओ out;
		पूर्ण
	पूर्ण
	ret = true;
out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस ret;
पूर्ण

/* IF a steering entry contains only promisc QPs, it can be हटाओd. */
अटल bool can_हटाओ_steering_entry(काष्ठा mlx4_dev *dev, u8 port,
				      क्रमागत mlx4_steer_type steer,
				      अचिन्हित पूर्णांक index, u32 tqpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_steer_index *entry = शून्य, *पंचांगp_entry;
	u32 members_count;
	bool ret = false;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस शून्य;

	s_steer = &mlx4_priv(dev)->steer[port - 1];

	अगर (!promisc_steering_entry(dev, port, steer, index,
				    tqpn, &members_count))
		जाओ out;

	/* All the qps currently रेजिस्टरed क्रम this entry are promiscuous,
	  * Checking क्रम duplicates */
	ret = true;
	list_क्रम_each_entry_safe(entry, पंचांगp_entry, &s_steer->steer_entries[steer], list) अणु
		अगर (entry->index == index) अणु
			अगर (list_empty(&entry->duplicates) ||
			    members_count == 1) अणु
				काष्ठा mlx4_promisc_qp *pqp, *पंचांगp_pqp;
				/* If there is only 1 entry in duplicates then
				 * this is the QP we want to delete, going over
				 * the list and deleting the entry.
				 */
				list_del(&entry->list);
				list_क्रम_each_entry_safe(pqp, पंचांगp_pqp,
							 &entry->duplicates,
							 list) अणु
					list_del(&pqp->list);
					kमुक्त(pqp);
				पूर्ण
				kमुक्त(entry);
			पूर्ण अन्यथा अणु
				/* This entry contains duplicates so it shouldn't be हटाओd */
				ret = false;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक add_promisc_qp(काष्ठा mlx4_dev *dev, u8 port,
			  क्रमागत mlx4_steer_type steer, u32 qpn)
अणु
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	काष्ठा mlx4_steer_index *entry;
	काष्ठा mlx4_promisc_qp *pqp;
	काष्ठा mlx4_promisc_qp *dqp;
	u32 members_count;
	u32 prot;
	पूर्णांक i;
	bool found;
	पूर्णांक err;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस -EINVAL;

	s_steer = &mlx4_priv(dev)->steer[port - 1];

	mutex_lock(&priv->mcg_table.mutex);

	अगर (get_promisc_qp(dev, port, steer, qpn)) अणु
		err = 0;  /* Noting to करो, alपढ़ोy exists */
		जाओ out_mutex;
	पूर्ण

	pqp = kदो_स्मृति(माप(*pqp), GFP_KERNEL);
	अगर (!pqp) अणु
		err = -ENOMEM;
		जाओ out_mutex;
	पूर्ण
	pqp->qpn = qpn;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = -ENOMEM;
		जाओ out_alloc;
	पूर्ण
	mgm = mailbox->buf;

	अगर (!(mlx4_is_mfunc(dev) && steer == MLX4_UC_STEER)) अणु
		/* The promisc QP needs to be added क्रम each one of the steering
		 * entries. If it alपढ़ोy exists, needs to be added as
		 * a duplicate क्रम this entry.
		 */
		list_क्रम_each_entry(entry,
				    &s_steer->steer_entries[steer],
				    list) अणु
			err = mlx4_READ_ENTRY(dev, entry->index, mailbox);
			अगर (err)
				जाओ out_mailbox;

			members_count = be32_to_cpu(mgm->members_count) &
					0xffffff;
			prot = be32_to_cpu(mgm->members_count) >> 30;
			found = false;
			क्रम (i = 0; i < members_count; i++) अणु
				अगर ((be32_to_cpu(mgm->qp[i]) &
				     MGM_QPN_MASK) == qpn) अणु
					/* Entry alपढ़ोy exists.
					 * Add to duplicates.
					 */
					dqp = kदो_स्मृति(माप(*dqp), GFP_KERNEL);
					अगर (!dqp) अणु
						err = -ENOMEM;
						जाओ out_mailbox;
					पूर्ण
					dqp->qpn = qpn;
					list_add_tail(&dqp->list,
						      &entry->duplicates);
					found = true;
				पूर्ण
			पूर्ण
			अगर (!found) अणु
				/* Need to add the qpn to mgm */
				अगर (members_count ==
				    dev->caps.num_qp_per_mgm) अणु
					/* entry is full */
					err = -ENOMEM;
					जाओ out_mailbox;
				पूर्ण
				mgm->qp[members_count++] =
					cpu_to_be32(qpn & MGM_QPN_MASK);
				mgm->members_count =
					cpu_to_be32(members_count |
						    (prot << 30));
				err = mlx4_WRITE_ENTRY(dev, entry->index,
						       mailbox);
				अगर (err)
					जाओ out_mailbox;
			पूर्ण
		पूर्ण
	पूर्ण

	/* add the new qpn to list of promisc qps */
	list_add_tail(&pqp->list, &s_steer->promisc_qps[steer]);
	/* now need to add all the promisc qps to शेष entry */
	स_रखो(mgm, 0, माप(*mgm));
	members_count = 0;
	list_क्रम_each_entry(dqp, &s_steer->promisc_qps[steer], list) अणु
		अगर (members_count == dev->caps.num_qp_per_mgm) अणु
			/* entry is full */
			err = -ENOMEM;
			जाओ out_list;
		पूर्ण
		mgm->qp[members_count++] = cpu_to_be32(dqp->qpn & MGM_QPN_MASK);
	पूर्ण
	mgm->members_count = cpu_to_be32(members_count | MLX4_PROT_ETH << 30);

	err = mlx4_WRITE_PROMISC(dev, port, steer, mailbox);
	अगर (err)
		जाओ out_list;

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	mutex_unlock(&priv->mcg_table.mutex);
	वापस 0;

out_list:
	list_del(&pqp->list);
out_mailbox:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
out_alloc:
	kमुक्त(pqp);
out_mutex:
	mutex_unlock(&priv->mcg_table.mutex);
	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_promisc_qp(काष्ठा mlx4_dev *dev, u8 port,
			     क्रमागत mlx4_steer_type steer, u32 qpn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_steer *s_steer;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	काष्ठा mlx4_steer_index *entry, *पंचांगp_entry;
	काष्ठा mlx4_promisc_qp *pqp;
	काष्ठा mlx4_promisc_qp *dqp;
	u32 members_count;
	bool found;
	bool back_to_list = false;
	पूर्णांक i;
	पूर्णांक err;

	अगर (port < 1 || port > dev->caps.num_ports)
		वापस -EINVAL;

	s_steer = &mlx4_priv(dev)->steer[port - 1];
	mutex_lock(&priv->mcg_table.mutex);

	pqp = get_promisc_qp(dev, port, steer, qpn);
	अगर (unlikely(!pqp)) अणु
		mlx4_warn(dev, "QP %x is not promiscuous QP\n", qpn);
		/* nothing to करो */
		err = 0;
		जाओ out_mutex;
	पूर्ण

	/*हटाओ from list of promisc qps */
	list_del(&pqp->list);

	/* set the शेष entry not to include the हटाओd one */
	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = -ENOMEM;
		back_to_list = true;
		जाओ out_list;
	पूर्ण
	mgm = mailbox->buf;
	members_count = 0;
	list_क्रम_each_entry(dqp, &s_steer->promisc_qps[steer], list)
		mgm->qp[members_count++] = cpu_to_be32(dqp->qpn & MGM_QPN_MASK);
	mgm->members_count = cpu_to_be32(members_count | MLX4_PROT_ETH << 30);

	err = mlx4_WRITE_PROMISC(dev, port, steer, mailbox);
	अगर (err)
		जाओ out_mailbox;

	अगर (!(mlx4_is_mfunc(dev) && steer == MLX4_UC_STEER)) अणु
		/* Remove the QP from all the steering entries */
		list_क्रम_each_entry_safe(entry, पंचांगp_entry,
					 &s_steer->steer_entries[steer],
					 list) अणु
			found = false;
			list_क्रम_each_entry(dqp, &entry->duplicates, list) अणु
				अगर (dqp->qpn == qpn) अणु
					found = true;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (found) अणु
				/* A duplicate, no need to change the MGM,
				 * only update the duplicates list
				 */
				list_del(&dqp->list);
				kमुक्त(dqp);
			पूर्ण अन्यथा अणु
				पूर्णांक loc = -1;

				err = mlx4_READ_ENTRY(dev,
						      entry->index,
						      mailbox);
				अगर (err)
					जाओ out_mailbox;
				members_count =
					be32_to_cpu(mgm->members_count) &
					0xffffff;
				अगर (!members_count) अणु
					mlx4_warn(dev, "QP %06x wasn't found in entry %x mcount=0. deleting entry...\n",
						  qpn, entry->index);
					list_del(&entry->list);
					kमुक्त(entry);
					जारी;
				पूर्ण

				क्रम (i = 0; i < members_count; ++i)
					अगर ((be32_to_cpu(mgm->qp[i]) &
					     MGM_QPN_MASK) == qpn) अणु
						loc = i;
						अवरोध;
					पूर्ण

				अगर (loc < 0) अणु
					mlx4_err(dev, "QP %06x wasn't found in entry %d\n",
						 qpn, entry->index);
					err = -EINVAL;
					जाओ out_mailbox;
				पूर्ण

				/* Copy the last QP in this MGM
				 * over हटाओd QP
				 */
				mgm->qp[loc] = mgm->qp[members_count - 1];
				mgm->qp[members_count - 1] = 0;
				mgm->members_count =
					cpu_to_be32(--members_count |
						    (MLX4_PROT_ETH << 30));

				err = mlx4_WRITE_ENTRY(dev,
						       entry->index,
						       mailbox);
				अगर (err)
					जाओ out_mailbox;
			पूर्ण
		पूर्ण
	पूर्ण

out_mailbox:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
out_list:
	अगर (back_to_list)
		list_add_tail(&pqp->list, &s_steer->promisc_qps[steer]);
	अन्यथा
		kमुक्त(pqp);
out_mutex:
	mutex_unlock(&priv->mcg_table.mutex);
	वापस err;
पूर्ण

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
अटल पूर्णांक find_entry(काष्ठा mlx4_dev *dev, u8 port,
		      u8 *gid, क्रमागत mlx4_protocol prot,
		      काष्ठा mlx4_cmd_mailbox *mgm_mailbox,
		      पूर्णांक *prev, पूर्णांक *index)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm = mgm_mailbox->buf;
	u8 *mgid;
	पूर्णांक err;
	u16 hash;
	u8 op_mod = (prot == MLX4_PROT_ETH) ?
		!!(dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER) : 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस -ENOMEM;
	mgid = mailbox->buf;

	स_नकल(mgid, gid, 16);

	err = mlx4_GID_HASH(dev, mailbox, &hash, op_mod);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (err)
		वापस err;

	अगर (0)
		mlx4_dbg(dev, "Hash for %pI6 is %04x\n", gid, hash);

	*index = hash;
	*prev  = -1;

	करो अणु
		err = mlx4_READ_ENTRY(dev, *index, mgm_mailbox);
		अगर (err)
			वापस err;

		अगर (!(be32_to_cpu(mgm->members_count) & 0xffffff)) अणु
			अगर (*index != hash) अणु
				mlx4_err(dev, "Found zero MGID in AMGM\n");
				err = -EINVAL;
			पूर्ण
			वापस err;
		पूर्ण

		अगर (!स_भेद(mgm->gid, gid, 16) &&
		    be32_to_cpu(mgm->members_count) >> 30 == prot)
			वापस err;

		*prev = *index;
		*index = be32_to_cpu(mgm->next_gid_index) >> 6;
	पूर्ण जबतक (*index);

	*index = -1;
	वापस err;
पूर्ण

अटल स्थिर u8 __promisc_mode[] = अणु
	[MLX4_FS_REGULAR]   = 0x0,
	[MLX4_FS_ALL_DEFAULT] = 0x1,
	[MLX4_FS_MC_DEFAULT] = 0x3,
	[MLX4_FS_MIRROR_RX_PORT] = 0x4,
	[MLX4_FS_MIRROR_SX_PORT] = 0x5,
	[MLX4_FS_UC_SNIFFER] = 0x6,
	[MLX4_FS_MC_SNIFFER] = 0x7,
पूर्ण;

पूर्णांक mlx4_map_sw_to_hw_steering_mode(काष्ठा mlx4_dev *dev,
				    क्रमागत mlx4_net_trans_promisc_mode flow_type)
अणु
	अगर (flow_type >= MLX4_FS_MODE_NUM) अणु
		mlx4_err(dev, "Invalid flow type. type = %d\n", flow_type);
		वापस -EINVAL;
	पूर्ण
	वापस __promisc_mode[flow_type];
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_map_sw_to_hw_steering_mode);

अटल व्योम trans_rule_ctrl_to_hw(काष्ठा mlx4_net_trans_rule *ctrl,
				  काष्ठा mlx4_net_trans_rule_hw_ctrl *hw)
अणु
	u8 flags = 0;

	flags = ctrl->queue_mode == MLX4_NET_TRANS_Q_LIFO ? 1 : 0;
	flags |= ctrl->exclusive ? (1 << 2) : 0;
	flags |= ctrl->allow_loopback ? (1 << 3) : 0;

	hw->flags = flags;
	hw->type = __promisc_mode[ctrl->promisc_mode];
	hw->prio = cpu_to_be16(ctrl->priority);
	hw->port = ctrl->port;
	hw->qpn = cpu_to_be32(ctrl->qpn);
पूर्ण

स्थिर u16 __sw_id_hw[] = अणु
	[MLX4_NET_TRANS_RULE_ID_ETH]     = 0xE001,
	[MLX4_NET_TRANS_RULE_ID_IB]      = 0xE005,
	[MLX4_NET_TRANS_RULE_ID_IPV6]    = 0xE003,
	[MLX4_NET_TRANS_RULE_ID_IPV4]    = 0xE002,
	[MLX4_NET_TRANS_RULE_ID_TCP]     = 0xE004,
	[MLX4_NET_TRANS_RULE_ID_UDP]     = 0xE006,
	[MLX4_NET_TRANS_RULE_ID_VXLAN]	 = 0xE008
पूर्ण;

पूर्णांक mlx4_map_sw_to_hw_steering_id(काष्ठा mlx4_dev *dev,
				  क्रमागत mlx4_net_trans_rule_id id)
अणु
	अगर (id >= MLX4_NET_TRANS_RULE_NUM) अणु
		mlx4_err(dev, "Invalid network rule id. id = %d\n", id);
		वापस -EINVAL;
	पूर्ण
	वापस __sw_id_hw[id];
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_map_sw_to_hw_steering_id);

अटल स्थिर पूर्णांक __rule_hw_sz[] = अणु
	[MLX4_NET_TRANS_RULE_ID_ETH] =
		माप(काष्ठा mlx4_net_trans_rule_hw_eth),
	[MLX4_NET_TRANS_RULE_ID_IB] =
		माप(काष्ठा mlx4_net_trans_rule_hw_ib),
	[MLX4_NET_TRANS_RULE_ID_IPV6] = 0,
	[MLX4_NET_TRANS_RULE_ID_IPV4] =
		माप(काष्ठा mlx4_net_trans_rule_hw_ipv4),
	[MLX4_NET_TRANS_RULE_ID_TCP] =
		माप(काष्ठा mlx4_net_trans_rule_hw_tcp_udp),
	[MLX4_NET_TRANS_RULE_ID_UDP] =
		माप(काष्ठा mlx4_net_trans_rule_hw_tcp_udp),
	[MLX4_NET_TRANS_RULE_ID_VXLAN] =
		माप(काष्ठा mlx4_net_trans_rule_hw_vxlan)
पूर्ण;

पूर्णांक mlx4_hw_rule_sz(काष्ठा mlx4_dev *dev,
	       क्रमागत mlx4_net_trans_rule_id id)
अणु
	अगर (id >= MLX4_NET_TRANS_RULE_NUM) अणु
		mlx4_err(dev, "Invalid network rule id. id = %d\n", id);
		वापस -EINVAL;
	पूर्ण

	वापस __rule_hw_sz[id];
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_hw_rule_sz);

अटल पूर्णांक parse_trans_rule(काष्ठा mlx4_dev *dev, काष्ठा mlx4_spec_list *spec,
			    काष्ठा _rule_hw *rule_hw)
अणु
	अगर (mlx4_hw_rule_sz(dev, spec->id) < 0)
		वापस -EINVAL;
	स_रखो(rule_hw, 0, mlx4_hw_rule_sz(dev, spec->id));
	rule_hw->id = cpu_to_be16(__sw_id_hw[spec->id]);
	rule_hw->size = mlx4_hw_rule_sz(dev, spec->id) >> 2;

	चयन (spec->id) अणु
	हाल MLX4_NET_TRANS_RULE_ID_ETH:
		स_नकल(rule_hw->eth.dst_mac, spec->eth.dst_mac, ETH_ALEN);
		स_नकल(rule_hw->eth.dst_mac_msk, spec->eth.dst_mac_msk,
		       ETH_ALEN);
		स_नकल(rule_hw->eth.src_mac, spec->eth.src_mac, ETH_ALEN);
		स_नकल(rule_hw->eth.src_mac_msk, spec->eth.src_mac_msk,
		       ETH_ALEN);
		अगर (spec->eth.ether_type_enable) अणु
			rule_hw->eth.ether_type_enable = 1;
			rule_hw->eth.ether_type = spec->eth.ether_type;
		पूर्ण
		rule_hw->eth.vlan_tag = spec->eth.vlan_id;
		rule_hw->eth.vlan_tag_msk = spec->eth.vlan_id_msk;
		अवरोध;

	हाल MLX4_NET_TRANS_RULE_ID_IB:
		rule_hw->ib.l3_qpn = spec->ib.l3_qpn;
		rule_hw->ib.qpn_mask = spec->ib.qpn_msk;
		स_नकल(&rule_hw->ib.dst_gid, &spec->ib.dst_gid, 16);
		स_नकल(&rule_hw->ib.dst_gid_msk, &spec->ib.dst_gid_msk, 16);
		अवरोध;

	हाल MLX4_NET_TRANS_RULE_ID_IPV6:
		वापस -EOPNOTSUPP;

	हाल MLX4_NET_TRANS_RULE_ID_IPV4:
		rule_hw->ipv4.src_ip = spec->ipv4.src_ip;
		rule_hw->ipv4.src_ip_msk = spec->ipv4.src_ip_msk;
		rule_hw->ipv4.dst_ip = spec->ipv4.dst_ip;
		rule_hw->ipv4.dst_ip_msk = spec->ipv4.dst_ip_msk;
		अवरोध;

	हाल MLX4_NET_TRANS_RULE_ID_TCP:
	हाल MLX4_NET_TRANS_RULE_ID_UDP:
		rule_hw->tcp_udp.dst_port = spec->tcp_udp.dst_port;
		rule_hw->tcp_udp.dst_port_msk = spec->tcp_udp.dst_port_msk;
		rule_hw->tcp_udp.src_port = spec->tcp_udp.src_port;
		rule_hw->tcp_udp.src_port_msk = spec->tcp_udp.src_port_msk;
		अवरोध;

	हाल MLX4_NET_TRANS_RULE_ID_VXLAN:
		rule_hw->vxlan.vni =
			cpu_to_be32(be32_to_cpu(spec->vxlan.vni) << 8);
		rule_hw->vxlan.vni_mask =
			cpu_to_be32(be32_to_cpu(spec->vxlan.vni_mask) << 8);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस __rule_hw_sz[spec->id];
पूर्ण

अटल व्योम mlx4_err_rule(काष्ठा mlx4_dev *dev, अक्षर *str,
			  काष्ठा mlx4_net_trans_rule *rule)
अणु
#घोषणा BUF_SIZE 256
	काष्ठा mlx4_spec_list *cur;
	अक्षर buf[BUF_SIZE];
	पूर्णांक len = 0;

	mlx4_err(dev, "%s", str);
	len += scnम_लिखो(buf + len, BUF_SIZE - len,
			 "port = %d prio = 0x%x qp = 0x%x ",
			 rule->port, rule->priority, rule->qpn);

	list_क्रम_each_entry(cur, &rule->list, list) अणु
		चयन (cur->id) अणु
		हाल MLX4_NET_TRANS_RULE_ID_ETH:
			len += scnम_लिखो(buf + len, BUF_SIZE - len,
					 "dmac = %pM ", &cur->eth.dst_mac);
			अगर (cur->eth.ether_type)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "ethertype = 0x%x ",
						 be16_to_cpu(cur->eth.ether_type));
			अगर (cur->eth.vlan_id)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "vlan-id = %d ",
						 be16_to_cpu(cur->eth.vlan_id));
			अवरोध;

		हाल MLX4_NET_TRANS_RULE_ID_IPV4:
			अगर (cur->ipv4.src_ip)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "src-ip = %pI4 ",
						 &cur->ipv4.src_ip);
			अगर (cur->ipv4.dst_ip)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "dst-ip = %pI4 ",
						 &cur->ipv4.dst_ip);
			अवरोध;

		हाल MLX4_NET_TRANS_RULE_ID_TCP:
		हाल MLX4_NET_TRANS_RULE_ID_UDP:
			अगर (cur->tcp_udp.src_port)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "src-port = %d ",
						 be16_to_cpu(cur->tcp_udp.src_port));
			अगर (cur->tcp_udp.dst_port)
				len += scnम_लिखो(buf + len, BUF_SIZE - len,
						 "dst-port = %d ",
						 be16_to_cpu(cur->tcp_udp.dst_port));
			अवरोध;

		हाल MLX4_NET_TRANS_RULE_ID_IB:
			len += scnम_लिखो(buf + len, BUF_SIZE - len,
					 "dst-gid = %pI6\n", cur->ib.dst_gid);
			len += scnम_लिखो(buf + len, BUF_SIZE - len,
					 "dst-gid-mask = %pI6\n",
					 cur->ib.dst_gid_msk);
			अवरोध;

		हाल MLX4_NET_TRANS_RULE_ID_VXLAN:
			len += scnम_लिखो(buf + len, BUF_SIZE - len,
					 "VNID = %d ", be32_to_cpu(cur->vxlan.vni));
			अवरोध;
		हाल MLX4_NET_TRANS_RULE_ID_IPV6:
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	len += scnम_लिखो(buf + len, BUF_SIZE - len, "\n");
	mlx4_err(dev, "%s", buf);

	अगर (len >= BUF_SIZE)
		mlx4_err(dev, "Network rule error message was truncated, print buffer is too small\n");
पूर्ण

पूर्णांक mlx4_flow_attach(काष्ठा mlx4_dev *dev,
		     काष्ठा mlx4_net_trans_rule *rule, u64 *reg_id)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_spec_list *cur;
	u32 size = 0;
	पूर्णांक ret;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	अगर (!mlx4_qp_lookup(dev, rule->qpn)) अणु
		mlx4_err_rule(dev, "QP doesn't exist\n", rule);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	trans_rule_ctrl_to_hw(rule, mailbox->buf);

	size += माप(काष्ठा mlx4_net_trans_rule_hw_ctrl);

	list_क्रम_each_entry(cur, &rule->list, list) अणु
		ret = parse_trans_rule(dev, cur, mailbox->buf + size);
		अगर (ret < 0)
			जाओ out;

		size += ret;
	पूर्ण

	ret = mlx4_QP_FLOW_STEERING_ATTACH(dev, mailbox, size >> 2, reg_id);
	अगर (ret == -ENOMEM) अणु
		mlx4_err_rule(dev,
			      "mcg table is full. Fail to register network rule\n",
			      rule);
	पूर्ण अन्यथा अगर (ret) अणु
		अगर (ret == -ENXIO) अणु
			अगर (dev->caps.steering_mode != MLX4_STEERING_MODE_DEVICE_MANAGED)
				mlx4_err_rule(dev,
					      "DMFS is not enabled, "
					      "failed to register network rule.\n",
					      rule);
			अन्यथा
				mlx4_err_rule(dev,
					      "Rule exceeds the dmfs_high_rate_mode limitations, "
					      "failed to register network rule.\n",
					      rule);

		पूर्ण अन्यथा अणु
			mlx4_err_rule(dev, "Fail to register network rule.\n", rule);
		पूर्ण
	पूर्ण

out:
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_flow_attach);

पूर्णांक mlx4_flow_detach(काष्ठा mlx4_dev *dev, u64 reg_id)
अणु
	पूर्णांक err;

	err = mlx4_QP_FLOW_STEERING_DETACH(dev, reg_id);
	अगर (err)
		mlx4_err(dev, "Fail to detach network rule. registration id = 0x%llx\n",
			 reg_id);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_flow_detach);

पूर्णांक mlx4_tunnel_steer_add(काष्ठा mlx4_dev *dev, अचिन्हित अक्षर *addr,
			  पूर्णांक port, पूर्णांक qpn, u16 prio, u64 *reg_id)
अणु
	पूर्णांक err;
	काष्ठा mlx4_spec_list spec_eth_outer = अणु अणुशून्यपूर्ण पूर्ण;
	काष्ठा mlx4_spec_list spec_vxlan     = अणु अणुशून्यपूर्ण पूर्ण;
	काष्ठा mlx4_spec_list spec_eth_inner = अणु अणुशून्यपूर्ण पूर्ण;

	काष्ठा mlx4_net_trans_rule rule = अणु
		.queue_mode = MLX4_NET_TRANS_Q_FIFO,
		.exclusive = 0,
		.allow_loopback = 1,
		.promisc_mode = MLX4_FS_REGULAR,
	पूर्ण;

	__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

	rule.port = port;
	rule.qpn = qpn;
	rule.priority = prio;
	INIT_LIST_HEAD(&rule.list);

	spec_eth_outer.id = MLX4_NET_TRANS_RULE_ID_ETH;
	स_नकल(spec_eth_outer.eth.dst_mac, addr, ETH_ALEN);
	स_नकल(spec_eth_outer.eth.dst_mac_msk, &mac_mask, ETH_ALEN);

	spec_vxlan.id = MLX4_NET_TRANS_RULE_ID_VXLAN;    /* any vxlan header */
	spec_eth_inner.id = MLX4_NET_TRANS_RULE_ID_ETH;	 /* any inner eth header */

	list_add_tail(&spec_eth_outer.list, &rule.list);
	list_add_tail(&spec_vxlan.list,     &rule.list);
	list_add_tail(&spec_eth_inner.list, &rule.list);

	err = mlx4_flow_attach(dev, &rule, reg_id);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx4_tunnel_steer_add);

पूर्णांक mlx4_FLOW_STEERING_IB_UC_QP_RANGE(काष्ठा mlx4_dev *dev, u32 min_range_qpn,
				      u32 max_range_qpn)
अणु
	पूर्णांक err;
	u64 in_param;

	in_param = ((u64) min_range_qpn) << 32;
	in_param |= ((u64) max_range_qpn) & 0xFFFFFFFF;

	err = mlx4_cmd(dev, in_param, 0, 0,
			MLX4_FLOW_STEERING_IB_UC_QP_RANGE,
			MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_FLOW_STEERING_IB_UC_QP_RANGE);

पूर्णांक mlx4_qp_attach_common(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  पूर्णांक block_mcast_loopback, क्रमागत mlx4_protocol prot,
			  क्रमागत mlx4_steer_type steer)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	u32 members_count;
	पूर्णांक index = -1, prev;
	पूर्णांक link = 0;
	पूर्णांक i;
	पूर्णांक err;
	u8 port = gid[5];
	u8 new_entry = 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	mgm = mailbox->buf;

	mutex_lock(&priv->mcg_table.mutex);
	err = find_entry(dev, port, gid, prot,
			 mailbox, &prev, &index);
	अगर (err)
		जाओ out;

	अगर (index != -1) अणु
		अगर (!(be32_to_cpu(mgm->members_count) & 0xffffff)) अणु
			new_entry = 1;
			स_नकल(mgm->gid, gid, 16);
		पूर्ण
	पूर्ण अन्यथा अणु
		link = 1;

		index = mlx4_biपंचांगap_alloc(&priv->mcg_table.biपंचांगap);
		अगर (index == -1) अणु
			mlx4_err(dev, "No AMGM entries left\n");
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		index += dev->caps.num_mgms;

		new_entry = 1;
		स_रखो(mgm, 0, माप(*mgm));
		स_नकल(mgm->gid, gid, 16);
	पूर्ण

	members_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	अगर (members_count == dev->caps.num_qp_per_mgm) अणु
		mlx4_err(dev, "MGM at index %x is full\n", index);
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < members_count; ++i)
		अगर ((be32_to_cpu(mgm->qp[i]) & MGM_QPN_MASK) == qp->qpn) अणु
			mlx4_dbg(dev, "QP %06x already a member of MGM\n", qp->qpn);
			err = 0;
			जाओ out;
		पूर्ण

	अगर (block_mcast_loopback)
		mgm->qp[members_count++] = cpu_to_be32((qp->qpn & MGM_QPN_MASK) |
						       (1U << MGM_BLCK_LB_BIT));
	अन्यथा
		mgm->qp[members_count++] = cpu_to_be32(qp->qpn & MGM_QPN_MASK);

	mgm->members_count = cpu_to_be32(members_count | (u32) prot << 30);

	err = mlx4_WRITE_ENTRY(dev, index, mailbox);
	अगर (err)
		जाओ out;

	अगर (!link)
		जाओ out;

	err = mlx4_READ_ENTRY(dev, prev, mailbox);
	अगर (err)
		जाओ out;

	mgm->next_gid_index = cpu_to_be32(index << 6);

	err = mlx4_WRITE_ENTRY(dev, prev, mailbox);
	अगर (err)
		जाओ out;

out:
	अगर (prot == MLX4_PROT_ETH && index != -1) अणु
		/* manage the steering entry क्रम promisc mode */
		अगर (new_entry)
			err = new_steering_entry(dev, port, steer,
						 index, qp->qpn);
		अन्यथा
			err = existing_steering_entry(dev, port, steer,
						      index, qp->qpn);
	पूर्ण
	अगर (err && link && index != -1) अणु
		अगर (index < dev->caps.num_mgms)
			mlx4_warn(dev, "Got AMGM index %d < %d\n",
				  index, dev->caps.num_mgms);
		अन्यथा
			mlx4_biपंचांगap_मुक्त(&priv->mcg_table.biपंचांगap,
					 index - dev->caps.num_mgms, MLX4_USE_RR);
	पूर्ण
	mutex_unlock(&priv->mcg_table.mutex);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;
पूर्ण

पूर्णांक mlx4_qp_detach_common(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  क्रमागत mlx4_protocol prot, क्रमागत mlx4_steer_type steer)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_mgm *mgm;
	u32 members_count;
	पूर्णांक prev, index;
	पूर्णांक i, loc = -1;
	पूर्णांक err;
	u8 port = gid[5];
	bool हटाओd_entry = false;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);
	mgm = mailbox->buf;

	mutex_lock(&priv->mcg_table.mutex);

	err = find_entry(dev, port, gid, prot,
			 mailbox, &prev, &index);
	अगर (err)
		जाओ out;

	अगर (index == -1) अणु
		mlx4_err(dev, "MGID %pI6 not found\n", gid);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* If this QP is also a promisc QP, it shouldn't be हटाओd only अगर
	 * at least one none promisc QP is also attached to this MCG
	 */
	अगर (prot == MLX4_PROT_ETH &&
	    check_duplicate_entry(dev, port, steer, index, qp->qpn) &&
	    !promisc_steering_entry(dev, port, steer, index, qp->qpn, शून्य))
			जाओ out;

	members_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	क्रम (i = 0; i < members_count; ++i)
		अगर ((be32_to_cpu(mgm->qp[i]) & MGM_QPN_MASK) == qp->qpn) अणु
			loc = i;
			अवरोध;
		पूर्ण

	अगर (loc == -1) अणु
		mlx4_err(dev, "QP %06x not found in MGM\n", qp->qpn);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	/* copy the last QP in this MGM over हटाओd QP */
	mgm->qp[loc] = mgm->qp[members_count - 1];
	mgm->qp[members_count - 1] = 0;
	mgm->members_count = cpu_to_be32(--members_count | (u32) prot << 30);

	अगर (prot == MLX4_PROT_ETH)
		हटाओd_entry = can_हटाओ_steering_entry(dev, port, steer,
								index, qp->qpn);
	अगर (members_count && (prot != MLX4_PROT_ETH || !हटाओd_entry)) अणु
		err = mlx4_WRITE_ENTRY(dev, index, mailbox);
		जाओ out;
	पूर्ण

	/* We are going to delete the entry, members count should be 0 */
	mgm->members_count = cpu_to_be32((u32) prot << 30);

	अगर (prev == -1) अणु
		/* Remove entry from MGM */
		पूर्णांक amgm_index = be32_to_cpu(mgm->next_gid_index) >> 6;
		अगर (amgm_index) अणु
			err = mlx4_READ_ENTRY(dev, amgm_index, mailbox);
			अगर (err)
				जाओ out;
		पूर्ण अन्यथा
			स_रखो(mgm->gid, 0, 16);

		err = mlx4_WRITE_ENTRY(dev, index, mailbox);
		अगर (err)
			जाओ out;

		अगर (amgm_index) अणु
			अगर (amgm_index < dev->caps.num_mgms)
				mlx4_warn(dev, "MGM entry %d had AMGM index %d < %d\n",
					  index, amgm_index, dev->caps.num_mgms);
			अन्यथा
				mlx4_biपंचांगap_मुक्त(&priv->mcg_table.biपंचांगap,
						 amgm_index - dev->caps.num_mgms, MLX4_USE_RR);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Remove entry from AMGM */
		पूर्णांक cur_next_index = be32_to_cpu(mgm->next_gid_index) >> 6;
		err = mlx4_READ_ENTRY(dev, prev, mailbox);
		अगर (err)
			जाओ out;

		mgm->next_gid_index = cpu_to_be32(cur_next_index << 6);

		err = mlx4_WRITE_ENTRY(dev, prev, mailbox);
		अगर (err)
			जाओ out;

		अगर (index < dev->caps.num_mgms)
			mlx4_warn(dev, "entry %d had next AMGM index %d < %d\n",
				  prev, index, dev->caps.num_mgms);
		अन्यथा
			mlx4_biपंचांगap_मुक्त(&priv->mcg_table.biपंचांगap,
					 index - dev->caps.num_mgms, MLX4_USE_RR);
	पूर्ण

out:
	mutex_unlock(&priv->mcg_table.mutex);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (err && dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		/* In हाल device is under an error, वापस success as a closing command */
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_QP_ATTACH(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
			  u8 gid[16], u8 attach, u8 block_loopback,
			  क्रमागत mlx4_protocol prot)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err = 0;
	पूर्णांक qpn;

	अगर (!mlx4_is_mfunc(dev))
		वापस -EBADF;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	स_नकल(mailbox->buf, gid, 16);
	qpn = qp->qpn;
	qpn |= (prot << 28);
	अगर (attach && block_loopback)
		qpn |= (1 << 31);

	err = mlx4_cmd(dev, mailbox->dma, qpn, attach,
		       MLX4_CMD_QP_ATTACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_WRAPPED);

	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	अगर (err && !attach &&
	    dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR)
		err = 0;
	वापस err;
पूर्ण

पूर्णांक mlx4_trans_to_dmfs_attach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
			      u8 gid[16], u8 port,
			      पूर्णांक block_mcast_loopback,
			      क्रमागत mlx4_protocol prot, u64 *reg_id)
अणु
		काष्ठा mlx4_spec_list spec = अणु अणुशून्यपूर्ण पूर्ण;
		__be64 mac_mask = cpu_to_be64(MLX4_MAC_MASK << 16);

		काष्ठा mlx4_net_trans_rule rule = अणु
			.queue_mode = MLX4_NET_TRANS_Q_FIFO,
			.exclusive = 0,
			.promisc_mode = MLX4_FS_REGULAR,
			.priority = MLX4_DOMAIN_NIC,
		पूर्ण;

		rule.allow_loopback = !block_mcast_loopback;
		rule.port = port;
		rule.qpn = qp->qpn;
		INIT_LIST_HEAD(&rule.list);

		चयन (prot) अणु
		हाल MLX4_PROT_ETH:
			spec.id = MLX4_NET_TRANS_RULE_ID_ETH;
			स_नकल(spec.eth.dst_mac, &gid[10], ETH_ALEN);
			स_नकल(spec.eth.dst_mac_msk, &mac_mask, ETH_ALEN);
			अवरोध;

		हाल MLX4_PROT_IB_IPV6:
			spec.id = MLX4_NET_TRANS_RULE_ID_IB;
			स_नकल(spec.ib.dst_gid, gid, 16);
			स_रखो(&spec.ib.dst_gid_msk, 0xff, 16);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		list_add_tail(&spec.list, &rule.list);

		वापस mlx4_flow_attach(dev, &rule, reg_id);
पूर्ण

पूर्णांक mlx4_multicast_attach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  u8 port, पूर्णांक block_mcast_loopback,
			  क्रमागत mlx4_protocol prot, u64 *reg_id)
अणु
	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_A0:
		अगर (prot == MLX4_PROT_ETH)
			वापस 0;
		fallthrough;

	हाल MLX4_STEERING_MODE_B0:
		अगर (prot == MLX4_PROT_ETH)
			gid[7] |= (MLX4_MC_STEER << 1);

		अगर (mlx4_is_mfunc(dev))
			वापस mlx4_QP_ATTACH(dev, qp, gid, 1,
					      block_mcast_loopback, prot);
		वापस mlx4_qp_attach_common(dev, qp, gid,
					     block_mcast_loopback, prot,
					     MLX4_MC_STEER);

	हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
		वापस mlx4_trans_to_dmfs_attach(dev, qp, gid, port,
						 block_mcast_loopback,
						 prot, reg_id);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_multicast_attach);

पूर्णांक mlx4_multicast_detach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp, u8 gid[16],
			  क्रमागत mlx4_protocol prot, u64 reg_id)
अणु
	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_A0:
		अगर (prot == MLX4_PROT_ETH)
			वापस 0;
		fallthrough;

	हाल MLX4_STEERING_MODE_B0:
		अगर (prot == MLX4_PROT_ETH)
			gid[7] |= (MLX4_MC_STEER << 1);

		अगर (mlx4_is_mfunc(dev))
			वापस mlx4_QP_ATTACH(dev, qp, gid, 0, 0, prot);

		वापस mlx4_qp_detach_common(dev, qp, gid, prot,
					     MLX4_MC_STEER);

	हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
		वापस mlx4_flow_detach(dev, reg_id);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_multicast_detach);

पूर्णांक mlx4_flow_steer_promisc_add(काष्ठा mlx4_dev *dev, u8 port,
				u32 qpn, क्रमागत mlx4_net_trans_promisc_mode mode)
अणु
	काष्ठा mlx4_net_trans_rule rule = अणु
		.queue_mode = MLX4_NET_TRANS_Q_FIFO,
		.exclusive = 0,
		.allow_loopback = 1,
	पूर्ण;

	u64 *regid_p;

	चयन (mode) अणु
	हाल MLX4_FS_ALL_DEFAULT:
		regid_p = &dev->regid_promisc_array[port];
		अवरोध;
	हाल MLX4_FS_MC_DEFAULT:
		regid_p = &dev->regid_allmulti_array[port];
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (*regid_p != 0)
		वापस -1;

	rule.promisc_mode = mode;
	rule.port = port;
	rule.qpn = qpn;
	INIT_LIST_HEAD(&rule.list);
	mlx4_info(dev, "going promisc on %x\n", port);

	वापस  mlx4_flow_attach(dev, &rule, regid_p);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_flow_steer_promisc_add);

पूर्णांक mlx4_flow_steer_promisc_हटाओ(काष्ठा mlx4_dev *dev, u8 port,
				   क्रमागत mlx4_net_trans_promisc_mode mode)
अणु
	पूर्णांक ret;
	u64 *regid_p;

	चयन (mode) अणु
	हाल MLX4_FS_ALL_DEFAULT:
		regid_p = &dev->regid_promisc_array[port];
		अवरोध;
	हाल MLX4_FS_MC_DEFAULT:
		regid_p = &dev->regid_allmulti_array[port];
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	अगर (*regid_p == 0)
		वापस -1;

	ret =  mlx4_flow_detach(dev, *regid_p);
	अगर (ret == 0)
		*regid_p = 0;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_flow_steer_promisc_हटाओ);

पूर्णांक mlx4_unicast_attach(काष्ठा mlx4_dev *dev,
			काष्ठा mlx4_qp *qp, u8 gid[16],
			पूर्णांक block_mcast_loopback, क्रमागत mlx4_protocol prot)
अणु
	अगर (prot == MLX4_PROT_ETH)
		gid[7] |= (MLX4_UC_STEER << 1);

	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_QP_ATTACH(dev, qp, gid, 1,
					block_mcast_loopback, prot);

	वापस mlx4_qp_attach_common(dev, qp, gid, block_mcast_loopback,
					prot, MLX4_UC_STEER);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unicast_attach);

पूर्णांक mlx4_unicast_detach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
			       u8 gid[16], क्रमागत mlx4_protocol prot)
अणु
	अगर (prot == MLX4_PROT_ETH)
		gid[7] |= (MLX4_UC_STEER << 1);

	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_QP_ATTACH(dev, qp, gid, 0, 0, prot);

	वापस mlx4_qp_detach_common(dev, qp, gid, prot, MLX4_UC_STEER);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unicast_detach);

पूर्णांक mlx4_PROMISC_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd)
अणु
	u32 qpn = (u32) vhcr->in_param & 0xffffffff;
	पूर्णांक port = mlx4_slave_convert_port(dev, slave, vhcr->in_param >> 62);
	क्रमागत mlx4_steer_type steer = vhcr->in_modअगरier;

	अगर (port < 0)
		वापस -EINVAL;

	/* Promiscuous unicast is not allowed in mfunc */
	अगर (mlx4_is_mfunc(dev) && steer == MLX4_UC_STEER)
		वापस 0;

	अगर (vhcr->op_modअगरier)
		वापस add_promisc_qp(dev, port, steer, qpn);
	अन्यथा
		वापस हटाओ_promisc_qp(dev, port, steer, qpn);
पूर्ण

अटल पूर्णांक mlx4_PROMISC(काष्ठा mlx4_dev *dev, u32 qpn,
			क्रमागत mlx4_steer_type steer, u8 add, u8 port)
अणु
	वापस mlx4_cmd(dev, (u64) qpn | (u64) port << 62, (u32) steer, add,
			MLX4_CMD_PROMISC, MLX4_CMD_TIME_CLASS_A,
			MLX4_CMD_WRAPPED);
पूर्ण

पूर्णांक mlx4_multicast_promisc_add(काष्ठा mlx4_dev *dev, u32 qpn, u8 port)
अणु
	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_PROMISC(dev, qpn, MLX4_MC_STEER, 1, port);

	वापस add_promisc_qp(dev, port, MLX4_MC_STEER, qpn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_multicast_promisc_add);

पूर्णांक mlx4_multicast_promisc_हटाओ(काष्ठा mlx4_dev *dev, u32 qpn, u8 port)
अणु
	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_PROMISC(dev, qpn, MLX4_MC_STEER, 0, port);

	वापस हटाओ_promisc_qp(dev, port, MLX4_MC_STEER, qpn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_multicast_promisc_हटाओ);

पूर्णांक mlx4_unicast_promisc_add(काष्ठा mlx4_dev *dev, u32 qpn, u8 port)
अणु
	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_PROMISC(dev, qpn, MLX4_UC_STEER, 1, port);

	वापस add_promisc_qp(dev, port, MLX4_UC_STEER, qpn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unicast_promisc_add);

पूर्णांक mlx4_unicast_promisc_हटाओ(काष्ठा mlx4_dev *dev, u32 qpn, u8 port)
अणु
	अगर (mlx4_is_mfunc(dev))
		वापस mlx4_PROMISC(dev, qpn, MLX4_UC_STEER, 0, port);

	वापस हटाओ_promisc_qp(dev, port, MLX4_UC_STEER, qpn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_unicast_promisc_हटाओ);

पूर्णांक mlx4_init_mcg_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक err;

	/* No need क्रम mcg_table when fw managed the mcg table*/
	अगर (dev->caps.steering_mode ==
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		वापस 0;
	err = mlx4_biपंचांगap_init(&priv->mcg_table.biपंचांगap, dev->caps.num_amgms,
			       dev->caps.num_amgms - 1, 0, 0);
	अगर (err)
		वापस err;

	mutex_init(&priv->mcg_table.mutex);

	वापस 0;
पूर्ण

व्योम mlx4_cleanup_mcg_table(काष्ठा mlx4_dev *dev)
अणु
	अगर (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->mcg_table.biपंचांगap);
पूर्ण
