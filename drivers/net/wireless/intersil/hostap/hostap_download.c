<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
अटल पूर्णांक prism2_enable_aux_port(काष्ठा net_device *dev, पूर्णांक enable)
अणु
	u16 val, reg;
	पूर्णांक i, tries;
	अचिन्हित दीर्घ flags;
	काष्ठा hostap_पूर्णांकerface *अगरace;
	local_info_t *local;

	अगरace = netdev_priv(dev);
	local = अगरace->local;

	अगर (local->no_pri) अणु
		अगर (enable) अणु
			PDEBUG(DEBUG_EXTRA2, "%s: no PRI f/w - assuming Aux "
			       "port is already enabled\n", dev->name);
		पूर्ण
		वापस 0;
	पूर्ण

	spin_lock_irqsave(&local->cmdlock, flags);

	/* रुको until busy bit is clear */
	tries = HFA384X_CMD_BUSY_TIMEOUT;
	जबतक (HFA384X_INW(HFA384X_CMD_OFF) & HFA384X_CMD_BUSY && tries > 0) अणु
		tries--;
		udelay(1);
	पूर्ण
	अगर (tries == 0) अणु
		reg = HFA384X_INW(HFA384X_CMD_OFF);
		spin_unlock_irqrestore(&local->cmdlock, flags);
		prपूर्णांकk("%s: prism2_enable_aux_port - timeout - reg=0x%04x\n",
		       dev->name, reg);
		वापस -ETIMEDOUT;
	पूर्ण

	val = HFA384X_INW(HFA384X_CONTROL_OFF);

	अगर (enable) अणु
		HFA384X_OUTW(HFA384X_AUX_MAGIC0, HFA384X_PARAM0_OFF);
		HFA384X_OUTW(HFA384X_AUX_MAGIC1, HFA384X_PARAM1_OFF);
		HFA384X_OUTW(HFA384X_AUX_MAGIC2, HFA384X_PARAM2_OFF);

		अगर ((val & HFA384X_AUX_PORT_MASK) != HFA384X_AUX_PORT_DISABLED)
			prपूर्णांकk("prism2_enable_aux_port: was not disabled!?\n");
		val &= ~HFA384X_AUX_PORT_MASK;
		val |= HFA384X_AUX_PORT_ENABLE;
	पूर्ण अन्यथा अणु
		HFA384X_OUTW(0, HFA384X_PARAM0_OFF);
		HFA384X_OUTW(0, HFA384X_PARAM1_OFF);
		HFA384X_OUTW(0, HFA384X_PARAM2_OFF);

		अगर ((val & HFA384X_AUX_PORT_MASK) != HFA384X_AUX_PORT_ENABLED)
			prपूर्णांकk("prism2_enable_aux_port: was not enabled!?\n");
		val &= ~HFA384X_AUX_PORT_MASK;
		val |= HFA384X_AUX_PORT_DISABLE;
	पूर्ण
	HFA384X_OUTW(val, HFA384X_CONTROL_OFF);

	udelay(5);

	i = 10000;
	जबतक (i > 0) अणु
		val = HFA384X_INW(HFA384X_CONTROL_OFF);
		val &= HFA384X_AUX_PORT_MASK;

		अगर ((enable && val == HFA384X_AUX_PORT_ENABLED) ||
		    (!enable && val == HFA384X_AUX_PORT_DISABLED))
			अवरोध;

		udelay(10);
		i--;
	पूर्ण

	spin_unlock_irqrestore(&local->cmdlock, flags);

	अगर (i == 0) अणु
		prपूर्णांकk("prism2_enable_aux_port(%d) timed out\n",
		       enable);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक hfa384x_from_aux(काष्ठा net_device *dev, अचिन्हित पूर्णांक addr, पूर्णांक len,
			    व्योम *buf)
अणु
	u16 page, offset;
	अगर (addr & 1 || len & 1)
		वापस -1;

	page = addr >> 7;
	offset = addr & 0x7f;

	HFA384X_OUTW(page, HFA384X_AUXPAGE_OFF);
	HFA384X_OUTW(offset, HFA384X_AUXOFFSET_OFF);

	udelay(5);

#अगर_घोषित PRISM2_PCI
	अणु
		__le16 *pos = (__le16 *) buf;
		जबतक (len > 0) अणु
			*pos++ = HFA384X_INW_DATA(HFA384X_AUXDATA_OFF);
			len -= 2;
		पूर्ण
	पूर्ण
