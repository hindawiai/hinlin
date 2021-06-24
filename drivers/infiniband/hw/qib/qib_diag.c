<शैली गुरु>
/*
 * Copyright (c) 2012 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
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

/*
 * This file contains support क्रम diagnostic functions.  It is accessed by
 * खोलोing the qib_diag device, normally minor number 129.  Diagnostic use
 * of the QLogic_IB chip may render the chip or board unusable until the
 * driver is unloaded, or in some हालs, until the प्रणाली is rebooted.
 *
 * Accesses to the chip through this पूर्णांकerface are not similar to going
 * through the /sys/bus/pci resource mmap पूर्णांकerface.
 */

#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/poll.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>

#समावेश "qib.h"
#समावेश "qib_common.h"

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) QIB_DRV_NAME ": " fmt

/*
 * Each client that खोलोs the diag device must पढ़ो then ग_लिखो
 * offset 0, to prevent lossage from अक्रमom cat or od. diag_state
 * sequences this "handshake".
 */
क्रमागत diag_state अणु UNUSED = 0, OPENED, INIT, READY पूर्ण;

/* State क्रम an inभागidual client. PID so children cannot abuse handshake */
अटल काष्ठा qib_diag_client अणु
	काष्ठा qib_diag_client *next;
	काष्ठा qib_devdata *dd;
	pid_t pid;
	क्रमागत diag_state state;
पूर्ण *client_pool;

/*
 * Get a client काष्ठा. Recycled अगर possible, अन्यथा kदो_स्मृति.
 * Must be called with qib_mutex held
 */
अटल काष्ठा qib_diag_client *get_client(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_diag_client *dc;

	dc = client_pool;
	अगर (dc)
		/* got from pool हटाओ it and use */
		client_pool = dc->next;
	अन्यथा
		/* None in pool, alloc and init */
		dc = kदो_स्मृति(माप(*dc), GFP_KERNEL);

	अगर (dc) अणु
		dc->next = शून्य;
		dc->dd = dd;
		dc->pid = current->pid;
		dc->state = OPENED;
	पूर्ण
	वापस dc;
पूर्ण

/*
 * Return to pool. Must be called with qib_mutex held
 */
अटल व्योम वापस_client(काष्ठा qib_diag_client *dc)
अणु
	काष्ठा qib_devdata *dd = dc->dd;
	काष्ठा qib_diag_client *tdc, *rdc;

	rdc = शून्य;
	अगर (dc == dd->diag_client) अणु
		dd->diag_client = dc->next;
		rdc = dc;
	पूर्ण अन्यथा अणु
		tdc = dc->dd->diag_client;
		जबतक (tdc) अणु
			अगर (dc == tdc->next) अणु
				tdc->next = dc->next;
				rdc = dc;
				अवरोध;
			पूर्ण
			tdc = tdc->next;
		पूर्ण
	पूर्ण
	अगर (rdc) अणु
		rdc->state = UNUSED;
		rdc->dd = शून्य;
		rdc->pid = 0;
		rdc->next = client_pool;
		client_pool = rdc;
	पूर्ण
पूर्ण

अटल पूर्णांक qib_diag_खोलो(काष्ठा inode *in, काष्ठा file *fp);
अटल पूर्णांक qib_diag_release(काष्ठा inode *in, काष्ठा file *fp);
अटल sमाप_प्रकार qib_diag_पढ़ो(काष्ठा file *fp, अक्षर __user *data,
			     माप_प्रकार count, loff_t *off);
अटल sमाप_प्रकार qib_diag_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *data,
			      माप_प्रकार count, loff_t *off);

अटल स्थिर काष्ठा file_operations diag_file_ops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = qib_diag_ग_लिखो,
	.पढ़ो = qib_diag_पढ़ो,
	.खोलो = qib_diag_खोलो,
	.release = qib_diag_release,
	.llseek = शेष_llseek,
