<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright 2019 NXP

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/iommu.h>
#समावेश <linux/sys_soc.h>
#समावेश <linux/fsl/mc.h>
#समावेश <soc/fsl/dpaa2-पन.स>

#समावेश "../virt-dma.h"
#समावेश "dpdmai.h"
#समावेश "dpaa2-qdma.h"

अटल bool smmu_disable = true;

अटल काष्ठा dpaa2_qdma_chan *to_dpaa2_qdma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा dpaa2_qdma_chan, vchan.chan);
पूर्ण

अटल काष्ठा dpaa2_qdma_comp *to_fsl_qdma_comp(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा dpaa2_qdma_comp, vdesc);
पूर्ण

अटल पूर्णांक dpaa2_qdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	काष्ठा dpaa2_qdma_engine *dpaa2_qdma = dpaa2_chan->qdma;
	काष्ठा device *dev = &dpaa2_qdma->priv->dpdmai_dev->dev;

	dpaa2_chan->fd_pool = dma_pool_create("fd_pool", dev,
					      माप(काष्ठा dpaa2_fd),
					      माप(काष्ठा dpaa2_fd), 0);
	अगर (!dpaa2_chan->fd_pool)
		जाओ err;

	dpaa2_chan->fl_pool = dma_pool_create("fl_pool", dev,
					      माप(काष्ठा dpaa2_fl_entry),
					      माप(काष्ठा dpaa2_fl_entry), 0);
	अगर (!dpaa2_chan->fl_pool)
		जाओ err_fd;

	dpaa2_chan->sdd_pool =
		dma_pool_create("sdd_pool", dev,
				माप(काष्ठा dpaa2_qdma_sd_d),
				माप(काष्ठा dpaa2_qdma_sd_d), 0);
	अगर (!dpaa2_chan->sdd_pool)
		जाओ err_fl;

	वापस dpaa2_qdma->desc_allocated++;
err_fl:
	dma_pool_destroy(dpaa2_chan->fl_pool);
err_fd:
	dma_pool_destroy(dpaa2_chan->fd_pool);
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम dpaa2_qdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	काष्ठा dpaa2_qdma_engine *dpaa2_qdma = dpaa2_chan->qdma;
	अचिन्हित दीर्घ flags;

	LIST_HEAD(head);

	spin_lock_irqsave(&dpaa2_chan->vchan.lock, flags);
	vchan_get_all_descriptors(&dpaa2_chan->vchan, &head);
	spin_unlock_irqrestore(&dpaa2_chan->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&dpaa2_chan->vchan, &head);

	dpaa2_dpdmai_मुक्त_comp(dpaa2_chan, &dpaa2_chan->comp_used);
	dpaa2_dpdmai_मुक्त_comp(dpaa2_chan, &dpaa2_chan->comp_मुक्त);

	dma_pool_destroy(dpaa2_chan->fd_pool);
	dma_pool_destroy(dpaa2_chan->fl_pool);
	dma_pool_destroy(dpaa2_chan->sdd_pool);
	dpaa2_qdma->desc_allocated--;
पूर्ण

/*
 * Request a command descriptor क्रम enqueue.
 */
अटल काष्ठा dpaa2_qdma_comp *
dpaa2_qdma_request_desc(काष्ठा dpaa2_qdma_chan *dpaa2_chan)
अणु
	काष्ठा dpaa2_qdma_priv *qdma_priv = dpaa2_chan->qdma->priv;
	काष्ठा device *dev = &qdma_priv->dpdmai_dev->dev;
	काष्ठा dpaa2_qdma_comp *comp_temp = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dpaa2_chan->queue_lock, flags);
	अगर (list_empty(&dpaa2_chan->comp_मुक्त)) अणु
		spin_unlock_irqrestore(&dpaa2_chan->queue_lock, flags);
		comp_temp = kzalloc(माप(*comp_temp), GFP_NOWAIT);
		अगर (!comp_temp)
			जाओ err;
		comp_temp->fd_virt_addr =
			dma_pool_alloc(dpaa2_chan->fd_pool, GFP_NOWAIT,
				       &comp_temp->fd_bus_addr);
		अगर (!comp_temp->fd_virt_addr)
			जाओ err_comp;

		comp_temp->fl_virt_addr =
			dma_pool_alloc(dpaa2_chan->fl_pool, GFP_NOWAIT,
				       &comp_temp->fl_bus_addr);
		अगर (!comp_temp->fl_virt_addr)
			जाओ err_fd_virt;

		comp_temp->desc_virt_addr =
			dma_pool_alloc(dpaa2_chan->sdd_pool, GFP_NOWAIT,
				       &comp_temp->desc_bus_addr);
		अगर (!comp_temp->desc_virt_addr)
			जाओ err_fl_virt;

		comp_temp->qchan = dpaa2_chan;
		वापस comp_temp;
	पूर्ण

	comp_temp = list_first_entry(&dpaa2_chan->comp_मुक्त,
				     काष्ठा dpaa2_qdma_comp, list);
	list_del(&comp_temp->list);
	spin_unlock_irqrestore(&dpaa2_chan->queue_lock, flags);

	comp_temp->qchan = dpaa2_chan;

	वापस comp_temp;

