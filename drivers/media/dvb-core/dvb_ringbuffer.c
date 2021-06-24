<शैली गुरु>
/*
 *
 * dvb_ringbuffer.c: ring buffer implementation क्रम the dvb driver
 *
 * Copyright (C) 2003 Oliver Endriss
 * Copyright (C) 2004 Andrew de Quincey
 *
 * based on code originally found in av7110.c & dvb_ci.c:
 * Copyright (C) 1999-2003 Ralph  Metzler
 *                       & Marcus Metzler क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License क्रम more details.
 */



#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/माला.स>
#समावेश <linux/uaccess.h>

#समावेश <media/dvb_ringbuffer.h>

#घोषणा PKT_READY 0
#घोषणा PKT_DISPOSED 1


व्योम dvb_ringbuffer_init(काष्ठा dvb_ringbuffer *rbuf, व्योम *data, माप_प्रकार len)
अणु
	rbuf->pपढ़ो=rbuf->pग_लिखो=0;
	rbuf->data=data;
	rbuf->size=len;
	rbuf->error=0;

	init_रुकोqueue_head(&rbuf->queue);

	spin_lock_init(&(rbuf->lock));
पूर्ण



पूर्णांक dvb_ringbuffer_empty(काष्ठा dvb_ringbuffer *rbuf)
अणु
	/* smp_load_acquire() to load ग_लिखो poपूर्णांकer on पढ़ोer side
	 * this pairs with smp_store_release() in dvb_ringbuffer_ग_लिखो(),
	 * dvb_ringbuffer_ग_लिखो_user(), or dvb_ringbuffer_reset()
	 *
	 * क्रम memory barriers also see Documentation/core-api/circular-buffers.rst
	 */
	वापस (rbuf->pपढ़ो == smp_load_acquire(&rbuf->pग_लिखो));
पूर्ण



sमाप_प्रकार dvb_ringbuffer_मुक्त(काष्ठा dvb_ringbuffer *rbuf)
अणु
	sमाप_प्रकार मुक्त;

	/* READ_ONCE() to load पढ़ो poपूर्णांकer on ग_लिखोr side
	 * this pairs with smp_store_release() in dvb_ringbuffer_पढ़ो(),
	 * dvb_ringbuffer_पढ़ो_user(), dvb_ringbuffer_flush(),
	 * or dvb_ringbuffer_reset()
	 */
	मुक्त = READ_ONCE(rbuf->pपढ़ो) - rbuf->pग_लिखो;
	अगर (मुक्त <= 0)
		मुक्त += rbuf->size;
	वापस मुक्त-1;
पूर्ण



sमाप_प्रकार dvb_ringbuffer_avail(काष्ठा dvb_ringbuffer *rbuf)
अणु
	sमाप_प्रकार avail;

	/* smp_load_acquire() to load ग_लिखो poपूर्णांकer on पढ़ोer side
	 * this pairs with smp_store_release() in dvb_ringbuffer_ग_लिखो(),
	 * dvb_ringbuffer_ग_लिखो_user(), or dvb_ringbuffer_reset()
	 */
	avail = smp_load_acquire(&rbuf->pग_लिखो) - rbuf->pपढ़ो;
	अगर (avail < 0)
		avail += rbuf->size;
	वापस avail;
पूर्ण



व्योम dvb_ringbuffer_flush(काष्ठा dvb_ringbuffer *rbuf)
अणु
	/* dvb_ringbuffer_flush() counts as पढ़ो operation
	 * smp_load_acquire() to load ग_लिखो poपूर्णांकer
	 * smp_store_release() to update पढ़ो poपूर्णांकer, this ensures that the
	 * correct poपूर्णांकer is visible क्रम subsequent dvb_ringbuffer_मुक्त()
	 * calls on other cpu cores
	 */
	smp_store_release(&rbuf->pपढ़ो, smp_load_acquire(&rbuf->pग_लिखो));
	rbuf->error = 0;
पूर्ण
EXPORT_SYMBOL(dvb_ringbuffer_flush);

