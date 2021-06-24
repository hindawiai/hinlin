<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*******************************************************************************
 * SCSI RDMA Protocol lib functions
 *
 * Copyright (C) 2006 FUJITA Tomonori <tomof@acm.org>
 * Copyright (C) 2016 Bryant G. Ly <bryantly@linux.vnet.ibm.com> IBM Corp.
 *
 ***********************************************************************/

#घोषणा pr_fmt(fmt)	"libsrp: " fmt

#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <scsi/srp.h>
#समावेश <target/target_core_base.h>
#समावेश "libsrp.h"
#समावेश "ibmvscsi_tgt.h"

अटल पूर्णांक srp_iu_pool_alloc(काष्ठा srp_queue *q, माप_प्रकार max,
			     काष्ठा srp_buf **ring)
अणु
	काष्ठा iu_entry *iue;
	पूर्णांक i;

	q->pool = kसुस्मृति(max, माप(काष्ठा iu_entry *), GFP_KERNEL);
	अगर (!q->pool)
		वापस -ENOMEM;
	q->items = kसुस्मृति(max, माप(काष्ठा iu_entry), GFP_KERNEL);
	अगर (!q->items)
		जाओ मुक्त_pool;

	spin_lock_init(&q->lock);
	kfअगरo_init(&q->queue, (व्योम *)q->pool, max * माप(व्योम *));

	क्रम (i = 0, iue = q->items; i < max; i++) अणु
		kfअगरo_in(&q->queue, (व्योम *)&iue, माप(व्योम *));
		iue->sbuf = ring[i];
		iue++;
	पूर्ण
	वापस 0;

मुक्त_pool:
	kमुक्त(q->pool);
	वापस -ENOMEM;
पूर्ण

अटल व्योम srp_iu_pool_मुक्त(काष्ठा srp_queue *q)
अणु
	kमुक्त(q->items);
	kमुक्त(q->pool);
पूर्ण

अटल काष्ठा srp_buf **srp_ring_alloc(काष्ठा device *dev,
				       माप_प्रकार max, माप_प्रकार size)
अणु
	काष्ठा srp_buf **ring;
	पूर्णांक i;

	ring = kसुस्मृति(max, माप(काष्ठा srp_buf *), GFP_KERNEL);
	अगर (!ring)
		वापस शून्य;

	क्रम (i = 0; i < max; i++) अणु
		ring[i] = kzalloc(माप(*ring[i]), GFP_KERNEL);
		अगर (!ring[i])
			जाओ out;
		ring[i]->buf = dma_alloc_coherent(dev, size, &ring[i]->dma,
						  GFP_KERNEL);
		अगर (!ring[i]->buf)
			जाओ out;
	पूर्ण
	वापस ring;

out:
	क्रम (i = 0; i < max && ring[i]; i++) अणु
		अगर (ring[i]->buf) अणु
			dma_मुक्त_coherent(dev, size, ring[i]->buf,
					  ring[i]->dma);
		पूर्ण
		kमुक्त(ring[i]);
	पूर्ण
	kमुक्त(ring);

	वापस शून्य;
पूर्ण

अटल व्योम srp_ring_मुक्त(काष्ठा device *dev, काष्ठा srp_buf **ring,
			  माप_प्रकार max, माप_प्रकार size)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < max; i++) अणु
		dma_मुक्त_coherent(dev, size, ring[i]->buf, ring[i]->dma);
		kमुक्त(ring[i]);
	पूर्ण
	kमुक्त(ring);
पूर्ण

पूर्णांक srp_target_alloc(काष्ठा srp_target *target, काष्ठा device *dev,
		     माप_प्रकार nr, माप_प्रकार iu_size)
अणु
	पूर्णांक err;

	spin_lock_init(&target->lock);

	target->dev = dev;

	target->srp_iu_size = iu_size;
	target->rx_ring_size = nr;
	target->rx_ring = srp_ring_alloc(target->dev, nr, iu_size);
	अगर (!target->rx_ring)
		वापस -ENOMEM;
	err = srp_iu_pool_alloc(&target->iu_queue, nr, target->rx_ring);
	अगर (err)
		जाओ मुक्त_ring;

	dev_set_drvdata(target->dev, target);
	वापस 0;

