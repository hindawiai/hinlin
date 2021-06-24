<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  skl-debug.c - Debugfs क्रम skl driver
 *
 *  Copyright (C) 2016-17 Intel Corp
 */

#समावेश <linux/pci.h>
#समावेश <linux/debugfs.h>
#समावेश <uapi/sound/skl-tplg-पूर्णांकerface.h>
#समावेश "skl.h"
#समावेश "skl-sst-dsp.h"
#समावेश "skl-sst-ipc.h"
#समावेश "skl-topology.h"
#समावेश "../common/sst-dsp.h"
#समावेश "../common/sst-dsp-priv.h"

#घोषणा MOD_BUF		PAGE_SIZE
#घोषणा FW_REG_BUF	PAGE_SIZE
#घोषणा FW_REG_SIZE	0x60

काष्ठा skl_debug अणु
	काष्ठा skl_dev *skl;
	काष्ठा device *dev;

	काष्ठा dentry *fs;
	काष्ठा dentry *modules;
	u8 fw_पढ़ो_buff[FW_REG_BUF];
पूर्ण;

अटल sमाप_प्रकार skl_prपूर्णांक_pins(काष्ठा skl_module_pin *m_pin, अक्षर *buf,
				पूर्णांक max_pin, sमाप_प्रकार size, bool direction)
अणु
	पूर्णांक i;
	sमाप_प्रकार ret = 0;

	क्रम (i = 0; i < max_pin; i++) अणु
		ret += scnम_लिखो(buf + size, MOD_BUF - size,
				"%s %d\n\tModule %d\n\tInstance %d\n\t"
				"In-used %s\n\tType %s\n"
				"\tState %d\n\tIndex %d\n",
				direction ? "Input Pin:" : "Output Pin:",
				i, m_pin[i].id.module_id,
				m_pin[i].id.instance_id,
				m_pin[i].in_use ? "Used" : "Unused",
				m_pin[i].is_dynamic ? "Dynamic" : "Static",
				m_pin[i].pin_state, i);
		size += ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार skl_prपूर्णांक_fmt(काष्ठा skl_module_fmt *fmt, अक्षर *buf,
					sमाप_प्रकार size, bool direction)
अणु
	वापस scnम_लिखो(buf + size, MOD_BUF - size,
			"%s\n\tCh %d\n\tFreq %d\n\tBit depth %d\n\t"
			"Valid bit depth %d\n\tCh config %#x\n\tInterleaving %d\n\t"
			"Sample Type %d\n\tCh Map %#x\n",
			direction ? "Input Format:" : "Output Format:",
			fmt->channels, fmt->s_freq, fmt->bit_depth,
			fmt->valid_bit_depth, fmt->ch_cfg,
			fmt->पूर्णांकerleaving_style, fmt->sample_type,
			fmt->ch_map);
पूर्ण

अटल sमाप_प्रकार module_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			   माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा skl_module_cfg *mconfig = file->निजी_data;
	काष्ठा skl_module *module = mconfig->module;
	काष्ठा skl_module_res *res = &module->resources[mconfig->res_idx];
	अक्षर *buf;
	sमाप_प्रकार ret;

	buf = kzalloc(MOD_BUF, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	ret = scnम_लिखो(buf, MOD_BUF, "Module:\n\tUUID %pUL\n\tModule id %d\n"
			"\tInstance id %d\n\tPvt_id %d\n", mconfig->guid,
			mconfig->id.module_id, mconfig->id.instance_id,
			mconfig->id.pvt_id);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Resources:\n\tCPC %#x\n\tIBS %#x\n\tOBS %#x\t\n",
			res->cpc, res->ibs, res->obs);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Module data:\n\tCore %d\n\tIn queue %d\n\t"
			"Out queue %d\n\tType %s\n",
			mconfig->core_id, mconfig->max_in_queue,
			mconfig->max_out_queue,
			mconfig->is_loadable ? "loadable" : "inbuilt");

	ret += skl_prपूर्णांक_fmt(mconfig->in_fmt, buf, ret, true);
	ret += skl_prपूर्णांक_fmt(mconfig->out_fmt, buf, ret, false);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Fixup:\n\tParams %#x\n\tConverter %#x\n",
			mconfig->params_fixup, mconfig->converter);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Module Gateway:\n\tType %#x\n\tVbus %#x\n\tHW conn %#x\n\tSlot %#x\n",
			mconfig->dev_type, mconfig->vbus_id,
			mconfig->hw_conn_type, mconfig->समय_slot);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Pipeline:\n\tID %d\n\tPriority %d\n\tConn Type %d\n\t"
			"Pages %#x\n", mconfig->pipe->ppl_id,
			mconfig->pipe->pipe_priority, mconfig->pipe->conn_type,
			mconfig->pipe->memory_pages);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"\tParams:\n\t\tHost DMA %d\n\t\tLink DMA %d\n",
			mconfig->pipe->p_params->host_dma_id,
			mconfig->pipe->p_params->link_dma_id);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"\tPCM params:\n\t\tCh %d\n\t\tFreq %d\n\t\tFormat %d\n",
			mconfig->pipe->p_params->ch,
			mconfig->pipe->p_params->s_freq,
			mconfig->pipe->p_params->s_fmt);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"\tLink %#x\n\tStream %#x\n",
			mconfig->pipe->p_params->linktype,
			mconfig->pipe->p_params->stream);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"\tState %d\n\tPassthru %s\n",
			mconfig->pipe->state,
			mconfig->pipe->passthru ? "true" : "false");

	ret += skl_prपूर्णांक_pins(mconfig->m_in_pin, buf,
			mconfig->max_in_queue, ret, true);
	ret += skl_prपूर्णांक_pins(mconfig->m_out_pin, buf,
			mconfig->max_out_queue, ret, false);

	ret += scnम_लिखो(buf + ret, MOD_BUF - ret,
			"Other:\n\tDomain %d\n\tHomogeneous Input %s\n\t"
			"Homogeneous Output %s\n\tIn Queue Mask %d\n\t"
			"Out Queue Mask %d\n\tDMA ID %d\n\tMem Pages %d\n\t"
			"Module Type %d\n\tModule State %d\n",
			mconfig->करोमुख्य,
			mconfig->homogenous_inमाला_दो ? "true" : "false",
			mconfig->homogenous_outमाला_दो ? "true" : "false",
			mconfig->in_queue_mask, mconfig->out_queue_mask,
			mconfig->dma_id, mconfig->mem_pages, mconfig->m_state,
			mconfig->m_type);

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, ret);

	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations mcfg_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = module_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;


