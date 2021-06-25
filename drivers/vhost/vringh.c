<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Helpers क्रम the host side of a virtio ring.
 *
 * Since these may be in userspace, we use (अंतरभूत) accessors.
 */
#समावेश <linux/compiler.h>
#समावेश <linux/module.h>
#समावेश <linux/vringh.h>
#समावेश <linux/virtio_ring.h>
#समावेश <linux/kernel.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#अगर IS_REACHABLE(CONFIG_VHOST_IOTLB)
#समावेश <linux/bvec.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/vhost_iotlb.h>
#पूर्ण_अगर
#समावेश <uapi/linux/virtio_config.h>

अटल __म_लिखो(1,2) __cold व्योम vringh_bad(स्थिर अक्षर *fmt, ...)
अणु
	अटल DEFINE_RATELIMIT_STATE(vringh_rs,
				      DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	अगर (__ratelimit(&vringh_rs)) अणु
		बहु_सूची ap;
		बहु_शुरू(ap, fmt);
		prपूर्णांकk(KERN_NOTICE "vringh:");
		vprपूर्णांकk(fmt, ap);
		बहु_पूर्ण(ap);
	पूर्ण
पूर्ण

/* Returns vring->num अगर empty, -ve on error. */
अटल अंतरभूत पूर्णांक __vringh_get_head(स्थिर काष्ठा vringh *vrh,
				    पूर्णांक (*getu16)(स्थिर काष्ठा vringh *vrh,
						  u16 *val, स्थिर __virtio16 *p),
				    u16 *last_avail_idx)
अणु
	u16 avail_idx, i, head;
	पूर्णांक err;

	err = getu16(vrh, &avail_idx, &vrh->vring.avail->idx);
	अगर (err) अणु
		vringh_bad("Failed to access avail idx at %p",
			   &vrh->vring.avail->idx);
		वापस err;
	पूर्ण

	अगर (*last_avail_idx == avail_idx)
		वापस vrh->vring.num;

	/* Only get avail ring entries after they have been exposed by guest. */
	virtio_rmb(vrh->weak_barriers);

	i = *last_avail_idx & (vrh->vring.num - 1);

	err = getu16(vrh, &head, &vrh->vring.avail->ring[i]);
	अगर (err) अणु
		vringh_bad("Failed to read head: idx %d address %p",
			   *last_avail_idx, &vrh->vring.avail->ring[i]);
		वापस err;
	पूर्ण

	अगर (head >= vrh->vring.num) अणु
		vringh_bad("Guest says index %u > %u is available",
			   head, vrh->vring.num);
		वापस -EINVAL;
	पूर्ण

	(*last_avail_idx)++;
	वापस head;
पूर्ण

/**
 * vringh_kiov_advance - skip bytes from vring_kiov
 * @iov: an iov passed to vringh_getdesc_*() (updated as we consume)
 * @len: the maximum length to advance
 */
व्योम vringh_kiov_advance(काष्ठा vringh_kiov *iov, माप_प्रकार len)
अणु
	जबतक (len && iov->i < iov->used) अणु
		माप_प्रकार partlen = min(iov->iov[iov->i].iov_len, len);

		iov->consumed += partlen;
		iov->iov[iov->i].iov_len -= partlen;
		iov->iov[iov->i].iov_base += partlen;

		अगर (!iov->iov[iov->i].iov_len) अणु
			/* Fix up old iov element then increment. */
			iov->iov[iov->i].iov_len = iov->consumed;
			iov->iov[iov->i].iov_base -= iov->consumed;

			iov->consumed = 0;
			iov->i++;
		पूर्ण

		len -= partlen;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(vringh_kiov_advance);

/* Copy some bytes to/from the iovec.  Returns num copied. */
अटल अंतरभूत sमाप_प्रकार vringh_iov_xfer(काष्ठा vringh *vrh,
				      काष्ठा vringh_kiov *iov,
				      व्योम *ptr, माप_प्रकार len,
				      पूर्णांक (*xfer)(स्थिर काष्ठा vringh *vrh,
						  व्योम *addr, व्योम *ptr,
						  माप_प्रकार len))
अणु
	पूर्णांक err, करोne = 0;

	जबतक (len && iov->i < iov->used) अणु
		माप_प्रकार partlen;

		partlen = min(iov->iov[iov->i].iov_len, len);
		err = xfer(vrh, iov->iov[iov->i].iov_base, ptr, partlen);
		अगर (err)
			वापस err;
		करोne += partlen;
		len -= partlen;
		ptr += partlen;

		vringh_kiov_advance(iov, partlen);
	पूर्ण
	वापस करोne;
पूर्ण

/* May reduce *len अगर range is लघुer. */
अटल अंतरभूत bool range_check(काष्ठा vringh *vrh, u64 addr, माप_प्रकार *len,
			       काष्ठा vringh_range *range,
			       bool (*getrange)(काष्ठा vringh *,
						u64, काष्ठा vringh_range *))
अणु
	अगर (addr < range->start || addr > range->end_incl) अणु
		अगर (!getrange(vrh, addr, range))
			वापस false;
	पूर्ण
	BUG_ON(addr < range->start || addr > range->end_incl);

	/* To end of memory? */
	अगर (unlikely(addr + *len == 0)) अणु
		अगर (range->end_incl == -1ULL)
			वापस true;
		जाओ truncate;
	पूर्ण

	/* Otherwise, करोn't wrap. */
	अगर (addr + *len < addr) अणु
		vringh_bad("Wrapping descriptor %zu@0x%llx",
			   *len, (अचिन्हित दीर्घ दीर्घ)addr);
		वापस false;
	पूर्ण

	अगर (unlikely(addr + *len - 1 > range->end_incl))
		जाओ truncate;
	वापस true;

truncate:
	*len = range->end_incl + 1 - addr;
	वापस true;
पूर्ण

अटल अंतरभूत bool no_range_check(काष्ठा vringh *vrh, u64 addr, माप_प्रकार *len,
				  काष्ठा vringh_range *range,
				  bool (*getrange)(काष्ठा vringh *,
						   u64, काष्ठा vringh_range *))
अणु
	वापस true;
पूर्ण

/* No reason क्रम this code to be अंतरभूत. */
अटल पूर्णांक move_to_indirect(स्थिर काष्ठा vringh *vrh,
			    पूर्णांक *up_next, u16 *i, व्योम *addr,
			    स्थिर काष्ठा vring_desc *desc,
			    काष्ठा vring_desc **descs, पूर्णांक *desc_max)
अणु
	u32 len;

	/* Indirect tables can't have indirect. */
	अगर (*up_next != -1) अणु
		vringh_bad("Multilevel indirect %u->%u", *up_next, *i);
		वापस -EINVAL;
	पूर्ण

	len = vringh32_to_cpu(vrh, desc->len);
	अगर (unlikely(len % माप(काष्ठा vring_desc))) अणु
		vringh_bad("Strange indirect len %u", desc->len);
		वापस -EINVAL;
	पूर्ण

	/* We will check this when we follow it! */
	अगर (desc->flags & cpu_to_vringh16(vrh, VRING_DESC_F_NEXT))
		*up_next = vringh16_to_cpu(vrh, desc->next);
	अन्यथा
		*up_next = -2;
	*descs = addr;
	*desc_max = len / माप(काष्ठा vring_desc);

	/* Now, start at the first indirect. */
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक resize_iovec(काष्ठा vringh_kiov *iov, gfp_t gfp)
अणु
	काष्ठा kvec *new;
	अचिन्हित पूर्णांक flag, new_num = (iov->max_num & ~VRINGH_IOV_ALLOCATED) * 2;

	अगर (new_num < 8)
		new_num = 8;

	flag = (iov->max_num & VRINGH_IOV_ALLOCATED);
	अगर (flag)
		new = kपुनः_स्मृति_array(iov->iov, new_num,
				     माप(काष्ठा iovec), gfp);
	अन्यथा अणु
		new = kदो_स्मृति_array(new_num, माप(काष्ठा iovec), gfp);
		अगर (new) अणु
			स_नकल(new, iov->iov,
			       iov->max_num * माप(काष्ठा iovec));
			flag = VRINGH_IOV_ALLOCATED;
		पूर्ण
	पूर्ण
	अगर (!new)
		वापस -ENOMEM;
	iov->iov = new;
	iov->max_num = (new_num | flag);
	वापस 0;
पूर्ण

अटल u16 __cold वापस_from_indirect(स्थिर काष्ठा vringh *vrh, पूर्णांक *up_next,
				       काष्ठा vring_desc **descs, पूर्णांक *desc_max)
अणु
	u16 i = *up_next;

	*up_next = -1;
	*descs = vrh->vring.desc;
	*desc_max = vrh->vring.num;
	वापस i;
पूर्ण

अटल पूर्णांक slow_copy(काष्ठा vringh *vrh, व्योम *dst, स्थिर व्योम *src,
		     bool (*rcheck)(काष्ठा vringh *vrh, u64 addr, माप_प्रकार *len,
				    काष्ठा vringh_range *range,
				    bool (*getrange)(काष्ठा vringh *vrh,
						     u64,
						     काष्ठा vringh_range *)),
		     bool (*getrange)(काष्ठा vringh *vrh,
				      u64 addr,
				      काष्ठा vringh_range *r),
		     काष्ठा vringh_range *range,
		     पूर्णांक (*copy)(स्थिर काष्ठा vringh *vrh,
				 व्योम *dst, स्थिर व्योम *src, माप_प्रकार len))
अणु
	माप_प्रकार part, len = माप(काष्ठा vring_desc);

	करो अणु
		u64 addr;
		पूर्णांक err;

		part = len;
		addr = (u64)(अचिन्हित दीर्घ)src - range->offset;

		अगर (!rcheck(vrh, addr, &part, range, getrange))
			वापस -EINVAL;

		err = copy(vrh, dst, src, part);
		अगर (err)
			वापस err;

		dst += part;
		src += part;
		len -= part;
	पूर्ण जबतक (len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
__vringh_iov(काष्ठा vringh *vrh, u16 i,
	     काष्ठा vringh_kiov *riov,
	     काष्ठा vringh_kiov *wiov,
	     bool (*rcheck)(काष्ठा vringh *vrh, u64 addr, माप_प्रकार *len,
			    काष्ठा vringh_range *range,
			    bool (*getrange)(काष्ठा vringh *, u64,
					     काष्ठा vringh_range *)),
	     bool (*getrange)(काष्ठा vringh *, u64, काष्ठा vringh_range *),
	     gfp_t gfp,
	     पूर्णांक (*copy)(स्थिर काष्ठा vringh *vrh,
			 व्योम *dst, स्थिर व्योम *src, माप_प्रकार len))
अणु
	पूर्णांक err, count = 0, up_next, desc_max;
	काष्ठा vring_desc desc, *descs;
	काष्ठा vringh_range range = अणु -1ULL, 0 पूर्ण, slowrange;
	bool slow = false;

	/* We start traversing vring's descriptor table. */
	descs = vrh->vring.desc;
	desc_max = vrh->vring.num;
	up_next = -1;

	/* You must want something! */
	अगर (WARN_ON(!riov && !wiov))
		वापस -EINVAL;

	अगर (riov)
		riov->i = riov->used = riov->consumed = 0;
	अगर (wiov)
		wiov->i = wiov->used = wiov->consumed = 0;

	क्रम (;;) अणु
		व्योम *addr;
		काष्ठा vringh_kiov *iov;
		माप_प्रकार len;

		अगर (unlikely(slow))
			err = slow_copy(vrh, &desc, &descs[i], rcheck, getrange,
					&slowrange, copy);
		अन्यथा
			err = copy(vrh, &desc, &descs[i], माप(desc));
		अगर (unlikely(err))
			जाओ fail;

		अगर (unlikely(desc.flags &
			     cpu_to_vringh16(vrh, VRING_DESC_F_INसूचीECT))) अणु
			u64 a = vringh64_to_cpu(vrh, desc.addr);

			/* Make sure it's OK, and get offset. */
			len = vringh32_to_cpu(vrh, desc.len);
			अगर (!rcheck(vrh, a, &len, &range, getrange)) अणु
				err = -EINVAL;
				जाओ fail;
			पूर्ण

			अगर (unlikely(len != vringh32_to_cpu(vrh, desc.len))) अणु
				slow = true;
				/* We need to save this range to use offset */
				slowrange = range;
			पूर्ण

			addr = (व्योम *)(दीर्घ)(a + range.offset);
			err = move_to_indirect(vrh, &up_next, &i, addr, &desc,
					       &descs, &desc_max);
			अगर (err)
				जाओ fail;
			जारी;
		पूर्ण

		अगर (count++ == vrh->vring.num) अणु
			vringh_bad("Descriptor loop in %p", descs);
			err = -ELOOP;
			जाओ fail;
		पूर्ण

		अगर (desc.flags & cpu_to_vringh16(vrh, VRING_DESC_F_WRITE))
			iov = wiov;
		अन्यथा अणु
			iov = riov;
			अगर (unlikely(wiov && wiov->i)) अणु
				vringh_bad("Readable desc %p after writable",
					   &descs[i]);
				err = -EINVAL;
				जाओ fail;
			पूर्ण
		पूर्ण

		अगर (!iov) अणु
			vringh_bad("Unexpected %s desc",
				   !wiov ? "writable" : "readable");
			err = -EPROTO;
			जाओ fail;
		पूर्ण

	again:
		/* Make sure it's OK, and get offset. */
		len = vringh32_to_cpu(vrh, desc.len);
		अगर (!rcheck(vrh, vringh64_to_cpu(vrh, desc.addr), &len, &range,
			    getrange)) अणु
			err = -EINVAL;
			जाओ fail;
		पूर्ण
		addr = (व्योम *)(अचिन्हित दीर्घ)(vringh64_to_cpu(vrh, desc.addr) +
					       range.offset);

		अगर (unlikely(iov->used == (iov->max_num & ~VRINGH_IOV_ALLOCATED))) अणु
			err = resize_iovec(iov, gfp);
			अगर (err)
				जाओ fail;
		पूर्ण

		iov->iov[iov->used].iov_base = addr;
		iov->iov[iov->used].iov_len = len;
		iov->used++;

		अगर (unlikely(len != vringh32_to_cpu(vrh, desc.len))) अणु
			desc.len = cpu_to_vringh32(vrh,
				   vringh32_to_cpu(vrh, desc.len) - len);
			desc.addr = cpu_to_vringh64(vrh,
				    vringh64_to_cpu(vrh, desc.addr) + len);
			जाओ again;
		पूर्ण

		अगर (desc.flags & cpu_to_vringh16(vrh, VRING_DESC_F_NEXT)) अणु
			i = vringh16_to_cpu(vrh, desc.next);
		पूर्ण अन्यथा अणु
			/* Just in हाल we need to finish traversing above. */
			अगर (unlikely(up_next > 0)) अणु
				i = वापस_from_indirect(vrh, &up_next,
							 &descs, &desc_max);
				slow = false;
			पूर्ण अन्यथा
				अवरोध;
		पूर्ण

		अगर (i >= desc_max) अणु
			vringh_bad("Chained index %u > %u", i, desc_max);
			err = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक __vringh_complete(काष्ठा vringh *vrh,
				    स्थिर काष्ठा vring_used_elem *used,
				    अचिन्हित पूर्णांक num_used,
				    पूर्णांक (*putu16)(स्थिर काष्ठा vringh *vrh,
						  __virtio16 *p, u16 val),
				    पूर्णांक (*putused)(स्थिर काष्ठा vringh *vrh,
						   काष्ठा vring_used_elem *dst,
						   स्थिर काष्ठा vring_used_elem
						   *src, अचिन्हित num))
अणु
	काष्ठा vring_used *used_ring;
	पूर्णांक err;
	u16 used_idx, off;

	used_ring = vrh->vring.used;
	used_idx = vrh->last_used_idx + vrh->completed;

	off = used_idx % vrh->vring.num;

	/* Compiler knows num_used == 1 someबार, hence extra check */
	अगर (num_used > 1 && unlikely(off + num_used >= vrh->vring.num)) अणु
		u16 part = vrh->vring.num - off;
		err = putused(vrh, &used_ring->ring[off], used, part);
		अगर (!err)
			err = putused(vrh, &used_ring->ring[0], used + part,
				      num_used - part);
	पूर्ण अन्यथा
		err = putused(vrh, &used_ring->ring[off], used, num_used);

	अगर (err) अणु
		vringh_bad("Failed to write %u used entries %u at %p",
			   num_used, off, &used_ring->ring[off]);
		वापस err;
	पूर्ण

	/* Make sure buffer is written beक्रमe we update index. */
	virtio_wmb(vrh->weak_barriers);

	err = putu16(vrh, &vrh->vring.used->idx, used_idx + num_used);
	अगर (err) अणु
		vringh_bad("Failed to update used index at %p",
			   &vrh->vring.used->idx);
		वापस err;
	पूर्ण

	vrh->completed += num_used;
	वापस 0;
पूर्ण


अटल अंतरभूत पूर्णांक __vringh_need_notअगरy(काष्ठा vringh *vrh,
				       पूर्णांक (*getu16)(स्थिर काष्ठा vringh *vrh,
						     u16 *val,
						     स्थिर __virtio16 *p))
अणु
	bool notअगरy;
	u16 used_event;
	पूर्णांक err;

	/* Flush out used index update. This is paired with the
	 * barrier that the Guest executes when enabling
	 * पूर्णांकerrupts. */
	virtio_mb(vrh->weak_barriers);

	/* Old-style, without event indices. */
	अगर (!vrh->event_indices) अणु
		u16 flags;
		err = getu16(vrh, &flags, &vrh->vring.avail->flags);
		अगर (err) अणु
			vringh_bad("Failed to get flags at %p",
				   &vrh->vring.avail->flags);
			वापस err;
		पूर्ण
		वापस (!(flags & VRING_AVAIL_F_NO_INTERRUPT));
	पूर्ण

	/* Modern: we know when other side wants to know. */
	err = getu16(vrh, &used_event, &vring_used_event(&vrh->vring));
	अगर (err) अणु
		vringh_bad("Failed to get used event idx at %p",
			   &vring_used_event(&vrh->vring));
		वापस err;
	पूर्ण

	/* Just in हाल we added so many that we wrap. */
	अगर (unlikely(vrh->completed > 0xffff))
		notअगरy = true;
	अन्यथा
		notअगरy = vring_need_event(used_event,
					  vrh->last_used_idx + vrh->completed,
					  vrh->last_used_idx);

	vrh->last_used_idx += vrh->completed;
	vrh->completed = 0;
	वापस notअगरy;
पूर्ण

अटल अंतरभूत bool __vringh_notअगरy_enable(काष्ठा vringh *vrh,
					  पूर्णांक (*getu16)(स्थिर काष्ठा vringh *vrh,
							u16 *val, स्थिर __virtio16 *p),
					  पूर्णांक (*putu16)(स्थिर काष्ठा vringh *vrh,
							__virtio16 *p, u16 val))
अणु
	u16 avail;

	अगर (!vrh->event_indices) अणु
		/* Old-school; update flags. */
		अगर (putu16(vrh, &vrh->vring.used->flags, 0) != 0) अणु
			vringh_bad("Clearing used flags %p",
				   &vrh->vring.used->flags);
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (putu16(vrh, &vring_avail_event(&vrh->vring),
			   vrh->last_avail_idx) != 0) अणु
			vringh_bad("Updating avail event index %p",
				   &vring_avail_event(&vrh->vring));
			वापस true;
		पूर्ण
	पूर्ण

	/* They could have slipped one in as we were करोing that: make
	 * sure it's written, then check again. */
	virtio_mb(vrh->weak_barriers);

	अगर (getu16(vrh, &avail, &vrh->vring.avail->idx) != 0) अणु
		vringh_bad("Failed to check avail idx at %p",
			   &vrh->vring.avail->idx);
		वापस true;
	पूर्ण

	/* This is unlikely, so we just leave notअगरications enabled
	 * (अगर we're using event_indices, we'll only get one
	 * notअगरication anyway). */
	वापस avail == vrh->last_avail_idx;
पूर्ण

अटल अंतरभूत व्योम __vringh_notअगरy_disable(काष्ठा vringh *vrh,
					   पूर्णांक (*putu16)(स्थिर काष्ठा vringh *vrh,
							 __virtio16 *p, u16 val))
अणु
	अगर (!vrh->event_indices) अणु
		/* Old-school; update flags. */
		अगर (putu16(vrh, &vrh->vring.used->flags,
			   VRING_USED_F_NO_NOTIFY)) अणु
			vringh_bad("Setting used flags %p",
				   &vrh->vring.used->flags);
		पूर्ण
	पूर्ण
पूर्ण

/* Userspace access helpers: in this हाल, addresses are really userspace. */
अटल अंतरभूत पूर्णांक getu16_user(स्थिर काष्ठा vringh *vrh, u16 *val, स्थिर __virtio16 *p)
अणु
	__virtio16 v = 0;
	पूर्णांक rc = get_user(v, (__क्रमce __virtio16 __user *)p);
	*val = vringh16_to_cpu(vrh, v);
	वापस rc;
पूर्ण

अटल अंतरभूत पूर्णांक putu16_user(स्थिर काष्ठा vringh *vrh, __virtio16 *p, u16 val)
अणु
	__virtio16 v = cpu_to_vringh16(vrh, val);
	वापस put_user(v, (__क्रमce __virtio16 __user *)p);
पूर्ण

अटल अंतरभूत पूर्णांक copydesc_user(स्थिर काष्ठा vringh *vrh,
				व्योम *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	वापस copy_from_user(dst, (__क्रमce व्योम __user *)src, len) ?
		-EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक putused_user(स्थिर काष्ठा vringh *vrh,
			       काष्ठा vring_used_elem *dst,
			       स्थिर काष्ठा vring_used_elem *src,
			       अचिन्हित पूर्णांक num)
अणु
	वापस copy_to_user((__क्रमce व्योम __user *)dst, src,
			    माप(*dst) * num) ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfer_from_user(स्थिर काष्ठा vringh *vrh, व्योम *src,
				 व्योम *dst, माप_प्रकार len)
अणु
	वापस copy_from_user(dst, (__क्रमce व्योम __user *)src, len) ?
		-EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfer_to_user(स्थिर काष्ठा vringh *vrh,
			       व्योम *dst, व्योम *src, माप_प्रकार len)
अणु
	वापस copy_to_user((__क्रमce व्योम __user *)dst, src, len) ?
		-EFAULT : 0;
पूर्ण

/**
 * vringh_init_user - initialize a vringh क्रम a userspace vring.
 * @vrh: the vringh to initialize.
 * @features: the feature bits क्रम this ring.
 * @num: the number of elements.
 * @weak_barriers: true अगर we only need memory barriers, not I/O.
 * @desc: the userpace descriptor poपूर्णांकer.
 * @avail: the userpace avail poपूर्णांकer.
 * @used: the userpace used poपूर्णांकer.
 *
 * Returns an error अगर num is invalid: you should check poपूर्णांकers
 * yourself!
 */
पूर्णांक vringh_init_user(काष्ठा vringh *vrh, u64 features,
		     अचिन्हित पूर्णांक num, bool weak_barriers,
		     vring_desc_t __user *desc,
		     vring_avail_t __user *avail,
		     vring_used_t __user *used)
अणु
	/* Sane घातer of 2 please! */
	अगर (!num || num > 0xffff || (num & (num - 1))) अणु
		vringh_bad("Bad ring size %u", num);
		वापस -EINVAL;
	पूर्ण

	vrh->little_endian = (features & (1ULL << VIRTIO_F_VERSION_1));
	vrh->event_indices = (features & (1 << VIRTIO_RING_F_EVENT_IDX));
	vrh->weak_barriers = weak_barriers;
	vrh->completed = 0;
	vrh->last_avail_idx = 0;
	vrh->last_used_idx = 0;
	vrh->vring.num = num;
	/* vring expects kernel addresses, but only used via accessors. */
	vrh->vring.desc = (__क्रमce काष्ठा vring_desc *)desc;
	vrh->vring.avail = (__क्रमce काष्ठा vring_avail *)avail;
	vrh->vring.used = (__क्रमce काष्ठा vring_used *)used;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vringh_init_user);

/**
 * vringh_getdesc_user - get next available descriptor from userspace ring.
 * @vrh: the userspace vring.
 * @riov: where to put the पढ़ोable descriptors (or शून्य)
 * @wiov: where to put the writable descriptors (or शून्य)
 * @getrange: function to call to check ranges.
 * @head: head index we received, क्रम passing to vringh_complete_user().
 *
 * Returns 0 अगर there was no descriptor, 1 अगर there was, or -त्रुटि_सं.
 *
 * Note that on error वापस, you can tell the dअगरference between an
 * invalid ring and a single invalid descriptor: in the क्रमmer हाल,
 * *head will be vrh->vring.num.  You may be able to ignore an invalid
 * descriptor, but there's not much you can करो with an invalid ring.
 *
 * Note that you can reuse riov and wiov with subsequent calls. Content is
 * overwritten and memory पुनः_स्मृतिated अगर more space is needed.
 * When you करोn't have to use riov and wiov anymore, you should clean up them
 * calling vringh_iov_cleanup() to release the memory, even on error!
 */
पूर्णांक vringh_getdesc_user(काष्ठा vringh *vrh,
			काष्ठा vringh_iov *riov,
			काष्ठा vringh_iov *wiov,
			bool (*getrange)(काष्ठा vringh *vrh,
					 u64 addr, काष्ठा vringh_range *r),
			u16 *head)
अणु
	पूर्णांक err;

	*head = vrh->vring.num;
	err = __vringh_get_head(vrh, getu16_user, &vrh->last_avail_idx);
	अगर (err < 0)
		वापस err;

	/* Empty... */
	अगर (err == vrh->vring.num)
		वापस 0;

	/* We need the layouts to be the identical क्रम this to work */
	BUILD_BUG_ON(माप(काष्ठा vringh_kiov) != माप(काष्ठा vringh_iov));
	BUILD_BUG_ON(दुरत्व(काष्ठा vringh_kiov, iov) !=
		     दुरत्व(काष्ठा vringh_iov, iov));
	BUILD_BUG_ON(दुरत्व(काष्ठा vringh_kiov, i) !=
		     दुरत्व(काष्ठा vringh_iov, i));
	BUILD_BUG_ON(दुरत्व(काष्ठा vringh_kiov, used) !=
		     दुरत्व(काष्ठा vringh_iov, used));
	BUILD_BUG_ON(दुरत्व(काष्ठा vringh_kiov, max_num) !=
		     दुरत्व(काष्ठा vringh_iov, max_num));
	BUILD_BUG_ON(माप(काष्ठा iovec) != माप(काष्ठा kvec));
	BUILD_BUG_ON(दुरत्व(काष्ठा iovec, iov_base) !=
		     दुरत्व(काष्ठा kvec, iov_base));
	BUILD_BUG_ON(दुरत्व(काष्ठा iovec, iov_len) !=
		     दुरत्व(काष्ठा kvec, iov_len));
	BUILD_BUG_ON(माप(((काष्ठा iovec *)शून्य)->iov_base)
		     != माप(((काष्ठा kvec *)शून्य)->iov_base));
	BUILD_BUG_ON(माप(((काष्ठा iovec *)शून्य)->iov_len)
		     != माप(((काष्ठा kvec *)शून्य)->iov_len));

	*head = err;
	err = __vringh_iov(vrh, *head, (काष्ठा vringh_kiov *)riov,
			   (काष्ठा vringh_kiov *)wiov,
			   range_check, getrange, GFP_KERNEL, copydesc_user);
	अगर (err)
		वापस err;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(vringh_getdesc_user);

/**
 * vringh_iov_pull_user - copy bytes from vring_iov.
 * @riov: the riov as passed to vringh_getdesc_user() (updated as we consume)
 * @dst: the place to copy.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_pull_user(काष्ठा vringh_iov *riov, व्योम *dst, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(शून्य, (काष्ठा vringh_kiov *)riov,
			       dst, len, xfer_from_user);
पूर्ण
EXPORT_SYMBOL(vringh_iov_pull_user);

/**
 * vringh_iov_push_user - copy bytes पूर्णांकo vring_iov.
 * @wiov: the wiov as passed to vringh_getdesc_user() (updated as we consume)
 * @src: the place to copy from.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_push_user(काष्ठा vringh_iov *wiov,
			     स्थिर व्योम *src, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(शून्य, (काष्ठा vringh_kiov *)wiov,
			       (व्योम *)src, len, xfer_to_user);
पूर्ण
EXPORT_SYMBOL(vringh_iov_push_user);

/**
 * vringh_abanकरोn_user - we've decided not to handle the descriptor(s).
 * @vrh: the vring.
 * @num: the number of descriptors to put back (ie. num
 *	 vringh_get_user() to unकरो).
 *
 * The next vringh_get_user() will वापस the old descriptor(s) again.
 */
व्योम vringh_abanकरोn_user(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num)
अणु
	/* We only update vring_avail_event(vr) when we want to be notअगरied,
	 * so we haven't changed that yet. */
	vrh->last_avail_idx -= num;
पूर्ण
EXPORT_SYMBOL(vringh_abanकरोn_user);

/**
 * vringh_complete_user - we've finished with descriptor, publish it.
 * @vrh: the vring.
 * @head: the head as filled in by vringh_getdesc_user.
 * @len: the length of data we have written.
 *
 * You should check vringh_need_notअगरy_user() after one or more calls
 * to this function.
 */
पूर्णांक vringh_complete_user(काष्ठा vringh *vrh, u16 head, u32 len)
अणु
	काष्ठा vring_used_elem used;

	used.id = cpu_to_vringh32(vrh, head);
	used.len = cpu_to_vringh32(vrh, len);
	वापस __vringh_complete(vrh, &used, 1, putu16_user, putused_user);
पूर्ण
EXPORT_SYMBOL(vringh_complete_user);

/**
 * vringh_complete_multi_user - we've finished with many descriptors.
 * @vrh: the vring.
 * @used: the head, length pairs.
 * @num_used: the number of used elements.
 *
 * You should check vringh_need_notअगरy_user() after one or more calls
 * to this function.
 */
पूर्णांक vringh_complete_multi_user(काष्ठा vringh *vrh,
			       स्थिर काष्ठा vring_used_elem used[],
			       अचिन्हित num_used)
अणु
	वापस __vringh_complete(vrh, used, num_used,
				 putu16_user, putused_user);
पूर्ण
EXPORT_SYMBOL(vringh_complete_multi_user);

/**
 * vringh_notअगरy_enable_user - we want to know अगर something changes.
 * @vrh: the vring.
 *
 * This always enables notअगरications, but वापसs false अगर there are
 * now more buffers available in the vring.
 */
bool vringh_notअगरy_enable_user(काष्ठा vringh *vrh)
अणु
	वापस __vringh_notअगरy_enable(vrh, getu16_user, putu16_user);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_enable_user);

/**
 * vringh_notअगरy_disable_user - करोn't tell us अगर something changes.
 * @vrh: the vring.
 *
 * This is our normal running state: we disable and then only enable when
 * we're going to sleep.
 */
व्योम vringh_notअगरy_disable_user(काष्ठा vringh *vrh)
अणु
	__vringh_notअगरy_disable(vrh, putu16_user);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_disable_user);

