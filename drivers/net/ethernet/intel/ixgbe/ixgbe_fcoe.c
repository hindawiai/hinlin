<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#समावेश "ixgbe.h"
#समावेश <linux/अगर_ether.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <generated/utsrelease.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/libfcoe.h>

/**
 * ixgbe_fcoe_clear_ddp - clear the given ddp context
 * @ddp: ptr to the ixgbe_fcoe_ddp
 *
 * Returns : none
 *
 */
अटल अंतरभूत व्योम ixgbe_fcoe_clear_ddp(काष्ठा ixgbe_fcoe_ddp *ddp)
अणु
	ddp->len = 0;
	ddp->err = 1;
	ddp->udl = शून्य;
	ddp->udp = 0UL;
	ddp->sgl = शून्य;
	ddp->sgc = 0;
पूर्ण

/**
 * ixgbe_fcoe_ddp_put - मुक्त the ddp context क्रम a given xid
 * @netdev: the corresponding net_device
 * @xid: the xid that corresponding ddp will be मुक्तd
 *
 * This is the implementation of net_device_ops.nकरो_fcoe_ddp_करोne
 * and it is expected to be called by ULD, i.e., FCP layer of libfc
 * to release the corresponding ddp context when the I/O is करोne.
 *
 * Returns : data length alपढ़ोy ddp-ed in bytes
 */
पूर्णांक ixgbe_fcoe_ddp_put(काष्ठा net_device *netdev, u16 xid)
अणु
	पूर्णांक len;
	काष्ठा ixgbe_fcoe *fcoe;
	काष्ठा ixgbe_adapter *adapter;
	काष्ठा ixgbe_fcoe_ddp *ddp;
	काष्ठा ixgbe_hw *hw;
	u32 fcbuff;

	अगर (!netdev)
		वापस 0;

	अगर (xid >= netdev->fcoe_ddp_xid)
		वापस 0;

	adapter = netdev_priv(netdev);
	fcoe = &adapter->fcoe;
	ddp = &fcoe->ddp[xid];
	अगर (!ddp->udl)
		वापस 0;

	hw = &adapter->hw;
	len = ddp->len;
	/* अगर no error then skip ddp context invalidation */
	अगर (!ddp->err)
		जाओ skip_ddpinv;

	अगर (hw->mac.type == ixgbe_mac_X550) अणु
		/* X550 करोes not require DDP FCoE lock */

		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(0, xid), 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(3, xid),
				(xid | IXGBE_FCFLTRW_WE));

		/* program FCBUFF */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(2, xid), 0);

		/* program FCDMARW */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(3, xid),
				(xid | IXGBE_FCDMARW_WE));

		/* पढ़ो FCBUFF to check context invalidated */
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(3, xid),
				(xid | IXGBE_FCDMARW_RE));
		fcbuff = IXGBE_READ_REG(hw, IXGBE_FCDDC(2, xid));
	पूर्ण अन्यथा अणु
		/* other hardware requires DDP FCoE lock */
		spin_lock_bh(&fcoe->lock);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLT, 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLTRW,
				(xid | IXGBE_FCFLTRW_WE));
		IXGBE_WRITE_REG(hw, IXGBE_FCBUFF, 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_WE));

		/* guaranteed to be invalidated after 100us */
		IXGBE_WRITE_REG(hw, IXGBE_FCDMARW,
				(xid | IXGBE_FCDMARW_RE));
		fcbuff = IXGBE_READ_REG(hw, IXGBE_FCBUFF);
		spin_unlock_bh(&fcoe->lock);
		पूर्ण

	अगर (fcbuff & IXGBE_FCBUFF_VALID)
		usleep_range(100, 150);

skip_ddpinv:
	अगर (ddp->sgl)
		dma_unmap_sg(&adapter->pdev->dev, ddp->sgl, ddp->sgc,
			     DMA_FROM_DEVICE);
	अगर (ddp->pool) अणु
		dma_pool_मुक्त(ddp->pool, ddp->udl, ddp->udp);
		ddp->pool = शून्य;
	पूर्ण

	ixgbe_fcoe_clear_ddp(ddp);

	वापस len;
पूर्ण

/**
 * ixgbe_fcoe_ddp_setup - called to set up ddp context
 * @netdev: the corresponding net_device
 * @xid: the exchange id requesting ddp
 * @sgl: the scatter-gather list क्रम this request
 * @sgc: the number of scatter-gather items
 * @target_mode: 1 to setup target mode, 0 to setup initiator mode
 *
 * Returns : 1 क्रम success and 0 क्रम no ddp
 */
अटल पूर्णांक ixgbe_fcoe_ddp_setup(काष्ठा net_device *netdev, u16 xid,
				काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc,
				पूर्णांक target_mode)