पूर्ण;

अटल atomic_t diagpkt_count = ATOMIC_INIT(0);
अटल काष्ठा cdev *diagpkt_cdev;
अटल काष्ठा device *diagpkt_device;

अटल sमाप_प्रकार qib_diagpkt_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *data,
				 माप_प्रकार count, loff_t *off);

अटल स्थिर काष्ठा file_operations diagpkt_file_ops = अणु
	.owner = THIS_MODULE,
	.ग_लिखो = qib_diagpkt_ग_लिखो,
	.llseek = noop_llseek,
पूर्ण;

पूर्णांक qib_diag_add(काष्ठा qib_devdata *dd)
अणु
	अक्षर name[16];
	पूर्णांक ret = 0;

	अगर (atomic_inc_वापस(&diagpkt_count) == 1) अणु
		ret = qib_cdev_init(QIB_DIAGPKT_MINOR, "ipath_diagpkt",
				    &diagpkt_file_ops, &diagpkt_cdev,
				    &diagpkt_device);
		अगर (ret)
			जाओ करोne;
	पूर्ण

	snम_लिखो(name, माप(name), "ipath_diag%d", dd->unit);
	ret = qib_cdev_init(QIB_DIAG_MINOR_BASE + dd->unit, name,
			    &diag_file_ops, &dd->diag_cdev,
			    &dd->diag_device);
करोne:
	वापस ret;
पूर्ण

अटल व्योम qib_unरेजिस्टर_observers(काष्ठा qib_devdata *dd);

व्योम qib_diag_हटाओ(काष्ठा qib_devdata *dd)
अणु
	काष्ठा qib_diag_client *dc;

	अगर (atomic_dec_and_test(&diagpkt_count))
		qib_cdev_cleanup(&diagpkt_cdev, &diagpkt_device);

	qib_cdev_cleanup(&dd->diag_cdev, &dd->diag_device);

	/*
	 * Return all diag_clients of this device. There should be none,
	 * as we are "guaranteed" that no clients are still खोलो
	 */
	जबतक (dd->diag_client)
		वापस_client(dd->diag_client);

	/* Now clean up all unused client काष्ठाs */
	जबतक (client_pool) अणु
		dc = client_pool;
		client_pool = dc->next;
		kमुक्त(dc);
	पूर्ण
	/* Clean up observer list */
	qib_unरेजिस्टर_observers(dd);
पूर्ण

/* qib_remap_ioaddr32 - remap an offset पूर्णांकo chip address space to __iomem *
 *
 * @dd: the qlogic_ib device
 * @offs: the offset in chip-space
 * @cntp: Poपूर्णांकer to max (byte) count क्रम transfer starting at offset
 * This वापसs a u32 __iomem * so it can be used क्रम both 64 and 32-bit
 * mapping. It is needed because with the use of PAT क्रम control of
 * ग_लिखो-combining, the logically contiguous address-space of the chip
 * may be split पूर्णांकo भवly non-contiguous spaces, with dअगरferent
 * attributes, which are them mapped to contiguous physical space
 * based from the first BAR.
 *
 * The code below makes the same assumptions as were made in
 * init_chip_wc_pat() (qib_init.c), copied here:
 * Assumes chip address space looks like:
 *		- kregs + sregs + cregs + uregs (in any order)
 *		- piobufs (2K and 4K bufs in either order)
 *	or:
 *		- kregs + sregs + cregs (in any order)
 *		- piobufs (2K and 4K bufs in either order)
 *		- uregs
 *
 * If cntp is non-शून्य, वापसs how many bytes from offset can be accessed
 * Returns 0 अगर the offset is not mapped.
 */
अटल u32 __iomem *qib_remap_ioaddr32(काष्ठा qib_devdata *dd, u32 offset,
				       u32 *cntp)