व्योम dvb_ringbuffer_reset(काष्ठा dvb_ringbuffer *rbuf)
अणु
	/* dvb_ringbuffer_reset() counts as पढ़ो and ग_लिखो operation
	 * smp_store_release() to update पढ़ो poपूर्णांकer
	 */
	smp_store_release(&rbuf->pपढ़ो, 0);
	/* smp_store_release() to update ग_लिखो poपूर्णांकer */
	smp_store_release(&rbuf->pग_लिखो, 0);
	rbuf->error = 0;
पूर्ण

व्योम dvb_ringbuffer_flush_spinlock_wakeup(काष्ठा dvb_ringbuffer *rbuf)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rbuf->lock, flags);
	dvb_ringbuffer_flush(rbuf);
	spin_unlock_irqrestore(&rbuf->lock, flags);

	wake_up(&rbuf->queue);
पूर्ण

sमाप_प्रकार dvb_ringbuffer_पढ़ो_user(काष्ठा dvb_ringbuffer *rbuf, u8 __user *buf, माप_प्रकार len)
अणु
	माप_प्रकार toकरो = len;
	माप_प्रकार split;

	split = (rbuf->pपढ़ो + len > rbuf->size) ? rbuf->size - rbuf->pपढ़ो : 0;
	अगर (split > 0) अणु
		अगर (copy_to_user(buf, rbuf->data+rbuf->pपढ़ो, split))
			वापस -EFAULT;
		buf += split;
		toकरो -= split;
		/* smp_store_release() क्रम पढ़ो poपूर्णांकer update to ensure
		 * that buf is not overwritten until पढ़ो is complete,
		 * this pairs with READ_ONCE() in dvb_ringbuffer_मुक्त()
		 */
		smp_store_release(&rbuf->pपढ़ो, 0);
	पूर्ण
	अगर (copy_to_user(buf, rbuf->data+rbuf->pपढ़ो, toकरो))
		वापस -EFAULT;

	/* smp_store_release() to update पढ़ो poपूर्णांकer, see above */
	smp_store_release(&rbuf->pपढ़ो, (rbuf->pपढ़ो + toकरो) % rbuf->size);

	वापस len;
पूर्ण

व्योम dvb_ringbuffer_पढ़ो(काष्ठा dvb_ringbuffer *rbuf, u8 *buf, माप_प्रकार len)
अणु
	माप_प्रकार toकरो = len;
	माप_प्रकार split;

	split = (rbuf->pपढ़ो + len > rbuf->size) ? rbuf->size - rbuf->pपढ़ो : 0;
	अगर (split > 0) अणु
		स_नकल(buf, rbuf->data+rbuf->pपढ़ो, split);
		buf += split;
		toकरो -= split;
		/* smp_store_release() क्रम पढ़ो poपूर्णांकer update to ensure
		 * that buf is not overwritten until पढ़ो is complete,
		 * this pairs with READ_ONCE() in dvb_ringbuffer_मुक्त()
		 */
		smp_store_release(&rbuf->pपढ़ो, 0);
	पूर्ण
	स_नकल(buf, rbuf->data+rbuf->pपढ़ो, toकरो);

	/* smp_store_release() to update पढ़ो poपूर्णांकer, see above */
	smp_store_release(&rbuf->pपढ़ो, (rbuf->pपढ़ो + toकरो) % rbuf->size);
पूर्ण


sमाप_प्रकार dvb_ringbuffer_ग_लिखो(काष्ठा dvb_ringbuffer *rbuf, स्थिर u8 *buf, माप_प्रकार len)
अणु
	माप_प्रकार toकरो = len;
	माप_प्रकार split;

	split = (rbuf->pग_लिखो + len > rbuf->size) ? rbuf->size - rbuf->pग_लिखो : 0;

	अगर (split > 0) अणु
		स_नकल(rbuf->data+rbuf->pग_लिखो, buf, split);
		buf += split;
		toकरो -= split;
		/* smp_store_release() क्रम ग_लिखो poपूर्णांकer update to ensure that
		 * written data is visible on other cpu cores beक्रमe the poपूर्णांकer
		 * update, this pairs with smp_load_acquire() in
		 * dvb_ringbuffer_empty() or dvb_ringbuffer_avail()
		 */
		smp_store_release(&rbuf->pग_लिखो, 0);
	पूर्ण
	स_नकल(rbuf->data+rbuf->pग_लिखो, buf, toकरो);
	/* smp_store_release() क्रम ग_लिखो poपूर्णांकer update, see above */
	smp_store_release(&rbuf->pग_लिखो, (rbuf->pग_लिखो + toकरो) % rbuf->size);

	वापस len;
