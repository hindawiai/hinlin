<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016 Tom Haynes <loghyr@primarydata.com>
 *
 * The following implements a super-simple flex-file server
 * where the NFSv4.1 mds is also the ds. And the storage is
 * the same. I.e., writing to the mds via a NFSv4.1 WRITE
 * goes to the same location as the NFSv3 WRITE.
 */
#समावेश <linux/slab.h>

#समावेश <linux/nfsd/debug.h>

#समावेश <linux/sunrpc/addr.h>

#समावेश "flexfilelayoutxdr.h"
#समावेश "pnfs.h"

#घोषणा NFSDDBG_FACILITY	NFSDDBG_PNFS

अटल __be32
nfsd4_ff_proc_layoutget(काष्ठा inode *inode, स्थिर काष्ठा svc_fh *fhp,
		काष्ठा nfsd4_layoutget *args)
अणु
	काष्ठा nfsd4_layout_seg *seg = &args->lg_seg;
	u32 device_generation = 0;
	पूर्णांक error;
	uid_t u;

	काष्ठा pnfs_ff_layout *fl;

	/*
	 * The super simple flex file server has 1 mirror, 1 data server,
	 * and 1 file handle. So instead of 4 allocs, करो 1 क्रम now.
	 * Zero it out क्रम the stateid - करोn't want junk in there!
	 */
	error = -ENOMEM;
	fl = kzalloc(माप(*fl), GFP_KERNEL);
	अगर (!fl)
		जाओ out_error;
	args->lg_content = fl;

	/*
	 * Aव्योम layout commit, try to क्रमce the I/O to the DS,
	 * and क्रम fun, cause all IOMODE_RW layout segments to
	 * effectively be WRITE only.
	 */
	fl->flags = FF_FLAGS_NO_LAYOUTCOMMIT | FF_FLAGS_NO_IO_THRU_MDS |
		    FF_FLAGS_NO_READ_IO;

	/* Do not allow a IOMODE_READ segment to have ग_लिखो pemissions */
	अगर (seg->iomode == IOMODE_READ) अणु
		u = from_kuid(&init_user_ns, inode->i_uid) + 1;
		fl->uid = make_kuid(&init_user_ns, u);
	पूर्ण अन्यथा
		fl->uid = inode->i_uid;
	fl->gid = inode->i_gid;

	error = nfsd4_set_deviceid(&fl->deviceid, fhp, device_generation);
	अगर (error)
		जाओ out_error;

	fl->fh.size = fhp->fh_handle.fh_size;
	स_नकल(fl->fh.data, &fhp->fh_handle.fh_base, fl->fh.size);

	/* Give whole file layout segments */
	seg->offset = 0;
	seg->length = NFS4_MAX_UINT64;

	dprपूर्णांकk("GET: 0x%llx:0x%llx %d\n", seg->offset, seg->length,
		seg->iomode);
	वापस 0;

out_error:
	seg->length = 0;
	वापस nfsत्रुटि_सं(error);
पूर्ण

अटल __be32
nfsd4_ff_proc_getdeviceinfo(काष्ठा super_block *sb, काष्ठा svc_rqst *rqstp,
		काष्ठा nfs4_client *clp, काष्ठा nfsd4_getdeviceinfo *gdp)
अणु
	काष्ठा pnfs_ff_device_addr *da;

	u16 port;
	अक्षर addr[INET6_ADDRSTRLEN];

	da = kzalloc(माप(काष्ठा pnfs_ff_device_addr), GFP_KERNEL);
	अगर (!da)
		वापस nfsत्रुटि_सं(-ENOMEM);

	gdp->gd_device = da;

	da->version = 3;
	da->minor_version = 0;

	da->rsize = svc_max_payload(rqstp);
	da->wsize = da->rsize;

	rpc_ntop((काष्ठा sockaddr *)&rqstp->rq_daddr,
		 addr, INET6_ADDRSTRLEN);
	अगर (rqstp->rq_daddr.ss_family == AF_INET) अणु
		काष्ठा sockaddr_in *sin;

		sin = (काष्ठा sockaddr_in *)&rqstp->rq_daddr;
		port = ntohs(sin->sin_port);
		snम_लिखो(da->netaddr.netid, FF_NETID_LEN + 1, "tcp");
		da->netaddr.netid_len = 3;
	पूर्ण अन्यथा अणु
		काष्ठा sockaddr_in6 *sin6;

		sin6 = (काष्ठा sockaddr_in6 *)&rqstp->rq_daddr;
		port = ntohs(sin6->sin6_port);
		snम_लिखो(da->netaddr.netid, FF_NETID_LEN + 1, "tcp6");
		da->netaddr.netid_len = 4;
	पूर्ण

	da->netaddr.addr_len =
		snम_लिखो(da->netaddr.addr, FF_ADDR_LEN + 1,
			 "%s.%hhu.%hhu", addr, port >> 8, port & 0xff);

	da->tightly_coupled = false;

	वापस 0;
पूर्ण

स्थिर काष्ठा nfsd4_layout_ops ff_layout_ops = अणु
	.notअगरy_types		=
			NOTIFY_DEVICEID4_DELETE | NOTIFY_DEVICEID4_CHANGE,
	.disable_recalls	= true,
	.proc_getdeviceinfo	= nfsd4_ff_proc_getdeviceinfo,
	.encode_getdeviceinfo	= nfsd4_ff_encode_getdeviceinfo,
	.proc_layoutget		= nfsd4_ff_proc_layoutget,
	.encode_layoutget	= nfsd4_ff_encode_layoutget,
पूर्ण;
