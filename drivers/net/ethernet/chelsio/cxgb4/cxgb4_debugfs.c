<शैली गुरु>
/*
 * This file is part of the Chelsio T4 Ethernet driver क्रम Linux.
 *
 * Copyright (c) 2003-2014 Chelsio Communications, Inc. All rights reserved.
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

#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/sort.h>
#समावेश <linux/प्रकार.स>

#समावेश "cxgb4.h"
#समावेश "t4_regs.h"
#समावेश "t4_values.h"
#समावेश "t4fw_api.h"
#समावेश "cxgb4_debugfs.h"
#समावेश "clip_tbl.h"
#समावेश "l2t.h"
#समावेश "cudbg_if.h"
#समावेश "cudbg_lib_common.h"
#समावेश "cudbg_entity.h"
#समावेश "cudbg_lib.h"
#समावेश "cxgb4_tc_mqprio.h"

/* generic seq_file support क्रम showing a table of size rows x width. */
अटल व्योम *seq_tab_get_idx(काष्ठा seq_tab *tb, loff_t pos)
अणु
	pos -= tb->skip_first;
	वापस pos >= tb->rows ? शून्य : &tb->data[pos * tb->width];
पूर्ण

अटल व्योम *seq_tab_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा seq_tab *tb = seq->निजी;

	अगर (tb->skip_first && *pos == 0)
		वापस SEQ_START_TOKEN;

	वापस seq_tab_get_idx(tb, *pos);
पूर्ण

अटल व्योम *seq_tab_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	v = seq_tab_get_idx(seq->निजी, *pos + 1);
	++(*pos);
	वापस v;
पूर्ण

अटल व्योम seq_tab_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल पूर्णांक seq_tab_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	स्थिर काष्ठा seq_tab *tb = seq->निजी;

	वापस tb->show(seq, v, ((अक्षर *)v - tb->data) / tb->width);
पूर्ण

अटल स्थिर काष्ठा seq_operations seq_tab_ops = अणु
	.start = seq_tab_start,
	.next  = seq_tab_next,
	.stop  = seq_tab_stop,
	.show  = seq_tab_show
पूर्ण;

काष्ठा seq_tab *seq_खोलो_tab(काष्ठा file *f, अचिन्हित पूर्णांक rows,
			     अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक have_header,
			     पूर्णांक (*show)(काष्ठा seq_file *seq, व्योम *v, पूर्णांक i))
अणु
	काष्ठा seq_tab *p;

	p = __seq_खोलो_निजी(f, &seq_tab_ops, माप(*p) + rows * width);
	अगर (p) अणु
		p->show = show;
		p->rows = rows;
		p->width = width;
		p->skip_first = have_header != 0;
	पूर्ण
	वापस p;
पूर्ण

/* Trim the size of a seq_tab to the supplied number of rows.  The operation is
 * irreversible.
 */
अटल पूर्णांक seq_tab_trim(काष्ठा seq_tab *p, अचिन्हित पूर्णांक new_rows)
अणु
	अगर (new_rows > p->rows)
		वापस -EINVAL;
	p->rows = new_rows;
	वापस 0;
पूर्ण

