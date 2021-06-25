<शैली गुरु>
/*
 * Copyright(c) 2015-2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#समावेश <linux/debugfs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/fault-inject.h>

#समावेश "hfi.h"
#समावेश "trace.h"
#समावेश "debugfs.h"
#समावेश "device.h"
#समावेश "qp.h"
#समावेश "sdma.h"
#समावेश "fault.h"

अटल काष्ठा dentry *hfi1_dbg_root;

/* wrappers to enक्रमce srcu in seq file */
sमाप_प्रकार hfi1_seq_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
		      loff_t *ppos)
अणु
	काष्ठा dentry *d = file->f_path.dentry;
	sमाप_प्रकार r;

	r = debugfs_file_get(d);
	अगर (unlikely(r))
		वापस r;
	r = seq_पढ़ो(file, buf, size, ppos);
	debugfs_file_put(d);
	वापस r;
पूर्ण

loff_t hfi1_seq_lseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा dentry *d = file->f_path.dentry;
	loff_t r;

	r = debugfs_file_get(d);
	अगर (unlikely(r))
		वापस r;
	r = seq_lseek(file, offset, whence);
	debugfs_file_put(d);
	वापस r;
पूर्ण

#घोषणा निजी2dd(file) (file_inode(file)->i_निजी)
#घोषणा निजी2ppd(file) (file_inode(file)->i_निजी)

अटल व्योम *_opcode_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_opcode_stats_perctx *opstats;

	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_opcode_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_opcode_stats_perctx *opstats;

	++*pos;
	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _opcode_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक opcode_stats_show(काष्ठा seq_file *s, u8 i, u64 packets, u64 bytes)
