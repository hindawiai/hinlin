<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pci.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/घातer_supply.h>
#समावेश "wil6210.h"
#समावेश "wmi.h"
#समावेश "txrx.h"
#समावेश "pmc.h"

/* Nasty hack. Better have per device instances */
अटल u32 mem_addr;
अटल u32 dbg_txdesc_index;
अटल u32 dbg_ring_index; /* 24+ क्रम Rx, 0..23 क्रम Tx */
अटल u32 dbg_status_msg_index;
/* 0..wil->num_rx_status_rings-1 क्रम Rx, wil->tx_sring_idx क्रम Tx */
अटल u32 dbg_sring_index;

क्रमागत dbg_off_type अणु
	करोff_u32 = 0,
	करोff_x32 = 1,
	करोff_uदीर्घ = 2,
	करोff_io32 = 3,
	करोff_u8 = 4
पूर्ण;

/* offset to "wil" */
काष्ठा dbg_off अणु
	स्थिर अक्षर *name;
	umode_t mode;
	uदीर्घ off;
	क्रमागत dbg_off_type type;
पूर्ण;

अटल व्योम wil_prपूर्णांक_desc_edma(काष्ठा seq_file *s, काष्ठा wil6210_priv *wil,
				काष्ठा wil_ring *ring,
				अक्षर _s, अक्षर _h, पूर्णांक idx)
अणु
	u8 num_of_descs;
	bool has_skb = false;

	अगर (ring->is_rx) अणु
		काष्ठा wil_rx_enhanced_desc *rx_d =
			(काष्ठा wil_rx_enhanced_desc *)
			&ring->va[idx].rx.enhanced;
		u16 buff_id = le16_to_cpu(rx_d->mac.buff_id);

		अगर (wil->rx_buff_mgmt.buff_arr &&
		    wil_val_in_range(buff_id, 0, wil->rx_buff_mgmt.size))
			has_skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
		seq_म_लिखो(s, "%c", (has_skb) ? _h : _s);
	पूर्ण अन्यथा अणु
		काष्ठा wil_tx_enhanced_desc *d =
			(काष्ठा wil_tx_enhanced_desc *)
			&ring->va[idx].tx.enhanced;

		num_of_descs = (u8)d->mac.d[2];
		has_skb = ring->ctx && ring->ctx[idx].skb;
		अगर (num_of_descs >= 1)
			seq_म_लिखो(s, "%c", has_skb ? _h : _s);
		अन्यथा
			/* num_of_descs == 0, it's a frag in a list of descs */
			seq_म_लिखो(s, "%c", has_skb ? 'h' : _s);
	पूर्ण
पूर्ण

अटल व्योम wil_prपूर्णांक_ring(काष्ठा seq_file *s, काष्ठा wil6210_priv *wil,
			   स्थिर अक्षर *name, काष्ठा wil_ring *ring,
			   अक्षर _s, अक्षर _h)
अणु
	व्योम __iomem *x;
	u32 v;

	seq_म_लिखो(s, "RING %s = {\n", name);
	seq_म_लिखो(s, "  pa     = %pad\n", &ring->pa);
	seq_म_लिखो(s, "  va     = 0x%p\n", ring->va);
	seq_म_लिखो(s, "  size   = %d\n", ring->size);
	अगर (wil->use_enhanced_dma_hw && ring->is_rx)
		seq_म_लिखो(s, "  swtail = %u\n", *ring->edma_rx_swtail.va);
	अन्यथा
		seq_म_लिखो(s, "  swtail = %d\n", ring->swtail);
	seq_म_लिखो(s, "  swhead = %d\n", ring->swhead);
	अगर (wil->use_enhanced_dma_hw) अणु
		पूर्णांक ring_id = ring->is_rx ?
			WIL_RX_DESC_RING_ID : ring - wil->ring_tx;
		/* SUBQ_CONS is a table of 32 entries, one क्रम each Q pair.
		 * lower 16bits are क्रम even ring_id and upper 16bits are क्रम
		 * odd ring_id
		 */
		x = wmi_addr(wil, RGF_DMA_SCM_SUBQ_CONS + 4 * (ring_id / 2));
		v = पढ़ोl_relaxed(x);

		v = (ring_id % 2 ? (v >> 16) : (v & 0xffff));
		seq_म_लिखो(s, "  hwhead = %u\n", v);
	पूर्ण
	seq_म_लिखो(s, "  hwtail = [0x%08x] -> ", ring->hwtail);
	x = wmi_addr(wil, ring->hwtail);
	अगर (x) अणु
		v = पढ़ोl(x);
		seq_म_लिखो(s, "0x%08x = %d\n", v, v);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "???\n");
	पूर्ण

	अगर (ring->va && (ring->size <= (1 << WIL_RING_SIZE_ORDER_MAX))) अणु
		uपूर्णांक i;

		क्रम (i = 0; i < ring->size; i++) अणु
			अगर ((i % 128) == 0 && i != 0)
				seq_माला_दो(s, "\n");
			अगर (wil->use_enhanced_dma_hw) अणु
				wil_prपूर्णांक_desc_edma(s, wil, ring, _s, _h, i);
			पूर्ण अन्यथा अणु
				अस्थिर काष्ठा vring_tx_desc *d =
					&ring->va[i].tx.legacy;
				seq_म_लिखो(s, "%c", (d->dma.status & BIT(0)) ?
					   _s : (ring->ctx[i].skb ? _h : 'h'));
			पूर्ण
		पूर्ण
		seq_माला_दो(s, "\n");
	पूर्ण
	seq_माला_दो(s, "}\n");
पूर्ण

अटल पूर्णांक ring_show(काष्ठा seq_file *s, व्योम *data)
अणु
	uपूर्णांक i;
	काष्ठा wil6210_priv *wil = s->निजी;

	wil_prपूर्णांक_ring(s, wil, "rx", &wil->ring_rx, 'S', '_');

	क्रम (i = 0; i < ARRAY_SIZE(wil->ring_tx); i++) अणु
		काष्ठा wil_ring *ring = &wil->ring_tx[i];
		काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[i];

		अगर (ring->va) अणु
			पूर्णांक cid = wil->ring2cid_tid[i][0];
			पूर्णांक tid = wil->ring2cid_tid[i][1];
			u32 swhead = ring->swhead;
			u32 swtail = ring->swtail;
			पूर्णांक used = (ring->size + swhead - swtail)
				   % ring->size;
			पूर्णांक avail = ring->size - used - 1;
			अक्षर name[10];
			अक्षर sidle[10];
			/* perक्रमmance monitoring */
			cycles_t now = get_cycles();
			uपूर्णांक64_t idle = txdata->idle * 100;
			uपूर्णांक64_t total = now - txdata->begin;

			अगर (total != 0) अणु
				करो_भाग(idle, total);
				snम_लिखो(sidle, माप(sidle), "%3d%%",
					 (पूर्णांक)idle);
			पूर्ण अन्यथा अणु
				snम_लिखो(sidle, माप(sidle), "N/A");
			पूर्ण
			txdata->begin = now;
			txdata->idle = 0ULL;

			snम_लिखो(name, माप(name), "tx_%2d", i);

			अगर (cid < wil->max_assoc_sta)
				seq_म_लिखो(s,
					   "\n%pM CID %d TID %d 1x%s BACK([%u] %u TU A%s) [%3d|%3d] idle %s\n",
					   wil->sta[cid].addr, cid, tid,
					   txdata->करोt1x_खोलो ? "+" : "-",
					   txdata->agg_wsize,
					   txdata->agg_समयout,
					   txdata->agg_amsdu ? "+" : "-",
					   used, avail, sidle);
			अन्यथा
				seq_म_लिखो(s,
					   "\nBroadcast 1x%s [%3d|%3d] idle %s\n",
					   txdata->करोt1x_खोलो ? "+" : "-",
					   used, avail, sidle);

			wil_prपूर्णांक_ring(s, wil, name, ring, '_', 'H');
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(ring);

अटल व्योम wil_prपूर्णांक_sring(काष्ठा seq_file *s, काष्ठा wil6210_priv *wil,
			    काष्ठा wil_status_ring *sring)
अणु
	व्योम __iomem *x;
	पूर्णांक sring_idx = sring - wil->srings;
	u32 v;

	seq_म_लिखो(s, "Status Ring %s [ %d ] = {\n",
		   sring->is_rx ? "RX" : "TX", sring_idx);
	seq_म_लिखो(s, "  pa     = %pad\n", &sring->pa);
	seq_म_लिखो(s, "  va     = 0x%pK\n", sring->va);
	seq_म_लिखो(s, "  size   = %d\n", sring->size);
	seq_म_लिखो(s, "  elem_size   = %zu\n", sring->elem_size);
	seq_म_लिखो(s, "  swhead = %d\n", sring->swhead);
	अगर (wil->use_enhanced_dma_hw) अणु
		/* COMPQ_PROD is a table of 32 entries, one क्रम each Q pair.
		 * lower 16bits are क्रम even ring_id and upper 16bits are क्रम
		 * odd ring_id
		 */
		x = wmi_addr(wil, RGF_DMA_SCM_COMPQ_PROD + 4 * (sring_idx / 2));
		v = पढ़ोl_relaxed(x);

		v = (sring_idx % 2 ? (v >> 16) : (v & 0xffff));
		seq_म_लिखो(s, "  hwhead = %u\n", v);
	पूर्ण
	seq_म_लिखो(s, "  hwtail = [0x%08x] -> ", sring->hwtail);
	x = wmi_addr(wil, sring->hwtail);
	अगर (x) अणु
		v = पढ़ोl_relaxed(x);
		seq_म_लिखो(s, "0x%08x = %d\n", v, v);
	पूर्ण अन्यथा अणु
		seq_माला_दो(s, "???\n");
	पूर्ण
	seq_म_लिखो(s, "  desc_rdy_pol   = %d\n", sring->desc_rdy_pol);
	seq_म_लिखो(s, "  invalid_buff_id_cnt   = %d\n",
		   sring->invalid_buff_id_cnt);

	अगर (sring->va && (sring->size <= (1 << WIL_RING_SIZE_ORDER_MAX))) अणु
		uपूर्णांक i;

		क्रम (i = 0; i < sring->size; i++) अणु
			u32 *sdword_0 =
				(u32 *)(sring->va + (sring->elem_size * i));

			अगर ((i % 128) == 0 && i != 0)
				seq_माला_दो(s, "\n");
			अगर (i == sring->swhead)
				seq_म_लिखो(s, "%c", (*sdword_0 & BIT(31)) ?
					   'X' : 'x');
			अन्यथा
				seq_म_लिखो(s, "%c", (*sdword_0 & BIT(31)) ?
					   '1' : '0');
		पूर्ण
		seq_माला_दो(s, "\n");
	पूर्ण
	seq_माला_दो(s, "}\n");
पूर्ण

अटल पूर्णांक srings_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक i = 0;

	क्रम (i = 0; i < WIL6210_MAX_STATUS_RINGS; i++)
		अगर (wil->srings[i].va)
			wil_prपूर्णांक_sring(s, wil, &wil->srings[i]);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(srings);

अटल व्योम wil_seq_hexdump(काष्ठा seq_file *s, व्योम *p, पूर्णांक len,
			    स्थिर अक्षर *prefix)
अणु
	seq_hex_dump(s, prefix, DUMP_PREFIX_NONE, 16, 1, p, len, false);
पूर्ण