पूर्ण

sमाप_प्रकार dvb_ringbuffer_ग_लिखो_user(काष्ठा dvb_ringbuffer *rbuf,
				  स्थिर u8 __user *buf, माप_प्रकार len)
अणु
	पूर्णांक status;
	माप_प्रकार toकरो = len;
	माप_प्रकार split;

	split = (rbuf->pग_लिखो + len > rbuf->size) ? rbuf->size - rbuf->pग_लिखो : 0;

	अगर (split > 0) अणु
		status = copy_from_user(rbuf->data+rbuf->pग_लिखो, buf, split);
		अगर (status)
			वापस len - toकरो;
		buf += split;
		toकरो -= split;
		/* smp_store_release() क्रम ग_लिखो poपूर्णांकer update to ensure that
		 * written data is visible on other cpu cores beक्रमe the poपूर्णांकer
		 * update, this pairs with smp_load_acquire() in
		 * dvb_ringbuffer_empty() or dvb_ringbuffer_avail()
		 */
		smp_store_release(&rbuf->pग_लिखो, 0);
	पूर्ण
	status = copy_from_user(rbuf->data+rbuf->pग_लिखो, buf, toकरो);
	अगर (status)
		वापस len - toकरो;
	/* smp_store_release() क्रम ग_लिखो poपूर्णांकer update, see above */
	smp_store_release(&rbuf->pग_लिखो, (rbuf->pग_लिखो + toकरो) % rbuf->size);

	वापस len;
पूर्ण

sमाप_प्रकार dvb_ringbuffer_pkt_ग_लिखो(काष्ठा dvb_ringbuffer *rbuf, u8* buf, माप_प्रकार len)
अणु
	पूर्णांक status;
	sमाप_प्रकार oldpग_लिखो = rbuf->pग_लिखो;

	DVB_RINGBUFFER_WRITE_BYTE(rbuf, len >> 8);
	DVB_RINGBUFFER_WRITE_BYTE(rbuf, len & 0xff);
	DVB_RINGBUFFER_WRITE_BYTE(rbuf, PKT_READY);
	status = dvb_ringbuffer_ग_लिखो(rbuf, buf, len);

	अगर (status < 0) rbuf->pग_लिखो = oldpग_लिखो;
	वापस status;
पूर्ण

sमाप_प्रकार dvb_ringbuffer_pkt_पढ़ो_user(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx,
				पूर्णांक offset, u8 __user *buf, माप_प्रकार len)
अणु
	माप_प्रकार toकरो;
	माप_प्रकार split;
	माप_प्रकार pktlen;

	pktlen = rbuf->data[idx] << 8;
	pktlen |= rbuf->data[(idx + 1) % rbuf->size];
	अगर (offset > pktlen) वापस -EINVAL;
	अगर ((offset + len) > pktlen) len = pktlen - offset;

	idx = (idx + DVB_RINGBUFFER_PKTHDRSIZE + offset) % rbuf->size;
	toकरो = len;
	split = ((idx + len) > rbuf->size) ? rbuf->size - idx : 0;
	अगर (split > 0) अणु
		अगर (copy_to_user(buf, rbuf->data+idx, split))
			वापस -EFAULT;
		buf += split;
		toकरो -= split;
		idx = 0;
	पूर्ण
	अगर (copy_to_user(buf, rbuf->data+idx, toकरो))
		वापस -EFAULT;

	वापस len;
पूर्ण

sमाप_प्रकार dvb_ringbuffer_pkt_पढ़ो(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx,
				पूर्णांक offset, u8* buf, माप_प्रकार len)
