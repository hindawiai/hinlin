<शैली गुरु>
/*
 * Copyright (c) 2004 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005 Sun Microप्रणालीs, Inc. All rights reserved.
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
#समावेश <linux/slab.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>

#समावेश "mthca_dev.h"

क्रमागत अणु
      MTHCA_RATE_TAVOR_FULL   = 0,
      MTHCA_RATE_TAVOR_1X     = 1,
      MTHCA_RATE_TAVOR_4X     = 2,
      MTHCA_RATE_TAVOR_1X_DDR = 3
पूर्ण;

क्रमागत अणु
      MTHCA_RATE_MEMFREE_FULL    = 0,
      MTHCA_RATE_MEMFREE_QUARTER = 1,
      MTHCA_RATE_MEMFREE_EIGHTH  = 2,
      MTHCA_RATE_MEMFREE_HALF    = 3
पूर्ण;

काष्ठा mthca_av अणु
	__be32 port_pd;
	u8     reserved1;
	u8     g_slid;
	__be16 dlid;
	u8     reserved2;
	u8     gid_index;
	u8     msg_sr;
	u8     hop_limit;
	__be32 sl_tclass_flowlabel;
	__be32 dgid[4];
पूर्ण;

अटल क्रमागत ib_rate memमुक्त_rate_to_ib(u8 mthca_rate, u8 port_rate)
अणु
	चयन (mthca_rate) अणु
	हाल MTHCA_RATE_MEMFREE_EIGHTH:
		वापस mult_to_ib_rate(port_rate >> 3);
	हाल MTHCA_RATE_MEMFREE_QUARTER:
		वापस mult_to_ib_rate(port_rate >> 2);
	हाल MTHCA_RATE_MEMFREE_HALF:
		वापस mult_to_ib_rate(port_rate >> 1);
	हाल MTHCA_RATE_MEMFREE_FULL:
	शेष:
		वापस mult_to_ib_rate(port_rate);
	पूर्ण
पूर्ण

अटल क्रमागत ib_rate tavor_rate_to_ib(u8 mthca_rate, u8 port_rate)
अणु
	चयन (mthca_rate) अणु
	हाल MTHCA_RATE_TAVOR_1X:     वापस IB_RATE_2_5_GBPS;
	हाल MTHCA_RATE_TAVOR_1X_DDR: वापस IB_RATE_5_GBPS;
	हाल MTHCA_RATE_TAVOR_4X:     वापस IB_RATE_10_GBPS;
	शेष:		      वापस mult_to_ib_rate(port_rate);
	पूर्ण
पूर्ण

क्रमागत ib_rate mthca_rate_to_ib(काष्ठा mthca_dev *dev, u8 mthca_rate, u32 port)
अणु
	अगर (mthca_is_memमुक्त(dev)) अणु
		/* Handle old Arbel FW */
		अगर (dev->limits.stat_rate_support == 0x3 && mthca_rate)
			वापस IB_RATE_2_5_GBPS;

		वापस memमुक्त_rate_to_ib(mthca_rate, dev->rate[port - 1]);
	पूर्ण अन्यथा
		वापस tavor_rate_to_ib(mthca_rate, dev->rate[port - 1]);
पूर्ण

अटल u8 ib_rate_to_memमुक्त(u8 req_rate, u8 cur_rate)
अणु
	अगर (cur_rate <= req_rate)
		वापस 0;

	/*
	 * Inter-packet delay (IPD) to get from rate X करोwn to a rate
	 * no more than Y is (X - 1) / Y.
	 */
	चयन ((cur_rate - 1) / req_rate) अणु
	हाल 0:	 वापस MTHCA_RATE_MEMFREE_FULL;
	हाल 1:	 वापस MTHCA_RATE_MEMFREE_HALF;
	हाल 2:
	हाल 3:	 वापस MTHCA_RATE_MEMFREE_QUARTER;
	शेष: वापस MTHCA_RATE_MEMFREE_EIGHTH;
	पूर्ण
पूर्ण

अटल u8 ib_rate_to_tavor(u8 अटल_rate)
अणु
	चयन (अटल_rate) अणु
	हाल IB_RATE_2_5_GBPS: वापस MTHCA_RATE_TAVOR_1X;
	हाल IB_RATE_5_GBPS:   वापस MTHCA_RATE_TAVOR_1X_DDR;
	हाल IB_RATE_10_GBPS:  वापस MTHCA_RATE_TAVOR_4X;
	शेष:	       वापस MTHCA_RATE_TAVOR_FULL;
	पूर्ण
पूर्ण

