<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AFS Volume Location Service client पूर्णांकerface
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित AFS_VL_H
#घोषणा AFS_VL_H

#समावेश "afs.h"

#घोषणा AFS_VL_PORT		7003	/* volume location service port */
#घोषणा VL_SERVICE		52	/* RxRPC service ID क्रम the Volume Location service */
#घोषणा YFS_VL_SERVICE		2503	/* Service ID क्रम AuriStor upgraded VL service */

क्रमागत AFSVL_Operations अणु
	VLGETENTRYBYID		= 503,	/* AFS Get VLDB entry by ID */
	VLGETENTRYBYNAME	= 504,	/* AFS Get VLDB entry by name */
	VLPROBE			= 514,	/* AFS probe VL service */
	VLGETENTRYBYIDU		= 526,	/* AFS Get VLDB entry by ID (UUID-variant) */
	VLGETENTRYBYNAMEU	= 527,	/* AFS Get VLDB entry by name (UUID-variant) */
	VLGETADDRSU		= 533,	/* AFS Get addrs क्रम fileserver */
	YVLGETENDPOINTS		= 64002, /* YFS Get endpoपूर्णांकs क्रम file/volume server */
	YVLGETCELLNAME		= 64014, /* YFS Get actual cell name */
	VLGETCAPABILITIES	= 65537, /* AFS Get server capabilities */
पूर्ण;

क्रमागत AFSVL_Errors अणु
	AFSVL_IDEXIST 		= 363520,	/* Volume Id entry exists in vl database */
	AFSVL_IO 		= 363521,	/* I/O related error */
	AFSVL_NAMEEXIST 	= 363522,	/* Volume name entry exists in vl database */
	AFSVL_CREATEFAIL 	= 363523,	/* Internal creation failure */
	AFSVL_NOENT 		= 363524,	/* No such entry */
	AFSVL_EMPTY 		= 363525,	/* Vl database is empty */
	AFSVL_ENTDELETED 	= 363526,	/* Entry is deleted (soft delete) */
	AFSVL_BADNAME 		= 363527,	/* Volume name is illegal */
	AFSVL_BADINDEX 		= 363528,	/* Index is out of range */
	AFSVL_BADVOLTYPE 	= 363529,	/* Bad volume type */
	AFSVL_BADSERVER 	= 363530,	/* Illegal server number (out of range) */
	AFSVL_BADPARTITION 	= 363531,	/* Bad partition number */
	AFSVL_REPSFULL 		= 363532,	/* Run out of space क्रम Replication sites */
	AFSVL_NOREPSERVER 	= 363533,	/* No such Replication server site exists */
	AFSVL_DUPREPSERVER 	= 363534,	/* Replication site alपढ़ोy exists */
	AFSVL_RWNOTFOUND 	= 363535,	/* Parent R/W entry not found */
	AFSVL_BADREFCOUNT 	= 363536,	/* Illegal Reference Count number */
	AFSVL_SIZEEXCEEDED 	= 363537,	/* Vl size क्रम attributes exceeded */
	AFSVL_BADENTRY 		= 363538,	/* Bad incoming vl entry */
	AFSVL_BADVOLIDBUMP 	= 363539,	/* Illegal max volid increment */
	AFSVL_IDALREADYHASHED 	= 363540,	/* RO/BACK id alपढ़ोy hashed */
	AFSVL_ENTRYLOCKED 	= 363541,	/* Vl entry is alपढ़ोy locked */
	AFSVL_BADVOLOPER 	= 363542,	/* Bad volume operation code */
	AFSVL_BADRELLOCKTYPE 	= 363543,	/* Bad release lock type */
	AFSVL_RERELEASE 	= 363544,	/* Status report: last release was पातed */
	AFSVL_BADSERVERFLAG 	= 363545,	/* Invalid replication site server flag */
	AFSVL_PERM 		= 363546,	/* No permission access */
	AFSVL_NOMEM 		= 363547,	/* दो_स्मृति/पुनः_स्मृति failed to alloc enough memory */