मुक्त_ring:
	srp_ring_मुक्त(target->dev, target->rx_ring, nr, iu_size);
	वापस -ENOMEM;
पूर्ण

व्योम srp_target_मुक्त(काष्ठा srp_target *target)
अणु
	dev_set_drvdata(target->dev, शून्य);
	srp_ring_मुक्त(target->dev, target->rx_ring, target->rx_ring_size,
		      target->srp_iu_size);
	srp_iu_pool_मुक्त(&target->iu_queue);
पूर्ण

काष्ठा iu_entry *srp_iu_get(काष्ठा srp_target *target)
अणु
	काष्ठा iu_entry *iue = शून्य;

	अगर (kfअगरo_out_locked(&target->iu_queue.queue, (व्योम *)&iue,
			     माप(व्योम *),
			     &target->iu_queue.lock) != माप(व्योम *)) अणु
		WARN_ONCE(1, "unexpected fifo state");
		वापस शून्य;
	पूर्ण
	अगर (!iue)
		वापस iue;
	iue->target = target;
	iue->flags = 0;
	वापस iue;
पूर्ण

व्योम srp_iu_put(काष्ठा iu_entry *iue)
अणु
	kfअगरo_in_locked(&iue->target->iu_queue.queue, (व्योम *)&iue,
			माप(व्योम *), &iue->target->iu_queue.lock);
पूर्ण

अटल पूर्णांक srp_direct_data(काष्ठा ibmvscsis_cmd *cmd, काष्ठा srp_direct_buf *md,
			   क्रमागत dma_data_direction dir, srp_rdma_t rdma_io,
			   पूर्णांक dma_map, पूर्णांक ext_desc)
अणु
	काष्ठा iu_entry *iue = शून्य;
	काष्ठा scatterlist *sg = शून्य;
	पूर्णांक err, nsg = 0, len;

	अगर (dma_map) अणु
		iue = cmd->iue;
		sg = cmd->se_cmd.t_data_sg;
		nsg = dma_map_sg(iue->target->dev, sg, cmd->se_cmd.t_data_nents,
				 DMA_BIसूचीECTIONAL);
		अगर (!nsg) अणु
			pr_err("fail to map %p %d\n", iue,
			       cmd->se_cmd.t_data_nents);
			वापस 0;
		पूर्ण
		len = min(cmd->se_cmd.data_length, be32_to_cpu(md->len));
	पूर्ण अन्यथा अणु
		len = be32_to_cpu(md->len);
	पूर्ण

	err = rdma_io(cmd, sg, nsg, md, 1, dir, len);

	अगर (dma_map)
		dma_unmap_sg(iue->target->dev, sg, nsg, DMA_BIसूचीECTIONAL);

	वापस err;
पूर्ण

अटल पूर्णांक srp_indirect_data(काष्ठा ibmvscsis_cmd *cmd, काष्ठा srp_cmd *srp_cmd,
			     काष्ठा srp_indirect_buf *id,
			     क्रमागत dma_data_direction dir, srp_rdma_t rdma_io,
			     पूर्णांक dma_map, पूर्णांक ext_desc)