अणु
	काष्ठा ixgbe_adapter *adapter;
	काष्ठा ixgbe_hw *hw;
	काष्ठा ixgbe_fcoe *fcoe;
	काष्ठा ixgbe_fcoe_ddp *ddp;
	काष्ठा ixgbe_fcoe_ddp_pool *ddp_pool;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i, j, dmacount;
	अचिन्हित पूर्णांक len;
	अटल स्थिर अचिन्हित पूर्णांक bufflen = IXGBE_FCBUFF_MIN;
	अचिन्हित पूर्णांक firstoff = 0;
	अचिन्हित पूर्णांक lastsize;
	अचिन्हित पूर्णांक thisoff = 0;
	अचिन्हित पूर्णांक thislen = 0;
	u32 fcbuff, fcdmarw, fcfltrw, fcrxctl;
	dma_addr_t addr = 0;

	अगर (!netdev || !sgl)
		वापस 0;

	adapter = netdev_priv(netdev);
	अगर (xid >= netdev->fcoe_ddp_xid) अणु
		e_warn(drv, "xid=0x%x out-of-range\n", xid);
		वापस 0;
	पूर्ण

	/* no DDP अगर we are alपढ़ोy करोwn or resetting */
	अगर (test_bit(__IXGBE_DOWN, &adapter->state) ||
	    test_bit(__IXGBE_RESETTING, &adapter->state))
		वापस 0;

	fcoe = &adapter->fcoe;
	ddp = &fcoe->ddp[xid];
	अगर (ddp->sgl) अणु
		e_err(drv, "xid 0x%x w/ non-null sgl=%p nents=%d\n",
		      xid, ddp->sgl, ddp->sgc);
		वापस 0;
	पूर्ण
	ixgbe_fcoe_clear_ddp(ddp);


	अगर (!fcoe->ddp_pool) अणु
		e_warn(drv, "No ddp_pool resources allocated\n");
		वापस 0;
	पूर्ण

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, get_cpu());
	अगर (!ddp_pool->pool) अणु
		e_warn(drv, "xid=0x%x no ddp pool for fcoe\n", xid);
		जाओ out_noddp;
	पूर्ण

	/* setup dma from scsi command sgl */
	dmacount = dma_map_sg(&adapter->pdev->dev, sgl, sgc, DMA_FROM_DEVICE);
	अगर (dmacount == 0) अणु
		e_err(drv, "xid 0x%x DMA map error\n", xid);
		जाओ out_noddp;
	पूर्ण

	/* alloc the udl from per cpu ddp pool */
	ddp->udl = dma_pool_alloc(ddp_pool->pool, GFP_ATOMIC, &ddp->udp);
	अगर (!ddp->udl) अणु
		e_err(drv, "failed allocated ddp context\n");
		जाओ out_noddp_unmap;
	पूर्ण
	ddp->pool = ddp_pool->pool;
	ddp->sgl = sgl;
	ddp->sgc = sgc;

	j = 0;
	क्रम_each_sg(sgl, sg, dmacount, i) अणु
		addr = sg_dma_address(sg);
		len = sg_dma_len(sg);
		जबतक (len) अणु
			/* max number of buffers allowed in one DDP context */
			अगर (j >= IXGBE_BUFFCNT_MAX) अणु
				ddp_pool->noddp++;
				जाओ out_noddp_मुक्त;
			पूर्ण

			/* get the offset of length of current buffer */
			thisoff = addr & ((dma_addr_t)bufflen - 1);
			thislen = min((bufflen - thisoff), len);
			/*
			 * all but the 1st buffer (j == 0)
			 * must be aligned on bufflen
			 */
			अगर ((j != 0) && (thisoff))
				जाओ out_noddp_मुक्त;
			/*
			 * all but the last buffer
			 * ((i == (dmacount - 1)) && (thislen == len))
			 * must end at bufflen
			 */
			अगर (((i != (dmacount - 1)) || (thislen != len))
			    && ((thislen + thisoff) != bufflen))
				जाओ out_noddp_मुक्त;

			ddp->udl[j] = (u64)(addr - thisoff);
			/* only the first buffer may have none-zero offset */
			अगर (j == 0)
				firstoff = thisoff;
			len -= thislen;
			addr += thislen;
			j++;
		पूर्ण
	पूर्ण
	/* only the last buffer may have non-full bufflen */
	lastsize = thisoff + thislen;

	/*
	 * lastsize can not be buffer len.
	 * If it is then adding another buffer with lastsize = 1.
	 */
	अगर (lastsize == bufflen) अणु
		अगर (j >= IXGBE_BUFFCNT_MAX) अणु
			ddp_pool->noddp_ext_buff++;
			जाओ out_noddp_मुक्त;
		पूर्ण

		ddp->udl[j] = (u64)(fcoe->extra_ddp_buffer_dma);
		j++;
		lastsize = 1;
	पूर्ण
	put_cpu();

	fcbuff = (IXGBE_FCBUFF_4KB << IXGBE_FCBUFF_BUFFSIZE_SHIFT);
	fcbuff |= ((j & 0xff) << IXGBE_FCBUFF_BUFFCNT_SHIFT);
	fcbuff |= (firstoff << IXGBE_FCBUFF_OFFSET_SHIFT);
	/* Set WRCONTX bit to allow DDP क्रम target */
	अगर (target_mode)
		fcbuff |= (IXGBE_FCBUFF_WRCONTX);
	fcbuff |= (IXGBE_FCBUFF_VALID);

	fcdmarw = xid;
	fcdmarw |= IXGBE_FCDMARW_WE;
	fcdmarw |= (lastsize << IXGBE_FCDMARW_LASTSIZE_SHIFT);

	fcfltrw = xid;
	fcfltrw |= IXGBE_FCFLTRW_WE;

	/* program DMA context */
	hw = &adapter->hw;

	/* turn on last frame indication क्रम target mode as FCP_RSPtarget is
	 * supposed to send FCP_RSP when it is करोne. */
	अगर (target_mode && !test_bit(__IXGBE_FCOE_TARGET, &fcoe->mode)) अणु
		set_bit(__IXGBE_FCOE_TARGET, &fcoe->mode);
		fcrxctl = IXGBE_READ_REG(hw, IXGBE_FCRXCTRL);
		fcrxctl |= IXGBE_FCRXCTRL_LASTSEQH;
		IXGBE_WRITE_REG(hw, IXGBE_FCRXCTRL, fcrxctl);
	पूर्ण

	अगर (hw->mac.type == ixgbe_mac_X550) अणु
		/* X550 करोes not require DDP lock */

		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(0, xid),
				ddp->udp & DMA_BIT_MASK(32));
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(1, xid), (u64)ddp->udp >> 32);
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(2, xid), fcbuff);
		IXGBE_WRITE_REG(hw, IXGBE_FCDDC(3, xid), fcdmarw);
		/* program filter context */
		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(0, xid), IXGBE_FCFLT_VALID);
		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(1, xid), 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCDFC(3, xid), fcfltrw);
	पूर्ण अन्यथा अणु
		/* DDP lock क्रम indirect DDP context access */
		spin_lock_bh(&fcoe->lock);

		IXGBE_WRITE_REG(hw, IXGBE_FCPTRL, ddp->udp & DMA_BIT_MASK(32));
		IXGBE_WRITE_REG(hw, IXGBE_FCPTRH, (u64)ddp->udp >> 32);
		IXGBE_WRITE_REG(hw, IXGBE_FCBUFF, fcbuff);
		IXGBE_WRITE_REG(hw, IXGBE_FCDMARW, fcdmarw);
		/* program filter context */
		IXGBE_WRITE_REG(hw, IXGBE_FCPARAM, 0);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLT, IXGBE_FCFLT_VALID);
		IXGBE_WRITE_REG(hw, IXGBE_FCFLTRW, fcfltrw);

		spin_unlock_bh(&fcoe->lock);
	पूर्ण

	वापस 1;