/**
 * vringh_need_notअगरy_user - must we tell the other side about used buffers?
 * @vrh: the vring we've called vringh_complete_user() on.
 *
 * Returns -त्रुटि_सं or 0 अगर we करोn't need to tell the other side, 1 अगर we करो.
 */
पूर्णांक vringh_need_notअगरy_user(काष्ठा vringh *vrh)
अणु
	वापस __vringh_need_notअगरy(vrh, getu16_user);
पूर्ण
EXPORT_SYMBOL(vringh_need_notअगरy_user);

/* Kernelspace access helpers. */
अटल अंतरभूत पूर्णांक getu16_kern(स्थिर काष्ठा vringh *vrh,
			      u16 *val, स्थिर __virtio16 *p)
अणु
	*val = vringh16_to_cpu(vrh, READ_ONCE(*p));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक putu16_kern(स्थिर काष्ठा vringh *vrh, __virtio16 *p, u16 val)
अणु
	WRITE_ONCE(*p, cpu_to_vringh16(vrh, val));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copydesc_kern(स्थिर काष्ठा vringh *vrh,
				व्योम *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	स_नकल(dst, src, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक putused_kern(स्थिर काष्ठा vringh *vrh,
			       काष्ठा vring_used_elem *dst,
			       स्थिर काष्ठा vring_used_elem *src,
			       अचिन्हित पूर्णांक num)
अणु
	स_नकल(dst, src, num * माप(*dst));
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfer_kern(स्थिर काष्ठा vringh *vrh, व्योम *src,
			    व्योम *dst, माप_प्रकार len)
अणु
	स_नकल(dst, src, len);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक kern_xfer(स्थिर काष्ठा vringh *vrh, व्योम *dst,
			    व्योम *src, माप_प्रकार len)
अणु
	स_नकल(dst, src, len);
	वापस 0;
पूर्ण

/**
 * vringh_init_kern - initialize a vringh क्रम a kernelspace vring.
 * @vrh: the vringh to initialize.
 * @features: the feature bits क्रम this ring.
 * @num: the number of elements.
 * @weak_barriers: true अगर we only need memory barriers, not I/O.
 * @desc: the userpace descriptor poपूर्णांकer.
 * @avail: the userpace avail poपूर्णांकer.
 * @used: the userpace used poपूर्णांकer.
 *
 * Returns an error अगर num is invalid.
 */
पूर्णांक vringh_init_kern(काष्ठा vringh *vrh, u64 features,
		     अचिन्हित पूर्णांक num, bool weak_barriers,
		     काष्ठा vring_desc *desc,
		     काष्ठा vring_avail *avail,
		     काष्ठा vring_used *used)
अणु
	/* Sane घातer of 2 please! */
	अगर (!num || num > 0xffff || (num & (num - 1))) अणु
		vringh_bad("Bad ring size %u", num);
		वापस -EINVAL;
	पूर्ण

	vrh->little_endian = (features & (1ULL << VIRTIO_F_VERSION_1));
	vrh->event_indices = (features & (1 << VIRTIO_RING_F_EVENT_IDX));
	vrh->weak_barriers = weak_barriers;
	vrh->completed = 0;
	vrh->last_avail_idx = 0;
	vrh->last_used_idx = 0;
	vrh->vring.num = num;
	vrh->vring.desc = desc;
	vrh->vring.avail = avail;
	vrh->vring.used = used;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vringh_init_kern);

/**
 * vringh_getdesc_kern - get next available descriptor from kernelspace ring.
 * @vrh: the kernelspace vring.
 * @riov: where to put the पढ़ोable descriptors (or शून्य)
 * @wiov: where to put the writable descriptors (or शून्य)
 * @head: head index we received, क्रम passing to vringh_complete_kern().
 * @gfp: flags क्रम allocating larger riov/wiov.
 *
 * Returns 0 अगर there was no descriptor, 1 अगर there was, or -त्रुटि_सं.
 *
 * Note that on error वापस, you can tell the dअगरference between an
 * invalid ring and a single invalid descriptor: in the क्रमmer हाल,
 * *head will be vrh->vring.num.  You may be able to ignore an invalid
 * descriptor, but there's not much you can करो with an invalid ring.
 *
 * Note that you can reuse riov and wiov with subsequent calls. Content is
 * overwritten and memory पुनः_स्मृतिated अगर more space is needed.
 * When you करोn't have to use riov and wiov anymore, you should clean up them
 * calling vringh_kiov_cleanup() to release the memory, even on error!
 */
पूर्णांक vringh_getdesc_kern(काष्ठा vringh *vrh,
			काष्ठा vringh_kiov *riov,
			काष्ठा vringh_kiov *wiov,
			u16 *head,
			gfp_t gfp)
अणु
	पूर्णांक err;

	err = __vringh_get_head(vrh, getu16_kern, &vrh->last_avail_idx);
	अगर (err < 0)
		वापस err;

	/* Empty... */
	अगर (err == vrh->vring.num)
		वापस 0;

	*head = err;
	err = __vringh_iov(vrh, *head, riov, wiov, no_range_check, शून्य,
			   gfp, copydesc_kern);
	अगर (err)
		वापस err;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(vringh_getdesc_kern);

/**
 * vringh_iov_pull_kern - copy bytes from vring_iov.
 * @riov: the riov as passed to vringh_getdesc_kern() (updated as we consume)
 * @dst: the place to copy.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_pull_kern(काष्ठा vringh_kiov *riov, व्योम *dst, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(शून्य, riov, dst, len, xfer_kern);
पूर्ण
EXPORT_SYMBOL(vringh_iov_pull_kern);

/**
 * vringh_iov_push_kern - copy bytes पूर्णांकo vring_iov.
 * @wiov: the wiov as passed to vringh_getdesc_kern() (updated as we consume)
 * @src: the place to copy from.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_push_kern(काष्ठा vringh_kiov *wiov,
			     स्थिर व्योम *src, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(शून्य, wiov, (व्योम *)src, len, kern_xfer);
पूर्ण
EXPORT_SYMBOL(vringh_iov_push_kern);

/**
 * vringh_abanकरोn_kern - we've decided not to handle the descriptor(s).
 * @vrh: the vring.
 * @num: the number of descriptors to put back (ie. num
 *	 vringh_get_kern() to unकरो).
 *
 * The next vringh_get_kern() will वापस the old descriptor(s) again.
 */
व्योम vringh_abanकरोn_kern(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num)
अणु
	/* We only update vring_avail_event(vr) when we want to be notअगरied,
	 * so we haven't changed that yet. */
	vrh->last_avail_idx -= num;
पूर्ण
EXPORT_SYMBOL(vringh_abanकरोn_kern);

/**
 * vringh_complete_kern - we've finished with descriptor, publish it.
 * @vrh: the vring.
 * @head: the head as filled in by vringh_getdesc_kern.
 * @len: the length of data we have written.
 *
 * You should check vringh_need_notअगरy_kern() after one or more calls
 * to this function.
 */
पूर्णांक vringh_complete_kern(काष्ठा vringh *vrh, u16 head, u32 len)
अणु
	काष्ठा vring_used_elem used;

	used.id = cpu_to_vringh32(vrh, head);
	used.len = cpu_to_vringh32(vrh, len);

	वापस __vringh_complete(vrh, &used, 1, putu16_kern, putused_kern);
पूर्ण
EXPORT_SYMBOL(vringh_complete_kern);

/**
 * vringh_notअगरy_enable_kern - we want to know अगर something changes.
 * @vrh: the vring.
 *
 * This always enables notअगरications, but वापसs false अगर there are
 * now more buffers available in the vring.
 */
bool vringh_notअगरy_enable_kern(काष्ठा vringh *vrh)
अणु
	वापस __vringh_notअगरy_enable(vrh, getu16_kern, putu16_kern);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_enable_kern);

