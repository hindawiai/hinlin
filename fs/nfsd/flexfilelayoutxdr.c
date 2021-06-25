<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Tom Haynes <loghyr@primarydata.com>
 */
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/nfs4.h>

#समावेश "nfsd.h"
#समावेश "flexfilelayoutxdr.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_PNFS

काष्ठा ff_idmap अणु
	अक्षर buf[11];
	पूर्णांक len;
पूर्ण;

__be32
nfsd4_ff_encode_layoutget(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_layoutget *lgp)
अणु
	काष्ठा pnfs_ff_layout *fl = lgp->lg_content;
	पूर्णांक len, mirror_len, ds_len, fh_len;
	__be32 *p;

	/*
	 * Unlike nfsd4_encode_user, we know these will
	 * always be stringअगरied.
	 */
	काष्ठा ff_idmap uid;
	काष्ठा ff_idmap gid;

	fh_len = 4 + fl->fh.size;

	uid.len = प्र_लिखो(uid.buf, "%u", from_kuid(&init_user_ns, fl->uid));
	gid.len = प्र_लिखो(gid.buf, "%u", from_kgid(&init_user_ns, fl->gid));

	/* 8 + len क्रम recording the length, name, and padding */
	ds_len = 20 + माप(stateid_opaque_t) + 4 + fh_len +
		 8 + uid.len + 8 + gid.len;

	mirror_len = 4 + ds_len;

	/* The layout segment */
	len = 20 + mirror_len;

	p = xdr_reserve_space(xdr, माप(__be32) + len);
	अगर (!p)
		वापस nfserr_toosmall;

	*p++ = cpu_to_be32(len);
	p = xdr_encode_hyper(p, 0);		/* stripe unit of 1 */

	*p++ = cpu_to_be32(1);			/* single mirror */
	*p++ = cpu_to_be32(1);			/* single data server */

	p = xdr_encode_opaque_fixed(p, &fl->deviceid,
			माप(काष्ठा nfsd4_deviceid));

	*p++ = cpu_to_be32(1);			/* efficiency */

	*p++ = cpu_to_be32(fl->stateid.si_generation);
	p = xdr_encode_opaque_fixed(p, &fl->stateid.si_opaque,
				    माप(stateid_opaque_t));

	*p++ = cpu_to_be32(1);			/* single file handle */
	p = xdr_encode_opaque(p, fl->fh.data, fl->fh.size);

	p = xdr_encode_opaque(p, uid.buf, uid.len);
	p = xdr_encode_opaque(p, gid.buf, gid.len);

	*p++ = cpu_to_be32(fl->flags);
	*p++ = cpu_to_be32(0);			/* No stats collect hपूर्णांक */

	वापस 0;
पूर्ण

__be32
nfsd4_ff_encode_getdeviceinfo(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	काष्ठा pnfs_ff_device_addr *da = gdp->gd_device;
	पूर्णांक len;
	पूर्णांक ver_len;
	पूर्णांक addr_len;
	__be32 *p;

	/* len + padding क्रम two strings */
	addr_len = 16 + da->netaddr.netid_len + da->netaddr.addr_len;
	ver_len = 20;

	len = 4 + ver_len + 4 + addr_len;

	p = xdr_reserve_space(xdr, len + माप(__be32));
	अगर (!p)
		वापस nfserr_resource;

	/*
	 * Fill in the overall length and number of volumes at the beginning
	 * of the layout.
	 */
	*p++ = cpu_to_be32(len);
	*p++ = cpu_to_be32(1);			/* 1 netaddr */
	p = xdr_encode_opaque(p, da->netaddr.netid, da->netaddr.netid_len);
	p = xdr_encode_opaque(p, da->netaddr.addr, da->netaddr.addr_len);

	*p++ = cpu_to_be32(1);			/* 1 versions */

	*p++ = cpu_to_be32(da->version);
	*p++ = cpu_to_be32(da->minor_version);
	*p++ = cpu_to_be32(da->rsize);
	*p++ = cpu_to_be32(da->wsize);
	*p++ = cpu_to_be32(da->tightly_coupled);

	वापस 0;
पूर्ण