#अन्यथा /* PRISM2_PCI */
	HFA384X_INSW(HFA384X_AUXDATA_OFF, buf, len / 2);
#पूर्ण_अगर /* PRISM2_PCI */

	वापस 0;
पूर्ण


अटल पूर्णांक hfa384x_to_aux(काष्ठा net_device *dev, अचिन्हित पूर्णांक addr, पूर्णांक len,
			  व्योम *buf)
अणु
	u16 page, offset;
	अगर (addr & 1 || len & 1)
		वापस -1;

	page = addr >> 7;
	offset = addr & 0x7f;

	HFA384X_OUTW(page, HFA384X_AUXPAGE_OFF);
	HFA384X_OUTW(offset, HFA384X_AUXOFFSET_OFF);

	udelay(5);

#अगर_घोषित PRISM2_PCI
	अणु
		__le16 *pos = (__le16 *) buf;
		जबतक (len > 0) अणु
			HFA384X_OUTW_DATA(*pos++, HFA384X_AUXDATA_OFF);
			len -= 2;
		पूर्ण
	पूर्ण
#अन्यथा /* PRISM2_PCI */
	HFA384X_OUTSW(HFA384X_AUXDATA_OFF, buf, len / 2);
#पूर्ण_अगर /* PRISM2_PCI */

	वापस 0;
पूर्ण


अटल पूर्णांक prism2_pda_ok(u8 *buf)
अणु
	__le16 *pda = (__le16 *) buf;
	पूर्णांक pos;
	u16 len, pdr;

	अगर (buf[0] == 0xff && buf[1] == 0x00 && buf[2] == 0xff &&
	    buf[3] == 0x00)
		वापस 0;

	pos = 0;
	जबतक (pos + 1 < PRISM2_PDA_SIZE / 2) अणु
		len = le16_to_cpu(pda[pos]);
		pdr = le16_to_cpu(pda[pos + 1]);
		अगर (len == 0 || pos + len > PRISM2_PDA_SIZE / 2)
			वापस 0;

		अगर (pdr == 0x0000 && len == 2) अणु
			/* PDA end found */
			वापस 1;
		पूर्ण

		pos += len + 1;
	पूर्ण

	वापस 0;
पूर्ण


#घोषणा prism2_करोwnload_aux_dump_npages 65536

काष्ठा prism2_करोwnload_aux_dump अणु
	local_info_t *local;
	u16 page[0x80];
पूर्ण;

अटल पूर्णांक prism2_करोwnload_aux_dump_proc_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा prism2_करोwnload_aux_dump *ctx = m->निजी;

	hfa384x_from_aux(ctx->local->dev, (अचिन्हित दीर्घ)v - 1, 0x80, ctx->page);
	seq_ग_लिखो(m, ctx->page, 0x80);
	वापस 0;
पूर्ण

अटल व्योम *prism2_करोwnload_aux_dump_proc_start(काष्ठा seq_file *m, loff_t *_pos)
अणु
	काष्ठा prism2_करोwnload_aux_dump *ctx = m->निजी;
	prism2_enable_aux_port(ctx->local->dev, 1);
	अगर (*_pos >= prism2_करोwnload_aux_dump_npages)
		वापस शून्य;
	वापस (व्योम *)((अचिन्हित दीर्घ)*_pos + 1);
पूर्ण

अटल व्योम *prism2_करोwnload_aux_dump_proc_next(काष्ठा seq_file *m, व्योम *v, loff_t *_pos)
अणु
	++*_pos;
	अगर (*_pos >= prism2_करोwnload_aux_dump_npages)
		वापस शून्य;
	वापस (व्योम *)((अचिन्हित दीर्घ)*_pos + 1);
पूर्ण