अणु
	काष्ठा iu_entry *iue = शून्य;
	काष्ठा srp_direct_buf *md = शून्य;
	काष्ठा scatterlist dummy, *sg = शून्य;
	dma_addr_t token = 0;
	पूर्णांक err = 0;
	पूर्णांक nmd, nsg = 0, len;

	अगर (dma_map || ext_desc) अणु
		iue = cmd->iue;
		sg = cmd->se_cmd.t_data_sg;
	पूर्ण

	nmd = be32_to_cpu(id->table_desc.len) / माप(काष्ठा srp_direct_buf);

	अगर ((dir == DMA_FROM_DEVICE && nmd == srp_cmd->data_in_desc_cnt) ||
	    (dir == DMA_TO_DEVICE && nmd == srp_cmd->data_out_desc_cnt)) अणु
		md = &id->desc_list[0];
		जाओ rdma;
	पूर्ण

	अगर (ext_desc && dma_map) अणु
		md = dma_alloc_coherent(iue->target->dev,
					be32_to_cpu(id->table_desc.len),
					&token, GFP_KERNEL);
		अगर (!md) अणु
			pr_err("Can't get dma memory %u\n",
			       be32_to_cpu(id->table_desc.len));
			वापस -ENOMEM;
		पूर्ण

		sg_init_one(&dummy, md, be32_to_cpu(id->table_desc.len));
		sg_dma_address(&dummy) = token;
		sg_dma_len(&dummy) = be32_to_cpu(id->table_desc.len);
		err = rdma_io(cmd, &dummy, 1, &id->table_desc, 1, DMA_TO_DEVICE,
			      be32_to_cpu(id->table_desc.len));
		अगर (err) अणु
			pr_err("Error copying indirect table %d\n", err);
			जाओ मुक्त_mem;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("This command uses external indirect buffer\n");
		वापस -EINVAL;
	पूर्ण

rdma:
	अगर (dma_map) अणु
		nsg = dma_map_sg(iue->target->dev, sg, cmd->se_cmd.t_data_nents,
				 DMA_BIसूचीECTIONAL);
		अगर (!nsg) अणु
			pr_err("fail to map %p %d\n", iue,
			       cmd->se_cmd.t_data_nents);
			err = -EIO;
			जाओ मुक्त_mem;
		पूर्ण
		len = min(cmd->se_cmd.data_length, be32_to_cpu(id->len));
	पूर्ण अन्यथा अणु
		len = be32_to_cpu(id->len);
	पूर्ण

	err = rdma_io(cmd, sg, nsg, md, nmd, dir, len);

	अगर (dma_map)
		dma_unmap_sg(iue->target->dev, sg, nsg, DMA_BIसूचीECTIONAL);

मुक्त_mem:
	अगर (token && dma_map) अणु
		dma_मुक्त_coherent(iue->target->dev,
				  be32_to_cpu(id->table_desc.len), md, token);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक data_out_desc_size(काष्ठा srp_cmd *cmd)
अणु
	पूर्णांक size = 0;
	u8 fmt = cmd->buf_fmt >> 4;

	चयन (fmt) अणु
	हाल SRP_NO_DATA_DESC:
		अवरोध;
	हाल SRP_DATA_DESC_सूचीECT:
		size = माप(काष्ठा srp_direct_buf);
		अवरोध;
	हाल SRP_DATA_DESC_INसूचीECT:
		size = माप(काष्ठा srp_indirect_buf) +
			माप(काष्ठा srp_direct_buf) * cmd->data_out_desc_cnt;
		अवरोध;
	शेष:
		pr_err("client error. Invalid data_out_format %x\n", fmt);
		अवरोध;
	पूर्ण
	वापस size;
पूर्ण

/*
 * TODO: this can be called multiple बार क्रम a single command अगर it
 * has very दीर्घ data.
 */
पूर्णांक srp_transfer_data(काष्ठा ibmvscsis_cmd *cmd, काष्ठा srp_cmd *srp_cmd,
		      srp_rdma_t rdma_io, पूर्णांक dma_map, पूर्णांक ext_desc)
अणु
	काष्ठा srp_direct_buf *md;
	काष्ठा srp_indirect_buf *id;
	क्रमागत dma_data_direction dir;
	पूर्णांक offset, err = 0;
	u8 क्रमmat;

	अगर (!cmd->se_cmd.t_data_nents)
		वापस 0;

	offset = srp_cmd->add_cdb_len & ~3;

	dir = srp_cmd_direction(srp_cmd);
	अगर (dir == DMA_FROM_DEVICE)
		offset += data_out_desc_size(srp_cmd);

	अगर (dir == DMA_TO_DEVICE)
		क्रमmat = srp_cmd->buf_fmt >> 4;
	अन्यथा
		क्रमmat = srp_cmd->buf_fmt & ((1U << 4) - 1);

	चयन (क्रमmat) अणु
	हाल SRP_NO_DATA_DESC:
		अवरोध;
	हाल SRP_DATA_DESC_सूचीECT:
		md = (काष्ठा srp_direct_buf *)(srp_cmd->add_data + offset);
		err = srp_direct_data(cmd, md, dir, rdma_io, dma_map, ext_desc);
		अवरोध;
	हाल SRP_DATA_DESC_INसूचीECT:
		id = (काष्ठा srp_indirect_buf *)(srp_cmd->add_data + offset);
		err = srp_indirect_data(cmd, srp_cmd, id, dir, rdma_io, dma_map,
					ext_desc);
		अवरोध;
	शेष:
		pr_err("Unknown format %d %x\n", dir, क्रमmat);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