out_noddp_मुक्त:
	dma_pool_मुक्त(ddp->pool, ddp->udl, ddp->udp);
	ixgbe_fcoe_clear_ddp(ddp);

out_noddp_unmap:
	dma_unmap_sg(&adapter->pdev->dev, sgl, sgc, DMA_FROM_DEVICE);
out_noddp:
	put_cpu();
	वापस 0;
पूर्ण

/**
 * ixgbe_fcoe_ddp_get - called to set up ddp context in initiator mode
 * @netdev: the corresponding net_device
 * @xid: the exchange id requesting ddp
 * @sgl: the scatter-gather list क्रम this request
 * @sgc: the number of scatter-gather items
 *
 * This is the implementation of net_device_ops.nकरो_fcoe_ddp_setup
 * and is expected to be called from ULD, e.g., FCP layer of libfc
 * to set up ddp क्रम the corresponding xid of the given sglist क्रम
 * the corresponding I/O.
 *
 * Returns : 1 क्रम success and 0 क्रम no ddp
 */
पूर्णांक ixgbe_fcoe_ddp_get(काष्ठा net_device *netdev, u16 xid,
		       काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	वापस ixgbe_fcoe_ddp_setup(netdev, xid, sgl, sgc, 0);
पूर्ण

/**
 * ixgbe_fcoe_ddp_target - called to set up ddp context in target mode
 * @netdev: the corresponding net_device
 * @xid: the exchange id requesting ddp
 * @sgl: the scatter-gather list क्रम this request
 * @sgc: the number of scatter-gather items
 *
 * This is the implementation of net_device_ops.nकरो_fcoe_ddp_target
 * and is expected to be called from ULD, e.g., FCP layer of libfc
 * to set up ddp क्रम the corresponding xid of the given sglist क्रम
 * the corresponding I/O. The DDP in target mode is a ग_लिखो I/O request
 * from the initiator.
 *
 * Returns : 1 क्रम success and 0 क्रम no ddp
 */
पूर्णांक ixgbe_fcoe_ddp_target(काष्ठा net_device *netdev, u16 xid,
			    काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	वापस ixgbe_fcoe_ddp_setup(netdev, xid, sgl, sgc, 1);
पूर्ण

/**
 * ixgbe_fcoe_ddp - check ddp status and mark it करोne
 * @adapter: ixgbe adapter
 * @rx_desc: advanced rx descriptor
 * @skb: the skb holding the received data
 *
 * This checks ddp status.
 *
 * Returns : < 0 indicates an error or not a FCiE ddp, 0 indicates
 * not passing the skb to ULD, > 0 indicates is the length of data
 * being ddped.
 */
पूर्णांक ixgbe_fcoe_ddp(काष्ठा ixgbe_adapter *adapter,
		   जोड़ ixgbe_adv_rx_desc *rx_desc,
		   काष्ठा sk_buff *skb)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा ixgbe_fcoe *fcoe;
	काष्ठा ixgbe_fcoe_ddp *ddp;
	काष्ठा fc_frame_header *fh;
	काष्ठा fcoe_crc_eof *crc;
	__le32 fcerr = ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_FCERR);
	__le32 ddp_err;
	पूर्णांक ddp_max;
	u32 fctl;
	u16 xid;

	अगर (fcerr == cpu_to_le32(IXGBE_FCERR_BADCRC))
		skb->ip_summed = CHECKSUM_NONE;
	अन्यथा
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (eth_hdr(skb)->h_proto == htons(ETH_P_8021Q))
		fh = (काष्ठा fc_frame_header *)(skb->data +
			माप(काष्ठा vlan_hdr) + माप(काष्ठा fcoe_hdr));
	अन्यथा
		fh = (काष्ठा fc_frame_header *)(skb->data +
			माप(काष्ठा fcoe_hdr));

	fctl = ntoh24(fh->fh_f_ctl);
	अगर (fctl & FC_FC_EX_CTX)
		xid =  be16_to_cpu(fh->fh_ox_id);
	अन्यथा
		xid =  be16_to_cpu(fh->fh_rx_id);

	ddp_max = IXGBE_FCOE_DDP_MAX;
	/* X550 has dअगरferent DDP Max limit */
	अगर (adapter->hw.mac.type == ixgbe_mac_X550)
		ddp_max = IXGBE_FCOE_DDP_MAX_X550;
	अगर (xid >= ddp_max)
		वापस -EINVAL;

	fcoe = &adapter->fcoe;
	ddp = &fcoe->ddp[xid];
	अगर (!ddp->udl)
		वापस -EINVAL;

	ddp_err = ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_FCखातापूर्णE |
					      IXGBE_RXDADV_ERR_FCERR);
	अगर (ddp_err)
		वापस -EINVAL;

	चयन (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_STAT_FCSTAT)) अणु
	/* वापस 0 to bypass going to ULD क्रम DDPed data */
	हाल cpu_to_le32(IXGBE_RXDADV_STAT_FCSTAT_DDP):
		/* update length of DDPed data */
		ddp->len = le32_to_cpu(rx_desc->wb.lower.hi_dword.rss);
		rc = 0;
		अवरोध;
	/* unmap the sg list when FCPRSP is received */
	हाल cpu_to_le32(IXGBE_RXDADV_STAT_FCSTAT_FCPRSP):
		dma_unmap_sg(&adapter->pdev->dev, ddp->sgl,
			     ddp->sgc, DMA_FROM_DEVICE);
		ddp->err = (__क्रमce u32)ddp_err;
		ddp->sgl = शून्य;
		ddp->sgc = 0;
		fallthrough;
	/* अगर DDP length is present pass it through to ULD */
	हाल cpu_to_le32(IXGBE_RXDADV_STAT_FCSTAT_NODDP):
		/* update length of DDPed data */
		ddp->len = le32_to_cpu(rx_desc->wb.lower.hi_dword.rss);
		अगर (ddp->len)
			rc = ddp->len;
		अवरोध;
	/* no match will वापस as an error */
	हाल cpu_to_le32(IXGBE_RXDADV_STAT_FCSTAT_NOMTCH):
	शेष:
		अवरोध;
	पूर्ण

	/* In target mode, check the last data frame of the sequence.
	 * For DDP in target mode, data is alपढ़ोy DDPed but the header
	 * indication of the last data frame ould allow is to tell अगर we
	 * got all the data and the ULP can send FCP_RSP back, as this is
	 * not a full fcoe frame, we fill the trailer here so it won't be
	 * dropped by the ULP stack.
	 */
	अगर ((fh->fh_r_ctl == FC_RCTL_DD_SOL_DATA) &&
	    (fctl & FC_FC_END_SEQ)) अणु
		skb_linearize(skb);
		crc = skb_put(skb, माप(*crc));
		crc->fcoe_eof = FC_खातापूर्ण_T;
	पूर्ण

	वापस rc;
