<शैली गुरु>
/*
 * Copyright(c) 2018 Intel Corporation.
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
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "debugfs.h"
#समावेश "fault.h"
#समावेश "trace.h"

#घोषणा HFI1_FAULT_सूची_TX   BIT(0)
#घोषणा HFI1_FAULT_सूची_RX   BIT(1)
#घोषणा HFI1_FAULT_सूची_TXRX (HFI1_FAULT_सूची_TX | HFI1_FAULT_सूची_RX)

अटल व्योम *_fault_stats_seq_start(काष्ठा seq_file *s, loff_t *pos)
अणु
	काष्ठा hfi1_opcode_stats_perctx *opstats;

	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम *_fault_stats_seq_next(काष्ठा seq_file *s, व्योम *v, loff_t *pos)
अणु
	काष्ठा hfi1_opcode_stats_perctx *opstats;

	++*pos;
	अगर (*pos >= ARRAY_SIZE(opstats->stats))
		वापस शून्य;
	वापस pos;
पूर्ण

अटल व्योम _fault_stats_seq_stop(काष्ठा seq_file *s, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक _fault_stats_seq_show(काष्ठा seq_file *s, व्योम *v)
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
	क्रम_each_possible_cpu(j) अणु
		काष्ठा hfi1_opcode_stats_perctx *sp =
			per_cpu_ptr(dd->tx_opstats, j);

		n_packets += sp->stats[i].n_packets;
		n_bytes += sp->stats[i].n_bytes;
	पूर्ण
	अगर (!n_packets && !n_bytes)
		वापस SEQ_SKIP;
	अगर (!ibd->fault->n_rxfaults[i] && !ibd->fault->n_txfaults[i])
		वापस SEQ_SKIP;
	seq_म_लिखो(s, "%02llx %llu/%llu (faults rx:%llu faults: tx:%llu)\n", i,
		   (अचिन्हित दीर्घ दीर्घ)n_packets,
		   (अचिन्हित दीर्घ दीर्घ)n_bytes,
		   (अचिन्हित दीर्घ दीर्घ)ibd->fault->n_rxfaults[i],
		   (अचिन्हित दीर्घ दीर्घ)ibd->fault->n_txfaults[i]);
	वापस 0;
पूर्ण

DEBUGFS_SEQ_खाता_OPS(fault_stats);
DEBUGFS_SEQ_खाता_OPEN(fault_stats);
DEBUGFS_खाता_OPS(fault_stats);

अटल पूर्णांक fault_opcodes_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	file->निजी_data = inode->i_निजी;
	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार fault_opcodes_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार len, loff_t *pos)
अणु
	sमाप_प्रकार ret = 0;
	/* 1280 = 256 opcodes * 4 अक्षरs/opcode + 255 commas + शून्य */
	माप_प्रकार copy, datalen = 1280;
	अक्षर *data, *token, *ptr, *end;
	काष्ठा fault *fault = file->निजी_data;

	data = kसुस्मृति(datalen, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	copy = min(len, datalen - 1);
	अगर (copy_from_user(data, buf, copy)) अणु
		ret = -EFAULT;
		जाओ मुक्त_data;
	पूर्ण

	ret = debugfs_file_get(file->f_path.dentry);
	अगर (unlikely(ret))
		जाओ मुक्त_data;
	ptr = data;
	token = ptr;
	क्रम (ptr = data; *ptr; ptr = end + 1, token = ptr) अणु
		अक्षर *dash;
		अचिन्हित दीर्घ range_start, range_end, i;
		bool हटाओ = false;
		अचिन्हित दीर्घ bound = 1U << BITS_PER_BYTE;

		end = म_अक्षर(ptr, ',');
		अगर (end)
			*end = '\0';
		अगर (token[0] == '-') अणु
			हटाओ = true;
			token++;
		पूर्ण
		dash = म_अक्षर(token, '-');
		अगर (dash)
			*dash = '\0';
		अगर (kम_से_अदीर्घ(token, 0, &range_start))
			अवरोध;
		अगर (dash) अणु
			token = dash + 1;
			अगर (kम_से_अदीर्घ(token, 0, &range_end))
				अवरोध;
		पूर्ण अन्यथा अणु
			range_end = range_start;
		पूर्ण
		अगर (range_start == range_end && range_start == -1UL) अणु
			biपंचांगap_zero(fault->opcodes, माप(fault->opcodes) *
				    BITS_PER_BYTE);
			अवरोध;
		पूर्ण
		/* Check the inमाला_दो */
		अगर (range_start >= bound || range_end >= bound)
			अवरोध;

		क्रम (i = range_start; i <= range_end; i++) अणु
			अगर (हटाओ)
				clear_bit(i, fault->opcodes);
			अन्यथा
				set_bit(i, fault->opcodes);
		पूर्ण
		अगर (!end)
			अवरोध;
	पूर्ण
	ret = len;

	debugfs_file_put(file->f_path.dentry);
मुक्त_data:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार fault_opcodes_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				  माप_प्रकार len, loff_t *pos)
अणु
	sमाप_प्रकार ret = 0;
	अक्षर *data;
	माप_प्रकार datalen = 1280, size = 0; /* see fault_opcodes_ग_लिखो() */
	अचिन्हित दीर्घ bit = 0, zero = 0;
	काष्ठा fault *fault = file->निजी_data;
	माप_प्रकार bitsize = माप(fault->opcodes) * BITS_PER_BYTE;

	data = kसुस्मृति(datalen, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	ret = debugfs_file_get(file->f_path.dentry);
	अगर (unlikely(ret))
		जाओ मुक्त_data;
	bit = find_first_bit(fault->opcodes, bitsize);
	जबतक (bit < bitsize) अणु
		zero = find_next_zero_bit(fault->opcodes, bitsize, bit);
		अगर (zero - 1 != bit)
			size += scnम_लिखो(data + size,
					 datalen - size - 1,
					 "0x%lx-0x%lx,", bit, zero - 1);
		अन्यथा
			size += scnम_लिखो(data + size,
					 datalen - size - 1, "0x%lx,",
					 bit);
		bit = find_next_bit(fault->opcodes, bitsize, zero);
	पूर्ण
	debugfs_file_put(file->f_path.dentry);
	data[size - 1] = '\n';
	data[size] = '\0';
	ret = simple_पढ़ो_from_buffer(buf, len, pos, data, size);
मुक्त_data:
	kमुक्त(data);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations __fault_opcodes_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = fault_opcodes_खोलो,
	.पढ़ो = fault_opcodes_पढ़ो,
	.ग_लिखो = fault_opcodes_ग_लिखो,
	.llseek = no_llseek
पूर्ण;

व्योम hfi1_fault_निकास_debugfs(काष्ठा hfi1_ibdev *ibd)
अणु
	अगर (ibd->fault)
		debugfs_हटाओ_recursive(ibd->fault->dir);
	kमुक्त(ibd->fault);
	ibd->fault = शून्य;
पूर्ण

पूर्णांक hfi1_fault_init_debugfs(काष्ठा hfi1_ibdev *ibd)
अणु
	काष्ठा dentry *parent = ibd->hfi1_ibdev_dbg;
	काष्ठा dentry *fault_dir;

	ibd->fault = kzalloc(माप(*ibd->fault), GFP_KERNEL);
	अगर (!ibd->fault)
		वापस -ENOMEM;

	ibd->fault->attr.पूर्णांकerval = 1;
	ibd->fault->attr.require_end = अच_दीर्घ_उच्च;
	ibd->fault->attr.stacktrace_depth = 32;
	ibd->fault->attr.dname = शून्य;
	ibd->fault->attr.verbose = 0;
	ibd->fault->enable = false;
	ibd->fault->opcode = false;
	ibd->fault->fault_skip = 0;
	ibd->fault->skip = 0;
	ibd->fault->direction = HFI1_FAULT_सूची_TXRX;
	ibd->fault->suppress_err = false;
	biपंचांगap_zero(ibd->fault->opcodes,
		    माप(ibd->fault->opcodes) * BITS_PER_BYTE);

	fault_dir =
		fault_create_debugfs_attr("fault", parent, &ibd->fault->attr);
	अगर (IS_ERR(fault_dir)) अणु
		kमुक्त(ibd->fault);
		ibd->fault = शून्य;
		वापस -ENOENT;
	पूर्ण
	ibd->fault->dir = fault_dir;

	debugfs_create_file("fault_stats", 0444, fault_dir, ibd,
			    &_fault_stats_file_ops);
	debugfs_create_bool("enable", 0600, fault_dir, &ibd->fault->enable);
	debugfs_create_bool("suppress_err", 0600, fault_dir,
			    &ibd->fault->suppress_err);
	debugfs_create_bool("opcode_mode", 0600, fault_dir,
			    &ibd->fault->opcode);
	debugfs_create_file("opcodes", 0600, fault_dir, ibd->fault,
			    &__fault_opcodes_fops);
	debugfs_create_u64("skip_pkts", 0600, fault_dir,
			   &ibd->fault->fault_skip);
	debugfs_create_u64("skip_usec", 0600, fault_dir,
			   &ibd->fault->fault_skip_usec);
	debugfs_create_u8("direction", 0600, fault_dir, &ibd->fault->direction);

	वापस 0;
पूर्ण

bool hfi1_dbg_fault_suppress_err(काष्ठा hfi1_ibdev *ibd)
अणु
	अगर (ibd->fault)
		वापस ibd->fault->suppress_err;
	वापस false;
पूर्ण

अटल bool __hfi1_should_fault(काष्ठा hfi1_ibdev *ibd, u32 opcode,
				u8 direction)
अणु
	bool ret = false;

	अगर (!ibd->fault || !ibd->fault->enable)
		वापस false;
	अगर (!(ibd->fault->direction & direction))
		वापस false;
	अगर (ibd->fault->opcode) अणु
		अगर (biपंचांगap_empty(ibd->fault->opcodes,
				 (माप(ibd->fault->opcodes) *
				  BITS_PER_BYTE)))
			वापस false;
		अगर (!(test_bit(opcode, ibd->fault->opcodes)))
			वापस false;
	पूर्ण
	अगर (ibd->fault->fault_skip_usec &&
	    समय_beक्रमe(jअगरfies, ibd->fault->skip_usec))
		वापस false;
	अगर (ibd->fault->fault_skip && ibd->fault->skip) अणु
		ibd->fault->skip--;
		वापस false;
	पूर्ण
	ret = should_fail(&ibd->fault->attr, 1);
	अगर (ret) अणु
		ibd->fault->skip = ibd->fault->fault_skip;
		ibd->fault->skip_usec = jअगरfies +
			usecs_to_jअगरfies(ibd->fault->fault_skip_usec);
	पूर्ण
	वापस ret;
पूर्ण

bool hfi1_dbg_should_fault_tx(काष्ठा rvt_qp *qp, u32 opcode)
अणु
	काष्ठा hfi1_ibdev *ibd = to_idev(qp->ibqp.device);

	अगर (__hfi1_should_fault(ibd, opcode, HFI1_FAULT_सूची_TX)) अणु
		trace_hfi1_fault_opcode(qp, opcode);
		ibd->fault->n_txfaults[opcode]++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool hfi1_dbg_should_fault_rx(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibdev *ibd = &packet->rcd->dd->verbs_dev;

	अगर (__hfi1_should_fault(ibd, packet->opcode, HFI1_FAULT_सूची_RX)) अणु
		trace_hfi1_fault_packet(packet);
		ibd->fault->n_rxfaults[packet->opcode]++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