err_fl_virt:
		dma_pool_मुक्त(dpaa2_chan->fl_pool,
			      comp_temp->fl_virt_addr,
			      comp_temp->fl_bus_addr);
err_fd_virt:
		dma_pool_मुक्त(dpaa2_chan->fd_pool,
			      comp_temp->fd_virt_addr,
			      comp_temp->fd_bus_addr);
err_comp:
	kमुक्त(comp_temp);
err:
	dev_err(dev, "Failed to request descriptor\n");
	वापस शून्य;
पूर्ण

अटल व्योम
dpaa2_qdma_populate_fd(u32 क्रमmat, काष्ठा dpaa2_qdma_comp *dpaa2_comp)
अणु
	काष्ठा dpaa2_fd *fd;

	fd = dpaa2_comp->fd_virt_addr;
	स_रखो(fd, 0, माप(काष्ठा dpaa2_fd));

	/* fd populated */
	dpaa2_fd_set_addr(fd, dpaa2_comp->fl_bus_addr);

	/*
	 * Bypass memory translation, Frame list क्रमmat, लघु length disable
	 * we need to disable BMT अगर fsl-mc use iova addr
	 */
	अगर (smmu_disable)
		dpaa2_fd_set_bpid(fd, QMAN_FD_BMT_ENABLE);
	dpaa2_fd_set_क्रमmat(fd, QMAN_FD_FMT_ENABLE | QMAN_FD_SL_DISABLE);

	dpaa2_fd_set_frc(fd, क्रमmat | QDMA_SER_CTX);
पूर्ण

/* first frame list क्रम descriptor buffer */
अटल व्योम
dpaa2_qdma_populate_first_framel(काष्ठा dpaa2_fl_entry *f_list,
				 काष्ठा dpaa2_qdma_comp *dpaa2_comp,
				 bool wrt_changed)
अणु
	काष्ठा dpaa2_qdma_sd_d *sdd;

	sdd = dpaa2_comp->desc_virt_addr;
	स_रखो(sdd, 0, 2 * (माप(*sdd)));

	/* source descriptor CMD */
	sdd->cmd = cpu_to_le32(QDMA_SD_CMD_RDTTYPE_COHERENT);
	sdd++;

	/* dest descriptor CMD */
	अगर (wrt_changed)
		sdd->cmd = cpu_to_le32(LX2160_QDMA_DD_CMD_WRTTYPE_COHERENT);
	अन्यथा
		sdd->cmd = cpu_to_le32(QDMA_DD_CMD_WRTTYPE_COHERENT);

	स_रखो(f_list, 0, माप(काष्ठा dpaa2_fl_entry));

	/* first frame list to source descriptor */
	dpaa2_fl_set_addr(f_list, dpaa2_comp->desc_bus_addr);
	dpaa2_fl_set_len(f_list, 0x20);
	dpaa2_fl_set_क्रमmat(f_list, QDMA_FL_FMT_SBF | QDMA_FL_SL_LONG);

	/* bypass memory translation */
	अगर (smmu_disable)
		f_list->bpid = cpu_to_le16(QDMA_FL_BMT_ENABLE);
पूर्ण

/* source and destination frame list */
अटल व्योम
dpaa2_qdma_populate_frames(काष्ठा dpaa2_fl_entry *f_list,
			   dma_addr_t dst, dma_addr_t src,
			   माप_प्रकार len, uपूर्णांक8_t fmt)