पूर्ण

/**
 * ixgbe_fso - ixgbe FCoE Sequence Offload (FSO)
 * @tx_ring: tx desc ring
 * @first: first tx_buffer काष्ठाure containing skb, tx_flags, and protocol
 * @hdr_len: hdr_len to be वापसed
 *
 * This sets up large send offload क्रम FCoE
 *
 * Returns : 0 indicates success, < 0 क्रम error
 */
पूर्णांक ixgbe_fso(काष्ठा ixgbe_ring *tx_ring,
	      काष्ठा ixgbe_tx_buffer *first,
	      u8 *hdr_len)
अणु
	काष्ठा sk_buff *skb = first->skb;
	काष्ठा fc_frame_header *fh;
	u32 vlan_macip_lens;
	u32 fcoe_sof_eof = 0;
	u32 mss_l4len_idx;
	u32 type_tucmd = IXGBE_ADVTXT_TUCMD_FCOE;
	u8 sof, eof;

	अगर (skb_is_gso(skb) && (skb_shinfo(skb)->gso_type != SKB_GSO_FCOE)) अणु
		dev_err(tx_ring->dev, "Wrong gso type %d:expecting SKB_GSO_FCOE\n",
			skb_shinfo(skb)->gso_type);
		वापस -EINVAL;
	पूर्ण

	/* resets the header to poपूर्णांक fcoe/fc */
	skb_set_network_header(skb, skb->mac_len);
	skb_set_transport_header(skb, skb->mac_len +
				 माप(काष्ठा fcoe_hdr));

	/* sets up SOF and ORIS */
	sof = ((काष्ठा fcoe_hdr *)skb_network_header(skb))->fcoe_sof;
	चयन (sof) अणु
	हाल FC_SOF_I2:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_ORIS;
		अवरोध;
	हाल FC_SOF_I3:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_SOF |
			       IXGBE_ADVTXD_FCOEF_ORIS;
		अवरोध;
	हाल FC_SOF_N2:
		अवरोध;
	हाल FC_SOF_N3:
		fcoe_sof_eof = IXGBE_ADVTXD_FCOEF_SOF;
		अवरोध;
	शेष:
		dev_warn(tx_ring->dev, "unknown sof = 0x%x\n", sof);
		वापस -EINVAL;
	पूर्ण

	/* the first byte of the last dword is खातापूर्ण */
	skb_copy_bits(skb, skb->len - 4, &eof, 1);
	/* sets up खातापूर्ण and ORIE */
	चयन (eof) अणु
	हाल FC_खातापूर्ण_N:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_खातापूर्ण_N;
		अवरोध;
	हाल FC_खातापूर्ण_T:
		/* lso needs ORIE */
		अगर (skb_is_gso(skb))
			fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_खातापूर्ण_N |
					IXGBE_ADVTXD_FCOEF_ORIE;
		अन्यथा
			fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_खातापूर्ण_T;
		अवरोध;
	हाल FC_खातापूर्ण_NI:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_खातापूर्ण_NI;
		अवरोध;
	हाल FC_खातापूर्ण_A:
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_खातापूर्ण_A;
		अवरोध;
	शेष:
		dev_warn(tx_ring->dev, "unknown eof = 0x%x\n", eof);
		वापस -EINVAL;
	पूर्ण

	/* sets up PARINC indicating data offset */
	fh = (काष्ठा fc_frame_header *)skb_transport_header(skb);
	अगर (fh->fh_f_ctl[2] & FC_FC_REL_OFF)
		fcoe_sof_eof |= IXGBE_ADVTXD_FCOEF_PARINC;

	/* include trailer in headlen as it is replicated per frame */
	*hdr_len = माप(काष्ठा fcoe_crc_eof);

	/* hdr_len includes fc_hdr अगर FCoE LSO is enabled */
	अगर (skb_is_gso(skb)) अणु
		*hdr_len += skb_transport_offset(skb) +
			    माप(काष्ठा fc_frame_header);
		/* update gso_segs and bytecount */
		first->gso_segs = DIV_ROUND_UP(skb->len - *hdr_len,
					       skb_shinfo(skb)->gso_size);
		first->bytecount += (first->gso_segs - 1) * *hdr_len;
		first->tx_flags |= IXGBE_TX_FLAGS_TSO;
		/* Hardware expects L4T to be RSV क्रम FCoE TSO */
		type_tucmd |= IXGBE_ADVTXD_TUCMD_L4T_RSV;
	पूर्ण

	/* set flag indicating FCOE to ixgbe_tx_map call */
	first->tx_flags |= IXGBE_TX_FLAGS_FCOE | IXGBE_TX_FLAGS_CC;

	/* mss_l4len_id: use 0 क्रम FSO as TSO, no need क्रम L4LEN */
	mss_l4len_idx = skb_shinfo(skb)->gso_size << IXGBE_ADVTXD_MSS_SHIFT;

	/* vlan_macip_lens: HEADLEN, MACLEN, VLAN tag */
	vlan_macip_lens = skb_transport_offset(skb) +
			  माप(काष्ठा fc_frame_header);
	vlan_macip_lens |= (skb_transport_offset(skb) - 4)
			   << IXGBE_ADVTXD_MACLEN_SHIFT;
	vlan_macip_lens |= first->tx_flags & IXGBE_TX_FLAGS_VLAN_MASK;

	/* ग_लिखो context desc */
	ixgbe_tx_ctxtdesc(tx_ring, vlan_macip_lens, fcoe_sof_eof,
			  type_tucmd, mss_l4len_idx);

	वापस 0;