अटल व्योम wil_prपूर्णांक_mbox_ring(काष्ठा seq_file *s, स्थिर अक्षर *prefix,
				व्योम __iomem *off)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil6210_mbox_ring r;
	पूर्णांक rsize;
	uपूर्णांक i;

	wil_halp_vote(wil);

	अगर (wil_mem_access_lock(wil)) अणु
		wil_halp_unvote(wil);
		वापस;
	पूर्ण

	wil_स_नकल_fromio_32(&r, off, माप(r));
	wil_mbox_ring_le2cpus(&r);
	/*
	 * we just पढ़ो memory block from NIC. This memory may be
	 * garbage. Check validity beक्रमe using it.
	 */
	rsize = r.size / माप(काष्ठा wil6210_mbox_ring_desc);

	seq_म_लिखो(s, "ring %s = {\n", prefix);
	seq_म_लिखो(s, "  base = 0x%08x\n", r.base);
	seq_म_लिखो(s, "  size = 0x%04x bytes -> %d entries\n", r.size, rsize);
	seq_म_लिखो(s, "  tail = 0x%08x\n", r.tail);
	seq_म_लिखो(s, "  head = 0x%08x\n", r.head);
	seq_म_लिखो(s, "  entry size = %d\n", r.entry_size);

	अगर (r.size % माप(काष्ठा wil6210_mbox_ring_desc)) अणु
		seq_म_लिखो(s, "  ??? size is not multiple of %zd, garbage?\n",
			   माप(काष्ठा wil6210_mbox_ring_desc));
		जाओ out;
	पूर्ण

	अगर (!wmi_addr(wil, r.base) ||
	    !wmi_addr(wil, r.tail) ||
	    !wmi_addr(wil, r.head)) अणु
		seq_माला_दो(s, "  ??? pointers are garbage?\n");
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < rsize; i++) अणु
		काष्ठा wil6210_mbox_ring_desc d;
		काष्ठा wil6210_mbox_hdr hdr;
		माप_प्रकार delta = i * माप(d);
		व्योम __iomem *x = wil->csr + HOSTADDR(r.base) + delta;

		wil_स_नकल_fromio_32(&d, x, माप(d));

		seq_म_लिखो(s, "  [%2x] %s %s%s 0x%08x", i,
			   d.sync ? "F" : "E",
			   (r.tail - r.base == delta) ? "t" : " ",
			   (r.head - r.base == delta) ? "h" : " ",
			   le32_to_cpu(d.addr));
		अगर (0 == wmi_पढ़ो_hdr(wil, d.addr, &hdr)) अणु
			u16 len = le16_to_cpu(hdr.len);

			seq_म_लिखो(s, " -> %04x %04x %04x %02x\n",
				   le16_to_cpu(hdr.seq), len,
				   le16_to_cpu(hdr.type), hdr.flags);
			अगर (len <= MAX_MBOXITEM_SIZE) अणु
				अचिन्हित अक्षर databuf[MAX_MBOXITEM_SIZE];
				व्योम __iomem *src = wmi_buffer(wil, d.addr) +
					माप(काष्ठा wil6210_mbox_hdr);
				/*
				 * No need to check @src क्रम validity -
				 * we alपढ़ोy validated @d.addr जबतक
				 * पढ़ोing header
				 */
				wil_स_नकल_fromio_32(databuf, src, len);
				wil_seq_hexdump(s, databuf, len, "      : ");
			पूर्ण
		पूर्ण अन्यथा अणु
			seq_माला_दो(s, "\n");
		पूर्ण
	पूर्ण
 out:
	seq_माला_दो(s, "}\n");
	wil_mem_access_unlock(wil);
	wil_halp_unvote(wil);
पूर्ण

अटल पूर्णांक mbox_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक ret;

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		वापस ret;

	wil_prपूर्णांक_mbox_ring(s, "tx", wil->csr + HOST_MBOX +
		       दुरत्व(काष्ठा wil6210_mbox_ctl, tx));
	wil_prपूर्णांक_mbox_ring(s, "rx", wil->csr + HOST_MBOX +
		       दुरत्व(काष्ठा wil6210_mbox_ctl, rx));

	wil_pm_runसमय_put(wil);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mbox);

अटल पूर्णांक wil_debugfs_iomem_x32_set(व्योम *data, u64 val)
अणु
	काष्ठा wil_debugfs_iomem_data *d = (काष्ठा
					    wil_debugfs_iomem_data *)data;
	काष्ठा wil6210_priv *wil = d->wil;
	पूर्णांक ret;

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl_relaxed(val, (व्योम __iomem *)d->offset);

	wmb(); /* make sure ग_लिखो propagated to HW */

	wil_pm_runसमय_put(wil);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_debugfs_iomem_x32_get(व्योम *data, u64 *val)
अणु
	काष्ठा wil_debugfs_iomem_data *d = (काष्ठा
					    wil_debugfs_iomem_data *)data;
	काष्ठा wil6210_priv *wil = d->wil;
	पूर्णांक ret;

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		वापस ret;

	*val = पढ़ोl((व्योम __iomem *)d->offset);

	wil_pm_runसमय_put(wil);

	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_iomem_x32, wil_debugfs_iomem_x32_get,
			 wil_debugfs_iomem_x32_set, "0x%08llx\n");

