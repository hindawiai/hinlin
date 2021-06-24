<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS Volume Location Service client
 *
 * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश "afs_fs.h"
#समावेश "internal.h"

/*
 * Deliver reply data to a VL.GetEntryByNameU call.
 */
अटल पूर्णांक afs_deliver_vl_get_entry_by_name_u(काष्ठा afs_call *call)
अणु
	काष्ठा afs_uvldbentry__xdr *uvldb;
	काष्ठा afs_vldb_entry *entry;
	bool new_only = false;
	u32 पंचांगp, nr_servers, vlflags;
	पूर्णांक i, ret;

	_enter("");

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	uvldb = call->buffer;
	entry = call->ret_vldb;

	nr_servers = ntohl(uvldb->nServers);
	अगर (nr_servers > AFS_NMAXNSERVERS)
		nr_servers = AFS_NMAXNSERVERS;

	क्रम (i = 0; i < ARRAY_SIZE(uvldb->name) - 1; i++)
		entry->name[i] = (u8)ntohl(uvldb->name[i]);
	entry->name[i] = 0;
	entry->name_len = म_माप(entry->name);

	/* If there is a new replication site that we can use, ignore all the
	 * sites that aren't marked as new.
	 */
	क्रम (i = 0; i < nr_servers; i++) अणु
		पंचांगp = ntohl(uvldb->serverFlags[i]);
		अगर (!(पंचांगp & AFS_VLSF_DONTUSE) &&
		    (पंचांगp & AFS_VLSF_NEWREPSITE))
			new_only = true;
	पूर्ण

	vlflags = ntohl(uvldb->flags);
	क्रम (i = 0; i < nr_servers; i++) अणु
		काष्ठा afs_uuid__xdr *xdr;
		काष्ठा afs_uuid *uuid;
		पूर्णांक j;
		पूर्णांक n = entry->nr_servers;

		पंचांगp = ntohl(uvldb->serverFlags[i]);
		अगर (पंचांगp & AFS_VLSF_DONTUSE ||
		    (new_only && !(पंचांगp & AFS_VLSF_NEWREPSITE)))
			जारी;
		अगर (पंचांगp & AFS_VLSF_RWVOL) अणु
			entry->fs_mask[n] |= AFS_VOL_VTM_RW;
			अगर (vlflags & AFS_VLF_BACKEXISTS)
				entry->fs_mask[n] |= AFS_VOL_VTM_BAK;
		पूर्ण
		अगर (पंचांगp & AFS_VLSF_ROVOL)
			entry->fs_mask[n] |= AFS_VOL_VTM_RO;
		अगर (!entry->fs_mask[n])
			जारी;

		xdr = &uvldb->serverNumber[i];
		uuid = (काष्ठा afs_uuid *)&entry->fs_server[n];
		uuid->समय_low			= xdr->समय_low;
		uuid->समय_mid			= htons(ntohl(xdr->समय_mid));
		uuid->समय_hi_and_version	= htons(ntohl(xdr->समय_hi_and_version));
		uuid->घड़ी_seq_hi_and_reserved	= (u8)ntohl(xdr->घड़ी_seq_hi_and_reserved);
		uuid->घड़ी_seq_low		= (u8)ntohl(xdr->घड़ी_seq_low);
		क्रम (j = 0; j < 6; j++)
			uuid->node[j] = (u8)ntohl(xdr->node[j]);

		entry->addr_version[n] = ntohl(uvldb->serverUnique[i]);
		entry->nr_servers++;
	पूर्ण

	क्रम (i = 0; i < AFS_MAXTYPES; i++)
		entry->vid[i] = ntohl(uvldb->volumeId[i]);

	अगर (vlflags & AFS_VLF_RWEXISTS)
		__set_bit(AFS_VLDB_HAS_RW, &entry->flags);
	अगर (vlflags & AFS_VLF_ROEXISTS)
		__set_bit(AFS_VLDB_HAS_RO, &entry->flags);
	अगर (vlflags & AFS_VLF_BACKEXISTS)
		__set_bit(AFS_VLDB_HAS_BAK, &entry->flags);

	अगर (!(vlflags & (AFS_VLF_RWEXISTS | AFS_VLF_ROEXISTS | AFS_VLF_BACKEXISTS))) अणु
		entry->error = -ENOMEDIUM;
		__set_bit(AFS_VLDB_QUERY_ERROR, &entry->flags);
	पूर्ण

	__set_bit(AFS_VLDB_QUERY_VALID, &entry->flags);
	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