अणु
	माप_प्रकार toकरो;
	माप_प्रकार split;
	माप_प्रकार pktlen;

	pktlen = rbuf->data[idx] << 8;
	pktlen |= rbuf->data[(idx + 1) % rbuf->size];
	अगर (offset > pktlen) वापस -EINVAL;
	अगर ((offset + len) > pktlen) len = pktlen - offset;

	idx = (idx + DVB_RINGBUFFER_PKTHDRSIZE + offset) % rbuf->size;
	toकरो = len;
	split = ((idx + len) > rbuf->size) ? rbuf->size - idx : 0;
	अगर (split > 0) अणु
		स_नकल(buf, rbuf->data+idx, split);
		buf += split;
		toकरो -= split;
		idx = 0;
	पूर्ण
	स_नकल(buf, rbuf->data+idx, toकरो);
	वापस len;
पूर्ण

व्योम dvb_ringbuffer_pkt_dispose(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx)
अणु
	माप_प्रकार pktlen;

	rbuf->data[(idx + 2) % rbuf->size] = PKT_DISPOSED;

	// clean up disposed packets
	जबतक(dvb_ringbuffer_avail(rbuf) > DVB_RINGBUFFER_PKTHDRSIZE) अणु
		अगर (DVB_RINGBUFFER_PEEK(rbuf, 2) == PKT_DISPOSED) अणु
			pktlen = DVB_RINGBUFFER_PEEK(rbuf, 0) << 8;
			pktlen |= DVB_RINGBUFFER_PEEK(rbuf, 1);
			DVB_RINGBUFFER_SKIP(rbuf, pktlen + DVB_RINGBUFFER_PKTHDRSIZE);
		पूर्ण अन्यथा अणु
			// first packet is not disposed, so we stop cleaning now
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

sमाप_प्रकार dvb_ringbuffer_pkt_next(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx, माप_प्रकार* pktlen)
अणु
	पूर्णांक consumed;
	पूर्णांक curpktlen;
	पूर्णांक curpktstatus;

	अगर (idx == -1) अणु
	       idx = rbuf->pपढ़ो;
	पूर्ण अन्यथा अणु
		curpktlen = rbuf->data[idx] << 8;
		curpktlen |= rbuf->data[(idx + 1) % rbuf->size];
		idx = (idx + curpktlen + DVB_RINGBUFFER_PKTHDRSIZE) % rbuf->size;
	पूर्ण

	consumed = (idx - rbuf->pपढ़ो) % rbuf->size;

	जबतक((dvb_ringbuffer_avail(rbuf) - consumed) > DVB_RINGBUFFER_PKTHDRSIZE) अणु

		curpktlen = rbuf->data[idx] << 8;
		curpktlen |= rbuf->data[(idx + 1) % rbuf->size];
		curpktstatus = rbuf->data[(idx + 2) % rbuf->size];

		अगर (curpktstatus == PKT_READY) अणु
			*pktlen = curpktlen;
			वापस idx;
		पूर्ण

		consumed += curpktlen + DVB_RINGBUFFER_PKTHDRSIZE;
		idx = (idx + curpktlen + DVB_RINGBUFFER_PKTHDRSIZE) % rbuf->size;
	पूर्ण

	// no packets available
	वापस -1;
पूर्ण



EXPORT_SYMBOL(dvb_ringbuffer_init);
EXPORT_SYMBOL(dvb_ringbuffer_empty);
EXPORT_SYMBOL(dvb_ringbuffer_मुक्त);
EXPORT_SYMBOL(dvb_ringbuffer_avail);
EXPORT_SYMBOL(dvb_ringbuffer_flush_spinlock_wakeup);
EXPORT_SYMBOL(dvb_ringbuffer_पढ़ो_user);
EXPORT_SYMBOL(dvb_ringbuffer_पढ़ो);
EXPORT_SYMBOL(dvb_ringbuffer_ग_लिखो);
EXPORT_SYMBOL(dvb_ringbuffer_ग_लिखो_user);