अणु
	अगर (!packets && !bytes)
		वापस SEQ_SKIP;
	seq_म_लिखो(s, "%02x %llu/%llu\n", i,
		   (अचिन्हित दीर्घ दीर्घ)packets,
		   (अचिन्हित दीर्घ दीर्घ)bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक _opcode_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos = v;
	loff_t i = *spos, j;
	u64 n_packets = 0, n_bytes = 0;
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	काष्ठा hfi1_ctxtdata *rcd;

	क्रम (j = 0; j < dd->first_dyn_alloc_ctxt; j++) अणु
		rcd = hfi1_rcd_get_by_index(dd, j);
		अगर (rcd) अणु
			n_packets += rcd->opstats->stats[i].n_packets;
			n_bytes += rcd->opstats->stats[i].n_bytes;
		पूर्ण
		hfi1_rcd_put(rcd);
	पूर्ण
	वापस opcode_stats_show(s, i, n_packets, n_bytes);
पूर्ण

DEBUGFS_SEQ_खाता_OPS(opcode_stats);
DEBUGFS_SEQ_खाता_OPEN(opcode_stats)
DEBUGFS_खाता_OPS(opcode_stats);

अटल व्योम *_tx_opcode_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	वापस _opcode_stats_seq_start(s, pos);
पूर्ण

अटल व्योम *_tx_opcode_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	वापस _opcode_stats_seq_next(s, v, pos);
पूर्ण

अटल व्योम _tx_opcode_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _tx_opcode_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos = v;
	loff_t i = *spos;
	पूर्णांक j;
	u64 n_packets = 0, n_bytes = 0;
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	क्रम_each_possible_cpu(j) अणु
		काष्ठा hfi1_opcode_stats_perctx *s =
			per_cpu_ptr(dd->tx_opstats, j);
		n_packets += s->stats[i].n_packets;
		n_bytes += s->stats[i].n_bytes;
	पूर्ण
	वापस opcode_stats_show(s, i, n_packets, n_bytes);
पूर्ण

DEBUGFS_SEQ_खाता_OPS(tx_opcode_stats);
DEBUGFS_SEQ_खाता_OPEN(tx_opcode_stats)
DEBUGFS_खाता_OPS(tx_opcode_stats);

अटल व्योम *_ctx_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	अगर (!*pos)
		वापस SEQ_START_TOKEN;
	अगर (*pos >= dd->first_dyn_alloc_ctxt)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_ctx_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	अगर (v == SEQ_START_TOKEN)
		वापस pos;

	++*pos;
	अगर (*pos >= dd->first_dyn_alloc_ctxt)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _ctx_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	/* nothing allocated */
पूर्ण

अटल पूर्णांक _ctx_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos;
	loff_t i, j;
	u64 n_packets = 0;
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	काष्ठा hfi1_ctxtdata *rcd;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(s, "Ctx:npkts\n");
		वापस 0;
	पूर्ण

	spos = v;
	i = *spos;

	rcd = hfi1_rcd_get_by_index_safe(dd, i);
	अगर (!rcd)
		वापस SEQ_SKIP;

	क्रम (j = 0; j < ARRAY_SIZE(rcd->opstats->stats); j++)
		n_packets += rcd->opstats->stats[j].n_packets;

	hfi1_rcd_put(rcd);

	अगर (!n_packets)
		वापस SEQ_SKIP;

	seq_म_लिखो(s, "  %llu:%llu\n", i, n_packets);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(ctx_stats);
DEBUGFS_SEQ_खाता_OPEN(ctx_stats)
DEBUGFS_खाता_OPS(ctx_stats);

अटल व्योम *_qp_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
	__acquires(RCU)
अणु
	काष्ठा rvt_qp_iter *iter;
	loff_t n = *pos;

	iter = rvt_qp_iter_init(s->निजी, 0, शून्य);

	/* stop calls rcu_पढ़ो_unlock */
	rcu_पढ़ो_lock();

	अगर (!iter)
		वापस शून्य;

	करो अणु
		अगर (rvt_qp_iter_next(iter)) अणु
			kमुक्त(iter);
			वापस शून्य;
		पूर्ण
	पूर्ण जबतक (n--);

	वापस iter;
पूर्ण

अटल व्योम *_qp_stats_seq_next(काष्ठा seq_file *s, व्योम *iter_ptr,
				loff_t *pos)
	__must_hold(RCU)
अणु
	काष्ठा rvt_qp_iter *iter = iter_ptr;

	(*pos)++;

	अगर (rvt_qp_iter_next(iter)) अणु
		kमुक्त(iter);
		वापस शून्य;
	पूर्ण

	वापस iter;
पूर्ण

अटल व्योम _qp_stats_seq_stop(काष्ठा seq_file *s, व्योम *iter_ptr)
	__releases(RCU)
अणु
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक _qp_stats_seq_show(काष्ठा seq_file *s, व्योम *iter_ptr)
अणु
	काष्ठा rvt_qp_iter *iter = iter_ptr;

	अगर (!iter)
		वापस 0;

	qp_iter_prपूर्णांक(s, iter);

	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(qp_stats);
DEBUGFS_SEQ_खाता_OPEN(qp_stats)
DEBUGFS_खाता_OPS(qp_stats);

अटल व्योम *_sdes_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd;
	काष्ठा hfi1_devdata *dd;

	ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	dd = dd_from_dev(ibd);
	अगर (!dd->per_sdma || *pos >= dd->num_sdma)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_sdes_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	++*pos;
	अगर (!dd->per_sdma || *pos >= dd->num_sdma)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _sdes_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _sdes_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	loff_t *spos = v;
	loff_t i = *spos;

	sdma_seqfile_dump_sde(s, &dd->per_sdma[i]);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(sdes);
DEBUGFS_SEQ_खाता_OPEN(sdes)
DEBUGFS_खाता_OPS(sdes);

अटल व्योम *_rcds_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd;
	काष्ठा hfi1_devdata *dd;

	ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	dd = dd_from_dev(ibd);
	अगर (!dd->rcd || *pos >= dd->n_krcv_queues)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_rcds_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	++*pos;
	अगर (!dd->rcd || *pos >= dd->num_rcv_contexts)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _rcds_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _rcds_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	काष्ठा hfi1_ctxtdata *rcd;
	loff_t *spos = v;
	loff_t i = *spos;

	rcd = hfi1_rcd_get_by_index_safe(dd, i);
	अगर (rcd)
		seqfile_dump_rcd(s, rcd);
	hfi1_rcd_put(rcd);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(rcds);
DEBUGFS_SEQ_खाता_OPEN(rcds)
DEBUGFS_खाता_OPS(rcds);

अटल व्योम *_pios_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd;
	काष्ठा hfi1_devdata *dd;

	ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	dd = dd_from_dev(ibd);
	अगर (!dd->send_contexts || *pos >= dd->num_send_contexts)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_pios_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);

	++*pos;
	अगर (!dd->send_contexts || *pos >= dd->num_send_contexts)
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _pios_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _pios_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	काष्ठा send_context_info *sci;
	loff_t *spos = v;
	loff_t i = *spos;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->sc_lock, flags);
	sci = &dd->send_contexts[i];
	अगर (sci && sci->type != SC_USER && sci->allocated && sci->sc)
		seqfile_dump_sci(s, i, sci);
	spin_unlock_irqrestore(&dd->sc_lock, flags);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(pios);
DEBUGFS_SEQ_खाता_OPEN(pios)
DEBUGFS_खाता_OPS(pios);

/* पढ़ो the per-device counters */
अटल sमाप_प्रकार dev_counters_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	u64 *counters;
	माप_प्रकार avail;
	काष्ठा hfi1_devdata *dd;
	sमाप_प्रकार rval;

	dd = निजी2dd(file);
	avail = hfi1_पढ़ो_cntrs(dd, शून्य, &counters);
	rval =  simple_पढ़ो_from_buffer(buf, count, ppos, counters, avail);
	वापस rval;
पूर्ण

/* पढ़ो the per-device counters */
अटल sमाप_प्रकार dev_names_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *names;
	माप_प्रकार avail;
	काष्ठा hfi1_devdata *dd;
	sमाप_प्रकार rval;

	dd = निजी2dd(file);
	avail = hfi1_पढ़ो_cntrs(dd, &names, शून्य);
	rval =  simple_पढ़ो_from_buffer(buf, count, ppos, names, avail);
	वापस rval;
पूर्ण