अटल व्योम afs_destroy_vl_get_entry_by_name_u(काष्ठा afs_call *call)
अणु
	kमुक्त(call->ret_vldb);
	afs_flat_call_deकाष्ठाor(call);
पूर्ण

/*
 * VL.GetEntryByNameU operation type.
 */
अटल स्थिर काष्ठा afs_call_type afs_RXVLGetEntryByNameU = अणु
	.name		= "VL.GetEntryByNameU",
	.op		= afs_VL_GetEntryByNameU,
	.deliver	= afs_deliver_vl_get_entry_by_name_u,
	.deकाष्ठाor	= afs_destroy_vl_get_entry_by_name_u,
पूर्ण;

/*
 * Dispatch a get volume entry by name or ID operation (uuid variant).  If the
 * volname is a decimal number then it's a volume ID not a volume name.
 */
काष्ठा afs_vldb_entry *afs_vl_get_entry_by_name_u(काष्ठा afs_vl_cursor *vc,
						  स्थिर अक्षर *volname,
						  पूर्णांक volnamesz)
अणु
	काष्ठा afs_vldb_entry *entry;
	काष्ठा afs_call *call;
	काष्ठा afs_net *net = vc->cell->net;
	माप_प्रकार reqsz, padsz;
	__be32 *bp;

	_enter("");

	padsz = (4 - (volnamesz & 3)) & 3;
	reqsz = 8 + volnamesz + padsz;

	entry = kzalloc(माप(काष्ठा afs_vldb_entry), GFP_KERNEL);
	अगर (!entry)
		वापस ERR_PTR(-ENOMEM);

	call = afs_alloc_flat_call(net, &afs_RXVLGetEntryByNameU, reqsz,
				   माप(काष्ठा afs_uvldbentry__xdr));
	अगर (!call) अणु
		kमुक्त(entry);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	call->key = vc->key;
	call->ret_vldb = entry;
	call->max_lअगरespan = AFS_VL_MAX_LIFESPAN;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETENTRYBYNAMEU);
	*bp++ = htonl(volnamesz);
	स_नकल(bp, volname, volnamesz);
	अगर (padsz > 0)
		स_रखो((व्योम *)bp + volnamesz, 0, padsz);

	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	वापस (काष्ठा afs_vldb_entry *)afs_रुको_क्रम_call_to_complete(call, &vc->ac);
पूर्ण

/*
 * Deliver reply data to a VL.GetAddrsU call.
 *
 *	GetAddrsU(IN ListAddrByAttributes *inaddr,
 *		  OUT afsUUID *uuidp1,
 *		  OUT uपूर्णांक32_t *uniquअगरier,
 *		  OUT uपूर्णांक32_t *nentries,
 *		  OUT bulkaddrs *blkaddrs);
 */
अटल पूर्णांक afs_deliver_vl_get_addrs_u(काष्ठा afs_call *call)
अणु
	काष्ठा afs_addr_list *alist;
	__be32 *bp;
	u32 uniquअगरier, nentries, count;
	पूर्णांक i, ret;

	_enter("{%u,%zu/%u}",
	       call->unmarshall, iov_iter_count(call->iter), call->count);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_buf(call,
				   माप(काष्ठा afs_uuid__xdr) + 3 * माप(__be32));
		call->unmarshall++;

		/* Extract the वापसed uuid, uniquअगरier, nentries and
		 * blkaddrs size */
		fallthrough;
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer + माप(काष्ठा afs_uuid__xdr);
		uniquअगरier	= ntohl(*bp++);
		nentries	= ntohl(*bp++);
		count		= ntohl(*bp);

		nentries = min(nentries, count);
		alist = afs_alloc_addrlist(nentries, FS_SERVICE, AFS_FS_PORT);
		अगर (!alist)
			वापस -ENOMEM;
		alist->version = uniquअगरier;
		call->ret_alist = alist;
		call->count = count;
		call->count2 = nentries;
		call->unmarshall++;

	more_entries:
		count = min(call->count, 4U);
		afs_extract_to_buf(call, count * माप(__be32));

		fallthrough;	/* and extract entries */
	हाल 2:
		ret = afs_extract_data(call, call->count > 4);
		अगर (ret < 0)
			वापस ret;

		alist = call->ret_alist;
		bp = call->buffer;
		count = min(call->count, 4U);
		क्रम (i = 0; i < count; i++)
			अगर (alist->nr_addrs < call->count2)
				afs_merge_fs_addr4(alist, *bp++, AFS_FS_PORT);

		call->count -= count;
		अगर (call->count > 0)
			जाओ more_entries;
		call->unmarshall++;
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