व्योम skl_debug_init_module(काष्ठा skl_debug *d,
			काष्ठा snd_soc_dapm_widget *w,
			काष्ठा skl_module_cfg *mconfig)
अणु
	debugfs_create_file(w->name, 0444, d->modules, mconfig,
			    &mcfg_fops);
पूर्ण

अटल sमाप_प्रकार fw_softreg_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा skl_debug *d = file->निजी_data;
	काष्ठा sst_dsp *sst = d->skl->dsp;
	माप_प्रकार w0_stat_sz = sst->addr.w0_stat_sz;
	व्योम __iomem *in_base = sst->mailbox.in_base;
	व्योम __iomem *fw_reg_addr;
	अचिन्हित पूर्णांक offset;
	अक्षर *पंचांगp;
	sमाप_प्रकार ret = 0;

	पंचांगp = kzalloc(FW_REG_BUF, GFP_KERNEL);
	अगर (!पंचांगp)
		वापस -ENOMEM;

	fw_reg_addr = in_base - w0_stat_sz;
	स_रखो(d->fw_पढ़ो_buff, 0, FW_REG_BUF);

	अगर (w0_stat_sz > 0)
		__ioपढ़ो32_copy(d->fw_पढ़ो_buff, fw_reg_addr, w0_stat_sz >> 2);

	क्रम (offset = 0; offset < FW_REG_SIZE; offset += 16) अणु
		ret += scnम_लिखो(पंचांगp + ret, FW_REG_BUF - ret, "%#.4x: ", offset);
		hex_dump_to_buffer(d->fw_पढ़ो_buff + offset, 16, 16, 4,
				   पंचांगp + ret, FW_REG_BUF - ret, 0);
		ret += म_माप(पंचांगp + ret);

		/* prपूर्णांक newline क्रम each offset */
		अगर (FW_REG_BUF - ret > 0)
			पंचांगp[ret++] = '\n';
	पूर्ण

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, पंचांगp, ret);
	kमुक्त(पंचांगp);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations soft_regs_ctrl_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = fw_softreg_पढ़ो,
	.llseek = शेष_llseek,
पूर्ण;

काष्ठा skl_debug *skl_debugfs_init(काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_debug *d;

	d = devm_kzalloc(&skl->pci->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस शून्य;

	/* create the debugfs dir with platक्रमm component's debugfs as parent */
	d->fs = debugfs_create_dir("dsp", skl->component->debugfs_root);

	d->skl = skl;
	d->dev = &skl->pci->dev;

	/* now create the module dir */
	d->modules = debugfs_create_dir("modules", d->fs);

	debugfs_create_file("fw_soft_regs_rd", 0444, d->fs, d,
			    &soft_regs_ctrl_fops);

	वापस d;
पूर्ण

व्योम skl_debugfs_निकास(काष्ठा skl_dev *skl)
अणु
	काष्ठा skl_debug *d = skl->debugfs;

	debugfs_हटाओ_recursive(d->fs);

	d = शून्य;
पूर्ण
