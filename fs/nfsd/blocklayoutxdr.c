<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014-2016 Christoph Hellwig.
 */
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/nfs4.h>

#समावेश "nfsd.h"
#समावेश "blocklayoutxdr.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_PNFS


__be32
nfsd4_block_encode_layoutget(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_layoutget *lgp)
अणु
	काष्ठा pnfs_block_extent *b = lgp->lg_content;
	पूर्णांक len = माप(__be32) + 5 * माप(__be64) + माप(__be32);
	__be32 *p;

	p = xdr_reserve_space(xdr, माप(__be32) + len);
	अगर (!p)
		वापस nfserr_toosmall;

	*p++ = cpu_to_be32(len);
	*p++ = cpu_to_be32(1);		/* we always वापस a single extent */

	p = xdr_encode_opaque_fixed(p, &b->vol_id,
			माप(काष्ठा nfsd4_deviceid));
	p = xdr_encode_hyper(p, b->foff);
	p = xdr_encode_hyper(p, b->len);
	p = xdr_encode_hyper(p, b->soff);
	*p++ = cpu_to_be32(b->es);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfsd4_block_encode_volume(काष्ठा xdr_stream *xdr, काष्ठा pnfs_block_volume *b)
अणु
	__be32 *p;
	पूर्णांक len;

	चयन (b->type) अणु
	हाल PNFS_BLOCK_VOLUME_SIMPLE:
		len = 4 + 4 + 8 + 4 + (XDR_QUADLEN(b->simple.sig_len) << 2);
		p = xdr_reserve_space(xdr, len);
		अगर (!p)
			वापस -ETOOSMALL;

		*p++ = cpu_to_be32(b->type);
		*p++ = cpu_to_be32(1);	/* single signature */
		p = xdr_encode_hyper(p, b->simple.offset);
		p = xdr_encode_opaque(p, b->simple.sig, b->simple.sig_len);
		अवरोध;
	हाल PNFS_BLOCK_VOLUME_SCSI:
		len = 4 + 4 + 4 + 4 + (XDR_QUADLEN(b->scsi.designator_len) << 2) + 8;
		p = xdr_reserve_space(xdr, len);
		अगर (!p)
			वापस -ETOOSMALL;

		*p++ = cpu_to_be32(b->type);
		*p++ = cpu_to_be32(b->scsi.code_set);
		*p++ = cpu_to_be32(b->scsi.designator_type);
		p = xdr_encode_opaque(p, b->scsi.designator, b->scsi.designator_len);
		p = xdr_encode_hyper(p, b->scsi.pr_key);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस len;
पूर्ण