अटल व्योम afs_vl_get_addrs_u_deकाष्ठाor(काष्ठा afs_call *call)
अणु
	afs_put_addrlist(call->ret_alist);
	वापस afs_flat_call_deकाष्ठाor(call);
पूर्ण

/*
 * VL.GetAddrsU operation type.
 */
अटल स्थिर काष्ठा afs_call_type afs_RXVLGetAddrsU = अणु
	.name		= "VL.GetAddrsU",
	.op		= afs_VL_GetAddrsU,
	.deliver	= afs_deliver_vl_get_addrs_u,
	.deकाष्ठाor	= afs_vl_get_addrs_u_deकाष्ठाor,
पूर्ण;

/*
 * Dispatch an operation to get the addresses क्रम a server, where the server is
 * nominated by UUID.
 */
काष्ठा afs_addr_list *afs_vl_get_addrs_u(काष्ठा afs_vl_cursor *vc,
					 स्थिर uuid_t *uuid)
अणु
	काष्ठा afs_ListAddrByAttributes__xdr *r;
	स्थिर काष्ठा afs_uuid *u = (स्थिर काष्ठा afs_uuid *)uuid;
	काष्ठा afs_call *call;
	काष्ठा afs_net *net = vc->cell->net;
	__be32 *bp;
	पूर्णांक i;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXVLGetAddrsU,
				   माप(__be32) + माप(काष्ठा afs_ListAddrByAttributes__xdr),
				   माप(काष्ठा afs_uuid__xdr) + 3 * माप(__be32));
	अगर (!call)
		वापस ERR_PTR(-ENOMEM);

	call->key = vc->key;
	call->ret_alist = शून्य;
	call->max_lअगरespan = AFS_VL_MAX_LIFESPAN;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETADDRSU);
	r = (काष्ठा afs_ListAddrByAttributes__xdr *)bp;
	r->Mask		= htonl(AFS_VLADDR_UUID);
	r->ipaddr	= 0;
	r->index	= 0;
	r->spare	= 0;
	r->uuid.समय_low			= u->समय_low;
	r->uuid.समय_mid			= htonl(ntohs(u->समय_mid));
	r->uuid.समय_hi_and_version		= htonl(ntohs(u->समय_hi_and_version));
	r->uuid.घड़ी_seq_hi_and_reserved 	= htonl(u->घड़ी_seq_hi_and_reserved);
	r->uuid.घड़ी_seq_low			= htonl(u->घड़ी_seq_low);
	क्रम (i = 0; i < 6; i++)
		r->uuid.node[i] = htonl(u->node[i]);

	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	वापस (काष्ठा afs_addr_list *)afs_रुको_क्रम_call_to_complete(call, &vc->ac);
पूर्ण

/*
 * Deliver reply data to an VL.GetCapabilities operation.
 */
अटल पूर्णांक afs_deliver_vl_get_capabilities(काष्ठा afs_call *call)
अणु
	u32 count;
	पूर्णांक ret;

	_enter("{%u,%zu/%u}",
	       call->unmarshall, iov_iter_count(call->iter), call->count);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;

		fallthrough;	/* and extract the capabilities word count */
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		count = ntohl(call->पंचांगp);
		call->count = count;
		call->count2 = count;

		call->unmarshall++;
		afs_extract_discard(call, count * माप(__be32));

		fallthrough;	/* and extract capabilities words */
	हाल 2:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		/* TODO: Examine capabilities */

		call->unmarshall++;
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

अटल व्योम afs_destroy_vl_get_capabilities(काष्ठा afs_call *call)
अणु
	afs_put_vlserver(call->net, call->vlserver);
	afs_flat_call_deकाष्ठाor(call);