पूर्ण

अटल व्योम ixgbe_fcoe_dma_pool_मुक्त(काष्ठा ixgbe_fcoe *fcoe, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा ixgbe_fcoe_ddp_pool *ddp_pool;

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
	dma_pool_destroy(ddp_pool->pool);
	ddp_pool->pool = शून्य;
पूर्ण

अटल पूर्णांक ixgbe_fcoe_dma_pool_alloc(काष्ठा ixgbe_fcoe *fcoe,
				     काष्ठा device *dev,
				     अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा ixgbe_fcoe_ddp_pool *ddp_pool;
	काष्ठा dma_pool *pool;
	अक्षर pool_name[32];

	snम_लिखो(pool_name, 32, "ixgbe_fcoe_ddp_%u", cpu);

	pool = dma_pool_create(pool_name, dev, IXGBE_FCPTR_MAX,
			       IXGBE_FCPTR_ALIGN, PAGE_SIZE);
	अगर (!pool)
		वापस -ENOMEM;

	ddp_pool = per_cpu_ptr(fcoe->ddp_pool, cpu);
	ddp_pool->pool = pool;
	ddp_pool->noddp = 0;
	ddp_pool->noddp_ext_buff = 0;

	वापस 0;
पूर्ण

/**
 * ixgbe_configure_fcoe - configures रेजिस्टरs क्रम fcoe at start
 * @adapter: ptr to ixgbe adapter
 *
 * This sets up FCoE related रेजिस्टरs
 *
 * Returns : none
 */
व्योम ixgbe_configure_fcoe(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_ring_feature *fcoe = &adapter->ring_feature[RING_F_FCOE];
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	पूर्णांक i, fcoe_q, fcoe_i, fcoe_q_h = 0;
	पूर्णांक fcreta_size;
	u32 etqf;

	/* Minimal functionality क्रम FCoE requires at least CRC offloads */
	अगर (!(adapter->netdev->features & NETIF_F_FCOE_CRC))
		वापस;

	/* Enable L2 EtherType filter क्रम FCoE, needed क्रम FCoE CRC and DDP */
	etqf = ETH_P_FCOE | IXGBE_ETQF_FCOE | IXGBE_ETQF_FILTER_EN;
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		etqf |= IXGBE_ETQF_POOL_ENABLE;
		etqf |= VMDQ_P(0) << IXGBE_ETQF_POOL_SHIFT;
	पूर्ण
	IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_FCOE), etqf);
	IXGBE_WRITE_REG(hw, IXGBE_ETQS(IXGBE_ETQF_FILTER_FCOE), 0);

	/* leave रेजिस्टरs un-configured अगर FCoE is disabled */
	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_ENABLED))
		वापस;

	/* Use one or more Rx queues क्रम FCoE by redirection table */
	fcreta_size = IXGBE_FCRETA_SIZE;
	अगर (adapter->hw.mac.type == ixgbe_mac_X550)
		fcreta_size = IXGBE_FCRETA_SIZE_X550;

	क्रम (i = 0; i < fcreta_size; i++) अणु
		अगर (adapter->hw.mac.type == ixgbe_mac_X550) अणु
			पूर्णांक fcoe_i_h = fcoe->offset + ((i + fcreta_size) %
							fcoe->indices);
			fcoe_q_h = adapter->rx_ring[fcoe_i_h]->reg_idx;
			fcoe_q_h = (fcoe_q_h << IXGBE_FCRETA_ENTRY_HIGH_SHIFT) &
				   IXGBE_FCRETA_ENTRY_HIGH_MASK;
		पूर्ण

		fcoe_i = fcoe->offset + (i % fcoe->indices);
		fcoe_i &= IXGBE_FCRETA_ENTRY_MASK;
		fcoe_q = adapter->rx_ring[fcoe_i]->reg_idx;
		fcoe_q |= fcoe_q_h;
		IXGBE_WRITE_REG(hw, IXGBE_FCRETA(i), fcoe_q);
	पूर्ण
	IXGBE_WRITE_REG(hw, IXGBE_FCRECTL, IXGBE_FCRECTL_ENA);

	/* Enable L2 EtherType filter क्रम FIP */
	etqf = ETH_P_FIP | IXGBE_ETQF_FILTER_EN;
	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED) अणु
		etqf |= IXGBE_ETQF_POOL_ENABLE;
		etqf |= VMDQ_P(0) << IXGBE_ETQF_POOL_SHIFT;
	पूर्ण
	IXGBE_WRITE_REG(hw, IXGBE_ETQF(IXGBE_ETQF_FILTER_FIP), etqf);

	/* Send FIP frames to the first FCoE queue */
	fcoe_q = adapter->rx_ring[fcoe->offset]->reg_idx;
	IXGBE_WRITE_REG(hw, IXGBE_ETQS(IXGBE_ETQF_FILTER_FIP),
			IXGBE_ETQS_QUEUE_EN |
			(fcoe_q << IXGBE_ETQS_RX_QUEUE_SHIFT));

	/* Configure FCoE Rx control */
	IXGBE_WRITE_REG(hw, IXGBE_FCRXCTRL,
			IXGBE_FCRXCTRL_FCCRCBO |
			(FC_FCOE_VER << IXGBE_FCRXCTRL_FCOEVER_SHIFT));