/**
 * vringh_notअगरy_disable_kern - करोn't tell us अगर something changes.
 * @vrh: the vring.
 *
 * This is our normal running state: we disable and then only enable when
 * we're going to sleep.
 */
व्योम vringh_notअगरy_disable_kern(काष्ठा vringh *vrh)
अणु
	__vringh_notअगरy_disable(vrh, putu16_kern);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_disable_kern);

/**
 * vringh_need_notअगरy_kern - must we tell the other side about used buffers?
 * @vrh: the vring we've called vringh_complete_kern() on.
 *
 * Returns -त्रुटि_सं or 0 अगर we करोn't need to tell the other side, 1 अगर we करो.
 */
पूर्णांक vringh_need_notअगरy_kern(काष्ठा vringh *vrh)
अणु
	वापस __vringh_need_notअगरy(vrh, getu16_kern);
पूर्ण
EXPORT_SYMBOL(vringh_need_notअगरy_kern);

#अगर IS_REACHABLE(CONFIG_VHOST_IOTLB)

अटल पूर्णांक iotlb_translate(स्थिर काष्ठा vringh *vrh,
			   u64 addr, u64 len, काष्ठा bio_vec iov[],
			   पूर्णांक iov_size, u32 perm)
अणु
	काष्ठा vhost_iotlb_map *map;
	काष्ठा vhost_iotlb *iotlb = vrh->iotlb;
	पूर्णांक ret = 0;
	u64 s = 0;

	spin_lock(vrh->iotlb_lock);

	जबतक (len > s) अणु
		u64 size, pa, pfn;

		अगर (unlikely(ret >= iov_size)) अणु
			ret = -ENOBUFS;
			अवरोध;
		पूर्ण

		map = vhost_iotlb_itree_first(iotlb, addr,
					      addr + len - 1);
		अगर (!map || map->start > addr) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण अन्यथा अगर (!(map->perm & perm)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		size = map->size - addr + map->start;
		pa = map->addr + addr - map->start;
		pfn = pa >> PAGE_SHIFT;
		iov[ret].bv_page = pfn_to_page(pfn);
		iov[ret].bv_len = min(len - s, size);
		iov[ret].bv_offset = pa & (PAGE_SIZE - 1);
		s += size;
		addr += size;
		++ret;
	पूर्ण

	spin_unlock(vrh->iotlb_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक copy_from_iotlb(स्थिर काष्ठा vringh *vrh, व्योम *dst,
				  व्योम *src, माप_प्रकार len)
अणु
	काष्ठा iov_iter iter;
	काष्ठा bio_vec iov[16];
	पूर्णांक ret;

	ret = iotlb_translate(vrh, (u64)(uपूर्णांकptr_t)src,
			      len, iov, 16, VHOST_MAP_RO);
	अगर (ret < 0)
		वापस ret;

	iov_iter_bvec(&iter, READ, iov, ret, len);

	ret = copy_from_iter(dst, len, &iter);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक copy_to_iotlb(स्थिर काष्ठा vringh *vrh, व्योम *dst,
				व्योम *src, माप_प्रकार len)
अणु
	काष्ठा iov_iter iter;
	काष्ठा bio_vec iov[16];
	पूर्णांक ret;

	ret = iotlb_translate(vrh, (u64)(uपूर्णांकptr_t)dst,
			      len, iov, 16, VHOST_MAP_WO);
	अगर (ret < 0)
		वापस ret;

	iov_iter_bvec(&iter, WRITE, iov, ret, len);

	वापस copy_to_iter(src, len, &iter);
पूर्ण

अटल अंतरभूत पूर्णांक getu16_iotlb(स्थिर काष्ठा vringh *vrh,
			       u16 *val, स्थिर __virtio16 *p)
अणु
	काष्ठा bio_vec iov;
	व्योम *kaddr, *from;
	पूर्णांक ret;

	/* Atomic पढ़ो is needed क्रम getu16 */
	ret = iotlb_translate(vrh, (u64)(uपूर्णांकptr_t)p, माप(*p),
			      &iov, 1, VHOST_MAP_RO);
	अगर (ret < 0)
		वापस ret;

	kaddr = kmap_atomic(iov.bv_page);
	from = kaddr + iov.bv_offset;
	*val = vringh16_to_cpu(vrh, READ_ONCE(*(__virtio16 *)from));
	kunmap_atomic(kaddr);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक putu16_iotlb(स्थिर काष्ठा vringh *vrh,
			       __virtio16 *p, u16 val)
अणु
	काष्ठा bio_vec iov;
	व्योम *kaddr, *to;
	पूर्णांक ret;

	/* Atomic ग_लिखो is needed क्रम putu16 */
	ret = iotlb_translate(vrh, (u64)(uपूर्णांकptr_t)p, माप(*p),
			      &iov, 1, VHOST_MAP_WO);
	अगर (ret < 0)
		वापस ret;

	kaddr = kmap_atomic(iov.bv_page);
	to = kaddr + iov.bv_offset;
	WRITE_ONCE(*(__virtio16 *)to, cpu_to_vringh16(vrh, val));
	kunmap_atomic(kaddr);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक copydesc_iotlb(स्थिर काष्ठा vringh *vrh,
				 व्योम *dst, स्थिर व्योम *src, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = copy_from_iotlb(vrh, dst, (व्योम *)src, len);
	अगर (ret != len)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfer_from_iotlb(स्थिर काष्ठा vringh *vrh, व्योम *src,
				  व्योम *dst, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = copy_from_iotlb(vrh, dst, src, len);
	अगर (ret != len)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक xfer_to_iotlb(स्थिर काष्ठा vringh *vrh,
			       व्योम *dst, व्योम *src, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = copy_to_iotlb(vrh, dst, src, len);
	अगर (ret != len)
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक putused_iotlb(स्थिर काष्ठा vringh *vrh,
				काष्ठा vring_used_elem *dst,
				स्थिर काष्ठा vring_used_elem *src,
				अचिन्हित पूर्णांक num)
अणु
	पूर्णांक size = num * माप(*dst);
	पूर्णांक ret;

	ret = copy_to_iotlb(vrh, dst, (व्योम *)src, num * माप(*dst));
	अगर (ret != size)
		वापस -EFAULT;

	वापस 0;
पूर्ण

/**
 * vringh_init_iotlb - initialize a vringh क्रम a ring with IOTLB.
 * @vrh: the vringh to initialize.
 * @features: the feature bits क्रम this ring.
 * @num: the number of elements.
 * @weak_barriers: true अगर we only need memory barriers, not I/O.
 * @desc: the userpace descriptor poपूर्णांकer.
 * @avail: the userpace avail poपूर्णांकer.
 * @used: the userpace used poपूर्णांकer.
 *
 * Returns an error अगर num is invalid.
 */
पूर्णांक vringh_init_iotlb(काष्ठा vringh *vrh, u64 features,
		      अचिन्हित पूर्णांक num, bool weak_barriers,
		      काष्ठा vring_desc *desc,
		      काष्ठा vring_avail *avail,
		      काष्ठा vring_used *used)
अणु
	वापस vringh_init_kern(vrh, features, num, weak_barriers,
				desc, avail, used);
पूर्ण
EXPORT_SYMBOL(vringh_init_iotlb);

/**
 * vringh_set_iotlb - initialize a vringh क्रम a ring with IOTLB.
 * @vrh: the vring
 * @iotlb: iotlb associated with this vring
 * @iotlb_lock: spinlock to synchronize the iotlb accesses
 */
व्योम vringh_set_iotlb(काष्ठा vringh *vrh, काष्ठा vhost_iotlb *iotlb,
		      spinlock_t *iotlb_lock)
अणु
	vrh->iotlb = iotlb;
	vrh->iotlb_lock = iotlb_lock;
पूर्ण
EXPORT_SYMBOL(vringh_set_iotlb);

/**
 * vringh_getdesc_iotlb - get next available descriptor from ring with
 * IOTLB.
 * @vrh: the kernelspace vring.
 * @riov: where to put the पढ़ोable descriptors (or शून्य)
 * @wiov: where to put the writable descriptors (or शून्य)
 * @head: head index we received, क्रम passing to vringh_complete_iotlb().
 * @gfp: flags क्रम allocating larger riov/wiov.
 *
 * Returns 0 अगर there was no descriptor, 1 अगर there was, or -त्रुटि_सं.
 *
 * Note that on error वापस, you can tell the dअगरference between an
 * invalid ring and a single invalid descriptor: in the क्रमmer हाल,
 * *head will be vrh->vring.num.  You may be able to ignore an invalid
 * descriptor, but there's not much you can करो with an invalid ring.
 *
 * Note that you can reuse riov and wiov with subsequent calls. Content is
 * overwritten and memory पुनः_स्मृतिated अगर more space is needed.
 * When you करोn't have to use riov and wiov anymore, you should clean up them
 * calling vringh_kiov_cleanup() to release the memory, even on error!
 */
पूर्णांक vringh_getdesc_iotlb(काष्ठा vringh *vrh,
			 काष्ठा vringh_kiov *riov,
			 काष्ठा vringh_kiov *wiov,
			 u16 *head,
			 gfp_t gfp)
अणु
	पूर्णांक err;

	err = __vringh_get_head(vrh, getu16_iotlb, &vrh->last_avail_idx);
	अगर (err < 0)
		वापस err;

	/* Empty... */
	अगर (err == vrh->vring.num)
		वापस 0;

	*head = err;
	err = __vringh_iov(vrh, *head, riov, wiov, no_range_check, शून्य,
			   gfp, copydesc_iotlb);
	अगर (err)
		वापस err;

	वापस 1;
पूर्ण
EXPORT_SYMBOL(vringh_getdesc_iotlb);

/**
 * vringh_iov_pull_iotlb - copy bytes from vring_iov.
 * @vrh: the vring.
 * @riov: the riov as passed to vringh_getdesc_iotlb() (updated as we consume)
 * @dst: the place to copy.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_pull_iotlb(काष्ठा vringh *vrh,
			      काष्ठा vringh_kiov *riov,
			      व्योम *dst, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(vrh, riov, dst, len, xfer_from_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_iov_pull_iotlb);

/**
 * vringh_iov_push_iotlb - copy bytes पूर्णांकo vring_iov.
 * @vrh: the vring.
 * @wiov: the wiov as passed to vringh_getdesc_iotlb() (updated as we consume)
 * @src: the place to copy from.
 * @len: the maximum length to copy.
 *
 * Returns the bytes copied <= len or a negative त्रुटि_सं.
 */
sमाप_प्रकार vringh_iov_push_iotlb(काष्ठा vringh *vrh,
			      काष्ठा vringh_kiov *wiov,
			      स्थिर व्योम *src, माप_प्रकार len)
अणु
	वापस vringh_iov_xfer(vrh, wiov, (व्योम *)src, len, xfer_to_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_iov_push_iotlb);

/**
 * vringh_abanकरोn_iotlb - we've decided not to handle the descriptor(s).
 * @vrh: the vring.
 * @num: the number of descriptors to put back (ie. num
 *	 vringh_get_iotlb() to unकरो).
 *
 * The next vringh_get_iotlb() will वापस the old descriptor(s) again.
 */
व्योम vringh_abanकरोn_iotlb(काष्ठा vringh *vrh, अचिन्हित पूर्णांक num)
अणु
	/* We only update vring_avail_event(vr) when we want to be notअगरied,
	 * so we haven't changed that yet.
	 */
	vrh->last_avail_idx -= num;
पूर्ण
EXPORT_SYMBOL(vringh_abanकरोn_iotlb);

/**
 * vringh_complete_iotlb - we've finished with descriptor, publish it.
 * @vrh: the vring.
 * @head: the head as filled in by vringh_getdesc_iotlb.
 * @len: the length of data we have written.
 *
 * You should check vringh_need_notअगरy_iotlb() after one or more calls
 * to this function.
 */
पूर्णांक vringh_complete_iotlb(काष्ठा vringh *vrh, u16 head, u32 len)
अणु
	काष्ठा vring_used_elem used;

	used.id = cpu_to_vringh32(vrh, head);
	used.len = cpu_to_vringh32(vrh, len);

	वापस __vringh_complete(vrh, &used, 1, putu16_iotlb, putused_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_complete_iotlb);

/**
 * vringh_notअगरy_enable_iotlb - we want to know अगर something changes.
 * @vrh: the vring.
 *
 * This always enables notअगरications, but वापसs false अगर there are
 * now more buffers available in the vring.
 */
bool vringh_notअगरy_enable_iotlb(काष्ठा vringh *vrh)
अणु
	वापस __vringh_notअगरy_enable(vrh, getu16_iotlb, putu16_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_enable_iotlb);

/**
 * vringh_notअगरy_disable_iotlb - करोn't tell us अगर something changes.
 * @vrh: the vring.
 *
 * This is our normal running state: we disable and then only enable when
 * we're going to sleep.
 */
व्योम vringh_notअगरy_disable_iotlb(काष्ठा vringh *vrh)
अणु
	__vringh_notअगरy_disable(vrh, putu16_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_notअगरy_disable_iotlb);

/**
 * vringh_need_notअगरy_iotlb - must we tell the other side about used buffers?
 * @vrh: the vring we've called vringh_complete_iotlb() on.
 *
 * Returns -त्रुटि_सं or 0 अगर we करोn't need to tell the other side, 1 अगर we करो.
 */
पूर्णांक vringh_need_notअगरy_iotlb(काष्ठा vringh *vrh)
अणु
	वापस __vringh_need_notअगरy(vrh, getu16_iotlb);
पूर्ण
EXPORT_SYMBOL(vringh_need_notअगरy_iotlb);

#पूर्ण_अगर

MODULE_LICENSE("GPL");