पूर्ण

/*
 * VL.GetCapabilities operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXVLGetCapabilities = अणु
	.name		= "VL.GetCapabilities",
	.op		= afs_VL_GetCapabilities,
	.deliver	= afs_deliver_vl_get_capabilities,
	.करोne		= afs_vlserver_probe_result,
	.deकाष्ठाor	= afs_destroy_vl_get_capabilities,
पूर्ण;

/*
 * Probe a volume server क्रम the capabilities that it supports.  This can
 * वापस up to 196 words.
 *
 * We use this to probe क्रम service upgrade to determine what the server at the
 * other end supports.
 */
काष्ठा afs_call *afs_vl_get_capabilities(काष्ठा afs_net *net,
					 काष्ठा afs_addr_cursor *ac,
					 काष्ठा key *key,
					 काष्ठा afs_vlserver *server,
					 अचिन्हित पूर्णांक server_index)
अणु
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXVLGetCapabilities, 1 * 4, 16 * 4);
	अगर (!call)
		वापस ERR_PTR(-ENOMEM);

	call->key = key;
	call->vlserver = afs_get_vlserver(server);
	call->server_index = server_index;
	call->upgrade = true;
	call->async = true;
	call->max_lअगरespan = AFS_PROBE_MAX_LIFESPAN;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(VLGETCAPABILITIES);

	/* Can't take a ref on server */
	trace_afs_make_vl_call(call);
	afs_make_call(ac, call, GFP_KERNEL);
	वापस call;
पूर्ण

/*
 * Deliver reply data to a YFSVL.GetEndpoपूर्णांकs call.
 *
 *	GetEndpoपूर्णांकs(IN yfsServerAttributes *attr,
 *		     OUT opr_uuid *uuid,
 *		     OUT afs_पूर्णांक32 *uniquअगरier,
 *		     OUT endpoपूर्णांकs *fsEndpoपूर्णांकs,
 *		     OUT endpoपूर्णांकs *volEndpoपूर्णांकs)
 */