पूर्ण

/**
 * ixgbe_मुक्त_fcoe_ddp_resources - release all fcoe ddp context resources
 * @adapter : ixgbe adapter
 *
 * Cleans up outstanding ddp context resources
 *
 * Returns : none
 */
व्योम ixgbe_मुक्त_fcoe_ddp_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;
	पूर्णांक cpu, i, ddp_max;

	/* करो nothing अगर no DDP pools were allocated */
	अगर (!fcoe->ddp_pool)
		वापस;

	ddp_max = IXGBE_FCOE_DDP_MAX;
	/* X550 has dअगरferent DDP Max limit */
	अगर (adapter->hw.mac.type == ixgbe_mac_X550)
		ddp_max = IXGBE_FCOE_DDP_MAX_X550;

	क्रम (i = 0; i < ddp_max; i++)
		ixgbe_fcoe_ddp_put(adapter->netdev, i);

	क्रम_each_possible_cpu(cpu)
		ixgbe_fcoe_dma_pool_मुक्त(fcoe, cpu);

	dma_unmap_single(&adapter->pdev->dev,
			 fcoe->extra_ddp_buffer_dma,
			 IXGBE_FCBUFF_MIN,
			 DMA_FROM_DEVICE);
	kमुक्त(fcoe->extra_ddp_buffer);

	fcoe->extra_ddp_buffer = शून्य;
	fcoe->extra_ddp_buffer_dma = 0;