काष्ठा counter_info अणु
	अक्षर *name;
	स्थिर काष्ठा file_operations ops;
पूर्ण;

/*
 * Could use file_inode(file)->i_ino to figure out which file,
 * instead of separate routine क्रम each, but क्रम now, this works...
 */

/* पढ़ो the per-port names (same क्रम each port) */
अटल sमाप_प्रकार portnames_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *names;
	माप_प्रकार avail;
	काष्ठा hfi1_devdata *dd;
	sमाप_प्रकार rval;

	dd = निजी2dd(file);
	avail = hfi1_पढ़ो_portcntrs(dd->pport, &names, शून्य);
	rval = simple_पढ़ो_from_buffer(buf, count, ppos, names, avail);
	वापस rval;
पूर्ण

/* पढ़ो the per-port counters */
अटल sमाप_प्रकार portcntrs_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	u64 *counters;
	माप_प्रकार avail;
	काष्ठा hfi1_pportdata *ppd;
	sमाप_प्रकार rval;

	ppd = निजी2ppd(file);
	avail = hfi1_पढ़ो_portcntrs(ppd, शून्य, &counters);
	rval = simple_पढ़ो_from_buffer(buf, count, ppos, counters, avail);
	वापस rval;
पूर्ण

अटल व्योम check_dyn_flag(u64 scratch0, अक्षर *p, पूर्णांक size, पूर्णांक *used,
			   पूर्णांक this_hfi, पूर्णांक hfi, u32 flag, स्थिर अक्षर *what)
अणु
	u32 mask;

	mask = flag << (hfi ? CR_DYN_SHIFT : 0);
	अगर (scratch0 & mask) अणु
		*used += scnम_लिखो(p + *used, size - *used,
				   "  0x%08x - HFI%d %s in use, %s device\n",
				   mask, hfi, what,
				   this_hfi == hfi ? "this" : "other");
	पूर्ण
पूर्ण

अटल sमाप_प्रकार asic_flags_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;
	u64 scratch0;
	अक्षर *पंचांगp;
	पूर्णांक ret = 0;
	पूर्णांक size;
	पूर्णांक used;
	पूर्णांक i;

	ppd = निजी2ppd(file);
	dd = ppd->dd;
	size = PAGE_SIZE;
	used = 0;
	पंचांगp = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	used += scnम_लिखो(पंचांगp + used, size - used,
			  "Resource flags: 0x%016llx\n", scratch0);

	/* check permanent flag */
	अगर (scratch0 & CR_THERM_INIT) अणु
		used += scnम_लिखो(पंचांगp + used, size - used,
				  "  0x%08x - thermal monitoring initialized\n",
				  (u32)CR_THERM_INIT);
	पूर्ण

	/* check each dynamic flag on each HFI */
	क्रम (i = 0; i < 2; i++) अणु
		check_dyn_flag(scratch0, पंचांगp, size, &used, dd->hfi1_id, i,
			       CR_SBUS, "SBus");
		check_dyn_flag(scratch0, पंचांगp, size, &used, dd->hfi1_id, i,
			       CR_EPROM, "EPROM");
		check_dyn_flag(scratch0, पंचांगp, size, &used, dd->hfi1_id, i,
			       CR_I2C1, "i2c chain 1");
		check_dyn_flag(scratch0, पंचांगp, size, &used, dd->hfi1_id, i,
			       CR_I2C2, "i2c chain 2");
	पूर्ण
	used += scnम_लिखो(पंचांगp + used, size - used, "Write bits to clear\n");

	ret = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp, used);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार asic_flags_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;
	अक्षर *buff;
	पूर्णांक ret;
	अचिन्हित दीर्घ दीर्घ value;
	u64 scratch0;
	u64 clear;

	ppd = निजी2ppd(file);
	dd = ppd->dd;

	/* zero terminate and पढ़ो the expected पूर्णांकeger */
	buff = memdup_user_nul(buf, count);
	अगर (IS_ERR(buff))
		वापस PTR_ERR(buff);

	ret = kम_से_अदीर्घl(buff, 0, &value);
	अगर (ret)
		जाओ करो_मुक्त;
	clear = value;

	/* obtain exclusive access */
	mutex_lock(&dd->asic_data->asic_resource_mutex);
	acquire_hw_mutex(dd);

	scratch0 = पढ़ो_csr(dd, ASIC_CFG_SCRATCH);
	scratch0 &= ~clear;
	ग_लिखो_csr(dd, ASIC_CFG_SCRATCH, scratch0);
	/* क्रमce ग_लिखो to be visible to other HFI on another OS */
	(व्योम)पढ़ो_csr(dd, ASIC_CFG_SCRATCH);

	release_hw_mutex(dd);
	mutex_unlock(&dd->asic_data->asic_resource_mutex);

	/* वापस the number of bytes written */
	ret = count;

 करो_मुक्त:
	kमुक्त(buff);
	वापस ret;
पूर्ण

