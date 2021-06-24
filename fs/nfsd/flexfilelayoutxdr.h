<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2016 Tom Haynes <loghyr@primarydata.com>
 */
#अगर_अघोषित _NFSD_FLEXखाताLAYOUTXDR_H
#घोषणा _NFSD_FLEXखाताLAYOUTXDR_H 1

#समावेश <linux/inet.h>
#समावेश "xdr4.h"

#घोषणा FF_FLAGS_NO_LAYOUTCOMMIT 1
#घोषणा FF_FLAGS_NO_IO_THRU_MDS  2
#घोषणा FF_FLAGS_NO_READ_IO      4

काष्ठा xdr_stream;

#घोषणा FF_NETID_LEN		(4)
#घोषणा FF_ADDR_LEN		(INET6_ADDRSTRLEN + 8)
काष्ठा pnfs_ff_netaddr अणु
	अक्षर				netid[FF_NETID_LEN + 1];
	अक्षर				addr[FF_ADDR_LEN + 1];
	u32				netid_len;
	u32				addr_len;
पूर्ण;

काष्ठा pnfs_ff_device_addr अणु
	काष्ठा pnfs_ff_netaddr		netaddr;
	u32				version;
	u32				minor_version;
	u32				rsize;
	u32				wsize;
	bool				tightly_coupled;
पूर्ण;

काष्ठा pnfs_ff_layout अणु
	u32				flags;
	u32				stats_collect_hपूर्णांक;
	kuid_t				uid;
	kgid_t				gid;
	काष्ठा nfsd4_deviceid		deviceid;
	stateid_t			stateid;
	काष्ठा nfs_fh			fh;
पूर्ण;

__be32 nfsd4_ff_encode_getdeviceinfo(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_getdeviceinfo *gdp);
__be32 nfsd4_ff_encode_layoutget(काष्ठा xdr_stream *xdr,
		काष्ठा nfsd4_layoutget *lgp);

#पूर्ण_अगर /* _NFSD_FLEXखाताLAYOUTXDR_H */