अणु
	/* source frame list to source buffer */
	स_रखो(f_list, 0, माप(काष्ठा dpaa2_fl_entry));

	dpaa2_fl_set_addr(f_list, src);
	dpaa2_fl_set_len(f_list, len);

	/* single buffer frame or scatter gather frame */
	dpaa2_fl_set_क्रमmat(f_list, (fmt | QDMA_FL_SL_LONG));

	/* bypass memory translation */
	अगर (smmu_disable)
		f_list->bpid = cpu_to_le16(QDMA_FL_BMT_ENABLE);

	f_list++;

	/* destination frame list to destination buffer */
	स_रखो(f_list, 0, माप(काष्ठा dpaa2_fl_entry));

	dpaa2_fl_set_addr(f_list, dst);
	dpaa2_fl_set_len(f_list, len);
	dpaa2_fl_set_क्रमmat(f_list, (fmt | QDMA_FL_SL_LONG));
	/* single buffer frame or scatter gather frame */
	dpaa2_fl_set_final(f_list, QDMA_FL_F);
	/* bypass memory translation */
	अगर (smmu_disable)
		f_list->bpid = cpu_to_le16(QDMA_FL_BMT_ENABLE);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor
*dpaa2_qdma_prep_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst,
			dma_addr_t src, माप_प्रकार len, uदीर्घ flags)
अणु
	काष्ठा dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	काष्ठा dpaa2_qdma_engine *dpaa2_qdma;
	काष्ठा dpaa2_qdma_comp *dpaa2_comp;
	काष्ठा dpaa2_fl_entry *f_list;
	bool wrt_changed;

	dpaa2_qdma = dpaa2_chan->qdma;
	dpaa2_comp = dpaa2_qdma_request_desc(dpaa2_chan);
	अगर (!dpaa2_comp)
		वापस शून्य;

	wrt_changed = (bool)dpaa2_qdma->qdma_wrtype_fixup;

	/* populate Frame descriptor */
	dpaa2_qdma_populate_fd(QDMA_FD_LONG_FORMAT, dpaa2_comp);

	f_list = dpaa2_comp->fl_virt_addr;

	/* first frame list क्रम descriptor buffer (logn क्रमmat) */
	dpaa2_qdma_populate_first_framel(f_list, dpaa2_comp, wrt_changed);

	f_list++;

	dpaa2_qdma_populate_frames(f_list, dst, src, len, QDMA_FL_FMT_SBF);

	वापस vchan_tx_prep(&dpaa2_chan->vchan, &dpaa2_comp->vdesc, flags);
पूर्ण

अटल व्योम dpaa2_qdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	काष्ठा dpaa2_qdma_comp *dpaa2_comp;
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा dpaa2_fd *fd;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	spin_lock_irqsave(&dpaa2_chan->queue_lock, flags);
	spin_lock(&dpaa2_chan->vchan.lock);
	अगर (vchan_issue_pending(&dpaa2_chan->vchan)) अणु
		vdesc = vchan_next_desc(&dpaa2_chan->vchan);
		अगर (!vdesc)
			जाओ err_enqueue;
		dpaa2_comp = to_fsl_qdma_comp(vdesc);

		fd = dpaa2_comp->fd_virt_addr;

		list_del(&vdesc->node);
		list_add_tail(&dpaa2_comp->list, &dpaa2_chan->comp_used);

		err = dpaa2_io_service_enqueue_fq(शून्य, dpaa2_chan->fqid, fd);
		अगर (err) अणु
			list_del(&dpaa2_comp->list);
			list_add_tail(&dpaa2_comp->list,
				      &dpaa2_chan->comp_मुक्त);
		पूर्ण
	पूर्ण
err_enqueue:
	spin_unlock(&dpaa2_chan->vchan.lock);
	spin_unlock_irqrestore(&dpaa2_chan->queue_lock, flags);
पूर्ण