/* पढ़ो the dc8051 memory */
अटल sमाप_प्रकार dc8051_memory_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd = निजी2ppd(file);
	sमाप_प्रकार rval;
	व्योम *पंचांगp;
	loff_t start, end;

	/* the checks below expect the position to be positive */
	अगर (*ppos < 0)
		वापस -EINVAL;

	पंचांगp = kzalloc(DC8051_DATA_MEM_SIZE, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	/*
	 * Fill in the requested portion of the temporary buffer from the
	 * 8051 memory.  The 8051 memory पढ़ो is करोne in terms of 8 bytes.
	 * Adjust start and end to fit.  Skip पढ़ोing anything अगर out of
	 * range.
	 */
	start = *ppos & ~0x7;	/* round करोwn */
	अगर (start < DC8051_DATA_MEM_SIZE) अणु
		end = (*ppos + count + 7) & ~0x7; /* round up */
		अगर (end > DC8051_DATA_MEM_SIZE)
			end = DC8051_DATA_MEM_SIZE;
		rval = पढ़ो_8051_data(ppd->dd, start, end - start,
				      (u64 *)(पंचांगp + start));
		अगर (rval)
			जाओ करोne;
	पूर्ण

	rval = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp,
				       DC8051_DATA_MEM_SIZE);
करोne:
	kमुक्त(पंचांगp);
	वापस rval;
पूर्ण

अटल sमाप_प्रकार debugfs_lcb_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd = निजी2ppd(file);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ total, csr_off;
	u64 data;

	अगर (*ppos < 0)
		वापस -EINVAL;
	/* only पढ़ो 8 byte quantities */
	अगर ((count % 8) != 0)
		वापस -EINVAL;
	/* offset must be 8-byte aligned */
	अगर ((*ppos % 8) != 0)
		वापस -EINVAL;
	/* करो nothing अगर out of range or zero count */
	अगर (*ppos >= (LCB_END - LCB_START) || !count)
		वापस 0;
	/* reduce count अगर needed */
	अगर (*ppos + count > LCB_END - LCB_START)
		count = (LCB_END - LCB_START) - *ppos;

	csr_off = LCB_START + *ppos;
	क्रम (total = 0; total < count; total += 8, csr_off += 8) अणु
		अगर (पढ़ो_lcb_csr(dd, csr_off, (u64 *)&data))
			अवरोध; /* failed */
		अगर (put_user(data, (अचिन्हित दीर्घ __user *)(buf + total)))
			अवरोध;
	पूर्ण
	*ppos += total;
	वापस total;
पूर्ण

अटल sमाप_प्रकार debugfs_lcb_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd = निजी2ppd(file);
	काष्ठा hfi1_devdata *dd = ppd->dd;
	अचिन्हित दीर्घ total, csr_off, data;

	अगर (*ppos < 0)
		वापस -EINVAL;
	/* only ग_लिखो 8 byte quantities */
	अगर ((count % 8) != 0)
		वापस -EINVAL;
	/* offset must be 8-byte aligned */
	अगर ((*ppos % 8) != 0)
		वापस -EINVAL;
	/* करो nothing अगर out of range or zero count */
	अगर (*ppos >= (LCB_END - LCB_START) || !count)
		वापस 0;
	/* reduce count अगर needed */
	अगर (*ppos + count > LCB_END - LCB_START)
		count = (LCB_END - LCB_START) - *ppos;

	csr_off = LCB_START + *ppos;
	क्रम (total = 0; total < count; total += 8, csr_off += 8) अणु
		अगर (get_user(data, (अचिन्हित दीर्घ __user *)(buf + total)))
			अवरोध;
		अगर (ग_लिखो_lcb_csr(dd, csr_off, data))
			अवरोध; /* failed */
	पूर्ण
	*ppos += total;
	वापस total;
पूर्ण

/*
 * पढ़ो the per-port QSFP data क्रम ppd
 */