अटल व्योम prism2_करोwnload_aux_dump_proc_stop(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा prism2_करोwnload_aux_dump *ctx = m->निजी;
	prism2_enable_aux_port(ctx->local->dev, 0);
पूर्ण

अटल स्थिर काष्ठा seq_operations prism2_करोwnload_aux_dump_proc_seqops = अणु
	.start	= prism2_करोwnload_aux_dump_proc_start,
	.next	= prism2_करोwnload_aux_dump_proc_next,
	.stop	= prism2_करोwnload_aux_dump_proc_stop,
	.show	= prism2_करोwnload_aux_dump_proc_show,
पूर्ण;

अटल पूर्णांक prism2_करोwnload_aux_dump_proc_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक ret = seq_खोलो_निजी(file, &prism2_करोwnload_aux_dump_proc_seqops,
				   माप(काष्ठा prism2_करोwnload_aux_dump));
	अगर (ret == 0) अणु
		काष्ठा seq_file *m = file->निजी_data;
		m->निजी = PDE_DATA(inode);
	पूर्ण
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा proc_ops prism2_करोwnload_aux_dump_proc_ops = अणु
	.proc_खोलो		= prism2_करोwnload_aux_dump_proc_खोलो,
	.proc_पढ़ो		= seq_पढ़ो,
	.proc_lseek		= seq_lseek,
	.proc_release		= seq_release_निजी,
पूर्ण;


अटल u8 * prism2_पढ़ो_pda(काष्ठा net_device *dev)
अणु
	u8 *buf;
	पूर्णांक res, i, found = 0;
#घोषणा NUM_PDA_ADDRS 4
	अचिन्हित पूर्णांक pda_addr[NUM_PDA_ADDRS] = अणु
		0x7f0000 /* others than HFA3841 */,
		0x3f0000 /* HFA3841 */,
		0x390000 /* apparently used in older cards */,
		0x7f0002 /* Intel PRO/Wireless 2011B (PCI) */,
	पूर्ण;

	buf = kदो_स्मृति(PRISM2_PDA_SIZE, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस शून्य;

	/* Note: wlan card should be in initial state (just after init cmd)
	 * and no other operations should be perक्रमmed concurrently. */

	prism2_enable_aux_port(dev, 1);

	क्रम (i = 0; i < NUM_PDA_ADDRS; i++) अणु
		PDEBUG(DEBUG_EXTRA2, "%s: trying to read PDA from 0x%08x",
		       dev->name, pda_addr[i]);
		res = hfa384x_from_aux(dev, pda_addr[i], PRISM2_PDA_SIZE, buf);
		अगर (res)
			जारी;
		अगर (res == 0 && prism2_pda_ok(buf)) अणु
			PDEBUG2(DEBUG_EXTRA2, ": OK\n");
			found = 1;
			अवरोध;
		पूर्ण अन्यथा अणु
			PDEBUG2(DEBUG_EXTRA2, ": failed\n");
		पूर्ण
	पूर्ण

	prism2_enable_aux_port(dev, 0);

	अगर (!found) अणु
		prपूर्णांकk(KERN_DEBUG "%s: valid PDA not found\n", dev->name);
		kमुक्त(buf);
		buf = शून्य;
	पूर्ण

	वापस buf;
पूर्ण


अटल पूर्णांक prism2_करोwnload_अस्थिर(local_info_t *local,
				    काष्ठा prism2_करोwnload_data *param)
अणु
	काष्ठा net_device *dev = local->dev;
	पूर्णांक ret = 0, i;
	u16 param0, param1;

	अगर (local->hw_करोwnloading) अणु
		prपूर्णांकk(KERN_WARNING "%s: Already downloading - aborting new "
		       "request\n", dev->name);
		वापस -1;
	पूर्ण

	local->hw_करोwnloading = 1;
	अगर (local->pri_only) अणु
		hfa384x_disable_पूर्णांकerrupts(dev);
	पूर्ण अन्यथा अणु
		prism2_hw_shutकरोwn(dev, 0);

		अगर (prism2_hw_init(dev, 0)) अणु
			prपूर्णांकk(KERN_WARNING "%s: Could not initialize card for"
			       " download\n", dev->name);
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (prism2_enable_aux_port(dev, 1)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Could not enable AUX port\n",
		       dev->name);
		ret = -1;
		जाओ out;
	पूर्ण

	param0 = param->start_addr & 0xffff;
	param1 = param->start_addr >> 16;

	HFA384X_OUTW(0, HFA384X_PARAM2_OFF);
	HFA384X_OUTW(param1, HFA384X_PARAM1_OFF);
	अगर (hfa384x_cmd_रुको(dev, HFA384X_CMDCODE_DOWNLOAD |
			     (HFA384X_PROGMODE_ENABLE_VOLATILE << 8),
			     param0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Download command execution failed\n",
		       dev->name);
		ret = -1;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < param->num_areas; i++) अणु
		PDEBUG(DEBUG_EXTRA2, "%s: Writing %d bytes at 0x%08x\n",
		       dev->name, param->data[i].len, param->data[i].addr);
		अगर (hfa384x_to_aux(dev, param->data[i].addr,
				   param->data[i].len, param->data[i].data)) अणु
			prपूर्णांकk(KERN_WARNING "%s: RAM download at 0x%08x "
			       "(len=%d) failed\n", dev->name,
			       param->data[i].addr, param->data[i].len);
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	HFA384X_OUTW(param1, HFA384X_PARAM1_OFF);
	HFA384X_OUTW(0, HFA384X_PARAM2_OFF);
	अगर (hfa384x_cmd_no_रुको(dev, HFA384X_CMDCODE_DOWNLOAD |
				(HFA384X_PROGMODE_DISABLE << 8), param0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Download command execution failed\n",
		       dev->name);
		ret = -1;
		जाओ out;
	पूर्ण
	/* ProgMode disable causes the hardware to restart itself from the
	 * given starting address. Give hw some समय and ACK command just in
	 * हाल restart did not happen. */
	mdelay(5);
	HFA384X_OUTW(HFA384X_EV_CMD, HFA384X_EVACK_OFF);

	अगर (prism2_enable_aux_port(dev, 0)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Disabling AUX port failed\n",
		       dev->name);
		/* जारी anyway.. restart should have taken care of this */
	पूर्ण

	mdelay(5);
	local->hw_करोwnloading = 0;
	अगर (prism2_hw_config(dev, 2)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Card configuration after RAM "
		       "download failed\n", dev->name);
		ret = -1;
		जाओ out;
	पूर्ण

 out:
	local->hw_करोwnloading = 0;
	वापस ret;
पूर्ण


अटल पूर्णांक prism2_enable_genesis(local_info_t *local, पूर्णांक hcr)
अणु
	काष्ठा net_device *dev = local->dev;
	u8 initseq[4] = अणु 0x00, 0xe1, 0xa1, 0xff पूर्ण;
	u8 पढ़ोbuf[4];

	prपूर्णांकk(KERN_DEBUG "%s: test Genesis mode with HCR 0x%02x\n",
	       dev->name, hcr);
	local->func->cor_sreset(local);
	hfa384x_to_aux(dev, 0x7e0038, माप(initseq), initseq);
	local->func->genesis_reset(local, hcr);

	/* Readback test */
	hfa384x_from_aux(dev, 0x7e0038, माप(पढ़ोbuf), पढ़ोbuf);
	hfa384x_to_aux(dev, 0x7e0038, माप(initseq), initseq);
	hfa384x_from_aux(dev, 0x7e0038, माप(पढ़ोbuf), पढ़ोbuf);

	अगर (स_भेद(initseq, पढ़ोbuf, माप(initseq)) == 0) अणु
		prपूर्णांकk(KERN_DEBUG "Readback test succeeded, HCR 0x%02x\n",
		       hcr);
		वापस 0;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_DEBUG "Readback test failed, HCR 0x%02x write %4ph read %4ph\n",
		       hcr, initseq, पढ़ोbuf);
		वापस 1;
	पूर्ण
पूर्ण


अटल पूर्णांक prism2_get_ram_size(local_info_t *local)
अणु
	पूर्णांक ret;

	/* Try to enable genesis mode; 0x1F क्रम x8 SRAM or 0x0F क्रम x16 SRAM */
	अगर (prism2_enable_genesis(local, 0x1f) == 0)
		ret = 8;
	अन्यथा अगर (prism2_enable_genesis(local, 0x0f) == 0)
		ret = 16;
	अन्यथा
		ret = -1;

	/* Disable genesis mode */
	local->func->genesis_reset(local, ret == 16 ? 0x07 : 0x17);

	वापस ret;
पूर्ण


अटल पूर्णांक prism2_करोwnload_genesis(local_info_t *local,
				   काष्ठा prism2_करोwnload_data *param)
अणु
	काष्ठा net_device *dev = local->dev;
	पूर्णांक ram16 = 0, i;
	पूर्णांक ret = 0;

	अगर (local->hw_करोwnloading) अणु
		prपूर्णांकk(KERN_WARNING "%s: Already downloading - aborting new "
		       "request\n", dev->name);
		वापस -EBUSY;
	पूर्ण

	अगर (!local->func->genesis_reset || !local->func->cor_sreset) अणु
		prपूर्णांकk(KERN_INFO "%s: Genesis mode downloading not supported "
		       "with this hwmodel\n", dev->name);
		वापस -EOPNOTSUPP;
	पूर्ण

	local->hw_करोwnloading = 1;

	अगर (prism2_enable_aux_port(dev, 1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: failed to enable AUX port\n",
		       dev->name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (local->sram_type == -1) अणु
		/* 0x1F क्रम x8 SRAM or 0x0F क्रम x16 SRAM */
		अगर (prism2_enable_genesis(local, 0x1f) == 0) अणु
			ram16 = 0;
			PDEBUG(DEBUG_EXTRA2, "%s: Genesis mode OK using x8 "
			       "SRAM\n", dev->name);
		पूर्ण अन्यथा अगर (prism2_enable_genesis(local, 0x0f) == 0) अणु
			ram16 = 1;
			PDEBUG(DEBUG_EXTRA2, "%s: Genesis mode OK using x16 "
			       "SRAM\n", dev->name);
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_DEBUG "%s: Could not initiate genesis "
			       "mode\n", dev->name);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (prism2_enable_genesis(local, local->sram_type == 8 ?
					  0x1f : 0x0f)) अणु
			prपूर्णांकk(KERN_DEBUG "%s: Failed to set Genesis "
			       "mode (sram_type=%d)\n", dev->name,
			       local->sram_type);
			ret = -EIO;
			जाओ out;
		पूर्ण
		ram16 = local->sram_type != 8;
	पूर्ण

	क्रम (i = 0; i < param->num_areas; i++) अणु
		PDEBUG(DEBUG_EXTRA2, "%s: Writing %d bytes at 0x%08x\n",
		       dev->name, param->data[i].len, param->data[i].addr);
		अगर (hfa384x_to_aux(dev, param->data[i].addr,
				   param->data[i].len, param->data[i].data)) अणु
			prपूर्णांकk(KERN_WARNING "%s: RAM download at 0x%08x "
			       "(len=%d) failed\n", dev->name,
			       param->data[i].addr, param->data[i].len);
			ret = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	PDEBUG(DEBUG_EXTRA2, "Disable genesis mode\n");
	local->func->genesis_reset(local, ram16 ? 0x07 : 0x17);
	अगर (prism2_enable_aux_port(dev, 0)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Failed to disable AUX port\n",
		       dev->name);
	पूर्ण

	mdelay(5);
	local->hw_करोwnloading = 0;

	PDEBUG(DEBUG_EXTRA2, "Trying to initialize card\n");
	/*
	 * Make sure the INIT command करोes not generate a command completion
	 * event by disabling पूर्णांकerrupts.
	 */
	hfa384x_disable_पूर्णांकerrupts(dev);
	अगर (prism2_hw_init(dev, 1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Initialization after genesis mode "
		       "download failed\n", dev->name);
		ret = -EIO;
		जाओ out;
	पूर्ण

	PDEBUG(DEBUG_EXTRA2, "Card initialized - running PRI only\n");
	अगर (prism2_hw_init2(dev, 1)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Initialization(2) after genesis mode "
		       "download failed\n", dev->name);
		ret = -EIO;
		जाओ out;
	पूर्ण

 out:
	local->hw_करोwnloading = 0;
	वापस ret;
पूर्ण


#अगर_घोषित PRISM2_NON_VOLATILE_DOWNLOAD
/* Note! Non-अस्थिर करोwnloading functionality has not yet been tested
 * thoroughly and it may corrupt flash image and effectively समाप्त the card that
 * is being updated. You have been warned. */

अटल अंतरभूत पूर्णांक prism2_करोwnload_block(काष्ठा net_device *dev,
					u32 addr, u8 *data,
					u32 bufaddr, पूर्णांक rest_len)
अणु
	u16 param0, param1;
	पूर्णांक block_len;

	block_len = rest_len < 4096 ? rest_len : 4096;

	param0 = addr & 0xffff;
	param1 = addr >> 16;

	HFA384X_OUTW(block_len, HFA384X_PARAM2_OFF);
	HFA384X_OUTW(param1, HFA384X_PARAM1_OFF);

	अगर (hfa384x_cmd_रुको(dev, HFA384X_CMDCODE_DOWNLOAD |
			     (HFA384X_PROGMODE_ENABLE_NON_VOLATILE << 8),
			     param0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Flash download command execution "
		       "failed\n", dev->name);
		वापस -1;
	पूर्ण

	अगर (hfa384x_to_aux(dev, bufaddr, block_len, data)) अणु
		prपूर्णांकk(KERN_WARNING "%s: flash download at 0x%08x "
		       "(len=%d) failed\n", dev->name, addr, block_len);
		वापस -1;
	पूर्ण

	HFA384X_OUTW(0, HFA384X_PARAM2_OFF);
	HFA384X_OUTW(0, HFA384X_PARAM1_OFF);
	अगर (hfa384x_cmd_रुको(dev, HFA384X_CMDCODE_DOWNLOAD |
			     (HFA384X_PROGMODE_PROGRAM_NON_VOLATILE << 8),
			     0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Flash write command execution "
		       "failed\n", dev->name);
		वापस -1;
	पूर्ण

	वापस block_len;
पूर्ण


अटल पूर्णांक prism2_करोwnload_nonअस्थिर(local_info_t *local,
				       काष्ठा prism2_करोwnload_data *dl)
अणु
	काष्ठा net_device *dev = local->dev;
	पूर्णांक ret = 0, i;
	काष्ठा अणु
		__le16 page;
		__le16 offset;
		__le16 len;
	पूर्ण dlbuffer;
	u32 bufaddr;

	अगर (local->hw_करोwnloading) अणु
		prपूर्णांकk(KERN_WARNING "%s: Already downloading - aborting new "
		       "request\n", dev->name);
		वापस -1;
	पूर्ण

	ret = local->func->get_rid(dev, HFA384X_RID_DOWNLOADBUFFER,
				   &dlbuffer, 6, 0);

	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_WARNING "%s: Could not read download buffer "
		       "parameters\n", dev->name);
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "Download buffer: %d bytes at 0x%04x:0x%04x\n",
	       le16_to_cpu(dlbuffer.len),
	       le16_to_cpu(dlbuffer.page),
	       le16_to_cpu(dlbuffer.offset));

	bufaddr = (le16_to_cpu(dlbuffer.page) << 7) + le16_to_cpu(dlbuffer.offset);

	local->hw_करोwnloading = 1;

	अगर (!local->pri_only) अणु
		prism2_hw_shutकरोwn(dev, 0);

		अगर (prism2_hw_init(dev, 0)) अणु
			prपूर्णांकk(KERN_WARNING "%s: Could not initialize card for"
			       " download\n", dev->name);
			ret = -1;
			जाओ out;
		पूर्ण
	पूर्ण

	hfa384x_disable_पूर्णांकerrupts(dev);

	अगर (prism2_enable_aux_port(dev, 1)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Could not enable AUX port\n",
		       dev->name);
		ret = -1;
		जाओ out;
	पूर्ण

	prपूर्णांकk(KERN_DEBUG "%s: starting flash download\n", dev->name);
	क्रम (i = 0; i < dl->num_areas; i++) अणु
		पूर्णांक rest_len = dl->data[i].len;
		पूर्णांक data_off = 0;

		जबतक (rest_len > 0) अणु
			पूर्णांक block_len;

			block_len = prism2_करोwnload_block(
				dev, dl->data[i].addr + data_off,
				dl->data[i].data + data_off, bufaddr,
				rest_len);

			अगर (block_len < 0) अणु
				ret = -1;
				जाओ out;
			पूर्ण

			rest_len -= block_len;
			data_off += block_len;
		पूर्ण
	पूर्ण

	HFA384X_OUTW(0, HFA384X_PARAM1_OFF);
	HFA384X_OUTW(0, HFA384X_PARAM2_OFF);
	अगर (hfa384x_cmd_रुको(dev, HFA384X_CMDCODE_DOWNLOAD |
				(HFA384X_PROGMODE_DISABLE << 8), 0)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Download command execution failed\n",
		       dev->name);
		ret = -1;
		जाओ out;
	पूर्ण

	अगर (prism2_enable_aux_port(dev, 0)) अणु
		prपूर्णांकk(KERN_DEBUG "%s: Disabling AUX port failed\n",
		       dev->name);
		/* जारी anyway.. restart should have taken care of this */
	पूर्ण

	mdelay(5);

	local->func->hw_reset(dev);
	local->hw_करोwnloading = 0;
	अगर (prism2_hw_config(dev, 2)) अणु
		prपूर्णांकk(KERN_WARNING "%s: Card configuration after flash "
		       "download failed\n", dev->name);
		ret = -1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_INFO "%s: Card initialized successfully after "
		       "flash download\n", dev->name);
	पूर्ण

 out:
	local->hw_करोwnloading = 0;
	वापस ret;
पूर्ण
#पूर्ण_अगर /* PRISM2_NON_VOLATILE_DOWNLOAD */


अटल व्योम prism2_करोwnload_मुक्त_data(काष्ठा prism2_करोwnload_data *dl)
अणु
	पूर्णांक i;

	अगर (dl == शून्य)
		वापस;

	क्रम (i = 0; i < dl->num_areas; i++)
		kमुक्त(dl->data[i].data);
	kमुक्त(dl);
पूर्ण


अटल पूर्णांक prism2_करोwnload(local_info_t *local,
			   काष्ठा prism2_करोwnload_param *param)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;
	u32 total_len = 0;
	काष्ठा prism2_करोwnload_data *dl = शून्य;

	prपूर्णांकk(KERN_DEBUG "prism2_download: dl_cmd=%d start_addr=0x%08x "
	       "num_areas=%d\n",
	       param->dl_cmd, param->start_addr, param->num_areas);

	अगर (param->num_areas > 100) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	dl = kzalloc(माप(*dl) + param->num_areas *
		     माप(काष्ठा prism2_करोwnload_data_area), GFP_KERNEL);
	अगर (dl == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	dl->dl_cmd = param->dl_cmd;
	dl->start_addr = param->start_addr;
	dl->num_areas = param->num_areas;
	क्रम (i = 0; i < param->num_areas; i++) अणु
		PDEBUG(DEBUG_EXTRA2,
		       "  area %d: addr=0x%08x len=%d ptr=0x%p\n",
		       i, param->data[i].addr, param->data[i].len,
		       param->data[i].ptr);

		dl->data[i].addr = param->data[i].addr;
		dl->data[i].len = param->data[i].len;

		total_len += param->data[i].len;
		अगर (param->data[i].len > PRISM2_MAX_DOWNLOAD_AREA_LEN ||
		    total_len > PRISM2_MAX_DOWNLOAD_LEN) अणु
			ret = -E2BIG;
			जाओ out;
		पूर्ण

		dl->data[i].data = kदो_स्मृति(dl->data[i].len, GFP_KERNEL);
		अगर (dl->data[i].data == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		अगर (copy_from_user(dl->data[i].data, param->data[i].ptr,
				   param->data[i].len)) अणु
			ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	चयन (param->dl_cmd) अणु
	हाल PRISM2_DOWNLOAD_VOLATILE:
	हाल PRISM2_DOWNLOAD_VOLATILE_PERSISTENT:
		ret = prism2_करोwnload_अस्थिर(local, dl);
		अवरोध;
	हाल PRISM2_DOWNLOAD_VOLATILE_GENESIS:
	हाल PRISM2_DOWNLOAD_VOLATILE_GENESIS_PERSISTENT:
		ret = prism2_करोwnload_genesis(local, dl);
		अवरोध;
	हाल PRISM2_DOWNLOAD_NON_VOLATILE:
#अगर_घोषित PRISM2_NON_VOLATILE_DOWNLOAD
		ret = prism2_करोwnload_nonअस्थिर(local, dl);
#अन्यथा /* PRISM2_NON_VOLATILE_DOWNLOAD */
		prपूर्णांकk(KERN_INFO "%s: non-volatile downloading not enabled\n",
		       local->dev->name);
		ret = -EOPNOTSUPP;
#पूर्ण_अगर /* PRISM2_NON_VOLATILE_DOWNLOAD */
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "%s: unsupported download command %d\n",
		       local->dev->name, param->dl_cmd);
		ret = -EINVAL;
		अवरोध;
	पूर्ण

 out:
	अगर (ret == 0 && dl &&
	    param->dl_cmd == PRISM2_DOWNLOAD_VOLATILE_GENESIS_PERSISTENT) अणु
		prism2_करोwnload_मुक्त_data(local->dl_pri);
		local->dl_pri = dl;
	पूर्ण अन्यथा अगर (ret == 0 && dl &&
		   param->dl_cmd == PRISM2_DOWNLOAD_VOLATILE_PERSISTENT) अणु
		prism2_करोwnload_मुक्त_data(local->dl_sec);
		local->dl_sec = dl;
	पूर्ण अन्यथा
		prism2_करोwnload_मुक्त_data(dl);

	वापस ret;
पूर्ण