__be32
nfsd4_block_encode_getdeviceinfo(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	काष्ठा pnfs_block_deviceaddr *dev = gdp->gd_device;
	पूर्णांक len = माप(__be32), ret, i;
	__be32 *p;

	p = xdr_reserve_space(xdr, len + माप(__be32));
	अगर (!p)
		वापस nfserr_resource;

	क्रम (i = 0; i < dev->nr_volumes; i++) अणु
		ret = nfsd4_block_encode_volume(xdr, &dev->volumes[i]);
		अगर (ret < 0)
			वापस nfsत्रुटि_सं(ret);
		len += ret;
	पूर्ण

	/*
	 * Fill in the overall length and number of volumes at the beginning
	 * of the layout.
	 */
	*p++ = cpu_to_be32(len);
	*p++ = cpu_to_be32(dev->nr_volumes);
	वापस 0;
पूर्ण

पूर्णांक
nfsd4_block_decode_layoutupdate(__be32 *p, u32 len, काष्ठा iomap **iomapp,
		u32 block_size)
अणु
	काष्ठा iomap *iomaps;
	u32 nr_iomaps, i;

	अगर (len < माप(u32)) अणु
		dprपूर्णांकk("%s: extent array too small: %u\n", __func__, len);
		वापस -EINVAL;
	पूर्ण
	len -= माप(u32);
	अगर (len % PNFS_BLOCK_EXTENT_SIZE) अणु
		dprपूर्णांकk("%s: extent array invalid: %u\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	nr_iomaps = be32_to_cpup(p++);
	अगर (nr_iomaps != len / PNFS_BLOCK_EXTENT_SIZE) अणु
		dprपूर्णांकk("%s: extent array size mismatch: %u/%u\n",
			__func__, len, nr_iomaps);
		वापस -EINVAL;
	पूर्ण

	iomaps = kसुस्मृति(nr_iomaps, माप(*iomaps), GFP_KERNEL);
	अगर (!iomaps) अणु
		dprपूर्णांकk("%s: failed to allocate extent array\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nr_iomaps; i++) अणु
		काष्ठा pnfs_block_extent bex;

		स_नकल(&bex.vol_id, p, माप(काष्ठा nfsd4_deviceid));
		p += XDR_QUADLEN(माप(काष्ठा nfsd4_deviceid));

		p = xdr_decode_hyper(p, &bex.foff);
		अगर (bex.foff & (block_size - 1)) अणु
			dprपूर्णांकk("%s: unaligned offset 0x%llx\n",
				__func__, bex.foff);
			जाओ fail;
		पूर्ण
		p = xdr_decode_hyper(p, &bex.len);
		अगर (bex.len & (block_size - 1)) अणु
			dprपूर्णांकk("%s: unaligned length 0x%llx\n",
				__func__, bex.foff);
			जाओ fail;
		पूर्ण
		p = xdr_decode_hyper(p, &bex.soff);
		अगर (bex.soff & (block_size - 1)) अणु
			dprपूर्णांकk("%s: unaligned disk offset 0x%llx\n",
				__func__, bex.soff);
			जाओ fail;
		पूर्ण
		bex.es = be32_to_cpup(p++);
		अगर (bex.es != PNFS_BLOCK_READWRITE_DATA) अणु
			dprपूर्णांकk("%s: incorrect extent state %d\n",
				__func__, bex.es);
			जाओ fail;
		पूर्ण

		iomaps[i].offset = bex.foff;
		iomaps[i].length = bex.len;
	पूर्ण

	*iomapp = iomaps;
	वापस nr_iomaps;
fail:
	kमुक्त(iomaps);
	वापस -EINVAL;
पूर्ण

पूर्णांक
nfsd4_scsi_decode_layoutupdate(__be32 *p, u32 len, काष्ठा iomap **iomapp,
		u32 block_size)
अणु
	काष्ठा iomap *iomaps;
	u32 nr_iomaps, expected, i;

	अगर (len < माप(u32)) अणु
		dprपूर्णांकk("%s: extent array too small: %u\n", __func__, len);
		वापस -EINVAL;
	पूर्ण

	nr_iomaps = be32_to_cpup(p++);
	expected = माप(__be32) + nr_iomaps * PNFS_SCSI_RANGE_SIZE;
	अगर (len != expected) अणु
		dprपूर्णांकk("%s: extent array size mismatch: %u/%u\n",
			__func__, len, expected);
		वापस -EINVAL;
	पूर्ण

	iomaps = kसुस्मृति(nr_iomaps, माप(*iomaps), GFP_KERNEL);
	अगर (!iomaps) अणु
		dprपूर्णांकk("%s: failed to allocate extent array\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < nr_iomaps; i++) अणु
		u64 val;

		p = xdr_decode_hyper(p, &val);
		अगर (val & (block_size - 1)) अणु
			dprपूर्णांकk("%s: unaligned offset 0x%llx\n", __func__, val);
			जाओ fail;
		पूर्ण
		iomaps[i].offset = val;

		p = xdr_decode_hyper(p, &val);
		अगर (val & (block_size - 1)) अणु
			dprपूर्णांकk("%s: unaligned length 0x%llx\n", __func__, val);
			जाओ fail;
		पूर्ण
		iomaps[i].length = val;
	पूर्ण

	*iomapp = iomaps;
	वापस nr_iomaps;
fail:
	kमुक्त(iomaps);
	वापस -EINVAL;
पूर्ण