अणु
	u32 kreglen;
	u32 snd_bottom, snd_lim = 0;
	u32 __iomem *krb32 = (u32 __iomem *)dd->kregbase;
	u32 __iomem *map = शून्य;
	u32 cnt = 0;
	u32 tot4k, offs4k;

	/* First, simplest हाल, offset is within the first map. */
	kreglen = (dd->kregend - dd->kregbase) * माप(u64);
	अगर (offset < kreglen) अणु
		map = krb32 + (offset / माप(u32));
		cnt = kreglen - offset;
		जाओ mapped;
	पूर्ण

	/*
	 * Next check क्रम user regs, the next most common हाल,
	 * and a cheap check because अगर they are not in the first map
	 * they are last in chip.
	 */
	अगर (dd->userbase) अणु
		/* If user regs mapped, they are after send, so set limit. */
		u32 ulim = (dd->cfgctxts * dd->ureg_align) + dd->uregbase;

		अगर (!dd->piovl15base)
			snd_lim = dd->uregbase;
		krb32 = (u32 __iomem *)dd->userbase;
		अगर (offset >= dd->uregbase && offset < ulim) अणु
			map = krb32 + (offset - dd->uregbase) / माप(u32);
			cnt = ulim - offset;
			जाओ mapped;
		पूर्ण
	पूर्ण

	/*
	 * Lastly, check क्रम offset within Send Buffers.
	 * This is gnarly because काष्ठा devdata is deliberately vague
	 * about things like 7322 VL15 buffers, and we are not in
	 * chip-specअगरic code here, so should not make many assumptions.
	 * The one we _करो_ make is that the only chip that has more sndbufs
	 * than we admit is the 7322, and it has userregs above that, so
	 * we know the snd_lim.
	 */
	/* Assume 2K buffers are first. */
	snd_bottom = dd->pio2k_bufbase;
	अगर (snd_lim == 0) अणु
		u32 tot2k = dd->piobcnt2k * ALIGN(dd->piosize2k, dd->palign);

		snd_lim = snd_bottom + tot2k;
	पूर्ण
	/* If 4k buffers exist, account क्रम them by bumping
	 * appropriate limit.
	 */
	tot4k = dd->piobcnt4k * dd->align4k;
	offs4k = dd->piobufbase >> 32;
	अगर (dd->piobcnt4k) अणु
		अगर (snd_bottom > offs4k)
			snd_bottom = offs4k;
		अन्यथा अणु
			/* 4k above 2k. Bump snd_lim, अगर needed*/
			अगर (!dd->userbase || dd->piovl15base)
				snd_lim = offs4k + tot4k;
		पूर्ण
	पूर्ण
	/*
	 * Judgement call: can we ignore the space between SendBuffs and
	 * UserRegs, where we would like to see vl15 buffs, but not more?
	 */
	अगर (offset >= snd_bottom && offset < snd_lim) अणु
		offset -= snd_bottom;
		map = (u32 __iomem *)dd->piobase + (offset / माप(u32));
		cnt = snd_lim - offset;
	पूर्ण

	अगर (!map && offs4k && dd->piovl15base) अणु
		snd_lim = offs4k + tot4k + 2 * dd->align4k;
		अगर (offset >= (offs4k + tot4k) && offset < snd_lim) अणु
			map = (u32 __iomem *)dd->piovl15base +
				((offset - (offs4k + tot4k)) / माप(u32));
			cnt = snd_lim - offset;
		पूर्ण
	पूर्ण

mapped:
	अगर (cntp)
		*cntp = cnt;
	वापस map;
पूर्ण

/*
 * qib_पढ़ो_umem64 - पढ़ो a 64-bit quantity from the chip पूर्णांकo user space
 * @dd: the qlogic_ib device
 * @uaddr: the location to store the data in user memory
 * @regoffs: the offset from BAR0 (_NOT_ full poपूर्णांकer, anymore)
 * @count: number of bytes to copy (multiple of 32 bits)
 *
 * This function also localizes all chip memory accesses.
 * The copy should be written such that we पढ़ो full cacheline packets
 * from the chip.  This is usually used क्रम a single qword
 *
 * NOTE:  This assumes the chip address is 64-bit aligned.
 */