u8 mthca_get_rate(काष्ठा mthca_dev *dev, पूर्णांक अटल_rate, u32 port)
अणु
	u8 rate;

	अगर (!अटल_rate || ib_rate_to_mult(अटल_rate) >= dev->rate[port - 1])
		वापस 0;

	अगर (mthca_is_memमुक्त(dev))
		rate = ib_rate_to_memमुक्त(ib_rate_to_mult(अटल_rate),
					  dev->rate[port - 1]);
	अन्यथा
		rate = ib_rate_to_tavor(अटल_rate);

	अगर (!(dev->limits.stat_rate_support & (1 << rate)))
		rate = 1;

	वापस rate;
पूर्ण

पूर्णांक mthca_create_ah(काष्ठा mthca_dev *dev,
		    काष्ठा mthca_pd *pd,
		    काष्ठा rdma_ah_attr *ah_attr,
		    काष्ठा mthca_ah *ah)
अणु
	u32 index = -1;
	काष्ठा mthca_av *av = शून्य;

	ah->type = MTHCA_AH_PCI_POOL;

	अगर (mthca_is_memमुक्त(dev)) अणु
		ah->av   = kदो_स्मृति(माप *ah->av, GFP_ATOMIC);
		अगर (!ah->av)
			वापस -ENOMEM;

		ah->type = MTHCA_AH_KMALLOC;
		av       = ah->av;
	पूर्ण अन्यथा अगर (!atomic_पढ़ो(&pd->sqp_count) &&
		 !(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) अणु
		index = mthca_alloc(&dev->av_table.alloc);

		/* fall back to allocate in host memory */
		अगर (index == -1)
			जाओ on_hca_fail;

		av = kदो_स्मृति(माप *av, GFP_ATOMIC);
		अगर (!av)
			जाओ on_hca_fail;

		ah->type = MTHCA_AH_ON_HCA;
		ah->avdma  = dev->av_table.ddr_av_base +
			index * MTHCA_AV_SIZE;
	पूर्ण

on_hca_fail:
	अगर (ah->type == MTHCA_AH_PCI_POOL) अणु
		ah->av = dma_pool_zalloc(dev->av_table.pool,
					 GFP_ATOMIC, &ah->avdma);
		अगर (!ah->av)
			वापस -ENOMEM;

		av = ah->av;
	पूर्ण

	ah->key = pd->nपंचांगr.ibmr.lkey;

	av->port_pd = cpu_to_be32(pd->pd_num |
				  (rdma_ah_get_port_num(ah_attr) << 24));
	av->g_slid  = rdma_ah_get_path_bits(ah_attr);
	av->dlid    = cpu_to_be16(rdma_ah_get_dlid(ah_attr));
	av->msg_sr  = (3 << 4) | /* 2K message */
		mthca_get_rate(dev, rdma_ah_get_अटल_rate(ah_attr),
			       rdma_ah_get_port_num(ah_attr));
	av->sl_tclass_flowlabel = cpu_to_be32(rdma_ah_get_sl(ah_attr) << 28);
	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		स्थिर काष्ठा ib_global_route *grh = rdma_ah_पढ़ो_grh(ah_attr);

		av->g_slid |= 0x80;
		av->gid_index = (rdma_ah_get_port_num(ah_attr) - 1) *
				  dev->limits.gid_table_len +
				  grh->sgid_index;
		av->hop_limit = grh->hop_limit;
		av->sl_tclass_flowlabel |=
			cpu_to_be32((grh->traffic_class << 20) |
				    grh->flow_label);
		स_नकल(av->dgid, grh->dgid.raw, 16);
	पूर्ण अन्यथा अणु
		/* Arbel workaround -- low byte of GID must be 2 */
		av->dgid[3] = cpu_to_be32(2);
	पूर्ण

	अगर (0) अणु
		पूर्णांक j;

		mthca_dbg(dev, "Created UDAV at %p/%08lx:\n",
			  av, (अचिन्हित दीर्घ) ah->avdma);
		क्रम (j = 0; j < 8; ++j)
			prपूर्णांकk(KERN_DEBUG "  [%2x] %08x\n",
			       j * 4, be32_to_cpu(((__be32 *) av)[j]));
	पूर्ण

	अगर (ah->type == MTHCA_AH_ON_HCA) अणु
		स_नकल_toio(dev->av_table.av_map + index * MTHCA_AV_SIZE,
			    av, MTHCA_AV_SIZE);
		kमुक्त(av);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mthca_destroy_ah(काष्ठा mthca_dev *dev, काष्ठा mthca_ah *ah)
अणु
	चयन (ah->type) अणु
	हाल MTHCA_AH_ON_HCA:
		mthca_मुक्त(&dev->av_table.alloc,
			   (ah->avdma - dev->av_table.ddr_av_base) /
			   MTHCA_AV_SIZE);
		अवरोध;

	हाल MTHCA_AH_PCI_POOL:
		dma_pool_मुक्त(dev->av_table.pool, ah->av, ah->avdma);
		अवरोध;

	हाल MTHCA_AH_KMALLOC:
		kमुक्त(ah->av);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mthca_ah_grh_present(काष्ठा mthca_ah *ah)
अणु
	वापस !!(ah->av->g_slid & 0x80);
पूर्ण

पूर्णांक mthca_पढ़ो_ah(काष्ठा mthca_dev *dev, काष्ठा mthca_ah *ah,
		  काष्ठा ib_ud_header *header)
अणु
	अगर (ah->type == MTHCA_AH_ON_HCA)
		वापस -EINVAL;

	header->lrh.service_level   = be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 28;
	header->lrh.destination_lid = ah->av->dlid;
	header->lrh.source_lid      = cpu_to_be16(ah->av->g_slid & 0x7f);
	अगर (mthca_ah_grh_present(ah)) अणु
		header->grh.traffic_class =
			(be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 20) & 0xff;
		header->grh.flow_label    =
			ah->av->sl_tclass_flowlabel & cpu_to_be32(0xfffff);
		header->grh.hop_limit     = ah->av->hop_limit;
		header->grh.source_gid = ah->ibah.sgid_attr->gid;
		स_नकल(header->grh.destination_gid.raw,
		       ah->av->dgid, 16);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mthca_ah_query(काष्ठा ib_ah *ibah, काष्ठा rdma_ah_attr *attr)
अणु
	काष्ठा mthca_ah *ah   = to_mah(ibah);
	काष्ठा mthca_dev *dev = to_mdev(ibah->device);
	u32 port_num = be32_to_cpu(ah->av->port_pd) >> 24;

	/* Only implement क्रम MAD and memमुक्त ah क्रम now. */
	अगर (ah->type == MTHCA_AH_ON_HCA)
		वापस -ENOSYS;

	स_रखो(attr, 0, माप *attr);
	attr->type = ibah->type;
	rdma_ah_set_dlid(attr, be16_to_cpu(ah->av->dlid));
	rdma_ah_set_sl(attr, be32_to_cpu(ah->av->sl_tclass_flowlabel) >> 28);
	rdma_ah_set_port_num(attr, port_num);
	rdma_ah_set_अटल_rate(attr,
				mthca_rate_to_ib(dev, ah->av->msg_sr & 0x7,
						 port_num));
	rdma_ah_set_path_bits(attr, ah->av->g_slid & 0x7F);
	अगर (mthca_ah_grh_present(ah)) अणु
		u32 tc_fl = be32_to_cpu(ah->av->sl_tclass_flowlabel);

		rdma_ah_set_grh(attr, शून्य,
				tc_fl & 0xfffff,
				ah->av->gid_index &
				(dev->limits.gid_table_len - 1),
				ah->av->hop_limit,
				(tc_fl >> 20) & 0xff);
		rdma_ah_set_dgid_raw(attr, ah->av->dgid);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mthca_init_av_table(काष्ठा mthca_dev *dev)
अणु
	पूर्णांक err;

	अगर (mthca_is_memमुक्त(dev))
		वापस 0;

	err = mthca_alloc_init(&dev->av_table.alloc,
			       dev->av_table.num_ddr_avs,
			       dev->av_table.num_ddr_avs - 1,
			       0);
	अगर (err)
		वापस err;

	dev->av_table.pool = dma_pool_create("mthca_av", &dev->pdev->dev,
					     MTHCA_AV_SIZE,
					     MTHCA_AV_SIZE, 0);
	अगर (!dev->av_table.pool)
		जाओ out_मुक्त_alloc;

	अगर (!(dev->mthca_flags & MTHCA_FLAG_DDR_HIDDEN)) अणु
		dev->av_table.av_map = ioremap(pci_resource_start(dev->pdev, 4) +
					       dev->av_table.ddr_av_base -
					       dev->ddr_start,
					       dev->av_table.num_ddr_avs *
					       MTHCA_AV_SIZE);
		अगर (!dev->av_table.av_map)
			जाओ out_मुक्त_pool;
	पूर्ण अन्यथा
		dev->av_table.av_map = शून्य;

	वापस 0;

 out_मुक्त_pool:
	dma_pool_destroy(dev->av_table.pool);

 out_मुक्त_alloc:
	mthca_alloc_cleanup(&dev->av_table.alloc);
	वापस -ENOMEM;
पूर्ण

व्योम mthca_cleanup_av_table(काष्ठा mthca_dev *dev)
अणु
	अगर (mthca_is_memमुक्त(dev))
		वापस;

	अगर (dev->av_table.av_map)
		iounmap(dev->av_table.av_map);
	dma_pool_destroy(dev->av_table.pool);
	mthca_alloc_cleanup(&dev->av_table.alloc);
पूर्ण
