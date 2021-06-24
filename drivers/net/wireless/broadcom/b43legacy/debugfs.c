<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  debugfs driver debugging code

  Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>


*/

#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#समावेश "b43legacy.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "dma.h"
#समावेश "pio.h"
#समावेश "xmit.h"


/* The root directory. */
अटल काष्ठा dentry *rootdir;

काष्ठा b43legacy_debugfs_fops अणु
	sमाप_प्रकार (*पढ़ो)(काष्ठा b43legacy_wldev *dev, अक्षर *buf, माप_प्रकार bufsize);
	पूर्णांक (*ग_लिखो)(काष्ठा b43legacy_wldev *dev, स्थिर अक्षर *buf, माप_प्रकार count);
	काष्ठा file_operations fops;
	/* Offset of काष्ठा b43legacy_dfs_file in काष्ठा b43legacy_dfsentry */
	माप_प्रकार file_काष्ठा_offset;
	/* Take wl->irq_lock beक्रमe calling पढ़ो/ग_लिखो? */
	bool take_irqlock;
पूर्ण;

अटल अंतरभूत
काष्ठा b43legacy_dfs_file * fops_to_dfs_file(काष्ठा b43legacy_wldev *dev,
				       स्थिर काष्ठा b43legacy_debugfs_fops *dfops)
अणु
	व्योम *p;

	p = dev->dfsentry;
	p += dfops->file_काष्ठा_offset;

	वापस p;
पूर्ण