पूर्ण

/**
 * ixgbe_setup_fcoe_ddp_resources - setup all fcoe ddp context resources
 * @adapter: ixgbe adapter
 *
 * Sets up ddp context resouces
 *
 * Returns : 0 indicates success or -EINVAL on failure
 */
पूर्णांक ixgbe_setup_fcoe_ddp_resources(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;
	काष्ठा device *dev = &adapter->pdev->dev;
	व्योम *buffer;
	dma_addr_t dma;
	अचिन्हित पूर्णांक cpu;

	/* करो nothing अगर no DDP pools were allocated */
	अगर (!fcoe->ddp_pool)
		वापस 0;

	/* Extra buffer to be shared by all DDPs क्रम HW work around */
	buffer = kदो_स्मृति(IXGBE_FCBUFF_MIN, GFP_KERNEL);
	अगर (!buffer)
		वापस -ENOMEM;

	dma = dma_map_single(dev, buffer, IXGBE_FCBUFF_MIN, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(dev, dma)) अणु
		e_err(drv, "failed to map extra DDP buffer\n");
		kमुक्त(buffer);
		वापस -ENOMEM;
	पूर्ण

	fcoe->extra_ddp_buffer = buffer;
	fcoe->extra_ddp_buffer_dma = dma;

	/* allocate pci pool क्रम each cpu */
	क्रम_each_possible_cpu(cpu) अणु
		पूर्णांक err = ixgbe_fcoe_dma_pool_alloc(fcoe, dev, cpu);
		अगर (!err)
			जारी;

		e_err(drv, "failed to alloc DDP pool on cpu:%d\n", cpu);
		ixgbe_मुक्त_fcoe_ddp_resources(adapter);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_fcoe_ddp_enable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;

	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_CAPABLE))
		वापस -EINVAL;

	fcoe->ddp_pool = alloc_percpu(काष्ठा ixgbe_fcoe_ddp_pool);

	अगर (!fcoe->ddp_pool) अणु
		e_err(drv, "failed to allocate percpu DDP resources\n");
		वापस -ENOMEM;
	पूर्ण

	adapter->netdev->fcoe_ddp_xid = IXGBE_FCOE_DDP_MAX - 1;
	/* X550 has dअगरferent DDP Max limit */
	अगर (adapter->hw.mac.type == ixgbe_mac_X550)
		adapter->netdev->fcoe_ddp_xid = IXGBE_FCOE_DDP_MAX_X550 - 1;

	वापस 0;
पूर्ण

अटल व्योम ixgbe_fcoe_ddp_disable(काष्ठा ixgbe_adapter *adapter)
अणु
	काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;

	adapter->netdev->fcoe_ddp_xid = 0;

	अगर (!fcoe->ddp_pool)
		वापस;

	मुक्त_percpu(fcoe->ddp_pool);
	fcoe->ddp_pool = शून्य;
पूर्ण

/**
 * ixgbe_fcoe_enable - turn on FCoE offload feature
 * @netdev: the corresponding netdev
 *
 * Turns on FCoE offload feature in 82599.
 *
 * Returns : 0 indicates success or -EINVAL on failure
 */
पूर्णांक ixgbe_fcoe_enable(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_fcoe *fcoe = &adapter->fcoe;

	atomic_inc(&fcoe->refcnt);

	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_CAPABLE))
		वापस -EINVAL;

	अगर (adapter->flags & IXGBE_FLAG_FCOE_ENABLED)
		वापस -EINVAL;

	e_info(drv, "Enabling FCoE offload features.\n");

	अगर (adapter->flags & IXGBE_FLAG_SRIOV_ENABLED)
		e_warn(probe, "Enabling FCoE on PF will disable legacy VFs\n");

	अगर (netअगर_running(netdev))
		netdev->netdev_ops->nकरो_stop(netdev);

	/* Allocate per CPU memory to track DDP pools */
	ixgbe_fcoe_ddp_enable(adapter);

	/* enable FCoE and notअगरy stack */
	adapter->flags |= IXGBE_FLAG_FCOE_ENABLED;
	netdev->features |= NETIF_F_FCOE_MTU;
	netdev_features_change(netdev);

	/* release existing queues and पुनः_स्मृतिate them */
	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);
	ixgbe_init_पूर्णांकerrupt_scheme(adapter);

	अगर (netअगर_running(netdev))
		netdev->netdev_ops->nकरो_खोलो(netdev);

	वापस 0;
पूर्ण

/**
 * ixgbe_fcoe_disable - turn off FCoE offload feature
 * @netdev: the corresponding netdev
 *
 * Turns off FCoE offload feature in 82599.
 *
 * Returns : 0 indicates success or -EINVAL on failure
 */