अटल पूर्णांक cim_la_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "Status   Data      PC     LS0Stat  LS0Addr "
			 "            LS0Data\n");
	अन्यथा अणु
		स्थिर u32 *p = v;

		seq_म_लिखो(seq,
			   "  %02x  %x%07x %x%07x %08x %08x %08x%08x%08x%08x\n",
			   (p[0] >> 4) & 0xff, p[0] & 0xf, p[1] >> 4,
			   p[1] & 0xf, p[2] >> 4, p[2] & 0xf, p[3], p[4], p[5],
			   p[6], p[7]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_la_show_3in1(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Status   Data      PC\n");
	पूर्ण अन्यथा अणु
		स्थिर u32 *p = v;

		seq_म_लिखो(seq, "  %02x   %08x %08x\n", p[5] & 0xff, p[6],
			   p[7]);
		seq_म_लिखो(seq, "  %02x   %02x%06x %02x%06x\n",
			   (p[3] >> 8) & 0xff, p[3] & 0xff, p[4] >> 8,
			   p[4] & 0xff, p[5] >> 8);
		seq_म_लिखो(seq, "  %02x   %x%07x %x%07x\n", (p[0] >> 4) & 0xff,
			   p[0] & 0xf, p[1] >> 4, p[1] & 0xf, p[2] >> 4);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_la_show_t6(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Status   Inst    Data      PC     LS0Stat  "
			 "LS0Addr  LS0Data  LS1Stat  LS1Addr  LS1Data\n");
	पूर्ण अन्यथा अणु
		स्थिर u32 *p = v;

		seq_म_लिखो(seq, "  %02x   %04x%04x %04x%04x %04x%04x %08x %08x %08x %08x %08x %08x\n",
			   (p[9] >> 16) & 0xff,       /* Status */
			   p[9] & 0xffff, p[8] >> 16, /* Inst */
			   p[8] & 0xffff, p[7] >> 16, /* Data */
			   p[7] & 0xffff, p[6] >> 16, /* PC */
			   p[2], p[1], p[0],      /* LS0 Stat, Addr and Data */
			   p[5], p[4], p[3]);     /* LS1 Stat, Addr and Data */
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_la_show_pc_t6(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Status   Inst    Data      PC\n");
	पूर्ण अन्यथा अणु
		स्थिर u32 *p = v;

		seq_म_लिखो(seq, "  %02x   %08x %08x %08x\n",
			   p[3] & 0xff, p[2], p[1], p[0]);
		seq_म_लिखो(seq, "  %02x   %02x%06x %02x%06x %02x%06x\n",
			   (p[6] >> 8) & 0xff, p[6] & 0xff, p[5] >> 8,
			   p[5] & 0xff, p[4] >> 8, p[4] & 0xff, p[3] >> 8);
		seq_म_लिखो(seq, "  %02x   %04x%04x %04x%04x %04x%04x\n",
			   (p[9] >> 16) & 0xff, p[9] & 0xffff, p[8] >> 16,
			   p[8] & 0xffff, p[7] >> 16, p[7] & 0xffff,
			   p[6] >> 16);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_la_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक cfg;
	काष्ठा seq_tab *p;
	काष्ठा adapter *adap = inode->i_निजी;

	ret = t4_cim_पढ़ो(adap, UP_UP_DBG_LA_CFG_A, 1, &cfg);
	अगर (ret)
		वापस ret;

	अगर (is_t6(adap->params.chip)) अणु
		/* +1 to account क्रम पूर्णांकeger भागision of CIMLA_SIZE/10 */
		p = seq_खोलो_tab(file, (adap->params.cim_la_size / 10) + 1,
				 10 * माप(u32), 1,
				 cfg & UPDBGLACAPTPCONLY_F ?
					cim_la_show_pc_t6 : cim_la_show_t6);
	पूर्ण अन्यथा अणु
		p = seq_खोलो_tab(file, adap->params.cim_la_size / 8,
				 8 * माप(u32), 1,
				 cfg & UPDBGLACAPTPCONLY_F ? cim_la_show_3in1 :
							     cim_la_show);
	पूर्ण
	अगर (!p)
		वापस -ENOMEM;

	ret = t4_cim_पढ़ो_la(adap, (u32 *)p->data, शून्य);
	अगर (ret)
		seq_release_निजी(inode, file);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations cim_la_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cim_la_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

अटल पूर्णांक cim_pअगर_la_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u32 *p = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Cntl ID DataBE   Addr                 Data\n");
	पूर्ण अन्यथा अगर (idx < CIM_PIFLA_SIZE) अणु
		seq_म_लिखो(seq, " %02x  %02x  %04x  %08x %08x%08x%08x%08x\n",
			   (p[5] >> 22) & 0xff, (p[5] >> 16) & 0x3f,
			   p[5] & 0xffff, p[4], p[3], p[2], p[1], p[0]);
	पूर्ण अन्यथा अणु
		अगर (idx == CIM_PIFLA_SIZE)
			seq_माला_दो(seq, "\nCntl ID               Data\n");
		seq_म_लिखो(seq, " %02x  %02x %08x%08x%08x%08x\n",
			   (p[4] >> 6) & 0xff, p[4] & 0x3f,
			   p[3], p[2], p[1], p[0]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_pअगर_la_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_tab *p;
	काष्ठा adapter *adap = inode->i_निजी;

	p = seq_खोलो_tab(file, 2 * CIM_PIFLA_SIZE, 6 * माप(u32), 1,
			 cim_pअगर_la_show);
	अगर (!p)
		वापस -ENOMEM;

	t4_cim_पढ़ो_pअगर_la(adap, (u32 *)p->data,
			   (u32 *)p->data + 6 * CIM_PIFLA_SIZE, शून्य, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations cim_pअगर_la_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cim_pअगर_la_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

अटल पूर्णांक cim_ma_la_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u32 *p = v;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "\n");
	पूर्ण अन्यथा अगर (idx < CIM_MALA_SIZE) अणु
		seq_म_लिखो(seq, "%02x%08x%08x%08x%08x\n",
			   p[4], p[3], p[2], p[1], p[0]);
	पूर्ण अन्यथा अणु
		अगर (idx == CIM_MALA_SIZE)
			seq_माला_दो(seq,
				 "\nCnt ID Tag UE       Data       RDY VLD\n");
		seq_म_लिखो(seq, "%3u %2u  %x   %u %08x%08x  %u   %u\n",
			   (p[2] >> 10) & 0xff, (p[2] >> 7) & 7,
			   (p[2] >> 3) & 0xf, (p[2] >> 2) & 1,
			   (p[1] >> 2) | ((p[2] & 3) << 30),
			   (p[0] >> 2) | ((p[1] & 3) << 30), (p[0] >> 1) & 1,
			   p[0] & 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cim_ma_la_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_tab *p;
	काष्ठा adapter *adap = inode->i_निजी;

	p = seq_खोलो_tab(file, 2 * CIM_MALA_SIZE, 5 * माप(u32), 1,
			 cim_ma_la_show);
	अगर (!p)
		वापस -ENOMEM;

	t4_cim_पढ़ो_ma_la(adap, (u32 *)p->data,
			  (u32 *)p->data + 5 * CIM_MALA_SIZE);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations cim_ma_la_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cim_ma_la_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

अटल पूर्णांक cim_qcfg_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर qname[] = अणु
		"TP0", "TP1", "ULP", "SGE0", "SGE1", "NC-SI",
		"ULP0", "ULP1", "ULP2", "ULP3", "SGE", "NC-SI",
		"SGE0-RX", "SGE1-RX"
	पूर्ण;

	पूर्णांक i;
	काष्ठा adapter *adap = seq->निजी;
	u16 base[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u16 size[CIM_NUM_IBQ + CIM_NUM_OBQ_T5];
	u32 stat[(4 * (CIM_NUM_IBQ + CIM_NUM_OBQ_T5))];
	u16 thres[CIM_NUM_IBQ];
	u32 obq_wr_t4[2 * CIM_NUM_OBQ], *wr;
	u32 obq_wr_t5[2 * CIM_NUM_OBQ_T5];
	u32 *p = stat;
	पूर्णांक cim_num_obq = is_t4(adap->params.chip) ?
				CIM_NUM_OBQ : CIM_NUM_OBQ_T5;

	i = t4_cim_पढ़ो(adap, is_t4(adap->params.chip) ? UP_IBQ_0_RDADDR_A :
			UP_IBQ_0_SHADOW_RDADDR_A,
			ARRAY_SIZE(stat), stat);
	अगर (!i) अणु
		अगर (is_t4(adap->params.chip)) अणु
			i = t4_cim_पढ़ो(adap, UP_OBQ_0_REALADDR_A,
					ARRAY_SIZE(obq_wr_t4), obq_wr_t4);
			wr = obq_wr_t4;
		पूर्ण अन्यथा अणु
			i = t4_cim_पढ़ो(adap, UP_OBQ_0_SHADOW_REALADDR_A,
					ARRAY_SIZE(obq_wr_t5), obq_wr_t5);
			wr = obq_wr_t5;
		पूर्ण
	पूर्ण
	अगर (i)
		वापस i;

	t4_पढ़ो_cimq_cfg(adap, base, size, thres);

	seq_म_लिखो(seq,
		   "  Queue  Base  Size Thres  RdPtr WrPtr  SOP  EOP Avail\n");
	क्रम (i = 0; i < CIM_NUM_IBQ; i++, p += 4)
		seq_म_लिखो(seq, "%7s %5x %5u %5u %6x  %4x %4u %4u %5u\n",
			   qname[i], base[i], size[i], thres[i],
			   IBQRDADDR_G(p[0]), IBQWRADDR_G(p[1]),
			   QUESOPCNT_G(p[3]), QUEEOPCNT_G(p[3]),
			   QUEREMFLITS_G(p[2]) * 16);
	क्रम ( ; i < CIM_NUM_IBQ + cim_num_obq; i++, p += 4, wr += 2)
		seq_म_लिखो(seq, "%7s %5x %5u %12x  %4x %4u %4u %5u\n",
			   qname[i], base[i], size[i],
			   QUERDADDR_G(p[0]) & 0x3fff, wr[0] - base[i],
			   QUESOPCNT_G(p[3]), QUEEOPCNT_G(p[3]),
			   QUEREMFLITS_G(p[2]) * 16);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cim_qcfg);

अटल पूर्णांक cimq_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u32 *p = v;

	seq_म_लिखो(seq, "%#06x: %08x %08x %08x %08x\n", idx * 16, p[0], p[1],
		   p[2], p[3]);
	वापस 0;
पूर्ण

अटल पूर्णांक cim_ibq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा seq_tab *p;
	अचिन्हित पूर्णांक qid = (uपूर्णांकptr_t)inode->i_निजी & 7;
	काष्ठा adapter *adap = inode->i_निजी - qid;

	p = seq_खोलो_tab(file, CIM_IBQ_SIZE, 4 * माप(u32), 0, cimq_show);
	अगर (!p)
		वापस -ENOMEM;

	ret = t4_पढ़ो_cim_ibq(adap, qid, (u32 *)p->data, CIM_IBQ_SIZE * 4);
	अगर (ret < 0)
		seq_release_निजी(inode, file);
	अन्यथा
		ret = 0;
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations cim_ibq_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cim_ibq_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

अटल पूर्णांक cim_obq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret;
	काष्ठा seq_tab *p;
	अचिन्हित पूर्णांक qid = (uपूर्णांकptr_t)inode->i_निजी & 7;
	काष्ठा adapter *adap = inode->i_निजी - qid;

	p = seq_खोलो_tab(file, 6 * CIM_OBQ_SIZE, 4 * माप(u32), 0, cimq_show);
	अगर (!p)
		वापस -ENOMEM;

	ret = t4_पढ़ो_cim_obq(adap, qid, (u32 *)p->data, 6 * CIM_OBQ_SIZE * 4);
	अगर (ret < 0) अणु
		seq_release_निजी(inode, file);
	पूर्ण अन्यथा अणु
		seq_tab_trim(p, ret / 4);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations cim_obq_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = cim_obq_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

काष्ठा field_desc अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक start;
	अचिन्हित पूर्णांक width;
पूर्ण;

अटल व्योम field_desc_show(काष्ठा seq_file *seq, u64 v,
			    स्थिर काष्ठा field_desc *p)
अणु
	अक्षर buf[32];
	पूर्णांक line_size = 0;

	जबतक (p->name) अणु
		u64 mask = (1ULL << p->width) - 1;
		पूर्णांक len = scnम_लिखो(buf, माप(buf), "%s: %llu", p->name,
				    ((अचिन्हित दीर्घ दीर्घ)v >> p->start) & mask);

		अगर (line_size + len >= 79) अणु
			line_size = 8;
			seq_माला_दो(seq, "\n        ");
		पूर्ण
		seq_म_लिखो(seq, "%s ", buf);
		line_size += len + 1;
		p++;
	पूर्ण
	seq_अ_दो(seq, '\n');
पूर्ण

अटल काष्ठा field_desc tp_la0[] = अणु
	अणु "RcfOpCodeOut", 60, 4 पूर्ण,
	अणु "State", 56, 4 पूर्ण,
	अणु "WcfState", 52, 4 पूर्ण,
	अणु "RcfOpcSrcOut", 50, 2 पूर्ण,
	अणु "CRxError", 49, 1 पूर्ण,
	अणु "ERxError", 48, 1 पूर्ण,
	अणु "SanityFailed", 47, 1 पूर्ण,
	अणु "SpuriousMsg", 46, 1 पूर्ण,
	अणु "FlushInputMsg", 45, 1 पूर्ण,
	अणु "FlushInputCpl", 44, 1 पूर्ण,
	अणु "RssUpBit", 43, 1 पूर्ण,
	अणु "RssFilterHit", 42, 1 पूर्ण,
	अणु "Tid", 32, 10 पूर्ण,
	अणु "InitTcb", 31, 1 पूर्ण,
	अणु "LineNumber", 24, 7 पूर्ण,
	अणु "Emsg", 23, 1 पूर्ण,
	अणु "EdataOut", 22, 1 पूर्ण,
	अणु "Cmsg", 21, 1 पूर्ण,
	अणु "CdataOut", 20, 1 पूर्ण,
	अणु "EreadPdu", 19, 1 पूर्ण,
	अणु "CreadPdu", 18, 1 पूर्ण,
	अणु "TunnelPkt", 17, 1 पूर्ण,
	अणु "RcfPeerFin", 16, 1 पूर्ण,
	अणु "RcfReasonOut", 12, 4 पूर्ण,
	अणु "TxCchannel", 10, 2 पूर्ण,
	अणु "RcfTxChannel", 8, 2 पूर्ण,
	अणु "RxEchannel", 6, 2 पूर्ण,
	अणु "RcfRxChannel", 5, 1 पूर्ण,
	अणु "RcfDataOutSrdy", 4, 1 पूर्ण,
	अणु "RxDvld", 3, 1 पूर्ण,
	अणु "RxOoDvld", 2, 1 पूर्ण,
	अणु "RxCongestion", 1, 1 पूर्ण,
	अणु "TxCongestion", 0, 1 पूर्ण,
	अणु शून्य पूर्ण
पूर्ण;

अटल पूर्णांक tp_la_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u64 *p = v;

	field_desc_show(seq, *p, tp_la0);
	वापस 0;
पूर्ण

अटल पूर्णांक tp_la_show2(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u64 *p = v;

	अगर (idx)
		seq_अ_दो(seq, '\n');
	field_desc_show(seq, p[0], tp_la0);
	अगर (idx < (TPLA_SIZE / 2 - 1) || p[1] != ~0ULL)
		field_desc_show(seq, p[1], tp_la0);
	वापस 0;
पूर्ण

अटल पूर्णांक tp_la_show3(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अटल काष्ठा field_desc tp_la1[] = अणु
		अणु "CplCmdIn", 56, 8 पूर्ण,
		अणु "CplCmdOut", 48, 8 पूर्ण,
		अणु "ESynOut", 47, 1 पूर्ण,
		अणु "EAckOut", 46, 1 पूर्ण,
		अणु "EFinOut", 45, 1 पूर्ण,
		अणु "ERstOut", 44, 1 पूर्ण,
		अणु "SynIn", 43, 1 पूर्ण,
		अणु "AckIn", 42, 1 पूर्ण,
		अणु "FinIn", 41, 1 पूर्ण,
		अणु "RstIn", 40, 1 पूर्ण,
		अणु "DataIn", 39, 1 पूर्ण,
		अणु "DataInVld", 38, 1 पूर्ण,
		अणु "PadIn", 37, 1 पूर्ण,
		अणु "RxBufEmpty", 36, 1 पूर्ण,
		अणु "RxDdp", 35, 1 पूर्ण,
		अणु "RxFbCongestion", 34, 1 पूर्ण,
		अणु "TxFbCongestion", 33, 1 पूर्ण,
		अणु "TxPktSumSrdy", 32, 1 पूर्ण,
		अणु "RcfUlpType", 28, 4 पूर्ण,
		अणु "Eread", 27, 1 पूर्ण,
		अणु "Ebypass", 26, 1 पूर्ण,
		अणु "Esave", 25, 1 पूर्ण,
		अणु "Static0", 24, 1 पूर्ण,
		अणु "Cread", 23, 1 पूर्ण,
		अणु "Cbypass", 22, 1 पूर्ण,
		अणु "Csave", 21, 1 पूर्ण,
		अणु "CPktOut", 20, 1 पूर्ण,
		अणु "RxPagePoolFull", 18, 2 पूर्ण,
		अणु "RxLpbkPkt", 17, 1 पूर्ण,
		अणु "TxLpbkPkt", 16, 1 पूर्ण,
		अणु "RxVfValid", 15, 1 पूर्ण,
		अणु "SynLearned", 14, 1 पूर्ण,
		अणु "SetDelEntry", 13, 1 पूर्ण,
		अणु "SetInvEntry", 12, 1 पूर्ण,
		अणु "CpcmdDvld", 11, 1 पूर्ण,
		अणु "CpcmdSave", 10, 1 पूर्ण,
		अणु "RxPstructsFull", 8, 2 पूर्ण,
		अणु "EpcmdDvld", 7, 1 पूर्ण,
		अणु "EpcmdFlush", 6, 1 पूर्ण,
		अणु "EpcmdTrimPrefix", 5, 1 पूर्ण,
		अणु "EpcmdTrimPostfix", 4, 1 पूर्ण,
		अणु "ERssIp4Pkt", 3, 1 पूर्ण,
		अणु "ERssIp6Pkt", 2, 1 पूर्ण,
		अणु "ERssTcpUdpPkt", 1, 1 पूर्ण,
		अणु "ERssFceFipPkt", 0, 1 पूर्ण,
		अणु शून्य पूर्ण
	पूर्ण;
	अटल काष्ठा field_desc tp_la2[] = अणु
		अणु "CplCmdIn", 56, 8 पूर्ण,
		अणु "MpsVfVld", 55, 1 पूर्ण,
		अणु "MpsPf", 52, 3 पूर्ण,
		अणु "MpsVf", 44, 8 पूर्ण,
		अणु "SynIn", 43, 1 पूर्ण,
		अणु "AckIn", 42, 1 पूर्ण,
		अणु "FinIn", 41, 1 पूर्ण,
		अणु "RstIn", 40, 1 पूर्ण,
		अणु "DataIn", 39, 1 पूर्ण,
		अणु "DataInVld", 38, 1 पूर्ण,
		अणु "PadIn", 37, 1 पूर्ण,
		अणु "RxBufEmpty", 36, 1 पूर्ण,
		अणु "RxDdp", 35, 1 पूर्ण,
		अणु "RxFbCongestion", 34, 1 पूर्ण,
		अणु "TxFbCongestion", 33, 1 पूर्ण,
		अणु "TxPktSumSrdy", 32, 1 पूर्ण,
		अणु "RcfUlpType", 28, 4 पूर्ण,
		अणु "Eread", 27, 1 पूर्ण,
		अणु "Ebypass", 26, 1 पूर्ण,
		अणु "Esave", 25, 1 पूर्ण,
		अणु "Static0", 24, 1 पूर्ण,
		अणु "Cread", 23, 1 पूर्ण,
		अणु "Cbypass", 22, 1 पूर्ण,
		अणु "Csave", 21, 1 पूर्ण,
		अणु "CPktOut", 20, 1 पूर्ण,
		अणु "RxPagePoolFull", 18, 2 पूर्ण,
		अणु "RxLpbkPkt", 17, 1 पूर्ण,
		अणु "TxLpbkPkt", 16, 1 पूर्ण,
		अणु "RxVfValid", 15, 1 पूर्ण,
		अणु "SynLearned", 14, 1 पूर्ण,
		अणु "SetDelEntry", 13, 1 पूर्ण,
		अणु "SetInvEntry", 12, 1 पूर्ण,
		अणु "CpcmdDvld", 11, 1 पूर्ण,
		अणु "CpcmdSave", 10, 1 पूर्ण,
		अणु "RxPstructsFull", 8, 2 पूर्ण,
		अणु "EpcmdDvld", 7, 1 पूर्ण,
		अणु "EpcmdFlush", 6, 1 पूर्ण,
		अणु "EpcmdTrimPrefix", 5, 1 पूर्ण,
		अणु "EpcmdTrimPostfix", 4, 1 पूर्ण,
		अणु "ERssIp4Pkt", 3, 1 पूर्ण,
		अणु "ERssIp6Pkt", 2, 1 पूर्ण,
		अणु "ERssTcpUdpPkt", 1, 1 पूर्ण,
		अणु "ERssFceFipPkt", 0, 1 पूर्ण,
		अणु शून्य पूर्ण
	पूर्ण;
	स्थिर u64 *p = v;

	अगर (idx)
		seq_अ_दो(seq, '\n');
	field_desc_show(seq, p[0], tp_la0);
	अगर (idx < (TPLA_SIZE / 2 - 1) || p[1] != ~0ULL)
		field_desc_show(seq, p[1], (p[0] & BIT(17)) ? tp_la2 : tp_la1);
	वापस 0;
पूर्ण

अटल पूर्णांक tp_la_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_tab *p;
	काष्ठा adapter *adap = inode->i_निजी;

	चयन (DBGLAMODE_G(t4_पढ़ो_reg(adap, TP_DBG_LA_CONFIG_A))) अणु
	हाल 2:
		p = seq_खोलो_tab(file, TPLA_SIZE / 2, 2 * माप(u64), 0,
				 tp_la_show2);
		अवरोध;
	हाल 3:
		p = seq_खोलो_tab(file, TPLA_SIZE / 2, 2 * माप(u64), 0,
				 tp_la_show3);
		अवरोध;
	शेष:
		p = seq_खोलो_tab(file, TPLA_SIZE, माप(u64), 0, tp_la_show);
	पूर्ण
	अगर (!p)
		वापस -ENOMEM;

	t4_tp_पढ़ो_la(adap, (u64 *)p->data, शून्य);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार tp_la_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक err;
	अक्षर s[32];
	अचिन्हित दीर्घ val;
	माप_प्रकार size = min(माप(s) - 1, count);
	काष्ठा adapter *adap = file_inode(file)->i_निजी;

	अगर (copy_from_user(s, buf, size))
		वापस -EFAULT;
	s[size] = '\0';
	err = kम_से_अदीर्घ(s, 0, &val);
	अगर (err)
		वापस err;
	अगर (val > 0xffff)
		वापस -EINVAL;
	adap->params.tp.la_mask = val << 16;
	t4_set_reg_field(adap, TP_DBG_LA_CONFIG_A, 0xffff0000U,
			 adap->params.tp.la_mask);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations tp_la_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = tp_la_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी,
	.ग_लिखो   = tp_la_ग_लिखो
पूर्ण;

अटल पूर्णांक ulprx_la_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	स्थिर u32 *p = v;

	अगर (v == SEQ_START_TOKEN)
		seq_माला_दो(seq, "      Pcmd        Type   Message"
			 "                Data\n");
	अन्यथा
		seq_म_लिखो(seq, "%08x%08x  %4x  %08x  %08x%08x%08x%08x\n",
			   p[1], p[0], p[2], p[3], p[7], p[6], p[5], p[4]);
	वापस 0;
पूर्ण

अटल पूर्णांक ulprx_la_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_tab *p;
	काष्ठा adapter *adap = inode->i_निजी;

	p = seq_खोलो_tab(file, ULPRX_LA_SIZE, 8 * माप(u32), 1,
			 ulprx_la_show);
	अगर (!p)
		वापस -ENOMEM;

	t4_ulprx_पढ़ो_la(adap, (u32 *)p->data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations ulprx_la_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = ulprx_la_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

/* Show the PM memory stats.  These stats include:
 *
 * TX:
 *   Read: memory पढ़ो operation
 *   Write Bypass: cut-through
 *   Bypass + mem: cut-through and save copy
 *
 * RX:
 *   Read: memory पढ़ो
 *   Write Bypass: cut-through
 *   Flush: payload trim or drop
 */
अटल पूर्णांक pm_stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर tx_pm_stats[] = अणु
		"Read:", "Write bypass:", "Write mem:", "Bypass + mem:"
	पूर्ण;
	अटल स्थिर अक्षर * स्थिर rx_pm_stats[] = अणु
		"Read:", "Write bypass:", "Write mem:", "Flush:"
	पूर्ण;

	पूर्णांक i;
	u32 tx_cnt[T6_PM_NSTATS], rx_cnt[T6_PM_NSTATS];
	u64 tx_cyc[T6_PM_NSTATS], rx_cyc[T6_PM_NSTATS];
	काष्ठा adapter *adap = seq->निजी;

	t4_pmtx_get_stats(adap, tx_cnt, tx_cyc);
	t4_pmrx_get_stats(adap, rx_cnt, rx_cyc);

	seq_म_लिखो(seq, "%13s %10s  %20s\n", " ", "Tx pcmds", "Tx bytes");
	क्रम (i = 0; i < PM_NSTATS - 1; i++)
		seq_म_लिखो(seq, "%-13s %10u  %20llu\n",
			   tx_pm_stats[i], tx_cnt[i], tx_cyc[i]);

	seq_म_लिखो(seq, "%13s %10s  %20s\n", " ", "Rx pcmds", "Rx bytes");
	क्रम (i = 0; i < PM_NSTATS - 1; i++)
		seq_म_लिखो(seq, "%-13s %10u  %20llu\n",
			   rx_pm_stats[i], rx_cnt[i], rx_cyc[i]);

	अगर (CHELSIO_CHIP_VERSION(adap->params.chip) > CHELSIO_T5) अणु
		/* In T5 the granularity of the total रुको is too fine.
		 * It is not useful as it reaches the max value too fast.
		 * Hence display this Input FIFO रुको क्रम T6 onwards.
		 */
		seq_म_लिखो(seq, "%13s %10s  %20s\n",
			   " ", "Total wait", "Total Occupancy");
		seq_म_लिखो(seq, "Tx FIFO wait  %10u  %20llu\n",
			   tx_cnt[i], tx_cyc[i]);
		seq_म_लिखो(seq, "Rx FIFO wait  %10u  %20llu\n",
			   rx_cnt[i], rx_cyc[i]);

		/* Skip index 6 as there is nothing useful ihere */
		i += 2;

		/* At index 7, a new stat क्रम पढ़ो latency (count, total रुको)
		 * is added.
		 */
		seq_म_लिखो(seq, "%13s %10s  %20s\n",
			   " ", "Reads", "Total wait");
		seq_म_लिखो(seq, "Tx latency    %10u  %20llu\n",
			   tx_cnt[i], tx_cyc[i]);
		seq_म_लिखो(seq, "Rx latency    %10u  %20llu\n",
			   rx_cnt[i], rx_cyc[i]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक pm_stats_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, pm_stats_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार pm_stats_clear(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा adapter *adap = file_inode(file)->i_निजी;

	t4_ग_लिखो_reg(adap, PM_RX_STAT_CONFIG_A, 0);
	t4_ग_लिखो_reg(adap, PM_TX_STAT_CONFIG_A, 0);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations pm_stats_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = pm_stats_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = single_release,
	.ग_लिखो   = pm_stats_clear
पूर्ण;

अटल पूर्णांक tx_rate_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	u64 nrate[NCHAN], orate[NCHAN];
	काष्ठा adapter *adap = seq->निजी;

	t4_get_chan_txrate(adap, nrate, orate);
	अगर (adap->params.arch.nchan == NCHAN) अणु
		seq_माला_दो(seq, "              channel 0   channel 1   "
			 "channel 2   channel 3\n");
		seq_म_लिखो(seq, "NIC B/s:     %10llu  %10llu  %10llu  %10llu\n",
			   (अचिन्हित दीर्घ दीर्घ)nrate[0],
			   (अचिन्हित दीर्घ दीर्घ)nrate[1],
			   (अचिन्हित दीर्घ दीर्घ)nrate[2],
			   (अचिन्हित दीर्घ दीर्घ)nrate[3]);
		seq_म_लिखो(seq, "Offload B/s: %10llu  %10llu  %10llu  %10llu\n",
			   (अचिन्हित दीर्घ दीर्घ)orate[0],
			   (अचिन्हित दीर्घ दीर्घ)orate[1],
			   (अचिन्हित दीर्घ दीर्घ)orate[2],
			   (अचिन्हित दीर्घ दीर्घ)orate[3]);
	पूर्ण अन्यथा अणु
		seq_माला_दो(seq, "              channel 0   channel 1\n");
		seq_म_लिखो(seq, "NIC B/s:     %10llu  %10llu\n",
			   (अचिन्हित दीर्घ दीर्घ)nrate[0],
			   (अचिन्हित दीर्घ दीर्घ)nrate[1]);
		seq_म_लिखो(seq, "Offload B/s: %10llu  %10llu\n",
			   (अचिन्हित दीर्घ दीर्घ)orate[0],
			   (अचिन्हित दीर्घ दीर्घ)orate[1]);
	पूर्ण
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tx_rate);

अटल पूर्णांक cctrl_tbl_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर dec_fac[] = अणु
		"0.5", "0.5625", "0.625", "0.6875", "0.75", "0.8125", "0.875",
		"0.9375" पूर्ण;

	पूर्णांक i;
	u16 (*incr)[NCCTRL_WIN];
	काष्ठा adapter *adap = seq->निजी;

	incr = kदो_स्मृति_array(NMTUS, माप(*incr), GFP_KERNEL);
	अगर (!incr)
		वापस -ENOMEM;

	t4_पढ़ो_cong_tbl(adap, incr);

	क्रम (i = 0; i < NCCTRL_WIN; ++i) अणु
		seq_म_लिखो(seq, "%2d: %4u %4u %4u %4u %4u %4u %4u %4u\n", i,
			   incr[0][i], incr[1][i], incr[2][i], incr[3][i],
			   incr[4][i], incr[5][i], incr[6][i], incr[7][i]);
		seq_म_लिखो(seq, "%8u %4u %4u %4u %4u %4u %4u %4u %5u %s\n",
			   incr[8][i], incr[9][i], incr[10][i], incr[11][i],
			   incr[12][i], incr[13][i], incr[14][i], incr[15][i],
			   adap->params.a_wnd[i],
			   dec_fac[adap->params.b_wnd[i]]);
	पूर्ण

	kमुक्त(incr);
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(cctrl_tbl);

/* Format a value in a unit that dअगरfers from the value's native unit by the
 * given factor.
 */
अटल अक्षर *unit_conv(अक्षर *buf, माप_प्रकार len, अचिन्हित पूर्णांक val,
		       अचिन्हित पूर्णांक factor)
अणु
	अचिन्हित पूर्णांक rem = val % factor;

	अगर (rem == 0) अणु
		snम_लिखो(buf, len, "%u", val / factor);
	पूर्ण अन्यथा अणु
		जबतक (rem % 10 == 0)
			rem /= 10;
		snम_लिखो(buf, len, "%u.%u", val / factor, rem);
	पूर्ण
	वापस buf;
पूर्ण

अटल पूर्णांक clk_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अक्षर buf[32];
	काष्ठा adapter *adap = seq->निजी;
	अचिन्हित पूर्णांक cclk_ps = 1000000000 / adap->params.vpd.cclk;  /* in ps */
	u32 res = t4_पढ़ो_reg(adap, TP_TIMER_RESOLUTION_A);
	अचिन्हित पूर्णांक tre = TIMERRESOLUTION_G(res);
	अचिन्हित पूर्णांक dack_re = DELAYEDACKRESOLUTION_G(res);
	अचिन्हित दीर्घ दीर्घ tp_tick_us = (cclk_ps << tre) / 1000000; /* in us */

	seq_म_लिखो(seq, "Core clock period: %s ns\n",
		   unit_conv(buf, माप(buf), cclk_ps, 1000));
	seq_म_लिखो(seq, "TP timer tick: %s us\n",
		   unit_conv(buf, माप(buf), (cclk_ps << tre), 1000000));
	seq_म_लिखो(seq, "TCP timestamp tick: %s us\n",
		   unit_conv(buf, माप(buf),
			     (cclk_ps << TIMESTAMPRESOLUTION_G(res)), 1000000));
	seq_म_लिखो(seq, "DACK tick: %s us\n",
		   unit_conv(buf, माप(buf), (cclk_ps << dack_re), 1000000));
	seq_म_लिखो(seq, "DACK timer: %u us\n",
		   ((cclk_ps << dack_re) / 1000000) *
		   t4_पढ़ो_reg(adap, TP_DACK_TIMER_A));
	seq_म_लिखो(seq, "Retransmit min: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_RXT_MIN_A));
	seq_म_लिखो(seq, "Retransmit max: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_RXT_MAX_A));
	seq_म_लिखो(seq, "Persist timer min: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_PERS_MIN_A));
	seq_म_लिखो(seq, "Persist timer max: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_PERS_MAX_A));
	seq_म_लिखो(seq, "Keepalive idle timer: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_KEEP_IDLE_A));
	seq_म_लिखो(seq, "Keepalive interval: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_KEEP_INTVL_A));
	seq_म_लिखो(seq, "Initial SRTT: %llu us\n",
		   tp_tick_us * INITSRTT_G(t4_पढ़ो_reg(adap, TP_INIT_SRTT_A)));
	seq_म_लिखो(seq, "FINWAIT2 timer: %llu us\n",
		   tp_tick_us * t4_पढ़ो_reg(adap, TP_FINWAIT2_TIMER_A));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(clk);

/* Firmware Device Log dump. */
अटल स्थिर अक्षर * स्थिर devlog_level_strings[] = अणु
	[FW_DEVLOG_LEVEL_EMERG]		= "EMERG",
	[FW_DEVLOG_LEVEL_CRIT]		= "CRIT",
	[FW_DEVLOG_LEVEL_ERR]		= "ERR",
	[FW_DEVLOG_LEVEL_NOTICE]	= "NOTICE",
	[FW_DEVLOG_LEVEL_INFO]		= "INFO",
	[FW_DEVLOG_LEVEL_DEBUG]		= "DEBUG"
पूर्ण;

अटल स्थिर अक्षर * स्थिर devlog_facility_strings[] = अणु
	[FW_DEVLOG_FACILITY_CORE]	= "CORE",
	[FW_DEVLOG_FACILITY_CF]         = "CF",
	[FW_DEVLOG_FACILITY_SCHED]	= "SCHED",
	[FW_DEVLOG_FACILITY_TIMER]	= "TIMER",
	[FW_DEVLOG_FACILITY_RES]	= "RES",
	[FW_DEVLOG_FACILITY_HW]		= "HW",
	[FW_DEVLOG_FACILITY_FLR]	= "FLR",
	[FW_DEVLOG_FACILITY_DMAQ]	= "DMAQ",
	[FW_DEVLOG_FACILITY_PHY]	= "PHY",
	[FW_DEVLOG_FACILITY_MAC]	= "MAC",
	[FW_DEVLOG_FACILITY_PORT]	= "PORT",
	[FW_DEVLOG_FACILITY_VI]		= "VI",
	[FW_DEVLOG_FACILITY_FILTER]	= "FILTER",
	[FW_DEVLOG_FACILITY_ACL]	= "ACL",
	[FW_DEVLOG_FACILITY_TM]		= "TM",
	[FW_DEVLOG_FACILITY_QFC]	= "QFC",
	[FW_DEVLOG_FACILITY_DCB]	= "DCB",
	[FW_DEVLOG_FACILITY_ETH]	= "ETH",
	[FW_DEVLOG_FACILITY_OFLD]	= "OFLD",
	[FW_DEVLOG_FACILITY_RI]		= "RI",
	[FW_DEVLOG_FACILITY_ISCSI]	= "ISCSI",
	[FW_DEVLOG_FACILITY_FCOE]	= "FCOE",
	[FW_DEVLOG_FACILITY_FOISCSI]	= "FOISCSI",
	[FW_DEVLOG_FACILITY_FOFCOE]	= "FOFCOE"
पूर्ण;

/* Inक्रमmation gathered by Device Log Open routine क्रम the display routine.
 */
काष्ठा devlog_info अणु
	अचिन्हित पूर्णांक nentries;		/* number of entries in log[] */
	अचिन्हित पूर्णांक first;		/* first [temporal] entry in log[] */
	काष्ठा fw_devlog_e log[];	/* Firmware Device Log */
पूर्ण;

/* Dump a Firmaware Device Log entry.
 */
अटल पूर्णांक devlog_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अगर (v == SEQ_START_TOKEN)
		seq_म_लिखो(seq, "%10s  %15s  %8s  %8s  %s\n",
			   "Seq#", "Tstamp", "Level", "Facility", "Message");
	अन्यथा अणु
		काष्ठा devlog_info *dinfo = seq->निजी;
		पूर्णांक fidx = (uपूर्णांकptr_t)v - 2;
		अचिन्हित दीर्घ index;
		काष्ठा fw_devlog_e *e;

		/* Get a poपूर्णांकer to the log entry to display.  Skip unused log
		 * entries.
		 */
		index = dinfo->first + fidx;
		अगर (index >= dinfo->nentries)
			index -= dinfo->nentries;
		e = &dinfo->log[index];
		अगर (e->बारtamp == 0)
			वापस 0;

		/* Prपूर्णांक the message.  This depends on the firmware using
		 * exactly the same क्रमmating strings as the kernel so we may
		 * eventually have to put a क्रमmat पूर्णांकerpreter in here ...
		 */
		seq_म_लिखो(seq, "%10d  %15llu  %8s  %8s  ",
			   be32_to_cpu(e->seqno),
			   be64_to_cpu(e->बारtamp),
			   (e->level < ARRAY_SIZE(devlog_level_strings)
			    ? devlog_level_strings[e->level]
			    : "UNKNOWN"),
			   (e->facility < ARRAY_SIZE(devlog_facility_strings)
			    ? devlog_facility_strings[e->facility]
			    : "UNKNOWN"));
		seq_म_लिखो(seq, e->fmt,
			   be32_to_cpu(e->params[0]),
			   be32_to_cpu(e->params[1]),
			   be32_to_cpu(e->params[2]),
			   be32_to_cpu(e->params[3]),
			   be32_to_cpu(e->params[4]),
			   be32_to_cpu(e->params[5]),
			   be32_to_cpu(e->params[6]),
			   be32_to_cpu(e->params[7]));
	पूर्ण
	वापस 0;
पूर्ण

/* Sequential File Operations क्रम Device Log.
 */
अटल अंतरभूत व्योम *devlog_get_idx(काष्ठा devlog_info *dinfo, loff_t pos)
अणु
	अगर (pos > dinfo->nentries)
		वापस शून्य;

	वापस (व्योम *)(uपूर्णांकptr_t)(pos + 1);
पूर्ण

अटल व्योम *devlog_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा devlog_info *dinfo = seq->निजी;

	वापस (*pos
		? devlog_get_idx(dinfo, *pos)
		: SEQ_START_TOKEN);
पूर्ण

अटल व्योम *devlog_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा devlog_info *dinfo = seq->निजी;

	(*pos)++;
	वापस devlog_get_idx(dinfo, *pos);
पूर्ण

अटल व्योम devlog_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations devlog_seq_ops = अणु
	.start = devlog_start,
	.next  = devlog_next,
	.stop  = devlog_stop,
	.show  = devlog_show
पूर्ण;

/* Set up क्रम पढ़ोing the firmware's device log.  We पढ़ो the entire log here
 * and then display it incrementally in devlog_show().
 */
अटल पूर्णांक devlog_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adapter *adap = inode->i_निजी;
	काष्ठा devlog_params *dparams = &adap->params.devlog;
	काष्ठा devlog_info *dinfo;
	अचिन्हित पूर्णांक index;
	u32 fseqno;
	पूर्णांक ret;

	/* If we करोn't know where the log is we can't करो anything.
	 */
	अगर (dparams->start == 0)
		वापस -ENXIO;

	/* Allocate the space to पढ़ो in the firmware's device log and set up
	 * क्रम the iterated call to our display function.
	 */
	dinfo = __seq_खोलो_निजी(file, &devlog_seq_ops,
				   माप(*dinfo) + dparams->size);
	अगर (!dinfo)
		वापस -ENOMEM;

	/* Record the basic log buffer inक्रमmation and पढ़ो in the raw log.
	 */
	dinfo->nentries = (dparams->size / माप(काष्ठा fw_devlog_e));
	dinfo->first = 0;
	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, adap->params.drv_memwin, dparams->memtype,
			   dparams->start, dparams->size, (__be32 *)dinfo->log,
			   T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	अगर (ret) अणु
		seq_release_निजी(inode, file);
		वापस ret;
	पूर्ण

	/* Find the earliest (lowest Sequence Number) log entry in the
	 * circular Device Log.
	 */
	क्रम (fseqno = ~((u32)0), index = 0; index < dinfo->nentries; index++) अणु
		काष्ठा fw_devlog_e *e = &dinfo->log[index];
		__u32 seqno;

		अगर (e->बारtamp == 0)
			जारी;

		seqno = be32_to_cpu(e->seqno);
		अगर (seqno < fseqno) अणु
			fseqno = seqno;
			dinfo->first = index;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations devlog_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = devlog_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

/* Show Firmware Mailbox Command/Reply Log
 *
 * Note that we करोn't करो any locking when dumping the Firmware Mailbox Log so
 * it's possible that we can catch things during a log update and thereक्रमe
 * see partially corrupted log entries.  But it's probably Good Enough(पंचांग).
 * If we ever decide that we want to make sure that we're dumping a coherent
 * log, we'd need to perक्रमm locking in the mailbox logging and in
 * mboxlog_खोलो() where we'd need to grab the entire mailbox log in one go
 * like we करो क्रम the Firmware Device Log.
 */
अटल पूर्णांक mboxlog_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;
	काष्ठा mbox_cmd *entry;
	पूर्णांक entry_idx, i;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_म_लिखो(seq,
			   "%10s  %15s  %5s  %5s  %s\n",
			   "Seq#", "Tstamp", "Atime", "Etime",
			   "Command/Reply");
		वापस 0;
	पूर्ण

	entry_idx = log->cursor + ((uपूर्णांकptr_t)v - 2);
	अगर (entry_idx >= log->size)
		entry_idx -= log->size;
	entry = mbox_cmd_log_entry(log, entry_idx);

	/* skip over unused entries */
	अगर (entry->बारtamp == 0)
		वापस 0;

	seq_म_लिखो(seq, "%10u  %15llu  %5d  %5d",
		   entry->seqno, entry->बारtamp,
		   entry->access, entry->execute);
	क्रम (i = 0; i < MBOX_LEN / 8; i++) अणु
		u64 flit = entry->cmd[i];
		u32 hi = (u32)(flit >> 32);
		u32 lo = (u32)flit;

		seq_म_लिखो(seq, "  %08x %08x", hi, lo);
	पूर्ण
	seq_माला_दो(seq, "\n");
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *mboxlog_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा mbox_cmd_log *log = adapter->mbox_log;

	वापस ((pos <= log->size) ? (व्योम *)(uपूर्णांकptr_t)(pos + 1) : शून्य);
पूर्ण

अटल व्योम *mboxlog_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? mboxlog_get_idx(seq, *pos) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *mboxlog_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस mboxlog_get_idx(seq, *pos);
पूर्ण

अटल व्योम mboxlog_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations mboxlog_seq_ops = अणु
	.start = mboxlog_start,
	.next  = mboxlog_next,
	.stop  = mboxlog_stop,
	.show  = mboxlog_show
पूर्ण;

अटल पूर्णांक mboxlog_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक res = seq_खोलो(file, &mboxlog_seq_ops);

	अगर (!res) अणु
		काष्ठा seq_file *seq = file->निजी_data;

		seq->निजी = inode->i_निजी;
	पूर्ण
	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations mboxlog_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = mboxlog_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;

अटल पूर्णांक mbox_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर owner[] = अणु "none", "FW", "driver",
					      "unknown", "<unread>" पूर्ण;

	पूर्णांक i;
	अचिन्हित पूर्णांक mbox = (uपूर्णांकptr_t)seq->निजी & 7;
	काष्ठा adapter *adap = seq->निजी - mbox;
	व्योम __iomem *addr = adap->regs + PF_REG(mbox, CIM_PF_MAILBOX_DATA_A);

	/* For T4 we करोn't have a shaकरोw copy of the Mailbox Control रेजिस्टर.
	 * And since पढ़ोing that real रेजिस्टर causes a side effect of
	 * granting ownership, we're best of simply not पढ़ोing it at all.
	 */
	अगर (is_t4(adap->params.chip)) अणु
		i = 4; /* index of "<unread>" */
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक ctrl_reg = CIM_PF_MAILBOX_CTRL_SHADOW_COPY_A;
		व्योम __iomem *ctrl = adap->regs + PF_REG(mbox, ctrl_reg);

		i = MBOWNER_G(पढ़ोl(ctrl));
	पूर्ण

	seq_म_लिखो(seq, "mailbox owned by %s\n\n", owner[i]);

	क्रम (i = 0; i < MBOX_LEN; i += 8)
		seq_म_लिखो(seq, "%016llx\n",
			   (अचिन्हित दीर्घ दीर्घ)पढ़ोq(addr + i));
	वापस 0;
पूर्ण

अटल पूर्णांक mbox_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mbox_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार mbox_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक i;
	अक्षर c = '\n', s[256];
	अचिन्हित दीर्घ दीर्घ data[8];
	स्थिर काष्ठा inode *ino;
	अचिन्हित पूर्णांक mbox;
	काष्ठा adapter *adap;
	व्योम __iomem *addr;
	व्योम __iomem *ctrl;

	अगर (count > माप(s) - 1 || !count)
		वापस -EINVAL;
	अगर (copy_from_user(s, buf, count))
		वापस -EFAULT;
	s[count] = '\0';

	अगर (माला_पूछो(s, "%llx %llx %llx %llx %llx %llx %llx %llx%c", &data[0],
		   &data[1], &data[2], &data[3], &data[4], &data[5], &data[6],
		   &data[7], &c) < 8 || c != '\n')
		वापस -EINVAL;

	ino = file_inode(file);
	mbox = (uपूर्णांकptr_t)ino->i_निजी & 7;
	adap = ino->i_निजी - mbox;
	addr = adap->regs + PF_REG(mbox, CIM_PF_MAILBOX_DATA_A);
	ctrl = addr + MBOX_LEN;

	अगर (MBOWNER_G(पढ़ोl(ctrl)) != X_MBOWNER_PL)
		वापस -EBUSY;

	क्रम (i = 0; i < 8; i++)
		ग_लिखोq(data[i], addr + 8 * i);

	ग_लिखोl(MBMSGVALID_F | MBOWNER_V(X_MBOWNER_FW), ctrl);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mbox_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = mbox_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = single_release,
	.ग_लिखो   = mbox_ग_लिखो
पूर्ण;

अटल पूर्णांक mps_trc_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक enabled, i;
	काष्ठा trace_params tp;
	अचिन्हित पूर्णांक trcidx = (uपूर्णांकptr_t)seq->निजी & 3;
	काष्ठा adapter *adap = seq->निजी - trcidx;

	t4_get_trace_filter(adap, &tp, trcidx, &enabled);
	अगर (!enabled) अणु
		seq_माला_दो(seq, "tracer is disabled\n");
		वापस 0;
	पूर्ण

	अगर (tp.skip_ofst * 8 >= TRACE_LEN) अणु
		dev_err(adap->pdev_dev, "illegal trace pattern skip offset\n");
		वापस -EINVAL;
	पूर्ण
	अगर (tp.port < 8) अणु
		i = adap->chan_map[tp.port & 3];
		अगर (i >= MAX_NPORTS) अणु
			dev_err(adap->pdev_dev, "tracer %u is assigned "
				"to non-existing port\n", trcidx);
			वापस -EINVAL;
		पूर्ण
		seq_म_लिखो(seq, "tracer is capturing %s %s, ",
			   adap->port[i]->name, tp.port < 4 ? "Rx" : "Tx");
	पूर्ण अन्यथा
		seq_म_लिखो(seq, "tracer is capturing loopback %d, ",
			   tp.port - 8);
	seq_म_लिखो(seq, "snap length: %u, min length: %u\n", tp.snap_len,
		   tp.min_len);
	seq_म_लिखो(seq, "packets captured %smatch filter\n",
		   tp.invert ? "do not " : "");

	अगर (tp.skip_ofst) अणु
		seq_माला_दो(seq, "filter pattern: ");
		क्रम (i = 0; i < tp.skip_ofst * 2; i += 2)
			seq_म_लिखो(seq, "%08x%08x", tp.data[i], tp.data[i + 1]);
		seq_अ_दो(seq, '/');
		क्रम (i = 0; i < tp.skip_ofst * 2; i += 2)
			seq_म_लिखो(seq, "%08x%08x", tp.mask[i], tp.mask[i + 1]);
		seq_माला_दो(seq, "@0\n");
	पूर्ण

	seq_माला_दो(seq, "filter pattern: ");
	क्रम (i = tp.skip_ofst * 2; i < TRACE_LEN / 4; i += 2)
		seq_म_लिखो(seq, "%08x%08x", tp.data[i], tp.data[i + 1]);
	seq_अ_दो(seq, '/');
	क्रम (i = tp.skip_ofst * 2; i < TRACE_LEN / 4; i += 2)
		seq_म_लिखो(seq, "%08x%08x", tp.mask[i], tp.mask[i + 1]);
	seq_म_लिखो(seq, "@%u\n", (tp.skip_ofst + tp.skip_len) * 8);
	वापस 0;
पूर्ण

अटल पूर्णांक mps_trc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, mps_trc_show, inode->i_निजी);
पूर्ण

अटल अचिन्हित पूर्णांक xdigit2पूर्णांक(अचिन्हित अक्षर c)
अणु
	वापस है_अंक(c) ? c - '0' : tolower(c) - 'a' + 10;
पूर्ण

#घोषणा TRC_PORT_NONE 0xff
#घोषणा TRC_RSS_ENABLE 0x33
#घोषणा TRC_RSS_DISABLE 0x13

/* Set an MPS trace filter.  Syntax is:
 *
 * disable
 *
 * to disable tracing, or
 *
 * पूर्णांकerface qid=<qid no> [snaplen=<val>] [minlen=<val>] [not] [<pattern>]...
 *
 * where पूर्णांकerface is one of rxN, txN, or loopbackN, N = 0..3, qid can be one
 * of the NIC's response qid obtained from sge_qinfo and pattern has the क्रमm
 *
 * <pattern data>[/<pattern mask>][@<anchor>]
 *
 * Up to 2 filter patterns can be specअगरied.  If 2 are supplied the first one
 * must be anchored at 0.  An omitted mask is taken as a mask of 1s, an omitted
 * anchor is taken as 0.
 */
अटल sमाप_प्रकार mps_trc_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक i, enable, ret;
	u32 *data, *mask;
	काष्ठा trace_params tp;
	स्थिर काष्ठा inode *ino;
	अचिन्हित पूर्णांक trcidx;
	अक्षर *s, *p, *word, *end;
	काष्ठा adapter *adap;
	u32 j;

	ino = file_inode(file);
	trcidx = (uपूर्णांकptr_t)ino->i_निजी & 3;
	adap = ino->i_निजी - trcidx;

	/* Don't accept input more than 1K, can't be anything valid except lots
	 * of whitespace.  Well, use less.
	 */
	अगर (count > 1024)
		वापस -EFBIG;
	p = s = kzalloc(count + 1, GFP_USER);
	अगर (!s)
		वापस -ENOMEM;
	अगर (copy_from_user(s, buf, count)) अणु
		count = -EFAULT;
		जाओ out;
	पूर्ण

	अगर (s[count - 1] == '\n')
		s[count - 1] = '\0';

	enable = म_भेद("disable", s) != 0;
	अगर (!enable)
		जाओ apply;

	/* enable or disable trace multi rss filter */
	अगर (adap->trace_rss)
		t4_ग_लिखो_reg(adap, MPS_TRC_CFG_A, TRC_RSS_ENABLE);
	अन्यथा
		t4_ग_लिखो_reg(adap, MPS_TRC_CFG_A, TRC_RSS_DISABLE);

	स_रखो(&tp, 0, माप(tp));
	tp.port = TRC_PORT_NONE;
	i = 0;	/* counts pattern nibbles */

	जबतक (p) अणु
		जबतक (है_खाली(*p))
			p++;
		word = strsep(&p, " ");
		अगर (!*word)
			अवरोध;

		अगर (!म_भेदन(word, "qid=", 4)) अणु
			end = (अक्षर *)word + 4;
			ret = kstrtouपूर्णांक(end, 10, &j);
			अगर (ret)
				जाओ out;
			अगर (!adap->trace_rss) अणु
				t4_ग_लिखो_reg(adap, MPS_T5_TRC_RSS_CONTROL_A, j);
				जारी;
			पूर्ण

			चयन (trcidx) अणु
			हाल 0:
				t4_ग_लिखो_reg(adap, MPS_TRC_RSS_CONTROL_A, j);
				अवरोध;
			हाल 1:
				t4_ग_लिखो_reg(adap,
					     MPS_TRC_FILTER1_RSS_CONTROL_A, j);
				अवरोध;
			हाल 2:
				t4_ग_लिखो_reg(adap,
					     MPS_TRC_FILTER2_RSS_CONTROL_A, j);
				अवरोध;
			हाल 3:
				t4_ग_लिखो_reg(adap,
					     MPS_TRC_FILTER3_RSS_CONTROL_A, j);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		अगर (!म_भेदन(word, "snaplen=", 8)) अणु
			end = (अक्षर *)word + 8;
			ret = kstrtouपूर्णांक(end, 10, &j);
			अगर (ret || j > 9600) अणु
inval:				count = -EINVAL;
				जाओ out;
			पूर्ण
			tp.snap_len = j;
			जारी;
		पूर्ण
		अगर (!म_भेदन(word, "minlen=", 7)) अणु
			end = (अक्षर *)word + 7;
			ret = kstrtouपूर्णांक(end, 10, &j);
			अगर (ret || j > TFMINPKTSIZE_M)
				जाओ inval;
			tp.min_len = j;
			जारी;
		पूर्ण
		अगर (!म_भेद(word, "not")) अणु
			tp.invert = !tp.invert;
			जारी;
		पूर्ण
		अगर (!म_भेदन(word, "loopback", 8) && tp.port == TRC_PORT_NONE) अणु
			अगर (word[8] < '0' || word[8] > '3' || word[9])
				जाओ inval;
			tp.port = word[8] - '0' + 8;
			जारी;
		पूर्ण
		अगर (!म_भेदन(word, "tx", 2) && tp.port == TRC_PORT_NONE) अणु
			अगर (word[2] < '0' || word[2] > '3' || word[3])
				जाओ inval;
			tp.port = word[2] - '0' + 4;
			अगर (adap->chan_map[tp.port & 3] >= MAX_NPORTS)
				जाओ inval;
			जारी;
		पूर्ण
		अगर (!म_भेदन(word, "rx", 2) && tp.port == TRC_PORT_NONE) अणु
			अगर (word[2] < '0' || word[2] > '3' || word[3])
				जाओ inval;
			tp.port = word[2] - '0';
			अगर (adap->chan_map[tp.port] >= MAX_NPORTS)
				जाओ inval;
			जारी;
		पूर्ण
		अगर (!है_षष्ठादशक(*word))
			जाओ inval;

		/* we have found a trace pattern */
		अगर (i) अणु                            /* split pattern */
			अगर (tp.skip_len)            /* too many splits */
				जाओ inval;
			tp.skip_ofst = i / 16;
		पूर्ण

		data = &tp.data[i / 8];
		mask = &tp.mask[i / 8];
		j = i;

		जबतक (है_षष्ठादशक(*word)) अणु
			अगर (i >= TRACE_LEN * 2) अणु
				count = -EFBIG;
				जाओ out;
			पूर्ण
			*data = (*data << 4) + xdigit2पूर्णांक(*word++);
			अगर (++i % 8 == 0)
				data++;
		पूर्ण
		अगर (*word == '/') अणु
			word++;
			जबतक (है_षष्ठादशक(*word)) अणु
				अगर (j >= i)         /* mask दीर्घer than data */
					जाओ inval;
				*mask = (*mask << 4) + xdigit2पूर्णांक(*word++);
				अगर (++j % 8 == 0)
					mask++;
			पूर्ण
			अगर (i != j)                 /* mask लघुer than data */
				जाओ inval;
		पूर्ण अन्यथा अणु                            /* no mask, use all 1s */
			क्रम ( ; i - j >= 8; j += 8)
				*mask++ = 0xffffffff;
			अगर (i % 8)
				*mask = (1 << (i % 8) * 4) - 1;
		पूर्ण
		अगर (*word == '@') अणु
			end = (अक्षर *)word + 1;
			ret = kstrtouपूर्णांक(end, 10, &j);
			अगर (*end && *end != '\n')
				जाओ inval;
			अगर (j & 7)          /* करोesn't start at multiple of 8 */
				जाओ inval;
			j /= 8;
			अगर (j < tp.skip_ofst)     /* overlaps earlier pattern */
				जाओ inval;
			अगर (j - tp.skip_ofst > 31)            /* skip too big */
				जाओ inval;
			tp.skip_len = j - tp.skip_ofst;
		पूर्ण
		अगर (i % 8) अणु
			*data <<= (8 - i % 8) * 4;
			*mask <<= (8 - i % 8) * 4;
			i = (i + 15) & ~15;         /* 8-byte align */
		पूर्ण
	पूर्ण

	अगर (tp.port == TRC_PORT_NONE)
		जाओ inval;

apply:
	i = t4_set_trace_filter(adap, &tp, trcidx, enable);
	अगर (i)
		count = i;
out:
	kमुक्त(s);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations mps_trc_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = mps_trc_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = single_release,
	.ग_लिखो   = mps_trc_ग_लिखो
पूर्ण;

अटल sमाप_प्रकार flash_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			  loff_t *ppos)
अणु
	loff_t pos = *ppos;
	loff_t avail = file_inode(file)->i_size;
	काष्ठा adapter *adap = file->निजी_data;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= avail)
		वापस 0;
	अगर (count > avail - pos)
		count = avail - pos;

	जबतक (count) अणु
		माप_प्रकार len;
		पूर्णांक ret, ofst;
		u8 data[256];

		ofst = pos & 3;
		len = min(count + ofst, माप(data));
		ret = t4_पढ़ो_flash(adap, pos - ofst, (len + 3) / 4,
				    (u32 *)data, 1);
		अगर (ret)
			वापस ret;

		len -= ofst;
		अगर (copy_to_user(buf, data + ofst, len))
			वापस -EFAULT;

		buf += len;
		pos += len;
		count -= len;
	पूर्ण
	count = pos - *ppos;
	*ppos = pos;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations flash_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = mem_खोलो,
	.पढ़ो    = flash_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

अटल अंतरभूत व्योम tcamxy2valmask(u64 x, u64 y, u8 *addr, u64 *mask)
अणु
	*mask = x | y;
	y = (__क्रमce u64)cpu_to_be64(y);
	स_नकल(addr, (अक्षर *)&y + 2, ETH_ALEN);
पूर्ण

अटल पूर्णांक mps_tcam_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adap = seq->निजी;
	अचिन्हित पूर्णांक chip_ver = CHELSIO_CHIP_VERSION(adap->params.chip);
	अगर (v == SEQ_START_TOKEN) अणु
		अगर (chip_ver > CHELSIO_T5) अणु
			seq_माला_दो(seq, "Idx  Ethernet address     Mask     "
				 "  VNI   Mask   IVLAN Vld "
				 "DIP_Hit   Lookup  Port "
				 "Vld Ports PF  VF                           "
				 "Replication                                "
				 "    P0 P1 P2 P3  ML\n");
		पूर्ण अन्यथा अणु
			अगर (adap->params.arch.mps_rplc_size > 128)
				seq_माला_दो(seq, "Idx  Ethernet address     Mask     "
					 "Vld Ports PF  VF                           "
					 "Replication                                "
					 "    P0 P1 P2 P3  ML\n");
			अन्यथा
				seq_माला_दो(seq, "Idx  Ethernet address     Mask     "
					 "Vld Ports PF  VF              Replication"
					 "	         P0 P1 P2 P3  ML\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		u64 mask;
		u8 addr[ETH_ALEN];
		bool replicate, dip_hit = false, vlan_vld = false;
		अचिन्हित पूर्णांक idx = (uपूर्णांकptr_t)v - 2;
		u64 tcamy, tcamx, val;
		u32 cls_lo, cls_hi, ctl, data2, vnix = 0, vniy = 0;
		u32 rplc[8] = अणु0पूर्ण;
		u8 lookup_type = 0, port_num = 0;
		u16 ivlan = 0;

		अगर (chip_ver > CHELSIO_T5) अणु
			/* CtlCmdType - 0: Read, 1: Write
			 * CtlTcamSel - 0: TCAM0, 1: TCAM1
			 * CtlXYBitSel- 0: Y bit, 1: X bit
			 */

			/* Read tcamy */
			ctl = CTLCMDTYPE_V(0) | CTLXYBITSEL_V(0);
			अगर (idx < 256)
				ctl |= CTLTCAMINDEX_V(idx) | CTLTCAMSEL_V(0);
			अन्यथा
				ctl |= CTLTCAMINDEX_V(idx - 256) |
				       CTLTCAMSEL_V(1);
			t4_ग_लिखो_reg(adap, MPS_CLS_TCAM_DATA2_CTL_A, ctl);
			val = t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA1_A);
			tcamy = DMACH_G(val) << 32;
			tcamy |= t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA0_A);
			data2 = t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA2_CTL_A);
			lookup_type = DATALKPTYPE_G(data2);
			/* 0 - Outer header, 1 - Inner header
			 * [71:48] bit locations are overloaded क्रम
			 * outer vs. inner lookup types.
			 */
			अगर (lookup_type && (lookup_type != DATALKPTYPE_M)) अणु
				/* Inner header VNI */
				vniy = (data2 & DATAVIDH2_F) |
				       (DATAVIDH1_G(data2) << 16) | VIDL_G(val);
				dip_hit = data2 & DATADIPHIT_F;
			पूर्ण अन्यथा अणु
				vlan_vld = data2 & DATAVIDH2_F;
				ivlan = VIDL_G(val);
			पूर्ण
			port_num = DATAPORTNUM_G(data2);

			/* Read tcamx. Change the control param */
			vnix = 0;
			ctl |= CTLXYBITSEL_V(1);
			t4_ग_लिखो_reg(adap, MPS_CLS_TCAM_DATA2_CTL_A, ctl);
			val = t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA1_A);
			tcamx = DMACH_G(val) << 32;
			tcamx |= t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA0_A);
			data2 = t4_पढ़ो_reg(adap, MPS_CLS_TCAM_DATA2_CTL_A);
			अगर (lookup_type && (lookup_type != DATALKPTYPE_M)) अणु
				/* Inner header VNI mask */
				vnix = (data2 & DATAVIDH2_F) |
				       (DATAVIDH1_G(data2) << 16) | VIDL_G(val);
			पूर्ण
		पूर्ण अन्यथा अणु
			tcamy = t4_पढ़ो_reg64(adap, MPS_CLS_TCAM_Y_L(idx));
			tcamx = t4_पढ़ो_reg64(adap, MPS_CLS_TCAM_X_L(idx));
		पूर्ण

		cls_lo = t4_पढ़ो_reg(adap, MPS_CLS_SRAM_L(idx));
		cls_hi = t4_पढ़ो_reg(adap, MPS_CLS_SRAM_H(idx));

		अगर (tcamx & tcamy) अणु
			seq_म_लिखो(seq, "%3u         -\n", idx);
			जाओ out;
		पूर्ण

		rplc[0] = rplc[1] = rplc[2] = rplc[3] = 0;
		अगर (chip_ver > CHELSIO_T5)
			replicate = (cls_lo & T6_REPLICATE_F);
		अन्यथा
			replicate = (cls_lo & REPLICATE_F);

		अगर (replicate) अणु
			काष्ठा fw_ldst_cmd ldst_cmd;
			पूर्णांक ret;
			काष्ठा fw_ldst_mps_rplc mps_rplc;
			u32 ldst_addrspc;

			स_रखो(&ldst_cmd, 0, माप(ldst_cmd));
			ldst_addrspc =
				FW_LDST_CMD_ADDRSPACE_V(FW_LDST_ADDRSPC_MPS);
			ldst_cmd.op_to_addrspace =
				htonl(FW_CMD_OP_V(FW_LDST_CMD) |
				      FW_CMD_REQUEST_F |
				      FW_CMD_READ_F |
				      ldst_addrspc);
			ldst_cmd.cycles_to_len16 = htonl(FW_LEN16(ldst_cmd));
			ldst_cmd.u.mps.rplc.fid_idx =
				htons(FW_LDST_CMD_FID_V(FW_LDST_MPS_RPLC) |
				      FW_LDST_CMD_IDX_V(idx));
			ret = t4_wr_mbox(adap, adap->mbox, &ldst_cmd,
					 माप(ldst_cmd), &ldst_cmd);
			अगर (ret)
				dev_warn(adap->pdev_dev, "Can't read MPS "
					 "replication map for idx %d: %d\n",
					 idx, -ret);
			अन्यथा अणु
				mps_rplc = ldst_cmd.u.mps.rplc;
				rplc[0] = ntohl(mps_rplc.rplc31_0);
				rplc[1] = ntohl(mps_rplc.rplc63_32);
				rplc[2] = ntohl(mps_rplc.rplc95_64);
				rplc[3] = ntohl(mps_rplc.rplc127_96);
				अगर (adap->params.arch.mps_rplc_size > 128) अणु
					rplc[4] = ntohl(mps_rplc.rplc159_128);
					rplc[5] = ntohl(mps_rplc.rplc191_160);
					rplc[6] = ntohl(mps_rplc.rplc223_192);
					rplc[7] = ntohl(mps_rplc.rplc255_224);
				पूर्ण
			पूर्ण
		पूर्ण

		tcamxy2valmask(tcamx, tcamy, addr, &mask);
		अगर (chip_ver > CHELSIO_T5) अणु
			/* Inner header lookup */
			अगर (lookup_type && (lookup_type != DATALKPTYPE_M)) अणु
				seq_म_लिखो(seq,
					   "%3u %pM %012llx %06x %06x    -    -   %3c      'I'  %4x   %3c   %#x%4u%4d",
					   idx, addr,
					   (अचिन्हित दीर्घ दीर्घ)mask,
					   vniy, (vnix | vniy),
					   dip_hit ? 'Y' : 'N',
					   port_num,
					   (cls_lo & T6_SRAM_VLD_F) ? 'Y' : 'N',
					   PORTMAP_G(cls_hi),
					   T6_PF_G(cls_lo),
					   (cls_lo & T6_VF_VALID_F) ?
					   T6_VF_G(cls_lo) : -1);
			पूर्ण अन्यथा अणु
				seq_म_लिखो(seq,
					   "%3u %pM %012llx    -       -   ",
					   idx, addr,
					   (अचिन्हित दीर्घ दीर्घ)mask);

				अगर (vlan_vld)
					seq_म_लिखो(seq, "%4u   Y     ", ivlan);
				अन्यथा
					seq_माला_दो(seq, "  -    N     ");

				seq_म_लिखो(seq,
					   "-      %3c  %4x   %3c   %#x%4u%4d",
					   lookup_type ? 'I' : 'O', port_num,
					   (cls_lo & T6_SRAM_VLD_F) ? 'Y' : 'N',
					   PORTMAP_G(cls_hi),
					   T6_PF_G(cls_lo),
					   (cls_lo & T6_VF_VALID_F) ?
					   T6_VF_G(cls_lo) : -1);
			पूर्ण
		पूर्ण अन्यथा
			seq_म_लिखो(seq, "%3u %pM %012llx%3c   %#x%4u%4d",
				   idx, addr, (अचिन्हित दीर्घ दीर्घ)mask,
				   (cls_lo & SRAM_VLD_F) ? 'Y' : 'N',
				   PORTMAP_G(cls_hi),
				   PF_G(cls_lo),
				   (cls_lo & VF_VALID_F) ? VF_G(cls_lo) : -1);

		अगर (replicate) अणु
			अगर (adap->params.arch.mps_rplc_size > 128)
				seq_म_लिखो(seq, " %08x %08x %08x %08x "
					   "%08x %08x %08x %08x",
					   rplc[7], rplc[6], rplc[5], rplc[4],
					   rplc[3], rplc[2], rplc[1], rplc[0]);
			अन्यथा
				seq_म_लिखो(seq, " %08x %08x %08x %08x",
					   rplc[3], rplc[2], rplc[1], rplc[0]);
		पूर्ण अन्यथा अणु
			अगर (adap->params.arch.mps_rplc_size > 128)
				seq_म_लिखो(seq, "%72c", ' ');
			अन्यथा
				seq_म_लिखो(seq, "%36c", ' ');
		पूर्ण

		अगर (chip_ver > CHELSIO_T5)
			seq_म_लिखो(seq, "%4u%3u%3u%3u %#x\n",
				   T6_SRAM_PRIO0_G(cls_lo),
				   T6_SRAM_PRIO1_G(cls_lo),
				   T6_SRAM_PRIO2_G(cls_lo),
				   T6_SRAM_PRIO3_G(cls_lo),
				   (cls_lo >> T6_MULTILISTEN0_S) & 0xf);
		अन्यथा
			seq_म_लिखो(seq, "%4u%3u%3u%3u %#x\n",
				   SRAM_PRIO0_G(cls_lo), SRAM_PRIO1_G(cls_lo),
				   SRAM_PRIO2_G(cls_lo), SRAM_PRIO3_G(cls_lo),
				   (cls_lo >> MULTILISTEN0_S) & 0xf);
	पूर्ण
out:	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *mps_tcam_get_idx(काष्ठा seq_file *seq, loff_t pos)
अणु
	काष्ठा adapter *adap = seq->निजी;
	पूर्णांक max_mac_addr = is_t4(adap->params.chip) ?
				NUM_MPS_CLS_SRAM_L_INSTANCES :
				NUM_MPS_T5_CLS_SRAM_L_INSTANCES;
	वापस ((pos <= max_mac_addr) ? (व्योम *)(uपूर्णांकptr_t)(pos + 1) : शून्य);
पूर्ण

अटल व्योम *mps_tcam_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	वापस *pos ? mps_tcam_get_idx(seq, *pos) : SEQ_START_TOKEN;
पूर्ण

अटल व्योम *mps_tcam_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	++*pos;
	वापस mps_tcam_get_idx(seq, *pos);
पूर्ण

अटल व्योम mps_tcam_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल स्थिर काष्ठा seq_operations mps_tcam_seq_ops = अणु
	.start = mps_tcam_start,
	.next  = mps_tcam_next,
	.stop  = mps_tcam_stop,
	.show  = mps_tcam_show
पूर्ण;

अटल पूर्णांक mps_tcam_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक res = seq_खोलो(file, &mps_tcam_seq_ops);

	अगर (!res) अणु
		काष्ठा seq_file *seq = file->निजी_data;

		seq->निजी = inode->i_निजी;
	पूर्ण
	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations mps_tcam_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = mps_tcam_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;

/* Display various sensor inक्रमmation.
 */
अटल पूर्णांक sensors_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adap = seq->निजी;
	u32 param[7], val[7];
	पूर्णांक ret;

	/* Note that अगर the sensors haven't been initialized and turned on
	 * we'll get values of 0, so treat those as "<unknown>" ...
	 */
	param[0] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		    FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_TMP));
	param[1] = (FW_PARAMS_MNEM_V(FW_PARAMS_MNEM_DEV) |
		    FW_PARAMS_PARAM_X_V(FW_PARAMS_PARAM_DEV_DIAG) |
		    FW_PARAMS_PARAM_Y_V(FW_PARAM_DEV_DIAG_VDD));
	ret = t4_query_params(adap, adap->mbox, adap->pf, 0, 2,
			      param, val);

	अगर (ret < 0 || val[0] == 0)
		seq_माला_दो(seq, "Temperature: <unknown>\n");
	अन्यथा
		seq_म_लिखो(seq, "Temperature: %dC\n", val[0]);

	अगर (ret < 0 || val[1] == 0)
		seq_माला_दो(seq, "Core VDD:    <unknown>\n");
	अन्यथा
		seq_म_लिखो(seq, "Core VDD:    %dmV\n", val[1]);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(sensors);

#अगर IS_ENABLED(CONFIG_IPV6)
DEFINE_SHOW_ATTRIBUTE(clip_tbl);
#पूर्ण_अगर

/*RSS Table.
 */

अटल पूर्णांक rss_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	u16 *entry = v;

	seq_म_लिखो(seq, "%4d:  %4u  %4u  %4u  %4u  %4u  %4u  %4u  %4u\n",
		   idx * 8, entry[0], entry[1], entry[2], entry[3], entry[4],
		   entry[5], entry[6], entry[7]);
	वापस 0;
पूर्ण

अटल पूर्णांक rss_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adapter *adap = inode->i_निजी;
	पूर्णांक ret, nentries;
	काष्ठा seq_tab *p;

	nentries = t4_chip_rss_size(adap);
	p = seq_खोलो_tab(file, nentries / 8, 8 * माप(u16), 0, rss_show);
	अगर (!p)
		वापस -ENOMEM;

	ret = t4_पढ़ो_rss(adap, (u16 *)p->data);
	अगर (ret)
		seq_release_निजी(inode, file);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations rss_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = rss_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

/* RSS Configuration.
 */

/* Small utility function to वापस the strings "yes" or "no" अगर the supplied
 * argument is non-zero.
 */
अटल स्थिर अक्षर *yesno(पूर्णांक x)
अणु
	अटल स्थिर अक्षर *yes = "yes";
	अटल स्थिर अक्षर *no = "no";

	वापस x ? yes : no;
पूर्ण

अटल पूर्णांक rss_config_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	अटल स्थिर अक्षर * स्थिर keymode[] = अणु
		"global",
		"global and per-VF scramble",
		"per-PF and per-VF scramble",
		"per-VF and per-VF scramble",
	पूर्ण;
	u32 rssconf;

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG: %#x\n", rssconf);
	seq_म_लिखो(seq, "  Tnl4TupEnIpv6: %3s\n", yesno(rssconf &
							TNL4TUPENIPV6_F));
	seq_म_लिखो(seq, "  Tnl2TupEnIpv6: %3s\n", yesno(rssconf &
							TNL2TUPENIPV6_F));
	seq_म_लिखो(seq, "  Tnl4TupEnIpv4: %3s\n", yesno(rssconf &
							TNL4TUPENIPV4_F));
	seq_म_लिखो(seq, "  Tnl2TupEnIpv4: %3s\n", yesno(rssconf &
							TNL2TUPENIPV4_F));
	seq_म_लिखो(seq, "  TnlTcpSel:     %3s\n", yesno(rssconf & TNLTCPSEL_F));
	seq_म_लिखो(seq, "  TnlIp6Sel:     %3s\n", yesno(rssconf & TNLIP6SEL_F));
	seq_म_लिखो(seq, "  TnlVrtSel:     %3s\n", yesno(rssconf & TNLVRTSEL_F));
	seq_म_लिखो(seq, "  TnlMapEn:      %3s\n", yesno(rssconf & TNLMAPEN_F));
	seq_म_लिखो(seq, "  OfdHashSave:   %3s\n", yesno(rssconf &
							OFDHASHSAVE_F));
	seq_म_लिखो(seq, "  OfdVrtSel:     %3s\n", yesno(rssconf & OFDVRTSEL_F));
	seq_म_लिखो(seq, "  OfdMapEn:      %3s\n", yesno(rssconf & OFDMAPEN_F));
	seq_म_लिखो(seq, "  OfdLkpEn:      %3s\n", yesno(rssconf & OFDLKPEN_F));
	seq_म_लिखो(seq, "  Syn4TupEnIpv6: %3s\n", yesno(rssconf &
							SYN4TUPENIPV6_F));
	seq_म_लिखो(seq, "  Syn2TupEnIpv6: %3s\n", yesno(rssconf &
							SYN2TUPENIPV6_F));
	seq_म_लिखो(seq, "  Syn4TupEnIpv4: %3s\n", yesno(rssconf &
							SYN4TUPENIPV4_F));
	seq_म_लिखो(seq, "  Syn2TupEnIpv4: %3s\n", yesno(rssconf &
							SYN2TUPENIPV4_F));
	seq_म_लिखो(seq, "  Syn4TupEnIpv6: %3s\n", yesno(rssconf &
							SYN4TUPENIPV6_F));
	seq_म_लिखो(seq, "  SynIp6Sel:     %3s\n", yesno(rssconf & SYNIP6SEL_F));
	seq_म_लिखो(seq, "  SynVrt6Sel:    %3s\n", yesno(rssconf & SYNVRTSEL_F));
	seq_म_लिखो(seq, "  SynMapEn:      %3s\n", yesno(rssconf & SYNMAPEN_F));
	seq_म_लिखो(seq, "  SynLkpEn:      %3s\n", yesno(rssconf & SYNLKPEN_F));
	seq_म_लिखो(seq, "  ChnEn:         %3s\n", yesno(rssconf &
							CHANNELENABLE_F));
	seq_म_लिखो(seq, "  PrtEn:         %3s\n", yesno(rssconf &
							PORTENABLE_F));
	seq_म_लिखो(seq, "  TnlAllLkp:     %3s\n", yesno(rssconf &
							TNLALLLOOKUP_F));
	seq_म_लिखो(seq, "  VrtEn:         %3s\n", yesno(rssconf &
							VIRTENABLE_F));
	seq_म_लिखो(seq, "  CngEn:         %3s\n", yesno(rssconf &
							CONGESTIONENABLE_F));
	seq_म_लिखो(seq, "  HashToeplitz:  %3s\n", yesno(rssconf &
							HASHTOEPLITZ_F));
	seq_म_लिखो(seq, "  Udp4En:        %3s\n", yesno(rssconf & UDPENABLE_F));
	seq_म_लिखो(seq, "  Disable:       %3s\n", yesno(rssconf & DISABLE_F));

	seq_माला_दो(seq, "\n");

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_TNL_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG_TNL: %#x\n", rssconf);
	seq_म_लिखो(seq, "  MaskSize:      %3d\n", MASKSIZE_G(rssconf));
	seq_म_लिखो(seq, "  MaskFilter:    %3d\n", MASKFILTER_G(rssconf));
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) > CHELSIO_T5) अणु
		seq_म_लिखो(seq, "  HashAll:     %3s\n",
			   yesno(rssconf & HASHALL_F));
		seq_म_लिखो(seq, "  HashEth:     %3s\n",
			   yesno(rssconf & HASHETH_F));
	पूर्ण
	seq_म_लिखो(seq, "  UseWireCh:     %3s\n", yesno(rssconf & USEWIRECH_F));

	seq_माला_दो(seq, "\n");

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_OFD_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG_OFD: %#x\n", rssconf);
	seq_म_लिखो(seq, "  MaskSize:      %3d\n", MASKSIZE_G(rssconf));
	seq_म_लिखो(seq, "  RRCplMapEn:    %3s\n", yesno(rssconf &
							RRCPLMAPEN_F));
	seq_म_लिखो(seq, "  RRCplQueWidth: %3d\n", RRCPLQUEWIDTH_G(rssconf));

	seq_माला_दो(seq, "\n");

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_SYN_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG_SYN: %#x\n", rssconf);
	seq_म_लिखो(seq, "  MaskSize:      %3d\n", MASKSIZE_G(rssconf));
	seq_म_लिखो(seq, "  UseWireCh:     %3s\n", yesno(rssconf & USEWIRECH_F));

	seq_माला_दो(seq, "\n");

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_VRT_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG_VRT: %#x\n", rssconf);
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) > CHELSIO_T5) अणु
		seq_म_लिखो(seq, "  KeyWrAddrX:     %3d\n",
			   KEYWRADDRX_G(rssconf));
		seq_म_लिखो(seq, "  KeyExtend:      %3s\n",
			   yesno(rssconf & KEYEXTEND_F));
	पूर्ण
	seq_म_लिखो(seq, "  VfRdRg:        %3s\n", yesno(rssconf & VFRDRG_F));
	seq_म_लिखो(seq, "  VfRdEn:        %3s\n", yesno(rssconf & VFRDEN_F));
	seq_म_लिखो(seq, "  VfPerrEn:      %3s\n", yesno(rssconf & VFPERREN_F));
	seq_म_लिखो(seq, "  KeyPerrEn:     %3s\n", yesno(rssconf & KEYPERREN_F));
	seq_म_लिखो(seq, "  DisVfVlan:     %3s\n", yesno(rssconf &
							DISABLEVLAN_F));
	seq_म_लिखो(seq, "  EnUpSwt:       %3s\n", yesno(rssconf & ENABLEUP0_F));
	seq_म_लिखो(seq, "  HashDelay:     %3d\n", HASHDELAY_G(rssconf));
	अगर (CHELSIO_CHIP_VERSION(adapter->params.chip) <= CHELSIO_T5)
		seq_म_लिखो(seq, "  VfWrAddr:      %3d\n", VFWRADDR_G(rssconf));
	अन्यथा
		seq_म_लिखो(seq, "  VfWrAddr:      %3d\n",
			   T6_VFWRADDR_G(rssconf));
	seq_म_लिखो(seq, "  KeyMode:       %s\n", keymode[KEYMODE_G(rssconf)]);
	seq_म_लिखो(seq, "  VfWrEn:        %3s\n", yesno(rssconf & VFWREN_F));
	seq_म_लिखो(seq, "  KeyWrEn:       %3s\n", yesno(rssconf & KEYWREN_F));
	seq_म_लिखो(seq, "  KeyWrAddr:     %3d\n", KEYWRADDR_G(rssconf));

	seq_माला_दो(seq, "\n");

	rssconf = t4_पढ़ो_reg(adapter, TP_RSS_CONFIG_CNG_A);
	seq_म_लिखो(seq, "TP_RSS_CONFIG_CNG: %#x\n", rssconf);
	seq_म_लिखो(seq, "  ChnCount3:     %3s\n", yesno(rssconf & CHNCOUNT3_F));
	seq_म_लिखो(seq, "  ChnCount2:     %3s\n", yesno(rssconf & CHNCOUNT2_F));
	seq_म_लिखो(seq, "  ChnCount1:     %3s\n", yesno(rssconf & CHNCOUNT1_F));
	seq_म_लिखो(seq, "  ChnCount0:     %3s\n", yesno(rssconf & CHNCOUNT0_F));
	seq_म_लिखो(seq, "  ChnUndFlow3:   %3s\n", yesno(rssconf &
							CHNUNDFLOW3_F));
	seq_म_लिखो(seq, "  ChnUndFlow2:   %3s\n", yesno(rssconf &
							CHNUNDFLOW2_F));
	seq_म_लिखो(seq, "  ChnUndFlow1:   %3s\n", yesno(rssconf &
							CHNUNDFLOW1_F));
	seq_म_लिखो(seq, "  ChnUndFlow0:   %3s\n", yesno(rssconf &
							CHNUNDFLOW0_F));
	seq_म_लिखो(seq, "  RstChn3:       %3s\n", yesno(rssconf & RSTCHN3_F));
	seq_म_लिखो(seq, "  RstChn2:       %3s\n", yesno(rssconf & RSTCHN2_F));
	seq_म_लिखो(seq, "  RstChn1:       %3s\n", yesno(rssconf & RSTCHN1_F));
	seq_म_लिखो(seq, "  RstChn0:       %3s\n", yesno(rssconf & RSTCHN0_F));
	seq_म_लिखो(seq, "  UpdVld:        %3s\n", yesno(rssconf & UPDVLD_F));
	seq_म_लिखो(seq, "  Xoff:          %3s\n", yesno(rssconf & XOFF_F));
	seq_म_लिखो(seq, "  UpdChn3:       %3s\n", yesno(rssconf & UPDCHN3_F));
	seq_म_लिखो(seq, "  UpdChn2:       %3s\n", yesno(rssconf & UPDCHN2_F));
	seq_म_लिखो(seq, "  UpdChn1:       %3s\n", yesno(rssconf & UPDCHN1_F));
	seq_म_लिखो(seq, "  UpdChn0:       %3s\n", yesno(rssconf & UPDCHN0_F));
	seq_म_लिखो(seq, "  Queue:         %3d\n", QUEUE_G(rssconf));

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(rss_config);

/* RSS Secret Key.
 */

अटल पूर्णांक rss_key_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	u32 key[10];

	t4_पढ़ो_rss_key(seq->निजी, key, true);
	seq_म_लिखो(seq, "%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x\n",
		   key[9], key[8], key[7], key[6], key[5], key[4], key[3],
		   key[2], key[1], key[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक rss_key_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, rss_key_show, inode->i_निजी);
पूर्ण

अटल sमाप_प्रकार rss_key_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			     माप_प्रकार count, loff_t *pos)
अणु
	पूर्णांक i, j;
	u32 key[10];
	अक्षर s[100], *p;
	काष्ठा adapter *adap = file_inode(file)->i_निजी;

	अगर (count > माप(s) - 1)
		वापस -EINVAL;
	अगर (copy_from_user(s, buf, count))
		वापस -EFAULT;
	क्रम (i = count; i > 0 && है_खाली(s[i - 1]); i--)
		;
	s[i] = '\0';

	क्रम (p = s, i = 9; i >= 0; i--) अणु
		key[i] = 0;
		क्रम (j = 0; j < 8; j++, p++) अणु
			अगर (!है_षष्ठादशक(*p))
				वापस -EINVAL;
			key[i] = (key[i] << 4) | hex2val(*p);
		पूर्ण
	पूर्ण

	t4_ग_लिखो_rss_key(adap, key, -1, true);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations rss_key_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = rss_key_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = single_release,
	.ग_लिखो   = rss_key_ग_लिखो
पूर्ण;

/* PF RSS Configuration.
 */

काष्ठा rss_pf_conf अणु
	u32 rss_pf_map;
	u32 rss_pf_mask;
	u32 rss_pf_config;
पूर्ण;

अटल पूर्णांक rss_pf_config_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	काष्ठा rss_pf_conf *pfconf;

	अगर (v == SEQ_START_TOKEN) अणु
		/* use the 0th entry to dump the PF Map Index Size */
		pfconf = seq->निजी + दुरत्व(काष्ठा seq_tab, data);
		seq_म_लिखो(seq, "PF Map Index Size = %d\n\n",
			   LKPIDXSIZE_G(pfconf->rss_pf_map));

		seq_माला_दो(seq, "     RSS              PF   VF    Hash Tuple Enable         Default\n");
		seq_माला_दो(seq, "     Enable       IPF Mask Mask  IPv6      IPv4      UDP   Queue\n");
		seq_माला_दो(seq, " PF  Map Chn Prt  Map Size Size  Four Two  Four Two  Four  Ch1  Ch0\n");
	पूर्ण अन्यथा अणु
		#घोषणा G_PFnLKPIDX(map, n) \
			(((map) >> PF1LKPIDX_S*(n)) & PF0LKPIDX_M)
		#घोषणा G_PFnMSKSIZE(mask, n) \
			(((mask) >> PF1MSKSIZE_S*(n)) & PF1MSKSIZE_M)

		pfconf = v;
		seq_म_लिखो(seq, "%3d  %3s %3s %3s  %3d  %3d  %3d   %3s %3s   %3s %3s   %3s  %3d  %3d\n",
			   idx,
			   yesno(pfconf->rss_pf_config & MAPENABLE_F),
			   yesno(pfconf->rss_pf_config & CHNENABLE_F),
			   yesno(pfconf->rss_pf_config & PRTENABLE_F),
			   G_PFnLKPIDX(pfconf->rss_pf_map, idx),
			   G_PFnMSKSIZE(pfconf->rss_pf_mask, idx),
			   IVFWIDTH_G(pfconf->rss_pf_config),
			   yesno(pfconf->rss_pf_config & IP6FOURTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP6TWOTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP4FOURTUPEN_F),
			   yesno(pfconf->rss_pf_config & IP4TWOTUPEN_F),
			   yesno(pfconf->rss_pf_config & UDPFOURTUPEN_F),
			   CH1DEFAULTQUEUE_G(pfconf->rss_pf_config),
			   CH0DEFAULTQUEUE_G(pfconf->rss_pf_config));

		#अघोषित G_PFnLKPIDX
		#अघोषित G_PFnMSKSIZE
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rss_pf_config_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adapter *adapter = inode->i_निजी;
	काष्ठा seq_tab *p;
	u32 rss_pf_map, rss_pf_mask;
	काष्ठा rss_pf_conf *pfconf;
	पूर्णांक pf;

	p = seq_खोलो_tab(file, 8, माप(*pfconf), 1, rss_pf_config_show);
	अगर (!p)
		वापस -ENOMEM;

	pfconf = (काष्ठा rss_pf_conf *)p->data;
	rss_pf_map = t4_पढ़ो_rss_pf_map(adapter, true);
	rss_pf_mask = t4_पढ़ो_rss_pf_mask(adapter, true);
	क्रम (pf = 0; pf < 8; pf++) अणु
		pfconf[pf].rss_pf_map = rss_pf_map;
		pfconf[pf].rss_pf_mask = rss_pf_mask;
		t4_पढ़ो_rss_pf_config(adapter, pf, &pfconf[pf].rss_pf_config,
				      true);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations rss_pf_config_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = rss_pf_config_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

/* VF RSS Configuration.
 */

काष्ठा rss_vf_conf अणु
	u32 rss_vf_vfl;
	u32 rss_vf_vfh;
पूर्ण;

अटल पूर्णांक rss_vf_config_show(काष्ठा seq_file *seq, व्योम *v, पूर्णांक idx)
अणु
	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "     RSS                     Hash Tuple Enable\n");
		seq_माला_दो(seq, "     Enable   IVF  Dis  Enb  IPv6      IPv4      UDP    Def  Secret Key\n");
		seq_माला_दो(seq, " VF  Chn Prt  Map  VLAN  uP  Four Two  Four Two  Four   Que  Idx       Hash\n");
	पूर्ण अन्यथा अणु
		काष्ठा rss_vf_conf *vfconf = v;

		seq_म_लिखो(seq, "%3d  %3s %3s  %3d   %3s %3s   %3s %3s   %3s  %3s   %3s  %4d  %3d %#10x\n",
			   idx,
			   yesno(vfconf->rss_vf_vfh & VFCHNEN_F),
			   yesno(vfconf->rss_vf_vfh & VFPRTEN_F),
			   VFLKPIDX_G(vfconf->rss_vf_vfh),
			   yesno(vfconf->rss_vf_vfh & VFVLNEX_F),
			   yesno(vfconf->rss_vf_vfh & VFUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4FOURTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP6TWOTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4FOURTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & VFIP4TWOTUPEN_F),
			   yesno(vfconf->rss_vf_vfh & ENABLEUDPHASH_F),
			   DEFAULTQUEUE_G(vfconf->rss_vf_vfh),
			   KEYINDEX_G(vfconf->rss_vf_vfh),
			   vfconf->rss_vf_vfl);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rss_vf_config_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा adapter *adapter = inode->i_निजी;
	काष्ठा seq_tab *p;
	काष्ठा rss_vf_conf *vfconf;
	पूर्णांक vf, vfcount = adapter->params.arch.vfcount;

	p = seq_खोलो_tab(file, vfcount, माप(*vfconf), 1, rss_vf_config_show);
	अगर (!p)
		वापस -ENOMEM;

	vfconf = (काष्ठा rss_vf_conf *)p->data;
	क्रम (vf = 0; vf < vfcount; vf++) अणु
		t4_पढ़ो_rss_vf_config(adapter, vf, &vfconf[vf].rss_vf_vfl,
				      &vfconf[vf].rss_vf_vfh, true);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations rss_vf_config_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = rss_vf_config_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release_निजी
पूर्ण;

#अगर_घोषित CONFIG_CHELSIO_T4_DCB

/* Data Center Briging inक्रमmation क्रम each port.
 */
अटल पूर्णांक dcb_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adap = seq->निजी;

	अगर (v == SEQ_START_TOKEN) अणु
		seq_माला_दो(seq, "Data Center Bridging Information\n");
	पूर्ण अन्यथा अणु
		पूर्णांक port = (uपूर्णांकptr_t)v - 2;
		काष्ठा net_device *dev = adap->port[port];
		काष्ठा port_info *pi = netdev2pinfo(dev);
		काष्ठा port_dcb_info *dcb = &pi->dcb;

		seq_माला_दो(seq, "\n");
		seq_म_लिखो(seq, "Port: %d (DCB negotiated: %s)\n",
			   port,
			   cxgb4_dcb_enabled(dev) ? "yes" : "no");

		अगर (cxgb4_dcb_enabled(dev))
			seq_म_लिखो(seq, "[ DCBx Version %s ]\n",
				   dcb_ver_array[dcb->dcb_version]);

		अगर (dcb->msgs) अणु
			पूर्णांक i;

			seq_माला_दो(seq, "\n  Index\t\t\t  :\t");
			क्रम (i = 0; i < 8; i++)
				seq_म_लिखो(seq, " %3d", i);
			seq_माला_दो(seq, "\n\n");
		पूर्ण

		अगर (dcb->msgs & CXGB4_DCB_FW_PGID) अणु
			पूर्णांक prio, pgid;

			seq_माला_दो(seq, "  Priority Group IDs\t  :\t");
			क्रम (prio = 0; prio < 8; prio++) अणु
				pgid = (dcb->pgid >> 4 * (7 - prio)) & 0xf;
				seq_म_लिखो(seq, " %3d", pgid);
			पूर्ण
			seq_माला_दो(seq, "\n");
		पूर्ण

		अगर (dcb->msgs & CXGB4_DCB_FW_PGRATE) अणु
			पूर्णांक pg;

			seq_माला_दो(seq, "  Priority Group BW(%)\t  :\t");
			क्रम (pg = 0; pg < 8; pg++)
				seq_म_लिखो(seq, " %3d", dcb->pgrate[pg]);
			seq_माला_दो(seq, "\n");

			अगर (dcb->dcb_version == FW_PORT_DCB_VER_IEEE) अणु
				seq_माला_दो(seq, "  TSA Algorithm\t\t  :\t");
				क्रम (pg = 0; pg < 8; pg++)
					seq_म_लिखो(seq, " %3d", dcb->tsa[pg]);
				seq_माला_दो(seq, "\n");
			पूर्ण

			seq_म_लिखो(seq, "  Max PG Traffic Classes  [%3d  ]\n",
				   dcb->pg_num_tcs_supported);

			seq_माला_दो(seq, "\n");
		पूर्ण

		अगर (dcb->msgs & CXGB4_DCB_FW_PRIORATE) अणु
			पूर्णांक prio;

			seq_माला_दो(seq, "  Priority Rate\t:\t");
			क्रम (prio = 0; prio < 8; prio++)
				seq_म_लिखो(seq, " %3d", dcb->priorate[prio]);
			seq_माला_दो(seq, "\n");
		पूर्ण

		अगर (dcb->msgs & CXGB4_DCB_FW_PFC) अणु
			पूर्णांक prio;

			seq_माला_दो(seq, "  Priority Flow Control   :\t");
			क्रम (prio = 0; prio < 8; prio++) अणु
				पूर्णांक pfcen = (dcb->pfcen >> 1 * (7 - prio))
					    & 0x1;
				seq_म_लिखो(seq, " %3d", pfcen);
			पूर्ण
			seq_माला_दो(seq, "\n");

			seq_म_लिखो(seq, "  Max PFC Traffic Classes [%3d  ]\n",
				   dcb->pfc_num_tcs_supported);

			seq_माला_दो(seq, "\n");
		पूर्ण

		अगर (dcb->msgs & CXGB4_DCB_FW_APP_ID) अणु
			पूर्णांक app, napps;

			seq_माला_दो(seq, "  Application Information:\n");
			seq_माला_दो(seq, "  App    Priority    Selection         Protocol\n");
			seq_माला_दो(seq, "  Index  Map         Field             ID\n");
			क्रम (app = 0, napps = 0;
			     app < CXGB4_MAX_DCBX_APP_SUPPORTED; app++) अणु
				काष्ठा app_priority *ap;
				अटल स्थिर अक्षर * स्थिर sel_names[] = अणु
					"Ethertype",
					"Socket TCP",
					"Socket UDP",
					"Socket All",
				पूर्ण;
				स्थिर अक्षर *sel_name;

				ap = &dcb->app_priority[app];
				/* skip empty slots */
				अगर (ap->protocolid == 0)
					जारी;
				napps++;

				अगर (ap->sel_field < ARRAY_SIZE(sel_names))
					sel_name = sel_names[ap->sel_field];
				अन्यथा
					sel_name = "UNKNOWN";

				seq_म_लिखो(seq, "  %3d    %#04x        %-10s (%d)    %#06x (%d)\n",
					   app,
					   ap->user_prio_map,
					   sel_name, ap->sel_field,
					   ap->protocolid, ap->protocolid);
			पूर्ण
			अगर (napps == 0)
				seq_माला_दो(seq, "    --- None ---\n");
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *dcb_info_get_idx(काष्ठा adapter *adap, loff_t pos)
अणु
	वापस (pos <= adap->params.nports
		? (व्योम *)((uपूर्णांकptr_t)pos + 1)
		: शून्य);
पूर्ण

अटल व्योम *dcb_info_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	काष्ठा adapter *adap = seq->निजी;

	वापस (*pos
		? dcb_info_get_idx(adap, *pos)
		: SEQ_START_TOKEN);
पूर्ण

अटल व्योम dcb_info_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *dcb_info_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	काष्ठा adapter *adap = seq->निजी;

	(*pos)++;
	वापस dcb_info_get_idx(adap, *pos);
पूर्ण

अटल स्थिर काष्ठा seq_operations dcb_info_seq_ops = अणु
	.start = dcb_info_start,
	.next  = dcb_info_next,
	.stop  = dcb_info_stop,
	.show  = dcb_info_show
पूर्ण;

अटल पूर्णांक dcb_info_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक res = seq_खोलो(file, &dcb_info_seq_ops);

	अगर (!res) अणु
		काष्ठा seq_file *seq = file->निजी_data;

		seq->निजी = inode->i_निजी;
	पूर्ण
	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations dcb_info_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = dcb_info_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;
#पूर्ण_अगर /* CONFIG_CHELSIO_T4_DCB */

अटल पूर्णांक resources_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adapter = seq->निजी;
	काष्ठा pf_resources *pfres = &adapter->params.pfres;

	#घोषणा S(desc, fmt, var) \
		seq_म_लिखो(seq, "%-60s " fmt "\n", \
			   desc " (" #var "):", pfres->var)

	S("Virtual Interfaces", "%d", nvi);
	S("Egress Queues", "%d", neq);
	S("Ethernet Control", "%d", nethctrl);
	S("Ingress Queues/w Free Lists/Interrupts", "%d", niqflपूर्णांक);
	S("Ingress Queues", "%d", niq);
	S("Traffic Class", "%d", tc);
	S("Port Access Rights Mask", "%#x", pmask);
	S("MAC Address Filters", "%d", nexactf);
	S("Firmware Command Read Capabilities", "%#x", r_caps);
	S("Firmware Command Write/Execute Capabilities", "%#x", wx_caps);

	#अघोषित S

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(resources);

/**
 * ethqset2pinfo - वापस port_info of an Ethernet Queue Set
 * @adap: the adapter
 * @qset: Ethernet Queue Set
 */
अटल अंतरभूत काष्ठा port_info *ethqset2pinfo(काष्ठा adapter *adap, पूर्णांक qset)
अणु
	पूर्णांक pidx;

	क्रम_each_port(adap, pidx) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, pidx);

		अगर (qset >= pi->first_qset &&
		    qset < pi->first_qset + pi->nqsets)
			वापस pi;
	पूर्ण

	/* should never happen! */
	BUG();
	वापस शून्य;
पूर्ण

अटल पूर्णांक sge_qinfo_uld_txq_entries(स्थिर काष्ठा adapter *adap, पूर्णांक uld)
अणु
	स्थिर काष्ठा sge_uld_txq_info *utxq_info = adap->sge.uld_txq_info[uld];

	अगर (!utxq_info)
		वापस 0;

	वापस DIV_ROUND_UP(utxq_info->ntxq, 4);
पूर्ण

अटल पूर्णांक sge_qinfo_uld_rspq_entries(स्थिर काष्ठा adapter *adap, पूर्णांक uld,
				      bool ciq)
अणु
	स्थिर काष्ठा sge_uld_rxq_info *urxq_info = adap->sge.uld_rxq_info[uld];

	अगर (!urxq_info)
		वापस 0;

	वापस ciq ? DIV_ROUND_UP(urxq_info->nciq, 4) :
		     DIV_ROUND_UP(urxq_info->nrxq, 4);
पूर्ण

अटल पूर्णांक sge_qinfo_uld_rxq_entries(स्थिर काष्ठा adapter *adap, पूर्णांक uld)
अणु
	वापस sge_qinfo_uld_rspq_entries(adap, uld, false);
पूर्ण

अटल पूर्णांक sge_qinfo_uld_ciq_entries(स्थिर काष्ठा adapter *adap, पूर्णांक uld)
अणु
	वापस sge_qinfo_uld_rspq_entries(adap, uld, true);
पूर्ण

अटल पूर्णांक sge_qinfo_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	पूर्णांक eth_entries, ctrl_entries, eohw_entries = 0, eosw_entries = 0;
	पूर्णांक uld_rxq_entries[CXGB4_ULD_MAX] = अणु 0 पूर्ण;
	पूर्णांक uld_ciq_entries[CXGB4_ULD_MAX] = अणु 0 पूर्ण;
	पूर्णांक uld_txq_entries[CXGB4_TX_MAX] = अणु 0 पूर्ण;
	स्थिर काष्ठा sge_uld_txq_info *utxq_info;
	स्थिर काष्ठा sge_uld_rxq_info *urxq_info;
	काष्ठा cxgb4_tc_port_mqprio *port_mqprio;
	काष्ठा adapter *adap = seq->निजी;
	पूर्णांक i, j, n, r = (uपूर्णांकptr_t)v - 1;
	काष्ठा sge *s = &adap->sge;

	eth_entries = DIV_ROUND_UP(adap->sge.ethqsets, 4);
	ctrl_entries = DIV_ROUND_UP(MAX_CTRL_QUEUES, 4);

	अगर (r)
		seq_अ_दो(seq, '\n');

#घोषणा S3(fmt_spec, s, v) \
करो अणु \
	seq_म_लिखो(seq, "%-12s", s); \
	क्रम (i = 0; i < n; ++i) \
		seq_म_लिखो(seq, " %16" fmt_spec, v); \
	seq_अ_दो(seq, '\n'); \
पूर्ण जबतक (0)
#घोषणा S(s, v) S3("s", s, v)
#घोषणा T3(fmt_spec, s, v) S3(fmt_spec, s, tx[i].v)
#घोषणा T(s, v) S3("u", s, tx[i].v)
#घोषणा TL(s, v) T3("lu", s, v)
#घोषणा R3(fmt_spec, s, v) S3(fmt_spec, s, rx[i].v)
#घोषणा R(s, v) S3("u", s, rx[i].v)
#घोषणा RL(s, v) R3("lu", s, v)

	अगर (r < eth_entries) अणु
		पूर्णांक base_qset = r * 4;
		स्थिर काष्ठा sge_eth_rxq *rx = &s->ethrxq[base_qset];
		स्थिर काष्ठा sge_eth_txq *tx = &s->ethtxq[base_qset];

		n = min(4, s->ethqsets - 4 * r);

		S("QType:", "Ethernet");
		S("Interface:",
		  rx[i].rspq.netdev ? rx[i].rspq.netdev->name : "N/A");
		T("TxQ ID:", q.cntxt_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ CIDX:", q.cidx);
		T("TxQ PIDX:", q.pidx);
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
		T("DCB Prio:", dcb_prio);
		S3("u", "DCB PGID:",
		   (ethqset2pinfo(adap, base_qset + i)->dcb.pgid >>
		    4*(7-tx[i].dcb_prio)) & 0xf);
		S3("u", "DCB PFC:",
		   (ethqset2pinfo(adap, base_qset + i)->dcb.pfcen >>
		    1*(7-tx[i].dcb_prio)) & 0x1);
#पूर्ण_अगर
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:", s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);
		RL("RxPackets:", stats.pkts);
		RL("RxCSO:", stats.rx_cso);
		RL("VLANxtract:", stats.vlan_ex);
		RL("LROmerged:", stats.lro_merged);
		RL("LROpackets:", stats.lro_pkts);
		RL("RxDrops:", stats.rx_drops);
		RL("RxBadPkts:", stats.bad_rx_pkts);
		TL("TSO:", tso);
		TL("USO:", uso);
		TL("TxCSO:", tx_cso);
		TL("VLANins:", vlan_ins);
		TL("TxQFull:", q.stops);
		TL("TxQRestarts:", q.restarts);
		TL("TxMapErr:", mapping_err);
		RL("FLAllocErr:", fl.alloc_failed);
		RL("FLLrgAlcErr:", fl.large_alloc_failed);
		RL("FLMapErr:", fl.mapping_err);
		RL("FLLow:", fl.low);
		RL("FLStarving:", fl.starving);

		जाओ out;
	पूर्ण

	r -= eth_entries;
	क्रम_each_port(adap, j) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, j);
		स्थिर काष्ठा sge_eth_rxq *rx;

		mutex_lock(&pi->vi_mirror_mutex);
		अगर (!pi->vi_mirror_count) अणु
			mutex_unlock(&pi->vi_mirror_mutex);
			जारी;
		पूर्ण

		अगर (r >= DIV_ROUND_UP(pi->nmirrorqsets, 4)) अणु
			r -= DIV_ROUND_UP(pi->nmirrorqsets, 4);
			mutex_unlock(&pi->vi_mirror_mutex);
			जारी;
		पूर्ण

		rx = &s->mirror_rxq[j][r * 4];
		n = min(4, pi->nmirrorqsets - 4 * r);

		S("QType:", "Mirror-Rxq");
		S("Interface:",
		  rx[i].rspq.netdev ? rx[i].rspq.netdev->name : "N/A");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:", s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);
		RL("RxPackets:", stats.pkts);
		RL("RxCSO:", stats.rx_cso);
		RL("VLANxtract:", stats.vlan_ex);
		RL("LROmerged:", stats.lro_merged);
		RL("LROpackets:", stats.lro_pkts);
		RL("RxDrops:", stats.rx_drops);
		RL("RxBadPkts:", stats.bad_rx_pkts);
		RL("FLAllocErr:", fl.alloc_failed);
		RL("FLLrgAlcErr:", fl.large_alloc_failed);
		RL("FLMapErr:", fl.mapping_err);
		RL("FLLow:", fl.low);
		RL("FLStarving:", fl.starving);

		mutex_unlock(&pi->vi_mirror_mutex);
		जाओ out;
	पूर्ण

	अगर (!adap->tc_mqprio)
		जाओ skip_mqprio;

	mutex_lock(&adap->tc_mqprio->mqprio_mutex);
	अगर (!refcount_पढ़ो(&adap->tc_mqprio->refcnt)) अणु
		mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
		जाओ skip_mqprio;
	पूर्ण

	eohw_entries = DIV_ROUND_UP(adap->sge.eoqsets, 4);
	अगर (r < eohw_entries) अणु
		पूर्णांक base_qset = r * 4;
		स्थिर काष्ठा sge_ofld_rxq *rx = &s->eohw_rxq[base_qset];
		स्थिर काष्ठा sge_eohw_txq *tx = &s->eohw_txq[base_qset];

		n = min(4, s->eoqsets - 4 * r);

		S("QType:", "ETHOFLD");
		S("Interface:",
		  rx[i].rspq.netdev ? rx[i].rspq.netdev->name : "N/A");
		T("TxQ ID:", q.cntxt_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ CIDX:", q.cidx);
		T("TxQ PIDX:", q.pidx);
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:", s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		S3("u", "FL size:", rx->fl.size ? rx->fl.size - 8 : 0);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);
		RL("RxPackets:", stats.pkts);
		RL("RxImm:", stats.imm);
		RL("RxAN", stats.an);
		RL("RxNoMem", stats.nomem);
		TL("TSO:", tso);
		TL("USO:", uso);
		TL("TxCSO:", tx_cso);
		TL("VLANins:", vlan_ins);
		TL("TxQFull:", q.stops);
		TL("TxQRestarts:", q.restarts);
		TL("TxMapErr:", mapping_err);
		RL("FLAllocErr:", fl.alloc_failed);
		RL("FLLrgAlcErr:", fl.large_alloc_failed);
		RL("FLMapErr:", fl.mapping_err);
		RL("FLLow:", fl.low);
		RL("FLStarving:", fl.starving);

		mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
		जाओ out;
	पूर्ण

	r -= eohw_entries;
	क्रम (j = 0; j < adap->params.nports; j++) अणु
		पूर्णांक entries;
		u8 tc;

		port_mqprio = &adap->tc_mqprio->port_mqprio[j];
		entries = 0;
		क्रम (tc = 0; tc < port_mqprio->mqprio.qopt.num_tc; tc++)
			entries += port_mqprio->mqprio.qopt.count[tc];

		अगर (!entries)
			जारी;

		eosw_entries = DIV_ROUND_UP(entries, 4);
		अगर (r < eosw_entries) अणु
			स्थिर काष्ठा sge_eosw_txq *tx;

			n = min(4, entries - 4 * r);
			tx = &port_mqprio->eosw_txq[4 * r];

			S("QType:", "EOSW-TXQ");
			S("Interface:",
			  adap->port[j] ? adap->port[j]->name : "N/A");
			T("EOTID:", hwtid);
			T("HWQID:", hwqid);
			T("State:", state);
			T("Size:", ndesc);
			T("In-Use:", inuse);
			T("Credits:", cred);
			T("Compl:", ncompl);
			T("Last-Compl:", last_compl);
			T("PIDX:", pidx);
			T("Last-PIDX:", last_pidx);
			T("CIDX:", cidx);
			T("Last-CIDX:", last_cidx);
			T("FLOWC-IDX:", flowc_idx);

			mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
			जाओ out;
		पूर्ण

		r -= eosw_entries;
	पूर्ण
	mutex_unlock(&adap->tc_mqprio->mqprio_mutex);

skip_mqprio:
	अगर (!is_uld(adap))
		जाओ skip_uld;

	mutex_lock(&uld_mutex);
	अगर (s->uld_txq_info)
		क्रम (i = 0; i < ARRAY_SIZE(uld_txq_entries); i++)
			uld_txq_entries[i] = sge_qinfo_uld_txq_entries(adap, i);

	अगर (s->uld_rxq_info) अणु
		क्रम (i = 0; i < ARRAY_SIZE(uld_rxq_entries); i++) अणु
			uld_rxq_entries[i] = sge_qinfo_uld_rxq_entries(adap, i);
			uld_ciq_entries[i] = sge_qinfo_uld_ciq_entries(adap, i);
		पूर्ण
	पूर्ण

	अगर (r < uld_txq_entries[CXGB4_TX_OFLD]) अणु
		स्थिर काष्ठा sge_uld_txq *tx;

		utxq_info = s->uld_txq_info[CXGB4_TX_OFLD];
		tx = &utxq_info->uldtxq[r * 4];
		n = min(4, utxq_info->ntxq - 4 * r);

		S("QType:", "OFLD-TXQ");
		T("TxQ ID:", q.cntxt_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ CIDX:", q.cidx);
		T("TxQ PIDX:", q.pidx);

		जाओ unlock;
	पूर्ण

	r -= uld_txq_entries[CXGB4_TX_OFLD];
	अगर (r < uld_rxq_entries[CXGB4_ULD_RDMA]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;

		urxq_info = s->uld_rxq_info[CXGB4_ULD_RDMA];
		rx = &urxq_info->uldrxq[r * 4];
		n = min(4, urxq_info->nrxq - 4 * r);

		S("QType:", "RDMA-CPL");
		S("Interface:",
		  rx[i].rspq.netdev ? rx[i].rspq.netdev->name : "N/A");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);

		जाओ unlock;
	पूर्ण

	r -= uld_rxq_entries[CXGB4_ULD_RDMA];
	अगर (r < uld_ciq_entries[CXGB4_ULD_RDMA]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;
		पूर्णांक ciq_idx = 0;

		urxq_info = s->uld_rxq_info[CXGB4_ULD_RDMA];
		ciq_idx = urxq_info->nrxq + (r * 4);
		rx = &urxq_info->uldrxq[ciq_idx];
		n = min(4, urxq_info->nciq - 4 * r);

		S("QType:", "RDMA-CIQ");
		S("Interface:",
		  rx[i].rspq.netdev ? rx[i].rspq.netdev->name : "N/A");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);

		जाओ unlock;
	पूर्ण

	r -= uld_ciq_entries[CXGB4_ULD_RDMA];
	अगर (r < uld_rxq_entries[CXGB4_ULD_ISCSI]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;

		urxq_info = s->uld_rxq_info[CXGB4_ULD_ISCSI];
		rx = &urxq_info->uldrxq[r * 4];
		n = min(4, urxq_info->nrxq - 4 * r);

		S("QType:", "iSCSI");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);

		जाओ unlock;
	पूर्ण

	r -= uld_rxq_entries[CXGB4_ULD_ISCSI];
	अगर (r < uld_rxq_entries[CXGB4_ULD_ISCSIT]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;

		urxq_info = s->uld_rxq_info[CXGB4_ULD_ISCSIT];
		rx = &urxq_info->uldrxq[r * 4];
		n = min(4, urxq_info->nrxq - 4 * r);

		S("QType:", "iSCSIT");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);

		जाओ unlock;
	पूर्ण

	r -= uld_rxq_entries[CXGB4_ULD_ISCSIT];
	अगर (r < uld_rxq_entries[CXGB4_ULD_TLS]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;

		urxq_info = s->uld_rxq_info[CXGB4_ULD_TLS];
		rx = &urxq_info->uldrxq[r * 4];
		n = min(4, urxq_info->nrxq - 4 * r);

		S("QType:", "TLS");
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);

		जाओ unlock;
	पूर्ण

	r -= uld_rxq_entries[CXGB4_ULD_TLS];
	अगर (r < uld_txq_entries[CXGB4_TX_CRYPTO]) अणु
		स्थिर काष्ठा sge_ofld_rxq *rx;
		स्थिर काष्ठा sge_uld_txq *tx;

		utxq_info = s->uld_txq_info[CXGB4_TX_CRYPTO];
		urxq_info = s->uld_rxq_info[CXGB4_ULD_CRYPTO];
		tx = &utxq_info->uldtxq[r * 4];
		rx = &urxq_info->uldrxq[r * 4];
		n = min(4, utxq_info->ntxq - 4 * r);

		S("QType:", "Crypto");
		T("TxQ ID:", q.cntxt_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ CIDX:", q.cidx);
		T("TxQ PIDX:", q.pidx);
		R("RspQ ID:", rspq.असल_id);
		R("RspQ size:", rspq.size);
		R("RspQE size:", rspq.iqe_len);
		R("RspQ CIDX:", rspq.cidx);
		R("RspQ Gen:", rspq.gen);
		S3("u", "Intr delay:", qसमयr_val(adap, &rx[i].rspq));
		S3("u", "Intr pktcnt:",	s->counter_val[rx[i].rspq.pktcnt_idx]);
		R("FL ID:", fl.cntxt_id);
		R("FL size:", fl.size - 8);
		R("FL pend:", fl.pend_cred);
		R("FL avail:", fl.avail);
		R("FL PIDX:", fl.pidx);
		R("FL CIDX:", fl.cidx);

		जाओ unlock;
	पूर्ण

	r -= uld_txq_entries[CXGB4_TX_CRYPTO];
	mutex_unlock(&uld_mutex);

skip_uld:
	अगर (r < ctrl_entries) अणु
		स्थिर काष्ठा sge_ctrl_txq *tx = &s->ctrlq[r * 4];

		n = min(4, adap->params.nports - 4 * r);

		S("QType:", "Control");
		T("TxQ ID:", q.cntxt_id);
		T("TxQ size:", q.size);
		T("TxQ inuse:", q.in_use);
		T("TxQ CIDX:", q.cidx);
		T("TxQ PIDX:", q.pidx);
		TL("TxQFull:", q.stops);
		TL("TxQRestarts:", q.restarts);

		जाओ out;
	पूर्ण

	r -= ctrl_entries;
	अगर (r < 1) अणु
		स्थिर काष्ठा sge_rspq *evtq = &s->fw_evtq;

		seq_म_लिखो(seq, "%-12s %16s\n", "QType:", "FW event queue");
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ ID:", evtq->असल_id);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ size:", evtq->size);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQE size:", evtq->iqe_len);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ CIDX:", evtq->cidx);
		seq_म_लिखो(seq, "%-12s %16u\n", "RspQ Gen:", evtq->gen);
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr delay:",
			   qसमयr_val(adap, evtq));
		seq_म_लिखो(seq, "%-12s %16u\n", "Intr pktcnt:",
			   s->counter_val[evtq->pktcnt_idx]);

		जाओ out;
	पूर्ण

#अघोषित R
#अघोषित RL
#अघोषित T
#अघोषित TL
#अघोषित S
#अघोषित R3
#अघोषित T3
#अघोषित S3
out:
	वापस 0;

unlock:
	mutex_unlock(&uld_mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक sge_queue_entries(काष्ठा adapter *adap)
अणु
	पूर्णांक i, tot_uld_entries = 0, eohw_entries = 0, eosw_entries = 0;
	पूर्णांक mirror_rxq_entries = 0;

	अगर (adap->tc_mqprio) अणु
		काष्ठा cxgb4_tc_port_mqprio *port_mqprio;
		u8 tc;

		mutex_lock(&adap->tc_mqprio->mqprio_mutex);
		अगर (adap->sge.eohw_txq)
			eohw_entries = DIV_ROUND_UP(adap->sge.eoqsets, 4);

		क्रम (i = 0; i < adap->params.nports; i++) अणु
			u32 entries = 0;

			port_mqprio = &adap->tc_mqprio->port_mqprio[i];
			क्रम (tc = 0; tc < port_mqprio->mqprio.qopt.num_tc; tc++)
				entries += port_mqprio->mqprio.qopt.count[tc];

			अगर (entries)
				eosw_entries += DIV_ROUND_UP(entries, 4);
		पूर्ण
		mutex_unlock(&adap->tc_mqprio->mqprio_mutex);
	पूर्ण

	क्रम_each_port(adap, i) अणु
		काष्ठा port_info *pi = adap2pinfo(adap, i);

		mutex_lock(&pi->vi_mirror_mutex);
		अगर (pi->vi_mirror_count)
			mirror_rxq_entries += DIV_ROUND_UP(pi->nmirrorqsets, 4);
		mutex_unlock(&pi->vi_mirror_mutex);
	पूर्ण

	अगर (!is_uld(adap))
		जाओ lld_only;

	mutex_lock(&uld_mutex);
	क्रम (i = 0; i < CXGB4_TX_MAX; i++)
		tot_uld_entries += sge_qinfo_uld_txq_entries(adap, i);

	क्रम (i = 0; i < CXGB4_ULD_MAX; i++) अणु
		tot_uld_entries += sge_qinfo_uld_rxq_entries(adap, i);
		tot_uld_entries += sge_qinfo_uld_ciq_entries(adap, i);
	पूर्ण
	mutex_unlock(&uld_mutex);

lld_only:
	वापस DIV_ROUND_UP(adap->sge.ethqsets, 4) + mirror_rxq_entries +
	       eohw_entries + eosw_entries + tot_uld_entries +
	       DIV_ROUND_UP(MAX_CTRL_QUEUES, 4) + 1;
पूर्ण

अटल व्योम *sge_queue_start(काष्ठा seq_file *seq, loff_t *pos)
अणु
	पूर्णांक entries = sge_queue_entries(seq->निजी);

	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल व्योम sge_queue_stop(काष्ठा seq_file *seq, व्योम *v)
अणु
पूर्ण

अटल व्योम *sge_queue_next(काष्ठा seq_file *seq, व्योम *v, loff_t *pos)
अणु
	पूर्णांक entries = sge_queue_entries(seq->निजी);

	++*pos;
	वापस *pos < entries ? (व्योम *)((uपूर्णांकptr_t)*pos + 1) : शून्य;
पूर्ण

अटल स्थिर काष्ठा seq_operations sge_qinfo_seq_ops = अणु
	.start = sge_queue_start,
	.next  = sge_queue_next,
	.stop  = sge_queue_stop,
	.show  = sge_qinfo_show
पूर्ण;

अटल पूर्णांक sge_qinfo_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक res = seq_खोलो(file, &sge_qinfo_seq_ops);

	अगर (!res) अणु
		काष्ठा seq_file *seq = file->निजी_data;

		seq->निजी = inode->i_निजी;
	पूर्ण
	वापस res;
पूर्ण

अटल स्थिर काष्ठा file_operations sge_qinfo_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = sge_qinfo_खोलो,
	.पढ़ो    = seq_पढ़ो,
	.llseek  = seq_lseek,
	.release = seq_release,
पूर्ण;

पूर्णांक mem_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अचिन्हित पूर्णांक mem;
	काष्ठा adapter *adap;

	file->निजी_data = inode->i_निजी;

	mem = (uपूर्णांकptr_t)file->निजी_data & 0x7;
	adap = file->निजी_data - mem;

	(व्योम)t4_fwcache(adap, FW_PARAM_DEV_FWCACHE_FLUSH);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mem_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	loff_t pos = *ppos;
	loff_t avail = file_inode(file)->i_size;
	अचिन्हित पूर्णांक mem = (uपूर्णांकptr_t)file->निजी_data & 0x7;
	काष्ठा adapter *adap = file->निजी_data - mem;
	__be32 *data;
	पूर्णांक ret;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= avail)
		वापस 0;
	अगर (count > avail - pos)
		count = avail - pos;

	data = kvzalloc(count, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	spin_lock(&adap->win0_lock);
	ret = t4_memory_rw(adap, 0, mem, pos, count, data, T4_MEMORY_READ);
	spin_unlock(&adap->win0_lock);
	अगर (ret) अणु
		kvमुक्त(data);
		वापस ret;
	पूर्ण
	ret = copy_to_user(buf, data, count);

	kvमुक्त(data);
	अगर (ret)
		वापस -EFAULT;

	*ppos = pos + count;
	वापस count;
पूर्ण
अटल स्थिर काष्ठा file_operations mem_debugfs_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = simple_खोलो,
	.पढ़ो    = mem_पढ़ो,
	.llseek  = शेष_llseek,
पूर्ण;

अटल पूर्णांक tid_info_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adap = seq->निजी;
	स्थिर काष्ठा tid_info *t;
	क्रमागत chip_type chip;

	t = &adap->tids;
	chip = CHELSIO_CHIP_VERSION(adap->params.chip);
	अगर (t4_पढ़ो_reg(adap, LE_DB_CONFIG_A) & HASHEN_F) अणु
		अचिन्हित पूर्णांक sb;
		seq_म_लिखो(seq, "Connections in use: %u\n",
			   atomic_पढ़ो(&t->conns_in_use));

		अगर (chip <= CHELSIO_T5)
			sb = t4_पढ़ो_reg(adap, LE_DB_SERVER_INDEX_A) / 4;
		अन्यथा
			sb = t4_पढ़ो_reg(adap, LE_DB_SRVR_START_INDEX_A);

		अगर (sb) अणु
			seq_म_लिखो(seq, "TID range: %u..%u/%u..%u", t->tid_base,
				   sb - 1, adap->tids.hash_base,
				   t->tid_base + t->ntids - 1);
			seq_म_लिखो(seq, ", in use: %u/%u\n",
				   atomic_पढ़ो(&t->tids_in_use),
				   atomic_पढ़ो(&t->hash_tids_in_use));
		पूर्ण अन्यथा अगर (adap->flags & CXGB4_FW_OFLD_CONN) अणु
			seq_म_लिखो(seq, "TID range: %u..%u/%u..%u",
				   t->aftid_base,
				   t->aftid_end,
				   adap->tids.hash_base,
				   t->tid_base + t->ntids - 1);
			seq_म_लिखो(seq, ", in use: %u/%u\n",
				   atomic_पढ़ो(&t->tids_in_use),
				   atomic_पढ़ो(&t->hash_tids_in_use));
		पूर्ण अन्यथा अणु
			seq_म_लिखो(seq, "TID range: %u..%u",
				   adap->tids.hash_base,
				   t->tid_base + t->ntids - 1);
			seq_म_लिखो(seq, ", in use: %u\n",
				   atomic_पढ़ो(&t->hash_tids_in_use));
		पूर्ण
	पूर्ण अन्यथा अगर (t->ntids) अणु
		seq_म_लिखो(seq, "Connections in use: %u\n",
			   atomic_पढ़ो(&t->conns_in_use));

		seq_म_लिखो(seq, "TID range: %u..%u", t->tid_base,
			   t->tid_base + t->ntids - 1);
		seq_म_लिखो(seq, ", in use: %u\n",
			   atomic_पढ़ो(&t->tids_in_use));
	पूर्ण

	अगर (t->nstids)
		seq_म_लिखो(seq, "STID range: %u..%u, in use-IPv4/IPv6: %u/%u\n",
			   (!t->stid_base &&
			   (chip <= CHELSIO_T5)) ?
			   t->stid_base + 1 : t->stid_base,
			   t->stid_base + t->nstids - 1,
			   t->stids_in_use - t->v6_stids_in_use,
			   t->v6_stids_in_use);

	अगर (t->natids)
		seq_म_लिखो(seq, "ATID range: 0..%u, in use: %u\n",
			   t->natids - 1, t->atids_in_use);
	seq_म_लिखो(seq, "FTID range: %u..%u\n", t->ftid_base,
		   t->ftid_base + t->nftids - 1);
	अगर (t->nsftids)
		seq_म_लिखो(seq, "SFTID range: %u..%u in use: %u\n",
			   t->sftid_base, t->sftid_base + t->nsftids - 2,
			   t->sftids_in_use);
	अगर (t->nhpftids)
		seq_म_लिखो(seq, "HPFTID range: %u..%u\n", t->hpftid_base,
			   t->hpftid_base + t->nhpftids - 1);
	अगर (t->neotids)
		seq_म_लिखो(seq, "EOTID range: %u..%u, in use: %u\n",
			   t->eotid_base, t->eotid_base + t->neotids - 1,
			   atomic_पढ़ो(&t->eotids_in_use));
	अगर (t->ntids)
		seq_म_लिखो(seq, "HW TID usage: %u IP users, %u IPv6 users\n",
			   t4_पढ़ो_reg(adap, LE_DB_ACT_CNT_IPV4_A),
			   t4_पढ़ो_reg(adap, LE_DB_ACT_CNT_IPV6_A));
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tid_info);

अटल व्योम add_debugfs_mem(काष्ठा adapter *adap, स्थिर अक्षर *name,
			    अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक size_mb)
अणु
	debugfs_create_file_size(name, 0400, adap->debugfs_root,
				 (व्योम *)adap + idx, &mem_debugfs_fops,
				 size_mb << 20);
पूर्ण

अटल sमाप_प्रकार blocked_fl_पढ़ो(काष्ठा file *filp, अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक len;
	स्थिर काष्ठा adapter *adap = filp->निजी_data;
	अक्षर *buf;
	sमाप_प्रकार size = (adap->sge.egr_sz + 3) / 4 +
			adap->sge.egr_sz / 32 + 2; /* includes ,/\न/\0 */

	buf = kzalloc(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len = snम_लिखो(buf, size - 1, "%*pb\n",
		       adap->sge.egr_sz, adap->sge.blocked_fl);
	len += प्र_लिखो(buf + len, "\n");
	size = simple_पढ़ो_from_buffer(ubuf, count, ppos, buf, len);
	kमुक्त(buf);
	वापस size;
पूर्ण

अटल sमाप_प्रकार blocked_fl_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *ubuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ *t;
	काष्ठा adapter *adap = filp->निजी_data;

	t = kसुस्मृति(BITS_TO_LONGS(adap->sge.egr_sz), माप(दीर्घ), GFP_KERNEL);
	अगर (!t)
		वापस -ENOMEM;

	err = biपंचांगap_parse_user(ubuf, count, t, adap->sge.egr_sz);
	अगर (err) अणु
		kमुक्त(t);
		वापस err;
	पूर्ण

	biपंचांगap_copy(adap->sge.blocked_fl, t, adap->sge.egr_sz);
	kमुक्त(t);
	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations blocked_fl_fops = अणु
	.owner   = THIS_MODULE,
	.खोलो    = simple_खोलो,
	.पढ़ो    = blocked_fl_पढ़ो,
	.ग_लिखो   = blocked_fl_ग_लिखो,
	.llseek  = generic_file_llseek,
पूर्ण;

अटल व्योम mem_region_show(काष्ठा seq_file *seq, स्थिर अक्षर *name,
			    अचिन्हित पूर्णांक from, अचिन्हित पूर्णांक to)
अणु
	अक्षर buf[40];

	string_get_size((u64)to - from + 1, 1, STRING_UNITS_2, buf,
			माप(buf));
	seq_म_लिखो(seq, "%-15s %#x-%#x [%s]\n", name, from, to, buf);
पूर्ण

अटल पूर्णांक meminfo_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	अटल स्थिर अक्षर * स्थिर memory[] = अणु "EDC0:", "EDC1:", "MC:",
					       "MC0:", "MC1:", "HMA:"पूर्ण;
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा cudbg_meminfo meminfo;
	पूर्णांक i, rc;

	स_रखो(&meminfo, 0, माप(काष्ठा cudbg_meminfo));
	rc = cudbg_fill_meminfo(adap, &meminfo);
	अगर (rc)
		वापस -ENXIO;

	क्रम (i = 0; i < meminfo.avail_c; i++)
		mem_region_show(seq, memory[meminfo.avail[i].idx],
				meminfo.avail[i].base,
				meminfo.avail[i].limit - 1);

	seq_अ_दो(seq, '\n');
	क्रम (i = 0; i < meminfo.mem_c; i++) अणु
		अगर (meminfo.mem[i].idx >= ARRAY_SIZE(cudbg_region))
			जारी;                        /* skip holes */
		अगर (!meminfo.mem[i].limit)
			meminfo.mem[i].limit =
				i < meminfo.mem_c - 1 ?
				meminfo.mem[i + 1].base - 1 : ~0;
		mem_region_show(seq, cudbg_region[meminfo.mem[i].idx],
				meminfo.mem[i].base, meminfo.mem[i].limit);
	पूर्ण

	seq_अ_दो(seq, '\n');
	mem_region_show(seq, "uP RAM:", meminfo.up_ram_lo, meminfo.up_ram_hi);
	mem_region_show(seq, "uP Extmem2:", meminfo.up_exपंचांगem2_lo,
			meminfo.up_exपंचांगem2_hi);

	seq_म_लिखो(seq, "\n%u Rx pages (%u free) of size %uKiB for %u channels\n",
		   meminfo.rx_pages_data[0], meminfo.मुक्त_rx_cnt,
		   meminfo.rx_pages_data[1], meminfo.rx_pages_data[2]);

	seq_म_लिखो(seq, "%u Tx pages (%u free) of size %u%ciB for %u channels\n",
		   meminfo.tx_pages_data[0], meminfo.मुक्त_tx_cnt,
		   meminfo.tx_pages_data[1], meminfo.tx_pages_data[2],
		   meminfo.tx_pages_data[3]);

	seq_म_लिखो(seq, "%u p-structs (%u free)\n\n",
		   meminfo.p_काष्ठाs, meminfo.p_काष्ठाs_मुक्त_cnt);

	क्रम (i = 0; i < 4; i++)
		/* For T6 these are MAC buffer groups */
		seq_म_लिखो(seq, "Port %d using %u pages out of %u allocated\n",
			   i, meminfo.port_used[i], meminfo.port_alloc[i]);

	क्रम (i = 0; i < adap->params.arch.nchan; i++)
		/* For T6 these are MAC buffer groups */
		seq_म_लिखो(seq,
			   "Loopback %d using %u pages out of %u allocated\n",
			   i, meminfo.loopback_used[i],
			   meminfo.loopback_alloc[i]);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(meminfo);

अटल पूर्णांक chcr_stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	काष्ठा ch_ktls_port_stats_debug *ktls_port;
	पूर्णांक i = 0;
#पूर्ण_अगर
	काष्ठा adapter *adap = seq->निजी;

	seq_माला_दो(seq, "Chelsio Crypto Accelerator Stats \n");
	seq_म_लिखो(seq, "Cipher Ops: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.cipher_rqst));
	seq_म_लिखो(seq, "Digest Ops: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.digest_rqst));
	seq_म_लिखो(seq, "Aead Ops: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.aead_rqst));
	seq_म_लिखो(seq, "Completion: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.complete));
	seq_म_लिखो(seq, "Error: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.error));
	seq_म_लिखो(seq, "Fallback: %10u \n",
		   atomic_पढ़ो(&adap->chcr_stats.fallback));
	seq_म_लिखो(seq, "TLS PDU Tx: %10u\n",
		   atomic_पढ़ो(&adap->chcr_stats.tls_pdu_tx));
	seq_म_लिखो(seq, "TLS PDU Rx: %10u\n",
		   atomic_पढ़ो(&adap->chcr_stats.tls_pdu_rx));
	seq_म_लिखो(seq, "TLS Keys (DDR) Count: %10u\n",
		   atomic_पढ़ो(&adap->chcr_stats.tls_key));
#अगर IS_ENABLED(CONFIG_CHELSIO_IPSEC_INLINE)
	seq_माला_दो(seq, "\nChelsio Inline IPsec Crypto Accelerator Stats\n");
	seq_म_लिखो(seq, "IPSec PDU: %10u\n",
		   atomic_पढ़ो(&adap->ch_ipsec_stats.ipsec_cnt));
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_CHELSIO_TLS_DEVICE)
	seq_माला_दो(seq, "\nChelsio KTLS Crypto Accelerator Stats\n");
	seq_म_लिखो(seq, "Tx TLS offload refcount:          %20u\n",
		   refcount_पढ़ो(&adap->chcr_ktls.ktls_refcount));
	seq_म_लिखो(seq, "Tx records send:                  %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_send_records));
	seq_म_लिखो(seq, "Tx partial start of records:      %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_start_pkts));
	seq_म_लिखो(seq, "Tx partial middle of records:     %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_middle_pkts));
	seq_म_लिखो(seq, "Tx partial end of record:         %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_end_pkts));
	seq_म_लिखो(seq, "Tx complete records:              %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_complete_pkts));
	seq_म_लिखो(seq, "TX trim pkts :                    %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_trimmed_pkts));
	seq_म_लिखो(seq, "TX sw fallback :                  %20llu\n",
		   atomic64_पढ़ो(&adap->ch_ktls_stats.ktls_tx_fallback));
	जबतक (i < MAX_NPORTS) अणु
		ktls_port = &adap->ch_ktls_stats.ktls_port[i];
		seq_म_लिखो(seq, "Port %d\n", i);
		seq_म_लिखो(seq, "Tx connection created:            %20llu\n",
			   atomic64_पढ़ो(&ktls_port->ktls_tx_connection_खोलो));
		seq_म_लिखो(seq, "Tx connection failed:             %20llu\n",
			   atomic64_पढ़ो(&ktls_port->ktls_tx_connection_fail));
		seq_म_लिखो(seq, "Tx connection closed:             %20llu\n",
			   atomic64_पढ़ो(&ktls_port->ktls_tx_connection_बंद));
		i++;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(chcr_stats);

#घोषणा PRINT_ADAP_STATS(string, value) \
	seq_म_लिखो(seq, "%-25s %-20llu\n", (string), \
		   (अचिन्हित दीर्घ दीर्घ)(value))

#घोषणा PRINT_CH_STATS(string, value) \
करो अणु \
	seq_म_लिखो(seq, "%-25s ", (string)); \
	क्रम (i = 0; i < adap->params.arch.nchan; i++) \
		seq_म_लिखो(seq, "%-20llu ", \
			   (अचिन्हित दीर्घ दीर्घ)stats.value[i]); \
	seq_म_लिखो(seq, "\n"); \
पूर्ण जबतक (0)

#घोषणा PRINT_CH_STATS2(string, value) \
करो अणु \
	seq_म_लिखो(seq, "%-25s ", (string)); \
	क्रम (i = 0; i < adap->params.arch.nchan; i++) \
		seq_म_लिखो(seq, "%-20llu ", \
			   (अचिन्हित दीर्घ दीर्घ)stats[i].value); \
	seq_म_लिखो(seq, "\n"); \
पूर्ण जबतक (0)

अटल व्योम show_tcp_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_tcp_stats v4, v6;

	spin_lock(&adap->stats_lock);
	t4_tp_get_tcp_stats(adap, &v4, &v6, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("tcp_ipv4_out_rsts:", v4.tcp_out_rsts);
	PRINT_ADAP_STATS("tcp_ipv4_in_segs:", v4.tcp_in_segs);
	PRINT_ADAP_STATS("tcp_ipv4_out_segs:", v4.tcp_out_segs);
	PRINT_ADAP_STATS("tcp_ipv4_retrans_segs:", v4.tcp_retrans_segs);
	PRINT_ADAP_STATS("tcp_ipv6_out_rsts:", v6.tcp_out_rsts);
	PRINT_ADAP_STATS("tcp_ipv6_in_segs:", v6.tcp_in_segs);
	PRINT_ADAP_STATS("tcp_ipv6_out_segs:", v6.tcp_out_segs);
	PRINT_ADAP_STATS("tcp_ipv6_retrans_segs:", v6.tcp_retrans_segs);
पूर्ण

अटल व्योम show_ddp_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_usm_stats stats;

	spin_lock(&adap->stats_lock);
	t4_get_usm_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("usm_ddp_frames:", stats.frames);
	PRINT_ADAP_STATS("usm_ddp_octets:", stats.octets);
	PRINT_ADAP_STATS("usm_ddp_drops:", stats.drops);
पूर्ण

अटल व्योम show_rdma_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_rdma_stats stats;

	spin_lock(&adap->stats_lock);
	t4_tp_get_rdma_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("rdma_no_rqe_mod_defer:", stats.rqe_dfr_mod);
	PRINT_ADAP_STATS("rdma_no_rqe_pkt_defer:", stats.rqe_dfr_pkt);
पूर्ण

अटल व्योम show_tp_err_adapter_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_err_stats stats;

	spin_lock(&adap->stats_lock);
	t4_tp_get_err_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_ADAP_STATS("tp_err_ofld_no_neigh:", stats.ofld_no_neigh);
	PRINT_ADAP_STATS("tp_err_ofld_cong_defer:", stats.ofld_cong_defer);
पूर्ण

अटल व्योम show_cpl_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_cpl_stats stats;
	u8 i;

	spin_lock(&adap->stats_lock);
	t4_tp_get_cpl_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_CH_STATS("tp_cpl_requests:", req);
	PRINT_CH_STATS("tp_cpl_responses:", rsp);
पूर्ण

अटल व्योम show_tp_err_channel_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_err_stats stats;
	u8 i;

	spin_lock(&adap->stats_lock);
	t4_tp_get_err_stats(adap, &stats, false);
	spin_unlock(&adap->stats_lock);

	PRINT_CH_STATS("tp_mac_in_errs:", mac_in_errs);
	PRINT_CH_STATS("tp_hdr_in_errs:", hdr_in_errs);
	PRINT_CH_STATS("tp_tcp_in_errs:", tcp_in_errs);
	PRINT_CH_STATS("tp_tcp6_in_errs:", tcp6_in_errs);
	PRINT_CH_STATS("tp_tnl_cong_drops:", tnl_cong_drops);
	PRINT_CH_STATS("tp_tnl_tx_drops:", tnl_tx_drops);
	PRINT_CH_STATS("tp_ofld_vlan_drops:", ofld_vlan_drops);
	PRINT_CH_STATS("tp_ofld_chan_drops:", ofld_chan_drops);
पूर्ण

अटल व्योम show_fcoe_stats(काष्ठा seq_file *seq)
अणु
	काष्ठा adapter *adap = seq->निजी;
	काष्ठा tp_fcoe_stats stats[NCHAN];
	u8 i;

	spin_lock(&adap->stats_lock);
	क्रम (i = 0; i < adap->params.arch.nchan; i++)
		t4_get_fcoe_stats(adap, i, &stats[i], false);
	spin_unlock(&adap->stats_lock);

	PRINT_CH_STATS2("fcoe_octets_ddp", octets_ddp);
	PRINT_CH_STATS2("fcoe_frames_ddp", frames_ddp);
	PRINT_CH_STATS2("fcoe_frames_drop", frames_drop);
पूर्ण

#अघोषित PRINT_CH_STATS2
#अघोषित PRINT_CH_STATS
#अघोषित PRINT_ADAP_STATS

अटल पूर्णांक tp_stats_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा adapter *adap = seq->निजी;

	seq_माला_दो(seq, "\n--------Adapter Stats--------\n");
	show_tcp_stats(seq);
	show_ddp_stats(seq);
	show_rdma_stats(seq);
	show_tp_err_adapter_stats(seq);

	seq_माला_दो(seq, "\n-------- Channel Stats --------\n");
	अगर (adap->params.arch.nchan == NCHAN)
		seq_म_लिखो(seq, "%-25s %-20s %-20s %-20s %-20s\n",
			   " ", "channel 0", "channel 1",
			   "channel 2", "channel 3");
	अन्यथा
		seq_म_लिखो(seq, "%-25s %-20s %-20s\n",
			   " ", "channel 0", "channel 1");
	show_cpl_stats(seq);
	show_tp_err_channel_stats(seq);
	show_fcoe_stats(seq);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(tp_stats);

/* Add an array of Debug FS files.
 */
व्योम add_debugfs_files(काष्ठा adapter *adap,
		       काष्ठा t4_debugfs_entry *files,
		       अचिन्हित पूर्णांक nfiles)
अणु
	पूर्णांक i;

	/* debugfs support is best efक्रमt */
	क्रम (i = 0; i < nfiles; i++)
		debugfs_create_file(files[i].name, files[i].mode,
				    adap->debugfs_root,
				    (व्योम *)adap + files[i].data,
				    files[i].ops);
पूर्ण

पूर्णांक t4_setup_debugfs(काष्ठा adapter *adap)
अणु
	पूर्णांक i;
	u32 size = 0;

	अटल काष्ठा t4_debugfs_entry t4_debugfs_files[] = अणु
		अणु "cim_la", &cim_la_fops, 0400, 0 पूर्ण,
		अणु "cim_pif_la", &cim_pअगर_la_fops, 0400, 0 पूर्ण,
		अणु "cim_ma_la", &cim_ma_la_fops, 0400, 0 पूर्ण,
		अणु "cim_qcfg", &cim_qcfg_fops, 0400, 0 पूर्ण,
		अणु "clk", &clk_fops, 0400, 0 पूर्ण,
		अणु "devlog", &devlog_fops, 0400, 0 पूर्ण,
		अणु "mboxlog", &mboxlog_fops, 0400, 0 पूर्ण,
		अणु "mbox0", &mbox_debugfs_fops, 0600, 0 पूर्ण,
		अणु "mbox1", &mbox_debugfs_fops, 0600, 1 पूर्ण,
		अणु "mbox2", &mbox_debugfs_fops, 0600, 2 पूर्ण,
		अणु "mbox3", &mbox_debugfs_fops, 0600, 3 पूर्ण,
		अणु "mbox4", &mbox_debugfs_fops, 0600, 4 पूर्ण,
		अणु "mbox5", &mbox_debugfs_fops, 0600, 5 पूर्ण,
		अणु "mbox6", &mbox_debugfs_fops, 0600, 6 पूर्ण,
		अणु "mbox7", &mbox_debugfs_fops, 0600, 7 पूर्ण,
		अणु "trace0", &mps_trc_debugfs_fops, 0600, 0 पूर्ण,
		अणु "trace1", &mps_trc_debugfs_fops, 0600, 1 पूर्ण,
		अणु "trace2", &mps_trc_debugfs_fops, 0600, 2 पूर्ण,
		अणु "trace3", &mps_trc_debugfs_fops, 0600, 3 पूर्ण,
		अणु "l2t", &t4_l2t_fops, 0400, 0पूर्ण,
		अणु "mps_tcam", &mps_tcam_debugfs_fops, 0400, 0 पूर्ण,
		अणु "rss", &rss_debugfs_fops, 0400, 0 पूर्ण,
		अणु "rss_config", &rss_config_fops, 0400, 0 पूर्ण,
		अणु "rss_key", &rss_key_debugfs_fops, 0400, 0 पूर्ण,
		अणु "rss_pf_config", &rss_pf_config_debugfs_fops, 0400, 0 पूर्ण,
		अणु "rss_vf_config", &rss_vf_config_debugfs_fops, 0400, 0 पूर्ण,
		अणु "resources", &resources_fops, 0400, 0 पूर्ण,
#अगर_घोषित CONFIG_CHELSIO_T4_DCB
		अणु "dcb_info", &dcb_info_debugfs_fops, 0400, 0 पूर्ण,
#पूर्ण_अगर
		अणु "sge_qinfo", &sge_qinfo_debugfs_fops, 0400, 0 पूर्ण,
		अणु "ibq_tp0",  &cim_ibq_fops, 0400, 0 पूर्ण,
		अणु "ibq_tp1",  &cim_ibq_fops, 0400, 1 पूर्ण,
		अणु "ibq_ulp",  &cim_ibq_fops, 0400, 2 पूर्ण,
		अणु "ibq_sge0", &cim_ibq_fops, 0400, 3 पूर्ण,
		अणु "ibq_sge1", &cim_ibq_fops, 0400, 4 पूर्ण,
		अणु "ibq_ncsi", &cim_ibq_fops, 0400, 5 पूर्ण,
		अणु "obq_ulp0", &cim_obq_fops, 0400, 0 पूर्ण,
		अणु "obq_ulp1", &cim_obq_fops, 0400, 1 पूर्ण,
		अणु "obq_ulp2", &cim_obq_fops, 0400, 2 पूर्ण,
		अणु "obq_ulp3", &cim_obq_fops, 0400, 3 पूर्ण,
		अणु "obq_sge",  &cim_obq_fops, 0400, 4 पूर्ण,
		अणु "obq_ncsi", &cim_obq_fops, 0400, 5 पूर्ण,
		अणु "tp_la", &tp_la_fops, 0400, 0 पूर्ण,
		अणु "ulprx_la", &ulprx_la_fops, 0400, 0 पूर्ण,
		अणु "sensors", &sensors_fops, 0400, 0 पूर्ण,
		अणु "pm_stats", &pm_stats_debugfs_fops, 0400, 0 पूर्ण,
		अणु "tx_rate", &tx_rate_fops, 0400, 0 पूर्ण,
		अणु "cctrl", &cctrl_tbl_fops, 0400, 0 पूर्ण,
#अगर IS_ENABLED(CONFIG_IPV6)
		अणु "clip_tbl", &clip_tbl_fops, 0400, 0 पूर्ण,
#पूर्ण_अगर
		अणु "tids", &tid_info_fops, 0400, 0पूर्ण,
		अणु "blocked_fl", &blocked_fl_fops, 0600, 0 पूर्ण,
		अणु "meminfo", &meminfo_fops, 0400, 0 पूर्ण,
		अणु "crypto", &chcr_stats_fops, 0400, 0 पूर्ण,
		अणु "tp_stats", &tp_stats_fops, 0400, 0 पूर्ण,
	पूर्ण;

	/* Debug FS nodes common to all T5 and later adapters.
	 */
	अटल काष्ठा t4_debugfs_entry t5_debugfs_files[] = अणु
		अणु "obq_sge_rx_q0", &cim_obq_fops, 0400, 6 पूर्ण,
		अणु "obq_sge_rx_q1", &cim_obq_fops, 0400, 7 पूर्ण,
	पूर्ण;

	add_debugfs_files(adap,
			  t4_debugfs_files,
			  ARRAY_SIZE(t4_debugfs_files));
	अगर (!is_t4(adap->params.chip))
		add_debugfs_files(adap,
				  t5_debugfs_files,
				  ARRAY_SIZE(t5_debugfs_files));

	i = t4_पढ़ो_reg(adap, MA_TARGET_MEM_ENABLE_A);
	अगर (i & EDRAM0_ENABLE_F) अणु
		size = t4_पढ़ो_reg(adap, MA_EDRAM0_BAR_A);
		add_debugfs_mem(adap, "edc0", MEM_EDC0, EDRAM0_SIZE_G(size));
	पूर्ण
	अगर (i & EDRAM1_ENABLE_F) अणु
		size = t4_पढ़ो_reg(adap, MA_EDRAM1_BAR_A);
		add_debugfs_mem(adap, "edc1", MEM_EDC1, EDRAM1_SIZE_G(size));
	पूर्ण
	अगर (is_t5(adap->params.chip)) अणु
		अगर (i & EXT_MEM0_ENABLE_F) अणु
			size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY0_BAR_A);
			add_debugfs_mem(adap, "mc0", MEM_MC0,
					EXT_MEM0_SIZE_G(size));
		पूर्ण
		अगर (i & EXT_MEM1_ENABLE_F) अणु
			size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY1_BAR_A);
			add_debugfs_mem(adap, "mc1", MEM_MC1,
					EXT_MEM1_SIZE_G(size));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (i & EXT_MEM_ENABLE_F) अणु
			size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY_BAR_A);
			add_debugfs_mem(adap, "mc", MEM_MC,
					EXT_MEM_SIZE_G(size));
		पूर्ण

		अगर (i & HMA_MUX_F) अणु
			size = t4_पढ़ो_reg(adap, MA_EXT_MEMORY1_BAR_A);
			add_debugfs_mem(adap, "hma", MEM_HMA,
					EXT_MEM1_SIZE_G(size));
		पूर्ण
	पूर्ण

	debugfs_create_file_size("flash", 0400, adap->debugfs_root, adap,
				 &flash_debugfs_fops, adap->params.sf_size);
	debugfs_create_bool("use_backdoor", 0600,
			    adap->debugfs_root, &adap->use_bd);
	debugfs_create_bool("trace_rss", 0600,
			    adap->debugfs_root, &adap->trace_rss);

	वापस 0;
पूर्ण