u64 srp_data_length(काष्ठा srp_cmd *cmd, क्रमागत dma_data_direction dir)
अणु
	काष्ठा srp_direct_buf *md;
	काष्ठा srp_indirect_buf *id;
	u64 len = 0;
	uपूर्णांक offset = cmd->add_cdb_len & ~3;
	u8 fmt;

	अगर (dir == DMA_TO_DEVICE) अणु
		fmt = cmd->buf_fmt >> 4;
	पूर्ण अन्यथा अणु
		fmt = cmd->buf_fmt & ((1U << 4) - 1);
		offset += data_out_desc_size(cmd);
	पूर्ण

	चयन (fmt) अणु
	हाल SRP_NO_DATA_DESC:
		अवरोध;
	हाल SRP_DATA_DESC_सूचीECT:
		md = (काष्ठा srp_direct_buf *)(cmd->add_data + offset);
		len = be32_to_cpu(md->len);
		अवरोध;
	हाल SRP_DATA_DESC_INसूचीECT:
		id = (काष्ठा srp_indirect_buf *)(cmd->add_data + offset);
		len = be32_to_cpu(id->len);
		अवरोध;
	शेष:
		pr_err("invalid data format %x\n", fmt);
		अवरोध;
	पूर्ण
	वापस len;
पूर्ण

पूर्णांक srp_get_desc_table(काष्ठा srp_cmd *srp_cmd, क्रमागत dma_data_direction *dir,
		       u64 *data_len)
अणु
	काष्ठा srp_indirect_buf *idb;
	काष्ठा srp_direct_buf *db;
	uपूर्णांक add_cdb_offset;
	पूर्णांक rc;

	/*
	 * The poपूर्णांकer computations below will only be compiled correctly
	 * अगर srp_cmd::add_data is declared as s8*, u8*, s8[] or u8[], so check
	 * whether srp_cmd::add_data has been declared as a byte poपूर्णांकer.
	 */
	BUILD_BUG_ON(!__same_type(srp_cmd->add_data[0], (s8)0)
		     && !__same_type(srp_cmd->add_data[0], (u8)0));

	BUG_ON(!dir);
	BUG_ON(!data_len);

	rc = 0;
	*data_len = 0;

	*dir = DMA_NONE;

	अगर (srp_cmd->buf_fmt & 0xf)
		*dir = DMA_FROM_DEVICE;
	अन्यथा अगर (srp_cmd->buf_fmt >> 4)
		*dir = DMA_TO_DEVICE;

	add_cdb_offset = srp_cmd->add_cdb_len & ~3;
	अगर (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_सूचीECT) ||
	    ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_सूचीECT)) अणु
		db = (काष्ठा srp_direct_buf *)(srp_cmd->add_data
					       + add_cdb_offset);
		*data_len = be32_to_cpu(db->len);
	पूर्ण अन्यथा अगर (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_INसूचीECT) ||
		   ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_INसूचीECT)) अणु
		idb = (काष्ठा srp_indirect_buf *)(srp_cmd->add_data
						  + add_cdb_offset);

		*data_len = be32_to_cpu(idb->len);
	पूर्ण
	वापस rc;
पूर्ण

MODULE_DESCRIPTION("SCSI RDMA Protocol lib functions");
MODULE_AUTHOR("FUJITA Tomonori");
MODULE_LICENSE("GPL");