अटल sमाप_प्रकार qsfp_debugfs_dump(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd;
	अक्षर *पंचांगp;
	पूर्णांक ret;

	ppd = निजी2ppd(file);
	पंचांगp = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	ret = qsfp_dump(ppd, पंचांगp, PAGE_SIZE);
	अगर (ret > 0)
		ret = simple_पढ़ो_from_buffer(buf, count, ppos, पंचांगp, ret);
	kमुक्त(पंचांगp);
	वापस ret;
पूर्ण

/* Do an i2c ग_लिखो operation on the chain क्रम the given HFI. */
अटल sमाप_प्रकार __i2c_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;
	अक्षर *buff;
	पूर्णांक ret;
	पूर्णांक i2c_addr;
	पूर्णांक offset;
	पूर्णांक total_written;

	ppd = निजी2ppd(file);

	/* byte offset क्रमmat: [offsetSize][i2cAddr][offsetHigh][offsetLow] */
	i2c_addr = (*ppos >> 16) & 0xffff;
	offset = *ppos & 0xffff;

	/* explicitly reject invalid address 0 to catch cp and cat */
	अगर (i2c_addr == 0)
		वापस -EINVAL;

	buff = memdup_user(buf, count);
	अगर (IS_ERR(buff))
		वापस PTR_ERR(buff);

	total_written = i2c_ग_लिखो(ppd, target, i2c_addr, offset, buff, count);
	अगर (total_written < 0) अणु
		ret = total_written;
		जाओ _मुक्त;
	पूर्ण

	*ppos += total_written;

	ret = total_written;

 _मुक्त:
	kमुक्त(buff);
	वापस ret;
पूर्ण

/* Do an i2c ग_लिखो operation on chain क्रम HFI 0. */
अटल sमाप_प्रकार i2c1_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस __i2c_debugfs_ग_लिखो(file, buf, count, ppos, 0);
पूर्ण

/* Do an i2c ग_लिखो operation on chain क्रम HFI 1. */
अटल sमाप_प्रकार i2c2_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस __i2c_debugfs_ग_लिखो(file, buf, count, ppos, 1);
पूर्ण

/* Do an i2c पढ़ो operation on the chain क्रम the given HFI. */
अटल sमाप_प्रकार __i2c_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;
	अक्षर *buff;
	पूर्णांक ret;
	पूर्णांक i2c_addr;
	पूर्णांक offset;
	पूर्णांक total_पढ़ो;

	ppd = निजी2ppd(file);

	/* byte offset क्रमmat: [offsetSize][i2cAddr][offsetHigh][offsetLow] */
	i2c_addr = (*ppos >> 16) & 0xffff;
	offset = *ppos & 0xffff;

	/* explicitly reject invalid address 0 to catch cp and cat */
	अगर (i2c_addr == 0)
		वापस -EINVAL;

	buff = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buff)
		वापस -ENOMEM;

	total_पढ़ो = i2c_पढ़ो(ppd, target, i2c_addr, offset, buff, count);
	अगर (total_पढ़ो < 0) अणु
		ret = total_पढ़ो;
		जाओ _मुक्त;
	पूर्ण

	*ppos += total_पढ़ो;

	ret = copy_to_user(buf, buff, total_पढ़ो);
	अगर (ret > 0) अणु
		ret = -EFAULT;
		जाओ _मुक्त;
	पूर्ण

	ret = total_पढ़ो;

 _मुक्त:
	kमुक्त(buff);
	वापस ret;
पूर्ण

/* Do an i2c पढ़ो operation on chain क्रम HFI 0. */
अटल sमाप_प्रकार i2c1_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस __i2c_debugfs_पढ़ो(file, buf, count, ppos, 0);
पूर्ण

/* Do an i2c पढ़ो operation on chain क्रम HFI 1. */
अटल sमाप_प्रकार i2c2_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस __i2c_debugfs_पढ़ो(file, buf, count, ppos, 1);
पूर्ण

/* Do a QSFP ग_लिखो operation on the i2c chain क्रम the given HFI. */
अटल sमाप_प्रकार __qsfp_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				    माप_प्रकार count, loff_t *ppos, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;
	अक्षर *buff;
	पूर्णांक ret;
	पूर्णांक total_written;

	अगर (*ppos + count > QSFP_PAGESIZE * 4) /* base page + page00-page03 */
		वापस -EINVAL;

	ppd = निजी2ppd(file);

	buff = memdup_user(buf, count);
	अगर (IS_ERR(buff))
		वापस PTR_ERR(buff);

	total_written = qsfp_ग_लिखो(ppd, target, *ppos, buff, count);
	अगर (total_written < 0) अणु
		ret = total_written;
		जाओ _मुक्त;
	पूर्ण

	*ppos += total_written;

	ret = total_written;

 _मुक्त:
	kमुक्त(buff);
	वापस ret;
पूर्ण

/* Do a QSFP ग_लिखो operation on i2c chain क्रम HFI 0. */
अटल sमाप_प्रकार qsfp1_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	वापस __qsfp_debugfs_ग_लिखो(file, buf, count, ppos, 0);
पूर्ण

/* Do a QSFP ग_लिखो operation on i2c chain क्रम HFI 1. */
अटल sमाप_प्रकार qsfp2_debugfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	वापस __qsfp_debugfs_ग_लिखो(file, buf, count, ppos, 1);
पूर्ण

/* Do a QSFP पढ़ो operation on the i2c chain क्रम the given HFI. */
अटल sमाप_प्रकार __qsfp_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;
	अक्षर *buff;
	पूर्णांक ret;
	पूर्णांक total_पढ़ो;

	अगर (*ppos + count > QSFP_PAGESIZE * 4) अणु /* base page + page00-page03 */
		ret = -EINVAL;
		जाओ _वापस;
	पूर्ण

	ppd = निजी2ppd(file);

	buff = kदो_स्मृति(count, GFP_KERNEL);
	अगर (!buff) अणु
		ret = -ENOMEM;
		जाओ _वापस;
	पूर्ण

	total_पढ़ो = qsfp_पढ़ो(ppd, target, *ppos, buff, count);
	अगर (total_पढ़ो < 0) अणु
		ret = total_पढ़ो;
		जाओ _मुक्त;
	पूर्ण

	*ppos += total_पढ़ो;

	ret = copy_to_user(buf, buff, total_पढ़ो);
	अगर (ret > 0) अणु
		ret = -EFAULT;
		जाओ _मुक्त;
	पूर्ण

	ret = total_पढ़ो;

 _मुक्त:
	kमुक्त(buff);
 _वापस:
	वापस ret;