पूर्ण;

क्रमागत अणु
	YFS_SERVER_INDEX	= 0,
	YFS_SERVER_UUID		= 1,
	YFS_SERVER_ENDPOINT	= 2,
पूर्ण;

क्रमागत अणु
	YFS_ENDPOINT_IPV4	= 0,
	YFS_ENDPOINT_IPV6	= 1,
पूर्ण;

#घोषणा YFS_MAXENDPOINTS	16

/*
 * maps to "struct vldbentry" in vvl-spec.pdf
 */
काष्ठा afs_vldbentry अणु
	अक्षर		name[65];		/* name of volume (with NUL अक्षर) */
	afs_voltype_t	type;			/* volume type */
	अचिन्हित	num_servers;		/* num servers that hold instances of this vol */
	अचिन्हित	clone_id;		/* cloning ID */

	अचिन्हित	flags;
#घोषणा AFS_VLF_RWEXISTS	0x1000		/* R/W volume exists */
#घोषणा AFS_VLF_ROEXISTS	0x2000		/* R/O volume exists */
#घोषणा AFS_VLF_BACKEXISTS	0x4000		/* backup volume exists */

	afs_volid_t	volume_ids[3];		/* volume IDs */

	काष्ठा अणु
		काष्ठा in_addr	addr;		/* server address */
		अचिन्हित	partition;	/* partition ID on this server */
		अचिन्हित	flags;		/* server specअगरic flags */
#घोषणा AFS_VLSF_NEWREPSITE	0x0001	/* Ignore all 'non-new' servers */
#घोषणा AFS_VLSF_ROVOL		0x0002	/* this server holds a R/O instance of the volume */
#घोषणा AFS_VLSF_RWVOL		0x0004	/* this server holds a R/W instance of the volume */
#घोषणा AFS_VLSF_BACKVOL	0x0008	/* this server holds a backup instance of the volume */
#घोषणा AFS_VLSF_UUID		0x0010	/* This server is referred to by its UUID */
#घोषणा AFS_VLSF_DONTUSE	0x0020	/* This server ref should be ignored */
	पूर्ण servers[8];
पूर्ण;

#घोषणा AFS_VLDB_MAXNAMELEN 65


काष्ठा afs_ListAddrByAttributes__xdr अणु
	__be32			Mask;
#घोषणा AFS_VLADDR_IPADDR	0x1	/* Match by ->ipaddr */
#घोषणा AFS_VLADDR_INDEX	0x2	/* Match by ->index */
#घोषणा AFS_VLADDR_UUID		0x4	/* Match by ->uuid */
	__be32			ipaddr;
	__be32			index;
	__be32			spare;
	काष्ठा afs_uuid__xdr	uuid;
पूर्ण;

काष्ठा afs_uvldbentry__xdr अणु
	__be32			name[AFS_VLDB_MAXNAMELEN];
	__be32			nServers;
	काष्ठा afs_uuid__xdr	serverNumber[AFS_NMAXNSERVERS];
	__be32			serverUnique[AFS_NMAXNSERVERS];
	__be32			serverPartition[AFS_NMAXNSERVERS];
	__be32			serverFlags[AFS_NMAXNSERVERS];
	__be32			volumeId[AFS_MAXTYPES];
	__be32			cloneId;
	__be32			flags;
	__be32			spares1;
	__be32			spares2;
	__be32			spares3;
	__be32			spares4;
	__be32			spares5;
	__be32			spares6;
	__be32			spares7;
	__be32			spares8;
	__be32			spares9;
पूर्ण;

काष्ठा afs_address_list अणु
	refcount_t		usage;
	अचिन्हित पूर्णांक		version;
	अचिन्हित पूर्णांक		nr_addrs;
	काष्ठा sockaddr_rxrpc	addrs[];
पूर्ण;

बाह्य व्योम afs_put_address_list(काष्ठा afs_address_list *alist);

#पूर्ण_अगर /* AFS_VL_H */