#घोषणा fappend(fmt, x...)	\
	करो अणु							\
		अगर (bufsize - count)				\
			count += scnम_लिखो(buf + count,		\
					  bufsize - count,	\
					  fmt , ##x);		\
		अन्यथा						\
			prपूर्णांकk(KERN_ERR "b43legacy: fappend overflow\n"); \
	पूर्ण जबतक (0)


/* wl->irq_lock is locked */
अटल sमाप_प्रकार tsf_पढ़ो_file(काष्ठा b43legacy_wldev *dev, अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	u64 tsf;

	b43legacy_tsf_पढ़ो(dev, &tsf);
	fappend("0x%08x%08x\n",
		(अचिन्हित पूर्णांक)((tsf & 0xFFFFFFFF00000000ULL) >> 32),
		(अचिन्हित पूर्णांक)(tsf & 0xFFFFFFFFULL));

	वापस count;
पूर्ण

/* wl->irq_lock is locked */
अटल पूर्णांक tsf_ग_लिखो_file(काष्ठा b43legacy_wldev *dev, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	u64 tsf;

	अगर (माला_पूछो(buf, "%llu", (अचिन्हित दीर्घ दीर्घ *)(&tsf)) != 1)
		वापस -EINVAL;
	b43legacy_tsf_ग_लिखो(dev, tsf);

	वापस 0;
पूर्ण

/* wl->irq_lock is locked */
अटल sमाप_प्रकार ucode_regs_पढ़ो_file(काष्ठा b43legacy_wldev *dev, अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		fappend("r%d = 0x%04x\n", i,
			b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_WIRELESS, i));
	पूर्ण

	वापस count;
पूर्ण

/* wl->irq_lock is locked */
अटल sमाप_प्रकार shm_पढ़ो_file(काष्ठा b43legacy_wldev *dev, अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	पूर्णांक i;
	u16 पंचांगp;
	__le16 *le16buf = (__le16 *)buf;

	क्रम (i = 0; i < 0x1000; i++) अणु
		अगर (bufsize < माप(पंचांगp))
			अवरोध;
		पंचांगp = b43legacy_shm_पढ़ो16(dev, B43legacy_SHM_SHARED, 2 * i);
		le16buf[i] = cpu_to_le16(पंचांगp);
		count += माप(पंचांगp);
		bufsize -= माप(पंचांगp);
	पूर्ण

	वापस count;
पूर्ण

अटल sमाप_प्रकार txstat_पढ़ो_file(काष्ठा b43legacy_wldev *dev, अक्षर *buf, माप_प्रकार bufsize)
अणु
	काष्ठा b43legacy_txstatus_log *log = &dev->dfsentry->txstatlog;
	sमाप_प्रकार count = 0;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, idx;
	काष्ठा b43legacy_txstatus *stat;

	spin_lock_irqsave(&log->lock, flags);
	अगर (log->end < 0) अणु
		fappend("Nothing transmitted, yet\n");
		जाओ out_unlock;
	पूर्ण
	fappend("b43legacy TX status reports:\n\n"
		"index | cookie | seq | phy_stat | frame_count | "
		"rts_count | supp_reason | pm_indicated | "
		"intermediate | for_ampdu | acked\n" "---\n");
	i = log->end + 1;
	idx = 0;
	जबतक (1) अणु
		अगर (i == B43legacy_NR_LOGGED_TXSTATUS)
			i = 0;
		stat = &(log->log[i]);
		अगर (stat->cookie) अणु
			fappend("%03d | "
				"0x%04X | 0x%04X | 0x%02X | "
				"0x%X | 0x%X | "
				"%u | %u | "
				"%u | %u | %u\n",
				idx,
				stat->cookie, stat->seq, stat->phy_stat,
				stat->frame_count, stat->rts_count,
				stat->supp_reason, stat->pm_indicated,
				stat->पूर्णांकermediate, stat->क्रम_ampdu,
				stat->acked);
			idx++;
		पूर्ण
		अगर (i == log->end)
			अवरोध;
		i++;
	पूर्ण
out_unlock:
	spin_unlock_irqrestore(&log->lock, flags);

	वापस count;
पूर्ण

/* wl->irq_lock is locked */
अटल पूर्णांक restart_ग_लिखो_file(काष्ठा b43legacy_wldev *dev, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err = 0;

	अगर (count > 0 && buf[0] == '1') अणु
		b43legacy_controller_restart(dev, "manually restarted");
	पूर्ण अन्यथा
		err = -EINVAL;

	वापस err;
पूर्ण

#अघोषित fappend

अटल sमाप_प्रकार b43legacy_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा b43legacy_wldev *dev;
	काष्ठा b43legacy_debugfs_fops *dfops;
	काष्ठा b43legacy_dfs_file *dfile;
	sमाप_प्रकार ret;
	अक्षर *buf;
	स्थिर माप_प्रकार bufsize = 1024 * 16; /* 16 KiB buffer */
	स्थिर माप_प्रकार buक्रमder = get_order(bufsize);
	पूर्णांक err = 0;

	अगर (!count)
		वापस 0;
	dev = file->निजी_data;
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->wl->mutex);
	अगर (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा b43legacy_debugfs_fops, fops);
	अगर (!dfops->पढ़ो) अणु
		err = -ENOSYS;
		जाओ out_unlock;
	पूर्ण
	dfile = fops_to_dfs_file(dev, dfops);

	अगर (!dfile->buffer) अणु
		buf = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL, buक्रमder);
		अगर (!buf) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		स_रखो(buf, 0, bufsize);
		अगर (dfops->take_irqlock) अणु
			spin_lock_irq(&dev->wl->irq_lock);
			ret = dfops->पढ़ो(dev, buf, bufsize);
			spin_unlock_irq(&dev->wl->irq_lock);
		पूर्ण अन्यथा
			ret = dfops->पढ़ो(dev, buf, bufsize);
		अगर (ret <= 0) अणु
			मुक्त_pages((अचिन्हित दीर्घ)buf, buक्रमder);
			err = ret;
			जाओ out_unlock;
		पूर्ण
		dfile->data_len = ret;
		dfile->buffer = buf;
	पूर्ण

	ret = simple_पढ़ो_from_buffer(userbuf, count, ppos,
				      dfile->buffer,
				      dfile->data_len);
	अगर (*ppos >= dfile->data_len) अणु
		मुक्त_pages((अचिन्हित दीर्घ)dfile->buffer, buक्रमder);
		dfile->buffer = शून्य;
		dfile->data_len = 0;
	पूर्ण
out_unlock:
	mutex_unlock(&dev->wl->mutex);

	वापस err ? err : ret;
पूर्ण

अटल sमाप_प्रकार b43legacy_debugfs_ग_लिखो(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा b43legacy_wldev *dev;
	काष्ठा b43legacy_debugfs_fops *dfops;
	अक्षर *buf;
	पूर्णांक err = 0;

	अगर (!count)
		वापस 0;
	अगर (count > PAGE_SIZE)
		वापस -E2BIG;
	dev = file->निजी_data;
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->wl->mutex);
	अगर (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा b43legacy_debugfs_fops, fops);
	अगर (!dfops->ग_लिखो) अणु
		err = -ENOSYS;
		जाओ out_unlock;
	पूर्ण

	buf = (अक्षर *)get_zeroed_page(GFP_KERNEL);
	अगर (!buf) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	अगर (copy_from_user(buf, userbuf, count)) अणु
		err = -EFAULT;
		जाओ out_मुक्तpage;
	पूर्ण
	अगर (dfops->take_irqlock) अणु
		spin_lock_irq(&dev->wl->irq_lock);
		err = dfops->ग_लिखो(dev, buf, count);
		spin_unlock_irq(&dev->wl->irq_lock);
	पूर्ण अन्यथा
		err = dfops->ग_लिखो(dev, buf, count);
	अगर (err)
		जाओ out_मुक्तpage;

out_मुक्तpage:
	मुक्त_page((अचिन्हित दीर्घ)buf);
out_unlock:
	mutex_unlock(&dev->wl->mutex);

	वापस err ? err : count;
पूर्ण


#घोषणा B43legacy_DEBUGFS_FOPS(name, _पढ़ो, _ग_लिखो, _take_irqlock)	\
	अटल काष्ठा b43legacy_debugfs_fops fops_##name = अणु		\
		.पढ़ो	= _पढ़ो,				\
		.ग_लिखो	= _ग_लिखो,				\
		.fops	= अणु					\
			.खोलो	= simple_खोलो,				\
			.पढ़ो	= b43legacy_debugfs_पढ़ो,		\
			.ग_लिखो	= b43legacy_debugfs_ग_लिखो,		\
			.llseek = generic_file_llseek,			\
		पूर्ण,						\
		.file_काष्ठा_offset = दुरत्व(काष्ठा b43legacy_dfsentry, \
					       file_##name),	\
		.take_irqlock	= _take_irqlock,		\
	पूर्ण

B43legacy_DEBUGFS_FOPS(tsf, tsf_पढ़ो_file, tsf_ग_लिखो_file, 1);
B43legacy_DEBUGFS_FOPS(ucode_regs, ucode_regs_पढ़ो_file, शून्य, 1);
B43legacy_DEBUGFS_FOPS(shm, shm_पढ़ो_file, शून्य, 1);
B43legacy_DEBUGFS_FOPS(txstat, txstat_पढ़ो_file, शून्य, 0);
B43legacy_DEBUGFS_FOPS(restart, शून्य, restart_ग_लिखो_file, 1);


पूर्णांक b43legacy_debug(काष्ठा b43legacy_wldev *dev, क्रमागत b43legacy_dyndbg feature)
अणु
	वापस !!(dev->dfsentry && dev->dfsentry->dyn_debug[feature]);
पूर्ण

अटल व्योम b43legacy_हटाओ_dynamic_debug(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dfsentry *e = dev->dfsentry;
	पूर्णांक i;

	क्रम (i = 0; i < __B43legacy_NR_DYNDBG; i++)
		debugfs_हटाओ(e->dyn_debug_dentries[i]);
पूर्ण

अटल व्योम b43legacy_add_dynamic_debug(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dfsentry *e = dev->dfsentry;

#घोषणा add_dyn_dbg(name, id, initstate) करो अणु			\
	e->dyn_debug[id] = (initstate);				\
	e->dyn_debug_dentries[id] =				\
		debugfs_create_bool(name, 0600, e->subdir,	\
				&(e->dyn_debug[id]));		\
	पूर्ण जबतक (0)

	add_dyn_dbg("debug_xmitpower", B43legacy_DBG_XMITPOWER, false);
	add_dyn_dbg("debug_dmaoverflow", B43legacy_DBG_DMAOVERFLOW, false);
	add_dyn_dbg("debug_dmaverbose", B43legacy_DBG_DMAVERBOSE, false);
	add_dyn_dbg("debug_pwork_fast", B43legacy_DBG_PWORK_FAST, false);
	add_dyn_dbg("debug_pwork_stop", B43legacy_DBG_PWORK_STOP, false);

#अघोषित add_dyn_dbg
पूर्ण

व्योम b43legacy_debugfs_add_device(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dfsentry *e;
	काष्ठा b43legacy_txstatus_log *log;
	अक्षर devdir[16];

	B43legacy_WARN_ON(!dev);
	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e) अणु
		b43legacyerr(dev->wl, "debugfs: add device OOM\n");
		वापस;
	पूर्ण
	e->dev = dev;
	log = &e->txstatlog;
	log->log = kसुस्मृति(B43legacy_NR_LOGGED_TXSTATUS,
			   माप(काष्ठा b43legacy_txstatus), GFP_KERNEL);
	अगर (!log->log) अणु
		b43legacyerr(dev->wl, "debugfs: add device txstatus OOM\n");
		kमुक्त(e);
		वापस;
	पूर्ण
	log->end = -1;
	spin_lock_init(&log->lock);

	dev->dfsentry = e;

	snम_लिखो(devdir, माप(devdir), "%s", wiphy_name(dev->wl->hw->wiphy));
	e->subdir = debugfs_create_dir(devdir, rootdir);

#घोषणा ADD_खाता(name, mode)	\
	करो अणु							\
		e->file_##name.dentry =				\
			debugfs_create_file(__stringअगरy(name),	\
					mode, e->subdir, dev,	\
					&fops_##name.fops);	\
		e->file_##name.dentry = शून्य;			\
	पूर्ण जबतक (0)


	ADD_खाता(tsf, 0600);
	ADD_खाता(ucode_regs, 0400);
	ADD_खाता(shm, 0400);
	ADD_खाता(txstat, 0400);
	ADD_खाता(restart, 0200);

#अघोषित ADD_खाता

	b43legacy_add_dynamic_debug(dev);
पूर्ण

व्योम b43legacy_debugfs_हटाओ_device(काष्ठा b43legacy_wldev *dev)
अणु
	काष्ठा b43legacy_dfsentry *e;

	अगर (!dev)
		वापस;
	e = dev->dfsentry;
	अगर (!e)
		वापस;
	b43legacy_हटाओ_dynamic_debug(dev);

	debugfs_हटाओ(e->file_tsf.dentry);
	debugfs_हटाओ(e->file_ucode_regs.dentry);
	debugfs_हटाओ(e->file_shm.dentry);
	debugfs_हटाओ(e->file_txstat.dentry);
	debugfs_हटाओ(e->file_restart.dentry);

	debugfs_हटाओ(e->subdir);
	kमुक्त(e->txstatlog.log);
	kमुक्त(e);
पूर्ण

व्योम b43legacy_debugfs_log_txstat(काष्ठा b43legacy_wldev *dev,
			    स्थिर काष्ठा b43legacy_txstatus *status)
अणु
	काष्ठा b43legacy_dfsentry *e = dev->dfsentry;
	काष्ठा b43legacy_txstatus_log *log;
	काष्ठा b43legacy_txstatus *cur;
	पूर्णांक i;

	अगर (!e)
		वापस;
	log = &e->txstatlog;
	B43legacy_WARN_ON(!irqs_disabled());
	spin_lock(&log->lock);
	i = log->end + 1;
	अगर (i == B43legacy_NR_LOGGED_TXSTATUS)
		i = 0;
	log->end = i;
	cur = &(log->log[i]);
	स_नकल(cur, status, माप(*cur));
	spin_unlock(&log->lock);
पूर्ण

व्योम b43legacy_debugfs_init(व्योम)
अणु
	rootdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);
पूर्ण

व्योम b43legacy_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ(rootdir);
पूर्ण