अटल पूर्णांक afs_deliver_yfsvl_get_endpoपूर्णांकs(काष्ठा afs_call *call)
अणु
	काष्ठा afs_addr_list *alist;
	__be32 *bp;
	u32 uniquअगरier, size;
	पूर्णांक ret;

	_enter("{%u,%zu,%u}",
	       call->unmarshall, iov_iter_count(call->iter), call->count2);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_buf(call, माप(uuid_t) + 3 * माप(__be32));
		call->unmarshall = 1;

		/* Extract the वापसed uuid, uniquअगरier, fsEndpoपूर्णांकs count and
		 * either the first fsEndpoपूर्णांक type or the volEndpoपूर्णांकs
		 * count अगर there are no fsEndpoपूर्णांकs. */
		fallthrough;
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer + माप(uuid_t);
		uniquअगरier	= ntohl(*bp++);
		call->count	= ntohl(*bp++);
		call->count2	= ntohl(*bp); /* Type or next count */

		अगर (call->count > YFS_MAXENDPOINTS)
			वापस afs_protocol_error(call, afs_eproto_yvl_fsendpt_num);

		alist = afs_alloc_addrlist(call->count, FS_SERVICE, AFS_FS_PORT);
		अगर (!alist)
			वापस -ENOMEM;
		alist->version = uniquअगरier;
		call->ret_alist = alist;

		अगर (call->count == 0)
			जाओ extract_volendpoपूर्णांकs;

	next_fsendpoपूर्णांक:
		चयन (call->count2) अणु
		हाल YFS_ENDPOINT_IPV4:
			size = माप(__be32) * (1 + 1 + 1);
			अवरोध;
		हाल YFS_ENDPOINT_IPV6:
			size = माप(__be32) * (1 + 4 + 1);
			अवरोध;
		शेष:
			वापस afs_protocol_error(call, afs_eproto_yvl_fsendpt_type);
		पूर्ण

		size += माप(__be32);
		afs_extract_to_buf(call, size);
		call->unmarshall = 2;

		fallthrough;	/* and extract fsEndpoपूर्णांकs[] entries */
	हाल 2:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		alist = call->ret_alist;
		bp = call->buffer;
		चयन (call->count2) अणु
		हाल YFS_ENDPOINT_IPV4:
			अगर (ntohl(bp[0]) != माप(__be32) * 2)
				वापस afs_protocol_error(
					call, afs_eproto_yvl_fsendpt4_len);
			afs_merge_fs_addr4(alist, bp[1], ntohl(bp[2]));
			bp += 3;
			अवरोध;
		हाल YFS_ENDPOINT_IPV6:
			अगर (ntohl(bp[0]) != माप(__be32) * 5)
				वापस afs_protocol_error(
					call, afs_eproto_yvl_fsendpt6_len);
			afs_merge_fs_addr6(alist, bp + 1, ntohl(bp[5]));
			bp += 6;
			अवरोध;
		शेष:
			वापस afs_protocol_error(call, afs_eproto_yvl_fsendpt_type);
		पूर्ण

		/* Got either the type of the next entry or the count of
		 * volEndpoपूर्णांकs अगर no more fsEndpoपूर्णांकs.
		 */
		call->count2 = ntohl(*bp++);

		call->count--;
		अगर (call->count > 0)
			जाओ next_fsendpoपूर्णांक;

	extract_volendpoपूर्णांकs:
		/* Extract the list of volEndpoपूर्णांकs. */
		call->count = call->count2;
		अगर (!call->count)
			जाओ end;
		अगर (call->count > YFS_MAXENDPOINTS)
			वापस afs_protocol_error(call, afs_eproto_yvl_vlendpt_type);

		afs_extract_to_buf(call, 1 * माप(__be32));
		call->unmarshall = 3;

		/* Extract the type of volEndpoपूर्णांकs[0].  Normally we would
		 * extract the type of the next endpoपूर्णांक when we extract the
		 * data of the current one, but this is the first...
		 */
		fallthrough;
	हाल 3:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;

	next_volendpoपूर्णांक:
		call->count2 = ntohl(*bp++);
		चयन (call->count2) अणु
		हाल YFS_ENDPOINT_IPV4:
			size = माप(__be32) * (1 + 1 + 1);
			अवरोध;
		हाल YFS_ENDPOINT_IPV6:
			size = माप(__be32) * (1 + 4 + 1);
			अवरोध;
		शेष:
			वापस afs_protocol_error(call, afs_eproto_yvl_vlendpt_type);
		पूर्ण

		अगर (call->count > 1)
			size += माप(__be32); /* Get next type too */
		afs_extract_to_buf(call, size);
		call->unmarshall = 4;

		fallthrough;	/* and extract volEndpoपूर्णांकs[] entries */
	हाल 4:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		चयन (call->count2) अणु
		हाल YFS_ENDPOINT_IPV4:
			अगर (ntohl(bp[0]) != माप(__be32) * 2)
				वापस afs_protocol_error(
					call, afs_eproto_yvl_vlendpt4_len);
			bp += 3;
			अवरोध;
		हाल YFS_ENDPOINT_IPV6:
			अगर (ntohl(bp[0]) != माप(__be32) * 5)
				वापस afs_protocol_error(
					call, afs_eproto_yvl_vlendpt6_len);
			bp += 6;
			अवरोध;
		शेष:
			वापस afs_protocol_error(call, afs_eproto_yvl_vlendpt_type);
		पूर्ण

		/* Got either the type of the next entry or the count of
		 * volEndpoपूर्णांकs अगर no more fsEndpoपूर्णांकs.
		 */
		call->count--;
		अगर (call->count > 0)
			जाओ next_volendpoपूर्णांक;

	end:
		afs_extract_discard(call, 0);
		call->unmarshall = 5;

		fallthrough;	/* Done */
	हाल 5:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;
		call->unmarshall = 6;
		fallthrough;

	हाल 6:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFSVL.GetEndpoपूर्णांकs operation type.
 */
अटल स्थिर काष्ठा afs_call_type afs_YFSVLGetEndpoपूर्णांकs = अणु
	.name		= "YFSVL.GetEndpoints",
	.op		= afs_YFSVL_GetEndpoपूर्णांकs,
	.deliver	= afs_deliver_yfsvl_get_endpoपूर्णांकs,
	.deकाष्ठाor	= afs_vl_get_addrs_u_deकाष्ठाor,