पूर्ण

/* Do a QSFP पढ़ो operation on i2c chain क्रम HFI 0. */
अटल sमाप_प्रकार qsfp1_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस __qsfp_debugfs_पढ़ो(file, buf, count, ppos, 0);
पूर्ण

/* Do a QSFP पढ़ो operation on i2c chain क्रम HFI 1. */
अटल sमाप_प्रकार qsfp2_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार count, loff_t *ppos)
अणु
	वापस __qsfp_debugfs_पढ़ो(file, buf, count, ppos, 1);
पूर्ण

अटल पूर्णांक __i2c_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;

	ppd = निजी2ppd(fp);

	वापस acquire_chip_resource(ppd->dd, i2c_target(target), 0);
पूर्ण

अटल पूर्णांक i2c1_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __i2c_debugfs_खोलो(in, fp, 0);
पूर्ण

अटल पूर्णांक i2c2_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __i2c_debugfs_खोलो(in, fp, 1);
पूर्ण

अटल पूर्णांक __i2c_debugfs_release(काष्ठा inode *in, काष्ठा file *fp, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;

	ppd = निजी2ppd(fp);

	release_chip_resource(ppd->dd, i2c_target(target));

	वापस 0;
पूर्ण

अटल पूर्णांक i2c1_debugfs_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __i2c_debugfs_release(in, fp, 0);
पूर्ण

अटल पूर्णांक i2c2_debugfs_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __i2c_debugfs_release(in, fp, 1);
पूर्ण

अटल पूर्णांक __qsfp_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;

	ppd = निजी2ppd(fp);

	वापस acquire_chip_resource(ppd->dd, i2c_target(target), 0);
पूर्ण

अटल पूर्णांक qsfp1_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __qsfp_debugfs_खोलो(in, fp, 0);
पूर्ण

अटल पूर्णांक qsfp2_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __qsfp_debugfs_खोलो(in, fp, 1);
पूर्ण

अटल पूर्णांक __qsfp_debugfs_release(काष्ठा inode *in, काष्ठा file *fp, u32 target)
अणु
	काष्ठा hfi1_pportdata *ppd;

	ppd = निजी2ppd(fp);

	release_chip_resource(ppd->dd, i2c_target(target));

	वापस 0;
पूर्ण

अटल पूर्णांक qsfp1_debugfs_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __qsfp_debugfs_release(in, fp, 0);
पूर्ण

अटल पूर्णांक qsfp2_debugfs_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	वापस __qsfp_debugfs_release(in, fp, 1);
पूर्ण

#घोषणा EXPROM_WRITE_ENABLE BIT_ULL(14)

अटल bool exprom_wp_disabled;

अटल पूर्णांक exprom_wp_set(काष्ठा hfi1_devdata *dd, bool disable)
अणु
	u64 gpio_val = 0;

	अगर (disable) अणु
		gpio_val = EXPROM_WRITE_ENABLE;
		exprom_wp_disabled = true;
		dd_dev_info(dd, "Disable Expansion ROM Write Protection\n");
	पूर्ण अन्यथा अणु
		exprom_wp_disabled = false;
		dd_dev_info(dd, "Enable Expansion ROM Write Protection\n");
	पूर्ण

	ग_लिखो_csr(dd, ASIC_GPIO_OUT, gpio_val);
	ग_लिखो_csr(dd, ASIC_GPIO_OE, gpio_val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार exprom_wp_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार exprom_wp_debugfs_ग_लिखो(काष्ठा file *file,
				       स्थिर अक्षर __user *buf, माप_प्रकार count,
				       loff_t *ppos)
अणु
	काष्ठा hfi1_pportdata *ppd = निजी2ppd(file);
	अक्षर cdata;

	अगर (count != 1)
		वापस -EINVAL;
	अगर (get_user(cdata, buf))
		वापस -EFAULT;
	अगर (cdata == '0')
		exprom_wp_set(ppd->dd, false);
	अन्यथा अगर (cdata == '1')
		exprom_wp_set(ppd->dd, true);
	अन्यथा
		वापस -EINVAL;

	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ exprom_in_use;

अटल पूर्णांक exprom_wp_debugfs_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	अगर (test_and_set_bit(0, &exprom_in_use))
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक exprom_wp_debugfs_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	काष्ठा hfi1_pportdata *ppd = निजी2ppd(fp);

	अगर (exprom_wp_disabled)
		exprom_wp_set(ppd->dd, false);
	clear_bit(0, &exprom_in_use);

	वापस 0;
पूर्ण

#घोषणा DEBUGFS_OPS(nm, पढ़ोroutine, ग_लिखोroutine)	\
अणु \
	.name = nm, \
	.ops = अणु \
		.owner = THIS_MODULE, \
		.पढ़ो = पढ़ोroutine, \
		.ग_लिखो = ग_लिखोroutine, \
		.llseek = generic_file_llseek, \
	पूर्ण, \
पूर्ण

#घोषणा DEBUGFS_XOPS(nm, पढ़ोf, ग_लिखोf, खोलोf, releasef) \
अणु \
	.name = nm, \
	.ops = अणु \
		.owner = THIS_MODULE, \
		.पढ़ो = पढ़ोf, \
		.ग_लिखो = ग_लिखोf, \
		.llseek = generic_file_llseek, \
		.खोलो = खोलोf, \
		.release = releasef \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा counter_info cntr_ops[] = अणु
	DEBUGFS_OPS("counter_names", dev_names_पढ़ो, शून्य),
	DEBUGFS_OPS("counters", dev_counters_पढ़ो, शून्य),
	DEBUGFS_OPS("portcounter_names", portnames_पढ़ो, शून्य),
पूर्ण;

अटल स्थिर काष्ठा counter_info port_cntr_ops[] = अणु
	DEBUGFS_OPS("port%dcounters", portcntrs_debugfs_पढ़ो, शून्य),
	DEBUGFS_XOPS("i2c1", i2c1_debugfs_पढ़ो, i2c1_debugfs_ग_लिखो,
		     i2c1_debugfs_खोलो, i2c1_debugfs_release),
	DEBUGFS_XOPS("i2c2", i2c2_debugfs_पढ़ो, i2c2_debugfs_ग_लिखो,
		     i2c2_debugfs_खोलो, i2c2_debugfs_release),
	DEBUGFS_OPS("qsfp_dump%d", qsfp_debugfs_dump, शून्य),
	DEBUGFS_XOPS("qsfp1", qsfp1_debugfs_पढ़ो, qsfp1_debugfs_ग_लिखो,
		     qsfp1_debugfs_खोलो, qsfp1_debugfs_release),
	DEBUGFS_XOPS("qsfp2", qsfp2_debugfs_पढ़ो, qsfp2_debugfs_ग_लिखो,
		     qsfp2_debugfs_खोलो, qsfp2_debugfs_release),
	DEBUGFS_XOPS("exprom_wp", exprom_wp_debugfs_पढ़ो,
		     exprom_wp_debugfs_ग_लिखो, exprom_wp_debugfs_खोलो,
		     exprom_wp_debugfs_release),
	DEBUGFS_OPS("asic_flags", asic_flags_पढ़ो, asic_flags_ग_लिखो),
	DEBUGFS_OPS("dc8051_memory", dc8051_memory_पढ़ो, शून्य),
	DEBUGFS_OPS("lcb", debugfs_lcb_पढ़ो, debugfs_lcb_ग_लिखो),
पूर्ण;

अटल व्योम *_sdma_cpu_list_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	अगर (*pos >= num_online_cpus())
		वापस शून्य;

	वापस pos;
पूर्ण

अटल व्योम *_sdma_cpu_list_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	++*pos;
	अगर (*pos >= num_online_cpus())
		वापस शून्य;

	वापस pos;
पूर्ण

अटल व्योम _sdma_cpu_list_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
	/* nothing allocated */
पूर्ण

अटल पूर्णांक _sdma_cpu_list_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	काष्ठा hfi1_ibdev *ibd = (काष्ठा hfi1_ibdev *)s->निजी;
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	loff_t *spos = v;
	loff_t i = *spos;

	sdma_seqfile_dump_cpu_list(s, dd, (अचिन्हित दीर्घ)i);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(sdma_cpu_list);
DEBUGFS_SEQ_खाता_OPEN(sdma_cpu_list)
DEBUGFS_खाता_OPS(sdma_cpu_list);

व्योम hfi1_dbg_ibdev_init(काष्ठा hfi1_ibdev *ibd)
अणु
	अक्षर name[माप("port0counters") + 1];
	अक्षर link[10];
	काष्ठा hfi1_devdata *dd = dd_from_dev(ibd);
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा dentry *root;
	पूर्णांक unit = dd->unit;
	पूर्णांक i, j;

	अगर (!hfi1_dbg_root)
		वापस;
	snम_लिखो(name, माप(name), "%s_%d", class_name(), unit);
	snम_लिखो(link, माप(link), "%d", unit);
	root = debugfs_create_dir(name, hfi1_dbg_root);
	ibd->hfi1_ibdev_dbg = root;

	ibd->hfi1_ibdev_link =
		debugfs_create_symlink(link, hfi1_dbg_root, name);

	debugfs_create_file("opcode_stats", 0444, root, ibd,
			    &_opcode_stats_file_ops);
	debugfs_create_file("tx_opcode_stats", 0444, root, ibd,
			    &_tx_opcode_stats_file_ops);
	debugfs_create_file("ctx_stats", 0444, root, ibd, &_ctx_stats_file_ops);
	debugfs_create_file("qp_stats", 0444, root, ibd, &_qp_stats_file_ops);
	debugfs_create_file("sdes", 0444, root, ibd, &_sdes_file_ops);
	debugfs_create_file("rcds", 0444, root, ibd, &_rcds_file_ops);
	debugfs_create_file("pios", 0444, root, ibd, &_pios_file_ops);
	debugfs_create_file("sdma_cpu_list", 0444, root, ibd,
			    &_sdma_cpu_list_file_ops);

	/* dev counter files */
	क्रम (i = 0; i < ARRAY_SIZE(cntr_ops); i++)
		debugfs_create_file(cntr_ops[i].name, 0444, root, dd,
				    &cntr_ops[i].ops);

	/* per port files */
	क्रम (ppd = dd->pport, j = 0; j < dd->num_pports; j++, ppd++)
		क्रम (i = 0; i < ARRAY_SIZE(port_cntr_ops); i++) अणु
			snम_लिखो(name,
				 माप(name),
				 port_cntr_ops[i].name,
				 j + 1);
			debugfs_create_file(name,
					    !port_cntr_ops[i].ops.ग_लिखो ?
						    S_IRUGO :
						    S_IRUGO | S_IWUSR,
					    root, ppd, &port_cntr_ops[i].ops);
		पूर्ण

	hfi1_fault_init_debugfs(ibd);
पूर्ण

व्योम hfi1_dbg_ibdev_निकास(काष्ठा hfi1_ibdev *ibd)
अणु
	अगर (!hfi1_dbg_root)
		जाओ out;
	hfi1_fault_निकास_debugfs(ibd);
	debugfs_हटाओ(ibd->hfi1_ibdev_link);
	debugfs_हटाओ_recursive(ibd->hfi1_ibdev_dbg);
out:
	ibd->hfi1_ibdev_dbg = शून्य;
पूर्ण

/*
 * driver stats field names, one line per stat, single string.  Used by
 * programs like hfistats to prपूर्णांक the stats in a way which works क्रम
 * dअगरferent versions of drivers, without changing program source.
 * अगर hfi1_ib_stats changes, this needs to change.  Names need to be
 * 12 अक्षरs or less (w/o newline), क्रम proper display by hfistats utility.
 */
अटल स्थिर अक्षर * स्थिर hfi1_statnames[] = अणु
	/* must be element 0*/
	"KernIntr",
	"ErrorIntr",
	"Tx_Errs",
	"Rcv_Errs",
	"H/W_Errs",
	"NoPIOBufs",
	"CtxtsOpen",
	"RcvLen_Errs",
	"EgrBufFull",
	"EgrHdrFull"
पूर्ण;

अटल व्योम *_driver_stats_names_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	अगर (*pos >= ARRAY_SIZE(hfi1_statnames))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_driver_stats_names_seq_next(
	काष्ठा seq_file *s,
	व्योम *v,
	loff_t *pos)
अणु
	++*pos;
	अगर (*pos >= ARRAY_SIZE(hfi1_statnames))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _driver_stats_names_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _driver_stats_names_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos = v;

	seq_म_लिखो(s, "%s\n", hfi1_statnames[*spos]);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(driver_stats_names);
DEBUGFS_SEQ_खाता_OPEN(driver_stats_names)
DEBUGFS_खाता_OPS(driver_stats_names);

अटल व्योम *_driver_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	अगर (*pos >= ARRAY_SIZE(hfi1_statnames))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_driver_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	++*pos;
	अगर (*pos >= ARRAY_SIZE(hfi1_statnames))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _driver_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल u64 hfi1_sps_पूर्णांकs(व्योम)
अणु
	अचिन्हित दीर्घ index, flags;
	काष्ठा hfi1_devdata *dd;
	u64 sps_पूर्णांकs = 0;

	xa_lock_irqsave(&hfi1_dev_table, flags);
	xa_क्रम_each(&hfi1_dev_table, index, dd) अणु
		sps_पूर्णांकs += get_all_cpu_total(dd->पूर्णांक_counter);
	पूर्ण
	xa_unlock_irqrestore(&hfi1_dev_table, flags);
	वापस sps_पूर्णांकs;
पूर्ण

अटल पूर्णांक _driver_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
अणु
	loff_t *spos = v;
	अक्षर *buffer;
	u64 *stats = (u64 *)&hfi1_stats;
	माप_प्रकार sz = seq_get_buf(s, &buffer);

	अगर (sz < माप(u64))
		वापस SEQ_SKIP;
	/* special हाल क्रम पूर्णांकerrupts */
	अगर (*spos == 0)
		*(u64 *)buffer = hfi1_sps_पूर्णांकs();
	अन्यथा
		*(u64 *)buffer = stats[*spos];
	seq_commit(s,  माप(u64));
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(driver_stats);
DEBUGFS_SEQ_खाता_OPEN(driver_stats)
DEBUGFS_खाता_OPS(driver_stats);

व्योम hfi1_dbg_init(व्योम)
अणु
	hfi1_dbg_root  = debugfs_create_dir(DRIVER_NAME, शून्य);
	debugfs_create_file("driver_stats_names", 0444, hfi1_dbg_root, शून्य,
			    &_driver_stats_names_file_ops);
	debugfs_create_file("driver_stats", 0444, hfi1_dbg_root, शून्य,
			    &_driver_stats_file_ops);
पूर्ण

व्योम hfi1_dbg_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(hfi1_dbg_root);
	hfi1_dbg_root = शून्य;
पूर्ण