अटल व्योम wil_debugfs_create_iomem_x32(स्थिर अक्षर *name, umode_t mode,
					 काष्ठा dentry *parent, व्योम *value,
					 काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_debugfs_iomem_data *data = &wil->dbg_data.data_arr[
					      wil->dbg_data.iomem_data_count];

	data->wil = wil;
	data->offset = value;

	debugfs_create_file_unsafe(name, mode, parent, data, &fops_iomem_x32);
	wil->dbg_data.iomem_data_count++;
पूर्ण

अटल पूर्णांक wil_debugfs_uदीर्घ_set(व्योम *data, u64 val)
अणु
	*(uदीर्घ *)data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक wil_debugfs_uदीर्घ_get(व्योम *data, u64 *val)
अणु
	*val = *(uदीर्घ *)data;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(wil_fops_uदीर्घ, wil_debugfs_uदीर्घ_get,
			 wil_debugfs_uदीर्घ_set, "0x%llx\n");

/**
 * wil6210_debugfs_init_offset - create set of debugfs files
 * @wil: driver's context, used क्रम prपूर्णांकing
 * @dbg: directory on the debugfs, where files will be created
 * @base: base address used in address calculation
 * @tbl: table with file descriptions. Should be terminated with empty element.
 *
 * Creates files accordingly to the @tbl.
 */
अटल व्योम wil6210_debugfs_init_offset(काष्ठा wil6210_priv *wil,
					काष्ठा dentry *dbg, व्योम *base,
					स्थिर काष्ठा dbg_off * स्थिर tbl)
अणु
	पूर्णांक i;

	क्रम (i = 0; tbl[i].name; i++) अणु
		चयन (tbl[i].type) अणु
		हाल करोff_u32:
			debugfs_create_u32(tbl[i].name, tbl[i].mode, dbg,
					   base + tbl[i].off);
			अवरोध;
		हाल करोff_x32:
			debugfs_create_x32(tbl[i].name, tbl[i].mode, dbg,
					   base + tbl[i].off);
			अवरोध;
		हाल करोff_uदीर्घ:
			debugfs_create_file_unsafe(tbl[i].name, tbl[i].mode,
						   dbg, base + tbl[i].off,
						   &wil_fops_uदीर्घ);
			अवरोध;
		हाल करोff_io32:
			wil_debugfs_create_iomem_x32(tbl[i].name, tbl[i].mode,
						     dbg, base + tbl[i].off,
						     wil);
			अवरोध;
		हाल करोff_u8:
			debugfs_create_u8(tbl[i].name, tbl[i].mode, dbg,
					  base + tbl[i].off);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dbg_off isr_off[] = अणु
	अणु"ICC", 0644, दुरत्व(काष्ठा RGF_ICR, ICC), करोff_io32पूर्ण,
	अणु"ICR", 0644, दुरत्व(काष्ठा RGF_ICR, ICR), करोff_io32पूर्ण,
	अणु"ICM", 0644, दुरत्व(काष्ठा RGF_ICR, ICM), करोff_io32पूर्ण,
	अणु"ICS",	0244, दुरत्व(काष्ठा RGF_ICR, ICS), करोff_io32पूर्ण,
	अणु"IMV", 0644, दुरत्व(काष्ठा RGF_ICR, IMV), करोff_io32पूर्ण,
	अणु"IMS",	0244, दुरत्व(काष्ठा RGF_ICR, IMS), करोff_io32पूर्ण,
	अणु"IMC",	0244, दुरत्व(काष्ठा RGF_ICR, IMC), करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम wil6210_debugfs_create_ISR(काष्ठा wil6210_priv *wil,
				       स्थिर अक्षर *name, काष्ठा dentry *parent,
				       u32 off)
अणु
	काष्ठा dentry *d = debugfs_create_dir(name, parent);

	wil6210_debugfs_init_offset(wil, d, (व्योम * __क्रमce)wil->csr + off,
				    isr_off);
पूर्ण

अटल स्थिर काष्ठा dbg_off pseuकरो_isr_off[] = अणु
	अणु"CAUSE",   0444, HOSTADDR(RGF_DMA_PSEUDO_CAUSE), करोff_io32पूर्ण,
	अणु"MASK_SW", 0444, HOSTADDR(RGF_DMA_PSEUDO_CAUSE_MASK_SW), करोff_io32पूर्ण,
	अणु"MASK_FW", 0444, HOSTADDR(RGF_DMA_PSEUDO_CAUSE_MASK_FW), करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम wil6210_debugfs_create_pseuकरो_ISR(काष्ठा wil6210_priv *wil,
					      काष्ठा dentry *parent)
अणु
	काष्ठा dentry *d = debugfs_create_dir("PSEUDO_ISR", parent);

	wil6210_debugfs_init_offset(wil, d, (व्योम * __क्रमce)wil->csr,
				    pseuकरो_isr_off);
पूर्ण

अटल स्थिर काष्ठा dbg_off lgc_itr_cnt_off[] = अणु
	अणु"TRSH", 0644, HOSTADDR(RGF_DMA_ITR_CNT_TRSH), करोff_io32पूर्ण,
	अणु"DATA", 0644, HOSTADDR(RGF_DMA_ITR_CNT_DATA), करोff_io32पूर्ण,
	अणु"CTL",  0644, HOSTADDR(RGF_DMA_ITR_CNT_CRL), करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dbg_off tx_itr_cnt_off[] = अणु
	अणु"TRSH", 0644, HOSTADDR(RGF_DMA_ITR_TX_CNT_TRSH),
	 करोff_io32पूर्ण,
	अणु"DATA", 0644, HOSTADDR(RGF_DMA_ITR_TX_CNT_DATA),
	 करोff_io32पूर्ण,
	अणु"CTL",  0644, HOSTADDR(RGF_DMA_ITR_TX_CNT_CTL),
	 करोff_io32पूर्ण,
	अणु"IDL_TRSH", 0644, HOSTADDR(RGF_DMA_ITR_TX_IDL_CNT_TRSH),
	 करोff_io32पूर्ण,
	अणु"IDL_DATA", 0644, HOSTADDR(RGF_DMA_ITR_TX_IDL_CNT_DATA),
	 करोff_io32पूर्ण,
	अणु"IDL_CTL",  0644, HOSTADDR(RGF_DMA_ITR_TX_IDL_CNT_CTL),
	 करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dbg_off rx_itr_cnt_off[] = अणु
	अणु"TRSH", 0644, HOSTADDR(RGF_DMA_ITR_RX_CNT_TRSH),
	 करोff_io32पूर्ण,
	अणु"DATA", 0644, HOSTADDR(RGF_DMA_ITR_RX_CNT_DATA),
	 करोff_io32पूर्ण,
	अणु"CTL",  0644, HOSTADDR(RGF_DMA_ITR_RX_CNT_CTL),
	 करोff_io32पूर्ण,
	अणु"IDL_TRSH", 0644, HOSTADDR(RGF_DMA_ITR_RX_IDL_CNT_TRSH),
	 करोff_io32पूर्ण,
	अणु"IDL_DATA", 0644, HOSTADDR(RGF_DMA_ITR_RX_IDL_CNT_DATA),
	 करोff_io32पूर्ण,
	अणु"IDL_CTL",  0644, HOSTADDR(RGF_DMA_ITR_RX_IDL_CNT_CTL),
	 करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक wil6210_debugfs_create_ITR_CNT(काष्ठा wil6210_priv *wil,
					  काष्ठा dentry *parent)
अणु
	काष्ठा dentry *d, *dtx, *drx;

	d = debugfs_create_dir("ITR_CNT", parent);

	dtx = debugfs_create_dir("TX", d);
	drx = debugfs_create_dir("RX", d);

	wil6210_debugfs_init_offset(wil, d, (व्योम * __क्रमce)wil->csr,
				    lgc_itr_cnt_off);

	wil6210_debugfs_init_offset(wil, dtx, (व्योम * __क्रमce)wil->csr,
				    tx_itr_cnt_off);

	wil6210_debugfs_init_offset(wil, drx, (व्योम * __क्रमce)wil->csr,
				    rx_itr_cnt_off);
	वापस 0;
पूर्ण

अटल पूर्णांक memपढ़ो_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	व्योम __iomem *a;
	पूर्णांक ret;

	ret = wil_pm_runसमय_get(wil);
	अगर (ret < 0)
		वापस ret;

	ret = wil_mem_access_lock(wil);
	अगर (ret) अणु
		wil_pm_runसमय_put(wil);
		वापस ret;
	पूर्ण

	a = wmi_buffer(wil, cpu_to_le32(mem_addr));

	अगर (a)
		seq_म_लिखो(s, "[0x%08x] = 0x%08x\n", mem_addr, पढ़ोl(a));
	अन्यथा
		seq_म_लिखो(s, "[0x%08x] = INVALID\n", mem_addr);

	wil_mem_access_unlock(wil);
	wil_pm_runसमय_put(wil);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(memपढ़ो);

अटल sमाप_प्रकार wil_पढ़ो_file_ioblob(काष्ठा file *file, अक्षर __user *user_buf,
				    माप_प्रकार count, loff_t *ppos)
अणु
	क्रमागत अणु max_count = 4096 पूर्ण;
	काष्ठा wil_blob_wrapper *wil_blob = file->निजी_data;
	काष्ठा wil6210_priv *wil = wil_blob->wil;
	loff_t aligned_pos, pos = *ppos;
	माप_प्रकार available = wil_blob->blob.size;
	व्योम *buf;
	माप_प्रकार unaligned_bytes, aligned_count, ret;
	पूर्णांक rc;

	अगर (pos < 0)
		वापस -EINVAL;

	अगर (pos >= available || !count)
		वापस 0;

	अगर (count > available - pos)
		count = available - pos;
	अगर (count > max_count)
		count = max_count;

	/* set pos to 4 bytes aligned */
	unaligned_bytes = pos % 4;
	aligned_pos = pos - unaligned_bytes;
	aligned_count = count + unaligned_bytes;

	buf = kदो_स्मृति(aligned_count, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	rc = wil_pm_runसमय_get(wil);
	अगर (rc < 0) अणु
		kमुक्त(buf);
		वापस rc;
	पूर्ण

	rc = wil_mem_access_lock(wil);
	अगर (rc) अणु
		kमुक्त(buf);
		wil_pm_runसमय_put(wil);
		वापस rc;
	पूर्ण

	wil_स_नकल_fromio_32(buf, (स्थिर व्योम __iomem *)
			     wil_blob->blob.data + aligned_pos, aligned_count);

	ret = copy_to_user(user_buf, buf + unaligned_bytes, count);

	wil_mem_access_unlock(wil);
	wil_pm_runसमय_put(wil);

	kमुक्त(buf);
	अगर (ret == count)
		वापस -EFAULT;

	count -= ret;
	*ppos = pos + count;

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_ioblob = अणु
	.पढ़ो =		wil_पढ़ो_file_ioblob,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल
काष्ठा dentry *wil_debugfs_create_ioblob(स्थिर अक्षर *name,
					 umode_t mode,
					 काष्ठा dentry *parent,
					 काष्ठा wil_blob_wrapper *wil_blob)
अणु
	वापस debugfs_create_file(name, mode, parent, wil_blob, &fops_ioblob);
पूर्ण

/*---ग_लिखो channel 1..4 to rxon क्रम it, 0 to rxoff---*/
अटल sमाप_प्रकार wil_ग_लिखो_file_rxon(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	पूर्णांक rc;
	दीर्घ channel;
	bool on;

	अक्षर *kbuf = memdup_user_nul(buf, len);

	अगर (IS_ERR(kbuf))
		वापस PTR_ERR(kbuf);
	rc = kम_से_दीर्घ(kbuf, 0, &channel);
	kमुक्त(kbuf);
	अगर (rc)
		वापस rc;

	अगर ((channel < 0) || (channel > 4)) अणु
		wil_err(wil, "Invalid channel %ld\n", channel);
		वापस -EINVAL;
	पूर्ण
	on = !!channel;

	अगर (on) अणु
		rc = wmi_set_channel(wil, (पूर्णांक)channel);
		अगर (rc)
			वापस rc;
	पूर्ण

	rc = wmi_rxon(wil, on);
	अगर (rc)
		वापस rc;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_rxon = अणु
	.ग_लिखो = wil_ग_लिखो_file_rxon,
	.खोलो  = simple_खोलो,
पूर्ण;

अटल sमाप_प्रकार wil_ग_लिखो_file_rbufcap(काष्ठा file *file,
				      स्थिर अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	पूर्णांक val;
	पूर्णांक rc;

	rc = kstrtoपूर्णांक_from_user(buf, count, 0, &val);
	अगर (rc) अणु
		wil_err(wil, "Invalid argument\n");
		वापस rc;
	पूर्ण
	/* input value: negative to disable, 0 to use प्रणाली शेष,
	 * 1..ring size to set descriptor threshold
	 */
	wil_info(wil, "%s RBUFCAP, descriptors threshold - %d\n",
		 val < 0 ? "Disabling" : "Enabling", val);

	अगर (!wil->ring_rx.va || val > wil->ring_rx.size) अणु
		wil_err(wil, "Invalid descriptors threshold, %d\n", val);
		वापस -EINVAL;
	पूर्ण

	rc = wmi_rbufcap_cfg(wil, val < 0 ? 0 : 1, val < 0 ? 0 : val);
	अगर (rc) अणु
		wil_err(wil, "RBUFCAP config failed: %d\n", rc);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_rbufcap = अणु
	.ग_लिखो = wil_ग_लिखो_file_rbufcap,
	.खोलो  = simple_खोलो,
पूर्ण;

/* block ack control, ग_लिखो:
 * - "add <ringid> <agg_size> <timeout>" to trigger ADDBA
 * - "del_tx <ringid> <reason>" to trigger DELBA क्रम Tx side
 * - "del_rx <CID> <TID> <reason>" to trigger DELBA क्रम Rx side
 */
अटल sमाप_प्रकार wil_ग_लिखो_back(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	पूर्णांक rc;
	अक्षर *kbuf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अक्षर cmd[9];
	पूर्णांक p1, p2, p3;

	अगर (!kbuf)
		वापस -ENOMEM;

	rc = simple_ग_लिखो_to_buffer(kbuf, len, ppos, buf, len);
	अगर (rc != len) अणु
		kमुक्त(kbuf);
		वापस rc >= 0 ? -EIO : rc;
	पूर्ण

	kbuf[len] = '\0';
	rc = माला_पूछो(kbuf, "%8s %d %d %d", cmd, &p1, &p2, &p3);
	kमुक्त(kbuf);

	अगर (rc < 0)
		वापस rc;
	अगर (rc < 2)
		वापस -EINVAL;

	अगर ((म_भेद(cmd, "add") == 0) ||
	    (म_भेद(cmd, "del_tx") == 0)) अणु
		काष्ठा wil_ring_tx_data *txdata;

		अगर (p1 < 0 || p1 >= WIL6210_MAX_TX_RINGS) अणु
			wil_err(wil, "BACK: invalid ring id %d\n", p1);
			वापस -EINVAL;
		पूर्ण
		txdata = &wil->ring_tx_data[p1];
		अगर (म_भेद(cmd, "add") == 0) अणु
			अगर (rc < 3) अणु
				wil_err(wil, "BACK: add require at least 2 params\n");
				वापस -EINVAL;
			पूर्ण
			अगर (rc < 4)
				p3 = 0;
			wmi_addba(wil, txdata->mid, p1, p2, p3);
		पूर्ण अन्यथा अणु
			अगर (rc < 3)
				p2 = WLAN_REASON_QSTA_LEAVE_QBSS;
			wmi_delba_tx(wil, txdata->mid, p1, p2);
		पूर्ण
	पूर्ण अन्यथा अगर (म_भेद(cmd, "del_rx") == 0) अणु
		काष्ठा wil_sta_info *sta;

		अगर (rc < 3) अणु
			wil_err(wil,
				"BACK: del_rx require at least 2 params\n");
			वापस -EINVAL;
		पूर्ण
		अगर (p1 < 0 || p1 >= wil->max_assoc_sta) अणु
			wil_err(wil, "BACK: invalid CID %d\n", p1);
			वापस -EINVAL;
		पूर्ण
		अगर (rc < 4)
			p3 = WLAN_REASON_QSTA_LEAVE_QBSS;
		sta = &wil->sta[p1];
		wmi_delba_rx(wil, sta->mid, p1, p2, p3);
	पूर्ण अन्यथा अणु
		wil_err(wil, "BACK: Unrecognized command \"%s\"\n", cmd);
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार wil_पढ़ो_back(काष्ठा file *file, अक्षर __user *user_buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	अटल स्थिर अक्षर text[] = "block ack control, write:\n"
	" - \"add <ringid> <agg_size> <timeout>\" to trigger ADDBA\n"
	"If missing, <timeout> defaults to 0\n"
	" - \"del_tx <ringid> <reason>\" to trigger DELBA for Tx side\n"
	" - \"del_rx <CID> <TID> <reason>\" to trigger DELBA for Rx side\n"
	"If missing, <reason> set to \"STA_LEAVING\" (36)\n";

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, text,
				       माप(text));
पूर्ण

अटल स्थिर काष्ठा file_operations fops_back = अणु
	.पढ़ो = wil_पढ़ो_back,
	.ग_लिखो = wil_ग_लिखो_back,
	.खोलो  = simple_खोलो,
पूर्ण;

/* pmc control, ग_लिखो:
 * - "alloc <num descriptors> <descriptor_size>" to allocate PMC
 * - "free" to release memory allocated क्रम PMC
 */
अटल sमाप_प्रकार wil_ग_लिखो_pmccfg(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	पूर्णांक rc;
	अक्षर *kbuf = kदो_स्मृति(len + 1, GFP_KERNEL);
	अक्षर cmd[9];
	पूर्णांक num_descs, desc_size;

	अगर (!kbuf)
		वापस -ENOMEM;

	rc = simple_ग_लिखो_to_buffer(kbuf, len, ppos, buf, len);
	अगर (rc != len) अणु
		kमुक्त(kbuf);
		वापस rc >= 0 ? -EIO : rc;
	पूर्ण

	kbuf[len] = '\0';
	rc = माला_पूछो(kbuf, "%8s %d %d", cmd, &num_descs, &desc_size);
	kमुक्त(kbuf);

	अगर (rc < 0)
		वापस rc;

	अगर (rc < 1) अणु
		wil_err(wil, "pmccfg: no params given\n");
		वापस -EINVAL;
	पूर्ण

	अगर (0 == म_भेद(cmd, "alloc")) अणु
		अगर (rc != 3) अणु
			wil_err(wil, "pmccfg: alloc requires 2 params\n");
			वापस -EINVAL;
		पूर्ण
		wil_pmc_alloc(wil, num_descs, desc_size);
	पूर्ण अन्यथा अगर (0 == म_भेद(cmd, "free")) अणु
		अगर (rc != 1) अणु
			wil_err(wil, "pmccfg: free does not have any params\n");
			वापस -EINVAL;
		पूर्ण
		wil_pmc_मुक्त(wil, true);
	पूर्ण अन्यथा अणु
		wil_err(wil, "pmccfg: Unrecognized command \"%s\"\n", cmd);
		वापस -EINVAL;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार wil_पढ़ो_pmccfg(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	अक्षर text[256];
	अक्षर help[] = "pmc control, write:\n"
	" - \"alloc <num descriptors> <descriptor_size>\" to allocate pmc\n"
	" - \"free\" to free memory allocated for pmc\n";

	snम_लिखो(text, माप(text), "Last command status: %d\n\n%s",
		 wil_pmc_last_cmd_status(wil), help);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, text,
				       म_माप(text) + 1);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_pmccfg = अणु
	.पढ़ो = wil_पढ़ो_pmccfg,
	.ग_लिखो = wil_ग_लिखो_pmccfg,
	.खोलो  = simple_खोलो,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_pmcdata = अणु
	.खोलो		= simple_खोलो,
	.पढ़ो		= wil_pmc_पढ़ो,
	.llseek		= wil_pmc_llseek,
पूर्ण;

अटल पूर्णांक wil_pmcring_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_pmcring_पढ़ो, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_pmcring = अणु
	.खोलो		= wil_pmcring_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
पूर्ण;

/*---tx_mgmt---*/
/* Write mgmt frame to this file to send it */
अटल sमाप_प्रकार wil_ग_लिखो_file_txmgmt(काष्ठा file *file, स्थिर अक्षर __user *buf,
				     माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	काष्ठा wireless_dev *wdev = wil->मुख्य_ndev->ieee80211_ptr;
	काष्ठा cfg80211_mgmt_tx_params params;
	पूर्णांक rc;
	व्योम *frame;

	स_रखो(&params, 0, माप(params));

	अगर (!len)
		वापस -EINVAL;

	frame = memdup_user(buf, len);
	अगर (IS_ERR(frame))
		वापस PTR_ERR(frame);

	params.buf = frame;
	params.len = len;

	rc = wil_cfg80211_mgmt_tx(wiphy, wdev, &params, शून्य);

	kमुक्त(frame);
	wil_info(wil, "-> %d\n", rc);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_txmgmt = अणु
	.ग_लिखो = wil_ग_लिखो_file_txmgmt,
	.खोलो  = simple_खोलो,
पूर्ण;

/* Write WMI command (w/o mbox header) to this file to send it
 * WMI starts from wil6210_mbox_hdr_wmi header
 */
अटल sमाप_प्रकार wil_ग_लिखो_file_wmi(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_cmd_hdr *wmi;
	व्योम *cmd;
	पूर्णांक cmdlen = len - माप(काष्ठा wmi_cmd_hdr);
	u16 cmdid;
	पूर्णांक rc, rc1;

	अगर (cmdlen < 0)
		वापस -EINVAL;

	wmi = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!wmi)
		वापस -ENOMEM;

	rc = simple_ग_लिखो_to_buffer(wmi, len, ppos, buf, len);
	अगर (rc < 0) अणु
		kमुक्त(wmi);
		वापस rc;
	पूर्ण

	cmd = (cmdlen > 0) ? &wmi[1] : शून्य;
	cmdid = le16_to_cpu(wmi->command_id);

	rc1 = wmi_send(wil, cmdid, vअगर->mid, cmd, cmdlen);
	kमुक्त(wmi);

	wil_info(wil, "0x%04x[%d] -> %d\n", cmdid, cmdlen, rc1);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_wmi = अणु
	.ग_लिखो = wil_ग_लिखो_file_wmi,
	.खोलो  = simple_खोलो,
पूर्ण;

अटल व्योम wil_seq_prपूर्णांक_skb(काष्ठा seq_file *s, काष्ठा sk_buff *skb)
अणु
	पूर्णांक i = 0;
	पूर्णांक len = skb_headlen(skb);
	व्योम *p = skb->data;
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;

	seq_म_लिखो(s, "    len = %d\n", len);
	wil_seq_hexdump(s, p, len, "      : ");

	अगर (nr_frags) अणु
		seq_म_लिखो(s, "    nr_frags = %d\n", nr_frags);
		क्रम (i = 0; i < nr_frags; i++) अणु
			स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

			len = skb_frag_size(frag);
			p = skb_frag_address_safe(frag);
			seq_म_लिखो(s, "    [%2d] : len = %d\n", i, len);
			wil_seq_hexdump(s, p, len, "      : ");
		पूर्ण
	पूर्ण
पूर्ण

/*---------Tx/Rx descriptor------------*/
अटल पूर्णांक txdesc_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil_ring *ring;
	bool tx;
	पूर्णांक ring_idx = dbg_ring_index;
	पूर्णांक txdesc_idx = dbg_txdesc_index;
	अस्थिर काष्ठा vring_tx_desc *d;
	अस्थिर u32 *u;
	काष्ठा sk_buff *skb;

	अगर (wil->use_enhanced_dma_hw) अणु
		/* RX ring index == 0 */
		अगर (ring_idx >= WIL6210_MAX_TX_RINGS) अणु
			seq_म_लिखो(s, "invalid ring index %d\n", ring_idx);
			वापस 0;
		पूर्ण
		tx = ring_idx > 0; /* desc ring 0 is reserved क्रम RX */
	पूर्ण अन्यथा अणु
		/* RX ring index == WIL6210_MAX_TX_RINGS */
		अगर (ring_idx > WIL6210_MAX_TX_RINGS) अणु
			seq_म_लिखो(s, "invalid ring index %d\n", ring_idx);
			वापस 0;
		पूर्ण
		tx = (ring_idx < WIL6210_MAX_TX_RINGS);
	पूर्ण

	ring = tx ? &wil->ring_tx[ring_idx] : &wil->ring_rx;

	अगर (!ring->va) अणु
		अगर (tx)
			seq_म_लिखो(s, "No Tx[%2d] RING\n", ring_idx);
		अन्यथा
			seq_माला_दो(s, "No Rx RING\n");
		वापस 0;
	पूर्ण

	अगर (txdesc_idx >= ring->size) अणु
		अगर (tx)
			seq_म_लिखो(s, "[%2d] TxDesc index (%d) >= size (%d)\n",
				   ring_idx, txdesc_idx, ring->size);
		अन्यथा
			seq_म_लिखो(s, "RxDesc index (%d) >= size (%d)\n",
				   txdesc_idx, ring->size);
		वापस 0;
	पूर्ण

	/* use काष्ठा vring_tx_desc क्रम Rx as well,
	 * only field used, .dma.length, is the same
	 */
	d = &ring->va[txdesc_idx].tx.legacy;
	u = (अस्थिर u32 *)d;
	skb = शून्य;

	अगर (wil->use_enhanced_dma_hw) अणु
		अगर (tx) अणु
			skb = ring->ctx ? ring->ctx[txdesc_idx].skb : शून्य;
		पूर्ण अन्यथा अगर (wil->rx_buff_mgmt.buff_arr) अणु
			काष्ठा wil_rx_enhanced_desc *rx_d =
				(काष्ठा wil_rx_enhanced_desc *)
				&ring->va[txdesc_idx].rx.enhanced;
			u16 buff_id = le16_to_cpu(rx_d->mac.buff_id);

			अगर (!wil_val_in_range(buff_id, 0,
					      wil->rx_buff_mgmt.size))
				seq_म_लिखो(s, "invalid buff_id %d\n", buff_id);
			अन्यथा
				skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = ring->ctx[txdesc_idx].skb;
	पूर्ण
	अगर (tx)
		seq_म_लिखो(s, "Tx[%2d][%3d] = {\n", ring_idx,
			   txdesc_idx);
	अन्यथा
		seq_म_लिखो(s, "Rx[%3d] = {\n", txdesc_idx);
	seq_म_लिखो(s, "  MAC = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	seq_म_लिखो(s, "  DMA = 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[4], u[5], u[6], u[7]);
	seq_म_लिखो(s, "  SKB = 0x%p\n", skb);

	अगर (skb) अणु
		skb_get(skb);
		wil_seq_prपूर्णांक_skb(s, skb);
		kमुक्त_skb(skb);
	पूर्ण
	seq_माला_दो(s, "}\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(txdesc);

/*---------Tx/Rx status message------------*/
अटल पूर्णांक status_msg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक sring_idx = dbg_sring_index;
	काष्ठा wil_status_ring *sring;
	bool tx;
	u32 status_msg_idx = dbg_status_msg_index;
	u32 *u;

	अगर (sring_idx >= WIL6210_MAX_STATUS_RINGS) अणु
		seq_म_लिखो(s, "invalid status ring index %d\n", sring_idx);
		वापस 0;
	पूर्ण

	sring = &wil->srings[sring_idx];
	tx = !sring->is_rx;

	अगर (!sring->va) अणु
		seq_म_लिखो(s, "No %cX status ring\n", tx ? 'T' : 'R');
		वापस 0;
	पूर्ण

	अगर (status_msg_idx >= sring->size) अणु
		seq_म_लिखो(s, "%cxDesc index (%d) >= size (%d)\n",
			   tx ? 'T' : 'R', status_msg_idx, sring->size);
		वापस 0;
	पूर्ण

	u = sring->va + (sring->elem_size * status_msg_idx);

	seq_म_लिखो(s, "%cx[%d][%3d] = {\n",
		   tx ? 'T' : 'R', sring_idx, status_msg_idx);

	seq_म_लिखो(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
		   u[0], u[1], u[2], u[3]);
	अगर (!tx && !wil->use_compressed_rx_status)
		seq_म_लिखो(s, "  0x%08x 0x%08x 0x%08x 0x%08x\n",
			   u[4], u[5], u[6], u[7]);

	seq_माला_दो(s, "}\n");

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(status_msg);

अटल पूर्णांक wil_prपूर्णांक_rx_buff(काष्ठा seq_file *s, काष्ठा list_head *lh)
अणु
	काष्ठा wil_rx_buff *it;
	पूर्णांक i = 0;

	list_क्रम_each_entry(it, lh, list) अणु
		अगर ((i % 16) == 0 && i != 0)
			seq_माला_दो(s, "\n    ");
		seq_म_लिखो(s, "[%4d] ", it->id);
		i++;
	पूर्ण
	seq_म_लिखो(s, "\nNumber of buffers: %u\n", i);

	वापस i;
पूर्ण

अटल पूर्णांक rx_buff_mgmt_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil_rx_buff_mgmt *rbm = &wil->rx_buff_mgmt;
	पूर्णांक num_active;
	पूर्णांक num_मुक्त;

	अगर (!rbm->buff_arr)
		वापस -EINVAL;

	seq_म_लिखो(s, "  size = %zu\n", rbm->size);
	seq_म_लिखो(s, "  free_list_empty_cnt = %lu\n",
		   rbm->मुक्त_list_empty_cnt);

	/* Prपूर्णांक active list */
	seq_माला_दो(s, "  Active list:\n");
	num_active = wil_prपूर्णांक_rx_buff(s, &rbm->active);
	seq_माला_दो(s, "\n  Free list:\n");
	num_मुक्त = wil_prपूर्णांक_rx_buff(s, &rbm->मुक्त);

	seq_म_लिखो(s, "  Total number of buffers: %u\n",
		   num_active + num_मुक्त);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(rx_buff_mgmt);

/*---------beamक्रमming------------*/
अटल अक्षर *wil_bख_स्थितिus_str(u32 status)
अणु
	चयन (status) अणु
	हाल 0:
		वापस "Failed";
	हाल 1:
		वापस "OK";
	हाल 2:
		वापस "Retrying";
	शेष:
		वापस "??";
	पूर्ण
पूर्ण

अटल bool is_all_zeros(व्योम * स्थिर x_, माप_प्रकार sz)
अणु
	/* अगर reply is all-0, ignore this CID */
	u32 *x = x_;
	पूर्णांक n;

	क्रम (n = 0; n < sz / माप(*x); n++)
		अगर (x[n])
			वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक bf_show(काष्ठा seq_file *s, व्योम *data)
अणु
	पूर्णांक rc;
	पूर्णांक i;
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);
	काष्ठा wmi_notअगरy_req_cmd cmd = अणु
		.पूर्णांकerval_usec = 0,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_notअगरy_req_करोne_event evt;
	पूर्ण __packed reply;

	स_रखो(&reply, 0, माप(reply));

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		u32 status;
		u8 bf_mcs;

		cmd.cid = i;
		rc = wmi_call(wil, WMI_NOTIFY_REQ_CMDID, vअगर->mid,
			      &cmd, माप(cmd),
			      WMI_NOTIFY_REQ_DONE_EVENTID, &reply,
			      माप(reply), WIL_WMI_CALL_GENERAL_TO_MS);
		/* अगर reply is all-0, ignore this CID */
		अगर (rc || is_all_zeros(&reply.evt, माप(reply.evt)))
			जारी;

		status = le32_to_cpu(reply.evt.status);
		bf_mcs = le16_to_cpu(reply.evt.bf_mcs);
		seq_म_लिखो(s, "CID %d {\n"
			   "  TSF = 0x%016llx\n"
			   "  TxMCS = %s TxTpt = %4d\n"
			   "  SQI = %4d\n"
			   "  RSSI = %4d\n"
			   "  Status = 0x%08x %s\n"
			   "  Sectors(rx:tx) my %2d:%2d peer %2d:%2d\n"
			   "  Goodput(rx:tx) %4d:%4d\n"
			   "}\n",
			   i,
			   le64_to_cpu(reply.evt.tsf),
			   WIL_EXTENDED_MCS_CHECK(bf_mcs),
			   le32_to_cpu(reply.evt.tx_tpt),
			   reply.evt.sqi,
			   reply.evt.rssi,
			   status, wil_bख_स्थितिus_str(status),
			   le16_to_cpu(reply.evt.my_rx_sector),
			   le16_to_cpu(reply.evt.my_tx_sector),
			   le16_to_cpu(reply.evt.other_rx_sector),
			   le16_to_cpu(reply.evt.other_tx_sector),
			   le32_to_cpu(reply.evt.rx_goodput),
			   le32_to_cpu(reply.evt.tx_goodput));
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(bf);

/*---------temp------------*/
अटल व्योम prपूर्णांक_temp(काष्ठा seq_file *s, स्थिर अक्षर *prefix, s32 t)
अणु
	चयन (t) अणु
	हाल 0:
	हाल WMI_INVALID_TEMPERATURE:
		seq_म_लिखो(s, "%s N/A\n", prefix);
	अवरोध;
	शेष:
		seq_म_लिखो(s, "%s %s%d.%03d\n", prefix, (t < 0 ? "-" : ""),
			   असल(t / 1000), असल(t % 1000));
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक temp_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक rc, i;

	अगर (test_bit(WMI_FW_CAPABILITY_TEMPERATURE_ALL_RF,
		     wil->fw_capabilities)) अणु
		काष्ठा wmi_temp_sense_all_करोne_event sense_all_evt;

		wil_dbg_misc(wil,
			     "WMI_FW_CAPABILITY_TEMPERATURE_ALL_RF is supported");
		rc = wmi_get_all_temperatures(wil, &sense_all_evt);
		अगर (rc) अणु
			seq_माला_दो(s, "Failed\n");
			वापस 0;
		पूर्ण
		prपूर्णांक_temp(s, "T_mac   =",
			   le32_to_cpu(sense_all_evt.baseband_t1000));
		seq_म_लिखो(s, "Connected RFs [0x%08x]\n",
			   sense_all_evt.rf_biपंचांगap);
		क्रम (i = 0; i < WMI_MAX_XIF_PORTS_NUM; i++) अणु
			seq_म_लिखो(s, "RF[%d]   = ", i);
			prपूर्णांक_temp(s, "",
				   le32_to_cpu(sense_all_evt.rf_t1000[i]));
		पूर्ण
	पूर्ण अन्यथा अणु
		s32 t_m, t_r;

		wil_dbg_misc(wil,
			     "WMI_FW_CAPABILITY_TEMPERATURE_ALL_RF is not supported");
		rc = wmi_get_temperature(wil, &t_m, &t_r);
		अगर (rc) अणु
			seq_माला_दो(s, "Failed\n");
			वापस 0;
		पूर्ण
		prपूर्णांक_temp(s, "T_mac   =", t_m);
		prपूर्णांक_temp(s, "T_radio =", t_r);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(temp);

/*---------freq------------*/
अटल पूर्णांक freq_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wireless_dev *wdev = wil->मुख्य_ndev->ieee80211_ptr;
	u32 freq = wdev->chandef.chan ? wdev->chandef.chan->center_freq : 0;

	seq_म_लिखो(s, "Freq = %d\n", freq);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(freq);

/*---------link------------*/
अटल पूर्णांक link_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा station_info *sinfo;
	पूर्णांक i, rc = 0;

	sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
	अगर (!sinfo)
		वापस -ENOMEM;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		काष्ठा wil_sta_info *p = &wil->sta[i];
		अक्षर *status = "unknown";
		काष्ठा wil6210_vअगर *vअगर;
		u8 mid;

		चयन (p->status) अणु
		हाल wil_sta_unused:
			status = "unused   ";
			अवरोध;
		हाल wil_sta_conn_pending:
			status = "pending  ";
			अवरोध;
		हाल wil_sta_connected:
			status = "connected";
			अवरोध;
		पूर्ण
		mid = (p->status != wil_sta_unused) ? p->mid : U8_MAX;
		seq_म_लिखो(s, "[%d][MID %d] %pM %s\n",
			   i, mid, p->addr, status);

		अगर (p->status != wil_sta_connected)
			जारी;

		vअगर = (mid < GET_MAX_VIFS(wil)) ? wil->vअगरs[mid] : शून्य;
		अगर (vअगर) अणु
			rc = wil_cid_fill_sinfo(vअगर, i, sinfo);
			अगर (rc)
				जाओ out;

			seq_म_लिखो(s, "  Tx_mcs = %s\n",
				   WIL_EXTENDED_MCS_CHECK(sinfo->txrate.mcs));
			seq_म_लिखो(s, "  Rx_mcs = %s\n",
				   WIL_EXTENDED_MCS_CHECK(sinfo->rxrate.mcs));
			seq_म_लिखो(s, "  SQ     = %d\n", sinfo->संकेत);
		पूर्ण अन्यथा अणु
			seq_माला_दो(s, "  INVALID MID\n");
		पूर्ण
	पूर्ण

out:
	kमुक्त(sinfo);
	वापस rc;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(link);

/*---------info------------*/
अटल पूर्णांक info_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	पूर्णांक is_ac = घातer_supply_is_प्रणाली_supplied();
	पूर्णांक rx = atomic_xchg(&wil->isr_count_rx, 0);
	पूर्णांक tx = atomic_xchg(&wil->isr_count_tx, 0);
	अटल uदीर्घ rxf_old, txf_old;
	uदीर्घ rxf = ndev->stats.rx_packets;
	uदीर्घ txf = ndev->stats.tx_packets;
	अचिन्हित पूर्णांक i;

	/* >0 : AC; 0 : battery; <0 : error */
	seq_म_लिखो(s, "AC powered : %d\n", is_ac);
	seq_म_लिखो(s, "Rx irqs:packets : %8d : %8ld\n", rx, rxf - rxf_old);
	seq_म_लिखो(s, "Tx irqs:packets : %8d : %8ld\n", tx, txf - txf_old);
	rxf_old = rxf;
	txf_old = txf;

#घोषणा CHECK_QSTATE(x) (state & BIT(__QUEUE_STATE_ ## x)) ? \
	" " __stringअगरy(x) : ""

	क्रम (i = 0; i < ndev->num_tx_queues; i++) अणु
		काष्ठा netdev_queue *txq = netdev_get_tx_queue(ndev, i);
		अचिन्हित दीर्घ state = txq->state;

		seq_म_लिखो(s, "Tx queue[%i] state : 0x%lx%s%s%s\n", i, state,
			   CHECK_QSTATE(DRV_XOFF),
			   CHECK_QSTATE(STACK_XOFF),
			   CHECK_QSTATE(FROZEN)
			  );
	पूर्ण
#अघोषित CHECK_QSTATE
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(info);

/*---------recovery------------*/
/* mode = [manual|स्वतः]
 * state = [idle|pending|running]
 */
अटल sमाप_प्रकार wil_पढ़ो_file_recovery(काष्ठा file *file, अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	अक्षर buf[80];
	पूर्णांक n;
	अटल स्थिर अक्षर * स्थिर sstate[] = अणु"idle", "pending", "running"पूर्ण;

	n = snम_लिखो(buf, माप(buf), "mode = %s\nstate = %s\n",
		     no_fw_recovery ? "manual" : "auto",
		     sstate[wil->recovery_state]);

	n = min_t(पूर्णांक, n, माप(buf));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       buf, n);
पूर्ण

अटल sमाप_प्रकार wil_ग_लिखो_file_recovery(काष्ठा file *file,
				       स्थिर अक्षर __user *buf_,
				       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	अटल स्थिर अक्षर run_command[] = "run";
	अक्षर buf[माप(run_command) + 1]; /* to detect "runx" */
	sमाप_प्रकार rc;

	अगर (wil->recovery_state != fw_recovery_pending) अणु
		wil_err(wil, "No recovery pending\n");
		वापस -EINVAL;
	पूर्ण

	अगर (*ppos != 0) अणु
		wil_err(wil, "Offset [%d]\n", (पूर्णांक)*ppos);
		वापस -EINVAL;
	पूर्ण

	अगर (count > माप(buf)) अणु
		wil_err(wil, "Input too long, len = %d\n", (पूर्णांक)count);
		वापस -EINVAL;
	पूर्ण

	rc = simple_ग_लिखो_to_buffer(buf, माप(buf) - 1, ppos, buf_, count);
	अगर (rc < 0)
		वापस rc;

	buf[rc] = '\0';
	अगर (0 == म_भेद(buf, run_command))
		wil_set_recovery_state(wil, fw_recovery_running);
	अन्यथा
		wil_err(wil, "Bad recovery command \"%s\"\n", buf);

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_recovery = अणु
	.पढ़ो = wil_पढ़ो_file_recovery,
	.ग_लिखो = wil_ग_लिखो_file_recovery,
	.खोलो  = simple_खोलो,
पूर्ण;

/*---------Station matrix------------*/
अटल व्योम wil_prपूर्णांक_rxtid(काष्ठा seq_file *s, काष्ठा wil_tid_ampdu_rx *r)
अणु
	पूर्णांक i;
	u16 index = ((r->head_seq_num - r->ssn) & 0xfff) % r->buf_size;
	अचिन्हित दीर्घ दीर्घ drop_dup = r->drop_dup, drop_old = r->drop_old;
	अचिन्हित दीर्घ दीर्घ drop_dup_mcast = r->drop_dup_mcast;

	seq_म_लिखो(s, "([%2d]) 0x%03x [", r->buf_size, r->head_seq_num);
	क्रम (i = 0; i < r->buf_size; i++) अणु
		अगर (i == index)
			seq_म_लिखो(s, "%c", r->reorder_buf[i] ? 'O' : '|');
		अन्यथा
			seq_म_लिखो(s, "%c", r->reorder_buf[i] ? '*' : '_');
	पूर्ण
	seq_म_लिखो(s,
		   "] total %llu drop %llu (dup %llu + old %llu + dup mcast %llu) last 0x%03x\n",
		   r->total, drop_dup + drop_old + drop_dup_mcast, drop_dup,
		   drop_old, drop_dup_mcast, r->ssn_last_drop);
पूर्ण

अटल व्योम wil_prपूर्णांक_rxtid_crypto(काष्ठा seq_file *s, पूर्णांक tid,
				   काष्ठा wil_tid_crypto_rx *c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा wil_tid_crypto_rx_single *cc = &c->key_id[i];

		अगर (cc->key_set)
			जाओ has_keys;
	पूर्ण
	वापस;

has_keys:
	अगर (tid < WIL_STA_TID_NUM)
		seq_म_लिखो(s, "  [%2d] PN", tid);
	अन्यथा
		seq_माला_दो(s, "  [GR] PN");

	क्रम (i = 0; i < 4; i++) अणु
		काष्ठा wil_tid_crypto_rx_single *cc = &c->key_id[i];

		seq_म_लिखो(s, " [%i%s]%6phN", i, cc->key_set ? "+" : "-",
			   cc->pn);
	पूर्ण
	seq_माला_दो(s, "\n");
पूर्ण

अटल पूर्णांक sta_show(काष्ठा seq_file *s, व्योम *data)
__acquires(&p->tid_rx_lock) __releases(&p->tid_rx_lock)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक i, tid, mcs;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		काष्ठा wil_sta_info *p = &wil->sta[i];
		अक्षर *status = "unknown";
		u8 aid = 0;
		u8 mid;
		bool sta_connected = false;

		चयन (p->status) अणु
		हाल wil_sta_unused:
			status = "unused   ";
			अवरोध;
		हाल wil_sta_conn_pending:
			status = "pending  ";
			अवरोध;
		हाल wil_sta_connected:
			status = "connected";
			aid = p->aid;
			अवरोध;
		पूर्ण
		mid = (p->status != wil_sta_unused) ? p->mid : U8_MAX;
		अगर (mid < GET_MAX_VIFS(wil)) अणु
			काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[mid];

			अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION &&
			    p->status == wil_sta_connected)
				sta_connected = true;
		पूर्ण
		/* prपूर्णांक roam counter only क्रम connected stations */
		अगर (sta_connected)
			seq_म_लिखो(s, "[%d] %pM connected (roam counter %d) MID %d AID %d\n",
				   i, p->addr, p->stats.ft_roams, mid, aid);
		अन्यथा
			seq_म_लिखो(s, "[%d] %pM %s MID %d AID %d\n", i,
				   p->addr, status, mid, aid);

		अगर (p->status == wil_sta_connected) अणु
			spin_lock_bh(&p->tid_rx_lock);
			क्रम (tid = 0; tid < WIL_STA_TID_NUM; tid++) अणु
				काष्ठा wil_tid_ampdu_rx *r = p->tid_rx[tid];
				काष्ठा wil_tid_crypto_rx *c =
						&p->tid_crypto_rx[tid];

				अगर (r) अणु
					seq_म_लिखो(s, "  [%2d] ", tid);
					wil_prपूर्णांक_rxtid(s, r);
				पूर्ण

				wil_prपूर्णांक_rxtid_crypto(s, tid, c);
			पूर्ण
			wil_prपूर्णांक_rxtid_crypto(s, WIL_STA_TID_NUM,
					       &p->group_crypto_rx);
			spin_unlock_bh(&p->tid_rx_lock);
			seq_म_लिखो(s,
				   "Rx invalid frame: non-data %lu, short %lu, large %lu, replay %lu\n",
				   p->stats.rx_non_data_frame,
				   p->stats.rx_लघु_frame,
				   p->stats.rx_large_frame,
				   p->stats.rx_replay);
			seq_म_लिखो(s,
				   "mic error %lu, key error %lu, amsdu error %lu, csum error %lu\n",
				   p->stats.rx_mic_error,
				   p->stats.rx_key_error,
				   p->stats.rx_amsdu_error,
				   p->stats.rx_csum_err);

			seq_माला_दो(s, "Rx/MCS:");
			क्रम (mcs = 0; mcs < ARRAY_SIZE(p->stats.rx_per_mcs);
			     mcs++)
				seq_म_लिखो(s, " %lld",
					   p->stats.rx_per_mcs[mcs]);
			seq_माला_दो(s, "\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sta);

अटल पूर्णांक mids_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev;
	पूर्णांक i;

	mutex_lock(&wil->vअगर_mutex);
	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];

		अगर (vअगर) अणु
			ndev = vअगर_to_ndev(vअगर);
			seq_म_लिखो(s, "[%d] %pM %s\n", i, ndev->dev_addr,
				   ndev->name);
		पूर्ण अन्यथा अणु
			seq_म_लिखो(s, "[%d] unused\n", i);
		पूर्ण
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(mids);

अटल पूर्णांक wil_tx_latency_debugfs_show(काष्ठा seq_file *s, व्योम *data)
__acquires(&p->tid_rx_lock) __releases(&p->tid_rx_lock)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक i, bin;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		काष्ठा wil_sta_info *p = &wil->sta[i];
		अक्षर *status = "unknown";
		u8 aid = 0;
		u8 mid;

		अगर (!p->tx_latency_bins)
			जारी;

		चयन (p->status) अणु
		हाल wil_sta_unused:
			status = "unused   ";
			अवरोध;
		हाल wil_sta_conn_pending:
			status = "pending  ";
			अवरोध;
		हाल wil_sta_connected:
			status = "connected";
			aid = p->aid;
			अवरोध;
		पूर्ण
		mid = (p->status != wil_sta_unused) ? p->mid : U8_MAX;
		seq_म_लिखो(s, "[%d] %pM %s MID %d AID %d\n", i, p->addr, status,
			   mid, aid);

		अगर (p->status == wil_sta_connected) अणु
			u64 num_packets = 0;
			u64 tx_latency_avg = p->stats.tx_latency_total_us;

			seq_माला_दो(s, "Tx/Latency bin:");
			क्रम (bin = 0; bin < WIL_NUM_LATENCY_BINS; bin++) अणु
				seq_म_लिखो(s, " %lld",
					   p->tx_latency_bins[bin]);
				num_packets += p->tx_latency_bins[bin];
			पूर्ण
			seq_माला_दो(s, "\n");
			अगर (!num_packets)
				जारी;
			करो_भाग(tx_latency_avg, num_packets);
			seq_म_लिखो(s, "Tx/Latency min/avg/max (us): %d/%lld/%d",
				   p->stats.tx_latency_min_us,
				   tx_latency_avg,
				   p->stats.tx_latency_max_us);

			seq_माला_दो(s, "\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wil_tx_latency_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_tx_latency_debugfs_show,
			   inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार wil_tx_latency_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक val, rc, i;
	bool enable;

	rc = kstrtoपूर्णांक_from_user(buf, len, 0, &val);
	अगर (rc) अणु
		wil_err(wil, "Invalid argument\n");
		वापस rc;
	पूर्ण
	अगर (val == 1)
		/* शेष resolution */
		val = 500;
	अगर (val && (val < 50 || val > 1000)) अणु
		wil_err(wil, "Invalid resolution %d\n", val);
		वापस -EINVAL;
	पूर्ण

	enable = !!val;
	अगर (wil->tx_latency == enable)
		वापस len;

	wil_info(wil, "%s TX latency measurements (resolution %dusec)\n",
		 enable ? "Enabling" : "Disabling", val);

	अगर (enable) अणु
		माप_प्रकार sz = माप(u64) * WIL_NUM_LATENCY_BINS;

		wil->tx_latency_res = val;
		क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
			काष्ठा wil_sta_info *sta = &wil->sta[i];

			kमुक्त(sta->tx_latency_bins);
			sta->tx_latency_bins = kzalloc(sz, GFP_KERNEL);
			अगर (!sta->tx_latency_bins)
				वापस -ENOMEM;
			sta->stats.tx_latency_min_us = U32_MAX;
			sta->stats.tx_latency_max_us = 0;
			sta->stats.tx_latency_total_us = 0;
		पूर्ण
	पूर्ण
	wil->tx_latency = enable;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_tx_latency = अणु
	.खोलो		= wil_tx_latency_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= wil_tx_latency_ग_लिखो,
	.llseek		= seq_lseek,
पूर्ण;

अटल व्योम wil_link_stats_prपूर्णांक_basic(काष्ठा wil6210_vअगर *vअगर,
				       काष्ठा seq_file *s,
				       काष्ठा wmi_link_stats_basic *basic)
अणु
	अक्षर per[5] = "?";

	अगर (basic->per_average != 0xff)
		snम_लिखो(per, माप(per), "%d%%", basic->per_average);

	seq_म_लिखो(s, "CID %d {\n"
		   "\tTxMCS %s TxTpt %d\n"
		   "\tGoodput(rx:tx) %d:%d\n"
		   "\tRxBcastFrames %d\n"
		   "\tRSSI %d SQI %d SNR %d PER %s\n"
		   "\tRx RFC %d Ant num %d\n"
		   "\tSectors(rx:tx) my %d:%d peer %d:%d\n"
		   "}\n",
		   basic->cid,
		   WIL_EXTENDED_MCS_CHECK(basic->bf_mcs),
		   le32_to_cpu(basic->tx_tpt),
		   le32_to_cpu(basic->rx_goodput),
		   le32_to_cpu(basic->tx_goodput),
		   le32_to_cpu(basic->rx_bcast_frames),
		   basic->rssi, basic->sqi, basic->snr, per,
		   basic->selected_rfc, basic->rx_effective_ant_num,
		   basic->my_rx_sector, basic->my_tx_sector,
		   basic->other_rx_sector, basic->other_tx_sector);
पूर्ण

अटल व्योम wil_link_stats_prपूर्णांक_global(काष्ठा wil6210_priv *wil,
					काष्ठा seq_file *s,
					काष्ठा wmi_link_stats_global *global)
अणु
	seq_म_लिखो(s, "Frames(rx:tx) %d:%d\n"
		   "BA Frames(rx:tx) %d:%d\n"
		   "Beacons %d\n"
		   "Rx Errors (MIC:CRC) %d:%d\n"
		   "Tx Errors (no ack) %d\n",
		   le32_to_cpu(global->rx_frames),
		   le32_to_cpu(global->tx_frames),
		   le32_to_cpu(global->rx_ba_frames),
		   le32_to_cpu(global->tx_ba_frames),
		   le32_to_cpu(global->tx_beacons),
		   le32_to_cpu(global->rx_mic_errors),
		   le32_to_cpu(global->rx_crc_errors),
		   le32_to_cpu(global->tx_fail_no_ack));
पूर्ण

अटल व्योम wil_link_stats_debugfs_show_vअगर(काष्ठा wil6210_vअगर *vअगर,
					    काष्ठा seq_file *s)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_link_stats_basic *stats;
	पूर्णांक i;

	अगर (!vअगर->fw_stats_पढ़ोy) अणु
		seq_माला_दो(s, "no statistics\n");
		वापस;
	पूर्ण

	seq_म_लिखो(s, "TSF %lld\n", vअगर->fw_stats_tsf);
	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		अगर (wil->sta[i].status == wil_sta_unused)
			जारी;
		अगर (wil->sta[i].mid != vअगर->mid)
			जारी;

		stats = &wil->sta[i].fw_stats_basic;
		wil_link_stats_prपूर्णांक_basic(vअगर, s, stats);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_link_stats_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;
	काष्ठा wil6210_vअगर *vअगर;
	पूर्णांक i, rc;

	rc = mutex_lock_पूर्णांकerruptible(&wil->vअगर_mutex);
	अगर (rc)
		वापस rc;

	/* iterate over all MIDs and show per-cid statistics. Then show the
	 * global statistics
	 */
	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];

		seq_म_लिखो(s, "MID %d ", i);
		अगर (!vअगर) अणु
			seq_माला_दो(s, "unused\n");
			जारी;
		पूर्ण

		wil_link_stats_debugfs_show_vअगर(vअगर, s);
	पूर्ण

	mutex_unlock(&wil->vअगर_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_link_stats_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_link_stats_debugfs_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार wil_link_stats_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक cid, पूर्णांकerval, rc, i;
	काष्ठा wil6210_vअगर *vअगर;
	अक्षर *kbuf = kदो_स्मृति(len + 1, GFP_KERNEL);

	अगर (!kbuf)
		वापस -ENOMEM;

	rc = simple_ग_लिखो_to_buffer(kbuf, len, ppos, buf, len);
	अगर (rc != len) अणु
		kमुक्त(kbuf);
		वापस rc >= 0 ? -EIO : rc;
	पूर्ण

	kbuf[len] = '\0';
	/* specअगरy cid (use -1 क्रम all cids) and snapshot पूर्णांकerval in ms */
	rc = माला_पूछो(kbuf, "%d %d", &cid, &पूर्णांकerval);
	kमुक्त(kbuf);
	अगर (rc < 0)
		वापस rc;
	अगर (rc < 2 || पूर्णांकerval < 0)
		वापस -EINVAL;

	wil_info(wil, "request link statistics, cid %d interval %d\n",
		 cid, पूर्णांकerval);

	rc = mutex_lock_पूर्णांकerruptible(&wil->vअगर_mutex);
	अगर (rc)
		वापस rc;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		vअगर = wil->vअगरs[i];
		अगर (!vअगर)
			जारी;

		rc = wmi_link_stats_cfg(vअगर, WMI_LINK_STATS_TYPE_BASIC,
					(cid == -1 ? 0xff : cid), पूर्णांकerval);
		अगर (rc)
			wil_err(wil, "link statistics failed for mid %d\n", i);
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_link_stats = अणु
	.खोलो		= wil_link_stats_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= wil_link_stats_ग_लिखो,
	.llseek		= seq_lseek,
पूर्ण;

अटल पूर्णांक
wil_link_stats_global_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;

	अगर (!wil->fw_stats_global.पढ़ोy)
		वापस 0;

	seq_म_लिखो(s, "TSF %lld\n", wil->fw_stats_global.tsf);
	wil_link_stats_prपूर्णांक_global(wil, s, &wil->fw_stats_global.stats);

	वापस 0;
पूर्ण

अटल पूर्णांक
wil_link_stats_global_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_link_stats_global_debugfs_show,
			   inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार
wil_link_stats_global_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			    माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक पूर्णांकerval, rc;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(wil->मुख्य_ndev);

	/* specअगरy snapshot पूर्णांकerval in ms */
	rc = kstrtoपूर्णांक_from_user(buf, len, 0, &पूर्णांकerval);
	अगर (rc || पूर्णांकerval < 0) अणु
		wil_err(wil, "Invalid argument\n");
		वापस -EINVAL;
	पूर्ण

	wil_info(wil, "request global link stats, interval %d\n", पूर्णांकerval);

	rc = wmi_link_stats_cfg(vअगर, WMI_LINK_STATS_TYPE_GLOBAL, 0, पूर्णांकerval);
	अगर (rc)
		wil_err(wil, "global link stats failed %d\n", rc);

	वापस rc ? rc : len;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_link_stats_global = अणु
	.खोलो		= wil_link_stats_global_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= wil_link_stats_global_ग_लिखो,
	.llseek		= seq_lseek,
पूर्ण;

अटल sमाप_प्रकार wil_पढ़ो_file_led_cfg(काष्ठा file *file, अक्षर __user *user_buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[80];
	पूर्णांक n;

	n = snम_लिखो(buf, माप(buf),
		     "led_id is set to %d, echo 1 to enable, 0 to disable\n",
		     led_id);

	n = min_t(पूर्णांक, n, माप(buf));

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       buf, n);
पूर्ण

अटल sमाप_प्रकार wil_ग_लिखो_file_led_cfg(काष्ठा file *file,
				      स्थिर अक्षर __user *buf_,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	पूर्णांक val;
	पूर्णांक rc;

	rc = kstrtoपूर्णांक_from_user(buf_, count, 0, &val);
	अगर (rc) अणु
		wil_err(wil, "Invalid argument\n");
		वापस rc;
	पूर्ण

	wil_info(wil, "%s led %d\n", val ? "Enabling" : "Disabling", led_id);
	rc = wmi_led_cfg(wil, val);
	अगर (rc) अणु
		wil_info(wil, "%s led %d failed\n",
			 val ? "Enabling" : "Disabling", led_id);
		वापस rc;
	पूर्ण

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_led_cfg = अणु
	.पढ़ो = wil_पढ़ो_file_led_cfg,
	.ग_लिखो = wil_ग_लिखो_file_led_cfg,
	.खोलो  = simple_खोलो,
पूर्ण;

/* led_blink_समय, ग_लिखो:
 * "<blink_on_slow> <blink_off_slow> <blink_on_med> <blink_off_med> <blink_on_fast> <blink_off_fast>
 */
अटल sमाप_प्रकार wil_ग_लिखो_led_blink_समय(काष्ठा file *file,
					स्थिर अक्षर __user *buf,
					माप_प्रकार len, loff_t *ppos)
अणु
	पूर्णांक rc;
	अक्षर *kbuf = kदो_स्मृति(len + 1, GFP_KERNEL);

	अगर (!kbuf)
		वापस -ENOMEM;

	rc = simple_ग_लिखो_to_buffer(kbuf, len, ppos, buf, len);
	अगर (rc != len) अणु
		kमुक्त(kbuf);
		वापस rc >= 0 ? -EIO : rc;
	पूर्ण

	kbuf[len] = '\0';
	rc = माला_पूछो(kbuf, "%d %d %d %d %d %d",
		    &led_blink_समय[WIL_LED_TIME_SLOW].on_ms,
		    &led_blink_समय[WIL_LED_TIME_SLOW].off_ms,
		    &led_blink_समय[WIL_LED_TIME_MED].on_ms,
		    &led_blink_समय[WIL_LED_TIME_MED].off_ms,
		    &led_blink_समय[WIL_LED_TIME_FAST].on_ms,
		    &led_blink_समय[WIL_LED_TIME_FAST].off_ms);
	kमुक्त(kbuf);

	अगर (rc < 0)
		वापस rc;
	अगर (rc < 6)
		वापस -EINVAL;

	वापस len;
पूर्ण

अटल sमाप_प्रकार wil_पढ़ो_led_blink_समय(काष्ठा file *file, अक्षर __user *user_buf,
				       माप_प्रकार count, loff_t *ppos)
अणु
	अटल अक्षर text[400];

	snम_लिखो(text, माप(text),
		 "To set led blink on/off time variables write:\n"
		 "<blink_on_slow> <blink_off_slow> <blink_on_med> "
		 "<blink_off_med> <blink_on_fast> <blink_off_fast>\n"
		 "The current values are:\n"
		 "%d %d %d %d %d %d\n",
		 led_blink_समय[WIL_LED_TIME_SLOW].on_ms,
		 led_blink_समय[WIL_LED_TIME_SLOW].off_ms,
		 led_blink_समय[WIL_LED_TIME_MED].on_ms,
		 led_blink_समय[WIL_LED_TIME_MED].off_ms,
		 led_blink_समय[WIL_LED_TIME_FAST].on_ms,
		 led_blink_समय[WIL_LED_TIME_FAST].off_ms);

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, text,
				       माप(text));
पूर्ण

अटल स्थिर काष्ठा file_operations fops_led_blink_समय = अणु
	.पढ़ो = wil_पढ़ो_led_blink_समय,
	.ग_लिखो = wil_ग_लिखो_led_blink_समय,
	.खोलो  = simple_खोलो,
पूर्ण;

/*---------FW capabilities------------*/
अटल पूर्णांक wil_fw_capabilities_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;

	seq_म_लिखो(s, "fw_capabilities : %*pb\n", WMI_FW_CAPABILITY_MAX,
		   wil->fw_capabilities);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_fw_capabilities_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_fw_capabilities_debugfs_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_capabilities = अणु
	.खोलो		= wil_fw_capabilities_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
पूर्ण;

/*---------FW version------------*/
अटल पूर्णांक wil_fw_version_debugfs_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;

	अगर (wil->fw_version[0])
		seq_म_लिखो(s, "%s\n", wil->fw_version);
	अन्यथा
		seq_माला_दो(s, "N/A\n");

	वापस 0;
पूर्ण

अटल पूर्णांक wil_fw_version_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_fw_version_debugfs_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_fw_version = अणु
	.खोलो		= wil_fw_version_seq_खोलो,
	.release	= single_release,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
पूर्ण;

/*---------suspend_stats---------*/
अटल sमाप_प्रकार wil_ग_लिखो_suspend_stats(काष्ठा file *file,
				       स्थिर अक्षर __user *buf,
				       माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;

	स_रखो(&wil->suspend_stats, 0, माप(wil->suspend_stats));

	वापस len;
पूर्ण

अटल sमाप_प्रकार wil_पढ़ो_suspend_stats(काष्ठा file *file,
				      अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा wil6210_priv *wil = file->निजी_data;
	अक्षर *text;
	पूर्णांक n, ret, text_size = 500;

	text = kदो_स्मृति(text_size, GFP_KERNEL);
	अगर (!text)
		वापस -ENOMEM;

	n = snम_लिखो(text, text_size,
		     "Radio on suspend statistics:\n"
		     "successful suspends:%ld failed suspends:%ld\n"
		     "successful resumes:%ld failed resumes:%ld\n"
		     "rejected by device:%ld\n"
		     "Radio off suspend statistics:\n"
		     "successful suspends:%ld failed suspends:%ld\n"
		     "successful resumes:%ld failed resumes:%ld\n"
		     "General statistics:\n"
		     "rejected by host:%ld\n",
		     wil->suspend_stats.r_on.successful_suspends,
		     wil->suspend_stats.r_on.failed_suspends,
		     wil->suspend_stats.r_on.successful_resumes,
		     wil->suspend_stats.r_on.failed_resumes,
		     wil->suspend_stats.rejected_by_device,
		     wil->suspend_stats.r_off.successful_suspends,
		     wil->suspend_stats.r_off.failed_suspends,
		     wil->suspend_stats.r_off.successful_resumes,
		     wil->suspend_stats.r_off.failed_resumes,
		     wil->suspend_stats.rejected_by_host);

	n = min_t(पूर्णांक, n, text_size);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, text, n);

	kमुक्त(text);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_suspend_stats = अणु
	.पढ़ो = wil_पढ़ो_suspend_stats,
	.ग_लिखो = wil_ग_लिखो_suspend_stats,
	.खोलो  = simple_खोलो,
पूर्ण;

/*---------compressed_rx_status---------*/
अटल sमाप_प्रकार wil_compressed_rx_status_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *buf,
					      माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा seq_file *s = file->निजी_data;
	काष्ठा wil6210_priv *wil = s->निजी;
	पूर्णांक compressed_rx_status;
	पूर्णांक rc;

	rc = kstrtoपूर्णांक_from_user(buf, len, 0, &compressed_rx_status);
	अगर (rc) अणु
		wil_err(wil, "Invalid argument\n");
		वापस rc;
	पूर्ण

	अगर (wil_has_active_अगरaces(wil, true, false)) अणु
		wil_err(wil, "cannot change edma config after iface is up\n");
		वापस -EPERM;
	पूर्ण

	wil_info(wil, "%sable compressed_rx_status\n",
		 compressed_rx_status ? "En" : "Dis");

	wil->use_compressed_rx_status = compressed_rx_status;

	वापस len;
पूर्ण

अटल पूर्णांक
wil_compressed_rx_status_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा wil6210_priv *wil = s->निजी;

	seq_म_लिखो(s, "%d\n", wil->use_compressed_rx_status);

	वापस 0;
पूर्ण

अटल पूर्णांक
wil_compressed_rx_status_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, wil_compressed_rx_status_show,
			   inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_compressed_rx_status = अणु
	.खोलो  = wil_compressed_rx_status_seq_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
	.ग_लिखो = wil_compressed_rx_status_ग_लिखो,
	.llseek	= seq_lseek,
पूर्ण;

/*----------------*/
अटल व्योम wil6210_debugfs_init_blobs(काष्ठा wil6210_priv *wil,
				       काष्ठा dentry *dbg)
अणु
	पूर्णांक i;
	अक्षर name[32];

	क्रम (i = 0; i < ARRAY_SIZE(fw_mapping); i++) अणु
		काष्ठा wil_blob_wrapper *wil_blob = &wil->blobs[i];
		काष्ठा debugfs_blob_wrapper *blob = &wil_blob->blob;
		स्थिर काष्ठा fw_map *map = &fw_mapping[i];

		अगर (!map->name)
			जारी;

		wil_blob->wil = wil;
		blob->data = (व्योम * __क्रमce)wil->csr + HOSTADDR(map->host);
		blob->size = map->to - map->from;
		snम_लिखो(name, माप(name), "blob_%s", map->name);
		wil_debugfs_create_ioblob(name, 0444, dbg, wil_blob);
	पूर्ण
पूर्ण

/* misc files */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	umode_t mode;
	स्थिर काष्ठा file_operations *fops;
पूर्ण dbg_files[] = अणु
	अणु"mbox",	0444,		&mbox_fopsपूर्ण,
	अणु"rings",	0444,		&ring_fopsपूर्ण,
	अणु"stations", 0444,		&sta_fopsपूर्ण,
	अणु"mids",	0444,		&mids_fopsपूर्ण,
	अणु"desc",	0444,		&txdesc_fopsपूर्ण,
	अणु"bf",		0444,		&bf_fopsपूर्ण,
	अणु"mem_val",	0644,		&memपढ़ो_fopsपूर्ण,
	अणु"rxon",	0244,		&fops_rxonपूर्ण,
	अणु"tx_mgmt",	0244,		&fops_txmgmtपूर्ण,
	अणु"wmi_send", 0244,		&fops_wmiपूर्ण,
	अणु"back",	0644,		&fops_backपूर्ण,
	अणु"pmccfg",	0644,		&fops_pmccfgपूर्ण,
	अणु"pmcdata",	0444,		&fops_pmcdataपूर्ण,
	अणु"pmcring",	0444,		&fops_pmcringपूर्ण,
	अणु"temp",	0444,		&temp_fopsपूर्ण,
	अणु"freq",	0444,		&freq_fopsपूर्ण,
	अणु"link",	0444,		&link_fopsपूर्ण,
	अणु"info",	0444,		&info_fopsपूर्ण,
	अणु"recovery", 0644,		&fops_recoveryपूर्ण,
	अणु"led_cfg",	0644,		&fops_led_cfgपूर्ण,
	अणु"led_blink_time",	0644,	&fops_led_blink_समयपूर्ण,
	अणु"fw_capabilities",	0444,	&fops_fw_capabilitiesपूर्ण,
	अणु"fw_version",	0444,		&fops_fw_versionपूर्ण,
	अणु"suspend_stats",	0644,	&fops_suspend_statsपूर्ण,
	अणु"compressed_rx_status", 0644,	&fops_compressed_rx_statusपूर्ण,
	अणु"srings",	0444,		&srings_fopsपूर्ण,
	अणु"status_msg",	0444,		&status_msg_fopsपूर्ण,
	अणु"rx_buff_mgmt",	0444,	&rx_buff_mgmt_fopsपूर्ण,
	अणु"tx_latency",	0644,		&fops_tx_latencyपूर्ण,
	अणु"link_stats",	0644,		&fops_link_statsपूर्ण,
	अणु"link_stats_global",	0644,	&fops_link_stats_globalपूर्ण,
	अणु"rbufcap",	0244,		&fops_rbufcapपूर्ण,
पूर्ण;

अटल व्योम wil6210_debugfs_init_files(काष्ठा wil6210_priv *wil,
				       काष्ठा dentry *dbg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dbg_files); i++)
		debugfs_create_file(dbg_files[i].name, dbg_files[i].mode, dbg,
				    wil, dbg_files[i].fops);
पूर्ण

/* पूर्णांकerrupt control blocks */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	u32 icr_off;
पूर्ण dbg_icr[] = अणु
	अणु"USER_ICR",		HOSTADDR(RGF_USER_USER_ICR)पूर्ण,
	अणु"DMA_EP_TX_ICR",	HOSTADDR(RGF_DMA_EP_TX_ICR)पूर्ण,
	अणु"DMA_EP_RX_ICR",	HOSTADDR(RGF_DMA_EP_RX_ICR)पूर्ण,
	अणु"DMA_EP_MISC_ICR",	HOSTADDR(RGF_DMA_EP_MISC_ICR)पूर्ण,
पूर्ण;

अटल व्योम wil6210_debugfs_init_isr(काष्ठा wil6210_priv *wil,
				     काष्ठा dentry *dbg)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dbg_icr); i++)
		wil6210_debugfs_create_ISR(wil, dbg_icr[i].name, dbg,
					   dbg_icr[i].icr_off);
पूर्ण

#घोषणा WIL_FIELD(name, mode, type) अणु __stringअगरy(name), mode, \
	दुरत्व(काष्ठा wil6210_priv, name), typeपूर्ण

/* fields in काष्ठा wil6210_priv */
अटल स्थिर काष्ठा dbg_off dbg_wil_off[] = अणु
	WIL_FIELD(status[0],	0644,	करोff_uदीर्घ),
	WIL_FIELD(hw_version,	0444,	करोff_x32),
	WIL_FIELD(recovery_count, 0444,	करोff_u32),
	WIL_FIELD(discovery_mode, 0644,	करोff_u8),
	WIL_FIELD(chip_revision, 0444,	करोff_u8),
	WIL_FIELD(abft_len, 0644,		करोff_u8),
	WIL_FIELD(wakeup_trigger, 0644,		करोff_u8),
	WIL_FIELD(ring_idle_trsh, 0644,	करोff_u32),
	WIL_FIELD(num_rx_status_rings, 0644,	करोff_u8),
	WIL_FIELD(rx_status_ring_order, 0644,	करोff_u32),
	WIL_FIELD(tx_status_ring_order, 0644,	करोff_u32),
	WIL_FIELD(rx_buff_id_count, 0644,	करोff_u32),
	WIL_FIELD(amsdu_en, 0644,	करोff_u8),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dbg_off dbg_wil_regs[] = अणु
	अणु"RGF_MAC_MTRL_COUNTER_0", 0444, HOSTADDR(RGF_MAC_MTRL_COUNTER_0),
		करोff_io32पूर्ण,
	अणु"RGF_USER_USAGE_1", 0444, HOSTADDR(RGF_USER_USAGE_1), करोff_io32पूर्ण,
	अणु"RGF_USER_USAGE_2", 0444, HOSTADDR(RGF_USER_USAGE_2), करोff_io32पूर्ण,
	अणुपूर्ण,
पूर्ण;

/* अटल parameters */
अटल स्थिर काष्ठा dbg_off dbg_अटलs[] = अणु
	अणु"desc_index",	0644, (uदीर्घ)&dbg_txdesc_index, करोff_u32पूर्ण,
	अणु"ring_index",	0644, (uदीर्घ)&dbg_ring_index, करोff_u32पूर्ण,
	अणु"mem_addr",	0644, (uदीर्घ)&mem_addr, करोff_u32पूर्ण,
	अणु"led_polarity", 0644, (uदीर्घ)&led_polarity, करोff_u8पूर्ण,
	अणु"status_index", 0644, (uदीर्घ)&dbg_status_msg_index, करोff_u32पूर्ण,
	अणु"sring_index",	0644, (uदीर्घ)&dbg_sring_index, करोff_u32पूर्ण,
	अणु"drop_if_ring_full", 0644, (uदीर्घ)&drop_अगर_ring_full, करोff_u8पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक dbg_off_count = 4 * (ARRAY_SIZE(isr_off) - 1) +
				ARRAY_SIZE(dbg_wil_regs) - 1 +
				ARRAY_SIZE(pseuकरो_isr_off) - 1 +
				ARRAY_SIZE(lgc_itr_cnt_off) - 1 +
				ARRAY_SIZE(tx_itr_cnt_off) - 1 +
				ARRAY_SIZE(rx_itr_cnt_off) - 1;

पूर्णांक wil6210_debugfs_init(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा dentry *dbg = wil->debug = debugfs_create_dir(WIL_NAME,
			wil_to_wiphy(wil)->debugfsdir);
	अगर (IS_ERR_OR_शून्य(dbg))
		वापस -ENODEV;

	wil->dbg_data.data_arr = kसुस्मृति(dbg_off_count,
					 माप(काष्ठा wil_debugfs_iomem_data),
					 GFP_KERNEL);
	अगर (!wil->dbg_data.data_arr) अणु
		debugfs_हटाओ_recursive(dbg);
		wil->debug = शून्य;
		वापस -ENOMEM;
	पूर्ण

	wil->dbg_data.iomem_data_count = 0;

	wil_pmc_init(wil);

	wil6210_debugfs_init_files(wil, dbg);
	wil6210_debugfs_init_isr(wil, dbg);
	wil6210_debugfs_init_blobs(wil, dbg);
	wil6210_debugfs_init_offset(wil, dbg, wil, dbg_wil_off);
	wil6210_debugfs_init_offset(wil, dbg, (व्योम * __क्रमce)wil->csr,
				    dbg_wil_regs);
	wil6210_debugfs_init_offset(wil, dbg, शून्य, dbg_अटलs);

	wil6210_debugfs_create_pseuकरो_ISR(wil, dbg);

	wil6210_debugfs_create_ITR_CNT(wil, dbg);

	वापस 0;
पूर्ण

व्योम wil6210_debugfs_हटाओ(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;

	debugfs_हटाओ_recursive(wil->debug);
	wil->debug = शून्य;

	kमुक्त(wil->dbg_data.data_arr);
	क्रम (i = 0; i < wil->max_assoc_sta; i++)
		kमुक्त(wil->sta[i].tx_latency_bins);

	/* मुक्त pmc memory without sending command to fw, as it will
	 * be reset on the way करोwn anyway
	 */
	wil_pmc_मुक्त(wil, false);
पूर्ण