पूर्ण;

/*
 * Dispatch an operation to get the addresses क्रम a server, where the server is
 * nominated by UUID.
 */
काष्ठा afs_addr_list *afs_yfsvl_get_endpoपूर्णांकs(काष्ठा afs_vl_cursor *vc,
					      स्थिर uuid_t *uuid)
अणु
	काष्ठा afs_call *call;
	काष्ठा afs_net *net = vc->cell->net;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_YFSVLGetEndpoपूर्णांकs,
				   माप(__be32) * 2 + माप(*uuid),
				   माप(काष्ठा in6_addr) + माप(__be32) * 3);
	अगर (!call)
		वापस ERR_PTR(-ENOMEM);

	call->key = vc->key;
	call->ret_alist = शून्य;
	call->max_lअगरespan = AFS_VL_MAX_LIFESPAN;

	/* Marshall the parameters */
	bp = call->request;
	*bp++ = htonl(YVLGETENDPOINTS);
	*bp++ = htonl(YFS_SERVER_UUID);
	स_नकल(bp, uuid, माप(*uuid)); /* Type opr_uuid */

	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	वापस (काष्ठा afs_addr_list *)afs_रुको_क्रम_call_to_complete(call, &vc->ac);
पूर्ण

/*
 * Deliver reply data to a YFSVL.GetCellName operation.
 */
अटल पूर्णांक afs_deliver_yfsvl_get_cell_name(काष्ठा afs_call *call)
अणु
	अक्षर *cell_name;
	u32 namesz, paddedsz;
	पूर्णांक ret;

	_enter("{%u,%zu/%u}",
	       call->unmarshall, iov_iter_count(call->iter), call->count);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;

		fallthrough;	/* and extract the cell name length */
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		namesz = ntohl(call->पंचांगp);
		अगर (namesz > AFS_MAXCELLNAME)
			वापस afs_protocol_error(call, afs_eproto_cellname_len);
		paddedsz = (namesz + 3) & ~3;
		call->count = namesz;
		call->count2 = paddedsz - namesz;

		cell_name = kदो_स्मृति(namesz + 1, GFP_KERNEL);
		अगर (!cell_name)
			वापस -ENOMEM;
		cell_name[namesz] = 0;
		call->ret_str = cell_name;

		afs_extract_begin(call, cell_name, namesz);
		call->unmarshall++;

		fallthrough;	/* and extract cell name */
	हाल 2:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		afs_extract_discard(call, call->count2);
		call->unmarshall++;

		fallthrough;	/* and extract padding */
	हाल 3:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		call->unmarshall++;
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

अटल व्योम afs_destroy_yfsvl_get_cell_name(काष्ठा afs_call *call)
अणु
	kमुक्त(call->ret_str);
	afs_flat_call_deकाष्ठाor(call);
पूर्ण

/*
 * VL.GetCapabilities operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_YFSVLGetCellName = अणु
	.name		= "YFSVL.GetCellName",
	.op		= afs_YFSVL_GetCellName,
	.deliver	= afs_deliver_yfsvl_get_cell_name,
	.deकाष्ठाor	= afs_destroy_yfsvl_get_cell_name,
पूर्ण;

/*
 * Probe a volume server क्रम the capabilities that it supports.  This can
 * वापस up to 196 words.
 *
 * We use this to probe क्रम service upgrade to determine what the server at the
 * other end supports.
 */
अक्षर *afs_yfsvl_get_cell_name(काष्ठा afs_vl_cursor *vc)
अणु
	काष्ठा afs_call *call;
	काष्ठा afs_net *net = vc->cell->net;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_YFSVLGetCellName, 1 * 4, 0);
	अगर (!call)
		वापस ERR_PTR(-ENOMEM);

	call->key = vc->key;
	call->ret_str = शून्य;
	call->max_lअगरespan = AFS_VL_MAX_LIFESPAN;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(YVLGETCELLNAME);

	/* Can't take a ref on server */
	trace_afs_make_vl_call(call);
	afs_make_call(&vc->ac, call, GFP_KERNEL);
	वापस (अक्षर *)afs_रुको_क्रम_call_to_complete(call, &vc->ac);
पूर्ण