अटल पूर्णांक qib_पढ़ो_umem64(काष्ठा qib_devdata *dd, व्योम __user *uaddr,
			   u32 regoffs, माप_प्रकार count)
अणु
	स्थिर u64 __iomem *reg_addr;
	स्थिर u64 __iomem *reg_end;
	u32 limit;
	पूर्णांक ret;

	reg_addr = (स्थिर u64 __iomem *)qib_remap_ioaddr32(dd, regoffs, &limit);
	अगर (reg_addr == शून्य || limit == 0 || !(dd->flags & QIB_PRESENT)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (count >= limit)
		count = limit;
	reg_end = reg_addr + (count / माप(u64));

	/* not very efficient, but it works क्रम now */
	जबतक (reg_addr < reg_end) अणु
		u64 data = पढ़ोq(reg_addr);

		अगर (copy_to_user(uaddr, &data, माप(u64))) अणु
			ret = -EFAULT;
			जाओ bail;
		पूर्ण
		reg_addr++;
		uaddr += माप(u64);
	पूर्ण
	ret = 0;
bail:
	वापस ret;
पूर्ण

/*
 * qib_ग_लिखो_umem64 - ग_लिखो a 64-bit quantity to the chip from user space
 * @dd: the qlogic_ib device
 * @regoffs: the offset from BAR0 (_NOT_ full poपूर्णांकer, anymore)
 * @uaddr: the source of the data in user memory
 * @count: the number of bytes to copy (multiple of 32 bits)
 *
 * This is usually used क्रम a single qword
 * NOTE:  This assumes the chip address is 64-bit aligned.
 */

अटल पूर्णांक qib_ग_लिखो_umem64(काष्ठा qib_devdata *dd, u32 regoffs,
			    स्थिर व्योम __user *uaddr, माप_प्रकार count)
अणु
	u64 __iomem *reg_addr;
	स्थिर u64 __iomem *reg_end;
	u32 limit;
	पूर्णांक ret;

	reg_addr = (u64 __iomem *)qib_remap_ioaddr32(dd, regoffs, &limit);
	अगर (reg_addr == शून्य || limit == 0 || !(dd->flags & QIB_PRESENT)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (count >= limit)
		count = limit;
	reg_end = reg_addr + (count / माप(u64));

	/* not very efficient, but it works क्रम now */
	जबतक (reg_addr < reg_end) अणु
		u64 data;

		अगर (copy_from_user(&data, uaddr, माप(data))) अणु
			ret = -EFAULT;
			जाओ bail;
		पूर्ण
		ग_लिखोq(data, reg_addr);

		reg_addr++;
		uaddr += माप(u64);
	पूर्ण
	ret = 0;
bail:
	वापस ret;
पूर्ण

/*
 * qib_पढ़ो_umem32 - पढ़ो a 32-bit quantity from the chip पूर्णांकo user space
 * @dd: the qlogic_ib device
 * @uaddr: the location to store the data in user memory
 * @regoffs: the offset from BAR0 (_NOT_ full poपूर्णांकer, anymore)
 * @count: number of bytes to copy
 *
 * पढ़ो 32 bit values, not 64 bit; क्रम memories that only
 * support 32 bit पढ़ोs; usually a single dword.
 */
अटल पूर्णांक qib_पढ़ो_umem32(काष्ठा qib_devdata *dd, व्योम __user *uaddr,
			   u32 regoffs, माप_प्रकार count)
अणु
	स्थिर u32 __iomem *reg_addr;
	स्थिर u32 __iomem *reg_end;
	u32 limit;
	पूर्णांक ret;

	reg_addr = qib_remap_ioaddr32(dd, regoffs, &limit);
	अगर (reg_addr == शून्य || limit == 0 || !(dd->flags & QIB_PRESENT)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (count >= limit)
		count = limit;
	reg_end = reg_addr + (count / माप(u32));

	/* not very efficient, but it works क्रम now */
	जबतक (reg_addr < reg_end) अणु
		u32 data = पढ़ोl(reg_addr);

		अगर (copy_to_user(uaddr, &data, माप(data))) अणु
			ret = -EFAULT;
			जाओ bail;
		पूर्ण

		reg_addr++;
		uaddr += माप(u32);

	पूर्ण
	ret = 0;
bail:
	वापस ret;
पूर्ण

/*
 * qib_ग_लिखो_umem32 - ग_लिखो a 32-bit quantity to the chip from user space
 * @dd: the qlogic_ib device
 * @regoffs: the offset from BAR0 (_NOT_ full poपूर्णांकer, anymore)
 * @uaddr: the source of the data in user memory
 * @count: number of bytes to copy
 *
 * ग_लिखो 32 bit values, not 64 bit; क्रम memories that only
 * support 32 bit ग_लिखो; usually a single dword.
 */

अटल पूर्णांक qib_ग_लिखो_umem32(काष्ठा qib_devdata *dd, u32 regoffs,
			    स्थिर व्योम __user *uaddr, माप_प्रकार count)
अणु
	u32 __iomem *reg_addr;
	स्थिर u32 __iomem *reg_end;
	u32 limit;
	पूर्णांक ret;

	reg_addr = qib_remap_ioaddr32(dd, regoffs, &limit);
	अगर (reg_addr == शून्य || limit == 0 || !(dd->flags & QIB_PRESENT)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (count >= limit)
		count = limit;
	reg_end = reg_addr + (count / माप(u32));

	जबतक (reg_addr < reg_end) अणु
		u32 data;

		अगर (copy_from_user(&data, uaddr, माप(data))) अणु
			ret = -EFAULT;
			जाओ bail;
		पूर्ण
		ग_लिखोl(data, reg_addr);

		reg_addr++;
		uaddr += माप(u32);
	पूर्ण
	ret = 0;
bail:
	वापस ret;
पूर्ण

अटल पूर्णांक qib_diag_खोलो(काष्ठा inode *in, काष्ठा file *fp)
अणु
	पूर्णांक unit = iminor(in) - QIB_DIAG_MINOR_BASE;
	काष्ठा qib_devdata *dd;
	काष्ठा qib_diag_client *dc;
	पूर्णांक ret;

	mutex_lock(&qib_mutex);

	dd = qib_lookup(unit);

	अगर (dd == शून्य || !(dd->flags & QIB_PRESENT) ||
	    !dd->kregbase) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	dc = get_client(dd);
	अगर (!dc) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण
	dc->next = dd->diag_client;
	dd->diag_client = dc;
	fp->निजी_data = dc;
	ret = 0;
bail:
	mutex_unlock(&qib_mutex);

	वापस ret;
पूर्ण

/**
 * qib_diagpkt_ग_लिखो - ग_लिखो an IB packet
 * @fp: the diag data device file poपूर्णांकer
 * @data: qib_diag_pkt काष्ठाure saying where to get the packet
 * @count: size of data to ग_लिखो
 * @off: unused by this code
 */
अटल sमाप_प्रकार qib_diagpkt_ग_लिखो(काष्ठा file *fp,
				 स्थिर अक्षर __user *data,
				 माप_प्रकार count, loff_t *off)
अणु
	u32 __iomem *piobuf;
	u32 plen, pbufn, maxlen_reserve;
	काष्ठा qib_diag_xpkt dp;
	u32 *पंचांगpbuf = शून्य;
	काष्ठा qib_devdata *dd;
	काष्ठा qib_pportdata *ppd;
	sमाप_प्रकार ret = 0;

	अगर (count != माप(dp)) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (copy_from_user(&dp, data, माप(dp))) अणु
		ret = -EFAULT;
		जाओ bail;
	पूर्ण

	dd = qib_lookup(dp.unit);
	अगर (!dd || !(dd->flags & QIB_PRESENT) || !dd->kregbase) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण
	अगर (!(dd->flags & QIB_INITTED)) अणु
		/* no hardware, मुक्तze, etc. */
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	अगर (dp.version != _DIAG_XPKT_VERS) अणु
		qib_dev_err(dd, "Invalid version %u for diagpkt_write\n",
			    dp.version);
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	/* send count must be an exact number of dwords */
	अगर (dp.len & 3) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	अगर (!dp.port || dp.port > dd->num_pports) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण
	ppd = &dd->pport[dp.port - 1];

	/*
	 * need total length beक्रमe first word written, plus 2 Dwords. One Dword
	 * is क्रम padding so we get the full user data when not aligned on
	 * a word boundary. The other Dword is to make sure we have room क्रम the
	 * ICRC which माला_लो tacked on later.
	 */
	maxlen_reserve = 2 * माप(u32);
	अगर (dp.len > ppd->ibmaxlen - maxlen_reserve) अणु
		ret = -EINVAL;
		जाओ bail;
	पूर्ण

	plen = माप(u32) + dp.len;

	पंचांगpbuf = vदो_स्मृति(plen);
	अगर (!पंचांगpbuf) अणु
		ret = -ENOMEM;
		जाओ bail;
	पूर्ण

	अगर (copy_from_user(पंचांगpbuf,
			   u64_to_user_ptr(dp.data),
			   dp.len)) अणु
		ret = -EFAULT;
		जाओ bail;
	पूर्ण

	plen >>= 2;             /* in dwords */

	अगर (dp.pbc_wd == 0)
		dp.pbc_wd = plen;

	piobuf = dd->f_माला_लोendbuf(ppd, dp.pbc_wd, &pbufn);
	अगर (!piobuf) अणु
		ret = -EBUSY;
		जाओ bail;
	पूर्ण
	/* disarm it just to be extra sure */
	dd->f_sendctrl(dd->pport, QIB_SENDCTRL_DISARM_BUF(pbufn));

	/* disable header check on pbufn क्रम this packet */
	dd->f_txchk_change(dd, pbufn, 1, TXCHK_CHG_TYPE_DIS1, शून्य);

	ग_लिखोq(dp.pbc_wd, piobuf);
	/*
	 * Copy all but the trigger word, then flush, so it's written
	 * to chip beक्रमe trigger word, then ग_लिखो trigger word, then
	 * flush again, so packet is sent.
	 */
	अगर (dd->flags & QIB_PIO_FLUSH_WC) अणु
		qib_flush_wc();
		qib_pio_copy(piobuf + 2, पंचांगpbuf, plen - 1);
		qib_flush_wc();
		__raw_ग_लिखोl(पंचांगpbuf[plen - 1], piobuf + plen + 1);
	पूर्ण अन्यथा
		qib_pio_copy(piobuf + 2, पंचांगpbuf, plen);

	अगर (dd->flags & QIB_USE_SPCL_TRIG) अणु
		u32 spcl_off = (pbufn >= dd->piobcnt2k) ? 2047 : 1023;

		qib_flush_wc();
		__raw_ग_लिखोl(0xaebecede, piobuf + spcl_off);
	पूर्ण

	/*
	 * Ensure buffer is written to the chip, then re-enable
	 * header checks (अगर supported by chip).  The txchk
	 * code will ensure seen by chip beक्रमe वापसing.
	 */
	qib_flush_wc();
	qib_sendbuf_करोne(dd, pbufn);
	dd->f_txchk_change(dd, pbufn, 1, TXCHK_CHG_TYPE_ENAB1, शून्य);

	ret = माप(dp);

bail:
	vमुक्त(पंचांगpbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक qib_diag_release(काष्ठा inode *in, काष्ठा file *fp)
अणु
	mutex_lock(&qib_mutex);
	वापस_client(fp->निजी_data);
	fp->निजी_data = शून्य;
	mutex_unlock(&qib_mutex);
	वापस 0;
पूर्ण

/*
 * Chip-specअगरic code calls to रेजिस्टर its पूर्णांकerest in
 * a specअगरic range.
 */
काष्ठा diag_observer_list_elt अणु
	काष्ठा diag_observer_list_elt *next;
	स्थिर काष्ठा diag_observer *op;
पूर्ण;

पूर्णांक qib_रेजिस्टर_observer(काष्ठा qib_devdata *dd,
			  स्थिर काष्ठा diag_observer *op)
अणु
	काष्ठा diag_observer_list_elt *olp;
	अचिन्हित दीर्घ flags;

	अगर (!dd || !op)
		वापस -EINVAL;
	olp = vदो_स्मृति(माप(*olp));
	अगर (!olp)
		वापस -ENOMEM;

	spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
	olp->op = op;
	olp->next = dd->diag_observer_list;
	dd->diag_observer_list = olp;
	spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);

	वापस 0;
पूर्ण

/* Remove all रेजिस्टरed observers when device is बंदd */
अटल व्योम qib_unरेजिस्टर_observers(काष्ठा qib_devdata *dd)
अणु
	काष्ठा diag_observer_list_elt *olp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
	olp = dd->diag_observer_list;
	जबतक (olp) अणु
		/* Pop one observer, let go of lock */
		dd->diag_observer_list = olp->next;
		spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
		vमुक्त(olp);
		/* try again. */
		spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
		olp = dd->diag_observer_list;
	पूर्ण
	spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
पूर्ण

/*
 * Find the observer, अगर any, क्रम the specअगरied address. Initial implementation
 * is simple stack of observers. This must be called with diag transaction
 * lock held.
 */
अटल स्थिर काष्ठा diag_observer *diag_get_observer(काष्ठा qib_devdata *dd,
						     u32 addr)
अणु
	काष्ठा diag_observer_list_elt *olp;
	स्थिर काष्ठा diag_observer *op = शून्य;

	olp = dd->diag_observer_list;
	जबतक (olp) अणु
		op = olp->op;
		अगर (addr >= op->bottom && addr <= op->top)
			अवरोध;
		olp = olp->next;
	पूर्ण
	अगर (!olp)
		op = शून्य;

	वापस op;
पूर्ण

अटल sमाप_प्रकार qib_diag_पढ़ो(काष्ठा file *fp, अक्षर __user *data,
			     माप_प्रकार count, loff_t *off)
अणु
	काष्ठा qib_diag_client *dc = fp->निजी_data;
	काष्ठा qib_devdata *dd = dc->dd;
	sमाप_प्रकार ret;

	अगर (dc->pid != current->pid) अणु
		ret = -EPERM;
		जाओ bail;
	पूर्ण

	अगर (count == 0)
		ret = 0;
	अन्यथा अगर ((count % 4) || (*off % 4))
		/* address or length is not 32-bit aligned, hence invalid */
		ret = -EINVAL;
	अन्यथा अगर (dc->state < READY && (*off || count != 8))
		ret = -EINVAL;  /* prevent cat /dev/qib_diag* */
	अन्यथा अणु
		अचिन्हित दीर्घ flags;
		u64 data64 = 0;
		पूर्णांक use_32;
		स्थिर काष्ठा diag_observer *op;

		use_32 = (count % 8) || (*off % 8);
		ret = -1;
		spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
		/*
		 * Check क्रम observer on this address range.
		 * we only support a single 32 or 64-bit पढ़ो
		 * via observer, currently.
		 */
		op = diag_get_observer(dd, *off);
		अगर (op) अणु
			u32 offset = *off;

			ret = op->hook(dd, op, offset, &data64, 0, use_32);
		पूर्ण
		/*
		 * We need to release lock beक्रमe any copy_to_user(),
		 * whether implicit in qib_पढ़ो_umem* or explicit below.
		 */
		spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
		अगर (!op) अणु
			अगर (use_32)
				/*
				 * Address or length is not 64-bit aligned;
				 * करो 32-bit rd
				 */
				ret = qib_पढ़ो_umem32(dd, data, (u32) *off,
						      count);
			अन्यथा
				ret = qib_पढ़ो_umem64(dd, data, (u32) *off,
						      count);
		पूर्ण अन्यथा अगर (ret == count) अणु
			/* Below finishes हाल where observer existed */
			ret = copy_to_user(data, &data64, use_32 ?
					   माप(u32) : माप(u64));
			अगर (ret)
				ret = -EFAULT;
		पूर्ण
	पूर्ण

	अगर (ret >= 0) अणु
		*off += count;
		ret = count;
		अगर (dc->state == OPENED)
			dc->state = INIT;
	पूर्ण
bail:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार qib_diag_ग_लिखो(काष्ठा file *fp, स्थिर अक्षर __user *data,
			      माप_प्रकार count, loff_t *off)
अणु
	काष्ठा qib_diag_client *dc = fp->निजी_data;
	काष्ठा qib_devdata *dd = dc->dd;
	sमाप_प्रकार ret;

	अगर (dc->pid != current->pid) अणु
		ret = -EPERM;
		जाओ bail;
	पूर्ण

	अगर (count == 0)
		ret = 0;
	अन्यथा अगर ((count % 4) || (*off % 4))
		/* address or length is not 32-bit aligned, hence invalid */
		ret = -EINVAL;
	अन्यथा अगर (dc->state < READY &&
		((*off || count != 8) || dc->state != INIT))
		/* No ग_लिखोs except second-step of init seq */
		ret = -EINVAL;  /* beक्रमe any other ग_लिखो allowed */
	अन्यथा अणु
		अचिन्हित दीर्घ flags;
		स्थिर काष्ठा diag_observer *op = शून्य;
		पूर्णांक use_32 =  (count % 8) || (*off % 8);

		/*
		 * Check क्रम observer on this address range.
		 * We only support a single 32 or 64-bit ग_लिखो
		 * via observer, currently. This helps, because
		 * we would otherwise have to jump through hoops
		 * to make "diag transaction" meaningful when we
		 * cannot करो a copy_from_user जबतक holding the lock.
		 */
		अगर (count == 4 || count == 8) अणु
			u64 data64;
			u32 offset = *off;

			ret = copy_from_user(&data64, data, count);
			अगर (ret) अणु
				ret = -EFAULT;
				जाओ bail;
			पूर्ण
			spin_lock_irqsave(&dd->qib_diag_trans_lock, flags);
			op = diag_get_observer(dd, *off);
			अगर (op)
				ret = op->hook(dd, op, offset, &data64, ~0Ull,
					       use_32);
			spin_unlock_irqrestore(&dd->qib_diag_trans_lock, flags);
		पूर्ण

		अगर (!op) अणु
			अगर (use_32)
				/*
				 * Address or length is not 64-bit aligned;
				 * करो 32-bit ग_लिखो
				 */
				ret = qib_ग_लिखो_umem32(dd, (u32) *off, data,
						       count);
			अन्यथा
				ret = qib_ग_लिखो_umem64(dd, (u32) *off, data,
						       count);
		पूर्ण
	पूर्ण

	अगर (ret >= 0) अणु
		*off += count;
		ret = count;
		अगर (dc->state == INIT)
			dc->state = READY; /* all पढ़ो/ग_लिखो OK now */
	पूर्ण
bail:
	वापस ret;
पूर्ण