अटल पूर्णांक __cold dpaa2_qdma_setup(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv;
	काष्ठा device *dev = &ls_dev->dev;
	काष्ठा dpaa2_qdma_priv *priv;
	u8 prio_def = DPDMAI_PRIO_NUM;
	पूर्णांक err = -EINVAL;
	पूर्णांक i;

	priv = dev_get_drvdata(dev);

	priv->dev = dev;
	priv->dpqdma_id = ls_dev->obj_desc.id;

	/* Get the handle क्रम the DPDMAI this पूर्णांकerface is associate with */
	err = dpdmai_खोलो(priv->mc_io, 0, priv->dpqdma_id, &ls_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpdmai_open() failed\n");
		वापस err;
	पूर्ण

	dev_dbg(dev, "Opened dpdmai object successfully\n");

	err = dpdmai_get_attributes(priv->mc_io, 0, ls_dev->mc_handle,
				    &priv->dpdmai_attr);
	अगर (err) अणु
		dev_err(dev, "dpdmai_get_attributes() failed\n");
		जाओ निकास;
	पूर्ण

	अगर (priv->dpdmai_attr.version.major > DPDMAI_VER_MAJOR) अणु
		err = -EINVAL;
		dev_err(dev, "DPDMAI major version mismatch\n"
			     "Found %u.%u, supported version is %u.%u\n",
				priv->dpdmai_attr.version.major,
				priv->dpdmai_attr.version.minor,
				DPDMAI_VER_MAJOR, DPDMAI_VER_MINOR);
		जाओ निकास;
	पूर्ण

	अगर (priv->dpdmai_attr.version.minor > DPDMAI_VER_MINOR) अणु
		err = -EINVAL;
		dev_err(dev, "DPDMAI minor version mismatch\n"
			     "Found %u.%u, supported version is %u.%u\n",
				priv->dpdmai_attr.version.major,
				priv->dpdmai_attr.version.minor,
				DPDMAI_VER_MAJOR, DPDMAI_VER_MINOR);
		जाओ निकास;
	पूर्ण

	priv->num_pairs = min(priv->dpdmai_attr.num_of_priorities, prio_def);
	ppriv = kसुस्मृति(priv->num_pairs, माप(*ppriv), GFP_KERNEL);
	अगर (!ppriv) अणु
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	priv->ppriv = ppriv;

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		err = dpdmai_get_rx_queue(priv->mc_io, 0, ls_dev->mc_handle,
					  i, &priv->rx_queue_attr[i]);
		अगर (err) अणु
			dev_err(dev, "dpdmai_get_rx_queue() failed\n");
			जाओ निकास;
		पूर्ण
		ppriv->rsp_fqid = priv->rx_queue_attr[i].fqid;

		err = dpdmai_get_tx_queue(priv->mc_io, 0, ls_dev->mc_handle,
					  i, &priv->tx_fqid[i]);
		अगर (err) अणु
			dev_err(dev, "dpdmai_get_tx_queue() failed\n");
			जाओ निकास;
		पूर्ण
		ppriv->req_fqid = priv->tx_fqid[i];
		ppriv->prio = i;
		ppriv->priv = priv;
		ppriv++;
	पूर्ण

	वापस 0;
निकास:
	dpdmai_बंद(priv->mc_io, 0, ls_dev->mc_handle);
	वापस err;
पूर्ण

अटल व्योम dpaa2_qdma_fqdan_cb(काष्ठा dpaa2_io_notअगरication_ctx *ctx)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv = container_of(ctx,
			काष्ठा dpaa2_qdma_priv_per_prio, nctx);
	काष्ठा dpaa2_qdma_comp *dpaa2_comp, *_comp_पंचांगp;
	काष्ठा dpaa2_qdma_priv *priv = ppriv->priv;
	u32 n_chans = priv->dpaa2_qdma->n_chans;
	काष्ठा dpaa2_qdma_chan *qchan;
	स्थिर काष्ठा dpaa2_fd *fd_eq;
	स्थिर काष्ठा dpaa2_fd *fd;
	काष्ठा dpaa2_dq *dq;
	पूर्णांक is_last = 0;
	पूर्णांक found;
	u8 status;
	पूर्णांक err;
	पूर्णांक i;

	करो अणु
		err = dpaa2_io_service_pull_fq(शून्य, ppriv->rsp_fqid,
					       ppriv->store);
	पूर्ण जबतक (err);

	जबतक (!is_last) अणु
		करो अणु
			dq = dpaa2_io_store_next(ppriv->store, &is_last);
		पूर्ण जबतक (!is_last && !dq);
		अगर (!dq) अणु
			dev_err(priv->dev, "FQID returned no valid frames!\n");
			जारी;
		पूर्ण

		/* obtain FD and process the error */
		fd = dpaa2_dq_fd(dq);

		status = dpaa2_fd_get_ctrl(fd) & 0xff;
		अगर (status)
			dev_err(priv->dev, "FD error occurred\n");
		found = 0;
		क्रम (i = 0; i < n_chans; i++) अणु
			qchan = &priv->dpaa2_qdma->chans[i];
			spin_lock(&qchan->queue_lock);
			अगर (list_empty(&qchan->comp_used)) अणु
				spin_unlock(&qchan->queue_lock);
				जारी;
			पूर्ण
			list_क्रम_each_entry_safe(dpaa2_comp, _comp_पंचांगp,
						 &qchan->comp_used, list) अणु
				fd_eq = dpaa2_comp->fd_virt_addr;

				अगर (le64_to_cpu(fd_eq->simple.addr) ==
				    le64_to_cpu(fd->simple.addr)) अणु
					spin_lock(&qchan->vchan.lock);
					vchan_cookie_complete(&
							dpaa2_comp->vdesc);
					spin_unlock(&qchan->vchan.lock);
					found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock(&qchan->queue_lock);
			अगर (found)
				अवरोध;
		पूर्ण
	पूर्ण

	dpaa2_io_service_rearm(शून्य, ctx);
पूर्ण

अटल पूर्णांक __cold dpaa2_qdma_dpio_setup(काष्ठा dpaa2_qdma_priv *priv)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv;
	काष्ठा device *dev = priv->dev;
	पूर्णांक err = -EINVAL;
	पूर्णांक i, num;

	num = priv->num_pairs;
	ppriv = priv->ppriv;
	क्रम (i = 0; i < num; i++) अणु
		ppriv->nctx.is_cdan = 0;
		ppriv->nctx.desired_cpu = DPAA2_IO_ANY_CPU;
		ppriv->nctx.id = ppriv->rsp_fqid;
		ppriv->nctx.cb = dpaa2_qdma_fqdan_cb;
		err = dpaa2_io_service_रेजिस्टर(शून्य, &ppriv->nctx, dev);
		अगर (err) अणु
			dev_err(dev, "Notification register failed\n");
			जाओ err_service;
		पूर्ण

		ppriv->store =
			dpaa2_io_store_create(DPAA2_QDMA_STORE_SIZE, dev);
		अगर (!ppriv->store) अणु
			err = -ENOMEM;
			dev_err(dev, "dpaa2_io_store_create() failed\n");
			जाओ err_store;
		पूर्ण

		ppriv++;
	पूर्ण
	वापस 0;

err_store:
	dpaa2_io_service_deरेजिस्टर(शून्य, &ppriv->nctx, dev);
err_service:
	ppriv--;
	जबतक (ppriv >= priv->ppriv) अणु
		dpaa2_io_service_deरेजिस्टर(शून्य, &ppriv->nctx, dev);
		dpaa2_io_store_destroy(ppriv->store);
		ppriv--;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम dpaa2_dpmai_store_मुक्त(काष्ठा dpaa2_qdma_priv *priv)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv = priv->ppriv;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		dpaa2_io_store_destroy(ppriv->store);
		ppriv++;
	पूर्ण
पूर्ण

अटल व्योम dpaa2_dpdmai_dpio_मुक्त(काष्ठा dpaa2_qdma_priv *priv)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv = priv->ppriv;
	काष्ठा device *dev = priv->dev;
	पूर्णांक i;

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		dpaa2_io_service_deरेजिस्टर(शून्य, &ppriv->nctx, dev);
		ppriv++;
	पूर्ण
पूर्ण

अटल पूर्णांक __cold dpaa2_dpdmai_bind(काष्ठा dpaa2_qdma_priv *priv)
अणु
	काष्ठा dpdmai_rx_queue_cfg rx_queue_cfg;
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv;
	काष्ठा device *dev = priv->dev;
	काष्ठा fsl_mc_device *ls_dev;
	पूर्णांक i, num;
	पूर्णांक err;

	ls_dev = to_fsl_mc_device(dev);
	num = priv->num_pairs;
	ppriv = priv->ppriv;
	क्रम (i = 0; i < num; i++) अणु
		rx_queue_cfg.options = DPDMAI_QUEUE_OPT_USER_CTX |
					DPDMAI_QUEUE_OPT_DEST;
		rx_queue_cfg.user_ctx = ppriv->nctx.qman64;
		rx_queue_cfg.dest_cfg.dest_type = DPDMAI_DEST_DPIO;
		rx_queue_cfg.dest_cfg.dest_id = ppriv->nctx.dpio_id;
		rx_queue_cfg.dest_cfg.priority = ppriv->prio;
		err = dpdmai_set_rx_queue(priv->mc_io, 0, ls_dev->mc_handle,
					  rx_queue_cfg.dest_cfg.priority,
					  &rx_queue_cfg);
		अगर (err) अणु
			dev_err(dev, "dpdmai_set_rx_queue() failed\n");
			वापस err;
		पूर्ण

		ppriv++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __cold dpaa2_dpdmai_dpio_unbind(काष्ठा dpaa2_qdma_priv *priv)
अणु
	काष्ठा dpaa2_qdma_priv_per_prio *ppriv = priv->ppriv;
	काष्ठा device *dev = priv->dev;
	काष्ठा fsl_mc_device *ls_dev;
	पूर्णांक err = 0;
	पूर्णांक i;

	ls_dev = to_fsl_mc_device(dev);

	क्रम (i = 0; i < priv->num_pairs; i++) अणु
		ppriv->nctx.qman64 = 0;
		ppriv->nctx.dpio_id = 0;
		ppriv++;
	पूर्ण

	err = dpdmai_reset(priv->mc_io, 0, ls_dev->mc_handle);
	अगर (err)
		dev_err(dev, "dpdmai_reset() failed\n");

	वापस err;
पूर्ण

अटल व्योम dpaa2_dpdmai_मुक्त_comp(काष्ठा dpaa2_qdma_chan *qchan,
				   काष्ठा list_head *head)
अणु
	काष्ठा dpaa2_qdma_comp *comp_पंचांगp, *_comp_पंचांगp;
	अचिन्हित दीर्घ flags;

	list_क्रम_each_entry_safe(comp_पंचांगp, _comp_पंचांगp,
				 head, list) अणु
		spin_lock_irqsave(&qchan->queue_lock, flags);
		list_del(&comp_पंचांगp->list);
		spin_unlock_irqrestore(&qchan->queue_lock, flags);
		dma_pool_मुक्त(qchan->fd_pool,
			      comp_पंचांगp->fd_virt_addr,
			      comp_पंचांगp->fd_bus_addr);
		dma_pool_मुक्त(qchan->fl_pool,
			      comp_पंचांगp->fl_virt_addr,
			      comp_पंचांगp->fl_bus_addr);
		dma_pool_मुक्त(qchan->sdd_pool,
			      comp_पंचांगp->desc_virt_addr,
			      comp_पंचांगp->desc_bus_addr);
		kमुक्त(comp_पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम dpaa2_dpdmai_मुक्त_channels(काष्ठा dpaa2_qdma_engine *dpaa2_qdma)
अणु
	काष्ठा dpaa2_qdma_chan *qchan;
	पूर्णांक num, i;

	num = dpaa2_qdma->n_chans;
	क्रम (i = 0; i < num; i++) अणु
		qchan = &dpaa2_qdma->chans[i];
		dpaa2_dpdmai_मुक्त_comp(qchan, &qchan->comp_used);
		dpaa2_dpdmai_मुक्त_comp(qchan, &qchan->comp_मुक्त);
		dma_pool_destroy(qchan->fd_pool);
		dma_pool_destroy(qchan->fl_pool);
		dma_pool_destroy(qchan->sdd_pool);
	पूर्ण
पूर्ण

अटल व्योम dpaa2_qdma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा dpaa2_qdma_comp *dpaa2_comp;
	काष्ठा dpaa2_qdma_chan *qchan;
	अचिन्हित दीर्घ flags;

	dpaa2_comp = to_fsl_qdma_comp(vdesc);
	qchan = dpaa2_comp->qchan;
	spin_lock_irqsave(&qchan->queue_lock, flags);
	list_del(&dpaa2_comp->list);
	list_add_tail(&dpaa2_comp->list, &qchan->comp_मुक्त);
	spin_unlock_irqrestore(&qchan->queue_lock, flags);
पूर्ण

अटल पूर्णांक dpaa2_dpdmai_init_channels(काष्ठा dpaa2_qdma_engine *dpaa2_qdma)
अणु
	काष्ठा dpaa2_qdma_priv *priv = dpaa2_qdma->priv;
	काष्ठा dpaa2_qdma_chan *dpaa2_chan;
	पूर्णांक num = priv->num_pairs;
	पूर्णांक i;

	INIT_LIST_HEAD(&dpaa2_qdma->dma_dev.channels);
	क्रम (i = 0; i < dpaa2_qdma->n_chans; i++) अणु
		dpaa2_chan = &dpaa2_qdma->chans[i];
		dpaa2_chan->qdma = dpaa2_qdma;
		dpaa2_chan->fqid = priv->tx_fqid[i % num];
		dpaa2_chan->vchan.desc_मुक्त = dpaa2_qdma_मुक्त_desc;
		vchan_init(&dpaa2_chan->vchan, &dpaa2_qdma->dma_dev);
		spin_lock_init(&dpaa2_chan->queue_lock);
		INIT_LIST_HEAD(&dpaa2_chan->comp_used);
		INIT_LIST_HEAD(&dpaa2_chan->comp_मुक्त);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dpaa2_qdma_probe(काष्ठा fsl_mc_device *dpdmai_dev)
अणु
	काष्ठा device *dev = &dpdmai_dev->dev;
	काष्ठा dpaa2_qdma_engine *dpaa2_qdma;
	काष्ठा dpaa2_qdma_priv *priv;
	पूर्णांक err;

	priv = kzalloc(माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	dev_set_drvdata(dev, priv);
	priv->dpdmai_dev = dpdmai_dev;

	priv->iommu_करोमुख्य = iommu_get_करोमुख्य_क्रम_dev(dev);
	अगर (priv->iommu_करोमुख्य)
		smmu_disable = false;

	/* obtain a MC portal */
	err = fsl_mc_portal_allocate(dpdmai_dev, 0, &priv->mc_io);
	अगर (err) अणु
		अगर (err == -ENXIO)
			err = -EPROBE_DEFER;
		अन्यथा
			dev_err(dev, "MC portal allocation failed\n");
		जाओ err_mcportal;
	पूर्ण

	/* DPDMAI initialization */
	err = dpaa2_qdma_setup(dpdmai_dev);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpdmai_setup() failed\n");
		जाओ err_dpdmai_setup;
	पूर्ण

	/* DPIO */
	err = dpaa2_qdma_dpio_setup(priv);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpdmai_dpio_setup() failed\n");
		जाओ err_dpio_setup;
	पूर्ण

	/* DPDMAI binding to DPIO */
	err = dpaa2_dpdmai_bind(priv);
	अगर (err) अणु
		dev_err(dev, "dpaa2_dpdmai_bind() failed\n");
		जाओ err_bind;
	पूर्ण

	/* DPDMAI enable */
	err = dpdmai_enable(priv->mc_io, 0, dpdmai_dev->mc_handle);
	अगर (err) अणु
		dev_err(dev, "dpdmai_enable() faile\n");
		जाओ err_enable;
	पूर्ण

	dpaa2_qdma = kzalloc(माप(*dpaa2_qdma), GFP_KERNEL);
	अगर (!dpaa2_qdma) अणु
		err = -ENOMEM;
		जाओ err_eng;
	पूर्ण

	priv->dpaa2_qdma = dpaa2_qdma;
	dpaa2_qdma->priv = priv;

	dpaa2_qdma->desc_allocated = 0;
	dpaa2_qdma->n_chans = NUM_CH;

	dpaa2_dpdmai_init_channels(dpaa2_qdma);

	अगर (soc_device_match(soc_fixup_tuning))
		dpaa2_qdma->qdma_wrtype_fixup = true;
	अन्यथा
		dpaa2_qdma->qdma_wrtype_fixup = false;

	dma_cap_set(DMA_PRIVATE, dpaa2_qdma->dma_dev.cap_mask);
	dma_cap_set(DMA_SLAVE, dpaa2_qdma->dma_dev.cap_mask);
	dma_cap_set(DMA_MEMCPY, dpaa2_qdma->dma_dev.cap_mask);

	dpaa2_qdma->dma_dev.dev = dev;
	dpaa2_qdma->dma_dev.device_alloc_chan_resources =
		dpaa2_qdma_alloc_chan_resources;
	dpaa2_qdma->dma_dev.device_मुक्त_chan_resources =
		dpaa2_qdma_मुक्त_chan_resources;
	dpaa2_qdma->dma_dev.device_tx_status = dma_cookie_status;
	dpaa2_qdma->dma_dev.device_prep_dma_स_नकल = dpaa2_qdma_prep_स_नकल;
	dpaa2_qdma->dma_dev.device_issue_pending = dpaa2_qdma_issue_pending;

	err = dma_async_device_रेजिस्टर(&dpaa2_qdma->dma_dev);
	अगर (err) अणु
		dev_err(dev, "Can't register NXP QDMA engine.\n");
		जाओ err_dpaa2_qdma;
	पूर्ण

	वापस 0;

err_dpaa2_qdma:
	kमुक्त(dpaa2_qdma);
err_eng:
	dpdmai_disable(priv->mc_io, 0, dpdmai_dev->mc_handle);
err_enable:
	dpaa2_dpdmai_dpio_unbind(priv);
err_bind:
	dpaa2_dpmai_store_मुक्त(priv);
	dpaa2_dpdmai_dpio_मुक्त(priv);
err_dpio_setup:
	kमुक्त(priv->ppriv);
	dpdmai_बंद(priv->mc_io, 0, dpdmai_dev->mc_handle);
err_dpdmai_setup:
	fsl_mc_portal_मुक्त(priv->mc_io);
err_mcportal:
	kमुक्त(priv);
	dev_set_drvdata(dev, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक dpaa2_qdma_हटाओ(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा dpaa2_qdma_engine *dpaa2_qdma;
	काष्ठा dpaa2_qdma_priv *priv;
	काष्ठा device *dev;

	dev = &ls_dev->dev;
	priv = dev_get_drvdata(dev);
	dpaa2_qdma = priv->dpaa2_qdma;

	dpdmai_disable(priv->mc_io, 0, ls_dev->mc_handle);
	dpaa2_dpdmai_dpio_unbind(priv);
	dpaa2_dpmai_store_मुक्त(priv);
	dpaa2_dpdmai_dpio_मुक्त(priv);
	dpdmai_बंद(priv->mc_io, 0, ls_dev->mc_handle);
	fsl_mc_portal_मुक्त(priv->mc_io);
	dev_set_drvdata(dev, शून्य);
	dpaa2_dpdmai_मुक्त_channels(dpaa2_qdma);

	dma_async_device_unरेजिस्टर(&dpaa2_qdma->dma_dev);
	kमुक्त(priv);
	kमुक्त(dpaa2_qdma);

	वापस 0;
पूर्ण

अटल व्योम dpaa2_qdma_shutकरोwn(काष्ठा fsl_mc_device *ls_dev)
अणु
	काष्ठा dpaa2_qdma_priv *priv;
	काष्ठा device *dev;

	dev = &ls_dev->dev;
	priv = dev_get_drvdata(dev);

	dpdmai_disable(priv->mc_io, 0, ls_dev->mc_handle);
	dpaa2_dpdmai_dpio_unbind(priv);
	dpdmai_बंद(priv->mc_io, 0, ls_dev->mc_handle);
	dpdmai_destroy(priv->mc_io, 0, ls_dev->mc_handle);
पूर्ण

अटल स्थिर काष्ठा fsl_mc_device_id dpaa2_qdma_id_table[] = अणु
	अणु
		.venकरोr = FSL_MC_VENDOR_FREESCALE,
		.obj_type = "dpdmai",
	पूर्ण,
	अणु .venकरोr = 0x0 पूर्ण
पूर्ण;

अटल काष्ठा fsl_mc_driver dpaa2_qdma_driver = अणु
	.driver		= अणु
		.name	= "dpaa2-qdma",
		.owner  = THIS_MODULE,
	पूर्ण,
	.probe          = dpaa2_qdma_probe,
	.हटाओ		= dpaa2_qdma_हटाओ,
	.shutकरोwn	= dpaa2_qdma_shutकरोwn,
	.match_id_table	= dpaa2_qdma_id_table
पूर्ण;

अटल पूर्णांक __init dpaa2_qdma_driver_init(व्योम)
अणु
	वापस fsl_mc_driver_रेजिस्टर(&(dpaa2_qdma_driver));
पूर्ण
late_initcall(dpaa2_qdma_driver_init);

अटल व्योम __निकास fsl_qdma_निकास(व्योम)
अणु
	fsl_mc_driver_unरेजिस्टर(&(dpaa2_qdma_driver));
पूर्ण
module_निकास(fsl_qdma_निकास);

MODULE_ALIAS("platform:fsl-dpaa2-qdma");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("NXP Layerscape DPAA2 qDMA engine driver");