पूर्णांक ixgbe_fcoe_disable(काष्ठा net_device *netdev)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);

	अगर (!atomic_dec_and_test(&adapter->fcoe.refcnt))
		वापस -EINVAL;

	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_ENABLED))
		वापस -EINVAL;

	e_info(drv, "Disabling FCoE offload features.\n");
	अगर (netअगर_running(netdev))
		netdev->netdev_ops->nकरो_stop(netdev);

	/* Free per CPU memory to track DDP pools */
	ixgbe_fcoe_ddp_disable(adapter);

	/* disable FCoE and notअगरy stack */
	adapter->flags &= ~IXGBE_FLAG_FCOE_ENABLED;
	netdev->features &= ~NETIF_F_FCOE_MTU;

	netdev_features_change(netdev);

	/* release existing queues and पुनः_स्मृतिate them */
	ixgbe_clear_पूर्णांकerrupt_scheme(adapter);
	ixgbe_init_पूर्णांकerrupt_scheme(adapter);

	अगर (netअगर_running(netdev))
		netdev->netdev_ops->nकरो_खोलो(netdev);

	वापस 0;
पूर्ण

/**
 * ixgbe_fcoe_get_wwn - get world wide name क्रम the node or the port
 * @netdev : ixgbe adapter
 * @wwn : the world wide name
 * @type: the type of world wide name
 *
 * Returns the node or port world wide name अगर both the prefix and the san
 * mac address are valid, then the wwn is क्रमmed based on the NAA-2 क्रम
 * IEEE Extended name identअगरier (ref. to T10 FC-LS Spec., Sec. 15.3).
 *
 * Returns : 0 on success
 */
पूर्णांक ixgbe_fcoe_get_wwn(काष्ठा net_device *netdev, u64 *wwn, पूर्णांक type)
अणु
	u16 prefix = 0xffff;
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_mac_info *mac = &adapter->hw.mac;

	चयन (type) अणु
	हाल NETDEV_FCOE_WWNN:
		prefix = mac->wwnn_prefix;
		अवरोध;
	हाल NETDEV_FCOE_WWPN:
		prefix = mac->wwpn_prefix;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर ((prefix != 0xffff) &&
	    is_valid_ether_addr(mac->san_addr)) अणु
		*wwn = ((u64) prefix << 48) |
		       ((u64) mac->san_addr[0] << 40) |
		       ((u64) mac->san_addr[1] << 32) |
		       ((u64) mac->san_addr[2] << 24) |
		       ((u64) mac->san_addr[3] << 16) |
		       ((u64) mac->san_addr[4] << 8)  |
		       ((u64) mac->san_addr[5]);
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

/**
 * ixgbe_fcoe_get_hbainfo - get FCoE HBA inक्रमmation
 * @netdev : ixgbe adapter
 * @info : HBA inक्रमmation
 *
 * Returns ixgbe HBA inक्रमmation
 *
 * Returns : 0 on success
 */
पूर्णांक ixgbe_fcoe_get_hbainfo(काष्ठा net_device *netdev,
			   काष्ठा netdev_fcoe_hbainfo *info)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(netdev);
	काष्ठा ixgbe_hw *hw = &adapter->hw;
	u64 dsn;

	अगर (!info)
		वापस -EINVAL;

	/* Don't वापस inक्रमmation on unsupported devices */
	अगर (!(adapter->flags & IXGBE_FLAG_FCOE_ENABLED))
		वापस -EINVAL;

	/* Manufacturer */
	snम_लिखो(info->manufacturer, माप(info->manufacturer),
		 "Intel Corporation");

	/* Serial Number */

	/* Get the PCI-e Device Serial Number Capability */
	dsn = pci_get_dsn(adapter->pdev);
	अगर (dsn)
		snम_लिखो(info->serial_number, माप(info->serial_number),
			 "%016llX", dsn);
	अन्यथा
		snम_लिखो(info->serial_number, माप(info->serial_number),
			 "Unknown");

	/* Hardware Version */
	snम_लिखो(info->hardware_version,
		 माप(info->hardware_version),
		 "Rev %d", hw->revision_id);
	/* Driver Name/Version */
	snम_लिखो(info->driver_version,
		 माप(info->driver_version),
		 "%s v%s",
		 ixgbe_driver_name,
		 UTS_RELEASE);
	/* Firmware Version */
	strlcpy(info->firmware_version, adapter->eeprom_id,
		माप(info->firmware_version));

	/* Model */
	अगर (hw->mac.type == ixgbe_mac_82599EB) अणु
		snम_लिखो(info->model,
			 माप(info->model),
			 "Intel 82599");
	पूर्ण अन्यथा अगर (hw->mac.type == ixgbe_mac_X550) अणु
		snम_लिखो(info->model,
			 माप(info->model),
			 "Intel X550");
	पूर्ण अन्यथा अणु
		snम_लिखो(info->model,
			 माप(info->model),
			 "Intel X540");
	पूर्ण

	/* Model Description */
	snम_लिखो(info->model_description,
		 माप(info->model_description),
		 "%s",
		 ixgbe_शेष_device_descr);

	वापस 0;
पूर्ण

/**
 * ixgbe_fcoe_get_tc - get the current TC that fcoe is mapped to
 * @adapter: poपूर्णांकer to the device adapter काष्ठाure
 *
 * Return : TC that FCoE is mapped to
 */
u8 ixgbe_fcoe_get_tc(काष्ठा ixgbe_adapter *adapter)
अणु
#अगर_घोषित CONFIG_IXGBE_DCB
	वापस netdev_get_prio_tc_map(adapter->netdev, adapter->fcoe.up);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण
