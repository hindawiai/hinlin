<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  debugfs driver debugging code

  Copyright (c) 2005-2007 Michael Buesch <m@bues.ch>


*/

#समावेश <linux/fs.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/mutex.h>

#समावेश "b43.h"
#समावेश "main.h"
#समावेश "debugfs.h"
#समावेश "dma.h"
#समावेश "xmit.h"


/* The root directory. */
अटल काष्ठा dentry *rootdir;

काष्ठा b43_debugfs_fops अणु
	sमाप_प्रकार (*पढ़ो)(काष्ठा b43_wldev *dev, अक्षर *buf, माप_प्रकार bufsize);
	पूर्णांक (*ग_लिखो)(काष्ठा b43_wldev *dev, स्थिर अक्षर *buf, माप_प्रकार count);
	काष्ठा file_operations fops;
	/* Offset of काष्ठा b43_dfs_file in काष्ठा b43_dfsentry */
	माप_प्रकार file_काष्ठा_offset;
पूर्ण;

अटल अंतरभूत
काष्ठा b43_dfs_file *fops_to_dfs_file(काष्ठा b43_wldev *dev,
				      स्थिर काष्ठा b43_debugfs_fops *dfops)
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
			prपूर्णांकk(KERN_ERR "b43: fappend overflow\n"); \
	पूर्ण जबतक (0)


/* The biggest address values क्रम SHM access from the debugfs files. */
#घोषणा B43_MAX_SHM_ROUTING	4
#घोषणा B43_MAX_SHM_ADDR	0xFFFF

अटल sमाप_प्रकार shm16पढ़ो__पढ़ो_file(काष्ठा b43_wldev *dev,
				    अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	अचिन्हित पूर्णांक routing, addr;
	u16 val;

	routing = dev->dfsentry->shm16पढ़ो_routing_next;
	addr = dev->dfsentry->shm16पढ़ो_addr_next;
	अगर ((routing > B43_MAX_SHM_ROUTING) ||
	    (addr > B43_MAX_SHM_ADDR))
		वापस -EDESTADDRREQ;

	val = b43_shm_पढ़ो16(dev, routing, addr);
	fappend("0x%04X\n", val);

	वापस count;
पूर्ण

अटल पूर्णांक shm16पढ़ो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक routing, addr;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X 0x%X", &routing, &addr);
	अगर (res != 2)
		वापस -EINVAL;
	अगर (routing > B43_MAX_SHM_ROUTING)
		वापस -EADDRNOTAVAIL;
	अगर (addr > B43_MAX_SHM_ADDR)
		वापस -EADDRNOTAVAIL;
	अगर (routing == B43_SHM_SHARED) अणु
		अगर ((addr % 2) != 0)
			वापस -EADDRNOTAVAIL;
	पूर्ण

	dev->dfsentry->shm16पढ़ो_routing_next = routing;
	dev->dfsentry->shm16पढ़ो_addr_next = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक shm16ग_लिखो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक routing, addr, mask, set;
	u16 val;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X 0x%X 0x%X 0x%X",
		     &routing, &addr, &mask, &set);
	अगर (res != 4)
		वापस -EINVAL;
	अगर (routing > B43_MAX_SHM_ROUTING)
		वापस -EADDRNOTAVAIL;
	अगर (addr > B43_MAX_SHM_ADDR)
		वापस -EADDRNOTAVAIL;
	अगर (routing == B43_SHM_SHARED) अणु
		अगर ((addr % 2) != 0)
			वापस -EADDRNOTAVAIL;
	पूर्ण
	अगर ((mask > 0xFFFF) || (set > 0xFFFF))
		वापस -E2BIG;

	अगर (mask == 0)
		val = 0;
	अन्यथा
		val = b43_shm_पढ़ो16(dev, routing, addr);
	val &= mask;
	val |= set;
	b43_shm_ग_लिखो16(dev, routing, addr, val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार shm32पढ़ो__पढ़ो_file(काष्ठा b43_wldev *dev,
				    अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	अचिन्हित पूर्णांक routing, addr;
	u32 val;

	routing = dev->dfsentry->shm32पढ़ो_routing_next;
	addr = dev->dfsentry->shm32पढ़ो_addr_next;
	अगर ((routing > B43_MAX_SHM_ROUTING) ||
	    (addr > B43_MAX_SHM_ADDR))
		वापस -EDESTADDRREQ;

	val = b43_shm_पढ़ो32(dev, routing, addr);
	fappend("0x%08X\n", val);

	वापस count;
पूर्ण

अटल पूर्णांक shm32पढ़ो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक routing, addr;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X 0x%X", &routing, &addr);
	अगर (res != 2)
		वापस -EINVAL;
	अगर (routing > B43_MAX_SHM_ROUTING)
		वापस -EADDRNOTAVAIL;
	अगर (addr > B43_MAX_SHM_ADDR)
		वापस -EADDRNOTAVAIL;
	अगर (routing == B43_SHM_SHARED) अणु
		अगर ((addr % 2) != 0)
			वापस -EADDRNOTAVAIL;
	पूर्ण

	dev->dfsentry->shm32पढ़ो_routing_next = routing;
	dev->dfsentry->shm32पढ़ो_addr_next = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक shm32ग_लिखो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक routing, addr, mask, set;
	u32 val;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X 0x%X 0x%X 0x%X",
		     &routing, &addr, &mask, &set);
	अगर (res != 4)
		वापस -EINVAL;
	अगर (routing > B43_MAX_SHM_ROUTING)
		वापस -EADDRNOTAVAIL;
	अगर (addr > B43_MAX_SHM_ADDR)
		वापस -EADDRNOTAVAIL;
	अगर (routing == B43_SHM_SHARED) अणु
		अगर ((addr % 2) != 0)
			वापस -EADDRNOTAVAIL;
	पूर्ण
	अगर ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		वापस -E2BIG;

	अगर (mask == 0)
		val = 0;
	अन्यथा
		val = b43_shm_पढ़ो32(dev, routing, addr);
	val &= mask;
	val |= set;
	b43_shm_ग_लिखो32(dev, routing, addr, val);

	वापस 0;
पूर्ण

/* The biggest MMIO address that we allow access to from the debugfs files. */
#घोषणा B43_MAX_MMIO_ACCESS	(0xF00 - 1)

अटल sमाप_प्रकार mmio16पढ़ो__पढ़ो_file(काष्ठा b43_wldev *dev,
				     अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	अचिन्हित पूर्णांक addr;
	u16 val;

	addr = dev->dfsentry->mmio16पढ़ो_next;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EDESTADDRREQ;

	val = b43_पढ़ो16(dev, addr);
	fappend("0x%04X\n", val);

	वापस count;
पूर्ण

अटल पूर्णांक mmio16पढ़ो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक addr;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X", &addr);
	अगर (res != 1)
		वापस -EINVAL;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EADDRNOTAVAIL;
	अगर ((addr % 2) != 0)
		वापस -EINVAL;

	dev->dfsentry->mmio16पढ़ो_next = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक mmio16ग_लिखो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक addr, mask, set;
	पूर्णांक res;
	u16 val;

	res = माला_पूछो(buf, "0x%X 0x%X 0x%X", &addr, &mask, &set);
	अगर (res != 3)
		वापस -EINVAL;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EADDRNOTAVAIL;
	अगर ((mask > 0xFFFF) || (set > 0xFFFF))
		वापस -E2BIG;
	अगर ((addr % 2) != 0)
		वापस -EINVAL;

	अगर (mask == 0)
		val = 0;
	अन्यथा
		val = b43_पढ़ो16(dev, addr);
	val &= mask;
	val |= set;
	b43_ग_लिखो16(dev, addr, val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mmio32पढ़ो__पढ़ो_file(काष्ठा b43_wldev *dev,
				     अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	अचिन्हित पूर्णांक addr;
	u32 val;

	addr = dev->dfsentry->mmio32पढ़ो_next;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EDESTADDRREQ;

	val = b43_पढ़ो32(dev, addr);
	fappend("0x%08X\n", val);

	वापस count;
पूर्ण

अटल पूर्णांक mmio32पढ़ो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक addr;
	पूर्णांक res;

	res = माला_पूछो(buf, "0x%X", &addr);
	अगर (res != 1)
		वापस -EINVAL;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EADDRNOTAVAIL;
	अगर ((addr % 4) != 0)
		वापस -EINVAL;

	dev->dfsentry->mmio32पढ़ो_next = addr;

	वापस 0;
पूर्ण

अटल पूर्णांक mmio32ग_लिखो__ग_लिखो_file(काष्ठा b43_wldev *dev,
				   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित पूर्णांक addr, mask, set;
	पूर्णांक res;
	u32 val;

	res = माला_पूछो(buf, "0x%X 0x%X 0x%X", &addr, &mask, &set);
	अगर (res != 3)
		वापस -EINVAL;
	अगर (addr > B43_MAX_MMIO_ACCESS)
		वापस -EADDRNOTAVAIL;
	अगर ((mask > 0xFFFFFFFF) || (set > 0xFFFFFFFF))
		वापस -E2BIG;
	अगर ((addr % 4) != 0)
		वापस -EINVAL;

	अगर (mask == 0)
		val = 0;
	अन्यथा
		val = b43_पढ़ो32(dev, addr);
	val &= mask;
	val |= set;
	b43_ग_लिखो32(dev, addr, val);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार txstat_पढ़ो_file(काष्ठा b43_wldev *dev,
				अक्षर *buf, माप_प्रकार bufsize)
अणु
	काष्ठा b43_txstatus_log *log = &dev->dfsentry->txstatlog;
	sमाप_प्रकार count = 0;
	पूर्णांक i, idx;
	काष्ठा b43_txstatus *stat;

	अगर (log->end < 0) अणु
		fappend("Nothing transmitted, yet\n");
		जाओ out;
	पूर्ण
	fappend("b43 TX status reports:\n\n"
		"index | cookie | seq | phy_stat | frame_count | "
		"rts_count | supp_reason | pm_indicated | "
		"intermediate | for_ampdu | acked\n" "---\n");
	i = log->end + 1;
	idx = 0;
	जबतक (1) अणु
		अगर (i == B43_NR_LOGGED_TXSTATUS)
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
out:

	वापस count;
पूर्ण

अटल पूर्णांक restart_ग_लिखो_file(काष्ठा b43_wldev *dev,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक err = 0;

	अगर (count > 0 && buf[0] == '1') अणु
		b43_controller_restart(dev, "manually restarted");
	पूर्ण अन्यथा
		err = -EINVAL;

	वापस err;
पूर्ण

अटल अचिन्हित दीर्घ calc_expire_secs(अचिन्हित दीर्घ now,
				      अचिन्हित दीर्घ समय,
				      अचिन्हित दीर्घ expire)
अणु
	expire = समय + expire;

	अगर (समय_after(now, expire))
		वापस 0; /* expired */
	अगर (expire < now) अणु
		/* jअगरfies wrapped */
		expire -= MAX_JIFFY_OFFSET;
		now -= MAX_JIFFY_OFFSET;
	पूर्ण
	B43_WARN_ON(expire < now);

	वापस (expire - now) / HZ;
पूर्ण

अटल sमाप_प्रकार loctls_पढ़ो_file(काष्ठा b43_wldev *dev,
				अक्षर *buf, माप_प्रकार bufsize)
अणु
	sमाप_प्रकार count = 0;
	काष्ठा b43_txघातer_lo_control *lo;
	पूर्णांक i, err = 0;
	काष्ठा b43_lo_calib *cal;
	अचिन्हित दीर्घ now = jअगरfies;
	काष्ठा b43_phy *phy = &dev->phy;

	अगर (phy->type != B43_PHYTYPE_G) अणु
		fappend("Device is not a G-PHY\n");
		err = -ENODEV;
		जाओ out;
	पूर्ण
	lo = phy->g->lo_control;
	fappend("-- Local Oscillator calibration data --\n\n");
	fappend("HW-power-control enabled: %d\n",
		dev->phy.hardware_घातer_control);
	fappend("TX Bias: 0x%02X,  TX Magn: 0x%02X  (expire in %lu sec)\n",
		lo->tx_bias, lo->tx_magn,
		calc_expire_secs(now, lo->txctl_measured_समय,
				 B43_LO_TXCTL_EXPIRE));
	fappend("Power Vector: 0x%08X%08X  (expires in %lu sec)\n",
		(अचिन्हित पूर्णांक)((lo->घातer_vector & 0xFFFFFFFF00000000ULL) >> 32),
		(अचिन्हित पूर्णांक)(lo->घातer_vector & 0x00000000FFFFFFFFULL),
		calc_expire_secs(now, lo->pwr_vec_पढ़ो_समय,
				 B43_LO_PWRVEC_EXPIRE));

	fappend("\nCalibrated settings:\n");
	list_क्रम_each_entry(cal, &lo->calib_list, list) अणु
		bool active;

		active = (b43_compare_bbatt(&cal->bbatt, &phy->g->bbatt) &&
			  b43_compare_rfatt(&cal->rfatt, &phy->g->rfatt));
		fappend("BB(%d), RF(%d,%d)  ->  I=%d, Q=%d  "
			"(expires in %lu sec)%s\n",
			cal->bbatt.att,
			cal->rfatt.att, cal->rfatt.with_padmix,
			cal->ctl.i, cal->ctl.q,
			calc_expire_secs(now, cal->calib_समय,
					 B43_LO_CALIB_EXPIRE),
			active ? "  ACTIVE" : "");
	पूर्ण

	fappend("\nUsed RF attenuation values:  Value(WithPadmix flag)\n");
	क्रम (i = 0; i < lo->rfatt_list.len; i++) अणु
		fappend("%u(%d), ",
			lo->rfatt_list.list[i].att,
			lo->rfatt_list.list[i].with_padmix);
	पूर्ण
	fappend("\n");
	fappend("\nUsed Baseband attenuation values:\n");
	क्रम (i = 0; i < lo->bbatt_list.len; i++) अणु
		fappend("%u, ",
			lo->bbatt_list.list[i].att);
	पूर्ण
	fappend("\n");

out:
	वापस err ? err : count;
पूर्ण

#अघोषित fappend

अटल sमाप_प्रकार b43_debugfs_पढ़ो(काष्ठा file *file, अक्षर __user *userbuf,
				माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा b43_wldev *dev;
	काष्ठा b43_debugfs_fops *dfops;
	काष्ठा b43_dfs_file *dfile;
	sमाप_प्रकार ret;
	अक्षर *buf;
	स्थिर माप_प्रकार bufsize = 1024 * 16; /* 16 kiB buffer */
	स्थिर माप_प्रकार buक्रमder = get_order(bufsize);
	पूर्णांक err = 0;

	अगर (!count)
		वापस 0;
	dev = file->निजी_data;
	अगर (!dev)
		वापस -ENODEV;

	mutex_lock(&dev->wl->mutex);
	अगर (b43_status(dev) < B43_STAT_INITIALIZED) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा b43_debugfs_fops, fops);
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

अटल sमाप_प्रकार b43_debugfs_ग_लिखो(काष्ठा file *file,
				 स्थिर अक्षर __user *userbuf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा b43_wldev *dev;
	काष्ठा b43_debugfs_fops *dfops;
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
	अगर (b43_status(dev) < B43_STAT_INITIALIZED) अणु
		err = -ENODEV;
		जाओ out_unlock;
	पूर्ण

	dfops = container_of(debugfs_real_fops(file),
			     काष्ठा b43_debugfs_fops, fops);
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
	err = dfops->ग_लिखो(dev, buf, count);
	अगर (err)
		जाओ out_मुक्तpage;

out_मुक्तpage:
	मुक्त_page((अचिन्हित दीर्घ)buf);
out_unlock:
	mutex_unlock(&dev->wl->mutex);

	वापस err ? err : count;
पूर्ण


#घोषणा B43_DEBUGFS_FOPS(name, _पढ़ो, _ग_लिखो)			\
	अटल काष्ठा b43_debugfs_fops fops_##name = अणु		\
		.पढ़ो	= _पढ़ो,				\
		.ग_लिखो	= _ग_लिखो,				\
		.fops	= अणु					\
			.खोलो	= simple_खोलो,			\
			.पढ़ो	= b43_debugfs_पढ़ो,		\
			.ग_लिखो	= b43_debugfs_ग_लिखो,		\
			.llseek = generic_file_llseek,		\
		पूर्ण,						\
		.file_काष्ठा_offset = दुरत्व(काष्ठा b43_dfsentry, \
					       file_##name),	\
	पूर्ण

B43_DEBUGFS_FOPS(shm16पढ़ो, shm16पढ़ो__पढ़ो_file, shm16पढ़ो__ग_लिखो_file);
B43_DEBUGFS_FOPS(shm16ग_लिखो, शून्य, shm16ग_लिखो__ग_लिखो_file);
B43_DEBUGFS_FOPS(shm32पढ़ो, shm32पढ़ो__पढ़ो_file, shm32पढ़ो__ग_लिखो_file);
B43_DEBUGFS_FOPS(shm32ग_लिखो, शून्य, shm32ग_लिखो__ग_लिखो_file);
B43_DEBUGFS_FOPS(mmio16पढ़ो, mmio16पढ़ो__पढ़ो_file, mmio16पढ़ो__ग_लिखो_file);
B43_DEBUGFS_FOPS(mmio16ग_लिखो, शून्य, mmio16ग_लिखो__ग_लिखो_file);
B43_DEBUGFS_FOPS(mmio32पढ़ो, mmio32पढ़ो__पढ़ो_file, mmio32पढ़ो__ग_लिखो_file);
B43_DEBUGFS_FOPS(mmio32ग_लिखो, शून्य, mmio32ग_लिखो__ग_लिखो_file);
B43_DEBUGFS_FOPS(txstat, txstat_पढ़ो_file, शून्य);
B43_DEBUGFS_FOPS(restart, शून्य, restart_ग_लिखो_file);
B43_DEBUGFS_FOPS(loctls, loctls_पढ़ो_file, शून्य);


bool b43_debug(काष्ठा b43_wldev *dev, क्रमागत b43_dyndbg feature)
अणु
	bool enabled;

	enabled = (dev->dfsentry && dev->dfsentry->dyn_debug[feature]);
	अगर (unlikely(enabled)) अणु
		/* Force full debugging messages, अगर the user enabled
		 * some dynamic debugging feature. */
		b43_modparam_verbose = B43_VERBOSITY_MAX;
	पूर्ण

	वापस enabled;
पूर्ण

अटल व्योम b43_हटाओ_dynamic_debug(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dfsentry *e = dev->dfsentry;
	पूर्णांक i;

	क्रम (i = 0; i < __B43_NR_DYNDBG; i++)
		debugfs_हटाओ(e->dyn_debug_dentries[i]);
पूर्ण

अटल व्योम b43_add_dynamic_debug(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dfsentry *e = dev->dfsentry;

#घोषणा add_dyn_dbg(name, id, initstate) करो अणु			\
	e->dyn_debug[id] = (initstate);				\
	e->dyn_debug_dentries[id] =				\
		debugfs_create_bool(name, 0600, e->subdir,	\
				&(e->dyn_debug[id]));		\
	पूर्ण जबतक (0)

	add_dyn_dbg("debug_xmitpower", B43_DBG_XMITPOWER, false);
	add_dyn_dbg("debug_dmaoverflow", B43_DBG_DMAOVERFLOW, false);
	add_dyn_dbg("debug_dmaverbose", B43_DBG_DMAVERBOSE, false);
	add_dyn_dbg("debug_pwork_fast", B43_DBG_PWORK_FAST, false);
	add_dyn_dbg("debug_pwork_stop", B43_DBG_PWORK_STOP, false);
	add_dyn_dbg("debug_lo", B43_DBG_LO, false);
	add_dyn_dbg("debug_firmware", B43_DBG_FIRMWARE, false);
	add_dyn_dbg("debug_keys", B43_DBG_KEYS, false);
	add_dyn_dbg("debug_verbose_stats", B43_DBG_VERBOSESTATS, false);

#अघोषित add_dyn_dbg
पूर्ण

व्योम b43_debugfs_add_device(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dfsentry *e;
	काष्ठा b43_txstatus_log *log;
	अक्षर devdir[16];

	B43_WARN_ON(!dev);
	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (!e) अणु
		b43err(dev->wl, "debugfs: add device OOM\n");
		वापस;
	पूर्ण
	e->dev = dev;
	log = &e->txstatlog;
	log->log = kसुस्मृति(B43_NR_LOGGED_TXSTATUS,
			   माप(काष्ठा b43_txstatus), GFP_KERNEL);
	अगर (!log->log) अणु
		b43err(dev->wl, "debugfs: add device txstatus OOM\n");
		kमुक्त(e);
		वापस;
	पूर्ण
	log->end = -1;

	dev->dfsentry = e;

	snम_लिखो(devdir, माप(devdir), "%s", wiphy_name(dev->wl->hw->wiphy));
	e->subdir = debugfs_create_dir(devdir, rootdir);

	e->mmio16पढ़ो_next = 0xFFFF; /* invalid address */
	e->mmio32पढ़ो_next = 0xFFFF; /* invalid address */
	e->shm16पढ़ो_routing_next = 0xFFFFFFFF; /* invalid routing */
	e->shm16पढ़ो_addr_next = 0xFFFFFFFF; /* invalid address */
	e->shm32पढ़ो_routing_next = 0xFFFFFFFF; /* invalid routing */
	e->shm32पढ़ो_addr_next = 0xFFFFFFFF; /* invalid address */

#घोषणा ADD_खाता(name, mode)	\
	करो अणु							\
		e->file_##name.dentry =				\
			debugfs_create_file(__stringअगरy(name),	\
					mode, e->subdir, dev,	\
					&fops_##name.fops);	\
	पूर्ण जबतक (0)


	ADD_खाता(shm16पढ़ो, 0600);
	ADD_खाता(shm16ग_लिखो, 0200);
	ADD_खाता(shm32पढ़ो, 0600);
	ADD_खाता(shm32ग_लिखो, 0200);
	ADD_खाता(mmio16पढ़ो, 0600);
	ADD_खाता(mmio16ग_लिखो, 0200);
	ADD_खाता(mmio32पढ़ो, 0600);
	ADD_खाता(mmio32ग_लिखो, 0200);
	ADD_खाता(txstat, 0400);
	ADD_खाता(restart, 0200);
	ADD_खाता(loctls, 0400);

#अघोषित ADD_खाता

	b43_add_dynamic_debug(dev);
पूर्ण

व्योम b43_debugfs_हटाओ_device(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_dfsentry *e;

	अगर (!dev)
		वापस;
	e = dev->dfsentry;
	अगर (!e)
		वापस;
	b43_हटाओ_dynamic_debug(dev);

	debugfs_हटाओ(e->file_shm16पढ़ो.dentry);
	debugfs_हटाओ(e->file_shm16ग_लिखो.dentry);
	debugfs_हटाओ(e->file_shm32पढ़ो.dentry);
	debugfs_हटाओ(e->file_shm32ग_लिखो.dentry);
	debugfs_हटाओ(e->file_mmio16पढ़ो.dentry);
	debugfs_हटाओ(e->file_mmio16ग_लिखो.dentry);
	debugfs_हटाओ(e->file_mmio32पढ़ो.dentry);
	debugfs_हटाओ(e->file_mmio32ग_लिखो.dentry);
	debugfs_हटाओ(e->file_txstat.dentry);
	debugfs_हटाओ(e->file_restart.dentry);
	debugfs_हटाओ(e->file_loctls.dentry);

	debugfs_हटाओ(e->subdir);
	kमुक्त(e->txstatlog.log);
	kमुक्त(e);
पूर्ण

व्योम b43_debugfs_log_txstat(काष्ठा b43_wldev *dev,
			    स्थिर काष्ठा b43_txstatus *status)
अणु
	काष्ठा b43_dfsentry *e = dev->dfsentry;
	काष्ठा b43_txstatus_log *log;
	काष्ठा b43_txstatus *cur;
	पूर्णांक i;

	अगर (!e)
		वापस;
	log = &e->txstatlog;
	i = log->end + 1;
	अगर (i == B43_NR_LOGGED_TXSTATUS)
		i = 0;
	log->end = i;
	cur = &(log->log[i]);
	स_नकल(cur, status, माप(*cur));
पूर्ण

व्योम b43_debugfs_init(व्योम)
अणु
	rootdir = debugfs_create_dir(KBUILD_MODNAME, शून्य);
पूर्ण

व्योम b43_debugfs_निकास(व्योम)
अणु
	debugfs_हटाओ(rootdir);
पूर्ण
